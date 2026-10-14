// decomp/D/EffectCore.c — cleaned Ghidra output (SLPM_602.19, Metrowerks MIPS), Shadow Hearts: Covenant JP demo.
// Field accesses are shown as this->T_off (T = u8/u16/u32/f32/i32/p, off = hex offset);
// JRing fields are named from the recovered struct. See notes/D/*.md for layouts.
// CAVEAT: when the base pointer is a float*/int*/short*, the number in `T_off` is an ELEMENT offset (byte offset = off*sizeof(elem)).
// `this` is the C++ this pointer (param_1); the Metrowerks ABI passes it in a0.

// JP: 0x002ffc50  __ct__10EffectCoreFP6Effect  =  EffectCore::EffectCore
int EffectCore::EffectCore(int this,undefined4 param_2)

{
  int iVar1;
  
  DelayDeleteObject::DelayDeleteObject(this);
  *(undefined1 **)(this + 8) = EffectCore::__vt;
  iVar1 = this + 0x30;
  do {
    FVector::FVector(iVar1);
    iVar1 = iVar1 + 0x10;
  } while (iVar1 != this + 0x80);
  iVar1 = this + 0x80;
  do {
    FVector::FVector(iVar1);
    iVar1 = iVar1 + 0x10;
  } while (iVar1 != this + 0xd0);
  EffProcParam::EffProcParam(this + 0xe4);
  this->u32_c = param_2;
  this->u32_d4 = 0;
  this->u32_10 = 0;
  this->u32_14 = 0;
  this->u32_18 = 0;
  this->u32_d0 = 0;
  this->u32_1c = 0;
  this->u32_20 = 0;
  this->u32_578 = 0;
  this->u32_600 = 0;
  this->u32_d8 = 0;
  this->u32_dc = 0;
  EffectCore::m_Fader = 0;
  tagEffCoreFlags::Init(this + 0xe0);
  this->u32_2a0 = 0;
  this->u32_36c = 0;
  this->u32_370 = 0;
  this->u32_438 = CApp::camera->u32_380;
  this->u32_43c = CApp::camera->u32_384;
  this->u64_440 = CApp::camera->u64_150;
  this->u32_194 = 0x3d088889;
  this->u32_190 = 0x3d088889;
  this->u32_18c = 0x3d088889;
  this->u32_188 = 0x3d088889;
  memset((void *)(this + 0x198),0,0xa0);
  memset((void *)(this + 0x238),0,0x40);
  memset((void *)(this + 0x278),0,0x28);
  memset((void *)(this + 0x2a4),0,0x28);
  memset((void *)(this + 0x2cc),0,0xa0);
  memset((void *)(this + 0x374),0,0x28);
  memset((void *)(this + 0x448),0,0xc);
  memset((void *)(this + 0x454),0,200);
  memset((void *)(this + 0x56c),0,0xc);
  memset((void *)(this + 0x51c),0,0x50);
  memset((void *)(this + 0x57c),0,0xc);
  for (iVar1 = 0; iVar1 < 10; iVar1 = iVar1 + 1) {
    tagEffSeCtrl::Init(this + iVar1 * 0xc + 0x39c);
  }
  for (iVar1 = 0; iVar1 < 10; iVar1 = iVar1 + 1) {
    tagFpPrimInfo::Init(this + iVar1 * 8 + 0x5b0);
  }
  for (iVar1 = 0; iVar1 < 5; iVar1 = iVar1 + 1) {
    _VibInfo::Init(this + iVar1 * 8 + 0x588);
  }
  EffectCore::InitSysSE(this);
  return this;
}

// JP: 0x00300160  __dt__10EffectCoreFv  =  EffectCore::~EffectCore
int EffectCore::~EffectCore(int this,short param_2)

