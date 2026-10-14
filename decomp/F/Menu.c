/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x00264de0  __ct__4MenuFv  size 0x100
// Menu::Menu()
int __ct__4MenuFv(Menu *this)
{
  __ct__7CPolObjFv(this);
  this->f_18 /*u32 **/ = 0;
  this->f_1c /*u32 **/ = 0;
  this->vptr_dd = __vt__17DelayDeleteObject;
  this->f_14 /*u8 **/ = __vt__4Menu;
  this->vptr_dd = 0x404f50;
  this->f_24 /*u32 **/ = 0;
  __ct__13MenuDataTableFv(this + 0x28);
  this->active = 0;
  this->scenes = 0;
  this->m3c = 0;
  this->f_3d /*u8 **/ = 0;
  this->m3e = 0;
  this->f_40 /*u16 **/ = 0;
  this->f_42 /*u16 **/ = 0;
  this->f_44 /*u16 **/ = 0;
  this->f_46 /*u16 **/ = 0;
  this->keys = 0;
  this->f_4a /*u16 **/ = 0;
  this->f_4c /*u8 **/ = 0;
  this->f_4d /*u8 **/ = 0;
  this->f_4e /*u8 **/ = 0;
  this->f_4f /*u8 **/ = 0;
  return this;
}

// JP: 0x00264ee0  __dt__4MenuFv  size 0xbc
// Menu::~Menu()
int __dt__4MenuFv(Menu *this,short param_2)
{
  if (this != 0) {
    this->f_14 /*u8 **/ = __vt__4Menu;
    this->vptr_dd = 0x404f50;
    __dt__13MenuDataTableFv(this + 0x28,0xffffffffffffffff);
    if (this != -0x18) {
      this->vptr_dd = __vt__17DelayDeleteObject;
    }
    __dt__7CPolObjFv(this,0);
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}

// JP: 0x00264fa0  Run__4MenuFv  size 0x7c
// Menu::Run()
void Run__4MenuFv(Menu *this)
{
  (**(code **)(this->f_14 /*int **/ + 0x2c))();
  if ((this->active != 0) &&
     ((long)((ulong)this->active->sflags << 0x3b) < 0)) {
    VCALL(this->active, 0x1c /*Destroy*/)();
  }
  return;
}

// JP: 0x00265020  Shutdown__4MenuFv  size 0x78
// Menu::Shutdown()
void Shutdown__4MenuFv(Menu *this)
{
  int iVar1;
  for (iVar1 = this->scenes; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x14)) {
    if (this->active != iVar1) {
      VCALL(iVar1, 0x20 /*Clear*/)();
    }
  }
  return;
}

// JP: 0x002650a0  Restore__4MenuFv  size 0x78
// Menu::Restore()
void Restore__4MenuFv(Menu *this)
{
  int iVar1;
  for (iVar1 = this->scenes; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x14)) {
    if (this->active != iVar1) {
      VCALL(iVar1, 0x24 /*SetPosition*/)();
    }
  }
  return;
}

// JP: 0x00265120  DestroyList__4MenuFv  size 0x98
// Menu::DestroyList()
void DestroyList__4MenuFv(Menu *this)
{
  int iVar1;
  int iVar2;
  iVar1 = this->scenes;
  while (iVar2 = iVar1, iVar2 != 0) {
    iVar1 = *(int *)(iVar2 + 0x14);
    if (iVar2 != 0) {
      VCALL(iVar2, 0x8 /*dtor*/)(iVar2,1);
    }
  }
  this->scenes = 0;
  return;
}

// JP: 0x002651c0  AddScene__4MenuFP9MenuScene  size 0x88
// Menu::AddScene(MenuScene*)
void AddScene__4MenuFP9MenuScene(int param_1,int this)
{
  if (-1 < (long)((ulong)this->f_23 /*u8 **/ << 0x3c)) {
    if (*(int *)(param_1 + 0x38) != 0) {
      this->f_14 /*u32 **/ = *(u32 *)(param_1 + 0x38);
    }
    *(int *)(param_1 + 0x38) = this;
    this->f_23 /*u8 **/ = this->f_23 /*u8 **/ & 0xf7 | 8;
  }
  return;
}

