/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x002890e0  SceneInit__15SaveMenuSectionFi  size 0x1b0
// SaveMenuSection::SceneInit(int)
void SceneInit__15SaveMenuSectionFi(SaveMenuSection *this)
{
  int iVar1;
  memset((void *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x180),0,0xa0);
  iVar1 = *(int *)(sm_pSubstance__15SaveMenuSection + 0xc);
  *(u16 *)(iVar1 + 0x2ac) = 0xffff;
  *(u16 *)(iVar1 + 0x2ae) = 0xffff;
  *(u16 *)(iVar1 + 0x2b0) = 0xffff;
  memset((void *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x220),0,0x4c);
  memset((void *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 700),0,0x10);
  memset((void *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x2cc),0,0x10);
  if (this == 0) {
    FieldNpcLibrary__Fii(5,0);
  }
  else {
    FieldNpcLibrary__Fii(5,1);
  }
  *(u32 *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x2fc) = 0;
  iVar1 = *(int *)(sm_pSubstance__15SaveMenuSection + 0xc);
  *(u8 *)(iVar1 + 0x275) = *(u8 *)(iVar1 + 0x275) & 0xcf | 0x10;
  *(u8 *)(iVar1 + 0x276) = *(u8 *)(iVar1 + 0x276) & 0xfc;
  return;
}

// JP: 0x00289290  Update__15SaveMenuSectionFv  size 0xb4
// SaveMenuSection::Update()
/* WARNING: Removing unreachable block (ram,0x002892c8) */
void Update__15SaveMenuSectionFv(void)
{
  SetBright__4CAppFf((float)*(u8 *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x278) *
                     0.03 + 0.7,app__4CApp);
  UpdateSoundOut__15SaveMenuSectionFv();
  UpdatePad__15SaveMenuSectionFv();
  UpdateVibration__15SaveMenuSectionFv();
  return;
}

// JP: 0x00289350  UpdateSoundOut__15SaveMenuSectionFv  size 0xb0
// SaveMenuSection::UpdateSoundOut()
void UpdateSoundOut__15SaveMenuSectionFv(void)
{
  ulong uVar1;
  u64 unaff_s0;
  if (sys__4Sdrv != 0) {
    uVar1 = ((ulong)*(u8 *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x274) & 0xf) >> 2;
    if (uVar1 == 2) {
      unaff_s0 = 0x1002;
    }
    else if (uVar1 == 1) {
      unaff_s0 = 0x1000;
    }
    else if (uVar1 == 0) {
      unaff_s0 = 0x1001;
    }
    SetMode__4SdrvFi(sys__4Sdrv,unaff_s0);
  }
  return;
}

// JP: 0x00289400  UpdatePad__15SaveMenuSectionFv  size 0xa8
// SaveMenuSection::UpdatePad()
void UpdatePad__15SaveMenuSectionFv(void)
{
  int iVar1;
  int iVar2;
  u16 auStack_20 [12];
  u16 auStack_8 [4];
  iVar1 = *(int *)(sm_pSubstance__15SaveMenuSection + 0xc);
  GetAssign__4CPadFiPUs(0,auStack_20);
  for (iVar2 = 0xc; iVar2 < 0x10; iVar2 = iVar2 + 1) {
    auStack_20[iVar2] = (short)(1 << (*(u16 *)(iVar1 + 0x26c + (iVar2 + -0xc) * 2) & 0x1f));
  }
  SetAssign__4CPadFiPCUs(0,auStack_20);
  return;
}

// JP: 0x002894b0  UpdateVibration__15SaveMenuSectionFv  size 0x4c
// SaveMenuSection::UpdateVibration()
void UpdateVibration__15SaveMenuSectionFv(void)
{
  if (sys__8CVibeMan != 0) {
    SetMode__8CVibeManFi
              (sys__8CVibeMan,
               *(u8 *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x274) & 3);
  }
  return;
}

// JP: 0x00289500  SetDefaultButton__15SaveMenuSectionFv  size 0x50
// SaveMenuSection::SetDefaultButton()
void SetDefaultButton__15SaveMenuSectionFv(void)
{
  int iVar1;
  iVar1 = *(int *)(sm_pSubstance__15SaveMenuSection + 0xc);
  *(u16 *)(iVar1 + 0x26c) = 0xc;
  *(u16 *)(iVar1 + 0x26e) = 0xd;
  *(u16 *)(iVar1 + 0x270) = 0xe;
  *(u16 *)(iVar1 + 0x272) = 0xf;
  return;
}

