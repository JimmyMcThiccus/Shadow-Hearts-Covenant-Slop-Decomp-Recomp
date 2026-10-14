/* ==== CLEANED (port: sh2_field/src/event.rs) ==== */
#include "_types.h"
extern void clipRadian(float *a);
/* JP 0x004bf020 CFieldEvent::Init */
void CFieldEvent_Init(CFieldEvent *this, SDB_tagEVENTBOX *boxes, int count, int is_camera) { this->is_camera = is_camera; this->boxes = boxes; this->count = count; }

/* JP 0x004bf0b0 CFieldEvent::HitCheck(FVector pos, int unused, int mode)  mode 0: kind-0 boxes, 1: all, 2: kind!=0 -> box index or -1 */
int CFieldEvent_HitCheck(CFieldEvent *this, FVector pos, int unused, int mode) {
    SDB_tagEVENTBOX *b = this->boxes;
    for (int i = 0; i < this->count; i++, b++) {
        int kind = (b->flags & 0x3f) >> 4;
        int use = 1;
        if (mode != 1 && kind != 0) use = 0;
        if (mode == 2) use = kind;
        if (!use) continue;
        FVector d = { pos.x - b->center.x, pos.y - b->center.y, pos.z - b->center.z, 1 };
        Matrix m; UnitMatrix(&m); RotYMatrix(&m, -b->rot_b); RotYMatrix(&m, -b->rot_a);
        FVector l = ApplyMatrix(&m, &d);
        FVector *c = b->corner;                                                    /* c[k].y of corner 0 = half height */
        float e, a;
        e = atan2f(c[0].x - c[1].x, c[0].z - c[1].z); a = atan2f(l.x - c[0].x, l.z - c[0].z) - e; clipRadian(&a); if (!(a < 0)) continue;
        e = atan2f(c[1].x - c[2].x, c[1].z - c[2].z); a = atan2f(l.x - c[1].x, l.z - c[1].z) - e; clipRadian(&a); if (!(a < 0)) continue;
        e = atan2f(c[2].x - c[3].x, c[2].z - c[3].z); a = atan2f(l.x - c[2].x, l.z - c[2].z) - e; clipRadian(&a); if (!(a < 0)) continue;
        e = atan2f(c[3].x - c[0].x, c[3].z - c[0].z); a = atan2f(l.x - c[3].x, l.z - c[3].z) - e; clipRadian(&a); if (!(a < 0)) continue;
        if (-c[0].y < l.y && l.y < c[0].y) return i;
    }
    return -1;
}
/* JP 0x004bf510 */ int CFieldEvent_GetEventNum(CFieldEvent *t, int i) { return (i >= 0 && i < t->count) ? t->boxes[i].id : -1; }
/* JP 0x004bf580 */ SDB_tagEVENTBOX *CFieldEvent_GetEventBox(CFieldEvent *t, int i) { return (i >= 0 && i < t->count) ? &t->boxes[i] : 0; }
/* JP 0x004bf5f0 */ int CFieldEvent_GetEventBoxFromID(CFieldEvent *t, int id, s16 *out) { int n = 0; for (int i = 0; i < t->count; i++) if (t->boxes[i].id == id) { out[n++] = i; if (n > 15) break; } return n; }
/* JP 0x004bf6b0 */ int CFieldEvent_GetEventBoxFromGroup(CFieldEvent *t, int g, s16 *out) { int n = 0; for (int i = 0; i < t->count; i++) if ((t->boxes[i].flags & 0xf) == g) { out[n++] = i; if (n > 15) break; } return n; }


/* ==== RAW (Ghidra output, names/globals resolved; not hand-cleaned) ==== */
/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CFieldEvent   functions: 8
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CFieldEvent.md).
 */

/* JP: 0x004befa0  CFieldEvent::CFieldEvent()   [__ct__11CFieldEventFv]  size=0x20 */
int __ct__11CFieldEventFv(CFieldEvent *this)

{
  this->pBoxes = (void *)0x0;
  return (int)this;
}

/* JP: 0x004befc0  CFieldEvent::~CFieldEvent()   [__dt__11CFieldEventFv]  size=0x54 */
int __dt__11CFieldEventFv(CFieldEvent *this,short flag)

{
  if ((this != (CFieldEvent *)0x0) && (0 < flag)) {
    __dl__FPv(this);
  }
  return (int)this;
}

/* JP: 0x004bf020  CFieldEvent::Init(SDB::tagEVENTBOX*, int, int)   [Init__11CFieldEventFPQ23SDB11tagEVENTBOXii]  size=0x8c */
void Init__11CFieldEventFPQ23SDB11tagEVENTBOXii(CFieldEvent *this,void *a0,int a1,int a2)

