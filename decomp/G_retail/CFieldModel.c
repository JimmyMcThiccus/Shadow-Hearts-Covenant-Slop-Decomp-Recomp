/* Cleaned retail CFieldModel (SH2US_FIELD.BIN): the movement callback, SetDir and the retail-only sight / menu-hide helpers.
 * NOTE: TransCallBack is an *outline* - structure, flag tests and constants are verbatim from the decompilation, blocks marked "..." are identical to the JP version.
 * JP reference: ../G/CFieldModel.c and notes/G/CFieldModel.md (movement pipeline). Offsets here are RETAIL offsets (JP + delta, see notes/G_retail/CFieldModel.md). */
#include "_types_retail.h"
#define CM(t, o, m) RF(t, o, m)
#define CM_DISP(m)      CM(u8, 0x90, m)       /* b0-1 load/display mode, b2-3 shown */
#define CM_GAIT(m)      CM(u8, 0x95, m)       /* b0-1 turn state, b2-3 move mode (0 none, 1 auto-move, 2 path-move) */
#define CM_FLAGS98(m)   CM(u8, 0x98, m)       /* b0 manual (player), b1-2 hit flags, b4-5 kind (1 = controlled) */
#define CM_ROT(m)       CM(FVector, 0x20, m)  /* .y = yaw (rad) */
#define CM_MROT(m)      CM(FVector, 0x30, m)  /* move rotation used to orient the root translation */
#define CM_POS(m)       CM(FVector, 0x10, m)
#define CM_SLOPE(m)     CM(float, 0x310, m)   /* JP +0x2b0 */

/* US 0x00511560 CFieldModel::TransCallBack(const FVector &trans, FVector &out)  (JP 0x004cb410) - called by the motion player every frame
 * with the root-bone translation of the animation; writes the actually applied translation to +0x40 and sets +0x10 (position). */
void CFieldModel_TransCallBack(FVector *out, CFieldModel *m, FVector *trans) {
    CFloorMan *fl = fld ? CF_FLOOR(fld) : 0;
    /* hold states: zero the translation */
    if ((CM_FLAGS98(m) & 6) || CM(s8, 0x118, m) != -1 || ((CM(u8, 0x96, m) & 0x1f) >> 3)) { *trans = (FVector){0, 0, 0, 0}; CM(FVector, 0x40, m) = *trans; if (CM(s8, 0x118, m) != -1) { *out = *trans; return; } }
    /* slope scale: floor height here vs one unit behind (unchanged constants) */
    CM_SLOPE(m) = 1.0f;
    if (fl && (CM_FLAGS98(m) >> 4 & 3) == 1 && CM(s8, 0x118, m) == -1 && !(CM_GAIT(m) & 0xc)) {
        if (tri = CFloorMan_OnFloorChk(fl, CM_POS(m))) { float y0 = CFloorMan_OnFloorPoint(fl, CM_POS(m), tri);
            FVector behind = CM_POS(m); behind.x -= -sinf(CM_MROT(m).y)... (uses ±sin/cos of +0x34); behind.z -= cosf(...);
            if (tri2 = CFloorMan_OnFloorChk(fl, behind)) { float dh = y0 - CFloorMan_OnFloorPoint(fl, behind, tri2); if (dh < 0) dh *= -0.5f; CM_SLOPE(m) = 1.2f / (dh + 1.2f); } } }
    trans->z *= CM_SLOPE(m);
    FVector step = apply(RotZ(CM_MROT(m).z) * RotY(CM_MROT(m).y) * RotX(CM_MROT(m).x), *trans);       /* M = Rz*Ry*Rx (unchanged) */
    float len = 0;
    if (CM_GAIT(m) & 0xc) { /* auto-move / path-move clamp: step length limited to the remaining distance, 0.1 scale when +0x1ba.0 clear */ }
    CM(FVector, 0x40, m) = *trans;
    float speed = len;                                                                   /* distance moved this frame */
    int hit = -1;
    if (CM_FLAGS98(m) & 8) {                                                             /* collides with models */
        int avoid = ((CM_GAIT(m) & 0xc) && (CM_FLAGS98(m) & 0x80)) ? CFieldModel_AutoAvoid(m) : 0;
        if (avoid == 1) { speed *= 0.8f; /* JP: same constant */ }
        if (avoid >= 0) hit = CFieldModel_HitChkM2M(m, 0) ? -1 : 0;
    }
    /* RETAIL: event boxes act as walls for the controlled model */
    if (CM_FLAGS98(m) >> 4 == 1 && CM(s8, 0x118, m) == -1 && !(CM_GAIT(m) & 0xc)) {
        int box = CFieldModel_HitChkM2E(m, -1);
        if (box >= 0) {
            int blocked = Retail_CField_CheckEventBoxSweep(fld, &CM_POS(m), &prev_pos, box);   /* -> SweepHit (0x00507010) */
            if (blocked && CFieldModel_HitChkM2E(m, box) < 0 && fl && !CFloorMan_CircleChk(fl, CM_POS(m), 4.0f)) blocked = 0;
            if (!blocked) CM_POS(m) = prev_pos;
            CM(u8, 0x92, m) = (CM(u8, 0x92, m) & ~2) | 2; return_translation_zero(m, out); return; } }
    /* floor confinement (unchanged): circle test r = 4.0 at the new position; on failure up to 13 iterations shrink the step by 0.91 and test
     * two candidate directions rotated by +-atan(0.11) (cx' = (cx + cz*0.11)*0.91, cz' = (cz - cx*0.11)*0.91); pick the first free one;
     * if none works the actor stays (auto movers count +0xcd up). Finally CircleChk + OnFloorPoint set y. */
    ...
    CFieldModel_UpdateMoveDistance(m, speed);                                                 /* encounter distance for the manual model */
    *out = step_applied;
}

