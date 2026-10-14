// decomp/D/Effect.c — cleaned Ghidra output (SLPM_602.19, Metrowerks MIPS), Shadow Hearts: Covenant JP demo.
// Field accesses are shown as this->T_off (T = u8/u16/u32/f32/i32/p, off = hex offset);
// JRing fields are named from the recovered struct. See notes/D/*.md for layouts.
// CAVEAT: when the base pointer is a float*/int*/short*, the number in `T_off` is an ELEMENT offset (byte offset = off*sizeof(elem)).
// `this` is the C++ this pointer (param_1); the Metrowerks ABI passes it in a0.

// JP: 0x002ff0f0  __ct__6EffectFPFPvi_vPvi  =  Effect::Effect
int Effect::Effect(int this,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  CPolObj::CPolObj(this);
  *(undefined1 **)(this + 0x14) = Effect::__vt;
  _rgba32::_rgba32(this + 0x44);
  this->u32_20 = 0;
  this->u32_28 = 0;
  this->u32_2c = param_2;
  this->u32_30 = param_3;
  this->u32_34 = param_4;
  this->u32_38 = 0;
  this->u32_3c = 0;
  this->u32_40 = 0;
  InitSysFunc();
  this->u32_18 = 1;
  this->u32_1c = 0;
  return this;
}

// JP: 0x002ff1b0  __dt__6EffectFv  =  Effect::~Effect
int Effect::~Effect(int this,short param_2)

