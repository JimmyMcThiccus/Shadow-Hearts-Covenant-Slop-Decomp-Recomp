/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x002c9750  getPacket__10ComboTrialFv  size 0x44
// ComboTrial::getPacket()
u32 getPacket__10ComboTrialFv(ComboTrial *this)
{
  MakePacket__10ComboTrialFv(this);
  return *(u32 *)(this + (this->f_3c /*u8 **/ & 3) * 4 + 0x18);
}

// JP: 0x002e1ac0  __ct__10ComboTrialFP5JRingis  size 0x450
// ComboTrial::ComboTrial(JRing*, int, short)
u64
__ct__10ComboTrialFP5JRingis(u64 param_1,int this,long param_3,u16 param_4)
{
  short sVar1;
  u32 in_zero_lo;
  u32 in_zero_hi;
  u32 in_zero_udw;
  u32 in_register_0000000c;
  u32 uVar2;
  int iVar3;
  float fVar4;
  float fVar5;
  __ct__7CPolObjFv(param_1);
  iVar3 = (int)param_1;
  __ct__8VIF1PrimFv(iVar3 + 0x18);
  *(u32 *)(iVar3 + 0x2c) = 0;
  *(u32 *)(iVar3 + 0x30) = 0;
  *(u8 **)(iVar3 + 0x34) = __vt__17DelayDeleteObject;
  *(u8 **)(iVar3 + 0x14) = __vt__10ComboTrial;
  *(u32 *)(iVar3 + 0x28) = 0x4067d0;
  *(u32 *)(iVar3 + 0x34) = 0x4067e0;
  *(u32 *)(iVar3 + 0x60) = in_zero_lo;
  *(u32 *)(iVar3 + 100) = in_zero_hi;
  *(u32 *)(iVar3 + 0x68) = in_zero_udw;
  *(u32 *)(iVar3 + 0x6c) = in_register_0000000c;
  *(u32 *)(iVar3 + 0x70) = in_zero_lo;
  *(u32 *)(iVar3 + 0x74) = in_zero_hi;
  *(u32 *)(iVar3 + 0x78) = in_zero_udw;
  *(u32 *)(iVar3 + 0x7c) = in_register_0000000c;
  *(int *)(iVar3 + 0x38) = this;
  *(u16 *)(iVar3 + 0x3c) = 0;
  *(u16 *)(iVar3 + 0x3e) = param_4;
  *(u32 *)(iVar3 + 0x40) = 0;
  *(u32 *)(iVar3 + 0x9c) = 0;
  uVar2 = GetTimer__7SysToolFv();
  *(u32 *)(iVar3 + 0xa0) = uVar2;
  *(u32 *)(iVar3 + 0x1c) = 0;
  *(u32 *)(iVar3 + 0x18) = 0;
  *(u32 *)(iVar3 + 0x98) = 0;
  *(u32 *)(iVar3 + 0x44) = this->f_68 /*u32 **/;
  *(u32 *)(iVar3 + 0x48) = this->f_6c /*u32 **/;
  if (param_3 == 2) {
    *(u16 *)(iVar3 + 0x88) = 0;
    *(u16 *)(iVar3 + 0x8a) = 0x48;
    *(u16 *)(iVar3 + 0x8c) = 0xae;
    *(u16 *)(iVar3 + 0x8e) = 0x21;
    *(u32 *)(iVar3 + 0x90) = 2;
  }
  else if (param_3 == 1) {
    *(u16 *)(iVar3 + 0x88) = 0;
    *(u16 *)(iVar3 + 0x8a) = 0x24;
    *(u16 *)(iVar3 + 0x8c) = 0x6e;
    *(u16 *)(iVar3 + 0x8e) = 0x1f;
    *(u32 *)(iVar3 + 0x90) = 0;
  }
  else if (param_3 == 0) {
    *(u16 *)(iVar3 + 0x88) = 0;
    *(u16 *)(iVar3 + 0x8a) = 0;
    *(u16 *)(iVar3 + 0x8c) = 0xa1;
    *(u16 *)(iVar3 + 0x8e) = 0x21;
    *(u32 *)(iVar3 + 0x90) = 3;
  }
  sVar1 = *(short *)(iVar3 + 0x3e);
  if (sVar1 == 3) {
    *(u32 *)(iVar3 + 0x70) = 0;
    *(u32 *)(iVar3 + 0x74) = 0;
    *(u32 *)(iVar3 + 0x78) = 0;
    *(u32 *)(iVar3 + 0x7c) = 0;
    *(u32 *)(iVar3 + 0x80) = 0x41000000;
    *(u32 *)(iVar3 + 0x84) = 0;
    *(u32 *)(iVar3 + 0xa4) = 0;
    *(u32 *)(iVar3 + 0x94) = 0xf;
  }
  else if (sVar1 == 2) {
    *(u32 *)(iVar3 + 0x70) = 0;
    *(u32 *)(iVar3 + 0x74) = 0x40c90fdb;
    *(u32 *)(iVar3 + 0x78) = 0;
    *(u32 *)(iVar3 + 0x7c) = 0;
    *(u32 *)(iVar3 + 0x80) = 0x3f99999a;
    *(u32 *)(iVar3 + 0x84) = 0;
    *(u32 *)(iVar3 + 0xa4) = 0;
    *(u32 *)(iVar3 + 0x94) = 0xf;
  }
  else if (sVar1 == 1) {
    *(u32 *)(iVar3 + 0x70) = 0;
    *(u32 *)(iVar3 + 0x74) = 0;
    *(u32 *)(iVar3 + 0x78) = 0;
    *(u32 *)(iVar3 + 0x7c) = 0;
    *(u32 *)(iVar3 + 0x80) = 0x41000000;
    *(u32 *)(iVar3 + 0x84) = 0;
    *(u32 *)(iVar3 + 0xa4) = 0;
    *(u32 *)(iVar3 + 0x94) = 0xf;
  }
  else if (sVar1 == 0) {
    *(u32 *)(iVar3 + 0x70) = 0;
    *(u32 *)(iVar3 + 0x74) = 0;
    *(u32 *)(iVar3 + 0x78) = 0;
    *(u32 *)(iVar3 + 0x7c) = 0;
    *(u32 *)(iVar3 + 0x80) = 0x3f99999a;
    *(u32 *)(iVar3 + 0x84) = 0x43000000;
    fVar5 = *(float *)(iVar3 + 0x44) * 2.0 +
            (float)(int)*(short *)(iVar3 + 0x8c) * *(float *)(iVar3 + 0x80);
    fVar4 = (512.0 - *(float *)(iVar3 + 0x44)) * 2.0 +
            (float)(int)*(short *)(iVar3 + 0x8c) * *(float *)(iVar3 + 0x80);
    if (fVar4 <= fVar5) {
      fVar4 = fVar5;
    }
    *(float *)(iVar3 + 0xa4) = fVar4;
    *(u32 *)(iVar3 + 0x94) = 0x14;
  }
  Entry__7CPollerFP7CPolObjib(app__4CApp + 0x48,param_1,0x80,0);
  return param_1;
}