/* US 0x0050d7b0 CFieldModel::SetDir(const FVector &dir, int mode, int steps)  (JP 0x004c70e0)
 * mode 0: snap, 1..3: turn with motions 0x2a (left) / 0x29 (right) when the model has them, bit 2 of mode (>=4): explicit side. */
void CFieldModel_SetDir(CFieldModel *m, const FVector *dir, int mode, int steps) {
    CM_MROT(m) = *dir; CM_SLOPE_TURN(m) /* +0x314 */ = 1.0f; CM_MROT(m).y = ClipRadian(CM_MROT(m).y);
    if (mode == 0) { CM_ROT(m) = CM_MROT(m); CM(u8, 0x9a, m) |= 0x80; return; }
    if (fabsf(CM_ROT(m).y - CM_MROT(m).y) <= 0.017453289f) {                  /* RETAIL: below 1 degree -> snap, no turn animation */
        CM_ROT(m) = CM_MROT(m); CM(u8, 0x96, m) &= 0xe7; return; }
    CM(float, 0x314, m) = steps < 0 ? -1.0f / steps : (steps + 1) * 0.25f;
    float c = dot(Ry(CM_MROT(m).y) * (0,0,1), Ry(CM_ROT(m).y) * (0,0,1));      /* cos of the heading change */
    if (c >= 0.999f) { CM_ROT(m).y = CM_MROT(m).y; CM(u8, 0x9a, m) |= 0x80; return; }
    int side;
    if (mode < 4) { float a = CM_ROT(m).y, b = CM_MROT(m).y; if (a < 0) a += 6.283184f; if (b < 0) b += 6.283184f; float d = b - a;
                    float lim = d < 0 ? -3.141592f : 3.141592f; side = (lim < d) + 2;                      /* 2 = left, 3 = right */
                    CM(u8, 0x96, m) = (CM(u8, 0x96, m) & 0x9f) | ((lim < d) << 5); CM_GAIT(m) = (CM_GAIT(m) & 0xfc) | (mode & 1); }
    else { side = (mode & 1) + 2; CM(u8, 0x96, m) = (CM(u8, 0x96, m) & 0x9f) | (side << 5); CM_GAIT(m) = (CM_GAIT(m) & 0xfc) | ((mode >> 1) & 1); }   /* RETAIL: 2-bit side field at +0x96 b5-6 */
    if ((CM_GAIT(m) & 3) == 0 || CM_MROT(m).y == CM_ROT(m).y) return;
    CM_GAIT(m) = (CM_GAIT(m) & 0xfc) | 2; CM(u8, 0x96, m) = (CM(u8, 0x96, m) & 0xe7) | 8; CM(u8, 0x9a, m) &= 0x7f;
    int motion = -1;
    if (side == 2 && FindMotionData(m, GetMotionName(0x2a))) motion = c < 0.5f ? 0x2a : 0;
    if (side == 3 && FindMotionData(m, GetMotionName(0x29))) motion = c < 0.5f ? 0x29 : 0;
    if (motion < 1) { if (motion == 0) CM(float, 0x314, m) *= (c * 0.5f + 1.0f);          /* RETAIL (JP: /= (2 - c)) */
                      CFieldModel_PlayMoveMotion(m, 1); }
    else { CFieldModel_ResetMotion(m); CM(u8, 0x91, m) |= 0x20; CFieldModel_SetMotion(m, motion); CM_GAIT(m) |= 3;
           float y = CM_ROT(m).y; if (y < 0) y += 6.283184f; CM(float, 0x154, m) = y; CM(u8, 0x96, m) &= 0xe7; CM(float, 0x15c, m) = 0; }
}

