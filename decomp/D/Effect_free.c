// decomp/D/Effect_free.c — cleaned Ghidra output (SLPM_602.19, Metrowerks MIPS), Shadow Hearts: Covenant JP demo.
// Field accesses are shown as this->T_off (T = u8/u16/u32/f32/i32/p, off = hex offset);
// JRing fields are named from the recovered struct. See notes/D/*.md for layouts.
// CAVEAT: when the base pointer is a float*/int*/short*, the number in `T_off` is an ELEMENT offset (byte offset = off*sizeof(elem)).
// `this` is the C++ this pointer (param_1); the Metrowerks ABI passes it in a0.

// JP: 0x0025fb40  __ct__Q211PutiTexture26@class$1573PutiTexture_cppFv  =  __ct__Q211PutiTexture26@class$1573PutiTexture_cppFv
int __ct__Q211PutiTexture26_class_1573PutiTexture_cppFv(int this)

{
  _QWD::_QWD(this);
  _QWD::_QWD(this + 0x10);
  return this;
}

// JP: 0x002a3320  CreateFpEffect__FiPv  =  CreateFpEffect
int CreateFpEffect(int this,float *param_2)

{
  long lVar1;
  undefined4 uStack_58;
  undefined4 uStack_54;
  
  uStack_54 = 0;
  if (this == 0xcc) {
    lVar1 = __nw(0x78);
    uStack_54 = 0;
    if (lVar1 != 0) {
      uStack_54 = FpTaki::FpTaki(lVar1);
    }
    FpTaki::Create(uStack_54,param_2);
  }
  else if (this == 0xcb) {
    if ((int)*param_2 == 1) {
      lVar1 = __nw(0x70);
      uStack_54 = 0;
      if (lVar1 != 0) {
        uStack_54 = FpFogMCES::FpFogMCES(lVar1);
      }
      FpFogMCES::Create(uStack_54,param_2);
    }
  }
  else if (this == 0xca) {
    lVar1 = __nw(0xc0);
    uStack_54 = 0;
    if (lVar1 != 0) {
      uStack_54 = FpBlackHole::FpBlackHole(lVar1);
    }
    FpBlackHole::Create(uStack_54,param_2);
  }
  else if (this == 0xc9) {
    lVar1 = __nw(0x100);
    uStack_54 = 0;
    if (lVar1 != 0) {
      uStack_54 = FpFunsui::FpFunsui(lVar1);
    }
    FpFunsui::Create(uStack_54,param_2);
  }
  else if (this == 200) {
    lVar1 = __nw(0xd0);
    uStack_54 = 0;
    if (lVar1 != 0) {
      uStack_54 = FpLenzFlare::FpLenzFlare(lVar1);
    }
    FpLenzFlare::Create(uStack_54,param_2);
  }
  else if (this == 5) {
    lVar1 = __nw(0xd0);
    uStack_54 = 0;
    if (lVar1 != 0) {
      uStack_54 = FpFog::FpFog(lVar1);
    }
    FpFog::Create(uStack_54,param_2);
  }
  else if (this == 4) {
    lVar1 = __nw(0x100);
    uStack_54 = 0;
    if (lVar1 != 0) {
      uStack_54 = FpSmoke::FpSmoke(lVar1);
    }
    FpSmoke::Create(uStack_54,param_2);
  }
  else if (this == 3) {
    lVar1 = __nw(0x70);
    uStack_54 = 0;
    if (lVar1 != 0) {
      uStack_54 = FpFlare::FpFlare(lVar1);
    }
    FpFlare::Create(uStack_54,param_2);
  }
  else if (this == 2) {
    uStack_58 = __nw(0xc0);
    if (uStack_58 != 0) {
      uStack_58 = FpCandle::FpCandle(uStack_58);
    }
    FpCandle::Create(uStack_58,param_2);
    uStack_54 = uStack_58;
  }
  else if (this == 1) {
    uStack_54 = __nw(0xc0);
    if (uStack_54 != 0) {
      uStack_54 = FpTorch::FpTorch(uStack_54);
    }
    FpTorch::Create(uStack_54,param_2);
  }
  return uStack_54;
}

