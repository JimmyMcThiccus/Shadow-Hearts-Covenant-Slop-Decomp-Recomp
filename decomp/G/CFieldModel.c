/* ==== CLEANED excerpts: movement/collision (port: sh2_field/src/movement.rs) ==== */
#include "_types.h"
/* JP 0x004ca3c0 CFieldModel::FloorChk -- snap to the floor and rebuild the frame matrix */
void CFieldModel_FloorChk(CFieldModel *t) {
    CFloorMan *fl = sys__6CField->floor;
    SDB_tagFTRIANGLE *tri = CFloorMan_OnFloorChk(fl, t->pos);
    if (!tri) return;
    t->pos.y = CFloorMan_OnFloorPoint(fl, t->pos, tri);
    Matrix m; UnitMatrix(&m); RotXMatrix(&m, t->rot.x); RotYMatrix(&m, t->rot.y); RotZMatrix(&m, t->rot.z); TransMatrix(&m, &t->pos);
    Frame *f = CFieldModel_GetFrame(t); f->local = m; Frame_myMatrixUpdate(f);
}
/* JP 0x004cb410 CFieldModel::TransCallBack(const FVector &trans, FVector &out) -- floor part only (hold/auto-move/collision omitted) */
FVector CFieldModel_TransCallBack_floor(CFieldModel *t, FVector *trans) {
    CFloorMan *fl = sys__6CField->floor; FVector old = t->pos; t->slope_scale = 1.0f;
    if (CFieldModel_isFloorChk(t) && t->attach_slot == -1 && !t->move_mode && fl) {
        SDB_tagFTRIANGLE *tri = CFloorMan_OnFloorChk(fl, t->pos);
        if (tri) {
            float h0 = CFloorMan_OnFloorPoint(fl, t->pos, tri);
            FVector behind = { old.x - sinf(t->move_rot.y), old.y, old.z - cosf(t->move_rot.y), 1 };
            SDB_tagFTRIANGLE *t2 = CFloorMan_OnFloorChk(fl, behind);
            if (t2) { float dh = h0 - CFloorMan_OnFloorPoint(fl, behind, t2); if (dh < 0) dh *= -0.5f; t->slope_scale = 1.2f / (dh + 1.2f); }
        }
    }
    trans->z *= t->slope_scale;
    Matrix m; UnitMatrix(&m); RotXMatrix(&m, t->move_rot.x); RotYMatrix(&m, t->move_rot.y); RotZMatrix(&m, t->move_rot.z);
    FVector step = ApplyMatrix(&m, trans);
    /* ... auto-move / path-move clamp, HitChkM2M, then: */
    t->pos.x += step.x; t->pos.y += step.y; t->pos.z += step.z;
    FVector f0 = step, c1 = step, c2 = step; SDB_tagFTRIANGLE *found = 0;
    for (int i = 0; i < 13; i++) {                                                  /* wall sliding */
        FVector p1 = { old.x + c1.x, old.y, old.z + c1.z, 1 }, p2 = { old.x + c2.x, old.y, old.z + c2.z, 1 };
        SDB_tagFTRIANGLE *ok1 = CFloorMan_CircleChk(fl, p1, 4.0f), *ok2 = CFloorMan_CircleChk(fl, p2, 4.0f);
        f0.x *= 0.91f; f0.z *= 0.91f;
        if (ok1 && ok2) { FVector p = { old.x + f0.x, old.y, old.z + f0.z, 1 }; if ((found = CFloorMan_CircleChk(fl, p, 4.0f))) break; }
        if (ok1 && !ok2) { f0 = c1; found = ok1; break; }
        if (!ok1 && ok2) { f0 = c2; found = ok2; break; }
        float h = c1.x + c1.z * 0.11f;  c1.x = h * 0.91f;  c1.z = (c1.z - h * 0.11f) * 0.91f;      /* rotate the candidates apart */
        float z = c2.z + c2.x * 0.11f;  c2.x = (c2.x - z * 0.11f) * 0.91f;  c2.z = z * 0.91f;
    }
    FVector np = { old.x + f0.x, old.y, old.z + f0.z, 1 }; SDB_tagFTRIANGLE *tri = found ? CFloorMan_CircleChk(fl, np, 4.0f) : 0;
    if (!tri) { t->pos = old; return (FVector){0, 0, 0, 1}; }                       /* blocked: stay */
    t->pos = np; t->pos.y = CFloorMan_OnFloorPoint(fl, np, tri);
    return f0;
}


/* ==== RAW (Ghidra output, names/globals resolved; not hand-cleaned) ==== */
/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CFieldModel   functions: 111
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CFieldModel.md).
 */

/* JP: 0x004a3630  CFieldModel::GetPos()   [GetPos__11CFieldModelFv]  size=0x34 */
void GetPos__11CFieldModelFv(undefined4 param_1,int param_2)

{
  __ct__7FVectorFRC7FVector(param_1,param_2 + 0x10);
  return;
}

/* JP: 0x004a3670  CFieldModel::isDsp()   [isDsp__11CFieldModelFv]  size=0x24 */
ulong isDsp__11CFieldModelFv(int param_1)

{
  return ((ulong)*(byte *)(param_1 + 0x80) & 0xf) >> 2;
}

/* JP: 0x004a8230  CFieldModel::isAutoCtrl()   [isAutoCtrl__11CFieldModelFv]  size=0x24 */
ulong isAutoCtrl__11CFieldModelFv(int param_1)

{
  return ((ulong)*(byte *)(param_1 + 0x85) & 0xf) >> 2;
}

/* JP: 0x004a8260  CFieldModel::GetRot()   [GetRot__11CFieldModelFv]  size=0x34 */
void GetRot__11CFieldModelFv(undefined4 param_1,int param_2)

{
  __ct__7FVectorFRC7FVector(param_1,param_2 + 0x30);
  return;
}

/* JP: 0x004a82e0  CFieldModel::isManual()   [isManual__11CFieldModelFv]  size=0x64 */
undefined4 isManual__11CFieldModelFv(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if ((((ulong)*(byte *)(param_1 + 0x85) & 0xf) >> 2 == 0) && ((*(byte *)(param_1 + 0x88) & 1) != 0)
     ) {
    uVar1 = 1;
  }
  return uVar1;
}

/* JP: 0x004a8350  CFieldModel::isLoading()   [isLoading__11CFieldModelFv]  size=0x2c */
bool isLoading__11CFieldModelFv(int param_1)

{
  return (*(byte *)(param_1 + 0x80) & 3) == 1;
}

/* JP: 0x004a8380  CFieldModel::GetRotY()   [GetRotY__11CFieldModelFv]  size=0x1c */
undefined4 GetRotY__11CFieldModelFv(int param_1)

{
  return *(undefined4 *)(param_1 + 0x24);
}

/* JP: 0x004aa6a0  CFieldModel::GetMdlRot()   [GetMdlRot__11CFieldModelFv]  size=0x34 */
void GetMdlRot__11CFieldModelFv(undefined4 param_1,int param_2)

{
  __ct__7FVectorFRC7FVector(param_1,param_2 + 0x20);
  return;
}

/* JP: 0x004ab800  CFieldModel::GetModel()   [GetModel__11CFieldModelFv]  size=0x1c */
undefined4 GetModel__11CFieldModelFv(int param_1)

{
  return *(undefined4 *)(param_1 + 0x70);
}

/* JP: 0x004ac840  CFieldModel::isLoaded()   [isLoaded__11CFieldModelFv]  size=0x2c */
bool isLoaded__11CFieldModelFv(int param_1)

{
  return (*(byte *)(param_1 + 0x80) & 3) == 3;
}

/* JP: 0x004b0540  CFieldModel::isEmpty()   [isEmpty__11CFieldModelFv]  size=0x2c */
bool isEmpty__11CFieldModelFv(int param_1)

{
  return (*(byte *)(param_1 + 0x80) & 3) == 0;
}

/* JP: 0x004b0570  CFieldModel::ClrViewPoint()   [ClrViewPoint__11CFieldModelFv]  size=0x1c */
void ClrViewPoint__11CFieldModelFv(int param_1)

{
  *(undefined1 *)(param_1 + 0xf3) = 0;
  return;
}

/* JP: 0x004b0590  CFieldModel::SetManual(int)   [SetManual__11CFieldModelFi]  size=0x3c */
void SetManual__11CFieldModelFi(int param_1,byte param_2)

{
  *(byte *)(param_1 + 0x88) = *(byte *)(param_1 + 0x88) & 0xfe | param_2 & 1;
  return;
}

/* JP: 0x004b05d0  CFieldModel::SetCmd(int)   [SetCmd__11CFieldModelFi]  size=0x28 */
void SetCmd__11CFieldModelFi(int param_1,undefined1 param_2)

{
  *(undefined1 *)(param_1 + 0x91) = param_2;
  return;
}

/* JP: 0x004b0600  CFieldModel::SetMotionSpeed(float)   [SetMotionSpeed__11CFieldModelFf]  size=0x24 */
void SetMotionSpeed__11CFieldModelFf(undefined4 param_1,int param_2)

{
  *(undefined4 *)(param_2 + 0xb4) = param_1;
  return;
}

/* JP: 0x004b0630  CFieldModel::SetLastCmdEvent(unsigned int)   [SetLastCmdEvent__11CFieldModelFUi]  size=0x24 */
void SetLastCmdEvent__11CFieldModelFUi(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 0x118) = param_2;
  return;
}

/* JP: 0x004b3d10  CFieldModel::isMove()   [isMove__11CFieldModelFv]  size=0x24 */
ulong isMove__11CFieldModelFv(int param_1)

{
  return ((ulong)*(byte *)(param_1 + 0x85) & 0xf) >> 2;
}

/* JP: 0x004b3ff0  CFieldModel::isFloorChk()   [isFloorChk__11CFieldModelFv]  size=0x30 */
bool isFloorChk__11CFieldModelFv(int param_1)

{
  return ((ulong)*(byte *)(param_1 + 0x88) & 0x3f) >> 4 == 1;
}

/* JP: 0x004b4df0  CFieldModel::isHitChk()   [isHitChk__11CFieldModelFv]  size=0x24 */
ulong isHitChk__11CFieldModelFv(int param_1)

{
  return ((ulong)*(byte *)(param_1 + 0x88) & 0xf) >> 3;
}

/* JP: 0x004b4fc0  CFieldModel::SetHitCheck(int)   [SetHitCheck__11CFieldModelFi]  size=0x40 */
void SetHitCheck__11CFieldModelFi(int param_1,byte param_2)

{
  *(byte *)(param_1 + 0x88) = *(byte *)(param_1 + 0x88) & 0xf7 | (param_2 & 1) << 3;
  return;
}

/* JP: 0x004b5000  CFieldModel::SetFloorChk(int)   [SetFloorChk__11CFieldModelFi]  size=0x40 */
void SetFloorChk__11CFieldModelFi(int param_1,byte param_2)

{
  *(byte *)(param_1 + 0x88) = *(byte *)(param_1 + 0x88) & 0xcf | (param_2 & 3) << 4;
  return;
}

/* JP: 0x004c03e0  CFieldModel::ReadMotionCB(int, BufMemory*)   [ReadMotionCB__11CFieldModelFiP9BufMemory]  size=0x1ac */
undefined4 ReadMotionCB__11CFieldModelFiP9BufMemory(int param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  long lVar3;
  int *piVar4;
  uint uVar5;
  
  lVar3 = GetLoadQ__11CFieldModelFi(param_2);
  if (lVar3 == 0) {
    uVar2 = 0;
  }
  else if ((long)((ulong)*(byte *)(param_1 + 0x82) << 0x3b) < 0) {
    uVar2 = 0;
  }
  else {
    piVar4 = (int *)lVar3;
    iVar1 = *piVar4;
    if (param_3 != 0) {
      *(int *)(iVar1 + 8) = param_3;
    }
    if (*(int *)(iVar1 + 8) != 0) {
      ReadCB__11CFieldModelFP15_FieldDataCachei(param_1,iVar1,0);
    }
    for (uVar5 = 0; (int)uVar5 < 0x10; uVar5 = uVar5 + 1) {
      if (*(int *)(param_1 + uVar5 * 4 + 0x14c) == 0) {
        *(int *)(param_1 + uVar5 * 4 + 0x14c) = iVar1;
        if (*(int *)(iVar1 + 8) == 0) {
          *(ushort *)(param_1 + 0x94) = *(ushort *)(param_1 + 0x94) | (ushort)(1 << (uVar5 & 0x1f));
        }
        else {
          *(byte *)(param_1 + 0x8a) = *(byte *)(param_1 + 0x8a) & 0xef | 0x10;
        }
        break;
      }
    }
    if (piVar4[2] != 0) {
      (*(code *)piVar4[2])(0,piVar4[1],piVar4[3]);
    }
    PurgeLoadQ__11CFieldModelFi(param_2);
    uVar2 = 1;
  }
  return uVar2;
}

/* JP: 0x004c0590  CFieldModel::GetNewLoadQ(int&)   [GetNewLoadQ__11CFieldModelFRi]  size=0x90 */
int * GetNewLoadQ__11CFieldModelFRi(int *param_1)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)&m_loadQ__11CFieldModel;
  iVar2 = 0;
  while( true ) {
    if (0x1f < iVar2) {
      *param_1 = -1;
      return (int *)0x0;
    }
    if (*piVar1 == 0) break;
    iVar2 = iVar2 + 1;
    piVar1 = piVar1 + 4;
  }
  *param_1 = iVar2;
  return piVar1;
}

/* JP: 0x004c0620  CFieldModel::GetLoadQ(int)   [GetLoadQ__11CFieldModelFi]  size=0x5c */
undefined1 * GetLoadQ__11CFieldModelFi(int param_1)

{
  undefined1 *puVar1;
  
  if ((param_1 < 0) || (0x1f < param_1)) {
    puVar1 = (undefined1 *)0x0;
  }
  else {
    puVar1 = &m_loadQ__11CFieldModel + param_1 * 0x10;
  }
  return puVar1;
}

/* JP: 0x004c0680  CFieldModel::PurgeLoadQ(int)   [PurgeLoadQ__11CFieldModelFi]  size=0x2c */
void PurgeLoadQ__11CFieldModelFi(undefined4 param_1)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)GetLoadQ__11CFieldModelFi(param_1);
  *puVar1 = 0;
  return;
}

/* JP: 0x004c06b0  CFieldModel::CFieldModel()   [__ct__11CFieldModelFv]  size=0xb8 */
int __ct__11CFieldModelFv(int param_1)

{
  __ct__17DelayDeleteObjectFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__11CFieldModel;
  __ct__7FVectorFv(param_1 + 0x10);
  __ct__7FVectorFv(param_1 + 0x20);
  __ct__7FVectorFv(param_1 + 0x30);
  __ct__7FVectorFv(param_1 + 0x40);
  __ct__7FVectorFv(param_1 + 0x50);
  __ct__7FVectorFv(param_1 + 0x60);
  __ct__Q211CFieldModel7_memberFv(param_1 + 0x80);
  InitWork__11CFieldModelFv(param_1);
  return param_1;
}

/* JP: 0x004c0840  CFieldModel::InitWork()   [InitWork__11CFieldModelFv]  size=0x1a4 */
void InitWork__11CFieldModelFv(int param_1)

{
  undefined1 auStack_20 [16];
  int iStack_10;
  
  iStack_10 = param_1;
  __ct__7FVectorFffff(0,0,0,0x3f800000,auStack_20);
  __as__7FVectorFRC7FVector(iStack_10 + 0x10,auStack_20);
  __as__7FVectorFRC7FVector(iStack_10 + 0x20,auStack_20);
  __as__7FVectorFRC7FVector(iStack_10 + 0x30,auStack_20);
  __as__7FVectorFRC7FVector(iStack_10 + 0x40,auStack_20);
  *(undefined4 *)(iStack_10 + 0x2b0) = 0x3f800000;
  *(undefined4 *)(iStack_10 + 0x2b4) = 0x3f800000;
  *(undefined1 *)(iStack_10 + 700) = 0;
  memset(iStack_10 + 0x80,0,0x230);
  *(undefined1 *)(iStack_10 + 0x93) = 1;
  *(undefined1 *)(iStack_10 + 0x92) = 1;
  *(undefined4 *)(iStack_10 + 0xb4) = 0x3f800000;
  *(byte *)(iStack_10 + 0x85) = *(byte *)(iStack_10 + 0x85) & 0xcf | 0x30;
  *(byte *)(iStack_10 + 0x82) = *(byte *)(iStack_10 + 0x82) & 0xf9 | 2;
  memset(iStack_10 + 0xfc,0xff,3);
  *(undefined4 *)(iStack_10 + 0x70) = 0;
  SetHitCheck__11CFieldModelFi(iStack_10,1);
  *(undefined4 *)(iStack_10 + 0x2b8) = 0;
  SetMoveMotion__11CFieldModelFiii(iStack_10,1,2,3);
  strcpy(iStack_10 + 0x2cc,PTR__2959_00556014);
  return;
}

/* JP: 0x004c09f0  CFieldModel::~CFieldModel()   [__dt__11CFieldModelFv]  size=0xf4 */
int __dt__11CFieldModelFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__11CFieldModel;
    if ((((ulong)*(byte *)(param_1 + 0x82) & 0x7f) >> 5 != 0) && (*(int *)(param_1 + 0x144) != 0)) {
      __destroy_new_array(*(undefined4 *)(param_1 + 0x144),0x3d4010);
      *(undefined4 *)(param_1 + 0x144) = 0;
    }
    if (*(int *)(param_1 + 0x148) != 0) {
      Release__15_FieldDataCacheFv(*(undefined4 *)(param_1 + 0x148));
      *(undefined4 *)(param_1 + 0x148) = 0;
    }
    UnloadMotion__11CFieldModelFPCc(param_1,0);
    __dt__17DelayDeleteObjectFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x004c0af0  CFieldModel::Delete()   [Delete__11CFieldModelFv]  size=0x128 */
void Delete__11CFieldModelFv(int param_1)

{
  int iVar1;
  
  if (-1 < (long)((ulong)*(byte *)(param_1 + 0x82) << 0x3b)) {
    if (((ulong)*(byte *)(param_1 + 0x82) & 0x7f) >> 5 != 0) {
      (**(code **)(*(int *)(*(int *)(param_1 + 0x144) + 0x7e4) + 0x10))();
    }
    if (*(int *)(param_1 + 0x70) != 0) {
      ClearShadow__11CFieldModelFv(param_1);
      ClearModel__11CFieldModelFv(param_1);
      if (*(int *)(param_1 + 0x124) != 0) {
        (**(code **)(*(int *)(*(int *)(param_1 + 0x124) + 0x1c) + 0xc))();
        *(undefined4 *)(param_1 + 0x124) = 0;
      }
      iVar1 = GetModel__11CFieldModelFv(param_1);
      (**(code **)(*(int *)(iVar1 + 0x1c) + 0xc))();
      *(undefined4 *)(param_1 + 0x70) = 0;
    }
    *(byte *)(param_1 + 0x82) = *(byte *)(param_1 + 0x82) & 0xef | 0x10;
    (**(code **)(*(int *)(param_1 + 8) + 0xc))();
  }
  return;
}

/* JP: 0x004c0c20  CFieldModel::FindData(const char*)   [FindData__11CFieldModelFPCc]  size=0x34 */
void FindData__11CFieldModelFPCc(undefined4 param_1)

{
  Find__15_FieldDataCacheFiPCc(0x55f390,0x80,param_1);
  return;
}

/* JP: 0x004c0c60  CFieldModel::ReadFile(const char*)   [ReadFile__11CFieldModelFPCc]  size=0xd8 */
long ReadFile__11CFieldModelFPCc(undefined4 param_1,undefined4 param_2)

{
  long lVar1;
  undefined1 auStack_a0 [128];
  undefined4 uStack_20;
  undefined4 uStack_10;
  
  uStack_20 = param_1;
  uStack_10 = param_2;
  lVar1 = FindData__11CFieldModelFPCc(param_2);
  if (lVar1 == 0) {
    sprintf(auStack_a0,0x556180,pDataPath__7SysTool,uStack_10);
    lVar1 = GetNewData__15_FieldDataCacheFiPCc(0x55f390,0x80,uStack_10);
    mdlReadCount = mdlReadCount + 1;
    ReadOrder__11DvdromOrderFPCcPFiP9BufMemoryiPcPv_iiPvi(Dvdromour__11DvdromOrder,auStack_a0,0x4c02f0,lVar1,uStack_20,0);
  }
  else {
    *(short *)((int)lVar1 + 2) = *(short *)((int)lVar1 + 2) + 1;
    ReadCB__11CFieldModelFP15_FieldDataCachei(uStack_20,lVar1,0);
  }
  return lVar1;
}

/* JP: 0x004c0d40  CFieldModel::LoadMotion(const char*, unsigned int, void(*)(unsigned int, unsigned int, void*)*, void*)   [LoadMotion__11CFieldModelFPCcUiPFUiUiPv_vPv]  size=0x1ec */
undefined4
LoadMotion__11CFieldModelFPCcUiPFUiUiPv_vPv
          (int param_1,undefined4 param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  undefined4 uVar2;
  long lVar3;
  int *piVar4;
  int iVar5;
  undefined1 auStack_e0 [140];
  undefined4 uStack_54;
  int iStack_50;
  undefined4 uStack_40;
  int iStack_30;
  int iStack_20;
  int iStack_10;
  
  iStack_50 = param_1;
  uStack_40 = param_2;
  iStack_30 = param_3;
  iStack_20 = param_4;
  iStack_10 = param_5;
  iVar1 = FindData__11CFieldModelFPCc(param_2);
  *(byte *)(iStack_50 + 0x8a) = *(byte *)(iStack_50 + 0x8a) & 0xef;
  if (iVar1 != 0) {
    for (iVar5 = 0; iVar5 < 0x10; iVar5 = iVar5 + 1) {
      if (*(int *)(iStack_50 + iVar5 * 4 + 0x14c) == iVar1) {
        *(byte *)(iStack_50 + 0x8a) = *(byte *)(iStack_50 + 0x8a) & 0xef | 0x10;
        return 1;
      }
    }
  }
  lVar3 = GetNewLoadQ__11CFieldModelFRi(&uStack_54);
  if (lVar3 == 0) {
    uVar2 = 0;
  }
  else {
    SetCmd__11CFieldModelFi(iStack_50,5);
    piVar4 = (int *)lVar3;
    piVar4[1] = iStack_30;
    piVar4[2] = iStack_20;
    piVar4[3] = iStack_10;
    if (iVar1 == 0) {
      sprintf(auStack_e0,0x556180,pDataPath__7SysTool,uStack_40);
      iVar1 = GetNewData__15_FieldDataCacheFiPCc(0x55f390,0x80,uStack_40);
      *piVar4 = iVar1;
      mdlReadCount = mdlReadCount + 1;
      ReadOrder__11DvdromOrderFPCcPFiP9BufMemoryiPcPv_iiPvi(Dvdromour__11DvdromOrder,auStack_e0,0x4c0370,uStack_54,iStack_50,0);
    }
    else {
      *piVar4 = iVar1;
      *(short *)(iVar1 + 2) = *(short *)(iVar1 + 2) + 1;
      ReadMotionCB__11CFieldModelFiP9BufMemory(iStack_50,uStack_54,0);
    }
    uVar2 = 1;
  }
  return uVar2;
}

/* JP: 0x004c0f30  CFieldModel::DetachModel(_FieldDataCache*)   [DetachModel__11CFieldModelFP15_FieldDataCache]  size=0x308 */
/* WARNING: Removing unreachable block (ram,0x004c11e4) */

void DetachModel__11CFieldModelFP15_FieldDataCache(int param_1,ushort *param_2)

{
  bool bVar1;
  long lVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  long lVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  undefined1 auStack_30 [12];
  undefined1 uStack_24;
  int iStack_20;
  ushort *puStack_10;
  
  iStack_20 = param_1;
  puStack_10 = param_2;
  lVar2 = GetModel__11CFieldModelFv(param_1);
  if (lVar2 != 0) {
    uStack_24 = 0;
    iVar8 = -1;
    bVar1 = false;
    if ((long)((ulong)*(byte *)(iStack_20 + 0x81) << 0x3d) < 0) {
      iVar8 = 0;
    }
    if ((long)((ulong)*(byte *)(iStack_20 + 0x81) << 0x3e) < 0) {
      iVar8 = 1;
    }
    iVar7 = (int)(uint)*puStack_10 >> 0xc;
    if (iVar7 == 2) {
      uVar3 = getBuffer__9BufMemoryFv(*(undefined4 *)(puStack_10 + 4));
      iVar7 = GetFileCount(uVar3);
      for (iVar9 = 0; iVar9 < iVar7; iVar9 = iVar9 + 1) {
        uVar4 = GetFileEntry(uVar3,iVar9);
        uVar5 = GetFileID(uVar3,iVar9);
        lVar6 = strcmp(0x556198,uVar5);
        if ((lVar6 == 0) || (lVar6 = strcmp(0x5561a0,uVar5), lVar6 == 0)) {
          if (iVar8 == 1) {
            releaseDetaleLevel__5ModelFUi(lVar2,1);
            bVar1 = true;
            iVar8 = 0;
          }
        }
        else {
          lVar6 = strcmp(0x5561a8,uVar5);
          if (lVar6 == 0) {
            uVar4 = GetAnmName__11CFieldModelFPUc(iStack_20,uVar4);
            memcpy(auStack_30,uVar4,0xc);
            deleteMotion__5ModelFPCc(lVar2,auStack_30);
          }
        }
      }
    }
    else if (iVar7 == 1) {
      uVar3 = getBuffer__9BufMemoryFv(*(undefined4 *)(puStack_10 + 4));
      uVar3 = GetAnmName__11CFieldModelFPUc(iStack_20,uVar3);
      memcpy(auStack_30,uVar3,0xc);
      deleteMotion__5ModelFPCc(lVar2,auStack_30);
    }
    else if ((iVar7 == 0) && (iVar8 == 1)) {
      releaseDetaleLevel__5ModelFUi(lVar2,1);
      bVar1 = true;
    }
    if (bVar1) {
      *(byte *)(iStack_20 + 0x81) = *(byte *)(iStack_20 + 0x81) & 0xfd;
    }
  }
  return;
}

