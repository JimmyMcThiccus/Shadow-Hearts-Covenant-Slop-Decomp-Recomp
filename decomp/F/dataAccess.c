/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x00391cd0  DVD_CBFunc__10dataAccessFiP9BufMemoryiPcPv  size 0xb8
// dataAccess::DVD_CBFunc(int, BufMemory*, int, char*, void*)
u64
DVD_CBFunc__10dataAccessFiP9BufMemoryiPcPv
          (u32 param_1,int this,u32 param_3,u32 param_4,u32 param_5)
{
  u32 uVar1;
  long lVar2;
  m_pTex = this->link_next;
  m_TexRead = 1;
  mpData = this;
  m_type = param_1;
  m_size = param_3;
  m_filename = param_4;
  m_data = param_5;
  lVar2 = __nw__FUi(0x52c);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = __ct__7primTexFv(lVar2);
  }
  m_pPT = uVar1;
  initialize__7primTexFP9BufMemory(m_pPT,this);
  return 0;
}

// JP: 0x00391d90  __ct__10dataAccessFv  size 0x134
// dataAccess::dataAccess()
int __ct__10dataAccessFv(dataAccess *this)
{
  __ct__7CPolObjFv(this);
  this->f_18 /*u32 **/ = 0;
  this->f_1c /*u32 **/ = 0;
  this->f_20 /*u8 **/ = __vt__17DelayDeleteObject;
  this->f_14 /*u8 **/ = __vt__10dataAccess;
  this->f_20 /*u32 **/ = 0x407200;
  __ct__4FontFv(this + 0x128);
  __ct__4FontFv(this + 300);
  mpData = 0;
  this->f_174 /*u8 **/ = 0;
  this->callback = 0;
  this->cb_arg = 0;
  this->disp = 0;
  this->f_120 /*u32 **/ = 0;
  this->f_124 /*u32 **/ = 0;
  this->fader = 0;
  this->f_3c /*u32 **/ = 0;
  this->bg = 0;
  this->f_44 /*u32 **/ = 0;
  this->popup = 0;
  this->win = 0;
  this->f_15c /*u32 **/ = 0;
  this->main_cursor = 0;
  this->cursor = 0;
  this->scrollmark = 0;
  this->snd = 0;
  this->f_94 /*u32 **/ = 0;
  this->f_98 /*u32 **/ = 0;
  return this;
}

// JP: 0x00391ed0  __dt__10dataAccessFv  size 0x178
// dataAccess::~dataAccess()
int __dt__10dataAccessFv(dataAccess *this,short param_2)
{
  int iVar1;
  if (this != 0) {
    this->f_14 /*u8 **/ = __vt__10dataAccess;
    this->f_20 /*u32 **/ = 0x407200;
    if (this->f_15c /*int **/ != 0) {
      iVar1 = this->f_15c /*int **/;
      if (iVar1 != 0) {
        VCALL14(iVar1, 8)(iVar1,1);
      }
      this->f_15c /*u32 **/ = 0;
    }
    if (m_pPT != 0) {
      __dt__7primTexFv(m_pPT,1);
      m_pPT = 0;
    }
    Dispose__7CPollerFP7CPolObj(app__4CApp + 0x48,this);
    if (this->snd != 0) {
      DelayDeleteRequest__9primSoundFv(this->snd);
      this->snd = 0;
    }
    __dt__4FontFv(this + 300,0xffffffffffffffff);
    __dt__4FontFv(this + 0x128,0xffffffffffffffff);
    if (this != -0x18) {
      this->f_20 /*u8 **/ = __vt__17DelayDeleteObject;
    }
    __dt__7CPolObjFv(this,0);
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}

// JP: 0x00392050  initialize__10dataAccessFQ210dataAccess10ACCESSMODEPFiPv_vPv  size 0x1c0
// dataAccess::initialize(dataAccess::ACCESSMODE, fn*, void*)
void initialize__10dataAccessFQ210dataAccess10ACCESSMODEPFiPv_vPv
               (dataAccess *this,int param_2,u32 param_3,u32 param_4)
{
  u32 uVar1;
  long lVar2;
  u64 uVar3;
  u8 auStack_140 [256];
  int iStack_40;
  int iStack_30;
  u32 uStack_20;
  u32 uStack_10;
  this->mode = param_2;
  iStack_40 = this;
  iStack_30 = param_2;
  uStack_20 = param_3;
  uStack_10 = param_4;
  if (param_2 == 2) {
    this->state = 0;
    this->mode2 = 0;
    lVar2 = __nw__FUi(0x40);
    uVar1 = 0;
    if (lVar2 != 0) {
      uVar1 = __ct__13deviceCheckerFv(lVar2);
    }
    *(u32 *)(iStack_40 + 0x15c) = uVar1;
    initialize__13deviceCheckerFv(*(u32 *)(iStack_40 + 0x15c));
  }
  else {
    this->state = 1;
    uVar3 = SetPathname__7SysToolFPcPCc(auStack_140,0x4010e0);
    ReadOrder__11DvdromOrderFPCcPFiP9BufMemoryiPcPv_iiPvi
              (Dvdromour__11DvdromOrder,uVar3,0x391cd0,0,iStack_40,0);
  }
  *(u32 *)(iStack_40 + 0x168) = 0;
  *(u8 *)(iStack_40 + 0x173) = 0;
  *(u32 *)(iStack_40 + 0x24) = uStack_20;
  *(u32 *)(iStack_40 + 0x28) = uStack_10;
  lVar2 = __nw__FUi(0x30);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = __ct__9primSoundFv(lVar2);
  }
  *(u32 *)(iStack_40 + 0x34) = uVar1;
  initialize__9primSoundFv(*(u32 *)(iStack_40 + 0x34));
  Entry__7CPollerFP7CPolObjib(app__4CApp + 0x48,iStack_40,0x80,0);
  m_TexRead = 0;
  *(u8 *)(iStack_40 + 0x171) = 0;
  *(bool *)(iStack_40 + 0x172) = (*(u8 *)(sys__6SSHSys + 0x3c) & 7) != 0;
  return;
}

// JP: 0x00392210  start__10dataAccessFQ210dataAccess9STARTMODEii  size 0x78
// dataAccess::start(dataAccess::STARTMODE, int, int)
void start__10dataAccessFQ210dataAccess9STARTMODEii
               (dataAccess *this,u32 param_2,int param_3,int param_4)
{
  this->f_173 /*u8 **/ = 1;
  this->f_148 /*u32 **/ = param_2;
  this->f_9c /*float **/ = (float)param_3;
  this->f_94 /*float **/ = (float)param_3;
  this->f_a0 /*float **/ = (float)param_4;
  this->f_98 /*float **/ = (float)param_4;
  return;
}

// JP: 0x00392290  getCursorPos__10dataAccessFPfPf  size 0x3c
// dataAccess::getCursorPos(float*, float*)
void getCursorPos__10dataAccessFPfPf(dataAccess *this,u32 *param_2,u32 *param_3)
{
  *param_2 = this->f_9c /*u32 **/;
  *param_3 = this->f_a0 /*u32 **/;
  return;
}

