/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x00288ac0  __ct__16MenuWindowObjectFv  size 0x3c
// MenuWindowObject::MenuWindowObject()
int __ct__16MenuWindowObjectFv(MenuWindowObject *this)
{
  __ct__7MenuObjFv(this);
  this->f_8 /*u8 **/ = __vt__16MenuWindowObject;
  return this;
}

// JP: 0x00288b00  __dt__16MenuWindowObjectFv  size 0x74
// MenuWindowObject::~MenuWindowObject()
int __dt__16MenuWindowObjectFv(MenuWindowObject *this,short param_2)
{
  if (this != 0) {
    this->f_8 /*u8 **/ = __vt__16MenuWindowObject;
    __dt__7MenuObjFv(this,0);
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}

// JP: 0x00288b80  SetForm__16MenuWindowObjectFffff  size 0x60
// MenuWindowObject::SetForm(float, float, float, float)
void SetForm__16MenuWindowObjectFffff(MenuWindowObject *this)
{
  ulong uVar1;
  uVar1 = (ulong)this->f_11 /*u8 **/ & 0xfffffffffffffff7 | 8;
  this->f_11 /*char **/ = (char)uVar1;
  this->f_10 /*u8 **/ =
       this->f_10 /*u8 **/ & 0xf7 | (u8)((uint)((uVar1 << 0x3c) >> 0x3f) << 3);
  return;
}

// JP: 0x00288be0  SetColor__16MenuWindowObjectFUcUcUc  size 0x10
// MenuWindowObject::SetColor(unsigned char, unsigned char, unsigned char)
void SetColor__16MenuWindowObjectFUcUcUc(void)
{
  return;
}