// JP: 0x00289550  SetCurrentCash__15SaveMenuSectionFi  size 0x80
// SaveMenuSection::SetCurrentCash(int)
void SetCurrentCash__15SaveMenuSectionFi(SaveMenuSection *this)
{
  int *piVar1;
  piVar1 = (int *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) +
                   (uint)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + 2) * 4 + 4);
  *piVar1 = this;
  if (99999999 < *piVar1) {
    *piVar1 = 99999999;
  }
  return;
}

// JP: 0x002895d0  ChengePartySet__15SaveMenuSectionFi  size 0xec
// SaveMenuSection::ChengePartySet(int)
int ChengePartySet__15SaveMenuSectionFi(SaveMenuSection *this)
{
  char cVar1;
  char *pcVar2;
  pcVar2 = (char *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x80);
  if (*(char *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x81) == '\0') {
    cVar1 = *pcVar2;
    do {
      cVar1 = cVar1 + this;
      if (cVar1 < '\x03') {
        if (cVar1 < '\0') {
          cVar1 = '\x02';
        }
      }
      else {
        cVar1 = '\0';
      }
    } while (pcVar2[cVar1 * 0x20 + 0x15] == '\0');
    *pcVar2 = cVar1;
  }
  return *(int *)(sm_pSubstance__15SaveMenuSection + 0xc) +
         *(char *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x80) * 0x20 + 0x84;
}

