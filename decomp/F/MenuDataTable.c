/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x00283760  Convert__13MenuDataTableFPUci  size 0x11c
// MenuDataTable::Convert(unsigned char*, int)
u32 Convert__13MenuDataTableFPUci(MenuDataTable *this,int param_2)
{
  int *piVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  iVar2 = this;
  while( true ) {
    if (*(char *)(iVar2 + 2) != '\0') {
      if (param_2 == 1) {
        this = iVar2;
      }
      iVar4 = iVar2 + 0x10;
      for (uVar5 = 0; uVar5 < *(uint *)(iVar2 + 8); uVar5 = uVar5 + 1 & 0xffff) {
        for (uVar3 = 0; uVar3 < *(u8 *)(iVar2 + 2); uVar3 = uVar3 + 1 & 0xffff) {
          piVar1 = (int *)(iVar4 + uVar3 * 4);
          *piVar1 = *piVar1 + this;
        }
        iVar4 = iVar4 + (uint)*(u16 *)(iVar2 + 6);
      }
      *(u8 *)(iVar2 + 2) = 0;
    }
    if (*(int *)(iVar2 + 0xc) == 0) break;
    iVar2 = iVar2 + *(int *)(iVar2 + 0xc);
  }
  return 1;
}

// JP: 0x00283880  __ct__13MenuDataTableFv  size 0x38
// MenuDataTable::MenuDataTable()
u32 * __ct__13MenuDataTableFv(MenuDataTable *this)
{
  *this = 0;
  this[1] = 0;
  this->f_2 /*u8 **/ = 0;
  *(u8 *)((int)this + 9) = 0;
  return this;
}

// JP: 0x002838c0  __dt__13MenuDataTableFv  size 0x5c
// MenuDataTable::~MenuDataTable()
int __dt__13MenuDataTableFv(MenuDataTable *this,short param_2)
{
  if ((this != 0) && (Release__13MenuDataTableFv(this), 0 < param_2)) {
    __dl__FPv(this);
  }
  return this;
}

// JP: 0x00283920  Order__13MenuDataTableFPCc  size 0x78
// MenuDataTable::Order(const char*)
void Order__13MenuDataTableFPCc(MenuDataTable *this,u32 param_2)
{
  char acStack_120 [256];
  int iStack_20;
  u32 uStack_10;
  this->loading = 1;
  iStack_20 = this;
  uStack_10 = param_2;
  sprintf(acStack_120,(char *)&_1566,pDataPath__7SysTool,param_2);
  ReadOrder__11DvdromOrderFPCcPFiP9BufMemoryiPcPv_iiPvi
            (Dvdromour__11DvdromOrder,acStack_120,0x2839a0,0,iStack_20,0);
  return;
}

// JP: 0x002839a0  ReadDataFunc__13MenuDataTableFiP9BufMemoryiPcPv  size 0x44
// MenuDataTable::ReadDataFunc(int, BufMemory*, int, char*, void*)
void ReadDataFunc__13MenuDataTableFiP9BufMemoryiPcPv
               (u64 param_1,int this,u64 param_3,u64 param_4,
               u32 param_5)
{
  Create__13MenuDataTableFPUcP9BufMemory(param_5,this->heap,this);
  return;
}

// JP: 0x002839f0  Find__13MenuDataTableFs  size 0x80
// MenuDataTable::Find(short)
short * Find__13MenuDataTableFs(MenuDataTable *this,short param_2)
{
  short *psVar1;
  psVar1 = (short *)*this;
  while( true ) {
    if (*psVar1 == param_2) {
      return psVar1;
    }
    if (*(int *)(psVar1 + 6) == 0) break;
    psVar1 = (short *)((int)psVar1 + *(int *)(psVar1 + 6));
  }
  return (short *)0x0;
}

// JP: 0x00283a70  Create__13MenuDataTableFPUcP9BufMemory  size 0x80
// MenuDataTable::Create(unsigned char*, BufMemory*)
bool Create__13MenuDataTableFPUcP9BufMemory
               (MenuDataTable *this,u32 param_2,u32 param_3)
{
  bool bVar1;
  this->f_2 /*u8 **/ = 0;
  bVar1 = *(char *)((int)this + 9) != '\0';
  if (bVar1) {
    *(u8 *)((int)this + 9) = 0;
  }
  else {
    Convert__13MenuDataTableFPUci(param_2,1);
    *this = param_2;
    this[1] = param_3;
  }
  return bVar1;
}

// JP: 0x00283af0  Release__13MenuDataTableFv  size 0x78
// MenuDataTable::Release()
void Release__13MenuDataTableFv(MenuDataTable *this)
{
  if (this->f_2 /*char **/ == '\0') {
    if (this[1] != 0) {
      __dt__9BufMemoryFv(this[1],1);
      this[1] = 0;
    }
    *this = 0;
  }
  else {
    *(u8 *)((int)this + 9) = 1;
  }
  return;
}
