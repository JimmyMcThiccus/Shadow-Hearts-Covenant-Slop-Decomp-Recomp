/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x00275140  __ct__12MenuObjTableFv  size 0x30
// MenuObjTable::MenuObjTable()
u32 * __ct__12MenuObjTableFv(MenuObjTable *this)
{
  *this = __vt__12MenuObjTable;
  this[1] = 0;
  return this;
}

// JP: 0x00275170  __dt__12MenuObjTableFv  size 0x64
// MenuObjTable::~MenuObjTable()
u32 * __dt__12MenuObjTableFv(MenuObjTable *this,short param_2)
{
  if ((this != (u32 *)0x0) && (*this = __vt__12MenuObjTable, 0 < param_2)) {
    __dl__FPv(this);
  }
  return this;
}

// JP: 0x002751e0  AddPriority__12MenuObjTableFP7MenuObj  size 0x160
// MenuObjTable::AddPriority(MenuObj*)
void AddPriority__12MenuObjTableFP7MenuObj(int param_1,int this)
{
  int iVar1;
  int iVar2;
  int iVar3;
  this->f_c /*u32 **/ = 0;
  this->f_12 /*u8 **/ = this->f_12 /*u8 **/ & 0xfb | 4;
  this->f_10 /*u8 **/ = this->f_10 /*u8 **/ | 0x3f;
  this->f_11 /*u8 **/ = this->f_11 /*u8 **/ | 0x3f;
  if (*(int *)(param_1 + 4) == 0) {
    *(int *)(param_1 + 4) = this;
  }
  else {
    iVar1 = *(int *)(param_1 + 4);
    iVar3 = 0;
    while (iVar2 = iVar1, iVar2 != 0) {
      if (this->f_14 /*short **/ < *(short *)(iVar2 + 0x14)) {
        if (iVar3 == 0) {
          *(int *)(param_1 + 4) = this;
        }
        else {
          *(int *)(iVar3 + 0xc) = this;
        }
        this->f_c /*int **/ = iVar2;
        break;
      }
      iVar3 = iVar2;
      iVar1 = *(int *)(iVar2 + 0xc);
    }
    if (iVar2 == 0) {
      *(int *)(iVar3 + 0xc) = this;
    }
  }
  return;
}

// JP: 0x00275340  RemoveObj__12MenuObjTableFP7MenuObj  size 0xf4
// MenuObjTable::RemoveObj(MenuObj*)
void RemoveObj__12MenuObjTableFP7MenuObj(int param_1,int this)
{
  int iVar1;
  if (*(int *)(param_1 + 4) == this) {
    *(u32 *)(param_1 + 4) = this->f_c /*u32 **/;
    iVar1 = this;
  }
  else {
    for (iVar1 = *(int *)(param_1 + 4); iVar1 != 0; iVar1 = *(int *)(iVar1 + 0xc)) {
      if (*(int *)(iVar1 + 0xc) == this) {
        *(u32 *)(iVar1 + 0xc) = this->f_c /*u32 **/;
        break;
      }
    }
  }
  if (iVar1 != 0) {
    this->f_c /*u32 **/ = 0;
    this->f_12 /*u8 **/ = this->f_12 /*u8 **/ & 0xfb;
  }
  return;
}

// JP: 0x00275440  FindObj__12MenuObjTableFs  size 0x7c
// MenuObjTable::FindObj(short)
int FindObj__12MenuObjTableFs(MenuObjTable *this,short param_2)
{
  int iVar1;
  for (iVar1 = this->head; (iVar1 != 0 && (param_2 != *(short *)(iVar1 + 0x16)));
      iVar1 = *(int *)(iVar1 + 0xc)) {
  }
  return iVar1;
}

// JP: 0x002754c0  ClearTable__12MenuObjTableFv  size 0x80
// MenuObjTable::ClearTable()
void ClearTable__12MenuObjTableFv(MenuObjTable *this)
{
  int iVar1;
  int iVar2;
  iVar2 = this->head;
  while (iVar2 != 0) {
    iVar1 = *(int *)(iVar2 + 0xc);
    *(u32 *)(iVar2 + 0xc) = 0;
    *(u8 *)(iVar2 + 0x12) = *(u8 *)(iVar2 + 0x12) & 0xfb;
    iVar2 = iVar1;
  }
  this->head = 0;
  return;
}

