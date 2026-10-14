/* ==== CLEANED (port: sh2_field/src/camera.rs) ==== */
#include "_types.h"
/* JP 0x004be2c0 CFieldCamera::Init */
int CFieldCamera_Init(CFieldCamera *this) {
    this->flags = 0; this->flags |= 1; this->flags |= 4;            /* enabled | compose */
    this->comp_len = 50.0f; this->view_delay = 0.0f;
    if (this->gsx) return 0;
    this->target = (FVector){0, 0, 0, 1}; this->cam_pos = (FVector){0, 0, -100.0f, 1};
    this->view_angle = 0.625f; this->gsx = camera__4CApp;
    CFieldCamera_Apply(this, 0.0f);
    return 1;
}
/* JP 0x004bef20 CFieldCamera::CompFrame(float len): start a transition from the last composed pose */
void CFieldCamera_CompFrame(CFieldCamera *this, float len) {
    this->from_target = this->final_target; this->from_cam = this->final_cam; this->prev_view_angle = this->final_angle;
    this->comp_len = len; this->comp_time = len;
}
/* JP 0x004be450/0x004be4c0/0x004aa5e0 setters: while view_delay > 0 the goal copies (+0x90/+0xa0) are written instead */
void CFieldCamera_SetTargetPos(CFieldCamera *t, FVector p) { if (t->view_delay > 0) t->goal_target = p; else t->target = p; }
void CFieldCamera_SetViewAngle(CFieldCamera *t, float a) { if (a == 0) a = 0.625f; if (t->view_delay > 0) t->goal_angle = a; else t->view_angle = a; }

/* JP 0x004be540 CFieldCamera::Apply(float dt) */
void CFieldCamera_Apply(CFieldCamera *this, float dt) {
    if ((!this->gsx && !(this->gsx = camera__4CApp)) || !(this->flags & 1)) return;
    FVector cam = this->cam_pos, tgt = this->target;
    if (this->view_delay > 0) {                                                    /* chase the goals */
        FVector diff = this->goal_target - this->target; float len = Length(diff), k = len * len;
        k = k < 0.2f ? 0.2f : (k > 10.0f ? 10.0f : k);
        float step = k * dt / this->view_delay; if (len < step) step = len;
        this->target += Normalize(diff) * step; tgt = this->target;
        float da = this->goal_angle - this->view_angle, sg = 1; if (da < 0) { da = -da; sg = -1; }
        float s = da * da; if (s < 0.1f) s = 0.1f; s = s * dt / this->view_delay; if (da < s) s = da;
        this->view_angle += s * sg;
    }
    if (this->flags & 4) {                                                         /* compose */
        float fov = this->view_angle;
        if (this->comp_time > 0) {
            this->comp_time -= dt; if (this->comp_time < 0) this->comp_time = 0;
            float f = this->comp_time * (1.0f / this->comp_len), s;
            if (this->flags & 8) { s = f >= 0.4f ? (f - 0.4f) * 1.1666666f + 0.3f : (f / 0.4f) * (f / 0.4f) * 0.3f;
                                   s = (atanf((s - 0.5f) * 3.141592f) + 1.0f) * 0.5f; if (s < 0) s = 0; if (s > 1) s = 1; }
            else if (f <= 0) { s = 0; this->comp_time = 0; }
            else s = f > 0.5f ? 1.0f - (1.0f - f) * (1.0f - f) * 2.0f : f * f * 2.0f;
            tgt = tgt - (tgt - this->from_target) * s; cam = cam - (cam - this->from_cam) * s; tgt.w = cam.w = 1;
            fov -= s * (this->view_angle - this->prev_view_angle);
        }
        this->final_target = tgt; this->final_cam = cam; this->final_angle = fov;
    }
    if (!(this->flags & 2)) {                                                      /* derive yaw/pitch from the look-at */
        FVector d = this->final_cam - this->final_target; float yaw = atan2f(d.x, d.z);
        this->yaw_deg = yaw * 57.29579f + 180.0f;
        FVector r = RotY(-yaw, d); this->pitch_deg = atan2f(-r.y, -r.z) * 57.29579f + 180.0f;
        this->roll_deg = this->roll; this->one = 1.0f;
    }
    Matrix *m = &this->gsx->frame_matrix;                                          /* GsxCamera+0x240 */
    UnitMatrix(m); RotZMatrix(m, GetRad(this->roll_deg)); RotXMatrix(m, GetRad(this->pitch_deg)); RotYMatrix(m, GetRad(this->yaw_deg));
    TransMatrix(m, &this->final_cam);
    GsxCamera_ApplyFrame(this->gsx);
    GsxCamera_SetViewMatrix(this->gsx, 320.0f / this->final_angle, 0.8f, 0.9333f, 1.0f, 16777000.0f);
}


