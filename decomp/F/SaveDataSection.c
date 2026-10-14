/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x00327ef0  __ct__15SaveDataSectionFv  size 0x1c
// SaveDataSection::SaveDataSection()
u64 __ct__15SaveDataSectionFv(SaveDataSection *this)
{
  u32 *puVar1;
  puVar1 = (u32 *)this;
  *puVar1 = __vt__15SaveDataSection;
  puVar1[1] = 0;
  puVar1[2] = 0;
  return this;
}

// JP: 0x00327f10  __dt__15SaveDataSectionFv  size 0x60
// SaveDataSection::~SaveDataSection()
long __dt__15SaveDataSectionFv(SaveDataSection *this,short param_2)
{
  if (this != 0) {
    *(u32 *)this = __vt__15SaveDataSection;
    __dla__FPv(((u32 *)this)[2]);
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}

// JP: 0x00327f70  CreateSection__15SaveDataSectionFPCcUiUs  size 0x90
// SaveDataSection::CreateSection(const char*, unsigned int, unsigned short)
void * CreateSection__15SaveDataSectionFPCcUiUs
                 (SaveDataSection *this,void *param_2,u32 param_3,u16 param_4)
{
  void *pvVar1;
  int iVar2;
  OrderSection__8SaveDataFP15SaveDataSectionUi(0x421e70,this);
  iVar2 = (int)this;
  memset(*(void **)(iVar2 + 8),0,0x10);
  pvVar1 = memcpy(*(void **)(iVar2 + 8),param_2,4);
  *(u16 *)(*(int *)(iVar2 + 8) + 4) = 0x10;
  *(u16 *)(*(int *)(iVar2 + 8) + 6) = param_4;
  *(u32 *)(*(int *)(iVar2 + 8) + 8) = param_3;
  return pvVar1;
}

// JP: 0x00328000  SetDefault__15SaveDataSectionFv  size 0x18
// SaveDataSection::SetDefault()
void * SetDefault__15SaveDataSectionFv(SaveDataSection *this)
{
  void *pvVar1;
  pvVar1 = memset((void *)(this->hdr + 0x10),0,(long)*(int *)(this->hdr + 8)
                 );
  return pvVar1;
}

// JP: 0x00328020  SetSection__15SaveDataSectionFP19_SaveDataSectionHdrPUc  size 0x74
// SaveDataSection::SetSection(_SaveDataSectionHdr*, unsigned char*)
void * SetSection__15SaveDataSectionFP19_SaveDataSectionHdrPUc
                 (int *param_1,int this,void *param_3)
{
  int iVar1;
  void *pvVar2;
  ulong __n;
  iVar1 = this->hdr;
  __n = (ulong)*(int *)(param_1[2] + 8);
  if ((ulong)(long)iVar1 < __n) {
    (**(code **)(*param_1 + 0xc))();
    __n = (long)iVar1;
  }
  pvVar2 = memcpy((void *)(param_1[2] + 0x10),param_3,__n);
  return pvVar2;
}

// JP: 0x003280a0  FlushData__15SaveDataSectionFv  size 0x8
// SaveDataSection::FlushData()
void FlushData__15SaveDataSectionFv(void)
{
  return;
}

// JP: 0x003280b0  CheckVersion__15SaveDataSectionFUs  size 0x8
// SaveDataSection::CheckVersion(unsigned short)
u32 CheckVersion__15SaveDataSectionFUs(void)
{
  return 1;
}

// JP: 0x0037da00  GetSection__15SaveDataSectionFv  size 0xc
// SaveDataSection::GetSection()
int GetSection__15SaveDataSectionFv(SaveDataSection *this)
{
  return this->hdr + 0x10;
}
