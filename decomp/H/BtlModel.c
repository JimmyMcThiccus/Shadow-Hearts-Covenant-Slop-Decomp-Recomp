/* decomp/H/BtlModel.c — cleaned Ghidra output (SH2JP_BATTLE.BIN, JP Furokuban, base 0x00430a00).
 * 45 function(s). Types: see types.h. Names/gp globals resolved from symbols/SLPM_602.19.syms. */
#include "types.h"

/* ---------------------------------------------------------------------------
 * JP: 0x00480ec0  GetPos__8BtlModelFv
 * C++: BtlModel::GetPos()
 * size: 0x1c bytes
 * --------------------------------------------------------------------------- */
int GetPos__8BtlModelFv(int param_1)

{
  return param_1 + 0x4c0;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b9c0  __ct__8BtlModelFs
 * C++: BtlModel::__ct(short)
 * size: 0x208 bytes
 * --------------------------------------------------------------------------- */
undefined8 __ct__8BtlModelFs(undefined8 param_1,undefined2 param_2)

{
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  int iVar1;
  
  __ct__5ModelFv(param_1);
  iVar1 = (int)param_1;
  *(undefined4 *)(iVar1 + 0x10) = 0x40a630;
  *(undefined4 *)(iVar1 + 0x1c) = 0x40a640;
  *(undefined4 *)(iVar1 + 0x4c0) = in_zero_lo;
  *(undefined4 *)(iVar1 + 0x4c4) = in_zero_hi;
  *(undefined4 *)(iVar1 + 0x4c8) = in_zero_udw;
  *(undefined4 *)(iVar1 + 0x4cc) = in_register_0000000c;
  *(undefined4 *)(iVar1 + 0x4d0) = in_zero_lo;
  *(undefined4 *)(iVar1 + 0x4d4) = in_zero_hi;
  *(undefined4 *)(iVar1 + 0x4d8) = in_zero_udw;
  *(undefined4 *)(iVar1 + 0x4dc) = in_register_0000000c;
  *(undefined4 *)(iVar1 + 0x550) = in_zero_lo;
  *(undefined4 *)(iVar1 + 0x554) = in_zero_hi;
  *(undefined4 *)(iVar1 + 0x558) = in_zero_udw;
  *(undefined4 *)(iVar1 + 0x55c) = in_register_0000000c;
  *(undefined4 *)(iVar1 + 0x5c0) = in_zero_lo;
  *(undefined4 *)(iVar1 + 0x5c4) = in_zero_hi;
  *(undefined4 *)(iVar1 + 0x5c8) = in_zero_udw;
  *(undefined4 *)(iVar1 + 0x5cc) = in_register_0000000c;
  *(undefined4 *)(iVar1 + 0x5d0) = in_zero_lo;
  *(undefined4 *)(iVar1 + 0x5d4) = in_zero_hi;
  *(undefined4 *)(iVar1 + 0x5d8) = in_zero_udw;
  *(undefined4 *)(iVar1 + 0x5dc) = in_register_0000000c;
  *(undefined4 *)(iVar1 + 0x4b0) = 0;
  *(undefined2 *)(iVar1 + 0x4b4) = param_2;
  *(undefined4 *)(iVar1 + 0x4c0) = 0;
  *(undefined4 *)(iVar1 + 0x4c4) = 0;
  *(undefined4 *)(iVar1 + 0x4c8) = 0;
  *(undefined4 *)(iVar1 + 0x4cc) = 0x3f800000;
  *(undefined4 *)(iVar1 + 0x4d0) = 0;
  *(undefined4 *)(iVar1 + 0x4d4) = 0;
  *(undefined4 *)(iVar1 + 0x4d8) = 0;
  *(undefined4 *)(iVar1 + 0x4dc) = 0x3f800000;
  *(undefined4 *)(iVar1 + 0x4e0) = 0x3f800000;
  *(undefined4 *)(iVar1 + 0x4e4) = 0x3f800000;
  *(undefined4 *)(iVar1 + 0x4ec) = 0x3f800000;
  *(undefined4 *)(iVar1 + 0x4e8) = 0x3f800000;
  *(undefined2 *)(iVar1 + 0x4f0) = 0;
  *(undefined2 *)(iVar1 + 0x4f2) = 0;
  *(undefined4 *)(iVar1 + 0x518) = 0x3f800000;
  *(undefined4 *)(iVar1 + 0x51c) = 0x3f800000;
  *(undefined4 *)(iVar1 + 0x528) = 0x43000000;
  *(undefined4 *)(iVar1 + 0x524) = 0x43000000;
  *(undefined4 *)(iVar1 + 0x520) = 0x43000000;
  *(undefined4 *)(iVar1 + 0x534) = 0;
  *(undefined4 *)(iVar1 + 0x530) = 0;
  *(undefined4 *)(iVar1 + 0x52c) = 0;
  *(undefined4 *)(iVar1 + 0x544) = 0;
  *(undefined4 *)(iVar1 + 0x540) = 0;
  *(undefined4 *)(iVar1 + 0x53c) = 0;
  *(undefined4 *)(iVar1 + 0x538) = 0;
  *(undefined4 *)(iVar1 + 0x56c) = 0;
  *(undefined4 *)(iVar1 + 0x564) = 0;
  *(undefined4 *)(iVar1 + 0x568) = 0;
  *(undefined4 *)(iVar1 + 0x560) = 0;
  *(undefined4 *)(iVar1 + 0x550) = 0;
  *(undefined4 *)(iVar1 + 0x554) = 0;
  *(undefined4 *)(iVar1 + 0x558) = 0;
  *(undefined4 *)(iVar1 + 0x55c) = 0x3f800000;
  *(undefined4 *)(iVar1 + 0x574) = 0xffffffff;
  *(undefined4 *)(iVar1 + 0x584) = 0xffffffff;
  *(undefined4 *)(iVar1 + 0x594) = 0xffffffff;
  *(undefined4 *)(iVar1 + 0x5a4) = 0xffffffff;
  *(undefined4 *)(iVar1 + 0x5b0) = 0xffffffff;
  return param_1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054bbd0  __dt__8BtlModelFv
 * C++: BtlModel::__dt()
 * size: 0x220 bytes
 * --------------------------------------------------------------------------- */
int __dt__8BtlModelFv(int param_1,short param_2)

{
  int iVar1;
  
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0x10) = 0x40a630;
    *(undefined4 *)(param_1 + 0x1c) = 0x40a640;
    if ((*(int *)(param_1 + 0x560) != 0) && (*(int *)(param_1 + 0x560) != 0)) {
      __dla__FPv(*(int *)(param_1 + 0x560) + -0x10);
    }
    if ((*(int *)(param_1 + 0x568) != 0) && (*(int *)(param_1 + 0x568) != 0)) {
      __dla__FPv(*(int *)(param_1 + 0x568) + -0x10);
    }
    if ((*(int *)(param_1 + 0x564) != 0) && (*(int *)(param_1 + 0x564) != 0)) {
      __dla__FPv(*(int *)(param_1 + 0x564) + -0x10);
    }
    if ((*(int *)(param_1 + 0x56c) != 0) && (*(int *)(param_1 + 0x56c) != 0)) {
      __dla__FPv(*(int *)(param_1 + 0x56c) + -0x10);
    }
    if (*(int *)(param_1 + 0x52c) != 0) {
      iVar1 = *(int *)(param_1 + 0x52c);
      if (iVar1 != 0) {
        (**(code **)(*(int *)(iVar1 + 0x10) + 8))(iVar1,1);
      }
    }
    if (*(int *)(param_1 + 0x530) != 0) {
      iVar1 = *(int *)(param_1 + 0x530);
      if (iVar1 != 0) {
        (**(code **)(*(int *)(iVar1 + 0x10) + 8))(iVar1,1);
      }
    }
    if (*(int *)(param_1 + 0x534) != 0) {
      iVar1 = *(int *)(param_1 + 0x534);
      if (iVar1 != 0) {
        (**(code **)(*(int *)(iVar1 + 0x10) + 8))(iVar1,1);
      }
    }
    __dt__5ModelFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054bdf0  DeleteSetUp__8BtlModelFv
 * C++: BtlModel::DeleteSetUp()
 * size: 0x2ac bytes
 * --------------------------------------------------------------------------- */
void DeleteSetUp__8BtlModelFv(int param_1)

{
  long lVar1;
  
  if (((*(float *)(param_1 + 0x550) != 0.0) || (*(float *)(param_1 + 0x554) != 0.0)) ||
     (*(float *)(param_1 + 0x558) != 0.0)) {
    ClutCtrl__8BtlModelFffff(0,0,0,0,param_1);
  }
  if ((long)((ulong)*(byte *)(param_1 + 0x4b1) << 0x3b) < 0) {
    deleteMF__15ModelEffManagerFP5Model(param_1);
  }
  *(undefined4 *)(param_1 + 0x574) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x584) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x594) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x5a4) = 0xffffffff;
  *(byte *)(param_1 + 0x4b1) = *(byte *)(param_1 + 0x4b1) & 0xef;
  if (*(int *)(param_1 + 0x52c) != 0) {
    (**(code **)(*(int *)(*(int *)(param_1 + 0x52c) + 0x10) + 0x40))();
    while (lVar1 = FindOT__5WorldFP8VIF1Prim(0x42bf10,*(undefined4 *)(param_1 + 0x52c)), lVar1 != 0) {
      ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,*(undefined4 *)(param_1 + 0x52c));
    }
  }
  if (*(int *)(param_1 + 0x530) != 0) {
    (**(code **)(*(int *)(*(int *)(param_1 + 0x530) + 0x10) + 0x40))();
    while (lVar1 = FindOT__5WorldFP8VIF1Prim(0x42bf10,*(undefined4 *)(param_1 + 0x530)), lVar1 != 0) {
      ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,*(undefined4 *)(param_1 + 0x530));
    }
  }
  if (*(int *)(param_1 + 0x534) != 0) {
    (**(code **)(*(int *)(*(int *)(param_1 + 0x534) + 0x10) + 0x40))();
    while (lVar1 = FindOT__5WorldFP8VIF1Prim(0x42bf10,*(undefined4 *)(param_1 + 0x534)), lVar1 != 0) {
      ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,*(undefined4 *)(param_1 + 0x534));
    }
  }
  DeleteSetUp__5ModelFv(param_1);
  while (lVar1 = FindOT__5WorldFP8VIF1Prim(0x42bf10,param_1), lVar1 != 0) {
    ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,param_1);
  }
  *(byte *)(param_1 + 0x4b0) = *(byte *)(param_1 + 0x4b0) & 0xfd;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054c0a0  Create__8BtlModelFPUc
 * C++: BtlModel::Create(uchar *)
 * size: 0x234 bytes
 * --------------------------------------------------------------------------- */
undefined4 Create__8BtlModelFPUc(int param_1,undefined4 param_2)

