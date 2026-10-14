/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x003280c0  SetCRC__8SaveDataFPUcUi  size 0xb0
// SaveData::SetCRC(unsigned char*, unsigned int)
void SetCRC__8SaveDataFPUcUi(SaveData *this,int param_2)
{
  int iVar1;
  u8 *pbVar2;
  u8 *pbVar3;
  pbVar2 = (u8 *)((int)this + param_2);
  pbVar3 = (u8 *)(this + 1);
  iVar1 = 0;
  if (pbVar3 < pbVar2) {
    if (8 < (int)pbVar2 - (int)pbVar3) {
      do {
        iVar1 = iVar1 + (uint)*pbVar3 + (uint)pbVar3[1] + (uint)pbVar3[2] + (uint)pbVar3[3] +
                (uint)pbVar3[4] + (uint)pbVar3[5] + (uint)pbVar3[6] + (uint)pbVar3[7];
        pbVar3 = pbVar3 + 8;
      } while (pbVar3 < pbVar2 + -8);
    }
    for (; pbVar3 < pbVar2; pbVar3 = pbVar3 + 1) {
      iVar1 = iVar1 + (uint)*pbVar3;
    }
  }
  *this = iVar1;
  return;
}

// JP: 0x00328170  CheckCRC__8SaveDataFPUcUi  size 0x8
// SaveData::CheckCRC(unsigned char*, unsigned int)
u32 CheckCRC__8SaveDataFPUcUi(void)
{
  return 1;
}

// JP: 0x00328180  __ct__8SaveDataFv  size 0xc0
// SaveData::SaveData()
u64 __ct__8SaveDataFv(SaveData *this)
{
  int iVar1;
  __ct__7CPolObjFv();
  iVar1 = (int)this;
  *(u8 **)(iVar1 + 0x14) = __vt__8SaveData;
  *(u32 *)(iVar1 + 0x18) = 0;
  *(u32 *)(iVar1 + 0x20) = 0;
  *(u32 *)(iVar1 + 0x24) = 0;
  *(u8 *)(iVar1 + 0x28) = 0;
  *(u8 *)(iVar1 + 0x29) = 0;
  *(u8 *)(iVar1 + 0x2a) = 0;
  *(u8 *)(iVar1 + 0x2b) = 0xff;
  *(u32 *)(iVar1 + 0x1c) = 0x100100;
  memcpy((void *)(*(int *)(iVar1 + 0x1c) + 4),_1580,8);
  memset((void *)(*(int *)(iVar1 + 0x1c) + 0xc),0,8);
  *(u16 *)(*(int *)(iVar1 + 0x1c) + 0x14) = 0;
  *(u16 *)(*(int *)(iVar1 + 0x1c) + 0x16) = 0x20;
  *(u32 *)(*(int *)(iVar1 + 0x1c) + 0x18) = 0;
  **(u32 **)(iVar1 + 0x1c) = 0;
  *(u16 *)(*(int *)(iVar1 + 0x1c) + 0x1c) = 0;
  *(u16 *)(*(int *)(iVar1 + 0x1c) + 0x1e) = 0;
  return this;
}