// JP: 0x002e0fc0  RotTransVector  =  RotTransVector
void RotTransVector(undefined1 (*this) [16],undefined1 (*param_2) [16],undefined1 (*param_3) [16]
                   ,int param_4)

{
  undefined1 auVar1 [16];
  undefined1 auVar2 [16];
  undefined1 auVar3 [16];
  undefined1 auVar4 [16];
  undefined1 auVar5 [16];
  undefined1 auVar6 [16];
  
  auVar3 = _lqc2(*param_3);
  auVar4 = _lqc2(param_3[1]);
  auVar5 = _lqc2(param_3[2]);
  auVar6 = _lqc2(param_3[3]);
  auVar1 = _lqc2(*param_2);
  do {
    _vmulabc(auVar3,auVar1);
    _vmaddabc(auVar4,auVar1);
    _vmaddabc(auVar5,auVar1);
    auVar2 = _vmaddbc(auVar6,auVar1);
    param_2 = param_2 + 1;
    param_4 = param_4 + -1;
    auVar1 = _lqc2(*param_2);
    auVar2 = _sqc2(auVar2);
    *this = auVar2;
    this = this + 1;
  } while (0 < param_4);
  return;
}

// JP: 0x002e1010  AreaHitCheck  =  AreaHitCheck
undefined4 AreaHitCheck(float this,float param_2,short param_3,short param_4,char param_5)

{
  undefined4 uVar1;
  float fVar2;
  float fVar3;
  float fStack_58;
  float fStack_54;
  
  if (360.0 <= (float)(int)param_4) {
    uVar1 = 1;
  }
  else {
    for (fStack_54 = this - (float)(int)param_3; fStack_54 < 0.0; fStack_54 = fStack_54 + 360.0)
    {
    }
    for (; 360.0 <= fStack_54; fStack_54 = fStack_54 - 360.0) {
    }
    if (fStack_54 <= (float)(int)param_4) {
      uVar1 = 1;
    }
    else if (this == param_2) {
      uVar1 = 0;
    }
    else {
      for (fStack_58 = param_2 - (float)(int)param_3; fStack_58 < 0.0; fStack_58 = fStack_58 + 360.0
          ) {
      }
      for (; 360.0 <= fStack_58; fStack_58 = fStack_58 - 360.0) {
      }
      if (fStack_58 <= (float)(int)param_4) {
        if (param_5 == '\x01') {
          return 1;
        }
        fVar2 = 360.0 - fStack_54;
        fVar3 = fStack_54 - (float)(int)param_4;
        fStack_54 = fVar2;
        if (fVar3 <= fVar2) {
          fStack_54 = fVar3;
        }
        fVar2 = (float)(int)param_4 - fStack_58;
        if (fStack_58 <= (float)(int)param_4 - fStack_58) {
          fVar2 = fStack_58;
        }
        fStack_58 = fVar2;
        if (fStack_54 < fStack_58) {
          return 1;
        }
      }
      for (fStack_54 = this - param_2; fStack_54 < 180.0; fStack_54 = fStack_54 + 360.0) {
      }
      for (; 180.0 < fStack_54; fStack_54 = fStack_54 - 360.0) {
      }
      if (0.0 < fStack_54) {
        for (fStack_58 = this - (float)(int)param_3; fStack_58 < 0.0;
            fStack_58 = fStack_58 + 360.0) {
        }
        for (; 360.0 <= fStack_58; fStack_58 = fStack_58 - 360.0) {
        }
        if (fStack_58 - fStack_54 < 0.0) {
          return 1;
        }
      }
      else {
        for (fStack_58 = param_2 - (float)(int)param_3; fStack_58 < 0.0;
            fStack_58 = fStack_58 + 360.0) {
        }
        for (; 360.0 <= fStack_58; fStack_58 = fStack_58 - 360.0) {
        }
        if (fStack_58 + fStack_54 < 0.0) {
          return 1;
        }
      }
      uVar1 = 0;
    }
  }
  return uVar1;
}

