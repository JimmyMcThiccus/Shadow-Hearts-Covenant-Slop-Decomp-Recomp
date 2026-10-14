/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x00291670  __ct__18MenuFieldStationedFv  size 0x3c
// MenuFieldStationed::MenuFieldStationed()
int __ct__18MenuFieldStationedFv(MenuFieldStationed *this)
{
  __ct__13MenuFieldDataFv(this);
  this->f_8 /*u8 **/ = __vt__18MenuFieldStationed;
  return this;
}

// JP: 0x002916b0  __dt__18MenuFieldStationedFv  size 0x7c
// MenuFieldStationed::~MenuFieldStationed()
int __dt__18MenuFieldStationedFv(MenuFieldStationed *this,short param_2)
{
  if (this != 0) {
    this->f_8 /*u8 **/ = __vt__18MenuFieldStationed;
    ClearFont__4FontFi(1);
    __dt__13MenuFieldDataFv(this,0);
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}

// JP: 0x00291730  GetReady__18MenuFieldStationedFv  size 0x48
// MenuFieldStationed::GetReady()
u32 GetReady__18MenuFieldStationedFv(MenuFieldStationed *this)
{
  CreateFont__4FontFiPUc(1,*(u32 *)(this->f_54 /*int **/ + 0x10));
  return 1;
}
