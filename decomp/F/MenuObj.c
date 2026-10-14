/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x002744b0  Initialize__7MenuObjFv  size 0xa4
// MenuObj::Initialize()
void Initialize__7MenuObjFv(void)
{
  long lVar1;
  if (-1 < (long)((ulong)DAT_00421623 << 0x3b)) {
    OrderFile__9MenuSceneFPCcP4Menu(0x421600,0x3fe980,0);
    Create__10MenuRenderFv(0x421a30);
    Entry__10MenuRenderFi(0x421a30,0xd);
    lVar1 = __nw__FUi(0x1c);
    if (lVar1 != 0) {
      __ct__15SaveMenuSectionFv(lVar1);
    }
  }
  return;
}

// JP: 0x00274560  IsReady__7MenuObjFv  size 0x18
// MenuObj::IsReady()
ulong IsReady__7MenuObjFv(void)
{
  return ((ulong)DAT_00421623 & 0x1f) >> 4;
}

// JP: 0x00274580  UpdateTimer__7MenuObjFv  size 0x7c
// MenuObj::UpdateTimer()
void UpdateTimer__7MenuObjFv(void)
{
  int iVar1;
  iVar1 = GetTimer__7SysToolFv();
  sm_iPassTime__7MenuObj = iVar1 - sm_prevTime__7MenuObj;
  sm_fPassTime__7MenuObj = (float)(uint)(iVar1 - sm_prevTime__7MenuObj);
  sm_prevTime__7MenuObj = iVar1;
  return;
}

// JP: 0x00274600  SetBright__7MenuObjFP7_rgba32f  size 0x2d8
// MenuObj::SetBright(_rgba32*, float)
/* WARNING: Removing unreachable block (ram,0x0027472c) */
/* WARNING: Removing unreachable block (ram,0x0027464c) */
/* WARNING: Removing unreachable block (ram,0x0027480c) */
void SetBright__7MenuObjFP7_rgba32f(float param_1,u8 *param_2)
{
  u8 bVar1;
  float fVar2;
  fVar2 = (float)*param_2 * param_1;
  if (255.0 < fVar2) {
    *param_2 = 0xff;
  }
  else if (fVar2 < 0.0) {
    *param_2 = 0;
  }
  else {
    if (fVar2 < 2.1474836e+09) {
      bVar1 = (u8)(int)fVar2;
    }
    else {
      bVar1 = (u8)(int)(fVar2 - 2.1474836e+09);
    }
    *param_2 = bVar1;
  }
  fVar2 = (float)param_2[1] * param_1;
  if (255.0 < fVar2) {
    param_2[1] = 0xff;
  }
  else if (fVar2 < 0.0) {
    param_2[1] = 0;
  }
  else {
    if (fVar2 < 2.1474836e+09) {
      bVar1 = (u8)(int)fVar2;
    }
    else {
      bVar1 = (u8)(int)(fVar2 - 2.1474836e+09);
    }
    param_2[1] = bVar1;
  }
  param_1 = (float)param_2[2] * param_1;
  if (255.0 < param_1) {
    param_2[2] = 0xff;
  }
  else if (param_1 < 0.0) {
    param_2[2] = 0;
  }
  else {
    if (param_1 < 2.1474836e+09) {
      bVar1 = (u8)(int)param_1;
    }
    else {
      bVar1 = (u8)(int)(param_1 - 2.1474836e+09);
    }
    param_2[2] = bVar1;
  }
  return;
}

