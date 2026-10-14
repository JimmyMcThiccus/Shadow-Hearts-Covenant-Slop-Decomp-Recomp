/* ==== CLEANED (hand-reconstructed from the decompilation; behaviour-equivalent, ported in port/crates/sh2_field/src/floor.rs) ==== */
#include "_types.h"
extern float atan2f(float, float);
extern void RotYMatrix(Matrix *m, float rad);      /* sceVu0RotMatrixY: M = M*Ry */
extern FVector ApplyMatrix(const Matrix *m, const FVector *v);

/* JP 0x004bc850 CFloorMan::CFloorMan() */
CFloorMan *CFloorMan_ctor(CFloorMan *this) {
    this->world = 0; this->vertices = 0; this->triangles = 0; this->slices = 0; this->cached = 0; this->rot_y = 0;
    return this;
}

/* JP 0x004bc900 CFloorMan::SetData(CSTGDB *db) -- relocates the on-disc indices into pointers (once; chunk.relocated guards it) */
int CFloorMan_SetData(CFloorMan *this, CSTGDB *db) {
    int ok = 1;
    SDB_tagHEADER *h = CSTGDB_Find(db, 'WORLD   ');
    if (!h) ok = 0; else {
        this->world = CSTGDB_GetDataAddr(db, h);
        if (this->world->slices_along_x == 0) { this->slice_along_z = 1; this->slice_count = this->world->slices_along_z; }
        else                                  { this->slice_along_z = 0; this->slice_count = this->world->slices_along_x; }
    }
    h = CSTGDB_Find(db, 'VERTEX  ');
    if (!h) ok = 0; else this->vertices = CSTGDB_GetDataAddr(db, h);
    h = CSTGDB_Find(db, 'TRIANGLE');
    if (!h) ok = 0; else {
        this->triangles = CSTGDB_GetDataAddr(db, h);
        if (!h->relocated) {
            h->relocated = 1;
            for (int i = 0; i < CSTGDB_GetDataNum(db, h); i++) {
                SDB_tagFTRIANGLE *t = &this->triangles[i];
                t->v[0] = (char *)this->vertices + (u32)t->v[0] * 0x10;     /* index -> vertex pointer */
                t->v[1] = (char *)this->vertices + (u32)t->v[1] * 0x10;
                t->v[2] = (char *)this->vertices + (u32)t->v[2] * 0x10;
            }
        }
    }
    h = CSTGDB_Find(db, 'SLICE   ');
    if (!h) ok = 0; else {
        u32 (*sl)[4] = CSTGDB_GetDataAddr(db, h); this->slices = (u32 *)sl;
        if (!h->relocated) {
            int n = CSTGDB_GetDataNum(db, h); h->relocated = 1;
            if (n != this->slice_count) ok = 0;
            for (int i = 0; i < n; i++) {
                u32 *e = &this->slices[i * 4];
                u32 *list = (u32 *)((char *)e + e[0]);                         /* entry+offset -> list */
                e[0] = (u32)list;
                for (u32 k = 0; k < e[1]; k++) list[k] = (u32)(this->triangles + list[k]);   /* tri index -> tri pointer */
            }
        }
    }
    return ok;
}

/* JP 0x004bcd30 CFloorMan::SetRotY(float deg) */
void CFloorMan_SetRotY(CFloorMan *this, float deg) {
    while (deg >= 360.0f) deg -= 360.0f;
    while (deg < 0.0f)    deg += 360.0f;
    this->rot_y = (deg < 180.0f) ? deg * 0.017453289f : (deg - 360.0f) * 0.017453289f;
}

/* JP 0x004bce40 CFloorMan::SetObstacle(int id, int flag) */
void CFloorMan_SetObstacle(CFloorMan *this, int id, u8 flag) {
    for (int i = 0; i < this->slice_count; i++) {
        SDB_tagFTRIANGLE **p = (SDB_tagFTRIANGLE **)this->slices[i * 4];          /* list pointer, entry [0] after relocation */
        for (; *p; p++) if ((*p)->obstacle_id == id) (*p)->blocked = flag;         /* lists are zero-terminated */
    }
}

