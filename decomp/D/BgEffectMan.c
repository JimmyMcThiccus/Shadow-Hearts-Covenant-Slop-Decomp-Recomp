// decomp/D/BgEffectMan.c — cleaned Ghidra output (SLPM_602.19, Metrowerks MIPS), Shadow Hearts: Covenant JP demo.
// Field accesses are shown as this->T_off (T = u8/u16/u32/f32/i32/p, off = hex offset);
// JRing fields are named from the recovered struct. See notes/D/*.md for layouts.
// CAVEAT: when the base pointer is a float*/int*/short*, the number in `T_off` is an ELEMENT offset (byte offset = off*sizeof(elem)).
// `this` is the C++ this pointer (param_1); the Metrowerks ABI passes it in a0.

// JP: 0x003c2810  __ct__11BgEffectManFv  =  BgEffectMan::BgEffectMan
int BgEffectMan::BgEffectMan(int this)

{
  undefined4 uVar1;
  
  PutiManager::PutiManager(this);
  uVar1 = __nwa(0x1400);
  this->u32_1c = uVar1;
  memset((void *)(this + 0x20),0,0x200);
  return this;
}

// JP: 0x003c2870  Init__11BgEffectManFv  =  BgEffectMan::Init
undefined4 BgEffectMan::Init(undefined4 this)

{
  PutiManager::Init(this);
  if (BgEffectMan::cmnTexture == 0) {
    DvdromOrder::ReadOrder
              (DvdromOrder::Dvdromour,0x401700,0x3c27c0,0,this,0);
  }
  BgEffectMan::InitCmnTex(this);
  return 1;
}

// JP: 0x003c28e0  GetEffect__11BgEffectManFii  =  BgEffectMan::GetEffect
undefined4 BgEffectMan::GetEffect(int this,int param_2,int param_3)

{
  undefined4 uVar1;
  
  if (param_2 < 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = *(undefined4 *)(this + (param_3 + param_2 * 0x40) * 4 + 0x20);
  }
  return uVar1;
}

// JP: 0x003c2960  InitCmnTex__11BgEffectManFv  =  BgEffectMan::InitCmnTex
undefined4 BgEffectMan::InitCmnTex(int this)

{
  int iVar1;
  short *psVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  long lVar6;
  undefined1 uVar7;
  
  if (BgEffectMan::cmnTexture == 0) {
    uVar3 = 0;
  }
  else {
    uVar3 = BgEffectMan::cmnTexture->u32_4;
    iVar1 = GetFileCount(uVar3);
    for (iVar4 = 0; iVar4 < iVar1; iVar4 = iVar4 + 1) {
      psVar2 = (short *)GetFileEntry(uVar3,iVar4);
      if (psVar2[5] == 0) {
        iVar5 = 2;
      }
      else {
        iVar5 = 4;
      }
      *(uint *)(this->i32_1c + iVar4 * 0x14 + 4) =
           (int)psVar2 + (psVar2[6] * iVar5 + 0xfU & 0xfffffff0) + 0x10;
      *(short **)(this->i32_1c + iVar4 * 0x14) = psVar2 + 8;
      lVar6 = 0;
      while (lVar6 < psVar2[6]) {
        iVar5 = (int)lVar6;
        *(char *)((int)psVar2 + iVar5 * 4 + 0x13) = (char)psVar2[iVar5 * 2 + 8];
        lVar6 = (long)(iVar5 + 1);
      }
      *(int *)(this->i32_1c + iVar4 * 0x14 + 8) = (int)*psVar2;
      *(int *)(this->i32_1c + iVar4 * 0x14 + 0xc) = (int)psVar2[1];
      if (psVar2[4] == 1) {
        uVar7 = 8;
      }
      else {
        uVar7 = 4;
      }
      *(undefined1 *)(this->i32_1c + iVar4 * 0x14 + 0x10) = uVar7;
    }
    uVar3 = 1;
  }
  return uVar3;
}

// JP: 0x003c2bc0  DeleteAll__11BgEffectManFi  =  BgEffectMan::DeleteAll
undefined4 BgEffectMan::DeleteAll(int this,int param_2)

