// decomp/D/VEC.c — cleaned Ghidra output (SLPM_602.19, Metrowerks MIPS), Shadow Hearts: Covenant JP demo.
// Field accesses are shown as this->T_off (T = u8/u16/u32/f32/i32/p, off = hex offset);
// JRing fields are named from the recovered struct. See notes/D/*.md for layouts.
// CAVEAT: when the base pointer is a float*/int*/short*, the number in `T_off` is an ELEMENT offset (byte offset = off*sizeof(elem)).
// `this` is the C++ this pointer (param_1); the Metrowerks ABI passes it in a0.

// JP: 0x002fc0c0  __ct__3VECFiP10EffectCorei  =  VEC::VEC
int VEC::VEC(int this,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  long lVar2;
  
  CList::CList(this);
  *(undefined1 **)(this + 0x250) = VEC::__vt;
  this->u32_244 = param_4;
  this->u32_c = 0;
  this->u32_10 = 0;
  this->u32_14 = 0;
  this->u32_21c = 0;
  this->u32_8 = param_2;
  this->u32_240 = 0;
  this->u32_234 = 0;
  lVar2 = __nw(0x10);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = BufMemory::BufMemory(lVar2,40000,0x10);
  }
  this->u32_70 = uVar1;
  uVar1 = BufMemory::getBuffer(this->u32_70);
  this->u32_74 = uVar1;
  this->u32_6c = 0;
  this->u32_18 = 0;
  this->u32_230 = param_3;
  this->u8_220 = 0;
  this->u8_221 = 0;
  this->u32_208 = 0;
  this->u32_20c = 0;
  this->u32_210 = 40000;
  this->u32_214 = 0;
  this->u32_218 = 0;
  this->u32_224 = 0;
  this->u32_228 = 0;
  this->u8_22c = 0;
  this->u8_24c = 0;
  tagEffectLoadWait::Init(this + 0x238);
  return this;
}

// JP: 0x002fc260  __dt__3VECFv  =  VEC::~VEC
int * VEC::~VEC(int *this,short param_2)