{
  int iVar1;
  
  if (this != 0) {
    *(undefined1 **)(this + 8) = EffectCore::__vt;
    if (this->i32_10 != 0) {
      iVar1 = this->i32_10;
      if (iVar1 != 0) {
        (**(code **)(iVar1->i32_250 + 8))(iVar1,1);
      }
      this->u32_10 = 0;
    }
    if (this->i32_d0 != 0) {
      BufMemory::~BufMemory(this->u32_d0,1);
      this->u32_d0 = 0;
    }
    if (this->i32_d4 != 0) {
      BufMemory::~BufMemory(this->u32_d4,1);
      this->u32_d4 = 0;
    }
    if (this->i32_18 != 0) {
      iVar1 = this->i32_18;
      if (iVar1 != 0) {
        (**(code **)(iVar1->i32_10 + 8))(iVar1,1);
      }
      this->u32_18 = 0;
    }
    if (EffectCore::m_Fader != 0) {
      if (EffectCore::m_Fader != 0) {
        (**(code **)(EffectCore::m_Fader->i32_38 + 8))(EffectCore::m_Fader,1);
      }
      EffectCore::m_Fader = 0;
    }
    if (this->i32_36c != 0) {
      iVar1 = this->i32_36c;
      if (iVar1 != 0) {
        (**(code **)(iVar1->i32_38 + 8))(iVar1,1);
      }
      this->u32_36c = 0;
    }
    if (this->i32_370 != 0) {
      iVar1 = this->i32_370;
      if (iVar1 != 0) {
        (**(code **)(iVar1->i32_5c + 8))(iVar1,1);
      }
      this->u32_370 = 0;
    }
    EffProcParam::~EffProcParam(this + 0xe4,0xffffffffffffffff);
    DelayDeleteObject::~DelayDeleteObject(this,0);
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}

// JP: 0x003003b0  Cleanup__10EffectCoreFv  =  EffectCore::Cleanup
void EffectCore::Cleanup(int this)

{
  int iVar1;
  int iVar2;
  undefined8 uVar3;
  long lVar4;
  undefined8 uVar5;
  
  for (iVar2 = 0; iVar2 < 0x28; iVar2 = iVar2 + 1) {
    if (*(int *)(this + iVar2 * 4 + 0x198) != 0) {
      lVar4 = LevelsModel::isCreate(*(int *)(this + iVar2 * 4 + 0x198) + 0xbc);
      if (lVar4 != 0) {
        ShadowControl::releaseShadow
                  (ShadowControl::m_pOur,*(undefined4 *)(this + iVar2 * 4 + 0x198));
      }
      if (*(int *)(*(int *)(*(int *)(this + iVar2 * 4 + 0x198) + 0x30) + 0x1e0) != 0) {
        Frame::unChainModel
                  (*(undefined4 *)(*(int *)(*(int *)(this + iVar2 * 4 + 0x198) + 0x30) + 0x1e0));
      }
      World::ReleaseOT
                ((World *)&CApp::m_World,*(VIF1Prim **)(this + iVar2 * 4 + 0x198));
      (**(code **)(*(int *)(*(int *)(this + iVar2 * 4 + 0x198) + 0x1c) + 0xc))();
      *(undefined4 *)(this + iVar2 * 4 + 0x198) = 0;
    }
  }
  for (iVar2 = 0; iVar2 < 0x10; iVar2 = iVar2 + 1) {
    if (*(int *)(this + iVar2 * 4 + 0x238) != 0) {
      (**(code **)(*(int *)(*(int *)(this + iVar2 * 4 + 0x238) + 0x10) + 0x2c))();
      (**(code **)(*(int *)(*(int *)(this + iVar2 * 4 + 0x238) + 0x1c) + 0xc))();
      *(undefined4 *)(this + iVar2 * 4 + 0x238) = 0;
    }
  }
  for (iVar2 = 0; iVar2 < 10; iVar2 = iVar2 + 1) {
    if (*(int *)(this + iVar2 * 4 + 0x2a4) != 0) {
      World::ReleaseOT
                ((World *)&CApp::m_World,*(VIF1Prim **)(this + iVar2 * 4 + 0x2a4));
      (**(code **)(*(int *)(*(int *)(this + iVar2 * 4 + 0x2a4) + 0x1c) + 0xc))();
      *(undefined4 *)(this + iVar2 * 4 + 0x2a4) = 0;
    }
  }
  for (iVar2 = 0; iVar2 < 0x14; iVar2 = iVar2 + 1) {
    if (*(int *)(this + iVar2 * 8 + 0x2d0) != 0) {
      uVar5 = EffectCore::GetModel
                        (this,*(undefined1 *)(this + iVar2 * 8 + 0x2cc),
                         *(undefined1 *)(this + iVar2 * 8 + 0x2cd),0,0);
      Model::deleteMotion(uVar5,*(undefined4 *)(this + iVar2 * 8 + 0x2d0));
    }
  }
  for (iVar2 = 0; iVar2 < 10; iVar2 = iVar2 + 1) {
    if (*(int *)(this + iVar2 * 4 + 0x278) != 0) {
      iVar1 = *(int *)(this + iVar2 * 4 + 0x278);
      if (iVar1 != 0) {
        (**(code **)(iVar1->i32_f4 + 0x10))(iVar1,1);
      }
      *(undefined4 *)(this + iVar2 * 4 + 0x278) = 0;
    }
  }
  for (iVar2 = 0; iVar2 < 10; iVar2 = iVar2 + 1) {
    if (*(int *)(this + iVar2 * 4 + 0x374) != 0) {
      iVar1 = *(int *)(this + iVar2 * 4 + 0x374);
      if (iVar1 != 0) {
        (**(code **)(iVar1->i32_20 + 0x10))(iVar1,1);
      }
      *(undefined4 *)(this + iVar2 * 4 + 0x374) = 0;
    }
  }
  if (this->i32_14 != 0) {
    World::ReleaseOT((World *)&CApp::m_World,*(VIF1Prim **)(this + 0x14));
    (**(code **)(*(int *)(this->i32_14 + 0x1c) + 0xc))();
    this->u32_14 = 0;
  }
  for (iVar2 = 0; iVar2 < 10; iVar2 = iVar2 + 1) {
    if ((*(byte *)(this + iVar2 * 0xc + 0x39c) & 1) != 0) {
      uVar3 = Sdrv::ReleaseSDH(Sdrv::sys,*(undefined4 *)(this + iVar2 * 0xc + 0x3a0));
      lVar4 = __nw(0x38);
      uVar5 = 0;
      if (lVar4 != 0) {
        uVar5 = SdState::SdState
                          (lVar4,0,uVar3,0x31c490,*(undefined4 *)(this + iVar2 * 0xc + 0x3a0),0,0
                          );
      }
      SdState::AddState(uVar5);
    }
  }
  for (iVar2 = 0; iVar2 < 3; iVar2 = iVar2 + 1) {
    if (*(int *)(this + iVar2 * 4 + 0x448) != 0) {
      World::ReleaseOT
                ((World *)&CApp::m_World,*(VIF1Prim **)(this + iVar2 * 4 + 0x448));
      (**(code **)(*(int *)(*(int *)(this + iVar2 * 4 + 0x448) + 0x1c) + 0xc))();
      *(undefined4 *)(this + iVar2 * 4 + 0x448) = 0;
    }
  }
  for (iVar2 = 0; iVar2 < 0x32; iVar2 = iVar2 + 1) {
    if (*(int *)(this + iVar2 * 4 + 0x454) != 0) {
      World::ReleaseOT
                ((World *)&CApp::m_World,*(VIF1Prim **)(this + iVar2 * 4 + 0x454));
      (**(code **)(*(int *)(*(int *)(this + iVar2 * 4 + 0x454) + 0x1c) + 0xc))();
      *(undefined4 *)(this + iVar2 * 4 + 0x454) = 0;
    }
  }
  for (iVar2 = 0; iVar2 < 0x14; iVar2 = iVar2 + 1) {
    if ((*(int *)(this + iVar2 * 4 + 0x51c) != 0) && (*(int *)(this + iVar2 * 4 + 0x51c) != 0)
       ) {
      CPath::~CPath(*(undefined4 *)(this + iVar2 * 4 + 0x51c),1);
      *(undefined4 *)(this + iVar2 * 4 + 0x51c) = 0;
    }
  }
  for (iVar2 = 0; iVar2 < 3; iVar2 = iVar2 + 1) {
    if (*(int *)(this + iVar2 * 4 + 0x56c) != 0) {
      World::ReleaseOT
                ((World *)&CApp::m_World,*(VIF1Prim **)(this + iVar2 * 4 + 0x56c));
      (**(code **)(*(int *)(*(int *)(this + iVar2 * 4 + 0x56c) + 0x1c) + 0xc))();
      *(undefined4 *)(this + iVar2 * 4 + 0x56c) = 0;
    }
  }
  for (iVar2 = 0; iVar2 < 10; iVar2 = iVar2 + 1) {
    if (*(int *)(this + iVar2 * 8 + 0x5b0) != 0) {
      PutiPrim::Delete(*(undefined4 *)(this + iVar2 * 8 + 0x5b0));
      tagFpPrimInfo::Init(this + iVar2 * 8 + 0x5b0);
    }
  }
  for (iVar2 = 0; iVar2 < 3; iVar2 = iVar2 + 1) {
    if (*(int *)(this + iVar2 * 4 + 0x57c) != 0) {
      World::ReleaseOT
                ((World *)&CApp::m_World,*(VIF1Prim **)(this + iVar2 * 4 + 0x57c));
      (**(code **)(*(int *)(*(int *)(this + iVar2 * 4 + 0x57c) + 0x1c) + 0xc))();
      *(undefined4 *)(this + iVar2 * 4 + 0x57c) = 0;
    }
  }
  for (iVar2 = 0; iVar2 < 5; iVar2 = iVar2 + 1) {
    if (*(int *)(this + iVar2 * 8 + 0x588) != 0) {
      CVibe::~CVibe(*(undefined4 *)(this + iVar2 * 8 + 0x588),1);
      *(undefined4 *)(this + iVar2 * 8 + 0x588) = 0;
    }
  }
  if (this->i32_578 != 0) {
    World::ReleaseOT((World *)&CApp::m_World,*(VIF1Prim **)(this + 0x578));
    (**(code **)(*(int *)(this->i32_578 + 0x1c) + 0xc))();
    this->u32_578 = 0;
  }
  if (this->i32_36c != 0) {
    iVar2 = this->i32_36c;
    if (iVar2 != 0) {
      (**(code **)(iVar2->i32_38 + 8))(iVar2,1);
    }
    this->u32_36c = 0;
  }
  if (this->i32_370 != 0) {
    iVar2 = this->i32_370;
    if (iVar2 != 0) {
      (**(code **)(iVar2->i32_5c + 8))(iVar2,1);
    }
    this->u32_370 = 0;
  }
  if (this->i32_600 != 0) {
    StreamBGM::Stop(this->u32_600,0,0);
    StreamBGM::Delete(this->u32_600);
    this->u32_600 = 0;
  }
  GsxCamera::SetFogParam
            (this->u32_438,this->u32_43c,CApp::camera);
  CApp::camera->u64_150 = this->u64_440;
  return;
}

// JP: 0x00300ea0  DelayDeleteCore__10EffectCoreFv  =  EffectCore::DelayDeleteCore
void EffectCore::DelayDeleteCore(int this)

{
  EffectCore::Cleanup(this);
  (**(code **)(this->i32_8 + 0xc))();
  return;
}

// JP: 0x00300ee0  Create__10EffectCoreFP9BufMemory  =  EffectCore::Create
undefined4 EffectCore::Create(int this,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  long lVar4;
  char *pcVar5;
  int iVar6;
  
  this->u32_d0 = param_2;
  lVar4 = __nw(0x130);
  uVar2 = 0;
  if (lVar4 != 0) {
    uVar2 = PolPacket::PolPacket(lVar4);
  }
  this->u32_14 = uVar2;
  World::AddOT((World *)&CApp::m_World,9,*(VIF1Prim **)(this + 0x14));
  iVar3 = BufMemory::getBuffer(this->u32_d0);
  pcVar5 = (char *)(iVar3 + 0x10);
  for (iVar6 = 0; iVar6 < (int)(uint)iVar3->u16_4; iVar6 = iVar6 + 1) {
    cVar1 = *pcVar5;
    if (cVar1 != 'M') {
      if (cVar1 == 'T') {
        EffectCore::CreateTexture(this,iVar3 + pcVar5->i32_4);
      }
      else if (cVar1 == 'C') {
        EffectCore::CreateVec(this,iVar3 + pcVar5->i32_4);
      }
    }
    pcVar5 = pcVar5 + 8;
  }
  EffectCore::Run(this);
  return 1;
}

// JP: 0x00301050  CreateVec__10EffectCoreFPc  =  EffectCore::CreateVec
undefined4 EffectCore::CreateVec(int this,void *param_2)

{
  undefined4 uVar1;
  int iVar2;
  void *__dest;
  long lVar3;
  void *__s1;
  void *__s1_00;
  
  __s1 = (void *)((int)param_2 + *(int *)((int)param_2 + 8));
  __s1_00 = (void *)((int)param_2 + *(int *)((int)param_2 + 0xc));
  lVar3 = __nw(0x254);
  uVar1 = 0;
  if (lVar3 != 0) {
    uVar1 = VEC::VEC(lVar3,*(undefined4 *)((int)param_2 + 0x10),this,0);
  }
  this->u32_10 = uVar1;
  iVar2 = memcmp(param_2,&_6686,4);
  if (iVar2 == 0) {
    if (*(int *)((int)param_2 + 4) < 3) {
      uVar1 = 0;
    }
    else if (*(int *)((int)param_2 + 4) < 4) {
      iVar2 = memcmp(__s1,&_6687,4);
      if (iVar2 == 0) {
        if (*(uint *)((int)__s1 + 4) < 0x9c41) {
          __dest = (void *)VEC::GetDsegAddr(this->u32_10,0);
          memcpy(__dest,(void *)((int)__s1 + 0x10),(long)*(int *)((int)__s1 + 4));
          iVar2 = memcmp(__s1_00,&_6688,4);
          if (iVar2 == 0) {
            VEC::SetIseg(this->u32_10,(int)__s1_00 + 0x10);
            uVar1 = 1;
          }
          else {
            uVar1 = 0;
          }
        }
        else {
          uVar1 = 0;
        }
      }
      else {
        uVar1 = 0;
      }
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

// JP: 0x00301220  CreateTexture__10EffectCoreFPc  =  EffectCore::CreateTexture
undefined4 EffectCore::CreateTexture(int this,undefined4 param_2)

{
  undefined4 uVar1;
  long lVar2;
  
  lVar2 = __nw(0x14);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = vpTextureFile::vpTextureFile(lVar2);
  }
  this->u32_18 = uVar1;
  vpTextureFile::Create(this->u32_18,param_2);
  return 1;
}

// JP: 0x003012a0  GetModel__10EffectCoreFiiii  =  EffectCore::GetModel
int EffectCore::GetModel
              (undefined4 this,int param_2,undefined4 param_3,int param_4,int param_5)

{
  int iVar1;
  
  if (param_2 == 0) {
    iVar1 = EffectCore::GetGenModel(this,param_3);
  }
  else {
    iVar1 = EffectCore::GetTargetModel(this,param_3);
  }
  if (param_4 == 1) {
    if (param_5 == 0) {
      iVar1 = iVar1->i32_52c;
    }
    else {
      iVar1 = iVar1->i32_530;
    }
  }
  else if (param_4 != 0) {
    iVar1 = 0;
  }
  return iVar1;
}

// JP: 0x00301390  GetTargetModel__10EffectCoreFi  =  EffectCore::GetTargetModel
undefined4 EffectCore::GetTargetModel(int this,int param_2)

{
  return *(undefined4 *)(this->i32_20 + param_2 * 0x14 + 4);
}

// JP: 0x003013d0  GetGenModel__10EffectCoreFi  =  EffectCore::GetGenModel
undefined4 EffectCore::GetGenModel(int this,int param_2)

{
  return *(undefined4 *)(this->i32_1c + param_2 * 0x14 + 4);
}

// JP: 0x00301410  GetModelSet__10EffectCoreFii  =  EffectCore::GetModelSet
int EffectCore::GetModelSet(int this,int param_2,int param_3)

{
  int iVar1;
  
  if (param_2 == 0) {
    iVar1 = this->i32_1c + param_3 * 0x14;
  }
  else {
    iVar1 = this->i32_20 + param_3 * 0x14;
  }
  return iVar1;
}

// JP: 0x00301480  GetBtlChrParam__10EffectCoreFii  =  EffectCore::GetBtlChrParam
undefined4 EffectCore::GetBtlChrParam(int this,int param_2,int param_3)

{
  undefined4 uVar1;
  
  if (param_2 == 0) {
    uVar1 = *(undefined4 *)(this->i32_1c + param_3 * 0x14 + 8);
  }
  else {
    uVar1 = *(undefined4 *)(this->i32_20 + param_3 * 0x14 + 8);
  }
  return uVar1;
}

// JP: 0x00301500  Run__10EffectCoreFv  =  EffectCore::Run
void EffectCore::Run(int this)

{
  VEC::Start(this->u32_10);
  return;
}

// JP: 0x00301560  Continue__10EffectCoreFv  =  EffectCore::Continue
bool EffectCore::Continue(int this)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  long lVar4;
  uint uVar5;
  
  iVar3 = this->i32_10;
  if ((this->u8_e0 & 3) == 1) {
    bVar1 = false;
  }
  else {
    uVar5 = 0;
    for (; iVar3 != 0; iVar3 = CList::GetNext(iVar3)) {
      lVar4 = VEC::GetRunState(iVar3);
      if (lVar4 == 0) {
        VEC::Start(iVar3);
      }
    }
    iVar3 = this->i32_10;
    EffectCore::AddTimeAll(this);
    while (iVar3 != 0) {
      iVar2 = CList::GetNext(iVar3);
      lVar4 = VEC::GetRunState(iVar3);
      if ((lVar4 == 2) || (lVar4 == 1)) {
        EffectCore::UpdateFader(this);
        lVar4 = VEC::Continue(iVar3);
        uVar5 = uVar5 | lVar4 != 0;
      }
      uVar5 = uVar5 << 1;
      iVar3 = iVar2;
    }
    iVar3 = this->i32_10;
    while (iVar2 = iVar3, iVar2 != 0) {
      iVar3 = CList::GetNext(iVar2);
      lVar4 = VEC::GetRunState(iVar2);
      if (lVar4 == 3) {
        EffectCore::RemoveThread(this,iVar2);
      }
    }
    if (uVar5 == 0) {
      this->u8_e0 = this->u8_e0 & 0xfc | 1;
      EffectCore::Cleanup(this);
    }
    bVar1 = uVar5 != 0;
  }
  return bVar1;
}

// JP: 0x00301790  AddTimeAll__10EffectCoreFv  =  EffectCore::AddTimeAll
void EffectCore::AddTimeAll(int this)

{
  int iVar1;
  undefined1 auStack_90 [64];
  undefined1 auStack_50 [64];
  int iStack_10;
  
  iStack_10 = this;
  if (this->i32_36c != 0) {
    HitCylinder::AddTime(this->u32_194,this->u32_36c);
  }
  if (iStack_10->i32_370 != 0) {
    HitShot::AddTime
              (iStack_10->u32_194,0x3d088889,iStack_10->u32_370);
  }
  for (iVar1 = 0; iVar1 < 0x28; iVar1 = iVar1 + 1) {
    if (*(int *)(iStack_10 + iVar1 * 4 + 0x198) != 0) {
      (**(code **)(*(int *)(*(int *)(iStack_10 + iVar1 * 4 + 0x198) + 0x10) + 0x2c))
                (iStack_10->u32_18c);
    }
  }
  for (iVar1 = 0; iVar1 < 10; iVar1 = iVar1 + 1) {
    if ((*(int *)(iStack_10 + iVar1 * 4 + 0x374) != 0) &&
       (*(int *)(*(int *)(iStack_10 + iVar1 * 4 + 0x374) + 8) != -1)) {
      tagEFLTMotionData::tagEFLTMotionData(auStack_50);
      (**(code **)(*(int *)(*(int *)(iStack_10 + iVar1 * 4 + 0x374) + 0x20) + 8))
                (iStack_10->u32_190);
      EffectLight::GetData
                (*(undefined4 *)(iStack_10 + iVar1 * 4 + 0x374),auStack_50);
      EffectLight::ChangeLight
                (*(undefined4 *)(iStack_10 + iVar1 * 4 + 0x374),auStack_50);
    }
  }
  EffectCore::CalcMatrix(iStack_10);
  if (iStack_10->i32_2a0 != 0) {
    tagEFCMMotionData::tagEFCMMotionData(auStack_90);
    (**(code **)(*(int *)(iStack_10->i32_2a0 + 0xf4) + 8))
              (iStack_10->u32_190);
    EffectCamera::GetData(iStack_10->u32_2a0,auStack_90);
    EffectCamera::LookAt(iStack_10->u32_2a0,auStack_90);
  }
  for (iVar1 = 0; iVar1 < 0x32; iVar1 = iVar1 + 1) {
    if (*(int *)(iStack_10 + iVar1 * 4 + 0x454) != 0) {
      CPathControl::AddTime
                (iStack_10->u32_18c,*(undefined4 *)(iStack_10 + iVar1 * 4 + 0x454));
    }
  }
  for (iVar1 = 0; iVar1 < 3; iVar1 = iVar1 + 1) {
    if (*(int *)(iStack_10 + iVar1 * 4 + 0x56c) != 0) {
      EffectGunya::AddTime
                (iStack_10->u32_18c,*(undefined4 *)(iStack_10 + iVar1 * 4 + 0x56c));
    }
  }
  for (iVar1 = 0; iVar1 < 10; iVar1 = iVar1 + 1) {
  }
  if (iStack_10->i32_578 != 0) {
    EffectBarin::AddTime(iStack_10->u32_18c,iStack_10->u32_578);
  }
  return;
}

// JP: 0x00301b80  CalcMatrix__10EffectCoreFv  =  EffectCore::CalcMatrix
void EffectCore::CalcMatrix(int this)

{
  int iVar1;
  int iVar2;
  
  for (iVar2 = 0; iVar2 < 0x28; iVar2 = iVar2 + 1) {
    if (*(int *)(this + iVar2 * 4 + 0x198) != 0) {
      iVar1 = *(int *)(this + iVar2 * 4 + 0x198);
      (**(code **)(iVar1->i32_10 + 0x28))(iVar1,0);
    }
  }
  return;
}

// JP: 0x00301c10  AddThread__10EffectCoreFP3VEC  =  EffectCore::AddThread
void EffectCore::AddThread(int this,undefined4 param_2)

{
  if (this->i32_10 != 0) {
    VEC::OnStartThread(this->u32_10,param_2);
  }
  CList::Add(this->u32_10,param_2);
  return;
}

// JP: 0x00301c70  RemoveThread__10EffectCoreFP3VEC  =  EffectCore::RemoveThread
void EffectCore::RemoveThread(int this,int param_2)

{
  undefined4 uVar1;
  
  uVar1 = CList::Remove(param_2);
  this->u32_10 = uVar1;
  if (this->i32_10 != 0) {
    VEC::OnEndThread(this->u32_10,param_2);
  }
  if ((param_2 != 0) && (param_2 != 0)) {
    (**(code **)(param_2->i32_250 + 8))(param_2,1);
  }
  return;
}

// JP: 0x00301d10  KillThread__10EffectCoreFi  =  EffectCore::KillThread
void EffectCore::KillThread(int this,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = this->i32_10;
  while (iVar2 = iVar1, iVar2 != 0) {
    iVar1 = CList::GetNext(iVar2);
    if (iVar2->i32_244 == param_2) {
      VEC::Stop(iVar2);
    }
  }
  return;
}

// JP: 0x00301db0  KillThreadAll__10EffectCoreFv  =  EffectCore::KillThreadAll
void EffectCore::KillThreadAll(int this)

{
  int iVar1;
  int iVar2;
  
  iVar2 = this->i32_10;
  while (iVar2 != 0) {
    iVar1 = CList::GetNext(iVar2);
    VEC::Stop(iVar2);
    iVar2 = iVar1;
  }
  return;
}

// JP: 0x00301e20  UpdateFader__10EffectCoreFv  =  EffectCore::UpdateFader
void EffectCore::UpdateFader(void)

{
  int iVar1;
  long lVar2;
  int iVar3;
  
  iVar1 = EffectCore::m_Fader;
  while (iVar3 = iVar1, iVar3 != 0) {
    iVar1 = CList::GetNext(iVar3);
    lVar2 = ModelFader::Update(iVar3);
    if (((lVar2 != 0) && (EffectCore::m_Fader = CList::Remove(iVar3), iVar3 != 0)) &&
       (iVar3 != 0)) {
      (**(code **)(iVar3->i32_38 + 8))(iVar3,1);
    }
  }
  return;
}

// JP: 0x00301ee0  FindWorkModel__10EffectCoreFUi  =  EffectCore::FindWorkModel
undefined4 EffectCore::FindWorkModel(int this,int param_2)

{
  int iVar1;
  
  iVar1 = 0;
  while( true ) {
    if (0x27 < iVar1) {
      return 0;
    }
    if (*(int *)(this + iVar1 * 4 + 0x198) == param_2) break;
    iVar1 = iVar1 + 1;
  }
  return *(undefined4 *)(this + iVar1 * 4 + 0x198);
}

// JP: 0x00301f60  FindIndexWorkModel__10EffectCoreFUi  =  EffectCore::FindIndexWorkModel
int EffectCore::FindIndexWorkModel(int this,int param_2)

{
  int iVar1;
  
  iVar1 = 0;
  while( true ) {
    if (0x27 < iVar1) {
      return -1;
    }
    if (*(int *)(this + iVar1 * 4 + 0x198) == param_2) break;
    iVar1 = iVar1 + 1;
  }
  return iVar1;
}

// JP: 0x00301fd0  DeleteWorkModel__10EffectCoreFP5Model  =  EffectCore::DeleteWorkModel
void EffectCore::DeleteWorkModel(int this,int param_2)

{
  int iVar1;
  
  iVar1 = 0;
  while( true ) {
    if (0x27 < iVar1) {
      return;
    }
    if (*(int *)(this + iVar1 * 4 + 0x198) == param_2) break;
    iVar1 = iVar1 + 1;
  }
  (**(code **)(param_2->i32_1c + 0xc))();
  *(undefined4 *)(this + iVar1 * 4 + 0x198) = 0;
  return;
}

// JP: 0x00302070  ManyDeleteWorkModel__10EffectCoreFiP3VEC  =  EffectCore::ManyDeleteWorkModel
void EffectCore::ManyDeleteWorkModel(int this,int param_2,int param_3)

{
  int iVar1;
  
  if (param_2 == 0) {
    for (iVar1 = 0; iVar1 < 0x28; iVar1 = iVar1 + 1) {
      if (*(int *)(this + iVar1 * 4 + 0x198) != 0) {
        World::ReleaseOT
                  ((World *)&CApp::m_World,*(VIF1Prim **)(this + iVar1 * 4 + 0x198));
        (**(code **)(*(int *)(*(int *)(this + iVar1 * 4 + 0x198) + 0x1c) + 0xc))();
        *(undefined4 *)(this + iVar1 * 4 + 0x198) = 0;
      }
    }
  }
  else {
    for (iVar1 = 0; iVar1 < 0x28; iVar1 = iVar1 + 1) {
      if ((*(int *)(this + iVar1 * 4 + 0x198) != 0) &&
         (*(int *)(*(int *)(this + iVar1 * 4 + 0x198) + 0x51c) == param_3)) {
        World::ReleaseOT
                  ((World *)&CApp::m_World,*(VIF1Prim **)(this + iVar1 * 4 + 0x198));
        (**(code **)(*(int *)(*(int *)(this + iVar1 * 4 + 0x198) + 0x1c) + 0xc))();
        *(undefined4 *)(this + iVar1 * 4 + 0x198) = 0;
      }
    }
  }
  return;
}

// JP: 0x00302210  CreateCustomModel__10EffectCoreFiPcUiPc  =  EffectCore::CreateCustomModel
undefined4
EffectCore::CreateCustomModel
          (int this,uint param_2,char *param_3,undefined4 param_4,undefined4 param_5)

{
  int iVar1;
  undefined4 uVar2;
  long lVar3;
  undefined8 uVar4;
  byte *pbVar5;
  int iVar6;
  
  iVar1 = BufMemory::getBuffer(this->u32_d0);
  pbVar5 = (byte *)(iVar1 + 0x10);
  uVar2 = 0;
  iVar6 = 0;
  do {
    if ((int)(uint)iVar1->u16_4 <= iVar6) {
LAB_00302370:
      uVar4 = EffectCore::FindWorkModel(this,param_4);
      EffectModel::AddCustom(uVar4,uVar2,param_5);
      return uVar2;
    }
    if (((ulong)*pbVar5 == (long)*param_3) && (param_2 == pbVar5[1])) {
      lVar3 = __nw(0xd0);
      uVar2 = 0;
      if (lVar3 != 0) {
        uVar2 = BBPLineModel::BBPLineModel(lVar3);
      }
      *(undefined4 *)(this + (uint)pbVar5[1] * 4 + 0x238) = uVar2;
      iVar6 = *(int *)(this + (uint)pbVar5[1] * 4 + 0x238);
      (**(code **)(iVar6->i32_10 + 0x30))(iVar6,iVar1 + pbVar5->i32_4,0);
      uVar2 = *(undefined4 *)(this + (uint)pbVar5[1] * 4 + 0x238);
      goto LAB_00302370;
    }
    pbVar5 = pbVar5 + 8;
    iVar6 = iVar6 + 1;
  } while( true );
}

// JP: 0x003023d0  FindCustomModel__10EffectCoreFUi  =  EffectCore::FindCustomModel
int EffectCore::FindCustomModel(int this,int param_2)

{
  int iVar1;
  
  iVar1 = 0;
  while( true ) {
    if (0x27 < iVar1) {
      return 0;
    }
    if (*(int *)(this + iVar1 * 4 + 0x238) == param_2) break;
    iVar1 = iVar1 + 1;
  }
  return param_2;
}

// JP: 0x00302450  CreateWorkModel__10EffectCoreFi  =  EffectCore::CreateWorkModel
undefined4 EffectCore::CreateWorkModel(int this,uint param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  long lVar4;
  char *pcVar5;
  int iVar6;
  int iVar7;
  
  iVar2 = BufMemory::getBuffer(this->u32_d0);
  pcVar5 = (char *)(iVar2 + 0x10);
  iVar7 = 0;
  while ((iVar6 = -1, iVar7 < 0x28 && (iVar6 = iVar7, *(int *)(this + iVar7 * 4 + 0x198) != 0)))
  {
    iVar7 = iVar7 + 1;
  }
  if (iVar6 == -1) {
    uVar3 = 0;
  }
  else {
    uVar3 = 0;
    for (iVar7 = 0; iVar7 < (int)(uint)iVar2->u16_4; iVar7 = iVar7 + 1) {
      if (*pcVar5 == 'A') {
        if (param_2 == (byte)pcVar5[1]) {
          Model::createMotion
                    (*(undefined4 *)(this + iVar6 * 4 + 0x198),iVar2 + pcVar5->i32_4);
          iVar1 = *(int *)(this + iVar6 * 4 + 0x198);
          (**(code **)(iVar1->i32_10 + 0x28))(iVar1,0);
        }
      }
      else if ((*pcVar5 == 'M') && (param_2 == (byte)pcVar5[1])) {
        lVar4 = __nw(0x5b0);
        uVar3 = 0;
        if (lVar4 != 0) {
          uVar3 = EffectModel::EffectModel(lVar4,this);
        }
        *(undefined4 *)(this + iVar6 * 4 + 0x198) = uVar3;
        iVar1 = *(int *)(this + iVar6 * 4 + 0x198);
        (**(code **)(iVar1->i32_10 + 0x24))(iVar1,iVar2 + pcVar5->i32_4);
        iVar1 = *(int *)(this + iVar6 * 4 + 0x198);
        (**(code **)(iVar1->i32_10 + 0x28))(iVar1,0);
        uVar3 = *(undefined4 *)(this + iVar6 * 4 + 0x198);
      }
      pcVar5 = pcVar5 + 8;
    }
  }
  return uVar3;
}

// JP: 0x003026b0  CreateMotion__10EffectCoreFP5Modeliiiii  =  EffectCore::CreateMotion
undefined8
EffectCore::CreateMotion
          (int this,int param_2,undefined1 param_3,undefined1 param_4,uint param_5,
          undefined1 param_6,undefined1 param_7)

{
  int iVar1;
  undefined8 uVar2;
  char *pcVar3;
  int iVar4;
  
  iVar1 = BufMemory::getBuffer(this->u32_d0);
  pcVar3 = (char *)(iVar1 + 0x10);
  iVar4 = 0;
  while( true ) {
    if ((int)(uint)iVar1->u16_4 <= iVar4) {
      return 0;
    }
    if (((*pcVar3 == 'A') && ((pcVar3[1] & 0x80U) != 0)) && (param_5 == ((byte)pcVar3[1] & 0x7f)))
    break;
    pcVar3 = pcVar3 + 8;
    iVar4 = iVar4 + 1;
  }
  iVar4 = 0;
  while ((iVar4 < 0x14 && (*(int *)(this + iVar4 * 8 + 0x2d0) != 0))) {
    iVar4 = iVar4 + 1;
  }
  *(undefined1 *)(this + iVar4 * 8 + 0x2cc) = param_3;
  *(undefined1 *)(this + iVar4 * 8 + 0x2cd) = param_4;
  *(undefined1 *)(this + iVar4 * 8 + 0x2ce) = param_6;
  *(undefined1 *)(this + iVar4 * 8 + 0x2cf) = param_7;
  uVar2 = Model::createMotion(param_2,iVar1 + pcVar3->i32_4);
  *(int *)(this + iVar4 * 8 + 0x2d0) = (int)uVar2;
  (**(code **)(param_2->i32_10 + 0x28))(param_2,0);
  return uVar2;
}

// JP: 0x003028b0  CloneWorkModel__10EffectCoreFi  =  EffectCore::CloneWorkModel
undefined4 EffectCore::CloneWorkModel(int this,uint param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  long lVar4;
  char *pcVar5;
  int iVar6;
  int iVar7;
  
  iVar2 = 0;
  while ((iVar6 = -1, iVar2 < 0x28 && (iVar6 = iVar2, *(int *)(this + iVar2 * 4 + 0x198) != 0)))
  {
    iVar2 = iVar2 + 1;
  }
  if (iVar6 == -1) {
    uVar3 = 0;
  }
  else {
    iVar2 = BufMemory::getBuffer(this->u32_d0);
    pcVar5 = (char *)(iVar2 + 0x10);
    uVar3 = 0;
    for (iVar7 = 0; iVar7 < (int)(uint)iVar2->u16_4; iVar7 = iVar7 + 1) {
      if (*pcVar5 == 'A') {
        if (param_2 == (byte)pcVar5[1]) {
          Model::createMotion
                    (*(undefined4 *)(this + iVar6 * 4 + 0x198),iVar2 + pcVar5->i32_4);
          iVar1 = *(int *)(this + iVar6 * 4 + 0x198);
          (**(code **)(iVar1->i32_10 + 0x28))(iVar1,0);
        }
      }
      else if ((*pcVar5 == 'M') && (param_2 == (byte)pcVar5[1])) {
        lVar4 = __nw(0x5b0);
        uVar3 = 0;
        if (lVar4 != 0) {
          uVar3 = EffectModel::EffectModel(lVar4,this);
        }
        *(undefined4 *)(this + iVar6 * 4 + 0x198) = uVar3;
        iVar1 = *(int *)(this + iVar6 * 4 + 0x198);
        (**(code **)(iVar1->i32_10 + 0x24))(iVar1,iVar2 + pcVar5->i32_4);
        iVar1 = *(int *)(this + iVar6 * 4 + 0x198);
        (**(code **)(iVar1->i32_10 + 0x28))(iVar1,0);
        uVar3 = *(undefined4 *)(this + iVar6 * 4 + 0x198);
      }
      pcVar5 = pcVar5 + 8;
    }
  }
  return uVar3;
}

// JP: 0x00302b00  CreateCamera__10EffectCoreFi  =  EffectCore::CreateCamera
undefined4 EffectCore::CreateCamera(int this,uint param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  long lVar4;
  int iVar5;
  char *pcVar6;
  
  iVar2 = BufMemory::getBuffer(this->u32_d0);
  pcVar6 = (char *)(iVar2 + 0x10);
  iVar5 = 0;
  while( true ) {
    if ((int)(uint)iVar2->u16_4 <= iVar5) {
      return 0;
    }
    if ((*pcVar6 == 'E') && (param_2 == (byte)pcVar6[1])) break;
    pcVar6 = pcVar6 + 8;
    iVar5 = iVar5 + 1;
  }
  iVar5 = 0;
  while( true ) {
    if (9 < iVar5) {
      return 0;
    }
    if (*(int *)(this + iVar5 * 4 + 0x278) == 0) break;
    iVar5 = iVar5 + 1;
  }
  lVar4 = __nw(0x100);
  uVar3 = 0;
  if (lVar4 != 0) {
    uVar3 = EffectCamera::EffectCamera(lVar4);
  }
  *(undefined4 *)(this + iVar5 * 4 + 0x278) = uVar3;
  iVar1 = *(int *)(this + iVar5 * 4 + 0x278);
  (**(code **)(iVar1->i32_f4 + 0xc))(iVar1,iVar2 + pcVar6->i32_4);
  return *(undefined4 *)(this + iVar5 * 4 + 0x278);
}

// JP: 0x00302ca0  CreateHitCylinder__10EffectCoreFR7FVectori  =  EffectCore::CreateHitCylinder
undefined4 EffectCore::CreateHitCylinder(int this,undefined4 param_2,uint param_3)

{
  int iVar1;
  undefined4 uVar2;
  long lVar3;
  char *pcVar4;
  int iVar5;
  
  iVar1 = BufMemory::getBuffer(this->u32_d0);
  pcVar4 = (char *)(iVar1 + 0x10);
  iVar5 = 0;
  while( true ) {
    if ((int)(uint)iVar1->u16_4 <= iVar5) {
      return 0;
    }
    if ((*pcVar4 == 'Y') && ((byte)pcVar4[1] == param_3)) break;
    pcVar4 = pcVar4 + 8;
    iVar5 = iVar5 + 1;
  }
  lVar3 = __nw(0x40);
  uVar2 = 0;
  if (lVar3 != 0) {
    uVar2 = HitCylinder::HitCylinder(lVar3,0x2ffc10,this);
  }
  this->u32_36c = uVar2;
  HitCylinder::Create
            (this->u32_36c,iVar1 + pcVar4->i32_4,param_2);
  return this->u32_36c;
}

// JP: 0x00302de0  CreateHitShot__10EffectCoreFiR7FVectorR7FVector  =  EffectCore::CreateHitShot
undefined4
EffectCore::CreateHitShot
          (int this,uint param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  long lVar3;
  char *pcVar4;
  int iVar5;
  
  iVar1 = BufMemory::getBuffer(this->u32_d0);
  pcVar4 = (char *)(iVar1 + 0x10);
  iVar5 = 0;
  while( true ) {
    if ((int)(uint)iVar1->u16_4 <= iVar5) {
      return 0;
    }
    if ((*pcVar4 == 'S') && ((byte)pcVar4[1] == param_2)) break;
    pcVar4 = pcVar4 + 8;
    iVar5 = iVar5 + 1;
  }
  lVar3 = __nw(0x60);
  uVar2 = 0;
  if (lVar3 != 0) {
    uVar2 = HitShot::HitShot(lVar3,0x2ffc10,this);
  }
  this->u32_370 = uVar2;
  HitShot::Create(this->u32_370,iVar1 + pcVar4->i32_4);
  HitShot::SetPoint(this->u32_370,param_3,param_4);
  return this->u32_370;
}

// JP: 0x00302f40  FindCamera__10EffectCoreFUi  =  EffectCore::FindCamera
int EffectCore::FindCamera(int this,int param_2)

{
  int iVar1;
  
  iVar1 = 0;
  while( true ) {
    if (9 < iVar1) {
      return 0;
    }
    if (*(int *)(this + iVar1 * 4 + 0x278) == param_2) break;
    iVar1 = iVar1 + 1;
  }
  return param_2;
}

// JP: 0x00302fc0  CreateLight__10EffectCoreFi  =  EffectCore::CreateLight
undefined4 EffectCore::CreateLight(int this,uint param_2)

{
  int iVar1;
  undefined4 uVar2;
  long lVar3;
  int iVar4;
  char *pcVar5;
  int iVar6;
  
  iVar1 = BufMemory::getBuffer(this->u32_d0);
  pcVar5 = (char *)(iVar1 + 0x10);
  iVar6 = 0;
  do {
    if ((int)(uint)iVar1->u16_4 <= iVar6) {
      return 0;
    }
    if ((*pcVar5 == 'L') && ((byte)pcVar5[1] == param_2)) {
      for (iVar4 = 0; iVar4 < 10; iVar4 = iVar4 + 1) {
        if (*(int *)(this + iVar4 * 4 + 0x374) == 0) {
          lVar3 = __nw(0x30);
          uVar2 = 0;
          if (lVar3 != 0) {
            uVar2 = EffectLight::EffectLight(lVar3);
          }
          *(undefined4 *)(this + iVar4 * 4 + 0x374) = uVar2;
          iVar6 = *(int *)(this + iVar4 * 4 + 0x374);
          (**(code **)(iVar6->i32_20 + 0xc))(iVar6,iVar1 + pcVar5->i32_4);
          return *(undefined4 *)(this + iVar4 * 4 + 0x374);
        }
      }
    }
    pcVar5 = pcVar5 + 8;
    iVar6 = iVar6 + 1;
  } while( true );
}

// JP: 0x00303140  FindLight__10EffectCoreFUi  =  EffectCore::FindLight
int EffectCore::FindLight(int this,int param_2)

{
  int iVar1;
  
  iVar1 = 0;
  while( true ) {
    if (9 < iVar1) {
      return 0;
    }
    if (*(int *)(this + iVar1 * 4 + 0x374) == param_2) break;
    iVar1 = iVar1 + 1;
  }
  return param_2;
}

// JP: 0x003031c0  FindLightIndex__10EffectCoreFP11EffectLight  =  EffectCore::FindLightIndex
int EffectCore::FindLightIndex(int this,int param_2)

{
  int iVar1;
  
  iVar1 = 0;
  while( true ) {
    if (9 < iVar1) {
      return -1;
    }
    if (*(int *)(this + iVar1 * 4 + 0x374) == param_2) break;
    iVar1 = iVar1 + 1;
  }
  return iVar1;
}

// JP: 0x00303230  SetCurrentCamera__10EffectCoreFP12EffectCamerai  =  EffectCore::SetCurrentCamera
void EffectCore::SetCurrentCamera(int this,undefined4 param_2)

{
  this->u32_2a0 = param_2;
  return;
}

// JP: 0x00303260  CreateSprite__10EffectCoreFP7FVectorP7FVectorP7FVectorP7FVectorP7FVectori  =  EffectCore::CreateSprite
undefined4
EffectCore::CreateSprite
          (int this,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,
          undefined4 param_6,undefined4 param_7)

{
  undefined4 uVar1;
  long lVar2;
  int iVar3;
  
  iVar3 = 0;
  while( true ) {
    if (9 < iVar3) {
      return 0;
    }
    if (*(int *)(this + iVar3 * 4 + 0x2a4) == 0) break;
    iVar3 = iVar3 + 1;
  }
  lVar2 = __nw(0x90);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = EffectSprite::EffectSprite
                      (lVar2,param_2,param_3,param_4,param_5,param_6,param_7);
  }
  *(undefined4 *)(this + iVar3 * 4 + 0x2a4) = uVar1;
  return *(undefined4 *)(this + iVar3 * 4 + 0x2a4);
}

// JP: 0x00303350  FindSprite__10EffectCoreFUi  =  EffectCore::FindSprite
undefined4 EffectCore::FindSprite(int this,int param_2)

{
  int iVar1;
  
  iVar1 = 0;
  while( true ) {
    if (9 < iVar1) {
      return 0;
    }
    if (*(int *)(this + iVar1 * 4 + 0x2a4) == param_2) break;
    iVar1 = iVar1 + 1;
  }
  return *(undefined4 *)(this + iVar1 * 4 + 0x2a4);
}

// JP: 0x003033e0  DeleteSprite__10EffectCoreFP12EffectSprite  =  EffectCore::DeleteSprite
void EffectCore::DeleteSprite(int this,VIF1Prim *param_2)

{
  int iVar1;
  
  iVar1 = 0;
  while( true ) {
    if (9 < iVar1) {
      return;
    }
    if (*(VIF1Prim **)(this + iVar1 * 4 + 0x2a4) == param_2) break;
    iVar1 = iVar1 + 1;
  }
  *(undefined4 *)(this + iVar1 * 4 + 0x2a4) = 0;
  World::ReleaseOT((World *)&CApp::m_World,param_2);
  (**(code **)(param_2[1].dwEnv + 0xc))();
  return;
}

// JP: 0x00303490  SetAddTime__10EffectCoreFif  =  EffectCore::SetAddTime
void EffectCore::SetAddTime(undefined4 this,int param_2,uint param_3)

{
  if ((param_3 & 1) != 0) {
    param_2->u32_188 = this;
  }
  if ((param_3 & 2) != 0) {
    param_2->u32_18c = this;
  }
  if ((param_3 & 4) != 0) {
    param_2->u32_190 = this;
  }
  if ((param_3 & 8) != 0) {
    param_2->u32_194 = this;
  }
  return;
}

// JP: 0x00303530  GetAddTime__10EffectCoreFi  =  EffectCore::GetAddTime
undefined4 EffectCore::GetAddTime(int this,uint param_2)

{
  undefined4 uVar1;
  
  if ((param_2 & 1) == 0) {
    if ((param_2 & 2) == 0) {
      if ((param_2 & 4) == 0) {
        if ((param_2 & 8) == 0) {
          uVar1 = 0;
        }
        else {
          uVar1 = this->u32_194;
        }
      }
      else {
        uVar1 = this->u32_190;
      }
    }
    else {
      uVar1 = this->u32_18c;
    }
  }
  else {
    uVar1 = this->u32_188;
  }
  return uVar1;
}

// JP: 0x003035e0  HitEnd__10EffectCoreFi  =  EffectCore::HitEnd
void EffectCore::HitEnd(int this,int param_2)

{
  int iVar1;
  
  if (param_2 == 0) {
    if (this->i32_36c != 0) {
      iVar1 = this->i32_36c;
      if (iVar1 != 0) {
        (**(code **)(iVar1->i32_38 + 8))(iVar1,1);
      }
      this->u32_36c = 0;
    }
  }
  else if (this->i32_370 != 0) {
    iVar1 = this->i32_370;
    if (iVar1 != 0) {
      (**(code **)(iVar1->i32_5c + 8))(iVar1,1);
    }
    this->u32_370 = 0;
  }
  return;
}

// JP: 0x003036b0  LoadSe__10EffectCoreFi  =  EffectCore::LoadSe
int EffectCore::LoadSe(int this,uint param_2)

{
  int iVar1;
  undefined8 uVar2;
  long lVar3;
  undefined8 uVar4;
  int iVar5;
  int iVar6;
  char *pcVar7;
  
  iVar1 = BufMemory::getBuffer(this->u32_d0);
  pcVar7 = (char *)(iVar1 + 0x10);
  iVar6 = 0;
  while( true ) {
    if ((int)(uint)iVar1->u16_4 <= iVar6) {
      return 0;
    }
    if ((*pcVar7 == '1') && (param_2 == (byte)pcVar7[1])) break;
    pcVar7 = pcVar7 + 8;
    iVar6 = iVar6 + 1;
  }
  iVar6 = 0;
  while( true ) {
    if (9 < iVar6) {
      return 0;
    }
    if ((*(byte *)(this + iVar6 * 0xc + 0x39c) & 1) == 0) break;
    iVar6 = iVar6 + 1;
  }
  iVar5 = this + iVar6 * 0xc;
  iVar5->u8_39c = iVar5->u8_39c & 0xfe | 1;
  iVar5 = pcVar7->i32_4;
  uVar2 = Sdrv::AutoLoad(Sdrv::sys,iVar1 + iVar5,0);
  lVar3 = __nw(0x38);
  uVar4 = 0;
  if (lVar3 != 0) {
    uVar4 = SdState::SdState
                      (lVar3,this + iVar6 * 0xc + 0x39c,uVar2,0x31bde0,iVar1 + iVar5,0,0);
  }
  SdState::AddState(uVar4);
  return this + iVar6 * 0xc + 0x39c;
}

// JP: 0x003038d0  UnloadSe__10EffectCoreFUi  =  EffectCore::UnloadSe
void EffectCore::UnloadSe(undefined4 this,undefined4 param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  long lVar3;
  undefined8 uVar4;
  
  uVar1 = EffectCore::FindSe(this,param_2);
  uVar2 = Sdrv::ReleaseSDH(Sdrv::sys,*(undefined4 *)((int)uVar1 + 4));
  lVar3 = __nw(0x38);
  uVar4 = 0;
  if (lVar3 != 0) {
    uVar4 = SdState::SdState
                      (lVar3,0,uVar2,0x31c490,*(undefined4 *)((int)uVar1 + 4),0,0);
  }
  SdState::AddState(uVar4);
  tagEffSeCtrl::Init(uVar1);
  return;
}

// JP: 0x003039a0  FindSe__10EffectCoreFUi  =  EffectCore::FindSe
int EffectCore::FindSe(int this,int param_2)

{
  int iVar1;
  
  iVar1 = 0;
  while( true ) {
    if (9 < iVar1) {
      if (this + 0x414 == param_2) {
        this = this + 0x414;
      }
      else if (this + 0x420 == param_2) {
        this = this + 0x420;
      }
      else if (this + 0x42c == param_2) {
        this = this + 0x42c;
      }
      else {
        this = 0;
      }
      return this;
    }
    if (this + iVar1 * 0xc + 0x39c == param_2) break;
    iVar1 = iVar1 + 1;
  }
  return this + iVar1 * 0xc + 0x39c;
}

// JP: 0x00303ab0  PlaySe__10EffectCoreFP12tagEffSeCtrlUi  =  EffectCore::PlaySe
void EffectCore::PlaySe
               (undefined8 this,undefined4 param_2,undefined4 param_3)

{
  undefined8 uVar1;
  long lVar2;
  undefined8 uVar3;
  
  uVar1 = Sdrv::PlaySE(Sdrv::sys,param_3,0);
  lVar2 = __nw(0x38);
  uVar3 = 0;
  if (lVar2 != 0) {
    uVar3 = SdState::SdState
                      (lVar2,param_2,uVar1,0x31bf30,param_3,0,0);
  }
  SdState::AddState(uVar3);
  return;
}

// JP: 0x00303b60  CreateBlur__10EffectCoreFv  =  EffectCore::CreateBlur
undefined4 EffectCore::CreateBlur(int this)

{
  undefined4 uVar1;
  long lVar2;
  int iVar3;
  
  iVar3 = 0;
  while( true ) {
    if (2 < iVar3) {
      return 0;
    }
    if (*(int *)(this + iVar3 * 4 + 0x448) == 0) break;
    iVar3 = iVar3 + 1;
  }
  lVar2 = __nw(0x70);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = EffectBlur::EffectBlur(lVar2);
  }
  *(undefined4 *)(this + iVar3 * 4 + 0x448) = uVar1;
  return *(undefined4 *)(this + iVar3 * 4 + 0x448);
}