{
  ushort uVar1;
  char cVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  int iVar5;
  int iVar6;
  
  cVar2 = create__5ModelFPUc(param_1,param_2);
  if (cVar2 == '\0') {
    uVar3 = 0;
  }
  else {
    *(byte *)(param_1 + 0x4b0) = *(byte *)(param_1 + 0x4b0) & 0xfe | 1;
    if ((*(int *)(param_1 + 0x560) != 0) && (*(int *)(param_1 + 0x560) != 0)) {
      __dla__FPv(*(int *)(param_1 + 0x560) + -0x10);
    }
    uVar1 = *(ushort *)(*(int *)(param_1 + 100) + 4);
    uVar4 = __nwa__FUi((uint)uVar1 * 0x410 + 0x10);
    uVar3 = __construct_new_array(uVar4,0x51c130,0,0x410,uVar1);
    *(undefined4 *)(param_1 + 0x560) = uVar3;
    for (iVar5 = 0; iVar5 < (int)(uint)*(ushort *)(*(int *)(param_1 + 100) + 4); iVar5 = iVar5 + 1)
    {
      *(undefined4 *)(*(int *)(param_1 + 0x560) + iVar5 * 0x410 + 0x400) =
           **(undefined4 **)(*(int *)(param_1 + 0x4c) + iVar5 * 0x4c + 0xc);
      for (iVar6 = 0; iVar6 < *(int *)(*(int *)(*(int *)(param_1 + 0x4c) + iVar5 * 0x4c + 0xc) + 4);
          iVar6 = iVar6 + 1) {
        *(undefined1 *)(*(int *)(param_1 + 0x560) + iVar5 * 0x410 + iVar6 * 4 + 3) =
             *(undefined1 *)
              (*(int *)(*(int *)(param_1 + 0x560) + iVar5 * 0x410 + 0x400) + iVar6 * 4 + 3);
      }
    }
    (**(code **)(*(int *)(param_1 + 0x10) + 0x28))(param_1,0);
    uVar3 = 1;
  }
  return uVar3;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054c2e0  CreateShadow__8BtlModelFPUc
 * C++: BtlModel::CreateShadow(uchar *)
 * size: 0x44 bytes
 * --------------------------------------------------------------------------- */
undefined4 CreateShadow__8BtlModelFPUc(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 0x538) = param_2;
  createLevelofDetale__5ModelFPUcUi(param_1,param_2,2);
  return 1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054c330  TranseCallBack__8BtlModelFRC7FVector7FVector
 * C++: BtlModel::TranseCallBack(FVector *, FVector)
 * size: 0x268 bytes
 * --------------------------------------------------------------------------- */
void TranseCallBack__8BtlModelFRC7FVector7FVector
               (undefined8 param_1,int param_2,float *param_3,undefined8 param_4)

{
  short sVar1;
  float *pfVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined1 auStack_70 [8];
  float fStack_68;
  float fStack_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined1 auStack_40 [64];
  
  sVar1 = *(short *)(param_2 + 0x4f0);
  pfVar2 = (float *)param_4;
  if (sVar1 == 0x20) {
    pfVar2[2] = 0.0;
  }
  else if (sVar1 == 0x19) {
    if ((long)((ulong)*(byte *)(param_2 + 0x4b0) << 0x3d) < 0) {
      *pfVar2 = 0.0;
      pfVar2[1] = 0.0;
      pfVar2[2] = 0.0;
    }
  }
  else if (((sVar1 == 2) || (sVar1 == 1)) && ((long)((ulong)*(byte *)(param_2 + 0x4b0) << 0x3d) < 0)
          ) {
    *pfVar2 = 0.0;
    pfVar2[1] = 0.0;
    pfVar2[2] = 0.0;
  }
  __amu__7FVectorFf(*(undefined4 *)(param_2 + 0x4e0),param_4);
  __amu__7FVectorFf(*(undefined4 *)(param_2 + 0x518),param_4);
  uStack_60 = 0;
  uStack_5c = 0;
  uStack_58 = 0;
  uStack_54 = 0x3f800000;
  uVar3 = GetRad(*(undefined4 *)(param_2 + 0x4d8));
  uVar4 = GetRad(*(undefined4 *)(param_2 + 0x4d4));
  uStack_50 = GetRad(*(undefined4 *)(param_2 + 0x4d0));
  uStack_44 = 0x3f800000;
  uStack_4c = uVar4;
  uStack_48 = uVar3;
  __ct__6MatrixFRC7FVectorRC7FVector(auStack_40,&uStack_50,&uStack_60);
  ApplyMatrix__6MatrixCFRC7FVector(auStack_70,auStack_40,param_4);
  *pfVar2 = auStack_70._0_4_;
  pfVar2[1] = auStack_70._4_4_;
  pfVar2[2] = fStack_68;
  pfVar2[3] = fStack_64;
  *(float *)(param_2 + 0x4c0) = *param_3 + *pfVar2;
  *(float *)(param_2 + 0x4c4) = param_3[1] + pfVar2[1];
  *(float *)(param_2 + 0x4c8) = param_3[2] + pfVar2[2];
  *(undefined4 *)(param_2 + 0x4cc) = 0x3f800000;
  __ct__7FVectorFRC7FVector(param_1,param_4);
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054c5a0  EventCallBack__8BtlModelFPCcPCciiUi
 * C++: BtlModel::EventCallBack(char *, char *, int, int, uint)
 * size: 0x7c bytes
 * --------------------------------------------------------------------------- */
void EventCallBack__8BtlModelFPCcPCciiUi
               (int param_1,char *param_2,char *param_3,undefined4 param_4,int param_5,uint param_6)

{
  EventCallBack__5ModelFPCcPCciiUi(param_1,param_2,param_3,param_4,param_5,param_6);
  MotionEventCallBack__7CBattleFsPCcPCcUsiUi
            (pCGpffff86b4,*(short *)(param_1 + 0x4b4),param_2,param_3,(ushort)param_4,param_5,
             param_6);
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054c620  MotionEndCallBack__8BtlModelFPCc
 * C++: BtlModel::MotionEndCallBack(char *)
 * size: 0x1644 bytes
 * --------------------------------------------------------------------------- */
void MotionEndCallBack__8BtlModelFPCc(int param_1,char *param_2)

{
  long lVar1;
  undefined8 uVar2;
  
  lVar1 = strcmp(param_2,0x652d60);
  if (lVar1 == 0) {
    *(byte *)(param_1 + 0x4b0) = *(byte *)(param_1 + 0x4b0) & 0xfb;
  }
  else {
    MotionEndCallBack__7CBattleFsPCc(pCGpffff86b4,*(short *)(param_1 + 0x4b4),param_2);
    switch(*(undefined2 *)(param_1 + 0x4f0)) {
    case 3:
      *(byte *)(param_1 + 0x4b0) = *(byte *)(param_1 + 0x4b0) & 0xfb | 4;
      setNextMotion__8BtlModelFPCc(param_1,param_1 + 0x50c);
      strcpy(param_1 + 0x4f4,param_1 + 0x50c);
      *(undefined1 *)(param_1 + 0x500) = 0;
      *(undefined2 *)(param_1 + 0x4f0) = 1;
      *(undefined2 *)(param_1 + 0x4f2) = 0;
      *(undefined4 *)(param_1 + 0x518) = 0x3f800000;
      break;
    case 5:
      *(byte *)(param_1 + 0x4b0) = *(byte *)(param_1 + 0x4b0) & 0xfb | 4;
      setNextMotion__8BtlModelFPCc(param_1,param_1 + 0x50c);
      strcpy(param_1 + 0x4f4,param_1 + 0x50c);
      *(undefined1 *)(param_1 + 0x500) = 0;
      *(undefined2 *)(param_1 + 0x4f0) = 1;
      *(undefined2 *)(param_1 + 0x4f2) = 0;
      *(undefined4 *)(param_1 + 0x518) = 0x3f800000;
      break;
    case 6:
      *(byte *)(param_1 + 0x4b0) = *(byte *)(param_1 + 0x4b0) & 0xfb | 4;
      setNextMotion__8BtlModelFPCc(param_1,param_1 + 0x50c);
      strcpy(param_1 + 0x4f4,param_1 + 0x50c);
      *(undefined1 *)(param_1 + 0x500) = 0;
      *(undefined2 *)(param_1 + 0x4f0) = 1;
      *(undefined2 *)(param_1 + 0x4f2) = 0;
      *(undefined4 *)(param_1 + 0x518) = 0x3f800000;
      break;
    case 7:
      *(byte *)(param_1 + 0x4b0) = *(byte *)(param_1 + 0x4b0) & 0xfb | 4;
      setNextMotion__8BtlModelFPCc(param_1,param_1 + 0x50c);
      strcpy(param_1 + 0x4f4,param_1 + 0x50c);
      *(undefined1 *)(param_1 + 0x500) = 0;
      *(undefined2 *)(param_1 + 0x4f0) = 1;
      *(undefined2 *)(param_1 + 0x4f2) = 0;
      *(undefined4 *)(param_1 + 0x518) = 0x3f800000;
      break;
    case 8:
      *(byte *)(param_1 + 0x4b0) = *(byte *)(param_1 + 0x4b0) & 0xfb | 4;
      uVar2 = setNextMotion__8BtlModelFPCc(param_1,param_1 + 0x50c);
      strcpy(param_1 + 0x4f4,param_1 + 0x50c,param_1,uVar2);
      *(undefined1 *)(param_1 + 0x500) = 0;
      *(undefined2 *)(param_1 + 0x4f0) = 1;
      *(undefined2 *)(param_1 + 0x4f2) = 0;
      *(undefined4 *)(param_1 + 0x518) = 0x3f800000;
      break;
    case 9:
      *(byte *)(param_1 + 0x4b0) = *(byte *)(param_1 + 0x4b0) & 0xfb | 4;
      setNextMotion__8BtlModelFPCc(param_1,param_1 + 0x50c);
      strcpy(param_1 + 0x4f4,param_1 + 0x50c);
      *(undefined1 *)(param_1 + 0x500) = 0;
      *(undefined2 *)(param_1 + 0x4f0) = 1;
      *(undefined2 *)(param_1 + 0x4f2) = 0;
      *(undefined4 *)(param_1 + 0x518) = 0x3f800000;
      break;
    case 10:
      if (*(short *)(param_1 + 0x4f2) == 1) {
        *(byte *)(param_1 + 0x4b0) = *(byte *)(param_1 + 0x4b0) & 0xfb | 4;
        setNextMotion__8BtlModelFPCc(param_1,param_1 + 0x50c);
        strcpy(param_1 + 0x4f4,param_1 + 0x50c);
        *(undefined1 *)(param_1 + 0x500) = 0;
        *(undefined2 *)(param_1 + 0x4f0) = 1;
        *(undefined2 *)(param_1 + 0x4f2) = 0;
        *(undefined4 *)(param_1 + 0x518) = 0x3f800000;
      }
      else if (*(short *)(param_1 + 0x4f2) == 0) {
        strcpy(param_1 + 0x4f4,param_1 + 0x500);
        *(undefined1 *)(param_1 + 0x500) = 0;
        setMotion__8BtlModelFPCc(param_1,param_1 + 0x4f4);
        *(undefined2 *)(param_1 + 0x4f2) = 1;
      }
      break;
    case 0xb:
      if (*(short *)(param_1 + 0x4f2) == 1) {
        *(byte *)(param_1 + 0x4b0) = *(byte *)(param_1 + 0x4b0) & 0xfb | 4;
        setNextMotion__8BtlModelFPCc(param_1,param_1 + 0x50c);
        strcpy(param_1 + 0x4f4,param_1 + 0x50c);
        *(undefined1 *)(param_1 + 0x500) = 0;
        *(undefined2 *)(param_1 + 0x4f0) = 1;
        *(undefined2 *)(param_1 + 0x4f2) = 0;
        *(undefined4 *)(param_1 + 0x518) = 0x3f800000;
      }
      else if (*(short *)(param_1 + 0x4f2) == 0) {
        strcpy(param_1 + 0x4f4,param_1 + 0x500);
        *(undefined1 *)(param_1 + 0x500) = 0;
        setMotion__8BtlModelFPCc(param_1,param_1 + 0x4f4);
        *(undefined2 *)(param_1 + 0x4f2) = 1;
      }
      break;
    case 0xc:
      if (*(short *)(param_1 + 0x4f2) == 1) {
        *(byte *)(param_1 + 0x4b0) = *(byte *)(param_1 + 0x4b0) & 0xfb | 4;
        setNextMotion__8BtlModelFPCc(param_1,param_1 + 0x50c);
        strcpy(param_1 + 0x4f4,param_1 + 0x50c);
        *(undefined1 *)(param_1 + 0x500) = 0;
        *(undefined2 *)(param_1 + 0x4f0) = 1;
        *(undefined2 *)(param_1 + 0x4f2) = 0;
        *(undefined4 *)(param_1 + 0x518) = 0x3f800000;
      }
      else if (*(short *)(param_1 + 0x4f2) == 0) {
        strcpy(param_1 + 0x4f4,param_1 + 0x500);
        *(undefined1 *)(param_1 + 0x500) = 0;
        setMotion__8BtlModelFPCc(param_1,param_1 + 0x4f4);
        *(undefined2 *)(param_1 + 0x4f2) = 1;
      }
      break;
    case 0xd:
      strcpy(param_1 + 0x4f4,param_1 + 0x500);
      strcpy(param_1 + 0x500,0x652d68);
      setNextMotion__8BtlModelFPCc(param_1,param_1 + 0x4f4);
      *(undefined2 *)(param_1 + 0x4f0) = 10;
      *(undefined2 *)(param_1 + 0x4f2) = 0;
      break;
    case 0xe:
      strcpy(param_1 + 0x4f4,param_1 + 0x500);
      strcpy(param_1 + 0x500,0x652d70);
      setNextMotion__8BtlModelFPCc(param_1,param_1 + 0x4f4);
      *(undefined2 *)(param_1 + 0x4f0) = 0xb;
      *(undefined2 *)(param_1 + 0x4f2) = 0;
      break;
    case 0xf:
      strcpy(param_1 + 0x4f4,param_1 + 0x500);
      strcpy(param_1 + 0x500,0x652d78);
      setNextMotion__8BtlModelFPCc(param_1,param_1 + 0x4f4);
      *(undefined2 *)(param_1 + 0x4f0) = 0xc;
      *(undefined2 *)(param_1 + 0x4f2) = 0;
      break;
    case 0x10:
      *(byte *)(param_1 + 0x4b0) = *(byte *)(param_1 + 0x4b0) & 0xfb | 4;
      setNextMotion__8BtlModelFPCc(param_1,param_1 + 0x50c);
      strcpy(param_1 + 0x4f4,param_1 + 0x50c);
      *(undefined1 *)(param_1 + 0x500) = 0;
      *(undefined2 *)(param_1 + 0x4f0) = 1;
      *(undefined2 *)(param_1 + 0x4f2) = 0;
      *(undefined4 *)(param_1 + 0x518) = 0x3f800000;
      break;
    case 0x11:
      *(byte *)(param_1 + 0x4b0) = *(byte *)(param_1 + 0x4b0) & 0xfb | 4;
      setNextMotion__8BtlModelFPCc(param_1,param_1 + 0x50c);
      strcpy(param_1 + 0x4f4,param_1 + 0x50c);
      *(undefined1 *)(param_1 + 0x500) = 0;
      *(undefined2 *)(param_1 + 0x4f0) = 1;
      *(undefined2 *)(param_1 + 0x4f2) = 0;
      *(undefined4 *)(param_1 + 0x518) = 0x3f800000;
      break;
    case 0x12:
      *(byte *)(param_1 + 0x4b0) = *(byte *)(param_1 + 0x4b0) & 0xfb | 4;
      setNextMotion__8BtlModelFPCc(param_1,param_1 + 0x50c);
      strcpy(param_1 + 0x4f4,param_1 + 0x50c);
      *(undefined1 *)(param_1 + 0x500) = 0;
      *(undefined2 *)(param_1 + 0x4f0) = 1;
      *(undefined2 *)(param_1 + 0x4f2) = 0;
      *(undefined4 *)(param_1 + 0x518) = 0x3f800000;
      break;
    case 0x13:
      strcpy(param_1 + 0x4f4,param_1 + 0x500);
      *(undefined1 *)(param_1 + 0x500) = 0;
      setMotion__8BtlModelFPCc(param_1,param_1 + 0x4f4);
      *(undefined2 *)(param_1 + 0x4f0) = 0x16;
      *(undefined2 *)(param_1 + 0x4f2) = 0;
      break;
    case 0x14:
      strcpy(param_1 + 0x4f4,param_1 + 0x500);
      *(undefined1 *)(param_1 + 0x500) = 0;
      setMotion__8BtlModelFPCc(param_1,param_1 + 0x4f4);
      *(undefined2 *)(param_1 + 0x4f0) = 0x17;
      *(undefined2 *)(param_1 + 0x4f2) = 0;
      break;
    case 0x15:
      strcpy(param_1 + 0x4f4,param_1 + 0x500);
      *(undefined1 *)(param_1 + 0x500) = 0;
      setMotion__8BtlModelFPCc(param_1,param_1 + 0x4f4);
      *(undefined2 *)(param_1 + 0x4f0) = 0x18;
      *(undefined2 *)(param_1 + 0x4f2) = 0;
      break;
    case 0x16:
      *(byte *)(param_1 + 0x4b0) = *(byte *)(param_1 + 0x4b0) & 0xfb | 4;
      setNextMotion__8BtlModelFPCc(param_1,param_1 + 0x50c);
      strcpy(param_1 + 0x4f4,param_1 + 0x50c);
      *(undefined1 *)(param_1 + 0x500) = 0;
      *(undefined2 *)(param_1 + 0x4f0) = 1;
      *(undefined2 *)(param_1 + 0x4f2) = 0;
      *(undefined4 *)(param_1 + 0x518) = 0x3f800000;
      break;
    case 0x17:
      *(byte *)(param_1 + 0x4b0) = *(byte *)(param_1 + 0x4b0) & 0xfb | 4;
      setNextMotion__8BtlModelFPCc(param_1,param_1 + 0x50c);
      strcpy(param_1 + 0x4f4,param_1 + 0x50c);
      *(undefined1 *)(param_1 + 0x500) = 0;
      *(undefined2 *)(param_1 + 0x4f0) = 1;
      *(undefined2 *)(param_1 + 0x4f2) = 0;
      *(undefined4 *)(param_1 + 0x518) = 0x3f800000;
      break;
    case 0x18:
      *(byte *)(param_1 + 0x4b0) = *(byte *)(param_1 + 0x4b0) & 0xfb | 4;
      setNextMotion__8BtlModelFPCc(param_1,param_1 + 0x50c);
      strcpy(param_1 + 0x4f4,param_1 + 0x50c);
      *(undefined1 *)(param_1 + 0x500) = 0;
      *(undefined2 *)(param_1 + 0x4f0) = 1;
      *(undefined2 *)(param_1 + 0x4f2) = 0;
      *(undefined4 *)(param_1 + 0x518) = 0x3f800000;
      break;
    case 0x1a:
      *(byte *)(param_1 + 0x4b0) = *(byte *)(param_1 + 0x4b0) & 0xfb | 4;
      strcpy(param_1 + 0x4f4,0x652d80);
      setNextMotion__8BtlModelFPCc(param_1,param_1 + 0x4f4);
      *(undefined1 *)(param_1 + 0x500) = 0;
      *(undefined2 *)(param_1 + 0x4f0) = 0x19;
      *(undefined2 *)(param_1 + 0x4f2) = 0;
      *(undefined4 *)(param_1 + 0x518) = 0x3f800000;
      break;
    case 0x1b:
      *(byte *)(param_1 + 0x4b0) = *(byte *)(param_1 + 0x4b0) & 0xfb | 4;
      strcpy(param_1 + 0x4f4,0x652d80);
      setNextMotion__8BtlModelFPCc(param_1,param_1 + 0x4f4);
      *(undefined1 *)(param_1 + 0x500) = 0;
      *(undefined2 *)(param_1 + 0x4f0) = 0x19;
      *(undefined2 *)(param_1 + 0x4f2) = 0;
      *(undefined4 *)(param_1 + 0x518) = 0x3f800000;
      break;
    case 0x1c:
      *(byte *)(param_1 + 0x4b0) = *(byte *)(param_1 + 0x4b0) & 0xfb | 4;
      setNextMotion__8BtlModelFPCc(param_1,param_1 + 0x50c);
      strcpy(param_1 + 0x4f4,param_1 + 0x50c);
      *(undefined1 *)(param_1 + 0x500) = 0;
      *(undefined2 *)(param_1 + 0x4f0) = 1;
      *(undefined2 *)(param_1 + 0x4f2) = 0;
      *(undefined4 *)(param_1 + 0x518) = 0x3f800000;
      break;
    case 0x1d:
      *(byte *)(param_1 + 0x4b0) = *(byte *)(param_1 + 0x4b0) & 0xfb | 4;
      setNextMotion__8BtlModelFPCc(param_1,param_1 + 0x50c);
      strcpy(param_1 + 0x4f4,param_1 + 0x50c);
      *(undefined1 *)(param_1 + 0x500) = 0;
      *(undefined2 *)(param_1 + 0x4f0) = 1;
      *(undefined2 *)(param_1 + 0x4f2) = 0;
      *(undefined4 *)(param_1 + 0x518) = 0x3f800000;
      break;
    case 0x1e:
      *(byte *)(param_1 + 0x4b0) = *(byte *)(param_1 + 0x4b0) & 0xfb | 4;
      setNextMotion__8BtlModelFPCc(param_1,param_1 + 0x50c);
      strcpy(param_1 + 0x4f4,param_1 + 0x50c);
      *(undefined1 *)(param_1 + 0x500) = 0;
      *(undefined2 *)(param_1 + 0x4f0) = 1;
      *(undefined2 *)(param_1 + 0x4f2) = 0;
      *(undefined4 *)(param_1 + 0x518) = 0x3f800000;
      break;
    case 0x22:
      *(byte *)(param_1 + 0x4b0) = *(byte *)(param_1 + 0x4b0) & 0xfb | 4;
      strcpy(param_1 + 0x4f4,0x652d88);
      setNextMotion__8BtlModelFPCc(param_1,param_1 + 0x4f4);
      *(undefined1 *)(param_1 + 0x500) = 0;
      *(undefined2 *)(param_1 + 0x4f0) = 0x24;
      *(undefined2 *)(param_1 + 0x4f2) = 0;
      *(undefined4 *)(param_1 + 0x518) = 0x3f800000;
      break;
    case 0x23:
      *(byte *)(param_1 + 0x4b0) = *(byte *)(param_1 + 0x4b0) & 0xfb | 4;
      strcpy(param_1 + 0x4f4,0x652d88);
      setNextMotion__8BtlModelFPCc(param_1,param_1 + 0x4f4);
      *(undefined1 *)(param_1 + 0x500) = 0;
      *(undefined2 *)(param_1 + 0x4f0) = 0x24;
      *(undefined2 *)(param_1 + 0x4f2) = 0;
      *(undefined4 *)(param_1 + 0x518) = 0x3f800000;
      break;
    case 0x25:
      *(byte *)(param_1 + 0x4b0) = *(byte *)(param_1 + 0x4b0) & 0xfb | 4;
      setNextMotion__8BtlModelFPCc(param_1,param_1 + 0x50c);
      strcpy(param_1 + 0x4f4,param_1 + 0x50c);
      *(undefined1 *)(param_1 + 0x500) = 0;
      *(undefined2 *)(param_1 + 0x4f0) = 1;
      *(undefined2 *)(param_1 + 0x4f2) = 0;
      *(undefined4 *)(param_1 + 0x518) = 0x3f800000;
      break;
    case 0x26:
      *(byte *)(param_1 + 0x4b0) = *(byte *)(param_1 + 0x4b0) & 0xfb | 4;
      setNextMotion__8BtlModelFPCc(param_1,param_1 + 0x50c);
      strcpy(param_1 + 0x4f4,param_1 + 0x50c);
      *(undefined1 *)(param_1 + 0x500) = 0;
      *(undefined2 *)(param_1 + 0x4f0) = 1;
      *(undefined2 *)(param_1 + 0x4f2) = 0;
      *(undefined4 *)(param_1 + 0x518) = 0x3f800000;
      break;
    case 0x27:
      *(byte *)(param_1 + 0x4b0) = *(byte *)(param_1 + 0x4b0) & 0xfb | 4;
      strcpy(param_1 + 0x4f4,0x652d90);
      setNextMotion__8BtlModelFPCc(param_1,param_1 + 0x4f4);
      *(undefined1 *)(param_1 + 0x500) = 0;
      *(undefined2 *)(param_1 + 0x4f0) = 0x28;
      *(undefined2 *)(param_1 + 0x4f2) = 0;
      *(undefined4 *)(param_1 + 0x518) = 0x3f800000;
      break;
    case 0x29:
      *(byte *)(param_1 + 0x4b0) = *(byte *)(param_1 + 0x4b0) & 0xfb | 4;
      setNextMotion__8BtlModelFPCc(param_1,param_1 + 0x50c);
      strcpy(param_1 + 0x4f4,param_1 + 0x50c);
      *(undefined1 *)(param_1 + 0x500) = 0;
      *(undefined2 *)(param_1 + 0x4f0) = 1;
      *(undefined2 *)(param_1 + 0x4f2) = 0;
      *(undefined4 *)(param_1 + 0x518) = 0x3f800000;
      break;
    case 0x2a:
      *(byte *)(param_1 + 0x4b0) = *(byte *)(param_1 + 0x4b0) & 0xfb | 4;
      strcpy(param_1 + 0x4f4,0x652d98);
      setNextMotion__8BtlModelFPCc(param_1,param_1 + 0x4f4);
      *(undefined1 *)(param_1 + 0x500) = 0;
      *(undefined2 *)(param_1 + 0x4f0) = 2;
      *(undefined2 *)(param_1 + 0x4f2) = 0;
      *(undefined4 *)(param_1 + 0x518) = 0x3f800000;
      break;
    case 0x2b:
      *(byte *)(param_1 + 0x4b0) = *(byte *)(param_1 + 0x4b0) & 0xf7 | 8;
      break;
    case 0x2c:
      *(byte *)(param_1 + 0x4b0) = *(byte *)(param_1 + 0x4b0) & 0xfb | 4;
      setNextMotion__8BtlModelFPCc(param_1,param_1 + 0x50c);
      strcpy(param_1 + 0x4f4,param_1 + 0x50c);
      *(undefined1 *)(param_1 + 0x500) = 0;
      *(undefined2 *)(param_1 + 0x4f0) = 1;
      *(undefined2 *)(param_1 + 0x4f2) = 0;
      *(undefined4 *)(param_1 + 0x518) = 0x3f800000;
      break;
    case 0x2d:
      *(byte *)(param_1 + 0x4b0) = *(byte *)(param_1 + 0x4b0) & 0xf7 | 8;
      break;
    case 0x2e:
      *(byte *)(param_1 + 0x4b0) = *(byte *)(param_1 + 0x4b0) & 0xfb | 4;
      setNextMotion__8BtlModelFPCc(param_1,param_1 + 0x50c);
      strcpy(param_1 + 0x4f4,param_1 + 0x50c);
      *(undefined1 *)(param_1 + 0x500) = 0;
      *(undefined2 *)(param_1 + 0x4f0) = 1;
      *(undefined2 *)(param_1 + 0x4f2) = 0;
      *(undefined4 *)(param_1 + 0x518) = 0x3f800000;
      break;
    case 0x2f:
    case 0x30:
    case 0x31:
    case 0x32:
    case 0x33:
    case 0x34:
    case 0x35:
    case 0x36:
    case 0x37:
    case 0x38:
    case 0x39:
    case 0x3a:
    case 0x3b:
    case 0x3c:
    case 0x3d:
    case 0x3e:
    case 0x3f:
    case 0x40:
    case 0x41:
    case 0x42:
    case 0x43:
    case 0x44:
    case 0x45:
    case 0x46:
    case 0x47:
    case 0x48:
    case 0x49:
    case 0x4a:
    case 0x4b:
    case 0x4c:
    case 0x4d:
    case 0x4e:
      lVar1 = SeachSequenceControl__15SequenceControlFPUc(*(undefined4 *)(param_1 + 0x34),param_1 + 0x4f4);
      if ((lVar1 == 0) || ((*(byte *)(*(int *)((int)lVar1 + 8) + 0x14) & 1) == 0)) {
        *(byte *)(param_1 + 0x4b0) = *(byte *)(param_1 + 0x4b0) & 0xfb | 4;
        setNextMotion__8BtlModelFPCc(param_1,param_1 + 0x50c);
        strcpy(param_1 + 0x4f4,param_1 + 0x50c);
        *(undefined1 *)(param_1 + 0x500) = 0;
        *(undefined2 *)(param_1 + 0x4f0) = 1;
        *(undefined2 *)(param_1 + 0x4f2) = 0;
        *(undefined4 *)(param_1 + 0x518) = 0x3f800000;
      }
    }
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054dc70  addTime__8BtlModelFf
 * C++: BtlModel::addTime(float)
 * size: 0x6f4 bytes
 * --------------------------------------------------------------------------- */
void addTime__8BtlModelFf(float param_1,undefined8 param_2)

{
  ulong uVar1;
  int iVar2;
  int iVar3;
  float fVar4;
  float fStack_10;
  float fStack_c;
  float fStack_8;
  
  iVar2 = (int)param_2;
  if ((*(byte *)(iVar2 + 0x4b0) & 1) != 0) {
    param_1 = param_1 * *(float *)(iVar2 + 0x51c);
    addTime__5ModelFf(param_1,param_2);
    if (*(int *)(iVar2 + 0x52c) != 0) {
      (**(code **)(*(int *)(*(int *)(iVar2 + 0x52c) + 0x10) + 0x2c))(param_1);
    }
    if (*(int *)(iVar2 + 0x530) != 0) {
      (**(code **)(*(int *)(*(int *)(iVar2 + 0x530) + 0x10) + 0x2c))(param_1);
    }
    if (*(int *)(iVar2 + 0x534) != 0) {
      (**(code **)(*(int *)(*(int *)(iVar2 + 0x534) + 0x10) + 0x2c))(param_1);
    }
    if (*(float *)(iVar2 + 0x4e8) < *(float *)(iVar2 + 0x4ec)) {
      *(float *)(iVar2 + 0x4ec) = *(float *)(iVar2 + 0x4ec) - *(float *)(iGpffff86b4 + 0x38) * 2.0;
      if (*(float *)(iVar2 + 0x4ec) < *(float *)(iVar2 + 0x4e8)) {
        *(undefined4 *)(iVar2 + 0x4ec) = *(undefined4 *)(iVar2 + 0x4e8);
      }
    }
    else if ((*(float *)(iVar2 + 0x4ec) < *(float *)(iVar2 + 0x4e8)) &&
            (*(float *)(iVar2 + 0x4ec) =
                  *(float *)(iVar2 + 0x4ec) + *(float *)(iGpffff86b4 + 0x38) * 2.0,
            *(float *)(iVar2 + 0x4e8) < *(float *)(iVar2 + 0x4ec))) {
      *(undefined4 *)(iVar2 + 0x4ec) = *(undefined4 *)(iVar2 + 0x4e8);
    }
    if ((((ulong)*(byte *)(iVar2 + 0x4b1) & 0xf) >> 2 == 1) &&
       (*(float *)(iVar2 + 0x548) = *(float *)(iVar2 + 0x548) + param_1 * 3.1415927,
       3.1415927 <= *(float *)(iVar2 + 0x548))) {
      *(float *)(iVar2 + 0x548) = *(float *)(iVar2 + 0x548) - 6.2831855;
    }
    iVar3 = (int)(*(float *)(iVar2 + 0x4e4) * *(float *)(iVar2 + 0x4ec) * 128.0);
    uVar1 = ((ulong)*(byte *)(iVar2 + 0x4b1) & 0xf) >> 2;
    if (uVar1 == 3) {
      SetBtlModelAlpha__8BtlModelFiii(param_2,iVar3,iVar3,1);
    }
    else if (uVar1 == 2) {
      SetBtlModelAlpha__8BtlModelFiii
                (param_2,iVar3,(int)(*(float *)(iVar2 + 0x548) * (float)iVar3),0x80);
    }
    else if (uVar1 == 1) {
      fVar4 = (float)sinf(*(undefined4 *)(iVar2 + 0x548));
      SetBtlModelAlpha__8BtlModelFiii(param_2,iVar3,(int)((float)iVar3 * (fVar4 / 2.0 + 0.5)),0x80);
    }
    else if (uVar1 == 0) {
      SetBtlModelAlpha__8BtlModelFiii(param_2,iVar3,0x80,0x80);
    }
    if ((long)((ulong)*(byte *)(iVar2 + 0x4b1) << 0x3b) < 0) {
      if ((long)((ulong)*(byte *)(iVar2 + 0x4b0) << 0x3e) < 0) {
        changeAlpha__15ModelEffManagerFP5Modelf((float)iVar3,param_2);
      }
      else {
        changeAlpha__15ModelEffManagerFP5Modelf(0,param_2);
      }
    }
    if (*(int *)(iVar2 + 0x5b0) != -1) {
      fStack_10 = 0.0;
      fStack_c = 0.0;
      fStack_8 = 0.0;
      if ((long)((ulong)*(byte *)(iVar2 + 0x4b1) << 0x38) < 0) {
        fStack_8 = *(float *)(iVar2 + 0x5d8);
        fStack_10 = (float)*(undefined8 *)(iVar2 + 0x5d0);
        fStack_c = (float)((ulong)*(undefined8 *)(iVar2 + 0x5d0) >> 0x20);
      }
      for (fStack_10 = fStack_10 - *(float *)(iVar2 + 0x5c0); fStack_10 < -3.1415927;
          fStack_10 = fStack_10 + 6.2831855) {
      }
      for (; 3.1415927 <= fStack_10; fStack_10 = fStack_10 - 6.2831855) {
      }
      if (param_1 * 6.2831855 < fStack_10) {
        fStack_10 = param_1 * 6.2831855;
      }
      if (fStack_10 < param_1 * -6.2831855) {
        fStack_10 = param_1 * -6.2831855;
      }
      *(float *)(iVar2 + 0x5c0) = *(float *)(iVar2 + 0x5c0) + fStack_10;
      for (fStack_c = fStack_c - *(float *)(iVar2 + 0x5c4); fStack_c < -3.1415927;
          fStack_c = fStack_c + 6.2831855) {
      }
      for (; 3.1415927 <= fStack_c; fStack_c = fStack_c - 6.2831855) {
      }
      if (param_1 * 6.2831855 < fStack_c) {
        fStack_c = param_1 * 6.2831855;
      }
      if (fStack_c < param_1 * -6.2831855) {
        fStack_c = param_1 * -6.2831855;
      }
      *(float *)(iVar2 + 0x5c4) = *(float *)(iVar2 + 0x5c4) + fStack_c;
      for (fStack_8 = fStack_8 - *(float *)(iVar2 + 0x5c8); fStack_8 < -3.1415927;
          fStack_8 = fStack_8 + 6.2831855) {
      }
      for (; 3.1415927 <= fStack_8; fStack_8 = fStack_8 - 6.2831855) {
      }
      if (param_1 * 6.2831855 < fStack_8) {
        fStack_8 = param_1 * 6.2831855;
      }
      if (fStack_8 < param_1 * -6.2831855) {
        fStack_8 = param_1 * -6.2831855;
      }
      *(float *)(iVar2 + 0x5c8) = *(float *)(iVar2 + 0x5c8) + fStack_8;
    }
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054e370  calcMatrix__8BtlModelFP6Matrix
 * C++: BtlModel::calcMatrix(Matrix *)
 * size: 0x188 bytes
 * --------------------------------------------------------------------------- */
void calcMatrix__8BtlModelFP6Matrix(undefined8 param_1,undefined8 param_2)

{
  int iVar1;
  int iVar2;
  undefined1 in_vf0 [16];
  undefined1 auVar3 [16];
  undefined1 auVar4 [16];
  undefined1 auVar5 [16];
  undefined1 auStack_40 [16];
  undefined1 auStack_30 [16];
  undefined1 auStack_20 [16];
  undefined1 auStack_10 [16];
  
  iVar2 = (int)param_1;
  if ((*(byte *)(iVar2 + 0x4b0) & 1) != 0) {
    calcMatrix__5ModelFP6Matrix(param_1,param_2);
    if (*(int *)(iVar2 + 0x52c) != 0) {
      (**(code **)(*(int *)(*(int *)(iVar2 + 0x52c) + 0x10) + 0x28))
                (*(int *)(iVar2 + 0x52c),param_2);
    }
    if (*(int *)(iVar2 + 0x530) != 0) {
      (**(code **)(*(int *)(*(int *)(iVar2 + 0x530) + 0x10) + 0x28))
                (*(int *)(iVar2 + 0x530),param_2);
    }
    if (*(int *)(iVar2 + 0x534) != 0) {
      (**(code **)(*(int *)(*(int *)(iVar2 + 0x534) + 0x10) + 0x28))
                (*(int *)(iVar2 + 0x534),param_2);
    }
    if (-1 < *(int *)(iVar2 + 0x5b0)) {
      auVar3 = _vmr32(in_vf0);
      auVar4 = _vmr32(auVar3);
      auVar5 = _vmr32(auVar4);
      _sqc2(in_vf0);
      _sqc2(auVar3);
      _sqc2(auVar4);
      _sqc2(auVar5);
      auVar3 = _vmr32(in_vf0);
      auVar4 = _vmr32(auVar3);
      auVar5 = _vmr32(auVar4);
      auStack_10 = _sqc2(in_vf0);
      auStack_20 = _sqc2(auVar3);
      auStack_30 = _sqc2(auVar4);
      auStack_40 = _sqc2(auVar5);
      sceVu0RotMatrix(auStack_40,auStack_40,iVar2 + 0x5c0);
      iVar1 = *(int *)(iVar2 + 0x30) + *(int *)(iVar2 + 0x5b0) * 0x1f0;
      *(undefined4 *)(iVar1 + 0x160) = auStack_40._0_4_;
      *(undefined4 *)(iVar1 + 0x164) = auStack_40._4_4_;
      *(undefined4 *)(iVar1 + 0x168) = auStack_40._8_4_;
      *(undefined4 *)(iVar1 + 0x16c) = auStack_40._12_4_;
      *(undefined4 *)(iVar1 + 0x170) = auStack_30._0_4_;
      *(undefined4 *)(iVar1 + 0x174) = auStack_30._4_4_;
      *(undefined4 *)(iVar1 + 0x178) = auStack_30._8_4_;
      *(undefined4 *)(iVar1 + 0x17c) = auStack_30._12_4_;
      *(undefined4 *)(iVar1 + 0x180) = auStack_20._0_4_;
      *(undefined4 *)(iVar1 + 0x184) = auStack_20._4_4_;
      *(undefined4 *)(iVar1 + 0x188) = auStack_20._8_4_;
      *(undefined4 *)(iVar1 + 0x18c) = auStack_20._12_4_;
      *(undefined4 *)(iVar1 + 400) = auStack_10._0_4_;
      *(undefined4 *)(iVar1 + 0x194) = auStack_10._4_4_;
      *(undefined4 *)(iVar1 + 0x198) = auStack_10._8_4_;
      *(undefined4 *)(iVar1 + 0x19c) = auStack_10._12_4_;
      myMatrixUpdate__5FrameFv(*(int *)(iVar2 + 0x30) + *(int *)(iVar2 + 0x5b0) * 0x1f0);
    }
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054e500  SetBtlMotion__8BtlModelFif
 * C++: BtlModel::SetBtlMotion(int, float)
 * size: 0x1a24 bytes
 * --------------------------------------------------------------------------- */
void SetBtlMotion__8BtlModelFif(undefined4 param_1,int param_2,undefined4 param_3)

{
  char unaff_s0_lo;
  
  *(byte *)(param_2 + 0x4b1) = *(byte *)(param_2 + 0x4b1) & 0xfe;
  switch(param_3) {
  case 1:
    strcpy(param_2 + 0x4f4,param_2 + 0x50c);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 2:
    strcpy(param_2 + 0x4f4,0x652d98);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 3:
    strcpy(param_2 + 0x4f4,0x652ee0);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 4:
    strcpy(param_2 + 0x4f4,0x652ee8);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 5:
    strcpy(param_2 + 0x4f4,0x652ef0);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 6:
    strcpy(param_2 + 0x4f4,0x652ef8);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 7:
    strcpy(param_2 + 0x4f4,0x652f00);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 8:
    strcpy(param_2 + 0x4f4,0x652f08);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 9:
    strcpy(param_2 + 0x4f4,0x652f10);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 10:
    strcpy(param_2 + 0x4f4,0x652f18);
    strcpy(param_2 + 0x500,0x652d68);
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0xb:
    strcpy(param_2 + 0x4f4,0x652f18);
    strcpy(param_2 + 0x500,0x652d70);
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0xc:
    strcpy(param_2 + 0x4f4,0x652f18);
    strcpy(param_2 + 0x500,0x652d78);
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0xd:
  case 0xe:
  case 0xf:
    strcpy(param_2 + 0x4f4,0x652f20);
    strcpy(param_2 + 0x500,0x652f18);
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x10:
    strcpy(param_2 + 0x4f4,0x652d68);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x11:
    strcpy(param_2 + 0x4f4,0x652d70);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x12:
    strcpy(param_2 + 0x4f4,0x652d78);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x13:
    strcpy(param_2 + 0x4f4,0x652f28);
    strcpy(param_2 + 0x500,0x652f30);
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x14:
    strcpy(param_2 + 0x4f4,0x652f28);
    strcpy(param_2 + 0x500,0x652f38);
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x15:
    strcpy(param_2 + 0x4f4,0x652f28);
    strcpy(param_2 + 0x500,0x652f40);
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x16:
    strcpy(param_2 + 0x4f4,0x652f30);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x17:
    strcpy(param_2 + 0x4f4,0x652f38);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x18:
    strcpy(param_2 + 0x4f4,0x652f40);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x19:
    strcpy(param_2 + 0x4f4,0x652d80);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x1a:
    strcpy(param_2 + 0x4f4,0x652f48);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x1b:
    strcpy(param_2 + 0x4f4,0x652f50);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x1c:
    strcpy(param_2 + 0x4f4,0x652f58);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x1d:
    strcpy(param_2 + 0x4f4,0x652f60);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x1e:
    strcpy(param_2 + 0x4f4,0x652f68);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x1f:
    strcpy(param_2 + 0x4f4,0x652f70);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x20:
    strcpy(param_2 + 0x4f4,0x652f68);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x21:
    strcpy(param_2 + 0x4f4,0x652f78);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x22:
    strcpy(param_2 + 0x4f4,0x652f80);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x23:
    strcpy(param_2 + 0x4f4,0x652f88);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x24:
    strcpy(param_2 + 0x4f4,0x652d88);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x25:
    strcpy(param_2 + 0x4f4,0x652f90);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x26:
    strcpy(param_2 + 0x4f4,0x652f98);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x27:
    strcpy(param_2 + 0x4f4,0x652fa0);
    strcpy(param_2 + 0x500,0x652d90);
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x28:
    strcpy(param_2 + 0x4f4,0x652d90);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x29:
    strcpy(param_2 + 0x4f4,0x652fa8);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x2a:
    strcpy(param_2 + 0x4f4,0x652fb0);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x2b:
    strcpy(param_2 + 0x4f4,0x652fb8);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x2c:
    strcpy(param_2 + 0x4f4,0x652fc0);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x2d:
    strcpy(param_2 + 0x4f4,0x652fc8);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x2e:
    strcpy(param_2 + 0x4f4,0x652fd0);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x2f:
    strcpy(param_2 + 0x4f4,0x652fd8);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x30:
    strcpy(param_2 + 0x4f4,0x652fe0);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x31:
    strcpy(param_2 + 0x4f4,0x652fe8);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x32:
    strcpy(param_2 + 0x4f4,0x652ff0);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x33:
    strcpy(param_2 + 0x4f4,0x652ff8);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x34:
    strcpy(param_2 + 0x4f4,0x653000);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x35:
    strcpy(param_2 + 0x4f4,0x653008);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x36:
    strcpy(param_2 + 0x4f4,0x653010);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x37:
    strcpy(param_2 + 0x4f4,0x653018);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x38:
    strcpy(param_2 + 0x4f4,0x653020);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x39:
    strcpy(param_2 + 0x4f4,0x653028);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x3a:
    strcpy(param_2 + 0x4f4,0x653030);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x3b:
    strcpy(param_2 + 0x4f4,0x653038);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x3c:
    strcpy(param_2 + 0x4f4,0x653040);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x3d:
    strcpy(param_2 + 0x4f4,0x653048);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x3e:
    strcpy(param_2 + 0x4f4,0x653050);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x3f:
    strcpy(param_2 + 0x4f4,0x653058);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x40:
    strcpy(param_2 + 0x4f4,0x653060);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x41:
    strcpy(param_2 + 0x4f4,0x653068);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x42:
    strcpy(param_2 + 0x4f4,0x653070);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x43:
    strcpy(param_2 + 0x4f4,0x653078);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x44:
    strcpy(param_2 + 0x4f4,0x653080);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x45:
    strcpy(param_2 + 0x4f4,0x653088);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x46:
    strcpy(param_2 + 0x4f4,0x653090);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x47:
    strcpy(param_2 + 0x4f4,0x653098);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x48:
    strcpy(param_2 + 0x4f4,0x6530a0);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x49:
    strcpy(param_2 + 0x4f4,0x6530a8);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x4a:
    strcpy(param_2 + 0x4f4,0x6530b0);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x4b:
    strcpy(param_2 + 0x4f4,0x6530b8);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x4c:
    strcpy(param_2 + 0x4f4,0x6530c0);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x4d:
    strcpy(param_2 + 0x4f4,0x6530c8);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x4e:
    strcpy(param_2 + 0x4f4,0x6530d0);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
  }
  if (unaff_s0_lo == '\x01') {
    *(byte *)(param_2 + 0x4b0) = *(byte *)(param_2 + 0x4b0) & 0xfb;
    *(byte *)(param_2 + 0x4b0) = *(byte *)(param_2 + 0x4b0) & 0xf7;
    *(short *)(param_2 + 0x4f0) = (short)param_3;
    *(undefined2 *)(param_2 + 0x4f2) = 0;
    *(undefined4 *)(param_2 + 0x518) = param_1;
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054ff30  SetNextBtlMotion__8BtlModelFif
 * C++: BtlModel::SetNextBtlMotion(int, float)
 * size: 0x1a24 bytes
 * --------------------------------------------------------------------------- */
void SetNextBtlMotion__8BtlModelFif(undefined4 param_1,int param_2,undefined4 param_3)

{
  undefined8 uVar1;
  char unaff_s0_lo;
  
  *(byte *)(param_2 + 0x4b1) = *(byte *)(param_2 + 0x4b1) & 0xfe;
  switch(param_3) {
  case 1:
    strcpy(param_2 + 0x4f4,param_2 + 0x50c);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 2:
    strcpy(param_2 + 0x4f4,0x652d98);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 3:
    strcpy(param_2 + 0x4f4,0x652ee0);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 4:
    strcpy(param_2 + 0x4f4,0x652ee8);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 5:
    strcpy(param_2 + 0x4f4,0x652ef0);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 6:
    strcpy(param_2 + 0x4f4,0x652ef8);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 7:
    strcpy(param_2 + 0x4f4,0x652f00);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 8:
    strcpy(param_2 + 0x4f4,0x652f08);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 9:
    strcpy(param_2 + 0x4f4,0x652f10);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 10:
    strcpy(param_2 + 0x4f4,0x652f18);
    strcpy(param_2 + 0x500,0x652d68);
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0xb:
    uVar1 = strcpy(param_2 + 0x4f4,0x652f18);
    strcpy(param_2 + 0x500,0x652d70,uVar1);
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0xc:
    strcpy(param_2 + 0x4f4,0x652f18);
    strcpy(param_2 + 0x500,0x652d78);
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0xd:
  case 0xe:
  case 0xf:
    strcpy(param_2 + 0x4f4,0x652f28);
    strcpy(param_2 + 0x500,0x652f18);
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x10:
    strcpy(param_2 + 0x4f4,0x652d68);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x11:
    strcpy(param_2 + 0x4f4,0x652d70);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x12:
    strcpy(param_2 + 0x4f4,0x652d78);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x13:
    strcpy(param_2 + 0x4f4,0x652f28);
    strcpy(param_2 + 0x500,0x652f30);
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x14:
    strcpy(param_2 + 0x4f4,0x652f28);
    strcpy(param_2 + 0x500,0x652f38);
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x15:
    strcpy(param_2 + 0x4f4,0x652f28);
    strcpy(param_2 + 0x500,0x652f40);
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x16:
    strcpy(param_2 + 0x4f4,0x652f30);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x17:
    strcpy(param_2 + 0x4f4,0x652f38);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x18:
    strcpy(param_2 + 0x4f4,0x652f40);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x19:
    strcpy(param_2 + 0x4f4,0x652d80);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x1a:
    strcpy(param_2 + 0x4f4,0x652f48);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x1b:
    strcpy(param_2 + 0x4f4,0x652f50);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x1c:
    strcpy(param_2 + 0x4f4,0x652f58);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x1d:
    strcpy(param_2 + 0x4f4,0x652f60);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x1e:
    strcpy(param_2 + 0x4f4,0x652f68);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x1f:
    strcpy(param_2 + 0x4f4,0x652f70);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x20:
    strcpy(param_2 + 0x4f4,0x652f68);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x21:
    strcpy(param_2 + 0x4f4,0x652f78);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x22:
    strcpy(param_2 + 0x4f4,0x652f80);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x23:
    strcpy(param_2 + 0x4f4,0x652f88);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x24:
    strcpy(param_2 + 0x4f4,0x652d88);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x25:
    strcpy(param_2 + 0x4f4,0x652f90);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x26:
    strcpy(param_2 + 0x4f4,0x652f98);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x27:
    strcpy(param_2 + 0x4f4,0x652fa0);
    strcpy(param_2 + 0x500,0x652d90);
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x28:
    strcpy(param_2 + 0x4f4,0x652d90);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x29:
    strcpy(param_2 + 0x4f4,0x652fa8);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x2a:
    strcpy(param_2 + 0x4f4,0x652fb0);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x2b:
    strcpy(param_2 + 0x4f4,0x652fb8);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x2c:
    strcpy(param_2 + 0x4f4,0x652fc0);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x2d:
    strcpy(param_2 + 0x4f4,0x652fc8);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x2e:
    strcpy(param_2 + 0x4f4,0x652fd0);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x2f:
    strcpy(param_2 + 0x4f4,0x652fd8);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x30:
    strcpy(param_2 + 0x4f4,0x652fe0);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x31:
    strcpy(param_2 + 0x4f4,0x652fe8);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x32:
    strcpy(param_2 + 0x4f4,0x652ff0);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x33:
    strcpy(param_2 + 0x4f4,0x652ff8);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x34:
    strcpy(param_2 + 0x4f4,0x653000);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x35:
    strcpy(param_2 + 0x4f4,0x653008);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x36:
    strcpy(param_2 + 0x4f4,0x653010);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x37:
    strcpy(param_2 + 0x4f4,0x653018);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x38:
    strcpy(param_2 + 0x4f4,0x653020);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x39:
    strcpy(param_2 + 0x4f4,0x653028);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x3a:
    strcpy(param_2 + 0x4f4,0x653030);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x3b:
    strcpy(param_2 + 0x4f4,0x653038);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x3c:
    strcpy(param_2 + 0x4f4,0x653040);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x3d:
    strcpy(param_2 + 0x4f4,0x653048);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x3e:
    strcpy(param_2 + 0x4f4,0x653050);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x3f:
    strcpy(param_2 + 0x4f4,0x653058);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x40:
    strcpy(param_2 + 0x4f4,0x653060);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x41:
    strcpy(param_2 + 0x4f4,0x653068);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x42:
    strcpy(param_2 + 0x4f4,0x653070);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x43:
    strcpy(param_2 + 0x4f4,0x653078);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x44:
    strcpy(param_2 + 0x4f4,0x653080);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x45:
    strcpy(param_2 + 0x4f4,0x653088);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x46:
    strcpy(param_2 + 0x4f4,0x653090);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x47:
    strcpy(param_2 + 0x4f4,0x653098);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x48:
    strcpy(param_2 + 0x4f4,0x6530a0);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x49:
    strcpy(param_2 + 0x4f4,0x6530a8);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x4a:
    strcpy(param_2 + 0x4f4,0x6530b0);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x4b:
    strcpy(param_2 + 0x4f4,0x6530b8);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x4c:
    strcpy(param_2 + 0x4f4,0x6530c0);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x4d:
    strcpy(param_2 + 0x4f4,0x6530c8);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
    break;
  case 0x4e:
    strcpy(param_2 + 0x4f4,0x6530d0);
    *(undefined1 *)(param_2 + 0x500) = 0;
    unaff_s0_lo = setNextMotion__8BtlModelFPCc(param_2,param_2 + 0x4f4);
  }
  if (unaff_s0_lo == '\x01') {
    *(byte *)(param_2 + 0x4b0) = *(byte *)(param_2 + 0x4b0) & 0xfb | 4;
    *(byte *)(param_2 + 0x4b0) = *(byte *)(param_2 + 0x4b0) & 0xf7;
    *(short *)(param_2 + 0x4f0) = (short)param_3;
    *(undefined2 *)(param_2 + 0x4f2) = 0;
    *(undefined4 *)(param_2 + 0x518) = param_1;
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00551960  setMotion__8BtlModelFPCc
 * C++: BtlModel::setMotion(char *)
 * size: 0x224 bytes
 * --------------------------------------------------------------------------- */
undefined1 setMotion__8BtlModelFPCc(int param_1,undefined4 param_2)

{
  undefined1 uVar1;
  long lVar2;
  
  if ((*(byte *)(param_1 + 0x4b0) & 1) == 0) {
    uVar1 = 0;
  }
  else {
    if (*(int *)(param_1 + 0x52c) != 0) {
      setMotion__5ModelFPCcf(0,*(undefined4 *)(param_1 + 0x52c),param_2);
    }
    if (*(int *)(param_1 + 0x530) != 0) {
      setMotion__5ModelFPCcf(0,*(undefined4 *)(param_1 + 0x530),param_2);
    }
    if (*(int *)(param_1 + 0x534) != 0) {
      setMotion__5ModelFPCcf(0,*(undefined4 *)(param_1 + 0x534),param_2);
    }
    uVar1 = setMotion__5ModelFPCcf(0,param_1,param_2);
    if ((*(int *)(param_1 + 0x5b0) < 0) ||
       (((((lVar2 = strcmp(param_1 + 0x50c,param_2), lVar2 != 0 &&
           (lVar2 = strcmp(0x652ee8,param_2), lVar2 != 0)) &&
          (lVar2 = strcmp(0x652d80,param_2), lVar2 != 0)) &&
         ((lVar2 = strcmp(0x652f48,param_2), lVar2 != 0 &&
          (lVar2 = strcmp(0x652f50,param_2), lVar2 != 0)))) &&
        ((lVar2 = strcmp(0x652f58,param_2), lVar2 != 0 &&
         ((lVar2 = strcmp(0x652f60,param_2), lVar2 != 0 &&
          (lVar2 = strcmp(0x652f98,param_2), lVar2 != 0)))))))) {
      *(byte *)(param_1 + 0x4b1) = *(byte *)(param_1 + 0x4b1) & 0x7f;
    }
    else {
      *(byte *)(param_1 + 0x4b1) = *(byte *)(param_1 + 0x4b1) & 0x7f | 0x80;
    }
  }
  return uVar1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00551b90  setNextMotion__8BtlModelFPCc
 * C++: BtlModel::setNextMotion(char *)
 * size: 0x224 bytes
 * --------------------------------------------------------------------------- */
undefined1 setNextMotion__8BtlModelFPCc(int param_1,undefined4 param_2)

{
  undefined1 uVar1;
  long lVar2;
  
  if ((*(byte *)(param_1 + 0x4b0) & 1) == 0) {
    uVar1 = 0;
  }
  else {
    if (*(int *)(param_1 + 0x52c) != 0) {
      setNextMotion__5ModelFPCcUs(*(undefined4 *)(param_1 + 0x52c),param_2,1);
    }
    if (*(int *)(param_1 + 0x530) != 0) {
      setNextMotion__5ModelFPCcUs(*(undefined4 *)(param_1 + 0x530),param_2,1);
    }
    if (*(int *)(param_1 + 0x534) != 0) {
      setNextMotion__5ModelFPCcUs(*(undefined4 *)(param_1 + 0x534),param_2,1);
    }
    uVar1 = setNextMotion__5ModelFPCcUs(param_1,param_2,1);
    if ((*(int *)(param_1 + 0x5b0) < 0) ||
       (((((lVar2 = strcmp(param_1 + 0x50c,param_2), lVar2 != 0 &&
           (lVar2 = strcmp(0x652ee8,param_2), lVar2 != 0)) &&
          (lVar2 = strcmp(0x652d80,param_2), lVar2 != 0)) &&
         ((lVar2 = strcmp(0x652f48,param_2), lVar2 != 0 &&
          (lVar2 = strcmp(0x652f50,param_2), lVar2 != 0)))) &&
        ((lVar2 = strcmp(0x652f58,param_2), lVar2 != 0 &&
         ((lVar2 = strcmp(0x652f60,param_2), lVar2 != 0 &&
          (lVar2 = strcmp(0x652f98,param_2), lVar2 != 0)))))))) {
      *(byte *)(param_1 + 0x4b1) = *(byte *)(param_1 + 0x4b1) & 0x7f;
    }
    else {
      *(byte *)(param_1 + 0x4b1) = *(byte *)(param_1 + 0x4b1) & 0x7f | 0x80;
    }
  }
  return uVar1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00551dc0  OTEntry__8BtlModelFii
 * C++: BtlModel::OTEntry(int, int)
 * size: 0x1e4 bytes
 * --------------------------------------------------------------------------- */
void OTEntry__8BtlModelFii(int param_1,undefined4 param_2,undefined4 param_3)

{
  *(undefined4 *)(param_1 + 0x5e0) = param_2;
  *(undefined4 *)(param_1 + 0x5e4) = param_3;
  if (-1 < (long)((ulong)*(byte *)(param_1 + 0x4b0) << 0x3e)) {
    AddDoubleOT__5WorldFiiP8VIF1Prim(0x42bf10,param_2,param_3,param_1);
    if ((*(int *)(param_1 + 0x52c) != 0) && ((*(byte *)(param_1 + 0x4b2) & 1) == 0)) {
      AddDoubleOT__5WorldFiiP8VIF1Prim(0x42bf10,param_2,param_3,*(undefined4 *)(param_1 + 0x52c));
    }
    if ((*(int *)(param_1 + 0x530) != 0) && (-1 < (long)((ulong)*(byte *)(param_1 + 0x4b2) << 0x3e))
       ) {
      AddDoubleOT__5WorldFiiP8VIF1Prim(0x42bf10,param_2,param_3,*(undefined4 *)(param_1 + 0x530));
    }
    if ((*(int *)(param_1 + 0x534) != 0) && (-1 < (long)((ulong)*(byte *)(param_1 + 0x4b2) << 0x3d))
       ) {
      AddDoubleOT__5WorldFiiP8VIF1Prim(0x42bf10,param_2,param_3,*(undefined4 *)(param_1 + 0x534));
    }
  }
  *(byte *)(param_1 + 0x4b0) = *(byte *)(param_1 + 0x4b0) & 0xfd | 2;
  if ((long)((ulong)*(byte *)(param_1 + 0x4b1) << 0x3b) < 0) {
    Dip__15ModelEffManagerFP5Modeli(param_1,*(undefined4 *)(param_1 + 0x578));
    changeAlpha__15ModelEffManagerFP5Modelf((float)(int)(*(float *)(param_1 + 0x4e4) * *(float *)(param_1 + 0x4ec) * 128.0),
                    param_1);
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00551fb0  OTRelease__8BtlModelFv
 * C++: BtlModel::OTRelease()
 * size: 0x1a8 bytes
 * --------------------------------------------------------------------------- */
void OTRelease__8BtlModelFv(int param_1)

{
  long lVar1;
  
  while (lVar1 = FindOT__5WorldFP8VIF1Prim(0x42bf10,param_1), lVar1 != 0) {
    ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,param_1);
  }
  if (*(int *)(param_1 + 0x52c) != 0) {
    while (lVar1 = FindOT__5WorldFP8VIF1Prim(0x42bf10,*(undefined4 *)(param_1 + 0x52c)), lVar1 != 0) {
      ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,*(undefined4 *)(param_1 + 0x52c));
    }
  }
  if (*(int *)(param_1 + 0x530) != 0) {
    while (lVar1 = FindOT__5WorldFP8VIF1Prim(0x42bf10,*(undefined4 *)(param_1 + 0x530)), lVar1 != 0) {
      ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,*(undefined4 *)(param_1 + 0x530));
    }
  }
  if (*(int *)(param_1 + 0x534) != 0) {
    while (lVar1 = FindOT__5WorldFP8VIF1Prim(0x42bf10,*(undefined4 *)(param_1 + 0x534)), lVar1 != 0) {
      ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,*(undefined4 *)(param_1 + 0x534));
    }
  }
  *(byte *)(param_1 + 0x4b0) = *(byte *)(param_1 + 0x4b0) & 0xfd;
  if ((long)((ulong)*(byte *)(param_1 + 0x4b1) << 0x3b) < 0) {
    changeAlpha__15ModelEffManagerFP5Modelf(0,param_1);
    Clr__15ModelEffManagerFP5Model(param_1);
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00552160  WeaponShow__8BtlModelFib
 * C++: BtlModel::WeaponShow(int, bool)
 * size: 0x884 bytes
 * --------------------------------------------------------------------------- */
void WeaponShow__8BtlModelFib(int param_1,int param_2,char param_3)

{
  undefined8 uVar1;
  long lVar2;
  
  if ((*(byte *)(param_1 + 0x4b0) & 1) != 0) {
    if (param_3 == '\x01') {
      if ((*(int *)(param_1 + 0x52c) != 0) &&
         ((((param_2 == 0 || (param_2 == 2)) || (param_2 == 4)) || (param_2 == 6)))) {
        if ((*(byte *)(param_1 + 0x4b2) & 1) != 0) {
          if ((long)((ulong)*(byte *)(param_1 + 0x4b0) << 0x3e) < 0) {
            AddDoubleOT__5WorldFiiP8VIF1Prim(0x42bf10,*(undefined4 *)(param_1 + 0x5e0),
                            *(undefined4 *)(param_1 + 0x5e4),*(undefined4 *)(param_1 + 0x52c));
          }
          if ((((long)((ulong)*(byte *)(param_1 + 0x4b0) << 0x3a) < 0) &&
              (*(int *)(param_1 + 0x52c) != 0)) && (*(int *)(param_1 + 0x53c) != 0)) {
            setDropShadow__13ShadowControlFP5Model(uGpffff83c4,*(undefined4 *)(param_1 + 0x52c));
          }
          uVar1 = searchFrame__5FrameFPCc(*(undefined4 *)(param_1 + 0x30),0x653360);
          chainModel__5FrameFP5Model(uVar1,*(undefined4 *)(param_1 + 0x52c));
        }
        *(byte *)(param_1 + 0x4b2) = *(byte *)(param_1 + 0x4b2) & 0xfe;
      }
      if ((*(int *)(param_1 + 0x530) != 0) &&
         (((param_2 == 1 || (param_2 == 2)) || ((param_2 == 5 || (param_2 == 6)))))) {
        if ((long)((ulong)*(byte *)(param_1 + 0x4b2) << 0x3e) < 0) {
          if ((long)((ulong)*(byte *)(param_1 + 0x4b0) << 0x3e) < 0) {
            AddDoubleOT__5WorldFiiP8VIF1Prim(0x42bf10,*(undefined4 *)(param_1 + 0x5e0),
                            *(undefined4 *)(param_1 + 0x5e4),*(undefined4 *)(param_1 + 0x530));
          }
          if ((((long)((ulong)*(byte *)(param_1 + 0x4b0) << 0x39) < 0) &&
              (*(int *)(param_1 + 0x530) != 0)) && (*(int *)(param_1 + 0x540) != 0)) {
            setDropShadow__13ShadowControlFP5Model(uGpffff83c4,*(undefined4 *)(param_1 + 0x530));
          }
          uVar1 = searchFrame__5FrameFPCc(*(undefined4 *)(param_1 + 0x30),0x653368);
          chainModel__5FrameFP5Model(uVar1,*(undefined4 *)(param_1 + 0x530));
        }
        *(byte *)(param_1 + 0x4b2) = *(byte *)(param_1 + 0x4b2) & 0xfd;
      }
      if ((*(int *)(param_1 + 0x534) != 0) &&
         (((param_2 == 3 || (param_2 == 4)) || ((param_2 == 5 || (param_2 == 6)))))) {
        if ((long)((ulong)*(byte *)(param_1 + 0x4b2) << 0x3d) < 0) {
          if ((long)((ulong)*(byte *)(param_1 + 0x4b0) << 0x3e) < 0) {
            AddDoubleOT__5WorldFiiP8VIF1Prim(0x42bf10,*(undefined4 *)(param_1 + 0x5e0),
                            *(undefined4 *)(param_1 + 0x5e4),*(undefined4 *)(param_1 + 0x534));
          }
          if ((((long)((ulong)*(byte *)(param_1 + 0x4b0) << 0x38) < 0) &&
              (*(int *)(param_1 + 0x534) != 0)) && (*(int *)(param_1 + 0x544) != 0)) {
            setDropShadow__13ShadowControlFP5Model(uGpffff83c4,*(undefined4 *)(param_1 + 0x534));
          }
          uVar1 = searchFrame__5FrameFPCc(*(undefined4 *)(param_1 + 0x30),0x653370);
          chainModel__5FrameFP5Model(uVar1,*(undefined4 *)(param_1 + 0x534));
        }
        *(byte *)(param_1 + 0x4b2) = *(byte *)(param_1 + 0x4b2) & 0xfb;
      }
    }
    else {
      if ((*(int *)(param_1 + 0x52c) != 0) &&
         ((((param_2 == 0 || (param_2 == 2)) || (param_2 == 4)) || (param_2 == 6)))) {
        if ((*(byte *)(param_1 + 0x4b2) & 1) == 0) {
          if ((long)((ulong)*(byte *)(param_1 + 0x4b0) << 0x3e) < 0) {
            while (lVar2 = FindOT__5WorldFP8VIF1Prim(0x42bf10,*(undefined4 *)(param_1 + 0x52c)), lVar2 != 0) {
              ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,*(undefined4 *)(param_1 + 0x52c));
            }
          }
          if ((((long)((ulong)*(byte *)(param_1 + 0x4b0) << 0x3a) < 0) &&
              (*(int *)(param_1 + 0x52c) != 0)) && (*(int *)(param_1 + 0x53c) != 0)) {
            releaseShadow__13ShadowControlFP5Model(uGpffff83c4,*(undefined4 *)(param_1 + 0x52c));
          }
          uVar1 = searchFrame__5FrameFPCc(*(undefined4 *)(param_1 + 0x30),0x653360);
          unChainModel__5FrameFv(uVar1);
        }
        *(byte *)(param_1 + 0x4b2) = *(byte *)(param_1 + 0x4b2) & 0xfe | 1;
      }
      if ((*(int *)(param_1 + 0x530) != 0) &&
         (((param_2 == 1 || (param_2 == 2)) || ((param_2 == 5 || (param_2 == 6)))))) {
        if ((long)((ulong)*(byte *)(param_1 + 0x4b2) << 0x3e) < 0) {
          if ((long)((ulong)*(byte *)(param_1 + 0x4b0) << 0x3e) < 0) {
            while (lVar2 = FindOT__5WorldFP8VIF1Prim(0x42bf10,*(undefined4 *)(param_1 + 0x530)), lVar2 != 0) {
              ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,*(undefined4 *)(param_1 + 0x530));
            }
          }
          if ((((long)((ulong)*(byte *)(param_1 + 0x4b0) << 0x39) < 0) &&
              (*(int *)(param_1 + 0x530) != 0)) && (*(int *)(param_1 + 0x540) != 0)) {
            releaseShadow__13ShadowControlFP5Model(uGpffff83c4,*(undefined4 *)(param_1 + 0x530));
          }
          uVar1 = searchFrame__5FrameFPCc(*(undefined4 *)(param_1 + 0x30),0x653368);
          unChainModel__5FrameFv(uVar1);
        }
        *(byte *)(param_1 + 0x4b2) = *(byte *)(param_1 + 0x4b2) & 0xfd | 2;
      }
      if ((*(int *)(param_1 + 0x534) != 0) &&
         (((param_2 == 3 || (param_2 == 4)) || ((param_2 == 5 || (param_2 == 6)))))) {
        if ((long)((ulong)*(byte *)(param_1 + 0x4b2) << 0x3d) < 0) {
          if ((long)((ulong)*(byte *)(param_1 + 0x4b0) << 0x3e) < 0) {
            while (lVar2 = FindOT__5WorldFP8VIF1Prim(0x42bf10,*(undefined4 *)(param_1 + 0x534)), lVar2 != 0) {
              ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,*(undefined4 *)(param_1 + 0x534));
            }
          }
          if ((((long)((ulong)*(byte *)(param_1 + 0x4b0) << 0x38) < 0) &&
              (*(int *)(param_1 + 0x534) != 0)) && (*(int *)(param_1 + 0x544) != 0)) {
            releaseShadow__13ShadowControlFP5Model(uGpffff83c4,*(undefined4 *)(param_1 + 0x534));
          }
          uVar1 = searchFrame__5FrameFPCc(*(undefined4 *)(param_1 + 0x30),0x653370);
          unChainModel__5FrameFv(uVar1);
        }
        *(byte *)(param_1 + 0x4b2) = *(byte *)(param_1 + 0x4b2) & 0xfb | 4;
      }
    }
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005529f0  SetPos__8BtlModelFP7FVector
 * C++: BtlModel::SetPos(FVector *)
 * size: 0x88 bytes
 * --------------------------------------------------------------------------- */
void SetPos__8BtlModelFP7FVector(int param_1,undefined8 param_2)

{
  undefined1 (*pauVar1) [16];
  undefined1 auVar2 [16];
  undefined1 auStack_10 [8];
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  __ct__7FVectorFPC7FVector(auStack_10,param_2);
  *(int *)(param_1 + 0x4c0) = auStack_10._0_4_;
  *(int *)(param_1 + 0x4c4) = auStack_10._4_4_;
  *(undefined4 *)(param_1 + 0x4c8) = uStack_8;
  *(undefined4 *)(param_1 + 0x4cc) = uStack_4;
  if ((*(byte *)(param_1 + 0x4b0) & 1) != 0) {
    pauVar1 = (undefined1 (*) [16])(*(int *)(param_1 + 0x30) + 400);
    _lqc2(*pauVar1);
    auVar2 = _lqc2(*(undefined1 (*) [16])param_2);
    auVar2 = _vmove(auVar2);
    auVar2 = _sqc2(auVar2);
    *pauVar1 = auVar2;
    myMatrixUpdate__5FrameFv(*(undefined4 *)(param_1 + 0x30));
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00552a80  SetAngle__8BtlModelFP7FVector
 * C++: BtlModel::SetAngle(FVector *)
 * size: 0x12c bytes
 * --------------------------------------------------------------------------- */
void SetAngle__8BtlModelFP7FVector(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined1 auStack_10 [8];
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  __ct__7FVectorFPC7FVector(auStack_10);
  *(int *)(param_1 + 0x4d0) = auStack_10._0_4_;
  *(int *)(param_1 + 0x4d4) = auStack_10._4_4_;
  *(undefined4 *)(param_1 + 0x4d8) = uStack_8;
  *(undefined4 *)(param_1 + 0x4dc) = uStack_4;
  if ((*(byte *)(param_1 + 0x4b0) & 1) != 0) {
    uVar2 = GetRad(*(undefined4 *)(param_1 + 0x4d8));
    uVar3 = GetRad(*(undefined4 *)(param_1 + 0x4d4));
    uStack_60 = GetRad(*(undefined4 *)(param_1 + 0x4d0));
    uStack_54 = 0x3f800000;
    uStack_5c = uVar3;
    uStack_58 = uVar2;
    __ct__6MatrixFRC7FVectorRC7FVector(&uStack_50,&uStack_60,param_1 + 0x4c0);
    iVar1 = *(int *)(param_1 + 0x30);
    *(undefined4 *)(iVar1 + 0x160) = uStack_50;
    *(undefined4 *)(iVar1 + 0x164) = uStack_4c;
    *(undefined4 *)(iVar1 + 0x168) = uStack_48;
    *(undefined4 *)(iVar1 + 0x16c) = uStack_44;
    *(undefined4 *)(iVar1 + 0x170) = uStack_40;
    *(undefined4 *)(iVar1 + 0x174) = uStack_3c;
    *(undefined4 *)(iVar1 + 0x178) = uStack_38;
    *(undefined4 *)(iVar1 + 0x17c) = uStack_34;
    *(undefined4 *)(iVar1 + 0x180) = uStack_30;
    *(undefined4 *)(iVar1 + 0x184) = uStack_2c;
    *(undefined4 *)(iVar1 + 0x188) = uStack_28;
    *(undefined4 *)(iVar1 + 0x18c) = uStack_24;
    *(undefined4 *)(iVar1 + 400) = uStack_20;
    *(undefined4 *)(iVar1 + 0x194) = uStack_1c;
    *(undefined4 *)(iVar1 + 0x198) = uStack_18;
    *(undefined4 *)(iVar1 + 0x19c) = uStack_14;
    *(float *)(*(int *)(param_1 + 0x30) + 0x160) =
         *(float *)(*(int *)(param_1 + 0x30) + 0x160) * *(float *)(param_1 + 0x4e0);
    *(float *)(*(int *)(param_1 + 0x30) + 0x174) =
         *(float *)(*(int *)(param_1 + 0x30) + 0x174) * *(float *)(param_1 + 0x4e0);
    *(float *)(*(int *)(param_1 + 0x30) + 0x188) =
         *(float *)(*(int *)(param_1 + 0x30) + 0x188) * *(float *)(param_1 + 0x4e0);
    myMatrixUpdate__5FrameFv(*(undefined4 *)(param_1 + 0x30));
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00552bb0  SetPosAngle__8BtlModelFP7FVectorP7FVector
 * C++: BtlModel::SetPosAngle(FVector *, FVector *)
 * size: 0x5c bytes
 * --------------------------------------------------------------------------- */
void SetPosAngle__8BtlModelFP7FVectorP7FVector
               (undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  int iVar1;
  undefined1 auStack_10 [8];
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  __ct__7FVectorFPC7FVector(auStack_10);
  iVar1 = (int)param_1;
  *(int *)(iVar1 + 0x4c0) = auStack_10._0_4_;
  *(int *)(iVar1 + 0x4c4) = auStack_10._4_4_;
  *(undefined4 *)(iVar1 + 0x4c8) = uStack_8;
  *(undefined4 *)(iVar1 + 0x4cc) = uStack_4;
  SetAngle__8BtlModelFP7FVector(param_1,param_3);
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00552c10  SetCameraAlpha__8BtlModelFfb
 * C++: BtlModel::SetCameraAlpha(float, bool)
 * size: 0x178 bytes
 * --------------------------------------------------------------------------- */
void SetCameraAlpha__8BtlModelFfb(undefined4 param_1,int param_2,char param_3)

{
  int iVar1;
  float fVar2;
  
  if ((*(byte *)(param_2 + 0x4b0) & 1) != 0) {
    *(undefined4 *)(param_2 + 0x4e8) = param_1;
    if (param_3 == '\x01') {
      *(undefined4 *)(param_2 + 0x4ec) = param_1;
      iVar1 = (int)(*(float *)(param_2 + 0x4e4) * *(float *)(param_2 + 0x4ec) * 128.0);
      if (((ulong)*(byte *)(param_2 + 0x4b1) & 0xf) >> 2 == 0) {
        SetBtlModelAlpha__8BtlModelFiii(param_2,iVar1,0x80,0x80);
      }
      else if (((ulong)*(byte *)(param_2 + 0x4b1) & 0xf) >> 2 == 3) {
        SetBtlModelAlpha__8BtlModelFiii(param_2,iVar1,iVar1,1);
      }
      else {
        fVar2 = (float)sinf(*(undefined4 *)(param_2 + 0x548));
        SetBtlModelAlpha__8BtlModelFiii
                  (param_2,iVar1,(int)((float)iVar1 * (fVar2 / 2.0 + 0.5)),0x80);
      }
    }
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00552d90  SetModelColor__8BtlModelFfff
 * C++: BtlModel::SetModelColor(float, float, float)
 * size: 0x2ac bytes
 * --------------------------------------------------------------------------- */
void SetModelColor__8BtlModelFfff(float param_1,float param_2,float param_3,int param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  if ((*(byte *)(param_4 + 0x4b0) & 1) != 0) {
    *(float *)(param_4 + 0x520) = param_1 * 128.0;
    *(float *)(param_4 + 0x524) = param_2 * 128.0;
    *(float *)(param_4 + 0x528) = param_3 * 128.0;
    *(float *)(param_4 + 0x280) = param_1 * 128.0;
    *(float *)(param_4 + 0x284) = param_2 * 128.0;
    *(float *)(param_4 + 0x288) = param_3 * 128.0;
    *(undefined4 *)(param_4 + 0x290) = *(undefined4 *)(param_4 + 0x280);
    *(undefined4 *)(param_4 + 0x294) = *(undefined4 *)(param_4 + 0x284);
    *(undefined4 *)(param_4 + 0x298) = *(undefined4 *)(param_4 + 0x288);
    *(undefined4 *)(param_4 + 0x29c) = *(undefined4 *)(param_4 + 0x28c);
    if (*(int *)(param_4 + 0x52c) != 0) {
      iVar1 = *(int *)(param_4 + 0x52c);
      uVar2 = *(undefined4 *)(param_4 + 0x284);
      uVar3 = *(undefined4 *)(param_4 + 0x288);
      *(undefined4 *)(iVar1 + 0x280) = *(undefined4 *)(param_4 + 0x280);
      *(undefined4 *)(iVar1 + 0x284) = uVar2;
      *(undefined4 *)(iVar1 + 0x288) = uVar3;
      *(undefined4 *)(iVar1 + 0x28c) = *(undefined4 *)(param_4 + 0x28c);
      iVar1 = *(int *)(param_4 + 0x52c);
      uVar2 = *(undefined4 *)(param_4 + 0x294);
      uVar3 = *(undefined4 *)(param_4 + 0x298);
      *(undefined4 *)(iVar1 + 0x290) = *(undefined4 *)(param_4 + 0x290);
      *(undefined4 *)(iVar1 + 0x294) = uVar2;
      *(undefined4 *)(iVar1 + 0x298) = uVar3;
      *(undefined4 *)(iVar1 + 0x29c) = *(undefined4 *)(param_4 + 0x29c);
    }
    if (*(int *)(param_4 + 0x530) != 0) {
      iVar1 = *(int *)(param_4 + 0x530);
      uVar2 = *(undefined4 *)(param_4 + 0x284);
      uVar3 = *(undefined4 *)(param_4 + 0x288);
      *(undefined4 *)(iVar1 + 0x280) = *(undefined4 *)(param_4 + 0x280);
      *(undefined4 *)(iVar1 + 0x284) = uVar2;
      *(undefined4 *)(iVar1 + 0x288) = uVar3;
      *(undefined4 *)(iVar1 + 0x28c) = *(undefined4 *)(param_4 + 0x28c);
      iVar1 = *(int *)(param_4 + 0x530);
      uVar2 = *(undefined4 *)(param_4 + 0x294);
      uVar3 = *(undefined4 *)(param_4 + 0x298);
      *(undefined4 *)(iVar1 + 0x290) = *(undefined4 *)(param_4 + 0x290);
      *(undefined4 *)(iVar1 + 0x294) = uVar2;
      *(undefined4 *)(iVar1 + 0x298) = uVar3;
      *(undefined4 *)(iVar1 + 0x29c) = *(undefined4 *)(param_4 + 0x29c);
    }
    if (*(int *)(param_4 + 0x534) != 0) {
      iVar1 = *(int *)(param_4 + 0x534);
      uVar2 = *(undefined4 *)(param_4 + 0x284);
      uVar3 = *(undefined4 *)(param_4 + 0x288);
      *(undefined4 *)(iVar1 + 0x280) = *(undefined4 *)(param_4 + 0x280);
      *(undefined4 *)(iVar1 + 0x284) = uVar2;
      *(undefined4 *)(iVar1 + 0x288) = uVar3;
      *(undefined4 *)(iVar1 + 0x28c) = *(undefined4 *)(param_4 + 0x28c);
      iVar1 = *(int *)(param_4 + 0x534);
      uVar2 = *(undefined4 *)(param_4 + 0x294);
      uVar3 = *(undefined4 *)(param_4 + 0x298);
      *(undefined4 *)(iVar1 + 0x290) = *(undefined4 *)(param_4 + 0x290);
      *(undefined4 *)(iVar1 + 0x294) = uVar2;
      *(undefined4 *)(iVar1 + 0x298) = uVar3;
      *(undefined4 *)(iVar1 + 0x29c) = *(undefined4 *)(param_4 + 0x29c);
    }
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00553040  CreateRightWeapon__8BtlModelFPUc
 * C++: BtlModel::CreateRightWeapon(uchar *)
 * size: 0x2e4 bytes
 * --------------------------------------------------------------------------- */
undefined4 CreateRightWeapon__8BtlModelFPUc(int param_1,undefined4 param_2)

{
  ushort uVar1;
  undefined4 uVar2;
  long lVar3;
  long lVar4;
  undefined8 uVar5;
  int iVar6;
  int iVar7;
  
  if (*(int *)(param_1 + 0x52c) == 0) {
    lVar3 = searchFrame__5FrameFPCc(*(undefined4 *)(param_1 + 0x30),0x653360);
    if (lVar3 == 0) {
      uVar2 = 0;
    }
    else {
      lVar4 = __nw__FUi(0x4b0);
      uVar2 = 0;
      if (lVar4 != 0) {
        uVar2 = __ct__5ModelFv(lVar4);
      }
      *(undefined4 *)(param_1 + 0x52c) = uVar2;
      (**(code **)(*(int *)(*(int *)(param_1 + 0x52c) + 0x10) + 0x24))
                (*(int *)(param_1 + 0x52c),param_2);
      chainModel__5FrameFP5Model(lVar3,*(undefined4 *)(param_1 + 0x52c));
      if ((long)((ulong)*(byte *)(param_1 + 0x4b0) << 0x3e) < 0) {
        AddDoubleOT__5WorldFiiP8VIF1Prim(0x42bf10,4,8,*(undefined4 *)(param_1 + 0x52c));
      }
      if ((*(int *)(param_1 + 0x564) != 0) && (*(int *)(param_1 + 0x564) != 0)) {
        __dla__FPv(*(int *)(param_1 + 0x564) + -0x10);
      }
      uVar1 = *(ushort *)(*(int *)(*(int *)(param_1 + 0x52c) + 100) + 4);
      uVar5 = __nwa__FUi((uint)uVar1 * 0x410 + 0x10);
      uVar2 = __construct_new_array(uVar5,0x51c130,0,0x410,uVar1);
      *(undefined4 *)(param_1 + 0x564) = uVar2;
      for (iVar6 = 0; iVar6 < (int)(uint)*(ushort *)(*(int *)(*(int *)(param_1 + 0x52c) + 100) + 4);
          iVar6 = iVar6 + 1) {
        *(undefined4 *)(*(int *)(param_1 + 0x564) + iVar6 * 0x410 + 0x400) =
             **(undefined4 **)(*(int *)(*(int *)(param_1 + 0x52c) + 0x4c) + iVar6 * 0x4c + 0xc);
        for (iVar7 = 0;
            iVar7 < *(int *)(*(int *)(*(int *)(*(int *)(param_1 + 0x52c) + 0x4c) + iVar6 * 0x4c +
                                     0xc) + 4); iVar7 = iVar7 + 1) {
          *(undefined1 *)(*(int *)(param_1 + 0x564) + iVar6 * 0x410 + iVar7 * 4 + 3) =
               *(undefined1 *)
                (*(int *)(*(int *)(param_1 + 0x564) + iVar6 * 0x410 + 0x400) + iVar7 * 4 + 3);
        }
      }
      uVar2 = 1;
    }
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00553330  CreateRightWeaponShadow__8BtlModelFPUc
 * C++: BtlModel::CreateRightWeaponShadow(uchar *)
 * size: 0x88 bytes
 * --------------------------------------------------------------------------- */
bool CreateRightWeaponShadow__8BtlModelFPUc(int param_1,undefined4 param_2)

{
  bool bVar1;
  
  bVar1 = *(int *)(param_1 + 0x52c) != 0;
  if (bVar1) {
    *(byte *)(param_1 + 0x4b0) = *(byte *)(param_1 + 0x4b0) & 0xdf;
    *(undefined4 *)(param_1 + 0x53c) = param_2;
    createLevelofDetale__5ModelFPUcUi(*(undefined4 *)(param_1 + 0x52c),param_2,2);
  }
  return bVar1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005533c0  CreateLeftWeapon__8BtlModelFPUc
 * C++: BtlModel::CreateLeftWeapon(uchar *)
 * size: 0x2e4 bytes
 * --------------------------------------------------------------------------- */
undefined4 CreateLeftWeapon__8BtlModelFPUc(int param_1,undefined4 param_2)

{
  ushort uVar1;
  undefined4 uVar2;
  long lVar3;
  long lVar4;
  undefined8 uVar5;
  int iVar6;
  int iVar7;
  
  if (*(int *)(param_1 + 0x530) == 0) {
    lVar3 = searchFrame__5FrameFPCc(*(undefined4 *)(param_1 + 0x30),0x653368);
    if (lVar3 == 0) {
      uVar2 = 0;
    }
    else {
      lVar4 = __nw__FUi(0x4b0);
      uVar2 = 0;
      if (lVar4 != 0) {
        uVar2 = __ct__5ModelFv(lVar4);
      }
      *(undefined4 *)(param_1 + 0x530) = uVar2;
      (**(code **)(*(int *)(*(int *)(param_1 + 0x530) + 0x10) + 0x24))
                (*(int *)(param_1 + 0x530),param_2);
      chainModel__5FrameFP5Model(lVar3,*(undefined4 *)(param_1 + 0x530));
      if ((long)((ulong)*(byte *)(param_1 + 0x4b0) << 0x3e) < 0) {
        AddDoubleOT__5WorldFiiP8VIF1Prim(0x42bf10,4,8,*(undefined4 *)(param_1 + 0x530));
      }
      if ((*(int *)(param_1 + 0x568) != 0) && (*(int *)(param_1 + 0x568) != 0)) {
        __dla__FPv(*(int *)(param_1 + 0x568) + -0x10);
      }
      uVar1 = *(ushort *)(*(int *)(*(int *)(param_1 + 0x530) + 100) + 4);
      uVar5 = __nwa__FUi((uint)uVar1 * 0x410 + 0x10);
      uVar2 = __construct_new_array(uVar5,0x51c130,0,0x410,uVar1);
      *(undefined4 *)(param_1 + 0x568) = uVar2;
      for (iVar6 = 0; iVar6 < (int)(uint)*(ushort *)(*(int *)(*(int *)(param_1 + 0x530) + 100) + 4);
          iVar6 = iVar6 + 1) {
        *(undefined4 *)(*(int *)(param_1 + 0x568) + iVar6 * 0x410 + 0x400) =
             **(undefined4 **)(*(int *)(*(int *)(param_1 + 0x530) + 0x4c) + iVar6 * 0x4c + 0xc);
        for (iVar7 = 0;
            iVar7 < *(int *)(*(int *)(*(int *)(*(int *)(param_1 + 0x530) + 0x4c) + iVar6 * 0x4c +
                                     0xc) + 4); iVar7 = iVar7 + 1) {
          *(undefined1 *)(*(int *)(param_1 + 0x568) + iVar6 * 0x410 + iVar7 * 4 + 3) =
               *(undefined1 *)
                (*(int *)(*(int *)(param_1 + 0x568) + iVar6 * 0x410 + 0x400) + iVar7 * 4 + 3);
        }
      }
      uVar2 = 1;
    }
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005536b0  CreateLeftWeaponShadow__8BtlModelFPUc
 * C++: BtlModel::CreateLeftWeaponShadow(uchar *)
 * size: 0x88 bytes
 * --------------------------------------------------------------------------- */
bool CreateLeftWeaponShadow__8BtlModelFPUc(int param_1,undefined4 param_2)

{
  bool bVar1;
  
  bVar1 = *(int *)(param_1 + 0x530) != 0;
  if (bVar1) {
    *(byte *)(param_1 + 0x4b0) = *(byte *)(param_1 + 0x4b0) & 0xbf;
    *(undefined4 *)(param_1 + 0x540) = param_2;
    createLevelofDetale__5ModelFPUcUi(*(undefined4 *)(param_1 + 0x530),param_2,2);
  }
  return bVar1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00553740  CreateCenterWeapon__8BtlModelFPUc
 * C++: BtlModel::CreateCenterWeapon(uchar *)
 * size: 0x2e4 bytes
 * --------------------------------------------------------------------------- */
undefined4 CreateCenterWeapon__8BtlModelFPUc(int param_1,undefined4 param_2)

{
  ushort uVar1;
  undefined4 uVar2;
  long lVar3;
  long lVar4;
  undefined8 uVar5;
  int iVar6;
  int iVar7;
  
  if (*(int *)(param_1 + 0x534) == 0) {
    lVar3 = searchFrame__5FrameFPCc(*(undefined4 *)(param_1 + 0x30),0x653370);
    if (lVar3 == 0) {
      uVar2 = 0;
    }
    else {
      lVar4 = __nw__FUi(0x4b0);
      uVar2 = 0;
      if (lVar4 != 0) {
        uVar2 = __ct__5ModelFv(lVar4);
      }
      *(undefined4 *)(param_1 + 0x534) = uVar2;
      (**(code **)(*(int *)(*(int *)(param_1 + 0x534) + 0x10) + 0x24))
                (*(int *)(param_1 + 0x534),param_2);
      chainModel__5FrameFP5Model(lVar3,*(undefined4 *)(param_1 + 0x534));
      if ((long)((ulong)*(byte *)(param_1 + 0x4b0) << 0x3e) < 0) {
        AddDoubleOT__5WorldFiiP8VIF1Prim(0x42bf10,4,8,*(undefined4 *)(param_1 + 0x534));
      }
      if ((*(int *)(param_1 + 0x56c) != 0) && (*(int *)(param_1 + 0x56c) != 0)) {
        __dla__FPv(*(int *)(param_1 + 0x56c) + -0x10);
      }
      uVar1 = *(ushort *)(*(int *)(*(int *)(param_1 + 0x534) + 100) + 4);
      uVar5 = __nwa__FUi((uint)uVar1 * 0x410 + 0x10);
      uVar2 = __construct_new_array(uVar5,0x51c130,0,0x410,uVar1);
      *(undefined4 *)(param_1 + 0x56c) = uVar2;
      for (iVar6 = 0; iVar6 < (int)(uint)*(ushort *)(*(int *)(*(int *)(param_1 + 0x534) + 100) + 4);
          iVar6 = iVar6 + 1) {
        *(undefined4 *)(*(int *)(param_1 + 0x56c) + iVar6 * 0x410 + 0x400) =
             **(undefined4 **)(*(int *)(*(int *)(param_1 + 0x534) + 0x4c) + iVar6 * 0x4c + 0xc);
        for (iVar7 = 0;
            iVar7 < *(int *)(*(int *)(*(int *)(*(int *)(param_1 + 0x534) + 0x4c) + iVar6 * 0x4c +
                                     0xc) + 4); iVar7 = iVar7 + 1) {
          *(undefined1 *)(*(int *)(param_1 + 0x56c) + iVar6 * 0x410 + iVar7 * 4 + 3) =
               *(undefined1 *)
                (*(int *)(*(int *)(param_1 + 0x56c) + iVar6 * 0x410 + 0x400) + iVar7 * 4 + 3);
        }
      }
      uVar2 = 1;
    }
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00553a30  CreateCenterWeaponShadow__8BtlModelFPUc
 * C++: BtlModel::CreateCenterWeaponShadow(uchar *)
 * size: 0x88 bytes
 * --------------------------------------------------------------------------- */
bool CreateCenterWeaponShadow__8BtlModelFPUc(int param_1,undefined4 param_2)

{
  bool bVar1;
  
  bVar1 = *(int *)(param_1 + 0x534) != 0;
  if (bVar1) {
    *(byte *)(param_1 + 0x4b0) = *(byte *)(param_1 + 0x4b0) & 0x7f;
    *(undefined4 *)(param_1 + 0x544) = param_2;
    createLevelofDetale__5ModelFPUcUi(*(undefined4 *)(param_1 + 0x534),param_2,2);
  }
  return bVar1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00553ac0  SetScale__8BtlModelFf
 * C++: BtlModel::SetScale(float)
 * size: 0x210 bytes
 * --------------------------------------------------------------------------- */
void SetScale__8BtlModelFf(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined4 uStack_80;
  undefined4 uStack_7c;
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  int iStack_20;
  undefined4 uStack_10;
  
  if ((*(byte *)(param_2 + 0x4b0) & 1) != 0) {
    *(undefined4 *)(param_2 + 0x4e0) = param_1;
    iStack_20 = param_2;
    uStack_10 = param_1;
    uStack_2c = GetRad(*(undefined4 *)(param_2 + 0x4d8));
    uStack_28 = GetRad(*(undefined4 *)(iStack_20 + 0x4d4));
    uStack_80 = GetRad(*(undefined4 *)(iStack_20 + 0x4d0));
    uStack_7c = uStack_28;
    uStack_78 = uStack_2c;
    uStack_74 = 0x3f800000;
    uStack_30 = uStack_80;
    uStack_24 = uStack_80;
    __ct__6MatrixFRC7FVectorRC7FVector(&uStack_70,&uStack_80,iStack_20 + 0x4c0);
    iVar1 = *(int *)(iStack_20 + 0x30);
    *(undefined4 *)(iVar1 + 0x160) = uStack_70;
    *(undefined4 *)(iVar1 + 0x164) = uStack_6c;
    *(undefined4 *)(iVar1 + 0x168) = uStack_68;
    *(undefined4 *)(iVar1 + 0x16c) = uStack_64;
    *(undefined4 *)(iVar1 + 0x170) = uStack_60;
    *(undefined4 *)(iVar1 + 0x174) = uStack_5c;
    *(undefined4 *)(iVar1 + 0x178) = uStack_58;
    *(undefined4 *)(iVar1 + 0x17c) = uStack_54;
    *(undefined4 *)(iVar1 + 0x180) = uStack_50;
    *(undefined4 *)(iVar1 + 0x184) = uStack_4c;
    *(undefined4 *)(iVar1 + 0x188) = uStack_48;
    *(undefined4 *)(iVar1 + 0x18c) = uStack_44;
    *(undefined4 *)(iVar1 + 400) = uStack_40;
    *(undefined4 *)(iVar1 + 0x194) = uStack_3c;
    *(undefined4 *)(iVar1 + 0x198) = uStack_38;
    *(undefined4 *)(iVar1 + 0x19c) = uStack_34;
    *(float *)(*(int *)(iStack_20 + 0x30) + 0x160) =
         *(float *)(*(int *)(iStack_20 + 0x30) + 0x160) * *(float *)(iStack_20 + 0x4e0);
    *(float *)(*(int *)(iStack_20 + 0x30) + 0x164) =
         *(float *)(*(int *)(iStack_20 + 0x30) + 0x164) * *(float *)(iStack_20 + 0x4e0);
    *(float *)(*(int *)(iStack_20 + 0x30) + 0x168) =
         *(float *)(*(int *)(iStack_20 + 0x30) + 0x168) * *(float *)(iStack_20 + 0x4e0);
    *(float *)(*(int *)(iStack_20 + 0x30) + 0x170) =
         *(float *)(*(int *)(iStack_20 + 0x30) + 0x170) * *(float *)(iStack_20 + 0x4e0);
    *(float *)(*(int *)(iStack_20 + 0x30) + 0x174) =
         *(float *)(*(int *)(iStack_20 + 0x30) + 0x174) * *(float *)(iStack_20 + 0x4e0);
    *(float *)(*(int *)(iStack_20 + 0x30) + 0x178) =
         *(float *)(*(int *)(iStack_20 + 0x30) + 0x178) * *(float *)(iStack_20 + 0x4e0);
    *(float *)(*(int *)(iStack_20 + 0x30) + 0x180) =
         *(float *)(*(int *)(iStack_20 + 0x30) + 0x180) * *(float *)(iStack_20 + 0x4e0);
    *(float *)(*(int *)(iStack_20 + 0x30) + 0x184) =
         *(float *)(*(int *)(iStack_20 + 0x30) + 0x184) * *(float *)(iStack_20 + 0x4e0);
    *(float *)(*(int *)(iStack_20 + 0x30) + 0x188) =
         *(float *)(*(int *)(iStack_20 + 0x30) + 0x188) * *(float *)(iStack_20 + 0x4e0);
    myMatrixUpdate__5FrameFv(*(undefined4 *)(iStack_20 + 0x30));
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00553cd0  ShadowOn__8BtlModelFv
 * C++: BtlModel::ShadowOn()
 * size: 0x1d8 bytes
 * --------------------------------------------------------------------------- */
void ShadowOn__8BtlModelFv(int param_1)

{
  if ((-1 < (long)((ulong)*(byte *)(param_1 + 0x4b0) << 0x3b)) && (*(int *)(param_1 + 0x538) != 0))
  {
    setDropShadow__13ShadowControlFP5Model(uGpffff83c4,param_1);
  }
  if (((-1 < (long)((ulong)*(byte *)(param_1 + 0x4b0) << 0x3a)) && (*(int *)(param_1 + 0x52c) != 0))
     && (*(int *)(param_1 + 0x53c) != 0)) {
    setDropShadow__13ShadowControlFP5Model(uGpffff83c4,*(undefined4 *)(param_1 + 0x52c));
  }
  if (((-1 < (long)((ulong)*(byte *)(param_1 + 0x4b0) << 0x39)) && (*(int *)(param_1 + 0x530) != 0))
     && (*(int *)(param_1 + 0x540) != 0)) {
    setDropShadow__13ShadowControlFP5Model(uGpffff83c4,*(undefined4 *)(param_1 + 0x530));
  }
  if (((-1 < (long)((ulong)*(byte *)(param_1 + 0x4b0) << 0x38)) && (*(int *)(param_1 + 0x534) != 0))
     && (*(int *)(param_1 + 0x544) != 0)) {
    setDropShadow__13ShadowControlFP5Model(uGpffff83c4,*(undefined4 *)(param_1 + 0x534));
  }
  *(byte *)(param_1 + 0x4b0) = *(byte *)(param_1 + 0x4b0) & 0xef | 0x10;
  *(byte *)(param_1 + 0x4b0) = *(byte *)(param_1 + 0x4b0) & 0xdf | 0x20;
  *(byte *)(param_1 + 0x4b0) = *(byte *)(param_1 + 0x4b0) & 0xbf | 0x40;
  *(byte *)(param_1 + 0x4b0) = *(byte *)(param_1 + 0x4b0) & 0x7f | 0x80;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00553eb0  ShadowOff__8BtlModelFv
 * C++: BtlModel::ShadowOff()
 * size: 0x1c8 bytes
 * --------------------------------------------------------------------------- */
void ShadowOff__8BtlModelFv(int param_1)

{
  if (((long)((ulong)*(byte *)(param_1 + 0x4b0) << 0x3b) < 0) && (*(int *)(param_1 + 0x538) != 0)) {
    releaseShadow__13ShadowControlFP5Model(uGpffff83c4,param_1);
  }
  if ((((long)((ulong)*(byte *)(param_1 + 0x4b0) << 0x3a) < 0) && (*(int *)(param_1 + 0x52c) != 0))
     && (*(int *)(param_1 + 0x53c) != 0)) {
    releaseShadow__13ShadowControlFP5Model(uGpffff83c4,*(undefined4 *)(param_1 + 0x52c));
  }
  if ((((long)((ulong)*(byte *)(param_1 + 0x4b0) << 0x39) < 0) && (*(int *)(param_1 + 0x530) != 0))
     && (*(int *)(param_1 + 0x540) != 0)) {
    releaseShadow__13ShadowControlFP5Model(uGpffff83c4,*(undefined4 *)(param_1 + 0x530));
  }
  if ((((long)((ulong)*(byte *)(param_1 + 0x4b0) << 0x38) < 0) && (*(int *)(param_1 + 0x534) != 0))
     && (*(int *)(param_1 + 0x544) != 0)) {
    releaseShadow__13ShadowControlFP5Model(uGpffff83c4,*(undefined4 *)(param_1 + 0x534));
  }
  *(byte *)(param_1 + 0x4b0) = *(byte *)(param_1 + 0x4b0) & 0xef;
  *(byte *)(param_1 + 0x4b0) = *(byte *)(param_1 + 0x4b0) & 0xdf;
  *(byte *)(param_1 + 0x4b0) = *(byte *)(param_1 + 0x4b0) & 0xbf;
  *(byte *)(param_1 + 0x4b0) = *(byte *)(param_1 + 0x4b0) & 0x7f;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00554080  searchBBoxIndex__8BtlModelFPci
 * C++: BtlModel::searchBBoxIndex(char *, int)
 * size: 0x1e8 bytes
 * --------------------------------------------------------------------------- */
int searchBBoxIndex__8BtlModelFPci(int param_1,char *param_2,int param_3)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  long lVar4;
  int iStack_34;
  int iStack_30;
  char *pcStack_20;
  int iStack_10;
  
  if ((*(byte *)(param_1 + 0x4b0) & 1) == 0) {
    iStack_34 = -1;
  }
  else {
    uVar1 = *(ushort *)(*(int *)(param_1 + 0x58) + 4);
    iVar2 = *(int *)(*(int *)(param_1 + 0x60) + 4);
    iVar3 = param_3;
    iStack_30 = param_1;
    pcStack_20 = param_2;
    iStack_10 = param_3;
    if ((*param_2 == '_') && (iVar3 = param_3, param_2[1] == '_')) {
      lVar4 = sscanf(param_2 + 2,0x653378,&iStack_34);
      if ((lVar4 == -1) || (lVar4 == 0)) {
        iStack_34 = -1;
      }
    }
    else {
      while (iStack_34 = iVar3, iStack_34 < iVar2) {
        if ((*(byte *)(*(int *)(iStack_30 + 0xe4) + iStack_34 * 0x110) < uVar1) &&
           (lVar4 = strcmp(*(undefined4 *)
                                     (*(int *)(iStack_30 + 0x30) +
                                      (uint)*(byte *)(*(int *)(iStack_30 + 0xe4) + iStack_34 * 0x110
                                                     ) * 0x1f0 + 0x80),pcStack_20), lVar4 == 0)) {
          return iStack_34;
        }
        iVar3 = iStack_34 + 1;
      }
      iStack_34 = -1;
    }
  }
  return iStack_34;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00554270  searchRWBBoxIndex__8BtlModelFPci
 * C++: BtlModel::searchRWBBoxIndex(char *, int)
 * size: 0x1f8 bytes
 * --------------------------------------------------------------------------- */
int searchRWBBoxIndex__8BtlModelFPci(int param_1,char *param_2,int param_3)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  long lVar4;
  int iStack_34;
  int iStack_30;
  char *pcStack_20;
  int iStack_10;
  
  if (*(int *)(param_1 + 0x52c) == 0) {
    iStack_34 = -1;
  }
  else {
    uVar1 = *(ushort *)(*(int *)(*(int *)(param_1 + 0x52c) + 0x58) + 4);
    iVar2 = *(int *)(*(int *)(*(int *)(param_1 + 0x52c) + 0x60) + 4);
    iVar3 = param_3;
    iStack_30 = param_1;
    pcStack_20 = param_2;
    iStack_10 = param_3;
    if ((*param_2 == '_') && (iVar3 = param_3, param_2[1] == '_')) {
      lVar4 = sscanf(param_2 + 2,0x653378,&iStack_34);
      if ((lVar4 == -1) || (lVar4 == 0)) {
        iStack_34 = -1;
      }
    }
    else {
      while (iStack_34 = iVar3, iStack_34 < iVar2) {
        if ((*(byte *)(*(int *)(*(int *)(iStack_30 + 0x52c) + 0xe4) + iStack_34 * 0x110) < uVar1) &&
           (lVar4 = strcmp(*(undefined4 *)
                                     (*(int *)(*(int *)(iStack_30 + 0x52c) + 0x30) +
                                      (uint)*(byte *)(*(int *)(*(int *)(iStack_30 + 0x52c) + 0xe4) +
                                                     iStack_34 * 0x110) * 0x1f0 + 0x80),pcStack_20),
           lVar4 == 0)) {
          return iStack_34;
        }
        iVar3 = iStack_34 + 1;
      }
      iStack_34 = -1;
    }
  }
  return iStack_34;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00554470  searchLWBBoxIndex__8BtlModelFPci
 * C++: BtlModel::searchLWBBoxIndex(char *, int)
 * size: 0x1f8 bytes
 * --------------------------------------------------------------------------- */
int searchLWBBoxIndex__8BtlModelFPci(int param_1,char *param_2,int param_3)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  long lVar4;
  int iStack_34;
  int iStack_30;
  char *pcStack_20;
  int iStack_10;
  
  if (*(int *)(param_1 + 0x530) == 0) {
    iStack_34 = -1;
  }
  else {
    uVar1 = *(ushort *)(*(int *)(*(int *)(param_1 + 0x530) + 0x58) + 4);
    iVar2 = *(int *)(*(int *)(*(int *)(param_1 + 0x530) + 0x60) + 4);
    iVar3 = param_3;
    iStack_30 = param_1;
    pcStack_20 = param_2;
    iStack_10 = param_3;
    if ((*param_2 == '_') && (iVar3 = param_3, param_2[1] == '_')) {
      lVar4 = sscanf(param_2 + 2,0x653378,&iStack_34);
      if ((lVar4 == -1) || (lVar4 == 0)) {
        iStack_34 = -1;
      }
    }
    else {
      while (iStack_34 = iVar3, iStack_34 < iVar2) {
        if ((*(byte *)(*(int *)(*(int *)(iStack_30 + 0x530) + 0xe4) + iStack_34 * 0x110) < uVar1) &&
           (lVar4 = strcmp(*(undefined4 *)
                                     (*(int *)(*(int *)(iStack_30 + 0x530) + 0x30) +
                                      (uint)*(byte *)(*(int *)(*(int *)(iStack_30 + 0x530) + 0xe4) +
                                                     iStack_34 * 0x110) * 0x1f0 + 0x80),pcStack_20),
           lVar4 == 0)) {
          return iStack_34;
        }
        iVar3 = iStack_34 + 1;
      }
      iStack_34 = -1;
    }
  }
  return iStack_34;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00554670  ClutCtrl__8BtlModelFffff
 * C++: BtlModel::ClutCtrl(float, float, float, float)
 * size: 0x4aec bytes
 * --------------------------------------------------------------------------- */
/* WARNING: Removing unreachable block (ram,0x00558fbc) */
/* WARNING: Removing unreachable block (ram,0x00558cf8) */
/* WARNING: Removing unreachable block (ram,0x00558b50) */
/* WARNING: Removing unreachable block (ram,0x0055888c) */
/* WARNING: Removing unreachable block (ram,0x005585d0) */
/* WARNING: Removing unreachable block (ram,0x00558428) */
/* WARNING: Removing unreachable block (ram,0x005576dc) */
/* WARNING: Removing unreachable block (ram,0x00557274) */
/* WARNING: Removing unreachable block (ram,0x00557f28) */
/* WARNING: Removing unreachable block (ram,0x00557b20) */
/* WARNING: Removing unreachable block (ram,0x005563e4) */
/* WARNING: Removing unreachable block (ram,0x005560dc) */
/* WARNING: Removing unreachable block (ram,0x00556960) */
/* WARNING: Removing unreachable block (ram,0x005566b8) */
/* WARNING: Removing unreachable block (ram,0x0055539c) */
/* WARNING: Removing unreachable block (ram,0x00555014) */
/* WARNING: Removing unreachable block (ram,0x00555a18) */
/* WARNING: Removing unreachable block (ram,0x005556f0) */
/* WARNING: Removing unreachable block (ram,0x00555880) */
/* WARNING: Removing unreachable block (ram,0x00555bb0) */
/* WARNING: Removing unreachable block (ram,0x005551d4) */
/* WARNING: Removing unreachable block (ram,0x00555564) */
/* WARNING: Removing unreachable block (ram,0x00556808) */
/* WARNING: Removing unreachable block (ram,0x00556ab8) */
/* WARNING: Removing unreachable block (ram,0x0055625c) */
/* WARNING: Removing unreachable block (ram,0x0055656c) */
/* WARNING: Removing unreachable block (ram,0x00557d18) */
/* WARNING: Removing unreachable block (ram,0x00558138) */
/* WARNING: Removing unreachable block (ram,0x0055749c) */
/* WARNING: Removing unreachable block (ram,0x0055791c) */
/* WARNING: Removing unreachable block (ram,0x005584fc) */
/* WARNING: Removing unreachable block (ram,0x005587b8) */
/* WARNING: Removing unreachable block (ram,0x00558960) */
/* WARNING: Removing unreachable block (ram,0x00558c24) */
/* WARNING: Removing unreachable block (ram,0x00558ee8) */
/* WARNING: Removing unreachable block (ram,0x00559090) */

void ClutCtrl__8BtlModelFffff
               (undefined4 param_1,undefined4 param_2,undefined4 param_3,float param_4,int param_5)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  byte bVar4;
  byte *pbVar5;
  int iVar6;
  undefined1 uVar7;
  float fVar8;
  
  *(undefined4 *)(param_5 + 0x550) = param_1;
  *(undefined4 *)(param_5 + 0x554) = param_2;
  *(undefined4 *)(param_5 + 0x558) = param_3;
  *(undefined4 *)(param_5 + 0x55c) = 0x3f800000;
  if ((((*(float *)(param_5 + 0x550) == 0.0) && (*(float *)(param_5 + 0x554) == 0.0)) &&
      (*(float *)(param_5 + 0x558) == 0.0)) && (param_4 == 0.0)) {
    if (*(int *)(param_5 + 0x560) != 0) {
      for (iVar3 = 0; iVar3 < (int)(uint)*(ushort *)(*(int *)(param_5 + 100) + 4); iVar3 = iVar3 + 1
          ) {
        **(undefined4 **)(*(int *)(param_5 + 0x4c) + iVar3 * 0x4c + 0xc) =
             *(undefined4 *)(*(int *)(param_5 + 0x560) + iVar3 * 0x410 + 0x400);
        *(undefined4 *)(*(int *)(*(int *)(param_5 + 0x4c) + iVar3 * 0x4c) + 0xf4) =
             *(undefined4 *)(*(int *)(param_5 + 0x560) + iVar3 * 0x410 + 0x400);
        *(undefined4 *)(*(int *)(*(int *)(param_5 + 0x4c) + iVar3 * 0x4c + 4) + 0xf4) =
             *(undefined4 *)(*(int *)(param_5 + 0x560) + iVar3 * 0x410 + 0x400);
      }
    }
    if (*(int *)(param_5 + 0x568) != 0) {
      for (iVar3 = 0; iVar3 < (int)(uint)*(ushort *)(*(int *)(*(int *)(param_5 + 0x530) + 100) + 4);
          iVar3 = iVar3 + 1) {
        **(undefined4 **)(*(int *)(*(int *)(param_5 + 0x530) + 0x4c) + iVar3 * 0x4c + 0xc) =
             *(undefined4 *)(*(int *)(param_5 + 0x568) + iVar3 * 0x410 + 0x400);
        *(undefined4 *)(*(int *)(*(int *)(*(int *)(param_5 + 0x530) + 0x4c) + iVar3 * 0x4c) + 0xf4)
             = *(undefined4 *)(*(int *)(param_5 + 0x568) + iVar3 * 0x410 + 0x400);
        *(undefined4 *)
         (*(int *)(*(int *)(*(int *)(param_5 + 0x530) + 0x4c) + iVar3 * 0x4c + 4) + 0xf4) =
             *(undefined4 *)(*(int *)(param_5 + 0x568) + iVar3 * 0x410 + 0x400);
      }
    }
    if (*(int *)(param_5 + 0x564) != 0) {
      for (iVar3 = 0; iVar3 < (int)(uint)*(ushort *)(*(int *)(*(int *)(param_5 + 0x52c) + 100) + 4);
          iVar3 = iVar3 + 1) {
        **(undefined4 **)(*(int *)(*(int *)(param_5 + 0x52c) + 0x4c) + iVar3 * 0x4c + 0xc) =
             *(undefined4 *)(*(int *)(param_5 + 0x564) + iVar3 * 0x410 + 0x400);
        *(undefined4 *)(*(int *)(*(int *)(*(int *)(param_5 + 0x52c) + 0x4c) + iVar3 * 0x4c) + 0xf4)
             = *(undefined4 *)(*(int *)(param_5 + 0x564) + iVar3 * 0x410 + 0x400);
        *(undefined4 *)
         (*(int *)(*(int *)(*(int *)(param_5 + 0x52c) + 0x4c) + iVar3 * 0x4c + 4) + 0xf4) =
             *(undefined4 *)(*(int *)(param_5 + 0x564) + iVar3 * 0x410 + 0x400);
      }
    }
    if (*(int *)(param_5 + 0x56c) != 0) {
      for (iVar3 = 0; iVar3 < (int)(uint)*(ushort *)(*(int *)(*(int *)(param_5 + 0x534) + 100) + 4);
          iVar3 = iVar3 + 1) {
        **(undefined4 **)(*(int *)(*(int *)(param_5 + 0x534) + 0x4c) + iVar3 * 0x4c + 0xc) =
             *(undefined4 *)(*(int *)(param_5 + 0x56c) + iVar3 * 0x410 + 0x400);
        *(undefined4 *)(*(int *)(*(int *)(*(int *)(param_5 + 0x534) + 0x4c) + iVar3 * 0x4c) + 0xf4)
             = *(undefined4 *)(*(int *)(param_5 + 0x56c) + iVar3 * 0x410 + 0x400);
        *(undefined4 *)
         (*(int *)(*(int *)(*(int *)(param_5 + 0x534) + 0x4c) + iVar3 * 0x4c + 4) + 0xf4) =
             *(undefined4 *)(*(int *)(param_5 + 0x56c) + iVar3 * 0x410 + 0x400);
      }
    }
  }
  else {
    if (*(float *)(param_5 + 0x550) == 0.0) {
      if (*(int *)(param_5 + 0x560) != 0) {
        for (iVar3 = 0; iVar3 < (int)(uint)*(ushort *)(*(int *)(param_5 + 100) + 4);
            iVar3 = iVar3 + 1) {
          for (iVar2 = 0;
              iVar2 < *(int *)(*(int *)(*(int *)(param_5 + 0x4c) + iVar3 * 0x4c + 0xc) + 4);
              iVar2 = iVar2 + 1) {
            *(undefined1 *)(*(int *)(param_5 + 0x560) + iVar3 * 0x410 + iVar2 * 4) =
                 *(undefined1 *)
                  (*(int *)(*(int *)(param_5 + 0x560) + iVar3 * 0x410 + 0x400) + iVar2 * 4);
            *(undefined1 *)(*(int *)(param_5 + 0x560) + iVar3 * 0x410 + iVar2 * 4 + 3) =
                 *(undefined1 *)
                  (*(int *)(*(int *)(param_5 + 0x560) + iVar3 * 0x410 + 0x400) + iVar2 * 4 + 3);
          }
        }
      }
      if (*(int *)(param_5 + 0x568) != 0) {
        for (iVar3 = 0;
            iVar3 < (int)(uint)*(ushort *)(*(int *)(*(int *)(param_5 + 0x530) + 100) + 4);
            iVar3 = iVar3 + 1) {
          for (iVar2 = 0;
              iVar2 < *(int *)(*(int *)(*(int *)(*(int *)(param_5 + 0x530) + 0x4c) + iVar3 * 0x4c +
                                       0xc) + 4); iVar2 = iVar2 + 1) {
            *(undefined1 *)(*(int *)(param_5 + 0x568) + iVar3 * 0x410 + iVar2 * 4) =
                 *(undefined1 *)
                  (*(int *)(*(int *)(param_5 + 0x568) + iVar3 * 0x410 + 0x400) + iVar2 * 4);
            *(undefined1 *)(*(int *)(param_5 + 0x568) + iVar3 * 0x410 + iVar2 * 4 + 3) =
                 *(undefined1 *)
                  (*(int *)(*(int *)(param_5 + 0x568) + iVar3 * 0x410 + 0x400) + iVar2 * 4 + 3);
          }
        }
      }
      if (*(int *)(param_5 + 0x564) != 0) {
        for (iVar3 = 0;
            iVar3 < (int)(uint)*(ushort *)(*(int *)(*(int *)(param_5 + 0x52c) + 100) + 4);
            iVar3 = iVar3 + 1) {
          for (iVar2 = 0;
              iVar2 < *(int *)(*(int *)(*(int *)(*(int *)(param_5 + 0x52c) + 0x4c) + iVar3 * 0x4c +
                                       0xc) + 4); iVar2 = iVar2 + 1) {
            *(undefined1 *)(*(int *)(param_5 + 0x564) + iVar3 * 0x410 + iVar2 * 4) =
                 *(undefined1 *)
                  (*(int *)(*(int *)(param_5 + 0x564) + iVar3 * 0x410 + 0x400) + iVar2 * 4);
            *(undefined1 *)(*(int *)(param_5 + 0x564) + iVar3 * 0x410 + iVar2 * 4 + 3) =
                 *(undefined1 *)
                  (*(int *)(*(int *)(param_5 + 0x564) + iVar3 * 0x410 + 0x400) + iVar2 * 4 + 3);
          }
        }
      }
      if (*(int *)(param_5 + 0x56c) != 0) {
        for (iVar3 = 0;
            iVar3 < (int)(uint)*(ushort *)(*(int *)(*(int *)(param_5 + 0x534) + 100) + 4);
            iVar3 = iVar3 + 1) {
          for (iVar2 = 0;
              iVar2 < *(int *)(*(int *)(*(int *)(*(int *)(param_5 + 0x534) + 0x4c) + iVar3 * 0x4c +
                                       0xc) + 4); iVar2 = iVar2 + 1) {
            *(undefined1 *)(*(int *)(param_5 + 0x56c) + iVar3 * 0x410 + iVar2 * 4) =
                 *(undefined1 *)
                  (*(int *)(*(int *)(param_5 + 0x56c) + iVar3 * 0x410 + 0x400) + iVar2 * 4);
            *(undefined1 *)(*(int *)(param_5 + 0x56c) + iVar3 * 0x410 + iVar2 * 4 + 3) =
                 *(undefined1 *)
                  (*(int *)(*(int *)(param_5 + 0x56c) + iVar3 * 0x410 + 0x400) + iVar2 * 4 + 3);
          }
        }
      }
    }
    else if (0.0 < *(float *)(param_5 + 0x550)) {
      if (*(int *)(param_5 + 0x560) != 0) {
        for (iVar3 = 0; iVar3 < (int)(uint)*(ushort *)(*(int *)(param_5 + 100) + 4);
            iVar3 = iVar3 + 1) {
          for (iVar2 = 0;
              iVar2 < *(int *)(*(int *)(*(int *)(param_5 + 0x4c) + iVar3 * 0x4c + 0xc) + 4);
              iVar2 = iVar2 + 1) {
            fVar8 = (float)*(byte *)(*(int *)(*(int *)(param_5 + 0x560) + iVar3 * 0x410 + 0x400) +
                                    iVar2 * 4) +
                    *(float *)(param_5 + 0x550) *
                    (float)(int)(0xff - (uint)*(byte *)(*(int *)(*(int *)(param_5 + 0x560) +
                                                                 iVar3 * 0x410 + 0x400) + iVar2 * 4)
                                );
            if (fVar8 < 2.1474836e+09) {
              uVar7 = (undefined1)(int)fVar8;
            }
            else {
              uVar7 = (undefined1)(int)(fVar8 - 2.1474836e+09);
            }
            *(undefined1 *)(*(int *)(param_5 + 0x560) + iVar3 * 0x410 + iVar2 * 4) = uVar7;
            *(undefined1 *)(*(int *)(param_5 + 0x560) + iVar3 * 0x410 + iVar2 * 4 + 3) =
                 *(undefined1 *)
                  (*(int *)(*(int *)(param_5 + 0x560) + iVar3 * 0x410 + 0x400) + iVar2 * 4 + 3);
          }
        }
      }
      if (*(int *)(param_5 + 0x568) != 0) {
        for (iVar3 = 0;
            iVar3 < (int)(uint)*(ushort *)(*(int *)(*(int *)(param_5 + 0x530) + 100) + 4);
            iVar3 = iVar3 + 1) {
          for (iVar2 = 0;
              iVar2 < *(int *)(*(int *)(*(int *)(*(int *)(param_5 + 0x530) + 0x4c) + iVar3 * 0x4c +
                                       0xc) + 4); iVar2 = iVar2 + 1) {
            fVar8 = (float)*(byte *)(*(int *)(*(int *)(param_5 + 0x568) + iVar3 * 0x410 + 0x400) +
                                    iVar2 * 4) +
                    *(float *)(param_5 + 0x550) *
                    (float)(int)(0xff - (uint)*(byte *)(*(int *)(*(int *)(param_5 + 0x568) +
                                                                 iVar3 * 0x410 + 0x400) + iVar2 * 4)
                                );
            if (fVar8 < 2.1474836e+09) {
              uVar7 = (undefined1)(int)fVar8;
            }
            else {
              uVar7 = (undefined1)(int)(fVar8 - 2.1474836e+09);
            }
            *(undefined1 *)(*(int *)(param_5 + 0x568) + iVar3 * 0x410 + iVar2 * 4) = uVar7;
            *(undefined1 *)(*(int *)(param_5 + 0x568) + iVar3 * 0x410 + iVar2 * 4 + 3) =
                 *(undefined1 *)
                  (*(int *)(*(int *)(param_5 + 0x568) + iVar3 * 0x410 + 0x400) + iVar2 * 4 + 3);
          }
        }
      }
      if (*(int *)(param_5 + 0x564) != 0) {
        for (iVar3 = 0;
            iVar3 < (int)(uint)*(ushort *)(*(int *)(*(int *)(param_5 + 0x52c) + 100) + 4);
            iVar3 = iVar3 + 1) {
          for (iVar2 = 0;
              iVar2 < *(int *)(*(int *)(*(int *)(*(int *)(param_5 + 0x52c) + 0x4c) + iVar3 * 0x4c +
                                       0xc) + 4); iVar2 = iVar2 + 1) {
            fVar8 = (float)*(byte *)(*(int *)(*(int *)(param_5 + 0x564) + iVar3 * 0x410 + 0x400) +
                                    iVar2 * 4) +
                    *(float *)(param_5 + 0x550) *
                    (float)(int)(0xff - (uint)*(byte *)(*(int *)(*(int *)(param_5 + 0x564) +
                                                                 iVar3 * 0x410 + 0x400) + iVar2 * 4)
                                );
            if (fVar8 < 2.1474836e+09) {
              uVar7 = (undefined1)(int)fVar8;
            }
            else {
              uVar7 = (undefined1)(int)(fVar8 - 2.1474836e+09);
            }
            *(undefined1 *)(*(int *)(param_5 + 0x564) + iVar3 * 0x410 + iVar2 * 4) = uVar7;
            *(undefined1 *)(*(int *)(param_5 + 0x564) + iVar3 * 0x410 + iVar2 * 4 + 3) =
                 *(undefined1 *)
                  (*(int *)(*(int *)(param_5 + 0x564) + iVar3 * 0x410 + 0x400) + iVar2 * 4 + 3);
          }
        }
      }
      if (*(int *)(param_5 + 0x56c) != 0) {
        for (iVar3 = 0;
            iVar3 < (int)(uint)*(ushort *)(*(int *)(*(int *)(param_5 + 0x534) + 100) + 4);
            iVar3 = iVar3 + 1) {
          for (iVar2 = 0;
              iVar2 < *(int *)(*(int *)(*(int *)(*(int *)(param_5 + 0x534) + 0x4c) + iVar3 * 0x4c +
                                       0xc) + 4); iVar2 = iVar2 + 1) {
            fVar8 = (float)*(byte *)(*(int *)(*(int *)(param_5 + 0x56c) + iVar3 * 0x410 + 0x400) +
                                    iVar2 * 4) +
                    *(float *)(param_5 + 0x550) *
                    (float)(int)(0xff - (uint)*(byte *)(*(int *)(*(int *)(param_5 + 0x56c) +
                                                                 iVar3 * 0x410 + 0x400) + iVar2 * 4)
                                );
            if (fVar8 < 2.1474836e+09) {
              uVar7 = (undefined1)(int)fVar8;
            }
            else {
              uVar7 = (undefined1)(int)(fVar8 - 2.1474836e+09);
            }
            *(undefined1 *)(*(int *)(param_5 + 0x56c) + iVar3 * 0x410 + iVar2 * 4) = uVar7;
            *(undefined1 *)(*(int *)(param_5 + 0x56c) + iVar3 * 0x410 + iVar2 * 4 + 3) =
                 *(undefined1 *)
                  (*(int *)(*(int *)(param_5 + 0x56c) + iVar3 * 0x410 + 0x400) + iVar2 * 4 + 3);
          }
        }
      }
    }
    else {
      if (*(int *)(param_5 + 0x560) != 0) {
        for (iVar3 = 0; iVar3 < (int)(uint)*(ushort *)(*(int *)(param_5 + 100) + 4);
            iVar3 = iVar3 + 1) {
          for (iVar2 = 0;
              iVar2 < *(int *)(*(int *)(*(int *)(param_5 + 0x4c) + iVar3 * 0x4c + 0xc) + 4);
              iVar2 = iVar2 + 1) {
            fVar8 = (*(float *)(param_5 + 0x550) + 1.0) *
                    (float)*(byte *)(*(int *)(*(int *)(param_5 + 0x560) + iVar3 * 0x410 + 0x400) +
                                    iVar2 * 4);
            if (fVar8 < 2.1474836e+09) {
              uVar7 = (undefined1)(int)fVar8;
            }
            else {
              uVar7 = (undefined1)(int)(fVar8 - 2.1474836e+09);
            }
            *(undefined1 *)(*(int *)(param_5 + 0x560) + iVar3 * 0x410 + iVar2 * 4) = uVar7;
            *(undefined1 *)(*(int *)(param_5 + 0x560) + iVar3 * 0x410 + iVar2 * 4 + 3) =
                 *(undefined1 *)
                  (*(int *)(*(int *)(param_5 + 0x560) + iVar3 * 0x410 + 0x400) + iVar2 * 4 + 3);
          }
        }
      }
      if (*(int *)(param_5 + 0x568) != 0) {
        for (iVar3 = 0;
            iVar3 < (int)(uint)*(ushort *)(*(int *)(*(int *)(param_5 + 0x530) + 100) + 4);
            iVar3 = iVar3 + 1) {
          for (iVar2 = 0;
              iVar2 < *(int *)(*(int *)(*(int *)(*(int *)(param_5 + 0x530) + 0x4c) + iVar3 * 0x4c +
                                       0xc) + 4); iVar2 = iVar2 + 1) {
            fVar8 = (*(float *)(param_5 + 0x550) + 1.0) *
                    (float)*(byte *)(*(int *)(*(int *)(param_5 + 0x568) + iVar3 * 0x410 + 0x400) +
                                    iVar2 * 4);
            if (fVar8 < 2.1474836e+09) {
              uVar7 = (undefined1)(int)fVar8;
            }
            else {
              uVar7 = (undefined1)(int)(fVar8 - 2.1474836e+09);
            }
            *(undefined1 *)(*(int *)(param_5 + 0x568) + iVar3 * 0x410 + iVar2 * 4) = uVar7;
            *(undefined1 *)(*(int *)(param_5 + 0x568) + iVar3 * 0x410 + iVar2 * 4 + 3) =
                 *(undefined1 *)
                  (*(int *)(*(int *)(param_5 + 0x568) + iVar3 * 0x410 + 0x400) + iVar2 * 4 + 3);
          }
        }
      }
      if (*(int *)(param_5 + 0x564) != 0) {
        for (iVar3 = 0;
            iVar3 < (int)(uint)*(ushort *)(*(int *)(*(int *)(param_5 + 0x52c) + 100) + 4);
            iVar3 = iVar3 + 1) {
          for (iVar2 = 0;
              iVar2 < *(int *)(*(int *)(*(int *)(*(int *)(param_5 + 0x52c) + 0x4c) + iVar3 * 0x4c +
                                       0xc) + 4); iVar2 = iVar2 + 1) {
            fVar8 = (*(float *)(param_5 + 0x550) + 1.0) *
                    (float)*(byte *)(*(int *)(*(int *)(param_5 + 0x564) + iVar3 * 0x410 + 0x400) +
                                    iVar2 * 4);
            if (fVar8 < 2.1474836e+09) {
              uVar7 = (undefined1)(int)fVar8;
            }
            else {
              uVar7 = (undefined1)(int)(fVar8 - 2.1474836e+09);
            }
            *(undefined1 *)(*(int *)(param_5 + 0x564) + iVar3 * 0x410 + iVar2 * 4) = uVar7;
            *(undefined1 *)(*(int *)(param_5 + 0x564) + iVar3 * 0x410 + iVar2 * 4 + 3) =
                 *(undefined1 *)
                  (*(int *)(*(int *)(param_5 + 0x564) + iVar3 * 0x410 + 0x400) + iVar2 * 4 + 3);
          }
        }
      }
      if (*(int *)(param_5 + 0x56c) != 0) {
        for (iVar3 = 0;
            iVar3 < (int)(uint)*(ushort *)(*(int *)(*(int *)(param_5 + 0x534) + 100) + 4);
            iVar3 = iVar3 + 1) {
          for (iVar2 = 0;
              iVar2 < *(int *)(*(int *)(*(int *)(*(int *)(param_5 + 0x534) + 0x4c) + iVar3 * 0x4c +
                                       0xc) + 4); iVar2 = iVar2 + 1) {
            fVar8 = (*(float *)(param_5 + 0x550) + 1.0) *
                    (float)*(byte *)(*(int *)(*(int *)(param_5 + 0x56c) + iVar3 * 0x410 + 0x400) +
                                    iVar2 * 4);
            if (fVar8 < 2.1474836e+09) {
              uVar7 = (undefined1)(int)fVar8;
            }
            else {
              uVar7 = (undefined1)(int)(fVar8 - 2.1474836e+09);
            }
            *(undefined1 *)(*(int *)(param_5 + 0x56c) + iVar3 * 0x410 + iVar2 * 4) = uVar7;
            *(undefined1 *)(*(int *)(param_5 + 0x56c) + iVar3 * 0x410 + iVar2 * 4 + 3) =
                 *(undefined1 *)
                  (*(int *)(*(int *)(param_5 + 0x56c) + iVar3 * 0x410 + 0x400) + iVar2 * 4 + 3);
          }
        }
      }
    }
    if (*(float *)(param_5 + 0x554) == 0.0) {
      if (*(int *)(param_5 + 0x560) != 0) {
        for (iVar3 = 0; iVar3 < (int)(uint)*(ushort *)(*(int *)(param_5 + 100) + 4);
            iVar3 = iVar3 + 1) {
          for (iVar2 = 0;
              iVar2 < *(int *)(*(int *)(*(int *)(param_5 + 0x4c) + iVar3 * 0x4c + 0xc) + 4);
              iVar2 = iVar2 + 1) {
            *(undefined1 *)(*(int *)(param_5 + 0x560) + iVar3 * 0x410 + iVar2 * 4 + 1) =
                 *(undefined1 *)
                  (*(int *)(*(int *)(param_5 + 0x560) + iVar3 * 0x410 + 0x400) + iVar2 * 4 + 1);
          }
        }
      }
      if (*(int *)(param_5 + 0x568) != 0) {
        for (iVar3 = 0;
            iVar3 < (int)(uint)*(ushort *)(*(int *)(*(int *)(param_5 + 0x530) + 100) + 4);
            iVar3 = iVar3 + 1) {
          for (iVar2 = 0;
              iVar2 < *(int *)(*(int *)(*(int *)(*(int *)(param_5 + 0x530) + 0x4c) + iVar3 * 0x4c +
                                       0xc) + 4); iVar2 = iVar2 + 1) {
            *(undefined1 *)(*(int *)(param_5 + 0x568) + iVar3 * 0x410 + iVar2 * 4 + 1) =
                 *(undefined1 *)
                  (*(int *)(*(int *)(param_5 + 0x568) + iVar3 * 0x410 + 0x400) + iVar2 * 4 + 1);
          }
        }
      }
      if (*(int *)(param_5 + 0x564) != 0) {
        for (iVar3 = 0;
            iVar3 < (int)(uint)*(ushort *)(*(int *)(*(int *)(param_5 + 0x52c) + 100) + 4);
            iVar3 = iVar3 + 1) {
          for (iVar2 = 0;
              iVar2 < *(int *)(*(int *)(*(int *)(*(int *)(param_5 + 0x52c) + 0x4c) + iVar3 * 0x4c +
                                       0xc) + 4); iVar2 = iVar2 + 1) {
            *(undefined1 *)(*(int *)(param_5 + 0x564) + iVar3 * 0x410 + iVar2 * 4 + 1) =
                 *(undefined1 *)
                  (*(int *)(*(int *)(param_5 + 0x564) + iVar3 * 0x410 + 0x400) + iVar2 * 4 + 1);
          }
        }
      }
      if (*(int *)(param_5 + 0x56c) != 0) {
        for (iVar3 = 0;
            iVar3 < (int)(uint)*(ushort *)(*(int *)(*(int *)(param_5 + 0x534) + 100) + 4);
            iVar3 = iVar3 + 1) {
          for (iVar2 = 0;
              iVar2 < *(int *)(*(int *)(*(int *)(*(int *)(param_5 + 0x534) + 0x4c) + iVar3 * 0x4c +
                                       0xc) + 4); iVar2 = iVar2 + 1) {
            *(undefined1 *)(*(int *)(param_5 + 0x56c) + iVar3 * 0x410 + iVar2 * 4 + 1) =
                 *(undefined1 *)
                  (*(int *)(*(int *)(param_5 + 0x56c) + iVar3 * 0x410 + 0x400) + iVar2 * 4 + 1);
          }
        }
      }
    }
    else if (0.0 < *(float *)(param_5 + 0x554)) {
      if (*(int *)(param_5 + 0x560) != 0) {
        for (iVar3 = 0; iVar3 < (int)(uint)*(ushort *)(*(int *)(param_5 + 100) + 4);
            iVar3 = iVar3 + 1) {
          for (iVar2 = 0;
              iVar2 < *(int *)(*(int *)(*(int *)(param_5 + 0x4c) + iVar3 * 0x4c + 0xc) + 4);
              iVar2 = iVar2 + 1) {
            fVar8 = (float)*(byte *)(*(int *)(*(int *)(param_5 + 0x560) + iVar3 * 0x410 + 0x400) +
                                     iVar2 * 4 + 1) +
                    *(float *)(param_5 + 0x554) *
                    (float)(int)(0xff - (uint)*(byte *)(*(int *)(*(int *)(param_5 + 0x560) +
                                                                 iVar3 * 0x410 + 0x400) + iVar2 * 4
                                                       + 1));
            if (fVar8 < 2.1474836e+09) {
              uVar7 = (undefined1)(int)fVar8;
            }
            else {
              uVar7 = (undefined1)(int)(fVar8 - 2.1474836e+09);
            }
            *(undefined1 *)(*(int *)(param_5 + 0x560) + iVar3 * 0x410 + iVar2 * 4 + 1) = uVar7;
          }
        }
      }
      if (*(int *)(param_5 + 0x568) != 0) {
        for (iVar3 = 0;
            iVar3 < (int)(uint)*(ushort *)(*(int *)(*(int *)(param_5 + 0x530) + 100) + 4);
            iVar3 = iVar3 + 1) {
          for (iVar2 = 0;
              iVar2 < *(int *)(*(int *)(*(int *)(*(int *)(param_5 + 0x530) + 0x4c) + iVar3 * 0x4c +
                                       0xc) + 4); iVar2 = iVar2 + 1) {
            fVar8 = (float)*(byte *)(*(int *)(*(int *)(param_5 + 0x568) + iVar3 * 0x410 + 0x400) +
                                     iVar2 * 4 + 1) +
                    *(float *)(param_5 + 0x554) *
                    (float)(int)(0xff - (uint)*(byte *)(*(int *)(*(int *)(param_5 + 0x568) +
                                                                 iVar3 * 0x410 + 0x400) + iVar2 * 4
                                                       + 1));
            if (fVar8 < 2.1474836e+09) {
              uVar7 = (undefined1)(int)fVar8;
            }
            else {
              uVar7 = (undefined1)(int)(fVar8 - 2.1474836e+09);
            }
            *(undefined1 *)(*(int *)(param_5 + 0x568) + iVar3 * 0x410 + iVar2 * 4 + 1) = uVar7;
          }
        }
      }
      if (*(int *)(param_5 + 0x564) != 0) {
        for (iVar3 = 0;
            iVar3 < (int)(uint)*(ushort *)(*(int *)(*(int *)(param_5 + 0x52c) + 100) + 4);
            iVar3 = iVar3 + 1) {
          for (iVar2 = 0;
              iVar2 < *(int *)(*(int *)(*(int *)(*(int *)(param_5 + 0x52c) + 0x4c) + iVar3 * 0x4c +
                                       0xc) + 4); iVar2 = iVar2 + 1) {
            fVar8 = (float)*(byte *)(*(int *)(*(int *)(param_5 + 0x564) + iVar3 * 0x410 + 0x400) +
                                     iVar2 * 4 + 1) +
                    *(float *)(param_5 + 0x554) *
                    (float)(int)(0xff - (uint)*(byte *)(*(int *)(*(int *)(param_5 + 0x564) +
                                                                 iVar3 * 0x410 + 0x400) + iVar2 * 4
                                                       + 1));
            if (fVar8 < 2.1474836e+09) {
              uVar7 = (undefined1)(int)fVar8;
            }
            else {
              uVar7 = (undefined1)(int)(fVar8 - 2.1474836e+09);
            }
            *(undefined1 *)(*(int *)(param_5 + 0x564) + iVar3 * 0x410 + iVar2 * 4 + 1) = uVar7;
          }
        }
      }
      if (*(int *)(param_5 + 0x56c) != 0) {
        for (iVar3 = 0;
            iVar3 < (int)(uint)*(ushort *)(*(int *)(*(int *)(param_5 + 0x534) + 100) + 4);
            iVar3 = iVar3 + 1) {
          for (iVar2 = 0;
              iVar2 < *(int *)(*(int *)(*(int *)(*(int *)(param_5 + 0x534) + 0x4c) + iVar3 * 0x4c +
                                       0xc) + 4); iVar2 = iVar2 + 1) {
            fVar8 = (float)*(byte *)(*(int *)(*(int *)(param_5 + 0x56c) + iVar3 * 0x410 + 0x400) +
                                     iVar2 * 4 + 1) +
                    *(float *)(param_5 + 0x554) *
                    (float)(int)(0xff - (uint)*(byte *)(*(int *)(*(int *)(param_5 + 0x56c) +
                                                                 iVar3 * 0x410 + 0x400) + iVar2 * 4
                                                       + 1));
            if (fVar8 < 2.1474836e+09) {
              uVar7 = (undefined1)(int)fVar8;
            }
            else {
              uVar7 = (undefined1)(int)(fVar8 - 2.1474836e+09);
            }
            *(undefined1 *)(*(int *)(param_5 + 0x56c) + iVar3 * 0x410 + iVar2 * 4 + 1) = uVar7;
          }
        }
      }
    }
    else {
      if (*(int *)(param_5 + 0x560) != 0) {
        for (iVar3 = 0; iVar3 < (int)(uint)*(ushort *)(*(int *)(param_5 + 100) + 4);
            iVar3 = iVar3 + 1) {
          for (iVar2 = 0;
              iVar2 < *(int *)(*(int *)(*(int *)(param_5 + 0x4c) + iVar3 * 0x4c + 0xc) + 4);
              iVar2 = iVar2 + 1) {
            fVar8 = (*(float *)(param_5 + 0x554) + 1.0) *
                    (float)*(byte *)(*(int *)(*(int *)(param_5 + 0x560) + iVar3 * 0x410 + 0x400) +
                                     iVar2 * 4 + 1);
            if (fVar8 < 2.1474836e+09) {
              uVar7 = (undefined1)(int)fVar8;
            }
            else {
              uVar7 = (undefined1)(int)(fVar8 - 2.1474836e+09);
            }
            *(undefined1 *)(*(int *)(param_5 + 0x560) + iVar3 * 0x410 + iVar2 * 4 + 1) = uVar7;
          }
        }
      }
      if (*(int *)(param_5 + 0x568) != 0) {
        for (iVar3 = 0;
            iVar3 < (int)(uint)*(ushort *)(*(int *)(*(int *)(param_5 + 0x530) + 100) + 4);
            iVar3 = iVar3 + 1) {
          for (iVar2 = 0;
              iVar2 < *(int *)(*(int *)(*(int *)(*(int *)(param_5 + 0x530) + 0x4c) + iVar3 * 0x4c +
                                       0xc) + 4); iVar2 = iVar2 + 1) {
            fVar8 = (*(float *)(param_5 + 0x554) + 1.0) *
                    (float)*(byte *)(*(int *)(*(int *)(param_5 + 0x568) + iVar3 * 0x410 + 0x400) +
                                     iVar2 * 4 + 1);
            if (fVar8 < 2.1474836e+09) {
              uVar7 = (undefined1)(int)fVar8;
            }
            else {
              uVar7 = (undefined1)(int)(fVar8 - 2.1474836e+09);
            }
            *(undefined1 *)(*(int *)(param_5 + 0x568) + iVar3 * 0x410 + iVar2 * 4 + 1) = uVar7;
          }
        }
      }
      if (*(int *)(param_5 + 0x564) != 0) {
        for (iVar3 = 0;
            iVar3 < (int)(uint)*(ushort *)(*(int *)(*(int *)(param_5 + 0x52c) + 100) + 4);
            iVar3 = iVar3 + 1) {
          for (iVar2 = 0;
              iVar2 < *(int *)(*(int *)(*(int *)(*(int *)(param_5 + 0x52c) + 0x4c) + iVar3 * 0x4c +
                                       0xc) + 4); iVar2 = iVar2 + 1) {
            fVar8 = (*(float *)(param_5 + 0x554) + 1.0) *
                    (float)*(byte *)(*(int *)(*(int *)(param_5 + 0x564) + iVar3 * 0x410 + 0x400) +
                                     iVar2 * 4 + 1);
            if (fVar8 < 2.1474836e+09) {
              uVar7 = (undefined1)(int)fVar8;
            }
            else {
              uVar7 = (undefined1)(int)(fVar8 - 2.1474836e+09);
            }
            *(undefined1 *)(*(int *)(param_5 + 0x564) + iVar3 * 0x410 + iVar2 * 4 + 1) = uVar7;
          }
        }
      }
      if (*(int *)(param_5 + 0x56c) != 0) {
        for (iVar3 = 0;
            iVar3 < (int)(uint)*(ushort *)(*(int *)(*(int *)(param_5 + 0x534) + 100) + 4);
            iVar3 = iVar3 + 1) {
          for (iVar2 = 0;
              iVar2 < *(int *)(*(int *)(*(int *)(*(int *)(param_5 + 0x534) + 0x4c) + iVar3 * 0x4c +
                                       0xc) + 4); iVar2 = iVar2 + 1) {
            fVar8 = (*(float *)(param_5 + 0x554) + 1.0) *
                    (float)*(byte *)(*(int *)(*(int *)(param_5 + 0x56c) + iVar3 * 0x410 + 0x400) +
                                     iVar2 * 4 + 1);
            if (fVar8 < 2.1474836e+09) {
              uVar7 = (undefined1)(int)fVar8;
            }
            else {
              uVar7 = (undefined1)(int)(fVar8 - 2.1474836e+09);
            }
            *(undefined1 *)(*(int *)(param_5 + 0x56c) + iVar3 * 0x410 + iVar2 * 4 + 1) = uVar7;
          }
        }
      }
    }
    if (*(float *)(param_5 + 0x558) == 0.0) {
      if (*(int *)(param_5 + 0x560) != 0) {
        for (iVar3 = 0; iVar3 < (int)(uint)*(ushort *)(*(int *)(param_5 + 100) + 4);
            iVar3 = iVar3 + 1) {
          for (iVar2 = 0;
              iVar2 < *(int *)(*(int *)(*(int *)(param_5 + 0x4c) + iVar3 * 0x4c + 0xc) + 4);
              iVar2 = iVar2 + 1) {
            *(undefined1 *)(*(int *)(param_5 + 0x560) + iVar3 * 0x410 + iVar2 * 4 + 2) =
                 *(undefined1 *)
                  (*(int *)(*(int *)(param_5 + 0x560) + iVar3 * 0x410 + 0x400) + iVar2 * 4 + 2);
          }
          **(int **)(*(int *)(param_5 + 0x4c) + iVar3 * 0x4c + 0xc) =
               *(int *)(param_5 + 0x560) + iVar3 * 0x410;
          *(int *)(*(int *)(*(int *)(param_5 + 0x4c) + iVar3 * 0x4c) + 0xf4) =
               *(int *)(param_5 + 0x560) + iVar3 * 0x410;
          *(int *)(*(int *)(*(int *)(param_5 + 0x4c) + iVar3 * 0x4c + 4) + 0xf4) =
               *(int *)(param_5 + 0x560) + iVar3 * 0x410;
        }
      }
      if (*(int *)(param_5 + 0x568) != 0) {
        for (iVar3 = 0;
            iVar3 < (int)(uint)*(ushort *)(*(int *)(*(int *)(param_5 + 0x530) + 100) + 4);
            iVar3 = iVar3 + 1) {
          for (iVar2 = 0;
              iVar2 < *(int *)(*(int *)(*(int *)(*(int *)(param_5 + 0x530) + 0x4c) + iVar3 * 0x4c +
                                       0xc) + 4); iVar2 = iVar2 + 1) {
            *(undefined1 *)(*(int *)(param_5 + 0x568) + iVar3 * 0x410 + iVar2 * 4 + 2) =
                 *(undefined1 *)
                  (*(int *)(*(int *)(param_5 + 0x568) + iVar3 * 0x410 + 0x400) + iVar2 * 4 + 2);
          }
          **(int **)(*(int *)(*(int *)(param_5 + 0x530) + 0x4c) + iVar3 * 0x4c + 0xc) =
               *(int *)(param_5 + 0x568) + iVar3 * 0x410;
          *(int *)(*(int *)(*(int *)(*(int *)(param_5 + 0x530) + 0x4c) + iVar3 * 0x4c) + 0xf4) =
               *(int *)(param_5 + 0x568) + iVar3 * 0x410;
          *(int *)(*(int *)(*(int *)(*(int *)(param_5 + 0x530) + 0x4c) + iVar3 * 0x4c + 4) + 0xf4) =
               *(int *)(param_5 + 0x568) + iVar3 * 0x410;
        }
      }
      if (*(int *)(param_5 + 0x564) != 0) {
        for (iVar3 = 0;
            iVar3 < (int)(uint)*(ushort *)(*(int *)(*(int *)(param_5 + 0x52c) + 100) + 4);
            iVar3 = iVar3 + 1) {
          for (iVar2 = 0;
              iVar2 < *(int *)(*(int *)(*(int *)(*(int *)(param_5 + 0x52c) + 0x4c) + iVar3 * 0x4c +
                                       0xc) + 4); iVar2 = iVar2 + 1) {
            *(undefined1 *)(*(int *)(param_5 + 0x564) + iVar3 * 0x410 + iVar2 * 4 + 2) =
                 *(undefined1 *)
                  (*(int *)(*(int *)(param_5 + 0x564) + iVar3 * 0x410 + 0x400) + iVar2 * 4 + 2);
          }
          **(int **)(*(int *)(*(int *)(param_5 + 0x52c) + 0x4c) + iVar3 * 0x4c + 0xc) =
               *(int *)(param_5 + 0x564) + iVar3 * 0x410;
          *(int *)(*(int *)(*(int *)(*(int *)(param_5 + 0x52c) + 0x4c) + iVar3 * 0x4c) + 0xf4) =
               *(int *)(param_5 + 0x564) + iVar3 * 0x410;
          *(int *)(*(int *)(*(int *)(*(int *)(param_5 + 0x52c) + 0x4c) + iVar3 * 0x4c + 4) + 0xf4) =
               *(int *)(param_5 + 0x564) + iVar3 * 0x410;
        }
      }
      if (*(int *)(param_5 + 0x56c) != 0) {
        for (iVar3 = 0;
            iVar3 < (int)(uint)*(ushort *)(*(int *)(*(int *)(param_5 + 0x534) + 100) + 4);
            iVar3 = iVar3 + 1) {
          for (iVar2 = 0;
              iVar2 < *(int *)(*(int *)(*(int *)(*(int *)(param_5 + 0x534) + 0x4c) + iVar3 * 0x4c +
                                       0xc) + 4); iVar2 = iVar2 + 1) {
            *(undefined1 *)(*(int *)(param_5 + 0x56c) + iVar3 * 0x410 + iVar2 * 4 + 2) =
                 *(undefined1 *)
                  (*(int *)(*(int *)(param_5 + 0x56c) + iVar3 * 0x410 + 0x400) + iVar2 * 4 + 2);
          }
          **(int **)(*(int *)(*(int *)(param_5 + 0x534) + 0x4c) + iVar3 * 0x4c + 0xc) =
               *(int *)(param_5 + 0x56c) + iVar3 * 0x410;
          *(int *)(*(int *)(*(int *)(*(int *)(param_5 + 0x534) + 0x4c) + iVar3 * 0x4c) + 0xf4) =
               *(int *)(param_5 + 0x56c) + iVar3 * 0x410;
          *(int *)(*(int *)(*(int *)(*(int *)(param_5 + 0x534) + 0x4c) + iVar3 * 0x4c + 4) + 0xf4) =
               *(int *)(param_5 + 0x56c) + iVar3 * 0x410;
        }
      }
    }
    else if (0.0 < *(float *)(param_5 + 0x558)) {
      if (*(int *)(param_5 + 0x560) != 0) {
        for (iVar3 = 0; iVar3 < (int)(uint)*(ushort *)(*(int *)(param_5 + 100) + 4);
            iVar3 = iVar3 + 1) {
          for (iVar2 = 0;
              iVar2 < *(int *)(*(int *)(*(int *)(param_5 + 0x4c) + iVar3 * 0x4c + 0xc) + 4);
              iVar2 = iVar2 + 1) {
            fVar8 = (float)*(byte *)(*(int *)(*(int *)(param_5 + 0x560) + iVar3 * 0x410 + 0x400) +
                                     iVar2 * 4 + 2) +
                    *(float *)(param_5 + 0x558) *
                    (float)(int)(0xff - (uint)*(byte *)(*(int *)(*(int *)(param_5 + 0x560) +
                                                                 iVar3 * 0x410 + 0x400) + iVar2 * 4
                                                       + 2));
            if (fVar8 < 2.1474836e+09) {
              uVar7 = (undefined1)(int)fVar8;
            }
            else {
              uVar7 = (undefined1)(int)(fVar8 - 2.1474836e+09);
            }
            *(undefined1 *)(*(int *)(param_5 + 0x560) + iVar3 * 0x410 + iVar2 * 4 + 2) = uVar7;
          }
          **(int **)(*(int *)(param_5 + 0x4c) + iVar3 * 0x4c + 0xc) =
               *(int *)(param_5 + 0x560) + iVar3 * 0x410;
          *(int *)(*(int *)(*(int *)(param_5 + 0x4c) + iVar3 * 0x4c) + 0xf4) =
               *(int *)(param_5 + 0x560) + iVar3 * 0x410;
          *(int *)(*(int *)(*(int *)(param_5 + 0x4c) + iVar3 * 0x4c + 4) + 0xf4) =
               *(int *)(param_5 + 0x560) + iVar3 * 0x410;
        }
      }
      if (*(int *)(param_5 + 0x568) != 0) {
        for (iVar3 = 0;
            iVar3 < (int)(uint)*(ushort *)(*(int *)(*(int *)(param_5 + 0x530) + 100) + 4);
            iVar3 = iVar3 + 1) {
          for (iVar2 = 0;
              iVar2 < *(int *)(*(int *)(*(int *)(*(int *)(param_5 + 0x530) + 0x4c) + iVar3 * 0x4c +
                                       0xc) + 4); iVar2 = iVar2 + 1) {
            fVar8 = (float)*(byte *)(*(int *)(*(int *)(param_5 + 0x568) + iVar3 * 0x410 + 0x400) +
                                     iVar2 * 4 + 2) +
                    *(float *)(param_5 + 0x558) *
                    (float)(int)(0xff - (uint)*(byte *)(*(int *)(*(int *)(param_5 + 0x568) +
                                                                 iVar3 * 0x410 + 0x400) + iVar2 * 4
                                                       + 2));
            if (fVar8 < 2.1474836e+09) {
              uVar7 = (undefined1)(int)fVar8;
            }
            else {
              uVar7 = (undefined1)(int)(fVar8 - 2.1474836e+09);
            }
            *(undefined1 *)(*(int *)(param_5 + 0x568) + iVar3 * 0x410 + iVar2 * 4 + 2) = uVar7;
          }
          **(int **)(*(int *)(*(int *)(param_5 + 0x530) + 0x4c) + iVar3 * 0x4c + 0xc) =
               *(int *)(param_5 + 0x568) + iVar3 * 0x410;
          *(int *)(*(int *)(*(int *)(*(int *)(param_5 + 0x530) + 0x4c) + iVar3 * 0x4c) + 0xf4) =
               *(int *)(param_5 + 0x568) + iVar3 * 0x410;
          *(int *)(*(int *)(*(int *)(*(int *)(param_5 + 0x530) + 0x4c) + iVar3 * 0x4c + 4) + 0xf4) =
               *(int *)(param_5 + 0x568) + iVar3 * 0x410;
        }
      }
      if (*(int *)(param_5 + 0x564) != 0) {
        for (iVar3 = 0;
            iVar3 < (int)(uint)*(ushort *)(*(int *)(*(int *)(param_5 + 0x52c) + 100) + 4);
            iVar3 = iVar3 + 1) {
          for (iVar2 = 0;
              iVar2 < *(int *)(*(int *)(*(int *)(*(int *)(param_5 + 0x52c) + 0x4c) + iVar3 * 0x4c +
                                       0xc) + 4); iVar2 = iVar2 + 1) {
            fVar8 = (float)*(byte *)(*(int *)(*(int *)(param_5 + 0x564) + iVar3 * 0x410 + 0x400) +
                                     iVar2 * 4 + 2) +
                    *(float *)(param_5 + 0x558) *
                    (float)(int)(0xff - (uint)*(byte *)(*(int *)(*(int *)(param_5 + 0x564) +
                                                                 iVar3 * 0x410 + 0x400) + iVar2 * 4
                                                       + 2));
            if (fVar8 < 2.1474836e+09) {
              uVar7 = (undefined1)(int)fVar8;
            }
            else {
              uVar7 = (undefined1)(int)(fVar8 - 2.1474836e+09);
            }
            *(undefined1 *)(*(int *)(param_5 + 0x564) + iVar3 * 0x410 + iVar2 * 4 + 2) = uVar7;
          }
          **(int **)(*(int *)(*(int *)(param_5 + 0x52c) + 0x4c) + iVar3 * 0x4c + 0xc) =
               *(int *)(param_5 + 0x564) + iVar3 * 0x410;
          *(int *)(*(int *)(*(int *)(*(int *)(param_5 + 0x52c) + 0x4c) + iVar3 * 0x4c) + 0xf4) =
               *(int *)(param_5 + 0x564) + iVar3 * 0x410;
          *(int *)(*(int *)(*(int *)(*(int *)(param_5 + 0x52c) + 0x4c) + iVar3 * 0x4c + 4) + 0xf4) =
               *(int *)(param_5 + 0x564) + iVar3 * 0x410;
        }
      }
      if (*(int *)(param_5 + 0x56c) != 0) {
        for (iVar3 = 0;
            iVar3 < (int)(uint)*(ushort *)(*(int *)(*(int *)(param_5 + 0x534) + 100) + 4);
            iVar3 = iVar3 + 1) {
          for (iVar2 = 0;
              iVar2 < *(int *)(*(int *)(*(int *)(*(int *)(param_5 + 0x534) + 0x4c) + iVar3 * 0x4c +
                                       0xc) + 4); iVar2 = iVar2 + 1) {
            fVar8 = (float)*(byte *)(*(int *)(*(int *)(param_5 + 0x56c) + iVar3 * 0x410 + 0x400) +
                                     iVar2 * 4 + 2) +
                    *(float *)(param_5 + 0x558) *
                    (float)(int)(0xff - (uint)*(byte *)(*(int *)(*(int *)(param_5 + 0x56c) +
                                                                 iVar3 * 0x410 + 0x400) + iVar2 * 4
                                                       + 2));
            if (fVar8 < 2.1474836e+09) {
              uVar7 = (undefined1)(int)fVar8;
            }
            else {
              uVar7 = (undefined1)(int)(fVar8 - 2.1474836e+09);
            }
            *(undefined1 *)(*(int *)(param_5 + 0x56c) + iVar3 * 0x410 + iVar2 * 4 + 2) = uVar7;
          }
          **(int **)(*(int *)(*(int *)(param_5 + 0x534) + 0x4c) + iVar3 * 0x4c + 0xc) =
               *(int *)(param_5 + 0x56c) + iVar3 * 0x410;
          *(int *)(*(int *)(*(int *)(*(int *)(param_5 + 0x534) + 0x4c) + iVar3 * 0x4c) + 0xf4) =
               *(int *)(param_5 + 0x56c) + iVar3 * 0x410;
          *(int *)(*(int *)(*(int *)(*(int *)(param_5 + 0x534) + 0x4c) + iVar3 * 0x4c + 4) + 0xf4) =
               *(int *)(param_5 + 0x56c) + iVar3 * 0x410;
        }
      }
    }
    else {
      if (*(int *)(param_5 + 0x560) != 0) {
        for (iVar3 = 0; iVar3 < (int)(uint)*(ushort *)(*(int *)(param_5 + 100) + 4);
            iVar3 = iVar3 + 1) {
          for (iVar2 = 0;
              iVar2 < *(int *)(*(int *)(*(int *)(param_5 + 0x4c) + iVar3 * 0x4c + 0xc) + 4);
              iVar2 = iVar2 + 1) {
            fVar8 = (*(float *)(param_5 + 0x558) + 1.0) *
                    (float)*(byte *)(*(int *)(*(int *)(param_5 + 0x560) + iVar3 * 0x410 + 0x400) +
                                     iVar2 * 4 + 2);
            if (fVar8 < 2.1474836e+09) {
              uVar7 = (undefined1)(int)fVar8;
            }
            else {
              uVar7 = (undefined1)(int)(fVar8 - 2.1474836e+09);
            }
            *(undefined1 *)(*(int *)(param_5 + 0x560) + iVar3 * 0x410 + iVar2 * 4 + 2) = uVar7;
          }
          **(int **)(*(int *)(param_5 + 0x4c) + iVar3 * 0x4c + 0xc) =
               *(int *)(param_5 + 0x560) + iVar3 * 0x410;
          *(int *)(*(int *)(*(int *)(param_5 + 0x4c) + iVar3 * 0x4c) + 0xf4) =
               *(int *)(param_5 + 0x560) + iVar3 * 0x410;
          *(int *)(*(int *)(*(int *)(param_5 + 0x4c) + iVar3 * 0x4c + 4) + 0xf4) =
               *(int *)(param_5 + 0x560) + iVar3 * 0x410;
        }
      }
      if (*(int *)(param_5 + 0x568) != 0) {
        for (iVar3 = 0;
            iVar3 < (int)(uint)*(ushort *)(*(int *)(*(int *)(param_5 + 0x530) + 100) + 4);
            iVar3 = iVar3 + 1) {
          for (iVar2 = 0;
              iVar2 < *(int *)(*(int *)(*(int *)(*(int *)(param_5 + 0x530) + 0x4c) + iVar3 * 0x4c +
                                       0xc) + 4); iVar2 = iVar2 + 1) {
            fVar8 = (*(float *)(param_5 + 0x558) + 1.0) *
                    (float)*(byte *)(*(int *)(*(int *)(param_5 + 0x568) + iVar3 * 0x410 + 0x400) +
                                     iVar2 * 4 + 2);
            if (fVar8 < 2.1474836e+09) {
              uVar7 = (undefined1)(int)fVar8;
            }
            else {
              uVar7 = (undefined1)(int)(fVar8 - 2.1474836e+09);
            }
            *(undefined1 *)(*(int *)(param_5 + 0x568) + iVar3 * 0x410 + iVar2 * 4 + 2) = uVar7;
          }
          **(int **)(*(int *)(*(int *)(param_5 + 0x530) + 0x4c) + iVar3 * 0x4c + 0xc) =
               *(int *)(param_5 + 0x568) + iVar3 * 0x410;
          *(int *)(*(int *)(*(int *)(*(int *)(param_5 + 0x530) + 0x4c) + iVar3 * 0x4c) + 0xf4) =
               *(int *)(param_5 + 0x568) + iVar3 * 0x410;
          *(int *)(*(int *)(*(int *)(*(int *)(param_5 + 0x530) + 0x4c) + iVar3 * 0x4c + 4) + 0xf4) =
               *(int *)(param_5 + 0x568) + iVar3 * 0x410;
        }
      }
      if (*(int *)(param_5 + 0x564) != 0) {
        for (iVar3 = 0;
            iVar3 < (int)(uint)*(ushort *)(*(int *)(*(int *)(param_5 + 0x52c) + 100) + 4);
            iVar3 = iVar3 + 1) {
          for (iVar2 = 0;
              iVar2 < *(int *)(*(int *)(*(int *)(*(int *)(param_5 + 0x52c) + 0x4c) + iVar3 * 0x4c +
                                       0xc) + 4); iVar2 = iVar2 + 1) {
            fVar8 = (*(float *)(param_5 + 0x558) + 1.0) *
                    (float)*(byte *)(*(int *)(*(int *)(param_5 + 0x564) + iVar3 * 0x410 + 0x400) +
                                     iVar2 * 4 + 2);
            if (fVar8 < 2.1474836e+09) {
              uVar7 = (undefined1)(int)fVar8;
            }
            else {
              uVar7 = (undefined1)(int)(fVar8 - 2.1474836e+09);
            }
            *(undefined1 *)(*(int *)(param_5 + 0x564) + iVar3 * 0x410 + iVar2 * 4 + 2) = uVar7;
          }
          **(int **)(*(int *)(*(int *)(param_5 + 0x52c) + 0x4c) + iVar3 * 0x4c + 0xc) =
               *(int *)(param_5 + 0x564) + iVar3 * 0x410;
          *(int *)(*(int *)(*(int *)(*(int *)(param_5 + 0x52c) + 0x4c) + iVar3 * 0x4c) + 0xf4) =
               *(int *)(param_5 + 0x564) + iVar3 * 0x410;
          *(int *)(*(int *)(*(int *)(*(int *)(param_5 + 0x52c) + 0x4c) + iVar3 * 0x4c + 4) + 0xf4) =
               *(int *)(param_5 + 0x564) + iVar3 * 0x410;
        }
      }
      if (*(int *)(param_5 + 0x56c) != 0) {
        for (iVar3 = 0;
            iVar3 < (int)(uint)*(ushort *)(*(int *)(*(int *)(param_5 + 0x534) + 100) + 4);
            iVar3 = iVar3 + 1) {
          for (iVar2 = 0;
              iVar2 < *(int *)(*(int *)(*(int *)(*(int *)(param_5 + 0x534) + 0x4c) + iVar3 * 0x4c +
                                       0xc) + 4); iVar2 = iVar2 + 1) {
            fVar8 = (*(float *)(param_5 + 0x558) + 1.0) *
                    (float)*(byte *)(*(int *)(*(int *)(param_5 + 0x56c) + iVar3 * 0x410 + 0x400) +
                                     iVar2 * 4 + 2);
            if (fVar8 < 2.1474836e+09) {
              uVar7 = (undefined1)(int)fVar8;
            }
            else {
              uVar7 = (undefined1)(int)(fVar8 - 2.1474836e+09);
            }
            *(undefined1 *)(*(int *)(param_5 + 0x56c) + iVar3 * 0x410 + iVar2 * 4 + 2) = uVar7;
          }
          **(int **)(*(int *)(*(int *)(param_5 + 0x534) + 0x4c) + iVar3 * 0x4c + 0xc) =
               *(int *)(param_5 + 0x56c) + iVar3 * 0x410;
          *(int *)(*(int *)(*(int *)(*(int *)(param_5 + 0x534) + 0x4c) + iVar3 * 0x4c) + 0xf4) =
               *(int *)(param_5 + 0x56c) + iVar3 * 0x410;
          *(int *)(*(int *)(*(int *)(*(int *)(param_5 + 0x534) + 0x4c) + iVar3 * 0x4c + 4) + 0xf4) =
               *(int *)(param_5 + 0x56c) + iVar3 * 0x410;
        }
      }
    }
    if (param_4 != 0.0) {
      if (*(int *)(param_5 + 0x560) != 0) {
        for (iVar3 = 0; iVar3 < (int)(uint)*(ushort *)(*(int *)(param_5 + 100) + 4);
            iVar3 = iVar3 + 1) {
          for (iVar2 = 0;
              iVar2 < *(int *)(*(int *)(*(int *)(param_5 + 0x4c) + iVar3 * 0x4c + 0xc) + 4);
              iVar2 = iVar2 + 1) {
            uVar1 = ((uint)*(byte *)(*(int *)(param_5 + 0x560) + iVar3 * 0x410 + iVar2 * 4 + 2) +
                    (uint)*(byte *)(*(int *)(param_5 + 0x560) + iVar3 * 0x410 + iVar2 * 4) +
                    (uint)*(byte *)(*(int *)(param_5 + 0x560) + iVar3 * 0x410 + iVar2 * 4 + 1)) / 3;
            pbVar5 = (byte *)(*(int *)(param_5 + 0x560) + iVar3 * 0x410 + iVar2 * 4);
            fVar8 = (float)*pbVar5 +
                    param_4 * (float)(int)(uVar1 - *(byte *)(*(int *)(param_5 + 0x560) +
                                                             iVar3 * 0x410 + iVar2 * 4));
            if (fVar8 < 2.1474836e+09) {
              bVar4 = (byte)(int)fVar8;
            }
            else {
              bVar4 = (byte)(int)(fVar8 - 2.1474836e+09);
            }
            *pbVar5 = bVar4;
            iVar6 = *(int *)(param_5 + 0x560) + iVar3 * 0x410 + iVar2 * 4;
            fVar8 = (float)*(byte *)(iVar6 + 1) +
                    param_4 * (float)(int)(uVar1 - *(byte *)(*(int *)(param_5 + 0x560) +
                                                             iVar3 * 0x410 + iVar2 * 4 + 1));
            if (fVar8 < 2.1474836e+09) {
              uVar7 = (undefined1)(int)fVar8;
            }
            else {
              uVar7 = (undefined1)(int)(fVar8 - 2.1474836e+09);
            }
            *(undefined1 *)(iVar6 + 1) = uVar7;
            iVar6 = *(int *)(param_5 + 0x560) + iVar3 * 0x410 + iVar2 * 4;
            fVar8 = (float)*(byte *)(iVar6 + 2) +
                    param_4 * (float)(int)(uVar1 - *(byte *)(*(int *)(param_5 + 0x560) +
                                                             iVar3 * 0x410 + iVar2 * 4 + 2));
            if (fVar8 < 2.1474836e+09) {
              uVar7 = (undefined1)(int)fVar8;
            }
            else {
              uVar7 = (undefined1)(int)(fVar8 - 2.1474836e+09);
            }
            *(undefined1 *)(iVar6 + 2) = uVar7;
          }
        }
      }
      if (*(int *)(param_5 + 0x568) != 0) {
        for (iVar3 = 0;
            iVar3 < (int)(uint)*(ushort *)(*(int *)(*(int *)(param_5 + 0x530) + 100) + 4);
            iVar3 = iVar3 + 1) {
          for (iVar2 = 0;
              iVar2 < *(int *)(*(int *)(*(int *)(*(int *)(param_5 + 0x530) + 0x4c) + iVar3 * 0x4c +
                                       0xc) + 4); iVar2 = iVar2 + 1) {
            uVar1 = ((uint)*(byte *)(*(int *)(param_5 + 0x568) + iVar3 * 0x410 + iVar2 * 4 + 2) +
                    (uint)*(byte *)(*(int *)(param_5 + 0x568) + iVar3 * 0x410 + iVar2 * 4) +
                    (uint)*(byte *)(*(int *)(param_5 + 0x568) + iVar3 * 0x410 + iVar2 * 4 + 1)) / 3;
            pbVar5 = (byte *)(*(int *)(param_5 + 0x568) + iVar3 * 0x410 + iVar2 * 4);
            fVar8 = (float)*pbVar5 +
                    param_4 * (float)(int)(uVar1 - *(byte *)(*(int *)(param_5 + 0x568) +
                                                             iVar3 * 0x410 + iVar2 * 4));
            if (fVar8 < 2.1474836e+09) {
              bVar4 = (byte)(int)fVar8;
            }
            else {
              bVar4 = (byte)(int)(fVar8 - 2.1474836e+09);
            }
            *pbVar5 = bVar4;
            iVar6 = *(int *)(param_5 + 0x568) + iVar3 * 0x410 + iVar2 * 4;
            fVar8 = (float)*(byte *)(iVar6 + 1) +
                    param_4 * (float)(int)(uVar1 - *(byte *)(*(int *)(param_5 + 0x568) +
                                                             iVar3 * 0x410 + iVar2 * 4 + 1));
            if (fVar8 < 2.1474836e+09) {
              uVar7 = (undefined1)(int)fVar8;
            }
            else {
              uVar7 = (undefined1)(int)(fVar8 - 2.1474836e+09);
            }
            *(undefined1 *)(iVar6 + 1) = uVar7;
            iVar6 = *(int *)(param_5 + 0x568) + iVar3 * 0x410 + iVar2 * 4;
            fVar8 = (float)*(byte *)(iVar6 + 2) +
                    param_4 * (float)(int)(uVar1 - *(byte *)(*(int *)(param_5 + 0x568) +
                                                             iVar3 * 0x410 + iVar2 * 4 + 2));
            if (fVar8 < 2.1474836e+09) {
              uVar7 = (undefined1)(int)fVar8;
            }
            else {
              uVar7 = (undefined1)(int)(fVar8 - 2.1474836e+09);
            }
            *(undefined1 *)(iVar6 + 2) = uVar7;
          }
        }
      }
      if (*(int *)(param_5 + 0x564) != 0) {
        for (iVar3 = 0;
            iVar3 < (int)(uint)*(ushort *)(*(int *)(*(int *)(param_5 + 0x52c) + 100) + 4);
            iVar3 = iVar3 + 1) {
          for (iVar2 = 0;
              iVar2 < *(int *)(*(int *)(*(int *)(*(int *)(param_5 + 0x52c) + 0x4c) + iVar3 * 0x4c +
                                       0xc) + 4); iVar2 = iVar2 + 1) {
            uVar1 = ((uint)*(byte *)(*(int *)(param_5 + 0x564) + iVar3 * 0x410 + iVar2 * 4 + 2) +
                    (uint)*(byte *)(*(int *)(param_5 + 0x564) + iVar3 * 0x410 + iVar2 * 4) +
                    (uint)*(byte *)(*(int *)(param_5 + 0x564) + iVar3 * 0x410 + iVar2 * 4 + 1)) / 3;
            pbVar5 = (byte *)(*(int *)(param_5 + 0x564) + iVar3 * 0x410 + iVar2 * 4);
            fVar8 = (float)*pbVar5 +
                    param_4 * (float)(int)(uVar1 - *(byte *)(*(int *)(param_5 + 0x564) +
                                                             iVar3 * 0x410 + iVar2 * 4));
            if (fVar8 < 2.1474836e+09) {
              bVar4 = (byte)(int)fVar8;
            }
            else {
              bVar4 = (byte)(int)(fVar8 - 2.1474836e+09);
            }
            *pbVar5 = bVar4;
            iVar6 = *(int *)(param_5 + 0x564) + iVar3 * 0x410 + iVar2 * 4;
            fVar8 = (float)*(byte *)(iVar6 + 1) +
                    param_4 * (float)(int)(uVar1 - *(byte *)(*(int *)(param_5 + 0x564) +
                                                             iVar3 * 0x410 + iVar2 * 4 + 1));
            if (fVar8 < 2.1474836e+09) {
              uVar7 = (undefined1)(int)fVar8;
            }
            else {
              uVar7 = (undefined1)(int)(fVar8 - 2.1474836e+09);
            }
            *(undefined1 *)(iVar6 + 1) = uVar7;
            iVar6 = *(int *)(param_5 + 0x564) + iVar3 * 0x410 + iVar2 * 4;
            fVar8 = (float)*(byte *)(iVar6 + 2) +
                    param_4 * (float)(int)(uVar1 - *(byte *)(*(int *)(param_5 + 0x564) +
                                                             iVar3 * 0x410 + iVar2 * 4 + 2));
            if (fVar8 < 2.1474836e+09) {
              uVar7 = (undefined1)(int)fVar8;
            }
            else {
              uVar7 = (undefined1)(int)(fVar8 - 2.1474836e+09);
            }
            *(undefined1 *)(iVar6 + 2) = uVar7;
          }
        }
      }
      if (*(int *)(param_5 + 0x56c) != 0) {
        for (iVar3 = 0;
            iVar3 < (int)(uint)*(ushort *)(*(int *)(*(int *)(param_5 + 0x534) + 100) + 4);
            iVar3 = iVar3 + 1) {
          for (iVar2 = 0;
              iVar2 < *(int *)(*(int *)(*(int *)(*(int *)(param_5 + 0x534) + 0x4c) + iVar3 * 0x4c +
                                       0xc) + 4); iVar2 = iVar2 + 1) {
            uVar1 = ((uint)*(byte *)(*(int *)(param_5 + 0x56c) + iVar3 * 0x410 + iVar2 * 4 + 2) +
                    (uint)*(byte *)(*(int *)(param_5 + 0x56c) + iVar3 * 0x410 + iVar2 * 4) +
                    (uint)*(byte *)(*(int *)(param_5 + 0x56c) + iVar3 * 0x410 + iVar2 * 4 + 1)) / 3;
            pbVar5 = (byte *)(*(int *)(param_5 + 0x56c) + iVar3 * 0x410 + iVar2 * 4);
            fVar8 = (float)*pbVar5 +
                    param_4 * (float)(int)(uVar1 - *(byte *)(*(int *)(param_5 + 0x56c) +
                                                             iVar3 * 0x410 + iVar2 * 4));
            if (fVar8 < 2.1474836e+09) {
              bVar4 = (byte)(int)fVar8;
            }
            else {
              bVar4 = (byte)(int)(fVar8 - 2.1474836e+09);
            }
            *pbVar5 = bVar4;
            iVar6 = *(int *)(param_5 + 0x56c) + iVar3 * 0x410 + iVar2 * 4;
            fVar8 = (float)*(byte *)(iVar6 + 1) +
                    param_4 * (float)(int)(uVar1 - *(byte *)(*(int *)(param_5 + 0x56c) +
                                                             iVar3 * 0x410 + iVar2 * 4 + 1));
            if (fVar8 < 2.1474836e+09) {
              uVar7 = (undefined1)(int)fVar8;
            }
            else {
              uVar7 = (undefined1)(int)(fVar8 - 2.1474836e+09);
            }
            *(undefined1 *)(iVar6 + 1) = uVar7;
            iVar6 = *(int *)(param_5 + 0x56c) + iVar3 * 0x410 + iVar2 * 4;
            fVar8 = (float)*(byte *)(iVar6 + 2) +
                    param_4 * (float)(int)(uVar1 - *(byte *)(*(int *)(param_5 + 0x56c) +
                                                             iVar3 * 0x410 + iVar2 * 4 + 2));
            if (fVar8 < 2.1474836e+09) {
              uVar7 = (undefined1)(int)fVar8;
            }
            else {
              uVar7 = (undefined1)(int)(fVar8 - 2.1474836e+09);
            }
            *(undefined1 *)(iVar6 + 2) = uVar7;
          }
        }
      }
    }
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00559160  SetCtrlMode__8BtlModelFbb
 * C++: BtlModel::SetCtrlMode(bool, bool)
 * size: 0xe8 bytes
 * --------------------------------------------------------------------------- */
void SetCtrlMode__8BtlModelFbb(int param_1,char param_2,char param_3)

{
  if (param_2 == '\x01') {
    *(byte *)(param_1 + 0x4b1) = *(byte *)(param_1 + 0x4b1) & 0xfe | 1;
    *(undefined2 *)(param_1 + 0x4f0) = 0;
    *(undefined2 *)(param_1 + 0x4f2) = 0;
  }
  else {
    *(byte *)(param_1 + 0x4b1) = *(byte *)(param_1 + 0x4b1) & 0xfe;
    if (param_3 == '\x01') {
      SetNextBtlMotion__8BtlModelFif(0x3f800000,param_1,1);
    }
    else {
      SetBtlMotion__8BtlModelFif(0x3f800000,param_1,1);
    }
    *(undefined2 *)(param_1 + 0x4f0) = 1;
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00559250  SetOpticalCamouflage__8BtlModelFii
 * C++: BtlModel::SetOpticalCamouflage(int, int)
 * size: 0x7f8 bytes
 * --------------------------------------------------------------------------- */
void SetOpticalCamouflage__8BtlModelFii(int param_1,uint param_2,int param_3)

{
  int iVar1;
  ulong uVar2;
  int iVar3;
  
  if (param_2 == 0) {
    *(byte *)(param_1 + 0x4b1) = *(byte *)(param_1 + 0x4b1) & 0xf3;
    if ((*(byte *)(param_1 + 0x4b0) & 1) != 0) {
      for (iVar3 = 0; iVar3 < (int)(uint)*(ushort *)(*(int *)(param_1 + 0x5c) + 4);
          iVar3 = iVar3 + 1) {
        iVar1 = *(int *)(*(int *)(param_1 + 0x48) + iVar3 * 4);
        (**(code **)(*(int *)(iVar1 + 0x370) + 0x1c))(iVar1,0);
        *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x48) + iVar3 * 4) + 800) = 0x43000000;
        iVar1 = *(int *)(*(int *)(param_1 + 0x48) + iVar3 * 4);
        (**(code **)(*(int *)(iVar1 + 0x370) + 0x24))(iVar1,0x80);
        setAtomicAlpha__6AtomicFUc(*(undefined4 *)(*(int *)(param_1 + 0x48) + iVar3 * 4),0x80);
      }
    }
    if (*(int *)(param_1 + 0x52c) != 0) {
      for (iVar3 = 0; iVar3 < (int)(uint)*(ushort *)(*(int *)(*(int *)(param_1 + 0x52c) + 0x5c) + 4)
          ; iVar3 = iVar3 + 1) {
        iVar1 = *(int *)(*(int *)(*(int *)(param_1 + 0x52c) + 0x48) + iVar3 * 4);
        (**(code **)(*(int *)(iVar1 + 0x370) + 0x1c))(iVar1,0);
        *(undefined4 *)(*(int *)(*(int *)(*(int *)(param_1 + 0x52c) + 0x48) + iVar3 * 4) + 800) =
             0x43000000;
        iVar1 = *(int *)(*(int *)(*(int *)(param_1 + 0x52c) + 0x48) + iVar3 * 4);
        (**(code **)(*(int *)(iVar1 + 0x370) + 0x24))(iVar1,0x80);
        setAtomicAlpha__6AtomicFUc(*(undefined4 *)(*(int *)(*(int *)(param_1 + 0x52c) + 0x48) + iVar3 * 4),0x80
                       );
      }
    }
    if (*(int *)(param_1 + 0x530) != 0) {
      for (iVar3 = 0; iVar3 < (int)(uint)*(ushort *)(*(int *)(*(int *)(param_1 + 0x530) + 0x5c) + 4)
          ; iVar3 = iVar3 + 1) {
        iVar1 = *(int *)(*(int *)(*(int *)(param_1 + 0x530) + 0x48) + iVar3 * 4);
        (**(code **)(*(int *)(iVar1 + 0x370) + 0x1c))(iVar1,0);
        *(undefined4 *)(*(int *)(*(int *)(*(int *)(param_1 + 0x530) + 0x48) + iVar3 * 4) + 800) =
             0x43000000;
        iVar1 = *(int *)(*(int *)(*(int *)(param_1 + 0x530) + 0x48) + iVar3 * 4);
        (**(code **)(*(int *)(iVar1 + 0x370) + 0x24))(iVar1,0x80);
        setAtomicAlpha__6AtomicFUc(*(undefined4 *)(*(int *)(*(int *)(param_1 + 0x530) + 0x48) + iVar3 * 4),0x80
                       );
      }
    }
    if (*(int *)(param_1 + 0x534) != 0) {
      for (iVar3 = 0; iVar3 < (int)(uint)*(ushort *)(*(int *)(*(int *)(param_1 + 0x534) + 0x5c) + 4)
          ; iVar3 = iVar3 + 1) {
        iVar1 = *(int *)(*(int *)(*(int *)(param_1 + 0x534) + 0x48) + iVar3 * 4);
        (**(code **)(*(int *)(iVar1 + 0x370) + 0x1c))(iVar1,0);
        *(undefined4 *)(*(int *)(*(int *)(*(int *)(param_1 + 0x534) + 0x48) + iVar3 * 4) + 800) =
             0x43000000;
        iVar1 = *(int *)(*(int *)(*(int *)(param_1 + 0x534) + 0x48) + iVar3 * 4);
        (**(code **)(*(int *)(iVar1 + 0x370) + 0x24))(iVar1,0x80);
        setAtomicAlpha__6AtomicFUc(*(undefined4 *)(*(int *)(*(int *)(param_1 + 0x534) + 0x48) + iVar3 * 4),0x80
                       );
      }
    }
    SetBtlModelAlpha__8BtlModelFiii
              (param_1,(int)(*(float *)(param_1 + 0x4e4) * *(float *)(param_1 + 0x4ec) * 128.0),0x80
               ,0x80);
  }
  else {
    *(byte *)(param_1 + 0x4b1) = *(byte *)(param_1 + 0x4b1) & 0xf3 | (byte)((param_2 & 3) << 2);
    if ((*(byte *)(param_1 + 0x4b0) & 1) != 0) {
      for (iVar3 = 0; iVar3 < (int)(uint)*(ushort *)(*(int *)(param_1 + 0x5c) + 4);
          iVar3 = iVar3 + 1) {
        iVar1 = *(int *)(*(int *)(param_1 + 0x48) + iVar3 * 4);
        (**(code **)(*(int *)(iVar1 + 0x370) + 0x1c))(iVar1,3);
        *(float *)(*(int *)(*(int *)(param_1 + 0x48) + iVar3 * 4) + 800) = (float)param_3;
      }
    }
    if (*(int *)(param_1 + 0x52c) != 0) {
      for (iVar3 = 0; iVar3 < (int)(uint)*(ushort *)(*(int *)(*(int *)(param_1 + 0x52c) + 0x5c) + 4)
          ; iVar3 = iVar3 + 1) {
        iVar1 = *(int *)(*(int *)(*(int *)(param_1 + 0x52c) + 0x48) + iVar3 * 4);
        (**(code **)(*(int *)(iVar1 + 0x370) + 0x1c))(iVar1,3);
        *(float *)(*(int *)(*(int *)(*(int *)(param_1 + 0x52c) + 0x48) + iVar3 * 4) + 800) =
             (float)param_3;
      }
    }
    if (*(int *)(param_1 + 0x530) != 0) {
      for (iVar3 = 0; iVar3 < (int)(uint)*(ushort *)(*(int *)(*(int *)(param_1 + 0x530) + 0x5c) + 4)
          ; iVar3 = iVar3 + 1) {
        iVar1 = *(int *)(*(int *)(*(int *)(param_1 + 0x530) + 0x48) + iVar3 * 4);
        (**(code **)(*(int *)(iVar1 + 0x370) + 0x1c))(iVar1,3);
        *(float *)(*(int *)(*(int *)(*(int *)(param_1 + 0x530) + 0x48) + iVar3 * 4) + 800) =
             (float)param_3;
      }
    }
    if (*(int *)(param_1 + 0x534) != 0) {
      for (iVar3 = 0; iVar3 < (int)(uint)*(ushort *)(*(int *)(*(int *)(param_1 + 0x534) + 0x5c) + 4)
          ; iVar3 = iVar3 + 1) {
        iVar1 = *(int *)(*(int *)(*(int *)(param_1 + 0x534) + 0x48) + iVar3 * 4);
        (**(code **)(*(int *)(iVar1 + 0x370) + 0x1c))(iVar1,3);
        *(float *)(*(int *)(*(int *)(*(int *)(param_1 + 0x534) + 0x48) + iVar3 * 4) + 800) =
             (float)param_3;
      }
    }
    iVar3 = (int)(*(float *)(param_1 + 0x4e4) * *(float *)(param_1 + 0x4ec) * 128.0);
    uVar2 = ((ulong)*(byte *)(param_1 + 0x4b1) & 0xf) >> 2;
    if (uVar2 == 3) {
      SetBtlModelAlpha__8BtlModelFiii(param_1,iVar3,iVar3,1);
    }
    else if (uVar2 == 2) {
      SetBtlModelAlpha__8BtlModelFiii(param_1,iVar3,0x80,0x80);
    }
    else if (uVar2 == 1) {
      SetBtlModelAlpha__8BtlModelFiii(param_1,iVar3,iVar3,0x80);
    }
    else if (uVar2 == 0) {
      SetBtlModelAlpha__8BtlModelFiii(param_1,iVar3,0x80,0x80);
    }
    *(undefined4 *)(param_1 + 0x548) = 0;
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00559a50  SetBtlModelAlpha__8BtlModelFiii
 * C++: BtlModel::SetBtlModelAlpha(int, int, int)
 * size: 0xbb8 bytes
 * --------------------------------------------------------------------------- */
void SetBtlModelAlpha__8BtlModelFiii(int param_1,int param_2,undefined4 param_3,undefined1 param_4)

{
  int iVar1;
  int iVar2;
  
  iVar1 = param_2;
  if (0x6f < param_2) {
    iVar1 = 0x70;
  }
  if ((param_2 != *(int *)(param_1 + 0x28c)) && ((*(byte *)(param_1 + 0x4b0) & 1) != 0)) {
    *(int *)(param_1 + 0x28c) = param_2;
    *(int *)(param_1 + 0x29c) = param_2;
    if ((long)((ulong)*(byte *)(param_1 + 0x4b1) << 0x3a) < 0) {
      for (iVar2 = 0; iVar2 < (int)(uint)*(ushort *)(*(int *)(param_1 + 100) + 4); iVar2 = iVar2 + 1
          ) {
        changeGSTest__7TextureFiiiiiiii(*(int *)(param_1 + 0x4c) + iVar2 * 0x4c,1,0,0,3,0,0,1);
      }
    }
    else if ((param_2 == 0x80) || (((ulong)*(byte *)(param_1 + 0x4b1) & 0xf) >> 2 != 0)) {
      for (iVar2 = 0; iVar2 < (int)(uint)*(ushort *)(*(int *)(param_1 + 100) + 4); iVar2 = iVar2 + 1
          ) {
        changeGSTest__7TextureFiiiiiiii(*(int *)(param_1 + 0x4c) + iVar2 * 0x4c,1,5,0x70,3,0,0,1);
      }
    }
    else {
      for (iVar2 = 0; iVar2 < (int)(uint)*(ushort *)(*(int *)(param_1 + 100) + 4); iVar2 = iVar2 + 1
          ) {
        changeGSTest__7TextureFiiiiiiii(*(int *)(param_1 + 0x4c) + iVar2 * 0x4c,0,5,iVar1,3,0,0,1);
      }
    }
  }
  if ((*(int *)(param_1 + 0x52c) != 0) && (param_2 != *(int *)(*(int *)(param_1 + 0x52c) + 0x28c)))
  {
    *(int *)(*(int *)(param_1 + 0x52c) + 0x28c) = param_2;
    *(int *)(*(int *)(param_1 + 0x52c) + 0x29c) = param_2;
    if ((long)((ulong)*(byte *)(param_1 + 0x4b1) << 0x3a) < 0) {
      for (iVar2 = 0; iVar2 < (int)(uint)*(ushort *)(*(int *)(*(int *)(param_1 + 0x52c) + 100) + 4);
          iVar2 = iVar2 + 1) {
        changeGSTest__7TextureFiiiiiiii(*(int *)(*(int *)(param_1 + 0x52c) + 0x4c) + iVar2 * 0x4c,1,0,0,3,0,0,1);
      }
    }
    else if ((param_2 == 0x80) || (((ulong)*(byte *)(param_1 + 0x4b1) & 0xf) >> 2 != 0)) {
      for (iVar2 = 0; iVar2 < (int)(uint)*(ushort *)(*(int *)(*(int *)(param_1 + 0x52c) + 100) + 4);
          iVar2 = iVar2 + 1) {
        changeGSTest__7TextureFiiiiiiii(*(int *)(*(int *)(param_1 + 0x52c) + 0x4c) + iVar2 * 0x4c,1,5,0x70,3,0,0,1);
      }
    }
    else {
      for (iVar2 = 0; iVar2 < (int)(uint)*(ushort *)(*(int *)(*(int *)(param_1 + 0x52c) + 100) + 4);
          iVar2 = iVar2 + 1) {
        changeGSTest__7TextureFiiiiiiii(*(int *)(*(int *)(param_1 + 0x52c) + 0x4c) + iVar2 * 0x4c,0,5,iVar1,3,0,0,1)
        ;
      }
    }
  }
  if ((*(int *)(param_1 + 0x530) != 0) && (param_2 != *(int *)(*(int *)(param_1 + 0x530) + 0x28c)))
  {
    *(int *)(*(int *)(param_1 + 0x530) + 0x28c) = param_2;
    *(int *)(*(int *)(param_1 + 0x530) + 0x29c) = param_2;
    if ((long)((ulong)*(byte *)(param_1 + 0x4b1) << 0x3a) < 0) {
      for (iVar2 = 0; iVar2 < (int)(uint)*(ushort *)(*(int *)(*(int *)(param_1 + 0x530) + 100) + 4);
          iVar2 = iVar2 + 1) {
        changeGSTest__7TextureFiiiiiiii(*(int *)(*(int *)(param_1 + 0x530) + 0x4c) + iVar2 * 0x4c,1,0,0,3,0,0,1);
      }
    }
    else if ((param_2 == 0x80) || (((ulong)*(byte *)(param_1 + 0x4b1) & 0xf) >> 2 != 0)) {
      for (iVar2 = 0; iVar2 < (int)(uint)*(ushort *)(*(int *)(*(int *)(param_1 + 0x530) + 100) + 4);
          iVar2 = iVar2 + 1) {
        changeGSTest__7TextureFiiiiiiii(*(int *)(*(int *)(param_1 + 0x530) + 0x4c) + iVar2 * 0x4c,1,5,0x70,3,0,0,1);
      }
    }
    else {
      for (iVar2 = 0; iVar2 < (int)(uint)*(ushort *)(*(int *)(*(int *)(param_1 + 0x530) + 100) + 4);
          iVar2 = iVar2 + 1) {
        changeGSTest__7TextureFiiiiiiii(*(int *)(*(int *)(param_1 + 0x530) + 0x4c) + iVar2 * 0x4c,0,5,iVar1,3,0,0,1)
        ;
      }
    }
  }
  if ((*(int *)(param_1 + 0x534) != 0) && (param_2 != *(int *)(*(int *)(param_1 + 0x534) + 0x28c)))
  {
    *(int *)(*(int *)(param_1 + 0x534) + 0x28c) = param_2;
    *(int *)(*(int *)(param_1 + 0x534) + 0x29c) = param_2;
    if ((long)((ulong)*(byte *)(param_1 + 0x4b1) << 0x3a) < 0) {
      for (iVar1 = 0; iVar1 < (int)(uint)*(ushort *)(*(int *)(*(int *)(param_1 + 0x534) + 100) + 4);
          iVar1 = iVar1 + 1) {
        changeGSTest__7TextureFiiiiiiii(*(int *)(*(int *)(param_1 + 0x534) + 0x4c) + iVar1 * 0x4c,1,0,0,3,0,0,1);
      }
    }
    else if ((param_2 == 0x80) || (((ulong)*(byte *)(param_1 + 0x4b1) & 0xf) >> 2 != 0)) {
      for (iVar1 = 0; iVar1 < (int)(uint)*(ushort *)(*(int *)(*(int *)(param_1 + 0x534) + 100) + 4);
          iVar1 = iVar1 + 1) {
        changeGSTest__7TextureFiiiiiiii(*(int *)(*(int *)(param_1 + 0x534) + 0x4c) + iVar1 * 0x4c,1,5,0x70,3,0,0,1);
      }
    }
    else {
      for (iVar2 = 0; iVar2 < (int)(uint)*(ushort *)(*(int *)(*(int *)(param_1 + 0x534) + 100) + 4);
          iVar2 = iVar2 + 1) {
        changeGSTest__7TextureFiiiiiiii(*(int *)(*(int *)(param_1 + 0x534) + 0x4c) + iVar2 * 0x4c,0,5,iVar1,3,0,0,1)
        ;
      }
    }
  }
  if (((ulong)*(byte *)(param_1 + 0x4b1) & 0xf) >> 2 != 0) {
    if ((*(byte *)(param_1 + 0x4b0) & 1) != 0) {
      for (iVar1 = 0; iVar1 < (int)(uint)*(ushort *)(*(int *)(param_1 + 0x5c) + 4);
          iVar1 = iVar1 + 1) {
        iVar2 = *(int *)(*(int *)(param_1 + 0x48) + iVar1 * 4);
        (**(code **)(*(int *)(iVar2 + 0x370) + 0x24))(iVar2,param_3);
        setAtomicAlpha__6AtomicFUc(*(undefined4 *)(*(int *)(param_1 + 0x48) + iVar1 * 4),param_4);
      }
    }
    if (*(int *)(param_1 + 0x52c) != 0) {
      for (iVar1 = 0; iVar1 < (int)(uint)*(ushort *)(*(int *)(*(int *)(param_1 + 0x52c) + 0x5c) + 4)
          ; iVar1 = iVar1 + 1) {
        iVar2 = *(int *)(*(int *)(*(int *)(param_1 + 0x52c) + 0x48) + iVar1 * 4);
        (**(code **)(*(int *)(iVar2 + 0x370) + 0x24))(iVar2,param_3);
        setAtomicAlpha__6AtomicFUc(*(undefined4 *)(*(int *)(*(int *)(param_1 + 0x52c) + 0x48) + iVar1 * 4),
                        param_4);
      }
    }
    if (*(int *)(param_1 + 0x530) != 0) {
      for (iVar1 = 0; iVar1 < (int)(uint)*(ushort *)(*(int *)(*(int *)(param_1 + 0x530) + 0x5c) + 4)
          ; iVar1 = iVar1 + 1) {
        iVar2 = *(int *)(*(int *)(*(int *)(param_1 + 0x530) + 0x48) + iVar1 * 4);
        (**(code **)(*(int *)(iVar2 + 0x370) + 0x24))(iVar2,param_3);
        setAtomicAlpha__6AtomicFUc(*(undefined4 *)(*(int *)(*(int *)(param_1 + 0x530) + 0x48) + iVar1 * 4),
                        param_4);
      }
    }
    if (*(int *)(param_1 + 0x534) != 0) {
      for (iVar1 = 0; iVar1 < (int)(uint)*(ushort *)(*(int *)(*(int *)(param_1 + 0x534) + 0x5c) + 4)
          ; iVar1 = iVar1 + 1) {
        iVar2 = *(int *)(*(int *)(*(int *)(param_1 + 0x534) + 0x48) + iVar1 * 4);
        (**(code **)(*(int *)(iVar2 + 0x370) + 0x24))(iVar2,param_3);
        setAtomicAlpha__6AtomicFUc(*(undefined4 *)(*(int *)(*(int *)(param_1 + 0x534) + 0x48) + iVar1 * 4),
                        param_4);
      }
    }
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0055a610  SetZWriteOff__8BtlModelFv
 * C++: BtlModel::SetZWriteOff()
 * size: 0x264 bytes
 * --------------------------------------------------------------------------- */
void SetZWriteOff__8BtlModelFv(int param_1)

{
  int iVar1;
  
  *(byte *)(param_1 + 0x4b1) = *(byte *)(param_1 + 0x4b1) & 0xdf | 0x20;
  if ((*(byte *)(param_1 + 0x4b0) & 1) != 0) {
    for (iVar1 = 0; iVar1 < (int)(uint)*(ushort *)(*(int *)(param_1 + 100) + 4); iVar1 = iVar1 + 1)
    {
      changeGSAlpha__7TextureFiiiii(*(int *)(param_1 + 0x4c) + iVar1 * 0x4c,0,2,0,1,0);
    }
  }
  if (*(int *)(param_1 + 0x52c) != 0) {
    for (iVar1 = 0; iVar1 < (int)(uint)*(ushort *)(*(int *)(*(int *)(param_1 + 0x52c) + 100) + 4);
        iVar1 = iVar1 + 1) {
      changeGSAlpha__7TextureFiiiii(*(int *)(*(int *)(param_1 + 0x52c) + 0x4c) + iVar1 * 0x4c,0,2,0,1,0);
    }
  }
  if (*(int *)(param_1 + 0x530) != 0) {
    for (iVar1 = 0; iVar1 < (int)(uint)*(ushort *)(*(int *)(*(int *)(param_1 + 0x530) + 100) + 4);
        iVar1 = iVar1 + 1) {
      changeGSAlpha__7TextureFiiiii(*(int *)(*(int *)(param_1 + 0x530) + 0x4c) + iVar1 * 0x4c,0,2,0,1,0);
    }
  }
  if (*(int *)(param_1 + 0x534) != 0) {
    for (iVar1 = 0; iVar1 < (int)(uint)*(ushort *)(*(int *)(*(int *)(param_1 + 0x534) + 100) + 4);
        iVar1 = iVar1 + 1) {
      changeGSAlpha__7TextureFiiiii(*(int *)(*(int *)(param_1 + 0x534) + 0x4c) + iVar1 * 0x4c,0,2,0,1,0);
    }
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0055a880  AddModelEffect__8BtlModelFiiPc
 * C++: BtlModel::AddModelEffect(int, int, char *)
 * size: 0x6dc bytes
 * --------------------------------------------------------------------------- */
void AddModelEffect__8BtlModelFiiPc(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = 0;
  if (((((param_2 == 0x211) || (param_2 == 0x210)) || (param_2 == 0x20f)) ||
      ((param_2 == 0x20e || (param_2 == 0x20d)))) || (param_2 == 0x20c)) {
    while ((iVar1 < 4 && (-1 < *(int *)(param_1 + iVar1 * 0x10 + 0x574)))) {
      iVar1 = iVar1 + 1;
    }
    *(undefined1 *)(param_1 + iVar1 * 0x10 + 0x570) = 7;
    *(undefined4 *)(param_1 + iVar1 * 0x10 + 0x574) = param_3;
    *(undefined4 *)(param_1 + iVar1 * 0x10 + 0x578) = 3;
    *(undefined4 *)(param_1 + iVar1 * 0x10 + 0x57c) = param_4;
    createMF__15ModelEffManagerFQ215ModelEffManager4MENoiP5ModeliPc(7,param_3,param_1,3,param_4);
    *(byte *)(param_1 + 0x4b1) = *(byte *)(param_1 + 0x4b1) & 0xef | 0x10;
    changeAlpha__15ModelEffManagerFP5Modelf(0,param_1);
  }
  else if ((param_2 == 0x1f0) || (param_2 == 0x1dd)) {
    while ((iVar1 < 4 && (-1 < *(int *)(param_1 + iVar1 * 0x10 + 0x574)))) {
      iVar1 = iVar1 + 1;
    }
    *(undefined1 *)(param_1 + iVar1 * 0x10 + 0x570) = 8;
    *(undefined4 *)(param_1 + iVar1 * 0x10 + 0x574) = param_3;
    *(undefined4 *)(param_1 + iVar1 * 0x10 + 0x578) = 9;
    *(undefined4 *)(param_1 + iVar1 * 0x10 + 0x57c) = param_4;
    createMF__15ModelEffManagerFQ215ModelEffManager4MENoiP5ModeliPc(8,param_3,param_1,9,param_4);
    *(byte *)(param_1 + 0x4b1) = *(byte *)(param_1 + 0x4b1) & 0xef | 0x10;
    changeAlpha__15ModelEffManagerFP5Modelf(0,param_1);
  }
  else if (param_2 == 0x1b6) {
    while ((iVar1 < 4 && (-1 < *(int *)(param_1 + iVar1 * 0x10 + 0x574)))) {
      iVar1 = iVar1 + 1;
    }
    *(undefined1 *)(param_1 + iVar1 * 0x10 + 0x570) = 4;
    *(undefined4 *)(param_1 + iVar1 * 0x10 + 0x574) = param_3;
    *(undefined4 *)(param_1 + iVar1 * 0x10 + 0x578) = 9;
    *(undefined4 *)(param_1 + iVar1 * 0x10 + 0x57c) = param_4;
    createMF__15ModelEffManagerFQ215ModelEffManager4MENoiP5ModeliPc(4,param_3,param_1,9,param_4);
    *(byte *)(param_1 + 0x4b1) = *(byte *)(param_1 + 0x4b1) & 0xef | 0x10;
    changeAlpha__15ModelEffManagerFP5Modelf(0,param_1);
  }
  else if (param_2 == 0x1b5) {
    while ((iVar1 < 4 && (-1 < *(int *)(param_1 + iVar1 * 0x10 + 0x574)))) {
      iVar1 = iVar1 + 1;
    }
    *(undefined1 *)(param_1 + iVar1 * 0x10 + 0x570) = 3;
    *(undefined4 *)(param_1 + iVar1 * 0x10 + 0x574) = param_3;
    *(undefined4 *)(param_1 + iVar1 * 0x10 + 0x578) = 9;
    *(undefined4 *)(param_1 + iVar1 * 0x10 + 0x57c) = param_4;
    createMF__15ModelEffManagerFQ215ModelEffManager4MENoiP5ModeliPc(3,param_3,param_1,9,param_4);
    *(byte *)(param_1 + 0x4b1) = *(byte *)(param_1 + 0x4b1) & 0xef | 0x10;
    changeAlpha__15ModelEffManagerFP5Modelf(0,param_1);
  }
  else if ((param_2 == 0x1fb) || (param_2 == 0x1a6)) {
    while ((iVar1 < 4 && (-1 < *(int *)(param_1 + iVar1 * 0x10 + 0x574)))) {
      iVar1 = iVar1 + 1;
    }
    *(undefined1 *)(param_1 + iVar1 * 0x10 + 0x570) = 2;
    *(undefined4 *)(param_1 + iVar1 * 0x10 + 0x574) = param_3;
    *(undefined4 *)(param_1 + iVar1 * 0x10 + 0x578) = 9;
    *(undefined4 *)(param_1 + iVar1 * 0x10 + 0x57c) = param_4;
    createMF__15ModelEffManagerFQ215ModelEffManager4MENoiP5ModeliPc(2,param_3,param_1,9,param_4);
    *(byte *)(param_1 + 0x4b1) = *(byte *)(param_1 + 0x4b1) & 0xef | 0x10;
    changeAlpha__15ModelEffManagerFP5Modelf(0,param_1);
  }
  else if (param_2 == 0x19d) {
    while ((iVar1 < 4 && (-1 < *(int *)(param_1 + iVar1 * 0x10 + 0x574)))) {
      iVar1 = iVar1 + 1;
    }
    *(undefined1 *)(param_1 + iVar1 * 0x10 + 0x570) = 6;
    *(undefined4 *)(param_1 + iVar1 * 0x10 + 0x574) = param_3;
    *(undefined4 *)(param_1 + iVar1 * 0x10 + 0x578) = 9;
    *(undefined4 *)(param_1 + iVar1 * 0x10 + 0x57c) = param_4;
    createMF__15ModelEffManagerFQ215ModelEffManager4MENoiP5ModeliPc(6,param_3,param_1,9,param_4);
    *(byte *)(param_1 + 0x4b1) = *(byte *)(param_1 + 0x4b1) & 0xef | 0x10;
    changeAlpha__15ModelEffManagerFP5Modelf(0,param_1);
  }
  else if (param_2 == 0x19c) {
    while ((iVar1 < 4 && (-1 < *(int *)(param_1 + iVar1 * 0x10 + 0x574)))) {
      iVar1 = iVar1 + 1;
    }
    *(undefined1 *)(param_1 + iVar1 * 0x10 + 0x570) = 5;
    *(undefined4 *)(param_1 + iVar1 * 0x10 + 0x574) = param_3;
    *(undefined4 *)(param_1 + iVar1 * 0x10 + 0x578) = 9;
    *(undefined4 *)(param_1 + iVar1 * 0x10 + 0x57c) = param_4;
    createMF__15ModelEffManagerFQ215ModelEffManager4MENoiP5ModeliPc(5,param_3,param_1,9,param_4);
    *(byte *)(param_1 + 0x4b1) = *(byte *)(param_1 + 0x4b1) & 0xef | 0x10;
    changeAlpha__15ModelEffManagerFP5Modelf(0,param_1);
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0055af60  SetIdleCtrlFrame__8BtlModelFi7FVector
 * C++: BtlModel::SetIdleCtrlFrame(int, FVector)
 * size: 0x80 bytes
 * --------------------------------------------------------------------------- */
void SetIdleCtrlFrame__8BtlModelFi7FVector(int param_1,undefined4 param_2,undefined8 *param_3)

{
  undefined8 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  *(byte *)(param_1 + 0x4b1) = *(byte *)(param_1 + 0x4b1) & 0x7f;
  *(undefined4 *)(param_1 + 0x5b0) = param_2;
  uVar1 = *param_3;
  uVar2 = *(undefined4 *)(param_3 + 1);
  uVar3 = *(undefined4 *)((int)param_3 + 0xc);
  *(int *)(param_1 + 0x5d0) = (int)uVar1;
  *(int *)(param_1 + 0x5d4) = (int)((ulong)uVar1 >> 0x20);
  *(undefined4 *)(param_1 + 0x5d8) = uVar2;
  *(undefined4 *)(param_1 + 0x5dc) = uVar3;
  *(undefined4 *)(param_1 + 0x5c0) = 0;
  *(undefined4 *)(param_1 + 0x5c4) = 0;
  *(undefined4 *)(param_1 + 0x5c8) = 0;
  *(undefined4 *)(param_1 + 0x5cc) = 0x3f800000;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0055afe0  ReleaseWeapon__8BtlModelFi
 * C++: BtlModel::ReleaseWeapon(int)
 * size: 0x3b8 bytes
 * --------------------------------------------------------------------------- */
void ReleaseWeapon__8BtlModelFi(int param_1,uint param_2)

{
  undefined8 uVar1;
  long lVar2;
  
  if ((*(int *)(param_1 + 0x52c) != 0) && ((param_2 & 1) != 0)) {
    uVar1 = searchFrame__5FrameFPCc(*(undefined4 *)(param_1 + 0x30),0x653360);
    unChainModel__5FrameFv(uVar1);
    (**(code **)(*(int *)(*(int *)(param_1 + 0x52c) + 0x10) + 0x40))();
    while (lVar2 = FindOT__5WorldFP8VIF1Prim(0x42bf10,*(undefined4 *)(param_1 + 0x52c)), lVar2 != 0) {
      ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,*(undefined4 *)(param_1 + 0x52c));
    }
    *(byte *)(param_1 + 0x4b0) = *(byte *)(param_1 + 0x4b0) & 0xdf;
    *(undefined4 *)(param_1 + 0x53c) = 0;
    if ((*(int *)(param_1 + 0x564) != 0) && (*(int *)(param_1 + 0x564) != 0)) {
      __dla__FPv(*(int *)(param_1 + 0x564) + -0x10);
    }
    *(undefined4 *)(param_1 + 0x564) = 0;
    (**(code **)(*(int *)(*(int *)(param_1 + 0x52c) + 0x1c) + 0xc))();
    *(undefined4 *)(param_1 + 0x52c) = 0;
  }
  if ((*(int *)(param_1 + 0x530) != 0) && ((param_2 & 2) != 0)) {
    uVar1 = searchFrame__5FrameFPCc(*(undefined4 *)(param_1 + 0x30),0x653368);
    unChainModel__5FrameFv(uVar1);
    (**(code **)(*(int *)(*(int *)(param_1 + 0x530) + 0x10) + 0x40))();
    while (lVar2 = FindOT__5WorldFP8VIF1Prim(0x42bf10,*(undefined4 *)(param_1 + 0x530)), lVar2 != 0) {
      ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,*(undefined4 *)(param_1 + 0x530));
    }
    *(byte *)(param_1 + 0x4b0) = *(byte *)(param_1 + 0x4b0) & 0xbf;
    *(undefined4 *)(param_1 + 0x540) = 0;
    if ((*(int *)(param_1 + 0x568) != 0) && (*(int *)(param_1 + 0x568) != 0)) {
      __dla__FPv(*(int *)(param_1 + 0x568) + -0x10);
    }
    *(undefined4 *)(param_1 + 0x568) = 0;
    (**(code **)(*(int *)(*(int *)(param_1 + 0x530) + 0x1c) + 0xc))();
    *(undefined4 *)(param_1 + 0x530) = 0;
  }
  if ((*(int *)(param_1 + 0x534) != 0) && ((param_2 & 4) != 0)) {
    uVar1 = searchFrame__5FrameFPCc(*(undefined4 *)(param_1 + 0x30),0x653370);
    unChainModel__5FrameFv(uVar1);
    (**(code **)(*(int *)(*(int *)(param_1 + 0x534) + 0x10) + 0x40))();
    while (lVar2 = FindOT__5WorldFP8VIF1Prim(0x42bf10,*(undefined4 *)(param_1 + 0x534)), lVar2 != 0) {
      ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,*(undefined4 *)(param_1 + 0x534));
    }
    *(byte *)(param_1 + 0x4b0) = *(byte *)(param_1 + 0x4b0) & 0x7f;
    *(undefined4 *)(param_1 + 0x544) = 0;
    if ((*(int *)(param_1 + 0x56c) != 0) && (*(int *)(param_1 + 0x56c) != 0)) {
      __dla__FPv(*(int *)(param_1 + 0x56c) + -0x10);
    }
    *(undefined4 *)(param_1 + 0x56c) = 0;
    (**(code **)(*(int *)(*(int *)(param_1 + 0x534) + 0x1c) + 0xc))();
    *(undefined4 *)(param_1 + 0x534) = 0;
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0055b3a0  @20@__dt__8BtlModelFv
 * C++: @20@__dt__8BtlModelFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int _20___dt__8BtlModelFv(int param_1,short param_2)

{
  int iVar1;
  int iVar2;
  
  iVar2 = param_1 + -0x14;
  if (iVar2 != 0) {
    *(undefined4 *)(param_1 + -4) = 0x40a630;
    *(undefined4 *)(param_1 + 8) = 0x40a640;
    if ((*(int *)(param_1 + 0x54c) != 0) && (*(int *)(param_1 + 0x54c) != 0)) {
      __dla__FPv(*(int *)(param_1 + 0x54c) + -0x10);
    }
    if ((*(int *)(param_1 + 0x554) != 0) && (*(int *)(param_1 + 0x554) != 0)) {
      __dla__FPv(*(int *)(param_1 + 0x554) + -0x10);
    }
    if ((*(int *)(param_1 + 0x550) != 0) && (*(int *)(param_1 + 0x550) != 0)) {
      __dla__FPv(*(int *)(param_1 + 0x550) + -0x10);
    }
    if ((*(int *)(param_1 + 0x558) != 0) && (*(int *)(param_1 + 0x558) != 0)) {
      __dla__FPv(*(int *)(param_1 + 0x558) + -0x10);
    }
    if (*(int *)(param_1 + 0x518) != 0) {
      iVar1 = *(int *)(param_1 + 0x518);
      if (iVar1 != 0) {
        (**(code **)(*(int *)(iVar1 + 0x10) + 8))(iVar1,1);
      }
    }
    if (*(int *)(param_1 + 0x51c) != 0) {
      iVar1 = *(int *)(param_1 + 0x51c);
      if (iVar1 != 0) {
        (**(code **)(*(int *)(iVar1 + 0x10) + 8))(iVar1,1);
      }
    }
    if (*(int *)(param_1 + 0x520) != 0) {
      iVar1 = *(int *)(param_1 + 0x520);
      if (iVar1 != 0) {
        (**(code **)(*(int *)(iVar1 + 0x10) + 8))(iVar1,1);
      }
    }
    __dt__5ModelFv(iVar2,0);
    if (0 < param_2) {
      __dl__FPv(iVar2);
    }
  }
  return iVar2;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0057bf70  ModelEffectReset__8BtlModelFv
 * C++: BtlModel::ModelEffectReset()
 * size: 0x28 bytes
 * --------------------------------------------------------------------------- */
void ModelEffectReset__8BtlModelFv(undefined4 param_1)

{
  Reset__15ModelEffManagerFP5Model(param_1);
  return;
}