{
  int *piVar1;
  int iVar2;
  
  if (param_2 < 0) {
    PutiManager::DeleteAll(this);
    memset((void *)(this + 0x20),0,0x200);
  }
  else {
    piVar1 = (int *)(this + param_2 * 0x100 + 0x20);
    for (iVar2 = 0; iVar2 < 0x40; iVar2 = iVar2 + 1) {
      if (*piVar1 != 0) {
        PutiPrim::Delete(*piVar1);
        *piVar1 = 0;
      }
      piVar1 = piVar1 + 1;
    }
  }
  return 1;
}

// JP: 0x003c2ca0  CreateEffect__11BgEffectManFiiiPv  =  BgEffectMan::CreateEffect
bool BgEffectMan::CreateEffect
               (int this,int param_2,int param_3,int param_4,undefined4 param_5)

{
  long lVar1;
  
  if (param_4 < 0x100) {
    lVar1 = CreateFpEffect(param_4,param_5);
  }
  else {
    lVar1 = CreateFldBGEffect(param_4,param_5);
  }
  if (lVar1 != 0) {
    *(int *)(this + (param_3 + param_2 * 0x40) * 4 + 0x20) = (int)lVar1;
  }
  return lVar1 != 0;
}

// JP: 0x003c2d60  ClearEffect__11BgEffectManFii  =  BgEffectMan::ClearEffect
undefined8 BgEffectMan::ClearEffect(int this,int param_2,int param_3)

{
  int iVar1;
  undefined8 uVar2;
  int *piVar3;
  
  if (param_3 < 0) {
    uVar2 = BgEffectMan::DeleteAll(this,param_2);
  }
  else {
    piVar3 = (int *)(this + (param_3 + param_2 * 0x40) * 4 + 0x20);
    iVar1 = *piVar3;
    if (iVar1 == 0) {
      uVar2 = 0;
    }
    else {
      PutiPrim::Delete(iVar1);
      *piVar3 = 0;
      uVar2 = 1;
    }
  }
  return uVar2;
}

// JP: 0x003c2e10  Dsp__11BgEffectManFi  =  BgEffectMan::Dsp
void BgEffectMan::Dsp(int this,int param_2)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  piVar2 = (int *)(this + param_2 * 0x100 + 0x20);
  for (iVar3 = 0; iVar3 < 0x40; iVar3 = iVar3 + 1) {
    iVar1 = *piVar2;
    if (iVar1 != 0) {
      (**(code **)(iVar1->i32_10 + 0x38))(iVar1,1);
    }
    piVar2 = piVar2 + 1;
  }
  return;
}

// JP: 0x003c2eb0  Clr__11BgEffectManFi  =  BgEffectMan::Clr
void BgEffectMan::Clr(int this,int param_2)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  piVar2 = (int *)(this + param_2 * 0x100 + 0x20);
  for (iVar3 = 0; iVar3 < 0x40; iVar3 = iVar3 + 1) {
    iVar1 = *piVar2;
    if (iVar1 != 0) {
      (**(code **)(iVar1->i32_10 + 0x38))(iVar1,0);
    }
    piVar2 = piVar2 + 1;
  }
  return;
}

// JP: 0x003c2f50  EffectAlpha__11BgEffectManFiifi  =  BgEffectMan::EffectAlpha
void BgEffectMan::EffectAlpha
               (undefined4 this,int param_2,int param_3,int param_4,undefined4 param_5)

{
  int iVar1;
  
  iVar1 = *(int *)(param_2 + (param_4 + param_3 * 0x40) * 4 + 0x20);
  if (iVar1 != 0) {
    (**(code **)(iVar1->i32_10 + 0x34))(this,iVar1,param_5);
  }
  return;
}

// JP: 0x003c2fd0  __ct__10CBgElementFv  =  CBgElement::CBgElement
int CBgElement::CBgElement(int this)

{
  int iVar1;
  
  for (iVar1 = 0; iVar1 < 0x20; iVar1 = iVar1 + 1) {
    *(undefined4 *)(this + iVar1 * 4) = 0xffffffff;
  }
  this->u32_284 = 0;
  this->u16_282 = 0xffff;
  return this;
}

// JP: 0x003c3040  __dt__10CBgElementFv  =  CBgElement::~CBgElement
int CBgElement::~CBgElement(int this,short param_2)

