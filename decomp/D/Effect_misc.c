// decomp/D/Effect_misc.c — cleaned Ghidra output (SLPM_602.19, Metrowerks MIPS), Shadow Hearts: Covenant JP demo.
// Field accesses are shown as this->T_off (T = u8/u16/u32/f32/i32/p, off = hex offset);
// JRing fields are named from the recovered struct. See notes/D/*.md for layouts.
// CAVEAT: when the base pointer is a float*/int*/short*, the number in `T_off` is an ELEMENT offset (byte offset = off*sizeof(elem)).
// `this` is the C++ this pointer (param_1); the Metrowerks ABI passes it in a0.

// JP: 0x0025e710  __dt__15DelayPutiObjectFv  =  DelayPutiObject::~DelayPutiObject
int DelayPutiObject::~DelayPutiObject(int this,short param_2)

{
  int iVar1;
  
  if (this != 0) {
    if (this->i32_8 != 0) {
      iVar1 = this->i32_8;
      if (iVar1 != 0) {
        (**(code **)(iVar1->i32_1e4 + 0x34))(iVar1,1);
      }
      this->u32_8 = 0;
    }
    CList::~CList(this,0);
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}

// JP: 0x002f0d10  __ct__9CrackInfoFv  =  CrackInfo::CrackInfo
int CrackInfo::CrackInfo(int this)

{
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  
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
  return this;
}

// JP: 0x002fc240  Init__17tagEffectLoadWaitFv  =  tagEffectLoadWait::Init
void tagEffectLoadWait::Init(undefined4 *this)

{
  *this = 0;
  return;
}

// JP: 0x002ff7b0  Init__11tagModelSetFv  =  tagModelSet::Init
void tagModelSet::Init(int this)

{
  tagHitParam::Init(this + 0xc);
  return;
}

// JP: 0x002ff7e0  Init__11tagHitParamFv  =  tagHitParam::Init
void * tagHitParam::Init(void *this)

{
  void *pvVar1;
  
  pvVar1 = memset(this,0,8);
  return pvVar1;
}

// JP: 0x002fffc0  __dt__12EffProcParamFv  =  EffProcParam::~EffProcParam
int EffProcParam::~EffProcParam(int this,short param_2)

{
  if ((this != 0) && (0 < param_2)) {
    __dl(this);
  }
  return this;
}

// JP: 0x00300020  Init__8_VibInfoFv  =  _VibInfo::Init
void _VibInfo::Init(undefined4 *this)

{
  *this = 0;
  this[1] = 0;
  return;
}

// JP: 0x00300050  Init__13tagFpPrimInfoFv  =  tagFpPrimInfo::Init
void tagFpPrimInfo::Init(undefined4 *this)

{
  *this = 0;
  this[1] = 0;
  return;
}

// JP: 0x00300080  Init__12tagEffSeCtrlFv  =  tagEffSeCtrl::Init
void tagEffSeCtrl::Init(byte *this)

{
  *this = *this & 0xfe;
  *this = *this & 0xfb;
  *this = *this & 0xf7;
  *this = *this & 0xfd;
  this[4] = 0;
  this[5] = 0;
  this[6] = 0;
  this[7] = 0;
  this[8] = 0xff;
  this[9] = 0xff;
  this[10] = 0xff;
  this[0xb] = 0xff;
  return;
}

// JP: 0x00300130  Init__15tagEffCoreFlagsFv  =  tagEffCoreFlags::Init
void tagEffCoreFlags::Init(byte *this)

{
  *this = *this & 0xfc;
  return;
}

// JP: 0x00301af0  __ct__17tagEFCMMotionDataFv  =  tagEFCMMotionData::tagEFCMMotionData
int tagEFCMMotionData::tagEFCMMotionData(int this)

{
  FVector::FVector(this);
  FVector::FVector(this + 0x10);
  return this;
}

// JP: 0x00301b30  __ct__17tagEFLTMotionDataFv  =  tagEFLTMotionData::tagEFLTMotionData
int tagEFLTMotionData::tagEFLTMotionData(int this)

{
  FVector::FVector(this);
  FVector::FVector(this + 0x10);
  FVector::FVector(this + 0x20);
  return this;
}

// JP: 0x00304cb0  __as__13tagFpPrimInfoFRC13tagFpPrimInfo  =  tagFpPrimInfo::__as
undefined4 * tagFpPrimInfo::__as(undefined4 *this,undefined4 *param_2)

{
  *this = *param_2;
  this[1] = param_2[1];
  return this;
}

// JP: 0x00304cf0  __as__10tagSaveFogFRC10tagSaveFog  =  tagSaveFog::__as
undefined4 * tagSaveFog::__as(undefined4 *this,undefined4 *param_2)

{
  *this = *param_2;
  this[1] = param_2[1];
  this->u64_2 = param_2->u64_2;
  return this;
}

// JP: 0x00304d40  __as__13MotionAddInfoFRC13MotionAddInfo  =  MotionAddInfo::__as
undefined1 * MotionAddInfo::__as(undefined1 *this,undefined1 *param_2)

{
  *this = *param_2;
  this[1] = param_2[1];
  this[2] = param_2[2];
  this[3] = param_2[3];
  this->u32_4 = param_2->u32_4;
  return this;
}

// JP: 0x00304db0  __as__12EffProcParamFRC12EffProcParam  =  EffProcParam::__as
undefined4 * EffProcParam::__as(undefined4 *this,undefined4 *param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  
  *this = *param_2;
  puVar5 = param_2 + 1;
  puVar4 = this + 1;
  iVar3 = 10;
  do {
    uVar1 = *puVar5;
    uVar2 = puVar5[1];
    puVar5 = puVar5 + 2;
    iVar3 = iVar3 + -1;
    *puVar4 = uVar1;
    puVar4[1] = uVar2;
    puVar4 = puVar4 + 2;
  } while (0 < iVar3);
  param_2 = param_2 + 0x15;
  puVar4 = this + 0x15;
  iVar3 = 10;
  do {
    uVar1 = *param_2;
    uVar2 = param_2[1];
    param_2 = param_2 + 2;
    iVar3 = iVar3 + -1;
    *puVar4 = uVar1;
    puVar4[1] = uVar2;
    puVar4 = puVar4 + 2;
  } while (0 < iVar3);
  return this;
}

// JP: 0x00304f50  __ct__12EffProcParamFv  =  EffProcParam::EffProcParam
undefined4 * EffProcParam::EffProcParam(undefined4 *this)

{
  int iVar1;
  
  *this = 0;
  for (iVar1 = 0; iVar1 < 0x14; iVar1 = iVar1 + 1) {
    this[iVar1 + 0x15] = 0;
    this[iVar1 + 1] = 0;
  }
  return this;
}

// JP: 0x00304fc0  AddHandle__12EffProcParamFiUiUi  =  EffProcParam::AddHandle
void EffProcParam::AddHandle(int *this,int param_2,int param_3,int param_4)

{
  this[param_2 + 0x15] = param_4;
  this[param_2 + 1] = param_3;
  *this = *this + 1;
  return;
}

// JP: 0x0030a7c0  __as__17tagEFCMMotionDataFRC17tagEFCMMotionData  =  tagEFCMMotionData::__as
int tagEFCMMotionData::__as(int this,int param_2)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  undefined1 *puVar4;
  undefined1 *puVar5;
  
  FVector::__as(this,param_2);
  FVector::__as(this + 0x10,param_2 + 0x10);
  this->u32_20 = param_2->u32_20;
  this->u16_24 = param_2->u16_24;
  this->u16_26 = param_2->u16_26;
  this->u32_28 = param_2->u32_28;
  this->u32_2c = param_2->u32_2c;
  puVar5 = (undefined1 *)(param_2 + 0x30);
  puVar4 = (undefined1 *)(this + 0x30);
  iVar3 = 8;
  do {
    uVar1 = *puVar5;
    uVar2 = puVar5[1];
    puVar5 = puVar5 + 2;
    iVar3 = iVar3 + -1;
    *puVar4 = uVar1;
    puVar4[1] = uVar2;
    puVar4 = puVar4 + 2;
  } while (0 < iVar3);
  return this;
}

// JP: 0x00310fc0  GetCount__12EffProcParamFv  =  EffProcParam::GetCount
undefined4 EffProcParam::GetCount(undefined4 *this)

{
  return *this;
}

// JP: 0x003198b0  __as__17tagEFLTMotionDataFRC17tagEFLTMotionData  =  tagEFLTMotionData::__as
int tagEFLTMotionData::__as(int this,int param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  FVector::__as(this,param_2);
  FVector::__as(this + 0x10,param_2 + 0x10);
  FVector::__as(this + 0x20,param_2 + 0x20);
  this->u32_30 = param_2->u32_30;
  uVar1 = param_2->u32_38;
  uVar2 = param_2->u32_3c;
  this->u32_34 = param_2->u32_34;
  this->u32_38 = uVar1;
  this->u32_3c = uVar2;
  return this;
}

// JP: 0x0031a5e0  IsLoaded__12tagEffSeCtrlFv  =  tagEffSeCtrl::IsLoaded
bool tagEffSeCtrl::IsLoaded(byte *this)

{
  return (long)((ulong)*this << 0x3e) < 0;
}