/* JP 0x004bd580 CFloorMan::TriangleChk(tri, p, Matrix *m) -- m is the floor yaw matrix or NULL */
int CFloorMan_TriangleChk(CFloorMan *this, SDB_tagFTRIANGLE *t, FVector p, Matrix *m) {
    FVector a = *(FVector *)t->v[0], b = *(FVector *)t->v[1], c = *(FVector *)t->v[2];
    a.w = b.w = c.w = 1.0f;
    if (m) { a = ApplyMatrix(m, &a); b = ApplyMatrix(m, &b); c = ApplyMatrix(m, &c); }
    if (t->blocked) return 0;
    float e, q, d;
    e = atan2f(a.x - b.x, a.z - b.z); q = atan2f(p.x - b.x, p.z - b.z); d = q - e;
    if (d < -3.141592f) d += 6.283184f; if (d > 3.141592f) d -= 6.283184f; if (d < 0) return 0;
    e = atan2f(b.x - c.x, b.z - c.z); q = atan2f(p.x - c.x, p.z - c.z); d = q - e;
    if (d < -3.141592f) d += 6.283184f; if (d > 3.141592f) d -= 6.283184f; if (d < 0) return 0;
    e = atan2f(c.x - a.x, c.z - a.z); q = atan2f(p.x - a.x, p.z - a.z); d = q - e;
    if (d < -3.141592f) d += 6.283184f; if (d > 3.141592f) d -= 6.283184f; if (d < 0) return 0;
    float h = (c.y + a.y + b.y) * 0.3333f;
    return !(p.y < h - 20.0f || h + 20.0f < p.y);
}

/* JP 0x004bcef0 CFloorMan::OnFloorChk(FVector p) -> triangle or NULL, caches the hit in this->cached */
SDB_tagFTRIANGLE *CFloorMan_OnFloorChk(CFloorMan *this, FVector p) {
    Matrix fwd, inv; UnitMatrix(&fwd); UnitMatrix(&inv);
    if (this->rot_y != 0.0f) { RotYMatrix(&fwd, this->rot_y); RotYMatrix(&inv, -this->rot_y); }
    if (this->cached && CFloorMan_TriangleChk(this, this->cached, p, &fwd)) return this->cached;
    FVector l = ApplyMatrix(&inv, &p);
    float dx = l.x - this->world->origin_x, dz = l.z - this->world->origin_z;
    if (dx < 0 || dz < 0 || dx >= this->world->size_x || dz >= this->world->size_z) return 0;
    float frac, other; int first_half;
    if (!this->slice_along_z) { frac = dx / this->world->size_x; other = l.z; first_half = dz < this->world->size_z * 0.5f; }
    else                      { frac = dz / this->world->size_z; other = l.x; first_half = dx < this->world->size_x * 0.5f; }
    u32 *entry = &this->slices[(int)(this->slice_count * frac) * 4];
    SDB_tagFTRIANGLE **list = (SDB_tagFTRIANGLE **)entry[0]; u32 n = entry[1];
    SDB_tagFTRIANGLE **it = first_half ? list : list + n - 1;                      /* scan from the near end */
    for (;; it += first_half ? 1 : -1) {
        SDB_tagFTRIANGLE *t = *it;
        if (!t) { this->cached = 0; return 0; }                                    /* zero sentinel before/after the list */
        if (other < t->min_c || t->max_c < other) continue;
        if (CFloorMan_TriangleChk(this, t, p, &fwd)) { this->cached = t; return t; }
    }
}

/* JP 0x004bdaf0 CFloorMan::OnFloorPoint(FVector p, tri) -> y of the triangle plane at (p.x, p.z) */
float CFloorMan_OnFloorPoint(CFloorMan *this, FVector p, SDB_tagFTRIANGLE *t) {
    FVector *A = t->v[0], *B = t->v[1], *C = t->v[2];
    Matrix m; UnitMatrix(&m); RotYMatrix(&m, -this->rot_y); p = ApplyMatrix(&m, &p);
    FVector e50 = {C->x - B->x, C->y - B->y, C->z - B->z, 1}, e60 = {A->x - B->x, A->y - B->y, A->z - B->z, 1}, e70 = {p.x - B->x, 0, p.z - B->z, 1};
    float ang = atan2f(e50.x, e50.z);
    UnitMatrix(&m); RotYMatrix(&m, -ang);
    FVector r50 = ApplyMatrix(&m, &e50), r60 = ApplyMatrix(&m, &e60), r70 = ApplyMatrix(&m, &e70);
    float base = r50.y * (r70.z / r50.z) + B->y;                                   /* height on edge B->C */
    float corr;
    if (r60.z < r70.z) { float u = (r50.z - r70.z) / (r50.z - r60.z);
        corr = ((C->y + u * (A->y - C->y)) - base) * (r70.x / (r60.x * u)); }
    else               { float s = r70.z / r60.z;
        corr = ((B->y + r60.y * s) - base) * (r70.x / (r60.x * s)); }
    return base + corr;
}

/* JP 0x004bde90 CFloorMan::CircleChk(FVector p, float r) -> centre triangle if centre and 8 samples are all on the floor */
SDB_tagFTRIANGLE *CFloorMan_CircleChk(CFloorMan *this, FVector p, float r) {
    SDB_tagFTRIANGLE *c = CFloorMan_OnFloorChk(this, p); if (!c) return 0;
    float d = r * 0.707107f; FVector q = p;
    float dx[8] = { r, -r, 0, 0, -d, -d, d, d }, dz[8] = { 0, 0, -r, r, -d, d, d, -d };
    for (int i = 0; i < 8; i++) { q.x = p.x + dx[i]; q.z = p.z + dz[i]; if (!CFloorMan_OnFloorChk(this, q)) return 0; }
    return c;
}


