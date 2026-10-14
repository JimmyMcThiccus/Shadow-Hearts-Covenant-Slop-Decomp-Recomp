/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: tailor   functions: 27
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/tailor.md).
 */

/* JP: 0x004eafe0  tailor::DVD_CBFunc(int, BufMemory*, int, char*, void*)   [DVD_CBFunc__6tailorFiP9BufMemoryiPcPv]  size=0xa4 */
undefined8 DVD_CBFunc__6tailorFiP9BufMemoryiPcPv(undefined8 param_1,int param_2)

{
  undefined4 uVar1;
  long lVar2;
  
  if (m_bModel == '\0') {
    m_TexRead = 1;
    lVar2 = __nw__FUi(0x52c);
    uVar1 = 0;
    if (lVar2 != 0) {
      uVar1 = __ct__7primTexFv(lVar2);
    }
    m_pPT = uVar1;
    initialize__7primTexFP9BufMemory(m_pPT,param_2);
    m_pBuffer = *(undefined4 *)(param_2 + 4);
  }
  else {
    m_TexRead = 1;
    m_pModel = param_2;
  }
  return 0;
}

/* JP: 0x004eb090  tailor::tailor()   [__ct__6tailorFv]  size=0x128 */
undefined8 __ct__6tailorFv(undefined8 param_1)

{
  undefined1 auVar1 [16];
  uint uVar2;
  int iVar3;
  int iVar4;
  undefined1 in_vf0 [16];
  undefined1 auVar5 [16];
  undefined1 auVar6 [16];
  undefined1 auVar7 [16];
  
  __ct__7CPolObjFv(param_1);
  iVar4 = (int)param_1;
  *(undefined4 *)(iVar4 + 0x18) = 0;
  *(undefined4 *)(iVar4 + 0x1c) = 0;
  *(undefined1 **)(iVar4 + 0x20) = &__vt__17DelayDeleteObject;
  *(undefined1 **)(iVar4 + 0x14) = &__vt__6tailor;
  *(undefined4 *)(iVar4 + 0x20) = 0x409810;
  auVar5 = _vmr32(in_vf0);
  auVar6 = _vmr32(auVar5);
  auVar7 = _vmr32(auVar6);
  auVar1 = _sqc2(in_vf0);
  *(undefined1 (*) [16])(iVar4 + 0x100) = auVar1;
  auVar1 = _sqc2(auVar5);
  *(undefined1 (*) [16])(iVar4 + 0xf0) = auVar1;
  auVar1 = _sqc2(auVar6);
  *(undefined1 (*) [16])(iVar4 + 0xe0) = auVar1;
  auVar1 = _sqc2(auVar7);
  *(undefined1 (*) [16])(iVar4 + 0xd0) = auVar1;
  *(undefined4 *)(iVar4 + 0x60) = 0;
  *(undefined4 *)(iVar4 + 100) = 0;
  *(undefined4 *)(iVar4 + 0x68) = 0;
  *(undefined4 *)(iVar4 + 0x80) = 0;
  *(undefined4 *)(iVar4 + 0x84) = 0;
  *(undefined4 *)(iVar4 + 0x6c) = 0;
  *(undefined4 *)(iVar4 + 0x70) = 0;
  *(undefined4 *)(iVar4 + 0x78) = 0;
  *(undefined4 *)(iVar4 + 0x74) = 0;
  *(undefined4 *)(iVar4 + 0x7c) = 0;
  *(undefined4 *)(iVar4 + 0x150) = 0;
  *(undefined4 *)(iVar4 + 0x154) = 0;
  *(undefined4 *)(iVar4 + 0x160) = 0;
  *(undefined4 *)(iVar4 + 0x90) = 0;
  *(undefined4 *)(iVar4 + 0x88) = 0;
  *(undefined4 *)(iVar4 + 0x94) = 0;
  *(undefined4 *)(iVar4 + 0x98) = 0;
  *(undefined4 *)(iVar4 + 0x9c) = 0;
  *(undefined4 *)(iVar4 + 0xa0) = 0;
  *(undefined4 *)(iVar4 + 0xa4) = 0;
  *(undefined4 *)(iVar4 + 0xc4) = 0;
  m_pModel = 0;
  *(undefined4 *)(iVar4 + 0x14c) = 0;
  for (iVar3 = 0; iVar3 < 5; iVar3 = iVar3 + 1) {
    *(undefined4 *)(iVar4 + iVar3 * 4 + 0xb0) = 0;
    uVar2 = rand();
    *(uint *)(iVar4 + iVar3 * 4 + 0x4c) = uVar2 & 0xff;
  }
  return param_1;
}

/* JP: 0x004eb1c0  tailor::~tailor()   [__dt__6tailorFv]  size=0x1e0 */
int __dt__6tailorFv(int param_1,short param_2)

{
  int iVar1;
  
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 0x14) = &__vt__6tailor;
    *(undefined4 *)(param_1 + 0x20) = 0x409810;
    Dispose__7CPollerFP7CPolObj(app__4CApp + 0x48,param_1);
    if (m_pPT != 0) {
      __dt__7primTexFv(m_pPT,1);
      m_pPT = 0;
    }
    if (*(int *)(param_1 + 0x150) != 0) {
      DelayDeleteRequest__9primSoundFv(*(undefined4 *)(param_1 + 0x150));
      *(undefined4 *)(param_1 + 0x150) = 0;
    }
    if (*(int *)(param_1 + 0x154) != 0) {
      DelayDeleteRequest__9primSoundFv(*(undefined4 *)(param_1 + 0x154));
      *(undefined4 *)(param_1 + 0x154) = 0;
    }
    (**(code **)(*(int *)(*(int *)(param_1 + 0x88) + 8) + 0x18))();
    if (*(int *)(param_1 + 0x88) != 0) {
      iVar1 = *(int *)(param_1 + 0x88);
      if (iVar1 != 0) {
        (**(code **)(*(int *)(iVar1 + 8) + 8))(iVar1,1);
      }
      *(undefined4 *)(param_1 + 0x88) = 0;
    }
    if (m_pModel != 0) {
      __dt__9BufMemoryFv(m_pModel,1);
      m_pModel = 0;
    }
    if (*(int *)(param_1 + 0x14c) != 0) {
      __dt__9BufMemoryFv(*(undefined4 *)(param_1 + 0x14c),1);
      *(undefined4 *)(param_1 + 0x14c) = 0;
    }
    if (param_1 != -0x18) {
      *(undefined1 **)(param_1 + 0x20) = &__vt__17DelayDeleteObject;
    }
    __dt__7CPolObjFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x004eb3a0  tailor::initialize(void(*)(int, void*)*, void*, int)   [initialize__6tailorFPFiPv_vPvi]  size=0x170 */
void initialize__6tailorFPFiPv_vPvi
               (int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  long lVar2;
  undefined8 uVar3;
  undefined1 auStack_140 [256];
  int iStack_40;
  undefined4 uStack_30;
  undefined4 uStack_20;
  undefined4 uStack_10;
  
  iStack_40 = param_1;
  uStack_30 = param_2;
  uStack_20 = param_3;
  uStack_10 = param_4;
  lVar2 = __nw__FUi(0x6b0);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = __ct__10CmdElementFv(lVar2);
  }
  *(undefined4 *)(iStack_40 + 0x88) = uVar1;
  OrderFile__9MenuSceneFPCcP4Menu(*(undefined4 *)(iStack_40 + 0x88),0x55b770,0);
  Entry__7CPollerFP7CPolObjib(app__4CApp + 0x48,iStack_40,0x80,0);
  *(undefined1 *)(iStack_40 + 0x38) = 0;
  *(undefined4 *)(iStack_40 + 0x30) = uStack_10;
  *(undefined4 *)(iStack_40 + 0x2c) = 0;
  m_TexRead = 0;
  m_bModel = 0;
  uVar3 = SetPathname__7SysToolFPcPCc(auStack_140,0x55b790);
  ReadOrder__11DvdromOrderFPCcPFiP9BufMemoryiPcPv_iiPvi(Dvdromour__11DvdromOrder,uVar3,0x4eafe0,0,iStack_40,0);
  lVar2 = __nw__FUi(0x30);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = __ct__9primSoundFv(lVar2);
  }
  *(undefined4 *)(iStack_40 + 0x150) = uVar1;
  initialize__9primSoundFv(*(undefined4 *)(iStack_40 + 0x150));
  loadSE__9primSoundFPc(*(undefined4 *)(iStack_40 + 0x150),0x55b7a0);
  *(undefined4 *)(iStack_40 + 0x24) = uStack_30;
  *(undefined4 *)(iStack_40 + 0x28) = uStack_20;
  return;
}

/* JP: 0x004eb510  tailor::start()   [start__6tailorFv]  size=0x20 */
void start__6tailorFv(int param_1)

{
  *(undefined1 *)(param_1 + 0x38) = 1;
  return;
}

/* JP: 0x004eb530  tailor::Polling()   [Polling__6tailorFv]  size=0xe4 */
undefined8 Polling__6tailorFv(int param_1)

{
  ushort uVar1;
  int iVar2;
  
  iVar2 = GetActive__4CPadFi(0);
  uVar1 = *(ushort *)(*(int *)(&m_pCoreArray__4CPad + *(int *)(iVar2 + 4) * 4) + 0x70) & 0xf0 |
          *(ushort *)(*(int *)(&m_pCoreArray__4CPad + *(int *)(iVar2 + 4) * 4) + 0x6c);
  if (*(int *)(param_1 + 0x30) == 0) {
    mTailorPolling__6tailorFUs(param_1,uVar1);
  }
  else {
    mMenuPolling__6tailorFUs(param_1,uVar1);
  }
  return 0;
}

/* JP: 0x004eb620  tailor::mTailorPolling(unsigned short)   [mTailorPolling__6tailorFUs]  size=0x1d5c */
void mTailorPolling__6tailorFUs(int param_1,ushort param_2)

