// decomp/D/LsdEffectServer.c — cleaned Ghidra output (SLPM_602.19, Metrowerks MIPS), Shadow Hearts: Covenant JP demo.
// Field accesses are shown as this->T_off (T = u8/u16/u32/f32/i32/p, off = hex offset);
// JRing fields are named from the recovered struct. See notes/D/*.md for layouts.
// CAVEAT: when the base pointer is a float*/int*/short*, the number in `T_off` is an ELEMENT offset (byte offset = off*sizeof(elem)).
// `this` is the C++ this pointer (param_1); the Metrowerks ABI passes it in a0.

// JP: 0x00324b00  __ct__15LsdEffectServerFv  =  LsdEffectServer::LsdEffectServer
int LsdEffectServer::LsdEffectServer(int this)

{
  LSDDeviceHandler::LSDDeviceHandler(this);
  *(undefined1 **)(this + 0x10) = LsdEffectServer::__vt;
  return this;
}

// JP: 0x00324b40  __dt__15LsdEffectServerFv  =  LsdEffectServer::~LsdEffectServer
int LsdEffectServer::~LsdEffectServer(int this,short param_2)

{
  if (this != 0) {
    *(undefined1 **)(this + 0x10) = LsdEffectServer::__vt;
    LSDDeviceHandler::~LSDDeviceHandler(this,0);
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}

// JP: 0x00324bc0  CheckData__15LsdEffectServerFP12_LSDTrackHdr  =  LsdEffectServer::CheckData
bool LsdEffectServer::CheckData(undefined8 this,int *param_2)

{
  return *param_2 == 0x4446452e;
}

// JP: 0x00324c10  Open__15LsdEffectServerFP10RingBuffer  =  LsdEffectServer::Open
undefined8 LsdEffectServer::Open(undefined4 this,undefined4 param_2)

{
  undefined4 uVar1;
  long lVar2;
  undefined8 uVar3;
  undefined4 *puVar4;
  
  lVar2 = __nw(0x40);
  uVar3 = 0;
  if (lVar2 != 0) {
    uVar3 = LsdEffect::LsdEffect(lVar2);
  }
  puVar4 = (undefined4 *)uVar3;
  RingBuffer::getReadData(param_2,puVar4 + 4,0x20,0);
  *puVar4 = puVar4[4];
  puVar4[2] = this;
  puVar4[3] = puVar4;
  lVar2 = __nw(0x10);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = BufMemory::BufMemory(lVar2,puVar4[10] << 4,0x80);
  }
  puVar4[0xd] = uVar1;
  return uVar3;
}

// JP: 0x00324cf0  Read__15LsdEffectServerFP10_LSDHANDLEP10RingBuffer  =  LsdEffectServer::Read
int LsdEffectServer::Read
              (undefined8 this,int param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  long lVar5;
  
  iVar2 = RingBuffer::getReadTopAdress(param_3);
  iVar1 = param_2->i32_c;
  iVar3 = BufMemory::getBuffer(iVar1->u32_34);
  RingBuffer::getReadData
            (param_3,iVar3 + iVar1->i32_38,iVar2->i32_8 << 4,0x10);
  iVar1->i32_38 = iVar1->i32_38 + iVar2->i32_8 * 0x10;
  if ((uint)(iVar1->i32_28 << 4) <= iVar1->u32_38) {
    lVar5 = __nw(0x48);
    uVar4 = 0;
    if (lVar5 != 0) {
      uVar4 = Effect::Effect(lVar5,0,0,0);
    }
    iVar1->u32_30 = uVar4;
    Effect::Create(iVar1->u32_30,iVar1->u32_34);
  }
  return iVar2->i32_8 * 0x10 + 0x10;
}

// JP: 0x00324e50  Event__15LsdEffectServerFP10_LSDHANDLEiff  =  LsdEffectServer::Event
void LsdEffectServer::Event(undefined8 this,int param_2,undefined4 param_3)

{
  int iVar1;
  
  iVar1 = param_2->i32_c;
  if (iVar1->i32_30 != 0) {
    switch(param_3) {
    case 1:
      Effect::Run(iVar1->u32_30);
      break;
    case 2:
      Effect::Stop(iVar1->u32_30);
      break;
    case 3:
      Effect::Continue(iVar1->u32_30);
      break;
    case 4:
      Effect::Stop(iVar1->u32_30);
      break;
    case 5:
      Effect::Stop(iVar1->u32_30);
      break;
    case 6:
      Effect::Continue(iVar1->u32_30);
    }
  }
  return;
}

// JP: 0x00324f50  Close__15LsdEffectServerFP10_LSDHANDLE  =  LsdEffectServer::Close
undefined4 LsdEffectServer::Close(undefined8 this,int param_2)

{
  int iVar1;
  
  iVar1 = param_2->i32_c;
  if (iVar1 != 0) {
    (**(code **)(iVar1->i32_3c + 8))(iVar1,1);
  }
  return 1;
}

// JP: 0x00324fb0  __ct__9LsdEffectFv  =  LsdEffect::LsdEffect
int LsdEffect::LsdEffect(int this)

{
  *(undefined1 **)(this + 0x3c) = LsdEffect::__vt;
  this->u32_30 = 0;
  this->u32_34 = 0;
  this->u32_38 = 0;
  return this;
}

// JP: 0x00324ff0  __dt__9LsdEffectFv  =  LsdEffect::~LsdEffect
int LsdEffect::~LsdEffect(int this,short param_2)

{
  int iVar1;
  
  if (this != 0) {
    *(undefined1 **)(this + 0x3c) = LsdEffect::__vt;
    if (this->i32_30 != 0) {
      iVar1 = this->i32_30;
      if (iVar1 != 0) {
        (**(code **)(iVar1->i32_14 + 8))(iVar1,1);
      }
      this->u32_30 = 0;
    }
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}
