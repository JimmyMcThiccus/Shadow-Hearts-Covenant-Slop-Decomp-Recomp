/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x0028f7d0  FindMotion__13MenuModelPackFP17MenuMotionConnectPCc  size 0x98
// MenuModelPack::FindMotion(MenuMotionConnect*, const char*)
u32 FindMotion__13MenuModelPackFP17MenuMotionConnectPCc(MenuModelPack *this,char *param_2)
{
  int iVar1;
  u32 *puStack_20;
  puStack_20 = this;
  if (this != (u32 *)0x0) {
    for (; *(char *)*puStack_20 != '\0'; puStack_20 = puStack_20 + 2) {
      iVar1 = strncmp(param_2,(char *)*puStack_20,4);
      if (iVar1 == 0) {
        return puStack_20[1];
      }
    }
  }
  return 0;
}

// JP: 0x0028f870  __ct__13MenuModelPackFv  size 0xfc
// MenuModelPack::MenuModelPack()
u32 * __ct__13MenuModelPackFv(MenuModelPack *this)
{
  *this = 0;
  this[1] = 0;
  this[2] = __vt__17DelayDeleteObject;
  this[2] = __vt__13MenuModelPack;
  this[3] = 0;
  this[5] = 0;
  this[6] = 0;
  this[7] = 0;
  this[10] = 0;
  this[0xb] = 0;
  this[0xc] = 0;
  *(u8 *)((int)this + 0x66) = 0x7f;
  this->f_1a /*u8 **/ = 0;
  *(u8 *)((int)this + 0x69) = 0;
  *(u8 *)((int)this + 0x6a) = 0;
  this->f_1b /*u16 **/ = 4;
  *(u16 *)((int)this + 0x6e) = 5;
  memset(this + 0xd,0,8);
  memset(this + 0xf,0,0x1c);
  *(u8 *)((int)this + 0x6b) = 0;
  return this;
}

// JP: 0x0028f970  __dt__13MenuModelPackFv  size 0x2a8
// MenuModelPack::~MenuModelPack()
int __dt__13MenuModelPackFv(MenuModelPack *this,short param_2)
{
  int iVar1;
  if (this != 0) {
    this->f_8 /*u8 **/ = __vt__13MenuModelPack;
    if (this->f_20 /*int **/ != 0) {
      iVar1 = this->f_20 /*int **/;
      if (iVar1 != 0) {
        (**(code **)(*(int *)(iVar1 + 0x10) + 8))(iVar1,1);
      }
      this->f_20 /*u32 **/ = 0;
    }
    if (this->f_24 /*int **/ != 0) {
      iVar1 = this->f_24 /*int **/;
      if (iVar1 != 0) {
        (**(code **)(*(int *)(iVar1 + 0x10) + 8))(iVar1,1);
      }
      this->f_24 /*u32 **/ = 0;
    }
    if (this->f_28 /*int **/ != 0) {
      iVar1 = this->f_28 /*int **/;
      if (iVar1 != 0) {
        (**(code **)(*(int *)(iVar1 + 0x10) + 8))(iVar1,1);
      }
      this->f_28 /*u32 **/ = 0;
    }
    if (this->f_2c /*int **/ != 0) {
      iVar1 = this->f_2c /*int **/;
      if (iVar1 != 0) {
        (**(code **)(*(int *)(iVar1 + 0x10) + 8))(iVar1,1);
      }
      this->f_2c /*u32 **/ = 0;
    }
    if (this->f_34 /*int **/ != 0) {
      iVar1 = this->f_34 /*int **/;
      if (iVar1 != 0) {
        (**(code **)(*(int *)(iVar1 + 0x10) + 8))(iVar1,1);
      }
      this->f_34 /*u32 **/ = 0;
    }
    if (this->f_38 /*int **/ != 0) {
      iVar1 = this->f_38 /*int **/;
      if (iVar1 != 0) {
        (**(code **)(*(int *)(iVar1 + 0x10) + 8))(iVar1,1);
      }
      this->f_38 /*u32 **/ = 0;
    }
    for (iVar1 = 0; iVar1 < 7; iVar1 = iVar1 + 1) {
      if (*(int *)(this + iVar1 * 4 + 0x3c) != 0) {
        __dt__9BufMemoryFv(*(u32 *)(this + iVar1 * 4 + 0x3c),1);
        *(u32 *)(this + iVar1 * 4 + 0x3c) = 0;
      }
    }
    if (this != 0) {
      this->f_8 /*u8 **/ = __vt__17DelayDeleteObject;
    }
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}

// JP: 0x0028fc20  Create__13MenuModelPackFP16MenuModelManeger  size 0x9c
// MenuModelPack::Create(MenuModelManeger*)
void Create__13MenuModelPackFP16MenuModelManeger(MenuModelPack *this,u32 param_2)
{
  u32 uVar1;
  long lVar2;
  lVar2 = __nw__FUi(0x4e0);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = __ct__9MenuModelFv(lVar2);
  }
  this->f_20 /*u32 **/ = uVar1;
  lVar2 = __nw__FUi(0x4e0);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = __ct__9MenuModelFv(lVar2);
  }
  this->f_24 /*u32 **/ = uVar1;
  this->f_c /*u32 **/ = param_2;
  return;
}