{
  int *piVar1;
  undefined1 uVar2;
  undefined4 uVar3;
  long lVar4;
  undefined8 uVar5;
  int iVar6;
  undefined1 auStack_1f0 [256];
  int iStack_f0;
  int iStack_ec;
  int iStack_e8;
  int iStack_e4;
  int iStack_e0;
  int *piStack_dc;
  int *piStack_d8;
  int iStack_d4;
  int iStack_d0;
  int iStack_cc;
  int iStack_c8;
  int iStack_c4;
  int iStack_c0;
  int iStack_bc;
  int iStack_b8;
  int iStack_b4;
  int iStack_b0;
  int iStack_ac;
  int iStack_a8;
  int iStack_a4;
  undefined4 uStack_a0;
  int iStack_9c;
  undefined4 uStack_98;
  int iStack_94;
  int iStack_90;
  int iStack_8c;
  int iStack_88;
  int iStack_84;
  int iStack_80;
  int iStack_7c;
  int iStack_78;
  int iStack_74;
  int iStack_70;
  int iStack_6c;
  int iStack_68;
  int iStack_64;
  int iStack_60;
  int iStack_5c;
  int iStack_58;
  int iStack_54;
  int iStack_50;
  int iStack_4c;
  int iStack_48;
  int iStack_44;
  int iStack_40;
  int iStack_3c;
  int iStack_38;
  int iStack_34;
  int iStack_30;
  int iStack_2c;
  undefined1 uStack_28;
  undefined1 uStack_27;
  undefined1 uStack_26;
  undefined1 uStack_25;
  undefined1 uStack_24;
  undefined1 uStack_23;
  undefined1 uStack_22;
  char cStack_21;
  int iStack_20;
  ushort uStack_10;
  
  iStack_20 = param_1;
  uStack_10 = param_2;
  if ((*(int *)(param_1 + 0x80) != 0) && ((param_2 & 0x2000) != 0)) {
    Finish__11MenuMessageFv(*(undefined4 *)(param_1 + 0x80));
  }
  switch(*(undefined4 *)(iStack_20 + 0x2c)) {
  case 0:
    if ((*(char *)(iStack_20 + 0x38) != '\0') && (m_TexRead != '\0')) {
      *(undefined4 *)(iStack_20 + 0x2c) = 2;
    }
    break;
  case 2:
    if (*(int *)(iStack_20 + 100) == 0) {
      SetFFMode__3GsxFibi(0,1,1);
      *(undefined4 *)(iStack_20 + 0x34) = 0;
      (**(code **)(iStack_20 + 0x24))
                (*(undefined4 *)(iStack_20 + 0x34),*(undefined4 *)(iStack_20 + 0x28));
      mSetupSelectWin__6tailorFv(iStack_20);
      mSetupFWin__6tailorFii(iStack_20,10,0);
      fadeout__7primWinFi(*(undefined4 *)(iStack_20 + 0x74),0x10);
    }
    else {
      *(undefined4 *)(iStack_20 + 0x34) = 1;
      (**(code **)(iStack_20 + 0x24))
                (*(undefined4 *)(iStack_20 + 0x34),*(undefined4 *)(iStack_20 + 0x28));
      *(undefined4 *)(iStack_20 + 0x40) = 0;
      *(undefined4 *)(iStack_20 + 0x2c) = 3;
    }
    break;
  case 3:
    *(int *)(iStack_20 + 0x40) = *(int *)(iStack_20 + 0x40) + 1;
    iStack_50 = *(int *)(iStack_20 + 0x80);
    uStack_22 = *(ushort *)(iStack_50 + 0x76) <= *(ushort *)(iStack_50 + 0x80);
    if ((((bool)uStack_22) && (0x3b < *(int *)(iStack_20 + 0x40))) &&
       (iStack_54 = *(int *)(iStack_20 + 0x150), *(char *)(iStack_54 + 0x2e) != '\0')) {
      lVar4 = __nw__FUi(0x30);
      uVar3 = 0;
      if (lVar4 != 0) {
        uVar3 = __ct__14bookScrollMarkFv(lVar4);
      }
      *(undefined4 *)(iStack_20 + 0x160) = uVar3;
      initialize__14bookScrollMarkFP7primTexii
                (*(undefined4 *)(iStack_20 + 0x160),m_pPT,*(undefined4 *)(iStack_20 + 0x3c),
                 *(undefined4 *)(iStack_20 + 0x140));
      *(undefined4 *)(iStack_20 + 0x2c) = 4;
    }
    break;
  case 4:
    lVar4 = mIsPageMotion__6tailorFv(iStack_20);
    if (lVar4 == 0) {
      if ((*(int *)(iStack_20 + 0x30) == 0) &&
         (iStack_cc = ourBtlSaveDat__10BtlSaveSec + 0xd44, iStack_2c = iStack_cc,
         ((uint)*(ushort *)(ourBtlSaveDat__10BtlSaveSec + 0xda8) &
         1 << (*(uint *)(iStack_20 + *(int *)(iStack_20 + 0x3c) * 4 + 0x114) & 0x1f)) != 0)) {
        setPolyAlpha__7primWinFii(*(undefined4 *)(iStack_20 + 0x6c),1,0x80);
      }
      if ((uStack_10 & 0x2000) == 0) {
        if ((uStack_10 & 0x80) == 0) {
          if (((uStack_10 & 0x20) != 0) &&
             (*(int *)(iStack_20 + 0x3c) < *(int *)(iStack_20 + 0x140) + -1)) {
            play__9primSoundFi(*(undefined4 *)(iStack_20 + 0x150),0x3000004);
            *(int *)(iStack_20 + 0x3c) = *(int *)(iStack_20 + 0x3c) + 1;
            mSetPage__6tailorFi(iStack_20,0);
            iStack_38 = GetRegDat__9RegDatApiFiii(0x35,*(undefined4 *)
                                              (iStack_20 + *(int *)(iStack_20 + 0x3c) * 4 + 0x114),
                                        0xffffffffffffffff);
            ReCreate__10CmdElementFUc
                      (*(undefined4 *)(iStack_20 + 0x88),*(byte *)(iStack_38 + 6) & 7);
            mSetupClothNote__6tailorFv(iStack_20);
          }
        }
        else if (0 < *(int *)(iStack_20 + 0x3c)) {
          play__9primSoundFi(*(undefined4 *)(iStack_20 + 0x150),0x3000004);
          *(int *)(iStack_20 + 0x3c) = *(int *)(iStack_20 + 0x3c) + -1;
          mSetPage__6tailorFi(iStack_20,1);
          iStack_34 = GetRegDat__9RegDatApiFiii(0x35,*(undefined4 *)
                                            (iStack_20 + *(int *)(iStack_20 + 0x3c) * 4 + 0x114),
                                      0xffffffffffffffff);
          ReCreate__10CmdElementFUc(*(undefined4 *)(iStack_20 + 0x88),*(byte *)(iStack_34 + 6) & 7);
          mSetupClothNote__6tailorFv(iStack_20);
        }
      }
      else {
        iStack_d0 = ourBtlSaveDat__10BtlSaveSec + 0xd44;
        iStack_30 = iStack_d0;
        if ((*(int *)(iStack_20 + 0x30) == 0) &&
           (((uint)*(ushort *)(ourBtlSaveDat__10BtlSaveSec + 0xda8) &
            1 << (*(uint *)(iStack_20 + *(int *)(iStack_20 + 0x3c) * 4 + 0x114) & 0x1f)) != 0)) {
          play__9primSoundFi(*(undefined4 *)(iStack_20 + 0x150),4);
        }
        else {
          if (*(int *)(iStack_20 + 0x160) != 0) {
            iStack_d4 = *(int *)(iStack_20 + 0x160);
            if (iStack_d4 != 0) {
              (**(code **)(*(int *)(iStack_d4 + 0x14) + 8))(iStack_d4,1);
            }
            *(undefined4 *)(iStack_20 + 0x160) = 0;
          }
          mSetupMess__6tailorFi(iStack_20,2);
          *(undefined4 *)(iStack_20 + 0x2c) = 8;
          play__9primSoundFi(*(undefined4 *)(iStack_20 + 0x150),2);
        }
      }
    }
    break;
  case 8:
    iStack_58 = *(int *)(iStack_20 + 0x80);
    uStack_23 = *(ushort *)(iStack_58 + 0x76) <= *(ushort *)(iStack_58 + 0x80);
    if ((bool)uStack_23) {
      iStack_5c = *(int *)(iStack_20 + 0x8c);
      *(byte *)(iStack_5c + 0x12) = *(byte *)(iStack_5c + 0x12) & 0xfe | 1;
      *(undefined4 *)(iStack_20 + 0x2c) = 9;
    }
    break;
  case 9:
    if ((uStack_10 & 0x2000) != 0) {
      iStack_60 = *(int *)(iStack_20 + 0x8c);
      *(byte *)(iStack_60 + 0x12) = *(byte *)(iStack_60 + 0x12) & 0xfe;
      play__9primSoundFi(*(undefined4 *)(iStack_20 + 0x150),2);
      *(undefined4 *)(iStack_20 + 0x80) = 0;
      if (*(int *)(iStack_20 + 0x68) != 0) {
        DelayDeleteRequest__7primWinFv(*(undefined4 *)(iStack_20 + 0x68));
        *(undefined4 *)(iStack_20 + 0x68) = 0;
      }
      *(undefined4 *)(iStack_20 + 0x2c) = 10;
    }
    break;
  case 10:
    mSetupYesNoWin__6tailorFi(iStack_20,0);
    *(undefined4 *)(iStack_20 + 0x2c) = 0xb;
    break;
  case 0xb:
    if ((uStack_10 & 0x2000) == 0) {
      if ((uStack_10 & 0x4000) == 0) {
        iStack_3c = *(int *)(iStack_20 + 0x44);
        uVar3 = menuCheckKey__7primWinFiP10primCursor(*(undefined4 *)(iStack_20 + 0x70),uStack_10,
                                *(undefined4 *)(iStack_20 + 0x7c));
        *(undefined4 *)(iStack_20 + 0x44) = uVar3;
        if (*(int *)(iStack_20 + 0x44) != iStack_3c) {
          play__9primSoundFi(*(undefined4 *)(iStack_20 + 0x150),0);
        }
      }
      else {
        mSetupMess__6tailorFi(iStack_20,0);
        *(undefined4 *)(iStack_20 + 0x40) = 0;
        *(undefined4 *)(iStack_20 + 0x2c) = 3;
        play__9primSoundFi(*(undefined4 *)(iStack_20 + 0x150),3);
        mReleaseYesNoWin__6tailorFv(iStack_20);
      }
    }
    else {
      if (*(int *)(iStack_20 + 0x44) == 0) {
        mSetCloth__6tailorFv(iStack_20);
        if (*(int *)(iStack_20 + 0x6c) != 0) {
          DelayDeleteRequest__7primWinFv(*(undefined4 *)(iStack_20 + 0x6c));
          *(undefined4 *)(iStack_20 + 0x6c) = 0;
        }
        mSetupMess__6tailorFi(iStack_20,3);
        *(undefined4 *)(iStack_20 + 0x2c) = 0xc;
        sprintf(auStack_1f0,0x55b7c0,
                        *(int *)(iStack_20 + *(int *)(iStack_20 + 0x3c) * 4 + 0x114) + 1);
        lVar4 = __nw__FUi(0x30);
        uVar3 = 0;
        if (lVar4 != 0) {
          uVar3 = __ct__9primSoundFv(lVar4);
        }
        *(undefined4 *)(iStack_20 + 0x154) = uVar3;
        initialize__9primSoundFv(*(undefined4 *)(iStack_20 + 0x154));
        loadSE__9primSoundFPc(*(undefined4 *)(iStack_20 + 0x154),auStack_1f0);
        mReadModel__6tailorFi
                  (iStack_20,*(undefined4 *)(iStack_20 + *(int *)(iStack_20 + 0x3c) * 4 + 0x114));
      }
      else {
        mSetupMess__6tailorFi(iStack_20,0);
        *(undefined4 *)(iStack_20 + 0x40) = 0;
        *(undefined4 *)(iStack_20 + 0x2c) = 3;
      }
      play__9primSoundFi(*(undefined4 *)(iStack_20 + 0x150),2);
      mReleaseYesNoWin__6tailorFv(iStack_20);
    }
    break;
  case 0xc:
    iStack_64 = *(int *)(iStack_20 + 0x80);
    uStack_24 = *(ushort *)(iStack_64 + 0x76) <= *(ushort *)(iStack_64 + 0x80);
    if (((bool)uStack_24) && (m_TexRead != '\0')) {
      iStack_68 = *(int *)(iStack_20 + 0x8c);
      *(byte *)(iStack_68 + 0x12) = *(byte *)(iStack_68 + 0x12) & 0xfe | 1;
      *(undefined4 *)(iStack_20 + 0x2c) = 0xd;
    }
    break;
  case 0xd:
    if ((uStack_10 & 0x2000) != 0) {
      iStack_6c = *(int *)(iStack_20 + 0x8c);
      *(byte *)(iStack_6c + 0x12) = *(byte *)(iStack_6c + 0x12) & 0xfe;
      play__9primSoundFi(*(undefined4 *)(iStack_20 + 0x150),2);
      *(undefined4 *)(iStack_20 + 0x80) = 0;
      if (*(int *)(iStack_20 + 0x68) != 0) {
        DelayDeleteRequest__7primWinFv(*(undefined4 *)(iStack_20 + 0x68));
        *(undefined4 *)(iStack_20 + 0x68) = 0;
      }
      if (*(int *)(iStack_20 + 0x60) != 0) {
        DelayDeleteRequest__7primWinFv(*(undefined4 *)(iStack_20 + 0x60));
        *(undefined4 *)(iStack_20 + 0x60) = 0;
      }
      if (*(int *)(iStack_20 + 100) != 0) {
        DelayDeleteRequest__7primWinFv(*(undefined4 *)(iStack_20 + 100));
        *(undefined4 *)(iStack_20 + 100) = 0;
      }
      iStack_70 = *(int *)(iStack_20 + 0x88);
      ReleaseOT__7MenuObjFv(iStack_70 + 0x58);
      if (*(int *)(iStack_20 + 0x74) != 0) {
        DelayDeleteRequest__7primWinFv(*(undefined4 *)(iStack_20 + 0x74));
        *(undefined4 *)(iStack_20 + 0x74) = 0;
      }
      mSetupFWin__6tailorFii(iStack_20,1,0);
      setPolyAlpha__7primWinFii(*(undefined4 *)(iStack_20 + 0x74),0,0x40);
      fadein__7primWinFi(*(undefined4 *)(iStack_20 + 0x74),0x20);
      *(undefined4 *)(iStack_20 + 0x2c) = 0xe;
      mFadeFieldBGM__6tailorFi(iStack_20,0);
    }
    break;
  case 0xe:
    lVar4 = isFade__7primWinFv(*(undefined4 *)(iStack_20 + 0x74));
    if (lVar4 == 0) {
      uVar2 = play__9primSoundFi(*(undefined4 *)(iStack_20 + 0x150),0x3000000);
      *(undefined1 *)(iStack_20 + 0x158) = uVar2;
      lVar4 = __nw__FUi(0x5c);
      uVar3 = 0;
      if (lVar4 != 0) {
        uVar3 = __ct__5dRollFv(lVar4);
      }
      *(undefined4 *)(iStack_20 + 0xc4) = uVar3;
      start__5dRollFv(*(undefined4 *)(iStack_20 + 0xc4));
      *(undefined4 *)(iStack_20 + 0x2c) = 0xf;
      *(undefined4 *)(iStack_20 + 0x144) = 0;
    }
    break;
  case 0xf:
    *(int *)(iStack_20 + 0x144) = *(int *)(iStack_20 + 0x144) + 1;
    if (((300 < *(int *)(iStack_20 + 0x144)) &&
        (iStack_74 = *(int *)(iStack_20 + 0x154), *(char *)(iStack_74 + 0x2e) != '\0')) &&
       (m_TexRead != '\0')) {
      stop__9primSoundFc(*(undefined4 *)(iStack_20 + 0x150),*(undefined1 *)(iStack_20 + 0x158));
      play__9primSoundFi(*(undefined4 *)(iStack_20 + 0x150),0x3000001);
      uVar2 = play__9primSoundFi(*(undefined4 *)(iStack_20 + 0x154),0x10000000);
      *(undefined1 *)(iStack_20 + 0x159) = uVar2;
      stop__5dRollFv(*(undefined4 *)(iStack_20 + 0xc4));
      mSetupBaseWin__6tailorFv(iStack_20);
      mSetupMess__6tailorFi(iStack_20,4);
      if (*(int *)(iStack_20 + 0x90) != 0) {
        DelayDeleteRequest__9primModelFv(*(undefined4 *)(iStack_20 + 0x90));
        *(undefined4 *)(iStack_20 + 0x90) = 0;
      }
      iStack_78 = m_pModel;
      piVar1 = *(int **)(m_pModel + 4);
      iStack_40 = *piVar1;
      cStack_21 = '\0';
      piStack_dc = piVar1;
      piStack_d8 = piVar1;
      lVar4 = __nw__FUi(0x58);
      uVar3 = 0;
      if (lVar4 != 0) {
        uVar3 = __ct__9primModelFv(lVar4);
      }
      *(undefined4 *)(iStack_20 + 0x94) = uVar3;
      for (iVar6 = 0; iVar6 < iStack_40; iVar6 = iVar6 + 1) {
        lVar4 = strcmp(piVar1[iVar6 * 2 + 2],0x55b7e0);
        if ((lVar4 == 0) || (cStack_21 != '\0')) {
          lVar4 = strcmp(piVar1[iVar6 * 2 + 2],0x55b7e8);
          if (lVar4 != 0) {
            iStack_80 = m_pModel;
            iStack_ec = *(int *)(m_pModel + 4);
            iStack_e8 = iStack_ec;
            addMotion__9primModelFPUc(*(undefined4 *)(iStack_20 + 0x94),iStack_ec + piVar1[iVar6 * 2 + 3]);
          }
        }
        else {
          cStack_21 = '\x01';
          iStack_7c = m_pModel;
          iStack_e4 = *(int *)(m_pModel + 4);
          iStack_e0 = iStack_e4;
          initialize__9primModelFPUci(*(undefined4 *)(iStack_20 + 0x94),iStack_e4 + piVar1[iVar6 * 2 + 3],7);
        }
      }
      setMotion__9primModelFPCc(*(undefined4 *)(iStack_20 + 0x94),0x55b7f0);
      uVar5 = setAddTime__9primModelFf(0x3cbf258d,*(undefined4 *)(iStack_20 + 0x94));
      setColor__9primModelFfff(0x41f00000,0x41f00000,0x41f00000,*(undefined4 *)(iStack_20 + 0x94),uVar5);
      iStack_84 = *(int *)(iStack_20 + 0x94);
      *(undefined4 *)(iStack_84 + 0x40) = 0x3fd33333;
      setPos__9primModelFfff(0xc0f00000,0xc0666666,0x41700000,*(undefined4 *)(iStack_20 + 0x94));
      (**(code **)(*(int *)(*(int *)(iStack_20 + 0x94) + 0x14) + 0xc))();
      *(undefined4 *)(iStack_20 + 0x2c) = 0x10;
      *(undefined4 *)(iStack_20 + 0x40) = 0;
    }
    break;
  case 0x10:
    *(int *)(iStack_20 + 0x40) = *(int *)(iStack_20 + 0x40) + 1;
    if (*(int *)(iStack_20 + 0x40) == 300) {
      uVar5 = setAddTime__9primModelFf(0x3c888889,*(undefined4 *)(iStack_20 + 0x98));
      play__9primSoundFi(*(undefined4 *)(iStack_20 + 0x150),0x3000002,uVar5);
    }
    iStack_88 = *(int *)(iStack_20 + 0x80);
    uStack_25 = *(ushort *)(iStack_88 + 0x76) <= *(ushort *)(iStack_88 + 0x80);
    if (((bool)uStack_25) && (0x1a3 < *(int *)(iStack_20 + 0x40))) {
      iStack_8c = *(int *)(iStack_20 + 0x8c);
      *(byte *)(iStack_8c + 0x12) = *(byte *)(iStack_8c + 0x12) & 0xfe | 1;
      *(undefined4 *)(iStack_20 + 0x2c) = 0x11;
    }
    break;
  case 0x11:
    if ((uStack_10 & 0x2000) != 0) {
      stop__9primSoundFc(*(undefined4 *)(iStack_20 + 0x154),*(undefined1 *)(iStack_20 + 0x159));
      iStack_90 = *(int *)(iStack_20 + 0x8c);
      *(byte *)(iStack_90 + 0x12) = *(byte *)(iStack_90 + 0x12) & 0xfe;
      *(undefined4 *)(iStack_20 + 0x80) = 0;
      if (*(int *)(iStack_20 + 0x68) != 0) {
        DelayDeleteRequest__7primWinFv(*(undefined4 *)(iStack_20 + 0x68));
        *(undefined4 *)(iStack_20 + 0x68) = 0;
      }
      mSetupMess__6tailorFi(iStack_20,5);
      *(undefined4 *)(iStack_20 + 0x2c) = 0x12;
      fadeout__7primWinFi(*(undefined4 *)(iStack_20 + 0x74),8);
      if (*(int *)(iStack_20 + 0xac) != 0) {
        DelayDeleteRequest__6prim2DFv(*(undefined4 *)(iStack_20 + 0xac));
        *(undefined4 *)(iStack_20 + 0xac) = 0;
      }
      lVar4 = __nw__FUi(0x260);
      uVar3 = 0;
      if (lVar4 != 0) {
        uVar3 = __ct__6prim2DFi(lVar4,6);
      }
      *(undefined4 *)(iStack_20 + 0xac) = uVar3;
      uStack_98 = m_pBuffer;
      iStack_94 = *(int *)(iStack_20 + 0xac);
      *(undefined4 *)(iStack_94 + 0x30) = m_pBuffer;
      setDisp__6prim2DFiffff(0x42400000,0x42980000,0x3f800000,0x3f800000,*(undefined4 *)(iStack_20 + 0xac),
                      4);
      for (iVar6 = 0; iVar6 < 5; iVar6 = iVar6 + 1) {
        if (*(int *)(iStack_20 + iVar6 * 4 + 0xb0) != 0) {
          DelayDeleteRequest__6prim2DFv(*(undefined4 *)(iStack_20 + iVar6 * 4 + 0xb0));
          *(undefined4 *)(iStack_20 + iVar6 * 4 + 0xb0) = 0;
        }
        iStack_44 = 0x30;
        iStack_48 = 0x4c;
        lVar4 = __nw__FUi(0x260);
        uVar3 = 0;
        if (lVar4 != 0) {
          uVar3 = __ct__6prim2DFi(lVar4,6);
        }
        *(undefined4 *)(iStack_20 + iVar6 * 4 + 0xb0) = uVar3;
        uStack_a0 = m_pBuffer;
        iStack_9c = *(int *)(iStack_20 + iVar6 * 4 + 0xb0);
        *(undefined4 *)(iStack_9c + 0x30) = m_pBuffer;
        setDisp__6prim2DFiffff((float)(int)(iStack_44 + (uint)(byte)(&mStarPos)[iVar6 * 2]),
                        (float)(int)(iStack_48 + (uint)(byte)(&DAT_005542e1)[iVar6 * 2]),0x3f800000,
                        0x3f800000,*(undefined4 *)(iStack_20 + iVar6 * 4 + 0xb0),9);
        setUV__6prim2DFiiii(*(undefined4 *)(iStack_20 + iVar6 * 4 + 0xb0),1,iVar6 * 0x28 + 1,0x20,
                        iVar6 * 0x28 + 0x28);
        setSize__6prim2DFii(*(undefined4 *)(iStack_20 + iVar6 * 4 + 0xb0),0x20,0x28);
      }
      uVar5 = mGetMotion__6tailorFi
                        (iStack_20,
                         *(undefined4 *)(iStack_20 + *(int *)(iStack_20 + 0x3c) * 4 + 0x114));
      setMotion__9primModelFPCc(*(undefined4 *)(iStack_20 + 0x94),uVar5);
      setColor__9primModelFfff(0x43000000,0x43000000,0x43000000,*(undefined4 *)(iStack_20 + 0x94));
      play__9primSoundFi(*(undefined4 *)(iStack_20 + 0x150),0x3000003);
      *(undefined4 *)(iStack_20 + 0x40) = 0;
    }
    break;
  case 0x12:
    *(int *)(iStack_20 + 0x40) = *(int *)(iStack_20 + 0x40) + 1;
    if (*(int *)(iStack_20 + 0x40) == 0x5a) {
      uVar2 = play__9primSoundFi(*(undefined4 *)(iStack_20 + 0x154),0x10000001);
      *(undefined1 *)(iStack_20 + 0x159) = uVar2;
    }
    iStack_a4 = *(int *)(iStack_20 + 0x94);
    if (*(char *)(iStack_a4 + 0x54) == '\0') {
      if (*(int *)(iStack_20 + 0x78) == 0) {
        mSetupMagic__6tailorFv(iStack_20);
        mFadeFieldBGM__6tailorFi(iStack_20,1);
      }
      iStack_a8 = *(int *)(iStack_20 + 0x80);
      uStack_26 = *(ushort *)(iStack_a8 + 0x76) <= *(ushort *)(iStack_a8 + 0x80);
      if (((bool)uStack_26) && (0xf0 < *(int *)(iStack_20 + 0x40))) {
        iStack_ac = *(int *)(iStack_20 + 0x8c);
        *(byte *)(iStack_ac + 0x12) = *(byte *)(iStack_ac + 0x12) & 0xfe | 1;
        *(undefined4 *)(iStack_20 + 0x2c) = 0x13;
      }
    }
    break;
  case 0x13:
    if ((uStack_10 & 0x2000) != 0) {
      iStack_b0 = *(int *)(iStack_20 + 0x8c);
      *(byte *)(iStack_b0 + 0x12) = *(byte *)(iStack_b0 + 0x12) & 0xfe;
      play__9primSoundFi(*(undefined4 *)(iStack_20 + 0x150),2);
      if (*(int *)(iStack_20 + 0x78) != 0) {
        DelayDeleteRequest__7primWinFv(*(undefined4 *)(iStack_20 + 0x78));
        *(undefined4 *)(iStack_20 + 0x78) = 0;
      }
      *(undefined4 *)(iStack_20 + 0x80) = 0;
      if (*(int *)(iStack_20 + 0x68) != 0) {
        DelayDeleteRequest__7primWinFv(*(undefined4 *)(iStack_20 + 0x68));
        *(undefined4 *)(iStack_20 + 0x68) = 0;
      }
      mSetupMess__6tailorFi(iStack_20,6);
      *(undefined4 *)(iStack_20 + 0x2c) = 0x14;
    }
    break;
  case 0x14:
    iStack_b4 = *(int *)(iStack_20 + 0x80);
    uStack_27 = *(ushort *)(iStack_b4 + 0x76) <= *(ushort *)(iStack_b4 + 0x80);
    if ((bool)uStack_27) {
      iStack_b8 = *(int *)(iStack_20 + 0x8c);
      *(byte *)(iStack_b8 + 0x12) = *(byte *)(iStack_b8 + 0x12) & 0xfe | 1;
      *(undefined4 *)(iStack_20 + 0x2c) = 0x15;
    }
    break;
  case 0x15:
    if ((uStack_10 & 0x2000) != 0) {
      iStack_bc = *(int *)(iStack_20 + 0x8c);
      *(byte *)(iStack_bc + 0x12) = *(byte *)(iStack_bc + 0x12) & 0xfe;
      play__9primSoundFi(*(undefined4 *)(iStack_20 + 0x150),2);
      *(undefined4 *)(iStack_20 + 0x80) = 0;
      if (*(int *)(iStack_20 + 0x68) != 0) {
        DelayDeleteRequest__7primWinFv(*(undefined4 *)(iStack_20 + 0x68));
        *(undefined4 *)(iStack_20 + 0x68) = 0;
      }
      *(undefined4 *)(iStack_20 + 0x2c) = 0x18;
    }
    break;
  case 0x16:
    iStack_c0 = *(int *)(iStack_20 + 0x80);
    uStack_28 = *(ushort *)(iStack_c0 + 0x76) <= *(ushort *)(iStack_c0 + 0x80);
    if ((bool)uStack_28) {
      mSetupYesNoWin__6tailorFi(iStack_20,1);
      *(undefined4 *)(iStack_20 + 0x2c) = 0x17;
    }
    break;
  case 0x17:
    if ((uStack_10 & 0x2000) == 0) {
      if ((uStack_10 & 0x4000) == 0) {
        iStack_4c = *(int *)(iStack_20 + 0x44);
        uVar3 = menuCheckKey__7primWinFiP10primCursor(*(undefined4 *)(iStack_20 + 0x70),uStack_10,
                                *(undefined4 *)(iStack_20 + 0x7c));
        *(undefined4 *)(iStack_20 + 0x44) = uVar3;
        if (*(int *)(iStack_20 + 0x44) != iStack_4c) {
          play__9primSoundFi(*(undefined4 *)(iStack_20 + 0x150),0);
        }
      }
      else {
        *(undefined4 *)(iStack_20 + 0x40) = 0;
        uVar5 = mSetupMess__6tailorFi(iStack_20,0);
        *(undefined4 *)(iStack_20 + 0x2c) = 3;
        uVar5 = play__9primSoundFi(*(undefined4 *)(iStack_20 + 0x150),3,uVar5);
        mReleaseYesNoWin__6tailorFv(iStack_20,uVar5);
      }
    }
    else {
      if (*(int *)(iStack_20 + 0x44) == 0) {
        if (*(int *)(iStack_20 + 0x160) != 0) {
          iStack_f0 = *(int *)(iStack_20 + 0x160);
          if (iStack_f0 != 0) {
            (**(code **)(*(int *)(iStack_f0 + 0x14) + 8))(iStack_f0,1);
          }
          *(undefined4 *)(iStack_20 + 0x160) = 0;
        }
        *(undefined4 *)(iStack_20 + 0x80) = 0;
        if (*(int *)(iStack_20 + 0x68) != 0) {
          DelayDeleteRequest__7primWinFv(*(undefined4 *)(iStack_20 + 0x68));
          *(undefined4 *)(iStack_20 + 0x68) = 0;
        }
        if (*(int *)(iStack_20 + 0x6c) != 0) {
          DelayDeleteRequest__7primWinFv(*(undefined4 *)(iStack_20 + 0x6c));
          *(undefined4 *)(iStack_20 + 0x6c) = 0;
        }
        iStack_c4 = *(int *)(iStack_20 + 0x88);
        ReleaseOT__7MenuObjFv(iStack_c4 + 0x58);
        *(undefined4 *)(iStack_20 + 0x2c) = 0x18;
      }
      else {
        mSetupMess__6tailorFi(iStack_20,0);
        *(undefined4 *)(iStack_20 + 0x40) = 0;
        *(undefined4 *)(iStack_20 + 0x2c) = 3;
      }
      play__9primSoundFi(*(undefined4 *)(iStack_20 + 0x150),2);
      mReleaseYesNoWin__6tailorFv(iStack_20);
    }
    break;
  case 0x18:
    iStack_c8 = *(int *)(iStack_20 + 0x74);
    if (*(char *)(iStack_c8 + 0x102) == '\0') {
      lVar4 = isFade__7primWinFv(*(undefined4 *)(iStack_20 + 0x74));
      if (lVar4 == 0) {
        *(undefined4 *)(iStack_20 + 0x2c) = 0x19;
      }
    }
    else {
      if (*(int *)(iStack_20 + 0x74) != 0) {
        DelayDeleteRequest__7primWinFv(*(undefined4 *)(iStack_20 + 0x74));
        *(undefined4 *)(iStack_20 + 0x74) = 0;
      }
      mSetupFWin__6tailorFii(iStack_20,10,0);
      fadein__7primWinFi(*(undefined4 *)(iStack_20 + 0x74),0x10);
    }
    break;
  case 0x19:
    *(undefined4 *)(iStack_20 + 0x34) = 2;
    (**(code **)(iStack_20 + 0x24))
              (*(undefined4 *)(iStack_20 + 0x34),*(undefined4 *)(iStack_20 + 0x28));
    *(undefined4 *)(iStack_20 + 0x2c) = 0x1a;
    break;
  case 0x1a:
    mReleaseWin__6tailorFv(iStack_20);
    *(undefined4 *)(iStack_20 + 0x34) = 3;
    uVar5 = (**(code **)(iStack_20 + 0x24))
                      (*(undefined4 *)(iStack_20 + 0x34),*(undefined4 *)(iStack_20 + 0x28));
    (**(code **)(*(int *)(iStack_20 + 0x20) + 0xc))(iStack_20 + 0x18,uVar5);
  }
  mMoveStars__6tailorFv(iStack_20);
  return;
}