/* JP: 0x004c1240  CFieldModel::UnloadMotion(const char*)   [UnloadMotion__11CFieldModelFPCc]  size=0x194 */
void UnloadMotion__11CFieldModelFPCc(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  SetCmd__11CFieldModelFi(param_1,6);
  *(byte *)(param_1 + 0x8a) = *(byte *)(param_1 + 0x8a) & 0xdf | 0x20;
  if ((param_2 != 0) && (iVar1 = FindData__11CFieldModelFPCc(param_2), iVar1 != 0)) {
    for (iVar2 = 0; iVar2 < 0x10; iVar2 = iVar2 + 1) {
      if (iVar1 == *(int *)(param_1 + iVar2 * 4 + 0x14c)) {
        DetachModel__11CFieldModelFP15_FieldDataCache(param_1,iVar1);
        Release__15_FieldDataCacheFv(iVar1);
        *(undefined4 *)(param_1 + iVar2 * 4 + 0x14c) = 0;
        break;
      }
    }
  }
  iVar1 = 0;
  while( true ) {
    if (0xf < iVar1) {
      return;
    }
    if (*(int *)(param_1 + iVar1 * 4 + 0x14c) != 0) break;
    iVar1 = iVar1 + 1;
  }
  DetachModel__11CFieldModelFP15_FieldDataCache
            (param_1,*(undefined4 *)(param_1 + iVar1 * 4 + 0x14c));
  Release__15_FieldDataCacheFv(*(undefined4 *)(param_1 + iVar1 * 4 + 0x14c));
  *(undefined4 *)(param_1 + iVar1 * 4 + 0x14c) = 0;
  return;
}

/* JP: 0x004c13e0  CFieldModel::ReadCB(_FieldDataCache*, int)   [ReadCB__11CFieldModelFP15_FieldDataCachei]  size=0x368 */
undefined4 ReadCB__11CFieldModelFP15_FieldDataCachei(int param_1,ushort *param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  long lVar6;
  int iVar7;
  int iVar8;
  
  if ((long)((ulong)*(byte *)(param_1 + 0x82) << 0x3b) < 0) {
    uVar1 = 0;
  }
  else if (*(int *)(param_2 + 4) == 0) {
    *(byte *)(param_1 + 0x84) = *(byte *)(param_1 + 0x84) & 0xfb | 4;
    uVar1 = 1;
  }
  else {
    if ((int)(uint)*param_2 >> 0xc == 2) {
      uVar3 = getBuffer__9BufMemoryFv(*(undefined4 *)(param_2 + 4));
      for (iVar8 = 0; iVar8 < 2; iVar8 = iVar8 + 1) {
        iVar2 = GetFileCount(uVar3);
        for (iVar7 = 0; iVar7 < iVar2; iVar7 = iVar7 + 1) {
          uVar4 = GetFileEntry(uVar3,iVar7);
          uVar5 = GetFileID(uVar3,iVar7);
          if (iVar8 == 0) {
            lVar6 = strcmp(0x556198,uVar5);
            if (((lVar6 == 0) || (lVar6 = strcmp(0x5561a0,uVar5), lVar6 == 0)) &&
               (SetModel__11CFieldModelFPUci(param_1,uVar4,0), (*(byte *)(param_1 + 0x80) & 3) == 1)
               ) {
              *(byte *)(param_1 + 0x80) = *(byte *)(param_1 + 0x80) & 0xfc | 3;
              *(byte *)(param_1 + 0x8a) = *(byte *)(param_1 + 0x8a) & 0xfe | 1;
              if (sys__6CField != 0) {
                LoadModelCB__6CFieldFP11CFieldModel(sys__6CField,param_1);
              }
            }
          }
          else {
            lVar6 = strcmp(0x5561a8,uVar5);
            if (lVar6 == 0) {
              uVar5 = GetModel__11CFieldModelFv(param_1);
              createMotion__5ModelFPUc(uVar5,uVar4);
            }
            else {
              lVar6 = strcmp(0x5561b0,uVar5);
              if (lVar6 == 0) {
                *(byte *)(param_1 + 0x81) = *(byte *)(param_1 + 0x81) & 0xe7 | 8;
                *(int *)(param_1 + 0x140) = (int)uVar4;
              }
            }
          }
        }
      }
    }
    else if ((int)(uint)*param_2 >> 0xc == 0) {
      uVar3 = getBuffer__9BufMemoryFv(*(undefined4 *)(param_2 + 4));
      SetModel__11CFieldModelFPUci(param_1,uVar3,0);
      if ((*(byte *)(param_1 + 0x80) & 3) == 1) {
        *(byte *)(param_1 + 0x80) = *(byte *)(param_1 + 0x80) & 0xfc | 3;
        *(byte *)(param_1 + 0x8a) = *(byte *)(param_1 + 0x8a) & 0xfe | 1;
      }
    }
    uVar1 = 1;
  }
  return uVar1;
}

/* JP: 0x004c1750  CFieldModel::LoadModel(const char*)   [LoadModel__11CFieldModelFPCc]  size=0xb0 */
bool LoadModel__11CFieldModelFPCc(int param_1,undefined4 param_2)

{
  bool bVar1;
  undefined4 uVar2;
  
  *(byte *)(param_1 + 0x8a) = *(byte *)(param_1 + 0x8a) & 0xfe;
  bVar1 = (*(byte *)(param_1 + 0x80) & 3) != 3;
  if (bVar1) {
    *(byte *)(param_1 + 0x80) = *(byte *)(param_1 + 0x80) & 0xfc | 1;
    uVar2 = ReadFile__11CFieldModelFPCc(param_1,param_2);
    *(undefined4 *)(param_1 + 0x148) = uVar2;
    SetCmd__11CFieldModelFi(param_1,1);
  }
  return bVar1;
}

/* JP: 0x004c1800  CFieldModel::Reset(int)   [Reset__11CFieldModelFi]  size=0x134 */
void Reset__11CFieldModelFi(int param_1,undefined4 param_2)

{
  undefined8 uVar1;
  undefined1 auStack_40 [16];
  undefined1 auStack_30 [16];
  int iStack_20;
  undefined4 uStack_10;
  
  iStack_20 = param_1;
  uStack_10 = param_2;
  SetFloorChk__11CFieldModelFi(param_1,1);
  SetHitCheck__11CFieldModelFi(iStack_20,1);
  clear__Q311CFieldModel7_member8_evflagsFv(iStack_20 + 0x8a);
  clear__Q311CFieldModel7_member6_flagsFv(iStack_20 + 0x84);
  *(byte *)(iStack_20 + 0x80) = *(byte *)(iStack_20 + 0x80) & 0xdf;
  SetMoveMotion__11CFieldModelFiii(iStack_20,1,2,3);
  *(byte *)(iStack_20 + 0x82) =
       *(byte *)(iStack_20 + 0x82) & 0xf9 |
       (byte)(((uint)(((ulong)*(byte *)(iStack_20 + 0x82) << 0x3d) >> 0x3e) | 1) << 1);
  ChgCtrl__11CFieldModelFi(iStack_20,uStack_10);
  SetDir__11CFieldModelFiii(iStack_20,0,0,3);
  __ct__7FVectorFffff(0,0,0,0x3f800000,auStack_30);
  uVar1 = __ct__7FVectorFRC7FVector(auStack_40,auStack_30);
  SetPos__11CFieldModelF7FVectorb(iStack_20,uVar1,1);
  return;
}

/* JP: 0x004c1980  CFieldModel::ChgCtrl(int)   [ChgCtrl__11CFieldModelFi]  size=0x78 */
void ChgCtrl__11CFieldModelFi(int param_1,int param_2)

{
  SetFootStep__11CFieldModelFi(param_1,1);
  *(undefined4 *)(param_1 + 300) = 0;
  *(undefined4 *)(param_1 + 0x130) = 0;
  if (param_2 != 0) {
    SetManual__11CFieldModelFi(param_1,1);
    *(undefined4 *)(param_1 + 300) = 0x40000000;
    *(undefined4 *)(param_1 + 0x130) = 0x30000000;
  }
  return;
}

/* JP: 0x004c1a00  CFieldModel::SetFootStep(int)   [SetFootStep__11CFieldModelFi]  size=0x40 */
void SetFootStep__11CFieldModelFi(int param_1,byte param_2)

{
  *(byte *)(param_1 + 0x88) = *(byte *)(param_1 + 0x88) & 0xbf | (param_2 & 1) << 6;
  return;
}

/* JP: 0x004c1a40  CFieldModel::GetAnmName(unsigned char*)   [GetAnmName__11CFieldModelFPUc]  size=0x48 */
int * GetAnmName__11CFieldModelFPUc(undefined8 param_1,int *param_2)

{
  if (*param_2 == 0x44485153) {
    param_2 = param_2 + 1;
  }
  else {
    param_2 = (int *)0x0;
  }
  return param_2;
}

/* JP: 0x004c1a90  CFieldModel::FindMotionData(const char*)   [FindMotionData__11CFieldModelFPCc]  size=0x78 */
undefined4 FindMotionData__11CFieldModelFPCc(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  long lVar3;
  
  iVar1 = GetModel__11CFieldModelFv(param_1);
  if ((*(int *)(iVar1 + 0x34) == 0) ||
     (lVar3 = SeachSequenceControl__15SequenceControlFPUc(*(int *)(iVar1 + 0x34),param_2), lVar3 == 0)) {
    uVar2 = 0;
  }
  else {
    uVar2 = *(undefined4 *)((int)lVar3 + 8);
  }
  return uVar2;
}

/* JP: 0x004c1b10  CFieldModel::SetModelType(int)   [SetModelType__11CFieldModelFi]  size=0x90 */
void SetModelType__11CFieldModelFi(int param_1,uint param_2)

{
  *(byte *)(param_1 + 0x81) =
       *(byte *)(param_1 + 0x81) & 0x7f |
       (byte)(((uint)(((ulong)*(byte *)(param_1 + 0x81) << 0x38) >> 0x3f) | (int)param_2 >> 7 & 1U)
             << 7);
  *(short *)(param_1 + 0x98) = (short)(param_2 & 0x7f);
  SetMoveLock__11CFieldModelFi(param_1,(param_2 & 0x7f) != 0);
  return;
}

/* JP: 0x004c1ba0  CFieldModel::SetMoveLock(int)   [SetMoveLock__11CFieldModelFi]  size=0x40 */
void SetMoveLock__11CFieldModelFi(int param_1,byte param_2)

{
  *(byte *)(param_1 + 0x88) = *(byte *)(param_1 + 0x88) & 0xf9 | (param_2 & 3) << 1;
  return;
}

/* JP: 0x004c1be0  CFieldModel::AddNaviItem(int, int, int)   [AddNaviItem__11CFieldModelFiii]  size=0x80 */
void AddNaviItem__11CFieldModelFiii(int param_1,char param_2,byte param_3,char param_4)

{
  *(char *)(param_1 + 0xb0) = param_2 + '\x01';
  *(byte *)(param_1 + 0xb1) = *(byte *)(param_1 + 0xb1) & 0xf0 | param_3 & 0xf;
  *(byte *)(param_1 + 0xb1) = *(byte *)(param_1 + 0xb1) & 0xf | param_4 << 4;
  return;
}

/* JP: 0x004c1c60  CFieldModel::SetModel(unsigned char*, int)   [SetModel__11CFieldModelFPUci]  size=0x1e0 */
undefined4 SetModel__11CFieldModelFPUci(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  undefined8 uVar2;
  long lVar3;
  
  if (*(int *)(param_1 + 0x70) == 0) {
    CreateModel__11CFieldModelFv(param_1);
  }
  if (((*(byte *)(param_1 + 0x81) & 1) == 0) &&
     (-1 < (long)((ulong)*(byte *)(param_1 + 0x81) << 0x3e))) {
    SetModelType__11CFieldModelFi(param_1,param_3);
    uVar2 = GetModel__11CFieldModelFv(param_1);
    lVar3 = (**(code **)(*(int *)((int)uVar2 + 0x10) + 0x24))(uVar2,param_2);
    if (lVar3 == 0) {
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    *(byte *)(param_1 + 0x81) = *(byte *)(param_1 + 0x81) & 0xfe | 1;
    uVar1 = 1;
  }
  else if ((long)((ulong)*(byte *)(param_1 + 0x81) << 0x3d) < 0) {
    if ((long)((ulong)*(byte *)(param_1 + 0x81) << 0x3e) < 0) {
      uVar1 = 0;
    }
    else {
      uVar2 = GetModel__11CFieldModelFv(param_1);
      createLevelofDetale__5ModelFPUcUi(uVar2,param_2,1);
      *(byte *)(param_1 + 0x81) = *(byte *)(param_1 + 0x81) & 0xfd | 2;
      uVar1 = 1;
    }
  }
  else {
    uVar2 = GetModel__11CFieldModelFv(param_1);
    createLevelofDetale__5ModelFPUcUi(uVar2,param_2,2);
    *(byte *)(param_1 + 0x81) = *(byte *)(param_1 + 0x81) & 0xfb | 4;
    *(undefined4 *)(param_1 + 0x128) = param_2;
    uVar1 = 1;
  }
  return uVar1;
}

/* JP: 0x004c1e40  CFieldModel::SetBlink(int)   [SetBlink__11CFieldModelFi]  size=0x134 */
void SetBlink__11CFieldModelFi(int param_1,uint param_2)

{
  uint uVar1;
  
  uVar1 = param_2 & 0xff;
  *(byte *)(param_1 + 0x89) = *(byte *)(param_1 + 0x89) & 0xfe | 1;
  if (((int)param_2 >> 8 & 0xfU) < 4) {
    if (uVar1 < 3) {
      uVar1 = 4;
    }
    *(byte *)(param_1 + 0x105) = *(byte *)(param_1 + 0x105) & 0xf3 | (byte)((uVar1 - 3 & 3) << 2);
    if (uVar1 <= (*(byte *)(param_1 + 0x104) & 0x1f)) {
      *(byte *)(param_1 + 0x104) = *(byte *)(param_1 + 0x104) & 0xe0;
    }
  }
  else {
    *(byte *)(param_1 + 0x104) = *(byte *)(param_1 + 0x104) & 0xe0 | (byte)param_2 & 0x1f;
  }
  *(byte *)(param_1 + 0x104) =
       *(byte *)(param_1 + 0x104) & 0x1f | (byte)(((int)param_2 >> 8 & 7U) << 5);
  *(undefined1 *)(param_1 + 0x106) = 2;
  return;
}

/* JP: 0x004c1f80  CFieldModel::SetTalk(int)   [SetTalk__11CFieldModelFi]  size=0x118 */
void SetTalk__11CFieldModelFi(int param_1,uint param_2)

{
  uint uVar1;
  
  if (param_2 == 0) {
    *(byte *)(param_1 + 0x89) = *(byte *)(param_1 + 0x89) & 0xf9;
  }
  else if ((param_2 & 1) == 0) {
    *(byte *)(param_1 + 0x89) =
         *(byte *)(param_1 + 0x89) & 0xf9 |
         (byte)(((uint)(((ulong)*(byte *)(param_1 + 0x89) << 0x3d) >> 0x3e) &
                ~((int)param_2 >> 1 & 3U) & 0xff) << 1);
  }
  else {
    if ((param_2 & 2) == 0) {
      uVar1 = 1;
    }
    else {
      uVar1 = 2;
    }
    *(byte *)(param_1 + 0x89) =
         *(byte *)(param_1 + 0x89) & 0xf9 |
         (byte)(((uint)(((ulong)*(byte *)(param_1 + 0x89) << 0x3d) >> 0x3e) | uVar1) << 1);
  }
  return;
}

/* JP: 0x004c20a0  CFieldModel::SetMotion(int, int)   [SetMotion__11CFieldModelFii]  size=0x114 */
void SetMotion__11CFieldModelFii(int param_1,undefined4 param_2,uint param_3)

{
  SetCmd__11CFieldModelFi(param_1,7);
  *(byte *)(param_1 + 0x8a) = *(byte *)(param_1 + 0x8a) & 0xbf;
  if (((param_3 & 7) == 0) || ((long)((ulong)*(byte *)(param_1 + 0x81) << 0x39) < 0)) {
    *(byte *)(param_1 + 0x84) = *(byte *)(param_1 + 0x84) & 0xbf | ((param_3 & 0x80) != 0) << 6;
    *(undefined1 *)(param_1 + 0xf0) = 0;
    *(undefined1 *)(param_1 + 0xf1) = 0;
    SetMotion__11CFieldModelFi(param_1,param_2);
  }
  else {
    if ((param_3 & 7) == 1) {
      *(undefined1 *)(param_1 + 0xf0) = 0;
      *(undefined1 *)(param_1 + 0xf1) = 0;
    }
    ChainMotion__11CFieldModelFUii(param_1,param_2,param_3);
  }
  return;
}

/* JP: 0x004c21c0  CFieldModel::ChainMotion(unsigned int, int)   [ChainMotion__11CFieldModelFUii]  size=0x1d4 */
undefined4 ChainMotion__11CFieldModelFUii(int param_1,uint param_2,uint param_3)

{
  byte bVar1;
  byte bVar2;
  undefined4 uVar3;
  int iVar4;
  
  if (*(byte *)(param_1 + 0xf0) < 8) {
    SetCmd__11CFieldModelFi(param_1,7);
    *(byte *)(param_1 + 0x8a) = *(byte *)(param_1 + 0x8a) & 0xbf;
    bVar2 = ((param_3 & 0x80) != 0) << (*(byte *)(param_1 + 0xf0) & 0x1f);
    if (param_2 < 0x80) {
      bVar1 = *(byte *)(param_1 + 0xf0);
      *(byte *)(param_1 + 0xf0) = bVar1 + 1;
      *(char *)(param_1 + (uint)bVar1 + 0xe8) = (char)param_2;
      *(byte *)(param_1 + 0xf1) = *(byte *)(param_1 + 0xf1) | bVar2;
      uVar3 = 1;
    }
    else {
      for (iVar4 = 0; iVar4 < 4; iVar4 = iVar4 + 1) {
        if (*(int *)(param_1 + iVar4 * 4 + 0xd8) == 0) {
          *(uint *)(param_1 + iVar4 * 4 + 0xd8) = param_2;
          *(byte *)(param_1 + 0xf1) = *(byte *)(param_1 + 0xf1) | bVar2;
          bVar2 = *(byte *)(param_1 + 0xf0);
          *(byte *)(param_1 + 0xf0) = bVar2 + 1;
          *(char *)(param_1 + (uint)bVar2 + 0xe8) = (char)iVar4 + -0x10;
          return 1;
        }
      }
      uVar3 = 0;
    }
  }
  else {
    uVar3 = 0;
  }
  return uVar3;
}

/* JP: 0x004c23a0  CFieldModel::SetMotion(int)   [SetMotion__11CFieldModelFi]  size=0x84 */
undefined8 SetMotion__11CFieldModelFi(int param_1,undefined4 param_2)

{
  undefined8 uVar1;
  long lVar2;
  
  uVar1 = GetMotionName__FUi(param_2);
  lVar2 = strcmp(param_1 + 700,uVar1);
  if (lVar2 == 0) {
    uVar1 = 1;
  }
  else {
    *(undefined4 *)(param_1 + 0xa0) = param_2;
    uVar1 = SetMotion__11CFieldModelFPCc(param_1,uVar1);
  }
  return uVar1;
}

/* JP: 0x004c2430  CFieldModel::GetMotionCode()   [GetMotionCode__11CFieldModelFv]  size=0xcc */
int GetMotionCode__11CFieldModelFv(int param_1)

{
  long lVar1;
  int iVar2;
  undefined **ppuVar3;
  
  ppuVar3 = &PTR__2959_00556014;
  iVar2 = 1;
  while( true ) {
    if (0x34 < iVar2) {
      return -1;
    }
    lVar1 = strcmp(param_1 + 700,*ppuVar3);
    if (lVar1 == 0) break;
    iVar2 = iVar2 + 1;
    ppuVar3 = ppuVar3 + 1;
  }
  return iVar2;
}

/* JP: 0x004c2500  CFieldModel::SetMotion(const char*)   [SetMotion__11CFieldModelFPCc]  size=0x294 */
undefined4 SetMotion__11CFieldModelFPCc(int param_1,undefined4 param_2)

{
  bool bVar1;
  char cVar2;
  long lVar3;
  undefined8 uVar4;
  undefined4 uVar5;
  
  *(byte *)(param_1 + 0x88) =
       *(byte *)(param_1 + 0x88) & 0xf9 |
       (byte)(((uint)(((ulong)*(byte *)(param_1 + 0x88) << 0x3d) >> 0x3e) & 1) << 1);
  *(byte *)(param_1 + 0x85) = *(byte *)(param_1 + 0x85) & 0xcf | 0x30;
  lVar3 = GetFrame__11CFieldModelFv(param_1);
  if (lVar3 != 0) {
    uVar4 = GetModel__11CFieldModelFv(param_1);
    uVar5 = getSequenceEndTime__5ModelFQ25Model10MotionKindPCc(uVar4,0,param_2);
    *(undefined4 *)(param_1 + 0x138) = uVar5;
    if ((long)((ulong)*(byte *)(param_1 + 0x81) << 0x3a) < 0) {
      cVar2 = setNextMotion__5ModelFPCcUs(uVar4,param_2,1);
    }
    else {
      cVar2 = setMotion__5ModelFPCcf(0,uVar4,param_2);
    }
    lVar3 = FindMotionData__11CFieldModelFPCc(param_1,param_2);
    if ((*(byte *)(param_1 + 0x104) >> 5 == 0) || ((*(byte *)(param_1 + 0x104) >> 5 & 1) != 0)) {
      bVar1 = false;
      if ((lVar3 != 0) && ((*(byte *)((int)lVar3 + 0x14) & 1) != 0)) {
        bVar1 = true;
      }
      if (bVar1) {
        uVar5 = 0x100;
      }
      else {
        uVar5 = 0x400;
      }
      SetBlink__11CFieldModelFi(param_1,uVar5);
    }
    if (cVar2 != '\0') {
      *(byte *)(param_1 + 0x81) = *(byte *)(param_1 + 0x81) & 0xbf;
      strcpy(param_1 + 700,param_2);
      *(byte *)(param_1 + 0x80) = *(byte *)(param_1 + 0x80) & 0xdf | 0x20;
      if (-1 < (long)((ulong)*(byte *)(param_1 + 0x81) << 0x38)) {
        SetLastMotion__11CFieldModelFPCc(param_1,param_2);
      }
      return 1;
    }
  }
  *(byte *)(param_1 + 0x81) = *(byte *)(param_1 + 0x81) & 0xbf | 0x40;
  *(undefined1 *)(param_1 + 700) = 0;
  return 0;
}

/* JP: 0x004c27a0  CFieldModel::DispModel(int)   [DispModel__11CFieldModelFi]  size=0x38 */
void DispModel__11CFieldModelFi(undefined4 param_1,undefined4 param_2)

{
  DispModel__11CFieldModelFiii(param_1,param_2,param_2,0);
  return;
}

/* JP: 0x004c27e0  CFieldModel::DspModelEff()   [DspModelEff__11CFieldModelFv]  size=0x170 */
void DspModelEff__11CFieldModelFv(int param_1)

{
  undefined8 uVar1;
  
  if ((*(int *)(param_1 + 0x140) != 0) && (((ulong)*(byte *)(param_1 + 0x81) & 0x1f) >> 3 == 1)) {
    uVar1 = GetModel__11CFieldModelFv(param_1);
    createMF__15ModelEffManagerFQ215ModelEffManager4MENoiP5ModeliPc(1,0,uVar1,*(undefined1 *)(param_1 + 0x93),*(undefined4 *)(param_1 + 0x140));
    *(byte *)(param_1 + 0x81) = *(byte *)(param_1 + 0x81) & 0xe7 | 0x10;
  }
  if ((((ulong)*(byte *)(param_1 + 0x82) & 0x7f) >> 5 != 0) && (*(int *)(param_1 + 0x144) != 0)) {
    if (((ulong)*(byte *)(param_1 + 0x82) & 0x7f) >> 5 == 1) {
      *(byte *)(param_1 + 0x82) = *(byte *)(param_1 + 0x82) & 0x9f | 0x40;
      uVar1 = GetModel__11CFieldModelFv(param_1);
      CnvModelGray__FP5Model(uVar1);
      AttachModel__9CGhostEfxFP5Model(*(undefined4 *)(param_1 + 0x144),uVar1);
    }
    Dsp__9CGhostEfxFi(*(undefined4 *)(param_1 + 0x144),*(undefined1 *)(param_1 + 0x93));
  }
  return;
}

/* JP: 0x004c2980  CFieldModel::ClrModelEff()   [ClrModelEff__11CFieldModelFv]  size=0xc8 */
void ClrModelEff__11CFieldModelFv(int param_1)

{
  undefined8 uVar1;
  
  if ((*(int *)(param_1 + 0x140) != 0) && (((ulong)*(byte *)(param_1 + 0x81) & 0x1f) >> 3 == 2)) {
    uVar1 = GetModel__11CFieldModelFv(param_1);
    deleteMF__15ModelEffManagerFP5Model(uVar1);
    *(byte *)(param_1 + 0x81) = *(byte *)(param_1 + 0x81) & 0xe7 | 8;
  }
  if ((((ulong)*(byte *)(param_1 + 0x82) & 0x7f) >> 5 != 0) && (*(int *)(param_1 + 0x144) != 0)) {
    (**(code **)(*(int *)(*(int *)(param_1 + 0x144) + 0x7e4) + 0x10))();
  }
  return;
}

/* JP: 0x004c2a50  CFieldModel::SetGhost()   [SetGhost__11CFieldModelFv]  size=0xac */
void SetGhost__11CFieldModelFv(int param_1)

{
  undefined4 uVar1;
  long lVar2;
  
  if (((ulong)*(byte *)(param_1 + 0x82) & 0x7f) >> 5 == 0) {
    *(byte *)(param_1 + 0x82) = *(byte *)(param_1 + 0x82) & 0x9f | 0x20;
    lVar2 = __nw__FUi(0x830);
    uVar1 = 0;
    if (lVar2 != 0) {
      uVar1 = __ct__9CGhostEfxFv(lVar2);
    }
    *(undefined4 *)(param_1 + 0x144) = uVar1;
    (**(code **)(*(int *)(*(int *)(param_1 + 0x144) + 0x7e4) + 0x20))();
  }
  return;
}

/* JP: 0x004c2b00  CFieldModel::SetMirror(int)   [SetMirror__11CFieldModelFi]  size=0x150 */
void SetMirror__11CFieldModelFi(int param_1,uint param_2)

{
  byte bVar1;
  undefined4 uVar2;
  long lVar3;
  
  if (param_2 == 0) {
    ClrMirror__11CFieldModelFi(param_1,1);
    *(byte *)(param_1 + 0x89) = *(byte *)(param_1 + 0x89) & 199;
  }
  else {
    bVar1 = *(byte *)(param_1 + 0x89);
    *(byte *)(param_1 + 0x89) = *(byte *)(param_1 + 0x89) & 199 | (byte)((param_2 & 7) << 3);
    if (*(int *)(param_1 + 0x124) == 0) {
      lVar3 = __nw__FUi(0x4d0);
      uVar2 = 0;
      if (lVar3 != 0) {
        uVar2 = __ct__11MirrorModelFv(lVar3);
      }
      *(undefined4 *)(param_1 + 0x124) = uVar2;
      *(byte *)(param_1 + 0x8c) = *(byte *)(param_1 + 0x8c) & 0xf7 | 8;
    }
    if ((((ulong)*(byte *)(param_1 + 0x82) & 7) >> 1 == 3) ||
       (((ulong)bVar1 & 0x3f) >> 3 != (long)(int)param_2)) {
      DspMirror__11CFieldModelFv(param_1);
    }
  }
  return;
}

/* JP: 0x004c2c50  CFieldModel::DspMirror()   [DspMirror__11CFieldModelFv]  size=0x2c8 */
void DspMirror__11CFieldModelFv(int param_1)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  
  if (*(int *)(param_1 + 0x124) != 0) {
    if ((*(byte *)(param_1 + 0x8c) & 1) == 0) {
      if ((long)((ulong)*(byte *)(param_1 + 0x8c) << 0x3c) < 0) {
        *(byte *)(param_1 + 0x8c) = *(byte *)(param_1 + 0x8c) & 0xfb | 4;
      }
      else {
        iVar2 = LayerMan_GetLayer__Fi(5);
        AddOT__5WorldFiP8VIF1Prim(0x42bf10,iVar2 + -1,*(undefined4 *)(param_1 + 0x124));
        setOffset__11MirrorModelFfff
                  (*(undefined4 *)(param_1 + 0x60),*(undefined4 *)(param_1 + 100),
                   *(undefined4 *)(param_1 + 0x68),*(undefined4 *)(param_1 + 0x124));
        *(byte *)(param_1 + 0x8c) = *(byte *)(param_1 + 0x8c) & 0xfb;
        *(byte *)(param_1 + 0x8c) = *(byte *)(param_1 + 0x8c) & 0xfe | 1;
      }
    }
    else {
      bVar1 = *(byte *)(param_1 + 0x89);
      setOffset__11MirrorModelFfff
                (*(undefined4 *)(param_1 + 0x60),*(undefined4 *)(param_1 + 100),
                 *(undefined4 *)(param_1 + 0x68),*(undefined4 *)(param_1 + 0x124));
      uVar3 = (uint)(((ulong)bVar1 << 0x3a) >> 0x3d);
      setMirror__11MirrorModelFbbb
                (*(undefined4 *)(param_1 + 0x124),(((ulong)bVar1 & 0x3f) >> 3 & 1) != 0,
                 ((int)uVar3 >> 1 & 1U) != 0,(int)uVar3 >> 2 != 0);
    }
    if ((*(int *)(param_1 + 0x2b8) != 0) && ((long)((ulong)*(byte *)(param_1 + 0x80) << 0x3b) < 0))
    {
      if (((long)((ulong)*(byte *)(param_1 + 0x8c) << 0x3e) < 0) ||
         ((((ulong)*(byte *)(param_1 + 0x89) & 0x3f) >> 3 & 2) != 0)) {
        if ((((ulong)*(byte *)(param_1 + 0x8c) & 3) >> 1 == 1) &&
           ((((ulong)*(byte *)(param_1 + 0x89) & 0x3f) >> 3 & 2) != 0)) {
          *(byte *)(param_1 + 0x8c) = *(byte *)(param_1 + 0x8c) & 0xfd;
          releaseShadow__13ShadowControlFP5Model(*(undefined4 *)(param_1 + 0x2b8),*(undefined4 *)(param_1 + 0x124));
        }
      }
      else {
        *(byte *)(param_1 + 0x8c) = *(byte *)(param_1 + 0x8c) & 0xfd | 2;
        setDropShadow__13ShadowControlFP5Model(*(undefined4 *)(param_1 + 0x2b8),*(undefined4 *)(param_1 + 0x124));
      }
    }
  }
  return;
}

