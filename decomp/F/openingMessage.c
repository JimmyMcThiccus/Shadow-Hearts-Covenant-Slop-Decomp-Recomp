/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x003a8340  LSD_CB__14openingMessageFv  size 0x14
// openingMessage::LSD_CB()
u32 LSD_CB__14openingMessageFv(void)
{
  m_bLSDStart = 1;
  return 1;
}

// JP: 0x003a83f0  __ct__14openingMessageFv  size 0x110
// openingMessage::openingMessage()
int __ct__14openingMessageFv(openingMessage *this)
{
  u32 in_zero_lo;
  u32 in_zero_hi;
  u32 in_zero_udw;
  u32 in_register_0000000c;
  __ct__7CPolObjFv(this);
  this->f_18 /*u32 **/ = 0;
  this->f_1c /*u32 **/ = 0;
  this->f_20 /*u8 **/ = __vt__17DelayDeleteObject;
  this->f_14 /*u8 **/ = __vt__14openingMessage;
  this->f_20 /*u32 **/ = 0x407460;
  this->f_30 /*u32 **/ = in_zero_lo;
  this->f_34 /*u32 **/ = in_zero_hi;
  this->f_38 /*u32 **/ = in_zero_udw;
  this->f_3c /*u32 **/ = in_register_0000000c;
  this->f_40 /*u32 **/ = in_zero_lo;
  this->f_44 /*u32 **/ = in_zero_hi;
  this->f_48 /*u32 **/ = in_zero_udw;
  this->f_4c /*u32 **/ = in_register_0000000c;
  if (camera__4CApp != 0) {
    __dt__9GsxCameraFv(camera__4CApp,1);
    camera__4CApp = 0;
  }
  this->fader = 0;
  this->f_68 /*u32 **/ = 0;
  this->title = 0;
  this->menu = 0;
  this->cursor = 0;
  this->snd = 0;
  this->bgm = 0;
  this->d0 = 0;
  this->demo = 0;
  this->data_access = 0;
  this->install = 0;
  this->cam = 0;
  this->disp_w = 0;
  this->disp_h = 0;
  return this;
}