// JP: 0x0028fcc0  Order__13MenuModelPackFv  size 0x170
// MenuModelPack::Order()
void Order__13MenuModelPackFv(MenuModelPack *this)
{
  u16 uVar1;
  u16 uVar2;
  u64 uVar3;
  this->f_6b /*u8 **/ = this->f_6b /*u8 **/ & 0xfe | 1;
  uVar1 = this->f_6c /*u16 **/;
  uVar2 = this->f_6e /*u16 **/;
  Order__9MenuModelFP13MenuModelPackii(this->f_20 /*u32 **/,this,uVar1,uVar2);
  CalcMatrix__9MenuModelFv(this->f_20 /*u32 **/);
  if (this->f_28 /*int **/ != 0) {
    uVar3 = searchFrame__5FrameFPCc(*(u32 *)(this->f_20 /*int **/ + 0x30),0x3feb20);
    chainModel__5FrameFP5Model(uVar3,this->f_28 /*u32 **/);
    Order__9MenuModelFP13MenuModelPackii(this->f_28 /*u32 **/,0,uVar1,uVar2);
  }
  if (this->f_2c /*int **/ != 0) {
    uVar3 = searchFrame__5FrameFPCc(*(u32 *)(this->f_20 /*int **/ + 0x30),0x3feb28);
    chainModel__5FrameFP5Model(uVar3,this->f_2c /*u32 **/);
    Order__9MenuModelFP13MenuModelPackii(this->f_2c /*u32 **/,0,uVar1,uVar2);
  }
  SetMotion__13MenuModelPackFPCc(this,*this->f_10 /*u32 **/);
  return;
}

// JP: 0x0028fe30  Standby__13MenuModelPackFv  size 0xe8
// MenuModelPack::Standby()
void Standby__13MenuModelPackFv(MenuModelPack *this)
{
  this->f_6b /*u8 **/ = this->f_6b /*u8 **/ & 0xfe;
  ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,this->f_20 /*u32 **/);
  ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,this->f_20 /*u32 **/);
  if (this->f_28 /*int **/ != 0) {
    ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,this->f_28 /*u32 **/);
    ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,this->f_28 /*u32 **/);
  }
  if (this->f_2c /*int **/ != 0) {
    ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,this->f_2c /*u32 **/);
    ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,this->f_2c /*u32 **/);
  }
  return;
}

// JP: 0x0028ff20  SafeDestroy__13MenuModelPackFv  size 0x134
// MenuModelPack::SafeDestroy()
void SafeDestroy__13MenuModelPackFv(MenuModelPack *this)
{
  if ((this->f_6b /*u8 **/ & 1) != 0) {
    if (this->f_20 /*int **/ != 0) {
      (**(code **)(*(int *)(this->f_20 /*int **/ + 0x10) + 0x40))();
    }
    if (this->f_24 /*int **/ != 0) {
      (**(code **)(*(int *)(this->f_24 /*int **/ + 0x10) + 0x40))();
    }
    if (this->f_28 /*int **/ != 0) {
      (**(code **)(*(int *)(this->f_28 /*int **/ + 0x10) + 0x40))();
    }
    if (this->f_2c /*int **/ != 0) {
      (**(code **)(*(int *)(this->f_2c /*int **/ + 0x10) + 0x40))();
    }
    if (this->f_34 /*int **/ != 0) {
      (**(code **)(*(int *)(this->f_34 /*int **/ + 0x10) + 0x40))();
    }
    if (this->f_38 /*int **/ != 0) {
      (**(code **)(*(int *)(this->f_38 /*int **/ + 0x10) + 0x40))();
    }
  }
  (**(code **)(this->f_8 /*int **/ + 0xc))();
  return;
}

