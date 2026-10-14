/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x00282590  ReadComplete__16MenuModelManegerFiP9BufMemoryiPcPv  size 0x38
// MenuModelManeger::ReadComplete(int, BufMemory*, int, char*, void*)
void ReadComplete__16MenuModelManegerFiP9BufMemoryiPcPv
               (MenuModelManeger *this,u32 param_2,u64 param_3,u64 param_4,
               u32 param_5)
{
  ReadFile__16MenuModelManegerFiP9BufMemory(param_5,this,param_2);
  return;
}

// JP: 0x002825d0  __ct__16MenuModelManegerFv  size 0x80
// MenuModelManeger::MenuModelManeger()
int __ct__16MenuModelManegerFv(MenuModelManeger *this)
{
  __ct__7CPolObjFv(this);
  this->f_14 /*u8 **/ = __vt__16MenuModelManeger;
  this->f_18 /*u32 **/ = 0;
  this->f_64 /*u16 **/ = 0xffff;
  this->f_68 /*u16 **/ = 0;
  this->f_6c /*u32 **/ = 0x3c888889;
  this->f_46 /*u8 **/ = 3;
  this->f_47 /*u8 **/ = 0;
  return this;
}

// JP: 0x00282650  __dt__16MenuModelManegerFv  size 0x7c
// MenuModelManeger::~MenuModelManeger()
int __dt__16MenuModelManegerFv(MenuModelManeger *this,short param_2)
{
  if (this != 0) {
    this->f_14 /*u8 **/ = __vt__16MenuModelManeger;
    this->f_46 /*u8 **/ = 3;
    __dt__7CPolObjFv(this,0);
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}

// JP: 0x002826d0  Create__16MenuModelManegerFPCc  size 0x40
// MenuModelManeger::Create(const char*)
void Create__16MenuModelManegerFPCc(MenuModelManeger *this)
{
  this->f_6a /*u16 **/ = 0;
  Entry__7CPollerFP7CPolObjib(app__4CApp + 0x48,this,0x80,0);
  return;
}

// JP: 0x00282710  Destroy__16MenuModelManegerFUc  size 0x154
// MenuModelManeger::Destroy(unsigned char)
void Destroy__16MenuModelManegerFUc(MenuModelManeger *this,char param_2)
{
  ulong uVar1;
  DIntr();
  uVar1 = ((ulong)this->f_46 /*u8 **/ & 0x3f) >> 5;
  if (this->f_18 /*int **/ != 0) {
    SafeDestroy__13MenuModelPackFv(this->f_18 /*u32 **/);
    this->f_18 /*u32 **/ = 0;
  }
  this->f_6a /*u16 **/ = 4;
  this->f_46 /*u8 **/ = this->f_46 /*u8 **/ & 0xbf;
  this->f_47 /*u8 **/ = 0;
  if (uVar1 != 0) {
    this->f_46 /*u8 **/ = this->f_46 /*u8 **/ & 0x7f | 0x80;
  }
  if (param_2 != '\0') {
    this->f_c /*u8 **/ = 1;
    this->f_e /*u8 **/ = 0;
    if (uVar1 == 0) {
      this->f_46 /*u8 **/ = this->f_46 /*u8 **/ & 0xf7 | 8;
    }
    else {
      this->f_46 /*u8 **/ = this->f_46 /*u8 **/ & 0xef | 0x10;
    }
  }
  EIntr();
  return;
}

// JP: 0x00282870  Access__16MenuModelManegerFv  size 0xfc
// MenuModelManeger::Access()
void Access__16MenuModelManegerFv(MenuModelManeger *this)
{
  u8 bVar1;
  DIntr();
  if ((long)((ulong)this->f_46 /*u8 **/ << 0x3a) < 0) {
    this->f_46 /*u8 **/ = this->f_46 /*u8 **/ & 0xbf | 0x40;
  }
  else {
    bVar1 = OrderFile__16MenuModelManegerFv(this);
    this->f_46 /*u8 **/ = this->f_46 /*u8 **/ & 0xdf | (bVar1 & 1) << 5;
  }
  this->f_64 /*u16 **/ = 0xffff;
  this->f_47 /*u8 **/ = 7;
  memset((void *)(this + 0x48),0,0x1c);
  this->f_46 /*u8 **/ = this->f_46 /*u8 **/ & 0x7f;
  this->f_6a /*u16 **/ = 4;
  EIntr();
  return;
}

// JP: 0x00282970  Reset__16MenuModelManegerFv  size 0x138
// MenuModelManeger::Reset()
void Reset__16MenuModelManegerFv(MenuModelManeger *this)
{
  u32 uVar1;
  long lVar2;
  int iVar3;
  DIntr();
  for (iVar3 = 0; iVar3 < 7; iVar3 = iVar3 + 1) {
    *(u16 *)(this + iVar3 * 2 + 0x38) = 0xffff;
  }
  memset((void *)(this + 0x1c),0,0x1c);
  if (this->f_18 /*int **/ != 0) {
    SafeDestroy__13MenuModelPackFv(this->f_18 /*u32 **/);
    this->f_18 /*u32 **/ = 0;
  }
  lVar2 = __nw__FUi(0x70);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = __ct__13MenuModelPackFv(lVar2);
  }
  this->f_18 /*u32 **/ = uVar1;
  Create__13MenuModelPackFP16MenuModelManeger(this->f_18 /*u32 **/,this);
  if ((long)((ulong)this->f_46 /*u8 **/ << 0x3a) < 0) {
    this->f_46 /*u8 **/ = this->f_46 /*u8 **/ & 0x7f | 0x80;
  }
  this->f_47 /*u8 **/ = 0;
  EIntr();
  return;
}