// JP: 0x002e1510  EasyAreaHitCheck  =  EasyAreaHitCheck
undefined4 EasyAreaHitCheck(float this,short param_2,short param_3)

{
  undefined4 uVar1;
  undefined4 uStack_34;
  
  if (360.0 <= (float)(int)param_3) {
    uVar1 = 1;
  }
  else {
    for (uStack_34 = this - (float)(int)param_2; uStack_34 < 0.0; uStack_34 = uStack_34 + 360.0)
    {
    }
    for (; 360.0 <= uStack_34; uStack_34 = uStack_34 - 360.0) {
    }
    if (uStack_34 <= (float)(int)param_3) {
      uVar1 = 1;
    }
    else {
      uVar1 = 0;
    }
  }
  return uVar1;
}

// JP: 0x002e1630  HitStopAngle  =  HitStopAngle
float HitStopAngle(float this,int param_2)

{
  char cVar1;
  short sVar2;
  int unaff_s0_lo;
  int unaff_s1_lo;
  float fVar3;
  undefined4 uStack_24;
  
  cVar1 = param_2->i8_2;
  if (cVar1 == '\x02') {
    if (param_2->i16_1a == 0x78) {
      sVar2 = param_2->i16_4 + param_2->i16_6;
      unaff_s1_lo = (int)sVar2;
      unaff_s0_lo = (int)(short)(sVar2 - param_2->i16_8);
    }
    else if (param_2->i16_1a == 100) {
      sVar2 = (param_2->i16_4 + param_2->i16_6) - param_2->i16_8;
      unaff_s1_lo = (int)sVar2;
      unaff_s0_lo = (int)(short)(sVar2 - param_2->i16_a);
    }
    else {
      unaff_s0_lo = (int)param_2->i16_4;
      unaff_s1_lo = (int)(short)(((param_2->i16_4 + param_2->i16_6) -
                                 param_2->i16_8) - param_2->i16_a);
    }
  }
  else if (cVar1 == '\x01') {
    if (param_2->i16_1a == 0x78) {
      sVar2 = param_2->i16_4 + param_2->i16_6;
      unaff_s1_lo = (int)sVar2;
      unaff_s0_lo = (int)(short)(sVar2 - param_2->i16_8);
    }
    else {
      unaff_s0_lo = (int)param_2->i16_4;
      unaff_s1_lo = (int)(short)((param_2->i16_4 + param_2->i16_6) -
                                param_2->i16_8);
    }
  }
  else if (cVar1 == '\0') {
    unaff_s0_lo = (int)param_2->i16_4;
    unaff_s1_lo = (int)(short)(param_2->i16_4 + param_2->i16_6);
  }
  sVar2 = (short)unaff_s1_lo - (short)unaff_s0_lo;
  if (sVar2 < 0x168) {
    fVar3 = (360.0 - (float)(int)sVar2) / 2.0;
    for (uStack_24 = this - (float)unaff_s0_lo; uStack_24 < -fVar3; uStack_24 = uStack_24 + 360.0
        ) {
    }
    for (; (float)(int)sVar2 + fVar3 < uStack_24; uStack_24 = uStack_24 - 360.0) {
    }
    if (uStack_24 < 0.0) {
      this = (float)unaff_s0_lo;
    }
    else if ((float)(int)sVar2 < uStack_24) {
      this = (float)unaff_s1_lo;
    }
  }
  return this;
}

// JP: 0x002fdbd0  __as__Q23VEC4OpdSFRCQ23VEC4OpdS  =  __as__Q23VEC4OpdSFRCQ23VEC4OpdS
undefined4 * __as__Q23VEC4OpdSFRCQ23VEC4OpdS(undefined4 *this,undefined4 *param_2)

{
  *this = *param_2;
  return this;
}