{
  int iVar1;
  
  this->nIs_camera = a2;
  this->pBoxes = a0;
  this->nCount = a1;
  for (iVar1 = 0; iVar1 < a1; iVar1 = iVar1 + 1) {
  }
  return;
}

/* JP: 0x004bf0b0  CFieldEvent::HitCheck(FVector, int, int)   [HitCheck__11CFieldEventF7FVectorii]  size=0x454 */
undefined4 HitCheck__11CFieldEventF7FVectorii(CFieldEvent *this,FVector *a0,int a1,int a2)

{
  ulong uVar1;
  float *pfVar2;
  void *pvVar3;
  int iVar4;
  undefined1 auStack_e0 [16];
  undefined1 auStack_d0 [16];
  undefined1 auStack_c0 [16];
  float fStack_b0;
  float fStack_ac;
  float fStack_a8;
  undefined1 auStack_a0 [16];
  undefined1 auStack_90 [64];
  float fStack_50;
  float fStack_4c;
  float fStack_48;
  float fStack_44;
  CFieldEvent *pCStack_40;
  FVector *pFStack_30;
  int iStack_10;
  
  pvVar3 = this->pBoxes;
  pCStack_40 = this;
  pFStack_30 = a0;
  iStack_10 = a2;
  __ct__6MatrixFv(auStack_90,a0,a1);
  __ct__7FVectorFv(auStack_a0);
  __ct__7FVectorFv(&fStack_b0);
  iVar4 = 0;
  do {
    if (pCStack_40->nCount <= iVar4) {
      return 0xffffffff;
    }
    uVar1 = 1;
    if ((iStack_10 != 1) && (((ulong)*(byte *)((int)pvVar3 + 8) & 0x3f) >> 4 != 0)) {
      uVar1 = 0;
    }
    if (iStack_10 == 2) {
      uVar1 = ((ulong)*(byte *)((int)pvVar3 + 8) & 0x3f) >> 4;
    }
    if (uVar1 != 0) {
      pfVar2 = (float *)((int)pvVar3 + 0x30);
      __ct__7FVectorFRC7FVector(auStack_c0,(int)pvVar3 + 0x10);
      __mi__7FVectorCFRC7FVector(auStack_d0,pFStack_30,auStack_c0);
      __as__7FVectorFRC7FVector(auStack_a0,auStack_d0);
      UnitMatrix__6MatrixFv(auStack_90);
      RotYMatrix__6MatrixFf(-*(float *)((int)pvVar3 + 0x24),auStack_90);
      RotYMatrix__6MatrixFf(-*(float *)((int)pvVar3 + 0x20),auStack_90);
      ApplyMatrix__6MatrixCFRC7FVector(auStack_e0,auStack_90,auStack_a0);
      __as__7FVectorFRC7FVector(&fStack_b0,auStack_e0);
      fStack_44 = *pfVar2 - *(float *)((int)pvVar3 + 0x40);
      fStack_48 = *(float *)((int)pvVar3 + 0x38) - *(float *)((int)pvVar3 + 0x48);
      fStack_4c = (float)atan2f(fStack_44,fStack_48);
      fStack_44 = fStack_b0 - *pfVar2;
      fStack_48 = fStack_a8 - *(float *)((int)pvVar3 + 0x38);
      fStack_50 = (float)atan2f(fStack_44,fStack_48);
      fStack_50 = fStack_50 - fStack_4c;
      clipRadian__FRf(&fStack_50);
      if (fStack_50 < 0.0) {
        fStack_44 = *(float *)((int)pvVar3 + 0x40) - *(float *)((int)pvVar3 + 0x50);
        fStack_48 = *(float *)((int)pvVar3 + 0x48) - *(float *)((int)pvVar3 + 0x58);
        fStack_4c = (float)atan2f(fStack_44,fStack_48);
        fStack_44 = fStack_b0 - *(float *)((int)pvVar3 + 0x40);
        fStack_48 = fStack_a8 - *(float *)((int)pvVar3 + 0x48);
        fStack_50 = (float)atan2f(fStack_44,fStack_48);
        fStack_50 = fStack_50 - fStack_4c;
        clipRadian__FRf(&fStack_50);
        if (fStack_50 < 0.0) {
          fStack_44 = *(float *)((int)pvVar3 + 0x50) - *(float *)((int)pvVar3 + 0x60);
          fStack_48 = *(float *)((int)pvVar3 + 0x58) - *(float *)((int)pvVar3 + 0x68);
          fStack_4c = (float)atan2f(fStack_44,fStack_48);
          fStack_44 = fStack_b0 - *(float *)((int)pvVar3 + 0x50);
          fStack_48 = fStack_a8 - *(float *)((int)pvVar3 + 0x58);
          fStack_50 = (float)atan2f(fStack_44,fStack_48);
          fStack_50 = fStack_50 - fStack_4c;
          clipRadian__FRf(&fStack_50);
          if (fStack_50 < 0.0) {
            fStack_44 = *(float *)((int)pvVar3 + 0x60) - *pfVar2;
            fStack_48 = *(float *)((int)pvVar3 + 0x68) - *(float *)((int)pvVar3 + 0x38);
            fStack_4c = (float)atan2f(fStack_44,fStack_48);
            fStack_44 = fStack_b0 - *(float *)((int)pvVar3 + 0x60);
            fStack_48 = fStack_a8 - *(float *)((int)pvVar3 + 0x68);
            fStack_50 = (float)atan2f(fStack_44,fStack_48);
            fStack_50 = fStack_50 - fStack_4c;
            clipRadian__FRf(&fStack_50);
            if (((fStack_50 < 0.0) && (-*(float *)((int)pvVar3 + 0x34) < fStack_ac)) &&
               (fStack_ac < *(float *)((int)pvVar3 + 0x34))) {
              return iVar4;
            }
          }
        }
      }
    }
    iVar4 = iVar4 + 1;
    pvVar3 = (void *)((int)pvVar3 + 0x70);
  } while( true );
}