{
  int iVar1;
  
  if (this != (int *)0x0) {
    this[0x94] = (int)VEC::__vt;
    if (this[0x1c] != 0) {
      BufMemory::~BufMemory(this[0x1c],1);
      this[0x1c] = 0;
    }
    if (*this != 0) {
      iVar1 = *this;
      if (iVar1 != 0) {
        (**(code **)(iVar1->i32_250 + 8))(iVar1,1);
      }
      *this = 0;
    }
    CList::~CList(this,0);
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}

// JP: 0x002fc350  Start__3VECFv  =  VEC::Start
undefined8 VEC::Start(int this)

{
  this->u32_c = this->u32_8;
  this->u32_18 = 1;
  return 0;
}

// JP: 0x002fc390  Continue__3VECFv  =  VEC::Continue
undefined8 VEC::Continue(int this)

{
  undefined8 uVar1;
  
  if ((this->i32_18 == -1) || (this->i32_18 == 3)) {
    uVar1 = 0;
  }
  else {
    this->u32_18 = 1;
    uVar1 = VEC::DecodeVSM(this);
  }
  return uVar1;
}

// JP: 0x002fc400  DecodeVSM__3VECFv  =  VEC::DecodeVSM
undefined4 VEC::DecodeVSM(int this)

{
  byte bVar1;
  char cVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  undefined4 uVar6;
  long lVar7;
  undefined8 uVar8;
  uint uVar9;
  undefined1 *puStack_18;
  undefined1 *puStack_14;
  
switchD_002fc6b0_caseD_0:
  if (this->i32_18 != 1) {
    return 0xffffffff;
  }
  if ((this->i32_c < 0) || (0x1fff < this->i32_c)) {
    printf(_2579,this->u32_c);
    this->u32_18 = 0xffffffff;
    return 0xffffffff;
  }
  if ((99 < this->i32_10) || (this->i32_10 < 0)) {
    printf(_2580,this->u32_10,this->u32_c);
    this->u32_18 = 0xffffffff;
    return 0xffffffff;
  }
  if (this->i8_221 != '\0') {
    if (this->i8_22c == '\0') {
      return 1;
    }
    if (this->i32_228 != 0) {
      return 1;
    }
    this->u8_221 = 0;
    this->u32_248 = 0;
    this->u32_228 = 0;
    this->u8_22c = 0;
  }
  lVar7 = VEC::IsMotionWait(this);
  if (lVar7 != 0) {
    return 1;
  }
  if (((this->u8_238 & 1) != 0) &&
     (-1 < (long)((ulong)this->u8_238 << 0x3e))) {
    return 1;
  }
  bVar1 = *(byte *)(this->i32_6c + this->i32_c * 8);
  uVar4 = *(uint *)(this->i32_6c + this->i32_c * 8 + 4);
  iVar5 = this->i32_c;
  this->i32_c = iVar5 + 1;
  if (*(char *)(this->i32_6c + iVar5 * 8 + 1) != '\0') {
    uVar4 = uVar4 + this->i32_14;
  }
  this->i32_208 = this->i32_208 + 1;
  if (this->i32_20c < this->i32_10) {
    this->u32_20c = this->u32_10;
  }
  switch(bVar1) {
  case 0:
    goto switchD_002fc6b0_caseD_0;
  case 1:
    iVar5 = *(int *)(this + (this->i32_10 + -1) * 4 + 0x78);
    uVar6 = *(undefined4 *)(this + this->i32_10 * 4 + 0x78);
    *(undefined4 *)(this + (this->i32_10 + -1) * 4 + 0x78) = uVar6;
    *(char *)(this->i32_74 + iVar5) = (char)uVar6;
    break;
  case 2:
    iVar5 = this->i32_74;
    iVar3 = *(int *)(this + (this->i32_10 + -1) * 4 + 0x78);
    uVar6 = *(undefined4 *)(this + this->i32_10 * 4 + 0x78);
    *(undefined4 *)(this + (this->i32_10 + -1) * 4 + 0x78) = uVar6;
    *(undefined4 *)(iVar5 + iVar3) = uVar6;
    break;
  case 3:
    iVar5 = this->i32_74;
    iVar3 = *(int *)(this + (this->i32_10 + -1) * 4 + 0x78);
    uVar6 = *(undefined4 *)(this + this->i32_10 * 4 + 0x78);
    *(undefined4 *)(this + (this->i32_10 + -1) * 4 + 0x78) = uVar6;
    *(undefined4 *)(iVar5 + iVar3) = uVar6;
    break;
  case 4:
    *(int *)(this + (this->i32_10 + -1) * 4 + 0x78) =
         *(int *)(this + (this->i32_10 + -1) * 4 + 0x78) +
         *(int *)(this + this->i32_10 * 4 + 0x78);
    break;
  case 5:
    *(float *)(this + (this->i32_10 + -1) * 4 + 0x78) =
         *(float *)(this + (this->i32_10 + -1) * 4 + 0x78) +
         *(float *)(this + this->i32_10 * 4 + 0x78);
    break;
  case 6:
    iVar5 = this + this->i32_10 * 4;
    iVar5->u32_78 = iVar5->i32_78 + uVar4;
    goto switchD_002fc6b0_caseD_0;
  case 7:
    *(int *)(this + (this->i32_10 + -1) * 4 + 0x78) =
         *(int *)(this + (this->i32_10 + -1) * 4 + 0x78) -
         *(int *)(this + this->i32_10 * 4 + 0x78);
    break;
  case 8:
    *(float *)(this + (this->i32_10 + -1) * 4 + 0x78) =
         *(float *)(this + (this->i32_10 + -1) * 4 + 0x78) -
         *(float *)(this + this->i32_10 * 4 + 0x78);
    break;
  case 9:
    iVar5 = this + this->i32_10 * 4;
    iVar5->u32_78 = iVar5->i32_78 - uVar4;
    goto switchD_002fc6b0_caseD_0;
  case 10:
    *(int *)(this + (this->i32_10 + -1) * 4 + 0x78) =
         *(int *)(this + (this->i32_10 + -1) * 4 + 0x78) *
         *(int *)(this + this->i32_10 * 4 + 0x78);
    break;
  case 0xb:
    *(float *)(this + (this->i32_10 + -1) * 4 + 0x78) =
         *(float *)(this + (this->i32_10 + -1) * 4 + 0x78) *
         *(float *)(this + this->i32_10 * 4 + 0x78);
    break;
  case 0xc:
    iVar5 = this + this->i32_10 * 4;
    iVar5->u32_78 = iVar5->i32_78 * uVar4;
    goto switchD_002fc6b0_caseD_0;
  case 0xd:
    if (*(int *)(this + this->i32_10 * 4 + 0x78) == 0) {
      printf(_2581,this->i32_c + -1);
      return 0xffffffff;
    }
    iVar5 = *(int *)(this + this->i32_10 * 4 + 0x78);
    if (iVar5 == 0) {
      trap(7);
    }
    *(int *)(this + (this->i32_10 + -1) * 4 + 0x78) =
         *(int *)(this + (this->i32_10 + -1) * 4 + 0x78) / iVar5;
    break;
  case 0xe:
    if (*(float *)(this + this->i32_10 * 4 + 0x78) == 0.0) {
      printf(_2581,this->i32_c + -1);
      return 0xffffffff;
    }
    *(float *)(this + (this->i32_10 + -1) * 4 + 0x78) =
         *(float *)(this + (this->i32_10 + -1) * 4 + 0x78) /
         *(float *)(this + this->i32_10 * 4 + 0x78);
    break;
  case 0xf:
    iVar5 = this + this->i32_10 * 4;
    if (uVar4 == 0) {
      trap(7);
    }
    iVar5->i32_78 = iVar5->i32_78 / (int)uVar4;
    goto switchD_002fc6b0_caseD_0;
  case 0x10:
    if (*(int *)(this + this->i32_10 * 4 + 0x78) == 0) {
      printf(_2581,this->i32_c + -1);
      return 0xffffffff;
    }
    iVar5 = *(int *)(this + this->i32_10 * 4 + 0x78);
    if (iVar5 == 0) {
      trap(7);
    }
    *(int *)(this + (this->i32_10 + -1) * 4 + 0x78) =
         *(int *)(this + (this->i32_10 + -1) * 4 + 0x78) % iVar5;
    break;
  default:
    goto switchD_002fc6b0_caseD_11;
  case 0x12:
    iVar5 = this + this->i32_10 * 4;
    if (uVar4 == 0) {
      trap(7);
    }
    iVar5->i32_78 = iVar5->i32_78 % (int)uVar4;
    goto switchD_002fc6b0_caseD_0;
  case 0x13:
    *(int *)(this + this->i32_10 * 4 + 0x78) =
         -*(int *)(this + this->i32_10 * 4 + 0x78);
    goto switchD_002fc6b0_caseD_0;
  case 0x14:
    *(float *)(this + this->i32_10 * 4 + 0x78) =
         -*(float *)(this + this->i32_10 * 4 + 0x78);
    goto switchD_002fc6b0_caseD_0;
  case 0x15:
    if (*(int *)(this + (this->i32_10 + -1) * 4 + 0x78) <
        *(int *)(this + this->i32_10 * 4 + 0x78)) {
      uVar4 = 0xffffffff;
    }
    else {
      uVar4 = (uint)(*(int *)(this + this->i32_10 * 4 + 0x78) <
                    *(int *)(this + (this->i32_10 + -1) * 4 + 0x78));
    }
    *(uint *)(this + (this->i32_10 + -1) * 4 + 0x78) = uVar4;
    break;
  case 0x16:
    if (*(float *)(this + (this->i32_10 + -1) * 4 + 0x78) <
        *(float *)(this + this->i32_10 * 4 + 0x78)) {
      uVar4 = 0xffffffff;
    }
    else {
      uVar4 = (uint)(*(float *)(this + this->i32_10 * 4 + 0x78) <
                    *(float *)(this + (this->i32_10 + -1) * 4 + 0x78));
    }
    *(float *)(this + (this->i32_10 + -1) * 4 + 0x78) = (float)(int)uVar4;
    break;
  case 0x17:
    if (*(int *)(this + this->i32_10 * 4 + 0x78) < (int)uVar4) {
      uVar4 = 0xffffffff;
    }
    else {
      uVar4 = (uint)((int)uVar4 < *(int *)(this + this->i32_10 * 4 + 0x78));
    }
    *(uint *)(this + this->i32_10 * 4 + 0x78) = uVar4;
    goto switchD_002fc6b0_caseD_0;
  case 0x18:
    this->i32_10 = this->i32_10 + 1;
    __as__Q23VEC4OpdSFRCQ23VEC4OpdS
              (this + this->i32_10 * 4 + 0x78,
               this + (this->i32_10 + -1) * 4 + 0x78);
    goto switchD_002fc6b0_caseD_0;
  case 0x19:
    cVar2 = *(char *)(this->i32_74 + uVar4);
    iVar5 = this->i32_10 + 1;
    this->i32_10 = iVar5;
    *(int *)(this + iVar5 * 4 + 0x78) = (int)cVar2;
    goto switchD_002fc6b0_caseD_0;
  case 0x1a:
    uVar6 = *(undefined4 *)(this->i32_74 + uVar4);
    iVar5 = this->i32_10 + 1;
    this->i32_10 = iVar5;
    *(undefined4 *)(this + iVar5 * 4 + 0x78) = uVar6;
    goto switchD_002fc6b0_caseD_0;
  case 0x1b:
    uVar6 = *(undefined4 *)(this->i32_74 + uVar4);
    iVar5 = this->i32_10 + 1;
    this->i32_10 = iVar5;
    *(undefined4 *)(this + iVar5 * 4 + 0x78) = uVar6;
    goto switchD_002fc6b0_caseD_0;
  case 0x1c:
    iVar5 = this->i32_10 + 1;
    this->i32_10 = iVar5;
    *(uint *)(this + iVar5 * 4 + 0x78) = uVar4;
    goto switchD_002fc6b0_caseD_0;
  case 0x1d:
    *(int *)(this + this->i32_10 * 4 + 0x78) =
         (int)*(char *)(this->i32_74 +
                       *(int *)(this + this->i32_10 * 4 + 0x78));
    goto switchD_002fc6b0_caseD_0;
  case 0x1e:
    *(undefined4 *)(this + this->i32_10 * 4 + 0x78) =
         *(undefined4 *)
          (this->i32_74 + *(int *)(this + this->i32_10 * 4 + 0x78));
    goto switchD_002fc6b0_caseD_0;
  case 0x1f:
    *(undefined4 *)(this + this->i32_10 * 4 + 0x78) =
         *(undefined4 *)
          (this->i32_74 + *(int *)(this + this->i32_10 * 4 + 0x78));
    goto switchD_002fc6b0_caseD_0;
  case 0x20:
    break;
  case 0x21:
    *(char *)(this->i32_74 + uVar4) =
         (char)*(undefined4 *)(this + this->i32_10 * 4 + 0x78);
    break;
  case 0x22:
    *(undefined4 *)(this->i32_74 + uVar4) =
         *(undefined4 *)(this + this->i32_10 * 4 + 0x78);
    break;
  case 0x23:
    *(undefined4 *)(this->i32_74 + uVar4) =
         *(undefined4 *)(this + this->i32_10 * 4 + 0x78);
    break;
  case 0x24:
    this->u32_14 = uVar4;
    goto switchD_002fc6b0_caseD_0;
  case 0x25:
    uVar4 = this->i32_14 + uVar4;
    this->u32_14 = uVar4;
    if (40000 < uVar4) {
      printf(_2582);
      this->u32_18 = 0xffffffff;
      return 0xfffffffe;
    }
    goto switchD_002fc6b0_caseD_0;
  case 0x26:
    iVar5 = this->i32_14 - uVar4;
    this->i32_14 = iVar5;
    if (iVar5 < this->i32_210) {
      if (this->i32_14 <= this->i32_21c) {
        printf(_2582);
        this->u32_18 = 0xffffffff;
        return 0xfffffffe;
      }
      this->u32_210 = this->u32_14;
    }
    goto switchD_002fc6b0_caseD_0;
  case 0x27:
    *(float *)(this + this->i32_10 * 4 + 0x78) =
         (float)*(int *)(this + this->i32_10 * 4 + 0x78);
    goto switchD_002fc6b0_caseD_0;
  case 0x28:
    *(int *)(this + this->i32_10 * 4 + 0x78) =
         (int)*(float *)(this + this->i32_10 * 4 + 0x78);
    goto switchD_002fc6b0_caseD_0;
  case 0x29:
    this->u32_c = uVar4;
    goto switchD_002fc6b0_caseD_0;
  case 0x2a:
    iVar5 = this->i32_10;
    this->i32_10 = iVar5 + -1;
    if (*(int *)(this + iVar5 * 4 + 0x78) < 0) {
      this->u32_c = uVar4;
    }
    goto switchD_002fc6b0_caseD_0;
  case 0x2b:
    iVar5 = this->i32_10;
    this->i32_10 = iVar5 + -1;
    if (*(int *)(this + iVar5 * 4 + 0x78) < 1) {
      this->u32_c = uVar4;
    }
    goto switchD_002fc6b0_caseD_0;
  case 0x2c:
    iVar5 = this->i32_10;
    this->i32_10 = iVar5 + -1;
    if (*(int *)(this + iVar5 * 4 + 0x78) == 0) {
      this->u32_c = uVar4;
    }
    goto switchD_002fc6b0_caseD_0;
  case 0x2d:
    iVar5 = this->i32_10;
    this->i32_10 = iVar5 + -1;
    if (*(int *)(this + iVar5 * 4 + 0x78) != 0) {
      this->u32_c = uVar4;
    }
    goto switchD_002fc6b0_caseD_0;
  case 0x2e:
    iVar5 = this->i32_10;
    this->i32_10 = iVar5 + -1;
    if (-1 < *(int *)(this + iVar5 * 4 + 0x78)) {
      this->u32_c = uVar4;
    }
    goto switchD_002fc6b0_caseD_0;
  case 0x2f:
    iVar5 = this->i32_10;
    this->i32_10 = iVar5 + -1;
    if (0 < *(int *)(this + iVar5 * 4 + 0x78)) {
      this->u32_c = uVar4;
    }
    goto switchD_002fc6b0_caseD_0;
  case 0x30:
    iVar5 = this->i32_10 + 1;
    this->i32_10 = iVar5;
    *(undefined4 *)(this + iVar5 * 4 + 0x78) = this->u32_c;
    this->u32_c = uVar4;
    this->i32_218 = this->i32_218 + 1;
    goto switchD_002fc6b0_caseD_0;
  case 0x31:
    iVar5 = this->i32_10;
    this->i32_10 = iVar5 + -1;
    this->u32_c = *(undefined4 *)(this + iVar5 * 4 + 0x78);
    goto switchD_002fc6b0_caseD_0;
  case 0x32:
    if (this->i32_10 != 0) {
      printf(_2584);
      printf(_2585);
      printf(_2584);
    }
    this->u32_18 = 3;
    return 0;
  case 0x33:
    this->i32_10 = this->i32_10 + -3;
    puStack_18 = (undefined1 *)
                 (this->i32_74 +
                 *(int *)(this + (this->i32_10 + 2) * 4 + 0x78));
    puStack_14 = (undefined1 *)
                 (this->i32_74 +
                 *(int *)(this + (this->i32_10 + 1) * 4 + 0x78));
    for (iVar5 = *(int *)(this + (this->i32_10 + 3) * 4 + 0x78); 0 < iVar5;
        iVar5 = iVar5 + -1) {
      *puStack_18 = *puStack_14;
      puStack_18 = puStack_18 + 1;
      puStack_14 = puStack_14 + 1;
    }
    goto switchD_002fc6b0_caseD_0;
  case 0x34:
    iVar5 = __nwa(*(undefined4 *)(this + this->i32_10 * 4 + 0x78));
    *(int *)(this + this->i32_10 * 4 + 0x78) = iVar5 - this->i32_74;
    goto switchD_002fc6b0_caseD_0;
  case 0x35:
    iVar5 = this->i32_10;
    this->i32_10 = iVar5 + -1;
    __dla(this->i32_74 + *(int *)(this + iVar5 * 4 + 0x78));
    goto switchD_002fc6b0_caseD_0;
  case 0x36:
    iVar5 = scanf((char *)(this->i32_74 +
                          *(int *)(this + (this->i32_10 + -1) * 4 + 0x78)),
                  this->i32_74 + *(int *)(this + this->i32_10 * 4 + 0x78)
                 );
    *(int *)(this + (this->i32_10 + -1) * 4 + 0x78) = iVar5;
    break;
  case 0x37:
    this->i32_10 = this->i32_10 + -2;
    goto switchD_002fc6b0_caseD_0;
  case 0x38:
    this->i32_10 = this->i32_10 + -1;
    goto switchD_002fc6b0_caseD_0;
  case 0x39:
    uVar9 = uVar4 & 0xffff;
    uVar4 = (int)uVar4 >> 0x10 & 0xffff;
    if (0x14 < uVar9) {
      printf(_2583);
      this->u32_18 = 0xffffffff;
      return 0xfffffffd;
    }
    lVar7 = GetSysCallFunc(uVar4);
    iVar5 = (int)lVar7;
    cVar2 = iVar5->i8_c;
    if (cVar2 == '\x02') {
      (**(code **)(iVar5 + 4))(uVar4,uVar9,this + 0x1c,0);
    }
    else if (cVar2 == '\x01') {
      (**(code **)(iVar5 + 4))(uVar4,uVar9,this + 0x1c,this);
    }
    else if (cVar2 == '\0') {
      (**(code **)(iVar5 + 4))(uVar4,uVar9,this + 0x1c,this->u32_230);
    }
    else if (lVar7 != 0) {
      (**(code **)(iVar5 + 4))(uVar4,uVar9,this + 0x1c,iVar5->u32_8);
    }
    goto switchD_002fc6b0_caseD_0;
  case 0x3a:
    if (((int)uVar4 < 0) || (0x14 < (int)uVar4)) {
      printf(_2583);
      this->u32_18 = 0xffffffff;
      return 0xfffffffd;
    }
    *(int *)(this + uVar4 * 4 + 0x1c) =
         this->i32_74 + *(int *)(this + this->i32_10 * 4 + 0x78);
    break;
  case 0x3b:
    uVar8 = VEC::CreateThread
                      (this,uVar4,
                       *(undefined4 *)(this->i32_6c + this->i32_c * 8 + 4));
    VEC::AddThread(this,uVar8);
    this->i32_c = this->i32_c + 1;
    goto switchD_002fc6b0_caseD_0;
  case 0x3c:
    VEC::RemoveThread(this);
    return 0;
  case 0x3d:
    this->u32_248 = uVar4;
    this->u8_221 = 1;
    iVar5 = VEC::GetCore(this);
    uVar6 = VEC::GetThreadCount(iVar5->u32_10,this->u32_248);
    this->u32_228 = uVar6;
    if (this->i32_228 != 0) {
      this->u8_22c = 1;
    }
    goto switchD_002fc6b0_caseD_0;
  case 0x3e:
    uVar8 = VEC::GetCore(this);
    EffectCore::KillThread(uVar8,uVar4);
    goto switchD_002fc6b0_caseD_0;
  }
  this->i32_10 = this->i32_10 + -1;
  goto switchD_002fc6b0_caseD_0;
switchD_002fc6b0_caseD_11:
  printf(_2586,(ulong)bVar1,this->u32_c);
  this->u32_18 = 0xffffffff;
  return 0xfffffffc;
}

// JP: 0x002fdbb0  GetCore__3VECFv  =  VEC::GetCore
undefined4 VEC::GetCore(int this)

{
  return this->u32_230;
}

// JP: 0x002fdc00  IsMotionWait__3VECFv  =  VEC::IsMotionWait
bool VEC::IsMotionWait(int this)

{
  return this->i32_224 != 0;
}

// JP: 0x002fdc50  GetDsegAddr__3VECFi  =  VEC::GetDsegAddr
int VEC::GetDsegAddr(int this,int param_2)

{
  return this->i32_74 + param_2;
}

// JP: 0x002fdc80  CreateThread__3VECFii  =  VEC::CreateThread
undefined8 VEC::CreateThread(int this,undefined4 param_2,undefined4 param_3)

{
  void *__dest;
  void *__src;
  long lVar1;
  undefined8 uVar2;
  
  lVar1 = __nw(0x254);
  uVar2 = 0;
  if (lVar1 != 0) {
    uVar2 = VEC::VEC(lVar1,param_2,this->u32_230,param_3);
  }
  __dest = (void *)VEC::GetDsegAddr(uVar2,0);
  __src = (void *)VEC::GetDsegAddr(this,0);
  memcpy(__dest,__src,40000);
  VEC::SetIseg(uVar2,this->u32_6c);
  *(undefined4 *)((int)uVar2 + 0x14) = 20000;
  return uVar2;
}

// JP: 0x002fdd50  SetIseg__3VECFPv  =  VEC::SetIseg
void VEC::SetIseg(int this,undefined4 param_2)

{
  this->u32_6c = param_2;
  return;
}

// JP: 0x002fdd80  AddThread__3VECFP3VEC  =  VEC::AddThread
void VEC::AddThread(int this,undefined4 param_2)

{
  EffectCore::AddThread(this->u32_230,param_2);
  return;
}

// JP: 0x002fddc0  RemoveThread__3VECFv  =  VEC::RemoveThread
void VEC::RemoveThread(int this)

{
  EffectCore::RemoveThread(this->u32_230,this);
  return;
}

// JP: 0x002fddf0  MotionWait__3VECFP11EffectModel  =  VEC::MotionWait
void VEC::MotionWait(int this,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = VEC::GetCore(this);
  iVar2 = 0;
  while( true ) {
    if (0x27 < iVar2) {
      return;
    }
    if (*(int *)(iVar1 + iVar2 * 4 + 0x198) == param_2) break;
    iVar2 = iVar2 + 1;
  }
  this->i32_224 = param_2;
  return;
}

// JP: 0x002fde90  ReleaseMotionWait__3VECFP11EffectModel  =  VEC::ReleaseMotionWait
void VEC::ReleaseMotionWait(int *this,int param_2)

{
  if (this[0x89] == param_2) {
    this[0x89] = 0;
  }
  else if (*this != 0) {
    VEC::ReleaseMotionWait(*this,param_2);
  }
  return;
}

// JP: 0x002fdf00  OnStartThread__3VECFP3VEC  =  VEC::OnStartThread
void VEC::OnStartThread(int *this,int param_2)

{
  if (this[0x92] == param_2->i32_244) {
    this[0x8a] = this[0x8a] + 1;
    this->u8_8b = 1;
  }
  if (*this != 0) {
    VEC::OnStartThread(*this,param_2);
  }
  return;
}

// JP: 0x002fdf80  OnEndThread__3VECFP3VEC  =  VEC::OnEndThread
void VEC::OnEndThread(int *this,int param_2)

{
  if (this[0x92] == param_2->i32_244) {
    this[0x8a] = this[0x8a] + -1;
  }
  if (*this != 0) {
    VEC::OnEndThread(*this,param_2);
  }
  return;
}

// JP: 0x002fdff0  GetThreadCount__3VECFi  =  VEC::GetThreadCount
int VEC::GetThreadCount(int *this,int param_2)

{
  int iVar1;
  
  iVar1 = 0;
  if (*this != 0) {
    iVar1 = VEC::GetThreadCount(*this,param_2);
  }
  if (this[0x91] == param_2) {
    iVar1 = iVar1 + 1;
  }
  return iVar1;
}

// JP: 0x002fe3a0  __ct__9vpTextureFv  =  vpTexture::vpTexture
int vpTexture::vpTexture(int this)

{
  *(undefined1 **)(this + 0x40) = vpTexture::__vt;
  __ct__Q29vpTexture24_class_1573vpTexture_cppFv(this + 0x10);
  this->u32_4 = 0;
  return this;
}

// JP: 0x002fe430  __dt__9vpTextureFv  =  vpTexture::~vpTexture
int vpTexture::~vpTexture(int this,short param_2)

{
  int iVar1;
  
  if (this != 0) {
    *(undefined1 **)(this + 0x40) = vpTexture::__vt;
    if (this->i32_4 != 0) {
      iVar1 = this->i32_4;
      if (iVar1 != 0) {
        (**(code **)(iVar1->i32_c + 8))(iVar1,1);
      }
      this->u32_4 = 0;
    }
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}

// JP: 0x002fe4e0  Create__9vpTextureFPc  =  vpTexture::Create
/* WARNING: Removing unreachable block (ram,0x002fe878) */
/* WARNING: Removing unreachable block (ram,0x002fe67c) */
/* WARNING: Removing unreachable block (ram,0x002fe6b8) */
/* WARNING: Removing unreachable block (ram,0x002fe8b8) */

int vpTexture::Create(int *this,int param_2)

{
  byte bVar1;
  undefined2 uVar2;
  ushort uVar3;
  int iVar4;
  long lVar5;
  ulong uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  undefined1 auStack_40 [24];
  int iStack_28;
  byte bStack_21;
  int *piStack_20;
  int iStack_10;
  
  piStack_20 = this;
  iStack_10 = param_2;
  _QWD::_QWD(auStack_40);
  *piStack_20 = iStack_10;
  if (*(int *)(*piStack_20 + 4) == -1) {
    iStack_28 = 0;
  }
  else {
    iStack_28 = iStack_10 + *(int *)(*piStack_20 + 4);
  }
  if (*(char *)(*piStack_20 + 0xe) == '\x04') {
    bStack_21 = 0x2c;
  }
  else {
    bStack_21 = 0x1b;
  }
  if (*(char *)(*piStack_20 + 0xe) == '\x04') {
    iVar8 = 8;
  }
  else {
    iVar8 = 0x10;
  }
  if (*(char *)(*piStack_20 + 0xe) == '\x04') {
    iVar9 = 2;
  }
  else {
    iVar9 = 0x10;
  }
  lVar5 = __nw(0x30);
  iVar4 = 0;
  if (lVar5 != 0) {
    iVar4 = CVif1Packet::CVif1Packet(lVar5,0x28,0x10);
  }
  piStack_20[1] = iVar4;
  if ((int)(uint)*(ushort *)(*piStack_20 + 10) >> 6 == 0) {
    iVar4 = 1;
  }
  else {
    iVar4 = (int)(uint)*(ushort *)(*piStack_20 + 10) >> 6;
  }
  uVar2 = GsxFrameBuf::GetBufEntry(CApp::camera->u32_340);
  iVar7 = (uint)*(ushort *)(*piStack_20 + 10) * (uint)*(ushort *)(*piStack_20 + 0xc);
  if (iVar7 < 0) {
    iVar7 = iVar7 + 0xf;
  }
  CVif1Packet::RefLoadImage
            (piStack_20[1],uVar2,bStack_21,iVar4,*piStack_20 + (uint)*(ushort *)(*piStack_20 + 8),
             iVar7 >> 4,0,0);
  iVar4 = ClutAdressControl::getAdress(CApp::app + 0x80,10);
  piStack_20[2] = iVar4;
  CVif1Packet::RefLoadImage
            (piStack_20[1],piStack_20[2] & 0xffff,0,1,*piStack_20 + 0x10,(uint)(iVar8 * iVar9) >> 2,
             0,0);
  memset(piStack_20 + 4,0,0x30);
  piStack_20[4] = 0x8002;
  piStack_20[5] = 0x10000000;
  piStack_20[6] = 0xe;
  piStack_20[7] = 0;
  piStack_20[10] = 0x3f;
  piStack_20[0xb] = 0;
  uVar3 = GsxFrameBuf::GetBufEntry(CApp::camera->u32_340);
  piStack_20->u16_c = piStack_20->u16_c & 0xc000 | uVar3 & 0x3fff;
  if ((int)(uint)*(ushort *)(*piStack_20 + 10) >> 6 == 0) {
    iVar8 = 1;
  }
  else {
    iVar8 = (int)(uint)*(ushort *)(*piStack_20 + 10) >> 6;
  }
  piStack_20->u64_c =
       piStack_20->u64_c & 0xfffffffffff03fff | ((long)iVar8 & 0x3fU) << 0xe;
  *(ushort *)((int)piStack_20 + 0x32) =
       *(ushort *)((int)piStack_20 + 0x32) & 0xfc0f | (bStack_21 & 0x3f) << 4;
  bVar1 = GetBekijo(*(undefined2 *)(*piStack_20 + 10));
  *(byte *)((int)piStack_20 + 0x33) = *(byte *)((int)piStack_20 + 0x33) & 0xc3 | (bVar1 & 0xf) << 2;
  uVar6 = GetBekijo(*(undefined2 *)(*piStack_20 + 0xc));
  piStack_20->u64_c =
       piStack_20->u64_c & 0xfffffffc3fffffff | (uVar6 & 0xf) << 0x1e;
  piStack_20->u8_d = piStack_20->u8_d & 0xfb | 4;
  piStack_20->u8_d = piStack_20->u8_d & 0xe7;
  piStack_20->u64_c =
       piStack_20->u64_c & 0xfff8001fffffffff | ((long)piStack_20[2] & 0x3fffU) << 0x25;
  *(byte *)((int)piStack_20 + 0x36) = *(byte *)((int)piStack_20 + 0x36) & 0x87;
  *(byte *)((int)piStack_20 + 0x36) = *(byte *)((int)piStack_20 + 0x36) & 0x7f;
  *(byte *)((int)piStack_20 + 0x37) = *(byte *)((int)piStack_20 + 0x37) & 0xe0;
  *(byte *)((int)piStack_20 + 0x37) = *(byte *)((int)piStack_20 + 0x37) & 0x1f | 0x20;
  piStack_20[0xe] = 6;
  piStack_20[0xf] = 0;
  CVif1Packet::Ref(piStack_20[1],piStack_20 + 4,3,0,0x50000003,0);
  CVif1Packet::Ret(piStack_20[1],0);
  CVif1Packet::Terminate(piStack_20[1]);
  return iStack_28;
}

// JP: 0x002feb50  GetPacket__9vpTextureFv  =  vpTexture::GetPacket
void vpTexture::GetPacket(int this)

{
  CPacket::GetBuffer(this->u32_4);
  return;
}

// JP: 0x002feb80  __ct__5vpSeqFv  =  vpSeq::vpSeq
undefined4 * vpSeq::vpSeq(undefined4 *this)

{
  this[4] = vpSeq::__vt;
  *this = 0;
  this[1] = 0;
  this[2] = 0;
  return this;
}

// JP: 0x002febc0  __dt__5vpSeqFv  =  vpSeq::~vpSeq
int vpSeq::~vpSeq(int this,short param_2)

{
  if ((this != 0) && (*(undefined1 **)(this + 0x10) = vpSeq::__vt, 0 < param_2)) {
    __dl(this);
  }
  return this;
}

// JP: 0x002fec30  Create__5vpSeqFPcP9vpTexture  =  vpSeq::Create
int vpSeq::Create(int *this,int param_2,int param_3)

{
  *this = param_2;
  this[1] = *this + 0x10;
  this[2] = this[1] + (uint)*(ushort *)(*this + 10) * 0x10;
  this[3] = param_3 + (uint)*(byte *)(*this + 0xd) * 0x50;
  if (*(int *)(*this + 4) == -1) {
    param_2 = 0;
  }
  else {
    param_2 = param_2 + *(int *)(*this + 4);
  }
  return param_2;
}

// JP: 0x002fed20  __ct__13vpTextureFileFv  =  vpTextureFile::vpTextureFile
undefined4 * vpTextureFile::vpTextureFile(undefined4 *this)

{
  this[4] = vpTextureFile::__vt;
  this[2] = 0;
  *this = 0;
  vpTextureFile::texControl = this;
  return this;
}

// JP: 0x002fed60  __dt__13vpTextureFileFv  =  vpTextureFile::~vpTextureFile
int vpTextureFile::~vpTextureFile(int this,short param_2)

{
  if (this != 0) {
    *(undefined1 **)(this + 0x10) = vpTextureFile::__vt;
    if (this->i32_8 != 0) {
      __destroy_new_array(this->u32_8,0x2fe430);
      this->u32_8 = 0;
    }
    if (this->i32_c != 0) {
      __destroy_new_array(this->u32_c,0x2febc0);
      this->u32_c = 0;
    }
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}

// JP: 0x002fee30  Create__13vpTextureFileFPc  =  vpTextureFile::Create
void vpTextureFile::Create(int *this,int param_2)

{
  byte bVar1;
  int iVar2;
  undefined8 uVar3;
  int iVar4;
  
  this[1] = param_2;
  iVar4 = param_2 + *(int *)(this[1] + 8);
  bVar1 = *(byte *)(this[1] + 0x10);
  uVar3 = __nwa((uint)bVar1 * 0x50 + 0x10);
  iVar2 = __construct_new_array(uVar3,0x2fe3a0,0x2fe430,0x50,bVar1);
  this[2] = iVar2;
  while (*this < (int)(uint)*(byte *)(this[1] + 0x10)) {
    iVar4 = vpTexture::Create(this[2] + *this * 0x50,iVar4);
    *this = *this + 1;
  }
  param_2 = param_2 + *(int *)(this[1] + 0xc);
  bVar1 = *(byte *)(this[1] + 0x11);
  uVar3 = __nwa((uint)bVar1 * 0x14 + 0x10);
  iVar2 = __construct_new_array(uVar3,0x2feb80,0x2febc0,0x14,bVar1);
  this[3] = iVar2;
  for (iVar2 = 0; iVar2 < (int)(uint)*(byte *)(this[1] + 0x11); iVar2 = iVar2 + 1) {
    param_2 = vpSeq::Create(this[3] + iVar2 * 0x14,param_2,this[2]);
  }
  return;
}

// JP: 0x002ff040  FindTexture__13vpTextureFileFi  =  vpTextureFile::FindTexture
int vpTextureFile::FindTexture(int this,uint param_2)

{
  int iVar1;
  
  iVar1 = 0;
  while( true ) {
    if ((int)(uint)*(byte *)(this->i32_4 + 0x10) <= iVar1) {
      return 0;
    }
    if (param_2 == *(byte *)(*(int *)(this->i32_8 + iVar1 * 0x50) + 0xf)) break;
    iVar1 = iVar1 + 1;
  }
  return this->i32_8 + iVar1 * 0x50;
}

// JP: 0x00301530  SetRunState__3VECFi  =  VEC::SetRunState
void VEC::SetRunState(int this,undefined4 param_2)

{
  this->u32_18 = param_2;
  return;
}

// JP: 0x00301770  GetRunState__3VECFv  =  VEC::GetRunState
undefined4 VEC::GetRunState(int this)

{
  return this->u32_18;
}

// JP: 0x00301d90  Stop__3VECFv  =  VEC::Stop
void VEC::Stop(int this)

{
  this->u32_18 = 3;
  return;
}