/* JP: 0x004c2fc0  CFieldModel::ClrMirror(int)   [ClrMirror__11CFieldModelFi]  size=0x118 */
void ClrMirror__11CFieldModelFi(int param_1,int param_2)

{
  if (*(int *)(param_1 + 0x124) != 0) {
    *(byte *)(param_1 + 0x8c) = *(byte *)(param_1 + 0x8c) & 0xfb;
    if ((*(byte *)(param_1 + 0x8c) & 1) != 0) {
      *(byte *)(param_1 + 0x8c) = *(byte *)(param_1 + 0x8c) & 0xfe;
      ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,*(undefined4 *)(param_1 + 0x124));
    }
    if ((long)((ulong)*(byte *)(param_1 + 0x8c) << 0x3e) < 0) {
      *(byte *)(param_1 + 0x8c) = *(byte *)(param_1 + 0x8c) & 0xfd;
      releaseShadow__13ShadowControlFP5Model(*(undefined4 *)(param_1 + 0x2b8),*(undefined4 *)(param_1 + 0x124));
    }
    if (param_2 != 0) {
      (**(code **)(*(int *)(*(int *)(param_1 + 0x124) + 0x1c) + 0xc))();
      *(undefined4 *)(param_1 + 0x124) = 0;
    }
  }
  return;
}

/* JP: 0x004c30e0  CFieldModel::UpdateMirrorOfs(int, FVector&)   [UpdateMirrorOfs__11CFieldModelFiR7FVector]  size=0x98 */
void UpdateMirrorOfs__11CFieldModelFiR7FVector(int param_1,uint param_2,undefined4 param_3)

{
  if ((int)param_2 < 0) {
    ClrMirror__11CFieldModelFi(param_1,0);
  }
  else {
    *(byte *)(param_1 + 0x89) =
         *(byte *)(param_1 + 0x89) & 199 | (byte)((1 << (param_2 & 0x1f) & 7U) << 3);
    __as__7FVectorFRC7FVector(param_1 + 0x60,param_3);
    DspMirror__11CFieldModelFv(param_1);
  }
  return;
}

/* JP: 0x004c3180  CFieldModel::DispModel(int, int, int)   [DispModel__11CFieldModelFiii]  size=0x464 */
undefined4 DispModel__11CFieldModelFiii(int param_1,uint param_2,uint param_3,int param_4)

{
  undefined8 uVar1;
  undefined1 auStack_a0 [16];
  undefined1 auStack_90 [64];
  undefined1 auStack_50 [12];
  undefined4 uStack_44;
  int iStack_40;
  uint uStack_30;
  uint uStack_20;
  int iStack_10;
  
  if (param_2 == 0xffffffff) {
    uStack_30 = (uint)*(byte *)(param_1 + 0x92);
  }
  else {
    *(char *)(param_1 + 0x92) = (char)param_2;
    uStack_30 = param_2;
  }
  if (param_3 == 0xffffffff) {
    uStack_20 = (uint)*(byte *)(param_1 + 0x93);
  }
  else {
    *(char *)(param_1 + 0x93) = (char)param_3;
    uStack_20 = param_3;
  }
  if (((ulong)*(byte *)(param_1 + 0x82) & 0x7f) >> 5 != 0) {
    *(undefined1 *)(param_1 + 0x93) = 10;
    *(undefined1 *)(param_1 + 0x92) = 10;
  }
  iStack_40 = param_1;
  iStack_10 = param_4;
  SetCmd__11CFieldModelFi(param_1,3);
  *(byte *)(iStack_40 + 0x8a) = *(byte *)(iStack_40 + 0x8a) & 0xfb;
  *(byte *)(iStack_40 + 0x85) = *(byte *)(iStack_40 + 0x85) & 0xcf | 0x30;
  uVar1 = GetModel__11CFieldModelFv(iStack_40);
  Clr__11CFieldModelFi(iStack_40,2);
  *(byte *)(iStack_40 + 0x80) = *(byte *)(iStack_40 + 0x80) & 0xf3;
  if ((*(byte *)(iStack_40 + 0x81) & 1) == 0) {
    *(byte *)(iStack_40 + 0x84) = *(byte *)(iStack_40 + 0x84) & 0xcf | 0x10;
    *(char *)(iStack_40 + 0x96) = (char)iStack_10;
  }
  else {
    __ct__7FVectorFv(auStack_50);
    getModelColor__5ModelFv(auStack_a0,uVar1);
    __as__7FVectorFRC7FVector(auStack_50,auStack_a0);
    if (iStack_10 == 1) {
      uStack_44 = 0;
      setModelColor__5ModelFR7FVector(uVar1,auStack_50);
      if (*(int *)(iStack_40 + 0x140) != 0) {
        changeAlpha__15ModelEffManagerFP5Modelf(0,uVar1);
      }
      *(byte *)(iStack_40 + 0x80) = *(byte *)(iStack_40 + 0x80) & 0xf3 | 4;
    }
    else {
      uStack_44 = 0x43000000;
      setModelColor__5ModelFR7FVector(uVar1,auStack_50);
      if (*(int *)(iStack_40 + 0x140) != 0) {
        changeAlpha__15ModelEffManagerFP5Modelf(0x43000000,uVar1);
      }
      iStack_10 = 0;
      *(byte *)(iStack_40 + 0x80) = *(byte *)(iStack_40 + 0x80) & 0xf3 | 0xc;
      *(byte *)(iStack_40 + 0x8a) = *(byte *)(iStack_40 + 0x8a) & 0xfb | 4;
    }
    *(char *)(iStack_40 + 0x96) = (char)iStack_10;
    *(undefined1 *)(iStack_40 + 0x97) = 0;
    *(undefined4 *)(iStack_40 + 0x9c) = 0;
    Dsp__11CFieldModelFi(iStack_40,2);
    __ct__6MatrixFv(auStack_90);
    UnitMatrix__6MatrixFv(auStack_90);
    RotXMatrix__6MatrixFf(*(undefined4 *)(iStack_40 + 0x20),auStack_90);
    RotYMatrix__6MatrixFf(*(undefined4 *)(iStack_40 + 0x24),auStack_90);
    RotZMatrix__6MatrixFf(*(undefined4 *)(iStack_40 + 0x28),auStack_90);
    TransMatrix__6MatrixFRC7FVector(auStack_90,iStack_40 + 0x10);
    __as__6MatrixFRC6Matrix(*(int *)((int)uVar1 + 0x30) + 0x160,auStack_90);
    CalcMatrix__11CFieldModelFv(iStack_40);
    *(byte *)(iStack_40 + 0x81) = *(byte *)(iStack_40 + 0x81) & 0xdf;
    *(byte *)(iStack_40 + 0x85) = *(byte *)(iStack_40 + 0x85) & 0xcf | 0x30;
    PlayMoveMotion__11CFieldModelFi(iStack_40,0);
    AddTime__11CFieldModelFf(0,iStack_40);
    if (-1 < (long)((ulong)*(byte *)(iStack_40 + 0x81) << 0x3a)) {
      __as__7FVectorFRC7FVector(iStack_40 + 0x20,iStack_40 + 0x30);
    }
  }
  return 1;
}

/* JP: 0x004c35f0  CFieldModel::Clear(int)   [Clear__11CFieldModelFi]  size=0x118 */
void Clear__11CFieldModelFi(int param_1,int param_2)

{
  undefined4 uStack_10;
  
  if ((((ulong)*(byte *)(param_1 + 0x80) & 0xf) >> 2 & 1) != 0) {
    SetCmd__11CFieldModelFi(param_1,4);
    *(byte *)(param_1 + 0x8a) = *(byte *)(param_1 + 0x8a) & 0xf7;
    uStack_10 = param_2;
    if (param_2 != 1) {
      uStack_10 = 0;
      ClearShadow__11CFieldModelFv(param_1);
      ClearModel__11CFieldModelFv(param_1);
      *(byte *)(param_1 + 0x8a) = *(byte *)(param_1 + 0x8a) & 0xf7 | 8;
    }
    if (uStack_10 != 0) {
      *(byte *)(param_1 + 0x80) = *(byte *)(param_1 + 0x80) & 0xf3 | 8;
      *(undefined1 *)(param_1 + 0x97) = 0;
      *(undefined4 *)(param_1 + 0x9c) = 0;
    }
    *(char *)(param_1 + 0x96) = (char)uStack_10;
  }
  return;
}

/* JP: 0x004c3710  CFieldModel::Dsp(int)   [Dsp__11CFieldModelFi]  size=0x1b0 */
void Dsp__11CFieldModelFi(int param_1,uint param_2)

{
  byte bVar1;
  undefined8 uVar2;
  
  bVar1 = *(byte *)(param_1 + 0x82);
  *(byte *)(param_1 + 0x82) =
       *(byte *)(param_1 + 0x82) & 0xf9 |
       (byte)(((uint)(((ulong)*(byte *)(param_1 + 0x82) << 0x3d) >> 0x3e) | param_2 & 3) << 1);
  if ((((ulong)bVar1 & 7) >> 1 != 3) && (((ulong)*(byte *)(param_1 + 0x82) & 7) >> 1 == 3)) {
    if (*(int *)(param_1 + 0x120) != 0) {
      Dsp__8CBalIconFv(*(undefined4 *)(param_1 + 0x120));
    }
    uVar2 = GetModel__11CFieldModelFv(param_1);
    if (*(char *)(param_1 + 0x92) == *(char *)(param_1 + 0x93)) {
      AddOT__5WorldFiP8VIF1Prim(0x42bf10,*(undefined1 *)(param_1 + 0x92),uVar2);
      if ((long)((ulong)*(byte *)(param_1 + 0x81) << 0x3e) < 0) {
        chengeDetaleLevel__5ModelFUi(uVar2,2);
      }
    }
    else {
      AddDoubleOT__5WorldFiiP8VIF1Prim(0x42bf10,*(undefined1 *)(param_1 + 0x92),*(undefined1 *)(param_1 + 0x93),uVar2
                     );
      if ((long)((ulong)*(byte *)(param_1 + 0x81) << 0x3e) < 0) {
        chengeDetaleLevel__5ModelFUi(uVar2,1);
      }
    }
    DspMirror__11CFieldModelFv(param_1);
    DspModelEff__11CFieldModelFv(param_1);
  }
  return;
}

/* JP: 0x004c38c0  CFieldModel::Clr(int)   [Clr__11CFieldModelFi]  size=0x11c */
void Clr__11CFieldModelFi(int param_1,uint param_2)

{
  byte bVar1;
  undefined8 uVar2;
  
  bVar1 = *(byte *)(param_1 + 0x82);
  *(byte *)(param_1 + 0x82) =
       *(byte *)(param_1 + 0x82) & 0xf9 |
       (byte)(((uint)(((ulong)*(byte *)(param_1 + 0x82) << 0x3d) >> 0x3e) & ~param_2 & 0xff) << 1);
  if ((((ulong)bVar1 & 7) >> 1 == 3) && (((ulong)*(byte *)(param_1 + 0x82) & 7) >> 1 != 3)) {
    if (*(int *)(param_1 + 0x120) != 0) {
      Clr__8CBalIconFv(*(undefined4 *)(param_1 + 0x120));
    }
    ClrMirror__11CFieldModelFi(param_1,0);
    ClrModelEff__11CFieldModelFv(param_1);
    uVar2 = GetModel__11CFieldModelFv(param_1);
    ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,uVar2);
  }
  *(byte *)(param_1 + 0x81) = *(byte *)(param_1 + 0x81) & 0xdf;
  return;
}

/* JP: 0x004c39e0  CFieldModel::ClearModel()   [ClearModel__11CFieldModelFv]  size=0xc4 */
undefined4 ClearModel__11CFieldModelFv(int param_1)

{
  DspIcon__11CFieldModelFi(param_1,0xffffffffffffffff);
  ClrModelEff__11CFieldModelFv(param_1);
  if (((((ulong)*(byte *)(param_1 + 0x80) & 0xf) >> 2 & 1) != 0) ||
     (((ulong)*(byte *)(param_1 + 0x82) & 7) >> 1 == 3)) {
    Clr__11CFieldModelFi(param_1,2);
    *(byte *)(param_1 + 0x80) = *(byte *)(param_1 + 0x80) & 0xf3;
    *(byte *)(param_1 + 0x81) = *(byte *)(param_1 + 0x81) & 0xdf;
  }
  return 1;
}

/* JP: 0x004c3ab0  CFieldModel::DispShadow(ShadowControl*)   [DispShadow__11CFieldModelFP13ShadowControl]  size=0x28 */
undefined4 DispShadow__11CFieldModelFP13ShadowControl(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 0x2b8) = param_2;
  return 1;
}

/* JP: 0x004c3ae0  CFieldModel::ClearShadow()   [ClearShadow__11CFieldModelFv]  size=0xf4 */
undefined4 ClearShadow__11CFieldModelFv(int param_1)

{
  undefined8 uVar1;
  
  if ((long)((ulong)*(byte *)(param_1 + 0x80) << 0x3b) < 0) {
    if (*(int *)(param_1 + 0x2b8) != 0) {
      if ((*(int *)(param_1 + 0x124) != 0) && ((long)((ulong)*(byte *)(param_1 + 0x8c) << 0x3e) < 0)
         ) {
        *(byte *)(param_1 + 0x8c) = *(byte *)(param_1 + 0x8c) & 0xfd;
        releaseShadow__13ShadowControlFP5Model(*(undefined4 *)(param_1 + 0x2b8),*(undefined4 *)(param_1 + 0x124));
      }
      uVar1 = GetModel__11CFieldModelFv(param_1);
      releaseShadow__13ShadowControlFP5Model(*(undefined4 *)(param_1 + 0x2b8),uVar1);
    }
    *(byte *)(param_1 + 0x80) = *(byte *)(param_1 + 0x80) & 0xef;
  }
  *(undefined4 *)(param_1 + 0x2b8) = 0;
  return 1;
}

/* JP: 0x004c3be0  CFieldModel::DispClearCtrl()   [DispClearCtrl__11CFieldModelFv]  size=0x374 */
void DispClearCtrl__11CFieldModelFv(int param_1)

{
  undefined8 uVar1;
  undefined1 auStack_60 [16];
  undefined1 auStack_50 [16];
  undefined1 auStack_40 [12];
  float fStack_34;
  undefined1 auStack_30 [12];
  float fStack_24;
  float fStack_18;
  float fStack_14;
  int iStack_10;
  
  iStack_10 = param_1;
  uVar1 = GetModel__11CFieldModelFv(param_1);
  if (((ulong)*(byte *)(iStack_10 + 0x80) & 0xf) >> 2 == 1) {
    if (*(char *)(iStack_10 + 0x96) == '\x01') {
      __ct__7FVectorFv(auStack_30);
      fStack_14 = *(float *)(iStack_10 + 0x9c) / 0.8;
      getModelColor__5ModelFv(auStack_50,uVar1);
      __as__7FVectorFRC7FVector(auStack_30,auStack_50);
      if (1.0 < fStack_14) {
        fStack_14 = 1.0;
      }
      fStack_24 = fStack_14 * 128.0;
      setModelColor__5ModelFR7FVector(uVar1,auStack_30);
      if (*(int *)(iStack_10 + 0x140) != 0) {
        changeAlpha__15ModelEffManagerFP5Modelf(fStack_14 * 128.0,uVar1);
      }
      if (*(int *)(iStack_10 + 0x124) != 0) {
        setModelColor__5ModelFR7FVector(*(undefined4 *)(iStack_10 + 0x124),auStack_30);
      }
      if (1.0 <= fStack_14) {
        *(byte *)(iStack_10 + 0x80) = *(byte *)(iStack_10 + 0x80) & 0xf3 | 0xc;
        *(byte *)(iStack_10 + 0x8a) = *(byte *)(iStack_10 + 0x8a) & 0xfb | 4;
      }
    }
  }
  else if (*(char *)(iStack_10 + 0x96) == '\x01') {
    __ct__7FVectorFv(auStack_40);
    fStack_18 = *(float *)(iStack_10 + 0x9c) / 0.8;
    getModelColor__5ModelFv(auStack_60,uVar1);
    __as__7FVectorFRC7FVector(auStack_40,auStack_60);
    if (1.0 < fStack_18) {
      fStack_18 = 1.0;
    }
    fStack_34 = 128.0 - fStack_18 * 128.0;
    if (*(int *)(iStack_10 + 0x140) != 0) {
      changeAlpha__15ModelEffManagerFP5Modelf((1.0 - fStack_18) * 128.0,uVar1);
    }
    setModelColor__5ModelFR7FVector(uVar1,auStack_40);
    if (*(int *)(iStack_10 + 0x124) != 0) {
      setModelColor__5ModelFR7FVector(*(undefined4 *)(iStack_10 + 0x124),auStack_40);
    }
    if (1.0 <= fStack_18) {
      ClearShadow__11CFieldModelFv(iStack_10);
      ClearModel__11CFieldModelFv(iStack_10);
      *(byte *)(iStack_10 + 0x80) = *(byte *)(iStack_10 + 0x80) & 0xf3;
      *(byte *)(iStack_10 + 0x8a) = *(byte *)(iStack_10 + 0x8a) & 0xf7 | 8;
    }
  }
  return;
}

/* JP: 0x004c3f60  CFieldModel::SetViewPoint(FVector*, float, int, int)   [SetViewPoint__11CFieldModelFP7FVectorfii]  size=0xbc */
void SetViewPoint__11CFieldModelFP7FVectorfii
               (undefined4 param_1,int param_2,undefined4 param_3,undefined1 param_4,uint param_5)

{
  *(undefined1 *)(param_2 + 0xf3) = 1;
  if ((int)param_5 < 0) {
    __as__7FVectorFRC7FVector(param_2 + 0x50,param_3);
  }
  else if ((param_5 & 0x20000) == 0) {
    *(char *)(param_2 + 0xf3) = (char)param_5;
  }
  else {
    *(undefined1 *)(param_2 + 0xf3) = 2;
  }
  *(undefined4 *)(param_2 + 0xf8) = param_1;
  *(undefined1 *)(param_2 + 0xf2) = param_4;
  return;
}

/* JP: 0x004c4140  CFieldModel::UpdateViewPoint(float)   [UpdateViewPoint__11CFieldModelFf]  size=0xcc4 */
void UpdateViewPoint__11CFieldModelFf(float param_1,int param_2)

