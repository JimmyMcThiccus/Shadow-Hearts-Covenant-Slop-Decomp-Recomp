/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x00267e40  __ct__10MenuWindowFv  size 0xa0
// MenuWindow::MenuWindow()
int __ct__10MenuWindowFv(MenuWindow *this)
{
  __ct__7MenuObjFv(this);
  __ct__12MenuObjTableFv(this + 0x18);
  __ct__10MenuPacketFv(this + 0x24);
  this->vptr = __vt__10MenuWindow;
  this->objs = 0x405084;
  this->packet = 0x405090;
  __ct__7ScissorFv(this + 0x4c);
  VCALL(this, 0x20 /*Clear*/)();
  return this;
}

// JP: 0x00267ee0  __dt__10MenuWindowFv  size 0xe4
// MenuWindow::~MenuWindow()
int __dt__10MenuWindowFv(MenuWindow *this,short param_2)
{
  if (this != 0) {
    this->vptr = __vt__10MenuWindow;
    this->objs = 0x405084;
    this->packet = 0x405090;
    VCALL(this, 0x1c /*Destroy*/)();
    __dt__7ScissorFv(this + 0x4c,0xffffffffffffffff);
    __dt__10MenuPacketFv(this + 0x24,0);
    __dt__12MenuObjTableFv(this + 0x18,0);
    __dt__7MenuObjFv(this,0);
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}

// JP: 0x00267fd0  Create__10MenuWindowFUcUcffff  size 0x390
// MenuWindow::Create(unsigned char, unsigned char, float, float, float, float)
void Create__10MenuWindowFUcUcffff
               (u32 param_1,u32 param_2,float param_3,float param_4,int this,
               u8 param_6,u8 param_7)
{
  u32 uVar1;
  long lVar2;
  ulong uVar3;
  CreatePacket__10MenuPacketFUs(this + 0x24,4);
  if (this->frame != 0) {
    VCALL(this->frame, 0xc /*DelayDelete*/)();
    this->frame = 0;
  }
  switch(param_6) {
  case 1:
    lVar2 = __nw__FUi(0x250);
    uVar1 = 0;
    if (lVar2 != 0) {
      uVar1 = __ct__17MenuWindowMessageFv(lVar2);
    }
    this->frame = uVar1;
    break;
  case 2:
    lVar2 = __nw__FUi(0xac);
    uVar1 = 0;
    if (lVar2 != 0) {
      uVar1 = __ct__14MenuWindowFaceFv(lVar2);
    }
    this->frame = uVar1;
    break;
  case 3:
    lVar2 = __nw__FUi(0x2ec);
    uVar1 = 0;
    if (lVar2 != 0) {
      uVar1 = __ct__14MenuWindowNoteFv(lVar2);
    }
    this->frame = uVar1;
    break;
  case 4:
    lVar2 = __nw__FUi(0xd8);
    uVar1 = 0;
    if (lVar2 != 0) {
      uVar1 = __ct__15MenuWindowFrameFv(lVar2);
    }
    this->frame = uVar1;
    break;
  case 5:
    lVar2 = __nw__FUi(0xa0);
    uVar1 = 0;
    if (lVar2 != 0) {
      uVar1 = __ct__15MenuWindowPlainFv(lVar2);
    }
    this->frame = uVar1;
    break;
  case 6:
    lVar2 = __nw__FUi(0x490);
    uVar1 = 0;
    if (lVar2 != 0) {
      uVar1 = __ct__17MenuWindowGeneralFv(lVar2);
    }
    this->frame = uVar1;
    break;
  case 7:
    lVar2 = __nw__FUi(0x22c);
    uVar1 = 0;
    if (lVar2 != 0) {
      uVar1 = __ct__17MenuWindowCompactFv(lVar2);
    }
    this->frame = uVar1;
  }
  if (this->frame != 0) {
    VCALL(this->frame, 0x24 /*SetPosition*/)(this->frame,this);
  }
  this->wflags0 = this->wflags0 & 0xfe3f | (param_6 & 7) << 6;
  SetClip__10MenuWindowFUc(this,param_7);
  SetPosition__10MenuWindowFff(param_1,param_2,this);
  SetSize__10MenuWindowFff(param_3 + 1.0,param_4 + 1.0,this);
  uVar3 = (ulong)this->dirty1 & 0xffffffffffffff7f | 0x80;
  this->dirty1 = (char)uVar3;
  this->dirty0 =
       this->dirty0 & 0x7f | (u8)((uint)((uVar3 << 0x38) >> 0x3f) << 7);
  this->dirty0 = this->dirty0 | 0x3f;
  this->dirty1 = this->dirty1 | 0x3f;
  this->env_dirty = 0;
  this->env_dirty2 = this->env_dirty2 | 0x3f;
  return;
}

// JP: 0x00268360  CreateScroll__10MenuWindowFUissffUc  size 0x2f8
// MenuWindow::CreateScroll(unsigned int, short, short, float, float, unsigned char)
void CreateScroll__10MenuWindowFUissffUc
               (u32 param_1,u32 param_2,int this,int param_4,short param_5,
               short param_6,u8 param_7)
{
  int iVar1;
  u8 bVar2;
  u32 uVar3;
  long lVar4;
  u64 uVar5;
  u32 *puVar6;
  short sVar7;
  if (this->scroll != 0) {
    VCALL(this->scroll, 0xc /*DelayDelete*/)();
  }
  lVar4 = __nw__FUi(0x3c);
  puVar6 = (u32 *)0x0;
  if (lVar4 != 0) {
    puVar6 = (u32 *)lVar4;
    *puVar6 = 0;
    puVar6[1] = 0;
    puVar6[2] = __vt__17DelayDeleteObject;
    puVar6[2] = __vt__10ScrollData;
    puVar6[4] = 0;
  }
  this->scroll = puVar6;
  sVar7 = param_6;
  if (param_6 <= param_5) {
    sVar7 = param_5;
  }
  puVar6[3] = (short)(param_5 * param_6 + sVar7) * param_4;
  *(short *)(puVar6 + 6) = param_5;
  *(short *)((int)puVar6 + 0x1a) = param_6;
  puVar6[7] = param_1;
  puVar6[8] = param_2;
  *(u16 *)((int)puVar6 + 0x36) = 0;
  puVar6[9] = 0;
  puVar6[10] = 0;
  *(u16 *)(puVar6 + 0xd) = 0;
  if (param_4 != 0) {
    iVar1 = puVar6[3];
    uVar5 = __nwa__FUi(iVar1 * 0x20 + 0x10);
    uVar3 = __construct_new_array(uVar5,0x224b30,0,0x10,iVar1 << 1);
    puVar6[4] = uVar3;
    puVar6[5] = puVar6[4] + puVar6[3] * 0x10;
  }
  bVar2 = ~param_7;
  lVar4 = GetCornerPlace__10MenuWindowFis(this,8,0);
  if ((lVar4 != 0) && (*(short *)((int)lVar4 + 0x1c) != 0)) {
    bVar2 = bVar2 | 0xc;
  }
  lVar4 = GetCornerPlace__10MenuWindowFis(this,2,0);
  if ((lVar4 != 0) && (*(short *)((int)lVar4 + 0x1e) != 0)) {
    bVar2 = bVar2 | 3;
  }
  CreateScrollMark__10MenuWindowFUc(this,bVar2);
  this->mark_mask = param_7;
  return;
}

// JP: 0x00268660  CreateScrollMark__10MenuWindowFUc  size 0xf8
// MenuWindow::CreateScrollMark(unsigned char)
void CreateScrollMark__10MenuWindowFUc(MenuWindow *this,u8 param_2)
{
  u32 uVar1;
  long lVar2;
  if (this->mark != 0) {
    VCALL(this->mark, 0xc /*DelayDelete*/)();
  }
  lVar2 = __nw__FUi(0x84);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = __ct__10ScrollMarkFv(lVar2);
  }
  this->mark = uVar1;
  Create__10ScrollMarkFUcP10MenuWindowUc(this->mark,param_2,this,0);
  SetArea__10ScrollMarkFUcffff
            (0xbf800000,0xbf800000,this->w + 2.0,this->h + 2.0
             ,this->mark,this->mark_mask);
  return;
}

