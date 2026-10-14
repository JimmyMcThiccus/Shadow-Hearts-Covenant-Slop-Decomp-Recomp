/* ==== CLEANED (port: sh2_field/src/movement.rs) ==== */
#include "_types.h"
extern s8 dirTbl[16];  /* JP 0x005559e0: {-1,0,2,1,4,-1,3,-1,6,7,-1,-1,5,-1,-1,-1} */
/* JP 0x004a5f20 MakeMoveControl(float &speed, float &degrees, CPad *pad) -> gait 1 walk / 2 run */
int MakeMoveControl(float *speed, float *deg, CPad *pad) {
    u16 real = CPad_GetReal(pad); int gait = 1;
    CAnalogStick st = *CPad_GetAnalogStickL(pad);
    *speed = CAnalogStick_GetGauge(&st); *deg = CAnalogStick_GetDegree(&st);
    if (*speed < 0.1f) {
        if (real & 0xf0) {                                                          /* d-pad fallback */
            u32 i = ((real & 0x10) != 0) | (((real & 0x20) != 0) << 1) | (((real & 0x40) != 0) << 2) | (((real & 0x80) != 0) << 3);
            if (dirTbl[i] >= 0) { *speed = 0.5f; *deg = dirTbl[i] * 45; }
        }
        if (real & 0x4000) gait = 2;                                                /* cross held with d-pad: run */
    } else if (*speed >= 0.95f && !(real & 0x4000)) gait = 2;                       /* full tilt without cross: run */
    return gait;
}
/* JP 0x004a2a50 clipRadian */ void clipRadian(float *a) { if (3.141592f < *a) *a -= 6.283184f; if (*a < -3.141592f) *a += 6.283184f; }
/* JP 0x004a8b20 CField::ReverseVector -- mirror-world axis flips selected by flags_18f bits 0-2 */
void CField_ReverseVector(CField *t, FVector *v) { u8 f = t->flags_18f; if (f & 1) v->x = -v->x; if (f & 2) v->y = -v->y; if (f & 4) v->z = -v->z; }


/* ==== RAW (Ghidra output, names/globals resolved; not hand-cleaned) ==== */
/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: <free>   functions: 62
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/FieldFree.md).
 */

/* JP: 0x00430a80  cbSvpCallback(int, BufMemory*, int, char*, void*)   [cbSvpCallback__FiP9BufMemoryiPcPv]  size=0x40 */
undefined8
cbSvpCallback__FiP9BufMemoryiPcPv
          (undefined8 param_1,undefined4 param_2,undefined8 param_3,undefined8 param_4,
          undefined4 param_5)

{
  CreateDirect__9SavePointFP9BufMemory(param_5,param_2);
  return 0;
}

/* JP: 0x00430ac0  CbOn(char*, void*)   [CbOn__FPcPv]  size=0x34 */
void CbOn__FPcPv(undefined8 param_1,undefined4 param_2)

{
  cbOn__9SavePointFv(param_2);
  return;
}

/* JP: 0x00430b00  CbOff_1(char*, void*)   [CbOff_1__FPcPv]  size=0x34 */
void CbOff_1__FPcPv(undefined8 param_1,undefined4 param_2)

{
  cbOff_1__9SavePointFv(param_2);
  return;
}

/* JP: 0x00430b40  CbOff_2(char*, void*)   [CbOff_2__FPcPv]  size=0x34 */
void CbOff_2__FPcPv(undefined8 param_1,undefined4 param_2)

{
  cbOff_2__9SavePointFv(param_2);
  return;
}

/* JP: 0x00430c30  Init__Q29SavePoint18@class$2151SVP_cppFv   [Init__Q29SavePoint18@class$2151SVP_cppFv]  size=0x1c */
void Init__Q29SavePoint18_class_2151SVP_cppFv(undefined4 *param_1)

{
  *param_1 = 0;
  return;
}

/* JP: 0x004329f0  cbWpCallback(int, BufMemory*, int, char*, void*)   [cbWpCallback__FiP9BufMemoryiPcPv]  size=0x40 */
undefined8
cbWpCallback__FiP9BufMemoryiPcPv
          (undefined8 param_1,undefined4 param_2,undefined8 param_3,undefined8 param_4,
          undefined4 param_5)

{
  CreateDirect__9WarpPointFP9BufMemory(param_5,param_2);
  return 0;
}

/* JP: 0x00432bb0  Init__Q29WarpPoint17@class$2141WP_cppFv   [Init__Q29WarpPoint17@class$2141WP_cppFv]  size=0x1c */
void Init__Q29WarpPoint17_class_2141WP_cppFv(undefined4 *param_1)

{
  *param_1 = 0;
  return;
}

/* JP: 0x00432bd0  __ct__Q29WarpPoint17@class$2140WP_cppFv   [__ct__Q29WarpPoint17@class$2140WP_cppFv]  size=0x3c */
int __ct__Q29WarpPoint17_class_2140WP_cppFv(int param_1)

{
  __ct__7FVectorFv(param_1);
  __ct__7FVectorFv(param_1 + 0x10);
  return param_1;
}

/* JP: 0x004a2a30  GetDTCExSize(_DTCINFO*)   [GetDTCExSize__FP8_DTCINFO]  size=0x1c */
undefined4 GetDTCExSize__FP8_DTCINFO(int param_1)

{
  return *(undefined4 *)(param_1 + 8);
}

/* JP: 0x004a2a50  clipRadian(float&)   [clipRadian__FRf]  size=0xa4 */
void clipRadian__FRf(float *param_1)

{
  if (3.141592 < *param_1) {
    *param_1 = *param_1 - 6.283184;
  }
  if (*param_1 < -3.141592) {
    *param_1 = *param_1 + 6.283184;
  }
  return;
}

/* JP: 0x004a3f90  FldInitLSDPlayer()   [FldInitLSDPlayer__Fv]  size=0x144 */
void FldInitLSDPlayer__Fv(void)

{
  long lVar1;
  
  if (sys__9LSDPlayer == 0) {
    PlugDevice__9LSDPlayerFP16LSDDeviceHandler(0x423750);
    PlugDevice__9LSDPlayerFP16LSDDeviceHandler(0x4238c0);
    PlugDevice__9LSDPlayerFP16LSDDeviceHandler(0x4236f0);
    PlugDevice__9LSDPlayerFP16LSDDeviceHandler(0x423720);
    PlugDevice__9LSDPlayerFP16LSDDeviceHandler(0x423790);
    PlugDevice__9LSDPlayerFP16LSDDeviceHandler(0x423890);
    PlugDevice__9LSDPlayerFP16LSDDeviceHandler(0x42b750);
    PlugDevice__9LSDPlayerFP16LSDDeviceHandler(0x42b7d0);
    PlugDevice__9LSDPlayerFP16LSDDeviceHandler(0x421b90);
    PlugDevice__9LSDPlayerFP16LSDDeviceHandler(0x42bee0);
    PlugDevice__9LSDPlayerFP16LSDDeviceHandler(0x42beb0);
    PlugDevice__9LSDPlayerFP16LSDDeviceHandler(0x4237c0);
    PlugDevice__9LSDPlayerFP16LSDDeviceHandler(0x421e40);
    if ((sys__9LSDPlayer == 0) && (lVar1 = __nw__FUi(0xbc), lVar1 != 0)) {
      __ct__9LSDPlayerFv(lVar1);
    }
    Reset__9LSDPlayerFv(sys__9LSDPlayer);
  }
  return;
}

/* JP: 0x004a4fe0  FieldBreakMCES()   [FieldBreakMCES__Fv]  size=0x38 */
void FieldBreakMCES__Fv(void)

{
  if (sys__6CField != 0) {
    BreakMCES__6CFieldFi(sys__6CField,0);
  }
  return;
}

/* JP: 0x004a5020  FieldExitPauseMCES()   [FieldExitPauseMCES__Fv]  size=0xa0 */
void FieldExitPauseMCES__Fv(void)

{
  char cVar1;
  
  if (((sys__6CField != 0) &&
      (cVar1 = *(char *)(sys__6CField + 0x6a9), *(char *)(sys__6CField + 0x6a9) = cVar1 + '\x01',
      9 < (byte)(cVar1 + 1U))) && (-1 < (long)((ulong)*(byte *)(sys__6CField + 0x6a8) << 0x3e))) {
    *(byte *)(sys__6CField + 0x6a8) = *(byte *)(sys__6CField + 0x6a8) & 0xfd | 2;
    DisablePause__6CPauseFv(*(undefined4 *)(app__4CApp + 0x78));
  }
  return;
}

/* JP: 0x004a5250  MCESInvokeBattle()   [MCESInvokeBattle__Fv]  size=0xec */
void MCESInvokeBattle__Fv(void)

{
  int iVar1;
  undefined8 uVar2;
  
  iVar1 = sys__6CField;
  if (sys__6CField != 0) {
    if (((ulong)*(byte *)(sys__6CField + 0x18e) & 0x7f) >> 5 == 3) {
      BreakMCES__6CFieldFi(sys__6CField,0);
      *(ushort *)(iVar1 + 0x6a6) = *(ushort *)(iVar1 + 0x6a6) | 1;
      uVar2 = GetCurMPSname__12CFieldSocketFv(m_socket__12CFieldSocket);
      strcpy(iVar1 + 0x694,uVar2);
    }
    else {
      BreakMCES__6CFieldFi(sys__6CField,2);
      if (((int)(uint)*(byte *)(iVar1 + 0x6a5) >> 1 & 1U) == 0) {
        CaptureBtlIn__5BtlInFv();
        StartBtlIn__5BtlInFv();
      }
      else {
        CaptureBtlIn__9BtlInBossFv();
        StartBtlIn__9BtlInBossFv();
      }
    }
  }
  return;
}

/* JP: 0x004a59f0  _toUpper(int)   [_toUpper__Fi]  size=0x48 */
uint _toUpper__Fi(uint param_1)

{
  undefined4 uStack_10;
  
  uStack_10 = param_1;
  if ((0x60 < (int)param_1) && ((int)param_1 < 0x7b)) {
    uStack_10 = param_1 & 0xdf;
  }
  return uStack_10;
}

/* JP: 0x004a5a40  _stricmp(const char*, const char*)   [_stricmp__FPCcPCc]  size=0x98 */
undefined4 _stricmp__FPCcPCc(undefined1 *param_1,undefined1 *param_2)

{
  long lVar1;
  long lVar2;
  undefined1 *puStack_20;
  undefined1 *puStack_10;
  
  puStack_20 = param_1;
  puStack_10 = param_2;
  do {
    lVar1 = _toUpper__Fi(*puStack_20);
    lVar2 = _toUpper__Fi(*puStack_10);
    if (lVar1 != lVar2) {
      return 1;
    }
    puStack_20 = puStack_20 + 1;
    puStack_10 = puStack_10 + 1;
  } while (lVar1 != 0);
  return 0;
}

