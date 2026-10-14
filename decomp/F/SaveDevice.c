/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x0032a240  cbReadFile__10SaveDeviceFiP9BufMemoryiPcPv  size 0x3c
// SaveDevice::cbReadFile(int, BufMemory*, int, char*, void*)
u64 cbReadFile__10SaveDeviceFiP9BufMemoryiPcPv(SaveDevice *this)
{
  u64 uVar1;
  u64 in_t0;
  if (this == 0) {
    uVar1 = CreateIcon__10SaveDeviceFP9BufMemoryi(in_t0);
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}

// JP: 0x0032a280  __ct__10SaveDeviceFv  size 0x68
// SaveDevice::SaveDevice()
u64 __ct__10SaveDeviceFv(SaveDevice *this)
{
  u32 *puVar1;
  puVar1 = (u32 *)this;
  *puVar1 = __vt__10SaveDevice;
  *(u8 *)(puVar1 + 1) = 0;
  *(u8 *)((int)puVar1 + 6) = 0;
  *(u8 *)((int)puVar1 + 7) = 0;
  *(u16 *)(puVar1 + 2) = 0;
  *(u16 *)((int)puVar1 + 10) = 0;
  puVar1[3] = 0;
  puVar1[4] = 0;
  puVar1[5] = 0;
  puVar1[6] = 0;
  __ct__10SystemFileFv(puVar1 + 7);
  puVar1[0xfb] = 0;
  puVar1[0xfc] = 0;
  *(u8 *)((int)puVar1 + 5) = 0;
  return this;
}

// JP: 0x0032a2f0  __dt__10SaveDeviceFv  size 0x68
// SaveDevice::~SaveDevice()
long __dt__10SaveDeviceFv(SaveDevice *this,short param_2)
{
  if (this != 0) {
    *(u32 *)this = __vt__10SaveDevice;
    DeleteHeap__10SaveDeviceFv();
    __dt__10SystemFileFv((u32 *)this + 7,0xffffffffffffffff);
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}

// JP: 0x0032a360  LoadIcon__10SaveDeviceFv  size 0x74
// SaveDevice::LoadIcon()
void LoadIcon__10SaveDeviceFv(SaveDevice *this)
{
  char acStack_40 [64];
  sprintf(acStack_40,_1566,pDataPath__7SysTool,0x40a940,0x40a938);
  *(u8 *)((int)this + 5) = *(u8 *)((int)this + 5) & 0xfb | 4;
  ReadOrder__11DvdromOrderFPCcPFiP9BufMemoryiPcPv_iiPvi
            (Dvdromour__11DvdromOrder,acStack_40,0x32a240,0,this,0);
  return;
}

// JP: 0x0032a3e0  CreateIcon__10SaveDeviceFP9BufMemoryi  size 0x128
// SaveDevice::CreateIcon(BufMemory*, int)
u64 CreateIcon__10SaveDeviceFP9BufMemoryi(SaveDevice *this,int param_2)
{
  int iVar1;
  iVar1 = *(int *)(param_2 + 4);
  this->icon_buf = param_2;
  this->icon_data = iVar1;
  memset((void *)(this + 0x28),0,0x3c4);
  strcpy((char *)(this + 0x28),(char *)&_1578);
  strcpy((char *)(this + 0xe8),_1579);
  this->f_2e /*u16 **/ = 0x14;
  this->f_34 /*u32 **/ = 0x60;
  this->f_38 /*u32 **/ = 0x80;
  this->f_4c /*u32 **/ = 0x80;
  this->f_60 /*u32 **/ = 0x80;
  this->f_68 /*u32 **/ = 0x80;
  this->f_6c /*u32 **/ = 0x80;
  this->f_70 /*u32 **/ = 0x80;
  memcpy((void *)(this + 0x78),(void *)(iVar1 + 0x10),0x30);
  memcpy((void *)(this + 0xa8),(void *)(iVar1 + 0x40),0x30);
  memcpy((void *)(this + 0xd8),(void *)(iVar1 + 0x70),0x10);
  strcpy((char *)(this + 300),sm_iconFile__10SaveDevice);
  strcpy((char *)(this + 0x16c),sm_iconFile__10SaveDevice);
  strcpy((char *)(this + 0x1ac),sm_iconFile__10SaveDevice);
  this->dflags = this->dflags & 0xfb;
  this->dflags = this->dflags & 0xf7 | 8;
  return 0;
}

// JP: 0x0032a510  NewHeap__10SaveDeviceFi  size 0x54
// SaveDevice::NewHeap(int)
void NewHeap__10SaveDeviceFi(SaveDevice *this,u64 param_2)
{
  u32 uVar1;
  uVar1 = __nwa__FUi(param_2);
  this->io_ptr = uVar1;
  this->io_len = (int)param_2;
  this->dflags = this->dflags & 0xef | 0x10;
  return;
}

// JP: 0x0032a570  DeleteHeap__10SaveDeviceFv  size 0x6c
// SaveDevice::DeleteHeap()
void DeleteHeap__10SaveDeviceFv(SaveDevice *this)
{
  if (((long)((ulong)this->dflags << 0x3b) < 0) && (this->io_ptr != 0)) {
    __dla__FPv();
  }
  this->dflags = this->dflags & 0xef;
  this->io_ptr = 0;
  this->io_len = 0;
  return;
}

// JP: 0x0032a5e0  Save__10SaveDeviceFUc  size 0xb0
// SaveDevice::Save(unsigned char)
u64 Save__10SaveDeviceFUc(SaveDevice *this,u8 param_2)
{
  int iVar1;
  u64 uVar2;
  long lVar3;
  int *piVar4;
  char acStack_20 [32];
  sprintf(acStack_20,sm_slotName__10SaveDevice,(ulong)param_2);
  iVar1 = DAT_00421e8c;
  uVar2 = GetHeap__8SaveDataCFv(0x421e70);
  piVar4 = (int *)this;
  lVar3 = (**(code **)(*piVar4 + 0x34))
                    (this,acStack_20,uVar2,
                     (uint)*(u16 *)(iVar1 + 0x16) + *(int *)(iVar1 + 0x18));
  uVar2 = 0xffffffffffffffff;
  if (lVar3 != -1) {
    uVar2 = 1;
    *(u8 *)(piVar4[7] + 0xc) = param_2;
    *(u8 *)((int)piVar4 + 6) = 5;
    *(u8 *)((int)piVar4 + 7) = 0;
  }
  return uVar2;
}

// JP: 0x0032a690  Load__10SaveDeviceFUc  size 0x70
// SaveDevice::Load(unsigned char)
u64 Load__10SaveDeviceFUc(SaveDevice *this,ulong param_2)
{
  long lVar1;
  u64 uVar2;
  int *piVar3;
  char acStack_20 [32];
  sprintf(acStack_20,sm_slotName__10SaveDevice,param_2 & 0xff);
  piVar3 = (int *)this;
  lVar1 = (**(code **)(*piVar3 + 0x30))(this,acStack_20);
  uVar2 = 0xffffffffffffffff;
  if (lVar1 != -1) {
    *(u8 *)((int)piVar3 + 6) = 6;
    uVar2 = 1;
    *(u8 *)((int)piVar3 + 7) = 0;
  }
  return uVar2;
}