// JP: 0x00268760  AddPlace__10MenuWindowFP9MenuPlace  size 0x9c
// MenuWindow::AddPlace(MenuPlace*)
void AddPlace__10MenuWindowFP9MenuPlace(int param_1,int this)
{
  if (*(int *)(param_1 + 0x38) != 0) {
    this->places = *(u32 *)(param_1 + 0x38);
  }
  *(int *)(param_1 + 0x38) = this;
  VCALL(this, 0x38 /*SetOwner*/)(this,param_1);
  if ((this->f_21 /*u8 **/ & 1) == 0) {
    VCALL(this, 0x4c /*Attach*/)(this,param_1);
  }
  return;
}

// JP: 0x00268800  RemovePlace__10MenuWindowFP9MenuPlace  size 0xe4
// MenuWindow::RemovePlace(MenuPlace*)
void RemovePlace__10MenuWindowFP9MenuPlace(int param_1,int this)
{
  int iVar1;
  int iVar2;
  int iVar3;
  iVar1 = *(int *)(param_1 + 0x38);
  iVar3 = 0;
  while (iVar2 = iVar1, iVar2 != 0) {
    if (iVar2 == this) {
      if (iVar3 == 0) {
        *(u32 *)(param_1 + 0x38) = this->places;
      }
      else {
        *(u32 *)(iVar3 + 0x38) = *(u32 *)(iVar2 + 0x38);
      }
    }
    iVar3 = iVar2;
    iVar1 = *(int *)(iVar2 + 0x38);
  }
  VCALL(this, 0x50 /*Detach*/)();
  VCALL(this, 0x38 /*SetOwner*/)(this,0);
  return;
}

// JP: 0x002688f0  ClearPlace__10MenuWindowFv  size 0xac
// MenuWindow::ClearPlace()
void ClearPlace__10MenuWindowFv(MenuWindow *this)
{
  int iVar1;
  int iVar2;
  iVar2 = this->places;
  while (iVar2 != 0) {
    iVar1 = *(int *)(iVar2 + 0x38);
    VCALL(iVar2, 0x38 /*SetOwner*/)(iVar2,0);
    *(u8 *)(iVar2 + 0x12) = *(u8 *)(iVar2 + 0x12) & 0xfb;
    *(u32 *)(iVar2 + 0x38) = 0;
    iVar2 = iVar1;
  }
  this->places = 0;
  ClearTable__12MenuObjTableFv(this + 0x18);
  return;
}

// JP: 0x002689a0  GetCornerPlace__10MenuWindowFis  size 0x31c
// MenuWindow::GetCornerPlace(int, short)
int GetCornerPlace__10MenuWindowFis(MenuWindow *this,int param_2,short param_3)
{
  int iVar1;
  int iVar2;
  iVar2 = 0;
  iVar1 = this->places;
  if (param_2 == 8) {
    for (; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x38)) {
      if ((((long)((ulong)*(u8 *)(iVar1 + 0x21) << 0x3e) < 0) &&
          (param_3 == *(short *)(iVar1 + 0x1c))) &&
         ((iVar2 == 0 || (*(short *)(iVar2 + 0x1c) < *(short *)(iVar1 + 0x1c))))) {
        iVar2 = iVar1;
      }
    }
  }
  else if (param_2 == 4) {
    for (; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x38)) {
      if ((((long)((ulong)*(u8 *)(iVar1 + 0x21) << 0x3e) < 0) &&
          (param_3 == *(short *)(iVar1 + 0x1e))) &&
         ((iVar2 == 0 || (*(short *)(iVar1 + 0x1c) < *(short *)(iVar2 + 0x1c))))) {
        iVar2 = iVar1;
      }
    }
  }
  else if (param_2 == 2) {
    for (; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x38)) {
      if ((((long)((ulong)*(u8 *)(iVar1 + 0x21) << 0x3e) < 0) &&
          (param_3 == *(short *)(iVar1 + 0x1c))) &&
         ((iVar2 == 0 || (*(short *)(iVar2 + 0x1e) < *(short *)(iVar1 + 0x1e))))) {
        iVar2 = iVar1;
      }
    }
  }
  else if (param_2 == 1) {
    for (; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x38)) {
      if ((((long)((ulong)*(u8 *)(iVar1 + 0x21) << 0x3e) < 0) &&
          (param_3 == *(short *)(iVar1 + 0x1c))) &&
         ((iVar2 == 0 || (*(short *)(iVar1 + 0x1e) < *(short *)(iVar2 + 0x1e))))) {
        iVar2 = iVar1;
      }
    }
  }
  return iVar2;
}

// JP: 0x00268cc0  GetPlace__10MenuWindowFss  size 0xb0
// MenuWindow::GetPlace(short, short)
int GetPlace__10MenuWindowFss(MenuWindow *this,short param_2,short param_3)
{
  int iVar1;
  for (iVar1 = this->places;
      (iVar1 != 0 &&
      ((param_2 != *(short *)(iVar1 + 0x1c) || (param_3 != *(short *)(iVar1 + 0x1e)))));
      iVar1 = *(int *)(iVar1 + 0x38)) {
  }
  return iVar1;
}

// JP: 0x00268d70  GetPlace__10MenuWindowFs  size 0x7c
// MenuWindow::GetPlace(short)
int GetPlace__10MenuWindowFs(MenuWindow *this,short param_2)
{
  int iVar1;
  for (iVar1 = this->places; (iVar1 != 0 && (param_2 != *(short *)(iVar1 + 0x16)));
      iVar1 = *(int *)(iVar1 + 0x38)) {
  }
  return iVar1;
}

