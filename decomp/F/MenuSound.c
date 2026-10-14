/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x0028eb40  ReadComplete__9MenuSoundFiP9BufMemoryiPcPv  size 0x38
// MenuSound::ReadComplete(int, BufMemory*, int, char*, void*)
void ReadComplete__9MenuSoundFiP9BufMemoryiPcPv
               (MenuSound *this,u32 param_2,u64 param_3,u64 param_4,
               u32 param_5)
{
  ReadSDH__9MenuSoundFP9BufMemoryi(param_5,param_2,this);
  return;
}

// JP: 0x0028eb80  __ct__9MenuSoundFv  size 0x190
// MenuSound::MenuSound()
int __ct__9MenuSoundFv(MenuSound *this)
{
  char cVar1;
  char *pcVar2;
  __ct__7CPolObjFv(this);
  this->f_14 /*u8 **/ = __vt__9MenuSound;
  this->f_148 /*u16 **/ = 0;
  this->f_14a /*u16 **/ = 0;
  memset((void *)(this + 0x68),0,0xa0);
  memset((void *)(this + 0x108),0,0x40);
  memset((void *)(this + 0x18),0,0x50);
  pcVar2 = (char *)(this + 0x68);
  for (cVar1 = '\0'; cVar1 < '\b'; cVar1 = cVar1 + '\x01') {
    *pcVar2 = cVar1;
    pcVar2[4] = -1;
    pcVar2[5] = -1;
    pcVar2[6] = -1;
    pcVar2[7] = -1;
    pcVar2 = pcVar2 + 0x14;
  }
  pcVar2 = (char *)(this + 0x108);
  for (cVar1 = '\0'; cVar1 < '\x02'; cVar1 = cVar1 + '\x01') {
    *pcVar2 = cVar1;
    pcVar2[4] = -1;
    pcVar2[5] = -1;
    pcVar2[6] = -1;
    pcVar2[7] = -1;
    pcVar2 = pcVar2 + 0x20;
  }
  pcVar2 = (char *)(this + 0x18);
  for (cVar1 = '\0'; cVar1 < '\x04'; cVar1 = cVar1 + '\x01') {
    *pcVar2 = cVar1;
    pcVar2[8] = -1;
    pcVar2[9] = -1;
    pcVar2[10] = -1;
    pcVar2[0xb] = -1;
    pcVar2 = pcVar2 + 0x14;
  }
  return this;
}