/* ==== RAW (Ghidra output, names/globals resolved; not hand-cleaned) ==== */
/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CFieldCamera   functions: 15
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CFieldCamera.md).
 */

/* JP: 0x004a34a0  CFieldCamera::SetViewDelay(float)   [SetViewDelay__12CFieldCameraFf]  size=0x24 */
void SetViewDelay__12CFieldCameraFf(CFieldCamera *this,float a0)

{
  this->flView_delay = a0;
  return;
}

/* JP: 0x004a3960  CFieldCamera::CompClear()   [CompClear__12CFieldCameraFv]  size=0x20 */
void CompClear__12CFieldCameraFv(CFieldCamera *this)

{
  this->flComp_time = 0.0;
  return;
}

/* JP: 0x004a82a0  CFieldCamera::GetCameraAngle()   [GetCameraAngle__12CFieldCameraFv]  size=0x34 */
void GetCameraAngle__12CFieldCameraFv(CFieldCamera *this)

{
  int in_a1_lo;
  
  __ct__7FVectorFRC7FVector(this,in_a1_lo + 0xc0);
  return;
}

/* JP: 0x004a89b0  CFieldCamera::GetCameraPos()   [GetCameraPos__12CFieldCameraFv]  size=0x34 */
void GetCameraPos__12CFieldCameraFv(CFieldCamera *this)

{
  int in_a1_lo;
  
  __ct__7FVectorFRC7FVector(this,in_a1_lo + 0x40);
  return;
}

/* JP: 0x004aa5e0  CFieldCamera::SetCameraPos(FVector)   [SetCameraPos__12CFieldCameraF7FVector]  size=0x34 */
void SetCameraPos__12CFieldCameraF7FVector(CFieldCamera *this,FVector *a0)

{
  __as__7FVectorFRC7FVector(&this->cam_pos,a0);
  return;
}

/* JP: 0x004aa620  CFieldCamera::GetTargetPos()   [GetTargetPos__12CFieldCameraFv]  size=0x34 */
void GetTargetPos__12CFieldCameraFv(CFieldCamera *this)

{
  int in_a1_lo;
  
  __ct__7FVectorFRC7FVector(this,in_a1_lo + 0x30);
  return;
}

/* JP: 0x004aa710  CFieldCamera::bComp()   [bComp__12CFieldCameraFv]  size=0x38 */
bool bComp__12CFieldCameraFv(CFieldCamera *this)

{
  return this->flComp_time != 0.0;
}

/* JP: 0x004ab820  CFieldCamera::SetCmpMode(int)   [SetCmpMode__12CFieldCameraFi]  size=0x40 */
void SetCmpMode__12CFieldCameraFi(CFieldCamera *this,int a0)

{
  this->bFlags = this->bFlags & 0xf7 | (byte)((a0 & 1U) << 3);
  return;
}

/* JP: 0x004be190  CFieldCamera::CFieldCamera()   [__ct__12CFieldCameraFv]  size=0xc4 */
undefined4 * __ct__12CFieldCameraFv(CFieldCamera *this)

{
  __ct__7FVectorFv(&this->target);
  __ct__7FVectorFv(&this->cam_pos);
  __ct__7FVectorFv(&this->from_target);
  __ct__7FVectorFv(&this->from_cam);
  __ct__7FVectorFv(&this->final_target);
  __ct__7FVectorFv(&this->final_cam);
  __ct__7FVectorFv(&this->goal_target);
  __ct__7FVectorFv(&this->vec_b0);
  __ct__7FVectorFv(&this->flPitch_deg);
  this->flComp_time = 0.0;
  this->pGsx_camera = (void *)0x0;
  return &this->pGsx_camera;
}