{
  bool bVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  undefined8 uVar5;
  int iVar6;
  float fVar7;
  undefined1 auStack_140 [16];
  undefined1 auStack_130 [16];
  undefined1 auStack_120 [16];
  undefined1 auStack_110 [16];
  undefined1 auStack_100 [4];
  float fStack_fc;
  undefined1 auStack_f0 [16];
  undefined1 auStack_e0 [4];
  undefined4 uStack_dc;
  undefined1 auStack_d0 [4];
  undefined4 uStack_cc;
  undefined1 auStack_c0 [4];
  float fStack_bc;
  undefined1 auStack_b0 [4];
  float fStack_ac;
  undefined1 auStack_a0 [68];
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
  float fStack_30;
  float fStack_2c;
  float fStack_28;
  float fStack_24;
  int iStack_20;
  float fStack_10;
  
  fStack_28 = 0.0;
  fStack_24 = 0.0;
  iStack_20 = param_2;
  fStack_10 = param_1;
  __ct__6MatrixFv(auStack_a0);
  fStack_2c = 0.0;
  fStack_30 = 0.0;
  fStack_34 = 0.0;
  fStack_38 = 0.0;
  lVar2 = SearchFrame__11CFieldModelFPCc(iStack_20,FRAME_NECK);
  if (lVar2 == 0) {
    lVar2 = SearchFrame__11CFieldModelFPCc(iStack_20,FRAME_HEAD);
  }
  fVar7 = fStack_24;
  if (*(char *)(iStack_20 + 0xf3) != '\0') {
    __ct__7FVectorFv(auStack_b0);
    __as__7FVectorFRC7FVector(auStack_b0,iStack_20 + 0x50);
    if ((*(byte *)(iStack_20 + 0xf3) & 0x80) == 0) {
      if (*(char *)(iStack_20 + 0xf3) == '\x02') {
        uVar5 = GetActiveCamera__9GsxCameraFv();
        uVar5 = GetFrame__9GsxCameraFv(uVar5);
        uVar5 = GetPos__6MatrixFv(uVar5);
        __as__7FVectorFRC7FVector(auStack_b0,uVar5);
      }
    }
    else {
      lVar3 = GetModel__6CFieldFi(sys__6CField,*(byte *)(iStack_20 + 0xf3) & 0x7f);
      if (lVar3 == 0) {
        *(undefined1 *)(iStack_20 + 0xf3) = 0;
        return;
      }
      GetPos__11CFieldModelFv(auStack_110,lVar3);
      __as__7FVectorFRC7FVector(auStack_b0,auStack_110);
      lVar4 = SearchFrame__11CFieldModelFPCc(lVar3,FRAME_NECK);
      bVar1 = lVar4 == 0;
      if (bVar1) {
        lVar4 = SearchFrame__11CFieldModelFPCc(lVar3,FRAME_HEAD);
      }
      if ((lVar4 != 0) && (getWorldPos__5FrameFi(auStack_c0,lVar4,m_Env__8VIF1Prim & 1), !bVar1)) {
        fStack_ac = fStack_bc - 1.5;
      }
    }
    __ct__7FVectorFRC7FVector(auStack_d0,iStack_20 + 0x10);
    getWorldPos__5FrameFi(auStack_e0,lVar2,m_Env__8VIF1Prim & 1);
    uStack_cc = uStack_dc;
    __ami__7FVectorFRC7FVector(auStack_b0,auStack_d0);
    __as__7FVectorFRC7FVector(auStack_d0,auStack_b0);
    uStack_cc = 0;
    fStack_40 = fStack_ac;
    fStack_3c = (float)Length__7FVectorCFv(auStack_d0);
    Normalize__7FVectorFv(auStack_d0);
    if ((*(float *)(iStack_20 + 0xf8) <= fStack_3c) || (*(float *)(iStack_20 + 0xf8) <= fStack_40))
    {
      fStack_24 = 0.0;
    }
    else {
      UnitMatrix__6MatrixFv(auStack_a0);
      RotYMatrix__6MatrixFf(*(undefined4 *)(iStack_20 + 0x24),auStack_a0);
      __ct__7FVectorFv(auStack_f0);
      uVar5 = __ct__7FVectorFffff(0,0,0xbf800000,0x3f800000,auStack_130);
      ApplyMatrix__6MatrixCFRC7FVector(auStack_120,auStack_a0,uVar5);
      __as__7FVectorFRC7FVector(auStack_f0,auStack_120);
      fStack_44 = (float)InnerProduct__7FVectorCFRC7FVector(auStack_f0,auStack_d0);
      __ct__7FVectorFv(auStack_100);
      OuterProduct__7FVectorCFRC7FVector(auStack_140,auStack_f0,auStack_d0);
      __as__7FVectorFRC7FVector(auStack_100,auStack_140);
      fStack_24 = fStack_44 * -1.570796 + 1.570796;
      if (fStack_3c != 0.0) {
        fStack_34 = (float)atanf(fStack_40 / fStack_3c);
        if (fStack_34 < -1.7) {
          fStack_34 = -1.7;
        }
        if (0.8 < fStack_34) {
          fStack_34 = 0.8;
        }
      }
      fStack_30 = fStack_fc;
    }
    fStack_48 = *(float *)(&clipTbl_4510 + (*(byte *)(iStack_20 + 0xf2) - 1) * 4);
    fVar7 = fStack_48;
    if (fStack_24 < fStack_48) {
      fVar7 = fStack_24;
    }
  }
  fStack_24 = fVar7;
  fStack_4c = *(float *)(iStack_20 + 0x108);
  if (fStack_30 < 0.0) {
    fStack_24 = -fStack_24;
  }
  fStack_50 = fStack_4c - fStack_24;
  if (fStack_50 < 0.0) {
    fStack_50 = -fStack_50;
  }
  if (fStack_50 < 0.02) {
    if (((ulong)*(byte *)(iStack_20 + 0x105) & 0x3f) >> 4 == 2) {
      *(byte *)(iStack_20 + 0x105) = *(byte *)(iStack_20 + 0x105) & 0xcf;
    }
  }
  else if ((((ulong)*(byte *)(iStack_20 + 0x105) & 0x3f) >> 4 == 2) && (fStack_50 < 0.087266445)) {
    *(byte *)(iStack_20 + 0x105) = *(byte *)(iStack_20 + 0x105) & 0xcf | 0x30;
    *(undefined1 *)(iStack_20 + 0x107) = 0;
  }
  if (((ulong)*(byte *)(iStack_20 + 0x105) & 0x3f) >> 4 == 0) {
    if (fStack_50 < 0.17453289) {
      fStack_50 = 0.0;
    }
    else {
      *(byte *)(iStack_20 + 0x105) = *(byte *)(iStack_20 + 0x105) & 0xcf | 0x10;
      *(undefined1 *)(iStack_20 + 0x107) = 0;
    }
  }
  if (((ulong)*(byte *)(iStack_20 + 0x105) & 0x3f) >> 4 == 1) {
    iVar6 = (uint)*(byte *)(iStack_20 + 0x107) + (int)(fStack_10 * 1000.0);
    if (iVar6 < 200) {
      *(char *)(iStack_20 + 0x107) = (char)iVar6;
      fStack_50 = (fStack_50 * (float)iVar6) / 200.0;
    }
    else {
      *(byte *)(iStack_20 + 0x105) = *(byte *)(iStack_20 + 0x105) & 0xcf | 0x20;
    }
  }
  if (((ulong)*(byte *)(iStack_20 + 0x105) & 0x3f) >> 4 == 3) {
    if (0.17453289 <= fStack_50) {
      *(byte *)(iStack_20 + 0x105) = *(byte *)(iStack_20 + 0x105) & 0xcf | 0x10;
      *(undefined1 *)(iStack_20 + 0x107) = 0;
    }
    else {
      iVar6 = (uint)*(byte *)(iStack_20 + 0x107) + (int)(fStack_10 * 1000.0);
      if (iVar6 < 300) {
        *(char *)(iStack_20 + 0x107) = (char)iVar6;
        fStack_50 = fStack_50 * (1.0 - (float)iVar6 / 300.0);
      }
      else {
        *(byte *)(iStack_20 + 0x105) = *(byte *)(iStack_20 + 0x105) & 0xcf;
      }
    }
  }
  if (fStack_50 < 0.7) {
    fStack_50 = 0.7;
  }
  else if (2.0 < fStack_50) {
    fStack_50 = 2.0;
  }
  fStack_10 = fStack_10 * fStack_50 * 5.0;
  bVar1 = false;
  if (fStack_24 < fStack_4c) {
    fStack_4c = fStack_4c - fStack_10;
    if (fStack_4c < fStack_24) {
      fStack_4c = fStack_24;
    }
    bVar1 = true;
  }
  else if (fStack_4c < fStack_24) {
    fStack_4c = fStack_4c + fStack_10;
    if (fStack_24 < fStack_4c) {
      fStack_4c = fStack_24;
    }
    bVar1 = true;
  }
  *(float *)(iStack_20 + 0x108) = fStack_4c;
  fStack_24 = fStack_4c;
  if (fStack_34 != *(float *)(iStack_20 + 0x110)) {
    bVar1 = true;
    fStack_34 = (float)InterPolPitch__Ffff(fStack_34,*(undefined4 *)(iStack_20 + 0x110),
                                           fStack_10 * 0.5);
    *(float *)(iStack_20 + 0x110) = fStack_34;
    fStack_38 = fStack_34;
    if (0.0 < fStack_34) {
      fStack_38 = fStack_34 * 0.7;
    }
  }
  if (*(char *)(iStack_20 + 0xf2) == '\x03') {
    fStack_54 = fStack_24;
    if (fStack_24 < 0.0) {
      fStack_54 = -fStack_24;
    }
    fStack_58 = 1.0;
    if (0.69813156 <= fStack_54) {
      fVar7 = (float)cosf(fStack_54 - 0.69813156);
      fStack_58 = fVar7 * 0.6 + 0.4;
    }
    if (fStack_58 < 1.0) {
      fStack_28 = fStack_24 * (1.0 - fStack_58);
      fStack_24 = fStack_24 * fStack_58;
    }
  }
  if ((bVar1) && (lVar2 != 0)) {
    fStack_2c = fStack_28 * 0.2;
    UnitMatrix__6MatrixFv(auStack_a0);
    RotZMatrix__6MatrixFf(fStack_2c,auStack_a0);
    if (fStack_2c < 0.0) {
      fStack_2c = -fStack_2c;
    }
    fStack_5c = fStack_38;
    fStack_2c = fStack_2c + fStack_38;
    uVar5 = RotXMatrix__6MatrixFf(fStack_2c,auStack_a0);
    RotYMatrix__6MatrixFf(fStack_24,auStack_a0,uVar5);
    __as__6MatrixFRC6Matrix((int)lVar2 + 0x160,auStack_a0);
    myMatrixUpdate__5FrameFv(lVar2);
  }
  lVar2 = SearchFrame__11CFieldModelFPCc(iStack_20,FRAME_UBODY);
  if ((bVar1) && (lVar2 != 0)) {
    UnitMatrix__6MatrixFv(auStack_a0);
    fStack_28 = (float)InterPolPitch__Ffff(fStack_28,*(undefined4 *)(iStack_20 + 0x10c),
                                           fStack_10 * 0.3);
    *(float *)(iStack_20 + 0x10c) = fStack_28;
    RotYMatrix__6MatrixFf(fStack_28,auStack_a0);
    __as__6MatrixFRC6Matrix((int)lVar2 + 0x160,auStack_a0);
    myMatrixUpdate__5FrameFv(lVar2);
  }
  return;
}

/* JP: 0x004c4fb0  CFieldModel::Update(float)   [Update__11CFieldModelFf]  size=0x1a84 */
void Update__11CFieldModelFf(float param_1,int param_2)

{
  bool bVar1;
  bool bVar2;
  char cVar3;
  char cVar4;
  undefined1 uVar5;
  undefined4 uVar6;
  int iVar7;
  undefined8 uVar8;
  long lVar9;
  undefined8 uVar10;
  long lVar11;
  byte bVar12;
  ulong uVar13;
  uint uVar14;
  int iVar15;
  undefined1 auStack_1e0 [64];
  undefined1 auStack_1a0 [64];
  undefined1 auStack_160 [64];
  undefined1 auStack_120 [4];
  float fStack_11c;
  undefined1 auStack_110 [8];
  float fStack_108;
  undefined1 auStack_100 [64];
  undefined1 auStack_c0 [4];
  undefined4 uStack_bc;
  undefined1 auStack_b0 [4];
  undefined4 uStack_ac;
  undefined4 uStack_8c;
  undefined4 uStack_88;
  int iStack_84;
  float fStack_80;
  float fStack_7c;
  float fStack_78;
  int iStack_74;
  int iStack_70;
  int iStack_6c;
  int iStack_68;
  uint uStack_64;
  int iStack_60;
  int iStack_5c;
  uint uStack_58;
  uint uStack_54;
  int iStack_50;
  float fStack_4c;
  float fStack_48;
  float fStack_44;
  float fStack_40;
  float fStack_3c;
  float fStack_38;
  float fStack_34;
  float fStack_30;
  undefined4 uStack_2c;
  uint uStack_28;
  undefined1 uStack_21;
  int iStack_20;
  float fStack_10;
  
  *(float *)(param_2 + 0x9c) = *(float *)(param_2 + 0x9c) + param_1;
  if ((long)((ulong)*(byte *)(param_2 + 0x82) << 0x3b) < 0) {
    return;
  }
  iStack_20 = param_2;
  fStack_10 = param_1;
  if (((long)((ulong)*(byte *)(param_2 + 0x84) << 0x3d) < 0) &&
     (*(int *)(*(int *)(param_2 + 0x148) + 8) != 0)) {
    *(byte *)(param_2 + 0x84) = *(byte *)(param_2 + 0x84) & 0xfb;
    ReadCB__11CFieldModelFP15_FieldDataCachei(param_2,*(undefined4 *)(param_2 + 0x148),0);
  }
  if (*(short *)(iStack_20 + 0x94) != 0) {
    for (uVar14 = 0; (int)uVar14 < 0x10; uVar14 = uVar14 + 1) {
      if ((((uint)*(ushort *)(iStack_20 + 0x94) & 1 << (uVar14 & 0x1f)) != 0) &&
         (*(int *)(*(int *)(iStack_20 + uVar14 * 4 + 0x14c) + 8) != 0)) {
        *(ushort *)(iStack_20 + 0x94) =
             *(ushort *)(iStack_20 + 0x94) & ~(ushort)(1 << (uVar14 & 0x1f));
        ReadCB__11CFieldModelFP15_FieldDataCachei
                  (iStack_20,*(undefined4 *)(iStack_20 + uVar14 * 4 + 0x14c),0);
      }
    }
    if (*(short *)(iStack_20 + 0x94) == 0) {
      *(byte *)(iStack_20 + 0x8a) = *(byte *)(iStack_20 + 0x8a) & 0xef | 0x10;
    }
  }
  if ((*(byte *)(iStack_20 + 0x80) & 3) < 3) {
    return;
  }
  if ((long)((ulong)*(byte *)(iStack_20 + 0x8c) << 0x3c) < 0) {
    *(byte *)(iStack_20 + 0x8c) = *(byte *)(iStack_20 + 0x8c) & 0xf7;
    uStack_28 = (uint)(((ulong)*(byte *)(iStack_20 + 0x89) << 0x3a) >> 0x3d);
    uStack_2c = GetModel__11CFieldModelFv(iStack_20);
    createMirror__11MirrorModelFP5Modelbbb(*(undefined4 *)(iStack_20 + 0x124),uStack_2c,(uStack_28 & 1) != 0,
                    ((int)uStack_28 >> 1 & 1U) != 0,((int)uStack_28 >> 2 & 1U) != 0);
    if (*(int *)(iStack_20 + 0x128) == 0) {
      createLevelofDetale__5ModelFP9BufMemoryUi(*(undefined4 *)(iStack_20 + 0x124),
                      *(undefined4 *)(*(int *)(iStack_20 + 0x148) + 8),2);
    }
    else {
      createLevelofDetale__5ModelFPUcUi(*(undefined4 *)(iStack_20 + 0x124),*(undefined4 *)(iStack_20 + 0x128),2);
    }
    if ((long)((ulong)*(byte *)(iStack_20 + 0x8c) << 0x3d) < 0) {
      DspMirror__11CFieldModelFv(iStack_20);
    }
  }
  fStack_30 = fStack_10 * *(float *)(iStack_20 + 0xb4);
  if ((*(byte *)(iStack_20 + 0x85) & 3) == 3) {
    fStack_3c = *(float *)(iStack_20 + 0x134);
    fStack_38 = *(float *)(iStack_20 + 0x34);
    if (fStack_38 < 0.0) {
      fStack_38 = fStack_38 + 6.283184;
    }
    *(float *)(iStack_20 + 0x13c) = *(float *)(iStack_20 + 0x13c) + fStack_30;
    fStack_44 = *(float *)(iStack_20 + 0x13c) / *(float *)(iStack_20 + 0x138);
    *(byte *)(iStack_20 + 0x86) = *(byte *)(iStack_20 + 0x86) & 0xe7 | 0x10;
    fStack_40 = fStack_44;
    fStack_40 = (float)GetSmoothVelocity__Ffffff
                                 (fStack_44,0x3e4ccccd,0x3dcccccd,0x3f333333,0x3f666666);
    if ((long)((ulong)*(byte *)(iStack_20 + 0x85) << 0x38) < 0) {
      if (fStack_3c < fStack_38) {
        fStack_38 = fStack_38 - 6.283184;
      }
    }
    else if (fStack_38 < fStack_3c) {
      fStack_38 = fStack_38 + 6.283184;
    }
    fStack_34 = fStack_3c + fStack_40 * (fStack_38 - fStack_3c);
    if (fStack_34 < 0.0) {
      fStack_34 = fStack_34 + 6.283184;
    }
    if (6.283184 <= fStack_34) {
      fStack_34 = fStack_34 - 6.283184;
    }
    if (3.141592 <= fStack_34) {
      fStack_34 = fStack_34 - 6.283184;
    }
    *(float *)(iStack_20 + 0x24) = fStack_34;
  }
  else {
    fStack_38 = *(float *)(iStack_20 + 0x34);
    fStack_34 = *(float *)(iStack_20 + 0x24);
    if (fStack_34 != fStack_38) {
      fStack_48 = fStack_30 * 6.283184 * *(float *)(iStack_20 + 0x2b4);
      if ((*(char *)(iStack_20 + 0xbc) != '\0') && (*(float *)(iStack_20 + 0xb8) == 0.0)) {
        fStack_48 = fStack_30 * 12.566368 * 0.1;
      }
      if (fStack_34 < 0.0) {
        fStack_34 = fStack_34 + 6.283184;
      }
      if (fStack_38 < 0.0) {
        fStack_38 = fStack_38 + 6.283184;
      }
      iStack_50 = 0;
      if (fStack_34 < fStack_38) {
        fStack_4c = fStack_38 - fStack_34;
      }
      else {
        fStack_4c = fStack_34 - fStack_38;
      }
      uStack_54 = (uint)(fStack_34 >= fStack_38);
      if ((long)((ulong)*(byte *)(iStack_20 + 0x85) << 0x38) < 0) {
        fStack_34 = fStack_34 - fStack_48;
        if (uStack_54 == 0) {
          fStack_7c = fStack_38 - 6.283184;
        }
        else {
          fStack_7c = fStack_38;
        }
        if (fStack_34 < fStack_7c) {
          fStack_34 = *(float *)(iStack_20 + 0x34);
          iStack_50 = 1;
        }
      }
      else {
        fStack_34 = fStack_34 + fStack_48;
        if (uStack_54 == 0) {
          fStack_78 = fStack_38;
        }
        else {
          fStack_78 = fStack_38 + 6.283184;
        }
        if (fStack_78 < fStack_34) {
          fStack_34 = *(float *)(iStack_20 + 0x34);
          iStack_50 = 1;
        }
      }
      if (fStack_34 < -3.141592) {
        fStack_34 = fStack_34 + 6.283184;
      }
      if (3.141592 < fStack_34) {
        fStack_34 = fStack_34 - 6.283184;
      }
      *(float *)(iStack_20 + 0x24) = fStack_34;
      if (iStack_50 != 0) {
        if ((*(byte *)(iStack_20 + 0x85) & 3) == 2) {
          *(byte *)(iStack_20 + 0x85) = *(byte *)(iStack_20 + 0x85) & 0xfc;
          *(byte *)(iStack_20 + 0x86) = *(byte *)(iStack_20 + 0x86) & 0xe7 | 0x10;
          PlayMoveMotion__11CFieldModelFi(iStack_20,0);
        }
        else {
          *(byte *)(iStack_20 + 0x86) = *(byte *)(iStack_20 + 0x86) & 0xe7;
        }
        *(byte *)(iStack_20 + 0x8a) = *(byte *)(iStack_20 + 0x8a) & 0x7f | 0x80;
      }
    }
  }
  *(undefined4 *)(iStack_20 + 0x20) = *(undefined4 *)(iStack_20 + 0x30);
  *(undefined4 *)(iStack_20 + 0x28) = *(undefined4 *)(iStack_20 + 0x38);
  if (((ulong)*(byte *)(iStack_20 + 0x84) & 0x3f) >> 4 != 0) {
    if ((*(byte *)(iStack_20 + 0x81) & 1) == 0) {
      return;
    }
    DispModel__11CFieldModelFiii
              (iStack_20,0xffffffffffffffff,0xffffffffffffffff,*(undefined1 *)(iStack_20 + 0x96));
    *(byte *)(iStack_20 + 0x84) = *(byte *)(iStack_20 + 0x84) & 0xcf;
  }
  uVar8 = GetModel__11CFieldModelFv(iStack_20);
  lVar9 = GetFrame__11CFieldModelFv(iStack_20);
  if (lVar9 == 0) {
    return;
  }
  if (((ulong)*(byte *)(iStack_20 + 0x80) & 0xf) >> 2 == 0) {
    return;
  }
  if (((ulong)*(byte *)(iStack_20 + 0x80) & 0xf) >> 2 != 3) {
    DispClearCtrl__11CFieldModelFv(iStack_20);
  }
  if ((*(int *)(iStack_20 + 0x2b8) != 0) &&
     (-1 < (long)((ulong)*(byte *)(iStack_20 + 0x80) << 0x3b))) {
    if ((-1 < (long)((ulong)*(byte *)(iStack_20 + 0x81) << 0x3d)) &&
       (*(int *)(iStack_20 + 0x128) == 0)) {
      *(byte *)(iStack_20 + 0x81) = *(byte *)(iStack_20 + 0x81) & 0xfb | 4;
      createLevelofDetale__5ModelFP9BufMemoryUi(uVar8,*(undefined4 *)(*(int *)(iStack_20 + 0x148) + 8),2);
    }
    setDropShadow__13ShadowControlFP5Model(*(undefined4 *)(iStack_20 + 0x2b8),uVar8);
    if (((*(int *)(iStack_20 + 0x124) != 0) &&
        ((((ulong)*(byte *)(iStack_20 + 0x89) & 0x3f) >> 3 & 2) == 0)) &&
       (-1 < (long)((ulong)*(byte *)(iStack_20 + 0x8c) << 0x3e))) {
      *(byte *)(iStack_20 + 0x8c) = *(byte *)(iStack_20 + 0x8c) & 0xfd | 2;
      setDropShadow__13ShadowControlFP5Model(*(undefined4 *)(iStack_20 + 0x2b8),*(undefined4 *)(iStack_20 + 0x124));
    }
    *(byte *)(iStack_20 + 0x80) = *(byte *)(iStack_20 + 0x80) & 0xef | 0x10;
  }
  AddTime__11CFieldModelFf(fStack_30,iStack_20);
  if (*(int *)(iStack_20 + 0x120) != 0) {
    uVar10 = GetModel__11CFieldModelFv(iStack_20);
    CalcModelBBox__FP5ModelPf(uVar10,auStack_b0);
    __ct__7FVectorFRC7FVector(auStack_c0,iStack_20 + 0x10);
    uStack_bc = uStack_ac;
    SetCenter__8CBalIconFP7FVector(*(undefined4 *)(iStack_20 + 0x120),auStack_c0);
    AddTime__8CBalIconFf(fStack_10,*(undefined4 *)(iStack_20 + 0x120));
  }
  if ((long)((ulong)*(byte *)(iStack_20 + 0x81) << 0x3e) < 0) {
    uVar10 = GetMatrix__9GsxCameraFv(camera__4CApp);
    __ct__6MatrixFRC6Matrix(auStack_100,uVar10);
    ApplyMatrix__6MatrixCFRC7FVector(auStack_110,auStack_100,iStack_20 + 0x10);
    chengeDetaleLevel__5ModelFUi(uVar8,80.0 < fStack_108);
  }
  if ((((ulong)*(byte *)(iStack_20 + 0x85) & 0xf) >> 2 != 0) &&
     (-1 < (long)((ulong)*(byte *)(iStack_20 + 0x85) << 0x39))) {
    bVar12 = *(byte *)(iStack_20 + 0x86) & 7;
    if (bVar12 == 4) {
      iStack_60 = HitChkM2M__11CFieldModelFf(0x40800000,iStack_20);
      if (iStack_60 == 0) {
        *(byte *)(iStack_20 + 0x86) = *(byte *)(iStack_20 + 0x86) & 0xf8;
      }
    }
    else {
      if (bVar12 != 3) {
        if (bVar12 != 2) {
          if ((*(byte *)(iStack_20 + 0x86) & 7) == 0) {
            uVar13 = ((ulong)*(byte *)(iStack_20 + 0x85) & 0xf) >> 2;
            if (uVar13 == 2) {
              UpdatePathMove__11CFieldModelFf(fStack_10,iStack_20);
            }
            else if (uVar13 == 1) {
              UpdateAutoMove__11CFieldModelFf(fStack_10,iStack_20);
            }
          }
          goto LAB_004c5fd8;
        }
        *(byte *)(iStack_20 + 0x85) = *(byte *)(iStack_20 + 0x85) & 0xcf | 0x30;
        PlayMoveMotion__11CFieldModelFi(iStack_20,0);
        uVar6 = GetTimer__7SysToolFv();
        *(undefined4 *)(iStack_20 + 0xcc) = uVar6;
        iVar7 = GetRand__Fi(800);
        *(int *)(iStack_20 + 0xd0) = iVar7 + 200;
        *(byte *)(iStack_20 + 0x86) =
             *(byte *)(iStack_20 + 0x86) & 0xf8 | (*(byte *)(iStack_20 + 0x86) & 7) + 1 & 7;
      }
      iVar7 = GetTimer__7SysToolFv();
      uStack_58 = iVar7 - *(int *)(iStack_20 + 0xcc);
      if (*(uint *)(iStack_20 + 0xd0) <= uStack_58) {
        lVar9 = GetRand__Fi(10);
        if (2 < lVar9) {
          __ct__7FVectorFRC7FVector(auStack_120,iStack_20 + 0x20);
          lVar9 = GetRand__Fi(2);
          if (lVar9 == 0) {
            fStack_80 = -1.570796;
          }
          else {
            fStack_80 = 1.570796;
          }
          fStack_11c = fStack_11c + fStack_80;
          SetDir__11CFieldModelFR7FVectorii(iStack_20,auStack_120,3,1);
        }
        iStack_5c = AutoAvoid__11CFieldModelFv(iStack_20);
        if (iStack_5c < 0) {
          *(byte *)(iStack_20 + 0x86) = *(byte *)(iStack_20 + 0x86) & 0xf8 | 2;
        }
        else {
          *(byte *)(iStack_20 + 0x86) = *(byte *)(iStack_20 + 0x86) & 0xf8;
          if (iStack_5c == 0) {
            *(byte *)(iStack_20 + 0x19a) = *(byte *)(iStack_20 + 0x19a) & 0xfe;
          }
          UpdateNodeLen__11CFieldModelFv(iStack_20);
        }
      }
    }
  }
LAB_004c5fd8:
  if ((*(byte *)(iStack_20 + 0x89) & 1) != 0) {
    bVar2 = false;
    iVar7 = *(byte *)(iStack_20 + 0x106) - 1;
    bVar1 = iVar7 < 1;
    if (bVar1) {
      iVar7 = 0;
    }
    *(char *)(iStack_20 + 0x106) = (char)iVar7;
    if ((long)((ulong)*(byte *)(iStack_20 + 0x105) << 0x3e) < 0) {
      iVar7 = iVar7 >> 1;
    }
    bVar12 = *(byte *)(iStack_20 + 0x104) >> 5;
    if (bVar12 == 4) {
      bVar2 = true;
    }
    else if ((bVar12 == 3) || (bVar12 == 2)) {
      uStack_64 = (uint)(((ulong)*(byte *)(iStack_20 + 0x105) << 0x3c) >> 0x3e) + 2;
      if ((*(byte *)(iStack_20 + 0x104) & 0x1f) < uStack_64) {
        if (bVar1) {
          *(byte *)(iStack_20 + 0x104) =
               *(byte *)(iStack_20 + 0x104) & 0xe0 |
               (*(byte *)(iStack_20 + 0x104) & 0x1f) + 1 & 0x1f;
          if ((long)((ulong)*(byte *)(iStack_20 + 0x105) << 0x3e) < 0) {
            uStack_8c = 4;
          }
          else {
            uStack_8c = 2;
          }
          *(char *)(iStack_20 + 0x106) = (char)uStack_8c;
          bVar2 = true;
        }
      }
      else {
        bVar2 = true;
      }
      if ((*(byte *)(iStack_20 + 0x104) >> 5 == 3) &&
         (uStack_64 <= (*(byte *)(iStack_20 + 0x104) & 0x1f))) {
        *(byte *)(iStack_20 + 0x104) = *(byte *)(iStack_20 + 0x104) & 0x1f;
      }
    }
    else if (bVar12 == 0) {
      if ((*(byte *)(iStack_20 + 0x104) & 0x1f) == 0) {
        *(byte *)(iStack_20 + 0x89) = *(byte *)(iStack_20 + 0x89) & 0xfe;
      }
      else if (bVar1) {
        bVar2 = true;
        *(byte *)(iStack_20 + 0x104) =
             *(byte *)(iStack_20 + 0x104) & 0xe0 | (*(byte *)(iStack_20 + 0x104) & 0x1f) - 1 & 0x1f;
        if ((long)((ulong)*(byte *)(iStack_20 + 0x105) << 0x3e) < 0) {
          uStack_88 = 4;
        }
        else {
          uStack_88 = 2;
        }
        *(char *)(iStack_20 + 0x106) = (char)uStack_88;
      }
    }
    else if (bVar12 == 1) {
      if ((*(byte *)(iStack_20 + 0x105) & 1) == 1) {
        iVar15 = (uint)(((ulong)*(byte *)(iStack_20 + 0x105) << 0x3c) >> 0x3e) + 2;
        if (iVar7 < iVar15) {
          bVar2 = true;
          *(byte *)(iStack_20 + 0x104) =
               *(byte *)(iStack_20 + 0x104) & 0xe0 | (char)iVar15 - (char)iVar7 & 0x1fU;
          if (bVar1) {
            *(byte *)(iStack_20 + 0x105) = *(byte *)(iStack_20 + 0x105) & 0xfe;
            if ((long)((ulong)*(byte *)(iStack_20 + 0x105) << 0x3e) < 0) {
              iStack_84 = iVar15 * 4 + 3;
            }
            else {
              iStack_84 = iVar15 * 2 + 1;
            }
            *(char *)(iStack_20 + 0x106) = (char)iStack_84;
          }
        }
      }
      else {
        bVar2 = true;
        *(byte *)(iStack_20 + 0x104) =
             *(byte *)(iStack_20 + 0x104) & 0xe0 | (byte)(iVar7 >> 1) & 0x1f;
        if (bVar1) {
          *(byte *)(iStack_20 + 0x105) = *(byte *)(iStack_20 + 0x105) & 0xfe | 1;
          cVar3 = GetRand__Fi(0x3c);
          *(char *)(iStack_20 + 0x106) = cVar3 + '@';
          if ((long)((ulong)*(byte *)(iStack_20 + 0x105) << 0x3e) < 0) {
            *(char *)(iStack_20 + 0x106) = *(char *)(iStack_20 + 0x106) << 1;
          }
        }
      }
    }
    if (bVar2) {
      changeTextureAnim__5ModelFPcUi(uVar8,0x5561c8,*(byte *)(iStack_20 + 0x104) & 0x1f);
    }
  }
  if (((ulong)*(byte *)(iStack_20 + 0x89) & 7) >> 1 == 0) {
    if (*(char *)(iStack_20 + 0x103) != '\0') {
      *(char *)(iStack_20 + 0x103) = *(char *)(iStack_20 + 0x103) + -1;
      lVar9 = SearchFrame__11CFieldModelFPCc(iStack_20,0x5561d0);
      if (lVar9 != 0) {
        __ct__6MatrixFv(auStack_1a0);
        UnitMatrix__6MatrixFv(auStack_1a0);
        RotXMatrix__6MatrixFf((float)(int)*(char *)(iStack_20 + 0x103) * 0.017453289,auStack_1a0);
        __as__6MatrixFRC6Matrix((int)lVar9 + 0x160,auStack_1a0);
        myMatrixUpdate__5FrameFv(lVar9);
      }
    }
  }
  else {
    iStack_68 = 0;
    iStack_6c = 10;
    cVar3 = *(char *)(iStack_20 + 0x101);
    if (cVar3 == '\x02') {
      uStack_21 = *(char *)(iStack_20 + 0x103) < *(char *)(iStack_20 + 0x102);
      if ((bool)uStack_21) {
        uVar14 = (uint)*(byte *)(iStack_20 + 0x100);
      }
      else {
        uVar14 = -(uint)*(byte *)(iStack_20 + 0x100);
      }
      lVar9 = (long)(int)((int)*(char *)(iStack_20 + 0x103) + uVar14);
      if ((((bool)uStack_21) && (*(char *)(iStack_20 + 0x102) <= lVar9)) ||
         ((!(bool)uStack_21 && (lVar9 <= *(char *)(iStack_20 + 0x102))))) {
        lVar9 = (long)*(char *)(iStack_20 + 0x102);
        uVar5 = GetRand__Fi(10);
        *(undefined1 *)(iStack_20 + 0x100) = uVar5;
        if ((*(char *)(iStack_20 + 0x103) < '\x03') && (lVar11 = GetRand__Fi(10), lVar11 < 5)) {
          cVar3 = GetRand__Fi(0x14);
          *(char *)(iStack_20 + 0x100) = *(char *)(iStack_20 + 0x100) + cVar3;
        }
        *(undefined1 *)(iStack_20 + 0x101) = 1;
      }
      *(char *)(iStack_20 + 0x103) = (char)lVar9;
      iStack_68 = 1;
    }
    else if ((cVar3 == '\x01') || (cVar3 == '\0')) {
      cVar3 = *(char *)(iStack_20 + 0x100);
      *(char *)(iStack_20 + 0x100) = cVar3 + -1;
      if (cVar3 == '\0') {
        lVar9 = GetRand__Fi(100);
        if (lVar9 < 7) {
          cVar3 = '\0';
        }
        else if (lVar9 < 0x41) {
          cVar3 = GetRand__Fi(iStack_6c >> 1);
          cVar3 = cVar3 + '\x01';
        }
        else {
          cVar3 = GetRand__Fi(iStack_6c >> 1);
          cVar3 = (char)(iStack_6c >> 1) + cVar3;
        }
        cVar4 = GetRand__Fi(4);
        *(char *)(iStack_20 + 0x100) = cVar4 + '\x02';
        *(char *)(iStack_20 + 0x102) = cVar3;
        *(undefined1 *)(iStack_20 + 0x101) = 2;
      }
      else if (*(char *)(iStack_20 + 0x103) != '\0') {
        *(char *)(iStack_20 + 0x103) = *(char *)(iStack_20 + 0x103) + -1;
        iStack_68 = 1;
      }
    }
    if ((iStack_68 != 0) &&
       (iStack_70 = SearchFrame__11CFieldModelFPCc(iStack_20,0x5561d0), iStack_70 != 0)) {
      __ct__6MatrixFv(auStack_160);
      uVar8 = UnitMatrix__6MatrixFv(auStack_160);
      RotXMatrix__6MatrixFf
                ((float)(int)*(char *)(iStack_20 + 0x103) * 0.017453289,auStack_160,uVar8);
      __as__6MatrixFRC6Matrix(iStack_70 + 0x160,auStack_160);
      myMatrixUpdate__5FrameFv(iStack_70);
    }
  }
  __ct__6MatrixFv(auStack_1e0);
  UnitMatrix__6MatrixFv(auStack_1e0);
  RotXMatrix__6MatrixFf(*(undefined4 *)(iStack_20 + 0x20),auStack_1e0);
  uVar8 = RotYMatrix__6MatrixFf(*(undefined4 *)(iStack_20 + 0x24),auStack_1e0);
  RotZMatrix__6MatrixFf(*(undefined4 *)(iStack_20 + 0x28),auStack_1e0,uVar8);
  TransMatrix__6MatrixFRC7FVector(auStack_1e0,iStack_20 + 0x10);
  iStack_74 = GetFrame__11CFieldModelFv(iStack_20);
  __as__6MatrixFRC6Matrix(iStack_74 + 0x160,auStack_1e0);
  if ((((ulong)*(byte *)(iStack_20 + 0x88) & 7) >> 1 & 1) != 0) {
    myMatrixUpdate__5FrameFv(iStack_74);
  }
  UpdateViewPoint__11CFieldModelFf(fStack_10,iStack_20);
  CalcMatrix__11CFieldModelFv(iStack_20);
  *(byte *)(iStack_20 + 0x81) = *(byte *)(iStack_20 + 0x81) & 0xdf | 0x20;
  return;
}

