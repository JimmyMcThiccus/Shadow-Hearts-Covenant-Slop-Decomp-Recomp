/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x003c9500  __ct__14CFieldSaveDataFv  size 0x9c
// CFieldSaveData::CFieldSaveData()
u32 * __ct__14CFieldSaveDataFv(CFieldSaveData *this)
{
  __ct__15SaveDataSectionFv(this);
  *this = __vt__14CFieldSaveData;
  this->f_3 /*u16 **/ = 0xa2;
  *(u16 *)((int)this + 0xe) = 0;
  this->f_3 /*u16 **/ = 0xa2;
  CreateSection__15SaveDataSectionFPCcUiUs(this,0x401820,(uint)this->f_3 /*u16 **/ << 4,0);
  InitializeData__14CFieldSaveDataFi(this,0);
  sys__14CFieldSaveData = this;
  return this;
}

// JP: 0x003c95a0  __dt__14CFieldSaveDataFv  size 0x74
// CFieldSaveData::~CFieldSaveData()
u32 * __dt__14CFieldSaveDataFv(CFieldSaveData *this,short param_2)
{
  if (this != (u32 *)0x0) {
    *this = __vt__14CFieldSaveData;
    __dt__15SaveDataSectionFv(this,0);
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}

// JP: 0x003c9620  Initialize__14CFieldSaveDataFv  size 0x54
// CFieldSaveData::Initialize()
void Initialize__14CFieldSaveDataFv(void)
{
  long lVar1;
  if ((sys__14CFieldSaveData == 0) && (lVar1 = __nw__FUi(0x10), lVar1 != 0)) {
    __ct__14CFieldSaveDataFv(lVar1);
  }
  return;
}

// JP: 0x003c9680  InitializeData__14CFieldSaveDataFi  size 0x40
// CFieldSaveData::InitializeData(int)
void InitializeData__14CFieldSaveDataFi(CFieldSaveData *this,int param_2)
{
  if (param_2 == 0) {
    (**(code **)(*this + 0xc))();
  }
  return;
}

// JP: 0x003c96c0  SetDefault__14CFieldSaveDataFv  size 0xd8
// CFieldSaveData::SetDefault()
void SetDefault__14CFieldSaveDataFv(CFieldSaveData *this)
{
  memset((void *)(this->hdr + 0x10),0,0xa20);
  this->used_units = 0;
  AddChunk__14CFieldSaveDataFPCcii(this,0x401828,8,0);
  AddChunk__14CFieldSaveDataFPCcii(this,0x401830,0x81,0);
  AddChunk__14CFieldSaveDataFPCcii(this,0x401838,0x10,0);
  AddChunk__14CFieldSaveDataFPCcii(this,0x401840,5,0);
  AddChunk__14CFieldSaveDataFPCcii(this,0x401848,4,0);
  return;
}

// JP: 0x003c97a0  SetSection__14CFieldSaveDataFP19_SaveDataSectionHdrPUc  size 0x10c
// CFieldSaveData::SetSection(_SaveDataSectionHdr*, unsigned char*)
void * SetSection__14CFieldSaveDataFP19_SaveDataSectionHdrPUc
                 (CFieldSaveData *this,void *param_2,void *param_3)
{
  void *pvVar1;
  uint uVar2;
  int iVar3;
  this->used_units = 0;
  memcpy(this->hdr,param_2,(ulong)*(u16 *)((int)param_2 + 4));
  pvVar1 = memcpy((void *)(this->hdr + 0x10),param_3,(long)*(int *)((int)param_2 + 8));
  iVar3 = this->hdr + 0x10;
  for (uVar2 = 0; uVar2 < *(uint *)((int)param_2 + 0xc); uVar2 = uVar2 + 1) {
    this->used_units = this->used_units + (u16)*(u8 *)(iVar3 + 2);
    iVar3 = iVar3 + (uint)*(u8 *)(iVar3 + 2) * 0x10;
  }
  return pvVar1;
}

// JP: 0x003c98b0  FindChunk__14CFieldSaveDataFPCc  size 0xb4
// CFieldSaveData::FindChunk(const char*)
void * FindChunk__14CFieldSaveDataFPCc(CFieldSaveData *this,void *param_2)
{
  int iVar1;
  uint uVar2;
  void *__s2;
  __s2 = (void *)(this->hdr + 0x10);
  uVar2 = 0;
  while( true ) {
    if (*(uint *)(this->hdr + 0xc) <= uVar2) {
      return (void *)0x0;
    }
    iVar1 = memcmp(param_2,__s2,2);
    if (iVar1 == 0) break;
    __s2 = (void *)((int)__s2 + (uint)*(u8 *)((int)__s2 + 2) * 0x10);
    uVar2 = uVar2 + 1;
  }
  return __s2;
}

// JP: 0x003c9970  AddChunk__14CFieldSaveDataFPCcii  size 0x118
// CFieldSaveData::AddChunk(const char*, int, int)
void * AddChunk__14CFieldSaveDataFPCcii(CFieldSaveData *this,void *param_2,int param_3,u8 param_4)
{
  void *__s;
  if ((int)(uint)this->capacity_units < (int)(param_3 + (uint)this->used_units)) {
    printf(_1426);
    __s = (void *)0x0;
  }
  else {
    __s = (void *)(this->hdr + 0x10 + (uint)this->used_units * 0x10);
    this->used_units = this->used_units + (short)param_3;
    memset(__s,0,(long)(param_3 << 4));
    memcpy(__s,param_2,2);
    *(char *)((int)__s + 2) = (char)param_3;
    *(u8 *)((int)__s + 3) = param_4;
    *(int *)(this->hdr + 0xc) = *(int *)(this->hdr + 0xc) + 1;
  }
  return __s;
}
