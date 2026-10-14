// decomp/D/JRing_Tex.c — cleaned Ghidra output (SLPM_602.19, Metrowerks MIPS), Shadow Hearts: Covenant JP demo.
// Field accesses are shown as this->T_off (T = u8/u16/u32/f32/i32/p, off = hex offset);
// JRing fields are named from the recovered struct. See notes/D/*.md for layouts.
// CAVEAT: when the base pointer is a float*/int*/short*, the number in `T_off` is an ELEMENT offset (byte offset = off*sizeof(elem)).
// `this` is the C++ this pointer (param_1); the Metrowerks ABI passes it in a0.

// JP: 0x002fa380  __ct__6JRCTexFUs  =  JRCTex::JRCTex
undefined2 * JRCTex::JRCTex(undefined2 *this,undefined2 param_2)

{
  int iVar1;
  
  *(undefined1 **)(this + 0x42) = JRCTex::__vt;
  GsxRaster::GsxRaster(this + 0x28);
  GsxFrameBuf::GsxFrameBuf(this + 0x34);
  *this = param_2;
  this[1] = 0;
  this[2] = 0;
  for (iVar1 = 0; iVar1 < 0x10; iVar1 = iVar1 + 1) {
    *(undefined4 *)(this + iVar1 * 2 + 6) = 0;
  }
  this->u64_28 = 0;
  this->u64_34 = 0;
  this[5] = 0;
  return this;
}

// JP: 0x002fa450  __dt__6JRCTexFv  =  JRCTex::~JRCTex
int JRCTex::~JRCTex(int this,short param_2)