/* JP: 0x004be260  CFieldCamera::~CFieldCamera()   [__dt__12CFieldCameraFv]  size=0x5c */
undefined4 * __dt__12CFieldCameraFv(CFieldCamera *this,short flag)

{
  if ((this != (CFieldCamera *)0x0) && (this->pGsx_camera = (void *)0x0, 0 < flag)) {
    __dl__FPv(this);
  }
  return &this->pGsx_camera;
}

/* JP: 0x004be2c0  CFieldCamera::Init()   [Init__12CFieldCameraFv]  size=0x170 */
bool Init__12CFieldCameraFv(CFieldCamera *this)

{
  bool bVar1;
  undefined8 uVar2;
  undefined1 auStack_30 [16];
  undefined1 auStack_20 [16];
  CFieldCamera *pCStack_10;
  
  pCStack_10 = this;
  clear__Q212CFieldCamera6_flagsFv(&this->bFlags);
  pCStack_10->bFlags = pCStack_10->bFlags & 0xfe | 1;
  pCStack_10->bFlags = pCStack_10->bFlags & 0xfb | 4;
  pCStack_10->flComp_len = 50.0;
  pCStack_10->flView_delay = 0.0;
  bVar1 = pCStack_10->pGsx_camera == (void *)0x0;
  if (bVar1) {
    uVar2 = __ct__7FVectorFffff(0,0,0,0x3f800000,auStack_20);
    __as__7FVectorFRC7FVector(&pCStack_10->target,uVar2);
    uVar2 = __ct__7FVectorFffff(0,0,0xc2c80000,0x3f800000,auStack_30);
    __as__7FVectorFRC7FVector(&pCStack_10->cam_pos,uVar2);
    pCStack_10->flView_angle = 0.625;
    *(undefined4 *)&pCStack_10->field_0x8 = 0;
    *(undefined4 *)&pCStack_10->field_0xc = 0;
    pCStack_10->flRoll = 0.0;
    pCStack_10->pGsx_camera = camera__4CApp;
    Apply__12CFieldCameraFf(pCStack_10,0.0);
  }
  return bVar1;
}

/* JP: 0x004be450  CFieldCamera::SetTargetPos(FVector)   [SetTargetPos__12CFieldCameraF7FVector]  size=0x70 */
void SetTargetPos__12CFieldCameraF7FVector(CFieldCamera *this,FVector *a0)

{
  if (0.0 < this->flView_delay) {
    __as__7FVectorFRC7FVector(&this->goal_target,a0);
  }
  else {
    __as__7FVectorFRC7FVector(&this->target,a0);
  }
  return;
}

/* JP: 0x004be4c0  CFieldCamera::SetViewAngle(float)   [SetViewAngle__12CFieldCameraFf]  size=0x7c */
void SetViewAngle__12CFieldCameraFf(CFieldCamera *this,float a0)

{
  float fStack_10;
  
  fStack_10 = a0;
  if (a0 == 0.0) {
    fStack_10 = 0.625;
  }
  if (0.0 < this->flView_delay) {
    this->flGoal_angle = fStack_10;
  }
  else {
    this->flView_angle = fStack_10;
  }
  return;
}

/* JP: 0x004be540  CFieldCamera::Apply(float)   [Apply__12CFieldCameraFf]  size=0x978 */
void Apply__12CFieldCameraFf(CFieldCamera *this,float a0)

