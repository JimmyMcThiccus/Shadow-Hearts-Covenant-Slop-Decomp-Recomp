/* CFieldCamera / CField camera path - retail (US). JP reference: ../G/CFieldCamera.c, notes/G_retail/CFieldCamera.md */
#include "_types_retail.h"

/* US 0x00506250 CFieldCamera::Init (JP 0x004be2c0): default pose; the fov default 0.625 (=320/512), compose length 50 (0x42480000 at +0x18),
 * camera (0,0,-100). Returns true on first init. */
int CFieldCamera_Init(CFieldCamera *c) {
    RF(u16, 6, c) = 0; CC_FLAGS(c) |= 1; CC_FLAGS(c) = (CC_FLAGS(c) & 0xfb) | 4;
    CC_COMP_LEN(c) = 50.0f; CC_DELAY(c) = 0;
    CC_POS_OFS(c) = (FVector){0, 0, 0, 1};  CC_ANG_OFS(c) = (FVector){0, 0, 0, 1};      /* retail only */
    if (CC_GSX(c) == 0) {
        CC_TARGET(c) = (FVector){0, 0, 0, 1}; CC_CAM(c) = (FVector){0, 0, -100.0f, 1};
        CC_FOV(c) = 0.625f; CC_GSX(c) = camera__4CApp;  CFieldCamera_Apply(c, 0);
        return 1;
    }
    return 0;
}

/* US 0x00506420 CFieldCamera::Apply(dt): chase (view delay), transition blend, then the look-at angles and the SetViewMatrix call. */
void CFieldCamera_Apply(CFieldCamera *c, float dt) {
    if (!CC_GSX(c)) CC_GSX(c) = camera__4CApp;
    if (!CC_GSX(c) || !(CC_FLAGS(c) & 1)) return;
    FVector cam = CC_CAM(c), tgt = CC_TARGET(c);
    if (CC_DELAY(c) > 0) {                                   /* exponential chase of the goal (+0x90) */
        FVector d = goal_target - tgt; float l = Length(d), k = clamp(l * l, 0.2f, 10.0f);
        float step = k * dt / CC_DELAY(c); if (step > l) step = l;
        CC_TARGET(c) = tgt = tgt + Normalize(d) * step;
        float da = goal_fov - CC_FOV(c), s = 1; if (da < 0) { da = -da; s = -1; }
        float sf = max(da * da, 0.1f) * dt / CC_DELAY(c); if (sf > da) sf = da; CC_FOV(c) += sf * s;
    }
    if (CC_FLAGS(c) & 4) {                                   /* compose / transition */
        float fov = CC_FOV(c);
        if (CC_COMP_TIME(c) > 0) {
            CC_COMP_TIME(c) = max(CC_COMP_TIME(c) - dt, 0.0f);
            float f = CC_COMP_TIME(c) / CC_COMP_LEN(c), e;
            if (CC_FLAGS(c) & 8) { e = f >= 0.4f ? (f - 0.4f) * 1.1666666f + 0.3f : (f / 0.4f) * (f / 0.4f) * 0.3f;
                                   e = (atanf((e - 0.5f) * 3.141592f) + 1) * 0.5f; e = clamp(e, 0, 1); }
            else if (f <= 0) { CC_COMP_TIME(c) = 0; e = 0; }
            else e = f > 0.5f ? 1 - (1 - f) * (1 - f) * 2 : f * f * 2;
            tgt = tgt - (tgt - CC_FROM_TARGET(c)) * e; cam = cam - (cam - CC_FROM_CAM(c)) * e; tgt.w = cam.w = 1;
            fov -= e * (CC_FOV(c) - CC_FOV_PREV(c));
        }
        CC_FINAL_TARGET(c) = tgt; CC_FINAL_CAM(c) = cam; CC_FOV_FINAL(c) = fov;
    }
    cam = CC_FINAL_CAM(c) + CC_POS_OFS(c);                    /* RETAIL: camera FX position offset */
    if (!(CC_FLAGS(c) & 2)) {                                 /* derive yaw/pitch from the look-at */
        FVector d = CC_FINAL_CAM(c) - CC_FINAL_TARGET(c);
        float yaw = atan2f(d.x, d.z);  CC_YAW(c) = yaw * 57.29579f + 180;
        FVector r = RotY(-yaw, d);     CC_PITCH(c) = atan2f(-r.y, -r.z) * 57.29579f + 180;
    }
    CC_ROLL(c) = RF(float, 0x10, c);  RF(float, 0xcc, c) = 1.0f;
    Matrix m = Unit();                                        /* RETAIL: pitch/roll offsets added before building the matrix */
    RotZ(&m, GetRad(CC_ROLL(c)) + CC_ANG_OFS(c).z);
    RotX(&m, GetRad(CC_PITCH(c)) + CC_ANG_OFS(c).x);
    RotY(&m, GetRad(CC_YAW(c)));
    m.col[3] = cam; GsxCamera_SetMatrix(CC_GSX(c), &m);
    GsxCamera_SetViewMatrix(CC_GSX(c), 320.0f / CC_FOV_FINAL(c), 0.8f, 0.93333f, 1.0f, 16777000.0f);
}