/* JP: 0x004ed380  tailor::mMenuPolling(unsigned short)   [mMenuPolling__6tailorFUs]  size=0x1274 */
void mMenuPolling__6tailorFUs(int param_1,ushort param_2)

{
  int *piVar1;
  undefined4 uVar2;
  long lVar3;
  undefined8 uVar4;
  undefined8 extraout_a0;
  int iVar5;
  int iVar6;
  undefined1 uStack_c0;
  undefined1 uStack_bf;
  char cStack_be;
  char cStack_bd;
  undefined4 uStack_bc;
  undefined4 uStack_b8;
  undefined4 uStack_b4;
  int iStack_a8;
  int iStack_a4;
  int iStack_a0;
  int iStack_9c;
  int iStack_98;
  int iStack_94;
  int *piStack_90;
  int *piStack_8c;
  int iStack_88;
  int iStack_84;
  int iStack_80;
  int iStack_7c;
  int iStack_78;
  undefined1 *puStack_74;
  int iStack_70;
  int iStack_6c;
  int iStack_68;
  int iStack_64;
  int iStack_60;
  int iStack_5c;
  int iStack_58;
  int iStack_54;
  int iStack_50;
  int iStack_4c;
  int iStack_48;
  int iStack_44;
  int iStack_40;
  int iStack_3c;
  int iStack_38;
  int iStack_34;
  int iStack_30;
  int iStack_2c;
  int iStack_28;
  undefined1 uStack_24;
  undefined1 uStack_23;
  undefined1 uStack_22;
  char cStack_21;
  int iStack_20;
  ushort uStack_10;
  
  iStack_20 = param_1;
  uStack_10 = param_2;
  iStack_28 = GetActive__4CPadFi(0);
  iVar5 = *(int *)(iStack_28 + 4) * 4;
  iVar6 = *(int *)(&m_pCoreArray__4CPad + iVar5);
  puStack_74 = (undefined1 *)(iVar6 + 0x88);
  uStack_c0 = *puStack_74;
  uStack_bf = *(undefined1 *)(iVar6 + 0x89);
  cStack_be = *(char *)(iVar6 + 0x8a);
  cStack_bd = *(char *)(iVar6 + 0x8b);
  uStack_bc = *(undefined4 *)(iVar6 + 0x8c);
  uStack_b8 = *(undefined4 *)(iVar6 + 0x90);
  uStack_b4 = *(undefined4 *)(iVar6 + 0x94);
  iVar6 = *(int *)(iStack_20 + 0x2c);
  if (iVar6 == 0x1a) {
    mReleaseWin__6tailorFv(iStack_20);
    *(undefined4 *)(iStack_20 + 0x34) = 3;
    (**(code **)(iStack_20 + 0x24))
              (*(undefined4 *)(iStack_20 + 0x34),*(undefined4 *)(iStack_20 + 0x28));
    (**(code **)(*(int *)(iStack_20 + 0x20) + 0xc))();
  }
  else if (iVar6 == 0x18) {
    *(undefined4 *)(iStack_20 + 0x34) = 2;
    (**(code **)(iStack_20 + 0x24))
              (*(undefined4 *)(iStack_20 + 0x34),*(undefined4 *)(iStack_20 + 0x28));
    *(undefined4 *)(iStack_20 + 0x2c) = 0x1a;
  }
  else {
    uVar4 = 5;
    if (iVar6 == 5) {
      if ((uStack_10 & 0x2000) == 0) {
        if ((uStack_10 & 0x5000) != 0) {
          if (*(int *)(iStack_20 + 0x78) != 0) {
            DelayDeleteRequest__7primWinFv(*(undefined4 *)(iStack_20 + 0x78));
            *(undefined4 *)(iStack_20 + 0x78) = 0;
          }
          setPolyAlpha__7primWinFii(*(undefined4 *)(iStack_20 + 0x60),0,0);
          setPolyAlpha__7primWinFii(*(undefined4 *)(iStack_20 + 0x60),1,0x80);
          mSetupMess__6tailorFi(iStack_20,7);
          mSetupClothNote__6tailorFv(iStack_20);
          iStack_70 = *(int *)(iStack_20 + 0x88);
          SetPosition__10MenuWindowFff(0x43c60000,0x42980000,iStack_70 + 0x58);
          *(undefined4 *)(iStack_20 + 0x2c) = 3;
        }
      }
      else {
        Finish__11MenuMessageFv(*(undefined4 *)(iStack_20 + 0x84));
      }
    }
    else if (iVar6 == 7) {
      iStack_60 = *(int *)(iStack_20 + 0x90);
      if ((*(char *)(iStack_60 + 0x54) == '\0') && (*(int *)(iStack_20 + 0x80) == 0)) {
        if (*(int *)(iStack_20 + 0x68) != 0) {
          iVar5 = DelayDeleteRequest__7primWinFv(*(undefined4 *)(iStack_20 + 0x68));
          *(undefined4 *)(iStack_20 + 0x68) = 0;
          uVar4 = extraout_a0;
        }
        iVar6 = rand(uVar4,iVar5);
        mSetupMess__6tailorFi(iStack_20,iVar6 % 6 + 10);
      }
      if ((*(int *)(iStack_20 + 0x80) != 0) &&
         (uStack_24 = *(ushort *)(*(int *)(iStack_20 + 0x80) + 0x76) <=
                      *(ushort *)(*(int *)(iStack_20 + 0x80) + 0x80), (bool)uStack_24)) {
        iStack_64 = *(int *)(iStack_20 + 0x8c);
        *(byte *)(iStack_64 + 0x12) = *(byte *)(iStack_64 + 0x12) & 0xfe | 1;
        if ((uStack_10 & 0x2000) == 0) {
          if ((uStack_10 & 0x4000) != 0) {
            if (*(int *)(iStack_20 + 0x160) != 0) {
              iStack_a4 = *(int *)(iStack_20 + 0x160);
              if (iStack_a4 != 0) {
                (**(code **)(*(int *)(iStack_a4 + 0x14) + 8))(iStack_a4,1);
              }
              *(undefined4 *)(iStack_20 + 0x160) = 0;
            }
            *(undefined4 *)(iStack_20 + 0x80) = 0;
            if (*(int *)(iStack_20 + 0x68) != 0) {
              DelayDeleteRequest__7primWinFv(*(undefined4 *)(iStack_20 + 0x68));
              *(undefined4 *)(iStack_20 + 0x68) = 0;
            }
            if (*(int *)(iStack_20 + 0x6c) != 0) {
              DelayDeleteRequest__7primWinFv(*(undefined4 *)(iStack_20 + 0x6c));
              *(undefined4 *)(iStack_20 + 0x6c) = 0;
            }
            iStack_6c = *(int *)(iStack_20 + 0x88);
            ReleaseOT__7MenuObjFv(iStack_6c + 0x58);
            *(undefined4 *)(iStack_20 + 0x2c) = 0x18;
            play__9primSoundFi(*(undefined4 *)(iStack_20 + 0x150),3);
          }
        }
        else {
          iStack_68 = *(int *)(iStack_20 + 0x8c);
          *(byte *)(iStack_68 + 0x12) = *(byte *)(iStack_68 + 0x12) & 0xfe;
          *(undefined4 *)(iStack_20 + 0x80) = 0;
          if (*(int *)(iStack_20 + 0x68) != 0) {
            DelayDeleteRequest__7primWinFv(*(undefined4 *)(iStack_20 + 0x68));
            *(undefined4 *)(iStack_20 + 0x68) = 0;
          }
          mSetupMess__6tailorFi(iStack_20,7);
          *(undefined4 *)(iStack_20 + 0x2c) = 3;
          *(undefined1 *)(iStack_20 + 0x39) = 0;
        }
      }
    }
    else if (iVar6 == 6) {
      iStack_4c = *(int *)(iStack_20 + 0x98);
      if (((*(char *)(iStack_4c + 0x54) == '\0') && (m_TexRead != 0)) &&
         (uStack_23 = *(ushort *)(*(int *)(iStack_20 + 0x80) + 0x76) <=
                      *(ushort *)(*(int *)(iStack_20 + 0x80) + 0x80), (bool)uStack_23)) {
        if (*(int *)(iStack_20 + 0x90) != 0) {
          DelayDeleteRequest__9primModelFv(*(undefined4 *)(iStack_20 + 0x90));
          *(undefined4 *)(iStack_20 + 0x90) = 0;
        }
        iStack_50 = m_pModel;
        piVar1 = *(int **)(m_pModel + 4);
        iStack_38 = *piVar1;
        cStack_21 = '\0';
        piStack_90 = piVar1;
        piStack_8c = piVar1;
        lVar3 = __nw__FUi(0x58);
        uVar2 = 0;
        if (lVar3 != 0) {
          uVar2 = __ct__9primModelFv(lVar3);
        }
        *(undefined4 *)(iStack_20 + 0x90) = uVar2;
        for (iVar6 = 0; iVar6 < iStack_38; iVar6 = iVar6 + 1) {
          lVar3 = strcmp(piVar1[iVar6 * 2 + 2],0x55b7e0);
          if ((lVar3 == 0) || (cStack_21 != '\0')) {
            lVar3 = strcmp(piVar1[iVar6 * 2 + 2],0x55b7e8);
            if (lVar3 != 0) {
              iStack_58 = m_pModel;
              iStack_a0 = *(int *)(m_pModel + 4);
              iStack_9c = iStack_a0;
              addMotion__9primModelFPUc(*(undefined4 *)(iStack_20 + 0x90),iStack_a0 + piVar1[iVar6 * 2 + 3]);
            }
          }
          else {
            cStack_21 = '\x01';
            iStack_54 = m_pModel;
            iStack_98 = *(int *)(m_pModel + 4);
            iStack_94 = iStack_98;
            initialize__9primModelFPUci(*(undefined4 *)(iStack_20 + 0x90),iStack_98 + piVar1[iVar6 * 2 + 3],7);
          }
        }
        setAddTime__9primModelFf(0x3cbf258d,*(undefined4 *)(iStack_20 + 0x90));
        uVar4 = mGetMotion__6tailorFi
                          (iStack_20,
                           *(undefined4 *)(iStack_20 + *(int *)(iStack_20 + 0x3c) * 4 + 0x114));
        setRotMotion__9primModelFPc(*(undefined4 *)(iStack_20 + 0x90),uVar4);
        iStack_5c = *(int *)(iStack_20 + 0x90);
        *(undefined4 *)(iStack_5c + 0x40) = 0x3fd33333;
        setPos__9primModelFfff(0xc0f00000,0xc0666666,0x41700000,*(undefined4 *)(iStack_20 + 0x90));
        (**(code **)(*(int *)(*(int *)(iStack_20 + 0x90) + 0x14) + 0xc))();
        setMotion__9primModelFPCc(*(undefined4 *)(iStack_20 + 0x98),0x55b878);
        play__9primSoundFi(*(undefined4 *)(iStack_20 + 0x150),0x3000002);
        *(undefined4 *)(iStack_20 + 0x80) = 0;
        *(undefined4 *)(iStack_20 + 0x2c) = 7;
      }
    }
    else if (iVar6 == 4) {
      lVar3 = mIsPageMotion__6tailorFv(iStack_20);
      iVar6 = ourBtlSaveDat__10BtlSaveSec;
      if (lVar3 == 0) {
        if ((uStack_10 & 0x2000) == 0) {
          if ((uStack_10 & 0x1000) == 0) {
            if ((uStack_10 & 0x4000) == 0) {
              if ((uStack_10 & 0x80) == 0) {
                if (((uStack_10 & 0x20) != 0) &&
                   (*(int *)(iStack_20 + 0x3c) < *(int *)(iStack_20 + 0x140) + -1)) {
                  *(int *)(iStack_20 + 0x3c) = *(int *)(iStack_20 + 0x3c) + 1;
                  mSetPage__6tailorFi(iStack_20,0);
                  play__9primSoundFi(*(undefined4 *)(iStack_20 + 0x150),0x3000004);
                  iStack_34 = GetRegDat__9RegDatApiFiii(0x35,*(undefined4 *)
                                                    (iStack_20 + *(int *)(iStack_20 + 0x3c) * 4 +
                                                    0x114),0xffffffffffffffff);
                  uVar4 = ReCreate__10CmdElementFUc
                                    (*(undefined4 *)(iStack_20 + 0x88),*(byte *)(iStack_34 + 6) & 7)
                  ;
                  mSetupClothNote__6tailorFv(iStack_20,uVar4);
                }
              }
              else if (0 < *(int *)(iStack_20 + 0x3c)) {
                *(int *)(iStack_20 + 0x3c) = *(int *)(iStack_20 + 0x3c) + -1;
                mSetPage__6tailorFi(iStack_20,1);
                play__9primSoundFi(*(undefined4 *)(iStack_20 + 0x150),0x3000004);
                iStack_30 = GetRegDat__9RegDatApiFiii(0x35,*(undefined4 *)
                                                  (iStack_20 + *(int *)(iStack_20 + 0x3c) * 4 +
                                                  0x114),0xffffffffffffffff);
                ReCreate__10CmdElementFUc
                          (*(undefined4 *)(iStack_20 + 0x88),*(byte *)(iStack_30 + 6) & 7);
                mSetupClothNote__6tailorFv(iStack_20);
              }
            }
            else {
              if (*(int *)(iStack_20 + 0x160) != 0) {
                iStack_88 = *(int *)(iStack_20 + 0x160);
                if (iStack_88 != 0) {
                  (**(code **)(*(int *)(iStack_88 + 0x14) + 8))(iStack_88,1);
                }
                *(undefined4 *)(iStack_20 + 0x160) = 0;
              }
              *(undefined4 *)(iStack_20 + 0x80) = 0;
              if (*(int *)(iStack_20 + 0x68) != 0) {
                DelayDeleteRequest__7primWinFv(*(undefined4 *)(iStack_20 + 0x68));
                *(undefined4 *)(iStack_20 + 0x68) = 0;
              }
              if (*(int *)(iStack_20 + 0x6c) != 0) {
                DelayDeleteRequest__7primWinFv(*(undefined4 *)(iStack_20 + 0x6c));
                *(undefined4 *)(iStack_20 + 0x6c) = 0;
              }
              iStack_48 = *(int *)(iStack_20 + 0x88);
              ReleaseOT__7MenuObjFv(iStack_48 + 0x58);
              *(undefined4 *)(iStack_20 + 0x2c) = 0x18;
              play__9primSoundFi(*(undefined4 *)(iStack_20 + 0x150),3);
            }
          }
          else {
            if (*(int *)(iStack_20 + 0x160) != 0) {
              iStack_84 = *(int *)(iStack_20 + 0x160);
              if (iStack_84 != 0) {
                (**(code **)(*(int *)(iStack_84 + 0x14) + 8))(iStack_84,1);
              }
              *(undefined4 *)(iStack_20 + 0x160) = 0;
            }
            *(undefined4 *)(iStack_20 + 0x80) = 0;
            if (*(int *)(iStack_20 + 0x68) != 0) {
              DelayDeleteRequest__7primWinFv(*(undefined4 *)(iStack_20 + 0x68));
              *(undefined4 *)(iStack_20 + 0x68) = 0;
            }
            if (*(int *)(iStack_20 + 0x6c) != 0) {
              DelayDeleteRequest__7primWinFv(*(undefined4 *)(iStack_20 + 0x6c));
              *(undefined4 *)(iStack_20 + 0x6c) = 0;
            }
            mSetupMess__6tailorFi(iStack_20,9);
            mSetupNote__6tailorFv(iStack_20);
            setPolyAlpha__7primWinFii(*(undefined4 *)(iStack_20 + 0x60),1,0);
            setPolyAlpha__7primWinFii(*(undefined4 *)(iStack_20 + 0x60),0,0x80);
            *(undefined4 *)(iStack_20 + 0x2c) = 5;
            iStack_44 = *(int *)(iStack_20 + 0x88);
            SetPosition__10MenuWindowFff(0x44750000,0x42980000,iStack_44 + 0x58);
            play__9primSoundFi(*(undefined4 *)(iStack_20 + 0x150),2);
          }
        }
        else {
          iStack_7c = ourBtlSaveDat__10BtlSaveSec + 0xd44;
          if ((uint)*(byte *)(ourBtlSaveDat__10BtlSaveSec + 0xdaa) ==
              *(uint *)(iStack_20 + *(int *)(iStack_20 + 0x3c) * 4 + 0x114)) {
            play__9primSoundFi(*(undefined4 *)(iStack_20 + 0x150),4);
          }
          else {
            if (*(int *)(iStack_20 + 0x160) != 0) {
              iStack_80 = *(int *)(iStack_20 + 0x160);
              if (iStack_80 != 0) {
                (**(code **)(*(int *)(iStack_80 + 0x14) + 8))(iStack_80,1);
              }
              *(undefined4 *)(iStack_20 + 0x160) = 0;
            }
            setMotion__9primModelFPCc(*(undefined4 *)(iStack_20 + 0x98),0x55b870);
            setAddTime__9primModelFf(0x3c888889,*(undefined4 *)(iStack_20 + 0x98));
            *(undefined4 *)(iStack_20 + 0x80) = 0;
            if (*(int *)(iStack_20 + 0x68) != 0) {
              DelayDeleteRequest__7primWinFv(*(undefined4 *)(iStack_20 + 0x68));
              *(undefined4 *)(iStack_20 + 0x68) = 0;
            }
            mSetupMess__6tailorFi(iStack_20,8);
            *(undefined4 *)(iStack_20 + 0x2c) = 6;
            mReadModel__6tailorFi
                      (iStack_20,*(undefined4 *)(iStack_20 + *(int *)(iStack_20 + 0x3c) * 4 + 0x114)
                      );
            *(char *)(iVar6 + 0xdaa) =
                 (char)*(undefined4 *)(iStack_20 + *(int *)(iStack_20 + 0x3c) * 4 + 0x114);
            *(undefined1 *)(iStack_20 + 0x39) = 1;
          }
        }
      }
    }
    else if (iVar6 == 3) {
      uStack_22 = *(ushort *)(*(int *)(iStack_20 + 0x80) + 0x76) <=
                  *(ushort *)(*(int *)(iStack_20 + 0x80) + 0x80);
      if (((bool)uStack_22) &&
         (iStack_40 = *(int *)(iStack_20 + 0x150), *(char *)(iStack_40 + 0x2e) != '\0')) {
        lVar3 = __nw__FUi(0x30);
        uVar2 = 0;
        if (lVar3 != 0) {
          uVar2 = __ct__14bookScrollMarkFv(lVar3);
        }
        *(undefined4 *)(iStack_20 + 0x160) = uVar2;
        initialize__14bookScrollMarkFP7primTexii
                  (*(undefined4 *)(iStack_20 + 0x160),m_pPT,*(undefined4 *)(iStack_20 + 0x3c),
                   *(undefined4 *)(iStack_20 + 0x140));
        *(undefined4 *)(iStack_20 + 0x2c) = 4;
      }
    }
    else if (iVar6 == 2) {
      if (*(int *)(iStack_20 + 100) == 0) {
        *(undefined4 *)(iStack_20 + 0x34) = 0;
        (**(code **)(iStack_20 + 0x24))
                  (*(undefined4 *)(iStack_20 + 0x34),*(undefined4 *)(iStack_20 + 0x28));
        mSetupSelectWin__6tailorFv(iStack_20);
      }
      else {
        lVar3 = isFade__7primWinFv(*(undefined4 *)(iStack_20 + 100));
        if (lVar3 == 0) {
          *(undefined4 *)(iStack_20 + 0x34) = 1;
          (**(code **)(iStack_20 + 0x24))
                    (*(undefined4 *)(iStack_20 + 0x34),*(undefined4 *)(iStack_20 + 0x28));
          *(undefined4 *)(iStack_20 + 0x2c) = 3;
          *(undefined1 *)(iStack_20 + 0x39) = 0;
        }
      }
    }
    else if (iVar6 == 1) {
      if ((*(byte *)(iStack_20 + 0x38) & m_TexRead) != 0) {
        *(undefined4 *)(iStack_20 + 0x2c) = 2;
      }
    }
    else if ((iVar6 == 0) && (m_TexRead != 0)) {
      iStack_78 = ourBtlSaveDat__10BtlSaveSec + 0xd44;
      iStack_2c = iStack_78;
      mReadModel__6tailorFi(iStack_20,*(undefined1 *)(ourBtlSaveDat__10BtlSaveSec + 0xdaa));
      *(undefined4 *)(iStack_20 + 0x2c) = 1;
    }
  }
  if ((*(int *)(iStack_20 + 0x90) != 0) && (*(char *)(iStack_20 + 0x39) == '\0')) {
    if (cStack_be == '\0') {
      if (cStack_bd != '\0') {
        addYRot__9primModelFf(0xbc8efa33,*(undefined4 *)(iStack_20 + 0x90));
      }
    }
    else {
      addYRot__9primModelFf(0x3c8efa33,*(undefined4 *)(iStack_20 + 0x90));
    }
    if ((uStack_10 & 0x8000) != 0) {
      iStack_a8 = ourBtlSaveDat__10BtlSaveSec + 0xd44;
      iStack_3c = iStack_a8;
      uVar4 = mGetMotion__6tailorFi(iStack_20,*(undefined1 *)(ourBtlSaveDat__10BtlSaveSec + 0xdaa));
      setMotion__9primModelFPCc(*(undefined4 *)(iStack_20 + 0x90),uVar4);
    }
  }
  if (((*(int *)(iStack_20 + 0x80) != 0) &&
      (*(int *)(iStack_20 + 0x148) = *(int *)(iStack_20 + 0x148) + 1, (uStack_10 & 0x2000) != 0)) &&
     (5 < *(int *)(iStack_20 + 0x148))) {
    Finish__11MenuMessageFv(*(undefined4 *)(iStack_20 + 0x80));
  }
  mMoveStars__6tailorFv(iStack_20);
  __dt__12CAnalogStickFv(&uStack_c0,0xffffffffffffffff);
  return;
}