// JP: 0x002fe060  InitSysFunc__Fv  =  InitSysFunc
void InitSysFunc(void)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  
  if (funcReader == 0) {
    for (iVar3 = 0; iVar3 < 0x83; iVar3 = iVar3 + 1) {
      *(undefined4 *)(&funcHash + iVar3 * 4) = 0;
    }
    for (iVar3 = 0; iVar3 < 0x10d; iVar3 = iVar3 + 1) {
      iVar1 = *(int *)(FuncTbl + iVar3 * 0xc);
      puVar2 = (undefined4 *)__nw(0x14);
      *puVar2 = *(undefined4 *)(FuncTbl + iVar3 * 0xc);
      puVar2[1] = *(undefined4 *)(FuncTbl + iVar3 * 0xc + 4);
      puVar2[2] = 0;
      puVar2->u8_3 = FuncTbl[iVar3 * 0xc + 8];
      puVar2[4] = *(undefined4 *)(&funcHash + (iVar1 % 0x83) * 4);
      *(undefined4 **)(&funcHash + (iVar1 % 0x83) * 4) = puVar2;
    }
  }
  funcReader = funcReader + 1;
  return;
}

// JP: 0x002fe1d0  GetSysCallFunc__Fi  =  GetSysCallFunc
int * GetSysCallFunc(int this)

{
  int *piVar1;
  
  piVar1 = *(int **)(&funcHash + (this % 0x83) * 4);
  while( true ) {
    if (piVar1 == (int *)0x0) {
      return (int *)0x0;
    }
    if (*piVar1 == this) break;
    piVar1 = (int *)piVar1[4];
  }
  return piVar1;
}

// JP: 0x002fe270  CleanSysFunc__Fv  =  CleanSysFunc
void CleanSysFunc(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  funcReader = funcReader + -1;
  if (funcReader < 1) {
    for (iVar3 = 0; iVar3 < 0x83; iVar3 = iVar3 + 1) {
      iVar2 = *(int *)(&funcHash + iVar3 * 4);
      while (iVar2 != 0) {
        iVar1 = iVar2->i32_10;
        __dl(iVar2);
        iVar2 = iVar1;
      }
      *(undefined4 *)(&funcHash + iVar3 * 4) = 0;
    }
  }
  return;
}

// JP: 0x002fe340  GetBekijo__FUi  =  GetBekijo
int GetBekijo(uint this)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = 0;
  for (uVar2 = 1; uVar2 < this; uVar2 = uVar2 << 1) {
    iVar1 = iVar1 + 1;
  }
  return iVar1;
}

// JP: 0x002fe3f0  __ct__Q29vpTexture24@class$1573vpTexture_cppFv  =  __ct__Q29vpTexture24@class$1573vpTexture_cppFv
int __ct__Q29vpTexture24_class_1573vpTexture_cppFv(int this)

{
  _QWD::_QWD(this);
  _QWD::_QWD(this + 0x10);
  return this;
}

// JP: 0x002ffc10  cbEndCallback__FPvi  =  cbEndCallback
void cbEndCallback(undefined4 this,undefined4 param_2)

{
  EffectCore::HitEnd(this,param_2);
  return;
}

// JP: 0x0030aee0  Init__Q27HitShot22@class$1793HitShot_cppFv  =  Init__Q27HitShot22@class$1793HitShot_cppFv
void Init__Q27HitShot22_class_1793HitShot_cppFv(byte *this)

{
  *this = *this & 0xfc;
  *this = *this & 0xfb | 4;
  return;
}

// JP: 0x00322250  Init__Q211EffectBarin23@class$1589EffBarin_cppFv  =  Init__Q211EffectBarin23@class$1589EffBarin_cppFv
void Init__Q211EffectBarin23_class_1589EffBarin_cppFv(byte *this)

{
  *this = *this & 0xfe;
  return;
}

// JP: 0x00404080  __sinit_PutiEffect.cpp  =  __sinit_PutiEffect.cpp
void __sinit_PutiEffect_cpp(void)

{
  Matrix::Matrix(0x4213c0);
  return;
}