// JP: 0x002748e0  CreateField__7MenuObjFv  size 0x134
// MenuObj::CreateField()
void CreateField__7MenuObjFv(void)
{
  int iVar1;
  u32 uVar2;
  long lVar3;
  if (sm_pFieldData__7MenuObj == 0) {
    lVar3 = __nw__FUi(0x5c);
    iVar1 = 0;
    if (lVar3 != 0) {
      iVar1 = __ct__18MenuFieldStationedFv(lVar3);
    }
    sm_pFieldData__7MenuObj = iVar1;
    OrderFile__9MenuSceneFPCcP4Menu(sm_pFieldData__7MenuObj,*(u32 *)(DAT_00421624 + 0x10),0);
    lVar3 = __nw__FUi(0x10);
    uVar2 = 0;
    if (lVar3 != 0) {
      uVar2 = __ct__11FileManegerFPCcPCc(lVar3,0x3fe998,0x3fe9a8);
    }
    sm_pFace__7MenuObj = uVar2;
    lVar3 = __nw__FUi(0x14c);
    uVar2 = 0;
    if (lVar3 != 0) {
      uVar2 = __ct__9MenuSoundFv(lVar3);
    }
    sm_pSound__7MenuObj = uVar2;
    Entry__7CPollerFP7CPolObjib(app__4CApp + 0x48,sm_pSound__7MenuObj,0x80,0);
  }
  *(char *)(sm_pFieldData__7MenuObj + 0x22) = *(char *)(sm_pFieldData__7MenuObj + 0x22) + '\x01';
  return;
}

// JP: 0x00274a20  CreateCmdMenu__7MenuObjFv  size 0x9c
// MenuObj::CreateCmdMenu()
void CreateCmdMenu__7MenuObjFv(void)
{
  int iVar1;
  long lVar2;
  if (sm_pCmdMenu__7MenuObj == 0) {
    lVar2 = __nw__FUi(0x5c);
    iVar1 = 0;
    if (lVar2 != 0) {
      iVar1 = __ct__13MenuFieldDataFv(lVar2);
    }
    sm_pCmdMenu__7MenuObj = iVar1;
    OrderFile__9MenuSceneFPCcP4Menu(sm_pCmdMenu__7MenuObj,*(u32 *)(DAT_00421624 + 0x18),0);
  }
  *(char *)(sm_pCmdMenu__7MenuObj + 0x22) = *(char *)(sm_pCmdMenu__7MenuObj + 0x22) + '\x01';
  return;
}

// JP: 0x00274ac0  ReleaseField__7MenuObjFv  size 0xb4
// MenuObj::ReleaseField()
void ReleaseField__7MenuObjFv(void)
{
  char cVar1;
  if ((sm_pFieldData__7MenuObj != 0) &&
     (cVar1 = *(char *)(sm_pFieldData__7MenuObj + 0x22) + -1,
     *(char *)(sm_pFieldData__7MenuObj + 0x22) = cVar1, cVar1 == '\0')) {
    if (sm_pFieldData__7MenuObj != 0) {
      VCALL(sm_pFieldData__7MenuObj, 0xc /*DelayDelete*/)();
      sm_pFieldData__7MenuObj = 0;
    }
    if (sm_pFace__7MenuObj != 0) {
      __dt__11FileManegerFv(sm_pFace__7MenuObj,1);
      sm_pFace__7MenuObj = 0;
    }
    if (sm_pSound__7MenuObj != 0) {
      SelfDelete__9MenuSoundFv(sm_pSound__7MenuObj);
      sm_pSound__7MenuObj = 0;
    }
  }
  return;
}

// JP: 0x00274b80  ReleaseCmdMenu__7MenuObjFv  size 0x64
// MenuObj::ReleaseCmdMenu()
void ReleaseCmdMenu__7MenuObjFv(void)
{
  char cVar1;
  if ((sm_pCmdMenu__7MenuObj != 0) &&
     (cVar1 = *(char *)(sm_pCmdMenu__7MenuObj + 0x22) + -1,
     *(char *)(sm_pCmdMenu__7MenuObj + 0x22) = cVar1, cVar1 == '\0')) {
    VCALL(sm_pCmdMenu__7MenuObj, 0xc /*DelayDelete*/)();
    sm_pCmdMenu__7MenuObj = 0;
  }
  return;
}

// JP: 0x00274bf0  IsReadyField__7MenuObjFv  size 0x48
// MenuObj::IsReadyField()
ulong IsReadyField__7MenuObjFv(void)
{
  ulong uVar1;
  if (sm_pFieldData__7MenuObj == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = ((ulong)*(u8 *)(sm_pFieldData__7MenuObj + 0x23) & 0x1f) >> 4;
  }
  return uVar1;
}