/* JP: 0x004ee600  tailor::mSetupSelectWin()   [mSetupSelectWin__6tailorFv]  size=0xa24 */
void mSetupSelectWin__6tailorFv(undefined8 param_1)

{
  bool bVar1;
  int *piVar2;
  undefined1 auVar3 [16];
  undefined4 uVar4;
  int iVar5;
  long lVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  int iVar9;
  int iVar10;
  undefined1 in_vf0 [16];
  undefined1 auVar11 [16];
  undefined1 auVar12 [16];
  undefined1 auVar13 [16];
  undefined1 auStack_60 [16];
  undefined1 auStack_50 [16];
  undefined1 auStack_40 [16];
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  mMakeSketchBook__6tailorFv(param_1);
  mSetupBaseWin__6tailorFv(param_1);
  iVar9 = (int)param_1;
  bVar1 = *(int *)(iVar9 + 0x30) != 1;
  if (bVar1) {
    mSetupMess__6tailorFi(param_1,0);
  }
  else {
    mSetupMess__6tailorFi(param_1,7);
  }
  mSetupClothNote__6tailorFv(param_1);
  lVar6 = __nw__FUi(0x260);
  uVar4 = 0;
  if (lVar6 != 0) {
    uVar4 = __ct__6prim2DFi(lVar6,9);
  }
  *(undefined4 *)(iVar9 + 0xa8) = uVar4;
  *(undefined4 *)(*(int *)(iVar9 + 0xa8) + 0x30) = m_pBuffer;
  setDisp__6prim2DFiffff(0,0,0x3f800000,0x3f800000,*(undefined4 *)(iVar9 + 0xa8),3);
  lVar6 = __nw__FUi(0x260);
  uVar4 = 0;
  if (lVar6 != 0) {
    uVar4 = __ct__6prim2DFi(lVar6,6);
  }
  *(undefined4 *)(iVar9 + 0xac) = uVar4;
  *(undefined4 *)(*(int *)(iVar9 + 0xac) + 0x30) = m_pBuffer;
  setDisp__6prim2DFiffff(0x42400000,0x42980000,0x3f800000,0x3f800000,*(undefined4 *)(iVar9 + 0xac),
                  bVar1 + '\x04');
  for (iVar5 = 0; iVar5 < 5; iVar5 = iVar5 + 1) {
    lVar6 = __nw__FUi(0x260);
    uVar4 = 0;
    if (lVar6 != 0) {
      uVar4 = __ct__6prim2DFi(lVar6,6);
    }
    *(undefined4 *)(iVar9 + iVar5 * 4 + 0xb0) = uVar4;
    *(undefined4 *)(*(int *)(iVar9 + iVar5 * 4 + 0xb0) + 0x30) = m_pBuffer;
    setDisp__6prim2DFiffff((float)((byte)(&mStarPos)[iVar5 * 2] + 0x30),
                    (float)((byte)(&DAT_005542e1)[iVar5 * 2] + 0x4c),0x3f800000,0x3f800000,
                    *(undefined4 *)(iVar9 + iVar5 * 4 + 0xb0),bVar1 + '\t');
    setUV__6prim2DFiiii(*(undefined4 *)(iVar9 + iVar5 * 4 + 0xb0),1,iVar5 * 0x28 + 1,0x20,
                    iVar5 * 0x28 + 0x28);
    setSize__6prim2DFii(*(undefined4 *)(iVar9 + iVar5 * 4 + 0xb0),0x20,0x28);
  }
  lVar6 = __nw__FUi(0x58);
  uVar4 = 0;
  if (lVar6 != 0) {
    uVar4 = __ct__9primModelFv(lVar6);
  }
  *(undefined4 *)(iVar9 + 0x98) = uVar4;
  uVar7 = getData__7primTexFi(m_pPT,0xb);
  initialize__9primModelFPUci(*(undefined4 *)(iVar9 + 0x98),uVar7,8);
  setPos__9primModelFfff(0xc0b66666,0xc0000000,0x40a00000,*(undefined4 *)(iVar9 + 0x98));
  *(undefined4 *)(*(int *)(iVar9 + 0x98) + 0x40) = 0x3f8ccccd;
  uVar7 = getData__7primTexFi(m_pPT,0xd);
  addMotion__9primModelFPUc(*(undefined4 *)(iVar9 + 0x98),uVar7);
  uVar7 = getData__7primTexFi(m_pPT,0xc);
  addMotion__9primModelFPUc(*(undefined4 *)(iVar9 + 0x98),uVar7);
  if (*(int *)(iVar9 + 0x30) == 1) {
    setMotion__9primModelFPCc(*(undefined4 *)(iVar9 + 0x98),0x55b870);
  }
  else {
    setMotion__9primModelFPCc(*(undefined4 *)(iVar9 + 0x98),0x55b878);
  }
  setAddTime__9primModelFf(0,*(undefined4 *)(iVar9 + 0x98));
  (**(code **)(*(int *)(*(int *)(iVar9 + 0x98) + 0x14) + 0xc))();
  lVar6 = __nw__FUi(0x58);
  uVar4 = 0;
  if (lVar6 != 0) {
    uVar4 = __ct__9primModelFv(lVar6);
  }
  *(undefined4 *)(iVar9 + 0x9c) = uVar4;
  uVar7 = getData__7primTexFi(m_pPT,0xe);
  initialize__9primModelFPUci(*(undefined4 *)(iVar9 + 0x9c),uVar7,10);
  setRot__9primModelFfff(0x3fa66666,0x3f000000,0x3f333333,*(undefined4 *)(iVar9 + 0x9c));
  setPos__9primModelFfff(0x4164cccd,0xc0000000,0x3dcccccd,*(undefined4 *)(iVar9 + 0x9c));
  lVar6 = __nw__FUi(0x58);
  uVar4 = 0;
  if (lVar6 != 0) {
    uVar4 = __ct__9primModelFv(lVar6);
  }
  *(undefined4 *)(iVar9 + 0xa0) = uVar4;
  uVar7 = getData__7primTexFi(m_pPT,*(int *)(iVar9 + *(int *)(iVar9 + 0x3c) * 4 + 0x114) + 0xf);
  initialize__9primModelFPUci(*(undefined4 *)(iVar9 + 0xa0),uVar7,0xb);
  setRot__9primModelFfff(0x3fa66666,0x3f000000,0x3f333333,*(undefined4 *)(iVar9 + 0xa0));
  setPos__9primModelFfff(0x4164cccd,0xc0000000,0,*(undefined4 *)(iVar9 + 0xa0));
  uVar7 = getData__7primTexFi(m_pPT,0x1b);
  addMotion__9primModelFPUc(*(undefined4 *)(iVar9 + 0xa0),uVar7);
  uVar7 = getData__7primTexFi(m_pPT,0x1a);
  addMotion__9primModelFPUc(*(undefined4 *)(iVar9 + 0xa0),uVar7);
  (**(code **)(*(int *)(*(int *)(iVar9 + 0xa0) + 0x14) + 0xc))();
  if (*(int *)(iVar9 + 0x30) == 1) {
    piVar2 = *(int **)(m_pModel + 4);
    iVar5 = *piVar2;
    bVar1 = false;
    lVar6 = __nw__FUi(0x58);
    uVar4 = 0;
    if (lVar6 != 0) {
      uVar4 = __ct__9primModelFv(lVar6);
    }
    *(undefined4 *)(iVar9 + 0x90) = uVar4;
    for (iVar10 = 0; iVar10 < iVar5; iVar10 = iVar10 + 1) {
      lVar6 = strcmp(piVar2[iVar10 * 2 + 2],0x55b7e0);
      if ((lVar6 == 0) || (bVar1)) {
        lVar6 = strcmp(piVar2[iVar10 * 2 + 2],0x55b7e8);
        if (lVar6 != 0) {
          addMotion__9primModelFPUc(*(undefined4 *)(iVar9 + 0x90),
                          *(int *)(m_pModel + 4) + piVar2[iVar10 * 2 + 3]);
        }
      }
      else {
        bVar1 = true;
        initialize__9primModelFPUci(*(undefined4 *)(iVar9 + 0x90),
                        *(int *)(m_pModel + 4) + piVar2[iVar10 * 2 + 3],7);
      }
    }
    setMotion__9primModelFPCc(*(undefined4 *)(iVar9 + 0x90),0x55b7f0);
    setAddTime__9primModelFf(0x3cbf258d,*(undefined4 *)(iVar9 + 0x90));
    *(undefined4 *)(*(int *)(iVar9 + 0x90) + 0x40) = 0x3fd33333;
    setPos__9primModelFfff(0xc0f00000,0xc0666666,0x41700000,*(undefined4 *)(iVar9 + 0x90));
    (**(code **)(*(int *)(*(int *)(iVar9 + 0x90) + 0x14) + 0xc))();
  }
  uStack_10 = 0x3e4ccccd;
  uStack_c = 0x3e4ccccd;
  uStack_8 = 0x3e4ccccd;
  uStack_4 = 0x3f800000;
  uStack_20 = 0xbe4511a4;
  uStack_1c = 0xbe4511a4;
  uStack_18 = 0x3f76560c;
  uStack_14 = 0x3f800000;
  uStack_30 = 0x3f666666;
  uStack_2c = 0x3f666666;
  uStack_28 = 0x3f666666;
  uStack_24 = 0x3f800000;
  uVar7 = __ct__7FVectorFRC7FVector(auStack_40,&uStack_10);
  uVar4 = CreateAmbient__12LightControlF7FVector(uVar7);
  *(undefined4 *)(iVar9 + 200) = uVar4;
  uVar7 = __ct__7FVectorFRC7FVector(auStack_50,&uStack_20);
  uVar8 = __ct__7FVectorFRC7FVector(auStack_60,&uStack_30);
  uVar4 = CreateDirectional__12LightControlF7FVector7FVector(uVar7,uVar8);
  *(undefined4 *)(iVar9 + 0xcc) = uVar4;
  *(undefined4 *)(camera__4CApp + 0x380) = 0x3f800000;
  *(undefined4 *)(camera__4CApp + 900) = 0x447a0000;
  *(undefined4 *)(camera__4CApp + 0x360) = 0;
  *(undefined4 *)(camera__4CApp + 0x364) = *(undefined4 *)(camera__4CApp + 0x380);
  *(float *)(camera__4CApp + 0x368) =
       256.0 / (*(float *)(camera__4CApp + 900) - *(float *)(camera__4CApp + 0x380));
  *(undefined4 *)(camera__4CApp + 0x36c) = 0x437f0000;
  SetViewMatrix__9GsxCameraFfffff(0x44000000,0x3f4ccccd,0x3f6eeeef,0x3f800000,0x4b7fff28,camera__4CApp);
  auVar11 = _vmr32(in_vf0);
  auVar12 = _vmr32(auVar11);
  auVar13 = _vmr32(auVar12);
  auVar3 = _sqc2(in_vf0);
  *(undefined1 (*) [16])(camera__4CApp + 0x270) = auVar3;
  auVar3 = _sqc2(auVar11);
  *(undefined1 (*) [16])(camera__4CApp + 0x260) = auVar3;
  auVar3 = _sqc2(auVar12);
  *(undefined1 (*) [16])(camera__4CApp + 0x250) = auVar3;
  auVar3 = _sqc2(auVar13);
  *(undefined1 (*) [16])(camera__4CApp + 0x240) = auVar3;
  *(undefined4 *)(camera__4CApp + 0x270) = 0;
  *(undefined4 *)(camera__4CApp + 0x274) = 0xc1200000;
  *(undefined4 *)(camera__4CApp + 0x278) = 0xc1f00000;
  *(undefined4 *)(camera__4CApp + 0x27c) = 0x3f800000;
  ApplyFrame__9GsxCameraFv(camera__4CApp);
  iVar5 = GetRegDat__9RegDatApiFiii(0x35,*(undefined4 *)(iVar9 + *(int *)(iVar9 + 0x3c) * 4 + 0x114),
                          0xffffffffffffffff);
  Create__10CmdElementFUc(*(undefined4 *)(iVar9 + 0x88),*(byte *)(iVar5 + 6) & 7);
  Open__10CmdElementFv(*(undefined4 *)(iVar9 + 0x88));
  SetPosition__10MenuWindowFff(0x43c60000,0x42980000,*(int *)(iVar9 + 0x88) + 0x58);
  return;
}

