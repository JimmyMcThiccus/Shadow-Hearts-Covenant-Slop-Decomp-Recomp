// decomp/D/JRing_Combo.c — cleaned Ghidra output (SLPM_602.19, Metrowerks MIPS), Shadow Hearts: Covenant JP demo.
// Field accesses are shown as this->T_off (T = u8/u16/u32/f32/i32/p, off = hex offset);
// JRing fields are named from the recovered struct. See notes/D/*.md for layouts.
// CAVEAT: when the base pointer is a float*/int*/short*, the number in `T_off` is an ELEMENT offset (byte offset = off*sizeof(elem)).
// `this` is the C++ this pointer (param_1); the Metrowerks ABI passes it in a0.

// JP: 0x002c9750  getPacket__10ComboTrialFv  =  ComboTrial::getPacket
undefined4 ComboTrial::getPacket(int this)

{
  ComboTrial::MakePacket(this);
  return *(undefined4 *)(this + (this->u8_3c & 3) * 4 + 0x18);
}

// JP: 0x002e1ac0  __ct__10ComboTrialFP5JRingis  =  ComboTrial::ComboTrial
undefined8
ComboTrial::ComboTrial(undefined8 this,int param_2,long param_3,undefined2 param_4)

{
  short sVar1;
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  undefined4 uVar2;
  int this;
  float fVar4;
  float fVar5;
  
  CPolObj::CPolObj(this);
  
  VIF1Prim::VIF1Prim((VIF1Prim *)(this + 0x18));
  this->u32_2c = 0;
  this->u32_30 = 0;
  *(undefined1 **)(this + 0x34) = DelayDeleteObject::__vt;
  *(undefined1 **)(this + 0x14) = ComboTrial::__vt;
  this->u32_28 = 0x4067d0;
  this->u32_34 = 0x4067e0;
  this->u32_60 = in_zero_lo;
  this->u32_64 = in_zero_hi;
  this->u32_68 = in_zero_udw;
  this->u32_6c = in_register_0000000c;
  this->u32_70 = in_zero_lo;
  this->u32_74 = in_zero_hi;
  this->u32_78 = in_zero_udw;
  this->u32_7c = in_register_0000000c;
  this->i32_38 = param_2;
  this->u16_3c = 0;
  this->u16_3e = param_4;
  this->u32_40 = 0;
  this->u32_9c = 0;
  uVar2 = SysTool::GetTimer();
  this->u32_a0 = uVar2;
  this->u32_1c = 0;
  this->u32_18 = 0;
  this->u32_98 = 0;
  this->u32_44 = param_2->u32_68;
  this->u32_48 = param_2->u32_6c;
  if (param_3 == 2) {
    this->u16_88 = 0;
    this->u16_8a = 0x48;
    this->u16_8c = 0xae;
    this->u16_8e = 0x21;
    this->u32_90 = 2;
  }
  else if (param_3 == 1) {
    this->u16_88 = 0;
    this->u16_8a = 0x24;
    this->u16_8c = 0x6e;
    this->u16_8e = 0x1f;
    this->u32_90 = 0;
  }
  else if (param_3 == 0) {
    this->u16_88 = 0;
    this->u16_8a = 0;
    this->u16_8c = 0xa1;
    this->u16_8e = 0x21;
    this->u32_90 = 3;
  }
  sVar1 = this->i16_3e;
  if (sVar1 == 3) {
    this->u32_70 = 0;
    this->u32_74 = 0;
    this->u32_78 = 0;
    this->u32_7c = 0;
    this->u32_80 = 0x41000000;
    this->u32_84 = 0;
    this->u32_a4 = 0;
    this->u32_94 = 0xf;
  }
  else if (sVar1 == 2) {
    this->u32_70 = 0;
    this->u32_74 = 0x40c90fdb;
    this->u32_78 = 0;
    this->u32_7c = 0;
    this->u32_80 = 0x3f99999a;
    this->u32_84 = 0;
    this->u32_a4 = 0;
    this->u32_94 = 0xf;
  }
  else if (sVar1 == 1) {
    this->u32_70 = 0;
    this->u32_74 = 0;
    this->u32_78 = 0;
    this->u32_7c = 0;
    this->u32_80 = 0x41000000;
    this->u32_84 = 0;
    this->u32_a4 = 0;
    this->u32_94 = 0xf;
  }
  else if (sVar1 == 0) {
    this->u32_70 = 0;
    this->u32_74 = 0;
    this->u32_78 = 0;
    this->u32_7c = 0;
    this->u32_80 = 0x3f99999a;
    this->u32_84 = 0x43000000;
    fVar5 = this->f32_44 * 2.0 +
            (float)(int)this->i16_8c * this->f32_80;
    fVar4 = (512.0 - this->f32_44) * 2.0 +
            (float)(int)this->i16_8c * this->f32_80;
    if (fVar4 <= fVar5) {
      fVar4 = fVar5;
    }
    this->f32_a4 = fVar4;
    this->u32_94 = 0x14;
  }
  CPoller::Entry(CApp::app + 0x48,this,0x80,0);
  return this;
}