// JP: 0x00282ab0  OrderFile__16MenuModelManegerFv  size 0x170
// MenuModelManeger::OrderFile()
u32 OrderFile__16MenuModelManegerFv(MenuModelManeger *this)
{
  short sVar1;
  char *__format;
  int iVar2;
  char acStack_90 [64];
  char acStack_50 [64];
  int iStack_10;
  iVar2 = 0;
  while( true ) {
    if (6 < iVar2) {
      return 0;
    }
    sVar1 = *(short *)(this + iVar2 * 2 + 0x38);
    __format = *(char **)(this + iVar2 * 4 + 0x1c);
    if ((__format != (char *)0x0) && (sVar1 != -1)) break;
    iVar2 = iVar2 + 1;
  }
  iStack_10 = this;
  if ((iVar2 == 1) || (iVar2 == 0)) {
    sprintf(acStack_50,__format,this->f_68 /*u16 **/,sVar1);
  }
  else {
    sprintf(acStack_50,__format,sVar1);
  }
  sprintf(acStack_90,(char *)&_2930,pDataPath__7SysTool,acStack_50);
  ReadOrder__11DvdromOrderFPCcPFiP9BufMemoryiPcPv_iiPvi
            (Dvdromour__11DvdromOrder,acStack_90,0x282590,iVar2,iStack_10,0);
  *(u16 *)(iStack_10 + iVar2 * 2 + 0x38) = 0xffff;
  return 1;
}

// JP: 0x00282c20  ReadFile__16MenuModelManegerFiP9BufMemory  size 0x27c
// MenuModelManeger::ReadFile(int, BufMemory*)
u32 ReadFile__16MenuModelManegerFiP9BufMemory(MenuModelManeger *this,int param_2,int param_3)
{
  u32 uVar1;
  int iVar2;
  uint uVar3;
  long lVar4;
  ulong uVar5;
  this->f_46 /*u8 **/ = this->f_46 /*u8 **/ & 0xdf;
  if ((long)((ulong)this->f_46 /*u8 **/ << 0x3b) < 0) {
    this->f_6a /*u16 **/ = 4;
    this->f_46 /*u8 **/ = this->f_46 /*u8 **/ & 0xf7 | 8;
    uVar1 = 1;
  }
  else if ((long)((ulong)this->f_46 /*u8 **/ << 0x38) < 0) {
    this->f_46 /*u8 **/ = this->f_46 /*u8 **/ & 0x7f;
    uVar1 = 1;
  }
  else {
    if ((long)((ulong)this->f_46 /*u8 **/ << 0x39) < 0) {
      uVar1 = 1;
      this->f_46 /*u8 **/ = this->f_46 /*u8 **/ & 0xbf;
    }
    else {
      if ((param_2 == 6) || (param_2 == 5)) {
        lVar4 = __nw__FUi(0x520);
        iVar2 = 0;
        if (lVar4 != 0) {
          iVar2 = __ct__15MenuEffectModelFv(lVar4);
        }
        *(u32 *)(iVar2 + 0x510) = this->f_18 /*u32 **/;
        *(int *)(this->f_18 /*int **/ + (param_2 + -5) * 4 + 0x34) = iVar2;
      }
      *(int *)(this->f_18 /*int **/ + param_2 * 4 + 0x3c) = param_3;
      uVar1 = 0;
      *(u32 *)(this + param_2 * 4 + 0x48) = *(u32 *)(param_3 + 4);
    }
    uVar3 = OrderFile__16MenuModelManegerFv(this);
    uVar5 = (ulong)this->f_46 /*u8 **/ & 0xffffffffffffffdf | (long)(int)((uVar3 & 1) << 5);
    this->f_46 /*char **/ = (char)uVar5;
    if (-1 < (long)(uVar5 << 0x3a)) {
      this->f_47 /*u8 **/ = this->f_47 /*u8 **/ & 0xfb;
    }
  }
  return uVar1;
}