/* US 0x00506390 SetTargetPos: with a view delay the goal (+0x90) is moved, otherwise the target itself. */
void CFieldCamera_SetTargetPos(CFieldCamera *c, FVector p) { if (CC_DELAY(c) > 0) RF(FVector, 0x90, c) = p; else CC_TARGET(c) = p; }
/* US 0x00506bb0 CompFrame(len, cam): start a transition from the last composed pose. */
void CFieldCamera_CompFrame(float len, CFieldCamera *c) { CC_FROM_TARGET(c) = CC_FINAL_TARGET(c); CC_FROM_CAM(c) = CC_FINAL_CAM(c);
    CC_FOV_PREV(c) = CC_FOV_FINAL(c); CC_COMP_LEN(c) = len; CC_COMP_TIME(c) = len; }
/* US 0x00506bf0 Retail_CFieldCamera_CompSnap: like CompFrame from the *uncomposed* pose and cancel the running transition. */
void CFieldCamera_CompSnap(CFieldCamera *c) { CC_FROM_TARGET(c) = CC_TARGET(c); CC_FROM_CAM(c) = CC_CAM(c); CC_COMP_TIME(c) = 0; }

/* ---------------------------------------------------------------------------------------------------------------------------
 * Rail camera (CAMERA kind 5, rounded-corner mode) - identical in both builds; ported to Rust in sh2_field::camera.
 * node (0x40 bytes): +0x00 camera FVector, +0x10 target FVector, +0x20 u16 fov (0 = 320), +0x30 path vertex p, +0x3c u32 flags (bit0 sharp corner,
 * node 0 bit1 = rounded mode; the float 2.0 marks a spline break). */

/* US 0x00504a40 FldSpline::GetPosition(t): cubic uniform B-spline, accumulator starts at (0,0,0,1) so lane w = 1 + sum(basis*w). */
FVector FldSpline_GetPosition(const FldSpline *s, float t) {
    FVector acc = {0, 0, 0, 1};
    if (!FldSpline_isCreated(s)) return acc;
    if (s->count == 1) return s->pts[0];
    if (s->count == 2) { t = clamp(t, 0, 1); return s->pts[0] * (1 - t) + s->pts[1] * t; }
    t = clamp(t, 0, (float)s->count);
    for (int i = max((int)(t - 2), -2); i <= min((int)(t + 2), s->count + 2); i++) {
        const FVector *p = i < 0 ? &s->pts[0] : (i >= s->count ? &s->pts[s->count - 1] : &s->pts[i]);
        float x = fabsf(t - i), b = x < 1 ? x * x * x * 0.5f - x * x + 0.6666667f : (x < 2 ? (x - 2) * -(x - 2) * (x - 2) / 6.0f : 0);
        acc = acc + *p * b;
    }
    return acc;
}

/* US 0x005028b0 GetNearestPath(blob, pos, &seg): all vectors below have y = 0 (plan view) except the nearest-vertex search. Returns 1000+node for sharp
 * nodes, else the fraction on segment seg. See sh2_field::camera::get_nearest_path for the line-by-line port (fillet size 5%..50% of the shorter leg). */
float GetNearestPath(const SDB_tagFCAMERA *cam, FVector *pos, int *seg);
/* US 0x005039c0 GetCamPathA(t, seg, out[2]): spline run [start,end) bounded by nodes whose +0x3c word == 2.0f; out[0] = target spline, out[1] = camera spline (w = 1 + fov). */
int GetCamPathA(float t, CField *f, int seg, FVector out[2]);
/* US 0x00503df0 GetCamPath2(f, out[2], node, pos): blend of the cameras of segments node-1 and node weighted by the player's position along each leg: A0 = T2 + (T1-T2)*2*f0,
 * B0 = T1 + (T2-T1)*2*f1, result (A0+B0)/2; camera w = 320. */
int GetCamPath2(CField *f, FVector out[2], int node, FVector pos);
