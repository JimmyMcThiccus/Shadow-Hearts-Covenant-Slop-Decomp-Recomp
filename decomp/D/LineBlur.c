// decomp/D/LineBlur.c — cleaned Ghidra output (SLPM_602.19, Metrowerks MIPS), Shadow Hearts: Covenant JP demo.
// Field accesses are shown as this->T_off (T = u8/u16/u32/f32/i32/p, off = hex offset);
// JRing fields are named from the recovered struct. See notes/D/*.md for layouts.
// CAVEAT: when the base pointer is a float*/int*/short*, the number in `T_off` is an ELEMENT offset (byte offset = off*sizeof(elem)).
// `this` is the C++ this pointer (param_1); the Metrowerks ABI passes it in a0.

// JP: 0x0031cb10  SetCenter__8LineBlurFUiUi  =  LineBlur::SetCenter
void LineBlur::SetCenter(int this,undefined4 param_2,undefined4 param_3)

{
  this->u32_1e0c0 = param_2;
  this->u32_1e0c4 = param_3;
  this->u8_1e0dc = 1;
  return;
}

// JP: 0x0031cb70  SetPower__8LineBlurFf  =  LineBlur::SetPower
void LineBlur::SetPower(undefined4 this,int param_2)

{
  param_2->u32_1e0d8 = this;
  param_2->u8_1e0dc = 1;
  return;
}

// JP: 0x00326860  __ct__8LineBlurFv  =  LineBlur::LineBlur
VIF1Prim * LineBlur::LineBlur(VIF1Prim *this)

{
  VIF1Prim *pVVar1;
  byte *pbVar2;
  
  VIF1Prim::VIF1Prim(this);
  DelayDeleteObject::DelayDeleteObject(this + 1);
  this->pVptr = LineBlur::__vt;
  this[1].dwEnv = 0x406c70;
  pbVar2 = &this[1].bFlags;
  do {
    _QWD::_QWD(pbVar2);
    pbVar2 = (byte *)((int)pbVar2 + 0x10);
  } while ((VIF1Prim *)pbVar2 != this + 8);
  pVVar1 = this + 8;
  do {
    _QWD::_QWD(pVVar1);
    pVVar1 = (VIF1Prim *)&pVVar1->pVptr;
  } while (pVVar1 != (VIF1Prim *)&this[0x1809].bFlags);
  LineBlur::Create(this);
  return this;
}

// JP: 0x00326930  __dt__8LineBlurFv  =  LineBlur::~LineBlur
int * LineBlur::~LineBlur(int *this,short param_2)