/* ==== RAW (Ghidra output, names/globals resolved; not hand-cleaned) ==== */
/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CFloorMan   functions: 9
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CFloorMan.md).
 */

/* JP: 0x004bc850  CFloorMan::CFloorMan()   [__ct__9CFloorManFv]  size=0x4c */
undefined4 * __ct__9CFloorManFv(CFloorMan *this)

{
  this->pWorld = (void *)0x0;
  this->pVertices = (void *)0x0;
  this->pTriangles = (void *)0x0;
  this->pSlices = (void *)0x0;
  this->pCached_tri = (void *)0x0;
  this->flRot_y = 0.0;
  return &this->pWorld;
}

/* JP: 0x004bc8a0  CFloorMan::~CFloorMan()   [__dt__9CFloorManFv]  size=0x54 */
int __dt__9CFloorManFv(CFloorMan *this,short flag)

{
  if ((this != (CFloorMan *)0x0) && (0 < flag)) {
    __dl__FPv(this);
  }
  return (int)this;
}

/* JP: 0x004bc900  CFloorMan::SetData(CSTGDB*)   [SetData__9CFloorManFP6CSTGDB]  size=0x430 */
undefined4 SetData__9CFloorManFP6CSTGDB(CFloorMan *this,CSTGDB *a0)

{
  void *pvVar1;
  int iVar2;
  long lVar3;
  int iVar4;
  undefined4 uVar5;
  uint uVar6;
  int iVar7;
  
  uVar5 = 1;
  lVar3 = Find__6CSTGDBFUl(a0,0x202020444c524f57);
  if (lVar3 == 0) {
    uVar5 = 0;
  }
  else {
    pvVar1 = (void *)GetDataAddr__6CSTGDBFPQ23SDB9tagHEADER(a0,lVar3);
    this->pWorld = pvVar1;
    if (*(int *)((int)this->pWorld + 8) == 0) {
      this->nSlice_along_z = 1;
      this->nSlice_count = *(int *)((int)this->pWorld + 0xc);
    }
    else {
      this->nSlice_along_z = 0;
      this->nSlice_count = *(int *)((int)this->pWorld + 8);
    }
  }
  lVar3 = Find__6CSTGDBFUl(a0,0x2020584554524556);
  if (lVar3 == 0) {
    uVar5 = 0;
  }
  else {
    pvVar1 = (void *)GetDataAddr__6CSTGDBFPQ23SDB9tagHEADER(a0,lVar3);
    this->pVertices = pvVar1;
  }
  lVar3 = Find__6CSTGDBFUl(a0,0x454c474e41495254);
  if (lVar3 == 0) {
    uVar5 = 0;
  }
  else {
    pvVar1 = (void *)GetDataAddr__6CSTGDBFPQ23SDB9tagHEADER(a0,lVar3);
    this->pTriangles = pvVar1;
    if (*(int *)((int)lVar3 + 0x10) == 0) {
      iVar2 = GetDataNum__6CSTGDBFPQ23SDB9tagHEADER(a0,lVar3);
      *(undefined4 *)((int)lVar3 + 0x10) = 1;
      for (iVar4 = 0; iVar4 < iVar2; iVar4 = iVar4 + 1) {
        *(void **)((int)this->pTriangles + iVar4 * 0x20) =
             (void *)((int)this->pVertices + *(int *)((int)this->pTriangles + iVar4 * 0x20) * 0x10);
        *(void **)((int)this->pTriangles + iVar4 * 0x20 + 4) =
             (void *)((int)this->pVertices +
                     *(int *)((int)this->pTriangles + iVar4 * 0x20 + 4) * 0x10);
        *(void **)((int)this->pTriangles + iVar4 * 0x20 + 8) =
             (void *)((int)this->pVertices +
                     *(int *)((int)this->pTriangles + iVar4 * 0x20 + 8) * 0x10);
      }
    }
  }
  lVar3 = Find__6CSTGDBFUl(a0,0x2020204543494c53);
  if (lVar3 == 0) {
    uVar5 = 0;
  }
  else {
    pvVar1 = (void *)GetDataAddr__6CSTGDBFPQ23SDB9tagHEADER(a0,lVar3);
    this->pSlices = pvVar1;
    if (*(int *)((int)lVar3 + 0x10) == 0) {
      iVar2 = GetDataNum__6CSTGDBFPQ23SDB9tagHEADER(a0,lVar3);
      *(undefined4 *)((int)lVar3 + 0x10) = 1;
      if (iVar2 != this->nSlice_count) {
        uVar5 = 0;
      }
      for (iVar4 = 0; iVar4 < iVar2; iVar4 = iVar4 + 1) {
        iVar7 = (int)this->pSlices + *(int *)((int)this->pSlices + iVar4 * 0x10) + iVar4 * 0x10;
        *(int *)((int)this->pSlices + iVar4 * 0x10) = iVar7;
        for (uVar6 = 0; uVar6 < *(uint *)((int)this->pSlices + iVar4 * 0x10 + 4); uVar6 = uVar6 + 1)
        {
          *(void **)(iVar7 + uVar6 * 4) =
               (void *)((int)this->pTriangles + *(int *)(iVar7 + uVar6 * 4) * 0x20);
        }
      }
    }
  }
  return uVar5;
}