// JP: 0x00275540  TraceSetRendering__12MenuObjTableFUc  size 0x6c
// MenuObjTable::TraceSetRendering(unsigned char)
void TraceSetRendering__12MenuObjTableFUc(MenuObjTable *this,u8 param_2)
{
  int iVar1;
  for (iVar1 = this->head; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0xc)) {
    *(u8 *)(iVar1 + 0x12) = *(u8 *)(iVar1 + 0x12) & 0xfe | param_2 & 1;
  }
  return;
}

// JP: 0x002755b0  TracePolling__12MenuObjTableFv  size 0x78
// MenuObjTable::TracePolling()
void TracePolling__12MenuObjTableFv(MenuObjTable *this)
{
  int iVar1;
  for (iVar1 = this->head; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0xc)) {
    if ((long)((ulong)*(u8 *)(iVar1 + 0x12) << 0x3e) < 0) {
      VCALL(iVar1, 0x10 /*Polling*/)();
    }
  }
  return;
}

// JP: 0x00275630  TraceUpdate__12MenuObjTableFiiUs  size 0xb4
// MenuObjTable::TraceUpdate(int, int, unsigned short)
void TraceUpdate__12MenuObjTableFiiUs
               (MenuObjTable *this,u32 param_2,u32 param_3,u16 param_4)
{
  int iVar1;
  for (iVar1 = this->head; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0xc)) {
    if (((*(u8 *)(iVar1 + 0x12) & 1) != 0) &&
       (*(char *)(iVar1 + (m_Env__8VIF1Prim & 1) + 0x10) != '\0')) {
      VCALL(iVar1, 0x14 /*Update*/)(iVar1,param_2,param_3,param_4);
    }
  }
  return;
}

// JP: 0x002756f0  TraceUpdate__12MenuObjTableFiiUsUc  size 0xd4
// MenuObjTable::TraceUpdate(int, int, unsigned short, unsigned char)
void TraceUpdate__12MenuObjTableFiiUsUc
               (MenuObjTable *this,u32 param_2,u32 param_3,u16 param_4,u8 param_5)
{
  int iVar1;
  for (iVar1 = this->head; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0xc)) {
    if (((*(u8 *)(iVar1 + 0x12) & 1) != 0) &&
       (*(char *)(iVar1 + (m_Env__8VIF1Prim & 1) + 0x10) != '\0')) {
      *(u8 *)(iVar1 + 0x10) = *(u8 *)(iVar1 + 0x10) | param_5;
      *(u8 *)(iVar1 + 0x11) = *(u8 *)(iVar1 + 0x11) | param_5;
      VCALL(iVar1, 0x14 /*Update*/)(iVar1,param_2,param_3,param_4);
    }
  }
  return;
}

// JP: 0x002757d0  TraceAddUpdate__12MenuObjTableFUc  size 0x6c
// MenuObjTable::TraceAddUpdate(unsigned char)
void TraceAddUpdate__12MenuObjTableFUc(MenuObjTable *this,u8 param_2)
{
  int iVar1;
  for (iVar1 = this->head; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0xc)) {
    *(u8 *)(iVar1 + 0x10) = *(u8 *)(iVar1 + 0x10) | param_2;
    *(u8 *)(iVar1 + 0x11) = *(u8 *)(iVar1 + 0x11) | param_2;
  }
  return;
}

// JP: 0x00275840  TraceConnect__12MenuObjTableFP4_QWD  size 0x84
// MenuObjTable::TraceConnect(_QWD*)
u32 TraceConnect__12MenuObjTableFP4_QWD(MenuObjTable *this,u32 param_2)
{
  int iVar1;
  u32 uStack_10;
  uStack_10 = param_2;
  for (iVar1 = this->head; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0xc)) {
    if ((*(u8 *)(iVar1 + 0x12) & 1) != 0) {
      uStack_10 = VCALL(iVar1, 0x18 /*Connect*/)(iVar1,uStack_10);
    }
  }
  return uStack_10;
}
