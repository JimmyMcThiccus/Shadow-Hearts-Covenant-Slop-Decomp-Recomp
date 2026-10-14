// decomp/D/EffectGunya.c — cleaned Ghidra output (SLPM_602.19, Metrowerks MIPS), Shadow Hearts: Covenant JP demo.
// Field accesses are shown as this->T_off (T = u8/u16/u32/f32/i32/p, off = hex offset);
// JRing fields are named from the recovered struct. See notes/D/*.md for layouts.
// CAVEAT: when the base pointer is a float*/int*/short*, the number in `T_off` is an ELEMENT offset (byte offset = off*sizeof(elem)).
// `this` is the C++ this pointer (param_1); the Metrowerks ABI passes it in a0.

// JP: 0x0031d760  __ct__11EffectGunyaFv  =  EffectGunya::EffectGunya
VIF1Prim * EffectGunya::EffectGunya(VIF1Prim *this)

{
  uint uVar1;
  VIF1Prim *pVVar2;
  
  VIF1Prim::VIF1Prim(this);
  DelayDeleteObject::DelayDeleteObject(this + 1);
  FBufTex::FBufTex(&this[1].bFlags,1);
  this->pVptr = EffectGunya::__vt;
  this[1].dwEnv = 0x406b80;
  this[0xd].bFlags = 0x90;
  this[0xd].b_pad0d = 0x6b;
  this[0xd].nZvolume = 0x40;
  _QWD::_QWD(&this[0xbb].dw_unk4);
  pVVar2 = this + 0xbc;
  do {
    _QWD::_QWD(pVVar2);
    pVVar2 = (VIF1Prim *)&pVVar2->pVptr;
  } while (pVVar2 != (VIF1Prim *)&this[0xc0].pVptr);
  uVar1 = __nwa(0x5440);
  this->dw_unk0 = uVar1;
  uVar1 = __nwa(0x5440);
  this->dw_unk4 = uVar1;
  memset((void *)this->dw_unk0,0,0x5440);
  memset((void *)this->dw_unk4,0,0x5440);
  this[0xc1].dw_unk0 = 0;
  this[0xc0].pVptr = (void *)0x0;
  this[0xbb].pVptr = &_align_segment;
  this[0xbb].bFlags = 0x80;
  this[0xbb].b_pad0d = 0;
  this[0xbb].nZvolume = 0;
  this[0xbb].dwEnv = 0x80;
  this[0xbb].dw_unk4 = 0x80;
  EffectGunya::Initialize(this);
  return this;
}

// JP: 0x0031d930  __dt__11EffectGunyaFv  =  EffectGunya::~EffectGunya
int * EffectGunya::~EffectGunya(int *this,short param_2)

