/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x002758d0  __ct__9MenuGroupFv  size 0x50
// MenuGroup::MenuGroup()
int __ct__9MenuGroupFv(MenuGroup *this)
{
  __ct__9MenuPlaceFv(this);
  this->vptr = __vt__9MenuGroup;
  VCALL(this, 0x20 /*Clear*/)();
  return this;
}

// JP: 0x00275920  __dt__9MenuGroupFv  size 0x74
// MenuGroup::~MenuGroup()
int __dt__9MenuGroupFv(MenuGroup *this,short param_2)
{
  if (this != 0) {
    this->vptr = __vt__9MenuGroup;
    __dt__9MenuPlaceFv(this,0);
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}

// JP: 0x002759a0  AddPlace__9MenuGroupFP9MenuPlace  size 0x244
// MenuGroup::AddPlace(MenuPlace*)
void AddPlace__9MenuGroupFP9MenuPlace(MenuGroup *this,MenuPlace *menuPlace)
{
  float fVar1;
  float fVar2;
  if ((long)((ulong)menuPlace->pflags << 0x3b) < 0) {
    this->key_place = menuPlace;
  }
  if (menuPlace->x < this->min_x) {
    this->min_x = menuPlace->x;
  }
  if (menuPlace->y < this->min_y) {
    this->min_y = menuPlace->y;
  }
  fVar1 = menuPlace->x + menuPlace->w;
  fVar2 = this->min_x + this->w;
  if (fVar2 < fVar1) {
    this->w = this->w + (fVar1 - fVar2);
  }
  fVar1 = menuPlace->y + menuPlace->h;
  fVar2 = this->min_y + this->h;
  if (fVar2 < fVar1) {
    this->h = this->h + (fVar1 - fVar2);
  }
  if (this->children != 0) {
    menuPlace->next_place = this->children;
  }
  this->children = menuPlace;
  VCALL(menuPlace, 0x38 /*SetOwner*/)(menuPlace,this->owner);
  if (this->owner != 0) {
    VCALL(menuPlace, 0x4c /*Attach*/)(menuPlace,this->owner);
  }
  menuPlace->dirty0 = menuPlace->dirty0 | 0x3f;
  menuPlace->dirty1 = menuPlace->dirty1 | 0x3f;
  return;
}

// JP: 0x00275bf0  RemovePlace__9MenuGroupFP9MenuPlace  size 0x118
// MenuGroup::RemovePlace(MenuPlace*)
void RemovePlace__9MenuGroupFP9MenuPlace(MenuGroup *this,MenuPlace *menuPlace)
{
  int iVar1;
  int iVar2;
  int iVar3;
  iVar1 = this->children;
  iVar3 = 0;
  do {
    iVar2 = iVar1;
    if (iVar2 == 0) {
LAB_00275c88:
      if (iVar2 != 0) {
        if (this->key_place == menuPlace) {
          this->key_place = 0;
        }
        VCALL(menuPlace, 0x50 /*Detach*/)();
        VCALL(menuPlace, 0x38 /*SetOwner*/)(menuPlace,0);
      }
      return;
    }
    if (iVar2 == menuPlace) {
      if (iVar3 == 0) {
        this->children = menuPlace->next_place;
      }
      else {
        *(u32 *)(iVar3 + 0x38) = *(u32 *)(iVar2 + 0x38);
      }
      goto LAB_00275c88;
    }
    iVar1 = *(int *)(iVar2 + 0x38);
    iVar3 = iVar2;
  } while( true );
}

// JP: 0x00275d10  FindPlace__9MenuGroupFs  size 0x7c
// MenuGroup::FindPlace(short)
int FindPlace__9MenuGroupFs(MenuGroup *this,short param_2)
{
  int iVar1;
  for (iVar1 = this->children; (iVar1 != 0 && (param_2 != *(short *)(iVar1 + 0x16)));
      iVar1 = *(int *)(iVar1 + 0x38)) {
  }
  return iVar1;
}

// JP: 0x00275d90  GetKeyPlace__9MenuGroupFv  size 0x4c
// MenuGroup::GetKeyPlace()
int GetKeyPlace__9MenuGroupFv(MenuGroup *this)
{
  if (this->key_place != 0) {
    this = this->key_place;
  }
  return this;
}

// JP: 0x00275de0  GetKeyRect__9MenuGroupFP8DrawRect  size 0x13c
// MenuGroup::GetKeyRect(DrawRect*)
void GetKeyRect__9MenuGroupFP8DrawRect(MenuGroup *this,float *param_2)
{
  if (this->key_place == 0) {
    *param_2 = this->x;
    param_2[1] = this->y;
    param_2[2] = this->w;
    param_2[3] = this->h;
  }
  else {
    *param_2 = this->x + this->key_place->x;
    param_2[1] = this->y + this->key_place->y;
    param_2[2] = this->key_place->w;
    param_2[3] = this->key_place->h;
  }
  return;
}

// JP: 0x00275f20  AllotPacket__9MenuGroupFP4_QWDP4_QWD  size 0x108
// MenuGroup::AllotPacket(_QWD*, _QWD*)
void AllotPacket__9MenuGroupFP4_QWDP4_QWD(MenuGroup *this,int param_2,int param_3)
{
  int iVar1;
  int iVar2;
  int iVar3;
  if (param_2 == 0) {
    for (iVar1 = this->children; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x38)) {
      VCALL(iVar1, 0x44 /*AllotPacket*/)(iVar1,0,0);
    }
  }
  else {
    iVar3 = 0;
    for (iVar1 = this->children; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x38)) {
      VCALL(iVar1, 0x44 /*AllotPacket*/)(iVar1,param_2 + iVar3 * 0x10,param_3 + iVar3 * 0x10)
      ;
      iVar2 = VCALL(iVar1, 0x48 /*GetAllotCount*/)();
      iVar3 = iVar3 + iVar2;
    }
  }
  return;
}