// JP: 0x00303c20  FindBlur__10EffectCoreFUi  =  EffectCore::FindBlur
int EffectCore::FindBlur(int this,int param_2)

{
  int iVar1;
  
  iVar1 = 0;
  while( true ) {
    if (2 < iVar1) {
      return 0;
    }
    if (*(int *)(this + iVar1 * 4 + 0x448) == param_2) break;
    iVar1 = iVar1 + 1;
  }
  return param_2;
}

// JP: 0x00303ca0  DeleteBlur__10EffectCoreFP10EffectBlur  =  EffectCore::DeleteBlur
void EffectCore::DeleteBlur(int this,int param_2)

{
  int iVar1;
  
  iVar1 = 0;
  while( true ) {
    if (2 < iVar1) {
      return;
    }
    if (*(int *)(this + iVar1 * 4 + 0x448) == param_2) break;
    iVar1 = iVar1 + 1;
  }
  (**(code **)(param_2->i32_1c + 0xc))();
  *(undefined4 *)(this + iVar1 * 4 + 0x448) = 0;
  return;
}

// JP: 0x00303d40  FindPathIndex__10EffectCoreFPv  =  EffectCore::FindPathIndex
int EffectCore::FindPathIndex(int this,int param_2)

{
  int iVar1;
  
  iVar1 = 0;
  while( true ) {
    if (0x31 < iVar1) {
      return -1;
    }
    if (*(int *)(this + iVar1 * 4 + 0x454) == param_2) break;
    iVar1 = iVar1 + 1;
  }
  return iVar1;
}

