// decomp/D/CGhostEfx.c — cleaned Ghidra output (SLPM_602.19, Metrowerks MIPS), Shadow Hearts: Covenant JP demo.
// Field accesses are shown as this->T_off (T = u8/u16/u32/f32/i32/p, off = hex offset);
// JRing fields are named from the recovered struct. See notes/D/*.md for layouts.
// CAVEAT: when the base pointer is a float*/int*/short*, the number in `T_off` is an ELEMENT offset (byte offset = off*sizeof(elem)).
// `this` is the C++ this pointer (param_1); the Metrowerks ABI passes it in a0.

// JP: 0x003d3f50  __ct__9CGhostEfxFv  =  CGhostEfx::CGhostEfx
undefined4 * CGhostEfx::CGhostEfx(undefined4 *this)

{
  *this = 0;
  this[1] = 0;
  this[0x1f9] = CBBPolygon::__vt;
  SequenceBase::SequenceBase(this + 8);
  SequenceBase::SequenceBase(this + 0xac);
  SequenceBase::SequenceBase(this + 0x150);
  this[2] = 0;
  this[3] = 0;
  this[4] = 0;
  this[500] = 0;
  this[0x1f5] = 0;
  this[0x1f6] = 0;
  this[0x1f9] = CGhostEfx::__vt;
  this->u16_207 = 0;
  this[0x1ff] = 0;
  memset(this + 0x204,0xff,0xc);
  return this;
}

// JP: 0x003d4010  __dt__9CGhostEfxFv  =  CGhostEfx::~CGhostEfx
int CGhostEfx::~CGhostEfx(int this,short param_2)