/* JP: 0x004c6a60  CFieldModel::GetFramePos(char*)   [GetFramePos__11CFieldModelFPc]  size=0x9c */
void GetFramePos__11CFieldModelFPc(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  long lVar1;
  undefined1 auStack_50 [16];
  undefined1 auStack_40 [16];
  undefined4 uStack_30;
  undefined4 uStack_20;
  undefined4 uStack_10;
  
  uStack_30 = param_1;
  uStack_20 = param_2;
  uStack_10 = param_3;
  lVar1 = SearchFrame__11CFieldModelFPCc(param_2,param_3);
  __ct__7FVectorFv(auStack_40);
  Origin__7FVectorFv(auStack_40);
  if (lVar1 != 0) {
    getWorldPos__5FrameFi(auStack_50,lVar1,m_Env__8VIF1Prim & 1);
    __as__7FVectorFRC7FVector(auStack_40,auStack_50);
  }
  __ct__7FVectorFRC7FVector(uStack_30,auStack_40);
  return;
}

/* JP: 0x004c6b00  CFieldModel::SetPos(FVector, bool)   [SetPos__11CFieldModelF7FVectorb]  size=0xec */
void SetPos__11CFieldModelF7FVectorb(int param_1,undefined4 param_2,char param_3)

{
  long lVar1;
  undefined1 auStack_70 [64];
  int iStack_30;
  undefined4 uStack_20;
  char cStack_10;
  
  iStack_30 = param_1;
  uStack_20 = param_2;
  cStack_10 = param_3;
  __as__7FVectorFRC7FVector(param_1 + 0x10,param_2);
  if (cStack_10 != '\0') {
    __ct__6MatrixFv(auStack_70);
    UnitMatrix__6MatrixFv(auStack_70);
    RotXMatrix__6MatrixFf(*(undefined4 *)(iStack_30 + 0x20),auStack_70);
    RotYMatrix__6MatrixFf(*(undefined4 *)(iStack_30 + 0x24),auStack_70);
    RotZMatrix__6MatrixFf(*(undefined4 *)(iStack_30 + 0x28),auStack_70);
    TransMatrix__6MatrixFRC7FVector(auStack_70,iStack_30 + 0x10);
    lVar1 = GetFrame__11CFieldModelFv(iStack_30);
    if (lVar1 != 0) {
      __as__6MatrixFRC6Matrix((int)lVar1 + 0x160,auStack_70);
      myMatrixUpdate__5FrameFv(lVar1);
    }
  }
  return;
}

/* JP: 0x004c6d70  CFieldModel::GetWorldPos()   [GetWorldPos__11CFieldModelFv]  size=0xf8 */
void GetWorldPos__11CFieldModelFv(undefined4 param_1,int param_2)

{
  undefined1 auStack_90 [16];
  undefined1 auStack_80 [16];
  undefined1 auStack_70 [64];
  undefined1 auStack_30 [12];
  undefined4 uStack_24;
  undefined4 uStack_20;
  int iStack_10;
  
  uStack_20 = param_1;
  iStack_10 = param_2;
  if (*(char *)(param_2 + 0xfc) == -1) {
    __ct__7FVectorFRC7FVector(param_1,param_2 + 0x10);
  }
  else {
    __ct__7FVectorFv(auStack_30);
    getWorldRot__5FrameFi(auStack_70,*(undefined4 *)(iStack_10 + 0xf4),m_Env__8VIF1Prim & 1);
    getWorldPos__5FrameFi(auStack_80,*(undefined4 *)(iStack_10 + 0xf4),m_Env__8VIF1Prim & 1);
    SetPos__6MatrixFRC7FVector(auStack_70,auStack_80);
    ApplyMatrix__6MatrixCFRC7FVector(auStack_90,auStack_70,iStack_10 + 0x10);
    __as__7FVectorFRC7FVector(auStack_30,auStack_90);
    uStack_24 = 0x3f800000;
    __ct__7FVectorFRC7FVector(uStack_20,auStack_30);
  }
  return;
}

/* JP: 0x004c6ef0  CFieldModel::GetDir()   [GetDir__11CFieldModelFv]  size=0xa4 */
int GetDir__11CFieldModelFv(int param_1)

{
  int iVar1;
  float fVar2;
  
  fVar2 = *(float *)(param_1 + 0x24);
  if (0.0 <= fVar2) {
    iVar1 = (int)(fVar2 * 5.0929594);
  }
  else {
    iVar1 = (int)(fVar2 * 5.0929594) + 0x20;
  }
  return iVar1 % 0x1f;
}

/* JP: 0x004c7060  CFieldModel::SetDir(int, int, int)   [SetDir__11CFieldModelFiii]  size=0x80 */
void SetDir__11CFieldModelFiii(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined1 auStack_50 [4];
  undefined4 uStack_4c;
  undefined4 uStack_40;
  int iStack_30;
  undefined4 uStack_20;
  undefined4 uStack_10;
  
  uStack_40 = param_1;
  iStack_30 = param_2;
  uStack_20 = param_3;
  uStack_10 = param_4;
  __ct__7FVectorFffff(0,0,0,0x3f800000,auStack_50);
  if (-1 < iStack_30) {
    uStack_4c = GetRotAngle__Fi(iStack_30);
  }
  SetDir__11CFieldModelFR7FVectorii(uStack_40,auStack_50,uStack_20,uStack_10);
  return;
}

/* JP: 0x004c70e0  CFieldModel::SetDir(FVector&, int, int)   [SetDir__11CFieldModelFR7FVectorii]  size=0x6dc */
void SetDir__11CFieldModelFR7FVectorii(int param_1,undefined4 param_2,uint param_3,int param_4)

{
  undefined8 uVar1;
  long lVar2;
  long lVar3;
  undefined4 uVar4;
  undefined1 auStack_d0 [16];
  undefined1 auStack_c0 [16];
  undefined1 auStack_b0 [64];
  undefined1 auStack_70 [16];
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  float fStack_50;
  float fStack_4c;
  float fStack_48;
  float fStack_44;
  int iStack_40;
  undefined4 uStack_30;
  uint uStack_20;
  int iStack_10;
  
  iStack_40 = param_1;
  uStack_30 = param_2;
  uStack_20 = param_3;
  iStack_10 = param_4;
  __as__7FVectorFRC7FVector(param_1 + 0x30,param_2);
  *(undefined4 *)(iStack_40 + 0x2b4) = 0x3f800000;
  uVar4 = ClipRadian__Ff(*(undefined4 *)(iStack_40 + 0x34));
  *(undefined4 *)(iStack_40 + 0x34) = uVar4;
  if (uStack_20 == 0) {
    __as__7FVectorFRC7FVector(iStack_40 + 0x20,iStack_40 + 0x30);
    *(byte *)(iStack_40 + 0x8a) = *(byte *)(iStack_40 + 0x8a) & 0x7f | 0x80;
    return;
  }
  if (iStack_10 < 0) {
    *(float *)(iStack_40 + 0x2b4) = -1.0 / (float)iStack_10;
  }
  else {
    *(float *)(iStack_40 + 0x2b4) = (float)(iStack_10 + 1) * 0.25;
  }
  __ct__7FVectorFv(&uStack_60);
  __ct__7FVectorFv(auStack_70);
  fStack_48 = *(float *)(iStack_40 + 0x34);
  fStack_44 = *(float *)(iStack_40 + 0x24);
  uStack_5c = 0;
  uStack_60 = 0;
  uStack_54 = 0x3f800000;
  uStack_58 = 0x3f800000;
  __ct__6MatrixFv(auStack_b0);
  UnitMatrix__6MatrixFv(auStack_b0);
  RotYMatrix__6MatrixFf(fStack_48,auStack_b0);
  ApplyMatrix__6MatrixCFRC7FVector(auStack_c0,auStack_b0,&uStack_60);
  __as__7FVectorFRC7FVector(auStack_70,auStack_c0);
  UnitMatrix__6MatrixFv(auStack_b0);
  RotYMatrix__6MatrixFf(fStack_44,auStack_b0);
  ApplyMatrix__6MatrixCFRC7FVector(auStack_d0,auStack_b0,&uStack_60);
  __as__7FVectorFRC7FVector(&uStack_60,auStack_d0);
  fStack_4c = (float)InnerProduct__7FVectorCFRC7FVector(&uStack_60,auStack_70);
  if (0.999 <= fStack_4c) {
    *(undefined4 *)(iStack_40 + 0x24) = *(undefined4 *)(iStack_40 + 0x34);
    *(byte *)(iStack_40 + 0x8a) = *(byte *)(iStack_40 + 0x8a) & 0x7f | 0x80;
    return;
  }
  *(byte *)(iStack_40 + 0x8a) = *(byte *)(iStack_40 + 0x8a) & 0x7f;
  if ((int)uStack_20 < 4) {
    if (fStack_44 < 0.0) {
      fStack_44 = fStack_44 + 6.283184;
    }
    if (fStack_48 < 0.0) {
      fStack_48 = fStack_48 + 6.283184;
    }
    if (fStack_48 < fStack_44) {
      fStack_44 = fStack_44 - 3.141592;
    }
    else {
      fStack_48 = fStack_48 - 3.141592;
    }
    *(byte *)(iStack_40 + 0x85) = *(byte *)(iStack_40 + 0x85) & 0x7f | (fStack_44 <= fStack_48) << 7
    ;
    *(byte *)(iStack_40 + 0x85) = *(byte *)(iStack_40 + 0x85) & 0xfc | (byte)uStack_20 & 1;
  }
  else {
    *(byte *)(iStack_40 + 0x85) = *(byte *)(iStack_40 + 0x85) & 0x7f | (byte)((uStack_20 & 1) << 7);
    *(byte *)(iStack_40 + 0x85) =
         *(byte *)(iStack_40 + 0x85) & 0xfc | (byte)((int)uStack_20 >> 1) & 1;
  }
  if ((*(byte *)(iStack_40 + 0x85) & 3) == 0) {
    return;
  }
  if (*(float *)(iStack_40 + 0x34) == *(float *)(iStack_40 + 0x24)) {
    return;
  }
  *(byte *)(iStack_40 + 0x85) = *(byte *)(iStack_40 + 0x85) & 0xfc | 2;
  *(byte *)(iStack_40 + 0x86) = *(byte *)(iStack_40 + 0x86) & 0xe7 | 8;
  lVar3 = -1;
  if (-1 < (long)((ulong)*(byte *)(iStack_40 + 0x85) << 0x38)) {
    uVar1 = GetMotionName__FUi(0x2a);
    lVar2 = FindMotionData__11CFieldModelFPCc(iStack_40,uVar1);
    if (lVar2 != 0) {
      if (fStack_4c < 0.5) {
        lVar3 = 0x2a;
      }
      else {
        lVar3 = 0;
      }
      goto LAB_004c7678;
    }
  }
  if (*(char *)(iStack_40 + 0x85) < '\0') {
    uVar1 = GetMotionName__FUi(0x29);
    lVar2 = FindMotionData__11CFieldModelFPCc(iStack_40,uVar1);
    if (lVar2 != 0) {
      if (fStack_4c < 0.5) {
        lVar3 = 0x29;
      }
      else {
        lVar3 = 0;
      }
    }
  }
LAB_004c7678:
  if (lVar3 < 1) {
    if (lVar3 == 0) {
      *(float *)(iStack_40 + 0x2b4) = *(float *)(iStack_40 + 0x2b4) / (2.0 - fStack_4c);
    }
    PlayMoveMotion__11CFieldModelFi(iStack_40,1);
  }
  else {
    ResetMotion__11CFieldModelFv(iStack_40);
    *(byte *)(iStack_40 + 0x81) = *(byte *)(iStack_40 + 0x81) & 0xdf | 0x20;
    SetMotion__11CFieldModelFi(iStack_40,lVar3);
    *(byte *)(iStack_40 + 0x85) = *(byte *)(iStack_40 + 0x85) & 0xfc | 3;
    fStack_50 = *(float *)(iStack_40 + 0x24);
    if (fStack_50 < 0.0) {
      fStack_50 = fStack_50 + 6.283184;
    }
    *(float *)(iStack_40 + 0x134) = fStack_50;
    *(byte *)(iStack_40 + 0x86) = *(byte *)(iStack_40 + 0x86) & 0xe7;
    *(undefined4 *)(iStack_40 + 0x13c) = 0;
  }
  return;
}

/* JP: 0x004c77c0  CFieldModel::ResetMotion()   [ResetMotion__11CFieldModelFv]  size=0x1c */
void ResetMotion__11CFieldModelFv(int param_1)

{
  *(undefined1 *)(param_1 + 700) = 0;
  return;
}

/* JP: 0x004c77e0  CFieldModel::HitChkM2M(float)   [HitChkM2M__11CFieldModelFf]  size=0x244 */
int HitChkM2M__11CFieldModelFf(float param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  long lVar3;
  int iVar4;
  undefined1 auStack_b0 [16];
  undefined1 auStack_a0 [16];
  undefined1 auStack_90 [16];
  undefined1 auStack_80 [64];
  undefined1 auStack_40 [24];
  float fStack_28;
  float fStack_24;
  int iStack_20;
  float fStack_10;
  
  iStack_20 = param_2;
  fStack_10 = param_1;
  __ct__7FVectorFv(auStack_40);
  __ct__6MatrixFv(auStack_80);
  __ct__7FVectorFffff(0,0,0xbf800000,0x3f800000,auStack_90);
  UnitMatrix__6MatrixFv(auStack_80);
  RotYMatrix__6MatrixFf(*(undefined4 *)(iStack_20 + 0x24),auStack_80);
  ApplyMatrix__6MatrixCFRC7FVector(auStack_a0,auStack_80,auStack_90);
  __as__7FVectorFRC7FVector(auStack_90,auStack_a0);
  bVar1 = *(byte *)(sys__6CField + 0x192);
  iVar4 = 0;
  do {
    if ((int)(uint)bVar1 <= iVar4) {
      return 0;
    }
    iVar2 = GetModel__6CFieldFi(sys__6CField,iVar4);
    if ((((iVar2 != 0) && (iVar2 != iStack_20)) &&
        (lVar3 = isDsp__11CFieldModelFv(iVar2), lVar3 != 0)) &&
       ((*(char *)(iVar2 + 0xfc) == -1 && (lVar3 = isHitChk__11CFieldModelFv(iVar2), lVar3 != 0))))
    {
      __mi__7FVectorCFRC7FVector(auStack_b0,iVar2 + 0x10,iStack_20 + 0x10);
      __as__7FVectorFRC7FVector(auStack_40,auStack_b0);
      fStack_24 = (float)Length__7FVectorCFv(auStack_40);
      Normalize__7FVectorFv(auStack_40);
      fStack_28 = (float)InnerProduct__7FVectorCFRC7FVector(auStack_90,auStack_40);
      fStack_24 = fStack_24 - fStack_10 * (fStack_28 + 1.0) * 0.5;
      if (fStack_24 <= 8.0) {
        if (0.4 <= fStack_28) {
          return iVar2;
        }
        if (fStack_24 <= 6.0) {
          return iVar2;
        }
      }
    }
    iVar4 = iVar4 + 1;
  } while( true );
}

/* JP: 0x004c7a30  CFieldModel::HitChkM2E()   [HitChkM2E__11CFieldModelFv]  size=0x30 */
void HitChkM2E__11CFieldModelFv(int param_1)

{
  CheckEventBox__6CFieldFR7FVector(sys__6CField,param_1 + 0x10);
  return;
}

