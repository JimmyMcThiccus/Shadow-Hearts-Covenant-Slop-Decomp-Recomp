/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x00329710  __ct__13SaveDeviceHDDFv  size 0x38
// SaveDeviceHDD::SaveDeviceHDD()
u64 __ct__13SaveDeviceHDDFv(SaveDeviceHDD *this)
{
  __ct__10SaveDeviceFv();
  *(u32 *)this = __vt__13SaveDeviceHDD;
  ((u32 *)this)[0xfd] = 0;
  return this;
}

// JP: 0x00329750  __dt__13SaveDeviceHDDFv  size 0xa0
// SaveDeviceHDD::~SaveDeviceHDD()
long __dt__13SaveDeviceHDDFv(SaveDeviceHDD *this,short param_2)
{
  int iVar1;
  u32 *puVar2;
  if (this != 0) {
    puVar2 = (u32 *)this;
    *puVar2 = __vt__13SaveDeviceHDD;
    if (puVar2[0xfd] != 0) {
      iVar1 = *(int *)(puVar2[0xfd] + 0xa4);
      if (iVar1 != 0) {
        __dt__9BufMemoryFv(iVar1,1);
        *(u32 *)(puVar2[0xfd] + 0xa4) = 0;
      }
      close__9FileIOLibFP7_FIOHND(ourFio__9FileIOLib,puVar2[0xfd]);
    }
    __dt__10SaveDeviceFv(this,0);
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}

// JP: 0x003297f0  Sync__13SaveDeviceHDDFv  size 0x614
// SaveDeviceHDD::Sync()
u64 Sync__13SaveDeviceHDDFv(SaveDeviceHDD *this)
{
  char cVar1;
  short sVar2;
  int *piVar3;
  int iVar4;
  long lVar5;
  u64 uVar6;
  int *piVar7;
  piVar7 = (int *)this;
  if (piVar7[0xfd] != 0) {
    iVar4 = getStatus__9FileIOLibFP7_FIOHND(ourFio__9FileIOLib);
    piVar7[5] = iVar4;
    if ((piVar7[5] != 0xf003) && (piVar7[5] != 0)) {
      return 0;
    }
  }
  if ((short)piVar7[2] == 2) {
    if (*(short *)((int)piVar7 + 10) == 1) {
      if (*(int *)(piVar7[0xfd] + 0xa4) != 0) {
        __dt__9BufMemoryFv();
        *(u32 *)(piVar7[0xfd] + 0xa4) = 0;
      }
      close__9FileIOLibFP7_FIOHND(ourFio__9FileIOLib,piVar7[0xfd]);
      piVar7[0xfd] = 0;
      *(u16 *)(piVar7 + 2) = 0;
      *(u16 *)((int)piVar7 + 10) = 0;
    }
    else if ((*(short *)((int)piVar7 + 10) == 0) && (piVar7[5] == 0)) {
      lVar5 = write__9FileIOLibFP7_FIOHNDPcib
                        (ourFio__9FileIOLib,piVar7[0xfd],piVar7[0xfb],piVar7[0xfc],0);
      if (lVar5 != 1) {
        return 0xffffffffffffffff;
      }
      *(short *)((int)piVar7 + 10) = *(short *)((int)piVar7 + 10) + 1;
    }
  }
  else if ((short)piVar7[2] == 1) {
    sVar2 = *(short *)((int)piVar7 + 10);
    if (sVar2 != 2) {
      if (sVar2 != 1) {
        if (sVar2 == 0) {
          if (piVar7[5] == 0xf003) {
            *(u16 *)((int)piVar7 + 10) = 2;
          }
          else {
            lVar5 = read__9FileIOLibFP7_FIOHNDP9BufMemoryi(ourFio__9FileIOLib,piVar7[0xfd],0,0);
            if (lVar5 != 1) {
              return 0xffffffffffffffff;
            }
            *(short *)((int)piVar7 + 10) = *(short *)((int)piVar7 + 10) + 1;
          }
        }
        goto LAB_003299e0;
      }
      NewHeap__10SaveDeviceFi(this,*(u32 *)(piVar7[0xfd] + 0x90));
      memcpy((void *)piVar7[0xfb],*(void **)(*(int *)(piVar7[0xfd] + 0xa4) + 4),(long)piVar7[0xfc]);
    }
    if (*(int *)(piVar7[0xfd] + 0xa4) != 0) {
      __dt__9BufMemoryFv(*(int *)(piVar7[0xfd] + 0xa4),1);
      *(u32 *)(piVar7[0xfd] + 0xa4) = 0;
    }
    close__9FileIOLibFP7_FIOHND(ourFio__9FileIOLib,piVar7[0xfd]);
    piVar7[0xfd] = 0;
    *(u16 *)(piVar7 + 2) = 0;
    *(u16 *)((int)piVar7 + 10) = 0;
  }
LAB_003299e0:
  if ((short)piVar7[2] == 0) {
    switch(*(u8 *)((int)piVar7 + 6)) {
    case 0:
      return 0xfffffffffffffffe;
    case 1:
      cVar1 = *(char *)((int)piVar7 + 7);
      if (cVar1 == '\x03') {
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
      if (cVar1 == '\x02') {
        lVar5 = (**(code **)(*piVar7 + 0x30))(this,0x3f9aa0);
        if (lVar5 != -1) {
          *(char *)((int)piVar7 + 7) = *(char *)((int)piVar7 + 7) + '\x01';
        }
      }
      else if (cVar1 == '\x01') {
        iVar4 = checkPFSFreeSize__9FileIOLibFPCc(0x40a928);
        piVar7[4] = iVar4;
        *(char *)((int)piVar7 + 7) = *(char *)((int)piVar7 + 7) + '\x01';
      }
      else if (cVar1 == '\0') {
        lVar5 = SetPfsDeviceName__9FileIOLibFPCc(0x40a928);
        if (lVar5 != 0) {
          return 0xffffffffffffffff;
        }
        *(char *)((int)piVar7 + 7) = *(char *)((int)piVar7 + 7) + '\x01';
      }
      break;
    case 2:
      SetPfsDeviceName__9FileIOLibFPCc(0x40a930);
      *(u8 *)((int)piVar7 + 6) = 0;
      *(u8 *)((int)piVar7 + 7) = 0;
      return 1;
    case 3:
      cVar1 = *(char *)((int)piVar7 + 7);
      if (cVar1 == '\x03') {
        *(u8 *)((int)piVar7 + 6) = 0;
        *(u8 *)((int)piVar7 + 7) = 0;
        return 1;
      }
      if (cVar1 == '\x02') {
        iVar4 = piVar7[7];
        uVar6 = GetHeap__10SystemFileCFv(piVar7 + 7);
        lVar5 = (**(code **)(*piVar7 + 0x34))
                          (this,0x3f9aa0,uVar6,
                           (uint)*(u16 *)(iVar4 + 0xe) + *(int *)(iVar4 + 8));
        if (lVar5 != -1) {
          *(char *)((int)piVar7 + 7) = *(char *)((int)piVar7 + 7) + '\x01';
        }
      }
      else if (cVar1 == '\x01') {
        piVar3 = (int *)piVar7[9];
        lVar5 = (**(code **)(*piVar7 + 0x34))(this,0x40a938,(int)piVar3 + *piVar3,piVar3[1]);
        if (lVar5 == -1) {
          *(char *)((int)piVar7 + 7) = *(char *)((int)piVar7 + 7) + '\x01';
        }
      }
      else if ((((cVar1 == '\0') && (-1 < (long)((ulong)*(u8 *)((int)piVar7 + 5) << 0x3d))) &&
               (piVar7[8] != 0)) &&
              (lVar5 = (**(code **)(*piVar7 + 0x34))(this,0x3f9a90,piVar7 + 10,0x3c4),
              lVar5 != -1)) {
        *(u8 *)((int)piVar7 + 7) = 1;
      }
      break;
    case 4:
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
        iVar4 = piVar7[7];
        uVar6 = GetHeap__10SystemFileCFv(piVar7 + 7);
        lVar5 = (**(code **)(*piVar7 + 0x34))
                          (this,0x3f9aa0,uVar6,
                           (uint)*(u16 *)(iVar4 + 0xe) + *(int *)(iVar4 + 8));
        if (lVar5 != -1) {
          *(u8 *)((int)piVar7 + 7) = 1;
        }
      }
      break;
    case 6:
      if (*(char *)((int)piVar7 + 7) == '\x01') {
        lVar5 = SetData__10SystemFileFP14_SystemFileHdr(piVar7 + 7,piVar7[0xfb]);
        if (lVar5 == 0) {
          return 0xffffffffffffffff;
        }
        FlushCommon__10SystemFileFv(piVar7 + 7);
        *(u8 *)((int)piVar7 + 6) = 0;
        *(u8 *)((int)piVar7 + 7) = 0;
        return 1;
      }
      if (*(char *)((int)piVar7 + 7) == '\0') {
        lVar5 = CreateSection__8SaveDataFP12_SaveDataHdr(0x421e70,piVar7[0xfb]);
        if (lVar5 == 0) {
          return 0xffffffffffffffff;
        }
        lVar5 = (**(code **)(*piVar7 + 0x30))(this,0x3f9aa0);
        if (lVar5 != -1) {
          *(u8 *)((int)piVar7 + 7) = 1;
        }
      }
      break;
    case 7:
      *(u8 *)((int)piVar7 + 6) = 0;
      *(u8 *)((int)piVar7 + 7) = 0;
      return 1;
    case 8:
      *(u8 *)((int)piVar7 + 6) = 0;
      *(u8 *)((int)piVar7 + 7) = 0;
      return 1;
    }
  }
  return 0;
}

// JP: 0x00329e10  Open__13SaveDeviceHDDFi  size 0x144
// SaveDeviceHDD::Open(int)
u32 Open__13SaveDeviceHDDFi(SaveDeviceHDD *this,u64 param_2)
{
  long lVar1;
  this->f_5 /*u8 **/ = 0;
  lVar1 = checkHddStatus__9FileIOLibFPCc(0x40a920);
  if (lVar1 == 1) {
    this->f_5 /*u8 **/ = this->f_5 /*u8 **/ & 0xfe | 1;
    this->f_7 /*u8 **/ = 3;
  }
  else if (lVar1 == 0) {
    this->f_c /*u32 **/ = 1;
    this->f_5 /*u8 **/ = this->f_5 /*u8 **/ & 0xfe | 1;
    lVar1 = SetHddDeviceName__9FileIOLibFPCc(0x40a920);
    if (lVar1 != 0) {
      return 0xffffffff;
    }
    lVar1 = mountPartition__9FileIOLibFPcPcPc(0x40a928,0x3f9a80,0x3ff188);
    if (lVar1 < 0) {
      if (lVar1 != -5) {
        return 0xffffffff;
      }
      this->f_5 /*u8 **/ = this->f_5 /*u8 **/ & 0xdf | 0x20;
      this->f_7 /*u8 **/ = 3;
    }
    else {
      this->f_7 /*u8 **/ = 0;
    }
  }
  else if (lVar1 == 3) {
    return 0xffffffff;
  }
  this->f_4 /*char **/ = (char)param_2;
  this->f_10 /*u32 **/ = 0;
  Create__10SystemFileFi(this + 0x1c,param_2);
  this->f_6 /*u8 **/ = 1;
  return 1;
}

// JP: 0x00329f60  Close__13SaveDeviceHDDFv  size 0x48
// SaveDeviceHDD::Close()
u32 Close__13SaveDeviceHDDFv(SaveDeviceHDD *this)
{
  DeleteHeap__10SaveDeviceFv();
  this->f_5 /*u8 **/ = 0;
  Release__10SystemFileFv(this + 0x1c);
  unmountPartition__9FileIOLibFPc(0x40a928);
  this->f_6 /*u8 **/ = 2;
  this->f_7 /*u8 **/ = 0;
  return 1;
}

// JP: 0x00329fb0  CreateSystem__13SaveDeviceHDDFv  size 0x34
// SaveDeviceHDD::CreateSystem()
u32 CreateSystem__13SaveDeviceHDDFv(SaveDeviceHDD *this)
{
  LoadIcon__10SaveDeviceFv();
  this->f_6 /*u8 **/ = 3;
  this->f_7 /*u8 **/ = 0;
  return 1;
}

// JP: 0x00329ff0  GetStatus__13SaveDeviceHDDFv  size 0x14
// SaveDeviceHDD::GetStatus()
u32 GetStatus__13SaveDeviceHDDFv(SaveDeviceHDD *this)
{
  this->f_6 /*u8 **/ = 4;
  this->f_7 /*u8 **/ = 0;
  return 1;
}

// JP: 0x0032a010  Delete__13SaveDeviceHDDFUc  size 0x14
// SaveDeviceHDD::Delete(unsigned char)
u32 Delete__13SaveDeviceHDDFUc(SaveDeviceHDD *this)
{
  this->f_6 /*u8 **/ = 7;
  this->f_7 /*u8 **/ = 0;
  return 1;
}

// JP: 0x0032a030  Format__13SaveDeviceHDDFv  size 0xd0
// SaveDeviceHDD::Format()
u32 Format__13SaveDeviceHDDFv(SaveDeviceHDD *this)
{
  u64 uVar1;
  long lVar2;
  char acStack_170 [32];
  u8 auStack_150 [64];
  u8 auStack_110 [268];
  u32 uStack_4;
  uStack_4 = 0x2000;
  sceFormat(0x40a920,0,0,0);
  uVar1 = sceDopen(0x40a920);
  lVar2 = sceDread(uVar1,auStack_150);
  while (0 < lVar2) {
    sprintf(acStack_170,(char *)&_1739,0x40a920,auStack_110);
    sceFormat(0x3ff198,acStack_170,&uStack_4,4);
    lVar2 = sceDread(uVar1,auStack_150);
  }
  sceDclose(uVar1);
  this->f_6 /*u8 **/ = 8;
  this->f_7 /*u8 **/ = 0;
  return 1;
}

// JP: 0x0032a100  Read__13SaveDeviceHDDFPCc  size 0x88
// SaveDeviceHDD::Read(const char*)
u32 Read__13SaveDeviceHDDFPCc(SaveDeviceHDD *this,u64 param_2)
{
  u32 uVar1;
  long lVar2;
  int iVar3;
  char acStack_40 [64];
  sprintf(acStack_40,_1750,0x3f9a70,0x3f9aa0,param_2);
  lVar2 = open__9FileIOLibFPcib(ourFio__9FileIOLib,acStack_40,0xffffffff80000001,1);
  iVar3 = (int)this;
  *(int *)(iVar3 + 0x3f4) = (int)lVar2;
  if (lVar2 == 0) {
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

// JP: 0x0032a190  Write__13SaveDeviceHDDFPCcPUci  size 0xa8
// SaveDeviceHDD::Write(const char*, unsigned char*, int)
u32
Write__13SaveDeviceHDDFPCcPUci
          (SaveDeviceHDD *this,u64 param_2,u32 param_3,u32 param_4)
{
  u32 uVar1;
  long lVar2;
  int iVar3;
  char acStack_40 [64];
  EEFioStatus = (undefined *)0x0;
  sprintf(acStack_40,_1762,0x3f9a70,0x3f9aa0,param_2);
  lVar2 = open__9FileIOLibFPcib(ourFio__9FileIOLib,acStack_40,0xffffffff80000202,1);
  iVar3 = (int)this;
  *(int *)(iVar3 + 0x3f4) = (int)lVar2;
  if (lVar2 == 0) {
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
