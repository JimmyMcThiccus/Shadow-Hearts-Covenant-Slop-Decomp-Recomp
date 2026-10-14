/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x003ad0f0  __dt__14GameOverSelectFv  size 0xdc
// GameOverSelect::~GameOverSelect()
int __dt__14GameOverSelectFv(GameOverSelect *this,short param_2)
{
  if (this != 0) {
    this->f_8 /*u8 **/ = __vt__14GameOverSelect;
    __destroy_arr(this + 0x1fc,0x27c030,0x80,3);
    __dt__8FontDrawFv(this + 0x1bc,0xffffffffffffffff);
    __dt__6CursorFv(this + 0xc0,0xffffffffffffffff);
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