// JP: 0x003922d0  Polling__10dataAccessFv  size 0x2018
// dataAccess::Polling()
/* WARNING: Removing unreachable block (ram,0x00394138) */
u64 Polling__10dataAccessFv(dataAccess *this)
{
  u16 uVar1;
  char cVar2;
  u16 uVar3;
  short sVar4;
  int iVar5;
  u32 uVar6;
  u64 uVar7;
  long lVar8;
  u8 *pbVar9;
  int iVar10;
  uint uVar11;
  int iStack_28;
  iVar5 = GetActive__4CPadFi(0);
  uVar1 = *(u16 *)((&m_pCoreArray__4CPad)[*(int *)(iVar5 + 4)] + 0x6c);
  uVar3 = *(u16 *)((&m_pCoreArray__4CPad)[*(int *)(iVar5 + 4)] + 0x70) & 0xf0 | uVar1;
  switch(this->state) {
  case 0:
    lVar8 = mInitialDeviceCheck__10dataAccessFi(this,uVar3);
    if (lVar8 != 0) {
      if (this->mode2 == 4) {
        this->state = 0x1d;
      }
      else {
        if (this->popup != 0) {
          DelayDeleteRequest__7primWinFv(this->popup);
          this->popup = 0;
        }
        this->state = 0x1c;
      }
    }
    break;
  case 1:
    if ((m_TexRead != '\0') && (this->f_173 /*char **/ != '\0')) {
      mSetupBG__10dataAccessFv(this);
      this->result = 0;
      (*this->callback)
                (this->result,this->cb_arg);
      this->state = 2;
    }
    break;
  case 2:
    lVar8 = isFade__7primWinFv(this->fader);
    if (lVar8 == 0) {
      this->result = 1;
      (*this->callback)
                (this->result,this->cb_arg);
      this->state = 5;
    }
    break;
  case 3:
    lVar8 = isFade__7primWinFv(this->win);
    if (lVar8 == 0) {
      mReleaseWin__10dataAccessFv(this);
      this->state = 4;
    }
    break;
  case 4:
    mSetupSelectDevice__10dataAccessFv(this);
    this->state = 5;
    break;
  case 5:
    lVar8 = isFade__7primWinFv(this->win);
    if (lVar8 == 0) {
      if ((uVar1 & 0x2000) == 0) {
        if ((uVar1 & 0x4000) == 0) {
          mCheckDirKey__10dataAccessFi(this,uVar3);
        }
        else {
          play__9primSoundFi(this->snd,3);
          fadeout__7primWinFi(this->win,0x10);
          this->state = 0x19;
        }
      }
      else {
        play__9primSoundFi(this->snd,2);
        this->retry = 0;
        mOpenDevice__10dataAccessFi(this,this->device_sel);
        mSetupProgress__10dataAccessFv(this);
        this->progress = 0;
        this->state = 6;
      }
    }
    break;
  case 6:
    mGrowProgress__10dataAccessFi(this,4);
    if ((short)DAT_00421e94 != 1) {
      if ((short)DAT_00421e94 == 3) {
        if ((*(uint *)(DAT_00421e90 + 0xc) & 0xff) == 0) {
          mSetupWarning__10dataAccessFPc
                    (this,*(u32 *)
                              (dataMess_deviceWarning_J + this->dev_kind * 4));
        }
        else {
          mSetupWarning__10dataAccessFPc
                    (this,*(u32 *)
                              (dataMess_systemWarning_J + this->dev_kind * 4));
        }
        Close__8SaveDataFv(0x421e70);
        this->state = 7;
        this->next_state = 0x19;
      }
      else if (this->progress == 0) {
        if ((*(uint *)(DAT_00421e90 + 0xc) & 0xff) == 0) {
          this->retry = this->retry + 1;
          if (this->retry < 3) {
            Close__8SaveDataFv(0x421e70);
            this->state = 8;
          }
          else {
            mSetupWarning__10dataAccessFPc
                      (this,*(u32 *)
                                (dataMess_deviceUnformat_J + this->dev_kind * 4));
            this->state = 7;
            if (this->dev_kind < 2) {
              this->next_state = 9;
            }
            else {
              Close__8SaveDataFv(0x421e70);
              this->next_state = 0x19;
            }
          }
        }
        else if ((long)((ulong)*(u8 *)(DAT_00421e90 + 5) << 0x3e) < 0) {
          iStack_28 = 0;
          uVar11 = (uint)*(u8 *)(*(int *)(DAT_00421e90 + 0x1c) + 0xc);
          this->cur_slot = uVar11;
          printf(_5972,0x1d44);
          printf(_5973,(uint)*(u16 *)(sys__14CFieldSaveData + 0xc) << 4);
          printf(_5974,0x400);
          printf(_5975,(uint)*(u16 *)(sys__14CFieldSaveData + 0xc) * 0x10 + 0x21c4);
          printf(_5976,uVar11);
          for (uVar11 = 0; (int)uVar11 < this->slot_count; uVar11 = uVar11 + 1) {
            pbVar9 = (u8 *)(*(int *)(DAT_00421e90 + 0x1c) +
                              *(int *)(*(int *)(DAT_00421e90 + 0x1c) + 0x1c) +
                             (uVar11 & 0xff) * 0x60);
            printf(_5977,uVar11,(ulong)*pbVar9,pbVar9 + 0x38);
            if (*pbVar9 == 0xff) {
              *(u8 *)(this + uVar11 + 0xac) = 1;
            }
            else {
              *(u8 *)(this + uVar11 + 0xac) = 0;
              iStack_28 = iStack_28 + 1;
            }
          }
          if ((this->mode == 1) && (iStack_28 == 0)) {
            Close__8SaveDataFv(0x421e70);
            mSetupWarning__10dataAccessFPc
                      (this,*(u32 *)
                                (dataMess_deviceNoSaveData_J + this->dev_kind * 4));
            this->state = 7;
            this->next_state = 0x19;
          }
          else {
            mReleaseWin__10dataAccessFv(this);
            this->state = 0xe;
          }
        }
        else if (this->mode == 1) {
          Close__8SaveDataFv(0x421e70);
          mSetupWarning__10dataAccessFPc
                    (this,*(u32 *)
                              (dataMess_deviceNoSaveData_J + this->dev_kind * 4));
          this->state = 7;
          this->next_state = 0x19;
        }
        else {
          for (iVar5 = 0; iVar5 < this->slot_count; iVar5 = iVar5 + 1) {
            *(u8 *)(this + iVar5 + 0xac) = 1;
          }
          mReleaseWin__10dataAccessFv(this);
          this->state = 0xe;
        }
      }
    }
    break;
  case 7:
    lVar8 = mCheckWarning__10dataAccessFi(this,uVar3);
    if (lVar8 != 0) {
      mReleaseWarning__10dataAccessFv(this);
      mReleaseWin__10dataAccessFv(this);
      this->state = this->next_state;
    }
    break;
  case 8:
    if (DAT_00421e90 == 0) {
      mOpenDevice__10dataAccessFi(this,this->device_sel);
      this->state = 6;
    }
    else {
      Close__8SaveDataFv(0x421e70);
    }
    break;
  case 9:
    mSetupFormat__10dataAccessFv(this);
    this->state = 10;
    break;
  case 10:
    if ((uVar1 & 0x2000) == 0) {
      if ((uVar1 & 0x4000) == 0) {
        mCheckDirKey__10dataAccessFi(this,uVar3);
      }
      else {
        play__9primSoundFi(this->snd,3);
        mReleaseWin__10dataAccessFv(this);
        this->state = 0x19;
      }
    }
    else if (this->device_sel == 0) {
      uVar6 = DisableReset__6CPauseFv(*(u32 *)(app__4CApp + 0x78));
      this->reset_lock = uVar6;
      play__9primSoundFi(this->snd,2);
      mSetupProgressFormat__10dataAccessFv(this);
      cVar2 = Format__8SaveDataFv(0x421e70);
      if (cVar2 == '\0') {
        do {
                    /* WARNING: Do nothing block with infinite loop */
        } while( true );
      }
      this->state = 0xb;
    }
    else {
      play__9primSoundFi(this->snd,2);
      mReleaseWin__10dataAccessFv(this);
      this->state = 0x19;
    }
    break;
  case 0xb:
    mGrowProgress__10dataAccessFi(this,4);
    sVar4 = (short)DAT_00421e94;
    if (sVar4 != 1) {
      if ((sVar4 == 0) || (sVar4 == 3)) {
        EnableReset__6CPauseFi(*(u32 *)(app__4CApp + 0x78),this->reset_lock);
        Close__8SaveDataFv(0x421e70);
        setTextAlpha__7primWinFii(this->win,2,0);
        mSetupWarning__10dataAccessFPc(this,PTR__5490_003f9c78);
        this->state = 7;
        this->next_state = 0x19;
      }
      else if (sVar4 == 2) {
        EnableReset__6CPauseFi(*(u32 *)(app__4CApp + 0x78),this->reset_lock);
        mGrowProgress__10dataAccessFi(this,0x130);
        setTextAlpha__7primWinFii(this->win,2,0);
        setTextAlpha__7primWinFii(this->win,3,0x80);
        if (this->cursor == 0) {
          lVar8 = __nw__FUi(0x10c);
          uVar6 = 0;
          if (lVar8 != 0) {
            uVar6 = __ct__10primCursorFv(lVar8);
          }
          this->cursor = uVar6;
          createCursor__10primCursorFiiii(this->cursor,1,1,2,10);
          setPos__10primCursorFff(0x43480000,0x43a20000,this->cursor);
        }
        this->state = 0xd;
      }
    }
    break;
  case 0xd:
    if ((uVar1 & 0x2000) != 0) {
      play__9primSoundFi(this->snd,2);
      mReleaseWin__10dataAccessFv(this);
      if (this->cursor != 0) {
        DelayDeleteRequest__10primCursorFv(this->cursor);
        this->cursor = 0;
      }
      if (this->mode == 1) {
        this->state = 0x19;
      }
      else {
        this->state = 0xe;
      }
    }
    break;
  case 0xe:
    mSetupSelectFile__10dataAccessFv(this);
    this->state = 0xf;
    break;
  case 0xf:
    if (((short)DAT_00421e94 == 0) || ((short)DAT_00421e94 == 3)) {
      Close__8SaveDataFv(0x421e70);
      if (this->scrollmark != 0) {
        iVar5 = this->scrollmark;
        if (iVar5 != 0) {
          VCALL14(iVar5, 8)(iVar5,1);
        }
        this->scrollmark = 0;
      }
      mSetupWarning__10dataAccessFPc
                (this,*(u32 *)(dataMess_deviceWarning_J + this->dev_kind * 4));
      this->state = 0x16;
      this->next_state = 0x19;
    }
    else if ((uVar1 & 0x2000) == 0) {
      if ((uVar1 & 0x4000) == 0) {
        if ((uVar3 & 0x10) == 0) {
          if (((uVar3 & 0x40) != 0) && (this->cur_slot < this->slot_count + -1))
          {
            play__9primSoundFi(this->snd,0);
            mSetFileViewScroll__10dataAccessFi(this,0x10);
            this->cur_slot = this->cur_slot + 1;
            this->state = 0x10;
            this->scroll_timer = 0xc;
            select__12udScrollMarkFi
                      (this->scrollmark,this->cur_slot);
          }
        }
        else if (0 < this->cur_slot) {
          play__9primSoundFi(this->snd,0);
          mSetFileViewScroll__10dataAccessFi(this,0x40);
          this->cur_slot = this->cur_slot + -1;
          this->state = 0x11;
          this->scroll_timer = 0xc;
          select__12udScrollMarkFi(this->scrollmark,this->cur_slot)
          ;
        }
      }
      else {
        play__9primSoundFi(this->snd,3);
        if (this->scrollmark != 0) {
          iVar5 = this->scrollmark;
          if (iVar5 != 0) {
            VCALL14(iVar5, 8)(iVar5,1);
          }
          this->scrollmark = 0;
        }
        mReleaseSelectFile__10dataAccessFv(this);
        this->state = 0x19;
      }
    }
    else if ((this->mode == 1) &&
            (*(char *)(this + this->cur_slot + 0xac) != '\0')) {
      play__9primSoundFi(this->snd,4);
    }
    else if ((this->mode == 0) &&
            (lVar8 = mCheckFreeArea__10dataAccessFv(this), lVar8 == 0)) {
      play__9primSoundFi(this->snd,2);
      this->next_state = 0x19;
      mSetupWarning__10dataAccessFPc(this,dataMess_saveWarning_J);
      if (this->scrollmark != 0) {
        iVar5 = this->scrollmark;
        if (iVar5 != 0) {
          VCALL14(iVar5, 8)(iVar5,1);
        }
        this->scrollmark = 0;
      }
      this->state = 0x16;
    }
    else {
      play__9primSoundFi(this->snd,2);
      this->state = 0x12;
      if (this->scrollmark != 0) {
        iVar5 = this->scrollmark;
        if (iVar5 != 0) {
          VCALL14(iVar5, 8)(iVar5,1);
        }
        this->scrollmark = 0;
      }
    }
    break;
  case 0x10:
    this->scroll_timer = this->scroll_timer + -1;
    mMoveFileView__10dataAccessFi(this,0x10);
    if (this->scroll_timer == 0) {
      mFinishFileViewScroll__10dataAccessFi(this,0x10);
      this->state = 0xf;
    }
    break;
  case 0x11:
    this->scroll_timer = this->scroll_timer + -1;
    mMoveFileView__10dataAccessFi(this,0x40);
    if (this->scroll_timer == 0) {
      mFinishFileViewScroll__10dataAccessFi(this,0x40);
      this->state = 0xf;
    }
    break;
  case 0x12:
    if ((this->mode != 0) || (*(int *)(sm_pSubstance__15SaveMenuSection + 0x10) != 0))
    {
      mSetupQuerySaveLoad__10dataAccessFv(this);
      this->state = 0x13;
    }
    break;
  case 0x13:
    if (((uVar1 & 0x2000) == 0) || (this->device_sel != 0)) {
      if ((uVar1 & 0x6000) == 0) {
        mCheckDirKey__10dataAccessFi(this,uVar3);
      }
      else {
        if ((uVar1 & 0x2000) == 0) {
          play__9primSoundFi(this->snd,3);
        }
        else {
          play__9primSoundFi(this->snd,2);
        }
        mRecoverSelectFile__10dataAccessFv(this);
        fadeout__7primWinFi(this->popup,0x10);
        this->state = 0x14;
        this->next_state = 0xf;
      }
    }
    else {
      uVar6 = DisableReset__6CPauseFv(*(u32 *)(app__4CApp + 0x78));
      this->reset_lock = uVar6;
      play__9primSoundFi(this->snd,2);
      mSetupProgressSaveLoad__10dataAccessFv(this);
      this->state = 0x14;
      this->next_state = 0x15;
    }
    break;
  case 0x14:
    if ((((this->next_state != 0x15) || (this->mode != 0)) ||
        (lVar8 = GetSaveDataSlot__15SaveMenuSectionFP13_SaveDataInfo
                           (this->info), lVar8 != 0)) &&
       (lVar8 = isFade__7primWinFv(this->popup), lVar8 == 0)) {
      if (this->popup != 0) {
        DelayDeleteRequest__7primWinFv(this->popup);
        this->popup = 0;
      }
      mReleaseMainCursor__10dataAccessFv(this);
      this->state = this->next_state;
    }
    break;
  case 0x15:
    mGrowProgress__10dataAccessFi(this,1);
    sVar4 = (short)DAT_00421e94;
    if (sVar4 != 1) {
      if ((sVar4 == 0) || (sVar4 == 3)) {
        uVar7 = EnableReset__6CPauseFi
                          (*(u32 *)(app__4CApp + 0x78),this->reset_lock);
        Close__8SaveDataFv(0x421e70,uVar7);
        setTextAlpha__7primWinFii(this->win,2,0);
        mSetupWarning__10dataAccessFPc(this,*(u32 *)(this->f_140 /*int **/ + 8));
        this->state = 0x17;
        this->next_state = 0x19;
      }
      else if (sVar4 == 2) {
        this->progress = this->progress + -1;
        if (this->progress == 0) {
          play__9primSoundFi(this->snd,0x1000);
          mGrowProgress__10dataAccessFi(this,0x130);
          setTextAlpha__7primWinFii(this->win,2,0);
          iVar5 = setTextAlpha__7primWinFii(this->win,3,0x80);
          if (this->mode == 0) {
            iVar10 = 0;
            while (iVar10 < 3) {
              if (*(int *)(this + iVar10 * 4 + 0x110) == 1) {
                if (*(int *)(this + iVar10 * 4 + 0x11c) != 0) {
                  __dt__12dispSaveFileFv(*(u32 *)(this + iVar10 * 4 + 0x11c),1);
                  *(u32 *)(this + iVar10 * 4 + 0x11c) = 0;
                }
                lVar8 = __nw__FUi(0x34);
                uVar6 = 0;
                if (lVar8 != 0) {
                  uVar6 = __ct__12dispSaveFileFiiiQ210dataAccess10ACCESSMODEP7primTexPPc
                                    (lVar8,this->cur_slot,1,iVar10,
                                     this->mode,m_pPT,0x3f9d20);
                }
                *(u32 *)(this + iVar10 * 4 + 0x11c) = uVar6;
              }
              iVar5 = iVar10 + 1;
              iVar10 = iVar5;
            }
          }
          if (this->cursor == 0) {
            lVar8 = __nw__FUi(0x10c,iVar5);
            uVar6 = 0;
            if (lVar8 != 0) {
              uVar6 = __ct__10primCursorFv(lVar8);
            }
            this->cursor = uVar6;
            createCursor__10primCursorFiiii(this->cursor,1,1,2,10);
            setPos__10primCursorFff(0x43480000,0x43a20000,this->cursor);
          }
          EnableReset__6CPauseFi
                    (*(u32 *)(app__4CApp + 0x78),this->reset_lock);
          this->state = 0x18;
        }
        else {
          Save__8SaveDataFUc(0x421e70,this->cur_slot & 0xff);
        }
      }
    }
    break;
  case 0x16:
  case 0x17:
    if (DAT_00421e90 == 0) {
      lVar8 = mCheckWarning__10dataAccessFi(this,uVar3);
      if (lVar8 != 0) {
        mReleaseWarning__10dataAccessFv(this);
        mReleaseWin__10dataAccessFv(this);
        mReleaseSelectFile__10dataAccessFv(this);
        this->state = this->next_state;
      }
    }
    else {
      Close__8SaveDataFv(0x421e70);
    }
    break;
  case 0x18:
    if ((uVar1 & 0x2000) != 0) {
      play__9primSoundFi(this->snd,2);
      Close__8SaveDataFv(0x421e70);
      mReleaseWin__10dataAccessFv(this);
      uVar7 = mReleaseSelectFile__10dataAccessFv(this);
      if (this->cursor != 0) {
        DelayDeleteRequest__10primCursorFv(this->cursor,uVar7);
        this->cursor = 0;
      }
      if (this->mode == 1) {
        this->result = 5;
      }
      else {
        this->result = 3;
      }
      (*this->callback)
                (this->result,this->cb_arg);
      fadeout__7primWinFi(this->fader,0x10);
      this->state = 0x1c;
    }
    break;
  case 0x19:
    lVar8 = isFade__7primWinFv(this->win);
    if (lVar8 == 0) {
      mReleaseWin__10dataAccessFv(this);
      this->state = 0x1a;
    }
    break;
  case 0x1a:
    Close__8SaveDataFv(0x421e70);
    mSetupQuit__10dataAccessFv(this);
    this->state = 0x1b;
    break;
  case 0x1b:
    lVar8 = isFade__7primWinFv(this->win);
    if (lVar8 == 0) {
      if ((uVar1 & 0x2000) == 0) {
        if ((uVar1 & 0x4000) == 0) {
          mCheckDirKey__10dataAccessFi(this,uVar3);
        }
        else {
          play__9primSoundFi(this->snd,3);
          fadeout__7primWinFi(this->win,0x10);
          this->state = 3;
        }
      }
      else {
        play__9primSoundFi(this->snd,2);
        if (this->device_sel == 1) {
          getPos__10primCursorFPfPf(this->main_cursor,this + 0x94,this + 0x98);
          fadeout__7primWinFi(this->win,0x10);
          this->state = 3;
        }
        else {
          getPos__10primCursorFPfPf(this->main_cursor,this + 0x9c,this + 0xa0);
          fadeout__7primWinFi(this->win,0x10);
          uVar7 = mReleaseMainCursor__10dataAccessFv(this);
          this->result = 3;
          (*this->callback)
                    (this->result,this->cb_arg,uVar7);
          fadeout__7primWinFi(this->fader,0x10);
          this->state = 0x1c;
        }
      }
    }
    break;
  case 0x1c:
    lVar8 = isFade__7primWinFv(this->fader);
    if (lVar8 == 0) {
      if (this->result == 5) {
        SetBright__4CAppFf((float)*(u8 *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x278
                                           ) * 0.03 + 0.7,app__4CApp);
        uVar6 = GetSavedMpsName__Fi(0);
        printf(_5978,uVar6);
        FieldMapJump__FPCci(uVar6,0xfffffffffffffffe);
      }
      if (this->bg != 0) {
        DelayDeleteRequest__7primWinFv(this->bg);
        this->bg = 0;
      }
      mReleaseBG__10dataAccessFv(this);
      this->state = 0x1d;
    }
    break;
  case 0x1d:
    if ((this->result != 5) &&
       (this->result = 4, this->callback != 0)) {
      (*this->callback)
                (this->result,this->cb_arg);
      this->callback = 0;
    }
    (**(code **)(this->f_20 /*int **/ + 0xc))();
  }
  return 0;
}