// JP: 0x00265250  RemoveScene__4MenuFP9MenuScene  size 0x10c
// Menu::RemoveScene(MenuScene*)
u32 RemoveScene__4MenuFP9MenuScene(Menu *this,MenuScene *menuScene)
{
  int iVar1;
  int iVar2;
  int iVar3;
  menuScene->sflags = menuScene->sflags & 0xf7;
  if (this->active == menuScene) {
    this->active = 0;
  }
  iVar1 = this->scenes;
  iVar3 = 0;
  while( true ) {
    iVar2 = iVar1;
    if (iVar2 == 0) {
      return 0;
    }
    if (iVar2 == menuScene) break;
    iVar1 = *(int *)(iVar2 + 0x14);
    iVar3 = iVar2;
  }
  if (iVar3 != 0) {
    *(u32 *)(iVar3 + 0x14) = *(u32 *)(iVar2 + 0x14);
    return *(u32 *)(iVar3 + 0x14);
  }
  this->scenes = *(u32 *)(menuScene + 0x14);
  return this->scenes;
}

// JP: 0x00265360  GetScene__4MenuFs  size 0x90
// Menu::GetScene(short)
int GetScene__4MenuFs(Menu *this,short param_2)
{
  int iVar1;
  iVar1 = this->scenes;
  while( true ) {
    if (iVar1 == 0) {
      return 0;
    }
    if (param_2 == *(short *)(iVar1 + 0x1c)) break;
    iVar1 = *(int *)(iVar1 + 0x14);
  }
  return iVar1;
}

// JP: 0x002653f0  DestroyScene__4MenuFP9MenuSceneb  size 0x8c
// Menu::DestroyScene(MenuScene*, bool)
void DestroyScene__4MenuFP9MenuSceneb(u32 param_1,int this,char param_3)
{
  RemoveScene__4MenuFP9MenuScene(param_1,this);
  if (param_3 == '\0') {
    if (this != 0) {
      VCALL(this, 0x8 /*dtor*/)(this,1);
    }
  }
  else {
    VCALL(this, 0xc /*DelayDelete*/)();
  }
  return;
}

// JP: 0x00265480  Create__4MenuFP9BufMemory  size 0x14
// Menu::Create(BufMemory*)
u32 Create__4MenuFP9BufMemory(void)
{
  return 1;
}

// JP: 0x002654a0  Polling__4MenuFv  size 0x14
// Menu::Polling()
u32 Polling__4MenuFv(void)
{
  return 1;
}

// JP: 0x002654c0  Active__4MenuFs  size 0x50
// Menu::Active(short)
void Active__4MenuFs(Menu *this,u16 param_2)
{
  long lVar1;
  lVar1 = GetScene__4MenuFs(this,param_2);
  this->active = (int)lVar1;
  if (lVar1 != 0) {
    Run__4MenuFv(this);
  }
  return;
}

// JP: 0x00265510  Ready__4MenuFsss  size 0x14
// Menu::Ready(short, short, short)
u64 Ready__4MenuFsss(void)
{
  return 0;
}

// JP: 0x00265530  GetKey__4MenuFv  size 0xf0
// Menu::GetKey()
void GetKey__4MenuFv(Menu *this)
{
  long lVar1;
  long lVar2;
  lVar1 = GetActive__4CPadFi(0);
  if (lVar1 == 0) {
    lVar2 = __nw__FUi(0x18);
    lVar1 = 0;
    if (lVar2 != 0) {
      lVar1 = __ct__4CPadFi(lVar2,0);
    }
    Enable__4CPadFv(lVar1);
  }
  this->keys =
       *(u16 *)((&m_pCoreArray__4CPad)[*(int *)((int)lVar1 + 4)] + 0x6c) & 0xff0f |
       *(u16 *)((&m_pCoreArray__4CPad)[*(int *)((int)lVar1 + 4)] + 0x70) & 0xf0;
  return;
}

// JP: 0x00265620  @24@__dt__4MenuFv  size 0x8
// @24@__dt__4MenuFv
int _24___dt__4MenuFv(Menu *this,short param_2)
{
  int iVar1;
  iVar1 = this + -0x18;
  if (iVar1 != 0) {
    *(u8 **)(this + -4) = __vt__4Menu;
    this->vptr = 0x404f50;
    __dt__13MenuDataTableFv(this + 0x10,0xffffffffffffffff);
    if (iVar1 != -0x18) {
      this->vptr = __vt__17DelayDeleteObject;
    }
    __dt__7CPolObjFv(iVar1,0);
    if (0 < param_2) {
      __dl__FPv(iVar1);
    }
  }
  return iVar1;
}