/* JP: 0x004a5f20  MakeMoveControl(float&, float&, CPad*)   [MakeMoveControl__FRfRfP4CPad]  size=0x1ec */
undefined4 MakeMoveControl__FRfRfP4CPad(float *param_1,float *param_2,undefined4 param_3)

{
  char cVar1;
  ulong uVar2;
  undefined8 uVar3;
  uint uVar4;
  undefined4 uVar5;
  float fVar6;
  undefined1 auStack_40 [16];
  float *pfStack_30;
  float *pfStack_20;
  undefined4 uStack_10;
  
  pfStack_30 = param_1;
  pfStack_20 = param_2;
  uStack_10 = param_3;
  uVar2 = GetReal__4CPadCFv(param_3);
  GetPress__4CPadCFv(uStack_10);
  uVar5 = 1;
  uVar3 = GetAnalogStickL__4CPadCFv(uStack_10);
  __ct__12CAnalogStickFRC12CAnalogStick(auStack_40,uVar3);
  fVar6 = (float)GetGauge__12CAnalogStickCFv(auStack_40);
  *pfStack_30 = fVar6;
  fVar6 = (float)GetDegree__12CAnalogStickCFv(auStack_40);
  *pfStack_20 = fVar6;
  if (*pfStack_30 < 0.1) {
    if ((uVar2 & 0xf0) != 0) {
      uVar4 = (uint)((uVar2 & 0x10) != 0);
      if ((uVar2 & 0x20) != 0) {
        uVar4 = uVar4 | 2;
      }
      if ((uVar2 & 0x40) != 0) {
        uVar4 = uVar4 | 4;
      }
      if ((uVar2 & 0x80) != 0) {
        uVar4 = uVar4 | 8;
      }
      cVar1 = (&dirTbl)[uVar4];
      if (-1 < cVar1) {
        *pfStack_30 = 0.5;
        *pfStack_20 = (float)(cVar1 * 0x2d);
      }
    }
    if ((uVar2 & 0x4000) != 0) {
      uVar5 = 2;
    }
  }
  else if ((0.95 <= *pfStack_30) && ((uVar2 & 0x4000) == 0)) {
    uVar5 = 2;
  }
  __dt__12CAnalogStickFv(auStack_40,0xffffffffffffffff);
  return uVar5;
}

/* JP: 0x004b0c50  GetNumber(const char&*)   [GetNumber__FRPCc]  size=0x88 */
int GetNumber__FRPCc(int *param_1)

{
  byte bVar1;
  int iVar2;
  
  iVar2 = 0;
  while ((bVar1 = *(byte *)*param_1, 0x2f < bVar1 && (bVar1 < 0x3a))) {
    *param_1 = *param_1 + 1;
    iVar2 = (bVar1 - 0x30) + iVar2 * 10;
  }
  return iVar2;
}

/* JP: 0x004b1590  VectorOperation(int, _ParStack*)   [VectorOperation__FiP9_ParStack]  size=0x5bc */
undefined4 VectorOperation__FiP9_ParStack(undefined4 param_1,float *param_2)

{
  float *pfVar1;
  float fVar2;
  undefined1 auStack_180 [16];
  undefined1 auStack_170 [16];
  undefined1 auStack_160 [64];
  undefined1 auStack_120 [16];
  undefined1 auStack_110 [16];
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
  undefined1 auStack_50 [16];
  undefined1 auStack_40 [28];
  float fStack_24;
  undefined4 uStack_20;
  float *pfStack_10;
  
  uStack_20 = param_1;
  pfStack_10 = param_2;
  switch(param_1) {
  case 0x80:
    memset(*param_2,0,0xc);
    break;
  case 0x81:
    memcpy(*param_2,param_2[1],0xc);
    break;
  case 0x82:
    __ct__7FVectorFv(auStack_40);
    memcpy(auStack_40,*pfStack_10,0xc);
    fStack_24 = (float)Length__7FVectorCFv(auStack_40);
    if (fStack_24 == 0.0) {
      memset(*pfStack_10,0,0xc);
    }
    else {
      Normalize__7FVectorFv(auStack_40);
      memcpy(*pfStack_10,auStack_40,0xc);
    }
    *pfStack_10 = fStack_24;
    return 2;
  case 0x83:
    __ct__7FVectorFv(auStack_50);
    memcpy(auStack_50,*pfStack_10,0xc);
    fVar2 = (float)Length__7FVectorCFv(auStack_50);
    *pfStack_10 = fVar2;
    return 2;
  case 0x84:
    __ct__7FVectorFv(auStack_60);
    __ct__7FVectorFv(auStack_70);
    memcpy(auStack_60,pfStack_10[1],0xc);
    memcpy(auStack_70,pfStack_10[2],0xc);
    __apl__7FVectorFRC7FVector(auStack_60,auStack_70);
    memcpy(*pfStack_10,auStack_60,0xc);
    break;
  case 0x85:
    __ct__7FVectorFv(auStack_80);
    __ct__7FVectorFv(auStack_90);
    memcpy(auStack_80,pfStack_10[1],0xc);
    memcpy(auStack_90,pfStack_10[2],0xc);
    __ami__7FVectorFRC7FVector(auStack_80,auStack_90);
    memcpy(*pfStack_10,auStack_80,0xc);
    break;
  case 0x86:
    __ct__7FVectorFv(auStack_a0);
    __ct__7FVectorFv(auStack_b0);
    memcpy(auStack_a0,pfStack_10[1],0xc);
    memcpy(auStack_b0,pfStack_10[2],0xc);
    __amu__7FVectorFRC7FVector(auStack_a0,auStack_b0);
    memcpy(*pfStack_10,auStack_a0,0xc);
    break;
  case 0x87:
    __ct__7FVectorFv(auStack_c0);
    memcpy(auStack_c0,pfStack_10[1],0xc);
    __amu__7FVectorFf(pfStack_10[2],auStack_c0);
    memcpy(*pfStack_10,auStack_c0,0xc);
    break;
  case 0x88:
    __ct__7FVectorFv(auStack_d0);
    memcpy(auStack_d0,pfStack_10[1],0xc);
    if (pfStack_10[2] == 0.0) {
      memset(*pfStack_10,0,0xc);
    }
    else {
      __adv__7FVectorFf(pfStack_10[2],auStack_d0);
      memcpy(*pfStack_10,auStack_d0,0xc);
    }
    break;
  case 0x89:
    __ct__7FVectorFv(auStack_e0);
    __ct__7FVectorFv(auStack_f0);
    memcpy(auStack_e0,*pfStack_10,0xc);
    memcpy(auStack_f0,pfStack_10[1],0xc);
    fVar2 = (float)InnerProduct__7FVectorCFRC7FVector(auStack_e0,auStack_f0);
    *pfStack_10 = fVar2;
    return 2;
  case 0x8a:
    __ct__7FVectorFv(auStack_100);
    __ct__7FVectorFv(auStack_110);
    memcpy(auStack_100,pfStack_10[1],0xc);
    memcpy(auStack_110,pfStack_10[2],0xc);
    OuterProduct__7FVectorCFRC7FVector(auStack_170,auStack_100,auStack_110);
    __as__7FVectorFRC7FVector(auStack_100,auStack_170);
    memcpy(*pfStack_10,auStack_100,0xc);
    break;
  case 0x8b:
    __ct__7FVectorFv(auStack_120);
    __ct__6MatrixFv(auStack_160);
    UnitMatrix__6MatrixFv(auStack_160);
    RotYMatrix__6MatrixFf(pfStack_10[2],auStack_160);
    memcpy(auStack_120,pfStack_10[1],0xc);
    ApplyMatrix__6MatrixCFRC7FVector(auStack_180,auStack_160,auStack_120);
    __as__7FVectorFRC7FVector(auStack_120,auStack_180);
    memcpy(*pfStack_10,auStack_120,0xc);
    break;
  case 0x8c:
    pfVar1 = (float *)*param_2;
    *pfVar1 = param_2[1];
    pfVar1[1] = param_2[2];
    pfVar1[2] = param_2[3];
  }
  return 0;
}

/* JP: 0x004b2b10  cbLoadMotion(unsigned int, unsigned int, void*)   [cbLoadMotion__FUiUiPv]  size=0x38 */
void cbLoadMotion__FUiUiPv(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  LoadMotionCB__6CFieldFUiUi(param_3,param_1,param_2);
  return;
}

/* JP: 0x004b3d40  FindFrame(CFieldModel*, const char*)   [FindFrame__FP11CFieldModelPCc]  size=0x90 */
undefined8 FindFrame__FP11CFieldModelPCc(undefined4 param_1,undefined *param_2)

{
  undefined8 uVar1;
  undefined *puStack_10;
  
  if (param_2 == (undefined *)0x0) {
    uVar1 = 0;
  }
  else {
    if (param_2 == (undefined *)0x1) {
      puStack_10 = &_11657;
    }
    else {
      puStack_10 = param_2;
      if (param_2 == (undefined *)0x2) {
        puStack_10 = &_11658;
      }
    }
    uVar1 = SearchFrame__11CFieldModelFPCc(param_1,puStack_10);
  }
  return uVar1;
}

/* JP: 0x004b4020  CalcStandParent(FVector&, CFieldModel*, float)   [CalcStandParent__FR7FVectorP11CFieldModelf]  size=0x108 */
float CalcStandParent__FR7FVectorP11CFieldModelf(float param_1,int param_2,undefined4 param_3)

{
  undefined1 auStack_60 [16];
  undefined1 auStack_50 [28];
  float fStack_34;
  int iStack_30;
  undefined4 uStack_20;
  float fStack_10;
  
  iStack_30 = param_2;
  uStack_20 = param_3;
  fStack_10 = param_1;
  fStack_34 = (float)GetRotY__11CFieldModelFv(param_3);
  fStack_34 = fStack_34 - fStack_10;
  if (fStack_34 < -3.141592) {
    fStack_34 = fStack_34 + 6.283184;
  }
  else if (3.141592 < fStack_34) {
    fStack_34 = fStack_34 - 6.283184;
  }
  GetPos__11CFieldModelFv(auStack_60,uStack_20);
  __mi__7FVectorCFRC7FVector(auStack_50,auStack_60,iStack_30);
  __as__7FVectorFRC7FVector(iStack_30,auStack_50);
  *(undefined4 *)(iStack_30 + 0xc) = 0x3f800000;
  return fStack_34;
}