// JP: 0x00328240  __dt__8SaveDataFv  size 0x60
// SaveData::~SaveData()
long __dt__8SaveDataFv(SaveData *this,short param_2)
{
  if (this != 0) {
    *(u8 **)((int)this + 0x14) = __vt__8SaveData;
    __dt__7CPolObjFv(this,0);
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}

// JP: 0x003282a0  Release__8SaveDataFv  size 0x68
// SaveData::Release()
void Release__8SaveDataFv(SaveData *this)
{
  int *piVar1;
  piVar1 = this->device;
  if (piVar1 != (int *)0x0) {
    if (piVar1 != (int *)0x0) {
      (**(code **)(*piVar1 + 8))(piVar1,1);
    }
    this->device = 0;
  }
  this->state = 0;
  this->pending_op = 0;
  this->op2a = 0;
  this->last_op = 0;
  this->slot = 0xff;
  return;
}

// JP: 0x00328310  GetSection__8SaveDataFPCUc  size 0x60
// SaveData::GetSection(const unsigned char*)
int GetSection__8SaveDataFPCUc(SaveData *this,void *param_2)
{
  int iVar1;
  int iVar2;
  iVar1 = this->sections;
  while ((iVar1 != 0 && (iVar2 = memcmp(*(void **)(iVar1 + 8),param_2,4), iVar2 != 0))) {
    iVar1 = *(int *)(iVar1 + 4);
  }
  return iVar1;
}

// JP: 0x00328370  OrderSection__8SaveDataFP15SaveDataSectionUi  size 0x58
// SaveData::OrderSection(SaveDataSection*, unsigned int)
void OrderSection__8SaveDataFP15SaveDataSectionUi(SaveData *this,SaveDataSection *saveDataSection,int param_3)
{
  int iVar1;
  iVar1 = this->heap;
  saveDataSection->hdr = *(int *)(iVar1 + 0x18) + iVar1 + (uint)*(u16 *)(iVar1 + 0x16);
  *(int *)(this->heap + 0x18) =
       *(int *)(this->heap + 0x18) + param_3 + 0x10;
  *(short *)(this->heap + 0x1c) = *(short *)(this->heap + 0x1c) + 1;
  if (this->sections != 0) {
    saveDataSection->next = this->sections;
  }
  this->sections = saveDataSection;
  return;
}

// JP: 0x003283d0  CreateSection__8SaveDataFP12_SaveDataHdr  size 0x16c
// SaveData::CreateSection(_SaveDataHdr*)
u32 CreateSection__8SaveDataFP12_SaveDataHdr(SaveData *this,u64 param_2)
{
  char cVar1;
  int iVar2;
  u32 uVar3;
  long lVar4;
  u16 uVar5;
  u16 uVar6;
  int iVar7;
  iVar7 = (int)param_2;
  iVar2 = memcmp((void *)(iVar7 + 4),_1683,8);
  if ((iVar2 == 0) &&
     (lVar4 = CheckCRC__8SaveDataFPUcUi
                        (param_2,*(int *)(iVar7 + 0x18) + (uint)*(u16 *)(iVar7 + 0x16)),
     lVar4 != 0)) {
    iVar2 = iVar7 + 0x20;
    uVar6 = 0;
    uVar5 = 0;
    if (*(short *)(iVar7 + 0x1c) != 0) {
      do {
        lVar4 = GetSection__8SaveDataFPCUc(this,iVar2);
        if ((lVar4 != 0) &&
           (cVar1 = (**(code **)(*(int *)lVar4 + 0x14))(lVar4,*(u16 *)(iVar2 + 6)),
           cVar1 == '\0')) {
          return 0;
        }
        uVar6 = uVar6 + 1;
        uVar5 = *(u16 *)(iVar7 + 0x1c);
        iVar2 = *(int *)(iVar2 + 8) + iVar2 + (uint)*(u16 *)(iVar2 + 4);
      } while (uVar6 < uVar5);
    }
    iVar2 = iVar7 + 0x20;
    uVar6 = 0;
    if (uVar5 != 0) {
      do {
        lVar4 = GetSection__8SaveDataFPCUc(this,iVar2);
        if (lVar4 != 0) {
          (**(code **)(*(int *)lVar4 + 0x10))(lVar4,iVar2,iVar2 + 0x10);
        }
        uVar6 = uVar6 + 1;
        iVar2 = *(int *)(iVar2 + 8) + iVar2 + (uint)*(u16 *)(iVar2 + 4);
      } while (uVar6 < *(u16 *)(iVar7 + 0x1c));
    }
    uVar3 = 1;
  }
  else {
    uVar3 = 0;
  }
  return uVar3;
}

// JP: 0x00328540  GetHeap__8SaveDataCFv  size 0x38
// SaveData::GetHeap() const
u32 GetHeap__8SaveDataCFv(SaveData *this)
{
  int iVar1;
  iVar1 = this->heap;
  SetCRC__8SaveDataFPUcUi(iVar1,*(int *)(iVar1 + 0x18) + (uint)*(u16 *)(iVar1 + 0x16));
  return this->heap;
}

// JP: 0x00328580  Polling__8SaveDataFv  size 0x1e0
// SaveData::Polling()
u32 Polling__8SaveDataFv(SaveData *this)
{
  long lVar1;
  int iVar2;
  iVar2 = (int)this;
  if ((*(int **)(iVar2 + 0x20) != (int *)0x0) && (*(int *)(iVar2 + 0x24) != 3)) {
    lVar1 = (**(code **)(**(int **)(iVar2 + 0x20) + 0xc))();
    if (lVar1 != -1) {
      if (lVar1 != -2) {
        if (lVar1 != 1) {
          return 0;
        }
        if (*(char *)(iVar2 + 0x28) == '\x02') {
          Release__8SaveDataFv(this);
          return 1;
        }
        if (*(char *)(iVar2 + 0x28) != '\x04') {
          *(u32 *)(iVar2 + 0x24) = 2;
        }
      }
      switch(*(u8 *)(iVar2 + 0x29)) {
      default:
        lVar1 = 1;
        break;
      case 2:
        lVar1 = (**(code **)(**(int **)(iVar2 + 0x20) + 0x14))();
        break;
      case 3:
        lVar1 = (**(code **)(**(int **)(iVar2 + 0x20) + 0x18))();
        break;
      case 4:
        lVar1 = (**(code **)(**(int **)(iVar2 + 0x20) + 0x1c))();
        break;
      case 5:
        lVar1 = (**(code **)(**(int **)(iVar2 + 0x20) + 0x20))
                          (*(int **)(iVar2 + 0x20),*(u8 *)(iVar2 + 0x2b));
        break;
      case 6:
        lVar1 = (**(code **)(**(int **)(iVar2 + 0x20) + 0x24))
                          (*(int **)(iVar2 + 0x20),*(u8 *)(iVar2 + 0x2b));
        break;
      case 7:
        lVar1 = (**(code **)(**(int **)(iVar2 + 0x20) + 0x28))
                          (*(int **)(iVar2 + 0x20),*(u8 *)(iVar2 + 0x2b));
        break;
      case 8:
        lVar1 = (**(code **)(**(int **)(iVar2 + 0x20) + 0x2c))();
      }
      *(u8 *)(iVar2 + 0x28) = *(u8 *)(iVar2 + 0x29);
      *(u8 *)(iVar2 + 0x29) = 4;
      if (lVar1 == 1) {
        return 0;
      }
    }
    *(u32 *)(iVar2 + 0x24) = 3;
  }
  return 0;
}

// JP: 0x00328760  Open__8SaveDataFs  size 0x11c
// SaveData::Open(short)
u32 Open__8SaveDataFs(SaveData *this,short param_2)
{
  u32 uVar1;
  long lVar2;
  int iVar3;
  iVar3 = (int)this;
  if (*(int *)(iVar3 + 0x24) == 0) {
    if (param_2 == 2) {
      lVar2 = __nw__FUi(0x3f8);
      uVar1 = 0;
      if (lVar2 != 0) {
        uVar1 = __ct__13SaveDeviceHDDFv(lVar2);
      }
      *(u32 *)(iVar3 + 0x20) = uVar1;
    }
    else {
      if ((param_2 != 1) && (param_2 != 0)) {
        return 0;
      }
      lVar2 = __nw__FUi(0x3fc);
      uVar1 = 0;
      if (lVar2 != 0) {
        uVar1 = __ct__12SaveDeviceMCFv(lVar2);
      }
      *(u32 *)(iVar3 + 0x20) = uVar1;
    }
    lVar2 = (**(code **)(**(int **)(iVar3 + 0x20) + 0x10))(*(int **)(iVar3 + 0x20),param_2);
    if (lVar2 == -1) {
      Release__8SaveDataFv(this);
      uVar1 = 0;
    }
    else {
      *(u32 *)(iVar3 + 0x24) = 1;
      *(u8 *)(iVar3 + 0x29) = 1;
      *(u8 *)(iVar3 + 0x2a) = 1;
      Entry__7CPollerFP7CPolObjib(app__4CApp + 0x48,this,0x80,0);
      uVar1 = 1;
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

// JP: 0x00328880  Close__8SaveDataFv  size 0x80
// SaveData::Close()
u32 Close__8SaveDataFv(SaveData *this)
{
  int iVar1;
  u32 uVar2;
  iVar1 = this->state;
  if ((iVar1 == 0) || (iVar1 == 1)) {
    uVar2 = 0;
  }
  else {
    if (iVar1 == 3) {
      (**(code **)(*this->device + 0x14))();
      this->last_op = 2;
    }
    uVar2 = 1;
    this->state = 1;
    this->pending_op = 2;
    this->op2a = 2;
  }
  return uVar2;
}

// JP: 0x00328900  CreateSystem__8SaveDataFv  size 0x38
// SaveData::CreateSystem()
bool CreateSystem__8SaveDataFv(SaveData *this)
{
  bool bVar1;
  bVar1 = this->state == 2;
  if (bVar1) {
    this->state = 1;
    this->pending_op = 3;
    this->op2a = 3;
  }
  return bVar1;
}

// JP: 0x00328940  Save__8SaveDataFUc  size 0x90
// SaveData::Save(unsigned char)
u32 Save__8SaveDataFUc(SaveData *this,u8 param_2)
{
  int *piVar1;
  u32 uVar2;
  if (this->state == 2) {
    for (piVar1 = this->sections; piVar1 != (int *)0x0; piVar1 = (int *)piVar1[1]) {
      (**(code **)(*piVar1 + 0x18))(piVar1);
    }
    uVar2 = 1;
    this->state = 1;
    this->pending_op = 5;
    this->op2a = 5;
    this->slot = param_2;
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

// JP: 0x003289d0  Load__8SaveDataFUc  size 0x38
// SaveData::Load(unsigned char)
bool Load__8SaveDataFUc(SaveData *this,u8 param_2)
{
  bool bVar1;
  bVar1 = this->state == 2;
  if (bVar1) {
    this->state = 1;
    this->pending_op = 6;
    this->op2a = 6;
    this->slot = param_2;
  }
  return bVar1;
}

// JP: 0x00328a10  Format__8SaveDataFv  size 0x38
// SaveData::Format()
bool Format__8SaveDataFv(SaveData *this)
{
  bool bVar1;
  bVar1 = this->state == 2;
  if (bVar1) {
    this->state = 1;
    this->pending_op = 8;
    this->op2a = 8;
  }
  return bVar1;
}