// JP: 0x003942f0  mSetupBG__10dataAccessFv  size 0x47c
// dataAccess::mSetupBG()
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
void mSetupBG__10dataAccessFv(dataAccess *this)
{
  u32 uVar1;
  u64 uVar2;
  long lVar3;
  int iVar4;
  u32 auStack_60 [7];
  u32 uStack_44;
  u32 uStack_40;
  u32 uStack_3c;
  u32 uStack_38;
  u32 uStack_34;
  u32 uStack_30;
  u32 uStack_2c;
  u32 uStack_28;
  u32 uStack_24;
  u32 uStack_20;
  u32 uStack_1c;
  u32 uStack_18;
  u32 uStack_14;
  int iStack_10;
  auStack_60[0] = (u32)__5987;
  auStack_60[1] = (u32)((ulong)__5987 >> 0x20);
  auStack_60[2] = DAT_003f9d68;
  auStack_60[3] = DAT_003f9d6c;
  auStack_60[4] = (u32)_DAT_003f9d70;
  auStack_60[5] = (u32)((ulong)_DAT_003f9d70 >> 0x20);
  auStack_60[6] = DAT_003f9d78;
  uStack_44 = DAT_003f9d7c;
  uStack_40 = (u32)_DAT_003f9d80;
  uStack_3c = (u32)((ulong)_DAT_003f9d80 >> 0x20);
  uStack_38 = DAT_003f9d88;
  uStack_34 = DAT_003f9d8c;
  uStack_30 = (u32)_DAT_003f9d90;
  uStack_2c = (u32)((ulong)_DAT_003f9d90 >> 0x20);
  uStack_28 = DAT_003f9d98;
  uStack_24 = DAT_003f9d9c;
  uStack_20 = (u32)_DAT_003f9da0;
  uStack_1c = (u32)((ulong)_DAT_003f9da0 >> 0x20);
  uStack_18 = DAT_003f9da8;
  uStack_14 = DAT_003f9dac;
  iStack_10 = this;
  if (this->mode == 0) {
    Order__13MenuDataTableFPCc
              (sm_pSubstance__15SaveMenuSection + 0x10,*(u32 *)(DAT_00421624 + 0x20));
  }
  uVar1 = m_pTex;
  uVar2 = GetFileEntry(m_pTex,0x13);
  CreateFont__4FontFiPUc(2,uVar2);
  uVar2 = GetFileEntry(uVar1,0x12);
  CreateFont__4FontFiPUc(3,uVar2);
  lVar3 = __nw__FUi(0x148);
  uVar1 = 0;
  if (lVar3 != 0) {
    uVar1 = __ct__7primWinFv(lVar3);
  }
  *(u32 *)(iStack_10 + 0x38) = uVar1;
  uVar1 = *(u32 *)(iStack_10 + 0x38);
  initialize__7primWinFP7primTex(uVar1,m_pPT);
  setItem__7primWinFiii(uVar1,5,4,1);
  for (iVar4 = 0; iVar4 < 4; iVar4 = iVar4 + 1) {
    if ((iVar4 == 2) && (*(int *)(iStack_10 + 0xa8) == 2)) {
      setTex__7primWinFiiii(uVar1,4,2,0x48,0x20);
    }
    else {
      setTex__7primWinFiiii(uVar1,iVar4,iVar4,auStack_60[iVar4 * 4 + 2],auStack_60[iVar4 * 4 + 3]);
    }
    createTexPoly__7primWinFiiiiii
              (uVar1,iVar4,iVar4,auStack_60[iVar4 * 4],auStack_60[iVar4 * 4 + 1],0,0);
  }
  if (*(int *)(iStack_10 + 0xa8) != 2) {
    setTexBlock__7primWinFiii(uVar1,2,0,*(u32 *)(iStack_10 + 0xa8));
  }
  setPolySize__7primWinFiff(0x40000000,0x40000000,uVar1,0);
  setPolyRGBA__7primWinFiiiii(uVar1,3,0x80,0x80,0x80,0);
  setPolyFadeScroll__7primWinFiii(uVar1,2,1,0x10);
  setTextArea__7primWinFiiib(uVar1,4,0x200,0x40,1);
  if (*(int *)(iStack_10 + 0xa8) == 2) {
    createText__7primWinFiiiiPciib
              (uVar1,0,4,0xffffffffffffff54,0x14,
               *(u32 *)(dataMess_bg_rubi_J + *(int *)(iStack_10 + 0xa8) * 4),0,3);
  }
  else {
    createText__7primWinFiiiiPciib
              (uVar1,0,4,uStack_20,uStack_1c,
               *(u32 *)(dataMess_bg_rubi_J + *(int *)(iStack_10 + 0xa8) * 4),0,3);
  }
  setTextFadeScroll__7primWinFiii(uVar1,0,1,0x10);
  buildWin__7primWinFiiiiii(uVar1,1,0,0,0,0,0);
  fadein__7primWinFi(uVar1,0x10);
  if (*(int *)(iStack_10 + 0xa8) == 2) {
    mSetupInitialWarning__10dataAccessFv(iStack_10);
  }
  else {
    mSetupSelectDevice__10dataAccessFv(iStack_10);
  }
  return;
}

// JP: 0x00394770  mReleaseBG__10dataAccessFv  size 0xa8
// dataAccess::mReleaseBG()
void mReleaseBG__10dataAccessFv(dataAccess *this)
{
  if (this->fader != 0) {
    DelayDeleteRequest__7primWinFv(this->fader);
    this->fader = 0;
  }
  ClearFont__4FontFi(2);
  ClearFont__4FontFi(3);
  if (this->mode == 0) {
    Release__13MenuDataTableFv(sm_pSubstance__15SaveMenuSection + 0x10);
  }
  return;
}

// JP: 0x00394820  mSetupSelectDevice__10dataAccessFv  size 0x4b0
// dataAccess::mSetupSelectDevice()
void mSetupSelectDevice__10dataAccessFv(dataAccess *this)
{
  u64 uVar1;
  long lVar2;
  u64 uVar3;
  u32 uVar4;
  u32 uVar5;
  u32 uVar6;
  u32 uVar7;
  int iVar8;
  u64 *puVar9;
  u64 *puVar10;
  u64 uStack_180;
  uint auStack_178 [90];
  int iStack_10;
  puVar10 = (u64 *)&_6043;
  puVar9 = &uStack_180;
  iVar8 = 0xb;
  do {
    uVar3 = *puVar10;
    uVar6 = *(u32 *)(puVar10 + 1);
    uVar7 = *(u32 *)((int)puVar10 + 0xc);
    uVar1 = puVar10[2];
    uVar4 = *(u32 *)(puVar10 + 3);
    uVar5 = *(u32 *)((int)puVar10 + 0x1c);
    puVar10 = puVar10 + 4;
    iVar8 = iVar8 + -1;
    *(int *)puVar9 = (int)uVar3;
    *(int *)((int)puVar9 + 4) = (int)((ulong)uVar3 >> 0x20);
    *(u32 *)(puVar9 + 1) = uVar6;
    *(u32 *)((int)puVar9 + 0xc) = uVar7;
    *(int *)(puVar9 + 2) = (int)uVar1;
    *(int *)((int)puVar9 + 0x14) = (int)((ulong)uVar1 >> 0x20);
    *(u32 *)(puVar9 + 3) = uVar4;
    *(u32 *)((int)puVar9 + 0x1c) = uVar5;
    puVar9 = puVar9 + 4;
  } while (0 < iVar8);
  *puVar9 = *puVar10;
  this->device_sel = 0;
  this->f_84 /*u32 **/ = 3;
  iStack_10 = this;
  lVar2 = __nw__FUi(0x148);
  uVar4 = 0;
  if (lVar2 != 0) {
    uVar4 = __ct__7primWinFv(lVar2);
  }
  *(u32 *)(iStack_10 + 0x3c) = uVar4;
  uVar4 = *(u32 *)(iStack_10 + 0x3c);
  initialize__7primWinFP7primTex(uVar4,m_pPT);
  setItem__7primWinFiii(uVar4,3,0xb,*(int *)(iStack_10 + 0x84) * 2 + 1);
  setMenuTex__7primWinFP11MenuTextureiii(uVar4,0x421898,1,0,0);
  for (iVar8 = 0; iVar8 < 10; iVar8 = iVar8 + 1) {
    createTexPoly__7primWinFiiiiii
              (uVar4,iVar8,*(u32 *)((int)&uStack_180 + iVar8 * 0x24),
               auStack_178[iVar8 * 9 + -1],auStack_178[iVar8 * 9],0,0);
    uVar3 = getPP__7primWinFi(uVar4,iVar8);
    (**(code **)(*(int *)((int)uVar3 + 8) + 0x28))
              ((float)(int)auStack_178[iVar8 * 9 + 1],(float)(int)auStack_178[iVar8 * 9 + 2]);
    SetUV__11MenuPolygonFUsUsUsUs
              (uVar3,auStack_178[iVar8 * 9 + 3] & 0xffff,auStack_178[iVar8 * 9 + 4] & 0xffff,
               auStack_178[iVar8 * 9 + 5] & 0xffff,auStack_178[iVar8 * 9 + 6] & 0xffff);
  }
  createPoly__7primWinFiiiiii(uVar4,10,0,0x14,0x52,0x154,0x74);
  setPolyRGBA__7primWinFiiiiii(uVar4,10,0,0x41,0x41,0x4e,0x4c);
  setPolyRGBA__7primWinFiiiiii(uVar4,10,2,0x41,0x41,0x4e,0x4c);
  setPolyRGBA__7primWinFiiiiii(uVar4,10,1,10,8,10,0x4c);
  setPolyRGBA__7primWinFiiiiii(uVar4,10,3,10,8,10,0x4c);
  setTextArea__7primWinFiiib(uVar4,2,0x280,0x180,1);
  for (iVar8 = 0; iVar8 < *(int *)(iStack_10 + 0x84); iVar8 = iVar8 + 1) {
    createText__7primWinFiiiiPciib
              (uVar4,iVar8,2,0x60,iVar8 * 0x18 + 0x7a,
               *(u32 *)(dataMess_selectDevice_J + iVar8 * 4),0,0);
    createText__7primWinFiiiiPciib
              (uVar4,*(int *)(iStack_10 + 0x84) + iVar8,2,0xc,0x1a0,
               *(u32 *)(dataMess_selectDeviceNote_J + iVar8 * 4),0,0);
    *(int *)(iStack_10 + iVar8 * 0xc + 0x50) = iVar8;
    *(int *)(iStack_10 + iVar8 * 0xc + 0x54) = iVar8 + *(int *)(iStack_10 + 0x84);
    *(u8 *)(iStack_10 + iVar8 * 0xc + 0x58) = 1;
  }
  if (*(char *)(iStack_10 + 0x172) == '\0') {
    *(u8 *)(iStack_10 + 0x70) = 0;
  }
  *(u32 *)(iStack_10 + 0x88) = uVar4;
  createText__7primWinFiiiiPciib
            (uVar4,*(int *)(iStack_10 + 0x84) << 1,2,0x2c,0x5e,
             *(u32 *)(dataMess_selectDeviceTitle_J + *(int *)(iStack_10 + 0xa8) * 4),0,0);
  buildWin__7primWinFiiiiii(uVar4,2,0,0,0,0,0);
  fadein__7primWinFi(uVar4,0x10);
  mSetMainCursor__10dataAccessFi(iStack_10,*(u32 *)(iStack_10 + 0x80));
  mSelectItem__10dataAccessFi(iStack_10,*(u32 *)(iStack_10 + 0x80));
  return;
}