{
  if (this != 0) {
    *(undefined1 **)(this + 0x7e4) = CGhostEfx::__vt;
    scePrintf(0x402bd0);
    CBBPolygon::~CBBPolygon(this,0);
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}

// JP: 0x003d40a0  Initialization__9CGhostEfxFv  =  CGhostEfx::Initialization
void CGhostEfx::Initialization(void)

{
  return;
}

// JP: 0x003d40b0  NewLifeMake__9CGhostEfxFi  =  CGhostEfx::NewLifeMake
void CGhostEfx::NewLifeMake(void)

{
  return;
}

// JP: 0x003d40c0  AddTime__9CGhostEfxFf  =  CGhostEfx::AddTime
void CGhostEfx::AddTime(float this,int param_2)

{
  int iVar1;
  uint uVar2;
  
  this = this * 100.0;
  if (this < 2.1474836e+09) {
    uVar2 = (uint)this;
  }
  else {
    uVar2 = (int)(this - 2.1474836e+09) | 0x80000000;
  }
  param_2->u32_808 = param_2->i32_808 + uVar2;
  iVar1 = rand();
  param_2->u16_80c = (ushort)iVar1 & 0x3f;
  iVar1 = rand();
  param_2->u16_80e = (ushort)iVar1 & 0x3f;
  return;
}

// JP: 0x003d4180  Create__9CGhostEfxFv  =  CGhostEfx::Create
void CGhostEfx::Create(int this)

{
  undefined4 uVar1;
  uint uVar2;
  undefined8 uVar3;
  int iVar4;
  ushort auStack_20 [8];
  int iStack_10;
  
  if (-1 < (long)((ulong)this->u8_81c << 0x3e)) {
    iStack_10 = this;
    uVar3 = __nwa(0x68);
    uVar1 = __construct_new_array(uVar3,0x3c6b10,0x3c9480,0x2c,2);
    iStack_10->u32_7fc = uVar1;
    iVar4 = iStack_10->i32_7fc;
    *(code **)(iVar4 + 0x24) = CGhostEfx::UpdateS;
    iVar4->i32_28 = iStack_10;
    P2Pkt::Create(iStack_10->u32_7fc,0x18,1);
    P2Pkt::Create(iStack_10->i32_7fc + 0x2c,0x60,1);
    *(undefined **)(iStack_10 + 0x7f0) = &DAT_30a05a46;
    for (iVar4 = 0; iVar4 < 4; iVar4 = iVar4 + 1) {
      uVar2 = rand();
      *(short *)(iStack_10 + iVar4 * 2 + 0x800) = (short)((uVar2 & 0x3f) << 3) + 0xb4;
    }
    iStack_10->u32_808 = 0;
    iStack_10->u32_7f8 = 0x3f800000;
    GsxFrameBuf::GsxFrameBuf(auStack_20);
    GsxFrameBuf::Create(auStack_20,0,1,0x200,0x1c0);
    iStack_10->u32_824 = auStack_20[0] & 0x3fff;
    iStack_10->u8_81c = iStack_10->u8_81c & 0xfd | 2;
    CGhostEfx::MakePacket(iStack_10);
    GsxFrameBuf::~GsxFrameBuf(auStack_20,0xffffffffffffffff);
  }
  return;
}

// JP: 0x003d4350  UpdateS__9CGhostEfxFPv  =  CGhostEfx::UpdateS
void CGhostEfx::UpdateS(undefined4 this)

{
  CGhostEfx::MakePacket(this);
  return;
}

// JP: 0x003d4380  Dsp__9CGhostEfxFi  =  CGhostEfx::Dsp
void CGhostEfx::Dsp(int this)

{
  if ((this->u8_81c & 1) == 0) {
    scePrintf(0x402be0,this->u32_7d0);
    this->u8_81c = this->u8_81c & 0xfe | 1;
    if (-1 < (long)((ulong)this->u8_81c << 0x3e)) {
      CGhostEfx::Create(this);
    }
    World::AddOTBefor
              ((World *)&CApp::m_World,*(VIF1Prim **)(this + 2000),
               *(VIF1Prim **)(this + 0x7fc));
    World::AddOTAfter
              ((World *)&CApp::m_World,*(VIF1Prim **)(this + 2000),
               (VIF1Prim *)(this->i32_7fc + 0x2c));
    *(byte *)(this->i32_7fc + 0x1c) =
         *(byte *)(this->i32_7fc + 0x1c) & 0xfe | 1;
    *(byte *)(this->i32_7fc + 0x48) =
         *(byte *)(this->i32_7fc + 0x48) & 0xfe | 1;
    CGhostEfx::CreateLight(this);
  }
  return;
}

// JP: 0x003d44c0  Clr__9CGhostEfxFv  =  CGhostEfx::Clr
void CGhostEfx::Clr(int this)

{
  if ((this->u8_81c & 1) != 0) {
    scePrintf(0x402bf8);
    this->u8_81c = this->u8_81c & 0xfe;
    *(byte *)(this->i32_7fc + 0x1c) = *(byte *)(this->i32_7fc + 0x1c) & 0xfe
    ;
    *(byte *)(this->i32_7fc + 0x48) = *(byte *)(this->i32_7fc + 0x48) & 0xfe
    ;
    World::ReleaseOT((World *)&CApp::m_World,*(VIF1Prim **)(this + 0x7fc));
    World::ReleaseOT
              ((World *)&CApp::m_World,(VIF1Prim *)(this->i32_7fc + 0x2c));
    CGhostEfx::ReleaseLight(this);
  }
  return;
}

// JP: 0x003d45b0  CreateLight__9CGhostEfxFv  =  CGhostEfx::CreateLight
void CGhostEfx::CreateLight(int this)

{
  undefined8 uVar1;
  undefined8 uVar2;
  long lVar3;
  int iVar4;
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
  int iStack_10;
  
  uStack_20 = 0;
  uStack_1c = 0;
  uStack_18 = 0;
  uStack_14 = 0x3f800000;
  uStack_30 = 0x3ecccccd;
  uStack_2c = 0x3ecccccd;
  uStack_28 = 0x3ecccccd;
  uStack_24 = 0x3f800000;
  iStack_10 = this;
  for (iVar4 = 0; iVar4 < 2; iVar4 = iVar4 + 1) {
    uVar1 = FVector::FVector(auStack_40,&uStack_20);
    uVar2 = FVector::FVector(auStack_50,&uStack_30);
    lVar3 = LightControl::CreatePoint(uVar1,uVar2);
    if (-1 < lVar3) {
      LightControl::changeDeclineType(lVar3,3);
      LightControl::changeActive(lVar3,1);
      LightControl::changeStrength(0x3dcccccd,lVar3);
      *(int *)(iStack_10 + iVar4 * 4 + 0x810) = (int)lVar3;
    }
  }
  return;
}

// JP: 0x003d4710  ReleaseLight__9CGhostEfxFv  =  CGhostEfx::ReleaseLight
void CGhostEfx::ReleaseLight(int this)

{
  int iVar1;
  int iVar2;
  
  for (iVar2 = 0; iVar2 < 3; iVar2 = iVar2 + 1) {
    iVar1 = *(int *)(this + iVar2 * 4 + 0x810);
    if (-1 < iVar1) {
      LightControl::release(iVar1);
      *(undefined4 *)(this + iVar2 * 4 + 0x810) = 0xffffffff;
    }
  }
  return;
}

// JP: 0x003d47a0  UpdateLight__9CGhostEfxF7FVector  =  CGhostEfx::UpdateLight
void CGhostEfx::UpdateLight(int this,undefined4 param_2)

{
  int iVar1;
  undefined8 uVar2;
  int iVar3;
  undefined1 auStack_30 [16];
  int iStack_20;
  undefined4 uStack_10;
  
  iStack_20 = this;
  uStack_10 = param_2;
  for (iVar3 = 0; iVar3 < 2; iVar3 = iVar3 + 1) {
    iVar1 = *(int *)(iStack_20 + iVar3 * 4 + 0x810);
    if (-1 < iVar1) {
      uVar2 = FVector::FVector(auStack_30,uStack_10);
      LightControl::changePos(iVar1,uVar2);
    }
  }
  return;
}

// JP: 0x003d4830  MakePacket__9CGhostEfxFv  =  CGhostEfx::MakePacket
/* WARNING: Removing unreachable block (ram,0x003d4f58) */
/* WARNING: Removing unreachable block (ram,0x003d50b4) */

void CGhostEfx::MakePacket(undefined8 this)

{
  ushort uVar1;
  undefined4 uVar2;
  GsxCamera *this;
  uint uVar3;
  undefined8 *puVar4;
  int iVar5;
  QWD *pQVar6;
  int iVar7;
  undefined8 uVar8;
  P2Pkt *this_00;
  int this;
  float fVar10;
  float fVar11;
  undefined1 auVar12 [16];
  undefined1 auVar13 [16];
  undefined1 auStack_80 [16];
  undefined8 uStack_70;
  undefined4 uStack_68;
  undefined4 uStack_64;
  int aiStack_60 [4];
  undefined1 auStack_50 [16];
  undefined1 auStack_40 [16];
  undefined1 auStack_30 [14];
  undefined2 uStack_22;
  undefined2 uStack_20;
  undefined2 uStack_1e;
  undefined2 uStack_18;
  undefined2 uStack_16;
  undefined2 uStack_8;
  undefined2 uStack_6;
  undefined4 uStack_4;
  
  
  uVar8 = Frame::searchFrame(*(undefined4 *)(this->i32_7d0 + 0x30),FRAME_WAIST);
  Frame::getWorldPos(&uStack_70,uVar8,VIF1Prim::m_Env & 1);
  auStack_40._8_4_ = uStack_68;
  auStack_40._0_8_ = uStack_70;
  auStack_40._12_4_ = uStack_64;
  auVar13 = _lqc2(auStack_40);
  auVar12 = _lqc2(*(undefined1 (*) [16])(GsxCamera::m_pActiveCamera + 0x270));
  auVar12 = _vsub(auVar12,auVar13);
  auStack_50 = _sqc2(auVar12);
  fVar10 = (float)FVector::Length(auStack_50);
  FVector::Normalize(auStack_50);
  FVector::__amu(0x3f000000,auStack_50);
  auVar13 = _lqc2(auStack_50);
  auVar12 = _lqc2(auStack_40);
  auVar12 = _vadd(auVar12,auVar13);
  auStack_40 = _sqc2(auVar12);
  uVar8 = FVector::FVector(auStack_80,auStack_40);
  CGhostEfx::UpdateLight(this,uVar8);
  if ((long)((ulong)*(byte *)(this->i32_7fc + 0x1c) << 0x3e) < 0) {
    uVar3 = VIF1Prim::m_Env & 1;
  }
  else {
    uVar3 = 0;
  }
  *(undefined2 *)(this->i32_7fc + uVar3 * 2 + 0x20) = 0;
  if ((long)((ulong)*(byte *)(this->i32_7fc + 0x48) << 0x3e) < 0) {
    uVar3 = VIF1Prim::m_Env & 1;
  }
  else {
    uVar3 = 0;
  }
  *(undefined2 *)(this->i32_7fc + uVar3 * 2 + 0x4c) = 0;
  this = CApp::camera;
  if (CApp::camera == (GsxCamera *)0x0) {
    P2Pkt::Terminate(this->u32_7fc);
    P2Pkt::Terminate(this->i32_7fc + 0x2c);
  }
  else {
    memset(auStack_30,0,0x1c);
    uVar2 = this->u32_7fc;
    uStack_18 = 0x200;
    uStack_16 = 0x1c0;
    uStack_1e = 1;
    uStack_20 = 8;
    uStack_22 = (undefined2)this->u32_824;
    uVar8 = P2ChangeCamera(0,auStack_30);
    uVar8 = P2Pkt::AddCnt(uVar2,uVar8);
    P2ChangeCamera(uVar8,auStack_30);
    puVar4 = (undefined8 *)P2Pkt::AddCnt(uVar2,2);
    *puVar4 = 0x1000000000008001;
    puVar4[1] = 0xe;
    puVar4[4] = 0x33001;
    puVar4[5] = 0x47;
    uStack_4 = 0;
    puVar4 = (undefined8 *)P2Pkt::AddCnt(uVar2,3);
    *puVar4 = 0x4400000000008001;
    puVar4[1] = 0x4410;
    puVar4[2] = 0x46;
    puVar4[3] = 0x80000000;
    puVar4[4] = CONCAT44(uStack_4,0x72007000);
    uStack_8 = 0x9000;
    uStack_6 = 0x8e00;
    puVar4[5] = CONCAT44(uStack_4,0x8e009000);
    P2Pkt::Terminate(uVar2);
    if (ff_2466 == 0) {
      P2Pkt::Dump0(uVar2);
    }
    this_00 = (P2Pkt *)(this->i32_7fc + 0x2c);
    iVar5 = P2GraTex::GetPktSize(0x402c10);
    pQVar6 = P2Pkt::Add(this_00,iVar5);
    P2GraTex::SetPacket(pQVar6,0x402c10,0);
    puVar4 = (undefined8 *)P2Pkt::AddCnt(this_00,7);
    *puVar4 = 0x1000000000008006;
    puVar4[1] = 0xe;
    puVar4[2] = 0;
    puVar4[3] = 0x3f;
    if (P2Clut::m_refCount == 0) {
      uVar3 = 0;
    }
    else {
      uVar3 = P2Clut::m_raster & 0x3fff;
    }
    iVar5 = pix2tex(0x40);
    iVar7 = pix2tex(0x40);
    puVar4[4] = (long)(int)uVar3 << 0x25 |
                (long)iVar5 << 0x1a | 0x1b20000U | (long)iVar7 << 0x1e | 0x400000000 |
                0x2000000000000000;
    puVar4[5] = 6;
    puVar4[6] = 0;
    puVar4[7] = 0x14;
    puVar4[8] = 0x33001;
    puVar4[9] = 0x47;
    puVar4[10] = 0;
    puVar4[0xb] = 8;
    puVar4[0xc] = 0x42;
    puVar4[0xd] = 0x42;
    SetFullSprite2
              (this_00,0xffffffff80808080,0,this->u16_80c,
               this->u16_80e);
    pQVar6 = P2Pkt::Add(this_00,0);
    iVar5 = GsxCamera::GetRenderTargPkt(this,pQVar6);
    P2Pkt::Add(this_00,iVar5);
    puVar4 = (undefined8 *)P2Pkt::AddCnt(this_00,6);
    *puVar4 = 0x1000000000008005;
    puVar4[1] = 0xe;
    puVar4[2] = 0;
    puVar4[3] = 0x3f;
    puVar4[4] = 0x33001;
    puVar4[5] = 0x47;
    puVar4[6] = 0x60;
    puVar4[7] = 0x14;
    iVar5 = pix2tex(0x200);
    uVar3 = this->u32_824;
    iVar7 = pix2tex(0x1c0);
    puVar4[8] = (ulong)uVar3 | 0x120000 | (long)iVar5 << 0x1a | (long)iVar7 << 0x1e | 0x800000000;
    puVar4[9] = 6;
    puVar4[10] = 0x48;
    puVar4[0xb] = 0x42;
    fVar10 = (4.0 - (fVar10 - 10.0) / 30.0) * 16.0;
    if (fVar10 < 16.0) {
      fVar10 = 16.0;
    }
    if (64.0 < fVar10) {
      fVar10 = 64.0;
    }
    for (iVar5 = 0; iVar5 < 4; iVar5 = iVar5 + 1) {
      uVar1 = *(ushort *)(this + iVar5 * 2 + 0x800);
      if (uVar1 == 0) {
        trap(7);
      }
      fVar11 = sinf(((float)(uint)(this->i32_808 % (int)(uint)uVar1) * 6.283184) /
                    (float)uVar1);
      aiStack_60[iVar5] = (int)(fVar10 * fVar11);
    }
    fVar10 = (float)(this->u32_7f0 >> 0x18) * this->f32_7f8 * 0.75;
    if (2.1474836e+09 <= fVar10) {
      fVar10 = fVar10 - 2.1474836e+09;
    }
    iVar5 = (uint)((ulong)((long)this->i32_7f0 << 0x28) >> 0x28) + (int)fVar10 * 0x1000000
    ;
    SetFullSprite(this_00,iVar5,0,aiStack_60[0],0);
    SetFullSprite(this_00,iVar5,0,-aiStack_60[1],0);
    SetFullSprite(this_00,iVar5,0,0,aiStack_60[2]);
    SetFullSprite(this_00,iVar5,0,0,-aiStack_60[3]);
    puVar4 = (undefined8 *)P2Pkt::AddCnt(this_00,2);
    *puVar4 = 0x1000000000008001;
    puVar4[1] = 0xe;
    puVar4[2] = 0;
    puVar4[3] = 0x14;
    fVar10 = (float)(this->u32_7f0 >> 0x18) * this->f32_7f8;
    if (2.1474836e+09 <= fVar10) {
      fVar10 = fVar10 - 2.1474836e+09;
    }
    SetFullSprite(this_00,(int)fVar10 << 0x18 | 0x808080,0,0,0);
    P2Pkt::Terminate(this_00);
    if (ff_2466 == 0) {
      P2Pkt::Dump0(this_00);
    }
    ff_2466 = 1;
  }
  return;
}

// JP: 0x003d53c0  dip__9CGhostEfxFi  =  CGhostEfx::dip
void CGhostEfx::dip(undefined4 this,undefined4 param_2)

{
  CGhostEfx::Dsp(this,param_2);
  return;
}