/* JP: 0x004bcd30  CFloorMan::SetRotY(float)   [SetRotY__9CFloorManFf]  size=0x104 */
void SetRotY__9CFloorManFf(CFloorMan *this,float a0)

{
  float fStack_10;
  
  for (fStack_10 = a0; 360.0 <= fStack_10; fStack_10 = fStack_10 - 360.0) {
  }
  for (; fStack_10 < 0.0; fStack_10 = fStack_10 + 360.0) {
  }
  if (fStack_10 < 180.0) {
    this->flRot_y = fStack_10 * 0.017453289;
  }
  else {
    this->flRot_y = (fStack_10 - 360.0) * 0.017453289;
  }
  return;
}

/* JP: 0x004bce40  CFloorMan::SetObstacle(int, int)   [SetObstacle__9CFloorManFii]  size=0xac */
void SetObstacle__9CFloorManFii(CFloorMan *this,int a0,int a1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  
  for (iVar2 = 0; iVar2 < this->nSlice_count; iVar2 = iVar2 + 1) {
    piVar3 = *(int **)((int)this->pSlices + iVar2 * 0x10);
    while( true ) {
      piVar4 = piVar3 + 1;
      iVar1 = *piVar3;
      if (iVar1 == 0) break;
      piVar3 = piVar4;
      if ((uint)*(byte *)(iVar1 + 0x17) == a0) {
        *(char *)(iVar1 + 0x16) = (char)a1;
      }
    }
  }
  return;
}

/* JP: 0x004bcef0  CFloorMan::OnFloorChk(FVector)   [OnFloorChk__9CFloorManF7FVector]  size=0x690 */
int OnFloorChk__9CFloorManF7FVector(CFloorMan *this,FVector *a0)