/* JP: 0x004c7a60  CFieldModel::SetMoveMotion(int, int, int)   [SetMoveMotion__11CFieldModelFiii]  size=0xb0 */
void SetMoveMotion__11CFieldModelFiii(int param_1,int param_2,int param_3,int param_4)

{
  if (-1 < param_2) {
    *(int *)(param_1 + 0xa4) = param_2;
  }
  if (-1 < param_3) {
    *(int *)(param_1 + 0xa8) = param_3;
  }
  if (-1 < param_4) {
    *(int *)(param_1 + 0xac) = param_4;
  }
  *(byte *)(param_1 + 0x85) = *(byte *)(param_1 + 0x85) & 0xcf | 0x30;
  *(byte *)(param_1 + 0x81) = *(byte *)(param_1 + 0x81) & 0xdf;
  return;
}

/* JP: 0x004c7b10  CFieldModel::SetLastMotion(const char*)   [SetLastMotion__11CFieldModelFPCc]  size=0x34 */
void SetLastMotion__11CFieldModelFPCc(int param_1,undefined4 param_2)

{
  strcpy(param_1 + 0x2cc,param_2);
  return;
}

/* JP: 0x004c7b50  CFieldModel::PlayMoveMotion(int)   [PlayMoveMotion__11CFieldModelFi]  size=0x1bc */
void PlayMoveMotion__11CFieldModelFi(int param_1,uint param_2)

{
  int iVar1;
  long lVar2;
  
  if (((((ulong)*(byte *)(param_1 + 0x80) & 0xf) >> 2 != 0) && ((int)param_2 < 3)) &&
     ((long)(int)param_2 != ((ulong)*(byte *)(param_1 + 0x85) & 0x3f) >> 4)) {
    if ((long)((ulong)*(byte *)(param_1 + 0x81) << 0x38) < 0) {
      SetMotion__11CFieldModelFPCc(param_1,param_1 + 0x2cc);
    }
    else {
      iVar1 = *(int *)(param_1 + param_2 * 4 + 0xa4);
      if (iVar1 != 0) {
        *(byte *)(param_1 + 0x86) = *(byte *)(param_1 + 0x86) & 0xdf;
        if ((((((ulong)*(byte *)(param_1 + 0x85) & 0x3f) >> 4 == 2) && (param_2 == 1)) &&
            ((lVar2 = isManual__11CFieldModelFv(param_1), lVar2 != 0 &&
             ((lVar2 = GetModel__11CFieldModelFv(param_1), lVar2 != 0 &&
              (lVar2 = getSequenceName__5ModelFQ25Model10MotionKind(lVar2,0), lVar2 != 0)))))) &&
           (lVar2 = strcmp(lVar2,0x5561d8), lVar2 == 0)) {
          return;
        }
        SetMotion__11CFieldModelFi(param_1,iVar1);
      }
    }
    *(byte *)(param_1 + 0x85) = *(byte *)(param_1 + 0x85) & 0xcf | (byte)((param_2 & 3) << 4);
  }
  return;
}

/* JP: 0x004c7d10  CFieldModel::CheckLastCmdComplete()   [CheckLastCmdComplete__11CFieldModelFv]  size=0x12c */
ulong CheckLastCmdComplete__11CFieldModelFv(int param_1)

{
  ulong uVar1;
  
  switch(*(undefined1 *)(param_1 + 0x91)) {
  default:
    uVar1 = 0xffffffffffffffff;
    break;
  case 1:
    uVar1 = (ulong)*(byte *)(param_1 + 0x8a) & 1;
    break;
  case 2:
    uVar1 = ((ulong)*(byte *)(param_1 + 0x8a) & 3) >> 1;
    break;
  case 3:
    uVar1 = ((ulong)*(byte *)(param_1 + 0x8a) & 7) >> 2;
    break;
  case 4:
    uVar1 = ((ulong)*(byte *)(param_1 + 0x8a) & 0xf) >> 3;
    break;
  case 5:
    uVar1 = ((ulong)*(byte *)(param_1 + 0x8a) & 0x1f) >> 4;
    break;
  case 6:
    uVar1 = ((ulong)*(byte *)(param_1 + 0x8a) & 0x3f) >> 5;
    break;
  case 7:
    uVar1 = ((ulong)*(byte *)(param_1 + 0x8a) & 0x7f) >> 6;
    break;
  case 8:
    uVar1 = (ulong)(*(byte *)(param_1 + 0x8a) >> 7);
    break;
  case 9:
    uVar1 = (ulong)*(byte *)(param_1 + 0x8b) & 1;
  }
  return uVar1;
}

/* JP: 0x004c7f10  CFieldModel::SearchFrame(const char*)   [SearchFrame__11CFieldModelFPCc]  size=0x70 */
undefined8 SearchFrame__11CFieldModelFPCc(int param_1,undefined4 param_2)

{
  undefined8 uVar1;
  
  if ((*(int *)(param_1 + 0x70) == 0) || (*(int *)(*(int *)(param_1 + 0x70) + 0x30) == 0)) {
    uVar1 = 0;
  }
  else {
    uVar1 = searchFrame__5FrameFPCc(*(undefined4 *)(*(int *)(param_1 + 0x70) + 0x30),param_2);
  }
  return uVar1;
}

/* JP: 0x004c7f80  CFieldModel::AutoMove(FVector*, int, int, int)   [AutoMove__11CFieldModelFP7FVectoriii]  size=0x314 */
void AutoMove__11CFieldModelFP7FVectoriii
               (int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,uint param_5)

{
  undefined8 uVar1;
  long lVar2;
  undefined1 auStack_80 [16];
  undefined1 auStack_70 [28];
  float fStack_54;
  int iStack_50;
  undefined4 uStack_40;
  undefined4 uStack_30;
  undefined4 uStack_20;
  uint uStack_10;
  
  *(undefined1 *)(param_1 + 0xbd) = 0;
  iStack_50 = param_1;
  uStack_40 = param_2;
  uStack_30 = param_3;
  uStack_20 = param_4;
  uStack_10 = param_5;
  PushChkFlags__11CFieldModelFv(param_1);
  clear__13_AutoMoveInfoFv(param_1 + 400);
  *(byte *)(param_1 + 0x19b) =
       *(byte *)(param_1 + 0x19b) & 0xdf | (byte)(((int)uStack_10 >> 4 & 1U) << 5);
  if ((long)((ulong)*(byte *)(param_1 + 0x19b) << 0x3a) < 0) {
    lVar2 = 1;
    memcpy(param_1 + 0x1b0,iStack_50 + 0x10,0xc);
    memcpy(param_1 + 0x1c0,uStack_40,0xc);
    *(undefined4 *)(param_1 + 0x1cc) = 0;
    *(undefined1 *)(param_1 + 0x19c) = 2;
    *(undefined2 *)(param_1 + 0x198) = 1;
    *(byte *)(param_1 + 0x19b) = *(byte *)(param_1 + 0x19b) & 0xef | 0x10;
    __as__7FVectorFRC7FVector(param_1 + 0x1a0,uStack_40);
    __mi__7FVectorCFRC7FVector(auStack_70,uStack_40,iStack_50 + 0x10);
    fStack_54 = (float)Length__7FVectorCFv(auStack_70);
    if (fStack_54 == 0.0) {
      *(byte *)(param_1 + 0x19a) = *(byte *)(param_1 + 0x19a) & 0xfd | 2;
      lVar2 = 0;
      PopChkFlags__11CFieldModelFv(iStack_50);
    }
  }
  else {
    uVar1 = __ct__7FVectorFRC7FVector(auStack_80,iStack_50 + 0x10);
    lVar2 = MakeMoveNode__11CFieldModelFP7FVector7FVector(iStack_50,uStack_40,uVar1);
  }
  *(char *)(param_1 + 0x19d) = (char)uStack_30;
  *(byte *)(param_1 + 0x19b) = *(byte *)(param_1 + 0x19b) & 0xfc | (char)uStack_20 + 1U & 3;
  *(byte *)(param_1 + 0x19b) = *(byte *)(param_1 + 0x19b) & 0xf3 | (byte)((uStack_10 & 3) << 2);
  *(byte *)(param_1 + 0x19b) =
       *(byte *)(param_1 + 0x19b) & 0xbf | (byte)(((int)uStack_10 >> 5 & 1U) << 6);
  SetFloorChk__11CFieldModelFi(iStack_50,((ulong)*(byte *)(param_1 + 0x19b) & 0xf) >> 2 & 1);
  SetHitCheck__11CFieldModelFi
            (iStack_50,(int)(uint)(((ulong)*(byte *)(param_1 + 0x19b) << 0x3c) >> 0x3e) >> 1);
  if (lVar2 < 1) {
    if (lVar2 == 0) {
      SetDir__11CFieldModelFiii(iStack_50,uStack_30,2,1);
      *(byte *)(iStack_50 + 0x8b) = *(byte *)(iStack_50 + 0x8b) & 0xfe | 1;
    }
  }
  else {
    *(byte *)(iStack_50 + 0x85) = *(byte *)(iStack_50 + 0x85) & 0xf3 | 4;
    UpdateNodeLen__11CFieldModelFv(iStack_50);
  }
  return;
}

/* JP: 0x004c82a0  CFieldModel::PathMove(int, const _PATHLIST*, unsigned int)   [PathMove__11CFieldModelFiPC9_PATHLISTUi]  size=0xcc */
void PathMove__11CFieldModelFiPC9_PATHLISTUi
               (int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  *(undefined1 *)(param_1 + 0xbd) = 0;
  PushChkFlags__11CFieldModelFv(param_1);
  if (param_2 != 0) {
    clear__13_PathMoveInfoFv(param_1 + 400);
    *(short *)(param_1 + 0x19e) = (short)param_2;
    *(undefined4 *)(param_1 + 0x1a0) = param_3;
    UpdateNodeLen__11CFieldModelFv(param_1);
  }
  *(byte *)(param_1 + 0x19a) = *(byte *)(param_1 + 0x19a) & 0xfe;
  *(byte *)(param_1 + 0x85) = *(byte *)(param_1 + 0x85) & 0xf3 | 8;
  *(undefined4 *)(param_1 + 0xd4) = param_4;
  return;
}

/* JP: 0x004c84c0  CFieldModel::MakeMoveNode(FVector*, FVector)   [MakeMoveNode__11CFieldModelFP7FVector7FVector]  size=0x954 */
undefined4 MakeMoveNode__11CFieldModelFP7FVector7FVector(int param_1,int param_2,undefined4 param_3)

{
  int *piVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined8 uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined4 *puVar9;
  int iVar10;
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
  undefined1 auStack_2d0 [4];
  float fStack_2cc;
  undefined1 auStack_2c0 [16];
  int aiStack_2b0 [20];
  undefined4 *apuStack_260 [20];
  undefined4 auStack_210 [4];
  undefined4 auStack_200 [68];
  undefined4 auStack_f0 [16];
  undefined1 auStack_b0 [16];
  undefined1 auStack_a0 [16];
  undefined4 auStack_90 [2];
  undefined4 uStack_88;
  undefined4 uStack_84;
  undefined1 auStack_80 [20];
  undefined4 uStack_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  int iStack_5c;
  int iStack_58;
  int iStack_54;
  float fStack_50;
  float fStack_4c;
  float fStack_48;
  float fStack_44;
  int iStack_40;
  float fStack_3c;
  int iStack_38;
  int iStack_34;
  int iStack_30;
  int iStack_20;
  undefined4 uStack_10;
  
  iStack_30 = param_1;
  iStack_20 = param_2;
  uStack_10 = param_3;
  __ct__7FVectorFv(auStack_80);
  __ct__7FVectorFv(auStack_90);
  iVar2 = iStack_30;
  iVar6 = iStack_30 + 400;
  if ((long)((ulong)*(byte *)(iStack_30 + 0x19a) << 0x3e) < 0) {
    uStack_6c = 0;
  }
  else if ((long)((ulong)*(byte *)(iStack_30 + 0x19b) << 0x3b) < 0) {
    uStack_6c = 1;
  }
  else {
    *(undefined4 *)(iStack_20 + 0xc) = 0x3f800000;
    FixNode__13_AutoMoveInfoFv(iVar6);
    iVar7 = *(byte *)(iVar2 + 0x19c) + 1;
    iStack_38 = iVar6 + (uint)*(byte *)(iVar2 + 0x19c) * 0x10 + 0x20;
    memcpy(iStack_38,uStack_10,0xc);
    *(short *)(iVar2 + 0x198) = *(short *)(iVar2 + 0x198) + 1;
    iStack_34 = 0x10 - iVar7;
    __as__7FVectorFRC7FVector(iVar2 + 0x1a0,iStack_20);
    __mi__7FVectorCFRC7FVector(auStack_a0,iStack_20,uStack_10);
    fStack_3c = (float)Length__7FVectorCFv(auStack_a0);
    if (fStack_3c == 0.0) {
      *(byte *)(iVar2 + 0x19a) = *(byte *)(iVar2 + 0x19a) & 0xfd | 2;
      uStack_6c = 0;
    }
    else {
      __ct__7FVectorFffff(0,0,0x3f800000,0x3f800000,auStack_b0);
      __ct__6MatrixFv(auStack_f0);
      UnitMatrix__6MatrixFv(auStack_f0);
      RotYMatrix__6MatrixFf(*(undefined4 *)(iStack_30 + 0x24),auStack_f0);
      ApplyMatrix__6MatrixCFRC7FVector(auStack_2e0,auStack_f0,auStack_b0);
      __as__7FVectorFRC7FVector(auStack_b0,auStack_2e0);
      puVar3 = auStack_210;
      do {
        __ct__7FVectorFv(puVar3);
        puVar3 = puVar3 + 4;
      } while (puVar3 != auStack_f0);
      iStack_40 = 0;
      uVar5 = __ct__7FVectorFRC7FVector(auStack_2f0,uStack_10);
      puVar3 = (undefined4 *)
               OnFloorChk__9CFloorManF7FVector(*(undefined4 *)(sys__6CField + 0x1b8),uVar5);
      uVar5 = __ct__7FVectorFRC7FVector(auStack_300,iStack_20);
      puVar4 = (undefined4 *)
               OnFloorChk__9CFloorManF7FVector(*(undefined4 *)(sys__6CField + 0x1b8),uVar5);
      __as__7FVectorFRC7FVector(auStack_210,uStack_10);
      apuStack_260[0] = puVar3;
      for (iVar8 = 1; (puVar3 != puVar4 && (iVar8 <= iStack_34)); iVar8 = iVar8 + 1) {
        __mi__7FVectorCFRC7FVector(auStack_310,iStack_20,uStack_10);
        __as__7FVectorFRC7FVector(auStack_80,auStack_310);
        fStack_44 = (float)Length__7FVectorCFv(auStack_80);
        Normalize__7FVectorFv(auStack_80);
        __ct__7FVectorFv(auStack_2c0);
        __as__7FVectorFRC7FVector(auStack_2c0,auStack_80);
        fStack_48 = 1.0;
        __ct__7FVectorFv(auStack_2d0);
        OuterProduct__7FVectorCFRC7FVector(auStack_320,auStack_80,auStack_b0);
        __as__7FVectorFRC7FVector(auStack_2d0,auStack_320);
        if (0.0 <= fStack_2cc) {
          fStack_48 = -1.0;
        }
        iStack_54 = 0;
        fStack_50 = 2.0;
        puVar9 = puVar3;
LAB_004c8858:
        fStack_4c = fStack_50;
        while( true ) {
          if (fStack_44 < fStack_4c) {
            fStack_4c = fStack_44;
          }
          __ml__7FVectorCFf(fStack_4c,auStack_330,auStack_2c0);
          __as__7FVectorFRC7FVector(auStack_90,auStack_330);
          __apl__7FVectorFRC7FVector(auStack_90,uStack_10);
          uVar5 = __ct__7FVectorFRC7FVector(auStack_340,auStack_90);
          puVar3 = (undefined4 *)
                   OnFloorChk__9CFloorManF7FVector(*(undefined4 *)(sys__6CField + 0x1b8),uVar5);
          if (puVar9 != puVar3) goto LAB_004c8920;
          if (fStack_44 <= fStack_4c) break;
          fStack_4c = fStack_4c + fStack_50;
        }
        puVar3 = (undefined4 *)0x0;
LAB_004c8920:
        if ((puVar3 != (undefined4 *)0x0) && (puVar3 != puVar4)) {
          for (iStack_58 = 0; iStack_58 < iVar8; iStack_58 = iStack_58 + 1) {
            if (apuStack_260[iStack_58] == puVar3) {
              puVar3 = (undefined4 *)0x0;
              break;
            }
          }
          if (puVar3 != (undefined4 *)0x0) {
            for (iStack_5c = 0; iStack_5c < iStack_40; iStack_5c = iStack_5c + 1) {
              if ((undefined4 *)aiStack_2b0[iStack_5c] == puVar3) {
                puVar3 = (undefined4 *)0x0;
                break;
              }
            }
          }
        }
        if (puVar3 == (undefined4 *)0x0) {
          UnitMatrix__6MatrixFv(auStack_f0);
          RotYMatrix__6MatrixFf(fStack_48 * 0.1963495,auStack_f0);
          ApplyMatrix__6MatrixCFRC7FVector(auStack_350,auStack_f0,auStack_2c0);
          __as__7FVectorFRC7FVector(auStack_2c0,auStack_350);
          iStack_54 = iStack_54 + 1;
          if (0x1f < iStack_54) {
            __as__7FVectorFRC7FVector(auStack_2c0,auStack_80);
            iStack_54 = 0;
            if (fStack_50 <= 0.5) {
              if (iVar8 < 2) {
                return 0xffffffff;
              }
              piVar1 = aiStack_2b0 + iStack_40;
              iStack_40 = iStack_40 + 1;
              *piVar1 = (int)apuStack_260[iVar8 + -1];
              __as__7FVectorFRC7FVector(uStack_10,auStack_210 + (iVar8 + -2) * 4);
              puVar9 = apuStack_260[iVar8 + -2];
              iVar8 = iVar8 + -1;
            }
            else {
              fStack_50 = 0.5;
            }
          }
          goto LAB_004c8858;
        }
        if (puVar3 == puVar4) {
          __as__7FVectorFRC7FVector(auStack_90,iStack_20);
        }
        else {
          uStack_60 = *puVar3;
          uStack_64 = puVar3[1];
          uStack_68 = puVar3[2];
          __pl__7FVectorCFRC7FVector(auStack_370,uStack_60,uStack_64);
          __pl__7FVectorCFRC7FVector(auStack_360,auStack_370,uStack_68);
          __as__7FVectorFRC7FVector(auStack_90,auStack_360);
          __adv__7FVectorFf(0x40400000,auStack_90);
        }
        uStack_84 = 0x3f800000;
        __as__7FVectorFRC7FVector(uStack_10,auStack_90);
        uStack_84 = 0;
        __as__7FVectorFRC7FVector(auStack_210 + iVar8 * 4,uStack_10);
        apuStack_260[iVar8] = puVar3;
      }
      if (puVar3 == puVar4) {
        if (iVar8 == 1) {
          __as__7FVectorFRC7FVector(auStack_90,iStack_20);
          uStack_84 = 0;
          __as__7FVectorFRC7FVector(auStack_210 + 4,auStack_90);
          iVar8 = 2;
        }
        *(byte *)(iVar2 + 0x19b) = *(byte *)(iVar2 + 0x19b) & 0xef | 0x10;
      }
      for (iVar10 = 1; iVar10 < iVar8 + -1; iVar10 = iVar10 + 1) {
        __pl__7FVectorCFRC7FVector
                  (auStack_390,auStack_210 + (iVar10 + 1) * 4,auStack_210 + iVar10 * 4);
        __ml__7FVectorCFf(0x3e800000,auStack_380,auStack_390);
        __as__7FVectorFRC7FVector(auStack_90,auStack_380);
        __ml__7FVectorCFf(0x3f000000,auStack_3a0,auStack_210 + (iVar10 + -1) * 4);
        __apl__7FVectorFRC7FVector(auStack_90,auStack_3a0);
        uStack_84 = 0x3f800000;
        auStack_210[iVar10 * 4] = auStack_90[0];
        auStack_210[iVar10 * 4 + 2] = uStack_88;
      }
      for (iVar10 = 1; iVar10 < iVar8; iVar10 = iVar10 + 1) {
        memcpy(iVar6 + iVar7 * 0x10 + 0x20,auStack_210 + iVar10 * 4,0xc);
        iVar7 = iVar7 + 1;
      }
      *(char *)(iVar2 + 0x19c) = (char)iVar7;
      if (iVar8 == 0) {
        uStack_6c = 0xffffffff;
      }
      else {
        uStack_6c = 1;
      }
    }
  }
  return uStack_6c;
}

/* JP: 0x004c8e20  CFieldModel::UpdateNodeLen()   [UpdateNodeLen__11CFieldModelFv]  size=0x1a8 */
void UpdateNodeLen__11CFieldModelFv(int param_1)

{
  int iVar1;
  undefined1 auStack_40 [4];
  float fStack_3c;
  undefined4 uStack_34;
  undefined1 auStack_30 [20];
  float fStack_1c;
  float fStack_18;
  int iStack_10;
  
  iStack_10 = param_1;
  __ct__7FVectorFv(auStack_30);
  __ct__7FVectorFv(auStack_40);
  if (((ulong)*(byte *)(iStack_10 + 0x85) & 0xf) >> 2 == 1) {
    iVar1 = iStack_10 + (uint)*(ushort *)(iStack_10 + 0x198) * 0x10 + 0x1b0;
  }
  else {
    iVar1 = *(int *)(iStack_10 + 0x1a0) + (uint)*(ushort *)(iStack_10 + 0x198) * 0x10;
  }
  memcpy(auStack_40,iVar1,0xc);
  uStack_34 = 0x3f800000;
  __ami__7FVectorFRC7FVector(auStack_40,iStack_10 + 0x10);
  fStack_18 = fStack_3c;
  fStack_3c = 0.0;
  fStack_1c = (float)Length__7FVectorCFv(auStack_40);
  if (fStack_18 < 0.0) {
    fStack_18 = -fStack_18;
  }
  *(byte *)(iStack_10 + 0x19a) = *(byte *)(iStack_10 + 0x19a) & 0xfb | (fStack_1c < fStack_18) << 2;
  if (fStack_1c < fStack_18) {
    fStack_1c = fStack_18;
  }
  *(float *)(iStack_10 + 400) = fStack_1c;
  *(undefined4 *)(iStack_10 + 0x194) = 0;
  return;
}

/* JP: 0x004c8fd0  CFieldModel::PauseAutoMove(int)   [PauseAutoMove__11CFieldModelFi]  size=0x134 */
void PauseAutoMove__11CFieldModelFi(int param_1,uint param_2)

{
  undefined4 uVar1;
  long lVar2;
  byte bVar3;
  
  *(byte *)(param_1 + 0x85) = *(byte *)(param_1 + 0x85) & 0xbf | (byte)((param_2 & 1) << 6);
  if (((ulong)*(byte *)(param_1 + 0x85) & 0xf) >> 2 != 0) {
    if (param_2 == 0) {
      uVar1 = GetTimer__7SysToolFv();
      *(undefined4 *)(param_1 + 0xcc) = uVar1;
      *(undefined4 *)(param_1 + 0xd0) = 0x32;
      lVar2 = HitChkM2M__11CFieldModelFf(0,param_1);
      if (lVar2 == 0) {
        bVar3 = 3;
      }
      else {
        bVar3 = 4;
      }
      *(byte *)(param_1 + 0x86) = *(byte *)(param_1 + 0x86) & 0xf8 | bVar3;
    }
    else {
      *(byte *)(param_1 + 0x85) = *(byte *)(param_1 + 0x85) & 0xcf | 0x30;
      *(byte *)(param_1 + 0x19a) = *(byte *)(param_1 + 0x19a) & 0xfe;
      PlayMoveMotion__11CFieldModelFi(param_1,0);
    }
  }
  return;
}

/* JP: 0x004c9110  CFieldModel::ArriveDistination(int)   [ArriveDistination__11CFieldModelFi]  size=0x140 */
void ArriveDistination__11CFieldModelFi(int param_1,uint param_2)

{
  undefined4 uVar1;
  
  *(byte *)(param_1 + 0x19a) = *(byte *)(param_1 + 0x19a) & 0xfd | 2;
  *(byte *)(param_1 + 0x85) = *(byte *)(param_1 + 0x85) & 0xf3;
  *(byte *)(param_1 + 0x8b) = *(byte *)(param_1 + 0x8b) & 0xfe | 1;
  PlayMoveMotion__11CFieldModelFi(param_1,0);
  if (-1 < (int)param_2) {
    if ((param_2 & 0x40) == 0) {
      uVar1 = 3;
    }
    else {
      uVar1 = 2;
    }
    SetDir__11CFieldModelFiii(param_1,param_2 & 0x3f,uVar1,1);
    if (*(float *)(param_1 + 0x24) != *(float *)(param_1 + 0x34)) {
      SetCmd__11CFieldModelFi(param_1,8);
    }
  }
  PopChkFlags__11CFieldModelFv(param_1);
  return;
}

/* JP: 0x004c9250  CFieldModel::UpdateAutoMove(float)   [UpdateAutoMove__11CFieldModelFf]  size=0x7f4 */
undefined4 UpdateAutoMove__11CFieldModelFf(int param_1)