// JP: 0x00394cd0  mSetupQuit__10dataAccessFv  size 0x4d4
// dataAccess::mSetupQuit()
void mSetupQuit__10dataAccessFv(dataAccess *this)
{
  u64 uVar1;
  long lVar2;
  u64 uVar3;
  u32 uVar4;
  u32 uVar5;
  u32 uVar6;
  u32 uVar7;
  int iVar8;
  u64 *puVar9;
  u64 *puVar10;
  u8 *puVar11;
  undefined **ppuVar12;
  u64 uStack_180;
  uint auStack_178 [90];
  int iStack_10;
  puVar10 = (u64 *)&_6072;
  puVar9 = &uStack_180;
  iVar8 = 0xb;
  do {
    uVar3 = *puVar10;
    uVar6 = *(u32 *)(puVar10 + 1);
    uVar7 = *(u32 *)((int)puVar10 + 0xc);
    uVar1 = puVar10[2];
    uVar4 = *(u32 *)(puVar10 + 3);
    uVar5 = *(u32 *)((int)puVar10 + 0x1c);
    puVar10 = puVar10 + 4;
    iVar8 = iVar8 + -1;
    *(int *)puVar9 = (int)uVar3;
    *(int *)((int)puVar9 + 4) = (int)((ulong)uVar3 >> 0x20);
    *(u32 *)(puVar9 + 1) = uVar6;
    *(u32 *)((int)puVar9 + 0xc) = uVar7;
    *(int *)(puVar9 + 2) = (int)uVar1;
    *(int *)((int)puVar9 + 0x14) = (int)((ulong)uVar1 >> 0x20);
    *(u32 *)(puVar9 + 3) = uVar4;
    *(u32 *)((int)puVar9 + 0x1c) = uVar5;
    puVar9 = puVar9 + 4;
  } while (0 < iVar8);
  *puVar9 = *puVar10;
  if (this->mode == 1) {
    puVar11 = dataMess_loadQuit_J;
    ppuVar12 = &dataMess_loadQuitNote_J;
  }
  else {
    puVar11 = dataMess_saveQuit_J;
    ppuVar12 = (undefined **)&dataMess_saveQuitNote_J;
  }
  this->device_sel = 1;
  this->f_84 /*u32 **/ = 2;
  iStack_10 = this;
  lVar2 = __nw__FUi(0x148);
  uVar4 = 0;
  if (lVar2 != 0) {
    uVar4 = __ct__7primWinFv(lVar2);
  }
  *(u32 *)(iStack_10 + 0x40) = uVar4;
  uVar4 = *(u32 *)(iStack_10 + 0x40);
  initialize__7primWinFP7primTex(uVar4,m_pPT);
  setItem__7primWinFiii(uVar4,3,0xb,*(int *)(iStack_10 + 0x84) * 2 + 1);
  setMenuTex__7primWinFP11MenuTextureiii(uVar4,0x421898,1,0,0);
  for (iVar8 = 0; iVar8 < 10; iVar8 = iVar8 + 1) {
    createTexPoly__7primWinFiiiiii
              (uVar4,iVar8,*(u32 *)((int)&uStack_180 + iVar8 * 0x24),
               auStack_178[iVar8 * 9 + -1],auStack_178[iVar8 * 9],0,0);
    uVar3 = getPP__7primWinFi(uVar4,iVar8);
    (**(code **)(*(int *)((int)uVar3 + 8) + 0x28))
              ((float)(int)auStack_178[iVar8 * 9 + 1],(float)(int)auStack_178[iVar8 * 9 + 2]);
    SetUV__11MenuPolygonFUsUsUsUs
              (uVar3,auStack_178[iVar8 * 9 + 3] & 0xffff,auStack_178[iVar8 * 9 + 4] & 0xffff,
               auStack_178[iVar8 * 9 + 5] & 0xffff,auStack_178[iVar8 * 9 + 6] & 0xffff);
  }
  createPoly__7primWinFiiiiii(uVar4,10,0,0x14,0x52,0xf0,0x60);
  setPolyRGBA__7primWinFiiiiii(uVar4,10,0,0,0,0,0x60);
  setPolyRGBA__7primWinFiiiiii(uVar4,10,1,0,0,0,0x60);
  setPolyRGBA__7primWinFiiiiii(uVar4,10,2,0,0,0,0x20);
  setPolyRGBA__7primWinFiiiiii(uVar4,10,3,0,0,0,0x20);
  setTextArea__7primWinFiiib(uVar4,2,0x280,0x180,1);
  for (iVar8 = 0; iVar8 < *(int *)(iStack_10 + 0x84); iVar8 = iVar8 + 1) {
    createText__7primWinFiiiiPciib
              (uVar4,iVar8,2,0x60,iVar8 * 0x1a + 0x78,*(u32 *)(puVar11 + iVar8 * 4),0,0);
    createText__7primWinFiiiiPciib
              (uVar4,*(int *)(iStack_10 + 0x84) + iVar8,2,0xc,0x1a0,ppuVar12[iVar8],0,0);
    *(int *)(iStack_10 + iVar8 * 0xc + 0x50) = iVar8;
    *(int *)(iStack_10 + iVar8 * 0xc + 0x54) = iVar8 + *(int *)(iStack_10 + 0x84);
    *(u8 *)(iStack_10 + iVar8 * 0xc + 0x58) = 1;
  }
  *(u32 *)(iStack_10 + 0x88) = uVar4;
  createText__7primWinFiiiiPciib
            (uVar4,*(int *)(iStack_10 + 0x84) << 1,2,0x2c,0x5e,
             *(u32 *)(puVar11 + *(int *)(iStack_10 + 0x84) * 4),0,0);
  buildWin__7primWinFiiiiii(uVar4,2,0,0,0,0,0);
  fadein__7primWinFi(uVar4,0x10);
  mSetMainCursor__10dataAccessFi(iStack_10,*(u32 *)(iStack_10 + 0x80));
  mSelectItem__10dataAccessFi(iStack_10,*(u32 *)(iStack_10 + 0x80));
  return;
}

// JP: 0x003951b0  mSetupProgressCommon__10dataAccessFv  size 0x3ac
// dataAccess::mSetupProgressCommon()
void mSetupProgressCommon__10dataAccessFv(dataAccess *this)
{
  u32 uVar1;
  long lVar2;
  u64 uVar3;
  setTextAlpha__7primWinFii
            (this->win,
             *(u32 *)(this + this->device_sel * 0xc + 0x54),0);
  this->f_a4 /*u32 **/ = 0x10;
  lVar2 = __nw__FUi(0x148);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = __ct__7primWinFv(lVar2);
  }
  this->f_44 /*u32 **/ = uVar1;
  uVar1 = this->f_44 /*u32 **/;
  initialize__7primWinFP7primTex(uVar1,m_pPT);
  setItem__7primWinFiii(uVar1,3,5,4);
  setTex__7primWinFiiii(uVar1,8,0,8,0x14);
  setMenuTex__7primWinFP11MenuTextureiii(uVar1,0x421818,1,0,0);
  setTextArea__7primWinFiiib(uVar1,2,0x280,0x1c0,1);
  createTexPoly__7primWinFiiiiii(uVar1,0,0,0x26,0x110,0,0);
  createTexPoly__7primWinFiiiiii(uVar1,1,0,0x2e,0x110,2,0);
  setPolySize__7primWinFiff(0x42180000,0x3f800000,uVar1,1);
  createTexPoly__7primWinFiiiiii(uVar1,2,0,0x15e,0x110,4,0);
  uVar3 = getPP__7primWinFi(uVar1,1);
  SetUV__11MenuPolygonFUsUsUsUs(uVar3,0x11,1,0x17,0x14);
  createPoly__7primWinFiiiiii(uVar1,3,1,0x2e,0x116,this->f_a4 /*u32 **/,8);
  setPolyRGBA__7primWinFiiiiii(uVar1,3,0,0x2a,0x50,0xa5,0x80);
  setPolyRGBA__7primWinFiiiiii(uVar1,3,1,0x2a,0x50,0xa5,0x80);
  setPolyRGBA__7primWinFiiiiii(uVar1,3,2,0x1e,0xff,0xff,0x80);
  setPolyRGBA__7primWinFiiiiii(uVar1,3,3,0x1e,0xff,0xff,0x80);
  createTexPoly__7primWinFiiiiii(uVar1,4,1,this->f_a4 /*int **/ + 0x22,0x10b,0,0);
  setPolySize__7primWinFiff(0x3f400000,0x3f400000,uVar1,4);
  createText__7primWinFiiiiPciib(uVar1,0,2,0xc,0xf8,dataMess_progress_J,0x34,2);
  createText__7primWinFiiiiPciib(uVar1,1,2,0x3e,0x176,dataMess_progressNote_J,0,0);
  buildWin__7primWinFiiiiii(uVar1,3,0,0,0,0,0);
  fadein__7primWinFi(uVar1,4);
  this->win = uVar1;
  return;
}

// JP: 0x00395560  mSetupProgress__10dataAccessFv  size 0x80
// dataAccess::mSetupProgress()
void mSetupProgress__10dataAccessFv(dataAccess *this)
{
  mSetupProgressCommon__10dataAccessFv(this);
  createText__7primWinFiiiiPciib
            (this->win,2,2,0x26,0x12e,
             *(u32 *)(dataMess_progressDevice_J + this->dev_kind * 4),0,0);
  mReleaseMainCursor__10dataAccessFv(this);
  return;
}

// JP: 0x003955e0  mSetupWarning__10dataAccessFPc  size 0x90
// dataAccess::mSetupWarning(char*)
void mSetupWarning__10dataAccessFPc(dataAccess *this,u32 param_2)
{
  u32 uVar1;
  setPolyRGBA__7primWinFiiiii(this->fader,3,0x80,0x80,0x80,0x80);
  setTextAlpha__7primWinFii(this->win,2,0);
  this->progress = 0;
  uVar1 = addMessage__7primWinFiiPcib(this->win,0x20,0x12d,param_2,0,1);
  this->f_8c /*u32 **/ = uVar1;
  return;
}

// JP: 0x00395670  mReleaseWarning__10dataAccessFv  size 0x40
// dataAccess::mReleaseWarning()
void mReleaseWarning__10dataAccessFv(dataAccess *this)
{
  setPolyRGBA__7primWinFiiiii(this->fader,3,0x80,0x80,0x80,0);
  return;
}

// JP: 0x003956b0  mSetupSelectFile__10dataAccessFv  size 0x404
// dataAccess::mSetupSelectFile()
void mSetupSelectFile__10dataAccessFv(dataAccess *this)
{
  int iVar1;
  u32 uVar2;
  long lVar3;
  char acStack_220 [520];
  u32 uStack_18;
  u32 uStack_14;
  int iStack_10;
  uStack_18 = *(u32 *)(DAT_00421e90 + 0x10);
  this->f_144 /*u32 **/ = uStack_18;
  if (this->dev_kind == 2) {
    iVar1 = this->f_144 /*int **/;
    if (iVar1 < 0) {
      iVar1 = iVar1 + 0x3ff;
    }
    this->f_144 /*int **/ = iVar1 >> 10;
  }
  uStack_14 = uStack_18;
  iStack_10 = this;
  if (this->f_144 /*int **/ < 10000) {
    sprintf(acStack_220,*(char **)(dataMess_deviceInfo_J + this->dev_kind * 4),
            this->f_144 /*u32 **/);
  }
  else {
    iVar1 = this->f_144 /*int **/;
    if (iVar1 < 0) {
      iVar1 = iVar1 + 0x3ff;
    }
    sprintf(acStack_220,(char *)dataMess_deviceInfo_J._12_4_,iVar1 >> 10);
  }
  lVar3 = __nw__FUi(0x148);
  uVar2 = 0;
  if (lVar3 != 0) {
    uVar2 = __ct__7primWinFv(lVar3);
  }
  *(u32 *)(iStack_10 + 0x48) = uVar2;
  uVar2 = *(u32 *)(iStack_10 + 0x48);
  initialize__7primWinFP7primTex(uVar2,m_pPT);
  setItem__7primWinFiii(uVar2,3,0,4);
  setTextArea__7primWinFiiib(uVar2,2,0x280,0xe0,1);
  createText__7primWinFiiiiPciib(uVar2,0,2,0xc,0x3a,acStack_220,0,0);
  createText__7primWinFiiiiPciib(uVar2,1,2,0xc,0x1a0,dataMess_selectFileNote_J,0,0);
  buildWin__7primWinFiiiiii(uVar2,2,0,0,0,0,0);
  fadein__7primWinFi(uVar2,4);
  *(u32 *)(iStack_10 + 0x88) = uVar2;
  *(u32 *)(iStack_10 + 0x110) = 1;
  lVar3 = __nw__FUi(0x34);
  uVar2 = 0;
  if (lVar3 != 0) {
    uVar2 = __ct__12dispSaveFileFiiiQ210dataAccess10ACCESSMODEP7primTexPPc
                      (lVar3,*(u32 *)(iStack_10 + 0x134),1,0,
                       *(u32 *)(iStack_10 + 0xa8),m_pPT,0x3f9d20);
  }
  *(u32 *)(iStack_10 + 0x11c) = uVar2;
  if (*(int *)(iStack_10 + 0x134) + 1 < *(int *)(iStack_10 + 0x138)) {
    *(u32 *)(iStack_10 + 0x114) = 2;
    lVar3 = __nw__FUi(0x34);
    uVar2 = 0;
    if (lVar3 != 0) {
      uVar2 = __ct__12dispSaveFileFiiiQ210dataAccess10ACCESSMODEP7primTexPPc
                        (lVar3,*(int *)(iStack_10 + 0x134) + 1,2,1,*(u32 *)(iStack_10 + 0xa8)
                         ,m_pPT,0x3f9d20);
    }
    *(u32 *)(iStack_10 + 0x120) = uVar2;
    move__12dispSaveFileFiii(*(u32 *)(iStack_10 + 0x120),0,0,0xffffffffffffffc0);
  }
  else {
    *(u32 *)(iStack_10 + 0x114) = 0xffffffff;
    *(u32 *)(iStack_10 + 0x120) = 0;
  }
  *(u32 *)(iStack_10 + 0x118) = 0xffffffff;
  *(u32 *)(iStack_10 + 0x124) = 0;
  lVar3 = __nw__FUi(0x3c);
  uVar2 = 0;
  if (lVar3 != 0) {
    uVar2 = __ct__12udScrollMarkFv(lVar3);
  }
  *(u32 *)(iStack_10 + 0x30) = uVar2;
  initialize__12udScrollMarkFP7primTexiiiii
            (*(u32 *)(iStack_10 + 0x30),m_pPT,*(u32 *)(iStack_10 + 0x134),
             *(u32 *)(iStack_10 + 0x138),0xe0,0x22,0xac);
  return;
}