{
  if ((this != 0) && (0 < param_2)) {
    __dl(this);
  }
  return this;
}

// JP: 0x003c30a0  Create__10CBgElementFPUcb  =  CBgElement::Create
char CBgElement::Create(undefined8 this,undefined8 param_2,long param_3)

{
  ushort uVar1;
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  char cVar2;
  char cVar3;
  uint *puVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  long lVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  undefined8 uVar12;
  int iVar13;
  int this;
  ulong uVar15;
  ulong uVar16;
  bool bVar17;
  uint uVar18;
  uint uVar19;
  bool bStack_140;
  undefined1 auStack_110 [16];
  undefined1 auStack_100 [16];
  undefined1 auStack_f0 [16];
  undefined1 auStack_e0 [16];
  undefined1 auStack_d0 [16];
  undefined1 auStack_c0 [16];
  undefined1 auStack_b0 [16];
  undefined1 auStack_a0 [16];
  undefined1 auStack_90 [16];
  undefined1 auStack_80 [8];
  undefined4 uStack_78;
  undefined4 uStack_74;
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
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  lVar8 = __nw(0x24);
  uVar9 = 0;
  if (lVar8 != 0) {
    uVar9 = CSTGDB::CSTGDB(lVar8);
  }
  
  this->u16_280 = 0;
  memset((void *)(this + 0x80),0,0x80);
  if ((this->u8_284 & 1) != 0) {
    CBgElement::Clear(this);
  }
  cVar2 = CSTGDB::SetData(uVar9,param_2);
  if (cVar2 != '\0') {
    if ((param_3 == 0) && (lVar8 = CSTGDB::Find(uVar9,0x202020544847494c), lVar8 != 0)) {
      uStack_30 = in_zero_lo;
      uStack_2c = in_zero_hi;
      uStack_20 = in_zero_lo;
      uStack_1c = in_zero_hi;
      uStack_18 = in_zero_udw;
      uStack_14 = in_register_0000000c;
      uStack_10 = in_zero_lo;
      uStack_c = in_zero_hi;
      uStack_8 = in_zero_udw;
      uStack_4 = in_register_0000000c;
      puVar4 = (uint *)CSTGDB::GetDataAddr(uVar9,lVar8);
      cVar3 = CSTGDB::CheckVersion(uVar9,0x30312e3020444253);
      iVar5 = CSTGDB::GetDataNum(uVar9,lVar8);
      this->i16_280 = (short)iVar5;
      for (iVar7 = 0; iVar7 < iVar5; iVar7 = iVar7 + 1) {
        if (cVar3 == '\0') {
          FVector::FVector(auStack_70,puVar4 + 4);
          uStack_10 = auStack_70._0_4_;
          uStack_c = auStack_70._4_4_;
          uStack_8 = uStack_68;
          uStack_4 = uStack_64;
          FVector::FVector(auStack_80,puVar4 + 8);
          uStack_20 = auStack_80._0_4_;
          uStack_1c = auStack_80._4_4_;
          uStack_18 = uStack_78;
          uStack_14 = uStack_74;
          FVector::FVector(auStack_90,puVar4 + 0xc);
          uStack_30 = (undefined4)auStack_90._0_8_;
          uStack_2c = SUB84(auStack_90._0_8_,4);
          uVar6 = (byte)*puVar4 & 7;
          uVar15 = ((ulong)(byte)*puVar4 & 0x7f) >> 5;
          uVar16 = ((ulong)(byte)*puVar4 & 0x1f) >> 3;
          bVar17 = (long)((ulong)(byte)*puVar4 << 0x38) < 0;
          bStack_140 = (*puVar4 & 0x100) != 0;
          uVar18 = puVar4[2];
          uVar19 = puVar4[3];
        }
        else {
          FVector::FVector(auStack_40,puVar4 + 4);
          uStack_10 = auStack_40._0_4_;
          uStack_c = auStack_40._4_4_;
          uStack_8 = uStack_38;
          uStack_4 = uStack_34;
          FVector::FVector(auStack_50,puVar4 + 8);
          uStack_20 = auStack_50._0_4_;
          uStack_1c = auStack_50._4_4_;
          uStack_18 = uStack_48;
          uStack_14 = uStack_44;
          FVector::FVector(auStack_60,puVar4 + 0xc);
          uStack_30 = (undefined4)auStack_60._0_8_;
          uStack_2c = SUB84(auStack_60._0_8_,4);
          uVar6 = *puVar4;
          uVar15 = (ulong)(int)puVar4[2];
          uVar16 = 1;
          bVar17 = false;
          bStack_140 = true;
          uVar18 = 0x42340000;
          uVar19 = 0x3f800000;
        }
        lVar8 = -1;
        if (uVar6 == 3) {
          uVar10 = FVector::FVector(auStack_f0,&uStack_20);
          uVar11 = FVector::FVector(auStack_100,&uStack_30);
          uVar12 = FVector::FVector(auStack_110,&uStack_10);
          lVar8 = LightControl::CreateSpot(uVar10,uVar11,uVar12);
          LightControl::changeAngle(uVar18,lVar8);
          LightControl::changeDropOff(uVar19,lVar8);
        }
        else if (uVar6 == 2) {
          uVar10 = FVector::FVector(auStack_d0,&uStack_20);
          uVar11 = FVector::FVector(auStack_e0,&uStack_10);
          lVar8 = LightControl::CreatePoint(uVar10,uVar11);
        }
        else if (uVar6 == 1) {
          uVar10 = FVector::FVector(auStack_b0,&uStack_30);
          uVar11 = FVector::FVector(auStack_c0,&uStack_10);
          lVar8 = LightControl::CreateDirectional(uVar10,uVar11);
        }
        else if (uVar6 == 0) {
          uVar10 = FVector::FVector(auStack_a0,&uStack_10);
          lVar8 = LightControl::CreateAmbient(uVar10);
        }
        *(int *)(this + iVar7 * 4) = (int)lVar8;
        if (-1 < lVar8) {
          memcpy((void *)(this + iVar7 * 0xc + 0x100),&uStack_20,0xc);
          LightControl::changeLevel(lVar8,uVar15);
          LightControl::changeDeclineType(lVar8,uVar16);
          LightControl::changeShadowFlg(lVar8,bVar17);
          LightControl::changeActive(lVar8,bStack_140);
          LightControl::changeStrength(puVar4[1],lVar8);
        }
        puVar4 = puVar4 + 0x10;
      }
    }
    lVar8 = CSTGDB::Find(uVar9,0x2020544345464645);
    if (lVar8 != 0) {
      iVar5 = CSTGDB::GetDataAddr(uVar9,lVar8);
      if (this->i16_282 < 0) {
        uVar1 = (ushort)BgEffectMan::m_curMagic;
        BgEffectMan::m_curMagic = BgEffectMan::m_curMagic + 1;
        this->u16_282 = uVar1 & 1;
      }
      iVar7 = CSTGDB::GetDataNum(uVar9,lVar8);
      for (iVar13 = 0; iVar13 < iVar7; iVar13 = iVar13 + 1) {
        if ((iVar5->u8_4 & 1) == 0) {
          iVar5->u8_4 = iVar5->u8_4 & 0xfe;
        }
        else {
          BgEffectMan::CreateEffect
                    (BgEffectMan::eff,this->u16_282,iVar13,
                     iVar5->u16_2,iVar5 + iVar5->i32_8);
        }
        iVar5 = iVar5 + 0x10;
      }
    }
    this->u8_284 = this->u8_284 & 0xfe | 1;
  }
  (**(code **)(*(int *)((int)uVar9 + 8) + 0xc))();
  return cVar2;
}

