/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x003990f0  __ct__13deviceCheckerFv  size 0x3c
// deviceChecker::deviceChecker()
int __ct__13deviceCheckerFv(deviceChecker *this)
{
  __ct__7CPolObjFv(this);
  this->f_14 /*u8 **/ = __vt__13deviceChecker;
  return this;
}

// JP: 0x00399130  __dt__13deviceCheckerFv  size 0x84
// deviceChecker::~deviceChecker()
int __dt__13deviceCheckerFv(deviceChecker *this,short param_2)
{
  if (this != 0) {
    this->f_14 /*u8 **/ = __vt__13deviceChecker;
    Dispose__7CPollerFP7CPolObj(app__4CApp + 0x48,this);
    __dt__7CPolObjFv(this,0);
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}

// JP: 0x003991c0  initialize__13deviceCheckerFv  size 0x58
// deviceChecker::initialize()
void initialize__13deviceCheckerFv(deviceChecker *this)
{
  this->f_18 /*u32 **/ = 0;
  this->f_20 /*u32 **/ = 0;
  this->f_24 /*u8 **/ = 0;
  this->f_25 /*u8 **/ = 0;
  Entry__7CPollerFP7CPolObjib(app__4CApp + 0x48,this,0x80,0);
  return;
}

// JP: 0x00399220  checkDeviceAll__13deviceCheckerFv  size 0x38
// deviceChecker::checkDeviceAll()
void checkDeviceAll__13deviceCheckerFv(deviceChecker *this)
{
  this->f_18 /*u32 **/ = 1;
  this->f_20 /*u32 **/ = 0;
  this->f_1c /*u32 **/ = 0;
  this->f_24 /*u8 **/ = 0;
  return;
}

// JP: 0x00399260  checkPollMC__13deviceCheckerFv  size 0x38
// deviceChecker::checkPollMC()
void checkPollMC__13deviceCheckerFv(deviceChecker *this)
{
  this->f_18 /*u32 **/ = 2;
  this->f_20 /*u32 **/ = 0;
  this->f_25 /*u8 **/ = 0;
  this->f_24 /*u8 **/ = 0;
  return;
}

// JP: 0x003992a0  finishPollMC__13deviceCheckerFv  size 0x34
// deviceChecker::finishPollMC()
void finishPollMC__13deviceCheckerFv(deviceChecker *this)
{
  this->f_18 /*u32 **/ = 0;
  Close__8SaveDataFv(0x421e70);
  return;
}

// JP: 0x003992e0  Polling__13deviceCheckerFv  size 0x74
// deviceChecker::Polling()
u64 Polling__13deviceCheckerFv(deviceChecker *this)
{
  if (this->f_18 /*int **/ == 2) {
    mPollMC__13deviceCheckerFv(this);
  }
  else if (this->f_18 /*int **/ == 1) {
    mCheckAll__13deviceCheckerFv(this);
  }
  return 0;
}

// JP: 0x00399360  mPollMC__13deviceCheckerFv  size 0x304
// deviceChecker::mPollMC()
void mPollMC__13deviceCheckerFv(deviceChecker *this)
{
  long lVar1;
  int iVar2;
  int iVar3;
  iVar2 = this->f_20 /*int **/;
  if (iVar2 < 0) {
    iVar2 = iVar2 + 1;
  }
  iVar3 = this + (iVar2 >> 1) * 8;
  iVar2 = this->f_20 /*int **/;
  if ((iVar2 == 3) || (iVar2 == 1)) {
    if ((short)DAT_00421e94 != 1) {
      if ((short)DAT_00421e94 == 3) {
        *(u8 *)(iVar3 + 0x28) = 1;
        if (*(char *)(iVar3 + 0x29) == '\x01') {
          this->f_25 /*u8 **/ = 1;
        }
        *(u8 *)(iVar3 + 0x29) = 0;
        Close__8SaveDataFv(0x421e70);
        if (this->f_20 /*int **/ == 1) {
          this->f_20 /*int **/ = this->f_20 /*int **/ + 1;
        }
        else {
          this->f_20 /*u32 **/ = 0;
        }
      }
      else {
        *(u8 *)(iVar3 + 0x28) = 1;
        if (*(char *)(iVar3 + 0x29) == '\0') {
          this->f_25 /*u8 **/ = 1;
        }
        *(u8 *)(iVar3 + 0x29) = 1;
        *(bool *)(iVar3 + 0x2a) = (char)*(u32 *)(DAT_00421e90 + 0xc) != '\0';
        *(bool *)(iVar3 + 0x2b) = (long)((ulong)*(u8 *)(DAT_00421e90 + 5) << 0x3e) < 0;
        *(u32 *)(iVar3 + 0x2c) = *(u32 *)(DAT_00421e90 + 0x10);
        Close__8SaveDataFv(0x421e70);
        if (this->f_20 /*int **/ == 1) {
          this->f_20 /*int **/ = this->f_20 /*int **/ + 1;
        }
        else {
          this->f_20 /*u32 **/ = 0;
        }
      }
    }
  }
  else if (iVar2 == 2) {
    lVar1 = Open__8SaveDataFs(0x421e70,1);
    if (lVar1 != 0) {
      this->f_20 /*int **/ = this->f_20 /*int **/ + 1;
    }
  }
  else if ((iVar2 == 0) && (lVar1 = Open__8SaveDataFs(0x421e70,0), lVar1 != 0)) {
    this->f_20 /*int **/ = this->f_20 /*int **/ + 1;
  }
  return;
}

// JP: 0x00399670  mCheckAll__13deviceCheckerFv  size 0x434
// deviceChecker::mCheckAll()
void mCheckAll__13deviceCheckerFv(deviceChecker *this)
{
  u8 bVar1;
  u8 *pbVar2;
  long lVar3;
  int iVar4;
  uint uVar5;
  iVar4 = this->f_20 /*int **/;
  if (iVar4 < 0) {
    iVar4 = iVar4 + 1;
  }
  iVar4 = this + (iVar4 >> 1) * 8;
  switch(this->f_20 /*u32 **/) {
  case 0:
    lVar3 = Open__8SaveDataFs(0x421e70,0);
    if (lVar3 != 0) {
      this->f_20 /*int **/ = this->f_20 /*int **/ + 1;
    }
    break;
  case 1:
  case 3:
  case 5:
    if ((short)DAT_00421e94 != 1) {
      if ((short)DAT_00421e94 == 3) {
        *(u8 *)(iVar4 + 0x28) = 1;
        *(u8 *)(iVar4 + 0x29) = 0;
        Close__8SaveDataFv(0x421e70);
        this->f_20 /*int **/ = this->f_20 /*int **/ + 1;
      }
      else {
        *(u8 *)(iVar4 + 0x28) = 1;
        *(u8 *)(iVar4 + 0x29) = 1;
        *(bool *)(iVar4 + 0x2a) = (char)*(u32 *)(DAT_00421e90 + 0xc) != '\0';
        *(bool *)(iVar4 + 0x2b) = (long)((ulong)*(u8 *)(DAT_00421e90 + 5) << 0x3e) < 0;
        *(u32 *)(iVar4 + 0x2c) = *(u32 *)(DAT_00421e90 + 0x10);
        this->f_20 /*int **/ = this->f_20 /*int **/ + 1;
        if (*(char *)(iVar4 + 0x2b) != '\0') {
          bVar1 = *(u8 *)(*(int *)(DAT_00421e90 + 0x1c) + 0xd);
          iVar4 = 0;
          for (uVar5 = 0; (int)uVar5 < (int)(uint)bVar1; uVar5 = uVar5 + 1) {
            pbVar2 = (u8 *)(*(int *)(DAT_00421e90 + 0x1c) +
                              *(int *)(*(int *)(DAT_00421e90 + 0x1c) + 0x1c) + (uVar5 & 0xff) * 0x60
                             );
            printf(_5602,uVar5,(ulong)*pbVar2,pbVar2 + 0x38);
            if (*pbVar2 != 0xff) {
              iVar4 = iVar4 + 1;
            }
          }
          this->f_1c /*int **/ = this->f_1c /*int **/ + iVar4;
        }
        Close__8SaveDataFv(0x421e70);
      }
    }
    break;
  case 2:
    lVar3 = Open__8SaveDataFs(0x421e70,1);
    if (lVar3 != 0) {
      this->f_20 /*int **/ = this->f_20 /*int **/ + 1;
    }
    break;
  case 4:
    lVar3 = Open__8SaveDataFs(0x421e70,2);
    if (lVar3 != 0) {
      this->f_20 /*int **/ = this->f_20 /*int **/ + 1;
    }
    break;
  case 6:
    *(u8 *)(sys__6SSHSys + 0x3c) =
         *(u8 *)(sys__6SSHSys + 0x3c) & 0xf8 | this->f_39 /*u8 **/ & 7;
    if (this->f_39 /*char **/ != '\0') {
      checkHDDInstall__7installFv();
    }
    this->f_24 /*u8 **/ = 1;
    this->f_18 /*u32 **/ = 0;
  }
  return;
}

// JP: 0x00399ab0  closeDevice__13deviceCheckerFv  size 0x60
// deviceChecker::closeDevice()
bool closeDevice__13deviceCheckerFv(void)
{
  bool bVar1;
  bVar1 = DAT_00421e90 != 0;
  if (bVar1) {
    Close__8SaveDataFv(0x421e70);
  }
  return !bVar1;
}

// JP: 0x00399b10  isChangeStatus__13deviceCheckerFv  size 0x34
// deviceChecker::isChangeStatus()
u8 isChangeStatus__13deviceCheckerFv(deviceChecker *this)
{
  u8 uVar1;
  uVar1 = this->f_25 /*u8 **/;
  this->f_25 /*u8 **/ = 0;
  return uVar1;
}

// JP: 0x00399b50  getActiveDeviceNum__13deviceCheckerFv  size 0x6c
// deviceChecker::getActiveDeviceNum()
int getActiveDeviceNum__13deviceCheckerFv(deviceChecker *this)
{
  int iVar1;
  int iVar2;
  iVar2 = 0;
  for (iVar1 = 0; iVar1 < 3; iVar1 = iVar1 + 1) {
    if (*(char *)(this + iVar1 * 8 + 0x29) != '\0') {
      iVar2 = iVar2 + 1;
    }
  }
  return iVar2;
}

// JP: 0x00399bc0  getSavedDeviceNum__13deviceCheckerFv  size 0x84
// deviceChecker::getSavedDeviceNum()
int getSavedDeviceNum__13deviceCheckerFv(deviceChecker *this)
{
  int iVar1;
  int iVar2;
  iVar2 = 0;
  for (iVar1 = 0; iVar1 < 3; iVar1 = iVar1 + 1) {
    if ((*(char *)(this + iVar1 * 8 + 0x29) != '\0') &&
       (*(char *)(this + iVar1 * 8 + 0x2b) != '\0')) {
      iVar2 = iVar2 + 1;
    }
  }
  return iVar2;
}

// JP: 0x00399c50  getFreeDeviceNum__13deviceCheckerFv  size 0xa4
// deviceChecker::getFreeDeviceNum()
int getFreeDeviceNum__13deviceCheckerFv(deviceChecker *this)
{
  int iVar1;
  int iVar2;
  iVar2 = 0;
  for (iVar1 = 0; iVar1 < 3; iVar1 = iVar1 + 1) {
    if ((*(char *)(this + iVar1 * 8 + 0x29) != '\0') &&
       ((*(char *)(this + iVar1 * 8 + 0x2a) == '\0' ||
        (99 < *(int *)(this + iVar1 * 8 + 0x2c))))) {
      iVar2 = iVar2 + 1;
    }
  }
  return iVar2;
}

// JP: 0x00399d00  isOnlyHDD__13deviceCheckerFv  size 0x5c
// deviceChecker::isOnlyHDD()
u32 isOnlyHDD__13deviceCheckerFv(deviceChecker *this)
{
  u32 uVar1;
  if (((this->f_29 /*char **/ == '\0') && (this->f_31 /*char **/ == '\0')) &&
     (this->f_39 /*char **/ != '\0')) {
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

// JP: 0x00399d60  isHDD__13deviceCheckerFv  size 0x3c
// deviceChecker::isHDD()
bool isHDD__13deviceCheckerFv(deviceChecker *this)
{
  return this->f_39 /*char **/ != '\0';
}