// JP: 0x003a8500  __dt__14openingMessageFv  size 0x170
// openingMessage::~openingMessage()
int __dt__14openingMessageFv(openingMessage *this,short param_2)
{
  if (this != 0) {
    this->f_14 /*u8 **/ = __vt__14openingMessage;
    this->f_20 /*u32 **/ = 0x407460;
    if (sys__9LSDPlayer != 0) {
      if (sys__9LSDPlayer != 0) {
        VCALL14(sys__9LSDPlayer, 8)(sys__9LSDPlayer,1);
      }
    }
    if (m_pPT != 0) {
      __dt__7primTexFv(m_pPT,1);
      m_pPT = 0;
    }
    mReleaseFader__14openingMessageFv(this);
    Dispose__7CPollerFP7CPolObj(app__4CApp + 0x48,this);
    if (this->snd != 0) {
      DelayDeleteRequest__9primSoundFv(this->snd);
      this->snd = 0;
    }
    if (this->bgm != 0) {
      DelayDeleteRequest__9primMusicFv(this->bgm);
      this->bgm = 0;
    }
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

// JP: 0x003a8670  initialize__14openingMessageFv  size 0x134
// openingMessage::initialize()
void initialize__14openingMessageFv(openingMessage *this)
{
  u32 uVar1;
  long lVar2;
  if ((sys__9LSDPlayer == 0) && (lVar2 = __nw__FUi(0xbc), lVar2 != 0)) {
    __ct__9LSDPlayerFv(lVar2);
  }
  *(code **)(sys__9LSDPlayer + 0x7c) = LSD_CB__14openingMessageFv;
  Reset__9LSDPlayerFv(sys__9LSDPlayer);
  Entry__7CPollerFP7CPolObjib(app__4CApp + 0x48,this,0x80,0);
  lVar2 = __nw__FUi(0x30);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = __ct__9primSoundFv(lVar2);
  }
  this->snd = uVar1;
  initialize__9primSoundFv(this->snd);
  mSetupFader__14openingMessageFv(this);
  Update__15SaveMenuSectionFv();
  if (DAT_0040ad44 == '\0') {
    DAT_0040ad44 = '\x01';
    this->state = 0x1a;
  }
  else {
    this->state = 0x10;
  }
  return;
}

// JP: 0x003a87b0  changeDispMode__14openingMessageFii  size 0x2a4
// openingMessage::changeDispMode(int, int)
void changeDispMode__14openingMessageFii(openingMessage *this,int param_2,u32 param_3)
{
  u8 auVar1 [16];
  u64 uVar2;
  u32 uVar3;
  long lVar4;
  u32 uVar5;
  int iVar6;
  u8 in_vf0 [16];
  u8 auVar7 [16];
  u8 auVar8 [16];
  u8 auVar9 [16];
  if (this->disp_w != param_2) {
    this->disp_w = param_2;
    this->disp_h = param_3;
    if (this->cam != 0) {
      __dt__9GsxCameraFv(this->cam,1);
      this->cam = 0;
    }
    lVar4 = __nw__FUi(0x3a0);
    uVar3 = 0;
    if (lVar4 != 0) {
      uVar3 = __ct__9GsxCameraFUiUiUiUiUi
                        (lVar4,this->disp_w,this->disp_h,0,
                         0x18,0xb);
    }
    this->cam = uVar3;
    if (this->cam != 0) {
      camera__4CApp = this->cam;
      *(u32 *)(this->cam + 0x180) = 0;
      *(u32 *)(this->cam + 0x370) = 0x41200000;
      *(u32 *)(this->cam + 0x374) = 0x46fa0000;
      if (this->disp_w == 0x280) {
        SetViewMatrix__9GsxCameraFfffff
                  (0x44200000,0x3f800000,0x3f6eeeef,0x3f800000,0x4b7fff28,
                   this->cam);
        SetFFMode__3GsxFibi(0,0,1);
        SetInter30__3GsxFi(1);
      }
      else {
        SetViewMatrix__9GsxCameraFfffff
                  (0x44000000,0x3f4ccccd,0x3f6eeeef,0x3f800000,0x4b7fff28,
                   this->cam);
        SetFFMode__3GsxFibi(0,1,1);
        SetInter30__3GsxFi(1);
      }
      SetCamera__5WorldFUiiP9GsxCamera(0x42bf10,0,0,this->cam);
      if (this->cam != 0) {
        iVar6 = this->cam;
        auVar7 = _vmr32(in_vf0);
        auVar8 = _vmr32(auVar7);
        auVar9 = _vmr32(auVar8);
        auVar1 = _sqc2(in_vf0);
        *(u8 (*) [16])(iVar6 + 0x270) = auVar1;
        auVar1 = _sqc2(auVar7);
        *(u8 (*) [16])(iVar6 + 0x260) = auVar1;
        auVar1 = _sqc2(auVar8);
        *(u8 (*) [16])(iVar6 + 0x250) = auVar1;
        auVar1 = _sqc2(auVar9);
        *(u8 (*) [16])(iVar6 + 0x240) = auVar1;
        uVar3 = GetRad(this->f_40 /*u32 **/);
        iVar6 = this->cam + 0x240;
        sceVu0RotMatrixX(uVar3,iVar6,iVar6);
        uVar3 = GetRad(this->f_44 /*u32 **/);
        iVar6 = this->cam + 0x240;
        sceVu0RotMatrixY(uVar3,iVar6,iVar6);
        uVar3 = GetRad(this->f_48 /*u32 **/);
        iVar6 = this->cam + 0x240;
        sceVu0RotMatrixZ(uVar3,iVar6,iVar6);
        iVar6 = this->cam;
        uVar2 = this->f_30 /*u64 **/;
        uVar3 = this->f_38 /*u32 **/;
        uVar5 = this->f_3c /*u32 **/;
        *(int *)(iVar6 + 0x270) = (int)uVar2;
        *(int *)(iVar6 + 0x274) = (int)((ulong)uVar2 >> 0x20);
        *(u32 *)(iVar6 + 0x278) = uVar3;
        *(u32 *)(iVar6 + 0x27c) = uVar5;
        ApplyFrame__9GsxCameraFv(this->cam);
      }
    }
  }
  return;
}

// JP: 0x003a8a60  Polling__14openingMessageFv  size 0x15b8
// openingMessage::Polling()
u64 Polling__14openingMessageFv(openingMessage *this)
{
  u16 uVar1;
  u16 uVar2;
  int iVar3;
  u32 uVar4;
  u16 *puVar5;
  long lVar6;
  u64 uVar7;
  u8 auStack_280 [256];
  u8 auStack_180 [260];
  u32 uStack_7c;
  int iStack_78;
  int iStack_74;
  int iStack_70;
  u32 uStack_6c;
  u32 uStack_68;
  int iStack_64;
  int iStack_60;
  u32 uStack_5c;
  u32 uStack_58;
  u32 uStack_54;
  int iStack_50;
  int iStack_48;
  int iStack_44;
  int iStack_40;
  int iStack_3c;
  int iStack_38;
  int iStack_34;
  int iStack_30;
  int iStack_2c;
  int iStack_28;
  int iStack_24;
  int iStack_20;
  int iStack_1c;
  u32 uStack_18;
  u16 uStack_14;
  u16 uStack_12;
  int iStack_10;
  iStack_10 = this;
  iVar3 = GetActive__4CPadFi(0);
  uStack_12 = *(u16 *)((&m_pCoreArray__4CPad)[*(int *)(iVar3 + 4)] + 0x70);
  uVar1 = *(u16 *)((&m_pCoreArray__4CPad)[*(int *)(iVar3 + 4)] + 0x6c);
  uVar2 = uStack_12 & 0xf0 | uVar1;
  uStack_14 = uVar1;
  switch(*(u32 *)(iStack_10 + 0xe0)) {
  case 0:
    lVar6 = __nw__FUi(0x184);
    uVar4 = 0;
    if (lVar6 != 0) {
      uVar4 = __ct__10dataAccessFv(lVar6);
    }
    *(u32 *)(iStack_10 + 0xd8) = uVar4;
    initialize__10dataAccessFQ210dataAccess10ACCESSMODEPFiPv_vPv
              (*(u32 *)(iStack_10 + 0xd8),2,0x3aa020,iStack_10);
    fadeout__7primWinFi(*(u32 *)(iStack_10 + 100),1);
    *(u32 *)(iStack_10 + 0xe0) = 1;
    break;
  case 1:
    if (*(int *)(iStack_10 + 0xf0) == 6) {
      changeDispMode__14openingMessageFii(iStack_10,0x200,0x1c0);
    }
    else if (*(int *)(iStack_10 + 0xf0) == 3) {
      DAT_0040ad42 = 1;
      *(u32 *)(iStack_10 + 0xe0) = 3;
    }
    else if (*(int *)(iStack_10 + 0xf0) == 2) {
      *(u32 *)(iStack_10 + 0xe0) = 3;
    }
    break;
  case 3:
    if (*(int *)(iStack_10 + 0xf0) == 4) {
      *(u32 *)(iStack_10 + 0xe0) = 7;
      fadein__7primWinFi(*(u32 *)(iStack_10 + 100),1);
    }
    break;
  case 10:
    changeDispMode__14openingMessageFii(iStack_10,0x280,0x1c0);
    lVar6 = Reset__9LSDPlayerFv(sys__9LSDPlayer);
    if (lVar6 != 0) {
      m_bLSDStart = '\0';
      uVar7 = SetPathname__7SysToolFPcPCc(auStack_180,0x401370);
      startStream__9LSDPlayerFPc(sys__9LSDPlayer,uVar7);
      *(u32 *)(iStack_10 + 0xe0) = 0xb;
    }
    break;
  case 0xb:
    if (m_bLSDStart != '\0') {
      uStack_18 = 0x80ffffff;
      iStack_2c = *(int *)(iStack_10 + 0x28);
      uStack_54 = 0x80ffffff;
      *(u32 *)(iStack_2c + 0x180) = 0x80ffffff;
      if ((uVar1 & 0x2008) == 0) {
        lVar6 = Reset__9LSDPlayerFv(sys__9LSDPlayer);
        if (lVar6 != 0) {
          *(u32 *)(iStack_10 + 0xe0) = 0xc;
          setPolyRGBA__7primWinFiiiii(*(u32 *)(iStack_10 + 100),0,0xff,0xff,0xff,0x80);
          fadein__7primWinFi(*(u32 *)(iStack_10 + 100),8);
        }
      }
      else {
        Pause__9LSDPlayerFv(sys__9LSDPlayer);
        Exit__9LSDPlayerFv(sys__9LSDPlayer);
        *(u32 *)(iStack_10 + 0xe0) = 0xc;
        setPolyRGBA__7primWinFiiiii(*(u32 *)(iStack_10 + 100),0,0xff,0xff,0xff,0x80);
        fadein__7primWinFi(*(u32 *)(iStack_10 + 100),8);
      }
    }
    break;
  case 0xc:
    lVar6 = isFade__7primWinFv(*(u32 *)(iStack_10 + 100));
    if (lVar6 == 0) {
      SetFFMode__3GsxFibi(0,1,1);
      *(u32 *)(iStack_10 + 0xe0) = 0x10;
    }
    break;
  case 0x10:
    iStack_30 = *(int *)(iStack_10 + 100);
    if (*(char *)(iStack_30 + 0x102) == '\0') {
      lVar6 = isFade__7primWinFv(*(u32 *)(iStack_10 + 100));
      if (lVar6 == 0) {
        changeDispMode__14openingMessageFii(iStack_10,0x280,0x1c0);
        mSetupTitleWin__14openingMessageFv(iStack_10);
        fadeout__7primWinFi(*(u32 *)(iStack_10 + 100),0x20);
      }
    }
    else {
      *(u32 *)(iStack_10 + 0xec) = 0;
      *(u32 *)(iStack_10 + 0xe0) = 0x11;
    }
    break;
  case 0x11:
    *(int *)(iStack_10 + 0xec) = *(int *)(iStack_10 + 0xec) + 1;
    if (*(int *)(iStack_10 + 0xec) < 0x4b1) {
      if ((uVar1 & 0x2008) == 0) {
        *(int *)(iStack_10 + 0xc4) = *(int *)(iStack_10 + 0xc4) + 1;
        if (*(int *)(iStack_10 + 0xc4) < 0x40) {
          setPolyAlpha__7primWinFii
                    (*(u32 *)(iStack_10 + 0x6c),4,*(int *)(iStack_10 + 0xc4) << 1);
        }
        else if (*(int *)(iStack_10 + 0xc4) < 0x80) {
          setPolyAlpha__7primWinFii
                    (*(u32 *)(iStack_10 + 0x6c),4,
                     (*(int *)(iStack_10 + 0xc4) + -0x40) * -2 + 0x80);
        }
        else {
          *(u32 *)(iStack_10 + 0xc4) = 0;
        }
      }
      else {
        play__9primSoundFi(*(u32 *)(iStack_10 + 0x5c),2);
        stop__9primMusicFv(*(u32 *)(iStack_10 + 0x60));
        if (*(int *)(iStack_10 + 0x60) != 0) {
          DelayDeleteRequest__9primMusicFv(*(u32 *)(iStack_10 + 0x60));
          *(u32 *)(iStack_10 + 0x60) = 0;
        }
        setPolyAlpha__7primWinFii(*(u32 *)(iStack_10 + 0x6c),4,0);
        mSetupTrialMainWin__14openingMessageFv(iStack_10);
        *(u32 *)(iStack_10 + 0xec) = 0;
        *(u32 *)(iStack_10 + 0xe0) = 0x12;
      }
    }
    else {
      stop__9primMusicFv(*(u32 *)(iStack_10 + 0x60));
      if (*(int *)(iStack_10 + 0x60) != 0) {
        DelayDeleteRequest__9primMusicFv(*(u32 *)(iStack_10 + 0x60));
        *(u32 *)(iStack_10 + 0x60) = 0;
      }
      setPolyRGBA__7primWinFiiiii(*(u32 *)(iStack_10 + 100),0,0,0,0,0x80);
      fadein__7primWinFi(*(u32 *)(iStack_10 + 100),0x20);
      *(u32 *)(iStack_10 + 0xe0) = 0x13;
      *(u32 *)(iStack_10 + 0xe4) = 0x23;
      lVar6 = __nw__FUi(0x48);
      uVar4 = 0;
      if (lVar6 != 0) {
        uVar4 = __ct__17openingBattleDemoFv(lVar6);
      }
      *(u32 *)(iStack_10 + 0xd4) = uVar4;
      iStack_34 = m_TexPool;
      uStack_5c = *(u32 *)(m_TexPool + 4);
      uStack_58 = uStack_5c;
      initialize__17openingBattleDemoFPUci(*(u32 *)(iStack_10 + 0xd4),uStack_5c,0x13);
    }
    break;
  case 0x12:
    lVar6 = isFade__7primWinFv(*(u32 *)(iStack_10 + 0x70));
    if (lVar6 == 0) {
      if (*(int *)(iStack_10 + 0x74) == 0) {
        lVar6 = __nw__FUi(0x10c);
        uVar4 = 0;
        if (lVar6 != 0) {
          uVar4 = __ct__10primCursorFv(lVar6);
        }
        *(u32 *)(iStack_10 + 0x74) = uVar4;
        createCursor__10primCursorFiiii(*(u32 *)(iStack_10 + 0x74),0,2,8,10);
        iStack_38 = *(int *)(iStack_10 + 0x70);
        iStack_64 = iStack_38 + 0x3c;
        iStack_60 = iStack_64;
        setItem__10primCursorFP10MenuWindowi(*(u32 *)(iStack_10 + 0x74),iStack_64,0);
        qMove__10primCursorFv(*(u32 *)(iStack_10 + 0x74));
      }
      if ((uVar1 & 0x2000) == 0) {
        iStack_1c = *(int *)(iStack_10 + 0x78);
        uVar4 = menuCheckKey__7primWinFiP10primCursor
                          (*(u32 *)(iStack_10 + 0x70),uVar2,*(u32 *)(iStack_10 + 0x74)
                          );
        *(u32 *)(iStack_10 + 0x78) = uVar4;
        if (iStack_1c != *(int *)(iStack_10 + 0x78)) {
          play__9primSoundFi(*(u32 *)(iStack_10 + 0x5c),0);
        }
      }
      else {
        play__9primSoundFi(*(u32 *)(iStack_10 + 0x5c),2);
        if (*(int *)(iStack_10 + 0x74) != 0) {
          DelayDeleteRequest__10primCursorFv(*(u32 *)(iStack_10 + 0x74));
          *(u32 *)(iStack_10 + 0x74) = 0;
        }
        if (*(int *)(iStack_10 + 0x78) == 0) {
          setPolyRGBA__7primWinFiiiii(*(u32 *)(iStack_10 + 100),0,0,0,0,0x80);
          fadein__7primWinFi(*(u32 *)(iStack_10 + 100),0x20);
          *(u32 *)(iStack_10 + 0xe0) = 0x13;
          *(u32 *)(iStack_10 + 0xe4) = 0x26;
        }
        else {
          mReleaseTrialMainWin__14openingMessageFv(iStack_10);
          *(u32 *)(iStack_10 + 0xe0) = 0x18;
        }
      }
      if (uVar2 != 0) {
        *(u32 *)(iStack_10 + 0xec) = 0;
      }
      *(int *)(iStack_10 + 0xec) = *(int *)(iStack_10 + 0xec) + 1;
      if (0xe10 < *(int *)(iStack_10 + 0xec)) {
        *(u32 *)(iStack_10 + 0xe0) = 0x13;
        *(u32 *)(iStack_10 + 0xe4) = 0x23;
        lVar6 = __nw__FUi(0x48);
        uVar4 = 0;
        if (lVar6 != 0) {
          uVar4 = __ct__17openingBattleDemoFv(lVar6);
        }
        *(u32 *)(iStack_10 + 0xd4) = uVar4;
        iStack_3c = m_TexPool;
        uStack_6c = *(u32 *)(m_TexPool + 4);
        uStack_68 = uStack_6c;
        initialize__17openingBattleDemoFPUci(*(u32 *)(iStack_10 + 0xd4),uStack_6c,0x13);
        setPolyRGBA__7primWinFiiiii(*(u32 *)(iStack_10 + 100),0,0,0,0,0x80);
        fadein__7primWinFi(*(u32 *)(iStack_10 + 100),0x20);
      }
    }
    break;
  case 0x13:
    lVar6 = isFade__7primWinFv(*(u32 *)(iStack_10 + 100));
    if (lVar6 == 0) {
      uVar7 = mReleaseTitleWin__14openingMessageFv(iStack_10);
      mReleaseMenuWin__14openingMessageFv(iStack_10,uVar7);
      *(u32 *)(iStack_10 + 0xe0) = *(u32 *)(iStack_10 + 0xe4);
    }
    break;
  case 0x14:
    uVar7 = changeDispMode__14openingMessageFii(iStack_10,0x200,0x1c0);
    start__7installFv(*(u32 *)(iStack_10 + 0xdc),uVar7);
    *(u32 *)(iStack_10 + 0xdc) = 0;
    fadeout__7primWinFi(*(u32 *)(iStack_10 + 100),1);
    *(u32 *)(iStack_10 + 0xe0) = 0x16;
    break;
  case 0x15:
    changeDispMode__14openingMessageFii(iStack_10,0x200,0x1c0);
    start__10dataAccessFQ210dataAccess9STARTMODEii(*(u32 *)(iStack_10 + 0xd8),1,0,0);
    *(u32 *)(iStack_10 + 0xd8) = 0;
    fadeout__7primWinFi(*(u32 *)(iStack_10 + 100),1);
    *(u32 *)(iStack_10 + 0xe0) = 0x16;
    break;
  case 0x16:
    if (*(int *)(iStack_10 + 0xf0) == 3) {
      *(u32 *)(iStack_10 + 0xe0) = 0x17;
    }
    else if (*(int *)(iStack_10 + 0xf0) == 5) {
      *(u32 *)(iStack_10 + 0xe0) = 0x27;
    }
    break;
  case 0x17:
    if (*(int *)(iStack_10 + 0xf0) == 4) {
      fadein__7primWinFi(*(u32 *)(iStack_10 + 100),1);
      *(u32 *)(iStack_10 + 0xe0) = 0x10;
    }
    break;
  case 0x18:
    if (*(int *)(iStack_10 + 0x70) == 0) {
      mSetupTrialMovieWin__14openingMessageFv(iStack_10);
    }
    else {
      if (*(int *)(iStack_10 + 0x74) == 0) {
        lVar6 = __nw__FUi(0x10c);
        uVar4 = 0;
        if (lVar6 != 0) {
          uVar4 = __ct__10primCursorFv(lVar6);
        }
        *(u32 *)(iStack_10 + 0x74) = uVar4;
        createCursor__10primCursorFiiii(*(u32 *)(iStack_10 + 0x74),0,2,8,10);
        iStack_40 = *(int *)(iStack_10 + 0x70);
        iStack_74 = iStack_40 + 0x3c;
        iStack_70 = iStack_74;
        setItem__10primCursorFP10MenuWindowi(*(u32 *)(iStack_10 + 0x74),iStack_74,0);
        qMove__10primCursorFv(*(u32 *)(iStack_10 + 0x74));
      }
      *(u32 *)(iStack_10 + 0xe0) = 0x19;
    }
    break;
  case 0x19:
    if ((uVar1 & 0x2000) == 0) {
      if ((uVar1 & 0x4000) == 0) {
        iStack_24 = *(int *)(iStack_10 + 0x78);
        uVar4 = menuCheckKey__7primWinFiP10primCursor
                          (*(u32 *)(iStack_10 + 0x70),uVar2,*(u32 *)(iStack_10 + 0x74)
                          );
        *(u32 *)(iStack_10 + 0x78) = uVar4;
        if (iStack_24 != *(int *)(iStack_10 + 0x78)) {
          play__9primSoundFi(*(u32 *)(iStack_10 + 0x5c),0);
        }
      }
      else {
        play__9primSoundFi(*(u32 *)(iStack_10 + 0x5c),3);
        if (*(int *)(iStack_10 + 0x74) != 0) {
          DelayDeleteRequest__10primCursorFv(*(u32 *)(iStack_10 + 0x74));
          *(u32 *)(iStack_10 + 0x74) = 0;
        }
        mReleaseTrialMovieWin__14openingMessageFv(iStack_10);
        mSetupTrialMainWin__14openingMessageFv(iStack_10);
        *(u32 *)(iStack_10 + 0xe0) = 0x12;
      }
    }
    else {
      play__9primSoundFi(*(u32 *)(iStack_10 + 0x5c),2);
      if (*(int *)(iStack_10 + 0x74) != 0) {
        DelayDeleteRequest__10primCursorFv(*(u32 *)(iStack_10 + 0x74));
        *(u32 *)(iStack_10 + 0x74) = 0;
      }
      iVar3 = *(int *)(sm_pSubstance__15SaveMenuSection + 0xc);
      iStack_78 = iVar3 + 0x26c;
      if (*(int *)(iStack_10 + 0x78) == 0) {
        uStack_7c = 0;
      }
      else {
        uStack_7c = 2;
      }
      *(u8 *)(iVar3 + 0x274) = *(u8 *)(iVar3 + 0x274) & 0xfc | (u8)uStack_7c;
      iStack_20 = iStack_78;
      UpdateVibration__15SaveMenuSectionFv();
      mReleaseTrialMovieWin__14openingMessageFv(iStack_10);
      mSetupTrialMainWin__14openingMessageFv(iStack_10);
      *(u32 *)(iStack_10 + 0xe0) = 0x12;
    }
    break;
  case 0x1a:
    iStack_28 = *(int *)(iStack_10 + 100);
    if (*(char *)(iStack_28 + 0x102) == '\0') {
      lVar6 = isFade__7primWinFv(*(u32 *)(iStack_10 + 100));
      if (lVar6 == 0) {
        changeDispMode__14openingMessageFii(iStack_10,0x280,0x1c0);
        mSetupTrialWin__14openingMessageFv(iStack_10);
        fadeout__7primWinFi(*(u32 *)(iStack_10 + 100),0x20);
      }
    }
    else {
      *(u32 *)(iStack_10 + 0xec) = 0;
      *(u32 *)(iStack_10 + 0xe0) = 0x1b;
    }
    break;
  case 0x1b:
    *(int *)(iStack_10 + 0xec) = *(int *)(iStack_10 + 0xec) + 1;
    if ((0x1c2 < *(int *)(iStack_10 + 0xec)) || ((uVar1 & 0x2008) != 0)) {
      *(u32 *)(iStack_10 + 0xe0) = 0x1c;
      fadein__7primWinFi(*(u32 *)(iStack_10 + 100),0x20);
    }
    break;
  case 0x1c:
    lVar6 = isFade__7primWinFv(*(u32 *)(iStack_10 + 100));
    if (lVar6 == 0) {
      mReleaseTrialWin__14openingMessageFv(iStack_10);
      fadeout__7primWinFi(*(u32 *)(iStack_10 + 100),1);
      *(u32 *)(iStack_10 + 0xe0) = 10;
    }
    break;
  case 0x1d:
    fadeout__7primWinFi(*(u32 *)(iStack_10 + 100),1);
    changeDispMode__14openingMessageFii(iStack_10,0x280,0x1c0);
    lVar6 = Reset__9LSDPlayerFv(sys__9LSDPlayer);
    if (lVar6 != 0) {
      m_bLSDStart = '\0';
      iVar3 = *(int *)(iStack_10 + 0x78);
      if (iVar3 == 2) {
        uVar7 = SetPathname__7SysToolFPcPCc(auStack_280,0x4013a8);
        startStream__9LSDPlayerFPc(sys__9LSDPlayer,uVar7);
      }
      else if (iVar3 == 1) {
        uVar7 = SetPathname__7SysToolFPcPCc(auStack_280,0x401398);
        startStream__9LSDPlayerFPc(sys__9LSDPlayer,uVar7);
      }
      else if (iVar3 == 0) {
        uVar7 = SetPathname__7SysToolFPcPCc(auStack_280,0x401388);
        startStream__9LSDPlayerFPc(sys__9LSDPlayer,uVar7);
      }
      *(u32 *)(iStack_10 + 0xe0) = 0x1e;
      *(u32 *)(iStack_10 + 0xe8) = 0x1e;
    }
    break;
  case 0x1e:
    if (m_bLSDStart != '\0') {
      if ((uVar1 & 0x2008) == 0) {
        lVar6 = Reset__9LSDPlayerFv(sys__9LSDPlayer);
        if (lVar6 != 0) {
          *(u32 *)(iStack_10 + 0xe0) = 0x1f;
          fadein__7primWinFi(*(u32 *)(iStack_10 + 100),8);
        }
      }
      else {
        Pause__9LSDPlayerFv(sys__9LSDPlayer);
        Exit__9LSDPlayerFv(sys__9LSDPlayer);
        *(u32 *)(iStack_10 + 0xe0) = 0x1f;
        fadein__7primWinFi(*(u32 *)(iStack_10 + 100),8);
      }
    }
    break;
  case 0x1f:
    lVar6 = isFade__7primWinFv(*(u32 *)(iStack_10 + 100));
    if (lVar6 == 0) {
      SetFFMode__3GsxFibi(0,1,1);
      *(u32 *)(iStack_10 + 0xe0) = 0x10;
    }
    break;
  case 0x20:
    iStack_44 = *(int *)(iStack_10 + 100);
    if (*(char *)(iStack_44 + 0x102) == '\0') {
      lVar6 = isFade__7primWinFv(*(u32 *)(iStack_10 + 100));
      if (lVar6 == 0) {
        changeDispMode__14openingMessageFii(iStack_10,0x200,0x1c0);
        iStack_48 = *(int *)(iStack_10 + 0xd0);
        *(u8 *)(iStack_48 + 0x3d) = 0x11;
        fadeout__7primWinFi(*(u32 *)(iStack_10 + 100),0x20);
      }
    }
    else {
      *(u32 *)(iStack_10 + 0xe0) = 0x21;
    }
    break;
  case 0x21:
    if (m_MenuNum == 2) {
      *(u32 *)(iStack_10 + 0xe0) = 0x22;
      fadein__7primWinFi(*(u32 *)(iStack_10 + 100),0x20);
    }
    break;
  case 0x22:
    lVar6 = isFade__7primWinFv(*(u32 *)(iStack_10 + 100));
    if (lVar6 == 0) {
      *(u32 *)(iStack_10 + 0xe0) = 0x10;
    }
    break;
  case 0x23:
    fadeout__7primWinFi(*(u32 *)(iStack_10 + 100),1);
    changeDispMode__14openingMessageFii(iStack_10,0x200,0x1c0);
    uVar7 = SetFFMode__3GsxFibi(0,1,2);
    start__17openingBattleDemoFv(*(u32 *)(iStack_10 + 0xd4),uVar7);
    *(u32 *)(iStack_10 + 0xec) = 0;
    *(u32 *)(iStack_10 + 0xe0) = 0x24;
    break;
  case 0x24:
    if (*(char *)(*(int *)(iStack_10 + 0xd4) + 0x23) != '\0') {
      *(u32 *)(iStack_10 + 0xe0) = 0x25;
    }
    break;
  case 0x25:
    iStack_50 = *(int *)(iStack_10 + 0xd4);
    if (*(char *)(iStack_50 + 0x21) == '\0') {
      *(u32 *)(iStack_10 + 0xe0) = 0x10;
    }
    else {
      *(u32 *)(iStack_10 + 0xe0) = 10;
    }
    if (*(int *)(iStack_10 + 0xd4) != 0) {
      iVar3 = *(int *)(iStack_10 + 0xd4);
      if (iVar3 != 0) {
        VCALL14(iVar3, 8)(iVar3,1);
      }
      *(u32 *)(iStack_10 + 0xd4) = 0;
    }
    if (*(int *)(iStack_10 + 0xe0) != 10) {
      fadein__7primWinFi(*(u32 *)(iStack_10 + 100),1);
    }
    break;
  case 0x26:
    puVar5 = (u16 *)GetWorldMapInfo__Fv();
    *puVar5 = 0;
    puVar5[1] = 0;
    *(u32 *)(puVar5 + 2) = 0;
    FieldMapJump__FPCci(0x4013b8,0);
    fadeout__7primWinFi(*(u32 *)(iStack_10 + 100),1);
    changeDispMode__14openingMessageFii(iStack_10,0x200,0x1c0);
    *(u32 *)(iStack_10 + 0xe0) = 0x27;
    break;
  case 0x27:
    *(u32 *)(iStack_10 + 0xe0) = 0x28;
    (**(code **)(*(int *)(iStack_10 + 0x20) + 0xc))();
  }
  return 0;
}

// JP: 0x003aa020  CBEntry__14openingMessageFiPv  size 0x24
// openingMessage::CBEntry(int, void*)
void CBEntry__14openingMessageFiPv(u32 param_1,int this)
{
  this->cb_event = param_1;
  return;
}

// JP: 0x003aa050  mSetupFader__14openingMessageFv  size 0x108
// openingMessage::mSetupFader()
void mSetupFader__14openingMessageFv(openingMessage *this)
{
  u32 uVar1;
  long lVar2;
  lVar2 = __nw__FUi(0x148);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = __ct__7primWinFv(lVar2);
  }
  this->fader = uVar1;
  uVar1 = this->fader;
  initialize__7primWinFP7primTex(uVar1,0);
  setItem__7primWinFiii(uVar1,1,1,0);
  createPoly__7primWinFiiiiii(uVar1,0,0,0,0,0x280,0x1c0);
  setPolyRGBA__7primWinFiiiii(uVar1,0,0,0,0,0x80);
  buildWin__7primWinFiiiiii(uVar1,0xf,0xffffffffffffffc0,0,0,0,0);
  fadein__7primWinFi(uVar1,1);
  return;
}

