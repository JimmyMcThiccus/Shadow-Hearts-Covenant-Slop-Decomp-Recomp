/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x0032a700  __ct__10SystemFileFv  size 0xc
// SystemFile::SystemFile()
u64 __ct__10SystemFileFv(SystemFile *this)
{
  *(u32 *)this = 0;
  return this;
}

// JP: 0x0032a710  __dt__10SystemFileFv  size 0x68
// SystemFile::~SystemFile()
long __dt__10SystemFileFv(SystemFile *this,short param_2)
{
  if (this != 0) {
    if (*(int *)this != 0) {
      __dla__FPv();
      *(int *)this = 0;
    }
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}

// JP: 0x0032a780  Create__10SystemFileFi  size 0x170
// SystemFile::Create(int)
void * Create__10SystemFileFi(SystemFile *this)
{
  int iVar1;
  void *pvVar2;
  u8 *puVar3;
  u8 *puVar4;
  u8 *puVar5;
  iVar1 = __nwa__FUi(0x6c0);
  *this = iVar1;
  memset((void *)*this,0,0x6c0);
  pvVar2 = memcpy((void *)(*this + 4),&id__10SystemFile,4);
  *(u16 *)(*this + 0xe) = 0x20;
  *(uint *)(*this + 8) = 0x6c0 - (uint)*(u16 *)(*this + 0xe);
  *(u16 *)(*this + 0x10) = 0x100;
  *(u16 *)(*this + 0x12) = 0;
  *(u32 *)(*this + 0x14) = 0x20;
  *(u16 *)(*this + 0x18) = 0x60;
  *(u16 *)(*this + 0x1a) = 0;
  *(u32 *)(*this + 0x1c) = 0x120;
  *(u8 *)(*this + 0xd) = 0xf;
  puVar5 = (u8 *)(*this + *(int *)(*this + 0x1c));
  puVar4 = puVar5 + 0x5a0;
  if (puVar5 < puVar4) {
    puVar3 = puVar5 + 0x2a0;
    if (8 < (int)(puVar4 + (0x5f - (int)puVar5)) / 0x60) {
      do {
        *puVar5 = 0xff;
        puVar5[0x60] = 0xff;
        puVar5[0xc0] = 0xff;
        puVar5[0x120] = 0xff;
        puVar5[0x180] = 0xff;
        puVar5[0x1e0] = 0xff;
        puVar5[0x240] = 0xff;
        puVar5[0x2a0] = 0xff;
        puVar5 = puVar5 + 0x300;
      } while (puVar5 < puVar3);
    }
    for (; puVar5 < puVar4; puVar5 = puVar5 + 0x60) {
      *puVar5 = 0xff;
    }
  }
  return pvVar2;
}

// JP: 0x0032a8f0  Release__10SystemFileFv  size 0x38
// SystemFile::Release()
void Release__10SystemFileFv(SystemFile *this)
{
  if (*this != 0) {
    __dla__FPv();
    *this = 0;
  }
  return;
}

// JP: 0x0032a930  SetData__10SystemFileFP14_SystemFileHdr  size 0xbc
// SystemFile::SetData(_SystemFileHdr*)
u32 SetData__10SystemFileFP14_SystemFileHdr(SystemFile *this,u64 param_2)
{
  int iVar1;
  u32 uVar2;
  long lVar3;
  void *__src;
  __src = (void *)param_2;
  iVar1 = memcmp((void *)(*this + 4),(void *)((int)__src + 4),4);
  if ((iVar1 == 0) &&
     (lVar3 = CheckCRC__8SaveDataFPUcUi(param_2,*(u32 *)((int)__src + 8)), lVar3 != 0)) {
    memcpy((void *)(*this + *(int *)(*this + 0x14)),
           (void *)((int)__src + *(int *)((int)__src + 0x14)),(ulong)*(u16 *)((int)__src + 0x10))
    ;
    memcpy((void *)(*this + *(int *)(*this + 0x1c)),
           (void *)((int)__src + *(int *)((int)__src + 0x1c)),
           (long)(int)((uint)*(u16 *)((int)__src + 0x18) * (uint)*(u8 *)((int)__src + 0xd)));
    memcpy((void *)*this,__src,(ulong)*(u16 *)((int)__src + 0xe));
    uVar2 = 1;
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

// JP: 0x0032a9f0  GetHeap__10SystemFileCFv  size 0x38
// SystemFile::GetHeap() const
int GetHeap__10SystemFileCFv(SystemFile *this)
{
  int iVar1;
  iVar1 = *this;
  SetCRC__8SaveDataFPUcUi(iVar1,*(int *)(iVar1 + 8) + (uint)*(u16 *)(iVar1 + 0xe));
  return *this;
}

// JP: 0x0032aa30  StoreCommon__10SystemFileFv  size 0x18
// SystemFile::StoreCommon()
void * StoreCommon__10SystemFileFv(SystemFile *this)
{
  void *pvVar1;
  pvVar1 = memcpy((void *)(*this + *(int *)(*this + 0x14)),(void *)0x100000,0x100);
  return pvVar1;
}

// JP: 0x0032aa50  FlushCommon__10SystemFileFv  size 0x18
// SystemFile::FlushCommon()
void * FlushCommon__10SystemFileFv(SystemFile *this)
{
  void *pvVar1;
  pvVar1 = memcpy((void *)0x100000,(void *)(*this + *(int *)(*this + 0x14)),0x100);
  return pvVar1;
}

// JP: 0x0032aa70  SetCurrentSlot__10SystemFileFv  size 0x68
// SystemFile::SetCurrentSlot()
void SetCurrentSlot__10SystemFileFv(SystemFile *this)
{
  int iVar1;
  uint uVar2;
  iVar1 = *this;
  uVar2 = 0;
  if (*(u8 *)(iVar1 + 0xd) != 0) {
    do {
      if (*(char *)(iVar1 + *(int *)(iVar1 + 0x1c) + uVar2 * 0x60) != -1) {
        *(char *)(iVar1 + 0xc) = (char)uVar2;
        return;
      }
      uVar2 = uVar2 + 1 & 0xff;
    } while (uVar2 < *(u8 *)(iVar1 + 0xd));
  }
  return;
}