// JP: 0x00303dc0  FindCalcPathIndex__10EffectCoreFPv  =  EffectCore::FindCalcPathIndex
int EffectCore::FindCalcPathIndex(int this,int param_2)

{
  int iVar1;
  
  iVar1 = 0;
  while( true ) {
    if (0x13 < iVar1) {
      return -1;
    }
    if (*(int *)(this + iVar1 * 4 + 0x51c) == param_2) break;
    iVar1 = iVar1 + 1;
  }
  return iVar1;
}

// JP: 0x00303e40  GetDataPtr__10EffectCoreFUciUiUi  =  EffectCore::GetDataPtr
int EffectCore::GetDataPtr
              (int this,char param_2,uint param_3,uint param_4,uint param_5)

{
  int iVar1;
  char *pcVar2;
  int iVar3;
  
  iVar1 = BufMemory::getBuffer(this->u32_d0);
  pcVar2 = (char *)(iVar1 + 0x10);
  iVar3 = 0;
  do {
    if ((int)(uint)iVar1->u16_4 <= iVar3) {
      return 0;
    }
    if (param_4 == 0xffffffff) {
      if ((*pcVar2 == param_2) && ((byte)pcVar2[1] == param_3)) {
        return iVar1 + pcVar2->i32_4;
      }
    }
    else if (((*pcVar2 == param_2) && (((byte)pcVar2[1] & param_4) != 0)) &&
            (param_3 == ((byte)pcVar2[1] & param_5))) {
      return iVar1 + pcVar2->i32_4;
    }
    pcVar2 = pcVar2 + 8;
    iVar3 = iVar3 + 1;
  } while( true );
}