/* JP: 0x004b64c0  GetImgName(char*, const char*)   [GetImgName__FPcPCc]  size=0x3c */
void GetImgName__FPcPCc(undefined4 param_1,undefined4 param_2)

{
  sprintf(param_1,0x555e10,pDataPath__7SysTool,param_2);
  return;
}

/* JP: 0x004b7110  CreateSavePoint(_SavPoint*, Model*)   [CreateSavePoint__FP9_SavPointP5Model]  size=0xb0 */
void CreateSavePoint__FP9_SavPointP5Model(int param_1,undefined4 param_2)

{
  long lVar1;
  undefined8 uVar2;
  undefined1 auStack_30 [16];
  int iStack_20;
  undefined4 uStack_10;
  
  iStack_20 = param_1;
  uStack_10 = param_2;
  __ct__7FVectorFv(auStack_30);
  GetShortPos__FP7FVectorPs(auStack_30,iStack_20);
  lVar1 = __nw__FUi(0xc0);
  uVar2 = 0;
  if (lVar1 != 0) {
    uVar2 = __ct__9SavePointFv(lVar1);
  }
  *(int *)(iStack_20 + 8) = (int)uVar2;
  Create__9SavePointFv(uVar2);
  SetPos__9SavePointFR7FVector(uVar2,auStack_30);
  SetCheckModel__9SavePointFP5Model(uVar2,uStack_10);
  return;
}

/* JP: 0x004b79c0  CreateWarpPoint(_WapPoint*, int)   [CreateWarpPoint__FP9_WapPointi]  size=0xbc */
void CreateWarpPoint__FP9_WapPointi(int param_1,undefined4 param_2)

{
  long lVar1;
  undefined8 uVar2;
  undefined1 auStack_30 [16];
  int iStack_20;
  undefined4 uStack_10;
  
  iStack_20 = param_1;
  uStack_10 = param_2;
  __ct__7FVectorFv(auStack_30);
  GetShortPos__FP7FVectorPs(auStack_30,iStack_20);
  lVar1 = __nw__FUi(0xe0);
  uVar2 = 0;
  if (lVar1 != 0) {
    uVar2 = __ct__9WarpPointFv(lVar1);
  }
  *(int *)(iStack_20 + 8) = (int)uVar2;
  *(char *)(iStack_20 + 7) = (char)uStack_10;
  Create__9WarpPointFs(uVar2,(short)uStack_10);
  SetPos__9WarpPointFR7FVector(uVar2,auStack_30);
  return;
}