/* JP: 0x004bf510  CFieldEvent::GetEventNum(int)   [GetEventNum__11CFieldEventFi]  size=0x6c */
undefined4 GetEventNum__11CFieldEventFi(CFieldEvent *this,int a0)

{
  undefined4 uVar1;
  
  uVar1 = 0xffffffff;
  if ((-1 < a0) && (a0 < this->nCount)) {
    uVar1 = *(undefined4 *)((int)this->pBoxes + a0 * 0x70 + 4);
  }
  return uVar1;
}

/* JP: 0x004bf580  CFieldEvent::GetEventBox(int)   [GetEventBox__11CFieldEventFi]  size=0x6c */
int GetEventBox__11CFieldEventFi(CFieldEvent *this,int a0)

{
  void *pvVar1;
  
  if ((a0 < 0) || (this->nCount <= a0)) {
    pvVar1 = (void *)0x0;
  }
  else {
    pvVar1 = (void *)((int)this->pBoxes + a0 * 0x70);
  }
  return (int)pvVar1;
}

/* JP: 0x004bf5f0  CFieldEvent::GetEventBoxFromID(int, short*)   [GetEventBoxFromID__11CFieldEventFiPs]  size=0xb8 */
int GetEventBoxFromID__11CFieldEventFiPs(CFieldEvent *this,int a0,short *a1)

{
  int iVar1;
  void *pvVar2;
  int iVar3;
  short *psStack_10;
  
  pvVar2 = this->pBoxes;
  iVar3 = 0;
  iVar1 = 0;
  psStack_10 = a1;
  do {
    if (this->nCount <= iVar1) {
      return iVar3;
    }
    if (*(int *)((int)pvVar2 + 4) == a0) {
      *psStack_10 = (short)iVar1;
      iVar3 = iVar3 + 1;
      psStack_10 = psStack_10 + 1;
      if (0xf < iVar3) {
        return iVar3;
      }
    }
    iVar1 = iVar1 + 1;
    pvVar2 = (void *)((int)pvVar2 + 0x70);
  } while( true );
}

/* JP: 0x004bf6b0  CFieldEvent::GetEventBoxFromGroup(int, short*)   [GetEventBoxFromGroup__11CFieldEventFiPs]  size=0xc0 */
int GetEventBoxFromGroup__11CFieldEventFiPs(CFieldEvent *this,int a0,short *a1)

{
  int iVar1;
  int iVar2;
  void *pvVar3;
  short *psStack_10;
  
  pvVar3 = this->pBoxes;
  iVar2 = 0;
  iVar1 = 0;
  psStack_10 = a1;
  do {
    if (this->nCount <= iVar1) {
      return iVar2;
    }
    if ((*(byte *)((int)pvVar3 + 8) & 0xf) == a0) {
      *psStack_10 = (short)iVar1;
      iVar2 = iVar2 + 1;
      psStack_10 = psStack_10 + 1;
      if (0xf < iVar2) {
        return iVar2;
      }
    }
    iVar1 = iVar1 + 1;
    pvVar3 = (void *)((int)pvVar3 + 0x70);
  } while( true );
}