/* JP: 0x004ef030  tailor::mReleaseWin()   [mReleaseWin__6tailorFv]  size=0x23c */
void mReleaseWin__6tailorFv(int param_1)

{
  int iVar1;
  
  if (*(int *)(param_1 + 0x74) != 0) {
    DelayDeleteRequest__7primWinFv(*(undefined4 *)(param_1 + 0x74));
    *(undefined4 *)(param_1 + 0x74) = 0;
  }
  if (*(int *)(param_1 + 0xa0) != 0) {
    DelayDeleteRequest__9primModelFv(*(undefined4 *)(param_1 + 0xa0));
    *(undefined4 *)(param_1 + 0xa0) = 0;
  }
  if (*(int *)(param_1 + 0x9c) != 0) {
    DelayDeleteRequest__9primModelFv(*(undefined4 *)(param_1 + 0x9c));
    *(undefined4 *)(param_1 + 0x9c) = 0;
  }
  if (*(int *)(param_1 + 0x98) != 0) {
    DelayDeleteRequest__9primModelFv(*(undefined4 *)(param_1 + 0x98));
    *(undefined4 *)(param_1 + 0x98) = 0;
  }
  if (*(int *)(param_1 + 0xa8) != 0) {
    DelayDeleteRequest__6prim2DFv(*(undefined4 *)(param_1 + 0xa8));
    *(undefined4 *)(param_1 + 0xa8) = 0;
  }
  if (*(int *)(param_1 + 0xac) != 0) {
    DelayDeleteRequest__6prim2DFv(*(undefined4 *)(param_1 + 0xac));
    *(undefined4 *)(param_1 + 0xac) = 0;
  }
  if (*(int *)(param_1 + 0x90) != 0) {
    DelayDeleteRequest__9primModelFv(*(undefined4 *)(param_1 + 0x90));
    *(undefined4 *)(param_1 + 0x90) = 0;
  }
  if (*(int *)(param_1 + 0x94) != 0) {
    DelayDeleteRequest__9primModelFv(*(undefined4 *)(param_1 + 0x94));
    *(undefined4 *)(param_1 + 0x94) = 0;
  }
  for (iVar1 = 0; iVar1 < 5; iVar1 = iVar1 + 1) {
    if (*(int *)(param_1 + iVar1 * 4 + 0xb0) != 0) {
      DelayDeleteRequest__6prim2DFv(*(undefined4 *)(param_1 + iVar1 * 4 + 0xb0));
      *(undefined4 *)(param_1 + iVar1 * 4 + 0xb0) = 0;
    }
  }
  release__12LightControlFi(*(undefined4 *)(param_1 + 200));
  release__12LightControlFi(*(undefined4 *)(param_1 + 0xcc));
  if (*(int *)(param_1 + 0x60) != 0) {
    DelayDeleteRequest__7primWinFv(*(undefined4 *)(param_1 + 0x60));
    *(undefined4 *)(param_1 + 0x60) = 0;
  }
  if (*(int *)(param_1 + 100) != 0) {
    DelayDeleteRequest__7primWinFv(*(undefined4 *)(param_1 + 100));
    *(undefined4 *)(param_1 + 100) = 0;
  }
  return;
}