// JP: 0x003c36f0  Clear__10CBgElementFv  =  CBgElement::Clear
void CBgElement::Clear(int this)

{
  int iVar1;
  
  for (iVar1 = 0; iVar1 < 0x20; iVar1 = iVar1 + 1) {
    if (*(int *)(this + iVar1 * 4) != -1) {
      LightControl::release(*(undefined4 *)(this + iVar1 * 4));
    }
    *(undefined4 *)(this + iVar1 * 4) = 0xffffffff;
  }
  if (-1 < this->i16_282) {
    BgEffectMan::DeleteAll(BgEffectMan::eff,this->u16_282);
  }
  this->u16_282 = 0xffff;
  this->u8_284 = this->u8_284 & 0xfe;
  this->u8_284 = this->u8_284 & 0xfd;
  return;
}

// JP: 0x003c3800  Dsp__10CBgElementFv  =  CBgElement::Dsp
void CBgElement::Dsp(int this)

{
  int iVar1;
  int iVar2;
  
  if (-1 < this->i16_282) {
    BgEffectMan::Dsp(BgEffectMan::eff,this->u16_282);
  }
  for (iVar2 = 0; iVar2 < 0x20; iVar2 = iVar2 + 1) {
    iVar1 = *(int *)(this + iVar2 * 4);
    if (-1 < iVar1) {
      LightControl::changeActive(iVar1,1);
    }
  }
  this->u8_284 = this->u8_284 & 0xfd | 2;
  return;
}