/* JP: 0x004b9f50  GetNearestPath(SDB::tagFCAMERA*, FVector, int&)   [GetNearestPath__FPQ23SDB10tagFCAMERA7FVectorRi]  size=0x1270 */
float GetNearestPath__FPQ23SDB10tagFCAMERA7FVectorRi(int param_1,int param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  bool bVar3;
  bool bVar4;
  undefined8 uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  float fVar10;
  undefined1 auStack_3a0 [16];
  undefined1 auStack_390 [16];
  undefined1 auStack_380 [16];
  undefined1 auStack_370 [16];
  undefined1 auStack_360 [16];
  undefined1 auStack_350 [16];
  undefined1 auStack_340 [16];
  undefined1 auStack_330 [16];
  undefined1 auStack_320 [16];
  undefined1 auStack_310 [16];
  undefined1 auStack_300 [16];
  undefined1 auStack_2f0 [16];
  undefined1 auStack_2e0 [16];
  undefined1 auStack_2d0 [16];
  undefined1 auStack_2c0 [16];
  undefined1 auStack_2b0 [16];
  undefined1 auStack_2a0 [16];
  undefined1 auStack_290 [16];
  undefined1 auStack_280 [16];
  undefined1 auStack_270 [16];
  undefined1 auStack_260 [16];
  undefined1 auStack_250 [16];
  undefined1 auStack_240 [16];
  undefined1 auStack_230 [16];
  undefined1 auStack_220 [16];
  undefined1 auStack_210 [16];
  undefined1 auStack_200 [16];
  undefined1 auStack_1f0 [16];
  undefined1 auStack_1e0 [16];
  undefined1 auStack_1d0 [16];
  undefined1 auStack_1c0 [16];
  undefined1 auStack_1b0 [4];
  float fStack_1ac;
  undefined1 auStack_1a0 [4];
  undefined4 uStack_19c;
  undefined1 auStack_190 [4];
  undefined4 uStack_18c;
  undefined1 auStack_180 [4];
  undefined4 uStack_17c;
  undefined1 auStack_170 [16];
  undefined1 auStack_160 [16];
  undefined1 auStack_150 [4];
  undefined4 uStack_14c;
  undefined1 auStack_140 [16];
  undefined1 auStack_130 [4];
  undefined4 uStack_12c;
  undefined1 auStack_120 [4];
  undefined4 uStack_11c;
  undefined1 auStack_110 [16];
  undefined1 auStack_100 [16];
  undefined1 auStack_f0 [16];
  undefined1 auStack_e0 [16];
  undefined1 auStack_d0 [16];
  undefined1 auStack_c0 [4];
  undefined4 uStack_bc;
  undefined1 auStack_b0 [4];
  undefined4 uStack_ac;
  undefined1 auStack_a0 [4];
  undefined4 uStack_9c;
  undefined1 auStack_90 [4];
  undefined4 uStack_8c;
  float afStack_78 [4];
  float fStack_68;
  float fStack_64;
  float fStack_60;
  float fStack_5c;
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
  int iStack_30;
  int iStack_20;
  int *piStack_10;
  
  iVar1 = *(int *)(param_1 + 4);
  iStack_30 = param_1;
  iStack_20 = param_2;
  piStack_10 = param_3;
  __ct__7FVectorFv(auStack_90);
  __ct__7FVectorFv(auStack_a0);
  __ct__7FVectorFv(auStack_c0);
  __ct__7FVectorFv(auStack_b0);
  __ct__7FVectorFv(auStack_e0);
  __ct__7FVectorFv(auStack_d0);
  __ct__7FVectorFv(auStack_f0);
  iVar2 = *(int *)(iStack_30 + 8);
  fStack_3c = 32000.0;
  __ct__7FVectorFv(auStack_100);
  __ct__7FVectorFv(auStack_110);
  iVar8 = -1;
  for (iVar6 = 0; iVar6 < iVar1; iVar6 = iVar6 + 1) {
    __mi__7FVectorCFRC7FVector(auStack_1c0,iStack_20,iVar2 + iVar6 * 0x40 + 0x30);
    __as__7FVectorFRC7FVector(auStack_100,auStack_1c0);
    fStack_40 = (float)Length__7FVectorCFv(auStack_100);
    iVar7 = iVar6;
    fVar10 = fStack_40;
    if ((-1 < iVar8) && (fVar10 = fStack_40, fStack_3c <= fStack_40)) {
      iVar7 = iVar8;
      fVar10 = fStack_3c;
    }
    fStack_3c = fVar10;
    iVar8 = iVar7;
  }
  if (iVar8 == 0) {
    iVar6 = 0;
  }
  else if (iVar8 < iVar1 + -1) {
    __ct__7FVectorFv(auStack_120);
    __ct__7FVectorFv(auStack_130);
    __ct__7FVectorFv(auStack_140);
    __ct__7FVectorFv(auStack_150);
    __as__7FVectorFRC7FVector(auStack_120,iVar2 + (iVar8 + -1) * 0x40 + 0x30);
    __as__7FVectorFRC7FVector(auStack_130,iVar2 + (iVar8 + 1) * 0x40 + 0x30);
    __as__7FVectorFRC7FVector(auStack_140,iVar2 + iVar8 * 0x40 + 0x30);
    __ami__7FVectorFRC7FVector(auStack_120,auStack_140);
    __ami__7FVectorFRC7FVector(auStack_130,auStack_140);
    uStack_11c = 0;
    uStack_12c = 0;
    Normalize__7FVectorFv(auStack_120);
    Normalize__7FVectorFv(auStack_130);
    __mi__7FVectorCFRC7FVector(auStack_1d0,iStack_20,auStack_140);
    __as__7FVectorFRC7FVector(auStack_150,auStack_1d0);
    __pl__7FVectorCFRC7FVector(auStack_1e0,auStack_120,auStack_130);
    __as__7FVectorFRC7FVector(auStack_140,auStack_1e0);
    uStack_14c = 0;
    Normalize__7FVectorFv(auStack_150);
    fVar10 = (float)InnerProduct__7FVectorCFRC7FVector(auStack_120,auStack_130);
    iVar6 = iVar8;
    if (-0.9999 < fVar10) {
      Normalize__7FVectorFv(auStack_140);
      fStack_48 = (float)InnerProduct__7FVectorCFRC7FVector(auStack_140,auStack_150);
      if (0.0 <= fStack_48) {
        OuterProduct__7FVectorCFRC7FVector(auStack_160,auStack_140,auStack_120);
        OuterProduct__7FVectorCFRC7FVector(auStack_1f0,auStack_160,auStack_140);
        __as__7FVectorFRC7FVector(auStack_160,auStack_1f0);
        fStack_48 = (float)InnerProduct__7FVectorCFRC7FVector(auStack_160,auStack_150);
        if (0.0 <= fStack_48) {
          iVar6 = iVar8 + -1;
        }
      }
      else {
        OuterProduct__7FVectorCFRC7FVector(auStack_170,auStack_140,auStack_130);
        OuterProduct__7FVectorCFRC7FVector(auStack_200,auStack_170,auStack_140);
        __as__7FVectorFRC7FVector(auStack_170,auStack_200);
        fStack_48 = (float)InnerProduct__7FVectorCFRC7FVector(auStack_170,auStack_150);
        if (0.0 <= fStack_48) {
          iVar6 = iVar8 + -1;
        }
      }
    }
    else {
      fStack_44 = (float)InnerProduct__7FVectorCFRC7FVector(auStack_120,auStack_150);
      if (0.0 <= fStack_44) {
        iVar6 = iVar8 + -1;
      }
    }
  }
  else {
    iVar6 = iVar8 + -1;
  }
  *(undefined4 *)(iStack_20 + 4) = 0;
  __as__7FVectorFRC7FVector(auStack_90,iVar2 + iVar8 * 0x40 + 0x30);
  uStack_8c = 0;
  uVar9 = *(uint *)(iVar2 + iVar8 * 0x40 + 0x3c);
  if ((uVar9 & 0xff000000) != 0) {
    uVar9 = 0;
  }
  if ((uVar9 & 1) == 0) {
    if (iVar8 < 1) {
      __mi__7FVectorCFRC7FVector(auStack_240,iVar2 + (iVar8 + 1) * 0x40 + 0x30,auStack_90);
      __as__7FVectorFRC7FVector(auStack_b0,auStack_240);
      __ml__7FVectorCFf(0xbf800000,auStack_250,auStack_b0);
      __as__7FVectorFRC7FVector(auStack_c0,auStack_250);
    }
    else {
      __mi__7FVectorCFRC7FVector(auStack_210,iVar2 + (iVar8 + -1) * 0x40 + 0x30,auStack_90);
      __as__7FVectorFRC7FVector(auStack_c0,auStack_210);
      if (iVar8 < iVar1 + -1) {
        __mi__7FVectorCFRC7FVector(auStack_220,iVar2 + (iVar8 + 1) * 0x40 + 0x30,auStack_90);
        __as__7FVectorFRC7FVector(auStack_b0,auStack_220);
      }
      else {
        __ml__7FVectorCFf(0xbf800000,auStack_230,auStack_c0);
        __as__7FVectorFRC7FVector(auStack_b0,auStack_230);
      }
    }
    uStack_bc = 0;
    uStack_ac = 0;
    afStack_78[2] = (float)Length__7FVectorCFv(auStack_c0);
    afStack_78[3] = (float)Length__7FVectorCFv(auStack_b0);
    Normalize__7FVectorFv(auStack_c0);
    Normalize__7FVectorFv(auStack_b0);
    fStack_34 = (float)InnerProduct__7FVectorCFRC7FVector(auStack_c0,auStack_b0);
    if (fStack_34 <= -0.9999) {
      __ct__7FVectorFv(auStack_180);
      if (iVar8 == 0) {
        __mi__7FVectorCFRC7FVector(auStack_260,iStack_20,auStack_90);
        __as__7FVectorFRC7FVector(auStack_180,auStack_260);
        fStack_38 = (float)InnerProduct__7FVectorCFRC7FVector(auStack_b0,auStack_180);
        fStack_38 = fStack_38 / afStack_78[3];
        if (fStack_38 < 0.0) {
          fStack_38 = 0.0;
        }
      }
      else {
        __ct__7FVectorFv(auStack_190);
        __as__7FVectorFRC7FVector(auStack_190,iVar2 + iVar8 * 0x40 + 0x30);
        __mi__7FVectorCFRC7FVector(auStack_270,iStack_20,auStack_190);
        __as__7FVectorFRC7FVector(auStack_180,auStack_270);
        if (iVar6 < iVar8) {
          __mi__7FVectorCFRC7FVector(auStack_280,iVar2 + (iVar8 + -1) * 0x40 + 0x30,auStack_190);
          __as__7FVectorFRC7FVector(auStack_190,auStack_280);
        }
        else {
          __mi__7FVectorCFRC7FVector(auStack_290,iVar2 + (iVar8 + 1) * 0x40 + 0x30,auStack_190);
          __as__7FVectorFRC7FVector(auStack_190,auStack_290);
        }
        uStack_17c = 0;
        uStack_18c = 0;
        afStack_78[2] = (float)Length__7FVectorCFv(auStack_190);
        afStack_78[3] = (float)Length__7FVectorCFv(auStack_180);
        Normalize__7FVectorFv(auStack_190);
        Normalize__7FVectorFv(auStack_180);
        fVar10 = (float)InnerProduct__7FVectorCFRC7FVector(auStack_190,auStack_180);
        fStack_38 = (afStack_78[3] * fVar10) / afStack_78[2];
        if (iVar6 < iVar8) {
          fStack_38 = 1.0 - fStack_38;
        }
        if (1.0 < fStack_38) {
          fStack_38 = 1.0;
        }
        if (fStack_38 < 0.0) {
          if (iVar6 == 0) {
            fStack_38 = 0.0;
          }
          else {
            iVar6 = iVar6 + -1;
            fStack_38 = fStack_38 + 1.0;
          }
        }
      }
    }
    else {
      __pl__7FVectorCFRC7FVector(auStack_2a0,auStack_c0,auStack_b0);
      __as__7FVectorFRC7FVector(auStack_f0,auStack_2a0);
      Normalize__7FVectorFv(auStack_f0);
      uVar9 = (uint)(afStack_78[3] < afStack_78[2]);
      fStack_34 = (float)InnerProduct__7FVectorCFRC7FVector(auStack_f0,auStack_c0 + uVar9 * 0x10);
      afStack_78[uVar9] = 0.2;
      if (afStack_78[uVar9 + 2] < 100.0) {
        fStack_4c = (fStack_34 * 100.0) / afStack_78[uVar9 + 2];
        if (0.5 < fStack_4c) {
          fStack_4c = 0.5;
        }
        if (fStack_4c < 0.05) {
          fStack_4c = 0.05;
        }
        afStack_78[uVar9] = fStack_4c;
      }
      fStack_50 = afStack_78[uVar9 + 2] * afStack_78[uVar9];
      __ml__7FVectorCFf(fStack_50,auStack_2c0,auStack_c0 + uVar9 * 0x10);
      __pl__7FVectorCFRC7FVector(auStack_2b0,auStack_90,auStack_2c0);
      __as__7FVectorFRC7FVector(auStack_e0 + uVar9 * 0x10,auStack_2b0);
      fStack_50 = fStack_50 / fStack_34;
      __ml__7FVectorCFf(fStack_50,auStack_2e0,auStack_f0);
      __pl__7FVectorCFRC7FVector(auStack_2d0,auStack_90,auStack_2e0);
      __as__7FVectorFRC7FVector(auStack_a0,auStack_2d0);
      uStack_9c = 0;
      fStack_34 = (float)InnerProduct__7FVectorCFRC7FVector
                                   (auStack_f0,auStack_c0 + (uVar9 ^ 1) * 0x10);
      fStack_34 = fStack_34 * fStack_50;
      __ml__7FVectorCFf(fStack_34,auStack_300,auStack_c0 + (uVar9 ^ 1) * 0x10);
      __pl__7FVectorCFRC7FVector(auStack_2f0,auStack_90,auStack_300);
      __as__7FVectorFRC7FVector(auStack_e0 + (uVar9 ^ 1) * 0x10,auStack_2f0);
      afStack_78[uVar9 ^ 1] = fStack_34 / afStack_78[(uVar9 ^ 1) + 2];
      uVar5 = __ct__7FVectorFv(auStack_1a0);
      __ct__7FVectorFv(auStack_1b0,uVar5);
      __mi__7FVectorCFRC7FVector(auStack_310,auStack_90,auStack_a0);
      __as__7FVectorFRC7FVector(auStack_1a0,auStack_310);
      uStack_19c = 0;
      Normalize__7FVectorFv(auStack_1a0);
      __mi__7FVectorCFRC7FVector(auStack_320,iVar2 + (iVar8 + -1) * 0x40 + 0x30,auStack_a0);
      uVar5 = __as__7FVectorFRC7FVector(auStack_1b0,auStack_320);
      fStack_1ac = 0.0;
      Normalize__7FVectorFv(auStack_1b0,uVar5);
      OuterProduct__7FVectorCFRC7FVector(auStack_330,auStack_1a0,auStack_1b0);
      __as__7FVectorFRC7FVector(auStack_1b0,auStack_330);
      fStack_34 = fStack_1ac;
      __mi__7FVectorCFRC7FVector(auStack_340,iStack_20,auStack_a0);
      __as__7FVectorFRC7FVector(auStack_1b0,auStack_340);
      fStack_1ac = 0.0;
      Normalize__7FVectorFv(auStack_1b0);
      OuterProduct__7FVectorCFRC7FVector(auStack_350,auStack_1a0,auStack_1b0);
      __as__7FVectorFRC7FVector(auStack_1b0,auStack_350);
      bVar3 = fStack_34 < 0.0;
      bVar4 = fStack_1ac < 0.0;
      __mi__7FVectorCFRC7FVector(auStack_360,iStack_20,auStack_a0);
      __as__7FVectorFRC7FVector(auStack_1b0,auStack_360);
      Normalize__7FVectorFv(auStack_1b0);
      fStack_58 = (float)InnerProduct__7FVectorCFRC7FVector(auStack_1a0,auStack_1b0);
      if (bVar3 == bVar4) {
        if (iVar8 == iVar6) {
          iVar6 = iVar6 + -1;
        }
        __mi__7FVectorCFRC7FVector(auStack_370,auStack_e0,auStack_a0);
        uVar5 = __as__7FVectorFRC7FVector(auStack_1b0,auStack_370);
        fStack_1ac = 0.0;
        Normalize__7FVectorFv(auStack_1b0,uVar5);
        fStack_54 = (float)InnerProduct__7FVectorCFRC7FVector(auStack_1a0,auStack_1b0);
        if (fStack_54 < fStack_58) {
          if (fStack_54 < 1.0) {
            fStack_5c = (float)acosf(fStack_54);
          }
          else {
            fStack_5c = 0.0;
          }
          fStack_54 = fStack_5c;
          if (fStack_58 < 1.0) {
            fStack_60 = (float)acosf(fStack_58);
          }
          else {
            fStack_60 = 0.0;
          }
          fStack_38 = afStack_78[0] * ((fStack_54 - fStack_60) / fStack_54 - 1.0) + 1.0;
        }
        else {
          __mi__7FVectorCFRC7FVector(auStack_380,iVar2 + (iVar8 + -1) * 0x40 + 0x30,iStack_20);
          __as__7FVectorFRC7FVector(auStack_1b0,auStack_380);
          fStack_1ac = 0.0;
          fStack_38 = (float)InnerProduct__7FVectorCFRC7FVector(auStack_c0,auStack_1b0);
          fStack_38 = fStack_38 / afStack_78[2];
          if (fStack_38 < 0.0) {
            iVar6 = iVar6 + -1;
            fStack_38 = fStack_38 + 1.0;
          }
        }
      }
      else {
        if (iVar6 < iVar8) {
          iVar6 = iVar6 + 1;
        }
        __mi__7FVectorCFRC7FVector(auStack_390,auStack_d0,auStack_a0);
        __as__7FVectorFRC7FVector(auStack_1b0,auStack_390);
        fStack_1ac = 0.0;
        Normalize__7FVectorFv(auStack_1b0);
        fStack_54 = (float)InnerProduct__7FVectorCFRC7FVector(auStack_1a0,auStack_1b0);
        if (fStack_54 < fStack_58) {
          if (fStack_54 < 1.0) {
            fStack_64 = (float)acosf(fStack_54);
          }
          else {
            fStack_64 = 0.0;
          }
          fStack_54 = fStack_64;
          if (fStack_58 < 1.0) {
            fStack_68 = (float)acosf(fStack_58);
          }
          else {
            fStack_68 = 0.0;
          }
          fStack_38 = (1.0 - (fStack_54 - fStack_68) / fStack_54) * afStack_78[1];
        }
        else {
          __mi__7FVectorCFRC7FVector(auStack_3a0,iStack_20,auStack_90);
          __as__7FVectorFRC7FVector(auStack_1b0,auStack_3a0);
          fStack_1ac = 0.0;
          fStack_38 = (float)InnerProduct__7FVectorCFRC7FVector(auStack_b0,auStack_1b0);
          fStack_38 = fStack_38 / afStack_78[3];
        }
      }
    }
    *piStack_10 = iVar6;
  }
  else {
    fStack_38 = (float)(iVar8 + 1000);
  }
  return fStack_38;
}

