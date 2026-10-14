/* decomp/H/FVector.c — cleaned Ghidra output (SH2JP_BATTLE.BIN, JP Furokuban, base 0x00430a00).
 * 10 function(s). Types: see types.h. Names/gp globals resolved from symbols/SLPM_602.19.syms. */
#include "types.h"

/* ---------------------------------------------------------------------------
 * JP: 0x0044b1c0  __ct__7FVectorFffff
 * C++: FVector::__ct(float, float, float, float)
 * size: 0x84 bytes
 * --------------------------------------------------------------------------- */
undefined4 *
__ct__7FVectorFffff(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                   undefined4 *param_5)

{
  *param_5 = param_1;
  param_5[1] = param_2;
  param_5[2] = param_3;
  param_5[3] = param_4;
  return param_5;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0044b250  __as__7FVectorFRC7FVector
 * C++: FVector::__as(FVector *)
 * size: 0x14 bytes
 * --------------------------------------------------------------------------- */
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

/* ---------------------------------------------------------------------------
 * JP: 0x0044b2d0  __mi__7FVectorCFRC7FVector
 * C++: FVector::__mi(FVector *)
 * size: 0x3c bytes
 * --------------------------------------------------------------------------- */
void __mi__7FVectorCFRC7FVector
               (undefined8 param_1,undefined1 (*param_2) [16],undefined1 (*param_3) [16])

{
  undefined1 auVar1 [16];
  undefined1 auVar2 [16];
  undefined1 auStack_10 [16];
  
  auVar1 = _lqc2(*param_2);
  auVar2 = _lqc2(*param_3);
  auVar1 = _vsub(auVar1,auVar2);
  auStack_10 = _sqc2(auVar1);
  __ct__7FVectorFRC7FVector(param_1,auStack_10);
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0044b3b0  __pl__7FVectorCFRC7FVector
 * C++: FVector::__pl(FVector *)
 * size: 0x3c bytes
 * --------------------------------------------------------------------------- */
void __pl__7FVectorCFRC7FVector
               (undefined8 param_1,undefined1 (*param_2) [16],undefined1 (*param_3) [16])

{
  undefined1 auVar1 [16];
  undefined1 auVar2 [16];
  undefined1 auStack_10 [16];
  
  auVar1 = _lqc2(*param_2);
  auVar2 = _lqc2(*param_3);
  auVar1 = _vadd(auVar1,auVar2);
  auStack_10 = _sqc2(auVar1);
  __ct__7FVectorFRC7FVector(param_1,auStack_10);
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0044b3f0  vw__7FVectorFv
 * C++: FVector::vw()
 * size: 0x1c bytes
 * --------------------------------------------------------------------------- */
int vw__7FVectorFv(int param_1)

{
  return param_1 + 0xc;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0044b410  vz__7FVectorFv
 * C++: FVector::vz()
 * size: 0x1c bytes
 * --------------------------------------------------------------------------- */
int vz__7FVectorFv(int param_1)

{
  return param_1 + 8;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0044b430  vy__7FVectorFv
 * C++: FVector::vy()
 * size: 0x1c bytes
 * --------------------------------------------------------------------------- */
int vy__7FVectorFv(int param_1)

{
  return param_1 + 4;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0044b450  vx__7FVectorFv
 * C++: FVector::vx()
 * size: 0x18 bytes
 * --------------------------------------------------------------------------- */
undefined4 vx__7FVectorFv(undefined4 param_1)

{
  return param_1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00548b80  __ct__7FVectorFv
 * C++: FVector::__ct()
 * size: 0x20 bytes
 * --------------------------------------------------------------------------- */
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

/* ---------------------------------------------------------------------------
 * JP: 0x0057bfa0  __ml__7FVectorCFf
 * C++: FVector::__ml(float)
 * size: 0x44 bytes
 * --------------------------------------------------------------------------- */
void __ml__7FVectorCFf(undefined4 param_1,undefined8 param_2,undefined1 (*param_3) [16])

{
  undefined1 auVar1 [16];
  undefined1 auVar2 [16];
  undefined1 auStack_10 [16];
  
  auVar1 = _lqc2(*param_3);
  auVar2 = _qmtc2(param_1);
  auVar1 = _vmulbc(auVar1,auVar2);
  auStack_10 = _sqc2(auVar1);
  __ct__7FVectorFRC7FVector(param_2,auStack_10);
  return;
}