// JP: 0x00303f90  FindGunya__10EffectCoreFUi  =  EffectCore::FindGunya
undefined4 EffectCore::FindGunya(undefined4 this,undefined4 param_2)

{
  long lVar1;
  
  lVar1 = EffectCore::FindGunyaIndex(this,param_2);
  if (lVar1 == -1) {
    param_2 = 0;
  }
  return param_2;
}

// JP: 0x00303ff0  FindGunyaIndex__10EffectCoreFP11EffectGunya  =  EffectCore::FindGunyaIndex
int EffectCore::FindGunyaIndex(int this,int param_2)

{
  int iVar1;
  
  iVar1 = 0;
  while( true ) {
    if (2 < iVar1) {
      return -1;
    }
    if (*(int *)(this + iVar1 * 4 + 0x56c) == param_2) break;
    iVar1 = iVar1 + 1;
  }
  return iVar1;
}

// JP: 0x00304060  InitSysSE__10EffectCoreFv  =  EffectCore::InitSysSE
void EffectCore::InitSysSE(int this)

{
  tagEffSeCtrl::Init(this + 0x414);
  tagEffSeCtrl::Init(this + 0x420);
  tagEffSeCtrl::Init(this + 0x42c);
  this->u8_414 = this->u8_414 & 0xfd | 2;
  this->u32_418 = 0xffffffff;
  this->u32_424 = 0xffffffff;
  this->u32_430 = 0xffffffff;
  if (CBattle::Sys != 0) {
    this->u8_420 = this->u8_420 & 0xfd | 2;
  }
  if (CField::sys != 0) {
    this->u8_42c = this->u8_42c & 0xfd | 2;
  }
  return;
}