// JP: 0x00268df0  GetPlace__10MenuWindowFiss  size 0x4c0
// MenuWindow::GetPlace(int, short, short)
int GetPlace__10MenuWindowFiss(int param_1,int param_2,short this,short param_4)
{
  int iVar1;
  int iVar2;
  iVar2 = *(int *)(param_1 + 0x38);
  iVar1 = 0;
  if (param_2 == 8) {
    for (; iVar2 != 0; iVar2 = *(int *)(iVar2 + 0x38)) {
      if ((((long)((ulong)*(u8 *)(iVar2 + 0x21) << 0x3e) < 0) &&
          (param_4 == *(short *)(iVar2 + 0x1e))) && (this < *(short *)(iVar2 + 0x1c))) {
        if ((long)(this + 1) == (long)*(short *)(iVar2 + 0x1c)) {
          return iVar2;
        }
        if ((iVar1 == 0) || (*(short *)(iVar2 + 0x1c) < *(short *)(iVar1 + 0x1c))) {
          iVar1 = iVar2;
        }
      }
    }
  }
  else if (param_2 == 4) {
    for (; iVar2 != 0; iVar2 = *(int *)(iVar2 + 0x38)) {
      if ((((long)((ulong)*(u8 *)(iVar2 + 0x21) << 0x3e) < 0) &&
          (param_4 == *(short *)(iVar2 + 0x1e))) && (*(short *)(iVar2 + 0x1c) < this)) {
        if ((long)(this + -1) == (long)*(short *)(iVar2 + 0x1c)) {
          return iVar2;
        }
        if ((iVar1 == 0) || (*(short *)(iVar1 + 0x1c) < *(short *)(iVar2 + 0x1c))) {
          iVar1 = iVar2;
        }
      }
    }
  }
  else if (param_2 == 2) {
    for (; iVar2 != 0; iVar2 = *(int *)(iVar2 + 0x38)) {
      if ((((long)((ulong)*(u8 *)(iVar2 + 0x21) << 0x3e) < 0) &&
          (this == *(short *)(iVar2 + 0x1c))) && (param_4 < *(short *)(iVar2 + 0x1e))) {
        if ((long)(param_4 + 1) == (long)*(short *)(iVar2 + 0x1e)) {
          return iVar2;
        }
        if ((iVar1 == 0) || (*(short *)(iVar2 + 0x1e) < *(short *)(iVar1 + 0x1e))) {
          iVar1 = iVar2;
        }
      }
    }
  }
  else if (param_2 == 1) {
    for (; iVar2 != 0; iVar2 = *(int *)(iVar2 + 0x38)) {
      if ((((long)((ulong)*(u8 *)(iVar2 + 0x21) << 0x3e) < 0) &&
          (this == *(short *)(iVar2 + 0x1c))) && (*(short *)(iVar2 + 0x1e) < param_4)) {
        if ((long)(param_4 + -1) == (long)*(short *)(iVar2 + 0x1e)) {
          return iVar2;
        }
        if ((iVar1 == 0) || (*(short *)(iVar1 + 0x1e) < *(short *)(iVar2 + 0x1e))) {
          iVar1 = iVar2;
        }
      }
    }
  }
  return iVar1;
}

// JP: 0x002692b0  MovePlace__10MenuWindowFiss  size 0x170
// MenuWindow::MovePlace(int, short, short)
long MovePlace__10MenuWindowFiss(MenuWindow *this,int param_2,u16 param_3,u16 param_4)
{
  long lVar1;
  lVar1 = GetPlace__10MenuWindowFiss(this,param_2,param_3,param_4);
  if (lVar1 == 0) {
    if (param_2 == 8) {
      if ((long)((ulong)this->wflags1 << 0x3c) < 0) {
        lVar1 = GetCornerPlace__10MenuWindowFis(this,4,param_4);
      }
    }
    else if (param_2 == 4) {
      if ((long)((ulong)this->wflags1 << 0x3c) < 0) {
        lVar1 = GetCornerPlace__10MenuWindowFis(this,8,param_4);
      }
    }
    else if (param_2 == 2) {
      if ((long)((ulong)this->wflags1 << 0x3b) < 0) {
        lVar1 = GetCornerPlace__10MenuWindowFis(this,1,param_3);
      }
    }
    else if ((param_2 == 1) && ((long)((ulong)this->wflags1 << 0x3b) < 0)) {
      lVar1 = GetCornerPlace__10MenuWindowFis(this,2,param_3);
    }
  }
  return lVar1;
}

// JP: 0x00269420  SetCursor__10MenuWindowFP6Cursori  size 0x294
// MenuWindow::SetCursor(Cursor*, int)
int SetCursor__10MenuWindowFP6Cursori(MenuWindow *this,Cursor *cursor,int param_3)
{
  int iVar1;
  int iVar2;
  float fStack_44;
  float fStack_40;
  float fStack_3c;
  float fStack_38;
  float fStack_34;
  int iStack_30;
  int iStack_20;
  int iStack_10;
  iVar2 = 0;
  fStack_3c = 0.0;
  iVar1 = this->places;
  iStack_30 = this;
  iStack_20 = cursor;
  iStack_10 = param_3;
  GetScreen__6CursorFPfPf(cursor,&fStack_34,&fStack_38);
  fStack_34 = fStack_34 - (*(float *)(iStack_30 + 100) + *(float *)(iStack_30 + 0x8c));
  fStack_38 = fStack_38 - (*(float *)(iStack_30 + 0x68) + *(float *)(iStack_30 + 0x90));
  if (iStack_10 != 3) {
    if (iStack_10 == 2) {
      for (; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x38)) {
        if ((long)((ulong)*(u8 *)(iVar1 + 0x21) << 0x3e) < 0) {
          GetTarget__6CursorFP8DrawRectPfPf(iStack_20,iVar1 + 0x24,&fStack_40,&fStack_44);
          fStack_44 = fStack_38 - fStack_44;
          if (fStack_44 < 0.0) {
            fStack_44 = -fStack_44;
          }
          if ((iVar2 == 0) || (fStack_44 < fStack_3c)) {
            fStack_3c = fStack_44;
            iVar2 = iVar1;
          }
        }
      }
    }
    else if (iStack_10 == 1) {
      for (; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x38)) {
        if ((long)((ulong)*(u8 *)(iVar1 + 0x21) << 0x3e) < 0) {
          GetTarget__6CursorFP8DrawRectPfPf(iStack_20,iVar1 + 0x24,&fStack_40,&fStack_44);
          fStack_40 = fStack_34 - fStack_40;
          if (fStack_40 < 0.0) {
            fStack_40 = -fStack_40;
          }
          if ((iVar2 == 0) || (fStack_40 < fStack_3c)) {
            fStack_3c = fStack_40;
            iVar2 = iVar1;
          }
        }
      }
    }
  }
  if (iVar2 != 0) {
    **(float **)(iStack_20 + 0xd8) = fStack_34;
    *(float *)(*(int *)(iStack_20 + 0xd8) + 4) = fStack_38;
    IsSelected__9MenuPlaceFP6Cursor(iVar2,iStack_20);
  }
  return iVar2;
}

// JP: 0x002696c0  Scroll__10MenuWindowFss  size 0x1e8
// MenuWindow::Scroll(short, short)
int Scroll__10MenuWindowFss(MenuWindow *this,short param_2,short param_3)
{
  int iVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  iVar1 = 0;
  fVar2 = (float)GetTargetX__10MenuWindowCFv(this);
  fVar3 = this->scroll->cell_w;
  fVar4 = (float)GetTargetY__10MenuWindowCFv(this);
  if (param_2 == (short)(int)(-fVar2 / fVar3)) {
    if (param_3 != (short)(int)(-fVar4 / this->scroll->cell_h)) {
      this->scroll->target_x = this->scroll_x;
      this->scroll->target_y =
           -((float)(int)param_3 * this->scroll->cell_h);
      this->scroll->scrolling = 1;
      iVar1 = 1;
    }
  }
  else {
    this->scroll->target_x =
         -((float)(int)param_2 * this->scroll->cell_w);
    this->scroll->target_y = this->scroll_y;
    this->scroll->scrolling = 2;
    iVar1 = 1;
  }
  if (iVar1 != 0) {
    SetScrollMark__10MenuWindowFss(this,param_2,param_3);
  }
  return iVar1;
}

