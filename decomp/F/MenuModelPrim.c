/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x00291a90  __ct__13MenuModelPrimFv  size 0x44
// MenuModelPrim::MenuModelPrim()
int __ct__13MenuModelPrimFv(MenuModelPrim *this)
{
  __ct__8VIF1PrimFv(this);
  this->f_10 /*u8 **/ = __vt__13MenuModelPrim;
  this->f_14 /*u32 **/ = 0;
  return this;
}

// JP: 0x00291ae0  __dt__13MenuModelPrimFv  size 0x74
// MenuModelPrim::~MenuModelPrim()
int __dt__13MenuModelPrimFv(MenuModelPrim *this,short param_2)
{
  if (this != 0) {
    this->f_10 /*u8 **/ = __vt__13MenuModelPrim;
    __dt__8VIF1PrimFv(this,0);
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}

// JP: 0x00291b60  getPacket__13MenuModelPrimFv  size 0x3c
// MenuModelPrim::getPacket()
void getPacket__13MenuModelPrimFv(MenuModelPrim *this)
{
  GetPacket__9MenuModelFUc
            (this->f_14 /*u32 **/,((ulong)this->f_c /*u8 **/ & 7) >> 1);
  return;
}
