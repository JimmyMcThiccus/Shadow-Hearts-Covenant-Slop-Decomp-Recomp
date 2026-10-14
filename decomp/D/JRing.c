// decomp/D/JRing.c — cleaned Ghidra output (SLPM_602.19, Metrowerks MIPS), Shadow Hearts: Covenant JP demo.
// Field accesses are shown as this->T_off (T = u8/u16/u32/f32/i32/p, off = hex offset);
// JRing fields are named from the recovered struct. See notes/D/*.md for layouts.
// CAVEAT: when the base pointer is a float*/int*/short*, the number in `T_off` is an ELEMENT offset (byte offset = off*sizeof(elem)).
// `this` is the C++ this pointer (param_1); the Metrowerks ABI passes it in a0.

// JP: 0x002bf6f0  __ct__5JRingFsi  =  JRing::JRing
int JRing::JRing(int this,undefined2 param_2,undefined4 param_3)

{
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  VIF1Prim *prim;
  
  CPolObj::CPolObj(this);
  VIF1Prim::VIF1Prim((VIF1Prim *)(this + 0x18));
  this->u32_2c = 0;
  this->u32_30 = 0;
  *(undefined1 **)(this + 0x34) = DelayDeleteObject::__vt;
  *(undefined1 **)(this + 0x14) = JRing::__vt;
  this->u32_28 = 0x4066d0;
  this->u32_34 = 0x4066e0;
  this->u32_70 = in_zero_lo;
  this->u32_74 = in_zero_hi;
  this->u32_78 = in_zero_udw;
  this->u32_7c = in_register_0000000c;
  this->u32_a0 = in_zero_lo;
  this->u32_a4 = in_zero_hi;
  this->u32_a8 = in_zero_udw;
  this->u32_ac = in_register_0000000c;
  iVar3 = this + 0x100;
  do {
    iVar2 = iVar3 + 0xc;
    do {
      iVar2 = iVar2 + 4;
    } while (iVar2 != iVar3 + 0x18);
    iVar3 = iVar3 + 0x24;
  } while (iVar3 != this + 0x2b0);
  iVar3 = this + 0x2b0;
  do {
    iVar2 = iVar3 + 0xc;
    do {
      iVar2 = iVar2 + 4;
    } while (iVar2 != iVar3 + 0x18);
    iVar3 = iVar3 + 0x24;
  } while (iVar3 != this + 0x460);
  iVar3 = this + 0x46c;
  do {
    iVar3 = iVar3 + 4;
  } while (iVar3 != this + 0x478);
  iVar3 = this + 0x490;
  do {
    iVar3 = iVar3 + 4;
  } while (iVar3 != this + 0x49c);
  if (JRing::Pad == 0) {
    JRing::Pad = CPad::GetActive(0);
  }
  this->flagsA = 0;
  this->id = param_2;
  this->state = 0;
  this->sub = 0;
  this->intro = 0;
  this->ring_type = 0;
  this->end_miss = 0;
  this->end_ok = 0;
  this->end_strike = 0;
  uVar1 = SysTool::GetTimer();
  this->last_ms = uVar1;
  this->wait = 0;
  this->cx = 0x43800000;
  this->cy = 0x43600000;
  this->u32_70 = 0;
  this->u32_74 = 0;
  this->u32_78 = 0;
  this->u32_7c = 0x3f800000;
  this->scale_y = 0x3f59999a;
  this->scale_x = 0x3f800000;
  this->home_scale_x = 0x3f800000;
  this->u32_a0 = 0xbf060a92;
  this->u32_a4 = 0x3f75be0b;
  this->u32_a8 = 0;
  this->u32_ac = 0x3f800000;
  this->home_scale_y = 0x3f59999a;
  this->home_period = 0x3fcccccd;
  this->lap_add = 0;
  this->lap_mul = 0x3f800000;
  this->accel = 0;
  this->combo_window = 0x3e4ccccd;
  this->e8 = 1;
  this->ec = 0;
  this->cur_angle = 0;
  this->laps_allowed = 1;
  this->u32_1c = 0;
  this->u32_18 = 0;
  this->u32_554 = 0;
  this->u32_550 = 0;
  this->cb_mask = 0;
  this->cb_fn = 0;
  this->cb_user = 0;
  this->u16_570 = 0;
  this->u32_560 = 0;
  this->u32_564 = 0;
  this->u16_572 = 0;
  this->u32_568 = 0;
  this->u32_56c = 0;
  this->trial_a = 0;
  this->trial_b = 0;
  this->crack = 0;
  this->cut = 0;
  this->res_flags = 0;
  this->res_hit_count = 0;
  this->res_total = 0;
  this->res_base = 10000;
  this->res_percent = 0;
  this->res_strike_mult = 12000;
  this->res_damage_mult = 10000;
  for (iVar3 = 0; iVar3 < 0x20; iVar3 = iVar3 + 1) {
    *(undefined1 *)(this + 0x528 + iVar3) = 0;
  }
  this->custom_data = 0;
  this->u32_4fc = 0;
  this->u32_4f8 = 0;
  this->u32_504 = 0;
  this->u32_500 = 0;
  this->combo_button = 0;
  this->abn_c = 0;
  this->u32_55c = 0;
  this->u32_558 = 0;
  this->ot_layer = param_3;
  this->base_percent = 10000;
  this->max_percent = 12000;
  this->auto_mode = 0;
  JRing::Initialize(this);
  JRing::Entry(this);
  CPoller::Entry(CApp::app + 0x48,this,0x80,0);
  prim = (VIF1Prim *)0x0;
  if (this != 0) {
    prim = (VIF1Prim *)(this + 0x18);
  }
  World::AddOT((World *)&CApp::m_World,this->ot_layer,prim);
  this->flagsB = this->flagsB & 0xbf | 0x40;
  return this;
}

// JP: 0x002bfb50  __dt__5JRingFv  =  JRing::~JRing
int JRing::~JRing(int this,short param_2)

{
  if (this != 0) {
    *(undefined1 **)(this + 0x14) = JRing::__vt;
    this->u32_28 = 0x4066d0;
    this->u32_34 = 0x4066e0;
    if (this->i32_18 != 0) {
      __dla(this->u32_18);
    }
    if (this->i32_1c != 0) {
      __dla(this->u32_1c);
    }
    if ((this->i32_4f8 != 0) && (this->i32_4f8 != 0)) {
      __dla(this->i32_4f8 + -0x10);
    }
    if ((this->i32_4fc != 0) && (this->i32_4fc != 0)) {
      __dla(this->i32_4fc + -0x10);
    }
    if ((this->i32_500 != 0) && (this->i32_500 != 0)) {
      __dla(this->i32_500 + -0x10);
    }
    if ((this->i32_504 != 0) && (this->i32_504 != 0)) {
      __dla(this->i32_504 + -0x10);
    }
    if (this->crack != 0) {
      CrackJRing::~CrackJRing(this->crack,1);
    }
    if (this->cut != 0) {
      CutJRing::~CutJRing(this->cut,1);
    }
    JRing::Release(this);
    if ((this->cb_fn != 0) && ((long)((ulong)this->u8_f1 << 0x3d) < 0)) {
      (**(code **)(this + 0xf8))(0x400,0,this->cb_user);
    }
    if ((long)((ulong)this->flagsC << 0x3c) < 0) {
      JRing::DataDelete();
    }
    if (this != -0x2c) {
      *(undefined1 **)(this + 0x34) = DelayDeleteObject::__vt;
    }
    VIF1Prim::~VIF1Prim(this + 0x18,0);
    CPolObj::~CPolObj(this,0);
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}

// JP: 0x002bfe10  Destruct__5JRingFb  =  JRing::Destruct
void JRing::Destruct(int this,byte param_2)

{
  VIF1Prim *prim;
  
  this->flagsC = this->flagsC & 0xf7 | (param_2 & 1) << 3;
  if (this->crack != 0) {
    CrackJRing::~CrackJRing(this->crack,1);
  }
  this->crack = 0;
  this->flagsB = this->flagsB & 0xef;
  if (this->cut != 0) {
    CutJRing::~CutJRing(this->cut,1);
  }
  this->cut = 0;
  this->flagsB = this->flagsB & 0xdf;
  JRing::AllHitMesDelete(this);
  JRing::AllHitBarDelete(this);
  JRing::AllHitAreaEffDelete(this);
  if (this->trial_a != 0) {
    ComboTrial::Destruct(this->trial_a);
  }
  this->trial_a = 0;
  if (this->trial_b != 0) {
    ComboTrial::Destruct(this->trial_b);
  }
  this->trial_b = 0;
  this->flagsA = this->flagsA & 0x7f;
  this->flagsB = this->flagsB & 0xfe;
  this->flagsB = this->flagsB & 0xfd;
  if ((long)((ulong)this->flagsB << 0x39) < 0) {
    prim = (VIF1Prim *)0x0;
    if (this != 0) {
      prim = (VIF1Prim *)(this + 0x18);
    }
    World::ReleaseOT((World *)&CApp::m_World,prim);
  }
  this->flagsB = this->flagsB & 0xbf;
  CPoller::Dispose(CApp::app + 0x48,this);
  this->flagsA = this->flagsA & 0xf9 | 6;
  (**(code **)(this->i32_34 + 0xc))();
  return;
}

// JP: 0x002c0090  Initialize__5JRingFv  =  JRing::Initialize
void JRing::Initialize(undefined8 this)

{
  int iVar1;
  int this;
  undefined1 in_vf0 [16];
  undefined1 auVar3 [16];
  undefined1 auVar4 [16];
  undefined1 auVar5 [16];
  undefined4 uStack_430;
  undefined4 uStack_42c;
  undefined4 uStack_428;
  undefined4 uStack_424;
  undefined4 uStack_420;
  undefined4 uStack_41c;
  undefined4 uStack_418;
  undefined4 uStack_414;
  undefined4 auStack_410 [16];
  undefined1 auStack_3d0 [16];
  undefined1 auStack_3c0 [16];
  undefined4 uStack_3b0;
  undefined4 uStack_3ac;
  undefined4 uStack_3a8;
  undefined4 uStack_3a4;
  GsxCamera GStack_3a0;
  
  JRing::AllAreaInitialize(this);
  
  if (this->crack != 0) {
    CrackJRing::~CrackJRing(this->crack,1);
  }
  this->crack = 0;
  this->flagsB = this->flagsB & 0xef;
  if (this->cut != 0) {
    CutJRing::~CutJRing(this->cut,1);
  }
  this->cut = 0;
  this->flagsB = this->flagsB & 0xdf;
  this->u32_4d8 = 0;
  for (iVar1 = 0; iVar1 < 9; iVar1 = iVar1 + 1) {
    *(undefined4 *)(this + iVar1 * 4 + 0x4b4) = this->cur_angle;
  }
  GsxCamera::GsxCamera(&GStack_3a0);
  GStack_3a0.flNearZ = 10.0;
  GStack_3a0.flFarZ = 32000.0;
  GsxCamera::SetViewMatrix(&GStack_3a0,512.0,0.8,0.93333334,1.0,1.6777e+07);
  auVar3 = _vmr32(in_vf0);
  auVar4 = _vmr32(auVar3);
  auVar5 = _vmr32(auVar4);
  GStack_3a0.frame.r3 = (_BAD_)_sqc2(in_vf0);
  GStack_3a0.frame.r2 = (_BAD_)_sqc2(auVar3);
  GStack_3a0.frame.r1 = (_BAD_)_sqc2(auVar4);
  GStack_3a0.frame.r0 = (_BAD_)_sqc2(auVar5);
  uStack_3b0 = 0;
  uStack_3ac = 0;
  uStack_3a8 = 0xc4000000;
  uStack_3a4 = 0x3f800000;
  uStack_420 = 0;
  uStack_41c = 0x3f800000;
  uStack_418 = 0;
  uStack_414 = 0x3f800000;
  Matrix::ApplyMatrix(auStack_3c0,&GStack_3a0.frame,&uStack_420);
  uStack_430 = 0;
  uStack_42c = 0;
  uStack_428 = 0x3f800000;
  uStack_424 = 0x3f800000;
  Matrix::ApplyMatrix(auStack_3d0,&GStack_3a0.frame,&uStack_430);
  sceVu0CameraMatrix(&GStack_3a0.viewMat,&uStack_3b0,auStack_3d0,auStack_3c0);
  GsxCamera::GetViewScreenMatrix(auStack_410,&GStack_3a0);
  for (iVar1 = 0; iVar1 < 4; iVar1 = iVar1 + 1) {
    *(undefined4 *)(this + iVar1 * 0x10 + 0x590) = auStack_410[iVar1 * 4];
    *(undefined4 *)(this + iVar1 * 0x10 + 0x594) = auStack_410[iVar1 * 4 + 1];
    *(undefined4 *)(this + iVar1 * 0x10 + 0x598) = auStack_410[iVar1 * 4 + 2];
    *(undefined4 *)(this + iVar1 * 0x10 + 0x59c) = auStack_410[iVar1 * 4 + 3];
  }
  GsxCamera::~GsxCamera(&GStack_3a0,0xffffffffffffffff);
  return;
}

// JP: 0x002c0390  Polling__5JRingFv  =  JRing::Polling
undefined8 JRing::Polling(JRing *this)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = SysTool::GetTimer();
  this->flDt = (float)(uVar1 - this->dwLast_ms) / 1000.0;
  this->dwLast_ms = uVar1;
  for (iVar2 = 0; iVar2 < 0xc; iVar2 = iVar2 + 1) {
    if (((ulong)this->aAreas[iVar2].bFlags0 & 0x3f) >> 4 != 0) {
      if ((long)((ulong)this->aAreas[iVar2].bFlags0 << 0x39) < 0) {
        this->aAreas[iVar2].flBlink_t =
             this->aAreas[iVar2].flBlink_t - this->flDt * 0.75 * 6.0;
        if (this->aAreas[iVar2].flBlink_t <= 0.0) {
          this->aAreas[iVar2].flBlink_t = 0.0;
          this->aAreas[iVar2].bFlags0 = this->aAreas[iVar2].bFlags0 & 0xbf;
        }
      }
      else {
        this->aAreas[iVar2].flBlink_t =
             this->aAreas[iVar2].flBlink_t + this->flDt * 0.75 * 6.0;
        if (1.5 <= this->aAreas[iVar2].flBlink_t) {
          this->aAreas[iVar2].flBlink_t = 1.5;
          this->aAreas[iVar2].bFlags0 = this->aAreas[iVar2].bFlags0 & 0xbf | 0x40;
        }
      }
      this->bFlagsA = this->bFlagsA & 0x9f | 0x60;
    }
    if (((ulong)this->aAreas[iVar2].bFlags1 & 7) >> 1 != 0) {
      this->aAreas[iVar2].flFade_t = this->aAreas[iVar2].flFade_t - this->flDt * 6.0;
      if (this->aAreas[iVar2].flFade_t <= 0.0) {
        this->aAreas[iVar2].flFade_t = 0.0;
        this->aAreas[iVar2].bFlags1 = this->aAreas[iVar2].bFlags1 & 0xf9;
      }
      this->bFlagsA = this->bFlagsA & 0x9f | 0x60;
    }
    if (((ulong)this->aCustom[iVar2].bFlags0 & 0x3f) >> 4 != 0) {
      if ((long)((ulong)this->aCustom[iVar2].bFlags0 << 0x39) < 0) {
        this->aCustom[iVar2].flBlink_t =
             this->aCustom[iVar2].flBlink_t - this->flDt * 0.75 * 6.0;
        if (this->aCustom[iVar2].flBlink_t <= 0.0) {
          this->aCustom[iVar2].flBlink_t = 0.0;
          this->aCustom[iVar2].bFlags0 = this->aCustom[iVar2].bFlags0 & 0xbf;
        }
      }
      else {
        this->aCustom[iVar2].flBlink_t =
             this->aCustom[iVar2].flBlink_t + this->flDt * 0.75 * 6.0;
        if (1.5 <= this->aCustom[iVar2].flBlink_t) {
          this->aCustom[iVar2].flBlink_t = 1.5;
          this->aCustom[iVar2].bFlags0 = this->aCustom[iVar2].bFlags0 & 0xbf | 0x40;
        }
      }
      this->bFlagsA = this->bFlagsA & 0x9f | 0x60;
    }
    if (((ulong)this->aCustom[iVar2].bFlags1 & 7) >> 1 != 0) {
      this->aCustom[iVar2].flFade_t = this->aCustom[iVar2].flFade_t - this->flDt * 6.0;
      if (this->aCustom[iVar2].flFade_t <= 0.0) {
        this->aCustom[iVar2].flFade_t = 0.0;
        this->aCustom[iVar2].bFlags1 = this->aCustom[iVar2].bFlags1 & 0xf9;
      }
      this->bFlagsA = this->bFlagsA & 0x9f | 0x60;
    }
  }
  if (((ulong)(this->gamble).bFlags0 & 0x3f) >> 4 != 0) {
    if ((long)((ulong)(this->gamble).bFlags0 << 0x39) < 0) {
      (this->gamble).flBlink_t = (this->gamble).flBlink_t - this->flDt * 0.75 * 6.0;
      if ((this->gamble).flBlink_t <= 0.0) {
        (this->gamble).flBlink_t = 0.0;
        (this->gamble).bFlags0 = (this->gamble).bFlags0 & 0xbf;
      }
    }
    else {
      (this->gamble).flBlink_t = (this->gamble).flBlink_t + this->flDt * 0.75 * 6.0;
      if (1.5 <= (this->gamble).flBlink_t) {
        (this->gamble).flBlink_t = 1.5;
        (this->gamble).bFlags0 = (this->gamble).bFlags0 & 0xbf | 0x40;
      }
    }
    this->bFlagsA = this->bFlagsA & 0x9f | 0x60;
  }
  if (((ulong)(this->gamble).bFlags1 & 7) >> 1 != 0) {
    (this->gamble).flFade_t = (this->gamble).flFade_t - this->flDt * 6.0;
    if ((this->gamble).flFade_t <= 0.0) {
      (this->gamble).flFade_t = 0.0;
      (this->gamble).bFlags1 = (this->gamble).bFlags1 & 0xf9;
    }
    this->bFlagsA = this->bFlagsA & 0x9f | 0x60;
  }
  if ((long)((ulong)this->bFlagsC << 0x3b) < 0) {
    this->flDt = 0.0;
  }
  else {
    JRing::Sequence(this);
  }
  return 0;
}

// JP: 0x002c0cf0  Sequence__5JRingFv  =  JRing::Sequence
void JRing::Sequence(undefined8 this)

{
  bool bVar1;
  char cVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  long lVar6;
  long lVar7;
  ushort uVar8;
  uint uVar9;
  int iVar10;
  short sVar11;
  int this;
  int unaff_s1_lo;
  float fVar13;
  
  
  if (this->wait != 0.0) {
    this->wait = this->wait - this->dt;
    if (0.0 < this->wait) {
      return;
    }
    this->wait = 0;
  }
  switch(this->state) {
  case 0:
    cVar2 = JRing::AutoLoadEndCheck(this);
    if (((cVar2 != '\0') && (JRing::RingSleep(this), this->cb_fn != 0)) &&
       ((this->cb_mask & 1) != 0)) {
      (**(code **)(this + 0xf8))(1,0,this->cb_user);
    }
    break;
  case 1:
    if (this->sub == 1) {
      cVar2 = JRing::DataLoadEndCheck();
      if (((cVar2 != '\0') && (JRing::RingSleep(this), this->cb_fn != 0)) &&
         ((this->cb_mask & 1) != 0)) {
        (**(code **)(this + 0xf8))(1,0,this->cb_user);
      }
    }
    else if (this->sub == 0) {
      if ((JRing::System & 3) == 0) {
        JRing::DataLoad(0);
      }
      this->sub = 1;
    }
    break;
  case 3:
    switch(this->intro) {
    case 1:
      this->scale_x = this->home_scale_x;
      this->scale_y = this->home_scale_y;
      this->i32_70 = (int)this->u64_a0;
      this->i32_74 = (int)((ulong)this->u64_a0 >> 0x20);
      this->u32_78 = this->u32_a8;
      this->u32_7c = this->u32_ac;
      this->state = 4;
      this->sub = 0;
      break;
    case 2:
      if (this->sub == 1) {
        this->scale_x =
             this->scale_x +
             this->dt *
             ((this->home_scale_x - this->scale_x) / 7.0) * 60.0;
        this->anim_a = this->anim_a + this->dt;
        this->flagsA = this->flagsA & 0x9f | 0x60;
        if (0.8 <= this->anim_a) {
          this->scale_x = this->home_scale_x;
          this->state = 4;
          this->sub = 0;
        }
      }
      else if (this->sub == 0) {
        this->scale_x = 0;
        this->scale_y = this->home_scale_y;
        this->anim_a = 0;
        this->sub = 1;
        this->flagsA = this->flagsA & 0x9f | 0x60;
      }
      break;
    case 3:
      if (this->sub == 1) {
        this->scale_y =
             this->scale_y +
             this->dt *
             ((this->home_scale_y - this->scale_y) / 7.0) * 60.0;
        this->anim_a = this->anim_a + this->dt;
        this->flagsA = this->flagsA & 0x9f | 0x60;
        if (0.8 <= this->anim_a) {
          this->scale_y = this->home_scale_y;
          this->state = 4;
          this->sub = 0;
        }
      }
      else if (this->sub == 0) {
        this->scale_x = this->home_scale_x;
        this->scale_y = 0;
        this->sub = 1;
        this->flagsA = this->flagsA & 0x9f | 0x60;
      }
      break;
    case 4:
      if (this->sub == 1) {
        this->anim_a =
             this->anim_a -
             (this->anim_a / 7.0) * 60.0 * this->dt;
        this->anim_b =
             this->anim_b -
             (this->anim_b / 7.0) * 60.0 * this->dt;
        this->f32_70 = this->f32_a0 + this->anim_a;
        this->f32_74 = this->f32_a4 + this->anim_b;
        this->u32_78 = this->u32_a8;
        this->u32_7c = 0;
        while (this->f32_70 < -3.1415927) {
          this->f32_70 = this->f32_70 + 6.2831855;
        }
        while (3.1415927 < this->f32_70) {
          this->f32_70 = this->f32_70 - 6.2831855;
        }
        while (this->f32_74 < -3.1415927) {
          this->f32_74 = this->f32_74 + 6.2831855;
        }
        while (3.1415927 < this->f32_74) {
          this->f32_74 = this->f32_74 - 6.2831855;
        }
        this->scale_x =
             this->scale_x +
             this->dt *
             ((this->home_scale_x - this->scale_x) / 7.0) * 60.0;
        this->anim_c = this->anim_c + this->dt;
        this->flagsA = this->flagsA & 0x9f | 0x60;
        if (0.8 <= this->anim_c) {
          this->scale_x = this->home_scale_x;
          this->i32_70 = (int)this->u64_a0;
          this->i32_74 = (int)((ulong)this->u64_a0 >> 0x20);
          this->u32_78 = this->u32_a8;
          this->u32_7c = this->u32_ac;
          this->state = 4;
          this->sub = 0;
        }
      }
      else if (this->sub == 0) {
        this->scale_x = 0;
        this->scale_y = this->home_scale_y;
        this->anim_a = 0xc0afede0;
        this->anim_b = 0x40c90fdb;
        this->f32_70 = this->f32_a0 + this->anim_a;
        this->f32_74 = this->f32_a4 + this->anim_b;
        this->u32_78 = this->u32_a8;
        this->u32_7c = 0;
        while (this->f32_70 < -3.1415927) {
          this->f32_70 = this->f32_70 + 6.2831855;
        }
        while (3.1415927 < this->f32_70) {
          this->f32_70 = this->f32_70 - 6.2831855;
        }
        while (this->f32_74 < -3.1415927) {
          this->f32_74 = this->f32_74 + 6.2831855;
        }
        while (3.1415927 < this->f32_74) {
          this->f32_74 = this->f32_74 - 6.2831855;
        }
        this->anim_c = 0;
        this->sub = 1;
        this->flagsA = this->flagsA & 0x9f | 0x60;
      }
      break;
    case 5:
      if (this->sub == 1) {
        this->anim_a =
             this->anim_a -
             (this->anim_a / 7.0) * 60.0 * this->dt;
        this->anim_b =
             this->anim_b -
             (this->anim_b / 7.0) * 60.0 * this->dt;
        this->f32_70 = this->f32_a0 + this->anim_a;
        this->f32_74 = this->f32_a4 + this->anim_b;
        this->u32_78 = this->u32_a8;
        this->u32_7c = 0;
        while (this->f32_70 < -3.1415927) {
          this->f32_70 = this->f32_70 + 6.2831855;
        }
        while (3.1415927 < this->f32_70) {
          this->f32_70 = this->f32_70 - 6.2831855;
        }
        while (this->f32_74 < -3.1415927) {
          this->f32_74 = this->f32_74 + 6.2831855;
        }
        while (3.1415927 < this->f32_74) {
          this->f32_74 = this->f32_74 - 6.2831855;
        }
        this->scale_y =
             this->scale_y +
             this->dt *
             ((this->home_scale_y - this->scale_y) / 7.0) * 60.0;
        this->anim_c = this->anim_c + this->dt;
        this->flagsA = this->flagsA & 0x9f | 0x60;
        if (0.8 <= this->anim_c) {
          this->scale_y = this->home_scale_y;
          this->i32_70 = (int)this->u64_a0;
          this->i32_74 = (int)((ulong)this->u64_a0 >> 0x20);
          this->u32_78 = this->u32_a8;
          this->u32_7c = this->u32_ac;
          this->state = 4;
          this->sub = 0;
        }
      }
      else if (this->sub == 0) {
        this->scale_x = this->home_scale_x;
        this->scale_y = 0;
        this->anim_a = 0xc0afede0;
        this->anim_b = 0x40c90fdb;
        this->f32_70 = this->f32_a0 + this->anim_a;
        this->f32_74 = this->f32_a4 + this->anim_b;
        this->u32_78 = this->u32_a8;
        this->u32_7c = 0;
        while (this->f32_70 < -3.1415927) {
          this->f32_70 = this->f32_70 + 6.2831855;
        }
        while (3.1415927 < this->f32_70) {
          this->f32_70 = this->f32_70 - 6.2831855;
        }
        while (this->f32_74 < -3.1415927) {
          this->f32_74 = this->f32_74 + 6.2831855;
        }
        while (3.1415927 < this->f32_74) {
          this->f32_74 = this->f32_74 - 6.2831855;
        }
        this->anim_c = 0;
        this->sub = 1;
        this->flagsA = this->flagsA & 0x9f | 0x60;
        HNMSnd::PlaySE(HNMSnd::sys,0x2002,1,0);
      }
      break;
    case 6:
      if (this->sub == 1) {
        this->f32_78 =
             this->f32_78 +
             (6.2831855 / this->period) * this->dt;
        while (3.1415927 <= this->f32_78) {
          this->f32_78 = this->f32_78 - 6.2831855;
        }
        this->scale_x =
             this->scale_x +
             this->dt *
             ((this->home_scale_x - this->scale_x) / 7.0) * 60.0;
        this->anim_a = this->anim_a + this->dt;
        this->flagsA = this->flagsA & 0x9f | 0x60;
        if (0.8 <= this->anim_a) {
          this->scale_x = this->home_scale_x;
          this->state = 4;
          this->sub = 0;
        }
      }
      else if (this->sub == 0) {
        this->scale_x = 0;
        this->scale_y = this->home_scale_y;
        this->anim_a = 0;
        this->sub = 1;
        this->flagsA = this->flagsA & 0x9f | 0x60;
      }
    }
    if (this->state == 4) {
      if (((-1 < (long)((ulong)this->abn_d << 0x3d)) &&
          (this->ring_type != 0)) && (this->ring_type != 6)) {
        this->flagsB = this->flagsB & 0xfd | 2;
      }
      this->flagsA = this->flagsA & 0xf9 | 6;
      if ((this->cb_fn != 0) && ((long)((ulong)this->cb_mask << 0x3e) < 0)) {
        (**(code **)(this + 0xf8))(2,0,this->cb_user);
      }
      if (this->ring_type == 5) {
        HNMSnd::PlaySE(HNMSnd::sys,0x3000000,1,0);
      }
      else if ((this->ring_type != 0) && (this->ring_type != 6)) {
        HNMSnd::PlaySE(HNMSnd::sys,0x2001,1,0);
      }
    }
    break;
  case 4:
    switch(this->ring_type) {
    case 1:
      if (this->sub == 1) {
        bVar1 = false;
        if (this->auto_mode == 0) {
          if ((*(ushort *)((&CPad::m_pCoreArray)[JRing::Pad->i32_4] + 0x6c) & 0xf000) != 0)
          {
            bVar1 = true;
          }
        }
        else {
          cVar2 = JRing::JRingAuto(this);
          if (cVar2 == '\x01') {
            bVar1 = true;
          }
        }
        if (bVar1) {
          if (((ulong)this->flagsB & 0xf) >> 2 == 3) {
            lVar7 = JRing::HitCheck(this,this + 0x460);
          }
          else if ((long)((ulong)this->flagsC << 0x3d) < 0) {
            lVar7 = JRing::HitCheck
                              (this,this + this->cur_area * 0x24 + 0x2b0);
          }
          else {
            lVar7 = JRing::HitCheck
                              (this,this + this->cur_area * 0x24 + 0x100);
          }
          if ((this->flagsD & 1) != 0) {
            lVar7 = -1;
          }
          if ((lVar7 < 0) || ((this->laps_allowed == 0 && (lVar7 < 0x65)))) {
            HNMSnd::PlaySE(HNMSnd::sys,0x2007,1,0);
            if ((this->cb_fn != 0) &&
               ((long)((ulong)this->cb_mask << 0x3c) < 0)) {
              (**(code **)(this + 0xf8))(8,0,this->cb_user);
            }
            this->flagsB = this->flagsB & 0x7f;
            this->flagsC = this->flagsC & 0xfe;
            lVar7 = __nw(0xb0);
            if (lVar7 != 0) {
              HitMes::HitMes(lVar7,this,0,1);
            }
            if ((((ulong)this->flagsB & 0xf) >> 2 != 1) ||
               (this->laps_allowed < 1)) {
              if (this->hits == 0) {
                this->res_flags = this->res_flags & 0xf9;
              }
              else {
                this->res_flags = this->res_flags & 0xf9 | 2;
              }
              this->state = 6;
              this->sub = 0;
              this->wait = 0x3f800000;
              break;
            }
            if (((ulong)this->flagsB & 0xf) >> 2 == 3) {
              this->res_damage_mult = this->res_damage_mult * 9000;
              this->res_damage_mult = this->res_damage_mult / 10000;
            }
            else {
              if (this->period < 0.0) {
                iVar4 = this->cur_area + 1;
                if ((0xb < iVar4) || (*(char *)(this + iVar4 * 0x24 + 0x102) == -1)) {
                  iVar4 = 0;
                }
              }
              else {
                iVar4 = this->cur_area + -1;
                if (iVar4 < 0) {
                  iVar4 = this->area_count + -1;
                }
              }
              if ((long)((ulong)this->flagsC << 0x3d) < 0) {
                cVar2 = EasyAreaHitCheck(this->cur_angle,
                                         *(undefined2 *)(this + iVar4 * 0x24 + 0x2b4),
                                         *(undefined2 *)(this + iVar4 * 0x24 + 0x2b6));
                if (cVar2 == '\0') {
                  this->res_damage_mult = this->res_damage_mult * 9000;
                  this->res_damage_mult = this->res_damage_mult / 10000;
                }
              }
              else {
                cVar2 = EasyAreaHitCheck(this->cur_angle,
                                         *(undefined2 *)(this + iVar4 * 0x24 + 0x104),
                                         *(undefined2 *)(this + iVar4 * 0x24 + 0x106));
                if (cVar2 == '\0') {
                  this->res_damage_mult = this->res_damage_mult * 9000;
                  this->res_damage_mult = this->res_damage_mult / 10000;
                }
              }
            }
          }
          else {
            if (((ulong)this->flagsB & 0xf) >> 2 == 3) {
              iVar4 = this + 0x460;
            }
            else if ((long)((ulong)this->flagsC << 0x3d) < 0) {
              iVar4 = this + this->cur_area * 0x24 + 0x2b0;
            }
            else {
              iVar4 = this + this->cur_area * 0x24 + 0x100;
            }
            if (iVar4->i16_1a < 0x65) {
              iVar4->u8_1 = iVar4->u8_1 & 0xf9 | 2;
              iVar4->u32_20 = 0x3f800000;
              lVar6 = __nw(0x70);
              if (lVar6 != 0) {
                HitArea::HitArea
                          ((float)(int)iVar4->i16_4,
                           (float)((int)iVar4->i16_6 - (int)iVar4->i16_8),lVar6,
                           this,iVar4 + 0xc);
              }
            }
            else {
              iVar4->u8_1 = iVar4->u8_1 & 0xf9 | 4;
              iVar4->u32_20 = 0x3f800000;
              if (iVar4->i8_2 == '\x02') {
                lVar6 = __nw(0x70);
                if (lVar6 != 0) {
                  HitArea::HitArea
                            ((float)(((int)iVar4->i16_4 + (int)iVar4->i16_6) -
                                    (int)iVar4->i16_8),(float)(int)iVar4->i16_8,
                             lVar6,this,iVar4 + 0x14);
                }
              }
              else {
                lVar6 = __nw(0x70);
                if (lVar6 != 0) {
                  HitArea::HitArea
                            ((float)(((int)iVar4->i16_4 + (int)iVar4->i16_6) -
                                    (int)iVar4->i16_8),(float)(int)iVar4->i16_8,
                             lVar6,this,iVar4 + 0x10);
                }
              }
            }
            if ((this->cb_fn != 0) &&
               ((long)((ulong)this->cb_mask << 0x3d) < 0)) {
              (**(code **)(this + 0xf8))(4,0,this->cb_user);
            }
            if (this->laps_allowed == 0) {
              if (lVar7 == 100) {
                this->u8_528 = 1;
                this->res_percent = 10000;
              }
              else if (lVar7 < 100) {
                this->u8_528 = 2;
                this->res_percent = (int)lVar7 * 100;
              }
              else {
                this->u8_528 = 3;
                this->res_percent = 10000;
              }
            }
            else if (lVar7 == 100) {
              uVar3 = this->hits & 3;
              if (((int)this->hits < 0) && (uVar3 != 0)) {
                uVar3 = uVar3 - 4;
              }
              iVar10 = this + (this->hits >> 2);
              iVar10->u8_528 =
                   iVar10->u8_528 | (byte)(1 << ((uVar3 & 0xf) << 1));
              this->res_percent = 10000;
            }
            else if (lVar7 < 100) {
              uVar3 = this->hits & 3;
              if (((int)this->hits < 0) && (uVar3 != 0)) {
                uVar3 = uVar3 - 4;
              }
              iVar10 = this + (this->hits >> 2);
              iVar10->u8_528 =
                   iVar10->u8_528 | (byte)(2 << ((uVar3 & 0xf) << 1));
              this->res_percent = (int)lVar7 * 100;
            }
            else {
              uVar3 = this->hits & 3;
              if (((int)this->hits < 0) && (uVar3 != 0)) {
                uVar3 = uVar3 - 4;
              }
              iVar10 = this + (this->hits >> 2);
              iVar10->u8_528 =
                   iVar10->u8_528 | (byte)(3 << ((uVar3 & 0xf) << 1));
              this->res_percent = 10000;
            }
            this->res_hit_count = this->res_hit_count + 1;
            this->hits = this->hits + 1;
            if ((this->result_total != 0) &&
               (this->result_total <= this->hits)) {
              if ((long)this->res_hit_count < (long)this->result_total) {
                this->res_flags = this->res_flags & 0xf9 | 2;
              }
              else if ((this->flagsC & 1) == 0) {
                this->res_flags = this->res_flags & 0xf9 | 4;
              }
              else {
                this->res_flags = this->res_flags & 0xf9 | 6;
              }
              uVar5 = HitStopAngle(this->cur_angle,iVar4);
              this->cur_angle = uVar5;
              if (iVar4->i16_1a < 0x65) {
                HNMSnd::PlaySE(HNMSnd::sys,0x2004,1,0);
              }
              else {
                HNMSnd::PlaySE(HNMSnd::sys,0x2005,1,0);
              }
              if ((((ulong)this->flagsB & 0xf) >> 2 == 1) &&
                 (iVar4->i8_2 == '\x02')) {
                this->res_flags = this->res_flags & 0xf9 | 4;
              }
              if (((ulong)this->flagsB & 0xf) >> 2 == 2) {
                if (((ulong)this->res_flags & 7) >> 1 < 2) {
                  lVar7 = __nw(0xb0);
                  if (lVar7 != 0) {
                    HitMes::HitMes(lVar7,this,0,1);
                  }
                  this->state = 6;
                  this->sub = 0;
                  this->wait = 0x3f800000;
                  break;
                }
                if (this->res_has_modulate == 1) {
                  uVar9 = (int)this->res_total - 1;
                  uVar3 = uVar9 & 3;
                  if (((int)uVar9 < 0) && (uVar3 != 0)) {
                    uVar3 = uVar3 - 4;
                  }
                  uVar9 = (int)(uint)*(byte *)(this + (this->res_total + -1 >> 2) +
                                              0x528) >> ((uVar3 & 0xf) << 1);
                  uVar3 = uVar9 & 3;
                  if (((int)uVar9 < 0) && (uVar3 != 0)) {
                    uVar3 = uVar3 - 4;
                  }
                  if ((uVar3 == 0) || (uVar3 == 2)) {
                    lVar7 = __nw(0xb0);
                    if (lVar7 != 0) {
                      HitMes::HitMes(lVar7,this,0,1);
                    }
                    this->state = 6;
                    this->sub = 0;
                    this->wait = 0x3f800000;
                    break;
                  }
                }
              }
              if (((this->flagsC & 1) == 0) || (lVar7 < 0x65)) {
                lVar7 = __nw(0xb0);
                if (lVar7 != 0) {
                  HitMes::HitMes(lVar7,this,iVar4,0);
                }
              }
              else {
                lVar7 = __nw(0xb0);
                if (lVar7 != 0) {
                  HitMes::HitMes(lVar7,this,iVar4,1);
                }
              }
              if (((long)((ulong)this->flagsC << 0x3e) < 0) &&
                 ((long)this->result_total <= (long)this->res_hit_count)) {
                this->state = 5;
                this->sub = 0;
                this->wait = 0x3f000000;
                if (this->trial_a == 0) {
                  lVar7 = __nw(0xb0);
                  uVar5 = 0;
                  if (lVar7 != 0) {
                    uVar5 = ComboTrial::ComboTrial(lVar7,this,0,0);
                  }
                  this->trial_a = uVar5;
                }
              }
              else if ((this->flagsC & 1) == 0) {
                this->state = 7;
                this->sub = 0;
                if ((long)((ulong)this->flagsC << 0x38) < 0) {
                  this->wait = 0;
                }
                else {
                  this->wait = 0x3f000000;
                }
              }
              else {
                this->state = 8;
                this->sub = 0;
                if ((long)((ulong)this->flagsC << 0x38) < 0) {
                  this->wait = 0;
                }
                else {
                  this->wait = 0x3f000000;
                }
              }
              break;
            }
            uVar5 = HitStopAngle(this->cur_angle,iVar4);
            if (iVar4->i16_1a < 0x65) {
              HNMSnd::PlaySE(HNMSnd::sys,0x2004,1,0);
            }
            else {
              HNMSnd::PlaySE(HNMSnd::sys,0x2005,1,0);
            }
            lVar7 = __nw(0x60);
            if (lVar7 != 0) {
              HitBar::HitBar(uVar5,lVar7,this);
            }
            lVar7 = __nw(0xb0);
            if (lVar7 != 0) {
              HitMes::HitMes(lVar7,this,iVar4,0);
            }
            iVar4 = this->cur_area;
            if (0.0 <= this->period) {
              this->cur_area = this->cur_area + 1;
              if ((0xb < this->cur_area) ||
                 (*(char *)(this + this->cur_area * 0x24 + 0x102) == -1)) {
                this->cur_area = 0;
              }
            }
            else {
              this->cur_area = this->cur_area + -1;
              if (this->cur_area < 0) {
                this->cur_area = this->area_count + -1;
              }
            }
            if (iVar4 == this->cur_area) {
              this->flagsD = this->flagsD & 0xfe | 1;
            }
            JRing::AreaOverCheckInit(this,this->cur_area);
            if (this->auto_mode == 3) {
              if (((ulong)this->flagsB & 0xf) >> 2 == 3) {
                JRing::JRingAutoInit(this,this + 0x460,0,1);
              }
              else if ((long)((ulong)this->flagsC << 0x3d) < 0) {
                JRing::JRingAutoInit
                          (this,this + this->cur_area * 0x24 + 0x2b0,
                           this + iVar4 * 0x24 + 0x2b0,1);
              }
              else {
                JRing::JRingAutoInit
                          (this,this + this->cur_area * 0x24 + 0x100,
                           this + iVar4 * 0x24 + 0x100,1);
              }
            }
            this->anim_a = 0;
          }
        }
        cVar2 = JRing::AreaOverCheck(this);
        if (cVar2 == '\0') {
          bVar1 = 0 < this->laps_allowed && ((ulong)this->flagsB & 0xf) >> 2 == 1;
          if ((((0 < this->laps_allowed) &&
               (this->laps_allowed <= this->laps_done + 1)) &&
              (0.0 <= this->period)) &&
             (this->area_count <= this->cur_area + 1)) {
            bVar1 = false;
          }
          if (((0 < this->laps_allowed) &&
              (this->laps_allowed <= this->laps_done + 1)) &&
             ((this->period < 0.0 && (this->cur_area == 0)))) {
            bVar1 = false;
          }
          if (bVar1) {
            if ((this->cb_fn != 0) &&
               ((long)((ulong)this->cb_mask << 0x3b) < 0)) {
              (**(code **)(this + 0xf8))(0x10,0,this->cb_user);
            }
            HNMSnd::PlaySE(HNMSnd::sys,0x2007,1,0);
            this->flagsB = this->flagsB & 0x7f;
            this->flagsC = this->flagsC & 0xfe;
            lVar7 = __nw(0xb0);
            if (lVar7 != 0) {
              HitMes::HitMes(lVar7,this,0,1);
            }
            this->res_damage_mult = this->res_damage_mult * 9000;
            this->res_damage_mult = this->res_damage_mult / 10000;
            this->hits = this->hits + 1;
            iVar4 = this->cur_area;
            if (0.0 <= this->period) {
              this->cur_area = this->cur_area + 1;
              if ((0xb < this->cur_area) ||
                 (*(char *)(this + this->cur_area * 0x24 + 0x102) == -1)) {
                this->cur_area = 0;
              }
            }
            else {
              this->cur_area = this->cur_area + -1;
              if (this->cur_area < 0) {
                this->cur_area = this->area_count + -1;
              }
            }
            JRing::AreaOverCheckInit(this,this->cur_area);
            if (this->auto_mode == 3) {
              if (((ulong)this->flagsB & 0xf) >> 2 == 3) {
                JRing::JRingAutoInit(this,this + 0x460,0,1);
              }
              else if ((long)((ulong)this->flagsC << 0x3d) < 0) {
                JRing::JRingAutoInit
                          (this,this + this->cur_area * 0x24 + 0x2b0,
                           this + iVar4 * 0x24 + 0x2b0,1);
              }
              else {
                JRing::JRingAutoInit
                          (this,this + this->cur_area * 0x24 + 0x100,
                           this + iVar4 * 0x24 + 0x100,1);
              }
            }
            this->anim_a = 0;
          }
          else {
            fVar13 = (360.0 / this->period) * this->dt;
            if (fVar13 < 0.0) {
              fVar13 = fVar13 * -1.0;
            }
            this->anim_a = this->anim_a + fVar13;
            if (7.5 <= this->anim_a) {
              if ((this->cb_fn != 0) &&
                 ((long)((ulong)this->cb_mask << 0x3b) < 0)) {
                (**(code **)(this + 0xf8))(0x10,0,this->cb_user);
              }
              HNMSnd::PlaySE(HNMSnd::sys,0x2007,1,0);
              this->flagsB = this->flagsB & 0x7f;
              this->flagsC = this->flagsC & 0xfe;
              if (this->hits == 0) {
                this->res_flags = this->res_flags & 0xf9;
              }
              else {
                this->res_flags = this->res_flags & 0xf9 | 2;
              }
              lVar7 = __nw(0xb0);
              if (lVar7 != 0) {
                HitMes::HitMes(lVar7,this,0,1);
              }
              this->state = 6;
              this->sub = 0;
              this->wait = 0x3f800000;
              break;
            }
          }
        }
        this->prev_angle = this->cur_angle;
        this->cur_angle =
             this->cur_angle +
             (360.0 / this->period) * this->dt;
        if (this->cur_angle < -180.0) {
          this->cur_angle = this->cur_angle + 360.0;
        }
        if (180.0 < this->cur_angle) {
          this->cur_angle = this->cur_angle - 360.0;
        }
        if (0.0 <= this->period) {
          this->period =
               this->period +
               this->accel * this->dt * 60.0;
        }
        else {
          this->period =
               this->period -
               this->accel * this->dt * 60.0;
        }
        if ((((long)((ulong)this->abn_d << 0x3a) < 0) &&
            (this->wobble_target != 0.0)) && (this->wobble_step != 0.0)) {
          this->period = this->period - this->wobble_cur;
          if (this->wobble_cur < this->wobble_target) {
            this->wobble_cur = this->wobble_cur + this->wobble_step;
            if (this->wobble_target <= this->wobble_cur) {
              this->wobble_cur = this->wobble_target;
              this->wobble_target = 0;
              this->wobble_step = 0;
            }
          }
          else {
            this->wobble_cur = this->wobble_cur + this->wobble_step;
            if (this->wobble_cur <= this->wobble_target) {
              this->wobble_cur = this->wobble_target;
              this->wobble_target = 0;
              this->wobble_step = 0;
            }
          }
          this->period = this->period + this->wobble_cur;
        }
        else if ((long)((ulong)this->abn_d << 0x39) < 0) {
          this->period = this->period - this->wobble_cur;
          if (this->wobble_cur < this->wobble_target) {
            this->wobble_cur = this->wobble_cur + this->wobble_step;
            if (this->wobble_target <= this->wobble_cur) {
              this->wobble_cur = this->wobble_target;
              iVar4 = rand();
              this->wobble_target =
                   this->wobble_amp * ((float)iVar4 / 2.1474836e+09) * 2.0 -
                   this->wobble_amp;
              iVar4 = rand();
              this->wobble_step =
                   (this->wobble_target - this->wobble_cur) /
                   (((float)iVar4 / 2.1474836e+09) * 20.0 + 3.0);
            }
          }
          else {
            this->wobble_cur = this->wobble_cur + this->wobble_step;
            if (this->wobble_cur <= this->wobble_target) {
              this->wobble_cur = this->wobble_target;
              iVar4 = rand();
              this->wobble_target =
                   this->wobble_amp * ((float)iVar4 / 2.1474836e+09) * 2.0 -
                   this->wobble_amp;
              iVar4 = rand();
              this->wobble_step =
                   (this->wobble_target - this->wobble_cur) /
                   (((float)iVar4 / 2.1474836e+09) * 20.0 + 3.0);
            }
          }
          this->period = this->period + this->wobble_cur;
        }
        if (0.0 <= this->period) {
          if ((this->prev_angle < 0.0) && (0.0 <= this->cur_angle)) {
            this->laps_done = this->laps_done + 1;
            this->period = this->period + this->lap_add;
            this->period = this->period * this->lap_mul;
            if ((long)((ulong)this->abn_d << 0x3a) < 0) {
              iVar4 = rand();
              this->wobble_target =
                   this->wobble_amp * ((float)iVar4 / 2.1474836e+09) * 2.0 -
                   this->wobble_amp;
              this->wobble_step =
                   (this->wobble_target - this->wobble_cur) / 5.0;
            }
            this->flagsD = this->flagsD & 0xfe;
          }
        }
        else if ((0.0 < this->prev_angle) && (this->cur_angle <= 0.0)) {
          this->laps_done = this->laps_done + 1;
          this->period = this->period - this->lap_add;
          this->period = this->period * this->lap_mul;
          if ((long)((ulong)this->abn_d << 0x3a) < 0) {
            iVar4 = rand();
            this->wobble_target =
                 this->wobble_amp * ((float)iVar4 / 2.1474836e+09) * 2.0 -
                 this->wobble_amp;
            this->wobble_step =
                 (this->wobble_target - this->wobble_cur) / 5.0;
          }
          this->flagsD = this->flagsD & 0xfe;
        }
        bVar1 = false;
        if (((ulong)this->flagsB & 0xf) >> 2 == 3) {
          if (0 < this->laps_done) {
            bVar1 = true;
          }
        }
        else if ((this->laps_allowed != 0) &&
                (this->laps_allowed <= this->laps_done)) {
          bVar1 = true;
        }
        if (bVar1) {
          if ((this->cb_fn != 0) &&
             ((long)((ulong)this->cb_mask << 0x3a) < 0)) {
            (**(code **)(this + 0xf8))(0x20,0,this->cb_user);
          }
          HNMSnd::PlaySE(HNMSnd::sys,0x2007,1,0);
          this->flagsB = this->flagsB & 0x7f;
          this->flagsC = this->flagsC & 0xfe;
          lVar7 = __nw(0xb0);
          if (lVar7 != 0) {
            HitMes::HitMes(lVar7,this,0,1);
          }
          if (this->hits == 0) {
            this->res_flags = this->res_flags & 0xf9;
          }
          else {
            this->res_flags = this->res_flags & 0xf9 | 2;
          }
          this->state = 6;
          this->sub = 0;
          this->wait = 0x3f800000;
        }
        else if (0.0 <= this->period) {
          if (this->period < 0.53333336) {
            this->period = 0x3f088889;
          }
          if (4.8 < this->period) {
            this->period = 0x4099999a;
          }
        }
        else {
          this->period = this->period * -1.0;
          if (this->period < 0.53333336) {
            this->period = 0x3f088889;
          }
          if (4.8 < this->period) {
            this->period = 0x4099999a;
          }
          this->period = this->period * -1.0;
        }
      }
      else if (this->sub == 0) {
        this->flagsB = this->flagsB & 0x7f | 0x80;
        this->flagsC = this->flagsC & 0xfe | 1;
        if (0.0 <= this->period) {
          this->cur_area = 0;
        }
        else {
          this->cur_area = this->area_count + -1;
        }
        if ((long)((ulong)this->abn_d << 0x3a) < 0) {
          this->wobble_target = 0;
          this->wobble_step = 0;
          iVar4 = rand();
          this->wobble_cur =
               this->wobble_amp * ((float)iVar4 / 2.1474836e+09) * 2.0 -
               this->wobble_amp;
        }
        else if ((long)((ulong)this->abn_d << 0x39) < 0) {
          iVar4 = rand();
          this->wobble_target =
               this->wobble_amp * ((float)iVar4 / 2.1474836e+09) * 2.0 -
               this->wobble_amp;
          iVar4 = rand();
          this->wobble_step =
               this->wobble_target / (((float)iVar4 / 2.1474836e+09) * 10.0 + 3.0);
          this->wobble_cur = 0;
        }
        this->inside_at_start = 0;
        JRing::AreaOverCheckInit(this,this->cur_area);
        if (this->auto_mode == 3) {
          if (((ulong)this->flagsB & 0xf) >> 2 == 3) {
            JRing::JRingAutoInit(this,this + 0x460,0,0);
          }
          else if ((long)((ulong)this->flagsC << 0x3d) < 0) {
            JRing::JRingAutoInit
                      (this,this + this->cur_area * 0x24 + 0x2b0,0,0);
          }
          else {
            JRing::JRingAutoInit
                      (this,this + this->cur_area * 0x24 + 0x100,0,0);
          }
        }
        this->anim_a = 0;
        this->sub = 1;
      }
      break;
    case 2:
    case 3:
    case 4:
      if (this->sub == 1) {
        if ((*(ushort *)((&CPad::m_pCoreArray)[JRing::Pad->i32_4] + 0x6c) & 0xf000) == 0) {
LAB_002c48e0:
          cVar2 = JRing::AreaOverCheck(this);
          if (cVar2 == '\0') {
            fVar13 = (360.0 / this->period) * this->dt;
            if (fVar13 < 0.0) {
              fVar13 = fVar13 * -1.0;
            }
            this->anim_a = this->anim_a + fVar13;
            if (7.5 <= this->anim_a) {
              if ((this->cb_fn != 0) &&
                 ((long)((ulong)this->cb_mask << 0x3b) < 0)) {
                (**(code **)(this + 0xf8))(0x10,0,this->cb_user);
              }
              HNMSnd::PlaySE(HNMSnd::sys,0x2007,1,0);
              this->flagsB = this->flagsB & 0x7f;
              this->flagsC = this->flagsC & 0xfe;
              if (this->hits == 0) {
                this->res_flags = this->res_flags & 0xf9;
              }
              else {
                this->res_flags = this->res_flags & 0xf9 | 2;
              }
              sVar11 = this->ring_type;
              if (sVar11 == 3) {
                if (this->area_count == 0) {
                  trap(7);
                }
                this->event_value = this->hits / this->area_count;
              }
              else if ((sVar11 == 4) || (sVar11 == 2)) {
                this->event_value = this->hits;
              }
              lVar7 = __nw(0xb0);
              if (lVar7 != 0) {
                HitMes::HitMes(lVar7,this,0,1);
              }
              this->state = 6;
              this->sub = 0;
              this->wait = 0x3f800000;
              break;
            }
          }
          this->prev_angle = this->cur_angle;
          this->cur_angle =
               this->cur_angle +
               (360.0 / this->period) * this->dt;
          if (this->cur_angle < -180.0) {
            this->cur_angle = this->cur_angle + 360.0;
          }
          if (180.0 < this->cur_angle) {
            this->cur_angle = this->cur_angle - 360.0;
          }
          if (0.0 <= this->period) {
            this->period =
                 this->period +
                 this->accel * this->dt * 60.0;
          }
          else {
            this->period =
                 this->period -
                 this->accel * this->dt * 60.0;
          }
          if ((((long)((ulong)this->abn_d << 0x3a) < 0) &&
              (this->wobble_target != 0.0)) && (this->wobble_step != 0.0)) {
            this->period = this->period - this->wobble_cur;
            if (this->wobble_cur < this->wobble_target) {
              this->wobble_cur = this->wobble_cur + this->wobble_step;
              if (this->wobble_target <= this->wobble_cur) {
                this->wobble_cur = this->wobble_target;
                this->wobble_target = 0;
                this->wobble_step = 0;
              }
            }
            else {
              this->wobble_cur = this->wobble_cur + this->wobble_step;
              if (this->wobble_cur <= this->wobble_target) {
                this->wobble_cur = this->wobble_target;
                this->wobble_target = 0;
                this->wobble_step = 0;
              }
            }
            this->period = this->period + this->wobble_cur;
          }
          else if ((long)((ulong)this->abn_d << 0x39) < 0) {
            this->period = this->period - this->wobble_cur;
            if (this->wobble_cur < this->wobble_target) {
              this->wobble_cur = this->wobble_cur + this->wobble_step;
              if (this->wobble_target <= this->wobble_cur) {
                this->wobble_cur = this->wobble_target;
                iVar4 = rand();
                this->wobble_target =
                     this->wobble_amp * ((float)iVar4 / 2.1474836e+09) * 2.0 -
                     this->wobble_amp;
                iVar4 = rand();
                this->wobble_step =
                     (this->wobble_target - this->wobble_cur) /
                     (((float)iVar4 / 2.1474836e+09) * 20.0 + 3.0);
              }
            }
            else {
              this->wobble_cur = this->wobble_cur + this->wobble_step;
              if (this->wobble_cur <= this->wobble_target) {
                this->wobble_cur = this->wobble_target;
                iVar4 = rand();
                this->wobble_target =
                     this->wobble_amp * ((float)iVar4 / 2.1474836e+09) * 2.0 -
                     this->wobble_amp;
                iVar4 = rand();
                this->wobble_step =
                     (this->wobble_target - this->wobble_cur) /
                     (((float)iVar4 / 2.1474836e+09) * 20.0 + 3.0);
              }
            }
            this->period = this->period + this->wobble_cur;
          }
          if (0.0 <= this->period) {
            if ((this->prev_angle < 0.0) && (0.0 <= this->cur_angle)) {
              this->laps_done = this->laps_done + 1;
              this->period = this->period + this->lap_add;
              this->period = this->period * this->lap_mul;
              if ((long)((ulong)this->abn_d << 0x3a) < 0) {
                iVar4 = rand();
                this->wobble_target =
                     this->wobble_amp * ((float)iVar4 / 2.1474836e+09) * 2.0 -
                     this->wobble_amp;
                this->wobble_step =
                     (this->wobble_target - this->wobble_cur) / 5.0;
              }
              this->flagsD = this->flagsD & 0xfe;
            }
          }
          else if ((0.0 < this->prev_angle) && (this->cur_angle <= 0.0)) {
            this->laps_done = this->laps_done + 1;
            this->period = this->period - this->lap_add;
            this->period = this->period * this->lap_mul;
            if ((long)((ulong)this->abn_d << 0x3a) < 0) {
              iVar4 = rand();
              this->wobble_target =
                   this->wobble_amp * ((float)iVar4 / 2.1474836e+09) * 2.0 -
                   this->wobble_amp;
              this->wobble_step =
                   (this->wobble_target - this->wobble_cur) / 5.0;
            }
            this->flagsD = this->flagsD & 0xfe;
          }
          if (this->laps_done < this->laps_allowed) {
            if (0.0 <= this->period) {
              if (this->period < 0.53333336) {
                this->period = 0x3f088889;
              }
              if (4.8 < this->period) {
                this->period = 0x4099999a;
              }
            }
            else {
              this->period = this->period * -1.0;
              if (this->period < 0.53333336) {
                this->period = 0x3f088889;
              }
              if (4.8 < this->period) {
                this->period = 0x4099999a;
              }
              this->period = this->period * -1.0;
            }
          }
          else {
            if ((this->cb_fn != 0) &&
               ((long)((ulong)this->cb_mask << 0x3a) < 0)) {
              (**(code **)(this + 0xf8))(0x20,0,this->cb_user);
            }
            HNMSnd::PlaySE(HNMSnd::sys,0x2007,1,0);
            this->flagsB = this->flagsB & 0x7f;
            this->flagsC = this->flagsC & 0xfe;
            sVar11 = this->ring_type;
            if (sVar11 == 3) {
              if (this->area_count == 0) {
                trap(7);
              }
              this->event_value = this->hits / this->area_count;
            }
            else if ((sVar11 == 4) || (sVar11 == 2)) {
              this->event_value = this->hits;
            }
            lVar7 = __nw(0xb0);
            if (lVar7 != 0) {
              HitMes::HitMes(lVar7,this,0,1);
            }
            if (this->hits == 0) {
              this->res_flags = this->res_flags & 0xf9;
            }
            else {
              this->res_flags = this->res_flags & 0xf9 | 2;
            }
            this->state = 6;
            this->sub = 0;
            this->wait = 0x3f800000;
          }
        }
        else {
          if ((long)((ulong)this->flagsC << 0x3d) < 0) {
            lVar7 = JRing::HitCheck
                              (this,this + this->cur_area * 0x24 + 0x2b0);
          }
          else {
            lVar7 = JRing::HitCheck
                              (this,this + this->cur_area * 0x24 + 0x100);
          }
          if ((this->flagsD & 1) != 0) {
            lVar7 = -1;
          }
          if (lVar7 < 0) {
            HNMSnd::PlaySE(HNMSnd::sys,0x2007,1,0);
            if ((this->cb_fn != 0) &&
               ((long)((ulong)this->cb_mask << 0x3c) < 0)) {
              (**(code **)(this + 0xf8))(8,0,this->cb_user);
            }
            lVar7 = __nw(0xb0);
            if (lVar7 != 0) {
              HitMes::HitMes(lVar7,this,0,1);
            }
            if (this->hits == 0) {
              this->res_flags = this->res_flags & 0xf9;
            }
            else {
              this->res_flags = this->res_flags & 0xf9 | 2;
            }
            sVar11 = this->ring_type;
            if (sVar11 == 3) {
              if (this->area_count == 0) {
                trap(7);
              }
              this->event_value = this->hits / this->area_count;
            }
            else if ((sVar11 == 4) || (sVar11 == 2)) {
              this->event_value = this->hits;
            }
            this->state = 6;
            this->sub = 0;
            this->wait = 0x3f800000;
          }
          else {
            if ((long)((ulong)this->flagsC << 0x3d) < 0) {
              iVar4 = this + this->cur_area * 0x24 + 0x2b0;
            }
            else {
              iVar4 = this + this->cur_area * 0x24 + 0x100;
            }
            iVar4->u8_1 = iVar4->u8_1 & 0xf9 | 6;
            iVar4->u32_20 = 0x3f800000;
            lVar6 = __nw(0x70);
            if (lVar6 != 0) {
              HitArea::HitArea
                        ((float)(int)iVar4->i16_4,(float)(int)iVar4->i16_6,lVar6,
                         this,iVar4 + 0xc);
            }
            if ((this->cb_fn != 0) &&
               ((long)((ulong)this->cb_mask << 0x3d) < 0)) {
              (**(code **)(this + 0xf8))(4,0,this->cb_user);
            }
            if (lVar7 == 100) {
              uVar3 = this->hits & 3;
              if (((int)this->hits < 0) && (uVar3 != 0)) {
                uVar3 = uVar3 - 4;
              }
              iVar10 = this + (this->hits >> 2);
              iVar10->u8_528 =
                   iVar10->u8_528 | (byte)(1 << ((uVar3 & 0xf) << 1));
              this->res_percent = 10000;
            }
            else if (lVar7 < 100) {
              uVar3 = this->hits & 3;
              if (((int)this->hits < 0) && (uVar3 != 0)) {
                uVar3 = uVar3 - 4;
              }
              iVar10 = this + (this->hits >> 2);
              iVar10->u8_528 =
                   iVar10->u8_528 | (byte)(2 << ((uVar3 & 0xf) << 1));
              this->res_percent = (int)lVar7 * 100;
            }
            else {
              uVar3 = this->hits & 3;
              if (((int)this->hits < 0) && (uVar3 != 0)) {
                uVar3 = uVar3 - 4;
              }
              iVar10 = this + (this->hits >> 2);
              iVar10->u8_528 =
                   iVar10->u8_528 | (byte)(3 << ((uVar3 & 0xf) << 1));
              this->res_percent = 10000;
            }
            this->res_hit_count = this->res_hit_count + 1;
            this->hits = this->hits + 1;
            if (this->hits < this->result_total) {
              uVar5 = HitStopAngle(this->cur_angle,iVar4);
              HNMSnd::PlaySE(HNMSnd::sys,0x2004,1,0);
              lVar7 = __nw(0x60);
              if (lVar7 != 0) {
                HitBar::HitBar(uVar5,lVar7,this);
              }
              lVar7 = __nw(0xb0);
              if (lVar7 != 0) {
                HitMes::HitMes(lVar7,this,iVar4,0);
              }
              iVar4 = this->cur_area;
              if (0.0 <= this->period) {
                this->cur_area = this->cur_area + 1;
                if ((0xb < this->cur_area) ||
                   (*(char *)(this + this->cur_area * 0x24 + 0x102) == -1)) {
                  this->cur_area = 0;
                }
              }
              else {
                this->cur_area = this->cur_area + -1;
                if (this->cur_area < 0) {
                  this->cur_area = this->area_count + -1;
                }
              }
              if (iVar4 == this->cur_area) {
                this->flagsD = this->flagsD & 0xfe | 1;
              }
              JRing::AreaOverCheckInit(this,this->cur_area);
              this->anim_a = 0;
              goto LAB_002c48e0;
            }
            if ((long)this->res_hit_count < (long)this->result_total) {
              this->res_flags = this->res_flags & 0xf9 | 2;
            }
            else {
              this->res_flags = this->res_flags & 0xf9 | 4;
            }
            uVar5 = HitStopAngle(this->cur_angle,iVar4);
            this->cur_angle = uVar5;
            HNMSnd::PlaySE(HNMSnd::sys,0x2004,1,0);
            lVar7 = __nw(0xb0);
            if (lVar7 != 0) {
              HitMes::HitMes(lVar7,this,iVar4,0);
            }
            sVar11 = this->ring_type;
            if (sVar11 == 3) {
              if (this->area_count == 0) {
                trap(7);
              }
              this->event_value = this->hits / this->area_count;
            }
            else if ((sVar11 == 4) || (sVar11 == 2)) {
              this->event_value = this->hits;
            }
            this->state = 7;
            this->sub = 0;
            this->wait = 0x3f000000;
          }
        }
      }
      else if (this->sub == 0) {
        if (0.0 <= this->period) {
          this->cur_area = 0;
        }
        else {
          this->cur_area = this->area_count + -1;
        }
        if ((long)((ulong)this->abn_d << 0x3a) < 0) {
          this->wobble_target = 0;
          this->wobble_step = 0;
          iVar4 = rand();
          this->wobble_cur =
               this->wobble_amp * ((float)iVar4 / 2.1474836e+09) * 2.0 -
               this->wobble_amp;
        }
        else if ((long)((ulong)this->abn_d << 0x39) < 0) {
          iVar4 = rand();
          this->wobble_target =
               this->wobble_amp * ((float)iVar4 / 2.1474836e+09) * 2.0 -
               this->wobble_amp;
          iVar4 = rand();
          this->wobble_step =
               this->wobble_target / (((float)iVar4 / 2.1474836e+09) * 10.0 + 3.0);
          this->wobble_cur = 0;
        }
        this->inside_at_start = 0;
        JRing::AreaOverCheckInit(this,this->cur_area);
        this->anim_a = 0;
        this->sub = 1;
      }
      break;
    case 5:
      sVar11 = this->sub;
      if (sVar11 == 2) {
        this->prev_angle = this->cur_angle;
        bVar1 = false;
        if (0.0 <= this->period) {
          this->anim_b =
               (360.0 / this->period) * this->dt;
          this->anim_c = this->anim_a / 50.0;
          if (this->anim_c < 0.2) {
            this->anim_c = 0x3e4ccccd;
          }
          if (this->anim_c < this->anim_b) {
            this->anim_b = this->anim_c;
          }
          this->cur_angle = this->cur_angle + this->anim_b;
          this->anim_a = this->anim_a - this->anim_b;
          if (this->anim_a < 0.1) {
            this->cur_angle = this->cur_angle + this->anim_a;
            bVar1 = true;
          }
        }
        else {
          this->anim_b =
               (360.0 / this->period) * this->dt * -1.0;
          this->anim_c = this->anim_a / 50.0;
          if (this->anim_c < 0.2) {
            this->anim_c = 0x3e4ccccd;
          }
          if (this->anim_c < this->anim_b) {
            this->anim_b = this->anim_c;
          }
          this->cur_angle = this->cur_angle - this->anim_b;
          this->anim_a = this->anim_a - this->anim_b;
          if (this->anim_a < 0.1) {
            this->cur_angle = this->cur_angle - this->anim_a;
            bVar1 = true;
          }
        }
        if (this->cur_angle < -180.0) {
          this->cur_angle = this->cur_angle + 360.0;
        }
        if (180.0 < this->cur_angle) {
          this->cur_angle = this->cur_angle - 360.0;
        }
        if (bVar1) {
          if ((long)((ulong)this->flagsC << 0x3d) < 0) {
            lVar7 = JRing::HitCheck(this,this + 0x2b0);
            if (-1 < lVar7) {
              iVar4 = this + (int)lVar7 * 0x24;
              unaff_s1_lo = iVar4 + 0x2b0;
              lVar7 = (long)iVar4->i16_2c8;
              iVar4->u8_2b1 = iVar4->u8_2b1 & 0xf9 | 6;
              iVar4->u32_2d0 = 0x3f800000;
              lVar6 = __nw(0x70);
              if (lVar6 != 0) {
                HitArea::HitArea
                          ((float)(int)iVar4->i16_2b4,
                           (float)(int)iVar4->i16_2b6,lVar6,this,iVar4 + 700);
              }
            }
          }
          else {
            lVar7 = JRing::HitCheck(this,this + 0x100);
            if (-1 < lVar7) {
              iVar4 = this + (int)lVar7 * 0x24;
              unaff_s1_lo = iVar4 + 0x100;
              lVar7 = (long)iVar4->i16_118;
              iVar4->u8_101 = iVar4->u8_101 & 0xf9 | 6;
              iVar4->u32_120 = 0x3f800000;
              lVar6 = __nw(0x70);
              if (lVar6 != 0) {
                HitArea::HitArea
                          ((float)(int)iVar4->i16_104,
                           (float)(int)iVar4->i16_106,lVar6,this,iVar4 + 0x10c);
              }
            }
          }
          this->res_flags = this->res_flags & 0xf9 | 4;
          this->i8_528 = (char)lVar7;
          this->res_hit_count = 1;
          if (lVar7 < 0) {
            this->event_value = 0;
            lVar7 = __nw(0xb0);
            if (lVar7 != 0) {
              HitMes::HitMes(lVar7,this,0,1);
            }
            HNMSnd::SetSEEnd(HNMSnd::sys,0x3000000,0xffffffffffffffff);
            HNMSnd::PlaySE(HNMSnd::sys,0x3000001,1,0);
          }
          else {
            this->event_value = (int)lVar7;
            lVar7 = __nw(0xb0);
            if (lVar7 != 0) {
              HitMes::HitMes(lVar7,this,unaff_s1_lo,0);
            }
            HNMSnd::SetSEEnd(HNMSnd::sys,0x3000000,0xffffffffffffffff);
            HNMSnd::PlaySE(HNMSnd::sys,0x3000001,1,0);
          }
          this->state = 7;
          this->sub = 0;
          this->wait = 0x3f000000;
        }
      }
      else if (sVar11 == 1) {
        if ((*(ushort *)((&CPad::m_pCoreArray)[JRing::Pad->i32_4] + 0x6c) & 0xf000) == 0) {
          this->prev_angle = this->cur_angle;
          this->cur_angle =
               this->cur_angle +
               (360.0 / this->period) * this->dt;
          if (this->cur_angle < -180.0) {
            this->cur_angle = this->cur_angle + 360.0;
          }
          if (180.0 < this->cur_angle) {
            this->cur_angle = this->cur_angle - 360.0;
          }
          if (0.0 <= this->period) {
            this->period =
                 this->period +
                 this->accel * this->dt * 60.0;
          }
          else {
            this->period =
                 this->period -
                 this->accel * this->dt * 60.0;
          }
          if ((((long)((ulong)this->abn_d << 0x3a) < 0) &&
              (this->wobble_target != 0.0)) && (this->wobble_step != 0.0)) {
            this->period = this->period - this->wobble_cur;
            if (this->wobble_cur < this->wobble_target) {
              this->wobble_cur = this->wobble_cur + this->wobble_step;
              if (this->wobble_target <= this->wobble_cur) {
                this->wobble_cur = this->wobble_target;
                this->wobble_target = 0;
                this->wobble_step = 0;
              }
            }
            else {
              this->wobble_cur = this->wobble_cur + this->wobble_step;
              if (this->wobble_cur <= this->wobble_target) {
                this->wobble_cur = this->wobble_target;
                this->wobble_target = 0;
                this->wobble_step = 0;
              }
            }
            this->period = this->period + this->wobble_cur;
          }
          else if ((long)((ulong)this->abn_d << 0x39) < 0) {
            this->period = this->period - this->wobble_cur;
            if (this->wobble_cur < this->wobble_target) {
              this->wobble_cur = this->wobble_cur + this->wobble_step;
              if (this->wobble_target <= this->wobble_cur) {
                this->wobble_cur = this->wobble_target;
                iVar4 = rand();
                this->wobble_target =
                     this->wobble_amp * ((float)iVar4 / 2.1474836e+09) * 2.0 -
                     this->wobble_amp;
                iVar4 = rand();
                this->wobble_step =
                     (this->wobble_target - this->wobble_cur) /
                     (((float)iVar4 / 2.1474836e+09) * 20.0 + 3.0);
              }
            }
            else {
              this->wobble_cur = this->wobble_cur + this->wobble_step;
              if (this->wobble_cur <= this->wobble_target) {
                this->wobble_cur = this->wobble_target;
                iVar4 = rand();
                this->wobble_target =
                     this->wobble_amp * ((float)iVar4 / 2.1474836e+09) * 2.0 -
                     this->wobble_amp;
                iVar4 = rand();
                this->wobble_step =
                     (this->wobble_target - this->wobble_cur) /
                     (((float)iVar4 / 2.1474836e+09) * 20.0 + 3.0);
              }
            }
            this->period = this->period + this->wobble_cur;
          }
          if (0.0 <= this->period) {
            if ((this->prev_angle < 0.0) && (0.0 <= this->cur_angle)) {
              this->laps_done = this->laps_done + 1;
              this->period = this->period + this->lap_add;
              this->period = this->period * this->lap_mul;
              if ((long)((ulong)this->abn_d << 0x3a) < 0) {
                iVar4 = rand();
                this->wobble_target =
                     this->wobble_amp * ((float)iVar4 / 2.1474836e+09) * 2.0 -
                     this->wobble_amp;
                this->wobble_step =
                     (this->wobble_target - this->wobble_cur) / 5.0;
              }
            }
          }
          else if ((0.0 < this->prev_angle) && (this->cur_angle <= 0.0)) {
            this->laps_done = this->laps_done + 1;
            this->period = this->period - this->lap_add;
            this->period = this->period * this->lap_mul;
            if ((long)((ulong)this->abn_d << 0x3a) < 0) {
              iVar4 = rand();
              this->wobble_target =
                   this->wobble_amp * ((float)iVar4 / 2.1474836e+09) * 2.0 -
                   this->wobble_amp;
              this->wobble_step =
                   (this->wobble_target - this->wobble_cur) / 5.0;
            }
          }
          if (0.0 <= this->period) {
            if (this->period < 0.53333336) {
              this->period = 0x3f088889;
            }
            if (4.8 < this->period) {
              this->period = 0x4099999a;
            }
          }
          else {
            this->period = this->period * -1.0;
            if (this->period < 0.53333336) {
              this->period = 0x3f088889;
            }
            if (4.8 < this->period) {
              this->period = 0x4099999a;
            }
            this->period = this->period * -1.0;
          }
        }
        else {
          this->anim_a = 0x43b40000;
          this->sub = 2;
          if ((this->cb_fn != 0) &&
             ((long)((ulong)this->cb_mask << 0x3d) < 0)) {
            (**(code **)(this + 0xf8))(4,0,this->cb_user);
          }
        }
      }
      else if (sVar11 == 0) {
        if ((long)((ulong)this->abn_d << 0x3a) < 0) {
          iVar4 = rand();
          this->wobble_cur =
               this->wobble_amp * ((float)iVar4 / 2.1474836e+09) * 2.0 -
               this->wobble_amp;
          this->wobble_target = 0;
          this->wobble_step = 0;
        }
        else if ((long)((ulong)this->abn_d << 0x39) < 0) {
          iVar4 = rand();
          this->wobble_target =
               this->wobble_amp * ((float)iVar4 / 2.1474836e+09) * 2.0 -
               this->wobble_amp;
          iVar4 = rand();
          this->wobble_step =
               this->wobble_target / (((float)iVar4 / 2.1474836e+09) * 10.0 + 3.0);
          this->wobble_cur = 0;
        }
        this->anim_a = 0;
        this->sub = 1;
      }
      break;
    case 6:
      this->f32_78 =
           this->f32_78 +
           (6.2831855 / this->period) * this->dt;
      while (3.1415927 <= this->f32_78) {
        this->f32_78 = this->f32_78 - 6.2831855;
      }
    }
    if (((this->state == 6) || (this->state == 7)) ||
       (this->state == 8)) {
      HNMSnd::SetSEEnd(HNMSnd::sys,0x2001,0xffffffffffffffff);
      JRing::MakeResult(this);
    }
    else if (this->state == 5) {
      HNMSnd::SetSEEnd(HNMSnd::sys,0x2001,0xffffffffffffffff);
    }
    break;
  case 5:
    sVar11 = this->sub;
    if (sVar11 == 2) {
      this->f32_70 =
           this->f32_70 - this->f32_70 * this->dt * 2.0;
      if (this->auto_mode == 9) {
        sVar11 = this->auto_sub;
        if (sVar11 == 2) {
          this->f32_74 =
               this->f32_74 +
               (6.2831855 / this->combo_spin) * this->dt;
        }
        else if ((sVar11 != 1) && (sVar11 == 0)) {
          fVar13 = this->f32_74 +
                   (6.2831855 / this->combo_spin) * this->dt;
          if ((0.0 <= this->f32_74) || (fVar13 == 0.0)) {
            this->f32_74 = fVar13;
          }
          else {
            this->u32_74 = 0;
            this->auto_sub = 1;
          }
        }
      }
      else {
        this->f32_74 =
             this->f32_74 +
             (6.2831855 / this->combo_spin) * this->dt;
      }
      if (3.1415927 <= this->f32_74) {
        this->f32_74 = this->f32_74 - 6.2831855;
      }
      bVar1 = false;
      if (((-1.5707964 < this->f32_70) && (this->f32_70 < 1.5707964)) ||
         ((this->f32_74 <= -1.5707964 || (1.5707964 <= this->f32_74)))) {
        if ((((this->f32_74 <= -1.5707964) || (1.5707964 <= this->f32_74))
            && (-1.5707964 < this->f32_70)) && (this->f32_70 < 1.5707964))
        {
          bVar1 = true;
        }
      }
      else {
        bVar1 = true;
      }
      this->flagsA = this->flagsA & 0x9f | 0x60;
      if (this->flip == 0) {
        if (bVar1) {
          this->flip = 1;
          this->flagsB = this->flagsB & 0xfe;
          this->flagsB = this->flagsB & 0xfd;
          this->flagsA = this->flagsA & 0xf9 | 6;
        }
      }
      else if (!bVar1) {
        this->flip = 2;
      }
      if ((this->flip < 2) || (bVar1)) {
        this->e8 = 1;
      }
      else {
        this->e8 = this->combo_button + 2;
      }
      if ((this->auto_mode != 9) || (this->auto_sub != 1)) {
        this->anim_b = this->anim_b + this->dt;
      }
      uVar8 = *(ushort *)((&CPad::m_pCoreArray)[JRing::Pad->i32_4] + 0x6c);
      bVar1 = false;
      if (this->auto_mode == 0) {
        if ((uVar8 & 0xf000) != 0) {
          bVar1 = true;
          uVar8 = uVar8 & 0xf000;
        }
      }
      else {
        cVar2 = JRing::JRingAuto(this);
        if (cVar2 == '\x01') {
          iVar4 = this->combo_button;
          if (iVar4 == 3) {
            uVar8 = 0x8000;
          }
          else if (iVar4 == 2) {
            uVar8 = 0x1000;
          }
          else if (iVar4 == 1) {
            uVar8 = 0x4000;
          }
          else if (iVar4 == 0) {
            uVar8 = 0x2000;
          }
          bVar1 = true;
        }
      }
      if (bVar1) {
        this->u32_74 = 0;
        this->e8 = this->combo_button + 2;
        if (((((this->combo_button == 0) && (uVar8 == 0x2000)) ||
             ((this->combo_button == 1 && (uVar8 == 0x4000)))) ||
            ((this->combo_button == 2 && (uVar8 == 0x1000)))) ||
           ((this->combo_button == 3 && (uVar8 == 0x8000)))) {
          if (this->trial_b == 0) {
            lVar7 = __nw(0xb0);
            uVar5 = 0;
            if (lVar7 != 0) {
              uVar5 = ComboTrial::ComboTrial(lVar7,this,1,3);
            }
            this->trial_b = uVar5;
          }
          this->res_flags = this->res_flags & 0xf7 | 8;
          if (this->trial_a != 0) {
            *(undefined4 *)(this->trial_a + 0x40) = 2;
          }
          if ((this->flagsC & 1) == 0) {
            HNMSnd::PlaySE(HNMSnd::sys,0x2004,1,0);
            this->state = 7;
            this->sub = 0;
          }
          else {
            HNMSnd::PlaySE(HNMSnd::sys,0x2005,1,0);
            this->state = 8;
            this->sub = 0;
          }
        }
        else {
          if (((ulong)this->flagsB & 0xf) >> 2 == 1) goto LAB_002c6e88;
          this->flagsC = this->flagsC & 0xdf | 0x20;
          if (this->trial_b == 0) {
            lVar7 = __nw(0xb0);
            uVar5 = 0;
            if (lVar7 != 0) {
              uVar5 = ComboTrial::ComboTrial(lVar7,this,2,2);
            }
            this->trial_b = uVar5;
          }
          if (this->trial_a != 0) {
            *(undefined4 *)(this->trial_a + 0x40) = 2;
          }
          HNMSnd::PlaySE(HNMSnd::sys,0x2007,1,0);
          if ((this->flagsC & 1) == 0) {
            this->state = 7;
            this->sub = 0;
          }
          else {
            this->state = 8;
            this->sub = 0;
          }
        }
      }
      else {
LAB_002c6e88:
        if (this->combo_window < this->anim_b) {
          this->u32_74 = 0;
          this->e8 = this->combo_button + 2;
          this->flagsC = this->flagsC & 0xdf | 0x20;
          if (this->trial_b == 0) {
            lVar7 = __nw(0xb0);
            uVar5 = 0;
            if (lVar7 != 0) {
              uVar5 = ComboTrial::ComboTrial(lVar7,this,2,2);
            }
            this->trial_b = uVar5;
          }
          if (this->trial_a != 0) {
            *(undefined4 *)(this->trial_a + 0x40) = 2;
          }
          if ((this->flagsC & 1) == 0) {
            this->state = 7;
            this->sub = 0;
          }
          else {
            this->state = 8;
            this->sub = 0;
          }
        }
      }
    }
    else if (sVar11 == 1) {
      this->anim_a = this->anim_a + this->dt * 3.0;
      if (1.0 < this->anim_a) {
        this->anim_a = 0x3f800000;
      }
      this->combo_spin = 0.2 / this->anim_a;
      this->f32_70 =
           this->f32_70 - this->f32_70 * this->dt * 2.0;
      this->f32_74 =
           this->f32_74 +
           (6.2831855 / this->combo_spin) * this->dt;
      if (3.1415927 <= this->f32_74) {
        this->f32_74 = this->f32_74 - 6.2831855;
      }
      bVar1 = false;
      if ((((-1.5707964 < this->f32_70) && (this->f32_70 < 1.5707964)) ||
          (this->f32_74 <= -1.5707964)) || (1.5707964 <= this->f32_74)) {
        if (((this->f32_74 <= -1.5707964) || (1.5707964 <= this->f32_74))
           && ((-1.5707964 < this->f32_70 && (this->f32_70 < 1.5707964))))
        {
          bVar1 = true;
        }
      }
      else {
        bVar1 = true;
      }
      this->flagsA = this->flagsA & 0x9f | 0x60;
      if (this->flip == 0) {
        if (bVar1) {
          this->flip = 1;
          this->flagsB = this->flagsB & 0xfe;
          this->flagsB = this->flagsB & 0xfd;
          this->flagsA = this->flagsA & 0xf9 | 6;
        }
      }
      else if (!bVar1) {
        this->flip = 2;
      }
      if (this->anim_a == 1.0) {
        this->sub = 2;
      }
    }
    else if (sVar11 == 0) {
      JRing::JRingAutoInit(this,0,0,1);
      this->sub = 1;
      this->anim_a = 0;
      this->anim_b = 0;
      this->flip = 0;
      this->combo_spin = 0;
      this->res_flags = this->res_flags & 0xf7;
      this->res_flags = this->res_flags & 0xbf | 0x40;
      this->auto_sub = 0;
      HNMSnd::PlaySE(HNMSnd::sys,0x2000001,1,0);
    }
    if (((this->state == 6) || (this->state == 7)) ||
       (this->state == 8)) {
      JRing::MakeResult(this);
    }
    break;
  case 6:
  case 7:
  case 8:
    if (-1 < (long)((ulong)this->flagsC << 0x39)) {
      sVar11 = this->end_miss;
      if (this->state == 7) {
        sVar11 = this->end_ok;
      }
      else if (this->state == 8) {
        sVar11 = this->end_strike;
      }
      if (sVar11 == 4) {
        if (-1 < (long)((ulong)this->flagsB << 0x3a)) {
          this->scale_x = 0;
          if ((long)((ulong)this->flagsC << 0x3a) < 0) {
            lVar7 = __nw(0x2f0);
            uVar5 = 0;
            if (lVar7 != 0) {
              uVar5 = CutJRing::CutJRing(lVar7,this,1);
            }
            this->cut = uVar5;
          }
          else if (((long)((ulong)this->res_flags << 0x3c) < 0) ||
                  ((long)((ulong)this->flagsC << 0x38) < 0)) {
            lVar7 = __nw(0x2f0);
            uVar5 = 0;
            if (lVar7 != 0) {
              uVar5 = CutJRing::CutJRing(lVar7,this,2);
            }
            this->cut = uVar5;
          }
          else {
            lVar7 = __nw(0x2f0);
            uVar5 = 0;
            if (lVar7 != 0) {
              uVar5 = CutJRing::CutJRing(lVar7,this,0);
            }
            this->cut = uVar5;
          }
          this->flagsA = this->flagsA & 0xf9 | 6;
          this->flagsB = this->flagsB & 0xdf | 0x20;
          if (((long)((ulong)this->flagsC << 0x3a) < 0) ||
             ((-1 < (long)((ulong)this->res_flags << 0x3c) &&
              (-1 < (long)((ulong)this->flagsC << 0x38))))) {
            if ((this->cb_fn != 0) && ((this->u8_f1 & 1) != 0)) {
              (**(code **)(this + 0xf8))(0x100,0,this->cb_user);
            }
            HNMSnd::PlaySE(HNMSnd::sys,0x2003,1,0);
          }
          this->flip = 0;
        }
        if (((-1 < (long)((ulong)this->flagsC << 0x3a)) &&
            ((((long)((ulong)this->res_flags << 0x3c) < 0 ||
              ((long)((ulong)this->flagsC << 0x38) < 0)) &&
             (0.33333334 <= *(float *)(this->cut + 0x2c0))))) &&
           (this->flip == 0)) {
          if ((this->cb_fn != 0) && ((this->u8_f1 & 1) != 0)) {
            (**(code **)(this + 0xf8))(0x100,0,this->cb_user);
          }
          HNMSnd::PlaySE(HNMSnd::sys,0x2000002,1,0);
          this->flip = 1;
        }
        this->anim_a = this->anim_a + this->dt;
        if (((*(float *)(this->cut + 0x2b0) == 0.0) &&
            (this->trial_a == 0)) && (this->trial_b == 0)) {
          JRing::RingSleep(this);
        }
        if (((long)((ulong)this->flagsB << 0x3a) < 0) && (this->cut != 0)
           ) {
          CutJRing::Update(this->dt,this->cut);
        }
      }
      else if (sVar11 == 3) {
        if (-1 < (long)((ulong)this->flagsB << 0x3b)) {
          this->scale_x = 0;
          if ((long)((ulong)this->flagsC << 0x3a) < 0) {
            lVar7 = __nw(0x5a0);
            uVar5 = 0;
            if (lVar7 != 0) {
              uVar5 = CrackJRing::CrackJRing(lVar7,this,1,1);
            }
            this->crack = uVar5;
          }
          else if (((long)((ulong)this->res_flags << 0x3c) < 0) ||
                  ((long)((ulong)this->flagsC << 0x38) < 0)) {
            lVar7 = __nw(0x5a0);
            uVar5 = 0;
            if (lVar7 != 0) {
              uVar5 = CrackJRing::CrackJRing(lVar7,this,2,1);
            }
            this->crack = uVar5;
          }
          else {
            lVar7 = __nw(0x5a0);
            uVar5 = 0;
            if (lVar7 != 0) {
              uVar5 = CrackJRing::CrackJRing(lVar7,this,0,1);
            }
            this->crack = uVar5;
          }
          this->flagsA = this->flagsA & 0xf9 | 6;
          this->flagsB = this->flagsB & 0xef | 0x10;
          if (((long)((ulong)this->flagsC << 0x3a) < 0) ||
             ((-1 < (long)((ulong)this->res_flags << 0x3c) &&
              (-1 < (long)((ulong)this->flagsC << 0x38))))) {
            if ((this->cb_fn != 0) && ((this->u8_f1 & 1) != 0)) {
              (**(code **)(this + 0xf8))(0x100,0,this->cb_user);
            }
            HNMSnd::PlaySE(HNMSnd::sys,0x2006,1,0);
          }
          this->flip = 0;
        }
        if ((-1 < (long)((ulong)this->flagsC << 0x3a)) &&
           (((((long)((ulong)this->res_flags << 0x3c) < 0 ||
              ((long)((ulong)this->flagsC << 0x38) < 0)) &&
             (0.33333334 <= *(float *)(this->crack + 0x18))) &&
            (this->flip == 0)))) {
          if ((this->cb_fn != 0) && ((this->u8_f1 & 1) != 0)) {
            (**(code **)(this + 0xf8))(0x100,0,this->cb_user);
          }
          HNMSnd::PlaySE(HNMSnd::sys,0x2000002,1,0);
          this->flip = 1;
        }
        this->anim_a = this->anim_a + this->dt;
        if (((*(float *)(this->crack + 0xc) == 0.0) && (this->trial_a == 0))
           && (this->trial_b == 0)) {
          JRing::RingSleep(this);
        }
        if (((long)((ulong)this->flagsB << 0x3b) < 0) && (this->crack != 0)
           ) {
          CrackJRing::Update(this->dt,this->crack);
        }
      }
      else if (sVar11 == 2) {
        if (this->sub == 1) {
          this->anim_a = this->anim_a + this->dt * 4.0;
          if (1.0 < this->anim_a) {
            this->anim_a = 0x3f800000;
          }
          this->scale_y = (1.0 - this->anim_a) * this->home_scale_y;
          this->flagsA = this->flagsA & 0x9f | 0x60;
          if (((this->anim_a == 1.0) && (this->trial_a == 0)) &&
             (this->trial_b == 0)) {
            JRing::RingSleep(this);
          }
        }
        else if (this->sub == 0) {
          this->anim_a = 0;
          this->sub = 1;
          this->flagsA = this->flagsA & 0x9f | 0x60;
          if ((this->cb_fn != 0) && ((this->u8_f1 & 1) != 0)) {
            (**(code **)(this + 0xf8))(0x100,0,this->cb_user);
          }
        }
      }
      else if (sVar11 == 1) {
        if (this->sub == 1) {
          this->anim_a =
               this->anim_a +
               this->dt * 4.0 * this->home_scale_x;
          if (this->home_scale_x < this->anim_a) {
            this->anim_a = this->home_scale_x;
          }
          this->scale_x = this->home_scale_x - this->anim_a;
          this->flagsA = this->flagsA & 0x9f | 0x60;
          if (((this->anim_a == this->home_scale_x) &&
              (this->trial_a == 0)) && (this->trial_b == 0)) {
            JRing::RingSleep(this);
          }
        }
        else if (this->sub == 0) {
          this->anim_a = 0;
          this->sub = 1;
          this->flagsA = this->flagsA & 0x9f | 0x60;
          if ((this->cb_fn != 0) && ((this->u8_f1 & 1) != 0)) {
            (**(code **)(this + 0xf8))(0x100,0,this->cb_user);
          }
          HNMSnd::PlaySE(HNMSnd::sys,0x2008,1,0);
        }
      }
      if (((this->state == 2) && (this->cb_fn != 0)) &&
         ((long)((ulong)this->u8_f1 << 0x3e) < 0)) {
        (**(code **)(this + 0xf8))(0x200,0,this->cb_user);
      }
    }
  }
  return;
}

// JP: 0x002c7a40  AutoLoadSet__5JRingFv  =  JRing::AutoLoadSet
void JRing::AutoLoadSet(int this)

{
  if (this->state == 0) {
    this->state = 1;
    this->sub = 0;
  }
  return;
}

// JP: 0x002c7a90  AutoLoadEndCheck__5JRingFv  =  JRing::AutoLoadEndCheck
undefined4 JRing::AutoLoadEndCheck(int this)

{
  undefined4 uVar1;
  
  if (this->state == 1) {
    uVar1 = 0;
  }
  else if ((JRing::System & 3) == 2) {
    if ((long)((ulong)JRing::System << 0x3d) < 0) {
      uVar1 = 1;
    }
    else {
      uVar1 = 0;
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

// JP: 0x002c7b20  SetMode__5JRingFsssss  =  JRing::SetMode
void JRing::SetMode
               (int this,undefined2 param_2,undefined2 param_3,undefined2 param_4,
               undefined2 param_5,undefined2 param_6)

{
  this->intro = param_2;
  this->ring_type = param_3;
  this->end_miss = param_4;
  this->end_ok = param_5;
  this->end_strike = param_6;
  return;
}

// JP: 0x002c7b90  SetEventRing__5JRingFibi  =  JRing::SetEventRing
void JRing::SetEventRing(int this,int param_2,byte param_3,undefined4 param_4)

{
  this->flagsC = this->flagsC & 0xbf | (param_3 & 1) << 6;
  if (param_2 == 3) {
    this->intro = 5;
    this->ring_type = 4;
    this->end_miss = 1;
    this->end_ok = 3;
    this->end_strike = 3;
    this->laps_allowed = 1;
  }
  else if (param_2 == 2) {
    this->intro = 5;
    this->ring_type = 5;
    this->end_miss = 1;
    this->end_ok = 1;
    this->end_strike = 1;
    this->laps_allowed = 0;
  }
  else if (param_2 == 1) {
    this->intro = 5;
    this->ring_type = 3;
    this->end_miss = 1;
    this->end_ok = 1;
    this->end_strike = 1;
    this->laps_allowed = param_4;
  }
  else if (param_2 == 0) {
    this->intro = 5;
    this->ring_type = 2;
    this->end_miss = 1;
    this->end_ok = 1;
    this->end_strike = 1;
    this->laps_allowed = 1;
  }
  return;
}

// JP: 0x002c7d50  RingActive__5JRingFv  =  JRing::RingActive
void JRing::RingActive(undefined8 this)

{
  undefined4 uVar1;
  int iVar2;
  int this;
  
  
  this->state = 3;
  this->sub = 0;
  this->flagsC = this->flagsC & 0xdf;
  this->flagsC = this->flagsC & 0x7f;
  if (this->crack != 0) {
    CrackJRing::~CrackJRing(this->crack,1);
  }
  this->crack = 0;
  this->flagsB = this->flagsB & 0xef;
  if (this->cut != 0) {
    CutJRing::~CutJRing(this->cut,1);
  }
  this->cut = 0;
  this->flagsB = this->flagsB & 0xdf;
  if (-1 < (long)((ulong)this->abn_d << 0x3d)) {
    this->flagsA = this->flagsA & 0x7f | 0x80;
  }
  this->i32_70 = (int)this->u64_a0;
  this->i32_74 = (int)((ulong)this->u64_a0 >> 0x20);
  this->u32_78 = this->u32_a8;
  this->u32_7c = this->u32_ac;
  this->period = this->home_period;
  this->lap_add = 0;
  this->lap_mul = 0x3f800000;
  this->accel = 0;
  if ((long)((ulong)this->abn_c << 0x39) < 0) {
    if (this->ring_type == 5) {
      this->accel = 0xbb1d4952;
    }
    else {
      this->period = this->period / 0.75;
      this->accel = 0xbc449ba6;
    }
  }
  if ((long)((ulong)this->abn_c << 0x38) < 0) {
    this->period = this->period * 0.75;
    this->accel = 0x3c449ba6;
  }
  if ((this->abn_c & 1) != 0) {
    this->period = this->period / 2.0;
  }
  if ((long)((ulong)this->abn_c << 0x3e) < 0) {
    this->period = this->period * 2.0;
  }
  if ((long)((ulong)this->abn_d << 0x3c) < 0) {
    this->period = this->period * -1.0;
  }
  if ((this->abn_d & 1) != 0) {
    this->home_scale_y = 0x3ed9999a;
  }
  if (((ulong)this->flagsB & 0xf) >> 2 == 3) {
    this->period = this->period * 0.9;
  }
  if ((this->laps_allowed != 1) &&
     ((this->ring_type == 1 || (this->ring_type == 3)))) {
    this->lap_mul = 0x3f600000;
  }
  this->laps_done = 0;
  this->hits = 0;
  this->e8 = 1;
  this->ec = 0;
  this->flip = 0;
  this->anim_b = 0;
  this->anim_a = 0;
  JRing::AreaReset(this);
  if ((-1 < (long)((ulong)this->abn_d << 0x3e)) &&
     (-1 < (long)((ulong)this->abn_d << 0x3d))) {
    this->flagsB = this->flagsB & 0xfe | 1;
  }
  this->prev_angle = 0;
  this->cur_angle = 0;
  for (iVar2 = 0; iVar2 < 9; iVar2 = iVar2 + 1) {
    *(undefined4 *)(this + iVar2 * 4 + 0x4b4) = this->cur_angle;
  }
  this->flagsB = this->flagsB & 0xfd;
  uVar1 = JRing::ResultInit(this);
  this->result_total = uVar1;
  if (this->auto_mode == 9) {
    this->combo_button = 2;
  }
  else {
    iVar2 = rand();
    this->combo_button = (int)(((float)iVar2 / 2.1474836e+09) * 4.0);
  }
  this->event_value = 0xffffffff;
  this->auto_sub = 0;
  this->flagsA = this->flagsA & 0xf9 | 6;
  return;
}

// JP: 0x002c8200  RingClose__5JRingFi  =  JRing::RingClose
void JRing::RingClose(int this,int param_2)

{
  if (param_2 == 2) {
    this->state = 8;
  }
  else if (param_2 == 1) {
    this->state = 7;
  }
  else {
    this->state = 6;
  }
  this->sub = 0;
  return;
}

// JP: 0x002c8290  RingSleep__5JRingFv  =  JRing::RingSleep
void JRing::RingSleep(int this)

{
  this->state = 2;
  this->sub = 0;
  this->scale_x = 0;
  this->scale_y = 0;
  this->ec = 0;
  if (this->crack != 0) {
    CrackJRing::~CrackJRing(this->crack,1);
  }
  this->crack = 0;
  this->flagsB = this->flagsB & 0xef;
  if (this->cut != 0) {
    CutJRing::~CutJRing(this->cut,1);
  }
  this->cut = 0;
  this->flagsB = this->flagsB & 0xdf;
  this->flagsA = this->flagsA & 0x7f;
  JRing::AreaOff(this,0xffffffffffffffff);
  this->flagsB = this->flagsB & 0xfe;
  this->flagsA = this->flagsA & 0x9f;
  this->flagsB = this->flagsB & 0xfd;
  this->flagsA = this->flagsA & 0xf9 | 6;
  this->flagsA = this->flagsA & 0xe7 | 0x18;
  return;
}

// JP: 0x002c8460  RingSleepCheck__5JRingFv  =  JRing::RingSleepCheck
bool JRing::RingSleepCheck(int this)

{
  return this->state == 2;
}

// JP: 0x002c84b0  MakePacket__5JRingFv  =  JRing::MakePacket
void JRing::MakePacket(undefined8 this)

{
  bool bVar1;
  undefined4 *puVar2;
  float in_zero_lo;
  float in_zero_hi;
  float in_zero_udw;
  float in_register_0000000c;
  undefined4 uVar3;
  ulong *puVar4;
  ulong uVar5;
  undefined8 extraout_v0_udw;
  float *pfVar6;
  int this;
  uint uVar8;
  undefined8 *puVar9;
  uint uVar10;
  int iVar11;
  long lVar12;
  uint uVar13;
  uint uVar14;
  long unaff_s6;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float __x;
  undefined1 in_vf0 [16];
  undefined1 auVar19 [16];
  undefined1 auVar20 [16];
  undefined1 auVar21 [16];
  int aiStack_6b0 [136];
  undefined1 auStack_490 [16];
  undefined1 auStack_480 [16];
  undefined1 auStack_470 [16];
  undefined1 auStack_460 [16];
  float afStack_450 [275];
  float fStack_4;
  
  uVar13 = 0;
  uVar14 = 0;
  lVar12 = 0;
  
  fVar17 = (float)(1 << (uint)(((ulong)*(byte *)((&JRing::JRTex)[this->e8] + 0x53) <<
                               0x3a) >> 0x3c));
  fVar18 = (float)(1 << (uint)((ulong)(*(long *)((&JRing::JRTex)[this->e8] + 0x50) <<
                                      0x1e) >> 0x3c));
  bVar1 = (this->flagsA & 1) == 0;
  uVar8 = 6;
  if ((long)((ulong)JRing::System << 0x3d) < 0) {
    uVar8 = 8;
  }
  if (((long)((ulong)this->flagsB << 0x3b) < 0) ||
     ((long)((ulong)this->flagsB << 0x3a) < 0)) {
    if ((long)((ulong)this->flagsB << 0x3b) < 0) {
      lVar12 = CrackJRing::GetPacketCnt(this->crack);
      uVar8 = uVar8 + (int)lVar12;
    }
    else if ((long)((ulong)this->flagsB << 0x3a) < 0) {
      lVar12 = CutJRing::GetPacketCnt(this->cut);
      uVar8 = uVar8 + (int)lVar12;
    }
  }
  else {
    unaff_s6 = 0;
    if ((((-1.5707964 < this->f32_70) && (this->f32_70 < 1.5707964)) ||
        (this->f32_74 <= -1.5707964)) || (1.5707964 <= this->f32_74)) {
      if (((this->f32_74 <= -1.5707964) || (1.5707964 <= this->f32_74)) &&
         ((-1.5707964 < this->f32_70 && (this->f32_70 < 1.5707964)))) {
        unaff_s6 = 1;
      }
    }
    else {
      unaff_s6 = 1;
    }
    if ((long)((ulong)this->flagsA << 0x38) < 0) {
      uVar8 = uVar8 + 0x3a;
    }
    uVar13 = (uint)((this->flagsB & 1) != 0);
    uVar14 = (uint)((long)((ulong)this->flagsB << 0x3e) < 0);
    uVar8 = uVar8 + uVar13 + uVar14;
  }
  uVar10 = (uint)bVar1;
  if (((((ulong)this->flagsA & 7) >> 1 & (long)(1 << uVar10)) != 0) ||
     (*(uint *)(this + uVar10 * 4 + 0x550) < uVar8)) {
    if (*(int *)(this + uVar10 * 4 + 0x18) != 0) {
      __dla(*(undefined4 *)(this + uVar10 * 4 + 0x18));
    }
    *(undefined4 *)(this + uVar10 * 4 + 0x18) = 0;
    *(undefined4 *)(this + uVar10 * 4 + 0x550) = 0;
    if ((((ulong)this->flagsA & 7) >> 1 & (long)(1 << uVar10)) != 0) {
      this->flagsA =
           this->flagsA & 0xf9 |
           (byte)(((uint)(((ulong)this->flagsA << 0x3d) >> 0x3e) - (1 << uVar10 & 0xffU)
                  & 3) << 1);
    }
  }
  if (*(int *)(this + uVar10 * 4 + 0x18) == 0) {
    uVar3 = __nwa(uVar8 << 4);
    *(undefined4 *)(this + uVar10 * 4 + 0x18) = uVar3;
    *(uint *)(this + uVar10 * 4 + 0x550) = uVar8;
  }
  puVar2 = *(undefined4 **)(this + uVar10 * 4 + 0x18);
  if ((long)((ulong)JRing::System << 0x3d) < 0) {
    *puVar2 = 0x50000000;
    puVar2[1] = *(undefined4 *)
                 ((&JRing::JRTex)[this->e8] +
                  (uint)*(ushort *)((&JRing::JRTex)[this->e8] + 10) * 4 + 0xc);
    puVar2[2] = 0;
    puVar2[3] = 0;
    puVar2[4] = 0x10000005;
    puVar2[5] = 0;
    puVar2[6] = 0;
    puVar2[7] = 0x50000005;
    puVar2->u64_8 = 0x4000000000008001;
    puVar2->u64_a = 0xe8ee;
    puVar2->u64_c = 1;
    puVar2->u64_e = 0x3f;
    puVar9 = (undefined8 *)(puVar2 + 0x10);
  }
  else {
    *puVar2 = &DAT_10000004;
    puVar2[1] = 0;
    puVar2[2] = 0;
    puVar2[3] = 0x50000004;
    puVar2->u64_4 = 0x3000000000008001;
    puVar2->u64_6 = 0xe8e;
    puVar9 = (undefined8 *)(puVar2 + 8);
  }
  *puVar9 = 0x60;
  puVar9[1] = 0x14;
  puVar9[2] = 5;
  puVar9[3] = 0;
  puVar9[4] = 0x3001;
  puVar9[5] = 0x47;
  puVar4 = puVar9 + 6;
  if (((long)((ulong)this->flagsB << 0x3b) < 0) ||
     ((long)((ulong)this->flagsB << 0x3a) < 0)) {
    if ((long)((ulong)this->flagsB << 0x3b) < 0) {
      if (lVar12 != 0) {
        puVar4 = (ulong *)CrackJRing::MakePacket(this->crack,puVar4);
      }
    }
    else if (lVar12 != 0) {
      puVar4 = (ulong *)CutJRing::MakePacket(this->cut,puVar4);
    }
  }
  else if ((this->scale_x != 0.0) && (this->scale_y != 0.0)) {
    if ((long)((ulong)this->flagsA << 0x38) < 0) {
      pfVar6 = afStack_450 + 0x88;
      do {
        *pfVar6 = in_zero_lo;
        pfVar6[1] = in_zero_hi;
        pfVar6[2] = in_zero_udw;
        pfVar6[3] = in_register_0000000c;
        pfVar6 = pfVar6 + 4;
      } while (pfVar6 != afStack_450 + 0x110);
      pfVar6 = afStack_450;
      do {
        *pfVar6 = in_zero_lo;
        pfVar6[1] = in_zero_hi;
        pfVar6[2] = in_zero_udw;
        pfVar6[3] = in_register_0000000c;
        pfVar6 = pfVar6 + 4;
      } while (pfVar6 != afStack_450 + 0x88);
      afStack_450[0x88] = 0.0;
      afStack_450[0x89] = 0.0;
      afStack_450[0x8a] = 0.0;
      afStack_450[0x8b] = 1.0;
      __x = 0.0;
      for (iVar11 = 1; iVar11 < 0x22; iVar11 = iVar11 + 1) {
        fVar15 = sinf(__x);
        fVar16 = cosf(__x);
        afStack_450[iVar11 * 4 + 0x88] = fVar16;
        afStack_450[iVar11 * 4 + 0x89] = -fVar15;
        afStack_450[iVar11 * 4 + 0x8a] = 0.0;
        afStack_450[iVar11 * 4 + 0x8b] = 1.0;
        __x = __x + 0.19634955;
      }
      auVar19 = _vmr32(in_vf0);
      auVar20 = _vmr32(auVar19);
      auVar21 = _vmr32(auVar20);
      _sqc2(in_vf0);
      _sqc2(auVar19);
      _sqc2(auVar20);
      _sqc2(auVar21);
      auVar19 = _vmr32(in_vf0);
      auVar20 = _vmr32(auVar19);
      auVar21 = _vmr32(auVar20);
      auStack_460 = _sqc2(in_vf0);
      auStack_470 = _sqc2(auVar19);
      auStack_480 = _sqc2(auVar20);
      auStack_490 = _sqc2(auVar21);
      sceVu0RotMatrixZ(this->u32_78,auStack_490,auStack_490);
      sceVu0RotMatrixX(this->u32_70,auStack_490,auStack_490);
      sceVu0RotMatrixY(this->u32_74,auStack_490,auStack_490);
      FVector::__amu(this->scale_y * 114.0,auStack_490);
      FVector::__amu(this->scale_y * 114.0,auStack_480);
      FVector::__amu(this->scale_y * 114.0,auStack_470);
      FVector::__amu(this->scale_y * 114.0,auStack_460);
      RotTransVector(afStack_450,afStack_450 + 0x88,auStack_490,0x22);
      sceVu0RotTransPersN(aiStack_6b0,this + 0x590,afStack_450,0x22,0);
      for (iVar11 = 0; iVar11 < 0x22; iVar11 = iVar11 + 1) {
        aiStack_6b0[iVar11 * 4] =
             (int)((float)aiStack_6b0[iVar11 * 4] + (this->cx - 256.0) * 16.0);
        aiStack_6b0[iVar11 * 4 + 1] =
             (int)((float)aiStack_6b0[iVar11 * 4 + 1] + (this->cy - 224.0) * 16.0);
        aiStack_6b0[iVar11 * 4 + 2] = (int)((float)aiStack_6b0[iVar11 * 4 + 2] / 16.0);
      }
      this->ec = 0;
      *(undefined **)puVar4 = &DAT_10000039;
      *(undefined4 *)((int)puVar9 + 0x34) = 0;
      puVar9->u32_7 = 0;
      *(undefined4 *)((int)puVar9 + 0x3c) = 0x50000039;
      puVar9[8] = 0x2000000000000001;
      puVar9[9] = 0xee;
      uVar5 = JRCTex::GetTex0((&JRing::JRTex)[this->e8],1);
      puVar9[10] = uVar5 & 0xfffffffc0fffff | 0x2000000001300000;
      puVar9[0xb] = 0x16;
      puVar9[0xc] = 0x44;
      puVar9[0xd] = 0x42;
      auVar20._8_8_ = extraout_v0_udw;
      auVar20._0_8_ = 0x8400000000000001;
      auVar19._4_4_ = in_zero_hi;
      auVar19._0_4_ = in_zero_lo;
      auVar19._8_4_ = in_zero_udw;
      auVar19._12_4_ = in_register_0000000c;
      auVar19 = _pcpyld(auVar19,auVar20);
      puVar9[0xe] = auVar19._0_8_;
      puVar9[0xf] = 0xc12c1206;
      uVar5 = JRCTex::GetTex0((&JRing::JRTex)[this->e8],1);
      puVar9[0x10] = uVar5 & 0xffffffffffffff | (long)this->ec << 0x38;
      puVar9[0x11] = 0x5d;
      afStack_450[0x111] = 16.0 / (float)aiStack_6b0[3];
      fStack_4 = afStack_450[0x111] * ((afStack_450[0x88] * 114.0 + 128.0) / fVar17);
      afStack_450[0x112] = afStack_450[0x111] * ((afStack_450[0x89] * 114.0 + 128.0) / fVar18);
      puVar9[0x12] = CONCAT44(afStack_450[0x112],fStack_4);
      lVar12 = __fixunssfdi(this->scale_x * 128.0);
      puVar9[0x13] = lVar12 << 0x18 | 0x808080U | (ulong)(uint)afStack_450[0x111] << 0x20;
      puVar9[0x14] = (long)aiStack_6b0[2] << 0x20 |
                     (long)aiStack_6b0[0] | (long)aiStack_6b0[1] << 0x10;
      afStack_450[0x111] = 16.0 / (float)aiStack_6b0[7];
      fStack_4 = afStack_450[0x111] * ((afStack_450[0x8c] * 114.0 + 128.0) / fVar17);
      afStack_450[0x112] = afStack_450[0x111] * ((afStack_450[0x8d] * 114.0 + 128.0) / fVar18);
      puVar9[0x15] = CONCAT44(afStack_450[0x112],fStack_4);
      lVar12 = __fixunssfdi(this->scale_x * 128.0);
      puVar9[0x16] = lVar12 << 0x18 | 0x808080U | (ulong)(uint)afStack_450[0x111] << 0x20;
      puVar9[0x17] = (long)aiStack_6b0[6] << 0x20 |
                     (long)aiStack_6b0[4] | (long)aiStack_6b0[5] << 0x10;
      puVar9[0x18] = 0x3400000000008020;
      puVar9[0x19] = 0x412;
      puVar4 = puVar9 + 0x1a;
      for (uVar8 = 2; (int)uVar8 < 0x22; uVar8 = uVar8 + 1) {
        afStack_450[0x111] = 16.0 / (float)aiStack_6b0[uVar8 * 4 + 3];
        fStack_4 = afStack_450[0x111] * ((afStack_450[uVar8 * 4 + 0x88] * 114.0 + 128.0) / fVar17);
        afStack_450[0x112] =
             afStack_450[0x111] * ((afStack_450[uVar8 * 4 + 0x89] * 114.0 + 128.0) / fVar18);
        if ((uVar8 & 1) == 0) {
          *puVar4 = CONCAT44(afStack_450[0x112],fStack_4);
          lVar12 = __fixunssfdi(this->scale_x * 128.0);
          puVar4[1] = lVar12 << 0x18 | 0x808080U | (ulong)(uint)afStack_450[0x111] << 0x20;
          puVar4 = puVar4 + 2;
          *puVar4 = (long)aiStack_6b0[uVar8 * 4 + 2] << 0x20 |
                    (long)aiStack_6b0[uVar8 * 4] | (long)aiStack_6b0[uVar8 * 4 + 1] << 0x10;
        }
        else {
          puVar4[1] = CONCAT44(afStack_450[0x112],fStack_4);
          lVar12 = __fixunssfdi(this->scale_x * 128.0);
          puVar4[2] = lVar12 << 0x18 | 0x808080U | (ulong)(uint)afStack_450[0x111] << 0x20;
          puVar4[3] = (long)aiStack_6b0[uVar8 * 4 + 2] << 0x20 |
                      (long)aiStack_6b0[uVar8 * 4] | (long)aiStack_6b0[uVar8 * 4 + 1] << 0x10;
          puVar4 = puVar4 + 4;
        }
      }
    }
    if ((uVar13 == 0) || (unaff_s6 != 0)) {
      if (uVar13 == 0) {
        if ((*(int *)(this + uVar10 * 4 + 0x4f8) != 0) &&
           (iVar11 = *(int *)(this + uVar10 * 4 + 0x4f8), iVar11 != 0)) {
          __dla(iVar11 + -0x10);
        }
        *(undefined4 *)(this + uVar10 * 4 + 0x4f8) = 0;
      }
    }
    else {
      *(undefined4 *)puVar4 = 0x50000000;
      uVar3 = JRing::SetAreaPacket(this,bVar1);
      *(undefined4 *)((int)puVar4 + 4) = uVar3;
      puVar4->u32_1 = 0;
      *(undefined4 *)((int)puVar4 + 0xc) = 0;
      puVar4 = puVar4 + 2;
    }
    if ((uVar14 == 0) || (unaff_s6 != 0)) {
      if (uVar14 == 0) {
        if ((*(int *)(this + uVar10 * 4 + 0x500) != 0) &&
           (iVar11 = *(int *)(this + uVar10 * 4 + 0x500), iVar11 != 0)) {
          __dla(iVar11 + -0x10);
        }
        *(undefined4 *)(this + uVar10 * 4 + 0x500) = 0;
      }
    }
    else {
      *(undefined4 *)puVar4 = 0x50000000;
      uVar3 = JRing::MakeBarPacket(this,bVar1);
      *(undefined4 *)((int)puVar4 + 4) = uVar3;
      puVar4->u32_1 = 0;
      *(undefined4 *)((int)puVar4 + 0xc) = 0;
      puVar4 = puVar4 + 2;
    }
  }
  for (iVar11 = this->i32_568; iVar11 != 0; iVar11 = iVar11->i32_3c) {
    if ((long)((ulong)iVar11->u8_44 << 0x3b) < 0) {
      *(undefined4 *)puVar4 = 0x20000000;
      uVar3 = (**(code **)(iVar11->i32_14 + 0x30))();
      *(undefined4 *)((int)puVar4 + 4) = uVar3;
      puVar4->u32_1 = 0;
      *(undefined4 *)((int)puVar4 + 0xc) = 0;
      puVar4 = *(ulong **)(iVar11 + 0x5c);
    }
    else {
      iVar11->u8_44 = iVar11->u8_44 & 0xef | 0x10;
    }
  }
  for (iVar11 = this->i32_560; iVar11 != 0; iVar11 = iVar11->i32_3c) {
    *(undefined4 *)puVar4 = 0x20000000;
    uVar3 = (**(code **)(iVar11->i32_14 + 0x30))();
    *(undefined4 *)((int)puVar4 + 4) = uVar3;
    puVar4->u32_1 = 0;
    *(undefined4 *)((int)puVar4 + 0xc) = 0;
    puVar4 = *(ulong **)(iVar11 + 0x5c);
  }
  for (iVar11 = this->i32_558; iVar11 != 0; iVar11 = iVar11->i32_3c) {
    *(undefined4 *)puVar4 = 0x20000000;
    uVar3 = (**(code **)(iVar11->i32_14 + 0x30))();
    *(undefined4 *)((int)puVar4 + 4) = uVar3;
    puVar4->u32_1 = 0;
    *(undefined4 *)((int)puVar4 + 0xc) = 0;
    puVar4 = *(ulong **)(iVar11 + 0x98);
  }
  if (this->trial_a != 0) {
    if ((long)((ulong)*(byte *)(this->trial_a + 0x3c) << 0x3c) < 0) {
      this->trial_a = 0;
    }
    else {
      *(undefined4 *)puVar4 = 0x20000000;
      uVar3 = (**(code **)(*(int *)(this->trial_a + 0x14) + 0x30))();
      *(undefined4 *)((int)puVar4 + 4) = uVar3;
      puVar4->u32_1 = 0;
      *(undefined4 *)((int)puVar4 + 0xc) = 0;
      puVar4 = *(ulong **)(this->trial_a + 0x98);
    }
  }
  if (this->trial_b != 0) {
    if ((long)((ulong)*(byte *)(this->trial_b + 0x3c) << 0x3c) < 0) {
      this->trial_b = 0;
    }
    else {
      *(undefined4 *)puVar4 = 0x20000000;
      uVar3 = (**(code **)(*(int *)(this->trial_b + 0x14) + 0x30))();
      *(undefined4 *)((int)puVar4 + 4) = uVar3;
      puVar4->u32_1 = 0;
      *(undefined4 *)((int)puVar4 + 0xc) = 0;
      puVar4 = *(ulong **)(this->trial_b + 0x98);
    }
  }
  *(undefined4 *)puVar4 = 0x60000000;
  *(undefined4 *)((int)puVar4 + 4) = 0;
  puVar4[1] = 0;
  this->flagsA = this->flagsA & 0xfe | bVar1;
  return;
}

// JP: 0x002c98e0  SetRingPos__5JRingFff  =  JRing::SetRingPos
void JRing::SetRingPos(undefined4 this,undefined4 param_2,int param_3)

{
  param_3->u32_68 = this;
  param_3->u32_6c = param_2;
  return;
}

// JP: 0x002c9920  SetRotSpeed__5JRingFfff  =  JRing::SetRotSpeed
void JRing::SetRotSpeed(undefined4 this,undefined4 param_2,undefined4 param_3,int param_4)

{
  param_4->u32_b4 = this;
  param_4->u32_c0 = param_2;
  param_4->u32_c4 = param_3;
  return;
}

// JP: 0x002c9970  AllAreaInitialize__5JRingFv  =  JRing::AllAreaInitialize
void JRing::AllAreaInitialize(int this)

{
  int iVar1;
  int iVar2;
  
  for (iVar2 = 0; iVar2 < 0xc; iVar2 = iVar2 + 1) {
    *(undefined1 *)(this + iVar2 * 0x24 + 0x102) = 0xff;
    *(undefined2 *)(this + iVar2 * 0x24 + 0x100) = 0;
    *(undefined2 *)(this + iVar2 * 0x24 + 0x108) = 0;
    *(undefined2 *)(this + iVar2 * 0x24 + 0x10a) = 0;
    *(undefined2 *)(this + iVar2 * 0x24 + 0x106) = 0;
    *(undefined2 *)(this + iVar2 * 0x24 + 0x104) = 0;
    *(undefined1 *)(this + iVar2 * 0x24 + 0x114) = 0;
    *(undefined1 *)(this + iVar2 * 0x24 + 0x115) = 0;
    *(undefined1 *)(this + iVar2 * 0x24 + 0x116) = 0;
    *(undefined1 *)(this + iVar2 * 0x24 + 0x117) = 0;
    iVar1 = this + iVar2 * 0x24;
    *(undefined1 *)(this + iVar2 * 0x24 + 0x110) = iVar1->u8_114;
    *(undefined1 *)(this + iVar2 * 0x24 + 0x111) = iVar1->u8_115;
    *(undefined1 *)(this + iVar2 * 0x24 + 0x112) = iVar1->u8_116;
    *(undefined1 *)(this + iVar2 * 0x24 + 0x113) = iVar1->u8_117;
    iVar1 = this + iVar2 * 0x24;
    *(undefined1 *)(this + iVar2 * 0x24 + 0x10c) = iVar1->u8_110;
    *(undefined1 *)(this + iVar2 * 0x24 + 0x10d) = iVar1->u8_111;
    *(undefined1 *)(this + iVar2 * 0x24 + 0x10e) = iVar1->u8_112;
    *(undefined1 *)(this + iVar2 * 0x24 + 0x10f) = iVar1->u8_113;
    *(undefined2 *)(this + iVar2 * 0x24 + 0x118) = 0;
    *(undefined2 *)(this + iVar2 * 0x24 + 0x11a) = 0xffff;
    *(undefined1 *)(this + iVar2 * 0x24 + 0x2b2) = 0xff;
    *(undefined2 *)(this + iVar2 * 0x24 + 0x2b0) = 0;
    *(undefined2 *)(this + iVar2 * 0x24 + 0x2b8) = 0;
    *(undefined2 *)(this + iVar2 * 0x24 + 0x2ba) = 0;
    *(undefined2 *)(this + iVar2 * 0x24 + 0x2b6) = 0;
    *(undefined2 *)(this + iVar2 * 0x24 + 0x2b4) = 0;
    *(undefined1 *)(this + iVar2 * 0x24 + 0x2c4) = 0;
    *(undefined1 *)(this + iVar2 * 0x24 + 0x2c5) = 0;
    *(undefined1 *)(this + iVar2 * 0x24 + 0x2c6) = 0;
    *(undefined1 *)(this + iVar2 * 0x24 + 0x2c7) = 0;
    iVar1 = this + iVar2 * 0x24;
    *(undefined1 *)(this + iVar2 * 0x24 + 0x2c0) = iVar1->u8_2c4;
    *(undefined1 *)(this + iVar2 * 0x24 + 0x2c1) = iVar1->u8_2c5;
    *(undefined1 *)(this + iVar2 * 0x24 + 0x2c2) = iVar1->u8_2c6;
    *(undefined1 *)(this + iVar2 * 0x24 + 0x2c3) = iVar1->u8_2c7;
    iVar1 = this + iVar2 * 0x24;
    *(undefined1 *)(this + iVar2 * 0x24 + 700) = iVar1->u8_2c0;
    *(undefined1 *)(this + iVar2 * 0x24 + 0x2bd) = iVar1->u8_2c1;
    *(undefined1 *)(this + iVar2 * 0x24 + 0x2be) = iVar1->u8_2c2;
    *(undefined1 *)(this + iVar2 * 0x24 + 0x2bf) = iVar1->u8_2c3;
    *(undefined2 *)(this + iVar2 * 0x24 + 0x2c8) = 0;
    *(undefined2 *)(this + iVar2 * 0x24 + 0x2ca) = 0xffff;
  }
  this->u8_462 = 0xff;
  this->u16_460 = 0;
  this->u16_468 = 0;
  this->u16_46a = 0;
  this->u16_466 = 0;
  this->u16_464 = 0;
  this->u8_474 = 0;
  this->u8_475 = 0;
  this->u8_476 = 0;
  this->u8_477 = 0;
  this->u8_470 = this->u8_474;
  this->u8_471 = this->u8_475;
  this->u8_472 = this->u8_476;
  this->u8_473 = this->u8_477;
  this->u8_46c = this->u8_470;
  this->u8_46d = this->u8_471;
  this->u8_46e = this->u8_472;
  this->u8_46f = this->u8_473;
  this->u16_478 = 0;
  this->u16_47a = 0xffff;
  this->custom_data = 0;
  this->area_count = 0;
  this->flagsA = this->flagsA & 0xf9 | 6;
  this->flagsA = this->flagsA & 0xe7 | 0x18;
  this->flagsA = this->flagsA & 0x9f | 0x60;
  return;
}

// JP: 0x002ca0b0  AddStepArea__5JRingFssP7_rgba32s  =  JRing::AddStepArea
void JRing::AddStepArea
               (int this,undefined2 param_2,short param_3,undefined1 *param_4,undefined2 param_5)

{
  int iVar1;
  int iVar2;
  
  if (0 < param_3) {
    for (iVar2 = 0; iVar2 < 0xc; iVar2 = iVar2 + 1) {
      if (*(char *)(this + iVar2 * 0x24 + 0x102) == -1) {
        *(undefined1 *)(this + iVar2 * 0x24 + 0x102) = 0;
        *(undefined2 *)(this + iVar2 * 0x24 + 0x104) = param_2;
        *(short *)(this + iVar2 * 0x24 + 0x106) = param_3;
        *(undefined2 *)(this + iVar2 * 0x24 + 0x10a) = 0;
        *(undefined2 *)(this + iVar2 * 0x24 + 0x108) = 0;
        if (param_4 == (undefined1 *)0x0) {
          *(undefined1 *)(this + iVar2 * 0x24 + 0x10c) = 0;
          *(undefined1 *)(this + iVar2 * 0x24 + 0x10d) = 0xa4;
          *(undefined1 *)(this + iVar2 * 0x24 + 0x10e) = 0x50;
          *(undefined1 *)(this + iVar2 * 0x24 + 0x10f) = 0;
        }
        else {
          *(undefined1 *)(this + iVar2 * 0x24 + 0x10c) = *param_4;
          *(undefined1 *)(this + iVar2 * 0x24 + 0x10d) = param_4[1];
          *(undefined1 *)(this + iVar2 * 0x24 + 0x10e) = param_4[2];
          *(undefined1 *)(this + iVar2 * 0x24 + 0x10f) = param_4[3];
        }
        *(undefined1 *)(this + iVar2 * 0x24 + 0x114) = 0;
        *(undefined1 *)(this + iVar2 * 0x24 + 0x115) = 0;
        *(undefined1 *)(this + iVar2 * 0x24 + 0x116) = 0;
        *(undefined1 *)(this + iVar2 * 0x24 + 0x117) = 0;
        iVar1 = this + iVar2 * 0x24;
        *(undefined1 *)(this + iVar2 * 0x24 + 0x110) = iVar1->u8_114;
        *(undefined1 *)(this + iVar2 * 0x24 + 0x111) = iVar1->u8_115;
        *(undefined1 *)(this + iVar2 * 0x24 + 0x112) = iVar1->u8_116;
        *(undefined1 *)(this + iVar2 * 0x24 + 0x113) = iVar1->u8_117;
        *(undefined2 *)(this + iVar2 * 0x24 + 0x118) = param_5;
        *(undefined2 *)(this + iVar2 * 0x24 + 0x11a) = 0xffff;
        this->area_count = this->area_count + 1;
        this->flagsA = this->flagsA & 0xf9 | 6;
        this->flagsA = this->flagsA & 0xe7 | 0x18;
        this->flagsA = this->flagsA & 0x9f | 0x60;
        return;
      }
    }
  }
  return;
}

// JP: 0x002ca4d0  AddStrikeArea__5JRingFsssP7_rgba32P7_rgba32  =  JRing::AddStrikeArea
void JRing::AddStrikeArea
               (int this,undefined2 param_2,short param_3,short param_4,undefined1 *param_5,
               undefined1 *param_6)

{
  int iVar1;
  
  if ((0 < param_3) && (param_4 <= param_3)) {
    for (iVar1 = 0; iVar1 < 0xc; iVar1 = iVar1 + 1) {
      if (*(char *)(this + iVar1 * 0x24 + 0x102) == -1) {
        *(undefined1 *)(this + iVar1 * 0x24 + 0x102) = 1;
        *(undefined2 *)(this + iVar1 * 0x24 + 0x104) = param_2;
        *(short *)(this + iVar1 * 0x24 + 0x106) = param_3;
        *(undefined2 *)(this + iVar1 * 0x24 + 0x10a) = 0;
        *(short *)(this + iVar1 * 0x24 + 0x108) = param_4;
        if (param_5 == (undefined1 *)0x0) {
          *(undefined1 *)(this + iVar1 * 0x24 + 0x10c) = 0xe0;
          *(undefined1 *)(this + iVar1 * 0x24 + 0x10d) = 0x98;
          *(undefined1 *)(this + iVar1 * 0x24 + 0x10e) = 0x40;
          *(undefined1 *)(this + iVar1 * 0x24 + 0x10f) = 0;
        }
        else {
          *(undefined1 *)(this + iVar1 * 0x24 + 0x10c) = *param_5;
          *(undefined1 *)(this + iVar1 * 0x24 + 0x10d) = param_5[1];
          *(undefined1 *)(this + iVar1 * 0x24 + 0x10e) = param_5[2];
          *(undefined1 *)(this + iVar1 * 0x24 + 0x10f) = param_5[3];
        }
        if (param_6 == (undefined1 *)0x0) {
          *(undefined1 *)(this + iVar1 * 0x24 + 0x110) = 0xff;
          *(undefined1 *)(this + iVar1 * 0x24 + 0x111) = 0x20;
          *(undefined1 *)(this + iVar1 * 0x24 + 0x112) = 0x18;
          *(undefined1 *)(this + iVar1 * 0x24 + 0x113) = 0;
        }
        else {
          *(undefined1 *)(this + iVar1 * 0x24 + 0x110) = *param_6;
          *(undefined1 *)(this + iVar1 * 0x24 + 0x111) = param_6[1];
          *(undefined1 *)(this + iVar1 * 0x24 + 0x112) = param_6[2];
          *(undefined1 *)(this + iVar1 * 0x24 + 0x113) = param_6[3];
        }
        *(undefined1 *)(this + iVar1 * 0x24 + 0x114) = 0;
        *(undefined1 *)(this + iVar1 * 0x24 + 0x115) = 0;
        *(undefined1 *)(this + iVar1 * 0x24 + 0x116) = 0;
        *(undefined1 *)(this + iVar1 * 0x24 + 0x117) = 0;
        *(undefined2 *)(this + iVar1 * 0x24 + 0x118) = 0;
        *(undefined2 *)(this + iVar1 * 0x24 + 0x11a) = 0xffff;
        this->area_count = this->area_count + 1;
        this->flagsA = this->flagsA & 0xf9 | 6;
        this->flagsA = this->flagsA & 0xe7 | 0x18;
        this->flagsA = this->flagsA & 0x9f | 0x60;
        return;
      }
    }
  }
  return;
}

// JP: 0x002ca990  AddModulateArea__5JRingFssssP7_rgba32P7_rgba32P7_rgba32  =  JRing::AddModulateArea
void JRing::AddModulateArea
               (int this,undefined2 param_2,short param_3,short param_4,short param_5,
               undefined1 *param_6,undefined1 *param_7,undefined1 *param_8)

{
  int iVar1;
  
  if (0 < param_3) {
    for (iVar1 = 0; iVar1 < 0xc; iVar1 = iVar1 + 1) {
      if (*(char *)(this + iVar1 * 0x24 + 0x102) == -1) {
        *(undefined1 *)(this + iVar1 * 0x24 + 0x102) = 2;
        *(undefined2 *)(this + iVar1 * 0x24 + 0x104) = param_2;
        *(short *)(this + iVar1 * 0x24 + 0x106) = param_3;
        *(char *)(this + iVar1 * 0x24 + 0x103) = (char)param_4;
        *(short *)(this + iVar1 * 0x24 + 0x10a) = (short)(((int)param_3 - (int)param_5) / 3);
        *(short *)(this + iVar1 * 0x24 + 0x108) = param_5;
        if (param_6 == (undefined1 *)0x0) {
          *(undefined1 *)(this + iVar1 * 0x24 + 0x10c) = 0xff;
          *(undefined1 *)(this + iVar1 * 0x24 + 0x10d) = 0xff;
          *(undefined1 *)(this + iVar1 * 0x24 + 0x10e) = 0xff;
          *(undefined1 *)(this + iVar1 * 0x24 + 0x10f) = 0;
        }
        else {
          *(undefined1 *)(this + iVar1 * 0x24 + 0x10c) = *param_6;
          *(undefined1 *)(this + iVar1 * 0x24 + 0x10d) = param_6[1];
          *(undefined1 *)(this + iVar1 * 0x24 + 0x10e) = param_6[2];
          *(undefined1 *)(this + iVar1 * 0x24 + 0x10f) = param_6[3];
        }
        if (param_7 == (undefined1 *)0x0) {
          *(undefined1 *)(this + iVar1 * 0x24 + 0x110) = 0x20;
          *(undefined1 *)(this + iVar1 * 0x24 + 0x111) = 200;
          *(undefined1 *)(this + iVar1 * 0x24 + 0x112) = 0xfa;
          *(undefined1 *)(this + iVar1 * 0x24 + 0x113) = 0;
        }
        else {
          *(undefined1 *)(this + iVar1 * 0x24 + 0x110) = *param_7;
          *(undefined1 *)(this + iVar1 * 0x24 + 0x111) = param_7[1];
          *(undefined1 *)(this + iVar1 * 0x24 + 0x112) = param_7[2];
          *(undefined1 *)(this + iVar1 * 0x24 + 0x113) = param_7[3];
        }
        if (param_8 == (undefined1 *)0x0) {
          *(undefined1 *)(this + iVar1 * 0x24 + 0x114) = 0xff;
          *(undefined1 *)(this + iVar1 * 0x24 + 0x115) = 0x20;
          *(undefined1 *)(this + iVar1 * 0x24 + 0x116) = 0x18;
          *(undefined1 *)(this + iVar1 * 0x24 + 0x117) = 0;
        }
        else {
          *(undefined1 *)(this + iVar1 * 0x24 + 0x114) = *param_8;
          *(undefined1 *)(this + iVar1 * 0x24 + 0x115) = param_8[1];
          *(undefined1 *)(this + iVar1 * 0x24 + 0x116) = param_8[2];
          *(undefined1 *)(this + iVar1 * 0x24 + 0x117) = param_8[3];
        }
        if (param_4 == 100) {
          *(undefined1 *)(this + iVar1 * 0x24 + 0x10c) =
               *(undefined1 *)(this + iVar1 * 0x24 + 0x110);
          *(undefined1 *)(this + iVar1 * 0x24 + 0x10d) =
               *(undefined1 *)(this + iVar1 * 0x24 + 0x111);
          *(undefined1 *)(this + iVar1 * 0x24 + 0x10e) =
               *(undefined1 *)(this + iVar1 * 0x24 + 0x112);
          *(undefined1 *)(this + iVar1 * 0x24 + 0x10f) =
               *(undefined1 *)(this + iVar1 * 0x24 + 0x113);
        }
        *(undefined2 *)(this + iVar1 * 0x24 + 0x118) = 0;
        *(undefined2 *)(this + iVar1 * 0x24 + 0x11a) = 0xffff;
        this->area_count = this->area_count + 1;
        this->flagsA = this->flagsA & 0xf9 | 6;
        this->flagsA = this->flagsA & 0xe7 | 0x18;
        this->flagsA = this->flagsA & 0x9f | 0x60;
        return;
      }
    }
  }
  return;
}

// JP: 0x002cb010  AddEventRingArea__5JRingFssc  =  JRing::AddEventRingArea
void JRing::AddEventRingArea(int this,undefined2 param_2,short param_3,char param_4)

{
  int iVar1;
  int iVar2;
  
  if (0 < param_3) {
    for (iVar2 = 0; iVar2 < 0xc; iVar2 = iVar2 + 1) {
      if (*(char *)(this + iVar2 * 0x24 + 0x102) == -1) {
        *(undefined1 *)(this + iVar2 * 0x24 + 0x102) = 0;
        *(undefined2 *)(this + iVar2 * 0x24 + 0x104) = param_2;
        *(short *)(this + iVar2 * 0x24 + 0x106) = param_3;
        *(undefined2 *)(this + iVar2 * 0x24 + 0x10a) = 0;
        *(undefined2 *)(this + iVar2 * 0x24 + 0x108) = 0;
        if (param_4 == '\x04') {
          *(undefined1 *)(this + iVar2 * 0x24 + 0x10c) = 0;
          *(undefined1 *)(this + iVar2 * 0x24 + 0x10d) = 0xa4;
          *(undefined1 *)(this + iVar2 * 0x24 + 0x10e) = 0x50;
          *(undefined1 *)(this + iVar2 * 0x24 + 0x10f) = 0;
        }
        else if (param_4 == '\x03') {
          *(undefined1 *)(this + iVar2 * 0x24 + 0x10c) = 0x20;
          *(undefined1 *)(this + iVar2 * 0x24 + 0x10d) = 200;
          *(undefined1 *)(this + iVar2 * 0x24 + 0x10e) = 0xfa;
          *(undefined1 *)(this + iVar2 * 0x24 + 0x10f) = 0;
        }
        else if (param_4 == '\x02') {
          *(undefined1 *)(this + iVar2 * 0x24 + 0x10c) = 0xe0;
          *(undefined1 *)(this + iVar2 * 0x24 + 0x10d) = 0x98;
          *(undefined1 *)(this + iVar2 * 0x24 + 0x10e) = 0x40;
          *(undefined1 *)(this + iVar2 * 0x24 + 0x10f) = 0;
        }
        else if (param_4 == '\x01') {
          *(undefined1 *)(this + iVar2 * 0x24 + 0x10c) = 0xff;
          *(undefined1 *)(this + iVar2 * 0x24 + 0x10d) = 0x20;
          *(undefined1 *)(this + iVar2 * 0x24 + 0x10e) = 0x18;
          *(undefined1 *)(this + iVar2 * 0x24 + 0x10f) = 0;
        }
        *(undefined1 *)(this + iVar2 * 0x24 + 0x114) = 0;
        *(undefined1 *)(this + iVar2 * 0x24 + 0x115) = 0;
        *(undefined1 *)(this + iVar2 * 0x24 + 0x116) = 0;
        *(undefined1 *)(this + iVar2 * 0x24 + 0x117) = 0;
        iVar1 = this + iVar2 * 0x24;
        *(undefined1 *)(this + iVar2 * 0x24 + 0x110) = iVar1->u8_114;
        *(undefined1 *)(this + iVar2 * 0x24 + 0x111) = iVar1->u8_115;
        *(undefined1 *)(this + iVar2 * 0x24 + 0x112) = iVar1->u8_116;
        *(undefined1 *)(this + iVar2 * 0x24 + 0x113) = iVar1->u8_117;
        *(short *)(this + iVar2 * 0x24 + 0x118) = (short)param_4;
        *(undefined2 *)(this + iVar2 * 0x24 + 0x11a) = 0xffff;
        this->area_count = this->area_count + 1;
        this->flagsA = this->flagsA & 0xf9 | 6;
        this->flagsA = this->flagsA & 0xe7 | 0x18;
        this->flagsA = this->flagsA & 0x9f | 0x60;
        return;
      }
    }
  }
  return;
}

// JP: 0x002cb5b0  GetAreaPacketCnt__5JRingFv  =  JRing::GetAreaPacketCnt
undefined4 JRing::GetAreaPacketCnt(int this)

{
  int iVar1;
  int iVar2;
  
  this->u32_4a8 = 2;
  if (((ulong)this->flagsB & 0xf) >> 2 == 3) {
    iVar1 = JRing::CalcAreaPacketCnt(this,this + 0x460);
    this->i32_4a8 = this->i32_4a8 + iVar1;
  }
  else if ((long)((ulong)this->flagsC << 0x3d) < 0) {
    for (iVar1 = 0; iVar1 < 0xc; iVar1 = iVar1 + 1) {
      iVar2 = JRing::CalcAreaPacketCnt(this,this + iVar1 * 0x24 + 0x2b0);
      this->i32_4a8 = this->i32_4a8 + iVar2;
    }
  }
  else {
    for (iVar1 = 0; iVar1 < 0xc; iVar1 = iVar1 + 1) {
      iVar2 = JRing::CalcAreaPacketCnt(this,this + iVar1 * 0x24 + 0x100);
      this->i32_4a8 = this->i32_4a8 + iVar2;
    }
  }
  if ((long)((ulong)this->abn_d << 0x3b) < 0) {
    iVar1 = JRing::CalcAreaPacketCnt(this,this + 0x484);
    this->i32_4a8 = this->i32_4a8 + iVar1;
  }
  return this->u32_4a8;
}

// JP: 0x002cb750  CalcAreaPacketCnt__5JRingFP6JRAREA  =  JRing::CalcAreaPacketCnt
int JRing::CalcAreaPacketCnt(undefined8 this,byte *param_2)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  float fStack_24;
  
  bVar1 = param_2[2];
  if (bVar1 == 2) {
    if ((0 < param_2->i16_6) && ((long)((ulong)*param_2 << 0x3c) < 0)) {
      iVar2 = 2;
      fStack_24 = (float)((int)param_2->i16_4 + (int)param_2->i16_6);
      if (param_2->i16_8 != 0) {
        if (param_2->i16_8 < 5) {
          fStack_24 = (float)((int)param_2->i16_4 + (int)param_2->i16_6) -
                      ((float)(int)param_2->i16_8 * 4.0) / 5.0;
          iVar2 = 4;
        }
        else {
          fStack_24 = fStack_24 - 2.0;
          iVar2 = 3;
          while ((float)(((int)param_2->i16_4 + (int)param_2->i16_6) -
                        (param_2->i16_8 + -1)) < fStack_24) {
            fStack_24 = fStack_24 - 11.25;
            if (fStack_24 <=
                (float)(((int)param_2->i16_4 + (int)param_2->i16_6) -
                       (param_2->i16_8 + -1))) {
              fStack_24 = (float)(((int)param_2->i16_4 + (int)param_2->i16_6) -
                                 (param_2->i16_8 + -1));
            }
            iVar2 = iVar2 + 1;
          }
        }
      }
      if (param_2->i16_a != 0) {
        if (((param_2->i16_8 == 0) || (param_2->i16_a < 4)) &&
           ((param_2->i16_8 != 0 || (param_2->i16_a < 3)))) {
          fStack_24 = (float)(((int)param_2->i16_4 + (int)param_2->i16_6) -
                             ((int)param_2->i16_8 + (int)param_2->i16_a));
          iVar2 = iVar2 + 2;
        }
        else {
          if (param_2->i16_8 == 0) {
            fStack_24 = (float)((int)param_2->i16_4 + (int)param_2->i16_6) - 2.0;
          }
          else {
            fStack_24 = (float)((int)param_2->i16_4 + (int)param_2->i16_6) -
                        ((float)(int)param_2->i16_8 + 1.0);
          }
          while (iVar2 = iVar2 + 1,
                (float)(((int)param_2->i16_4 + (int)param_2->i16_6) -
                       ((int)param_2->i16_8 + (int)param_2->i16_a)) < fStack_24)
          {
            fStack_24 = fStack_24 - 11.25;
            if (fStack_24 <=
                (float)(((int)param_2->i16_4 + (int)param_2->i16_6) -
                       ((int)param_2->i16_8 + (int)param_2->i16_a))) {
              fStack_24 = (float)(((int)param_2->i16_4 + (int)param_2->i16_6) -
                                 ((int)param_2->i16_8 + (int)param_2->i16_a));
            }
          }
        }
      }
      if ((param_2->i16_a == 0) && (param_2->i16_8 == 0)) {
        if (param_2->i16_6 < 6) {
          iVar2 = iVar2 + 3;
        }
        else {
          fStack_24 = fStack_24 - 2.0;
          while (iVar3 = iVar2 + 1, (float)(param_2->i16_4 + 2) < fStack_24) {
            fStack_24 = fStack_24 - 11.25;
            iVar2 = iVar3;
            if (fStack_24 <= (float)(param_2->i16_4 + 2)) {
              fStack_24 = (float)(param_2->i16_4 + 2);
            }
          }
          iVar2 = iVar2 + 2;
        }
      }
      else if (((param_2->i16_a == 0) ||
               ((int)param_2->i16_6 -
                ((int)param_2->i16_8 + (int)param_2->i16_a) < 4)) &&
              ((param_2->i16_a != 0 ||
               ((int)param_2->i16_6 -
                ((int)param_2->i16_8 + (int)param_2->i16_a) < 5)))) {
        if (param_2->i16_a == 0) {
          iVar2 = iVar2 + 3;
        }
        else {
          iVar2 = iVar2 + 2;
        }
      }
      else {
        if (param_2->i16_a == 0) {
          fStack_24 = (float)(((int)param_2->i16_4 + (int)param_2->i16_6) -
                             ((int)param_2->i16_8 + (int)param_2->i16_a + 1));
          iVar2 = iVar2 + 1;
        }
        else {
          fStack_24 = (float)(((int)param_2->i16_4 + (int)param_2->i16_6) -
                             ((int)param_2->i16_8 + (int)param_2->i16_a));
        }
        while ((float)(param_2->i16_4 + 2) < fStack_24) {
          fStack_24 = fStack_24 - 11.25;
          if (fStack_24 <= (float)(param_2->i16_4 + 2)) {
            fStack_24 = (float)(param_2->i16_4 + 2);
          }
          iVar2 = iVar2 + 1;
        }
        iVar2 = iVar2 + 1;
      }
      return iVar2 + 3;
    }
  }
  else if (bVar1 == 1) {
    if ((-1 < param_2->i16_6) && ((long)((ulong)*param_2 << 0x3c) < 0)) {
      if ((param_2->i16_8 == 0) || (param_2->i16_6 == param_2->i16_8)) {
        if (param_2->i16_6 < 6) {
          iVar2 = 5;
        }
        else {
          iVar2 = 3;
          for (fStack_24 = 2.0; fStack_24 < (float)(param_2->i16_6 + -2);
              fStack_24 = fStack_24 + 11.25) {
            iVar2 = iVar2 + 1;
          }
          iVar2 = iVar2 + 1;
        }
      }
      else {
        if (param_2->i16_8 < 5) {
          iVar2 = 4;
        }
        else {
          iVar2 = 3;
          for (fStack_24 = 2.0; fStack_24 < (float)(param_2->i16_8 + -1);
              fStack_24 = fStack_24 + 11.25) {
            iVar2 = iVar2 + 1;
          }
        }
        if ((int)param_2->i16_6 - (int)param_2->i16_8 < 5) {
          iVar2 = iVar2 + 3;
        }
        else {
          for (fStack_24 = (float)(int)param_2->i16_8 + 1.0;
              fStack_24 < (float)(param_2->i16_6 + -2); fStack_24 = fStack_24 + 11.25) {
            iVar2 = iVar2 + 1;
          }
          iVar2 = iVar2 + 2;
        }
      }
      return iVar2 + 3;
    }
  }
  else if (((bVar1 == 0) && (0 < param_2->i16_6)) && ((long)((ulong)*param_2 << 0x3c) < 0))
  {
    if (param_2->i16_6 < 6) {
      iVar2 = 5;
    }
    else {
      iVar2 = 3;
      for (fStack_24 = 2.0; fStack_24 < (float)(param_2->i16_6 + -2);
          fStack_24 = fStack_24 + 11.25) {
        iVar2 = iVar2 + 1;
      }
      iVar2 = iVar2 + 1;
    }
    return iVar2 + 3;
  }
  return 0;
}

// JP: 0x002cc480  SetAreaPacket__5JRingFUi  =  JRing::SetAreaPacket
undefined4 JRing::SetAreaPacket(int this,uint param_2)

{
  undefined4 uVar1;
  int *piVar2;
  undefined8 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  if ((((ulong)this->flagsA & 0x1f) >> 3 & (long)(1 << (param_2 & 0x1f))) != 0) {
    if ((*(int *)(this + param_2 * 4 + 0x4f8) != 0) &&
       (iVar6 = *(int *)(this + param_2 * 4 + 0x4f8), iVar6 != 0)) {
      __dla(iVar6 + -0x10);
    }
    *(undefined4 *)(this + param_2 * 4 + 0x4f8) = 0;
    this->flagsA =
         this->flagsA & 0xe7 |
         (byte)(((uint)(((ulong)this->flagsA << 0x3b) >> 0x3e) -
                 (1 << (param_2 & 0x1f) & 0xffU) & 3) << 3);
  }
  if (*(int *)(this + param_2 * 4 + 0x4f8) == 0) {
    iVar6 = this->i32_4a8 + 1;
    uVar3 = __nwa(iVar6 * 0x10 + 0x10);
    uVar1 = __construct_new_array(uVar3,0x224b30,0,0x10,iVar6);
    *(undefined4 *)(this + param_2 * 4 + 0x4f8) = uVar1;
    this->flagsA =
         this->flagsA & 0x9f |
         (byte)(((uint)(((ulong)this->flagsA << 0x39) >> 0x3e) |
                1 << (param_2 & 0x1f) & 3U) << 5);
  }
  if ((((ulong)this->flagsA & 0x7f) >> 5 & (long)(1 << (param_2 & 0x1f))) == 0) {
    uVar1 = *(undefined4 *)(this + param_2 * 4 + 0x4f8);
  }
  else {
    piVar2 = *(int **)(this + param_2 * 4 + 0x4f8);
    *piVar2 = this->i32_4a8 + 0x60000000;
    piVar2[1] = 0;
    piVar2[2] = 0;
    piVar2[3] = this->i32_4a8 + 0x50000000;
    piVar2[4] = 1;
    piVar2[5] = 0x10000000;
    piVar2[6] = 0xe;
    piVar2[7] = 0;
    piVar2[8] = 0x44;
    piVar2[9] = 0;
    piVar2[10] = 0x42;
    piVar2[0xb] = 0;
    piVar2 = piVar2 + 0xc;
    if (((ulong)this->flagsB & 0xf) >> 2 == 3) {
      if ((long)((ulong)this->abn_d << 0x3b) < 0) {
        piVar2 = (int *)JRing::MakeAreaPacket(this,piVar2,this + 0x460,0);
      }
      else {
        piVar2 = (int *)JRing::MakeAreaPacket(this,piVar2,this + 0x460,1);
      }
    }
    else if ((long)((ulong)this->flagsC << 0x3d) < 0) {
      for (iVar6 = 0; iVar6 < 0xc; iVar6 = iVar6 + 1) {
        iVar5 = 0;
        iVar4 = iVar6;
        while (iVar4 = iVar4 + 1, iVar4 < 0xc) {
          if ((0 < *(short *)(this + iVar4 * 0x24 + 0x106)) &&
             ((long)((ulong)*(byte *)(this + iVar4 * 0x24 + 0x100) << 0x3c) < 0)) {
            iVar5 = iVar5 + 1;
          }
        }
        if ((-1 < (long)((ulong)this->abn_d << 0x3b)) && (iVar5 == 0)) {
          piVar2 = (int *)JRing::MakeAreaPacket
                                    (this,piVar2,this + iVar6 * 0x24 + 0x2b0,1);
          break;
        }
        piVar2 = (int *)JRing::MakeAreaPacket
                                  (this,piVar2,this + iVar6 * 0x24 + 0x2b0,0);
      }
    }
    else {
      for (iVar6 = 0; iVar6 < 0xc; iVar6 = iVar6 + 1) {
        iVar5 = 0;
        iVar4 = iVar6;
        while (iVar4 = iVar4 + 1, iVar4 < 0xc) {
          if ((0 < *(short *)(this + iVar4 * 0x24 + 0x106)) &&
             ((long)((ulong)*(byte *)(this + iVar4 * 0x24 + 0x100) << 0x3c) < 0)) {
            iVar5 = iVar5 + 1;
          }
        }
        if ((-1 < (long)((ulong)this->abn_d << 0x3b)) && (iVar5 == 0)) {
          piVar2 = (int *)JRing::MakeAreaPacket
                                    (this,piVar2,this + iVar6 * 0x24 + 0x100,1);
          break;
        }
        piVar2 = (int *)JRing::MakeAreaPacket
                                  (this,piVar2,this + iVar6 * 0x24 + 0x100,0);
      }
    }
    if ((long)((ulong)this->abn_d << 0x3b) < 0) {
      JRing::MakeAreaPacket(this,piVar2,this + 0x484,1);
    }
    this->flagsA =
         this->flagsA & 0x9f |
         (byte)(((uint)(((ulong)this->flagsA << 0x39) >> 0x3e) -
                 (1 << (param_2 & 0x1f) & 0xffU) & 3) << 5);
    uVar1 = *(undefined4 *)(this + param_2 * 4 + 0x4f8);
  }
  return uVar1;
}

// JP: 0x002ccab0  MakeAreaPacket__5JRingFP4_QWDP6JRAREAb  =  JRing::MakeAreaPacket
/* WARNING: Removing unreachable block (ram,0x002d3dc0) */
/* WARNING: Removing unreachable block (ram,0x002d3cec) */
/* WARNING: Removing unreachable block (ram,0x002d3c18) */
/* WARNING: Removing unreachable block (ram,0x002d3f80) */
/* WARNING: Removing unreachable block (ram,0x002d42dc) */
/* WARNING: Removing unreachable block (ram,0x002d41f8) */
/* WARNING: Removing unreachable block (ram,0x002d35b8) */
/* WARNING: Removing unreachable block (ram,0x002d3490) */
/* WARNING: Removing unreachable block (ram,0x002d3368) */
/* WARNING: Removing unreachable block (ram,0x002cd630) */
/* WARNING: Removing unreachable block (ram,0x002cd714) */
/* WARNING: Removing unreachable block (ram,0x002cd7f8) */
/* WARNING: Removing unreachable block (ram,0x002cd85c) */
/* WARNING: Removing unreachable block (ram,0x002cd9bc) */
/* WARNING: Removing unreachable block (ram,0x002cd8e8) */
/* WARNING: Removing unreachable block (ram,0x002cd93c) */
/* WARNING: Removing unreachable block (ram,0x002cda10) */
/* WARNING: Removing unreachable block (ram,0x002cdae4) */
/* WARNING: Removing unreachable block (ram,0x002cfe78) */
/* WARNING: Removing unreachable block (ram,0x002cfcd0) */
/* WARNING: Removing unreachable block (ram,0x002d00cc) */
/* WARNING: Removing unreachable block (ram,0x002d0038) */
/* WARNING: Removing unreachable block (ram,0x002cffa4) */
/* WARNING: Removing unreachable block (ram,0x002d0330) */
/* WARNING: Removing unreachable block (ram,0x002cf80c) */
/* WARNING: Removing unreachable block (ram,0x002cf8a0) */
/* WARNING: Removing unreachable block (ram,0x002cf934) */
/* WARNING: Removing unreachable block (ram,0x002d3b30) */
/* WARNING: Removing unreachable block (ram,0x002d3a4c) */
/* WARNING: Removing unreachable block (ram,0x002d3968) */
/* WARNING: Removing unreachable block (ram,0x002d3884) */
/* WARNING: Removing unreachable block (ram,0x002d37a0) */
/* WARNING: Removing unreachable block (ram,0x002d3658) */
/* WARNING: Removing unreachable block (ram,0x002d373c) */
/* WARNING: Removing unreachable block (ram,0x002d3820) */
/* WARNING: Removing unreachable block (ram,0x002d3904) */
/* WARNING: Removing unreachable block (ram,0x002d39e8) */
/* WARNING: Removing unreachable block (ram,0x002d3acc) */
/* WARNING: Removing unreachable block (ram,0x002d3200) */
/* WARNING: Removing unreachable block (ram,0x002d312c) */
/* WARNING: Removing unreachable block (ram,0x002d3058) */
/* WARNING: Removing unreachable block (ram,0x002d2f84) */
/* WARNING: Removing unreachable block (ram,0x002d2eb0) */
/* WARNING: Removing unreachable block (ram,0x002d2ddc) */
/* WARNING: Removing unreachable block (ram,0x002d2d88) */
/* WARNING: Removing unreachable block (ram,0x002d2e5c) */
/* WARNING: Removing unreachable block (ram,0x002d2f30) */
/* WARNING: Removing unreachable block (ram,0x002d3004) */
/* WARNING: Removing unreachable block (ram,0x002d30d8) */
/* WARNING: Removing unreachable block (ram,0x002d31ac) */
/* WARNING: Removing unreachable block (ram,0x002cf6e0) */
/* WARNING: Removing unreachable block (ram,0x002cf60c) */
/* WARNING: Removing unreachable block (ram,0x002cf58c) */
/* WARNING: Removing unreachable block (ram,0x002cf538) */
/* WARNING: Removing unreachable block (ram,0x002cf660) */
/* WARNING: Removing unreachable block (ram,0x002cf734) */
/* WARNING: Removing unreachable block (ram,0x002cfb98) */
/* WARNING: Removing unreachable block (ram,0x002cfab4) */
/* WARNING: Removing unreachable block (ram,0x002cfa34) */
/* WARNING: Removing unreachable block (ram,0x002cf9d0) */
/* WARNING: Removing unreachable block (ram,0x002cfb18) */
/* WARNING: Removing unreachable block (ram,0x002cfbfc) */
/* WARNING: Removing unreachable block (ram,0x002d0168) */
/* WARNING: Removing unreachable block (ram,0x002d024c) */
/* WARNING: Removing unreachable block (ram,0x002cfd24) */
/* WARNING: Removing unreachable block (ram,0x002cd590) */
/* WARNING: Removing unreachable block (ram,0x002cd4fc) */
/* WARNING: Removing unreachable block (ram,0x002cd468) */
/* WARNING: Removing unreachable block (ram,0x002d32d4) */
/* WARNING: Removing unreachable block (ram,0x002d33fc) */
/* WARNING: Removing unreachable block (ram,0x002d3524) */
/* WARNING: Removing unreachable block (ram,0x002d4194) */
/* WARNING: Removing unreachable block (ram,0x002d4278) */
/* WARNING: Removing unreachable block (ram,0x002d3eec) */
/* WARNING: Removing unreachable block (ram,0x002d4014) */
/* WARNING: Removing unreachable block (ram,0x002d3c6c) */
/* WARNING: Removing unreachable block (ram,0x002d3d40) */
/* WARNING: Removing unreachable block (ram,0x002d3e14) */
/* WARNING: Removing unreachable block (ram,0x002d40b0) */
/* WARNING: Removing unreachable block (ram,0x002cd778) */
/* WARNING: Removing unreachable block (ram,0x002cd694) */
/* WARNING: Removing unreachable block (ram,0x002d0394) */
/* WARNING: Removing unreachable block (ram,0x002d01cc) */
/* WARNING: Removing unreachable block (ram,0x002d02b0) */
/* WARNING: Removing unreachable block (ram,0x002cfdf8) */
/* WARNING: Removing unreachable block (ram,0x002cfda4) */
/* WARNING: Removing unreachable block (ram,0x002cfecc) */
/* WARNING: Removing unreachable block (ram,0x002cda90) */
/* WARNING: Removing unreachable block (ram,0x002d36bc) */
/* WARNING: Removing unreachable block (ram,0x002d4114) */

ulong * JRing::MakeAreaPacket
                  (int this,ulong *param_2,ushort *param_3,char param_4)

{
  byte bVar1;
  ushort uVar2;
  float in_zero_lo;
  float in_zero_hi;
  float in_zero_udw;
  float in_register_0000000c;
  undefined1 uVar3;
  undefined1 uVar4;
  float *pfVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  ulong *puVar11;
  float fVar12;
  float __x;
  float fVar13;
  float fVar14;
  float fVar15;
  undefined1 in_vf0 [16];
  undefined1 auVar16 [16];
  undefined1 auVar17 [16];
  undefined1 auVar18 [16];
  int aiStack_1860 [6];
  int iStack_1848;
  int iStack_1844;
  int aiStack_1840 [504];
  float afStack_1060 [1024];
  undefined1 auStack_60 [16];
  undefined1 auStack_50 [16];
  undefined1 auStack_40 [16];
  undefined1 auStack_30 [16];
  undefined1 auStack_18 [2];
  byte bStack_16;
  undefined1 auStack_14 [2];
  byte bStack_12;
  undefined1 auStack_10 [2];
  byte bStack_e;
  undefined1 auStack_8 [2];
  char cStack_6;
  
  auVar16 = _vmr32(in_vf0);
  auVar17 = _vmr32(auVar16);
  auVar18 = _vmr32(auVar17);
  _sqc2(in_vf0);
  _sqc2(auVar16);
  _sqc2(auVar17);
  _sqc2(auVar18);
  auVar16 = _vmr32(in_vf0);
  auVar17 = _vmr32(auVar16);
  auVar18 = _vmr32(auVar17);
  auStack_30 = _sqc2(in_vf0);
  auStack_40 = _sqc2(auVar16);
  auStack_50 = _sqc2(auVar17);
  auStack_60 = _sqc2(auVar18);
  sceVu0RotMatrixZ(this->u32_78,auStack_60,auStack_60);
  sceVu0RotMatrixX(this->u32_70,auStack_60,auStack_60);
  sceVu0RotMatrixY(this->u32_74,auStack_60,auStack_60);
  pfVar5 = afStack_1060 + 0x200;
  do {
    *pfVar5 = in_zero_lo;
    pfVar5[1] = in_zero_hi;
    pfVar5[2] = in_zero_udw;
    pfVar5[3] = in_register_0000000c;
    pfVar5 = pfVar5 + 4;
  } while (pfVar5 != (float *)auStack_60);
  pfVar5 = afStack_1060;
  do {
    *pfVar5 = in_zero_lo;
    pfVar5[1] = in_zero_hi;
    pfVar5[2] = in_zero_udw;
    pfVar5[3] = in_register_0000000c;
    pfVar5 = pfVar5 + 4;
  } while (pfVar5 != afStack_1060 + 0x200);
  bVar1 = (byte)param_3[1];
  if (bVar1 == 2) {
    if ((0 < (short)param_3[3]) && ((long)((ulong)(byte)*param_3 << 0x3c) < 0)) {
      afStack_1060[0x200] = 0.0;
      afStack_1060[0x201] = 0.0;
      afStack_1060[0x202] = 0.0;
      afStack_1060[0x203] = 1.0;
      fVar15 = (float)((int)(short)param_3[2] + (int)(short)param_3[3]);
      fVar12 = (float)GetRad(90.0 - fVar15);
      fVar12 = sinf(fVar12);
      fVar13 = this->scale_y * -fVar12 * 101.0;
      fVar12 = (float)GetRad(90.0 - fVar15);
      afStack_1060[0x204] = cosf(fVar12);
      afStack_1060[0x204] = this->scale_y * 101.0 * afStack_1060[0x204];
      afStack_1060[0x206] = 0.0;
      afStack_1060[0x207] = 1.0;
      iVar7 = 0;
      iVar9 = 0;
      iVar6 = 2;
      afStack_1060[0x205] = fVar13;
      if (param_3[4] != 0) {
        if ((short)param_3[4] < 5) {
          fVar15 = (float)((int)(short)param_3[2] + (int)(short)param_3[3]) -
                   ((float)(int)(short)param_3[4] * 2.0) / 5.0;
          fVar12 = (float)GetRad(90.0 - fVar15);
          fVar12 = sinf(fVar12);
          fVar13 = this->scale_y * -fVar12 * 101.0;
          fVar12 = (float)GetRad(90.0 - fVar15);
          afStack_1060[0x208] = cosf(fVar12);
          afStack_1060[0x208] = this->scale_y * 101.0 * afStack_1060[0x208];
          afStack_1060[0x20a] = 0.0;
          afStack_1060[0x20b] = 1.0;
          fVar15 = (float)((int)(short)param_3[2] + (int)(short)param_3[3]) -
                   ((float)(int)(short)param_3[4] * 4.0) / 5.0;
          afStack_1060[0x209] = fVar13;
          fVar12 = (float)GetRad(90.0 - fVar15);
          fVar12 = sinf(fVar12);
          fVar13 = this->scale_y * -fVar12 * 101.0;
          fVar12 = (float)GetRad(90.0 - fVar15);
          afStack_1060[0x20c] = cosf(fVar12);
          afStack_1060[0x20c] = this->scale_y * 101.0 * afStack_1060[0x20c];
          afStack_1060[0x20e] = 0.0;
          afStack_1060[0x20f] = 1.0;
          iVar9 = 3;
          iVar6 = 4;
          afStack_1060[0x20d] = fVar13;
        }
        else {
          fVar15 = fVar15 - 2.0;
          fVar12 = (float)GetRad(90.0 - fVar15);
          fVar12 = sinf(fVar12);
          fVar13 = this->scale_y * -fVar12 * 101.0;
          fVar12 = (float)GetRad(90.0 - fVar15);
          afStack_1060[0x208] = cosf(fVar12);
          afStack_1060[0x208] = this->scale_y * 101.0 * afStack_1060[0x208];
          afStack_1060[0x20a] = 0.0;
          afStack_1060[0x20b] = 1.0;
          iVar6 = 3;
          afStack_1060[0x209] = fVar13;
          while ((float)(((int)(short)param_3[2] + (int)(short)param_3[3]) -
                        ((short)param_3[4] + -1)) < fVar15) {
            fVar15 = fVar15 - 11.25;
            if (fVar15 <= (float)(((int)(short)param_3[2] + (int)(short)param_3[3]) -
                                 ((short)param_3[4] + -1))) {
              fVar15 = (float)(((int)(short)param_3[2] + (int)(short)param_3[3]) -
                              ((short)param_3[4] + -1));
            }
            fVar12 = (float)GetRad(90.0 - fVar15);
            fVar12 = sinf(fVar12);
            fVar13 = this->scale_y * -fVar12 * 101.0;
            fVar12 = (float)GetRad(90.0 - fVar15);
            fVar12 = cosf(fVar12);
            afStack_1060[iVar6 * 4 + 0x200] = this->scale_y * 101.0 * fVar12;
            afStack_1060[iVar6 * 4 + 0x201] = fVar13;
            afStack_1060[iVar6 * 4 + 0x202] = 0.0;
            afStack_1060[iVar6 * 4 + 0x203] = 1.0;
            iVar6 = iVar6 + 1;
          }
          iVar9 = iVar6 + -1;
        }
      }
      if (param_3[5] != 0) {
        if (((param_3[4] == 0) || ((short)param_3[5] < 4)) &&
           ((param_3[4] != 0 || ((short)param_3[5] < 3)))) {
          fVar15 = (float)((int)(short)param_3[2] + (int)(short)param_3[3]) -
                   ((float)(int)(short)param_3[4] + (float)(int)(short)param_3[5] / 3.0);
          fVar12 = (float)GetRad(90.0 - fVar15);
          fVar12 = sinf(fVar12);
          fVar13 = this->scale_y * -fVar12 * 101.0;
          fVar12 = (float)GetRad(90.0 - fVar15);
          fVar12 = cosf(fVar12);
          afStack_1060[iVar6 * 4 + 0x200] = this->scale_y * 101.0 * fVar12;
          afStack_1060[iVar6 * 4 + 0x201] = fVar13;
          afStack_1060[iVar6 * 4 + 0x202] = 0.0;
          afStack_1060[iVar6 * 4 + 0x203] = 1.0;
          fVar15 = (float)(((int)(short)param_3[2] + (int)(short)param_3[3]) -
                          ((int)(short)param_3[4] + (int)(short)param_3[5]));
          fVar12 = (float)GetRad(90.0 - fVar15);
          fVar12 = sinf(fVar12);
          fVar13 = this->scale_y * -fVar12 * 101.0;
          fVar12 = (float)GetRad(90.0 - fVar15);
          fVar12 = cosf(fVar12);
          iVar7 = iVar6 + 1;
          afStack_1060[iVar7 * 4 + 0x200] = this->scale_y * 101.0 * fVar12;
          afStack_1060[iVar7 * 4 + 0x201] = fVar13;
          afStack_1060[iVar7 * 4 + 0x202] = 0.0;
          afStack_1060[iVar7 * 4 + 0x203] = 1.0;
          iVar7 = 2;
          iVar6 = iVar6 + 2;
        }
        else {
          if (param_3[4] == 0) {
            fVar15 = (float)((int)(short)param_3[2] + (int)(short)param_3[3]) - 2.0;
          }
          else {
            fVar15 = (float)((int)(short)param_3[2] + (int)(short)param_3[3]) -
                     ((float)(int)(short)param_3[4] + 1.0);
          }
          fVar12 = (float)GetRad(90.0 - fVar15);
          fVar12 = sinf(fVar12);
          fVar13 = this->scale_y * -fVar12 * 101.0;
          fVar12 = (float)GetRad(90.0 - fVar15);
          fVar12 = cosf(fVar12);
          afStack_1060[iVar6 * 4 + 0x200] = this->scale_y * 101.0 * fVar12;
          afStack_1060[iVar6 * 4 + 0x201] = fVar13;
          afStack_1060[iVar6 * 4 + 0x202] = 0.0;
          afStack_1060[iVar6 * 4 + 0x203] = 1.0;
          while (iVar6 = iVar6 + 1,
                (float)(((int)(short)param_3[2] + (int)(short)param_3[3]) -
                       ((int)(short)param_3[4] + (int)(short)param_3[5])) < fVar15) {
            fVar15 = fVar15 - 11.25;
            if (fVar15 <= (float)(((int)(short)param_3[2] + (int)(short)param_3[3]) -
                                 ((int)(short)param_3[4] + (int)(short)param_3[5]))) {
              fVar15 = (float)(((int)(short)param_3[2] + (int)(short)param_3[3]) -
                              ((int)(short)param_3[4] + (int)(short)param_3[5]));
            }
            fVar12 = (float)GetRad(90.0 - fVar15);
            fVar12 = sinf(fVar12);
            fVar13 = this->scale_y * -fVar12 * 101.0;
            fVar12 = (float)GetRad(90.0 - fVar15);
            fVar12 = cosf(fVar12);
            afStack_1060[iVar6 * 4 + 0x200] = this->scale_y * 101.0 * fVar12;
            afStack_1060[iVar6 * 4 + 0x201] = fVar13;
            afStack_1060[iVar6 * 4 + 0x202] = 0.0;
            afStack_1060[iVar6 * 4 + 0x203] = 1.0;
          }
          iVar7 = (iVar6 - iVar9) + -1;
        }
      }
      if ((param_3[5] == 0) && (param_3[4] == 0)) {
        if ((short)param_3[3] < 6) {
          fVar15 = (float)(int)(short)param_3[2] + ((float)(int)(short)param_3[3] * 2.0) / 3.0;
          fVar12 = (float)GetRad(90.0 - fVar15);
          fVar12 = sinf(fVar12);
          fVar13 = this->scale_y * -fVar12 * 101.0;
          fVar12 = (float)GetRad(90.0 - fVar15);
          afStack_1060[0x208] = cosf(fVar12);
          afStack_1060[0x208] = this->scale_y * 101.0 * afStack_1060[0x208];
          afStack_1060[0x20a] = 0.0;
          afStack_1060[0x20b] = 1.0;
          fVar15 = (float)(int)(short)param_3[2] + (float)(int)(short)param_3[3] / 3.0;
          afStack_1060[0x209] = fVar13;
          fVar12 = (float)GetRad(90.0 - fVar15);
          fVar12 = sinf(fVar12);
          fVar13 = this->scale_y * -fVar12 * 101.0;
          fVar12 = (float)GetRad(90.0 - fVar15);
          afStack_1060[0x20c] = cosf(fVar12);
          afStack_1060[0x20c] = this->scale_y * 101.0 * afStack_1060[0x20c];
          afStack_1060[0x20e] = 0.0;
          afStack_1060[0x20f] = 1.0;
          uVar2 = param_3[2];
          afStack_1060[0x20d] = fVar13;
          fVar12 = (float)GetRad(90.0 - (float)(int)(short)uVar2);
          fVar12 = sinf(fVar12);
          fVar13 = this->scale_y * -fVar12 * 101.0;
          fVar12 = (float)GetRad(90.0 - (float)(int)(short)uVar2);
          afStack_1060[0x210] = cosf(fVar12);
          afStack_1060[0x210] = this->scale_y * 101.0 * afStack_1060[0x210];
          afStack_1060[0x212] = 0.0;
          afStack_1060[0x213] = 1.0;
          iVar6 = 4;
          afStack_1060[0x211] = fVar13;
        }
        else {
          fVar15 = fVar15 - 2.0;
          fVar12 = (float)GetRad(90.0 - fVar15);
          fVar12 = sinf(fVar12);
          fVar13 = this->scale_y * -fVar12 * 101.0;
          fVar12 = (float)GetRad(90.0 - fVar15);
          afStack_1060[0x208] = cosf(fVar12);
          afStack_1060[0x208] = this->scale_y * 101.0 * afStack_1060[0x208];
          afStack_1060[0x20a] = 0.0;
          afStack_1060[0x20b] = 1.0;
          iVar6 = 3;
          afStack_1060[0x209] = fVar13;
          while ((float)((short)param_3[2] + 2) < fVar15) {
            fVar15 = fVar15 - 11.25;
            if (fVar15 <= (float)((short)param_3[2] + 2)) {
              fVar15 = (float)((short)param_3[2] + 2);
            }
            fVar12 = (float)GetRad(90.0 - fVar15);
            fVar12 = sinf(fVar12);
            fVar13 = this->scale_y * -fVar12 * 101.0;
            fVar12 = (float)GetRad(90.0 - fVar15);
            fVar12 = cosf(fVar12);
            afStack_1060[iVar6 * 4 + 0x200] = this->scale_y * 101.0 * fVar12;
            afStack_1060[iVar6 * 4 + 0x201] = fVar13;
            afStack_1060[iVar6 * 4 + 0x202] = 0.0;
            afStack_1060[iVar6 * 4 + 0x203] = 1.0;
            iVar6 = iVar6 + 1;
          }
          uVar2 = param_3[2];
          fVar12 = (float)GetRad(90.0 - (float)(int)(short)uVar2);
          fVar12 = sinf(fVar12);
          fVar13 = this->scale_y * -fVar12 * 101.0;
          fVar12 = (float)GetRad(90.0 - (float)(int)(short)uVar2);
          fVar12 = cosf(fVar12);
          afStack_1060[iVar6 * 4 + 0x200] = this->scale_y * 101.0 * fVar12;
          afStack_1060[iVar6 * 4 + 0x201] = fVar13;
          afStack_1060[iVar6 * 4 + 0x202] = 0.0;
          afStack_1060[iVar6 * 4 + 0x203] = 1.0;
        }
      }
      else if (((param_3[5] == 0) ||
               ((int)(short)param_3[3] - ((int)(short)param_3[4] + (int)(short)param_3[5]) < 4)) &&
              ((param_3[5] != 0 ||
               ((int)(short)param_3[3] - ((int)(short)param_3[4] + (int)(short)param_3[5]) < 5)))) {
        if (param_3[5] == 0) {
          fVar15 = (float)(int)(short)param_3[2] +
                   ((float)((int)(short)param_3[3] -
                           ((int)(short)param_3[4] + (int)(short)param_3[5])) * 4.0) / 5.0;
          fVar12 = (float)GetRad(90.0 - fVar15);
          fVar12 = sinf(fVar12);
          fVar13 = this->scale_y * -fVar12 * 101.0;
          fVar12 = (float)GetRad(90.0 - fVar15);
          fVar12 = cosf(fVar12);
          afStack_1060[iVar6 * 4 + 0x200] = this->scale_y * 101.0 * fVar12;
          afStack_1060[iVar6 * 4 + 0x201] = fVar13;
          afStack_1060[iVar6 * 4 + 0x202] = 0.0;
          afStack_1060[iVar6 * 4 + 0x203] = 1.0;
          fVar15 = (float)(int)(short)param_3[2] +
                   ((float)((int)(short)param_3[3] -
                           ((int)(short)param_3[4] + (int)(short)param_3[5])) * 2.0) / 5.0;
          fVar12 = (float)GetRad(90.0 - fVar15);
          fVar12 = sinf(fVar12);
          fVar13 = this->scale_y * -fVar12 * 101.0;
          fVar12 = (float)GetRad(90.0 - fVar15);
          fVar12 = cosf(fVar12);
          iVar8 = iVar6 + 1;
          afStack_1060[iVar8 * 4 + 0x200] = this->scale_y * 101.0 * fVar12;
          afStack_1060[iVar8 * 4 + 0x201] = fVar13;
          afStack_1060[iVar8 * 4 + 0x202] = 0.0;
          afStack_1060[iVar8 * 4 + 0x203] = 1.0;
          uVar2 = param_3[2];
          fVar12 = (float)GetRad(90.0 - (float)(int)(short)uVar2);
          fVar12 = sinf(fVar12);
          fVar13 = this->scale_y * -fVar12 * 101.0;
          fVar12 = (float)GetRad(90.0 - (float)(int)(short)uVar2);
          fVar12 = cosf(fVar12);
          iVar6 = iVar6 + 2;
          afStack_1060[iVar6 * 4 + 0x200] = this->scale_y * 101.0 * fVar12;
          afStack_1060[iVar6 * 4 + 0x201] = fVar13;
          afStack_1060[iVar6 * 4 + 0x202] = 0.0;
          afStack_1060[iVar6 * 4 + 0x203] = 1.0;
          iVar6 = 3;
        }
        else {
          fVar15 = (float)(int)(short)param_3[2] +
                   (float)((int)(short)param_3[3] -
                          ((int)(short)param_3[4] + (int)(short)param_3[5])) / 2.0;
          fVar12 = (float)GetRad(90.0 - fVar15);
          fVar12 = sinf(fVar12);
          fVar13 = this->scale_y * -fVar12 * 101.0;
          fVar12 = (float)GetRad(90.0 - fVar15);
          fVar12 = cosf(fVar12);
          afStack_1060[iVar6 * 4 + 0x200] = this->scale_y * 101.0 * fVar12;
          afStack_1060[iVar6 * 4 + 0x201] = fVar13;
          afStack_1060[iVar6 * 4 + 0x202] = 0.0;
          afStack_1060[iVar6 * 4 + 0x203] = 1.0;
          uVar2 = param_3[2];
          fVar12 = (float)GetRad(90.0 - (float)(int)(short)uVar2);
          fVar12 = sinf(fVar12);
          fVar13 = this->scale_y * -fVar12 * 101.0;
          fVar12 = (float)GetRad(90.0 - (float)(int)(short)uVar2);
          fVar12 = cosf(fVar12);
          iVar6 = iVar6 + 1;
          afStack_1060[iVar6 * 4 + 0x200] = this->scale_y * 101.0 * fVar12;
          afStack_1060[iVar6 * 4 + 0x201] = fVar13;
          afStack_1060[iVar6 * 4 + 0x202] = 0.0;
          afStack_1060[iVar6 * 4 + 0x203] = 1.0;
          iVar6 = 2;
        }
      }
      else {
        if (param_3[5] == 0) {
          fVar15 = (float)(((int)(short)param_3[2] + (int)(short)param_3[3]) -
                          ((int)(short)param_3[4] + (int)(short)param_3[5] + 1));
          fVar12 = (float)GetRad(90.0 - fVar15);
          fVar12 = sinf(fVar12);
          fVar13 = this->scale_y * -fVar12 * 101.0;
          fVar12 = (float)GetRad(90.0 - fVar15);
          fVar12 = cosf(fVar12);
          afStack_1060[iVar6 * 4 + 0x200] = this->scale_y * 101.0 * fVar12;
          afStack_1060[iVar6 * 4 + 0x201] = fVar13;
          afStack_1060[iVar6 * 4 + 0x202] = 0.0;
          afStack_1060[iVar6 * 4 + 0x203] = 1.0;
          iVar6 = iVar6 + 1;
        }
        else {
          fVar15 = (float)(((int)(short)param_3[2] + (int)(short)param_3[3]) -
                          ((int)(short)param_3[4] + (int)(short)param_3[5]));
        }
        while ((float)((short)param_3[2] + 2) < fVar15) {
          fVar15 = fVar15 - 11.25;
          if (fVar15 <= (float)((short)param_3[2] + 2)) {
            fVar15 = (float)((short)param_3[2] + 2);
          }
          fVar12 = (float)GetRad(90.0 - fVar15);
          fVar12 = sinf(fVar12);
          fVar13 = this->scale_y * -fVar12 * 101.0;
          fVar12 = (float)GetRad(90.0 - fVar15);
          fVar12 = cosf(fVar12);
          afStack_1060[iVar6 * 4 + 0x200] = this->scale_y * 101.0 * fVar12;
          afStack_1060[iVar6 * 4 + 0x201] = fVar13;
          afStack_1060[iVar6 * 4 + 0x202] = 0.0;
          afStack_1060[iVar6 * 4 + 0x203] = 1.0;
          iVar6 = iVar6 + 1;
        }
        uVar2 = param_3[2];
        fVar12 = (float)GetRad(90.0 - (float)(int)(short)uVar2);
        fVar12 = sinf(fVar12);
        fVar13 = this->scale_y * -fVar12 * 101.0;
        fVar12 = (float)GetRad(90.0 - (float)(int)(short)uVar2);
        fVar12 = cosf(fVar12);
        afStack_1060[iVar6 * 4 + 0x200] = this->scale_y * 101.0 * fVar12;
        afStack_1060[iVar6 * 4 + 0x201] = fVar13;
        afStack_1060[iVar6 * 4 + 0x202] = 0.0;
        afStack_1060[iVar6 * 4 + 0x203] = 1.0;
        iVar6 = (iVar6 - iVar9) - iVar7;
      }
      RotTransVector(afStack_1060,afStack_1060 + 0x200,auStack_60,iVar6 + iVar9 + iVar7 + 1);
      sceVu0RotTransPersN(aiStack_1860,this + 0x590,afStack_1060,iVar6 + iVar9 + iVar7 + 1,0);
      for (iVar8 = 0; iVar8 < iVar6 + iVar9 + iVar7 + 1; iVar8 = iVar8 + 1) {
        aiStack_1860[iVar8 * 4] =
             (int)((float)aiStack_1860[iVar8 * 4] + (this->cx - 256.0) * 16.0);
        aiStack_1860[iVar8 * 4 + 1] =
             (int)((float)aiStack_1860[iVar8 * 4 + 1] + (this->cy - 224.0) * 16.0)
        ;
        aiStack_1860[iVar8 * 4 + 2] = (int)((float)aiStack_1860[iVar8 * 4 + 2] / 16.0);
      }
      if ((((ulong)*(byte *)((int)param_3 + 1) & 7) >> 1 == 1) ||
         (((ulong)*(byte *)((int)param_3 + 1) & 7) >> 1 == 3)) {
        fVar12 = (float)(byte)param_3[6] +
                 (255.0 - (float)(byte)param_3[6]) * param_3->f32_10;
        if (fVar12 < 2.1474836e+09) {
          uVar3 = (undefined1)(int)fVar12;
        }
        else {
          uVar3 = (undefined1)(int)(fVar12 - 2.1474836e+09);
        }
        fVar12 = (float)*(byte *)((int)param_3 + 0xd) +
                 (255.0 - (float)*(byte *)((int)param_3 + 0xd)) * param_3->f32_10;
        if (fVar12 < 2.1474836e+09) {
          uVar4 = (undefined1)(int)fVar12;
        }
        else {
          uVar4 = (undefined1)(int)(fVar12 - 2.1474836e+09);
        }
        auStack_18 = (undefined1  [2])CONCAT11(uVar4,uVar3);
        fVar12 = (float)(byte)param_3[7] +
                 (255.0 - (float)(byte)param_3[7]) * param_3->f32_10;
        if (fVar12 < 2.1474836e+09) {
          uVar3 = (undefined1)(int)fVar12;
        }
        else {
          uVar3 = (undefined1)(int)(fVar12 - 2.1474836e+09);
        }
        _auStack_18 = CONCAT12(uVar3,auStack_18);
        fVar12 = (float)(byte)param_3[8] +
                 (255.0 - (float)(byte)param_3[8]) * param_3->f32_10;
        if (fVar12 < 2.1474836e+09) {
          uVar3 = (undefined1)(int)fVar12;
        }
        else {
          uVar3 = (undefined1)(int)(fVar12 - 2.1474836e+09);
        }
        fVar12 = (float)*(byte *)((int)param_3 + 0x11) +
                 (255.0 - (float)*(byte *)((int)param_3 + 0x11)) * param_3->f32_10;
        if (fVar12 < 2.1474836e+09) {
          uVar4 = (undefined1)(int)fVar12;
        }
        else {
          uVar4 = (undefined1)(int)(fVar12 - 2.1474836e+09);
        }
        auStack_14 = (undefined1  [2])CONCAT11(uVar4,uVar3);
        fVar12 = (float)(byte)param_3[9] +
                 (255.0 - (float)(byte)param_3[9]) * param_3->f32_10;
        if (fVar12 < 2.1474836e+09) {
          uVar3 = (undefined1)(int)fVar12;
        }
        else {
          uVar3 = (undefined1)(int)(fVar12 - 2.1474836e+09);
        }
        _auStack_14 = CONCAT12(uVar3,auStack_14);
      }
      else if ((((ulong)(byte)*param_3 & 0x3f) >> 4 == 1) ||
              (((ulong)(byte)*param_3 & 0x3f) >> 4 == 3)) {
        if (param_3->f32_e <= 0.75) {
          fVar12 = (float)(byte)param_3[6] * (param_3->f32_e + 0.25);
          if (fVar12 < 2.1474836e+09) {
            uVar3 = (undefined1)(int)fVar12;
          }
          else {
            uVar3 = (undefined1)(int)(fVar12 - 2.1474836e+09);
          }
          fVar12 = (float)*(byte *)((int)param_3 + 0xd) * (param_3->f32_e + 0.25);
          if (fVar12 < 2.1474836e+09) {
            uVar4 = (undefined1)(int)fVar12;
          }
          else {
            uVar4 = (undefined1)(int)(fVar12 - 2.1474836e+09);
          }
          auStack_18 = (undefined1  [2])CONCAT11(uVar4,uVar3);
          fVar12 = (float)(byte)param_3[7] * (param_3->f32_e + 0.25);
          if (fVar12 < 2.1474836e+09) {
            uVar3 = (undefined1)(int)fVar12;
          }
          else {
            uVar3 = (undefined1)(int)(fVar12 - 2.1474836e+09);
          }
          _auStack_18 = CONCAT12(uVar3,auStack_18);
          fVar12 = (float)(byte)param_3[8] * (param_3->f32_e + 0.25);
          if (fVar12 < 2.1474836e+09) {
            uVar3 = (undefined1)(int)fVar12;
          }
          else {
            uVar3 = (undefined1)(int)(fVar12 - 2.1474836e+09);
          }
          fVar12 = (float)*(byte *)((int)param_3 + 0x11) * (param_3->f32_e + 0.25);
          if (fVar12 < 2.1474836e+09) {
            uVar4 = (undefined1)(int)fVar12;
          }
          else {
            uVar4 = (undefined1)(int)(fVar12 - 2.1474836e+09);
          }
          auStack_14 = (undefined1  [2])CONCAT11(uVar4,uVar3);
          fVar12 = (float)(byte)param_3[9] * (param_3->f32_e + 0.25);
          if (fVar12 < 2.1474836e+09) {
            uVar3 = (undefined1)(int)fVar12;
          }
          else {
            uVar3 = (undefined1)(int)(fVar12 - 2.1474836e+09);
          }
          _auStack_14 = CONCAT12(uVar3,auStack_14);
        }
        else {
          fVar12 = (float)(byte)param_3[6] +
                   (255.0 - (float)(byte)param_3[6]) * (param_3->f32_e - 0.75);
          if (fVar12 < 2.1474836e+09) {
            uVar3 = (undefined1)(int)fVar12;
          }
          else {
            uVar3 = (undefined1)(int)(fVar12 - 2.1474836e+09);
          }
          fVar12 = (float)*(byte *)((int)param_3 + 0xd) +
                   (255.0 - (float)*(byte *)((int)param_3 + 0xd)) *
                   (param_3->f32_e - 0.75);
          if (fVar12 < 2.1474836e+09) {
            uVar4 = (undefined1)(int)fVar12;
          }
          else {
            uVar4 = (undefined1)(int)(fVar12 - 2.1474836e+09);
          }
          auStack_18 = (undefined1  [2])CONCAT11(uVar4,uVar3);
          fVar12 = (float)(byte)param_3[7] +
                   (255.0 - (float)(byte)param_3[7]) * (param_3->f32_e - 0.75);
          if (fVar12 < 2.1474836e+09) {
            uVar3 = (undefined1)(int)fVar12;
          }
          else {
            uVar3 = (undefined1)(int)(fVar12 - 2.1474836e+09);
          }
          _auStack_18 = CONCAT12(uVar3,auStack_18);
          fVar12 = (float)(byte)param_3[8] +
                   (255.0 - (float)(byte)param_3[8]) * (param_3->f32_e - 0.75);
          if (fVar12 < 2.1474836e+09) {
            uVar3 = (undefined1)(int)fVar12;
          }
          else {
            uVar3 = (undefined1)(int)(fVar12 - 2.1474836e+09);
          }
          fVar12 = (float)*(byte *)((int)param_3 + 0x11) +
                   (255.0 - (float)*(byte *)((int)param_3 + 0x11)) *
                   (param_3->f32_e - 0.75);
          if (fVar12 < 2.1474836e+09) {
            uVar4 = (undefined1)(int)fVar12;
          }
          else {
            uVar4 = (undefined1)(int)(fVar12 - 2.1474836e+09);
          }
          auStack_14 = (undefined1  [2])CONCAT11(uVar4,uVar3);
          fVar12 = (float)(byte)param_3[9] +
                   (255.0 - (float)(byte)param_3[9]) * (param_3->f32_e - 0.75);
          if (fVar12 < 2.1474836e+09) {
            uVar3 = (undefined1)(int)fVar12;
          }
          else {
            uVar3 = (undefined1)(int)(fVar12 - 2.1474836e+09);
          }
          _auStack_14 = CONCAT12(uVar3,auStack_14);
        }
      }
      else {
        _auStack_18 = param_3->uint3_6;
        _auStack_14 = param_3->uint3_8;
      }
      if ((((ulong)*(byte *)((int)param_3 + 1) & 7) >> 1 == 2) ||
         (((ulong)*(byte *)((int)param_3 + 1) & 7) >> 1 == 3)) {
        fVar12 = (float)(byte)param_3[10] +
                 (255.0 - (float)(byte)param_3[10]) * param_3->f32_10;
        if (fVar12 < 2.1474836e+09) {
          uVar3 = (undefined1)(int)fVar12;
        }
        else {
          uVar3 = (undefined1)(int)(fVar12 - 2.1474836e+09);
        }
        fVar12 = (float)*(byte *)((int)param_3 + 0x15) +
                 (255.0 - (float)*(byte *)((int)param_3 + 0x15)) * param_3->f32_10;
        if (fVar12 < 2.1474836e+09) {
          uVar4 = (undefined1)(int)fVar12;
        }
        else {
          uVar4 = (undefined1)(int)(fVar12 - 2.1474836e+09);
        }
        auStack_10 = (undefined1  [2])CONCAT11(uVar4,uVar3);
        fVar12 = (float)(byte)param_3[0xb] +
                 (255.0 - (float)(byte)param_3[0xb]) * param_3->f32_10;
        if (fVar12 < 2.1474836e+09) {
          uVar3 = (undefined1)(int)fVar12;
        }
        else {
          uVar3 = (undefined1)(int)(fVar12 - 2.1474836e+09);
        }
        _auStack_10 = CONCAT12(uVar3,auStack_10);
      }
      else if ((((ulong)(byte)*param_3 & 0x3f) >> 4 == 2) ||
              (((ulong)(byte)*param_3 & 0x3f) >> 4 == 3)) {
        if (param_3->f32_e <= 0.75) {
          fVar12 = (float)(byte)param_3[10] * (param_3->f32_e + 0.25);
          if (fVar12 < 2.1474836e+09) {
            uVar3 = (undefined1)(int)fVar12;
          }
          else {
            uVar3 = (undefined1)(int)(fVar12 - 2.1474836e+09);
          }
          fVar12 = (float)*(byte *)((int)param_3 + 0x15) * (param_3->f32_e + 0.25);
          if (fVar12 < 2.1474836e+09) {
            uVar4 = (undefined1)(int)fVar12;
          }
          else {
            uVar4 = (undefined1)(int)(fVar12 - 2.1474836e+09);
          }
          auStack_10 = (undefined1  [2])CONCAT11(uVar4,uVar3);
          fVar12 = (float)(byte)param_3[0xb] * (param_3->f32_e + 0.25);
          if (fVar12 < 2.1474836e+09) {
            uVar3 = (undefined1)(int)fVar12;
          }
          else {
            uVar3 = (undefined1)(int)(fVar12 - 2.1474836e+09);
          }
          _auStack_10 = CONCAT12(uVar3,auStack_10);
        }
        else {
          fVar12 = (float)(byte)param_3[10] +
                   (255.0 - (float)(byte)param_3[10]) * (param_3->f32_e - 0.75);
          if (fVar12 < 2.1474836e+09) {
            uVar3 = (undefined1)(int)fVar12;
          }
          else {
            uVar3 = (undefined1)(int)(fVar12 - 2.1474836e+09);
          }
          fVar12 = (float)*(byte *)((int)param_3 + 0x15) +
                   (255.0 - (float)*(byte *)((int)param_3 + 0x15)) *
                   (param_3->f32_e - 0.75);
          if (fVar12 < 2.1474836e+09) {
            uVar4 = (undefined1)(int)fVar12;
          }
          else {
            uVar4 = (undefined1)(int)(fVar12 - 2.1474836e+09);
          }
          auStack_10 = (undefined1  [2])CONCAT11(uVar4,uVar3);
          fVar12 = (float)(byte)param_3[0xb] +
                   (255.0 - (float)(byte)param_3[0xb]) * (param_3->f32_e - 0.75);
          if (fVar12 < 2.1474836e+09) {
            uVar3 = (undefined1)(int)fVar12;
          }
          else {
            uVar3 = (undefined1)(int)(fVar12 - 2.1474836e+09);
          }
          _auStack_10 = CONCAT12(uVar3,auStack_10);
        }
      }
      else {
        _auStack_10 = param_3->uint3_a;
      }
      if ((((ulong)*param_3 & 0x1ff) >> 7 == 1) || (((ulong)*param_3 & 0x1ff) >> 7 == 3)) {
        auStack_18 = (undefined1  [2])CONCAT11(auStack_18[1] >> 1,auStack_18[0] >> 1);
        _auStack_18 = CONCAT12(bStack_16 >> 1,auStack_18);
        auStack_14 = (undefined1  [2])CONCAT11(auStack_14[1] >> 1,auStack_14[0] >> 1);
        _auStack_14 = CONCAT12(bStack_12 >> 1,auStack_14);
      }
      if ((((ulong)*param_3 & 0x1ff) >> 7 == 2) || (((ulong)*param_3 & 0x1ff) >> 7 == 3)) {
        auStack_10 = (undefined1  [2])CONCAT11(auStack_10[1] >> 1,auStack_10[0] >> 1);
        _auStack_10 = CONCAT12(bStack_e >> 1,auStack_10);
      }
      *param_2 = 0x6400000000000001;
      param_2[1] = 0xc1c1f0;
      param_2[2] = 0x4d;
      param_2[3] = 0;
      fVar12 = this->scale_x * 31.0;
      if (2.1474836e+09 <= fVar12) {
        fVar12 = fVar12 - 2.1474836e+09;
      }
      param_2[4] = ((long)(int)fVar12 & 0xffU) << 0x18 |
                   (ulong)(uint)(16.0 / (float)aiStack_1860[3]) << 0x20;
      param_2[5] = (long)aiStack_1860[2] << 0x20 |
                   (long)aiStack_1860[0] | (long)aiStack_1860[1] << 0x10;
      puVar11 = param_2 + 6;
      fVar12 = 16.0 / (float)iStack_1844;
      if (param_3[3] == 0x168) {
        if (param_3[4] == 0) {
          fVar13 = this->scale_x * 127.0;
          if (2.1474836e+09 <= fVar13) {
            fVar13 = fVar13 - 2.1474836e+09;
          }
          *puVar11 = (ulong)(uint)fVar12 << 0x20 |
                     ((long)(int)fVar13 & 0xffU) << 0x18 | (ulong)_auStack_14;
        }
        else {
          fVar13 = this->scale_x * 127.0;
          if (2.1474836e+09 <= fVar13) {
            fVar13 = fVar13 - 2.1474836e+09;
          }
          *puVar11 = (ulong)(uint)fVar12 << 0x20 |
                     ((long)(int)fVar13 & 0xffU) << 0x18 | (ulong)_auStack_10;
        }
      }
      else if (param_3[4] == 0) {
        fVar13 = this->scale_x * 15.0;
        if (2.1474836e+09 <= fVar13) {
          fVar13 = fVar13 - 2.1474836e+09;
        }
        *puVar11 = (ulong)(uint)fVar12 << 0x20 |
                   ((long)(int)fVar13 & 0xffU) << 0x18 | (ulong)_auStack_14;
      }
      else {
        fVar13 = this->scale_x * 15.0;
        if (2.1474836e+09 <= fVar13) {
          fVar13 = fVar13 - 2.1474836e+09;
        }
        *puVar11 = (ulong)(uint)fVar12 << 0x20 |
                   ((long)(int)fVar13 & 0xffU) << 0x18 | (ulong)_auStack_10;
      }
      param_2[7] = (long)iStack_1848 << 0x20 | (long)aiStack_1860[4] | (long)aiStack_1860[5] << 0x10
      ;
      if (param_4 == '\x01') {
        param_2[8] = (long)(iVar6 + iVar9 + iVar7 + -1) | 0x2400000000008000;
      }
      else {
        param_2[8] = (long)(iVar6 + iVar9 + iVar7 + -1) | 0x2400000000000000;
      }
      param_2[9] = 0x41;
      param_2 = param_2 + 10;
      if (((iVar9 == 0) || (iVar7 == 0)) || (iVar6 == 0)) {
        if (((iVar9 == 0) && (iVar7 != 0)) && (iVar6 != 0)) {
          for (iVar9 = 2; iVar8 = iVar7, iVar9 < iVar7 + 1; iVar9 = iVar9 + 1) {
            fVar12 = this->scale_x * 127.0;
            if (2.1474836e+09 <= fVar12) {
              fVar12 = fVar12 - 2.1474836e+09;
            }
            *param_2 = (ulong)(uint)(16.0 / (float)aiStack_1860[iVar9 * 4 + 3]) << 0x20 |
                       ((long)(int)fVar12 & 0xffU) << 0x18 | (ulong)_auStack_14;
            param_2[1] = (long)aiStack_1860[iVar9 * 4 + 2] << 0x20 |
                         (long)aiStack_1860[iVar9 * 4] | (long)aiStack_1860[iVar9 * 4 + 1] << 0x10;
            param_2 = param_2 + 2;
          }
          while (iVar8 = iVar8 + 1, iVar8 < iVar6 + iVar7) {
            if (iVar6 == 0) {
              trap(7);
            }
            if (iVar6 == 0) {
              trap(7);
            }
            auStack_8 = (undefined1  [2])
                        CONCAT11(auStack_14[1] +
                                 (char)((int)(((uint)auStack_18[1] - (uint)auStack_14[1]) *
                                             (iVar8 - (iVar7 + 1))) / iVar6),
                                 auStack_14[0] +
                                 (char)((int)(((uint)auStack_18[0] - (uint)auStack_14[0]) *
                                             (iVar8 - (iVar7 + 1))) / iVar6));
            if (iVar6 == 0) {
              trap(7);
            }
            _auStack_8 = CONCAT12(bStack_12 +
                                  (char)((int)(((uint)bStack_16 - (uint)bStack_12) *
                                              (iVar8 - (iVar7 + 1))) / iVar6),auStack_8);
            fVar12 = this->scale_x * 127.0;
            if (2.1474836e+09 <= fVar12) {
              fVar12 = fVar12 - 2.1474836e+09;
            }
            *param_2 = (ulong)(uint)(16.0 / (float)aiStack_1860[iVar8 * 4 + 3]) << 0x20 |
                       ((long)(int)fVar12 & 0xffU) << 0x18 | (ulong)_auStack_8;
            param_2[1] = (long)aiStack_1860[iVar8 * 4 + 2] << 0x20 |
                         (long)aiStack_1860[iVar8 * 4] | (long)aiStack_1860[iVar8 * 4 + 1] << 0x10;
            param_2 = param_2 + 2;
          }
        }
      }
      else {
        for (iVar8 = 2; iVar10 = iVar9, iVar8 < iVar9 + 1; iVar8 = iVar8 + 1) {
          fVar12 = this->scale_x * 127.0;
          if (2.1474836e+09 <= fVar12) {
            fVar12 = fVar12 - 2.1474836e+09;
          }
          *param_2 = (ulong)(uint)(16.0 / (float)aiStack_1860[iVar8 * 4 + 3]) << 0x20 |
                     ((long)(int)fVar12 & 0xffU) << 0x18 | (ulong)_auStack_10;
          param_2[1] = (long)aiStack_1860[iVar8 * 4 + 2] << 0x20 |
                       (long)aiStack_1860[iVar8 * 4] | (long)aiStack_1860[iVar8 * 4 + 1] << 0x10;
          param_2 = param_2 + 2;
        }
        while (iVar10 = iVar10 + 1, iVar10 < iVar9 + iVar7 + 1) {
          fVar12 = this->scale_x * 127.0;
          if (2.1474836e+09 <= fVar12) {
            fVar12 = fVar12 - 2.1474836e+09;
          }
          *param_2 = (ulong)(uint)(16.0 / (float)aiStack_1860[iVar10 * 4 + 3]) << 0x20 |
                     ((long)(int)fVar12 & 0xffU) << 0x18 | (ulong)_auStack_14;
          param_2[1] = (long)aiStack_1860[iVar10 * 4 + 2] << 0x20 |
                       (long)aiStack_1860[iVar10 * 4] | (long)aiStack_1860[iVar10 * 4 + 1] << 0x10;
          param_2 = param_2 + 2;
        }
        iVar8 = iVar9 + iVar7;
        while (iVar8 = iVar8 + 1, iVar8 < iVar6 + iVar9 + iVar7) {
          if (iVar6 == 0) {
            trap(7);
          }
          if (iVar6 == 0) {
            trap(7);
          }
          auStack_8 = (undefined1  [2])
                      CONCAT11(auStack_14[1] +
                               (char)((int)(((uint)auStack_18[1] - (uint)auStack_14[1]) *
                                           (iVar8 - (iVar9 + iVar7 + 1))) / iVar6),
                               auStack_14[0] +
                               (char)((int)(((uint)auStack_18[0] - (uint)auStack_14[0]) *
                                           (iVar8 - (iVar9 + iVar7 + 1))) / iVar6));
          if (iVar6 == 0) {
            trap(7);
          }
          _auStack_8 = CONCAT12(bStack_12 +
                                (char)((int)(((uint)bStack_16 - (uint)bStack_12) *
                                            (iVar8 - (iVar9 + iVar7 + 1))) / iVar6),auStack_8);
          fVar12 = this->scale_x * 127.0;
          if (2.1474836e+09 <= fVar12) {
            fVar12 = fVar12 - 2.1474836e+09;
          }
          *param_2 = (ulong)(uint)(16.0 / (float)aiStack_1860[iVar8 * 4 + 3]) << 0x20 |
                     ((long)(int)fVar12 & 0xffU) << 0x18 | (ulong)_auStack_8;
          param_2[1] = (long)aiStack_1860[iVar8 * 4 + 2] << 0x20 |
                       (long)aiStack_1860[iVar8 * 4] | (long)aiStack_1860[iVar8 * 4 + 1] << 0x10;
          param_2 = param_2 + 2;
        }
      }
      fVar12 = 16.0 / (float)aiStack_1860[iVar8 * 4 + 3];
      if (param_3[3] == 0x168) {
        if (param_3[4] == 0x168) {
          fVar13 = this->scale_x * 127.0;
          if (2.1474836e+09 <= fVar13) {
            fVar13 = fVar13 - 2.1474836e+09;
          }
          *param_2 = (ulong)(uint)fVar12 << 0x20 |
                     ((long)(int)fVar13 & 0xffU) << 0x18 | (ulong)_auStack_10;
        }
        else if (param_3[5] == 0x168) {
          fVar13 = this->scale_x * 127.0;
          if (2.1474836e+09 <= fVar13) {
            fVar13 = fVar13 - 2.1474836e+09;
          }
          *param_2 = (ulong)(uint)fVar12 << 0x20 |
                     ((long)(int)fVar13 & 0xffU) << 0x18 | (ulong)_auStack_14;
        }
        else {
          fVar13 = this->scale_x * 127.0;
          if (2.1474836e+09 <= fVar13) {
            fVar13 = fVar13 - 2.1474836e+09;
          }
          *param_2 = (ulong)(uint)fVar12 << 0x20 |
                     ((long)(int)fVar13 & 0xffU) << 0x18 | (ulong)_auStack_18;
        }
      }
      else if (param_3[3] == param_3[4]) {
        fVar13 = this->scale_x * 15.0;
        if (2.1474836e+09 <= fVar13) {
          fVar13 = fVar13 - 2.1474836e+09;
        }
        *param_2 = (ulong)(uint)fVar12 << 0x20 |
                   ((long)(int)fVar13 & 0xffU) << 0x18 | (ulong)_auStack_10;
      }
      else if (param_3[3] == param_3[5]) {
        fVar13 = this->scale_x * 15.0;
        if (2.1474836e+09 <= fVar13) {
          fVar13 = fVar13 - 2.1474836e+09;
        }
        *param_2 = (ulong)(uint)fVar12 << 0x20 |
                   ((long)(int)fVar13 & 0xffU) << 0x18 | (ulong)_auStack_14;
      }
      else {
        fVar13 = this->scale_x * 15.0;
        if (2.1474836e+09 <= fVar13) {
          fVar13 = fVar13 - 2.1474836e+09;
        }
        *param_2 = (ulong)(uint)fVar12 << 0x20 |
                   ((long)(int)fVar13 & 0xffU) << 0x18 | (ulong)_auStack_18;
      }
      param_2[1] = (long)aiStack_1860[iVar8 * 4 + 2] << 0x20 |
                   (long)aiStack_1860[iVar8 * 4] | (long)aiStack_1860[iVar8 * 4 + 1] << 0x10;
      param_2 = param_2 + 2;
    }
  }
  else if (bVar1 == 1) {
    if ((0 < (short)param_3[3]) && ((long)((ulong)(byte)*param_3 << 0x3c) < 0)) {
      afStack_1060[0x200] = 0.0;
      afStack_1060[0x201] = 0.0;
      afStack_1060[0x202] = 0.0;
      afStack_1060[0x203] = 1.0;
      fVar15 = (float)((int)(short)param_3[2] + (int)(short)param_3[3]);
      fVar12 = (float)GetRad(90.0 - fVar15);
      fVar12 = sinf(fVar12);
      fVar13 = this->scale_y * -fVar12 * 101.0;
      fVar12 = (float)GetRad(90.0 - fVar15);
      afStack_1060[0x204] = cosf(fVar12);
      afStack_1060[0x204] = this->scale_y * 101.0 * afStack_1060[0x204];
      afStack_1060[0x206] = 0.0;
      afStack_1060[0x207] = 1.0;
      afStack_1060[0x205] = fVar13;
      if ((param_3[4] == 0) || (param_3[3] == param_3[4])) {
        if ((short)param_3[3] < 6) {
          fVar15 = (float)(int)(short)param_3[2] + ((float)(int)(short)param_3[3] * 2.0) / 3.0;
          fVar12 = (float)GetRad(90.0 - fVar15);
          fVar12 = sinf(fVar12);
          fVar13 = this->scale_y * -fVar12 * 101.0;
          fVar12 = (float)GetRad(90.0 - fVar15);
          afStack_1060[0x208] = cosf(fVar12);
          afStack_1060[0x208] = this->scale_y * 101.0 * afStack_1060[0x208];
          afStack_1060[0x20a] = 0.0;
          afStack_1060[0x20b] = 1.0;
          fVar15 = (float)(int)(short)param_3[2] + (float)(int)(short)param_3[3] / 3.0;
          afStack_1060[0x209] = fVar13;
          fVar12 = (float)GetRad(90.0 - fVar15);
          fVar12 = sinf(fVar12);
          fVar13 = this->scale_y * -fVar12 * 101.0;
          fVar12 = (float)GetRad(90.0 - fVar15);
          afStack_1060[0x20c] = cosf(fVar12);
          afStack_1060[0x20c] = this->scale_y * 101.0 * afStack_1060[0x20c];
          afStack_1060[0x20e] = 0.0;
          afStack_1060[0x20f] = 1.0;
          uVar2 = param_3[2];
          afStack_1060[0x20d] = fVar13;
          fVar12 = (float)GetRad(90.0 - (float)(int)(short)uVar2);
          fVar12 = sinf(fVar12);
          fVar13 = this->scale_y * -fVar12 * 101.0;
          fVar12 = (float)GetRad(90.0 - (float)(int)(short)uVar2);
          afStack_1060[0x210] = cosf(fVar12);
          afStack_1060[0x210] = this->scale_y * 101.0 * afStack_1060[0x210];
          afStack_1060[0x212] = 0.0;
          afStack_1060[0x213] = 1.0;
          afStack_1060[0x211] = fVar13;
          if (param_3[4] == 0) {
            iVar6 = 0;
            iVar7 = 4;
          }
          else {
            iVar6 = 4;
            iVar7 = 0;
          }
        }
        else {
          fVar15 = fVar15 - 2.0;
          fVar12 = (float)GetRad(90.0 - fVar15);
          fVar12 = sinf(fVar12);
          fVar13 = this->scale_y * -fVar12 * 101.0;
          fVar12 = (float)GetRad(90.0 - fVar15);
          afStack_1060[0x208] = cosf(fVar12);
          afStack_1060[0x208] = this->scale_y * 101.0 * afStack_1060[0x208];
          afStack_1060[0x20a] = 0.0;
          afStack_1060[0x20b] = 1.0;
          iVar7 = 3;
          afStack_1060[0x209] = fVar13;
          while ((float)((short)param_3[2] + 2) < fVar15) {
            fVar15 = fVar15 - 11.25;
            if (fVar15 <= (float)((short)param_3[2] + 2)) {
              fVar15 = (float)((short)param_3[2] + 2);
            }
            fVar12 = (float)GetRad(90.0 - fVar15);
            fVar12 = sinf(fVar12);
            fVar13 = this->scale_y * -fVar12 * 101.0;
            fVar12 = (float)GetRad(90.0 - fVar15);
            fVar12 = cosf(fVar12);
            afStack_1060[iVar7 * 4 + 0x200] = this->scale_y * 101.0 * fVar12;
            afStack_1060[iVar7 * 4 + 0x201] = fVar13;
            afStack_1060[iVar7 * 4 + 0x202] = 0.0;
            afStack_1060[iVar7 * 4 + 0x203] = 1.0;
            iVar7 = iVar7 + 1;
          }
          uVar2 = param_3[2];
          fVar12 = (float)GetRad(90.0 - (float)(int)(short)uVar2);
          fVar12 = sinf(fVar12);
          fVar13 = this->scale_y * -fVar12 * 101.0;
          fVar12 = (float)GetRad(90.0 - (float)(int)(short)uVar2);
          fVar12 = cosf(fVar12);
          afStack_1060[iVar7 * 4 + 0x200] = this->scale_y * 101.0 * fVar12;
          afStack_1060[iVar7 * 4 + 0x201] = fVar13;
          afStack_1060[iVar7 * 4 + 0x202] = 0.0;
          afStack_1060[iVar7 * 4 + 0x203] = 1.0;
          if (param_3[4] == 0) {
            iVar6 = 0;
          }
          else {
            iVar6 = iVar7;
            iVar7 = 0;
          }
        }
      }
      else {
        if ((short)param_3[4] < 5) {
          fVar14 = ((float)(int)(short)param_3[4] * 2.0) / 5.0;
          fVar15 = fVar15 - fVar14;
          fVar12 = (float)GetRad(90.0 - fVar15);
          fVar12 = sinf(fVar12);
          fVar13 = this->scale_y;
          __x = (float)GetRad(90.0 - fVar15);
          afStack_1060[0x208] = cosf(__x);
          afStack_1060[0x208] = this->scale_y * 101.0 * afStack_1060[0x208];
          afStack_1060[0x20a] = 0.0;
          afStack_1060[0x20b] = 1.0;
          afStack_1060[0x209] = fVar13 * -fVar12 * 101.0;
          fVar12 = (float)GetRad(90.0 - (fVar15 - fVar14));
          fVar12 = sinf(fVar12);
          fVar13 = this->scale_y * -fVar12 * 101.0;
          fVar12 = (float)GetRad(90.0 - (fVar15 - fVar14));
          afStack_1060[0x20c] = cosf(fVar12);
          afStack_1060[0x20c] = this->scale_y * 101.0 * afStack_1060[0x20c];
          afStack_1060[0x20e] = 0.0;
          afStack_1060[0x20f] = 1.0;
          iVar6 = 3;
          iVar7 = 4;
          afStack_1060[0x20d] = fVar13;
        }
        else {
          fVar15 = fVar15 - 2.0;
          fVar12 = (float)GetRad(90.0 - fVar15);
          fVar12 = sinf(fVar12);
          fVar13 = this->scale_y * -fVar12 * 101.0;
          fVar12 = (float)GetRad(90.0 - fVar15);
          afStack_1060[0x208] = cosf(fVar12);
          afStack_1060[0x208] = this->scale_y * 101.0 * afStack_1060[0x208];
          afStack_1060[0x20a] = 0.0;
          afStack_1060[0x20b] = 1.0;
          iVar7 = 3;
          afStack_1060[0x209] = fVar13;
          while ((float)(((int)(short)param_3[2] + (int)(short)param_3[3]) -
                        ((short)param_3[4] + -1)) < fVar15) {
            fVar15 = fVar15 - 11.25;
            if (fVar15 <= (float)(((int)(short)param_3[2] + (int)(short)param_3[3]) -
                                 ((short)param_3[4] + -1))) {
              fVar15 = (float)(((int)(short)param_3[2] + (int)(short)param_3[3]) -
                              ((short)param_3[4] + -1));
            }
            fVar12 = (float)GetRad(90.0 - fVar15);
            fVar12 = sinf(fVar12);
            fVar13 = this->scale_y * -fVar12 * 101.0;
            fVar12 = (float)GetRad(90.0 - fVar15);
            fVar12 = cosf(fVar12);
            afStack_1060[iVar7 * 4 + 0x200] = this->scale_y * 101.0 * fVar12;
            afStack_1060[iVar7 * 4 + 0x201] = fVar13;
            afStack_1060[iVar7 * 4 + 0x202] = 0.0;
            afStack_1060[iVar7 * 4 + 0x203] = 1.0;
            iVar7 = iVar7 + 1;
          }
          iVar6 = iVar7 + -1;
        }
        if ((int)(short)param_3[3] - (int)(short)param_3[4] < 5) {
          fVar15 = (float)(((int)(short)param_3[2] + (int)(short)param_3[3]) -
                          (int)(short)param_3[4]) -
                   (float)((int)(short)param_3[3] - (int)(short)param_3[4]) / 5.0;
          fVar12 = (float)GetRad(90.0 - fVar15);
          fVar12 = sinf(fVar12);
          fVar13 = this->scale_y * -fVar12 * 101.0;
          fVar12 = (float)GetRad(90.0 - fVar15);
          fVar12 = cosf(fVar12);
          afStack_1060[iVar7 * 4 + 0x200] = this->scale_y * 101.0 * fVar12;
          afStack_1060[iVar7 * 4 + 0x201] = fVar13;
          afStack_1060[iVar7 * 4 + 0x202] = 0.0;
          afStack_1060[iVar7 * 4 + 0x203] = 1.0;
          fVar15 = (float)(((int)(short)param_3[2] + (int)(short)param_3[3]) -
                          (int)(short)param_3[4]) -
                   ((float)((int)(short)param_3[3] - (int)(short)param_3[4]) * 3.0) / 5.0;
          fVar12 = (float)GetRad(90.0 - fVar15);
          fVar12 = sinf(fVar12);
          fVar13 = this->scale_y * -fVar12 * 101.0;
          fVar12 = (float)GetRad(90.0 - fVar15);
          fVar12 = cosf(fVar12);
          iVar9 = iVar7 + 1;
          afStack_1060[iVar9 * 4 + 0x200] = this->scale_y * 101.0 * fVar12;
          afStack_1060[iVar9 * 4 + 0x201] = fVar13;
          afStack_1060[iVar9 * 4 + 0x202] = 0.0;
          afStack_1060[iVar9 * 4 + 0x203] = 1.0;
          uVar2 = param_3[2];
          fVar12 = (float)GetRad(90.0 - (float)(int)(short)uVar2);
          fVar12 = sinf(fVar12);
          fVar13 = this->scale_y * -fVar12 * 101.0;
          fVar12 = (float)GetRad(90.0 - (float)(int)(short)uVar2);
          fVar12 = cosf(fVar12);
          iVar7 = iVar7 + 2;
          afStack_1060[iVar7 * 4 + 0x200] = this->scale_y * 101.0 * fVar12;
          afStack_1060[iVar7 * 4 + 0x201] = fVar13;
          afStack_1060[iVar7 * 4 + 0x202] = 0.0;
          afStack_1060[iVar7 * 4 + 0x203] = 1.0;
          iVar7 = 3;
        }
        else {
          fVar15 = (float)((int)(short)param_3[2] + (int)(short)param_3[3]) -
                   ((float)(int)(short)param_3[4] + 1.0);
          fVar12 = (float)GetRad(90.0 - fVar15);
          fVar12 = sinf(fVar12);
          fVar13 = this->scale_y * -fVar12 * 101.0;
          fVar12 = (float)GetRad(90.0 - fVar15);
          fVar12 = cosf(fVar12);
          afStack_1060[iVar7 * 4 + 0x200] = this->scale_y * 101.0 * fVar12;
          afStack_1060[iVar7 * 4 + 0x201] = fVar13;
          afStack_1060[iVar7 * 4 + 0x202] = 0.0;
          afStack_1060[iVar7 * 4 + 0x203] = 1.0;
          while (iVar7 = iVar7 + 1, (float)((short)param_3[2] + 2) < fVar15) {
            fVar15 = fVar15 - 11.25;
            if (fVar15 <= (float)((short)param_3[2] + 2)) {
              fVar15 = (float)((short)param_3[2] + 2);
            }
            fVar12 = (float)GetRad(90.0 - fVar15);
            fVar12 = sinf(fVar12);
            fVar13 = this->scale_y * -fVar12 * 101.0;
            fVar12 = (float)GetRad(90.0 - fVar15);
            fVar12 = cosf(fVar12);
            afStack_1060[iVar7 * 4 + 0x200] = this->scale_y * 101.0 * fVar12;
            afStack_1060[iVar7 * 4 + 0x201] = fVar13;
            afStack_1060[iVar7 * 4 + 0x202] = 0.0;
            afStack_1060[iVar7 * 4 + 0x203] = 1.0;
          }
          uVar2 = param_3[2];
          fVar12 = (float)GetRad(90.0 - (float)(int)(short)uVar2);
          fVar12 = sinf(fVar12);
          fVar13 = this->scale_y * -fVar12 * 101.0;
          fVar12 = (float)GetRad(90.0 - (float)(int)(short)uVar2);
          fVar12 = cosf(fVar12);
          afStack_1060[iVar7 * 4 + 0x200] = this->scale_y * 101.0 * fVar12;
          afStack_1060[iVar7 * 4 + 0x201] = fVar13;
          afStack_1060[iVar7 * 4 + 0x202] = 0.0;
          afStack_1060[iVar7 * 4 + 0x203] = 1.0;
          iVar7 = iVar7 - iVar6;
        }
      }
      RotTransVector(afStack_1060,afStack_1060 + 0x200,auStack_60,iVar6 + iVar7 + 1);
      sceVu0RotTransPersN(aiStack_1860,this + 0x590,afStack_1060,iVar6 + iVar7 + 1,0);
      for (iVar9 = 0; iVar9 < iVar6 + iVar7 + 1; iVar9 = iVar9 + 1) {
        aiStack_1860[iVar9 * 4] =
             (int)((float)aiStack_1860[iVar9 * 4] + (this->cx - 256.0) * 16.0);
        aiStack_1860[iVar9 * 4 + 1] =
             (int)((float)aiStack_1860[iVar9 * 4 + 1] + (this->cy - 224.0) * 16.0)
        ;
        aiStack_1860[iVar9 * 4 + 2] = (int)((float)aiStack_1860[iVar9 * 4 + 2] / 16.0);
      }
      if ((((ulong)*(byte *)((int)param_3 + 1) & 7) >> 1 == 1) ||
         (((ulong)*(byte *)((int)param_3 + 1) & 7) >> 1 == 3)) {
        fVar12 = (float)(byte)param_3[6] +
                 (255.0 - (float)(byte)param_3[6]) * param_3->f32_10;
        if (fVar12 < 2.1474836e+09) {
          uVar3 = (undefined1)(int)fVar12;
        }
        else {
          uVar3 = (undefined1)(int)(fVar12 - 2.1474836e+09);
        }
        fVar12 = (float)*(byte *)((int)param_3 + 0xd) +
                 (255.0 - (float)*(byte *)((int)param_3 + 0xd)) * param_3->f32_10;
        if (fVar12 < 2.1474836e+09) {
          uVar4 = (undefined1)(int)fVar12;
        }
        else {
          uVar4 = (undefined1)(int)(fVar12 - 2.1474836e+09);
        }
        auStack_18 = (undefined1  [2])CONCAT11(uVar4,uVar3);
        fVar12 = (float)(byte)param_3[7] +
                 (255.0 - (float)(byte)param_3[7]) * param_3->f32_10;
        if (fVar12 < 2.1474836e+09) {
          uVar3 = (undefined1)(int)fVar12;
        }
        else {
          uVar3 = (undefined1)(int)(fVar12 - 2.1474836e+09);
        }
        _auStack_18 = CONCAT12(uVar3,auStack_18);
      }
      else if ((((ulong)(byte)*param_3 & 0x3f) >> 4 == 1) ||
              (((ulong)(byte)*param_3 & 0x3f) >> 4 == 3)) {
        if (param_3->f32_e <= 0.75) {
          fVar12 = (float)(byte)param_3[6] * (param_3->f32_e + 0.25);
          if (fVar12 < 2.1474836e+09) {
            uVar3 = (undefined1)(int)fVar12;
          }
          else {
            uVar3 = (undefined1)(int)(fVar12 - 2.1474836e+09);
          }
          fVar12 = (float)*(byte *)((int)param_3 + 0xd) * (param_3->f32_e + 0.25);
          if (fVar12 < 2.1474836e+09) {
            uVar4 = (undefined1)(int)fVar12;
          }
          else {
            uVar4 = (undefined1)(int)(fVar12 - 2.1474836e+09);
          }
          auStack_18 = (undefined1  [2])CONCAT11(uVar4,uVar3);
          fVar12 = (float)(byte)param_3[7] * (param_3->f32_e + 0.25);
          if (fVar12 < 2.1474836e+09) {
            uVar3 = (undefined1)(int)fVar12;
          }
          else {
            uVar3 = (undefined1)(int)(fVar12 - 2.1474836e+09);
          }
          _auStack_18 = CONCAT12(uVar3,auStack_18);
        }
        else {
          fVar12 = (float)(byte)param_3[6] +
                   (255.0 - (float)(byte)param_3[6]) * (param_3->f32_e - 0.75);
          if (fVar12 < 2.1474836e+09) {
            uVar3 = (undefined1)(int)fVar12;
          }
          else {
            uVar3 = (undefined1)(int)(fVar12 - 2.1474836e+09);
          }
          fVar12 = (float)*(byte *)((int)param_3 + 0xd) +
                   (255.0 - (float)*(byte *)((int)param_3 + 0xd)) *
                   (param_3->f32_e - 0.75);
          if (fVar12 < 2.1474836e+09) {
            uVar4 = (undefined1)(int)fVar12;
          }
          else {
            uVar4 = (undefined1)(int)(fVar12 - 2.1474836e+09);
          }
          auStack_18 = (undefined1  [2])CONCAT11(uVar4,uVar3);
          fVar12 = (float)(byte)param_3[7] +
                   (255.0 - (float)(byte)param_3[7]) * (param_3->f32_e - 0.75);
          if (fVar12 < 2.1474836e+09) {
            uVar3 = (undefined1)(int)fVar12;
          }
          else {
            uVar3 = (undefined1)(int)(fVar12 - 2.1474836e+09);
          }
          _auStack_18 = CONCAT12(uVar3,auStack_18);
        }
      }
      else {
        _auStack_18 = param_3->uint3_6;
      }
      if ((((ulong)*(byte *)((int)param_3 + 1) & 7) >> 1 == 2) ||
         (((ulong)*(byte *)((int)param_3 + 1) & 7) >> 1 == 3)) {
        fVar12 = (float)(byte)param_3[8] +
                 (255.0 - (float)(byte)param_3[8]) * param_3->f32_10;
        if (fVar12 < 2.1474836e+09) {
          uVar3 = (undefined1)(int)fVar12;
        }
        else {
          uVar3 = (undefined1)(int)(fVar12 - 2.1474836e+09);
        }
        fVar12 = (float)*(byte *)((int)param_3 + 0x11) +
                 (255.0 - (float)*(byte *)((int)param_3 + 0x11)) * param_3->f32_10;
        if (fVar12 < 2.1474836e+09) {
          uVar4 = (undefined1)(int)fVar12;
        }
        else {
          uVar4 = (undefined1)(int)(fVar12 - 2.1474836e+09);
        }
        auStack_14 = (undefined1  [2])CONCAT11(uVar4,uVar3);
        fVar12 = (float)(byte)param_3[9] +
                 (255.0 - (float)(byte)param_3[9]) * param_3->f32_10;
        if (fVar12 < 2.1474836e+09) {
          uVar3 = (undefined1)(int)fVar12;
        }
        else {
          uVar3 = (undefined1)(int)(fVar12 - 2.1474836e+09);
        }
        _auStack_14 = CONCAT12(uVar3,auStack_14);
      }
      else if ((((ulong)(byte)*param_3 & 0x3f) >> 4 == 2) ||
              (((ulong)(byte)*param_3 & 0x3f) >> 4 == 3)) {
        if (param_3->f32_e <= 0.75) {
          fVar12 = (float)(byte)param_3[8] * (param_3->f32_e + 0.25);
          if (fVar12 < 2.1474836e+09) {
            uVar3 = (undefined1)(int)fVar12;
          }
          else {
            uVar3 = (undefined1)(int)(fVar12 - 2.1474836e+09);
          }
          fVar12 = (float)*(byte *)((int)param_3 + 0x11) * (param_3->f32_e + 0.25);
          if (fVar12 < 2.1474836e+09) {
            uVar4 = (undefined1)(int)fVar12;
          }
          else {
            uVar4 = (undefined1)(int)(fVar12 - 2.1474836e+09);
          }
          auStack_14 = (undefined1  [2])CONCAT11(uVar4,uVar3);
          fVar12 = (float)(byte)param_3[9] * (param_3->f32_e + 0.25);
          if (fVar12 < 2.1474836e+09) {
            uVar3 = (undefined1)(int)fVar12;
          }
          else {
            uVar3 = (undefined1)(int)(fVar12 - 2.1474836e+09);
          }
          _auStack_14 = CONCAT12(uVar3,auStack_14);
        }
        else {
          fVar12 = (float)(byte)param_3[8] +
                   (255.0 - (float)(byte)param_3[8]) * (param_3->f32_e - 0.75);
          if (fVar12 < 2.1474836e+09) {
            uVar3 = (undefined1)(int)fVar12;
          }
          else {
            uVar3 = (undefined1)(int)(fVar12 - 2.1474836e+09);
          }
          fVar12 = (float)*(byte *)((int)param_3 + 0x11) +
                   (255.0 - (float)*(byte *)((int)param_3 + 0x11)) *
                   (param_3->f32_e - 0.75);
          if (fVar12 < 2.1474836e+09) {
            uVar4 = (undefined1)(int)fVar12;
          }
          else {
            uVar4 = (undefined1)(int)(fVar12 - 2.1474836e+09);
          }
          auStack_14 = (undefined1  [2])CONCAT11(uVar4,uVar3);
          fVar12 = (float)(byte)param_3[9] +
                   (255.0 - (float)(byte)param_3[9]) * (param_3->f32_e - 0.75);
          if (fVar12 < 2.1474836e+09) {
            uVar3 = (undefined1)(int)fVar12;
          }
          else {
            uVar3 = (undefined1)(int)(fVar12 - 2.1474836e+09);
          }
          _auStack_14 = CONCAT12(uVar3,auStack_14);
        }
      }
      else {
        _auStack_14 = param_3->uint3_8;
      }
      if ((((ulong)*param_3 & 0x1ff) >> 7 == 1) || (((ulong)*param_3 & 0x1ff) >> 7 == 3)) {
        auStack_18 = (undefined1  [2])CONCAT11(auStack_18[1] >> 1,auStack_18[0] >> 1);
        _auStack_18 = CONCAT12(bStack_16 >> 1,auStack_18);
      }
      if ((((ulong)*param_3 & 0x1ff) >> 7 == 2) || (((ulong)*param_3 & 0x1ff) >> 7 == 3)) {
        auStack_14 = (undefined1  [2])CONCAT11(auStack_14[1] >> 1,auStack_14[0] >> 1);
        _auStack_14 = CONCAT12(bStack_12 >> 1,auStack_14);
      }
      *param_2 = 0x6400000000000001;
      param_2[1] = 0xc1c1f0;
      param_2[2] = 0x4d;
      param_2[3] = 0;
      fVar12 = this->scale_x * 31.0;
      if (2.1474836e+09 <= fVar12) {
        fVar12 = fVar12 - 2.1474836e+09;
      }
      param_2[4] = ((long)(int)fVar12 & 0xffU) << 0x18 |
                   (ulong)(uint)(16.0 / (float)aiStack_1860[3]) << 0x20;
      param_2[5] = (long)aiStack_1860[2] << 0x20 |
                   (long)aiStack_1860[0] | (long)aiStack_1860[1] << 0x10;
      puVar11 = param_2 + 6;
      fVar12 = 16.0 / (float)iStack_1844;
      if (param_3[3] == 0x168) {
        if (param_3[4] == 0) {
          fVar13 = this->scale_x * 127.0;
          if (2.1474836e+09 <= fVar13) {
            fVar13 = fVar13 - 2.1474836e+09;
          }
          *puVar11 = (ulong)(uint)fVar12 << 0x20 |
                     ((long)(int)fVar13 & 0xffU) << 0x18 | (ulong)_auStack_18;
        }
        else {
          fVar13 = this->scale_x * 127.0;
          if (2.1474836e+09 <= fVar13) {
            fVar13 = fVar13 - 2.1474836e+09;
          }
          *puVar11 = (ulong)(uint)fVar12 << 0x20 |
                     ((long)(int)fVar13 & 0xffU) << 0x18 | (ulong)_auStack_14;
        }
      }
      else if (param_3[4] == 0) {
        fVar13 = this->scale_x * 15.0;
        if (2.1474836e+09 <= fVar13) {
          fVar13 = fVar13 - 2.1474836e+09;
        }
        *puVar11 = (ulong)(uint)fVar12 << 0x20 |
                   ((long)(int)fVar13 & 0xffU) << 0x18 | (ulong)_auStack_18;
      }
      else {
        fVar13 = this->scale_x * 15.0;
        if (2.1474836e+09 <= fVar13) {
          fVar13 = fVar13 - 2.1474836e+09;
        }
        *puVar11 = (ulong)(uint)fVar12 << 0x20 |
                   ((long)(int)fVar13 & 0xffU) << 0x18 | (ulong)_auStack_14;
      }
      param_2[7] = (long)iStack_1848 << 0x20 | (long)aiStack_1860[4] | (long)aiStack_1860[5] << 0x10
      ;
      if (param_4 == '\x01') {
        param_2[8] = (long)(iVar6 + iVar7 + -1) | 0x2400000000008000;
      }
      else {
        param_2[8] = (long)(iVar6 + iVar7 + -1) | 0x2400000000000000;
      }
      param_2[9] = 0x41;
      param_2 = param_2 + 10;
      if ((iVar6 == 0) || (iVar7 == 0)) {
        for (iVar9 = 2; iVar9 < iVar6 + iVar7; iVar9 = iVar9 + 1) {
          if (iVar6 == 0) {
            fVar12 = this->scale_x * 127.0;
            if (2.1474836e+09 <= fVar12) {
              fVar12 = fVar12 - 2.1474836e+09;
            }
            *param_2 = (ulong)(uint)(16.0 / (float)aiStack_1860[iVar9 * 4 + 3]) << 0x20 |
                       ((long)(int)fVar12 & 0xffU) << 0x18 | (ulong)_auStack_18;
          }
          else {
            fVar12 = this->scale_x * 127.0;
            if (2.1474836e+09 <= fVar12) {
              fVar12 = fVar12 - 2.1474836e+09;
            }
            *param_2 = (ulong)(uint)(16.0 / (float)aiStack_1860[iVar9 * 4 + 3]) << 0x20 |
                       ((long)(int)fVar12 & 0xffU) << 0x18 | (ulong)_auStack_14;
          }
          param_2[1] = (long)aiStack_1860[iVar9 * 4 + 2] << 0x20 |
                       (long)aiStack_1860[iVar9 * 4] | (long)aiStack_1860[iVar9 * 4 + 1] << 0x10;
          param_2 = param_2 + 2;
        }
      }
      else {
        for (iVar8 = 2; iVar9 = iVar6, iVar8 < iVar6 + 1; iVar8 = iVar8 + 1) {
          fVar12 = this->scale_x * 127.0;
          if (2.1474836e+09 <= fVar12) {
            fVar12 = fVar12 - 2.1474836e+09;
          }
          *param_2 = (ulong)(uint)(16.0 / (float)aiStack_1860[iVar8 * 4 + 3]) << 0x20 |
                     ((long)(int)fVar12 & 0xffU) << 0x18 | (ulong)_auStack_14;
          param_2[1] = (long)aiStack_1860[iVar8 * 4 + 2] << 0x20 |
                       (long)aiStack_1860[iVar8 * 4] | (long)aiStack_1860[iVar8 * 4 + 1] << 0x10;
          param_2 = param_2 + 2;
        }
        while (iVar9 = iVar9 + 1, iVar9 < iVar6 + iVar7) {
          fVar12 = this->scale_x * 127.0;
          if (2.1474836e+09 <= fVar12) {
            fVar12 = fVar12 - 2.1474836e+09;
          }
          *param_2 = (ulong)(uint)(16.0 / (float)aiStack_1860[iVar9 * 4 + 3]) << 0x20 |
                     ((long)(int)fVar12 & 0xffU) << 0x18 | (ulong)_auStack_18;
          param_2[1] = (long)aiStack_1860[iVar9 * 4 + 2] << 0x20 |
                       (long)aiStack_1860[iVar9 * 4] | (long)aiStack_1860[iVar9 * 4 + 1] << 0x10;
          param_2 = param_2 + 2;
        }
      }
      fVar12 = 16.0 / (float)aiStack_1860[iVar9 * 4 + 3];
      if (param_3[3] == 0x168) {
        if (param_3[3] == param_3[4]) {
          fVar13 = this->scale_x * 127.0;
          if (2.1474836e+09 <= fVar13) {
            fVar13 = fVar13 - 2.1474836e+09;
          }
          *param_2 = (ulong)(uint)fVar12 << 0x20 |
                     ((long)(int)fVar13 & 0xffU) << 0x18 | (ulong)_auStack_14;
        }
        else {
          fVar13 = this->scale_x * 127.0;
          if (2.1474836e+09 <= fVar13) {
            fVar13 = fVar13 - 2.1474836e+09;
          }
          *param_2 = (ulong)(uint)fVar12 << 0x20 |
                     ((long)(int)fVar13 & 0xffU) << 0x18 | (ulong)_auStack_18;
        }
      }
      else if (param_3[3] == param_3[4]) {
        fVar13 = this->scale_x * 15.0;
        if (2.1474836e+09 <= fVar13) {
          fVar13 = fVar13 - 2.1474836e+09;
        }
        *param_2 = (ulong)(uint)fVar12 << 0x20 |
                   ((long)(int)fVar13 & 0xffU) << 0x18 | (ulong)_auStack_14;
      }
      else {
        fVar13 = this->scale_x * 15.0;
        if (2.1474836e+09 <= fVar13) {
          fVar13 = fVar13 - 2.1474836e+09;
        }
        *param_2 = (ulong)(uint)fVar12 << 0x20 |
                   ((long)(int)fVar13 & 0xffU) << 0x18 | (ulong)_auStack_18;
      }
      param_2[1] = (long)aiStack_1860[iVar9 * 4 + 2] << 0x20 |
                   (long)aiStack_1860[iVar9 * 4] | (long)aiStack_1860[iVar9 * 4 + 1] << 0x10;
      param_2 = param_2 + 2;
    }
  }
  else if (((bVar1 == 0) && (0 < (short)param_3[3])) && ((long)((ulong)(byte)*param_3 << 0x3c) < 0))
  {
    afStack_1060[0x200] = 0.0;
    afStack_1060[0x201] = 0.0;
    afStack_1060[0x202] = 0.0;
    afStack_1060[0x203] = 1.0;
    fVar15 = (float)((int)(short)param_3[2] + (int)(short)param_3[3]);
    fVar12 = (float)GetRad(90.0 - fVar15);
    fVar12 = sinf(fVar12);
    fVar13 = this->scale_y * -fVar12 * 101.0;
    fVar12 = (float)GetRad(90.0 - fVar15);
    afStack_1060[0x204] = cosf(fVar12);
    afStack_1060[0x204] = this->scale_y * 101.0 * afStack_1060[0x204];
    afStack_1060[0x206] = 0.0;
    afStack_1060[0x207] = 1.0;
    afStack_1060[0x205] = fVar13;
    if ((short)param_3[3] < 6) {
      fVar15 = (float)(int)(short)param_3[2] + ((float)(int)(short)param_3[3] * 2.0) / 3.0;
      fVar12 = (float)GetRad(90.0 - fVar15);
      fVar12 = sinf(fVar12);
      fVar13 = this->scale_y * -fVar12 * 101.0;
      fVar12 = (float)GetRad(90.0 - fVar15);
      afStack_1060[0x208] = cosf(fVar12);
      afStack_1060[0x208] = this->scale_y * 101.0 * afStack_1060[0x208];
      afStack_1060[0x20a] = 0.0;
      afStack_1060[0x20b] = 1.0;
      fVar15 = (float)(int)(short)param_3[2] + (float)(int)(short)param_3[3] / 3.0;
      afStack_1060[0x209] = fVar13;
      fVar12 = (float)GetRad(90.0 - fVar15);
      fVar12 = sinf(fVar12);
      fVar13 = this->scale_y * -fVar12 * 101.0;
      fVar12 = (float)GetRad(90.0 - fVar15);
      afStack_1060[0x20c] = cosf(fVar12);
      afStack_1060[0x20c] = this->scale_y * 101.0 * afStack_1060[0x20c];
      afStack_1060[0x20e] = 0.0;
      afStack_1060[0x20f] = 1.0;
      uVar2 = param_3[2];
      afStack_1060[0x20d] = fVar13;
      fVar12 = (float)GetRad(90.0 - (float)(int)(short)uVar2);
      fVar12 = sinf(fVar12);
      fVar13 = this->scale_y * -fVar12 * 101.0;
      fVar12 = (float)GetRad(90.0 - (float)(int)(short)uVar2);
      afStack_1060[0x210] = cosf(fVar12);
      afStack_1060[0x210] = this->scale_y * 101.0 * afStack_1060[0x210];
      afStack_1060[0x212] = 0.0;
      afStack_1060[0x213] = 1.0;
      iVar6 = 4;
      afStack_1060[0x211] = fVar13;
    }
    else {
      fVar15 = fVar15 - 2.0;
      fVar12 = (float)GetRad(90.0 - fVar15);
      fVar12 = sinf(fVar12);
      fVar13 = this->scale_y * -fVar12 * 101.0;
      fVar12 = (float)GetRad(90.0 - fVar15);
      afStack_1060[0x208] = cosf(fVar12);
      afStack_1060[0x208] = this->scale_y * 101.0 * afStack_1060[0x208];
      afStack_1060[0x20a] = 0.0;
      afStack_1060[0x20b] = 1.0;
      iVar6 = 3;
      afStack_1060[0x209] = fVar13;
      while ((float)((short)param_3[2] + 2) < fVar15) {
        fVar15 = fVar15 - 11.25;
        if (fVar15 <= (float)((short)param_3[2] + 2)) {
          fVar15 = (float)((short)param_3[2] + 2);
        }
        fVar12 = (float)GetRad(90.0 - fVar15);
        fVar12 = sinf(fVar12);
        fVar13 = this->scale_y * -fVar12 * 101.0;
        fVar12 = (float)GetRad(90.0 - fVar15);
        fVar12 = cosf(fVar12);
        afStack_1060[iVar6 * 4 + 0x200] = this->scale_y * 101.0 * fVar12;
        afStack_1060[iVar6 * 4 + 0x201] = fVar13;
        afStack_1060[iVar6 * 4 + 0x202] = 0.0;
        afStack_1060[iVar6 * 4 + 0x203] = 1.0;
        iVar6 = iVar6 + 1;
      }
      uVar2 = param_3[2];
      fVar12 = (float)GetRad(90.0 - (float)(int)(short)uVar2);
      fVar12 = sinf(fVar12);
      fVar13 = this->scale_y * -fVar12 * 101.0;
      fVar12 = (float)GetRad(90.0 - (float)(int)(short)uVar2);
      fVar12 = cosf(fVar12);
      afStack_1060[iVar6 * 4 + 0x200] = this->scale_y * 101.0 * fVar12;
      afStack_1060[iVar6 * 4 + 0x201] = fVar13;
      afStack_1060[iVar6 * 4 + 0x202] = 0.0;
      afStack_1060[iVar6 * 4 + 0x203] = 1.0;
    }
    RotTransVector(afStack_1060,afStack_1060 + 0x200,auStack_60,iVar6 + 1);
    sceVu0RotTransPersN(aiStack_1860,this + 0x590,afStack_1060,iVar6 + 1,0);
    for (iVar7 = 0; iVar7 < iVar6 + 1; iVar7 = iVar7 + 1) {
      aiStack_1860[iVar7 * 4] =
           (int)((float)aiStack_1860[iVar7 * 4] + (this->cx - 256.0) * 16.0);
      aiStack_1860[iVar7 * 4 + 1] =
           (int)((float)aiStack_1860[iVar7 * 4 + 1] + (this->cy - 224.0) * 16.0);
      aiStack_1860[iVar7 * 4 + 2] = (int)((float)aiStack_1860[iVar7 * 4 + 2] / 16.0);
    }
    if ((((ulong)(byte)*param_3 & 0x3f) >> 4 == 0) &&
       (((ulong)*(byte *)((int)param_3 + 1) & 7) >> 1 == 0)) {
      _auStack_18 = param_3->uint3_6;
    }
    else if (((ulong)*(byte *)((int)param_3 + 1) & 7) >> 1 == 0) {
      if (param_3->f32_e <= 0.75) {
        fVar12 = (float)(byte)param_3[6] * (param_3->f32_e + 0.25);
        if (fVar12 < 2.1474836e+09) {
          uVar3 = (undefined1)(int)fVar12;
        }
        else {
          uVar3 = (undefined1)(int)(fVar12 - 2.1474836e+09);
        }
        fVar12 = (float)*(byte *)((int)param_3 + 0xd) * (param_3->f32_e + 0.25);
        if (fVar12 < 2.1474836e+09) {
          uVar4 = (undefined1)(int)fVar12;
        }
        else {
          uVar4 = (undefined1)(int)(fVar12 - 2.1474836e+09);
        }
        auStack_18 = (undefined1  [2])CONCAT11(uVar4,uVar3);
        fVar12 = (float)(byte)param_3[7] * (param_3->f32_e + 0.25);
        if (fVar12 < 2.1474836e+09) {
          uVar3 = (undefined1)(int)fVar12;
        }
        else {
          uVar3 = (undefined1)(int)(fVar12 - 2.1474836e+09);
        }
        _auStack_18 = CONCAT12(uVar3,auStack_18);
      }
      else {
        fVar12 = (float)(byte)param_3[6] +
                 (255.0 - (float)(byte)param_3[6]) * (param_3->f32_e - 0.75);
        if (fVar12 < 2.1474836e+09) {
          uVar3 = (undefined1)(int)fVar12;
        }
        else {
          uVar3 = (undefined1)(int)(fVar12 - 2.1474836e+09);
        }
        fVar12 = (float)*(byte *)((int)param_3 + 0xd) +
                 (255.0 - (float)*(byte *)((int)param_3 + 0xd)) * (param_3->f32_e - 0.75)
        ;
        if (fVar12 < 2.1474836e+09) {
          uVar4 = (undefined1)(int)fVar12;
        }
        else {
          uVar4 = (undefined1)(int)(fVar12 - 2.1474836e+09);
        }
        auStack_18 = (undefined1  [2])CONCAT11(uVar4,uVar3);
        fVar12 = (float)(byte)param_3[7] +
                 (255.0 - (float)(byte)param_3[7]) * (param_3->f32_e - 0.75);
        if (fVar12 < 2.1474836e+09) {
          uVar3 = (undefined1)(int)fVar12;
        }
        else {
          uVar3 = (undefined1)(int)(fVar12 - 2.1474836e+09);
        }
        _auStack_18 = CONCAT12(uVar3,auStack_18);
      }
    }
    else {
      fVar12 = (float)(byte)param_3[6] +
               (255.0 - (float)(byte)param_3[6]) * param_3->f32_10;
      if (fVar12 < 2.1474836e+09) {
        uVar3 = (undefined1)(int)fVar12;
      }
      else {
        uVar3 = (undefined1)(int)(fVar12 - 2.1474836e+09);
      }
      fVar12 = (float)*(byte *)((int)param_3 + 0xd) +
               (255.0 - (float)*(byte *)((int)param_3 + 0xd)) * param_3->f32_10;
      if (fVar12 < 2.1474836e+09) {
        uVar4 = (undefined1)(int)fVar12;
      }
      else {
        uVar4 = (undefined1)(int)(fVar12 - 2.1474836e+09);
      }
      auStack_18 = (undefined1  [2])CONCAT11(uVar4,uVar3);
      fVar12 = (float)(byte)param_3[7] +
               (255.0 - (float)(byte)param_3[7]) * param_3->f32_10;
      if (fVar12 < 2.1474836e+09) {
        uVar3 = (undefined1)(int)fVar12;
      }
      else {
        uVar3 = (undefined1)(int)(fVar12 - 2.1474836e+09);
      }
      _auStack_18 = CONCAT12(uVar3,auStack_18);
    }
    if (((ulong)*param_3 & 0x1ff) >> 7 != 0) {
      auStack_18 = (undefined1  [2])CONCAT11(auStack_18[1] >> 1,auStack_18[0] >> 1);
      _auStack_18 = CONCAT12(bStack_16 >> 1,auStack_18);
    }
    *param_2 = 0x6400000000000001;
    param_2[1] = 0xc1c1f0;
    param_2[2] = 0x4d;
    param_2[3] = 0;
    fVar12 = this->scale_x * 31.0;
    if (2.1474836e+09 <= fVar12) {
      fVar12 = fVar12 - 2.1474836e+09;
    }
    param_2[4] = ((long)(int)fVar12 & 0xffU) << 0x18 |
                 (ulong)(uint)(16.0 / (float)aiStack_1860[3]) << 0x20;
    param_2[5] = (long)aiStack_1860[2] << 0x20 |
                 (long)aiStack_1860[0] | (long)aiStack_1860[1] << 0x10;
    if (param_3[3] == 0x168) {
      fVar12 = this->scale_x * 127.0;
      if (2.1474836e+09 <= fVar12) {
        fVar12 = fVar12 - 2.1474836e+09;
      }
      param_2[6] = (ulong)(uint)(16.0 / (float)iStack_1844) << 0x20 |
                   ((long)(int)fVar12 & 0xffU) << 0x18 | (ulong)_auStack_18;
    }
    else {
      fVar12 = this->scale_x * 15.0;
      if (2.1474836e+09 <= fVar12) {
        fVar12 = fVar12 - 2.1474836e+09;
      }
      param_2[6] = (ulong)(uint)(16.0 / (float)iStack_1844) << 0x20 |
                   ((long)(int)fVar12 & 0xffU) << 0x18 | (ulong)_auStack_18;
    }
    param_2[7] = (long)iStack_1848 << 0x20 | (long)aiStack_1860[4] | (long)aiStack_1860[5] << 0x10;
    if (param_4 == '\x01') {
      param_2[8] = (long)(iVar6 + -1) | 0x2400000000008000;
    }
    else {
      param_2[8] = (long)(iVar6 + -1) | 0x2400000000000000;
    }
    param_2[9] = 0x41;
    param_2 = param_2 + 10;
    for (iVar7 = 2; iVar7 < iVar6; iVar7 = iVar7 + 1) {
      fVar12 = this->scale_x * 127.0;
      if (2.1474836e+09 <= fVar12) {
        fVar12 = fVar12 - 2.1474836e+09;
      }
      *param_2 = (ulong)(uint)(16.0 / (float)aiStack_1860[iVar7 * 4 + 3]) << 0x20 |
                 ((long)(int)fVar12 & 0xffU) << 0x18 | (ulong)_auStack_18;
      param_2[1] = (long)aiStack_1860[iVar7 * 4 + 2] << 0x20 |
                   (long)aiStack_1860[iVar7 * 4] | (long)aiStack_1860[iVar7 * 4 + 1] << 0x10;
      param_2 = param_2 + 2;
    }
    if (param_3[3] == 0x168) {
      fVar12 = this->scale_x * 127.0;
      if (2.1474836e+09 <= fVar12) {
        fVar12 = fVar12 - 2.1474836e+09;
      }
      *param_2 = (ulong)(uint)(16.0 / (float)aiStack_1860[iVar7 * 4 + 3]) << 0x20 |
                 ((long)(int)fVar12 & 0xffU) << 0x18 | (ulong)_auStack_18;
    }
    else {
      fVar12 = this->scale_x * 15.0;
      if (2.1474836e+09 <= fVar12) {
        fVar12 = fVar12 - 2.1474836e+09;
      }
      *param_2 = (ulong)(uint)(16.0 / (float)aiStack_1860[iVar7 * 4 + 3]) << 0x20 |
                 ((long)(int)fVar12 & 0xffU) << 0x18 | (ulong)_auStack_18;
    }
    param_2[1] = (long)aiStack_1860[iVar7 * 4 + 2] << 0x20 |
                 (long)aiStack_1860[iVar7 * 4] | (long)aiStack_1860[iVar7 * 4 + 1] << 0x10;
    param_2 = param_2 + 2;
  }
  return param_2;
}

// JP: 0x002d5690  AreaOn__5JRingFi  =  JRing::AreaOn
void JRing::AreaOn(int this,int param_2)

{
  int iVar1;
  int iVar2;
  
  if (((ulong)this->flagsB & 0xf) >> 2 == 3) {
    this->u8_460 = this->u8_460 & 0xf7 | 8;
  }
  else if (param_2 == -1) {
    for (iVar2 = 0; iVar2 < 0xc; iVar2 = iVar2 + 1) {
      if (*(char *)(this + iVar2 * 0x24 + 0x102) != -1) {
        iVar1 = this + iVar2 * 0x24;
        iVar1->u8_100 = iVar1->u8_100 & 0xf7 | 8;
      }
    }
    for (iVar2 = 0; iVar2 < 0xc; iVar2 = iVar2 + 1) {
      if (*(char *)(this + iVar2 * 0x24 + 0x2b2) != -1) {
        iVar1 = this + iVar2 * 0x24;
        iVar1->u8_2b0 = iVar1->u8_2b0 & 0xf7 | 8;
      }
    }
  }
  else {
    if ((param_2 < 0xc) && (*(char *)(this + param_2 * 0x24 + 0x102) != -1)) {
      iVar2 = this + param_2 * 0x24;
      iVar2->u8_100 = iVar2->u8_100 & 0xf7 | 8;
    }
    if ((param_2 < 0xc) && (*(char *)(this + param_2 * 0x24 + 0x2b2) != -1)) {
      iVar2 = this + param_2 * 0x24;
      iVar2->u8_2b0 = iVar2->u8_2b0 & 0xf7 | 8;
    }
  }
  if ((long)((ulong)this->abn_d << 0x3b) < 0) {
    this->u8_484 = this->u8_484 & 0xf7 | 8;
  }
  this->flagsA = this->flagsA & 0xf9 | 6;
  JRing::GetAreaPacketCnt(this);
  return;
}

// JP: 0x002d5990  AreaOff__5JRingFi  =  JRing::AreaOff
void JRing::AreaOff(int this,int param_2)

{
  int iVar1;
  int iVar2;
  
  if (((ulong)this->flagsB & 0xf) >> 2 == 3) {
    this->u8_460 = this->u8_460 & 0xf7;
  }
  else if (param_2 == -1) {
    for (iVar2 = 0; iVar2 < 0xc; iVar2 = iVar2 + 1) {
      if (*(char *)(this + iVar2 * 0x24 + 0x102) != -1) {
        iVar1 = this + iVar2 * 0x24;
        iVar1->u8_100 = iVar1->u8_100 & 0xf7;
      }
    }
    for (iVar2 = 0; iVar2 < 0xc; iVar2 = iVar2 + 1) {
      if (*(char *)(this + iVar2 * 0x24 + 0x2b2) != -1) {
        iVar1 = this + iVar2 * 0x24;
        iVar1->u8_2b0 = iVar1->u8_2b0 & 0xf7;
      }
    }
  }
  else {
    if ((param_2 < 0xc) && (*(char *)(this + param_2 * 0x24 + 0x102) != -1)) {
      iVar2 = this + param_2 * 0x24;
      iVar2->u8_100 = iVar2->u8_100 & 0xf7;
    }
    if ((param_2 < 0xc) && (*(char *)(this + param_2 * 0x24 + 0x2b2) != -1)) {
      iVar2 = this + param_2 * 0x24;
      iVar2->u8_2b0 = iVar2->u8_2b0 & 0xf7;
    }
  }
  if ((long)((ulong)this->abn_d << 0x3b) < 0) {
    this->u8_484 = this->u8_484 & 0xf7;
  }
  this->flagsA = this->flagsA & 0xf9 | 6;
  JRing::GetAreaPacketCnt(this);
  return;
}

// JP: 0x002d5c80  AreaOverCheckInit__5JRingFi  =  JRing::AreaOverCheckInit
void JRing::AreaOverCheckInit(int this,int param_2)

{
  int iVar1;
  int iVar2;
  float fStack_24;
  
  for (fStack_24 = this->cur_angle; fStack_24 < 0.0; fStack_24 = fStack_24 + 360.0) {
  }
  for (; 360.0 <= fStack_24; fStack_24 = fStack_24 - 360.0) {
  }
  if (((ulong)this->flagsB & 0xf) >> 2 == 3) {
    if (this->i16_466 < 0x168) {
      if ((fStack_24 < (float)(int)this->i16_464) ||
         ((float)((int)this->i16_464 + (int)this->i16_466) < fStack_24))
      {
        this->u8_460 = this->u8_460 & 0xf8;
        this->inside_at_start = 0;
      }
      else {
        this->u8_460 = this->u8_460 & 0xf8 | 1;
        this->inside_at_start = 1;
      }
    }
    else {
      this->u8_460 = this->u8_460 & 0xf8 | 1;
      this->inside_at_start = 0;
    }
  }
  else if (param_2 == -1) {
    for (iVar2 = 0; iVar2 < 0xc; iVar2 = iVar2 + 1) {
      if (*(char *)(this + iVar2 * 0x24 + 0x102) != -1) {
        iVar1 = this + iVar2 * 0x24;
        iVar1->u8_100 = iVar1->u8_100 & 0xf8;
      }
    }
    for (iVar2 = 0; iVar2 < 0xc; iVar2 = iVar2 + 1) {
      if (*(char *)(this + iVar2 * 0x24 + 0x2b2) != -1) {
        iVar1 = this + iVar2 * 0x24;
        iVar1->u8_2b0 = iVar1->u8_2b0 & 0xf8;
      }
    }
    this->inside_at_start = 0;
  }
  else if ((long)((ulong)this->flagsC << 0x3d) < 0) {
    if ((param_2 < 0xc) && (*(char *)(this + param_2 * 0x24 + 0x2b2) != -1)) {
      if (*(short *)(this + param_2 * 0x24 + 0x2b6) < 0x168) {
        if ((fStack_24 < (float)(int)*(short *)(this + param_2 * 0x24 + 0x2b4)) ||
           ((float)((int)*(short *)(this + param_2 * 0x24 + 0x2b4) +
                   (int)*(short *)(this + param_2 * 0x24 + 0x2b6)) < fStack_24)) {
          iVar2 = this + param_2 * 0x24;
          iVar2->u8_2b0 = iVar2->u8_2b0 & 0xf8;
          this->inside_at_start = 0;
        }
        else {
          iVar2 = this + param_2 * 0x24;
          iVar2->u8_2b0 = iVar2->u8_2b0 & 0xf8 | 1;
          this->inside_at_start = 1;
        }
      }
      else {
        iVar2 = this + param_2 * 0x24;
        iVar2->u8_2b0 = iVar2->u8_2b0 & 0xf8 | 1;
        this->inside_at_start = 0;
      }
    }
  }
  else if ((param_2 < 0xc) && (*(char *)(this + param_2 * 0x24 + 0x102) != -1)) {
    if (*(short *)(this + param_2 * 0x24 + 0x106) < 0x168) {
      if ((fStack_24 < (float)(int)*(short *)(this + param_2 * 0x24 + 0x104)) ||
         ((float)((int)*(short *)(this + param_2 * 0x24 + 0x104) +
                 (int)*(short *)(this + param_2 * 0x24 + 0x106)) < fStack_24)) {
        iVar2 = this + param_2 * 0x24;
        iVar2->u8_100 = iVar2->u8_100 & 0xf8;
        this->inside_at_start = 0;
      }
      else {
        iVar2 = this + param_2 * 0x24;
        iVar2->u8_100 = iVar2->u8_100 & 0xf8 | 1;
        this->inside_at_start = 1;
      }
    }
    else {
      iVar2 = this + param_2 * 0x24;
      iVar2->u8_100 = iVar2->u8_100 & 0xf8 | 1;
      this->inside_at_start = 0;
    }
  }
  return;
}

// JP: 0x002d6340  AreaOverCheck__5JRingFv  =  JRing::AreaOverCheck
undefined4 JRing::AreaOverCheck(int this)

{
  byte bVar1;
  byte bVar2;
  int iVar3;
  float fStack_14;
  
  for (fStack_14 = this->cur_angle; fStack_14 < 0.0; fStack_14 = fStack_14 + 360.0) {
  }
  for (; 360.0 <= fStack_14; fStack_14 = fStack_14 - 360.0) {
  }
  if (((ulong)this->flagsB & 0xf) >> 2 == 3) {
    if (this->i16_466 < 0x168) {
      bVar1 = this->u8_460 & 7;
      if (bVar1 == 2) {
        return 0;
      }
      if (bVar1 == 1) {
        if ((fStack_14 < (float)(int)this->i16_464) ||
           ((float)((int)this->i16_464 + (int)this->i16_466) < fStack_14
           )) {
          if (this->inside_at_start == 0) {
            this->u8_460 = this->u8_460 & 0xf8 | 2;
            return 0;
          }
          this->u8_460 = this->u8_460 & 0xf8;
          this->inside_at_start = 0;
        }
      }
      else if ((((this->u8_460 & 7) == 0) &&
               ((float)(int)this->i16_464 <= fStack_14)) &&
              (fStack_14 <=
               (float)((int)this->i16_464 + (int)this->i16_466))) {
        this->u8_460 = this->u8_460 & 0xf8 | 1;
      }
    }
    else {
      this->u8_460 = this->u8_460 & 0xf8 | 1;
      this->inside_at_start = 0;
    }
  }
  else if ((long)((ulong)this->flagsC << 0x3d) < 0) {
    if (*(short *)(this + this->cur_area * 0x24 + 0x2b6) < 0x168) {
      bVar1 = *(byte *)(this + this->cur_area * 0x24 + 0x2b0);
      bVar2 = bVar1 & 7;
      if (bVar2 == 2) {
        return 0;
      }
      if (bVar2 == 1) {
        if ((fStack_14 < (float)(int)*(short *)(this + this->cur_area * 0x24 + 0x2b4))
           || ((float)((int)*(short *)(this + this->cur_area * 0x24 + 0x2b4) +
                      (int)*(short *)(this + this->cur_area * 0x24 + 0x2b6)) <
               fStack_14)) {
          if (this->inside_at_start == 0) {
            this = this + this->cur_area * 0x24;
            this->u8_2b0 = this->u8_2b0 & 0xf8 | 2;
            return 0;
          }
          iVar3 = this + this->cur_area * 0x24;
          iVar3->u8_2b0 = iVar3->u8_2b0 & 0xf8;
          this->inside_at_start = 0;
        }
      }
      else if ((((bVar1 & 7) == 0) &&
               ((float)(int)*(short *)(this + this->cur_area * 0x24 + 0x2b4) <=
                fStack_14)) &&
              (fStack_14 <=
               (float)((int)*(short *)(this + this->cur_area * 0x24 + 0x2b4) +
                      (int)*(short *)(this + this->cur_area * 0x24 + 0x2b6)))) {
        this = this + this->cur_area * 0x24;
        this->u8_2b0 = this->u8_2b0 & 0xf8 | 1;
      }
    }
    else {
      iVar3 = this + this->cur_area * 0x24;
      iVar3->u8_2b0 = iVar3->u8_2b0 & 0xf8 | 1;
      this->inside_at_start = 0;
    }
  }
  else if (*(short *)(this + this->cur_area * 0x24 + 0x106) < 0x168) {
    bVar1 = *(byte *)(this + this->cur_area * 0x24 + 0x100);
    bVar2 = bVar1 & 7;
    if (bVar2 == 2) {
      return 0;
    }
    if (bVar2 == 1) {
      if ((fStack_14 < (float)(int)*(short *)(this + this->cur_area * 0x24 + 0x104)) ||
         ((float)((int)*(short *)(this + this->cur_area * 0x24 + 0x104) +
                 (int)*(short *)(this + this->cur_area * 0x24 + 0x106)) < fStack_14)) {
        if (this->inside_at_start == 0) {
          this = this + this->cur_area * 0x24;
          this->u8_100 = this->u8_100 & 0xf8 | 2;
          return 0;
        }
        iVar3 = this + this->cur_area * 0x24;
        iVar3->u8_100 = iVar3->u8_100 & 0xf8;
        this->inside_at_start = 0;
      }
    }
    else if ((((bVar1 & 7) == 0) &&
             ((float)(int)*(short *)(this + this->cur_area * 0x24 + 0x104) <= fStack_14
             )) && (fStack_14 <=
                    (float)((int)*(short *)(this + this->cur_area * 0x24 + 0x104) +
                           (int)*(short *)(this + this->cur_area * 0x24 + 0x106)))) {
      this = this + this->cur_area * 0x24;
      this->u8_100 = this->u8_100 & 0xf8 | 1;
    }
  }
  else {
    iVar3 = this + this->cur_area * 0x24;
    iVar3->u8_100 = iVar3->u8_100 & 0xf8 | 1;
    this->inside_at_start = 0;
  }
  return 1;
}

// JP: 0x002d6c60  HitCheck__5JRingFP6JRAREA  =  JRing::HitCheck
/* WARNING: Removing unreachable block (ram,0x002d7244) */

long JRing::HitCheck(int this,int param_2)

{
  char cVar1;
  int iVar2;
  long lVar3;
  float fStack_24;
  
  if (this->ring_type == 5) {
    lVar3 = 0;
    while (lVar3 < 0xc) {
      iVar2 = (int)lVar3;
      cVar1 = EasyAreaHitCheck(this->cur_angle,
                               *(undefined2 *)(param_2 + iVar2 * 0x24 + 4),
                               *(undefined2 *)(param_2 + iVar2 * 0x24 + 6));
      if (cVar1 == '\x01') {
        *(undefined2 *)(param_2 + iVar2 * 0x24 + 0x1a) =
             *(undefined2 *)(param_2 + iVar2 * 0x24 + 0x18);
        return lVar3;
      }
      lVar3 = (long)(iVar2 + 1);
    }
  }
  else {
    cVar1 = param_2->i8_2;
    if (cVar1 == '\x02') {
      if (((((ulong)this->flagsB & 0xf) >> 2 != 1) && (param_2->i16_8 != 0))
         && (cVar1 = AreaHitCheck(this->cur_angle,this->prev_angle,
                                  (param_2->i16_4 + param_2->i16_6) -
                                  param_2->i16_8,param_2->u16_8,1),
            cVar1 == '\x01')) {
        param_2->u16_1a = 0x78;
        return 0x78;
      }
      if (param_2->u8_3 < 100) {
        cVar1 = AreaHitCheck(this->cur_angle,this->prev_angle,
                             ((param_2->i16_4 + param_2->i16_6) -
                             param_2->i16_8) - param_2->i16_a,
                             param_2->u16_a,1);
        if (cVar1 == '\x01') {
          param_2->u16_1a = 100;
          if (0 < param_2->i16_8) {
            this->flagsC = this->flagsC & 0xfe;
          }
          return 100;
        }
        cVar1 = AreaHitCheck(this->cur_angle,this->prev_angle,
                             param_2->u16_4,param_2->u16_6,1);
        if (cVar1 == '\x01') {
          for (fStack_24 = this->cur_angle - (float)(int)param_2->i16_4;
              fStack_24 < 0.0; fStack_24 = fStack_24 + 360.0) {
          }
          for (; 360.0 <= fStack_24; fStack_24 = fStack_24 - 360.0) {
          }
          param_2->i16_1a =
               (short)(int)((float)param_2->u8_3 +
                           (fStack_24 * (float)(int)(100 - (uint)param_2->u8_3)) /
                           (float)(((int)param_2->i16_6 - (int)param_2->i16_8) -
                                  (int)param_2->i16_a));
          if (100 < param_2->i16_1a) {
            param_2->u16_1a = 100;
          }
          this->flagsC = this->flagsC & 0xfe;
          return (long)param_2->i16_1a;
        }
      }
      else {
        cVar1 = AreaHitCheck(this->cur_angle,this->prev_angle,
                             param_2->u16_4,param_2->u16_6,1);
        if (cVar1 == '\x01') {
          param_2->u16_1a = 100;
          if (0 < param_2->i16_8) {
            this->flagsC = this->flagsC & 0xfe;
          }
          return 100;
        }
      }
    }
    else if (cVar1 == '\x01') {
      if (((((ulong)this->flagsB & 0xf) >> 2 != 1) && (param_2->i16_8 != 0))
         && (cVar1 = AreaHitCheck(this->cur_angle,this->prev_angle,
                                  (param_2->i16_4 + param_2->i16_6) -
                                  param_2->i16_8,param_2->u16_8,1),
            cVar1 == '\x01')) {
        param_2->u16_1a = 0x78;
        return 0x78;
      }
      cVar1 = AreaHitCheck(this->cur_angle,this->prev_angle,
                           param_2->u16_4,param_2->u16_6,1);
      if (cVar1 == '\x01') {
        param_2->u16_1a = 100;
        if (0 < param_2->i16_8) {
          this->flagsC = this->flagsC & 0xfe;
        }
        return 100;
      }
    }
    else if ((cVar1 == '\0') &&
            (cVar1 = AreaHitCheck(this->cur_angle,this->prev_angle,
                                  param_2->u16_4,param_2->u16_6,1),
            cVar1 == '\x01')) {
      param_2->u16_1a = 100;
      return 100;
    }
  }
  return -1;
}

// JP: 0x002d7390  MakeGambleArea__5JRingFv  =  JRing::MakeGambleArea
void JRing::MakeGambleArea(int this)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  float fVar6;
  float fStack_1c;
  float fStack_18;
  float fStack_14;
  
  iVar5 = 0;
  iVar3 = 0;
  iVar4 = 0;
  fStack_14 = 0.0;
  fStack_18 = 0.0;
  fStack_1c = 0.0;
  if ((long)((ulong)this->flagsC << 0x3d) < 0) {
    for (iVar2 = 0; iVar2 < 0xc; iVar2 = iVar2 + 1) {
      if (*(char *)(this + iVar2 * 0x24 + 0x2b2) != -1) {
        fStack_14 = fStack_14 +
                    (float)(int)*(short *)(this + iVar2 * 0x24 + 0x2b4) +
                    (float)(int)*(short *)(this + iVar2 * 0x24 + 0x2b6) / 2.0;
        fStack_18 = fStack_18 + (float)(int)*(short *)(this + iVar2 * 0x24 + 0x2b6);
        fStack_1c = fStack_1c + (float)(int)*(short *)(this + iVar2 * 0x24 + 0x2b8);
        iVar5 = iVar5 + 1;
        iVar3 = iVar3 + iVar5;
        cVar1 = *(char *)(this + iVar2 * 0x24 + 0x2b2);
        if (cVar1 == '\x02') {
          iVar4 = 2;
        }
        else if ((cVar1 == '\x01') && (iVar4 != 2)) {
          iVar4 = 1;
        }
      }
    }
  }
  else {
    for (iVar2 = 0; iVar2 < 0xc; iVar2 = iVar2 + 1) {
      if (*(char *)(this + iVar2 * 0x24 + 0x102) != -1) {
        fStack_14 = fStack_14 +
                    (float)(int)*(short *)(this + iVar2 * 0x24 + 0x104) +
                    (float)(int)*(short *)(this + iVar2 * 0x24 + 0x106) / 2.0;
        fStack_18 = fStack_18 + (float)(int)*(short *)(this + iVar2 * 0x24 + 0x106);
        fStack_1c = fStack_1c + (float)(int)*(short *)(this + iVar2 * 0x24 + 0x108);
        iVar5 = iVar5 + 1;
        iVar3 = iVar3 + iVar5;
        cVar1 = *(char *)(this + iVar2 * 0x24 + 0x102);
        if (cVar1 == '\x02') {
          iVar4 = 2;
        }
        else if ((cVar1 == '\x01') && (iVar4 != 2)) {
          iVar4 = 1;
        }
      }
    }
  }
  if (this->laps_allowed == 0) {
    iVar3 = iVar3 << 4;
  }
  else {
    iVar3 = iVar3 * this->laps_allowed;
  }
  fStack_18 = fStack_18 / (float)iVar3;
  fStack_1c = fStack_1c / (float)iVar3;
  if (fStack_1c == 0.0) {
    if (fStack_18 < 1.0) {
      fStack_18 = 1.0;
    }
  }
  else if (fStack_1c < fStack_18) {
    if (fStack_18 < 1.0) {
      fStack_18 = 1.0;
    }
    if (fStack_1c < 1.0) {
      fStack_1c = 1.0;
    }
    if (fStack_18 - fStack_1c < 1.0) {
      fStack_18 = fStack_1c + 1.0;
    }
  }
  else {
    if (fStack_1c < 1.0) {
      fStack_1c = 1.0;
    }
    fStack_18 = fStack_1c;
  }
  fVar6 = fStack_14 / (float)iVar5 - fStack_18 / 2.0;
  if (iVar4 == 2) {
    this->u8_462 = 2;
    this->i16_464 = (short)(int)fVar6;
    this->i16_466 = (short)(int)fStack_18;
    this->i16_46a = (short)(int)((fStack_18 - fStack_1c) / 3.0);
    this->i16_468 = (short)(int)fStack_1c;
    this->u8_46c = 0xff;
    this->u8_46d = 0xff;
    this->u8_46e = 0xff;
    this->u8_46f = 0;
    this->u8_470 = 0x20;
    this->u8_471 = 200;
    this->u8_472 = 0xfa;
    this->u8_473 = 0;
    this->u8_474 = 0xff;
    this->u8_475 = 0x20;
    this->u8_476 = 0x18;
    this->u8_477 = 0;
    this->u16_478 = 0;
    this->u16_47a = 0xffff;
  }
  else if (iVar4 == 1) {
    this->u8_462 = 1;
    this->i16_464 = (short)(int)fVar6;
    this->i16_466 = (short)(int)fStack_18;
    this->u16_46a = 0;
    this->i16_468 = (short)(int)fStack_1c;
    this->u8_46c = 0xe0;
    this->u8_46d = 0x98;
    this->u8_46e = 0x40;
    this->u8_46f = 0;
    this->u8_470 = 0xff;
    this->u8_471 = 0x20;
    this->u8_472 = 0x18;
    this->u8_473 = 0;
    this->u8_474 = 0;
    this->u8_475 = 0;
    this->u8_476 = 0;
    this->u8_477 = 0;
    this->u16_478 = 0;
    this->u16_47a = 0xffff;
  }
  else if (iVar4 == 0) {
    this->u8_462 = 0;
    this->i16_464 = (short)(int)fVar6;
    this->i16_466 = (short)(int)fStack_18;
    this->u16_46a = 0;
    this->u16_468 = 0;
    this->u8_46c = 0;
    this->u8_46d = 0xa4;
    this->u8_46e = 0x50;
    this->u8_46f = 0;
    this->u8_474 = 0;
    this->u8_475 = 0;
    this->u8_476 = 0;
    this->u8_477 = 0;
    this->u8_470 = this->u8_474;
    this->u8_471 = this->u8_475;
    this->u8_472 = this->u8_476;
    this->u8_473 = this->u8_477;
    this->u16_478 = 0;
    this->u16_47a = 0xffff;
  }
  this->flagsA = this->flagsA & 0xf9 | 6;
  this->flagsA = this->flagsA & 0xe7 | 0x18;
  this->flagsA = this->flagsA & 0x9f | 0x60;
  JRing::GetAreaPacketCnt(this);
  return;
}

// JP: 0x002d7dd0  MakeFakeArea__5JRingFv  =  JRing::MakeFakeArea
void JRing::MakeFakeArea(int this)

{
  bool bVar1;
  short sVar2;
  int iVar3;
  uint uVar4;
  short sVar5;
  int iVar6;
  short sVar7;
  undefined2 *unaff_s1_lo;
  short sVar8;
  long lVar9;
  int iVar10;
  float fVar11;
  int iStack_1c;
  
  if (((ulong)this->flagsB & 0xf) >> 2 == 3) {
    unaff_s1_lo = (undefined2 *)(this + 0x460);
    iVar6 = 0x14;
  }
  else {
    if ((long)((ulong)this->flagsC << 0x3d) < 0) {
      for (iVar6 = 0; iVar6 < 0xc; iVar6 = iVar6 + 1) {
        if (*(char *)(this + iVar6 * 0x24 + 0x2b2) != -1) {
          unaff_s1_lo = (undefined2 *)(this + iVar6 * 0x24 + 0x2b0);
        }
      }
    }
    else {
      for (iVar6 = 0; iVar6 < 0xc; iVar6 = iVar6 + 1) {
        *(undefined2 *)(this + iVar6 * 0x24 + 0x2b0) =
             *(undefined2 *)(this + iVar6 * 0x24 + 0x100);
        *(undefined1 *)(this + iVar6 * 0x24 + 0x2b2) =
             *(undefined1 *)(this + iVar6 * 0x24 + 0x102);
        *(undefined2 *)(this + iVar6 * 0x24 + 0x2b4) =
             *(undefined2 *)(this + iVar6 * 0x24 + 0x104);
        *(undefined2 *)(this + iVar6 * 0x24 + 0x2b6) =
             *(undefined2 *)(this + iVar6 * 0x24 + 0x106);
        *(undefined1 *)(this + iVar6 * 0x24 + 0x2b3) =
             *(undefined1 *)(this + iVar6 * 0x24 + 0x103);
        *(undefined2 *)(this + iVar6 * 0x24 + 0x2b8) =
             *(undefined2 *)(this + iVar6 * 0x24 + 0x108);
        *(undefined1 *)(this + iVar6 * 0x24 + 700) =
             *(undefined1 *)(this + iVar6 * 0x24 + 0x10c);
        *(undefined1 *)(this + iVar6 * 0x24 + 0x2bd) =
             *(undefined1 *)(this + iVar6 * 0x24 + 0x10d);
        *(undefined1 *)(this + iVar6 * 0x24 + 0x2be) =
             *(undefined1 *)(this + iVar6 * 0x24 + 0x10e);
        *(undefined1 *)(this + iVar6 * 0x24 + 0x2bf) =
             *(undefined1 *)(this + iVar6 * 0x24 + 0x10f);
        *(undefined1 *)(this + iVar6 * 0x24 + 0x2c0) =
             *(undefined1 *)(this + iVar6 * 0x24 + 0x110);
        *(undefined1 *)(this + iVar6 * 0x24 + 0x2c1) =
             *(undefined1 *)(this + iVar6 * 0x24 + 0x111);
        *(undefined1 *)(this + iVar6 * 0x24 + 0x2c2) =
             *(undefined1 *)(this + iVar6 * 0x24 + 0x112);
        *(undefined1 *)(this + iVar6 * 0x24 + 0x2c3) =
             *(undefined1 *)(this + iVar6 * 0x24 + 0x113);
        *(undefined1 *)(this + iVar6 * 0x24 + 0x2c4) =
             *(undefined1 *)(this + iVar6 * 0x24 + 0x114);
        *(undefined1 *)(this + iVar6 * 0x24 + 0x2c5) =
             *(undefined1 *)(this + iVar6 * 0x24 + 0x115);
        *(undefined1 *)(this + iVar6 * 0x24 + 0x2c6) =
             *(undefined1 *)(this + iVar6 * 0x24 + 0x116);
        *(undefined1 *)(this + iVar6 * 0x24 + 0x2c7) =
             *(undefined1 *)(this + iVar6 * 0x24 + 0x117);
        *(undefined2 *)(this + iVar6 * 0x24 + 0x2c8) =
             *(undefined2 *)(this + iVar6 * 0x24 + 0x118);
        *(undefined2 *)(this + iVar6 * 0x24 + 0x2ca) =
             *(undefined2 *)(this + iVar6 * 0x24 + 0x11a);
        if (*(char *)(this + iVar6 * 0x24 + 0x2b2) != -1) {
          unaff_s1_lo = (undefined2 *)(this + iVar6 * 0x24 + 0x2b0);
        }
      }
      this->flagsC = this->flagsC & 0xfb | 4;
    }
    iStack_1c = 0;
    iVar6 = 0;
    for (iVar3 = 0; iVar3 < 0xc; iVar3 = iVar3 + 1) {
      if (*(char *)(this + iVar3 * 0x24 + 0x2b2) != -1) {
        sVar2 = 0x168;
        sVar8 = 0x168;
        for (iVar10 = 0; iVar10 < 0xc; iVar10 = iVar10 + 1) {
          if ((iVar3 != iVar10) && (*(char *)(this + iVar10 * 0x24 + 0x2b2) != -1)) {
            if (*(short *)(this + iVar3 * 0x24 + 0x2b4) <
                *(short *)(this + iVar10 * 0x24 + 0x2b4)) {
              sVar5 = *(short *)(this + iVar10 * 0x24 + 0x2b4) -
                      (*(short *)(this + iVar3 * 0x24 + 0x2b4) +
                      *(short *)(this + iVar3 * 0x24 + 0x2b6));
              if (sVar5 < sVar2) {
                sVar2 = sVar5;
              }
            }
            else {
              sVar5 = *(short *)(this + iVar3 * 0x24 + 0x2b4) -
                      (*(short *)(this + iVar10 * 0x24 + 0x2b4) +
                      *(short *)(this + iVar10 * 0x24 + 0x2b6));
              if (sVar5 < sVar8) {
                sVar8 = sVar5;
              }
            }
          }
        }
        if (sVar2 < 0x168) {
          iVar6 = iVar6 + sVar2;
          iStack_1c = iStack_1c + 1;
        }
        if (sVar8 < 0x168) {
          iVar6 = iVar6 + sVar8;
          iStack_1c = iStack_1c + 1;
        }
      }
    }
    if (iStack_1c == 0) {
      iVar6 = 0x14;
    }
    else {
      iVar6 = iVar6 / iStack_1c;
      if (iStack_1c == 0) {
        trap(7);
      }
    }
  }
  this->u16_484 = *unaff_s1_lo;
  this->u8_486 = unaff_s1_lo->u8_1;
  this->u16_488 = unaff_s1_lo[2];
  this->u16_48a = unaff_s1_lo[3];
  this->u8_487 = *(undefined1 *)((int)unaff_s1_lo + 3);
  this->u16_48c = unaff_s1_lo[4];
  this->u8_490 = unaff_s1_lo->u8_6;
  this->u8_491 = *(undefined1 *)((int)unaff_s1_lo + 0xd);
  this->u8_492 = unaff_s1_lo->u8_7;
  this->u8_493 = *(undefined1 *)((int)unaff_s1_lo + 0xf);
  this->u8_494 = unaff_s1_lo->u8_8;
  this->u8_495 = *(undefined1 *)((int)unaff_s1_lo + 0x11);
  this->u8_496 = unaff_s1_lo->u8_9;
  this->u8_497 = *(undefined1 *)((int)unaff_s1_lo + 0x13);
  this->u8_498 = unaff_s1_lo->u8_a;
  this->u8_499 = *(undefined1 *)((int)unaff_s1_lo + 0x15);
  this->u8_49a = unaff_s1_lo->u8_b;
  this->u8_49b = *(undefined1 *)((int)unaff_s1_lo + 0x17);
  this->u16_49c = unaff_s1_lo[0xc];
  this->u16_49e = unaff_s1_lo[0xd];
  sVar2 = (short)(iVar6 >> 1);
  if (((ulong)this->flagsB & 0xf) >> 2 == 3) {
    iVar3 = (int)(short)unaff_s1_lo[3];
    if ((short)unaff_s1_lo[3] < 0) {
      iVar3 = iVar3 + 1;
    }
    sVar8 = unaff_s1_lo[2] + (short)(iVar3 >> 1);
    uVar4 = rand();
    if ((uVar4 & 4) == 0) {
      sVar5 = sVar2;
      if (iVar6 < 0) {
        sVar5 = (short)(iVar6 + 1 >> 1);
      }
      this->i16_488 = sVar8 - (this->i16_48a + sVar5);
      if (iVar6 < 0) {
        sVar2 = (short)(iVar6 + 1 >> 1);
      }
      unaff_s1_lo[2] = sVar8 + sVar2;
    }
    else {
      sVar5 = sVar2;
      if (iVar6 < 0) {
        sVar5 = (short)(iVar6 + 1 >> 1);
      }
      unaff_s1_lo[2] = sVar8 - (unaff_s1_lo[3] + sVar5);
      if (iVar6 < 0) {
        sVar2 = (short)(iVar6 + 1 >> 1);
      }
      this->i16_488 = sVar8 + sVar2;
    }
    if ((short)unaff_s1_lo[3] < 0x168) {
      if (this->i16_464 < 5) {
        sVar2 = 5 - this->i16_464;
        this->u16_464 = 5;
        this->i16_466 = this->i16_466 - sVar2;
        this->i16_48a = this->i16_48a - sVar2;
      }
      if (0x163 < (int)this->i16_464 + (int)this->i16_466) {
        sVar2 = this->i16_464 + this->i16_466 + -0x163;
        this->i16_466 = this->i16_466 - sVar2;
        this->i16_48a = this->i16_48a - sVar2;
      }
      if (this->i16_488 < 5) {
        sVar2 = 5 - this->i16_488;
        this->u16_488 = 5;
        this->i16_48a = this->i16_48a - sVar2;
        this->i16_466 = this->i16_466 - sVar2;
      }
      if (0x163 < (int)this->i16_488 + (int)this->i16_48a) {
        sVar2 = this->i16_488 + this->i16_48a + -0x163;
        this->i16_48a = this->i16_48a - sVar2;
        this->i16_466 = this->i16_466 - sVar2;
      }
    }
  }
  else {
    sVar8 = 0;
    for (iVar3 = 0; iVar3 < 0xc; iVar3 = iVar3 + 1) {
      if (((*(char *)(this + iVar3 * 0x24 + 0x2b2) != -1) &&
          (unaff_s1_lo != (undefined2 *)(this + iVar3 * 0x24 + 0x2b0))) &&
         (sVar5 = *(short *)(this + iVar3 * 0x24 + 0x2b4) +
                  *(short *)(this + iVar3 * 0x24 + 0x2b6), sVar8 < sVar5)) {
        sVar8 = sVar5;
      }
    }
    if (sVar8 == 0) {
      iVar3 = (int)(short)unaff_s1_lo[3];
      if ((short)unaff_s1_lo[3] < 0) {
        iVar3 = iVar3 + 1;
      }
      sVar8 = unaff_s1_lo[2] + (short)(iVar3 >> 1);
      uVar4 = rand();
      if ((uVar4 & 4) == 0) {
        sVar5 = sVar2;
        if (iVar6 < 0) {
          sVar5 = (short)(iVar6 + 1 >> 1);
        }
        this->i16_488 = sVar8 - (this->i16_48a + sVar5);
        if (iVar6 < 0) {
          sVar2 = (short)(iVar6 + 1 >> 1);
        }
        unaff_s1_lo[2] = sVar8 + sVar2;
      }
      else {
        sVar5 = sVar2;
        if (iVar6 < 0) {
          sVar5 = (short)(iVar6 + 1 >> 1);
        }
        unaff_s1_lo[2] = sVar8 - (unaff_s1_lo[3] + sVar5);
        if (iVar6 < 0) {
          sVar2 = (short)(iVar6 + 1 >> 1);
        }
        this->i16_488 = sVar8 + sVar2;
      }
      if ((short)unaff_s1_lo[3] < 0x168) {
        if ((short)unaff_s1_lo[2] < 5) {
          sVar2 = unaff_s1_lo[2];
          unaff_s1_lo[2] = 5;
          unaff_s1_lo[3] = unaff_s1_lo[3] - (5 - sVar2);
          this->i16_48a = this->i16_48a - (5 - sVar2);
        }
        if (0x163 < (int)(short)unaff_s1_lo[2] + (int)(short)unaff_s1_lo[3]) {
          sVar2 = unaff_s1_lo[2] + unaff_s1_lo[3] + -0x163;
          unaff_s1_lo[3] = unaff_s1_lo[3] - sVar2;
          this->i16_48a = this->i16_48a - sVar2;
        }
        if (this->i16_488 < 5) {
          sVar2 = 5 - this->i16_488;
          this->u16_488 = 5;
          this->i16_48a = this->i16_48a - sVar2;
          unaff_s1_lo[3] = unaff_s1_lo[3] - sVar2;
        }
        if (0x163 < (int)this->i16_488 + (int)this->i16_48a) {
          sVar2 = this->i16_488 + this->i16_48a + -0x163;
          this->i16_48a = this->i16_48a - sVar2;
          unaff_s1_lo[3] = unaff_s1_lo[3] - sVar2;
        }
      }
    }
    else {
      sVar2 = 0x168;
      sVar5 = 0;
      for (iVar3 = 0; iVar3 < 0xc; iVar3 = iVar3 + 1) {
        if (*(char *)(this + iVar3 * 0x24 + 0x2b2) != -1) {
          if (*(short *)(this + iVar3 * 0x24 + 0x2b4) < sVar2) {
            sVar2 = *(short *)(this + iVar3 * 0x24 + 0x2b4);
          }
          if ((long)sVar5 <
              (long)((int)*(short *)(this + iVar3 * 0x24 + 0x2b4) +
                    (int)*(short *)(this + iVar3 * 0x24 + 0x2b6))) {
            sVar5 = *(short *)(this + iVar3 * 0x24 + 0x2b4) +
                    *(short *)(this + iVar3 * 0x24 + 0x2b6);
          }
        }
      }
      uVar4 = rand();
      sVar7 = (short)iVar6;
      if ((uVar4 & 4) == 0) {
        this->i16_488 = sVar8 + sVar7;
        unaff_s1_lo[2] = sVar7 + this->i16_488 + this->i16_48a;
        sVar8 = unaff_s1_lo[2] + unaff_s1_lo[3];
      }
      else {
        unaff_s1_lo[2] = sVar8 + sVar7;
        this->i16_488 = sVar7 + unaff_s1_lo[2] + unaff_s1_lo[3];
        sVar8 = this->i16_488 + this->i16_48a;
      }
      if ((short)unaff_s1_lo[3] < 0x168) {
        sVar7 = (short)(int)((float)(sVar2 + -5) * 0.75 + 5.0);
        sVar5 = (short)(int)(355.0 - (float)(0x163 - sVar5) * 0.75) - sVar7;
        sVar8 = sVar8 - sVar2;
        if (sVar5 < sVar8) {
          fVar11 = (float)(int)sVar5 / (float)(int)sVar8;
          lVar9 = 0;
          sVar2 = 0;
          bVar1 = true;
          while (bVar1) {
            sVar8 = 2000;
            bVar1 = false;
            for (iVar6 = 0; iVar6 < 0xc; iVar6 = iVar6 + 1) {
              if (((*(char *)(this + iVar6 * 0x24 + 0x2b2) != -1) &&
                  ((short)lVar9 < *(short *)(this + iVar6 * 0x24 + 0x2b4))) &&
                 (*(short *)(this + iVar6 * 0x24 + 0x2b4) < sVar8)) {
                sVar8 = *(short *)(this + iVar6 * 0x24 + 0x2b4);
                unaff_s1_lo = (undefined2 *)(this + iVar6 * 0x24 + 0x2b0);
                bVar1 = true;
              }
            }
            if (((short)lVar9 < this->i16_488) &&
               (this->i16_488 < sVar8)) {
              unaff_s1_lo = (undefined2 *)(this + 0x484);
              bVar1 = true;
            }
            if (bVar1) {
              if (lVar9 == 0) {
                sVar2 = unaff_s1_lo[2] + unaff_s1_lo[3];
                unaff_s1_lo[2] = sVar7;
              }
              else {
                sVar8 = unaff_s1_lo[2] - sVar2;
                sVar2 = unaff_s1_lo[2] + unaff_s1_lo[3];
                unaff_s1_lo[2] = (short)(int)((float)(int)lVar9 + (float)(int)sVar8 * fVar11);
              }
              unaff_s1_lo[3] = (short)(int)((float)(int)(short)unaff_s1_lo[3] * fVar11);
              if (((unaff_s1_lo->i8_1 == '\x01') || (unaff_s1_lo->i8_1 == '\x02'))
                 && (unaff_s1_lo[4] != 0)) {
                unaff_s1_lo[4] = (short)(int)((float)(int)(short)unaff_s1_lo[4] * fVar11);
              }
              lVar9 = (long)(short)(unaff_s1_lo[2] + unaff_s1_lo[3]);
            }
          }
        }
        else {
          iVar6 = (int)sVar5 - (int)sVar8;
          if (iVar6 < 0) {
            iVar6 = iVar6 + 1;
          }
          sVar2 = sVar2 - ((short)(iVar6 >> 1) + 5);
          for (iVar6 = 0; iVar6 < 0xc; iVar6 = iVar6 + 1) {
            if (*(char *)(this + iVar6 * 0x24 + 0x2b2) != -1) {
              iVar3 = this + iVar6 * 0x24;
              iVar3->i16_2b4 = iVar3->i16_2b4 - sVar2;
            }
          }
          this->i16_488 = this->i16_488 - sVar2;
        }
      }
    }
  }
  if (((ulong)this->flagsB & 0xf) >> 2 == 3) {
    if ((((this->i8_462 == '\x01') || (this->i8_462 == '\x02')) &&
        (this->i16_468 != 0)) &&
       (this->i16_466 < this->i16_468)) {
      this->u16_468 = this->u16_468;
    }
    if ((this->i8_462 == '\x02') &&
       (this->i16_468 < this->i16_466)) {
      this->i16_46a =
           (short)(((int)this->i16_466 - (int)this->i16_468) / 3);
    }
    else {
      this->u16_46a = 0;
    }
  }
  else {
    for (iVar6 = 0; iVar6 < 0xc; iVar6 = iVar6 + 1) {
      if (((*(char *)(this + iVar6 * 0x24 + 0x2b2) == '\x01') ||
          (*(char *)(this + iVar6 * 0x24 + 0x2b2) == '\x02')) &&
         ((*(short *)(this + iVar6 * 0x24 + 0x2b8) != 0 &&
          (*(short *)(this + iVar6 * 0x24 + 0x2b6) < *(short *)(this + iVar6 * 0x24 + 0x2b8)))
         )) {
        *(undefined2 *)(this + iVar6 * 0x24 + 0x2b8) =
             *(undefined2 *)(this + iVar6 * 0x24 + 0x2b8);
      }
      if ((*(char *)(this + iVar6 * 0x24 + 0x2b2) == '\x02') &&
         (*(short *)(this + iVar6 * 0x24 + 0x2b8) < *(short *)(this + iVar6 * 0x24 + 0x2b6)))
      {
        if (*(byte *)(this + iVar6 * 0x24 + 0x2b3) < 100) {
          *(short *)(this + iVar6 * 0x24 + 0x2ba) =
               (short)(((int)*(short *)(this + iVar6 * 0x24 + 0x2b6) -
                       (int)*(short *)(this + iVar6 * 0x24 + 0x2b8)) / 3);
        }
        else {
          *(short *)(this + iVar6 * 0x24 + 0x2ba) =
               *(short *)(this + iVar6 * 0x24 + 0x2b6) -
               *(short *)(this + iVar6 * 0x24 + 0x2b8);
        }
      }
      else {
        *(undefined2 *)(this + iVar6 * 0x24 + 0x2ba) = 0;
      }
    }
  }
  if (((this->i8_486 == '\x01') || (this->i8_486 == '\x02')) &&
     ((this->i16_48c != 0 &&
      (this->i16_48a < this->i16_48c)))) {
    this->u16_48c = this->u16_48c;
  }
  if ((this->i8_486 == '\x02') &&
     (this->i16_48c < this->i16_48a)) {
    if (this->u8_487 < 100) {
      this->i16_48e =
           (short)(((int)this->i16_48a - (int)this->i16_48c) / 3);
    }
    else {
      this->i16_48e = this->i16_48a - this->i16_48c;
    }
  }
  else {
    this->u16_48e = 0;
  }
  this->flagsA = this->flagsA & 0xf9 | 6;
  this->flagsA = this->flagsA & 0xe7 | 0x18;
  this->flagsA = this->flagsA & 0x9f | 0x60;
  JRing::GetAreaPacketCnt(this);
  return;
}

// JP: 0x002d9db0  CustomConvert__5JRingFv  =  JRing::CustomConvert
void JRing::CustomConvert(int this)

{
  bool bVar1;
  short sVar2;
  int iVar3;
  short sVar4;
  undefined2 uVar5;
  int iVar6;
  int iVar7;
  int aiStack_d0 [52];
  
  aiStack_d0[0x30] = this;
  this->flagsC = this->flagsC & 0xfb | 4;
  for (iVar6 = 0; iVar6 < 0xc; iVar6 = iVar6 + 1) {
    *(undefined2 *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2b0) =
         *(undefined2 *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x100);
    *(undefined1 *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2b2) =
         *(undefined1 *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x102);
    *(undefined2 *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2b4) =
         *(undefined2 *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x104);
    *(undefined2 *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2b6) =
         *(undefined2 *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x106);
    *(undefined1 *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2b3) =
         *(undefined1 *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x103);
    *(undefined2 *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2b8) =
         *(undefined2 *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x108);
    *(undefined1 *)(aiStack_d0[0x30] + iVar6 * 0x24 + 700) =
         *(undefined1 *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x10c);
    *(undefined1 *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2bd) =
         *(undefined1 *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x10d);
    *(undefined1 *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2be) =
         *(undefined1 *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x10e);
    *(undefined1 *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2bf) =
         *(undefined1 *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x10f);
    *(undefined1 *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2c0) =
         *(undefined1 *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x110);
    *(undefined1 *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2c1) =
         *(undefined1 *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x111);
    *(undefined1 *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2c2) =
         *(undefined1 *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x112);
    *(undefined1 *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2c3) =
         *(undefined1 *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x113);
    *(undefined1 *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2c4) =
         *(undefined1 *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x114);
    *(undefined1 *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2c5) =
         *(undefined1 *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x115);
    *(undefined1 *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2c6) =
         *(undefined1 *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x116);
    *(undefined1 *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2c7) =
         *(undefined1 *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x117);
    *(undefined2 *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2c8) =
         *(undefined2 *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x118);
    *(undefined2 *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2ca) =
         *(undefined2 *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x11a);
    aiStack_d0[iVar6 * 2 + 0x18] = 0;
    aiStack_d0[iVar6 * 2 + 0x19] = 0;
  }
  if (*(int *)(aiStack_d0[0x30] + 0x4f4) != 0) {
    for (iVar6 = 0; iVar6 < 0xc; iVar6 = iVar6 + 1) {
      if ((*(char *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2b2) != -1) &&
         (aiStack_d0[iVar6 * 2 + 0x18] =
               (uint)*(byte *)(*(int *)(aiStack_d0[0x30] + 0x4f4) + iVar6) -
               (uint)*(byte *)(*(int *)(aiStack_d0[0x30] + 0x4f4) + iVar6 + 5),
         *(short *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2b8) != 0)) {
        aiStack_d0[iVar6 * 2 + 0x19] =
             (uint)*(byte *)(*(int *)(aiStack_d0[0x30] + 0x4f4) + iVar6 + 10) -
             (uint)*(byte *)(*(int *)(aiStack_d0[0x30] + 0x4f4) + iVar6 + 0xf);
      }
    }
  }
  if ((((long)((ulong)*(byte *)(aiStack_d0[0x30] + 0x50c) << 0x3c) < 0) &&
      (-1 < (long)((ulong)*(byte *)(aiStack_d0[0x30] + 0x50c) << 0x3d))) &&
     (-1 < (long)((ulong)*(byte *)(aiStack_d0[0x30] + 0x50c) << 0x3b))) {
    for (iVar6 = 0; iVar6 < 0xc; iVar6 = iVar6 + 1) {
      if ((*(char *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2b2) != -1) &&
         (aiStack_d0[iVar6 * 2 + 0x18] =
               aiStack_d0[iVar6 * 2 + 0x18] +
               (int)(short)(*(short *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2b6) +
                           (short)aiStack_d0[iVar6 * 2 + 0x18]),
         *(short *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2b8) != 0)) {
        aiStack_d0[iVar6 * 2 + 0x19] =
             aiStack_d0[iVar6 * 2 + 0x19] +
             (int)(short)(*(short *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2b8) +
                         (short)aiStack_d0[iVar6 * 2 + 0x19]);
      }
    }
  }
  for (iVar6 = 0; iVar6 < 0xc; iVar6 = iVar6 + 1) {
    if (*(char *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2b2) != -1) {
      aiStack_d0[iVar6 * 2] = -1;
      aiStack_d0[iVar6 * 2 + 1] = -1;
      sVar2 = 0;
      sVar4 = 0x168;
      for (iVar3 = 0; iVar3 < 0xc; iVar3 = iVar3 + 1) {
        if ((*(char *)(aiStack_d0[0x30] + iVar3 * 0x24 + 0x2b2) != -1) && (iVar6 != iVar3)) {
          if (((long)((int)*(short *)(aiStack_d0[0x30] + iVar3 * 0x24 + 0x2b4) +
                     (int)*(short *)(aiStack_d0[0x30] + iVar3 * 0x24 + 0x2b6)) <
               (long)*(short *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2b4)) &&
             ((long)sVar2 <
              (long)((int)*(short *)(aiStack_d0[0x30] + iVar3 * 0x24 + 0x2b4) +
                    (int)*(short *)(aiStack_d0[0x30] + iVar3 * 0x24 + 0x2b6)))) {
            sVar2 = *(short *)(aiStack_d0[0x30] + iVar3 * 0x24 + 0x2b4) +
                    *(short *)(aiStack_d0[0x30] + iVar3 * 0x24 + 0x2b6);
            aiStack_d0[iVar6 * 2] = iVar3;
          }
          if (((long)((int)*(short *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2b4) +
                     (int)*(short *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2b6)) <
               (long)*(short *)(aiStack_d0[0x30] + iVar3 * 0x24 + 0x2b4)) &&
             (*(short *)(aiStack_d0[0x30] + iVar3 * 0x24 + 0x2b4) < sVar4)) {
            sVar4 = *(short *)(aiStack_d0[0x30] + iVar3 * 0x24 + 0x2b4);
            aiStack_d0[iVar6 * 2 + 1] = iVar3;
          }
        }
      }
    }
  }
  bVar1 = true;
  while (bVar1) {
    bVar1 = false;
    for (iVar6 = 0; iVar6 < 0xc; iVar6 = iVar6 + 1) {
      if ((*(char *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2b2) != -1) &&
         (aiStack_d0[iVar6 * 2 + 0x18] != 0)) {
        sVar4 = 5;
        if (aiStack_d0[iVar6 * 2] != -1) {
          sVar4 = *(short *)(aiStack_d0[0x30] + aiStack_d0[iVar6 * 2] * 0x24 + 0x2b4) +
                  *(short *)(aiStack_d0[0x30] + aiStack_d0[iVar6 * 2] * 0x24 + 0x2b6) + 5;
        }
        sVar2 = 0x163;
        if (aiStack_d0[iVar6 * 2 + 1] != -1) {
          sVar2 = *(short *)(aiStack_d0[0x30] + aiStack_d0[iVar6 * 2 + 1] * 0x24 + 0x2b4) + -5;
        }
        if (aiStack_d0[iVar6 * 2 + 0x18] < 1) {
          while (aiStack_d0[iVar6 * 2 + 0x18] != 0) {
            if (*(short *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2b6) < 6) {
              aiStack_d0[iVar6 * 2 + 0x18] = 0;
            }
            else {
              iVar3 = aiStack_d0[0x30] + iVar6 * 0x24;
              iVar3->i16_2b4 = iVar3->i16_2b4 + 1;
              iVar3 = aiStack_d0[0x30] + iVar6 * 0x24;
              iVar3->i16_2b6 = iVar3->i16_2b6 + -1;
              aiStack_d0[iVar6 * 2 + 0x18] = aiStack_d0[iVar6 * 2 + 0x18] + 1;
              if (aiStack_d0[iVar6 * 2 + 0x18] < 0) {
                if (*(short *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2b6) < 6) {
                  aiStack_d0[iVar6 * 2 + 0x18] = 0;
                }
                else {
                  iVar3 = aiStack_d0[0x30] + iVar6 * 0x24;
                  iVar3->i16_2b6 = iVar3->i16_2b6 + -1;
                  aiStack_d0[iVar6 * 2 + 0x18] = aiStack_d0[iVar6 * 2 + 0x18] + 1;
                }
              }
            }
          }
        }
        else {
          if (sVar4 < *(short *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2b4)) {
            iVar3 = aiStack_d0[0x30] + iVar6 * 0x24;
            iVar3->i16_2b4 = iVar3->i16_2b4 + -1;
            iVar3 = aiStack_d0[0x30] + iVar6 * 0x24;
            iVar3->i16_2b6 = iVar3->i16_2b6 + 1;
            aiStack_d0[iVar6 * 2 + 0x18] = aiStack_d0[iVar6 * 2 + 0x18] + -1;
          }
          if (0 < aiStack_d0[iVar6 * 2 + 0x18]) {
            if ((long)((int)*(short *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2b4) +
                      (int)*(short *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2b6)) < (long)sVar2) {
              iVar3 = aiStack_d0[0x30] + iVar6 * 0x24;
              iVar3->i16_2b6 = iVar3->i16_2b6 + 1;
              aiStack_d0[iVar6 * 2 + 0x18] = aiStack_d0[iVar6 * 2 + 0x18] + -1;
              if (0 < aiStack_d0[iVar6 * 2 + 0x18]) {
                bVar1 = true;
              }
            }
            else if (sVar4 < *(short *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2b4)) {
              bVar1 = true;
            }
          }
        }
      }
    }
  }
  for (iVar6 = 0; iVar6 < 0xc; iVar6 = iVar6 + 1) {
    if (*(char *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2b2) != -1) {
      if (((ulong)*(byte *)(aiStack_d0[0x30] + 0x41) & 0xf) >> 2 == 2) {
        sVar4 = *(short *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2b6);
        iVar3 = (int)sVar4;
        if (sVar4 < 0) {
          iVar3 = iVar3 + 7;
        }
        iVar7 = aiStack_d0[0x30] + iVar6 * 0x24;
        iVar7->i16_2b4 = iVar7->i16_2b4 + (short)(iVar3 >> 3);
        iVar3 = aiStack_d0[0x30] + iVar6 * 0x24;
        iVar3->i16_2b6 = iVar3->i16_2b6 * 3;
        iVar3 = aiStack_d0[0x30] + iVar6 * 0x24;
        sVar4 = iVar3->i16_2b6;
        uVar5 = (undefined2)((int)sVar4 >> 2);
        if (sVar4 < 0) {
          uVar5 = (undefined2)(sVar4 + 3 >> 2);
        }
        iVar3->u16_2b6 = uVar5;
      }
      if (*(short *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2b8) != 0) {
        iVar3 = aiStack_d0[0x30] + iVar6 * 0x24;
        iVar3->i16_2b8 = iVar3->i16_2b8 + (short)aiStack_d0[iVar6 * 2 + 0x19];
        if (((ulong)*(byte *)(aiStack_d0[0x30] + 0x41) & 0xf) >> 2 == 2) {
          iVar3 = aiStack_d0[0x30] + iVar6 * 0x24;
          iVar3->i16_2b8 = iVar3->i16_2b8 * 3;
          iVar3 = aiStack_d0[0x30] + iVar6 * 0x24;
          sVar4 = iVar3->i16_2b8;
          uVar5 = (undefined2)((int)sVar4 >> 2);
          if (sVar4 < 0) {
            uVar5 = (undefined2)(sVar4 + 3 >> 2);
          }
          iVar3->u16_2b8 = uVar5;
        }
        if (*(short *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2b6) <
            *(short *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2b8)) {
          *(undefined2 *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2b8) =
               *(undefined2 *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2b6);
        }
        if (*(short *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2b8) < 1) {
          *(undefined2 *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2b8) = 1;
        }
      }
    }
  }
  if ((((long)((ulong)*(byte *)(aiStack_d0[0x30] + 0x50c) << 0x3d) < 0) &&
      (-1 < (long)((ulong)*(byte *)(aiStack_d0[0x30] + 0x50c) << 0x3c))) &&
     (-1 < (long)((ulong)*(byte *)(aiStack_d0[0x30] + 0x50c) << 0x3b))) {
    for (iVar6 = 0; iVar6 < 0xc; iVar6 = iVar6 + 1) {
      if (*(char *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2b2) != -1) {
        sVar4 = *(short *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2b6);
        iVar3 = (int)sVar4;
        if (sVar4 < 0) {
          iVar3 = iVar3 + 3;
        }
        iVar7 = aiStack_d0[0x30] + iVar6 * 0x24;
        iVar7->i16_2b4 = iVar7->i16_2b4 + (short)(iVar3 >> 2);
        iVar3 = aiStack_d0[0x30] + iVar6 * 0x24;
        sVar4 = iVar3->i16_2b6;
        uVar5 = (undefined2)((int)sVar4 >> 1);
        if (sVar4 < 0) {
          uVar5 = (undefined2)(sVar4 + 1 >> 1);
        }
        iVar3->u16_2b6 = uVar5;
        if (*(short *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2b8) != 0) {
          iVar3 = aiStack_d0[0x30] + iVar6 * 0x24;
          sVar4 = iVar3->i16_2b8;
          uVar5 = (undefined2)((int)sVar4 >> 1);
          if (sVar4 < 0) {
            uVar5 = (undefined2)(sVar4 + 1 >> 1);
          }
          iVar3->u16_2b8 = uVar5;
          if (*(short *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2b6) <
              *(short *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2b8)) {
            *(undefined2 *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2b8) =
                 *(undefined2 *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2b6);
          }
          if (*(short *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2b8) < 1) {
            *(undefined2 *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2b8) = 1;
          }
        }
      }
    }
  }
  if ((long)((ulong)*(byte *)(aiStack_d0[0x30] + 0x50c) << 0x3b) < 0) {
    for (iVar6 = 0; iVar6 < 0xc; iVar6 = iVar6 + 1) {
      if (((*(char *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2b2) != -1) &&
          (*(undefined2 *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2b6) = 0x168,
          *(short *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2b8) != 0)) &&
         (-1 < (long)((ulong)*(byte *)(aiStack_d0[0x30] + 0x50c) << 0x3a))) {
        *(undefined2 *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2b8) = 0;
      }
    }
  }
  if ((long)((ulong)*(byte *)(aiStack_d0[0x30] + 0x50c) << 0x3a) < 0) {
    for (iVar6 = 0; iVar6 < 0xc; iVar6 = iVar6 + 1) {
      if ((*(char *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2b2) != -1) &&
         (*(short *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2b8) != 0)) {
        *(undefined2 *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2b8) =
             *(undefined2 *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2b6);
      }
    }
  }
  if (((ulong)*(byte *)(aiStack_d0[0x30] + 0x41) & 0xf) >> 2 == 1) {
    for (iVar6 = 0; iVar6 < 0xc; iVar6 = iVar6 + 1) {
      if ((*(char *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2b2) != -1) &&
         (*(short *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2b8) != 0)) {
        *(undefined2 *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2b8) = 0;
      }
    }
  }
  for (iVar6 = 0; iVar6 < 0xc; iVar6 = iVar6 + 1) {
    if ((*(char *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x102) == '\x02') &&
       (*(short *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2b8) <
        *(short *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2b6))) {
      if (*(byte *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2b3) < 100) {
        *(short *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2ba) =
             (short)(((int)*(short *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2b6) -
                     (int)*(short *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2b8)) / 3);
      }
      else {
        *(short *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2ba) =
             *(short *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2b6) -
             *(short *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2b8);
      }
    }
    else {
      *(undefined2 *)(aiStack_d0[0x30] + iVar6 * 0x24 + 0x2ba) = 0;
    }
  }
  return;
}

// JP: 0x002db500  JRCustomCheck__5JRingFP8JRCUSTOM  =  JRing::JRCustomCheck
undefined4 JRing::JRCustomCheck(int this,int param_2)

{
  bool bVar1;
  short sVar2;
  short sVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  int *piVar7;
  undefined4 uStack_2f0;
  short asStack_2ec [4];
  undefined1 auStack_2e4 [12];
  undefined2 auStack_2d8 [204];
  int aiStack_140 [76];
  int iStack_10;
  
  aiStack_140[0x48] = this;
  iStack_10 = param_2;
  piVar6 = &uStack_2f0;
  do {
    piVar7 = piVar6 + 3;
    do {
      piVar7 = piVar7 + 1;
    } while (piVar7 != piVar6 + 6);
    piVar6 = piVar6 + 9;
  } while (piVar6 != aiStack_140);
  for (iVar4 = 0; iVar4 < 0xc; iVar4 = iVar4 + 1) {
    asStack_2ec[iVar4 * 0x12 + -2] = *(short *)(aiStack_140[0x48] + iVar4 * 0x24 + 0x100);
    *(undefined1 *)(asStack_2ec + iVar4 * 0x12 + -1) =
         *(undefined1 *)(aiStack_140[0x48] + iVar4 * 0x24 + 0x102);
    asStack_2ec[iVar4 * 0x12] = *(short *)(aiStack_140[0x48] + iVar4 * 0x24 + 0x104);
    asStack_2ec[iVar4 * 0x12 + 1] = *(short *)(aiStack_140[0x48] + iVar4 * 0x24 + 0x106);
    *(undefined1 *)((int)asStack_2ec + iVar4 * 0x24 + -1) =
         *(undefined1 *)(aiStack_140[0x48] + iVar4 * 0x24 + 0x103);
    asStack_2ec[iVar4 * 0x12 + 2] = *(short *)(aiStack_140[0x48] + iVar4 * 0x24 + 0x108);
    auStack_2e4[iVar4 * 0x24] = *(undefined1 *)(aiStack_140[0x48] + iVar4 * 0x24 + 0x10c);
    auStack_2e4[iVar4 * 0x24 + 1] = *(undefined1 *)(aiStack_140[0x48] + iVar4 * 0x24 + 0x10d);
    auStack_2e4[iVar4 * 0x24 + 2] = *(undefined1 *)(aiStack_140[0x48] + iVar4 * 0x24 + 0x10e);
    auStack_2e4[iVar4 * 0x24 + 3] = *(undefined1 *)(aiStack_140[0x48] + iVar4 * 0x24 + 0x10f);
    auStack_2e4[iVar4 * 0x24 + 4] = *(undefined1 *)(aiStack_140[0x48] + iVar4 * 0x24 + 0x110);
    auStack_2e4[iVar4 * 0x24 + 5] = *(undefined1 *)(aiStack_140[0x48] + iVar4 * 0x24 + 0x111);
    auStack_2e4[iVar4 * 0x24 + 6] = *(undefined1 *)(aiStack_140[0x48] + iVar4 * 0x24 + 0x112);
    auStack_2e4[iVar4 * 0x24 + 7] = *(undefined1 *)(aiStack_140[0x48] + iVar4 * 0x24 + 0x113);
    auStack_2e4[iVar4 * 0x24 + 8] = *(undefined1 *)(aiStack_140[0x48] + iVar4 * 0x24 + 0x114);
    auStack_2e4[iVar4 * 0x24 + 9] = *(undefined1 *)(aiStack_140[0x48] + iVar4 * 0x24 + 0x115);
    auStack_2e4[iVar4 * 0x24 + 10] = *(undefined1 *)(aiStack_140[0x48] + iVar4 * 0x24 + 0x116);
    auStack_2e4[iVar4 * 0x24 + 0xb] = *(undefined1 *)(aiStack_140[0x48] + iVar4 * 0x24 + 0x117);
    auStack_2d8[iVar4 * 0x12] = *(undefined2 *)(aiStack_140[0x48] + iVar4 * 0x24 + 0x118);
    auStack_2d8[iVar4 * 0x12 + 1] = *(undefined2 *)(aiStack_140[0x48] + iVar4 * 0x24 + 0x11a);
    aiStack_140[iVar4 * 2 + 0x30] = 0;
    aiStack_140[iVar4 * 2 + 0x31] = 0;
  }
  if (param_2 != 0) {
    for (iVar4 = 0; iVar4 < 0xc; iVar4 = iVar4 + 1) {
      if ((char)asStack_2ec[iVar4 * 0x12 + -1] != -1) {
        aiStack_140[iVar4 * 2 + 0x30] =
             (uint)*(byte *)(param_2 + iVar4) - (uint)*(byte *)(param_2 + iVar4 + 5);
        if (asStack_2ec[iVar4 * 0x12 + 2] != 0) {
          aiStack_140[iVar4 * 2 + 0x31] =
               (uint)*(byte *)(param_2 + iVar4 + 10) - (uint)*(byte *)(param_2 + iVar4 + 0xf);
        }
        aiStack_140[iVar4 * 2 + 0x18] = aiStack_140[iVar4 * 2 + 0x30];
        aiStack_140[iVar4 * 2 + 0x19] = aiStack_140[iVar4 * 2 + 0x31];
      }
    }
  }
  for (iVar4 = 0; iVar4 < 0xc; iVar4 = iVar4 + 1) {
    if ((char)asStack_2ec[iVar4 * 0x12 + -1] != -1) {
      aiStack_140[iVar4 * 2] = -1;
      aiStack_140[iVar4 * 2 + 1] = -1;
      sVar3 = 0;
      sVar2 = 0x168;
      for (iVar5 = 0; iVar5 < 0xc; iVar5 = iVar5 + 1) {
        if (((char)asStack_2ec[iVar5 * 0x12 + -1] != -1) && (iVar4 != iVar5)) {
          if (((long)((int)asStack_2ec[iVar5 * 0x12] + (int)asStack_2ec[iVar5 * 0x12 + 1]) <
               (long)asStack_2ec[iVar4 * 0x12]) &&
             ((long)sVar3 <
              (long)((int)asStack_2ec[iVar5 * 0x12] + (int)asStack_2ec[iVar5 * 0x12 + 1]))) {
            sVar3 = asStack_2ec[iVar5 * 0x12] + asStack_2ec[iVar5 * 0x12 + 1];
            aiStack_140[iVar4 * 2] = iVar5;
          }
          if (((long)((int)asStack_2ec[iVar4 * 0x12] + (int)asStack_2ec[iVar4 * 0x12 + 1]) <
               (long)asStack_2ec[iVar5 * 0x12]) && (asStack_2ec[iVar5 * 0x12] < sVar2)) {
            sVar2 = asStack_2ec[iVar5 * 0x12];
            aiStack_140[iVar4 * 2 + 1] = iVar5;
          }
        }
      }
    }
  }
  bVar1 = true;
  while (bVar1) {
    bVar1 = false;
    for (iVar4 = 0; iVar4 < 0xc; iVar4 = iVar4 + 1) {
      if (((char)asStack_2ec[iVar4 * 0x12 + -1] != -1) && (aiStack_140[iVar4 * 2 + 0x30] != 0)) {
        sVar2 = 5;
        if (aiStack_140[iVar4 * 2] != -1) {
          sVar2 = asStack_2ec[aiStack_140[iVar4 * 2] * 0x12] +
                  asStack_2ec[aiStack_140[iVar4 * 2] * 0x12 + 1] + 5;
        }
        sVar3 = 0x163;
        if (aiStack_140[iVar4 * 2 + 1] != -1) {
          sVar3 = asStack_2ec[aiStack_140[iVar4 * 2 + 1] * 0x12] + -5;
        }
        if (aiStack_140[iVar4 * 2 + 0x30] < 1) {
          if (aiStack_140[iVar4 * 2 + 0x30] < 0) {
            while ((aiStack_140[iVar4 * 2 + 0x30] < 0 && (5 < asStack_2ec[iVar4 * 0x12 + 1]))) {
              asStack_2ec[iVar4 * 0x12] = asStack_2ec[iVar4 * 0x12] + 1;
              asStack_2ec[iVar4 * 0x12 + 1] = asStack_2ec[iVar4 * 0x12 + 1] + -1;
              aiStack_140[iVar4 * 2 + 0x30] = aiStack_140[iVar4 * 2 + 0x30] + 1;
              if ((aiStack_140[iVar4 * 2 + 0x30] < 0) && (5 < asStack_2ec[iVar4 * 0x12 + 1])) {
                asStack_2ec[iVar4 * 0x12 + 1] = asStack_2ec[iVar4 * 0x12 + 1] + -1;
                aiStack_140[iVar4 * 2 + 0x30] = aiStack_140[iVar4 * 2 + 0x30] + 1;
              }
            }
          }
        }
        else {
          if (sVar2 < asStack_2ec[iVar4 * 0x12]) {
            asStack_2ec[iVar4 * 0x12] = asStack_2ec[iVar4 * 0x12] + -1;
            asStack_2ec[iVar4 * 0x12 + 1] = asStack_2ec[iVar4 * 0x12 + 1] + 1;
            aiStack_140[iVar4 * 2 + 0x30] = aiStack_140[iVar4 * 2 + 0x30] + -1;
          }
          if ((0 < aiStack_140[iVar4 * 2 + 0x30]) &&
             ((long)((int)asStack_2ec[iVar4 * 0x12] + (int)asStack_2ec[iVar4 * 0x12 + 1]) <
              (long)sVar3)) {
            asStack_2ec[iVar4 * 0x12 + 1] = asStack_2ec[iVar4 * 0x12 + 1] + 1;
            aiStack_140[iVar4 * 2 + 0x30] = aiStack_140[iVar4 * 2 + 0x30] + -1;
          }
          if (((sVar2 < asStack_2ec[iVar4 * 0x12]) ||
              ((long)((int)asStack_2ec[iVar4 * 0x12] + (int)asStack_2ec[iVar4 * 0x12 + 1]) <
               (long)sVar3)) && (0 < aiStack_140[iVar4 * 2 + 0x30])) {
            bVar1 = true;
          }
        }
      }
    }
  }
  for (iVar4 = 0; iVar4 < 0xc; iVar4 = iVar4 + 1) {
    if (((char)asStack_2ec[iVar4 * 0x12 + -1] != -1) && (asStack_2ec[iVar4 * 0x12 + 2] != 0)) {
      if (aiStack_140[iVar4 * 2 + 0x31] < 1) {
        if (aiStack_140[iVar4 * 2 + 0x31] < 0) {
          while ((1 < asStack_2ec[iVar4 * 0x12 + 2] && (aiStack_140[iVar4 * 2 + 0x31] < 0))) {
            asStack_2ec[iVar4 * 0x12 + 2] = asStack_2ec[iVar4 * 0x12 + 2] + -1;
            aiStack_140[iVar4 * 2 + 0x31] = aiStack_140[iVar4 * 2 + 0x31] + 1;
          }
        }
      }
      else {
        while ((asStack_2ec[iVar4 * 0x12 + 2] < asStack_2ec[iVar4 * 0x12 + 1] &&
               (0 < aiStack_140[iVar4 * 2 + 0x31]))) {
          asStack_2ec[iVar4 * 0x12 + 2] = asStack_2ec[iVar4 * 0x12 + 2] + 1;
          aiStack_140[iVar4 * 2 + 0x31] = aiStack_140[iVar4 * 2 + 0x31] + -1;
        }
      }
    }
  }
  iVar4 = 0;
  do {
    if (0xb < iVar4) {
      return 1;
    }
    if ((char)asStack_2ec[iVar4 * 0x12 + -1] != -1) {
      if ((0 < aiStack_140[iVar4 * 2 + 0x18]) && (0 < aiStack_140[iVar4 * 2 + 0x30])) {
        return 0;
      }
      if ((aiStack_140[iVar4 * 2 + 0x18] < 0) && (aiStack_140[iVar4 * 2 + 0x30] < 0)) {
        return 0;
      }
      if (asStack_2ec[iVar4 * 0x12 + 2] != 0) {
        if ((0 < aiStack_140[iVar4 * 2 + 0x19]) && (0 < aiStack_140[iVar4 * 2 + 0x31])) {
          return 0;
        }
        if ((aiStack_140[iVar4 * 2 + 0x19] < 0) && (aiStack_140[iVar4 * 2 + 0x31] < 0)) {
          return 0;
        }
      }
    }
    iVar4 = iVar4 + 1;
  } while( true );
}

// JP: 0x002dc420  AreaReset__5JRingFv  =  JRing::AreaReset
void JRing::AreaReset(int this)

{
  JRing::CustomConvert(this);
  if (((ulong)this->flagsB & 0xf) >> 2 == 3) {
    JRing::MakeGambleArea(this);
  }
  if ((long)((ulong)this->abn_d << 0x3b) < 0) {
    JRing::MakeFakeArea(this);
  }
  JRing::AreaBlinkInit(this);
  JRing::AreaOverCheckInit(this,0xffffffffffffffff);
  JRing::AreaOn(this,0xffffffffffffffff);
  this->flagsA = this->flagsA & 0xf9 | 6;
  this->flagsA = this->flagsA & 0xe7 | 0x18;
  this->flagsA = this->flagsA & 0x9f | 0x60;
  return;
}

// JP: 0x002dc560  AreaBlinkInit__5JRingFv  =  JRing::AreaBlinkInit
void JRing::AreaBlinkInit(int this)

{
  int iVar1;
  int iVar2;
  
  for (iVar2 = 0; iVar2 < 0xc; iVar2 = iVar2 + 1) {
    iVar1 = this + iVar2 * 0x24;
    iVar1->u8_100 = iVar1->u8_100 & 0xcf;
    iVar1 = this + iVar2 * 0x24;
    iVar1->u8_101 = iVar1->u8_101 & 0xf9;
    iVar1 = this + iVar2 * 0x24;
    iVar1->u8_100 = iVar1->u8_100 & 0xbf;
    iVar1 = this + iVar2 * 0x24;
    iVar1->u16_100 = iVar1->u16_100 & 0xfe7f;
    *(undefined4 *)(this + iVar2 * 0x24 + 0x11c) = 0x3f400000;
    *(undefined4 *)(this + iVar2 * 0x24 + 0x120) = 0;
    iVar1 = this + iVar2 * 0x24;
    iVar1->u8_2b0 = iVar1->u8_2b0 & 0xcf;
    iVar1 = this + iVar2 * 0x24;
    iVar1->u8_2b1 = iVar1->u8_2b1 & 0xf9;
    iVar1 = this + iVar2 * 0x24;
    iVar1->u8_2b0 = iVar1->u8_2b0 & 0xbf;
    iVar1 = this + iVar2 * 0x24;
    iVar1->u16_2b0 = iVar1->u16_2b0 & 0xfe7f;
    *(undefined4 *)(this + iVar2 * 0x24 + 0x2cc) = 0x3f400000;
    *(undefined4 *)(this + iVar2 * 0x24 + 0x2d0) = 0;
  }
  this->u8_460 = this->u8_460 & 0xcf;
  this->u8_461 = this->u8_461 & 0xf9;
  this->u8_460 = this->u8_460 & 0xbf;
  this->u16_460 = this->u16_460 & 0xfe7f;
  this->u32_47c = 0x3f400000;
  this->u32_480 = 0;
  this->flagsA = this->flagsA & 0x9f | 0x60;
  return;
}

// JP: 0x002dc860  SetAreaBlink__5JRingFiii  =  JRing::SetAreaBlink
void JRing::SetAreaBlink(int this,int param_2,uint param_3,uint param_4)

{
  int iVar1;
  int iVar2;
  
  if (param_2 == -1) {
    for (iVar2 = 0; iVar2 < 0xc; iVar2 = iVar2 + 1) {
      iVar1 = this + iVar2 * 0x24;
      iVar1->u8_100 = iVar1->u8_100 & 0xcf | (byte)((param_3 & 3) << 4);
      iVar1 = this + iVar2 * 0x24;
      iVar1->u8_100 = iVar1->u8_100 & 0xbf;
      iVar1 = this + iVar2 * 0x24;
      iVar1->u16_100 =
           iVar1->u16_100 & 0xfe7f | (ushort)((param_4 & 3) << 7);
      *(undefined4 *)(this + iVar2 * 0x24 + 0x11c) = 0x3f400000;
      iVar1 = this + iVar2 * 0x24;
      iVar1->u8_2b0 = iVar1->u8_2b0 & 0xcf | (byte)((param_3 & 3) << 4);
      iVar1 = this + iVar2 * 0x24;
      iVar1->u8_2b0 = iVar1->u8_2b0 & 0xbf;
      iVar1 = this + iVar2 * 0x24;
      iVar1->u16_2b0 =
           iVar1->u16_2b0 & 0xfe7f | (ushort)((param_4 & 3) << 7);
      *(undefined4 *)(this + iVar2 * 0x24 + 0x2cc) = 0x3f400000;
    }
    this->u8_460 = this->u8_460 & 0xcf | (byte)((param_3 & 3) << 4);
    this->u8_460 = this->u8_460 & 0xbf;
    this->u16_460 =
         this->u16_460 & 0xfe7f | (ushort)((param_4 & 3) << 7);
    this->u32_47c = 0x3f400000;
  }
  else if (param_2 < 0xc) {
    iVar2 = this + param_2 * 0x24;
    iVar2->u8_100 = iVar2->u8_100 & 0xcf | (byte)((param_3 & 3) << 4);
    iVar2 = this + param_2 * 0x24;
    iVar2->u8_100 = iVar2->u8_100 & 0xbf;
    iVar2 = this + param_2 * 0x24;
    iVar2->u16_100 = iVar2->u16_100 & 0xfe7f | (ushort)((param_4 & 3) << 7);
    *(undefined4 *)(this + param_2 * 0x24 + 0x11c) = 0x3f400000;
    iVar2 = this + param_2 * 0x24;
    iVar2->u8_2b0 = iVar2->u8_2b0 & 0xcf | (byte)((param_3 & 3) << 4);
    iVar2 = this + param_2 * 0x24;
    iVar2->u8_2b0 = iVar2->u8_2b0 & 0xbf;
    iVar2 = this + param_2 * 0x24;
    iVar2->u16_2b0 = iVar2->u16_2b0 & 0xfe7f | (ushort)((param_4 & 3) << 7);
    *(undefined4 *)(this + param_2 * 0x24 + 0x2cc) = 0x3f400000;
  }
  else if (param_2 == 0xc) {
    this->u8_460 = this->u8_460 & 0xcf | (byte)((param_3 & 3) << 4);
    this->u8_460 = this->u8_460 & 0xbf;
    this->u16_460 =
         this->u16_460 & 0xfe7f | (ushort)((param_4 & 3) << 7);
    this->u32_47c = 0x3f400000;
  }
  this->flagsA = this->flagsA & 0x9f | 0x60;
  return;
}

// JP: 0x002dcd40  ResultInit__5JRingFv  =  JRing::ResultInit
undefined2 JRing::ResultInit(int this)

{
  char cVar1;
  short sVar2;
  undefined2 uVar3;
  int iVar4;
  
  this->res_flags = this->res_flags & 0xef;
  this->res_flags = this->res_flags & 0xdf;
  this->res_flags = this->res_flags & 0xbf;
  if (this->auto_mode != 0) {
    this->res_flags = this->res_flags & 0xef | 0x10;
  }
  this->res_total = 0;
  this->res_hit_count = 0;
  this->res_base = this->base_percent;
  this->res_percent = 0;
  this->res_strike_mult = this->max_percent;
  this->res_damage_mult = 10000;
  for (iVar4 = 0; iVar4 < 0x20; iVar4 = iVar4 + 1) {
    *(undefined1 *)(this + iVar4 + 0x528) = 0;
  }
  this->res_has_modulate = 0;
  for (iVar4 = 0; iVar4 < 0xc; iVar4 = iVar4 + 1) {
    cVar1 = *(char *)(this + iVar4 * 0x24 + 0x102);
    if (cVar1 == '\x02') {
      this->res_has_modulate = 1;
      this->res_total = this->res_total + 1;
      if (*(short *)(this + iVar4 * 0x24 + 0x108) != 0) {
        this->res_flags = this->res_flags & 0xdf | 0x20;
      }
    }
    else if (cVar1 == '\x01') {
      this->res_total = this->res_total + 1;
      if (*(short *)(this + iVar4 * 0x24 + 0x108) != 0) {
        this->res_flags = this->res_flags & 0xdf | 0x20;
      }
    }
    else if (cVar1 == '\0') {
      this->res_total = this->res_total + 1;
    }
  }
  sVar2 = this->ring_type;
  if (sVar2 == 5) {
    this->res_total = 1;
    uVar3 = 1;
  }
  else if (((sVar2 == 4) || (sVar2 == 3)) || (sVar2 == 2)) {
    this->res_total =
         this->res_total * (short)this->laps_allowed;
    uVar3 = this->res_total;
  }
  else if (sVar2 == 1) {
    if (((ulong)this->flagsB & 0xf) >> 2 == 3) {
      this->res_total =
           this->res_total * (short)this->laps_allowed;
      uVar3 = 1;
    }
    else if (this->laps_allowed == 0) {
      this->res_total = 0xffff;
      uVar3 = 0;
    }
    else {
      this->res_total =
           this->res_total * (short)this->laps_allowed;
      uVar3 = this->res_total;
    }
  }
  else {
    uVar3 = 1;
  }
  return uVar3;
}

// JP: 0x002dd100  MakeResult__5JRingFv  =  JRing::MakeResult
void JRing::MakeResult(int this)

{
  char cVar1;
  short sVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  ulong uVar7;
  int iVar8;
  ulong uVar9;
  byte bVar10;
  int iVar11;
  
  if (((ulong)this->flagsB & 0xf) >> 2 == 2) {
    this->res_strike_mult = this->res_strike_mult * 0xc;
    this->res_strike_mult = this->res_strike_mult / 10;
  }
  if ((((ulong)this->flagsB & 0xf) >> 2 == 1) || (this->auto_mode == 10)) {
    this->res_flags = this->res_flags & 0xdf;
  }
  sVar2 = this->ring_type;
  if ((((sVar2 == 5) || (sVar2 == 4)) || (sVar2 == 3)) || (sVar2 == 2)) {
    if ((this->cb_fn != 0) && ((long)((ulong)this->cb_mask << 0x38) < 0)) {
      (**(code **)(this + 0xf8))(0x80,this + 0x588,this->cb_user);
    }
  }
  else if (sVar2 == 1) {
    if (((ulong)this->flagsB & 0xf) >> 2 == 3) {
      bVar10 = this->u8_528 & 3;
      if (this->laps_allowed == 0) {
        this->u8_528 = bVar10;
        this->res_hit_count = 0xffff;
        this->res_total = 0xffff;
      }
      else {
        for (iVar8 = 0; iVar8 < 0x20; iVar8 = iVar8 + 1) {
          *(undefined1 *)(this + iVar8 + 0x528) = 0;
        }
        uVar6 = 0;
        for (iVar8 = 0; iVar8 < this->laps_allowed; iVar8 = iVar8 + 1) {
          for (iVar11 = 0; iVar11 < 0xc; iVar11 = iVar11 + 1) {
            cVar1 = *(char *)(this + iVar11 * 0x24 + 0x102);
            if (((cVar1 == '\x02') || (cVar1 == '\x01')) || (cVar1 == '\0')) {
              uVar3 = uVar6 & 3;
              if (((int)uVar6 < 0) && (uVar3 != 0)) {
                uVar3 = uVar3 - 4;
              }
              iVar5 = this + ((int)uVar6 >> 2);
              iVar5->u8_528 = iVar5->u8_528 | bVar10 << ((uVar3 & 0xf) << 1);
              uVar6 = uVar6 + 1;
            }
          }
        }
      }
      if (((ulong)this->res_flags & 7) >> 1 < 2) {
        this->res_flags = this->res_flags & 0xf9;
        this->res_hit_count = 0;
      }
      else {
        this->res_hit_count = this->res_total;
      }
    }
    else if ((((ulong)this->flagsB & 0xf) >> 2 == 2) &&
            (this->laps_allowed != 0)) {
      uVar3 = (int)this->res_total - 1;
      uVar6 = uVar3 & 3;
      if (((int)uVar3 < 0) && (uVar6 != 0)) {
        uVar6 = uVar6 - 4;
      }
      uVar6 = (int)(uint)*(byte *)(this + (this->res_total + -1 >> 2) + 0x528) >>
              ((uVar6 & 0xf) << 1);
      if (((ulong)this->res_flags & 7) >> 1 < 2) {
        this->res_flags = this->res_flags & 0xf9;
        this->res_hit_count = 0;
        for (iVar8 = 0; iVar8 < 0x20; iVar8 = iVar8 + 1) {
          *(undefined1 *)(this + iVar8 + 0x528) = 0;
        }
      }
      else if ((this->res_has_modulate == 1) && (((uVar6 & 3) == 0 || ((uVar6 & 3) == 2)))) {
        this->res_flags = this->res_flags & 0xf9;
        this->res_hit_count = 0;
        for (iVar8 = 0; iVar8 < 0x20; iVar8 = iVar8 + 1) {
          *(undefined1 *)(this + iVar8 + 0x528) = 0;
        }
      }
    }
    else if ((((ulong)this->flagsB & 0xf) >> 2 == 1) &&
            ((this->laps_allowed != 0 && (this->res_has_modulate == 0)))) {
      for (uVar7 = 0; uVar9 = uVar7, (long)uVar7 < (long)this->res_hit_count;
          uVar7 = (ulong)((int)uVar7 + 1)) {
        while( true ) {
          iVar8 = (int)uVar9 >> 2;
          if ((long)this->res_total <= (long)uVar9) break;
          uVar6 = (uint)(uVar9 & 3);
          if (((long)uVar9 < 0) && ((uVar9 & 3) != 0)) {
            uVar6 = uVar6 - 4;
          }
          if (((uint)*(byte *)(this + iVar8 + 0x528) & 3 << ((uVar6 & 0xf) << 1)) != 0) break;
          uVar9 = (long)((int)uVar9 + 1);
        }
        if ((long)uVar9 < (long)this->res_total) {
          bVar10 = *(byte *)(this + iVar8 + 0x528);
          uVar6 = (uint)(uVar9 & 3);
          if (((long)uVar9 < 0) && ((uVar9 & 3) != 0)) {
            uVar6 = uVar6 - 4;
          }
          uVar3 = (uint)(uVar9 & 3);
          if (((long)uVar9 < 0) && ((uVar9 & 3) != 0)) {
            uVar3 = uVar3 - 4;
          }
          uVar4 = (uint)(uVar9 & 3);
          if (((long)uVar9 < 0) && ((uVar9 & 3) != 0)) {
            uVar4 = uVar4 - 4;
          }
          *(byte *)(this + iVar8 + 0x528) =
               *(byte *)(this + iVar8 + 0x528) & -(char)(3 << ((uVar4 & 0xf) << 1)) - 1U;
          uVar4 = (uint)(uVar7 & 3);
          if (((long)uVar7 < 0) && ((uVar7 & 3) != 0)) {
            uVar4 = uVar4 - 4;
          }
          iVar11 = (int)uVar7 >> 2;
          iVar8 = this + iVar11;
          iVar8->u8_528 =
               iVar8->u8_528 & -(char)(3 << ((uVar4 & 0xf) << 1)) - 1U;
          uVar4 = (uint)(uVar7 & 3);
          if (((long)uVar7 < 0) && ((uVar7 & 3) != 0)) {
            uVar4 = uVar4 - 4;
          }
          iVar11 = this + iVar11;
          iVar11->u8_528 =
               iVar11->u8_528 |
               (byte)(((int)((uint)bVar10 & 3 << ((uVar6 & 0xf) << 1)) >> ((uVar3 & 0xf) << 1) &
                      0xffU) << ((uVar4 & 0xf) << 1));
        }
      }
    }
    else if (this->laps_allowed == 0) {
      this->u8_528 = this->u8_528 & 3;
      this->res_total = 0xffff;
    }
    if ((this->cb_fn != 0) && ((long)((ulong)this->cb_mask << 0x39) < 0)) {
      (**(code **)(this + 0xf8))(0x40,this + 0x510,this->cb_user);
    }
  }
  return;
}

// JP: 0x002dd940  JRingAutoInit__5JRingFP6JRAREAP6JRAREAb  =  JRing::JRingAutoInit
void JRing::JRingAutoInit(int this,int param_2,int param_3)

{
  int iVar1;
  float fVar2;
  float fStack_60;
  float fStack_5c;
  float fStack_58;
  float fStack_54;
  float fStack_50;
  float fStack_4c;
  float fStack_48;
  
  if (param_2 == 0) {
    if (this->auto_mode == 10) {
      iVar1 = rand();
      if (iVar1 % 100 < 0x65) {
        this->auto_aim = 1;
      }
      else {
        this->auto_aim = 0xffff;
      }
    }
    else {
      iVar1 = rand();
      if (((float)iVar1 / 2.1474836e+09) * 0.7 + 0.3 <= this->combo_window) {
        this->auto_aim = 1;
      }
      else {
        this->auto_aim = 0xffff;
      }
    }
  }
  else {
    if (param_2->i8_2 == '\x02') {
      if ((param_2->i16_8 < param_2->i16_6) && (param_2->i16_8 != 0)) {
        fStack_48 = (float)(((int)param_2->i16_4 + (int)param_2->i16_6) -
                           (int)param_2->i16_8);
        fStack_4c = (float)(int)param_2->i16_8;
      }
      else {
        fStack_4c = 0.0;
      }
      if (param_2->u8_3 < 100) {
        fStack_54 = ((float)(int)param_2->i16_a * 2.0) / 3.0;
        fStack_50 = (float)((int)param_2->i16_4 +
                           ((int)param_2->i16_6 - (int)param_2->i16_8)) -
                    fStack_54;
      }
      else {
        fStack_54 = (float)((int)param_2->i16_6 - (int)param_2->i16_8) / 6.0;
        fStack_50 = (float)((int)param_2->i16_4 +
                           ((int)param_2->i16_6 - (int)param_2->i16_8)) -
                    fStack_54;
      }
    }
    else if (param_2->i8_2 == '\x01') {
      if ((param_2->i16_8 < param_2->i16_6) && (param_2->i16_8 != 0)) {
        fStack_48 = (float)(((int)param_2->i16_4 + (int)param_2->i16_6) -
                           (int)param_2->i16_8);
        fStack_4c = (float)(int)param_2->i16_8;
      }
      else {
        fStack_4c = 0.0;
      }
      fStack_54 = (float)((int)param_2->i16_6 - (int)param_2->i16_8) / 6.0;
      fStack_50 = (float)((int)param_2->i16_4 +
                         ((int)param_2->i16_6 - (int)param_2->i16_8)) - fStack_54;
    }
    else {
      fStack_54 = (float)(int)param_2->i16_6 / 2.0;
      fStack_50 = (float)(int)param_2->i16_4 + fStack_54;
    }
    if (param_3 == 0) {
      fStack_58 = fStack_48;
      fStack_5c = fStack_50;
    }
    else {
      fStack_58 = fStack_48 - (float)(int)this->auto_aim;
      fStack_5c = fStack_50 - (float)(int)this->auto_aim;
    }
    fVar2 = this->period;
    if (0.0 < fStack_4c) {
      fStack_60 = (fStack_58 / ((360.0 / this->period) / 60.0)) * 0.104166664 * 100.0;
      if (100.0 <= fStack_60) {
        fStack_60 = 100.0;
      }
      fStack_60 = fStack_60 *
                  (((fStack_4c * 2.0) / ((360.0 / this->period) / 60.0)) / 18.0);
      if (100.0 <= fStack_60) {
        fStack_60 = 100.0;
      }
      iVar1 = rand();
      if (((float)iVar1 / 2.1474836e+09) * 100.0 <= fStack_60) {
        iVar1 = rand();
        this->auto_aim =
             (short)(int)(fStack_4c * ((float)iVar1 / 2.1474836e+09) * 1.9 - fStack_4c * 0.95);
        this->auto_aim =
             (short)(int)((float)(int)this->auto_aim + fStack_48);
        if ((param_2->i16_4 <= this->auto_aim) &&
           ((long)this->auto_aim <=
            (long)((int)param_2->i16_4 + (int)param_2->i16_6))) {
          return;
        }
      }
    }
    fStack_60 = (fStack_5c / ((360.0 / fVar2) / 60.0)) * 0.104166664 * 100.0 *
                (((fStack_54 * 2.0) / ((360.0 / this->period) / 60.0)) / 6.0);
    if (100.0 <= fStack_60) {
      fStack_60 = 100.0;
    }
    iVar1 = rand();
    if ((((float)iVar1 / 2.1474836e+09) * 100.0 <= fStack_60) || (this->auto_mode == 5))
    {
      iVar1 = rand();
      this->auto_aim =
           (short)(int)(fStack_54 * ((float)iVar1 / 2.1474836e+09) * 1.9 - fStack_54 * 0.95);
      this->auto_aim =
           (short)(int)((float)(int)this->auto_aim + fStack_50);
      if ((param_2->i16_4 <= this->auto_aim) &&
         ((long)this->auto_aim <=
          (long)((int)param_2->i16_4 + (int)param_2->i16_6))) {
        return;
      }
    }
    this->auto_aim = 0xffff;
  }
  return;
}

// JP: 0x002de380  JRingAuto__5JRingFv  =  JRing::JRingAuto
undefined4 JRing::JRingAuto(int this)

{
  char cVar1;
  char cVar2;
  short sVar3;
  short sVar4;
  int iVar5;
  undefined2 uVar6;
  undefined2 uVar7;
  float fStack_1c;
  float fStack_18;
  float fStack_14;
  
  if ((this->flagsD & 1) != 0) {
    return 0;
  }
  switch(this->auto_mode) {
  case 1:
  case 6:
  case 7:
  case 8:
  case 9:
  case 10:
    if (this->state == 5) {
      if ((this->auto_mode == 10) && (this->auto_aim < 0)) {
        return 0;
      }
      if (this->combo_window / 2.0 < this->anim_b) {
        return 1;
      }
    }
    else {
      if ((this->auto_mode == 7) && (this->hits != 0)) {
        return 0;
      }
      if (((ulong)this->flagsB & 0xf) >> 2 == 3) {
        sVar3 = this->i16_464;
        sVar4 = this->i16_466;
      }
      else if ((long)((ulong)this->flagsC << 0x3d) < 0) {
        sVar3 = *(short *)(this + this->cur_area * 0x24 + 0x2b4);
        sVar4 = *(short *)(this + this->cur_area * 0x24 + 0x2b6);
      }
      else {
        sVar3 = *(short *)(this + this->cur_area * 0x24 + 0x104);
        sVar4 = *(short *)(this + this->cur_area * 0x24 + 0x106);
      }
      if ((this->auto_mode == 8) && (this->hits != 0)) {
        if (((ulong)this->flagsB & 0xf) >> 2 == 3) {
          sVar3 = (this->i16_464 + this->i16_466) -
                  (this->i16_468 + this->i16_46a);
          sVar4 = this->i16_46a;
        }
        else if ((long)((ulong)this->flagsC << 0x3d) < 0) {
          sVar3 = (*(short *)(this + this->cur_area * 0x24 + 0x2b4) +
                  *(short *)(this + this->cur_area * 0x24 + 0x2b6)) -
                  (*(short *)(this + this->cur_area * 0x24 + 0x2b8) +
                  *(short *)(this + this->cur_area * 0x24 + 0x2ba));
          sVar4 = *(short *)(this + this->cur_area * 0x24 + 0x2ba);
        }
        else {
          sVar3 = (*(short *)(this + this->cur_area * 0x24 + 0x104) +
                  *(short *)(this + this->cur_area * 0x24 + 0x106)) -
                  (*(short *)(this + this->cur_area * 0x24 + 0x108) +
                  *(short *)(this + this->cur_area * 0x24 + 0x10a));
          sVar4 = *(short *)(this + this->cur_area * 0x24 + 0x10a);
        }
      }
      if (0.0 <= this->period) {
        fStack_1c = this->cur_angle +
                    (360.0 / this->period) * this->dt;
      }
      else {
        fStack_1c = this->cur_angle -
                    (360.0 / this->period) * this->dt;
      }
      cVar1 = AreaHitCheck(this->cur_angle,this->prev_angle,sVar3,
                           sVar4,0);
      cVar2 = AreaHitCheck(fStack_1c,this->cur_angle,sVar3,sVar4,0);
      if (cVar1 != '\x01') {
        return 0;
      }
      if (cVar2 != '\x01') {
        return 1;
      }
      iVar5 = (int)sVar4;
      if (sVar4 < 0) {
        iVar5 = iVar5 + 1;
      }
      fStack_14 = (float)((int)sVar3 + (iVar5 >> 1));
      fStack_18 = fStack_14 - fStack_1c;
      for (fStack_14 = fStack_14 - this->cur_angle; fStack_14 < -180.0;
          fStack_14 = fStack_14 + 360.0) {
      }
      for (; 180.0 < fStack_14; fStack_14 = fStack_14 - 360.0) {
      }
      for (; fStack_18 < -180.0; fStack_18 = fStack_18 + 360.0) {
      }
      for (; 180.0 < fStack_18; fStack_18 = fStack_18 - 360.0) {
      }
      if (fStack_14 < 0.0) {
        fStack_14 = fStack_14 * -1.0;
      }
      if (fStack_18 < 0.0) {
        fStack_18 = fStack_18 * -1.0;
      }
      if (fStack_14 < fStack_18) {
        return 1;
      }
    }
    break;
  case 2:
    if (this->state == 5) {
      if (this->combo_window / 2.0 < this->anim_b) {
        fStack_14 = this->f32_74;
        fStack_18 = this->f32_74 +
                    (6.2831855 / this->combo_spin) * this->dt;
        if (fStack_14 < 0.0) {
          fStack_14 = fStack_14 * -1.0;
        }
        if (fStack_18 < 0.0) {
          fStack_18 = fStack_18 * -1.0;
        }
        if (fStack_14 < fStack_18) {
          return 1;
        }
      }
    }
    else {
      if (((ulong)this->flagsB & 0xf) >> 2 == 3) {
        if (this->i16_468 == 0) {
          sVar4 = this->i16_464;
          sVar3 = this->i16_466;
        }
        else {
          sVar4 = (this->i16_464 + this->i16_466) -
                  this->i16_468;
          sVar3 = this->i16_468;
        }
      }
      else if ((long)((ulong)this->flagsC << 0x3d) < 0) {
        if (*(short *)(this + this->cur_area * 0x24 + 0x2b8) == 0) {
          sVar4 = *(short *)(this + this->cur_area * 0x24 + 0x2b4);
          sVar3 = *(short *)(this + this->cur_area * 0x24 + 0x2b6);
        }
        else {
          sVar4 = (*(short *)(this + this->cur_area * 0x24 + 0x2b4) +
                  *(short *)(this + this->cur_area * 0x24 + 0x2b6)) -
                  *(short *)(this + this->cur_area * 0x24 + 0x2b8);
          sVar3 = *(short *)(this + this->cur_area * 0x24 + 0x2b8);
        }
      }
      else if (*(short *)(this + this->cur_area * 0x24 + 0x108) == 0) {
        sVar4 = *(short *)(this + this->cur_area * 0x24 + 0x104);
        sVar3 = *(short *)(this + this->cur_area * 0x24 + 0x106);
      }
      else {
        sVar4 = (*(short *)(this + this->cur_area * 0x24 + 0x104) +
                *(short *)(this + this->cur_area * 0x24 + 0x106)) -
                *(short *)(this + this->cur_area * 0x24 + 0x108);
        sVar3 = *(short *)(this + this->cur_area * 0x24 + 0x108);
      }
      if (0.0 <= this->period) {
        fStack_1c = this->cur_angle +
                    (360.0 / this->period) * this->dt;
      }
      else {
        fStack_1c = this->cur_angle -
                    (360.0 / this->period) * this->dt;
      }
      cVar1 = AreaHitCheck(this->cur_angle,this->prev_angle,sVar4,
                           sVar3,0);
      cVar2 = AreaHitCheck(fStack_1c,this->cur_angle,sVar4,sVar3,0);
      if (cVar1 != '\x01') {
        return 0;
      }
      if (cVar2 != '\x01') {
        return 1;
      }
      iVar5 = (int)sVar3;
      if (sVar3 < 0) {
        iVar5 = iVar5 + 1;
      }
      fStack_14 = (float)((int)sVar4 + (iVar5 >> 1));
      fStack_18 = fStack_14 - fStack_1c;
      for (fStack_14 = fStack_14 - this->cur_angle; fStack_14 < -180.0;
          fStack_14 = fStack_14 + 360.0) {
      }
      for (; 180.0 < fStack_14; fStack_14 = fStack_14 - 360.0) {
      }
      for (; fStack_18 < -180.0; fStack_18 = fStack_18 + 360.0) {
      }
      for (; 180.0 < fStack_18; fStack_18 = fStack_18 - 360.0) {
      }
      if (fStack_14 < 0.0) {
        fStack_14 = fStack_14 * -1.0;
      }
      if (fStack_18 < 0.0) {
        fStack_18 = fStack_18 * -1.0;
      }
      if (fStack_14 < fStack_18) {
        return 1;
      }
    }
    break;
  case 3:
    if (-1 < this->auto_aim) {
      if (this->state == 5) {
        if (this->combo_window / 2.0 < this->anim_b) {
          fStack_14 = this->f32_74;
          fStack_18 = this->f32_74 +
                      (6.2831855 / this->combo_spin) * this->dt;
          if (fStack_14 < 0.0) {
            fStack_14 = fStack_14 * -1.0;
          }
          if (fStack_18 < 0.0) {
            fStack_18 = fStack_18 * -1.0;
          }
          if (fStack_14 < fStack_18) {
            return 1;
          }
        }
      }
      else {
        if (((ulong)this->flagsB & 0xf) >> 2 == 3) {
          uVar7 = this->u16_464;
          uVar6 = this->u16_466;
        }
        else if ((long)((ulong)this->flagsC << 0x3d) < 0) {
          uVar7 = *(undefined2 *)(this + this->cur_area * 0x24 + 0x2b4);
          uVar6 = *(undefined2 *)(this + this->cur_area * 0x24 + 0x2b6);
        }
        else {
          uVar7 = *(undefined2 *)(this + this->cur_area * 0x24 + 0x104);
          uVar6 = *(undefined2 *)(this + this->cur_area * 0x24 + 0x106);
        }
        if (0.0 <= this->period) {
          fStack_1c = this->cur_angle +
                      (360.0 / this->period) * this->dt;
        }
        else {
          fStack_1c = this->cur_angle -
                      (360.0 / this->period) * this->dt;
        }
        cVar1 = AreaHitCheck(this->cur_angle,this->prev_angle,uVar7
                             ,uVar6,0);
        cVar2 = AreaHitCheck(fStack_1c,this->cur_angle,uVar7,uVar6,0);
        if (cVar1 != '\x01') {
          return 0;
        }
        if (cVar2 != '\x01') {
          return 1;
        }
        fStack_18 = (float)(int)this->auto_aim - fStack_1c;
        for (fStack_14 = (float)(int)this->auto_aim - this->cur_angle;
            fStack_14 < -180.0; fStack_14 = fStack_14 + 360.0) {
        }
        for (; 180.0 < fStack_14; fStack_14 = fStack_14 - 360.0) {
        }
        for (; fStack_18 < -180.0; fStack_18 = fStack_18 + 360.0) {
        }
        for (; 180.0 < fStack_18; fStack_18 = fStack_18 - 360.0) {
        }
        if (fStack_14 < 0.0) {
          fStack_14 = fStack_14 * -1.0;
        }
        if (fStack_18 < 0.0) {
          fStack_18 = fStack_18 * -1.0;
        }
        if (fStack_14 < fStack_18) {
          return 1;
        }
      }
    }
    break;
  case 4:
  case 5:
    if (-1 < this->auto_aim) {
      if (this->state == 5) {
        if (this->combo_window / 2.0 < this->anim_b) {
          fStack_14 = this->f32_74;
          fStack_18 = this->f32_74 +
                      (6.2831855 / this->combo_spin) * this->dt;
          if (fStack_14 < 0.0) {
            fStack_14 = fStack_14 * -1.0;
          }
          if (fStack_18 < 0.0) {
            fStack_18 = fStack_18 * -1.0;
          }
          if (fStack_14 < fStack_18) {
            return 1;
          }
        }
      }
      else {
        if (((ulong)this->flagsB & 0xf) >> 2 == 3) {
          uVar7 = this->u16_464;
          uVar6 = this->u16_466;
        }
        else if ((long)((ulong)this->flagsC << 0x3d) < 0) {
          uVar7 = *(undefined2 *)(this + this->cur_area * 0x24 + 0x2b4);
          uVar6 = *(undefined2 *)(this + this->cur_area * 0x24 + 0x2b6);
        }
        else {
          uVar7 = *(undefined2 *)(this + this->cur_area * 0x24 + 0x104);
          uVar6 = *(undefined2 *)(this + this->cur_area * 0x24 + 0x106);
        }
        if (0.0 <= this->period) {
          fStack_1c = this->cur_angle +
                      (360.0 / this->period) * this->dt;
        }
        else {
          fStack_1c = this->cur_angle -
                      (360.0 / this->period) * this->dt;
        }
        cVar1 = AreaHitCheck(this->cur_angle,this->prev_angle,uVar7
                             ,uVar6,0);
        cVar2 = AreaHitCheck(fStack_1c,this->cur_angle,uVar7,uVar6,0);
        if (cVar1 != '\x01') {
          return 0;
        }
        if (cVar2 != '\x01') {
          return 1;
        }
        fStack_18 = (float)(int)this->auto_aim - fStack_1c;
        for (fStack_14 = (float)(int)this->auto_aim - this->cur_angle;
            fStack_14 < -180.0; fStack_14 = fStack_14 + 360.0) {
        }
        for (; 180.0 < fStack_14; fStack_14 = fStack_14 - 360.0) {
        }
        for (; fStack_18 < -180.0; fStack_18 = fStack_18 + 360.0) {
        }
        for (; 180.0 < fStack_18; fStack_18 = fStack_18 - 360.0) {
        }
        if (fStack_14 < 0.0) {
          fStack_14 = fStack_14 * -1.0;
        }
        if (fStack_18 < 0.0) {
          fStack_18 = fStack_18 * -1.0;
        }
        if (fStack_14 < fStack_18) {
          return 1;
        }
      }
    }
  }
  return 0;
}

// JP: 0x002dfdc0  MakeBarPacket__5JRingFUi  =  JRing::MakeBarPacket
undefined4 JRing::MakeBarPacket(int this,int param_2)

{
  undefined4 *puVar1;
  float in_zero_lo;
  float in_zero_hi;
  float in_zero_udw;
  float in_register_0000000c;
  undefined4 uVar2;
  undefined8 uVar3;
  float *pfVar4;
  undefined8 in_v1_udw;
  int iVar5;
  int iVar6;
  int iVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  undefined1 in_vf0 [16];
  undefined1 auVar13 [16];
  undefined1 auVar14 [16];
  undefined1 auVar15 [16];
  int aiStack_2f0 [56];
  undefined1 auStack_210 [16];
  undefined1 auStack_200 [16];
  undefined1 auStack_1f0 [16];
  undefined1 auStack_1e0 [16];
  float afStack_1d0 [101];
  float fStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  float fStack_30;
  float fStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  float fStack_20;
  float fStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  float afStack_10 [4];
  
  pfVar4 = afStack_1d0 + 0x38;
  do {
    *pfVar4 = in_zero_lo;
    pfVar4[1] = in_zero_hi;
    pfVar4[2] = in_zero_udw;
    pfVar4[3] = in_register_0000000c;
    pfVar4 = pfVar4 + 4;
  } while (pfVar4 != afStack_10);
  pfVar4 = afStack_1d0;
  do {
    *pfVar4 = in_zero_lo;
    pfVar4[1] = in_zero_hi;
    pfVar4[2] = in_zero_udw;
    pfVar4[3] = in_register_0000000c;
    pfVar4 = pfVar4 + 4;
  } while (pfVar4 != afStack_1d0 + 0x38);
  auVar13 = _vmr32(in_vf0);
  auVar14 = _vmr32(auVar13);
  auVar15 = _vmr32(auVar14);
  auStack_1e0 = _sqc2(in_vf0);
  auStack_1f0 = _sqc2(auVar13);
  auStack_200 = _sqc2(auVar14);
  auStack_210 = _sqc2(auVar15);
  if (-1 < (long)((ulong)this->flagsC << 0x3b)) {
    this->i32_4d8 = this->i32_4d8 + 1;
    if (8 < this->i32_4d8) {
      this->u32_4d8 = 0;
    }
    *(undefined4 *)(this + this->i32_4d8 * 4 + 0x4b4) =
         this->cur_angle;
  }
  afStack_1d0[0x38] = 0.0;
  afStack_1d0[0x39] = 0.0;
  afStack_1d0[0x3a] = 0.0;
  afStack_1d0[0x3b] = 1.0;
  iVar6 = this->i32_4d8;
  for (iVar7 = 1; iVar7 < 10; iVar7 = iVar7 + 1) {
    iVar6 = iVar6 + 1;
    if (8 < iVar6) {
      iVar6 = 0;
    }
    fVar8 = (float)GetRad(90.0 - *(float *)(this + iVar6 * 4 + 0x4b4));
    fVar8 = sinf(fVar8);
    fVar9 = this->scale_y;
    fVar10 = (float)GetRad(90.0 - *(float *)(this + iVar6 * 4 + 0x4b4));
    fVar10 = cosf(fVar10);
    afStack_1d0[iVar7 * 4 + 0x38] = this->scale_y * fVar10 * 103.0;
    afStack_1d0[iVar7 * 4 + 0x39] = fVar9 * -fVar8 * 103.0;
    afStack_1d0[iVar7 * 4 + 0x3a] = 0.0;
    afStack_1d0[iVar7 * 4 + 0x3b] = 1.0;
  }
  fVar8 = (float)GetRad((90.0 - *(float *)(this + this->i32_4d8 * 4 + 0x4b4)) - 90.0)
  ;
  fVar8 = sinf(fVar8);
  fVar9 = (float)GetRad((90.0 - *(float *)(this + this->i32_4d8 * 4 + 0x4b4)) - 90.0)
  ;
  afStack_1d0[0x60] = cosf(fVar9);
  afStack_1d0[0x60] = afStack_1d0[0x60] * 1.5;
  afStack_1d0[0x62] = 0.0;
  afStack_1d0[99] = 1.0;
  afStack_1d0[0x61] = -fVar8 * 1.5;
  fVar8 = (float)GetRad((90.0 - *(float *)(this + this->i32_4d8 * 4 + 0x4b4)) + 90.0)
  ;
  fVar8 = sinf(fVar8);
  fVar9 = (float)GetRad((90.0 - *(float *)(this + this->i32_4d8 * 4 + 0x4b4)) + 90.0)
  ;
  afStack_1d0[100] = cosf(fVar9);
  afStack_1d0[100] = afStack_1d0[100] * 1.5;
  uStack_38 = 0;
  uStack_34 = 0x3f800000;
  fStack_3c = -fVar8 * 1.5;
  fVar8 = (float)GetRad(90.0 - *(float *)(this + this->i32_4d8 * 4 + 0x4b4));
  fVar8 = sinf(fVar8);
  fVar9 = this->scale_y;
  fVar10 = (float)GetRad(90.0 - *(float *)(this + this->i32_4d8 * 4 + 0x4b4));
  fVar10 = sinf(fVar10 - 90.0);
  fVar11 = (float)GetRad(90.0 - *(float *)(this + this->i32_4d8 * 4 + 0x4b4));
  fVar11 = cosf(fVar11);
  fVar12 = this->scale_y * fVar11 * 103.0;
  fVar11 = (float)GetRad((90.0 - *(float *)(this + this->i32_4d8 * 4 + 0x4b4)) - 90.0
                        );
  fVar11 = cosf(fVar11);
  fStack_30 = fVar12 + fVar11 * 1.5;
  uStack_28 = 0;
  uStack_24 = 0x3f800000;
  fStack_2c = fVar9 * -fVar8 * 103.0 + -fVar10 * 1.5;
  fVar8 = (float)GetRad(90.0 - *(float *)(this + this->i32_4d8 * 4 + 0x4b4));
  fVar8 = sinf(fVar8);
  fVar9 = this->scale_y;
  fVar10 = (float)GetRad(90.0 - *(float *)(this + this->i32_4d8 * 4 + 0x4b4));
  fVar10 = sinf(fVar10 + 90.0);
  fVar11 = (float)GetRad(90.0 - *(float *)(this + this->i32_4d8 * 4 + 0x4b4));
  fVar11 = cosf(fVar11);
  fVar12 = this->scale_y * fVar11 * 103.0;
  fVar11 = (float)GetRad((90.0 - *(float *)(this + this->i32_4d8 * 4 + 0x4b4)) + 90.0
                        );
  fVar11 = cosf(fVar11);
  fStack_20 = fVar12 + fVar11 * 1.5;
  uStack_18 = 0;
  uStack_14 = 0x3f800000;
  auVar13 = _vmr32(in_vf0);
  auVar14 = _vmr32(auVar13);
  auVar15 = _vmr32(auVar14);
  auStack_1e0 = _sqc2(in_vf0);
  auStack_1f0 = _sqc2(auVar13);
  auStack_200 = _sqc2(auVar14);
  auStack_210 = _sqc2(auVar15);
  fStack_1c = fVar9 * -fVar8 * 103.0 + -fVar10 * 1.5;
  sceVu0RotMatrixZ(this->u32_78,auStack_210,auStack_210);
  sceVu0RotMatrixX(this->u32_70,auStack_210,auStack_210);
  sceVu0RotMatrixY(this->u32_74,auStack_210,auStack_210);
  RotTransVector(afStack_1d0,afStack_1d0 + 0x38,auStack_210,0xe);
  sceVu0RotTransPersN(aiStack_2f0,this + 0x590,afStack_1d0,0xe,0);
  for (iVar6 = 0; iVar6 < 0xe; iVar6 = iVar6 + 1) {
    aiStack_2f0[iVar6 * 4] =
         (int)((float)aiStack_2f0[iVar6 * 4] + (this->cx - 256.0) * 16.0);
    aiStack_2f0[iVar6 * 4 + 1] =
         (int)((float)aiStack_2f0[iVar6 * 4 + 1] + (this->cy - 224.0) * 16.0);
    aiStack_2f0[iVar6 * 4 + 2] = (int)((float)aiStack_2f0[iVar6 * 4 + 2] / 16.0);
  }
  if (*(int *)(this + param_2 * 4 + 0x500) == 0) {
    uVar3 = __nwa(0x170);
    uVar2 = __construct_new_array(uVar3,0x224b30,0,0x10,0x16);
    *(undefined4 *)(this + param_2 * 4 + 0x500) = uVar2;
    puVar1 = *(undefined4 **)(this + param_2 * 4 + 0x500);
    *puVar1 = 0x60000015;
    puVar1[1] = 0;
    puVar1[2] = 0;
    puVar1[3] = 0x50000015;
    puVar1->u64_4 = 0x1000000000000001;
    puVar1->u64_6 = 0xe;
    puVar1->u64_8 = 0x44;
    puVar1->u64_a = 0x42;
    puVar1->u64_c = 0x6400000000000001;
    puVar1->u64_e = 0xc1c1f0;
    puVar1->u64_10 = 0x4d;
    puVar1->u64_12 = 0;
    puVar1->u64_1c = 0x2400000000000008;
    puVar1->u64_1e = 0x41;
    auVar14._8_8_ = in_v1_udw;
    auVar14._0_8_ = 0xa400000000008001;
    auVar13._4_4_ = in_zero_hi;
    auVar13._0_4_ = in_zero_lo;
    auVar13._8_4_ = in_zero_udw;
    auVar13._12_4_ = in_register_0000000c;
    auVar13 = _pcpyld(auVar13,auVar14);
    puVar1->i64_40 = auVar13._0_8_;
    puVar1->u64_42 = 0x4141c1c1f0;
    puVar1->u64_44 = 0x4c;
    puVar1->u64_46 = 0;
  }
  iVar6 = *(int *)(this + param_2 * 4 + 0x500);
  iVar6->u64_50 = (ulong)(uint)(16.0 / (float)aiStack_2f0[3]) << 0x20 | 0x7fff3f;
  iVar6->i64_58 =
       (long)aiStack_2f0[2] << 0x20 | (long)aiStack_2f0[0] | (long)aiStack_2f0[1] << 0x10;
  iVar6->u64_60 = (ulong)(uint)(16.0 / (float)aiStack_2f0[7]) << 0x20 | 0x7fff3f;
  iVar6->i64_68 =
       (long)aiStack_2f0[6] << 0x20 | (long)aiStack_2f0[4] | (long)aiStack_2f0[5] << 0x10;
  for (iVar7 = 2; iVar7 < 10; iVar7 = iVar7 + 1) {
    iVar5 = (iVar7 + -1) * 0x40;
    if (iVar5 < 0) {
      iVar5 = iVar5 + 7;
    }
    fVar8 = this->scale_x * (float)(iVar5 >> 3);
    if (2.1474836e+09 <= fVar8) {
      fVar8 = fVar8 - 2.1474836e+09;
    }
    *(ulong *)(iVar6 + (iVar7 + 6) * 0x10) =
         (ulong)(uint)(16.0 / (float)aiStack_2f0[iVar7 * 4 + 3]) << 0x20 |
         ((long)(int)fVar8 & 0xffU) << 0x18 | 0x7fff3f;
    *(long *)(iVar6 + (iVar7 + 6) * 0x10 + 8) =
         (long)aiStack_2f0[iVar7 * 4 + 2] << 0x20 |
         (long)aiStack_2f0[iVar7 * 4] | (long)aiStack_2f0[iVar7 * 4 + 1] << 0x10;
  }
  fVar8 = this->scale_x * 128.0;
  if (2.1474836e+09 <= fVar8) {
    fVar8 = fVar8 - 2.1474836e+09;
  }
  iVar6->u64_120 =
       ((long)(int)fVar8 & 0xffU) << 0x18 | 0xf3fff |
       (ulong)(uint)(16.0 / (float)aiStack_2f0[0x2b]) << 0x20;
  iVar6->i64_128 =
       (long)aiStack_2f0[0x2a] << 0x20 | (long)aiStack_2f0[0x28] | (long)aiStack_2f0[0x29] << 0x10;
  fVar8 = this->scale_x * 128.0;
  if (2.1474836e+09 <= fVar8) {
    fVar8 = fVar8 - 2.1474836e+09;
  }
  iVar6->u64_130 =
       ((long)(int)fVar8 & 0xffU) << 0x18 | 0xf3fff |
       (ulong)(uint)(16.0 / (float)aiStack_2f0[0x2f]) << 0x20;
  iVar6->i64_138 =
       (long)aiStack_2f0[0x2e] << 0x20 | (long)aiStack_2f0[0x2c] | (long)aiStack_2f0[0x2d] << 0x10;
  fVar8 = this->scale_x * 128.0;
  if (2.1474836e+09 <= fVar8) {
    fVar8 = fVar8 - 2.1474836e+09;
  }
  iVar6->u64_140 =
       ((long)(int)fVar8 & 0xffU) << 0x18 | 0xbfefff |
       (ulong)(uint)(16.0 / (float)aiStack_2f0[0x33]) << 0x20;
  iVar6->i64_148 =
       (long)aiStack_2f0[0x32] << 0x20 | (long)aiStack_2f0[0x30] | (long)aiStack_2f0[0x31] << 0x10;
  fVar8 = this->scale_x * 128.0;
  if (2.1474836e+09 <= fVar8) {
    fVar8 = fVar8 - 2.1474836e+09;
  }
  iVar6->u64_150 =
       ((long)(int)fVar8 & 0xffU) << 0x18 | 0xbfefff |
       (ulong)(uint)(16.0 / (float)aiStack_2f0[0x37]) << 0x20;
  iVar6->i64_158 =
       (long)aiStack_2f0[0x36] << 0x20 | (long)aiStack_2f0[0x34] | (long)aiStack_2f0[0x35] << 0x10;
  return *(undefined4 *)(this + param_2 * 4 + 0x500);
}

// JP: 0x002e0d20  SetCombo__5JRingFf  =  JRing::SetCombo
void JRing::SetCombo(float this,int param_2)

{
  if (this == -1.0) {
    param_2->u8_42 = param_2->u8_42 & 0xfd;
  }
  else {
    param_2->u8_42 = param_2->u8_42 & 0xfd | 2;
    param_2->f32_e0 = this;
  }
  return;
}

// JP: 0x002e0db0  SetEventRingAbnormal__5JRingFi  =  JRing::SetEventRingAbnormal
void JRing::SetEventRingAbnormal(int this,undefined4 param_2)

{
  this->abn_c = 0;
  this->wobble_amp = 0;
  switch(param_2) {
  case 0:
    this->abn_d = this->abn_d & 0xfe | 1;
    break;
  case 1:
    this->abn_d = this->abn_d & 0xfd | 2;
    break;
  case 2:
    this->abn_d = this->abn_d & 0xdf | 0x20;
    this->wobble_amp = 0x3fb33333;
    break;
  case 3:
    this->abn_c = this->abn_c & 0xbf | 0x40;
    break;
  case 4:
    this->abn_d = this->abn_d & 0xf7 | 8;
    break;
  case 5:
    this->abn_d = this->abn_d & 0xbf | 0x40;
    this->wobble_amp = 0x3f99999a;
  }
  return;
}

// JP: 0x002e0f40  getPacket__5JRingFv  =  JRing::getPacket
undefined4 JRing::getPacket(int this)

{
  JRing::MakePacket(this);
  return *(undefined4 *)(this + (this->flagsA & 1) * 4 + 0x18);
}

// JP: 0x002fb470  SystemInitialize__5JRingFv  =  JRing::SystemInitialize
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void JRing::SystemInitialize(void)

{
  int iVar1;
  long lVar2;
  
  JRing::JRTop = 0;
  JRing::JREnd = 0;
  JRing::Pad = 0;
  JRing::JRData = 0;
  JRing::_System = 0;
  JRing::JRTexInfo = 0;
  for (iVar1 = 0; iVar1 < 8; iVar1 = iVar1 + 1) {
    *(undefined4 *)(&DAT_00421bb4 + iVar1 * 4) = 0;
    *(undefined4 *)(&DAT_00421bd4 + iVar1 * 4) = 0;
    (&JRing::JRTex)[iVar1] = 0;
  }
  JRing::DataLoad(0);
  iVar1 = HNMSnd::sys;
  if (HNMSnd::sys == 0) {
    lVar2 = __nw(0x440);
    iVar1 = 0;
    if (lVar2 != 0) {
      iVar1 = HNMSnd::HNMSnd(lVar2);
    }
  }
  HNMSnd::sys = iVar1;
  return;
}

// JP: 0x002fb560  Entry__5JRingFP5JRing  =  JRing::Entry
void JRing::Entry(int this)

{
  if (JRing::JREnd == 0) {
    JRing::JRTop = this;
    JRing::JREnd = this;
    this->u32_38 = 0;
  }
  else {
    this->i32_38 = JRing::JREnd;
    *(int *)(this->i32_38 + 0x3c) = this;
    JRing::JREnd = this;
  }
  this->u32_3c = 0;
  return;
}

// JP: 0x002fb5d0  Release__5JRingFP5JRing  =  JRing::Release
void JRing::Release(int this)

{
  if (this->i32_38 == 0) {
    JRing::JRTop = this->u32_3c;
  }
  else {
    *(undefined4 *)(this->i32_38 + 0x3c) = this->u32_3c;
  }
  if (this->i32_3c == 0) {
    JRing::JREnd = this->u32_38;
  }
  else {
    *(undefined4 *)(this->i32_3c + 0x38) = this->u32_38;
  }
  this->u32_38 = 0;
  this->u32_3c = 0;
  return;
}

// JP: 0x002fb680  DataLoad__5JRingFPc  =  JRing::DataLoad
undefined4 JRing::DataLoad(int this)

{
  undefined4 uVar1;
  undefined1 auStack_90 [128];
  int iStack_10;
  
  iStack_10 = this;
  if (this == 0) {
    SysTool::SetPathname(auStack_90,0x3fece0);
    DvdromOrder::ReadOrder
              (DvdromOrder::Dvdromour,auStack_90,0x2fb900,0,0,0);
    JRing::System = JRing::System & 0xfc | 1;
    JRing::JRData = 0;
    uVar1 = 1;
  }
  else if ((JRing::System & 3) == 0) {
    SysTool::SetPathname(auStack_90,this);
    DvdromOrder::ReadOrder
              (DvdromOrder::Dvdromour,auStack_90,0x2fb900,0,0,0);
    JRing::System = JRing::System & 0xfc | 1;
    JRing::JRData = 0;
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

// JP: 0x002fb790  DataLoadEndCheck__5JRingFv  =  JRing::DataLoadEndCheck
bool JRing::DataLoadEndCheck(void)

{
  return (JRing::System & 3) != 1;
}

// JP: 0x002fb7c0  DataDelete__5JRingFv  =  JRing::DataDelete
undefined4 JRing::DataDelete(void)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  
  if ((JRing::System & 3) == 1) {
    uVar2 = 0;
  }
  else {
    if (JRing::JRData != 0) {
      BufMemory::~BufMemory(JRing::JRData,1);
    }
    JRing::JRData = 0;
    JRing::System = JRing::System & 0xf8;
    for (uVar3 = 0; uVar3 < JRing::JRTexInfo; uVar3 = uVar3 + 1) {
      if ((&JRing::JRTex)[uVar3] != 0) {
        iVar1 = (&JRing::JRTex)[uVar3];
        if (iVar1 != 0) {
          (**(code **)(iVar1->i32_84 + 8))(iVar1,1);
        }
      }
      (&JRing::JRTex)[uVar3] = 0;
    }
    JRing::JRTexInfo = 0;
    uVar2 = 1;
  }
  return uVar2;
}

// JP: 0x002fb900  ReadCallBack__5JRingFiP9BufMemoryiPcPv  =  JRing::ReadCallBack
undefined8 JRing::ReadCallBack(undefined8 this,int param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined8 uVar3;
  long lVar4;
  uint uVar5;
  int iVar6;
  
  JRing::System = JRing::System & 0xfc | 2;
  uVar1 = param_2->u32_4;
  JRing::JRData = param_2;
  JRing::JRTexInfo = GetFileCount(uVar1);
  for (uVar5 = 0; uVar5 < JRing::JRTexInfo; uVar5 = uVar5 + 1) {
    uVar3 = GetFileEntry(uVar1,uVar5);
    iVar6 = (int)uVar3;
    *(uint *)(&DAT_00421bb4 + uVar5 * 4) = (uint)iVar6->u16_4;
    *(uint *)(&DAT_00421bd4 + uVar5 * 4) = (uint)iVar6->u16_6;
    lVar4 = __nw(0x88);
    uVar2 = 0;
    if (lVar4 != 0) {
      uVar2 = JRCTex::JRCTex(lVar4,0);
    }
    (&JRing::JRTex)[uVar5] = uVar2;
    if ((iVar6->u8_8 & 7) == 1) {
      JRCTex::RasterCreate
                ((&JRing::JRTex)[uVar5],0x1b,iVar6->u16_4,iVar6->u16_6)
      ;
    }
    else {
      JRCTex::RasterCreate
                ((&JRing::JRTex)[uVar5],0x2c,iVar6->u16_4,iVar6->u16_6)
      ;
    }
    JRCTex::ClutCreate((&JRing::JRTex)[uVar5],0,0x10,0x10);
    JRCTex::Create((&JRing::JRTex)[uVar5],uVar3,0,0,0);
  }
  JRing::System = JRing::System & 0xfb | 4;
  return 0;
}

// JP: 0x002fbb50  HitMesEntry__5JRingFP6HitMes  =  JRing::HitMesEntry
void JRing::HitMesEntry(int this,int param_2)

{
  if (this->i32_55c == 0) {
    this->i32_558 = param_2;
    this->i32_55c = param_2;
    param_2->u32_38 = 0;
  }
  else {
    param_2->u32_38 = this->u32_55c;
    *(int *)(param_2->i32_38 + 0x3c) = param_2;
    this->i32_55c = param_2;
  }
  param_2->u32_3c = 0;
  return;
}

// JP: 0x002fbbe0  HitMesRelease__5JRingFP6HitMes  =  JRing::HitMesRelease
void JRing::HitMesRelease(int this,int param_2)

{
  if (param_2->i32_38 == 0) {
    this->u32_558 = param_2->u32_3c;
  }
  else {
    *(undefined4 *)(param_2->i32_38 + 0x3c) = param_2->u32_3c;
  }
  if (param_2->i32_3c == 0) {
    this->u32_55c = param_2->u32_38;
  }
  else {
    *(undefined4 *)(param_2->i32_3c + 0x38) = param_2->u32_38;
  }
  param_2->u32_38 = 0;
  param_2->u32_3c = 0;
  return;
}

// JP: 0x002fbc90  AllHitMesDelete__5JRingFv  =  JRing::AllHitMesDelete
void JRing::AllHitMesDelete(int this)

{
  int iVar1;
  int iVar2;
  
  iVar2 = this->i32_558;
  while (iVar2 != 0) {
    iVar1 = iVar2->i32_3c;
    HitMes::Destruct(iVar2);
    iVar2 = iVar1;
  }
  return;
}

// JP: 0x002fbd00  HitBarEntry__5JRingFP6HitBar  =  JRing::HitBarEntry
void JRing::HitBarEntry(int this,int param_2)

{
  if (this->i32_564 == 0) {
    this->i32_560 = param_2;
    this->i32_564 = param_2;
    param_2->u32_38 = 0;
  }
  else {
    param_2->u32_38 = this->u32_564;
    *(int *)(param_2->i32_38 + 0x3c) = param_2;
    this->i32_564 = param_2;
  }
  param_2->u32_3c = 0;
  this->i16_570 = this->i16_570 + 1;
  return;
}

// JP: 0x002fbda0  HitBarRelease__5JRingFP6HitBar  =  JRing::HitBarRelease
void JRing::HitBarRelease(int this,int param_2)

{
  if (param_2->i32_38 == 0) {
    this->u32_560 = param_2->u32_3c;
  }
  else {
    *(undefined4 *)(param_2->i32_38 + 0x3c) = param_2->u32_3c;
  }
  if (param_2->i32_3c == 0) {
    this->u32_564 = param_2->u32_38;
  }
  else {
    *(undefined4 *)(param_2->i32_3c + 0x38) = param_2->u32_38;
  }
  param_2->u32_38 = 0;
  param_2->u32_3c = 0;
  this->i16_570 = this->i16_570 + -1;
  return;
}

// JP: 0x002fbe60  AllHitBarDelete__5JRingFv  =  JRing::AllHitBarDelete
void JRing::AllHitBarDelete(int this)

{
  int iVar1;
  int iVar2;
  
  iVar2 = this->i32_560;
  while (iVar2 != 0) {
    iVar1 = iVar2->i32_3c;
    HitBar::Destruct(iVar2);
    iVar2 = iVar1;
  }
  this->u32_564 = 0;
  this->u32_560 = 0;
  return;
}

// JP: 0x002fbee0  HitAreaEffEntry__5JRingFP7HitArea  =  JRing::HitAreaEffEntry
void JRing::HitAreaEffEntry(int this,int param_2)

{
  if (this->i32_56c == 0) {
    this->i32_568 = param_2;
    this->i32_56c = param_2;
    param_2->u32_38 = 0;
  }
  else {
    param_2->u32_38 = this->u32_56c;
    *(int *)(param_2->i32_38 + 0x3c) = param_2;
    this->i32_56c = param_2;
  }
  param_2->u32_3c = 0;
  this->i16_572 = this->i16_572 + 1;
  return;
}

// JP: 0x002fbf80  HitAreaEffRelease__5JRingFP7HitArea  =  JRing::HitAreaEffRelease
void JRing::HitAreaEffRelease(int this,int param_2)

{
  if (param_2->i32_38 == 0) {
    this->u32_568 = param_2->u32_3c;
  }
  else {
    *(undefined4 *)(param_2->i32_38 + 0x3c) = param_2->u32_3c;
  }
  if (param_2->i32_3c == 0) {
    this->u32_56c = param_2->u32_38;
  }
  else {
    *(undefined4 *)(param_2->i32_3c + 0x38) = param_2->u32_38;
  }
  param_2->u32_38 = 0;
  param_2->u32_3c = 0;
  this->i16_572 = this->i16_572 + -1;
  return;
}

// JP: 0x002fc040  AllHitAreaEffDelete__5JRingFv  =  JRing::AllHitAreaEffDelete
void JRing::AllHitAreaEffDelete(int this)

{
  int iVar1;
  int iVar2;
  
  iVar2 = this->i32_568;
  while (iVar2 != 0) {
    iVar1 = iVar2->i32_3c;
    HitArea::Destruct(iVar2);
    iVar2 = iVar1;
  }
  this->u32_56c = 0;
  this->u32_568 = 0;
  return;
}