{
  int iVar1;
  
  if (this != (int *)0x0) {
    this[4] = (int)EffectGunya::__vt;
    this[7] = 0x406b80;
    this[0x44] = 0x406b90;
    if (*this != 0) {
      __dla(*this);
      *this = 0;
    }
    if (this[1] != 0) {
      __dla(this[1]);
      this[1] = 0;
    }
    if (this[0x3c5] != 0) {
      iVar1 = this[0x3c5];
      if (iVar1 != 0) {
        (**(code **)(iVar1->i32_10 + 8))(iVar1,1);
      }
      this[0x3c5] = 0;
    }
    FBufTex::~FBufTex(this + 8,0);
    DelayDeleteObject::~DelayDeleteObject(this + 5,0);
    VIF1Prim::~VIF1Prim(this,0);
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}

// JP: 0x0031da80  Initialize__11EffectGunyaFv  =  EffectGunya::Initialize
void EffectGunya::Initialize(undefined4 *this)

{
  undefined8 uVar1;
  uint *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  float fVar9;
  uint uVar10;
  float afStack_710 [434];
  undefined4 uStack_48;
  undefined4 uStack_44;
  float fStack_40;
  float fStack_3c;
  undefined4 uStack_38;
  int iStack_34;
  float fStack_30;
  float fStack_2c;
  float fStack_28;
  float fStack_24;
  float fStack_20;
  float fStack_1c;
  float fStack_18;
  float fStack_14;
  undefined4 *puStack_10;
  
  fStack_14 = 340.16467;
  fStack_18 = 0.6630061;
  fStack_1c = 0.17453289;
  puStack_10 = this;
  for (iVar5 = 0; puVar3 = puStack_10, iVar5 < 6; iVar5 = iVar5 + 1) {
    fStack_20 = fStack_14 - (fStack_14 / 6.0) * (float)iVar5;
    fStack_24 = fStack_18 - (fStack_18 / 6.0) * (float)iVar5;
    for (iVar7 = 0; iVar7 < 0x24; iVar7 = iVar7 + 1) {
      fStack_28 = fStack_1c * (float)iVar7;
      fVar9 = cosf(fStack_28);
      afStack_710[iVar5 * 0x48 + iVar7 * 2] = fStack_20 * fVar9;
      fVar9 = sinf(fStack_28);
      afStack_710[iVar5 * 0x48 + iVar7 * 2 + 1] = fStack_20 * fVar9;
      if ((afStack_710[iVar5 * 0x48 + iVar7 * 2] < -256.0) ||
         (256.0 < afStack_710[iVar5 * 0x48 + iVar7 * 2])) {
        fStack_3c = 256.0 / afStack_710[iVar5 * 0x48 + iVar7 * 2];
        if (fStack_3c < 0.0) {
          fStack_3c = -fStack_3c;
        }
        fStack_2c = fStack_3c;
        afStack_710[iVar5 * 0x48 + iVar7 * 2] = afStack_710[iVar5 * 0x48 + iVar7 * 2] * fStack_3c;
        afStack_710[iVar5 * 0x48 + iVar7 * 2 + 1] =
             afStack_710[iVar5 * 0x48 + iVar7 * 2 + 1] * fStack_3c;
        fVar9 = cosf(fStack_28);
        puStack_10[iVar5 * 0x90 + iVar7 * 4 + 0x48] = fStack_2c * fStack_24 * fVar9;
        fVar9 = sinf(fStack_28);
        puStack_10[iVar5 * 0x90 + iVar7 * 4 + 0x49] = fStack_2c * fStack_24 * fVar9;
      }
      else if ((afStack_710[iVar5 * 0x48 + iVar7 * 2 + 1] < -224.0) ||
              (224.0 < afStack_710[iVar5 * 0x48 + iVar7 * 2 + 1])) {
        fStack_40 = 224.0 / afStack_710[iVar5 * 0x48 + iVar7 * 2 + 1];
        if (fStack_40 < 0.0) {
          fStack_40 = -fStack_40;
        }
        fStack_30 = fStack_40;
        afStack_710[iVar5 * 0x48 + iVar7 * 2] = afStack_710[iVar5 * 0x48 + iVar7 * 2] * fStack_40;
        afStack_710[iVar5 * 0x48 + iVar7 * 2 + 1] =
             afStack_710[iVar5 * 0x48 + iVar7 * 2 + 1] * fStack_40;
        fVar9 = cosf(fStack_28);
        puStack_10[iVar5 * 0x90 + iVar7 * 4 + 0x48] = fStack_30 * fStack_24 * fVar9;
        fVar9 = sinf(fStack_28);
        puStack_10[iVar5 * 0x90 + iVar7 * 4 + 0x49] = fStack_30 * fStack_24 * fVar9;
      }
      else {
        fVar9 = cosf(fStack_28);
        puStack_10[iVar5 * 0x90 + iVar7 * 4 + 0x48] = fStack_24 * fVar9;
        fVar9 = sinf(fStack_28);
        puStack_10[iVar5 * 0x90 + iVar7 * 4 + 0x49] = fStack_24 * fVar9;
      }
    }
  }
  puVar4 = puStack_10 + 0x3ac;
  memset(puVar4,0,0x60);
  *puVar4 = 0x60000005;
  puVar3[0x3ae] = 0x13000000;
  puVar3[0x3af] = 0x50000005;
  puVar3->u64_3b0 = 0x1000000000000004;
  puVar3->u64_3b2 = 0xe;
  puVar3->u64_3b4 = 0x33001;
  puVar3->u64_3b6 = 0x47;
  puVar3->u64_3b8 = 1;
  puVar3->u64_3ba = 0x14;
  puVar3->u64_3bc = 5;
  puVar3->u64_3be = 8;
  puVar3->u64_3c0 = 0x44;
  puVar3->u64_3c2 = 0x42;
  puVar3 = (undefined4 *)*puStack_10;
  iVar5 = puStack_10[1];
  *puVar3 = 0x50000000;
  puVar3[1] = puStack_10 + 0x3ac;
  _QWD::__as(iVar5,puVar3);
  puVar3[4] = 0x50000000;
  iVar5->u32_10 = 0x50000000;
  puVar3 = puVar3 + 8;
  puVar4 = (undefined4 *)(iVar5 + 0x20);
  iStack_34 = 0;
  uStack_38 = 0;
  for (iVar5 = 0; iVar7 = iStack_34, iVar5 < 6; iVar5 = iVar5 + 1) {
    *puVar3 = &DAT_100000df;
    puVar3[3] = 0x500000df;
    _QWD::__as(puVar4,puVar3);
    puVar3->u64_4 = 0x300a40000000804a;
    puVar3->u64_6 = 0x512;
    _QWD::__as(puVar4 + 4,puVar3 + 4);
    puVar3 = puVar3 + 0xc;
    puVar4 = puVar4 + 0xc;
    iVar6 = iVar7;
    for (iVar8 = 0; iVar8 < 0x25; iVar8 = iVar8 + 1) {
      uVar1 = _QWD::__as(puVar4,puStack_10 + 0x3a8);
      _QWD::__as(puVar3,uVar1);
      fVar9 = (afStack_710[iVar5 * 0x48 + iVar7 * 2] + 2048.0) * 16.0;
      if (fVar9 < 2.1474836e+09) {
        uVar10 = (uint)fVar9;
      }
      else {
        uVar10 = (int)(fVar9 - 2.1474836e+09) | 0x80000000;
      }
      puVar3[4] = uVar10;
      fVar9 = (afStack_710[iVar5 * 0x48 + iVar7 * 2 + 1] + 2048.0) * 16.0;
      if (fVar9 < 2.1474836e+09) {
        uVar10 = (uint)fVar9;
      }
      else {
        uVar10 = (int)(fVar9 - 2.1474836e+09) | 0x80000000;
      }
      puVar3[5] = uVar10;
      puVar3[6] = 0;
      if (iVar8 == 0) {
        uStack_44 = 0x8000;
      }
      else {
        uStack_44 = 0;
      }
      puVar3[7] = uStack_44;
      _QWD::__as(puVar4 + 4,puVar3 + 4);
      uVar1 = _QWD::__as(puVar4 + 0xc,puStack_10 + 0x3a8);
      _QWD::__as(puVar3 + 0xc,uVar1);
      puVar2 = puVar3 + 0x10;
      if (iVar5 == 5) {
        *puVar2 = 0x8000;
        puVar3[0x11] = 0x8000;
      }
      else {
        fVar9 = (afStack_710[(iVar5 + 1) * 0x48 + iVar6 * 2] + 2048.0) * 16.0;
        if (fVar9 < 2.1474836e+09) {
          uVar10 = (uint)fVar9;
        }
        else {
          uVar10 = (int)(fVar9 - 2.1474836e+09) | 0x80000000;
        }
        *puVar2 = uVar10;
        fVar9 = (afStack_710[(iVar5 + 1) * 0x48 + iVar6 * 2 + 1] + 2048.0) * 16.0;
        if (fVar9 < 2.1474836e+09) {
          uVar10 = (uint)fVar9;
        }
        else {
          uVar10 = (int)(fVar9 - 2.1474836e+09) | 0x80000000;
        }
        puVar3[0x11] = uVar10;
      }
      puVar3[0x12] = 0;
      if (iVar8 == 0) {
        uStack_48 = 0x8000;
      }
      else {
        uStack_48 = 0;
      }
      puVar3[0x13] = uStack_48;
      _QWD::__as(puVar4 + 0x10,puVar2);
      puVar3 = puVar3 + 0x18;
      puVar4 = puVar4 + 0x18;
      iVar7 = iVar7 + 1;
      iVar6 = iVar6 + 1;
      if (0x23 < iVar7) {
        iVar7 = 0;
      }
      if (0x23 < iVar6) {
        iVar6 = 0;
      }
    }
    puVar3 = puVar3 + -4;
    puVar4 = puVar4 + -4;
  }
  *puVar3 = 0x60000000;
  *puVar4 = 0x60000000;
  return;
}

// JP: 0x0031e4e0  getPacket__11EffectGunyaFv  =  EffectGunya::getPacket
undefined4 EffectGunya::getPacket(int this)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined1 auStack_d0 [16];
  undefined1 auStack_c0 [16];
  undefined1 auStack_b0 [16];
  undefined1 auStack_a0 [48];
  undefined4 uStack_70;
  undefined4 uStack_6c;
  undefined1 auStack_60 [48];
  undefined4 uStack_30;
  undefined4 uStack_2c;
  float fStack_1c;
  float fStack_18;
  float fStack_14;
  int iStack_10;
  
  iVar3 = *(int *)(this + (VIF1Prim::m_Env & 1) * 4);
  iStack_10 = this;
  uVar1 = FBufTex::getFBTexPacket(this + 0x20);
  iVar3->u32_14 = uVar1;
  iVar3 = *(int *)(iStack_10 + (VIF1Prim::m_Env & 1) * 4) + 0x40;
  if (iStack_10->i32_f14 == 0) {
    fStack_1c = 0.0;
  }
  else {
    fStack_1c = (float)GunyaKey::GetMiddle
                                 (iStack_10->u32_f10,
                                  iStack_10->u32_f14);
  }
  fStack_14 = fStack_1c;
  for (iVar5 = 0; iVar5 < 6; iVar5 = iVar5 + 1) {
    iVar7 = 0;
    iVar6 = 0;
    Matrix::Matrix(auStack_60);
    Matrix::Matrix(auStack_a0);
    FVector::FVector(auStack_b0);
    fStack_18 = fStack_14 * (float)iVar5;
    if (3.141592 < fStack_18) {
      fStack_18 = fStack_18 - 6.283184;
    }
    if (fStack_18 < -3.141592) {
      fStack_18 = fStack_18 + 6.283184;
    }
    Matrix::RotZMatrix(fStack_18,auStack_60);
    uStack_30 = 0x3eff8000;
    uStack_2c = 0x3edf8000;
    fStack_18 = fStack_14 * (float)(iVar5 + 1);
    if (3.141592 < fStack_18) {
      fStack_18 = fStack_18 - 6.283184;
    }
    if (fStack_18 < -3.141592) {
      fStack_18 = fStack_18 + 6.283184;
    }
    Matrix::RotZMatrix(fStack_18,auStack_a0);
    uStack_70 = 0x3eff8000;
    uStack_6c = 0x3edf8000;
    for (iVar8 = 0; iVar8 < 0x25; iVar8 = iVar8 + 1) {
      uVar1 = *(undefined4 *)(iStack_10 + iVar5 * 0x240 + iVar7 * 0x10 + 0x120);
      puVar2 = (undefined4 *)FVector::vx(auStack_b0);
      *puVar2 = uVar1;
      uVar1 = *(undefined4 *)(iStack_10 + iVar5 * 0x240 + iVar7 * 0x10 + 0x124);
      puVar2 = (undefined4 *)FVector::vy(auStack_b0);
      *puVar2 = uVar1;
      puVar2 = (undefined4 *)FVector::vz(auStack_b0);
      *puVar2 = 0;
      puVar2 = (undefined4 *)FVector::vw(auStack_b0);
      *puVar2 = 0x3f800000;
      Matrix::ApplyMatrix(auStack_c0,auStack_60,auStack_b0);
      FVector::__as(auStack_b0,auStack_c0);
      EffectGunya::ClumpSt(iStack_10,auStack_b0);
      puVar2 = (undefined4 *)FVector::vx(auStack_b0);
      uVar1 = *puVar2;
      puVar2 = (undefined4 *)FVector::vx(iVar3);
      *puVar2 = uVar1;
      puVar2 = (undefined4 *)FVector::vy(auStack_b0);
      uVar1 = *puVar2;
      puVar2 = (undefined4 *)FVector::vy(iVar3);
      *puVar2 = uVar1;
      puVar2 = (undefined4 *)FVector::vz(iVar3);
      *puVar2 = 0x3f800000;
      iVar4 = iVar3 + 0x30;
      if (iVar5 == 5) {
        puVar2 = (undefined4 *)FVector::vx(iVar4);
        *puVar2 = 0x3eff8000;
        puVar2 = (undefined4 *)FVector::vy(iVar4);
        *puVar2 = 0x3edf8000;
      }
      else {
        uVar1 = *(undefined4 *)(iStack_10 + (iVar5 + 1) * 0x240 + iVar6 * 0x10 + 0x120);
        puVar2 = (undefined4 *)FVector::vx(auStack_b0);
        *puVar2 = uVar1;
        uVar1 = *(undefined4 *)(iStack_10 + (iVar5 + 1) * 0x240 + iVar6 * 0x10 + 0x124);
        puVar2 = (undefined4 *)FVector::vy(auStack_b0);
        *puVar2 = uVar1;
        puVar2 = (undefined4 *)FVector::vz(auStack_b0);
        *puVar2 = 0;
        puVar2 = (undefined4 *)FVector::vw(auStack_b0);
        *puVar2 = 0x3f800000;
        Matrix::ApplyMatrix(auStack_d0,auStack_a0,auStack_b0);
        FVector::__as(auStack_b0,auStack_d0);
        EffectGunya::ClumpSt(iStack_10,auStack_b0);
        puVar2 = (undefined4 *)FVector::vx(auStack_b0);
        uVar1 = *puVar2;
        puVar2 = (undefined4 *)FVector::vx(iVar4);
        *puVar2 = uVar1;
        puVar2 = (undefined4 *)FVector::vy(auStack_b0);
        uVar1 = *puVar2;
        puVar2 = (undefined4 *)FVector::vy(iVar4);
        *puVar2 = uVar1;
      }
      puVar2 = (undefined4 *)FVector::vz(iVar4);
      *puVar2 = 0x3f800000;
      iVar3 = iVar3 + 0x60;
      iVar7 = iVar7 + 1;
      iVar6 = iVar6 + 1;
      if (0x23 < iVar7) {
        iVar7 = 0;
      }
      if (0x23 < iVar6) {
        iVar6 = 0;
      }
    }
    iVar3 = iVar3 + 0x20;
  }
  return *(undefined4 *)(iStack_10 + (VIF1Prim::m_Env & 1) * 4);
}