// JP: 0x002e1f10  __dt__10ComboTrialFv  size 0x114
// ComboTrial::~ComboTrial()
int __dt__10ComboTrialFv(ComboTrial *this,short param_2)
{
  if (this != 0) {
    this->f_14 /*u8 **/ = __vt__10ComboTrial;
    this->f_28 /*u32 **/ = 0x4067d0;
    this->f_34 /*u32 **/ = 0x4067e0;
    if (this->f_18 /*int **/ != 0) {
      __dla__FPv(this->f_18 /*u32 **/);
    }
    if (this->f_1c /*int **/ != 0) {
      __dla__FPv(this->f_1c /*u32 **/);
    }
    if (this != -0x2c) {
      this->f_34 /*u8 **/ = __vt__17DelayDeleteObject;
    }
    __dt__8VIF1PrimFv(this + 0x18,0);
    __dt__7CPolObjFv(this,0);
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}

// JP: 0x002e2030  Destruct__10ComboTrialFv  size 0x48
// ComboTrial::Destruct()
void Destruct__10ComboTrialFv(ComboTrial *this)
{
  Dispose__7CPollerFP7CPolObj(app__4CApp + 0x48,this);
  (**(code **)(this->f_34 /*int **/ + 0xc))();
  return;
}

// JP: 0x002e2080  Polling__10ComboTrialFv  size 0xa9c
// ComboTrial::Polling()
u32 Polling__10ComboTrialFv(ComboTrial *this)
{
  short sVar1;
  u32 uVar2;
  int iVar3;
  float fVar4;
  float fStack_20;
  float fStack_18;
  if ((long)((ulong)this->f_3c /*u8 **/ << 0x3c) < 0) {
    (**(code **)(this->f_34 /*int **/ + 0xc))();
    uVar2 = 1;
  }
  else {
    iVar3 = GetTimer__7SysToolFv();
    fVar4 = (float)(uint)(iVar3 - this->f_a0 /*int **/) * 0.001;
    this->f_a0 /*int **/ = iVar3;
    sVar1 = this->f_3e /*short **/;
    if (sVar1 == 3) {
      iVar3 = this->f_40 /*int **/;
      if (iVar3 == 2) {
        this->f_9c /*float **/ = this->f_9c /*float **/ + fVar4;
        this->f_84 /*float **/ = 128.0 - (this->f_9c /*float **/ / 0.25) * 128.0;
        if (this->f_84 /*float **/ <= 0.0) {
          this->f_84 /*u32 **/ = 0;
          this->f_3c /*u8 **/ = this->f_3c /*u8 **/ & 0xf7 | 8;
        }
      }
      else if (iVar3 == 1) {
        this->f_9c /*float **/ = this->f_9c /*float **/ + fVar4;
        if (0.5 <= this->f_9c /*float **/) {
          this->f_9c /*u32 **/ = 0;
          this->f_40 /*u32 **/ = 2;
        }
      }
      else if (iVar3 == 0) {
        this->f_9c /*float **/ = this->f_9c /*float **/ + fVar4;
        this->f_84 /*float **/ = this->f_9c /*float **/ * 128.0 * 8.0;
        if (128.0 <= this->f_84 /*float **/) {
          this->f_84 /*u32 **/ = 0x43000000;
        }
        this->f_80 /*float **/ = 8.0 - this->f_9c /*float **/ * 7.0 * 5.0;
        if (this->f_80 /*float **/ <= 1.0) {
          this->f_80 /*u32 **/ = 0x3f800000;
        }
        if ((this->f_80 /*float **/ == 1.0) && (this->f_84 /*float **/ == 128.0)) {
          this->f_9c /*u32 **/ = 0;
          this->f_40 /*u32 **/ = 1;
        }
      }
    }
    else if (sVar1 == 2) {
      iVar3 = this->f_40 /*int **/;
      if (iVar3 == 2) {
        this->f_9c /*float **/ = this->f_9c /*float **/ + fVar4;
        this->f_84 /*float **/ = 128.0 - (this->f_9c /*float **/ / 0.25) * 128.0;
        if (this->f_84 /*float **/ <= 0.0) {
          this->f_84 /*u32 **/ = 0;
          this->f_3c /*u8 **/ = this->f_3c /*u8 **/ & 0xf7 | 8;
        }
      }
      else if (iVar3 == 1) {
        this->f_9c /*float **/ = this->f_9c /*float **/ + fVar4;
        if (0.5 <= this->f_9c /*float **/) {
          this->f_9c /*u32 **/ = 0;
          this->f_40 /*u32 **/ = 2;
        }
      }
      else if (iVar3 == 0) {
        this->f_9c /*float **/ = this->f_9c /*float **/ + fVar4;
        fStack_20 = (this->f_9c /*float **/ / 0.25) * 6.2831855;
        if (6.2831855 < fStack_20) {
          fStack_20 = 6.2831855;
        }
        this->f_74 /*float **/ = 6.2831855 - fStack_20;
        this->f_84 /*float **/ = (this->f_9c /*float **/ / 0.125) * 128.0;
        if (128.0 < this->f_84 /*float **/) {
          this->f_84 /*u32 **/ = 0x43000000;
        }
        if (0.25 <= this->f_9c /*float **/) {
          this->f_74 /*u32 **/ = 0;
          this->f_84 /*u32 **/ = 0x43000000;
          this->f_40 /*u32 **/ = 1;
          this->f_9c /*u32 **/ = 0;
        }
      }
    }
    else if (sVar1 == 1) {
      iVar3 = this->f_40 /*int **/;
      if (iVar3 == 2) {
        this->f_9c /*float **/ = this->f_9c /*float **/ + fVar4;
        this->f_84 /*float **/ = 128.0 - (this->f_9c /*float **/ / 0.25) * 128.0;
        if (this->f_84 /*float **/ <= 0.0) {
          this->f_84 /*u32 **/ = 0;
          this->f_3c /*u8 **/ = this->f_3c /*u8 **/ & 0xf7 | 8;
        }
      }
      else if ((iVar3 != 1) && (iVar3 == 0)) {
        this->f_9c /*float **/ = this->f_9c /*float **/ + fVar4;
        this->f_84 /*float **/ = this->f_9c /*float **/ * 128.0 * 8.0;
        if (128.0 <= this->f_84 /*float **/) {
          this->f_84 /*u32 **/ = 0x43000000;
        }
        this->f_80 /*float **/ = 8.0 - this->f_9c /*float **/ * 7.0 * 5.0;
        if (this->f_80 /*float **/ <= 1.0) {
          this->f_80 /*u32 **/ = 0x3f800000;
        }
        if ((this->f_80 /*float **/ == 1.0) && (this->f_84 /*float **/ == 128.0)) {
          this->f_9c /*u32 **/ = 0;
          this->f_40 /*u32 **/ = 1;
        }
        this->f_48 /*float **/ =
             *(float *)(this->f_38 /*int **/ + 0x6c) -
             *(float *)(this->f_38 /*int **/ + 0x84) * 122.0;
      }
    }
    else if (sVar1 == 0) {
      iVar3 = this->f_40 /*int **/;
      if (iVar3 == 2) {
        this->f_9c /*float **/ = this->f_9c /*float **/ + fVar4;
        this->f_84 /*float **/ = 128.0 - (this->f_9c /*float **/ / 0.25) * 128.0;
        if (this->f_84 /*float **/ <= 0.0) {
          this->f_84 /*u32 **/ = 0;
          this->f_3c /*u8 **/ = this->f_3c /*u8 **/ & 0xf7 | 8;
        }
      }
      else if ((iVar3 != 1) && (iVar3 == 0)) {
        this->f_9c /*float **/ = this->f_9c /*float **/ + fVar4;
        fVar4 = this->f_44 /*float **/ * 2.0 +
                (float)(int)this->f_8c /*short **/ * this->f_80 /*float **/;
        fStack_18 = (512.0 - this->f_44 /*float **/) * 2.0 +
                    (float)(int)this->f_8c /*short **/ * this->f_80 /*float **/;
        if (fStack_18 <= fVar4) {
          fStack_18 = fVar4;
        }
        this->f_a4 /*float **/ = fStack_18 * (1.0 - this->f_9c /*float **/ / 0.25);
        if (this->f_a4 /*float **/ <= 0.0) {
          this->f_a4 /*u32 **/ = 0;
          this->f_9c /*u32 **/ = 0;
          this->f_40 /*u32 **/ = 1;
        }
        this->f_48 /*float **/ =
             *(float *)(this->f_38 /*int **/ + 0x6c) -
             *(float *)(this->f_38 /*int **/ + 0x84) * 122.0;
      }
    }
    uVar2 = 0;
  }
  return uVar2;
}

// JP: 0x002e2b20  MakePacket__10ComboTrialFv  size 0x1518
// ComboTrial::MakePacket()
void MakePacket__10ComboTrialFv(ComboTrial *this)
{
  bool bVar1;
  bool bVar2;
  float in_zero_lo;
  float in_zero_hi;
  u32 in_zero_udw;
  u32 in_register_0000000c;
  u32 uVar3;
  int iVar4;
  ulong uVar5;
  long lVar6;
  u64 extraout_v0_udw;
  u8 auVar7 [16];
  u32 *puVar8;
  uint uVar9;
  u8 in_vf0 [16];
  u8 auVar10 [16];
  u8 auVar11 [16];
  u8 auVar12 [16];
  u8 auStack_1c0 [16];
  u8 auStack_1b0 [16];
  u8 auStack_1a0 [16];
  u8 auStack_190 [16];
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
  u32 uStack_78;
  u32 uStack_74;
  float fStack_70;
  float fStack_6c;
  u32 uStack_68;
  u32 uStack_64;
  float fStack_60;
  float fStack_5c;
  u32 uStack_58;
  u32 uStack_54;
  float fStack_50;
  float fStack_4c;
  u32 uStack_48;
  u32 uStack_44;
  float fStack_40;
  float fStack_3c;
  u32 uStack_38;
  u32 uStack_34;
  float fStack_30;
  float fStack_2c;
  u32 uStack_28;
  u32 uStack_24;
  float fStack_20;
  float fStack_1c;
  u32 uStack_18;
  u32 uStack_14;
  float fStack_10;
  float fStack_c;
  u32 uStack_8;
  u32 uStack_4;
  auVar10 = _vmr32(in_vf0);
  auVar11 = _vmr32(auVar10);
  auVar12 = _vmr32(auVar11);
  _sqc2(in_vf0);
  _sqc2(auVar10);
  _sqc2(auVar11);
  _sqc2(auVar12);
  if (this->f_3e /*short **/ == 0) {
    fStack_7c = ((float)-(int)this->f_8e /*short **/ * this->f_80 /*float **/) / 2.0;
    fStack_80 = ((float)-(int)this->f_8c /*short **/ * this->f_80 /*float **/) / 2.0;
    uStack_78 = 0;
    uStack_74 = 0x3f800000;
    fStack_70 = ((float)-(int)this->f_8c /*short **/ * this->f_80 /*float **/) / 2.0;
    fStack_6c = 0.0;
    uStack_68 = 0;
    uStack_64 = 0x3f800000;
    fStack_5c = ((float)-(int)this->f_8e /*short **/ * this->f_80 /*float **/) / 2.0;
    fStack_60 = ((float)(int)this->f_8c /*short **/ * this->f_80 /*float **/) / 2.0;
    uStack_58 = 0;
    uStack_54 = 0x3f800000;
    fStack_50 = ((float)(int)this->f_8c /*short **/ * this->f_80 /*float **/) / 2.0;
    fStack_4c = 0.0;
    uStack_48 = 0;
    uStack_44 = 0x3f800000;
    fStack_40 = ((float)-(int)this->f_8c /*short **/ * this->f_80 /*float **/) / 2.0;
    fStack_3c = 0.0;
    uStack_38 = 0;
    uStack_34 = 0x3f800000;
    fStack_2c = ((float)(int)this->f_8e /*short **/ * this->f_80 /*float **/) / 2.0;
    fStack_30 = ((float)-(int)this->f_8c /*short **/ * this->f_80 /*float **/) / 2.0;
    uStack_28 = 0;
    uStack_24 = 0x3f800000;
    fStack_20 = ((float)(int)this->f_8c /*short **/ * this->f_80 /*float **/) / 2.0;
    fStack_1c = 0.0;
    uStack_18 = 0;
    uStack_14 = 0x3f800000;
    fStack_c = ((float)(int)this->f_8e /*short **/ * this->f_80 /*float **/) / 2.0;
    fStack_10 = ((float)(int)this->f_8c /*short **/ * this->f_80 /*float **/) / 2.0;
    uStack_8 = 0;
    uStack_4 = 0x3f800000;
    auVar10 = _vmr32(in_vf0);
    auVar11 = _vmr32(auVar10);
    auVar12 = _vmr32(auVar11);
    auStack_190 = _sqc2(in_vf0);
    auStack_1a0 = _sqc2(auVar10);
    auStack_1b0 = _sqc2(auVar11);
    auStack_1c0 = _sqc2(auVar12);
    sceVu0RotMatrixZ(this->f_78 /*u32 **/,auStack_1c0,auStack_1c0);
    sceVu0RotMatrixX(this->f_70 /*u32 **/,auStack_1c0,auStack_1c0);
    sceVu0RotMatrixY(this->f_74 /*u32 **/,auStack_1c0,auStack_1c0);
    RotTransVector(afStack_100,&fStack_80,auStack_1c0,8);
    bVar2 = false;
    for (iVar4 = 0; iVar4 < 4; iVar4 = iVar4 + 1) {
      aiStack_180[iVar4 * 4] =
           (int)((this->f_a4 /*float **/ / 2.0 +
                 this->f_44 /*float **/ + afStack_100[iVar4 * 4]) * 16.0 + 28672.0);
      aiStack_180[iVar4 * 4 + 1] =
           (int)((this->f_48 /*float **/ + afStack_100[iVar4 * 4 + 1]) * 16.0 + 29184.0);
      if ((aiStack_180[iVar4 * 4] < 0) || (0x10000 < aiStack_180[iVar4 * 4])) {
        bVar2 = true;
      }
      if ((aiStack_180[iVar4 * 4 + 1] < 0) || (0x10000 < aiStack_180[iVar4 * 4 + 1])) {
        bVar2 = true;
      }
    }
    for (iVar4 = 4; iVar4 < 8; iVar4 = iVar4 + 1) {
      aiStack_180[iVar4 * 4] =
           (int)(((this->f_44 /*float **/ + afStack_100[iVar4 * 4]) -
                 this->f_a4 /*float **/ / 2.0) * 16.0 + 28672.0);
      aiStack_180[iVar4 * 4 + 1] =
           (int)((this->f_48 /*float **/ + afStack_100[iVar4 * 4 + 1]) * 16.0 + 29184.0);
      if ((aiStack_180[iVar4 * 4] < 0) || (0x10000 < aiStack_180[iVar4 * 4])) {
        bVar2 = true;
      }
      if ((aiStack_180[iVar4 * 4 + 1] < 0) || (0x10000 < aiStack_180[iVar4 * 4 + 1])) {
        bVar2 = true;
      }
    }
  }
  else {
    fStack_7c = ((float)-(int)this->f_8e /*short **/ * this->f_80 /*float **/) / 2.0;
    fStack_80 = ((float)-(int)this->f_8c /*short **/ * this->f_80 /*float **/) / 2.0;
    uStack_78 = 0;
    uStack_74 = 0x3f800000;
    fStack_6c = ((float)(int)this->f_8e /*short **/ * this->f_80 /*float **/) / 2.0;
    fStack_70 = ((float)-(int)this->f_8c /*short **/ * this->f_80 /*float **/) / 2.0;
    uStack_68 = 0;
    uStack_64 = 0x3f800000;
    fStack_5c = ((float)-(int)this->f_8e /*short **/ * this->f_80 /*float **/) / 2.0;
    fStack_60 = ((float)(int)this->f_8c /*short **/ * this->f_80 /*float **/) / 2.0;
    uStack_58 = 0;
    uStack_54 = 0x3f800000;
    fStack_4c = ((float)(int)this->f_8e /*short **/ * this->f_80 /*float **/) / 2.0;
    fStack_50 = ((float)(int)this->f_8c /*short **/ * this->f_80 /*float **/) / 2.0;
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
    sceVu0RotMatrixZ(this->f_78 /*u32 **/,auStack_1c0,auStack_1c0);
    sceVu0RotMatrixX(this->f_70 /*u32 **/,auStack_1c0,auStack_1c0);
    sceVu0RotMatrixY(this->f_74 /*u32 **/,auStack_1c0,auStack_1c0);
    RotTransVector(afStack_100,&fStack_80,auStack_1c0,4);
    bVar2 = false;
    for (iVar4 = 0; iVar4 < 4; iVar4 = iVar4 + 1) {
      aiStack_180[iVar4 * 4] =
           (int)((this->f_44 /*float **/ + afStack_100[iVar4 * 4]) * 16.0 + 28672.0);
      aiStack_180[iVar4 * 4 + 1] =
           (int)((this->f_48 /*float **/ + afStack_100[iVar4 * 4 + 1]) * 16.0 + 29184.0);
      if ((aiStack_180[iVar4 * 4] < 0) || (0x10000 < aiStack_180[iVar4 * 4])) {
        bVar2 = true;
      }
      if ((aiStack_180[iVar4 * 4 + 1] < 0) || (0x10000 < aiStack_180[iVar4 * 4 + 1])) {
        bVar2 = true;
      }
    }
  }
  bVar1 = (this->f_3c /*u8 **/ & 3) == 0;
  uVar9 = (uint)bVar1;
  if (*(int *)(this + uVar9 * 4 + 0x18) == 0) {
    uVar3 = __nwa__FUi(this->f_94 /*int **/ << 4);
    *(u32 *)(this + uVar9 * 4 + 0x18) = uVar3;
  }
  this->f_3c /*u8 **/ = this->f_3c /*u8 **/ & 0xfb | 4;
  puVar8 = *(u32 **)(this + uVar9 * 4 + 0x18);
  if (bVar2) {
    this->f_98 /*u32 **/ = puVar8;
    this->f_3c /*u8 **/ = this->f_3c /*u8 **/ & 0xfc | bVar1;
  }
  else {
    *puVar8 = 0x50000000;
    puVar8[1] = *(u32 *)(DAT_00421c18 + (uint)*(u16 *)(DAT_00421c18 + 10) * 4 + 0xc);
    puVar8[2] = 0;
    puVar8[3] = 0;
    puVar8[4] = this->f_94 /*int **/ + 0xffffffd;
    puVar8[5] = 0;
    puVar8[6] = 0;
    puVar8[7] = this->f_94 /*int **/ + 0x4ffffffd;
    *(u64 *)(puVar8 + 8) = 0x5000000000000001;
    *(u64 *)(puVar8 + 10) = 0xee6ee;
    *(u64 *)(puVar8 + 0xc) = 1;
    *(u64 *)(puVar8 + 0xe) = 0x3f;
    uVar5 = GetTex0__6JRCTexFb(DAT_00421c18,1);
    *(ulong *)(puVar8 + 0x10) = uVar5 & 0xfffffffc0fffff | 0x2000000001300000;
    *(u64 *)(puVar8 + 0x12) = 0x16;
    uVar5 = GetTex0__6JRCTexFb(DAT_00421c18,1);
    *(ulong *)(puVar8 + 0x14) = uVar5 & 0xffffffffffffff | (long)this->f_90 /*int **/ << 0x38;
    *(u64 *)(puVar8 + 0x16) = 0;
    *(u64 *)(puVar8 + 0x18) = 0x23001;
    *(u64 *)(puVar8 + 0x1a) = 0x47;
    *(u64 *)(puVar8 + 0x1c) = 0x44;
    *(u64 *)(puVar8 + 0x1e) = 0x42;
    if (this->f_3e /*short **/ == 0) {
      auVar7._8_8_ = extraout_v0_udw;
      auVar7._0_8_ = 0xa400000000008002;
      auVar12._4_4_ = in_zero_hi;
      auVar12._0_4_ = in_zero_lo;
      auVar12._8_4_ = in_zero_udw;
      auVar12._12_4_ = in_register_0000000c;
      auVar10 = _pcpyld(auVar12,auVar7);
      *(long *)(puVar8 + 0x20) = auVar10._0_8_;
      *(u64 *)(puVar8 + 0x22) = 0x4343c3c310;
      *(u64 *)(puVar8 + 0x24) = 0x154;
      lVar6 = __fixunssfdi(this->f_84 /*u32 **/);
      *(ulong *)(puVar8 + 0x26) = lVar6 << 0x18 | 0x808080;
      *(long *)(puVar8 + 0x28) =
           (long)((int)this->f_88 /*short **/ << 4) |
           (long)((int)this->f_8a /*short **/ << 4) << 0x10;
      *(long *)(puVar8 + 0x2a) = (long)aiStack_180[0] | (long)aiStack_180[1] << 0x10;
      iVar4 = (int)this->f_8e /*short **/;
      if (this->f_8e /*short **/ < 0) {
        iVar4 = iVar4 + 1;
      }
      *(long *)(puVar8 + 0x2c) =
           (long)((int)this->f_88 /*short **/ << 4) |
           (long)(((int)this->f_8a /*short **/ + (iVar4 >> 1)) * 0x10) << 0x10;
      *(long *)(puVar8 + 0x2e) = (long)aiStack_180[4] | (long)iStack_16c << 0x10;
      *(long *)(puVar8 + 0x30) =
           (long)((int)this->f_8a /*short **/ << 4) << 0x10 |
           (long)(((int)this->f_88 /*short **/ + (int)this->f_8c /*short **/) * 0x10);
      *(long *)(puVar8 + 0x32) = (long)iStack_160 | (long)iStack_15c << 0x10;
      iVar4 = (int)this->f_8e /*short **/;
      if (this->f_8e /*short **/ < 0) {
        iVar4 = iVar4 + 1;
      }
      *(long *)(puVar8 + 0x34) =
           (long)(((int)this->f_88 /*short **/ + (int)this->f_8c /*short **/) * 0x10) |
           (long)(((int)this->f_8a /*short **/ + (iVar4 >> 1)) * 0x10) << 0x10;
      *(long *)(puVar8 + 0x36) = (long)iStack_150 | (long)iStack_14c << 0x10;
      *(u64 *)(puVar8 + 0x38) = 0x154;
      lVar6 = __fixunssfdi(this->f_84 /*u32 **/);
      *(ulong *)(puVar8 + 0x3a) = lVar6 << 0x18 | 0x808080;
      iVar4 = (int)this->f_8e /*short **/;
      if (this->f_8e /*short **/ < 0) {
        iVar4 = iVar4 + 1;
      }
      *(long *)(puVar8 + 0x3c) =
           (long)((int)this->f_88 /*short **/ << 4) |
           (long)(((int)this->f_8a /*short **/ + (iVar4 >> 1)) * 0x10) << 0x10;
      *(long *)(puVar8 + 0x3e) = (long)aiStack_140[0] | (long)aiStack_140[1] << 0x10;
      *(long *)(puVar8 + 0x40) =
           (long)((int)this->f_88 /*short **/ << 4) |
           (long)(((int)this->f_8a /*short **/ + (int)this->f_8e /*short **/) * 0x10) <<
           0x10;
      *(long *)(puVar8 + 0x42) = (long)aiStack_140[4] | (long)iStack_12c << 0x10;
      iVar4 = (int)this->f_8e /*short **/;
      if (this->f_8e /*short **/ < 0) {
        iVar4 = iVar4 + 1;
      }
      *(long *)(puVar8 + 0x44) =
           (long)(((int)this->f_88 /*short **/ + (int)this->f_8c /*short **/) * 0x10) |
           (long)(((int)this->f_8a /*short **/ + (iVar4 >> 1)) * 0x10) << 0x10;
      *(long *)(puVar8 + 0x46) = (long)iStack_120 | (long)iStack_11c << 0x10;
      *(long *)(puVar8 + 0x48) =
           (long)(((int)this->f_88 /*short **/ + (int)this->f_8c /*short **/) * 0x10) |
           (long)(((int)this->f_8a /*short **/ + (int)this->f_8e /*short **/) * 0x10) <<
           0x10;
      *(long *)(puVar8 + 0x4a) = (long)iStack_110 | (long)iStack_10c << 0x10;
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
      *(long *)(puVar8 + 0x20) = auVar10._0_8_;
      *(u64 *)(puVar8 + 0x22) = 0x4343c3c310;
      *(u64 *)(puVar8 + 0x24) = 0x154;
      lVar6 = __fixunssfdi(this->f_84 /*u32 **/);
      *(ulong *)(puVar8 + 0x26) = lVar6 << 0x18 | 0x808080;
      *(long *)(puVar8 + 0x28) =
           (long)((int)this->f_88 /*short **/ << 4) |
           (long)((int)this->f_8a /*short **/ << 4) << 0x10;
      *(long *)(puVar8 + 0x2a) = (long)aiStack_180[0] | (long)aiStack_180[1] << 0x10;
      *(long *)(puVar8 + 0x2c) =
           (long)((int)this->f_88 /*short **/ << 4) |
           (long)(((int)this->f_8a /*short **/ + (int)this->f_8e /*short **/) * 0x10) <<
           0x10;
      *(long *)(puVar8 + 0x2e) = (long)aiStack_180[4] | (long)iStack_16c << 0x10;
      *(long *)(puVar8 + 0x30) =
           (long)((int)this->f_8a /*short **/ << 4) << 0x10 |
           (long)(((int)this->f_88 /*short **/ + (int)this->f_8c /*short **/) * 0x10);
      *(long *)(puVar8 + 0x32) = (long)iStack_160 | (long)iStack_15c << 0x10;
      *(long *)(puVar8 + 0x34) =
           (long)(((int)this->f_88 /*short **/ + (int)this->f_8c /*short **/) * 0x10) |
           (long)(((int)this->f_8a /*short **/ + (int)this->f_8e /*short **/) * 0x10) <<
           0x10;
      *(long *)(puVar8 + 0x36) = (long)iStack_150 | (long)iStack_14c << 0x10;
      puVar8 = puVar8 + 0x38;
    }
    this->f_98 /*u32 **/ = puVar8;
    this->f_3c /*u8 **/ = this->f_3c /*u8 **/ & 0xfc | bVar1;
  }
  return;
}

// JP: 0x002fa2c0  @24@getPacket__10ComboTrialFv  size 0x8
// @24@getPacket__10ComboTrialFv
u32 _24_getPacket__10ComboTrialFv(ComboTrial *this)
{
  MakePacket__10ComboTrialFv(this + -0x18);
  return *(u32 *)(this + -0x18 + (this->f_24 /*u8 **/ & 3) * 4 + 0x18);
}

// JP: 0x002fa2d0  @24@__dt__10ComboTrialFv  size 0x8
// @24@__dt__10ComboTrialFv
int * _24___dt__10ComboTrialFv(ComboTrial *this,short param_2)
{
  int *piVar1;
  piVar1 = this + -6;
  if (piVar1 != (int *)0x0) {
    this[-1] = (int)__vt__10ComboTrial;
    this[4] = 0x4067d0;
    this[7] = 0x4067e0;
    if (*this != 0) {
      __dla__FPv(*this);
    }
    if (this[1] != 0) {
      __dla__FPv(this[1]);
    }
    if (piVar1 != (int *)0xffffffd4) {
      this[7] = (int)__vt__17DelayDeleteObject;
    }
    __dt__8VIF1PrimFv(this,0);
    __dt__7CPolObjFv(piVar1,0);
    if (0 < param_2) {
      __dl__FPv(piVar1);
    }
  }
  return piVar1;
}

// JP: 0x002fa2e0  @44@__dt__10ComboTrialFv  size 0x8
// @44@__dt__10ComboTrialFv
int _44___dt__10ComboTrialFv(ComboTrial *this,short param_2)
{
  int iVar1;
  iVar1 = this + -0x2c;
  if (iVar1 != 0) {
    *(u8 **)(this + -0x18) = __vt__10ComboTrial;
    *(u32 *)(this + -4) = 0x4067d0;
    this->f_8 /*u32 **/ = 0x4067e0;
    if (*(int *)(this + -0x14) != 0) {
      __dla__FPv(*(u32 *)(this + -0x14));
    }
    if (*(int *)(this + -0x10) != 0) {
      __dla__FPv(*(u32 *)(this + -0x10));
    }
    if (iVar1 != -0x2c) {
      this->f_8 /*u8 **/ = __vt__17DelayDeleteObject;
    }
    __dt__8VIF1PrimFv(this + -0x14,0);
    __dt__7CPolObjFv(iVar1,0);
    if (0 < param_2) {
      __dl__FPv(iVar1);
    }
  }
  return iVar1;
}