// JP: 0x003aa160  mReleaseFader__14openingMessageFv  size 0x48
// openingMessage::mReleaseFader()
void mReleaseFader__14openingMessageFv(openingMessage *this)
{
  if (this->fader != 0) {
    DelayDeleteRequest__7primWinFv(this->fader);
    this->fader = 0;
  }
  return;
}

// JP: 0x003aa1b0  mSetupTitleWin__14openingMessageFv  size 0xccc
// openingMessage::mSetupTitleWin()
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
void mSetupTitleWin__14openingMessageFv(openingMessage *this)
{
  u32 uVar1;
  long lVar2;
  int iVar3;
  u32 uStack_f0;
  u32 uStack_ec;
  u32 uStack_e8;
  u32 uStack_e4;
  u64 uStack_e0;
  u8 auStack_d0 [20];
  u32 uStack_bc;
  u32 uStack_b8;
  u32 uStack_b4;
  u32 uStack_b0;
  u32 uStack_ac;
  u32 uStack_a8;
  u32 uStack_a4;
  u32 uStack_a0;
  int iStack_9c;
  u32 uStack_98;
  u32 uStack_94;
  int iStack_90;
  u32 uStack_8c;
  u32 uStack_88;
  int iStack_84;
  u32 uStack_80;
  u32 uStack_7c;
  int iStack_78;
  int iStack_74;
  int iStack_70;
  int iStack_6c;
  int iStack_68;
  int iStack_64;
  int iStack_60;
  int iStack_5c;
  int iStack_58;
  u32 uStack_54;
  int iStack_50;
  u32 uStack_4c;
  int iStack_48;
  u32 uStack_44;
  int iStack_40;
  u32 uStack_3c;
  int iStack_38;
  u32 uStack_34;
  int iStack_30;
  u32 uStack_2c;
  int iStack_28;
  u32 uStack_24;
  int iStack_20;
  float fStack_1c;
  int iStack_18;
  int iStack_14;
  int iStack_10;
  iStack_10 = this;
  __ct__9BufMemoryFv(auStack_d0);
  iStack_14 = 6;
  uStack_f0 = (u32)__7982;
  uStack_ec = (u32)((ulong)__7982 >> 0x20);
  uStack_e8 = DAT_003fa538;
  uStack_e4 = DAT_003fa53c;
  uStack_e0 = DAT_003fa540;
  iStack_74 = __nw__FUi(0x148);
  if (iStack_74 != 0) {
    iStack_74 = __ct__7primWinFv(iStack_74);
  }
  *(int *)(iStack_10 + 0x6c) = iStack_74;
  uVar1 = *(u32 *)(iStack_10 + 0x6c);
  initialize__7primWinFP7primTex(uVar1,m_pPT);
  setItem__7primWinFiii(uVar1,iStack_14,iStack_14,0);
  for (iVar3 = 0; iVar3 < iStack_14; iVar3 = iVar3 + 1) {
    setTex__7primWinFiiii(uVar1,iVar3 + 1,iVar3,0,0);
    createTexPoly__7primWinFiiiiii
              (uVar1,iVar3,iVar3,*(short *)(&uStack_f0 + iVar3) + -0x40,
               *(u16 *)((int)&uStack_f0 + (iVar3 * 2 + 1) * 2),0,0);
  }
  setPolyAlpha__7primWinFii(uVar1,0,0x80);
  setPolyAlpha__7primWinFii(uVar1,4,0);
  buildWin__7primWinFiiiiii(uVar1,3,0,0,0,0,0);
  *(u32 *)(iStack_10 + 0xc4) = 0;
  iStack_18 = 0x40;
  fStack_1c = 0.0002;
  iStack_78 = __nw__FUi(0x260);
  if (iStack_78 != 0) {
    iStack_78 = __ct__6prim2DFi(iStack_78,6);
  }
  *(int *)(iStack_10 + 0x80) = iStack_78;
  iStack_58 = m_TexPool;
  uStack_80 = *(u32 *)(m_TexPool + 4);
  iStack_20 = *(int *)(iStack_10 + 0x80);
  *(u32 *)(iStack_20 + 0x30) = uStack_80;
  uStack_7c = uStack_80;
  uStack_24 = uStack_80;
  setDisp__6prim2DFiffff
            ((float)-iStack_18,0,0x3f800000,0x3f800000,*(u32 *)(iStack_10 + 0x80),0);
  iStack_84 = __nw__FUi(0x260);
  if (iStack_84 != 0) {
    iStack_84 = __ct__6prim2DFi(iStack_84,6);
  }
  *(int *)(iStack_10 + 0x84) = iStack_84;
  iStack_5c = m_TexPool;
  uStack_8c = *(u32 *)(m_TexPool + 4);
  iStack_28 = *(int *)(iStack_10 + 0x84);
  *(u32 *)(iStack_28 + 0x30) = uStack_8c;
  uStack_88 = uStack_8c;
  uStack_2c = uStack_8c;
  setDisp__6prim2DFiffff
            (0xc2400000,0x43f80000,0x3f800000,0x3f800000,*(u32 *)(iStack_10 + 0x84),0xd);
  setRot__6prim2DFf(-fStack_1c,*(u32 *)(iStack_10 + 0x84));
  setRGBA__6prim2DFiiii(*(u32 *)(iStack_10 + 0x84),0x7f,0x7f,0x7f,0x19);
  setDispWidth__6prim2DFf(0x3f8ccccd,*(u32 *)(iStack_10 + 0x84));
  setBlendMode__6prim2DFi(*(u32 *)(iStack_10 + 0x84),1);
  setCenterMode__6prim2DFi(*(u32 *)(iStack_10 + 0x84),4);
  iStack_90 = __nw__FUi(0x260);
  if (iStack_90 != 0) {
    iStack_90 = __ct__6prim2DFi(iStack_90,6);
  }
  *(int *)(iStack_10 + 0x88) = iStack_90;
  iStack_60 = m_TexPool;
  uStack_98 = *(u32 *)(m_TexPool + 4);
  iStack_30 = *(int *)(iStack_10 + 0x88);
  *(u32 *)(iStack_30 + 0x30) = uStack_98;
  uStack_94 = uStack_98;
  uStack_34 = uStack_98;
  setDisp__6prim2DFiffff
            (0xc2400000,0x43f80000,0x3f800000,0x3f800000,*(u32 *)(iStack_10 + 0x88),0xe);
  setRot__6prim2DFf(-fStack_1c,*(u32 *)(iStack_10 + 0x88));
  setRGBA__6prim2DFiiii(*(u32 *)(iStack_10 + 0x88),0x7f,0x7f,0x7f,0x19);
  setDispWidth__6prim2DFf(0x3f8ccccd,*(u32 *)(iStack_10 + 0x88));
  setBlendMode__6prim2DFi(*(u32 *)(iStack_10 + 0x88),1);
  setCenterMode__6prim2DFi(*(u32 *)(iStack_10 + 0x88),1);
  iStack_9c = __nw__FUi(0x260);
  if (iStack_9c != 0) {
    iStack_9c = __ct__6prim2DFi(iStack_9c,6);
  }
  *(int *)(iStack_10 + 0x8c) = iStack_9c;
  iStack_64 = m_TexPool;
  uStack_a4 = *(u32 *)(m_TexPool + 4);
  iStack_38 = *(int *)(iStack_10 + 0x8c);
  *(u32 *)(iStack_38 + 0x30) = uStack_a4;
  uStack_a0 = uStack_a4;
  uStack_3c = uStack_a4;
  setDisp__6prim2DFiffff
            (0xc2400000,0x43f80000,0x3f800000,0x3f800000,*(u32 *)(iStack_10 + 0x8c),0xf);
  setRot__6prim2DFf(-fStack_1c,*(u32 *)(iStack_10 + 0x8c));
  setRGBA__6prim2DFiiii(*(u32 *)(iStack_10 + 0x8c),0x7f,0x7f,0x7f,0x19);
  setDispWidth__6prim2DFf(0x3f8ccccd,*(u32 *)(iStack_10 + 0x8c));
  setBlendMode__6prim2DFi(*(u32 *)(iStack_10 + 0x8c),1);
  setCenterMode__6prim2DFi(*(u32 *)(iStack_10 + 0x8c),3);
  lVar2 = __nw__FUi(0x260);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = __ct__6prim2DFi(lVar2,6);
  }
  *(u32 *)(iStack_10 + 0x90) = uVar1;
  iStack_68 = m_TexPool;
  uStack_ac = *(u32 *)(m_TexPool + 4);
  iStack_40 = *(int *)(iStack_10 + 0x90);
  *(u32 *)(iStack_40 + 0x30) = uStack_ac;
  uStack_a8 = uStack_ac;
  uStack_44 = uStack_ac;
  setDisp__6prim2DFiffff
            (0xc2400000,0x43f80000,0x3f800000,0x3f800000,*(u32 *)(iStack_10 + 0x90),0x10);
  setRot__6prim2DFf(-fStack_1c,*(u32 *)(iStack_10 + 0x90));
  setRGBA__6prim2DFiiii(*(u32 *)(iStack_10 + 0x90),0x7f,0x7f,0x7f,0x19);
  setDispWidth__6prim2DFf(0x3f8ccccd,*(u32 *)(iStack_10 + 0x90));
  setBlendMode__6prim2DFi(*(u32 *)(iStack_10 + 0x90),1);
  setCenterMode__6prim2DFi(*(u32 *)(iStack_10 + 0x90),0);
  lVar2 = __nw__FUi(0x260);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = __ct__6prim2DFi(lVar2,6);
  }
  *(u32 *)(iStack_10 + 0x94) = uVar1;
  iStack_6c = m_TexPool;
  uStack_b4 = *(u32 *)(m_TexPool + 4);
  iStack_48 = *(int *)(iStack_10 + 0x94);
  *(u32 *)(iStack_48 + 0x30) = uStack_b4;
  uStack_b0 = uStack_b4;
  uStack_4c = uStack_b4;
  setDisp__6prim2DFiffff
            (0xc2400000,0x43f80000,0x3f800000,0x3f800000,*(u32 *)(iStack_10 + 0x94),0x11);
  setRot__6prim2DFf(fStack_1c * 3.0,*(u32 *)(iStack_10 + 0x94));
  setRGBA__6prim2DFiiii(*(u32 *)(iStack_10 + 0x94),0x7f,0x7f,0x7f,0x19);
  setDispWidth__6prim2DFf(0x3f8ccccd,*(u32 *)(iStack_10 + 0x94));
  setBlendMode__6prim2DFi(*(u32 *)(iStack_10 + 0x94),1);
  setCenterMode__6prim2DFi(*(u32 *)(iStack_10 + 0x94),2);
  lVar2 = __nw__FUi(0x260);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = __ct__6prim2DFi(lVar2,6);
  }
  *(u32 *)(iStack_10 + 0x98) = uVar1;
  iStack_70 = m_TexPool;
  uStack_bc = *(u32 *)(m_TexPool + 4);
  iStack_50 = *(int *)(iStack_10 + 0x98);
  *(u32 *)(iStack_50 + 0x30) = uStack_bc;
  uStack_b8 = uStack_bc;
  uStack_54 = uStack_bc;
  setDisp__6prim2DFiffff
            (0xc2400000,0x43f80000,0x3f800000,0x3f800000,*(u32 *)(iStack_10 + 0x98),0x12);
  setRGBA__6prim2DFiiii(*(u32 *)(iStack_10 + 0x98),0x7f,0x7f,0x7f,0x19);
  setDispWidth__6prim2DFf(0x3f8ccccd,*(u32 *)(iStack_10 + 0x98));
  setBlendMode__6prim2DFi(*(u32 *)(iStack_10 + 0x98),1);
  setCenterMode__6prim2DFi(*(u32 *)(iStack_10 + 0x98),2);
  *(u32 *)(iStack_10 + 0xbc) = 7;
  if (*(int *)(iStack_10 + 0x60) != 0) {
    DelayDeleteRequest__9primMusicFv(*(u32 *)(iStack_10 + 0x60));
    *(u32 *)(iStack_10 + 0x60) = 0;
  }
  lVar2 = __nw__FUi(0x38);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = __ct__9primMusicFv(lVar2);
  }
  *(u32 *)(iStack_10 + 0x60) = uVar1;
  initialize__9primMusicFi(*(u32 *)(iStack_10 + 0x60),1);
  play__9primMusicFPc(*(u32 *)(iStack_10 + 0x60),0x401480);
  __dt__9BufMemoryFv(auStack_d0,0xffffffffffffffff);
  return;
}