// JP: 0x00290060  AddTime__13MenuModelPackFf  size 0x130
// MenuModelPack::AddTime(float)
void AddTime__13MenuModelPackFf(u32 param_1,int this)
{
  (**(code **)(*(int *)(this->f_20 /*int **/ + 0x10) + 0x2c))(param_1);
  (**(code **)(*(int *)(this->f_20 /*int **/ + 0x10) + 0x28))(this->f_20 /*int **/,0);
  if (this->f_28 /*int **/ != 0) {
    (**(code **)(*(int *)(this->f_28 /*int **/ + 0x10) + 0x2c))(param_1);
    (**(code **)(*(int *)(this->f_28 /*int **/ + 0x10) + 0x28))(this->f_28 /*int **/,0);
  }
  if (this->f_2c /*int **/ != 0) {
    (**(code **)(*(int *)(this->f_2c /*int **/ + 0x10) + 0x2c))(param_1);
    (**(code **)(*(int *)(this->f_2c /*int **/ + 0x10) + 0x28))(this->f_2c /*int **/,0);
  }
  if (this->f_30 /*int **/ != 0) {
    (**(code **)(*(int *)(this->f_30 /*int **/ + 0x10) + 0x2c))(param_1);
    (**(code **)(*(int *)(this->f_30 /*int **/ + 0x10) + 0x28))(this->f_30 /*int **/,0);
  }
  return;
}

// JP: 0x00290190  EnableAlpha__13MenuModelPackFv  size 0x70
// MenuModelPack::EnableAlpha()
void EnableAlpha__13MenuModelPackFv(MenuModelPack *this)
{
  EnableAlpha__9MenuModelFv(this->f_20 /*u32 **/);
  if (this->f_28 /*int **/ != 0) {
    EnableAlpha__9MenuModelFv(this->f_28 /*u32 **/);
  }
  if (this->f_2c /*int **/ != 0) {
    EnableAlpha__9MenuModelFv(this->f_2c /*u32 **/);
  }
  return;
}

// JP: 0x00290200  DisableAlpha__13MenuModelPackFv  size 0x70
// MenuModelPack::DisableAlpha()
void DisableAlpha__13MenuModelPackFv(MenuModelPack *this)
{
  DisableAlpha__9MenuModelFv(this->f_20 /*u32 **/);
  if (this->f_28 /*int **/ != 0) {
    DisableAlpha__9MenuModelFv(this->f_28 /*u32 **/);
  }
  if (this->f_2c /*int **/ != 0) {
    DisableAlpha__9MenuModelFv(this->f_2c /*u32 **/);
  }
  return;
}

// JP: 0x00290270  SetAlpha__13MenuModelPackFUc  size 0x80
// MenuModelPack::SetAlpha(unsigned char)
void SetAlpha__13MenuModelPackFUc(MenuModelPack *this,u8 param_2)
{
  SetAlpha__9MenuModelFUc(this->f_20 /*u32 **/,param_2);
  if (this->f_28 /*int **/ != 0) {
    SetAlpha__9MenuModelFUc(this->f_28 /*u32 **/,param_2);
  }
  if (this->f_2c /*int **/ != 0) {
    SetAlpha__9MenuModelFUc(this->f_2c /*u32 **/,param_2);
  }
  return;
}