// JP: 0x002698b0  Scroll__10MenuWindowFP9MenuPlace  size 0x2c4
// MenuWindow::Scroll(MenuPlace*)
u64 Scroll__10MenuWindowFP9MenuPlace(int param_1,int this)
{
  short sVar1;
  short sVar2;
  u64 uVar3;
  float fVar4;
  if (*(int *)(param_1 + 0x40) != 0) {
    fVar4 = (float)GetTargetX__10MenuWindowCFv(param_1);
    sVar1 = (short)(int)(-fVar4 / *(float *)(*(int *)(param_1 + 0x40) + 0x1c));
    fVar4 = (float)GetTargetY__10MenuWindowCFv(param_1);
    sVar2 = (short)(int)(-fVar4 / *(float *)(*(int *)(param_1 + 0x40) + 0x20));
    if ((this->f_1c /*short **/ < sVar1) || (this->f_1e /*short **/ < sVar2)) {
      uVar3 = Scroll__10MenuWindowFss
                        (param_1,this->f_1c /*u16 **/,this->f_1e /*u16 **/);
      return uVar3;
    }
    if ((long)((int)sVar1 + (int)*(short *)(*(int *)(param_1 + 0x40) + 0x18)) <=
        (long)this->f_1c /*short **/) {
      uVar3 = Scroll__10MenuWindowFss
                        (param_1,(this->f_1c /*short **/ -
                                 *(short *)(*(int *)(param_1 + 0x40) + 0x18)) + 1,sVar2);
      return uVar3;
    }
    if ((long)((int)sVar2 + (int)*(short *)(*(int *)(param_1 + 0x40) + 0x1a)) <=
        (long)this->f_1e /*short **/) {
      uVar3 = Scroll__10MenuWindowFss
                        (param_1,sVar1,
                         (this->f_1e /*short **/ - *(short *)(*(int *)(param_1 + 0x40) + 0x1a))
                         + 1);
      return uVar3;
    }
  }
  return 0;
}

// JP: 0x00269b80  Scroll__10MenuWindowFP8DrawRect  size 0x310
// MenuWindow::Scroll(DrawRect*)
u64 Scroll__10MenuWindowFP8DrawRect(MenuWindow *this,float *param_2)
{
  u64 uVar1;
  float fVar2;
  float fVar3;
  if (this->scroll != 0) {
    fVar2 = (float)GetTargetX__10MenuWindowCFv(this);
    fVar3 = (float)GetTargetY__10MenuWindowCFv(this);
    if (param_2[1] < -fVar3) {
      fVar2 = (float)GetTargetX__10MenuWindowCFv(this);
      uVar1 = Scroll__10MenuWindowFss
                        (this,(short)(int)(-fVar2 / this->scroll->cell_w),
                         (int)(param_2[1] / this->scroll->cell_h));
      return uVar1;
    }
    if (-fVar3 + this->h < param_2[3]) {
      fVar2 = (float)GetTargetX__10MenuWindowCFv(this);
      uVar1 = Scroll__10MenuWindowFss
                        (this,(short)(int)(-fVar2 / this->scroll->cell_w),
                         (short)(int)(param_2[3] / this->scroll->cell_h) -
                         this->scroll->rows);
      return uVar1;
    }
    if (*param_2 < -fVar2) {
      fVar2 = (float)GetTargetY__10MenuWindowCFv(this);
      uVar1 = Scroll__10MenuWindowFss
                        (this,(int)(*param_2 / this->scroll->cell_w),
                         (short)(int)(-fVar2 / this->scroll->cell_h));
      return uVar1;
    }
    if (-fVar2 + this->w < param_2[2]) {
      fVar2 = (float)GetTargetY__10MenuWindowCFv(this);
      uVar1 = Scroll__10MenuWindowFss
                        (this,(short)(int)(param_2[2] /
                                             this->scroll->cell_w) -
                                 this->scroll->cols,
                         (short)(int)(-fVar2 / this->scroll->cell_h));
      return uVar1;
    }
  }
  return 0;
}

// JP: 0x00269e90  SetScroll__10MenuWindowFss  size 0xa8
// MenuWindow::SetScroll(short, short)
void SetScroll__10MenuWindowFss(MenuWindow *this,short param_2,short param_3)
{
  if (this->scroll != 0) {
    SetOffset__10MenuWindowFff
              ((float)-(int)param_2 * this->scroll->cell_w,
               (float)-(int)param_3 * this->scroll->cell_h,this);
    this->scroll->scrolling = 0;
  }
  return;
}

// JP: 0x00269f40  FinishScroll__10MenuWindowFv  size 0x88
// MenuWindow::FinishScroll()
void FinishScroll__10MenuWindowFv(MenuWindow *this)
{
  if ((this->scroll != 0) && (this->scroll->scrolling != 0)) {
    this->scroll_x = this->scroll->target_x;
    this->scroll_y = this->scroll->target_y;
    this->scroll->scrolling = 0;
    AllotPacket__10MenuWindowFv(this);
  }
  return;
}

// JP: 0x00269fd0  Open__10MenuWindowFUci  size 0x268
// MenuWindow::Open(unsigned char, int)
/* WARNING: Removing unreachable block (ram,0x0026a08c) */
u8 Open__10MenuWindowFUci(MenuWindow *this,u8 param_2,int param_3)
{
  u16 uVar1;
  u32 uVar2;
  Finish__10MenuWindowFv(this);
  this->flags = this->flags & 0xfe | 1;
  this->alpha = 0x8000;
  if (param_3 != 0) {
    switch(param_2) {
    default:
      uVar1 = this->alpha;
      this->alpha = 0;
      SetupFade__10MenuWindowFif((float)uVar1,this,param_3);
      break;
    case 1:
      uVar2 = this->y;
      this->y = -(this->h + 100.0);
      SetupMove__10MenuWindowFiff(this->x,uVar2,this,param_3);
      break;
    case 2:
      uVar2 = this->y;
      this->y = 0x44090000;
      SetupMove__10MenuWindowFiff(this->x,uVar2,this,param_3);
      break;
    case 3:
      uVar2 = this->x;
      this->x = -(this->w + 100.0);
      SetupMove__10MenuWindowFiff(uVar2,this->y,this,param_3);
      break;
    case 4:
      uVar2 = this->x;
      this->x = 0x44190000;
      SetupMove__10MenuWindowFiff(uVar2,this->y,this,param_3);
      break;
    case 5:
      SetupZoom__10MenuWindowFiUc(this,param_3,1);
    }
  }
  return this->state;
}