// JP: 0x003aae80  mReleaseTitleWin__14openingMessageFv  size 0xbc
// openingMessage::mReleaseTitleWin()
void mReleaseTitleWin__14openingMessageFv(openingMessage *this)
{
  int iVar1;
  for (iVar1 = 0; iVar1 < this->n_title_sprite; iVar1 = iVar1 + 1) {
    if (*(int *)(this + iVar1 * 4 + 0x80) != 0) {
      DelayDeleteRequest__6prim2DFv(*(u32 *)(this + iVar1 * 4 + 0x80));
      *(u32 *)(this + iVar1 * 4 + 0x80) = 0;
    }
  }
  if (this->title != 0) {
    DelayDeleteRequest__7primWinFv(this->title);
    this->title = 0;
  }
  return;
}

// JP: 0x003aaf40  mReleaseMenuWin__14openingMessageFv  size 0x70
// openingMessage::mReleaseMenuWin()
void mReleaseMenuWin__14openingMessageFv(openingMessage *this)
{
  if (this->menu != 0) {
    DelayDeleteRequest__7primWinFv(this->menu);
    this->menu = 0;
  }
  if (this->cursor != 0) {
    DelayDeleteRequest__10primCursorFv(this->cursor);
    this->cursor = 0;
  }
  return;
}