{
  if (this != (int *)0x0) {
    this[4] = (int)LineBlur::__vt;
    this[7] = 0x406c70;
    if (*this != 0) {
      __dla(*this);
      *this = 0;
    }
    if (this[1] != 0) {
      __dla(this[1]);
      this[1] = 0;
    }
    DelayDeleteObject::~DelayDeleteObject(this + 5,0);
    VIF1Prim::~VIF1Prim(this,0);
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}

// JP: 0x00326a20  Create__8LineBlurFv  =  LineBlur::Create
void * LineBlur::Create(undefined4 *this)

{
  undefined4 uVar1;
  void *pvVar2;
  
  this[0x7830] = 0x100;
  this[0x7831] = 0xe0;
  this[0x7832] = 0;
  this[0x7833] = 0x200;
  this[0x7834] = 0;
  this[0x7835] = 0x1c0;
  this[0x7836] = 0x3f800000;
  this->u8_7837 = 0;
  memset(this + 8,0,0x80);
  this[8] = 0x60000007;
  this[0xb] = 0x50000007;
  this->u64_c = 0x1000000000008006;
  this->u64_e = 0xe;
  this->u64_10 = 0x70000;
  this->u64_12 = 0x47;
  this->u64_14 = 0x48929292;
  this->u64_16 = 1;
  this->u64_18 = 1;
  this->u64_1a = 0x14;
  this->u64_1c = 5;
  this->u64_1e = 8;
  this->u64_20 = 0x44;
  this->u64_22 = 0x42;
  memset(this + 0x28,0,0x1e020);
  this[0x28] = 0x60001e01;
  this[0x2b] = 0x50001e01;
  this->u64_2c = 0x40a8c00000008780;
  this->u64_2e = 0x5353;
  uVar1 = __nwa(0xa0);
  *this = uVar1;
  uVar1 = __nwa(0xa0);
  this[1] = uVar1;
  memset((void *)*this,0,0xa0);
  pvVar2 = memset((void *)this[1],0,0xa0);
  return pvVar2;
}

// JP: 0x00326c70  getPacket__8LineBlurFv  =  LineBlur::getPacket
/* WARNING: Removing unreachable block (ram,0x00326d2c) */

undefined4 LineBlur::getPacket(int this)

{
  byte bVar1;
  byte bVar2;
  ushort uVar3;
  undefined4 *puVar4;
  ulong uVar5;
  ulong uVar6;
  
  puVar4 = *(undefined4 **)(this + (VIF1Prim::m_Env & 1) * 4);
  *puVar4 = 0x50000000;
  puVar4[1] = this + 0x20;
  puVar4[3] = 0x13000000;
  puVar4[4] = &DAT_10000002;
  puVar4[7] = 0x50000002;
  puVar4->u64_8 = 0x1000000000008001;
  puVar4->u64_a = 0xe;
  uVar3 = *(ushort *)(CApp::camera + (uint)CApp::camera->u8_394 * 2 + 0x38c);
  bVar1 = CApp::camera->u8_52;
  bVar2 = CApp::camera->u8_53;
  uVar5 = GetBekijo(0x200);
  uVar6 = GetBekijo(0x1c0);
  puVar4->u64_c =
       ((ulong)bVar2 & 0x3f) << 0x14 |
       ((ulong)bVar1 & 0x3f) << 0xe | (long)((int)((uint)uVar3 * 0x800) >> 6) |
       (uVar5 & 0xffffffff) << 0x1a | (uVar6 & 0xffffffff) << 0x1e;
  puVar4->u64_e = 6;
  puVar4[0x10] = 0x50000000;
  puVar4[0x11] = this + 0xa0;
  puVar4[0x14] = 0x60000000;
  if (this->i8_1e0dc != '\0') {
    LineBlur::ChangeLine(this);
    this->u8_1e0dc = 0;
  }
  return *(undefined4 *)(this + (VIF1Prim::m_Env & 1) * 4);
}

// JP: 0x00326e30  SetPacket__8LineBlurFP4_QWD  =  LineBlur::SetPacket
/* WARNING: Removing unreachable block (ram,0x00326f08) */

undefined4 * LineBlur::SetPacket(int this,undefined4 *param_2)

{
  byte bVar1;
  byte bVar2;
  ushort uVar3;
  ulong uVar4;
  ulong uVar5;
  
  *param_2 = 0x50000000;
  param_2[1] = this + 0x20;
  param_2[3] = 0x13000000;
  param_2[4] = &DAT_10000002;
  param_2[7] = 0x50000002;
  param_2->u64_8 = 0x1000000000008001;
  param_2->u64_a = 0xe;
  uVar3 = *(ushort *)(CApp::camera + (uint)CApp::camera->u8_394 * 2 + 0x38c);
  bVar1 = CApp::camera->u8_52;
  bVar2 = CApp::camera->u8_53;
  uVar4 = GetBekijo(0x200);
  uVar5 = GetBekijo(0x1c0);
  param_2->u64_c =
       ((ulong)bVar2 & 0x3f) << 0x14 |
       ((ulong)bVar1 & 0x3f) << 0xe | (long)((int)((uint)uVar3 * 0x800) >> 6) |
       (uVar4 & 0xffffffff) << 0x1a | (uVar5 & 0xffffffff) << 0x1e;
  param_2->u64_e = 6;
  param_2[0x10] = 0x50000000;
  param_2[0x11] = this + 0xa0;
  if (this->i8_1e0dc != '\0') {
    LineBlur::ChangeLine(this);
    this->u8_1e0dc = 0;
  }
  return param_2 + 0x14;
}

// JP: 0x00327010  ChangeLine__8LineBlurFv  =  LineBlur::ChangeLine
void LineBlur::ChangeLine(int this)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  iVar6 = this->i32_1e0c0 << 4;
  iVar5 = this->i32_1e0c4 << 4;
  iVar4 = (this->i32_1e0c0 + 0x700) * 0x10;
  iVar3 = (this->i32_1e0c4 + 0x720) * 0x10;
  piVar1 = (int *)(this + 0xc0);
  for (uVar2 = this->u32_1e0c8; uVar2 < this->u32_1e0cc; uVar2 = uVar2 + 1
      ) {
    *piVar1 = iVar6;
    piVar1[1] = iVar5;
    piVar1[4] = iVar4;
    piVar1[5] = iVar3;
    piVar1[6] = -1;
    LineBlur::GetUV
              (this,uVar2,this->u32_1e0d0,piVar1 + 8,piVar1 + 9);
    piVar1[0xc] = (uVar2 + 0x700) * 0x10;
    piVar1[0xd] = (this->i32_1e0d0 + 0x720) * 0x10;
    piVar1[0xe] = -1;
    piVar1 = piVar1 + 0x10;
  }
  for (uVar2 = this->u32_1e0c8; uVar2 < this->u32_1e0cc; uVar2 = uVar2 + 1
      ) {
    *piVar1 = iVar6;
    piVar1[1] = iVar5;
    piVar1[4] = iVar4;
    piVar1[5] = iVar3;
    piVar1[6] = -1;
    LineBlur::GetUV
              (this,uVar2,this->u32_1e0d4,piVar1 + 8,piVar1 + 9);
    piVar1[0xc] = (uVar2 + 0x700) * 0x10;
    piVar1[0xd] = (this->i32_1e0d4 + 0x720) * 0x10;
    piVar1[0xe] = -1;
    piVar1 = piVar1 + 0x10;
  }
  for (uVar2 = this->u32_1e0d0; uVar2 < this->u32_1e0d4; uVar2 = uVar2 + 1
      ) {
    *piVar1 = iVar6;
    piVar1[1] = iVar5;
    piVar1[4] = iVar4;
    piVar1[5] = iVar3;
    piVar1[6] = -1;
    LineBlur::GetUV
              (this,this->u32_1e0c8,uVar2,piVar1 + 8,piVar1 + 9);
    piVar1[0xc] = (this->i32_1e0c8 + 0x700) * 0x10;
    piVar1[0xd] = (uVar2 + 0x720) * 0x10;
    piVar1[0xe] = -1;
    piVar1 = piVar1 + 0x10;
  }
  for (uVar2 = this->u32_1e0d0; uVar2 < this->u32_1e0d4; uVar2 = uVar2 + 1
      ) {
    *piVar1 = iVar6;
    piVar1[1] = iVar5;
    piVar1[4] = iVar4;
    piVar1[5] = iVar3;
    piVar1[6] = -1;
    LineBlur::GetUV
              (this,this->u32_1e0cc,uVar2,piVar1 + 8,piVar1 + 9);
    piVar1[0xc] = (this->i32_1e0cc + 0x700) * 0x10;
    piVar1[0xd] = (uVar2 + 0x720) * 0x10;
    piVar1[0xe] = -1;
    piVar1 = piVar1 + 0x10;
  }
  return;
}

