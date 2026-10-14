// decomp/D/Fp.c — cleaned Ghidra output (SLPM_602.19, Metrowerks MIPS), Shadow Hearts: Covenant JP demo.
// Field accesses are shown as this->T_off (T = u8/u16/u32/f32/i32/p, off = hex offset);
// JRing fields are named from the recovered struct. See notes/D/*.md for layouts.
// CAVEAT: when the base pointer is a float*/int*/short*, the number in `T_off` is an ELEMENT offset (byte offset = off*sizeof(elem)).
// `this` is the C++ this pointer (param_1); the Metrowerks ABI passes it in a0.

// JP: 0x00298b60  __ct__5FpFogFv  =  FpFog::FpFog
undefined8 FpFog::FpFog(undefined8 this)

{
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  int this;
  
  FpPrim::FpPrim(this);
  
  *(undefined1 **)(this + 0x10) = FpFog::__vt;
  this->u32_1c = 0x405d30;
  this->u32_70 = in_zero_lo;
  this->u32_74 = in_zero_hi;
  this->u32_78 = in_zero_udw;
  this->u32_7c = in_register_0000000c;
  this->u32_80 = in_zero_lo;
  this->u32_84 = in_zero_hi;
  this->u32_88 = in_zero_udw;
  this->u32_8c = in_register_0000000c;
  this->u32_90 = in_zero_lo;
  this->u32_94 = in_zero_hi;
  this->u32_98 = in_zero_udw;
  this->u32_9c = in_register_0000000c;
  this->u32_a0 = in_zero_lo;
  this->u32_a4 = in_zero_hi;
  this->u32_a8 = in_zero_udw;
  this->u32_ac = in_register_0000000c;
  this->u32_70 = 0;
  this->u32_74 = 0;
  this->u32_78 = 0;
  this->u32_7c = 0;
  this->u32_80 = 0;
  this->u32_84 = 0;
  this->u32_88 = 0;
  this->u32_8c = 0;
  this->u32_90 = 0;
  this->u32_94 = 0;
  this->u32_98 = 0;
  this->u32_9c = 0;
  this->u32_a0 = 0;
  this->u32_a4 = 0;
  this->u32_a8 = 0;
  this->u32_ac = 0;
  this->u32_b0 = 0;
  this->u32_b4 = 0;
  this->u32_b8 = 0;
  this->u32_bc = 0;
  this->u32_c0 = 0;
  this->u32_c4 = 0;
  this->u32_c8 = 0;
  this->u32_cc = 0;
  return this;
}

// JP: 0x00298d10  __dt__5FpFogFv  =  FpFog::~FpFog
int FpFog::~FpFog(int this,short param_2)

{
  if (this != 0) {
    *(undefined1 **)(this + 0x10) = FpFog::__vt;
    this->u32_1c = 0x405d30;
    FpPrim::~FpPrim(this,0);
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}

// JP: 0x00298da0  Create__5FpFogF7FVector7FVector7FVector7FVectorfffiifff  =  FpFog::Create
void FpFog::Create
               (undefined4 this,undefined4 param_2,undefined4 param_3,undefined4 param_4,
               undefined4 param_5,undefined4 param_6,undefined8 param_7,undefined8 *param_8,
               undefined8 *param_9,undefined8 *param_10,undefined8 *param_11,undefined4 param_12,
               undefined4 param_13)

{
  long lVar1;
  undefined8 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  
  iVar6 = (int)param_7;
  uVar2 = *param_8;
  uVar3 = param_8->u32_1;
  uVar4 = *(undefined4 *)((int)param_8 + 0xc);
  iVar6->i32_70 = (int)uVar2;
  iVar6->i32_74 = (int)((ulong)uVar2 >> 0x20);
  iVar6->u32_78 = uVar3;
  iVar6->u32_7c = uVar4;
  uVar2 = *param_9;
  uVar3 = param_9->u32_1;
  uVar4 = *(undefined4 *)((int)param_9 + 0xc);
  iVar6->i32_80 = (int)uVar2;
  iVar6->i32_84 = (int)((ulong)uVar2 >> 0x20);
  iVar6->u32_88 = uVar3;
  iVar6->u32_8c = uVar4;
  uVar2 = *param_10;
  uVar3 = param_10->u32_1;
  uVar4 = *(undefined4 *)((int)param_10 + 0xc);
  iVar6->i32_90 = (int)uVar2;
  iVar6->i32_94 = (int)((ulong)uVar2 >> 0x20);
  iVar6->u32_98 = uVar3;
  iVar6->u32_9c = uVar4;
  uVar2 = *param_11;
  uVar3 = param_11->u32_1;
  uVar4 = *(undefined4 *)((int)param_11 + 0xc);
  iVar6->i32_a0 = (int)uVar2;
  iVar6->i32_a4 = (int)((ulong)uVar2 >> 0x20);
  iVar6->u32_a8 = uVar3;
  iVar6->u32_ac = uVar4;
  iVar6->u32_b0 = this;
  iVar6->u32_b4 = param_2;
  iVar6->u32_b8 = param_3;
  iVar6->u32_bc = param_12;
  iVar6->u32_c0 = param_13;
  iVar6->u32_c4 = param_4;
  iVar6->u32_c8 = param_5;
  iVar6->u32_cc = param_6;
  if (iVar6->f32_90 < 0.0) {
    iVar6->u32_90 = 0;
  }
  else if (2.0 < iVar6->f32_90) {
    iVar6->u32_90 = 0x40000000;
  }
  if (iVar6->f32_94 < 0.0) {
    iVar6->u32_94 = 0;
  }
  else if (2.0 < iVar6->f32_94) {
    iVar6->u32_94 = 0x40000000;
  }
  if (iVar6->f32_98 < 0.0) {
    iVar6->u32_98 = 0;
  }
  else if (2.0 < iVar6->f32_98) {
    iVar6->u32_98 = 0x40000000;
  }
  iVar5 = BgEffectMan::eff->i32_1c + 0x8c;
  SetWhiteTex(iVar5);
  PutiPrim::SetTexture(param_7,iVar5,1);
  if (iVar6->i8_58 == '\0') {
    iVar6->u8_24 = iVar6->u8_24 & 0xfe | 1;
  }
  iVar5 = iVar6->i32_c0;
  lVar1 = __nw(0x210);
  uVar2 = 0;
  if (lVar1 != 0) {
    uVar2 = FpObjectFog::FpObjectFog(lVar1,iVar5 * 0xc + 0x14,0);
  }
  PutiPrim::AddObject(param_7,uVar2);
  iVar5 = (int)uVar2;
  (**(code **)(iVar5->i32_1e4 + 0x40))
            (uVar2,iVar6->u32_c0,iVar6->u8_58);
  iVar5->u16_14 = iVar5->u16_14 & 0xe01f | 0x20;
  PutiManager::AddPrim(BgEffectMan::eff,iVar6->u32_54,param_7);
  return;
}

// JP: 0x00299040  Create__5FpFogFPv  =  FpFog::Create
void FpFog::Create(undefined4 this,undefined4 *param_2)

{
  undefined2 *puVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  float fVar6;
  float fVar7;
  undefined1 auStack_d0 [16];
  undefined1 auStack_c0 [16];
  undefined1 auStack_b0 [16];
  undefined1 auStack_a0 [16];
  undefined1 auStack_90 [16];
  undefined1 auStack_80 [16];
  undefined1 auStack_70 [16];
  undefined1 auStack_60 [28];
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined2 uStack_28;
  undefined2 uStack_26;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 *puStack_10;
  
  uStack_24 = *param_2;
  uStack_20 = this;
  puStack_10 = param_2;
  puVar1 = (undefined2 *)FpPrim::InitFpFlag(uStack_24,this);
  uStack_28 = *puVar1;
  uStack_26 = puVar1[1];
  memset(&uStack_2c,0,4);
  uStack_2c = param_2[4];
  FVector::FVector(auStack_60,param_2 + 8);
  FVector::FVector(auStack_70,param_2 + 0xc);
  uStack_30 = param_2[0x10];
  uStack_34 = param_2[0x11];
  FVector::FVector(auStack_80,param_2 + 0x14);
  uStack_38 = param_2[0x18];
  uStack_3c = param_2[0x19];
  fVar6 = (float)param_2[0x1a];
  fVar7 = (float)param_2[0x1b];
  uStack_40 = param_2[0x1c];
  uStack_44 = param_2[0x1d];
  FVector::FVector(auStack_90,param_2 + 0x20);
  uVar2 = FVector::FVector(auStack_a0,auStack_60);
  uVar3 = FVector::FVector(auStack_b0,auStack_80);
  uVar4 = FVector::FVector(auStack_c0,auStack_90);
  uVar5 = FVector::FVector(auStack_d0,auStack_70);
  FpFog::Create
            (uStack_38,uStack_3c,uStack_40,uStack_30,uStack_34,uStack_44,uStack_20,uVar2,uVar3,uVar4
             ,uVar5,(int)fVar6,(int)fVar7);
  return;
}

// JP: 0x00299220  __ct__11FpObjectFogFiPv  =  FpObjectFog::FpObjectFog
int FpObjectFog::FpObjectFog(int this,undefined4 param_2,undefined4 param_3)

{
  FpObject::FpObject(this,param_2,param_3);
  *(undefined1 **)(this + 0x1e4) = FpObjectFog::__vt;
  return this;
}

// JP: 0x00299270  __dt__11FpObjectFogFv  =  FpObjectFog::~FpObjectFog
int FpObjectFog::~FpObjectFog(int this,short param_2)

{
  if (this != 0) {
    *(undefined1 **)(this + 0x1e4) = FpObjectFog::__vt;
    FpObject::~FpObject(this,0);
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}

// JP: 0x002992f0  CreateData__11FpObjectFogFib  =  FpObjectFog::CreateData
void FpObjectFog::CreateData(int this,int param_2,long param_3)

{
  int iVar1;
  undefined8 uVar2;
  int iVar3;
  int iVar4;
  float fVar5;
  float fVar6;
  float *pfVar7;
  undefined4 uVar8;
  float fVar9;
  undefined1 in_vf0 [16];
  undefined1 auVar10 [16];
  undefined1 auVar11 [16];
  undefined1 auVar12 [16];
  undefined1 auStack_c0 [16];
  undefined1 auStack_b0 [8];
  float fStack_a8;
  float fStack_a4;
  undefined8 uStack_a0;
  undefined4 uStack_98;
  undefined4 uStack_94;
  undefined4 uStack_90;
  undefined4 uStack_8c;
  undefined4 uStack_88;
  undefined4 uStack_84;
  undefined4 uStack_80;
  undefined4 uStack_7c;
  undefined4 uStack_78;
  undefined4 uStack_74;
  float fStack_70;
  float fStack_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined1 auStack_50 [16];
  undefined1 auStack_40 [16];
  undefined1 auStack_30 [16];
  undefined1 auStack_20 [16];
  float fStack_10;
  float fStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  iVar1 = this->i32_8;
  pfVar7 = (float *)(this->i32_1fc + param_2 * 0xf0);
  if (param_3 == 0) {
    pfVar7[1] = 0.0;
  }
  else {
    iVar3 = rand();
    fVar9 = (1.0 - iVar1->f32_90) +
            (iVar1->f32_90 * (float)iVar3) / 2.1474836e+09;
    rand();
    rand();
    *pfVar7 = (float)iVar1->i32_bc;
    iVar3 = rand();
    pfVar7[1] = *pfVar7 * (1.0 - (float)iVar3 / 2.1474836e+09);
    pfVar7[2] = 0.0;
    uVar2 = iVar1->u64_80;
    fVar5 = iVar1->f32_88;
    fVar6 = iVar1->f32_8c;
    pfVar7[4] = (float)uVar2;
    pfVar7[5] = (float)((ulong)uVar2 >> 0x20);
    pfVar7[6] = fVar5;
    pfVar7[7] = fVar6;
    pfVar7[4] = pfVar7[4] * fVar9;
    pfVar7[5] = pfVar7[5] * fVar9;
    pfVar7[6] = pfVar7[6] * fVar9;
    uStack_60 = 0;
    uStack_5c = 0;
    uStack_58 = 0;
    uStack_54 = 0x3f800000;
    pfVar7[8] = 0.0;
    pfVar7[9] = 0.0;
    pfVar7[10] = 0.0;
    pfVar7[0xb] = 1.0;
    fStack_6c = iVar1->f32_b4;
    fStack_70 = iVar1->f32_b0;
    uStack_68 = 0;
    uStack_64 = 0x3f800000;
    pfVar7[0x10] = fStack_70;
    pfVar7[0x11] = fStack_6c;
    pfVar7[0x12] = 0.0;
    pfVar7[0x13] = 1.0;
    uStack_80 = 0;
    uStack_7c = 0;
    uStack_78 = 0;
    uStack_74 = 0x3f800000;
    pfVar7[0x18] = 0.0;
    pfVar7[0x19] = 0.0;
    pfVar7[0x1a] = 0.0;
    pfVar7[0x1b] = 1.0;
    uVar2 = iVar1->u64_a0;
    fVar5 = iVar1->f32_a8;
    fVar6 = iVar1->f32_ac;
    pfVar7[0x2c] = (float)uVar2;
    pfVar7[0x2d] = (float)((ulong)uVar2 >> 0x20);
    pfVar7[0x2e] = fVar5;
    pfVar7[0x2f] = fVar6;
    pfVar7[0x30] = 0.0;
    pfVar7[0x31] = 0.0;
    pfVar7[0x32] = 0.0;
    pfVar7[0x33] = 1.0;
    pfVar7[0x34] = 1.0;
    pfVar7[0x35] = 0.0;
    pfVar7[0x36] = 1.0;
    pfVar7[0x37] = 1.0;
  }
  pfVar7[0x2f] = 0.0;
  uStack_90 = 0x3f800000;
  uStack_8c = 0x3f800000;
  uStack_88 = 0x3f800000;
  uStack_84 = 0x3f800000;
  pfVar7[0x14] = 1.0;
  pfVar7[0x15] = 1.0;
  pfVar7[0x16] = 1.0;
  pfVar7[0x17] = 1.0;
  iVar3 = rand();
  fVar5 = iVar1->f32_cc;
  iVar4 = rand();
  fStack_10 = pfVar7[0x10] * 0.15 + (iVar1->f32_b8 * (float)iVar4) / 2.1474836e+09;
  uStack_8 = 0;
  uStack_4 = 0x3f800000;
  auVar10 = _vmr32(in_vf0);
  auVar11 = _vmr32(auVar10);
  auVar12 = _vmr32(auVar11);
  auStack_20 = _sqc2(in_vf0);
  auStack_30 = _sqc2(auVar10);
  auStack_40 = _sqc2(auVar11);
  auStack_50 = _sqc2(auVar12);
  fStack_c = (-fVar5 * (float)iVar3) / 2.1474836e+09;
  uVar8 = GetRad((float)param_2 * (360.0 / (float)this->i32_1f8));
  sceVu0RotMatrixY(uVar8,auStack_50,auStack_50);
  if (iVar1->f32_c4 != 0.0) {
    uVar8 = GetRad(iVar1->u32_c4);
    sceVu0RotMatrixX(uVar8,auStack_50,auStack_50);
  }
  if (iVar1->f32_c8 != 0.0) {
    uVar8 = GetRad(iVar1->u32_c8);
    sceVu0RotMatrixY(uVar8,auStack_50,auStack_50);
  }
  Matrix::ApplyMatrix(&uStack_a0,auStack_50,&fStack_10);
  fStack_10 = (float)uStack_a0;
  fStack_c = (float)((ulong)uStack_a0 >> 0x20);
  uStack_8 = uStack_98;
  uStack_4 = uStack_94;
  auVar10._8_4_ = uStack_98;
  auVar10._0_8_ = uStack_a0;
  auVar10._12_4_ = uStack_94;
  auVar10 = _lqc2(auVar10);
  auVar11 = _lqc2(*(undefined1 (*) [16])(iVar1 + 0x70));
  auVar10 = _vadd(auVar10,auVar11);
  auStack_c0 = _sqc2(auVar10);
  FVector::FVector(auStack_b0,auStack_c0);
  pfVar7[0xc] = auStack_b0._0_4_;
  pfVar7[0xd] = auStack_b0._4_4_;
  pfVar7[0xe] = fStack_a8;
  pfVar7[0xf] = fStack_a4;
  return;
}

// JP: 0x00299850  Init__11FpObjectFogFib  =  FpObjectFog::Init
void FpObjectFog::Init(undefined8 this,undefined4 param_2,long param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined4 uVar5;
  undefined1 (*pauVar6) [16];
  int iVar7;
  int this;
  float fVar9;
  undefined1 auVar10 [16];
  undefined1 auVar11 [16];
  undefined1 auStack_70 [16];
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined1 auStack_50 [16];
  undefined1 auStack_40 [16];
  undefined1 auStack_30 [16];
  undefined1 auStack_20 [4];
  float fStack_1c;
  float fStack_10;
  float fStack_c;
  float fStack_8;
  undefined4 uStack_4;
  
  
  this->u32_1f8 = param_2;
  this->u32_1f4 = param_2;
  iVar1 = this->i32_1f8;
  uVar3 = __nwa(iVar1 * 0xf0 + 0x10);
  uVar2 = __construct_new_array(uVar3,0x299b50,0,0xf0,iVar1);
  this->u32_1fc = uVar2;
  memset(*(void **)(this + 0x1fc),0,(long)(this->i32_1f8 * 0xf0));
  iVar1 = this->i32_8;
  uVar3 = iVar1->u64_70;
  uVar2 = iVar1->u32_78;
  uVar5 = iVar1->u32_7c;
  this->i32_100 = (int)uVar3;
  this->i32_104 = (int)((ulong)uVar3 >> 0x20);
  this->u32_108 = uVar2;
  this->u32_10c = uVar5;
  for (iVar7 = 0; iVar7 < this->i32_1f8; iVar7 = iVar7 + 1) {
    (**(code **)(this->i32_1e4 + 0x4c))(this,iVar7,1);
    auVar10 = _lqc2(*(undefined1 (*) [16])(this->i32_1fc + iVar7 * 0xf0 + 0x10));
    auVar11 = _qmtc2(*(undefined4 *)(this->i32_1fc + iVar7 * 0xf0 + 4));
    auVar10 = _vmulbc(auVar10,auVar11);
    auStack_70 = _sqc2(auVar10);
    FVector::FVector(auStack_30,auStack_70);
    pauVar6 = (undefined1 (*) [16])(this->i32_1fc + iVar7 * 0xf0 + 0x30);
    auVar11 = _lqc2(auStack_30);
    auVar10 = _lqc2(*pauVar6);
    auVar10 = _vadd(auVar10,auVar11);
    auVar10 = _sqc2(auVar10);
    *pauVar6 = auVar10;
  }
  this->u32_1e0 = 0xffffffff;
  this->u8_14 = this->u8_14 & 0xfe | 1;
  this->u16_14 = this->u16_14 & 0xe01f;
  if (param_3 == 0) {
    PutiObject::SetRegTest(this,0x33001);
  }
  else {
    PutiObject::SetRegTest(this,0x73001);
  }
  PutiObject::SetRegAlpha(this,0x44);
  fVar9 = iVar1->f32_cc / 2.0;
  fStack_10 = iVar1->f32_b8 * 0.95;
  uStack_4 = 0x3f800000;
  fStack_c = fVar9;
  fStack_8 = fStack_10;
  FVector::FVector(auStack_20,iVar1 + 0x70);
  fStack_1c = fStack_1c - fVar9;
  uStack_5c = iVar1->u32_c8;
  uStack_60 = iVar1->u32_c4;
  uStack_58 = 0;
  uStack_54 = 0x3f800000;
  uVar3 = FVector::FVector(auStack_40,auStack_20);
  uVar4 = FVector::FVector(auStack_50,&fStack_10);
  FpObject::InitBBox(0,this,uVar3,uVar4,&uStack_60,1,1);
  return;
}

// JP: 0x00299b50  __ct__7_FpDataFv  =  _FpData::_FpData
int _FpData::_FpData(int this)

{
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  undefined4 *puVar1;
  
  this->u32_10 = in_zero_lo;
  this->u32_14 = in_zero_hi;
  this->u32_18 = in_zero_udw;
  this->u32_1c = in_register_0000000c;
  this->u32_20 = in_zero_lo;
  this->u32_24 = in_zero_hi;
  this->u32_28 = in_zero_udw;
  this->u32_2c = in_register_0000000c;
  this->u32_30 = in_zero_lo;
  this->u32_34 = in_zero_hi;
  this->u32_38 = in_zero_udw;
  this->u32_3c = in_register_0000000c;
  this->u32_40 = in_zero_lo;
  this->u32_44 = in_zero_hi;
  this->u32_48 = in_zero_udw;
  this->u32_4c = in_register_0000000c;
  this->u32_50 = in_zero_lo;
  this->u32_54 = in_zero_hi;
  this->u32_58 = in_zero_udw;
  this->u32_5c = in_register_0000000c;
  this->u32_60 = in_zero_lo;
  this->u32_64 = in_zero_hi;
  this->u32_68 = in_zero_udw;
  this->u32_6c = in_register_0000000c;
  puVar1 = (undefined4 *)(this + 0x70);
  do {
    *puVar1 = in_zero_lo;
    puVar1[1] = in_zero_hi;
    puVar1[2] = in_zero_udw;
    puVar1[3] = in_register_0000000c;
    puVar1 = puVar1 + 4;
  } while (puVar1 != (undefined4 *)(this + 0xb0));
  this->u32_b0 = in_zero_lo;
  this->u32_b4 = in_zero_hi;
  this->u32_b8 = in_zero_udw;
  this->u32_bc = in_register_0000000c;
  return this;
}

// JP: 0x00299bd0  CalculateFunc__11FpObjectFogFv  =  FpObjectFog::CalculateFunc
void FpObjectFog::CalculateFunc(int this)

{
  float *pfVar1;
  int iVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  
  iVar2 = this->i32_8;
  fVar3 = (float)FpPrim::GetFrameSpeed(iVar2);
  fVar4 = iVar2->f32_ac;
  fVar5 = (float)iVar2->i32_bc * 0.33333;
  fVar6 = (float)iVar2->i32_bc * 0.66666;
  pfVar1 = *(float **)(this + 0x1fc);
  for (iVar2 = 0; iVar2 < this->i32_1f8; iVar2 = iVar2 + 1) {
    pfVar1[1] = pfVar1[1] + fVar3;
    if (*pfVar1 <= pfVar1[1]) {
      (**(code **)(this->i32_1e4 + 0x4c))(this,iVar2,0);
    }
    else if (1.0 < pfVar1[1]) {
      if (pfVar1[1] < fVar5) {
        pfVar1[0x2f] = (fVar4 * pfVar1[1]) / fVar5;
      }
      else if (pfVar1[1] < fVar6) {
        pfVar1[0x2f] = fVar4;
      }
      else {
        pfVar1[0x2f] = (fVar4 * (*pfVar1 - pfVar1[1])) / (*pfVar1 - fVar6);
      }
      pfVar1[0xc] = pfVar1[0xc] + pfVar1[4] * fVar3;
      pfVar1[0xd] = pfVar1[0xd] + pfVar1[5] * fVar3;
      pfVar1[0xe] = pfVar1[0xe] + pfVar1[6] * fVar3;
    }
    pfVar1 = pfVar1 + 0x3c;
  }
  (**(code **)(this->i32_1e4 + 0x44))();
  return;
}

// JP: 0x00299e10  SetPacket__11FpObjectFogFv  =  FpObjectFog::SetPacket
void FpObjectFog::SetPacket(undefined8 this)

{
  ulong *puVar1;
  uint *puVar2;
  float in_zero_lo;
  float in_zero_hi;
  float in_zero_udw;
  float in_register_0000000c;
  ulong uVar3;
  float *pfVar4;
  int this;
  int iVar6;
  int iVar7;
  int iVar8;
  float fVar9;
  float fVar10;
  uint uVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  undefined1 auVar16 [16];
  undefined1 auVar17 [16];
  undefined1 auStack_b0 [16];
  undefined1 auStack_a0 [16];
  undefined1 auStack_90 [16];
  float fStack_80;
  float fStack_7c;
  float fStack_78;
  float fStack_74;
  undefined1 auStack_70 [16];
  undefined1 auStack_60 [4];
  float fStack_5c;
  undefined1 auStack_50 [16];
  undefined1 auStack_40 [32];
  undefined1 auStack_20 [16];
  undefined1 auStack_10 [16];
  
  
  fVar15 = this->f32_1f0 * *(float *)(this->i32_8 + 0x5c);
  iVar8 = this->i32_8;
  pfVar4 = *(float **)(this + 0x88);
  *pfVar4 = in_zero_lo;
  pfVar4[1] = in_zero_hi;
  pfVar4[2] = in_zero_udw;
  pfVar4[3] = in_register_0000000c;
  *pfVar4 = (float)(&DAT_10000001 + this->i32_1f8 * 0xc);
  pfVar4[3] = (float)(this->i32_1f8 * 0xc + 1U | 0x50000000);
  this->i32_88 = this->i32_88 + 0x10;
  puVar1 = *(ulong **)(this + 0x88);
  *puVar1 = (long)(this->i32_1f8 << 2) | 0x302a400000008000;
  puVar1[1] = 0x412;
  this->i32_88 = this->i32_88 + 0x10;
  pfVar4 = *(float **)(this + 0x88);
  Matrix::Matrix(auStack_40,CApp::camera + 0x240);
  FVector::FVector(auStack_50,auStack_10);
  FVector::FVector(auStack_60,auStack_20);
  auVar16 = _lqc2(*(undefined1 (*) [16])(iVar8 + 0x70));
  auVar17 = _lqc2(auStack_50);
  auVar16 = _vsub(auVar16,auVar17);
  auStack_a0 = _sqc2(auVar16);
  FVector::FVector(auStack_70,auStack_a0);
  if (fStack_5c < 0.0) {
    fStack_5c = fStack_5c * -1.0;
  }
  fVar9 = (float)FVector::Length(auStack_70);
  fVar9 = iVar8->f32_b8 * fStack_5c + fVar9;
  if (CApp::camera->f32_384 < fVar9) {
    fVar9 = CApp::camera->f32_384;
  }
  fVar12 = 10.0;
  iVar8 = this->i32_1fc;
  fStack_80 = in_zero_lo;
  fStack_7c = in_zero_hi;
  fStack_78 = in_zero_udw;
  fStack_74 = in_register_0000000c;
  for (iVar7 = 0; iVar7 < this->i32_1f8; iVar7 = iVar7 + 1) {
    fVar13 = 0.0;
    auVar16 = _lqc2(*(undefined1 (*) [16])(iVar8 + 0x30));
    auVar17 = _lqc2(auStack_50);
    auVar16 = _vsub(auVar16,auVar17);
    auStack_b0 = _sqc2(auVar16);
    FVector::FVector(auStack_90,auStack_b0);
    fVar10 = (float)FVector::Length(auStack_90);
    if (fVar10 < fVar9) {
      fVar13 = (fVar9 - fVar10) / fVar9;
    }
    fVar14 = 1.0;
    if ((fVar10 < fVar12) && (fVar14 = 1.0, 0.0 < fVar10)) {
      fVar14 = (fVar10 / fVar12) * (fVar10 / fVar12);
    }
    fVar14 = fVar14 * fVar13 * iVar8->f32_bc * fVar15;
    if (fVar14 < 0.0) {
      fVar14 = 0.0;
    }
    else if (128.0 < fVar14) {
      fVar14 = 128.0;
    }
    if (fVar14 <= 0.0) {
      for (iVar6 = 0; iVar6 < 4; iVar6 = iVar6 + 1) {
        *pfVar4 = in_zero_lo;
        pfVar4[1] = in_zero_hi;
        pfVar4[2] = in_zero_udw;
        pfVar4[3] = in_register_0000000c;
        this->i32_88 = this->i32_88 + 0x10;
        pfVar4 = *(float **)(this + 0x88);
        *pfVar4 = in_zero_lo;
        pfVar4[1] = in_zero_hi;
        pfVar4[2] = in_zero_udw;
        pfVar4[3] = in_register_0000000c;
        this->i32_88 = this->i32_88 + 0x10;
        pfVar4 = *(float **)(this + 0x88);
        *pfVar4 = in_zero_lo;
        pfVar4[1] = in_zero_hi;
        pfVar4[2] = in_zero_udw;
        pfVar4[3] = in_register_0000000c;
        pfVar4[3] = 4.59177e-41;
        this->i32_88 = this->i32_88 + 0x10;
        pfVar4 = *(float **)(this + 0x88);
      }
    }
    else {
      for (iVar6 = 0; iVar6 < 4; iVar6 = iVar6 + 1) {
        fVar10 = (float)PutiObject::RotTransPer
                                  (this,iVar8 + iVar6 * 0x10 + 0x70,&fStack_80);
        uVar3 = PutiObject::ClipFlag(this);
        *pfVar4 = *(float *)(iVar8 + iVar6 * 8 + 0xc0) * fVar10;
        pfVar4[1] = *(float *)(iVar8 + iVar6 * 8 + 0xc4) * fVar10;
        pfVar4[2] = fVar10;
        this->i32_88 = this->i32_88 + 0x10;
        puVar2 = *(uint **)(this + 0x88);
        fVar10 = iVar8->f32_b0;
        if (fVar10 < 2.1474836e+09) {
          uVar11 = (uint)fVar10;
        }
        else {
          uVar11 = (int)(fVar10 - 2.1474836e+09) | 0x80000000;
        }
        *puVar2 = uVar11;
        fVar10 = iVar8->f32_b4;
        if (fVar10 < 2.1474836e+09) {
          uVar11 = (uint)fVar10;
        }
        else {
          uVar11 = (int)(fVar10 - 2.1474836e+09) | 0x80000000;
        }
        puVar2[1] = uVar11;
        fVar10 = iVar8->f32_b8;
        if (fVar10 < 2.1474836e+09) {
          uVar11 = (uint)fVar10;
        }
        else {
          uVar11 = (int)(fVar10 - 2.1474836e+09) | 0x80000000;
        }
        puVar2[2] = uVar11;
        if (fVar14 < 2.1474836e+09) {
          uVar11 = (uint)fVar14;
        }
        else {
          uVar11 = (int)(fVar14 - 2.1474836e+09) | 0x80000000;
        }
        puVar2[3] = uVar11;
        this->i32_88 = this->i32_88 + 0x10;
        pfVar4 = *(float **)(this + 0x88);
        if ((iVar6 < 2) || ((uVar3 & 0x3ffff) != 0)) {
          fStack_74 = 4.59177e-41;
        }
        *pfVar4 = fStack_80;
        pfVar4[1] = fStack_7c;
        pfVar4[2] = fStack_78;
        pfVar4[3] = fStack_74;
        this->i32_88 = this->i32_88 + 0x10;
        pfVar4 = *(float **)(this + 0x88);
      }
    }
    iVar8 = iVar8 + 0xf0;
  }
  return;
}

// JP: 0x0029a3a0  __ct__9FpFogMCESFv  =  FpFogMCES::FpFogMCES
int FpFogMCES::FpFogMCES(int this)

{
  FpPrim::FpPrim(this);
  *(undefined1 **)(this + 0x10) = FpFogMCES::__vt;
  this->u32_1c = 0x405c90;
  return this;
}

// JP: 0x0029a3f0  __dt__9FpFogMCESFv  =  FpFogMCES::~FpFogMCES
int FpFogMCES::~FpFogMCES(int this,short param_2)

{
  if (this != 0) {
    *(undefined1 **)(this + 0x10) = FpFogMCES::__vt;
    this->u32_1c = 0x405c90;
    FpPrim::~FpPrim(this,0);
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}

// JP: 0x0029a480  Create__9FpFogMCESFv  =  FpFogMCES::Create
void FpFogMCES::Create(int this)

{
  long lVar1;
  undefined8 uVar2;
  int iVar3;
  
  iVar3 = BgEffectMan::eff->i32_1c + 0x8c;
  SetWhiteTex(iVar3);
  PutiPrim::SetTexture(this,iVar3,0);
  lVar1 = __nw(0x220);
  uVar2 = 0;
  if (lVar1 != 0) {
    uVar2 = FpObjectFogMCES::FpObjectFogMCES(lVar1,0x14,0);
  }
  PutiPrim::AddObject(this,uVar2);
  (**(code **)(*(int *)((int)uVar2 + 0x1e4) + 0x40))(uVar2,0,0);
  PutiManager::AddPrim(BgEffectMan::eff,this->u32_54,this);
  return;
}

// JP: 0x0029a560  Create__9FpFogMCESFPv  =  FpFogMCES::Create
void FpFogMCES::Create(undefined4 this)

{
  FpFogMCES::Create(this);
  return;
}

// JP: 0x0029a5b0  getPacket__9FpFogMCESFv  =  FpFogMCES::getPacket
void FpFogMCES::getPacket(undefined4 this)

{
  PutiPrim::getPacket(this);
  return;
}

// JP: 0x0029a5e0  __ct__15FpObjectFogMCESFiPv  =  FpObjectFogMCES::FpObjectFogMCES
int FpObjectFogMCES::FpObjectFogMCES(int this,undefined4 param_2,undefined4 param_3)

{
  FpObject::FpObject(this,param_2,param_3);
  *(undefined1 **)(this + 0x1e4) = FpObjectFogMCES::__vt;
  this->u32_210 = 0;
  return this;
}

// JP: 0x0029a640  __dt__15FpObjectFogMCESFv  =  FpObjectFogMCES::~FpObjectFogMCES
int FpObjectFogMCES::~FpObjectFogMCES(int this,short param_2)

{
  if (this != 0) {
    *(undefined1 **)(this + 0x1e4) = FpObjectFogMCES::__vt;
    FpObject::~FpObject(this,0);
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}

// JP: 0x0029a6c0  Init__15FpObjectFogMCESFib  =  FpObjectFogMCES::Init
void FpObjectFogMCES::Init(int this)

{
  undefined4 uVar1;
  long lVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined1 auStack_d0 [16];
  undefined1 auStack_c0 [16];
  undefined1 auStack_b0 [16];
  undefined1 auStack_a0 [16];
  undefined4 uStack_90;
  undefined4 uStack_8c;
  undefined4 uStack_88;
  undefined4 uStack_84;
  undefined4 uStack_80;
  undefined4 uStack_7c;
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  this->u32_1f4 = 1;
  this->u32_1f8 = 1;
  this->u8_14 = this->u8_14 & 0xef;
  this->u8_14 = this->u8_14 & 0xf7;
  this->u8_14 = this->u8_14 & 0xfb;
  this->u8_14 = this->u8_14 & 0xfd;
  this->u8_14 = this->u8_14 & 0xfe;
  this->u16_14 = this->u16_14 & 0xe01f | 0x1fe0;
  this->u16_14 = this->u16_14 & 0xe01f;
  uVar7 = this->u32_8;
  lVar2 = __nw(0x260);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = FpObjectFogBox::FpObjectFogBox(lVar2,0x26c,0);
  }
  this->u32_210 = uVar1;
  PutiPrim::AddObject(uVar7,this->u32_210);
  (**(code **)(*(int *)(this->i32_210 + 0x1e4) + 0x40))
            (this->i32_210,0x32,1);
  uStack_60 = 0x4211a830;
  uStack_5c = 0xc22b3135;
  uStack_58 = 0x415802ae;
  uStack_54 = 0x3f800000;
  uStack_10 = 0x4211a830;
  uStack_c = 0xc22b3135;
  uStack_8 = 0x415802ae;
  uStack_4 = 0x3f800000;
  uStack_70 = 0xbf7253b9;
  uStack_6c = 0x3e4f0996;
  uStack_68 = 0xbe805921;
  uStack_64 = 0x3f800000;
  uStack_20 = 0xbf7253b9;
  uStack_1c = 0x3e4f0996;
  uStack_18 = 0xbe805921;
  uStack_14 = 0x3f800000;
  uStack_80 = 0x3e485165;
  uStack_7c = 0x3f7ab65b;
  uStack_78 = 0x3d514b16;
  uStack_74 = 0x3f800000;
  uStack_30 = 0x3e485165;
  uStack_2c = 0x3f7ab65b;
  uStack_28 = 0x3d514b16;
  uStack_24 = 0x3f800000;
  uVar8 = 0;
  uVar7 = 0x41200000;
  uVar1 = 0x40a00000;
  uStack_90 = 0x43000000;
  uStack_8c = 0x42800000;
  uStack_88 = 0x43000000;
  uStack_84 = 0x41f00000;
  uStack_50 = 0x43000000;
  uStack_4c = 0x42800000;
  uStack_48 = 0x43000000;
  uStack_44 = 0x41f00000;
  uVar3 = FVector::FVector(auStack_a0,&uStack_10);
  uVar4 = FVector::FVector(auStack_b0,&uStack_20);
  uVar5 = FVector::FVector(auStack_c0,&uStack_30);
  uVar6 = FVector::FVector(auStack_d0,&uStack_50);
  FpObjectFogBox::ChangeDataCup
            (0x3f800000,uVar8,0x41200000,uVar7,0x42c80000,uVar1,0xbc23d70a,
             this->u32_210,uVar3,uVar4,uVar5,uVar6);
  return;
}

// JP: 0x0029aad0  Calculate__15FpObjectFogMCESFv  =  FpObjectFogMCES::Calculate
undefined4 FpObjectFogMCES::Calculate(int this)

{
  (**(code **)(this->i32_1e4 + 0x48))();
  return 1;
}

// JP: 0x0029ab10  FuncChangeData__15FpObjectFogMCESFv  =  FpObjectFogMCES::FuncChangeData
/* WARNING: Removing unreachable block (ram,0x0029ab84) */
/* WARNING: Removing unreachable block (ram,0x0029ac0c) */

void FpObjectFogMCES::FuncChangeData(int this)

{
  undefined8 uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  float fVar5;
  uint uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined1 auStack_a20 [16];
  undefined1 auStack_a10 [16];
  undefined1 auStack_a00 [16];
  undefined1 auStack_9f0 [16];
  undefined4 uStack_9e0;
  undefined4 uStack_9dc;
  undefined4 uStack_9d8;
  undefined4 uStack_9d4;
  undefined4 uStack_9d0;
  undefined4 uStack_9cc;
  undefined4 uStack_9c8;
  undefined4 uStack_9c4;
  undefined4 uStack_9c0;
  undefined4 uStack_9bc;
  undefined4 uStack_9b8;
  undefined4 uStack_9b4;
  undefined1 auStack_9b0 [16];
  undefined1 auStack_9a0 [16];
  undefined1 auStack_990 [16];
  undefined1 auStack_980 [16];
  undefined4 uStack_970;
  undefined4 uStack_96c;
  undefined4 uStack_968;
  undefined4 uStack_964;
  undefined4 uStack_960;
  undefined4 uStack_95c;
  undefined4 uStack_958;
  undefined4 uStack_954;
  undefined4 uStack_950;
  undefined4 uStack_94c;
  undefined4 uStack_948;
  undefined4 uStack_944;
  undefined1 auStack_940 [16];
  undefined1 auStack_930 [16];
  undefined1 auStack_920 [16];
  undefined1 auStack_910 [16];
  undefined4 uStack_900;
  undefined4 uStack_8fc;
  undefined4 uStack_8f8;
  undefined4 uStack_8f4;
  undefined4 uStack_8f0;
  undefined4 uStack_8ec;
  undefined4 uStack_8e8;
  undefined4 uStack_8e4;
  undefined4 uStack_8e0;
  undefined4 uStack_8dc;
  undefined4 uStack_8d8;
  undefined4 uStack_8d4;
  undefined1 auStack_8d0 [16];
  undefined1 auStack_8c0 [16];
  undefined1 auStack_8b0 [16];
  undefined1 auStack_8a0 [16];
  undefined4 uStack_890;
  undefined4 uStack_88c;
  undefined4 uStack_888;
  undefined4 uStack_884;
  undefined4 uStack_880;
  undefined4 uStack_87c;
  undefined4 uStack_878;
  undefined4 uStack_874;
  undefined4 uStack_870;
  undefined4 uStack_86c;
  undefined4 uStack_868;
  undefined4 uStack_864;
  undefined1 auStack_860 [16];
  undefined1 auStack_850 [16];
  undefined1 auStack_840 [16];
  undefined1 auStack_830 [16];
  undefined4 uStack_820;
  undefined4 uStack_81c;
  undefined4 uStack_818;
  undefined4 uStack_814;
  undefined4 uStack_810;
  undefined4 uStack_80c;
  undefined4 uStack_808;
  undefined4 uStack_804;
  undefined4 uStack_800;
  undefined4 uStack_7fc;
  undefined4 uStack_7f8;
  undefined4 uStack_7f4;
  undefined1 auStack_7f0 [16];
  undefined1 auStack_7e0 [16];
  undefined1 auStack_7d0 [16];
  undefined1 auStack_7c0 [16];
  undefined4 uStack_7b0;
  undefined4 uStack_7ac;
  undefined4 uStack_7a8;
  undefined4 uStack_7a4;
  undefined4 uStack_7a0;
  undefined4 uStack_79c;
  undefined4 uStack_798;
  undefined4 uStack_794;
  undefined4 uStack_790;
  undefined4 uStack_78c;
  undefined4 uStack_788;
  undefined4 uStack_784;
  undefined1 auStack_780 [16];
  undefined1 auStack_770 [16];
  undefined1 auStack_760 [16];
  undefined1 auStack_750 [16];
  undefined4 uStack_740;
  undefined4 uStack_73c;
  undefined4 uStack_738;
  undefined4 uStack_734;
  undefined4 uStack_730;
  undefined4 uStack_72c;
  undefined4 uStack_728;
  undefined4 uStack_724;
  undefined4 uStack_720;
  undefined4 uStack_71c;
  undefined4 uStack_718;
  undefined4 uStack_714;
  undefined1 auStack_710 [16];
  undefined1 auStack_700 [16];
  undefined1 auStack_6f0 [16];
  undefined1 auStack_6e0 [16];
  undefined4 uStack_6d0;
  undefined4 uStack_6cc;
  undefined4 uStack_6c8;
  undefined4 uStack_6c4;
  undefined4 uStack_6c0;
  undefined4 uStack_6bc;
  undefined4 uStack_6b8;
  undefined4 uStack_6b4;
  undefined4 uStack_6b0;
  undefined4 uStack_6ac;
  undefined4 uStack_6a8;
  undefined4 uStack_6a4;
  undefined1 auStack_6a0 [16];
  undefined1 auStack_690 [16];
  undefined1 auStack_680 [16];
  undefined1 auStack_670 [16];
  undefined4 uStack_660;
  undefined4 uStack_65c;
  undefined4 uStack_658;
  undefined4 uStack_654;
  undefined4 uStack_650;
  undefined4 uStack_64c;
  undefined4 uStack_648;
  undefined4 uStack_644;
  undefined4 uStack_640;
  undefined4 uStack_63c;
  undefined4 uStack_638;
  undefined4 uStack_634;
  undefined1 auStack_630 [16];
  undefined1 auStack_620 [16];
  undefined1 auStack_610 [16];
  undefined1 auStack_600 [16];
  undefined4 uStack_5f0;
  undefined4 uStack_5ec;
  undefined4 uStack_5e8;
  undefined4 uStack_5e4;
  undefined4 uStack_5e0;
  undefined4 uStack_5dc;
  undefined4 uStack_5d8;
  undefined4 uStack_5d4;
  undefined4 uStack_5d0;
  undefined4 uStack_5cc;
  undefined4 uStack_5c8;
  undefined4 uStack_5c4;
  undefined1 auStack_5c0 [16];
  undefined1 auStack_5b0 [16];
  undefined1 auStack_5a0 [16];
  undefined1 auStack_590 [16];
  undefined4 uStack_580;
  undefined4 uStack_57c;
  undefined4 uStack_578;
  undefined4 uStack_574;
  undefined4 uStack_570;
  undefined4 uStack_56c;
  undefined4 uStack_568;
  undefined4 uStack_564;
  undefined4 uStack_560;
  undefined4 uStack_55c;
  undefined4 uStack_558;
  undefined4 uStack_554;
  undefined1 auStack_550 [16];
  undefined1 auStack_540 [16];
  undefined1 auStack_530 [16];
  undefined1 auStack_520 [16];
  undefined4 uStack_510;
  undefined4 uStack_50c;
  undefined4 uStack_508;
  undefined4 uStack_504;
  undefined4 uStack_500;
  undefined4 uStack_4fc;
  undefined4 uStack_4f8;
  undefined4 uStack_4f4;
  undefined4 uStack_4f0;
  undefined4 uStack_4ec;
  undefined4 uStack_4e8;
  undefined4 uStack_4e4;
  undefined1 auStack_4e0 [16];
  undefined1 auStack_4d0 [16];
  undefined1 auStack_4c0 [16];
  undefined1 auStack_4b0 [16];
  undefined4 uStack_4a0;
  undefined4 uStack_49c;
  undefined4 uStack_498;
  undefined4 uStack_494;
  undefined4 uStack_490;
  undefined4 uStack_48c;
  undefined4 uStack_488;
  undefined4 uStack_484;
  undefined4 uStack_480;
  undefined4 uStack_47c;
  undefined4 uStack_478;
  undefined4 uStack_474;
  undefined1 auStack_470 [16];
  undefined1 auStack_460 [16];
  undefined1 auStack_450 [16];
  undefined1 auStack_440 [16];
  undefined4 uStack_430;
  undefined4 uStack_42c;
  undefined4 uStack_428;
  undefined4 uStack_424;
  undefined4 uStack_420;
  undefined4 uStack_41c;
  undefined4 uStack_418;
  undefined4 uStack_414;
  undefined4 uStack_410;
  undefined4 uStack_40c;
  undefined4 uStack_408;
  undefined4 uStack_404;
  undefined1 auStack_400 [16];
  undefined1 auStack_3f0 [16];
  undefined1 auStack_3e0 [16];
  undefined1 auStack_3d0 [16];
  undefined4 uStack_3c0;
  undefined4 uStack_3bc;
  undefined4 uStack_3b8;
  undefined4 uStack_3b4;
  undefined4 uStack_3b0;
  undefined4 uStack_3ac;
  undefined4 uStack_3a8;
  undefined4 uStack_3a4;
  undefined4 uStack_3a0;
  undefined4 uStack_39c;
  undefined4 uStack_398;
  undefined4 uStack_394;
  undefined1 auStack_390 [16];
  undefined1 auStack_380 [16];
  undefined1 auStack_370 [16];
  undefined1 auStack_360 [16];
  undefined4 uStack_350;
  undefined4 uStack_34c;
  undefined4 uStack_348;
  undefined4 uStack_344;
  undefined4 uStack_340;
  undefined4 uStack_33c;
  undefined4 uStack_338;
  undefined4 uStack_334;
  undefined4 uStack_330;
  undefined4 uStack_32c;
  undefined4 uStack_328;
  undefined4 uStack_324;
  undefined1 auStack_320 [16];
  undefined1 auStack_310 [16];
  undefined1 auStack_300 [16];
  undefined1 auStack_2f0 [16];
  undefined4 uStack_2e0;
  undefined4 uStack_2dc;
  undefined4 uStack_2d8;
  undefined4 uStack_2d4;
  undefined4 uStack_2d0;
  undefined4 uStack_2cc;
  undefined4 uStack_2c8;
  undefined4 uStack_2c4;
  undefined4 uStack_2c0;
  undefined4 uStack_2bc;
  undefined *puStack_2b8;
  undefined4 uStack_2b4;
  undefined1 auStack_2b0 [16];
  undefined1 auStack_2a0 [16];
  undefined1 auStack_290 [16];
  undefined1 auStack_280 [16];
  undefined4 uStack_270;
  undefined4 uStack_26c;
  undefined4 uStack_268;
  undefined4 uStack_264;
  undefined4 uStack_260;
  undefined4 uStack_25c;
  undefined4 uStack_258;
  undefined4 uStack_254;
  undefined4 uStack_250;
  undefined4 uStack_24c;
  undefined4 uStack_248;
  undefined4 uStack_244;
  undefined1 auStack_240 [16];
  undefined1 auStack_230 [16];
  undefined1 auStack_220 [16];
  undefined1 auStack_210 [16];
  undefined4 uStack_200;
  undefined4 uStack_1fc;
  undefined4 uStack_1f8;
  undefined4 uStack_1f4;
  undefined4 uStack_1f0;
  undefined4 uStack_1ec;
  undefined4 uStack_1e8;
  undefined4 uStack_1e4;
  undefined4 uStack_1e0;
  undefined4 uStack_1dc;
  undefined4 uStack_1d8;
  undefined4 uStack_1d4;
  undefined1 auStack_1d0 [16];
  undefined1 auStack_1c0 [16];
  undefined1 auStack_1b0 [16];
  undefined1 auStack_1a0 [16];
  undefined4 uStack_190;
  undefined4 uStack_18c;
  undefined4 uStack_188;
  undefined4 uStack_184;
  undefined4 uStack_180;
  undefined4 uStack_17c;
  undefined4 uStack_178;
  undefined4 uStack_174;
  undefined4 uStack_170;
  undefined4 uStack_16c;
  undefined4 uStack_168;
  undefined4 uStack_164;
  undefined1 auStack_160 [16];
  undefined1 auStack_150 [16];
  undefined1 auStack_140 [16];
  undefined1 auStack_130 [16];
  undefined4 uStack_120;
  undefined4 uStack_11c;
  undefined4 uStack_118;
  undefined4 uStack_114;
  undefined4 uStack_110;
  undefined4 uStack_10c;
  undefined4 uStack_108;
  undefined4 uStack_104;
  undefined4 uStack_100;
  undefined4 uStack_fc;
  undefined4 uStack_f8;
  undefined4 uStack_f4;
  undefined1 auStack_f0 [16];
  undefined1 auStack_e0 [16];
  undefined1 auStack_d0 [16];
  undefined1 auStack_c0 [16];
  undefined4 uStack_b0;
  undefined4 uStack_ac;
  undefined4 uStack_a8;
  undefined4 uStack_a4;
  undefined4 uStack_a0;
  undefined4 uStack_9c;
  undefined4 uStack_98;
  undefined4 uStack_94;
  undefined4 uStack_90;
  undefined4 uStack_8c;
  undefined4 uStack_88;
  undefined4 uStack_84;
  undefined4 uStack_80;
  undefined4 uStack_7c;
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined *puStack_8;
  undefined4 uStack_4;
  
  if (LSDPlayer::sys != 0) {
    fVar5 = LSDPlayer::sys->f32_1c * (float)LSDPlayer::sys->u16_3e;
    if (fVar5 < 2.1474836e+09) {
      uVar6 = (uint)fVar5;
    }
    else {
      uVar6 = (int)(fVar5 - 2.1474836e+09) | 0x80000000;
    }
    uVar9 = 0;
    uVar7 = 0x41200000;
    uVar8 = 0x40a00000;
    uStack_80 = 0x43000000;
    uStack_7c = 0x42800000;
    uStack_78 = 0x43000000;
    uStack_74 = 0x41f00000;
    uStack_70 = 0x43000000;
    uStack_6c = 0x42800000;
    uStack_68 = 0x43000000;
    uStack_64 = 0x41f00000;
    if (uVar6 == 0xdf9) {
      uStack_9c0 = 0xc1e2bf5e;
      uStack_9bc = 0xc117b9d8;
      uStack_9b8 = 0xc1c66c71;
      uStack_9b4 = 0x3f800000;
      uStack_10 = 0xc1e2bf5e;
      uStack_c = 0xc117b9d8;
      puStack_8 = (undefined *)0xc1c66c71;
      uStack_4 = 0x3f800000;
      uStack_9d0 = 0x3f73a0a5;
      uStack_9cc = 0xbdffe08b;
      uStack_9c8 = 0xbe8f49cf;
      uStack_9c4 = 0x3f800000;
      uStack_20 = 0x3f73a0a5;
      uStack_1c = 0xbdffe08b;
      uStack_18 = 0xbe8f49cf;
      uStack_14 = 0x3f800000;
      uStack_9e0 = 0x3df59d56;
      uStack_9dc = 0x3f7dfe65;
      uStack_9d8 = 0xbd0f7caa;
      uStack_9d4 = 0x3f800000;
      uStack_30 = 0x3df59d56;
      uStack_2c = 0x3f7dfe65;
      uStack_28 = 0xbd0f7caa;
      uStack_24 = 0x3f800000;
      uVar8 = 0x40800000;
      uVar1 = FVector::FVector(auStack_9f0,&uStack_10);
      uVar2 = FVector::FVector(auStack_a00,&uStack_20);
      uVar3 = FVector::FVector(auStack_a10,&uStack_30);
      uVar4 = FVector::FVector(auStack_a20,&uStack_70);
      FpObjectFogBox::ChangeDataCup
                (0,uVar9,0x41200000,uVar7,0x42c80000,uVar8,0x3ca3d70a,
                 this->u32_210,uVar1,uVar2,uVar3,uVar4);
    }
    else if (uVar6 == 0xd4e) {
      uStack_950 = 0xc15bb4a8;
      uStack_94c = 0xc1738406;
      uStack_948 = 0xc2565319;
      uStack_944 = 0x3f800000;
      uStack_10 = 0xc15bb4a8;
      uStack_c = 0xc1738406;
      puStack_8 = (undefined *)0xc2565319;
      uStack_4 = 0x3f800000;
      uStack_960 = 0x3c5d7ecc;
      uStack_95c = 0x3e3fa4c6;
      uStack_958 = 0x3f7b73e2;
      uStack_954 = 0x3f800000;
      uStack_20 = 0x3c5d7ecc;
      uStack_1c = 0x3e3fa4c6;
      uStack_18 = 0x3f7b73e2;
      uStack_14 = 0x3f800000;
      uStack_970 = 0xbb13ea2d;
      uStack_96c = 0x3f7b79fb;
      uStack_968 = 0xbe3fa11b;
      uStack_964 = 0x3f800000;
      uStack_30 = 0xbb13ea2d;
      uStack_2c = 0x3f7b79fb;
      uStack_28 = 0xbe3fa11b;
      uStack_24 = 0x3f800000;
      uVar1 = FVector::FVector(auStack_980,&uStack_10);
      uVar2 = FVector::FVector(auStack_990,&uStack_20);
      uVar3 = FVector::FVector(auStack_9a0,&uStack_30);
      uVar4 = FVector::FVector(auStack_9b0,&uStack_70);
      FpObjectFogBox::ChangeDataCup
                (0,uVar9,0x41200000,uVar7,0x42c80000,uVar8,0x3ca3d70a,
                 this->u32_210,uVar1,uVar2,uVar3,uVar4);
    }
    else if (uVar6 == 0xc2b) {
      uStack_8e0 = 0xc09adc55;
      uStack_8dc = 0xc129ea5d;
      uStack_8d8 = 0xc058779f;
      uStack_8d4 = 0x3f800000;
      uStack_10 = 0xc09adc55;
      uStack_c = 0xc129ea5d;
      puStack_8 = (undefined *)0xc058779f;
      uStack_4 = 0x3f800000;
      uStack_8f0 = 0x3e8176de;
      uStack_8ec = 0xbd6e2867;
      uStack_8e8 = 0x3f773b75;
      uStack_8e4 = 0x3f800000;
      uStack_20 = 0x3e8176de;
      uStack_1c = 0xbd6e2867;
      uStack_18 = 0x3f773b75;
      uStack_14 = 0x3f800000;
      uStack_900 = 0xbcef459e;
      uStack_8fc = 0x3f7f4dad;
      uStack_8f8 = 0x3d8aa10e;
      uStack_8f4 = 0x3f800000;
      uStack_30 = 0xbcef459e;
      uStack_2c = 0x3f7f4dad;
      uStack_28 = 0x3d8aa10e;
      uStack_24 = 0x3f800000;
      uVar8 = 0x40800000;
      uVar1 = FVector::FVector(auStack_910,&uStack_10);
      uVar2 = FVector::FVector(auStack_920,&uStack_20);
      uVar3 = FVector::FVector(auStack_930,&uStack_30);
      uVar4 = FVector::FVector(auStack_940,&uStack_70);
      FpObjectFogBox::ChangeDataCup
                (0,uVar9,0x41200000,uVar7,0x42c80000,uVar8,0x3ca3d70a,
                 this->u32_210,uVar1,uVar2,uVar3,uVar4);
    }
    else if (uVar6 == 0xb03) {
      uStack_870 = 0xc1547f20;
      uStack_86c = 0xc13dae84;
      uStack_868 = 0xc20bc055;
      uStack_864 = 0x3f800000;
      uStack_10 = 0xc1547f20;
      uStack_c = 0xc13dae84;
      puStack_8 = (undefined *)0xc20bc055;
      uStack_4 = 0x3f800000;
      uStack_880 = 0xbe764e8b;
      uStack_87c = 0xbd168f8e;
      uStack_878 = 0xbf7847e5;
      uStack_874 = 0x3f800000;
      uStack_20 = 0xbe764e8b;
      uStack_1c = 0xbd168f8e;
      uStack_18 = 0xbf7847e5;
      uStack_14 = 0x3f800000;
      uStack_890 = 0xbc004d98;
      uStack_88c = 0x3f7fd3b3;
      uStack_888 = 0xbd132b56;
      uStack_884 = 0x3f800000;
      uStack_30 = 0xbc004d98;
      uStack_2c = 0x3f7fd3b3;
      uStack_28 = 0xbd132b56;
      uStack_24 = 0x3f800000;
      uVar1 = FVector::FVector(auStack_8a0,&uStack_10);
      uVar2 = FVector::FVector(auStack_8b0,&uStack_20);
      uVar3 = FVector::FVector(auStack_8c0,&uStack_30);
      uVar4 = FVector::FVector(auStack_8d0,&uStack_70);
      FpObjectFogBox::ChangeDataCup
                (0,uVar9,0x41200000,uVar7,0x42c80000,uVar8,0x3ca3d70a,
                 this->u32_210,uVar1,uVar2,uVar3,uVar4);
    }
    else if (uVar6 == 0xab4) {
      uStack_800 = 0xc0a4fb03;
      uStack_7fc = 0xc141fdf5;
      uStack_7f8 = 0xc1220190;
      uStack_7f4 = 0x3f800000;
      uStack_10 = 0xc0a4fb03;
      uStack_c = 0xc141fdf5;
      puStack_8 = (undefined *)0xc1220190;
      uStack_4 = 0x3f800000;
      uStack_810 = 0x3e84957d;
      uStack_80c = 0x3df4ea07;
      uStack_808 = 0x3f755d5f;
      uStack_804 = 0x3f800000;
      uStack_20 = 0x3e84957d;
      uStack_1c = 0x3df4ea07;
      uStack_18 = 0x3f755d5f;
      uStack_14 = 0x3f800000;
      uStack_820 = 0xbd031f04;
      uStack_81c = 0x3f7e29a6;
      uStack_818 = 0xbdebfb9c;
      uStack_814 = 0x3f800000;
      uStack_30 = 0xbd031f04;
      uStack_2c = 0x3f7e29a6;
      uStack_28 = 0xbdebfb9c;
      uStack_24 = 0x3f800000;
      uVar1 = FVector::FVector(auStack_830,&uStack_10);
      uVar2 = FVector::FVector(auStack_840,&uStack_20);
      uVar3 = FVector::FVector(auStack_850,&uStack_30);
      uVar4 = FVector::FVector(auStack_860,&uStack_70);
      FpObjectFogBox::ChangeDataCup
                (0,uVar9,0x41200000,uVar7,0x42c80000,uVar8,0x3ca3d70a,
                 this->u32_210,uVar1,uVar2,uVar3,uVar4);
    }
    else if (uVar6 == 0xa29) {
      uStack_790 = 0x41eda7a6;
      uStack_78c = 0xc1910ade;
      uStack_788 = 0x407e33b9;
      uStack_784 = 0x3f800000;
      uStack_10 = 0x41eda7a6;
      uStack_c = 0xc1910ade;
      puStack_8 = (undefined *)0x407e33b9;
      uStack_4 = 0x3f800000;
      uStack_7a0 = 0xbf0b2f34;
      uStack_79c = 0x3e86afee;
      uStack_798 = 0xbf4bc04d;
      uStack_794 = 0x3f800000;
      uStack_20 = 0xbf0b2f34;
      uStack_1c = 0x3e86afee;
      uStack_18 = 0xbf4bc04d;
      uStack_14 = 0x3f800000;
      uStack_7b0 = 0x3e189268;
      uStack_7ac = 0x3f76fa94;
      uStack_7a8 = 0x3e5e00d2;
      uStack_7a4 = 0x3f800000;
      uStack_30 = 0x3e189268;
      uStack_2c = 0x3f76fa94;
      uStack_28 = 0x3e5e00d2;
      uStack_24 = 0x3f800000;
      uVar1 = FVector::FVector(auStack_7c0,&uStack_10);
      uVar2 = FVector::FVector(auStack_7d0,&uStack_20);
      uVar3 = FVector::FVector(auStack_7e0,&uStack_30);
      uVar4 = FVector::FVector(auStack_7f0,&uStack_70);
      FpObjectFogBox::ChangeDataCup
                (0,uVar9,0x41200000,uVar7,0x42c80000,uVar8,0x3ca3d70a,
                 this->u32_210,uVar1,uVar2,uVar3,uVar4);
    }
    else if (uVar6 == 0x8b3) {
      uStack_720 = 0xc15b98d8;
      uStack_71c = 0xc1243b1f;
      uStack_718 = 0xc2081137;
      uStack_714 = 0x3f800000;
      uStack_10 = 0xc15b98d8;
      uStack_c = 0xc1243b1f;
      puStack_8 = (undefined *)0xc2081137;
      uStack_4 = 0x3f800000;
      uStack_730 = 0xbe41b79e;
      uStack_72c = 0xbe4fc04d;
      uStack_728 = 0xbf75d862;
      uStack_724 = 0x3f800000;
      uStack_20 = 0xbe41b79e;
      uStack_1c = 0xbe4fc04d;
      uStack_18 = 0xbf75d862;
      uStack_14 = 0x3f800000;
      uStack_740 = 0xbd1b866e;
      uStack_73c = 0x3f7aacb8;
      uStack_738 = 0xbe4c1590;
      uStack_734 = 0x3f800000;
      uStack_30 = 0xbd1b866e;
      uStack_2c = 0x3f7aacb8;
      uStack_28 = 0xbe4c1590;
      uStack_24 = 0x3f800000;
      uVar1 = FVector::FVector(auStack_750,&uStack_10);
      uVar2 = FVector::FVector(auStack_760,&uStack_20);
      uVar3 = FVector::FVector(auStack_770,&uStack_30);
      uVar4 = FVector::FVector(auStack_780,&uStack_70);
      FpObjectFogBox::ChangeDataCup
                (0,uVar9,0x41200000,uVar7,0x42c80000,uVar8,0x3ca3d70a,
                 this->u32_210,uVar1,uVar2,uVar3,uVar4);
    }
    else if (uVar6 == 0x7bd) {
      uStack_6b0 = 0xc15d993f;
      uStack_6ac = 0xc0a98277;
      uStack_6a8 = 0xc2809bd5;
      uStack_6a4 = 0x3f800000;
      uStack_10 = 0xc15d993f;
      uStack_c = 0xc0a98277;
      puStack_8 = (undefined *)0xc2809bd5;
      uStack_4 = 0x3f800000;
      uStack_6c0 = 0xbd2dfe76;
      uStack_6bc = 0xbd18383b;
      uStack_6b8 = 0x3f7f97ab;
      uStack_6b4 = 0x3f800000;
      uStack_20 = 0xbd2dfe76;
      uStack_1c = 0xbd18383b;
      uStack_18 = 0x3f7f97ab;
      uStack_14 = 0x3f800000;
      uStack_6d0 = 0xbb13c89f;
      uStack_6cc = 0x3f7fd2c8;
      uStack_6c8 = 0x3d17f738;
      uStack_6c4 = 0x3f800000;
      uStack_30 = 0xbb13c89f;
      uStack_2c = 0x3f7fd2c8;
      uStack_28 = 0x3d17f738;
      uStack_24 = 0x3f800000;
      uVar9 = 0x41a00000;
      uVar7 = 0xc1200000;
      uVar8 = 0x40fccccd;
      uVar1 = FVector::FVector(auStack_6e0,&uStack_10);
      uVar2 = FVector::FVector(auStack_6f0,&uStack_20);
      uVar3 = FVector::FVector(auStack_700,&uStack_30);
      uVar4 = FVector::FVector(auStack_710,&uStack_70);
      FpObjectFogBox::ChangeDataCup
                (0x41200000,uVar7,0x41a00000,uVar9,0x42c80000,uVar8,0x3bc49ba6,
                 this->u32_210,uVar1,uVar2,uVar3,uVar4);
    }
    else if (uVar6 == 0x754) {
      uStack_640 = 0xbfe50596;
      uStack_63c = 0xc129e90b;
      uStack_638 = 0xc19ca59a;
      uStack_634 = 0x3f800000;
      uStack_10 = 0xbfe50596;
      uStack_c = 0xc129e90b;
      puStack_8 = (undefined *)0xc19ca59a;
      uStack_4 = 0x3f800000;
      uStack_650 = 0xbdd77d95;
      uStack_64c = 0x3d69fe00;
      uStack_648 = 0x3f7e2889;
      uStack_644 = 0x3f800000;
      uStack_20 = 0xbdd77d95;
      uStack_1c = 0x3d69fe00;
      uStack_18 = 0x3f7e2889;
      uStack_14 = 0x3f800000;
      uStack_660 = 0x3ba29846;
      uStack_65c = 0x3f7f94ea;
      uStack_658 = 0xbd6925ff;
      uStack_654 = 0x3f800000;
      uStack_30 = 0x3ba29846;
      uStack_2c = 0x3f7f94ea;
      uStack_28 = 0xbd6925ff;
      uStack_24 = 0x3f800000;
      uVar1 = FVector::FVector(auStack_670,&uStack_10);
      uVar2 = FVector::FVector(auStack_680,&uStack_20);
      uVar3 = FVector::FVector(auStack_690,&uStack_30);
      uVar4 = FVector::FVector(auStack_6a0,&uStack_70);
      FpObjectFogBox::ChangeDataCup
                (0,uVar9,0x41200000,uVar7,0x42c80000,uVar8,0x3ca3d70a,
                 this->u32_210,uVar1,uVar2,uVar3,uVar4);
    }
    else if (uVar6 == 0x727) {
      uStack_5d0 = 0xbf363ee2;
      uStack_5cc = 0xc13e12ca;
      uStack_5c8 = 0xc1669d83;
      uStack_5c4 = 0x3f800000;
      uStack_10 = 0xbf363ee2;
      uStack_c = 0xc13e12ca;
      puStack_8 = (undefined *)0xc1669d83;
      uStack_4 = 0x3f800000;
      uStack_5e0 = 0xbf3ee7e6;
      uStack_5dc = 0x3e0f8ec1;
      uStack_5d8 = 0x3f26ba5a;
      uStack_5d4 = 0x3f800000;
      uStack_20 = 0xbf3ee7e6;
      uStack_1c = 0x3e0f8ec1;
      uStack_18 = 0x3f26ba5a;
      uStack_14 = 0x3f800000;
      uStack_5f0 = 0x3dd6c3fc;
      uStack_5ec = 0x3f7d78b3;
      uStack_5e8 = 0xbdbe9100;
      uStack_5e4 = 0x3f800000;
      uStack_30 = 0x3dd6c3fc;
      uStack_2c = 0x3f7d78b3;
      uStack_28 = 0xbdbe9100;
      uStack_24 = 0x3f800000;
      uVar8 = 0x40400000;
      uVar1 = FVector::FVector(auStack_600,&uStack_10);
      uVar2 = FVector::FVector(auStack_610,&uStack_20);
      uVar3 = FVector::FVector(auStack_620,&uStack_30);
      uVar4 = FVector::FVector(auStack_630,&uStack_70);
      FpObjectFogBox::ChangeDataCup
                (0,uVar9,0x41200000,uVar7,0x42c80000,uVar8,0x3ca3d70a,
                 this->u32_210,uVar1,uVar2,uVar3,uVar4);
    }
    else if (uVar6 == 0x618) {
      uStack_560 = 0xc0fb732c;
      uStack_55c = 0xc09e8c97;
      uStack_558 = 0x4183b82b;
      uStack_554 = 0x3f800000;
      uStack_10 = 0xc0fb732c;
      uStack_c = 0xc09e8c97;
      puStack_8 = (undefined *)0x4183b82b;
      uStack_4 = 0x3f800000;
      uStack_570 = 0x3dd2a62b;
      uStack_56c = 0xbe64e2f3;
      uStack_568 = 0xbf780d4e;
      uStack_564 = 0x3f800000;
      uStack_20 = 0x3dd2a62b;
      uStack_1c = 0xbe64e2f3;
      uStack_18 = 0xbf780d4e;
      uStack_14 = 0x3f800000;
      uStack_580 = 0xbbfc610f;
      uStack_57c = 0x3f7d15ad;
      uStack_578 = 0x3e19df55;
      uStack_574 = 0x3f800000;
      uStack_30 = 0xbbfc610f;
      uStack_2c = 0x3f7d15ad;
      uStack_28 = 0x3e19df55;
      uStack_24 = 0x3f800000;
      uVar1 = FVector::FVector(auStack_590,&uStack_10);
      uVar2 = FVector::FVector(auStack_5a0,&uStack_20);
      uVar3 = FVector::FVector(auStack_5b0,&uStack_30);
      uVar4 = FVector::FVector(auStack_5c0,&uStack_70);
      FpObjectFogBox::ChangeDataCup
                (0,uVar9,0x41200000,uVar7,0x42c80000,uVar8,0x3ca3d70a,
                 this->u32_210,uVar1,uVar2,uVar3,uVar4);
    }
    else if (uVar6 == 0x577) {
      uStack_4f0 = 0x41f3bb2c;
      uStack_4ec = 0xc180fb39;
      uStack_4e8 = 0x40fc8eb4;
      uStack_4e4 = 0x3f800000;
      uStack_10 = 0x41f3bb2c;
      uStack_c = 0xc180fb39;
      puStack_8 = (undefined *)0x40fc8eb4;
      uStack_4 = 0x3f800000;
      uStack_500 = 0x3d676534;
      uStack_4fc = 0x3e1a1230;
      uStack_4f8 = 0xbf7c81e4;
      uStack_4f4 = 0x3f800000;
      uStack_20 = 0x3d676534;
      uStack_1c = 0x3e1a1230;
      uStack_18 = 0xbf7c81e4;
      uStack_14 = 0x3f800000;
      uStack_510 = 0xbbfc610f;
      uStack_50c = 0x3f7d15ad;
      uStack_508 = 0x3e19df55;
      uStack_504 = 0x3f800000;
      uStack_30 = 0xbbfc610f;
      uStack_2c = 0x3f7d15ad;
      uStack_28 = 0x3e19df55;
      uStack_24 = 0x3f800000;
      uVar1 = FVector::FVector(auStack_520,&uStack_10);
      uVar2 = FVector::FVector(auStack_530,&uStack_20);
      uVar3 = FVector::FVector(auStack_540,&uStack_30);
      uVar4 = FVector::FVector(auStack_550,&uStack_70);
      FpObjectFogBox::ChangeDataCup
                (0,uVar9,0x41200000,uVar7,0x42c80000,uVar8,0x3ca3d70a,
                 this->u32_210,uVar1,uVar2,uVar3,uVar4);
    }
    else if (uVar6 == 0x536) {
      uStack_480 = 0x418a07f8;
      uStack_47c = 0xc1824bfd;
      uStack_478 = 0xc1ceafaf;
      uStack_474 = 0x3f800000;
      uStack_10 = 0x418a07f8;
      uStack_c = 0xc1824bfd;
      puStack_8 = (undefined *)0xc1ceafaf;
      uStack_4 = 0x3f800000;
      uStack_490 = 0x3f49ec5f;
      uStack_48c = 0x3e4481f5;
      uStack_488 = 0x3f15758e;
      uStack_484 = 0x3f800000;
      uStack_20 = 0x3f49ec5f;
      uStack_1c = 0x3e4481f5;
      uStack_18 = 0x3f15758e;
      uStack_14 = 0x3f800000;
      uStack_4a0 = 0xbe1e62dc;
      uStack_49c = 0x3f7b3db0;
      uStack_498 = 0xbde8a1e0;
      uStack_494 = 0x3f800000;
      uStack_30 = 0xbe1e62dc;
      uStack_2c = 0x3f7b3db0;
      uStack_28 = 0xbde8a1e0;
      uStack_24 = 0x3f800000;
      uVar1 = FVector::FVector(auStack_4b0,&uStack_10);
      uVar2 = FVector::FVector(auStack_4c0,&uStack_20);
      uVar3 = FVector::FVector(auStack_4d0,&uStack_30);
      uVar4 = FVector::FVector(auStack_4e0,&uStack_70);
      FpObjectFogBox::ChangeDataCup
                (0,uVar9,0x41200000,uVar7,0x42c80000,uVar8,0x3ca3d70a,
                 this->u32_210,uVar1,uVar2,uVar3,uVar4);
    }
    else if (uVar6 == 0x4bb) {
      uStack_410 = 0x41fed871;
      uStack_40c = 0xc181567c;
      uStack_408 = 0x40e601c1;
      uStack_404 = 0x3f800000;
      uStack_10 = 0x41fed871;
      uStack_c = 0xc181567c;
      puStack_8 = (undefined *)0x40e601c1;
      uStack_4 = 0x3f800000;
      uStack_420 = 0x3d4b72c5;
      uStack_41c = 0x3e0fa3fd;
      uStack_418 = 0xbf7d014b;
      uStack_414 = 0x3f800000;
      uStack_20 = 0x3d4b72c5;
      uStack_1c = 0x3e0fa3fd;
      uStack_18 = 0xbf7d014b;
      uStack_14 = 0x3f800000;
      uStack_430 = 0xbbc2efd4;
      uStack_42c = 0x3f7d77c9;
      uStack_428 = 0x3e0f8402;
      uStack_424 = 0x3f800000;
      uStack_30 = 0xbbc2efd4;
      uStack_2c = 0x3f7d77c9;
      uStack_28 = 0x3e0f8402;
      uStack_24 = 0x3f800000;
      uVar1 = FVector::FVector(auStack_440,&uStack_10);
      uVar2 = FVector::FVector(auStack_450,&uStack_20);
      uVar3 = FVector::FVector(auStack_460,&uStack_30);
      uVar4 = FVector::FVector(auStack_470,&uStack_70);
      FpObjectFogBox::ChangeDataCup
                (0,uVar9,0x41200000,uVar7,0x42c80000,uVar8,0x3ca3d70a,
                 this->u32_210,uVar1,uVar2,uVar3,uVar4);
    }
    else if (uVar6 == 0x442) {
      uStack_3a0 = 0x41c2a48f;
      uStack_39c = 0xc171ff24;
      uStack_398 = 0xc1a8121a;
      uStack_394 = 0x3f800000;
      uStack_10 = 0x41c2a48f;
      uStack_c = 0xc171ff24;
      puStack_8 = (undefined *)0xc1a8121a;
      uStack_4 = 0x3f800000;
      uStack_3b0 = 0x3f6eff2a;
      uStack_3ac = 0x3d139325;
      uStack_3a8 = 0x3eb66a12;
      uStack_3a4 = 0x3f800000;
      uStack_20 = 0x3f6eff2a;
      uStack_1c = 0x3d139325;
      uStack_18 = 0x3eb66a12;
      uStack_14 = 0x3f800000;
      uStack_3c0 = 0xbd0adcd3;
      uStack_3bc = 0x3f7fd567;
      uStack_3b8 = 0xbc481909;
      uStack_3b4 = 0x3f800000;
      uStack_30 = 0xbd0adcd3;
      uStack_2c = 0x3f7fd567;
      uStack_28 = 0xbc481909;
      uStack_24 = 0x3f800000;
      uVar1 = FVector::FVector(auStack_3d0,&uStack_10);
      uVar2 = FVector::FVector(auStack_3e0,&uStack_20);
      uVar3 = FVector::FVector(auStack_3f0,&uStack_30);
      uVar4 = FVector::FVector(auStack_400,&uStack_70);
      FpObjectFogBox::ChangeDataCup
                (0,uVar9,0x41200000,uVar7,0x42c80000,uVar8,0x3ca3d70a,
                 this->u32_210,uVar1,uVar2,uVar3,uVar4);
    }
    else if (uVar6 == 0x39f) {
      uStack_330 = 0xbeba367e;
      uStack_32c = 0xc19df1bd;
      uStack_328 = 0xc1bfee8e;
      uStack_324 = 0x3f800000;
      uStack_10 = 0xbeba367e;
      uStack_c = 0xc19df1bd;
      puStack_8 = (undefined *)0xc1bfee8e;
      uStack_4 = 0x3f800000;
      uStack_340 = 0xbee562bf;
      uStack_33c = 0x3eaf963a;
      uStack_338 = 0x3f535ad9;
      uStack_334 = 0x3f800000;
      uStack_20 = 0xbee562bf;
      uStack_1c = 0x3eaf963a;
      uStack_18 = 0x3f535ad9;
      uStack_14 = 0x3f800000;
      uStack_350 = 0x3e265a57;
      uStack_34c = 0x3f70790c;
      uStack_348 = 0xbe9aa348;
      uStack_344 = 0x3f800000;
      uStack_30 = 0x3e265a57;
      uStack_2c = 0x3f70790c;
      uStack_28 = 0xbe9aa348;
      uStack_24 = 0x3f800000;
      uVar1 = FVector::FVector(auStack_360,&uStack_10);
      uVar2 = FVector::FVector(auStack_370,&uStack_20);
      uVar3 = FVector::FVector(auStack_380,&uStack_30);
      uVar4 = FVector::FVector(auStack_390,&uStack_70);
      FpObjectFogBox::ChangeDataCup
                (0,uVar9,0x41200000,uVar7,0x42c80000,uVar8,0x3ca3d70a,
                 this->u32_210,uVar1,uVar2,uVar3,uVar4);
    }
    else if (uVar6 == 0x337) {
      uStack_2c0 = 0xc168627e;
      uStack_2bc = 0xc183150a;
      puStack_2b8 = &DAT_bfc00179;
      uStack_2b4 = 0x3f800000;
      uStack_10 = 0xc168627e;
      uStack_c = 0xc183150a;
      puStack_8 = &DAT_bfc00179;
      uStack_4 = 0x3f800000;
      uStack_2d0 = 0x3ee0be0e;
      uStack_2cc = 0x3f33f488;
      uStack_2c8 = 0xbf0f2852;
      uStack_2c4 = 0x3f800000;
      uStack_20 = 0x3ee0be0e;
      uStack_1c = 0x3f33f488;
      uStack_18 = 0xbf0f2852;
      uStack_14 = 0x3f800000;
      uStack_2e0 = 0xbeddaa0d;
      uStack_2dc = 0x3f360fb2;
      uStack_2d8 = 0x3f0dc66d;
      uStack_2d4 = 0x3f800000;
      uStack_30 = 0xbeddaa0d;
      uStack_2c = 0x3f360fb2;
      uStack_28 = 0x3f0dc66d;
      uStack_24 = 0x3f800000;
      uVar7 = 0x40400000;
      uVar8 = 0x41000000;
      uVar1 = FVector::FVector(auStack_2f0,&uStack_10);
      uVar2 = FVector::FVector(auStack_300,&uStack_20);
      uVar3 = FVector::FVector(auStack_310,&uStack_30);
      uVar4 = FVector::FVector(auStack_320,&uStack_70);
      FpObjectFogBox::ChangeDataCup
                (0,uVar9,0x41000000,uVar8,0x42c80000,uVar7,0x3bc49ba6,
                 this->u32_210,uVar1,uVar2,uVar3,uVar4);
    }
    else if (uVar6 == 0x2c1) {
      uStack_250 = 0xc0603f4f;
      uStack_24c = 0xc1095179;
      uStack_248 = 0xc18a3d85;
      uStack_244 = 0x3f800000;
      uStack_10 = 0xc0603f4f;
      uStack_c = 0xc1095179;
      puStack_8 = (undefined *)0xc18a3d85;
      uStack_4 = 0x3f800000;
      uStack_260 = 0xbf0a96a2;
      uStack_25c = 0xbe5a66dc;
      uStack_258 = 0x3f503233;
      uStack_254 = 0x3f800000;
      uStack_20 = 0xbf0a96a2;
      uStack_1c = 0xbe5a66dc;
      uStack_18 = 0x3f503233;
      uStack_14 = 0x3f800000;
      uStack_270 = 0xbdf3a68b;
      uStack_26c = 0x3f7a1be3;
      uStack_268 = 0x3e3544fe;
      uStack_264 = 0x3f800000;
      uStack_30 = 0xbdf3a68b;
      uStack_2c = 0x3f7a1be3;
      uStack_28 = 0x3e3544fe;
      uStack_24 = 0x3f800000;
      uVar1 = FVector::FVector(auStack_280,&uStack_10);
      uVar2 = FVector::FVector(auStack_290,&uStack_20);
      uVar3 = FVector::FVector(auStack_2a0,&uStack_30);
      uVar4 = FVector::FVector(auStack_2b0,&uStack_70);
      FpObjectFogBox::ChangeDataCup
                (0,uVar9,0x41200000,uVar7,0x42c80000,uVar8,0x3ca3d70a,
                 this->u32_210,uVar1,uVar2,uVar3,uVar4);
    }
    else if (uVar6 == 0x2a0) {
      uStack_1e0 = 0xbf7343a6;
      uStack_1dc = 0xc120df99;
      uStack_1d8 = 0xc160a969;
      uStack_1d4 = 0x3f800000;
      uStack_10 = 0xbf7343a6;
      uStack_c = 0xc120df99;
      puStack_8 = (undefined *)0xc160a969;
      uStack_4 = 0x3f800000;
      uStack_1f0 = 0x3f05b552;
      uStack_1ec = 0xbd1641f6;
      uStack_1e8 = 0x3f5a19db;
      uStack_1e4 = 0x3f800000;
      uStack_20 = 0x3f05b552;
      uStack_1c = 0xbd1641f6;
      uStack_18 = 0x3f5a19db;
      uStack_14 = 0x3f800000;
      uStack_200 = 0x3c948dc1;
      uStack_1fc = 0x3f7fd3d4;
      uStack_1f8 = 0x3d02b628;
      uStack_1f4 = 0x3f800000;
      uStack_30 = 0x3c948dc1;
      uStack_2c = 0x3f7fd3d4;
      uStack_28 = 0x3d02b628;
      uStack_24 = 0x3f800000;
      uVar1 = FVector::FVector(auStack_210,&uStack_10);
      uVar2 = FVector::FVector(auStack_220,&uStack_20);
      uVar3 = FVector::FVector(auStack_230,&uStack_30);
      uVar4 = FVector::FVector(auStack_240,&uStack_70);
      FpObjectFogBox::ChangeDataCup
                (0,uVar9,0x41200000,uVar7,0x42c80000,uVar8,0x3ca3d70a,
                 this->u32_210,uVar1,uVar2,uVar3,uVar4);
    }
    else if (uVar6 == 0x1d9) {
      uStack_170 = 0xc13198bc;
      uStack_16c = 0xc150ee00;
      uStack_168 = 0xc1c7fa6b;
      uStack_164 = 0x3f800000;
      uStack_10 = 0xc13198bc;
      uStack_c = 0xc150ee00;
      puStack_8 = (undefined *)0xc1c7fa6b;
      uStack_4 = 0x3f800000;
      uStack_180 = 0xbef64064;
      uStack_17c = 0xbd5460aa;
      uStack_178 = 0x3f600cd8;
      uStack_174 = 0x3f800000;
      uStack_20 = 0xbef64064;
      uStack_1c = 0xbd5460aa;
      uStack_18 = 0x3f600cd8;
      uStack_14 = 0x3f800000;
      uStack_190 = 0xbccb1898;
      uStack_18c = 0x3f7fa7db;
      uStack_188 = 0x3d3a8827;
      uStack_184 = 0x3f800000;
      uStack_30 = 0xbccb1898;
      uStack_2c = 0x3f7fa7db;
      uStack_28 = 0x3d3a8827;
      uStack_24 = 0x3f800000;
      uVar1 = FVector::FVector(auStack_1a0,&uStack_10);
      uVar2 = FVector::FVector(auStack_1b0,&uStack_20);
      uVar3 = FVector::FVector(auStack_1c0,&uStack_30);
      uVar4 = FVector::FVector(auStack_1d0,&uStack_70);
      FpObjectFogBox::ChangeDataCup
                (0,uVar9,0x41200000,uVar7,0x42c80000,uVar8,0x3ca3d70a,
                 this->u32_210,uVar1,uVar2,uVar3,uVar4);
    }
    else if (uVar6 == 0x142) {
      uStack_100 = 0xc21449ff;
      uStack_fc = 0xc03432d7;
      uStack_f8 = 0xc38b8652;
      uStack_f4 = 0x3f800000;
      uStack_10 = 0xc21449ff;
      uStack_c = 0xc03432d7;
      puStack_8 = (undefined *)0xc38b8652;
      uStack_4 = 0x3f800000;
      uStack_110 = 0x3e000eae;
      uStack_10c = 0xbd802fb6;
      uStack_108 = 0x3f7d7bfa;
      uStack_104 = 0x3f800000;
      uStack_20 = 0x3e000eae;
      uStack_1c = 0xbd802fb6;
      uStack_18 = 0x3f7d7bfa;
      uStack_14 = 0x3f800000;
      uStack_120 = 0x3c001712;
      uStack_11c = 0x3f7f7f7c;
      uStack_118 = 0x3d7e5c92;
      uStack_114 = 0x3f800000;
      uStack_30 = 0x3c001712;
      uStack_2c = 0x3f7f7f7c;
      uStack_28 = 0x3d7e5c92;
      uStack_24 = 0x3f800000;
      uVar1 = FVector::FVector(auStack_130,&uStack_10);
      uVar2 = FVector::FVector(auStack_140,&uStack_20);
      uVar3 = FVector::FVector(auStack_150,&uStack_30);
      uVar4 = FVector::FVector(auStack_160,&uStack_70);
      FpObjectFogBox::ChangeDataCup
                (0,uVar9,0x41200000,uVar7,0x42c80000,uVar8,0x3ca3d70a,
                 this->u32_210,uVar1,uVar2,uVar3,uVar4);
    }
    else if (uVar6 == 0x5b) {
      uStack_90 = 0x4167454e;
      uStack_8c = 0xc1034482;
      uStack_88 = 0x41244655;
      uStack_84 = 0x3f800000;
      uStack_10 = 0x4167454e;
      uStack_c = 0xc1034482;
      puStack_8 = (undefined *)0x41244655;
      uStack_4 = 0x3f800000;
      uStack_a0 = 0x3eeec765;
      uStack_9c = 0xbe05d399;
      uStack_98 = 0xbf5fe814;
      uStack_94 = 0x3f800000;
      uStack_20 = 0x3eeec765;
      uStack_1c = 0xbe05d399;
      uStack_18 = 0xbf5fe814;
      uStack_14 = 0x3f800000;
      uStack_b0 = 0x3d7d9664;
      uStack_ac = 0x3f7dcdd5;
      uStack_a8 = 0xbdebb774;
      uStack_a4 = 0x3f800000;
      uStack_30 = 0x3d7d9664;
      uStack_2c = 0x3f7dcdd5;
      uStack_28 = 0xbdebb774;
      uStack_24 = 0x3f800000;
      uVar1 = FVector::FVector(auStack_c0,&uStack_10);
      uVar2 = FVector::FVector(auStack_d0,&uStack_20);
      uVar3 = FVector::FVector(auStack_e0,&uStack_30);
      uVar4 = FVector::FVector(auStack_f0,&uStack_70);
      FpObjectFogBox::ChangeDataCup
                (0,uVar9,0x41200000,uVar7,0x42c80000,uVar8,0x3ca3d70a,
                 this->u32_210,uVar1,uVar2,uVar3,uVar4);
    }
  }
  return;
}

// JP: 0x0029d290  CalculateFunc__15FpObjectFogMCESFv  =  FpObjectFogMCES::CalculateFunc
void FpObjectFogMCES::CalculateFunc(void)

{
  return;
}

// JP: 0x0029d2a0  SetPacket__15FpObjectFogMCESFv  =  FpObjectFogMCES::SetPacket
void FpObjectFogMCES::SetPacket(undefined4 this)

{
  FpObjectFogMCES::FuncChangeData(this);
  return;
}

// JP: 0x0029d2d0  __ct__14FpObjectFogBoxFiPv  =  FpObjectFogBox::FpObjectFogBox
undefined8 FpObjectFogBox::FpObjectFogBox(undefined8 this)

{
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  int this;
  
  FpObject::FpObject(this);
  
  *(undefined1 **)(this + 0x1e4) = FpObjectFogBox::__vt;
  this->u32_210 = in_zero_lo;
  this->u32_214 = in_zero_hi;
  this->u32_218 = in_zero_udw;
  this->u32_21c = in_register_0000000c;
  this->u32_220 = in_zero_lo;
  this->u32_224 = in_zero_hi;
  this->u32_228 = in_zero_udw;
  this->u32_22c = in_register_0000000c;
  this->u32_230 = in_zero_lo;
  this->u32_234 = in_zero_hi;
  this->u32_238 = in_zero_udw;
  this->u32_23c = in_register_0000000c;
  this->u32_240 = in_zero_lo;
  this->u32_244 = in_zero_hi;
  this->u32_248 = in_zero_udw;
  this->u32_24c = in_register_0000000c;
  this->u32_210 = 0;
  this->u32_214 = 0;
  this->u32_218 = 0;
  this->u32_21c = 0x3f800000;
  this->u32_220 = 0;
  this->u32_224 = 0xc2c80000;
  this->u32_228 = 0x42c80000;
  this->u32_22c = 0x3f800000;
  this->u32_230 = 0x3dcccccd;
  this->u32_234 = 0;
  this->u32_238 = 0;
  this->u32_23c = 0x3f800000;
  this->u32_240 = 0x43000000;
  this->u32_244 = 0x43000000;
  this->u32_248 = 0x43000000;
  this->u32_24c = 0x43000000;
  this->u32_254 = 0x41200000;
  this->u32_250 = 0x41200000;
  this->u32_258 = 0x3f800000;
  return this;
}

// JP: 0x0029d470  __dt__14FpObjectFogBoxFv  =  FpObjectFogBox::~FpObjectFogBox
int FpObjectFogBox::~FpObjectFogBox(int this,short param_2)

{
  if (this != 0) {
    *(undefined1 **)(this + 0x1e4) = FpObjectFogBox::__vt;
    FpObject::~FpObject(this,0);
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}

// JP: 0x0029d4f0  ChangeDataCup__14FpObjectFogBoxF7FVector7FVector7FVector7FVectorfffffff  =  FpObjectFogBox::ChangeDataCup
void FpObjectFogBox::ChangeDataCup
               (undefined4 this,undefined4 param_2,undefined4 param_3,undefined4 param_4,
               undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined8 param_8,
               undefined1 (*param_9) [16],undefined8 param_10,undefined8 param_11,
               undefined8 *param_12)

{
  undefined8 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  undefined1 auVar6 [16];
  undefined1 auVar7 [16];
  undefined1 auStack_d0 [16];
  undefined1 auStack_c0 [16];
  undefined1 auStack_b0 [16];
  undefined1 auStack_a0 [16];
  undefined1 auStack_90 [16];
  undefined1 auStack_80 [16];
  undefined1 auStack_70 [8];
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined1 auStack_60 [16];
  undefined1 auStack_50 [8];
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined1 auStack_40 [16];
  undefined1 auStack_30 [8];
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined1 auStack_20 [16];
  undefined1 auStack_10 [16];
  
  FVector::Normalize(param_10);
  FVector::__amu(param_6,param_10);
  auVar6 = _lqc2(*(undefined1 (*) [16])param_11);
  auVar7 = _qmtc2(this);
  auVar6 = _vmulbc(auVar6,auVar7);
  auStack_80 = _sqc2(auVar6);
  FVector::FVector(auStack_10,auStack_80);
  auVar6 = _lqc2(*(undefined1 (*) [16])param_11);
  auVar7 = _qmtc2(param_2);
  auVar6 = _vmulbc(auVar6,auVar7);
  auStack_90 = _sqc2(auVar6);
  FVector::FVector(auStack_20,auStack_90);
  auVar6 = _lqc2(*param_9);
  auVar7 = _lqc2(*(undefined1 (*) [16])param_10);
  auVar6 = _vadd(auVar6,auVar7);
  auStack_c0 = _sqc2(auVar6);
  FVector::FVector(auStack_40,auStack_c0);
  auVar6 = _lqc2(auStack_40);
  auVar7 = _lqc2(auStack_10);
  auVar6 = _vadd(auVar6,auVar7);
  auStack_a0 = _sqc2(auVar6);
  FVector::FVector(auStack_30,auStack_a0);
  iVar5 = (int)param_8;
  iVar5->i32_210 = auStack_30._0_4_;
  iVar5->i32_214 = auStack_30._4_4_;
  iVar5->u32_218 = uStack_28;
  iVar5->u32_21c = uStack_24;
  auVar6 = _lqc2(*param_9);
  auVar7 = _lqc2(*(undefined1 (*) [16])param_10);
  auVar6 = _vadd(auVar6,auVar7);
  auStack_d0 = _sqc2(auVar6);
  FVector::FVector(auStack_60,auStack_d0);
  auVar6 = _lqc2(auStack_60);
  auVar7 = _lqc2(auStack_20);
  auVar6 = _vadd(auVar6,auVar7);
  auStack_b0 = _sqc2(auVar6);
  FVector::FVector(auStack_50,auStack_b0);
  iVar5->i32_220 = auStack_50._0_4_;
  iVar5->i32_224 = auStack_50._4_4_;
  iVar5->u32_228 = uStack_48;
  iVar5->u32_22c = uStack_44;
  FVector::OuterProduct(auStack_70,param_11,param_10);
  iVar5->i32_230 = auStack_70._0_4_;
  iVar5->i32_234 = auStack_70._4_4_;
  iVar5->u32_238 = uStack_68;
  iVar5->u32_23c = uStack_64;
  FVector::Normalize(iVar5 + 0x230);
  FVector::__amu(param_7,iVar5 + 0x230);
  uVar1 = *param_12;
  uVar2 = param_12->u32_1;
  uVar3 = *(undefined4 *)((int)param_12 + 0xc);
  iVar5->i32_240 = (int)uVar1;
  iVar5->i32_244 = (int)((ulong)uVar1 >> 0x20);
  iVar5->u32_248 = uVar2;
  iVar5->u32_24c = uVar3;
  iVar5->u32_250 = param_3;
  iVar5->u32_254 = param_4;
  iVar5->u32_258 = param_5;
  for (iVar4 = 0; iVar4 < iVar5->i32_1f8; iVar4 = iVar4 + 1) {
    (**(code **)(iVar5->i32_1e4 + 0x4c))(param_8,iVar4,1);
  }
  return;
}

// JP: 0x0029d780  CreateData__14FpObjectFogBoxFib  =  FpObjectFogBox::CreateData
void FpObjectFogBox::CreateData(int this,int param_2)

{
  int iVar1;
  undefined8 uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 *puVar6;
  float fVar7;
  float fVar8;
  undefined1 auVar9 [16];
  undefined1 auVar10 [16];
  undefined1 auStack_90 [16];
  undefined1 auStack_80 [16];
  undefined1 auStack_70 [8];
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined1 auStack_20 [16];
  float fStack_10;
  float fStack_c;
  float fStack_8;
  undefined4 uStack_4;
  
  puVar6 = (undefined4 *)(this->i32_1fc + param_2 * 0xf0);
  iVar3 = rand();
  fVar8 = ((float)iVar3 * 0.5) / 2.1474836e+09 + 0.5;
  rand();
  rand();
  *puVar6 = 0;
  puVar6[1] = 0;
  puVar6[2] = 0;
  uVar2 = this->u64_230;
  uVar4 = this->u32_238;
  uVar5 = this->u32_23c;
  puVar6[4] = (int)uVar2;
  puVar6[5] = (int)((ulong)uVar2 >> 0x20);
  puVar6[6] = uVar4;
  puVar6[7] = uVar5;
  puVar6[4] = (float)puVar6[4] * fVar8;
  puVar6[5] = (float)puVar6[5] * fVar8;
  puVar6[6] = (float)puVar6[6] * fVar8;
  uStack_30 = 0;
  uStack_2c = 0;
  uStack_28 = 0;
  uStack_24 = 0x3f800000;
  puVar6[8] = 0;
  puVar6[9] = 0;
  puVar6[10] = 0;
  puVar6[0xb] = 0x3f800000;
  uStack_3c = this->u32_254;
  uStack_40 = this->u32_250;
  uStack_38 = 0;
  uStack_34 = 0x3f800000;
  puVar6[0x10] = uStack_40;
  puVar6[0x11] = uStack_3c;
  puVar6[0x12] = 0;
  puVar6[0x13] = 0x3f800000;
  uStack_50 = 0;
  uStack_4c = 0;
  uStack_48 = 0;
  uStack_44 = 0x3f800000;
  puVar6[0x18] = 0;
  puVar6[0x19] = 0;
  puVar6[0x1a] = 0;
  puVar6[0x1b] = 0x3f800000;
  uStack_60 = 0x3f800000;
  uStack_5c = 0x3f800000;
  uStack_58 = 0x3f800000;
  uStack_54 = 0x3f800000;
  puVar6[0x14] = 0x3f800000;
  puVar6[0x15] = 0x3f800000;
  puVar6[0x16] = 0x3f800000;
  puVar6[0x17] = 0x3f800000;
  uVar2 = this->u64_240;
  uVar4 = this->u32_248;
  uVar5 = this->u32_24c;
  puVar6[0x2c] = (int)uVar2;
  puVar6[0x2d] = (int)((ulong)uVar2 >> 0x20);
  puVar6[0x2e] = uVar4;
  puVar6[0x2f] = uVar5;
  puVar6[0x30] = 0;
  puVar6[0x31] = 0;
  puVar6[0x32] = 0;
  puVar6[0x33] = 0x3f800000;
  puVar6[0x34] = 0x3f800000;
  puVar6[0x35] = 0;
  puVar6[0x36] = 0x3f800000;
  puVar6[0x37] = 0x3f800000;
  auVar9 = _lqc2(*(undefined1 (*) [16])(this + 0x220));
  auVar10 = _lqc2(*(undefined1 (*) [16])(this + 0x210));
  auVar9 = _vsub(auVar9,auVar10);
  auStack_80 = _sqc2(auVar9);
  FVector::FVector(&fStack_10,auStack_80);
  iVar3 = rand();
  fStack_10 = fStack_10 * ((float)iVar3 / 2.1474836e+09);
  iVar3 = rand();
  fStack_c = fStack_c * ((float)iVar3 / 2.1474836e+09);
  iVar3 = rand();
  fStack_8 = fStack_8 * ((float)iVar3 / 2.1474836e+09);
  auVar10 = _lqc2(*(undefined1 (*) [16])(this + 0x210));
  auVar9._4_4_ = fStack_c;
  auVar9._0_4_ = fStack_10;
  auVar9._8_4_ = fStack_8;
  auVar9._12_4_ = uStack_4;
  auVar9 = _lqc2(auVar9);
  auVar9 = _vadd(auVar10,auVar9);
  auStack_90 = _sqc2(auVar9);
  FVector::FVector(auStack_70,auStack_90);
  puVar6[0xc] = auStack_70._0_4_;
  puVar6[0xd] = auStack_70._4_4_;
  puVar6[0xe] = uStack_68;
  puVar6[0xf] = uStack_64;
  iVar3 = this->i32_1f8;
  fVar8 = this->f32_258;
  iVar1 = this->i32_1f8;
  fVar7 = this->f32_258;
  FVector::FVector(auStack_20,this + 0x230);
  FVector::Normalize(auStack_20);
  FVector::__amu((fVar8 * (float)(iVar3 - param_2)) / (float)iVar1 - fVar7 * 0.5,auStack_20);
  auVar10 = _lqc2(auStack_20);
  auVar9 = _lqc2(*(undefined1 (*) [16])(puVar6 + 0xc));
  auVar9 = _vadd(auVar9,auVar10);
  auVar9 = _sqc2(auVar9);
  *(undefined1 (*) [16])(puVar6 + 0xc) = auVar9;
  return;
}

// JP: 0x0029dc10  Init__14FpObjectFogBoxFib  =  FpObjectFogBox::Init
void FpObjectFogBox::Init(int this,undefined4 param_2,char param_3)

{
  undefined4 uVar1;
  undefined8 uVar2;
  int iVar3;
  
  this->u32_1f8 = param_2;
  this->u32_1f4 = param_2;
  iVar3 = this->i32_1f8;
  uVar2 = __nwa(iVar3 * 0xf0 + 0x10);
  uVar1 = __construct_new_array(uVar2,0x299b50,0,0xf0,iVar3);
  this->u32_1fc = uVar1;
  memset(*(void **)(this + 0x1fc),0,(long)(this->i32_1f8 * 0xf0));
  for (iVar3 = 0; iVar3 < this->i32_1f8; iVar3 = iVar3 + 1) {
    (**(code **)(this->i32_1e4 + 0x4c))(this,iVar3,1);
  }
  this->u32_1e0 = 0xffffffff;
  this->u8_14 = this->u8_14 & 0xfe | 1;
  this->u16_14 = this->u16_14 & 0xe01f;
  if (param_3 == '\0') {
    PutiObject::SetRegTest(this,0x33001);
  }
  else {
    PutiObject::SetRegTest(this,0x73001);
  }
  PutiObject::SetRegAlpha(this,0x44);
  return;
}

// JP: 0x0029ddc0  Calculate__14FpObjectFogBoxFv  =  FpObjectFogBox::Calculate
undefined4 FpObjectFogBox::Calculate(int this)

{
  (**(code **)(this->i32_1e4 + 0x48))();
  return 1;
}

// JP: 0x0029de00  CalculateFunc__14FpObjectFogBoxFv  =  FpObjectFogBox::CalculateFunc
void FpObjectFogBox::CalculateFunc(int this)

{
  int iVar1;
  int iVar2;
  float fVar3;
  undefined1 auVar4 [16];
  undefined1 auVar5 [16];
  undefined1 auStack_20 [16];
  undefined1 auStack_10 [12];
  undefined4 uStack_4;
  
  fVar3 = (float)FpPrim::GetFrameSpeed(this->u32_8);
  iVar2 = this->i32_1fc;
  for (iVar1 = 0; iVar1 < this->i32_1f8; iVar1 = iVar1 + 1) {
    iVar2->f32_4 = iVar2->f32_4 + fVar3;
    auVar4 = _lqc2(*(undefined1 (*) [16])(iVar2 + 0x10));
    auVar5 = _qmtc2(fVar3);
    auVar4 = _vmulbc(auVar4,auVar5);
    auStack_20 = _sqc2(auVar4);
    FVector::FVector(auStack_10,auStack_20);
    uStack_4 = 0;
    auVar4._12_4_ = 0;
    auVar4._0_12_ = auStack_10;
    auVar5 = _lqc2(auVar4);
    auVar4 = _lqc2(*(undefined1 (*) [16])(iVar2 + 0x30));
    auVar4 = _vadd(auVar4,auVar5);
    auVar4 = _sqc2(auVar4);
    *(undefined1 (*) [16])(iVar2 + 0x30) = auVar4;
    iVar2 = iVar2 + 0xf0;
  }
  (**(code **)(this->i32_1e4 + 0x44))();
  return;
}

// JP: 0x0029df00  SetPacket__14FpObjectFogBoxFv  =  FpObjectFogBox::SetPacket
/* WARNING: Removing unreachable block (ram,0x0029df80) */

void FpObjectFogBox::SetPacket(int this)

{
  float in_zero_lo;
  float in_zero_hi;
  float in_zero_udw;
  float in_register_0000000c;
  float *pfVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  float fVar5;
  uint uVar6;
  float fStack_70;
  float fStack_6c;
  float fStack_68;
  float fStack_64;
  float *pfStack_5c;
  float *pfStack_58;
  float *pfStack_54;
  float *pfStack_50;
  float *pfStack_4c;
  float *pfStack_48;
  float *pfStack_44;
  uint *puStack_40;
  uint *puStack_3c;
  float *pfStack_38;
  float *pfStack_34;
  ulong *puStack_30;
  ulong *puStack_2c;
  float *pfStack_28;
  uint uStack_24;
  float fStack_20;
  float fStack_1c;
  undefined4 uStack_18;
  float fStack_14;
  int iStack_10;
  
  fStack_14 = 1.0;
  if (LSDPlayer::sys != 0) {
    uStack_18 = LSDPlayer::sys->u32_1c;
    fVar5 = LSDPlayer::sys->f32_1c * (float)LSDPlayer::sys->u16_3e;
    if (fVar5 < 2.1474836e+09) {
      uVar6 = (uint)fVar5;
    }
    else {
      uVar6 = (int)(fVar5 - 2.1474836e+09) | 0x80000000;
    }
    if (uVar6 < 0x5c) {
      fStack_14 = (float)uVar6 / 100.0;
    }
    else if (uVar6 < 0xc0) {
      fStack_14 = (float)(uVar6 - 0x5b) / 100.0;
    }
  }
  pfStack_28 = *(float **)(this + 0x88);
  *pfStack_28 = in_zero_lo;
  pfStack_28[1] = in_zero_hi;
  pfStack_28[2] = in_zero_udw;
  pfStack_28[3] = in_register_0000000c;
  *pfStack_28 = (float)(&DAT_10000001 + this->i32_1f8 * 0xc);
  pfStack_28[3] = (float)(this->i32_1f8 * 0xc + 1U | 0x50000000);
  this->i32_88 = this->i32_88 + 0x10;
  puStack_30 = *(ulong **)(this + 0x88);
  *puStack_30 = (long)(this->i32_1f8 << 2) | 0x302a400000008000;
  puStack_30[1] = 0x412;
  this->i32_88 = this->i32_88 + 0x10;
  pfVar1 = *(float **)(this + 0x88);
  iVar2 = this->i32_1fc;
  fStack_70 = in_zero_lo;
  fStack_6c = in_zero_hi;
  fStack_68 = in_zero_udw;
  fStack_64 = in_register_0000000c;
  pfStack_38 = pfVar1;
  pfStack_34 = pfVar1;
  puStack_2c = puStack_30;
  iStack_10 = this;
  for (iVar4 = 0; iVar4 < iStack_10->i32_1f8; iVar4 = iVar4 + 1) {
    fStack_1c = iVar2->f32_bc * fStack_14;
    if (fStack_1c < 0.0) {
      fStack_1c = 0.0;
    }
    else if (128.0 < fStack_1c) {
      fStack_1c = 128.0;
    }
    if (0.0 < fStack_1c) {
      for (iVar3 = 0; iVar3 < 4; iVar3 = iVar3 + 1) {
        fStack_20 = (float)PutiObject::RotTransPer
                                     (iStack_10,iVar2 + iVar3 * 0x10 + 0x70,&fStack_70);
        uStack_24 = PutiObject::ClipFlag(iStack_10);
        *pfVar1 = *(float *)(iVar2 + iVar3 * 8 + 0xc0) * fStack_20;
        pfVar1[1] = *(float *)(iVar2 + iVar3 * 8 + 0xc4) * fStack_20;
        pfVar1[2] = fStack_20;
        iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
        puStack_40 = *(uint **)(iStack_10 + 0x88);
        fVar5 = iVar2->f32_b0;
        if (fVar5 < 2.1474836e+09) {
          uVar6 = (uint)fVar5;
        }
        else {
          uVar6 = (int)(fVar5 - 2.1474836e+09) | 0x80000000;
        }
        *puStack_40 = uVar6;
        fVar5 = iVar2->f32_b4;
        if (fVar5 < 2.1474836e+09) {
          uVar6 = (uint)fVar5;
        }
        else {
          uVar6 = (int)(fVar5 - 2.1474836e+09) | 0x80000000;
        }
        puStack_40[1] = uVar6;
        fVar5 = iVar2->f32_b8;
        if (fVar5 < 2.1474836e+09) {
          uVar6 = (uint)fVar5;
        }
        else {
          uVar6 = (int)(fVar5 - 2.1474836e+09) | 0x80000000;
        }
        puStack_40[2] = uVar6;
        if (fStack_1c < 2.1474836e+09) {
          uVar6 = (uint)fStack_1c;
        }
        else {
          uVar6 = (int)(fStack_1c - 2.1474836e+09) | 0x80000000;
        }
        puStack_40[3] = uVar6;
        iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
        pfStack_48 = *(float **)(iStack_10 + 0x88);
        if ((iVar3 < 2) || ((uStack_24 & 0x3ffff) != 0)) {
          fStack_64 = 4.59177e-41;
        }
        *pfStack_48 = fStack_70;
        pfStack_48[1] = fStack_6c;
        pfStack_48[2] = fStack_68;
        pfStack_48[3] = fStack_64;
        iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
        pfVar1 = *(float **)(iStack_10 + 0x88);
        pfStack_50 = pfVar1;
        pfStack_4c = pfVar1;
        pfStack_44 = pfStack_48;
        puStack_3c = puStack_40;
      }
    }
    else {
      for (iVar3 = 0; iVar3 < 4; iVar3 = iVar3 + 1) {
        *pfVar1 = in_zero_lo;
        pfVar1[1] = in_zero_hi;
        pfVar1[2] = in_zero_udw;
        pfVar1[3] = in_register_0000000c;
        iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
        pfStack_58 = *(float **)(iStack_10 + 0x88);
        *pfStack_58 = in_zero_lo;
        pfStack_58[1] = in_zero_hi;
        pfStack_58[2] = in_zero_udw;
        pfStack_58[3] = in_register_0000000c;
        iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
        pfStack_5c = *(float **)(iStack_10 + 0x88);
        *pfStack_5c = in_zero_lo;
        pfStack_5c[1] = in_zero_hi;
        pfStack_5c[2] = in_zero_udw;
        pfStack_5c[3] = in_register_0000000c;
        pfStack_5c[3] = 4.59177e-41;
        iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
        pfVar1 = *(float **)(iStack_10 + 0x88);
        pfStack_54 = pfStack_58;
      }
    }
    iVar2 = iVar2 + 0xf0;
  }
  return;
}

// JP: 0x0029e590  setZtest__6FpPrimFb  =  FpPrim::setZtest
void FpPrim::setZtest(int this,undefined1 param_2)

{
  this->u8_58 = param_2;
  return;
}

// JP: 0x0029e5c0  SetDrawFlag__6FpPrimFb  =  FpPrim::SetDrawFlag
void FpPrim::SetDrawFlag(int this,undefined1 param_2)

{
  this->u8_68 = param_2;
  return;
}

// JP: 0x0029e610  __ct__7FpTorchFv  =  FpTorch::FpTorch
undefined8 FpTorch::FpTorch(undefined8 this)

{
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  undefined4 *puVar1;
  int this;
  
  FpPrim::FpPrim(this);
  
  *(undefined1 **)(this + 0x10) = FpTorch::__vt;
  this->u32_1c = 0x405dd0;
  this->u32_70 = in_zero_lo;
  this->u32_74 = in_zero_hi;
  this->u32_78 = in_zero_udw;
  this->u32_7c = in_register_0000000c;
  puVar1 = (undefined4 *)(this + 0x80);
  do {
    *puVar1 = in_zero_lo;
    puVar1[1] = in_zero_hi;
    puVar1[2] = in_zero_udw;
    puVar1[3] = in_register_0000000c;
    puVar1 = puVar1 + 4;
  } while (puVar1 != (undefined4 *)(this + 0xb0));
  this->u32_70 = 0;
  this->u32_74 = 0;
  this->u32_78 = 0;
  this->u32_7c = 0x3f800000;
  this->u32_80 = 0x43000000;
  this->u32_84 = 0x43000000;
  this->u32_88 = 0x43000000;
  this->u32_8c = 0x43000000;
  this->u32_90 = 0x43000000;
  this->u32_94 = 0x43000000;
  this->u32_98 = 0x43000000;
  this->u32_9c = 0x43000000;
  this->u32_a0 = 0x43000000;
  this->u32_a4 = 0x43000000;
  this->u32_a8 = 0x43000000;
  this->u32_ac = 0x43000000;
  this->u32_b0 = 0;
  return this;
}

// JP: 0x0029e7d0  __dt__7FpTorchFv  =  FpTorch::~FpTorch
int FpTorch::~FpTorch(int this,short param_2)

{
  if (this != 0) {
    *(undefined1 **)(this + 0x10) = FpTorch::__vt;
    this->u32_1c = 0x405dd0;
    FpPrim::~FpPrim(this,0);
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}

// JP: 0x0029e860  SetColor1__7FpTorchFUcUcUcUc  =  FpTorch::SetColor1
undefined4
FpTorch::SetColor1(int this,ulong param_2,ulong param_3,ulong param_4,ulong param_5)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  
  if ((long)param_2 < 0) {
    fVar1 = (float)(param_2 & 0xffffffff);
  }
  else {
    fVar1 = (float)(int)param_2;
  }
  if ((long)param_3 < 0) {
    fVar2 = (float)(param_3 & 0xffffffff);
  }
  else {
    fVar2 = (float)(int)param_3;
  }
  if ((long)param_4 < 0) {
    fVar3 = (float)(param_4 & 0xffffffff);
  }
  else {
    fVar3 = (float)(int)param_4;
  }
  if ((long)param_5 < 0) {
    fVar4 = (float)(param_5 & 0xffffffff);
  }
  else {
    fVar4 = (float)(int)param_5;
  }
  this->f32_80 = fVar1 * 0.5019608;
  this->f32_84 = fVar2 * 0.5019608;
  this->f32_88 = fVar3 * 0.5019608;
  this->f32_8c = fVar4 * 0.5019608;
  return 1;
}

// JP: 0x0029e990  SetColor2__7FpTorchFUcUcUcUc  =  FpTorch::SetColor2
undefined4
FpTorch::SetColor2(int this,ulong param_2,ulong param_3,ulong param_4,ulong param_5)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  
  if ((long)param_2 < 0) {
    fVar1 = (float)(param_2 & 0xffffffff);
  }
  else {
    fVar1 = (float)(int)param_2;
  }
  if ((long)param_3 < 0) {
    fVar2 = (float)(param_3 & 0xffffffff);
  }
  else {
    fVar2 = (float)(int)param_3;
  }
  if ((long)param_4 < 0) {
    fVar3 = (float)(param_4 & 0xffffffff);
  }
  else {
    fVar3 = (float)(int)param_4;
  }
  if ((long)param_5 < 0) {
    fVar4 = (float)(param_5 & 0xffffffff);
  }
  else {
    fVar4 = (float)(int)param_5;
  }
  this->f32_90 = fVar1 * 0.5019608;
  this->f32_94 = fVar2 * 0.5019608;
  this->f32_98 = fVar3 * 0.5019608;
  this->f32_9c = fVar4 * 0.5019608;
  return 1;
}

// JP: 0x0029eac0  SetColor3__7FpTorchFUcUcUcUc  =  FpTorch::SetColor3
undefined4
FpTorch::SetColor3(int this,ulong param_2,ulong param_3,ulong param_4,ulong param_5)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  
  if ((long)param_2 < 0) {
    fVar1 = (float)(param_2 & 0xffffffff);
  }
  else {
    fVar1 = (float)(int)param_2;
  }
  if ((long)param_3 < 0) {
    fVar2 = (float)(param_3 & 0xffffffff);
  }
  else {
    fVar2 = (float)(int)param_3;
  }
  if ((long)param_4 < 0) {
    fVar3 = (float)(param_4 & 0xffffffff);
  }
  else {
    fVar3 = (float)(int)param_4;
  }
  if ((long)param_5 < 0) {
    fVar4 = (float)(param_5 & 0xffffffff);
  }
  else {
    fVar4 = (float)(int)param_5;
  }
  this->f32_a0 = fVar1 * 0.5019608;
  this->f32_a4 = fVar2 * 0.5019608;
  this->f32_a8 = fVar3 * 0.5019608;
  this->f32_ac = fVar4 * 0.5019608;
  return 1;
}

// JP: 0x0029ebf0  SetPos1__7FpTorchF7FVectorb  =  FpTorch::SetPos1
undefined4 FpTorch::SetPos1(int this,undefined8 param_2,long param_3)

{
  int iVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined1 auVar7 [16];
  undefined1 auVar8 [16];
  undefined1 auStack_60 [16];
  undefined1 auStack_50 [16];
  undefined1 auStack_40 [16];
  float fStack_30;
  float fStack_2c;
  float fStack_28;
  undefined4 uStack_24;
  undefined1 auStack_20 [12];
  undefined4 uStack_14;
  undefined1 auStack_10 [16];
  
  FVector::FVector(auStack_10,this + 0x70);
  puVar6 = (undefined4 *)param_2;
  this->u32_70 = *puVar6;
  this->u32_74 = puVar6[1];
  this->u32_78 = puVar6[2];
  iVar1 = this->i32_28;
  auVar7 = _lqc2(*(undefined1 (*) [16])(this + 0x70));
  auVar8 = _lqc2(auStack_10);
  auVar7 = _vsub(auVar7,auVar8);
  auStack_60 = _sqc2(auVar7);
  FVector::FVector(auStack_20,auStack_60);
  uStack_14 = 0;
  if (param_3 == 0) {
    iVar1->u8_204 = 1;
    iVar5 = iVar1->i32_1fc;
    for (iVar4 = 0; iVar4 < iVar1->i32_1f4; iVar4 = iVar4 + 1) {
      iVar5->u8_e0 = iVar5->u8_e0 & 0xfe | 1;
    }
    iVar4 = iVar1->i32_1fc + iVar1->i32_1f4 * 0xf0;
    for (iVar5 = iVar1->i32_1f4; iVar5 < iVar1->i32_1f8; iVar5 = iVar5 + 1) {
      iVar4->u8_e0 = iVar4->u8_e0 & 0xfe;
      auVar7._12_4_ = 0;
      auVar7._0_12_ = auStack_20;
      auVar8 = _lqc2(auVar7);
      auVar7 = _lqc2(*(undefined1 (*) [16])(iVar4 + 0x30));
      auVar7 = _vadd(auVar7,auVar8);
      auVar7 = _sqc2(auVar7);
      *(undefined1 (*) [16])(iVar4 + 0x30) = auVar7;
    }
  }
  else {
    iVar5 = iVar1->i32_1fc;
    for (iVar4 = 0; iVar4 < iVar1->i32_1f8; iVar4 = iVar4 + 1) {
      auVar8._12_4_ = 0;
      auVar8._0_12_ = auStack_20;
      auVar8 = _lqc2(auVar8);
      auVar7 = _lqc2(*(undefined1 (*) [16])(iVar5 + 0x30));
      auVar7 = _vadd(auVar7,auVar8);
      auVar7 = _sqc2(auVar7);
      *(undefined1 (*) [16])(iVar5 + 0x30) = auVar7;
      iVar5 = iVar5 + 0xf0;
    }
  }
  fStack_30 = this->f32_b0 * 0.5;
  fStack_2c = fStack_30 * 2.0;
  uStack_24 = 0x3f800000;
  puVar6[1] = (float)puVar6[1] - fStack_30 * 1.1;
  fStack_28 = fStack_30;
  uVar2 = FVector::FVector(auStack_40,param_2);
  uVar3 = FVector::FVector(auStack_50,&fStack_30);
  FpObject::UpdateBBox(0x42c80000,iVar1,uVar2,uVar3);
  return 1;
}

// JP: 0x0029ee50  Create__7FpTorchF7FVector7FVector7FVector7FVectorf  =  FpTorch::Create
void FpTorch::Create
               (undefined4 this,undefined8 param_2,undefined8 *param_3,undefined8 *param_4,
               undefined8 *param_5,undefined8 *param_6)

{
  long lVar1;
  undefined8 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  
  iVar5 = (int)param_2;
  uVar2 = *param_3;
  uVar3 = param_3->u32_1;
  uVar4 = *(undefined4 *)((int)param_3 + 0xc);
  iVar5->i32_70 = (int)uVar2;
  iVar5->i32_74 = (int)((ulong)uVar2 >> 0x20);
  iVar5->u32_78 = uVar3;
  iVar5->u32_7c = uVar4;
  iVar5->u32_b0 = this;
  iVar5->f32_74 = iVar5->f32_74 - iVar5->f32_b0 / 4.0;
  uVar2 = *param_4;
  uVar3 = param_4->u32_1;
  uVar4 = *(undefined4 *)((int)param_4 + 0xc);
  iVar5->i32_80 = (int)uVar2;
  iVar5->i32_84 = (int)((ulong)uVar2 >> 0x20);
  iVar5->u32_88 = uVar3;
  iVar5->u32_8c = uVar4;
  uVar2 = *param_5;
  uVar3 = param_5->u32_1;
  uVar4 = *(undefined4 *)((int)param_5 + 0xc);
  iVar5->i32_90 = (int)uVar2;
  iVar5->i32_94 = (int)((ulong)uVar2 >> 0x20);
  iVar5->u32_98 = uVar3;
  iVar5->u32_9c = uVar4;
  uVar2 = *param_6;
  uVar3 = param_6->u32_1;
  uVar4 = *(undefined4 *)((int)param_6 + 0xc);
  iVar5->i32_a0 = (int)uVar2;
  iVar5->i32_a4 = (int)((ulong)uVar2 >> 0x20);
  iVar5->u32_a8 = uVar3;
  iVar5->u32_ac = uVar4;
  PutiPrim::SetTexture(param_2,BgEffectMan::eff->i32_1c + 100,0);
  if (iVar5->i8_58 == '\0') {
    iVar5->u8_24 = iVar5->u8_24 & 0xfe | 1;
  }
  lVar1 = __nw(0x210);
  uVar2 = 0;
  if (lVar1 != 0) {
    uVar2 = FpObjectTorch::FpObjectTorch(lVar1,500,0);
  }
  PutiPrim::AddObject(param_2,uVar2);
  (**(code **)(*(int *)((int)uVar2 + 0x1e4) + 0x40))(uVar2,0x28,iVar5->u8_58);
  PutiManager::AddPrim(BgEffectMan::eff,iVar5->u32_54,param_2);
  return;
}

// JP: 0x0029efa0  Create__7FpTorchFPv  =  FpTorch::Create
void FpTorch::Create(int this,int param_2)

{
  int iVar1;
  undefined2 *puVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  uint *puVar7;
  bool bVar8;
  bool bVar9;
  undefined1 auStack_d0 [16];
  undefined1 auStack_c0 [16];
  undefined1 auStack_b0 [16];
  undefined1 auStack_a0 [16];
  undefined1 auStack_90 [16];
  undefined1 auStack_80 [16];
  undefined1 auStack_70 [16];
  undefined1 auStack_60 [16];
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined1 auStack_40 [12];
  undefined4 uStack_34;
  uint uStack_2c;
  uint uStack_28;
  undefined2 uStack_24;
  undefined2 uStack_22;
  int iStack_20;
  int iStack_10;
  
  iStack_20 = this;
  iStack_10 = param_2;
  FVector::FVector(auStack_40,param_2);
  puVar7 = (uint *)(param_2 + 0x10);
  uStack_50 = 0;
  uStack_4c = 0;
  uStack_48 = 0;
  uStack_44 = 0;
  FVector::FVector(auStack_60,auStack_40);
  bVar9 = true;
  bVar8 = false;
  puVar2 = (undefined2 *)FpPrim::InitFpFlag(uStack_34,iStack_20);
  uStack_24 = *puVar2;
  uStack_22 = puVar2[1];
  memset(&uStack_28,0,4);
  if ((long)((ulong)uStack_22._1_1_ << 0x3a) < 0) {
    uStack_28 = *puVar7;
    puVar7 = (uint *)(param_2 + 0x20);
    bVar9 = (uStack_28 & 1) != 0;
    bVar8 = (long)((ulong)(byte)uStack_28 << 0x3e) < 0;
  }
  FVector::FVector(auStack_70,puVar7);
  FVector::FVector(auStack_80,puVar7 + 4);
  FVector::FVector(auStack_90,puVar7 + 8);
  uStack_2c = puVar7[0xc];
  uVar3 = FVector::FVector(auStack_a0,auStack_40);
  uVar4 = FVector::FVector(auStack_b0,auStack_70);
  uVar5 = FVector::FVector(auStack_c0,auStack_80);
  uVar6 = FVector::FVector(auStack_d0,auStack_90);
  FpTorch::Create(uStack_2c,iStack_20,uVar3,uVar4,uVar5,uVar6);
  iVar1 = iStack_20->i32_28;
  if (iVar1->i32_200 != 0) {
    *(byte *)(iVar1->i32_200 + 1) = *(byte *)(iVar1->i32_200 + 1) & 0xfe | bVar9;
  }
  if (iVar1->i32_200 != 0) {
    *(byte *)(iVar1->i32_200 + 1) =
         *(byte *)(iVar1->i32_200 + 1) & 0xfd | bVar8 << 1;
  }
  return;
}

// JP: 0x0029f210  __ct__13FpObjectTorchFiPv  =  FpObjectTorch::FpObjectTorch
int FpObjectTorch::FpObjectTorch(int this,undefined4 param_2,undefined4 param_3)

{
  FpObject::FpObject(this,param_2,param_3);
  *(undefined1 **)(this + 0x1e4) = FpObjectTorch::__vt;
  return this;
}

// JP: 0x0029f260  __dt__13FpObjectTorchFv  =  FpObjectTorch::~FpObjectTorch
int FpObjectTorch::~FpObjectTorch(int this,short param_2)

{
  if (this != 0) {
    *(undefined1 **)(this + 0x1e4) = FpObjectTorch::__vt;
    FpObject::~FpObject(this,0);
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}

// JP: 0x0029f2e0  CreateData__13FpObjectTorchFib  =  FpObjectTorch::CreateData
void FpObjectTorch::CreateData(int this,int param_2,long param_3)

{
  undefined8 uVar1;
  int iVar2;
  float fVar3;
  float *pfVar4;
  float fVar5;
  undefined1 auVar6 [16];
  undefined1 auVar7 [16];
  undefined1 aauStack_b0 [6] [16];
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined1 auStack_40 [8];
  float fStack_38;
  float fStack_34;
  float fStack_30;
  float fStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined1 auStack_20 [16];
  undefined4 uStack_10;
  float fStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  pfVar4 = (float *)(this->i32_1fc + param_2 * 0xf0);
  iVar2 = this->i32_8;
  fStack_30 = iVar2->f32_b0;
  *pfVar4 = 35.0;
  if (param_3 == 0) {
    pfVar4[1] = 0.0;
  }
  else {
    pfVar4[1] = (float)(int)(((float)param_2 * *pfVar4) / (float)this->i32_1f8);
  }
  uStack_28 = 0;
  uStack_24 = 0x3f800000;
  pfVar4[0x10] = fStack_30;
  pfVar4[0x11] = fStack_30;
  pfVar4[0x12] = 0.0;
  pfVar4[0x13] = 1.0;
  uStack_10 = 0;
  fStack_c = -(fStack_30 / 20.0);
  uStack_8 = 0;
  uStack_4 = 0x3f800000;
  fVar5 = (fStack_30 / 20.0) * 0.4;
  fStack_2c = fStack_30;
  PutiObject::GetPos(fVar5,0,fVar5,auStack_40,&uStack_10);
  pfVar4[4] = auStack_40._0_4_;
  pfVar4[5] = auStack_40._4_4_;
  pfVar4[6] = fStack_38;
  pfVar4[7] = fStack_34;
  pfVar4[8] = -pfVar4[4];
  pfVar4[9] = pfVar4[5];
  pfVar4[10] = -pfVar4[6];
  pfVar4[0xb] = 0.0;
  *pfVar4 = *pfVar4 - (float)(int)(((pfVar4[4] * pfVar4[4] + pfVar4[6] * pfVar4[6]) * 40.0) /
                                  (fVar5 * fVar5 * 2.0));
  uVar1 = iVar2->u64_70;
  fVar5 = iVar2->f32_78;
  fVar3 = iVar2->f32_7c;
  pfVar4[0xc] = (float)uVar1;
  pfVar4[0xd] = (float)((ulong)uVar1 >> 0x20);
  pfVar4[0xe] = fVar5;
  pfVar4[0xf] = fVar3;
  auVar6 = _lqc2(*(undefined1 (*) [16])(pfVar4 + 4));
  auVar7 = _qmtc2(pfVar4[1]);
  auVar6 = _vmulbc(auVar6,auVar7);
  aauStack_b0[0] = _sqc2(auVar6);
  FVector::FVector(auStack_20,aauStack_b0);
  auVar7 = _lqc2(auStack_20);
  auVar6 = _lqc2(*(undefined1 (*) [16])(pfVar4 + 0xc));
  auVar6 = _vadd(auVar6,auVar7);
  auVar6 = _sqc2(auVar6);
  *(undefined1 (*) [16])(pfVar4 + 0xc) = auVar6;
  uStack_50 = 0x3f800000;
  uStack_4c = 0x3f800000;
  uStack_48 = 0x3f800000;
  uStack_44 = 0x3f800000;
  pfVar4[0x14] = 1.0;
  pfVar4[0x15] = 1.0;
  pfVar4[0x16] = 1.0;
  pfVar4[0x17] = 1.0;
  iVar2 = rand();
  pfVar4[0x18] = 0.0;
  pfVar4[0x19] = 0.0;
  pfVar4[0x1a] = ((float)iVar2 / 2.1474836e+09) * 6.2831855;
  pfVar4[0x1b] = 1.0;
  pfVar4[0x1c] = 0.0;
  pfVar4[0x1d] = 0.0;
  pfVar4[0x1e] = 0.0;
  pfVar4[0x1f] = 1.0;
  pfVar4[0x20] = 0.0;
  pfVar4[0x21] = 0.0;
  pfVar4[0x22] = 0.0;
  pfVar4[0x23] = 1.0;
  pfVar4[0x24] = 0.0;
  pfVar4[0x25] = 0.0;
  pfVar4[0x26] = 0.0;
  pfVar4[0x27] = 1.0;
  pfVar4[0x28] = 0.0;
  pfVar4[0x29] = 0.0;
  pfVar4[0x2a] = 0.0;
  pfVar4[0x2b] = 1.0;
  pfVar4[0x2c] = *(float *)(this->i32_8 + 0x80);
  pfVar4[0x2d] = *(float *)(this->i32_8 + 0x84);
  pfVar4[0x2e] = *(float *)(this->i32_8 + 0x88);
  pfVar4[0x2f] = *(float *)(this->i32_8 + 0x8c);
  pfVar4->u8_38 = pfVar4->u8_38 & 0xfe;
  return;
}

// JP: 0x0029f780  Init__13FpObjectTorchFib  =  FpObjectTorch::Init
void FpObjectTorch::Init(int this,undefined4 param_2,char param_3)

{
  undefined4 uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  int iVar4;
  undefined1 auStack_90 [16];
  undefined1 auStack_80 [16];
  undefined1 auStack_70 [16];
  undefined1 auStack_60 [4];
  float fStack_5c;
  float fStack_50;
  float fStack_4c;
  float fStack_48;
  undefined4 uStack_44;
  float fStack_34;
  int iStack_30;
  undefined4 uStack_20;
  char cStack_10;
  
  this->u32_1f4 = param_2;
  this->u32_1f8 = param_2;
  iVar4 = this->i32_1f8;
  iStack_30 = this;
  uStack_20 = param_2;
  cStack_10 = param_3;
  uVar2 = __nwa(iVar4 * 0xf0 + 0x10);
  uVar1 = __construct_new_array(uVar2,0x299b50,0,0xf0,iVar4);
  iStack_30->u32_1fc = uVar1;
  memset(*(void **)(iStack_30 + 0x1fc),0,(long)(iStack_30->i32_1f8 * 0xf0));
  for (iVar4 = 0; iVar4 < iStack_30->i32_1f8; iVar4 = iVar4 + 1) {
    FpObject::InitData(iStack_30,iVar4);
    (**(code **)(iStack_30->i32_1e4 + 0x4c))(iStack_30,iVar4,1);
  }
  iStack_30->u32_1e0 = 0xffffffff;
  iStack_30->u8_14 = iStack_30->u8_14 & 0xfe | 1;
  iStack_30->u16_14 = iStack_30->u16_14 & 0xe01f;
  if (cStack_10 == '\0') {
    PutiObject::SetRegTest(iStack_30,0x33001);
  }
  else {
    PutiObject::SetRegTest(iStack_30,0x73001);
  }
  fStack_50 = *(float *)(iStack_30->i32_8 + 0xb0) * 0.5;
  fStack_4c = fStack_50 * 2.0;
  uStack_44 = 0x3f800000;
  fStack_48 = fStack_50;
  fStack_34 = fStack_50;
  FVector::FVector(auStack_60,iStack_30->i32_8 + 0x70);
  fStack_5c = fStack_5c - fStack_34 * 1.1;
  uVar2 = FVector::FVector(auStack_70,auStack_60);
  uVar3 = FVector::FVector(auStack_80,&fStack_50);
  FpObject::InitBBox(0x42c80000,iStack_30,uVar2,uVar3,auStack_90,1,0);
  return;
}

// JP: 0x0029fa10  CalculateFunc__13FpObjectTorchFv  =  FpObjectTorch::CalculateFunc
void FpObjectTorch::CalculateFunc(undefined8 this)

{
  undefined1 auVar1 [16];
  int iVar2;
  float *pfVar3;
  int this;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  undefined1 auVar10 [16];
  undefined1 auVar11 [16];
  undefined1 auStack_f0 [16];
  undefined1 auStack_e0 [16];
  undefined1 auStack_d0 [16];
  undefined1 auStack_c0 [16];
  undefined1 auStack_b0 [16];
  undefined1 auStack_a0 [16];
  undefined1 auStack_90 [8];
  float fStack_88;
  float fStack_84;
  undefined1 auStack_80 [16];
  undefined1 auStack_70 [8];
  float fStack_68;
  float fStack_64;
  undefined1 auStack_60 [16];
  undefined1 auStack_50 [16];
  undefined1 auStack_40 [16];
  undefined8 uStack_30;
  float fStack_28;
  float fStack_24;
  undefined1 auStack_20 [16];
  undefined8 uStack_10;
  float fStack_8;
  float fStack_4;
  
  
  iVar2 = this->i32_8;
  fVar7 = (float)FpPrim::GetFrameSpeed(iVar2);
  FVector::FVector(&uStack_10,iVar2 + 0x80);
  FVector::FVector(auStack_20,iVar2 + 0x90);
  FVector::FVector(&uStack_30,iVar2 + 0xa0);
  pfVar3 = *(float **)(this + 0x1fc);
  for (iVar2 = 0; iVar2 < this->i32_1f8; iVar2 = iVar2 + 1) {
    pfVar3[1] = pfVar3[1] + fVar7;
    if (*pfVar3 <= pfVar3[1]) {
      (**(code **)(this->i32_1e4 + 0x4c))(this,iVar2,0);
    }
    else {
      pfVar3[0xc] = pfVar3[0xc] + pfVar3[4] * fVar7;
      pfVar3[0xd] = pfVar3[0xd] + pfVar3[5] * fVar7;
      pfVar3[0xe] = pfVar3[0xe] + pfVar3[6] * fVar7;
    }
    fVar5 = *pfVar3;
    fVar9 = fVar5 * 0.1;
    fVar8 = fVar9 + fVar5 * 0.4;
    fVar6 = fVar8 + fVar5 * 0.4;
    if (pfVar3[1] < fVar9) {
      pfVar3[0x2c] = (float)uStack_10;
      pfVar3[0x2d] = (float)((ulong)uStack_10 >> 0x20);
      pfVar3[0x2e] = fStack_8;
      pfVar3[0x2f] = fStack_4;
      pfVar3[0x2f] = pfVar3[0x2f] * (pfVar3[1] / fVar9);
    }
    else if (pfVar3[1] < fVar8) {
      fVar5 = (pfVar3[1] - fVar9) / (fVar5 * 0.4);
      auVar11 = _lqc2(auStack_20);
      auVar10._8_4_ = fStack_8;
      auVar10._0_8_ = uStack_10;
      auVar10._12_4_ = fStack_4;
      auVar10 = _lqc2(auVar10);
      auVar10 = _vsub(auVar11,auVar10);
      auStack_c0 = _sqc2(auVar10);
      FVector::FVector(auStack_60,auStack_c0);
      auVar10 = _lqc2(auStack_60);
      auVar11 = _qmtc2(fVar5);
      auVar10 = _vmulbc(auVar10,auVar11);
      auStack_a0 = _sqc2(auVar10);
      FVector::FVector(auStack_40,auStack_a0);
      auVar11._8_4_ = fStack_8;
      auVar11._0_8_ = uStack_10;
      auVar11._12_4_ = fStack_4;
      auVar10 = _lqc2(auVar11);
      auVar11 = _lqc2(auStack_40);
      auVar10 = _vadd(auVar10,auVar11);
      auStack_d0 = _sqc2(auVar10);
      FVector::FVector(auStack_70,auStack_d0);
      pfVar3[0x2c] = auStack_70._0_4_;
      pfVar3[0x2d] = auStack_70._4_4_;
      pfVar3[0x2e] = fStack_68;
      pfVar3[0x2f] = fStack_64;
    }
    else if (pfVar3[1] < fVar6) {
      fVar5 = (pfVar3[1] - fVar8) / (fVar5 * 0.4);
      auVar1._8_4_ = fStack_28;
      auVar1._0_8_ = uStack_30;
      auVar1._12_4_ = fStack_24;
      auVar10 = _lqc2(auVar1);
      auVar11 = _lqc2(auStack_20);
      auVar10 = _vsub(auVar10,auVar11);
      auStack_e0 = _sqc2(auVar10);
      FVector::FVector(auStack_80,auStack_e0);
      auVar10 = _lqc2(auStack_80);
      auVar11 = _qmtc2(fVar5);
      auVar10 = _vmulbc(auVar10,auVar11);
      auStack_b0 = _sqc2(auVar10);
      FVector::FVector(auStack_50,auStack_b0);
      auVar10 = _lqc2(auStack_20);
      auVar11 = _lqc2(auStack_50);
      auVar10 = _vadd(auVar10,auVar11);
      auStack_f0 = _sqc2(auVar10);
      FVector::FVector(auStack_90,auStack_f0);
      pfVar3[0x2c] = auStack_90._0_4_;
      pfVar3[0x2d] = auStack_90._4_4_;
      pfVar3[0x2e] = fStack_88;
      pfVar3[0x2f] = fStack_84;
    }
    else {
      pfVar3[0x2c] = (float)uStack_30;
      pfVar3[0x2d] = (float)((ulong)uStack_30 >> 0x20);
      pfVar3[0x2e] = fStack_28;
      pfVar3[0x2f] = fStack_24;
      pfVar3[0x2f] = pfVar3[0x2f] + -fStack_24 * ((pfVar3[1] - fVar6) / (fVar5 * 0.1));
    }
    pfVar3 = pfVar3 + 0x3c;
  }
  (**(code **)(this->i32_1e4 + 0x44))();
  return;
}

// JP: 0x0029fdd0  SetPacket__13FpObjectTorchFv  =  FpObjectTorch::SetPacket
void FpObjectTorch::SetPacket(int this)

{
  float in_zero_lo;
  float in_zero_hi;
  float in_zero_udw;
  float in_register_0000000c;
  float *pfVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  float fVar5;
  uint uVar6;
  float fStack_70;
  float fStack_6c;
  float fStack_68;
  float fStack_64;
  float *pfStack_4c;
  float *pfStack_48;
  float *pfStack_44;
  float *pfStack_40;
  uint *puStack_3c;
  uint *puStack_38;
  float *pfStack_34;
  float *pfStack_30;
  ulong *puStack_2c;
  ulong *puStack_28;
  float *pfStack_24;
  uint uStack_20;
  float fStack_1c;
  float fStack_18;
  float fStack_14;
  int iStack_10;
  
  fStack_14 = this->f32_1f0 * *(float *)(this->i32_8 + 0x5c);
  pfStack_24 = *(float **)(this + 0x88);
  *pfStack_24 = in_zero_lo;
  pfStack_24[1] = in_zero_hi;
  pfStack_24[2] = in_zero_udw;
  pfStack_24[3] = in_register_0000000c;
  *pfStack_24 = (float)(&DAT_10000001 + this->i32_1f8 * 0xc);
  pfStack_24[3] = (float)(this->i32_1f8 * 0xc + 1U | 0x50000000);
  this->i32_88 = this->i32_88 + 0x10;
  puStack_2c = *(ulong **)(this + 0x88);
  *puStack_2c = (long)(this->i32_1f8 << 2) | 0x302a400000008000;
  puStack_2c[1] = 0x412;
  this->i32_88 = this->i32_88 + 0x10;
  pfVar1 = *(float **)(this + 0x88);
  iStack_10 = this;
  if (this->i32_1f4 != 0) {
    iVar4 = this->i32_1fc;
    fStack_70 = in_zero_lo;
    fStack_6c = in_zero_hi;
    fStack_68 = in_zero_udw;
    fStack_64 = in_register_0000000c;
    pfStack_34 = pfVar1;
    pfStack_30 = pfVar1;
    puStack_28 = puStack_2c;
    for (iVar3 = 0; iVar3 < iStack_10->i32_1f4; iVar3 = iVar3 + 1) {
      fStack_18 = iVar4->f32_bc * fStack_14;
      if (fStack_18 < 0.0) {
        fStack_18 = 0.0;
      }
      else if (128.0 < fStack_18) {
        fStack_18 = 128.0;
      }
      for (iVar2 = 0; iVar2 < 4; iVar2 = iVar2 + 1) {
        fStack_1c = (float)PutiObject::RotTransPer
                                     (iStack_10,iVar4 + iVar2 * 0x10 + 0x70,&fStack_70);
        uStack_20 = PutiObject::ClipFlag(iStack_10);
        *pfVar1 = *(float *)(iVar4 + iVar2 * 8 + 0xc0) * fStack_1c;
        pfVar1[1] = *(float *)(iVar4 + iVar2 * 8 + 0xc4) * fStack_1c;
        pfVar1[2] = fStack_1c;
        iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
        puStack_3c = *(uint **)(iStack_10 + 0x88);
        fVar5 = iVar4->f32_b0;
        if (fVar5 < 2.1474836e+09) {
          uVar6 = (uint)fVar5;
        }
        else {
          uVar6 = (int)(fVar5 - 2.1474836e+09) | 0x80000000;
        }
        *puStack_3c = uVar6;
        fVar5 = iVar4->f32_b4;
        if (fVar5 < 2.1474836e+09) {
          uVar6 = (uint)fVar5;
        }
        else {
          uVar6 = (int)(fVar5 - 2.1474836e+09) | 0x80000000;
        }
        puStack_3c[1] = uVar6;
        fVar5 = iVar4->f32_b8;
        if (fVar5 < 2.1474836e+09) {
          uVar6 = (uint)fVar5;
        }
        else {
          uVar6 = (int)(fVar5 - 2.1474836e+09) | 0x80000000;
        }
        puStack_3c[2] = uVar6;
        if (fStack_18 < 2.1474836e+09) {
          uVar6 = (uint)fStack_18;
        }
        else {
          uVar6 = (int)(fStack_18 - 2.1474836e+09) | 0x80000000;
        }
        puStack_3c[3] = uVar6;
        iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
        pfStack_44 = *(float **)(iStack_10 + 0x88);
        if ((iVar2 < 2) || ((uStack_20 & 0x3ffff) != 0)) {
          fStack_64 = 4.59177e-41;
        }
        *pfStack_44 = fStack_70;
        pfStack_44[1] = fStack_6c;
        pfStack_44[2] = fStack_68;
        pfStack_44[3] = fStack_64;
        iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
        pfVar1 = *(float **)(iStack_10 + 0x88);
        pfStack_4c = pfVar1;
        pfStack_48 = pfVar1;
        pfStack_40 = pfStack_44;
        puStack_38 = puStack_3c;
      }
      iVar4 = iVar4 + 0xf0;
    }
  }
  for (iVar4 = iStack_10->i32_1f4; iVar4 < iStack_10->i32_1f8; iVar4 = iVar4 + 1) {
    for (iVar3 = 0; iVar3 < 4; iVar3 = iVar3 + 1) {
      *pfVar1 = in_zero_lo;
      pfVar1[1] = in_zero_hi;
      pfVar1[2] = in_zero_udw;
      pfVar1[3] = in_register_0000000c;
      iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
      pfVar1 = *(float **)(iStack_10 + 0x88);
      *pfVar1 = in_zero_lo;
      pfVar1[1] = in_zero_hi;
      pfVar1[2] = in_zero_udw;
      pfVar1[3] = in_register_0000000c;
      iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
      pfVar1 = *(float **)(iStack_10 + 0x88);
      *pfVar1 = in_zero_lo;
      pfVar1[1] = in_zero_hi;
      pfVar1[2] = in_zero_udw;
      pfVar1[3] = in_register_0000000c;
      pfVar1[3] = 4.59177e-41;
      iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
      pfVar1 = *(float **)(iStack_10 + 0x88);
    }
  }
  return;
}

// JP: 0x002a03f0  __ct__8FpObjectFiPv  =  FpObject::FpObject
int FpObject::FpObject(int this,undefined4 param_2,undefined4 param_3)

{
  PutiObject::PutiObject(this,param_2,param_3);
  *(undefined1 **)(this + 0x1e4) = FpObject::__vt;
  this->u32_1f0 = 0x3f800000;
  this->u32_1f4 = 0;
  this->u32_1f8 = 0;
  this->u32_1fc = 0;
  this->u32_200 = 0;
  this->u8_204 = 0;
  return this;
}

// JP: 0x002a0480  __dt__8FpObjectFv  =  FpObject::~FpObject
int FpObject::~FpObject(int this,short param_2)

{
  if (this != 0) {
    *(undefined1 **)(this + 0x1e4) = FpObject::__vt;
    if (this->i32_1fc != 0) {
      if (this->i32_1fc != 0) {
        __dla(this->i32_1fc + -0x10);
      }
      this->u32_1fc = 0;
    }
    if (this->i32_200 != 0) {
      __dl(this->u32_200);
      this->u32_200 = 0;
    }
    PutiObject::~PutiObject(this,0);
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}

// JP: 0x002a0560  SetRGB__8FpObjectFUcUcUc  =  FpObject::SetRGB
/* WARNING: Removing unreachable block (ram,0x002a0668) */
/* WARNING: Removing unreachable block (ram,0x002a05d8) */
/* WARNING: Removing unreachable block (ram,0x002a0620) */

void FpObject::SetRGB(int this,byte param_2,byte param_3,byte param_4)

{
  int iVar1;
  int iVar2;
  
  if (this->i32_1fc != 0) {
    iVar1 = this->i32_1fc;
    for (iVar2 = 0; iVar2 < this->i32_1f8; iVar2 = iVar2 + 1) {
      iVar1->f32_b0 = (float)param_2 * 0.5019608;
      iVar1->f32_b4 = (float)param_3 * 0.5019608;
      iVar1->f32_b8 = (float)param_4 * 0.5019608;
      iVar1 = iVar1 + 0xf0;
    }
  }
  return;
}

// JP: 0x002a06d0  SetRGBA__8FpObjectFUcUcUcUc  =  FpObject::SetRGBA
/* WARNING: Removing unreachable block (ram,0x002a07d8) */
/* WARNING: Removing unreachable block (ram,0x002a0748) */
/* WARNING: Removing unreachable block (ram,0x002a0790) */
/* WARNING: Removing unreachable block (ram,0x002a0820) */

void FpObject::SetRGBA(int this,byte param_2,byte param_3,byte param_4,byte param_5)

{
  int iVar1;
  int iVar2;
  
  if (this->i32_1fc != 0) {
    iVar1 = this->i32_1fc;
    for (iVar2 = 0; iVar2 < this->i32_1f8; iVar2 = iVar2 + 1) {
      iVar1->f32_b0 = (float)param_2 * 0.5019608;
      iVar1->f32_b4 = (float)param_3 * 0.5019608;
      iVar1->f32_b8 = (float)param_4 * 0.5019608;
      iVar1->f32_bc = (float)param_5 * 0.5019608;
      iVar1 = iVar1 + 0xf0;
    }
  }
  return;
}

// JP: 0x002a0880  InitData__8FpObjectFi  =  FpObject::InitData
void FpObject::InitData(int this,int param_2)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)(this->i32_1fc + param_2 * 0xf0);
  *puVar1 = 0;
  puVar1[1] = 0;
  puVar1[2] = 0;
  puVar1[4] = 0;
  puVar1[5] = 0;
  puVar1[6] = 0;
  puVar1[7] = 0x3f800000;
  puVar1[8] = 0;
  puVar1[9] = 0;
  puVar1[10] = 0;
  puVar1[0xb] = 0x3f800000;
  puVar1[0xc] = 0;
  puVar1[0xd] = 0;
  puVar1[0xe] = 0;
  puVar1[0xf] = 0x3f800000;
  puVar1[0x10] = 0;
  puVar1[0x11] = 0;
  puVar1[0x12] = 0;
  puVar1[0x13] = 0x3f800000;
  puVar1[0x14] = 0x3f800000;
  puVar1[0x15] = 0x3f800000;
  puVar1[0x16] = 0x3f800000;
  puVar1[0x17] = 0x3f800000;
  puVar1[0x18] = 0;
  puVar1[0x19] = 0;
  puVar1[0x1a] = 0;
  puVar1[0x1b] = 0x3f800000;
  puVar1[0x1c] = 0;
  puVar1[0x1d] = 0;
  puVar1[0x1e] = 0;
  puVar1[0x1f] = 0x3f800000;
  puVar1[0x20] = 0;
  puVar1[0x21] = 0;
  puVar1[0x22] = 0;
  puVar1[0x23] = 0x3f800000;
  puVar1[0x24] = 0;
  puVar1[0x25] = 0;
  puVar1[0x26] = 0;
  puVar1[0x27] = 0x3f800000;
  puVar1[0x28] = 0;
  puVar1[0x29] = 0;
  puVar1[0x2a] = 0;
  puVar1[0x2b] = 0x3f800000;
  puVar1[0x2c] = 0;
  puVar1[0x2d] = 0;
  puVar1[0x2e] = 0;
  puVar1[0x2f] = 0;
  puVar1[0x30] = 0;
  puVar1[0x31] = 0;
  puVar1[0x32] = 0;
  puVar1[0x33] = 0x3f800000;
  puVar1[0x34] = 0x3f800000;
  puVar1[0x35] = 0;
  puVar1[0x36] = 0x3f800000;
  puVar1[0x37] = 0x3f800000;
  return;
}

// JP: 0x002a0c30  InitBBox__8FpObjectF7FVector7FVector7FVectorfbb  =  FpObject::InitBBox
void FpObject::InitBBox
               (undefined4 this,int param_2,undefined1 (*param_3) [16],float *param_4,
               float *param_5,byte param_6,byte param_7)

{
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  int iVar1;
  long lVar2;
  undefined4 *puVar3;
  int iVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  undefined1 in_vf0 [16];
  undefined1 auVar8 [16];
  undefined1 auVar9 [16];
  undefined1 auVar10 [16];
  undefined4 uVar11;
  undefined1 auStack_1b0 [16];
  undefined1 auStack_1a0 [16];
  undefined1 auStack_190 [16];
  undefined1 auStack_180 [16];
  undefined1 auStack_170 [8];
  undefined4 uStack_168;
  undefined4 uStack_164;
  undefined1 auStack_160 [8];
  undefined4 uStack_158;
  undefined4 uStack_154;
  undefined1 auStack_150 [8];
  float fStack_148;
  float fStack_144;
  float fStack_140;
  float fStack_13c;
  float fStack_138;
  undefined4 uStack_134;
  float fStack_130;
  float fStack_12c;
  float fStack_128;
  undefined4 uStack_124;
  float fStack_120;
  float fStack_11c;
  float fStack_118;
  undefined4 uStack_114;
  float fStack_110;
  float fStack_10c;
  float fStack_108;
  undefined4 uStack_104;
  float fStack_100;
  float fStack_fc;
  float fStack_f8;
  undefined4 uStack_f4;
  float fStack_f0;
  float fStack_ec;
  float fStack_e8;
  undefined4 uStack_e4;
  float fStack_e0;
  float fStack_dc;
  float fStack_d8;
  undefined4 uStack_d4;
  float fStack_d0;
  float fStack_cc;
  float fStack_c8;
  undefined4 uStack_c4;
  undefined1 auStack_c0 [16];
  undefined1 auStack_b0 [16];
  undefined1 auStack_a0 [16];
  undefined1 auStack_90 [16];
  float afStack_80 [32];
  
  if (param_2->i32_200 != 0) {
    __dl(param_2->u32_200);
    param_2->u32_200 = 0;
  }
  lVar2 = __nw(0x130);
  iVar4 = (int)lVar2;
  if (lVar2 != 0) {
    puVar3 = (undefined4 *)(iVar4 + 0x10);
    do {
      *puVar3 = in_zero_lo;
      puVar3[1] = in_zero_hi;
      puVar3[2] = in_zero_udw;
      puVar3[3] = in_register_0000000c;
      puVar3 = puVar3 + 4;
    } while (puVar3 != (undefined4 *)(iVar4 + 0xa0));
    puVar3 = (undefined4 *)(iVar4 + 0xa0);
    do {
      *puVar3 = in_zero_lo;
      puVar3[1] = in_zero_hi;
      puVar3[2] = in_zero_udw;
      puVar3[3] = in_register_0000000c;
      puVar3 = puVar3 + 4;
    } while (puVar3 != (undefined4 *)(iVar4 + 0x130));
  }
  param_2->i32_200 = iVar4;
  memset(*(void **)(param_2 + 0x200),0,0x130);
  **(undefined1 **)(param_2 + 0x200) = (char)(((ulong)param_2->u16_14 << 0x33) >> 0x38);
  fStack_c8 = -param_4[2];
  fStack_cc = -param_4[1];
  fStack_d0 = -*param_4;
  uStack_c4 = 0x3f800000;
  afStack_80[0] = fStack_d0;
  afStack_80[1] = fStack_cc;
  afStack_80[2] = fStack_c8;
  afStack_80[3] = 1.0;
  fStack_d8 = -param_4[2];
  fStack_dc = param_4[1];
  fStack_e0 = -*param_4;
  uStack_d4 = 0x3f800000;
  afStack_80[4] = fStack_e0;
  afStack_80[5] = fStack_dc;
  afStack_80[6] = fStack_d8;
  afStack_80[7] = 1.0;
  fStack_e8 = -param_4[2];
  fStack_ec = -param_4[1];
  fStack_f0 = *param_4;
  uStack_e4 = 0x3f800000;
  afStack_80[8] = fStack_f0;
  afStack_80[9] = fStack_ec;
  afStack_80[10] = fStack_e8;
  afStack_80[0xb] = 1.0;
  fStack_f8 = -param_4[2];
  fStack_fc = param_4[1];
  fStack_100 = *param_4;
  uStack_f4 = 0x3f800000;
  afStack_80[0xc] = fStack_100;
  afStack_80[0xd] = fStack_fc;
  afStack_80[0xe] = fStack_f8;
  afStack_80[0xf] = 1.0;
  fStack_108 = param_4[2];
  fStack_10c = -param_4[1];
  fStack_110 = -*param_4;
  uStack_104 = 0x3f800000;
  afStack_80[0x10] = fStack_110;
  afStack_80[0x11] = fStack_10c;
  afStack_80[0x12] = fStack_108;
  afStack_80[0x13] = 1.0;
  fStack_118 = param_4[2];
  fStack_11c = param_4[1];
  fStack_120 = -*param_4;
  uStack_114 = 0x3f800000;
  afStack_80[0x14] = fStack_120;
  afStack_80[0x15] = fStack_11c;
  afStack_80[0x16] = fStack_118;
  afStack_80[0x17] = 1.0;
  fStack_128 = param_4[2];
  fStack_12c = -param_4[1];
  fStack_130 = *param_4;
  uStack_124 = 0x3f800000;
  afStack_80[0x18] = fStack_130;
  afStack_80[0x19] = fStack_12c;
  afStack_80[0x1a] = fStack_128;
  afStack_80[0x1b] = 1.0;
  fStack_138 = param_4[2];
  fStack_13c = param_4[1];
  fStack_140 = *param_4;
  uStack_134 = 0x3f800000;
  afStack_80[0x1c] = fStack_140;
  afStack_80[0x1d] = fStack_13c;
  afStack_80[0x1e] = fStack_138;
  afStack_80[0x1f] = 1.0;
  auVar8 = _vmr32(in_vf0);
  auVar9 = _vmr32(auVar8);
  auVar10 = _vmr32(auVar9);
  auStack_90 = _sqc2(in_vf0);
  auStack_a0 = _sqc2(auVar8);
  auStack_b0 = _sqc2(auVar9);
  auStack_c0 = _sqc2(auVar10);
  fVar5 = param_5[2];
  if (fVar5 != 0.0) {
    uVar11 = GetRad(param_5[2]);
    sceVu0RotMatrixZ(uVar11,auStack_c0,auStack_c0);
  }
  fVar7 = *param_5;
  if (fVar7 != 0.0) {
    uVar11 = GetRad(*param_5);
    sceVu0RotMatrixX(uVar11,auStack_c0,auStack_c0);
  }
  fVar6 = param_5[1];
  if (fVar6 != 0.0) {
    uVar11 = GetRad(param_5[1]);
    sceVu0RotMatrixY(uVar11,auStack_c0,auStack_c0);
  }
  if (fVar6 != 0.0 || (fVar7 != 0.0 || fVar5 != 0.0)) {
    for (iVar4 = 0; iVar4 < 8; iVar4 = iVar4 + 1) {
      Matrix::ApplyMatrix(auStack_150,auStack_c0,afStack_80 + iVar4 * 4);
      afStack_80[iVar4 * 4] = auStack_150._0_4_;
      afStack_80[iVar4 * 4 + 1] = auStack_150._4_4_;
      afStack_80[iVar4 * 4 + 2] = fStack_148;
      afStack_80[iVar4 * 4 + 3] = fStack_144;
    }
  }
  for (iVar4 = 0; iVar4 < 8; iVar4 = iVar4 + 1) {
    auVar8 = _lqc2(*(undefined1 (*) [16])(afStack_80 + iVar4 * 4));
    auVar9 = _lqc2(*param_3);
    auVar8 = _vadd(auVar8,auVar9);
    auStack_190 = _sqc2(auVar8);
    FVector::FVector(auStack_160,auStack_190);
    iVar1 = param_2->i32_200 + iVar4 * 0x10;
    iVar1->i32_10 = auStack_160._0_4_;
    iVar1->i32_14 = auStack_160._4_4_;
    iVar1->u32_18 = uStack_158;
    iVar1->u32_1c = uStack_154;
  }
  auVar8 = _lqc2(*(undefined1 (*) [16])(param_2->i32_200 + 0x10));
  auVar9 = _lqc2(*(undefined1 (*) [16])(param_2->i32_200 + 0x80));
  auVar8 = _vadd(auVar8,auVar9);
  auStack_1b0 = _sqc2(auVar8);
  FVector::FVector(auStack_180,auStack_1b0);
  auVar8 = _qmtc2(0x40000000);
  _vdiv(in_vf0,0,auVar8,0);
  auVar8 = _lqc2(auStack_180);
  uVar11 = _vwaitq();
  auVar8 = _vmulq(auVar8,uVar11);
  auStack_1a0 = _sqc2(auVar8);
  FVector::FVector(auStack_170,auStack_1a0);
  iVar4 = param_2->i32_200;
  iVar4->i32_90 = auStack_170._0_4_;
  iVar4->i32_94 = auStack_170._4_4_;
  iVar4->u32_98 = uStack_168;
  iVar4->u32_9c = uStack_164;
  *(undefined4 *)(param_2->i32_200 + 4) = this;
  *(byte *)(param_2->i32_200 + 1) =
       *(byte *)(param_2->i32_200 + 1) & 0xfe | param_6 & 1;
  *(byte *)(param_2->i32_200 + 1) =
       *(byte *)(param_2->i32_200 + 1) & 0xfd | (param_7 & 1) << 1;
  return;
}

// JP: 0x002a11f0  InitBBox__8FpObjectF7FVectorb  =  FpObject::InitBBox
void FpObject::InitBBox(int this,undefined8 *param_2,byte param_3)

{
  undefined8 uVar1;
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  int iVar2;
  long lVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 *puVar6;
  
  if (this->i32_200 != 0) {
    __dl(this->u32_200);
    this->u32_200 = 0;
  }
  lVar3 = __nw(0x130);
  iVar2 = (int)lVar3;
  if (lVar3 != 0) {
    puVar6 = (undefined4 *)(iVar2 + 0x10);
    do {
      *puVar6 = in_zero_lo;
      puVar6[1] = in_zero_hi;
      puVar6[2] = in_zero_udw;
      puVar6[3] = in_register_0000000c;
      puVar6 = puVar6 + 4;
    } while (puVar6 != (undefined4 *)(iVar2 + 0xa0));
    puVar6 = (undefined4 *)(iVar2 + 0xa0);
    do {
      *puVar6 = in_zero_lo;
      puVar6[1] = in_zero_hi;
      puVar6[2] = in_zero_udw;
      puVar6[3] = in_register_0000000c;
      puVar6 = puVar6 + 4;
    } while (puVar6 != (undefined4 *)(iVar2 + 0x130));
  }
  this->i32_200 = iVar2;
  memset(*(void **)(this + 0x200),0,0x130);
  **(undefined1 **)(this + 0x200) = (char)(((ulong)this->u16_14 << 0x33) >> 0x38);
  iVar2 = this->i32_200;
  uVar1 = *param_2;
  uVar4 = param_2->u32_1;
  uVar5 = *(undefined4 *)((int)param_2 + 0xc);
  iVar2->i32_90 = (int)uVar1;
  iVar2->i32_94 = (int)((ulong)uVar1 >> 0x20);
  iVar2->u32_98 = uVar4;
  iVar2->u32_9c = uVar5;
  *(undefined4 *)(this->i32_200 + 4) = 0;
  *(byte *)(this->i32_200 + 1) = *(byte *)(this->i32_200 + 1) & 0xfe;
  *(byte *)(this->i32_200 + 1) =
       *(byte *)(this->i32_200 + 1) & 0xfd | (param_3 & 1) << 1;
  return;
}

// JP: 0x002a1330  UpdateBBox__8FpObjectF7FVector7FVectorf  =  FpObject::UpdateBBox
void FpObject::UpdateBBox
               (undefined4 this,int param_2,float *param_3,float *param_4)

{
  int iVar1;
  undefined1 in_vf0 [16];
  undefined1 auVar2 [16];
  undefined1 auVar3 [16];
  undefined4 uVar4;
  undefined1 auStack_c0 [16];
  undefined1 auStack_b0 [16];
  undefined1 auStack_a0 [16];
  undefined1 auStack_90 [8];
  undefined4 uStack_88;
  undefined4 uStack_84;
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
  undefined4 uStack_44;
  float fStack_40;
  float fStack_3c;
  float fStack_38;
  undefined4 uStack_34;
  float fStack_30;
  float fStack_2c;
  float fStack_28;
  undefined4 uStack_24;
  float fStack_20;
  float fStack_1c;
  float fStack_18;
  undefined4 uStack_14;
  float fStack_10;
  float fStack_c;
  float fStack_8;
  undefined4 uStack_4;
  
  if (param_2->i32_200 != 0) {
    fStack_8 = param_3[2] - param_4[2];
    fStack_c = param_3[1] - param_4[1];
    fStack_10 = *param_3 - *param_4;
    uStack_4 = 0x3f800000;
    iVar1 = param_2->i32_200;
    iVar1->f32_10 = fStack_10;
    iVar1->f32_14 = fStack_c;
    iVar1->f32_18 = fStack_8;
    iVar1->u32_1c = 0x3f800000;
    fStack_18 = param_3[2] - param_4[2];
    fStack_1c = param_3[1] + param_4[1];
    fStack_20 = *param_3 - *param_4;
    uStack_14 = 0x3f800000;
    iVar1 = param_2->i32_200;
    iVar1->f32_20 = fStack_20;
    iVar1->f32_24 = fStack_1c;
    iVar1->f32_28 = fStack_18;
    iVar1->u32_2c = 0x3f800000;
    fStack_28 = param_3[2] - param_4[2];
    fStack_2c = param_3[1] - param_4[1];
    fStack_30 = *param_3 + *param_4;
    uStack_24 = 0x3f800000;
    iVar1 = param_2->i32_200;
    iVar1->f32_30 = fStack_30;
    iVar1->f32_34 = fStack_2c;
    iVar1->f32_38 = fStack_28;
    iVar1->u32_3c = 0x3f800000;
    fStack_38 = param_3[2] - param_4[2];
    fStack_3c = param_3[1] + param_4[1];
    fStack_40 = *param_3 + *param_4;
    uStack_34 = 0x3f800000;
    iVar1 = param_2->i32_200;
    iVar1->f32_40 = fStack_40;
    iVar1->f32_44 = fStack_3c;
    iVar1->f32_48 = fStack_38;
    iVar1->u32_4c = 0x3f800000;
    fStack_48 = param_3[2] + param_4[2];
    fStack_4c = param_3[1] - param_4[1];
    fStack_50 = *param_3 - *param_4;
    uStack_44 = 0x3f800000;
    iVar1 = param_2->i32_200;
    iVar1->f32_50 = fStack_50;
    iVar1->f32_54 = fStack_4c;
    iVar1->f32_58 = fStack_48;
    iVar1->u32_5c = 0x3f800000;
    fStack_58 = param_3[2] + param_4[2];
    fStack_5c = param_3[1] + param_4[1];
    fStack_60 = *param_3 - *param_4;
    uStack_54 = 0x3f800000;
    iVar1 = param_2->i32_200;
    iVar1->f32_60 = fStack_60;
    iVar1->f32_64 = fStack_5c;
    iVar1->f32_68 = fStack_58;
    iVar1->u32_6c = 0x3f800000;
    fStack_68 = param_3[2] + param_4[2];
    fStack_6c = param_3[1] - param_4[1];
    fStack_70 = *param_3 + *param_4;
    uStack_64 = 0x3f800000;
    iVar1 = param_2->i32_200;
    iVar1->f32_70 = fStack_70;
    iVar1->f32_74 = fStack_6c;
    iVar1->f32_78 = fStack_68;
    iVar1->u32_7c = 0x3f800000;
    fStack_78 = param_3[2] + param_4[2];
    fStack_7c = param_3[1] + param_4[1];
    fStack_80 = *param_3 + *param_4;
    uStack_74 = 0x3f800000;
    iVar1 = param_2->i32_200;
    iVar1->f32_80 = fStack_80;
    iVar1->f32_84 = fStack_7c;
    iVar1->f32_88 = fStack_78;
    iVar1->u32_8c = 0x3f800000;
    auVar2 = _lqc2(*(undefined1 (*) [16])(param_2->i32_200 + 0x10));
    auVar3 = _lqc2(*(undefined1 (*) [16])(param_2->i32_200 + 0x80));
    auVar2 = _vadd(auVar2,auVar3);
    auStack_c0 = _sqc2(auVar2);
    FVector::FVector(auStack_a0,auStack_c0);
    auVar2 = _qmtc2(0x40000000);
    _vdiv(in_vf0,0,auVar2,0);
    auVar2 = _lqc2(auStack_a0);
    uVar4 = _vwaitq();
    auVar2 = _vmulq(auVar2,uVar4);
    auStack_b0 = _sqc2(auVar2);
    FVector::FVector(auStack_90,auStack_b0);
    iVar1 = param_2->i32_200;
    iVar1->i32_90 = auStack_90._0_4_;
    iVar1->i32_94 = auStack_90._4_4_;
    iVar1->u32_98 = uStack_88;
    iVar1->u32_9c = uStack_84;
    *(undefined4 *)(param_2->i32_200 + 4) = this;
  }
  return;
}

// JP: 0x002a16b0  UpdateBBox__8FpObjectF7FVector  =  FpObject::UpdateBBox
void FpObject::UpdateBBox(int this,undefined8 *param_2)

{
  int iVar1;
  undefined8 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
  if (this->i32_200 != 0) {
    iVar1 = this->i32_200;
    uVar2 = *param_2;
    uVar3 = param_2->u32_1;
    uVar4 = *(undefined4 *)((int)param_2 + 0xc);
    iVar1->i32_90 = (int)uVar2;
    iVar1->i32_94 = (int)((ulong)uVar2 >> 0x20);
    iVar1->u32_98 = uVar3;
    iVar1->u32_9c = uVar4;
  }
  return;
}

// JP: 0x002a16e0  UpdateBBoxMove__8FpObjectF7FVector  =  FpObject::UpdateBBoxMove
void FpObject::UpdateBBoxMove(int this,undefined1 (*param_2) [16])

{
  undefined1 (*pauVar1) [16];
  int iVar2;
  undefined1 auVar3 [16];
  undefined1 auVar4 [16];
  
  if (this->i32_200 != 0) {
    for (iVar2 = 0; iVar2 < 9; iVar2 = iVar2 + 1) {
      pauVar1 = (undefined1 (*) [16])(this->i32_200 + iVar2 * 0x10 + 0x10);
      auVar4 = _lqc2(*param_2);
      auVar3 = _lqc2(*pauVar1);
      auVar3 = _vadd(auVar3,auVar4);
      auVar3 = _sqc2(auVar3);
      *pauVar1 = auVar3;
    }
  }
  return;
}

// JP: 0x002a1740  FuncBBox__8FpObjectFv  =  FpObject::FuncBBox
void FpObject::FuncBBox(int this)

{
  int iVar1;
  int iVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  bool bVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fStack_1e0;
  float fStack_1dc;
  float fStack_1d8;
  undefined1 auStack_1d0 [48];
  undefined1 auStack_1a0 [16];
  float fStack_190;
  float fStack_18c;
  undefined4 uStack_188;
  undefined4 uStack_184;
  float fStack_180;
  float fStack_17c;
  undefined4 uStack_178;
  undefined4 uStack_174;
  float fStack_170;
  float fStack_16c;
  undefined4 uStack_168;
  undefined4 uStack_164;
  float fStack_160;
  float fStack_15c;
  undefined4 uStack_158;
  undefined4 uStack_154;
  int aiStack_150 [52];
  int aiStack_80 [16];
  char acStack_40 [16];
  char acStack_30 [16];
  char acStack_20 [16];
  char acStack_10 [16];
  
  if (this->i32_200 != 0) {
    this->u32_1f4 = this->u32_1f8;
    if ((*(byte *)(this->i32_200 + 1) & 1) != 0) {
      GsxCamera::GetViewScreenMatrix(aiStack_80,CApp::camera);
      for (iVar8 = 0; iVar8 < 4; iVar8 = iVar8 + 1) {
        aiStack_150[iVar8 * 4 + 0x24] = aiStack_80[iVar8 * 4];
        aiStack_150[iVar8 * 4 + 0x25] = aiStack_80[iVar8 * 4 + 1];
        aiStack_150[iVar8 * 4 + 0x26] = aiStack_80[iVar8 * 4 + 2];
        aiStack_150[iVar8 * 4 + 0x27] = aiStack_80[iVar8 * 4 + 3];
      }
      sceVu0RotTransPersN(aiStack_150,aiStack_150 + 0x24,this->i32_200 + 0x10,9,0);
      iVar8 = 0;
      for (iVar9 = 0; iVar9 < 9; iVar9 = iVar9 + 1) {
        acStack_40[iVar9] = '\0';
        acStack_30[iVar9] = '\0';
        acStack_20[iVar9] = '\0';
        acStack_10[iVar9] = '\0';
        iVar1 = aiStack_150[iVar9 * 4 + 2];
        iVar2 = aiStack_150[iVar9 * 4 + 1];
        iVar7 = this->i32_200 + iVar9 * 0x10;
        iVar7->f32_a0 = (float)aiStack_150[iVar9 * 4] / 16.0;
        iVar7->f32_a4 = (float)iVar2 / 16.0;
        iVar7->f32_a8 = (float)iVar1;
        iVar7->u32_ac = 0;
        bVar5 = *(float *)(this->i32_200 + iVar9 * 0x10 + 0xa0) < 1792.0;
        if (bVar5) {
          acStack_10[iVar9] = '\x01';
        }
        bVar3 = 2304.0 < *(float *)(this->i32_200 + iVar9 * 0x10 + 0xa0);
        if (bVar3) {
          acStack_20[iVar9] = '\x01';
        }
        bVar6 = *(float *)(this->i32_200 + iVar9 * 0x10 + 0xa4) < 1824.0;
        if (bVar6) {
          acStack_30[iVar9] = '\x01';
        }
        bVar4 = 2272.0 < *(float *)(this->i32_200 + iVar9 * 0x10 + 0xa4);
        if (bVar4) {
          acStack_40[iVar9] = '\x01';
        }
        if (bVar4 || (bVar6 || (bVar3 || bVar5))) {
          *(undefined4 *)(this->i32_200 + iVar9 * 0x10 + 0xac) = 0x47000000;
          iVar8 = iVar8 + 1;
        }
      }
      bVar5 = false;
      if (iVar8 == 9) {
        bVar5 = true;
        if (((((acStack_10[0] == '\0') || (acStack_10[1] == '\0')) || (acStack_10[2] == '\0')) ||
            ((acStack_10[3] == '\0' || (acStack_10[4] == '\0')))) ||
           (((acStack_10[5] == '\0' || ((acStack_10[6] == '\0' || (acStack_10[7] == '\0')))) ||
            (acStack_10[8] == '\0')))) {
          if (((((acStack_20[0] == '\0') || (acStack_20[1] == '\0')) || (acStack_20[2] == '\0')) ||
              (((acStack_20[3] == '\0' || (acStack_20[4] == '\0')) ||
               ((acStack_20[5] == '\0' || ((acStack_20[6] == '\0' || (acStack_20[7] == '\0'))))))))
             || (acStack_20[8] == '\0')) {
            if (((((acStack_30[0] == '\0') || (acStack_30[1] == '\0')) || (acStack_30[2] == '\0'))
                || (((acStack_30[3] == '\0' || (acStack_30[4] == '\0')) ||
                    ((acStack_30[5] == '\0' || ((acStack_30[6] == '\0' || (acStack_30[7] == '\0'))))
                    )))) || (acStack_30[8] == '\0')) {
              if ((((((acStack_40[0] != '\0') && (acStack_40[1] != '\0')) && (acStack_40[2] != '\0')
                    ) && ((acStack_40[3] != '\0' && (acStack_40[4] != '\0')))) &&
                  (acStack_40[5] != '\0')) &&
                 (((acStack_40[6] != '\0' && (acStack_40[7] != '\0')) && (acStack_40[8] != '\0'))))
              {
                bVar5 = true;
              }
            }
            else {
              bVar5 = true;
            }
          }
          else {
            bVar5 = true;
          }
        }
        else {
          bVar5 = true;
        }
      }
      if ((((((!bVar5) && (*(float *)(this->i32_200 + 0xa8) <= 0.0)) &&
            (*(float *)(this->i32_200 + 0xb8) <= 0.0)) &&
           ((*(float *)(this->i32_200 + 200) <= 0.0 &&
            (*(float *)(this->i32_200 + 0xd8) <= 0.0)))) &&
          ((*(float *)(this->i32_200 + 0xe8) <= 0.0 &&
           ((*(float *)(this->i32_200 + 0xf8) <= 0.0 &&
            (*(float *)(this->i32_200 + 0x108) <= 0.0)))))) &&
         ((*(float *)(this->i32_200 + 0x118) <= 0.0 &&
          (*(float *)(this->i32_200 + 0x128) <= 0.0)))) {
        bVar5 = true;
      }
      if ((bVar5) && (this->i8_204 == '\0')) {
        this->u32_1f4 = 0;
      }
      else if (0.0 < *(float *)(this->i32_200 + 4)) {
        fStack_15c = *(float *)(this->i32_200 + 0xa4) -
                     *(float *)(this->i32_200 + 0x114);
        fStack_160 = *(float *)(this->i32_200 + 0xa0) -
                     *(float *)(this->i32_200 + 0x110);
        uStack_158 = 0;
        uStack_154 = 0x3f800000;
        fStack_16c = *(float *)(this->i32_200 + 0xb4) -
                     *(float *)(this->i32_200 + 0x104);
        fStack_170 = *(float *)(this->i32_200 + 0xb0) -
                     *(float *)(this->i32_200 + 0x100);
        uStack_168 = 0;
        uStack_164 = 0x3f800000;
        fStack_17c = *(float *)(this->i32_200 + 0xc4) -
                     *(float *)(this->i32_200 + 0xf4);
        fStack_180 = *(float *)(this->i32_200 + 0xc0) -
                     *(float *)(this->i32_200 + 0xf0);
        uStack_178 = 0;
        uStack_174 = 0x3f800000;
        fStack_18c = *(float *)(this->i32_200 + 0xd4) -
                     *(float *)(this->i32_200 + 0xe4);
        fStack_190 = *(float *)(this->i32_200 + 0xd0) -
                     *(float *)(this->i32_200 + 0xe0);
        uStack_188 = 0;
        uStack_184 = 0x3f800000;
        fVar10 = (float)FVector::Length(&fStack_160);
        fVar13 = (float)FVector::Length(&fStack_170);
        fVar12 = (float)FVector::Length(&fStack_180);
        fVar11 = (float)FVector::Length(&fStack_190);
        if (fVar13 <= fVar10) {
          fVar13 = fVar10;
        }
        if (fVar12 <= fVar13) {
          fVar12 = fVar13;
        }
        if (fVar11 <= fVar12) {
          fVar11 = fVar12;
        }
        fVar12 = *(float *)(this->i32_200 + 4);
        if (fVar11 < fVar12) {
          this->i32_1f4 = (int)(((float)this->i32_1f8 * fVar11) / fVar12);
        }
        else {
          this->u32_1f4 = this->u32_1f8;
        }
      }
    }
    if ((this->i32_1f4 != 0) &&
       ((long)((ulong)*(byte *)(this->i32_200 + 1) << 0x3e) < 0)) {
      Matrix::Matrix(auStack_1d0,CApp::camera + 0x240);
      FVector::FVector(&fStack_1e0,auStack_1a0);
      fStack_1e0 = fStack_1e0 - *(float *)(this->i32_200 + 0x90);
      fStack_1dc = fStack_1dc - *(float *)(this->i32_200 + 0x94);
      fStack_1d8 = fStack_1d8 - *(float *)(this->i32_200 + 0x98);
      fVar11 = (float)FVector::Length(&fStack_1e0);
      iVar8 = this->i32_8;
      if (iVar8->i8_50 == '\0') {
        fVar12 = CApp::camera->f32_380;
        fVar13 = CApp::camera->f32_384;
      }
      else {
        fVar12 = iVar8->f32_48;
        fVar13 = iVar8->f32_4c;
      }
      fVar10 = fVar12;
      if (fVar12 <= fVar11) {
        fVar10 = fVar11;
      }
      fVar11 = fVar13;
      if (fVar10 <= fVar13) {
        fVar11 = fVar10;
      }
      this->f32_1f0 = (fVar13 - fVar11) / (fVar13 - fVar12);
      if (1.0 < this->f32_1f0) {
        this->u32_1f0 = 0x3f800000;
      }
      else if (this->f32_1f0 <= 0.0) {
        this->u32_1f0 = 0;
        this->u32_1f4 = 0;
      }
    }
  }
  return;
}

// JP: 0x002a20f0  CalcUv__8FpObjectFv  =  FpObject::CalcUv
void FpObject::CalcUv(int this)

{
  int iVar1;
  int iVar2;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  int iStack_10;
  
  if ((long)((ulong)this->u8_14 << 0x3c) < 0) {
    iVar1 = this->i32_1fc;
    iStack_10 = this;
    for (iVar2 = 0; iVar2 < iStack_10->i32_1f8; iVar2 = iVar2 + 1) {
      PutiTexAnim::GetUVA
                (*(undefined4 *)(iStack_10->i32_8 + 0x30),(int)iVar1->f32_4,
                 &uStack_14,&uStack_18,&uStack_1c,&uStack_20,iVar1 + 0xbc);
      iVar1->u32_c0 = uStack_14;
      iVar1->u32_c4 = uStack_18;
      iVar1->u32_c8 = uStack_14;
      iVar1->u32_cc = uStack_20;
      iVar1->u32_d0 = uStack_1c;
      iVar1->u32_d4 = uStack_18;
      iVar1->u32_d8 = uStack_1c;
      iVar1->u32_dc = uStack_20;
    }
  }
  return;
}

// JP: 0x002a21e0  CalcFpVertex__8FpObjectFv  =  FpObject::CalcFpVertex
void FpObject::CalcFpVertex(int this)

{
  bool bVar1;
  undefined1 auVar2 [16];
  int iVar3;
  undefined1 (*pauVar4) [16];
  int iVar5;
  int iVar6;
  int iVar7;
  undefined1 in_vf0 [16];
  undefined1 auVar8 [16];
  undefined1 auVar9 [16];
  undefined1 auVar10 [16];
  undefined1 auStack_d0 [8];
  undefined4 uStack_c8;
  undefined4 uStack_c4;
  undefined1 auStack_c0 [8];
  undefined4 uStack_b8;
  undefined4 uStack_b4;
  undefined1 auStack_b0 [8];
  undefined4 uStack_a8;
  undefined4 uStack_a4;
  undefined1 auStack_a0 [8];
  undefined4 uStack_98;
  undefined4 uStack_94;
  float fStack_90;
  float fStack_8c;
  float fStack_88;
  undefined4 uStack_84;
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
  undefined1 auStack_50 [16];
  undefined1 auStack_40 [16];
  undefined1 auStack_30 [16];
  undefined1 auStack_20 [16];
  undefined1 auStack_10 [12];
  undefined4 uStack_4;
  
  bVar1 = false;
  iVar7 = this->i32_1fc;
  if (((iVar7->f32_60 != 0.0) || (iVar7->f32_64 != 0.0)) ||
     (iVar7->f32_68 != 0.0)) {
    bVar1 = true;
  }
  for (iVar6 = 0; iVar6 < this->i32_1f8; iVar6 = iVar6 + 1) {
    fStack_90 = (iVar7->f32_40 / 2.0) * iVar7->f32_50;
    fStack_8c = (iVar7->f32_44 / 2.0) * iVar7->f32_54;
    fStack_78 = (iVar7->f32_48 / 2.0) * iVar7->f32_58;
    fStack_60 = -fStack_90;
    fStack_5c = -fStack_8c;
    uStack_54 = 0x3f800000;
    iVar7->f32_70 = fStack_60;
    iVar7->f32_74 = fStack_5c;
    iVar7->f32_78 = fStack_78;
    iVar7->u32_7c = 0x3f800000;
    fStack_70 = -fStack_90;
    fStack_68 = -fStack_78;
    uStack_64 = 0x3f800000;
    iVar7->f32_80 = fStack_70;
    iVar7->f32_84 = fStack_8c;
    iVar7->f32_88 = fStack_68;
    iVar7->u32_8c = 0x3f800000;
    fStack_7c = -fStack_8c;
    uStack_74 = 0x3f800000;
    iVar7->f32_90 = fStack_90;
    iVar7->f32_94 = fStack_7c;
    iVar7->f32_98 = fStack_78;
    iVar7->u32_9c = 0x3f800000;
    fStack_88 = -fStack_78;
    uStack_84 = 0x3f800000;
    iVar7->f32_a0 = fStack_90;
    iVar7->f32_a4 = fStack_8c;
    iVar7->f32_a8 = fStack_88;
    iVar7->u32_ac = 0x3f800000;
    fStack_80 = fStack_90;
    fStack_6c = fStack_8c;
    fStack_58 = fStack_78;
    FVector::FVector(auStack_10,iVar7 + 0x30);
    uStack_4 = 0;
    if (bVar1) {
      auVar8 = _vmr32(in_vf0);
      auVar9 = _vmr32(auVar8);
      auVar10 = _vmr32(auVar9);
      auStack_20 = _sqc2(in_vf0);
      auStack_30 = _sqc2(auVar8);
      auStack_40 = _sqc2(auVar9);
      auStack_50 = _sqc2(auVar10);
      sceVu0RotMatrix(auStack_50,auStack_50,iVar7 + 0x60);
      if ((this->u8_14 & 1) == 0) {
        for (iVar5 = 0; iVar5 < 4; iVar5 = iVar5 + 1) {
          Matrix::ApplyMatrix(auStack_c0,auStack_50,iVar7 + iVar5 * 0x10 + 0x70);
          iVar3 = iVar7 + iVar5 * 0x10;
          iVar3->i32_70 = auStack_c0._0_4_;
          iVar3->i32_74 = auStack_c0._4_4_;
          iVar3->u32_78 = uStack_b8;
          iVar3->u32_7c = uStack_b4;
          pauVar4 = (undefined1 (*) [16])(iVar7 + iVar5 * 0x10 + 0x70);
          auVar10._12_4_ = uStack_4;
          auVar10._0_12_ = auStack_10;
          auVar9 = _lqc2(auVar10);
          auVar8 = _lqc2(*pauVar4);
          auVar8 = _vadd(auVar8,auVar9);
          auVar8 = _sqc2(auVar8);
          *pauVar4 = auVar8;
        }
      }
      else {
        for (iVar5 = 0; iVar5 < 4; iVar5 = iVar5 + 1) {
          Matrix::ApplyMatrix(auStack_a0,auStack_50,iVar7 + iVar5 * 0x10 + 0x70);
          iVar3 = iVar7 + iVar5 * 0x10;
          iVar3->i32_70 = auStack_a0._0_4_;
          iVar3->i32_74 = auStack_a0._4_4_;
          iVar3->u32_78 = uStack_98;
          iVar3->u32_7c = uStack_94;
          Matrix::ApplyMatrix(auStack_b0,0x4213c0,iVar7 + iVar5 * 0x10 + 0x70);
          iVar3 = iVar7 + iVar5 * 0x10;
          iVar3->i32_70 = auStack_b0._0_4_;
          iVar3->i32_74 = auStack_b0._4_4_;
          iVar3->u32_78 = uStack_a8;
          iVar3->u32_7c = uStack_a4;
          pauVar4 = (undefined1 (*) [16])(iVar7 + iVar5 * 0x10 + 0x70);
          auVar2._12_4_ = uStack_4;
          auVar2._0_12_ = auStack_10;
          auVar9 = _lqc2(auVar2);
          auVar8 = _lqc2(*pauVar4);
          auVar8 = _vadd(auVar8,auVar9);
          auVar8 = _sqc2(auVar8);
          *pauVar4 = auVar8;
        }
      }
    }
    else if ((this->u8_14 & 1) == 0) {
      for (iVar5 = 0; iVar5 < 4; iVar5 = iVar5 + 1) {
        pauVar4 = (undefined1 (*) [16])(iVar7 + iVar5 * 0x10 + 0x70);
        auVar8._12_4_ = 0;
        auVar8._0_12_ = auStack_10;
        auVar9 = _lqc2(auVar8);
        auVar8 = _lqc2(*pauVar4);
        auVar8 = _vadd(auVar8,auVar9);
        auVar8 = _sqc2(auVar8);
        *pauVar4 = auVar8;
      }
    }
    else {
      for (iVar5 = 0; iVar5 < 4; iVar5 = iVar5 + 1) {
        Matrix::ApplyMatrix(auStack_d0,0x4213c0,iVar7 + iVar5 * 0x10 + 0x70);
        iVar3 = iVar7 + iVar5 * 0x10;
        iVar3->i32_70 = auStack_d0._0_4_;
        iVar3->i32_74 = auStack_d0._4_4_;
        iVar3->u32_78 = uStack_c8;
        iVar3->u32_7c = uStack_c4;
        pauVar4 = (undefined1 (*) [16])(iVar7 + iVar5 * 0x10 + 0x70);
        auVar9._12_4_ = uStack_4;
        auVar9._0_12_ = auStack_10;
        auVar9 = _lqc2(auVar9);
        auVar8 = _lqc2(*pauVar4);
        auVar8 = _vadd(auVar8,auVar9);
        auVar8 = _sqc2(auVar8);
        *pauVar4 = auVar8;
      }
    }
    iVar7 = iVar7 + 0xf0;
  }
  return;
}

// JP: 0x002a2640  GetRotMatrix__8FpObjectF7FVector  =  FpObject::GetRotMatrix
void FpObject::GetRotMatrix(undefined8 this,undefined8 param_2,float *param_3)

{
  undefined1 auVar1 [16];
  float fVar2;
  undefined1 in_vf0 [16];
  undefined1 auVar3 [16];
  undefined1 auVar4 [16];
  undefined1 auVar5 [16];
  undefined8 uStack_130;
  undefined4 uStack_128;
  undefined4 uStack_124;
  undefined8 uStack_120;
  undefined4 uStack_118;
  undefined4 uStack_114;
  undefined8 uStack_110;
  undefined4 uStack_108;
  undefined4 uStack_104;
  undefined8 uStack_100;
  undefined4 uStack_f8;
  undefined4 uStack_f4;
  undefined4 uStack_f0;
  undefined4 uStack_ec;
  undefined4 uStack_e8;
  undefined4 uStack_e4;
  undefined1 auStack_e0 [64];
  undefined1 auStack_a0 [64];
  float fStack_60;
  float fStack_5c;
  float fStack_58;
  float fStack_54;
  float fStack_50;
  float fStack_4c;
  float fStack_48;
  float fStack_44;
  undefined1 auStack_40 [16];
  undefined1 auStack_30 [16];
  undefined1 auStack_20 [16];
  undefined1 auStack_10 [16];
  
  auVar3 = _vmr32(in_vf0);
  auVar4 = _vmr32(auVar3);
  auVar5 = _vmr32(auVar4);
  auStack_10 = _sqc2(in_vf0);
  auStack_20 = _sqc2(auVar3);
  auStack_30 = _sqc2(auVar4);
  auStack_40 = _sqc2(auVar5);
  if (param_3[3] != 0.0) {
    fStack_50 = *param_3;
    fStack_48 = param_3[2];
    fStack_44 = param_3[3];
    fStack_4c = 0.0;
    FVector::Normalize(&fStack_50);
    uStack_f0 = 0;
    uStack_ec = 0;
    uStack_e8 = 0x3f800000;
    uStack_e4 = 0x3f800000;
    fStack_60 = 0.0;
    fStack_5c = 0.0;
    fStack_58 = 1.0;
    fStack_54 = 1.0;
    auVar3._12_4_ = 0x3f800000;
    auVar3._0_12_ = ZEXT412(0x3f800000) << 0x40;
    auVar3 = _lqc2(auVar3);
    auVar4._4_4_ = fStack_4c;
    auVar4._0_4_ = fStack_50;
    auVar4._8_4_ = fStack_48;
    auVar4._12_4_ = fStack_44;
    auVar4 = _lqc2(auVar4);
    auVar3 = _vmul(auVar3,auVar4);
    auVar3 = _vaddbc(auVar3,auVar3);
    auVar3 = _vaddbc(auVar3,auVar3);
    auVar3 = _qmfc2(auVar3._0_4_);
    fVar2 = auVar3._0_4_;
    Matrix::Matrix(fVar2,0,SQRT(1.0 - fVar2 * fVar2),0,0,0x3f800000,0,0,auStack_a0);
    if (0.0 < fStack_50) {
      sceVu0InversMatrix(auStack_a0,auStack_a0);
    }
    fStack_60 = *param_3;
    fStack_5c = param_3[1];
    fStack_58 = param_3[2];
    fStack_54 = param_3[3];
    fStack_50 = fStack_60;
    fStack_4c = fStack_5c;
    fStack_48 = fStack_58;
    fStack_44 = fStack_54;
    FVector::Normalize(&fStack_50);
    fStack_5c = 0.0;
    FVector::Normalize(&fStack_60);
    auVar5._4_4_ = fStack_5c;
    auVar5._0_4_ = fStack_60;
    auVar5._8_4_ = fStack_58;
    auVar5._12_4_ = fStack_54;
    auVar3 = _lqc2(auVar5);
    auVar1._4_4_ = fStack_4c;
    auVar1._0_4_ = fStack_50;
    auVar1._8_4_ = fStack_48;
    auVar1._12_4_ = fStack_44;
    auVar4 = _lqc2(auVar1);
    auVar3 = _vmul(auVar3,auVar4);
    auVar3 = _vaddbc(auVar3,auVar3);
    auVar3 = _vaddbc(auVar3,auVar3);
    auVar3 = _qmfc2(auVar3._0_4_);
    fVar2 = auVar3._0_4_;
    Matrix::Matrix(0x3f800000,0,0,0,0,fVar2,-SQRT(1.0 - fVar2 * fVar2),0,auStack_e0)
    ;
    if (fStack_4c < 0.0) {
      sceVu0InversMatrix(auStack_e0,auStack_e0);
    }
    Matrix::MulMatrix(&uStack_130,auStack_a0,auStack_e0);
    auStack_40._8_4_ = uStack_128;
    auStack_40._0_8_ = uStack_130;
    auStack_40._12_4_ = uStack_124;
    auStack_30._8_4_ = uStack_118;
    auStack_30._0_8_ = uStack_120;
    auStack_30._12_4_ = uStack_114;
    auStack_20._8_4_ = uStack_108;
    auStack_20._0_8_ = uStack_110;
    auStack_20._12_4_ = uStack_104;
    auStack_10._8_4_ = uStack_f8;
    auStack_10._0_8_ = uStack_100;
    auStack_10._12_4_ = uStack_f4;
  }
  Matrix::Matrix(this,auStack_40);
  return;
}

// JP: 0x002a2980  Calculate__8FpObjectFv  =  FpObject::Calculate
undefined4 FpObject::Calculate(int this)

{
  bool bVar1;
  undefined1 uVar2;
  int iVar3;
  
  iVar3 = this->i32_8;
  FpPrim::FuncAlphaPowerAdd(iVar3);
  if (iVar3->i8_68 != '\0') {
    FpObject::FuncBBox(this);
    if (this->i32_1f4 == 0) {
      uVar2 = FpPrim::FuncbDrawNum(iVar3);
      iVar3->u8_69 = uVar2;
    }
    else {
      iVar3->u8_69 = 1;
      (**(code **)(this->i32_1e4 + 0x48))();
      if (this->i8_204 != '\0') {
        bVar1 = false;
        for (iVar3 = 0; iVar3 < this->i32_1f8; iVar3 = iVar3 + 1) {
          if ((*(byte *)(this->i32_1fc + iVar3 * 0xf0 + 0xe0) & 1) != 0) {
            bVar1 = true;
            break;
          }
        }
        if (!bVar1) {
          this->u8_204 = 0;
        }
      }
    }
  }
  return 1;
}

// JP: 0x002a2ac0  CalculateFunc__8FpObjectFv  =  FpObject::CalculateFunc
void FpObject::CalculateFunc(void)

{
  return;
}

// JP: 0x002a2ad0  SetPacket__8FpObjectFv  =  FpObject::SetPacket
void FpObject::SetPacket(void)

{
  return;
}

// JP: 0x002a2ae0  __ct__6FpPrimFv  =  FpPrim::FpPrim
int FpPrim::FpPrim(int this)

{
  PutiPrim::PutiPrim(this,100);
  *(undefined1 **)(this + 0x10) = FpPrim::__vt;
  this->u32_1c = 0x405e20;
  this->u32_54 = 10;
  this->u8_58 = 1;
  this->u8_59 = 1;
  this->u32_48 = 0;
  this->u32_4c = 0;
  this->u8_50 = 0;
  this->u32_5c = 0x3f800000;
  this->u8_68 = 1;
  this->u8_69 = 1;
  this->u32_60 = 0;
  this->u32_64 = 0;
  this->u8_6a = 0;
  return this;
}

// JP: 0x002a2bc0  __dt__6FpPrimFv  =  FpPrim::~FpPrim
int FpPrim::~FpPrim(int this,short param_2)

{
  if (this != 0) {
    *(undefined1 **)(this + 0x10) = FpPrim::__vt;
    this->u32_1c = 0x405e20;
    PutiPrim::~PutiPrim(this,0);
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}

// JP: 0x002a2c50  FuncbDrawNum__6FpPrimFv  =  FpPrim::FuncbDrawNum
undefined4 FpPrim::FuncbDrawNum(int this)

{
  undefined4 *puVar1;
  
  puVar1 = *(undefined4 **)(this + 0x28);
  while( true ) {
    if (puVar1 == (undefined4 *)0x0) {
      return 0;
    }
    if (0 < (int)puVar1[0x7d]) break;
    puVar1 = (undefined4 *)*puVar1;
  }
  return 1;
}

// JP: 0x002a2cc0  FuncAlphaPowerAdd__6FpPrimFv  =  FpPrim::FuncAlphaPowerAdd
void FpPrim::FuncAlphaPowerAdd(int this)

{
  if (0 < this->i32_64) {
    this->f32_5c = this->f32_5c + this->f32_60;
    this->i32_64 = this->i32_64 + -1;
    if (this->f32_5c <= 0.0) {
      this->u32_5c = 0;
      this->u32_60 = 0;
      this->u32_64 = 0;
      this->u8_68 = 0;
    }
    else {
      this->u8_68 = 1;
    }
  }
  return;
}

// JP: 0x002a2d70  InitFpFlag__6FpPrimFf  =  FpPrim::InitFpFlag
undefined4 * FpPrim::InitFpFlag(undefined4 this,VIF1Prim *param_2)

{
  ulong uVar1;
  undefined4 uStack_10;
  
  uStack_10._2_1_ = (byte)((uint)this >> 0x10);
  uVar1 = (ulong)uStack_10._2_1_;
  uStack_10 = this;
  if ((long)(uVar1 << 0x38) < 0) {
    (**(code **)((int)param_2->pVptr + 0x30))(param_2,0);
  }
  if ((long)((ulong)uStack_10._2_1_ << 0x3a) < 0) {
    VIF1Prim::setZvolume(param_2,(short)uStack_10);
  }
  if ((long)((ulong)uStack_10._2_1_ << 0x39) < 0) {
    (**(code **)((int)param_2->pVptr + 0x2c))(param_2,uStack_10._2_1_ & 0x1f);
  }
  return &uStack_10;
}

// JP: 0x002a2e30  GetFrameSpeed__6FpPrimFv  =  FpPrim::GetFrameSpeed
/* WARNING: Removing unreachable block (ram,0x002a2e5c) */

float FpPrim::GetFrameSpeed(void)

{
  return (float)Gsx::m_syncCount * 0.5;
}

// JP: 0x002a2e90  CreateStart__6FpPrimFf  =  FpPrim::CreateStart
void FpPrim::CreateStart(void)

{
  return;
}

// JP: 0x002a2eb0  SetAlphaPower__6FpPrimFfUi  =  FpPrim::SetAlphaPower
void FpPrim::SetAlphaPower(float this,int param_2,int param_3)

{
  uint uVar1;
  float fVar2;
  undefined4 uStack_34;
  
  if (param_3 == 0) {
    param_2->f32_5c = this;
    if (param_2->f32_5c <= 0.0) {
      param_2->u8_68 = 0;
    }
    else {
      param_2->u8_68 = 1;
    }
    param_2->u32_64 = 0;
    param_2->u32_60 = 0;
  }
  else {
    uStack_34 = this;
    if (this <= 0.0) {
      uStack_34 = 0.0;
    }
    uVar1 = param_3 * 0x3c;
    if ((int)uVar1 < 0) {
      fVar2 = (float)(uVar1 >> 1) + (float)(uVar1 >> 1);
    }
    else {
      fVar2 = (float)(int)uVar1;
    }
    param_2->i32_64 =
         (int)(fVar2 / (float)(((uint)Gsx::m_syncCount * 0x7c + (uint)Gsx::m_syncCount) * 8));
    param_2->f32_60 =
         (uStack_34 - param_2->f32_5c) / (float)param_2->i32_64;
  }
  return;
}

// JP: 0x002a3040  setLayer__6FpPrimFi  =  FpPrim::setLayer
void FpPrim::setLayer(int this,int param_2)

{
  long lVar1;
  
  if (this->i32_54 != param_2) {
    lVar1 = PutiManager::FindPrim
                      (PutiManager::ourManager,this->u32_54,this);
    if (lVar1 == 0) {
      this->i32_54 = param_2;
    }
    else {
      this->i32_54 = param_2;
      PutiManager::RemovePrim(PutiManager::ourManager,this);
      PutiManager::AddPrim
                (PutiManager::ourManager,this->u32_54,this);
    }
  }
  return;
}

// JP: 0x002a30e0  SetColor1__6FpPrimFUcUcUcUc  =  FpPrim::SetColor1
undefined8 FpPrim::SetColor1(void)

{
  return 0;
}

// JP: 0x002a3100  SetColor2__6FpPrimFUcUcUcUc  =  FpPrim::SetColor2
undefined8 FpPrim::SetColor2(void)

{
  return 0;
}

// JP: 0x002a3120  SetColor3__6FpPrimFUcUcUcUc  =  FpPrim::SetColor3
undefined8 FpPrim::SetColor3(void)

{
  return 0;
}

// JP: 0x002a3140  SetPos1__6FpPrimF7FVectorb  =  FpPrim::SetPos1
undefined8 FpPrim::SetPos1(void)

{
  return 0;
}

// JP: 0x002a3160  SetRegAlpha__6FpPrimFUl  =  FpPrim::SetRegAlpha
void FpPrim::SetRegAlpha(int this,undefined8 param_2)

{
  undefined4 *puVar1;
  
  for (puVar1 = *(undefined4 **)(this + 0x28); puVar1 != (undefined4 *)0x0;
      puVar1 = (undefined4 *)*puVar1) {
    PutiObject::SetRegAlpha(puVar1,param_2);
  }
  return;
}

// JP: 0x002a31c0  getPacket__6FpPrimFv  =  FpPrim::getPacket
undefined4 FpPrim::getPacket(int this)

{
  undefined4 *puVar1;
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  undefined4 uVar2;
  
  if ((this->i8_68 == '\0') || (this->i8_69 == '\0')) {
    puVar1 = *(undefined4 **)(this + (VIF1Prim::m_Env & 1) * 4);
    *puVar1 = in_zero_lo;
    puVar1[1] = in_zero_hi;
    puVar1[2] = in_zero_udw;
    puVar1[3] = in_register_0000000c;
    *puVar1 = &DAT_10000002;
    puVar1[3] = 0x50000002;
    puVar1->u64_4 = 0x1000000000008001;
    puVar1->u64_6 = 0xe;
    puVar1->u64_8 = this->u64_20;
    puVar1->u64_a = 0x4e;
    puVar1[0xc] = in_zero_lo;
    puVar1[0xd] = in_zero_hi;
    puVar1[0xe] = in_zero_udw;
    puVar1[0xf] = in_register_0000000c;
    puVar1[0xc] = 0x60000002;
    puVar1[0xf] = 0x50000002;
    puVar1->u64_10 = 0x1000000000008001;
    puVar1->u64_12 = 0xe;
    puVar1->u64_14 = CApp::camera->u64_60;
    puVar1->u64_16 = 0x4e;
    uVar2 = *(undefined4 *)(this + (VIF1Prim::m_Env & 1) * 4);
  }
  else {
    uVar2 = PutiPrim::getPacket(this);
  }
  return uVar2;
}

// JP: 0x002a3740  __ct__7FpFlareFv  =  FpFlare::FpFlare
int FpFlare::FpFlare(int this)

{
  FpPrim::FpPrim(this);
  *(undefined1 **)(this + 0x10) = FpFlare::__vt;
  this->u32_1c = 0x405f10;
  return this;
}

// JP: 0x002a3790  __dt__7FpFlareFv  =  FpFlare::~FpFlare
int FpFlare::~FpFlare(int this,short param_2)

{
  if (this != 0) {
    *(undefined1 **)(this + 0x10) = FpFlare::__vt;
    this->u32_1c = 0x405f10;
    FpPrim::~FpPrim(this,0);
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}

// JP: 0x002a3820  CreateEffect__7FpFlareFP12FpFlareParam  =  FpFlare::CreateEffect
/* WARNING: Removing unreachable block (ram,0x002a3914) */
/* WARNING: Removing unreachable block (ram,0x002a3864) */
/* WARNING: Removing unreachable block (ram,0x002a38bc) */
/* WARNING: Removing unreachable block (ram,0x002a396c) */

void FpFlare::CreateEffect(int this,int param_2)

{
  int iVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined1 auStack_70 [16];
  undefined1 auStack_60 [16];
  undefined1 auStack_50 [16];
  float fStack_40;
  float fStack_3c;
  float fStack_38;
  float fStack_34;
  float fStack_24;
  int iStack_20;
  int iStack_10;
  
  fStack_40 = (float)param_2->u8_10 * 0.5019608;
  fStack_3c = (float)param_2->u8_11 * 0.5019608;
  fStack_38 = (float)param_2->u8_12 * 0.5019608;
  fStack_34 = (float)param_2->u8_13 * 0.5019608;
  fStack_24 = param_2->f32_14;
  if ((param_2->u8_30 & 1) == 0) {
    fStack_24 = fStack_24 * 0.73;
  }
  iStack_20 = this;
  iStack_10 = param_2;
  uVar2 = FVector::FVector(auStack_50,param_2);
  uVar3 = FVector::FVector(auStack_60,&fStack_40);
  uVar4 = FVector::FVector(auStack_70,iStack_10 + 0x40);
  FpFlare::Create
            (fStack_24,iStack_10->u32_18,iStack_10->u32_20,
             iStack_10->u32_1c,iStack_10->u32_24,
             iStack_10->u32_28,iStack_20,uVar2,uVar3,
             iStack_10->u32_2c,uVar4);
  iVar1 = iStack_20->i32_28;
  if (iVar1->i32_200 != 0) {
    *(byte *)(iVar1->i32_200 + 1) = *(byte *)(iVar1->i32_200 + 1) & 0xfe;
  }
  if (iVar1->i32_200 != 0) {
    *(byte *)(iVar1->i32_200 + 1) = *(byte *)(iVar1->i32_200 + 1) & 0xfd | 2;
  }
  iVar1->u8_380 = (long)((ulong)iStack_10->u8_30 << 0x3e) < 0;
  if ((iStack_10->u8_30 & 1) != 0) {
    iVar1->u8_381 = 0;
  }
  return;
}

// JP: 0x002a3b20  SetColor1__7FpFlareFUcUcUcUc  =  FpFlare::SetColor1
undefined4
FpFlare::SetColor1(int this,ulong param_2,ulong param_3,ulong param_4,ulong param_5)

{
  int iVar1;
  undefined4 uVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  
  iVar1 = this->i32_28;
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    (**(code **)(iVar1->i32_1e4 + 0x38))(iVar1,param_2,param_3,param_4);
    if ((long)param_2 < 0) {
      fVar3 = (float)(param_2 & 0xffffffff);
    }
    else {
      fVar3 = (float)(int)param_2;
    }
    if ((long)param_3 < 0) {
      fVar4 = (float)(param_3 & 0xffffffff);
    }
    else {
      fVar4 = (float)(int)param_3;
    }
    if ((long)param_4 < 0) {
      fVar5 = (float)(param_4 & 0xffffffff);
    }
    else {
      fVar5 = (float)(int)param_4;
    }
    if ((long)param_5 < 0) {
      fVar6 = (float)(param_5 & 0xffffffff);
    }
    else {
      fVar6 = (float)(int)param_5;
    }
    iVar1->f32_220 = fVar3 * 0.5019608;
    iVar1->f32_224 = fVar4 * 0.5019608;
    iVar1->f32_228 = fVar5 * 0.5019608;
    iVar1->f32_22c = fVar6 * 0.5019608;
    iVar1->i32_320 = (int)iVar1->u64_220;
    iVar1->i32_324 = (int)((ulong)iVar1->u64_220 >> 0x20);
    iVar1->u32_328 = iVar1->u32_228;
    iVar1->u32_32c = iVar1->u32_22c;
    uVar2 = 1;
  }
  return uVar2;
}

// JP: 0x002a3ce0  SetPos1__7FpFlareF7FVectorb  =  FpFlare::SetPos1
undefined4 FpFlare::SetPos1(int this,undefined8 param_2)

{
  int iVar1;
  undefined8 uVar2;
  float fVar3;
  float fVar4;
  float *pfVar5;
  undefined1 auStack_80 [16];
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
  undefined1 auStack_40 [48];
  undefined1 auStack_10 [16];
  
  iVar1 = this->i32_28;
  Matrix::Matrix(auStack_40,CApp::camera + 0x240);
  FVector::FVector(&fStack_50,auStack_10);
  pfVar5 = (float *)param_2;
  if (iVar1->f32_234 != 0.0) {
    if (iVar1->f32_24c == 0.0) {
      fStack_60 = fStack_50 - *pfVar5;
      fStack_5c = fStack_4c - pfVar5[1];
      fStack_58 = fStack_48 - pfVar5[2];
      uStack_54 = 0x3f800000;
      FVector::Normalize(&fStack_60);
      FVector::__amu(iVar1->u32_234,&fStack_60);
      *pfVar5 = *pfVar5 + fStack_60;
      pfVar5[1] = pfVar5[1] + fStack_5c;
      pfVar5[2] = pfVar5[2] + fStack_58;
    }
    else {
      fStack_70 = iVar1->f32_240;
      fStack_6c = iVar1->f32_244;
      fStack_68 = iVar1->f32_248;
      uStack_64 = 0x3f800000;
      FVector::Normalize(&fStack_70);
      FVector::__amu(iVar1->u32_234,&fStack_70);
      *pfVar5 = *pfVar5 + fStack_70;
      pfVar5[1] = pfVar5[1] + fStack_6c;
      pfVar5[2] = pfVar5[2] + fStack_68;
    }
  }
  uVar2 = FVector::FVector(auStack_80,param_2);
  FpObject::UpdateBBox(iVar1,uVar2);
  uVar2 = *(undefined8 *)pfVar5;
  fVar3 = pfVar5[2];
  fVar4 = pfVar5[3];
  iVar1->i32_2a0 = (int)uVar2;
  iVar1->i32_2a4 = (int)((ulong)uVar2 >> 0x20);
  iVar1->f32_2a8 = fVar3;
  iVar1->f32_2ac = fVar4;
  return 1;
}

// JP: 0x002a3eb0  Create__7FpFlareF7FVector7FVectorffffffi7FVector  =  FpFlare::Create
void FpFlare::Create
               (undefined4 this,undefined4 param_2,undefined4 param_3,undefined4 param_4,
               undefined4 param_5,undefined4 param_6,int param_7,undefined4 param_8,
               undefined4 param_9,int param_10,undefined4 param_11)

{
  long lVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  int iVar6;
  undefined1 auStack_e0 [16];
  undefined1 auStack_d0 [16];
  undefined1 auStack_c0 [16];
  int iStack_b0;
  undefined4 uStack_a0;
  undefined4 uStack_90;
  undefined4 uStack_80;
  undefined4 uStack_70;
  undefined4 uStack_60;
  undefined4 uStack_50;
  undefined4 uStack_40;
  undefined4 uStack_30;
  int iStack_20;
  undefined4 uStack_10;
  
  iStack_b0 = param_7;
  uStack_a0 = param_8;
  uStack_90 = param_9;
  uStack_80 = this;
  uStack_70 = param_2;
  uStack_60 = param_3;
  uStack_50 = param_4;
  uStack_40 = param_5;
  uStack_30 = param_6;
  iStack_20 = param_10;
  uStack_10 = param_11;
  PutiPrim::SetTexture(param_7,BgEffectMan::eff->i32_1c + 200,0);
  if (iStack_b0->i8_58 == '\0') {
    iStack_b0->u8_24 = iStack_b0->u8_24 & 0xfe | 1;
  }
  iVar6 = iStack_20 * iStack_20;
  if (iVar6 < 1) {
    iVar6 = 1;
  }
  lVar1 = __nw(0x390);
  uVar2 = 0;
  if (lVar1 != 0) {
    uVar2 = FpObjectFlare::FpObjectFlare(lVar1,iVar6 * 0xc + 8,0);
  }
  PutiPrim::AddObject(iStack_b0,uVar2);
  uVar3 = FVector::FVector(auStack_c0,uStack_a0);
  uVar4 = FVector::FVector(auStack_d0,uStack_90);
  uVar5 = FVector::FVector(auStack_e0,uStack_10);
  FpObjectFlare::SetData
            (uStack_80,uStack_70,uStack_60,uStack_50,uStack_40,uStack_30,uVar2,uVar3,uVar4,iStack_20
             ,uVar5);
  (**(code **)(*(int *)((int)uVar2 + 0x1e4) + 0x40))(uVar2,iVar6,iStack_b0->u8_58);
  PutiManager::AddPrim(BgEffectMan::eff,iStack_b0->u32_54,iStack_b0)
  ;
  return;
}

// JP: 0x002a40a0  Create__7FpFlareFPv  =  FpFlare::Create
void FpFlare::Create(int this,int param_2)

{
  undefined2 *puVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  uint *puVar5;
  uint *puVar6;
  bool bVar7;
  bool bVar8;
  int iVar9;
  undefined1 auStack_d0 [16];
  undefined1 auStack_c0 [16];
  undefined1 auStack_b0 [16];
  undefined1 auStack_a0 [16];
  undefined1 auStack_90 [16];
  undefined1 auStack_80 [16];
  undefined1 auStack_70 [16];
  undefined1 auStack_60 [16];
  undefined1 auStack_50 [12];
  undefined4 uStack_44;
  uint uStack_40;
  uint uStack_3c;
  uint uStack_38;
  uint uStack_34;
  uint uStack_30;
  float fStack_2c;
  uint uStack_28;
  undefined2 uStack_24;
  undefined2 uStack_22;
  int iStack_20;
  int iStack_10;
  
  iStack_20 = this;
  iStack_10 = param_2;
  FVector::FVector(auStack_50,param_2);
  puVar5 = (uint *)(param_2 + 0x10);
  bVar8 = false;
  bVar7 = true;
  puVar1 = (undefined2 *)FpPrim::InitFpFlag(uStack_44,iStack_20);
  uStack_24 = *puVar1;
  uStack_22 = puVar1[1];
  memset(&uStack_28,0,4);
  if ((long)((ulong)uStack_22._1_1_ << 0x3a) < 0) {
    uStack_28 = *puVar5;
    iStack_20->u32_48 = param_2->u32_14;
    iStack_20->u32_4c = param_2->u32_18;
    puVar5 = (uint *)(param_2 + 0x20);
    iStack_20->u8_50 = (byte)(((ulong)(byte)uStack_28 << 0x3b) >> 0x3e);
    bVar8 = (uStack_28 & 1) != 0;
    bVar7 = (long)((ulong)(byte)uStack_28 << 0x3e) < 0;
  }
  FVector::FVector(auStack_60,puVar5);
  fStack_2c = (float)puVar5[4];
  uStack_30 = puVar5[5];
  uStack_34 = puVar5[6];
  uStack_38 = puVar5[7];
  puVar6 = puVar5 + 8;
  iVar9 = 1;
  uStack_3c = 0;
  uStack_40 = 0;
  if ((long)((ulong)uStack_22._1_1_ << 0x3c) < 0) {
    uStack_3c = *puVar6;
    uStack_40 = puVar5[9];
    iVar9 = (int)(float)puVar5[10];
    if (iVar9 < 1) {
      iVar9 = 1;
    }
    puVar6 = puVar5 + 0xc;
  }
  if (((ulong)uStack_22._1_1_ & 7) >> 1 == 0) {
    fStack_2c = fStack_2c * 0.73;
  }
  if ((uStack_22 & 0x100) == 0) {
    uVar2 = FVector::FVector(auStack_80,auStack_50);
    uVar3 = FVector::FVector(auStack_90,auStack_60);
    FpFlare::Create
              (fStack_2c,uStack_30,uStack_34,uStack_38,uStack_3c,uStack_40,iStack_20,uVar2,uVar3,
               iVar9,auStack_a0);
  }
  else {
    FVector::FVector(auStack_70,puVar6);
    uVar2 = FVector::FVector(auStack_b0,auStack_50);
    uVar3 = FVector::FVector(auStack_c0,auStack_60);
    uVar4 = FVector::FVector(auStack_d0,auStack_70);
    FpFlare::Create
              (fStack_2c,uStack_30,uStack_34,uStack_38,uStack_3c,uStack_40,iStack_20,uVar2,uVar3,
               iVar9,uVar4);
  }
  iVar9 = iStack_20->i32_28;
  if (iVar9->i32_200 != 0) {
    *(byte *)(iVar9->i32_200 + 1) = *(byte *)(iVar9->i32_200 + 1) & 0xfe | bVar8;
  }
  if (iVar9->i32_200 != 0) {
    *(byte *)(iVar9->i32_200 + 1) =
         *(byte *)(iVar9->i32_200 + 1) & 0xfd | bVar7 << 1;
  }
  if ((long)((ulong)uStack_22._1_1_ << 0x3b) < 0) {
    iVar9->u8_380 = 1;
  }
  if (((ulong)uStack_22._1_1_ & 7) >> 1 == 1) {
    iVar9->u8_381 = 0;
  }
  return;
}

// JP: 0x002a4460  __ct__13FpObjectFlareFiPv  =  FpObjectFlare::FpObjectFlare
undefined8 FpObjectFlare::FpObjectFlare(undefined8 this)

{
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  undefined4 *puVar1;
  int this;
  
  FpObject::FpObject(this);
  
  *(undefined1 **)(this + 0x1e4) = FpObjectFlare::__vt;
  this->u32_210 = in_zero_lo;
  this->u32_214 = in_zero_hi;
  this->u32_218 = in_zero_udw;
  this->u32_21c = in_register_0000000c;
  this->u32_220 = in_zero_lo;
  this->u32_224 = in_zero_hi;
  this->u32_228 = in_zero_udw;
  this->u32_22c = in_register_0000000c;
  this->u32_240 = in_zero_lo;
  this->u32_244 = in_zero_hi;
  this->u32_248 = in_zero_udw;
  this->u32_24c = in_register_0000000c;
  this->u32_280 = in_zero_lo;
  this->u32_284 = in_zero_hi;
  this->u32_288 = in_zero_udw;
  this->u32_28c = in_register_0000000c;
  this->u32_290 = in_zero_lo;
  this->u32_294 = in_zero_hi;
  this->u32_298 = in_zero_udw;
  this->u32_29c = in_register_0000000c;
  this->u32_2a0 = in_zero_lo;
  this->u32_2a4 = in_zero_hi;
  this->u32_2a8 = in_zero_udw;
  this->u32_2ac = in_register_0000000c;
  this->u32_2b0 = in_zero_lo;
  this->u32_2b4 = in_zero_hi;
  this->u32_2b8 = in_zero_udw;
  this->u32_2bc = in_register_0000000c;
  this->u32_2c0 = in_zero_lo;
  this->u32_2c4 = in_zero_hi;
  this->u32_2c8 = in_zero_udw;
  this->u32_2cc = in_register_0000000c;
  this->u32_2d0 = in_zero_lo;
  this->u32_2d4 = in_zero_hi;
  this->u32_2d8 = in_zero_udw;
  this->u32_2dc = in_register_0000000c;
  puVar1 = (undefined4 *)(this + 0x2e0);
  do {
    *puVar1 = in_zero_lo;
    puVar1[1] = in_zero_hi;
    puVar1[2] = in_zero_udw;
    puVar1[3] = in_register_0000000c;
    puVar1 = puVar1 + 4;
  } while (puVar1 != (undefined4 *)(this + 800));
  this->u32_320 = in_zero_lo;
  this->u32_324 = in_zero_hi;
  this->u32_328 = in_zero_udw;
  this->u32_32c = in_register_0000000c;
  this->u32_370 = in_zero_lo;
  this->u32_374 = in_zero_hi;
  this->u32_378 = in_zero_udw;
  this->u32_37c = in_register_0000000c;
  this->u32_210 = 0;
  this->u32_214 = 0;
  this->u32_218 = 0;
  this->u32_21c = 0x3f800000;
  this->u32_220 = 0x43000000;
  this->u32_224 = 0x43000000;
  this->u32_228 = 0x43000000;
  this->u32_22c = 0x43000000;
  this->u32_370 = 0;
  this->u32_374 = 0;
  this->u32_378 = 0;
  this->u32_37c = 0;
  this->u32_230 = 0;
  this->u32_234 = 0;
  this->u32_240 = 0;
  this->u32_244 = 0;
  this->u32_248 = 0;
  this->u32_24c = 0;
  this->u32_250 = 0x3f4ccccd;
  this->u32_254 = 0x3f800000;
  this->u32_258 = 0;
  this->u32_25c = 0;
  this->u32_260 = 0;
  this->u32_264 = 0;
  this->u32_268 = 0;
  memset((void *)(this + 0x270),0,0xf0);
  this->u32_360 = 1;
  this->u8_380 = 0;
  this->u8_381 = 1;
  return this;
}

// JP: 0x002a46a0  __dt__13FpObjectFlareFv  =  FpObjectFlare::~FpObjectFlare
int FpObjectFlare::~FpObjectFlare(int this,short param_2)

{
  if (this != 0) {
    *(undefined1 **)(this + 0x1e4) = FpObjectFlare::__vt;
    FpObject::~FpObject(this,0);
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}

// JP: 0x002a4720  SetData__13FpObjectFlareF7FVector7FVectorffffffi7FVector  =  FpObjectFlare::SetData
/* WARNING: Function: fptodp replaced with injection: fptodp */

void FpObjectFlare::SetData
               (undefined4 this,undefined4 param_2,undefined4 param_3,float param_4,
               undefined4 param_5,undefined4 param_6,int param_7,undefined8 *param_8,
               undefined8 *param_9,undefined4 param_10,undefined8 *param_11)

{
  undefined8 uVar1;
  int iVar2;
  long lVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  float fVar6;
  
  uVar1 = *param_8;
  uVar4 = param_8->u32_1;
  uVar5 = *(undefined4 *)((int)param_8 + 0xc);
  param_7->i32_210 = (int)uVar1;
  param_7->i32_214 = (int)((ulong)uVar1 >> 0x20);
  param_7->u32_218 = uVar4;
  param_7->u32_21c = uVar5;
  uVar1 = *param_9;
  uVar4 = param_9->u32_1;
  uVar5 = *(undefined4 *)((int)param_9 + 0xc);
  param_7->i32_220 = (int)uVar1;
  param_7->i32_224 = (int)((ulong)uVar1 >> 0x20);
  param_7->u32_228 = uVar4;
  param_7->u32_22c = uVar5;
  param_7->u32_230 = this;
  param_7->u32_234 = param_2;
  uVar1 = *param_11;
  uVar4 = param_11->u32_1;
  uVar5 = *(undefined4 *)((int)param_11 + 0xc);
  param_7->i32_240 = (int)uVar1;
  param_7->i32_244 = (int)((ulong)uVar1 >> 0x20);
  param_7->u32_248 = uVar4;
  param_7->u32_24c = uVar5;
  param_7->u32_260 = param_3;
  if (param_4 == 0.0) {
    param_7->u32_250 = 0x3f4ccccd;
  }
  else {
    param_7->f32_250 = param_4;
  }
  param_7->u32_254 = 0x3f800000;
  param_7->u32_264 = param_5;
  param_7->u32_268 = param_6;
  iVar2 = rand();
  fVar6 = param_7->f32_264 * (((float)iVar2 / 2.1474836e+09) * 2.0 - 1.0);
  lVar3 = _dpfle((double)param_7->f32_268,0x3fe0000000000000);
  if (lVar3 == 0) {
    param_7->f32_258 =
         param_7->f32_254 -
         (param_7->f32_268 - 0.5) *
         (param_7->f32_254 - param_7->f32_250) * 2.0;
    param_7->f32_25c = param_7->f32_260 * -0.001 * (fVar6 + 1.0);
  }
  else {
    param_7->f32_258 =
         param_7->f32_250 +
         param_7->f32_268 * (param_7->f32_254 - param_7->f32_250) *
         2.0;
    param_7->f32_25c = param_7->f32_260 * 0.001 * (fVar6 + 1.0);
  }
  param_7->u32_360 = param_10;
  return;
}

// JP: 0x002a4930  CreateData__13FpObjectFlareFib  =  FpObjectFlare::CreateData
void FpObjectFlare::CreateData(int this)

{
  this->u32_270 = 0x42f00000;
  this->u32_274 = 0;
  this->u32_278 = 0;
  this->u32_2b0 = this->u32_230;
  this->u32_2b4 = this->u32_230;
  this->u32_2b8 = 0;
  this->u32_2bc = 0x3f800000;
  this->u32_280 = 0;
  this->u32_284 = 0;
  this->u32_288 = 0;
  this->u32_28c = 0x3f800000;
  this->u32_290 = 0;
  this->u32_294 = 0;
  this->u32_298 = 0;
  this->u32_29c = 0x3f800000;
  this->i32_2a0 = (int)this->u64_210;
  this->i32_2a4 = (int)((ulong)this->u64_210 >> 0x20);
  this->u32_2a8 = this->u32_218;
  this->u32_2ac = this->u32_21c;
  this->u32_2c0 = 0x3f800000;
  this->u32_2c4 = 0x3f800000;
  this->u32_2c8 = 0x3f800000;
  this->u32_2cc = 0x3f800000;
  this->u32_2d0 = 0;
  this->u32_2d4 = 0;
  this->u32_2d8 = 0;
  this->u32_2dc = 0x3f800000;
  this->u32_2e0 = 0;
  this->u32_2e4 = 0;
  this->u32_2e8 = 0;
  this->u32_2ec = 0x3f800000;
  this->u32_2f0 = 0;
  this->u32_2f4 = 0;
  this->u32_2f8 = 0;
  this->u32_2fc = 0x3f800000;
  this->u32_300 = 0;
  this->u32_304 = 0;
  this->u32_308 = 0;
  this->u32_30c = 0x3f800000;
  this->u32_310 = 0;
  this->u32_314 = 0;
  this->u32_318 = 0;
  this->u32_31c = 0x3f800000;
  this->u32_320 = this->u32_220;
  this->u32_324 = this->u32_224;
  this->u32_328 = this->u32_228;
  this->u32_32c = this->u32_22c;
  this->u32_330 = 0;
  this->u32_334 = 0;
  this->u32_338 = 0;
  this->u32_33c = 0x3f800000;
  this->u32_340 = 0x3f800000;
  this->u32_344 = 0;
  this->u32_348 = 0x3f800000;
  this->u32_34c = 0x3f800000;
  this->f32_338 = this->f32_338 / (float)this->i32_360;
  this->f32_33c = this->f32_33c / (float)this->i32_360;
  this->f32_340 = this->f32_340 / (float)this->i32_360;
  this->f32_344 = this->f32_344 / (float)this->i32_360;
  this->f32_348 = this->f32_348 / (float)this->i32_360;
  this->f32_34c = this->f32_34c / (float)this->i32_360;
  return;
}

// JP: 0x002a4d10  Init__13FpObjectFlareFib  =  FpObjectFlare::Init
void FpObjectFlare::Init(int this,undefined4 param_2,char param_3)

{
  undefined4 uVar1;
  undefined8 uVar2;
  int iVar3;
  undefined1 auStack_c0 [16];
  float fStack_b0;
  float fStack_ac;
  float fStack_a8;
  undefined4 uStack_a4;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  float fStack_90;
  float fStack_8c;
  float fStack_88;
  undefined1 auStack_80 [48];
  undefined1 auStack_50 [16];
  float fStack_40;
  float fStack_3c;
  float fStack_38;
  int iStack_30;
  undefined4 uStack_20;
  char cStack_10;
  
  this->u32_1f4 = param_2;
  this->u32_1f8 = param_2;
  iVar3 = this->i32_1f8;
  iStack_30 = this;
  uStack_20 = param_2;
  cStack_10 = param_3;
  uVar2 = __nwa(iVar3 * 0xf0 + 0x10);
  uVar1 = __construct_new_array(uVar2,0x299b50,0,0xf0,iVar3);
  iStack_30->u32_1fc = uVar1;
  memset(*(void **)(iStack_30 + 0x1fc),0,(long)(iStack_30->i32_1f8 * 0xf0));
  for (iVar3 = 0; iVar3 < iStack_30->i32_1f8; iVar3 = iVar3 + 1) {
    (**(code **)(iStack_30->i32_1e4 + 0x4c))(iStack_30,iVar3,0);
    *(undefined4 *)(iStack_30->i32_1fc + iVar3 * 0xf0 + 0xb0) =
         iStack_30->u32_320;
    *(undefined4 *)(iStack_30->i32_1fc + iVar3 * 0xf0 + 0xb4) =
         iStack_30->u32_324;
    *(undefined4 *)(iStack_30->i32_1fc + iVar3 * 0xf0 + 0xb8) =
         iStack_30->u32_328;
  }
  iStack_30->u32_1e0 = 0xffffffff;
  if (iStack_30->f32_24c == 0.0) {
    iStack_30->u8_14 = iStack_30->u8_14 & 0xfe | 1;
  }
  iStack_30->u16_14 = iStack_30->u16_14 & 0xe01f;
  if (cStack_10 == '\0') {
    PutiObject::SetRegTest(iStack_30,0x33001);
  }
  else {
    PutiObject::SetRegTest(iStack_30,0x73001);
  }
  FVector::FVector(&fStack_40,iStack_30 + 0x210);
  Matrix::Matrix(auStack_80,CApp::camera + 0x240);
  FVector::FVector(&fStack_90,auStack_50);
  if (iStack_30->f32_234 != 0.0) {
    if (iStack_30->f32_24c == 0.0) {
      fStack_a0 = fStack_90 - fStack_40;
      fStack_9c = fStack_8c - fStack_3c;
      fStack_98 = fStack_88 - fStack_38;
      uStack_94 = 0x3f800000;
      FVector::Normalize(&fStack_a0);
      FVector::__amu(iStack_30->u32_234,&fStack_a0);
      fStack_40 = fStack_40 + fStack_a0;
      fStack_3c = fStack_3c + fStack_9c;
      fStack_38 = fStack_38 + fStack_98;
    }
    else {
      fStack_b0 = iStack_30->f32_240;
      fStack_ac = iStack_30->f32_244;
      fStack_a8 = iStack_30->f32_248;
      uStack_a4 = 0x3f800000;
      FVector::Normalize(&fStack_b0);
      FVector::__amu(iStack_30->u32_234,&fStack_b0);
      fStack_40 = fStack_40 + fStack_b0;
      fStack_3c = fStack_3c + fStack_ac;
      fStack_38 = fStack_38 + fStack_a8;
    }
  }
  uVar2 = FVector::FVector(auStack_c0,&fStack_40);
  FpObject::InitBBox(iStack_30,uVar2,1);
  return;
}

// JP: 0x002a5110  CalculateFunc__13FpObjectFlareFv  =  FpObjectFlare::CalculateFunc
void FpObjectFlare::CalculateFunc(undefined8 this)

{
  char cVar1;
  int iVar2;
  undefined8 uVar3;
  int this;
  float fVar5;
  float fVar6;
  undefined1 auStack_20 [16];
  float fStack_10;
  float fStack_c;
  float fStack_8;
  undefined4 uStack_4;
  
  
  fVar5 = (float)FpPrim::GetFrameSpeed(this->u32_8);
  if (this->f32_260 == 0.0) {
    fVar5 = this->f32_254;
    fVar6 = this->f32_250;
    iVar2 = rand();
    this->f32_258 =
         this->f32_250 + ((fVar5 - fVar6) * (float)iVar2) / 2.1474836e+09;
    fVar5 = this->f32_22c * this->f32_258;
    if (127.0 < fVar5) {
      fVar5 = 127.0;
    }
    else if (fVar5 < 0.0) {
      fVar5 = 0.0;
    }
    this->f32_32c = fVar5;
    if (this->i8_380 != '\0') {
      iVar2 = rand();
      this->f32_320 = (((float)iVar2 * 0.5) / 2.1474836e+09 + 0.5) * 128.0;
      iVar2 = rand();
      this->f32_324 = (((float)iVar2 * 0.5) / 2.1474836e+09 + 0.5) * 128.0;
      iVar2 = rand();
      this->f32_328 = (((float)iVar2 * 0.5) / 2.1474836e+09 + 0.5) * 128.0;
    }
  }
  else if (0.0 < this->f32_260) {
    iVar2 = rand();
    fVar6 = this->f32_264 * (((float)iVar2 / 2.1474836e+09) * 2.0 - 1.0);
    this->f32_258 = this->f32_258 + this->f32_25c;
    if (this->f32_254 < this->f32_258) {
      this->u32_258 = this->u32_254;
      this->f32_25c = fVar5 * this->f32_260 * -0.001 * (fVar6 + 1.0);
      if (this->i8_380 != '\0') {
        this->i32_220 = (int)this->u64_320;
        this->i32_224 = (int)((ulong)this->u64_320 >> 0x20);
        this->u32_228 = this->u32_328;
        this->u32_22c = this->u32_32c;
      }
    }
    else if (this->f32_258 < this->f32_250) {
      this->u32_258 = this->u32_250;
      this->f32_25c = this->f32_260 * 0.001 * (fVar6 + 1.0);
      if (this->i8_380 != '\0') {
        iVar2 = rand();
        fVar6 = (((float)iVar2 * 0.5) / 2.1474836e+09 + 0.5) * 128.0;
        iVar2 = rand();
        fVar5 = (((float)iVar2 * 0.5) / 2.1474836e+09 + 0.5) * 128.0;
        iVar2 = rand();
        fStack_10 = (((float)iVar2 * 0.5) / 2.1474836e+09 + 0.5) * 128.0;
        uStack_4 = 0x43000000;
        this->f32_370 = fStack_10;
        this->f32_374 = fVar5;
        this->f32_378 = fVar6;
        this->u32_37c = 0x43000000;
        fStack_c = fVar5;
        fStack_8 = fVar6;
      }
    }
    fVar5 = this->f32_22c * this->f32_258;
    if (127.0 < fVar5) {
      fVar5 = 127.0;
    }
    else if (fVar5 < 0.0) {
      fVar5 = 0.0;
    }
    this->f32_32c = fVar5;
    if (this->i8_380 != '\0') {
      fVar5 = (this->f32_258 - this->f32_250) /
              (this->f32_254 - this->f32_250);
      fVar6 = 1.0 - fVar5;
      this->f32_320 =
           this->f32_370 * fVar5 + this->f32_220 * fVar6;
      this->f32_324 =
           this->f32_374 * fVar5 + this->f32_224 * fVar6;
      this->f32_328 =
           this->f32_378 * fVar5 + this->f32_228 * fVar6;
    }
  }
  else if (this->f32_260 < 0.0) {
    this->u32_32c = this->u32_22c;
  }
  uVar3 = FVector::FVector(auStack_20,this + 0x240);
  cVar1 = FpObjectFlare::CalcFpFlareVertex(this->u32_234,this,uVar3)
  ;
  if (cVar1 == '\0') {
    this->u32_1f4 = 0;
  }
  return;
}

// JP: 0x002a56c0  CalcFpFlareVertex__13FpObjectFlareF7FVectorf  =  FpObjectFlare::CalcFpFlareVertex
undefined8
FpObjectFlare::CalcFpFlareVertex(float this,undefined8 param_2,undefined8 param_3)

{
  undefined1 auVar1 [16];
  undefined1 auVar2 [16];
  int iVar3;
  undefined8 uVar4;
  undefined1 (*pauVar5) [16];
  int iVar6;
  int iVar7;
  int iVar8;
  float *pfVar9;
  int iVar10;
  float fVar11;
  float fVar12;
  undefined1 in_vf0 [16];
  undefined1 auVar13 [16];
  undefined1 auVar14 [16];
  undefined4 uVar15;
  undefined1 auStack_340 [16];
  undefined1 auStack_330 [16];
  undefined1 auStack_320 [16];
  undefined1 auStack_310 [16];
  undefined1 auStack_300 [16];
  undefined1 auStack_2f0 [16];
  undefined1 auStack_2e0 [16];
  undefined1 auStack_2d0 [16];
  undefined1 auStack_2c0 [16];
  undefined1 auStack_2b0 [16];
  undefined1 auStack_2a0 [16];
  undefined1 auStack_290 [16];
  undefined1 auStack_280 [16];
  undefined1 auStack_270 [16];
  undefined1 auStack_260 [16];
  undefined4 uStack_250;
  undefined4 uStack_24c;
  undefined4 uStack_248;
  undefined4 uStack_244;
  undefined4 uStack_240;
  undefined4 uStack_23c;
  undefined4 uStack_238;
  undefined4 uStack_234;
  undefined4 uStack_230;
  undefined4 uStack_22c;
  undefined4 uStack_228;
  undefined4 uStack_224;
  undefined4 uStack_220;
  undefined4 uStack_21c;
  undefined4 uStack_218;
  undefined4 uStack_214;
  undefined4 uStack_210;
  undefined4 uStack_20c;
  undefined4 uStack_208;
  undefined4 uStack_204;
  undefined4 uStack_200;
  undefined4 uStack_1fc;
  undefined4 uStack_1f8;
  undefined4 uStack_1f4;
  undefined4 uStack_1f0;
  undefined4 uStack_1ec;
  undefined4 uStack_1e8;
  undefined4 uStack_1e4;
  undefined1 auStack_1e0 [16];
  undefined1 auStack_1d0 [16];
  undefined1 auStack_1c0 [16];
  undefined4 uStack_1b0;
  undefined4 uStack_1ac;
  undefined4 uStack_1a8;
  undefined4 uStack_1a4;
  undefined4 uStack_1a0;
  undefined4 uStack_19c;
  undefined4 uStack_198;
  undefined4 uStack_194;
  undefined4 uStack_190;
  undefined4 uStack_18c;
  undefined4 uStack_188;
  undefined4 uStack_184;
  undefined1 auStack_180 [16];
  undefined1 auStack_170 [16];
  float fStack_160;
  float fStack_15c;
  float fStack_158;
  undefined4 uStack_154;
  float fStack_150;
  float fStack_14c;
  float fStack_148;
  undefined4 uStack_144;
  float fStack_140;
  float fStack_13c;
  float fStack_138;
  undefined4 uStack_134;
  undefined1 auStack_130 [16];
  float fStack_120;
  float fStack_11c;
  float fStack_118;
  undefined4 uStack_114;
  float fStack_110;
  float fStack_10c;
  float fStack_108;
  undefined4 uStack_104;
  float fStack_100;
  float fStack_fc;
  float fStack_f8;
  undefined1 auStack_f0 [16];
  float fStack_e0;
  float fStack_dc;
  float fStack_d8;
  undefined4 uStack_d4;
  float fStack_d0;
  float fStack_cc;
  float fStack_c8;
  undefined4 uStack_c4;
  float fStack_c0;
  float fStack_bc;
  float fStack_b8;
  undefined4 uStack_b4;
  undefined1 auStack_b0 [16];
  undefined1 auStack_a0 [16];
  float fStack_90;
  float fStack_8c;
  float fStack_88;
  undefined1 auStack_80 [48];
  undefined1 auStack_50 [16];
  undefined1 auStack_40 [64];
  
  uVar4 = FVector::FVector(auStack_130,param_3);
  FpObject::GetRotMatrix(auStack_40,param_2,uVar4);
  Matrix::Matrix(auStack_80,CApp::camera + 0x240);
  FVector::FVector(&fStack_90,auStack_50);
  iVar10 = (int)param_2;
  fStack_160 = (iVar10->f32_2b0 / 2.0) * iVar10->f32_2c0;
  fStack_14c = (iVar10->f32_2b4 / 2.0) * iVar10->f32_2c4;
  fStack_158 = (iVar10->f32_2b8 / 2.0) * iVar10->f32_2c8;
  fStack_140 = -fStack_160;
  fStack_13c = -fStack_14c;
  uStack_134 = 0x3f800000;
  iVar10->f32_2e0 = fStack_140;
  iVar10->f32_2e4 = fStack_13c;
  iVar10->f32_2e8 = fStack_158;
  iVar10->u32_2ec = 0x3f800000;
  fStack_150 = -fStack_160;
  fStack_148 = -fStack_158;
  uStack_144 = 0x3f800000;
  iVar10->f32_2f0 = fStack_150;
  iVar10->f32_2f4 = fStack_14c;
  iVar10->f32_2f8 = fStack_148;
  iVar10->u32_2fc = 0x3f800000;
  fStack_15c = -fStack_14c;
  uStack_154 = 0x3f800000;
  iVar10->f32_300 = fStack_160;
  iVar10->f32_304 = fStack_15c;
  iVar10->f32_308 = fStack_158;
  iVar10->u32_30c = 0x3f800000;
  fVar11 = (float)iVar10->i32_360;
  auVar13 = _lqc2(*(undefined1 (*) [16])(iVar10 + 0x2f0));
  auVar14 = _lqc2(*(undefined1 (*) [16])(iVar10 + 0x2e0));
  auVar13 = _vsub(auVar13,auVar14);
  auStack_290 = _sqc2(auVar13);
  fStack_138 = fStack_158;
  FVector::FVector(auStack_170,auStack_290);
  auVar13 = _qmtc2(fVar11);
  _vdiv(in_vf0,0,auVar13,0);
  auVar13 = _lqc2(auStack_170);
  uVar15 = _vwaitq();
  auVar13 = _vmulq(auVar13,uVar15);
  auStack_260 = _sqc2(auVar13);
  FVector::FVector(auStack_a0,auStack_260);
  fVar11 = (float)iVar10->i32_360;
  auVar13 = _lqc2(*(undefined1 (*) [16])(iVar10 + 0x300));
  auVar14 = _lqc2(*(undefined1 (*) [16])(iVar10 + 0x2e0));
  auVar13 = _vsub(auVar13,auVar14);
  auStack_2a0 = _sqc2(auVar13);
  FVector::FVector(auStack_180,auStack_2a0);
  auVar13 = _qmtc2(fVar11);
  _vdiv(in_vf0,0,auVar13,0);
  auVar13 = _lqc2(auStack_180);
  uVar15 = _vwaitq();
  auVar13 = _vmulq(auVar13,uVar15);
  auStack_270 = _sqc2(auVar13);
  FVector::FVector(auStack_b0,auStack_270);
  auVar13 = _lqc2(*(undefined1 (*) [16])(iVar10 + 0x2e0));
  auVar14 = _lqc2(auStack_a0);
  auVar13 = _vadd(auVar13,auVar14);
  auStack_2b0 = _sqc2(auVar13);
  FVector::FVector(&uStack_190,auStack_2b0);
  iVar10->u32_2f0 = uStack_190;
  iVar10->u32_2f4 = uStack_18c;
  iVar10->u32_2f8 = uStack_188;
  iVar10->u32_2fc = uStack_184;
  auVar13 = _lqc2(*(undefined1 (*) [16])(iVar10 + 0x2e0));
  auVar14 = _lqc2(auStack_b0);
  auVar13 = _vadd(auVar13,auVar14);
  auStack_2c0 = _sqc2(auVar13);
  FVector::FVector(&uStack_1a0,auStack_2c0);
  iVar10->u32_300 = uStack_1a0;
  iVar10->u32_304 = uStack_19c;
  iVar10->u32_308 = uStack_198;
  iVar10->u32_30c = uStack_194;
  auVar13 = _lqc2(*(undefined1 (*) [16])(iVar10 + 0x2e0));
  auVar14 = _lqc2(auStack_a0);
  auVar13 = _vadd(auVar13,auVar14);
  auStack_340 = _sqc2(auVar13);
  FVector::FVector(auStack_1c0,auStack_340);
  auVar13 = _lqc2(auStack_1c0);
  auVar14 = _lqc2(auStack_b0);
  auVar13 = _vadd(auVar13,auVar14);
  auStack_2d0 = _sqc2(auVar13);
  FVector::FVector(&uStack_1b0,auStack_2d0);
  iVar10->u32_310 = uStack_1b0;
  iVar10->u32_314 = uStack_1ac;
  iVar10->u32_318 = uStack_1a8;
  iVar10->u32_31c = uStack_1a4;
  FVector::FVector(&fStack_c0,iVar10 + 0x2a0);
  pfVar9 = (float *)param_3;
  if (this != 0.0) {
    if (pfVar9[3] == 0.0) {
      fStack_d0 = fStack_90 - fStack_c0;
      fStack_cc = fStack_8c - fStack_bc;
      fStack_c8 = fStack_88 - fStack_b8;
      uStack_c4 = 0x3f800000;
      FVector::Normalize(&fStack_d0);
      FVector::__amu(this,&fStack_d0);
      fStack_c0 = fStack_c0 + fStack_d0;
      fStack_bc = fStack_bc + fStack_cc;
      fStack_b8 = fStack_b8 + fStack_c8;
    }
    else {
      fStack_e0 = *pfVar9;
      fStack_dc = pfVar9[1];
      fStack_d8 = pfVar9[2];
      uStack_d4 = 0x3f800000;
      FVector::Normalize(&fStack_e0);
      FVector::__amu(this,&fStack_e0);
      fStack_c0 = fStack_c0 + fStack_e0;
      fStack_bc = fStack_bc + fStack_dc;
      fStack_b8 = fStack_b8 + fStack_d8;
    }
  }
  uStack_b4 = 0;
  iVar8 = iVar10->i32_1fc;
  for (iVar7 = 0; iVar7 < iVar10->i32_1f8; iVar7 = iVar7 + 1) {
    if (iVar10->i32_360 == 0) {
      trap(7);
    }
    fVar11 = (float)(iVar7 / iVar10->i32_360);
    if (iVar10->i32_360 == 0) {
      trap(7);
    }
    fVar12 = (float)(iVar7 % iVar10->i32_360);
    auVar13 = _lqc2(auStack_b0);
    auVar14 = _qmtc2(fVar12);
    auVar13 = _vmulbc(auVar13,auVar14);
    auStack_2e0 = _sqc2(auVar13);
    FVector::FVector(auStack_1e0,auStack_2e0);
    auVar13 = _lqc2(auStack_a0);
    auVar14 = _qmtc2(fVar11);
    auVar13 = _vmulbc(auVar13,auVar14);
    auStack_2f0 = _sqc2(auVar13);
    FVector::FVector(auStack_1d0,auStack_2f0);
    auVar13 = _lqc2(auStack_1d0);
    auVar14 = _lqc2(auStack_1e0);
    auVar13 = _vadd(auVar13,auVar14);
    auStack_280 = _sqc2(auVar13);
    FVector::FVector(auStack_f0,auStack_280);
    auVar13 = _lqc2(*(undefined1 (*) [16])(iVar10 + 0x2e0));
    auVar14 = _lqc2(auStack_f0);
    auVar13 = _vadd(auVar13,auVar14);
    auStack_300 = _sqc2(auVar13);
    FVector::FVector(&uStack_1f0,auStack_300);
    iVar8->u32_70 = uStack_1f0;
    iVar8->u32_74 = uStack_1ec;
    iVar8->u32_78 = uStack_1e8;
    iVar8->u32_7c = uStack_1e4;
    auVar13 = _lqc2(*(undefined1 (*) [16])(iVar10 + 0x2f0));
    auVar14 = _lqc2(auStack_f0);
    auVar13 = _vadd(auVar13,auVar14);
    auStack_310 = _sqc2(auVar13);
    FVector::FVector(&uStack_200,auStack_310);
    iVar8->u32_80 = uStack_200;
    iVar8->u32_84 = uStack_1fc;
    iVar8->u32_88 = uStack_1f8;
    iVar8->u32_8c = uStack_1f4;
    auVar13 = _lqc2(*(undefined1 (*) [16])(iVar10 + 0x300));
    auVar14 = _lqc2(auStack_f0);
    auVar13 = _vadd(auVar13,auVar14);
    auStack_320 = _sqc2(auVar13);
    FVector::FVector(&uStack_210,auStack_320);
    iVar8->u32_90 = uStack_210;
    iVar8->u32_94 = uStack_20c;
    iVar8->u32_98 = uStack_208;
    iVar8->u32_9c = uStack_204;
    auVar13 = _lqc2(*(undefined1 (*) [16])(iVar10 + 0x310));
    auVar14 = _lqc2(auStack_f0);
    auVar13 = _vadd(auVar13,auVar14);
    auStack_330 = _sqc2(auVar13);
    FVector::FVector(&uStack_220,auStack_330);
    iVar8->u32_a0 = uStack_220;
    iVar8->u32_a4 = uStack_21c;
    iVar8->u32_a8 = uStack_218;
    iVar8->u32_ac = uStack_214;
    fVar12 = iVar10->f32_340 * fVar12;
    fVar11 = iVar10->f32_33c * fVar11;
    iVar8->f32_c0 = iVar10->f32_330 + fVar12;
    iVar8->f32_c4 = iVar10->f32_334 + fVar11;
    iVar8->f32_c8 = iVar10->f32_338 + fVar12;
    iVar8->f32_cc = iVar10->f32_33c + fVar11;
    iVar8->f32_d0 = iVar10->f32_340 + fVar12;
    iVar8->f32_d4 = iVar10->f32_344 + fVar11;
    iVar8->f32_d8 = iVar10->f32_348 + fVar12;
    iVar8->f32_dc = iVar10->f32_34c + fVar11;
    if ((iVar10->u8_14 & 1) == 0) {
      for (iVar6 = 0; iVar6 < 4; iVar6 = iVar6 + 1) {
        Matrix::ApplyMatrix(&uStack_250,auStack_40,iVar8 + iVar6 * 0x10 + 0x70);
        iVar3 = iVar8 + iVar6 * 0x10;
        iVar3->u32_70 = uStack_250;
        iVar3->u32_74 = uStack_24c;
        iVar3->u32_78 = uStack_248;
        iVar3->u32_7c = uStack_244;
        pauVar5 = (undefined1 (*) [16])(iVar8 + iVar6 * 0x10 + 0x70);
        auVar13._4_4_ = fStack_bc;
        auVar13._0_4_ = fStack_c0;
        auVar13._8_4_ = fStack_b8;
        auVar13._12_4_ = uStack_b4;
        auVar14 = _lqc2(auVar13);
        auVar13 = _lqc2(*pauVar5);
        auVar13 = _vadd(auVar13,auVar14);
        auVar13 = _sqc2(auVar13);
        *pauVar5 = auVar13;
      }
    }
    else {
      for (iVar6 = 0; iVar6 < 4; iVar6 = iVar6 + 1) {
        Matrix::ApplyMatrix(&uStack_230,auStack_40,iVar8 + iVar6 * 0x10 + 0x70);
        iVar3 = iVar8 + iVar6 * 0x10;
        iVar3->u32_70 = uStack_230;
        iVar3->u32_74 = uStack_22c;
        iVar3->u32_78 = uStack_228;
        iVar3->u32_7c = uStack_224;
        Matrix::ApplyMatrix(&uStack_240,0x4213c0,iVar8 + iVar6 * 0x10 + 0x70);
        iVar3 = iVar8 + iVar6 * 0x10;
        iVar3->u32_70 = uStack_240;
        iVar3->u32_74 = uStack_23c;
        iVar3->u32_78 = uStack_238;
        iVar3->u32_7c = uStack_234;
        pauVar5 = (undefined1 (*) [16])(iVar8 + iVar6 * 0x10 + 0x70);
        auVar14._4_4_ = fStack_bc;
        auVar14._0_4_ = fStack_c0;
        auVar14._8_4_ = fStack_b8;
        auVar14._12_4_ = uStack_b4;
        auVar14 = _lqc2(auVar14);
        auVar13 = _lqc2(*pauVar5);
        auVar13 = _vadd(auVar13,auVar14);
        auVar13 = _sqc2(auVar13);
        *pauVar5 = auVar13;
      }
    }
    iVar8 = iVar8 + 0xf0;
  }
  if (pfVar9[3] == 0.0) {
    uVar4 = 1;
  }
  else {
    FVector::FVector(&fStack_100,iVar10 + 0x2a0);
    fStack_110 = fStack_90 - fStack_100;
    fStack_10c = fStack_8c - fStack_fc;
    fStack_108 = fStack_88 - fStack_f8;
    uStack_104 = 0x3f800000;
    FVector::Normalize(&fStack_110);
    fStack_120 = *pfVar9;
    fStack_11c = pfVar9[1];
    fStack_118 = pfVar9[2];
    uStack_114 = 0x3f800000;
    FVector::Normalize(&fStack_120);
    auVar2._4_4_ = fStack_10c;
    auVar2._0_4_ = fStack_110;
    auVar2._8_4_ = fStack_108;
    auVar2._12_4_ = uStack_104;
    auVar13 = _lqc2(auVar2);
    auVar1._4_4_ = fStack_11c;
    auVar1._0_4_ = fStack_120;
    auVar1._8_4_ = fStack_118;
    auVar1._12_4_ = uStack_114;
    auVar14 = _lqc2(auVar1);
    auVar13 = _vmul(auVar13,auVar14);
    auVar13 = _vaddbc(auVar13,auVar13);
    auVar13 = _vaddbc(auVar13,auVar13);
    auVar13 = _qmfc2(auVar13._0_4_);
    if (0.0 < auVar13._0_4_) {
      uVar4 = 1;
    }
    else {
      uVar4 = 0;
    }
  }
  return uVar4;
}

// JP: 0x002a6060  SetPacket__13FpObjectFlareFv  =  FpObjectFlare::SetPacket
void FpObjectFlare::SetPacket(int this)

{
  float in_zero_lo;
  float in_zero_hi;
  float in_zero_udw;
  float in_register_0000000c;
  float *pfVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  float fVar5;
  uint uVar6;
  float fStack_70;
  float fStack_6c;
  float fStack_68;
  float fStack_64;
  float *pfStack_4c;
  float *pfStack_48;
  float *pfStack_44;
  float *pfStack_40;
  uint *puStack_3c;
  uint *puStack_38;
  float *pfStack_34;
  float *pfStack_30;
  ulong *puStack_2c;
  ulong *puStack_28;
  float *pfStack_24;
  uint uStack_20;
  float fStack_1c;
  float fStack_18;
  float fStack_14;
  int iStack_10;
  
  fStack_14 = this->f32_1f0 * *(float *)(this->i32_8 + 0x5c);
  pfStack_24 = *(float **)(this + 0x88);
  *pfStack_24 = in_zero_lo;
  pfStack_24[1] = in_zero_hi;
  pfStack_24[2] = in_zero_udw;
  pfStack_24[3] = in_register_0000000c;
  *pfStack_24 = (float)(&DAT_10000001 + this->i32_1f8 * 0xc);
  pfStack_24[3] = (float)(this->i32_1f8 * 0xc + 1U | 0x50000000);
  this->i32_88 = this->i32_88 + 0x10;
  puStack_2c = *(ulong **)(this + 0x88);
  *puStack_2c = ((ulong)this->u8_381 << 4 | 0x44) << 0x2f |
                (long)(this->i32_1f8 << 2) | 0x400000008000U | 0x3000000000000000;
  puStack_2c[1] = 0x412;
  this->i32_88 = this->i32_88 + 0x10;
  pfVar1 = *(float **)(this + 0x88);
  iStack_10 = this;
  if (this->i32_1f4 != 0) {
    fStack_18 = this->f32_32c * fStack_14;
    if (fStack_18 < 0.0) {
      fStack_18 = 0.0;
    }
    else if (128.0 < fStack_18) {
      fStack_18 = 128.0;
    }
    iVar4 = this->i32_1fc;
    fStack_70 = in_zero_lo;
    fStack_6c = in_zero_hi;
    fStack_68 = in_zero_udw;
    fStack_64 = in_register_0000000c;
    pfStack_34 = pfVar1;
    pfStack_30 = pfVar1;
    puStack_28 = puStack_2c;
    for (iVar3 = 0; iVar3 < iStack_10->i32_1f4; iVar3 = iVar3 + 1) {
      for (iVar2 = 0; iVar2 < 4; iVar2 = iVar2 + 1) {
        fStack_1c = (float)PutiObject::RotTransPer
                                     (iStack_10,iVar4 + iVar2 * 0x10 + 0x70,&fStack_70);
        uStack_20 = PutiObject::ClipFlag(iStack_10);
        *pfVar1 = *(float *)(iVar4 + iVar2 * 8 + 0xc0) * fStack_1c;
        pfVar1[1] = *(float *)(iVar4 + iVar2 * 8 + 0xc4) * fStack_1c;
        pfVar1[2] = fStack_1c;
        iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
        puStack_3c = *(uint **)(iStack_10 + 0x88);
        fVar5 = iStack_10->f32_320;
        if (fVar5 < 2.1474836e+09) {
          uVar6 = (uint)fVar5;
        }
        else {
          uVar6 = (int)(fVar5 - 2.1474836e+09) | 0x80000000;
        }
        *puStack_3c = uVar6;
        fVar5 = iStack_10->f32_324;
        if (fVar5 < 2.1474836e+09) {
          uVar6 = (uint)fVar5;
        }
        else {
          uVar6 = (int)(fVar5 - 2.1474836e+09) | 0x80000000;
        }
        puStack_3c[1] = uVar6;
        fVar5 = iStack_10->f32_328;
        if (fVar5 < 2.1474836e+09) {
          uVar6 = (uint)fVar5;
        }
        else {
          uVar6 = (int)(fVar5 - 2.1474836e+09) | 0x80000000;
        }
        puStack_3c[2] = uVar6;
        if (fStack_18 < 2.1474836e+09) {
          uVar6 = (uint)fStack_18;
        }
        else {
          uVar6 = (int)(fStack_18 - 2.1474836e+09) | 0x80000000;
        }
        puStack_3c[3] = uVar6;
        iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
        pfStack_44 = *(float **)(iStack_10 + 0x88);
        if ((iVar2 < 2) || ((uStack_20 & 0x3ffff) != 0)) {
          fStack_64 = 4.59177e-41;
        }
        *pfStack_44 = fStack_70;
        pfStack_44[1] = fStack_6c;
        pfStack_44[2] = fStack_68;
        pfStack_44[3] = fStack_64;
        iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
        pfVar1 = *(float **)(iStack_10 + 0x88);
        pfStack_4c = pfVar1;
        pfStack_48 = pfVar1;
        pfStack_40 = pfStack_44;
        puStack_38 = puStack_3c;
      }
      iVar4 = iVar4 + 0xf0;
    }
  }
  for (iVar4 = iStack_10->i32_1f4; iVar4 < iStack_10->i32_1f8; iVar4 = iVar4 + 1) {
    for (iVar3 = 0; iVar3 < 4; iVar3 = iVar3 + 1) {
      *pfVar1 = in_zero_lo;
      pfVar1[1] = in_zero_hi;
      pfVar1[2] = in_zero_udw;
      pfVar1[3] = in_register_0000000c;
      iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
      pfVar1 = *(float **)(iStack_10 + 0x88);
      *pfVar1 = in_zero_lo;
      pfVar1[1] = in_zero_hi;
      pfVar1[2] = in_zero_udw;
      pfVar1[3] = in_register_0000000c;
      iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
      pfVar1 = *(float **)(iStack_10 + 0x88);
      *pfVar1 = in_zero_lo;
      pfVar1[1] = in_zero_hi;
      pfVar1[2] = in_zero_udw;
      pfVar1[3] = in_register_0000000c;
      pfVar1[3] = 4.59177e-41;
      iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
      pfVar1 = *(float **)(iStack_10 + 0x88);
    }
  }
  return;
}

// JP: 0x002a65e0  __ct__8FpCandleFv  =  FpCandle::FpCandle
undefined8 FpCandle::FpCandle(undefined8 this)

{
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  undefined4 *puVar1;
  int this;
  
  FpPrim::FpPrim(this);
  
  *(undefined1 **)(this + 0x10) = FpCandle::__vt;
  this->u32_1c = 0x405fb0;
  this->u32_70 = in_zero_lo;
  this->u32_74 = in_zero_hi;
  this->u32_78 = in_zero_udw;
  this->u32_7c = in_register_0000000c;
  puVar1 = (undefined4 *)(this + 0x80);
  do {
    *puVar1 = in_zero_lo;
    puVar1[1] = in_zero_hi;
    puVar1[2] = in_zero_udw;
    puVar1[3] = in_register_0000000c;
    puVar1 = puVar1 + 4;
  } while (puVar1 != (undefined4 *)(this + 0xb0));
  this->u32_70 = 0;
  this->u32_74 = 0;
  this->u32_78 = 0;
  this->u32_7c = 0x3f800000;
  this->u32_80 = 0x43000000;
  this->u32_84 = 0x43000000;
  this->u32_88 = 0x43000000;
  this->u32_8c = 0x43000000;
  this->u32_90 = 0x43000000;
  this->u32_94 = 0x43000000;
  this->u32_98 = 0x43000000;
  this->u32_9c = 0x43000000;
  this->u32_a0 = 0x43000000;
  this->u32_a4 = 0x43000000;
  this->u32_a8 = 0x43000000;
  this->u32_ac = 0x43000000;
  this->u32_b0 = 0;
  return this;
}

// JP: 0x002a67a0  __dt__8FpCandleFv  =  FpCandle::~FpCandle
int FpCandle::~FpCandle(int this,short param_2)

{
  if (this != 0) {
    *(undefined1 **)(this + 0x10) = FpCandle::__vt;
    this->u32_1c = 0x405fb0;
    FpPrim::~FpPrim(this,0);
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}

// JP: 0x002a6830  SetColor1__8FpCandleFUcUcUcUc  =  FpCandle::SetColor1
undefined4
FpCandle::SetColor1(int this,ulong param_2,ulong param_3,ulong param_4,ulong param_5)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  
  if ((long)param_2 < 0) {
    fVar1 = (float)(param_2 & 0xffffffff);
  }
  else {
    fVar1 = (float)(int)param_2;
  }
  if ((long)param_3 < 0) {
    fVar2 = (float)(param_3 & 0xffffffff);
  }
  else {
    fVar2 = (float)(int)param_3;
  }
  if ((long)param_4 < 0) {
    fVar3 = (float)(param_4 & 0xffffffff);
  }
  else {
    fVar3 = (float)(int)param_4;
  }
  if ((long)param_5 < 0) {
    fVar4 = (float)(param_5 & 0xffffffff);
  }
  else {
    fVar4 = (float)(int)param_5;
  }
  this->f32_80 = fVar1 * 0.5019608;
  this->f32_84 = fVar2 * 0.5019608;
  this->f32_88 = fVar3 * 0.5019608;
  this->f32_8c = fVar4 * 0.5019608;
  return 1;
}

// JP: 0x002a6960  SetColor2__8FpCandleFUcUcUcUc  =  FpCandle::SetColor2
undefined4
FpCandle::SetColor2(int this,ulong param_2,ulong param_3,ulong param_4,ulong param_5)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  
  if ((long)param_2 < 0) {
    fVar1 = (float)(param_2 & 0xffffffff);
  }
  else {
    fVar1 = (float)(int)param_2;
  }
  if ((long)param_3 < 0) {
    fVar2 = (float)(param_3 & 0xffffffff);
  }
  else {
    fVar2 = (float)(int)param_3;
  }
  if ((long)param_4 < 0) {
    fVar3 = (float)(param_4 & 0xffffffff);
  }
  else {
    fVar3 = (float)(int)param_4;
  }
  if ((long)param_5 < 0) {
    fVar4 = (float)(param_5 & 0xffffffff);
  }
  else {
    fVar4 = (float)(int)param_5;
  }
  this->f32_90 = fVar1 * 0.5019608;
  this->f32_94 = fVar2 * 0.5019608;
  this->f32_98 = fVar3 * 0.5019608;
  this->f32_9c = fVar4 * 0.5019608;
  return 1;
}

// JP: 0x002a6a90  SetColor3__8FpCandleFUcUcUcUc  =  FpCandle::SetColor3
undefined4
FpCandle::SetColor3(int this,ulong param_2,ulong param_3,ulong param_4,ulong param_5)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  
  if ((long)param_2 < 0) {
    fVar1 = (float)(param_2 & 0xffffffff);
  }
  else {
    fVar1 = (float)(int)param_2;
  }
  if ((long)param_3 < 0) {
    fVar2 = (float)(param_3 & 0xffffffff);
  }
  else {
    fVar2 = (float)(int)param_3;
  }
  if ((long)param_4 < 0) {
    fVar3 = (float)(param_4 & 0xffffffff);
  }
  else {
    fVar3 = (float)(int)param_4;
  }
  if ((long)param_5 < 0) {
    fVar4 = (float)(param_5 & 0xffffffff);
  }
  else {
    fVar4 = (float)(int)param_5;
  }
  this->f32_a0 = fVar1 * 0.5019608;
  this->f32_a4 = fVar2 * 0.5019608;
  this->f32_a8 = fVar3 * 0.5019608;
  this->f32_ac = fVar4 * 0.5019608;
  return 1;
}

// JP: 0x002a6bc0  SetPos1__8FpCandleF7FVectorb  =  FpCandle::SetPos1
undefined4 FpCandle::SetPos1(int this,undefined8 param_2,long param_3)

{
  int iVar1;
  undefined8 uVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined1 auVar6 [16];
  undefined1 auVar7 [16];
  undefined1 auStack_40 [16];
  undefined1 auStack_30 [16];
  undefined1 auStack_20 [12];
  undefined4 uStack_14;
  undefined1 auStack_10 [16];
  
  FVector::FVector(auStack_10,this + 0x70);
  puVar5 = (undefined4 *)param_2;
  this->u32_70 = *puVar5;
  this->u32_74 = puVar5[1];
  this->u32_78 = puVar5[2];
  iVar1 = this->i32_28;
  if (param_3 != 0) {
    auVar6 = _lqc2(*(undefined1 (*) [16])(this + 0x70));
    auVar7 = _lqc2(auStack_10);
    auVar6 = _vsub(auVar6,auVar7);
    auStack_40 = _sqc2(auVar6);
    FVector::FVector(auStack_20,auStack_40);
    uStack_14 = 0;
    iVar4 = iVar1->i32_1fc;
    for (iVar3 = 0; iVar3 < iVar1->i32_1f8; iVar3 = iVar3 + 1) {
      auVar6._12_4_ = 0;
      auVar6._0_12_ = auStack_20;
      auVar7 = _lqc2(auVar6);
      auVar6 = _lqc2(*(undefined1 (*) [16])(iVar4 + 0x30));
      auVar6 = _vadd(auVar6,auVar7);
      auVar6 = _sqc2(auVar6);
      *(undefined1 (*) [16])(iVar4 + 0x30) = auVar6;
      iVar4 = iVar4 + 0xf0;
    }
  }
  uVar2 = FVector::FVector(auStack_30,param_2);
  FpObject::UpdateBBox(iVar1,uVar2);
  return 1;
}

// JP: 0x002a6ce0  Create__8FpCandleF7FVector7FVector7FVector7FVectorf  =  FpCandle::Create
void FpCandle::Create
               (undefined4 this,undefined8 param_2,undefined8 *param_3,undefined8 *param_4,
               undefined8 *param_5,undefined8 *param_6)

{
  long lVar1;
  undefined8 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  
  iVar5 = (int)param_2;
  uVar2 = *param_3;
  uVar3 = param_3->u32_1;
  uVar4 = *(undefined4 *)((int)param_3 + 0xc);
  iVar5->i32_70 = (int)uVar2;
  iVar5->i32_74 = (int)((ulong)uVar2 >> 0x20);
  iVar5->u32_78 = uVar3;
  iVar5->u32_7c = uVar4;
  iVar5->u32_b0 = this;
  iVar5->f32_74 = iVar5->f32_74 - iVar5->f32_b0 / 6.0;
  uVar2 = *param_4;
  uVar3 = param_4->u32_1;
  uVar4 = *(undefined4 *)((int)param_4 + 0xc);
  iVar5->i32_80 = (int)uVar2;
  iVar5->i32_84 = (int)((ulong)uVar2 >> 0x20);
  iVar5->u32_88 = uVar3;
  iVar5->u32_8c = uVar4;
  uVar2 = *param_5;
  uVar3 = param_5->u32_1;
  uVar4 = *(undefined4 *)((int)param_5 + 0xc);
  iVar5->i32_90 = (int)uVar2;
  iVar5->i32_94 = (int)((ulong)uVar2 >> 0x20);
  iVar5->u32_98 = uVar3;
  iVar5->u32_9c = uVar4;
  uVar2 = *param_6;
  uVar3 = param_6->u32_1;
  uVar4 = *(undefined4 *)((int)param_6 + 0xc);
  iVar5->i32_a0 = (int)uVar2;
  iVar5->i32_a4 = (int)((ulong)uVar2 >> 0x20);
  iVar5->u32_a8 = uVar3;
  iVar5->u32_ac = uVar4;
  PutiPrim::SetTexture(param_2,BgEffectMan::eff->i32_1c + 0xb4,0);
  if (iVar5->i8_58 == '\0') {
    iVar5->u8_24 = iVar5->u8_24 & 0xfe | 1;
  }
  lVar1 = __nw(0x210);
  uVar2 = 0;
  if (lVar1 != 0) {
    uVar2 = FpObjectCandle::FpObjectCandle(lVar1,0x8c,0);
  }
  PutiPrim::AddObject(param_2,uVar2);
  (**(code **)(*(int *)((int)uVar2 + 0x1e4) + 0x40))(uVar2,10,iVar5->u8_58);
  PutiManager::AddPrim(BgEffectMan::eff,iVar5->u32_54,param_2);
  return;
}

// JP: 0x002a6e30  Create__8FpCandleFPv  =  FpCandle::Create
void FpCandle::Create(int this,int param_2)

{
  int iVar1;
  undefined2 *puVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  uint *puVar7;
  bool bVar8;
  bool bVar9;
  undefined1 auStack_b0 [16];
  undefined1 auStack_a0 [16];
  undefined1 auStack_90 [16];
  undefined1 auStack_80 [16];
  undefined1 auStack_70 [16];
  undefined1 auStack_60 [16];
  undefined1 auStack_50 [16];
  undefined1 auStack_40 [12];
  undefined4 uStack_34;
  uint uStack_2c;
  uint uStack_28;
  undefined2 uStack_24;
  undefined2 uStack_22;
  int iStack_20;
  int iStack_10;
  
  iStack_20 = this;
  iStack_10 = param_2;
  FVector::FVector(auStack_40,param_2);
  puVar7 = (uint *)(param_2 + 0x10);
  bVar9 = false;
  bVar8 = true;
  puVar2 = (undefined2 *)FpPrim::InitFpFlag(uStack_34,iStack_20);
  uStack_24 = *puVar2;
  uStack_22 = puVar2[1];
  memset(&uStack_28,0,4);
  if ((long)((ulong)uStack_22._1_1_ << 0x3a) < 0) {
    uStack_28 = *puVar7;
    puVar7 = (uint *)(param_2 + 0x20);
    bVar9 = (uStack_28 & 1) != 0;
    bVar8 = (long)((ulong)(byte)uStack_28 << 0x3e) < 0;
  }
  FVector::FVector(auStack_50,puVar7);
  FVector::FVector(auStack_60,puVar7 + 4);
  FVector::FVector(auStack_70,puVar7 + 8);
  uStack_2c = puVar7[0xc];
  uVar3 = FVector::FVector(auStack_80,auStack_40);
  uVar4 = FVector::FVector(auStack_90,auStack_50);
  uVar5 = FVector::FVector(auStack_a0,auStack_60);
  uVar6 = FVector::FVector(auStack_b0,auStack_70);
  FpCandle::Create(uStack_2c,iStack_20,uVar3,uVar4,uVar5,uVar6);
  iVar1 = iStack_20->i32_28;
  if (iVar1->i32_200 != 0) {
    *(byte *)(iVar1->i32_200 + 1) = *(byte *)(iVar1->i32_200 + 1) & 0xfe | bVar9;
  }
  if (iVar1->i32_200 != 0) {
    *(byte *)(iVar1->i32_200 + 1) =
         *(byte *)(iVar1->i32_200 + 1) & 0xfd | bVar8 << 1;
  }
  return;
}

// JP: 0x002a7060  __ct__14FpObjectCandleFiPv  =  FpObjectCandle::FpObjectCandle
int FpObjectCandle::FpObjectCandle(int this,undefined4 param_2,undefined4 param_3)

{
  FpObject::FpObject(this,param_2,param_3);
  *(undefined1 **)(this + 0x1e4) = FpObjectCandle::__vt;
  return this;
}

// JP: 0x002a70b0  __dt__14FpObjectCandleFv  =  FpObjectCandle::~FpObjectCandle
int FpObjectCandle::~FpObjectCandle(int this,short param_2)

{
  if (this != 0) {
    *(undefined1 **)(this + 0x1e4) = FpObjectCandle::__vt;
    FpObject::~FpObject(this,0);
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}

// JP: 0x002a7130  CreateData__14FpObjectCandleFib  =  FpObjectCandle::CreateData
void FpObjectCandle::CreateData(int this,int param_2,long param_3)

{
  int iVar1;
  undefined8 uVar2;
  int iVar3;
  float fVar4;
  float *pfVar5;
  float fVar6;
  undefined1 auVar7 [16];
  undefined1 auVar8 [16];
  undefined1 aauStack_a0 [6] [16];
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  float fStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  float fStack_20;
  float fStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined1 auStack_10 [16];
  
  pfVar5 = (float *)(this->i32_1fc + param_2 * 0xf0);
  iVar1 = this->i32_8;
  fStack_20 = iVar1->f32_b0;
  *pfVar5 = 30.0;
  if (param_3 == 0) {
    pfVar5[1] = 0.0;
  }
  else {
    pfVar5[1] = (float)(int)(((float)param_2 * *pfVar5) / (float)this->i32_1f8);
  }
  pfVar5[2] = 0.0;
  uStack_18 = 0;
  uStack_14 = 0x3f800000;
  pfVar5[0x10] = fStack_20;
  pfVar5[0x11] = fStack_20;
  pfVar5[0x12] = 0.0;
  pfVar5[0x13] = 1.0;
  fVar6 = fStack_20 / 20.0;
  uStack_30 = 0;
  fStack_2c = -fVar6;
  uStack_28 = 0;
  uStack_24 = 0x3f800000;
  pfVar5[4] = 0.0;
  pfVar5[5] = fStack_2c;
  pfVar5[6] = 0.0;
  pfVar5[7] = 1.0;
  pfVar5[8] = -pfVar5[4];
  pfVar5[9] = pfVar5[5];
  pfVar5[10] = -pfVar5[6];
  pfVar5[0xb] = 0.0;
  *pfVar5 = *pfVar5 - (float)(int)(((pfVar5[4] * pfVar5[4] + pfVar5[6] * pfVar5[6]) * 40.0) /
                                  (fVar6 * fVar6 * 2.0));
  uVar2 = iVar1->u64_70;
  fVar6 = iVar1->f32_78;
  fVar4 = iVar1->f32_7c;
  pfVar5[0xc] = (float)uVar2;
  pfVar5[0xd] = (float)((ulong)uVar2 >> 0x20);
  pfVar5[0xe] = fVar6;
  pfVar5[0xf] = fVar4;
  auVar7 = _lqc2(*(undefined1 (*) [16])(pfVar5 + 4));
  auVar8 = _qmtc2(pfVar5[1]);
  auVar7 = _vmulbc(auVar7,auVar8);
  aauStack_a0[0] = _sqc2(auVar7);
  fStack_1c = fStack_20;
  FVector::FVector(auStack_10,aauStack_a0);
  auVar8 = _lqc2(auStack_10);
  auVar7 = _lqc2(*(undefined1 (*) [16])(pfVar5 + 0xc));
  auVar7 = _vadd(auVar7,auVar8);
  auVar7 = _sqc2(auVar7);
  *(undefined1 (*) [16])(pfVar5 + 0xc) = auVar7;
  uStack_40 = 0x3f800000;
  uStack_3c = 0x3f800000;
  uStack_38 = 0x3f800000;
  uStack_34 = 0x3f800000;
  pfVar5[0x14] = 1.0;
  pfVar5[0x15] = 1.0;
  pfVar5[0x16] = 1.0;
  pfVar5[0x17] = 1.0;
  iVar3 = rand();
  pfVar5[0x18] = 0.0;
  pfVar5[0x19] = 0.0;
  pfVar5[0x1a] = ((float)iVar3 / 2.1474836e+09) * 6.2831855;
  pfVar5[0x1b] = 1.0;
  pfVar5[0x1c] = 0.0;
  pfVar5[0x1d] = 0.0;
  pfVar5[0x1e] = 0.0;
  pfVar5[0x1f] = 1.0;
  pfVar5[0x20] = 0.0;
  pfVar5[0x21] = 0.0;
  pfVar5[0x22] = 0.0;
  pfVar5[0x23] = 1.0;
  pfVar5[0x24] = 0.0;
  pfVar5[0x25] = 0.0;
  pfVar5[0x26] = 0.0;
  pfVar5[0x27] = 1.0;
  pfVar5[0x28] = 0.0;
  pfVar5[0x29] = 0.0;
  pfVar5[0x2a] = 0.0;
  pfVar5[0x2b] = 1.0;
  pfVar5[0x2c] = iVar1->f32_80;
  pfVar5[0x2d] = iVar1->f32_84;
  pfVar5[0x2e] = iVar1->f32_88;
  pfVar5[0x2f] = iVar1->f32_8c;
  pfVar5[0x30] = 0.0;
  pfVar5[0x31] = 0.0;
  pfVar5[0x32] = 0.0;
  pfVar5[0x33] = 1.0;
  pfVar5[0x34] = 1.0;
  pfVar5[0x35] = 0.0;
  pfVar5[0x36] = 1.0;
  pfVar5[0x37] = 1.0;
  return;
}

// JP: 0x002a75d0  Init__14FpObjectCandleFib  =  FpObjectCandle::Init
void FpObjectCandle::Init(int this,undefined4 param_2,char param_3)

{
  undefined4 uVar1;
  undefined8 uVar2;
  int iVar3;
  undefined1 auStack_50 [16];
  undefined1 auStack_40 [16];
  int iStack_30;
  undefined4 uStack_20;
  char cStack_10;
  
  this->u32_1f4 = param_2;
  this->u32_1f8 = param_2;
  iVar3 = this->i32_1f8;
  iStack_30 = this;
  uStack_20 = param_2;
  cStack_10 = param_3;
  uVar2 = __nwa(iVar3 * 0xf0 + 0x10);
  uVar1 = __construct_new_array(uVar2,0x299b50,0,0xf0,iVar3);
  iStack_30->u32_1fc = uVar1;
  memset(*(void **)(iStack_30 + 0x1fc),0,(long)(iStack_30->i32_1f8 * 0xf0));
  for (iVar3 = 0; iVar3 < iStack_30->i32_1f8; iVar3 = iVar3 + 1) {
    (**(code **)(iStack_30->i32_1e4 + 0x4c))(iStack_30,iVar3,1);
  }
  iStack_30->u32_1e0 = 0xffffffff;
  iStack_30->u8_14 = iStack_30->u8_14 & 0xfe | 1;
  iStack_30->u16_14 = iStack_30->u16_14 & 0xe01f;
  if (cStack_10 == '\0') {
    PutiObject::SetRegTest(iStack_30,0x33001);
  }
  else {
    PutiObject::SetRegTest(iStack_30,0x73001);
  }
  FVector::FVector(auStack_40,iStack_30->i32_8 + 0x70);
  uVar2 = FVector::FVector(auStack_50,auStack_40);
  FpObject::InitBBox(iStack_30,uVar2,1);
  return;
}

// JP: 0x002a77a0  CalculateFunc__14FpObjectCandleFv  =  FpObjectCandle::CalculateFunc
void FpObjectCandle::CalculateFunc(undefined8 this)

{
  int iVar1;
  undefined8 uVar2;
  int iVar3;
  float *pfVar4;
  int this;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  undefined1 auVar12 [16];
  undefined1 auVar13 [16];
  undefined1 auStack_c0 [16];
  undefined1 auStack_b0 [16];
  undefined1 auStack_a0 [16];
  undefined1 auStack_90 [16];
  undefined1 auStack_80 [16];
  undefined1 auStack_70 [16];
  undefined1 auStack_60 [8];
  float fStack_58;
  float fStack_54;
  undefined1 auStack_50 [16];
  undefined1 auStack_40 [8];
  float fStack_38;
  float fStack_34;
  undefined1 auStack_30 [16];
  undefined1 auStack_20 [16];
  undefined1 auStack_10 [16];
  
  
  iVar1 = this->i32_8;
  fVar8 = (float)FpPrim::GetFrameSpeed(iVar1);
  pfVar4 = *(float **)(this + 0x1fc);
  for (iVar3 = 0; iVar3 < this->i32_1f8; iVar3 = iVar3 + 1) {
    pfVar4[1] = pfVar4[1] + fVar8;
    if (*pfVar4 <= pfVar4[1]) {
      (**(code **)(this->i32_1e4 + 0x4c))(this,iVar3,0);
    }
    fVar6 = *pfVar4;
    fVar11 = fVar6 * 0.1;
    fVar10 = fVar11 + fVar6 * 0.3;
    fVar7 = fVar10 + fVar6 * 0.3;
    if (pfVar4[1] < fVar11) {
      uVar2 = iVar1->u64_80;
      fVar6 = iVar1->f32_88;
      fVar7 = iVar1->f32_8c;
      pfVar4[0x2c] = (float)uVar2;
      pfVar4[0x2d] = (float)((ulong)uVar2 >> 0x20);
      pfVar4[0x2e] = fVar6;
      pfVar4[0x2f] = fVar7;
      pfVar4[0x2f] = pfVar4[0x2f] * ((fVar8 * pfVar4[1]) / fVar11);
      fVar6 = fVar8 * 0.02;
      pfVar4[0x14] = pfVar4[0x14] + fVar6;
      pfVar4[0x15] = pfVar4[0x15] + fVar6;
      pfVar4[0x16] = pfVar4[0x16] + fVar6;
    }
    else if (pfVar4[1] < fVar10) {
      fVar6 = (fVar8 * (pfVar4[1] - fVar11)) / (fVar6 * 0.3);
      auVar12 = _lqc2(*(undefined1 (*) [16])(iVar1 + 0x90));
      auVar13 = _lqc2(*(undefined1 (*) [16])(iVar1 + 0x80));
      auVar12 = _vsub(auVar12,auVar13);
      auStack_90 = _sqc2(auVar12);
      FVector::FVector(auStack_30,auStack_90);
      auVar12 = _lqc2(auStack_30);
      auVar13 = _qmtc2(fVar6);
      auVar12 = _vmulbc(auVar12,auVar13);
      auStack_70 = _sqc2(auVar12);
      FVector::FVector(auStack_10,auStack_70);
      auVar12 = _lqc2(*(undefined1 (*) [16])(iVar1 + 0x80));
      auVar13 = _lqc2(auStack_10);
      auVar12 = _vadd(auVar12,auVar13);
      auStack_a0 = _sqc2(auVar12);
      FVector::FVector(auStack_40,auStack_a0);
      pfVar4[0x2c] = auStack_40._0_4_;
      pfVar4[0x2d] = auStack_40._4_4_;
      pfVar4[0x2e] = fStack_38;
      pfVar4[0x2f] = fStack_34;
    }
    else if (pfVar4[1] < fVar7) {
      fVar6 = (fVar8 * (pfVar4[1] - fVar10)) / (fVar6 * 0.3);
      auVar12 = _lqc2(*(undefined1 (*) [16])(iVar1 + 0xa0));
      auVar13 = _lqc2(*(undefined1 (*) [16])(iVar1 + 0x90));
      auVar12 = _vsub(auVar12,auVar13);
      auStack_b0 = _sqc2(auVar12);
      FVector::FVector(auStack_50,auStack_b0);
      auVar12 = _lqc2(auStack_50);
      auVar13 = _qmtc2(fVar6);
      auVar12 = _vmulbc(auVar12,auVar13);
      auStack_80 = _sqc2(auVar12);
      FVector::FVector(auStack_20,auStack_80);
      auVar12 = _lqc2(*(undefined1 (*) [16])(iVar1 + 0x90));
      auVar13 = _lqc2(auStack_20);
      auVar12 = _vadd(auVar12,auVar13);
      auStack_c0 = _sqc2(auVar12);
      FVector::FVector(auStack_60,auStack_c0);
      pfVar4[0x2c] = auStack_60._0_4_;
      pfVar4[0x2d] = auStack_60._4_4_;
      pfVar4[0x2e] = fStack_58;
      pfVar4[0x2f] = fStack_54;
      fVar6 = fVar8 * -0.045;
      pfVar4[0x14] = pfVar4[0x14] + fVar6;
      pfVar4[0x15] = pfVar4[0x15] + fVar6;
      pfVar4[0x16] = pfVar4[0x16] + fVar6;
      pfVar4[5] = pfVar4[5] * (fVar8 * 0.02 + 1.0);
    }
    else {
      fVar9 = iVar1->f32_ac;
      uVar2 = iVar1->u64_a0;
      fVar10 = iVar1->f32_a8;
      fVar11 = iVar1->f32_ac;
      pfVar4[0x2c] = (float)uVar2;
      pfVar4[0x2d] = (float)((ulong)uVar2 >> 0x20);
      pfVar4[0x2e] = fVar10;
      pfVar4[0x2f] = fVar11;
      pfVar4[0x2f] = pfVar4[0x2f] + -fVar9 * ((fVar8 * (pfVar4[1] - fVar7)) / (fVar6 * 0.3));
      fVar6 = fVar8 * -0.06;
      pfVar4[0x14] = pfVar4[0x14] + fVar6;
      pfVar4[0x15] = pfVar4[0x15] + fVar6;
      pfVar4[0x16] = pfVar4[0x16] + fVar6;
      pfVar4[5] = pfVar4[5] * (fVar8 * 0.05 + 1.0);
    }
    if (1.0 <= pfVar4[1]) {
      pfVar4[0xc] = pfVar4[0xc] + pfVar4[4] * fVar8;
      pfVar4[0xd] = pfVar4[0xd] + pfVar4[5] * fVar8;
      pfVar4[0xe] = pfVar4[0xe] + pfVar4[6] * fVar8;
    }
    pfVar4 = pfVar4 + 0x3c;
  }
  (**(code **)(this->i32_1e4 + 0x44))();
  return;
}

// JP: 0x002a7c50  SetPacket__14FpObjectCandleFv  =  FpObjectCandle::SetPacket
void FpObjectCandle::SetPacket(int this)

{
  float in_zero_lo;
  float in_zero_hi;
  float in_zero_udw;
  float in_register_0000000c;
  float *pfVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  float fVar5;
  uint uVar6;
  float fStack_70;
  float fStack_6c;
  float fStack_68;
  float fStack_64;
  float *pfStack_4c;
  float *pfStack_48;
  float *pfStack_44;
  float *pfStack_40;
  uint *puStack_3c;
  uint *puStack_38;
  float *pfStack_34;
  float *pfStack_30;
  ulong *puStack_2c;
  ulong *puStack_28;
  float *pfStack_24;
  uint uStack_20;
  float fStack_1c;
  float fStack_18;
  float fStack_14;
  int iStack_10;
  
  fStack_14 = this->f32_1f0 * *(float *)(this->i32_8 + 0x5c);
  pfStack_24 = *(float **)(this + 0x88);
  *pfStack_24 = in_zero_lo;
  pfStack_24[1] = in_zero_hi;
  pfStack_24[2] = in_zero_udw;
  pfStack_24[3] = in_register_0000000c;
  *pfStack_24 = (float)(&DAT_10000001 + this->i32_1f8 * 0xc);
  pfStack_24[3] = (float)(this->i32_1f8 * 0xc + 1U | 0x50000000);
  this->i32_88 = this->i32_88 + 0x10;
  puStack_2c = *(ulong **)(this + 0x88);
  *puStack_2c = (long)(this->i32_1f8 << 2) | 0x302a400000008000;
  puStack_2c[1] = 0x412;
  this->i32_88 = this->i32_88 + 0x10;
  pfVar1 = *(float **)(this + 0x88);
  iStack_10 = this;
  if (this->i32_1f4 != 0) {
    iVar4 = this->i32_1fc;
    fStack_70 = in_zero_lo;
    fStack_6c = in_zero_hi;
    fStack_68 = in_zero_udw;
    fStack_64 = in_register_0000000c;
    pfStack_34 = pfVar1;
    pfStack_30 = pfVar1;
    puStack_28 = puStack_2c;
    for (iVar3 = 0; iVar3 < iStack_10->i32_1f4; iVar3 = iVar3 + 1) {
      fStack_18 = iVar4->f32_bc * fStack_14;
      if (fStack_18 < 0.0) {
        fStack_18 = 0.0;
      }
      else if (128.0 < fStack_18) {
        fStack_18 = 128.0;
      }
      for (iVar2 = 0; iVar2 < 4; iVar2 = iVar2 + 1) {
        fStack_1c = (float)PutiObject::RotTransPer
                                     (iStack_10,iVar4 + iVar2 * 0x10 + 0x70,&fStack_70);
        uStack_20 = PutiObject::ClipFlag(iStack_10);
        *pfVar1 = *(float *)(iVar4 + iVar2 * 8 + 0xc0) * fStack_1c;
        pfVar1[1] = *(float *)(iVar4 + iVar2 * 8 + 0xc4) * fStack_1c;
        pfVar1[2] = fStack_1c;
        iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
        puStack_3c = *(uint **)(iStack_10 + 0x88);
        fVar5 = iVar4->f32_b0;
        if (fVar5 < 2.1474836e+09) {
          uVar6 = (uint)fVar5;
        }
        else {
          uVar6 = (int)(fVar5 - 2.1474836e+09) | 0x80000000;
        }
        *puStack_3c = uVar6;
        fVar5 = iVar4->f32_b4;
        if (fVar5 < 2.1474836e+09) {
          uVar6 = (uint)fVar5;
        }
        else {
          uVar6 = (int)(fVar5 - 2.1474836e+09) | 0x80000000;
        }
        puStack_3c[1] = uVar6;
        fVar5 = iVar4->f32_b8;
        if (fVar5 < 2.1474836e+09) {
          uVar6 = (uint)fVar5;
        }
        else {
          uVar6 = (int)(fVar5 - 2.1474836e+09) | 0x80000000;
        }
        puStack_3c[2] = uVar6;
        if (fStack_18 < 2.1474836e+09) {
          uVar6 = (uint)fStack_18;
        }
        else {
          uVar6 = (int)(fStack_18 - 2.1474836e+09) | 0x80000000;
        }
        puStack_3c[3] = uVar6;
        iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
        pfStack_44 = *(float **)(iStack_10 + 0x88);
        if ((iVar2 < 2) || ((uStack_20 & 0x3ffff) != 0)) {
          fStack_64 = 4.59177e-41;
        }
        *pfStack_44 = fStack_70;
        pfStack_44[1] = fStack_6c;
        pfStack_44[2] = fStack_68;
        pfStack_44[3] = fStack_64;
        iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
        pfVar1 = *(float **)(iStack_10 + 0x88);
        pfStack_4c = pfVar1;
        pfStack_48 = pfVar1;
        pfStack_40 = pfStack_44;
        puStack_38 = puStack_3c;
      }
      iVar4 = iVar4 + 0xf0;
    }
  }
  for (iVar4 = iStack_10->i32_1f4; iVar4 < iStack_10->i32_1f8; iVar4 = iVar4 + 1) {
    for (iVar3 = 0; iVar3 < 4; iVar3 = iVar3 + 1) {
      *pfVar1 = in_zero_lo;
      pfVar1[1] = in_zero_hi;
      pfVar1[2] = in_zero_udw;
      pfVar1[3] = in_register_0000000c;
      iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
      pfVar1 = *(float **)(iStack_10 + 0x88);
      *pfVar1 = in_zero_lo;
      pfVar1[1] = in_zero_hi;
      pfVar1[2] = in_zero_udw;
      pfVar1[3] = in_register_0000000c;
      iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
      pfVar1 = *(float **)(iStack_10 + 0x88);
      *pfVar1 = in_zero_lo;
      pfVar1[1] = in_zero_hi;
      pfVar1[2] = in_zero_udw;
      pfVar1[3] = in_register_0000000c;
      pfVar1[3] = 4.59177e-41;
      iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
      pfVar1 = *(float **)(iStack_10 + 0x88);
    }
  }
  return;
}

// JP: 0x002a81a0  __ct__7FpSmokeFv  =  FpSmoke::FpSmoke
undefined8 FpSmoke::FpSmoke(undefined8 this)

{
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  int this;
  
  FpPrim::FpPrim(this);
  
  *(undefined1 **)(this + 0x10) = FpSmoke::__vt;
  this->u32_1c = 0x406050;
  this->u32_70 = in_zero_lo;
  this->u32_74 = in_zero_hi;
  this->u32_78 = in_zero_udw;
  this->u32_7c = in_register_0000000c;
  this->u32_80 = in_zero_lo;
  this->u32_84 = in_zero_hi;
  this->u32_88 = in_zero_udw;
  this->u32_8c = in_register_0000000c;
  this->u32_90 = in_zero_lo;
  this->u32_94 = in_zero_hi;
  this->u32_98 = in_zero_udw;
  this->u32_9c = in_register_0000000c;
  this->u32_a0 = in_zero_lo;
  this->u32_a4 = in_zero_hi;
  this->u32_a8 = in_zero_udw;
  this->u32_ac = in_register_0000000c;
  this->u32_b0 = in_zero_lo;
  this->u32_b4 = in_zero_hi;
  this->u32_b8 = in_zero_udw;
  this->u32_bc = in_register_0000000c;
  this->u32_e0 = in_zero_lo;
  this->u32_e4 = in_zero_hi;
  this->u32_e8 = in_zero_udw;
  this->u32_ec = in_register_0000000c;
  this->u32_70 = 0;
  this->u32_74 = 0;
  this->u32_78 = 0;
  this->u32_7c = 0x3f800000;
  this->u32_80 = 0;
  this->u32_84 = 0;
  this->u32_88 = 0;
  this->u32_8c = 0x3f800000;
  this->u32_90 = 0x43000000;
  this->u32_94 = 0x43000000;
  this->u32_98 = 0x43000000;
  this->u32_9c = 0x43000000;
  this->u32_a0 = 0x43000000;
  this->u32_a4 = 0x43000000;
  this->u32_a8 = 0x43000000;
  this->u32_ac = 0x43000000;
  this->u32_c0 = 0;
  this->u32_cc = 0;
  this->u32_d0 = 0;
  this->u32_d4 = 0;
  this->u32_d8 = 1;
  this->u32_dc = 0;
  this->u32_c8 = 0xffffffff;
  this->u32_c4 = 0xffffffff;
  this->u32_e0 = 0;
  this->u32_e4 = 0;
  this->u32_e8 = 0;
  this->u32_ec = 0x3f800000;
  this->u32_f0 = 0;
  return this;
}

// JP: 0x002a83d0  __dt__7FpSmokeFv  =  FpSmoke::~FpSmoke
int FpSmoke::~FpSmoke(int this,short param_2)

{
  if (this != 0) {
    *(undefined1 **)(this + 0x10) = FpSmoke::__vt;
    this->u32_1c = 0x406050;
    FpPrim::~FpPrim(this,0);
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}

// JP: 0x002a8460  SetColor1__7FpSmokeFUcUcUcUc  =  FpSmoke::SetColor1
undefined4
FpSmoke::SetColor1(int this,ulong param_2,ulong param_3,ulong param_4,ulong param_5)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  
  if ((long)param_2 < 0) {
    fVar1 = (float)(param_2 & 0xffffffff);
  }
  else {
    fVar1 = (float)(int)param_2;
  }
  if ((long)param_3 < 0) {
    fVar2 = (float)(param_3 & 0xffffffff);
  }
  else {
    fVar2 = (float)(int)param_3;
  }
  if ((long)param_4 < 0) {
    fVar3 = (float)(param_4 & 0xffffffff);
  }
  else {
    fVar3 = (float)(int)param_4;
  }
  if ((long)param_5 < 0) {
    fVar4 = (float)(param_5 & 0xffffffff);
  }
  else {
    fVar4 = (float)(int)param_5;
  }
  this->f32_a0 = fVar1 * 0.5019608;
  this->f32_a4 = fVar2 * 0.5019608;
  this->f32_a8 = fVar3 * 0.5019608;
  this->f32_ac = fVar4 * 0.5019608;
  this->i32_90 = (int)this->u64_a0;
  this->i32_94 = (int)((ulong)this->u64_a0 >> 0x20);
  this->u32_98 = this->u32_a8;
  this->u32_9c = this->u32_ac;
  this->u32_ac = 0;
  this->u32_cc = this->u32_9c;
  FpSmoke::InitColor((float)this->i32_d8);
  return 1;
}

// JP: 0x002a85e0  SetColor2__7FpSmokeFUcUcUcUc  =  FpSmoke::SetColor2
undefined4
FpSmoke::SetColor2(int this,ulong param_2,ulong param_3,ulong param_4,ulong param_5)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  
  if ((long)param_2 < 0) {
    fVar1 = (float)(param_2 & 0xffffffff);
  }
  else {
    fVar1 = (float)(int)param_2;
  }
  if ((long)param_3 < 0) {
    fVar2 = (float)(param_3 & 0xffffffff);
  }
  else {
    fVar2 = (float)(int)param_3;
  }
  if ((long)param_4 < 0) {
    fVar3 = (float)(param_4 & 0xffffffff);
  }
  else {
    fVar3 = (float)(int)param_4;
  }
  if ((long)param_5 < 0) {
    fVar4 = (float)(param_5 & 0xffffffff);
  }
  else {
    fVar4 = (float)(int)param_5;
  }
  this->f32_a0 = fVar1 * 0.5019608;
  this->f32_a4 = fVar2 * 0.5019608;
  this->f32_a8 = fVar3 * 0.5019608;
  this->f32_ac = fVar4 * 0.5019608;
  this->u32_ac = 0;
  FpSmoke::InitColor((float)this->i32_d8);
  return 1;
}

// JP: 0x002a8740  SetPos1__7FpSmokeF7FVectorb  =  FpSmoke::SetPos1
undefined4 FpSmoke::SetPos1(int this,undefined4 *param_2,long param_3)

{
  int iVar1;
  undefined8 uVar2;
  int iVar3;
  int iVar4;
  undefined1 auVar5 [16];
  undefined1 auVar6 [16];
  undefined1 auStack_40 [16];
  undefined1 auStack_30 [16];
  undefined1 auStack_20 [12];
  undefined4 uStack_14;
  undefined1 auStack_10 [16];
  
  FVector::FVector(auStack_10,this + 0x70);
  this->u32_70 = *param_2;
  this->u32_74 = param_2[1];
  this->u32_78 = param_2[2];
  iVar1 = this->i32_28;
  auVar5 = _lqc2(*(undefined1 (*) [16])(this + 0x70));
  auVar6 = _lqc2(auStack_10);
  auVar5 = _vsub(auVar5,auVar6);
  auStack_40 = _sqc2(auVar5);
  FVector::FVector(auStack_20,auStack_40);
  uStack_14 = 0;
  if (param_3 == 0) {
    iVar1->u8_204 = 1;
    iVar4 = iVar1->i32_1fc;
    for (iVar3 = 0; iVar3 < iVar1->i32_1f4; iVar3 = iVar3 + 1) {
      iVar4->u8_e0 = iVar4->u8_e0 & 0xfe | 1;
      iVar4 = iVar4 + 0xf0;
    }
    iVar3 = iVar1->i32_1fc + iVar1->i32_1f4 * 0xf0;
    for (iVar4 = iVar1->i32_1f4; iVar4 < iVar1->i32_1f8; iVar4 = iVar4 + 1) {
      iVar3->u8_e0 = iVar3->u8_e0 & 0xfe;
      auVar5._12_4_ = 0;
      auVar5._0_12_ = auStack_20;
      auVar6 = _lqc2(auVar5);
      auVar5 = _lqc2(*(undefined1 (*) [16])(iVar3 + 0x30));
      auVar5 = _vadd(auVar5,auVar6);
      auVar5 = _sqc2(auVar5);
      *(undefined1 (*) [16])(iVar3 + 0x30) = auVar5;
      iVar3 = iVar3 + 0xf0;
    }
  }
  else {
    iVar4 = iVar1->i32_1fc;
    for (iVar3 = 0; iVar3 < iVar1->i32_1f8; iVar3 = iVar3 + 1) {
      auVar6._12_4_ = 0;
      auVar6._0_12_ = auStack_20;
      auVar6 = _lqc2(auVar6);
      auVar5 = _lqc2(*(undefined1 (*) [16])(iVar4 + 0x30));
      auVar5 = _vadd(auVar5,auVar6);
      auVar5 = _sqc2(auVar5);
      *(undefined1 (*) [16])(iVar4 + 0x30) = auVar5;
      iVar4 = iVar4 + 0xf0;
    }
  }
  uVar2 = FVector::FVector(auStack_30,auStack_20);
  FpObject::UpdateBBoxMove(iVar1,uVar2);
  return 1;
}

// JP: 0x002a8920  CreateEffect__7FpSmokeFP12FpSmokeParam  =  FpSmoke::CreateEffect
/* WARNING: Removing unreachable block (ram,0x002a91b8) */
/* WARNING: Removing unreachable block (ram,0x002a9108) */
/* WARNING: Removing unreachable block (ram,0x002a9058) */
/* WARNING: Removing unreachable block (ram,0x002a8fa8) */
/* WARNING: Removing unreachable block (ram,0x002a9000) */
/* WARNING: Removing unreachable block (ram,0x002a90b0) */
/* WARNING: Removing unreachable block (ram,0x002a9160) */
/* WARNING: Removing unreachable block (ram,0x002a9210) */

void FpSmoke::CreateEffect(int this,float *param_2)

{
  float fVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  int iVar8;
  undefined1 auStack_140 [16];
  undefined1 auStack_130 [16];
  undefined1 auStack_120 [16];
  undefined1 auStack_110 [16];
  undefined1 auStack_100 [16];
  undefined1 auStack_f0 [16];
  undefined1 auStack_e0 [16];
  float fStack_d0;
  float fStack_cc;
  float fStack_c8;
  float fStack_c4;
  float fStack_c0;
  float fStack_bc;
  float fStack_b8;
  float fStack_b4;
  float fStack_b0;
  float fStack_ac;
  float fStack_a8;
  undefined4 uStack_a4;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  undefined4 uStack_90;
  undefined4 uStack_8c;
  undefined4 uStack_88;
  float fStack_84;
  float fStack_80;
  float fStack_7c;
  float fStack_78;
  float fStack_70;
  float fStack_6c;
  float fStack_68;
  float fStack_60;
  float fStack_5c;
  float fStack_58;
  float fStack_48;
  float fStack_44;
  float fStack_40;
  float fStack_3c;
  float fStack_38;
  float fStack_34;
  float fStack_30;
  float fStack_2c;
  float fStack_28;
  float fStack_24;
  int iStack_20;
  float *pfStack_10;
  
  if (param_2->i8_12 < '\0') {
    param_2->u8_12 = 0;
  }
  else if ('d' < param_2->i8_12) {
    param_2->u8_12 = 100;
  }
  if (*(char *)((int)param_2 + 0x49) < '\0') {
    *(undefined1 *)((int)param_2 + 0x49) = 0;
  }
  else if ('d' < *(char *)((int)param_2 + 0x49)) {
    *(undefined1 *)((int)param_2 + 0x49) = 100;
  }
  if (*(char *)((int)param_2 + 0x4a) < '\0') {
    *(undefined1 *)((int)param_2 + 0x4a) = 0;
  }
  else if ('d' < *(char *)((int)param_2 + 0x4a)) {
    *(undefined1 *)((int)param_2 + 0x4a) = 100;
  }
  iStack_20 = this;
  pfStack_10 = param_2;
  uVar2 = FVector::FVector(auStack_e0,param_2 + 8);
  FpSmoke::SetWind(iStack_20,uVar2);
  fStack_28 = *pfStack_10;
  fStack_30 = pfStack_10[1];
  fStack_38 = pfStack_10[2];
  fStack_34 = fStack_38;
  fStack_2c = fStack_30;
  fStack_24 = fStack_28;
  FVector::FVector(&fStack_60,pfStack_10);
  FVector::FVector(&fStack_70,pfStack_10 + 4);
  FVector::FVector(&fStack_80,pfStack_10 + 8);
  fStack_3c = 3.0;
  if ((0.0 <= pfStack_10[0xf]) && (pfStack_10[0xe] != 0.0)) {
    fStack_3c = pfStack_10[0xf] / pfStack_10[0xe];
  }
  uStack_90 = 0x3f800000;
  uStack_8c = 0x3f800000;
  uStack_88 = 0x3f800000;
  fStack_84 = fStack_3c;
  fVar1 = pfStack_10[0x11];
  iStack_20->i32_f0 = (int)((float)((int)fVar1 * (int)pfStack_10->i8_12) * 0.01)
  ;
  for (iVar8 = 0; iVar8 < (int)fVar1; iVar8 = iVar8 + 1) {
    if (0 < iVar8) {
      fStack_60 = fStack_60 + fStack_70;
      fStack_5c = fStack_5c + fStack_6c;
      fStack_58 = fStack_58 + fStack_68;
    }
    if (iStack_20->i32_f0 <= iVar8) {
      fStack_70 = fStack_70 + fStack_80;
      fStack_6c = fStack_6c + fStack_7c;
      fStack_68 = fStack_68 + fStack_78;
    }
    fStack_40 = (fStack_3c - 1.0) / (float)(int)fVar1;
    fStack_44 = fStack_40 * (float)iVar8 + 1.0;
    if (fStack_44 < 0.0) {
      fStack_44 = 0.0;
    }
    fStack_48 = pfStack_10[0xe] * 0.5 * fStack_44;
    if (fStack_24 < fStack_60 + fStack_48) {
      fStack_24 = fStack_60 + fStack_48;
    }
    if (fStack_60 - fStack_48 < fStack_28) {
      fStack_28 = fStack_60 - fStack_48;
    }
    if (fStack_2c < fStack_5c + fStack_48) {
      fStack_2c = fStack_5c + fStack_48;
    }
    if (fStack_5c - fStack_48 < fStack_30) {
      fStack_30 = fStack_5c - fStack_48;
    }
    if (fStack_34 < fStack_58 + fStack_48) {
      fStack_34 = fStack_58 + fStack_48;
    }
    if (fStack_58 - fStack_48 < fStack_38) {
      fStack_38 = fStack_58 - fStack_48;
    }
  }
  fStack_a0 = (fStack_24 - fStack_28) / 2.0;
  fStack_9c = (fStack_2c - fStack_30) / 2.0;
  fStack_98 = (fStack_34 - fStack_38) / 2.0;
  uStack_94 = 0;
  fStack_b0 = (fStack_24 + fStack_28) / 2.0;
  fStack_ac = (fStack_2c + fStack_30) / 2.0;
  fStack_a8 = (fStack_34 + fStack_38) / 2.0;
  uStack_a4 = 0;
  iStack_20->i32_c8 =
       (int)((float)((int)fVar1 * (int)*(char *)((int)pfStack_10 + 0x4a)) * 0.01);
  iStack_20->i32_c4 =
       (int)((float)((int)fVar1 * (int)*(char *)((int)pfStack_10 + 0x49)) * 0.01);
  fStack_c0 = (float)pfStack_10->u8_c * 0.5019608;
  fStack_bc = (float)*(byte *)((int)pfStack_10 + 0x31) * 0.5019608;
  fStack_b8 = (float)*(byte *)((int)pfStack_10 + 0x32) * 0.5019608;
  fStack_b4 = (float)*(byte *)((int)pfStack_10 + 0x33) * 0.5019608;
  fStack_d0 = (float)pfStack_10->u8_d * 0.5019608;
  fStack_cc = (float)*(byte *)((int)pfStack_10 + 0x35) * 0.5019608;
  fStack_c8 = (float)*(byte *)((int)pfStack_10 + 0x36) * 0.5019608;
  fStack_c4 = (float)*(byte *)((int)pfStack_10 + 0x37) * 0.5019608;
  uVar2 = FVector::FVector(auStack_f0,pfStack_10);
  uVar3 = FVector::FVector(auStack_100,pfStack_10 + 4);
  uVar4 = FVector::FVector(auStack_110,&fStack_c0);
  uVar5 = FVector::FVector(auStack_120,&fStack_d0);
  uVar6 = FVector::FVector(auStack_130,&fStack_a0);
  uVar7 = FVector::FVector(auStack_140,&fStack_b0);
  FpSmoke::Create
            (pfStack_10[0xe],pfStack_10[0xf],iStack_20,uVar2,uVar3,uVar4,uVar5,uVar6,uVar7,
             pfStack_10[0x11]);
  iVar8 = iStack_20->i32_28;
  if (iVar8->i32_200 != 0) {
    *(byte *)(iVar8->i32_200 + 1) = *(byte *)(iVar8->i32_200 + 1) & 0xfe | 1;
  }
  if (iVar8->i32_200 != 0) {
    *(byte *)(iVar8->i32_200 + 1) = *(byte *)(iVar8->i32_200 + 1) & 0xfd | 2;
  }
  return;
}

// JP: 0x002a93a0  Create__7FpSmokeF7FVector7FVector7FVector7FVector7FVector7FVectoriffi  =  FpSmoke::Create
void FpSmoke::Create
               (float this,float param_2,undefined8 param_3,undefined8 *param_4,
               undefined8 *param_5,undefined8 *param_6,undefined8 *param_7,undefined8 param_8,
               undefined8 param_9,undefined4 param_10,int param_11)

{
  long lVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  int iVar7;
  int iVar8;
  undefined1 auStack_30 [16];
  undefined1 auStack_20 [16];
  undefined1 auStack_10 [16];
  
  iVar7 = (int)param_3;
  uVar2 = *param_4;
  uVar5 = param_4->u32_1;
  uVar6 = *(undefined4 *)((int)param_4 + 0xc);
  iVar7->i32_70 = (int)uVar2;
  iVar7->i32_74 = (int)((ulong)uVar2 >> 0x20);
  iVar7->u32_78 = uVar5;
  iVar7->u32_7c = uVar6;
  uVar2 = *param_5;
  uVar5 = param_5->u32_1;
  uVar6 = *(undefined4 *)((int)param_5 + 0xc);
  iVar7->i32_80 = (int)uVar2;
  iVar7->i32_84 = (int)((ulong)uVar2 >> 0x20);
  iVar7->u32_88 = uVar5;
  iVar7->u32_8c = uVar6;
  iVar7->f32_c0 = this;
  iVar7->f32_74 = iVar7->f32_74 - iVar7->f32_c0 / 5.0;
  uVar2 = *param_6;
  uVar5 = param_6->u32_1;
  uVar6 = *(undefined4 *)((int)param_6 + 0xc);
  iVar7->i32_90 = (int)uVar2;
  iVar7->i32_94 = (int)((ulong)uVar2 >> 0x20);
  iVar7->u32_98 = uVar5;
  iVar7->u32_9c = uVar6;
  uVar2 = *param_7;
  uVar5 = param_7->u32_1;
  uVar6 = *(undefined4 *)((int)param_7 + 0xc);
  iVar7->i32_a0 = (int)uVar2;
  iVar7->i32_a4 = (int)((ulong)uVar2 >> 0x20);
  iVar7->u32_a8 = uVar5;
  iVar7->u32_ac = uVar6;
  iVar7->u32_ac = 0;
  iVar7->u32_cc = iVar7->u32_9c;
  iVar7->u32_d0 = 0;
  iVar7->u32_d8 = param_10;
  if (iVar7->i32_c4 == -1) {
    iVar7->u32_c4 = 0;
  }
  if (iVar7->i32_c8 == -1) {
    iVar7->i32_c8 = (int)((float)iVar7->i32_d8 * 0.1);
  }
  if (param_2 < 0.0) {
    iVar7->u32_dc = 0x40400000;
  }
  else {
    iVar7->f32_dc = param_2 / this;
  }
  iVar8 = BgEffectMan::eff->i32_1c + 0x8c;
  SetWhiteTex(iVar8);
  PutiPrim::SetTexture(param_3,iVar8,0);
  if (iVar7->i8_58 == '\0') {
    iVar7->u8_24 = iVar7->u8_24 & 0xfe | 1;
  }
  lVar1 = __nw(0x210);
  uVar2 = 0;
  if (lVar1 != 0) {
    uVar2 = FpObjectSmoke::FpObjectSmoke(lVar1,param_11 * 0xc + 0x14,0);
  }
  PutiPrim::AddObject(param_3,uVar2);
  (**(code **)(*(int *)((int)uVar2 + 0x1e4) + 0x40))(uVar2,param_11,iVar7->u8_58);
  uVar3 = FVector::FVector(auStack_10,param_9);
  uVar4 = FVector::FVector(auStack_20,param_8);
  FpObject::InitBBox(0,uVar2,uVar3,uVar4,auStack_30,0,1);
  PutiManager::AddPrim(BgEffectMan::eff,iVar7->u32_54,param_3);
  return;
}

// JP: 0x002a9630  Create__7FpSmokeFPv  =  FpSmoke::Create
void FpSmoke::Create(undefined8 this,undefined8 param_2)

{
  undefined2 *puVar1;
  undefined4 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  uint *puVar8;
  float *pfVar10;
  bool bVar11;
  bool bVar12;
  float fVar13;
  uint uVar14;
  uint uVar15;
  undefined1 auStack_f0 [16];
  undefined1 auStack_e0 [16];
  undefined1 auStack_d0 [16];
  undefined1 auStack_c0 [16];
  undefined1 auStack_b0 [16];
  undefined1 auStack_a0 [16];
  undefined1 auStack_90 [16];
  undefined1 auStack_80 [16];
  undefined4 uStack_70;
  undefined4 uStack_6c;
  float fStack_68;
  float fStack_64;
  undefined1 auStack_60 [16];
  undefined1 auStack_50 [16];
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined1 auStack_20 [12];
  undefined4 uStack_14;
  uint uStack_8;
  undefined2 uStack_4;
  undefined2 uStack_2;
  int this;
  
  FVector::FVector(auStack_20,param_2);
  this = (int)param_2;
  puVar8 = (uint *)(this + 0x10);
  uStack_30 = 0;
  uStack_2c = 0;
  uStack_28 = 0;
  uStack_24 = 0;
  FVector::FVector(&uStack_40,auStack_20);
  bVar12 = false;
  bVar11 = true;
  puVar1 = (undefined2 *)FpPrim::InitFpFlag(uStack_14,this);
  uStack_4 = *puVar1;
  uStack_2 = puVar1[1];
  memset(&uStack_8,0,4);
  if ((long)((ulong)uStack_2._1_1_ << 0x3a) < 0) {
    uStack_8 = *puVar8;
    puVar8 = (uint *)(this + 0x20);
    bVar12 = (uStack_8 & 1) != 0;
    bVar11 = (long)((ulong)(byte)uStack_8 << 0x3e) < 0;
    if ((long)((ulong)(byte)uStack_8 << 0x3d) < 0) {
      uStack_28 = this->u32_28;
      uStack_24 = this->u32_2c;
      uStack_30 = (undefined4)*(undefined8 *)puVar8;
      uStack_2c = (undefined4)((ulong)*(undefined8 *)puVar8 >> 0x20);
      uStack_38 = this->u32_38;
      uStack_34 = this->u32_3c;
      uStack_40 = (undefined4)this->u64_30;
      uStack_3c = (undefined4)((ulong)this->u64_30 >> 0x20);
      puVar8 = (uint *)(this + 0x40);
    }
  }
  FVector::FVector(auStack_50,puVar8);
  FVector::FVector(auStack_60,puVar8 + 4);
  fVar13 = (float)puVar8[8];
  uVar14 = puVar8[9];
  uVar15 = puVar8[10];
  pfVar10 = (float *)(puVar8 + 0xc);
  
  if ((long)((ulong)uStack_2._1_1_ << 0x3c) < 0) {
    this->i32_c4 = (int)*pfVar10;
    this->i32_c8 = (int)(float)puVar8[0xd];
    pfVar10 = (float *)(puVar8 + 0x10);
  }
  FVector::FVector(&uStack_70,auStack_60);
  if ((long)((ulong)uStack_2._1_1_ << 0x3b) < 0) {
    fStack_68 = pfVar10[2];
    fStack_64 = pfVar10[3];
    uStack_70 = (undefined4)*(undefined8 *)pfVar10;
    uStack_6c = (undefined4)((ulong)*(undefined8 *)pfVar10 >> 0x20);
    pfVar10 = pfVar10 + 4;
  }
  if (((ulong)uStack_2._1_1_ & 7) >> 1 == 1) {
    FVector::FVector(auStack_80,pfVar10);
    uVar3 = FVector::FVector(auStack_90,auStack_80);
    FpSmoke::SetWind(this,uVar3);
  }
  uVar3 = FVector::FVector(auStack_a0,auStack_20);
  uVar4 = FVector::FVector(auStack_b0,auStack_50);
  uVar5 = FVector::FVector(auStack_c0,auStack_60);
  uVar6 = FVector::FVector(auStack_d0,&uStack_70);
  uVar2 = FVector::FVector(auStack_e0,&uStack_30);
  uVar7 = FVector::FVector(auStack_f0,&uStack_40);
  FpSmoke::Create
            (uVar14,uVar15,this,uVar3,uVar4,uVar5,uVar6,uVar2,uVar7,(int)fVar13);
  this = this->i32_28;
  if (this->i32_200 != 0) {
    *(byte *)(this->i32_200 + 1) = *(byte *)(this->i32_200 + 1) & 0xfe | bVar12;
  }
  if (this->i32_200 != 0) {
    *(byte *)(this->i32_200 + 1) =
         *(byte *)(this->i32_200 + 1) & 0xfd | bVar11 << 1;
  }
  return;
}

// JP: 0x002a99f0  SetWind__7FpSmokeF7FVector  =  FpSmoke::SetWind
void FpSmoke::SetWind(int this,undefined4 *param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  uVar1 = param_2[1];
  uVar2 = param_2[2];
  uVar3 = param_2[3];
  this->u32_e0 = *param_2;
  this->u32_e4 = uVar1;
  this->u32_e8 = uVar2;
  this->u32_ec = uVar3;
  this->i32_f0 = (int)(float)param_2[3];
  this->u32_ec = 0;
  return;
}

// JP: 0x002a9a30  InitColor__7FpSmokeFf  =  FpSmoke::InitColor
void FpSmoke::InitColor(float this,int param_2)

{
  float fVar1;
  
  fVar1 = this - (float)param_2->i32_c4;
  param_2->f32_b0 = (param_2->f32_a0 - param_2->f32_90) / fVar1;
  param_2->f32_b4 = (param_2->f32_a4 - param_2->f32_94) / fVar1;
  param_2->f32_b8 = (param_2->f32_a8 - param_2->f32_98) / fVar1;
  param_2->f32_bc =
       (param_2->f32_ac - param_2->f32_9c) /
       (this - (float)param_2->i32_c8);
  return;
}

// JP: 0x002a9b20  GetColor__7FpSmokeFf  =  FpSmoke::GetColor
void FpSmoke::GetColor(float this,undefined4 param_2,int param_3)

{
  float fStack_50;
  float fStack_4c;
  float fStack_48;
  float fStack_44;
  float fStack_3c;
  float fStack_38;
  float fStack_34;
  undefined4 uStack_30;
  int iStack_20;
  float fStack_10;
  
  if (this < (float)param_3->i32_c8) {
    fStack_34 = this / (float)param_3->i32_c8;
    fStack_44 = param_3->f32_9c * fStack_34;
  }
  else {
    fStack_38 = this - (float)param_3->i32_c8;
    fStack_44 = param_3->f32_9c + param_3->f32_bc * fStack_38;
    if (fStack_44 < 0.0) {
      fStack_44 = 0.0;
    }
    else if (128.0 < fStack_44) {
      fStack_44 = 128.0;
    }
  }
  if (this < (float)param_3->i32_c4) {
    fStack_50 = param_3->f32_90;
    fStack_4c = param_3->f32_94;
    fStack_48 = param_3->f32_98;
  }
  else {
    fStack_3c = this - (float)param_3->i32_c4;
    fStack_50 = param_3->f32_90 + param_3->f32_b0 * fStack_3c;
    fStack_4c = param_3->f32_94 + param_3->f32_b4 * fStack_3c;
    fStack_48 = param_3->f32_98 + param_3->f32_b8 * fStack_3c;
    if (fStack_50 < 0.0) {
      fStack_50 = 0.0;
    }
    else if (128.0 < fStack_50) {
      fStack_50 = 128.0;
    }
    if (fStack_4c < 0.0) {
      fStack_4c = 0.0;
    }
    else if (128.0 < fStack_4c) {
      fStack_4c = 128.0;
    }
    if (fStack_48 < 0.0) {
      fStack_48 = 0.0;
    }
    else if (128.0 < fStack_48) {
      fStack_48 = 128.0;
    }
  }
  uStack_30 = param_2;
  iStack_20 = param_3;
  fStack_10 = this;
  FVector::FVector(param_2,&fStack_50);
  return;
}

// JP: 0x002a9e50  GetScale__7FpSmokeFfff  =  FpSmoke::GetScale
float FpSmoke::GetScale(float this,float param_2,float param_3)

{
  undefined4 uStack_48;
  
  uStack_48 = ((param_3 - 1.0) / this) * param_2 + 1.0;
  if (uStack_48 < 0.0) {
    uStack_48 = 0.0;
  }
  return uStack_48;
}

// JP: 0x002a9ee0  CreateStart__7FpSmokeFf  =  FpSmoke::CreateStart
void FpSmoke::CreateStart(float this,int param_2)

{
  undefined4 *puVar1;
  float *pfVar2;
  int iVar3;
  int iVar4;
  
  for (puVar1 = *(undefined4 **)(param_2 + 0x28); puVar1 != (undefined4 *)0x0;
      puVar1 = (undefined4 *)*puVar1) {
    pfVar2 = (float *)puVar1[0x7f];
    for (iVar4 = 0; iVar4 < (int)puVar1[0x7e]; iVar4 = iVar4 + 1) {
      (**(code **)(puVar1[0x79] + 0x4c))(puVar1,iVar4,1);
      pfVar2[1] = pfVar2[1] + (float)(int)(*pfVar2 * this);
      if (0.0 < pfVar2[1]) {
        for (iVar3 = 0; (float)iVar3 < pfVar2[1]; iVar3 = iVar3 + 1) {
          pfVar2[0xc] = pfVar2[0xc] + pfVar2[4];
          pfVar2[0xd] = pfVar2[0xd] + pfVar2[5];
          pfVar2[0xe] = pfVar2[0xe] + pfVar2[6];
          if (param_2->i32_f0 <= iVar3) {
            pfVar2[4] = pfVar2[4] + pfVar2[8];
            pfVar2[5] = pfVar2[5] + pfVar2[9];
            pfVar2[6] = pfVar2[6] + pfVar2[10];
          }
        }
      }
      pfVar2 = pfVar2 + 0x3c;
    }
  }
  return;
}

// JP: 0x002aa090  __ct__13FpObjectSmokeFiPv  =  FpObjectSmoke::FpObjectSmoke
int FpObjectSmoke::FpObjectSmoke(int this,undefined4 param_2,undefined4 param_3)

{
  FpObject::FpObject(this,param_2,param_3);
  *(undefined1 **)(this + 0x1e4) = FpObjectSmoke::__vt;
  return this;
}

// JP: 0x002aa0e0  __dt__13FpObjectSmokeFv  =  FpObjectSmoke::~FpObjectSmoke
int FpObjectSmoke::~FpObjectSmoke(int this,short param_2)

{
  if (this != 0) {
    *(undefined1 **)(this + 0x1e4) = FpObjectSmoke::__vt;
    FpObject::~FpObject(this,0);
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}

// JP: 0x002aa160  CreateData__13FpObjectSmokeFib  =  FpObjectSmoke::CreateData
void FpObjectSmoke::CreateData(int this,uint param_2,long param_3)

{
  int iVar1;
  undefined8 uVar2;
  int iVar3;
  uint uVar4;
  float fVar5;
  float fVar6;
  float *pfVar7;
  float fVar8;
  
  iVar1 = this->i32_8;
  pfVar7 = (float *)(this->i32_1fc + param_2 * 0xf0);
  *pfVar7 = (float)iVar1->i32_d8;
  if (param_3 == 0) {
    pfVar7[1] = 0.0;
  }
  else {
    pfVar7[1] = (float)(int)(((float)(int)param_2 * *pfVar7) / (float)this->i32_1f8) -
                *pfVar7;
    pfVar7[2] = 0.0;
    pfVar7[0x1c] = 0.0;
    pfVar7[0x1d] = 0.0;
    pfVar7[0x1e] = 0.0;
    pfVar7[0x1f] = 1.0;
    pfVar7[0x20] = 0.0;
    pfVar7[0x21] = 0.0;
    pfVar7[0x22] = 0.0;
    pfVar7[0x23] = 1.0;
    pfVar7[0x24] = 0.0;
    pfVar7[0x25] = 0.0;
    pfVar7[0x26] = 0.0;
    pfVar7[0x27] = 1.0;
    pfVar7[0x28] = 0.0;
    pfVar7[0x29] = 0.0;
    pfVar7[0x2a] = 0.0;
    pfVar7[0x2b] = 1.0;
    pfVar7[0x30] = 0.0;
    pfVar7[0x31] = 0.0;
    pfVar7[0x32] = 0.0;
    pfVar7[0x33] = 1.0;
    pfVar7[0x34] = 1.0;
    pfVar7[0x35] = 0.0;
    pfVar7[0x36] = 1.0;
    pfVar7[0x37] = 1.0;
    uVar2 = iVar1->u64_e0;
    fVar5 = iVar1->f32_e8;
    fVar6 = iVar1->f32_ec;
    pfVar7[8] = (float)uVar2;
    pfVar7[9] = (float)((ulong)uVar2 >> 0x20);
    pfVar7[10] = fVar5;
    pfVar7[0xb] = fVar6;
  }
  fVar8 = iVar1->f32_c0;
  pfVar7[0x10] = fVar8;
  pfVar7[0x11] = fVar8;
  pfVar7[0x12] = 0.0;
  pfVar7[0x13] = 1.0;
  uVar2 = iVar1->u64_70;
  fVar5 = iVar1->f32_78;
  fVar6 = iVar1->f32_7c;
  pfVar7[0xc] = (float)uVar2;
  pfVar7[0xd] = (float)((ulong)uVar2 >> 0x20);
  pfVar7[0xe] = fVar5;
  pfVar7[0xf] = fVar6;
  iVar3 = rand();
  pfVar7[0xc] = pfVar7[0xc] + fVar8 * 0.3 * ((float)iVar3 / 2.1474836e+09 - 0.5);
  iVar3 = rand();
  pfVar7[0xe] = pfVar7[0xe] + fVar8 * 0.3 * ((float)iVar3 / 2.1474836e+09 - 0.5);
  uVar2 = iVar1->u64_80;
  fVar5 = iVar1->f32_88;
  fVar6 = iVar1->f32_8c;
  pfVar7[4] = (float)uVar2;
  pfVar7[5] = (float)((ulong)uVar2 >> 0x20);
  pfVar7[6] = fVar5;
  pfVar7[7] = fVar6;
  iVar3 = rand();
  FVector::__amu(((float)iVar3 / 2.1474836e+09) * 0.4 + 0.8,pfVar7 + 4);
  iVar3 = rand();
  fVar5 = (float)iVar3 / 2.1474836e+09 + 0.5;
  pfVar7[0x14] = fVar5;
  pfVar7[0x15] = fVar5;
  pfVar7[0x16] = fVar5;
  pfVar7[0x17] = 1.0;
  iVar3 = rand();
  pfVar7[0x17] = iVar1->f32_dc * ((float)iVar3 / 2.1474836e+09 + 0.5);
  uVar4 = param_2 & 3;
  if (((int)param_2 < 0) && (uVar4 != 0)) {
    uVar4 = uVar4 - 4;
  }
  iVar3 = rand();
  pfVar7[0x18] = 0.0;
  pfVar7[0x19] = 0.0;
  pfVar7[0x1a] = (float)(int)(uVar4 + 1) * ((float)iVar3 / 2.1474836e+09) * 1.5707964;
  pfVar7[0x1b] = 1.0;
  pfVar7[0x2c] = iVar1->f32_90;
  pfVar7[0x2d] = iVar1->f32_94;
  pfVar7[0x2e] = iVar1->f32_98;
  pfVar7[0x2f] = 0.0;
  pfVar7->u8_38 = pfVar7->u8_38 & 0xfe;
  return;
}

// JP: 0x002aa6a0  Init__13FpObjectSmokeFib  =  FpObjectSmoke::Init
void FpObjectSmoke::Init(int this,undefined4 param_2,char param_3)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  float *pfVar5;
  int iVar6;
  int iVar7;
  
  iVar1 = this->i32_8;
  iVar2 = iVar1->i32_f0;
  this->u32_1f4 = param_2;
  this->u32_1f8 = param_2;
  iVar7 = this->i32_1f8;
  uVar4 = __nwa(iVar7 * 0xf0 + 0x10);
  uVar3 = __construct_new_array(uVar4,0x299b50,0,0xf0,iVar7);
  this->u32_1fc = uVar3;
  memset(*(void **)(this + 0x1fc),0,(long)(this->i32_1f8 * 0xf0));
  pfVar5 = *(float **)(this + 0x1fc);
  for (iVar7 = 0; iVar7 < this->i32_1f8; iVar7 = iVar7 + 1) {
    (**(code **)(this->i32_1e4 + 0x4c))(this,iVar7,1);
    pfVar5[1] = pfVar5[1] + *pfVar5;
    for (iVar6 = 0; iVar6 < (int)pfVar5[1]; iVar6 = iVar6 + 1) {
      pfVar5[0xc] = pfVar5[0xc] + pfVar5[4];
      pfVar5[0xd] = pfVar5[0xd] + pfVar5[5];
      pfVar5[0xe] = pfVar5[0xe] + pfVar5[6];
      if (iVar2 <= iVar6) {
        pfVar5[4] = pfVar5[4] + pfVar5[8];
        pfVar5[5] = pfVar5[5] + pfVar5[9];
        pfVar5[6] = pfVar5[6] + pfVar5[10];
      }
    }
    pfVar5 = pfVar5 + 0x3c;
  }
  FpSmoke::InitColor(**(undefined4 **)(this + 0x1fc),iVar1);
  this->u32_1e0 = 0xffffffff;
  this->u8_14 = this->u8_14 & 0xfe | 1;
  this->u16_14 = this->u16_14 & 0xe01f;
  if (param_3 == '\0') {
    PutiObject::SetRegTest(this,0x33001);
  }
  else {
    PutiObject::SetRegTest(this,0x73001);
  }
  PutiObject::SetRegAlpha(this,0x44);
  return;
}

// JP: 0x002aa950  CalculateFunc__13FpObjectSmokeFv  =  FpObjectSmoke::CalculateFunc
void FpObjectSmoke::CalculateFunc(undefined8 this)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  float *pfVar5;
  int this;
  float fVar7;
  float fVar8;
  undefined1 auStack_10 [8];
  float fStack_8;
  float fStack_4;
  
  
  iVar2 = this->i32_8;
  fVar7 = (float)FpPrim::GetFrameSpeed(iVar2);
  cVar1 = iVar2->i8_59;
  iVar3 = iVar2->i32_f0;
  pfVar5 = *(float **)(this + 0x1fc);
  for (iVar4 = 0; iVar4 < this->i32_1f8; iVar4 = iVar4 + 1) {
    pfVar5[1] = pfVar5[1] + fVar7;
    if (*pfVar5 < pfVar5[1]) {
      if (cVar1 == '\0') {
        if (pfVar5[0x2f] <= 0.0) {
          pfVar5[1] = *pfVar5 + 100.0;
        }
      }
      else {
        (**(code **)(this->i32_1e4 + 0x4c))(this,iVar4,0);
      }
    }
    else if (0.0 < pfVar5[1]) {
      pfVar5[0xc] = pfVar5[0xc] + pfVar5[4] * fVar7;
      pfVar5[0xd] = pfVar5[0xd] + pfVar5[5] * fVar7;
      pfVar5[0xe] = pfVar5[0xe] + pfVar5[6] * fVar7;
      if ((float)iVar3 <= pfVar5[1]) {
        pfVar5[4] = pfVar5[4] + pfVar5[8] * fVar7;
        pfVar5[5] = pfVar5[5] + pfVar5[9] * fVar7;
        pfVar5[6] = pfVar5[6] + pfVar5[10] * fVar7;
      }
      FpSmoke::GetColor(pfVar5[1],auStack_10,iVar2);
      pfVar5[0x2c] = auStack_10._0_4_;
      pfVar5[0x2d] = auStack_10._4_4_;
      pfVar5[0x2e] = fStack_8;
      pfVar5[0x2f] = fStack_4;
      fVar8 = (float)FpSmoke::GetScale(*pfVar5,pfVar5[1],pfVar5[0x17],iVar2);
      pfVar5[0x14] = fVar8;
      pfVar5[0x15] = fVar8;
      pfVar5[0x16] = fVar8;
    }
    pfVar5 = pfVar5 + 0x3c;
  }
  (**(code **)(this->i32_1e4 + 0x44))();
  return;
}

// JP: 0x002aab80  SetPacket__13FpObjectSmokeFv  =  FpObjectSmoke::SetPacket
void FpObjectSmoke::SetPacket(int this)

{
  float in_zero_lo;
  float in_zero_hi;
  float in_zero_udw;
  float in_register_0000000c;
  float *pfVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  float fVar5;
  uint uVar6;
  float fStack_90;
  float fStack_8c;
  float fStack_88;
  float fStack_84;
  float *pfStack_64;
  float *pfStack_60;
  float *pfStack_5c;
  float *pfStack_58;
  float *pfStack_54;
  float *pfStack_50;
  float *pfStack_4c;
  float *pfStack_48;
  float *pfStack_44;
  float *pfStack_40;
  uint *puStack_3c;
  uint *puStack_38;
  float *pfStack_34;
  float *pfStack_30;
  ulong *puStack_2c;
  ulong *puStack_28;
  float *pfStack_24;
  uint uStack_20;
  float fStack_1c;
  float fStack_18;
  float fStack_14;
  int iStack_10;
  
  fStack_14 = this->f32_1f0 * *(float *)(this->i32_8 + 0x5c);
  pfStack_24 = *(float **)(this + 0x88);
  *pfStack_24 = in_zero_lo;
  pfStack_24[1] = in_zero_hi;
  pfStack_24[2] = in_zero_udw;
  pfStack_24[3] = in_register_0000000c;
  *pfStack_24 = (float)(&DAT_10000001 + this->i32_1f8 * 0xc);
  pfStack_24[3] = (float)(this->i32_1f8 * 0xc + 1U | 0x50000000);
  this->i32_88 = this->i32_88 + 0x10;
  puStack_2c = *(ulong **)(this + 0x88);
  *puStack_2c = (long)(this->i32_1f8 << 2) | 0x302a400000008000;
  puStack_2c[1] = 0x412;
  this->i32_88 = this->i32_88 + 0x10;
  pfVar1 = *(float **)(this + 0x88);
  iStack_10 = this;
  if (this->i32_1f4 != 0) {
    iVar3 = this->i32_1fc;
    fStack_90 = in_zero_lo;
    fStack_8c = in_zero_hi;
    fStack_88 = in_zero_udw;
    fStack_84 = in_register_0000000c;
    pfStack_34 = pfVar1;
    pfStack_30 = pfVar1;
    puStack_28 = puStack_2c;
    for (iVar2 = 0; iVar2 < iStack_10->i32_1f4; iVar2 = iVar2 + 1) {
      fStack_18 = iVar3->f32_bc * fStack_14;
      if (fStack_18 < 0.0) {
        fStack_18 = 0.0;
      }
      else if (128.0 < fStack_18) {
        fStack_18 = 128.0;
      }
      if (0.0 < fStack_18) {
        for (iVar4 = 0; iVar4 < 4; iVar4 = iVar4 + 1) {
          fStack_1c = (float)PutiObject::RotTransPer
                                       (iStack_10,iVar3 + iVar4 * 0x10 + 0x70,&fStack_90);
          uStack_20 = PutiObject::ClipFlag(iStack_10);
          *pfVar1 = *(float *)(iVar3 + iVar4 * 8 + 0xc0) * fStack_1c;
          pfVar1[1] = *(float *)(iVar3 + iVar4 * 8 + 0xc4) * fStack_1c;
          pfVar1[2] = fStack_1c;
          iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
          puStack_3c = *(uint **)(iStack_10 + 0x88);
          fVar5 = iVar3->f32_b0;
          if (fVar5 < 2.1474836e+09) {
            uVar6 = (uint)fVar5;
          }
          else {
            uVar6 = (int)(fVar5 - 2.1474836e+09) | 0x80000000;
          }
          *puStack_3c = uVar6;
          fVar5 = iVar3->f32_b4;
          if (fVar5 < 2.1474836e+09) {
            uVar6 = (uint)fVar5;
          }
          else {
            uVar6 = (int)(fVar5 - 2.1474836e+09) | 0x80000000;
          }
          puStack_3c[1] = uVar6;
          fVar5 = iVar3->f32_b8;
          if (fVar5 < 2.1474836e+09) {
            uVar6 = (uint)fVar5;
          }
          else {
            uVar6 = (int)(fVar5 - 2.1474836e+09) | 0x80000000;
          }
          puStack_3c[2] = uVar6;
          if (fStack_18 < 2.1474836e+09) {
            uVar6 = (uint)fStack_18;
          }
          else {
            uVar6 = (int)(fStack_18 - 2.1474836e+09) | 0x80000000;
          }
          puStack_3c[3] = uVar6;
          iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
          pfStack_44 = *(float **)(iStack_10 + 0x88);
          if ((iVar4 < 2) || ((uStack_20 & 0x3ffff) != 0)) {
            fStack_84 = 4.59177e-41;
          }
          *pfStack_44 = fStack_90;
          pfStack_44[1] = fStack_8c;
          pfStack_44[2] = fStack_88;
          pfStack_44[3] = fStack_84;
          iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
          pfVar1 = *(float **)(iStack_10 + 0x88);
          pfStack_4c = pfVar1;
          pfStack_48 = pfVar1;
          pfStack_40 = pfStack_44;
          puStack_38 = puStack_3c;
        }
      }
      else {
        for (iVar4 = 0; iVar4 < 4; iVar4 = iVar4 + 1) {
          *pfVar1 = in_zero_lo;
          pfVar1[1] = in_zero_hi;
          pfVar1[2] = in_zero_udw;
          pfVar1[3] = in_register_0000000c;
          iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
          pfStack_54 = *(float **)(iStack_10 + 0x88);
          *pfStack_54 = in_zero_lo;
          pfStack_54[1] = in_zero_hi;
          pfStack_54[2] = in_zero_udw;
          pfStack_54[3] = in_register_0000000c;
          iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
          pfStack_5c = *(float **)(iStack_10 + 0x88);
          *pfStack_5c = in_zero_lo;
          pfStack_5c[1] = in_zero_hi;
          pfStack_5c[2] = in_zero_udw;
          pfStack_5c[3] = in_register_0000000c;
          pfStack_5c[3] = 4.59177e-41;
          iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
          pfVar1 = *(float **)(iStack_10 + 0x88);
          pfStack_64 = pfVar1;
          pfStack_60 = pfVar1;
          pfStack_58 = pfStack_5c;
          pfStack_50 = pfStack_54;
        }
      }
      iVar3 = iVar3 + 0xf0;
    }
  }
  for (iVar3 = iStack_10->i32_1f4; iVar3 < iStack_10->i32_1f8; iVar3 = iVar3 + 1) {
    for (iVar2 = 0; iVar2 < 4; iVar2 = iVar2 + 1) {
      *pfVar1 = in_zero_lo;
      pfVar1[1] = in_zero_hi;
      pfVar1[2] = in_zero_udw;
      pfVar1[3] = in_register_0000000c;
      iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
      pfVar1 = *(float **)(iStack_10 + 0x88);
      *pfVar1 = in_zero_lo;
      pfVar1[1] = in_zero_hi;
      pfVar1[2] = in_zero_udw;
      pfVar1[3] = in_register_0000000c;
      iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
      pfVar1 = *(float **)(iStack_10 + 0x88);
      *pfVar1 = in_zero_lo;
      pfVar1[1] = in_zero_hi;
      pfVar1[2] = in_zero_udw;
      pfVar1[3] = in_register_0000000c;
      pfVar1[3] = 4.59177e-41;
      iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
      pfVar1 = *(float **)(iStack_10 + 0x88);
    }
  }
  return;
}

// JP: 0x002ab1a0  __ct__5FpSunFv  =  FpSun::FpSun
int FpSun::FpSun(int this)

{
  FpPrim::FpPrim(this);
  *(undefined1 **)(this + 0x10) = FpSun::__vt;
  this->u32_1c = 0x4061f0;
  this->u32_70 = 0;
  return this;
}

// JP: 0x002ab200  __dt__5FpSunFv  =  FpSun::~FpSun
int FpSun::~FpSun(int this,short param_2)

{
  if (this != 0) {
    *(undefined1 **)(this + 0x10) = FpSun::__vt;
    this->u32_1c = 0x4061f0;
    FpPrim::~FpPrim(this,0);
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}

// JP: 0x002ab290  Create__5FpSunF7FVectorP11FpLenzFlare  =  FpSun::Create
void FpSun::Create(undefined8 this,undefined8 param_2,undefined4 param_3)

{
  long lVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  int this;
  undefined4 uVar6;
  undefined1 auStack_70 [16];
  undefined1 auStack_60 [16];
  undefined1 auStack_50 [16];
  undefined1 auStack_40 [16];
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  
  this->u32_70 = param_3;
  if (*(char *)(this->i32_70 + 200) == '\0') {
    this->u8_58 = 0;
  }
  if (this->i8_58 == '\0') {
    this->u8_24 = this->u8_24 & 0xfe | 1;
  }
  PutiPrim::SetTexture(this,BgEffectMan::eff->i32_1c + 0x28,0);
  lVar1 = __nw(0x240);
  uVar2 = 0;
  if (lVar1 != 0) {
    uVar2 = FpObjectSunFlare::FpObjectSunFlare(lVar1,0x14,0);
  }
  PutiPrim::AddObject(this,uVar2);
  uStack_10 = 0x42c80000;
  uStack_c = 0x42a00000;
  uStack_8 = 0x42700000;
  uStack_4 = 0x41f00000;
  if (*(char *)(this->i32_70 + 200) == '\x01') {
    uStack_30 = 0x428c0000;
    uStack_2c = 0x42480000;
    uStack_28 = 0x41f00000;
    uStack_24 = 0x42a00000;
    uStack_10 = 0x428c0000;
    uStack_c = 0x42480000;
    uStack_8 = 0x41f00000;
    uStack_4 = 0x42a00000;
  }
  uVar6 = 0x42c80000;
  if (*(char *)(this->i32_70 + 200) == '\0') {
    uVar6 = 0x437a0000;
  }
  uVar3 = FVector::FVector(auStack_40,param_2);
  uVar4 = FVector::FVector(auStack_50,&uStack_10);
  FpObjectSunFlare::SetData(uVar6,0,uVar2,uVar3,uVar4,0,0,0);
  (**(code **)(*(int *)((int)uVar2 + 0x1e4) + 0x40))(uVar2,1,this->u8_58);
  if (*(char *)(this->i32_70 + 200) == '\0') {
    PutiPrim::SetTexture(this,BgEffectMan::eff->i32_1c + 200,4);
    lVar1 = __nw(0x240);
    uVar2 = 0;
    if (lVar1 != 0) {
      uVar2 = FpObjectSunFlare::FpObjectSunFlare(lVar1,0x14,0);
    }
    PutiPrim::AddObject(this,uVar2);
    uStack_20 = 0x42800000;
    uStack_1c = 0x42800000;
    uStack_18 = 0x42600000;
    uStack_14 = 0x42800000;
    uVar3 = FVector::FVector(auStack_60,param_2);
    uVar4 = FVector::FVector(auStack_70,&uStack_20);
    FpObjectSunFlare::SetData(0x43fa0000,0,uVar2,uVar3,uVar4,4,1,1);
    (**(code **)(*(int *)((int)uVar2 + 0x1e4) + 0x40))(uVar2,1,this->u8_58);
  }
  this->u32_54 = 3;
  PutiManager::AddPrim(BgEffectMan::eff,this->u32_54,this);
  return;
}

// JP: 0x002ab610  __ct__11FpLenzFlareFv  =  FpLenzFlare::FpLenzFlare
undefined8 FpLenzFlare::FpLenzFlare(undefined8 this)

{
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  int this;
  
  FpPrim::FpPrim(this);
  
  *(undefined1 **)(this + 0x10) = FpLenzFlare::__vt;
  this->u32_1c = 0x406190;
  this->u32_70 = in_zero_lo;
  this->u32_74 = in_zero_hi;
  this->u32_78 = in_zero_udw;
  this->u32_7c = in_register_0000000c;
  this->u32_80 = in_zero_lo;
  this->u32_84 = in_zero_hi;
  this->u32_88 = in_zero_udw;
  this->u32_8c = in_register_0000000c;
  this->u32_90 = in_zero_lo;
  this->u32_94 = in_zero_hi;
  this->u32_98 = in_zero_udw;
  this->u32_9c = in_register_0000000c;
  this->u32_b0 = in_zero_lo;
  this->u32_b4 = in_zero_hi;
  this->u32_b8 = in_zero_udw;
  this->u32_bc = in_register_0000000c;
  this->u32_70 = 0;
  this->u32_74 = 0;
  this->u32_78 = 0;
  this->u32_7c = 0x3f800000;
  this->u32_80 = 0;
  this->u32_84 = 0;
  this->u32_88 = 0;
  this->u32_8c = 0x3f800000;
  this->u32_90 = 0;
  this->u32_94 = 0;
  this->u32_98 = 0;
  this->u32_9c = 0x3f800000;
  this->u8_a4 = 0;
  this->u32_a8 = 0x3f800000;
  this->u32_a0 = 0;
  this->u32_b0 = 0;
  this->u32_b4 = 0;
  this->u32_b8 = 0;
  this->u32_bc = 0x3f800000;
  this->u32_c0 = 0x45000000;
  this->u32_c4 = 0x45000000;
  this->u8_c8 = 0;
  this->u32_cc = 0;
  return this;
}

// JP: 0x002ab7d0  __dt__11FpLenzFlareFv  =  FpLenzFlare::~FpLenzFlare
int FpLenzFlare::~FpLenzFlare(int this,short param_2)

{
  if (this != 0) {
    *(undefined1 **)(this + 0x10) = FpLenzFlare::__vt;
    this->u32_1c = 0x406190;
    FpPrim::~FpPrim(this,0);
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}

// JP: 0x002ab860  setLayer__11FpLenzFlareFi  =  FpLenzFlare::setLayer
void FpLenzFlare::setLayer(int this,undefined4 param_2)

{
  if (this->i32_cc != 0) {
    (**(code **)(*(int *)(this->i32_cc + 0x10) + 0x2c))
              (this->i32_cc,param_2);
  }
  FpPrim::setLayer(this,param_2);
  return;
}

// JP: 0x002ab8c0  SetDrawFlag__11FpLenzFlareFb  =  FpLenzFlare::SetDrawFlag
void FpLenzFlare::SetDrawFlag(int this,undefined1 param_2)

{
  if (this->i32_cc != 0) {
    (**(code **)(*(int *)(this->i32_cc + 0x10) + 0x38))
              (this->i32_cc,param_2);
  }
  this->u8_68 = param_2;
  return;
}

// JP: 0x002ab920  SetAlphaPower__11FpLenzFlareFfUi  =  FpLenzFlare::SetAlphaPower
void FpLenzFlare::SetAlphaPower(undefined4 this,int param_2,undefined4 param_3)

{
  if (param_2->i32_cc != 0) {
    (**(code **)(*(int *)(param_2->i32_cc + 0x10) + 0x34))
              (this,param_2->i32_cc,param_3);
  }
  FpPrim::SetAlphaPower(this,param_2,param_3);
  return;
}

// JP: 0x002ab990  DelayDelete__11FpLenzFlareFv  =  FpLenzFlare::DelayDelete
void FpLenzFlare::DelayDelete(int this)

{
  long lVar1;
  
  if ((this->i32_cc != 0) &&
     (lVar1 = PutiManager::FindPrim
                        (PutiManager::ourManager,*(undefined4 *)(this->i32_cc + 0x54),
                         this->u32_cc), lVar1 != 0)) {
    PutiPrim::Delete(this->u32_cc);
  }
  DelayDeleteObject::DelayDelete(this + 0x14);
  return;
}

// JP: 0x002aba10  Create__11FpLenzFlareF7FVector  =  FpLenzFlare::Create
void FpLenzFlare::Create(undefined8 this,undefined8 param_2)

{
  undefined4 uVar1;
  long lVar2;
  undefined8 uVar3;
  undefined4 uVar4;
  undefined8 *puVar5;
  int this;
  float fVar7;
  undefined4 uStack_120;
  undefined4 uStack_11c;
  undefined4 uStack_118;
  undefined4 uStack_114;
  undefined4 uStack_110;
  undefined4 uStack_10c;
  undefined4 uStack_108;
  undefined4 uStack_104;
  undefined4 uStack_100;
  undefined4 uStack_fc;
  undefined4 uStack_f8;
  undefined4 uStack_f4;
  undefined4 uStack_f0;
  undefined4 uStack_ec;
  undefined4 uStack_e8;
  undefined4 uStack_e4;
  undefined4 uStack_e0;
  undefined4 uStack_dc;
  undefined4 uStack_d8;
  undefined4 uStack_d4;
  undefined4 uStack_d0;
  undefined4 uStack_cc;
  undefined4 uStack_c8;
  undefined4 uStack_c4;
  undefined4 uStack_c0;
  undefined4 uStack_bc;
  undefined4 uStack_b8;
  undefined4 uStack_b4;
  undefined4 uStack_b0;
  undefined4 uStack_ac;
  undefined4 uStack_a8;
  undefined4 uStack_a4;
  undefined4 uStack_a0;
  undefined4 uStack_9c;
  undefined4 uStack_98;
  undefined4 uStack_94;
  undefined4 uStack_90;
  undefined4 uStack_8c;
  undefined4 uStack_88;
  undefined4 uStack_84;
  undefined4 uStack_80;
  undefined4 uStack_7c;
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined1 auStack_10 [16];
  
  lVar2 = __nw(0x78);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = FpSun::FpSun(lVar2);
  }
  
  this->u32_cc = uVar1;
  uVar3 = FVector::FVector(auStack_10,param_2);
  FpSun::Create(this->u32_cc,uVar3,this);
  fVar7 = 1.0;
  if (this->i8_c8 == '\x01') {
    fVar7 = 2.5;
  }
  puVar5 = (undefined8 *)param_2;
  uVar3 = *puVar5;
  uVar1 = puVar5->u32_1;
  uVar4 = *(undefined4 *)((int)puVar5 + 0xc);
  this->i32_70 = (int)uVar3;
  this->i32_74 = (int)((ulong)uVar3 >> 0x20);
  this->u32_78 = uVar1;
  this->u32_7c = uVar4;
  this->u8_58 = 0;
  this->u8_24 = this->u8_24 & 0xfe | 1;
  PutiPrim::SetTexture(this,BgEffectMan::eff->i32_1c + 0x50,1);
  PutiPrim::SetTexture(this,BgEffectMan::eff->i32_1c + 0x14,2);
  PutiPrim::SetTexture(this,BgEffectMan::eff->i32_1c + 0x3c,3);
  lVar2 = __nw(0x220);
  uVar3 = 0;
  if (lVar2 != 0) {
    uVar3 = FpObjectLenzFlare::FpObjectLenzFlare(lVar2,0x14,0);
  }
  PutiPrim::AddObject(this,uVar3);
  (**(code **)(*(int *)((int)uVar3 + 0x1e4) + 0x40))(uVar3,1,this->u8_58);
  lVar2 = __nw(0x210);
  uVar3 = 0;
  if (lVar2 != 0) {
    uVar3 = FpObjectLenz::FpObjectLenz(lVar2,0x14,0);
  }
  PutiPrim::AddObject(this,uVar3);
  uStack_20 = 0x42b40000;
  uStack_1c = 0x42b40000;
  uStack_18 = 0x42700000;
  uStack_14 = 0x40a00000;
  FpObjectLenz::SetData(0x41700000,0xbeeb851f,uVar3,&uStack_20,1);
  lVar2 = __nw(0x210);
  uVar3 = 0;
  if (lVar2 != 0) {
    uVar3 = FpObjectLenz::FpObjectLenz(lVar2,0x14,0);
  }
  PutiPrim::AddObject(this,uVar3);
  uStack_30 = 0x42b40000;
  uStack_2c = 0x42b40000;
  uStack_28 = 0x42700000;
  uStack_24 = 0x40a00000;
  FpObjectLenz::SetData(0x41700000,0xbee66666,uVar3,&uStack_30,2);
  lVar2 = __nw(0x210);
  uVar3 = 0;
  if (lVar2 != 0) {
    uVar3 = FpObjectLenz::FpObjectLenz(lVar2,0x14,0);
  }
  PutiPrim::AddObject(this,uVar3);
  uStack_40 = 0x42b40000;
  uStack_3c = 0x42c80000;
  uStack_38 = 0x42a00000;
  uStack_34 = 0x40a00000;
  FpObjectLenz::SetData(0x41b00000,0xbe99999a,uVar3,&uStack_40,2);
  lVar2 = __nw(0x210);
  uVar3 = 0;
  if (lVar2 != 0) {
    uVar3 = FpObjectLenz::FpObjectLenz(lVar2,0x14,0);
  }
  PutiPrim::AddObject(this,uVar3);
  uStack_50 = 0x42b40000;
  uStack_4c = 0x42c80000;
  uStack_48 = 0x42a00000;
  uStack_44 = 0x40a00000;
  FpObjectLenz::SetData(0x41b00000,0xbe947ae1,uVar3,&uStack_50,1);
  lVar2 = __nw(0x210);
  uVar3 = 0;
  if (lVar2 != 0) {
    uVar3 = FpObjectLenz::FpObjectLenz(lVar2,0x14,0);
  }
  PutiPrim::AddObject(this,uVar3);
  uStack_60 = 0x42a00000;
  uStack_5c = 0x42b40000;
  uStack_58 = 0x42a00000;
  uStack_54 = 0x40a00000;
  FpObjectLenz::SetData(0x41e00000,0xbe6b851f,uVar3,&uStack_60,1);
  lVar2 = __nw(0x210);
  uVar3 = 0;
  if (lVar2 != 0) {
    uVar3 = FpObjectLenz::FpObjectLenz(lVar2,0x14,0);
  }
  PutiPrim::AddObject(this,uVar3);
  uStack_70 = 0x42c80000;
  uStack_6c = 0x42c80000;
  uStack_68 = 0x42a00000;
  uStack_64 = 0x40a00000;
  FpObjectLenz::SetData(0x41e00000,0xbe6147ae,uVar3,&uStack_70,2);
  lVar2 = __nw(0x210);
  uVar3 = 0;
  if (lVar2 != 0) {
    uVar3 = FpObjectLenz::FpObjectLenz(lVar2,0x14,0);
  }
  PutiPrim::AddObject(this,uVar3);
  uStack_80 = 0x42c80000;
  uStack_7c = 0x42c80000;
  uStack_78 = 0x42a00000;
  uStack_74 = 0x40a00000;
  FpObjectLenz::SetData(0x41a00000,0xbd4ccccd,uVar3,&uStack_80,1);
  lVar2 = __nw(0x210);
  uVar3 = 0;
  if (lVar2 != 0) {
    uVar3 = FpObjectLenz::FpObjectLenz(lVar2,0x14,0);
  }
  PutiPrim::AddObject(this,uVar3);
  uStack_90 = 0x42d20000;
  uStack_8c = 0x42d20000;
  uStack_88 = 0x41f00000;
  uStack_84 = 0x40a00000;
  FpObjectLenz::SetData(0x41c80000,0,uVar3,&uStack_90,1);
  lVar2 = __nw(0x210);
  uVar3 = 0;
  if (lVar2 != 0) {
    uVar3 = FpObjectLenz::FpObjectLenz(lVar2,0x14,0);
  }
  PutiPrim::AddObject(this,uVar3);
  uStack_a0 = 0x42a00000;
  uStack_9c = 0x42a00000;
  uStack_98 = 0x42c80000;
  uStack_94 = 0x40a00000;
  FpObjectLenz::SetData(0x41200000,fVar7 * 0.1,uVar3,&uStack_a0,1);
  lVar2 = __nw(0x210);
  uVar3 = 0;
  if (lVar2 != 0) {
    uVar3 = FpObjectLenz::FpObjectLenz(lVar2,0x14,0);
  }
  PutiPrim::AddObject(this,uVar3);
  uStack_b0 = 0x42a00000;
  uStack_ac = 0x428c0000;
  uStack_a8 = 0x42200000;
  uStack_a4 = 0x41200000;
  FpObjectLenz::SetData(0x40a00000,fVar7 * 0.105,uVar3,&uStack_b0,1);
  lVar2 = __nw(0x210);
  uVar3 = 0;
  if (lVar2 != 0) {
    uVar3 = FpObjectLenz::FpObjectLenz(lVar2,0x14,0);
  }
  PutiPrim::AddObject(this,uVar3);
  uStack_c0 = 0x42b40000;
  uStack_bc = 0x42c80000;
  uStack_b8 = 0x42b40000;
  uStack_b4 = 0x40a00000;
  FpObjectLenz::SetData(0x41a00000,fVar7 * 0.21,uVar3,&uStack_c0,1);
  lVar2 = __nw(0x210);
  uVar3 = 0;
  if (lVar2 != 0) {
    uVar3 = FpObjectLenz::FpObjectLenz(lVar2,0x14,0);
  }
  PutiPrim::AddObject(this,uVar3);
  uStack_d0 = 0x42a00000;
  uStack_cc = 0x428c0000;
  uStack_c8 = 0x42480000;
  uStack_c4 = 0x40a00000;
  FpObjectLenz::SetData(0x42040000,fVar7 * 0.24,uVar3,&uStack_d0,1);
  lVar2 = __nw(0x210);
  uVar3 = 0;
  if (lVar2 != 0) {
    uVar3 = FpObjectLenz::FpObjectLenz(lVar2,0x14,0);
  }
  PutiPrim::AddObject(this,uVar3);
  uStack_e0 = 0x42a00000;
  uStack_dc = 0x42a00000;
  uStack_d8 = 0x42200000;
  uStack_d4 = 0x40a00000;
  FpObjectLenz::SetData(0x42040000,fVar7 * 0.25,uVar3,&uStack_e0,3);
  lVar2 = __nw(0x210);
  uVar3 = 0;
  if (lVar2 != 0) {
    uVar3 = FpObjectLenz::FpObjectLenz(lVar2,0x14,0);
  }
  PutiPrim::AddObject(this,uVar3);
  uStack_f0 = 0x42b40000;
  uStack_ec = 0x42a00000;
  uStack_e8 = 0x42700000;
  uStack_e4 = 0x40800000;
  FpObjectLenz::SetData(0x42200000,fVar7 * 0.4,uVar3,&uStack_f0,1);
  lVar2 = __nw(0x210);
  uVar3 = 0;
  if (lVar2 != 0) {
    uVar3 = FpObjectLenz::FpObjectLenz(lVar2,0x14,0);
  }
  PutiPrim::AddObject(this,uVar3);
  uStack_100 = 0x428c0000;
  uStack_fc = 0x428c0000;
  uStack_f8 = 0x42480000;
  uStack_f4 = 0x41400000;
  FpObjectLenz::SetData(0x42820000,fVar7 * 0.5,uVar3,&uStack_100,2);
  lVar2 = __nw(0x210);
  uVar3 = 0;
  if (lVar2 != 0) {
    uVar3 = FpObjectLenz::FpObjectLenz(lVar2,0x14,0);
  }
  PutiPrim::AddObject(this,uVar3);
  uStack_110 = 0x42a00000;
  uStack_10c = 0x42820000;
  uStack_108 = 0x42480000;
  uStack_104 = 0x40400000;
  FpObjectLenz::SetData(0x437a0000,fVar7 * 0.6,uVar3,&uStack_110,1);
  lVar2 = __nw(0x210);
  uVar3 = 0;
  if (lVar2 != 0) {
    uVar3 = FpObjectLenz::FpObjectLenz(lVar2,0x14,0);
  }
  PutiPrim::AddObject(this,uVar3);
  uStack_120 = 0x42a00000;
  uStack_11c = 0x428c0000;
  uStack_118 = 0x42200000;
  uStack_114 = 0x41000000;
  FpObjectLenz::SetData(0x43340000,fVar7 * 0.73,uVar3,&uStack_120,3);
  PutiManager::AddPrim(BgEffectMan::eff,this->u32_54,this);
  return;
}

// JP: 0x002ac730  Create__11FpLenzFlareFPv  =  FpLenzFlare::Create
void FpLenzFlare::Create(int this,int param_2)

{
  undefined2 *puVar1;
  undefined8 uVar2;
  undefined1 uVar3;
  undefined1 auStack_60 [16];
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined1 auStack_40 [12];
  undefined4 uStack_34;
  undefined4 uStack_28;
  undefined2 uStack_24;
  undefined2 uStack_22;
  int iStack_20;
  int iStack_10;
  
  iStack_20 = this;
  iStack_10 = param_2;
  FVector::FVector(auStack_40,param_2);
  uVar3 = 0;
  puVar1 = (undefined2 *)FpPrim::InitFpFlag(uStack_34,iStack_20);
  uStack_24 = *puVar1;
  uStack_22 = puVar1[1];
  memset(&uStack_28,0,4);
  if ((long)((ulong)uStack_22._1_1_ << 0x3a) < 0) {
    uStack_28 = param_2->u32_10;
    iStack_20->u32_48 = param_2->u32_14;
    iStack_20->u32_4c = param_2->u32_18;
    uVar3 = (undefined1)(int)param_2->f32_1c;
    iStack_20->u8_50 = (byte)(((ulong)(byte)uStack_28 << 0x3b) >> 0x3e);
  }
  iStack_20->u8_c8 = uVar3;
  if (iStack_20->i8_c8 == '\x01') {
    iStack_20->u32_c4 = 0x44f60000;
    uStack_50 = 0x43fc7ae1;
    uStack_4c = 0xc36ee148;
    uStack_48 = 0xc1a00000;
    uStack_44 = 0x3f800000;
    FpLenzFlare::Create(iStack_20,&uStack_50);
  }
  else {
    uStack_34 = 0x3f800000;
    uVar2 = FVector::FVector(auStack_60,auStack_40);
    FpLenzFlare::Create(iStack_20,uVar2);
  }
  return;
}

// JP: 0x002ac8f0  __ct__17FpObjectLenzFlareFiPv  =  FpObjectLenzFlare::FpObjectLenzFlare
int FpObjectLenzFlare::FpObjectLenzFlare(int this,undefined4 param_2,undefined4 param_3)

{
  FpObject::FpObject(this,param_2,param_3);
  *(undefined1 **)(this + 0x1e4) = FpObjectLenzFlare::__vt;
  this->u8_210 = 0;
  return this;
}

// JP: 0x002ac950  __dt__17FpObjectLenzFlareFv  =  FpObjectLenzFlare::~FpObjectLenzFlare
int FpObjectLenzFlare::~FpObjectLenzFlare(int this,short param_2)

{
  if (this != 0) {
    *(undefined1 **)(this + 0x1e4) = FpObjectLenzFlare::__vt;
    FpObject::~FpObject(this,0);
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}

// JP: 0x002ac9d0  CreateData__17FpObjectLenzFlareFib  =  FpObjectLenzFlare::CreateData
void FpObjectLenzFlare::CreateData(int this,int param_2)

{
  int iVar1;
  undefined8 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  
  puVar5 = (undefined4 *)(this->i32_1fc + param_2 * 0xf0);
  *puVar5 = 0;
  puVar5[1] = 0;
  puVar5[2] = 0;
  puVar5[0x10] = 0x43960000;
  puVar5[0x11] = 0x43960000;
  puVar5[0x12] = 0x43960000;
  puVar5[0x13] = 0x3f800000;
  puVar5[4] = 0;
  puVar5[5] = 0;
  puVar5[6] = 0;
  puVar5[7] = 0x3f800000;
  puVar5[8] = 0;
  puVar5[9] = 0;
  puVar5[10] = 0;
  puVar5[0xb] = 0x3f800000;
  iVar1 = this->i32_8;
  uVar2 = iVar1->u64_70;
  uVar3 = iVar1->u32_78;
  uVar4 = iVar1->u32_7c;
  puVar5[0xc] = (int)uVar2;
  puVar5[0xd] = (int)((ulong)uVar2 >> 0x20);
  puVar5[0xe] = uVar3;
  puVar5[0xf] = uVar4;
  puVar5[0x14] = 0x3f800000;
  puVar5[0x15] = 0x3f800000;
  puVar5[0x16] = 0x3f800000;
  puVar5[0x17] = 0x3f800000;
  puVar5[0x18] = 0;
  puVar5[0x19] = 0;
  puVar5[0x1a] = 0;
  puVar5[0x1b] = 0x3f800000;
  puVar5[0x1c] = 0;
  puVar5[0x1d] = 0;
  puVar5[0x1e] = 0;
  puVar5[0x1f] = 0x3f800000;
  puVar5[0x20] = 0;
  puVar5[0x21] = 0;
  puVar5[0x22] = 0;
  puVar5[0x23] = 0x3f800000;
  puVar5[0x24] = 0;
  puVar5[0x25] = 0;
  puVar5[0x26] = 0;
  puVar5[0x27] = 0x3f800000;
  puVar5[0x28] = 0;
  puVar5[0x29] = 0;
  puVar5[0x2a] = 0;
  puVar5[0x2b] = 0x3f800000;
  puVar5[0x2c] = 0x42c80000;
  puVar5[0x2d] = 0x42700000;
  puVar5[0x2e] = 0x42200000;
  puVar5[0x2f] = 0x40000000;
  if (*(char *)(this->i32_8 + 200) == '\x01') {
    puVar5[0x2c] = 0x42b40000;
    puVar5[0x2d] = 0x42480000;
    puVar5[0x2e] = 0x41f00000;
    puVar5[0x2f] = 0x40400000;
  }
  puVar5[0x30] = 0;
  puVar5[0x31] = 0;
  puVar5[0x32] = 0;
  puVar5[0x33] = 0x3f800000;
  puVar5[0x34] = 0x3f800000;
  puVar5[0x35] = 0;
  puVar5[0x36] = 0x3f800000;
  puVar5[0x37] = 0x3f800000;
  return;
}

// JP: 0x002acdd0  Init__17FpObjectLenzFlareFib  =  FpObjectLenzFlare::Init
/* WARNING: Removing unreachable block (ram,0x002acf1c) */

void FpObjectLenzFlare::Init(int this,undefined4 param_2)

{
  undefined4 uVar1;
  undefined8 uVar2;
  int iVar3;
  
  this->u32_1f8 = param_2;
  this->u32_1f4 = param_2;
  iVar3 = this->i32_1f8;
  uVar2 = __nwa(iVar3 * 0xf0 + 0x10);
  uVar1 = __construct_new_array(uVar2,0x299b50,0,0xf0,iVar3);
  this->u32_1fc = uVar1;
  memset(*(void **)(this + 0x1fc),0,(long)(this->i32_1f8 * 0xf0));
  for (iVar3 = 0; iVar3 < this->i32_1f8; iVar3 = iVar3 + 1) {
    (**(code **)(this->i32_1e4 + 0x4c))(this,iVar3,0);
  }
  this->u32_1e0 = 0xffffffff;
  this->u8_14 = this->u8_14 & 0xfe | 1;
  this->u16_14 = this->u16_14 & 0xe01f | 0x20;
  PutiObject::SetRegTest(this,0x33001);
  return;
}

// JP: 0x002acf70  CalculateFunc__17FpObjectLenzFlareFv  =  FpObjectLenzFlare::CalculateFunc
/* WARNING: Removing unreachable block (ram,0x002ad634) */
/* WARNING: Removing unreachable block (ram,0x002ad534) */
/* WARNING: Removing unreachable block (ram,0x002ad5b4) */
/* WARNING: Removing unreachable block (ram,0x002ad6b4) */

void FpObjectLenzFlare::CalculateFunc(int this)

{
  int iVar1;
  undefined1 auVar2 [16];
  long lVar3;
  int iVar4;
  undefined1 (*pauVar5) [16];
  float fVar6;
  float fVar7;
  float fVar8;
  undefined1 auVar9 [16];
  undefined1 auVar10 [16];
  undefined1 auStack_1c0 [16];
  undefined1 auStack_1b0 [16];
  float fStack_1a0;
  float fStack_19c;
  undefined4 uStack_198;
  undefined4 uStack_194;
  float fStack_190;
  float fStack_18c;
  undefined4 uStack_188;
  undefined4 uStack_184;
  float fStack_180;
  float fStack_17c;
  undefined4 uStack_178;
  undefined4 uStack_174;
  float fStack_170;
  float fStack_16c;
  undefined4 uStack_168;
  undefined4 uStack_164;
  undefined4 uStack_160;
  undefined4 uStack_15c;
  undefined4 uStack_158;
  undefined4 uStack_154;
  undefined1 auStack_150 [16];
  undefined1 auStack_140 [16];
  undefined1 auStack_130 [16];
  undefined1 auStack_120 [32];
  undefined1 auStack_100 [16];
  undefined1 auStack_f0 [16];
  float fStack_e0;
  float fStack_dc;
  undefined4 uStack_d8;
  undefined4 uStack_d4;
  float fStack_d0;
  float fStack_cc;
  undefined4 uStack_c8;
  undefined4 uStack_c4;
  undefined4 uStack_c0;
  undefined4 uStack_bc;
  undefined4 uStack_b8;
  undefined4 uStack_b4;
  float fStack_b0;
  float fStack_ac;
  undefined4 uStack_a8;
  undefined4 uStack_a4;
  float fStack_a0;
  float fStack_9c;
  undefined4 uStack_98;
  undefined4 uStack_94;
  int iStack_90;
  int iStack_8c;
  undefined4 auStack_80 [16];
  undefined4 auStack_40 [16];
  
  this->u8_210 = 0;
  iVar1 = this->i32_8;
  if (iVar1->i8_c8 == '\x01') {
    lVar3 = CField::GetCtrlModel(CField::sys);
    if (lVar3 != 0) {
      FVector::FVector(&uStack_160,(int)lVar3 + 0x10);
      iVar1->u32_b0 = uStack_160;
      iVar1->u32_b4 = uStack_15c;
      iVar1->u32_b8 = uStack_158;
      iVar1->u32_bc = uStack_154;
    }
    if (iVar1->f32_b8 < -20.0) {
      this->u8_210 = 1;
    }
  }
  GsxCamera::GetViewScreenMatrix(auStack_40,CApp::camera);
  for (iVar4 = 0; iVar4 < 4; iVar4 = iVar4 + 1) {
    auStack_80[iVar4 * 4] = auStack_40[iVar4 * 4];
    auStack_80[iVar4 * 4 + 1] = auStack_40[iVar4 * 4 + 1];
    auStack_80[iVar4 * 4 + 2] = auStack_40[iVar4 * 4 + 2];
    auStack_80[iVar4 * 4 + 3] = auStack_40[iVar4 * 4 + 3];
  }
  sceVu0RotTransPers(&iStack_90,auStack_80,iVar1 + 0x70,0);
  fStack_9c = (float)iStack_8c / 16.0;
  fStack_a0 = (float)iStack_90 / 16.0;
  uStack_98 = 0;
  uStack_94 = 0x3f800000;
  fStack_ac = iVar1->f32_c4;
  fStack_b0 = iVar1->f32_c0;
  uStack_a8 = 0;
  uStack_a4 = 0x3f800000;
  uStack_c0 = 0x43800000;
  uStack_bc = 0x43600000;
  uStack_b8 = 0;
  uStack_b4 = 0x3f800000;
  fVar6 = (float)FVector::Length(&uStack_c0);
  auVar9._4_4_ = fStack_ac;
  auVar9._0_4_ = fStack_b0;
  auVar9._8_4_ = uStack_a8;
  auVar9._12_4_ = uStack_a4;
  auVar9 = _lqc2(auVar9);
  auVar10._4_4_ = fStack_9c;
  auVar10._0_4_ = fStack_a0;
  auVar10._8_4_ = uStack_98;
  auVar10._12_4_ = uStack_94;
  auVar10 = _lqc2(auVar10);
  auVar9 = _vsub(auVar9,auVar10);
  auStack_1b0 = _sqc2(auVar9);
  FVector::FVector(&fStack_d0,auStack_1b0);
  fVar7 = (float)FVector::Length(&fStack_d0);
  fVar8 = fVar6;
  if (fVar7 <= fVar6) {
    fVar8 = fVar7;
  }
  FVector::Normalize(&fStack_d0);
  FVector::__amu(0x43e00000,&fStack_d0);
  iVar1->f32_80 = fStack_d0;
  iVar1->f32_84 = fStack_cc;
  iVar1->u32_88 = uStack_c8;
  iVar1->u32_8c = uStack_c4;
  fVar8 = fVar8 / fVar6;
  iVar1->f32_a0 = fVar8;
  fStack_1a0 = *(float *)(this->i32_1fc + 0x40) / 2.0;
  fStack_19c = fStack_1a0 * 1.1428572;
  fStack_170 = -fStack_1a0;
  fStack_16c = -fStack_19c;
  uStack_168 = 0;
  uStack_164 = 0x3f800000;
  iVar4 = this->i32_1fc;
  iVar4->f32_70 = fStack_170;
  iVar4->f32_74 = fStack_16c;
  iVar4->u32_78 = 0;
  iVar4->u32_7c = 0x3f800000;
  fStack_180 = -fStack_1a0;
  uStack_178 = 0;
  uStack_174 = 0x3f800000;
  iVar4 = this->i32_1fc;
  iVar4->f32_80 = fStack_180;
  iVar4->f32_84 = fStack_19c;
  iVar4->u32_88 = 0;
  iVar4->u32_8c = 0x3f800000;
  fStack_18c = -fStack_19c;
  uStack_188 = 0;
  uStack_184 = 0x3f800000;
  iVar4 = this->i32_1fc;
  iVar4->f32_90 = fStack_1a0;
  iVar4->f32_94 = fStack_18c;
  iVar4->u32_98 = 0;
  iVar4->u32_9c = 0x3f800000;
  uStack_198 = 0;
  uStack_194 = 0x3f800000;
  iVar4 = this->i32_1fc;
  iVar4->f32_a0 = fStack_1a0;
  iVar4->f32_a4 = fStack_19c;
  iVar4->u32_a8 = 0;
  iVar4->u32_ac = 0x3f800000;
  for (iVar4 = 0; iVar4 < 4; iVar4 = iVar4 + 1) {
    pauVar5 = (undefined1 (*) [16])(this->i32_1fc + iVar4 * 0x10 + 0x70);
    auVar2._4_4_ = fStack_9c;
    auVar2._0_4_ = fStack_a0;
    auVar2._8_4_ = uStack_98;
    auVar2._12_4_ = uStack_94;
    auVar10 = _lqc2(auVar2);
    auVar9 = _lqc2(*pauVar5);
    auVar9 = _vadd(auVar9,auVar10);
    auVar9 = _sqc2(auVar9);
    *pauVar5 = auVar9;
  }
  fVar6 = 1.0;
  if (iVar1->i8_c8 == '\x01') {
    fVar6 = 2.5;
  }
  fStack_e0 = fStack_b0 + fVar8 * fStack_d0 * 0.73 * fVar6;
  fStack_dc = fStack_ac + fVar8 * fStack_cc * 0.73 * fVar6;
  uStack_d8 = 0;
  uStack_d4 = 0x3f800000;
  iVar1->f32_90 = fStack_e0;
  iVar1->f32_94 = fStack_dc;
  iVar1->f32_98 = fVar8;
  fVar8 = 1.0;
  fStack_a0 = fStack_a0 - 2048.0;
  fStack_9c = fStack_9c - 2048.0;
  if ((((fStack_a0 < -307.2) || (307.2 < fStack_a0)) || (fStack_9c < -268.80002)) ||
     (268.80002 < fStack_9c)) {
    this->u8_210 = 1;
    fVar8 = 0.0;
  }
  else {
    if (-256.0 <= fStack_a0) {
      if (256.0 < fStack_a0) {
        fVar8 = (307.2 - fStack_a0) / 51.2;
      }
      else if (fStack_9c < -224.0) {
        fVar8 = -(-268.80002 - fStack_9c) / 44.8;
      }
      else if (224.0 < fStack_9c) {
        fVar8 = (268.80002 - fStack_9c) / 44.8;
      }
    }
    else {
      fVar8 = -(-307.2 - fStack_a0) / 51.2;
    }
    fStack_190 = fStack_1a0;
    fStack_17c = fStack_19c;
    Matrix::Matrix(auStack_120,CApp::camera + 0x240);
    FVector::FVector(auStack_130,auStack_f0);
    FVector::FVector(auStack_140,auStack_100);
    auVar9 = _lqc2(*(undefined1 (*) [16])(iVar1 + 0x70));
    auVar10 = _lqc2(auStack_130);
    auVar9 = _vsub(auVar9,auVar10);
    auStack_1c0 = _sqc2(auVar9);
    FVector::FVector(auStack_150,auStack_1c0);
    auVar9 = _lqc2(auStack_140);
    auVar10 = _lqc2(auStack_150);
    auVar9 = _vmul(auVar9,auVar10);
    auVar9 = _vaddbc(auVar9,auVar9);
    auVar9 = _vaddbc(auVar9,auVar9);
    auVar9 = _qmfc2(auVar9._0_4_);
    if (auVar9._0_4_ < 0.0) {
      this->u8_210 = 1;
      fVar8 = 0.0;
    }
  }
  if (1.0 < fVar8) {
    fVar8 = 1.0;
  }
  iVar1->f32_a8 = fVar8;
  iVar1->u8_a4 = this->u8_210;
  iVar1->f32_5c = fVar8;
  return;
}

// JP: 0x002ad810  SetPacket__17FpObjectLenzFlareFv  =  FpObjectLenzFlare::SetPacket
void FpObjectLenzFlare::SetPacket(int this)

{
  int iVar1;
  uint *puVar2;
  ulong *puVar3;
  int iVar4;
  uint in_zero_lo;
  uint in_zero_hi;
  uint in_zero_udw;
  uint in_register_0000000c;
  undefined4 *puVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  float fVar9;
  uint uVar10;
  
  iVar1 = this->i32_8;
  puVar2 = *(uint **)(this + 0x88);
  *puVar2 = in_zero_lo;
  puVar2[1] = in_zero_hi;
  puVar2[2] = in_zero_udw;
  puVar2[3] = in_register_0000000c;
  *puVar2 = (uint)(&DAT_10000001 + this->i32_1f8 * 0xc);
  puVar2[3] = this->i32_1f8 * 0xc + 1U | 0x50000000;
  this->i32_88 = this->i32_88 + 0x10;
  puVar3 = *(ulong **)(this + 0x88);
  *puVar3 = (long)(this->i32_1f8 << 2) | 0x302a400000008000;
  puVar3[1] = 0x412;
  this->i32_88 = this->i32_88 + 0x10;
  puVar5 = *(undefined4 **)(this + 0x88);
  iVar6 = this->i32_1fc;
  for (iVar8 = 0; iVar8 < this->i32_1f8; iVar8 = iVar8 + 1) {
    for (iVar7 = 0; iVar7 < 4; iVar7 = iVar7 + 1) {
      *puVar5 = *(undefined4 *)(iVar6 + iVar7 * 8 + 0xc0);
      puVar5[1] = *(undefined4 *)(iVar6 + iVar7 * 8 + 0xc4);
      puVar5[2] = 0x3f800000;
      puVar5[3] = 0;
      this->i32_88 = this->i32_88 + 0x10;
      puVar2 = *(uint **)(this + 0x88);
      fVar9 = iVar6->f32_b0;
      if (fVar9 < 2.1474836e+09) {
        uVar10 = (uint)fVar9;
      }
      else {
        uVar10 = (int)(fVar9 - 2.1474836e+09) | 0x80000000;
      }
      *puVar2 = uVar10;
      fVar9 = iVar6->f32_b4;
      if (fVar9 < 2.1474836e+09) {
        uVar10 = (uint)fVar9;
      }
      else {
        uVar10 = (int)(fVar9 - 2.1474836e+09) | 0x80000000;
      }
      puVar2[1] = uVar10;
      fVar9 = iVar6->f32_b8;
      if (fVar9 < 2.1474836e+09) {
        uVar10 = (uint)fVar9;
      }
      else {
        uVar10 = (int)(fVar9 - 2.1474836e+09) | 0x80000000;
      }
      puVar2[2] = uVar10;
      fVar9 = iVar6->f32_bc;
      if (fVar9 < 2.1474836e+09) {
        uVar10 = (uint)fVar9;
      }
      else {
        uVar10 = (int)(fVar9 - 2.1474836e+09) | 0x80000000;
      }
      puVar2[3] = uVar10;
      if (iVar1->i8_c8 == '\x01') {
        iVar4 = this->i32_8;
        if ((iVar4->f32_b0 < 40.0) || (70.0 < iVar4->f32_b0)) {
          if ((70.0 < iVar4->f32_b0) && (iVar4->f32_b0 < 120.0)) {
            puVar2[3] = 0;
          }
        }
        else {
          fVar9 = iVar6->f32_bc * ((70.0 - iVar4->f32_b0) / 30.0);
          if (fVar9 < 2.1474836e+09) {
            uVar10 = (uint)fVar9;
          }
          else {
            uVar10 = (int)(fVar9 - 2.1474836e+09) | 0x80000000;
          }
          puVar2[3] = uVar10;
        }
        if ((iVar4->f32_b0 < 190.0) || (200.0 < iVar4->f32_b0)) {
          if (200.0 < iVar4->f32_b0) {
            puVar2[3] = 0;
          }
        }
        else {
          fVar9 = iVar6->f32_bc * ((200.0 - iVar4->f32_b0) / 10.0);
          if (fVar9 < 2.1474836e+09) {
            uVar10 = (uint)fVar9;
          }
          else {
            uVar10 = (int)(fVar9 - 2.1474836e+09) | 0x80000000;
          }
          puVar2[3] = uVar10;
        }
      }
      else {
        fVar9 = iVar6->f32_bc * iVar1->f32_a8;
        if (fVar9 < 2.1474836e+09) {
          uVar10 = (uint)fVar9;
        }
        else {
          uVar10 = (int)(fVar9 - 2.1474836e+09) | 0x80000000;
        }
        puVar2[3] = uVar10;
      }
      this->i32_88 = this->i32_88 + 0x10;
      puVar2 = *(uint **)(this + 0x88);
      *puVar2 = in_zero_lo;
      puVar2[1] = in_zero_hi;
      puVar2[2] = in_zero_udw;
      puVar2[3] = in_register_0000000c;
      fVar9 = *(float *)(iVar6 + iVar7 * 0x10 + 0x70) * 16.0;
      if (fVar9 < 2.1474836e+09) {
        uVar10 = (uint)fVar9;
      }
      else {
        uVar10 = (int)(fVar9 - 2.1474836e+09) | 0x80000000;
      }
      *puVar2 = uVar10;
      fVar9 = *(float *)(iVar6 + iVar7 * 0x10 + 0x74) * 16.0;
      if (fVar9 < 2.1474836e+09) {
        uVar10 = (uint)fVar9;
      }
      else {
        uVar10 = (int)(fVar9 - 2.1474836e+09) | 0x80000000;
      }
      puVar2[1] = uVar10;
      if ((iVar7 < 2) || (this->i8_210 != '\0')) {
        puVar2[3] = 0x8000;
      }
      this->i32_88 = this->i32_88 + 0x10;
      puVar5 = *(undefined4 **)(this + 0x88);
    }
    iVar6 = iVar6 + 0xf0;
  }
  return;
}

// JP: 0x002adea0  __ct__12FpObjectLenzFiPv  =  FpObjectLenz::FpObjectLenz
int FpObjectLenz::FpObjectLenz(int this,undefined4 param_2,undefined4 param_3)

{
  FpObject::FpObject(this,param_2,param_3);
  *(undefined1 **)(this + 0x1e4) = FpObjectLenz::__vt;
  (**(code **)(this->i32_1e4 + 0x40))(this,1,0);
  return this;
}

// JP: 0x002adf10  __dt__12FpObjectLenzFv  =  FpObjectLenz::~FpObjectLenz
int FpObjectLenz::~FpObjectLenz(int this,short param_2)

{
  if (this != 0) {
    *(undefined1 **)(this + 0x1e4) = FpObjectLenz::__vt;
    FpObject::~FpObject(this,0);
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}

// JP: 0x002adf90  CreateData__12FpObjectLenzFib  =  FpObjectLenz::CreateData
void FpObjectLenz::CreateData(int this,int param_2)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)(this->i32_1fc + param_2 * 0xf0);
  *puVar1 = 0;
  puVar1[1] = 0;
  puVar1[2] = 0;
  puVar1[0x10] = 0x3f800000;
  puVar1[0x11] = 0x3f800000;
  puVar1[0x12] = 0;
  puVar1[0x13] = 0x3f800000;
  puVar1[4] = 0;
  puVar1[5] = 0;
  puVar1[6] = 0;
  puVar1[7] = 0x3f800000;
  puVar1[8] = 0;
  puVar1[9] = 0;
  puVar1[10] = 0;
  puVar1[0xb] = 0x3f800000;
  puVar1[0xc] = 0;
  puVar1[0xd] = 0;
  puVar1[0xe] = 0;
  puVar1[0xf] = 0x3f800000;
  puVar1[0x14] = 0x3f800000;
  puVar1[0x15] = 0x3f800000;
  puVar1[0x16] = 0x3f800000;
  puVar1[0x17] = 0x3f800000;
  puVar1[0x18] = 0;
  puVar1[0x19] = 0;
  puVar1[0x1a] = 0;
  puVar1[0x1b] = 0x3f800000;
  puVar1[0x1c] = 0;
  puVar1[0x1d] = 0;
  puVar1[0x1e] = 0;
  puVar1[0x1f] = 0x3f800000;
  puVar1[0x20] = 0;
  puVar1[0x21] = 0;
  puVar1[0x22] = 0;
  puVar1[0x23] = 0x3f800000;
  puVar1[0x24] = 0;
  puVar1[0x25] = 0;
  puVar1[0x26] = 0;
  puVar1[0x27] = 0x3f800000;
  puVar1[0x28] = 0;
  puVar1[0x29] = 0;
  puVar1[0x2a] = 0;
  puVar1[0x2b] = 0x3f800000;
  puVar1[0x30] = 0;
  puVar1[0x31] = 0;
  puVar1[0x32] = 0;
  puVar1[0x33] = 0x3f800000;
  puVar1[0x34] = 0x3f800000;
  puVar1[0x35] = 0;
  puVar1[0x36] = 0x3f800000;
  puVar1[0x37] = 0x3f800000;
  return;
}

// JP: 0x002ae300  Init__12FpObjectLenzFib  =  FpObjectLenz::Init
void FpObjectLenz::Init(int this,undefined4 param_2,char param_3)

{
  undefined4 uVar1;
  undefined8 uVar2;
  int iVar3;
  
  this->u32_1f8 = param_2;
  this->u32_1f4 = param_2;
  iVar3 = this->i32_1f8;
  uVar2 = __nwa(iVar3 * 0xf0 + 0x10);
  uVar1 = __construct_new_array(uVar2,0x299b50,0,0xf0,iVar3);
  this->u32_1fc = uVar1;
  memset(*(void **)(this + 0x1fc),0,(long)(this->i32_1f8 * 0xf0));
  for (iVar3 = 0; iVar3 < this->i32_1f8; iVar3 = iVar3 + 1) {
    (**(code **)(this->i32_1e4 + 0x4c))(this,iVar3,0);
  }
  this->u32_1e0 = 0xffffffff;
  this->u8_14 = this->u8_14 & 0xfe | 1;
  this->u16_14 = this->u16_14 & 0xe01f;
  this->u8_14 = this->u8_14 & 0xf7;
  if (param_3 == '\0') {
    PutiObject::SetRegTest(this,0x33001);
  }
  else {
    PutiObject::SetRegTest(this,0x73001);
  }
  return;
}

// JP: 0x002ae4c0  SetData__12FpObjectLenzF7FVectorffUi  =  FpObjectLenz::SetData
void FpObjectLenz::SetData
               (undefined4 this,undefined4 param_2,int param_3,undefined8 *param_4,ushort param_5
               )

{
  int iVar1;
  undefined8 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
  iVar1 = param_3->i32_1fc;
  uVar2 = *param_4;
  uVar3 = param_4->u32_1;
  uVar4 = *(undefined4 *)((int)param_4 + 0xc);
  iVar1->i32_b0 = (int)uVar2;
  iVar1->i32_b4 = (int)((ulong)uVar2 >> 0x20);
  iVar1->u32_b8 = uVar3;
  iVar1->u32_bc = uVar4;
  iVar1->u32_40 = this;
  iVar1->u32_44 = this;
  iVar1->u32_48 = this;
  iVar1->u32_4c = 0x3f800000;
  param_3->u16_14 = param_3->u16_14 & 0xe01f | (param_5 & 0xff) << 5;
  iVar1->u32_10 = param_2;
  return;
}

// JP: 0x002ae530  CalculateFunc__12FpObjectLenzFv  =  FpObjectLenz::CalculateFunc
void FpObjectLenz::CalculateFunc(int this)

{
  int iVar1;
  int iVar2;
  int iVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  
  iVar1 = this->i32_1fc;
  iVar3 = this->i32_8;
  fVar11 = iVar1->f32_40 / 2.0;
  fVar4 = fVar11 * 1.1428572;
  iVar1->f32_70 = -fVar11;
  iVar1->f32_74 = -fVar4;
  iVar1->u32_78 = 0;
  iVar1->u32_7c = 0x3f800000;
  iVar1->f32_80 = -fVar11;
  iVar1->f32_84 = fVar4;
  iVar1->u32_88 = 0;
  iVar1->u32_8c = 0x3f800000;
  iVar1->f32_90 = fVar11;
  iVar1->f32_94 = -fVar4;
  iVar1->u32_98 = 0;
  iVar1->u32_9c = 0x3f800000;
  iVar1->f32_a0 = fVar11;
  iVar1->f32_a4 = fVar4;
  iVar1->u32_a8 = 0;
  iVar1->u32_ac = 0x3f800000;
  fVar4 = iVar3->f32_80;
  fVar5 = iVar1->f32_10;
  fVar6 = iVar3->f32_a0;
  fVar7 = iVar3->f32_c0;
  fVar11 = iVar3->f32_84;
  fVar8 = iVar1->f32_10;
  fVar9 = iVar3->f32_a0;
  fVar10 = iVar3->f32_c4;
  for (iVar3 = 0; iVar3 < 4; iVar3 = iVar3 + 1) {
    iVar2 = iVar1 + iVar3 * 0x10;
    iVar2->f32_70 = iVar2->f32_70 + fVar7 + fVar6 * fVar4 * fVar5;
    iVar2 = iVar1 + iVar3 * 0x10;
    iVar2->f32_74 = iVar2->f32_74 + fVar10 + fVar9 * fVar11 * fVar8;
  }
  return;
}

// JP: 0x002ae6d0  SetPacket__12FpObjectLenzFv  =  FpObjectLenz::SetPacket
void FpObjectLenz::SetPacket(int this)

{
  int iVar1;
  uint *puVar2;
  ulong *puVar3;
  int iVar4;
  uint in_zero_lo;
  uint in_zero_hi;
  uint in_zero_udw;
  uint in_register_0000000c;
  undefined4 *puVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  float fVar9;
  uint uVar10;
  
  iVar1 = this->i32_8;
  puVar2 = *(uint **)(this + 0x88);
  *puVar2 = in_zero_lo;
  puVar2[1] = in_zero_hi;
  puVar2[2] = in_zero_udw;
  puVar2[3] = in_register_0000000c;
  *puVar2 = (uint)(&DAT_10000001 + this->i32_1f8 * 0xc);
  puVar2[3] = this->i32_1f8 * 0xc + 1U | 0x50000000;
  this->i32_88 = this->i32_88 + 0x10;
  puVar3 = *(ulong **)(this + 0x88);
  *puVar3 = (long)(this->i32_1f8 << 2) | 0x302a400000008000;
  puVar3[1] = 0x412;
  this->i32_88 = this->i32_88 + 0x10;
  puVar5 = *(undefined4 **)(this + 0x88);
  iVar6 = this->i32_1fc;
  for (iVar8 = 0; iVar8 < this->i32_1f8; iVar8 = iVar8 + 1) {
    for (iVar7 = 0; iVar7 < 4; iVar7 = iVar7 + 1) {
      *puVar5 = *(undefined4 *)(iVar6 + iVar7 * 8 + 0xc0);
      puVar5[1] = *(undefined4 *)(iVar6 + iVar7 * 8 + 0xc4);
      puVar5[2] = 0x3f800000;
      puVar5[3] = 0;
      this->i32_88 = this->i32_88 + 0x10;
      puVar2 = *(uint **)(this + 0x88);
      fVar9 = iVar6->f32_b0;
      if (fVar9 < 2.1474836e+09) {
        uVar10 = (uint)fVar9;
      }
      else {
        uVar10 = (int)(fVar9 - 2.1474836e+09) | 0x80000000;
      }
      *puVar2 = uVar10;
      fVar9 = iVar6->f32_b4;
      if (fVar9 < 2.1474836e+09) {
        uVar10 = (uint)fVar9;
      }
      else {
        uVar10 = (int)(fVar9 - 2.1474836e+09) | 0x80000000;
      }
      puVar2[1] = uVar10;
      fVar9 = iVar6->f32_b8;
      if (fVar9 < 2.1474836e+09) {
        uVar10 = (uint)fVar9;
      }
      else {
        uVar10 = (int)(fVar9 - 2.1474836e+09) | 0x80000000;
      }
      puVar2[2] = uVar10;
      fVar9 = iVar6->f32_bc;
      if (fVar9 < 2.1474836e+09) {
        uVar10 = (uint)fVar9;
      }
      else {
        uVar10 = (int)(fVar9 - 2.1474836e+09) | 0x80000000;
      }
      puVar2[3] = uVar10;
      if (iVar1->i8_c8 == '\x01') {
        iVar4 = this->i32_8;
        if ((iVar4->f32_b0 < 40.0) || (70.0 < iVar4->f32_b0)) {
          if ((70.0 < iVar4->f32_b0) && (iVar4->f32_b0 < 120.0)) {
            puVar2[3] = 0;
          }
        }
        else {
          fVar9 = iVar6->f32_bc * ((70.0 - iVar4->f32_b0) / 30.0);
          if (fVar9 < 2.1474836e+09) {
            uVar10 = (uint)fVar9;
          }
          else {
            uVar10 = (int)(fVar9 - 2.1474836e+09) | 0x80000000;
          }
          puVar2[3] = uVar10;
        }
        if ((iVar4->f32_b0 < 190.0) || (200.0 < iVar4->f32_b0)) {
          if (200.0 < iVar4->f32_b0) {
            puVar2[3] = 0;
          }
        }
        else {
          fVar9 = iVar6->f32_bc * ((200.0 - iVar4->f32_b0) / 10.0);
          if (fVar9 < 2.1474836e+09) {
            uVar10 = (uint)fVar9;
          }
          else {
            uVar10 = (int)(fVar9 - 2.1474836e+09) | 0x80000000;
          }
          puVar2[3] = uVar10;
        }
      }
      else {
        fVar9 = iVar6->f32_bc * iVar1->f32_a8;
        if (fVar9 < 2.1474836e+09) {
          uVar10 = (uint)fVar9;
        }
        else {
          uVar10 = (int)(fVar9 - 2.1474836e+09) | 0x80000000;
        }
        puVar2[3] = uVar10;
      }
      this->i32_88 = this->i32_88 + 0x10;
      puVar2 = *(uint **)(this + 0x88);
      *puVar2 = in_zero_lo;
      puVar2[1] = in_zero_hi;
      puVar2[2] = in_zero_udw;
      puVar2[3] = in_register_0000000c;
      fVar9 = *(float *)(iVar6 + iVar7 * 0x10 + 0x70) * 16.0;
      if (fVar9 < 2.1474836e+09) {
        uVar10 = (uint)fVar9;
      }
      else {
        uVar10 = (int)(fVar9 - 2.1474836e+09) | 0x80000000;
      }
      *puVar2 = uVar10;
      fVar9 = *(float *)(iVar6 + iVar7 * 0x10 + 0x74) * 16.0;
      if (fVar9 < 2.1474836e+09) {
        uVar10 = (uint)fVar9;
      }
      else {
        uVar10 = (int)(fVar9 - 2.1474836e+09) | 0x80000000;
      }
      puVar2[1] = uVar10;
      if ((iVar7 < 2) || (iVar1->i8_a4 != '\0')) {
        puVar2[3] = 0x8000;
      }
      this->i32_88 = this->i32_88 + 0x10;
      puVar5 = *(undefined4 **)(this + 0x88);
    }
    iVar6 = iVar6 + 0xf0;
  }
  return;
}

// JP: 0x002aed60  __ct__16FpObjectSunFlareFiPv  =  FpObjectSunFlare::FpObjectSunFlare
undefined8 FpObjectSunFlare::FpObjectSunFlare(undefined8 this)

{
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  int this;
  
  FpObject::FpObject(this);
  
  *(undefined1 **)(this + 0x1e4) = FpObjectSunFlare::__vt;
  this->u32_210 = in_zero_lo;
  this->u32_214 = in_zero_hi;
  this->u32_218 = in_zero_udw;
  this->u32_21c = in_register_0000000c;
  this->u32_220 = in_zero_lo;
  this->u32_224 = in_zero_hi;
  this->u32_228 = in_zero_udw;
  this->u32_22c = in_register_0000000c;
  this->u32_210 = 0;
  this->u32_214 = 0;
  this->u32_218 = 0;
  this->u32_21c = 0x3f800000;
  this->u32_220 = 0x43000000;
  this->u32_224 = 0x43000000;
  this->u32_228 = 0x43000000;
  this->u32_22c = 0x43000000;
  this->u32_230 = 0;
  this->u32_234 = 0;
  this->u8_238 = 0;
  this->u8_239 = 0;
  return this;
}

// JP: 0x002aee60  __dt__16FpObjectSunFlareFv  =  FpObjectSunFlare::~FpObjectSunFlare
int FpObjectSunFlare::~FpObjectSunFlare(int this,short param_2)

{
  if (this != 0) {
    *(undefined1 **)(this + 0x1e4) = FpObjectSunFlare::__vt;
    FpObject::~FpObject(this,0);
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}

// JP: 0x002aeee0  SetData__16FpObjectSunFlareF7FVector7FVectorfUifbb  =  FpObjectSunFlare::SetData
void FpObjectSunFlare::SetData
               (undefined4 this,undefined4 param_2,int param_3,undefined4 *param_4,
               undefined4 *param_5,ushort param_6,undefined1 param_7,undefined1 param_8)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  uVar1 = param_4[1];
  uVar2 = param_4[2];
  uVar3 = param_4[3];
  param_3->u32_210 = *param_4;
  param_3->u32_214 = uVar1;
  param_3->u32_218 = uVar2;
  param_3->u32_21c = uVar3;
  uVar1 = param_5[1];
  uVar2 = param_5[2];
  uVar3 = param_5[3];
  param_3->u32_220 = *param_5;
  param_3->u32_224 = uVar1;
  param_3->u32_228 = uVar2;
  param_3->u32_22c = uVar3;
  param_3->u32_230 = this;
  param_3->u16_14 = param_3->u16_14 & 0xe01f | (param_6 & 0xff) << 5;
  param_3->u32_234 = param_2;
  param_3->u8_238 = param_7;
  param_3->u8_239 = param_8;
  return;
}

// JP: 0x002aef30  CreateData__16FpObjectSunFlareFib  =  FpObjectSunFlare::CreateData
void FpObjectSunFlare::CreateData(int this,int param_2)

{
  undefined8 uVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  
  puVar3 = (undefined4 *)(this->i32_1fc + param_2 * 0xf0);
  *puVar3 = 0;
  puVar3[1] = 0;
  puVar3[2] = 0;
  uVar4 = this->u32_230;
  puVar3[0x10] = this->u32_230;
  puVar3[0x11] = uVar4;
  puVar3[0x12] = 0;
  puVar3[0x13] = 0x3f800000;
  puVar3[4] = 0;
  puVar3[5] = 0;
  puVar3[6] = 0;
  puVar3[7] = 0x3f800000;
  puVar3[8] = 0;
  puVar3[9] = 0;
  puVar3[10] = 0;
  puVar3[0xb] = 0x3f800000;
  uVar1 = this->u64_210;
  uVar4 = this->u32_218;
  uVar2 = this->u32_21c;
  puVar3[0xc] = (int)uVar1;
  puVar3[0xd] = (int)((ulong)uVar1 >> 0x20);
  puVar3[0xe] = uVar4;
  puVar3[0xf] = uVar2;
  puVar3[0x14] = 0x3f800000;
  puVar3[0x15] = 0x3f800000;
  puVar3[0x16] = 0x3f800000;
  puVar3[0x17] = 0x3f800000;
  puVar3[0x18] = 0;
  puVar3[0x19] = 0;
  puVar3[0x1a] = 0;
  puVar3[0x1b] = 0x3f800000;
  puVar3[0x1c] = 0;
  puVar3[0x1d] = 0;
  puVar3[0x1e] = 0;
  puVar3[0x1f] = 0x3f800000;
  puVar3[0x20] = 0;
  puVar3[0x21] = 0;
  puVar3[0x22] = 0;
  puVar3[0x23] = 0x3f800000;
  puVar3[0x24] = 0;
  puVar3[0x25] = 0;
  puVar3[0x26] = 0;
  puVar3[0x27] = 0x3f800000;
  puVar3[0x28] = 0;
  puVar3[0x29] = 0;
  puVar3[0x2a] = 0;
  puVar3[0x2b] = 0x3f800000;
  puVar3[0x2c] = this->u32_220;
  puVar3[0x2d] = this->u32_224;
  puVar3[0x2e] = this->u32_228;
  puVar3[0x2f] = this->u32_22c;
  puVar3[0x30] = 0;
  puVar3[0x31] = 0;
  puVar3[0x32] = 0;
  puVar3[0x33] = 0x3f800000;
  puVar3[0x34] = 0x3f800000;
  puVar3[0x35] = 0;
  puVar3[0x36] = 0x3f800000;
  puVar3[0x37] = 0x3f800000;
  return;
}

// JP: 0x002af280  Init__16FpObjectSunFlareFib  =  FpObjectSunFlare::Init
void FpObjectSunFlare::Init(int this,undefined4 param_2,char param_3)

{
  undefined4 uVar1;
  undefined8 uVar2;
  int iVar3;
  
  this->u32_1f8 = param_2;
  this->u32_1f4 = param_2;
  iVar3 = this->i32_1f8;
  uVar2 = __nwa(iVar3 * 0xf0 + 0x10);
  uVar1 = __construct_new_array(uVar2,0x299b50,0,0xf0,iVar3);
  this->u32_1fc = uVar1;
  memset(*(void **)(this + 0x1fc),0,(long)(this->i32_1f8 * 0xf0));
  for (iVar3 = 0; iVar3 < this->i32_1f8; iVar3 = iVar3 + 1) {
    (**(code **)(this->i32_1e4 + 0x4c))(this,iVar3,0);
  }
  this->u32_1e0 = 0xffffffff;
  this->u8_14 = this->u8_14 & 0xfe | 1;
  if (param_3 == '\0') {
    PutiObject::SetRegTest(this,0x33001);
  }
  else {
    PutiObject::SetRegTest(this,0x73001);
  }
  return;
}

// JP: 0x002af400  CalculateFunc__16FpObjectSunFlareFv  =  FpObjectSunFlare::CalculateFunc
void FpObjectSunFlare::CalculateFunc(int this)

{
  if (*(char *)(*(int *)(this->i32_8 + 0x70) + 200) == '\x01') {
    (**(code **)(this->i32_1e4 + 0x44))();
  }
  else {
    FpObjectSunFlare::CalcFpSunVertex(this->u32_234,this);
  }
  return;
}

// JP: 0x002af480  CalcFpSunVertex__16FpObjectSunFlareFf  =  FpObjectSunFlare::CalcFpSunVertex
void FpObjectSunFlare::CalcFpSunVertex(undefined4 this,int param_2)

{
  bool bVar1;
  undefined1 auVar2 [16];
  int iVar3;
  undefined1 (*pauVar4) [16];
  int iVar5;
  int iVar6;
  int iVar7;
  float fVar8;
  undefined1 in_vf0 [16];
  undefined1 auVar9 [16];
  undefined1 auVar10 [16];
  undefined1 auVar11 [16];
  undefined1 auStack_130 [8];
  undefined4 uStack_128;
  undefined4 uStack_124;
  undefined1 auStack_120 [8];
  undefined4 uStack_118;
  undefined4 uStack_114;
  undefined1 auStack_110 [8];
  undefined4 uStack_108;
  undefined4 uStack_104;
  undefined1 auStack_100 [8];
  undefined4 uStack_f8;
  undefined4 uStack_f4;
  float fStack_f0;
  float fStack_ec;
  float fStack_e8;
  undefined4 uStack_e4;
  float fStack_e0;
  float fStack_dc;
  float fStack_d8;
  undefined4 uStack_d4;
  float fStack_d0;
  float fStack_cc;
  float fStack_c8;
  undefined4 uStack_c4;
  float fStack_c0;
  float fStack_bc;
  float fStack_b8;
  undefined4 uStack_b4;
  undefined1 auStack_b0 [16];
  undefined1 auStack_a0 [16];
  undefined1 auStack_90 [16];
  undefined1 auStack_80 [16];
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
  undefined1 auStack_40 [48];
  undefined1 auStack_10 [16];
  
  Matrix::Matrix(auStack_40,CApp::camera + 0x240);
  FVector::FVector(&fStack_50,auStack_10);
  bVar1 = false;
  iVar7 = param_2->i32_1fc;
  if (((iVar7->f32_60 != 0.0) || (iVar7->f32_64 != 0.0)) ||
     (iVar7->f32_68 != 0.0)) {
    bVar1 = true;
  }
  for (iVar6 = 0; iVar6 < param_2->i32_1f8; iVar6 = iVar6 + 1) {
    FVector::FVector(&fStack_60,iVar7 + 0x30);
    fStack_70 = fStack_60 - fStack_50;
    fStack_6c = fStack_5c - fStack_4c;
    fStack_68 = fStack_58 - fStack_48;
    uStack_64 = 0x3f800000;
    fVar8 = (float)FVector::Length(&fStack_70);
    fVar8 = fVar8 / 300.0;
    FVector::Normalize(&fStack_70);
    FVector::__amu(this,&fStack_70);
    fStack_60 = fStack_60 - fStack_70;
    fStack_5c = fStack_5c - fStack_6c;
    fStack_58 = fStack_58 - fStack_68;
    uStack_54 = 0;
    fStack_f0 = fVar8 * (iVar7->f32_40 / 2.0) * iVar7->f32_50;
    fStack_ec = fVar8 * (iVar7->f32_44 / 2.0) * iVar7->f32_54;
    fStack_d8 = fVar8 * (iVar7->f32_48 / 2.0) * iVar7->f32_58;
    fStack_c0 = -fStack_f0;
    fStack_bc = -fStack_ec;
    uStack_b4 = 0x3f800000;
    iVar7->f32_70 = fStack_c0;
    iVar7->f32_74 = fStack_bc;
    iVar7->f32_78 = fStack_d8;
    iVar7->u32_7c = 0x3f800000;
    fStack_d0 = -fStack_f0;
    fStack_c8 = -fStack_d8;
    uStack_c4 = 0x3f800000;
    iVar7->f32_80 = fStack_d0;
    iVar7->f32_84 = fStack_ec;
    iVar7->f32_88 = fStack_c8;
    iVar7->u32_8c = 0x3f800000;
    fStack_dc = -fStack_ec;
    uStack_d4 = 0x3f800000;
    iVar7->f32_90 = fStack_f0;
    iVar7->f32_94 = fStack_dc;
    iVar7->f32_98 = fStack_d8;
    iVar7->u32_9c = 0x3f800000;
    fStack_e8 = -fStack_d8;
    uStack_e4 = 0x3f800000;
    iVar7->f32_a0 = fStack_f0;
    iVar7->f32_a4 = fStack_ec;
    iVar7->f32_a8 = fStack_e8;
    iVar7->u32_ac = 0x3f800000;
    fStack_e0 = fStack_f0;
    fStack_cc = fStack_ec;
    fStack_b8 = fStack_d8;
    if (bVar1) {
      auVar9 = _vmr32(in_vf0);
      auVar10 = _vmr32(auVar9);
      auVar11 = _vmr32(auVar10);
      auStack_80 = _sqc2(in_vf0);
      auStack_90 = _sqc2(auVar9);
      auStack_a0 = _sqc2(auVar10);
      auStack_b0 = _sqc2(auVar11);
      sceVu0RotMatrix(auStack_b0,auStack_b0,iVar7 + 0x60);
      if ((param_2->u8_14 & 1) == 0) {
        for (iVar5 = 0; iVar5 < 4; iVar5 = iVar5 + 1) {
          Matrix::ApplyMatrix(auStack_120,auStack_b0,iVar7 + iVar5 * 0x10 + 0x70);
          iVar3 = iVar7 + iVar5 * 0x10;
          iVar3->i32_70 = auStack_120._0_4_;
          iVar3->i32_74 = auStack_120._4_4_;
          iVar3->u32_78 = uStack_118;
          iVar3->u32_7c = uStack_114;
          pauVar4 = (undefined1 (*) [16])(iVar7 + iVar5 * 0x10 + 0x70);
          auVar11._4_4_ = fStack_5c;
          auVar11._0_4_ = fStack_60;
          auVar11._8_4_ = fStack_58;
          auVar11._12_4_ = uStack_54;
          auVar10 = _lqc2(auVar11);
          auVar9 = _lqc2(*pauVar4);
          auVar9 = _vadd(auVar9,auVar10);
          auVar9 = _sqc2(auVar9);
          *pauVar4 = auVar9;
        }
      }
      else {
        for (iVar5 = 0; iVar5 < 4; iVar5 = iVar5 + 1) {
          Matrix::ApplyMatrix(auStack_100,auStack_b0,iVar7 + iVar5 * 0x10 + 0x70);
          iVar3 = iVar7 + iVar5 * 0x10;
          iVar3->i32_70 = auStack_100._0_4_;
          iVar3->i32_74 = auStack_100._4_4_;
          iVar3->u32_78 = uStack_f8;
          iVar3->u32_7c = uStack_f4;
          Matrix::ApplyMatrix(auStack_110,0x4213c0,iVar7 + iVar5 * 0x10 + 0x70);
          iVar3 = iVar7 + iVar5 * 0x10;
          iVar3->i32_70 = auStack_110._0_4_;
          iVar3->i32_74 = auStack_110._4_4_;
          iVar3->u32_78 = uStack_108;
          iVar3->u32_7c = uStack_104;
          pauVar4 = (undefined1 (*) [16])(iVar7 + iVar5 * 0x10 + 0x70);
          auVar2._4_4_ = fStack_5c;
          auVar2._0_4_ = fStack_60;
          auVar2._8_4_ = fStack_58;
          auVar2._12_4_ = uStack_54;
          auVar10 = _lqc2(auVar2);
          auVar9 = _lqc2(*pauVar4);
          auVar9 = _vadd(auVar9,auVar10);
          auVar9 = _sqc2(auVar9);
          *pauVar4 = auVar9;
        }
      }
    }
    else if ((param_2->u8_14 & 1) == 0) {
      for (iVar5 = 0; iVar5 < 4; iVar5 = iVar5 + 1) {
        pauVar4 = (undefined1 (*) [16])(iVar7 + iVar5 * 0x10 + 0x70);
        auVar9._4_4_ = fStack_5c;
        auVar9._0_4_ = fStack_60;
        auVar9._8_4_ = fStack_58;
        auVar9._12_4_ = 0;
        auVar10 = _lqc2(auVar9);
        auVar9 = _lqc2(*pauVar4);
        auVar9 = _vadd(auVar9,auVar10);
        auVar9 = _sqc2(auVar9);
        *pauVar4 = auVar9;
      }
    }
    else {
      for (iVar5 = 0; iVar5 < 4; iVar5 = iVar5 + 1) {
        Matrix::ApplyMatrix(auStack_130,0x4213c0,iVar7 + iVar5 * 0x10 + 0x70);
        iVar3 = iVar7 + iVar5 * 0x10;
        iVar3->i32_70 = auStack_130._0_4_;
        iVar3->i32_74 = auStack_130._4_4_;
        iVar3->u32_78 = uStack_128;
        iVar3->u32_7c = uStack_124;
        pauVar4 = (undefined1 (*) [16])(iVar7 + iVar5 * 0x10 + 0x70);
        auVar10._4_4_ = fStack_5c;
        auVar10._0_4_ = fStack_60;
        auVar10._8_4_ = fStack_58;
        auVar10._12_4_ = uStack_54;
        auVar10 = _lqc2(auVar10);
        auVar9 = _lqc2(*pauVar4);
        auVar9 = _vadd(auVar9,auVar10);
        auVar9 = _sqc2(auVar9);
        *pauVar4 = auVar9;
      }
    }
    iVar7 = iVar7 + 0xf0;
  }
  return;
}

// JP: 0x002af9d0  SetPacket__16FpObjectSunFlareFv  =  FpObjectSunFlare::SetPacket
void FpObjectSunFlare::SetPacket(int this)

{
  int iVar1;
  int *piVar2;
  int in_zero_lo;
  int in_zero_hi;
  int in_zero_udw;
  int in_register_0000000c;
  int iVar3;
  float *pfVar4;
  int iVar5;
  int iVar6;
  float fVar7;
  uint uVar8;
  int iStack_60;
  int iStack_5c;
  int iStack_58;
  int iStack_54;
  uint *puStack_44;
  uint *puStack_40;
  float *pfStack_3c;
  float *pfStack_38;
  ulong *puStack_34;
  ulong *puStack_30;
  int *piStack_2c;
  float fStack_28;
  float fStack_24;
  float fStack_20;
  uint uStack_1c;
  float fStack_18;
  float fStack_14;
  int iStack_10;
  
  iVar1 = *(int *)(this->i32_8 + 0x70);
  piStack_2c = *(int **)(this + 0x88);
  *piStack_2c = in_zero_lo;
  piStack_2c[1] = in_zero_hi;
  piStack_2c[2] = in_zero_udw;
  piStack_2c[3] = in_register_0000000c;
  *piStack_2c = (int)(&DAT_10000001 + this->i32_1f8 * 0xc);
  piStack_2c[3] = this->i32_1f8 * 0xc + 1U | 0x50000000;
  this->i32_88 = this->i32_88 + 0x10;
  puStack_34 = *(ulong **)(this + 0x88);
  *puStack_34 = (long)(this->i32_1f8 << 2) | 0x302a400000008000;
  puStack_34[1] = 0x412;
  this->i32_88 = this->i32_88 + 0x10;
  pfVar4 = *(float **)(this + 0x88);
  iVar5 = this->i32_1fc;
  iStack_60 = in_zero_lo;
  iStack_5c = in_zero_hi;
  iStack_58 = in_zero_udw;
  iStack_54 = in_register_0000000c;
  pfStack_3c = pfVar4;
  pfStack_38 = pfVar4;
  puStack_30 = puStack_34;
  iStack_10 = this;
  for (iVar6 = 0; iVar6 < iStack_10->i32_1f8; iVar6 = iVar6 + 1) {
    iVar3 = rand();
    fStack_14 = (float)iVar3 / 2.1474836e+09;
    for (iVar3 = 0; iVar3 < 4; iVar3 = iVar3 + 1) {
      fStack_18 = (float)PutiObject::RotTransPer
                                   (iStack_10,iVar5 + iVar3 * 0x10 + 0x70,&iStack_60);
      uStack_1c = PutiObject::ClipFlag(iStack_10);
      *pfVar4 = *(float *)(iVar5 + iVar3 * 8 + 0xc0) * fStack_18;
      pfVar4[1] = *(float *)(iVar5 + iVar3 * 8 + 0xc4) * fStack_18;
      pfVar4[2] = fStack_18;
      iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
      puStack_44 = *(uint **)(iStack_10 + 0x88);
      fVar7 = iVar5->f32_b0;
      if (fVar7 < 2.1474836e+09) {
        uVar8 = (uint)fVar7;
      }
      else {
        uVar8 = (int)(fVar7 - 2.1474836e+09) | 0x80000000;
      }
      *puStack_44 = uVar8;
      fVar7 = iVar5->f32_b4;
      if (fVar7 < 2.1474836e+09) {
        uVar8 = (uint)fVar7;
      }
      else {
        uVar8 = (int)(fVar7 - 2.1474836e+09) | 0x80000000;
      }
      puStack_44[1] = uVar8;
      fVar7 = iVar5->f32_b8;
      if (fVar7 < 2.1474836e+09) {
        uVar8 = (uint)fVar7;
      }
      else {
        uVar8 = (int)(fVar7 - 2.1474836e+09) | 0x80000000;
      }
      puStack_44[2] = uVar8;
      fVar7 = iVar5->f32_bc;
      if (fVar7 < 2.1474836e+09) {
        uVar8 = (uint)fVar7;
      }
      else {
        uVar8 = (int)(fVar7 - 2.1474836e+09) | 0x80000000;
      }
      puStack_44[3] = uVar8;
      if (iVar1->i8_c8 == '\x01') {
        fVar7 = iVar5->f32_b0 * 2.0;
        if (fVar7 < 2.1474836e+09) {
          uVar8 = (uint)fVar7;
        }
        else {
          uVar8 = (int)(fVar7 - 2.1474836e+09) | 0x80000000;
        }
        *puStack_44 = uVar8;
        fVar7 = iVar5->f32_b4 * 2.0;
        if (fVar7 < 2.1474836e+09) {
          uVar8 = (uint)fVar7;
        }
        else {
          uVar8 = (int)(fVar7 - 2.1474836e+09) | 0x80000000;
        }
        puStack_44[1] = uVar8;
        fVar7 = iVar5->f32_bc * 2.0;
        if (fVar7 < 2.1474836e+09) {
          uVar8 = (uint)fVar7;
        }
        else {
          uVar8 = (int)(fVar7 - 2.1474836e+09) | 0x80000000;
        }
        puStack_44[3] = uVar8;
        if (iVar1->i8_a4 != '\0') {
          fVar7 = iVar5->f32_bc * 0.8;
          if (fVar7 < 2.1474836e+09) {
            uVar8 = (uint)fVar7;
          }
          else {
            uVar8 = (int)(fVar7 - 2.1474836e+09) | 0x80000000;
          }
          puStack_44[3] = uVar8;
        }
        if ((iVar1->f32_b0 < 40.0) || (70.0 < iVar1->f32_b0)) {
          if ((70.0 < iVar1->f32_b0) && (iVar1->f32_b0 < 120.0)) {
            fVar7 = iVar5->f32_bc * 2.0 * 0.4;
            if (fVar7 < 2.1474836e+09) {
              uVar8 = (uint)fVar7;
            }
            else {
              uVar8 = (int)(fVar7 - 2.1474836e+09) | 0x80000000;
            }
            puStack_44[3] = uVar8;
          }
        }
        else {
          fStack_20 = (70.0 - iVar1->f32_b0) / 50.0 + 0.4;
          fVar7 = iVar5->f32_bc * 2.0 * fStack_20;
          if (fVar7 < 2.1474836e+09) {
            uVar8 = (uint)fVar7;
          }
          else {
            uVar8 = (int)(fVar7 - 2.1474836e+09) | 0x80000000;
          }
          puStack_44[3] = uVar8;
        }
        if ((iVar1->f32_b0 < 190.0) || (200.0 < iVar1->f32_b0)) {
          if (200.0 < iVar1->f32_b0) {
            fVar7 = iVar5->f32_bc * 0.5;
            if (fVar7 < 2.1474836e+09) {
              uVar8 = (uint)fVar7;
            }
            else {
              uVar8 = (int)(fVar7 - 2.1474836e+09) | 0x80000000;
            }
            puStack_44[3] = uVar8;
          }
        }
        else {
          fStack_24 = (200.0 - iVar1->f32_b0) / 20.0 + 0.5;
          fVar7 = iVar5->f32_bc * fStack_24;
          if (fVar7 < 2.1474836e+09) {
            uVar8 = (uint)fVar7;
          }
          else {
            uVar8 = (int)(fVar7 - 2.1474836e+09) | 0x80000000;
          }
          puStack_44[3] = uVar8;
        }
      }
      else if (iVar1->i8_a4 == '\0') {
        fStack_28 = iVar5->f32_bc;
        if (iStack_10->i8_238 != '\0') {
          fStack_28 = fStack_28 * (fStack_14 * 0.15 + 0.85);
        }
        if (iStack_10->i8_239 == '\0') {
          fStack_28 = fStack_28 * iVar1->f32_a8;
        }
        if (fStack_28 < 2.1474836e+09) {
          uVar8 = (uint)fStack_28;
        }
        else {
          uVar8 = (int)(fStack_28 - 2.1474836e+09) | 0x80000000;
        }
        puStack_44[3] = uVar8;
      }
      else if (iStack_10->i8_239 == '\0') {
        puStack_44[3] = 0;
      }
      iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
      piVar2 = *(int **)(iStack_10 + 0x88);
      if ((iVar3 < 2) || ((uStack_1c & 0x3ffff) != 0)) {
        iStack_54 = 0x8000;
      }
      *piVar2 = iStack_60;
      piVar2[1] = iStack_5c;
      piVar2[2] = iStack_58;
      piVar2[3] = iStack_54;
      iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
      pfVar4 = *(float **)(iStack_10 + 0x88);
      puStack_40 = puStack_44;
    }
    iVar5 = iVar5 + 0xf0;
  }
  return;
}

// JP: 0x002b02f0  __ct__8FpFunsuiFv  =  FpFunsui::FpFunsui
undefined8 FpFunsui::FpFunsui(undefined8 this)

{
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  int this;
  
  FpPrim::FpPrim(this);
  
  *(undefined1 **)(this + 0x10) = FpFunsui::__vt;
  this->u32_1c = 0x406290;
  this->u32_70 = in_zero_lo;
  this->u32_74 = in_zero_hi;
  this->u32_78 = in_zero_udw;
  this->u32_7c = in_register_0000000c;
  this->u32_70 = 0;
  this->u32_74 = 0;
  this->u32_78 = 0;
  this->u32_7c = 0x3f800000;
  this->u32_80 = 0x3f7c1c61;
  this->u32_c0 = 0x3e31d0c8;
  this->u32_84 = 0x3f51b3f2;
  this->u32_c4 = 0x3f12d5e0;
  this->u32_88 = 0x3f12d5e0;
  this->u32_c8 = 0x3f51b3f2;
  this->u32_8c = 0x3e31d0c8;
  this->u32_cc = 0x3f7c1c61;
  this->u32_90 = 0xbe31d0c8;
  this->u32_d0 = 0x3f7c1c61;
  this->u32_94 = 0xbf12d5e0;
  this->u32_d4 = 0x3f51b3f2;
  this->u32_98 = 0xbf51b3f2;
  this->u32_d8 = 0x3f12d5e0;
  this->u32_9c = 0xbf7c1c61;
  this->u32_dc = 0x3e31d0c8;
  this->u32_a0 = 0xbf7c1c61;
  this->u32_e0 = 0xbe31d0c8;
  this->u32_a4 = 0xbf51b3f2;
  this->u32_e4 = 0xbf12d5e0;
  this->u32_a8 = 0xbf12d5e0;
  this->u32_e8 = 0xbf51b3f2;
  this->u32_ac = 0xbe31d0c8;
  this->u32_ec = 0xbf7c1c61;
  this->u32_b0 = 0x3e31d0c8;
  this->u32_f0 = 0xbf7c1c61;
  this->u32_b4 = 0x3f12d5e0;
  this->u32_f4 = 0xbf51b3f2;
  this->u32_b8 = 0x3f51b3f2;
  this->u32_f8 = 0xbf12d5e0;
  this->u32_bc = 0x3f7c1c61;
  this->u32_fc = 0xbe31d0c8;
  return this;
}

// JP: 0x002b0610  __dt__8FpFunsuiFv  =  FpFunsui::~FpFunsui
int FpFunsui::~FpFunsui(int this,short param_2)

{
  if (this != 0) {
    *(undefined1 **)(this + 0x10) = FpFunsui::__vt;
    this->u32_1c = 0x406290;
    FpPrim::~FpPrim(this,0);
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}

// JP: 0x002b06a0  Create__8FpFunsuiF7FVector  =  FpFunsui::Create
void FpFunsui::Create(undefined8 this,undefined8 *param_2)

{
  long lVar1;
  undefined8 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  int this;
  
  
  uVar2 = *param_2;
  uVar3 = param_2->u32_1;
  uVar4 = *(undefined4 *)((int)param_2 + 0xc);
  this->i32_70 = (int)uVar2;
  this->i32_74 = (int)((ulong)uVar2 >> 0x20);
  this->u32_78 = uVar3;
  this->u32_7c = uVar4;
  iVar5 = BgEffectMan::eff->i32_1c + 0x78;
  SetWhiteTex(iVar5);
  PutiPrim::SetTexture(this,iVar5,0);
  if (this->i8_58 == '\0') {
    this->u8_24 = this->u8_24 & 0xfe | 1;
  }
  lVar1 = __nw(0x210);
  uVar2 = 0;
  if (lVar1 != 0) {
    uVar2 = FpObjectFunsui::FpObjectFunsui(lVar1,0x254,0);
  }
  PutiPrim::AddObject(this,uVar2);
  (**(code **)(*(int *)((int)uVar2 + 0x1e4) + 0x40))(uVar2,0x30,this->u8_58);
  PutiManager::AddPrim(BgEffectMan::eff,this->u32_54,this);
  return;
}

// JP: 0x002b07c0  Create__8FpFunsuiFPv  =  FpFunsui::Create
void FpFunsui::Create(undefined4 this,undefined4 param_2)

{
  undefined8 uVar1;
  undefined1 auStack_40 [16];
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_10;
  
  uStack_30 = 0xc13849ba;
  uStack_2c = 0xc0cfae14;
  uStack_28 = 0x4115c28f;
  uStack_24 = 0x3f800000;
  uStack_20 = this;
  uStack_10 = param_2;
  uVar1 = FVector::FVector(auStack_40,&uStack_30);
  FpFunsui::Create(uStack_20,uVar1);
  return;
}

// JP: 0x002b0860  __ct__14FpObjectFunsuiFiPv  =  FpObjectFunsui::FpObjectFunsui
int FpObjectFunsui::FpObjectFunsui(int this,undefined4 param_2,undefined4 param_3)

{
  FpObject::FpObject(this,param_2,param_3);
  *(undefined1 **)(this + 0x1e4) = FpObjectFunsui::__vt;
  return this;
}

// JP: 0x002b08b0  __dt__14FpObjectFunsuiFv  =  FpObjectFunsui::~FpObjectFunsui
int FpObjectFunsui::~FpObjectFunsui(int this,short param_2)

{
  if (this != 0) {
    *(undefined1 **)(this + 0x1e4) = FpObjectFunsui::__vt;
    FpObject::~FpObject(this,0);
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}

// JP: 0x002b0930  CreateData__14FpObjectFunsuiFib  =  FpObjectFunsui::CreateData
void FpObjectFunsui::CreateData(int this,uint param_2,long param_3)

{
  undefined8 uVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int iVar6;
  uint uVar7;
  undefined4 *puVar8;
  float fVar9;
  
  iVar3 = this->i32_8;
  puVar8 = (undefined4 *)(this->i32_1fc + param_2 * 0xf0);
  if (param_3 == 0) {
    puVar8[1] = 0;
  }
  else {
    uVar7 = param_2 & 0xf;
    if (((int)param_2 < 0) && (uVar7 != 0)) {
      uVar7 = uVar7 - 0x10;
    }
    uVar2 = param_2;
    if ((int)param_2 < 0) {
      uVar2 = param_2 + 0xf;
    }
    iVar6 = (int)uVar2 >> 4;
    switch(uVar7) {
    case 0:
      puVar8[1] = (float)(iVar6 * -0x14);
      break;
    case 1:
      puVar8[1] = (float)(iVar6 * -0x14 + 8);
      break;
    case 2:
      puVar8[1] = (float)(iVar6 * -0x14 + 0xc);
      break;
    case 3:
      puVar8[1] = (float)(iVar6 * -0x14 + 4);
      break;
    case 4:
      puVar8[1] = (float)(iVar6 * -0x14 + 9);
      break;
    case 5:
      puVar8[1] = (float)(iVar6 * -0x14 + 1);
      break;
    case 6:
      puVar8[1] = (float)(iVar6 * -0x14 + 5);
      break;
    case 7:
      puVar8[1] = (float)(iVar6 * -0x14 + 0xd);
      break;
    case 8:
      puVar8[1] = (float)(iVar6 * -0x14 + 10);
      break;
    case 9:
      puVar8[1] = (float)(iVar6 * -0x14 + 0xe);
      break;
    case 10:
      puVar8[1] = (float)(iVar6 * -0x14 + 2);
      break;
    case 0xb:
      puVar8[1] = (float)(iVar6 * -0x14 + 6);
      break;
    case 0xc:
      puVar8[1] = (float)(iVar6 * -0x14 + 0xf);
      break;
    case 0xd:
      puVar8[1] = (float)(iVar6 * -0x14 + 0xb);
      break;
    case 0xe:
      puVar8[1] = (float)(iVar6 * -0x14 + 3);
      break;
    case 0xf:
      puVar8[1] = (float)(iVar6 * -0x14 + 7);
    }
    puVar8[1] = (float)puVar8[1] + 40.0;
    *puVar8 = 0x42700000;
    puVar8[2] = 0;
    puVar8[0x10] = 0x41c00000;
    puVar8[0x11] = 0x41c00000;
    puVar8[0x12] = 0;
    puVar8[0x13] = 0x3f800000;
    puVar8[0x1c] = 0;
    puVar8[0x1d] = 0;
    puVar8[0x1e] = 0;
    puVar8[0x1f] = 0x3f800000;
    puVar8[0x20] = 0;
    puVar8[0x21] = 0;
    puVar8[0x22] = 0;
    puVar8[0x23] = 0x3f800000;
    puVar8[0x24] = 0;
    puVar8[0x25] = 0;
    puVar8[0x26] = 0;
    puVar8[0x27] = 0x3f800000;
    puVar8[0x28] = 0;
    puVar8[0x29] = 0;
    puVar8[0x2a] = 0;
    puVar8[0x2b] = 0x3f800000;
    puVar8[4] = 0;
    puVar8[5] = 0;
    puVar8[6] = 0;
    puVar8[7] = 0x3f800000;
    puVar8[0x18] = 0;
    puVar8[0x19] = 0;
    puVar8[0x1a] = 0;
    puVar8[0x1b] = 0x3f800000;
    puVar8[0x2c] = 0x43000000;
    puVar8[0x2d] = 0x42e60000;
    puVar8[0x2e] = 0x42dc0000;
    puVar8[0x2f] = 0;
    puVar8[0x30] = 0;
    puVar8[0x31] = 0;
    puVar8[0x32] = 0;
    puVar8[0x33] = 0x3f800000;
    puVar8[0x34] = 0x3f800000;
    puVar8[0x35] = 0;
    puVar8[0x36] = 0x3f800000;
    puVar8[0x37] = 0x3f800000;
  }
  uVar1 = iVar3->u64_70;
  uVar4 = iVar3->u32_78;
  uVar5 = iVar3->u32_7c;
  puVar8[0xc] = (int)uVar1;
  puVar8[0xd] = (int)((ulong)uVar1 >> 0x20);
  puVar8[0xe] = uVar4;
  puVar8[0xf] = uVar5;
  iVar6 = rand();
  uVar7 = param_2 & 0xf;
  if (((int)param_2 < 0) && (uVar7 != 0)) {
    uVar7 = uVar7 - 0x10;
  }
  puVar8[0xc] = (float)puVar8[0xc] +
                *(float *)(iVar3 + uVar7 * 4 + 0x80) * 19.0 +
                ((float)iVar6 / 2.1474836e+09 - 0.5) * 5.0;
  iVar6 = rand();
  uVar7 = param_2 & 0xf;
  if (((int)param_2 < 0) && (uVar7 != 0)) {
    uVar7 = uVar7 - 0x10;
  }
  puVar8[0xe] = (float)puVar8[0xe] +
                *(float *)(iVar3 + uVar7 * 4 + 0xc0) * 19.0 +
                ((float)iVar6 / 2.1474836e+09 - 0.5) * 5.0;
  iVar3 = rand();
  fVar9 = ((float)iVar3 * 0.5) / 2.1474836e+09 + 0.75;
  puVar8[0x14] = fVar9;
  puVar8[0x15] = fVar9;
  puVar8[0x16] = fVar9;
  puVar8[0x17] = 0x3f800000;
  return;
}

// JP: 0x002b1130  Init__14FpObjectFunsuiFib  =  FpObjectFunsui::Init
void FpObjectFunsui::Init(int this,undefined4 param_2,char param_3)

{
  undefined4 uVar1;
  undefined8 uVar2;
  int iVar3;
  
  this->u32_1f8 = param_2;
  this->u32_1f4 = param_2;
  iVar3 = this->i32_1f8;
  uVar2 = __nwa(iVar3 * 0xf0 + 0x10);
  uVar1 = __construct_new_array(uVar2,0x299b50,0,0xf0,iVar3);
  this->u32_1fc = uVar1;
  memset(*(void **)(this + 0x1fc),0,(long)(this->i32_1f8 * 0xf0));
  for (iVar3 = 0; iVar3 < this->i32_1f8; iVar3 = iVar3 + 1) {
    (**(code **)(this->i32_1e4 + 0x4c))(this,iVar3,1);
  }
  this->u32_1e0 = 0xffffffff;
  this->u8_14 = this->u8_14 & 0xfe | 1;
  this->u16_14 = this->u16_14 & 0xe01f;
  if (param_3 == '\0') {
    PutiObject::SetRegTest(this,0x33001);
  }
  else {
    PutiObject::SetRegTest(this,0x73001);
  }
  PutiObject::SetRegAlpha(this,0x44);
  return;
}

// JP: 0x002b12e0  CalculateFunc__14FpObjectFunsuiFv  =  FpObjectFunsui::CalculateFunc
void FpObjectFunsui::CalculateFunc(int this)

{
  float *pfVar1;
  int iVar2;
  float fStack_14;
  
  pfVar1 = *(float **)(this + 0x1fc);
  for (iVar2 = 0; iVar2 < this->i32_1f8; iVar2 = iVar2 + 1) {
    pfVar1[1] = pfVar1[1] + 1.0;
    if (*pfVar1 <= pfVar1[1]) {
      (**(code **)(this->i32_1e4 + 0x4c))(this,iVar2,0);
    }
    pfVar1[0x2f] = 10.0;
    if (pfVar1[1] < 15.0) {
      fStack_14 = 0.0;
      if (0.0 < pfVar1[1]) {
        fStack_14 = pfVar1[1] / 15.0;
      }
      pfVar1[0x2f] = pfVar1[0x2f] * fStack_14;
    }
    else if (40.0 < pfVar1[1]) {
      pfVar1[0x2f] = pfVar1[0x2f] * ((*pfVar1 - pfVar1[1]) / 20.0);
    }
    pfVar1 = pfVar1 + 0x3c;
  }
  (**(code **)(this->i32_1e4 + 0x44))();
  return;
}

// JP: 0x002b1470  SetPacket__14FpObjectFunsuiFv  =  FpObjectFunsui::SetPacket
void FpObjectFunsui::SetPacket(int this)

{
  int *piVar1;
  int in_zero_lo;
  int in_zero_hi;
  int in_zero_udw;
  int in_register_0000000c;
  float *pfVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  float fVar6;
  uint uVar7;
  int iStack_40;
  int iStack_3c;
  int iStack_38;
  int iStack_34;
  uint *puStack_30;
  float *pfStack_2c;
  float *pfStack_28;
  ulong *puStack_24;
  ulong *puStack_20;
  int *piStack_1c;
  uint uStack_18;
  float fStack_14;
  int iStack_10;
  
  piStack_1c = *(int **)(this + 0x88);
  *piStack_1c = in_zero_lo;
  piStack_1c[1] = in_zero_hi;
  piStack_1c[2] = in_zero_udw;
  piStack_1c[3] = in_register_0000000c;
  *piStack_1c = (int)(&DAT_10000001 + this->i32_1f8 * 0xc);
  piStack_1c[3] = this->i32_1f8 * 0xc + 1U | 0x50000000;
  this->i32_88 = this->i32_88 + 0x10;
  puStack_24 = *(ulong **)(this + 0x88);
  *puStack_24 = (long)(this->i32_1f8 << 2) | 0x302a400000008000;
  puStack_24[1] = 0x412;
  this->i32_88 = this->i32_88 + 0x10;
  pfVar2 = *(float **)(this + 0x88);
  iVar3 = this->i32_1fc;
  iStack_40 = in_zero_lo;
  iStack_3c = in_zero_hi;
  iStack_38 = in_zero_udw;
  iStack_34 = in_register_0000000c;
  pfStack_2c = pfVar2;
  pfStack_28 = pfVar2;
  puStack_20 = puStack_24;
  iStack_10 = this;
  for (iVar5 = 0; iVar5 < iStack_10->i32_1f8; iVar5 = iVar5 + 1) {
    for (iVar4 = 0; iVar4 < 4; iVar4 = iVar4 + 1) {
      fStack_14 = (float)PutiObject::RotTransPer
                                   (iStack_10,iVar3 + iVar4 * 0x10 + 0x70,&iStack_40);
      uStack_18 = PutiObject::ClipFlag(iStack_10);
      *pfVar2 = *(float *)(iVar3 + iVar4 * 8 + 0xc0) * fStack_14;
      pfVar2[1] = *(float *)(iVar3 + iVar4 * 8 + 0xc4) * fStack_14;
      pfVar2[2] = fStack_14;
      iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
      puStack_30 = *(uint **)(iStack_10 + 0x88);
      fVar6 = iVar3->f32_b0;
      if (fVar6 < 2.1474836e+09) {
        uVar7 = (uint)fVar6;
      }
      else {
        uVar7 = (int)(fVar6 - 2.1474836e+09) | 0x80000000;
      }
      *puStack_30 = uVar7;
      fVar6 = iVar3->f32_b4;
      if (fVar6 < 2.1474836e+09) {
        uVar7 = (uint)fVar6;
      }
      else {
        uVar7 = (int)(fVar6 - 2.1474836e+09) | 0x80000000;
      }
      puStack_30[1] = uVar7;
      fVar6 = iVar3->f32_b8;
      if (fVar6 < 2.1474836e+09) {
        uVar7 = (uint)fVar6;
      }
      else {
        uVar7 = (int)(fVar6 - 2.1474836e+09) | 0x80000000;
      }
      puStack_30[2] = uVar7;
      fVar6 = iVar3->f32_bc;
      if (fVar6 < 2.1474836e+09) {
        uVar7 = (uint)fVar6;
      }
      else {
        uVar7 = (int)(fVar6 - 2.1474836e+09) | 0x80000000;
      }
      puStack_30[3] = uVar7;
      iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
      piVar1 = *(int **)(iStack_10 + 0x88);
      if ((iVar4 < 2) || ((uStack_18 & 0x3ffff) != 0)) {
        iStack_34 = 0x8000;
      }
      *piVar1 = iStack_40;
      piVar1[1] = iStack_3c;
      piVar1[2] = iStack_38;
      piVar1[3] = iStack_34;
      iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
      pfVar2 = *(float **)(iStack_10 + 0x88);
    }
    iVar3 = iVar3 + 0xf0;
  }
  return;
}

// JP: 0x002b1850  __ct__9FpThunderFv  =  FpThunder::FpThunder
int FpThunder::FpThunder(int this)

{
  FpPrim::FpPrim(this);
  *(undefined1 **)(this + 0x10) = FpThunder::__vt;
  this->u32_1c = 0x406380;
  return this;
}

// JP: 0x002b18a0  __dt__9FpThunderFv  =  FpThunder::~FpThunder
int FpThunder::~FpThunder(int this,short param_2)

{
  if (this != 0) {
    *(undefined1 **)(this + 0x10) = FpThunder::__vt;
    this->u32_1c = 0x406380;
    FpPrim::~FpPrim(this,0);
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}

// JP: 0x002b1930  CreateEffect__9FpThunderFP14FpThunderParam  =  FpThunder::CreateEffect
void FpThunder::CreateEffect(undefined4 this,int param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  undefined1 auStack_40 [16];
  undefined1 auStack_30 [16];
  undefined4 uStack_20;
  int iStack_10;
  
  uStack_20 = this;
  iStack_10 = param_2;
  uVar1 = FVector::FVector(auStack_30,param_2);
  uVar2 = FVector::FVector(auStack_40,iStack_10 + 0x10);
  FpThunder::Create
            (iStack_10->u32_28,iStack_10->u32_2c,
             iStack_10->u32_30,uStack_20,uVar1,uVar2,
             iStack_10->u32_20,iStack_10->u32_24,
             iStack_10->u32_34,(iStack_10->u8_38 & 1) != 0);
  return;
}

// JP: 0x002b19f0  Create__9FpThunderF7FVector7FVector7_rgba327_rgba32fffib  =  FpThunder::Create
void FpThunder::Create
               (undefined4 this,undefined4 param_2,undefined4 param_3,int param_4,
               undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,
               int param_9,undefined1 param_10)

{
  long lVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  int iVar5;
  undefined1 auStack_c0 [16];
  undefined1 auStack_b0 [16];
  int iStack_a0;
  undefined4 uStack_90;
  undefined4 uStack_80;
  undefined4 uStack_70;
  undefined4 uStack_60;
  undefined4 uStack_50;
  undefined4 uStack_40;
  undefined4 uStack_30;
  int iStack_20;
  undefined1 uStack_10;
  
  iVar5 = BgEffectMan::eff->i32_1c + 0xdc;
  iStack_a0 = param_4;
  uStack_90 = param_5;
  uStack_80 = param_6;
  uStack_70 = param_7;
  uStack_60 = param_8;
  uStack_50 = this;
  uStack_40 = param_2;
  uStack_30 = param_3;
  iStack_20 = param_9;
  uStack_10 = param_10;
  SetWhiteTex(iVar5);
  PutiPrim::SetTexture(iStack_a0,iVar5,0);
  if (iStack_a0->i8_58 == '\0') {
    iStack_a0->u8_24 = iStack_a0->u8_24 & 0xfe | 1;
  }
  iVar5 = iStack_20 * 0xc;
  lVar1 = __nw(0x330);
  uVar2 = 0;
  if (lVar1 != 0) {
    uVar2 = FpObjectThunder::FpObjectThunder(lVar1,iVar5 + 0x14,0);
  }
  PutiPrim::AddObject(iStack_a0,uVar2);
  uVar3 = FVector::FVector(auStack_b0,uStack_90);
  uVar4 = FVector::FVector(auStack_c0,uStack_80);
  FpObjectThunder::InitData
            (uStack_50,uStack_40,uStack_30,uVar2,uVar3,uVar4,uStack_70,uStack_60,iStack_20,uStack_10
             ,iStack_a0->u8_58);
  PutiManager::AddPrim(BgEffectMan::eff,iStack_a0->u32_54,iStack_a0)
  ;
  return;
}

// JP: 0x002b1b90  ChangeForm__9FpThunderFf  =  FpThunder::ChangeForm
void FpThunder::ChangeForm(undefined4 this,int param_2)

{
  FpObjectThunder::ChangeForm(this,param_2->u32_28);
  return;
}

// JP: 0x002b1bd0  SetPos__9FpThunderF7FVector7FVector  =  FpThunder::SetPos
void FpThunder::SetPos
               (int this,undefined1 (*param_2) [16],undefined1 (*param_3) [16])

{
  int iVar1;
  undefined8 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined1 auVar5 [16];
  undefined1 auVar6 [16];
  undefined1 auStack_20 [16];
  undefined1 auStack_10 [8];
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  iVar1 = this->i32_28;
  uVar2 = *(undefined8 *)*param_2;
  uVar3 = *(undefined4 *)(*param_2 + 8);
  uVar4 = *(undefined4 *)(*param_2 + 0xc);
  iVar1->i32_210 = (int)uVar2;
  iVar1->i32_214 = (int)((ulong)uVar2 >> 0x20);
  iVar1->u32_218 = uVar3;
  iVar1->u32_21c = uVar4;
  auVar5 = _lqc2(*param_3);
  auVar6 = _lqc2(*param_2);
  auVar5 = _vsub(auVar5,auVar6);
  auStack_20 = _sqc2(auVar5);
  FVector::FVector(auStack_10,auStack_20);
  iVar1->i32_220 = auStack_10._0_4_;
  iVar1->i32_224 = auStack_10._4_4_;
  iVar1->u32_228 = uStack_8;
  iVar1->u32_22c = uStack_4;
  return;
}

// JP: 0x002b1c40  __ct__15FpObjectThunderFiPv  =  FpObjectThunder::FpObjectThunder
undefined8 FpObjectThunder::FpObjectThunder(undefined8 this)

{
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  undefined4 *puVar1;
  int this;
  
  FpObject::FpObject(this);
  
  *(undefined1 **)(this + 0x1e4) = FpObjectThunder::__vt;
  this->u32_210 = in_zero_lo;
  this->u32_214 = in_zero_hi;
  this->u32_218 = in_zero_udw;
  this->u32_21c = in_register_0000000c;
  this->u32_220 = in_zero_lo;
  this->u32_224 = in_zero_hi;
  this->u32_228 = in_zero_udw;
  this->u32_22c = in_register_0000000c;
  puVar1 = (undefined4 *)(this + 0x230);
  do {
    *puVar1 = in_zero_lo;
    puVar1[1] = in_zero_hi;
    puVar1[2] = in_zero_udw;
    puVar1[3] = in_register_0000000c;
    puVar1 = puVar1 + 4;
  } while (puVar1 != (undefined4 *)(this + 0x270));
  this->u32_270 = in_zero_lo;
  this->u32_274 = in_zero_hi;
  this->u32_278 = in_zero_udw;
  this->u32_27c = in_register_0000000c;
  this->u32_280 = in_zero_lo;
  this->u32_284 = in_zero_hi;
  this->u32_288 = in_zero_udw;
  this->u32_28c = in_register_0000000c;
  this->u32_290 = in_zero_lo;
  this->u32_294 = in_zero_hi;
  this->u32_298 = in_zero_udw;
  this->u32_29c = in_register_0000000c;
  this->u32_2a0 = in_zero_lo;
  this->u32_2a4 = in_zero_hi;
  this->u32_2a8 = in_zero_udw;
  this->u32_2ac = in_register_0000000c;
  this->u32_2b0 = in_zero_lo;
  this->u32_2b4 = in_zero_hi;
  this->u32_2b8 = in_zero_udw;
  this->u32_2bc = in_register_0000000c;
  this->u32_2d0 = in_zero_lo;
  this->u32_2d4 = in_zero_hi;
  this->u32_2d8 = in_zero_udw;
  this->u32_2dc = in_register_0000000c;
  this->u32_2e0 = in_zero_lo;
  this->u32_2e4 = in_zero_hi;
  this->u32_2e8 = in_zero_udw;
  this->u32_2ec = in_register_0000000c;
  this->u32_300 = in_zero_lo;
  this->u32_304 = in_zero_hi;
  this->u32_308 = in_zero_udw;
  this->u32_30c = in_register_0000000c;
  this->u32_320 = in_zero_lo;
  this->u32_324 = in_zero_hi;
  this->u32_328 = in_zero_udw;
  this->u32_32c = in_register_0000000c;
  this->u32_2f4 = 0;
  this->u32_300 = in_zero_lo;
  this->u32_304 = in_zero_hi;
  this->u32_308 = in_zero_udw;
  this->u32_30c = in_register_0000000c;
  this->u32_310 = 0;
  this->u32_320 = in_zero_lo;
  this->u32_324 = in_zero_hi;
  this->u32_328 = in_zero_udw;
  this->u32_32c = in_register_0000000c;
  return this;
}

// JP: 0x002b1d00  __dt__15FpObjectThunderFv  =  FpObjectThunder::~FpObjectThunder
int FpObjectThunder::~FpObjectThunder(int this,short param_2)

{
  if (this != 0) {
    *(undefined1 **)(this + 0x1e4) = FpObjectThunder::__vt;
    FpObject::~FpObject(this,0);
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}

// JP: 0x002b1d80  Init__15FpObjectThunderFib  =  FpObjectThunder::Init
void FpObjectThunder::Init(void)

{
  return;
}

// JP: 0x002b1d90  InitData__15FpObjectThunderF7FVector7FVector7_rgba327_rgba32fffibb  =  FpObjectThunder::InitData
/* WARNING: Removing unreachable block (ram,0x002b20fc) */
/* WARNING: Removing unreachable block (ram,0x002b2064) */
/* WARNING: Removing unreachable block (ram,0x002b1fac) */
/* WARNING: Removing unreachable block (ram,0x002b1f14) */
/* WARNING: Removing unreachable block (ram,0x002b1f60) */
/* WARNING: Removing unreachable block (ram,0x002b1ff8) */
/* WARNING: Removing unreachable block (ram,0x002b20b0) */
/* WARNING: Removing unreachable block (ram,0x002b2148) */

void FpObjectThunder::InitData
               (undefined4 this,undefined4 param_2,undefined4 param_3,undefined8 param_4,
               undefined1 (*param_5) [16],undefined1 (*param_6) [16],uint param_7,uint param_8,
               long param_9,undefined1 param_10,long param_11)

{
  int iVar1;
  undefined4 uVar2;
  undefined8 uVar3;
  undefined4 uVar4;
  int iVar5;
  float fVar6;
  float fVar7;
  undefined1 in_vf0 [16];
  undefined1 auVar8 [16];
  undefined1 auVar9 [16];
  undefined1 auStack_b0 [16];
  undefined1 auStack_a0 [16];
  undefined1 auStack_90 [8];
  undefined4 uStack_88;
  undefined4 uStack_84;
  undefined1 auStack_80 [8];
  undefined4 uStack_78;
  undefined4 uStack_74;
  float fStack_70;
  float fStack_6c;
  float fStack_68;
  float fStack_64;
  float fStack_60;
  float fStack_5c;
  float fStack_58;
  float fStack_54;
  undefined1 auStack_50 [8];
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined1 auStack_40 [40];
  undefined4 uStack_18;
  undefined4 uStack_14;
  
  iVar1 = (int)param_9;
  if (param_9 < 0) {
    iVar1 = iVar1 + 1;
  }
  iVar1 = (iVar1 >> 1) << 1;
  iVar5 = (int)param_4;
  iVar5->i32_1f4 = iVar1;
  iVar5->i32_1f8 = iVar1;
  iVar1 = iVar5->i32_1f8;
  uVar3 = __nwa(iVar1 * 0xf0 + 0x10);
  uVar2 = __construct_new_array(uVar3,0x299b50,0,0xf0,iVar1);
  iVar5->u32_1fc = uVar2;
  memset(*(void **)(iVar5 + 0x1fc),0,(long)(iVar5->i32_1f8 * 0xf0));
  iVar5->u8_2f0 = param_10;
  *(undefined4 *)(*param_5 + 0xc) = 0x3f800000;
  *(undefined4 *)(*param_6 + 0xc) = 0x3f800000;
  uVar3 = *(undefined8 *)*param_5;
  uVar2 = *(undefined4 *)(*param_5 + 8);
  uVar4 = *(undefined4 *)(*param_5 + 0xc);
  iVar5->i32_210 = (int)uVar3;
  iVar5->i32_214 = (int)((ulong)uVar3 >> 0x20);
  iVar5->u32_218 = uVar2;
  iVar5->u32_21c = uVar4;
  auVar8 = _lqc2(*param_6);
  auVar9 = _lqc2(*param_5);
  auVar8 = _vsub(auVar8,auVar9);
  auStack_a0 = _sqc2(auVar8);
  FVector::FVector(auStack_50,auStack_a0);
  iVar5->i32_220 = auStack_50._0_4_;
  iVar5->i32_224 = auStack_50._4_4_;
  iVar5->u32_228 = uStack_48;
  iVar5->u32_22c = uStack_44;
  uVar3 = *(undefined8 *)*param_5;
  uVar2 = *(undefined4 *)(*param_5 + 8);
  uVar4 = *(undefined4 *)(*param_5 + 0xc);
  iVar5->i32_280 = (int)uVar3;
  iVar5->i32_284 = (int)((ulong)uVar3 >> 0x20);
  iVar5->u32_288 = uVar2;
  iVar5->u32_28c = uVar4;
  uVar3 = *(undefined8 *)*param_6;
  uVar2 = *(undefined4 *)(*param_6 + 8);
  uVar4 = *(undefined4 *)(*param_6 + 0xc);
  iVar5->i32_290 = (int)uVar3;
  iVar5->i32_294 = (int)((ulong)uVar3 >> 0x20);
  iVar5->u32_298 = uVar2;
  iVar5->u32_29c = uVar4;
  fStack_54 = (float)(param_7 >> 0x18) * 0.5019608;
  fStack_58 = (float)(param_7 >> 0x10 & 0xff) * 0.5019608;
  fStack_5c = (float)(param_7 >> 8 & 0xff) * 0.5019608;
  fStack_60 = (float)(param_7 & 0xff) * 0.5019608;
  iVar5->f32_2a0 = fStack_60;
  iVar5->f32_2a4 = fStack_5c;
  iVar5->f32_2a8 = fStack_58;
  iVar5->f32_2ac = fStack_54;
  fStack_64 = (float)(param_8 >> 0x18) * 0.5019608;
  fStack_68 = (float)(param_8 >> 0x10 & 0xff) * 0.5019608;
  fStack_6c = (float)(param_8 >> 8 & 0xff) * 0.5019608;
  fStack_70 = (float)(param_8 & 0xff) * 0.5019608;
  iVar5->f32_2b0 = fStack_70;
  iVar5->f32_2b4 = fStack_6c;
  iVar5->f32_2b8 = fStack_68;
  iVar5->f32_2bc = fStack_64;
  iVar5->u32_2c0 = this;
  iVar5->u32_2c4 = param_2;
  iVar5->u32_2c8 = param_3;
  Matrix::Matrix(auStack_40,CApp::camera + 0x240);
  iVar5->i32_270 = (int)auStack_40._32_8_;
  iVar5->i32_274 = SUB84(auStack_40._32_8_,4);
  iVar5->u32_278 = uStack_18;
  iVar5->u32_27c = uStack_14;
  auVar8 = _qmtc2((float)iVar5->i32_1f4);
  _vdiv(in_vf0,0,auVar8,0);
  auVar8 = _lqc2(*(undefined1 (*) [16])(iVar5 + 0x220));
  uVar2 = _vwaitq();
  auVar8 = _vmulq(auVar8,uVar2);
  auStack_b0 = _sqc2(auVar8);
  FVector::FVector(auStack_80,auStack_b0);
  iVar5->i32_2d0 = auStack_80._0_4_;
  iVar5->i32_2d4 = auStack_80._4_4_;
  iVar5->u32_2d8 = uStack_78;
  iVar5->u32_2dc = uStack_74;
  FVector::OuterProduct(auStack_90,iVar5 + 0x220,iVar5 + 0x270);
  iVar5->i32_2e0 = auStack_90._0_4_;
  iVar5->i32_2e4 = auStack_90._4_4_;
  iVar5->u32_2e8 = uStack_88;
  iVar5->u32_2ec = uStack_84;
  FVector::Normalize(iVar5 + 0x2e0);
  fVar6 = (float)FVector::Length(iVar5 + 0x2d0);
  fVar7 = (float)GetRad(iVar5->u32_2c8);
  fVar7 = sinf(fVar7);
  FVector::__amu(fVar6 * fVar7,iVar5 + 0x2e0);
  for (iVar1 = 0; iVar1 < iVar5->i32_1f8; iVar1 = iVar1 + 1) {
    (**(code **)(iVar5->i32_1e4 + 0x4c))(param_4,iVar1,1);
  }
  FpObjectThunder::CreateVertex(param_4);
  iVar5->u32_1e0 = 0xffffffff;
  iVar5->u16_14 = iVar5->u16_14 & 0xe01f;
  if (param_11 == 0) {
    PutiObject::SetRegTest(param_4,0x33001);
  }
  else {
    PutiObject::SetRegTest(param_4,0x73001);
  }
  return;
}

// JP: 0x002b2360  CreateData__15FpObjectThunderFib  =  FpObjectThunder::CreateData
void FpObjectThunder::CreateData(int this,uint param_2,long param_3)

{
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  uint uVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined1 auVar5 [16];
  undefined1 auVar6 [16];
  undefined1 auStack_150 [16];
  undefined1 auStack_140 [16];
  undefined1 auStack_130 [16];
  undefined1 auStack_120 [16];
  undefined1 auStack_110 [16];
  undefined1 auStack_100 [16];
  undefined1 auStack_f0 [16];
  undefined1 auStack_e0 [16];
  undefined1 auStack_d0 [8];
  undefined4 uStack_c8;
  undefined4 uStack_c4;
  undefined1 auStack_c0 [16];
  undefined1 auStack_b0 [8];
  undefined4 uStack_a8;
  undefined4 uStack_a4;
  undefined1 auStack_a0 [8];
  undefined4 uStack_98;
  undefined4 uStack_94;
  undefined1 auStack_90 [8];
  undefined4 uStack_88;
  undefined4 uStack_84;
  undefined1 auStack_80 [8];
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined1 auStack_70 [16];
  undefined1 auStack_60 [8];
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  
  puVar4 = (undefined4 *)(this->i32_1fc + param_2 * 0xf0);
  if (param_3 != 0) {
    *puVar4 = 0x3f800000;
    puVar4[1] = 0;
    puVar4[8] = in_zero_lo;
    puVar4[9] = in_zero_hi;
    puVar4[10] = in_zero_udw;
    puVar4[0xb] = in_register_0000000c;
    uStack_20 = 0;
    uStack_1c = 0;
    uStack_18 = 0;
    uStack_14 = 0;
    puVar4[0x2c] = 0;
    puVar4[0x2d] = 0;
    puVar4[0x2e] = 0;
    puVar4[0x2f] = 0;
    puVar4[2] = 0;
    uStack_30 = 0x3f800000;
    uStack_2c = 0x3f800000;
    uStack_28 = 0x3f800000;
    uStack_24 = 0x3f800000;
    puVar4[0x10] = 0x3f800000;
    puVar4[0x11] = 0x3f800000;
    puVar4[0x12] = 0x3f800000;
    puVar4[0x13] = 0x3f800000;
    uStack_40 = 0x3f800000;
    uStack_3c = 0x3f800000;
    uStack_38 = 0x3f800000;
    uStack_34 = 0x3f800000;
    puVar4[0x14] = 0x3f800000;
    puVar4[0x15] = 0x3f800000;
    puVar4[0x16] = 0x3f800000;
    puVar4[0x17] = 0x3f800000;
    uStack_50 = 0;
    uStack_4c = 0;
    uStack_48 = 0;
    uStack_44 = 0x3f800000;
    puVar4[0x18] = 0;
    puVar4[0x19] = 0;
    puVar4[0x1a] = 0;
    puVar4[0x1b] = 0x3f800000;
    uVar1 = param_2 & 1;
    if (((int)param_2 < 0) && (uVar1 != 0)) {
      uVar1 = uVar1 - 2;
    }
    if (uVar1 == 0) {
      puVar4[0x34] = 0;
      puVar4[0x30] = 0;
      puVar4[0x35] = 0x3f800000;
      puVar4[0x31] = 0x3f800000;
      puVar4[0x36] = 0x3f800000;
      puVar4[0x32] = 0x3f800000;
      puVar4[0x37] = 0x3f800000;
      puVar4[0x33] = 0x3f800000;
    }
    else {
      puVar4[0x34] = 0;
      puVar4[0x30] = 0;
      puVar4[0x35] = 0;
      puVar4[0x31] = 0;
      puVar4[0x36] = 0x3f800000;
      puVar4[0x32] = 0x3f800000;
      puVar4[0x37] = 0;
      puVar4[0x33] = 0;
    }
  }
  iVar3 = this->i32_1f4;
  if (this->i8_2f0 != '\0') {
    iVar2 = this->i32_1f4;
    iVar3 = iVar2 >> 1;
    if (iVar2 < 0) {
      iVar3 = iVar2 + 1 >> 1;
    }
  }
  iVar2 = rand();
  auVar5 = _lqc2(*(undefined1 (*) [16])(this + 0x2e0));
  auVar6 = _qmtc2(1.0 - ((float)iVar2 * 2.0) / 2.1474836e+09);
  auVar5 = _vmulbc(auVar5,auVar6);
  auStack_140 = _sqc2(auVar5);
  FVector::FVector(auStack_70,auStack_140);
  auVar5 = _lqc2(auStack_70);
  auVar6 = _lqc2(*(undefined1 (*) [16])(this + 0x2d0));
  auVar5 = _vadd(auVar5,auVar6);
  auStack_e0 = _sqc2(auVar5);
  FVector::FVector(auStack_60,auStack_e0);
  puVar4[4] = auStack_60._0_4_;
  puVar4[5] = auStack_60._4_4_;
  puVar4[6] = uStack_58;
  puVar4[7] = uStack_54;
  if (param_2 == 0) {
    auVar5 = _lqc2(*(undefined1 (*) [16])(this + 0x210));
    auVar6 = _lqc2(*(undefined1 (*) [16])(puVar4 + 4));
    auVar5 = _vadd(auVar5,auVar6);
    auStack_f0 = _sqc2(auVar5);
    FVector::FVector(auStack_80,auStack_f0);
    puVar4[0xc] = auStack_80._0_4_;
    puVar4[0xd] = auStack_80._4_4_;
    puVar4[0xe] = uStack_78;
    puVar4[0xf] = uStack_74;
  }
  else if (param_2 == 1) {
    auVar5 = _lqc2(*(undefined1 (*) [16])(this->i32_1fc + 0x30));
    auVar6 = _lqc2(*(undefined1 (*) [16])(puVar4 + 4));
    auVar5 = _vadd(auVar5,auVar6);
    auStack_100 = _sqc2(auVar5);
    FVector::FVector(auStack_90,auStack_100);
    puVar4[0xc] = auStack_90._0_4_;
    puVar4[0xd] = auStack_90._4_4_;
    puVar4[0xe] = uStack_88;
    puVar4[0xf] = uStack_84;
  }
  else if ((int)param_2 < iVar3) {
    auVar5 = _lqc2(*(undefined1 (*) [16])(this->i32_1fc + (param_2 - 1) * 0xf0 + 0x30));
    auVar6 = _lqc2(*(undefined1 (*) [16])(puVar4 + 4));
    auVar5 = _vadd(auVar5,auVar6);
    auStack_110 = _sqc2(auVar5);
    FVector::FVector(auStack_a0,auStack_110);
    puVar4[0xc] = auStack_a0._0_4_;
    puVar4[0xd] = auStack_a0._4_4_;
    puVar4[0xe] = uStack_98;
    puVar4[0xf] = uStack_94;
  }
  else {
    iVar3 = this->i32_1f4;
    iVar2 = this->i32_1fc;
    auVar5 = _lqc2(*(undefined1 (*) [16])(this + 0x2d0));
    auVar6 = _qmtc2(0x40000000);
    auVar5 = _vmulbc(auVar5,auVar6);
    auStack_150 = _sqc2(auVar5);
    FVector::FVector(auStack_c0,auStack_150);
    auVar5 = _lqc2(auStack_c0);
    auVar6 = _lqc2(*(undefined1 (*) [16])(iVar2 + ((iVar3 - param_2) + -1) * 0xf0 + 0x10));
    auVar5 = _vsub(auVar5,auVar6);
    auStack_120 = _sqc2(auVar5);
    FVector::FVector(auStack_b0,auStack_120);
    puVar4[4] = auStack_b0._0_4_;
    puVar4[5] = auStack_b0._4_4_;
    puVar4[6] = uStack_a8;
    puVar4[7] = uStack_a4;
    auVar5 = _lqc2(*(undefined1 (*) [16])(this->i32_1fc + (param_2 - 1) * 0xf0 + 0x30));
    auVar6 = _lqc2(*(undefined1 (*) [16])(puVar4 + 4));
    auVar5 = _vadd(auVar5,auVar6);
    auStack_130 = _sqc2(auVar5);
    FVector::FVector(auStack_d0,auStack_130);
    puVar4[0xc] = auStack_d0._0_4_;
    puVar4[0xd] = auStack_d0._4_4_;
    puVar4[0xe] = uStack_c8;
    puVar4[0xf] = uStack_c4;
  }
  return;
}

// JP: 0x002b28f0  ChangeForm__15FpObjectThunderFf  =  FpObjectThunder::ChangeForm
void FpObjectThunder::ChangeForm(float this,undefined8 param_2)

{
  int iVar1;
  int iVar2;
  float fVar3;
  float fVar4;
  undefined1 in_vf0 [16];
  undefined1 auVar5 [16];
  undefined4 uVar6;
  undefined1 auStack_70 [16];
  undefined1 auStack_60 [8];
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined1 auStack_50 [8];
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined1 auStack_40 [40];
  undefined4 uStack_18;
  undefined4 uStack_14;
  
  iVar2 = (int)param_2;
  if (iVar2->i32_1fc != 0) {
    if (1.0 < this) {
      this = 1.0;
    }
    else if (this < 0.0) {
      this = 0.0;
    }
    iVar1 = rand();
    this = this + ((1.0 - this) * (float)iVar1) / 2.1474836e+09;
    iVar1 = (int)((float)iVar2->i32_1f8 * this);
    if (iVar1 < 0) {
      iVar1 = iVar1 + 1;
    }
    iVar2->i32_1f4 = (iVar1 >> 1) << 1;
    Matrix::Matrix(auStack_40,CApp::camera + 0x240);
    iVar2->i32_270 = (int)auStack_40._32_8_;
    iVar2->i32_274 = SUB84(auStack_40._32_8_,4);
    iVar2->u32_278 = uStack_18;
    iVar2->u32_27c = uStack_14;
    auVar5 = _qmtc2((float)iVar2->i32_1f4);
    _vdiv(in_vf0,0,auVar5,0);
    auVar5 = _lqc2(*(undefined1 (*) [16])(iVar2 + 0x220));
    uVar6 = _vwaitq();
    auVar5 = _vmulq(auVar5,uVar6);
    auStack_70 = _sqc2(auVar5);
    FVector::FVector(auStack_50,auStack_70);
    iVar2->i32_2d0 = auStack_50._0_4_;
    iVar2->i32_2d4 = auStack_50._4_4_;
    iVar2->u32_2d8 = uStack_48;
    iVar2->u32_2dc = uStack_44;
    FVector::OuterProduct(auStack_60,iVar2 + 0x220,iVar2 + 0x270);
    iVar2->i32_2e0 = auStack_60._0_4_;
    iVar2->i32_2e4 = auStack_60._4_4_;
    iVar2->u32_2e8 = uStack_58;
    iVar2->u32_2ec = uStack_54;
    FVector::Normalize(iVar2 + 0x2e0);
    fVar3 = (float)FVector::Length(iVar2 + 0x2d0);
    fVar4 = (float)GetRad(iVar2->u32_2c8);
    fVar4 = sinf(fVar4);
    FVector::__amu(this * fVar3 * fVar4,iVar2 + 0x2e0);
    for (iVar1 = 0; iVar1 < iVar2->i32_1f4; iVar1 = iVar1 + 1) {
      (**(code **)(iVar2->i32_1e4 + 0x4c))(param_2,iVar1,1);
    }
    FpObjectThunder::CreateVertex(param_2);
  }
  return;
}

// JP: 0x002b2b30  CalculateFunc__15FpObjectThunderFv  =  FpObjectThunder::CalculateFunc
void FpObjectThunder::CalculateFunc(int this)

{
  undefined1 auVar1 [16];
  undefined1 auVar2 [16];
  
  if (0 < this->i32_2f4) {
    auVar2 = _lqc2(*(undefined1 (*) [16])(this + 0x300));
    auVar1 = _lqc2(*(undefined1 (*) [16])(this + 0x2a0));
    auVar1 = _vadd(auVar1,auVar2);
    auVar1 = _sqc2(auVar1);
    *(undefined1 (*) [16])(this + 0x2a0) = auVar1;
    this->i32_2f4 = this->i32_2f4 + -1;
  }
  if (0 < this->i32_310) {
    auVar2 = _lqc2(*(undefined1 (*) [16])(this + 800));
    auVar1 = _lqc2(*(undefined1 (*) [16])(this + 0x2b0));
    auVar1 = _vadd(auVar1,auVar2);
    auVar1 = _sqc2(auVar1);
    *(undefined1 (*) [16])(this + 0x2b0) = auVar1;
    this->i32_310 = this->i32_310 + -1;
  }
  return;
}

// JP: 0x002b2ba0  CreateVertex__15FpObjectThunderFv  =  FpObjectThunder::CreateVertex
void FpObjectThunder::CreateVertex(int this)

{
  undefined1 auVar1 [16];
  undefined1 auVar2 [16];
  undefined1 auVar3 [16];
  undefined1 auVar4 [16];
  undefined1 auVar5 [16];
  undefined1 auVar6 [16];
  undefined1 auVar7 [16];
  undefined1 auVar8 [16];
  undefined1 auVar9 [16];
  undefined1 auVar10 [16];
  undefined1 auVar11 [16];
  undefined1 auVar12 [16];
  undefined1 auVar13 [16];
  undefined1 auVar14 [16];
  int iVar15;
  int iVar16;
  undefined1 auVar17 [16];
  undefined1 auVar18 [16];
  undefined1 auStack_4e0 [16];
  undefined1 auStack_4d0 [16];
  undefined1 auStack_4c0 [16];
  undefined1 auStack_4b0 [16];
  undefined1 auStack_4a0 [16];
  undefined1 auStack_490 [16];
  undefined1 auStack_480 [16];
  undefined1 auStack_470 [16];
  undefined1 auStack_460 [16];
  undefined1 auStack_450 [16];
  undefined1 auStack_440 [16];
  undefined1 auStack_430 [16];
  undefined1 auStack_420 [16];
  undefined1 auStack_410 [16];
  undefined1 auStack_400 [16];
  undefined1 auStack_3f0 [16];
  undefined1 auStack_3e0 [16];
  undefined1 auStack_3d0 [16];
  undefined1 auStack_3c0 [16];
  undefined1 auStack_3b0 [16];
  undefined1 auStack_3a0 [16];
  undefined1 auStack_390 [16];
  undefined1 auStack_380 [16];
  undefined1 auStack_370 [16];
  undefined1 auStack_360 [16];
  undefined1 auStack_350 [16];
  undefined1 auStack_340 [16];
  undefined1 auStack_330 [16];
  undefined1 auStack_320 [16];
  undefined1 auStack_310 [16];
  undefined1 auStack_300 [16];
  undefined1 auStack_2f0 [16];
  undefined1 auStack_2e0 [16];
  undefined1 auStack_2d0 [16];
  undefined1 auStack_2c0 [16];
  undefined1 auStack_2b0 [16];
  undefined1 auStack_2a0 [16];
  undefined1 auStack_290 [8];
  undefined4 uStack_288;
  undefined4 uStack_284;
  undefined1 auStack_280 [16];
  undefined1 auStack_270 [8];
  undefined4 uStack_268;
  undefined4 uStack_264;
  undefined1 auStack_260 [16];
  undefined1 auStack_250 [8];
  undefined4 uStack_248;
  undefined4 uStack_244;
  undefined1 auStack_240 [16];
  undefined1 auStack_230 [8];
  undefined4 uStack_228;
  undefined4 uStack_224;
  undefined1 auStack_220 [8];
  undefined4 uStack_218;
  undefined4 uStack_214;
  undefined1 auStack_210 [8];
  undefined4 uStack_208;
  undefined4 uStack_204;
  undefined1 auStack_200 [16];
  undefined1 auStack_1f0 [8];
  undefined4 uStack_1e8;
  undefined4 uStack_1e4;
  undefined1 auStack_1e0 [16];
  undefined1 auStack_1d0 [8];
  undefined4 uStack_1c8;
  undefined4 uStack_1c4;
  undefined1 auStack_1c0 [16];
  undefined1 auStack_1b0 [8];
  undefined4 uStack_1a8;
  undefined4 uStack_1a4;
  undefined1 auStack_1a0 [16];
  undefined1 auStack_190 [8];
  undefined4 uStack_188;
  undefined4 uStack_184;
  undefined1 auStack_180 [8];
  undefined4 uStack_178;
  undefined4 uStack_174;
  undefined1 auStack_170 [8];
  undefined4 uStack_168;
  undefined4 uStack_164;
  undefined1 auStack_160 [16];
  undefined1 auStack_150 [8];
  undefined4 uStack_148;
  undefined4 uStack_144;
  undefined1 auStack_140 [16];
  undefined1 auStack_130 [8];
  undefined4 uStack_128;
  undefined4 uStack_124;
  undefined1 auStack_120 [16];
  undefined1 auStack_110 [8];
  undefined4 uStack_108;
  undefined4 uStack_104;
  undefined1 auStack_100 [16];
  undefined1 auStack_f0 [8];
  undefined4 uStack_e8;
  undefined4 uStack_e4;
  undefined1 auStack_e0 [8];
  undefined4 uStack_d8;
  undefined4 uStack_d4;
  undefined1 auStack_d0 [8];
  undefined4 uStack_c8;
  undefined4 uStack_c4;
  undefined1 auStack_c0 [16];
  undefined1 auStack_b0 [8];
  undefined4 uStack_a8;
  undefined4 uStack_a4;
  undefined1 auStack_a0 [16];
  undefined1 auStack_90 [8];
  undefined4 uStack_88;
  undefined4 uStack_84;
  undefined1 auStack_80 [16];
  undefined1 auStack_70 [8];
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined1 auStack_60 [16];
  undefined1 auStack_50 [8];
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined1 auStack_40 [8];
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined1 auStack_30 [8];
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  iVar16 = this->i32_1fc;
  auVar17 = _lqc2(*(undefined1 (*) [16])(iVar16 + 0x30));
  auVar18 = _lqc2(*(undefined1 (*) [16])(this + 0x210));
  auVar17 = _vsub(auVar17,auVar18);
  auStack_2b0 = _sqc2(auVar17);
  FVector::FVector(auStack_30,auStack_2b0);
  uStack_10 = auStack_30._0_4_;
  uStack_c = auStack_30._4_4_;
  uStack_8 = uStack_28;
  uStack_4 = uStack_24;
  FVector::OuterProduct(auStack_40,&uStack_10,this + 0x270);
  uStack_20 = auStack_40._0_4_;
  uStack_1c = auStack_40._4_4_;
  uStack_18 = uStack_38;
  uStack_14 = uStack_34;
  FVector::Normalize(&uStack_20);
  auVar17._4_4_ = uStack_1c;
  auVar17._0_4_ = uStack_20;
  auVar17._8_4_ = uStack_18;
  auVar17._12_4_ = uStack_14;
  auVar17 = _lqc2(auVar17);
  auVar18 = _qmtc2(-this->f32_2c4);
  auVar17 = _vmulbc(auVar17,auVar18);
  auStack_3f0 = _sqc2(auVar17);
  FVector::FVector(auStack_60,auStack_3f0);
  auVar17 = _lqc2(*(undefined1 (*) [16])(this + 0x210));
  auVar18 = _lqc2(auStack_60);
  auVar17 = _vadd(auVar17,auVar18);
  auStack_2c0 = _sqc2(auVar17);
  FVector::FVector(auStack_50,auStack_2c0);
  this->i32_230 = auStack_50._0_4_;
  this->i32_234 = auStack_50._4_4_;
  this->u32_238 = uStack_48;
  this->u32_23c = uStack_44;
  auVar18._4_4_ = uStack_1c;
  auVar18._0_4_ = uStack_20;
  auVar18._8_4_ = uStack_18;
  auVar18._12_4_ = uStack_14;
  auVar17 = _lqc2(auVar18);
  auVar18 = _qmtc2(this->u32_2c4);
  auVar17 = _vmulbc(auVar17,auVar18);
  auStack_400 = _sqc2(auVar17);
  FVector::FVector(auStack_80,auStack_400);
  auVar17 = _lqc2(*(undefined1 (*) [16])(this + 0x210));
  auVar18 = _lqc2(auStack_80);
  auVar17 = _vadd(auVar17,auVar18);
  auStack_2d0 = _sqc2(auVar17);
  FVector::FVector(auStack_70,auStack_2d0);
  this->i32_240 = auStack_70._0_4_;
  this->i32_244 = auStack_70._4_4_;
  this->u32_248 = uStack_68;
  this->u32_24c = uStack_64;
  auVar1._4_4_ = uStack_1c;
  auVar1._0_4_ = uStack_20;
  auVar1._8_4_ = uStack_18;
  auVar1._12_4_ = uStack_14;
  auVar17 = _lqc2(auVar1);
  auVar18 = _qmtc2(-this->f32_2c0);
  auVar17 = _vmulbc(auVar17,auVar18);
  auStack_410 = _sqc2(auVar17);
  FVector::FVector(auStack_a0,auStack_410);
  auVar17 = _lqc2(*(undefined1 (*) [16])(this + 0x210));
  auVar18 = _lqc2(auStack_a0);
  auVar17 = _vadd(auVar17,auVar18);
  auStack_2e0 = _sqc2(auVar17);
  FVector::FVector(auStack_90,auStack_2e0);
  this->i32_250 = auStack_90._0_4_;
  this->i32_254 = auStack_90._4_4_;
  this->u32_258 = uStack_88;
  this->u32_25c = uStack_84;
  auVar2._4_4_ = uStack_1c;
  auVar2._0_4_ = uStack_20;
  auVar2._8_4_ = uStack_18;
  auVar2._12_4_ = uStack_14;
  auVar17 = _lqc2(auVar2);
  auVar18 = _qmtc2(this->u32_2c0);
  auVar17 = _vmulbc(auVar17,auVar18);
  auStack_420 = _sqc2(auVar17);
  FVector::FVector(auStack_c0,auStack_420);
  auVar17 = _lqc2(*(undefined1 (*) [16])(this + 0x210));
  auVar18 = _lqc2(auStack_c0);
  auVar17 = _vadd(auVar17,auVar18);
  auStack_2f0 = _sqc2(auVar17);
  FVector::FVector(auStack_b0,auStack_2f0);
  this->i32_260 = auStack_b0._0_4_;
  this->i32_264 = auStack_b0._4_4_;
  this->u32_268 = uStack_a8;
  this->u32_26c = uStack_a4;
  if (1 < this->i32_1f4) {
    auVar17 = _lqc2(*(undefined1 (*) [16])(this->i32_1fc + 0x120));
    auVar18 = _lqc2(*(undefined1 (*) [16])(this + 0x210));
    auVar17 = _vsub(auVar17,auVar18);
    auStack_300 = _sqc2(auVar17);
    FVector::FVector(auStack_d0,auStack_300);
    uStack_10 = auStack_d0._0_4_;
    uStack_c = auStack_d0._4_4_;
    uStack_8 = uStack_c8;
    uStack_4 = uStack_c4;
    FVector::OuterProduct(auStack_e0,&uStack_10,this + 0x270);
    uStack_20 = auStack_e0._0_4_;
    uStack_1c = auStack_e0._4_4_;
    uStack_18 = uStack_d8;
    uStack_14 = uStack_d4;
    FVector::Normalize(&uStack_20);
  }
  auVar3._4_4_ = uStack_1c;
  auVar3._0_4_ = uStack_20;
  auVar3._8_4_ = uStack_18;
  auVar3._12_4_ = uStack_14;
  auVar17 = _lqc2(auVar3);
  auVar18 = _qmtc2(-this->f32_2c4);
  auVar17 = _vmulbc(auVar17,auVar18);
  auStack_430 = _sqc2(auVar17);
  FVector::FVector(auStack_100,auStack_430);
  auVar17 = _lqc2(*(undefined1 (*) [16])(iVar16 + 0x30));
  auVar18 = _lqc2(auStack_100);
  auVar17 = _vadd(auVar17,auVar18);
  auStack_310 = _sqc2(auVar17);
  FVector::FVector(auStack_f0,auStack_310);
  iVar16->i32_70 = auStack_f0._0_4_;
  iVar16->i32_74 = auStack_f0._4_4_;
  iVar16->u32_78 = uStack_e8;
  iVar16->u32_7c = uStack_e4;
  auVar4._4_4_ = uStack_1c;
  auVar4._0_4_ = uStack_20;
  auVar4._8_4_ = uStack_18;
  auVar4._12_4_ = uStack_14;
  auVar17 = _lqc2(auVar4);
  auVar18 = _qmtc2(this->u32_2c4);
  auVar17 = _vmulbc(auVar17,auVar18);
  auStack_440 = _sqc2(auVar17);
  FVector::FVector(auStack_120,auStack_440);
  auVar17 = _lqc2(*(undefined1 (*) [16])(iVar16 + 0x30));
  auVar18 = _lqc2(auStack_120);
  auVar17 = _vadd(auVar17,auVar18);
  auStack_320 = _sqc2(auVar17);
  FVector::FVector(auStack_110,auStack_320);
  iVar16->i32_80 = auStack_110._0_4_;
  iVar16->i32_84 = auStack_110._4_4_;
  iVar16->u32_88 = uStack_108;
  iVar16->u32_8c = uStack_104;
  auVar5._4_4_ = uStack_1c;
  auVar5._0_4_ = uStack_20;
  auVar5._8_4_ = uStack_18;
  auVar5._12_4_ = uStack_14;
  auVar17 = _lqc2(auVar5);
  auVar18 = _qmtc2(-this->f32_2c0);
  auVar17 = _vmulbc(auVar17,auVar18);
  auStack_450 = _sqc2(auVar17);
  FVector::FVector(auStack_140,auStack_450);
  auVar17 = _lqc2(*(undefined1 (*) [16])(iVar16 + 0x30));
  auVar18 = _lqc2(auStack_140);
  auVar17 = _vadd(auVar17,auVar18);
  auStack_330 = _sqc2(auVar17);
  FVector::FVector(auStack_130,auStack_330);
  iVar16->i32_90 = auStack_130._0_4_;
  iVar16->i32_94 = auStack_130._4_4_;
  iVar16->u32_98 = uStack_128;
  iVar16->u32_9c = uStack_124;
  auVar6._4_4_ = uStack_1c;
  auVar6._0_4_ = uStack_20;
  auVar6._8_4_ = uStack_18;
  auVar6._12_4_ = uStack_14;
  auVar17 = _lqc2(auVar6);
  auVar18 = _qmtc2(this->u32_2c0);
  auVar17 = _vmulbc(auVar17,auVar18);
  auStack_460 = _sqc2(auVar17);
  FVector::FVector(auStack_160,auStack_460);
  auVar17 = _lqc2(*(undefined1 (*) [16])(iVar16 + 0x30));
  auVar18 = _lqc2(auStack_160);
  auVar17 = _vadd(auVar17,auVar18);
  auStack_340 = _sqc2(auVar17);
  FVector::FVector(auStack_150,auStack_340);
  iVar16->i32_a0 = auStack_150._0_4_;
  iVar16->i32_a4 = auStack_150._4_4_;
  iVar16->u32_a8 = uStack_148;
  iVar16->u32_ac = uStack_144;
  iVar16 = this->i32_1fc;
  for (iVar15 = 1; iVar15 < this->i32_1f4 + -1; iVar15 = iVar15 + 1) {
    auVar17 = _lqc2(*(undefined1 (*) [16])(this->i32_1fc + (iVar15 + 1) * 0xf0 + 0x30));
    auVar18 = _lqc2(*(undefined1 (*) [16])(this->i32_1fc + (iVar15 + -1) * 0xf0 + 0x30))
    ;
    auVar17 = _vsub(auVar17,auVar18);
    auStack_350 = _sqc2(auVar17);
    FVector::FVector(auStack_170,auStack_350);
    uStack_10 = auStack_170._0_4_;
    uStack_c = auStack_170._4_4_;
    uStack_8 = uStack_168;
    uStack_4 = uStack_164;
    FVector::OuterProduct(auStack_180,&uStack_10,this + 0x270);
    uStack_20 = auStack_180._0_4_;
    uStack_1c = auStack_180._4_4_;
    uStack_18 = uStack_178;
    uStack_14 = uStack_174;
    FVector::Normalize(&uStack_20);
    auVar7._4_4_ = uStack_1c;
    auVar7._0_4_ = uStack_20;
    auVar7._8_4_ = uStack_18;
    auVar7._12_4_ = uStack_14;
    auVar17 = _lqc2(auVar7);
    auVar18 = _qmtc2(-this->f32_2c4);
    auVar17 = _vmulbc(auVar17,auVar18);
    auStack_470 = _sqc2(auVar17);
    FVector::FVector(auStack_1a0,auStack_470);
    auVar17 = _lqc2(*(undefined1 (*) [16])(iVar16 + 0x120));
    auVar18 = _lqc2(auStack_1a0);
    auVar17 = _vadd(auVar17,auVar18);
    auStack_360 = _sqc2(auVar17);
    FVector::FVector(auStack_190,auStack_360);
    iVar16->i32_160 = auStack_190._0_4_;
    iVar16->i32_164 = auStack_190._4_4_;
    iVar16->u32_168 = uStack_188;
    iVar16->u32_16c = uStack_184;
    auVar8._4_4_ = uStack_1c;
    auVar8._0_4_ = uStack_20;
    auVar8._8_4_ = uStack_18;
    auVar8._12_4_ = uStack_14;
    auVar17 = _lqc2(auVar8);
    auVar18 = _qmtc2(this->u32_2c4);
    auVar17 = _vmulbc(auVar17,auVar18);
    auStack_480 = _sqc2(auVar17);
    FVector::FVector(auStack_1c0,auStack_480);
    auVar17 = _lqc2(*(undefined1 (*) [16])(iVar16 + 0x120));
    auVar18 = _lqc2(auStack_1c0);
    auVar17 = _vadd(auVar17,auVar18);
    auStack_370 = _sqc2(auVar17);
    FVector::FVector(auStack_1b0,auStack_370);
    iVar16->i32_170 = auStack_1b0._0_4_;
    iVar16->i32_174 = auStack_1b0._4_4_;
    iVar16->u32_178 = uStack_1a8;
    iVar16->u32_17c = uStack_1a4;
    auVar9._4_4_ = uStack_1c;
    auVar9._0_4_ = uStack_20;
    auVar9._8_4_ = uStack_18;
    auVar9._12_4_ = uStack_14;
    auVar17 = _lqc2(auVar9);
    auVar18 = _qmtc2(-this->f32_2c0);
    auVar17 = _vmulbc(auVar17,auVar18);
    auStack_490 = _sqc2(auVar17);
    FVector::FVector(auStack_1e0,auStack_490);
    auVar17 = _lqc2(*(undefined1 (*) [16])(iVar16 + 0x120));
    auVar18 = _lqc2(auStack_1e0);
    auVar17 = _vadd(auVar17,auVar18);
    auStack_380 = _sqc2(auVar17);
    FVector::FVector(auStack_1d0,auStack_380);
    iVar16->i32_180 = auStack_1d0._0_4_;
    iVar16->i32_184 = auStack_1d0._4_4_;
    iVar16->u32_188 = uStack_1c8;
    iVar16->u32_18c = uStack_1c4;
    auVar10._4_4_ = uStack_1c;
    auVar10._0_4_ = uStack_20;
    auVar10._8_4_ = uStack_18;
    auVar10._12_4_ = uStack_14;
    auVar17 = _lqc2(auVar10);
    auVar18 = _qmtc2(this->u32_2c0);
    auVar17 = _vmulbc(auVar17,auVar18);
    auStack_4a0 = _sqc2(auVar17);
    FVector::FVector(auStack_200,auStack_4a0);
    auVar17 = _lqc2(*(undefined1 (*) [16])(iVar16 + 0x120));
    auVar18 = _lqc2(auStack_200);
    auVar17 = _vadd(auVar17,auVar18);
    auStack_390 = _sqc2(auVar17);
    FVector::FVector(auStack_1f0,auStack_390);
    iVar16->i32_190 = auStack_1f0._0_4_;
    iVar16->i32_194 = auStack_1f0._4_4_;
    iVar16->u32_198 = uStack_1e8;
    iVar16->u32_19c = uStack_1e4;
    iVar16 = iVar16 + 0xf0;
  }
  iVar16 = this->i32_1fc + (this->i32_1f4 + -1) * 0xf0;
  auVar17 = _lqc2(*(undefined1 (*) [16])(iVar16 + 0x30));
  auVar18 = _lqc2(*(undefined1 (*) [16])
                   (this->i32_1fc + (this->i32_1f4 + -2) * 0xf0 + 0x30));
  auVar17 = _vsub(auVar17,auVar18);
  auStack_3a0 = _sqc2(auVar17);
  FVector::FVector(auStack_210,auStack_3a0);
  uStack_10 = auStack_210._0_4_;
  uStack_c = auStack_210._4_4_;
  uStack_8 = uStack_208;
  uStack_4 = uStack_204;
  FVector::OuterProduct(auStack_220,&uStack_10,this + 0x270);
  uStack_20 = auStack_220._0_4_;
  uStack_1c = auStack_220._4_4_;
  uStack_18 = uStack_218;
  uStack_14 = uStack_214;
  FVector::Normalize(&uStack_20);
  auVar11._4_4_ = uStack_1c;
  auVar11._0_4_ = uStack_20;
  auVar11._8_4_ = uStack_18;
  auVar11._12_4_ = uStack_14;
  auVar17 = _lqc2(auVar11);
  auVar18 = _qmtc2(-this->f32_2c4);
  auVar17 = _vmulbc(auVar17,auVar18);
  auStack_4b0 = _sqc2(auVar17);
  FVector::FVector(auStack_240,auStack_4b0);
  auVar17 = _lqc2(*(undefined1 (*) [16])(iVar16 + 0x30));
  auVar18 = _lqc2(auStack_240);
  auVar17 = _vadd(auVar17,auVar18);
  auStack_3b0 = _sqc2(auVar17);
  FVector::FVector(auStack_230,auStack_3b0);
  iVar16->i32_70 = auStack_230._0_4_;
  iVar16->i32_74 = auStack_230._4_4_;
  iVar16->u32_78 = uStack_228;
  iVar16->u32_7c = uStack_224;
  auVar12._4_4_ = uStack_1c;
  auVar12._0_4_ = uStack_20;
  auVar12._8_4_ = uStack_18;
  auVar12._12_4_ = uStack_14;
  auVar17 = _lqc2(auVar12);
  auVar18 = _qmtc2(this->u32_2c4);
  auVar17 = _vmulbc(auVar17,auVar18);
  auStack_4c0 = _sqc2(auVar17);
  FVector::FVector(auStack_260,auStack_4c0);
  auVar17 = _lqc2(*(undefined1 (*) [16])(iVar16 + 0x30));
  auVar18 = _lqc2(auStack_260);
  auVar17 = _vadd(auVar17,auVar18);
  auStack_3c0 = _sqc2(auVar17);
  FVector::FVector(auStack_250,auStack_3c0);
  iVar16->i32_80 = auStack_250._0_4_;
  iVar16->i32_84 = auStack_250._4_4_;
  iVar16->u32_88 = uStack_248;
  iVar16->u32_8c = uStack_244;
  auVar13._4_4_ = uStack_1c;
  auVar13._0_4_ = uStack_20;
  auVar13._8_4_ = uStack_18;
  auVar13._12_4_ = uStack_14;
  auVar17 = _lqc2(auVar13);
  auVar18 = _qmtc2(-this->f32_2c0);
  auVar17 = _vmulbc(auVar17,auVar18);
  auStack_4d0 = _sqc2(auVar17);
  FVector::FVector(auStack_280,auStack_4d0);
  auVar17 = _lqc2(*(undefined1 (*) [16])(iVar16 + 0x30));
  auVar18 = _lqc2(auStack_280);
  auVar17 = _vadd(auVar17,auVar18);
  auStack_3d0 = _sqc2(auVar17);
  FVector::FVector(auStack_270,auStack_3d0);
  iVar16->i32_90 = auStack_270._0_4_;
  iVar16->i32_94 = auStack_270._4_4_;
  iVar16->u32_98 = uStack_268;
  iVar16->u32_9c = uStack_264;
  auVar14._4_4_ = uStack_1c;
  auVar14._0_4_ = uStack_20;
  auVar14._8_4_ = uStack_18;
  auVar14._12_4_ = uStack_14;
  auVar17 = _lqc2(auVar14);
  auVar18 = _qmtc2(this->u32_2c0);
  auVar17 = _vmulbc(auVar17,auVar18);
  auStack_4e0 = _sqc2(auVar17);
  FVector::FVector(auStack_2a0,auStack_4e0);
  auVar17 = _lqc2(*(undefined1 (*) [16])(iVar16 + 0x30));
  auVar18 = _lqc2(auStack_2a0);
  auVar17 = _vadd(auVar17,auVar18);
  auStack_3e0 = _sqc2(auVar17);
  FVector::FVector(auStack_290,auStack_3e0);
  iVar16->i32_a0 = auStack_290._0_4_;
  iVar16->i32_a4 = auStack_290._4_4_;
  iVar16->u32_a8 = uStack_288;
  iVar16->u32_ac = uStack_284;
  return;
}

// JP: 0x002b35f0  SetPacket__15FpObjectThunderFv  =  FpObjectThunder::SetPacket
void FpObjectThunder::SetPacket(int this)

{
  undefined4 *puVar1;
  float in_zero_lo;
  float in_zero_hi;
  float in_zero_udw;
  float in_register_0000000c;
  int iVar2;
  float *pfVar3;
  int iVar4;
  int iVar5;
  float fVar6;
  uint uVar7;
  float fStack_150;
  float fStack_14c;
  float fStack_148;
  float fStack_144;
  float *pfStack_11c;
  float *pfStack_118;
  float *pfStack_114;
  float *pfStack_110;
  float *pfStack_10c;
  float *pfStack_108;
  float *pfStack_104;
  float *pfStack_100;
  float *pfStack_fc;
  float *pfStack_f8;
  uint *puStack_f4;
  uint *puStack_f0;
  float *pfStack_ec;
  float *pfStack_e8;
  float *pfStack_e4;
  float *pfStack_e0;
  uint *puStack_dc;
  uint *puStack_d8;
  undefined4 *puStack_d4;
  undefined4 *puStack_d0;
  float *pfStack_cc;
  float *pfStack_c8;
  uint *puStack_c4;
  uint *puStack_c0;
  float *pfStack_bc;
  float *pfStack_b8;
  float *pfStack_b4;
  float *pfStack_b0;
  float *pfStack_ac;
  float *pfStack_a8;
  float *pfStack_a4;
  float *pfStack_a0;
  float *pfStack_9c;
  float *pfStack_98;
  float *pfStack_94;
  float *pfStack_90;
  float *pfStack_8c;
  float *pfStack_88;
  float *pfStack_84;
  float *pfStack_80;
  uint *puStack_7c;
  uint *puStack_78;
  float *pfStack_74;
  float *pfStack_70;
  float *pfStack_6c;
  float *pfStack_68;
  uint *puStack_64;
  uint *puStack_60;
  undefined4 *puStack_5c;
  undefined4 *puStack_58;
  float *pfStack_54;
  float *pfStack_50;
  uint *puStack_4c;
  uint *puStack_48;
  undefined4 *puStack_44;
  undefined4 *puStack_40;
  ulong *puStack_3c;
  ulong *puStack_38;
  float *pfStack_34;
  uint uStack_30;
  float fStack_2c;
  float fStack_28;
  uint uStack_24;
  float fStack_20;
  float fStack_1c;
  float fStack_18;
  float fStack_14;
  int iStack_10;
  
  fStack_14 = this->f32_1f0 * *(float *)(this->i32_8 + 0x5c);
  pfStack_34 = *(float **)(this + 0x88);
  *pfStack_34 = in_zero_lo;
  pfStack_34[1] = in_zero_hi;
  pfStack_34[2] = in_zero_udw;
  pfStack_34[3] = in_register_0000000c;
  *pfStack_34 = (float)(&DAT_10000001 + (this->i32_1f8 + 1) * 0xc);
  pfStack_34[3] = (float)((this->i32_1f8 + 1) * 0xc + 1U | 0x50000000);
  this->i32_88 = this->i32_88 + 0x10;
  puStack_3c = *(ulong **)(this + 0x88);
  *puStack_3c = (long)((this->i32_1f8 + 1) * 4) | 0x302e400000008000;
  puStack_3c[1] = 0x412;
  this->i32_88 = this->i32_88 + 0x10;
  puVar1 = *(undefined4 **)(this + 0x88);
  fStack_150 = in_zero_lo;
  fStack_14c = in_zero_hi;
  fStack_148 = in_zero_udw;
  puStack_44 = puVar1;
  puStack_40 = puVar1;
  puStack_38 = puStack_3c;
  iStack_10 = this;
  fStack_18 = (float)PutiObject::RotTransPer(this,this + 0x230,&fStack_150);
  PutiObject::ClipFlag(iStack_10);
  *puVar1 = 0;
  puVar1[1] = 0;
  puVar1[2] = fStack_18;
  iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
  puStack_4c = *(uint **)(iStack_10 + 0x88);
  fVar6 = iStack_10->f32_2b0;
  if (fVar6 < 2.1474836e+09) {
    uVar7 = (uint)fVar6;
  }
  else {
    uVar7 = (int)(fVar6 - 2.1474836e+09) | 0x80000000;
  }
  *puStack_4c = uVar7;
  fVar6 = iStack_10->f32_2b4;
  if (fVar6 < 2.1474836e+09) {
    uVar7 = (uint)fVar6;
  }
  else {
    uVar7 = (int)(fVar6 - 2.1474836e+09) | 0x80000000;
  }
  puStack_4c[1] = uVar7;
  fVar6 = iStack_10->f32_2b8;
  if (fVar6 < 2.1474836e+09) {
    uVar7 = (uint)fVar6;
  }
  else {
    uVar7 = (int)(fVar6 - 2.1474836e+09) | 0x80000000;
  }
  puStack_4c[2] = uVar7;
  puStack_4c[3] = 0;
  iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
  pfStack_54 = *(float **)(iStack_10 + 0x88);
  fStack_144 = 4.59177e-41;
  *pfStack_54 = fStack_150;
  pfStack_54[1] = fStack_14c;
  pfStack_54[2] = fStack_148;
  pfStack_54[3] = 4.59177e-41;
  iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
  puVar1 = *(undefined4 **)(iStack_10 + 0x88);
  puStack_5c = puVar1;
  puStack_58 = puVar1;
  pfStack_50 = pfStack_54;
  puStack_48 = puStack_4c;
  fStack_18 = (float)PutiObject::RotTransPer
                               (iStack_10,iStack_10 + 0x240,&fStack_150);
  PutiObject::ClipFlag(iStack_10);
  *puVar1 = fStack_18;
  puVar1[1] = 0;
  puVar1[2] = fStack_18;
  iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
  puStack_64 = *(uint **)(iStack_10 + 0x88);
  fVar6 = iStack_10->f32_2b0;
  if (fVar6 < 2.1474836e+09) {
    uVar7 = (uint)fVar6;
  }
  else {
    uVar7 = (int)(fVar6 - 2.1474836e+09) | 0x80000000;
  }
  *puStack_64 = uVar7;
  fVar6 = iStack_10->f32_2b4;
  if (fVar6 < 2.1474836e+09) {
    uVar7 = (uint)fVar6;
  }
  else {
    uVar7 = (int)(fVar6 - 2.1474836e+09) | 0x80000000;
  }
  puStack_64[1] = uVar7;
  fVar6 = iStack_10->f32_2b8;
  if (fVar6 < 2.1474836e+09) {
    uVar7 = (uint)fVar6;
  }
  else {
    uVar7 = (int)(fVar6 - 2.1474836e+09) | 0x80000000;
  }
  puStack_64[2] = uVar7;
  puStack_64[3] = 0;
  iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
  pfStack_6c = *(float **)(iStack_10 + 0x88);
  fStack_144 = 4.59177e-41;
  *pfStack_6c = fStack_150;
  pfStack_6c[1] = fStack_14c;
  pfStack_6c[2] = fStack_148;
  pfStack_6c[3] = 4.59177e-41;
  iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
  pfVar3 = *(float **)(iStack_10 + 0x88);
  iVar2 = iStack_10->i32_1fc;
  pfStack_74 = pfVar3;
  pfStack_70 = pfVar3;
  pfStack_68 = pfStack_6c;
  puStack_60 = puStack_64;
  for (iVar4 = 0; iVar4 < iStack_10->i32_1f4; iVar4 = iVar4 + 1) {
    fStack_1c = iStack_10->f32_2bc * fStack_14;
    if (fStack_1c < 0.0) {
      fStack_1c = 0.0;
    }
    else if (128.0 < fStack_1c) {
      fStack_1c = 128.0;
    }
    if (0.0 < fStack_1c) {
      for (iVar5 = 0; iVar5 < 2; iVar5 = iVar5 + 1) {
        fStack_20 = (float)PutiObject::RotTransPer
                                     (iStack_10,iVar2 + iVar5 * 0x10 + 0x70,&fStack_150);
        uStack_24 = PutiObject::ClipFlag(iStack_10);
        *pfVar3 = *(float *)(iVar2 + iVar5 * 8 + 0xc0) * fStack_20;
        pfVar3[1] = *(float *)(iVar2 + iVar5 * 8 + 0xc4) * fStack_20;
        pfVar3[2] = fStack_20;
        iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
        puStack_7c = *(uint **)(iStack_10 + 0x88);
        fVar6 = iStack_10->f32_2b0;
        if (fVar6 < 2.1474836e+09) {
          uVar7 = (uint)fVar6;
        }
        else {
          uVar7 = (int)(fVar6 - 2.1474836e+09) | 0x80000000;
        }
        *puStack_7c = uVar7;
        fVar6 = iStack_10->f32_2b4;
        if (fVar6 < 2.1474836e+09) {
          uVar7 = (uint)fVar6;
        }
        else {
          uVar7 = (int)(fVar6 - 2.1474836e+09) | 0x80000000;
        }
        puStack_7c[1] = uVar7;
        fVar6 = iStack_10->f32_2b8;
        if (fVar6 < 2.1474836e+09) {
          uVar7 = (uint)fVar6;
        }
        else {
          uVar7 = (int)(fVar6 - 2.1474836e+09) | 0x80000000;
        }
        puStack_7c[2] = uVar7;
        if (fStack_1c < 2.1474836e+09) {
          uVar7 = (uint)fStack_1c;
        }
        else {
          uVar7 = (int)(fStack_1c - 2.1474836e+09) | 0x80000000;
        }
        puStack_7c[3] = uVar7;
        if (iVar4 == iStack_10->i32_1f4 + -1) {
          puStack_7c[3] = 0;
        }
        iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
        pfStack_84 = *(float **)(iStack_10 + 0x88);
        if ((uStack_24 & 0x3ffff) != 0) {
          fStack_144 = 4.59177e-41;
        }
        *pfStack_84 = fStack_150;
        pfStack_84[1] = fStack_14c;
        pfStack_84[2] = fStack_148;
        pfStack_84[3] = fStack_144;
        iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
        pfVar3 = *(float **)(iStack_10 + 0x88);
        pfStack_8c = pfVar3;
        pfStack_88 = pfVar3;
        pfStack_80 = pfStack_84;
        puStack_78 = puStack_7c;
      }
    }
    else {
      for (iVar5 = 0; iVar5 < 2; iVar5 = iVar5 + 1) {
        *pfVar3 = in_zero_lo;
        pfVar3[1] = in_zero_hi;
        pfVar3[2] = in_zero_udw;
        pfVar3[3] = in_register_0000000c;
        iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
        pfStack_94 = *(float **)(iStack_10 + 0x88);
        *pfStack_94 = in_zero_lo;
        pfStack_94[1] = in_zero_hi;
        pfStack_94[2] = in_zero_udw;
        pfStack_94[3] = in_register_0000000c;
        iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
        pfStack_9c = *(float **)(iStack_10 + 0x88);
        *pfStack_9c = in_zero_lo;
        pfStack_9c[1] = in_zero_hi;
        pfStack_9c[2] = in_zero_udw;
        pfStack_9c[3] = in_register_0000000c;
        pfStack_9c[3] = 4.59177e-41;
        iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
        pfVar3 = *(float **)(iStack_10 + 0x88);
        pfStack_a4 = pfVar3;
        pfStack_a0 = pfVar3;
        pfStack_98 = pfStack_9c;
        pfStack_90 = pfStack_94;
      }
    }
    iVar2 = iVar2 + 0xf0;
  }
  for (iVar2 = iStack_10->i32_1f4; iVar2 < iStack_10->i32_1f8; iVar2 = iVar2 + 1) {
    for (iVar4 = 0; iVar4 < 2; iVar4 = iVar4 + 1) {
      *pfVar3 = in_zero_lo;
      pfVar3[1] = in_zero_hi;
      pfVar3[2] = in_zero_udw;
      pfVar3[3] = in_register_0000000c;
      iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
      pfStack_ac = *(float **)(iStack_10 + 0x88);
      *pfStack_ac = in_zero_lo;
      pfStack_ac[1] = in_zero_hi;
      pfStack_ac[2] = in_zero_udw;
      pfStack_ac[3] = in_register_0000000c;
      iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
      pfStack_b4 = *(float **)(iStack_10 + 0x88);
      *pfStack_b4 = in_zero_lo;
      pfStack_b4[1] = in_zero_hi;
      pfStack_b4[2] = in_zero_udw;
      pfStack_b4[3] = in_register_0000000c;
      pfStack_b4[3] = 4.59177e-41;
      iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
      pfVar3 = *(float **)(iStack_10 + 0x88);
      pfStack_bc = pfVar3;
      pfStack_b8 = pfVar3;
      pfStack_b0 = pfStack_b4;
      pfStack_a8 = pfStack_ac;
    }
  }
  fStack_18 = (float)PutiObject::RotTransPer
                               (iStack_10,iStack_10 + 0x250,&fStack_150);
  PutiObject::ClipFlag(iStack_10);
  *pfVar3 = 0.0;
  pfVar3[1] = 0.0;
  pfVar3[2] = fStack_18;
  iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
  puStack_c4 = *(uint **)(iStack_10 + 0x88);
  fVar6 = iStack_10->f32_2a0;
  if (fVar6 < 2.1474836e+09) {
    uVar7 = (uint)fVar6;
  }
  else {
    uVar7 = (int)(fVar6 - 2.1474836e+09) | 0x80000000;
  }
  *puStack_c4 = uVar7;
  fVar6 = iStack_10->f32_2a4;
  if (fVar6 < 2.1474836e+09) {
    uVar7 = (uint)fVar6;
  }
  else {
    uVar7 = (int)(fVar6 - 2.1474836e+09) | 0x80000000;
  }
  puStack_c4[1] = uVar7;
  fVar6 = iStack_10->f32_2a8;
  if (fVar6 < 2.1474836e+09) {
    uVar7 = (uint)fVar6;
  }
  else {
    uVar7 = (int)(fVar6 - 2.1474836e+09) | 0x80000000;
  }
  puStack_c4[2] = uVar7;
  puStack_c4[3] = 0;
  iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
  pfStack_cc = *(float **)(iStack_10 + 0x88);
  fStack_144 = 4.59177e-41;
  *pfStack_cc = fStack_150;
  pfStack_cc[1] = fStack_14c;
  pfStack_cc[2] = fStack_148;
  pfStack_cc[3] = 4.59177e-41;
  iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
  puVar1 = *(undefined4 **)(iStack_10 + 0x88);
  puStack_d4 = puVar1;
  puStack_d0 = puVar1;
  pfStack_c8 = pfStack_cc;
  puStack_c0 = puStack_c4;
  fStack_18 = (float)PutiObject::RotTransPer
                               (iStack_10,iStack_10 + 0x260,&fStack_150);
  PutiObject::ClipFlag(iStack_10);
  *puVar1 = fStack_18;
  puVar1[1] = 0;
  puVar1[2] = fStack_18;
  iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
  puStack_dc = *(uint **)(iStack_10 + 0x88);
  fVar6 = iStack_10->f32_2a0;
  if (fVar6 < 2.1474836e+09) {
    uVar7 = (uint)fVar6;
  }
  else {
    uVar7 = (int)(fVar6 - 2.1474836e+09) | 0x80000000;
  }
  *puStack_dc = uVar7;
  fVar6 = iStack_10->f32_2a4;
  if (fVar6 < 2.1474836e+09) {
    uVar7 = (uint)fVar6;
  }
  else {
    uVar7 = (int)(fVar6 - 2.1474836e+09) | 0x80000000;
  }
  puStack_dc[1] = uVar7;
  fVar6 = iStack_10->f32_2a8;
  if (fVar6 < 2.1474836e+09) {
    uVar7 = (uint)fVar6;
  }
  else {
    uVar7 = (int)(fVar6 - 2.1474836e+09) | 0x80000000;
  }
  puStack_dc[2] = uVar7;
  puStack_dc[3] = 0;
  iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
  pfStack_e4 = *(float **)(iStack_10 + 0x88);
  fStack_144 = 4.59177e-41;
  *pfStack_e4 = fStack_150;
  pfStack_e4[1] = fStack_14c;
  pfStack_e4[2] = fStack_148;
  pfStack_e4[3] = 4.59177e-41;
  iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
  pfVar3 = *(float **)(iStack_10 + 0x88);
  iVar2 = iStack_10->i32_1fc;
  pfStack_ec = pfVar3;
  pfStack_e8 = pfVar3;
  pfStack_e0 = pfStack_e4;
  puStack_d8 = puStack_dc;
  for (iVar4 = 0; iVar4 < iStack_10->i32_1f4; iVar4 = iVar4 + 1) {
    fStack_28 = iStack_10->f32_2ac * fStack_14;
    if (fStack_28 < 0.0) {
      fStack_28 = 0.0;
    }
    else if (128.0 < fStack_28) {
      fStack_28 = 128.0;
    }
    if (0.0 < fStack_28) {
      for (iVar5 = 2; iVar5 < 4; iVar5 = iVar5 + 1) {
        fStack_2c = (float)PutiObject::RotTransPer
                                     (iStack_10,iVar2 + iVar5 * 0x10 + 0x70,&fStack_150);
        uStack_30 = PutiObject::ClipFlag(iStack_10);
        *pfVar3 = *(float *)(iVar2 + iVar5 * 8 + 0xc0) * fStack_2c;
        pfVar3[1] = *(float *)(iVar2 + iVar5 * 8 + 0xc4) * fStack_2c;
        pfVar3[2] = fStack_2c;
        iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
        puStack_f4 = *(uint **)(iStack_10 + 0x88);
        fVar6 = iStack_10->f32_2a0;
        if (fVar6 < 2.1474836e+09) {
          uVar7 = (uint)fVar6;
        }
        else {
          uVar7 = (int)(fVar6 - 2.1474836e+09) | 0x80000000;
        }
        *puStack_f4 = uVar7;
        fVar6 = iStack_10->f32_2a4;
        if (fVar6 < 2.1474836e+09) {
          uVar7 = (uint)fVar6;
        }
        else {
          uVar7 = (int)(fVar6 - 2.1474836e+09) | 0x80000000;
        }
        puStack_f4[1] = uVar7;
        fVar6 = iStack_10->f32_2a8;
        if (fVar6 < 2.1474836e+09) {
          uVar7 = (uint)fVar6;
        }
        else {
          uVar7 = (int)(fVar6 - 2.1474836e+09) | 0x80000000;
        }
        puStack_f4[2] = uVar7;
        if (fStack_28 < 2.1474836e+09) {
          uVar7 = (uint)fStack_28;
        }
        else {
          uVar7 = (int)(fStack_28 - 2.1474836e+09) | 0x80000000;
        }
        puStack_f4[3] = uVar7;
        if (iVar4 == iStack_10->i32_1f4 + -1) {
          puStack_f4[3] = 0;
        }
        iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
        pfStack_fc = *(float **)(iStack_10 + 0x88);
        if ((uStack_30 & 0x3ffff) != 0) {
          fStack_144 = 4.59177e-41;
        }
        *pfStack_fc = fStack_150;
        pfStack_fc[1] = fStack_14c;
        pfStack_fc[2] = fStack_148;
        pfStack_fc[3] = fStack_144;
        iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
        pfVar3 = *(float **)(iStack_10 + 0x88);
        pfStack_104 = pfVar3;
        pfStack_100 = pfVar3;
        pfStack_f8 = pfStack_fc;
        puStack_f0 = puStack_f4;
      }
    }
    else {
      for (iVar5 = 2; iVar5 < 4; iVar5 = iVar5 + 1) {
        *pfVar3 = in_zero_lo;
        pfVar3[1] = in_zero_hi;
        pfVar3[2] = in_zero_udw;
        pfVar3[3] = in_register_0000000c;
        iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
        pfStack_10c = *(float **)(iStack_10 + 0x88);
        *pfStack_10c = in_zero_lo;
        pfStack_10c[1] = in_zero_hi;
        pfStack_10c[2] = in_zero_udw;
        pfStack_10c[3] = in_register_0000000c;
        iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
        pfStack_114 = *(float **)(iStack_10 + 0x88);
        *pfStack_114 = in_zero_lo;
        pfStack_114[1] = in_zero_hi;
        pfStack_114[2] = in_zero_udw;
        pfStack_114[3] = in_register_0000000c;
        pfStack_114[3] = 4.59177e-41;
        iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
        pfVar3 = *(float **)(iStack_10 + 0x88);
        pfStack_11c = pfVar3;
        pfStack_118 = pfVar3;
        pfStack_110 = pfStack_114;
        pfStack_108 = pfStack_10c;
      }
    }
    iVar2 = iVar2 + 0xf0;
  }
  for (iVar2 = iStack_10->i32_1f4; iVar2 < iStack_10->i32_1f8; iVar2 = iVar2 + 1) {
    for (iVar4 = 2; iVar4 < 4; iVar4 = iVar4 + 1) {
      *pfVar3 = in_zero_lo;
      pfVar3[1] = in_zero_hi;
      pfVar3[2] = in_zero_udw;
      pfVar3[3] = in_register_0000000c;
      iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
      pfVar3 = *(float **)(iStack_10 + 0x88);
      *pfVar3 = in_zero_lo;
      pfVar3[1] = in_zero_hi;
      pfVar3[2] = in_zero_udw;
      pfVar3[3] = in_register_0000000c;
      iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
      pfVar3 = *(float **)(iStack_10 + 0x88);
      *pfVar3 = in_zero_lo;
      pfVar3[1] = in_zero_hi;
      pfVar3[2] = in_zero_udw;
      pfVar3[3] = in_register_0000000c;
      pfVar3[3] = 4.59177e-41;
      iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
      pfVar3 = *(float **)(iStack_10 + 0x88);
    }
  }
  return;
}

// JP: 0x002b4810  __ct__13FpObjectTnderFiPv  =  FpObjectTnder::FpObjectTnder
int FpObjectTnder::FpObjectTnder(int this,undefined4 param_2,undefined4 param_3)

{
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  int iVar1;
  undefined4 *puVar2;
  
  FpObject::FpObject(this,param_2,param_3);
  *(undefined1 **)(this + 0x1e4) = FpObjectTnder::__vt;
  this->u32_210 = in_zero_lo;
  this->u32_214 = in_zero_hi;
  this->u32_218 = in_zero_udw;
  this->u32_21c = in_register_0000000c;
  puVar2 = (undefined4 *)(this + 0x220);
  do {
    *puVar2 = in_zero_lo;
    puVar2[1] = in_zero_hi;
    puVar2[2] = in_zero_udw;
    puVar2[3] = in_register_0000000c;
    puVar2 = puVar2 + 4;
  } while (puVar2 != (undefined4 *)(this + 0x260));
  this->u32_260 = in_zero_lo;
  this->u32_264 = in_zero_hi;
  this->u32_268 = in_zero_udw;
  this->u32_26c = in_register_0000000c;
  this->u32_270 = in_zero_lo;
  this->u32_274 = in_zero_hi;
  this->u32_278 = in_zero_udw;
  this->u32_27c = in_register_0000000c;
  this->u32_280 = in_zero_lo;
  this->u32_284 = in_zero_hi;
  this->u32_288 = in_zero_udw;
  this->u32_28c = in_register_0000000c;
  this->u8_294 = 0;
  iVar1 = rand();
  this->f32_298 = (float)iVar1 / 2.1474836e+09;
  return this;
}

// JP: 0x002b48e0  __dt__13FpObjectTnderFv  =  FpObjectTnder::~FpObjectTnder
int FpObjectTnder::~FpObjectTnder(int this,short param_2)

{
  if (this != 0) {
    *(undefined1 **)(this + 0x1e4) = FpObjectTnder::__vt;
    FpObject::~FpObject(this,0);
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}

// JP: 0x002b4960  Init__13FpObjectTnderFib  =  FpObjectTnder::Init
void FpObjectTnder::Init(undefined8 this,undefined4 param_2,long param_3)

{
  undefined4 uVar1;
  int iVar2;
  undefined8 uVar3;
  int this;
  undefined1 auStack_40 [40];
  undefined4 uStack_18;
  undefined4 uStack_14;
  
  
  this->u32_1f4 = param_2;
  this->u32_1f8 = param_2;
  iVar2 = this->i32_1f8;
  uVar3 = __nwa(iVar2 * 0xf0 + 0x10);
  uVar1 = __construct_new_array(uVar3,0x299b50,0,0xf0,iVar2);
  this->u32_1fc = uVar1;
  memset(*(void **)(this + 0x1fc),0,(long)(this->i32_1f8 * 0xf0));
  iVar2 = rand();
  this->f32_298 = (float)iVar2 / 2.1474836e+09;
  Matrix::Matrix(auStack_40,CApp::camera + 0x240);
  this->i32_260 = (int)auStack_40._32_8_;
  this->i32_264 = SUB84(auStack_40._32_8_,4);
  this->u32_268 = uStack_18;
  this->u32_26c = uStack_14;
  for (iVar2 = 0; iVar2 < this->i32_1f8; iVar2 = iVar2 + 1) {
    (**(code **)(this->i32_1e4 + 0x4c))(this,iVar2,1);
  }
  FpObjectTnder::CreateVertex(this);
  this->u32_1e0 = 0xffffffff;
  this->u16_14 = this->u16_14 & 0xe01f;
  if (param_3 == 0) {
    PutiObject::SetRegTest(this,0x33001);
  }
  else {
    PutiObject::SetRegTest(this,0x73001);
  }
  return;
}

// JP: 0x002b4b00  CreateData__13FpObjectTnderFib  =  FpObjectTnder::CreateData
void FpObjectTnder::CreateData(void)

{
  return;
}

// JP: 0x002b4b10  CalculateFunc__13FpObjectTnderFv  =  FpObjectTnder::CalculateFunc
void FpObjectTnder::CalculateFunc(undefined8 this)

{
  int iVar1;
  int iVar2;
  int this;
  float fVar4;
  undefined1 auStack_40 [40];
  undefined4 uStack_18;
  undefined4 uStack_14;
  
  
  fVar4 = (float)FpPrim::GetFrameSpeed(this->u32_8);
  iVar1 = rand();
  this->f32_298 = (float)iVar1 / 2.1474836e+09;
  iVar1 = this->i32_1fc;
  for (iVar2 = 0; iVar2 < this->i32_1f8; iVar2 = iVar2 + 1) {
    iVar1->f32_4 = iVar1->f32_4 + fVar4;
    iVar1 = iVar1 + 0xf0;
  }
  if (**(float **)(this + 0x1fc) <= *(float *)(this->i32_1fc + 4)) {
    Matrix::Matrix(auStack_40,CApp::camera + 0x240);
    this->i32_260 = (int)auStack_40._32_8_;
    this->i32_264 = SUB84(auStack_40._32_8_,4);
    this->u32_268 = uStack_18;
    this->u32_26c = uStack_14;
    for (iVar1 = 0; iVar1 < this->i32_1f4; iVar1 = iVar1 + 1) {
      (**(code **)(this->i32_1e4 + 0x4c))(this,iVar1,0);
    }
    FpObjectTnder::CreateVertex(this);
  }
  this->i32_90 = this->i32_90 + 1;
  if (0x168 < this->i32_90) {
    this->i32_90 = this->i32_90 + -0x168;
  }
  return;
}

// JP: 0x002b4c70  CreateVertex__13FpObjectTnderFv  =  FpObjectTnder::CreateVertex
void FpObjectTnder::CreateVertex(int this)

{
  undefined1 auVar1 [16];
  undefined1 auVar2 [16];
  undefined1 auVar3 [16];
  undefined1 auVar4 [16];
  undefined1 auVar5 [16];
  undefined1 auVar6 [16];
  undefined1 auVar7 [16];
  undefined1 auVar8 [16];
  undefined1 auVar9 [16];
  undefined1 auVar10 [16];
  undefined1 auVar11 [16];
  undefined1 auVar12 [16];
  undefined1 auVar13 [16];
  undefined1 auVar14 [16];
  int iVar15;
  int iVar16;
  undefined1 auVar17 [16];
  undefined1 auVar18 [16];
  undefined1 auStack_620 [16];
  undefined1 auStack_610 [16];
  undefined1 auStack_600 [16];
  undefined1 auStack_5f0 [16];
  undefined1 auStack_5e0 [16];
  undefined1 auStack_5d0 [16];
  undefined1 auStack_5c0 [16];
  undefined1 auStack_5b0 [16];
  undefined1 auStack_5a0 [16];
  undefined1 auStack_590 [16];
  undefined1 auStack_580 [16];
  undefined1 auStack_570 [16];
  undefined1 auStack_560 [16];
  undefined1 auStack_550 [16];
  undefined1 auStack_540 [16];
  undefined1 auStack_530 [16];
  undefined1 auStack_520 [16];
  undefined1 auStack_510 [16];
  undefined1 auStack_500 [16];
  undefined1 auStack_4f0 [16];
  undefined1 auStack_4e0 [16];
  undefined1 auStack_4d0 [16];
  undefined1 auStack_4c0 [16];
  undefined1 auStack_4b0 [16];
  undefined1 auStack_4a0 [16];
  undefined1 auStack_490 [16];
  undefined1 auStack_480 [16];
  undefined1 auStack_470 [16];
  undefined1 auStack_460 [16];
  undefined1 auStack_450 [16];
  undefined1 auStack_440 [16];
  undefined1 auStack_430 [16];
  undefined1 auStack_420 [16];
  undefined1 auStack_410 [16];
  undefined1 auStack_400 [16];
  undefined1 auStack_3f0 [16];
  undefined1 auStack_3e0 [16];
  undefined1 auStack_3d0 [16];
  undefined1 auStack_3c0 [16];
  undefined1 auStack_3b0 [16];
  undefined1 auStack_3a0 [16];
  undefined1 auStack_390 [16];
  undefined1 auStack_380 [16];
  undefined1 auStack_370 [16];
  undefined1 auStack_360 [16];
  undefined1 auStack_350 [16];
  undefined1 auStack_340 [16];
  undefined1 auStack_330 [8];
  undefined4 uStack_328;
  undefined4 uStack_324;
  undefined1 auStack_320 [16];
  undefined1 auStack_310 [8];
  undefined4 uStack_308;
  undefined4 uStack_304;
  undefined1 auStack_300 [16];
  undefined1 auStack_2f0 [16];
  undefined1 auStack_2e0 [8];
  undefined4 uStack_2d8;
  undefined4 uStack_2d4;
  undefined1 auStack_2d0 [16];
  undefined1 auStack_2c0 [16];
  undefined1 auStack_2b0 [8];
  undefined4 uStack_2a8;
  undefined4 uStack_2a4;
  undefined1 auStack_2a0 [8];
  undefined4 uStack_298;
  undefined4 uStack_294;
  undefined1 auStack_290 [8];
  undefined4 uStack_288;
  undefined4 uStack_284;
  undefined1 auStack_280 [8];
  undefined4 uStack_278;
  undefined4 uStack_274;
  undefined1 auStack_270 [16];
  undefined1 auStack_260 [8];
  undefined4 uStack_258;
  undefined4 uStack_254;
  undefined1 auStack_250 [16];
  undefined1 auStack_240 [8];
  undefined4 uStack_238;
  undefined4 uStack_234;
  undefined1 auStack_230 [16];
  undefined1 auStack_220 [16];
  undefined1 auStack_210 [8];
  undefined4 uStack_208;
  undefined4 uStack_204;
  undefined1 auStack_200 [16];
  undefined1 auStack_1f0 [16];
  undefined1 auStack_1e0 [8];
  undefined4 uStack_1d8;
  undefined4 uStack_1d4;
  undefined1 auStack_1d0 [8];
  undefined4 uStack_1c8;
  undefined4 uStack_1c4;
  undefined1 auStack_1c0 [8];
  undefined4 uStack_1b8;
  undefined4 uStack_1b4;
  undefined1 auStack_1b0 [16];
  undefined1 auStack_1a0 [8];
  undefined4 uStack_198;
  undefined4 uStack_194;
  undefined1 auStack_190 [16];
  undefined1 auStack_180 [8];
  undefined4 uStack_178;
  undefined4 uStack_174;
  undefined1 auStack_170 [16];
  undefined1 auStack_160 [16];
  undefined1 auStack_150 [8];
  undefined4 uStack_148;
  undefined4 uStack_144;
  undefined1 auStack_140 [16];
  undefined1 auStack_130 [16];
  undefined1 auStack_120 [8];
  undefined4 uStack_118;
  undefined4 uStack_114;
  undefined1 auStack_110 [8];
  undefined4 uStack_108;
  undefined4 uStack_104;
  undefined1 auStack_100 [8];
  undefined4 uStack_f8;
  undefined4 uStack_f4;
  undefined1 auStack_f0 [16];
  undefined1 auStack_e0 [8];
  undefined4 uStack_d8;
  undefined4 uStack_d4;
  undefined1 auStack_d0 [16];
  undefined1 auStack_c0 [8];
  undefined4 uStack_b8;
  undefined4 uStack_b4;
  undefined1 auStack_b0 [16];
  undefined1 auStack_a0 [16];
  undefined1 auStack_90 [8];
  undefined4 uStack_88;
  undefined4 uStack_84;
  undefined1 auStack_80 [16];
  undefined1 auStack_70 [16];
  undefined1 auStack_60 [8];
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined1 auStack_50 [8];
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined1 auStack_40 [8];
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined1 auStack_30 [8];
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  if (this->i8_294 == '\0') {
    auVar17 = _lqc2(*(undefined1 (*) [16])(this->i32_1fc + 0x30));
    auVar18 = _lqc2(*(undefined1 (*) [16])(this + 0x210));
    auVar17 = _vsub(auVar17,auVar18);
    auStack_360 = _sqc2(auVar17);
    FVector::FVector(auStack_40,auStack_360);
    uStack_10 = auStack_40._0_4_;
    uStack_c = auStack_40._4_4_;
    uStack_8 = uStack_38;
    uStack_4 = uStack_34;
  }
  else {
    auVar17 = _lqc2(*(undefined1 (*) [16])(this->i32_1fc + 0x30));
    auVar18 = _lqc2(*(undefined1 (*) [16])
                     (this->i32_1fc + (this->i32_1f4 + -1) * 0xf0 + 0x30));
    auVar17 = _vsub(auVar17,auVar18);
    auStack_350 = _sqc2(auVar17);
    FVector::FVector(auStack_30,auStack_350);
    uStack_10 = auStack_30._0_4_;
    uStack_c = auStack_30._4_4_;
    uStack_8 = uStack_28;
    uStack_4 = uStack_24;
  }
  FVector::OuterProduct(auStack_50,&uStack_10,this + 0x260);
  uStack_20 = auStack_50._0_4_;
  uStack_1c = auStack_50._4_4_;
  uStack_18 = uStack_48;
  uStack_14 = uStack_44;
  FVector::Normalize(&uStack_20);
  auVar17._4_4_ = uStack_1c;
  auVar17._0_4_ = uStack_20;
  auVar17._8_4_ = uStack_18;
  auVar17._12_4_ = uStack_14;
  auVar17 = _lqc2(auVar17);
  auVar18 = _qmtc2(-this->f32_290);
  auVar17 = _vmulbc(auVar17,auVar18);
  auStack_5b0 = _sqc2(auVar17);
  FVector::FVector(auStack_80,auStack_5b0);
  auVar17 = _lqc2(auStack_80);
  auVar18 = _qmtc2(0x40400000);
  auVar17 = _vmulbc(auVar17,auVar18);
  auStack_4b0 = _sqc2(auVar17);
  FVector::FVector(auStack_70,auStack_4b0);
  auVar17 = _lqc2(*(undefined1 (*) [16])(this + 0x210));
  auVar18 = _lqc2(auStack_70);
  auVar17 = _vadd(auVar17,auVar18);
  auStack_370 = _sqc2(auVar17);
  FVector::FVector(auStack_60,auStack_370);
  this->i32_220 = auStack_60._0_4_;
  this->i32_224 = auStack_60._4_4_;
  this->u32_228 = uStack_58;
  this->u32_22c = uStack_54;
  auVar18._4_4_ = uStack_1c;
  auVar18._0_4_ = uStack_20;
  auVar18._8_4_ = uStack_18;
  auVar18._12_4_ = uStack_14;
  auVar17 = _lqc2(auVar18);
  auVar18 = _qmtc2(this->u32_290);
  auVar17 = _vmulbc(auVar17,auVar18);
  auStack_5c0 = _sqc2(auVar17);
  FVector::FVector(auStack_b0,auStack_5c0);
  auVar17 = _lqc2(auStack_b0);
  auVar18 = _qmtc2(0x40400000);
  auVar17 = _vmulbc(auVar17,auVar18);
  auStack_4c0 = _sqc2(auVar17);
  FVector::FVector(auStack_a0,auStack_4c0);
  auVar17 = _lqc2(*(undefined1 (*) [16])(this + 0x210));
  auVar18 = _lqc2(auStack_a0);
  auVar17 = _vadd(auVar17,auVar18);
  auStack_380 = _sqc2(auVar17);
  FVector::FVector(auStack_90,auStack_380);
  this->i32_230 = auStack_90._0_4_;
  this->i32_234 = auStack_90._4_4_;
  this->u32_238 = uStack_88;
  this->u32_23c = uStack_84;
  auVar1._4_4_ = uStack_1c;
  auVar1._0_4_ = uStack_20;
  auVar1._8_4_ = uStack_18;
  auVar1._12_4_ = uStack_14;
  auVar17 = _lqc2(auVar1);
  auVar18 = _qmtc2(-this->f32_290);
  auVar17 = _vmulbc(auVar17,auVar18);
  auStack_4d0 = _sqc2(auVar17);
  FVector::FVector(auStack_d0,auStack_4d0);
  auVar17 = _lqc2(*(undefined1 (*) [16])(this + 0x210));
  auVar18 = _lqc2(auStack_d0);
  auVar17 = _vadd(auVar17,auVar18);
  auStack_390 = _sqc2(auVar17);
  FVector::FVector(auStack_c0,auStack_390);
  this->i32_240 = auStack_c0._0_4_;
  this->i32_244 = auStack_c0._4_4_;
  this->u32_248 = uStack_b8;
  this->u32_24c = uStack_b4;
  auVar2._4_4_ = uStack_1c;
  auVar2._0_4_ = uStack_20;
  auVar2._8_4_ = uStack_18;
  auVar2._12_4_ = uStack_14;
  auVar17 = _lqc2(auVar2);
  auVar18 = _qmtc2(this->u32_290);
  auVar17 = _vmulbc(auVar17,auVar18);
  auStack_4e0 = _sqc2(auVar17);
  FVector::FVector(auStack_f0,auStack_4e0);
  auVar17 = _lqc2(*(undefined1 (*) [16])(this + 0x210));
  auVar18 = _lqc2(auStack_f0);
  auVar17 = _vadd(auVar17,auVar18);
  auStack_3a0 = _sqc2(auVar17);
  FVector::FVector(auStack_e0,auStack_3a0);
  this->i32_250 = auStack_e0._0_4_;
  this->i32_254 = auStack_e0._4_4_;
  this->u32_258 = uStack_d8;
  this->u32_25c = uStack_d4;
  if (1 < this->i32_1f4) {
    auVar17 = _lqc2(*(undefined1 (*) [16])(this->i32_1fc + 0x120));
    auVar18 = _lqc2(*(undefined1 (*) [16])(this + 0x210));
    auVar17 = _vsub(auVar17,auVar18);
    auStack_3b0 = _sqc2(auVar17);
    FVector::FVector(auStack_100,auStack_3b0);
    uStack_10 = auStack_100._0_4_;
    uStack_c = auStack_100._4_4_;
    uStack_8 = uStack_f8;
    uStack_4 = uStack_f4;
    FVector::OuterProduct(auStack_110,&uStack_10,this + 0x260);
    uStack_20 = auStack_110._0_4_;
    uStack_1c = auStack_110._4_4_;
    uStack_18 = uStack_108;
    uStack_14 = uStack_104;
    FVector::Normalize(&uStack_20);
  }
  iVar16 = this->i32_1fc;
  auVar3._4_4_ = uStack_1c;
  auVar3._0_4_ = uStack_20;
  auVar3._8_4_ = uStack_18;
  auVar3._12_4_ = uStack_14;
  auVar17 = _lqc2(auVar3);
  auVar18 = _qmtc2(-this->f32_290);
  auVar17 = _vmulbc(auVar17,auVar18);
  auStack_5d0 = _sqc2(auVar17);
  FVector::FVector(auStack_140,auStack_5d0);
  auVar17 = _lqc2(auStack_140);
  auVar18 = _qmtc2(0x40400000);
  auVar17 = _vmulbc(auVar17,auVar18);
  auStack_4f0 = _sqc2(auVar17);
  FVector::FVector(auStack_130,auStack_4f0);
  auVar17 = _lqc2(*(undefined1 (*) [16])(iVar16 + 0x30));
  auVar18 = _lqc2(auStack_130);
  auVar17 = _vadd(auVar17,auVar18);
  auStack_3c0 = _sqc2(auVar17);
  FVector::FVector(auStack_120,auStack_3c0);
  iVar16->i32_70 = auStack_120._0_4_;
  iVar16->i32_74 = auStack_120._4_4_;
  iVar16->u32_78 = uStack_118;
  iVar16->u32_7c = uStack_114;
  auVar4._4_4_ = uStack_1c;
  auVar4._0_4_ = uStack_20;
  auVar4._8_4_ = uStack_18;
  auVar4._12_4_ = uStack_14;
  auVar17 = _lqc2(auVar4);
  auVar18 = _qmtc2(this->u32_290);
  auVar17 = _vmulbc(auVar17,auVar18);
  auStack_5e0 = _sqc2(auVar17);
  FVector::FVector(auStack_170,auStack_5e0);
  auVar17 = _lqc2(auStack_170);
  auVar18 = _qmtc2(0x40400000);
  auVar17 = _vmulbc(auVar17,auVar18);
  auStack_500 = _sqc2(auVar17);
  FVector::FVector(auStack_160,auStack_500);
  auVar17 = _lqc2(*(undefined1 (*) [16])(iVar16 + 0x30));
  auVar18 = _lqc2(auStack_160);
  auVar17 = _vadd(auVar17,auVar18);
  auStack_3d0 = _sqc2(auVar17);
  FVector::FVector(auStack_150,auStack_3d0);
  iVar16->i32_80 = auStack_150._0_4_;
  iVar16->i32_84 = auStack_150._4_4_;
  iVar16->u32_88 = uStack_148;
  iVar16->u32_8c = uStack_144;
  auVar5._4_4_ = uStack_1c;
  auVar5._0_4_ = uStack_20;
  auVar5._8_4_ = uStack_18;
  auVar5._12_4_ = uStack_14;
  auVar17 = _lqc2(auVar5);
  auVar18 = _qmtc2(-this->f32_290);
  auVar17 = _vmulbc(auVar17,auVar18);
  auStack_510 = _sqc2(auVar17);
  FVector::FVector(auStack_190,auStack_510);
  auVar17 = _lqc2(*(undefined1 (*) [16])(iVar16 + 0x30));
  auVar18 = _lqc2(auStack_190);
  auVar17 = _vadd(auVar17,auVar18);
  auStack_3e0 = _sqc2(auVar17);
  FVector::FVector(auStack_180,auStack_3e0);
  iVar16->i32_90 = auStack_180._0_4_;
  iVar16->i32_94 = auStack_180._4_4_;
  iVar16->u32_98 = uStack_178;
  iVar16->u32_9c = uStack_174;
  auVar6._4_4_ = uStack_1c;
  auVar6._0_4_ = uStack_20;
  auVar6._8_4_ = uStack_18;
  auVar6._12_4_ = uStack_14;
  auVar17 = _lqc2(auVar6);
  auVar18 = _qmtc2(this->u32_290);
  auVar17 = _vmulbc(auVar17,auVar18);
  auStack_520 = _sqc2(auVar17);
  FVector::FVector(auStack_1b0,auStack_520);
  auVar17 = _lqc2(*(undefined1 (*) [16])(iVar16 + 0x30));
  auVar18 = _lqc2(auStack_1b0);
  auVar17 = _vadd(auVar17,auVar18);
  auStack_3f0 = _sqc2(auVar17);
  FVector::FVector(auStack_1a0,auStack_3f0);
  iVar16->i32_a0 = auStack_1a0._0_4_;
  iVar16->i32_a4 = auStack_1a0._4_4_;
  iVar16->u32_a8 = uStack_198;
  iVar16->u32_ac = uStack_194;
  for (iVar15 = 1; iVar15 < this->i32_1f4 + -1; iVar15 = iVar15 + 1) {
    auVar17 = _lqc2(*(undefined1 (*) [16])(this->i32_1fc + (iVar15 + 1) * 0xf0 + 0x30));
    auVar18 = _lqc2(*(undefined1 (*) [16])(this->i32_1fc + (iVar15 + -1) * 0xf0 + 0x30))
    ;
    auVar17 = _vsub(auVar17,auVar18);
    auStack_400 = _sqc2(auVar17);
    FVector::FVector(auStack_1c0,auStack_400);
    uStack_10 = auStack_1c0._0_4_;
    uStack_c = auStack_1c0._4_4_;
    uStack_8 = uStack_1b8;
    uStack_4 = uStack_1b4;
    FVector::OuterProduct(auStack_1d0,&uStack_10,this + 0x260);
    uStack_20 = auStack_1d0._0_4_;
    uStack_1c = auStack_1d0._4_4_;
    uStack_18 = uStack_1c8;
    uStack_14 = uStack_1c4;
    FVector::Normalize(&uStack_20);
    auVar7._4_4_ = uStack_1c;
    auVar7._0_4_ = uStack_20;
    auVar7._8_4_ = uStack_18;
    auVar7._12_4_ = uStack_14;
    auVar17 = _lqc2(auVar7);
    auVar18 = _qmtc2(-this->f32_290);
    auVar17 = _vmulbc(auVar17,auVar18);
    auStack_5f0 = _sqc2(auVar17);
    FVector::FVector(auStack_200,auStack_5f0);
    auVar17 = _lqc2(auStack_200);
    auVar18 = _qmtc2(0x40400000);
    auVar17 = _vmulbc(auVar17,auVar18);
    auStack_530 = _sqc2(auVar17);
    FVector::FVector(auStack_1f0,auStack_530);
    auVar17 = _lqc2(*(undefined1 (*) [16])(iVar16 + 0x120));
    auVar18 = _lqc2(auStack_1f0);
    auVar17 = _vadd(auVar17,auVar18);
    auStack_410 = _sqc2(auVar17);
    FVector::FVector(auStack_1e0,auStack_410);
    iVar16->i32_160 = auStack_1e0._0_4_;
    iVar16->i32_164 = auStack_1e0._4_4_;
    iVar16->u32_168 = uStack_1d8;
    iVar16->u32_16c = uStack_1d4;
    auVar8._4_4_ = uStack_1c;
    auVar8._0_4_ = uStack_20;
    auVar8._8_4_ = uStack_18;
    auVar8._12_4_ = uStack_14;
    auVar17 = _lqc2(auVar8);
    auVar18 = _qmtc2(this->u32_290);
    auVar17 = _vmulbc(auVar17,auVar18);
    auStack_600 = _sqc2(auVar17);
    FVector::FVector(auStack_230,auStack_600);
    auVar17 = _lqc2(auStack_230);
    auVar18 = _qmtc2(0x40400000);
    auVar17 = _vmulbc(auVar17,auVar18);
    auStack_540 = _sqc2(auVar17);
    FVector::FVector(auStack_220,auStack_540);
    auVar17 = _lqc2(*(undefined1 (*) [16])(iVar16 + 0x120));
    auVar18 = _lqc2(auStack_220);
    auVar17 = _vadd(auVar17,auVar18);
    auStack_420 = _sqc2(auVar17);
    FVector::FVector(auStack_210,auStack_420);
    iVar16->i32_170 = auStack_210._0_4_;
    iVar16->i32_174 = auStack_210._4_4_;
    iVar16->u32_178 = uStack_208;
    iVar16->u32_17c = uStack_204;
    auVar9._4_4_ = uStack_1c;
    auVar9._0_4_ = uStack_20;
    auVar9._8_4_ = uStack_18;
    auVar9._12_4_ = uStack_14;
    auVar17 = _lqc2(auVar9);
    auVar18 = _qmtc2(-this->f32_290);
    auVar17 = _vmulbc(auVar17,auVar18);
    auStack_550 = _sqc2(auVar17);
    FVector::FVector(auStack_250,auStack_550);
    auVar17 = _lqc2(*(undefined1 (*) [16])(iVar16 + 0x120));
    auVar18 = _lqc2(auStack_250);
    auVar17 = _vadd(auVar17,auVar18);
    auStack_430 = _sqc2(auVar17);
    FVector::FVector(auStack_240,auStack_430);
    iVar16->i32_180 = auStack_240._0_4_;
    iVar16->i32_184 = auStack_240._4_4_;
    iVar16->u32_188 = uStack_238;
    iVar16->u32_18c = uStack_234;
    auVar10._4_4_ = uStack_1c;
    auVar10._0_4_ = uStack_20;
    auVar10._8_4_ = uStack_18;
    auVar10._12_4_ = uStack_14;
    auVar17 = _lqc2(auVar10);
    auVar18 = _qmtc2(this->u32_290);
    auVar17 = _vmulbc(auVar17,auVar18);
    auStack_560 = _sqc2(auVar17);
    FVector::FVector(auStack_270,auStack_560);
    auVar17 = _lqc2(*(undefined1 (*) [16])(iVar16 + 0x120));
    auVar18 = _lqc2(auStack_270);
    auVar17 = _vadd(auVar17,auVar18);
    auStack_440 = _sqc2(auVar17);
    FVector::FVector(auStack_260,auStack_440);
    iVar16->i32_190 = auStack_260._0_4_;
    iVar16->i32_194 = auStack_260._4_4_;
    iVar16->u32_198 = uStack_258;
    iVar16->u32_19c = uStack_254;
    iVar16 = iVar16 + 0xf0;
  }
  if (this->i8_294 == '\0') {
    auVar17 = _lqc2(*(undefined1 (*) [16])
                     (this->i32_1fc + (this->i32_1f4 + -1) * 0xf0 + 0x30));
    auVar18 = _lqc2(*(undefined1 (*) [16])
                     (this->i32_1fc + (this->i32_1f4 + -2) * 0xf0 + 0x30));
    auVar17 = _vsub(auVar17,auVar18);
    auStack_460 = _sqc2(auVar17);
    FVector::FVector(auStack_290,auStack_460);
    uStack_10 = auStack_290._0_4_;
    uStack_c = auStack_290._4_4_;
    uStack_8 = uStack_288;
    uStack_4 = uStack_284;
  }
  else {
    auVar17 = _lqc2(*(undefined1 (*) [16])(this->i32_1fc + 0x30));
    auVar18 = _lqc2(*(undefined1 (*) [16])
                     (this->i32_1fc + (this->i32_1f4 + -1) * 0xf0 + 0x30));
    auVar17 = _vsub(auVar17,auVar18);
    auStack_450 = _sqc2(auVar17);
    FVector::FVector(auStack_280,auStack_450);
    uStack_10 = auStack_280._0_4_;
    uStack_c = auStack_280._4_4_;
    uStack_8 = uStack_278;
    uStack_4 = uStack_274;
  }
  FVector::OuterProduct(auStack_2a0,&uStack_10,this + 0x260);
  uStack_20 = auStack_2a0._0_4_;
  uStack_1c = auStack_2a0._4_4_;
  uStack_18 = uStack_298;
  uStack_14 = uStack_294;
  FVector::Normalize(&uStack_20);
  iVar16 = this->i32_1fc + (this->i32_1f4 + -1) * 0xf0;
  auVar11._4_4_ = uStack_1c;
  auVar11._0_4_ = uStack_20;
  auVar11._8_4_ = uStack_18;
  auVar11._12_4_ = uStack_14;
  auVar17 = _lqc2(auVar11);
  auVar18 = _qmtc2(-this->f32_290);
  auVar17 = _vmulbc(auVar17,auVar18);
  auStack_610 = _sqc2(auVar17);
  FVector::FVector(auStack_2d0,auStack_610);
  auVar17 = _lqc2(auStack_2d0);
  auVar18 = _qmtc2(0x40400000);
  auVar17 = _vmulbc(auVar17,auVar18);
  auStack_570 = _sqc2(auVar17);
  FVector::FVector(auStack_2c0,auStack_570);
  auVar17 = _lqc2(*(undefined1 (*) [16])(iVar16 + 0x30));
  auVar18 = _lqc2(auStack_2c0);
  auVar17 = _vadd(auVar17,auVar18);
  auStack_470 = _sqc2(auVar17);
  FVector::FVector(auStack_2b0,auStack_470);
  iVar16->i32_70 = auStack_2b0._0_4_;
  iVar16->i32_74 = auStack_2b0._4_4_;
  iVar16->u32_78 = uStack_2a8;
  iVar16->u32_7c = uStack_2a4;
  auVar12._4_4_ = uStack_1c;
  auVar12._0_4_ = uStack_20;
  auVar12._8_4_ = uStack_18;
  auVar12._12_4_ = uStack_14;
  auVar17 = _lqc2(auVar12);
  auVar18 = _qmtc2(this->u32_290);
  auVar17 = _vmulbc(auVar17,auVar18);
  auStack_620 = _sqc2(auVar17);
  FVector::FVector(auStack_300,auStack_620);
  auVar17 = _lqc2(auStack_300);
  auVar18 = _qmtc2(0x40400000);
  auVar17 = _vmulbc(auVar17,auVar18);
  auStack_580 = _sqc2(auVar17);
  FVector::FVector(auStack_2f0,auStack_580);
  auVar17 = _lqc2(*(undefined1 (*) [16])(iVar16 + 0x30));
  auVar18 = _lqc2(auStack_2f0);
  auVar17 = _vadd(auVar17,auVar18);
  auStack_480 = _sqc2(auVar17);
  FVector::FVector(auStack_2e0,auStack_480);
  iVar16->i32_80 = auStack_2e0._0_4_;
  iVar16->i32_84 = auStack_2e0._4_4_;
  iVar16->u32_88 = uStack_2d8;
  iVar16->u32_8c = uStack_2d4;
  auVar13._4_4_ = uStack_1c;
  auVar13._0_4_ = uStack_20;
  auVar13._8_4_ = uStack_18;
  auVar13._12_4_ = uStack_14;
  auVar17 = _lqc2(auVar13);
  auVar18 = _qmtc2(-this->f32_290);
  auVar17 = _vmulbc(auVar17,auVar18);
  auStack_590 = _sqc2(auVar17);
  FVector::FVector(auStack_320,auStack_590);
  auVar17 = _lqc2(*(undefined1 (*) [16])(iVar16 + 0x30));
  auVar18 = _lqc2(auStack_320);
  auVar17 = _vadd(auVar17,auVar18);
  auStack_490 = _sqc2(auVar17);
  FVector::FVector(auStack_310,auStack_490);
  iVar16->i32_90 = auStack_310._0_4_;
  iVar16->i32_94 = auStack_310._4_4_;
  iVar16->u32_98 = uStack_308;
  iVar16->u32_9c = uStack_304;
  auVar14._4_4_ = uStack_1c;
  auVar14._0_4_ = uStack_20;
  auVar14._8_4_ = uStack_18;
  auVar14._12_4_ = uStack_14;
  auVar17 = _lqc2(auVar14);
  auVar18 = _qmtc2(this->u32_290);
  auVar17 = _vmulbc(auVar17,auVar18);
  auStack_5a0 = _sqc2(auVar17);
  FVector::FVector(auStack_340,auStack_5a0);
  auVar17 = _lqc2(*(undefined1 (*) [16])(iVar16 + 0x30));
  auVar18 = _lqc2(auStack_340);
  auVar17 = _vadd(auVar17,auVar18);
  auStack_4a0 = _sqc2(auVar17);
  FVector::FVector(auStack_330,auStack_4a0);
  iVar16->i32_a0 = auStack_330._0_4_;
  iVar16->i32_a4 = auStack_330._4_4_;
  iVar16->u32_a8 = uStack_328;
  iVar16->u32_ac = uStack_324;
  return;
}

// JP: 0x002b59b0  SetPacket__13FpObjectTnderFv  =  FpObjectTnder::SetPacket
void FpObjectTnder::SetPacket(int this)

{
  undefined4 *puVar1;
  int in_zero_lo;
  int in_zero_hi;
  int in_zero_udw;
  int in_register_0000000c;
  int iVar2;
  float *pfVar3;
  int iVar4;
  int iVar5;
  float fVar6;
  uint uVar7;
  int iStack_d0;
  int iStack_cc;
  int iStack_c8;
  int iStack_c4;
  int *piStack_bc;
  uint *puStack_b8;
  uint *puStack_b4;
  float *pfStack_b0;
  float *pfStack_ac;
  int *piStack_a8;
  int *piStack_a4;
  uint *puStack_a0;
  uint *puStack_9c;
  undefined4 *puStack_98;
  undefined4 *puStack_94;
  int *piStack_90;
  int *piStack_8c;
  uint *puStack_88;
  uint *puStack_84;
  float *pfStack_80;
  float *pfStack_7c;
  int *piStack_78;
  int *piStack_74;
  uint *puStack_70;
  uint *puStack_6c;
  float *pfStack_68;
  float *pfStack_64;
  int *piStack_60;
  int *piStack_5c;
  uint *puStack_58;
  uint *puStack_54;
  undefined4 *puStack_50;
  undefined4 *puStack_4c;
  int *piStack_48;
  int *piStack_44;
  uint *puStack_40;
  uint *puStack_3c;
  undefined4 *puStack_38;
  undefined4 *puStack_34;
  ulong *puStack_30;
  ulong *puStack_2c;
  int *piStack_28;
  uint uStack_24;
  float fStack_20;
  uint uStack_1c;
  float fStack_18;
  float fStack_14;
  int iStack_10;
  
  piStack_28 = *(int **)(this + 0x88);
  *piStack_28 = in_zero_lo;
  piStack_28[1] = in_zero_hi;
  piStack_28[2] = in_zero_udw;
  piStack_28[3] = in_register_0000000c;
  *piStack_28 = (int)(&DAT_10000001 + (this->i32_1f4 + 1) * 0xc);
  piStack_28[3] = (this->i32_1f4 + 1) * 0xc + 1U | 0x50000000;
  this->i32_88 = this->i32_88 + 0x10;
  puStack_30 = *(ulong **)(this + 0x88);
  *puStack_30 = (long)((this->i32_1f4 + 1) * 4) | 0x302e400000008000;
  puStack_30[1] = 0x412;
  this->i32_88 = this->i32_88 + 0x10;
  puVar1 = *(undefined4 **)(this + 0x88);
  iStack_d0 = in_zero_lo;
  iStack_cc = in_zero_hi;
  iStack_c8 = in_zero_udw;
  puStack_38 = puVar1;
  puStack_34 = puVar1;
  puStack_2c = puStack_30;
  iStack_10 = this;
  fStack_14 = (float)PutiObject::RotTransPer(this,this + 0x220,&iStack_d0);
  PutiObject::ClipFlag(iStack_10);
  *puVar1 = 0;
  puVar1[1] = 0;
  puVar1[2] = fStack_14;
  iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
  puStack_40 = *(uint **)(iStack_10 + 0x88);
  fVar6 = iStack_10->f32_270;
  if (fVar6 < 2.1474836e+09) {
    uVar7 = (uint)fVar6;
  }
  else {
    uVar7 = (int)(fVar6 - 2.1474836e+09) | 0x80000000;
  }
  *puStack_40 = uVar7;
  fVar6 = iStack_10->f32_274;
  if (fVar6 < 2.1474836e+09) {
    uVar7 = (uint)fVar6;
  }
  else {
    uVar7 = (int)(fVar6 - 2.1474836e+09) | 0x80000000;
  }
  puStack_40[1] = uVar7;
  fVar6 = iStack_10->f32_278;
  if (fVar6 < 2.1474836e+09) {
    uVar7 = (uint)fVar6;
  }
  else {
    uVar7 = (int)(fVar6 - 2.1474836e+09) | 0x80000000;
  }
  puStack_40[2] = uVar7;
  puStack_40[3] = 0;
  if (iStack_10->i8_294 != '\0') {
    fVar6 = iStack_10->f32_27c * *(float *)(iStack_10->i32_1fc + 0xbc);
    if (fVar6 < 2.1474836e+09) {
      uVar7 = (uint)fVar6;
    }
    else {
      uVar7 = (int)(fVar6 - 2.1474836e+09) | 0x80000000;
    }
    puStack_40[3] = uVar7;
  }
  iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
  piStack_48 = *(int **)(iStack_10 + 0x88);
  iStack_c4 = 0x8000;
  *piStack_48 = iStack_d0;
  piStack_48[1] = iStack_cc;
  piStack_48[2] = iStack_c8;
  piStack_48[3] = 0x8000;
  iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
  puVar1 = *(undefined4 **)(iStack_10 + 0x88);
  puStack_50 = puVar1;
  puStack_4c = puVar1;
  piStack_44 = piStack_48;
  puStack_3c = puStack_40;
  fStack_14 = (float)PutiObject::RotTransPer
                               (iStack_10,iStack_10 + 0x230,&iStack_d0);
  PutiObject::ClipFlag(iStack_10);
  *puVar1 = fStack_14;
  puVar1[1] = 0;
  puVar1[2] = fStack_14;
  iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
  puStack_58 = *(uint **)(iStack_10 + 0x88);
  fVar6 = iStack_10->f32_270;
  if (fVar6 < 2.1474836e+09) {
    uVar7 = (uint)fVar6;
  }
  else {
    uVar7 = (int)(fVar6 - 2.1474836e+09) | 0x80000000;
  }
  *puStack_58 = uVar7;
  fVar6 = iStack_10->f32_274;
  if (fVar6 < 2.1474836e+09) {
    uVar7 = (uint)fVar6;
  }
  else {
    uVar7 = (int)(fVar6 - 2.1474836e+09) | 0x80000000;
  }
  puStack_58[1] = uVar7;
  fVar6 = iStack_10->f32_278;
  if (fVar6 < 2.1474836e+09) {
    uVar7 = (uint)fVar6;
  }
  else {
    uVar7 = (int)(fVar6 - 2.1474836e+09) | 0x80000000;
  }
  puStack_58[2] = uVar7;
  puStack_58[3] = 0;
  if (iStack_10->i8_294 != '\0') {
    fVar6 = iStack_10->f32_27c * *(float *)(iStack_10->i32_1fc + 0xbc);
    if (fVar6 < 2.1474836e+09) {
      uVar7 = (uint)fVar6;
    }
    else {
      uVar7 = (int)(fVar6 - 2.1474836e+09) | 0x80000000;
    }
    puStack_58[3] = uVar7;
  }
  iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
  piStack_60 = *(int **)(iStack_10 + 0x88);
  iStack_c4 = 0x8000;
  *piStack_60 = iStack_d0;
  piStack_60[1] = iStack_cc;
  piStack_60[2] = iStack_c8;
  piStack_60[3] = 0x8000;
  iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
  pfVar3 = *(float **)(iStack_10 + 0x88);
  pfStack_68 = pfVar3;
  pfStack_64 = pfVar3;
  piStack_5c = piStack_60;
  puStack_54 = puStack_58;
  if (iStack_10->i32_1f4 != 0) {
    iVar4 = iStack_10->i32_1fc;
    for (iVar2 = 0; iVar2 < iStack_10->i32_1f4; iVar2 = iVar2 + 1) {
      for (iVar5 = 0; iVar5 < 2; iVar5 = iVar5 + 1) {
        fStack_18 = (float)PutiObject::RotTransPer
                                     (iStack_10,iVar4 + iVar5 * 0x10 + 0x70,&iStack_d0);
        uStack_1c = PutiObject::ClipFlag(iStack_10);
        *pfVar3 = *(float *)(iVar4 + iVar5 * 8 + 0xc0) * fStack_18;
        pfVar3[1] = *(float *)(iVar4 + iVar5 * 8 + 0xc4) * fStack_18;
        pfVar3[2] = fStack_18;
        iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
        puStack_70 = *(uint **)(iStack_10 + 0x88);
        fVar6 = iStack_10->f32_270;
        if (fVar6 < 2.1474836e+09) {
          uVar7 = (uint)fVar6;
        }
        else {
          uVar7 = (int)(fVar6 - 2.1474836e+09) | 0x80000000;
        }
        *puStack_70 = uVar7;
        fVar6 = iStack_10->f32_274;
        if (fVar6 < 2.1474836e+09) {
          uVar7 = (uint)fVar6;
        }
        else {
          uVar7 = (int)(fVar6 - 2.1474836e+09) | 0x80000000;
        }
        puStack_70[1] = uVar7;
        fVar6 = iStack_10->f32_278;
        if (fVar6 < 2.1474836e+09) {
          uVar7 = (uint)fVar6;
        }
        else {
          uVar7 = (int)(fVar6 - 2.1474836e+09) | 0x80000000;
        }
        puStack_70[2] = uVar7;
        fVar6 = iStack_10->f32_27c * iVar4->f32_bc;
        if (fVar6 < 2.1474836e+09) {
          uVar7 = (uint)fVar6;
        }
        else {
          uVar7 = (int)(fVar6 - 2.1474836e+09) | 0x80000000;
        }
        puStack_70[3] = uVar7;
        if ((iStack_10->i8_294 == '\0') && (iVar2 == iStack_10->i32_1f4 + -1)) {
          puStack_70[3] = 0;
        }
        iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
        piStack_78 = *(int **)(iStack_10 + 0x88);
        if ((uStack_1c & 0x3ffff) != 0) {
          iStack_c4 = 0x8000;
        }
        *piStack_78 = iStack_d0;
        piStack_78[1] = iStack_cc;
        piStack_78[2] = iStack_c8;
        piStack_78[3] = iStack_c4;
        iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
        pfVar3 = *(float **)(iStack_10 + 0x88);
        pfStack_80 = pfVar3;
        pfStack_7c = pfVar3;
        piStack_74 = piStack_78;
        puStack_6c = puStack_70;
      }
      iVar4 = iVar4 + 0xf0;
    }
  }
  fStack_14 = (float)PutiObject::RotTransPer
                               (iStack_10,iStack_10 + 0x240,&iStack_d0);
  PutiObject::ClipFlag(iStack_10);
  *pfVar3 = 0.0;
  pfVar3[1] = 0.0;
  pfVar3[2] = fStack_14;
  iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
  puStack_88 = *(uint **)(iStack_10 + 0x88);
  fVar6 = iStack_10->f32_280;
  if (fVar6 < 2.1474836e+09) {
    uVar7 = (uint)fVar6;
  }
  else {
    uVar7 = (int)(fVar6 - 2.1474836e+09) | 0x80000000;
  }
  *puStack_88 = uVar7;
  fVar6 = iStack_10->f32_284;
  if (fVar6 < 2.1474836e+09) {
    uVar7 = (uint)fVar6;
  }
  else {
    uVar7 = (int)(fVar6 - 2.1474836e+09) | 0x80000000;
  }
  puStack_88[1] = uVar7;
  fVar6 = iStack_10->f32_288;
  if (fVar6 < 2.1474836e+09) {
    uVar7 = (uint)fVar6;
  }
  else {
    uVar7 = (int)(fVar6 - 2.1474836e+09) | 0x80000000;
  }
  puStack_88[2] = uVar7;
  puStack_88[3] = 0;
  if (iStack_10->i8_294 != '\0') {
    fVar6 = iStack_10->f32_28c * *(float *)(iStack_10->i32_1fc + 0xbc);
    if (fVar6 < 2.1474836e+09) {
      uVar7 = (uint)fVar6;
    }
    else {
      uVar7 = (int)(fVar6 - 2.1474836e+09) | 0x80000000;
    }
    puStack_88[3] = uVar7;
  }
  iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
  piStack_90 = *(int **)(iStack_10 + 0x88);
  iStack_c4 = 0x8000;
  *piStack_90 = iStack_d0;
  piStack_90[1] = iStack_cc;
  piStack_90[2] = iStack_c8;
  piStack_90[3] = 0x8000;
  iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
  puVar1 = *(undefined4 **)(iStack_10 + 0x88);
  puStack_98 = puVar1;
  puStack_94 = puVar1;
  piStack_8c = piStack_90;
  puStack_84 = puStack_88;
  fStack_14 = (float)PutiObject::RotTransPer
                               (iStack_10,iStack_10 + 0x250,&iStack_d0);
  PutiObject::ClipFlag(iStack_10);
  *puVar1 = fStack_14;
  puVar1[1] = 0;
  puVar1[2] = fStack_14;
  iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
  puStack_a0 = *(uint **)(iStack_10 + 0x88);
  fVar6 = iStack_10->f32_280;
  if (fVar6 < 2.1474836e+09) {
    uVar7 = (uint)fVar6;
  }
  else {
    uVar7 = (int)(fVar6 - 2.1474836e+09) | 0x80000000;
  }
  *puStack_a0 = uVar7;
  fVar6 = iStack_10->f32_284;
  if (fVar6 < 2.1474836e+09) {
    uVar7 = (uint)fVar6;
  }
  else {
    uVar7 = (int)(fVar6 - 2.1474836e+09) | 0x80000000;
  }
  puStack_a0[1] = uVar7;
  fVar6 = iStack_10->f32_288;
  if (fVar6 < 2.1474836e+09) {
    uVar7 = (uint)fVar6;
  }
  else {
    uVar7 = (int)(fVar6 - 2.1474836e+09) | 0x80000000;
  }
  puStack_a0[2] = uVar7;
  puStack_a0[3] = 0;
  if (iStack_10->i8_294 != '\0') {
    fVar6 = iStack_10->f32_28c * *(float *)(iStack_10->i32_1fc + 0xbc);
    if (fVar6 < 2.1474836e+09) {
      uVar7 = (uint)fVar6;
    }
    else {
      uVar7 = (int)(fVar6 - 2.1474836e+09) | 0x80000000;
    }
    puStack_a0[3] = uVar7;
  }
  iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
  piStack_a8 = *(int **)(iStack_10 + 0x88);
  iStack_c4 = 0x8000;
  *piStack_a8 = iStack_d0;
  piStack_a8[1] = iStack_cc;
  piStack_a8[2] = iStack_c8;
  piStack_a8[3] = 0x8000;
  iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
  pfVar3 = *(float **)(iStack_10 + 0x88);
  if (iStack_10->i32_1f4 != 0) {
    iVar4 = iStack_10->i32_1fc;
    pfStack_b0 = pfVar3;
    pfStack_ac = pfVar3;
    piStack_a4 = piStack_a8;
    puStack_9c = puStack_a0;
    for (iVar2 = 0; iVar2 < iStack_10->i32_1f4; iVar2 = iVar2 + 1) {
      for (iVar5 = 2; iVar5 < 4; iVar5 = iVar5 + 1) {
        fStack_20 = (float)PutiObject::RotTransPer
                                     (iStack_10,iVar4 + iVar5 * 0x10 + 0x70,&iStack_d0);
        uStack_24 = PutiObject::ClipFlag(iStack_10);
        *pfVar3 = *(float *)(iVar4 + iVar5 * 8 + 0xc0) * fStack_20;
        pfVar3[1] = *(float *)(iVar4 + iVar5 * 8 + 0xc4) * fStack_20;
        pfVar3[2] = fStack_20;
        iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
        puStack_b8 = *(uint **)(iStack_10 + 0x88);
        fVar6 = iStack_10->f32_280;
        if (fVar6 < 2.1474836e+09) {
          uVar7 = (uint)fVar6;
        }
        else {
          uVar7 = (int)(fVar6 - 2.1474836e+09) | 0x80000000;
        }
        *puStack_b8 = uVar7;
        fVar6 = iStack_10->f32_284;
        if (fVar6 < 2.1474836e+09) {
          uVar7 = (uint)fVar6;
        }
        else {
          uVar7 = (int)(fVar6 - 2.1474836e+09) | 0x80000000;
        }
        puStack_b8[1] = uVar7;
        fVar6 = iStack_10->f32_288;
        if (fVar6 < 2.1474836e+09) {
          uVar7 = (uint)fVar6;
        }
        else {
          uVar7 = (int)(fVar6 - 2.1474836e+09) | 0x80000000;
        }
        puStack_b8[2] = uVar7;
        fVar6 = iStack_10->f32_28c * iVar4->f32_bc;
        if (fVar6 < 2.1474836e+09) {
          uVar7 = (uint)fVar6;
        }
        else {
          uVar7 = (int)(fVar6 - 2.1474836e+09) | 0x80000000;
        }
        puStack_b8[3] = uVar7;
        if ((iStack_10->i8_294 == '\0') && (iVar2 == iStack_10->i32_1f4 + -1)) {
          puStack_b8[3] = 0;
        }
        iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
        piStack_bc = *(int **)(iStack_10 + 0x88);
        if ((uStack_24 & 0x3ffff) != 0) {
          iStack_c4 = 0x8000;
        }
        *piStack_bc = iStack_d0;
        piStack_bc[1] = iStack_cc;
        piStack_bc[2] = iStack_c8;
        piStack_bc[3] = iStack_c4;
        iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
        pfVar3 = *(float **)(iStack_10 + 0x88);
        puStack_b4 = puStack_b8;
      }
      iVar4 = iVar4 + 0xf0;
    }
  }
  return;
}

// JP: 0x002b6960  __ct__11FpBlackHoleFv  =  FpBlackHole::FpBlackHole
undefined8 FpBlackHole::FpBlackHole(undefined8 this)

{
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  int this;
  
  FpPrim::FpPrim(this);
  
  *(undefined1 **)(this + 0x10) = FpBlackHole::__vt;
  this->u32_1c = 0x4064c0;
  this->u32_70 = in_zero_lo;
  this->u32_74 = in_zero_hi;
  this->u32_78 = in_zero_udw;
  this->u32_7c = in_register_0000000c;
  this->u32_80 = in_zero_lo;
  this->u32_84 = in_zero_hi;
  this->u32_88 = in_zero_udw;
  this->u32_8c = in_register_0000000c;
  this->u32_70 = 0;
  this->u32_74 = 0xc2c80000;
  this->u32_78 = 0x43960000;
  this->u32_7c = 0;
  this->u32_80 = 0x43000000;
  this->u32_84 = 0x43000000;
  this->u32_88 = 0x43000000;
  this->u32_8c = 0x43000000;
  this->u32_90 = 0;
  this->u32_94 = 0;
  this->u32_98 = 0;
  this->u32_9c = 0;
  this->u32_a0 = 0;
  this->u32_a4 = 0;
  this->u32_a8 = 0;
  this->u32_ac = 0;
  this->u32_b0 = 0;
  this->u32_b4 = 0;
  return this;
}

// JP: 0x002b6ac0  __dt__11FpBlackHoleFv  =  FpBlackHole::~FpBlackHole
int FpBlackHole::~FpBlackHole(int this,short param_2)

{
  if (this != 0) {
    *(undefined1 **)(this + 0x10) = FpBlackHole::__vt;
    this->u32_1c = 0x4064c0;
    FpPrim::~FpPrim(this,0);
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}

// JP: 0x002b6b50  DelayDelete__11FpBlackHoleFv  =  FpBlackHole::DelayDelete
void FpBlackHole::DelayDelete(int this)

{
  long lVar1;
  
  if ((this->i32_b4 != 0) &&
     (lVar1 = PutiManager::FindPrim
                        (PutiManager::ourManager,*(undefined4 *)(this->i32_b4 + 0x54),
                         this->u32_b4), lVar1 != 0)) {
    PutiPrim::Delete(this->u32_b4);
  }
  DelayDeleteObject::DelayDelete(this + 0x14);
  return;
}

// JP: 0x002b6bd0  Create__11FpBlackHoleFv  =  FpBlackHole::Create
void FpBlackHole::Create(undefined8 this)

{
  undefined4 uVar1;
  long lVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  int iVar7;
  int this;
  float fVar9;
  undefined4 uVar10;
  undefined1 auStack_210 [16];
  undefined1 auStack_200 [16];
  undefined1 auStack_1f0 [16];
  undefined1 auStack_1e0 [16];
  undefined1 auStack_1d0 [16];
  undefined1 auStack_1c0 [16];
  undefined1 auStack_1b0 [16];
  undefined1 auStack_1a0 [16];
  undefined1 auStack_190 [16];
  undefined1 auStack_180 [16];
  undefined1 auStack_170 [16];
  undefined1 auStack_160 [16];
  undefined1 auStack_150 [16];
  undefined1 auStack_140 [16];
  undefined1 auStack_130 [16];
  undefined1 auStack_120 [16];
  undefined1 auStack_110 [16];
  undefined1 auStack_100 [16];
  undefined1 auStack_f0 [16];
  undefined1 auStack_e0 [16];
  undefined1 auStack_d0 [16];
  undefined1 auStack_c0 [16];
  undefined1 auStack_b0 [16];
  undefined1 auStack_a0 [16];
  undefined1 auStack_90 [16];
  undefined1 auStack_80 [16];
  undefined4 uStack_70;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  uStack_70 = 0x42480000;
  uStack_6c = 0x42500000;
  uStack_68 = 0x425c0000;
  uStack_64 = 0x428c0000;
  
  this->u32_80 = 0x42480000;
  this->u32_84 = 0x42500000;
  this->u32_88 = 0x425c0000;
  this->u32_8c = 0x428c0000;
  this->u32_90 = 0x447a0000;
  this->u32_9c = 0x40000000;
  this->u32_a0 = 0x40000000;
  this->u32_a4 = 0x3f000000;
  this->f32_a8 = this->f32_90 / 3.0;
  this->f32_ac = this->f32_90 / 3.0;
  this->u32_94 = 0x42700000;
  if (this->i8_58 == '\0') {
    this->u8_24 = this->u8_24 & 0xfe | 1;
  }
  iVar7 = BgEffectMan::eff->i32_1c + 0x8c;
  SetWhiteTex(iVar7);
  PutiPrim::SetTexture(this,iVar7,0);
  lVar2 = __nw(0x270);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = FpObjectBlackHole::FpObjectBlackHole(lVar2,0xbcc,0);
  }
  this->u32_b0 = uVar1;
  PutiPrim::AddObject(this,this->u32_b0);
  (**(code **)(*(int *)(this->i32_b0 + 0x1e4) + 0x40))
            (this->i32_b0,0xfa,this->u8_58);
  PutiPrim::SetTexture(this,BgEffectMan::eff->i32_1c + 0xdc,1);
  uStack_10 = 0;
  uStack_c = 0x42200000;
  uStack_8 = 0x42c80000;
  uStack_4 = 0x41a00000;
  uStack_20 = 0x43000000;
  uStack_1c = 0x43000000;
  uStack_18 = 0x43000000;
  uStack_14 = 0x42480000;
  lVar2 = __nw(0x2b0);
  uVar3 = 0;
  if (lVar2 != 0) {
    uVar3 = FpObjectTnderBH::FpObjectTnderBH(lVar2,0x104,0);
  }
  PutiPrim::AddObject(this,uVar3);
  uVar4 = FVector::FVector(auStack_80,&uStack_10);
  uVar5 = FVector::FVector(auStack_90,&uStack_20);
  FpObjectTnderBH::InitData
            (0x40a00000,0x42480000,0x42340000,0,0x3e99999a,uVar3,uVar4,uVar5);
  iVar7 = (int)uVar3;
  (**(code **)(iVar7->i32_1e4 + 0x40))(uVar3,0x14,this->u8_58);
  iVar7->u16_14 = iVar7->u16_14 & 0xe01f | 0x20;
  lVar2 = __nw(0x2b0);
  uVar3 = 0;
  if (lVar2 != 0) {
    uVar3 = FpObjectTnderBH::FpObjectTnderBH(lVar2,0x104,0);
  }
  PutiPrim::AddObject(this,uVar3);
  uVar4 = FVector::FVector(auStack_a0,&uStack_10);
  uVar5 = FVector::FVector(auStack_b0,&uStack_20);
  FpObjectTnderBH::InitData
            (0x40a00000,0x42480000,0x42340000,0,0x3e99999a,uVar3,uVar4,uVar5);
  iVar7 = (int)uVar3;
  (**(code **)(iVar7->i32_1e4 + 0x40))(uVar3,0x14,this->u8_58);
  iVar7->u16_14 = iVar7->u16_14 & 0xe01f | 0x20;
  lVar2 = __nw(0x2b0);
  uVar3 = 0;
  if (lVar2 != 0) {
    uVar3 = FpObjectTnderBH::FpObjectTnderBH(lVar2,0x8c,0);
  }
  PutiPrim::AddObject(this,uVar3);
  uVar4 = FVector::FVector(auStack_c0,&uStack_10);
  uVar5 = FVector::FVector(auStack_d0,&uStack_20);
  FpObjectTnderBH::InitData
            (0x40a00000,0x41a00000,0x41f00000,0x42700000,0,uVar3,uVar4,uVar5);
  iVar7 = (int)uVar3;
  (**(code **)(iVar7->i32_1e4 + 0x40))(uVar3,10,this->u8_58);
  iVar7->u16_14 = iVar7->u16_14 & 0xe01f | 0x20;
  lVar2 = __nw(0x2b0);
  uVar3 = 0;
  if (lVar2 != 0) {
    uVar3 = FpObjectTnderBH::FpObjectTnderBH(lVar2,0x8c,0);
  }
  PutiPrim::AddObject(this,uVar3);
  uVar4 = FVector::FVector(auStack_e0,&uStack_10);
  uVar5 = FVector::FVector(auStack_f0,&uStack_20);
  FpObjectTnderBH::InitData
            (0x40a00000,0x41a00000,0x42340000,0x42f00000,0,uVar3,uVar4,uVar5);
  iVar7 = (int)uVar3;
  (**(code **)(iVar7->i32_1e4 + 0x40))(uVar3,10,this->u8_58);
  iVar7->u16_14 = iVar7->u16_14 & 0xe01f | 0x20;
  lVar2 = __nw(0x2b0);
  uVar3 = 0;
  if (lVar2 != 0) {
    uVar3 = FpObjectTnderBH::FpObjectTnderBH(lVar2,0x8c,0);
  }
  PutiPrim::AddObject(this,uVar3);
  uVar4 = FVector::FVector(auStack_100,&uStack_10);
  uVar5 = FVector::FVector(auStack_110,&uStack_20);
  FpObjectTnderBH::InitData
            (0x40a00000,0x41a00000,0x42700000,0x43480000,0,uVar3,uVar4,uVar5);
  iVar7 = (int)uVar3;
  (**(code **)(iVar7->i32_1e4 + 0x40))(uVar3,10,this->u8_58);
  iVar7->u16_14 = iVar7->u16_14 & 0xe01f | 0x20;
  lVar2 = __nw(0x2b0);
  uVar3 = 0;
  if (lVar2 != 0) {
    uVar3 = FpObjectTnderBH::FpObjectTnderBH(lVar2,0x104,0);
  }
  PutiPrim::AddObject(this,uVar3);
  uVar4 = FVector::FVector(auStack_120,&uStack_10);
  uVar5 = FVector::FVector(auStack_130,&uStack_20);
  FpObjectTnderBH::InitData
            (0x41200000,0x41f00000,0x41f00000,0x43960000,0,uVar3,uVar4,uVar5);
  iVar7 = (int)uVar3;
  (**(code **)(iVar7->i32_1e4 + 0x40))(uVar3,0x14,this->u8_58);
  iVar7->u16_14 = iVar7->u16_14 & 0xe01f | 0x20;
  lVar2 = __nw(0x2b0);
  uVar3 = 0;
  if (lVar2 != 0) {
    uVar3 = FpObjectTnderBH::FpObjectTnderBH(lVar2,0x104,0);
  }
  PutiPrim::AddObject(this,uVar3);
  uVar4 = FVector::FVector(auStack_140,&uStack_10);
  uVar5 = FVector::FVector(auStack_150,&uStack_20);
  FpObjectTnderBH::InitData
            (0x41200000,0x41f00000,0x41f00000,0x43fa0000,0,uVar3,uVar4,uVar5);
  iVar7 = (int)uVar3;
  (**(code **)(iVar7->i32_1e4 + 0x40))(uVar3,0x14,this->u8_58);
  iVar7->u16_14 = iVar7->u16_14 & 0xe01f | 0x20;
  lVar2 = __nw(0x2b0);
  uVar3 = 0;
  if (lVar2 != 0) {
    uVar3 = FpObjectTnderBH::FpObjectTnderBH(lVar2,0x104,0);
  }
  PutiPrim::AddObject(this,uVar3);
  uVar4 = FVector::FVector(auStack_160,&uStack_10);
  uVar5 = FVector::FVector(auStack_170,&uStack_20);
  FpObjectTnderBH::InitData
            (0x41200000,0x41f00000,0x41f00000,0x442f0000,0,uVar3,uVar4,uVar5);
  iVar7 = (int)uVar3;
  (**(code **)(iVar7->i32_1e4 + 0x40))(uVar3,0x14,this->u8_58);
  iVar7->u16_14 = iVar7->u16_14 & 0xe01f | 0x20;
  lVar2 = __nw(0x2b0);
  uVar3 = 0;
  if (lVar2 != 0) {
    uVar3 = FpObjectTnderBH2::FpObjectTnderBH2(lVar2,0x104,0);
  }
  PutiPrim::AddObject(this,uVar3);
  uVar4 = FVector::FVector(auStack_180,&uStack_10);
  uVar5 = FVector::FVector(auStack_190,&uStack_20);
  FpObjectTnderBH::InitData
            (0x40a00000,0x41f00000,0x41f00000,0x43480000,0,uVar3,uVar4,uVar5);
  iVar7 = (int)uVar3;
  (**(code **)(iVar7->i32_1e4 + 0x40))(uVar3,0x14,this->u8_58);
  iVar7->u16_14 = iVar7->u16_14 & 0xe01f | 0x20;
  lVar2 = __nw(0x2b0);
  uVar3 = 0;
  if (lVar2 != 0) {
    uVar3 = FpObjectTnderBH2::FpObjectTnderBH2(lVar2,0x104,0);
  }
  PutiPrim::AddObject(this,uVar3);
  uVar4 = FVector::FVector(auStack_1a0,&uStack_10);
  uVar5 = FVector::FVector(auStack_1b0,&uStack_20);
  FpObjectTnderBH::InitData
            (0x40a00000,0x41f00000,0x41f00000,0x43c80000,0,uVar3,uVar4,uVar5);
  iVar7 = (int)uVar3;
  (**(code **)(iVar7->i32_1e4 + 0x40))(uVar3,0x14,this->u8_58);
  iVar7->u16_14 = iVar7->u16_14 & 0xe01f | 0x20;
  lVar2 = __nw(0x2b0);
  uVar3 = 0;
  if (lVar2 != 0) {
    uVar3 = FpObjectTnderBH2::FpObjectTnderBH2(lVar2,0x104,0);
  }
  PutiPrim::AddObject(this,uVar3);
  uVar4 = FVector::FVector(auStack_1c0,&uStack_10);
  uVar5 = FVector::FVector(auStack_1d0,&uStack_20);
  FpObjectTnderBH::InitData
            (0x40a00000,0x41f00000,0x41f00000,0x44160000,0,uVar3,uVar4,uVar5);
  iVar7 = (int)uVar3;
  (**(code **)(iVar7->i32_1e4 + 0x40))(uVar3,0x14,this->u8_58);
  iVar7->u16_14 = iVar7->u16_14 & 0xe01f | 0x20;
  lVar2 = __nw(0xd0);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = FpAreaSmoke::FpAreaSmoke(lVar2);
  }
  this->u32_b4 = uVar1;
  uVar1 = 0x42700000;
  uVar10 = 0x43480000;
  fVar9 = 50.0;
  uStack_30 = 0;
  uStack_2c = 0x40400000;
  uStack_28 = 0;
  uStack_24 = 0x3f800000;
  uStack_40 = 0x3f000000;
  uStack_3c = 0;
  uStack_38 = 0;
  uStack_34 = 0x3f800000;
  uStack_50 = 0x42f00000;
  uStack_4c = 0x42e60000;
  uStack_48 = 0x42dc0000;
  uStack_44 = 0x42200000;
  uStack_60 = 0x43000000;
  uStack_5c = 0;
  uStack_58 = 0;
  uStack_54 = 0;
  uVar3 = FVector::FVector(auStack_1e0,&uStack_30);
  uVar4 = FVector::FVector(auStack_1f0,&uStack_40);
  uVar5 = FVector::FVector(auStack_200,&uStack_50);
  uVar6 = FVector::FVector(auStack_210,&uStack_60);
  FpAreaSmoke::Create
            (uVar1,0x41f00000,uVar10,0xbd4ccccd,this->u32_b4,uVar3,uVar4,uVar5,
             uVar6,100,(int)fVar9);
  (**(code **)(this->i32_10 + 0x2c))(this,1);
  PutiManager::AddPrim(BgEffectMan::eff,this->u32_54,this);
  return;
}

// JP: 0x002b7a00  Create__11FpBlackHoleFPv  =  FpBlackHole::Create
void FpBlackHole::Create(undefined4 this)

{
  FpBlackHole::Create(this);
  return;
}

// JP: 0x002b7a30  __ct__17FpObjectBlackHoleFiPv  =  FpObjectBlackHole::FpObjectBlackHole
undefined8 FpObjectBlackHole::FpObjectBlackHole(undefined8 this)

{
  undefined1 auVar1 [16];
  int this;
  undefined1 in_vf0 [16];
  undefined1 auVar3 [16];
  undefined1 auVar4 [16];
  undefined1 auVar5 [16];
  
  FpObject::FpObject(this);
  
  *(undefined1 **)(this + 0x1e4) = FpObjectBlackHole::__vt;
  auVar3 = _vmr32(in_vf0);
  auVar4 = _vmr32(auVar3);
  auVar5 = _vmr32(auVar4);
  auVar1 = _sqc2(in_vf0);
  *(undefined1 (*) [16])(this + 0x260) = auVar1;
  auVar1 = _sqc2(auVar3);
  *(undefined1 (*) [16])(this + 0x250) = auVar1;
  auVar1 = _sqc2(auVar4);
  *(undefined1 (*) [16])(this + 0x240) = auVar1;
  auVar1 = _sqc2(auVar5);
  *(undefined1 (*) [16])(this + 0x230) = auVar1;
  this->u32_210 = 0;
  this->u32_214 = 0;
  this->u32_218 = 0;
  this->u32_21c = 0;
  this->u32_220 = 0;
  return this;
}

// JP: 0x002b7ad0  __dt__17FpObjectBlackHoleFv  =  FpObjectBlackHole::~FpObjectBlackHole
int FpObjectBlackHole::~FpObjectBlackHole(int this,short param_2)

{
  if (this != 0) {
    *(undefined1 **)(this + 0x1e4) = FpObjectBlackHole::__vt;
    FpObject::~FpObject(this,0);
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}

// JP: 0x002b7b50  FuncPos__17FpObjectBlackHoleFP7_FpData  =  FpObjectBlackHole::FuncPos
void FpObjectBlackHole::FuncPos(int this,float *param_2)

{
  int iVar1;
  float fVar2;
  undefined4 uVar3;
  float fVar4;
  float fVar5;
  undefined1 in_vf0 [16];
  undefined1 auVar6 [16];
  undefined1 auVar7 [16];
  undefined1 auVar8 [16];
  undefined1 auStack_c0 [8];
  float fStack_b8;
  float fStack_b4;
  undefined1 auStack_b0 [64];
  float fStack_70;
  undefined4 uStack_6c;
  float fStack_68;
  undefined4 uStack_64;
  float fStack_60;
  undefined4 uStack_5c;
  float fStack_58;
  undefined4 uStack_54;
  undefined1 auStack_50 [16];
  undefined1 auStack_40 [16];
  undefined1 auStack_30 [16];
  undefined1 auStack_20 [16];
  float afStack_10 [3];
  undefined4 uStack_4;
  
  iVar1 = this->i32_8;
  fVar4 = param_2[1];
  fVar5 = param_2[8] + param_2[5] * fVar4;
  fVar2 = *param_2 / 2.0;
  if (fVar4 < fVar2) {
    fStack_58 = param_2[6] * (fVar4 - fVar2);
    fStack_60 = param_2[4] * fVar4;
    uStack_5c = 0;
    uStack_54 = 0x3f800000;
    afStack_10[0] = fStack_60;
    afStack_10[2] = fStack_58;
  }
  else {
    fStack_68 = param_2[6] * (fVar4 - fVar2);
    fStack_70 = param_2[4] * (*param_2 - fVar4);
    uStack_6c = 0;
    uStack_64 = 0x3f800000;
    fVar4 = param_2[4] * *param_2 * 0.075;
    afStack_10[0] = fStack_70;
    afStack_10[2] = fStack_68;
    if (fStack_70 < fVar4) {
      param_2[0x2f] = 0.0;
    }
    else if (fStack_70 < fVar4 * 2.0) {
      param_2[0x2f] = iVar1->f32_8c * ((fStack_70 - fVar4) / fVar4);
    }
  }
  afStack_10[1] = 0.0;
  uStack_4 = 0x3f800000;
  fVar2 = (afStack_10[0] * 2.8) / (iVar1->f32_9c * fVar2) + 1.1;
  if (fVar2 < 0.0) {
    fVar2 = 0.0;
  }
  param_2[0x14] = fVar2;
  param_2[0x15] = fVar2;
  auVar6 = _vmr32(in_vf0);
  auVar7 = _vmr32(auVar6);
  auVar8 = _vmr32(auVar7);
  auStack_20 = _sqc2(in_vf0);
  auStack_30 = _sqc2(auVar6);
  auStack_40 = _sqc2(auVar7);
  auStack_50 = _sqc2(auVar8);
  uVar3 = GetRad(fVar5 - (float)((int)fVar5 / 0x168) * 360.0);
  sceVu0RotMatrixZ(uVar3,auStack_50,auStack_50);
  Matrix::MulMatrix(auStack_b0,this + 0x230,auStack_50);
  Matrix::ApplyMatrix(auStack_c0,auStack_50,afStack_10);
  param_2[0xc] = auStack_c0._0_4_;
  param_2[0xd] = auStack_c0._4_4_;
  param_2[0xe] = fStack_b8;
  param_2[0xf] = fStack_b4;
  return;
}

// JP: 0x002b7e20  CreateData__17FpObjectBlackHoleFib  =  FpObjectBlackHole::CreateData
void FpObjectBlackHole::CreateData(int this,int param_2,long param_3)

{
  undefined8 uVar1;
  int iVar2;
  float fVar3;
  float *pfVar4;
  float fVar5;
  
  pfVar4 = (float *)(this->i32_1fc + param_2 * 0xf0);
  iVar2 = this->i32_8;
  pfVar4[4] = iVar2->f32_9c;
  pfVar4[5] = iVar2->f32_a4;
  pfVar4[6] = iVar2->f32_a0;
  if (param_3 == 0) {
    pfVar4[1] = 0.0;
  }
  else {
    *pfVar4 = (iVar2->f32_90 * 2.0) / iVar2->f32_a0;
    pfVar4[1] = (*pfVar4 * (float)param_2) / (float)this->i32_1f8;
    pfVar4[2] = 0.0;
    pfVar4[8] = 0.0;
    pfVar4[9] = 0.0;
    pfVar4[10] = 0.0;
    pfVar4[0xb] = 1.0;
    fVar5 = iVar2->f32_ac;
    pfVar4[0x10] = iVar2->f32_a8;
    pfVar4[0x11] = fVar5;
    pfVar4[0x12] = 0.0;
    pfVar4[0x13] = 1.0;
    pfVar4[0x18] = 0.0;
    pfVar4[0x19] = 0.0;
    pfVar4[0x1a] = 0.0;
    pfVar4[0x1b] = 1.0;
    pfVar4[0x30] = 0.0;
    pfVar4[0x31] = 0.0;
    pfVar4[0x32] = 0.0;
    pfVar4[0x33] = 1.0;
    pfVar4[0x34] = 1.0;
    pfVar4[0x35] = 0.0;
    pfVar4[0x36] = 1.0;
    pfVar4[0x37] = 1.0;
  }
  uVar1 = iVar2->u64_80;
  fVar5 = iVar2->f32_88;
  fVar3 = iVar2->f32_8c;
  pfVar4[0x2c] = (float)uVar1;
  pfVar4[0x2d] = (float)((ulong)uVar1 >> 0x20);
  pfVar4[0x2e] = fVar5;
  pfVar4[0x2f] = fVar3;
  pfVar4[0x2c] = pfVar4[0x2c] * 1.0;
  iVar2 = rand();
  pfVar4[0x2d] = pfVar4[0x2d] * (((float)iVar2 * 0.2) / 2.1474836e+09 + 1.0);
  iVar2 = rand();
  pfVar4[0x2e] = pfVar4[0x2e] * (((float)iVar2 * 0.2) / 2.1474836e+09 + 1.0);
  pfVar4[0x14] = 1.0;
  pfVar4[0x15] = 1.0;
  pfVar4[0x16] = 1.0;
  pfVar4[0x17] = 1.0;
  iVar2 = rand();
  pfVar4[8] = ((float)(param_2 % 10) + (0.5 - (float)iVar2 / 2.1474836e+09)) * 36.0;
  if (360.0 < pfVar4[8]) {
    pfVar4[8] = pfVar4[8] - 360.0;
  }
  return;
}

// JP: 0x002b81e0  Init__17FpObjectBlackHoleFib  =  FpObjectBlackHole::Init
void FpObjectBlackHole::Init(undefined8 this,undefined4 param_2,long param_3)

{
  int iVar1;
  undefined1 auVar2 [16];
  undefined4 uVar3;
  undefined8 uVar4;
  int iVar5;
  int this;
  undefined1 in_vf0 [16];
  undefined1 auVar7 [16];
  undefined1 auVar8 [16];
  undefined1 auVar9 [16];
  
  
  iVar5 = this->i32_8;
  this->u32_1f8 = param_2;
  this->u32_1f4 = param_2;
  iVar1 = this->i32_1f8;
  uVar4 = __nwa(iVar1 * 0xf0 + 0x10);
  uVar3 = __construct_new_array(uVar4,0x299b50,0,0xf0,iVar1);
  this->u32_1fc = uVar3;
  memset(*(void **)(this + 0x1fc),0,(long)(this->i32_1f8 * 0xf0));
  auVar7 = _vmr32(in_vf0);
  auVar8 = _vmr32(auVar7);
  auVar9 = _vmr32(auVar8);
  auVar2 = _sqc2(in_vf0);
  *(undefined1 (*) [16])(this + 0x260) = auVar2;
  auVar2 = _sqc2(auVar7);
  *(undefined1 (*) [16])(this + 0x250) = auVar2;
  auVar2 = _sqc2(auVar8);
  *(undefined1 (*) [16])(this + 0x240) = auVar2;
  auVar2 = _sqc2(auVar9);
  *(undefined1 (*) [16])(this + 0x230) = auVar2;
  uVar3 = GetRad(iVar5->u32_94);
  sceVu0RotMatrixX(uVar3,this + 0x230,this + 0x230);
  for (iVar5 = 0; iVar5 < this->i32_1f8; iVar5 = iVar5 + 1) {
    (**(code **)(this->i32_1e4 + 0x4c))(this,iVar5,1);
    FpObjectBlackHole::FuncPos(this,this->i32_1fc + iVar5 * 0xf0);
  }
  this->u32_1e0 = 0xffffffff;
  this->u8_14 = this->u8_14 & 0xfe | 1;
  this->u16_14 = this->u16_14 & 0xe01f;
  if (param_3 == 0) {
    PutiObject::SetRegTest(this,0x33001);
  }
  else {
    PutiObject::SetRegTest(this,0x73001);
  }
  PutiObject::SetRegAlpha(this,0x44);
  return;
}

// JP: 0x002b83c0  CalculateFunc__17FpObjectBlackHoleFv  =  FpObjectBlackHole::CalculateFunc
void FpObjectBlackHole::CalculateFunc(int this)

{
  int iVar1;
  float *pfVar2;
  float fVar3;
  
  fVar3 = (float)FpPrim::GetFrameSpeed(this->u32_8);
  pfVar2 = *(float **)(this + 0x1fc);
  for (iVar1 = 0; iVar1 < this->i32_1f8; iVar1 = iVar1 + 1) {
    pfVar2[1] = pfVar2[1] + fVar3;
    if (*pfVar2 < pfVar2[1]) {
      (**(code **)(this->i32_1e4 + 0x4c))(this,iVar1,0);
    }
    FpObjectBlackHole::FuncPos(this,pfVar2);
    pfVar2 = pfVar2 + 0x3c;
  }
  iVar1 = rand();
  this->f32_210 = ((float)iVar1 * 1.5) / 2.1474836e+09 + -1.0;
  iVar1 = rand();
  this->f32_214 = ((float)iVar1 * 1.5) / 2.1474836e+09 + -1.0;
  iVar1 = rand();
  this->f32_218 = (float)iVar1 / 2.1474836e+09;
  iVar1 = rand();
  this->f32_21c = (float)iVar1 / 2.1474836e+09;
  iVar1 = rand();
  this->f32_220 = (float)iVar1 / 2.1474836e+09;
  (**(code **)(this->i32_1e4 + 0x44))();
  return;
}

// JP: 0x002b85d0  CalcFpVertex__17FpObjectBlackHoleFv  =  FpObjectBlackHole::CalcFpVertex
void FpObjectBlackHole::CalcFpVertex(int this)

{
  int iVar1;
  undefined1 (*pauVar2) [16];
  int iVar3;
  int iVar4;
  int iVar5;
  float fVar6;
  float fVar7;
  undefined1 auVar8 [16];
  undefined1 auVar9 [16];
  undefined1 auStack_60 [8];
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
  undefined1 auStack_10 [12];
  undefined4 uStack_4;
  
  iVar5 = this->i32_1fc;
  fVar7 = iVar5->f32_40 / 2.0;
  fVar6 = iVar5->f32_44;
  for (iVar4 = 0; iVar4 < this->i32_1f8; iVar4 = iVar4 + 1) {
    fStack_50 = fVar7 * iVar5->f32_50;
    fStack_4c = (fVar6 / 2.0) * iVar5->f32_54;
    fStack_20 = -fStack_50;
    fStack_1c = -fStack_4c;
    uStack_18 = 0;
    uStack_14 = 0x3f800000;
    iVar5->f32_70 = fStack_20;
    iVar5->f32_74 = fStack_1c;
    iVar5->u32_78 = 0;
    iVar5->u32_7c = 0x3f800000;
    fStack_30 = -fStack_50;
    uStack_28 = 0;
    uStack_24 = 0x3f800000;
    iVar5->f32_80 = fStack_30;
    iVar5->f32_84 = fStack_4c;
    iVar5->u32_88 = 0;
    iVar5->u32_8c = 0x3f800000;
    fStack_3c = -fStack_4c;
    uStack_38 = 0;
    uStack_34 = 0x3f800000;
    iVar5->f32_90 = fStack_50;
    iVar5->f32_94 = fStack_3c;
    iVar5->u32_98 = 0;
    iVar5->u32_9c = 0x3f800000;
    uStack_48 = 0;
    uStack_44 = 0x3f800000;
    iVar5->f32_a0 = fStack_50;
    iVar5->f32_a4 = fStack_4c;
    iVar5->u32_a8 = 0;
    iVar5->u32_ac = 0x3f800000;
    fStack_40 = fStack_50;
    fStack_2c = fStack_4c;
    FVector::FVector(auStack_10,iVar5 + 0x30);
    uStack_4 = 0;
    for (iVar3 = 0; iVar3 < 4; iVar3 = iVar3 + 1) {
      Matrix::ApplyMatrix(auStack_60,0x4213c0,iVar5 + iVar3 * 0x10 + 0x70);
      iVar1 = iVar5 + iVar3 * 0x10;
      iVar1->i32_70 = auStack_60._0_4_;
      iVar1->i32_74 = auStack_60._4_4_;
      iVar1->u32_78 = uStack_58;
      iVar1->u32_7c = uStack_54;
      pauVar2 = (undefined1 (*) [16])(iVar5 + iVar3 * 0x10 + 0x70);
      auVar8._12_4_ = uStack_4;
      auVar8._0_12_ = auStack_10;
      auVar9 = _lqc2(auVar8);
      auVar8 = _lqc2(*pauVar2);
      auVar8 = _vadd(auVar8,auVar9);
      auVar8 = _sqc2(auVar8);
      *pauVar2 = auVar8;
    }
    iVar5 = iVar5 + 0xf0;
  }
  return;
}

// JP: 0x002b8800  SetPacket__17FpObjectBlackHoleFv  =  FpObjectBlackHole::SetPacket
void FpObjectBlackHole::SetPacket(undefined8 this)

{
  ulong *puVar1;
  uint *puVar2;
  bool bVar3;
  float in_zero_lo;
  float in_zero_hi;
  float in_zero_udw;
  float in_register_0000000c;
  ulong uVar4;
  int iVar5;
  float *pfVar6;
  int this;
  int iVar8;
  int iVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  uint uVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  undefined1 auVar23 [16];
  undefined1 auVar24 [16];
  undefined1 auStack_120 [16];
  int iStack_110;
  int iStack_10c;
  int iStack_108;
  undefined1 auStack_100 [16];
  float fStack_f0;
  float fStack_ec;
  float fStack_e8;
  float fStack_e4;
  undefined4 auStack_e0 [16];
  undefined4 auStack_a0 [16];
  undefined1 auStack_60 [16];
  undefined1 auStack_50 [16];
  undefined1 auStack_40 [32];
  undefined1 auStack_20 [16];
  undefined1 auStack_10 [16];
  
  
  fVar11 = this->f32_210;
  fVar17 = (this->f32_210 + this->f32_218) * 512.0 + 2048.0;
  fVar12 = this->f32_214;
  fVar16 = (this->f32_214 + this->f32_21c) * 448.0 + 2048.0;
  Matrix::Matrix(auStack_40,CApp::camera + 0x240);
  FVector::FVector(auStack_50,auStack_10);
  FVector::FVector(auStack_60,auStack_20);
  iVar9 = this->i32_8;
  pfVar6 = *(float **)(this + 0x88);
  *pfVar6 = in_zero_lo;
  pfVar6[1] = in_zero_hi;
  pfVar6[2] = in_zero_udw;
  pfVar6[3] = in_register_0000000c;
  *pfVar6 = (float)(&DAT_10000001 + this->i32_1f8 * 0xc);
  pfVar6[3] = (float)(this->i32_1f8 * 0xc + 1U | 0x50000000);
  this->i32_88 = this->i32_88 + 0x10;
  puVar1 = *(ulong **)(this + 0x88);
  *puVar1 = (long)(this->i32_1f8 << 2) | 0x302a400000008000;
  puVar1[1] = 0x412;
  this->i32_88 = this->i32_88 + 0x10;
  pfVar6 = *(float **)(this + 0x88);
  GsxCamera::GetViewScreenMatrix(auStack_a0,CApp::camera);
  for (iVar8 = 0; iVar8 < 4; iVar8 = iVar8 + 1) {
    auStack_e0[iVar8 * 4] = auStack_a0[iVar8 * 4];
    auStack_e0[iVar8 * 4 + 1] = auStack_a0[iVar8 * 4 + 1];
    auStack_e0[iVar8 * 4 + 2] = auStack_a0[iVar8 * 4 + 2];
    auStack_e0[iVar8 * 4 + 3] = auStack_a0[iVar8 * 4 + 3];
  }
  fVar15 = 2560.0;
  fVar13 = iVar9->f32_90;
  iVar9 = this->i32_1fc;
  fStack_f0 = in_zero_lo;
  fStack_ec = in_zero_hi;
  fStack_e8 = in_zero_udw;
  fStack_e4 = in_register_0000000c;
  for (iVar8 = 0; iVar8 < this->i32_1f8; iVar8 = iVar8 + 1) {
    fVar18 = iVar9->f32_34;
    bVar3 = false;
    if (fVar13 * 0.3 < fVar18) {
      bVar3 = true;
    }
    else {
      auVar23 = _lqc2(*(undefined1 (*) [16])(iVar9 + 0x30));
      auVar24 = _lqc2(auStack_50);
      auVar23 = _vsub(auVar23,auVar24);
      auStack_120 = _sqc2(auVar23);
      FVector::FVector(auStack_100,auStack_120);
      auVar23 = _lqc2(auStack_60);
      auVar24 = _lqc2(auStack_100);
      auVar23 = _vmul(auVar23,auVar24);
      auVar23 = _vaddbc(auVar23,auVar23);
      auVar23 = _vaddbc(auVar23,auVar23);
      auVar23 = _qmfc2(auVar23._0_4_);
      if (auVar23._0_4_ < 0.0) {
        bVar3 = true;
      }
      else {
        sceVu0RotTransPersN(&iStack_110,auStack_e0,iVar9 + 0x30,1,0);
        if ((float)iStack_110 / 16.0 < 1536.0) {
          bVar3 = true;
        }
        else if (fVar15 < (float)iStack_110 / 16.0) {
          bVar3 = true;
        }
        else if ((float)iStack_10c / 16.0 < 1600.0) {
          bVar3 = true;
        }
        else if (2496.0 < (float)iStack_10c / 16.0) {
          bVar3 = true;
        }
        else if ((float)iStack_108 < 0.0) {
          bVar3 = true;
        }
      }
    }
    if (bVar3) {
      for (iVar5 = 0; iVar5 < 4; iVar5 = iVar5 + 1) {
        *pfVar6 = in_zero_lo;
        pfVar6[1] = in_zero_hi;
        pfVar6[2] = in_zero_udw;
        pfVar6[3] = in_register_0000000c;
        this->i32_88 = this->i32_88 + 0x10;
        pfVar6 = *(float **)(this + 0x88);
        *pfVar6 = in_zero_lo;
        pfVar6[1] = in_zero_hi;
        pfVar6[2] = in_zero_udw;
        pfVar6[3] = in_register_0000000c;
        this->i32_88 = this->i32_88 + 0x10;
        pfVar6 = *(float **)(this + 0x88);
        *pfVar6 = in_zero_lo;
        pfVar6[1] = in_zero_hi;
        pfVar6[2] = in_zero_udw;
        pfVar6[3] = in_register_0000000c;
        pfVar6[3] = 4.59177e-41;
        this->i32_88 = this->i32_88 + 0x10;
        pfVar6 = *(float **)(this + 0x88);
      }
    }
    else {
      fVar21 = iVar9->f32_b0;
      fVar22 = iVar9->f32_b4;
      fVar19 = iVar9->f32_b8;
      fVar20 = iVar9->f32_bc;
      if (0.0 < fVar18) {
        fVar18 = fVar18 * 0.5;
        fVar21 = fVar21 + fVar18;
        if (128.0 < fVar21) {
          fVar21 = 128.0;
        }
        fVar22 = fVar22 + fVar18;
        if (128.0 < fVar22) {
          fVar22 = 128.0;
        }
        fVar19 = fVar19 + fVar18;
        if (128.0 < fVar19) {
          fVar19 = 128.0;
        }
        fVar20 = fVar20 + fVar18;
        if (128.0 < fVar20) {
          fVar20 = 128.0;
        }
      }
      for (iVar5 = 0; iVar5 < 4; iVar5 = iVar5 + 1) {
        fVar18 = (float)PutiObject::RotTransPer
                                  (this,iVar9 + iVar5 * 0x10 + 0x70,&fStack_f0);
        uVar4 = PutiObject::ClipFlag(this);
        if (iVar5 == 0) {
          if ((((fVar11 * 512.0 + 2048.0 < (float)(uint)fStack_f0 / 16.0) &&
               ((float)(uint)fStack_f0 / 16.0 < fVar17)) &&
              (fVar12 * 448.0 + 2048.0 < (float)(uint)fStack_ec / 16.0)) &&
             ((float)(uint)fStack_ec / 16.0 < fVar16)) {
            fVar10 = this->f32_220 * 0.5 + 1.0;
            fVar21 = fVar21 * fVar10;
            if (128.0 < fVar21) {
              fVar21 = 128.0;
            }
            fVar22 = fVar22 * fVar10;
            if (128.0 < fVar22) {
              fVar22 = 128.0;
            }
            fVar19 = fVar19 * fVar10;
            if (128.0 < fVar19) {
              fVar19 = 128.0;
            }
          }
        }
        *pfVar6 = *(float *)(iVar9 + iVar5 * 8 + 0xc0) * fVar18;
        pfVar6[1] = *(float *)(iVar9 + iVar5 * 8 + 0xc4) * fVar18;
        pfVar6[2] = fVar18;
        this->i32_88 = this->i32_88 + 0x10;
        puVar2 = *(uint **)(this + 0x88);
        if (fVar21 < 2.1474836e+09) {
          uVar14 = (uint)fVar21;
        }
        else {
          uVar14 = (int)(fVar21 - 2.1474836e+09) | 0x80000000;
        }
        *puVar2 = uVar14;
        if (fVar22 < 2.1474836e+09) {
          uVar14 = (uint)fVar22;
        }
        else {
          uVar14 = (int)(fVar22 - 2.1474836e+09) | 0x80000000;
        }
        puVar2[1] = uVar14;
        if (fVar19 < 2.1474836e+09) {
          uVar14 = (uint)fVar19;
        }
        else {
          uVar14 = (int)(fVar19 - 2.1474836e+09) | 0x80000000;
        }
        puVar2[2] = uVar14;
        if (fVar20 < 2.1474836e+09) {
          uVar14 = (uint)fVar20;
        }
        else {
          uVar14 = (int)(fVar20 - 2.1474836e+09) | 0x80000000;
        }
        puVar2[3] = uVar14;
        this->i32_88 = this->i32_88 + 0x10;
        pfVar6 = *(float **)(this + 0x88);
        if ((iVar5 < 2) || ((uVar4 & 0x3ffff) != 0)) {
          fStack_e4 = 4.59177e-41;
        }
        *pfVar6 = fStack_f0;
        pfVar6[1] = fStack_ec;
        pfVar6[2] = fStack_e8;
        pfVar6[3] = fStack_e4;
        this->i32_88 = this->i32_88 + 0x10;
        pfVar6 = *(float **)(this + 0x88);
      }
    }
    iVar9 = iVar9 + 0xf0;
  }
  return;
}

// JP: 0x002b9160  __ct__15FpObjectTnderBHFiPv  =  FpObjectTnderBH::FpObjectTnderBH
int FpObjectTnderBH::FpObjectTnderBH(int this,undefined4 param_2,undefined4 param_3)

{
  FpObjectTnder::FpObjectTnder(this,param_2,param_3);
  *(undefined1 **)(this + 0x1e4) = FpObjectTnderBH::__vt;
  this->u32_2a0 = 0x3f800000;
  this->u32_2a4 = 0x3f800000;
  this->u32_2ac = 0;
  return this;
}

// JP: 0x002b91e0  __dt__15FpObjectTnderBHFv  =  FpObjectTnderBH::~FpObjectTnderBH
int FpObjectTnderBH::~FpObjectTnderBH(int this,short param_2)

{
  if (this != 0) {
    *(undefined1 **)(this + 0x1e4) = FpObjectTnderBH::__vt;
    FpObjectTnder::~FpObjectTnder(this,0);
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}

// JP: 0x002b9260  InitData__15FpObjectTnderBHF7FVector7FVectorfffff  =  FpObjectTnderBH::InitData
void FpObjectTnderBH::InitData
               (undefined4 this,undefined4 param_2,undefined4 param_3,undefined4 param_4,
               undefined4 param_5,int param_6,undefined8 *param_7,undefined8 *param_8)

{
  undefined8 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  float fVar4;
  
  param_6->u32_210 = 0;
  param_6->u32_214 = 0;
  param_6->u32_218 = 0;
  param_6->u32_21c = 0x3f800000;
  uVar1 = *param_7;
  uVar2 = param_7->u32_1;
  uVar3 = *(undefined4 *)((int)param_7 + 0xc);
  param_6->i32_270 = (int)uVar1;
  param_6->i32_274 = (int)((ulong)uVar1 >> 0x20);
  param_6->u32_278 = uVar2;
  param_6->u32_27c = uVar3;
  uVar1 = *param_8;
  uVar2 = param_8->u32_1;
  uVar3 = *(undefined4 *)((int)param_8 + 0xc);
  param_6->i32_280 = (int)uVar1;
  param_6->i32_284 = (int)((ulong)uVar1 >> 0x20);
  param_6->u32_288 = uVar2;
  param_6->u32_28c = uVar3;
  param_6->u32_290 = this;
  param_6->u32_2a0 = param_2;
  fVar4 = (float)GetRad(param_3);
  fVar4 = sinf(fVar4);
  param_6->f32_2a4 = param_6->f32_2a0 * fVar4;
  param_6->u32_2a8 = param_4;
  param_6->u32_2ac = param_5;
  return;
}

// JP: 0x002b9330  CreateData__15FpObjectTnderBHFib  =  FpObjectTnderBH::CreateData
void FpObjectTnderBH::CreateData(int this,uint param_2,long param_3)

{
  int iVar1;
  undefined1 auVar2 [16];
  undefined1 auVar3 [16];
  undefined1 auVar4 [16];
  undefined1 auVar5 [16];
  float in_zero_lo;
  float in_zero_hi;
  float in_zero_udw;
  float in_register_0000000c;
  uint uVar6;
  int iVar7;
  float *pfVar8;
  undefined4 uVar9;
  float fVar10;
  undefined1 in_vf0 [16];
  undefined1 auVar11 [16];
  undefined1 auVar12 [16];
  undefined1 auVar13 [16];
  undefined1 auStack_340 [16];
  undefined1 auStack_330 [16];
  undefined1 auStack_320 [16];
  undefined1 auStack_310 [16];
  undefined1 auStack_300 [16];
  undefined1 auStack_2f0 [16];
  undefined1 auStack_2e0 [16];
  undefined1 auStack_2d0 [16];
  undefined1 auStack_2c0 [16];
  undefined1 auStack_2b0 [16];
  undefined1 auStack_2a0 [16];
  undefined1 auStack_290 [16];
  undefined1 auStack_280 [16];
  undefined1 auStack_270 [16];
  undefined1 auStack_260 [16];
  undefined1 auStack_250 [16];
  undefined1 auStack_240 [16];
  undefined1 auStack_230 [16];
  undefined1 auStack_220 [16];
  undefined1 auStack_210 [16];
  undefined1 auStack_200 [8];
  float fStack_1f8;
  float fStack_1f4;
  undefined1 auStack_1f0 [8];
  undefined4 uStack_1e8;
  undefined4 uStack_1e4;
  undefined1 auStack_1e0 [8];
  undefined4 uStack_1d8;
  undefined4 uStack_1d4;
  undefined1 auStack_1d0 [16];
  undefined1 auStack_1c0 [16];
  undefined1 auStack_1b0 [16];
  undefined1 auStack_1a0 [8];
  float fStack_198;
  float fStack_194;
  undefined1 auStack_190 [8];
  undefined4 uStack_188;
  undefined4 uStack_184;
  undefined1 auStack_180 [8];
  undefined4 uStack_178;
  undefined4 uStack_174;
  undefined1 auStack_170 [16];
  undefined1 auStack_160 [16];
  undefined1 auStack_150 [16];
  undefined1 auStack_140 [8];
  float fStack_138;
  float fStack_134;
  undefined1 auStack_130 [16];
  undefined1 auStack_120 [8];
  undefined4 uStack_118;
  undefined4 uStack_114;
  undefined1 auStack_110 [8];
  undefined4 uStack_108;
  undefined4 uStack_104;
  undefined1 auStack_100 [8];
  undefined4 uStack_f8;
  undefined4 uStack_f4;
  undefined4 uStack_f0;
  undefined4 uStack_ec;
  float fStack_e8;
  undefined4 uStack_e4;
  undefined4 uStack_e0;
  undefined4 uStack_dc;
  undefined4 uStack_d8;
  undefined4 uStack_d4;
  undefined4 uStack_d0;
  undefined4 uStack_cc;
  undefined4 uStack_c8;
  undefined4 uStack_c4;
  undefined4 uStack_c0;
  undefined4 uStack_bc;
  undefined4 uStack_b8;
  undefined4 uStack_b4;
  undefined4 uStack_b0;
  undefined4 uStack_ac;
  undefined4 uStack_a8;
  undefined4 uStack_a4;
  undefined1 auStack_90 [16];
  undefined1 auStack_80 [16];
  undefined1 auStack_70 [16];
  undefined1 auStack_60 [16];
  undefined1 auStack_50 [16];
  undefined1 auStack_40 [16];
  undefined4 uStack_30;
  undefined4 uStack_2c;
  float fStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  pfVar8 = (float *)(this->i32_1fc + param_2 * 0xf0);
  iVar1 = this->i32_8;
  if (param_3 == 0) {
    pfVar8[1] = 0.0;
  }
  else {
    *pfVar8 = 3.0;
    pfVar8[8] = in_zero_lo;
    pfVar8[9] = in_zero_hi;
    pfVar8[10] = in_zero_udw;
    pfVar8[0xb] = in_register_0000000c;
    uStack_b0 = 0;
    uStack_ac = 0;
    uStack_a8 = 0;
    uStack_a4 = 0;
    pfVar8[0x2c] = 0.0;
    pfVar8[0x2d] = 0.0;
    pfVar8[0x2e] = 0.0;
    pfVar8[0x2f] = 0.0;
    pfVar8[2] = 0.0;
    uStack_c0 = 0x3f800000;
    uStack_bc = 0x3f800000;
    uStack_b8 = 0x3f800000;
    uStack_b4 = 0x3f800000;
    pfVar8[0x10] = 1.0;
    pfVar8[0x11] = 1.0;
    pfVar8[0x12] = 1.0;
    pfVar8[0x13] = 1.0;
    uStack_d0 = 0x3f800000;
    uStack_cc = 0x3f800000;
    uStack_c8 = 0x3f800000;
    uStack_c4 = 0x3f800000;
    pfVar8[0x14] = 1.0;
    pfVar8[0x15] = 1.0;
    pfVar8[0x16] = 1.0;
    pfVar8[0x17] = 1.0;
    uStack_e0 = 0;
    uStack_dc = 0;
    uStack_d8 = 0;
    uStack_d4 = 0x3f800000;
    pfVar8[0x18] = 0.0;
    pfVar8[0x19] = 0.0;
    pfVar8[0x1a] = 0.0;
    pfVar8[0x1b] = 1.0;
    uVar6 = param_2 & 1;
    if (((int)param_2 < 0) && (uVar6 != 0)) {
      uVar6 = uVar6 - 2;
    }
    if (uVar6 == 0) {
      pfVar8[0x34] = 0.0;
      pfVar8[0x30] = 0.0;
      pfVar8[0x35] = 1.0;
      pfVar8[0x31] = 1.0;
      pfVar8[0x36] = 1.0;
      pfVar8[0x32] = 1.0;
      pfVar8[0x37] = 1.0;
      pfVar8[0x33] = 1.0;
    }
    else {
      pfVar8[0x34] = 0.0;
      pfVar8[0x30] = 0.0;
      pfVar8[0x35] = 0.0;
      pfVar8[0x31] = 0.0;
      pfVar8[0x36] = 1.0;
      pfVar8[0x32] = 1.0;
      pfVar8[0x37] = 0.0;
      pfVar8[0x33] = 0.0;
    }
    iVar7 = rand();
    pfVar8[1] = (*pfVar8 * (float)iVar7) / 2.1474836e+09;
  }
  iVar7 = this->i32_1f8;
  if (iVar7 < 0) {
    iVar7 = iVar7 + 1;
  }
  if ((int)param_2 < iVar7 >> 1) {
    pfVar8[0x2e] = (float)(int)param_2 / (float)this->i32_1f8;
  }
  else {
    pfVar8[0x2e] = 1.0 - (float)(int)param_2 / (float)this->i32_1f8;
  }
  iVar7 = rand();
  fVar10 = this->f32_2a4 * (1.0 - ((float)iVar7 * 2.0) / 2.1474836e+09);
  if (param_2 == 0) {
    fStack_28 = iVar1->f32_90 * 0.6;
    uStack_30 = 0;
    uStack_2c = 0;
    uStack_24 = 0x3f800000;
    auVar11 = _vmr32(in_vf0);
    auVar12 = _vmr32(auVar11);
    auVar13 = _vmr32(auVar12);
    auStack_40 = _sqc2(in_vf0);
    auStack_50 = _sqc2(auVar11);
    auStack_60 = _sqc2(auVar12);
    auStack_70 = _sqc2(auVar13);
    uVar9 = GetRad(iVar1->u32_94);
    sceVu0RotMatrixX(uVar9,auStack_70,auStack_70);
    uVar9 = GetRad(iVar1->u32_98);
    sceVu0RotMatrixY(uVar9,auStack_70,auStack_70);
    Matrix::ApplyMatrix(auStack_80,auStack_70,&uStack_30);
    fStack_e8 = iVar1->f32_90 * 0.6;
    uStack_f0 = 0x3f800000;
    uStack_ec = 0;
    uStack_e4 = 0x3f800000;
    uStack_30 = 0x3f800000;
    uStack_2c = 0;
    uStack_24 = 0x3f800000;
    fStack_28 = fStack_e8;
    iVar7 = rand();
    uVar9 = GetRad(((float)iVar7 * 360.0) / 2.1474836e+09);
    sceVu0RotMatrixZ(uVar9,auStack_70,auStack_70);
    uVar9 = GetRad(iVar1->u32_94);
    sceVu0RotMatrixX(uVar9,auStack_70,auStack_70);
    uVar9 = GetRad(iVar1->u32_98);
    sceVu0RotMatrixY(uVar9,auStack_70,auStack_70);
    Matrix::ApplyMatrix(auStack_90,auStack_70,&uStack_30);
    auVar11 = _lqc2(auStack_90);
    auVar12 = _lqc2(auStack_80);
    auVar11 = _vsub(auVar11,auVar12);
    auStack_240 = _sqc2(auVar11);
    FVector::FVector(auStack_100,auStack_240);
    uStack_10 = auStack_100._0_4_;
    uStack_c = auStack_100._4_4_;
    uStack_8 = uStack_f8;
    uStack_4 = uStack_f4;
    FVector::Normalize(&uStack_10);
    FVector::OuterProduct(auStack_110,&uStack_10,this + 0x260);
    uStack_20 = auStack_110._0_4_;
    uStack_1c = auStack_110._4_4_;
    uStack_18 = uStack_108;
    uStack_14 = uStack_104;
    FVector::Normalize(&uStack_20);
    auVar3._4_4_ = uStack_c;
    auVar3._0_4_ = uStack_10;
    auVar3._8_4_ = uStack_8;
    auVar3._12_4_ = uStack_4;
    auVar11 = _lqc2(auVar3);
    auVar12 = _qmtc2(this->u32_2a8);
    auVar11 = _vmulbc(auVar11,auVar12);
    auStack_2b0 = _sqc2(auVar11);
    FVector::FVector(auStack_130,auStack_2b0);
    auVar11 = _lqc2(auStack_80);
    auVar12 = _lqc2(auStack_130);
    auVar11 = _vadd(auVar11,auVar12);
    auStack_250 = _sqc2(auVar11);
    FVector::FVector(auStack_120,auStack_250);
    this->i32_210 = auStack_120._0_4_;
    this->i32_214 = auStack_120._4_4_;
    this->u32_218 = uStack_118;
    this->u32_21c = uStack_114;
    auVar4._4_4_ = uStack_c;
    auVar4._0_4_ = uStack_10;
    auVar4._8_4_ = uStack_8;
    auVar4._12_4_ = uStack_4;
    auVar11 = _lqc2(auVar4);
    auVar12 = _qmtc2(this->u32_2a0);
    auVar11 = _vmulbc(auVar11,auVar12);
    auStack_2c0 = _sqc2(auVar11);
    FVector::FVector(auStack_170,auStack_2c0);
    auVar2._4_4_ = uStack_1c;
    auVar2._0_4_ = uStack_20;
    auVar2._8_4_ = uStack_18;
    auVar2._12_4_ = uStack_14;
    auVar11 = _lqc2(auVar2);
    auVar12 = _qmtc2(fVar10);
    auVar11 = _vmulbc(auVar11,auVar12);
    auStack_2d0 = _sqc2(auVar11);
    FVector::FVector(auStack_160,auStack_2d0);
    auVar11 = _lqc2(*(undefined1 (*) [16])(this + 0x210));
    auVar12 = _lqc2(auStack_160);
    auVar11 = _vadd(auVar11,auVar12);
    auStack_2e0 = _sqc2(auVar11);
    FVector::FVector(auStack_150,auStack_2e0);
    auVar11 = _lqc2(auStack_150);
    auVar12 = _lqc2(auStack_170);
    auVar11 = _vadd(auVar11,auVar12);
    auStack_260 = _sqc2(auVar11);
    FVector::FVector(auStack_140,auStack_260);
    pfVar8[0xc] = auStack_140._0_4_;
    pfVar8[0xd] = auStack_140._4_4_;
    pfVar8[0xe] = fStack_138;
    pfVar8[0xf] = fStack_134;
  }
  else if (param_2 == 1) {
    auVar11 = _lqc2(*(undefined1 (*) [16])(this->i32_1fc + 0x30));
    auVar12 = _lqc2(*(undefined1 (*) [16])(this + 0x210));
    auVar11 = _vsub(auVar11,auVar12);
    auStack_270 = _sqc2(auVar11);
    FVector::FVector(auStack_180,auStack_270);
    uStack_10 = auStack_180._0_4_;
    uStack_c = auStack_180._4_4_;
    uStack_8 = uStack_178;
    uStack_4 = uStack_174;
    FVector::Normalize(&uStack_10);
    FVector::OuterProduct(auStack_190,&uStack_10,this + 0x260);
    uStack_20 = auStack_190._0_4_;
    uStack_1c = auStack_190._4_4_;
    uStack_18 = uStack_188;
    uStack_14 = uStack_184;
    FVector::Normalize(&uStack_20);
    auVar5._4_4_ = uStack_c;
    auVar5._0_4_ = uStack_10;
    auVar5._8_4_ = uStack_8;
    auVar5._12_4_ = uStack_4;
    auVar11 = _lqc2(auVar5);
    auVar12 = _qmtc2(this->u32_2a0);
    auVar11 = _vmulbc(auVar11,auVar12);
    auStack_2f0 = _sqc2(auVar11);
    FVector::FVector(auStack_1d0,auStack_2f0);
    auVar13._4_4_ = uStack_1c;
    auVar13._0_4_ = uStack_20;
    auVar13._8_4_ = uStack_18;
    auVar13._12_4_ = uStack_14;
    auVar11 = _lqc2(auVar13);
    auVar12 = _qmtc2(fVar10);
    auVar11 = _vmulbc(auVar11,auVar12);
    auStack_300 = _sqc2(auVar11);
    FVector::FVector(auStack_1c0,auStack_300);
    auVar11 = _lqc2(*(undefined1 (*) [16])(this->i32_1fc + 0x30));
    auVar12 = _lqc2(auStack_1c0);
    auVar11 = _vadd(auVar11,auVar12);
    auStack_310 = _sqc2(auVar11);
    FVector::FVector(auStack_1b0,auStack_310);
    auVar11 = _lqc2(auStack_1b0);
    auVar12 = _lqc2(auStack_1d0);
    auVar11 = _vadd(auVar11,auVar12);
    auStack_280 = _sqc2(auVar11);
    FVector::FVector(auStack_1a0,auStack_280);
    pfVar8[0xc] = auStack_1a0._0_4_;
    pfVar8[0xd] = auStack_1a0._4_4_;
    pfVar8[0xe] = fStack_198;
    pfVar8[0xf] = fStack_194;
  }
  else {
    auVar11 = _lqc2(*(undefined1 (*) [16])(this->i32_1fc + (param_2 - 1) * 0xf0 + 0x30))
    ;
    auVar12 = _lqc2(*(undefined1 (*) [16])(this->i32_1fc + (param_2 - 2) * 0xf0 + 0x30))
    ;
    auVar11 = _vsub(auVar11,auVar12);
    auStack_290 = _sqc2(auVar11);
    FVector::FVector(auStack_1e0,auStack_290);
    uStack_10 = auStack_1e0._0_4_;
    uStack_c = auStack_1e0._4_4_;
    uStack_8 = uStack_1d8;
    uStack_4 = uStack_1d4;
    FVector::Normalize(&uStack_10);
    FVector::OuterProduct(auStack_1f0,&uStack_10,this + 0x260);
    uStack_20 = auStack_1f0._0_4_;
    uStack_1c = auStack_1f0._4_4_;
    uStack_18 = uStack_1e8;
    uStack_14 = uStack_1e4;
    FVector::Normalize(&uStack_20);
    auVar12._4_4_ = uStack_c;
    auVar12._0_4_ = uStack_10;
    auVar12._8_4_ = uStack_8;
    auVar12._12_4_ = uStack_4;
    auVar11 = _lqc2(auVar12);
    auVar12 = _qmtc2(this->u32_2a0);
    auVar11 = _vmulbc(auVar11,auVar12);
    auStack_320 = _sqc2(auVar11);
    FVector::FVector(auStack_230,auStack_320);
    auVar11._4_4_ = uStack_1c;
    auVar11._0_4_ = uStack_20;
    auVar11._8_4_ = uStack_18;
    auVar11._12_4_ = uStack_14;
    auVar11 = _lqc2(auVar11);
    auVar12 = _qmtc2(fVar10);
    auVar11 = _vmulbc(auVar11,auVar12);
    auStack_330 = _sqc2(auVar11);
    FVector::FVector(auStack_220,auStack_330);
    auVar11 = _lqc2(*(undefined1 (*) [16])(this->i32_1fc + (param_2 - 1) * 0xf0 + 0x30))
    ;
    auVar12 = _lqc2(auStack_220);
    auVar11 = _vadd(auVar11,auVar12);
    auStack_340 = _sqc2(auVar11);
    FVector::FVector(auStack_210,auStack_340);
    auVar11 = _lqc2(auStack_210);
    auVar12 = _lqc2(auStack_230);
    auVar11 = _vadd(auVar11,auVar12);
    auStack_2a0 = _sqc2(auVar11);
    FVector::FVector(auStack_200,auStack_2a0);
    pfVar8[0xc] = auStack_200._0_4_;
    pfVar8[0xd] = auStack_200._4_4_;
    pfVar8[0xe] = fStack_1f8;
    pfVar8[0xf] = fStack_1f4;
  }
  return;
}

// JP: 0x002b9dc0  CreateVertex__15FpObjectTnderBHFv  =  FpObjectTnderBH::CreateVertex
void FpObjectTnderBH::CreateVertex(int this)

{
  undefined1 auVar1 [16];
  undefined1 auVar2 [16];
  undefined1 auVar3 [16];
  undefined1 auVar4 [16];
  undefined1 auVar5 [16];
  undefined1 auVar6 [16];
  undefined1 auVar7 [16];
  undefined1 auVar8 [16];
  undefined1 auVar9 [16];
  undefined1 auVar10 [16];
  undefined1 auVar11 [16];
  undefined1 auVar12 [16];
  undefined1 auVar13 [16];
  undefined1 auVar14 [16];
  int iVar15;
  int iVar16;
  float fVar17;
  undefined1 auVar18 [16];
  undefined1 auVar19 [16];
  undefined1 auStack_720 [16];
  undefined1 auStack_710 [16];
  undefined1 auStack_700 [16];
  undefined1 auStack_6f0 [16];
  undefined1 auStack_6e0 [16];
  undefined1 auStack_6d0 [16];
  undefined1 auStack_6c0 [16];
  undefined1 auStack_6b0 [16];
  undefined1 auStack_6a0 [16];
  undefined1 auStack_690 [16];
  undefined1 auStack_680 [16];
  undefined1 auStack_670 [16];
  undefined1 auStack_660 [16];
  undefined1 auStack_650 [16];
  undefined1 auStack_640 [16];
  undefined1 auStack_630 [16];
  undefined1 auStack_620 [16];
  undefined1 auStack_610 [16];
  undefined1 auStack_600 [16];
  undefined1 auStack_5f0 [16];
  undefined1 auStack_5e0 [16];
  undefined1 auStack_5d0 [16];
  undefined1 auStack_5c0 [16];
  undefined1 auStack_5b0 [16];
  undefined1 auStack_5a0 [16];
  undefined1 auStack_590 [16];
  undefined1 auStack_580 [16];
  undefined1 auStack_570 [16];
  undefined1 auStack_560 [16];
  undefined1 auStack_550 [16];
  undefined1 auStack_540 [16];
  undefined1 auStack_530 [16];
  undefined1 auStack_520 [16];
  undefined1 auStack_510 [16];
  undefined1 auStack_500 [16];
  undefined1 auStack_4f0 [16];
  undefined1 auStack_4e0 [16];
  undefined1 auStack_4d0 [16];
  undefined1 auStack_4c0 [16];
  undefined1 auStack_4b0 [16];
  undefined1 auStack_4a0 [16];
  undefined1 auStack_490 [16];
  undefined1 auStack_480 [16];
  undefined1 auStack_470 [16];
  undefined1 auStack_460 [16];
  undefined1 auStack_450 [16];
  undefined1 auStack_440 [16];
  undefined1 auStack_430 [16];
  undefined1 auStack_420 [16];
  undefined1 auStack_410 [16];
  undefined1 auStack_400 [16];
  undefined1 auStack_3f0 [16];
  undefined1 auStack_3e0 [16];
  undefined1 auStack_3d0 [16];
  undefined1 auStack_3c0 [16];
  undefined1 auStack_3b0 [16];
  undefined1 auStack_3a0 [8];
  undefined4 uStack_398;
  undefined4 uStack_394;
  undefined1 auStack_390 [16];
  undefined1 auStack_380 [16];
  undefined1 auStack_370 [8];
  undefined4 uStack_368;
  undefined4 uStack_364;
  undefined1 auStack_360 [16];
  undefined1 auStack_350 [16];
  undefined1 auStack_340 [16];
  undefined1 auStack_330 [8];
  undefined4 uStack_328;
  undefined4 uStack_324;
  undefined1 auStack_320 [16];
  undefined1 auStack_310 [16];
  undefined1 auStack_300 [16];
  undefined1 auStack_2f0 [8];
  undefined4 uStack_2e8;
  undefined4 uStack_2e4;
  undefined1 auStack_2e0 [8];
  undefined4 uStack_2d8;
  undefined4 uStack_2d4;
  undefined1 auStack_2d0 [8];
  undefined4 uStack_2c8;
  undefined4 uStack_2c4;
  undefined1 auStack_2c0 [8];
  undefined4 uStack_2b8;
  undefined4 uStack_2b4;
  undefined1 auStack_2b0 [16];
  undefined1 auStack_2a0 [16];
  undefined1 auStack_290 [8];
  undefined4 uStack_288;
  undefined4 uStack_284;
  undefined1 auStack_280 [16];
  undefined1 auStack_270 [16];
  undefined1 auStack_260 [8];
  undefined4 uStack_258;
  undefined4 uStack_254;
  undefined1 auStack_250 [16];
  undefined1 auStack_240 [16];
  undefined1 auStack_230 [16];
  undefined1 auStack_220 [8];
  undefined4 uStack_218;
  undefined4 uStack_214;
  undefined1 auStack_210 [16];
  undefined1 auStack_200 [16];
  undefined1 auStack_1f0 [16];
  undefined1 auStack_1e0 [8];
  undefined4 uStack_1d8;
  undefined4 uStack_1d4;
  undefined1 auStack_1d0 [8];
  undefined4 uStack_1c8;
  undefined4 uStack_1c4;
  undefined1 auStack_1c0 [8];
  undefined4 uStack_1b8;
  undefined4 uStack_1b4;
  undefined1 auStack_1b0 [16];
  undefined1 auStack_1a0 [8];
  undefined4 uStack_198;
  undefined4 uStack_194;
  undefined1 auStack_190 [16];
  undefined1 auStack_180 [8];
  undefined4 uStack_178;
  undefined4 uStack_174;
  undefined1 auStack_170 [16];
  undefined1 auStack_160 [16];
  undefined1 auStack_150 [8];
  undefined4 uStack_148;
  undefined4 uStack_144;
  undefined1 auStack_140 [16];
  undefined1 auStack_130 [16];
  undefined1 auStack_120 [8];
  undefined4 uStack_118;
  undefined4 uStack_114;
  undefined1 auStack_110 [8];
  undefined4 uStack_108;
  undefined4 uStack_104;
  undefined1 auStack_100 [8];
  undefined4 uStack_f8;
  undefined4 uStack_f4;
  undefined1 auStack_f0 [16];
  undefined1 auStack_e0 [8];
  undefined4 uStack_d8;
  undefined4 uStack_d4;
  undefined1 auStack_d0 [16];
  undefined1 auStack_c0 [8];
  undefined4 uStack_b8;
  undefined4 uStack_b4;
  undefined1 auStack_b0 [16];
  undefined1 auStack_a0 [16];
  undefined1 auStack_90 [8];
  undefined4 uStack_88;
  undefined4 uStack_84;
  undefined1 auStack_80 [16];
  undefined1 auStack_70 [16];
  undefined1 auStack_60 [8];
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined1 auStack_50 [8];
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined1 auStack_40 [8];
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined1 auStack_30 [8];
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  if (this->i8_294 == '\0') {
    auVar18 = _lqc2(*(undefined1 (*) [16])(this->i32_1fc + 0x30));
    auVar19 = _lqc2(*(undefined1 (*) [16])(this + 0x210));
    auVar18 = _vsub(auVar18,auVar19);
    auStack_3e0 = _sqc2(auVar18);
    FVector::FVector(auStack_40,auStack_3e0);
    uStack_10 = auStack_40._0_4_;
    uStack_c = auStack_40._4_4_;
    uStack_8 = uStack_38;
    uStack_4 = uStack_34;
  }
  else {
    auVar18 = _lqc2(*(undefined1 (*) [16])(this->i32_1fc + 0x30));
    auVar19 = _lqc2(*(undefined1 (*) [16])
                     (this->i32_1fc + (this->i32_1f4 + -1) * 0xf0 + 0x30));
    auVar18 = _vsub(auVar18,auVar19);
    auStack_3d0 = _sqc2(auVar18);
    FVector::FVector(auStack_30,auStack_3d0);
    uStack_10 = auStack_30._0_4_;
    uStack_c = auStack_30._4_4_;
    uStack_8 = uStack_28;
    uStack_4 = uStack_24;
  }
  FVector::OuterProduct(auStack_50,&uStack_10,this + 0x260);
  uStack_20 = auStack_50._0_4_;
  uStack_1c = auStack_50._4_4_;
  uStack_18 = uStack_48;
  uStack_14 = uStack_44;
  FVector::Normalize(&uStack_20);
  auVar18._4_4_ = uStack_1c;
  auVar18._0_4_ = uStack_20;
  auVar18._8_4_ = uStack_18;
  auVar18._12_4_ = uStack_14;
  auVar18 = _lqc2(auVar18);
  auVar19 = _qmtc2(-this->f32_290);
  auVar18 = _vmulbc(auVar18,auVar19);
  auStack_630 = _sqc2(auVar18);
  FVector::FVector(auStack_80,auStack_630);
  auVar18 = _lqc2(auStack_80);
  auVar19 = _qmtc2(0x40400000);
  auVar18 = _vmulbc(auVar18,auVar19);
  auStack_530 = _sqc2(auVar18);
  FVector::FVector(auStack_70,auStack_530);
  auVar18 = _lqc2(*(undefined1 (*) [16])(this + 0x210));
  auVar19 = _lqc2(auStack_70);
  auVar18 = _vadd(auVar18,auVar19);
  auStack_3f0 = _sqc2(auVar18);
  FVector::FVector(auStack_60,auStack_3f0);
  this->i32_220 = auStack_60._0_4_;
  this->i32_224 = auStack_60._4_4_;
  this->u32_228 = uStack_58;
  this->u32_22c = uStack_54;
  auVar19._4_4_ = uStack_1c;
  auVar19._0_4_ = uStack_20;
  auVar19._8_4_ = uStack_18;
  auVar19._12_4_ = uStack_14;
  auVar18 = _lqc2(auVar19);
  auVar19 = _qmtc2(this->u32_290);
  auVar18 = _vmulbc(auVar18,auVar19);
  auStack_640 = _sqc2(auVar18);
  FVector::FVector(auStack_b0,auStack_640);
  auVar18 = _lqc2(auStack_b0);
  auVar19 = _qmtc2(0x40400000);
  auVar18 = _vmulbc(auVar18,auVar19);
  auStack_540 = _sqc2(auVar18);
  FVector::FVector(auStack_a0,auStack_540);
  auVar18 = _lqc2(*(undefined1 (*) [16])(this + 0x210));
  auVar19 = _lqc2(auStack_a0);
  auVar18 = _vadd(auVar18,auVar19);
  auStack_400 = _sqc2(auVar18);
  FVector::FVector(auStack_90,auStack_400);
  this->i32_230 = auStack_90._0_4_;
  this->i32_234 = auStack_90._4_4_;
  this->u32_238 = uStack_88;
  this->u32_23c = uStack_84;
  auVar1._4_4_ = uStack_1c;
  auVar1._0_4_ = uStack_20;
  auVar1._8_4_ = uStack_18;
  auVar1._12_4_ = uStack_14;
  auVar18 = _lqc2(auVar1);
  auVar19 = _qmtc2(-this->f32_290);
  auVar18 = _vmulbc(auVar18,auVar19);
  auStack_550 = _sqc2(auVar18);
  FVector::FVector(auStack_d0,auStack_550);
  auVar18 = _lqc2(*(undefined1 (*) [16])(this + 0x210));
  auVar19 = _lqc2(auStack_d0);
  auVar18 = _vadd(auVar18,auVar19);
  auStack_410 = _sqc2(auVar18);
  FVector::FVector(auStack_c0,auStack_410);
  this->i32_240 = auStack_c0._0_4_;
  this->i32_244 = auStack_c0._4_4_;
  this->u32_248 = uStack_b8;
  this->u32_24c = uStack_b4;
  auVar2._4_4_ = uStack_1c;
  auVar2._0_4_ = uStack_20;
  auVar2._8_4_ = uStack_18;
  auVar2._12_4_ = uStack_14;
  auVar18 = _lqc2(auVar2);
  auVar19 = _qmtc2(this->u32_290);
  auVar18 = _vmulbc(auVar18,auVar19);
  auStack_560 = _sqc2(auVar18);
  FVector::FVector(auStack_f0,auStack_560);
  auVar18 = _lqc2(*(undefined1 (*) [16])(this + 0x210));
  auVar19 = _lqc2(auStack_f0);
  auVar18 = _vadd(auVar18,auVar19);
  auStack_420 = _sqc2(auVar18);
  FVector::FVector(auStack_e0,auStack_420);
  this->i32_250 = auStack_e0._0_4_;
  this->i32_254 = auStack_e0._4_4_;
  this->u32_258 = uStack_d8;
  this->u32_25c = uStack_d4;
  if (1 < this->i32_1f4) {
    auVar18 = _lqc2(*(undefined1 (*) [16])(this->i32_1fc + 0x120));
    auVar19 = _lqc2(*(undefined1 (*) [16])(this + 0x210));
    auVar18 = _vsub(auVar18,auVar19);
    auStack_430 = _sqc2(auVar18);
    FVector::FVector(auStack_100,auStack_430);
    uStack_10 = auStack_100._0_4_;
    uStack_c = auStack_100._4_4_;
    uStack_8 = uStack_f8;
    uStack_4 = uStack_f4;
    FVector::OuterProduct(auStack_110,&uStack_10,this + 0x260);
    uStack_20 = auStack_110._0_4_;
    uStack_1c = auStack_110._4_4_;
    uStack_18 = uStack_108;
    uStack_14 = uStack_104;
    FVector::Normalize(&uStack_20);
  }
  iVar16 = this->i32_1fc;
  auVar3._4_4_ = uStack_1c;
  auVar3._0_4_ = uStack_20;
  auVar3._8_4_ = uStack_18;
  auVar3._12_4_ = uStack_14;
  auVar18 = _lqc2(auVar3);
  auVar19 = _qmtc2(-this->f32_290);
  auVar18 = _vmulbc(auVar18,auVar19);
  auStack_650 = _sqc2(auVar18);
  FVector::FVector(auStack_140,auStack_650);
  auVar18 = _lqc2(auStack_140);
  auVar19 = _qmtc2(0x40400000);
  auVar18 = _vmulbc(auVar18,auVar19);
  auStack_570 = _sqc2(auVar18);
  FVector::FVector(auStack_130,auStack_570);
  auVar18 = _lqc2(*(undefined1 (*) [16])(iVar16 + 0x30));
  auVar19 = _lqc2(auStack_130);
  auVar18 = _vadd(auVar18,auVar19);
  auStack_440 = _sqc2(auVar18);
  FVector::FVector(auStack_120,auStack_440);
  iVar16->i32_70 = auStack_120._0_4_;
  iVar16->i32_74 = auStack_120._4_4_;
  iVar16->u32_78 = uStack_118;
  iVar16->u32_7c = uStack_114;
  auVar4._4_4_ = uStack_1c;
  auVar4._0_4_ = uStack_20;
  auVar4._8_4_ = uStack_18;
  auVar4._12_4_ = uStack_14;
  auVar18 = _lqc2(auVar4);
  auVar19 = _qmtc2(this->u32_290);
  auVar18 = _vmulbc(auVar18,auVar19);
  auStack_660 = _sqc2(auVar18);
  FVector::FVector(auStack_170,auStack_660);
  auVar18 = _lqc2(auStack_170);
  auVar19 = _qmtc2(0x40400000);
  auVar18 = _vmulbc(auVar18,auVar19);
  auStack_580 = _sqc2(auVar18);
  FVector::FVector(auStack_160,auStack_580);
  auVar18 = _lqc2(*(undefined1 (*) [16])(iVar16 + 0x30));
  auVar19 = _lqc2(auStack_160);
  auVar18 = _vadd(auVar18,auVar19);
  auStack_450 = _sqc2(auVar18);
  FVector::FVector(auStack_150,auStack_450);
  iVar16->i32_80 = auStack_150._0_4_;
  iVar16->i32_84 = auStack_150._4_4_;
  iVar16->u32_88 = uStack_148;
  iVar16->u32_8c = uStack_144;
  auVar5._4_4_ = uStack_1c;
  auVar5._0_4_ = uStack_20;
  auVar5._8_4_ = uStack_18;
  auVar5._12_4_ = uStack_14;
  auVar18 = _lqc2(auVar5);
  auVar19 = _qmtc2(-this->f32_290);
  auVar18 = _vmulbc(auVar18,auVar19);
  auStack_590 = _sqc2(auVar18);
  FVector::FVector(auStack_190,auStack_590);
  auVar18 = _lqc2(*(undefined1 (*) [16])(iVar16 + 0x30));
  auVar19 = _lqc2(auStack_190);
  auVar18 = _vadd(auVar18,auVar19);
  auStack_460 = _sqc2(auVar18);
  FVector::FVector(auStack_180,auStack_460);
  iVar16->i32_90 = auStack_180._0_4_;
  iVar16->i32_94 = auStack_180._4_4_;
  iVar16->u32_98 = uStack_178;
  iVar16->u32_9c = uStack_174;
  auVar6._4_4_ = uStack_1c;
  auVar6._0_4_ = uStack_20;
  auVar6._8_4_ = uStack_18;
  auVar6._12_4_ = uStack_14;
  auVar18 = _lqc2(auVar6);
  auVar19 = _qmtc2(this->u32_290);
  auVar18 = _vmulbc(auVar18,auVar19);
  auStack_5a0 = _sqc2(auVar18);
  FVector::FVector(auStack_1b0,auStack_5a0);
  auVar18 = _lqc2(*(undefined1 (*) [16])(iVar16 + 0x30));
  auVar19 = _lqc2(auStack_1b0);
  auVar18 = _vadd(auVar18,auVar19);
  auStack_470 = _sqc2(auVar18);
  FVector::FVector(auStack_1a0,auStack_470);
  iVar16->i32_a0 = auStack_1a0._0_4_;
  iVar16->i32_a4 = auStack_1a0._4_4_;
  iVar16->u32_a8 = uStack_198;
  iVar16->u32_ac = uStack_194;
  for (iVar15 = 1; iVar15 < this->i32_1f4 + -1; iVar15 = iVar15 + 1) {
    auVar18 = _lqc2(*(undefined1 (*) [16])(this->i32_1fc + (iVar15 + 1) * 0xf0 + 0x30));
    auVar19 = _lqc2(*(undefined1 (*) [16])(this->i32_1fc + (iVar15 + -1) * 0xf0 + 0x30))
    ;
    auVar18 = _vsub(auVar18,auVar19);
    auStack_480 = _sqc2(auVar18);
    FVector::FVector(auStack_1c0,auStack_480);
    uStack_10 = auStack_1c0._0_4_;
    uStack_c = auStack_1c0._4_4_;
    uStack_8 = uStack_1b8;
    uStack_4 = uStack_1b4;
    FVector::OuterProduct(auStack_1d0,&uStack_10,this + 0x260);
    uStack_20 = auStack_1d0._0_4_;
    uStack_1c = auStack_1d0._4_4_;
    uStack_18 = uStack_1c8;
    uStack_14 = uStack_1c4;
    FVector::Normalize(&uStack_20);
    fVar17 = (float)iVar15 * this->f32_2ac + 1.0;
    auVar7._4_4_ = uStack_1c;
    auVar7._0_4_ = uStack_20;
    auVar7._8_4_ = uStack_18;
    auVar7._12_4_ = uStack_14;
    auVar18 = _lqc2(auVar7);
    auVar19 = _qmtc2(-this->f32_290);
    auVar18 = _vmulbc(auVar18,auVar19);
    auStack_670 = _sqc2(auVar18);
    FVector::FVector(auStack_210,auStack_670);
    auVar18 = _lqc2(auStack_210);
    auVar19 = _qmtc2(fVar17);
    auVar18 = _vmulbc(auVar18,auVar19);
    auStack_680 = _sqc2(auVar18);
    FVector::FVector(auStack_200,auStack_680);
    auVar18 = _lqc2(auStack_200);
    auVar19 = _qmtc2(0x40400000);
    auVar18 = _vmulbc(auVar18,auVar19);
    auStack_5b0 = _sqc2(auVar18);
    FVector::FVector(auStack_1f0,auStack_5b0);
    auVar18 = _lqc2(*(undefined1 (*) [16])(iVar16 + 0x120));
    auVar19 = _lqc2(auStack_1f0);
    auVar18 = _vadd(auVar18,auVar19);
    auStack_490 = _sqc2(auVar18);
    FVector::FVector(auStack_1e0,auStack_490);
    iVar16->i32_160 = auStack_1e0._0_4_;
    iVar16->i32_164 = auStack_1e0._4_4_;
    iVar16->u32_168 = uStack_1d8;
    iVar16->u32_16c = uStack_1d4;
    auVar8._4_4_ = uStack_1c;
    auVar8._0_4_ = uStack_20;
    auVar8._8_4_ = uStack_18;
    auVar8._12_4_ = uStack_14;
    auVar18 = _lqc2(auVar8);
    auVar19 = _qmtc2(this->u32_290);
    auVar18 = _vmulbc(auVar18,auVar19);
    auStack_690 = _sqc2(auVar18);
    FVector::FVector(auStack_250,auStack_690);
    auVar18 = _lqc2(auStack_250);
    auVar19 = _qmtc2(fVar17);
    auVar18 = _vmulbc(auVar18,auVar19);
    auStack_6a0 = _sqc2(auVar18);
    FVector::FVector(auStack_240,auStack_6a0);
    auVar18 = _lqc2(auStack_240);
    auVar19 = _qmtc2(0x40400000);
    auVar18 = _vmulbc(auVar18,auVar19);
    auStack_5c0 = _sqc2(auVar18);
    FVector::FVector(auStack_230,auStack_5c0);
    auVar18 = _lqc2(*(undefined1 (*) [16])(iVar16 + 0x120));
    auVar19 = _lqc2(auStack_230);
    auVar18 = _vadd(auVar18,auVar19);
    auStack_4a0 = _sqc2(auVar18);
    FVector::FVector(auStack_220,auStack_4a0);
    iVar16->i32_170 = auStack_220._0_4_;
    iVar16->i32_174 = auStack_220._4_4_;
    iVar16->u32_178 = uStack_218;
    iVar16->u32_17c = uStack_214;
    auVar9._4_4_ = uStack_1c;
    auVar9._0_4_ = uStack_20;
    auVar9._8_4_ = uStack_18;
    auVar9._12_4_ = uStack_14;
    auVar18 = _lqc2(auVar9);
    auVar19 = _qmtc2(-this->f32_290);
    auVar18 = _vmulbc(auVar18,auVar19);
    auStack_6b0 = _sqc2(auVar18);
    FVector::FVector(auStack_280,auStack_6b0);
    auVar18 = _lqc2(auStack_280);
    auVar19 = _qmtc2(fVar17);
    auVar18 = _vmulbc(auVar18,auVar19);
    auStack_5d0 = _sqc2(auVar18);
    FVector::FVector(auStack_270,auStack_5d0);
    auVar18 = _lqc2(*(undefined1 (*) [16])(iVar16 + 0x120));
    auVar19 = _lqc2(auStack_270);
    auVar18 = _vadd(auVar18,auVar19);
    auStack_4b0 = _sqc2(auVar18);
    FVector::FVector(auStack_260,auStack_4b0);
    iVar16->i32_180 = auStack_260._0_4_;
    iVar16->i32_184 = auStack_260._4_4_;
    iVar16->u32_188 = uStack_258;
    iVar16->u32_18c = uStack_254;
    auVar10._4_4_ = uStack_1c;
    auVar10._0_4_ = uStack_20;
    auVar10._8_4_ = uStack_18;
    auVar10._12_4_ = uStack_14;
    auVar18 = _lqc2(auVar10);
    auVar19 = _qmtc2(this->u32_290);
    auVar18 = _vmulbc(auVar18,auVar19);
    auStack_6c0 = _sqc2(auVar18);
    FVector::FVector(auStack_2b0,auStack_6c0);
    auVar18 = _lqc2(auStack_2b0);
    auVar19 = _qmtc2(fVar17);
    auVar18 = _vmulbc(auVar18,auVar19);
    auStack_5e0 = _sqc2(auVar18);
    FVector::FVector(auStack_2a0,auStack_5e0);
    auVar18 = _lqc2(*(undefined1 (*) [16])(iVar16 + 0x120));
    auVar19 = _lqc2(auStack_2a0);
    auVar18 = _vadd(auVar18,auVar19);
    auStack_4c0 = _sqc2(auVar18);
    FVector::FVector(auStack_290,auStack_4c0);
    iVar16->i32_190 = auStack_290._0_4_;
    iVar16->i32_194 = auStack_290._4_4_;
    iVar16->u32_198 = uStack_288;
    iVar16->u32_19c = uStack_284;
    iVar16 = iVar16 + 0xf0;
  }
  if (this->i8_294 == '\0') {
    auVar18 = _lqc2(*(undefined1 (*) [16])
                     (this->i32_1fc + (this->i32_1f4 + -1) * 0xf0 + 0x30));
    auVar19 = _lqc2(*(undefined1 (*) [16])
                     (this->i32_1fc + (this->i32_1f4 + -2) * 0xf0 + 0x30));
    auVar18 = _vsub(auVar18,auVar19);
    auStack_4e0 = _sqc2(auVar18);
    FVector::FVector(auStack_2d0,auStack_4e0);
    uStack_10 = auStack_2d0._0_4_;
    uStack_c = auStack_2d0._4_4_;
    uStack_8 = uStack_2c8;
    uStack_4 = uStack_2c4;
  }
  else {
    auVar18 = _lqc2(*(undefined1 (*) [16])(this->i32_1fc + 0x30));
    auVar19 = _lqc2(*(undefined1 (*) [16])
                     (this->i32_1fc + (this->i32_1f4 + -1) * 0xf0 + 0x30));
    auVar18 = _vsub(auVar18,auVar19);
    auStack_4d0 = _sqc2(auVar18);
    FVector::FVector(auStack_2c0,auStack_4d0);
    uStack_10 = auStack_2c0._0_4_;
    uStack_c = auStack_2c0._4_4_;
    uStack_8 = uStack_2b8;
    uStack_4 = uStack_2b4;
  }
  FVector::OuterProduct(auStack_2e0,&uStack_10,this + 0x260);
  uStack_20 = auStack_2e0._0_4_;
  uStack_1c = auStack_2e0._4_4_;
  uStack_18 = uStack_2d8;
  uStack_14 = uStack_2d4;
  FVector::Normalize(&uStack_20);
  fVar17 = (float)(this->i32_1f4 + -1) * this->f32_2ac + 1.0;
  iVar16 = this->i32_1fc + (this->i32_1f4 + -1) * 0xf0;
  auVar11._4_4_ = uStack_1c;
  auVar11._0_4_ = uStack_20;
  auVar11._8_4_ = uStack_18;
  auVar11._12_4_ = uStack_14;
  auVar18 = _lqc2(auVar11);
  auVar19 = _qmtc2(-this->f32_290);
  auVar18 = _vmulbc(auVar18,auVar19);
  auStack_6d0 = _sqc2(auVar18);
  FVector::FVector(auStack_320,auStack_6d0);
  auVar18 = _lqc2(auStack_320);
  auVar19 = _qmtc2(fVar17);
  auVar18 = _vmulbc(auVar18,auVar19);
  auStack_6e0 = _sqc2(auVar18);
  FVector::FVector(auStack_310,auStack_6e0);
  auVar18 = _lqc2(auStack_310);
  auVar19 = _qmtc2(0x40400000);
  auVar18 = _vmulbc(auVar18,auVar19);
  auStack_5f0 = _sqc2(auVar18);
  FVector::FVector(auStack_300,auStack_5f0);
  auVar18 = _lqc2(*(undefined1 (*) [16])(iVar16 + 0x30));
  auVar19 = _lqc2(auStack_300);
  auVar18 = _vadd(auVar18,auVar19);
  auStack_4f0 = _sqc2(auVar18);
  FVector::FVector(auStack_2f0,auStack_4f0);
  iVar16->i32_70 = auStack_2f0._0_4_;
  iVar16->i32_74 = auStack_2f0._4_4_;
  iVar16->u32_78 = uStack_2e8;
  iVar16->u32_7c = uStack_2e4;
  auVar12._4_4_ = uStack_1c;
  auVar12._0_4_ = uStack_20;
  auVar12._8_4_ = uStack_18;
  auVar12._12_4_ = uStack_14;
  auVar18 = _lqc2(auVar12);
  auVar19 = _qmtc2(this->u32_290);
  auVar18 = _vmulbc(auVar18,auVar19);
  auStack_6f0 = _sqc2(auVar18);
  FVector::FVector(auStack_360,auStack_6f0);
  auVar18 = _lqc2(auStack_360);
  auVar19 = _qmtc2(fVar17);
  auVar18 = _vmulbc(auVar18,auVar19);
  auStack_700 = _sqc2(auVar18);
  FVector::FVector(auStack_350,auStack_700);
  auVar18 = _lqc2(auStack_350);
  auVar19 = _qmtc2(0x40400000);
  auVar18 = _vmulbc(auVar18,auVar19);
  auStack_600 = _sqc2(auVar18);
  FVector::FVector(auStack_340,auStack_600);
  auVar18 = _lqc2(*(undefined1 (*) [16])(iVar16 + 0x30));
  auVar19 = _lqc2(auStack_340);
  auVar18 = _vadd(auVar18,auVar19);
  auStack_500 = _sqc2(auVar18);
  FVector::FVector(auStack_330,auStack_500);
  iVar16->i32_80 = auStack_330._0_4_;
  iVar16->i32_84 = auStack_330._4_4_;
  iVar16->u32_88 = uStack_328;
  iVar16->u32_8c = uStack_324;
  auVar13._4_4_ = uStack_1c;
  auVar13._0_4_ = uStack_20;
  auVar13._8_4_ = uStack_18;
  auVar13._12_4_ = uStack_14;
  auVar18 = _lqc2(auVar13);
  auVar19 = _qmtc2(-this->f32_290);
  auVar18 = _vmulbc(auVar18,auVar19);
  auStack_710 = _sqc2(auVar18);
  FVector::FVector(auStack_390,auStack_710);
  auVar18 = _lqc2(auStack_390);
  auVar19 = _qmtc2(fVar17);
  auVar18 = _vmulbc(auVar18,auVar19);
  auStack_610 = _sqc2(auVar18);
  FVector::FVector(auStack_380,auStack_610);
  auVar18 = _lqc2(*(undefined1 (*) [16])(iVar16 + 0x30));
  auVar19 = _lqc2(auStack_380);
  auVar18 = _vadd(auVar18,auVar19);
  auStack_510 = _sqc2(auVar18);
  FVector::FVector(auStack_370,auStack_510);
  iVar16->i32_90 = auStack_370._0_4_;
  iVar16->i32_94 = auStack_370._4_4_;
  iVar16->u32_98 = uStack_368;
  iVar16->u32_9c = uStack_364;
  auVar14._4_4_ = uStack_1c;
  auVar14._0_4_ = uStack_20;
  auVar14._8_4_ = uStack_18;
  auVar14._12_4_ = uStack_14;
  auVar18 = _lqc2(auVar14);
  auVar19 = _qmtc2(this->u32_290);
  auVar18 = _vmulbc(auVar18,auVar19);
  auStack_720 = _sqc2(auVar18);
  FVector::FVector(auStack_3c0,auStack_720);
  auVar18 = _lqc2(auStack_3c0);
  auVar19 = _qmtc2(fVar17);
  auVar18 = _vmulbc(auVar18,auVar19);
  auStack_620 = _sqc2(auVar18);
  FVector::FVector(auStack_3b0,auStack_620);
  auVar18 = _lqc2(*(undefined1 (*) [16])(iVar16 + 0x30));
  auVar19 = _lqc2(auStack_3b0);
  auVar18 = _vadd(auVar18,auVar19);
  auStack_520 = _sqc2(auVar18);
  FVector::FVector(auStack_3a0,auStack_520);
  iVar16->i32_a0 = auStack_3a0._0_4_;
  iVar16->i32_a4 = auStack_3a0._4_4_;
  iVar16->u32_a8 = uStack_398;
  iVar16->u32_ac = uStack_394;
  return;
}

// JP: 0x002bacf0  CalculateFunc__15FpObjectTnderBHFv  =  FpObjectTnderBH::CalculateFunc
void FpObjectTnderBH::CalculateFunc(undefined8 this)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int this;
  float fVar5;
  undefined1 auStack_40 [40];
  undefined4 uStack_18;
  undefined4 uStack_14;
  
  
  fVar5 = (float)FpPrim::GetFrameSpeed(this->u32_8);
  iVar1 = rand();
  this->f32_298 = (float)iVar1 / 2.1474836e+09;
  iVar1 = this->i32_1fc;
  for (iVar2 = 0; iVar2 < this->i32_1f8; iVar2 = iVar2 + 1) {
    iVar1->f32_4 = iVar1->f32_4 + fVar5;
    iVar1 = iVar1 + 0xf0;
  }
  if (**(float **)(this + 0x1fc) <= *(float *)(this->i32_1fc + 4)) {
    Matrix::Matrix(auStack_40,CApp::camera + 0x240);
    this->i32_260 = (int)auStack_40._32_8_;
    this->i32_264 = SUB84(auStack_40._32_8_,4);
    this->u32_268 = uStack_18;
    this->u32_26c = uStack_14;
    for (iVar1 = 0; iVar1 < this->i32_1f4; iVar1 = iVar1 + 1) {
      (**(code **)(this->i32_1e4 + 0x4c))(this,iVar1,0);
    }
  }
  iVar1 = this->i32_1fc;
  iVar2 = this->i32_1f8;
  if (iVar2 < 0) {
    iVar2 = iVar2 + 1;
  }
  iVar2 = iVar2 >> 1;
  if (iVar1->f32_4 < 1.0) {
    for (iVar3 = 0; iVar3 < iVar2; iVar3 = iVar3 + 1) {
      iVar1->u32_bc = iVar1->u32_b8;
      iVar1 = iVar1 + 0xf0;
    }
    for (; iVar2 < this->i32_1f8; iVar2 = iVar2 + 1) {
      iVar1->u32_bc = 0;
      iVar1 = iVar1 + 0xf0;
    }
  }
  else if (iVar1->f32_4 < 2.0) {
    for (iVar2 = 0; iVar2 < this->i32_1f8; iVar2 = iVar2 + 1) {
      iVar1->u32_bc = 0;
      iVar1 = iVar1 + 0xf0;
    }
  }
  else {
    for (iVar2 = 0; iVar2 < this->i32_1f8; iVar2 = iVar2 + 1) {
      iVar1->u32_bc = iVar1->u32_b8;
      iVar1 = iVar1 + 0xf0;
    }
  }
  FpObjectTnderBH::CreateVertex(this);
  this->i32_90 = this->i32_90 + 1;
  if (0x168 < this->i32_90) {
    this->i32_90 = this->i32_90 + -0x168;
  }
  return;
}

// JP: 0x002baf80  __ct__16FpObjectTnderBH2FiPv  =  FpObjectTnderBH2::FpObjectTnderBH2
int FpObjectTnderBH2::FpObjectTnderBH2(int this,undefined4 param_2,undefined4 param_3)

{
  FpObjectTnderBH::FpObjectTnderBH(this,param_2,param_3);
  *(undefined1 **)(this + 0x1e4) = FpObjectTnderBH2::__vt;
  return this;
}

// JP: 0x002bafd0  __dt__16FpObjectTnderBH2Fv  =  FpObjectTnderBH2::~FpObjectTnderBH2
int FpObjectTnderBH2::~FpObjectTnderBH2(int this,short param_2)

{
  if (this != 0) {
    *(undefined1 **)(this + 0x1e4) = FpObjectTnderBH2::__vt;
    FpObjectTnderBH::~FpObjectTnderBH(this,0);
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}

// JP: 0x002bb050  CreateData__16FpObjectTnderBH2Fib  =  FpObjectTnderBH2::CreateData
void FpObjectTnderBH2::CreateData(int this,uint param_2,long param_3)

{
  int iVar1;
  undefined1 auVar2 [16];
  undefined1 auVar3 [16];
  undefined1 auVar4 [16];
  undefined1 auVar5 [16];
  float in_zero_lo;
  float in_zero_hi;
  float in_zero_udw;
  float in_register_0000000c;
  uint uVar6;
  int iVar7;
  float *pfVar8;
  undefined4 uVar9;
  float fVar10;
  undefined1 in_vf0 [16];
  undefined1 auVar11 [16];
  undefined1 auVar12 [16];
  undefined1 auVar13 [16];
  undefined1 auStack_340 [16];
  undefined1 auStack_330 [16];
  undefined1 auStack_320 [16];
  undefined1 auStack_310 [16];
  undefined1 auStack_300 [16];
  undefined1 auStack_2f0 [16];
  undefined1 auStack_2e0 [16];
  undefined1 auStack_2d0 [16];
  undefined1 auStack_2c0 [16];
  undefined1 auStack_2b0 [16];
  undefined1 auStack_2a0 [16];
  undefined1 auStack_290 [16];
  undefined1 auStack_280 [16];
  undefined1 auStack_270 [16];
  undefined1 auStack_260 [16];
  undefined1 auStack_250 [16];
  undefined1 auStack_240 [16];
  undefined1 auStack_230 [16];
  undefined1 auStack_220 [16];
  undefined1 auStack_210 [16];
  undefined1 auStack_200 [8];
  float fStack_1f8;
  float fStack_1f4;
  undefined1 auStack_1f0 [8];
  undefined4 uStack_1e8;
  undefined4 uStack_1e4;
  undefined1 auStack_1e0 [8];
  undefined4 uStack_1d8;
  undefined4 uStack_1d4;
  undefined1 auStack_1d0 [16];
  undefined1 auStack_1c0 [16];
  undefined1 auStack_1b0 [16];
  undefined1 auStack_1a0 [8];
  float fStack_198;
  float fStack_194;
  undefined1 auStack_190 [8];
  undefined4 uStack_188;
  undefined4 uStack_184;
  undefined1 auStack_180 [8];
  undefined4 uStack_178;
  undefined4 uStack_174;
  undefined1 auStack_170 [16];
  undefined1 auStack_160 [16];
  undefined1 auStack_150 [16];
  undefined1 auStack_140 [8];
  float fStack_138;
  float fStack_134;
  undefined1 auStack_130 [16];
  undefined1 auStack_120 [8];
  undefined4 uStack_118;
  undefined4 uStack_114;
  undefined1 auStack_110 [8];
  undefined4 uStack_108;
  undefined4 uStack_104;
  undefined1 auStack_100 [8];
  undefined4 uStack_f8;
  undefined4 uStack_f4;
  undefined4 uStack_f0;
  undefined4 uStack_ec;
  float fStack_e8;
  undefined4 uStack_e4;
  undefined4 uStack_e0;
  undefined4 uStack_dc;
  undefined4 uStack_d8;
  undefined4 uStack_d4;
  undefined4 uStack_d0;
  undefined4 uStack_cc;
  undefined4 uStack_c8;
  undefined4 uStack_c4;
  undefined4 uStack_c0;
  undefined4 uStack_bc;
  undefined4 uStack_b8;
  undefined4 uStack_b4;
  undefined4 uStack_b0;
  undefined4 uStack_ac;
  undefined4 uStack_a8;
  undefined4 uStack_a4;
  undefined1 auStack_90 [16];
  undefined1 auStack_80 [16];
  undefined1 auStack_70 [16];
  undefined1 auStack_60 [16];
  undefined1 auStack_50 [16];
  undefined1 auStack_40 [16];
  undefined4 uStack_30;
  undefined4 uStack_2c;
  float fStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  pfVar8 = (float *)(this->i32_1fc + param_2 * 0xf0);
  iVar1 = this->i32_8;
  if (param_3 == 0) {
    pfVar8[1] = 0.0;
  }
  else {
    *pfVar8 = 3.0;
    pfVar8[8] = in_zero_lo;
    pfVar8[9] = in_zero_hi;
    pfVar8[10] = in_zero_udw;
    pfVar8[0xb] = in_register_0000000c;
    uStack_b0 = 0;
    uStack_ac = 0;
    uStack_a8 = 0;
    uStack_a4 = 0;
    pfVar8[0x2c] = 0.0;
    pfVar8[0x2d] = 0.0;
    pfVar8[0x2e] = 0.0;
    pfVar8[0x2f] = 0.0;
    pfVar8[2] = 0.0;
    uStack_c0 = 0x3f800000;
    uStack_bc = 0x3f800000;
    uStack_b8 = 0x3f800000;
    uStack_b4 = 0x3f800000;
    pfVar8[0x10] = 1.0;
    pfVar8[0x11] = 1.0;
    pfVar8[0x12] = 1.0;
    pfVar8[0x13] = 1.0;
    uStack_d0 = 0x3f800000;
    uStack_cc = 0x3f800000;
    uStack_c8 = 0x3f800000;
    uStack_c4 = 0x3f800000;
    pfVar8[0x14] = 1.0;
    pfVar8[0x15] = 1.0;
    pfVar8[0x16] = 1.0;
    pfVar8[0x17] = 1.0;
    uStack_e0 = 0;
    uStack_dc = 0;
    uStack_d8 = 0;
    uStack_d4 = 0x3f800000;
    pfVar8[0x18] = 0.0;
    pfVar8[0x19] = 0.0;
    pfVar8[0x1a] = 0.0;
    pfVar8[0x1b] = 1.0;
    uVar6 = param_2 & 1;
    if (((int)param_2 < 0) && (uVar6 != 0)) {
      uVar6 = uVar6 - 2;
    }
    if (uVar6 == 0) {
      pfVar8[0x34] = 0.0;
      pfVar8[0x30] = 0.0;
      pfVar8[0x35] = 1.0;
      pfVar8[0x31] = 1.0;
      pfVar8[0x36] = 1.0;
      pfVar8[0x32] = 1.0;
      pfVar8[0x37] = 1.0;
      pfVar8[0x33] = 1.0;
    }
    else {
      pfVar8[0x34] = 0.0;
      pfVar8[0x30] = 0.0;
      pfVar8[0x35] = 0.0;
      pfVar8[0x31] = 0.0;
      pfVar8[0x36] = 1.0;
      pfVar8[0x32] = 1.0;
      pfVar8[0x37] = 0.0;
      pfVar8[0x33] = 0.0;
    }
    iVar7 = rand();
    pfVar8[1] = (*pfVar8 * (float)iVar7) / 2.1474836e+09;
  }
  iVar7 = this->i32_1f8;
  if (iVar7 < 0) {
    iVar7 = iVar7 + 1;
  }
  if ((int)param_2 < iVar7 >> 1) {
    pfVar8[0x2e] = (float)(int)param_2 / (float)this->i32_1f8;
  }
  else {
    pfVar8[0x2e] = 1.0 - (float)(int)param_2 / (float)this->i32_1f8;
  }
  iVar7 = rand();
  fVar10 = this->f32_2a4 * (1.0 - ((float)iVar7 * 2.0) / 2.1474836e+09);
  if (param_2 == 0) {
    fStack_28 = -iVar1->f32_90 * 0.6;
    uStack_30 = 0;
    uStack_2c = 0;
    uStack_24 = 0x3f800000;
    auVar11 = _vmr32(in_vf0);
    auVar12 = _vmr32(auVar11);
    auVar13 = _vmr32(auVar12);
    auStack_40 = _sqc2(in_vf0);
    auStack_50 = _sqc2(auVar11);
    auStack_60 = _sqc2(auVar12);
    auStack_70 = _sqc2(auVar13);
    uVar9 = GetRad(-iVar1->f32_94);
    sceVu0RotMatrixX(uVar9,auStack_70,auStack_70);
    Matrix::ApplyMatrix(auStack_80,auStack_70,&uStack_30);
    fStack_e8 = -iVar1->f32_90 * 0.6;
    uStack_f0 = 0xbf800000;
    uStack_ec = 0;
    uStack_e4 = 0x3f800000;
    uStack_30 = 0xbf800000;
    uStack_2c = 0;
    uStack_24 = 0x3f800000;
    fStack_28 = fStack_e8;
    iVar7 = rand();
    uVar9 = GetRad(((float)iVar7 * 360.0) / 2.1474836e+09);
    sceVu0RotMatrixZ(uVar9,auStack_70,auStack_70);
    uVar9 = GetRad(-iVar1->f32_94);
    sceVu0RotMatrixX(uVar9,auStack_70,auStack_70);
    Matrix::ApplyMatrix(auStack_90,auStack_70,&uStack_30);
    auVar11 = _lqc2(auStack_90);
    auVar12 = _lqc2(auStack_80);
    auVar11 = _vsub(auVar11,auVar12);
    auStack_240 = _sqc2(auVar11);
    FVector::FVector(auStack_100,auStack_240);
    uStack_10 = auStack_100._0_4_;
    uStack_c = auStack_100._4_4_;
    uStack_8 = uStack_f8;
    uStack_4 = uStack_f4;
    FVector::Normalize(&uStack_10);
    FVector::OuterProduct(auStack_110,&uStack_10,this + 0x260);
    uStack_20 = auStack_110._0_4_;
    uStack_1c = auStack_110._4_4_;
    uStack_18 = uStack_108;
    uStack_14 = uStack_104;
    FVector::Normalize(&uStack_20);
    auVar3._4_4_ = uStack_c;
    auVar3._0_4_ = uStack_10;
    auVar3._8_4_ = uStack_8;
    auVar3._12_4_ = uStack_4;
    auVar11 = _lqc2(auVar3);
    auVar12 = _qmtc2(this->u32_2a8);
    auVar11 = _vmulbc(auVar11,auVar12);
    auStack_2b0 = _sqc2(auVar11);
    FVector::FVector(auStack_130,auStack_2b0);
    auVar11 = _lqc2(auStack_80);
    auVar12 = _lqc2(auStack_130);
    auVar11 = _vadd(auVar11,auVar12);
    auStack_250 = _sqc2(auVar11);
    FVector::FVector(auStack_120,auStack_250);
    this->i32_210 = auStack_120._0_4_;
    this->i32_214 = auStack_120._4_4_;
    this->u32_218 = uStack_118;
    this->u32_21c = uStack_114;
    auVar4._4_4_ = uStack_c;
    auVar4._0_4_ = uStack_10;
    auVar4._8_4_ = uStack_8;
    auVar4._12_4_ = uStack_4;
    auVar11 = _lqc2(auVar4);
    auVar12 = _qmtc2(this->u32_2a0);
    auVar11 = _vmulbc(auVar11,auVar12);
    auStack_2c0 = _sqc2(auVar11);
    FVector::FVector(auStack_170,auStack_2c0);
    auVar2._4_4_ = uStack_1c;
    auVar2._0_4_ = uStack_20;
    auVar2._8_4_ = uStack_18;
    auVar2._12_4_ = uStack_14;
    auVar11 = _lqc2(auVar2);
    auVar12 = _qmtc2(fVar10);
    auVar11 = _vmulbc(auVar11,auVar12);
    auStack_2d0 = _sqc2(auVar11);
    FVector::FVector(auStack_160,auStack_2d0);
    auVar11 = _lqc2(*(undefined1 (*) [16])(this + 0x210));
    auVar12 = _lqc2(auStack_160);
    auVar11 = _vadd(auVar11,auVar12);
    auStack_2e0 = _sqc2(auVar11);
    FVector::FVector(auStack_150,auStack_2e0);
    auVar11 = _lqc2(auStack_150);
    auVar12 = _lqc2(auStack_170);
    auVar11 = _vadd(auVar11,auVar12);
    auStack_260 = _sqc2(auVar11);
    FVector::FVector(auStack_140,auStack_260);
    pfVar8[0xc] = auStack_140._0_4_;
    pfVar8[0xd] = auStack_140._4_4_;
    pfVar8[0xe] = fStack_138;
    pfVar8[0xf] = fStack_134;
  }
  else if (param_2 == 1) {
    auVar11 = _lqc2(*(undefined1 (*) [16])(this->i32_1fc + 0x30));
    auVar12 = _lqc2(*(undefined1 (*) [16])(this + 0x210));
    auVar11 = _vsub(auVar11,auVar12);
    auStack_270 = _sqc2(auVar11);
    FVector::FVector(auStack_180,auStack_270);
    uStack_10 = auStack_180._0_4_;
    uStack_c = auStack_180._4_4_;
    uStack_8 = uStack_178;
    uStack_4 = uStack_174;
    FVector::Normalize(&uStack_10);
    FVector::OuterProduct(auStack_190,&uStack_10,this + 0x260);
    uStack_20 = auStack_190._0_4_;
    uStack_1c = auStack_190._4_4_;
    uStack_18 = uStack_188;
    uStack_14 = uStack_184;
    FVector::Normalize(&uStack_20);
    auVar5._4_4_ = uStack_c;
    auVar5._0_4_ = uStack_10;
    auVar5._8_4_ = uStack_8;
    auVar5._12_4_ = uStack_4;
    auVar11 = _lqc2(auVar5);
    auVar12 = _qmtc2(this->u32_2a0);
    auVar11 = _vmulbc(auVar11,auVar12);
    auStack_2f0 = _sqc2(auVar11);
    FVector::FVector(auStack_1d0,auStack_2f0);
    auVar13._4_4_ = uStack_1c;
    auVar13._0_4_ = uStack_20;
    auVar13._8_4_ = uStack_18;
    auVar13._12_4_ = uStack_14;
    auVar11 = _lqc2(auVar13);
    auVar12 = _qmtc2(fVar10);
    auVar11 = _vmulbc(auVar11,auVar12);
    auStack_300 = _sqc2(auVar11);
    FVector::FVector(auStack_1c0,auStack_300);
    auVar11 = _lqc2(*(undefined1 (*) [16])(this->i32_1fc + 0x30));
    auVar12 = _lqc2(auStack_1c0);
    auVar11 = _vadd(auVar11,auVar12);
    auStack_310 = _sqc2(auVar11);
    FVector::FVector(auStack_1b0,auStack_310);
    auVar11 = _lqc2(auStack_1b0);
    auVar12 = _lqc2(auStack_1d0);
    auVar11 = _vadd(auVar11,auVar12);
    auStack_280 = _sqc2(auVar11);
    FVector::FVector(auStack_1a0,auStack_280);
    pfVar8[0xc] = auStack_1a0._0_4_;
    pfVar8[0xd] = auStack_1a0._4_4_;
    pfVar8[0xe] = fStack_198;
    pfVar8[0xf] = fStack_194;
  }
  else {
    auVar11 = _lqc2(*(undefined1 (*) [16])(this->i32_1fc + (param_2 - 1) * 0xf0 + 0x30))
    ;
    auVar12 = _lqc2(*(undefined1 (*) [16])(this->i32_1fc + (param_2 - 2) * 0xf0 + 0x30))
    ;
    auVar11 = _vsub(auVar11,auVar12);
    auStack_290 = _sqc2(auVar11);
    FVector::FVector(auStack_1e0,auStack_290);
    uStack_10 = auStack_1e0._0_4_;
    uStack_c = auStack_1e0._4_4_;
    uStack_8 = uStack_1d8;
    uStack_4 = uStack_1d4;
    FVector::Normalize(&uStack_10);
    FVector::OuterProduct(auStack_1f0,&uStack_10,this + 0x260);
    uStack_20 = auStack_1f0._0_4_;
    uStack_1c = auStack_1f0._4_4_;
    uStack_18 = uStack_1e8;
    uStack_14 = uStack_1e4;
    FVector::Normalize(&uStack_20);
    auVar12._4_4_ = uStack_c;
    auVar12._0_4_ = uStack_10;
    auVar12._8_4_ = uStack_8;
    auVar12._12_4_ = uStack_4;
    auVar11 = _lqc2(auVar12);
    auVar12 = _qmtc2(this->u32_2a0);
    auVar11 = _vmulbc(auVar11,auVar12);
    auStack_320 = _sqc2(auVar11);
    FVector::FVector(auStack_230,auStack_320);
    auVar11._4_4_ = uStack_1c;
    auVar11._0_4_ = uStack_20;
    auVar11._8_4_ = uStack_18;
    auVar11._12_4_ = uStack_14;
    auVar11 = _lqc2(auVar11);
    auVar12 = _qmtc2(fVar10);
    auVar11 = _vmulbc(auVar11,auVar12);
    auStack_330 = _sqc2(auVar11);
    FVector::FVector(auStack_220,auStack_330);
    auVar11 = _lqc2(*(undefined1 (*) [16])(this->i32_1fc + (param_2 - 1) * 0xf0 + 0x30))
    ;
    auVar12 = _lqc2(auStack_220);
    auVar11 = _vadd(auVar11,auVar12);
    auStack_340 = _sqc2(auVar11);
    FVector::FVector(auStack_210,auStack_340);
    auVar11 = _lqc2(auStack_210);
    auVar12 = _lqc2(auStack_230);
    auVar11 = _vadd(auVar11,auVar12);
    auStack_2a0 = _sqc2(auVar11);
    FVector::FVector(auStack_200,auStack_2a0);
    pfVar8[0xc] = auStack_200._0_4_;
    pfVar8[0xd] = auStack_200._4_4_;
    pfVar8[0xe] = fStack_1f8;
    pfVar8[0xf] = fStack_1f4;
  }
  return;
}

// JP: 0x002bbae0  __ct__11FpAreaSmokeFv  =  FpAreaSmoke::FpAreaSmoke
undefined8 FpAreaSmoke::FpAreaSmoke(undefined8 this)

{
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  int this;
  
  FpPrim::FpPrim(this);
  
  *(undefined1 **)(this + 0x10) = FpAreaSmoke::__vt;
  this->u32_1c = 0x406570;
  this->u32_70 = in_zero_lo;
  this->u32_74 = in_zero_hi;
  this->u32_78 = in_zero_udw;
  this->u32_7c = in_register_0000000c;
  this->u32_80 = in_zero_lo;
  this->u32_84 = in_zero_hi;
  this->u32_88 = in_zero_udw;
  this->u32_8c = in_register_0000000c;
  this->u32_90 = in_zero_lo;
  this->u32_94 = in_zero_hi;
  this->u32_98 = in_zero_udw;
  this->u32_9c = in_register_0000000c;
  this->u32_a0 = in_zero_lo;
  this->u32_a4 = in_zero_hi;
  this->u32_a8 = in_zero_udw;
  this->u32_ac = in_register_0000000c;
  this->u32_70 = 0;
  this->u32_74 = 0;
  this->u32_78 = 0;
  this->u32_7c = 0;
  this->u32_80 = 0;
  this->u32_84 = 0;
  this->u32_88 = 0;
  this->u32_8c = 0;
  this->u32_90 = 0;
  this->u32_94 = 0;
  this->u32_98 = 0;
  this->u32_9c = 0;
  this->u32_a0 = 0;
  this->u32_a4 = 0;
  this->u32_a8 = 0;
  this->u32_ac = 0;
  this->u32_b0 = 0;
  this->u32_b4 = 0;
  this->u32_b8 = 0;
  this->u32_bc = 0;
  this->u32_c0 = 0;
  this->u32_c4 = 0;
  return this;
}

// JP: 0x002bbc80  __dt__11FpAreaSmokeFv  =  FpAreaSmoke::~FpAreaSmoke
int FpAreaSmoke::~FpAreaSmoke(int this,short param_2)

{
  if (this != 0) {
    *(undefined1 **)(this + 0x10) = FpAreaSmoke::__vt;
    this->u32_1c = 0x406570;
    FpPrim::~FpPrim(this,0);
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}

// JP: 0x002bbd10  Create__11FpAreaSmokeF7FVector7FVector7FVector7FVectoriiffff  =  FpAreaSmoke::Create
void FpAreaSmoke::Create
               (undefined4 this,undefined4 param_2,undefined4 param_3,undefined4 param_4,
               undefined8 param_5,undefined8 *param_6,undefined8 *param_7,undefined8 *param_8,
               undefined8 *param_9,undefined4 param_10,undefined4 param_11)

{
  long lVar1;
  undefined8 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  
  iVar5 = (int)param_5;
  uVar2 = *param_6;
  uVar3 = param_6->u32_1;
  uVar4 = *(undefined4 *)((int)param_6 + 0xc);
  iVar5->i32_70 = (int)uVar2;
  iVar5->i32_74 = (int)((ulong)uVar2 >> 0x20);
  iVar5->u32_78 = uVar3;
  iVar5->u32_7c = uVar4;
  uVar2 = *param_7;
  uVar3 = param_7->u32_1;
  uVar4 = *(undefined4 *)((int)param_7 + 0xc);
  iVar5->i32_80 = (int)uVar2;
  iVar5->i32_84 = (int)((ulong)uVar2 >> 0x20);
  iVar5->u32_88 = uVar3;
  iVar5->u32_8c = uVar4;
  uVar2 = *param_8;
  uVar3 = param_8->u32_1;
  uVar4 = *(undefined4 *)((int)param_8 + 0xc);
  iVar5->i32_90 = (int)uVar2;
  iVar5->i32_94 = (int)((ulong)uVar2 >> 0x20);
  iVar5->u32_98 = uVar3;
  iVar5->u32_9c = uVar4;
  uVar2 = *param_9;
  uVar3 = param_9->u32_1;
  uVar4 = *(undefined4 *)((int)param_9 + 0xc);
  iVar5->i32_a0 = (int)uVar2;
  iVar5->i32_a4 = (int)((ulong)uVar2 >> 0x20);
  iVar5->u32_a8 = uVar3;
  iVar5->u32_ac = uVar4;
  iVar5->u32_b0 = param_4;
  iVar5->u32_b4 = this;
  iVar5->u32_b8 = param_2;
  iVar5->u32_bc = param_3;
  iVar5->u32_c0 = param_10;
  iVar5->u32_c4 = param_11;
  iVar6 = BgEffectMan::eff->i32_1c + 0x8c;
  SetWhiteTex(iVar6);
  PutiPrim::SetTexture(param_5,iVar6,0);
  if (iVar5->i8_58 == '\0') {
    iVar5->u8_24 = iVar5->u8_24 & 0xfe | 1;
  }
  iVar6 = iVar5->i32_c4;
  lVar1 = __nw(0x210);
  uVar2 = 0;
  if (lVar1 != 0) {
    uVar2 = FpObjectAreaSmoke::FpObjectAreaSmoke(lVar1,iVar6 * 0xc + 0x14,0);
  }
  PutiPrim::AddObject(param_5,uVar2);
  (**(code **)(*(int *)((int)uVar2 + 0x1e4) + 0x40))
            (uVar2,iVar5->u32_c4,iVar5->u8_58);
  PutiManager::AddPrim(BgEffectMan::eff,iVar5->u32_54,param_5);
  return;
}

// JP: 0x002bbe70  __ct__17FpObjectAreaSmokeFiPv  =  FpObjectAreaSmoke::FpObjectAreaSmoke
int FpObjectAreaSmoke::FpObjectAreaSmoke(int this,undefined4 param_2,undefined4 param_3)

{
  FpObject::FpObject(this,param_2,param_3);
  *(undefined1 **)(this + 0x1e4) = FpObjectAreaSmoke::__vt;
  return this;
}

// JP: 0x002bbec0  __dt__17FpObjectAreaSmokeFv  =  FpObjectAreaSmoke::~FpObjectAreaSmoke
int FpObjectAreaSmoke::~FpObjectAreaSmoke(int this,short param_2)

{
  if (this != 0) {
    *(undefined1 **)(this + 0x1e4) = FpObjectAreaSmoke::__vt;
    FpObject::~FpObject(this,0);
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}

// JP: 0x002bbf40  CreateData__17FpObjectAreaSmokeFib  =  FpObjectAreaSmoke::CreateData
void FpObjectAreaSmoke::CreateData(int this,int param_2,long param_3)

{
  int iVar1;
  undefined8 uVar2;
  int iVar3;
  float fVar4;
  float fVar5;
  float *pfVar6;
  undefined4 uVar7;
  undefined1 in_vf0 [16];
  undefined1 auVar8 [16];
  undefined1 auVar9 [16];
  undefined1 auVar10 [16];
  undefined1 auStack_c0 [16];
  undefined1 auStack_b0 [8];
  float fStack_a8;
  float fStack_a4;
  undefined8 uStack_a0;
  undefined4 uStack_98;
  undefined4 uStack_94;
  undefined4 uStack_90;
  undefined4 uStack_8c;
  undefined4 uStack_88;
  undefined4 uStack_84;
  undefined4 uStack_80;
  undefined4 uStack_7c;
  undefined4 uStack_78;
  undefined4 uStack_74;
  float fStack_70;
  float fStack_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  float fStack_50;
  float fStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined1 auStack_40 [16];
  undefined1 auStack_30 [16];
  undefined1 auStack_20 [16];
  undefined1 auStack_10 [16];
  
  pfVar6 = (float *)(this->i32_1fc + param_2 * 0xf0);
  iVar1 = this->i32_8;
  if (param_3 == 0) {
    pfVar6[1] = 0.0;
  }
  else {
    *pfVar6 = (float)iVar1->i32_c0;
    if (this->i32_1f8 == 0) {
      trap(7);
    }
    pfVar6[1] = (float)param_2 * (float)(iVar1->i32_c0 / this->i32_1f8);
    pfVar6[2] = 0.0;
    uVar2 = iVar1->u64_80;
    fVar4 = iVar1->f32_88;
    fVar5 = iVar1->f32_8c;
    pfVar6[4] = (float)uVar2;
    pfVar6[5] = (float)((ulong)uVar2 >> 0x20);
    pfVar6[6] = fVar4;
    pfVar6[7] = fVar5;
    pfVar6[5] = pfVar6[5] + iVar1->f32_b0;
    uStack_60 = 0;
    uStack_5c = 0;
    uStack_58 = 0;
    uStack_54 = 0x3f800000;
    pfVar6[8] = 0.0;
    pfVar6[9] = 0.0;
    pfVar6[10] = 0.0;
    pfVar6[0xb] = 1.0;
    fStack_6c = iVar1->f32_b8;
    fStack_70 = iVar1->f32_b4;
    uStack_68 = 0;
    uStack_64 = 0x3f800000;
    pfVar6[0x10] = fStack_70;
    pfVar6[0x11] = fStack_6c;
    pfVar6[0x12] = 0.0;
    pfVar6[0x13] = 1.0;
    uStack_80 = 0;
    uStack_7c = 0;
    uStack_78 = 0;
    uStack_74 = 0x3f800000;
    pfVar6[0x18] = 0.0;
    pfVar6[0x19] = 0.0;
    pfVar6[0x1a] = 0.0;
    pfVar6[0x1b] = 1.0;
    uVar2 = iVar1->u64_90;
    fVar4 = iVar1->f32_98;
    fVar5 = iVar1->f32_9c;
    pfVar6[0x2c] = (float)uVar2;
    pfVar6[0x2d] = (float)((ulong)uVar2 >> 0x20);
    pfVar6[0x2e] = fVar4;
    pfVar6[0x2f] = fVar5;
    pfVar6[0x30] = 0.0;
    pfVar6[0x31] = 0.0;
    pfVar6[0x32] = 0.0;
    pfVar6[0x33] = 1.0;
    pfVar6[0x34] = 1.0;
    pfVar6[0x35] = 0.0;
    pfVar6[0x36] = 1.0;
    pfVar6[0x37] = 1.0;
  }
  pfVar6[0x2f] = 0.0;
  uStack_90 = 0x3f800000;
  uStack_8c = 0x3f800000;
  uStack_88 = 0x3f800000;
  uStack_84 = 0x3f800000;
  pfVar6[0x14] = 1.0;
  pfVar6[0x15] = 1.0;
  pfVar6[0x16] = 1.0;
  pfVar6[0x17] = 1.0;
  auVar8 = _vmr32(in_vf0);
  auVar9 = _vmr32(auVar8);
  auVar10 = _vmr32(auVar9);
  auStack_10 = _sqc2(in_vf0);
  auStack_20 = _sqc2(auVar8);
  auStack_30 = _sqc2(auVar9);
  auStack_40 = _sqc2(auVar10);
  iVar3 = rand();
  uVar7 = GetRad(((float)iVar3 * 360.0) / 2.1474836e+09);
  sceVu0RotMatrixY(uVar7,auStack_40,auStack_40);
  fVar4 = *(float *)(this->i32_1fc + param_2 * 0xf0 + 0x44);
  iVar3 = rand();
  fStack_50 = *(float *)(this->i32_1fc + param_2 * 0xf0 + 0x40) * 0.15 +
              (iVar1->f32_bc * (float)iVar3) / 2.1474836e+09;
  uStack_48 = 0;
  uStack_44 = 0x3f800000;
  fStack_4c = -fVar4 * 0.2;
  Matrix::ApplyMatrix(&uStack_a0,auStack_40,&fStack_50);
  fStack_50 = (float)uStack_a0;
  fStack_4c = (float)((ulong)uStack_a0 >> 0x20);
  uStack_48 = uStack_98;
  uStack_44 = uStack_94;
  auVar8._8_4_ = uStack_98;
  auVar8._0_8_ = uStack_a0;
  auVar8._12_4_ = uStack_94;
  auVar8 = _lqc2(auVar8);
  auVar9 = _lqc2(*(undefined1 (*) [16])(iVar1 + 0x70));
  auVar8 = _vadd(auVar8,auVar9);
  auStack_c0 = _sqc2(auVar8);
  FVector::FVector(auStack_b0,auStack_c0);
  pfVar6[0xc] = auStack_b0._0_4_;
  pfVar6[0xd] = auStack_b0._4_4_;
  pfVar6[0xe] = fStack_a8;
  pfVar6[0xf] = fStack_a4;
  return;
}

// JP: 0x002bc370  Init__17FpObjectAreaSmokeFib  =  FpObjectAreaSmoke::Init
void FpObjectAreaSmoke::Init(int this,undefined4 param_2,char param_3)

{
  undefined4 uVar1;
  undefined8 uVar2;
  int iVar3;
  
  this->u32_1f8 = param_2;
  this->u32_1f4 = param_2;
  iVar3 = this->i32_1f8;
  uVar2 = __nwa(iVar3 * 0xf0 + 0x10);
  uVar1 = __construct_new_array(uVar2,0x299b50,0,0xf0,iVar3);
  this->u32_1fc = uVar1;
  memset(*(void **)(this + 0x1fc),0,(long)(this->i32_1f8 * 0xf0));
  for (iVar3 = 0; iVar3 < this->i32_1f8; iVar3 = iVar3 + 1) {
    (**(code **)(this->i32_1e4 + 0x4c))(this,iVar3,1);
  }
  this->u32_1e0 = 0xffffffff;
  this->u8_14 = this->u8_14 & 0xfe | 1;
  this->u16_14 = this->u16_14 & 0xe01f;
  if (param_3 == '\0') {
    PutiObject::SetRegTest(this,0x33001);
  }
  else {
    PutiObject::SetRegTest(this,0x73001);
  }
  PutiObject::SetRegAlpha(this,0x44);
  return;
}

// JP: 0x002bc520  CalculateFunc__17FpObjectAreaSmokeFv  =  FpObjectAreaSmoke::CalculateFunc
void FpObjectAreaSmoke::CalculateFunc(undefined8 this)

{
  int iVar1;
  int iVar2;
  int iVar3;
  float *pfVar4;
  int this;
  float fVar6;
  float fVar7;
  float fVar8;
  undefined1 auVar9 [16];
  undefined1 auVar10 [16];
  undefined1 auStack_80 [16];
  undefined1 auStack_70 [16];
  undefined1 auStack_60 [8];
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined1 auStack_50 [16];
  undefined1 auStack_40 [48];
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  
  iVar1 = this->i32_8;
  fVar7 = iVar1->f32_9c;
  fVar8 = (float)iVar1->i32_c0 * 0.3;
  Matrix::Matrix(auStack_40,CApp::camera + 0x240);
  FVector::FVector(auStack_50,&uStack_10);
  if (iVar1->f32_8c == 1.0) {
    uStack_10 = 0;
    uStack_c = 0;
    uStack_8 = 0;
    uStack_4 = 0x3f800000;
    Matrix::ApplyMatrix(auStack_60,auStack_40,iVar1 + 0x80);
    iVar3 = this->i32_1fc;
    for (iVar2 = 0; iVar2 < this->i32_1f8; iVar2 = iVar2 + 1) {
      iVar3->i32_10 = auStack_60._0_4_;
      iVar3->i32_14 = auStack_60._4_4_;
      iVar3->u32_18 = uStack_58;
      iVar3->u32_1c = uStack_54;
      iVar3->f32_14 = iVar3->f32_14 + iVar1->f32_b0;
      iVar3 = iVar3 + 0xf0;
    }
  }
  pfVar4 = *(float **)(this + 0x1fc);
  for (iVar3 = 0; iVar3 < this->i32_1f8; iVar3 = iVar3 + 1) {
    pfVar4[1] = pfVar4[1] + 1.0;
    if (*pfVar4 <= pfVar4[1]) {
      (**(code **)(this->i32_1e4 + 0x4c))(this,iVar3,0);
    }
    else if (1.0 < pfVar4[1]) {
      if (pfVar4[1] < fVar8) {
        pfVar4[0x2f] = (fVar7 * pfVar4[1]) / fVar8;
      }
      else {
        pfVar4[0x2f] = (fVar7 * (*pfVar4 - pfVar4[1])) / (*pfVar4 - fVar8);
      }
      pfVar4[0xc] = pfVar4[0xc] + pfVar4[4];
      pfVar4[0xd] = pfVar4[0xd] + pfVar4[5];
      pfVar4[0xe] = pfVar4[0xe] + pfVar4[6];
    }
    auVar9 = _lqc2(*(undefined1 (*) [16])(pfVar4 + 0xc));
    auVar10 = _lqc2(auStack_50);
    auVar9 = _vsub(auVar9,auVar10);
    auStack_80 = _sqc2(auVar9);
    FVector::FVector(auStack_70,auStack_80);
    fVar6 = (float)FVector::Length(auStack_70);
    if ((fVar6 < 0.0) || (iVar1->f32_bc <= fVar6)) {
      pfVar4[0x2f] = 0.0;
    }
    else {
      pfVar4[0x2f] = pfVar4[0x2f] * ((iVar1->f32_bc - fVar6) / iVar1->f32_bc);
    }
    pfVar4 = pfVar4 + 0x3c;
  }
  (**(code **)(this->i32_1e4 + 0x44))();
  return;
}

// JP: 0x002bc830  SetPacket__17FpObjectAreaSmokeFv  =  FpObjectAreaSmoke::SetPacket
void FpObjectAreaSmoke::SetPacket(int this)

{
  float in_zero_lo;
  float in_zero_hi;
  float in_zero_udw;
  float in_register_0000000c;
  float *pfVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  float fVar5;
  uint uVar6;
  float fStack_70;
  float fStack_6c;
  float fStack_68;
  float fStack_64;
  float *pfStack_54;
  float *pfStack_50;
  float *pfStack_4c;
  float *pfStack_48;
  float *pfStack_44;
  float *pfStack_40;
  uint *puStack_3c;
  uint *puStack_38;
  float *pfStack_34;
  float *pfStack_30;
  ulong *puStack_2c;
  ulong *puStack_28;
  float *pfStack_24;
  uint uStack_20;
  float fStack_1c;
  float fStack_18;
  float fStack_14;
  int iStack_10;
  
  fStack_14 = this->f32_1f0 * *(float *)(this->i32_8 + 0x5c);
  pfStack_24 = *(float **)(this + 0x88);
  *pfStack_24 = in_zero_lo;
  pfStack_24[1] = in_zero_hi;
  pfStack_24[2] = in_zero_udw;
  pfStack_24[3] = in_register_0000000c;
  *pfStack_24 = (float)(&DAT_10000001 + this->i32_1f8 * 0xc);
  pfStack_24[3] = (float)(this->i32_1f8 * 0xc + 1U | 0x50000000);
  this->i32_88 = this->i32_88 + 0x10;
  puStack_2c = *(ulong **)(this + 0x88);
  *puStack_2c = (long)(this->i32_1f8 << 2) | 0x302a400000008000;
  puStack_2c[1] = 0x412;
  this->i32_88 = this->i32_88 + 0x10;
  pfVar1 = *(float **)(this + 0x88);
  iVar2 = this->i32_1fc;
  fStack_70 = in_zero_lo;
  fStack_6c = in_zero_hi;
  fStack_68 = in_zero_udw;
  fStack_64 = in_register_0000000c;
  pfStack_34 = pfVar1;
  pfStack_30 = pfVar1;
  puStack_28 = puStack_2c;
  iStack_10 = this;
  for (iVar4 = 0; iVar4 < iStack_10->i32_1f8; iVar4 = iVar4 + 1) {
    fStack_18 = iVar2->f32_bc * fStack_14;
    if (fStack_18 < 0.0) {
      fStack_18 = 0.0;
    }
    else if (128.0 < fStack_18) {
      fStack_18 = 128.0;
    }
    if (0.0 < fStack_18) {
      for (iVar3 = 0; iVar3 < 4; iVar3 = iVar3 + 1) {
        fStack_1c = (float)PutiObject::RotTransPer
                                     (iStack_10,iVar2 + iVar3 * 0x10 + 0x70,&fStack_70);
        uStack_20 = PutiObject::ClipFlag(iStack_10);
        *pfVar1 = *(float *)(iVar2 + iVar3 * 8 + 0xc0) * fStack_1c;
        pfVar1[1] = *(float *)(iVar2 + iVar3 * 8 + 0xc4) * fStack_1c;
        pfVar1[2] = fStack_1c;
        iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
        puStack_3c = *(uint **)(iStack_10 + 0x88);
        fVar5 = iVar2->f32_b0;
        if (fVar5 < 2.1474836e+09) {
          uVar6 = (uint)fVar5;
        }
        else {
          uVar6 = (int)(fVar5 - 2.1474836e+09) | 0x80000000;
        }
        *puStack_3c = uVar6;
        fVar5 = iVar2->f32_b4;
        if (fVar5 < 2.1474836e+09) {
          uVar6 = (uint)fVar5;
        }
        else {
          uVar6 = (int)(fVar5 - 2.1474836e+09) | 0x80000000;
        }
        puStack_3c[1] = uVar6;
        fVar5 = iVar2->f32_b8;
        if (fVar5 < 2.1474836e+09) {
          uVar6 = (uint)fVar5;
        }
        else {
          uVar6 = (int)(fVar5 - 2.1474836e+09) | 0x80000000;
        }
        puStack_3c[2] = uVar6;
        fVar5 = iVar2->f32_bc;
        if (fVar5 < 2.1474836e+09) {
          uVar6 = (uint)fVar5;
        }
        else {
          uVar6 = (int)(fVar5 - 2.1474836e+09) | 0x80000000;
        }
        puStack_3c[3] = uVar6;
        iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
        pfStack_44 = *(float **)(iStack_10 + 0x88);
        if ((iVar3 < 2) || ((uStack_20 & 0x3ffff) != 0)) {
          fStack_64 = 4.59177e-41;
        }
        *pfStack_44 = fStack_70;
        pfStack_44[1] = fStack_6c;
        pfStack_44[2] = fStack_68;
        pfStack_44[3] = fStack_64;
        iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
        pfVar1 = *(float **)(iStack_10 + 0x88);
        pfStack_4c = pfVar1;
        pfStack_48 = pfVar1;
        pfStack_40 = pfStack_44;
        puStack_38 = puStack_3c;
      }
    }
    else {
      for (iVar3 = 0; iVar3 < 4; iVar3 = iVar3 + 1) {
        *pfVar1 = in_zero_lo;
        pfVar1[1] = in_zero_hi;
        pfVar1[2] = in_zero_udw;
        pfVar1[3] = in_register_0000000c;
        iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
        pfStack_54 = *(float **)(iStack_10 + 0x88);
        *pfStack_54 = in_zero_lo;
        pfStack_54[1] = in_zero_hi;
        pfStack_54[2] = in_zero_udw;
        pfStack_54[3] = in_register_0000000c;
        iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
        pfVar1 = *(float **)(iStack_10 + 0x88);
        *pfVar1 = in_zero_lo;
        pfVar1[1] = in_zero_hi;
        pfVar1[2] = in_zero_udw;
        pfVar1[3] = in_register_0000000c;
        pfVar1[3] = 4.59177e-41;
        iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
        pfVar1 = *(float **)(iStack_10 + 0x88);
        pfStack_50 = pfStack_54;
      }
    }
    iVar2 = iVar2 + 0xf0;
  }
  return;
}

// JP: 0x002bcd60  __ct__6FpTakiFv  =  FpTaki::FpTaki
int FpTaki::FpTaki(int this)

{
  FpPrim::FpPrim(this);
  *(undefined1 **)(this + 0x10) = FpTaki::__vt;
  this->u32_1c = 0x406680;
  this->u32_70 = 0;
  return this;
}

// JP: 0x002bcdc0  __dt__6FpTakiFv  =  FpTaki::~FpTaki
int FpTaki::~FpTaki(int this,short param_2)

{
  if (this != 0) {
    *(undefined1 **)(this + 0x10) = FpTaki::__vt;
    this->u32_1c = 0x406680;
    FpPrim::~FpPrim(this,0);
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}

// JP: 0x002bce50  Create__6FpTakiFi  =  FpTaki::Create
void FpTaki::Create(int this,int param_2)

{
  long lVar1;
  undefined8 uVar2;
  int iVar3;
  
  this->i32_70 = param_2;
  iVar3 = BgEffectMan::eff->i32_1c + 0x8c;
  SetWhiteTex(iVar3);
  PutiPrim::SetTexture(this,iVar3,0);
  if (this->i8_58 == '\0') {
    this->u8_24 = this->u8_24 & 0xfe | 1;
  }
  iVar3 = 100;
  if (param_2 == 1) {
    iVar3 = 0x32;
  }
  lVar1 = __nw(0x2e0);
  uVar2 = 0;
  if (lVar1 != 0) {
    uVar2 = FpObjectTaki::FpObjectTaki(lVar1,iVar3 * 0xc + 0x14,0);
  }
  PutiPrim::AddObject(this,uVar2);
  (**(code **)(*(int *)((int)uVar2 + 0x1e4) + 0x40))(uVar2,iVar3,this->u8_58);
  iVar3 = 100;
  if (LSDPlayer::sys != 0) {
    iVar3 = 0x32;
  }
  lVar1 = __nw(0x2e0);
  uVar2 = 0;
  if (lVar1 != 0) {
    uVar2 = FpObjectTaki2::FpObjectTaki2(lVar1,iVar3 * 0xc + 0x14,0);
  }
  PutiPrim::AddObject(this,uVar2);
  (**(code **)(*(int *)((int)uVar2 + 0x1e4) + 0x40))(uVar2,iVar3,this->u8_58);
  PutiManager::AddPrim(BgEffectMan::eff,this->u32_54,this);
  return;
}

// JP: 0x002bd050  Create__6FpTakiFPv  =  FpTaki::Create
void FpTaki::Create(undefined4 this,float *param_2)

{
  FpTaki::Create(this,(int)*param_2);
  return;
}

// JP: 0x002bd0a0  __ct__12FpObjectTakiFiPv  =  FpObjectTaki::FpObjectTaki
int FpObjectTaki::FpObjectTaki(int this,undefined4 param_2,undefined4 param_3)

{
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  
  FpObject::FpObject(this,param_2,param_3);
  *(undefined1 **)(this + 0x1e4) = FpObjectTaki::__vt;
  this->u32_210 = in_zero_lo;
  this->u32_214 = in_zero_hi;
  this->u32_218 = in_zero_udw;
  this->u32_21c = in_register_0000000c;
  this->u32_220 = in_zero_lo;
  this->u32_224 = in_zero_hi;
  this->u32_228 = in_zero_udw;
  this->u32_22c = in_register_0000000c;
  this->u32_230 = in_zero_lo;
  this->u32_234 = in_zero_hi;
  this->u32_238 = in_zero_udw;
  this->u32_23c = in_register_0000000c;
  this->u32_240 = in_zero_lo;
  this->u32_244 = in_zero_hi;
  this->u32_248 = in_zero_udw;
  this->u32_24c = in_register_0000000c;
  this->u32_250 = in_zero_lo;
  this->u32_254 = in_zero_hi;
  this->u32_258 = in_zero_udw;
  this->u32_25c = in_register_0000000c;
  this->u32_260 = in_zero_lo;
  this->u32_264 = in_zero_hi;
  this->u32_268 = in_zero_udw;
  this->u32_26c = in_register_0000000c;
  this->u32_270 = in_zero_lo;
  this->u32_274 = in_zero_hi;
  this->u32_278 = in_zero_udw;
  this->u32_27c = in_register_0000000c;
  this->u32_280 = in_zero_lo;
  this->u32_284 = in_zero_hi;
  this->u32_288 = in_zero_udw;
  this->u32_28c = in_register_0000000c;
  this->u32_290 = in_zero_lo;
  this->u32_294 = in_zero_hi;
  this->u32_298 = in_zero_udw;
  this->u32_29c = in_register_0000000c;
  this->u32_2a0 = in_zero_lo;
  this->u32_2a4 = in_zero_hi;
  this->u32_2a8 = in_zero_udw;
  this->u32_2ac = in_register_0000000c;
  this->u32_2b0 = in_zero_lo;
  this->u32_2b4 = in_zero_hi;
  this->u32_2b8 = in_zero_udw;
  this->u32_2bc = in_register_0000000c;
  return this;
}

// JP: 0x002bd150  __dt__12FpObjectTakiFv  =  FpObjectTaki::~FpObjectTaki
int FpObjectTaki::~FpObjectTaki(int this,short param_2)

{
  if (this != 0) {
    *(undefined1 **)(this + 0x1e4) = FpObjectTaki::__vt;
    FpObject::~FpObject(this,0);
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}

// JP: 0x002bd1d0  InitSetData__12FpObjectTakiFv  =  FpObjectTaki::InitSetData
void FpObjectTaki::InitSetData(int this)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 auVar3 [16];
  undefined1 auVar4 [16];
  undefined1 auStack_280 [16];
  undefined1 auStack_270 [16];
  undefined1 auStack_260 [16];
  undefined1 auStack_250 [16];
  undefined1 auStack_240 [16];
  undefined1 auStack_230 [16];
  undefined1 auStack_220 [16];
  undefined1 auStack_210 [16];
  undefined1 auStack_200 [16];
  undefined1 auStack_1f0 [16];
  undefined1 auStack_1e0 [8];
  undefined4 uStack_1d8;
  undefined4 uStack_1d4;
  undefined1 auStack_1d0 [8];
  undefined4 uStack_1c8;
  undefined4 uStack_1c4;
  undefined1 auStack_1c0 [8];
  undefined4 uStack_1b8;
  undefined4 uStack_1b4;
  undefined1 auStack_1b0 [8];
  undefined4 uStack_1a8;
  undefined4 uStack_1a4;
  undefined1 auStack_1a0 [8];
  undefined4 uStack_198;
  undefined4 uStack_194;
  undefined4 uStack_190;
  undefined4 uStack_18c;
  undefined4 uStack_188;
  undefined4 uStack_184;
  undefined4 uStack_180;
  undefined4 uStack_17c;
  undefined4 uStack_178;
  undefined4 uStack_174;
  undefined4 uStack_170;
  undefined4 uStack_16c;
  undefined4 uStack_168;
  undefined4 uStack_164;
  undefined4 uStack_160;
  undefined4 uStack_15c;
  undefined4 uStack_158;
  undefined4 uStack_154;
  undefined4 uStack_150;
  undefined4 uStack_14c;
  undefined4 uStack_148;
  undefined4 uStack_144;
  undefined4 uStack_140;
  undefined4 uStack_13c;
  undefined4 uStack_138;
  undefined4 uStack_134;
  undefined4 uStack_130;
  undefined4 uStack_12c;
  undefined4 uStack_128;
  undefined4 uStack_124;
  undefined4 uStack_120;
  undefined4 uStack_11c;
  undefined4 uStack_118;
  undefined4 uStack_114;
  undefined4 uStack_110;
  undefined4 uStack_10c;
  undefined4 uStack_108;
  undefined4 uStack_104;
  undefined4 uStack_100;
  undefined4 uStack_fc;
  undefined4 uStack_f8;
  undefined4 uStack_f4;
  undefined1 auStack_f0 [8];
  undefined4 uStack_e8;
  undefined4 uStack_e4;
  undefined1 auStack_e0 [8];
  undefined4 uStack_d8;
  undefined4 uStack_d4;
  undefined1 auStack_d0 [8];
  undefined4 uStack_c8;
  undefined4 uStack_c4;
  undefined1 auStack_c0 [8];
  undefined4 uStack_b8;
  undefined4 uStack_b4;
  undefined1 auStack_b0 [8];
  undefined4 uStack_a8;
  undefined4 uStack_a4;
  undefined4 uStack_a0;
  undefined4 uStack_9c;
  undefined4 uStack_98;
  undefined4 uStack_94;
  undefined4 uStack_90;
  undefined4 uStack_8c;
  undefined4 uStack_88;
  undefined4 uStack_84;
  undefined4 uStack_80;
  undefined4 uStack_7c;
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  iVar1 = *(int *)(this->i32_8 + 0x70);
  if (iVar1 == 1) {
    this->u32_1e0 = 0x96;
    uStack_100 = 0x42c80000;
    uStack_fc = 0x42800000;
    uStack_f8 = 0x42b40000;
    uStack_f4 = 0x42800000;
    this->u32_1d0 = 0x42c80000;
    this->u32_1d4 = 0x42800000;
    this->u32_1d8 = 0x42b40000;
    this->u32_1dc = 0x42800000;
    uStack_110 = 0x433e0000;
    uStack_10c = 0x433e0000;
    uStack_108 = 0;
    uStack_104 = 0;
    this->u32_110 = 0x433e0000;
    this->u32_114 = 0x433e0000;
    this->u32_118 = 0;
    this->u32_11c = 0;
    uStack_120 = 0x40400000;
    uStack_11c = 0;
    uStack_118 = 0;
    uStack_114 = 0x3f800000;
    this->u32_a0 = 0x40400000;
    this->u32_a4 = 0;
    this->u32_a8 = 0;
    this->u32_ac = 0x3f800000;
    uStack_130 = 0x40440831;
    uStack_12c = 0x41a28106;
    uStack_128 = 0x439e0810;
    uStack_124 = 0x3f800000;
    this->u32_e0 = 0x40440831;
    this->u32_e4 = 0x41a28106;
    this->u32_e8 = 0x439e0810;
    this->u32_ec = 0x3f800000;
    uStack_140 = 0x40400000;
    uStack_13c = 0xc3b7fba6;
    uStack_138 = 0x43e8de14;
    uStack_134 = 0x3f800000;
    this->u32_210 = 0x40400000;
    this->u32_214 = 0xc3b7fba6;
    this->u32_218 = 0x43e8de14;
    this->u32_21c = 0x3f800000;
    uStack_150 = 0x40400000;
    uStack_14c = 0xc39800c5;
    uStack_148 = 0x43bbaeb8;
    uStack_144 = 0x3f800000;
    this->u32_220 = 0x40400000;
    this->u32_224 = 0xc39800c5;
    this->u32_228 = 0x43bbaeb8;
    this->u32_22c = 0x3f800000;
    uStack_160 = 0x40400000;
    uStack_15c = 0xc31ae51f;
    uStack_158 = 0x43a11e35;
    uStack_154 = 0x3f800000;
    this->u32_230 = 0x40400000;
    this->u32_234 = 0xc31ae51f;
    this->u32_238 = 0x43a11e35;
    this->u32_23c = 0x3f800000;
    uStack_170 = 0x40400000;
    uStack_16c = 0x41a8ef9e;
    uStack_168 = 0x43977a7f;
    uStack_164 = 0x3f800000;
    this->u32_240 = 0x40400000;
    this->u32_244 = 0x41a8ef9e;
    this->u32_248 = 0x43977a7f;
    this->u32_24c = 0x3f800000;
    uStack_180 = 0x40400000;
    uStack_17c = 0x42f23be7;
    uStack_178 = 0x43977a7f;
    uStack_174 = 0x3f800000;
    this->u32_250 = 0x40400000;
    this->u32_254 = 0x42f23be7;
    this->u32_258 = 0x43977a7f;
    this->u32_25c = 0x3f800000;
    uStack_190 = 0x40400000;
    uStack_18c = 0x435d1df4;
    uStack_188 = 0x43977a7f;
    uStack_184 = 0x3f800000;
    this->u32_260 = 0x40400000;
    this->u32_264 = 0x435d1df4;
    this->u32_268 = 0x43977a7f;
    this->u32_26c = 0x3f800000;
    auVar3 = _lqc2(*(undefined1 (*) [16])(this + 0x220));
    auVar4 = _lqc2(*(undefined1 (*) [16])(this + 0x210));
    auVar3 = _vsub(auVar3,auVar4);
    auStack_240 = _sqc2(auVar3);
    FVector::FVector(auStack_1a0,auStack_240);
    this->i32_270 = auStack_1a0._0_4_;
    this->i32_274 = auStack_1a0._4_4_;
    this->u32_278 = uStack_198;
    this->u32_27c = uStack_194;
    auVar3 = _lqc2(*(undefined1 (*) [16])(this + 0x230));
    auVar4 = _lqc2(*(undefined1 (*) [16])(this + 0x220));
    auVar3 = _vsub(auVar3,auVar4);
    auStack_250 = _sqc2(auVar3);
    FVector::FVector(auStack_1b0,auStack_250);
    this->i32_280 = auStack_1b0._0_4_;
    this->i32_284 = auStack_1b0._4_4_;
    this->u32_288 = uStack_1a8;
    this->u32_28c = uStack_1a4;
    auVar3 = _lqc2(*(undefined1 (*) [16])(this + 0x240));
    auVar4 = _lqc2(*(undefined1 (*) [16])(this + 0x230));
    auVar3 = _vsub(auVar3,auVar4);
    auStack_260 = _sqc2(auVar3);
    FVector::FVector(auStack_1c0,auStack_260);
    this->i32_290 = auStack_1c0._0_4_;
    this->i32_294 = auStack_1c0._4_4_;
    this->u32_298 = uStack_1b8;
    this->u32_29c = uStack_1b4;
    auVar3 = _lqc2(*(undefined1 (*) [16])(this + 0x250));
    auVar4 = _lqc2(*(undefined1 (*) [16])(this + 0x240));
    auVar3 = _vsub(auVar3,auVar4);
    auStack_270 = _sqc2(auVar3);
    FVector::FVector(auStack_1d0,auStack_270);
    this->i32_2a0 = auStack_1d0._0_4_;
    this->i32_2a4 = auStack_1d0._4_4_;
    this->u32_2a8 = uStack_1c8;
    this->u32_2ac = uStack_1c4;
    auVar3 = _lqc2(*(undefined1 (*) [16])(this + 0x260));
    auVar4 = _lqc2(*(undefined1 (*) [16])(this + 0x250));
    auVar3 = _vsub(auVar3,auVar4);
    auStack_280 = _sqc2(auVar3);
    FVector::FVector(auStack_1e0,auStack_280);
    this->i32_2b0 = auStack_1e0._0_4_;
    this->i32_2b4 = auStack_1e0._4_4_;
    this->u32_2b8 = uStack_1d8;
    this->u32_2bc = uStack_1d4;
    uVar2 = FVector::Length(this + 0x270);
    this->u32_2c0 = uVar2;
    uVar2 = FVector::Length(this + 0x280);
    this->u32_2c4 = uVar2;
    uVar2 = FVector::Length(this + 0x290);
    this->u32_2c8 = uVar2;
    uVar2 = FVector::Length(this + 0x2a0);
    this->u32_2cc = uVar2;
    uVar2 = FVector::Length(this + 0x2b0);
    this->u32_2d0 = uVar2;
  }
  else if (iVar1 == 0) {
    this->u32_1e0 = 300;
    uStack_10 = 0x43000000;
    uStack_c = 0x43000000;
    uStack_8 = 0x43000000;
    uStack_4 = 0x42800000;
    this->u32_1d0 = 0x43000000;
    this->u32_1d4 = 0x43000000;
    this->u32_1d8 = 0x43000000;
    this->u32_1dc = 0x42800000;
    uStack_20 = 0x425c0000;
    uStack_1c = 0x425c0000;
    uStack_18 = 0;
    uStack_14 = 0;
    this->u32_110 = 0x425c0000;
    this->u32_114 = 0x425c0000;
    this->u32_118 = 0;
    this->u32_11c = 0;
    uStack_30 = 0x3f800000;
    uStack_2c = 0;
    uStack_28 = 0;
    uStack_24 = 0x3f800000;
    this->u32_a0 = 0x3f800000;
    this->u32_a4 = 0;
    this->u32_a8 = 0;
    this->u32_ac = 0x3f800000;
    uStack_40 = 0x3f7020c5;
    uStack_3c = 0xbf400000;
    uStack_38 = 0x42a12042;
    uStack_34 = 0x3f800000;
    this->u32_e0 = 0x3f7020c5;
    this->u32_e4 = 0xbf400000;
    this->u32_e8 = 0x42a12042;
    this->u32_ec = 0x3f800000;
    uStack_50 = 0x3f800000;
    uStack_4c = 0xc365be35;
    uStack_48 = 0x433e2354;
    uStack_44 = 0x3f800000;
    this->u32_210 = 0x3f800000;
    this->u32_214 = 0xc365be35;
    this->u32_218 = 0x433e2354;
    this->u32_21c = 0x3f800000;
    uStack_60 = 0x3f800000;
    uStack_5c = 0xc35cd0e5;
    uStack_58 = 0x43108bc7;
    uStack_54 = 0x3f800000;
    this->u32_220 = 0x3f800000;
    this->u32_224 = 0xc35cd0e5;
    this->u32_228 = 0x43108bc7;
    this->u32_22c = 0x3f800000;
    uStack_70 = 0x3f800000;
    uStack_6c = 0xc3324312;
    uStack_68 = 0x42c6b0a4;
    uStack_64 = 0x3f800000;
    this->u32_230 = 0x3f800000;
    this->u32_234 = 0xc3324312;
    this->u32_238 = 0x42c6b0a4;
    this->u32_23c = 0x3f800000;
    uStack_80 = 0x3f800000;
    uStack_7c = 0xc2e82d0e;
    uStack_78 = 0x42ac1f3b;
    uStack_74 = 0x3f800000;
    this->u32_240 = 0x3f800000;
    this->u32_244 = 0xc2e82d0e;
    this->u32_248 = 0x42ac1f3b;
    this->u32_24c = 0x3f800000;
    uStack_90 = 0x3f800000;
    uStack_8c = 0xc2728312;
    uStack_88 = 0x42a4849c;
    uStack_84 = 0x3f800000;
    this->u32_250 = 0x3f800000;
    this->u32_254 = 0xc2728312;
    this->u32_258 = 0x42a4849c;
    this->u32_25c = 0x3f800000;
    uStack_a0 = 0x3f800000;
    uStack_9c = 0x40ee8f5c;
    uStack_98 = 0x42a0b5c3;
    uStack_94 = 0x3f800000;
    this->u32_260 = 0x3f800000;
    this->u32_264 = 0x40ee8f5c;
    this->u32_268 = 0x42a0b5c3;
    this->u32_26c = 0x3f800000;
    auVar3 = _lqc2(*(undefined1 (*) [16])(this + 0x220));
    auVar4 = _lqc2(*(undefined1 (*) [16])(this + 0x210));
    auVar3 = _vsub(auVar3,auVar4);
    auStack_1f0 = _sqc2(auVar3);
    FVector::FVector(auStack_b0,auStack_1f0);
    this->i32_270 = auStack_b0._0_4_;
    this->i32_274 = auStack_b0._4_4_;
    this->u32_278 = uStack_a8;
    this->u32_27c = uStack_a4;
    auVar3 = _lqc2(*(undefined1 (*) [16])(this + 0x230));
    auVar4 = _lqc2(*(undefined1 (*) [16])(this + 0x220));
    auVar3 = _vsub(auVar3,auVar4);
    auStack_200 = _sqc2(auVar3);
    FVector::FVector(auStack_c0,auStack_200);
    this->i32_280 = auStack_c0._0_4_;
    this->i32_284 = auStack_c0._4_4_;
    this->u32_288 = uStack_b8;
    this->u32_28c = uStack_b4;
    auVar3 = _lqc2(*(undefined1 (*) [16])(this + 0x240));
    auVar4 = _lqc2(*(undefined1 (*) [16])(this + 0x230));
    auVar3 = _vsub(auVar3,auVar4);
    auStack_210 = _sqc2(auVar3);
    FVector::FVector(auStack_d0,auStack_210);
    this->i32_290 = auStack_d0._0_4_;
    this->i32_294 = auStack_d0._4_4_;
    this->u32_298 = uStack_c8;
    this->u32_29c = uStack_c4;
    auVar3 = _lqc2(*(undefined1 (*) [16])(this + 0x250));
    auVar4 = _lqc2(*(undefined1 (*) [16])(this + 0x240));
    auVar3 = _vsub(auVar3,auVar4);
    auStack_220 = _sqc2(auVar3);
    FVector::FVector(auStack_e0,auStack_220);
    this->i32_2a0 = auStack_e0._0_4_;
    this->i32_2a4 = auStack_e0._4_4_;
    this->u32_2a8 = uStack_d8;
    this->u32_2ac = uStack_d4;
    auVar3 = _lqc2(*(undefined1 (*) [16])(this + 0x260));
    auVar4 = _lqc2(*(undefined1 (*) [16])(this + 0x250));
    auVar3 = _vsub(auVar3,auVar4);
    auStack_230 = _sqc2(auVar3);
    FVector::FVector(auStack_f0,auStack_230);
    this->i32_2b0 = auStack_f0._0_4_;
    this->i32_2b4 = auStack_f0._4_4_;
    this->u32_2b8 = uStack_e8;
    this->u32_2bc = uStack_e4;
    uVar2 = FVector::Length(this + 0x270);
    this->u32_2c0 = uVar2;
    uVar2 = FVector::Length(this + 0x280);
    this->u32_2c4 = uVar2;
    uVar2 = FVector::Length(this + 0x290);
    this->u32_2c8 = uVar2;
    uVar2 = FVector::Length(this + 0x2a0);
    this->u32_2cc = uVar2;
    uVar2 = FVector::Length(this + 0x2b0);
    this->u32_2d0 = uVar2;
  }
  return;
}

// JP: 0x002bdbf0  CreateFpDataInit__12FpObjectTakiFP7_FpDatai  =  FpObjectTaki::CreateFpDataInit
void FpObjectTaki::CreateFpDataInit(int this,float *param_2,int param_3)

{
  undefined8 uVar1;
  int iVar2;
  float fVar3;
  float fVar4;
  undefined1 auVar5 [16];
  undefined1 auVar6 [16];
  undefined1 auStack_80 [16];
  undefined1 auStack_70 [8];
  float fStack_68;
  float fStack_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  *param_2 = (float)this->i32_1e0;
  param_2[2] = 0.0;
  uVar1 = this->u64_110;
  fVar3 = this->f32_118;
  fVar4 = this->f32_11c;
  param_2[0x10] = (float)uVar1;
  param_2[0x11] = (float)((ulong)uVar1 >> 0x20);
  param_2[0x12] = fVar3;
  param_2[0x13] = fVar4;
  uStack_10 = 0x3f800000;
  uStack_c = 0x3f800000;
  uStack_8 = 0;
  uStack_4 = 0x3f800000;
  param_2[0x14] = 1.0;
  param_2[0x15] = 1.0;
  param_2[0x16] = 0.0;
  param_2[0x17] = 1.0;
  uStack_20 = 0;
  uStack_1c = 0;
  uStack_18 = 0;
  uStack_14 = 0x3f800000;
  param_2[0x1c] = 0.0;
  param_2[0x1d] = 0.0;
  param_2[0x1e] = 0.0;
  param_2[0x1f] = 1.0;
  uStack_30 = 0;
  uStack_2c = 0;
  uStack_28 = 0;
  uStack_24 = 0x3f800000;
  param_2[0x20] = 0.0;
  param_2[0x21] = 0.0;
  param_2[0x22] = 0.0;
  param_2[0x23] = 1.0;
  uStack_40 = 0;
  uStack_3c = 0;
  uStack_38 = 0;
  uStack_34 = 0x3f800000;
  param_2[0x24] = 0.0;
  param_2[0x25] = 0.0;
  param_2[0x26] = 0.0;
  param_2[0x27] = 1.0;
  uStack_50 = 0;
  uStack_4c = 0;
  uStack_48 = 0;
  uStack_44 = 0x3f800000;
  param_2[0x28] = 0.0;
  param_2[0x29] = 0.0;
  param_2[0x2a] = 0.0;
  param_2[0x2b] = 1.0;
  uStack_60 = 0;
  uStack_5c = 0;
  uStack_58 = 0;
  uStack_54 = 0x3f800000;
  param_2[0x18] = 0.0;
  param_2[0x19] = 0.0;
  param_2[0x1a] = 0.0;
  param_2[0x1b] = 1.0;
  iVar2 = rand();
  param_2[0x1a] = ((float)iVar2 * 6.2831855) / 2.1474836e+09;
  uVar1 = this->u64_1d0;
  fVar3 = this->f32_1d8;
  fVar4 = this->f32_1dc;
  param_2[0x2c] = (float)uVar1;
  param_2[0x2d] = (float)((ulong)uVar1 >> 0x20);
  param_2[0x2e] = fVar3;
  param_2[0x2f] = fVar4;
  param_2[0x30] = 0.0;
  param_2[0x31] = 0.0;
  param_2[0x32] = 0.0;
  param_2[0x33] = 1.0;
  param_2[0x34] = 1.0;
  param_2[0x35] = 0.0;
  param_2[0x36] = 1.0;
  param_2[0x37] = 1.0;
  param_2[1] = (*param_2 * (float)(this->i32_1f8 - param_3)) /
               (float)this->i32_1f8;
  iVar2 = rand();
  auVar5 = _lqc2(*(undefined1 (*) [16])(this + 0xa0));
  auVar6 = _qmtc2(((float)iVar2 * 0.5) / 2.1474836e+09 + 1.0);
  auVar5 = _vmulbc(auVar5,auVar6);
  auStack_80 = _sqc2(auVar5);
  FVector::FVector(auStack_70,auStack_80);
  param_2[4] = auStack_70._0_4_;
  param_2[5] = auStack_70._4_4_;
  param_2[6] = fStack_68;
  param_2[7] = fStack_64;
  uVar1 = this->u64_100;
  fVar3 = this->f32_108;
  fVar4 = this->f32_10c;
  param_2[0xc] = (float)uVar1;
  param_2[0xd] = (float)((ulong)uVar1 >> 0x20);
  param_2[0xe] = fVar3;
  param_2[0xf] = fVar4;
  return;
}

// JP: 0x002bdf80  CreateFpData__12FpObjectTakiFP7_FpDatai  =  FpObjectTaki::CreateFpData
void FpObjectTaki::CreateFpData(int this,int param_2)

{
  undefined8 uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined1 auVar5 [16];
  undefined1 auVar6 [16];
  undefined1 auStack_20 [16];
  undefined1 auStack_10 [8];
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  param_2->u32_4 = 0;
  uVar1 = this->u64_100;
  uVar3 = this->u32_108;
  uVar4 = this->u32_10c;
  param_2->i32_30 = (int)uVar1;
  param_2->i32_34 = (int)((ulong)uVar1 >> 0x20);
  param_2->u32_38 = uVar3;
  param_2->u32_3c = uVar4;
  iVar2 = rand();
  auVar5 = _lqc2(*(undefined1 (*) [16])(this + 0xa0));
  auVar6 = _qmtc2(((float)iVar2 * 0.5) / 2.1474836e+09 + 1.0);
  auVar5 = _vmulbc(auVar5,auVar6);
  auStack_20 = _sqc2(auVar5);
  FVector::FVector(auStack_10,auStack_20);
  param_2->i32_10 = auStack_10._0_4_;
  param_2->i32_14 = auStack_10._4_4_;
  param_2->u32_18 = uStack_8;
  param_2->u32_1c = uStack_4;
  iVar2 = rand();
  param_2->f32_68 = ((float)iVar2 * 6.2831855) / 2.1474836e+09;
  return;
}

// JP: 0x002be090  Init__12FpObjectTakiFib  =  FpObjectTaki::Init
void FpObjectTaki::Init(int this,undefined4 param_2,char param_3)

{
  undefined4 uVar1;
  undefined8 uVar2;
  int iVar3;
  int iVar4;
  
  (**(code **)(this->i32_1e4 + 0x54))();
  this->u32_1f8 = param_2;
  this->u32_1f4 = param_2;
  iVar4 = this->i32_1f8;
  uVar2 = __nwa(iVar4 * 0xf0 + 0x10);
  uVar1 = __construct_new_array(uVar2,0x299b50,0,0xf0,iVar4);
  this->u32_1fc = uVar1;
  memset(*(void **)(this + 0x1fc),0,(long)(this->i32_1f8 * 0xf0));
  iVar4 = this->i32_1fc;
  for (iVar3 = 0; iVar3 < this->i32_1f8; iVar3 = iVar3 + 1) {
    (**(code **)(this->i32_1e4 + 0x50))(this,iVar4,iVar3);
    iVar4 = iVar4 + 0xf0;
  }
  this->u32_1e0 = 0xffffffff;
  this->u8_14 = this->u8_14 & 0xfe | 1;
  this->u16_14 = this->u16_14 & 0xe01f;
  if (param_3 == '\0') {
    PutiObject::SetRegTest(this,0x33001);
  }
  else {
    PutiObject::SetRegTest(this,0x73001);
  }
  PutiObject::SetRegAlpha(this,0x44);
  return;
}

// JP: 0x002be260  CalculateFunc__12FpObjectTakiFv  =  FpObjectTaki::CalculateFunc
void FpObjectTaki::CalculateFunc(undefined8 this)

{
  int iVar1;
  float *pfVar2;
  int this;
  float fVar4;
  float fVar5;
  float fVar6;
  undefined1 auVar7 [16];
  undefined1 auVar8 [16];
  undefined1 auStack_140 [16];
  undefined1 auStack_130 [16];
  undefined1 auStack_120 [16];
  undefined1 auStack_110 [16];
  undefined1 auStack_100 [16];
  undefined1 auStack_f0 [16];
  undefined1 auStack_e0 [16];
  undefined1 auStack_d0 [16];
  undefined1 auStack_c0 [16];
  undefined1 auStack_b0 [16];
  undefined1 auStack_a0 [16];
  undefined1 auStack_90 [8];
  float fStack_88;
  float fStack_84;
  undefined1 auStack_80 [16];
  undefined1 auStack_70 [8];
  float fStack_68;
  float fStack_64;
  undefined1 auStack_60 [16];
  undefined1 auStack_50 [8];
  float fStack_48;
  float fStack_44;
  undefined1 auStack_40 [16];
  undefined1 auStack_30 [8];
  float fStack_28;
  float fStack_24;
  undefined1 auStack_20 [16];
  undefined1 auStack_10 [8];
  float fStack_8;
  float fStack_4;
  
  
  fVar4 = (float)FpPrim::GetFrameSpeed(this->u32_8);
  pfVar2 = *(float **)(this + 0x1fc);
  fVar5 = this->f32_e4;
  for (iVar1 = 0; iVar1 < this->i32_1f8; iVar1 = iVar1 + 1) {
    pfVar2[1] = pfVar2[1] + fVar4;
    if (*pfVar2 <= *(float *)(this->i32_1fc + iVar1 * 0xf0 + 4)) {
      (**(code **)(this->i32_1e4 + 0x4c))(this,pfVar2,iVar1);
    }
    fVar6 = pfVar2[4] * pfVar2[1];
    if (fVar6 < this->f32_2c0) {
      auVar7 = _lqc2(*(undefined1 (*) [16])(this + 0x270));
      auVar8 = _qmtc2(fVar6 / this->f32_2c0);
      auVar7 = _vmulbc(auVar7,auVar8);
      auStack_100 = _sqc2(auVar7);
      FVector::FVector(auStack_20,auStack_100);
      auVar7 = _lqc2(*(undefined1 (*) [16])(this + 0x210));
      auVar8 = _lqc2(auStack_20);
      auVar7 = _vadd(auVar7,auVar8);
      auStack_b0 = _sqc2(auVar7);
      FVector::FVector(auStack_10,auStack_b0);
      pfVar2[0xc] = auStack_10._0_4_;
      pfVar2[0xd] = auStack_10._4_4_;
      pfVar2[0xe] = fStack_8;
      pfVar2[0xf] = fStack_4;
      pfVar2[0x2f] = 0.0;
    }
    else {
      fVar6 = fVar6 - this->f32_2c0;
      if (fVar6 < this->f32_2c4) {
        auVar7 = _lqc2(*(undefined1 (*) [16])(this + 0x280));
        auVar8 = _qmtc2(fVar6 / this->f32_2c4);
        auVar7 = _vmulbc(auVar7,auVar8);
        auStack_110 = _sqc2(auVar7);
        FVector::FVector(auStack_40,auStack_110);
        auVar7 = _lqc2(*(undefined1 (*) [16])(this + 0x220));
        auVar8 = _lqc2(auStack_40);
        auVar7 = _vadd(auVar7,auVar8);
        auStack_c0 = _sqc2(auVar7);
        FVector::FVector(auStack_30,auStack_c0);
        pfVar2[0xc] = auStack_30._0_4_;
        pfVar2[0xd] = auStack_30._4_4_;
        pfVar2[0xe] = fStack_28;
        pfVar2[0xf] = fStack_24;
        pfVar2[0x2f] = this->f32_1dc * (fVar6 / this->f32_2c4);
      }
      else {
        fVar6 = fVar6 - this->f32_2c4;
        if (fVar6 < this->f32_2c8) {
          auVar7 = _lqc2(*(undefined1 (*) [16])(this + 0x290));
          auVar8 = _qmtc2(fVar6 / this->f32_2c8);
          auVar7 = _vmulbc(auVar7,auVar8);
          auStack_120 = _sqc2(auVar7);
          FVector::FVector(auStack_60,auStack_120);
          auVar7 = _lqc2(*(undefined1 (*) [16])(this + 0x230));
          auVar8 = _lqc2(auStack_60);
          auVar7 = _vadd(auVar7,auVar8);
          auStack_d0 = _sqc2(auVar7);
          FVector::FVector(auStack_50,auStack_d0);
          pfVar2[0xc] = auStack_50._0_4_;
          pfVar2[0xd] = auStack_50._4_4_;
          pfVar2[0xe] = fStack_48;
          pfVar2[0xf] = fStack_44;
        }
        else {
          fVar6 = fVar6 - this->f32_2c8;
          if (fVar6 < this->f32_2cc) {
            auVar7 = _lqc2(*(undefined1 (*) [16])(this + 0x2a0));
            auVar8 = _qmtc2(fVar6 / this->f32_2cc);
            auVar7 = _vmulbc(auVar7,auVar8);
            auStack_130 = _sqc2(auVar7);
            FVector::FVector(auStack_80,auStack_130);
            auVar7 = _lqc2(*(undefined1 (*) [16])(this + 0x240));
            auVar8 = _lqc2(auStack_80);
            auVar7 = _vadd(auVar7,auVar8);
            auStack_e0 = _sqc2(auVar7);
            FVector::FVector(auStack_70,auStack_e0);
            pfVar2[0xc] = auStack_70._0_4_;
            pfVar2[0xd] = auStack_70._4_4_;
            pfVar2[0xe] = fStack_68;
            pfVar2[0xf] = fStack_64;
          }
          else {
            auVar7 = _lqc2(*(undefined1 (*) [16])(this + 0x2b0));
            auVar8 = _qmtc2((fVar6 - this->f32_2cc) / this->f32_2d0);
            auVar7 = _vmulbc(auVar7,auVar8);
            auStack_140 = _sqc2(auVar7);
            FVector::FVector(auStack_a0,auStack_140);
            auVar7 = _lqc2(*(undefined1 (*) [16])(this + 0x250));
            auVar8 = _lqc2(auStack_a0);
            auVar7 = _vadd(auVar7,auVar8);
            auStack_f0 = _sqc2(auVar7);
            FVector::FVector(auStack_90,auStack_f0);
            pfVar2[0xc] = auStack_90._0_4_;
            pfVar2[0xd] = auStack_90._4_4_;
            pfVar2[0xe] = fStack_88;
            pfVar2[0xf] = fStack_84;
          }
        }
      }
    }
    if (fVar5 < pfVar2[0xd]) {
      pfVar2[0x2f] = 0.0;
    }
    else {
      fVar6 = pfVar2[0xd] + this->f32_114 / 4.0;
      if (fVar5 < fVar6) {
        pfVar2[0x2f] = this->f32_1dc * (1.0 - (fVar6 - fVar5) / (fVar6 - pfVar2[0xd]));
      }
    }
    pfVar2 = pfVar2 + 0x3c;
  }
  (**(code **)(this->i32_1e4 + 0x44))();
  return;
}

// JP: 0x002be6f0  SetPacket__12FpObjectTakiFv  =  FpObjectTaki::SetPacket
void FpObjectTaki::SetPacket(int this)

{
  float in_zero_lo;
  float in_zero_hi;
  float in_zero_udw;
  float in_register_0000000c;
  float *pfVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  float fVar5;
  uint uVar6;
  float fStack_70;
  float fStack_6c;
  float fStack_68;
  float fStack_64;
  float *pfStack_54;
  float *pfStack_50;
  float *pfStack_4c;
  float *pfStack_48;
  float *pfStack_44;
  float *pfStack_40;
  uint *puStack_3c;
  uint *puStack_38;
  float *pfStack_34;
  float *pfStack_30;
  ulong *puStack_2c;
  ulong *puStack_28;
  float *pfStack_24;
  uint uStack_20;
  float fStack_1c;
  float fStack_18;
  float fStack_14;
  int iStack_10;
  
  fStack_14 = this->f32_1f0 * *(float *)(this->i32_8 + 0x5c);
  pfStack_24 = *(float **)(this + 0x88);
  *pfStack_24 = in_zero_lo;
  pfStack_24[1] = in_zero_hi;
  pfStack_24[2] = in_zero_udw;
  pfStack_24[3] = in_register_0000000c;
  *pfStack_24 = (float)(&DAT_10000001 + this->i32_1f8 * 0xc);
  pfStack_24[3] = (float)(this->i32_1f8 * 0xc + 1U | 0x50000000);
  this->i32_88 = this->i32_88 + 0x10;
  puStack_2c = *(ulong **)(this + 0x88);
  *puStack_2c = (long)(this->i32_1f8 << 2) | 0x302a400000008000;
  puStack_2c[1] = 0x412;
  this->i32_88 = this->i32_88 + 0x10;
  pfVar1 = *(float **)(this + 0x88);
  iVar2 = this->i32_1fc;
  fStack_70 = in_zero_lo;
  fStack_6c = in_zero_hi;
  fStack_68 = in_zero_udw;
  fStack_64 = in_register_0000000c;
  pfStack_34 = pfVar1;
  pfStack_30 = pfVar1;
  puStack_28 = puStack_2c;
  iStack_10 = this;
  for (iVar4 = 0; iVar4 < iStack_10->i32_1f8; iVar4 = iVar4 + 1) {
    fStack_18 = iVar2->f32_bc * fStack_14;
    if (fStack_18 < 0.0) {
      fStack_18 = 0.0;
    }
    else if (128.0 < fStack_18) {
      fStack_18 = 128.0;
    }
    if (0.0 < fStack_18) {
      for (iVar3 = 0; iVar3 < 4; iVar3 = iVar3 + 1) {
        fStack_1c = (float)PutiObject::RotTransPer
                                     (iStack_10,iVar2 + iVar3 * 0x10 + 0x70,&fStack_70);
        uStack_20 = PutiObject::ClipFlag(iStack_10);
        *pfVar1 = *(float *)(iVar2 + iVar3 * 8 + 0xc0) * fStack_1c;
        pfVar1[1] = *(float *)(iVar2 + iVar3 * 8 + 0xc4) * fStack_1c;
        pfVar1[2] = fStack_1c;
        iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
        puStack_3c = *(uint **)(iStack_10 + 0x88);
        fVar5 = iVar2->f32_b0;
        if (fVar5 < 2.1474836e+09) {
          uVar6 = (uint)fVar5;
        }
        else {
          uVar6 = (int)(fVar5 - 2.1474836e+09) | 0x80000000;
        }
        *puStack_3c = uVar6;
        fVar5 = iVar2->f32_b4;
        if (fVar5 < 2.1474836e+09) {
          uVar6 = (uint)fVar5;
        }
        else {
          uVar6 = (int)(fVar5 - 2.1474836e+09) | 0x80000000;
        }
        puStack_3c[1] = uVar6;
        fVar5 = iVar2->f32_b8;
        if (fVar5 < 2.1474836e+09) {
          uVar6 = (uint)fVar5;
        }
        else {
          uVar6 = (int)(fVar5 - 2.1474836e+09) | 0x80000000;
        }
        puStack_3c[2] = uVar6;
        if (fStack_18 < 2.1474836e+09) {
          uVar6 = (uint)fStack_18;
        }
        else {
          uVar6 = (int)(fStack_18 - 2.1474836e+09) | 0x80000000;
        }
        puStack_3c[3] = uVar6;
        iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
        pfStack_44 = *(float **)(iStack_10 + 0x88);
        if ((iVar3 < 2) || ((uStack_20 & 0x3ffff) != 0)) {
          fStack_64 = 4.59177e-41;
        }
        *pfStack_44 = fStack_70;
        pfStack_44[1] = fStack_6c;
        pfStack_44[2] = fStack_68;
        pfStack_44[3] = fStack_64;
        iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
        pfVar1 = *(float **)(iStack_10 + 0x88);
        pfStack_4c = pfVar1;
        pfStack_48 = pfVar1;
        pfStack_40 = pfStack_44;
        puStack_38 = puStack_3c;
      }
    }
    else {
      for (iVar3 = 0; iVar3 < 4; iVar3 = iVar3 + 1) {
        *pfVar1 = in_zero_lo;
        pfVar1[1] = in_zero_hi;
        pfVar1[2] = in_zero_udw;
        pfVar1[3] = in_register_0000000c;
        iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
        pfStack_54 = *(float **)(iStack_10 + 0x88);
        *pfStack_54 = in_zero_lo;
        pfStack_54[1] = in_zero_hi;
        pfStack_54[2] = in_zero_udw;
        pfStack_54[3] = in_register_0000000c;
        iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
        pfVar1 = *(float **)(iStack_10 + 0x88);
        *pfVar1 = in_zero_lo;
        pfVar1[1] = in_zero_hi;
        pfVar1[2] = in_zero_udw;
        pfVar1[3] = in_register_0000000c;
        pfVar1[3] = 4.59177e-41;
        iStack_10->i32_88 = iStack_10->i32_88 + 0x10;
        pfVar1 = *(float **)(iStack_10 + 0x88);
        pfStack_50 = pfStack_54;
      }
    }
    iVar2 = iVar2 + 0xf0;
  }
  return;
}

// JP: 0x002bec10  __ct__13FpObjectTaki2FiPv  =  FpObjectTaki2::FpObjectTaki2
int FpObjectTaki2::FpObjectTaki2(int this,undefined4 param_2,undefined4 param_3)

{
  FpObjectTaki::FpObjectTaki(this,param_2,param_3);
  *(undefined1 **)(this + 0x1e4) = FpObjectTaki2::__vt;
  return this;
}

// JP: 0x002bec60  __dt__13FpObjectTaki2Fv  =  FpObjectTaki2::~FpObjectTaki2
int FpObjectTaki2::~FpObjectTaki2(int this,short param_2)

{
  if (this != 0) {
    *(undefined1 **)(this + 0x1e4) = FpObjectTaki2::__vt;
    FpObjectTaki::~FpObjectTaki(this,0);
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}

// JP: 0x002bece0  InitSetData__13FpObjectTaki2Fv  =  FpObjectTaki2::InitSetData
void FpObjectTaki2::InitSetData(int this)

{
  int iVar1;
  
  iVar1 = *(int *)(this->i32_8 + 0x70);
  if (iVar1 == 1) {
    this->u32_1e0 = 300;
    this->u32_1d0 = 0x42c80000;
    this->u32_1d4 = 0x42800000;
    this->u32_1d8 = 0x42b40000;
    this->u32_1dc = 0x42000000;
    this->u32_110 = 0x42f00000;
    this->u32_114 = 0x42f00000;
    this->u32_118 = 0;
    this->u32_11c = 0;
    this->u32_100 = 0x40440831;
    this->u32_104 = 0x41a28106;
    this->u32_108 = 0x439e0810;
    this->u32_10c = 0x3f800000;
    this->f32_108 = this->f32_108 - 10.0;
    this->u32_a0 = 0x3f19999a;
    this->u32_a4 = 0xbf19999a;
    this->u32_a8 = 0;
    this->u32_ac = 0x3f800000;
  }
  else if (iVar1 == 0) {
    this->u32_1e0 = 300;
    this->u32_1d0 = 0x43000000;
    this->u32_1d4 = 0x43000000;
    this->u32_1d8 = 0x43000000;
    this->u32_1dc = 0x42000000;
    this->u32_110 = 0x42200000;
    this->u32_114 = 0x42200000;
    this->u32_118 = 0;
    this->u32_11c = 0;
    this->u32_100 = 0x3f7020c5;
    this->u32_104 = 0xbf400000;
    this->u32_108 = 0x42a12042;
    this->u32_10c = 0x3f800000;
    this->f32_108 = this->f32_108 - 10.0;
    this->u32_a0 = 0x3e4ccccd;
    this->u32_a4 = 0xbe4ccccd;
    this->u32_a8 = 0;
    this->u32_ac = 0x3f800000;
  }
  return;
}

// JP: 0x002beff0  CreateFpDataInit__13FpObjectTaki2FP7_FpDatai  =  FpObjectTaki2::CreateFpDataInit
void FpObjectTaki2::CreateFpDataInit
               (undefined8 this,undefined8 param_2,undefined8 param_3)

{
  undefined8 uVar1;
  float fVar2;
  float fVar3;
  float *pfVar4;
  int this;
  
  
  pfVar4 = (float *)param_2;
  *pfVar4 = (float)this->i32_1e0;
  pfVar4[2] = 0.0;
  uVar1 = this->u64_110;
  fVar2 = this->f32_118;
  fVar3 = this->f32_11c;
  pfVar4[0x10] = (float)uVar1;
  pfVar4[0x11] = (float)((ulong)uVar1 >> 0x20);
  pfVar4[0x12] = fVar2;
  pfVar4[0x13] = fVar3;
  pfVar4[0x14] = 1.0;
  pfVar4[0x15] = 1.0;
  pfVar4[0x16] = 0.0;
  pfVar4[0x17] = 1.0;
  pfVar4[0x1c] = 0.0;
  pfVar4[0x1d] = 0.0;
  pfVar4[0x1e] = 0.0;
  pfVar4[0x1f] = 1.0;
  pfVar4[0x20] = 0.0;
  pfVar4[0x21] = 0.0;
  pfVar4[0x22] = 0.0;
  pfVar4[0x23] = 1.0;
  pfVar4[0x24] = 0.0;
  pfVar4[0x25] = 0.0;
  pfVar4[0x26] = 0.0;
  pfVar4[0x27] = 1.0;
  pfVar4[0x28] = 0.0;
  pfVar4[0x29] = 0.0;
  pfVar4[0x2a] = 0.0;
  pfVar4[0x2b] = 1.0;
  pfVar4[0x18] = 0.0;
  pfVar4[0x19] = 0.0;
  pfVar4[0x1a] = 0.0;
  pfVar4[0x1b] = 1.0;
  uVar1 = this->u64_1d0;
  fVar2 = this->f32_1d8;
  fVar3 = this->f32_1dc;
  pfVar4[0x2c] = (float)uVar1;
  pfVar4[0x2d] = (float)((ulong)uVar1 >> 0x20);
  pfVar4[0x2e] = fVar2;
  pfVar4[0x2f] = fVar3;
  pfVar4[0x30] = 0.0;
  pfVar4[0x31] = 0.0;
  pfVar4[0x32] = 0.0;
  pfVar4[0x33] = 1.0;
  pfVar4[0x34] = 1.0;
  pfVar4[0x35] = 0.0;
  pfVar4[0x36] = 1.0;
  pfVar4[0x37] = 1.0;
  uVar1 = this->u64_100;
  fVar2 = this->f32_108;
  fVar3 = this->f32_10c;
  pfVar4[0xc] = (float)uVar1;
  pfVar4[0xd] = (float)((ulong)uVar1 >> 0x20);
  pfVar4[0xe] = fVar2;
  pfVar4[0xf] = fVar3;
  (**(code **)(this->i32_1e4 + 0x4c))(this,param_2,param_3);
  pfVar4[1] = (*pfVar4 * (float)(this->i32_1f8 - (int)param_3)) /
              (float)this->i32_1f8;
  return;
}

// JP: 0x002bf2e0  CreateFpData__13FpObjectTaki2FP7_FpDatai  =  FpObjectTaki2::CreateFpData
void FpObjectTaki2::CreateFpData(int this,int param_2)

{
  undefined8 uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined1 in_vf0 [16];
  undefined1 auVar5 [16];
  undefined1 auVar6 [16];
  undefined1 auVar7 [16];
  undefined1 auStack_90 [16];
  undefined1 auStack_80 [8];
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined1 auStack_70 [8];
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined1 auStack_60 [16];
  undefined1 auStack_50 [16];
  undefined1 auStack_40 [16];
  undefined1 auStack_30 [16];
  undefined1 auStack_20 [16];
  undefined1 auStack_10 [16];
  
  param_2->u32_4 = 0;
  uVar1 = this->u64_100;
  uVar3 = this->u32_108;
  uVar4 = this->u32_10c;
  param_2->i32_30 = (int)uVar1;
  param_2->i32_34 = (int)((ulong)uVar1 >> 0x20);
  param_2->u32_38 = uVar3;
  param_2->u32_3c = uVar4;
  param_2->u32_bc = 0;
  FVector::FVector(auStack_10,this + 0xa0);
  auVar5 = _vmr32(in_vf0);
  auVar6 = _vmr32(auVar5);
  auVar7 = _vmr32(auVar6);
  auStack_20 = _sqc2(in_vf0);
  auStack_30 = _sqc2(auVar5);
  auStack_40 = _sqc2(auVar6);
  auStack_50 = _sqc2(auVar7);
  iVar2 = rand();
  sceVu0RotMatrixY(((float)iVar2 * 3.1415927) / 2.1474836e+09,auStack_50,auStack_50);
  Matrix::ApplyMatrix(auStack_70,auStack_50,auStack_10);
  param_2->i32_10 = auStack_70._0_4_;
  param_2->i32_14 = auStack_70._4_4_;
  param_2->u32_18 = uStack_68;
  param_2->u32_1c = uStack_64;
  iVar2 = rand();
  param_2->f32_10 = param_2->f32_10 * ((float)iVar2 / 2.1474836e+09);
  param_2->f32_14 = param_2->f32_14 * (1.0 - (float)iVar2 / 2.1474836e+09);
  FVector::FVector(auStack_60,param_2 + 0x10);
  FVector::Normalize(auStack_60);
  auVar5 = _lqc2(auStack_60);
  auVar6 = _qmtc2(this->f32_110 * 0.15);
  auVar5 = _vmulbc(auVar5,auVar6);
  auStack_90 = _sqc2(auVar5);
  FVector::FVector(auStack_80,auStack_90);
  param_2->i32_20 = auStack_80._0_4_;
  param_2->i32_24 = auStack_80._4_4_;
  param_2->u32_28 = uStack_78;
  param_2->u32_2c = uStack_74;
  return;
}

// JP: 0x002bf4a0  CalculateFunc__13FpObjectTaki2Fv  =  FpObjectTaki2::CalculateFunc
void FpObjectTaki2::CalculateFunc(undefined8 this)

{
  int iVar1;
  float *pfVar2;
  int this;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  undefined1 auVar8 [16];
  undefined1 auVar9 [16];
  undefined1 auStack_60 [16];
  undefined1 auStack_50 [16];
  undefined1 auStack_40 [16];
  undefined1 auStack_30 [16];
  undefined1 auStack_20 [16];
  undefined1 auStack_10 [8];
  float fStack_8;
  float fStack_4;
  
  
  fVar4 = (float)FpPrim::GetFrameSpeed(this->u32_8);
  pfVar2 = *(float **)(this + 0x1fc);
  fVar7 = this->f32_1dc;
  fVar6 = *pfVar2 * 0.33333;
  fVar5 = *pfVar2;
  for (iVar1 = 0; iVar1 < this->i32_1f8; iVar1 = iVar1 + 1) {
    pfVar2[1] = pfVar2[1] + fVar4;
    if (*pfVar2 <= *(float *)(this->i32_1fc + iVar1 * 0xf0 + 4)) {
      (**(code **)(this->i32_1e4 + 0x4c))(this,pfVar2,iVar1);
    }
    auVar8 = _lqc2(*(undefined1 (*) [16])(pfVar2 + 4));
    auVar9 = _qmtc2(pfVar2[1]);
    auVar8 = _vmulbc(auVar8,auVar9);
    auStack_50 = _sqc2(auVar8);
    FVector::FVector(auStack_30,auStack_50);
    auVar8 = _lqc2(*(undefined1 (*) [16])(this + 0x100));
    auVar9 = _lqc2(auStack_30);
    auVar8 = _vadd(auVar8,auVar9);
    auStack_60 = _sqc2(auVar8);
    FVector::FVector(auStack_20,auStack_60);
    auVar8 = _lqc2(auStack_20);
    auVar9 = _lqc2(*(undefined1 (*) [16])(pfVar2 + 8));
    auVar8 = _vadd(auVar8,auVar9);
    auStack_40 = _sqc2(auVar8);
    FVector::FVector(auStack_10,auStack_40);
    pfVar2[0xc] = auStack_10._0_4_;
    pfVar2[0xd] = auStack_10._4_4_;
    pfVar2[0xe] = fStack_8;
    pfVar2[0xf] = fStack_4;
    if (pfVar2[1] < fVar6) {
      pfVar2[0x2f] = (fVar7 * pfVar2[1]) / fVar6;
    }
    else if (pfVar2[1] < fVar5 * 0.66666) {
      pfVar2[0x2f] = fVar7;
    }
    else {
      pfVar2[0x2f] = (fVar7 * (*pfVar2 - pfVar2[1])) / (*pfVar2 - fVar5 * 0.66666);
    }
    pfVar2 = pfVar2 + 0x3c;
  }
  (**(code **)(this->i32_1e4 + 0x44))();
  return;
}

// JP: 0x00325750  Init__12FpSmokeParamFv  =  FpSmokeParam::Init
void FpSmokeParam::Init(int this)

{
  undefined8 uVar1;
  undefined1 auStack_50 [16];
  undefined1 auStack_40 [16];
  undefined1 auStack_30 [24];
  undefined1 auStack_18 [4];
  undefined1 auStack_14 [4];
  int iStack_10;
  
  iStack_10 = this;
  uVar1 = FVector::FVector(0,0,0,0x3f800000,auStack_30);
  FVector::__as(iStack_10,uVar1);
  uVar1 = FVector::FVector(0,0xbf000000,0,0x3f800000,auStack_40);
  FVector::__as(iStack_10 + 0x10,uVar1);
  uVar1 = FVector::FVector(0,0,0,0x3f800000,auStack_50);
  FVector::__as(iStack_10 + 0x20,uVar1);
  uVar1 = _rgba32::_rgba32(auStack_14,0xff,0xff,0xff,0xff);
  _rgba32::__as(iStack_10 + 0x30,uVar1);
  uVar1 = _rgba32::_rgba32(auStack_18,0xff,0xff,0xff,0xff);
  _rgba32::__as(iStack_10 + 0x34,uVar1);
  iStack_10->u32_38 = 0x41200000;
  iStack_10->u32_3c = 0x41a00000;
  iStack_10->u32_40 = 0x1e;
  iStack_10->u32_44 = 0x5a;
  iStack_10->u8_48 = 0;
  iStack_10->u8_49 = 0;
  iStack_10->u8_4a = 10;
  iStack_10->u8_4b = 0;
  iStack_10->u32_4c = 0;
  return;
}

// JP: 0x003258d0  __ct__12FpSmokeParamFv  =  FpSmokeParam::FpSmokeParam
int FpSmokeParam::FpSmokeParam(int this)

{
  FVector::FVector(this);
  FVector::FVector(this + 0x10);
  FVector::FVector(this + 0x20);
  _rgba32::_rgba32(this + 0x30);
  _rgba32::_rgba32(this + 0x34);
  return this;
}

// JP: 0x00325d00  Init__12FpFlareParamFv  =  FpFlareParam::Init
void FpFlareParam::Init(int this)

{
  undefined8 uVar1;
  undefined1 auStack_40 [16];
  undefined1 auStack_30 [28];
  undefined1 auStack_14 [4];
  int iStack_10;
  
  iStack_10 = this;
  uVar1 = FVector::FVector(0,0,0,0x3f800000,auStack_30);
  FVector::__as(iStack_10,uVar1);
  uVar1 = _rgba32::_rgba32(auStack_14,0xff,0xff,0xff,0xff);
  _rgba32::__as(iStack_10 + 0x10,uVar1);
  iStack_10->u32_14 = 0x42c80000;
  iStack_10->u8_30 = iStack_10->u8_30 & 0xfe;
  iStack_10->u8_30 = iStack_10->u8_30 & 0xfd;
  iStack_10->u32_30 = iStack_10->u32_30 & 3;
  iStack_10->u32_18 = 0;
  iStack_10->u32_1c = 0x3f4ccccd;
  iStack_10->u32_20 = 0;
  iStack_10->u32_24 = 0;
  iStack_10->u32_28 = 0;
  iStack_10->u32_2c = 1;
  uVar1 = FVector::FVector(0,0,0,0,auStack_40);
  FVector::__as(iStack_10 + 0x40,uVar1);
  iStack_10->u32_3c = 0;
  iStack_10->u32_38 = 0;
  iStack_10->u32_34 = 0;
  return;
}

// JP: 0x00325e90  __ct__12FpFlareParamFv  =  FpFlareParam::FpFlareParam
int FpFlareParam::FpFlareParam(int this)

{
  FVector::FVector(this);
  _rgba32::_rgba32(this + 0x10);
  FVector::FVector(this + 0x40);
  return this;
}

// JP: 0x00326370  Init__14FpThunderParamFv  =  FpThunderParam::Init
void FpThunderParam::Init(int this)

{
  undefined8 uVar1;
  undefined1 auStack_40 [16];
  undefined1 auStack_30 [24];
  undefined1 auStack_18 [4];
  undefined1 auStack_14 [4];
  int iStack_10;
  
  iStack_10 = this;
  uVar1 = FVector::FVector(0,0,0,0x3f800000,auStack_30);
  FVector::__as(iStack_10,uVar1);
  uVar1 = FVector::FVector(0x42c80000,0xc2c80000,0x42c80000,0x3f800000,auStack_40);
  FVector::__as(iStack_10 + 0x10,uVar1);
  uVar1 = _rgba32::_rgba32(auStack_14,0xdc,0xdc,0xff,0x78);
  _rgba32::__as(iStack_10 + 0x20,uVar1);
  uVar1 = _rgba32::_rgba32(auStack_18,0,0,200,0x50);
  _rgba32::__as(iStack_10 + 0x24,uVar1);
  iStack_10->u32_28 = 0x3f800000;
  iStack_10->u32_2c = 0x40a00000;
  iStack_10->u32_30 = 0x42700000;
  iStack_10->u32_34 = 0x14;
  iStack_10->u8_38 = iStack_10->u8_38 & 0xfe;
  iStack_10->u32_3c = 0;
  iStack_10->u32_38 = iStack_10->u32_38 & 1;
  return;
}

// JP: 0x003264f0  __ct__14FpThunderParamFv  =  FpThunderParam::FpThunderParam
int FpThunderParam::FpThunderParam(int this)

{
  FVector::FVector(this);
  FVector::FVector(this + 0x10);
  _rgba32::_rgba32(this + 0x20);
  _rgba32::_rgba32(this + 0x24);
  return this;
}