// JP: 0x0026a240  Close__10MenuWindowFUci  size 0x230
// MenuWindow::Close(unsigned char, int)
u8 Close__10MenuWindowFUci(MenuWindow *this,u8 param_2,u32 param_3)
{
  u32 uVar1;
  this->state = 1;
  this->wflags1 = this->wflags1 & 0x7f | 0x80;
  this->wflags2 = this->wflags2 & 0xfe | 1;
  switch(param_2) {
  default:
    SetupFade__10MenuWindowFif(0,this,param_3);
    break;
  case 1:
    uVar1 = this->y;
    SetupMove__10MenuWindowFiff
              (this->x,-(this->h + 100.0),this,param_3)
    ;
    this->anim_b = uVar1;
    break;
  case 2:
    uVar1 = this->y;
    SetupMove__10MenuWindowFiff(this->x,0x44090000,this,param_3);
    this->anim_b = uVar1;
    break;
  case 3:
    uVar1 = this->x;
    SetupMove__10MenuWindowFiff
              (-(this->w + 100.0),this->y,this,param_3
              );
    this->anim_a = uVar1;
    break;
  case 4:
    uVar1 = this->x;
    SetupMove__10MenuWindowFiff(0x44190000,this->y,this,param_3);
    this->anim_a = uVar1;
    break;
  case 5:
    SetupZoom__10MenuWindowFiUc(this,param_3,0);
  }
  return this->state;
}

// JP: 0x0026a470  Finish__10MenuWindowFv  size 0x2a4
// MenuWindow::Finish()
void Finish__10MenuWindowFv(MenuWindow *this)
{
  char cVar1;
  ulong uVar2;
  u16 uVar3;
  float fVar4;
  cVar1 = this->state;
  if (cVar1 != '\b') {
    if (cVar1 == '\a') {
      fVar4 = this->anim_a;
      if (fVar4 < 2.1474836e+09) {
        uVar3 = (u16)(int)fVar4;
      }
      else {
        uVar3 = (u16)(int)(fVar4 - 2.1474836e+09);
      }
      this->alpha = uVar3;
      this->env_dirty = this->env_dirty & 0xef | 0x10;
      this->env_dirty2 = this->env_dirty2 & 0xef | 0x10;
    }
    else if (cVar1 == '\x06') {
      SetPosition__10MenuWindowFff
                (this->x,this->y,this);
      SetSize__10MenuWindowFff
                (this->w,this->h,this);
      this->clip_x = this->clip0_x;
      this->clip_y = this->clip0_y;
      this->clip_w = this->clip0_w;
      this->clip_h = this->clip0_h;
      if (this->frame != 0) {
        VCALL(this->frame, 0x28 /*SetSize*/)
                  (0,0,this->w,this->h);
      }
      uVar2 = (ulong)this->dirty1 & 0xfffffffffffffffd | 2;
      this->dirty1 = (char)uVar2;
      this->dirty0 =
           this->dirty0 & 0xfd | (u8)((uint)((uVar2 << 0x3e) >> 0x3f) << 1);
      this->env_dirty = this->env_dirty & 0xf7 | 8;
    }
    else if (cVar1 == '\x05') {
      SetPosition__10MenuWindowFff
                (this->anim_a,this->anim_b,this);
    }
  }
  ClearWork__10MenuWindowFv(this);
  return;
}

// JP: 0x0026a720  SetupMove__10MenuWindowFiff  size 0xf4
// MenuWindow::SetupMove(int, float, float)
u8 SetupMove__10MenuWindowFiff(float param_1,float param_2,int this,int param_4)
{
  this->anim_da = (param_1 - this->x) / (float)param_4;
  this->anim_db = (param_2 - this->y) / (float)param_4;
  if ((this->wflags2 & 1) == 0) {
    this->anim_a = param_1;
    this->anim_b = param_2;
  }
  else {
    this->anim_a = this->x;
    this->anim_b = this->y;
  }
  this->anim_time = param_4;
  this->state = 5;
  return this->state;
}

// JP: 0x0026a820  SetupFade__10MenuWindowFif  size 0xf4
// MenuWindow::SetupFade(int, float)
/* WARNING: Removing unreachable block (ram,0x0026a868) */
u8 SetupFade__10MenuWindowFif(float param_1,int this,int param_3)
{
  this->anim_da = (param_1 - (float)this->alpha) / (float)param_3;
  if ((this->wflags2 & 1) == 0) {
    this->anim_a = param_1;
  }
  else {
    this->anim_a = (float)this->alpha;
  }
  this->anim_time = param_3;
  this->state = 7;
  return this->state;
}

// JP: 0x0026a920  SetupZoom__10MenuWindowFiUc  size 0x138
// MenuWindow::SetupZoom(int, unsigned char)
u8 SetupZoom__10MenuWindowFiUc(MenuWindow *this,int param_2,char param_3)
{
  this->anim_da = (this->w * 0.5) / (float)param_2;
  this->anim_db = (this->h * 0.5) / (float)param_2;
  if (param_3 == '\x01') {
    this->anim_da = -this->anim_da;
    this->anim_db = -this->anim_db;
    this->anim_a = this->w * 0.5;
    this->anim_b = this->h * 0.5;
  }
  this->anim_time = param_2;
  this->state = 6;
  this->wflags1 = this->wflags1 & 0x9f | 0x40;
  return this->state;
}

// JP: 0x0026aa60  SetPosition__10MenuWindowFff  size 0xc8
// MenuWindow::SetPosition(float, float)
void SetPosition__10MenuWindowFff(u32 param_1,u32 param_2,int this)
{
  ulong uVar1;
  this->x = param_1;
  this->y = param_2;
  uVar1 = (ulong)this->dirty1 & 0xfffffffffffffffd | 2;
  this->dirty1 = (char)uVar1;
  this->dirty0 =
       this->dirty0 & 0xfd | (u8)((uint)((uVar1 << 0x3e) >> 0x3f) << 1);
  this->env_dirty = this->env_dirty & 0xf7 | 8;
  this->env_dirty2 = this->env_dirty2 & 0xf7 | 8;
  return;
}

// JP: 0x0026ab30  SetSize__10MenuWindowFff  size 0x1d4
// MenuWindow::SetSize(float, float)
void SetSize__10MenuWindowFff(float param_1,float param_2,int this)
{
  ulong uVar1;
  this->w = param_1;
  this->h = param_2;
  if (((ulong)this->wflags1 & 7) >> 1 == 1) {
    this->clip0_w = (short)(int)param_1;
    this->clip0_h = (short)(int)param_2;
    this->clip_w = this->clip0_w;
    this->clip_h = this->clip0_h;
    uVar1 = (ulong)this->dirty1 & 0xfffffffffffffffd | 2;
    this->dirty1 = (char)uVar1;
    this->dirty0 =
         this->dirty0 & 0xfd | (u8)((uint)((uVar1 << 0x3e) >> 0x3f) << 1);
  }
  if (this->frame != 0) {
    VCALL(this->frame, 0x28 /*SetSize*/)(0,0,param_1,param_2);
  }
  if (this->mark != 0) {
    SetArea__10ScrollMarkFUcffff
              (0xbf800000,0xbf800000,this->w + 2.0,
               this->h + 2.0,this->mark,
               this->mark_mask);
  }
  this->env_dirty = this->env_dirty & 0xf7 | 8;
  return;
}

// JP: 0x0026ad10  GetTargetX__10MenuWindowCFv  size 0x5c
// MenuWindow::GetTargetX() const
u32 GetTargetX__10MenuWindowCFv(MenuWindow *this)
{
  u32 uVar1;
  if ((this->scroll == 0) || (this->scroll->scrolling == 0)) {
    uVar1 = this->scroll_x;
  }
  else {
    uVar1 = this->scroll->target_x;
  }
  return uVar1;
}