/* JP: 0x004bc080  Clear__Q29FldSpline6_flagsFv   [Clear__Q29FldSpline6_flagsFv]  size=0x1c */
void Clear__Q29FldSpline6_flagsFv(undefined2 *param_1)

{
  *param_1 = 0;
  return;
}

/* JP: 0x004be430  clear__Q212CFieldCamera6_flagsFv   [clear__Q212CFieldCamera6_flagsFv]  size=0x1c */
void clear__Q212CFieldCamera6_flagsFv(undefined2 *param_1)

{
  *param_1 = 0;
  return;
}

/* JP: 0x004bf920  EncodeChar(int)   [EncodeChar__Fi]  size=0xa4 */
uint EncodeChar__Fi(uint param_1)

{
  uint uVar1;
  uint uStack_10;
  
  uStack_10 = param_1;
  if ((0x60 < (int)param_1) && ((int)param_1 < 0x7b)) {
    uStack_10 = param_1 & 0xdf;
  }
  for (uVar1 = 0; (uVar1 < 0x26 && ((long)(int)uStack_10 != (long)n38tbl[uVar1])); uVar1 = uVar1 + 1
      ) {
  }
  if (0x26 < uVar1) {
    uVar1 = 0x26;
  }
  return uVar1;
}

/* JP: 0x004bff50  EncodeMotionName(const char*)   [EncodeMotionName__FPCc]  size=0x170 */
uint EncodeMotionName__FPCc(char *param_1)

{
  char cVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  byte abStack_20 [12];
  uint uStack_14;
  char *pcStack_10;
  
  uVar5 = 0;
  pcStack_10 = param_1;
  memset(abStack_20,0,6);
  for (iVar3 = 0; iVar3 < 6; iVar3 = iVar3 + 1) {
    cVar1 = *pcStack_10;
    if (cVar1 == '\0') break;
    pcStack_10 = pcStack_10 + 1;
    bVar2 = EncodeChar__Fi(cVar1);
    abStack_20[iVar3] = bVar2;
  }
  uStack_14 = 0;
  for (iVar3 = 0; iVar3 < 3; iVar3 = iVar3 + 1) {
    iVar4 = (uint)abStack_20[iVar3 * 2] +
            ((uint)abStack_20[iVar3 * 2 + 1] * 0x12 + (uint)abStack_20[iVar3 * 2 + 1]) * 2;
    *(char *)((int)&uStack_14 + iVar3) = (char)iVar4;
    iVar4 = iVar4 >> 8;
    if (iVar3 == 1) {
      iVar4 = iVar4 * 5;
    }
    if (iVar3 == 2) {
      iVar4 = iVar4 * 0x19;
    }
    uVar5 = uVar5 + iVar4;
  }
  return uStack_14 | (uVar5 | 0x80) << 0x18;
}

/* JP: 0x004c00c0  DecodeMotionName(char*, unsigned int)   [DecodeMotionName__FPcUi]  size=0x1a8 */
void DecodeMotionName__FPcUi(byte *param_1,uint param_2)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  byte abStack_30 [12];
  uint auStack_24 [9];
  
  uVar3 = param_2 >> 0x18 & 0x7f;
  auStack_24[0] = param_2;
  for (iVar2 = 0; iVar2 < 3; iVar2 = iVar2 + 1) {
    uVar4 = (uint)*(byte *)((int)auStack_24 + iVar2) + (uVar3 % 5) * 0x100;
    uVar3 = uVar3 / 5;
    abStack_30[iVar2 * 2] = (byte)(uVar4 % 0x26);
    abStack_30[iVar2 * 2 + 1] = (byte)(uVar4 / 0x26);
  }
  for (iVar2 = 0; (iVar2 < 6 && (abStack_30[iVar2] != 0)); iVar2 = iVar2 + 1) {
    bVar1 = n38tbl[abStack_30[iVar2]];
    if (('@' < (char)bVar1) && ((char)bVar1 < '[')) {
      bVar1 = bVar1 | 0x20;
    }
    *param_1 = bVar1;
    param_1 = param_1 + 1;
  }
  *param_1 = 0;
  return;
}

/* JP: 0x004c0270  GetMotionName(unsigned int)   [GetMotionName__FUi]  size=0x60 */
undefined1 * GetMotionName__FUi(int param_1)

{
  undefined1 *puVar1;
  
  if (param_1 < 0) {
    DecodeMotionName__FPcUi(&gp0xffff85f8,param_1);
    puVar1 = &gp0xffff85f8;
  }
  else {
    puVar1 = *(undefined1 **)(&fldMotionList + param_1 * 4);
  }
  return puVar1;
}

/* JP: 0x004c02d0  InitFieldModel()   [InitFieldModel__Fv]  size=0xc */
void InitFieldModel__Fv(void)

{
  mdlReadCount = 0;
  return;
}

/* JP: 0x004c02e0  GetModelReadCt()   [GetModelReadCt__Fv]  size=0xc */
undefined4 GetModelReadCt__Fv(void)

{
  return mdlReadCount;
}

/* JP: 0x004c02f0  mdlReadCB(int, BufMemory*, int, char*, void*)   [mdlReadCB__FiP9BufMemoryiPcPv]  size=0x78 */
bool mdlReadCB__FiP9BufMemoryiPcPv
               (int param_1,undefined4 param_2,undefined8 param_3,undefined8 param_4,
               undefined4 param_5)

{
  long lVar1;
  
  mdlReadCount = mdlReadCount + -1;
  *(undefined4 *)(param_1 + 8) = param_2;
  lVar1 = ReadCB__11CFieldModelFP15_FieldDataCachei(param_5,param_1,0);
  if (lVar1 == 0) {
    *(undefined4 *)(param_1 + 8) = 0;
  }
  return lVar1 == 0;
}

/* JP: 0x004c0370  mdlReadMotionCB(int, BufMemory*, int, char*, void*)   [mdlReadMotionCB__FiP9BufMemoryiPcPv]  size=0x6c */
bool mdlReadMotionCB__FiP9BufMemoryiPcPv
               (undefined4 param_1,undefined4 param_2,undefined8 param_3,undefined8 param_4,
               undefined4 param_5)

{
  long lVar1;
  
  mdlReadCount = mdlReadCount + -1;
  lVar1 = ReadMotionCB__11CFieldModelFiP9BufMemory(param_5,param_1,param_2);
  return lVar1 == 0;
}

/* JP: 0x004c0770  __ct__Q211CFieldModel7_memberFv   [__ct__Q211CFieldModel7_memberFv]  size=0x30 */
int __ct__Q211CFieldModel7_memberFv(int param_1)

{
  __ct__13_AutoMoveInfoFv(param_1 + 0x110);
  return param_1;
}

/* JP: 0x004c1940  clear__Q311CFieldModel7_member6_flagsFv   [clear__Q311CFieldModel7_member6_flagsFv]  size=0x1c */
void clear__Q311CFieldModel7_member6_flagsFv(undefined4 *param_1)

{
  *param_1 = 0;
  return;
}

/* JP: 0x004c1960  clear__Q311CFieldModel7_member8_evflagsFv   [clear__Q311CFieldModel7_member8_evflagsFv]  size=0x1c */
void clear__Q311CFieldModel7_member8_evflagsFv(undefined2 *param_1)

{
  *param_1 = 0;
  return;
}

/* JP: 0x004c4020  InterPolPitch(float, float, float)   [InterPolPitch__Ffff]  size=0x120 */
float InterPolPitch__Ffff(float param_1,float param_2,float param_3)

{
  float fStack_34;
  float fStack_20;
  float fStack_10;
  
  fStack_34 = param_2 - param_1;
  if (fStack_34 < 0.0) {
    fStack_34 = -fStack_34;
  }
  fStack_10 = param_3;
  if (fStack_34 < 0.2) {
    fStack_10 = param_3 * (fStack_34 / 0.2);
  }
  fStack_20 = param_1;
  if (param_2 < param_1) {
    param_2 = param_2 + fStack_10 * 0.5;
    if (param_2 <= param_1) {
      fStack_20 = param_2;
    }
  }
  else if (param_1 <= param_2 - fStack_10) {
    fStack_20 = param_2 - fStack_10;
  }
  return fStack_20;
}

/* JP: 0x004c4e10  GetSmoothVelocity(float, float, float, float, float)   [GetSmoothVelocity__Ffffff]  size=0x19c */
float GetSmoothVelocity__Ffffff
                (float param_1,float param_2,float param_3,float param_4,float param_5)

{
  float fVar1;
  
  if (param_1 < 0.0) {
    param_3 = 0.0;
  }
  else if (1.0 <= param_1) {
    param_3 = 1.0;
  }
  else if (param_1 < param_2) {
    param_3 = param_3 * (param_1 / param_2) * (param_1 / param_2);
  }
  else if (param_1 <= param_4) {
    param_3 = param_3 + ((param_5 - param_3) / (param_4 - param_2)) * (param_1 - param_2);
  }
  else {
    fVar1 = (1.0 - param_1) / (1.0 - param_4);
    param_3 = 1.0 - (1.0 - param_5) * fVar1 * fVar1;
  }
  return param_3;
}

/* JP: 0x004c6bf0  ClipRadian(float)   [ClipRadian__Ff]  size=0x180 */
float ClipRadian__Ff(float param_1)

{
  undefined4 uStack_10;
  
  uStack_10 = param_1;
  if (6.283184 < param_1) {
    uStack_10 = param_1 - (float)(int)(param_1 / 6.283184) * 6.283184;
  }
  if (uStack_10 < -6.283184) {
    uStack_10 = uStack_10 + (float)(int)(uStack_10 / -6.283184) * 6.283184;
  }
  if (3.141592 < uStack_10) {
    uStack_10 = uStack_10 - 6.283184;
  }
  else if (uStack_10 < -3.141592) {
    uStack_10 = uStack_10 + 6.283184;
  }
  return uStack_10;
}

/* JP: 0x004c6fa0  GetRotAngle(int)   [GetRotAngle__Fi]  size=0xb8 */
float GetRotAngle__Fi(uint param_1)

