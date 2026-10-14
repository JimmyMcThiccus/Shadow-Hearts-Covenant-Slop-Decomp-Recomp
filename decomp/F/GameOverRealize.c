/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x003ad1d0  __dt__15GameOverRealizeFv  size 0xd4
// GameOverRealize::~GameOverRealize()
int __dt__15GameOverRealizeFv(GameOverRealize *this,short param_2)
{
  if (this != 0) {
    this->f_8 /*u8 **/ = __vt__15GameOverRealize;
    __dt__10MenuSpriteFv(this + 0x130,0xffffffffffffffff);
    __dt__11SendOnLocalFv(this + 0x100,0xffffffffffffffff);
    __dt__11MenuTextureFv(this + 0xc0,0xffffffffffffffff);
    __dt__10MenuWindowFv(this + 0xc,0xffffffffffffffff);
    if (this != 0) {
      this->f_8 /*u8 **/ = __vt__17DelayDeleteObject;
    }
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}