// JP: 0x0026ad70  GetTargetY__10MenuWindowCFv  size 0x5c
// MenuWindow::GetTargetY() const
u32 GetTargetY__10MenuWindowCFv(MenuWindow *this)
{
  u32 uVar1;
  if ((this->scroll == 0) || (this->scroll->scrolling == 0)) {
    uVar1 = this->scroll_y;
  }
  else {
    uVar1 = this->scroll->target_y;
  }
  return uVar1;
}

// JP: 0x0026add0  SetClip__10MenuWindowFUc  size 0x108
// MenuWindow::SetClip(unsigned char)
void SetClip__10MenuWindowFUc(MenuWindow *this,u8 param_2)
{
  ulong uVar1;
  if (param_2 == 1) {
    this->clip0_y = 0;
    this->clip0_x = 0;
    this->clip0_w = (short)(int)this->w;
    this->clip0_h = (short)(int)this->h;
    this->clip_x = this->clip0_x;
    this->clip_y = this->clip0_y;
    this->clip_w = this->clip0_w;
    this->clip_h = this->clip0_h;
  }
  uVar1 = (ulong)this->wflags1 & 0xffffffffffffff9f | (long)(int)((param_2 & 3) << 5);
  this->wflags1 = (char)uVar1;
  this->wflags1 =
       this->wflags1 & 0xf9 | (u8)((uint)((uVar1 << 0x39) >> 0x3e) << 1);
  return;
}

// JP: 0x0026aee0  SetAlpha__10MenuWindowFUc  size 0x50
// MenuWindow::SetAlpha(unsigned char)
void SetAlpha__10MenuWindowFUc(MenuWindow *this,u8 param_2)
{
  if (this->frame != 0) {
    VCALL(this->frame, 0x30 /*SetColor*/)(this->frame,param_2);
  }
  return;
}

// JP: 0x0026af30  SetOffset__10MenuWindowFff  size 0xe8
// MenuWindow::SetOffset(float, float)
void SetOffset__10MenuWindowFff(u32 param_1,u32 param_2,int this)
{
  Finish__10MenuWindowFv(this);
  this->scroll_x = param_1;
  this->scroll_y = param_2;
  if (this->scroll != 0) {
    this->scroll->scrolling = 0;
    SetScrollMark__10MenuWindowFss
              (this,(int)(-this->scroll_x /
                            this->scroll->cell_w),
               (int)(-this->scroll_y / this->scroll->cell_h));
  }
  AllotPacket__10MenuWindowFv(this);
  this->env_dirty2 = this->env_dirty2 & 0xf7 | 8;
  return;
}

// JP: 0x0026b020  Polling__10MenuWindowFv  size 0x6ec
// MenuWindow::Polling()
void Polling__10MenuWindowFv(MenuWindow *this)
{
  char cVar1;
  u16 uVar2;
  ulong uVar3;
  short sVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fStack_28;
  float fStack_24;
  float fStack_20;
  float fStack_1c;
  this->anim_time = this->anim_time - sm_iPassTime__7MenuObj;
  cVar1 = this->state;
  if (cVar1 == '\a') {
    if (this->anim_time < 1) {
      Finish__10MenuWindowFv(this);
    }
    else {
      fVar5 = this->anim_da * sm_fPassTime__7MenuObj;
      if (fVar5 < 2.1474836e+09) {
        sVar4 = (short)(int)fVar5;
      }
      else {
        sVar4 = (short)(int)(fVar5 - 2.1474836e+09);
      }
      this->alpha = this->alpha + sVar4;
      this->env_dirty = this->env_dirty & 0xef | 0x10;
      this->env_dirty2 = this->env_dirty2 & 0xef | 0x10;
    }
  }
  else if (cVar1 == '\x06') {
    if (this->anim_time < 1) {
      Finish__10MenuWindowFv(this);
    }
    else {
      this->anim_a =
           this->anim_a + this->anim_da * sm_fPassTime__7MenuObj;
      this->anim_b =
           this->anim_b + this->anim_db * sm_fPassTime__7MenuObj;
      fVar5 = this->w - this->anim_a * 2.0;
      fVar6 = this->h - this->anim_b * 2.0;
      if (this->frame != 0) {
        VCALL(this->frame, 0x28 /*SetSize*/)
                  (this->anim_a,this->anim_b,fVar5,fVar6);
      }
      this->clip_x = (short)(int)this->anim_a;
      this->clip_y = (short)(int)this->anim_b;
      this->clip_w = (short)(int)fVar5;
      this->clip_h = (short)(int)fVar6;
      uVar3 = (ulong)this->dirty1 & 0xfffffffffffffffd | 2;
      this->dirty1 = (char)uVar3;
      this->dirty0 =
           this->dirty0 & 0xfd | (u8)((uint)((uVar3 << 0x3e) >> 0x3f) << 1);
      this->env_dirty = this->env_dirty & 0xf7 | 8;
    }
  }
  else if (cVar1 == '\x05') {
    if (this->anim_time < 1) {
      Finish__10MenuWindowFv(this);
    }
    else {
      SetPosition__10MenuWindowFff
                (this->x + this->anim_da * sm_fPassTime__7MenuObj,
                 this->y + this->anim_db * sm_fPassTime__7MenuObj,
                 this);
    }
  }
  if ((this->scroll != 0) && (this->scroll->scrolling != 0)) {
    fVar5 = this->scroll->max_step_x;
    fVar6 = this->scroll->max_step_y;
    uVar2 = this->scroll->mode_bits;
    fStack_1c = this->scroll->target_x - this->scroll_x;
    fStack_20 = this->scroll->target_y - this->scroll_y;
    fVar7 = fStack_1c * sm_fPassTime__7MenuObj * 0.01;
    fVar8 = fStack_20 * sm_fPassTime__7MenuObj * 0.01;
    fStack_24 = fVar7;
    if (((uVar2 & 1) != 0) &&
       ((fStack_24 = fVar5, fVar7 <= fVar5 && (fStack_24 = fVar7, fVar7 < -fVar5)))) {
      fStack_24 = -fVar5;
    }
    fStack_28 = fVar8;
    if ((((uVar2 & 2) != 0) && (fStack_28 = fVar6, fVar8 <= fVar6)) &&
       (fStack_28 = fVar8, fVar8 < -fVar6)) {
      fStack_28 = -fVar6;
    }
    this->scroll_x = this->scroll_x + fStack_24;
    this->scroll_y = this->scroll_y + fStack_28;
    if (fStack_1c < 0.0) {
      fStack_1c = -fStack_1c;
    }
    if (fStack_20 < 0.0) {
      fStack_20 = -fStack_20;
    }
    if ((1.0 <= fStack_1c) || (1.0 <= fStack_20)) {
      AllotPacket__10MenuWindowFv(this);
      this->env_dirty2 = this->env_dirty2 & 0xf7 | 8;
    }
    else {
      FinishScroll__10MenuWindowFv(this);
    }
  }
  TracePolling__12MenuObjTableFv(this + 0x18);
  if ((this->mark != 0) &&
     ((long)((ulong)*(u8 *)(this->mark + 0x12) << 0x3e) < 0)) {
    VCALL(this->mark, 0x10 /*Polling*/)();
  }
  if ((this->extra != 0) &&
     ((long)((ulong)this->extra->flags << 0x3e) < 0)) {
    VCALL(this->extra, 0x10 /*Polling*/)();
  }
  return;
}