// JP: 0x00395ac0  mReleaseSelectFile__10dataAccessFv  size 0xbc
// dataAccess::mReleaseSelectFile()
void mReleaseSelectFile__10dataAccessFv(dataAccess *this)
{
  int iVar1;
  for (iVar1 = 0; iVar1 < 3; iVar1 = iVar1 + 1) {
    if (*(int *)(this + iVar1 * 4 + 0x11c) != 0) {
      __dt__12dispSaveFileFv(*(u32 *)(this + iVar1 * 4 + 0x11c),1);
      *(u32 *)(this + iVar1 * 4 + 0x11c) = 0;
    }
  }
  if (this->f_48 /*int **/ != 0) {
    DelayDeleteRequest__7primWinFv(this->f_48 /*u32 **/);
    this->f_48 /*u32 **/ = 0;
  }
  return;
}

// JP: 0x00395b80  mSetupQuerySaveLoad__10dataAccessFv  size 0x46c
// dataAccess::mSetupQuerySaveLoad()
void mSetupQuerySaveLoad__10dataAccessFv(dataAccess *this)
{
  u32 uVar1;
  long lVar2;
  int iVar3;
  u8 *puVar4;
  undefined **ppuVar5;
  int iVar6;
  iVar6 = 0;
  if (this->mode == 1) {
    puVar4 = dataMess_loadQueryLoad_J;
    ppuVar5 = &dataMess_loadQueryLoadNote_J;
  }
  else {
    iVar6 = 0x14;
    if (*(char *)(this + this->cur_slot + 0xac) == '\0') {
      puVar4 = dataMess_saveQueryOverWrite_J;
      ppuVar5 = (undefined **)&dataMess_saveQueryOverWriteNote_J;
    }
    else {
      puVar4 = dataMess_saveQuerySave_J;
      ppuVar5 = (undefined **)&dataMess_saveQuerySaveNote_J;
    }
  }
  setTextAlpha__7primWinFii(this->f_48 /*u32 **/,1,0);
  iVar3 = 0;
  do {
    if (2 < iVar3) {
LAB_00395ca0:
      this->device_sel = 1;
      this->f_84 /*u32 **/ = 2;
      lVar2 = __nw__FUi(0x148);
      uVar1 = 0;
      if (lVar2 != 0) {
        uVar1 = __ct__7primWinFv(lVar2);
      }
      this->popup = uVar1;
      uVar1 = this->popup;
      initialize__7primWinFP7primTex(uVar1,m_pPT);
      setItem__7primWinFiii(uVar1,2,1,this->f_84 /*int **/ * 2 + 1);
      setTextArea__7primWinFiiib(uVar1,1,0x280,0x180,1);
      for (iVar3 = 0; iVar3 < this->f_84 /*int **/; iVar3 = iVar3 + 1) {
        createText__7primWinFiiiiPciib
                  (uVar1,iVar3,1,0x40,iVar6 + 0xd6 + iVar3 * 0x16,
                   *(u32 *)(puVar4 + iVar3 * 4),0,0);
        createText__7primWinFiiiiPciib
                  (uVar1,this->f_84 /*int **/ + iVar3,1,0xc,0x1a0,ppuVar5[iVar3],0,0);
        *(int *)(this + iVar3 * 0xc + 0x50) = iVar3;
        *(int *)(this + iVar3 * 0xc + 0x54) = iVar3 + this->f_84 /*int **/;
        *(u8 *)(this + iVar3 * 0xc + 0x58) = 1;
      }
      this->win = uVar1;
      createText__7primWinFiiiiPciib
                (uVar1,this->f_84 /*int **/ << 1,1,0xc,0xb4,
                 *(u32 *)(puVar4 + this->f_84 /*int **/ * 4),0,0);
      createPoly__7primWinFiiiiii(uVar1,0,0,0,0xb0,0x200,0x1c);
      setPolyRGBA__7primWinFiiiiii(uVar1,0,0,0,0,0,0x60);
      setPolyRGBA__7primWinFiiiiii(uVar1,0,1,0,0,0,0x60);
      setPolyRGBA__7primWinFiiiiii(uVar1,0,2,0,0,0,0);
      setPolyRGBA__7primWinFiiiiii(uVar1,0,3,0,0,0,0);
      buildWin__7primWinFiiiiii(uVar1,0xd,0,0,0,0,0);
      fadein__7primWinFi(uVar1,0x10);
      mSetMainCursor__10dataAccessFi(this,this->device_sel);
      mSelectItem__10dataAccessFi(this,this->device_sel);
      return;
    }
    if (*(int *)(this + iVar3 * 4 + 0x110) == 2) {
      setDisp__12dispSaveFileFb(*(u32 *)(this + iVar3 * 4 + 0x11c),0);
      goto LAB_00395ca0;
    }
    iVar3 = iVar3 + 1;
  } while( true );
}

// JP: 0x00395ff0  mRecoverSelectFile__10dataAccessFv  size 0x118
// dataAccess::mRecoverSelectFile()
void mRecoverSelectFile__10dataAccessFv(dataAccess *this)
{
  u32 uVar1;
  long lVar2;
  int iVar3;
  setTextAlpha__7primWinFii(this->f_48 /*u32 **/,1,0x80);
  iVar3 = 0;
  do {
    if (2 < iVar3) {
LAB_00396080:
      lVar2 = __nw__FUi(0x3c);
      uVar1 = 0;
      if (lVar2 != 0) {
        uVar1 = __ct__12udScrollMarkFv(lVar2);
      }
      this->scrollmark = uVar1;
      initialize__12udScrollMarkFP7primTexiiiii
                (this->scrollmark,m_pPT,this->cur_slot,
                 this->slot_count,0xe0,0x22,0xac);
      this->win = this->f_48 /*u32 **/;
      return;
    }
    if (*(int *)(this + iVar3 * 4 + 0x110) == 2) {
      setDisp__12dispSaveFileFb(*(u32 *)(this + iVar3 * 4 + 0x11c),1);
      goto LAB_00396080;
    }
    iVar3 = iVar3 + 1;
  } while( true );
}

// JP: 0x00396110  mSetupProgressSaveLoad__10dataAccessFv  size 0x2d4
// dataAccess::mSetupProgressSaveLoad()
void mSetupProgressSaveLoad__10dataAccessFv(dataAccess *this)
{
  if (this->mode == 1) {
    *(undefined ***)(this + 0x140) = &dataMess_loadProgressLoad_J;
    Load__8SaveDataFUc(0x421e70,this->cur_slot & 0xff);
    this->progress = 1;
  }
  else {
    if (*(char *)(this + this->cur_slot + 0xac) == '\0') {
      this->f_140 /*u8 **/ = dataMess_saveProgressOverWrite_J;
    }
    else {
      this->f_140 /*u8 **/ = dataMess_saveProgressSave_J;
    }
    this->info =
         *(int *)(DAT_00421e90 + 0x1c) + *(int *)(*(int *)(DAT_00421e90 + 0x1c) + 0x1c) +
         (this->cur_slot & 0xff) * 0x60;
    *this->info = (char)this->cur_slot;
    if ((long)((ulong)*(u8 *)(DAT_00421e90 + 5) << 0x3e) < 0) {
      Save__8SaveDataFUc(0x421e70,this->cur_slot & 0xff);
      printf(_6293,this->cur_slot);
      this->progress = 1;
    }
    else {
      CreateSystem__8SaveDataFv(0x421e70);
      this->progress = 2;
    }
  }
  mSetupProgressCommon__10dataAccessFv(this);
  createText__7primWinFiiiiPciib
            (this->win,2,2,0x26,0x12e,*this->f_140 /*u32 **/,0,0);
  createText__7primWinFiiiiPciib
            (this->win,3,2,0x26,0x12e,
             *(u32 *)(this->f_140 /*int **/ + 4),0,0);
  setTextAlpha__7primWinFii(this->win,3,0);
  mReleaseMainCursor__10dataAccessFv(this);
  return;
}

// JP: 0x003963f0  mSetupFormat__10dataAccessFv  size 0x488
// dataAccess::mSetupFormat()
void mSetupFormat__10dataAccessFv(dataAccess *this)
{
  u64 uVar1;
  long lVar2;
  u64 uVar3;
  u32 uVar4;
  u32 uVar5;
  u32 uVar6;
  u32 uVar7;
  int iVar8;
  u64 *puVar9;
  u64 *puVar10;
  u64 uStack_180;
  uint auStack_178 [90];
  int iStack_10;
  puVar10 = (u64 *)&_6299;
  puVar9 = &uStack_180;
  iVar8 = 0xb;
  do {
    uVar3 = *puVar10;
    uVar6 = *(u32 *)(puVar10 + 1);
    uVar7 = *(u32 *)((int)puVar10 + 0xc);
    uVar1 = puVar10[2];
    uVar4 = *(u32 *)(puVar10 + 3);
    uVar5 = *(u32 *)((int)puVar10 + 0x1c);
    puVar10 = puVar10 + 4;
    iVar8 = iVar8 + -1;
    *(int *)puVar9 = (int)uVar3;
    *(int *)((int)puVar9 + 4) = (int)((ulong)uVar3 >> 0x20);
    *(u32 *)(puVar9 + 1) = uVar6;
    *(u32 *)((int)puVar9 + 0xc) = uVar7;
    *(int *)(puVar9 + 2) = (int)uVar1;
    *(int *)((int)puVar9 + 0x14) = (int)((ulong)uVar1 >> 0x20);
    *(u32 *)(puVar9 + 3) = uVar4;
    *(u32 *)((int)puVar9 + 0x1c) = uVar5;
    puVar9 = puVar9 + 4;
  } while (0 < iVar8);
  *puVar9 = *puVar10;
  this->device_sel = 1;
  this->f_84 /*u32 **/ = 2;
  iStack_10 = this;
  lVar2 = __nw__FUi(0x148);
  uVar4 = 0;
  if (lVar2 != 0) {
    uVar4 = __ct__7primWinFv(lVar2);
  }
  *(u32 *)(iStack_10 + 0x4c) = uVar4;
  uVar4 = *(u32 *)(iStack_10 + 0x4c);
  initialize__7primWinFP7primTex(uVar4,m_pPT);
  setItem__7primWinFiii(uVar4,3,0xb,*(int *)(iStack_10 + 0x84) * 2 + 1);
  setMenuTex__7primWinFP11MenuTextureiii(uVar4,0x421898,1,0,0);
  for (iVar8 = 0; iVar8 < 10; iVar8 = iVar8 + 1) {
    createTexPoly__7primWinFiiiiii
              (uVar4,iVar8,*(u32 *)((int)&uStack_180 + iVar8 * 0x24),
               auStack_178[iVar8 * 9 + -1],auStack_178[iVar8 * 9],0,0);
    uVar3 = getPP__7primWinFi(uVar4,iVar8);
    (**(code **)(*(int *)((int)uVar3 + 8) + 0x28))
              ((float)(int)auStack_178[iVar8 * 9 + 1],(float)(int)auStack_178[iVar8 * 9 + 2]);
    SetUV__11MenuPolygonFUsUsUsUs
              (uVar3,auStack_178[iVar8 * 9 + 3] & 0xffff,auStack_178[iVar8 * 9 + 4] & 0xffff,
               auStack_178[iVar8 * 9 + 5] & 0xffff,auStack_178[iVar8 * 9 + 6] & 0xffff);
  }
  createPoly__7primWinFiiiiii(uVar4,10,0,0x14,0x52,0x154,0x8c);
  setPolyRGBA__7primWinFiiiiii(uVar4,10,0,0,0,0,0x60);
  setPolyRGBA__7primWinFiiiiii(uVar4,10,1,0,0,0,0x60);
  setPolyRGBA__7primWinFiiiiii(uVar4,10,2,0,0,0,0x20);
  setPolyRGBA__7primWinFiiiiii(uVar4,10,3,0,0,0,0x20);
  setTextArea__7primWinFiiib(uVar4,2,0x280,0x180,1);
  for (iVar8 = 0; iVar8 < *(int *)(iStack_10 + 0x84); iVar8 = iVar8 + 1) {
    createText__7primWinFiiiiPciib
              (uVar4,iVar8,2,100,iVar8 * 0x18 + 0xa8,(&dataMess_queryYN_J)[iVar8],0,0);
    createText__7primWinFiiiiPciib
              (uVar4,*(int *)(iStack_10 + 0x84) + iVar8,2,0xc,0x1a0,
               (&dataMess_queryFormatSlotNote_J)[iVar8],0,0);
    *(int *)(iStack_10 + iVar8 * 0xc + 0x50) = iVar8;
    *(int *)(iStack_10 + iVar8 * 0xc + 0x54) = iVar8 + *(int *)(iStack_10 + 0x84);
    *(u8 *)(iStack_10 + iVar8 * 0xc + 0x58) = 1;
  }
  *(u32 *)(iStack_10 + 0x88) = uVar4;
  createText__7primWinFiiiiPciib
            (uVar4,*(int *)(iStack_10 + 0x84) << 1,2,0x2c,0x5e,
             (&dataMess_queryFormatSlotTitle_J)[*(int *)(iStack_10 + 0x16c)],0,0);
  buildWin__7primWinFiiiiii(uVar4,3,0,0,0,0,0);
  fadein__7primWinFi(uVar4,0x10);
  mSetMainCursor__10dataAccessFi(iStack_10,*(u32 *)(iStack_10 + 0x80));
  mSelectItem__10dataAccessFi(iStack_10,*(u32 *)(iStack_10 + 0x80));
  return;
}

