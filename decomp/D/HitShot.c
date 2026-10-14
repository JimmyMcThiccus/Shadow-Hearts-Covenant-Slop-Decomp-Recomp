// decomp/D/HitShot.c — cleaned Ghidra output (SLPM_602.19, Metrowerks MIPS), Shadow Hearts: Covenant JP demo.
// Field accesses are shown as this->T_off (T = u8/u16/u32/f32/i32/p, off = hex offset);
// JRing fields are named from the recovered struct. See notes/D/*.md for layouts.
// CAVEAT: when the base pointer is a float*/int*/short*, the number in `T_off` is an ELEMENT offset (byte offset = off*sizeof(elem)).
// `this` is the C++ this pointer (param_1); the Metrowerks ABI passes it in a0.

// JP: 0x0030adc0  __ct__7HitShotFPFPvi_vPv  =  HitShot::HitShot
undefined4 * HitShot::HitShot(undefined4 *this,undefined4 param_2,undefined4 param_3)

{
  undefined8 uVar1;
  undefined1 auStack_40 [16];
  undefined4 *puStack_30;
  undefined4 uStack_20;
  undefined4 uStack_10;
  
  this[0x17] = HitShot::__vt;
  puStack_30 = this;
  uStack_20 = param_2;
  uStack_10 = param_3;
  FVector::FVector(this + 4);
  FVector::FVector(puStack_30 + 8);
  FVector::FVector(puStack_30 + 0xc);
  FVector::FVector(puStack_30 + 0x10);
  *puStack_30 = 0;
  puStack_30[1] = 0;
  puStack_30[2] = 0;
  puStack_30[3] = 0;
  puStack_30[0x15] = uStack_20;
  puStack_30[0x16] = uStack_10;
  uVar1 = FVector::FVector(0,0,0,0x3f800000,auStack_40);
  uVar1 = FVector::__as(puStack_30 + 0xc,uVar1);
  uVar1 = FVector::__as(puStack_30 + 8,uVar1);
  FVector::__as(puStack_30 + 4,uVar1);
  Init__Q27HitShot22_class_1793HitShot_cppFv(puStack_30 + 0x14);
  return puStack_30;
}

// JP: 0x0030af40  __dt__7HitShotFv  =  HitShot::~HitShot
int HitShot::~HitShot(int this,short param_2)

