/* CFieldEvent / CFloorMan / CSTGDB consumers - retail (SH2US_FIELD.BIN). Unchanged algorithms are only referenced; the retail addition is SweepHit. */
#include "_types_retail.h"

/* US 0x00506c90 CFieldEvent::HitCheck(FVector p, int mode, int, int)  (JP 0x004bf0b0): unchanged.
 * mode 0: boxes whose kind ((flags & 0x3f) >> 4) == 0, 1: all, 2: kind != 0. Per box: translate by centre (+0x10), rotate by -(rot_a + rot_b) about Y,
 * four atan2(dx, dz) edge tests on the XZ corners (+0x30,+0x40,+0x50,+0x60), |y| < corner0.y. */

/* RETAIL US 0x00507010 CFieldEvent::SweepHit(box_index, FVector *p0 /*in: old, out: corrected*/, const FVector *p1) - slide along the nearest box edge.
 * Reconstructed from the decompilation (VU0 heavy; operand roles inferred): */
void CFieldEvent_SweepHit(CFieldEvent *ev, FVector *p0, const FVector *p1, int box_index) {
    SDB_tagEVENTBOX *b = (SDB_tagEVENTBOX *)((u8 *)ev->boxes + box_index * 0x70);
    FVector dir = *p1 - *p0;  dir.w = 0;  Normalize(&dir);                  /* movement direction */
    FVector probe = *p1 + dir * 5.0f;                                          /* segment p0 -> p1 extended by 5 units */
    Matrix m = Unit(); RotX(&m, b->rot_b); RotY(&m, b->rot_a);                /* box orientation */
    FVector corner[4];
    for (int k = 0; k < 4; k++) corner[k] = Apply(m, b->corner[k]) + b->center;
    /* for each of the 4 edges: distance from the probe segment; remember the nearest edge (i6) and project the movement onto it */
    float best = 3.4e38f; int edge = 0;
    for (int k = 0; k < 4; k++) { FVector e = corner[(k + 1) & 3] - corner[k]; ... compare |cross| / dot terms with thresholds -0.999 .. 0.999 ... }
    /* result: *p0 = slid position along edge `edge` (component of the step parallel to the edge), perpendicular part removed */
    *p0 = slid;
}

/* RETAIL US 0x004f1080 Retail_CField_CheckEventBoxSweep(CField *f, FVector *p0, const FVector *p1, int box): returns (byte f+0xa03 == 0), calling SweepHit when it is. */
int Retail_CField_CheckEventBoxSweep(CField *f, FVector *p0, const FVector *p1, int box) {
    int ok = RF(u8, 0xa03, f) == 0;
    if (ok) CFieldEvent_SweepHit(CF_EVENT_BOXES(f), p0, p1, box);
    return ok;
}

/* US 0x00504ec0 CFloorMan::SetData(CSTGDB *db)  (JP 0x004bc900): identical. */
int CFloorMan_SetData(CFloorMan *fm, CSTGDB *db) {
    int ok = 1; SDB_tagHEADER *h;
    if (!(h = CSTGDB_Find(db, 'WORLD   '))) ok = 0; else { fm->world = CSTGDB_GetDataAddr(db, h);
        if (fm->world->slices_along_x == 0) { fm->slice_along_z = 1; fm->slice_count = fm->world->slices_along_z; } else { fm->slice_along_z = 0; fm->slice_count = fm->world->slices_along_x; } }
    if (!(h = CSTGDB_Find(db, 'VERTEX  '))) ok = 0; else fm->vertices = CSTGDB_GetDataAddr(db, h);
    if (!(h = CSTGDB_Find(db, 'TRIANGLE'))) ok = 0; else { fm->triangles = CSTGDB_GetDataAddr(db, h);
        if (!h->relocated) { h->relocated = 1; for (i = 0; i < CSTGDB_GetDataNum(db, h); i++) for (k = 0; k < 3; k++) fm->triangles[i].v[k] = fm->vertices + (u32)fm->triangles[i].v[k]; } }   /* 0x10 byte vertices */
    if (!(h = CSTGDB_Find(db, 'SLICE   '))) ok = 0; else { fm->slices = CSTGDB_GetDataAddr(db, h);
        if (!h->relocated) { h->relocated = 1; if (CSTGDB_GetDataNum(db, h) != fm->slice_count) ok = 0;
            for (i = 0; i < n; i++) { u32 *list = (u32 *)((u8 *)&fm->slices[i] + fm->slices[i].list_off); fm->slices[i].list = list; for (k = 0; k < fm->slices[i].count; k++) list[k] = (u32)(fm->triangles + list[k]); } } }
    return ok;
}