// JP: 0x00282ea0  Polling__16MenuModelManegerFv  size 0x8a4
// MenuModelManeger::Polling()
u32 Polling__16MenuModelManegerFv(MenuModelManeger *this)
{
  short sVar1;
  int iVar2;
  u32 uVar3;
  u16 uVar4;
  u16 uVar5;
  int iVar6;
  int iVar7;
  char *pcVar8;
  u32 uVar9;
  u64 uVar10;
  long lVar11;
  int unaff_s1_lo;
  uint uVar12;
  iVar2 = this->f_18 /*int **/;
  if (iVar2 != 0) {
    unaff_s1_lo = *(int *)(this->f_18 /*int **/ + 0x20);
  }
  sVar1 = this->f_6a /*short **/;
  if (sVar1 == 4) {
    this->f_6a /*u16 **/ = 0;
    if ((long)((ulong)this->f_46 /*u8 **/ << 0x3c) < 0) {
      return 1;
    }
  }
  else if (sVar1 == 3) {
    if ((long)((ulong)this->f_46 /*u8 **/ << 0x3e) < 0) {
      iVar6 = GetActive__4CPadFi(0);
      if (*(char *)((&m_pCoreArray__4CPad)[*(int *)(iVar6 + 4)] + 0x8b) == '\0') {
        iVar6 = GetActive__4CPadFi(0);
        if (*(char *)((&m_pCoreArray__4CPad)[*(int *)(iVar6 + 4)] + 0x8a) != '\0') {
          SetAngle__9MenuModelFf(*(float *)(unaff_s1_lo + 0x4b8) + addAngle__9MenuModel,unaff_s1_lo)
          ;
        }
      }
      else {
        SetAngle__9MenuModelFf(*(float *)(unaff_s1_lo + 0x4b8) - addAngle__9MenuModel,unaff_s1_lo);
      }
      CalcMatrix__9MenuModelFv(unaff_s1_lo);
    }
    AddTime__13MenuModelPackFf(this->f_6c /*u32 **/,iVar2);
  }
  else if (sVar1 == 2) {
    iVar6 = *(int *)(unaff_s1_lo + 0x28c) + -8;
    *(int *)(unaff_s1_lo + 0x28c) = iVar6;
    if (iVar6 == 0) {
      this->f_6a /*u16 **/ = 5;
    }
    SetAlpha__13MenuModelPackFUc(iVar2,*(uint *)(unaff_s1_lo + 0x28c) & 0xff);
    AddTime__13MenuModelPackFf(this->f_6c /*u32 **/,iVar2);
  }
  else if (sVar1 == 1) {
    iVar6 = *(int *)(unaff_s1_lo + 0x28c) + 8;
    *(int *)(unaff_s1_lo + 0x28c) = iVar6;
    if (0x80 < iVar6) {
      *(u32 *)(unaff_s1_lo + 0x28c) = 0x80;
      DisableAlpha__13MenuModelPackFv(iVar2);
      this->f_6a /*u16 **/ = 3;
    }
    SetAlpha__13MenuModelPackFUc(iVar2,*(uint *)(unaff_s1_lo + 0x28c) & 0xff);
    AddTime__13MenuModelPackFf(this->f_6c /*u32 **/,iVar2);
  }
  if ((long)((ulong)this->f_47 /*u8 **/ << 0x3e) < 0) {
    if (this->f_64 /*short **/ < 0) {
      for (uVar12 = 0; uVar12 < 7; uVar12 = uVar12 + 1 & 0xffff) {
        if (*(int *)(this + uVar12 * 4 + 0x48) != 0) {
          this->f_66 /*u16 **/ = 0;
          this->f_64 /*short **/ = (short)uVar12;
          break;
        }
      }
    }
    if (this->f_64 /*short **/ < 0) {
      if (-1 < (long)((ulong)this->f_47 /*u8 **/ << 0x3d)) {
        this->f_47 /*u8 **/ = this->f_47 /*u8 **/ & 0xfd;
        if ((this->f_47 /*u8 **/ & 1) != 0) {
          Order__13MenuModelPackFv(iVar2);
        }
        this->f_6a /*u16 **/ = 1;
      }
    }
    else {
      uVar3 = *(u32 *)(this + this->f_64 /*short **/ * 4 + 0x48);
      uVar4 = GetFileCount(uVar3);
      iVar6 = GetTimer__7SysToolFv();
      for (uVar5 = this->f_66 /*u16 **/; uVar5 < uVar4; uVar5 = uVar5 + 1) {
        iVar7 = GetTimer__7SysToolFv();
        if (3 < (uint)(iVar7 - iVar6)) {
          this->f_66 /*u16 **/ = uVar5;
          return 0;
        }
        pcVar8 = (char *)GetFileID(uVar3,uVar5);
        uVar10 = GetFileEntry(uVar3,uVar5);
        switch(this->f_64 /*u16 **/) {
        case 0:
        case 1:
          iVar7 = strcmp(pcVar8,(char *)&_3095);
          if (iVar7 == 0) {
            if (*(int *)(iVar2 + 0x28) == 0) {
              lVar11 = __nw__FUi(0x4e0);
              uVar9 = 0;
              if (lVar11 != 0) {
                uVar9 = __ct__9MenuModelFv(lVar11);
              }
              *(u32 *)(iVar2 + 0x28) = uVar9;
            }
            (**(code **)(*(int *)(*(int *)(iVar2 + 0x28) + 0x10) + 0x24))
                      (*(int *)(iVar2 + 0x28),uVar10);
          }
          else {
            iVar7 = strcmp(pcVar8,(char *)&_3096);
            if (iVar7 == 0) {
              if (*(int *)(iVar2 + 0x2c) == 0) {
                lVar11 = __nw__FUi(0x4e0);
                uVar9 = 0;
                if (lVar11 != 0) {
                  uVar9 = __ct__9MenuModelFv(lVar11);
                }
                *(u32 *)(iVar2 + 0x2c) = uVar9;
              }
              (**(code **)(*(int *)(*(int *)(iVar2 + 0x2c) + 0x10) + 0x24))
                        (*(int *)(iVar2 + 0x2c),uVar10);
            }
            else {
              iVar7 = strcmp(pcVar8,(char *)&_3097);
              if (iVar7 == 0) {
                if (*(int *)(iVar2 + 0x28) != 0) {
                  createMotion__5ModelFPUc(*(u32 *)(iVar2 + 0x28),uVar10);
                }
                if (*(int *)(iVar2 + 0x2c) != 0) {
                  createMotion__5ModelFPUc(*(u32 *)(iVar2 + 0x2c),uVar10);
                }
              }
            }
          }
          break;
        case 2:
        case 3:
        case 4:
          iVar7 = strcmp(pcVar8,(char *)&_3090);
          if ((iVar7 == 0) || (iVar7 = strcmp(pcVar8,(char *)&_3091), iVar7 == 0)) {
            if ((long)((ulong)this->f_47 /*u8 **/ << 0x3c) < 0) {
              (**(code **)(*(int *)(*(int *)(iVar2 + 0x24) + 0x10) + 0x24))
                        (*(int *)(iVar2 + 0x24),uVar10);
            }
            else {
              (**(code **)(*(int *)(unaff_s1_lo + 0x10) + 0x24))(unaff_s1_lo,uVar10);
              this->f_47 /*u8 **/ = this->f_47 /*u8 **/ & 0xf7 | 8;
            }
          }
          else {
            iVar7 = strcmp(pcVar8,(char *)&_3092);
            if (iVar7 == 0) {
              pcVar8 = (char *)createMotion__5ModelFPUc(unaff_s1_lo,uVar10);
              iVar7 = strncmp((char *)&_3093,pcVar8,3);
              if (iVar7 == 0) {
                *(char *)(iVar2 + 0x68) = *(char *)(iVar2 + 0x68) + '\x01';
              }
            }
            else {
              iVar7 = strcmp(pcVar8,(char *)&_3094);
              if (iVar7 == 0) {
                (**(code **)(*(int *)(*(int *)(iVar2 + 0x24) + 0x10) + 0x24))
                          (*(int *)(iVar2 + 0x24),uVar10);
              }
            }
          }
          break;
        case 5:
        case 6:
          iVar7 = strcmp(pcVar8,(char *)&_3098);
          if (iVar7 == 0) {
            iVar7 = *(int *)(iVar2 + (this->f_64 /*short **/ + -5) * 4 + 0x34);
            (**(code **)(*(int *)(iVar7 + 0x10) + 0x24))(iVar7,uVar10);
            SetTest__15MenuEffectModelFi(iVar7,0);
          }
          else {
            iVar7 = strcmp(pcVar8,(char *)&_3099);
            if (iVar7 == 0) {
              createMotion__5ModelFPUc
                        (*(u32 *)(iVar2 + (this->f_64 /*short **/ + -5) * 4 + 0x34),uVar10
                        );
            }
          }
        }
      }
      *(u32 *)(this + this->f_64 /*short **/ * 4 + 0x48) = 0;
      this->f_64 /*u16 **/ = 0xffff;
    }
  }
  return 0;
}

// JP: 0x00283750  Event__16MenuModelManegerFP9MenuModelPCcPCc  size 0x10
// MenuModelManeger::Event(MenuModel*, const char*, const char*)
void Event__16MenuModelManegerFP9MenuModelPCcPCc(void)
{
  return;
}