// JP: 0x003aafb0  mSetupTrialWin__14openingMessageFv  size 0x10c
// openingMessage::mSetupTrialWin()
void mSetupTrialWin__14openingMessageFv(openingMessage *this)
{
  u32 uVar1;
  long lVar2;
  lVar2 = __nw__FUi(0x148);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = __ct__7primWinFv(lVar2);
  }
  this->menu = uVar1;
  uVar1 = this->menu;
  this->sel = 0;
  initialize__7primWinFP7primTex(uVar1,m_pPT);
  setItem__7primWinFiii(uVar1,1,1,0);
  setTex__7primWinFiiii(uVar1,0x14,0,0,0);
  createTexPoly__7primWinFiiiiii(uVar1,0,0,0,0,0,0);
  buildWin__7primWinFiiiiii(uVar1,3,0xffffffffffffffc0,0,0,0,0);
  fadein__7primWinFi(uVar1,0x20);
  return;
}

// JP: 0x003ab0c0  mReleaseTrialWin__14openingMessageFv  size 0x48
// openingMessage::mReleaseTrialWin()
void mReleaseTrialWin__14openingMessageFv(openingMessage *this)
{
  if (this->menu != 0) {
    DelayDeleteRequest__7primWinFv(this->menu);
    this->menu = 0;
  }
  return;
}