// JP: 0x002902f0  SetMotion__13MenuModelPackFPCcUcUc  size 0xf8
// MenuModelPack::SetMotion(const char*, unsigned char, unsigned char)
u32
SetMotion__13MenuModelPackFPCcUcUc(MenuModelPack *this,u32 param_2,u8 param_3,u8 param_4)
{
  u32 uVar1;
  long lVar2;
  lVar2 = setNextMotion__5ModelFPCcUs(this->f_20 /*u32 **/,param_2,1);
  if (lVar2 == 0) {
    uVar1 = 0;
  }
  else {
    if (this->f_28 /*int **/ != 0) {
      setNextMotion__5ModelFPCcUs(this->f_28 /*u32 **/,param_2,1);
    }
    if (this->f_2c /*int **/ != 0) {
      setNextMotion__5ModelFPCcUs(this->f_2c /*u32 **/,param_2,1);
    }
    this->f_6b /*u8 **/ = this->f_6b /*u8 **/ & 0xf7 | (param_3 & 1) << 3;
    this->f_6b /*u8 **/ = this->f_6b /*u8 **/ & 0xfd | (param_4 & 1) << 1;
    uVar1 = 1;
  }
  return uVar1;
}

// JP: 0x002903f0  SetMotion__13MenuModelPackFPCc  size 0xa8
// MenuModelPack::SetMotion(const char*)
u32 SetMotion__13MenuModelPackFPCc(MenuModelPack *this,u32 param_2)
{
  u32 uVar1;
  long lVar2;
  lVar2 = setMotion__5ModelFPCcf(0,this->f_20 /*u32 **/,param_2);
  if (lVar2 == 0) {
    uVar1 = 0;
  }
  else {
    if (this->f_28 /*int **/ != 0) {
      setMotion__5ModelFPCcf(0,this->f_28 /*u32 **/,param_2);
    }
    if (this->f_2c /*int **/ != 0) {
      setMotion__5ModelFPCcf(0,this->f_2c /*u32 **/,param_2);
    }
    uVar1 = 1;
  }
  return uVar1;
}

// JP: 0x002904a0  Event__13MenuModelPackFP9MenuModelPCcPCc  size 0x1b8
// MenuModelPack::Event(MenuModel*, const char*, const char*)
void Event__13MenuModelPackFP9MenuModelPCcPCc(MenuModelPack *this,int param_2,char *param_3,char *param_4)
{
  int iVar1;
  long lVar2;
  char acStack_48 [8];
  int iStack_40;
  int iStack_30;
  char *pcStack_20;
  char *pcStack_10;
  iStack_40 = this;
  iStack_30 = param_2;
  pcStack_20 = param_3;
  pcStack_10 = param_4;
  iVar1 = strncmp(param_3,_3274,8);
  if ((iVar1 == 0) &&
     (lVar2 = FindMotion__13MenuModelPackFP17MenuMotionConnectPCc
                        (*(u32 *)(iStack_40 + 0x18),pcStack_10), lVar2 != 0)) {
    BootEffect__13MenuModelPackFPCci(iStack_40,lVar2,1);
  }
  iVar1 = strncmp(pcStack_20,_3275,8);
  if (((iVar1 == 0) && (iVar1 = strncmp(pcStack_10,(char *)&_3276,4), iVar1 == 0)) &&
     (*(short *)(iStack_30 + 0x4c0) = *(short *)(iStack_30 + 0x4c0) + 1,
     (long)*(char *)(iStack_40 + 0x66) <= (long)*(short *)(iStack_30 + 0x4c0))) {
    sprintf(acStack_48,_3277,*(u16 *)(iStack_30 + 0x4c0));
    setMotion__5ModelFPCcf(0,iStack_30,acStack_48);
    if (*(int *)(iStack_40 + 0x28) != 0) {
      setMotion__5ModelFPCcf(0,*(u32 *)(iStack_40 + 0x28),acStack_48);
    }
    if (*(int *)(iStack_40 + 0x2c) != 0) {
      setMotion__5ModelFPCcf(0,*(u32 *)(iStack_40 + 0x2c),acStack_48);
    }
    *(u16 *)(iStack_30 + 0x4c0) = 0;
  }
  (**(code **)(*(int *)(*(int *)(iStack_40 + 0xc) + 0x14) + 0x10))
            (*(int *)(iStack_40 + 0xc),iStack_30,pcStack_20,pcStack_10);
  return;
}

