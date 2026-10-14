/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x002913b0  __ct__13MenuFieldDataFv  size 0x44
// MenuFieldData::MenuFieldData()
int __ct__13MenuFieldDataFv(MenuFieldData *this)
{
  __ct__9MenuSceneFv(this);
  this->f_8 /*u8 **/ = __vt__13MenuFieldData;
  this->f_58 /*u32 **/ = 0;
  return this;
}

// JP: 0x00291400  __dt__13MenuFieldDataFv  size 0x74
// MenuFieldData::~MenuFieldData()
int __dt__13MenuFieldDataFv(MenuFieldData *this,short param_2)
{
  if (this != 0) {
    this->f_8 /*u8 **/ = __vt__13MenuFieldData;
    __dt__9MenuSceneFv(this,0);
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}

// JP: 0x00291480  GetReady__13MenuFieldDataFv  size 0x80
// MenuFieldData::GetReady()
u32 GetReady__13MenuFieldDataFv(MenuFieldData *this)
{
  uint uVar1;
  for (uVar1 = 4; (int)uVar1 < 0xb; uVar1 = uVar1 + 1) {
    Convert__13MenuDataTableFPUci
              (*(u32 *)((uVar1 & 0xffff) * 0xc + this->f_54 /*int **/ + 0x10),0);
  }
  return 1;
}

// JP: 0x00291500  GetRealHeap__13MenuFieldDataFP9BufMemoryi  size 0xf0
// MenuFieldData::GetRealHeap(BufMemory*, int)
u32 GetRealHeap__13MenuFieldDataFP9BufMemoryi(MenuFieldData *this,int param_2,int param_3)
{
  long lVar1;
  if (sys__9FldMemory != 0) {
    lVar1 = FldAlloc__9FldMemoryFiUiUi(sys__9FldMemory,0,param_3,0x10);
    this->f_58 /*int **/ = (int)lVar1;
    if (lVar1 != 0) {
      memcpy(this->f_58 /*void **/,*(void **)(param_2 + 4),(long)param_3);
      this->f_23 /*u8 **/ = this->f_23 /*u8 **/ & 0x3f | 0x40;
      goto LAB_002915d0;
    }
  }
  this->f_58 /*u32 **/ = *(u32 *)(param_2 + 4);
  this->f_23 /*u8 **/ = this->f_23 /*u8 **/ & 0x3f;
LAB_002915d0:
  return this->f_58 /*u32 **/;
}

// JP: 0x002915f0  Release__13MenuFieldDataFv  size 0x74
// MenuFieldData::Release()
void Release__13MenuFieldDataFv(MenuFieldData *this)
{
  if (this->f_23 /*u8 **/ >> 6 != 0) {
    Free__9FldMemoryFPUc(sys__9FldMemory,this->f_58 /*u32 **/);
    this->f_23 /*u8 **/ = this->f_23 /*u8 **/ & 0x3f;
  }
  Release__9MenuSceneFv(this);
  return;
}