{
  int iVar1;
  
  if (this != 0) {
    *(undefined1 **)(this + 0x5c) = HitShot::__vt;
    if (this->i32_8 != 0) {
      iVar1 = this->i32_8;
      if (iVar1 != 0) {
        (**(code **)(iVar1->i32_10 + 8))(iVar1,1);
      }
      this->u32_8 = 0;
    }
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}

// JP: 0x0030b090  Create__7HitShotFPc  =  HitShot::Create
void HitShot::Create(int *this,int param_2)

{
  *this = param_2;
  this[1] = param_2 + (uint)*(ushort *)(*this + 8) * 0x10;
  return;
}

// JP: 0x0030b0e0  SetPoint__7HitShotFR7FVectorR7FVector  =  HitShot::SetPoint
void HitShot::SetPoint(int this,undefined4 param_2,undefined4 param_3)

{
  undefined1 auStack_40 [16];
  int iStack_30;
  undefined4 uStack_20;
  undefined4 uStack_10;
  
  iStack_30 = this;
  uStack_20 = param_2;
  uStack_10 = param_3;
  FVector::__as(this + 0x10,param_2);
  FVector::__as(iStack_30 + 0x30,uStack_20);
  FVector::__as(iStack_30 + 0x20,uStack_10);
  FVector::__mi(auStack_40,iStack_30 + 0x20,iStack_30 + 0x10);
  FVector::__as(iStack_30 + 0x40,auStack_40);
  FVector::Normalize(iStack_30 + 0x40);
  return;
}

// JP: 0x0030b180  AddTime__7HitShotFff  =  HitShot::AddTime
/* WARNING: Function: fptodp replaced with injection: fptodp */

void HitShot::AddTime(float this,float param_2,int param_3)

{
  long lVar1;
  byte bVar2;
  float fVar3;
  undefined4 uVar4;
  undefined1 auStack_70 [16];
  undefined1 auStack_60 [16];
  undefined1 auStack_50 [16];
  undefined1 auStack_40 [16];
  int iStack_30;
  float fStack_20;
  float fStack_10;
  
  bVar2 = param_3->u8_50 & 3;
  iStack_30 = param_3;
  fStack_20 = this;
  fStack_10 = param_2;
  if (bVar2 == 2) {
    param_3->f32_c = param_3->f32_c + this;
    fVar3 = (float)HitShot::GetModdleSpeed(param_3);
    printf(_1878,(double)fVar3);
    uVar4 = HitShot::GetModdleSpeed(iStack_30);
    FVector::__ml(uVar4,auStack_70,iStack_30 + 0x40);
    FVector::__ml(fStack_20 / fStack_10,auStack_60,auStack_70);
    FVector::__apl(iStack_30 + 0x30,auStack_60);
    lVar1 = HitShot::IsAtEnd(iStack_30);
    if (((lVar1 != 0) && (iStack_30->i32_54 != 0)) &&
       ((long)((ulong)iStack_30->u8_50 << 0x3d) < 0)) {
      (**(code **)(iStack_30 + 0x54))(iStack_30->u32_58,1);
      iStack_30->u32_54 = 0;
      iStack_30->u32_58 = 0;
    }
  }
  else if ((bVar2 != 1) && ((param_3->u8_50 & 3) == 0)) {
    param_3->f32_c = param_3->f32_c + this;
    FVector::__ml(*(undefined4 *)(param_3->i32_4 + 0x18),auStack_50,param_3 + 0x40);
    FVector::__ml(fStack_20 / fStack_10,auStack_40,auStack_50);
    FVector::__apl(iStack_30 + 0x30,auStack_40);
    lVar1 = HitShot::IsAtEnd(iStack_30);
    if ((lVar1 != 0) &&
       ((iStack_30->i32_54 != 0 && ((long)((ulong)iStack_30->u8_50 << 0x3d) < 0)
        ))) {
      (**(code **)(iStack_30 + 0x54))(iStack_30->u32_58,1);
      iStack_30->u32_54 = 0;
      iStack_30->u32_58 = 0;
    }
  }
  return;
}

// JP: 0x0030b3b0  IsAtEnd__7HitShotFv  =  HitShot::IsAtEnd
undefined4 HitShot::IsAtEnd(int this)

{
  float *pfVar1;
  float *pfVar2;
  undefined4 uVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  undefined1 auStack_50 [16];
  undefined1 auStack_40 [28];
  float fStack_24;
  float fStack_20;
  float fStack_1c;
  float fStack_18;
  float fStack_14;
  int iStack_10;
  
  iStack_10 = this;
  FVector::__mi(auStack_40,this + 0x20,this + 0x10);
  pfVar1 = (float *)FVector::vx(auStack_40);
  pfVar2 = (float *)FVector::vx(auStack_40);
  fVar4 = *pfVar1;
  fVar6 = *pfVar2;
  pfVar1 = (float *)FVector::vy(auStack_40);
  pfVar2 = (float *)FVector::vy(auStack_40);
  fVar5 = *pfVar1;
  fVar7 = *pfVar2;
  pfVar1 = (float *)FVector::vz(auStack_40);
  pfVar2 = (float *)FVector::vz(auStack_40);
  fStack_14 = SQRT(*pfVar1 * *pfVar2 + fVar4 * fVar6 + fVar5 * fVar7);
  if (fStack_14 < 0.2) {
    uVar3 = 1;
  }
  else {
    FVector::__mi(auStack_50,iStack_10 + 0x30,iStack_10 + 0x10);
    pfVar1 = (float *)FVector::vx(auStack_50);
    pfVar2 = (float *)FVector::vx(auStack_50);
    fVar4 = *pfVar1;
    fVar6 = *pfVar2;
    pfVar1 = (float *)FVector::vy(auStack_50);
    pfVar2 = (float *)FVector::vy(auStack_50);
    fVar5 = *pfVar1;
    fVar7 = *pfVar2;
    pfVar1 = (float *)FVector::vz(auStack_50);
    pfVar2 = (float *)FVector::vz(auStack_50);
    fStack_18 = *pfVar1 * *pfVar2 + fVar4 * fVar6 + fVar5 * fVar7;
    if (fStack_18 == 0.0) {
      uVar3 = 0;
    }
    else {
      pfVar1 = (float *)FVector::vx(auStack_40);
      pfVar2 = (float *)FVector::vx(auStack_50);
      fVar4 = *pfVar1;
      fVar6 = *pfVar2;
      pfVar1 = (float *)FVector::vy(auStack_40);
      pfVar2 = (float *)FVector::vy(auStack_50);
      fVar5 = *pfVar1;
      fVar7 = *pfVar2;
      pfVar1 = (float *)FVector::vz(auStack_40);
      pfVar2 = (float *)FVector::vz(auStack_50);
      fStack_1c = (*pfVar1 * *pfVar2 + fVar4 * fVar6 + fVar5 * fVar7) / fStack_18;
      if ((fStack_1c < 0.0) || (1.0 < fStack_1c)) {
        uVar3 = 0;
      }
      else {
        pfVar1 = (float *)FVector::vx(auStack_50);
        fVar5 = fStack_1c * *pfVar1;
        pfVar1 = (float *)FVector::vx(iStack_10 + 0x10);
        fVar4 = *pfVar1;
        pfVar1 = (float *)FVector::vx(iStack_10 + 0x20);
        fStack_20 = (fVar5 + fVar4) - *pfVar1;
        pfVar1 = (float *)FVector::vy(auStack_50);
        fVar5 = fStack_1c * *pfVar1;
        pfVar1 = (float *)FVector::vy(iStack_10 + 0x10);
        fVar4 = *pfVar1;
        pfVar1 = (float *)FVector::vy(iStack_10 + 0x20);
        fStack_24 = (fVar5 + fVar4) - *pfVar1;
        pfVar1 = (float *)FVector::vz(auStack_50);
        fVar5 = fStack_1c * *pfVar1;
        pfVar1 = (float *)FVector::vz(iStack_10 + 0x10);
        fVar4 = *pfVar1;
        pfVar1 = (float *)FVector::vz(iStack_10 + 0x20);
        fVar4 = (fVar5 + fVar4) - *pfVar1;
        if (SQRT(fVar4 * fVar4 + fStack_20 * fStack_20 + fStack_24 * fStack_24) <= 0.2) {
          uVar3 = 1;
        }
        else {
          uVar3 = 0;
        }
      }
    }
  }
  return uVar3;
}

// JP: 0x0030b790  SetUpdateMode__7HitShotFi  =  HitShot::SetUpdateMode
void HitShot::SetUpdateMode(int this,int param_2)

{
  this->u8_50 = this->u8_50 & 0xfc | (byte)param_2 & 3;
  if (param_2 == 1) {
    FVector::__as(this + 0x30,this + 0x20);
  }
  else if ((param_2 == 2) || (param_2 == 0)) {
    FVector::__as(this + 0x30,this + 0x10);
  }
  return;
}

// JP: 0x0030b840  AddKey__7HitShotFP10HitDynaKey  =  HitShot::AddKey
void HitShot::AddKey(int this,undefined4 param_2)

{
  this->u8_50 = this->u8_50 & 0xfc | 2;
  if (this->i32_8 == 0) {
    this->u32_8 = param_2;
  }
  else {
    CList::AddTail(this->u32_8,param_2);
  }
  return;
}

// JP: 0x0030b8c0  GetModdleSpeed__7HitShotFv  =  HitShot::GetModdleSpeed
float HitShot::GetModdleSpeed(int this)

{
  int iVar1;
  int iVar2;
  
  iVar1 = this->i32_8;
  do {
    iVar2 = iVar1;
    if (iVar2 == 0) {
      return 0.0;
    }
    if (iVar2->f32_8 == this->f32_c) {
      return iVar2->f32_c;
    }
    iVar1 = CList::GetNext(iVar2);
    if (iVar1 == 0) {
      return iVar2->f32_c;
    }
  } while ((this->f32_c <= iVar2->f32_8) ||
          (iVar1->f32_8 <= this->f32_c));
  return iVar2->f32_c +
         ((this->f32_c - iVar2->f32_8) /
         (iVar1->f32_8 - iVar2->f32_8)) *
         (iVar1->f32_c - iVar2->f32_c);
}