/* RETAIL US 0x00510d40 Retail_CFieldModel_SightTest(self, target, sight, trilist) -> -2 out of cone, -1 blocked, else cone value */
int Retail_CFieldModel_SightTest(CFieldModel *self, const FVector *target, int sight, const u8 *trilist) {
    FVector p = CFieldModel_GetWorldPos(self), v = *target - p; v.y = 0; Normalize(&v);
    FVector face = {-sinf(CM_MROT(self).y), 0, -cosf(CM_MROT(self).y), 1};
    int cone = (int)((1.0f - dot3(face, v)) * 90.0f); if (cone > 0xb4) cone = 0xb4;
    if (cone > sight) return -2;
    float seg[4] = {p.x, p.z, target->x, target->z};
    const u16 *tri = (const u16 *)(trilist + *(s32 *)(trilist + 8)); const u8 *verts = trilist + *(s32 *)(trilist + 0xc);   /* verts: 3 x s16, 1/16 units */
    for (u16 i = 0, n = *(u16 *)(trilist + 4); i < n; i++, tri += 3) {
        FVector a = GetShortPos(verts + tri[0] * 6), b = GetShortPos(verts + tri[1] * 6), c = GetShortPos(verts + tri[2] * 6);
        if (Retail_TriSegIntersectXZ(a, b, c, seg)) return -1;
    }
    return cone;
}

/* RETAIL US 0x0050ac70 / 0x0050acf0 / 0x0050aa80: hide the model for shop / tailor / menus and restore it afterwards. State: CM(u8,0x92) bits 4-7. */
void Retail_CFieldModel_SuspendForMenu(CFieldModel *m) {
    if ((CM(u8, 0x92, m) >> 6) == 3 && ((CM(u8, 0x92, m) & 0x3f) >> 4) == 0) {
        CM(u8, 0x92, m) = (CM(u8, 0x92, m) & 0xcf) | 0x10;  CM(int, 0xb0, m) = Model_GetMotionTime(CM(void *, 0x80, m), 0);
        CM(FVector, 0x70, m) = CM_POS(m); } }          /* position backup */
void Retail_CFieldModel_ResumeAfterMenu(CFieldModel *m) {
    if (((CM(u8, 0x92, m) & 0x3f) >> 4) == 1) { CM(u8, 0x92, m) = (CM(u8, 0x92, m) & 0xcf) | 0x20; CM_POS(m) = CM(FVector, 0x70, m); } }