// JP: 0x00396880  mSetupProgressFormat__10dataAccessFv  size 0xbc
// dataAccess::mSetupProgressFormat()
void mSetupProgressFormat__10dataAccessFv(dataAccess *this)
{
  mSetupProgressCommon__10dataAccessFv(this);
  createText__7primWinFiiiiPciib
            (this->win,2,2,0x26,0x12e,dataMess_progressFormatSlot1_J,0,0);
  createText__7primWinFiiiiPciib
            (this->win,3,2,0x26,0x12e,PTR__5489_003f9c74,0,0);
  setTextAlpha__7primWinFii(this->win,3,0);
  mReleaseMainCursor__10dataAccessFv(this);
  return;
}

// JP: 0x00396940  mSetFileViewScroll__10dataAccessFi  size 0x1b8
// dataAccess::mSetFileViewScroll(int)
void mSetFileViewScroll__10dataAccessFi(dataAccess *this,int param_2)
{
  bool bVar1;
  u32 uVar2;
  long lVar3;
  int iVar4;
  int iVar5;
  u32 uVar6;
  bVar1 = false;
  for (iVar4 = 0; iVar4 < 3; iVar4 = iVar4 + 1) {
    if (*(int *)(this + iVar4 * 4 + 0x110) == -1) {
      if (!bVar1) {
        bVar1 = true;
        uVar6 = 0;
        iVar5 = this->cur_slot + -1;
        if (param_2 == 0x10) {
          uVar6 = 3;
          iVar5 = this->cur_slot + 2;
        }
        if (iVar5 < this->slot_count) {
          *(u32 *)(this + iVar4 * 4 + 0x110) = uVar6;
          lVar3 = __nw__FUi(0x34);
          uVar2 = 0;
          if (lVar3 != 0) {
            uVar2 = __ct__12dispSaveFileFiiiQ210dataAccess10ACCESSMODEP7primTexPPc
                              (lVar3,iVar5,uVar6,iVar4,this->mode,m_pPT,
                               0x3f9d20);
          }
          *(u32 *)(this + iVar4 * 4 + 0x11c) = uVar2;
          setMove__12dispSaveFileFi(*(u32 *)(this + iVar4 * 4 + 0x11c),param_2);
          move__12dispSaveFileFiii
                    (*(u32 *)(this + iVar4 * 4 + 0x11c),0,0,0xffffffffffffff80);
        }
      }
    }
    else {
      setMove__12dispSaveFileFi(*(u32 *)(this + iVar4 * 4 + 0x11c),param_2);
    }
  }
  return;
}

// JP: 0x00396b00  mFinishFileViewScroll__10dataAccessFi  size 0x208
// dataAccess::mFinishFileViewScroll(int)
void mFinishFileViewScroll__10dataAccessFi(dataAccess *this,int param_2)
{
  int iVar1;
  int iVar2;
  if (param_2 == 0x10) {
    for (iVar2 = 0; iVar2 < 3; iVar2 = iVar2 + 1) {
      if (*(int *)(this + iVar2 * 4 + 0x110) == 1) {
        *(u32 *)(this + iVar2 * 4 + 0x110) = 0xffffffff;
        if (*(int *)(this + iVar2 * 4 + 0x11c) != 0) {
          __dt__12dispSaveFileFv(*(u32 *)(this + iVar2 * 4 + 0x11c),1);
          *(u32 *)(this + iVar2 * 4 + 0x11c) = 0;
        }
      }
      else if (*(int *)(this + iVar2 * 4 + 0x110) != -1) {
        iVar1 = this + iVar2 * 4;
        *(int *)(iVar1 + 0x110) = *(int *)(iVar1 + 0x110) + -1;
      }
    }
  }
  else {
    for (iVar2 = 0; iVar2 < 3; iVar2 = iVar2 + 1) {
      if (*(int *)(this + iVar2 * 4 + 0x110) == 2) {
        *(u32 *)(this + iVar2 * 4 + 0x110) = 0xffffffff;
        if (*(int *)(this + iVar2 * 4 + 0x11c) != 0) {
          __dt__12dispSaveFileFv(*(u32 *)(this + iVar2 * 4 + 0x11c),1);
          *(u32 *)(this + iVar2 * 4 + 0x11c) = 0;
        }
      }
      else if (*(int *)(this + iVar2 * 4 + 0x110) != -1) {
        iVar1 = this + iVar2 * 4;
        *(int *)(iVar1 + 0x110) = *(int *)(iVar1 + 0x110) + 1;
      }
    }
  }
  return;
}

// JP: 0x00396d10  mMoveFileView__10dataAccessFi  size 0x19c
// dataAccess::mMoveFileView(int)
void mMoveFileView__10dataAccessFi(dataAccess *this,int param_2)
{
  int iVar1;
  u64 uVar2;
  u32 uVar3;
  uVar3 = 9;
  uVar2 = 0;
  if (param_2 == 0x10) {
    uVar3 = 0xfffffff7;
  }
  for (iVar1 = 0; iVar1 < 3; iVar1 = iVar1 + 1) {
    if (param_2 == 0x10) {
      if (*(int *)(this + iVar1 * 4 + 0x110) == 1) {
        uVar2 = 0xfffffffffffffff8;
      }
      if (*(int *)(this + iVar1 * 4 + 0x110) == 2) {
        uVar2 = 4;
      }
      if (*(int *)(this + iVar1 * 4 + 0x110) == 3) {
        uVar2 = 4;
      }
    }
    else {
      if (*(int *)(this + iVar1 * 4 + 0x110) == 0) {
        uVar2 = 8;
      }
      if (*(int *)(this + iVar1 * 4 + 0x110) == 1) {
        uVar2 = 0xfffffffffffffffc;
      }
      if (*(int *)(this + iVar1 * 4 + 0x110) == 2) {
        uVar2 = 0xfffffffffffffffc;
      }
    }
    if (*(int *)(this + iVar1 * 4 + 0x11c) != 0) {
      move__12dispSaveFileFiii(*(u32 *)(this + iVar1 * 4 + 0x11c),0,uVar3,uVar2);
    }
  }
  return;
}

// JP: 0x00396eb0  mReleaseWin__10dataAccessFv  size 0xe0
// dataAccess::mReleaseWin()
void mReleaseWin__10dataAccessFv(dataAccess *this)
{
  if (this->f_3c /*int **/ != 0) {
    DelayDeleteRequest__7primWinFv(this->f_3c /*u32 **/);
    this->f_3c /*u32 **/ = 0;
  }
  if (this->bg != 0) {
    DelayDeleteRequest__7primWinFv(this->bg);
    this->bg = 0;
  }
  if (this->f_44 /*int **/ != 0) {
    DelayDeleteRequest__7primWinFv(this->f_44 /*u32 **/);
    this->f_44 /*u32 **/ = 0;
  }
  if (this->popup != 0) {
    DelayDeleteRequest__7primWinFv(this->popup);
    this->popup = 0;
  }
  if (this->main_cursor != 0) {
    leaveWin__10primCursorFv(this->main_cursor);
  }
  return;
}

// JP: 0x00396f90  mCheckDirKey__10dataAccessFi  size 0x280
// dataAccess::mCheckDirKey(int)
void mCheckDirKey__10dataAccessFi(dataAccess *this,uint param_2)
{
  int iVar1;
  if ((param_2 & 0x10) == 0) {
    if ((param_2 & 0x40) == 0) {
      return;
    }
    iVar1 = this->device_sel;
    do {
      if (this->f_84 /*int **/ + -1 <= iVar1) {
        iVar1 = 0;
        while( true ) {
          if (this->f_84 /*int **/ + -1 <= iVar1) {
            return;
          }
          if (*(char *)(this + iVar1 * 0xc + 0x58) == '\x01') break;
          iVar1 = iVar1 + 1;
        }
        this->device_sel = iVar1;
        play__9primSoundFi(this->snd,0);
        mSelectItem__10dataAccessFi(this,this->device_sel);
        return;
      }
      iVar1 = iVar1 + 1;
    } while (*(char *)(this + iVar1 * 0xc + 0x58) != '\x01');
    this->device_sel = iVar1;
    play__9primSoundFi(this->snd,0);
    mSelectItem__10dataAccessFi(this,this->device_sel);
    return;
  }
  iVar1 = this->device_sel;
  do {
    if (iVar1 == 0) {
      iVar1 = this->f_84 /*int **/;
      do {
        iVar1 = iVar1 + -1;
        if (iVar1 == 0) {
          return;
        }
      } while (*(char *)(this + iVar1 * 0xc + 0x58) != '\x01');
      this->device_sel = iVar1;
      play__9primSoundFi(this->snd,0);
      mSelectItem__10dataAccessFi(this,this->device_sel);
      return;
    }
    iVar1 = iVar1 + -1;
  } while (*(char *)(this + iVar1 * 0xc + 0x58) != '\x01');
  this->device_sel = iVar1;
  play__9primSoundFi(this->snd,0);
  mSelectItem__10dataAccessFi(this,this->device_sel);
  return;
}

// JP: 0x00397210  mSelectItem__10dataAccessFi  size 0x198
// dataAccess::mSelectItem(int)
void mSelectItem__10dataAccessFi(dataAccess *this,int param_2)
{
  int iVar1;
  for (iVar1 = 0; iVar1 < this->f_84 /*int **/; iVar1 = iVar1 + 1) {
    if (iVar1 == param_2) {
      setTextClut__7primWinFii
                (this->win,*(u32 *)(this + iVar1 * 0xc + 0x50),0x10)
      ;
      setTextAlpha__7primWinFii
                (this->win,*(u32 *)(this + iVar1 * 0xc + 0x54),0x80)
      ;
    }
    else {
      if (*(char *)(this + iVar1 * 0xc + 0x58) == '\0') {
        setTextClut__7primWinFii
                  (this->win,*(u32 *)(this + iVar1 * 0xc + 0x50),
                   0x20);
      }
      else {
        setTextClut__7primWinFii
                  (this->win,*(u32 *)(this + iVar1 * 0xc + 0x50),0);
      }
      setTextAlpha__7primWinFii
                (this->win,*(u32 *)(this + iVar1 * 0xc + 0x54),0);
    }
  }
  setItem__10primCursorFP7primWini
            (this->main_cursor,this->win,
             this->device_sel);
  return;
}

// JP: 0x003973b0  mCheckFreeArea__10dataAccessFv  size 0x3c
// dataAccess::mCheckFreeArea()
bool mCheckFreeArea__10dataAccessFv(dataAccess *this)
{
  return 0x62 < this->f_144 /*int **/;
}

// JP: 0x003973f0  mSetMainCursor__10dataAccessFi  size 0x13c
// dataAccess::mSetMainCursor(int)
void mSetMainCursor__10dataAccessFi(dataAccess *this,u32 param_2)
{
  u32 uVar1;
  long lVar2;
  if (this->main_cursor == 0) {
    lVar2 = __nw__FUi(0x10c);
    uVar1 = 0;
    if (lVar2 != 0) {
      uVar1 = __ct__10primCursorFv(lVar2);
    }
    this->main_cursor = uVar1;
    createCursor__10primCursorFiiii(this->main_cursor,0,2,8,10);
    if ((this->f_94 /*float **/ == 0.0) || (this->f_98 /*float **/ == 0.0)) {
      setItem__10primCursorFP7primWini
                (this->main_cursor,this->win,param_2);
      qMove__10primCursorFv(this->main_cursor);
    }
    else {
      setPos__10primCursorFff
                (this->f_94 /*u32 **/,this->f_98 /*u32 **/,
                 this->main_cursor);
      setItem__10primCursorFP7primWini
                (this->main_cursor,this->win,param_2);
    }
  }
  return;
}

// JP: 0x00397530  mReleaseMainCursor__10dataAccessFv  size 0x60
// dataAccess::mReleaseMainCursor()
void mReleaseMainCursor__10dataAccessFv(dataAccess *this)
{
  if (this->main_cursor != 0) {
    DelayDeleteRequest__10primCursorFv(this->main_cursor);
    this->main_cursor = 0;
  }
  this->f_94 /*u32 **/ = 0;
  this->f_98 /*u32 **/ = 0;
  return;
}