{
  ushort uVar1;
  long lVar2;
  undefined8 uVar3;
  float *pfVar4;
  float *pfVar5;
  uint uVar6;
  int iVar7;
  undefined4 uVar8;
  float fVar9;
  undefined1 auStack_140 [16];
  undefined1 auStack_130 [16];
  undefined1 auStack_120 [16];
  undefined1 auStack_110 [16];
  undefined1 auStack_100 [16];
  undefined1 auStack_f0 [16];
  undefined1 auStack_e0 [16];
  undefined1 auStack_d0 [64];
  undefined1 auStack_90 [16];
  undefined1 auStack_80 [4];
  undefined4 uStack_7c;
  undefined4 uStack_70;
  float fStack_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined1 auStack_60 [16];
  undefined1 auStack_50 [4];
  undefined4 uStack_4c;
  undefined4 uStack_44;
  undefined1 auStack_40 [4];
  undefined4 uStack_3c;
  float fStack_30;
  float fStack_2c;
  float fStack_28;
  float fStack_24;
  int iStack_20;
  
  pfVar4 = (float *)(param_1 + 400);
  uVar1 = *(ushort *)(param_1 + 0x198);
  uVar6 = (uint)uVar1;
  pfVar5 = pfVar4 + uVar6 * 4 + 8;
  iStack_20 = param_1;
  __ct__7FVectorFv(auStack_40);
  __ct__7FVectorFv(auStack_50);
  __ct__7FVectorFv(auStack_60);
  __ct__7FVectorFffff(0,0,0xbf800000,0x3f800000,&uStack_70);
  lVar2 = isCollided__11CFieldModelFv(iStack_20);
  if ((lVar2 == 0) || ((long)((ulong)*(byte *)(iStack_20 + 0x88) << 0x38) < 0)) {
    memcpy(auStack_50,pfVar5,0xc);
    uStack_44 = 0x3f800000;
    __mi__7FVectorCFRC7FVector(auStack_e0,auStack_50,iStack_20 + 0x10);
    __as__7FVectorFRC7FVector(auStack_40,auStack_e0);
    if (-1 < (long)((ulong)*(byte *)(param_1 + 0x19a) << 0x3d)) {
      uStack_3c = 0;
    }
    Normalize__7FVectorFv(auStack_40);
    if (uVar6 + 1 == (uint)*(byte *)(param_1 + 0x19c)) {
      __ct__7FVectorFv(auStack_80);
      memcpy(auStack_80,pfVar5,0xc);
      __mi__7FVectorCFRC7FVector(auStack_f0,iStack_20 + 0x10,auStack_80);
      __as__7FVectorFRC7FVector(auStack_80,auStack_f0);
      if (-1 < (long)((ulong)*(byte *)(param_1 + 0x19a) << 0x3d)) {
        uStack_7c = 0;
      }
      fStack_28 = (float)Length__7FVectorCFv(auStack_80);
      if (*(float *)(param_1 + 0x194) < *pfVar4) {
        *(float *)(param_1 + 0x194) = *pfVar4 - fStack_28;
      }
    }
    if ((*(byte *)(param_1 + 0x19b) & 3) == 2) {
      iVar7 = 2;
    }
    else {
      iVar7 = 1;
    }
    if (-1 < (long)((ulong)*(byte *)(param_1 + 0x19a) << 0x3d)) {
      fStack_24 = *(float *)(param_1 + 0x194) / *pfVar4;
      fStack_2c = pfVar4[uVar6 * 4 + 5];
      *(float *)(iStack_20 + 0x14) = fStack_2c + fStack_24 * (pfVar4[uVar6 * 4 + 9] - fStack_2c);
      if ((0.5 < fStack_24) &&
         ((int)(uint)*(ushort *)(param_1 + 0x198) < (int)(*(byte *)(param_1 + 0x19c) - 1))) {
        if (1.0 < fStack_24) {
          fStack_24 = 1.0;
        }
        fStack_24 = (fStack_24 - 0.5) / 0.5;
        __amu__7FVectorFf(1.0 - fStack_24,auStack_40);
        memcpy(auStack_50,pfVar4 + uVar6 * 4 + 0xc,0xc);
        __ami__7FVectorFRC7FVector(auStack_50,iStack_20 + 0x10);
        uStack_4c = 0;
        Normalize__7FVectorFv(auStack_50);
        __ml__7FVectorCFf(fStack_24,auStack_100,auStack_50);
        __apl__7FVectorFRC7FVector(auStack_40,auStack_100);
      }
      uVar8 = InnerProduct__7FVectorCFRC7FVector(&uStack_70,auStack_40);
      fStack_30 = (float)acosf(uVar8);
      fStack_24 = fStack_30;
      if (fStack_30 == NAN) {
        fStack_24 = 0.0;
      }
      OuterProduct__7FVectorCFRC7FVector(auStack_110,&uStack_70,auStack_40);
      __as__7FVectorFRC7FVector(&uStack_70,auStack_110);
      if (fStack_6c < 0.0) {
        fStack_24 = -fStack_24;
      }
      uStack_68 = 0;
      uStack_70 = 0;
      uStack_64 = 0x3f800000;
      fStack_6c = fStack_24;
      if ((*(byte *)(param_1 + 0x19b) & 3) == 0) {
        __mi__7FVectorCFRC7FVector(auStack_90,iStack_20 + 0x10,param_1 + 0x1a0);
        fVar9 = (float)Length__7FVectorCFv(auStack_90);
        if (20.0 < fVar9) {
          iVar7 = 2;
        }
      }
      if (-1 < (long)((ulong)*(byte *)(param_1 + 0x19b) << 0x39)) {
        if (iVar7 == 2) {
          uVar8 = 2;
        }
        else if ((*(byte *)(param_1 + 0x19a) & 1) == 0) {
          uVar8 = 3;
        }
        else {
          uVar8 = 1;
        }
        SetDir__11CFieldModelFR7FVectorii(iStack_20,&uStack_70,2,uVar8);
        fStack_6c = 0.0;
        uStack_70 = 0;
        uStack_68 = 0xbf800000;
        uStack_64 = 0x3f800000;
        __ct__6MatrixFv(auStack_d0);
        UnitMatrix__6MatrixFv(auStack_d0);
        RotYMatrix__6MatrixFf(*(undefined4 *)(iStack_20 + 0x24),auStack_d0);
        ApplyMatrix__6MatrixCFRC7FVector(auStack_120,auStack_d0,&uStack_70);
        __as__7FVectorFRC7FVector(&uStack_70,auStack_120);
        fStack_24 = (float)InnerProduct__7FVectorCFRC7FVector(&uStack_70,auStack_40);
        if ((fStack_24 < 0.6) && ((*(byte *)(param_1 + 0x19a) & 1) == 0)) {
          PlayMoveMotion__11CFieldModelFi(iStack_20,0);
          return 0;
        }
      }
    }
    if ((int)(*pfVar4 * 100.0) <= (int)(*(float *)(param_1 + 0x194) * 100.0)) {
      uVar6 = uVar1 + 1;
      if (*(byte *)(param_1 + 0x19c) <= uVar6) {
        *(ushort *)(param_1 + 0x198) = (ushort)*(byte *)(param_1 + 0x19c);
        memcpy(iStack_20 + 0x10,pfVar5,0xc);
        uVar3 = __ct__7FVectorFRC7FVector(auStack_130,iStack_20 + 0x10);
        SetPos__11CFieldModelF7FVectorb(iStack_20,uVar3,1);
        *(byte *)(iStack_20 + 0x88) =
             *(byte *)(iStack_20 + 0x88) & 0xf9 |
             (byte)(((uint)(((ulong)*(byte *)(iStack_20 + 0x88) << 0x3d) >> 0x3e) | 2) << 1);
        ArriveDistination__11CFieldModelFi(iStack_20,*(undefined1 *)(param_1 + 0x19d));
        return 1;
      }
      if (((long)((ulong)*(byte *)(param_1 + 0x19b) << 0x3b) < 0) || (uVar6 < 0xe)) {
        *(ushort *)(param_1 + 0x198) = (ushort)uVar6 & 0xff;
      }
      else {
        *(undefined1 *)(param_1 + 0x19c) = 0;
        *(undefined2 *)(param_1 + 0x198) = 0;
        uVar3 = __ct__7FVectorFRC7FVector(auStack_140,iStack_20 + 0x10);
        MakeMoveNode__11CFieldModelFP7FVector7FVector(iStack_20,param_1 + 0x1a0,uVar3);
      }
      UpdateNodeLen__11CFieldModelFv(iStack_20);
    }
    PlayMoveMotion__11CFieldModelFi(iStack_20,iVar7);
    *(byte *)(param_1 + 0x19a) = *(byte *)(param_1 + 0x19a) & 0xfe | 1;
  }
  else {
    PlayMoveMotion__11CFieldModelFi(iStack_20,0);
    *(byte *)(iStack_20 + 0x86) = *(byte *)(iStack_20 + 0x86) & 0xf8 | 4;
  }
  return 0;
}

/* JP: 0x004c9a50  CFieldModel::isCollided()   [isCollided__11CFieldModelFv]  size=0x24 */
ulong isCollided__11CFieldModelFv(int param_1)

{
  return ((ulong)*(byte *)(param_1 + 0x82) & 0xf) >> 3;
}

/* JP: 0x004c9a80  CFieldModel::UpdatePathMove(float)   [UpdatePathMove__11CFieldModelFf]  size=0x864 */
/* WARNING: Removing unreachable block (ram,0x004c9f94) */
/* WARNING: Removing unreachable block (ram,0x004c9fb0) */
/* WARNING: Removing unreachable block (ram,0x004ca030) */
/* WARNING: Removing unreachable block (ram,0x004ca028) */
/* WARNING: Removing unreachable block (ram,0x004ca048) */
/* WARNING: Removing unreachable block (ram,0x004ca070) */

undefined4 UpdatePathMove__11CFieldModelFf(int param_1)

{
  ushort uVar1;
  bool bVar2;
  long lVar3;
  float *pfVar4;
  uint uVar5;
  undefined8 uVar6;
  int iVar7;
  float fVar8;
  undefined4 uVar9;
  undefined1 auStack_100 [32];
  undefined1 auStack_e0 [16];
  undefined1 auStack_d0 [16];
  undefined1 auStack_c0 [80];
  undefined1 auStack_70 [4];
  undefined4 uStack_6c;
  undefined4 uStack_60;
  float fStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined1 auStack_50 [16];
  float afStack_40 [2];
  float fStack_38;
  undefined4 uStack_34;
  float fStack_28;
  float fStack_24;
  int iStack_20;
  
  pfVar4 = (float *)(param_1 + 400);
  uVar1 = *(ushort *)(param_1 + 0x198);
  iVar7 = *(int *)(param_1 + 0x1a0) + (uint)uVar1 * 0x10;
  iStack_20 = param_1;
  __ct__7FVectorFv(afStack_40);
  __ct__7FVectorFv(auStack_50);
  __ct__7FVectorFv(&uStack_60);
  lVar3 = isCollided__11CFieldModelFv(iStack_20);
  if ((lVar3 == 0) || ((long)((ulong)*(byte *)(iStack_20 + 0x88) << 0x38) < 0)) {
    memcpy(afStack_40,iVar7,0xc);
    __ami__7FVectorFRC7FVector(afStack_40,iStack_20 + 0x10);
    Normalize__7FVectorFv(afStack_40);
    SetFloorChk__11CFieldModelFi(iStack_20,*(byte *)(iVar7 + 0xe) >> 6 & 1);
    SetHitCheck__11CFieldModelFi(iStack_20,1);
    fStack_28 = 10.0;
    uVar5 = *(byte *)(iVar7 + 0xe) & 0x3f;
    if (1 < uVar5) {
      fStack_28 = (float)(int)(uVar5 - 2) * 2.0 + 4.0;
    }
    fStack_24 = 0.0;
    if (uVar5 != 1) {
      if (*pfVar4 < fStack_28) {
        fStack_24 = *(float *)(param_1 + 0x194) / *pfVar4;
      }
      else {
        fVar8 = *pfVar4 - *(float *)(param_1 + 0x194);
        if (fVar8 < fStack_28) {
          fStack_24 = 1.0 - fVar8 / fStack_28;
        }
        else {
          fStack_24 = 0.0;
        }
      }
    }
    if ((0.0 < fStack_24) && ((int)(uint)uVar1 < (int)(*(ushort *)(param_1 + 0x19e) - 1))) {
      if (1.0 < fStack_24) {
        fStack_24 = 1.0;
      }
      fStack_24 = (float)sinf(fStack_24 * 1.570796);
      fStack_24 = fStack_24 * 0.9;
      __amu__7FVectorFf(1.0 - fStack_24,afStack_40);
      memcpy(auStack_50,iVar7 + 0x10,0xc);
      __ami__7FVectorFRC7FVector(auStack_50,iStack_20 + 0x10);
      Normalize__7FVectorFv(auStack_50);
      __ml__7FVectorCFf(fStack_24,auStack_d0,auStack_50);
      __apl__7FVectorFRC7FVector(afStack_40,auStack_d0);
      Normalize__7FVectorFv(afStack_40);
      uStack_34 = 0x3f800000;
    }
    bVar2 = false;
    if ((afStack_40[0] != 0.0) || (fStack_38 != 0.0)) {
      bVar2 = true;
    }
    fStack_5c = 0.0;
    uStack_60 = 0;
    uStack_58 = 0xbf800000;
    __ct__7FVectorFRC7FVector(auStack_70,afStack_40);
    uStack_6c = 0;
    Normalize__7FVectorFv(auStack_70);
    uVar9 = InnerProduct__7FVectorCFRC7FVector(&uStack_60,auStack_70);
    fStack_24 = (float)acosf(uVar9);
    OuterProduct__7FVectorCFRC7FVector(auStack_e0,&uStack_60,auStack_70);
    __as__7FVectorFRC7FVector(&uStack_60,auStack_e0);
    if (fStack_5c < 0.0) {
      fStack_24 = -fStack_24;
    }
    if (*(float *)(iStack_20 + 0xb8) == 0.0) {
      if (*(char *)(iStack_20 + 0xbc) != '\0') {
        *(char *)(iStack_20 + 0xbc) = *(char *)(iStack_20 + 0xbc) + -1;
        bVar2 = false;
        fStack_24 = *(float *)(iStack_20 + 0x24);
      }
    }
    else {
      fStack_24 = *(float *)(iStack_20 + 0x24) + *(float *)(iStack_20 + 0xb8);
      *(undefined4 *)(iStack_20 + 0xb8) = 0;
      *(undefined1 *)(iStack_20 + 0xbc) = 0x14;
      bVar2 = false;
    }
    uStack_58 = 0;
    uStack_60 = 0;
    uStack_54 = 0x3f800000;
    fStack_5c = fStack_24;
    uVar6 = 1;
    if (-1 < (long)((ulong)*(byte *)(param_1 + 0x19a) << 0x3d)) {
      if ((*(byte *)(param_1 + 0x19a) & 1) == 0) {
        uVar9 = 3;
      }
      else {
        uVar9 = 1;
      }
      SetDir__11CFieldModelFR7FVectorii(iStack_20,&uStack_60,2,uVar9);
    }
    fStack_5c = 0.0;
    uStack_60 = 0;
    uStack_58 = 0xbf800000;
    __ct__6MatrixFv(auStack_c0);
    UnitMatrix__6MatrixFv(auStack_c0);
    RotYMatrix__6MatrixFf(*(undefined4 *)(iStack_20 + 0x24),auStack_c0);
    ApplyMatrix__6MatrixCFRC7FVector(auStack_100,auStack_c0,&uStack_60);
    __as__7FVectorFRC7FVector(&uStack_60,auStack_100);
    fStack_24 = (float)InnerProduct__7FVectorCFRC7FVector(&uStack_60,afStack_40);
    if ((((long)((ulong)*(byte *)(param_1 + 0x19a) << 0x3d) < 0) || (!bVar2)) || (0.6 <= fStack_24))
    {
      *(byte *)(param_1 + 0x19a) = *(byte *)(param_1 + 0x19a) & 0xfe | 1;
    }
    else {
      if ((*(byte *)(param_1 + 0x19a) & 1) == 0) {
        return 0;
      }
      *(byte *)(param_1 + 0x19a) = *(byte *)(param_1 + 0x19a) & 0xfe;
      uVar6 = 0;
    }
    if (*pfVar4 <= *(float *)(param_1 + 0x194)) {
      if (*(int *)(iStack_20 + 0xd4) != 0) {
        CharPathEvent__6CFieldFP11CFieldModelUii
                  (sys__6CField,iStack_20,*(undefined4 *)(iStack_20 + 0xd4),(uint)uVar1);
      }
      uVar5 = uVar1 + 1;
      if (*(ushort *)(param_1 + 0x19e) <= uVar5) {
        *(undefined2 *)(param_1 + 0x198) = *(undefined2 *)(param_1 + 0x19e);
        ArriveDistination__11CFieldModelFi(iStack_20,*(undefined1 *)(iVar7 + 0xc));
        return 1;
      }
      *(short *)(param_1 + 0x198) = (short)uVar5;
      UpdateNodeLen__11CFieldModelFv(iStack_20);
    }
    PlayMoveMotion__11CFieldModelFi(iStack_20,uVar6);
  }
  else {
    PlayMoveMotion__11CFieldModelFi(iStack_20,0);
    *(byte *)(iStack_20 + 0x86) = *(byte *)(iStack_20 + 0x86) & 0xf8 | 4;
  }
  return 0;
}

/* JP: 0x004ca2f0  CFieldModel::PushChkFlags()   [PushChkFlags__11CFieldModelFv]  size=0x48 */
void PushChkFlags__11CFieldModelFv(int param_1)

{
  *(byte *)(param_1 + 0xff) =
       (char)((uint)(((ulong)*(byte *)(param_1 + 0x88) << 0x3c) >> 0x3f) << 1) +
       (byte)(((ulong)*(byte *)(param_1 + 0x88) << 0x3a) >> 0x3e);
  return;
}

/* JP: 0x004ca340  CFieldModel::PopChkFlags()   [PopChkFlags__11CFieldModelFv]  size=0x80 */
void PopChkFlags__11CFieldModelFv(int param_1)

{
  *(byte *)(param_1 + 0x88) =
       *(byte *)(param_1 + 0x88) & 0xcf | (*(byte *)(param_1 + 0xff) & 1) << 4;
  *(byte *)(param_1 + 0x88) =
       *(byte *)(param_1 + 0x88) & 0xf7 |
       (byte)(((int)(uint)*(byte *)(param_1 + 0xff) >> 1 & 1U) << 3);
  return;
}

/* JP: 0x004ca3c0  CFieldModel::FloorChk()   [FloorChk__11CFieldModelFv]  size=0x128 */
void FloorChk__11CFieldModelFv(int param_1)

{
  undefined8 uVar1;
  long lVar2;
  undefined4 uVar3;
  undefined1 auStack_70 [16];
  undefined1 auStack_60 [16];
  undefined1 auStack_50 [64];
  int iStack_10;
  
  iStack_10 = param_1;
  uVar1 = __ct__7FVectorFRC7FVector(auStack_60,param_1 + 0x10);
  lVar2 = OnFloorChk__9CFloorManF7FVector(*(undefined4 *)(sys__6CField + 0x1b8),uVar1);
  if (lVar2 != 0) {
    uVar1 = __ct__7FVectorFRC7FVector(auStack_70,iStack_10 + 0x10);
    uVar3 = OnFloorPoint__9CFloorManF7FVectorPQ23SDB12tagFTRIANGLE
                      (*(undefined4 *)(sys__6CField + 0x1b8),uVar1,lVar2);
    *(undefined4 *)(iStack_10 + 0x14) = uVar3;
    __ct__6MatrixFv(auStack_50);
    UnitMatrix__6MatrixFv(auStack_50);
    RotXMatrix__6MatrixFf(*(undefined4 *)(iStack_10 + 0x20),auStack_50);
    RotYMatrix__6MatrixFf(*(undefined4 *)(iStack_10 + 0x24),auStack_50);
    RotZMatrix__6MatrixFf(*(undefined4 *)(iStack_10 + 0x28),auStack_50);
    TransMatrix__6MatrixFRC7FVector(auStack_50,iStack_10 + 0x10);
    uVar1 = GetFrame__11CFieldModelFv(iStack_10);
    __as__6MatrixFRC6Matrix((int)uVar1 + 0x160,auStack_50);
    myMatrixUpdate__5FrameFv(uVar1);
  }
  return;
}

/* JP: 0x004ca7e0  CFieldModel::AutoAvoid()   [AutoAvoid__11CFieldModelFv]  size=0x400 */
undefined4 AutoAvoid__11CFieldModelFv(int param_1)

{
  byte bVar1;
  int iVar2;
  long lVar3;
  int iVar4;
  undefined1 auStack_f0 [16];
  undefined1 auStack_e0 [16];
  undefined1 auStack_d0 [16];
  undefined1 auStack_c0 [16];
  undefined1 auStack_b0 [16];
  undefined1 auStack_a0 [16];
  undefined1 auStack_90 [16];
  undefined1 auStack_80 [16];
  undefined1 auStack_70 [64];
  undefined1 auStack_30 [4];
  float fStack_2c;
  float fStack_20;
  float fStack_1c;
  float fStack_18;
  float fStack_14;
  int iStack_10;
  
  iStack_10 = param_1;
  __ct__7FVectorFv(auStack_30);
  __ct__6MatrixFv(auStack_70);
  __ct__7FVectorFffff(0,0,0xbf800000,0x3f800000,auStack_80);
  UnitMatrix__6MatrixFv(auStack_70);
  RotYMatrix__6MatrixFf(*(undefined4 *)(iStack_10 + 0x24),auStack_70);
  ApplyMatrix__6MatrixCFRC7FVector(auStack_a0,auStack_70,auStack_80);
  __as__7FVectorFRC7FVector(auStack_80,auStack_a0);
  fStack_18 = 0.0;
  bVar1 = *(byte *)(sys__6CField + 0x192);
  iVar4 = 0;
  do {
    if ((int)(uint)bVar1 <= iVar4) {
      return 0;
    }
    iVar2 = GetModel__6CFieldFi(sys__6CField,iVar4);
    if ((((iVar2 != 0) && (iVar2 != iStack_10)) &&
        (lVar3 = isDsp__11CFieldModelFv(iVar2), lVar3 != 0)) &&
       ((*(char *)(iVar2 + 0xfc) == -1 && (lVar3 = isHitChk__11CFieldModelFv(iVar2), lVar3 != 0))))
    {
      __mi__7FVectorCFRC7FVector(auStack_b0,iVar2 + 0x10,iStack_10 + 0x10);
      __as__7FVectorFRC7FVector(auStack_30,auStack_b0);
      fStack_14 = (float)Length__7FVectorCFv(auStack_30);
      if (fStack_14 <= 20.0) {
        Normalize__7FVectorFv(auStack_30);
        fStack_1c = (float)InnerProduct__7FVectorCFRC7FVector(auStack_80,auStack_30);
        if (0.3 <= fStack_1c) {
          if (((((ulong)*(byte *)(iVar2 + 0x85) & 0xf) >> 2 != 0) &&
              ((*(byte *)(iVar2 + 0x86) & 7) == 0)) && (lVar3 = GetRand__Fi(10), lVar3 < 5)) {
            fStack_14 = 0.0;
          }
          if (fStack_14 <= 8.0) {
            *(byte *)(iStack_10 + 0x86) = *(byte *)(iStack_10 + 0x86) & 0xf8 | 2;
            return 0xffffffff;
          }
          __ct__7FVectorFv(auStack_90);
          __ml__7FVectorCFf(fStack_14 * 0.5,auStack_d0,auStack_30);
          __pl__7FVectorCFRC7FVector(auStack_c0,iStack_10 + 0x10,auStack_d0);
          __as__7FVectorFRC7FVector(auStack_90,auStack_c0);
          __mi__7FVectorCFRC7FVector(auStack_e0,iVar2 + 0x10,auStack_90);
          __as__7FVectorFRC7FVector(auStack_30,auStack_e0);
          Normalize__7FVectorFv(auStack_30);
          fStack_20 = (float)InnerProduct__7FVectorCFRC7FVector(auStack_80,auStack_30);
          if (0.5 <= fStack_20) {
            fStack_20 = (float)acosf(fStack_1c);
            fStack_20 = fStack_20 * 0.1;
            fStack_1c = fStack_1c * (21.0 - fStack_14);
            if (fStack_1c <= fStack_18) {
              return 0;
            }
            fStack_18 = fStack_1c;
            OuterProduct__7FVectorCFRC7FVector(auStack_f0,auStack_80,auStack_30);
            __as__7FVectorFRC7FVector(auStack_30,auStack_f0);
            if (0.0 <= fStack_2c) {
              fStack_20 = -fStack_20;
            }
            *(float *)(iStack_10 + 0xb8) = fStack_20;
            return 1;
          }
        }
      }
    }
    iVar4 = iVar4 + 1;
  } while( true );
}

/* JP: 0x004cabe0  CFieldModel::GetBaseModel()   [GetBaseModel__11CFieldModelFv]  size=0x1c */
undefined4 GetBaseModel__11CFieldModelFv(int param_1)

{
  return *(undefined4 *)(param_1 + 0x70);
}

/* JP: 0x004cac00  CFieldModel::CreateModel()   [CreateModel__11CFieldModelFv]  size=0xf0 */
undefined4 CreateModel__11CFieldModelFv(int param_1)

{
  long lVar1;
  undefined8 uVar2;
  
  if ((*(byte *)(param_1 + 0x82) & 1) == 0) {
    lVar1 = __nw__FUi(0x4c0);
    uVar2 = 0;
    if (lVar1 != 0) {
      uVar2 = __ct__7CFModelFv(lVar1);
    }
    SetOwner__7CFModelFP11CFieldModel(uVar2,param_1);
    *(int *)(param_1 + 0x70) = (int)uVar2;
  }
  else {
    lVar1 = __nw__FUi(0x520);
    uVar2 = 0;
    if (lVar1 != 0) {
      uVar2 = __ct__8CXFModelFv(lVar1);
    }
    SetOwner__8CXFModelFP11CFieldModel(uVar2,param_1);
    *(int *)(param_1 + 0x70) = (int)uVar2;
  }
  return *(undefined4 *)(param_1 + 0x70);
}

