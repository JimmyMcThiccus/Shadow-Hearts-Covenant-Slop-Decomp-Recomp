/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x00270370  __ct__6CursorFv  size 0x70
// Cursor::Cursor()
int __ct__6CursorFv(Cursor *this)
{
  __ct__7MenuObjFv(this);
  this->vptr = __vt__6Cursor;
  __ct__11MenuPolygonFv(this + 0x1c);
  __ct__11SendOnLocalFv(this + 0xa0);
  VCALL(this, 0x20 /*Clear*/)();
  return this;
}

// JP: 0x002703e0  __dt__6CursorFv  size 0xac
// Cursor::~Cursor()
int __dt__6CursorFv(Cursor *this,short param_2)
{
  if (this != 0) {
    this->vptr = __vt__6Cursor;
    VCALL(this, 0x1c /*Destroy*/)();
    __dt__11SendOnLocalFv(this + 0xa0,0xffffffffffffffff);
    __dt__11MenuPolygonFv(this + 0x1c,0xffffffffffffffff);
    __dt__7MenuObjFv(this,0);
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}

// JP: 0x00270490  Create__6CursorFUcUcUcUc  size 0x10c
// Cursor::Create(unsigned char, unsigned char, unsigned char, unsigned char)
void Create__6CursorFUcUcUcUc
               (Cursor *this,u8 param_2,u8 param_3,u8 param_4,
               u8 param_5)
{
  SetType__6CursorFUc(this,param_2);
  SetShadow__6CursorFUc(this,param_3);
  SetDirection__6CursorFUcf(0x40000000,this,param_4);
  SetRotation__6CursorFUc(this,param_5);
  this->place = this->place;
  this->cflags2 =
       this->cflags2 & 0xfb |
       (u8)((uint)(((ulong)this->cflags2 << 0x3d) >> 0x3f) << 2);
  this->dirty0 = this->dirty0 | 0x3f;
  this->dirty1 = this->dirty1 | 0x3f;
  this->flags = this->flags & 0xef | 0x10;
  return;
}

// JP: 0x002705a0  SetBackObject__6CursorFUc  size 0x158
// Cursor::SetBackObject(unsigned char)
void SetBackObject__6CursorFUc(Cursor *this,char param_2)
{
  int iVar1;
  u32 uVar2;
  long lVar3;
  ulong uVar4;
  if (param_2 == '\0') {
    if (this->back != 0) {
      VCALL(this->back, 0xc /*DelayDelete*/)();
      this->back = 0;
    }
  }
  else if (this->back == 0) {
    lVar3 = __nw__FUi(0x60);
    uVar2 = 0;
    if (lVar3 != 0) {
      uVar2 = __ct__10MenuSpriteFv(lVar3);
    }
    this->back = uVar2;
    Create__10MenuSpriteFUc(this->back,1);
    iVar1 = this->back;
    *(u8 *)(iVar1 + 0x21) = *(u8 *)(iVar1 + 0x21) & 0xbf;
    uVar4 = (ulong)*(u8 *)(iVar1 + 0x11) & 0xfffffffffffffffd | 2;
    *(char *)(iVar1 + 0x11) = (char)uVar4;
    *(u8 *)(iVar1 + 0x10) =
         *(u8 *)(iVar1 + 0x10) & 0xfd | (u8)((uint)((uVar4 << 0x3e) >> 0x3f) << 1);
    VCALL(this->back, 0x30 /*SetColor*/)
              (this->back,0x80,0x80,0xff);
  }
  return;
}

// JP: 0x00270700  Select__6CursorFP9MenuPlace  size 0x1c4
// Cursor::Select(MenuPlace*)
void Select__6CursorFP9MenuPlace(Cursor *this,MenuPlace *menuPlace)
{
  int iVar1;
  long lVar2;
  iVar1 = menuPlace->owner;
  this->cflags2 = this->cflags2 & 0x7f;
  ConvertScreen__6CursorFPfPf(this,this->pos,this->pos + 4);
  if (iVar1 != 0) {
    *this->pos =
         *this->pos -
         (menuPlace->owner->x + menuPlace->owner->scroll_x);
    *(float *)(this->pos + 4) =
         *(float *)(this->pos + 4) -
         (menuPlace->owner->y + menuPlace->owner->scroll_y)
    ;
    lVar2 = Scroll__10MenuWindowFP9MenuPlace(iVar1,menuPlace);
    if (lVar2 != 0) {
      this->cflags2 = this->cflags2 & 0x7f | 0x80;
    }
  }
  IsSelected__9MenuPlaceFP6Cursor(menuPlace,this);
  return;
}

// JP: 0x002708d0  QuickMove__6CursorFv  size 0x48
// Cursor::QuickMove()
void QuickMove__6CursorFv(Cursor *this)
{
  *this->pos = this->target_x;
  *(u32 *)(this->pos + 4) = this->target_y;
  this->move_state = 1;
  return;
}

// JP: 0x00270920  Leave__6CursorFv  size 0xb0
// Cursor::Leave()
int Leave__6CursorFv(Cursor *this)
{
  int iVar1;
  iVar1 = this->place;
  if (iVar1 != 0) {
    ConvertScreen__6CursorFPfPf
              (this,this->pos,this->pos + 4);
    ConvertScreen__6CursorFPfPf(this,this + 0xe4,this + 0xe8);
    IsCanceled__9MenuPlaceFP6Cursor(this->place,this);
    this->place = 0;
  }
  this->cflags2 = this->cflags2 & 0x7f;
  return iVar1;
}

// JP: 0x002709d0  ClearAfter__6CursorFv  size 0x40
// Cursor::ClearAfter()
void ClearAfter__6CursorFv(Cursor *this)
{
  if (this->flare != 0) {
    ClearAfter__9MenuFlareFv(this->flare);
  }
  return;
}

// JP: 0x00270a10  MoveCursor__6CursorFi  size 0x16c
// Cursor::MoveCursor(int)
long MoveCursor__6CursorFi(Cursor *this,u32 param_2)
{
  u32 uVar1;
  long lVar2;
  long lVar3;
  if ((this->place == 0) && (this->place->owner == 0)) {
    lVar2 = 0;
  }
  else {
    uVar1 = this->place->owner;
    lVar2 = MovePlace__10MenuWindowFiss
                      (uVar1,param_2,this->place->col,
                       this->place->row);
    if (lVar2 != 0) {
      lVar3 = Scroll__10MenuWindowFP9MenuPlace(uVar1,lVar2);
      if (lVar3 != 0) {
        this->cflags2 = this->cflags2 & 0x7f | 0x80;
      }
      IsSelected__9MenuPlaceFP6Cursor(lVar2,this);
    }
  }
  return lVar2;
}

// JP: 0x00270b80  SkipCursor__6CursorFi  size 0x3ec
// Cursor::SkipCursor(int)
long SkipCursor__6CursorFi(Cursor *this,int param_2)
{
  short sVar1;
  short sVar2;
  int iVar3;
  short sVar4;
  short sVar5;
  long lVar6;
  long lVar7;
  short sVar8;
  short sVar9;
  short sVar10;
  short unaff_s4_lo;
  short sVar11;
  float fVar12;
  if ((this->place == 0) && (this->place->owner == 0)) {
    lVar6 = 0;
  }
  else {
    iVar3 = this->place->owner;
    sVar10 = 0;
    sVar8 = 0;
    sVar4 = *(short *)(*(int *)(iVar3 + 0x40) + 0x18) + -1;
    sVar5 = *(short *)(*(int *)(iVar3 + 0x40) + 0x1a) + -1;
    sVar1 = this->place->col;
    sVar2 = this->place->row;
    sVar9 = sVar8;
    sVar11 = sVar2;
    if (param_2 != 8) {
      if (param_2 == 4) {
        sVar4 = -sVar4;
      }
      else {
        sVar9 = sVar5;
        sVar4 = sVar10;
        sVar11 = sVar1;
        if ((param_2 != 2) && (sVar9 = sVar8, sVar11 = unaff_s4_lo, param_2 == 1)) {
          sVar9 = -sVar5;
          sVar11 = sVar1;
        }
      }
    }
    lVar6 = GetPlace__10MenuWindowFss(iVar3,sVar1 + sVar4,sVar2 + sVar9);
    if ((lVar6 == 0) || (-1 < (long)((ulong)*(u8 *)((int)lVar6 + 0x21) << 0x3e))) {
      lVar6 = GetCornerPlace__10MenuWindowFis(iVar3,param_2,sVar11);
      Scroll__10MenuWindowFP9MenuPlace(iVar3,lVar6);
    }
    else {
      fVar12 = (float)GetTargetX__10MenuWindowCFv(iVar3);
      sVar4 = sVar4 + (short)(int)(-fVar12 / *(float *)(*(int *)(iVar3 + 0x40) + 0x1c));
      if (sVar4 < 0) {
        sVar4 = 0;
      }
      fVar12 = (float)GetTargetY__10MenuWindowCFv(iVar3);
      sVar9 = sVar9 + (short)(int)(-fVar12 / *(float *)(*(int *)(iVar3 + 0x40) + 0x20));
      if (sVar9 < 0) {
        sVar9 = 0;
      }
      lVar7 = Scroll__10MenuWindowFss(iVar3,sVar4,sVar9);
      if (lVar7 != 0) {
        this->cflags2 = this->cflags2 & 0x7f | 0x80;
      }
    }
    if (lVar6 != 0) {
      IsSelected__9MenuPlaceFP6Cursor(lVar6,this);
    }
  }
  return lVar6;
}

// JP: 0x00270f70  SetTarget__6CursorFff  size 0x90
// Cursor::SetTarget(float, float)
void SetTarget__6CursorFff(float param_1,float param_2,int this)
{
  this->target_x = param_1 + this->off_x;
  this->target_y = param_2 + this->off_y;
  this->move_state = 5;
  if (this->sound != 0) {
    PlaySE__9MenuSoundFUiUcP8_SeParam(this->sound,0,0,0);
  }
  return;
}

// JP: 0x00271000  SetTarget__6CursorFP8DrawRect  size 0x4c
// Cursor::SetTarget(DrawRect*)
void SetTarget__6CursorFP8DrawRect(Cursor *this,u32 param_2)
{
  u32 uStack_28;
  u32 uStack_24;
  u32 uStack_20;
  u32 uStack_10;
  uStack_20 = this;
  uStack_10 = param_2;
  GetTarget__6CursorFP8DrawRectPfPf(this,param_2,&uStack_24,&uStack_28);
  SetTarget__6CursorFff(uStack_24,uStack_28,uStack_20);
  return;
}

// JP: 0x00271050  GetTarget__6CursorFP8DrawRectPfPf  size 0x1e4
// Cursor::GetTarget(DrawRect*, float*, float*)
void GetTarget__6CursorFP8DrawRectPfPf(Cursor *this,float *param_2,float *param_3,float *param_4)
{
  ulong uVar1;
  float fVar2;
  fVar2 = (float)(int)this->gap;
  uVar1 = ((ulong)this->cflags & 0x3ff) >> 6;
  if (uVar1 == 8) {
    *param_3 = *param_2 - fVar2;
    *param_4 = param_2[1] + param_2[3] / 2.0;
  }
  else if (uVar1 == 4) {
    *param_3 = fVar2 + *param_2 + param_2[2];
    *param_4 = param_2[1] + param_2[3] / 2.0;
  }
  else if (uVar1 == 2) {
    *param_3 = *param_2 + param_2[2] / 2.0;
    *param_4 = param_2[1] - fVar2;
  }
  else if (uVar1 == 1) {
    *param_3 = *param_2 + param_2[2] / 2.0;
    *param_4 = fVar2 + param_2[1] + param_2[3];
  }
  return;
}

// JP: 0x00271240  GetScreen__6CursorFPfPf  size 0x60
// Cursor::GetScreen(float*, float*)
void GetScreen__6CursorFPfPf(Cursor *this,u32 *param_2,u32 *param_3)
{
  *param_2 = *this->pos;
  *param_3 = *(u32 *)(this->pos + 4);
  ConvertScreen__6CursorFPfPf(this,param_2,param_3);
  return;
}

// JP: 0x002712a0  ConvertScreen__6CursorFPfPf  size 0x178
// Cursor::ConvertScreen(float*, float*)
void ConvertScreen__6CursorFPfPf(Cursor *this,float *param_2,float *param_3)
{
  if ((this->place != 0) && (this->place->owner != 0)) {
    *param_2 = *param_2 +
               this->place->owner->x +
               this->place->owner->scroll_x;
    *param_3 = *param_3 +
               this->place->owner->y +
               this->place->owner->scroll_y;
  }
  return;
}

// JP: 0x00271420  GetPoint__6CursorFPfPf  size 0x5c
// Cursor::GetPoint(float*, float*)
void GetPoint__6CursorFPfPf(Cursor *this,float *param_2,float *param_3)
{
  *param_2 = *this->pos - this->off_x;
  *param_3 = *(float *)(this->pos + 4) - this->off_y;
  return;
}

// JP: 0x00271480  Restore__6CursorFv  size 0x9c
// Cursor::Restore()
void Restore__6CursorFv(Cursor *this)
{
  if ((this->flags & 1) == 0) {
    this->cflags2 = this->cflags2 & 0xef | 0x10;
    this->flags = this->flags & 0xfe | 1;
    QuickMove__6CursorFv(this);
    ClearAfter__6CursorFv(this);
  }
  return;
}

// JP: 0x00271520  Shutdown__6CursorFv  size 0x64
// Cursor::Shutdown()
void Shutdown__6CursorFv(Cursor *this)
{
  this->cflags2 = this->cflags2 & 0xef;
  this->flags = this->flags & 0xfe;
  Leave__6CursorFv(this);
  return;
}

// JP: 0x00271590  SetType__6CursorFUc  size 0x19c
// Cursor::SetType(unsigned char)
/* WARNING: Removing unreachable block (ram,0x00271660) */
/* WARNING: Removing unreachable block (ram,0x002716b0) */
void SetType__6CursorFUc(Cursor *this,u8 param_2)
{
  int iVar1;
  iVar1 = (uint)param_2 * 0x40;
  Create__11MenuPolygonFUcUc(this + 0x1c,1,1);
  SetUV__11MenuPolygonFUsUsUsUs
            (this + 0x1c,1,1,**(short **)(&DAT_004217a8 + iVar1) + -1,
             *(short *)(*(int *)(&DAT_004217a8 + iVar1) + 2) + -1);
  *(float *)(this->pos + 8) = (float)**(u16 **)(&DAT_004217a8 + iVar1);
  *(float *)(this->pos + 0xc) =
       (float)*(u16 *)(*(int *)(&DAT_004217a8 + iVar1) + 2);
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi
            (this + 0xa0,iVar1 + 0x4217b0,*(u32 *)(&DAT_004217ac + iVar1),1,0);
  return;
}

// JP: 0x00271730  SetShadow__6CursorFUc  size 0x24c
// Cursor::SetShadow(unsigned char)
u32 SetShadow__6CursorFUc(Cursor *this,u8 param_2)
{
  bool bVar1;
  bool bVar2;
  u32 uVar3;
  long lVar4;
  if (param_2 == 1) {
    if (this->shadow == 0) {
      lVar4 = __nw__FUi(0x84);
      uVar3 = 0;
      if (lVar4 != 0) {
        uVar3 = __ct__11MenuPolygonFv(lVar4);
      }
      this->shadow = uVar3;
      Create__11MenuPolygonFUcUc(this->shadow,1,1);
      VCALL(this->shadow, 0x30 /*SetColor*/)(this->shadow,0,0,0);
    }
    memcpy(this->shadow->uv,this->f_9c /*void **/,0x10);
    bVar2 = false;
    bVar1 = true;
  }
  else if (param_2 == 2) {
    if (this->flare == 0) {
      lVar4 = __nw__FUi(900);
      uVar3 = 0;
      if (lVar4 != 0) {
        uVar3 = __ct__9MenuFlareFv(lVar4);
      }
      this->flare = uVar3;
      Create__9MenuFlareFv(this->flare);
    }
    SetFlareOffset__6CursorFv(this);
    bVar2 = true;
    bVar1 = false;
  }
  else {
    bVar2 = true;
    bVar1 = true;
  }
  if ((bVar1) && (this->flare != 0)) {
    VCALL(this->flare, 0xc /*DelayDelete*/)();
    this->flare = 0;
  }
  if ((bVar2) && (this->shadow != 0)) {
    VCALL(this->shadow, 0xc /*DelayDelete*/)();
    this->shadow = 0;
  }
  this->cflags = this->cflags & 0xe7 | (param_2 & 3) << 3;
  return 1;
}

// JP: 0x00271980  SetDirection__6CursorFUcf  size 0x18c
// Cursor::SetDirection(unsigned char, float)
void SetDirection__6CursorFUcf(Cursor *this,u8 param_2)
{
  if (param_2 == 8) {
    this->off_x = -*(float *)(this->pos + 8);
    this->off_y = -(*(float *)(this->pos + 0xc) * 0.5);
  }
  else if (param_2 == 4) {
    this->off_x = sm_fZero__7MenuObj;
    this->off_y = -(*(float *)(this->pos + 0xc) * 0.5);
  }
  else if (param_2 == 2) {
    this->off_x = -(*(float *)(this->pos + 0xc) * 0.5);
    this->off_y = -*(float *)(this->pos + 8);
  }
  else if (param_2 == 1) {
    this->off_x = -(*(float *)(this->pos + 0xc) * 0.5);
    this->off_y = sm_fZero__7MenuObj;
  }
  this->cflags = this->cflags & 0xfc3f | (param_2 & 0xf) << 6;
  SetFlareOffset__6CursorFv(this);
  return;
}

// JP: 0x00271b10  SetRotation__6CursorFUc  size 0x5c
// Cursor::SetRotation(unsigned char)
void SetRotation__6CursorFUc(Cursor *this,u8 param_2)
{
  this->cflags = this->cflags & 0xdf | (param_2 & 1) << 5;
  this->angle = sm_fZero__7MenuObj;
  SetVertex__6CursorFv(this);
  return;
}

// JP: 0x00271b70  SetVertex__6CursorFv  size 0x3f0
// Cursor::SetVertex()
void SetVertex__6CursorFv(Cursor *this)
{
  ulong uVar1;
  int iVar2;
  u8 in_vf0 [16];
  u8 auVar3 [16];
  u8 auVar4 [16];
  u8 auVar5 [16];
  u8 auStack_c0 [8];
  float fStack_b8;
  float fStack_b4;
  u8 auStack_b0 [8];
  u32 uStack_a8;
  u32 uStack_a4;
  float afStack_a0 [8];
  float fStack_80;
  float fStack_7c;
  float fStack_70;
  float fStack_6c;
  float fStack_60;
  float fStack_5c;
  u32 uStack_58;
  u32 uStack_54;
  u8 auStack_50 [16];
  u8 auStack_40 [16];
  u8 auStack_30 [16];
  u8 auStack_20 [16];
  float fStack_8;
  float fStack_4;
  auVar3 = _vmr32(in_vf0);
  auVar4 = _vmr32(auVar3);
  auVar5 = _vmr32(auVar4);
  _sqc2(in_vf0);
  _sqc2(auVar3);
  _sqc2(auVar4);
  _sqc2(auVar5);
  fStack_8 = *(float *)(this->pos + 8) * 0.5;
  fStack_4 = *(float *)(this->pos + 0xc) * 0.5;
  auVar3 = _vmr32(in_vf0);
  auVar4 = _vmr32(auVar3);
  auVar5 = _vmr32(auVar4);
  auStack_20 = _sqc2(in_vf0);
  auStack_30 = _sqc2(auVar3);
  auStack_40 = _sqc2(auVar4);
  auStack_50 = _sqc2(auVar5);
  sceVu0RotMatrixX(this->angle * fRadian,auStack_50,auStack_50);
  fStack_60 = fStack_8;
  fStack_5c = fStack_4;
  uStack_58 = sm_fZero__7MenuObj;
  uStack_54 = 0x3f800000;
  ApplyMatrix__6MatrixCFRC7FVector(auStack_b0,auStack_50,&fStack_60);
  fStack_80 = auStack_b0._0_4_;
  fStack_5c = auStack_b0._4_4_;
  uStack_58 = uStack_a8;
  uStack_54 = uStack_a4;
  if (fStack_5c < -fStack_4) {
    fStack_5c = -fStack_4;
  }
  else if (fStack_4 < fStack_5c) {
    fStack_5c = fStack_4;
  }
  afStack_a0[0] = -fStack_80;
  afStack_a0[1] = -fStack_5c;
  afStack_a0[4] = -fStack_80;
  afStack_a0[5] = fStack_5c;
  fStack_7c = -fStack_5c;
  fStack_6c = fStack_5c;
  auVar3 = _vmr32(in_vf0);
  auVar4 = _vmr32(auVar3);
  auVar5 = _vmr32(auVar4);
  auStack_20 = _sqc2(in_vf0);
  auStack_30 = _sqc2(auVar3);
  auStack_40 = _sqc2(auVar4);
  auStack_50 = _sqc2(auVar5);
  uVar1 = ((ulong)this->cflags & 0x3ff) >> 6;
  fStack_70 = fStack_80;
  if (uVar1 != 8) {
    fStack_60 = fStack_80;
    if (uVar1 != 4) {
      if (uVar1 == 2) {
        sceVu0RotMatrixZ(fRadian * 90.0,auStack_50,auStack_50);
        fStack_60 = fStack_4;
        fStack_5c = fStack_8;
      }
      else if (uVar1 == 1) {
        sceVu0RotMatrixZ(fRadian * -90.0,auStack_50,auStack_50);
        fStack_60 = fStack_4;
        fStack_5c = fStack_8;
      }
      goto LAB_00271e30;
    }
    sceVu0RotMatrixZ(fRadian * -180.0,auStack_50,auStack_50);
  }
  fStack_60 = fStack_8;
  fStack_5c = fStack_4;
LAB_00271e30:
  for (iVar2 = 0; iVar2 < 4; iVar2 = iVar2 + 1) {
    ApplyMatrix__6MatrixCFRC7FVector(auStack_c0,auStack_50,afStack_a0 + iVar2 * 4);
    afStack_a0[iVar2 * 4] = auStack_c0._0_4_;
    afStack_a0[iVar2 * 4 + 1] = auStack_c0._4_4_;
    afStack_a0[iVar2 * 4 + 2] = fStack_b8;
    afStack_a0[iVar2 * 4 + 3] = fStack_b4;
    afStack_a0[iVar2 * 4] = afStack_a0[iVar2 * 4] + fStack_60;
    afStack_a0[iVar2 * 4 + 1] = afStack_a0[iVar2 * 4 + 1] + fStack_5c;
    SetVertex__11MenuPolygonFiffb
              (afStack_a0[iVar2 * 4],afStack_a0[iVar2 * 4 + 1],this + 0x1c,iVar2,0);
  }
  if (this->shadow != 0) {
    for (iVar2 = 0; iVar2 < 4; iVar2 = iVar2 + 1) {
      SetVertex__11MenuPolygonFiffb
                (*(u32 *)(iVar2 * 8 + this + 0x70),
                 *(u32 *)(iVar2 * 8 + this + 0x74),this->shadow,iVar2,1
                );
    }
  }
  return;
}

// JP: 0x00271f60  SetFlareOffset__6CursorFv  size 0x1c0
// Cursor::SetFlareOffset()
void SetFlareOffset__6CursorFv(Cursor *this)
{
  ulong uVar1;
  if (this->flare != 0) {
    uVar1 = ((ulong)this->cflags & 0x3ff) >> 6;
    if (uVar1 == 8) {
      SetOffset__9MenuFlareFffff
                (-*(float *)(this->pos + 8) / 6.0,sm_fZero__7MenuObj,
                 *(u32 *)(this->pos + 8),
                 *(u32 *)(this->pos + 0xc),this->flare);
    }
    else if (uVar1 == 4) {
      SetOffset__9MenuFlareFffff
                (*(float *)(this->pos + 8) / 6.0,sm_fZero__7MenuObj,
                 *(u32 *)(this->pos + 8),
                 *(u32 *)(this->pos + 0xc),this->flare);
    }
    else if (uVar1 == 2) {
      SetOffset__9MenuFlareFffff
                (sm_fZero__7MenuObj,-*(float *)(this->pos + 8) / 6.0,
                 *(u32 *)(this->pos + 0xc),
                 *(u32 *)(this->pos + 8),this->flare);
    }
    else if (uVar1 == 1) {
      SetOffset__9MenuFlareFffff
                (sm_fZero__7MenuObj,*(float *)(this->pos + 8) / 6.0,
                 *(u32 *)(this->pos + 0xc),
                 *(u32 *)(this->pos + 8),this->flare);
    }
  }
  return;
}

// JP: 0x00272120  Polling__6CursorFv  size 0x370
// Cursor::Polling()
void Polling__6CursorFv(Cursor *this)
{
  float fStack_18;
  float fStack_14;
  if ((long)((ulong)this->cflags << 0x3a) < 0) {
    this->angle = this->angle + sm_fPassTime__7MenuObj * 0.5;
    if (180.0 <= this->angle) {
      this->angle = this->angle - 360.0;
    }
    SetVertex__6CursorFv(this);
  }
  if (this->move_state == '\x05') {
    fStack_14 = this->target_x - *this->pos;
    fStack_18 = this->target_y - *(float *)(this->pos + 4);
    *this->pos =
         *this->pos + fStack_14 * sm_fPassTime__7MenuObj * 0.01;
    *(float *)(this->pos + 4) =
         *(float *)(this->pos + 4) + fStack_18 * sm_fPassTime__7MenuObj * 0.01;
    if (fStack_14 < sm_fZero__7MenuObj) {
      fStack_14 = -fStack_14;
    }
    if (fStack_18 < sm_fZero__7MenuObj) {
      fStack_18 = -fStack_18;
    }
    if ((fStack_14 < 1.0) && (fStack_18 < 1.0)) {
      *this->pos = this->target_x;
      *(u32 *)(this->pos + 4) = this->target_y;
      this->cflags2 = this->cflags2 & 0x7f;
      this->move_state = 1;
    }
  }
  if ((((long)((ulong)this->cflags2 << 0x3b) < 0) && (this->place != 0)) &&
     (this->place->owner != 0)) {
    this->flags =
         this->flags & 0xfe |
         this->place->owner->flags & 1;
  }
  if (this->flare != 0) {
    VCALL(this->flare, 0x10 /*Polling*/)();
  }
  return;
}

// JP: 0x00272490  Update__6CursorFiiUs  size 0x484
// Cursor::Update(int, int, unsigned short)
void Update__6CursorFiiUs(Cursor *this,int param_2,int param_3,uint param_4)
{
  u8 bVar1;
  ulong uVar2;
  int iVar3;
  u8 *pbVar4;
  int iVar5;
  u8 in_vf0 [16];
  u8 auVar6 [16];
  u8 auVar7 [16];
  u8 auVar8 [16];
  float fStack_8;
  float fStack_4;
  auVar6 = _vmr32(in_vf0);
  auVar7 = _vmr32(auVar6);
  auVar8 = _vmr32(auVar7);
  _sqc2(in_vf0);
  _sqc2(auVar6);
  _sqc2(auVar7);
  _sqc2(auVar8);
  iVar5 = (int)this;
  pbVar4 = (u8 *)(iVar5 + (m_Env__8VIF1Prim & 1) + 0x10);
  fStack_8 = sm_fZero__7MenuObj;
  fStack_4 = sm_fZero__7MenuObj;
  uVar2 = (ulong)*(u8 *)(iVar5 + 0x11) & 0xfffffffffffffff7 | 8;
  *(char *)(iVar5 + 0x11) = (char)uVar2;
  *(u8 *)(iVar5 + 0x10) =
       *(u8 *)(iVar5 + 0x10) & 0xf7 | (u8)((uint)((uVar2 << 0x3c) >> 0x3f) << 3);
  uVar2 = (ulong)*(u8 *)(iVar5 + 0x11) & 0xffffffffffffffef | 0x10;
  *(char *)(iVar5 + 0x11) = (char)uVar2;
  *(u8 *)(iVar5 + 0x10) =
       *(u8 *)(iVar5 + 0x10) & 0xef | (u8)((uint)((uVar2 << 0x3b) >> 0x3f) << 4);
  if (*(int *)(iVar5 + 0xec) == 0) {
    iVar3 = 0;
  }
  else {
    iVar3 = *(int *)(*(int *)(iVar5 + 0xec) + 0x18);
  }
  if (iVar3 != 0) {
    if ((long)((ulong)*(u8 *)(iVar5 + 0xfb) << 0x3c) < 0) {
      param_2 = param_2 + (int)((*(float *)(iVar3 + 100) + *(float *)(iVar3 + 0x8c)) * 16.0);
      param_3 = param_3 + (int)((*(float *)(iVar3 + 0x68) + *(float *)(iVar3 + 0x90)) * 16.0);
    }
    if ((long)((ulong)*(u8 *)(iVar5 + 0xfb) << 0x38) < 0) {
      GetPoint__6CursorFPfPf(this,&fStack_8,&fStack_4);
      fStack_8 = fStack_8 + *(float *)(iVar3 + 0x8c);
      fStack_4 = fStack_4 + *(float *)(iVar3 + 0x90);
      if (fStack_8 < sm_fZero__7MenuObj) {
        fStack_8 = -fStack_8;
      }
      else if (*(float *)(iVar3 + 0x6c) < fStack_8) {
        fStack_8 = *(float *)(iVar3 + 0x6c) - fStack_8;
      }
      else {
        fStack_8 = sm_fZero__7MenuObj;
      }
      if (fStack_4 < sm_fZero__7MenuObj) {
        fStack_4 = -fStack_4;
      }
      else if (*(float *)(iVar3 + 0x70) < fStack_4) {
        fStack_4 = *(float *)(iVar3 + 0x70) - fStack_4;
      }
      else {
        fStack_4 = sm_fZero__7MenuObj;
      }
    }
    if ((long)((ulong)*(u8 *)(iVar5 + 0xfb) << 0x3d) < 0) {
      param_4 = (param_4 & 0xffff) * (uint)*(u16 *)(iVar3 + 0xac) >> 0xf & 0xffff;
    }
  }
  if (*(char *)((m_Env__8VIF1Prim & 1) + iVar5 + 0xb0) != '\0') {
    (**(code **)(*(int *)(iVar5 + 0xa8) + 0x14))(iVar5 + 0xa0,0,0,0);
  }
  param_2 = param_2 + (int)((**(float **)(iVar5 + 0xd8) + fStack_8) * 16.0);
  param_3 = param_3 + (int)((*(float *)(*(int *)(iVar5 + 0xd8) + 4) + fStack_4) * 16.0);
  bVar1 = *pbVar4;
  *(u8 *)(iVar5 + 0x2c) = *(u8 *)(iVar5 + 0x2c) | bVar1;
  *(u8 *)(iVar5 + 0x2d) = *(u8 *)(iVar5 + 0x2d) | bVar1;
  (**(code **)(*(int *)(iVar5 + 0x24) + 0x14))(iVar5 + 0x1c,param_2,param_3,param_4);
  if (*(int *)(iVar5 + 0xd4) != 0) {
    (**(code **)(*(int *)(*(int *)(iVar5 + 0xd4) + 8) + 0x14))
              (*(int *)(iVar5 + 0xd4),param_2,param_3,param_4);
  }
  if (*(int *)(iVar5 + 0xd0) != 0) {
    bVar1 = *pbVar4;
    iVar3 = *(int *)(iVar5 + 0xd0);
    *(u8 *)(iVar3 + 0x10) = *(u8 *)(iVar3 + 0x10) | bVar1;
    *(u8 *)(iVar3 + 0x11) = *(u8 *)(iVar3 + 0x11) | bVar1;
    (**(code **)(*(int *)(*(int *)(iVar5 + 0xd0) + 8) + 0x14))
              (*(int *)(iVar5 + 0xd0),param_2 + 0x20,param_3 + 0x20,0);
  }
  *pbVar4 = *pbVar4 & 0x80;
  return;
}

// JP: 0x00272920  Connect__6CursorFP4_QWD  size 0xf4
// Cursor::Connect(_QWD*)
void Connect__6CursorFP4_QWD(Cursor *this,u32 param_2)
{
  u32 uVar1;
  ulong uVar2;
  u32 uStack_10;
  uVar2 = ((ulong)this->cflags & 0x1f) >> 3;
  if (uVar2 == 2) {
    uStack_10 = VCALL(this->flare, 0x18 /*Connect*/)
                          (this->flare,param_2);
  }
  else {
    uStack_10 = param_2;
    if (uVar2 == 1) {
      uVar1 = (**(code **)(this->f_a8 /*int **/ + 0x18))(this + 0xa0,param_2);
      uStack_10 = VCALL(this->shadow, 0x18 /*Connect*/)
                            (this->shadow,uVar1);
      goto LAB_002729e8;
    }
  }
  uStack_10 = (**(code **)(this->f_a8 /*int **/ + 0x18))(this + 0xa0,uStack_10);
LAB_002729e8:
  (**(code **)(this->f_24 /*int **/ + 0x18))(this + 0x1c,uStack_10);
  return;
}

// JP: 0x00272a20  Destroy__6CursorFv  size 0x124
// Cursor::Destroy()
void Destroy__6CursorFv(Cursor *this)
{
  int iVar1;
  (**(code **)(this->f_24 /*int **/ + 0x1c))();
  (**(code **)(this->f_a8 /*int **/ + 0x1c))();
  if (this->shadow != 0) {
    iVar1 = this->shadow;
    if (iVar1 != 0) {
      VCALL(iVar1, 0x8 /*dtor*/)(iVar1,1);
    }
    this->shadow = 0;
  }
  if (this->flare != 0) {
    iVar1 = this->flare;
    if (iVar1 != 0) {
      VCALL(iVar1, 0x8 /*dtor*/)(iVar1,1);
    }
    this->flare = 0;
  }
  if (this->back != 0) {
    iVar1 = this->back;
    if (iVar1 != 0) {
      VCALL(iVar1, 0x8 /*dtor*/)(iVar1,1);
    }
    this->back = 0;
  }
  return;
}

// JP: 0x00272b50  Clear__6CursorFv  size 0x134
// Cursor::Clear()
void Clear__6CursorFv(Cursor *this)
{
  u32 uVar1;
  ulong uVar2;
  Clear__7MenuObjFv(this);
  (**(code **)(this->f_24 /*int **/ + 0x20))();
  (**(code **)(this->f_a8 /*int **/ + 0x20))();
  this->shadow = 0;
  this->flare = 0;
  this->back = 0;
  this->place = 0;
  this->pos = this + 0x40;
  uVar1 = sm_fZero__7MenuObj;
  this->angle = sm_fZero__7MenuObj;
  this->target_y = uVar1;
  this->target_x = uVar1;
  this->off_y = uVar1;
  this->off_x = uVar1;
  this->move_state = 1;
  this->sound = 0;
  this->cflags = 0xe00;
  this->gap = 1;
  uVar2 = (ulong)this->dirty1 & 0xffffffffffffff7f | 0x80;
  this->dirty1 = (char)uVar2;
  this->dirty0 =
       this->dirty0 & 0x7f | (u8)((uint)((uVar2 << 0x38) >> 0x3f) << 7);
  return;
}