// JP: 0x0026b710  Update__10MenuWindowFiiUs  size 0x53c
// MenuWindow::Update(int, int, unsigned short)
void Update__10MenuWindowFiiUs(MenuWindow *this,int param_2,int param_3,u16 param_4)
{
  u8 bVar1;
  int *piVar2;
  int iVar3;
  u16 uVar4;
  u8 *pbVar5;
  pbVar5 = (u8 *)(this + (m_Env__8VIF1Prim & 1) + 0x10);
  if ((*pbVar5 & 1) != 0) {
    piVar2 = *(int **)(this + (m_Env__8VIF1Prim & 1) * 4 + 0x28);
    *piVar2 = this->pktqw + 0x30000000;
    piVar2[1] = *(int *)((m_Env__8VIF1Prim & 1) * 4 + this + 0x50);
    piVar2[3] = this->pktqw + 0x50000000;
    piVar2[8] = DAT_00421a8c + 0x30000000;
    piVar2[9] = *(int *)(&DAT_00421a84 + (m_Env__8VIF1Prim & 1) * 4);
    piVar2[0xb] = DAT_00421a8c + 0x50000000;
  }
  if ((long)((ulong)*pbVar5 << 0x3e) < 0) {
    Update__7ScissorFUsii
              (this + 0x4c,m_Env__8VIF1Prim & 1,(int)this->x,
               (int)this->y);
  }
  param_2 = param_2 + (int)this->x * 0x10;
  param_3 = param_3 + (int)this->y * 0x10;
  uVar4 = (u16)((uint)param_4 * (uint)this->alpha >> 0xf);
  if ((this->frame != 0) && ((*(u8 *)(this->frame + 0x12) & 1) != 0)) {
    bVar1 = this->env_dirty2;
    iVar3 = this->frame;
    *(u8 *)(iVar3 + 0x10) = *(u8 *)(iVar3 + 0x10) | bVar1;
    *(u8 *)(iVar3 + 0x11) = *(u8 *)(iVar3 + 0x11) | bVar1;
    VCALL(this->frame, 0x14 /*Update*/)
              (this->frame,param_2,param_3,uVar4);
  }
  if ((this->mark != 0) && ((*(u8 *)(this->mark + 0x12) & 1) != 0)) {
    bVar1 = this->env_dirty2;
    iVar3 = this->mark;
    *(u8 *)(iVar3 + 0x10) = *(u8 *)(iVar3 + 0x10) | bVar1;
    *(u8 *)(iVar3 + 0x11) = *(u8 *)(iVar3 + 0x11) | bVar1;
    VCALL(this->mark, 0x14 /*Update*/)
              (this->mark,param_2,param_3,uVar4);
  }
  param_2 = param_2 + (int)this->scroll_x * 0x10;
  param_3 = param_3 + (int)this->scroll_y * 0x10;
  if ((this->extra != 0) && ((this->extra->flags & 1) != 0)) {
    bVar1 = this->env_dirty2;
    iVar3 = this->extra;
    *(u8 *)(iVar3 + 0x10) = *(u8 *)(iVar3 + 0x10) | bVar1;
    *(u8 *)(iVar3 + 0x11) = *(u8 *)(iVar3 + 0x11) | bVar1;
    VCALL(this->extra, 0x14 /*Update*/)
              (this->extra,param_2,param_3,uVar4);
  }
  for (iVar3 = this->places; iVar3 != 0; iVar3 = *(int *)(iVar3 + 0x38)) {
    if (((*(u8 *)(iVar3 + 0x12) & 1) != 0) && ((long)((ulong)*(u8 *)(iVar3 + 0x12) << 0x3d) < 0)
       ) {
      bVar1 = this->env_dirty2;
      *(u8 *)(iVar3 + 0x10) = *(u8 *)(iVar3 + 0x10) | bVar1;
      *(u8 *)(iVar3 + 0x11) = *(u8 *)(iVar3 + 0x11) | bVar1;
      VCALL(iVar3, 0x14 /*Update*/)(iVar3,param_2,param_3,uVar4);
    }
  }
  TraceUpdate__12MenuObjTableFiiUsUc
            (this + 0x18,param_2,param_3,uVar4,this->env_dirty2);
  this->env_dirty = 0;
  this->env_dirty2 = 0;
  *pbVar5 = *pbVar5 & 0x80;
  return;
}

// JP: 0x0026bc50  Connect__10MenuWindowFP4_QWD  size 0x1c4
// MenuWindow::Connect(_QWD*)
int Connect__10MenuWindowFP4_QWD(MenuWindow *this,u32 *param_2)
{
  int iVar1;
  u32 *puVar2;
  u32 *puStack_10;
  puStack_10 = param_2;
  if ((this->frame != 0) && ((*(u8 *)(this->frame + 0x12) & 1) != 0)) {
    puStack_10 = (u32 *)
                 VCALL(this->frame, 0x18 /*Connect*/)
                           (this->frame,param_2);
  }
  if (((ulong)this->wflags1 & 0x7f) >> 5 == 0) {
    puStack_10 = (u32 *)TraceConnect__12MenuObjTableFP4_QWD(this + 0x18,puStack_10);
  }
  else {
    iVar1 = *(int *)(this + (m_Env__8VIF1Prim & 1) * 4 + 0x28);
    *puStack_10 = 0x20000000;
    puStack_10[1] = iVar1;
    puVar2 = (u32 *)TraceConnect__12MenuObjTableFP4_QWD(this + 0x18,iVar1 + 0x10);
    *puVar2 = 0x20000000;
    puVar2[1] = iVar1 + 0x20;
    puStack_10 = (u32 *)(iVar1 + 0x30);
  }
  if ((this->mark != 0) && ((*(u8 *)(this->mark + 0x12) & 1) != 0)) {
    puStack_10 = (u32 *)
                 VCALL(this->mark, 0x18 /*Connect*/)
                           (this->mark,puStack_10);
  }
  if ((this->extra != 0) && ((this->extra->flags & 1) != 0)) {
    puStack_10 = (u32 *)
                 VCALL(this->extra, 0x18 /*Connect*/)
                           (this->extra,puStack_10);
  }
  return (int)puStack_10;
}

// JP: 0x0026be20  SetScrollMark__10MenuWindowFss  size 0x1cc
// MenuWindow::SetScrollMark(short, short)
void SetScrollMark__10MenuWindowFss(MenuWindow *this,short param_2,short param_3)
{
  long lVar1;
  u16 uVar2;
  uVar2 = 0;
  if (((this->mark_mask & 1) != 0) &&
     (lVar1 = GetPlace__10MenuWindowFiss(this,1,param_2,param_3), lVar1 != 0)) {
    uVar2 = 1;
  }
  if (((this->mark_mask & 2) != 0) &&
     (lVar1 = GetPlace__10MenuWindowFiss
                        (this,2,param_2,
                         param_3 + this->scroll->rows + -1), lVar1 != 0)) {
    uVar2 = uVar2 | 2;
  }
  if (((this->mark_mask & 4) != 0) &&
     (lVar1 = GetPlace__10MenuWindowFiss(this,4,param_2,param_3), lVar1 != 0)) {
    uVar2 = uVar2 | 4;
  }
  if (((this->mark_mask & 8) != 0) &&
     (lVar1 = GetPlace__10MenuWindowFiss
                        (this,8,param_2 + this->scroll->cols + -1,
                         param_3), lVar1 != 0)) {
    uVar2 = uVar2 | 8;
  }
  SetMark__10ScrollMarkFUc(this->mark,uVar2);
  this->wflags2 = this->wflags2 & 0xfc03 | uVar2 << 2;
  return;
}