{
  float fVar1;
  undefined4 uVar2;
  undefined1 auStack_170 [16];
  undefined1 auStack_160 [16];
  undefined1 auStack_150 [16];
  undefined1 auStack_140 [16];
  undefined1 auStack_130 [16];
  undefined1 auStack_120 [16];
  undefined1 auStack_110 [16];
  undefined1 auStack_100 [64];
  undefined1 auStack_c0 [4];
  float fStack_bc;
  float fStack_b8;
  undefined4 auStack_b0 [2];
  undefined4 uStack_a8;
  undefined1 auStack_a0 [16];
  undefined1 auStack_90 [16];
  undefined1 auStack_80 [16];
  undefined1 auStack_70 [12];
  undefined4 uStack_64;
  undefined1 auStack_60 [12];
  undefined4 uStack_54;
  undefined1 auStack_50 [20];
  float fStack_3c;
  float fStack_38;
  float fStack_34;
  float fStack_30;
  float fStack_2c;
  float fStack_28;
  float fStack_24;
  CFieldCamera *pCStack_20;
  float fStack_10;
  
  if (((this->pGsx_camera != (void *)0x0) ||
      (this->pGsx_camera = camera__4CApp, this->pGsx_camera != (void *)0x0)) &&
     ((this->bFlags & 1) != 0)) {
    pCStack_20 = this;
    fStack_10 = a0;
    __ct__7FVectorFv(auStack_50);
    __ct__7FVectorFv(auStack_60);
    __ct__7FVectorFv(auStack_70);
    __as__7FVectorFRC7FVector(auStack_60,&pCStack_20->cam_pos);
    __as__7FVectorFRC7FVector(auStack_70,&pCStack_20->target);
    if (0.0 < pCStack_20->flView_delay) {
      __mi__7FVectorCFRC7FVector(auStack_80,&pCStack_20->goal_target,&pCStack_20->target);
      fStack_24 = (float)Length__7FVectorCFv(auStack_80);
      fStack_28 = fStack_24 * fStack_24;
      if (fStack_28 < 0.2) {
        fStack_28 = 0.2;
      }
      if (10.0 < fStack_28) {
        fStack_28 = 10.0;
      }
      fVar1 = (fStack_28 * fStack_10) / pCStack_20->flView_delay;
      fStack_28 = fStack_24;
      if (fVar1 <= fStack_24) {
        fStack_28 = fVar1;
      }
      Normalize__7FVectorFv(auStack_80);
      __ml__7FVectorCFf(fStack_28,auStack_110,auStack_80);
      __apl__7FVectorFRC7FVector(&pCStack_20->target,auStack_110);
      fStack_24 = pCStack_20->flGoal_angle - pCStack_20->flView_angle;
      fStack_2c = 1.0;
      if (fStack_24 < 0.0) {
        fStack_24 = -fStack_24;
        fStack_2c = -1.0;
      }
      fStack_28 = fStack_24 * fStack_24;
      if (fStack_28 < 0.1) {
        fStack_28 = 0.1;
      }
      fStack_28 = (fStack_28 * fStack_10) / pCStack_20->flView_delay;
      if (fStack_24 < fStack_28) {
        fStack_28 = fStack_24;
      }
      pCStack_20->flView_angle = pCStack_20->flView_angle + fStack_28 * fStack_2c;
    }
    if ((long)((ulong)pCStack_20->bFlags << 0x3d) < 0) {
      __ct__7FVectorFv(auStack_90);
      __ct__7FVectorFv(auStack_a0);
      fStack_30 = pCStack_20->flView_angle;
      if (0.0 < pCStack_20->flComp_time) {
        pCStack_20->flComp_time = pCStack_20->flComp_time - fStack_10;
        if (pCStack_20->flComp_time < 0.0) {
          pCStack_20->flComp_time = 0.0;
        }
        if ((long)((ulong)pCStack_20->bFlags << 0x3c) < 0) {
          fVar1 = pCStack_20->flComp_time * (1.0 / pCStack_20->flComp_len);
          if (0.4 <= fVar1) {
            fStack_34 = (fVar1 - 0.4) * 1.1666666 + 0.3;
          }
          else {
            fStack_34 = (fVar1 / 0.4) * (fVar1 / 0.4) * 0.3;
          }
          fStack_34 = (fStack_34 - 0.5) * 3.141592;
          fVar1 = (float)atanf(fStack_34);
          fStack_34 = (fVar1 + 1.0) * 0.5;
          if (fStack_34 < 0.0) {
            fStack_34 = 0.0;
          }
          else if (1.0 < fStack_34) {
            fStack_34 = 1.0;
          }
        }
        else {
          fVar1 = pCStack_20->flComp_time * (1.0 / pCStack_20->flComp_len);
          if (fVar1 <= 0.0) {
            fStack_34 = 0.0;
            pCStack_20->flComp_time = 0.0;
          }
          else if (0.5 < fVar1) {
            fStack_34 = 1.0 - (1.0 - fVar1) * (1.0 - fVar1) * 2.0;
          }
          else {
            fStack_34 = fVar1 * fVar1 * 2.0;
          }
        }
        __mi__7FVectorCFRC7FVector(auStack_120,&pCStack_20->target,&pCStack_20->from_target);
        __as__7FVectorFRC7FVector(auStack_90,auStack_120);
        __ml__7FVectorCFf(fStack_34,auStack_130,auStack_90);
        __ami__7FVectorFRC7FVector(auStack_70,auStack_130);
        __mi__7FVectorCFRC7FVector(auStack_140,&pCStack_20->cam_pos,&pCStack_20->from_cam);
        __as__7FVectorFRC7FVector(auStack_90,auStack_140);
        __ml__7FVectorCFf(fStack_34,auStack_150,auStack_90);
        __ami__7FVectorFRC7FVector(auStack_60,auStack_150);
        fStack_30 = fStack_30 -
                    fStack_34 * (pCStack_20->flView_angle - pCStack_20->flPrev_view_angle);
        uStack_64 = 0x3f800000;
        uStack_54 = 0x3f800000;
      }
      __as__7FVectorFRC7FVector(&pCStack_20->final_target,auStack_70);
      __as__7FVectorFRC7FVector(&pCStack_20->final_cam,auStack_60);
      pCStack_20->flFinal_angle = fStack_30;
    }
    if (-1 < (long)((ulong)pCStack_20->bFlags << 0x3e)) {
      __ct__7FVectorFv(auStack_b0);
      __ct__7FVectorFv(auStack_c0);
      __mi__7FVectorCFRC7FVector(auStack_160,auStack_60,auStack_70);
      __as__7FVectorFRC7FVector(auStack_b0,auStack_160);
      fStack_38 = (float)atan2f(auStack_b0[0],uStack_a8);
      pCStack_20->flYaw_deg = fStack_38 * 57.29579 + 180.0;
      __ct__6MatrixFv(auStack_100);
      UnitMatrix__6MatrixFv(auStack_100);
      RotYMatrix__6MatrixFf(-fStack_38,auStack_100);
      ApplyMatrix__6MatrixCFRC7FVector(auStack_170,auStack_100,auStack_b0);
      __as__7FVectorFRC7FVector(auStack_c0,auStack_170);
      fStack_38 = (float)atan2f(-fStack_bc,-fStack_b8);
      pCStack_20->flPitch_deg = fStack_38 * 57.29579 + 180.0;
      pCStack_20->flRoll_deg = pCStack_20->flRoll;
      pCStack_20->flOne = 1.0;
    }
    UnitMatrix__6MatrixFv((int)pCStack_20->pGsx_camera + 0x240);
    uVar2 = GetRad(pCStack_20->flRoll_deg);
    RotZMatrix__6MatrixFf(uVar2,(int)pCStack_20->pGsx_camera + 0x240);
    uVar2 = GetRad(pCStack_20->flPitch_deg);
    RotXMatrix__6MatrixFf(uVar2,(int)pCStack_20->pGsx_camera + 0x240);
    uVar2 = GetRad(pCStack_20->flYaw_deg);
    RotYMatrix__6MatrixFf(uVar2,(int)pCStack_20->pGsx_camera + 0x240);
    TransMatrix__6MatrixFRC7FVector((int)pCStack_20->pGsx_camera + 0x240,auStack_60);
    ApplyFrame__9GsxCameraFv(pCStack_20->pGsx_camera);
    fStack_3c = 320.0 / pCStack_20->flFinal_angle;
    SetViewMatrix__9GsxCameraFfffff(fStack_3c,0x3f4ccccd,0x3f6eeeef,0x3f800000,0x4b7fff28,pCStack_20->pGsx_camera);
  }
  return;
}

/* JP: 0x004bef20  CFieldCamera::CompFrame(float)   [CompFrame__12CFieldCameraFf]  size=0x74 */
void CompFrame__12CFieldCameraFf(CFieldCamera *this,float a0)

{
  __as__7FVectorFRC7FVector(&this->from_target,&this->final_target);
  __as__7FVectorFRC7FVector(&this->from_cam,&this->final_cam);
  this->flPrev_view_angle = this->flFinal_angle;
  this->flComp_len = a0;
  this->flComp_time = a0;
  return;
}