// JP: 0x002e1f10  __dt__10ComboTrialFv  =  ComboTrial::~ComboTrial
int ComboTrial::~ComboTrial(int this,short param_2)

{
  if (this != 0) {
    *(undefined1 **)(this + 0x14) = ComboTrial::__vt;
    this->u32_28 = 0x4067d0;
    this->u32_34 = 0x4067e0;
    if (this->i32_18 != 0) {
      __dla(this->u32_18);
    }
    if (this->i32_1c != 0) {
      __dla(this->u32_1c);
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

// JP: 0x002e2030  Destruct__10ComboTrialFv  =  ComboTrial::Destruct
void ComboTrial::Destruct(int this)

{
  CPoller::Dispose(CApp::app + 0x48,this);
  (**(code **)(this->i32_34 + 0xc))();
  return;
}

// JP: 0x002e2080  Polling__10ComboTrialFv  =  ComboTrial::Polling
undefined4 ComboTrial::Polling(int this)

{
  short sVar1;
  undefined4 uVar2;
  int iVar3;
  float fVar4;
  float fStack_20;
  float fStack_18;
  
  if ((long)((ulong)this->u8_3c << 0x3c) < 0) {
    (**(code **)(this->i32_34 + 0xc))();
    uVar2 = 1;
  }
  else {
    iVar3 = SysTool::GetTimer();
    fVar4 = (float)(uint)(iVar3 - this->i32_a0) * 0.001;
    this->i32_a0 = iVar3;
    sVar1 = this->i16_3e;
    if (sVar1 == 3) {
      iVar3 = this->i32_40;
      if (iVar3 == 2) {
        this->f32_9c = this->f32_9c + fVar4;
        this->f32_84 = 128.0 - (this->f32_9c / 0.25) * 128.0;
        if (this->f32_84 <= 0.0) {
          this->u32_84 = 0;
          this->u8_3c = this->u8_3c & 0xf7 | 8;
        }
      }
      else if (iVar3 == 1) {
        this->f32_9c = this->f32_9c + fVar4;
        if (0.5 <= this->f32_9c) {
          this->u32_9c = 0;
          this->u32_40 = 2;
        }
      }
      else if (iVar3 == 0) {
        this->f32_9c = this->f32_9c + fVar4;
        this->f32_84 = this->f32_9c * 128.0 * 8.0;
        if (128.0 <= this->f32_84) {
          this->u32_84 = 0x43000000;
        }
        this->f32_80 = 8.0 - this->f32_9c * 7.0 * 5.0;
        if (this->f32_80 <= 1.0) {
          this->u32_80 = 0x3f800000;
        }
        if ((this->f32_80 == 1.0) && (this->f32_84 == 128.0)) {
          this->u32_9c = 0;
          this->u32_40 = 1;
        }
      }
    }
    else if (sVar1 == 2) {
      iVar3 = this->i32_40;
      if (iVar3 == 2) {
        this->f32_9c = this->f32_9c + fVar4;
        this->f32_84 = 128.0 - (this->f32_9c / 0.25) * 128.0;
        if (this->f32_84 <= 0.0) {
          this->u32_84 = 0;
          this->u8_3c = this->u8_3c & 0xf7 | 8;
        }
      }
      else if (iVar3 == 1) {
        this->f32_9c = this->f32_9c + fVar4;
        if (0.5 <= this->f32_9c) {
          this->u32_9c = 0;
          this->u32_40 = 2;
        }
      }
      else if (iVar3 == 0) {
        this->f32_9c = this->f32_9c + fVar4;
        fStack_20 = (this->f32_9c / 0.25) * 6.2831855;
        if (6.2831855 < fStack_20) {
          fStack_20 = 6.2831855;
        }
        this->f32_74 = 6.2831855 - fStack_20;
        this->f32_84 = (this->f32_9c / 0.125) * 128.0;
        if (128.0 < this->f32_84) {
          this->u32_84 = 0x43000000;
        }
        if (0.25 <= this->f32_9c) {
          this->u32_74 = 0;
          this->u32_84 = 0x43000000;
          this->u32_40 = 1;
          this->u32_9c = 0;
        }
      }
    }
    else if (sVar1 == 1) {
      iVar3 = this->i32_40;
      if (iVar3 == 2) {
        this->f32_9c = this->f32_9c + fVar4;
        this->f32_84 = 128.0 - (this->f32_9c / 0.25) * 128.0;
        if (this->f32_84 <= 0.0) {
          this->u32_84 = 0;
          this->u8_3c = this->u8_3c & 0xf7 | 8;
        }
      }
      else if ((iVar3 != 1) && (iVar3 == 0)) {
        this->f32_9c = this->f32_9c + fVar4;
        this->f32_84 = this->f32_9c * 128.0 * 8.0;
        if (128.0 <= this->f32_84) {
          this->u32_84 = 0x43000000;
        }
        this->f32_80 = 8.0 - this->f32_9c * 7.0 * 5.0;
        if (this->f32_80 <= 1.0) {
          this->u32_80 = 0x3f800000;
        }
        if ((this->f32_80 == 1.0) && (this->f32_84 == 128.0)) {
          this->u32_9c = 0;
          this->u32_40 = 1;
        }
        this->f32_48 =
             *(float *)(this->i32_38 + 0x6c) -
             *(float *)(this->i32_38 + 0x84) * 122.0;
      }
    }
    else if (sVar1 == 0) {
      iVar3 = this->i32_40;
      if (iVar3 == 2) {
        this->f32_9c = this->f32_9c + fVar4;
        this->f32_84 = 128.0 - (this->f32_9c / 0.25) * 128.0;
        if (this->f32_84 <= 0.0) {
          this->u32_84 = 0;
          this->u8_3c = this->u8_3c & 0xf7 | 8;
        }
      }
      else if ((iVar3 != 1) && (iVar3 == 0)) {
        this->f32_9c = this->f32_9c + fVar4;
        fVar4 = this->f32_44 * 2.0 +
                (float)(int)this->i16_8c * this->f32_80;
        fStack_18 = (512.0 - this->f32_44) * 2.0 +
                    (float)(int)this->i16_8c * this->f32_80;
        if (fStack_18 <= fVar4) {
          fStack_18 = fVar4;
        }
        this->f32_a4 = fStack_18 * (1.0 - this->f32_9c / 0.25);
        if (this->f32_a4 <= 0.0) {
          this->u32_a4 = 0;
          this->u32_9c = 0;
          this->u32_40 = 1;
        }
        this->f32_48 =
             *(float *)(this->i32_38 + 0x6c) -
             *(float *)(this->i32_38 + 0x84) * 122.0;
      }
    }
    uVar2 = 0;
  }
  return uVar2;
}

// JP: 0x002e2b20  MakePacket__10ComboTrialFv  =  ComboTrial::MakePacket
void ComboTrial::MakePacket(int this)

{
  bool bVar1;
  bool bVar2;
  float in_zero_lo;
  float in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  undefined4 uVar3;
  int iVar4;
  ulong uVar5;
  long lVar6;
  undefined8 extraout_v0_udw;
  undefined1 auVar7 [16];
  undefined4 *puVar8;
  uint uVar9;
  undefined1 in_vf0 [16];
  undefined1 auVar10 [16];
  undefined1 auVar11 [16];
  undefined1 auVar12 [16];
  undefined1 auStack_1c0 [16];
  undefined1 auStack_1b0 [16];
  undefined1 auStack_1a0 [16];
  undefined1 auStack_190 [16];
  int aiStack_180 [5];
  int iStack_16c;
  int iStack_160;
  int iStack_15c;
  int iStack_150;
  int iStack_14c;
  int aiStack_140 [5];
  int iStack_12c;
  int iStack_120;
  int iStack_11c;
  int iStack_110;
  int iStack_10c;
  float afStack_100 [16];
  float afStack_c0 [16];
  float fStack_80;
  float fStack_7c;
  undefined4 uStack_78;
  undefined4 uStack_74;
  float fStack_70;
  float fStack_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
  float fStack_60;
  float fStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  float fStack_50;
  float fStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  float fStack_40;
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
  float fStack_10;
  float fStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  auVar10 = _vmr32(in_vf0);
  auVar11 = _vmr32(auVar10);
  auVar12 = _vmr32(auVar11);
  _sqc2(in_vf0);
  _sqc2(auVar10);
  _sqc2(auVar11);
  _sqc2(auVar12);
  if (this->i16_3e == 0) {
    fStack_7c = ((float)-(int)this->i16_8e * this->f32_80) / 2.0;
    fStack_80 = ((float)-(int)this->i16_8c * this->f32_80) / 2.0;
    uStack_78 = 0;
    uStack_74 = 0x3f800000;
    fStack_70 = ((float)-(int)this->i16_8c * this->f32_80) / 2.0;
    fStack_6c = 0.0;
    uStack_68 = 0;
    uStack_64 = 0x3f800000;
    fStack_5c = ((float)-(int)this->i16_8e * this->f32_80) / 2.0;
    fStack_60 = ((float)(int)this->i16_8c * this->f32_80) / 2.0;
    uStack_58 = 0;
    uStack_54 = 0x3f800000;
    fStack_50 = ((float)(int)this->i16_8c * this->f32_80) / 2.0;
    fStack_4c = 0.0;
    uStack_48 = 0;
    uStack_44 = 0x3f800000;
    fStack_40 = ((float)-(int)this->i16_8c * this->f32_80) / 2.0;
    fStack_3c = 0.0;
    uStack_38 = 0;
    uStack_34 = 0x3f800000;
    fStack_2c = ((float)(int)this->i16_8e * this->f32_80) / 2.0;
    fStack_30 = ((float)-(int)this->i16_8c * this->f32_80) / 2.0;
    uStack_28 = 0;
    uStack_24 = 0x3f800000;
    fStack_20 = ((float)(int)this->i16_8c * this->f32_80) / 2.0;
    fStack_1c = 0.0;
    uStack_18 = 0;
    uStack_14 = 0x3f800000;
    fStack_c = ((float)(int)this->i16_8e * this->f32_80) / 2.0;
    fStack_10 = ((float)(int)this->i16_8c * this->f32_80) / 2.0;
    uStack_8 = 0;
    uStack_4 = 0x3f800000;
    auVar10 = _vmr32(in_vf0);
    auVar11 = _vmr32(auVar10);
    auVar12 = _vmr32(auVar11);
    auStack_190 = _sqc2(in_vf0);
    auStack_1a0 = _sqc2(auVar10);
    auStack_1b0 = _sqc2(auVar11);
    auStack_1c0 = _sqc2(auVar12);
    sceVu0RotMatrixZ(this->u32_78,auStack_1c0,auStack_1c0);
    sceVu0RotMatrixX(this->u32_70,auStack_1c0,auStack_1c0);
    sceVu0RotMatrixY(this->u32_74,auStack_1c0,auStack_1c0);
    RotTransVector(afStack_100,&fStack_80,auStack_1c0,8);
    bVar2 = false;
    for (iVar4 = 0; iVar4 < 4; iVar4 = iVar4 + 1) {
      aiStack_180[iVar4 * 4] =
           (int)((this->f32_a4 / 2.0 +
                 this->f32_44 + afStack_100[iVar4 * 4]) * 16.0 + 28672.0);
      aiStack_180[iVar4 * 4 + 1] =
           (int)((this->f32_48 + afStack_100[iVar4 * 4 + 1]) * 16.0 + 29184.0);
      if ((aiStack_180[iVar4 * 4] < 0) || (0x10000 < aiStack_180[iVar4 * 4])) {
        bVar2 = true;
      }
      if ((aiStack_180[iVar4 * 4 + 1] < 0) || (0x10000 < aiStack_180[iVar4 * 4 + 1])) {
        bVar2 = true;
      }
    }
    for (iVar4 = 4; iVar4 < 8; iVar4 = iVar4 + 1) {
      aiStack_180[iVar4 * 4] =
           (int)(((this->f32_44 + afStack_100[iVar4 * 4]) -
                 this->f32_a4 / 2.0) * 16.0 + 28672.0);
      aiStack_180[iVar4 * 4 + 1] =
           (int)((this->f32_48 + afStack_100[iVar4 * 4 + 1]) * 16.0 + 29184.0);
      if ((aiStack_180[iVar4 * 4] < 0) || (0x10000 < aiStack_180[iVar4 * 4])) {
        bVar2 = true;
      }
      if ((aiStack_180[iVar4 * 4 + 1] < 0) || (0x10000 < aiStack_180[iVar4 * 4 + 1])) {
        bVar2 = true;
      }
    }
  }
  else {
    fStack_7c = ((float)-(int)this->i16_8e * this->f32_80) / 2.0;
    fStack_80 = ((float)-(int)this->i16_8c * this->f32_80) / 2.0;
    uStack_78 = 0;
    uStack_74 = 0x3f800000;
    fStack_6c = ((float)(int)this->i16_8e * this->f32_80) / 2.0;
    fStack_70 = ((float)-(int)this->i16_8c * this->f32_80) / 2.0;
    uStack_68 = 0;
    uStack_64 = 0x3f800000;
    fStack_5c = ((float)-(int)this->i16_8e * this->f32_80) / 2.0;
    fStack_60 = ((float)(int)this->i16_8c * this->f32_80) / 2.0;
    uStack_58 = 0;
    uStack_54 = 0x3f800000;
    fStack_4c = ((float)(int)this->i16_8e * this->f32_80) / 2.0;
    fStack_50 = ((float)(int)this->i16_8c * this->f32_80) / 2.0;
    uStack_48 = 0;
    uStack_44 = 0x3f800000;
    auVar10 = _vmr32(in_vf0);
    auVar11 = _vmr32(auVar10);
    auVar12 = _vmr32(auVar11);
    auStack_190 = _sqc2(in_vf0);
    auStack_1a0 = _sqc2(auVar10);
    auStack_1b0 = _sqc2(auVar11);
    auStack_1c0 = _sqc2(auVar12);
    fStack_40 = in_zero_lo;
    fStack_3c = in_zero_hi;
    uStack_38 = in_zero_udw;
    uStack_34 = in_register_0000000c;
    fStack_30 = in_zero_lo;
    fStack_2c = in_zero_hi;
    uStack_28 = in_zero_udw;
    uStack_24 = in_register_0000000c;
    fStack_20 = in_zero_lo;
    fStack_1c = in_zero_hi;
    uStack_18 = in_zero_udw;
    uStack_14 = in_register_0000000c;
    fStack_10 = in_zero_lo;
    fStack_c = in_zero_hi;
    uStack_8 = in_zero_udw;
    uStack_4 = in_register_0000000c;
    sceVu0RotMatrixZ(this->u32_78,auStack_1c0,auStack_1c0);
    sceVu0RotMatrixX(this->u32_70,auStack_1c0,auStack_1c0);
    sceVu0RotMatrixY(this->u32_74,auStack_1c0,auStack_1c0);
    RotTransVector(afStack_100,&fStack_80,auStack_1c0,4);
    bVar2 = false;
    for (iVar4 = 0; iVar4 < 4; iVar4 = iVar4 + 1) {
      aiStack_180[iVar4 * 4] =
           (int)((this->f32_44 + afStack_100[iVar4 * 4]) * 16.0 + 28672.0);
      aiStack_180[iVar4 * 4 + 1] =
           (int)((this->f32_48 + afStack_100[iVar4 * 4 + 1]) * 16.0 + 29184.0);
      if ((aiStack_180[iVar4 * 4] < 0) || (0x10000 < aiStack_180[iVar4 * 4])) {
        bVar2 = true;
      }
      if ((aiStack_180[iVar4 * 4 + 1] < 0) || (0x10000 < aiStack_180[iVar4 * 4 + 1])) {
        bVar2 = true;
      }
    }
  }
  bVar1 = (this->u8_3c & 3) == 0;
  uVar9 = (uint)bVar1;
  if (*(int *)(this + uVar9 * 4 + 0x18) == 0) {
    uVar3 = __nwa(this->i32_94 << 4);
    *(undefined4 *)(this + uVar9 * 4 + 0x18) = uVar3;
  }
  this->u8_3c = this->u8_3c & 0xfb | 4;
  puVar8 = *(undefined4 **)(this + uVar9 * 4 + 0x18);
  if (bVar2) {
    *(undefined4 **)(this + 0x98) = puVar8;
    this->u8_3c = this->u8_3c & 0xfc | bVar1;
  }
  else {
    *puVar8 = 0x50000000;
    puVar8[1] = *(undefined4 *)(DAT_00421c18 + (uint)DAT_00421c18->u16_a * 4 + 0xc);
    puVar8[2] = 0;
    puVar8[3] = 0;
    puVar8[4] = this->i32_94 + 0xffffffd;
    puVar8[5] = 0;
    puVar8[6] = 0;
    puVar8[7] = this->i32_94 + 0x4ffffffd;
    puVar8->u64_8 = 0x5000000000000001;
    puVar8->u64_a = 0xee6ee;
    puVar8->u64_c = 1;
    puVar8->u64_e = 0x3f;
    uVar5 = JRCTex::GetTex0(DAT_00421c18,1);
    puVar8->u64_10 = uVar5 & 0xfffffffc0fffff | 0x2000000001300000;
    puVar8->u64_12 = 0x16;
    uVar5 = JRCTex::GetTex0(DAT_00421c18,1);
    puVar8->u64_14 = uVar5 & 0xffffffffffffff | (long)this->i32_90 << 0x38;
    puVar8->u64_16 = 0;
    puVar8->u64_18 = 0x23001;
    puVar8->u64_1a = 0x47;
    puVar8->u64_1c = 0x44;
    puVar8->u64_1e = 0x42;
    if (this->i16_3e == 0) {
      auVar7._8_8_ = extraout_v0_udw;
      auVar7._0_8_ = 0xa400000000008002;
      auVar12._4_4_ = in_zero_hi;
      auVar12._0_4_ = in_zero_lo;
      auVar12._8_4_ = in_zero_udw;
      auVar12._12_4_ = in_register_0000000c;
      auVar10 = _pcpyld(auVar12,auVar7);
      puVar8->i64_20 = auVar10._0_8_;
      puVar8->u64_22 = 0x4343c3c310;
      puVar8->u64_24 = 0x154;
      lVar6 = __fixunssfdi(this->u32_84);
      puVar8->u64_26 = lVar6 << 0x18 | 0x808080;
      puVar8->i64_28 =
           (long)((int)this->i16_88 << 4) |
           (long)((int)this->i16_8a << 4) << 0x10;
      puVar8->i64_2a = (long)aiStack_180[0] | (long)aiStack_180[1] << 0x10;
      iVar4 = (int)this->i16_8e;
      if (this->i16_8e < 0) {
        iVar4 = iVar4 + 1;
      }
      puVar8->i64_2c =
           (long)((int)this->i16_88 << 4) |
           (long)(((int)this->i16_8a + (iVar4 >> 1)) * 0x10) << 0x10;
      puVar8->i64_2e = (long)aiStack_180[4] | (long)iStack_16c << 0x10;
      puVar8->i64_30 =
           (long)((int)this->i16_8a << 4) << 0x10 |
           (long)(((int)this->i16_88 + (int)this->i16_8c) * 0x10);
      puVar8->i64_32 = (long)iStack_160 | (long)iStack_15c << 0x10;
      iVar4 = (int)this->i16_8e;
      if (this->i16_8e < 0) {
        iVar4 = iVar4 + 1;
      }
      puVar8->i64_34 =
           (long)(((int)this->i16_88 + (int)this->i16_8c) * 0x10) |
           (long)(((int)this->i16_8a + (iVar4 >> 1)) * 0x10) << 0x10;
      puVar8->i64_36 = (long)iStack_150 | (long)iStack_14c << 0x10;
      puVar8->u64_38 = 0x154;
      lVar6 = __fixunssfdi(this->u32_84);
      puVar8->u64_3a = lVar6 << 0x18 | 0x808080;
      iVar4 = (int)this->i16_8e;
      if (this->i16_8e < 0) {
        iVar4 = iVar4 + 1;
      }
      puVar8->i64_3c =
           (long)((int)this->i16_88 << 4) |
           (long)(((int)this->i16_8a + (iVar4 >> 1)) * 0x10) << 0x10;
      puVar8->i64_3e = (long)aiStack_140[0] | (long)aiStack_140[1] << 0x10;
      puVar8->i64_40 =
           (long)((int)this->i16_88 << 4) |
           (long)(((int)this->i16_8a + (int)this->i16_8e) * 0x10) <<
           0x10;
      puVar8->i64_42 = (long)aiStack_140[4] | (long)iStack_12c << 0x10;
      iVar4 = (int)this->i16_8e;
      if (this->i16_8e < 0) {
        iVar4 = iVar4 + 1;
      }
      puVar8->i64_44 =
           (long)(((int)this->i16_88 + (int)this->i16_8c) * 0x10) |
           (long)(((int)this->i16_8a + (iVar4 >> 1)) * 0x10) << 0x10;
      puVar8->i64_46 = (long)iStack_120 | (long)iStack_11c << 0x10;
      puVar8->i64_48 =
           (long)(((int)this->i16_88 + (int)this->i16_8c) * 0x10) |
           (long)(((int)this->i16_8a + (int)this->i16_8e) * 0x10) <<
           0x10;
      puVar8->i64_4a = (long)iStack_110 | (long)iStack_10c << 0x10;
      puVar8 = puVar8 + 0x4c;
    }
    else {
      auVar11._8_8_ = extraout_v0_udw;
      auVar11._0_8_ = 0xa400000000008001;
      auVar10._4_4_ = in_zero_hi;
      auVar10._0_4_ = in_zero_lo;
      auVar10._8_4_ = in_zero_udw;
      auVar10._12_4_ = in_register_0000000c;
      auVar10 = _pcpyld(auVar10,auVar11);
      puVar8->i64_20 = auVar10._0_8_;
      puVar8->u64_22 = 0x4343c3c310;
      puVar8->u64_24 = 0x154;
      lVar6 = __fixunssfdi(this->u32_84);
      puVar8->u64_26 = lVar6 << 0x18 | 0x808080;
      puVar8->i64_28 =
           (long)((int)this->i16_88 << 4) |
           (long)((int)this->i16_8a << 4) << 0x10;
      puVar8->i64_2a = (long)aiStack_180[0] | (long)aiStack_180[1] << 0x10;
      puVar8->i64_2c =
           (long)((int)this->i16_88 << 4) |
           (long)(((int)this->i16_8a + (int)this->i16_8e) * 0x10) <<
           0x10;
      puVar8->i64_2e = (long)aiStack_180[4] | (long)iStack_16c << 0x10;
      puVar8->i64_30 =
           (long)((int)this->i16_8a << 4) << 0x10 |
           (long)(((int)this->i16_88 + (int)this->i16_8c) * 0x10);
      puVar8->i64_32 = (long)iStack_160 | (long)iStack_15c << 0x10;
      puVar8->i64_34 =
           (long)(((int)this->i16_88 + (int)this->i16_8c) * 0x10) |
           (long)(((int)this->i16_8a + (int)this->i16_8e) * 0x10) <<
           0x10;
      puVar8->i64_36 = (long)iStack_150 | (long)iStack_14c << 0x10;
      puVar8 = puVar8 + 0x38;
    }
    *(undefined4 **)(this + 0x98) = puVar8;
    this->u8_3c = this->u8_3c & 0xfc | bVar1;
  }
  return;
}