// JP: 0x00274c40  __ct__7MenuObjFv  size 0x48
// MenuObj::MenuObj()
u32 * __ct__7MenuObjFv(MenuObj *this)
{
  *this = 0;
  this[1] = 0;
  this[2] = __vt__17DelayDeleteObject;
  this[2] = __vt__7MenuObj;
  return this;
}

// JP: 0x00274c90  __dt__7MenuObjFv  size 0x84
// MenuObj::~MenuObj()
int __dt__7MenuObjFv(MenuObj *this,short param_2)
{
  if (this != 0) {
    this->vptr = __vt__7MenuObj;
    if (this != 0) {
      this->vptr = __vt__17DelayDeleteObject;
    }
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}

// JP: 0x00274d20  AddOT__7MenuObjFv  size 0x30
// MenuObj::AddOT()
void AddOT__7MenuObjFv(u32 param_1)
{
  AddPriority__12MenuObjTableFP7MenuObj(0x421a5c,param_1);
  return;
}

// JP: 0x00274d50  ReleaseOT__7MenuObjFv  size 0x30
// MenuObj::ReleaseOT()
void ReleaseOT__7MenuObjFv(u32 param_1)
{
  RemoveObj__12MenuObjTableFP7MenuObj(0x421a5c,param_1);
  return;
}

// JP: 0x00274d80  Release__7MenuObjFv  size 0x94
// MenuObj::Release()
void Release__7MenuObjFv(MenuObj *this)
{
  if ((long)((ulong)this->flags << 0x3c) < 0) {
    if (this != 0) {
      VCALL(this, 0x8 /*dtor*/)(this,1);
    }
  }
  else {
    VCALL(this, 0x1c /*Destroy*/)();
    VCALL(this, 0x20 /*Clear*/)();
  }
  return;
}

// JP: 0x00274e20  Polling__7MenuObjFv  size 0x10
// MenuObj::Polling()
void Polling__7MenuObjFv(void)
{
  return;
}

// JP: 0x00274e30  Update__7MenuObjFiiUs  size 0x10
// MenuObj::Update(int, int, unsigned short)
void Update__7MenuObjFiiUs(void)
{
  return;
}

// JP: 0x00274e40  Connect__7MenuObjFP4_QWD  size 0x18
// MenuObj::Connect(_QWD*)
u32 Connect__7MenuObjFP4_QWD(MenuObj *this,u32 param_2)
{
  return param_2;
}

// JP: 0x00274e60  Destroy__7MenuObjFv  size 0x10
// MenuObj::Destroy()
void Destroy__7MenuObjFv(void)
{
  return;
}

// JP: 0x00274e70  Clear__7MenuObjFv  size 0x4c
// MenuObj::Clear()
void Clear__7MenuObjFv(MenuObj *this)
{
  this->next = 0;
  this->id = 0xffff;
  this->priority = 0;
  this->dirty0 = 0;
  this->dirty1 = 0;
  this->flags = 3;
  return;
}

// JP: 0x00371720  UpdateRgba__7MenuObjFv  size 0x60
// MenuObj::UpdateRgba()
void UpdateRgba__7MenuObjFv(MenuObj *this)
{
  ulong uVar1;
  uVar1 = (ulong)this->dirty1 & 0xffffffffffffffef | 0x10;
  this->dirty1 = (char)uVar1;
  this->dirty0 =
       this->dirty0 & 0xef | (u8)((uint)((uVar1 << 0x3b) >> 0x3f) << 4);
  return;
}

// JP: 0x00371780  UpdateEnv__7MenuObjFv  size 0x60
// MenuObj::UpdateEnv()
void UpdateEnv__7MenuObjFv(MenuObj *this)
{
  ulong uVar1;
  uVar1 = (ulong)this->dirty1 & 0xfffffffffffffffd | 2;
  this->dirty1 = (char)uVar1;
  this->dirty0 =
       this->dirty0 & 0xfd | (u8)((uint)((uVar1 << 0x3e) >> 0x3f) << 1);
  return;
}