{
  int iVar1;
  
  if (this != 0) {
    *(undefined1 **)(this + 0x14) = Effect::__vt;
    Effect::DelayDeleteCore(this);
    CleanSysFunc();
    if (this->i32_28 != 0) {
      iVar1 = this->i32_28;
      if (iVar1 != 0) {
        (**(code **)(iVar1->i32_14 + 8))(iVar1,1);
      }
      this->u32_28 = 0;
    }
    CPolObj::~CPolObj(this,0);
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}

// JP: 0x002ff280  SetReplaceCallback__6EffectFPFP6EffectPvi_vPvi  =  Effect::SetReplaceCallback
void Effect::SetReplaceCallback
               (int this,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  this->u32_38 = param_2;
  this->u32_3c = param_3;
  this->u32_40 = param_4;
  return;
}

// JP: 0x002ff2d0  DelayDeleteCore__6EffectFv  =  Effect::DelayDeleteCore
void Effect::DelayDeleteCore(int this)

{
  Effect::Stop(this);
  if (this->i32_20 != 0) {
    EffectCore::DelayDeleteCore(this->u32_20);
  }
  this->u32_20 = 0;
  return;
}

// JP: 0x002ff320  Create__6EffectFP9BufMemory  =  Effect::Create
undefined4 Effect::Create(int this,undefined4 param_2)

{
  long lVar1;
  undefined8 uVar2;
  
  this->u32_24 = param_2;
  lVar1 = __nw(0x610);
  uVar2 = 0;
  if (lVar1 != 0) {
    uVar2 = EffectCore::EffectCore(lVar1,this);
  }
  EffectCore::Create(uVar2,param_2);
  if (this->i32_20 == 0) {
    this->i32_20 = (int)uVar2;
  }
  else {
    CList::Add(this->u32_20,uVar2);
  }
  (**(code **)(this->i32_14 + 0x10))(this,uVar2);
  return 1;
}

// JP: 0x002ff3f0  OnCreate__6EffectFP10EffectCore  =  Effect::OnCreate
void Effect::OnCreate(void)

{
  return;
}

// JP: 0x002ff400  Run__6EffectFv  =  Effect::Run
void Effect::Run(int this)

{
  long lVar1;
  
  this->u8_44 = CApp::camera->u8_180;
  this->u8_45 = CApp::camera->u8_181;
  this->u8_46 = CApp::camera->u8_182;
  this->u8_47 = CApp::camera->u8_183;
  lVar1 = CPoller::Find(CApp::app + 0x48,this);
  if (lVar1 == 0) {
    CPoller::Entry(CApp::app + 0x48,this,0x80,0);
  }
  EffectCore::Run(this->u32_20);
  this->u32_1c = 1;
  return;
}

// JP: 0x002ff4c0  Stop__6EffectFv  =  Effect::Stop
void Effect::Stop(int this)

{
  GsxCamera::SetBgColor(CApp::camera,this + 0x44);
  CPoller::Dispose(CApp::app + 0x48,this);
  return;
}

// JP: 0x002ff570  Continue__6EffectFv  =  Effect::Continue
void Effect::Continue(int this)

{
  long lVar1;
  
  if ((this->i32_1c != 0) &&
     (lVar1 = CPoller::Find(CApp::app + 0x48,this), lVar1 == 0)) {
    CPoller::Entry(CApp::app + 0x48,this,0x80,0);
  }
  return;
}

// JP: 0x002ff5e0  PollDelete__6EffectFv  =  Effect::PollDelete
void Effect::PollDelete(int this)

{
  this->u32_18 = 2;
  return;
}

// JP: 0x002ff600  Polling__6EffectFv  =  Effect::Polling
undefined4 Effect::Polling(int this)

{
  undefined4 uVar1;
  long lVar2;
  
  if (this->i32_18 == 0) {
    EffectCore::CalcMatrix(this->u32_20);
    uVar1 = 0;
  }
  else {
    lVar2 = EffectCore::Continue(this->u32_20);
    if ((lVar2 == 0) && (this->i32_2c != 0)) {
      (**(code **)(this + 0x2c))(this->u32_30,this->u32_34)
      ;
      this->u32_2c = 0;
      this->u32_30 = 0;
      this->u32_34 = 0;
    }
    if (this->i32_18 == 2) {
      CPolObj::SetAutoDelete(this,1);
      uVar1 = 1;
    }
    else {
      uVar1 = 0;
    }
  }
  return uVar1;
}

// JP: 0x002ff710  SetGenModel__6EffectFiP11tagModelSet  =  Effect::SetGenModel
void Effect::SetGenModel(int this,int param_2,undefined4 param_3)

{
  int iVar1;
  
  *(int *)(this->i32_20 + 0xdc) = param_2;
  *(undefined4 *)(this->i32_20 + 0x1c) = param_3;
  for (iVar1 = 0; iVar1 < param_2; iVar1 = iVar1 + 1) {
    tagModelSet::Init(*(int *)(this->i32_20 + 0x1c) + iVar1 * 0x14);
  }
  return;
}

// JP: 0x002ff810  SetTarModel__6EffectFiP11tagModelSet  =  Effect::SetTarModel
void Effect::SetTarModel(int this,int param_2,undefined4 param_3)

{
  int iVar1;
  
  *(int *)(this->i32_20 + 0xd8) = param_2;
  *(undefined4 *)(this->i32_20 + 0x20) = param_3;
  for (iVar1 = 0; iVar1 < param_2; iVar1 = iVar1 + 1) {
    tagModelSet::Init(*(int *)(this->i32_20 + 0x20) + iVar1 * 0x14);
  }
  return;
}

// JP: 0x002ff8b0  SetGenPos__6EffectFiP7FVector  =  Effect::SetGenPos
void Effect::SetGenPos(int this,int param_2,int param_3)

{
  undefined4 *puVar1;
  int iVar2;
  
  *(int *)(this->i32_20 + 0xdc) = param_2;
  for (iVar2 = 0; iVar2 < param_2; iVar2 = iVar2 + 1) {
    FVector::__as(this->i32_20 + iVar2 * 0x10 + 0x30,param_3 + iVar2 * 0x10)
    ;
    puVar1 = (undefined4 *)FVector::vw(this->i32_20 + iVar2 * 0x10 + 0x30);
    *puVar1 = 0x3f800000;
  }
  return;
}

// JP: 0x002ff970  SetTarPos__6EffectFiP7FVector  =  Effect::SetTarPos
void Effect::SetTarPos(int this,int param_2,int param_3)

{
  undefined4 *puVar1;
  int iVar2;
  
  *(int *)(this->i32_20 + 0xd8) = param_2;
  for (iVar2 = 0; iVar2 < param_2; iVar2 = iVar2 + 1) {
    FVector::__as(this->i32_20 + iVar2 * 0x10 + 0x80,param_3 + iVar2 * 0x10)
    ;
    puVar1 = (undefined4 *)FVector::vw(this->i32_20 + iVar2 * 0x10 + 0x80);
    *puVar1 = 0x3f800000;
  }
  return;
}

// JP: 0x002ffa30  EffectNext__6EffectFv  =  Effect::EffectNext
void Effect::EffectNext(int this)

{
  int iVar1;
  
  for (iVar1 = *(int *)(this->i32_20 + 0x10); iVar1 != 0;
      iVar1 = CList::GetNext(iVar1)) {
    iVar1->u8_24c = 0;
  }
  return;
}

// JP: 0x002ffa90  Pause__6EffectFb  =  Effect::Pause
void Effect::Pause(int this,char param_2)

{
  this->u32_18 = (uint)(param_2 == '\0');
  return;
}

// JP: 0x002ffae0  Duplicate__6EffectFP6Effect  =  Effect::Duplicate
void Effect::Duplicate(int this,int param_2)

{
  this->u32_2c = param_2->u32_2c;
  this->u32_30 = param_2->u32_30;
  this->u32_34 = param_2->u32_34;
  _rgba32::__as(this + 0x44,param_2 + 0x44);
  EffectCore::Duplicate
            (this->u32_20,param_2->u32_20);
  return;
}

// JP: 0x002ffbc0  SetEndCallback__6EffectFPFPvi_vPvi  =  Effect::SetEndCallback
void Effect::SetEndCallback
               (int this,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  this->u32_2c = param_2;
  this->u32_30 = param_3;
  this->u32_34 = param_4;
  return;
}