// JP: 0x0026bff0  AllotPacket__10MenuWindowFv  size 0x374
// MenuWindow::AllotPacket()
void AllotPacket__10MenuWindowFv(MenuWindow *this)
{
  int iVar1;
  int iVar2;
  short sVar3;
  short sVar4;
  int iVar5;
  short sVar6;
  short sVar7;
  if ((this->scroll != 0) && (this->scroll->cell_count != 0)) {
    iVar5 = 0;
    if (this->scroll->font_draw != 0) {
      ClearImage__8FontDrawFv(this->scroll->font_draw);
    }
    sVar7 = (short)(int)(-this->scroll_x / this->scroll->cell_w);
    sVar6 = (short)(int)(-this->scroll_y / this->scroll->cell_h);
    sVar3 = sVar7 + this->scroll->cols;
    sVar4 = sVar6 + this->scroll->rows;
    if (this->scroll->scrolling == 2) {
      sVar3 = sVar3 + 1;
    }
    else if (this->scroll->scrolling == 1) {
      sVar4 = sVar4 + 1;
    }
    for (iVar1 = this->places; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x38)) {
      if ((((*(short *)(iVar1 + 0x1c) < sVar7) || (sVar3 <= *(short *)(iVar1 + 0x1c))) ||
          (*(short *)(iVar1 + 0x1e) < sVar6)) || (sVar4 <= *(short *)(iVar1 + 0x1e))) {
        if ((long)((ulong)*(u8 *)(iVar1 + 0x12) << 0x3d) < 0) {
          VCALL(iVar1, 0x50 /*Detach*/)();
          VCALL(iVar1, 0x44 /*AllotPacket*/)(iVar1,0,0);
        }
      }
      else {
        if (-1 < (long)((ulong)*(u8 *)(iVar1 + 0x12) << 0x3d)) {
          VCALL(iVar1, 0x4c /*Attach*/)(iVar1,this);
        }
        VCALL(iVar1, 0x44 /*AllotPacket*/)
                  (iVar1,this->scroll->pkt0 + iVar5 * 0x10,
                   this->scroll->pkt1 + iVar5 * 0x10);
        iVar2 = VCALL(iVar1, 0x48 /*GetAllotCount*/)();
        iVar5 = iVar5 + iVar2;
      }
    }
  }
  return;
}

// JP: 0x0026c370  ClearWork__10MenuWindowFv  size 0x104
// MenuWindow::ClearWork()
void ClearWork__10MenuWindowFv(MenuWindow *this)
{
  this->anim_db = 0;
  this->anim_da = 0;
  this->anim_b = 0;
  this->anim_a = 0;
  this->anim_time = 0;
  this->wflags1 =
       this->wflags1 & 0x9f |
       (u8)((uint)(((ulong)this->wflags1 << 0x3d) >> 0x3e) << 5);
  this->wflags2 = this->wflags2 & 0xfe;
  if ((long)((ulong)this->wflags1 << 0x38) < 0) {
    this->state = 0;
    this->wflags1 = this->wflags1 & 0x7f;
    this->flags = this->flags & 0xfe;
  }
  else {
    this->state = 1;
  }
  return;
}

// JP: 0x0026c480  Destroy__10MenuWindowFv  size 0x11c
// MenuWindow::Destroy()
void Destroy__10MenuWindowFv(MenuWindow *this)
{
  int iVar1;
  DestroyPacket__10MenuPacketFv(this + 0x24);
  if (this->frame != 0) {
    iVar1 = this->frame;
    if (iVar1 != 0) {
      VCALL(iVar1, 0x8 /*dtor*/)(iVar1,1);
    }
    this->frame = 0;
  }
  if (this->scroll != 0) {
    iVar1 = this->scroll;
    if (iVar1 != 0) {
      VCALL(iVar1, 0x8 /*dtor*/)(iVar1,1);
    }
    this->scroll = 0;
  }
  if ((-1 < (long)((ulong)this->wflags2 << 0x3e)) && (this->mark != 0)) {
    iVar1 = this->mark;
    if (iVar1 != 0) {
      VCALL(iVar1, 0x8 /*dtor*/)(iVar1,1);
    }
  }
  this->mark = 0;
  return;
}

// JP: 0x0026c660  Clear__10MenuWindowFv  size 0x140
// MenuWindow::Clear()
void * Clear__10MenuWindowFv(MenuWindow *this)
{
  void *pvVar1;
  Clear__7MenuObjFv(this);
  ClearTable__12MenuObjTableFv(this + 0x18);
  ClearPacket__10MenuPacketFv(this + 0x24);
  this->rec = 0;
  this->places = 0;
  this->frame = 0;
  this->scroll = 0;
  this->mark = 0;
  this->extra = 0;
  this->state = 0;
  this->anim_time = 0;
  this->f_ae /*u16 **/ = 0;
  this->alpha = 0x8000;
  this->anim_db = 0;
  this->anim_da = 0;
  this->anim_b = 0;
  this->anim_a = 0;
  this->scroll_y = 0;
  this->scroll_x = 0;
  this->mark_mask = 0xf;
  this->env_dirty = 0;
  this->env_dirty2 = 0;
  this->wflags0 = 0x1800;
  memset((void *)(this + 100),0,0x10);
  memset((void *)(this + 0x74),0,0x10);
  pvVar1 = memset((void *)(this + 0x84),0,8);
  return pvVar1;
}

// JP: 0x0026c7a0  @24@__dt__10MenuWindowFv  size 0x8
// @24@__dt__10MenuWindowFv
u32 * _24___dt__10MenuWindowFv(MenuWindow *this,short param_2)
{
  u32 *puVar1;
  puVar1 = this + -6;
  if (puVar1 != (u32 *)0x0) {
    this[-4] = __vt__10MenuWindow;
    *this = 0x405084;
    this[3] = 0x405090;
    (**(code **)(this[-4] + 0x1c))();
    __dt__7ScissorFv(this + 0xd,0xffffffffffffffff);
    __dt__10MenuPacketFv(this + 3,0);
    __dt__12MenuObjTableFv(this,0);
    __dt__7MenuObjFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}

// JP: 0x0026c7b0  @36@__dt__10MenuWindowFv  size 0x8
// @36@__dt__10MenuWindowFv
u32 * _36___dt__10MenuWindowFv(MenuWindow *this,short param_2)
{
  u32 *puVar1;
  puVar1 = this + -9;
  if (puVar1 != (u32 *)0x0) {
    this[-7] = __vt__10MenuWindow;
    this[-3] = 0x405084;
    *this = 0x405090;
    (**(code **)(this[-7] + 0x1c))();
    __dt__7ScissorFv(this + 10,0xffffffffffffffff);
    __dt__10MenuPacketFv(this,0);
    __dt__12MenuObjTableFv(this + -3,0);
    __dt__7MenuObjFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}