// JP: 0x00397590  mGrowProgress__10dataAccessFi  size 0x10c
// dataAccess::mGrowProgress(int)
void mGrowProgress__10dataAccessFi(dataAccess *this,int param_2)
{
  int iVar1;
  if (this->f_a4 /*int **/ < 0x130) {
    this->f_a4 /*int **/ = this->f_a4 /*int **/ + param_2;
    if (0x130 < this->f_a4 /*int **/) {
      this->f_a4 /*u32 **/ = 0x130;
    }
    iVar1 = getPP__7primWinFi(this->win,3);
    VCALL(iVar1, 0x28 /*SetSize*/)((float)this->f_a4 /*int **/,0x41000000);
    iVar1 = getPP__7primWinFi(this->win,4);
    VCALL(iVar1, 0x24 /*SetPosition*/)((float)(this->f_a4 /*int **/ + 0x22),0x43858000);
  }
  return;
}

// JP: 0x003976a0  mInitialDeviceCheck__10dataAccessFi  size 0x131c
// dataAccess::mInitialDeviceCheck(int)
u32 mInitialDeviceCheck__10dataAccessFi(dataAccess *this,uint param_2)
{
  u32 uVar1;
  u64 uVar2;
  long lVar3;
  u8 auStack_130 [256];
  int iStack_30;
  int iStack_2c;
  int iStack_28;
  short sStack_24;
  short sStack_22;
  int iStack_20;
  uint uStack_10;
  iStack_20 = this;
  uStack_10 = param_2;
  switch(this->mode2) {
  case 0:
    this->mode2 = 2;
    checkDeviceAll__13deviceCheckerFv(this->f_15c /*u32 **/);
    break;
  case 1:
    lVar3 = closeDevice__13deviceCheckerFv(this->f_15c /*u32 **/);
    if ((lVar3 != 0) && (lVar3 = isFade__7primWinFv(*(u32 *)(iStack_20 + 0x38)), lVar3 == 0))
    {
      mReleaseWin__10dataAccessFv(iStack_20);
      mReleaseBG__10dataAccessFv(iStack_20);
      *(u32 *)(iStack_20 + 0x150) = 2;
      checkDeviceAll__13deviceCheckerFv(*(u32 *)(iStack_20 + 0x15c));
    }
    break;
  case 2:
    if (*(char *)(this->f_15c /*int **/ + 0x24) != '\0') {
      lVar3 = isHDD__13deviceCheckerFv(this->f_15c /*u32 **/);
      if (lVar3 != 0) {
        *(u8 *)(iStack_20 + 0x172) = 1;
      }
      lVar3 = getActiveDeviceNum__13deviceCheckerFv(*(u32 *)(iStack_20 + 0x15c));
      if (lVar3 == 0) {
        *(u32 *)(iStack_20 + 0x158) = 0;
        *(u32 *)(iStack_20 + 0x150) = 5;
      }
      else {
        lVar3 = getSavedDeviceNum__13deviceCheckerFv(*(u32 *)(iStack_20 + 0x15c));
        if (lVar3 == 0) {
          lVar3 = getFreeDeviceNum__13deviceCheckerFv(*(u32 *)(iStack_20 + 0x15c));
          if (lVar3 == 0) {
            lVar3 = isOnlyHDD__13deviceCheckerFv(*(u32 *)(iStack_20 + 0x15c));
            if (lVar3 == 0) {
              *(u32 *)(iStack_20 + 0x158) = 1;
            }
            else {
              *(u32 *)(iStack_20 + 0x158) = 2;
            }
            *(u32 *)(iStack_20 + 0x150) = 5;
          }
          else {
            *(u32 *)(iStack_20 + 0x158) = 3;
            *(u32 *)(iStack_20 + 0x150) = 5;
          }
        }
        else {
          *(u32 *)(iStack_20 + 0x150) = 3;
        }
      }
    }
    break;
  case 3:
    this->mode2 = 4;
    if (*(int *)(this->f_15c /*int **/ + 0x1c) == 0) {
      this->result = 2;
    }
    else {
      this->result = 3;
    }
    if (this->callback != 0) {
      (*this->callback)
                (this->result,this->cb_arg);
    }
    break;
  case 4:
    return 1;
  case 5:
    if ((m_TexRead == '\0') || (this->f_173 /*char **/ == '\0')) {
      if (this->f_173 /*char **/ == '\0') {
        this->f_173 /*u8 **/ = 1;
        this->result = 6;
        (*this->callback)
                  (this->result,this->cb_arg);
        uVar2 = SetPathname__7SysToolFPcPCc(auStack_130,0x4010e0);
        ReadOrder__11DvdromOrderFPCcPFiP9BufMemoryiPcPv_iiPvi
                  (Dvdromour__11DvdromOrder,uVar2,0x391cd0,0,iStack_20,0);
      }
    }
    else {
      mSetupBG__10dataAccessFv(this);
      *(u32 *)(iStack_20 + 0x150) = 6;
      if (*(int *)(iStack_20 + 0x158) != 3) {
        checkPollMC__13deviceCheckerFv(*(u32 *)(iStack_20 + 0x15c));
      }
    }
    break;
  case 6:
    lVar3 = isFade__7primWinFv(this->win);
    if (lVar3 == 0) {
      if (((uStack_10 & 0x2000) == 0) || (*(int *)(iStack_20 + 0x80) != 0)) {
        if ((uStack_10 & 0x6000) == 0) {
          lVar3 = isChangeStatus__13deviceCheckerFv(*(u32 *)(iStack_20 + 0x15c));
          if (lVar3 == 0) {
            mCheckDirKey__10dataAccessFi(iStack_20,uStack_10);
          }
          else {
            *(u32 *)(iStack_20 + 0x150) = 8;
            mReleaseMainCursor__10dataAccessFv(iStack_20);
          }
        }
        else {
          if ((uStack_10 & 0x2000) == 0) {
            play__9primSoundFi(*(u32 *)(iStack_20 + 0x34),3);
          }
          else {
            play__9primSoundFi(*(u32 *)(iStack_20 + 0x34),2);
          }
          if (*(int *)(iStack_20 + 0x158) == 3) {
            *(u32 *)(iStack_20 + 0x150) = 9;
          }
          else {
            *(u32 *)(iStack_20 + 0x150) = 8;
          }
          mReleaseMainCursor__10dataAccessFv(iStack_20);
        }
      }
      else {
        play__9primSoundFi(*(u32 *)(iStack_20 + 0x34),2);
        if (*(int *)(iStack_20 + 0x158) == 3) {
          fadeout__7primWinFi(*(u32 *)(iStack_20 + 0x88),0x10);
          *(u32 *)(iStack_20 + 0x150) = 10;
          leaveWin__10primCursorFv(*(u32 *)(iStack_20 + 0x90));
        }
        else {
          *(u32 *)(iStack_20 + 0x150) = 9;
          mReleaseMainCursor__10dataAccessFv(iStack_20);
        }
      }
    }
    break;
  case 7:
    return 1;
  case 8:
    if (this->f_158 /*int **/ != 3) {
      finishPollMC__13deviceCheckerFv(this->f_15c /*u32 **/);
    }
    if (*(int *)(iStack_20 + 0x4c) != 0) {
      fadeout__7primWinFi(*(u32 *)(iStack_20 + 0x4c),0x10);
    }
    if (*(int *)(iStack_20 + 0x44) != 0) {
      fadeout__7primWinFi(*(u32 *)(iStack_20 + 0x44),0x10);
    }
    fadeout__7primWinFi(*(u32 *)(iStack_20 + 0x38),0x10);
    if (*(int *)(iStack_20 + 0x3c) != 0) {
      fadeout__7primWinFi(*(u32 *)(iStack_20 + 0x3c),0x10);
    }
    *(u32 *)(iStack_20 + 0x150) = 1;
    break;
  case 9:
    if (this->f_158 /*int **/ != 3) {
      finishPollMC__13deviceCheckerFv(this->f_15c /*u32 **/);
    }
    fadeout__7primWinFi(*(u32 *)(iStack_20 + 0x88),0x10);
    fadeout__7primWinFi(*(u32 *)(iStack_20 + 0x38),0x10);
    *(u32 *)(iStack_20 + 0x180) = 2;
    if (*(int *)(iStack_20 + 0x24) != 0) {
      (**(code **)(iStack_20 + 0x24))
                (*(u32 *)(iStack_20 + 0x180),*(u32 *)(iStack_20 + 0x28));
    }
    *(u32 *)(iStack_20 + 0x150) = 7;
    break;
  case 10:
    lVar3 = isFade__7primWinFv(this->win);
    if (lVar3 == 0) {
      if (*(int *)(iStack_20 + 0x4c) != 0) {
        DelayDeleteRequest__7primWinFv(*(u32 *)(iStack_20 + 0x4c));
        *(u32 *)(iStack_20 + 0x4c) = 0;
      }
      *(u32 *)(iStack_20 + 0x150) = 0xb;
    }
    break;
  case 0xb:
    mSetupSelectDevice__10dataAccessFv(this);
    *(u32 *)(iStack_20 + 0x150) = 0xc;
    break;
  case 0xc:
    lVar3 = isFade__7primWinFv(this->win);
    if (lVar3 == 0) {
      if ((uStack_10 & 0x2000) == 0) {
        if ((uStack_10 & 0x4000) == 0) {
          mCheckDirKey__10dataAccessFi(iStack_20,uStack_10);
        }
        else {
          play__9primSoundFi(*(u32 *)(iStack_20 + 0x34),3);
          *(u32 *)(iStack_20 + 0x150) = 8;
          mReleaseMainCursor__10dataAccessFv(iStack_20);
        }
      }
      else {
        play__9primSoundFi(*(u32 *)(iStack_20 + 0x34),2);
        *(u32 *)(iStack_20 + 0x178) = 0;
        mOpenDevice__10dataAccessFi(iStack_20,*(u32 *)(iStack_20 + 0x80));
        mSetupProgressSystemSave__10dataAccessFv(iStack_20);
        *(u32 *)(iStack_20 + 0x168) = 0;
        *(u32 *)(iStack_20 + 0x150) = 0xd;
      }
    }
    break;
  case 0xd:
    mGrowProgress__10dataAccessFi(this,1);
    sStack_22 = (short)DAT_00421e94;
    if (sStack_22 != 1) {
      if (sStack_22 == 3) {
        if ((*(uint *)(DAT_00421e90 + 0xc) & 0xff) == 0) {
          mSetupWarning__10dataAccessFPc
                    (iStack_20,
                     *(u32 *)(dataMess_deviceWarning_J + *(int *)(iStack_20 + 0x16c) * 4));
        }
        else {
          mSetupWarning__10dataAccessFPc
                    (iStack_20,
                     *(u32 *)(dataMess_systemWarning_J + *(int *)(iStack_20 + 0x16c) * 4));
        }
        Close__8SaveDataFv(0x421e70);
        *(u32 *)(iStack_20 + 0x150) = 0x11;
        *(u32 *)(iStack_20 + 0x154) = 8;
      }
      else if ((*(uint *)(DAT_00421e90 + 0xc) & 0xff) == 0) {
        *(int *)(iStack_20 + 0x178) = *(int *)(iStack_20 + 0x178) + 1;
        if (*(int *)(iStack_20 + 0x178) < 3) {
          Close__8SaveDataFv(0x421e70);
          *(u32 *)(iStack_20 + 0x150) = 0xf;
        }
        else {
          mSetupWarning__10dataAccessFPc
                    (iStack_20,
                     *(u32 *)(dataMess_deviceUnformat_J + *(int *)(iStack_20 + 0x16c) * 4));
          *(u32 *)(iStack_20 + 0x150) = 0x11;
          if (*(int *)(iStack_20 + 0x16c) < 2) {
            *(u32 *)(iStack_20 + 0x154) = 0x12;
          }
          else {
            Close__8SaveDataFv(0x421e70);
            *(u32 *)(iStack_20 + 0x154) = 8;
          }
        }
      }
      else {
        iStack_2c = DAT_00421e90;
        if ((long)((ulong)*(u8 *)(DAT_00421e90 + 5) << 0x3e) < 0) {
          Close__8SaveDataFv(0x421e70);
          mSetupWarning__10dataAccessFPc
                    (iStack_20,initialMess_deviceExistSaveData_J[*(int *)(iStack_20 + 0x16c)]);
          *(u32 *)(iStack_20 + 0x150) = 0x11;
          *(u32 *)(iStack_20 + 0x154) = 8;
        }
        else {
          uVar1 = DisableReset__6CPauseFv(*(u32 *)(app__4CApp + 0x78));
          *(u32 *)(iStack_20 + 0x17c) = uVar1;
          CreateSystem__8SaveDataFv(0x421e70);
          *(u32 *)(iStack_20 + 0x150) = 0xe;
        }
      }
    }
    break;
  case 0xe:
    mGrowProgress__10dataAccessFi(this,1);
    if ((short)DAT_00421e94 != 1) {
      if ((short)DAT_00421e94 == 3) {
        if ((*(uint *)(DAT_00421e90 + 0xc) & 0xff) == 0) {
          mSetupWarning__10dataAccessFPc
                    (iStack_20,
                     *(u32 *)(dataMess_deviceWarning_J + *(int *)(iStack_20 + 0x16c) * 4));
        }
        else {
          mSetupWarning__10dataAccessFPc
                    (iStack_20,
                     *(u32 *)(dataMess_systemWarning_J + *(int *)(iStack_20 + 0x16c) * 4));
        }
        EnableReset__6CPauseFi
                  (*(u32 *)(app__4CApp + 0x78),*(u32 *)(iStack_20 + 0x17c));
        Close__8SaveDataFv(0x421e70);
        *(u32 *)(iStack_20 + 0x150) = 0x11;
        *(u32 *)(iStack_20 + 0x154) = 8;
      }
      else {
        EnableReset__6CPauseFi
                  (*(u32 *)(app__4CApp + 0x78),*(u32 *)(iStack_20 + 0x17c));
        setTextAlpha__7primWinFii(*(u32 *)(iStack_20 + 0x88),2,0);
        setTextAlpha__7primWinFii(*(u32 *)(iStack_20 + 0x88),3,0x80);
        Close__8SaveDataFv(0x421e70);
        mGrowProgress__10dataAccessFi(iStack_20,0x130);
        if (*(int *)(iStack_20 + 0x2c) == 0) {
          lVar3 = __nw__FUi(0x10c);
          uVar1 = 0;
          if (lVar3 != 0) {
            uVar1 = __ct__10primCursorFv(lVar3);
          }
          *(u32 *)(iStack_20 + 0x2c) = uVar1;
          createCursor__10primCursorFiiii(*(u32 *)(iStack_20 + 0x2c),1,1,2,10);
          setPos__10primCursorFff(0x43480000,0x43a20000,*(u32 *)(iStack_20 + 0x2c));
        }
        *(u32 *)(iStack_20 + 0x150) = 0x10;
      }
    }
    break;
  case 0xf:
    iStack_30 = DAT_00421e90;
    iStack_28 = DAT_00421e90;
    if (DAT_00421e90 == 0) {
      mOpenDevice__10dataAccessFi(this,this->device_sel);
      *(u32 *)(iStack_20 + 0x150) = 0xd;
    }
    else {
      Close__8SaveDataFv(0x421e70);
    }
    break;
  case 0x10:
    if ((param_2 & 0x2000) != 0) {
      play__9primSoundFi(this->snd,2);
      if (*(int *)(iStack_20 + 0x2c) != 0) {
        DelayDeleteRequest__10primCursorFv(*(u32 *)(iStack_20 + 0x2c));
        *(u32 *)(iStack_20 + 0x2c) = 0;
      }
      *(u32 *)(iStack_20 + 0x150) = 8;
    }
    break;
  case 0x11:
    lVar3 = mCheckWarning__10dataAccessFi(this,param_2);
    if (lVar3 != 0) {
      mReleaseWarning__10dataAccessFv(iStack_20);
      *(u32 *)(iStack_20 + 0x150) = *(u32 *)(iStack_20 + 0x154);
    }
    break;
  case 0x12:
    lVar3 = isFade__7primWinFv(this->win);
    if (lVar3 == 0) {
      mReleaseWin__10dataAccessFv(iStack_20);
      *(u32 *)(iStack_20 + 0x150) = 0x13;
    }
    break;
  case 0x13:
    mSetupFormat__10dataAccessFv(this);
    *(u32 *)(iStack_20 + 0x150) = 0x14;
    break;
  case 0x14:
    lVar3 = isFade__7primWinFv(this->win);
    if (lVar3 == 0) {
      if (((uStack_10 & 0x2000) == 0) || (*(int *)(iStack_20 + 0x80) != 0)) {
        if ((uStack_10 & 0x6000) == 0) {
          mCheckDirKey__10dataAccessFi(iStack_20,uStack_10);
        }
        else {
          if ((uStack_10 & 0x2000) == 0) {
            play__9primSoundFi(*(u32 *)(iStack_20 + 0x34),3);
          }
          else {
            play__9primSoundFi(*(u32 *)(iStack_20 + 0x34),2);
          }
          *(u32 *)(iStack_20 + 0x150) = 8;
        }
      }
      else {
        uVar1 = DisableReset__6CPauseFv(*(u32 *)(app__4CApp + 0x78));
        *(u32 *)(iStack_20 + 0x17c) = uVar1;
        play__9primSoundFi(*(u32 *)(iStack_20 + 0x34),2);
        mSetupProgressFormat__10dataAccessFv(iStack_20);
        Format__8SaveDataFv(0x421e70);
        *(u32 *)(iStack_20 + 0x150) = 0x15;
      }
    }
    break;
  case 0x15:
    mGrowProgress__10dataAccessFi(this,4);
    sStack_24 = (short)DAT_00421e94;
    if (sStack_24 != 1) {
      if ((sStack_24 == 0) || (sStack_24 == 3)) {
        EnableReset__6CPauseFi
                  (*(u32 *)(app__4CApp + 0x78),*(u32 *)(iStack_20 + 0x17c));
        Close__8SaveDataFv(0x421e70);
        setTextAlpha__7primWinFii(*(u32 *)(iStack_20 + 0x88),2,0);
        mSetupWarning__10dataAccessFPc(iStack_20,PTR__5490_003f9c78);
        *(u32 *)(iStack_20 + 0x150) = 0x11;
        *(u32 *)(iStack_20 + 0x154) = 8;
      }
      else if (sStack_24 == 2) {
        EnableReset__6CPauseFi
                  (*(u32 *)(app__4CApp + 0x78),*(u32 *)(iStack_20 + 0x17c));
        mGrowProgress__10dataAccessFi(iStack_20,0x130);
        setTextAlpha__7primWinFii(*(u32 *)(iStack_20 + 0x88),2,0);
        setTextAlpha__7primWinFii(*(u32 *)(iStack_20 + 0x88),3,0x80);
        if (*(int *)(iStack_20 + 0x2c) == 0) {
          lVar3 = __nw__FUi(0x10c);
          uVar1 = 0;
          if (lVar3 != 0) {
            uVar1 = __ct__10primCursorFv(lVar3);
          }
          *(u32 *)(iStack_20 + 0x2c) = uVar1;
          createCursor__10primCursorFiiii(*(u32 *)(iStack_20 + 0x2c),1,1,2,10);
          setPos__10primCursorFff(0x43480000,0x43a20000,*(u32 *)(iStack_20 + 0x2c));
        }
        *(u32 *)(iStack_20 + 0x150) = 0x16;
      }
    }
    break;
  case 0x16:
    if ((param_2 & 0x2000) != 0) {
      play__9primSoundFi(this->snd,2);
      if (*(int *)(iStack_20 + 0x2c) != 0) {
        DelayDeleteRequest__10primCursorFv(*(u32 *)(iStack_20 + 0x2c));
        *(u32 *)(iStack_20 + 0x2c) = 0;
      }
      *(u32 *)(iStack_20 + 0x150) = 8;
    }
  }
  return 0;
}