// JP: 0x00276030  GetAllotCount__9MenuGroupFv  size 0x78
// MenuGroup::GetAllotCount()
int GetAllotCount__9MenuGroupFv(MenuGroup *this)
{
  int iVar1;
  int iVar2;
  int iVar3;
  iVar3 = 0;
  for (iVar1 = this->children; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x38)) {
    iVar2 = VCALL(iVar1, 0x48 /*GetAllotCount*/)();
    iVar3 = iVar3 + iVar2;
  }
  return iVar3;
}

// JP: 0x002760b0  SetColor__9MenuGroupFUcUcUc  size 0x78
// MenuGroup::SetColor(unsigned char, unsigned char, unsigned char)
void SetColor__9MenuGroupFUcUcUc
               (MenuGroup *this,u8 param_2,u8 param_3,u8 param_4)
{
  int iVar1;
  for (iVar1 = this->children; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x38)) {
    VCALL(iVar1, 0x30 /*SetColor*/)(iVar1,param_2,param_3,param_4);
  }
  return;
}

// JP: 0x00276130  SetBright__9MenuGroupFf  size 0x68
// MenuGroup::SetBright(float)
void SetBright__9MenuGroupFf(u32 param_1,int this)
{
  int iVar1;
  for (iVar1 = this->children; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x38)) {
    VCALL(iVar1, 0x34 /*SetBright*/)(param_1);
  }
  return;
}

// JP: 0x002761a0  SetOwner__9MenuGroupFP10MenuWindow  size 0x74
// MenuGroup::SetOwner(MenuWindow*)
void SetOwner__9MenuGroupFP10MenuWindow(MenuGroup *this,u32 menuWindow)
{
  int iVar1;
  for (iVar1 = this->children; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x38)) {
    VCALL(iVar1, 0x38 /*SetOwner*/)(iVar1,menuWindow);
  }
  this->owner = menuWindow;
  return;
}