// JP: 0x003ab110  mSetupTrialMainWin__14openingMessageFv  size 0x174
// openingMessage::mSetupTrialMainWin()
void mSetupTrialMainWin__14openingMessageFv(openingMessage *this)
{
  u32 uVar1;
  long lVar2;
  lVar2 = __nw__FUi(0x148);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = __ct__7primWinFv(lVar2);
  }
  this->menu = uVar1;
  uVar1 = this->menu;
  this->sel = 0;
  initialize__7primWinFP7primTex(uVar1,m_pPT);
  setItem__7primWinFiii(uVar1,2,0,2);
  setTextArea__7primWinFiiib(uVar1,1,0x100,0x100,1);
  createText__7primWinFiiiiPciib(uVar1,0,1,0,0,0x401498,0,0);
  createText__7primWinFiiiiPciib(uVar1,1,1,0,0x20,0x4014a8,0,0);
  setMenuWindow__7primWinFiiiii(uVar1,2,0,0,0xffffffffffffffff,0xffffff);
  buildWin__7primWinFiiiiii(uVar1,3,200,300,0,0,0);
  fadein__7primWinFi(uVar1,0x10);
  return;
}

// JP: 0x003ab290  mReleaseTrialMainWin__14openingMessageFv  size 0x48
// openingMessage::mReleaseTrialMainWin()
void mReleaseTrialMainWin__14openingMessageFv(openingMessage *this)
{
  if (this->menu != 0) {
    DelayDeleteRequest__7primWinFv(this->menu);
    this->menu = 0;
  }
  return;
}