// JP: 0x003989c0  mSetupInitialWarning__10dataAccessFv  size 0x374
// dataAccess::mSetupInitialWarning()
void mSetupInitialWarning__10dataAccessFv(dataAccess *this)
{
  u32 uVar1;
  long lVar2;
  int iVar3;
  this->device_sel = 0;
  this->f_84 /*u32 **/ = 2;
  lVar2 = __nw__FUi(0x148);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = __ct__7primWinFv(lVar2);
  }
  this->popup = uVar1;
  uVar1 = this->popup;
  initialize__7primWinFP7primTex(uVar1,m_pPT);
  setItem__7primWinFiii(uVar1,2,1,this->f_84 /*int **/ * 2 + 1);
  setTextArea__7primWinFiiib(uVar1,1,0x280,0x180,1);
  for (iVar3 = 0; iVar3 < this->f_84 /*int **/; iVar3 = iVar3 + 1) {
    createText__7primWinFiiiiPciib
              (uVar1,iVar3,1,0x44,iVar3 * 0x16 + 0xa0,(&dataMess_queryYN_J)[iVar3],0,0);
    createText__7primWinFiiiiPciib
              (uVar1,this->f_84 /*int **/ + iVar3,1,0xc,0x1a0,
               *(u32 *)
                (initialMess_warningNote_J + (iVar3 + this->f_158 /*int **/ * 2) * 4),0,0);
    *(int *)(this + iVar3 * 0xc + 0x50) = iVar3;
    *(int *)(this + iVar3 * 0xc + 0x54) = iVar3 + this->f_84 /*int **/;
    *(u8 *)(this + iVar3 * 0xc + 0x58) = 1;
  }
  this->win = uVar1;
  createText__7primWinFiiiiPciib
            (uVar1,this->f_84 /*int **/ << 1,1,0xc,0x3a,
             *(u32 *)(initialMess_warning_J + this->f_158 /*int **/ * 4),0,0);
  createPoly__7primWinFiiiiii(uVar1,0,0,0,0x36,0x200,0x5e);
  setPolyRGBA__7primWinFiiiiii(uVar1,0,0,0,0,0,0x60);
  setPolyRGBA__7primWinFiiiiii(uVar1,0,1,0,0,0,0x60);
  setPolyRGBA__7primWinFiiiiii(uVar1,0,2,0,0,0,0);
  setPolyRGBA__7primWinFiiiiii(uVar1,0,3,0,0,0,0);
  buildWin__7primWinFiiiiii(uVar1,3,0,0,0,0,0);
  fadein__7primWinFi(uVar1,0x10);
  mSetMainCursor__10dataAccessFi(this,this->device_sel);
  mSelectItem__10dataAccessFi(this,this->device_sel);
  return;
}

// JP: 0x00398d40  mSetupProgressSystemSave__10dataAccessFv  size 0xcc
// dataAccess::mSetupProgressSystemSave()
void mSetupProgressSystemSave__10dataAccessFv(dataAccess *this)
{
  mSetupProgressCommon__10dataAccessFv(this);
  createText__7primWinFiiiiPciib
            (this->win,2,2,0x26,0x12e,
             *(u32 *)(initialMess_progress_J + this->dev_kind * 4),0,0);
  createText__7primWinFiiiiPciib
            (this->win,3,2,0x26,0x12e,initialMess_systemFileOK_J,0,0);
  setTextAlpha__7primWinFii(this->win,3,0);
  mReleaseMainCursor__10dataAccessFv(this);
  return;
}

// JP: 0x00398e10  mOpenDevice__10dataAccessFi  size 0x108
// dataAccess::mOpenDevice(int)
void mOpenDevice__10dataAccessFi(dataAccess *this,int param_2)
{
  if (param_2 == 0) {
    Open__8SaveDataFs(0x421e70,0);
  }
  else if (param_2 == 1) {
    Open__8SaveDataFs(0x421e70,1);
  }
  else if (param_2 == 2) {
    Open__8SaveDataFs(0x421e70,2);
  }
  this->slot_count = (uint)*(u8 *)(*(int *)(DAT_00421e90 + 0x1c) + 0xd);
  this->cur_slot = 0;
  this->dev_kind = param_2;
  return;
}

// JP: 0x00398f20  mCheckWarning__10dataAccessFi  size 0x1b4
// dataAccess::mCheckWarning(int)
u32 mCheckWarning__10dataAccessFi(dataAccess *this,uint param_2)
{
  u32 uVar1;
  long lVar2;
  if (this->progress == 1) {
    if ((param_2 & 0x2000) != 0) {
      play__9primSoundFi(this->snd,2);
      if (this->cursor != 0) {
        DelayDeleteRequest__10primCursorFv(this->cursor);
        this->cursor = 0;
      }
      return 1;
    }
  }
  else if (*(u16 *)(this->f_8c /*int **/ + 0x80) <
           *(u16 *)(this->f_8c /*int **/ + 0x76)) {
    if ((param_2 & 0x2000) != 0) {
      Finish__11MenuMessageFv(this->f_8c /*u32 **/);
    }
  }
  else {
    if (this->cursor == 0) {
      lVar2 = __nw__FUi(0x10c);
      uVar1 = 0;
      if (lVar2 != 0) {
        uVar1 = __ct__10primCursorFv(lVar2);
      }
      this->cursor = uVar1;
      createCursor__10primCursorFiiii(this->cursor,1,1,2,10);
      setPos__10primCursorFff(0x43700000,0x43aa0000,this->cursor);
    }
    this->progress = 1;
  }
  return 0;
}

// JP: 0x003990e0  @24@__dt__10dataAccessFv  size 0x8
// @24@__dt__10dataAccessFv
int _24___dt__10dataAccessFv(dataAccess *this,short param_2)
{
  int iVar1;
  int iVar2;
  iVar2 = this + -0x18;
  if (iVar2 != 0) {
    *(u8 **)(this + -4) = __vt__10dataAccess;
    this->vptr = 0x407200;
    if (this->f_144 /*int **/ != 0) {
      iVar1 = this->f_144 /*int **/;
      if (iVar1 != 0) {
        VCALL14(iVar1, 8)(iVar1,1);
      }
      this->f_144 /*u32 **/ = 0;
    }
    if (m_pPT != 0) {
      __dt__7primTexFv(m_pPT,1);
      m_pPT = 0;
    }
    Dispose__7CPollerFP7CPolObj(app__4CApp + 0x48,iVar2);
    if (this->f_1c /*int **/ != 0) {
      DelayDeleteRequest__9primSoundFv(this->f_1c /*u32 **/);
      this->f_1c /*u32 **/ = 0;
    }
    __dt__4FontFv(this + 0x114,0xffffffffffffffff);
    __dt__4FontFv(this + 0x110,0xffffffffffffffff);
    if (iVar2 != -0x18) {
      this->vptr = __vt__17DelayDeleteObject;
    }
    __dt__7CPolObjFv(iVar2,0);
    if (0 < param_2) {
      __dl__FPv(iVar2);
    }
  }
  return iVar2;
}