/* JP: 0x004cad50  CFieldModel::GetFrame()   [GetFrame__11CFieldModelFv]  size=0x4c */
undefined4 GetFrame__11CFieldModelFv(int param_1)

{
  undefined4 uVar1;
  
  if (*(int *)(param_1 + 0x70) == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = *(undefined4 *)(*(int *)(param_1 + 0x70) + 0x30);
  }
  return uVar1;
}

/* JP: 0x004cada0  CFieldModel::AddTime(float)   [AddTime__11CFieldModelFf]  size=0x88 */
void AddTime__11CFieldModelFf(undefined4 param_1,int param_2)

{
  int iVar1;
  
  iVar1 = GetModel__11CFieldModelFv(param_2);
  (**(code **)(*(int *)(iVar1 + 0x10) + 0x2c))(param_1);
  if ((((ulong)*(byte *)(param_2 + 0x82) & 0x7f) >> 5 != 0) && (*(int *)(param_2 + 0x144) != 0)) {
    (**(code **)(*(int *)(*(int *)(param_2 + 0x144) + 0x7e4) + 0x1c))(param_1);
  }
  return;
}

/* JP: 0x004cae30  CFieldModel::CalcMatrix()   [CalcMatrix__11CFieldModelFv]  size=0x88 */
void CalcMatrix__11CFieldModelFv(int param_1)

{
  undefined8 uVar1;
  
  uVar1 = GetModel__11CFieldModelFv(param_1);
  (**(code **)(*(int *)((int)uVar1 + 0x10) + 0x28))(uVar1,0);
  if ((*(int *)(param_1 + 0x124) != 0) && (-1 < (long)((ulong)*(byte *)(param_1 + 0x8c) << 0x3c))) {
    (**(code **)(*(int *)(*(int *)(param_1 + 0x124) + 0x10) + 0x28))(*(int *)(param_1 + 0x124),0);
  }
  return;
}

/* JP: 0x004caec0  CFieldModel::EventCallBack(const char*, const char*, int, int, unsigned int)   [EventCallBack__11CFieldModelFPCcPCciiUi]  size=0x1b4 */
void EventCallBack__11CFieldModelFPCcPCciiUi
               (int param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  long lVar1;
  undefined8 uVar2;
  undefined4 uVar3;
  undefined1 auStack_70 [12];
  float fStack_64;
  int iStack_60;
  undefined4 uStack_50;
  undefined4 uStack_40;
  int iStack_30;
  
  iStack_60 = param_1;
  uStack_50 = param_2;
  uStack_40 = param_3;
  iStack_30 = param_4;
  lVar1 = checkKind__FPCc(param_3);
  if (lVar1 == 5) {
    uVar2 = GetModel__11CFieldModelFv(iStack_60);
    getModelColor__5ModelFv(auStack_70,uVar2);
    fStack_64 = (float)iStack_30;
    setModelColor__5ModelFR7FVector(uVar2,auStack_70);
    if (*(int *)(iStack_60 + 0x140) != 0) {
      changeAlpha__15ModelEffManagerFP5Modelf((float)iStack_30,uVar2);
    }
    if (*(int *)(iStack_60 + 0x124) != 0) {
      setModelColor__5ModelFR7FVector(*(undefined4 *)(iStack_60 + 0x124),auStack_70);
    }
  }
  else if (lVar1 == 3) {
    lVar1 = strcmp(uStack_50,0x555e80);
    CallSe__6CFieldFiiUi(sys__6CField,lVar1 == 0,1,iStack_60);
    if (lVar1 != 0) {
      uVar3 = 2;
    }
    else {
      uVar3 = 3;
    }
    CallSe__6CFieldFiiUi(sys__6CField,uVar3,1,iStack_60);
  }
  return;
}

/* JP: 0x004cb080  CFieldModel::MotionEndCallBack(const char*)   [MotionEndCallBack__11CFieldModelFPCc]  size=0x390 */
void MotionEndCallBack__11CFieldModelFPCc(int param_1,undefined4 param_2)

{
  uint uVar1;
  long lVar2;
  uint uVar3;
  
  lVar2 = strcmp(param_2,param_1 + 700);
  if (lVar2 == 0) {
    *(byte *)(param_1 + 0x81) = *(byte *)(param_1 + 0x81) & 0xbf | 0x40;
    lVar2 = FindMotionData__11CFieldModelFPCc(param_1,param_2);
    if ((lVar2 == 0) || ((*(byte *)((int)lVar2 + 0x14) & 1) == 0)) {
      if ((long)((ulong)*(byte *)(param_1 + 0x84) << 0x39) < 0) {
        *(undefined1 *)(param_1 + 700) = 0;
        SetMotion__11CFieldModelFi(param_1,*(undefined4 *)(param_1 + 0xa0));
        *(byte *)(param_1 + 0x81) = *(byte *)(param_1 + 0x81) & 0xbf;
      }
      else if (*(char *)(param_1 + 0xf0) == '\0') {
        *(byte *)(param_1 + 0x8a) = *(byte *)(param_1 + 0x8a) & 0xbf | 0x40;
        *(byte *)(param_1 + 0x80) = *(byte *)(param_1 + 0x80) & 0xdf;
        if (((*(byte *)(param_1 + 0x85) & 3) == 3) &&
           (((ulong)*(byte *)(param_1 + 0x86) & 0x1f) >> 3 == 2)) {
          *(byte *)(param_1 + 0x85) = *(byte *)(param_1 + 0x85) & 0xfc;
          *(byte *)(param_1 + 0x86) = *(byte *)(param_1 + 0x86) & 0xe7;
          *(byte *)(param_1 + 0x8a) = *(byte *)(param_1 + 0x8a) & 0x7f | 0x80;
        }
        if ((*(short *)(param_1 + 0x98) == 0) &&
           (-1 < (long)((ulong)*(byte *)(param_1 + 0x81) << 0x38))) {
          *(byte *)(param_1 + 0x85) = *(byte *)(param_1 + 0x85) & 0xcf | 0x30;
          PlayMoveMotion__11CFieldModelFi(param_1,0);
        }
      }
      else {
        uVar1 = (uint)*(byte *)(param_1 + 0xe8);
        if (0xef < uVar1) {
          uVar3 = *(byte *)(param_1 + 0xe8) & 0xf;
          uVar1 = *(uint *)(param_1 + uVar3 * 4 + 0xd8);
          *(undefined4 *)(param_1 + uVar3 * 4 + 0xd8) = 0;
        }
        memcpy(param_1 + 0xe8,param_1 + 0xe9,7);
        *(char *)(param_1 + 0xf0) = *(char *)(param_1 + 0xf0) + -1;
        *(undefined1 *)(param_1 + 700) = 0;
        *(byte *)(param_1 + 0x84) =
             *(byte *)(param_1 + 0x84) & 0xbf | (*(byte *)(param_1 + 0xf1) & 1) << 6;
        *(byte *)(param_1 + 0xf1) = *(byte *)(param_1 + 0xf1) >> 1;
        SetMotion__11CFieldModelFi(param_1,uVar1);
        *(byte *)(param_1 + 0x81) = *(byte *)(param_1 + 0x81) & 0xbf;
      }
    }
    else if (((ulong)*(byte *)(param_1 + 0x85) & 0x3f) >> 4 < 3) {
      *(byte *)(param_1 + 0x80) = *(byte *)(param_1 + 0x80) & 0xdf;
    }
  }
  return;
}

/* JP: 0x004cb410  CFieldModel::TransCallBack(const FVector&, FVector)   [TransCallBack__11CFieldModelFRC7FVector7FVector]  size=0xe2c */
void TransCallBack__11CFieldModelFRC7FVector7FVector
               (undefined4 param_1,int param_2,undefined8 param_3,undefined4 *param_4)

{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined8 uVar4;
  long lVar5;
  long lVar6;
  long lVar7;
  float fVar8;
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
  undefined1 auStack_170 [16];
  float afStack_160 [2];
  float fStack_158;
  float afStack_150 [2];
  float fStack_148;
  float afStack_140 [2];
  float fStack_138;
  float afStack_130 [2];
  float fStack_128;
  undefined1 auStack_120 [16];
  undefined1 auStack_110 [16];
  undefined1 auStack_100 [4];
  undefined4 uStack_fc;
  float afStack_f0 [2];
  float fStack_e8;
  float fStack_e0;
  float fStack_dc;
  float fStack_d8;
  undefined1 auStack_d0 [4];
  float fStack_cc;
  undefined1 auStack_c0 [76];
  uint uStack_74;
  float fStack_70;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  int iStack_64;
  float fStack_60;
  float fStack_5c;
  float fStack_58;
  float fStack_54;
  float fStack_50;
  undefined4 uStack_4c;
  int iStack_48;
  int iStack_44;
  undefined4 uStack_40;
  int iStack_30;
  undefined4 *puStack_10;
  
  uStack_40 = param_1;
  iStack_30 = param_2;
  puStack_10 = param_4;
  if (1 < ((ulong)*(byte *)(param_2 + 0x86) & 0x1f) >> 3) {
    uVar4 = GetModel__11CFieldModelFv(param_2);
    uVar4 = getSequenceName__5ModelFQ25Model10MotionKind(uVar4,0);
    iStack_44 = strcmp(0x5561d8,uVar4);
    if ((iStack_44 == 0) && (((ulong)*(byte *)(iStack_30 + 0x86) & 0x1f) >> 3 == 2)) {
      *(byte *)(iStack_30 + 0x86) = *(byte *)(iStack_30 + 0x86) & 0xe7 | 0x18;
    }
    else if ((iStack_44 != 0) && (((ulong)*(byte *)(iStack_30 + 0x86) & 0x1f) >> 3 == 3)) {
      *(byte *)(iStack_30 + 0x86) = *(byte *)(iStack_30 + 0x86) & 0xe7;
    }
  }
  if (((((ulong)*(byte *)(iStack_30 + 0x88) & 7) >> 1 != 0) || (*(char *)(iStack_30 + 0xfc) != -1))
     || (((ulong)*(byte *)(iStack_30 + 0x86) & 0x1f) >> 3 != 0)) {
    puStack_10[2] = 0;
    puStack_10[1] = 0;
    *puStack_10 = 0;
    __as__7FVectorFRC7FVector(iStack_30 + 0x40,puStack_10);
    __ct__7FVectorFRC7FVector(uStack_40,puStack_10);
    return;
  }
  __ct__6MatrixFv(auStack_c0);
  __ct__7FVectorFv(auStack_d0);
  __ct__7FVectorFRC7FVector(&fStack_e0,iStack_30 + 0x10);
  iVar2 = *(int *)(sys__6CField + 0x1b8);
  *(undefined4 *)(iStack_30 + 0x2b0) = 0x3f800000;
  lVar5 = isFloorChk__11CFieldModelFv(iStack_30);
  if (((lVar5 != 0) && (*(char *)(iStack_30 + 0xfc) == -1)) &&
     ((((ulong)*(byte *)(iStack_30 + 0x85) & 0xf) >> 2 == 0 && (iVar2 != 0)))) {
    uVar4 = __ct__7FVectorFRC7FVector(auStack_170,iStack_30 + 0x10);
    iStack_48 = OnFloorChk__9CFloorManF7FVector(iVar2,uVar4);
    if (iStack_48 != 0) {
      uVar4 = __ct__7FVectorFRC7FVector(auStack_180,iStack_30 + 0x10);
      fStack_dc = (float)OnFloorPoint__9CFloorManF7FVectorPQ23SDB12tagFTRIANGLE
                                   (iVar2,uVar4,iStack_48);
      fVar8 = (float)sinf(*(undefined4 *)(iStack_30 + 0x34));
      fStack_e0 = fStack_e0 - fVar8;
      fVar8 = (float)cosf(*(undefined4 *)(iStack_30 + 0x34));
      fStack_d8 = fStack_d8 - fVar8;
      uVar4 = __ct__7FVectorFRC7FVector(auStack_190,&fStack_e0);
      lVar5 = OnFloorChk__9CFloorManF7FVector(iVar2,uVar4);
      uStack_4c = (undefined4)lVar5;
      if (lVar5 != 0) {
        uVar4 = __ct__7FVectorFRC7FVector(auStack_1a0,&fStack_e0);
        fStack_50 = (float)OnFloorPoint__9CFloorManF7FVectorPQ23SDB12tagFTRIANGLE
                                     (iVar2,uVar4,uStack_4c);
        fStack_50 = fStack_dc - fStack_50;
        if (fStack_50 < 0.0) {
          fStack_50 = fStack_50 * -0.5;
        }
        *(float *)(iStack_30 + 0x2b0) = 1.2 / (fStack_50 + 1.2);
      }
    }
  }
  puStack_10[2] = (float)puStack_10[2] * *(float *)(iStack_30 + 0x2b0);
  UnitMatrix__6MatrixFv(auStack_c0);
  RotXMatrix__6MatrixFf(*(undefined4 *)(iStack_30 + 0x30),auStack_c0);
  RotYMatrix__6MatrixFf(*(undefined4 *)(iStack_30 + 0x34),auStack_c0);
  RotZMatrix__6MatrixFf(*(undefined4 *)(iStack_30 + 0x38),auStack_c0);
  ApplyMatrix__6MatrixCFRC7FVector(auStack_1b0,auStack_c0,puStack_10);
  __as__7FVectorFRC7FVector(auStack_d0,auStack_1b0);
  fStack_54 = 0.0;
  __ct__7FVectorFRC7FVector(afStack_f0,auStack_d0);
  iVar3 = iStack_30;
  fVar8 = fStack_54;
  if (((ulong)*(byte *)(iStack_30 + 0x85) & 0xf) >> 2 != 0) {
    if (((ulong)*(byte *)(iStack_30 + 0x85) & 0xf) >> 2 == 1) {
      fStack_58 = fStack_cc;
      __ct__7FVectorFv(auStack_100);
      if (-1 < (long)((ulong)*(byte *)(iVar3 + 0x19a) << 0x3d)) {
        __as__7FVectorFRC7FVector(auStack_100,auStack_d0);
        uStack_fc = 0;
        fStack_58 = (float)Length__7FVectorCFv(auStack_100);
      }
      if ((*(byte *)(iVar3 + 0x19a) & 1) == 0) {
        __amu__7FVectorFf(0x3dcccccd,auStack_d0);
        fVar8 = fStack_54;
      }
      else {
        if (((long)((ulong)*(byte *)(iVar3 + 0x19b) << 0x3b) < 0) &&
           (*(ushort *)(iVar3 + 0x198) + 1 == (uint)*(byte *)(iVar3 + 0x19c))) {
          __mi__7FVectorCFRC7FVector(auStack_1c0,iVar3 + 0x1a0,iStack_30 + 0x10);
          __as__7FVectorFRC7FVector(auStack_100,auStack_1c0);
          fStack_5c = (float)Length__7FVectorCFv(auStack_100);
          fVar8 = fStack_5c;
          if (fStack_58 <= fStack_5c) {
            fVar8 = fStack_58;
          }
          fStack_58 = fVar8;
          Normalize__7FVectorFv(auStack_100);
          __ml__7FVectorCFf(fStack_58,auStack_1d0,auStack_100);
          __as__7FVectorFRC7FVector(auStack_d0,auStack_1d0);
        }
        fStack_54 = fStack_58;
        fVar8 = fStack_54;
      }
    }
    else {
      fStack_60 = (float)Length__7FVectorCFv(auStack_d0);
      fVar8 = fStack_60;
      if ((*(byte *)(iStack_30 + 0x19a) & 1) == 0) {
        __amu__7FVectorFf(0x3dcccccd,auStack_d0);
        fVar8 = fStack_54;
      }
    }
  }
  fStack_54 = fVar8;
  __as__7FVectorFRC7FVector(&fStack_e0,iStack_30 + 0x10);
  __as__7FVectorFRC7FVector(iStack_30 + 0x40,puStack_10);
  __apl__7FVectorFRC7FVector(iStack_30 + 0x10,auStack_d0);
  *(undefined4 *)(iStack_30 + 0x1c) = 0x3f800000;
  SetCollided__11CFieldModelFi(iStack_30,0);
  lVar5 = isHitChk__11CFieldModelFv(iStack_30);
  if ((lVar5 != 0) && (*(char *)(iStack_30 + 0xfc) == -1)) {
    lVar5 = 0;
    if ((((ulong)*(byte *)(iStack_30 + 0x85) & 0xf) >> 2 != 0) &&
       ((long)((ulong)*(byte *)(iStack_30 + 0x88) << 0x38) < 0)) {
      lVar5 = AutoAvoid__11CFieldModelFv(iStack_30);
    }
    if (lVar5 == 1) {
      fStack_54 = fStack_54 * 0.8;
      __amu__7FVectorFf(0x3f4ccccd,auStack_d0);
    }
    if (-1 < lVar5) {
      lVar5 = HitChkM2M__11CFieldModelFf(0,iStack_30);
      if (lVar5 == 0) {
        lVar5 = 0;
      }
      else {
        lVar5 = -1;
      }
    }
    if (lVar5 < 0) {
      SetCollided__11CFieldModelFi(iStack_30,1);
      __as__7FVectorFRC7FVector(iStack_30 + 0x10,&fStack_e0);
      Origin__7FVectorFv(auStack_d0);
      goto LAB_004cc188;
    }
  }
  lVar5 = isFloorChk__11CFieldModelFv(iStack_30);
  if ((((lVar5 == 0) || (*(char *)(iStack_30 + 0xfc) != -1)) ||
      (((ulong)*(byte *)(iStack_30 + 0x85) & 0xf) >> 2 != 0)) ||
     (iStack_64 = HitChkM2E__11CFieldModelFv(iStack_30), iStack_64 < 0)) {
    lVar5 = isFloorChk__11CFieldModelFv(iStack_30);
    if ((lVar5 != 0) && (iVar2 != 0)) {
      __ct__7FVectorFv(auStack_110);
      __ct__7FVectorFv(auStack_120);
      __ct__7FVectorFv(afStack_130);
      __ct__7FVectorFv(afStack_140);
      uVar4 = __as__7FVectorFRC7FVector(afStack_140,&fStack_e0);
      __as__7FVectorFRC7FVector(afStack_130,uVar4);
      __ct__7FVectorFv(afStack_150);
      __ct__7FVectorFv(afStack_160);
      uVar4 = __as__7FVectorFRC7FVector(afStack_160,afStack_f0);
      uVar4 = __as__7FVectorFRC7FVector(afStack_150,uVar4);
      lVar5 = 0;
      uStack_6c = Length__7FVectorCFv(puStack_10,uVar4);
      for (iVar3 = 0; iVar3 < 0xd; iVar3 = iVar3 + 1) {
        afStack_130[0] = fStack_e0 + afStack_150[0];
        fStack_128 = fStack_d8 + fStack_148;
        uVar4 = __ct__7FVectorFRC7FVector(auStack_1e0,afStack_130);
        lVar7 = CircleChk__9CFloorManF7FVectorf(0x40800000,iVar2,uVar4);
        afStack_140[0] = fStack_e0 + afStack_160[0];
        fStack_138 = fStack_d8 + fStack_158;
        uVar4 = __ct__7FVectorFRC7FVector(auStack_1f0,afStack_140);
        lVar6 = CircleChk__9CFloorManF7FVectorf(0x40800000,iVar2,uVar4);
        afStack_f0[0] = afStack_f0[0] * 0.91;
        fStack_e8 = fStack_e8 * 0.91;
        if ((lVar7 != 0) && (lVar6 != 0)) {
          afStack_130[0] = fStack_e0 + afStack_f0[0];
          fStack_128 = fStack_d8 + fStack_e8;
          uVar4 = __ct__7FVectorFRC7FVector(auStack_200,afStack_130);
          lVar5 = CircleChk__9CFloorManF7FVectorf(0x40800000,iVar2,uVar4);
          if (lVar5 != 0) break;
        }
        if ((lVar7 != 0) && (lVar6 == 0)) {
          __as__7FVectorFRC7FVector(afStack_f0,afStack_150);
          lVar5 = lVar7;
          break;
        }
        if ((lVar7 == 0) && (lVar6 != 0)) {
          __as__7FVectorFRC7FVector(afStack_f0,afStack_160);
          lVar5 = lVar6;
          break;
        }
        fVar8 = afStack_150[0] + fStack_148 * 0.11;
        fStack_158 = fStack_158 + afStack_160[0] * 0.11;
        afStack_150[0] = fVar8 * 0.91;
        fStack_148 = (fStack_148 - fVar8 * 0.11) * 0.91;
        afStack_160[0] = (afStack_160[0] - fStack_158 * 0.11) * 0.91;
        fStack_158 = fStack_158 * 0.91;
      }
      lVar7 = 0;
      if (lVar5 != 0) {
        __pl__7FVectorCFRC7FVector(auStack_210,&fStack_e0,afStack_f0);
        __as__7FVectorFRC7FVector(iStack_30 + 0x10,auStack_210);
        uVar4 = __ct__7FVectorFRC7FVector(auStack_220,iStack_30 + 0x10);
        lVar7 = CircleChk__9CFloorManF7FVectorf(0x40800000,iVar2,uVar4);
      }
      if (lVar7 == 0) {
        __as__7FVectorFRC7FVector(iStack_30 + 0x10,&fStack_e0);
        Origin__7FVectorFv(auStack_d0);
        fStack_54 = 0.0;
        if (((((ulong)*(byte *)(iStack_30 + 0x85) & 0xf) >> 2 != 0) &&
            ((long)((ulong)*(byte *)(iStack_30 + 0x88) << 0x38) < 0)) &&
           (cVar1 = *(char *)(iStack_30 + 0xbd), *(char *)(iStack_30 + 0xbd) = cVar1 + '\x01',
           100 < (byte)(cVar1 + 1U))) {
          *(byte *)(iStack_30 + 0x86) = *(byte *)(iStack_30 + 0x86) & 0xf8 | 2;
          *(undefined1 *)(iStack_30 + 0xbd) = 0;
        }
      }
      else {
        uVar4 = __ct__7FVectorFRC7FVector(auStack_230,iStack_30 + 0x10);
        uStack_68 = OnFloorPoint__9CFloorManF7FVectorPQ23SDB12tagFTRIANGLE(iVar2,uVar4,lVar7);
        *(undefined4 *)(iStack_30 + 0x14) = uStack_68;
        __as__7FVectorFRC7FVector(auStack_d0,afStack_f0);
      }
    }
    if ((*(byte *)(iStack_30 + 0x86) & 7) == 0) {
      *(float *)(iStack_30 + 0x194) = *(float *)(iStack_30 + 0x194) + fStack_54;
    }
  }
  else {
    SetCollided__11CFieldModelFi(iStack_30,1);
    __as__7FVectorFRC7FVector(iStack_30 + 0x10,&fStack_e0);
    Origin__7FVectorFv(auStack_d0);
  }
LAB_004cc188:
  lVar5 = isManual__11CFieldModelFv(iStack_30);
  if (lVar5 != 0) {
    fStack_70 = (float)Length__7FVectorCFv(auStack_d0);
    uStack_74 = (uint)(((ulong)*(byte *)(iStack_30 + 0x85) & 0x3f) >> 4 == 2);
    if (0.0 < fStack_70) {
      UpdateMoveDistance__6CFieldFfi(fStack_70,sys__6CField,uStack_74);
    }
  }
  __ct__7FVectorFRC7FVector(uStack_40,auStack_d0);
  return;
}

/* JP: 0x004cc240  CFieldModel::SetCollided(int)   [SetCollided__11CFieldModelFi]  size=0x40 */
void SetCollided__11CFieldModelFi(int param_1,byte param_2)

{
  *(byte *)(param_1 + 0x82) = *(byte *)(param_1 + 0x82) & 0xf7 | (param_2 & 1) << 3;
  return;
}

/* JP: 0x004cdc00  CFieldModel::DspIcon(int)   [DspIcon__11CFieldModelFi]  size=0xbc */
void DspIcon__11CFieldModelFi(int param_1,int param_2)

{
  undefined4 uVar1;
  long lVar2;
  
  if (param_2 < 0) {
    if (*(int *)(param_1 + 0x120) != 0) {
      Delete__8CBalIconFv(*(undefined4 *)(param_1 + 0x120));
      *(undefined4 *)(param_1 + 0x120) = 0;
    }
  }
  else {
    if (*(int *)(param_1 + 0x120) == 0) {
      lVar2 = __nw__FUi(0x2c);
      uVar1 = 0;
      if (lVar2 != 0) {
        uVar1 = __ct__8CBalIconFv(lVar2);
      }
      *(undefined4 *)(param_1 + 0x120) = uVar1;
    }
    SetPat__8CBalIconFii(*(undefined4 *)(param_1 + 0x120),param_2,0);
  }
  return;
}

/* JP: 0x004dae00  CFieldModel::SetRot(FVector)   [SetRot__11CFieldModelF7FVector]  size=0x38 */
void SetRot__11CFieldModelF7FVector(undefined4 param_1,undefined4 param_2)

{
  SetDir__11CFieldModelFR7FVectorii(param_1,param_2,0,3);
  return;
}

/* JP: 0x004dae40  CFieldModel::SetExModel(int)   [SetExModel__11CFieldModelFi]  size=0x3c */
void SetExModel__11CFieldModelFi(int param_1,byte param_2)

{
  *(byte *)(param_1 + 0x82) = *(byte *)(param_1 + 0x82) & 0xfe | param_2 & 1;
  return;
}

/* JP: 0x004dc4a0  CFieldModel::GetLastMotion   [GetLastMotion__11CFieldModelCFv]  size=0x1c */
int GetLastMotion__11CFieldModelCFv(int param_1)

{
  return param_1 + 0x2cc;
}