// JP: 0x003ab2e0  mSetupTrialMovieWin__14openingMessageFv  size 0x1a8
// openingMessage::mSetupTrialMovieWin()
void mSetupTrialMovieWin__14openingMessageFv(openingMessage *this)
{
  u32 uVar1;
  long lVar2;
  lVar2 = __nw__FUi(0x148);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = __ct__7primWinFv(lVar2);
  }
  this->menu = uVar1;
  uVar1 = this->menu;
  this->sel = 0;
  initialize__7primWinFP7primTex(uVar1,m_pPT);
  setItem__7primWinFiii(uVar1,2,0,3);
  setTextArea__7primWinFiiib(uVar1,1,0x100,0x100,1);
  createText__7primWinFiiiiPciib(uVar1,0,1,0x14,0x34,0x4014b8,0,0);
  createText__7primWinFiiiiPciib(uVar1,1,1,0x14,0x48,0x4014c0,0,0);
  createText__7primWinFiiiiPciib(uVar1,2,1,0,0x14,0x4014a8,0,0);
  setMenuWindow__7primWinFiiiii(uVar1,2,0,0,0xffffffffffffffff,0xffffff);
  buildWin__7primWinFiiiiii(uVar1,3,200,0x118,0,0,0);
  fadein__7primWinFi(uVar1,0x10);
  return;
}