// JP: 0x002896c0  JoinParty__15SaveMenuSectionFcc  size 0x178
// SaveMenuSection::JoinParty(char, char)
u32 JoinParty__15SaveMenuSectionFcc(SaveMenuSection *this,char param_2)
{
  int iVar1;
  long lVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  if (param_2 < '\0') {
    uVar5 = *(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0xe4;
    for (uVar3 = *(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x84; uVar3 < uVar5;
        uVar3 = uVar3 + 0x20) {
      if (('\a' < *(char *)(uVar3 + 0xf)) ||
         (lVar2 = FindPC__15SaveMenuSectionFcP16SaveMenuPartySet(this,uVar3), lVar2 != 0)) {
        return 0;
      }
    }
    for (uVar3 = *(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x84; uVar3 < uVar5;
        uVar3 = uVar3 + 0x20) {
      JoinParty__15SaveMenuSectionFcP16SaveMenuPartySet(this,uVar3);
    }
  }
  else {
    iVar1 = *(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + param_2 * 0x20;
    iVar4 = iVar1 + 0x84;
    if (('\a' < *(char *)(iVar1 + 0x93)) ||
       (lVar2 = FindPC__15SaveMenuSectionFcP16SaveMenuPartySet(this,iVar4), lVar2 != 0)) {
      return 0;
    }
    JoinParty__15SaveMenuSectionFcP16SaveMenuPartySet(this,iVar4);
  }
  return 1;
}

// JP: 0x00289840  LeaveParty__15SaveMenuSectionFcc  size 0x148
// SaveMenuSection::LeaveParty(char, char)
u32 LeaveParty__15SaveMenuSectionFcc(SaveMenuSection *this,char param_2)
{
  long lVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  if (param_2 < '\0') {
    uVar4 = *(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0xe4;
    for (uVar2 = *(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x84; uVar2 < uVar4;
        uVar2 = uVar2 + 0x20) {
      lVar1 = FindPC__15SaveMenuSectionFcP16SaveMenuPartySet(this,uVar2);
      if (lVar1 == 0) {
        return 0;
      }
    }
    for (uVar2 = *(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x84; uVar2 < uVar4;
        uVar2 = uVar2 + 0x20) {
      LeaveParty__15SaveMenuSectionFcP16SaveMenuPartySet(this,uVar2);
    }
  }
  else {
    iVar3 = *(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + param_2 * 0x20 + 0x84;
    lVar1 = FindPC__15SaveMenuSectionFcP16SaveMenuPartySet(this,iVar3);
    if (lVar1 == 0) {
      return 0;
    }
    LeaveParty__15SaveMenuSectionFcP16SaveMenuPartySet(this,iVar3);
  }
  return 1;
}

// JP: 0x00289990  SetBattleCount__15SaveMenuSectionFcc  size 0x78
// SaveMenuSection::SetBattleCount(char, char)
void SetBattleCount__15SaveMenuSectionFcc(SaveMenuSection *this,char param_2)
{
  int iVar1;
  iVar1 = *(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + param_2 * 0x20;
  *(u8 *)(iVar1 + 0x94) = this;
  if (*(char *)(iVar1 + 0x94) < *(char *)(iVar1 + 0x95)) {
    *(u8 *)(iVar1 + 0x95) = *(u8 *)(iVar1 + 0x94);
  }
  return;
}

// JP: 0x00289a10  ClearBattleTeam__15SaveMenuSectionFc  size 0x44
// SaveMenuSection::ClearBattleTeam(char)
void ClearBattleTeam__15SaveMenuSectionFc(SaveMenuSection *this)
{
  int iVar1;
  iVar1 = *(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + this * 0x20;
  *(u8 *)(iVar1 + 0x95) = 0;
  *(u16 *)(iVar1 + 0x9e) = 0;
  return;
}

// JP: 0x00289a60  JoinBattle__15SaveMenuSectionFccUc  size 0x17c
// SaveMenuSection::JoinBattle(char, char, unsigned char)
u32 JoinBattle__15SaveMenuSectionFccUc(SaveMenuSection *this,char param_2,char param_3)
{
  int iVar1;
  int iVar2;
  int iVar3;
  long lVar4;
  iVar1 = *(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + param_2 * 0x20;
  iVar2 = iVar1 + 0x84;
  if (*(char *)(iVar1 + 0x95) < *(char *)(iVar1 + 0x94)) {
    for (lVar4 = (long)*(char *)(iVar1 + 0x95); lVar4 < *(char *)(iVar1 + 0x93);
        lVar4 = (long)((int)lVar4 + 1)) {
      if (*(char *)(iVar2 + (int)lVar4 + 0x12) == this) {
        while ((*(char *)(iVar1 + 0x95) <= lVar4 && (0 < lVar4))) {
          iVar3 = (int)lVar4;
          *(u8 *)(iVar2 + iVar3 + 0x12) = *(u8 *)(iVar2 + iVar3 + 0x11);
          lVar4 = (long)(iVar3 + -1);
        }
        *(char *)(iVar2 + *(char *)(iVar1 + 0x95) + 0x12) = this;
        *(char *)(iVar1 + 0x95) = *(char *)(iVar1 + 0x95) + '\x01';
        if (param_3 != '\0') {
          *(u16 *)(iVar1 + 0x9e) =
               *(u16 *)(iVar1 + 0x9e) | (u16)(1 << ((int)this & 0x1fU));
        }
        return 1;
      }
    }
  }
  return 0;
}

// JP: 0x00289be0  FindPC__15SaveMenuSectionFcP16SaveMenuPartySet  size 0x94
// SaveMenuSection::FindPC(char, SaveMenuPartySet*)
u32 FindPC__15SaveMenuSectionFcP16SaveMenuPartySet(char param_1,int this)
{
  char *pcVar1;
  char *pcVar2;
  pcVar1 = (char *)(this + 0x12);
  pcVar2 = pcVar1 + this->f_f /*char **/;
  while( true ) {
    if (pcVar2 <= pcVar1) {
      return 0;
    }
    if (*pcVar1 == param_1) break;
    pcVar1 = pcVar1 + 1;
  }
  return 1;
}

// JP: 0x00289c80  JoinParty__15SaveMenuSectionFcP16SaveMenuPartySet  size 0x48
// SaveMenuSection::JoinParty(char, SaveMenuPartySet*)
void JoinParty__15SaveMenuSectionFcP16SaveMenuPartySet(u8 param_1,int this)
{
  *(u8 *)(this + this->f_f /*char **/ + 0x12) = param_1;
  this->f_f /*char **/ = this->f_f /*char **/ + '\x01';
  return;
}

// JP: 0x00289cd0  LeaveParty__15SaveMenuSectionFcP16SaveMenuPartySet  size 0x14c
// SaveMenuSection::LeaveParty(char, SaveMenuPartySet*)
void LeaveParty__15SaveMenuSectionFcP16SaveMenuPartySet(char param_1,int this)
{
  char cVar1;
  int iVar2;
  long lVar3;
  lVar3 = 0;
  while( true ) {
    if (this->f_f /*char **/ <= lVar3) {
      return;
    }
    if (*(char *)(this + (int)lVar3 + 0x12) == param_1) break;
    lVar3 = (long)((int)lVar3 + 1);
  }
  if (lVar3 < this->f_11 /*char **/) {
    this->f_11 /*char **/ = this->f_11 /*char **/ + -1;
  }
  this->f_1a /*u16 **/ = this->f_1a /*u16 **/ & ~(short)param_1;
  cVar1 = this->f_f /*char **/;
  while (iVar2 = (int)lVar3, lVar3 < cVar1 + -1) {
    *(u8 *)(this + iVar2 + 0x12) = *(u8 *)(this + iVar2 + 0x13);
    lVar3 = (long)(iVar2 + 1);
  }
  *(u8 *)(this + iVar2 + 0x12) = 0xff;
  this->f_f /*char **/ = this->f_f /*char **/ + -1;
  return;
}

// JP: 0x00289e20  GetSaveDataSlot__15SaveMenuSectionFP13_SaveDataInfo  size 0x314
// SaveMenuSection::GetSaveDataSlot(_SaveDataInfo*)
u32 GetSaveDataSlot__15SaveMenuSectionFP13_SaveDataInfo(SaveMenuSection *this)
{
  u16 *puVar1;
  int iVar2;
  u32 *puVar3;
  char *__src;
  int iVar4;
  u32 uVar5;
  long lVar6;
  u32 *puVar7;
  char *__src_00;
  if (*(int *)(sm_pSubstance__15SaveMenuSection + 0x10) == 0) {
    uVar5 = 0;
  }
  else {
    puVar1 = *(u16 **)(sm_pSubstance__15SaveMenuSection + 0xc);
    iVar2 = Find__13MenuDataTableFs((int *)(sm_pSubstance__15SaveMenuSection + 0x10),0x2d);
    puVar7 = (u32 *)(iVar2 + 0x10);
    puVar3 = puVar7 + *(int *)(iVar2 + 8) * 2;
    __src_00 = (char *)0x0;
    for (; puVar7 < puVar3; puVar7 = puVar7 + 2) {
      if (puVar7[1] == *(int *)(puVar1 + 8)) {
        __src_00 = (char *)*puVar7;
        break;
      }
    }
    iVar2 = *(int *)(sm_pSubstance__15SaveMenuSection + 0xc) +
            *(char *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x80) * 0x20;
    __src = (char *)(iVar2 + 0x84);
    iVar4 = ourBtlSaveDat__10BtlSaveSec + *(char *)(iVar2 + 0x96) * 0xc0;
    this->f_1 /*u8 **/ = *(u8 *)(iVar4 + 0x47);
    this->f_2 /*u16 **/ = *puVar1;
    this->next = *(u32 *)(puVar1 + 6);
    this->hdr =
         *(u32 *)
          (*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) +
           (uint)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + 2) * 4 + 4);
    strcpy((char *)(this + 0x16),(char *)(iVar4 + 0x4e));
    strcpy((char *)(this + 0x28),__src);
    strcpy((char *)(this + 0x38),__src_00);
    this->data = 0;
    lVar6 = 0;
    while (lVar6 < *(char *)(iVar2 + 0x95)) {
      iVar4 = (int)lVar6;
      *(u16 *)(this + iVar4 * 2 + 0xe) =
           *(u16 *)(ourBtlSaveDat__10BtlSaveSec + __src[iVar4 + 0x12] * 0xc0 + 0x4c);
      lVar6 = (long)(iVar4 + 1);
    }
    for (; lVar6 < 4; lVar6 = (long)((int)lVar6 + 1)) {
      *(u16 *)(this + (int)lVar6 * 2 + 0xe) = 0xffff;
    }
    this->data = 0;
    for (lVar6 = 0; lVar6 < *(char *)(iVar2 + 0x93); lVar6 = (long)((int)lVar6 + 1)) {
      this->data =
           this->data | (u16)(1 << ((int)__src[(int)lVar6 + 0x12] & 0x1fU));
    }
    uVar5 = 1;
  }
  return uVar5;
}

// JP: 0x0028a140  __ct__15SaveMenuSectionFv  size 0xac
// SaveMenuSection::SaveMenuSection()
int * __ct__15SaveMenuSectionFv(SaveMenuSection *this)
{
  __ct__15SaveDataSectionFv(this);
  *this = (int)__vt__15SaveMenuSection;
  __ct__13MenuDataTableFv(this + 4);
  sm_pSubstance__15SaveMenuSection = this;
  CreateSection__15SaveDataSectionFPCcUiUs(this,0x3feac0,0x400,0);
  this[3] = this[2] + 0x10;
  (**(code **)(*this + 0xc))();
  return this;
}

// JP: 0x0028a1f0  __dt__15SaveMenuSectionFv  size 0x84
// SaveMenuSection::~SaveMenuSection()
u32 * __dt__15SaveMenuSectionFv(SaveMenuSection *this,short param_2)
{
  if (this != (u32 *)0x0) {
    *this = __vt__15SaveMenuSection;
    __dt__13MenuDataTableFv(this + 4,0xffffffffffffffff);
    __dt__15SaveDataSectionFv(this,0);
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}

// JP: 0x0028a280  SetDefault__15SaveMenuSectionFv  size 0x270
// SaveMenuSection::SetDefault()
void SetDefault__15SaveMenuSectionFv(SaveMenuSection *this)
{
  int iVar1;
  uint uVar2;
  int iVar3;
  memset((void *)(this->hdr + 0x10),0,(long)*(int *)(this->hdr + 8));
  iVar1 = *(int *)(sm_pSubstance__15SaveMenuSection + 0xc);
  for (uVar2 = iVar1 + 0x84; uVar2 < iVar1 + 0x124U; uVar2 = uVar2 + 0x20) {
    *(u8 *)(uVar2 + 0xf) = 2;
    *(u8 *)(uVar2 + 0x11) = 2;
    *(u8 *)(uVar2 + 0x10) = 4;
    *(u8 *)(uVar2 + 0x12) = 0xb;
    *(u8 *)(uVar2 + 0x13) = 5;
    for (iVar3 = 2; iVar3 < 8; iVar3 = iVar3 + 1) {
      *(u8 *)(uVar2 + iVar3 + 0x12) = 0xff;
    }
  }
  strcpy((char *)(iVar1 + 0x84),_3052);
  strcpy((char *)(iVar1 + 0xa4),_3053);
  strcpy((char *)(iVar1 + 0xc4),_3054);
  strcpy((char *)(iVar1 + 0xe4),_3055);
  strcpy((char *)(iVar1 + 0x104),_3056);
  SetDefaultButton__15SaveMenuSectionFv();
  iVar1 = *(int *)(sm_pSubstance__15SaveMenuSection + 0xc);
  *(u8 *)(iVar1 + 0x278) = 8;
  *(u8 *)(iVar1 + 0x274) = *(u8 *)(iVar1 + 0x274) & 0xcf | 0x10;
  *(u8 *)(iVar1 + 0x275) = *(u8 *)(iVar1 + 0x275) & 0xcf | 0x10;
  *(u8 *)(iVar1 + 0x274) = *(u8 *)(iVar1 + 0x274) & 0xfc | 1;
  *(u8 *)(iVar1 + 0x274) = *(u8 *)(iVar1 + 0x274) & 0x3f | 0x40;
  iVar1 = *(int *)(sm_pSubstance__15SaveMenuSection + 0xc);
  *(u16 *)(iVar1 + 0x2ac) = 0xffff;
  *(u16 *)(iVar1 + 0x2ae) = 0xffff;
  *(u16 *)(iVar1 + 0x2b0) = 0xffff;
  *(u8 *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x300) = 2;
  *(u8 *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x312) = 2;
  return;
}

// JP: 0x0028a4f0  SetSection__15SaveMenuSectionFP19_SaveDataSectionHdrPUc  size 0xa8
// SaveMenuSection::SetSection(_SaveDataSectionHdr*, unsigned char*)
void * SetSection__15SaveMenuSectionFP19_SaveDataSectionHdrPUc
                 (int *param_1,int this,void *param_3)
{
  int iVar1;
  void *pvVar2;
  if (this->hdr < *(uint *)(param_1[2] + 8)) {
    iVar1 = this->hdr;
    (**(code **)(*param_1 + 0xc))();
  }
  else {
    iVar1 = *(int *)(param_1[2] + 8);
  }
  pvVar2 = memcpy((void *)(param_1[2] + 0x10),param_3,(long)iVar1);
  return pvVar2;
}

// JP: 0x0028a5a0  CheckVersion__15SaveMenuSectionFUs  size 0x14
// SaveMenuSection::CheckVersion(unsigned short)
u32 CheckVersion__15SaveMenuSectionFUs(void)
{
  return 1;
}

// JP: 0x00380c60  GetCurrentPartySet__15SaveMenuSectionFv  size 0x1c
// SaveMenuSection::GetCurrentPartySet()
int GetCurrentPartySet__15SaveMenuSectionFv(void)
{
  return *(int *)(sm_pSubstance__15SaveMenuSection + 0xc) +
         *(char *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x80) * 0x20 + 0x84;
}