{
  undefined4 uStack_14;
  
  param_1 = param_1 & 0x1f;
  if (param_1 < 0x11) {
    uStack_14 = (float)param_1 * 3.141592;
  }
  else {
    uStack_14 = (float)(int)(0x20 - param_1) * -3.141592;
  }
  uStack_14 = uStack_14 / 16.0;
  return uStack_14;
}

/* JP: 0x004c7e40  checkKind(const char*)   [checkKind__FPCc]  size=0xcc */
int checkKind__FPCc(undefined4 param_1)

{
  undefined8 uVar1;
  long lVar2;
  char *pcVar3;
  int iVar4;
  undefined1 auStack_18 [8];
  undefined4 uStack_10;
  
  uStack_10 = param_1;
  memset(auStack_18,0x20,8);
  uVar1 = strlen(uStack_10);
  memcpy(auStack_18,uStack_10,uVar1);
  iVar4 = 0;
  pcVar3 = evKindTbl;
  while( true ) {
    if (*pcVar3 == '\0') {
      return -1;
    }
    lVar2 = memcmp(pcVar3,auStack_18,8);
    if (lVar2 == 0) break;
    iVar4 = iVar4 + 1;
    pcVar3 = pcVar3 + 8;
  }
  return iVar4;
}

/* JP: 0x004ca4f0  GetRand(int)   [GetRand__Fi]  size=0x3c */
int GetRand__Fi(int param_1)

{
  uint uVar1;
  
  uVar1 = rand();
  return (int)(param_1 * (uVar1 & 0xffff)) >> 0x10;
}

/* JP: 0x004ca530  CalcModelBBox(Model*, float*)   [CalcModelBBox__FP5ModelPf]  size=0x2a8 */
void CalcModelBBox__FP5ModelPf(int param_1,float *param_2)

{
  int iVar1;
  int iVar2;
  byte *pbVar3;
  int iVar4;
  byte *pbVar5;
  int iVar6;
  undefined1 auStack_80 [16];
  float fStack_70;
  float fStack_6c;
  float fStack_68;
  undefined4 uStack_64;
  undefined1 auStack_60 [64];
  int iStack_20;
  float *pfStack_10;
  
  iVar1 = *(int *)(*(int *)(param_1 + 0x60) + 4);
  param_2[2] = 99999.9;
  param_2[1] = 99999.9;
  *param_2 = 99999.9;
  param_2[5] = -99999.9;
  param_2[4] = -99999.9;
  param_2[3] = -99999.9;
  pbVar3 = *(byte **)(param_1 + 0xe4);
  iStack_20 = param_1;
  pfStack_10 = param_2;
  __ct__6MatrixFv(auStack_60);
  iVar2 = iRam00430020;
  for (iVar6 = 1; pbVar3 = pbVar3 + 0x110, iVar6 < iVar1; iVar6 = iVar6 + 1) {
    __as__6MatrixFRC6Matrix
              (auStack_60,*(int *)(iStack_20 + 0x30) + (uint)*pbVar3 * 0x1f0 + iVar2 * 0x40);
    pbVar5 = pbVar3;
    for (iVar4 = 0; pbVar5 = pbVar5 + 0x10, iVar4 < 8; iVar4 = iVar4 + 1) {
      __ct__7FVectorFv(&fStack_70);
      memcpy(&fStack_70,pbVar5,0x10);
      uStack_64 = 0x3f800000;
      ApplyMatrix__6MatrixCFRC7FVector(auStack_80,auStack_60,&fStack_70);
      __as__7FVectorFRC7FVector(&fStack_70,auStack_80);
      if (fStack_70 < *pfStack_10) {
        *pfStack_10 = fStack_70;
      }
      if (pfStack_10[3] < fStack_70) {
        pfStack_10[3] = fStack_70;
      }
      if (fStack_6c < pfStack_10[1]) {
        pfStack_10[1] = fStack_6c;
      }
      if (pfStack_10[4] < fStack_6c) {
        pfStack_10[4] = fStack_6c;
      }
      if (fStack_68 < pfStack_10[2]) {
        pfStack_10[2] = fStack_68;
      }
      if (pfStack_10[5] < fStack_68) {
        pfStack_10[5] = fStack_68;
      }
    }
  }
  return;
}

/* JP: 0x004cc820  clear__Q28CBalIcon6_flagsFv   [clear__Q28CBalIcon6_flagsFv]  size=0x1c */
void clear__Q28CBalIcon6_flagsFv(undefined2 *param_1)

{
  *param_1 = 0;
  return;
}

/* JP: 0x004cdcc0  CnvY(unsigned int)   [CnvY__FUi]  size=0x1b4 */
int CnvY__FUi(uint param_1)

{
  uint uVar1;
  undefined4 uStack_14;
  
  uStack_14 = ((float)(int)(((param_1 >> 0x10 & 0xff) * 0x1d +
                             (param_1 & 0xff) * 0x4d + (param_1 >> 8 & 0xff) * 0x96 >> 8) - 0x80) *
               1.3 + 128.0) / 200.0;
  uStack_14 = uStack_14 * uStack_14;
  if (uStack_14 < 0.0) {
    uStack_14 = 0.0;
  }
  if (1.0 < uStack_14) {
    uStack_14 = 1.0;
  }
  uStack_14 = uStack_14 * 255.0;
  if (uStack_14 < 2.1474836e+09) {
    uVar1 = (uint)uStack_14;
  }
  else {
    uVar1 = (int)(uStack_14 - 2.1474836e+09) | 0x80000000;
  }
  return (param_1 & 0xff000000) + uVar1 * 0x10101;
}

/* JP: 0x004cde80  CnvModelGray(Model*)   [CnvModelGray__FP5Model]  size=0xfc */
void CnvModelGray__FP5Model(undefined4 param_1)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  long lVar5;
  undefined4 *puVar6;
  int iVar7;
  int iVar8;
  
  iVar3 = GetTextureCount__5ModelFv(param_1);
  for (iVar7 = 0; iVar7 < iVar3; iVar7 = iVar7 + 1) {
    lVar5 = GetTexture__5ModelFi(param_1,iVar7);
    if ((lVar5 != 0) && (puVar1 = *(undefined4 **)((int)lVar5 + 0xc), puVar1 != (undefined4 *)0x0))
    {
      puVar6 = (undefined4 *)*puVar1;
      iVar2 = puVar1[1];
      for (iVar8 = 0; iVar8 < iVar2; iVar8 = iVar8 + 1) {
        uVar4 = CnvY__FUi(*puVar6);
        *puVar6 = uVar4;
        puVar6 = puVar6 + 1;
      }
    }
  }
  return;
}

/* JP: 0x004cf0f0  CreateFldBGEffect(int, void*)   [CreateFldBGEffect__FiPv]  size=0xa8 */
undefined8 CreateFldBGEffect__FiPv(int param_1,undefined4 param_2)

{
  long lVar1;
  undefined8 uVar2;
  
  uVar2 = 0;
  if (param_1 == 0x100) {
    lVar1 = __nw__FUi(0x48);
    uVar2 = 0;
    if (lVar1 != 0) {
      uVar2 = __ct__14BgeffLightPrimFPv(lVar1,param_2);
    }
    AddPrim__11PutiManagerFiP8PutiPrim(eff__11BgEffectMan,10,uVar2);
  }
  return uVar2;
}

/* JP: 0x004d0560  GetColVector(FVector*, unsigned int)   [GetColVector__FP7FVectorUi]  size=0x144 */
/* WARNING: Removing unreachable block (ram,0x004d0674) */
/* WARNING: Removing unreachable block (ram,0x004d05dc) */
/* WARNING: Removing unreachable block (ram,0x004d0590) */
/* WARNING: Removing unreachable block (ram,0x004d0628) */

void GetColVector__FP7FVectorUi(float *param_1,uint param_2)

{
  *param_1 = (float)(param_2 & 0xff);
  param_1[1] = (float)(param_2 >> 8 & 0xff);
  param_1[2] = (float)(param_2 >> 0x10 & 0xff);
  param_1[3] = (float)(param_2 >> 0x18);
  return;
}

/* JP: 0x004d36b0  HalfCol(unsigned int)   [HalfCol__FUi]  size=0x40 */
int HalfCol__FUi(uint param_1)

{
  return (param_1 >> 1 & 0x7f7f7f) + (param_1 & 0xff000000);
}

/* JP: 0x004d4130  GetRotMatrix(Matrix&, int)   [GetRotMatrix__FR6Matrixi]  size=0x84 */
void GetRotMatrix__FR6Matrixi(undefined4 param_1,int param_2)

{
  undefined4 uStack_10;
  
  UnitMatrix__6MatrixFv(param_1);
  uStack_10 = param_2;
  if (0xb4 < param_2) {
    uStack_10 = 0x168 - param_2;
  }
  RotZMatrix__6MatrixFf((float)uStack_10 * 0.017453289,param_1);
  return;
}

/* JP: 0x004d5600  GetBgmFileName(char*, const char*)   [GetBgmFileName__FPcPCc]  size=0x3c */
void GetBgmFileName__FPcPCc(undefined4 param_1,undefined4 param_2)

{
  sprintf(param_1,0x558f80,pDataPath__7SysTool,param_2);
  return;
}

/* JP: 0x004d5640  GetSeFileName(char*, const char*)   [GetSeFileName__FPcPCc]  size=0x3c */
void GetSeFileName__FPcPCc(undefined4 param_1,undefined4 param_2)

{
  sprintf(param_1,0x558fa0,pDataPath__7SysTool,param_2);
  return;
}

/* JP: 0x004d5680  cbReadBGM(int, BufMemory*, int, char*, void*)   [cbReadBGM__FiP9BufMemoryiPcPv]  size=0x28 */
undefined8 cbReadBGM__FiP9BufMemoryiPcPv(void)

{
  OnLoadBGM__6CFieldFv(sys__6CField);
  return 0;
}

/* JP: 0x004d5730  GetObjSeSize(SDB::tagFOBJSE*)   [GetObjSeSize__FPQ23SDB9tagFOBJSE]  size=0x88 */
int GetObjSeSize__FPQ23SDB9tagFOBJSE(int param_1)

{
  int iVar1;
  
  if ((*(byte *)(param_1 + 4) & 0xf) < 2) {
    iVar1 = 2;
  }
  else {
    iVar1 = 3;
  }
  if ((*(byte *)(param_1 + 4) & 0xf) == 2) {
    iVar1 = (uint)(((ulong)*(byte *)(param_1 + 4) << 0x38) >> 0x3c) + 1;
  }
  return iVar1;
}

/* JP: 0x004d60e0  Exp3DVolume(FVector, FVector, FVector, int&, int&, int)   [Exp3DVolume__F7FVector7FVector7FVectorRiRii]  size=0x500 */
void Exp3DVolume__F7FVector7FVector7FVectorRiRii
               (undefined4 param_1,undefined4 param_2,int param_3,int *param_4,int *param_5,
               int param_6)