{
  FVector *pFVar1;
  int iVar2;
  void *a0_00;
  undefined4 *puVar3;
  undefined4 *puVar4;
  float fVar5;
  undefined1 auStack_130 [16];
  undefined1 auStack_120 [16];
  undefined1 auStack_110 [16];
  undefined1 auStack_100 [16];
  undefined1 auStack_f0 [16];
  undefined1 auStack_e0 [16];
  float afStack_d0 [2];
  float fStack_c8;
  undefined1 auStack_c0 [64];
  undefined1 auStack_80 [64];
  float afStack_40 [2];
  float fStack_38;
  float fStack_24;
  CFloorMan *pCStack_20;
  FVector *pFStack_10;
  
  pCStack_20 = this;
  pFStack_10 = a0;
  __ct__7FVectorFv(afStack_40);
  __ct__6MatrixFv(auStack_80);
  __ct__6MatrixFv(auStack_c0);
  UnitMatrix__6MatrixFv(auStack_80);
  UnitMatrix__6MatrixFv(auStack_c0);
  if (pCStack_20->flRot_y != 0.0) {
    RotYMatrix__6MatrixFf(pCStack_20->flRot_y,auStack_80);
    RotYMatrix__6MatrixFf(-pCStack_20->flRot_y,auStack_c0);
  }
  if (pCStack_20->pCached_tri != (void *)0x0) {
    pFVar1 = (FVector *)__ct__7FVectorFRC7FVector(auStack_e0,pFStack_10);
    iVar2 = TriangleChk__9CFloorManFPQ23SDB12tagFTRIANGLE7FVectorP6Matrix
                      (pCStack_20,pCStack_20->pCached_tri,pFVar1,auStack_80);
    if (iVar2 != 0) {
      return (int)pCStack_20->pCached_tri;
    }
  }
  __ct__7FVectorFv(afStack_d0);
  ApplyMatrix__6MatrixCFRC7FVector(auStack_f0,auStack_c0,pFStack_10);
  __as__7FVectorFRC7FVector(afStack_d0,auStack_f0);
  afStack_40[0] = afStack_d0[0] - *(float *)((int)pCStack_20->pWorld + 0x10);
  fStack_38 = fStack_c8 - *(float *)((int)pCStack_20->pWorld + 0x14);
  if ((((afStack_40[0] < 0.0) || (fStack_38 < 0.0)) ||
      (*(float *)pCStack_20->pWorld <= afStack_40[0])) ||
     (*(float *)((int)pCStack_20->pWorld + 4) <= fStack_38)) {
    a0_00 = (void *)0x0;
  }
  else if (pCStack_20->nSlice_along_z == 0) {
    fStack_24 = (float)pCStack_20->nSlice_count * (afStack_40[0] / *(float *)pCStack_20->pWorld);
    fVar5 = fStack_24;
    if (2.1474836e+09 <= fStack_24) {
      fVar5 = fStack_24 - 2.1474836e+09;
    }
    puVar3 = *(undefined4 **)((int)pCStack_20->pSlices + (int)fVar5 * 0x10);
    if (fStack_38 < *(float *)((int)pCStack_20->pWorld + 4) * 0.5) {
      do {
        do {
          puVar4 = puVar3 + 1;
          a0_00 = (void *)*puVar3;
          if (a0_00 == (void *)0x0) {
            pCStack_20->pCached_tri = (void *)0x0;
            return 0;
          }
          puVar3 = puVar4;
        } while ((fStack_c8 < *(float *)((int)a0_00 + 0x10)) ||
                (*(float *)((int)a0_00 + 0xc) < fStack_c8));
        pFVar1 = (FVector *)__ct__7FVectorFRC7FVector(auStack_100,pFStack_10);
        iVar2 = TriangleChk__9CFloorManFPQ23SDB12tagFTRIANGLE7FVectorP6Matrix
                          (pCStack_20,a0_00,pFVar1,auStack_80);
      } while (iVar2 == 0);
      pCStack_20->pCached_tri = a0_00;
    }
    else {
      fVar5 = fStack_24;
      if (2.1474836e+09 <= fStack_24) {
        fVar5 = fStack_24 - 2.1474836e+09;
      }
      puVar3 = puVar3 + *(int *)((int)pCStack_20->pSlices + (int)fVar5 * 0x10 + 4);
      do {
        do {
          puVar3 = puVar3 + -1;
          a0_00 = (void *)*puVar3;
          if (a0_00 == (void *)0x0) {
            pCStack_20->pCached_tri = (void *)0x0;
            return 0;
          }
        } while ((fStack_c8 < *(float *)((int)a0_00 + 0x10)) ||
                (*(float *)((int)a0_00 + 0xc) < fStack_c8));
        pFVar1 = (FVector *)__ct__7FVectorFRC7FVector(auStack_110,pFStack_10);
        iVar2 = TriangleChk__9CFloorManFPQ23SDB12tagFTRIANGLE7FVectorP6Matrix
                          (pCStack_20,a0_00,pFVar1,auStack_80);
      } while (iVar2 == 0);
      pCStack_20->pCached_tri = a0_00;
    }
  }
  else {
    fStack_24 = (float)pCStack_20->nSlice_count *
                (fStack_38 / *(float *)((int)pCStack_20->pWorld + 4));
    fVar5 = fStack_24;
    if (2.1474836e+09 <= fStack_24) {
      fVar5 = fStack_24 - 2.1474836e+09;
    }
    puVar3 = *(undefined4 **)((int)pCStack_20->pSlices + (int)fVar5 * 0x10);
    if (afStack_40[0] < *(float *)pCStack_20->pWorld * 0.5) {
      do {
        do {
          puVar4 = puVar3 + 1;
          a0_00 = (void *)*puVar3;
          if (a0_00 == (void *)0x0) {
            pCStack_20->pCached_tri = (void *)0x0;
            return 0;
          }
          puVar3 = puVar4;
        } while ((afStack_d0[0] < *(float *)((int)a0_00 + 0x10)) ||
                (*(float *)((int)a0_00 + 0xc) < afStack_d0[0]));
        pFVar1 = (FVector *)__ct__7FVectorFRC7FVector(auStack_120,pFStack_10);
        iVar2 = TriangleChk__9CFloorManFPQ23SDB12tagFTRIANGLE7FVectorP6Matrix
                          (pCStack_20,a0_00,pFVar1,auStack_80);
      } while (iVar2 == 0);
      pCStack_20->pCached_tri = a0_00;
    }
    else {
      fVar5 = fStack_24;
      if (2.1474836e+09 <= fStack_24) {
        fVar5 = fStack_24 - 2.1474836e+09;
      }
      puVar3 = puVar3 + *(int *)((int)pCStack_20->pSlices + (int)fVar5 * 0x10 + 4);
      do {
        do {
          puVar3 = puVar3 + -1;
          a0_00 = (void *)*puVar3;
          if (a0_00 == (void *)0x0) {
            pCStack_20->pCached_tri = (void *)0x0;
            return 0;
          }
        } while ((afStack_d0[0] < *(float *)((int)a0_00 + 0x10)) ||
                (*(float *)((int)a0_00 + 0xc) < afStack_d0[0]));
        pFVar1 = (FVector *)__ct__7FVectorFRC7FVector(auStack_130,pFStack_10);
        iVar2 = TriangleChk__9CFloorManFPQ23SDB12tagFTRIANGLE7FVectorP6Matrix
                          (pCStack_20,a0_00,pFVar1,auStack_80);
      } while (iVar2 == 0);
      pCStack_20->pCached_tri = a0_00;
    }
  }
  return (int)a0_00;
}