// JP: 0x003273c0  GetUV__8LineBlurFUiUiPUiPUi  =  LineBlur::GetUV
void LineBlur::GetUV(int this,uint param_2,uint param_3,uint *param_4,uint *param_5)

{
  float fVar1;
  uint uVar2;
  uint uVar3;
  
  uVar3 = this->u32_1e0c4;
  fVar1 = ((float)this->u32_1e0c0 +
          ((float)param_2 - (float)this->u32_1e0c0) * this->f32_1e0d8) *
          16.0;
  if (fVar1 < 2.1474836e+09) {
    uVar2 = (uint)fVar1;
  }
  else {
    uVar2 = (int)(fVar1 - 2.1474836e+09) | 0x80000000;
  }
  *param_4 = uVar2;
  fVar1 = ((float)this->u32_1e0c4 +
          ((float)param_3 - (float)uVar3) * this->f32_1e0d8) * 16.0;
  if (fVar1 < 2.1474836e+09) {
    uVar3 = (uint)fVar1;
  }
  else {
    uVar3 = (int)(fVar1 - 2.1474836e+09) | 0x80000000;
  }
  *param_5 = uVar3;
  return;
}

// JP: 0x00327670  SetBlurRect__8LineBlurFUiUiUiUi  =  LineBlur::SetBlurRect
void LineBlur::SetBlurRect
               (int this,undefined4 param_2,undefined4 param_3,undefined4 param_4,
               undefined4 param_5)

{
  this->u32_1e0c8 = param_2;
  this->u32_1e0cc = param_3;
  this->u32_1e0d0 = param_4;
  this->u32_1e0d4 = param_5;
  return;
}