// JP: 0x00290660  FinishMotion__13MenuModelPackFP9MenuModelPCc  size 0x194
// MenuModelPack::FinishMotion(MenuModel*, const char*)
void FinishMotion__13MenuModelPackFP9MenuModelPCc(MenuModelPack *this,int param_2,char *param_3)
{
  int iVar1;
  long lVar2;
  iVar1 = strncmp((char *)*this->f_10 /*u32 **/,param_3,4);
  if ((iVar1 != 0) && (iVar1 = strncmp(_3296,param_3,7), iVar1 != 0)) {
    if (((long)((ulong)this->f_6b /*u8 **/ << 0x3c) < 0) &&
       (iVar1 = SeachSequenceControl__15SequenceControlFPUc(*(u32 *)(param_2 + 0x34),param_3)
       , (*(u8 *)(*(int *)(iVar1 + 8) + 0x14) & 1) != 0)) {
      this->f_6b /*u8 **/ = this->f_6b /*u8 **/ & 0xf7;
    }
    else {
      lVar2 = FindMotion__13MenuModelPackFP17MenuMotionConnectPCc
                        (this->f_14 /*u32 **/,param_3);
      if ((lVar2 == 0) ||
         (lVar2 = SetMotion__13MenuModelPackFPCcUcUc
                            (this,lVar2,((ulong)this->f_6b /*u8 **/ & 0xf) >> 3,
                             ((ulong)this->f_6b /*u8 **/ & 3) >> 1), lVar2 == 0)) {
        this->f_6b /*u8 **/ = this->f_6b /*u8 **/ & 0xfd;
        SetMotion__13MenuModelPackFPCcUcUc(this,*this->f_10 /*u32 **/,0,0);
      }
      else {
        this->f_6a /*char **/ = this->f_6a /*char **/ + '\x01';
      }
    }
  }
  return;
}

// JP: 0x00290800  FinishEffect__13MenuModelPackFP15MenuEffectModelPCc  size 0xf0
// MenuModelPack::FinishEffect(MenuEffectModel*, const char*)
void FinishEffect__13MenuModelPackFP15MenuEffectModelPCc(MenuModelPack *this,int param_2,char *param_3)
{
  int iVar1;
  long lVar2;
  iVar1 = strncmp(_3313,param_3,7);
  if (iVar1 != 0) {
    if (this->f_1c /*int **/ == 0) {
      lVar2 = FindMotion__13MenuModelPackFP17MenuMotionConnectPCc
                        (this->f_14 /*u32 **/,param_3);
      this->f_1c /*int **/ = (int)lVar2;
      if (lVar2 == 0) {
        iVar1 = SeachSequenceControl__15SequenceControlFPUc(*(u32 *)(param_2 + 0x34),param_3)
        ;
        if ((*(u8 *)(*(int *)(iVar1 + 8) + 0x14) & 1) != 0) {
          setMotion__7ExModelFPCc(param_2,param_3);
          return;
        }
        Release__15MenuEffectModelFv(param_2);
        return;
      }
    }
    setMotion__7ExModelFPCc(param_2,this->f_1c /*u32 **/);
    this->f_1c /*u32 **/ = 0;
  }
  return;
}

// JP: 0x002908f0  SetAction__13MenuModelPackFv  size 0x1a4
// MenuModelPack::SetAction()
void SetAction__13MenuModelPackFv(MenuModelPack *this)
{
  long lVar1;
  char cVar2;
  if (((this->f_6b /*u8 **/ & 1) != 0) &&
     (-1 < (long)((ulong)this->f_6b /*u8 **/ << 0x3e))) {
    cVar2 = this->f_69 /*char **/;
    do {
      cVar2 = cVar2 + '\x01';
      if (**(char **)(this->f_10 /*int **/ + cVar2 * 4) == '\0') {
        cVar2 = '\x01';
        while( true ) {
          if (this->f_69 /*char **/ < cVar2) {
            return;
          }
          lVar1 = SetMotion__13MenuModelPackFPCcUcUc
                            (this,*(u32 *)(this->f_10 /*int **/ + cVar2 * 4),0,1);
          if (lVar1 != 0) break;
          cVar2 = cVar2 + '\x01';
        }
        this->f_69 /*char **/ = cVar2;
        return;
      }
      lVar1 = SetMotion__13MenuModelPackFPCcUcUc
                        (this,*(u32 *)(this->f_10 /*int **/ + cVar2 * 4),0,1);
    } while (lVar1 == 0);
    this->f_69 /*char **/ = cVar2;
  }
  return;
}

