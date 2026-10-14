/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x00328a50  __ct__12SaveDeviceMCFv  size 0x34
// SaveDeviceMC::SaveDeviceMC()
u64 __ct__12SaveDeviceMCFv(SaveDeviceMC *this)
{
  __ct__10SaveDeviceFv();
  *(u32 *)this = __vt__12SaveDeviceMC;
  return this;
}

// JP: 0x00328a90  __dt__12SaveDeviceMCFv  size 0x60
// SaveDeviceMC::~SaveDeviceMC()
long __dt__12SaveDeviceMCFv(SaveDeviceMC *this,short param_2)
{
  if (this != 0) {
    *(u32 *)this = __vt__12SaveDeviceMC;
    __dt__10SaveDeviceFv(this,0);
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}

// JP: 0x00328af0  Sync__12SaveDeviceMCFv  size 0x89c
// SaveDeviceMC::Sync()
u64 Sync__12SaveDeviceMCFv(SaveDeviceMC *this)
{
  char cVar1;
  short sVar2;
  int iVar3;
  int *piVar4;
  long lVar5;
  u64 uVar6;
  int *piVar7;
  piVar7 = (int *)this;
  lVar5 = sceMcSync(1,piVar7 + 6,piVar7 + 5);
  if (lVar5 == 1) {
    iVar3 = piVar7[6];
    if (((iVar3 == 0xf) || (iVar3 == 0xb)) || (iVar3 == 0xc)) {
      if ((piVar7[5] != 0) && (piVar7[5] != -4)) {
        return 0xffffffffffffffff;
      }
    }
    else if (((iVar3 == 0x10) || (iVar3 == 6)) || ((iVar3 == 5 || (iVar3 == 4)))) {
      if (piVar7[5] < 0) {
        return 0xffffffffffffffff;
      }
    }
    else if (iVar3 == 2) {
      piVar7[0xfe] = piVar7[5];
    }
    else {
      if ((iVar3 != 3) && (iVar3 != 1)) {
        return 0xfffffffffffffffe;
      }
      if (piVar7[5] < -4) {
        return 0xffffffffffffffff;
      }
    }
  }
  else if (lVar5 == 0) {
    return 0;
  }
  if ((short)piVar7[2] == 2) {
    sVar2 = *(short *)((int)piVar7 + 10);
    if (sVar2 == 2) {
      DeleteHeap__10SaveDeviceFv(this);
      *(u16 *)(piVar7 + 2) = 0;
      *(u16 *)((int)piVar7 + 10) = 0;
    }
    else if (sVar2 == 1) {
LAB_00328dc8:
      lVar5 = sceMcClose(piVar7[0xfe]);
      if (lVar5 < 0) {
        return 0xffffffffffffffff;
      }
      piVar7[0xfe] = -1;
      *(u16 *)((int)piVar7 + 10) = 2;
    }
    else if (sVar2 == 0) {
      if ((piVar7[0xfb] == 0) || (piVar7[0xfc] == 0)) goto LAB_00328dc8;
      lVar5 = sceMcWrite(piVar7[0xfe]);
      if (lVar5 < 0) {
        return 0xffffffffffffffff;
      }
      *(u16 *)((int)piVar7 + 10) = 1;
    }
  }
  else if ((short)piVar7[2] == 1) {
    sVar2 = *(short *)((int)piVar7 + 10);
    if (sVar2 == 4) {
      *(u16 *)(piVar7 + 2) = 0;
      *(u16 *)((int)piVar7 + 10) = 0;
    }
    else if (sVar2 == 3) {
      lVar5 = sceMcClose(piVar7[0xfe]);
      if (lVar5 < 0) {
        return 0xffffffffffffffff;
      }
      *(u16 *)((int)piVar7 + 10) = 4;
    }
    else if (sVar2 == 2) {
      lVar5 = sceMcRead(piVar7[0xfe],piVar7[0xfb],piVar7[0xfc]);
      if (lVar5 < 0) {
        return 0xffffffffffffffff;
      }
      *(u16 *)((int)piVar7 + 10) = 3;
    }
    else if (sVar2 == 1) {
      if (piVar7[5] == 0) {
        *(u16 *)((int)piVar7 + 10) = 4;
      }
      else {
        NewHeap__10SaveDeviceFi(this);
        lVar5 = sceMcSeek(piVar7[0xfe],0,0);
        if (lVar5 < 0) {
          return 0xffffffffffffffff;
        }
        *(u16 *)((int)piVar7 + 10) = 2;
      }
    }
    else if (sVar2 == 0) {
      if (piVar7[0xfe] < 0) {
        *(u16 *)((int)piVar7 + 10) = 4;
      }
      else {
        lVar5 = sceMcSeek(piVar7[0xfe],0);
        if (lVar5 < 0) {
          return 0xffffffffffffffff;
        }
        *(u16 *)((int)piVar7 + 10) = 1;
      }
    }
  }
  if ((short)piVar7[2] == 0) {
    switch(*(u8 *)((int)piVar7 + 6)) {
    case 0:
      return 0xfffffffffffffffe;
    case 1:
      cVar1 = *(char *)((int)piVar7 + 7);
      if (cVar1 == '\x02') {
LAB_00328f10:
        if ((piVar7[0xfb] != 0) && (piVar7[0xfc] != 0)) {
          lVar5 = SetData__10SystemFileFP14_SystemFileHdr(piVar7 + 7);
          if (lVar5 == 0) {
            return 0xffffffffffffffff;
          }
          *(u8 *)((int)piVar7 + 5) = *(u8 *)((int)piVar7 + 5) & 0xfd | 2;
          DeleteHeap__10SaveDeviceFv(this);
        }
        *(u8 *)((int)piVar7 + 6) = 0;
        *(u8 *)((int)piVar7 + 7) = 0;
        return 1;
      }
      if (cVar1 == '\x01') {
        if (piVar7[5] != 0) goto LAB_00328f10;
        (**(code **)(*piVar7 + 0x30))(this,0x3f9aa0);
        *(u8 *)((int)piVar7 + 7) = 2;
      }
      else if (cVar1 == '\0') {
        *(u8 *)((int)piVar7 + 5) = *(u8 *)((int)piVar7 + 5) & 0xfe | 1;
        if ((piVar7[0xfd] == 2) && (piVar7[3] != 0)) {
          lVar5 = sceMcChdir((char)piVar7[1],0,0x3f9ac0,0);
          if (lVar5 < 0) {
            return 0xffffffffffffffff;
          }
          *(u8 *)((int)piVar7 + 7) = 1;
        }
        else {
          *(u8 *)((int)piVar7 + 7) = 2;
        }
      }
      break;
    case 2:
      *(u8 *)((int)piVar7 + 6) = 0;
      *(u8 *)((int)piVar7 + 7) = 0;
      return 1;
    case 3:
      cVar1 = *(char *)((int)piVar7 + 7);
      if (cVar1 == '\x04') {
        *(u8 *)((int)piVar7 + 6) = 0;
        *(u8 *)((int)piVar7 + 7) = 0;
        return 1;
      }
      if (cVar1 == '\x03') {
        piVar4 = (int *)piVar7[9];
        lVar5 = (**(code **)(*piVar7 + 0x34))(this,0x40a938,(int)piVar4 + *piVar4,piVar4[1]);
        if (lVar5 == -1) {
          return 0xffffffffffffffff;
        }
        *(u8 *)((int)piVar7 + 7) = 4;
      }
      else if (cVar1 == '\x02') {
        if ((-1 < (long)((ulong)*(u8 *)((int)piVar7 + 5) << 0x3d)) && (piVar7[8] != 0)) {
          lVar5 = (**(code **)(*piVar7 + 0x34))(this,0x3f9a90,piVar7 + 10,0x3c4);
          if (lVar5 == -1) {
            return 0xffffffffffffffff;
          }
          *(u8 *)((int)piVar7 + 7) = 3;
        }
      }
      else if (cVar1 == '\x01') {
        iVar3 = piVar7[7];
        uVar6 = GetHeap__10SystemFileCFv(piVar7 + 7);
        lVar5 = (**(code **)(*piVar7 + 0x34))
                          (this,0x3f9aa0,uVar6,
                           (uint)*(u16 *)(iVar3 + 0xe) + *(int *)(iVar3 + 8));
        if (lVar5 == -1) {
          return 0xffffffffffffffff;
        }
        *(u8 *)((int)piVar7 + 7) = 2;
      }
      else if (cVar1 == '\0') {
        lVar5 = sceMcChdir((char)piVar7[1],0,0x3f9ac0,0);
        if (lVar5 < 0) {
          return 0xffffffffffffffff;
        }
        *(u8 *)((int)piVar7 + 7) = 1;
      }
      break;
    case 4:
      if (piVar7[5] != 0) {
        return 0xffffffffffffffff;
      }
      *(u8 *)((int)piVar7 + 6) = 0;
      *(u8 *)((int)piVar7 + 7) = 0;
      return 1;
    case 5:
      if (*(char *)((int)piVar7 + 7) == '\x01') {
        *(u8 *)((int)piVar7 + 6) = 0;
        *(u8 *)((int)piVar7 + 7) = 0;
        return 1;
      }
      if (*(char *)((int)piVar7 + 7) == '\0') {
        StoreCommon__10SystemFileFv(piVar7 + 7);
        iVar3 = piVar7[7];
        uVar6 = GetHeap__10SystemFileCFv(piVar7 + 7);
        lVar5 = (**(code **)(*piVar7 + 0x34))
                          (this,0x3f9aa0,uVar6,
                           (uint)*(u16 *)(iVar3 + 0xe) + *(int *)(iVar3 + 8));
        if (lVar5 == -1) {
          return 0xffffffffffffffff;
        }
        *(u8 *)((int)piVar7 + 7) = 1;
      }
      break;
    case 6:
      if (*(char *)((int)piVar7 + 7) == '\x01') {
        if ((piVar7[0xfb] != 0) && (piVar7[0xfc] != 0)) {
          lVar5 = SetData__10SystemFileFP14_SystemFileHdr(piVar7 + 7);
          if (lVar5 == 0) {
            return 0xffffffffffffffff;
          }
          FlushCommon__10SystemFileFv(piVar7 + 7);
          DeleteHeap__10SaveDeviceFv(this);
          *(u8 *)((int)piVar7 + 6) = 0;
          *(u8 *)((int)piVar7 + 7) = 0;
          return 1;
        }
        return 0xffffffffffffffff;
      }
      if (*(char *)((int)piVar7 + 7) == '\0') {
        if ((piVar7[0xfb] == 0) || (piVar7[0xfc] == 0)) {
          return 0xffffffffffffffff;
        }
        lVar5 = CreateSection__8SaveDataFP12_SaveDataHdr(0x421e70);
        if (lVar5 == 0) {
          return 0xffffffffffffffff;
        }
        lVar5 = (**(code **)(*piVar7 + 0x30))(this,0x3f9aa0);
        if (lVar5 == -1) {
          return 0xffffffffffffffff;
        }
        *(u8 *)((int)piVar7 + 7) = 1;
      }
      break;
    case 7:
      if (*(char *)((int)piVar7 + 7) == '\x01') {
        *(u8 *)((int)piVar7 + 6) = 0;
        *(u8 *)((int)piVar7 + 7) = 0;
        return 1;
      }
      if (*(char *)((int)piVar7 + 7) == '\0') {
        iVar3 = piVar7[7];
        uVar6 = GetHeap__10SystemFileCFv(piVar7 + 7);
        lVar5 = (**(code **)(*piVar7 + 0x34))
                          (this,0x3f9aa0,uVar6,
                           (uint)*(u16 *)(iVar3 + 0xe) + *(int *)(iVar3 + 8));
        if (lVar5 == -1) {
          return 0xffffffffffffffff;
        }
        *(u8 *)((int)piVar7 + 7) = 1;
      }
      break;
    case 8:
      piVar7[3] = 1;
      *(u8 *)((int)piVar7 + 6) = 0;
      *(u8 *)((int)piVar7 + 7) = 0;
      return 1;
    }
  }
  return 0;
}

// JP: 0x00329390  Open__12SaveDeviceMCFi  size 0x7c
// SaveDeviceMC::Open(int)
u32 Open__12SaveDeviceMCFi(SaveDeviceMC *this,u64 param_2)
{
  u32 uVar1;
  long lVar2;
  sceMcInit();
  this->f_5 /*u8 **/ = 0;
  this->f_4 /*char **/ = (char)param_2;
  this->f_c /*u32 **/ = 0;
  this->f_10 /*u32 **/ = 0;
  Create__10SystemFileFi(this + 0x1c,param_2);
  lVar2 = sceMcGetInfo(param_2,0,this + 0x3f4,this + 0x10,this + 0xc);
  if (lVar2 < 0) {
    uVar1 = 0xffffffff;
  }
  else {
    uVar1 = 1;
    this->f_6 /*u8 **/ = 1;
  }
  return uVar1;
}

// JP: 0x00329410  Close__12SaveDeviceMCFv  size 0x44
// SaveDeviceMC::Close()
u32 Close__12SaveDeviceMCFv(SaveDeviceMC *this)
{
  DeleteHeap__10SaveDeviceFv();
  this->f_5 /*u8 **/ = 0;
  Release__10SystemFileFv(this + 0x1c);
  sceMcEnd();
  this->f_6 /*u8 **/ = 2;
  return 1;
}

// JP: 0x00329460  CreateSystem__12SaveDeviceMCFv  size 0x58
// SaveDeviceMC::CreateSystem()
u32 CreateSystem__12SaveDeviceMCFv(SaveDeviceMC *this)
{
  u32 uVar1;
  long lVar2;
  LoadIcon__10SaveDeviceFv();
  lVar2 = sceMcMkdir(this->f_4 /*u8 **/,0,0x3f9ac0);
  if (lVar2 < 0) {
    uVar1 = 0xffffffff;
  }
  else {
    this->f_6 /*u8 **/ = 3;
    uVar1 = 1;
    this->f_7 /*u8 **/ = 0;
  }
  return uVar1;
}

// JP: 0x003294c0  GetStatus__12SaveDeviceMCFv  size 0x58
// SaveDeviceMC::GetStatus()
u32 GetStatus__12SaveDeviceMCFv(SaveDeviceMC *this)
{
  u32 uVar1;
  long lVar2;
  lVar2 = sceMcGetInfo(this->f_4 /*u8 **/,0,0,0,0);
  if (lVar2 < 0) {
    uVar1 = 0xffffffff;
  }
  else {
    this->f_6 /*u8 **/ = 4;
    uVar1 = 1;
    this->f_7 /*u8 **/ = 0;
  }
  return uVar1;
}

// JP: 0x00329520  Delete__12SaveDeviceMCFUc  size 0xb8
// SaveDeviceMC::Delete(unsigned char)
u32 Delete__12SaveDeviceMCFUc(SaveDeviceMC *this,ulong param_2)
{
  int iVar1;
  int iVar2;
  u32 uVar3;
  long lVar4;
  char acStack_20 [32];
  iVar1 = this->f_1c /*int **/;
  param_2 = param_2 & 0xff;
  iVar2 = *(int *)(iVar1 + 0x1c);
  sprintf(acStack_20,sm_slotName__10SaveDevice,param_2);
  lVar4 = sceMcDelete(this->f_4 /*u8 **/,0,acStack_20);
  if (lVar4 < 0) {
    uVar3 = 0xffffffff;
  }
  else {
    *(u8 *)(iVar1 + iVar2 + (int)param_2 * 0x60) = 0xff;
    if (param_2 == *(u8 *)(this->f_1c /*int **/ + 0xc)) {
      SetCurrentSlot__10SystemFileFv(this + 0x1c);
    }
    this->f_6 /*u8 **/ = 7;
    uVar3 = 1;
    this->f_7 /*u8 **/ = 0;
  }
  return uVar3;
}

// JP: 0x003295e0  Format__12SaveDeviceMCFv  size 0x50
// SaveDeviceMC::Format()
u32 Format__12SaveDeviceMCFv(SaveDeviceMC *this)
{
  u32 uVar1;
  long lVar2;
  lVar2 = sceMcFormat(this->f_4 /*u8 **/,0);
  if (lVar2 < 0) {
    uVar1 = 0xffffffff;
  }
  else {
    this->f_6 /*u8 **/ = 8;
    uVar1 = 1;
    this->f_7 /*u8 **/ = 0;
  }
  return uVar1;
}

// JP: 0x00329630  Read__12SaveDeviceMCFPCc  size 0x60
// SaveDeviceMC::Read(const char*)
u32 Read__12SaveDeviceMCFPCc(SaveDeviceMC *this,u64 param_2)
{
  u32 uVar1;
  long lVar2;
  int iVar3;
  iVar3 = (int)this;
  lVar2 = sceMcOpen(*(u8 *)(iVar3 + 4),0,param_2,1);
  if (lVar2 < 0) {
    uVar1 = 0xffffffff;
  }
  else {
    DeleteHeap__10SaveDeviceFv(this);
    uVar1 = 1;
    *(u16 *)(iVar3 + 8) = 1;
    *(u16 *)(iVar3 + 10) = 0;
  }
  return uVar1;
}

// JP: 0x00329690  Write__12SaveDeviceMCFPCcPUci  size 0x80
// SaveDeviceMC::Write(const char*, unsigned char*, int)
u32
Write__12SaveDeviceMCFPCcPUci
          (SaveDeviceMC *this,u64 param_2,u32 param_3,u32 param_4)
{
  u32 uVar1;
  long lVar2;
  int iVar3;
  iVar3 = (int)this;
  lVar2 = sceMcOpen(*(u8 *)(iVar3 + 4),0,param_2,0x202);
  if (lVar2 < 0) {
    uVar1 = 0xffffffff;
  }
  else {
    DeleteHeap__10SaveDeviceFv(this);
    *(u32 *)(iVar3 + 0x3ec) = param_3;
    *(u32 *)(iVar3 + 0x3f0) = param_4;
    uVar1 = 1;
    *(u16 *)(iVar3 + 8) = 2;
    *(u16 *)(iVar3 + 10) = 0;
  }
  return uVar1;
}