// JP: 0x003c38d0  Clr__10CBgElementFv  =  CBgElement::Clr
void CBgElement::Clr(int this)

{
  int iVar1;
  int iVar2;
  
  for (iVar2 = 0; iVar2 < 0x20; iVar2 = iVar2 + 1) {
    iVar1 = *(int *)(this + iVar2 * 4);
    if (-1 < iVar1) {
      LightControl::changeActive(iVar1,0);
    }
  }
  if (-1 < this->i16_282) {
    BgEffectMan::Clr(BgEffectMan::eff,this->u16_282);
  }
  this->u8_284 = this->u8_284 & 0xfd;
  return;
}

// JP: 0x003c39a0  UpdateLight__10CBgElementFf  =  CBgElement::UpdateLight
void CBgElement::UpdateLight(int this)

{
  int iVar1;
  undefined8 uVar2;
  int iVar3;
  undefined1 auVar4 [16];
  undefined1 auVar5 [16];
  undefined1 auStack_90 [16];
  undefined8 uStack_80;
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined8 uStack_70;
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined1 auStack_60 [64];
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined1 auStack_10 [16];
  
  if (((this->u8_284 & 1) != 0) &&
     ((long)((ulong)this->u8_284 << 0x3e) < 0)) {
    for (iVar3 = 0; iVar3 < 0x20; iVar3 = iVar3 + 1) {
      iVar1 = *(int *)(this + iVar3 * 4);
      if ((-1 < iVar1) && (*(int *)(this + iVar3 * 4 + 0x80) != 0)) {
        memcpy(auStack_10,(void *)(this + iVar3 * 0xc + 0x100),0xc);
        Frame::getWorldRot
                  (auStack_60,*(undefined4 *)(this + iVar3 * 4 + 0x80),VIF1Prim::m_Env & 1);
        Matrix::ApplyMatrix(&uStack_70,auStack_60,auStack_10);
        auStack_10._8_4_ = uStack_68;
        auStack_10._0_8_ = uStack_70;
        auStack_10._12_4_ = uStack_64;
        Frame::getWorldPos
                  (&uStack_80,*(undefined4 *)(this + iVar3 * 4 + 0x80),VIF1Prim::m_Env & 1);
        uStack_20 = (undefined4)uStack_80;
        uStack_1c = (undefined4)((ulong)uStack_80 >> 0x20);
        uStack_18 = uStack_78;
        uStack_14 = uStack_74;
        auVar4._8_4_ = uStack_78;
        auVar4._0_8_ = uStack_80;
        auVar4._12_4_ = uStack_74;
        auVar5 = _lqc2(auVar4);
        auVar4 = _lqc2(auStack_10);
        auVar4 = _vadd(auVar4,auVar5);
        auVar4 = _sqc2(auVar4);
        auStack_10._0_12_ = auVar4._0_12_;
        auStack_10._12_4_ = 0x3f800000;
        uVar2 = FVector::FVector(auStack_90,auStack_10);
        LightControl::changePos(iVar1,uVar2);
      }
    }
  }
  return;
}

// JP: 0x003c3b40  LgtAttachFrame__10CBgElementFiP5Frame  =  CBgElement::LgtAttachFrame
void CBgElement::LgtAttachFrame(int this,int param_2,undefined4 param_3)

{
  if ((((this->u8_284 & 1) != 0) &&
      ((long)((ulong)this->u8_284 << 0x3e) < 0)) &&
     (-1 < *(int *)(this + param_2 * 4))) {
    *(undefined4 *)(this + param_2 * 4 + 0x80) = param_3;
  }
  return;
}