/* JP: 0x004ef270  tailor::mSetupBaseWin()   [mSetupBaseWin__6tailorFv]  size=0x230 */
void mSetupBaseWin__6tailorFv(int param_1)

{
  undefined4 uVar1;
  long lVar2;
  
  lVar2 = __nw__FUi(0x148);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = __ct__7primWinFv(lVar2);
  }
  *(undefined4 *)(param_1 + 0x60) = uVar1;
  uVar1 = *(undefined4 *)(param_1 + 0x60);
  initialize__7primWinFP7primTex(uVar1,m_pPT);
  setItem__7primWinFiii(uVar1,2,2,0);
  setTex__7primWinFiiii(uVar1,1,0,0,0);
  setTex__7primWinFiiii(uVar1,2,1,0,0);
  createTexPoly__7primWinFiiiiii(uVar1,0,0,0,0,0,0);
  createTexPoly__7primWinFiiiiii(uVar1,1,1,0,0,0,0);
  if (*(int *)(param_1 + 0x30) == 1) {
    setPolyAlpha__7primWinFii(uVar1,0,0);
  }
  else {
    setPolyAlpha__7primWinFii(uVar1,1,0);
  }
  buildWin__7primWinFiiiiii(uVar1,2,8,0x128,0x40,0x40,2);
  lVar2 = __nw__FUi(0x148);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = __ct__7primWinFv(lVar2);
  }
  *(undefined4 *)(param_1 + 100) = uVar1;
  uVar1 = *(undefined4 *)(param_1 + 100);
  initialize__7primWinFP7primTex(uVar1,m_pPT);
  buildWin__7primWinFiiiiii(uVar1,2,0x80,0x152,0x15c,0x40,1);
  uVar1 = addKeyWait__7primWinFv(uVar1);
  *(undefined4 *)(param_1 + 0x8c) = uVar1;
  *(byte *)(*(int *)(param_1 + 0x8c) + 0x12) = *(byte *)(*(int *)(param_1 + 0x8c) + 0x12) & 0xfe;
  return;
}

/* JP: 0x004ef4a0  tailor::mSetupFWin(int, int)   [mSetupFWin__6tailorFii]  size=0x120 */
void mSetupFWin__6tailorFii(int param_1,undefined4 param_2,int param_3)

{
  undefined4 uVar1;
  long lVar2;
  
  lVar2 = __nw__FUi(0x148);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = __ct__7primWinFv(lVar2);
  }
  *(undefined4 *)(param_1 + 0x74) = uVar1;
  uVar1 = *(undefined4 *)(param_1 + 0x74);
  initialize__7primWinFP7primTex(uVar1,m_pPT);
  setItem__7primWinFiii(uVar1,1,1,0);
  createPoly__7primWinFiiiiii(uVar1,0,0,0,0,0x200,0x1c0);
  setPolyRGBA__7primWinFiiiii(uVar1,0,0,0,0,0x80);
  buildWin__7primWinFiiiiii(uVar1,param_2,0,0,0,0,0);
  if (param_3 != 0) {
    fadeout__7primWinFi(uVar1,0x40);
  }
  return;
}

/* JP: 0x004ef5c0  tailor::mSetupClothNote()   [mSetupClothNote__6tailorFv]  size=0x51c */
void mSetupClothNote__6tailorFv(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  long lVar3;
  undefined8 uVar4;
  float fVar5;
  
  if (*(int *)(param_1 + 0x6c) != 0) {
    DelayDeleteRequest__7primWinFv(*(undefined4 *)(param_1 + 0x6c));
    *(undefined4 *)(param_1 + 0x6c) = 0;
  }
  lVar3 = __nw__FUi(0x148);
  uVar1 = 0;
  if (lVar3 != 0) {
    uVar1 = __ct__7primWinFv(lVar3);
  }
  *(undefined4 *)(param_1 + 0x6c) = uVar1;
  uVar1 = *(undefined4 *)(param_1 + 0x6c);
  initialize__7primWinFP7primTex(uVar1,m_pPT);
  setItem__7primWinFiii(uVar1,3,2,6);
  setTex__7primWinFiiii(uVar1,0,1,0,0);
  createTexPoly__7primWinFiiiiii(uVar1,0,1,0x186,0x28,0,0);
  iVar2 = getPP__7primWinFi(uVar1,0);
  (**(code **)(*(int *)(iVar2 + 8) + 0x28))(0x42f40000,0x40800000);
  uVar4 = getPP__7primWinFi(uVar1,0);
  SetUV__11MenuPolygonFUsUsUsUs(uVar4,1,1,0x47,8);
  setTex__7primWinFiiii(uVar1,8,2,0,0);
  createTexPoly__7primWinFiiiiii(uVar1,1,2,0x16e,0xbc,0,0);
  setPolyAlpha__7primWinFii(uVar1,1,0);
  setTextArea__7primWinFiiib(uVar1,0,0x280,0xe4,1);
  uVar4 = GetRegDat__9RegDatApiFiii(0xb,*(undefined4 *)(param_1 + *(int *)(param_1 + 0x3c) * 4 + 0x114),
                          0xffffffffffffffff);
  createText__7primWinFiiiiPciib(uVar1,0,0,0,0,uVar4,0,1);
  iVar2 = getPT__7primWinFi(uVar1,0);
  fVar5 = *(float *)(iVar2 + 0x2c);
  iVar2 = getPT__7primWinFi(uVar1,0);
  (**(code **)(*(int *)(iVar2 + 8) + 0x24))((float)(int)(449.0 - fVar5 / 2.0),0x41800000);
  if (*(int *)(param_1 + 0x30) == 0) {
    if (((uint)*(ushort *)(ourBtlSaveDat__10BtlSaveSec + 0xda8) &
        1 << (*(uint *)(param_1 + *(int *)(param_1 + 0x3c) * 4 + 0x114) & 0x1f)) == 0) {
      uVar4 = GetRegDat__9RegDatApiFiii(0xc,2,*(int *)(param_1 + *(int *)(param_1 + 0x3c) * 4 + 0x114) + -1);
      createText__7primWinFiiiiPciib(uVar1,2,0,0,0,uVar4,0,0);
    }
    iVar2 = getPT__7primWinFi(uVar1,2);
    fVar5 = *(float *)(iVar2 + 0x2c);
    iVar2 = getPT__7primWinFi(uVar1,2);
    (**(code **)(*(int *)(iVar2 + 8) + 0x24))((float)(int)(449.0 - fVar5 / 2.0),0x42380000);
    createText__7primWinFiiiiPciib(uVar1,1,0,8,0x1a2,
                    (&tailorMess_clothNote_J)
                    [*(int *)(param_1 + *(int *)(param_1 + 0x3c) * 4 + 0x114)],0,1);
  }
  else {
    uVar4 = GetRegDat__9RegDatApiFiii(0x1c,*(undefined4 *)(param_1 + *(int *)(param_1 + 0x3c) * 4 + 0x114),
                            0xffffffffffffffff);
    createText__7primWinFiiiiPciib(uVar1,1,0,8,0x1a2,uVar4,0,1);
  }
  buildWin__7primWinFiiiiii(uVar1,3,0,0,0,0,0);
  fadein__7primWinFi(uVar1,0x10);
  if (*(int *)(param_1 + 0x160) != 0) {
    select__14bookScrollMarkFi(*(undefined4 *)(param_1 + 0x160),*(undefined4 *)(param_1 + 0x3c));
  }
  return;
}