/* JP: 0x004bd580  CFloorMan::TriangleChk(SDB::tagFTRIANGLE*, FVector, Matrix*)   [TriangleChk__9CFloorManFPQ23SDB12tagFTRIANGLE7FVectorP6Matrix]  size=0x56c */
undefined4
TriangleChk__9CFloorManFPQ23SDB12tagFTRIANGLE7FVectorP6Matrix
          (CFloorMan *this,void *a0,FVector *a1,void *a2)

{
  float *pfVar1;
  undefined4 uVar2;
  float fVar3;
  undefined1 auStack_b0 [16];
  undefined1 auStack_a0 [16];
  undefined1 auStack_90 [16];
  float fStack_80;
  float fStack_7c;
  float fStack_78;
  undefined4 uStack_74;
  float fStack_70;
  float fStack_6c;
  float fStack_68;
  undefined4 uStack_64;
  float fStack_60;
  float fStack_5c;
  float fStack_58;
  undefined4 uStack_54;
  float fStack_50;
  float fStack_4c;
  float fStack_48;
  float fStack_44;
  int *piStack_30;
  FVector *pFStack_20;
  void *pvStack_10;
  
  piStack_30 = a0;
  pFStack_20 = a1;
  pvStack_10 = a2;
  __ct__7FVectorFv(&fStack_60);
  __ct__7FVectorFv(&fStack_70);
  __ct__7FVectorFv(&fStack_80);
  pfVar1 = (float *)*piStack_30;
  fStack_60 = *pfVar1;
  fStack_5c = pfVar1[1];
  fStack_58 = pfVar1[2];
  pfVar1 = (float *)piStack_30[1];
  fStack_70 = *pfVar1;
  fStack_6c = pfVar1[1];
  fStack_68 = pfVar1[2];
  pfVar1 = (float *)piStack_30[2];
  fStack_80 = *pfVar1;
  fStack_7c = pfVar1[1];
  fStack_78 = pfVar1[2];
  uStack_74 = 0x3f800000;
  uStack_64 = 0x3f800000;
  uStack_54 = 0x3f800000;
  if (pvStack_10 != (void *)0x0) {
    ApplyMatrix__6MatrixCFRC7FVector(auStack_90,pvStack_10,&fStack_60);
    __as__7FVectorFRC7FVector(&fStack_60,auStack_90);
    ApplyMatrix__6MatrixCFRC7FVector(auStack_a0,pvStack_10,&fStack_70);
    __as__7FVectorFRC7FVector(&fStack_70,auStack_a0);
    ApplyMatrix__6MatrixCFRC7FVector(auStack_b0,pvStack_10,&fStack_80);
    __as__7FVectorFRC7FVector(&fStack_80,auStack_b0);
  }
  if (*(char *)((int)piStack_30 + 0x16) == '\0') {
    fStack_44 = fStack_60 - fStack_70;
    fStack_48 = fStack_58 - fStack_68;
    fStack_4c = (float)atan2f(fStack_44,fStack_48);
    fStack_44 = pFStack_20->flX - fStack_70;
    fStack_48 = pFStack_20->flZ - fStack_68;
    fStack_50 = (float)atan2f(fStack_44,fStack_48);
    fStack_50 = fStack_50 - fStack_4c;
    if (fStack_50 < -3.141592) {
      fStack_50 = fStack_50 + 6.283184;
    }
    if (3.141592 < fStack_50) {
      fStack_50 = fStack_50 - 6.283184;
    }
    if (fStack_50 < 0.0) {
      uVar2 = 0;
    }
    else {
      fStack_44 = fStack_70 - fStack_80;
      fStack_48 = fStack_68 - fStack_78;
      fStack_4c = (float)atan2f(fStack_44,fStack_48);
      fStack_44 = pFStack_20->flX - fStack_80;
      fStack_48 = pFStack_20->flZ - fStack_78;
      fStack_50 = (float)atan2f(fStack_44,fStack_48);
      fStack_50 = fStack_50 - fStack_4c;
      if (fStack_50 < -3.141592) {
        fStack_50 = fStack_50 + 6.283184;
      }
      if (3.141592 < fStack_50) {
        fStack_50 = fStack_50 - 6.283184;
      }
      if (fStack_50 < 0.0) {
        uVar2 = 0;
      }
      else {
        fStack_44 = fStack_80 - fStack_60;
        fStack_48 = fStack_78 - fStack_58;
        fStack_4c = (float)atan2f(fStack_44,fStack_48);
        fStack_44 = pFStack_20->flX - fStack_60;
        fStack_48 = pFStack_20->flZ - fStack_58;
        fStack_50 = (float)atan2f(fStack_44,fStack_48);
        fStack_50 = fStack_50 - fStack_4c;
        if (fStack_50 < -3.141592) {
          fStack_50 = fStack_50 + 6.283184;
        }
        if (3.141592 < fStack_50) {
          fStack_50 = fStack_50 - 6.283184;
        }
        if (fStack_50 < 0.0) {
          uVar2 = 0;
        }
        else {
          fVar3 = (fStack_7c + fStack_5c + fStack_6c) * 0.3333;
          if ((pFStack_20->flY < fVar3 - 20.0) || (fVar3 + 20.0 < pFStack_20->flY)) {
            uVar2 = 0;
          }
          else {
            uVar2 = 1;
          }
        }
      }
    }
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

/* JP: 0x004bdaf0  CFloorMan::OnFloorPoint(FVector, SDB::tagFTRIANGLE*)   [OnFloorPoint__9CFloorManF7FVectorPQ23SDB12tagFTRIANGLE]  size=0x394 */
undefined4
OnFloorPoint__9CFloorManF7FVectorPQ23SDB12tagFTRIANGLE(CFloorMan *this,FVector *a0,void *a1)

{
  float *pfVar1;
  float *pfVar2;
  float *pfVar3;
  undefined4 uVar4;
  undefined8 uVar5;
  undefined1 auStack_150 [16];
  undefined1 auStack_140 [16];
  undefined1 auStack_130 [16];
  undefined1 auStack_120 [16];
  undefined1 auStack_110 [16];
  undefined1 auStack_100 [16];
  undefined1 auStack_f0 [16];
  undefined1 auStack_e0 [64];
  undefined1 auStack_a0 [16];
  undefined1 auStack_90 [16];
  undefined1 auStack_80 [16];
  undefined1 auStack_70 [16];
  undefined1 auStack_60 [16];
  undefined4 auStack_50 [2];
  undefined4 uStack_48;
  float fStack_34;
  CFloorMan *pCStack_30;
  FVector *pFStack_20;
  int *piStack_10;
  
  pCStack_30 = this;
  pFStack_20 = a0;
  piStack_10 = a1;
  __ct__7FVectorFv(auStack_50);
  __ct__7FVectorFv(auStack_60);
  __ct__7FVectorFv(auStack_70);
  __ct__7FVectorFv(auStack_80);
  __ct__7FVectorFv(auStack_90);
  __ct__7FVectorFv(auStack_a0);
  __ct__6MatrixFv(auStack_e0);
  pfVar1 = (float *)*piStack_10;
  pfVar2 = (float *)piStack_10[1];
  pfVar3 = (float *)piStack_10[2];
  UnitMatrix__6MatrixFv(auStack_e0);
  RotYMatrix__6MatrixFf(-pCStack_30->flRot_y,auStack_e0);
  ApplyMatrix__6MatrixCFRC7FVector(auStack_f0,auStack_e0,pFStack_20);
  __as__7FVectorFRC7FVector(pFStack_20,auStack_f0);
  uVar5 = __ct__7FVectorFffff(*pfVar3 - *pfVar2,pfVar3[1] - pfVar2[1],pfVar3[2] - pfVar2[2],
                              0x3f800000,auStack_100);
  __as__7FVectorFRC7FVector(auStack_50,uVar5);
  uVar5 = __ct__7FVectorFffff(*pfVar1 - *pfVar2,pfVar1[1] - pfVar2[1],pfVar1[2] - pfVar2[2],
                              0x3f800000,auStack_110);
  __as__7FVectorFRC7FVector(auStack_60,uVar5);
  uVar5 = __ct__7FVectorFffff(pFStack_20->flX - *pfVar2,0,pFStack_20->flZ - pfVar2[2],0x3f800000,
                              auStack_120);
  __as__7FVectorFRC7FVector(auStack_70,uVar5);
  fStack_34 = (float)atan2f(auStack_50[0],uStack_48);
  UnitMatrix__6MatrixFv(auStack_e0);
  RotYMatrix__6MatrixFf(-fStack_34,auStack_e0);
  ApplyMatrix__6MatrixCFRC7FVector(auStack_130,auStack_e0,auStack_50);
  __as__7FVectorFRC7FVector(auStack_80,auStack_130);
  ApplyMatrix__6MatrixCFRC7FVector(auStack_140,auStack_e0,auStack_60);
  __as__7FVectorFRC7FVector(auStack_90,auStack_140);
  ApplyMatrix__6MatrixCFRC7FVector(auStack_150,auStack_e0,auStack_70);
  uVar4 = __as__7FVectorFRC7FVector(auStack_a0,auStack_150);
  return uVar4;
}

/* JP: 0x004bde90  CFloorMan::CircleChk(FVector, float)   [CircleChk__9CFloorManF7FVectorf]  size=0x2fc */
long CircleChk__9CFloorManF7FVectorf(CFloorMan *this,FVector *a0,float a1)

{
  FVector *pFVar1;
  int iVar2;
  long lVar3;
  undefined1 auStack_e0 [16];
  undefined1 auStack_d0 [16];
  undefined1 auStack_c0 [16];
  undefined1 auStack_b0 [16];
  undefined1 auStack_a0 [16];
  undefined1 auStack_90 [16];
  undefined1 auStack_80 [16];
  undefined1 auStack_70 [16];
  undefined1 auStack_60 [16];
  float afStack_50 [2];
  float fStack_48;
  float fStack_34;
  CFloorMan *pCStack_30;
  FVector *pFStack_20;
  float fStack_10;
  
  pCStack_30 = this;
  pFStack_20 = a0;
  fStack_10 = a1;
  __ct__7FVectorFRC7FVector(afStack_50,a0);
  pFVar1 = (FVector *)__ct__7FVectorFRC7FVector(auStack_60,pFStack_20);
  iVar2 = OnFloorChk__9CFloorManF7FVector(pCStack_30,pFVar1);
  lVar3 = (long)iVar2;
  if (lVar3 == 0) {
    lVar3 = 0;
  }
  else {
    afStack_50[0] = afStack_50[0] + fStack_10;
    pFVar1 = (FVector *)__ct__7FVectorFRC7FVector(auStack_70,afStack_50);
    iVar2 = OnFloorChk__9CFloorManF7FVector(pCStack_30,pFVar1);
    if (iVar2 == 0) {
      lVar3 = 0;
    }
    else {
      afStack_50[0] = pFStack_20->flX - fStack_10;
      pFVar1 = (FVector *)__ct__7FVectorFRC7FVector(auStack_80,afStack_50);
      iVar2 = OnFloorChk__9CFloorManF7FVector(pCStack_30,pFVar1);
      if (iVar2 == 0) {
        lVar3 = 0;
      }
      else {
        afStack_50[0] = pFStack_20->flX;
        fStack_48 = pFStack_20->flZ - fStack_10;
        pFVar1 = (FVector *)__ct__7FVectorFRC7FVector(auStack_90,afStack_50);
        iVar2 = OnFloorChk__9CFloorManF7FVector(pCStack_30,pFVar1);
        if (iVar2 == 0) {
          lVar3 = 0;
        }
        else {
          fStack_48 = pFStack_20->flZ + fStack_10;
          pFVar1 = (FVector *)__ct__7FVectorFRC7FVector(auStack_a0,afStack_50);
          iVar2 = OnFloorChk__9CFloorManF7FVector(pCStack_30,pFVar1);
          if (iVar2 == 0) {
            lVar3 = 0;
          }
          else {
            fStack_34 = fStack_10 * 0.707107;
            afStack_50[0] = pFStack_20->flX - fStack_34;
            fStack_48 = pFStack_20->flZ - fStack_34;
            pFVar1 = (FVector *)__ct__7FVectorFRC7FVector(auStack_b0,afStack_50);
            iVar2 = OnFloorChk__9CFloorManF7FVector(pCStack_30,pFVar1);
            if (iVar2 == 0) {
              lVar3 = 0;
            }
            else {
              fStack_48 = pFStack_20->flZ + fStack_34;
              pFVar1 = (FVector *)__ct__7FVectorFRC7FVector(auStack_c0,afStack_50);
              iVar2 = OnFloorChk__9CFloorManF7FVector(pCStack_30,pFVar1);
              if (iVar2 == 0) {
                lVar3 = 0;
              }
              else {
                afStack_50[0] = pFStack_20->flX + fStack_34;
                pFVar1 = (FVector *)__ct__7FVectorFRC7FVector(auStack_d0,afStack_50);
                iVar2 = OnFloorChk__9CFloorManF7FVector(pCStack_30,pFVar1);
                if (iVar2 == 0) {
                  lVar3 = 0;
                }
                else {
                  fStack_48 = pFStack_20->flZ - fStack_34;
                  pFVar1 = (FVector *)__ct__7FVectorFRC7FVector(auStack_e0,afStack_50);
                  iVar2 = OnFloorChk__9CFloorManF7FVector(pCStack_30,pFVar1);
                  if (iVar2 == 0) {
                    lVar3 = 0;
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  return lVar3;
}