{
  int iVar1;
  int iVar2;
  float fVar3;
  undefined1 auStack_c0 [16];
  undefined1 auStack_b0 [4];
  float fStack_ac;
  undefined1 auStack_a0 [4];
  undefined4 uStack_9c;
  undefined1 auStack_90 [16];
  undefined1 auStack_80 [24];
  float fStack_68;
  float fStack_64;
  undefined4 uStack_60;
  undefined4 uStack_50;
  int iStack_40;
  int *piStack_30;
  int *piStack_20;
  int iStack_10;
  
  *param_4 = 0x7f;
  *param_5 = 0x40;
  uStack_60 = param_1;
  uStack_50 = param_2;
  iStack_40 = param_3;
  piStack_30 = param_4;
  piStack_20 = param_5;
  iStack_10 = param_6;
  __ct__7FVectorFv(auStack_80);
  __ct__7FVectorFv(auStack_90);
  __mi__7FVectorCFRC7FVector(auStack_a0,uStack_50,uStack_60);
  fStack_68 = (float)Length__7FVectorCFv(auStack_a0);
  uStack_9c = 0;
  fStack_64 = (float)Length__7FVectorCFv(auStack_a0);
  if (iStack_10 == 2) {
    if (30.0 < fStack_68) {
      fStack_68 = 1.0 / ((fStack_68 - 29.0) * (fStack_68 - 29.0) * 0.005);
      *piStack_30 = (int)(fStack_68 * 128.0);
    }
  }
  else if (iStack_10 == 1) {
    if (20.0 < fStack_68) {
      fStack_68 = 1.0 / ((fStack_68 - 19.0) * (fStack_68 - 19.0) * 0.001);
      *piStack_30 = (int)(fStack_68 * 128.0);
    }
  }
  else if ((iStack_10 == 0) && (50.0 < fStack_68)) {
    fStack_68 = fStack_68 - 50.0;
    *piStack_30 = (int)((1.0 - fStack_68 * 0.008) * 128.0);
  }
  if (*piStack_30 < 0x50) {
    *piStack_30 = (*piStack_30 >> 1) + 0x28;
  }
  if (0x80 < *piStack_30) {
    *piStack_30 = 0x80;
  }
  Normalize__7FVectorFv(auStack_a0);
  Normalize__7FVectorFv(iStack_40);
  __ct__7FVectorFv(auStack_b0);
  OuterProduct__7FVectorCFRC7FVector(auStack_c0,auStack_a0,iStack_40);
  __as__7FVectorFRC7FVector(auStack_b0,auStack_c0);
  *(undefined4 *)(iStack_40 + 4) = 0;
  uStack_9c = 0;
  Normalize__7FVectorFv(iStack_40);
  Normalize__7FVectorFv(auStack_a0);
  fVar3 = (float)InnerProduct__7FVectorCFRC7FVector(auStack_a0,iStack_40);
  if (fStack_ac < 0.0) {
    fVar3 = fVar3 * 64.0;
    if (0.0 <= fVar3) {
      *piStack_20 = 0x7f - (int)fVar3;
    }
    else {
      *piStack_20 = -0x7f - (int)fVar3;
    }
  }
  else {
    *piStack_20 = (int)(fVar3 * 64.0);
  }
  if (fStack_64 < 40.0) {
    if (*piStack_20 < 0) {
      iVar2 = -*piStack_20;
    }
    else {
      iVar2 = *piStack_20;
    }
    if (*piStack_20 < 0) {
      iVar1 = -1;
    }
    else {
      iVar1 = 1;
    }
    *piStack_20 = iVar1 * ((int)((float)(iVar2 + -0x40) * (fStack_64 / 40.0)) + 0x40);
  }
  return;
}

/* JP: 0x004d65e0  Calc3DPosition(FVector*, FVector*, _ObjSE*)   [Calc3DPosition__FP7FVectorP7FVectorP6_ObjSE]  size=0xc70 */
float Calc3DPosition__FP7FVectorP7FVectorP6_ObjSE(undefined4 *param_1,int param_2,int param_3)