// JP: 0x0031eac0  ClumpSt__11EffectGunyaFP7FVector  =  EffectGunya::ClumpSt
void EffectGunya::ClumpSt(undefined8 this,undefined4 param_2)

{
  float *pfVar1;
  float fVar2;
  float fVar3;
  
  pfVar1 = (float *)FVector::vx(param_2);
  if (*pfVar1 < 0.0) {
    pfVar1 = (float *)FVector::vx(param_2);
    *pfVar1 = *pfVar1 - 0.49902344;
    pfVar1 = (float *)FVector::vy(param_2);
    *pfVar1 = *pfVar1 - 0.43652344;
    pfVar1 = (float *)FVector::vx(param_2);
    fVar2 = *pfVar1;
    pfVar1 = (float *)FVector::vx(param_2);
    fVar3 = *pfVar1;
    pfVar1 = (float *)FVector::vx(param_2);
    *pfVar1 = (-0.49902344 / fVar2) * fVar3 + 0.49902344;
    pfVar1 = (float *)FVector::vy(param_2);
    fVar3 = *pfVar1;
    pfVar1 = (float *)FVector::vy(param_2);
    *pfVar1 = (-0.49902344 / fVar2) * fVar3 + 0.43652344;
  }
  pfVar1 = (float *)FVector::vx(param_2);
  if (1.0 < *pfVar1) {
    pfVar1 = (float *)FVector::vx(param_2);
    *pfVar1 = *pfVar1 - 0.49902344;
    pfVar1 = (float *)FVector::vy(param_2);
    *pfVar1 = *pfVar1 - 0.43652344;
    pfVar1 = (float *)FVector::vx(param_2);
    fVar2 = *pfVar1;
    pfVar1 = (float *)FVector::vx(param_2);
    fVar3 = *pfVar1;
    pfVar1 = (float *)FVector::vx(param_2);
    *pfVar1 = (0.49902344 / fVar2) * fVar3 + 0.49902344;
    pfVar1 = (float *)FVector::vy(param_2);
    fVar3 = *pfVar1;
    pfVar1 = (float *)FVector::vy(param_2);
    *pfVar1 = (0.49902344 / fVar2) * fVar3 + 0.43652344;
  }
  pfVar1 = (float *)FVector::vy(param_2);
  if (*pfVar1 < 0.0) {
    pfVar1 = (float *)FVector::vx(param_2);
    *pfVar1 = *pfVar1 - 0.49902344;
    pfVar1 = (float *)FVector::vy(param_2);
    *pfVar1 = *pfVar1 - 0.43652344;
    pfVar1 = (float *)FVector::vy(param_2);
    fVar2 = *pfVar1;
    pfVar1 = (float *)FVector::vx(param_2);
    fVar3 = *pfVar1;
    pfVar1 = (float *)FVector::vx(param_2);
    *pfVar1 = (-0.43652344 / fVar2) * fVar3 + 0.49902344;
    pfVar1 = (float *)FVector::vy(param_2);
    fVar3 = *pfVar1;
    pfVar1 = (float *)FVector::vy(param_2);
    *pfVar1 = (-0.43652344 / fVar2) * fVar3 + 0.43652344;
  }
  pfVar1 = (float *)FVector::vy(param_2);
  if (0.8730469 < *pfVar1) {
    pfVar1 = (float *)FVector::vx(param_2);
    *pfVar1 = *pfVar1 - 0.49902344;
    pfVar1 = (float *)FVector::vy(param_2);
    *pfVar1 = *pfVar1 - 0.43652344;
    pfVar1 = (float *)FVector::vy(param_2);
    fVar2 = *pfVar1;
    pfVar1 = (float *)FVector::vx(param_2);
    fVar3 = *pfVar1;
    pfVar1 = (float *)FVector::vx(param_2);
    *pfVar1 = (0.43652344 / fVar2) * fVar3 + 0.49902344;
    pfVar1 = (float *)FVector::vy(param_2);
    fVar3 = *pfVar1;
    pfVar1 = (float *)FVector::vy(param_2);
    *pfVar1 = (0.43652344 / fVar2) * fVar3 + 0.43652344;
  }
  return;
}

// JP: 0x0031ef50  AddTime__11EffectGunyaFf  =  EffectGunya::AddTime
void EffectGunya::AddTime(float this,int param_2)

{
  param_2->f32_f10 = param_2->f32_f10 + this;
  return;
}

// JP: 0x0031ef80  AddRotKey__11EffectGunyaFff  =  EffectGunya::AddRotKey
void EffectGunya::AddRotKey(undefined4 this,undefined4 param_2,int param_3)

{
  long lVar1;
  undefined8 uVar2;
  
  lVar1 = __nw(0x14);
  uVar2 = 0;
  if (lVar1 != 0) {
    uVar2 = GunyaKey::GunyaKey(this,param_2,lVar1);
  }
  if (param_3->i32_f14 == 0) {
    param_3->i32_f14 = (int)uVar2;
  }
  else {
    GunyaKey::AddKey(param_3->u32_f14,uVar2);
  }
  return;
}