// JP: 0x003ab490  mReleaseTrialMovieWin__14openingMessageFv  size 0x48
// openingMessage::mReleaseTrialMovieWin()
void mReleaseTrialMovieWin__14openingMessageFv(openingMessage *this)
{
  if (this->menu != 0) {
    DelayDeleteRequest__7primWinFv(this->menu);
    this->menu = 0;
  }
  return;
}

// JP: 0x003ab500  @24@__dt__14openingMessageFv  size 0x8
// @24@__dt__14openingMessageFv
int _24___dt__14openingMessageFv(openingMessage *this,short param_2)
{
  int iVar1;
  iVar1 = this + -0x18;
  if (iVar1 != 0) {
    *(u8 **)(this + -4) = __vt__14openingMessage;
    this->vptr = 0x407460;
    if (sys__9LSDPlayer != 0) {
      if (sys__9LSDPlayer != 0) {
        VCALL14(sys__9LSDPlayer, 8)(sys__9LSDPlayer,1);
      }
    }
    if (m_pPT != 0) {
      __dt__7primTexFv(m_pPT,1);
      m_pPT = 0;
    }
    mReleaseFader__14openingMessageFv(iVar1);
    Dispose__7CPollerFP7CPolObj(app__4CApp + 0x48,iVar1);
    if (this->f_44 /*int **/ != 0) {
      DelayDeleteRequest__9primSoundFv(this->f_44 /*u32 **/);
      this->f_44 /*u32 **/ = 0;
    }
    if (this->f_48 /*int **/ != 0) {
      DelayDeleteRequest__9primMusicFv(this->f_48 /*u32 **/);
      this->f_48 /*u32 **/ = 0;
    }
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