{
  float fVar1;
  undefined8 uVar2;
  byte bVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  undefined4 uVar8;
  undefined1 auStack_330 [16];
  undefined1 auStack_320 [16];
  undefined1 auStack_310 [16];
  undefined1 auStack_300 [16];
  undefined1 auStack_2f0 [16];
  undefined1 auStack_2e0 [16];
  undefined1 auStack_2d0 [16];
  undefined1 auStack_2c0 [16];
  undefined1 auStack_2b0 [16];
  undefined1 auStack_2a0 [16];
  undefined1 auStack_290 [16];
  undefined1 auStack_280 [16];
  undefined1 auStack_270 [16];
  undefined1 auStack_260 [16];
  undefined1 auStack_250 [16];
  undefined1 auStack_240 [16];
  undefined1 auStack_230 [16];
  undefined1 auStack_220 [16];
  undefined1 auStack_210 [16];
  undefined1 auStack_200 [16];
  undefined1 auStack_1f0 [16];
  undefined1 auStack_1e0 [16];
  undefined1 auStack_1d0 [16];
  undefined1 auStack_1c0 [16];
  undefined1 auStack_1b0 [16];
  undefined1 auStack_1a0 [16];
  undefined1 auStack_190 [16];
  undefined1 auStack_180 [16];
  undefined1 auStack_170 [64];
  undefined1 auStack_130 [64];
  undefined1 auStack_f0 [4];
  float fStack_ec;
  undefined1 auStack_e0 [4];
  undefined4 uStack_dc;
  undefined4 uStack_d4;
  undefined1 auStack_d0 [16];
  undefined1 auStack_c0 [16];
  undefined1 auStack_b0 [4];
  undefined4 uStack_ac;
  undefined4 uStack_a4;
  undefined1 auStack_a0 [4];
  undefined4 uStack_9c;
  undefined4 uStack_90;
  undefined4 uStack_8c;
  float fStack_88;
  float fStack_84;
  undefined1 auStack_80 [16];
  float fStack_70;
  float fStack_6c;
  float fStack_68;
  float fStack_64;
  float fStack_60;
  float fStack_5c;
  float fStack_58;
  undefined4 uStack_54;
  float fStack_50;
  float fStack_4c;
  float fStack_48;
  float fStack_44;
  float fStack_40;
  float fStack_3c;
  float fStack_38;
  float fStack_34;
  undefined4 *puStack_30;
  int iStack_20;
  int iStack_10;
  
  fStack_34 = 1.0;
  puStack_30 = param_1;
  iStack_20 = param_2;
  iStack_10 = param_3;
  __ct__7FVectorFv(auStack_80);
  __ct__7FVectorFv(auStack_b0);
  __ct__7FVectorFv(auStack_a0);
  __ct__7FVectorFv(&uStack_90);
  bVar3 = *(byte *)(iStack_10 + 8) & 0xf;
  if ((bVar3 == 3) || (bVar3 == 2)) {
    GetShortPos__FP7FVectorPs(iStack_20,iStack_10 + 10);
    GetShortPos__FP7FVectorPs(&uStack_90,iStack_10 + 0x10);
    __ct__6MatrixFv(auStack_170);
    UnitMatrix__6MatrixFv(auStack_170);
    uVar8 = GetRad(uStack_90);
    uVar2 = RotXMatrix__6MatrixFf(uVar8,auStack_170);
    uVar8 = GetRad(uStack_8c,uVar2);
    RotYMatrix__6MatrixFf(uVar8,auStack_170);
    uVar2 = __ct__7FVectorFffff(0,0,0x3f800000,0x3f800000,auStack_300);
    ApplyMatrix__6MatrixCFRC7FVector(auStack_2f0,auStack_170,uVar2);
    __as__7FVectorFRC7FVector(auStack_a0,auStack_2f0);
    __mi__7FVectorCFRC7FVector(auStack_310,puStack_30,iStack_20);
    __as__7FVectorFRC7FVector(auStack_b0,auStack_310);
    uVar2 = Normalize__7FVectorFv(auStack_a0);
    uStack_ac = 0;
    fStack_60 = (float)Length__7FVectorCFv(auStack_b0,uVar2);
    Normalize__7FVectorFv(auStack_b0);
    fStack_64 = (float)InnerProduct__7FVectorCFRC7FVector(auStack_a0,auStack_b0);
    if (fStack_64 < 0.0) {
      if ((*(byte *)(iStack_10 + 8) & 0xf) != 3) {
        fStack_34 = 0.0;
        goto LAB_004d7210;
      }
      __amu__7FVectorFf(0xbf800000,auStack_a0);
    }
    __ml__7FVectorCFf(fStack_60 * fStack_64,auStack_330,auStack_a0);
    __pl__7FVectorCFRC7FVector(auStack_320,iStack_20,auStack_330);
    __as__7FVectorFRC7FVector(&uStack_90,auStack_320);
    *puStack_30 = uStack_90;
    puStack_30[2] = fStack_88;
    GetShortPos4__FP7FVectorPs(&uStack_90,iStack_10 + 0x10);
    uVar8 = acosf(fStack_64);
    fStack_68 = (float)sinf(uVar8);
    fStack_68 = fStack_60 * fStack_68;
    if (fStack_88 * 0.5 <= fStack_68) {
      fStack_84 = (float)GetRad(fStack_84);
      fStack_68 = (float)acosf(fStack_64);
      fStack_68 = fStack_68 - fStack_84;
      if (fStack_84 < fStack_68) {
        fStack_34 = 0.0;
      }
      else {
        fStack_64 = -fStack_84;
        fStack_34 = (fStack_68 + fStack_64) / fStack_64;
      }
    }
  }
  else if (bVar3 == 1) {
    GetShortPos__FP7FVectorPs(iStack_20,iStack_10 + 10);
    GetShortPos4__FP7FVectorPs(&uStack_90,iStack_10 + 0x10);
    __ct__6MatrixFv(auStack_130);
    UnitMatrix__6MatrixFv(auStack_130);
    uVar8 = GetRad(uStack_8c);
    RotXMatrix__6MatrixFf(uVar8,auStack_130);
    uVar8 = GetRad(uStack_90);
    RotYMatrix__6MatrixFf(uVar8,auStack_130);
    uVar2 = __ct__7FVectorFffff(0,0,0x3f800000,0x3f800000,auStack_2d0);
    ApplyMatrix__6MatrixCFRC7FVector(auStack_2c0,auStack_130,uVar2);
    __as__7FVectorFRC7FVector(auStack_a0,auStack_2c0);
    __mi__7FVectorCFRC7FVector(auStack_2e0,puStack_30,iStack_20);
    __as__7FVectorFRC7FVector(auStack_80,auStack_2e0);
    Normalize__7FVectorFv(auStack_a0);
    Normalize__7FVectorFv(auStack_80);
    fStack_58 = (float)InnerProduct__7FVectorCFRC7FVector(auStack_80,auStack_a0);
    fStack_88 = (float)GetRad(fStack_88);
    fStack_5c = (float)acosf(fStack_58);
    fStack_5c = fStack_5c - fStack_88;
    if (0.0 < fStack_5c) {
      fStack_84 = (float)GetRad(fStack_84);
      if (fStack_84 < fStack_5c) {
        fStack_34 = 0.0;
      }
      else {
        fStack_58 = -fStack_84;
        fStack_34 = (fStack_5c + fStack_58) / fStack_58;
      }
    }
  }
  else if ((*(byte *)(iStack_10 + 8) & 0xf) == 0) {
    bVar3 = *(byte *)(iStack_10 + 8);
    uVar6 = (uint)(bVar3 >> 4);
    __ct__7FVectorFv(auStack_c0);
    __ct__7FVectorFv(auStack_d0);
    if (uVar6 == 1) {
      GetShortPos__FP7FVectorPs(iStack_20,iStack_10 + 10);
    }
    else {
      iVar7 = -1;
      for (iVar5 = 0; iVar5 < (int)uVar6; iVar5 = iVar5 + 1) {
        GetShortPos__FP7FVectorPs(auStack_80,iStack_10 + iVar5 * 6 + 10);
        __ami__7FVectorFRC7FVector(auStack_80,puStack_30);
        fStack_44 = (float)Length__7FVectorCFv(auStack_80);
        iVar4 = iVar5;
        fVar1 = fStack_44;
        if ((-1 < iVar7) && (fVar1 = fStack_44, fStack_38 <= fStack_44)) {
          iVar4 = iVar7;
          fVar1 = fStack_38;
        }
        fStack_38 = fVar1;
        iVar7 = iVar4;
      }
      memset(auStack_b0,0,0x30);
      uStack_a4 = 0x3f800000;
      fStack_84 = 1.0;
      GetShortPos__FP7FVectorPs(auStack_a0,iStack_10 + iVar7 * 6 + 10);
      if (0 < iVar7) {
        GetShortPos__FP7FVectorPs(auStack_b0,iStack_10 + (iVar7 * 3 + -3) * 2 + 10);
      }
      uVar6 = (uint)(((ulong)bVar3 << 0x38) >> 0x3c);
      if (iVar7 < (int)(uVar6 - 1)) {
        GetShortPos__FP7FVectorPs(&uStack_90,iStack_10 + (iVar7 * 3 + 3) * 2 + 10);
      }
      __mi__7FVectorCFRC7FVector(auStack_190,puStack_30,auStack_a0);
      __as__7FVectorFRC7FVector(auStack_80,auStack_190);
      __mi__7FVectorCFRC7FVector(auStack_1a0,auStack_b0,auStack_a0);
      __as__7FVectorFRC7FVector(auStack_c0,auStack_1a0);
      __mi__7FVectorCFRC7FVector(auStack_1b0,&uStack_90,auStack_a0);
      __as__7FVectorFRC7FVector(auStack_d0,auStack_1b0);
      fStack_38 = (float)Length__7FVectorCFv(auStack_80);
      fStack_48 = (float)Length__7FVectorCFv(auStack_c0);
      fStack_4c = (float)Length__7FVectorCFv(auStack_d0);
      Normalize__7FVectorFv(auStack_80);
      Normalize__7FVectorFv(auStack_c0);
      Normalize__7FVectorFv(auStack_d0);
      fStack_40 = -1.0;
      fStack_3c = -1.0;
      if (0 < iVar7) {
        fStack_3c = (float)InnerProduct__7FVectorCFRC7FVector(auStack_c0,auStack_80);
      }
      if (iVar7 < (int)(uVar6 - 1)) {
        fStack_40 = (float)InnerProduct__7FVectorCFRC7FVector(auStack_d0,auStack_80);
      }
      if ((0.0 <= fStack_3c) || (0.0 <= fStack_40)) {
        if ((fStack_3c <= 0.0) || (fStack_40 <= 0.0)) {
          if (0.0 < fStack_3c) {
            __ml__7FVectorCFf(fStack_38 * fStack_3c,auStack_290,auStack_c0);
            __pl__7FVectorCFRC7FVector(auStack_280,auStack_a0,auStack_290);
            __as__7FVectorFRC7FVector(iStack_20,auStack_280);
          }
          else {
            __ml__7FVectorCFf(fStack_38 * fStack_40,auStack_2b0,auStack_d0);
            __pl__7FVectorCFRC7FVector(auStack_2a0,auStack_a0,auStack_2b0);
            __as__7FVectorFRC7FVector(iStack_20,auStack_2a0);
          }
        }
        else {
          __ct__7FVectorFv(auStack_e0);
          __ct__7FVectorFv(auStack_f0);
          __ml__7FVectorCFf(fStack_38 * fStack_3c,auStack_1d0,auStack_c0);
          __pl__7FVectorCFRC7FVector(auStack_1c0,auStack_a0,auStack_1d0);
          __as__7FVectorFRC7FVector(auStack_b0,auStack_1c0);
          __ml__7FVectorCFf(fStack_38 * fStack_40,auStack_1f0,auStack_d0);
          __pl__7FVectorCFRC7FVector(auStack_1e0,auStack_a0,auStack_1f0);
          __as__7FVectorFRC7FVector(&uStack_90,auStack_1e0);
          __pl__7FVectorCFRC7FVector(auStack_210,auStack_c0,auStack_d0);
          __ml__7FVectorCFf(0x3f000000,auStack_200,auStack_210);
          __as__7FVectorFRC7FVector(auStack_e0,auStack_200);
          OuterProduct__7FVectorCFRC7FVector(auStack_220,auStack_e0,auStack_80);
          __as__7FVectorFRC7FVector(auStack_f0,auStack_220);
          fStack_3c = (fStack_3c * fStack_38) / fStack_48;
          fStack_40 = (fStack_40 * fStack_38) / fStack_4c;
          iVar7 = 0;
          fStack_50 = fStack_3c;
          if (fStack_ec < 0.0) {
            iVar7 = 2;
            fStack_50 = fStack_40;
          }
          if (0.5 < fStack_50) {
            __as__7FVectorFRC7FVector(iStack_20,auStack_b0 + iVar7 * 0x10);
          }
          else {
            uStack_54 = uStack_dc;
            Normalize__7FVectorFv(auStack_e0);
            if (fStack_4c < fStack_48) {
              fStack_6c = fStack_48;
            }
            else {
              fStack_6c = fStack_4c;
            }
            __ml__7FVectorCFf(fStack_6c,auStack_240,auStack_e0);
            __pl__7FVectorCFRC7FVector(auStack_230,auStack_a0,auStack_240);
            __as__7FVectorFRC7FVector(auStack_e0,auStack_230);
            uStack_d4 = 0x3f800000;
            __mi__7FVectorCFRC7FVector(auStack_250,puStack_30,auStack_e0);
            __as__7FVectorFRC7FVector(auStack_e0,auStack_250);
            Normalize__7FVectorFv(auStack_e0);
            if (iVar7 == 0) {
              fStack_70 = fStack_48;
            }
            else {
              fStack_70 = fStack_4c;
            }
            fStack_50 = fStack_50 * fStack_70;
            __ml__7FVectorCFf(fStack_50,auStack_270,auStack_e0);
            __pl__7FVectorCFRC7FVector(auStack_260,puStack_30,auStack_270);
            __as__7FVectorFRC7FVector(iStack_20,auStack_260);
            *(undefined4 *)(iStack_20 + 4) = uStack_9c;
          }
        }
      }
      else {
        __as__7FVectorFRC7FVector(iStack_20,auStack_a0);
      }
      *(undefined4 *)(iStack_20 + 0xc) = 0x3f800000;
    }
  }
LAB_004d7210:
  __ct__7FVectorFRC7FVector(auStack_180,puStack_30);
  return fStack_34;
}

/* JP: 0x004d7250  Exp3DVolumeC(FVector&, FVector&, FVector&, float)   [Exp3DVolumeC__FR7FVectorR7FVectorR7FVectorf]  size=0x130 */
float Exp3DVolumeC__FR7FVectorR7FVectorR7FVectorf
                (float param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  float fVar1;
  undefined1 auStack_60 [24];
  float fStack_48;
  undefined4 uStack_40;
  undefined4 uStack_30;
  undefined4 uStack_20;
  float fStack_10;
  
  if (param_1 == 0.0) {
    fStack_48 = 1.0;
  }
  else {
    uStack_40 = param_2;
    uStack_30 = param_3;
    uStack_20 = param_4;
    fStack_10 = param_1;
    __mi__7FVectorCFRC7FVector(auStack_60,param_4,param_2);
    Normalize__7FVectorFv(auStack_60);
    fVar1 = (float)InnerProduct__7FVectorCFRC7FVector(uStack_30,auStack_60);
    fStack_48 = 1.0;
    if (fVar1 < fStack_10) {
      if (0.0 <= fVar1) {
        fStack_48 = (fVar1 / fStack_10) * 0.3 + 0.7;
      }
      else {
        fStack_48 = fVar1 * 0.2 + 0.7;
      }
    }
  }
  return fStack_48;
}

/* JP: 0x004da260  cbReplace(Effect*, void*, int)   [cbReplace__FP6EffectPvi]  size=0x2c */
void cbReplace__FP6EffectPvi(undefined4 param_1,int param_2)

{
  *(undefined4 *)(param_2 + 4) = param_1;
  return;
}

/* JP: 0x004daec0  CheckMirrorNormal(FVector&)   [CheckMirrorNormal__FR7FVector]  size=0xec */
undefined1 CheckMirrorNormal__FR7FVector(float *param_1)

{
  undefined1 uVar1;
  float fStack_1c;
  float fStack_18;
  float fStack_14;
  
  fStack_14 = *param_1;
  if (fStack_14 < 0.0) {
    fStack_14 = -fStack_14;
  }
  fStack_18 = param_1[1];
  if (fStack_18 < 0.0) {
    fStack_18 = -fStack_18;
  }
  fStack_1c = param_1[2];
  if (fStack_1c < 0.0) {
    fStack_1c = -fStack_1c;
  }
  uVar1 = fStack_14 < fStack_18;
  if ((bool)uVar1) {
    fStack_14 = fStack_18;
  }
  if (fStack_14 < fStack_1c) {
    uVar1 = 2;
  }
  return uVar1;
}