// JP: 0x00276220  SetAlpha__9MenuGroupFUc  size 0x68
// MenuGroup::SetAlpha(unsigned char)
void SetAlpha__9MenuGroupFUc(MenuGroup *this,u8 param_2)
{
  int iVar1;
  for (iVar1 = this->children; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x38)) {
    VCALL(iVar1, 0x2c /*SetAlpha*/)(iVar1,param_2);
  }
  return;
}

// JP: 0x00276290  Attach__9MenuGroupFP10MenuWindow  size 0x8c
// MenuGroup::Attach(MenuWindow*)
void Attach__9MenuGroupFP10MenuWindow(MenuGroup *this,u32 menuWindow)
{
  int iVar1;
  for (iVar1 = this->children; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x38)) {
    VCALL(iVar1, 0x4c /*Attach*/)(iVar1,menuWindow);
  }
  this->flags = this->flags & 0xfb | 4;
  return;
}

// JP: 0x00276320  Detach__9MenuGroupFv  size 0x88
// MenuGroup::Detach()
void Detach__9MenuGroupFv(MenuGroup *this)
{
  int iVar1;
  for (iVar1 = this->children; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x38)) {
    VCALL(iVar1, 0x50 /*Detach*/)();
  }
  this->flags = this->flags & 0xfb;
  return;
}

// JP: 0x002763b0  Update__9MenuGroupFiiUs  size 0x198
// MenuGroup::Update(int, int, unsigned short)
void Update__9MenuGroupFiiUs(MenuGroup *this,int param_2,int param_3,u16 param_4)
{
  u8 bVar1;
  u16 uVar2;
  int iVar3;
  u8 *pbVar4;
  float fVar5;
  float fVar6;
  pbVar4 = (u8 *)(this + (m_Env__8VIF1Prim & 1) + 0x10);
  fVar5 = this->x;
  fVar6 = this->y;
  uVar2 = this->alpha;
  for (iVar3 = this->children; iVar3 != 0; iVar3 = *(int *)(iVar3 + 0x38)) {
    bVar1 = *pbVar4;
    *(u8 *)(iVar3 + 0x10) = *(u8 *)(iVar3 + 0x10) | bVar1;
    *(u8 *)(iVar3 + 0x11) = *(u8 *)(iVar3 + 0x11) | bVar1;
    if (((*(u8 *)(iVar3 + 0x12) & 1) != 0) &&
       (*(char *)(iVar3 + (m_Env__8VIF1Prim & 1) + 0x10) != '\0')) {
      VCALL(iVar3, 0x14 /*Update*/)
                (iVar3,param_2 + (int)fVar5 * 0x10,param_3 + (int)fVar6 * 0x10,
                 (short)((uint)param_4 * (uint)uVar2 >> 0xf));
    }
  }
  *pbVar4 = *pbVar4 & 0x80;
  return;
}

// JP: 0x00276550  Connect__9MenuGroupFP4_QWD  size 0x84
// MenuGroup::Connect(_QWD*)
u32 Connect__9MenuGroupFP4_QWD(MenuGroup *this,u32 param_2)
{
  int iVar1;
  u32 uStack_10;
  uStack_10 = param_2;
  for (iVar1 = this->children; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x38)) {
    if ((*(u8 *)(iVar1 + 0x12) & 1) != 0) {
      uStack_10 = VCALL(iVar1, 0x18 /*Connect*/)(iVar1,uStack_10);
    }
  }
  return uStack_10;
}

// JP: 0x002765e0  Clear__9MenuGroupFv  size 0x58
// MenuGroup::Clear()
void Clear__9MenuGroupFv(MenuGroup *this)
{
  u32 uVar1;
  Clear__9MenuPlaceFv(this);
  uVar1 = sm_fZero__7MenuObj;
  this->min_y = sm_fZero__7MenuObj;
  this->min_x = uVar1;
  this->key_place = 0;
  this->children = 0;
  this->alpha = 0x8000;
  return;
}