// JP: 0x00304160  FindFParticle__10EffectCoreFPv  =  EffectCore::FindFParticle
int EffectCore::FindFParticle(int this,int param_2)

{
  int iVar1;
  
  iVar1 = 0;
  while( true ) {
    if (9 < iVar1) {
      return -1;
    }
    if (*(int *)(this + iVar1 * 8 + 0x5b0) == param_2) break;
    iVar1 = iVar1 + 1;
  }
  return iVar1;
}

// JP: 0x003041e0  CheckHandle__10EffectCoreFPv  =  EffectCore::CheckHandle
undefined4 EffectCore::CheckHandle(int this,int param_2)

{
  int iVar1;
  
  iVar1 = 0;
  while( true ) {
    if (0x13 < iVar1) {
      return 0;
    }
    if (*(int *)(this + iVar1 * 4 + 0x138) == param_2) break;
    iVar1 = iVar1 + 1;
  }
  return 1;
}

// JP: 0x00304250  Duplicate__10EffectCoreFP10EffectCore  =  EffectCore::Duplicate
void EffectCore::Duplicate(int this,int param_2)

{
  long lVar1;
  int iVar2;
  int iVar3;
  
  this->u32_d4 = param_2->u32_d0;
  param_2->u32_d0 = 0;
  this->u32_1c = param_2->u32_1c;
  this->u32_20 = param_2->u32_20;
  memcpy((void *)(this + 0x30),(void *)(param_2 + 0x30),0x50);
  memcpy((void *)(this + 0x80),(void *)(param_2 + 0x80),0x50);
  this->u32_d8 = param_2->u32_d8;
  this->u32_dc = param_2->u32_dc;
  EffProcParam::__as(this + 0xe4,param_2 + 0xe4);
  memcpy((void *)(this + 0x188),(void *)(param_2 + 0x188),0x10);
  iVar2 = 0;
  while( true ) {
    if (0x27 < iVar2) goto LAB_00304438;
    if (*(int *)(this + iVar2 * 4 + 0x198) == 0) break;
    iVar2 = iVar2 + 1;
  }
  for (iVar3 = 0; iVar3 < 0x28; iVar3 = iVar3 + 1) {
    if ((*(int *)(param_2 + iVar3 * 4 + 0x198) != 0) &&
       (lVar1 = EffectCore::CheckHandle(this,*(undefined4 *)(param_2 + iVar3 * 4 + 0x198)),
       lVar1 != 0)) {
      if (0x27 < iVar2) {
        return;
      }
      *(undefined4 *)(this + iVar2 * 4 + 0x198) = *(undefined4 *)(param_2 + iVar3 * 4 + 0x198);
      *(int *)(*(int *)(this + iVar2 * 4 + 0x198) + 0x510) = this;
      *(undefined4 *)(param_2 + iVar3 * 4 + 0x198) = 0;
      iVar2 = iVar2 + 1;
    }
  }
LAB_00304438:
  iVar2 = 0;
  while( true ) {
    if (0xf < iVar2) goto LAB_00304538;
    if (*(int *)(this + iVar2 * 4 + 0x238) == 0) break;
    iVar2 = iVar2 + 1;
  }
  for (iVar3 = 0; iVar3 < 0x10; iVar3 = iVar3 + 1) {
    if ((*(int *)(param_2 + iVar3 * 4 + 0x238) != 0) &&
       (lVar1 = EffectCore::CheckHandle(this,*(undefined4 *)(param_2 + iVar3 * 4 + 0x238)),
       lVar1 != 0)) {
      if (0xf < iVar2) {
        return;
      }
      *(undefined4 *)(this + iVar2 * 4 + 0x238) = *(undefined4 *)(param_2 + iVar3 * 4 + 0x238);
      *(undefined4 *)(param_2 + iVar3 * 4 + 0x238) = 0;
      iVar2 = iVar2 + 1;
    }
  }
LAB_00304538:
  iVar2 = 0;
  while( true ) {
    if (9 < iVar2) goto LAB_00304630;
    if (*(int *)(this + iVar2 * 4 + 0x278) == 0) break;
    iVar2 = iVar2 + 1;
  }
  for (iVar3 = 0; iVar3 < 10; iVar3 = iVar3 + 1) {
    if ((*(int *)(param_2 + iVar3 * 4 + 0x278) != 0) &&
       (lVar1 = EffectCore::CheckHandle(this,*(undefined4 *)(param_2 + iVar3 * 4 + 0x278)),
       lVar1 != 0)) {
      if (9 < iVar2) {
        return;
      }
      *(undefined4 *)(this + iVar2 * 4 + 0x278) = *(undefined4 *)(param_2 + iVar3 * 4 + 0x278);
      *(undefined4 *)(param_2 + iVar3 * 4 + 0x278) = 0;
      iVar2 = iVar2 + 1;
    }
  }
LAB_00304630:
  lVar1 = EffectCore::CheckHandle(this,param_2->u32_2a0);
  if (lVar1 != 0) {
    this->u32_2a0 = param_2->u32_2a0;
  }
  iVar2 = 0;
  while( true ) {
    if (9 < iVar2) goto LAB_00304758;
    if (*(int *)(this + iVar2 * 4 + 0x2a4) == 0) break;
    iVar2 = iVar2 + 1;
  }
  for (iVar3 = 0; iVar3 < 10; iVar3 = iVar3 + 1) {
    if ((*(int *)(param_2 + iVar3 * 4 + 0x2a4) != 0) &&
       (lVar1 = EffectCore::CheckHandle(this,*(undefined4 *)(param_2 + iVar3 * 4 + 0x2a4)),
       lVar1 != 0)) {
      if (9 < iVar2) {
        return;
      }
      *(undefined4 *)(this + iVar2 * 4 + 0x2a4) = *(undefined4 *)(param_2 + iVar3 * 4 + 0x2a4);
      *(undefined4 *)(param_2 + iVar3 * 4 + 0x2a4) = 0;
      iVar2 = iVar2 + 1;
    }
  }
LAB_00304758:
  iVar2 = 0;
  while( true ) {
    if (0x13 < iVar2) goto LAB_00304858;
    if (*(int *)(this + iVar2 * 8 + 0x2d0) == 0) break;
    iVar2 = iVar2 + 1;
  }
  for (iVar3 = 0; iVar3 < 0x14; iVar3 = iVar3 + 1) {
    if ((*(int *)(param_2 + iVar3 * 8 + 0x2d0) != 0) &&
       (lVar1 = EffectCore::CheckHandle(this,param_2 + iVar3 * 8 + 0x2cc), lVar1 != 0)) {
      if (0x13 < iVar2) {
        return;
      }
      MotionAddInfo::__as
                (this + iVar2 * 8 + 0x2cc,param_2 + iVar3 * 8 + 0x2cc);
      *(undefined4 *)(param_2 + iVar3 * 8 + 0x2d0) = 0;
      iVar2 = iVar2 + 1;
    }
  }
LAB_00304858:
  iVar2 = 0;
  while( true ) {
    if (9 < iVar2) goto LAB_00304950;
    if (*(int *)(this + iVar2 * 4 + 0x374) == 0) break;
    iVar2 = iVar2 + 1;
  }
  for (iVar3 = 0; iVar3 < 10; iVar3 = iVar3 + 1) {
    if ((*(int *)(param_2 + iVar3 * 4 + 0x374) != 0) &&
       (lVar1 = EffectCore::CheckHandle(this,*(undefined4 *)(param_2 + iVar3 * 4 + 0x374)),
       lVar1 != 0)) {
      if (9 < iVar2) {
        return;
      }
      *(undefined4 *)(this + iVar2 * 4 + 0x374) = *(undefined4 *)(param_2 + iVar3 * 4 + 0x374);
      *(undefined4 *)(param_2 + iVar3 * 4 + 0x374) = 0;
      iVar2 = iVar2 + 1;
    }
  }
LAB_00304950:
  tagSaveFog::__as(this + 0x438,param_2 + 0x438);
  iVar2 = 0;
  while( true ) {
    if (2 < iVar2) goto LAB_00304a60;
    if (*(int *)(this + iVar2 * 4 + 0x448) == 0) break;
    iVar2 = iVar2 + 1;
  }
  for (iVar3 = 0; iVar3 < 3; iVar3 = iVar3 + 1) {
    if ((*(int *)(param_2 + iVar3 * 4 + 0x448) != 0) &&
       (lVar1 = EffectCore::CheckHandle(this,*(undefined4 *)(param_2 + iVar3 * 4 + 0x448)),
       lVar1 != 0)) {
      if (2 < iVar2) {
        return;
      }
      *(undefined4 *)(this + iVar2 * 4 + 0x448) = *(undefined4 *)(param_2 + iVar3 * 4 + 0x448);
      *(undefined4 *)(param_2 + iVar3 * 4 + 0x448) = 0;
      iVar2 = iVar2 + 1;
    }
  }
LAB_00304a60:
  iVar2 = 0;
  while( true ) {
    if (2 < iVar2) goto LAB_00304b58;
    if (*(int *)(this + iVar2 * 4 + 0x56c) == 0) break;
    iVar2 = iVar2 + 1;
  }
  for (iVar3 = 0; iVar3 < 3; iVar3 = iVar3 + 1) {
    if ((*(int *)(param_2 + iVar3 * 4 + 0x56c) != 0) &&
       (lVar1 = EffectCore::CheckHandle(this,*(undefined4 *)(param_2 + iVar3 * 4 + 0x56c)),
       lVar1 != 0)) {
      if (2 < iVar2) {
        return;
      }
      *(undefined4 *)(this + iVar2 * 4 + 0x56c) = *(undefined4 *)(param_2 + iVar3 * 4 + 0x56c);
      *(undefined4 *)(param_2 + iVar3 * 4 + 0x56c) = 0;
      iVar2 = iVar2 + 1;
    }
  }
LAB_00304b58:
  lVar1 = EffectCore::CheckHandle(this,param_2->u32_578);
  if (lVar1 != 0) {
    this->u32_578 = param_2->u32_578;
    param_2->u32_578 = 0;
  }
  iVar2 = 0;
  while( true ) {
    if (9 < iVar2) {
      return;
    }
    if (*(int *)(this + iVar2 * 8 + 0x5b0) == 0) break;
    iVar2 = iVar2 + 1;
  }
  iVar3 = 0;
  do {
    if (9 < iVar3) {
      return;
    }
    if ((*(int *)(param_2 + iVar3 * 8 + 0x5b0) != 0) &&
       (lVar1 = EffectCore::CheckHandle(this,*(undefined4 *)(param_2 + iVar3 * 8 + 0x5b0)),
       lVar1 != 0)) {
      if (9 < iVar2) {
        return;
      }
      tagFpPrimInfo::__as
                (this + iVar2 * 8 + 0x5b0,param_2 + iVar3 * 8 + 0x5b0);
      tagFpPrimInfo::Init(param_2 + iVar3 * 8 + 0x5b0);
      iVar2 = iVar2 + 1;
    }
    iVar3 = iVar3 + 1;
  } while( true );
}

// JP: 0x00304e50  FindLineBlurIndex__10EffectCoreFUi  =  EffectCore::FindLineBlurIndex
int EffectCore::FindLineBlurIndex(int this,int param_2)

{
  int iVar1;
  
  iVar1 = 0;
  while( true ) {
    if (2 < iVar1) {
      return -1;
    }
    if (*(int *)(this + iVar1 * 4 + 0x57c) == param_2) break;
    iVar1 = iVar1 + 1;
  }
  return iVar1;
}

// JP: 0x00304ed0  FindVibIndex__10EffectCoreFUi  =  EffectCore::FindVibIndex
int EffectCore::FindVibIndex(int this,int param_2)

{
  int iVar1;
  
  iVar1 = 0;
  while( true ) {
    if (4 < iVar1) {
      return -1;
    }
    if (*(int *)(this + iVar1 * 8 + 0x588) == param_2) break;
    iVar1 = iVar1 + 1;
  }
  return iVar1;
}

// JP: 0x00310bb0  GetParent__10EffectCoreFv  =  EffectCore::GetParent
undefined4 EffectCore::GetParent(int this)

{
  return this->u32_c;
}