/* JP: 0x004efae0  tailor::mSetupMess(int)   [mSetupMess__6tailorFi]  size=0x1dc */
void mSetupMess__6tailorFi(int param_1,int param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  long lVar3;
  undefined8 uVar4;
  undefined1 auStack_120 [256];
  int iStack_20;
  int iStack_10;
  
  *(undefined4 *)(param_1 + 0x80) = 0;
  iStack_20 = param_1;
  iStack_10 = param_2;
  if (*(int *)(param_1 + 0x68) != 0) {
    DelayDeleteRequest__7primWinFv(*(undefined4 *)(param_1 + 0x68));
    *(undefined4 *)(iStack_20 + 0x68) = 0;
  }
  lVar3 = __nw__FUi(0x148);
  uVar1 = 0;
  if (lVar3 != 0) {
    uVar1 = __ct__7primWinFv(lVar3);
  }
  *(undefined4 *)(iStack_20 + 0x68) = uVar1;
  uVar1 = *(undefined4 *)(iStack_20 + 0x68);
  initialize__7primWinFP7primTex(uVar1,m_pPT);
  setItem__7primWinFiii(uVar1,1,0,1);
  setTextArea__7primWinFiiib(uVar1,0,0x200,0x100,1);
  if (iStack_10 == 5) {
    uVar4 = GetRegDat__9RegDatApiFiii(0xb,*(undefined4 *)(iStack_20 + *(int *)(iStack_20 + 0x3c) * 4 + 0x114),
                            0xffffffffffffffff);
    sprintf(auStack_120,(&tailorMess_mess_J)[iStack_10],uVar4);
    uVar2 = addMessage__7primWinFiiPcib(uVar1,0,0,auStack_120,1,0);
    *(undefined4 *)(iStack_20 + 0x80) = uVar2;
  }
  else {
    uVar2 = addMessage__7primWinFiiPcib(uVar1,0,0,(&tailorMess_mess_J)[iStack_10],1,0);
    *(undefined4 *)(iStack_20 + 0x80) = uVar2;
  }
  buildWin__7primWinFiiiiii(uVar1,3,0x80,0x152,0,0,0);
  *(undefined4 *)(iStack_20 + 0x148) = 0;
  return;
}

/* JP: 0x004efcc0  tailor::mSetupYesNoWin(int)   [mSetupYesNoWin__6tailorFi]  size=0x200 */
void mSetupYesNoWin__6tailorFi(int param_1,int param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  long lVar3;
  
  *(undefined4 *)(param_1 + 0x44) = 1;
  lVar3 = __nw__FUi(0x148);
  uVar1 = 0;
  if (lVar3 != 0) {
    uVar1 = __ct__7primWinFv(lVar3);
  }
  *(undefined4 *)(param_1 + 0x70) = uVar1;
  uVar1 = *(undefined4 *)(param_1 + 0x70);
  initialize__7primWinFP7primTex(uVar1,m_pPT);
  setItem__7primWinFiii(uVar1,1,0,2);
  setTextArea__7primWinFiiib(uVar1,0,0x80,0x40,1);
  createText__7primWinFiiiiPciib(uVar1,0,0,0x20,param_2 * 0x18 + 2,tailorMess_yesNo_J,0,1);
  createText__7primWinFiiiiPciib(uVar1,1,0,0x20,param_2 * 0x18 + 0x18,tailorMess_yesNo_J+0x4,0,1);
  setMenuWindow__7primWinFiiiii(uVar1,2,*(undefined4 *)(param_1 + 0x44),0,0xffffffffffffffff,0xffffff);
  buildWin__7primWinFiiiiii(uVar1,3,0x80,0x152,0,0,0);
  lVar3 = __nw__FUi(0x10c);
  uVar2 = 0;
  if (lVar3 != 0) {
    uVar2 = __ct__10primCursorFv(lVar3);
  }
  *(undefined4 *)(param_1 + 0x7c) = uVar2;
  createCursor__10primCursorFiiii(*(undefined4 *)(param_1 + 0x7c),0,2,8,10);
  setItem__10primCursorFP7primWini(*(undefined4 *)(param_1 + 0x7c),uVar1,*(undefined4 *)(param_1 + 0x44));
  qMove__10primCursorFv(*(undefined4 *)(param_1 + 0x7c));
  return;
}

/* JP: 0x004efec0  tailor::mReleaseYesNoWin()   [mReleaseYesNoWin__6tailorFv]  size=0x70 */
void mReleaseYesNoWin__6tailorFv(int param_1)

{
  if (*(int *)(param_1 + 0x70) != 0) {
    DelayDeleteRequest__7primWinFv(*(undefined4 *)(param_1 + 0x70));
    *(undefined4 *)(param_1 + 0x70) = 0;
  }
  if (*(int *)(param_1 + 0x7c) != 0) {
    DelayDeleteRequest__10primCursorFv(*(undefined4 *)(param_1 + 0x7c));
    *(undefined4 *)(param_1 + 0x7c) = 0;
  }
  return;
}

/* JP: 0x004eff30  tailor::mSetCloth()   [mSetCloth__6tailorFv]  size=0x1fc */
void mSetCloth__6tailorFv(int param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  
  *(char *)(ourBtlSaveDat__10BtlSaveSec + 0xdaa) =
       (char)*(undefined4 *)(param_1 + *(int *)(param_1 + 0x3c) * 4 + 0x114);
  if (*(int *)(param_1 + 0x30) == 0) {
    *(ushort *)(ourBtlSaveDat__10BtlSaveSec + 0xda8) =
         *(ushort *)(ourBtlSaveDat__10BtlSaveSec + 0xda8) |
         (short)(1 << (*(uint *)(param_1 + *(int *)(param_1 + 0x3c) * 4 + 0x114) & 0x1f)) + 1U;
    *(uint *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x2fc) =
         (*(uint *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x2fc) |
         1 << ((int)(short)((short)*(undefined4 *)(param_1 + *(int *)(param_1 + 0x3c) * 4 + 0x114) +
                           -1) & 0x1fU)) & 0x1ff;
  }
  iVar4 = ourBtlSaveDat__10BtlSaveSec + (uint)*(byte *)(ourBtlSaveDat__10BtlSaveSec + 2) * 0x200 + 0x944;
  for (uVar3 = 0x8a; (int)uVar3 < 0x93; uVar3 = uVar3 + 1) {
    uVar1 = uVar3;
    if ((int)uVar3 < 0) {
      uVar1 = uVar3 + 7;
    }
    iVar2 = (int)uVar1 >> 3;
    uVar1 = uVar3 & 7;
    if (((int)uVar3 < 0) && (uVar1 != 0)) {
      uVar1 = uVar1 - 8;
    }
    if ((((uint)*(byte *)(iVar4 + iVar2 + 0x40) & 1 << (uVar1 & 0x1f)) != 0) &&
       (((uint)*(byte *)(iVar4 + iVar2 + 0x60) & 1 << (uVar1 & 0x1f)) == 0)) {
      *(byte *)(iVar4 + iVar2 + 0x60) =
           *(byte *)(iVar4 + iVar2 + 0x60) | (byte)(1 << (uVar1 & 0x1f));
    }
  }
  return;
}

/* JP: 0x004f0130  tailor::mSetupMagic()   [mSetupMagic__6tailorFv]  size=0x1cc */
void mSetupMagic__6tailorFv(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  long lVar3;
  undefined8 uVar4;
  float fVar5;
  undefined1 auStack_120 [256];
  float fStack_20;
  float fStack_1c;
  float fStack_18;
  float fStack_14;
  int iStack_10;
  
  iStack_10 = param_1;
  lVar3 = __nw__FUi(0x148);
  uVar1 = 0;
  if (lVar3 != 0) {
    uVar1 = __ct__7primWinFv(lVar3);
  }
  *(undefined4 *)(iStack_10 + 0x78) = uVar1;
  uVar1 = *(undefined4 *)(iStack_10 + 0x78);
  initialize__7primWinFP7primTex(uVar1,m_pPT);
  setItem__7primWinFiii(uVar1,1,0,1);
  setTextArea__7primWinFiiib(uVar1,0,0x200,0x40,1);
  uVar4 = GetRegDat__9RegDatApiFiii(0xc,2,*(int *)(iStack_10 + *(int *)(iStack_10 + 0x3c) * 4 + 0x114) + -1);
  sprintf(auStack_120,tailorMess_magic_J,uVar4);
  createText__7primWinFiiiiPciib(uVar1,0,0,0,0,auStack_120,0,1);
  iVar2 = getPT__7primWinFi(uVar1,0);
  fStack_18 = *(float *)(iVar2 + 0x2c);
  fVar5 = fStack_18 / 2.0;
  fStack_14 = fStack_18;
  iVar2 = getPT__7primWinFi(uVar1,0);
  fStack_20 = *(float *)(iVar2 + 0x2c);
  fStack_1c = fStack_20;
  buildWin__7primWinFiiiiii(uVar1,3,(int)(192.0 - fVar5),0x50,(int)fStack_20,0x14,3);
  return;
}

/* JP: 0x004f0300  tailor::mSetupNote()   [mSetupNote__6tailorFv]  size=0x3ec */
void mSetupNote__6tailorFv(int param_1)

{
  byte bVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  long lVar5;
  undefined8 uVar6;
  int iVar7;
  
  bVar1 = *(byte *)(ourBtlSaveDat__10BtlSaveSec + 0xdaa);
  lVar5 = __nw__FUi(0x148);
  uVar2 = 0;
  if (lVar5 != 0) {
    uVar2 = __ct__7primWinFv(lVar5);
  }
  *(undefined4 *)(param_1 + 0x78) = uVar2;
  uVar2 = *(undefined4 *)(param_1 + 0x78);
  initialize__7primWinFP7primTex(uVar2,m_pPT);
  setItem__7primWinFiii(uVar2,3,3,2);
  setTextArea__7primWinFiiib(uVar2,2,0x100,0x180,1);
  uVar6 = GetRegDat__9RegDatApiFiii(0xb,bVar1,0xffffffffffffffff);
  createText__7primWinFiiiiPciib(uVar2,0,2,0,0,uVar6,0x10,1);
  createText__7primWinFiiiiPciib(uVar2,1,2,0,0x14,(&tailorMess_clothRuby_J)[bVar1],0,3);
  iVar3 = getPT__7primWinFi(uVar2,0);
  iVar7 = (int)(96.0 - *(float *)(iVar3 + 0x2c) / 2.0);
  iVar3 = getPT__7primWinFi(uVar2,0);
  (**(code **)(*(int *)(iVar3 + 8) + 0x24))((float)iVar7,0x41000000);
  iVar3 = getPT__7primWinFi(uVar2,1);
  (**(code **)(*(int *)(iVar3 + 8) + 0x24))((float)iVar7,0x42000000);
  uVar4 = addMessage__7primWinFiiPcib(uVar2,0xfffffffffffffffc,0x3c,(&tailorMess_clothMess_J)[bVar1],0,0);
  *(undefined4 *)(param_1 + 0x84) = uVar4;
  setMenuTex__7primWinFP11MenuTextureiii(uVar2,0x421698,1,0x10,0x14);
  setTex__7primWinFiiii(uVar2,0,0,0,0);
  createTexPoly__7primWinFiiiiii(uVar2,0,1,iVar7 + -0x10,8,2,2);
  createTexPoly__7primWinFiiiiii(uVar2,1,0,0,0x34,0,0);
  iVar3 = getPP__7primWinFi(uVar2,1);
  (**(code **)(*(int *)(iVar3 + 8) + 0x28))(0x42c00000,0x40000000);
  uVar6 = getPP__7primWinFi(uVar2,1);
  SetUV__11MenuPolygonFUsUsUsUs(uVar6,1,1,0x47,8);
  createTexPoly__7primWinFiiiiii(uVar2,2,0,0x60,0x34,0,0);
  iVar3 = getPP__7primWinFi(uVar2,2);
  (**(code **)(*(int *)(iVar3 + 8) + 0x28))(0x42c00000,0x40000000);
  uVar6 = getPP__7primWinFi(uVar2,2);
  SetUV__11MenuPolygonFUsUsUsUs(uVar6,0x46,1,0,8);
  buildWin__7primWinFiiiiii(uVar2,0xd,0x120,0x20,0xc0,0xe0,6);
  return;
}

/* JP: 0x004f06f0  tailor::mMakeSketchBook()   [mMakeSketchBook__6tailorFv]  size=0x16c */
void mMakeSketchBook__6tailorFv(int param_1)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  
  *(undefined4 *)(param_1 + 0x3c) = 0;
  *(undefined4 *)(param_1 + 0x140) = 0;
  if (*(int *)(param_1 + 0x30) == 0) {
    puVar1 = (uint *)GetTailorFlagAddr__Fv();
    uVar2 = *puVar1;
    if (uVar2 == 0) {
      uVar2 = 0x3fe;
    }
    for (uVar3 = 0; (int)uVar3 < 0xb; uVar3 = uVar3 + 1) {
      if ((uVar2 & 1 << (uVar3 & 0x1f)) != 0) {
        *(uint *)(param_1 + *(int *)(param_1 + 0x140) * 4 + 0x114) = uVar3;
        *(int *)(param_1 + 0x140) = *(int *)(param_1 + 0x140) + 1;
      }
    }
  }
  else {
    for (uVar2 = 0; (int)uVar2 < 0xb; uVar2 = uVar2 + 1) {
      if (((uint)*(ushort *)(ourBtlSaveDat__10BtlSaveSec + 0xda8) & 1 << (uVar2 & 0x1f)) != 0) {
        *(uint *)(param_1 + *(int *)(param_1 + 0x140) * 4 + 0x114) = uVar2;
        *(int *)(param_1 + 0x140) = *(int *)(param_1 + 0x140) + 1;
      }
    }
  }
  return;
}