{
  int iVar1;
  int iVar2;
  
  if (this != 0) {
    *(undefined1 **)(this + 0x84) = JRCTex::__vt;
    this->u64_50 = 0;
    this->u64_68 = 0;
    for (iVar2 = 0; iVar2 < 0x10; iVar2 = iVar2 + 1) {
      if ((*(int *)(this + iVar2 * 4 + 0xc) != 0) &&
         (iVar1 = *(int *)(this + iVar2 * 4 + 0xc), iVar1 != 0)) {
        __dla(iVar1 + -0x10);
      }
    }
    GsxFrameBuf::~GsxFrameBuf(this + 0x68,0xffffffffffffffff);
    GsxRaster::~GsxRaster(this + 0x50,0xffffffffffffffff);
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}

// JP: 0x002fa560  RasterCreate__6JRCTexF6GS_PSMUiUi  =  JRCTex::RasterCreate
void JRCTex::RasterCreate(int this,uint param_2,uint param_3,uint param_4)

{
  byte bVar1;
  int iVar2;
  undefined8 uVar3;
  
  this->u64_50 = 0;
  this->u16_50 = this->u16_50 & 0xc000;
  iVar2 = GetBufferWidth(param_2);
  this->u64_50 =
       this->u64_50 & 0xfffffffffff03fff |
       ((long)(int)((~(iVar2 - 1U) & param_3 + (iVar2 - 1U)) >> 6) & 0x3fU) << 0xe;
  this->u16_52 =
       this->u16_52 & 0xfc0f | (ushort)((param_2 & 0x3f) << 4);
  uVar3 = GetTexWidth(param_3);
  bVar1 = GetTexBit(uVar3);
  this->u8_53 = this->u8_53 & 0xc3 | (bVar1 & 0xf) << 2;
  uVar3 = GetTexWidth(param_4);
  iVar2 = GetTexBit(uVar3);
  this->u64_50 =
       this->u64_50 & 0xfffffffc3fffffff | ((long)iVar2 & 0xfU) << 0x1e;
  this->u16_54 =
       this->u16_54 & 0xc007 | (ushort)((param_3 & 0x7ff) << 3);
  this->u64_50 =
       this->u64_50 & 0xfe003fffffffffff | ((ulong)param_4 & 0x7ff) << 0x2e;
  this->u8_54 = this->u8_54 & 0xfb | 4;
  return;
}

// JP: 0x002fa750  ClutCreate__6JRCTexF6GS_PSMUiUi  =  JRCTex::ClutCreate
void JRCTex::ClutCreate(int this,uint param_2,uint param_3,uint param_4)

{
  byte bVar1;
  ushort uVar2;
  int iVar3;
  undefined8 uVar4;
  
  this->u64_68 = 0;
  uVar2 = ClutAdressControl::getAdress(CApp::app + 0x80,0);
  this->u16_68 = this->u16_68 & 0xc000 | uVar2 & 0x3fff;
  iVar3 = GetBufferWidth(param_2);
  this->u64_68 =
       this->u64_68 & 0xfffffffffff03fff |
       ((long)(int)((~(iVar3 - 1U) & param_3 + (iVar3 - 1U)) >> 6) & 0x3fU) << 0xe;
  this->u16_6a =
       this->u16_6a & 0xfc0f | (ushort)((param_2 & 0x3f) << 4);
  uVar4 = GetTexWidth(param_3);
  bVar1 = GetTexBit(uVar4);
  this->u8_6b = this->u8_6b & 0xc3 | (bVar1 & 0xf) << 2;
  uVar4 = GetTexWidth(param_4);
  iVar3 = GetTexBit(uVar4);
  this->u64_68 =
       this->u64_68 & 0xfffffffc3fffffff | ((long)iVar3 & 0xfU) << 0x1e;
  this->u16_6c =
       this->u16_6c & 0xc007 | (ushort)((param_3 & 0x7ff) << 3);
  this->u64_68 =
       this->u64_68 & 0xfe003fffffffffff | ((ulong)param_4 & 0x7ff) << 0x2e;
  return;
}

// JP: 0x002fa930  Create__6JRCTexFPvUsUsUs  =  JRCTex::Create
undefined4
JRCTex::Create
          (int this,undefined4 *param_2,ushort param_3,undefined2 param_4,undefined2 param_5)

{
  byte bVar1;
  
  this->u16_2 = param_2->u16_1;
  this->u16_4 = *(undefined2 *)((int)param_2 + 6);
  *(undefined4 **)(this + 0x78) = param_2 + 4;
  this->u32_7c =
       this->i32_78 +
       (param_2->u16_3 + 1) * (uint)*(ushort *)((int)param_2 + 10) * 4;
  this->u16_6 = *(undefined2 *)((int)param_2 + 10);
  this->i16_8 = param_2->i16_3 + 1;
  if (param_3 < this->u16_8) {
    this->u16_a = param_3;
  }
  bVar1 = param_2->u8_2 & 7;
  if (((bVar1 != 4) && (bVar1 != 3)) && (bVar1 != 2)) {
    if (bVar1 == 1) {
      JRCTex::Create8BIT(this,param_4,param_5);
    }
    else if ((param_2->u8_2 & 7) == 0) {
      JRCTex::Create4BIT(this,param_4,param_5);
    }
  }
  return *param_2;
}

// JP: 0x002faaa0  Create4BIT__6JRCTexFUsUs  =  JRCTex::Create4BIT
int JRCTex::Create4BIT(int this,undefined2 param_2,undefined2 param_3)

{
  int iVar1;
  
  JRCTex::CreateTexturePacket
            (this,((ulong)this->u16_52 & 0x3ff) >> 4,this->u16_2,
             this->u16_4,param_2,param_3);
  this->u32_80 = 0;
  this->u8_83 = this->u8_83 & 0x87 | 0x20;
  this->u32_80 = this->u32_80 & 0xfffc3fff;
  this->u16_80 =
       this->u16_80 & 0xc000 | this->u16_68 & 0x3fff;
  this->u8_83 = this->u8_83 & 0xf8 | 1;
  iVar1 = (uint)this->u16_2 * (uint)this->u16_4;
  if (iVar1 < 0) {
    iVar1 = iVar1 + 1;
  }
  return this->i32_7c + (iVar1 >> 1);
}

// JP: 0x002fabe0  Create8BIT__6JRCTexFUsUs  =  JRCTex::Create8BIT
int JRCTex::Create8BIT(int this,undefined2 param_2,undefined2 param_3)

{
  JRCTex::CreateTexturePacket
            (this,((ulong)this->u16_52 & 0x3ff) >> 4,this->u16_2,
             this->u16_4,param_2,param_3);
  this->u32_80 = 0;
  this->u8_83 = this->u8_83 & 0x87 | 0x40;
  this->u32_80 = this->u32_80 & 0xfffc3fff;
  this->u16_80 =
       this->u16_80 & 0xc000 | this->u16_68 & 0x3fff;
  this->u8_83 = this->u8_83 & 0xf8 | 1;
  return this->i32_7c + (uint)this->u16_2 * (uint)this->u16_4;
}

// JP: 0x002fad10  CreateTexturePacket__6JRCTexFUcUsUsUsUs  =  JRCTex::CreateTexturePacket
/* WARNING: Removing unreachable block (ram,0x002fad8c) */

void * JRCTex::CreateTexturePacket
                 (int this,char param_2,ushort param_3,ushort param_4,ushort param_5,
                 ushort param_6)

{
  bool bVar1;
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  void *pvVar2;
  int iVar3;
  undefined4 uVar4;
  undefined8 uVar5;
  undefined4 *puVar6;
  int *piVar7;
  uint uVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  int iVar12;
  undefined2 uStack_94;
  int iStack_74;
  
  if (this->u16_6 < 0x11) {
    if (((param_2 == '\x14') || (param_2 == '$')) || (param_2 == ',')) {
      iVar12 = 8;
      iVar11 = 2;
    }
    else {
      iVar12 = 0x10;
      iVar11 = 1;
    }
  }
  else {
    iVar12 = 0x10;
    iVar11 = (int)(uint)this->u16_6 >> 4;
  }
  uVar10 = (uint)(iVar11 * iVar12 * 0x20) >> 7;
  pvVar2 = (void *)GetPSMtoBPP(param_2);
  uVar8 = ((uint)param_3 * (uint)param_4 * (int)pvVar2 + 7 >> 3) + 0xf >> 4;
  bVar1 = uVar8 < 0x8000;
  if (bVar1) {
    iStack_74 = 0;
  }
  else {
    iStack_74 = 2;
  }
  for (iVar9 = 0; iVar9 < (int)(uint)this->u16_8; iVar9 = iVar9 + 1) {
    iVar3 = iStack_74 + 9 + uVar10 + 7;
    uVar5 = __nwa(iVar3 * 0x10 + 0x10);
    uVar4 = __construct_new_array(uVar5,0x224b30,0,0x10,iVar3);
    *(undefined4 *)(this + iVar9 * 4 + 0xc) = uVar4;
    piVar7 = *(int **)(this + iVar9 * 4 + 0xc);
    *piVar7 = uVar10 + 0x10000006;
    piVar7[2] = 0x10000000;
    piVar7[3] = uVar10 + 0x50000006;
    piVar7[4] = 4;
    piVar7[5] = 0x10000000;
    piVar7[6] = 0xe;
    piVar7[7] = 0;
    piVar7->u64_8 =
         (ulong)(CONCAT13((byte)(((ulong)this->u16_6a << 0x36) >> 0x3a),
                          CONCAT12((char)((this->u64_68 & 0xfffff) >> 0xe),
                                   this->u16_68)) & 0xffff3fff) << 0x20;
    piVar7[10] = 0x50;
    piVar7[0xb] = 0;
    piVar7[0xc] = 0;
    piVar7[0xd] = 0;
    piVar7[0xe] = 0x51;
    piVar7[0xf] = 0;
    uStack_94 = (undefined2)iVar11;
    piVar7->u64_10 = (ulong)CONCAT24(uStack_94,iVar12);
    piVar7[0x12] = 0x52;
    piVar7[0x13] = 0;
    piVar7[0x14] = 0;
    piVar7[0x15] = 0;
    piVar7[0x16] = 0x53;
    piVar7[0x17] = 0;
    piVar7->i64_18 = (long)(int)uVar10 + 0x800000000008000;
    pvVar2 = memcpy(piVar7 + 0x1c,
                    (void *)(this->i32_78 + iVar9 * (uint)this->u16_6 * 4),
                    (long)(int)(uVar10 << 4));
    puVar6 = (undefined4 *)(*(int *)(this + iVar9 * 4 + 0xc) + (uVar10 + 7) * 0x10);
    *puVar6 = in_zero_lo;
    puVar6[1] = in_zero_hi;
    puVar6[2] = in_zero_udw;
    puVar6[3] = in_register_0000000c;
    *puVar6 = 0x10000006;
    puVar6[2] = 0x10000000;
    puVar6[3] = 0x50000006;
    puVar6->u64_4 = 0x1000000000000004;
    puVar6->u64_6 = 0xe;
    puVar6->u64_8 =
         (ulong)(CONCAT13(param_2,CONCAT12((char)((this->u64_50 & 0xfffff) >> 0xe),
                                           this->u16_50)) & 0xffff3fff) << 0x20;
    puVar6->u64_a = 0x50;
    puVar6->u64_c = (ulong)param_5 << 0x20 | (ulong)param_6 << 0x30;
    puVar6->u64_e = 0x51;
    puVar6->u64_10 = (ulong)CONCAT24(param_4,(uint)param_3);
    puVar6->u64_12 = 0x52;
    puVar6->u64_14 = 0;
    puVar6->u64_16 = 0x53;
    if (bVar1) {
      puVar6->u64_18 = (ulong)uVar8 + 0x800000000008000;
    }
    else {
      puVar6->i64_18 = 0x800000000007fff;
    }
    piVar7 = puVar6 + 0x1c;
    iVar3 = this->i32_7c;
    if (!bVar1) {
      *piVar7 = 0x30007fff;
      puVar6[0x1d] = iVar3;
      puVar6[0x1e] = 0;
      puVar6[0x1f] = 0x50007fff;
      uVar8 = uVar8 - 0x7fff;
      iVar3 = iVar3 + 0x7fff0;
      puVar6[0x20] = &DAT_10000001;
      puVar6[0x22] = 0;
      puVar6[0x23] = 0x50000001;
      puVar6->u64_24 = (ulong)uVar8 + 0x800000000008000;
      piVar7 = puVar6 + 0x28;
    }
    *piVar7 = uVar8 + 0x30000000;
    piVar7[1] = iVar3;
    piVar7[2] = 0;
    piVar7[3] = uVar8 + 0x50000000;
    piVar7[4] = 0x60000000;
    piVar7[6] = 0;
    piVar7[7] = 0;
  }
  return pvVar2;
}

// JP: 0x002fb2f0  GetTex0__6JRCTexFb  =  JRCTex::GetTex0
ulong JRCTex::GetTex0(int this,char param_2)

{
  uint uVar1;
  undefined1 in_zero_qw [16];
  int iVar2;
  int iVar3;
  undefined8 uVar4;
  undefined8 extraout_v0_udw;
  undefined1 auVar5 [16];
  ulong uVar6;
  
  uVar1 = this->u32_80;
  uVar6 = this->u64_50;
  uVar4 = GetTexWidth(this->u16_2);
  iVar2 = GetTexBit(uVar4);
  uVar4 = GetTexWidth(this->u16_4);
  iVar3 = GetTexBit(uVar4);
  auVar5._8_8_ = extraout_v0_udw;
  auVar5._0_8_ = 0xfffffffc03ffffff;
  auVar5 = _pcpyld(in_zero_qw,auVar5);
  uVar6 = (uVar6 & 0x7ffffffff | (ulong)uVar1 << 0x25) & auVar5._0_8_ | (long)iVar2 << 0x1a |
          (long)iVar3 << 0x1e;
  if (param_2 != '\0') {
    uVar6 = uVar6 | 0x400000000;
  }
  return uVar6;
}

// JP: 0x002fb420  ChangeClut__6JRCTexFUs  =  JRCTex::ChangeClut
void JRCTex::ChangeClut(int this,ushort param_2)

{
  if (param_2 < this->u16_8) {
    this->u16_a = param_2;
  }
  return;
}