// JP: 0x00290aa0  BootEffect__13MenuModelPackFPCci  size 0x1c0
// MenuModelPack::BootEffect(const char*, int)
void BootEffect__13MenuModelPackFPCci(MenuModelPack *this,u64 param_2,int param_3)
{
  int iVar1;
  long lVar2;
  u64 uVar3;
  u8 (*pauVar4) [16];
  u8 auVar5 [16];
  u8 auVar6 [16];
  u8 auStack_50 [16];
  u64 uStack_40;
  u32 uStack_38;
  u32 uStack_34;
  u64 uStack_30;
  u32 uStack_28;
  u32 uStack_24;
  u32 uStack_20;
  u32 uStack_1c;
  u32 uStack_18;
  u32 uStack_14;
  u8 auStack_10 [16];
  iVar1 = *(int *)(this + param_3 * 4 + 0x34);
  if ((iVar1 != 0) && (lVar2 = setMotion__7ExModelFPCc(iVar1), lVar2 != 0)) {
    if (iVar1 != this->f_30 /*int **/) {
      if (this->f_30 /*int **/ != 0) {
        Release__15MenuEffectModelFv(this->f_30 /*u32 **/);
      }
      uStack_18 = *(u32 *)(camera__4CApp + 0x278);
      uStack_14 = *(u32 *)(camera__4CApp + 0x27c);
      uStack_20 = (u32)*(u64 *)(camera__4CApp + 0x270);
      uStack_1c = (u32)((ulong)*(u64 *)(camera__4CApp + 0x270) >> 0x20);
      uVar3 = searchFrame__5FrameFPCc(*(u32 *)(this->f_20 /*int **/ + 0x30),0x3feb70);
      getWorldPos__5FrameFi(&uStack_30,uVar3,m_Env__8VIF1Prim & 1);
      auStack_10._8_4_ = uStack_28;
      auStack_10._0_8_ = uStack_30;
      auStack_10._12_4_ = uStack_24;
      auVar5 = _lqc2(auStack_10);
      auVar6._4_4_ = uStack_1c;
      auVar6._0_4_ = uStack_20;
      auVar6._8_4_ = uStack_18;
      auVar6._12_4_ = uStack_14;
      auVar6 = _lqc2(auVar6);
      auVar6 = _vsub(auVar5,auVar6);
      auStack_50 = _sqc2(auVar6);
      __ct__7FVectorFRC7FVector(&uStack_40,auStack_50);
      auStack_10._8_4_ = uStack_38;
      auStack_10._0_8_ = uStack_40;
      auStack_10._12_4_ = uStack_34;
      Normalize__7FVectorFv(auStack_10);
      __amu__7FVectorFf(0x41f00000,auStack_10);
      auVar5._4_4_ = uStack_1c;
      auVar5._0_4_ = uStack_20;
      auVar5._8_4_ = uStack_18;
      auVar5._12_4_ = uStack_14;
      auVar5 = _lqc2(auVar5);
      auVar6 = _lqc2(auStack_10);
      auVar6 = _vadd(auVar6,auVar5);
      auStack_10 = _sqc2(auVar6);
      *(int *)(iVar1 + 0x4c0) = auStack_10._0_4_;
      *(int *)(iVar1 + 0x4c4) = auStack_10._4_4_;
      *(u32 *)(iVar1 + 0x4c8) = auStack_10._8_4_;
      *(u32 *)(iVar1 + 0x4cc) = auStack_10._12_4_;
      if (*(int *)(iVar1 + 0x30) != 0) {
        pauVar4 = (u8 (*) [16])(*(int *)(iVar1 + 0x30) + 400);
        _lqc2(*pauVar4);
        auVar6 = _lqc2(auStack_10);
        auVar6 = _vmove(auVar6);
        auVar6 = _sqc2(auVar6);
        *pauVar4 = auVar6;
      }
    }
    Order__15MenuEffectModelFv(iVar1);
    this->f_30 /*int **/ = iVar1;
  }
  return;
}

// JP: 0x00290c60  ResetEffect__13MenuModelPackFv  size 0x48
// MenuModelPack::ResetEffect()
void ResetEffect__13MenuModelPackFv(MenuModelPack *this)
{
  if (this->f_30 /*int **/ != 0) {
    Release__15MenuEffectModelFv(this->f_30 /*u32 **/);
    this->f_30 /*u32 **/ = 0;
  }
  return;
}