// JP: 0x0028ed10  __dt__9MenuSoundFv  size 0x74
// MenuSound::~MenuSound()
int __dt__9MenuSoundFv(MenuSound *this,short param_2)
{
  if (this != 0) {
    this->f_14 /*u8 **/ = __vt__9MenuSound;
    __dt__7CPolObjFv(this,0);
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}

// JP: 0x0028ed90  ReadSDH__9MenuSoundFP9BufMemoryi  size 0x78
// MenuSound::ReadSDH(BufMemory*, int)
bool ReadSDH__9MenuSoundFP9BufMemoryi(MenuSound *this,u32 param_2,int param_3)
{
  bool bVar1;
  this = this + param_3 * 0x14;
  bVar1 = this->f_28 /*int **/ == 0;
  if (bVar1) {
    this->f_1c /*u32 **/ = param_2;
    this->f_19 /*u8 **/ = 3;
    this->f_1a /*u8 **/ = 0;
  }
  else {
    this->f_20 /*u32 **/ = 0xffffffff;
  }
  return !bVar1;
}

// JP: 0x0028ee10  FindSDH__9MenuSoundFUi  size 0x74
// MenuSound::FindSDH(unsigned int)
uint FindSDH__9MenuSoundFUi(MenuSound *this,int param_2)
{
  uint uVar1;
  uVar1 = this + 0x18;
  while( true ) {
    if (this + 0x68U <= uVar1) {
      return 0;
    }
    if (*(int *)(uVar1 + 8) == param_2) break;
    uVar1 = uVar1 + 0x14;
  }
  return uVar1;
}

// JP: 0x0028ee90  GetSDH__9MenuSoundFPCc  size 0xb8
// MenuSound::GetSDH(const char*)
u8 GetSDH__9MenuSoundFPCc(MenuSound *this,u32 param_2)
{
  u8 uVar1;
  long lVar2;
  u8 *puVar3;
  char acStack_60 [64];
  u32 uStack_20;
  u32 uStack_10;
  uStack_20 = this;
  uStack_10 = param_2;
  lVar2 = FindSDH__9MenuSoundFUi(this,0xffffffffffffffff);
  if (lVar2 == 0) {
    uVar1 = 0xff;
  }
  else {
    sprintf(acStack_60,(char *)&_1464,pDataPath__7SysTool,uStack_10);
    puVar3 = (u8 *)lVar2;
    ReadOrder__11DvdromOrderFPCcPFiP9BufMemoryiPcPv_iiPvi
              (Dvdromour__11DvdromOrder,acStack_60,0x28eb40,*puVar3,uStack_20,0);
    puVar3[1] = 2;
    puVar3[2] = 0;
    *(u32 *)(puVar3 + 8) = 0;
    uVar1 = *puVar3;
  }
  return uVar1;
}

// JP: 0x0028ef50  ReleaseSDH__9MenuSoundFc  size 0x84
// MenuSound::ReleaseSDH(char)
void ReleaseSDH__9MenuSoundFc(MenuSound *this,char param_2)
{
  long lVar1;
  this = this + param_2 * 0x14;
  if (this->f_1b /*char **/ != '\0') {
    lVar1 = ReleaseSDH__4SdrvFUi(sys__4Sdrv,this->f_20 /*u32 **/);
    this->f_24 /*int **/ = (int)lVar1;
    if (lVar1 != -1) {
      this->f_20 /*u32 **/ = 0xffffffff;
      this->f_1b /*u8 **/ = 0;
    }
  }
  return;
}

// JP: 0x0028efe0  PlaySE__9MenuSoundFUiUcP8_SeParam  size 0x84
// MenuSound::PlaySE(unsigned int, unsigned char, _SeParam*)
u8
PlaySE__9MenuSoundFUiUcP8_SeParam
          (MenuSound *this,u32 param_2,u8 param_3,u32 param_4)
{
  u8 uVar1;
  long lVar2;
  u8 *puVar3;
  lVar2 = FindSE__9MenuSoundFUi(this,0xffffffffffffffff);
  if (lVar2 == 0) {
    uVar1 = 0xff;
  }
  else {
    puVar3 = (u8 *)lVar2;
    *(u32 *)(puVar3 + 0x10) = param_4;
    puVar3[1] = 1;
    puVar3[2] = 0;
    puVar3[3] = param_3;
    *(u32 *)(puVar3 + 4) = param_2;
    uVar1 = *puVar3;
  }
  return uVar1;
}

// JP: 0x0028f070  StopSE__9MenuSoundFc  size 0x50
// MenuSound::StopSE(char)
void StopSE__9MenuSoundFc(MenuSound *this,char param_2)
{
  this = this + param_2 * 0x14;
  this->f_69 /*u8 **/ = 3;
  this->f_6a /*u8 **/ = 0;
  return;
}

// JP: 0x0028f0c0  FindSE__9MenuSoundFUi  size 0x74
// MenuSound::FindSE(unsigned int)
uint FindSE__9MenuSoundFUi(MenuSound *this,int param_2)
{
  uint uVar1;
  uVar1 = this + 0x68;
  while( true ) {
    if (this + 0x108U <= uVar1) {
      return 0;
    }
    if (*(int *)(uVar1 + 4) == param_2) break;
    uVar1 = uVar1 + 0x14;
  }
  return uVar1;
}

// JP: 0x0028f140  IsDelete__9MenuSoundFv  size 0xcc
// MenuSound::IsDelete()
u32 IsDelete__9MenuSoundFv(MenuSound *this)
{
  uint uVar1;
  for (uVar1 = this + 0x68; uVar1 < this + 0x108U; uVar1 = uVar1 + 0x14) {
    if (*(int *)(uVar1 + 4) != -1) {
      return 0;
    }
  }
  uVar1 = this + 0x18;
  while( true ) {
    if (this + 0x68U <= uVar1) {
      return 1;
    }
    if (*(int *)(uVar1 + 8) != -1) break;
    uVar1 = uVar1 + 0x14;
  }
  return 0;
}

// JP: 0x0028f210  SelfDelete__9MenuSoundFv  size 0x9c
// MenuSound::SelfDelete()
void SelfDelete__9MenuSoundFv(MenuSound *this)
{
  u8 *puVar1;
  for (puVar1 = (u8 *)(this + 0x18); puVar1 < (u8 *)(this + 0x68);
      puVar1 = puVar1 + 0x14) {
    *(u32 *)(puVar1 + 0x10) = 1;
    if (puVar1[1] == '\x01') {
      ReleaseSDH__9MenuSoundFc(this,*puVar1);
    }
  }
  this->f_148 /*u16 **/ = 1;
  this->f_14a /*u16 **/ = 1;
  return;
}

// JP: 0x0028f2b0  Polling__9MenuSoundFv  size 0x514
// MenuSound::Polling()
u32 Polling__9MenuSoundFv(MenuSound *this)
{
  char cVar1;
  u32 uVar2;
  long lVar3;
  uint uVar4;
  short sVar5;
  short sVar6;
  uint uVar7;
  u8 auStack_20 [16];
  int iStack_10;
  sVar6 = 0;
  uVar4 = this + 0x68;
  iStack_10 = this;
  do {
    if (this + 0x108U <= uVar4) {
      sVar5 = 0;
      uVar7 = iStack_10 + 0x68;
      for (uVar4 = iStack_10 + 0x18; uVar4 < uVar7; uVar4 = uVar4 + 0x14) {
        if (*(int *)(uVar4 + 8) == -1) {
          sVar5 = sVar5 + 1;
        }
        else if (*(char *)(uVar4 + 1) == '\x03') {
          if (*(char *)(uVar4 + 2) == '\x01') {
            lVar3 = GetStatus__4SdrvFUi(sys__4Sdrv,*(u32 *)(uVar4 + 0xc));
            if (lVar3 == 3) {
              uVar2 = GetOption__4SdrvFUi(sys__4Sdrv,*(u32 *)(uVar4 + 0xc));
              *(u32 *)(uVar4 + 8) = uVar2;
              CloseHandle__4SdrvFUi(sys__4Sdrv,*(u32 *)(uVar4 + 0xc));
              if (*(int *)(uVar4 + 4) != 0) {
                __dt__9BufMemoryFv(*(u32 *)(uVar4 + 4),1);
                *(u32 *)(uVar4 + 4) = 0;
              }
              *(u8 *)(uVar4 + 1) = 1;
              *(u8 *)(uVar4 + 2) = 0;
              *(u8 *)(uVar4 + 3) = 1;
            }
            else if (lVar3 == -2) {
              CloseHandle__4SdrvFUi(sys__4Sdrv,*(u32 *)(uVar4 + 0xc));
              if (*(int *)(uVar4 + 4) != 0) {
                __dt__9BufMemoryFv(*(u32 *)(uVar4 + 4),1);
                *(u32 *)(uVar4 + 4) = 0;
              }
              *(u32 *)(uVar4 + 8) = 0xffffffff;
              *(u8 *)(uVar4 + 1) = 0;
              *(u8 *)(uVar4 + 2) = 0;
            }
          }
          else if (*(char *)(uVar4 + 2) == '\0') {
            lVar3 = AutoLoad__4SdrvFPvPv(sys__4Sdrv,*(u32 *)(*(int *)(uVar4 + 4) + 4),0);
            *(int *)(uVar4 + 0xc) = (int)lVar3;
            if (lVar3 != -1) {
              *(char *)(uVar4 + 2) = *(char *)(uVar4 + 2) + '\x01';
            }
          }
        }
      }
      if (((*(short *)(iStack_10 + 0x148) == 0) || (sVar6 != 8)) || (sVar5 != 4)) {
        uVar2 = 0;
      }
      else {
        *(u8 *)(iStack_10 + 0xc) = 1;
        *(u8 *)(iStack_10 + 0xe) = 0;
        uVar2 = 1;
      }
      return uVar2;
    }
    if (*(int *)(uVar4 + 4) == -1) {
      sVar6 = sVar6 + 1;
    }
    else if (*(char *)(uVar4 + 1) == '\x03') {
      if (*(char *)(uVar4 + 2) == '\x01') {
        lVar3 = GetStatus__4SdrvFUi(sys__4Sdrv,*(u32 *)(uVar4 + 8));
        if (lVar3 != 3) {
          if (lVar3 != -2) goto LAB_0028f558;
          *(u8 *)(uVar4 + 3) = 1;
        }
        CloseHandle__4SdrvFUi(sys__4Sdrv,*(u32 *)(uVar4 + 8));
        *(u32 *)(uVar4 + 4) = 0xffffffff;
        *(u8 *)(uVar4 + 3) = 0;
      }
      else if (*(char *)(uVar4 + 2) == '\0') {
        lVar3 = ReleaseSE__4SdrvFUii(sys__4Sdrv,*(u32 *)(uVar4 + 0xc),1);
        *(int *)(uVar4 + 8) = (int)lVar3;
        if (lVar3 != -1) {
          *(char *)(uVar4 + 2) = *(char *)(uVar4 + 2) + '\x01';
        }
      }
    }
    else if (*(char *)(uVar4 + 1) == '\x01') {
      cVar1 = *(char *)(uVar4 + 2);
      if (cVar1 == '\x02') {
        if ((*(u8 *)(uVar4 + 3) & 1) != 0) {
          *(u8 *)(uVar4 + 3) = *(u8 *)(uVar4 + 3) & 0xfe;
          *(u32 *)(uVar4 + 4) = 0xffffffff;
        }
      }
      else if (cVar1 == '\x01') {
        lVar3 = GetStatus__4SdrvFUi(sys__4Sdrv,*(u32 *)(uVar4 + 8));
        if (lVar3 != 3) {
          if (lVar3 != -2) goto LAB_0028f558;
          *(u8 *)(uVar4 + 3) = 1;
        }
        uVar2 = GetOption__4SdrvFUi(sys__4Sdrv,*(u32 *)(uVar4 + 8));
        *(u32 *)(uVar4 + 0xc) = uVar2;
        CloseHandle__4SdrvFUi(sys__4Sdrv,*(u32 *)(uVar4 + 8));
        *(char *)(uVar4 + 2) = *(char *)(uVar4 + 2) + '\x01';
      }
      else if (cVar1 == '\0') {
        if (*(int *)(uVar4 + 0x10) == 0) {
          InitSeParam__4SdrvFP8_SeParamiPv(sys__4Sdrv,auStack_20,9,uVar4 + 3);
        }
        else {
          memcpy(auStack_20,*(void **)(uVar4 + 0x10),0xc);
        }
        lVar3 = PlaySE__4SdrvFUiP8_SeParam(sys__4Sdrv,*(u32 *)(uVar4 + 4),auStack_20);
        *(int *)(uVar4 + 8) = (int)lVar3;
        if (lVar3 != -1) {
          *(char *)(uVar4 + 2) = *(char *)(uVar4 + 2) + '\x01';
        }
      }
    }
LAB_0028f558:
    uVar4 = uVar4 + 0x14;
  } while( true );
}