/* JP: 0x004f0860  tailor::mReadModel(int)   [mReadModel__6tailorFi]  size=0xe4 */
void mReadModel__6tailorFi(int param_1,int param_2)

{
  undefined8 uVar1;
  undefined1 auStack_230 [256];
  undefined1 auStack_130 [256];
  undefined8 uStack_30;
  undefined2 uStack_28;
  undefined1 uStack_26;
  int iStack_20;
  int iStack_10;
  
  iStack_20 = param_1;
  iStack_10 = param_2;
  uStack_30 = _6169;
  uStack_28 = DAT_005542f8;
  uStack_26 = DAT_005542fa;
  if (*(int *)(param_1 + 0x14c) != 0) {
    __dt__9BufMemoryFv(*(undefined4 *)(param_1 + 0x14c),1);
    *(undefined4 *)(iStack_20 + 0x14c) = 0;
  }
  *(undefined4 *)(iStack_20 + 0x14c) = m_pModel;
  m_bModel = 1;
  m_TexRead = 0;
  sprintf(auStack_130,0x55b880,*(undefined1 *)((int)&uStack_30 + iStack_10));
  uVar1 = SetPathname__7SysToolFPcPCc(auStack_230,auStack_130);
  ReadOrder__11DvdromOrderFPCcPFiP9BufMemoryiPcPv_iiPvi(Dvdromour__11DvdromOrder,uVar1,0x4eafe0,0,iStack_20,0);
  return;
}

/* JP: 0x004f0950  tailor::mGetMotion(int)   [mGetMotion__6tailorFi]  size=0x50 */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined * mGetMotion__6tailorFi(undefined8 param_1,int param_2)

{
  undefined *apuStack_50 [4];
  undefined *puStack_40;
  undefined *puStack_3c;
  undefined *puStack_38;
  undefined *puStack_34;
  undefined8 uStack_30;
  undefined *puStack_28;
  int iStack_10;
  
  iStack_10 = param_2;
  apuStack_50[0] = _6193;
  apuStack_50[1] = PTR__6183_00554304;
  apuStack_50[2] = PTR__6184_00554308;
  apuStack_50[3] = PTR__6185_0055430c;
  puStack_40 = PTR__6186_00554310;
  puStack_3c = PTR__6187_00554314;
  puStack_38 = PTR__6188_00554318;
  puStack_34 = PTR__6189_0055431c;
  uStack_30 = _PTR__6190_00554320;
  puStack_28 = PTR__6192_00554328;
  return apuStack_50[param_2];
}

/* JP: 0x004f09a0  tailor::mSetPage(int)   [mSetPage__6tailorFi]  size=0x430 */
void mSetPage__6tailorFi(int param_1,int param_2)

{
  undefined4 uVar1;
  long lVar2;
  undefined8 uVar3;
  
  if (param_2 == 0) {
    lVar2 = __nw__FUi(0x58);
    uVar1 = 0;
    if (lVar2 != 0) {
      uVar1 = __ct__9primModelFv(lVar2);
    }
    *(undefined4 *)(param_1 + 0xa4) = uVar1;
    uVar3 = getData__7primTexFi(m_pPT,
                            *(int *)(param_1 + *(int *)(param_1 + 0x3c) * 4 + 0x114) + 0xf);
    initialize__9primModelFPUci(*(undefined4 *)(param_1 + 0xa4),uVar3,0xb);
    setRot__9primModelFfff(0x3fa66666,0x3f000000,0x3f333333,*(undefined4 *)(param_1 + 0xa4));
    setPos__9primModelFfff(0x4164cccd,0xc0000000,0,*(undefined4 *)(param_1 + 0xa4));
    uVar3 = getData__7primTexFi(m_pPT,0x1b);
    addMotion__9primModelFPUc(*(undefined4 *)(param_1 + 0xa4),uVar3);
    uVar3 = getData__7primTexFi(m_pPT,0x1a);
    addMotion__9primModelFPUc(*(undefined4 *)(param_1 + 0xa4),uVar3);
    setMotion__9primModelFPCc(*(undefined4 *)(param_1 + 0xa4),0x55b8f0);
    (**(code **)(*(int *)(*(int *)(param_1 + 0xa4) + 0x14) + 0xc))();
  }
  else {
    if (*(int *)(param_1 + 0xa0) != 0) {
      DelayDeleteRequest__9primModelFv(*(undefined4 *)(param_1 + 0xa0));
      *(undefined4 *)(param_1 + 0xa0) = 0;
    }
    lVar2 = __nw__FUi(0x58);
    uVar1 = 0;
    if (lVar2 != 0) {
      uVar1 = __ct__9primModelFv(lVar2);
    }
    *(undefined4 *)(param_1 + 0xa4) = uVar1;
    uVar3 = getData__7primTexFi(m_pPT,
                            *(int *)(param_1 + *(int *)(param_1 + 0x3c) * 4 + 0x114) + 0xf);
    initialize__9primModelFPUci(*(undefined4 *)(param_1 + 0xa4),uVar3,0xb);
    setRot__9primModelFfff(0x3fa66666,0x3f000000,0x3f333333,*(undefined4 *)(param_1 + 0xa4));
    setPos__9primModelFfff(0x4164cccd,0xc0000000,0,*(undefined4 *)(param_1 + 0xa4));
    uVar3 = getData__7primTexFi(m_pPT,0x1b);
    addMotion__9primModelFPUc(*(undefined4 *)(param_1 + 0xa4),uVar3);
    uVar3 = getData__7primTexFi(m_pPT,0x1a);
    addMotion__9primModelFPUc(*(undefined4 *)(param_1 + 0xa4),uVar3);
    (**(code **)(*(int *)(*(int *)(param_1 + 0xa4) + 0x14) + 0xc))();
    lVar2 = __nw__FUi(0x58);
    uVar1 = 0;
    if (lVar2 != 0) {
      uVar1 = __ct__9primModelFv(lVar2);
    }
    *(undefined4 *)(param_1 + 0xa0) = uVar1;
    uVar3 = getData__7primTexFi(m_pPT,
                            *(int *)(param_1 + (*(int *)(param_1 + 0x3c) + 1) * 4 + 0x114) + 0xf);
    initialize__9primModelFPUci(*(undefined4 *)(param_1 + 0xa0),uVar3,0xb);
    setRot__9primModelFfff(0x3fa66666,0x3f000000,0x3f333333,*(undefined4 *)(param_1 + 0xa0));
    setPos__9primModelFfff(0x4164cccd,0xc0000000,0,*(undefined4 *)(param_1 + 0xa0));
    uVar3 = getData__7primTexFi(m_pPT,0x1b);
    addMotion__9primModelFPUc(*(undefined4 *)(param_1 + 0xa0),uVar3);
    uVar3 = getData__7primTexFi(m_pPT,0x1a);
    addMotion__9primModelFPUc(*(undefined4 *)(param_1 + 0xa0),uVar3);
    setMotion__9primModelFPCc(*(undefined4 *)(param_1 + 0xa0),0x55b900);
    (**(code **)(*(int *)(*(int *)(param_1 + 0xa0) + 0x14) + 0xc))();
  }
  *(int *)(param_1 + 0x48) = param_2;
  return;
}

/* JP: 0x004f0dd0  tailor::mIsPageMotion()   [mIsPageMotion__6tailorFv]  size=0x128 */
undefined4 mIsPageMotion__6tailorFv(int param_1)

{
  if (*(int *)(param_1 + 0xa4) != 0) {
    if (*(int *)(param_1 + 0x48) == 0) {
      if (*(char *)(*(int *)(param_1 + 0xa4) + 0x54) != '\0') {
        return 1;
      }
      if (*(int *)(param_1 + 0xa0) != 0) {
        DelayDeleteRequest__9primModelFv(*(undefined4 *)(param_1 + 0xa0));
        *(undefined4 *)(param_1 + 0xa0) = 0;
      }
      *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(param_1 + 0xa4);
      *(undefined4 *)(param_1 + 0xa4) = 0;
    }
    else {
      if (*(char *)(*(int *)(param_1 + 0xa0) + 0x54) != '\0') {
        return 1;
      }
      if (*(int *)(param_1 + 0xa0) != 0) {
        DelayDeleteRequest__9primModelFv(*(undefined4 *)(param_1 + 0xa0));
        *(undefined4 *)(param_1 + 0xa0) = 0;
      }
      *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(param_1 + 0xa4);
      *(undefined4 *)(param_1 + 0xa4) = 0;
    }
  }
  return 0;
}

/* JP: 0x004f0f00  tailor::mMoveStars()   [mMoveStars__6tailorFv]  size=0x1b0 */
void mMoveStars__6tailorFv(int param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  if (*(int *)(param_1 + 0xb0) != 0) {
    for (iVar3 = 0; iVar3 < 5; iVar3 = iVar3 + 1) {
      iVar4 = 0;
      iVar2 = param_1 + iVar3 * 4;
      *(int *)(iVar2 + 0x4c) = *(int *)(iVar2 + 0x4c) + 1;
      if (*(int *)(param_1 + iVar3 * 4 + 0x4c) < 0x17) {
        iVar4 = 0x20;
      }
      else if (*(int *)(param_1 + iVar3 * 4 + 0x4c) < 0x2e) {
        iVar4 = 0x40;
      }
      else if (*(int *)(param_1 + iVar3 * 4 + 0x4c) < 0x45) {
        iVar4 = 0x20;
      }
      else if (*(int *)(param_1 + iVar3 * 4 + 0x4c) == 0x5c) {
        uVar1 = rand();
        iVar2 = param_1 + iVar3 * 4;
        *(uint *)(iVar2 + 0x4c) = *(int *)(iVar2 + 0x4c) + (uVar1 & 0xff);
      }
      else if (0xfe < *(int *)(param_1 + iVar3 * 4 + 0x4c)) {
        *(undefined4 *)(param_1 + iVar3 * 4 + 0x4c) = 0;
      }
      setUV__6prim2DFiiii(*(undefined4 *)(param_1 + iVar3 * 4 + 0xb0),iVar4 + 1,iVar3 * 0x28 + 1,
                      iVar4 + 0x20,iVar3 * 0x28 + 0x28);
    }
  }
  return;
}

/* JP: 0x004f10b0  tailor::mFadeFieldBGM(int)   [mFadeFieldBGM__6tailorFi]  size=0x188 */
void mFadeFieldBGM__6tailorFi(int param_1,int param_2)

{
  if (param_2 == 0) {
    if (sys__6CMusic != 0) {
      *(uint *)(param_1 + 0x15c) = (uint)*(byte *)(sys__6CMusic + 0x7c);
      FadeBGM__6CMusicFUiUi(sys__6CMusic,*(int *)(param_1 + 0x15c) / 3,0x3c);
    }
    if (sys__9StreamBGM != 0) {
      *(uint *)(param_1 + 0x15c) = (uint)*(byte *)(sys__9StreamBGM + 0x78);
      SetVolume__9StreamBGMFi(sys__9StreamBGM,*(int *)(param_1 + 0x15c) / 3);
      *(byte *)(sys__9StreamBGM + 0x76) = *(byte *)(sys__9StreamBGM + 0x76) & 0x7f | 0x80;
      *(undefined1 *)(sys__9StreamBGM + 0x73) = 0;
    }
  }
  else {
    if (sys__6CMusic != 0) {
      FadeBGM__6CMusicFUiUi(sys__6CMusic,*(undefined4 *)(param_1 + 0x15c),0x3c);
    }
    if (sys__9StreamBGM != 0) {
      SetVolume__9StreamBGMFi(sys__9StreamBGM,*(undefined4 *)(param_1 + 0x15c));
      *(byte *)(sys__9StreamBGM + 0x76) = *(byte *)(sys__9StreamBGM + 0x76) & 0x7f | 0x80;
      *(undefined1 *)(sys__9StreamBGM + 0x73) = 0;
    }
  }
  return;
}

/* JP: 0x004f20a0  tailor::~tailor()   [@24@__dt__6tailorFv]  size=0x8 */
int _24___dt__6tailorFv(int param_1,short param_2)

{
  int iVar1;
  int iVar2;
  
  iVar2 = param_1 + -0x18;
  if (iVar2 != 0) {
    *(undefined1 **)(param_1 + -4) = &__vt__6tailor;
    *(undefined4 *)(param_1 + 8) = 0x409810;
    Dispose__7CPollerFP7CPolObj(app__4CApp + 0x48,iVar2);
    if (m_pPT != 0) {
      __dt__7primTexFv(m_pPT,1);
      m_pPT = 0;
    }
    if (*(int *)(param_1 + 0x138) != 0) {
      DelayDeleteRequest__9primSoundFv(*(undefined4 *)(param_1 + 0x138));
      *(undefined4 *)(param_1 + 0x138) = 0;
    }
    if (*(int *)(param_1 + 0x13c) != 0) {
      DelayDeleteRequest__9primSoundFv(*(undefined4 *)(param_1 + 0x13c));
      *(undefined4 *)(param_1 + 0x13c) = 0;
    }
    (**(code **)(*(int *)(*(int *)(param_1 + 0x70) + 8) + 0x18))();
    if (*(int *)(param_1 + 0x70) != 0) {
      iVar1 = *(int *)(param_1 + 0x70);
      if (iVar1 != 0) {
        (**(code **)(*(int *)(iVar1 + 8) + 8))(iVar1,1);
      }
      *(undefined4 *)(param_1 + 0x70) = 0;
    }
    if (m_pModel != 0) {
      __dt__9BufMemoryFv(m_pModel,1);
      m_pModel = 0;
    }
    if (*(int *)(param_1 + 0x134) != 0) {
      __dt__9BufMemoryFv(*(undefined4 *)(param_1 + 0x134),1);
      *(undefined4 *)(param_1 + 0x134) = 0;
    }
    if (iVar2 != -0x18) {
      *(undefined1 **)(param_1 + 8) = &__vt__17DelayDeleteObject;
    }
    __dt__7CPolObjFv(iVar2,0);
    if (0 < param_2) {
      __dl__FPv(iVar2);
    }
  }
  return iVar2;
}
