/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: solomon   functions: 43
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/solomon.md).
 */

/* JP: 0x004f20c0  solomon::DVD_CBFunc(int, BufMemory*, int, char*, void*)   [DVD_CBFunc__7solomonFiP9BufMemoryiPcPv]  size=0xb8 */
undefined8
DVD_CBFunc__7solomonFiP9BufMemoryiPcPv
          (undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5)

{
  undefined4 uVar1;
  long lVar2;
  
  m_pTex = *(undefined4 *)(param_2 + 4);
  m_TexRead = 1;
  mpData = param_2;
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
  initialize__7primTexFP9BufMemory(m_pPT,param_2);
  return 0;
}

/* JP: 0x004f2180  solomon::solomon()   [__ct__7solomonFv]  size=0x13c */
undefined8 __ct__7solomonFv(undefined8 param_1)

{
  undefined1 auVar1 [16];
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  int iVar2;
  int iVar3;
  undefined1 in_vf0 [16];
  undefined1 auVar4 [16];
  undefined1 auVar5 [16];
  undefined1 auVar6 [16];
  
  __ct__7CPolObjFv(param_1);
  iVar3 = (int)param_1;
  *(undefined4 *)(iVar3 + 0x18) = 0;
  *(undefined4 *)(iVar3 + 0x1c) = 0;
  *(undefined1 **)(iVar3 + 0x20) = &__vt__17DelayDeleteObject;
  *(undefined1 **)(iVar3 + 0x14) = &__vt__7solomon;
  *(undefined4 *)(iVar3 + 0x20) = 0x409830;
  __ct__7primWinFv(iVar3 + 0x6ac);
  __ct__4FontFv(iVar3 + 0x7f4);
  *(undefined4 *)(iVar3 + 0xa60) = in_zero_lo;
  *(undefined4 *)(iVar3 + 0xa64) = in_zero_hi;
  *(undefined4 *)(iVar3 + 0xa68) = in_zero_udw;
  *(undefined4 *)(iVar3 + 0xa6c) = in_register_0000000c;
  *(undefined4 *)(iVar3 + 0xa70) = in_zero_lo;
  *(undefined4 *)(iVar3 + 0xa74) = in_zero_hi;
  *(undefined4 *)(iVar3 + 0xa78) = in_zero_udw;
  *(undefined4 *)(iVar3 + 0xa7c) = in_register_0000000c;
  auVar4 = _vmr32(in_vf0);
  auVar5 = _vmr32(auVar4);
  auVar6 = _vmr32(auVar5);
  auVar1 = _sqc2(in_vf0);
  *(undefined1 (*) [16])(iVar3 + 0xab0) = auVar1;
  auVar1 = _sqc2(auVar4);
  *(undefined1 (*) [16])(iVar3 + 0xaa0) = auVar1;
  auVar1 = _sqc2(auVar5);
  *(undefined1 (*) [16])(iVar3 + 0xa90) = auVar1;
  auVar1 = _sqc2(auVar6);
  *(undefined1 (*) [16])(iVar3 + 0xa80) = auVar1;
  m_pPT = 0;
  *(undefined4 *)(iVar3 + 0x8c) = 0;
  *(undefined4 *)(iVar3 + 0x78) = 0;
  *(undefined4 *)(iVar3 + 0x88) = 0;
  *(undefined4 *)(iVar3 + 0x7c) = 0;
  *(undefined4 *)(iVar3 + 0x80) = 0;
  *(undefined4 *)(iVar3 + 0x84) = 0;
  *(undefined4 *)(iVar3 + 0x69c) = 0;
  *(undefined4 *)(iVar3 + 0x2c) = 0;
  *(undefined4 *)(iVar3 + 0x30) = 0;
  *(undefined4 *)(iVar3 + 0x6a0) = 0;
  *(undefined4 *)(iVar3 + 0x6a4) = 0;
  *(undefined4 *)(iVar3 + 0x24) = 0;
  *(undefined4 *)(iVar3 + 0x28) = 0;
  *(undefined4 *)(iVar3 + 0x94) = 0;
  *(undefined4 *)(iVar3 + 0x7fc) = 0;
  *(undefined4 *)(iVar3 + 0x3c4) = 0;
  *(undefined4 *)(iVar3 + 0x74) = 0;
  *(undefined4 *)(iVar3 + 0x804) = 0;
  *(undefined4 *)(iVar3 + 0x808) = 0;
  *(undefined4 *)(iVar3 + 0x84c) = 0;
  *(undefined4 *)(iVar3 + 0x850) = 0;
  *(undefined4 *)(iVar3 + 0x54) = 0;
  *(undefined4 *)(iVar3 + 0x854) = 0;
  *(undefined1 *)(iVar3 + 0x890) = 0;
  *(undefined1 *)(iVar3 + 0xbb4) = 1;
  for (iVar2 = 0; iVar2 < 0x10; iVar2 = iVar2 + 1) {
    *(undefined4 *)(iVar3 + iVar2 * 4 + 0x80c) = 0;
  }
  return param_1;
}

/* JP: 0x004f22c0  solomon::~solomon()   [__dt__7solomonFv]  size=0x15c */
int __dt__7solomonFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 0x14) = &__vt__7solomon;
    *(undefined4 *)(param_1 + 0x20) = 0x409830;
    if (*(int *)(param_1 + 0x854) != 0) {
      DelayDeleteRequest__13solomonEffectFv(*(undefined4 *)(param_1 + 0x854));
      *(undefined4 *)(param_1 + 0x854) = 0;
    }
    Dispose__7CPollerFP7CPolObj(app__4CApp + 0x48,param_1);
    if (m_pPT != 0) {
      __dt__7primTexFv(m_pPT,1);
      m_pPT = 0;
    }
    if (*(int *)(param_1 + 0x74) != 0) {
      DelayDeleteRequest__9primSoundFv(*(undefined4 *)(param_1 + 0x74));
      *(undefined4 *)(param_1 + 0x74) = 0;
    }
    __dt__4FontFv(param_1 + 0x7f4,0xffffffffffffffff);
    __dt__7primWinFv(param_1 + 0x6ac,0xffffffffffffffff);
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

/* JP: 0x004f2420  solomon::initialize(void(*)(int, void*)*, void*)   [initialize__7solomonFPFiPv_vPv]  size=0x158 */
void initialize__7solomonFPFiPv_vPv(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  undefined8 uVar2;
  long lVar3;
  undefined1 auStack_130 [256];
  int iStack_30;
  undefined4 uStack_20;
  undefined4 uStack_10;
  
  iStack_30 = param_1;
  uStack_20 = param_2;
  uStack_10 = param_3;
  uVar2 = SetPathname__7SysToolFPcPCc(auStack_130,0x55edd0);
  ReadOrder__11DvdromOrderFPCcPFiP9BufMemoryiPcPv_iiPvi(Dvdromour__11DvdromOrder,uVar2,0x4f20c0,0,iStack_30,0);
  Entry__7CPollerFP7CPolObjib(app__4CApp + 0x48,iStack_30,0x80,0);
  *(undefined4 *)(iStack_30 + 0x90) = 0;
  m_TexRead = 0;
  *(undefined1 *)(iStack_30 + 0x6a8) = 0;
  *(undefined4 *)(iStack_30 + 0x3c) = 0xffffffff;
  *(undefined4 *)(iStack_30 + 0x44) = 0x28;
  *(undefined4 *)(iStack_30 + 0x24) = uStack_20;
  *(undefined4 *)(iStack_30 + 0x28) = uStack_10;
  lVar3 = __nw__FUi(0x30);
  uVar1 = 0;
  if (lVar3 != 0) {
    uVar1 = __ct__9primSoundFv(lVar3);
  }
  *(undefined4 *)(iStack_30 + 0x74) = uVar1;
  initialize__9primSoundFv(*(undefined4 *)(iStack_30 + 0x74));
  lVar3 = __nw__FUi(0x58);
  uVar1 = 0;
  if (lVar3 != 0) {
    uVar1 = __ct__13solomonEffectFv(lVar3);
  }
  *(undefined4 *)(iStack_30 + 0x854) = uVar1;
  initialize__13solomonEffectFP6Matrix(*(undefined4 *)(iStack_30 + 0x854),iStack_30 + 0xa80);
  return;
}

/* JP: 0x004f2580  solomon::start()   [start__7solomonFv]  size=0x20 */
void start__7solomonFv(int param_1)

{
  *(undefined1 *)(param_1 + 0x6a8) = 1;
  return;
}

/* JP: 0x004f25a0  solomon::Polling()   [Polling__7solomonFv]  size=0x5f60 */
undefined1 Polling__7solomonFv(int param_1)

{
  char cVar1;
  ushort uVar2;
  int iVar3;
  undefined4 uVar4;
  ulong uVar5;
  long lVar6;
  undefined8 uVar7;
  int iVar8;
  ulong uVar9;
  undefined1 auStack_570 [512];
  undefined1 auStack_370 [512];
  undefined1 uStack_170;
  undefined1 uStack_16f;
  undefined1 uStack_16e;
  undefined1 uStack_16d;
  undefined4 uStack_16c;
  undefined4 uStack_168;
  undefined4 uStack_164;
  int iStack_160;
  int iStack_15c;
  short *psStack_158;
  int iStack_154;
  int iStack_150;
  int iStack_14c;
  int iStack_148;
  int iStack_144;
  int iStack_140;
  int iStack_13c;
  int iStack_138;
  int iStack_134;
  int iStack_130;
  int iStack_12c;
  int iStack_128;
  int iStack_124;
  int iStack_120;
  int iStack_11c;
  int iStack_118;
  int iStack_114;
  int iStack_110;
  int iStack_10c;
  int iStack_108;
  int iStack_104;
  int iStack_100;
  int iStack_fc;
  int iStack_f8;
  int iStack_f4;
  int iStack_f0;
  int iStack_ec;
  int iStack_e8;
  int iStack_e4;
  int iStack_e0;
  int iStack_dc;
  int iStack_d8;
  short *psStack_d4;
  undefined1 *puStack_d0;
  int iStack_cc;
  int iStack_c8;
  int iStack_c4;
  int iStack_c0;
  int iStack_bc;
  int iStack_b8;
  int iStack_b4;
  int iStack_b0;
  int iStack_ac;
  undefined4 uStack_a8;
  undefined4 uStack_a4;
  undefined4 uStack_a0;
  short *psStack_9c;
  int iStack_98;
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
  undefined4 uStack_58;
  int iStack_54;
  int iStack_50;
  undefined4 uStack_4c;
  int iStack_48;
  int iStack_44;
  int iStack_40;
  int iStack_3c;
  int iStack_38;
  int iStack_34;
  int iStack_30;
  int iStack_2c;
  int iStack_28;
  short *psStack_24;
  int iStack_20;
  ushort uStack_1a;
  ushort uStack_18;
  ushort uStack_16;
  undefined1 uStack_13;
  undefined1 uStack_12;
  undefined1 uStack_11;
  int iStack_10;
  
  iStack_10 = param_1;
  iStack_20 = GetActive__4CPadFi(0);
  iVar3 = *(int *)(&m_pCoreArray__4CPad + *(int *)(iStack_20 + 4) * 4);
  puStack_d0 = (undefined1 *)(iVar3 + 0x88);
  uStack_170 = *puStack_d0;
  uStack_16f = *(undefined1 *)(iVar3 + 0x89);
  uStack_16e = *(undefined1 *)(iVar3 + 0x8a);
  uStack_16d = *(undefined1 *)(iVar3 + 0x8b);
  uStack_16c = *(undefined4 *)(iVar3 + 0x8c);
  uStack_168 = *(undefined4 *)(iVar3 + 0x90);
  uStack_164 = *(undefined4 *)(iVar3 + 0x94);
  uStack_16 = *(ushort *)(*(int *)(&m_pCoreArray__4CPad + *(int *)(iStack_20 + 4) * 4) + 0x70);
  uVar2 = *(ushort *)(*(int *)(&m_pCoreArray__4CPad + *(int *)(iStack_20 + 4) * 4) + 0x6c);
  uVar9 = (ulong)uStack_16 & 0xf0 | (ulong)uVar2;
  uStack_1a = *(ushort *)(*(int *)(&m_pCoreArray__4CPad + *(int *)(iStack_20 + 4) * 4) + 0x6a);
  uVar5 = uVar9 | (ulong)uStack_1a & 0x300;
  iVar3 = *(int *)(iStack_10 + 0xa48);
  iVar8 = *(int *)(iStack_10 + 0xa44) + iVar3 * *(int *)(iStack_10 + 0xa4c);
  uStack_18 = uVar2;
  switch(*(undefined4 *)(iStack_10 + 0x90)) {
  case 0:
    if ((*(char *)(iStack_10 + 0x6a8) != '\0') && (m_TexRead != '\0')) {
      *(undefined4 *)(iStack_10 + 0x90) = 8;
    }
    break;
  case 1:
    iStack_d8 = __nw__FUi(0x48);
    if (iStack_d8 != 0) {
      iStack_d8 = __ct__15solomonTutorialFv(iStack_d8);
    }
    *(int *)(iStack_10 + 0x84c) = iStack_d8;
    initialize__15solomonTutorialFP7primTex(*(undefined4 *)(iStack_10 + 0x84c),m_pPT);
    *(undefined4 *)(iStack_10 + 0x90) = 2;
    break;
  case 2:
    lVar6 = isFinish__15solomonTutorialFv(*(undefined4 *)(iStack_10 + 0x84c));
    if (lVar6 != 0) {
      if (*(int *)(iStack_10 + 0x84c) != 0) {
        iStack_dc = *(int *)(iStack_10 + 0x84c);
        if (iStack_dc != 0) {
          (**(code **)(*(int *)(iStack_dc + 0x14) + 8))(iStack_dc,1);
        }
        *(undefined4 *)(iStack_10 + 0x84c) = 0;
      }
      *(undefined4 *)(iStack_10 + 0x90) = 10;
    }
    break;
  case 3:
    if (*(int *)(iStack_10 + 0x88) == 0) {
      *(undefined4 *)(iStack_10 + 0x38) = 1;
      mSetupQueryWin__7solomonFi(iStack_10,0);
    }
    else {
      lVar6 = isFade__7primWinFv(*(undefined4 *)(iStack_10 + 0x88));
      if (lVar6 == 0) {
        mSetupMainCursor__7solomonFi(iStack_10,0);
        setItem__10primCursorFP7primWini(*(undefined4 *)(iStack_10 + 0x2c),*(undefined4 *)(iStack_10 + 0x8c),
                        *(undefined4 *)(iStack_10 + 0x38));
        qMove__10primCursorFv(*(undefined4 *)(iStack_10 + 0x2c));
        *(undefined4 *)(iStack_10 + 0x90) = 4;
      }
    }
    break;
  case 4:
    if ((uVar2 & 0x2000) == 0) {
      if ((uVar2 & 0x4000) == 0) {
        iStack_30 = *(int *)(iStack_10 + 0x38);
        uVar4 = menuCheckKey__7primWinFiP10primCursor(*(undefined4 *)(iStack_10 + 0x8c),uVar5,
                                *(undefined4 *)(iStack_10 + 0x2c));
        *(undefined4 *)(iStack_10 + 0x38) = uVar4;
        if (*(int *)(iStack_10 + 0x38) != iStack_30) {
          play__9primSoundFi(*(undefined4 *)(iStack_10 + 0x74),0);
        }
      }
      else {
        play__9primSoundFi(*(undefined4 *)(iStack_10 + 0x74),3);
        *(undefined4 *)(iStack_10 + 0x90) = 10;
        mReleaseMainCursor__7solomonFv(iStack_10);
        if (*(int *)(iStack_10 + 0x88) != 0) {
          DelayDeleteRequest__7primWinFv(*(undefined4 *)(iStack_10 + 0x88));
          *(undefined4 *)(iStack_10 + 0x88) = 0;
        }
        *(undefined4 *)(iStack_10 + 0x8c) = 0;
      }
    }
    else {
      play__9primSoundFi(*(undefined4 *)(iStack_10 + 0x74),2);
      if (*(int *)(iStack_10 + 0x38) == 0) {
        *(undefined4 *)(iStack_10 + 0x90) = 0x1e;
      }
      else {
        *(undefined4 *)(iStack_10 + 0x90) = 10;
      }
      mReleaseMainCursor__7solomonFv(iStack_10);
      if (*(int *)(iStack_10 + 0x88) != 0) {
        DelayDeleteRequest__7primWinFv(*(undefined4 *)(iStack_10 + 0x88));
        *(undefined4 *)(iStack_10 + 0x88) = 0;
      }
      *(undefined4 *)(iStack_10 + 0x8c) = 0;
    }
    break;
  case 5:
    if (*(int *)(iStack_10 + 0x88) == 0) {
      *(undefined4 *)(iStack_10 + 0x38) = 1;
      mSetupQueryWin__7solomonFi(iStack_10,3);
    }
    else {
      lVar6 = isFade__7primWinFv(*(undefined4 *)(iStack_10 + 0x88));
      if (lVar6 == 0) {
        uVar7 = mSetupMainCursor__7solomonFi(iStack_10,0);
        setItem__10primCursorFP7primWini(*(undefined4 *)(iStack_10 + 0x2c),*(undefined4 *)(iStack_10 + 0x8c),
                        *(undefined4 *)(iStack_10 + 0x38),*(undefined4 *)(iStack_10 + 0x2c),
                        *(undefined4 *)(iStack_10 + 0x38),uVar7);
        qMove__10primCursorFv(*(undefined4 *)(iStack_10 + 0x2c));
        *(undefined4 *)(iStack_10 + 0x90) = 6;
      }
    }
    break;
  case 6:
    if ((uVar2 & 0x2000) == 0) {
      if ((uVar2 & 0x4000) == 0) {
        iStack_34 = *(int *)(iStack_10 + 0x38);
        uVar4 = menuCheckKey__7primWinFiP10primCursor(*(undefined4 *)(iStack_10 + 0x8c),uVar5,
                                *(undefined4 *)(iStack_10 + 0x2c));
        *(undefined4 *)(iStack_10 + 0x38) = uVar4;
        if (*(int *)(iStack_10 + 0x38) != iStack_34) {
          play__9primSoundFi(*(undefined4 *)(iStack_10 + 0x74),0);
        }
      }
      else {
        play__9primSoundFi(*(undefined4 *)(iStack_10 + 0x74),3);
        *(undefined4 *)(iStack_10 + 0x90) = 0x19;
        mReleaseMainCursor__7solomonFv(iStack_10);
        *(undefined4 *)(iStack_10 + 0x8c) = *(undefined4 *)(iStack_10 + 0x7c);
        iStack_e4 = __nw__FUi(0x3c);
        if (iStack_e4 != 0) {
          iStack_e4 = __ct__12udScrollMarkFv(iStack_e4);
        }
        *(int *)(iStack_10 + 0x54) = iStack_e4;
        initialize__12udScrollMarkFP7primTexiiiii(*(undefined4 *)(iStack_10 + 0x54),m_pPT,0,
                        *(int *)(iStack_10 + 0xbc0) + -5,400,0x5a,0xf2);
        uVar7 = select__12udScrollMarkFi(*(undefined4 *)(iStack_10 + 0x54),*(undefined4 *)(iStack_10 + 0xba0)
                               );
        mSetupMainCursor__7solomonFi(iStack_10,2,uVar7);
        if (*(int *)(iStack_10 + 0x88) != 0) {
          DelayDeleteRequest__7primWinFv(*(undefined4 *)(iStack_10 + 0x88));
          *(undefined4 *)(iStack_10 + 0x88) = 0;
        }
      }
    }
    else {
      play__9primSoundFi(*(undefined4 *)(iStack_10 + 0x74),2);
      if (*(int *)(iStack_10 + 0x38) == 0) {
        *(undefined4 *)(iStack_10 + 3000) = 0;
        *(undefined4 *)(iStack_10 + 0xbbc) = 0;
        *(undefined4 *)(iStack_10 + 0xbc0) = 0;
        *(undefined4 *)(iStack_10 + 0x90) = 7;
        mReleaseMainCursor__7solomonFv(iStack_10);
      }
      else {
        *(undefined4 *)(iStack_10 + 0x90) = 0x19;
        mReleaseMainCursor__7solomonFv(iStack_10);
        *(undefined4 *)(iStack_10 + 0x8c) = *(undefined4 *)(iStack_10 + 0x7c);
        iStack_e0 = __nw__FUi(0x3c);
        if (iStack_e0 != 0) {
          iStack_e0 = __ct__12udScrollMarkFv(iStack_e0);
        }
        *(int *)(iStack_10 + 0x54) = iStack_e0;
        initialize__12udScrollMarkFP7primTexiiiii(*(undefined4 *)(iStack_10 + 0x54),m_pPT,0,
                        *(int *)(iStack_10 + 0xbc0) + -5,400,0x5a,0xf2);
        select__12udScrollMarkFi(*(undefined4 *)(iStack_10 + 0x54),*(undefined4 *)(iStack_10 + 0xba0));
        mSetupMainCursor__7solomonFi(iStack_10,2);
      }
      if (*(int *)(iStack_10 + 0x88) != 0) {
        DelayDeleteRequest__7primWinFv(*(undefined4 *)(iStack_10 + 0x88));
        *(undefined4 *)(iStack_10 + 0x88) = 0;
      }
    }
    break;
  case 7:
    *(int *)(iStack_10 + 3000) = *(int *)(iStack_10 + 3000) + 1;
    if (0x10 < *(int *)(iStack_10 + 3000)) {
      *(undefined4 *)(iStack_10 + 0xbc0) = 0xffffffff;
      for (iStack_38 = 0; iStack_38 < 0x48; iStack_38 = iStack_38 + 1) {
        if (((*(char *)(iStack_10 + iStack_38 * 6 + 0x4ed) != '\x01') &&
            (lVar6 = isDemon__11solomonSlotFv(*(undefined4 *)(iStack_10 + iStack_38 * 4 + 0x3cc)),
            lVar6 != 0)) &&
           (*(char *)(iStack_10 + *(int *)(iStack_10 + 0x34) * 2 + 0xb04) ==
            (&mDemonAttr)[*(char *)(iStack_10 + iStack_38 * 6 + 0x4ec)])) {
          *(int *)(iStack_10 + 0xbc0) = iStack_38;
          break;
        }
      }
      if (*(int *)(iStack_10 + 0xbc0) == -1) {
        if (0x30 < *(int *)(iStack_10 + 3000)) {
          for (iStack_3c = 0; iStack_3c < *(int *)(iStack_10 + 0xbbc); iStack_3c = iStack_3c + 1) {
            if (*(int *)(iStack_10 + iStack_3c * 4 + 0x80c) != 0) {
              iStack_e8 = *(int *)(iStack_10 + iStack_3c * 4 + 0x80c);
              if (iStack_e8 != 0) {
                (**(code **)(*(int *)(iStack_e8 + 0x14) + 8))(iStack_e8,1);
              }
              *(undefined4 *)(iStack_10 + iStack_3c * 4 + 0x80c) = 0;
            }
          }
          uVar7 = mReleaseHintWin__7solomonFv(iStack_10);
          mReleaseMessWin__7solomonFv(iStack_10,uVar7);
          *(undefined4 *)(iStack_10 + 0x90) = 10;
          *(undefined4 *)(iStack_10 + 0x34) = 2;
          *(undefined4 *)(iStack_10 + 0x8c) = 0;
          *(undefined4 *)(iStack_10 + 3000) = 0;
        }
      }
      else {
        iStack_40 = *(int *)(iStack_10 + 0xbbc);
        iStack_44 = *(int *)(iStack_10 + 0xbc0);
        iStack_48 = (int)*(char *)(iStack_10 + *(int *)(iStack_10 + 0x34) * 2 + 0xb04);
        if (*(int *)(iStack_10 + iStack_40 * 4 + 0x80c) != 0) {
          iStack_ec = *(int *)(iStack_10 + iStack_40 * 4 + 0x80c);
          if (iStack_ec != 0) {
            (**(code **)(*(int *)(iStack_ec + 0x14) + 8))(iStack_ec,1);
          }
          *(undefined4 *)(iStack_10 + iStack_40 * 4 + 0x80c) = 0;
        }
        play__9primSoundFi(*(undefined4 *)(iStack_10 + 0x74),3);
        iStack_f0 = __nw__FUi(0x60);
        if (iStack_f0 != 0) {
          iStack_f0 = __ct__10floatDemonFv(iStack_f0);
        }
        *(int *)(iStack_10 + iStack_40 * 4 + 0x80c) = iStack_f0;
        initialize__10floatDemonFP6MatrixffP9primLayer
                  (0x43800000,0x43600000,*(undefined4 *)(iStack_10 + iStack_40 * 4 + 0x80c),
                   iStack_10 + 0xa80,*(undefined4 *)(iStack_10 + 0x7f8));
        setRGBA__10floatDemonFiiii
                  (*(undefined4 *)(iStack_10 + iStack_40 * 4 + 0x80c),(&mAREACOLORTbl)[iStack_48],
                   (&DAT_00554411)[iStack_48],(&DAT_00554412)[iStack_48],0x80);
        setCurrentDemon__10floatDemonFi
                  (*(undefined4 *)(iStack_10 + iStack_40 * 4 + 0x80c),
                   *(undefined1 *)(iStack_10 + iStack_44 * 6 + 0x4ec));
        eraseSlot__10floatDemonFff
                  (*(float *)(iStack_10 + 0x860) +
                   *(float *)(iStack_10 + 0xa54) * (float)*(int *)(&mSlotBaseTbl + iStack_44 * 0xc),
                   *(float *)(iStack_10 + 0x864) +
                   *(float *)(iStack_10 + 0xa54) * (float)*(int *)(&DAT_00554454 + iStack_44 * 0xc),
                   *(undefined4 *)(iStack_10 + iStack_40 * 4 + 0x80c));
        *(int *)(iStack_10 + 0xbbc) = *(int *)(iStack_10 + 0xbbc) + 1;
        *(undefined4 *)(iStack_10 + 3000) = 0;
        uStack_4c = setDemon__11solomonSlotFi
                              (*(undefined4 *)(iStack_10 + iStack_44 * 4 + 0x3cc),0xffffffffffffffff
                              );
        mBackDemon__7solomonFi(iStack_10,uStack_4c);
        mEraseLine__7solomonFi(iStack_10,iStack_44);
        *(undefined1 *)(iStack_10 + iStack_44 * 6 + 0x4ec) = 0xff;
        *(int *)(iStack_10 + 0xb00) = *(int *)(iStack_10 + 0xb00) + -1;
      }
    }
    break;
  case 8:
    if (*(int *)(iStack_10 + 0x94) == 0) {
      psStack_d4 = (short *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x220);
      psStack_24 = psStack_d4;
      if ((*psStack_d4 != 1) ||
         (lVar6 = isReady__13solomonEffectFv(*(undefined4 *)(iStack_10 + 0x854)), lVar6 != 0)) {
        mSetupBG__7solomonFv(iStack_10);
        *(undefined4 *)(iStack_10 + 0xbc4) = 0;
        (**(code **)(iStack_10 + 0x24))
                  (*(undefined4 *)(iStack_10 + 0xbc4),*(undefined4 *)(iStack_10 + 0x28));
      }
    }
    else {
      lVar6 = isFade__8primFadeFv(*(int *)(iStack_10 + 0x94) + 0xc);
      if (lVar6 == 0) {
        *(undefined4 *)(iStack_10 + 0xbc4) = 1;
        (**(code **)(iStack_10 + 0x24))
                  (*(undefined4 *)(iStack_10 + 0xbc4),*(undefined4 *)(iStack_10 + 0x28));
        *(undefined4 *)(iStack_10 + 0x34) = 0;
        if (*(char *)(iStack_10 + 0xbb4) == '\0') {
          *(undefined4 *)(iStack_10 + 0x90) = 10;
        }
        else {
          *(undefined4 *)(iStack_10 + 0x90) = 1;
        }
      }
    }
    break;
  case 9:
    if ((*(int *)(iStack_10 + 0x870) == 0) && (*(int *)(iStack_10 + 3000) == 0)) {
      if ((uVar2 & 0x2000) == 0) {
        if ((uVar2 & 0x4000) == 0) {
          mCheckKey__7solomonFi(iStack_10,uVar5);
          mCheckMapView__7solomonFiP12CAnalogStick(iStack_10,uVar5,&uStack_170);
        }
        else {
          setCursor__10floatDemonFP10primCursor
                    (*(undefined4 *)(iStack_10 + 0x808),*(undefined4 *)(iStack_10 + 0x2c));
          play__9primSoundFi(*(undefined4 *)(iStack_10 + 0x74),3);
          if (*(int *)(iStack_10 + 0x3c) != -1) {
            iStack_b0 = getPT__7primWinFi(*(undefined4 *)(iStack_10 + 0x84),
                                        *(undefined4 *)(iStack_10 + 0x34));
            SetCSA__8FontItemFUc(iStack_b0,1);
            *(undefined1 *)(iStack_b0 + 0x5c) = 0;
            uVar5 = (ulong)*(byte *)(iStack_b0 + 0x11) & 0xfffffffffffffffd | 2;
            *(char *)(iStack_b0 + 0x11) = (char)uVar5;
            *(byte *)(iStack_b0 + 0x10) =
                 *(byte *)(iStack_b0 + 0x10) & 0xfd | (byte)((uint)((uVar5 << 0x3e) >> 0x3f) << 1);
            mBackDemon__7solomonFi(iStack_10,*(undefined4 *)(iStack_10 + 0x3c));
            *(undefined4 *)(iStack_10 + 0x3c) = 0xffffffff;
          }
          mMakeDemonList__7solomonFv(iStack_10);
          removeCursor__13solomonCursorFv(*(undefined4 *)(iStack_10 + 0x69c));
          setPolyItem__10primCursorFP7primWini(*(undefined4 *)(iStack_10 + 0x2c),*(undefined4 *)(iStack_10 + 0x84),
                          *(undefined4 *)(iStack_10 + 0x34));
          *(undefined4 *)(iStack_10 + 0x90) = 0x13;
        }
      }
      else if ((&DAT_00554458)[iVar8 * 0xc] == '\x04') {
        if (((*(int *)(iStack_10 + 0x3c) == -1) && (*(char *)(iStack_10 + iVar8 * 6 + 0x4ec) == -1))
           || (*(char *)(iStack_10 + iVar8 * 6 + 0x4ed) != '\0')) {
          if (((*(char *)(iStack_10 + iVar8 * 6 + 0x4ec) == -1) && (*(int *)(iStack_10 + 0x84) == 0)
              ) && ((*(int *)(iStack_10 + 0xac8) != 0 &&
                    (lVar6 = isMove__10solomonThmFv(*(undefined4 *)(iStack_10 + 0x6a4)), lVar6 == 0)
                    ))) {
            play__9primSoundFi(*(undefined4 *)(iStack_10 + 0x74),1);
            *(undefined4 *)(iStack_10 + 0x90) = 0x12;
          }
        }
        else if ((*(int *)(iStack_10 + 0x3c) == -1) ||
                ((&mDemonAttr)[*(int *)(iStack_10 + 0x3c)] == (&DAT_00554458)[iVar8 * 0xc])) {
          if ((*(int *)(iStack_10 + 0x3c) == -1) || (*(char *)(iStack_10 + iVar8 * 6 + 0x4ec) == -1)
             ) {
            if (*(int *)(iStack_10 + 0x3c) == -1) {
              play__9primSoundFi(*(undefined4 *)(iStack_10 + 0x74),3);
            }
            else {
              play__9primSoundFi(*(undefined4 *)(iStack_10 + 0x74),0x1004);
            }
            if (*(int *)(iStack_10 + 0x808) != 0) {
              setSlot__10floatDemonFv(*(undefined4 *)(iStack_10 + 0x808));
            }
            iStack_28 = *(int *)(iStack_10 + 0x3c);
            if (*(int *)(iStack_10 + 0x3c) != -1) {
              *(int *)(iStack_10 + 0xb00) = *(int *)(iStack_10 + 0xb00) + 1;
              setDemon__10solomonThmFi
                        (*(undefined4 *)(iStack_10 + 0x6a4),*(undefined4 *)(iStack_10 + 0x3c));
              mSetLine__7solomonFi(iStack_10,iVar8);
            }
            *(char *)(iStack_10 + iVar8 * 6 + 0x4ec) = (char)*(undefined4 *)(iStack_10 + 0x3c);
            uVar4 = setDemon__11solomonSlotFi
                              (*(undefined4 *)(iStack_10 + iVar8 * 4 + 0x3cc),
                               *(undefined4 *)(iStack_10 + 0x3c));
            *(undefined4 *)(iStack_10 + 0x3c) = uVar4;
            if (*(int *)(iStack_10 + 0x3c) != -1) {
              *(int *)(iStack_10 + 0xb00) = *(int *)(iStack_10 + 0xb00) + -1;
              setDemon__10solomonThmFi
                        (*(undefined4 *)(iStack_10 + 0x6a4),*(undefined4 *)(iStack_10 + 0x3c));
            }
            mEraseLine__7solomonFi(iStack_10,iVar8);
            iStack_2c = (char)(&DAT_00554458)[iVar8 * 0xc] * 3;
            setRGBA__13solomonCursorFiiii
                      (*(undefined4 *)(iStack_10 + 0x69c),(&mAREACOLORTbl)[iStack_2c],
                       (&DAT_00554411)[iStack_2c],(&DAT_00554412)[iStack_2c],0x80);
            if ((iStack_28 == -1) ||
               (lVar6 = mCheckArea__7solomonFi(iStack_10,(&mDemonAttr)[iStack_28]), lVar6 == 0)) {
              if (*(int *)(iStack_10 + 0x3c) != -1) {
                iStack_ac = getPT__7primWinFi(*(undefined4 *)(iStack_10 + 0x84),
                                            *(undefined4 *)(iStack_10 + 0x34));
                SetCSA__8FontItemFUc(iStack_ac,1);
                *(undefined1 *)(iStack_ac + 0x5c) = 0;
                uVar5 = (ulong)*(byte *)(iStack_ac + 0x11) & 0xfffffffffffffffd | 2;
                *(char *)(iStack_ac + 0x11) = (char)uVar5;
                *(byte *)(iStack_ac + 0x10) =
                     *(byte *)(iStack_ac + 0x10) & 0xfd |
                     (byte)((uint)((uVar5 << 0x3e) >> 0x3f) << 1);
                mBackDemon__7solomonFi(iStack_10,*(undefined4 *)(iStack_10 + 0x3c));
                *(undefined4 *)(iStack_10 + 0x3c) = 0xffffffff;
              }
              mMakeDemonList__7solomonFv(iStack_10);
              removeCursor__13solomonCursorFv(*(undefined4 *)(iStack_10 + 0x69c));
              setPolyItem__10primCursorFP7primWini(*(undefined4 *)(iStack_10 + 0x2c),*(undefined4 *)(iStack_10 + 0x84),
                              *(undefined4 *)(iStack_10 + 0x34));
              *(undefined4 *)(iStack_10 + 0x90) = 0x13;
            }
            else {
              setDisp__14pageScrollMarkFb(*(undefined4 *)(iStack_10 + 0x804),0);
              setArea__11solomonAreaFibb
                        (*(undefined4 *)(iStack_10 + 0x6a0),(&DAT_00554458)[iVar8 * 0xc],1,1);
              mFixArea__7solomonFi(iStack_10,(&mDemonAttr)[iStack_28]);
              setDemon__10solomonThmFi(*(undefined4 *)(iStack_10 + 0x6a4),0xfffffffffffffffe);
              uVar7 = sprintf(auStack_370,solomonMess_areaComplete_J,
                                      (&solomonMess_areaName_J)[*(int *)(iStack_10 + 0x5c)]);
              mReleaseMessWin__7solomonFv(iStack_10,uVar7);
              mSetupMessWin__7solomonFPcbi(iStack_10,auStack_370,1,0);
              play__9primSoundFi(*(undefined4 *)(iStack_10 + 0x74),0x1000);
              *(undefined4 *)(iStack_10 + 0x90) = 0x1a;
            }
          }
          else {
            if (*(int *)(iStack_10 + 0x808) != 0) {
              removeCursor__10floatDemonFv(*(undefined4 *)(iStack_10 + 0x808));
            }
            play__9primSoundFi(*(undefined4 *)(iStack_10 + 0x74),2);
            *(undefined4 *)(iStack_10 + 0x90) = 0x16;
          }
        }
        else {
          play__9primSoundFi(*(undefined4 *)(iStack_10 + 0x74),4);
        }
      }
      else {
        play__9primSoundFi(*(undefined4 *)(iStack_10 + 0x74),4);
      }
    }
    else if (*(int *)(iStack_10 + 3000) != 0) {
      *(int *)(iStack_10 + 3000) = *(int *)(iStack_10 + 3000) + -1;
    }
    break;
  case 10:
    if (*(int *)(iStack_10 + 0x78) == 0) {
      if (*(int *)(iStack_10 + 0x8c) == 0) {
        mSetupMainWin__7solomonFv(iStack_10);
      }
    }
    else {
      lVar6 = isFade__7primWinFv(*(undefined4 *)(iStack_10 + 0x78));
      if (lVar6 == 0) {
        mSetupMainCursor__7solomonFi(iStack_10,1);
        *(undefined4 *)(iStack_10 + 0x90) = 0xb;
      }
    }
    break;
  case 0xb:
    if ((uVar2 & 0x2000) == 0) {
      if ((uVar2 & 0x4000) == 0) {
        iStack_60 = *(int *)(iStack_10 + 0x34);
        uVar4 = menuCheckKey__7primWinFiP10primCursor(*(undefined4 *)(iStack_10 + 0x8c),uVar5,
                                *(undefined4 *)(iStack_10 + 0x2c));
        *(undefined4 *)(iStack_10 + 0x34) = uVar4;
        if (*(int *)(iStack_10 + 0x34) != iStack_60) {
          play__9primSoundFi(*(undefined4 *)(iStack_10 + 0x74),0);
        }
        mCheckMapView__7solomonFiP12CAnalogStick(iStack_10,uVar5,&uStack_170);
      }
      else {
        play__9primSoundFi(*(undefined4 *)(iStack_10 + 0x74),3);
        mReleaseMainCursor__7solomonFv(iStack_10);
        fadeout__7primWinFi(*(undefined4 *)(iStack_10 + 0x78),0x10);
        *(undefined4 *)(iStack_10 + 0x90) = 3;
      }
    }
    else if (*(char *)(iStack_10 + *(int *)(iStack_10 + 0x34) * 2 + 0xb05) == '\0') {
      uVar7 = play__9primSoundFi(*(undefined4 *)(iStack_10 + 0x74),2);
      uVar7 = setTitle__10solomonThmFi
                        (*(undefined4 *)(iStack_10 + 0x6a4),*(int *)(iStack_10 + 0x34) + 1,uVar7);
      iVar3 = *(int *)(iStack_10 + 0x34);
      if (iVar3 == 2) {
        fadeout__7primWinFi(*(undefined4 *)(iStack_10 + 0x78),0x10);
        *(undefined4 *)(iStack_10 + 0x90) = 0x18;
        mReleaseMainCursor__7solomonFv(iStack_10);
      }
      else if (iVar3 == 1) {
        fadeout__7primWinFi(*(undefined4 *)(iStack_10 + 0x78),0x10,*(undefined4 *)(iStack_10 + 0x78),
                        uVar7);
        *(undefined4 *)(iStack_10 + 0x90) = 0xc;
        mReleaseMainCursor__7solomonFv(iStack_10);
      }
      else if (iVar3 == 0) {
        fadeout__7primWinFi(*(undefined4 *)(iStack_10 + 0x78),0x10,0x10,uVar7);
        *(undefined4 *)(iStack_10 + 0x90) = 0x10;
        mReleaseMainCursor__7solomonFv(iStack_10);
      }
    }
    else {
      play__9primSoundFi(*(undefined4 *)(iStack_10 + 0x74),4);
    }
    break;
  case 0xc:
    if (*(int *)(iStack_10 + 0x7c) == 0) {
      if (*(int *)(iStack_10 + 0x8c) == 0) {
        mSetupHintWin__7solomonFv(iStack_10);
        setDemon__10solomonThmFi(*(undefined4 *)(iStack_10 + 0x6a4),0xfffffffffffffffe);
      }
    }
    else {
      lVar6 = isFade__7primWinFv(*(undefined4 *)(iStack_10 + 0x7c));
      if (lVar6 == 0) {
        mSetupMainCursor__7solomonFi(iStack_10,2);
        iStack_110 = __nw__FUi(0x3c);
        if (iStack_110 != 0) {
          iStack_110 = __ct__12udScrollMarkFv(iStack_110);
        }
        *(int *)(iStack_10 + 0x54) = iStack_110;
        initialize__12udScrollMarkFP7primTexiiiii(*(undefined4 *)(iStack_10 + 0x54),m_pPT,0,
                        *(int *)(iStack_10 + 0xac0) + -5,400,0x5a,0xf2);
        select__12udScrollMarkFi(*(undefined4 *)(iStack_10 + 0x54),*(undefined4 *)(iStack_10 + 0xba0));
        *(undefined4 *)(iStack_10 + 0x90) = 0xd;
      }
    }
    break;
  case 0xd:
    if ((*(int *)(iStack_10 + 0xba4) == 0) && (*(int *)(iStack_10 + 0x870) == 0)) {
      if ((uVar2 & 0x4000) == 0) {
        if (((uVar9 & 0x50) == 0) || (*(int *)(iStack_10 + 0xac0) < 2)) {
          mCheckMapView__7solomonFiP12CAnalogStick(iStack_10,uVar5,&uStack_170);
        }
        else {
          play__9primSoundFi(*(undefined4 *)(iStack_10 + 0x74),0);
          iStack_bc = getPT__7primWinFi(*(undefined4 *)(iStack_10 + 0x8c),
                                      *(undefined4 *)(iStack_10 + 0x34));
          SetCSA__8FontItemFUc(iStack_bc,0);
          *(undefined1 *)(iStack_bc + 0x5c) = 0;
          uVar5 = (ulong)*(byte *)(iStack_bc + 0x11) & 0xfffffffffffffffd | 2;
          *(char *)(iStack_bc + 0x11) = (char)uVar5;
          *(byte *)(iStack_bc + 0x10) =
               *(byte *)(iStack_bc + 0x10) & 0xfd | (byte)((uint)((uVar5 << 0x3e) >> 0x3f) << 1);
          if ((uVar9 & 0x40) == 0) {
            iStack_78 = *(int *)(iStack_10 + 0x34) + -1;
            if (iStack_78 < 0) {
              iStack_78 = *(int *)(iStack_10 + 0xac0) + -1;
            }
          }
          else {
            iStack_78 = *(int *)(iStack_10 + 0x34) + 1;
            if (*(int *)(iStack_10 + 0xac0) <= iStack_78) {
              iStack_78 = 0;
            }
          }
          mSetTextScroll__7solomonFi(iStack_10,iStack_78);
          iStack_7c = (int)*(char *)(iStack_10 + *(int *)(iStack_10 + 0x34) * 2 + 0xb04);
          mReleaseMessWin__7solomonFv(iStack_10);
          mSetupMessWin__7solomonFPcbi(iStack_10,(&solomonMess_hintNote_J)[iStack_7c],0,0);
          Finish__11MenuMessageFv(*(undefined4 *)(iStack_10 + 0x7fc));
          *(int *)(iStack_10 + 0xa44) = (int)(char)(&mAreaBasePoint)[iStack_7c * 2];
          *(int *)(iStack_10 + 0xa48) = (int)(char)(&DAT_005543b1)[iStack_7c * 2];
          iStack_80 = *(int *)(iStack_10 + 0xa44) + *(int *)(iStack_10 + 0xa48) * 9;
          setArea__11solomonAreaFibb
                    (*(undefined4 *)(iStack_10 + 0x6a0),(&DAT_00554458)[iStack_80 * 0xc],
                     *(char *)(iStack_10 + iStack_80 * 6 + 0x4ed) != '\0',0);
          mSetWorldScroll__7solomonFv(iStack_10);
        }
      }
      else {
        if (*(int *)(iStack_10 + 0x54) != 0) {
          iStack_114 = *(int *)(iStack_10 + 0x54);
          if (iStack_114 != 0) {
            (**(code **)(*(int *)(iStack_114 + 0x14) + 8))(iStack_114,1);
          }
          *(undefined4 *)(iStack_10 + 0x54) = 0;
        }
        play__9primSoundFi(*(undefined4 *)(iStack_10 + 0x74),3);
        uVar7 = fadeout__7primWinFi(*(undefined4 *)(iStack_10 + 0x8c),0x10);
        fadeout__7primWinFi(*(undefined4 *)(iStack_10 + 0x80),0x10,0x10,uVar7);
        uVar7 = mReleaseMainCursor__7solomonFv(iStack_10);
        *(undefined4 *)(iStack_10 + 0x90) = 10;
        *(undefined4 *)(iStack_10 + 0x34) = 1;
        setTitle__10solomonThmFi(*(undefined4 *)(iStack_10 + 0x6a4),0,1,uVar7);
        setDemon__10solomonThmFi(*(undefined4 *)(iStack_10 + 0x6a4),0xffffffffffffffff);
      }
    }
    else if (*(int *)(iStack_10 + 0xba4) != 0) {
      *(int *)(iStack_10 + 0xbb0) = *(int *)(iStack_10 + 0xbb0) + *(int *)(iStack_10 + 0xba8);
      for (iStack_74 = 0; iStack_74 < *(int *)(iStack_10 + 0xac0); iStack_74 = iStack_74 + 1) {
        iVar3 = getPP__7primWinFi(*(undefined4 *)(iStack_10 + 0x8c),iStack_74);
        (**(code **)(*(int *)(iVar3 + 8) + 0x24))
                  ((float)*(int *)(iStack_10 + 0xbac),
                   (float)(*(int *)(iStack_10 + 0xbb0) + iStack_74 * 0x16));
        iVar3 = getPT__7primWinFi(*(undefined4 *)(iStack_10 + 0x8c),iStack_74);
        (**(code **)(*(int *)(iVar3 + 8) + 0x24))
                  ((float)(*(int *)(iStack_10 + 0xbac) + 0x12),
                   (float)(*(int *)(iStack_10 + 0xbb0) + iStack_74 * 0x16));
      }
      *(int *)(iStack_10 + 0xba4) = *(int *)(iStack_10 + 0xba4) + -1;
    }
    break;
  case 0xe:
    iStack_c0 = *(int *)(iStack_10 + 0x8c);
    if (*(char *)(iStack_c0 + 0x102) != '\0') {
      dispHint__10solomonThmFi(*(undefined4 *)(iStack_10 + 0x6a4),*(undefined4 *)(iStack_10 + 0x34))
      ;
      *(undefined4 *)(iStack_10 + 0x90) = 0xf;
    }
    break;
  case 0xf:
    if ((uVar2 & 0x4000) != 0) {
      uVar7 = play__9primSoundFi(*(undefined4 *)(iStack_10 + 0x74),3);
      *(undefined4 *)(iStack_10 + 0x90) = 0xc;
      fadein__10solomonThmFi(*(undefined4 *)(iStack_10 + 0x6a4),1,uVar7);
    }
    break;
  case 0x10:
    if (*(int *)(iStack_10 + 0x7c) == 0) {
      if (*(int *)(iStack_10 + 0x8c) == 0) {
        mSetupDemonMenuWin__7solomonFv(iStack_10);
      }
    }
    else {
      lVar6 = isFade__7primWinFv(*(undefined4 *)(iStack_10 + 0x7c));
      if (lVar6 == 0) {
        mSetupMainCursor__7solomonFi(iStack_10,2);
        iStack_118 = __nw__FUi(0x3c);
        if (iStack_118 != 0) {
          iStack_118 = __ct__12udScrollMarkFv(iStack_118);
        }
        *(int *)(iStack_10 + 0x54) = iStack_118;
        initialize__12udScrollMarkFP7primTexiiiii(*(undefined4 *)(iStack_10 + 0x54),m_pPT,0,4,400,0x5a,0xf2);
        select__12udScrollMarkFi(*(undefined4 *)(iStack_10 + 0x54),*(undefined4 *)(iStack_10 + 0xba0));
        *(undefined4 *)(iStack_10 + 0x90) = 0x11;
      }
    }
    break;
  case 0x11:
    if ((*(int *)(iStack_10 + 0xba4) == 0) && (*(int *)(iStack_10 + 0x870) == 0)) {
      if ((uVar2 & 0x2000) == 0) {
        if ((uVar2 & 0x4000) == 0) {
          if ((uVar9 & 0x50) == 0) {
            mCheckMapView__7solomonFiP12CAnalogStick(iStack_10,uVar5,&uStack_170);
          }
          else {
            uVar7 = play__9primSoundFi(*(undefined4 *)(iStack_10 + 0x74),0);
            uVar7 = getPT__7primWinFi(*(undefined4 *)(iStack_10 + 0x8c),
                                    *(undefined4 *)(iStack_10 + 0x34),iStack_10,uVar7);
            iVar3 = (int)uVar7;
            if ((*(uint *)(iStack_10 + 0x50) & 1 << (*(uint *)(iStack_10 + 0x34) & 0x1f)) == 0) {
              SetCSA__8FontItemFUc(uVar7,2);
              *(undefined1 *)(iVar3 + 0x5c) = 0;
              uVar5 = (ulong)*(byte *)(iVar3 + 0x11) & 0xfffffffffffffffd | 2;
              *(char *)(iVar3 + 0x11) = (char)uVar5;
              *(byte *)(iVar3 + 0x10) =
                   *(byte *)(iVar3 + 0x10) & 0xfd | (byte)((uint)((uVar5 << 0x3e) >> 0x3f) << 1);
              (**(code **)(*(int *)(iVar3 + 8) + 0x30))(uVar7,0x7f,0x7f,0x7f);
            }
            else {
              SetCSA__8FontItemFUc(uVar7,0);
              *(undefined1 *)(iVar3 + 0x5c) = 0;
              uVar5 = (ulong)*(byte *)(iVar3 + 0x11) & 0xfffffffffffffffd | 2;
              *(char *)(iVar3 + 0x11) = (char)uVar5;
              *(byte *)(iVar3 + 0x10) =
                   *(byte *)(iVar3 + 0x10) & 0xfd | (byte)((uint)((uVar5 << 0x3e) >> 0x3f) << 1);
            }
            if ((uVar9 & 0x40) == 0) {
              iVar3 = *(int *)(iStack_10 + 0x34) + -1;
              if (iVar3 < 0) {
                iVar3 = 8;
              }
            }
            else {
              iVar3 = *(int *)(iStack_10 + 0x34) + 1;
              if (8 < iVar3) {
                iVar3 = 0;
              }
            }
            mSetTextScroll__7solomonFi(iStack_10,iVar3);
            *(int *)(iStack_10 + 0xa44) =
                 (int)(char)(&mAreaBasePoint)[*(int *)(iStack_10 + 0x34) * 2];
            *(int *)(iStack_10 + 0xa48) = (int)(char)(&DAT_005543b1)[*(int *)(iStack_10 + 0x34) * 2]
            ;
            iStack_88 = *(int *)(iStack_10 + 0xa44) + *(int *)(iStack_10 + 0xa48) * 9;
            setArea__11solomonAreaFibb
                      (*(undefined4 *)(iStack_10 + 0x6a0),(&DAT_00554458)[iStack_88 * 0xc],
                       *(char *)(iStack_10 + iStack_88 * 6 + 0x4ed) != '\0',0);
            uVar7 = setArea__10solomonThmFi
                              (*(undefined4 *)(iStack_10 + 0x6a4),(&DAT_00554458)[iStack_88 * 0xc]);
            setDemon__10solomonThmFi
                      (*(undefined4 *)(iStack_10 + 0x6a4),0xffffffffffffffff,
                       *(undefined4 *)(iStack_10 + 0x6a4),uVar7);
            mSetWorldScroll__7solomonFv(iStack_10);
          }
        }
        else {
          if (*(int *)(iStack_10 + 0x804) != 0) {
            iStack_120 = *(int *)(iStack_10 + 0x804);
            if (iStack_120 != 0) {
              (**(code **)(*(int *)(iStack_120 + 0x14) + 8))(iStack_120,1);
            }
            *(undefined4 *)(iStack_10 + 0x804) = 0;
          }
          play__9primSoundFi(*(undefined4 *)(iStack_10 + 0x74),3);
          fadeout__7primWinFi(*(undefined4 *)(iStack_10 + 0x8c),0x10);
          mReleaseMainCursor__7solomonFv(iStack_10);
          if (*(int *)(iStack_10 + 0x54) != 0) {
            iStack_124 = *(int *)(iStack_10 + 0x54);
            if (iStack_124 != 0) {
              (**(code **)(*(int *)(iStack_124 + 0x14) + 8))(iStack_124,1);
            }
            *(undefined4 *)(iStack_10 + 0x54) = 0;
          }
          *(undefined4 *)(iStack_10 + 0x90) = 10;
          *(undefined4 *)(iStack_10 + 0x34) = 0;
          setTitle__10solomonThmFi(*(undefined4 *)(iStack_10 + 0x6a4),0);
          setDemon__10solomonThmFi(*(undefined4 *)(iStack_10 + 0x6a4),0xffffffffffffffff);
        }
      }
      else if (*(char *)(iStack_10 + *(int *)(iStack_10 + 0x34) * 2 + 0xb05) == '\0') {
        *(undefined4 *)(iStack_10 + 0xb94) = *(undefined4 *)(iStack_10 + 0x34);
        play__9primSoundFi(*(undefined4 *)(iStack_10 + 0x74),2);
        setTitle__10solomonThmFi(*(undefined4 *)(iStack_10 + 0x6a4),*(int *)(iStack_10 + 0xb94) + 4)
        ;
        fadeout__7primWinFi(*(undefined4 *)(iStack_10 + 0x8c),0x10);
        uVar7 = mReleaseMainCursor__7solomonFv(iStack_10);
        if (*(int *)(iStack_10 + 0x54) != 0) {
          iStack_11c = *(int *)(iStack_10 + 0x54);
          if (iStack_11c != 0) {
            (**(code **)(*(int *)(iStack_11c + 0x14) + 8))(iStack_11c,1,uVar7);
          }
          *(undefined4 *)(iStack_10 + 0x54) = 0;
        }
        *(undefined4 *)(iStack_10 + 0x90) = 0x12;
      }
      else {
        play__9primSoundFi(*(undefined4 *)(iStack_10 + 0x74),4);
      }
    }
    else if (*(int *)(iStack_10 + 0xba4) != 0) {
      *(int *)(iStack_10 + 0xbb0) = *(int *)(iStack_10 + 0xbb0) + *(int *)(iStack_10 + 0xba8);
      for (iStack_84 = 0; iStack_84 < 9; iStack_84 = iStack_84 + 1) {
        iVar3 = getPP__7primWinFi(*(undefined4 *)(iStack_10 + 0x8c),iStack_84);
        (**(code **)(*(int *)(iVar3 + 8) + 0x24))
                  ((float)*(int *)(iStack_10 + 0xbac),
                   (float)(*(int *)(iStack_10 + 0xbb0) + iStack_84 * 0x16));
        iVar3 = getPT__7primWinFi(*(undefined4 *)(iStack_10 + 0x8c),iStack_84);
        (**(code **)(*(int *)(iVar3 + 8) + 0x24))
                  ((float)(*(int *)(iStack_10 + 0xbac) + 0x12),
                   (float)(*(int *)(iStack_10 + 0xbb0) + iStack_84 * 0x16));
      }
      *(int *)(iStack_10 + 0xba4) = *(int *)(iStack_10 + 0xba4) + -1;
    }
    break;
  case 0x12:
    if (*(int *)(iStack_10 + 0x84) == 0) {
      if (*(int *)(iStack_10 + 0x8c) == 0) {
        mSetupDemonWin__7solomonFv(iStack_10);
      }
    }
    else {
      lVar6 = isFade__7primWinFv(*(undefined4 *)(iStack_10 + 0x84));
      if ((lVar6 == 0) &&
         (iStack_c4 = *(int *)(iStack_10 + 0x84), *(char *)(iStack_c4 + 0x102) == '\0')) {
        iStack_128 = __nw__FUi(0x3c);
        if (iStack_128 != 0) {
          iStack_128 = __ct__12udScrollMarkFv(iStack_128);
        }
        *(int *)(iStack_10 + 0x54) = iStack_128;
        initialize__12udScrollMarkFP7primTexiiiii(*(undefined4 *)(iStack_10 + 0x54),m_pPT,0,
                        *(int *)(iStack_10 + 0xacc) + -5,400,0x5a,0xf2);
        select__12udScrollMarkFi(*(undefined4 *)(iStack_10 + 0x54),*(undefined4 *)(iStack_10 + 0xba0));
        iStack_12c = __nw__FUi(0x34);
        if (iStack_12c != 0) {
          iStack_12c = __ct__14pageScrollMarkFv(iStack_12c);
        }
        *(int *)(iStack_10 + 0x804) = iStack_12c;
        initialize__14pageScrollMarkFP7primTexiii
                  (*(undefined4 *)(iStack_10 + 0x804),m_pPT,0,1,
                   *(undefined4 *)(iStack_10 + 0xb98));
        mSetupMainCursor__7solomonFi(iStack_10,2);
        iStack_130 = __nw__FUi(0x10c);
        if (iStack_130 != 0) {
          iStack_130 = __ct__10primCursorFv(iStack_130);
        }
        *(int *)(iStack_10 + 0x30) = iStack_130;
        createCursor__10primCursorFiiii(*(undefined4 *)(iStack_10 + 0x30),1,1,8,1);
        *(undefined4 *)(iStack_10 + 0x90) = 0x13;
      }
    }
    break;
  case 0x13:
    if (*(int *)(iStack_10 + 0x80) == 0) {
      mSetupMessWin__7solomonFPcbi
                (iStack_10,
                 (&solomonMess_demonNote_J)
                 [*(char *)(iStack_10 + *(int *)(iStack_10 + 0x34) * 2 + 0xb04)],0,0);
      iVar3 = Finish__11MenuMessageFv(*(undefined4 *)(iStack_10 + 0x7fc));
    }
    setDisp__14pageScrollMarkFb(*(undefined4 *)(iStack_10 + 0x804),1,iStack_10,iVar3);
    if ((uVar2 & 0x2000) == 0) {
      if ((uVar2 & 0x4000) == 0) {
        if ((uVar2 & 0xc00) == 0) {
          if (*(int *)(iStack_10 + 0x8c) == *(int *)(iStack_10 + 0x84)) {
            if (*(int *)(iStack_10 + 0xba4) == 0) {
              if ((uVar9 & 0x40) == 0) {
                if ((uVar9 & 0x10) != 0) {
                  play__9primSoundFi(*(undefined4 *)(iStack_10 + 0x74),0);
                  uVar7 = getPT__7primWinFi(*(undefined4 *)(iStack_10 + 0x84),
                                          *(undefined4 *)(iStack_10 + 0x34));
                  iVar3 = (int)uVar7;
                  if (*(char *)(iStack_10 + *(int *)(iStack_10 + 0x34) * 2 + 0xb05) == '\0') {
                    SetCSA__8FontItemFUc(uVar7,0);
                    *(undefined1 *)(iVar3 + 0x5c) = 0;
                    uVar9 = (ulong)*(byte *)(iVar3 + 0x11) & 0xfffffffffffffffd | 2;
                    *(char *)(iVar3 + 0x11) = (char)uVar9;
                    *(byte *)(iVar3 + 0x10) =
                         *(byte *)(iVar3 + 0x10) & 0xfd |
                         (byte)((uint)((uVar9 << 0x3e) >> 0x3f) << 1);
                  }
                  else {
                    SetCSA__8FontItemFUc(uVar7,2);
                    *(undefined1 *)(iVar3 + 0x5c) = 0;
                    uVar9 = (ulong)*(byte *)(iVar3 + 0x11) & 0xfffffffffffffffd | 2;
                    *(char *)(iVar3 + 0x11) = (char)uVar9;
                    *(byte *)(iVar3 + 0x10) =
                         *(byte *)(iVar3 + 0x10) & 0xfd |
                         (byte)((uint)((uVar9 << 0x3e) >> 0x3f) << 1);
                    (**(code **)(*(int *)(iVar3 + 8) + 0x30))(uVar7,0x7f,0x7f,0x7f);
                  }
                  iStack_98 = *(int *)(iStack_10 + 0x34) + -1;
                  if (iStack_98 < 0) {
                    iStack_98 = *(int *)(iStack_10 + 0xacc) + -1;
                  }
                  mSetTextScroll__7solomonFi(iStack_10,iStack_98);
                  setDemon__10solomonThmFi
                            (*(undefined4 *)(iStack_10 + 0x6a4),
                             *(undefined1 *)(iStack_10 + *(int *)(iStack_10 + 0x34) * 2 + 0xb04));
                  mReleaseMessWin__7solomonFv(iStack_10);
                  mSetupMessWin__7solomonFPcbi
                            (iStack_10,
                             (&solomonMess_demonNote_J)
                             [*(char *)(iStack_10 + *(int *)(iStack_10 + 0x34) * 2 + 0xb04)],0,0);
                  Finish__11MenuMessageFv(*(undefined4 *)(iStack_10 + 0x7fc));
                }
              }
              else {
                play__9primSoundFi(*(undefined4 *)(iStack_10 + 0x74),0);
                uVar7 = getPT__7primWinFi(*(undefined4 *)(iStack_10 + 0x84),
                                        *(undefined4 *)(iStack_10 + 0x34));
                iVar3 = (int)uVar7;
                if (*(char *)(iStack_10 + *(int *)(iStack_10 + 0x34) * 2 + 0xb05) == '\0') {
                  SetCSA__8FontItemFUc(uVar7,0);
                  *(undefined1 *)(iVar3 + 0x5c) = 0;
                  uVar9 = (ulong)*(byte *)(iVar3 + 0x11) & 0xfffffffffffffffd | 2;
                  *(char *)(iVar3 + 0x11) = (char)uVar9;
                  *(byte *)(iVar3 + 0x10) =
                       *(byte *)(iVar3 + 0x10) & 0xfd | (byte)((uint)((uVar9 << 0x3e) >> 0x3f) << 1)
                  ;
                }
                else {
                  SetCSA__8FontItemFUc(uVar7,2);
                  *(undefined1 *)(iVar3 + 0x5c) = 0;
                  uVar9 = (ulong)*(byte *)(iVar3 + 0x11) & 0xfffffffffffffffd | 2;
                  *(char *)(iVar3 + 0x11) = (char)uVar9;
                  *(byte *)(iVar3 + 0x10) =
                       *(byte *)(iVar3 + 0x10) & 0xfd | (byte)((uint)((uVar9 << 0x3e) >> 0x3f) << 1)
                  ;
                  (**(code **)(*(int *)(iVar3 + 8) + 0x30))(uVar7,0x7f,0x7f,0x7f);
                }
                iStack_94 = *(int *)(iStack_10 + 0x34) + 1;
                if (*(int *)(iStack_10 + 0xacc) <= iStack_94) {
                  iStack_94 = 0;
                }
                mSetTextScroll__7solomonFi(iStack_10,iStack_94);
                setDemon__10solomonThmFi
                          (*(undefined4 *)(iStack_10 + 0x6a4),
                           *(undefined1 *)(iStack_10 + *(int *)(iStack_10 + 0x34) * 2 + 0xb04));
                mReleaseMessWin__7solomonFv(iStack_10);
                mSetupMessWin__7solomonFPcbi
                          (iStack_10,
                           (&solomonMess_demonNote_J)
                           [*(char *)(iStack_10 + *(int *)(iStack_10 + 0x34) * 2 + 0xb04)],0,0);
                Finish__11MenuMessageFv(*(undefined4 *)(iStack_10 + 0x7fc));
              }
            }
            else {
              *(int *)(iStack_10 + 0xbb0) =
                   *(int *)(iStack_10 + 0xbb0) + *(int *)(iStack_10 + 0xba8);
              for (iStack_90 = 0; iStack_90 < *(int *)(iStack_10 + 0xacc); iStack_90 = iStack_90 + 1
                  ) {
                iVar3 = getPP__7primWinFi(*(undefined4 *)(iStack_10 + 0x84),iStack_90);
                (**(code **)(*(int *)(iVar3 + 8) + 0x24))
                          ((float)*(int *)(iStack_10 + 0xbac),
                           (float)(*(int *)(iStack_10 + 0xbb0) + iStack_90 * 0x16));
                iVar3 = getPT__7primWinFi(*(undefined4 *)(iStack_10 + 0x84),iStack_90);
                (**(code **)(*(int *)(iVar3 + 8) + 0x24))
                          ((float)(*(int *)(iStack_10 + 0xbac) + 0x12),
                           (float)(*(int *)(iStack_10 + 0xbb0) + iStack_90 * 0x16));
              }
              *(int *)(iStack_10 + 0xba4) = *(int *)(iStack_10 + 0xba4) + -1;
            }
            mCheckMapView__7solomonFiP12CAnalogStick(iStack_10,uVar5,&uStack_170);
          }
        }
        else if (1 < *(int *)(iStack_10 + 0xb98)) {
          do {
            if ((uVar2 & 0x400) == 0) {
              *(int *)(iStack_10 + 0xb94) = *(int *)(iStack_10 + 0xb94) + 1;
              if (8 < *(int *)(iStack_10 + 0xb94)) {
                *(undefined4 *)(iStack_10 + 0xb94) = 0;
              }
            }
            else {
              *(int *)(iStack_10 + 0xb94) = *(int *)(iStack_10 + 0xb94) + -1;
              if (*(int *)(iStack_10 + 0xb94) < 0) {
                *(undefined4 *)(iStack_10 + 0xb94) = 8;
              }
            }
          } while ((*(uint *)(iStack_10 + 0x50) & 1 << (*(uint *)(iStack_10 + 0xb94) & 0x1f)) == 0);
          play__9primSoundFi(*(undefined4 *)(iStack_10 + 0x74),1);
          if (*(int *)(iStack_10 + 0x808) != 0) {
            iStack_14c = *(int *)(iStack_10 + 0x808);
            if (iStack_14c != 0) {
              (**(code **)(*(int *)(iStack_14c + 0x14) + 8))(iStack_14c,1);
            }
            *(undefined4 *)(iStack_10 + 0x808) = 0;
          }
          if (*(int *)(iStack_10 + 0x54) != 0) {
            iStack_150 = *(int *)(iStack_10 + 0x54);
            if (iStack_150 != 0) {
              (**(code **)(*(int *)(iStack_150 + 0x14) + 8))(iStack_150,1);
            }
            *(undefined4 *)(iStack_10 + 0x54) = 0;
          }
          if (*(int *)(iStack_10 + 0x804) != 0) {
            iStack_154 = *(int *)(iStack_10 + 0x804);
            if (iStack_154 != 0) {
              (**(code **)(*(int *)(iStack_154 + 0x14) + 8))(iStack_154,1);
            }
            *(undefined4 *)(iStack_10 + 0x804) = 0;
          }
          if (*(int *)(iStack_10 + 0x30) != 0) {
            DelayDeleteRequest__10primCursorFv(*(undefined4 *)(iStack_10 + 0x30));
            *(undefined4 *)(iStack_10 + 0x30) = 0;
          }
          fadeout__7primWinFi(*(undefined4 *)(iStack_10 + 0x80),0x10);
          mReleaseMainCursor__7solomonFv(iStack_10);
          setTitle__10solomonThmFi
                    (*(undefined4 *)(iStack_10 + 0x6a4),*(int *)(iStack_10 + 0xb94) + 4);
          fadeout__7primWinFi(*(undefined4 *)(iStack_10 + 0x84),0x10);
          *(int *)(iStack_10 + 0xa44) =
               (int)(char)(&mAreaBasePoint)[*(int *)(iStack_10 + 0xb94) * 2];
          *(int *)(iStack_10 + 0xa48) = (int)(char)(&DAT_005543b1)[*(int *)(iStack_10 + 0xb94) * 2];
          iStack_8c = *(int *)(iStack_10 + 0xa44) + *(int *)(iStack_10 + 0xa48) * 9;
          setArea__11solomonAreaFibb
                    (*(undefined4 *)(iStack_10 + 0x6a0),(&DAT_00554458)[iStack_8c * 0xc],
                     *(char *)(iStack_10 + iStack_8c * 6 + 0x4ed) != '\0',0);
          setArea__10solomonThmFi
                    (*(undefined4 *)(iStack_10 + 0x6a4),(&DAT_00554458)[iStack_8c * 0xc]);
          mSetWorldScroll__7solomonFv(iStack_10);
          *(undefined4 *)(iStack_10 + 0x90) = 0x12;
        }
      }
      else {
        if (*(int *)(iStack_10 + 0x808) != 0) {
          iStack_140 = *(int *)(iStack_10 + 0x808);
          if (iStack_140 != 0) {
            (**(code **)(*(int *)(iStack_140 + 0x14) + 8))(iStack_140,1);
          }
          *(undefined4 *)(iStack_10 + 0x808) = 0;
        }
        if (*(int *)(iStack_10 + 0x54) != 0) {
          iStack_144 = *(int *)(iStack_10 + 0x54);
          if (iStack_144 != 0) {
            (**(code **)(*(int *)(iStack_144 + 0x14) + 8))(iStack_144,1);
          }
          *(undefined4 *)(iStack_10 + 0x54) = 0;
        }
        if (*(int *)(iStack_10 + 0x804) != 0) {
          iStack_148 = *(int *)(iStack_10 + 0x804);
          if (iStack_148 != 0) {
            (**(code **)(*(int *)(iStack_148 + 0x14) + 8))(iStack_148,1);
          }
          *(undefined4 *)(iStack_10 + 0x804) = 0;
        }
        if (*(int *)(iStack_10 + 0x30) != 0) {
          DelayDeleteRequest__10primCursorFv(*(undefined4 *)(iStack_10 + 0x30));
          *(undefined4 *)(iStack_10 + 0x30) = 0;
        }
        fadeout__7primWinFi(*(undefined4 *)(iStack_10 + 0x80),0x10);
        play__9primSoundFi(*(undefined4 *)(iStack_10 + 0x74),3);
        mReleaseMainCursor__7solomonFv(iStack_10);
        setTitle__10solomonThmFi(*(undefined4 *)(iStack_10 + 0x6a4),1);
        fadeout__7primWinFi(*(undefined4 *)(iStack_10 + 0x84),0x10);
        *(undefined4 *)(iStack_10 + 0x90) = 0x10;
      }
    }
    else {
      uVar7 = setDisp__14pageScrollMarkFb(*(undefined4 *)(iStack_10 + 0x804),0);
      cVar1 = *(char *)(iStack_10 + *(int *)(iStack_10 + 0x34) * 2 + 0xb05);
      if (cVar1 == '\0') {
        *(undefined1 *)(iStack_10 + *(int *)(iStack_10 + 0x34) * 2 + 0xb05) = 1;
        uVar7 = mSetDemon__7solomonFi
                          (iStack_10,
                           *(undefined1 *)(iStack_10 + *(int *)(iStack_10 + 0x34) * 2 + 0xb04));
        iVar3 = (char)(&DAT_00554458)[iVar8 * 0xc] * 3;
        mSetFreeSlotScroll__7solomonFi(iStack_10,*(undefined4 *)(iStack_10 + 0x3c),iStack_10,uVar7);
        setRGBA__13solomonCursorFiiii
                  (*(undefined4 *)(iStack_10 + 0x69c),(&mAREACOLORTbl)[iVar3],(&DAT_00554411)[iVar3]
                   ,(&DAT_00554412)[iVar3],0x80);
        if (*(int *)(iStack_10 + 0x808) != 0) {
          iStack_138 = *(int *)(iStack_10 + 0x808);
          if (iStack_138 != 0) {
            (**(code **)(*(int *)(iStack_138 + 0x14) + 8))(iStack_138,1);
          }
          *(undefined4 *)(iStack_10 + 0x808) = 0;
        }
        iStack_13c = __nw__FUi(0x60);
        if (iStack_13c != 0) {
          iStack_13c = __ct__10floatDemonFv(iStack_13c);
        }
        *(int *)(iStack_10 + 0x808) = iStack_13c;
        initialize__10floatDemonFP6MatrixffP9primLayer
                  (0x43800000,0x43600000,*(undefined4 *)(iStack_10 + 0x808),iStack_10 + 0xa80,
                   *(undefined4 *)(iStack_10 + 0x7f8));
        setCursor__10floatDemonFP10primCursor
                  (*(undefined4 *)(iStack_10 + 0x808),*(undefined4 *)(iStack_10 + 0x2c));
        uVar7 = setRGBA__10floatDemonFiiii
                          (*(undefined4 *)(iStack_10 + 0x808),(&mAREACOLORTbl)[iVar3],
                           (&DAT_00554411)[iVar3],(&DAT_00554412)[iVar3],0x80);
        setCurrentDemon__10floatDemonFi
                  (*(undefined4 *)(iStack_10 + 0x808),*(undefined4 *)(iStack_10 + 0x3c),uVar7);
        *(undefined4 *)(iStack_10 + 0x90) = 9;
        *(undefined4 *)(iStack_10 + 3000) = 0x14;
        play__9primSoundFi(*(undefined4 *)(iStack_10 + 0x74),1);
        leaveWin__10primCursorFv(*(undefined4 *)(iStack_10 + 0x2c));
        setCursor__13solomonCursorFP10primCursor
                  (*(undefined4 *)(iStack_10 + 0x69c),*(undefined4 *)(iStack_10 + 0x2c));
      }
      else if (cVar1 == '\x01') {
        play__9primSoundFi(*(undefined4 *)(iStack_10 + 0x74),1,1,1,uVar7);
        if (*(int *)(iStack_10 + 0x808) != 0) {
          iStack_134 = *(int *)(iStack_10 + 0x808);
          if (iStack_134 != 0) {
            (**(code **)(*(int *)(iStack_134 + 0x14) + 8))(iStack_134,1);
          }
          *(undefined4 *)(iStack_10 + 0x808) = 0;
        }
        *(undefined4 *)(iStack_10 + 0x3c) = 0xffffffff;
        *(undefined4 *)(iStack_10 + 0x90) = 0x14;
        mSetSlotScroll__7solomonFi
                  (iStack_10,*(undefined1 *)(iStack_10 + *(int *)(iStack_10 + 0x34) * 2 + 0xb04));
      }
      else if (cVar1 == '\x02') {
        play__9primSoundFi(*(undefined4 *)(iStack_10 + 0x74),4,4,2,uVar7);
      }
    }
    break;
  case 0x14:
    if (*(int *)(iStack_10 + 0x88) == 0) {
      *(undefined4 *)(iStack_10 + 0x38) = 1;
      mSetupQueryWin__7solomonFi(iStack_10,1);
    }
    else {
      lVar6 = isFade__7primWinFv(*(undefined4 *)(iStack_10 + 0x88));
      if (lVar6 == 0) {
        leaveWin__10primCursorFv(*(undefined4 *)(iStack_10 + 0x2c));
        setItem__10primCursorFP7primWini(*(undefined4 *)(iStack_10 + 0x2c),*(undefined4 *)(iStack_10 + 0x88),
                        *(undefined4 *)(iStack_10 + 0x38));
        *(undefined4 *)(iStack_10 + 0x90) = 0x15;
      }
    }
    break;
  case 0x15:
    if ((uVar2 & 0x2000) == 0) {
      if ((uVar2 & 0x4000) == 0) {
        iStack_54 = *(int *)(iStack_10 + 0x38);
        uVar4 = menuCheckKey__7primWinFiP10primCursor(*(undefined4 *)(iStack_10 + 0x8c),uVar5,
                                *(undefined4 *)(iStack_10 + 0x2c));
        *(undefined4 *)(iStack_10 + 0x38) = uVar4;
        if (*(int *)(iStack_10 + 0x38) != iStack_54) {
          play__9primSoundFi(*(undefined4 *)(iStack_10 + 0x74),0);
        }
      }
      else {
        uVar7 = play__9primSoundFi(*(undefined4 *)(iStack_10 + 0x74),3);
        mMakeDemonList__7solomonFv(iStack_10,uVar7);
        leaveWin__10primCursorFv(*(undefined4 *)(iStack_10 + 0x2c));
        setPolyItem__10primCursorFP7primWini(*(undefined4 *)(iStack_10 + 0x2c),*(undefined4 *)(iStack_10 + 0x84),
                        *(undefined4 *)(iStack_10 + 0x34));
        *(undefined4 *)(iStack_10 + 0x90) = 0x13;
        if (*(int *)(iStack_10 + 0x88) != 0) {
          DelayDeleteRequest__7primWinFv(*(undefined4 *)(iStack_10 + 0x88));
          *(undefined4 *)(iStack_10 + 0x88) = 0;
        }
      }
    }
    else {
      uVar7 = play__9primSoundFi(*(undefined4 *)(iStack_10 + 0x74),2);
      if (*(int *)(iStack_10 + 0x38) == 0) {
        *(undefined4 *)(iStack_10 + 0x3c) = 0xffffffff;
        *(char *)(iStack_10 + iVar8 * 6 + 0x4ec) = (char)*(undefined4 *)(iStack_10 + 0x3c);
        uVar4 = setDemon__11solomonSlotFi
                          (*(undefined4 *)(iStack_10 + iVar8 * 4 + 0x3cc),
                           *(undefined4 *)(iStack_10 + 0x3c));
        *(undefined4 *)(iStack_10 + 0x3c) = uVar4;
        if (*(int *)(iStack_10 + 0x3c) != -1) {
          *(int *)(iStack_10 + 0xb00) = *(int *)(iStack_10 + 0xb00) + -1;
        }
        mEraseLine__7solomonFi(iStack_10,iVar8);
        iStack_50 = (char)(&DAT_00554458)[iVar8 * 0xc] * 3;
        if (*(int *)(iStack_10 + 0x80c) != 0) {
          iStack_f4 = *(int *)(iStack_10 + 0x80c);
          if (iStack_f4 != 0) {
            (**(code **)(*(int *)(iStack_f4 + 0x14) + 8))(iStack_f4,1);
          }
          *(undefined4 *)(iStack_10 + 0x80c) = 0;
        }
        iStack_f8 = __nw__FUi(0x60);
        if (iStack_f8 != 0) {
          iStack_f8 = __ct__10floatDemonFv(iStack_f8);
        }
        *(int *)(iStack_10 + 0x80c) = iStack_f8;
        initialize__10floatDemonFP6MatrixffP9primLayer
                  (0x43800000,0x43600000,*(undefined4 *)(iStack_10 + 0x80c),iStack_10 + 0xa80,
                   *(undefined4 *)(iStack_10 + 0x7f8));
        setRGBA__10floatDemonFiiii
                  (*(undefined4 *)(iStack_10 + 0x80c),(&mAREACOLORTbl)[iStack_50],
                   (&DAT_00554411)[iStack_50],(&DAT_00554412)[iStack_50],0x80);
        setCurrentDemon__10floatDemonFi
                  (*(undefined4 *)(iStack_10 + 0x80c),*(undefined4 *)(iStack_10 + 0x3c));
        eraseSlot__10floatDemonFff
                  (*(float *)(iStack_10 + 0x860) +
                   *(float *)(iStack_10 + 0xa54) * (float)*(int *)(&mSlotBaseTbl + iVar8 * 0xc),
                   *(float *)(iStack_10 + 0x864) +
                   *(float *)(iStack_10 + 0xa54) * (float)*(int *)(&DAT_00554454 + iVar8 * 0xc),
                   *(undefined4 *)(iStack_10 + 0x80c));
        mBackDemon__7solomonFi(iStack_10,*(undefined4 *)(iStack_10 + 0x3c));
        uVar7 = 0xffffffffffffffff;
        *(undefined4 *)(iStack_10 + 0x3c) = 0xffffffff;
      }
      mMakeDemonList__7solomonFv(iStack_10,uVar7);
      leaveWin__10primCursorFv(*(undefined4 *)(iStack_10 + 0x2c));
      uVar7 = setPolyItem__10primCursorFP7primWini(*(undefined4 *)(iStack_10 + 0x2c),*(undefined4 *)(iStack_10 + 0x84),
                              *(undefined4 *)(iStack_10 + 0x34));
      *(undefined4 *)(iStack_10 + 0x90) = 0x13;
      if (*(int *)(iStack_10 + 0x88) != 0) {
        DelayDeleteRequest__7primWinFv(*(undefined4 *)(iStack_10 + 0x88),uVar7);
        *(undefined4 *)(iStack_10 + 0x88) = 0;
      }
    }
    break;
  case 0x16:
    if (*(int *)(iStack_10 + 0x88) == 0) {
      *(undefined4 *)(iStack_10 + 0x38) = 1;
      mSetupQueryWin__7solomonFi(iStack_10,2);
    }
    else {
      lVar6 = isFade__7primWinFv(*(undefined4 *)(iStack_10 + 0x88));
      if (lVar6 == 0) {
        removeCursor__13solomonCursorFv(*(undefined4 *)(iStack_10 + 0x69c));
        setItem__10primCursorFP7primWini(*(undefined4 *)(iStack_10 + 0x2c),*(undefined4 *)(iStack_10 + 0x88),
                        *(undefined4 *)(iStack_10 + 0x38));
        *(undefined4 *)(iStack_10 + 0x90) = 0x17;
      }
    }
    break;
  case 0x17:
    if ((uVar2 & 0x2000) == 0) {
      if ((uVar2 & 0x4000) == 0) {
        iStack_5c = *(int *)(iStack_10 + 0x38);
        uVar4 = menuCheckKey__7primWinFiP10primCursor(*(undefined4 *)(iStack_10 + 0x8c),uVar5,
                                *(undefined4 *)(iStack_10 + 0x2c));
        *(undefined4 *)(iStack_10 + 0x38) = uVar4;
        if (*(int *)(iStack_10 + 0x38) != iStack_5c) {
          play__9primSoundFi(*(undefined4 *)(iStack_10 + 0x74),0);
        }
      }
      else {
        play__9primSoundFi(*(undefined4 *)(iStack_10 + 0x74),3);
        leaveWin__10primCursorFv(*(undefined4 *)(iStack_10 + 0x2c));
        setCursor__13solomonCursorFP10primCursor
                  (*(undefined4 *)(iStack_10 + 0x69c),*(undefined4 *)(iStack_10 + 0x2c));
        *(undefined4 *)(iStack_10 + 0x90) = 9;
        if (*(int *)(iStack_10 + 0x88) != 0) {
          DelayDeleteRequest__7primWinFv(*(undefined4 *)(iStack_10 + 0x88));
          *(undefined4 *)(iStack_10 + 0x88) = 0;
        }
      }
    }
    else {
      play__9primSoundFi(*(undefined4 *)(iStack_10 + 0x74),2);
      if (*(int *)(iStack_10 + 0x38) == 0) {
        play__9primSoundFi(*(undefined4 *)(iStack_10 + 0x74),0x1004);
        uStack_58 = *(undefined4 *)(iStack_10 + 0x3c);
        if (*(int *)(iStack_10 + 0x3c) != -1) {
          *(int *)(iStack_10 + 0xb00) = *(int *)(iStack_10 + 0xb00) + 1;
          mSetLine__7solomonFi(iStack_10,iVar8);
        }
        *(char *)(iStack_10 + iVar8 * 6 + 0x4ec) = (char)*(undefined4 *)(iStack_10 + 0x3c);
        uVar4 = setDemon__11solomonSlotFi
                          (*(undefined4 *)(iStack_10 + iVar8 * 4 + 0x3cc),
                           *(undefined4 *)(iStack_10 + 0x3c));
        *(undefined4 *)(iStack_10 + 0x3c) = uVar4;
        if (*(int *)(iStack_10 + 0x3c) != -1) {
          *(int *)(iStack_10 + 0xb00) = *(int *)(iStack_10 + 0xb00) + -1;
        }
        mEraseLine__7solomonFi(iStack_10,iVar8);
        iVar3 = (char)(&DAT_00554458)[iVar8 * 0xc] * 3;
        setRGBA__13solomonCursorFiiii
                  (*(undefined4 *)(iStack_10 + 0x69c),(&mAREACOLORTbl)[iVar3],(&DAT_00554411)[iVar3]
                   ,(&DAT_00554412)[iVar3],0x80);
        setSlot__10floatDemonFv(*(undefined4 *)(iStack_10 + 0x808));
        if (*(int *)(iStack_10 + 0x80c) != 0) {
          iStack_fc = *(int *)(iStack_10 + 0x80c);
          if (iStack_fc != 0) {
            (**(code **)(*(int *)(iStack_fc + 0x14) + 8))(iStack_fc,1);
          }
          *(undefined4 *)(iStack_10 + 0x80c) = 0;
        }
        iStack_100 = __nw__FUi(0x60);
        if (iStack_100 != 0) {
          iStack_100 = __ct__10floatDemonFv(iStack_100);
        }
        *(int *)(iStack_10 + 0x80c) = iStack_100;
        initialize__10floatDemonFP6MatrixffP9primLayer
                  (0x43800000,0x43600000,*(undefined4 *)(iStack_10 + 0x80c),iStack_10 + 0xa80,
                   *(undefined4 *)(iStack_10 + 0x7f8));
        setRGBA__10floatDemonFiiii
                  (*(undefined4 *)(iStack_10 + 0x80c),(&mAREACOLORTbl)[iVar3],(&DAT_00554411)[iVar3]
                   ,(&DAT_00554412)[iVar3],0x80);
        setCurrentDemon__10floatDemonFi
                  (*(undefined4 *)(iStack_10 + 0x80c),*(undefined4 *)(iStack_10 + 0x3c));
        eraseSlot__10floatDemonFff
                  (*(float *)(iStack_10 + 0x860) +
                   *(float *)(iStack_10 + 0xa54) * (float)*(int *)(&mSlotBaseTbl + iVar8 * 0xc),
                   *(float *)(iStack_10 + 0x864) +
                   *(float *)(iStack_10 + 0xa54) * (float)*(int *)(&DAT_00554454 + iVar8 * 0xc),
                   *(undefined4 *)(iStack_10 + 0x80c));
        iStack_b4 = getPT__7primWinFi(*(undefined4 *)(iStack_10 + 0x84),
                                    *(undefined4 *)(iStack_10 + 0x34));
        SetCSA__8FontItemFUc(iStack_b4,1);
        *(undefined1 *)(iStack_b4 + 0x5c) = 0;
        uVar5 = (ulong)*(byte *)(iStack_b4 + 0x11) & 0xfffffffffffffffd | 2;
        *(char *)(iStack_b4 + 0x11) = (char)uVar5;
        *(byte *)(iStack_b4 + 0x10) =
             *(byte *)(iStack_b4 + 0x10) & 0xfd | (byte)((uint)((uVar5 << 0x3e) >> 0x3f) << 1);
        mBackDemon__7solomonFi(iStack_10,*(undefined4 *)(iStack_10 + 0x3c));
        mMakeDemonList__7solomonFv(iStack_10);
        leaveWin__10primCursorFv(*(undefined4 *)(iStack_10 + 0x2c));
        setPolyItem__10primCursorFP7primWini(*(undefined4 *)(iStack_10 + 0x2c),*(undefined4 *)(iStack_10 + 0x84),
                        *(undefined4 *)(iStack_10 + 0x34));
        *(undefined4 *)(iStack_10 + 0x90) = 0x13;
      }
      else {
        play__9primSoundFi(*(undefined4 *)(iStack_10 + 0x74),2);
        uVar7 = leaveWin__10primCursorFv(*(undefined4 *)(iStack_10 + 0x2c));
        setCursor__13solomonCursorFP10primCursor
                  (*(undefined4 *)(iStack_10 + 0x69c),*(undefined4 *)(iStack_10 + 0x2c),iStack_10,
                   *(undefined4 *)(iStack_10 + 0x69c),uVar7);
        *(undefined4 *)(iStack_10 + 0x90) = 9;
      }
      if (*(int *)(iStack_10 + 0x88) != 0) {
        DelayDeleteRequest__7primWinFv(*(undefined4 *)(iStack_10 + 0x88));
        *(undefined4 *)(iStack_10 + 0x88) = 0;
      }
    }
    break;
  case 0x18:
    if (*(int *)(iStack_10 + 0x7c) == 0) {
      if (*(int *)(iStack_10 + 0x8c) == 0) {
        mSetupAreaResetWin__7solomonFv(iStack_10);
      }
    }
    else {
      lVar6 = isFade__7primWinFv(*(undefined4 *)(iStack_10 + 0x8c));
      if (lVar6 == 0) {
        mSetupMainCursor__7solomonFi(iStack_10,2);
        iStack_104 = __nw__FUi(0x3c);
        if (iStack_104 != 0) {
          iStack_104 = __ct__12udScrollMarkFv(iStack_104);
        }
        *(int *)(iStack_10 + 0x54) = iStack_104;
        initialize__12udScrollMarkFP7primTexiiiii(*(undefined4 *)(iStack_10 + 0x54),m_pPT,0,
                        *(int *)(iStack_10 + 0xbc0) + -5,400,0x5a,0xf2);
        select__12udScrollMarkFi(*(undefined4 *)(iStack_10 + 0x54),*(undefined4 *)(iStack_10 + 0xba0));
        mSetupMainCursor__7solomonFi(iStack_10,1);
        *(undefined4 *)(iStack_10 + 0x90) = 0x19;
      }
    }
    break;
  case 0x19:
    if ((*(int *)(iStack_10 + 0xba4) == 0) && (*(int *)(iStack_10 + 0x870) == 0)) {
      if ((uVar2 & 0x2000) == 0) {
        if ((uVar2 & 0x4000) == 0) {
          if (((uVar9 & 0x50) == 0) || (*(int *)(iStack_10 + 0xbc0) < 2)) {
            mCheckMapView__7solomonFiP12CAnalogStick(iStack_10,uVar5,&uStack_170);
          }
          else {
            play__9primSoundFi(*(undefined4 *)(iStack_10 + 0x74),0);
            iStack_b8 = getPT__7primWinFi(*(undefined4 *)(iStack_10 + 0x8c),
                                        *(undefined4 *)(iStack_10 + 0x34));
            SetCSA__8FontItemFUc(iStack_b8,0);
            *(undefined1 *)(iStack_b8 + 0x5c) = 0;
            uVar5 = (ulong)*(byte *)(iStack_b8 + 0x11) & 0xfffffffffffffffd | 2;
            *(char *)(iStack_b8 + 0x11) = (char)uVar5;
            *(byte *)(iStack_b8 + 0x10) =
                 *(byte *)(iStack_b8 + 0x10) & 0xfd | (byte)((uint)((uVar5 << 0x3e) >> 0x3f) << 1);
            if ((uVar9 & 0x40) == 0) {
              iStack_68 = *(int *)(iStack_10 + 0x34) + -1;
              if (iStack_68 < 0) {
                iStack_68 = *(int *)(iStack_10 + 0xbc0) + -1;
              }
            }
            else {
              iStack_68 = *(int *)(iStack_10 + 0x34) + 1;
              if (*(int *)(iStack_10 + 0xbc0) <= iStack_68) {
                iStack_68 = 0;
              }
            }
            mSetTextScroll__7solomonFi(iStack_10,iStack_68);
            iStack_6c = (int)*(char *)(iStack_10 + *(int *)(iStack_10 + 0x34) * 2 + 0xb04);
            *(int *)(iStack_10 + 0xa44) = (int)(char)(&mAreaBasePoint)[iStack_6c * 2];
            *(int *)(iStack_10 + 0xa48) = (int)(char)(&DAT_005543b1)[iStack_6c * 2];
            iStack_70 = *(int *)(iStack_10 + 0xa44) + *(int *)(iStack_10 + 0xa48) * 9;
            setArea__11solomonAreaFibb
                      (*(undefined4 *)(iStack_10 + 0x6a0),(&DAT_00554458)[iStack_70 * 0xc],
                       *(char *)(iStack_10 + iStack_70 * 6 + 0x4ed) != '\0',0);
            mSetWorldScroll__7solomonFv(iStack_10);
          }
        }
        else {
          play__9primSoundFi(*(undefined4 *)(iStack_10 + 0x74),3);
          *(undefined4 *)(iStack_10 + 0x90) = 10;
          iVar3 = iStack_10;
          if (*(int *)(iStack_10 + 0x54) != 0) {
            iStack_10c = *(int *)(iStack_10 + 0x54);
            if (iStack_10c != 0) {
              iVar3 = (**(code **)(*(int *)(iStack_10c + 0x14) + 8))(iStack_10c,1);
            }
            *(undefined4 *)(iStack_10 + 0x54) = 0;
          }
          mReleaseMainCursor__7solomonFv(iStack_10,iVar3);
          uVar7 = setTitle__10solomonThmFi(*(undefined4 *)(iStack_10 + 0x6a4),0);
          fadeout__7primWinFi(*(undefined4 *)(iStack_10 + 0x8c),0x10,uVar7);
          fadeout__7primWinFi(*(undefined4 *)(iStack_10 + 0x80),0x10);
          *(undefined4 *)(iStack_10 + 0x34) = 2;
        }
      }
      else {
        play__9primSoundFi(*(undefined4 *)(iStack_10 + 0x74),2);
        *(undefined4 *)(iStack_10 + 0x90) = 5;
        if (*(int *)(iStack_10 + 0x54) != 0) {
          iStack_108 = *(int *)(iStack_10 + 0x54);
          if (iStack_108 != 0) {
            (**(code **)(*(int *)(iStack_108 + 0x14) + 8))(iStack_108,1);
          }
          *(undefined4 *)(iStack_10 + 0x54) = 0;
        }
        mReleaseMainCursor__7solomonFv(iStack_10);
      }
    }
    else if (*(int *)(iStack_10 + 0xba4) != 0) {
      *(int *)(iStack_10 + 0xbb0) = *(int *)(iStack_10 + 0xbb0) + *(int *)(iStack_10 + 0xba8);
      for (iStack_64 = 0; iStack_64 < *(int *)(iStack_10 + 0xbc0); iStack_64 = iStack_64 + 1) {
        iVar3 = getPP__7primWinFi(*(undefined4 *)(iStack_10 + 0x8c),iStack_64);
        (**(code **)(*(int *)(iVar3 + 8) + 0x24))
                  ((float)*(int *)(iStack_10 + 0xbac),
                   (float)(*(int *)(iStack_10 + 0xbb0) + iStack_64 * 0x16));
        iVar3 = getPT__7primWinFi(*(undefined4 *)(iStack_10 + 0x8c),iStack_64);
        (**(code **)(*(int *)(iVar3 + 8) + 0x24))
                  ((float)(*(int *)(iStack_10 + 0xbac) + 0x12),
                   (float)(*(int *)(iStack_10 + 0xbb0) + iStack_64 * 0x16));
      }
      *(int *)(iStack_10 + 0xba4) = *(int *)(iStack_10 + 0xba4) + -1;
    }
    break;
  case 0x1a:
    lVar6 = isFade__7primWinFv(*(undefined4 *)(iStack_10 + 0x80));
    if (lVar6 == 0) {
      iStack_c8 = *(int *)(iStack_10 + 0x7fc);
      uStack_12 = *(ushort *)(iStack_c8 + 0x76) <= *(ushort *)(iStack_c8 + 0x80);
      if (((bool)uStack_12) && (*(int *)(iStack_10 + 0x850) == 0)) {
        uVar4 = addKeyWait__7primWinFv(*(undefined4 *)(iStack_10 + 0x80));
        *(undefined4 *)(iStack_10 + 0x850) = uVar4;
      }
      if ((uVar2 & 0x2000) != 0) {
        if (*(int *)(iStack_10 + 0x850) == 0) {
          Finish__11MenuMessageFv(*(undefined4 *)(iStack_10 + 0x7fc));
        }
        else {
          if (*(int *)(iStack_10 + 0x3c4) != 0) {
            DelayDeleteRequest__6prim2DFv(*(undefined4 *)(iStack_10 + 0x3c4));
            *(undefined4 *)(iStack_10 + 0x3c4) = 0;
          }
          psStack_158 = (short *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x220);
          psStack_9c = psStack_158;
          lVar6 = mCheckNewMagic__7solomonFv(iStack_10);
          if (lVar6 == 0) {
            if (*psStack_9c == 1) {
              *(undefined1 *)(iStack_10 + 0x890) = 1;
              if (*(int *)(iStack_10 + 0x30) != 0) {
                DelayDeleteRequest__10primCursorFv(*(undefined4 *)(iStack_10 + 0x30));
                *(undefined4 *)(iStack_10 + 0x30) = 0;
              }
              if (*(int *)(iStack_10 + 0x54) != 0) {
                iStack_15c = *(int *)(iStack_10 + 0x54);
                if (iStack_15c != 0) {
                  (**(code **)(*(int *)(iStack_15c + 0x14) + 8))(iStack_15c,1);
                }
                *(undefined4 *)(iStack_10 + 0x54) = 0;
              }
              if (*(int *)(iStack_10 + 0x804) != 0) {
                iStack_160 = *(int *)(iStack_10 + 0x804);
                if (iStack_160 != 0) {
                  (**(code **)(*(int *)(iStack_160 + 0x14) + 8))(iStack_160,1);
                }
                *(undefined4 *)(iStack_10 + 0x804) = 0;
              }
              mReleaseMainCursor__7solomonFv(iStack_10);
              fadeout__7primWinFi(*(undefined4 *)(iStack_10 + 0x80),0x10);
              fadeout__7primWinFi(*(undefined4 *)(iStack_10 + 0x84),0x10);
              *(undefined4 *)(iStack_10 + 0x90) = 0x1b;
              mFadeoutBG__7solomonFv(iStack_10);
            }
            else {
              *(undefined4 *)(iStack_10 + 0x850) = 0;
              setDisp__14pageScrollMarkFb(*(undefined4 *)(iStack_10 + 0x804),1);
              uVar7 = fadeout__7primWinFi(*(undefined4 *)(iStack_10 + 0x80),0x10);
              *(undefined4 *)(iStack_10 + 0x8c) = *(undefined4 *)(iStack_10 + 0x84);
              mMakeDemonList__7solomonFv(iStack_10,uVar7);
              removeCursor__13solomonCursorFv(*(undefined4 *)(iStack_10 + 0x69c));
              uVar7 = setPolyItem__10primCursorFP7primWini(*(undefined4 *)(iStack_10 + 0x2c),
                                      *(undefined4 *)(iStack_10 + 0x84),
                                      *(undefined4 *)(iStack_10 + 0x34));
              *(undefined4 *)(iStack_10 + 0x90) = 0x13;
              setDemon__10solomonThmFi
                        (*(undefined4 *)(iStack_10 + 0x6a4),
                         *(undefined1 *)(iStack_10 + iVar8 * 6 + 0x4ec),uVar7);
            }
          }
          else {
            *(undefined4 *)(iStack_10 + 0x850) = 0;
            mReleaseMessWin__7solomonFv(iStack_10);
            uStack_a0 = GetRegDat__9RegDatApiFiii(0xd,*(undefined1 *)
                                             (iStack_10 + *(int *)(iStack_10 + 0x58) * 6 + 0x4ec),
                                        0xffffffffffffffff);
            uStack_a4 = GetRegDat__9RegDatApiFiii(0xe,*(undefined4 *)(iStack_10 + 100),0xffffffffffffffff);
            if (*(int *)(iStack_10 + 0x60) == 1) {
              sprintf(auStack_570,PTR__5036_00554814,0x55ede8,uStack_a0,0x55edf0,0x55edf8,
                              uStack_a4,0x55edf0);
            }
            else {
              uStack_a8 = GetRegDat__9RegDatApiFiii(0xe,*(undefined4 *)(iStack_10 + 0x68),0xffffffffffffffff);
              sprintf(auStack_570,PTR__5037_00554818,0x55ede8,uStack_a0,0x55edf0,0x55edf8,
                              uStack_a4,0x55edf0);
            }
            mSetupMessWin__7solomonFPcbi(iStack_10,auStack_570,1,0);
            *(int *)(iStack_10 + 0x58) = *(int *)(iStack_10 + 0x58) + 1;
          }
        }
      }
    }
    break;
  case 0x1b:
    lVar6 = isIdle__8primFadeFv(*(int *)(iStack_10 + 0x94) + 0xc);
    if (lVar6 == 0) {
      lVar6 = isFade__8primFadeFv(*(int *)(iStack_10 + 0x94) + 0xc);
      if (lVar6 == 0) {
        start__13solomonEffectFb(*(undefined4 *)(iStack_10 + 0x854),1);
        *(undefined4 *)(iStack_10 + 0x90) = 0x1c;
      }
    }
    else {
      mReleaseBG__7solomonFv(iStack_10);
      mSetupBG__7solomonFv(iStack_10);
    }
    break;
  case 0x1c:
    lVar6 = isFinish__13solomonEffectFv(*(undefined4 *)(iStack_10 + 0x854));
    if (lVar6 != 0) {
      if (*(int *)(iStack_10 + 0x80) == 0) {
        mSetupSolomonMessWin__7solomonFv(iStack_10);
        *(undefined4 *)(iStack_10 + 0x850) = 0;
      }
      else {
        iStack_cc = *(int *)(iStack_10 + 0x7fc);
        uStack_13 = *(ushort *)(iStack_cc + 0x76) <= *(ushort *)(iStack_cc + 0x80);
        if ((bool)uStack_13) {
          if (*(int *)(iStack_10 + 0x850) == 0) {
            uVar4 = addKeyWait__7primWinFv(*(undefined4 *)(iStack_10 + 0x80));
            *(undefined4 *)(iStack_10 + 0x850) = uVar4;
          }
          uVar5 = (ulong)uVar2 & 0x2000;
          if ((uVar2 & 0x2000) != 0) {
            if (*(int *)(iStack_10 + 0x80) != 0) {
              uVar5 = DelayDeleteRequest__7primWinFv(*(undefined4 *)(iStack_10 + 0x80));
              *(undefined4 *)(iStack_10 + 0x80) = 0;
            }
            mFadeoutBG__7solomonFv(iStack_10,uVar5);
            *(undefined4 *)(iStack_10 + 0x90) = 0x1d;
          }
        }
      }
    }
    break;
  case 0x1d:
    lVar6 = isIdle__8primFadeFv(*(int *)(iStack_10 + 0x94) + 0xc);
    if (lVar6 != 0) {
      *(undefined1 *)(iStack_10 + 0x890) = 0;
      mReleaseBG__7solomonFv(iStack_10);
      mSetupBG__7solomonFv(iStack_10);
      *(undefined4 *)(iStack_10 + 0x34) = 0;
      *(undefined4 *)(iStack_10 + 0x90) = 10;
    }
    break;
  case 0x1e:
    mFadeoutBG__7solomonFv(iStack_10);
    *(undefined4 *)(iStack_10 + 0xbc4) = 2;
    (**(code **)(iStack_10 + 0x24))
              (*(undefined4 *)(iStack_10 + 0xbc4),*(undefined4 *)(iStack_10 + 0x28));
    *(undefined4 *)(iStack_10 + 0x90) = 0x1f;
    break;
  case 0x1f:
    if (*(int *)(iStack_10 + 0x94) == 0) {
      *(undefined4 *)(iStack_10 + 0xbc4) = 3;
      (**(code **)(iStack_10 + 0x24))
                (*(undefined4 *)(iStack_10 + 0xbc4),*(undefined4 *)(iStack_10 + 0x28));
      (**(code **)(*(int *)(iStack_10 + 0x20) + 0xc))();
    }
    else {
      lVar6 = isFade__8primFadeFv(*(int *)(iStack_10 + 0x94) + 0xc);
      if (lVar6 == 0) {
        mReleaseBG__7solomonFv(iStack_10);
      }
    }
  }
  mWinPolling__7solomonFv(iStack_10);
  mWorldScroll__7solomonFv(iStack_10);
  uVar7 = mCheckSetDemon__7solomonFv(iStack_10);
  uStack_11 = 0;
  __dt__12CAnalogStickFv(&uStack_170,0xffffffffffffffff,uVar7);
  return uStack_11;
}

/* JP: 0x004f8500  solomon::mSetTextScroll(int)   [mSetTextScroll__7solomonFi]  size=0x368 */
void mSetTextScroll__7solomonFi(int param_1,int param_2)

{
  int iVar1;
  undefined8 uVar2;
  int iVar3;
  int iVar4;
  ulong uVar5;
  int iVar6;
  
  iVar6 = param_2 - *(int *)(param_1 + 0x34);
  if (iVar6 < 1) {
    if (iVar6 < 0) {
      if (iVar6 + *(int *)(param_1 + 0xb9c) < 0) {
        iVar1 = *(int *)(param_1 + 0xb9c);
        *(undefined4 *)(param_1 + 0xba4) = 0xb;
        iVar3 = iVar6 + *(int *)(param_1 + 0xb9c);
        iVar4 = iVar3 * -0x16;
        *(uint *)(param_1 + 0xba8) =
             iVar4 / 0xb + (iVar4 >> 0x1f) + ((iVar3 * -0xb & 0x7fffffffU) >> 0x1e);
        *(int *)(param_1 + 0xba0) = *(int *)(param_1 + 0xba0) + iVar6 + *(int *)(param_1 + 0xb9c);
        *(undefined4 *)(param_1 + 0xb9c) = 0;
        setPolyItem__10primCursorFP7primWini(*(undefined4 *)(param_1 + 0x2c),*(undefined4 *)(param_1 + 0x8c),
                        *(int *)(param_1 + 0x34) - iVar1);
        select__12udScrollMarkFi(*(undefined4 *)(param_1 + 0x54),*(undefined4 *)(param_1 + 0xba0));
      }
      else {
        *(int *)(param_1 + 0xb9c) = *(int *)(param_1 + 0xb9c) + iVar6;
        setPolyItem__10primCursorFP7primWini(*(undefined4 *)(param_1 + 0x2c),*(undefined4 *)(param_1 + 0x8c),param_2);
      }
    }
  }
  else if (iVar6 + *(int *)(param_1 + 0xb9c) < 6) {
    *(int *)(param_1 + 0xb9c) = *(int *)(param_1 + 0xb9c) + iVar6;
    setPolyItem__10primCursorFP7primWini(*(undefined4 *)(param_1 + 0x2c),*(undefined4 *)(param_1 + 0x8c),param_2);
  }
  else {
    iVar1 = *(int *)(param_1 + 0xb9c);
    *(undefined4 *)(param_1 + 0xba4) = 0xb;
    iVar3 = iVar6 + *(int *)(param_1 + 0xb9c) + -5;
    iVar4 = iVar3 * -0x16;
    *(uint *)(param_1 + 0xba8) =
         iVar4 / 0xb + (iVar4 >> 0x1f) + ((iVar3 * -0xb & 0x7fffffffU) >> 0x1e);
    *(int *)(param_1 + 0xba0) = *(int *)(param_1 + 0xba0) + iVar6 + *(int *)(param_1 + 0xb9c) + -5;
    *(undefined4 *)(param_1 + 0xb9c) = 5;
    setPolyItem__10primCursorFP7primWini(*(undefined4 *)(param_1 + 0x2c),*(undefined4 *)(param_1 + 0x8c),
                    (*(int *)(param_1 + 0x34) + 5) - iVar1);
    select__12udScrollMarkFi(*(undefined4 *)(param_1 + 0x54),*(undefined4 *)(param_1 + 0xba0));
  }
  *(int *)(param_1 + 0x34) = param_2;
  uVar2 = getPT__7primWinFi(*(undefined4 *)(param_1 + 0x8c),*(undefined4 *)(param_1 + 0x34));
  SetCSA__8FontItemFUc(uVar2,1);
  iVar6 = (int)uVar2;
  *(undefined1 *)(iVar6 + 0x5c) = 0;
  uVar5 = (ulong)*(byte *)(iVar6 + 0x11) & 0xfffffffffffffffd | 2;
  *(char *)(iVar6 + 0x11) = (char)uVar5;
  *(byte *)(iVar6 + 0x10) =
       *(byte *)(iVar6 + 0x10) & 0xfd | (byte)((uint)((uVar5 << 0x3e) >> 0x3f) << 1);
  if (*(char *)(param_1 + *(int *)(param_1 + 0x34) * 2 + 0xb05) != '\0') {
    (**(code **)(*(int *)(iVar6 + 8) + 0x30))(uVar2,0x40,0x40,0x40);
  }
  return;
}

/* JP: 0x004f8870  solomon::mSetupBG()   [mSetupBG__7solomonFv]  size=0x1340 */
void mSetupBG__7solomonFv(undefined8 param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined8 uVar5;
  long lVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  uint uVar12;
  undefined1 *puVar13;
  undefined1 *puVar14;
  uint uVar15;
  uint uVar16;
  int iVar17;
  ulong uVar18;
  int *piVar19;
  int iVar20;
  float fVar21;
  
  iVar20 = (int)param_1;
  *(undefined4 *)(iVar20 + 0xaf0) = 0;
  *(undefined4 *)(iVar20 + 0xaf4) = 0;
  *(undefined4 *)(iVar20 + 0xaf8) = 0;
  *(undefined4 *)(iVar20 + 0xafc) = 0;
  *(undefined4 *)(iVar20 + 0xa54) = 0x3f800000;
  *(undefined4 *)(iVar20 + 0xa44) = 1;
  *(undefined4 *)(iVar20 + 0xa48) = 2;
  iVar17 = *(int *)(sm_pSubstance__15SaveMenuSection + 0xc);
  iVar3 = ourBtlSaveDat__10BtlSaveSec + (uint)*(byte *)(ourBtlSaveDat__10BtlSaveSec + 2) * 0x200;
  uVar15 = 0;
  for (uVar16 = 0xac; (int)uVar16 < 0xb6; uVar16 = uVar16 + 1) {
    uVar7 = uVar16;
    if ((int)uVar16 < 0) {
      uVar7 = uVar16 + 7;
    }
    uVar12 = uVar16 & 7;
    if (((int)uVar16 < 0) && (uVar12 != 0)) {
      uVar12 = uVar12 - 8;
    }
    if (((uint)*(byte *)(iVar3 + ((int)uVar7 >> 3) + 0x984) & 1 << (uVar12 & 0x1f)) != 0) {
      *(ushort *)(iVar17 + 0x222) = *(ushort *)(iVar17 + 0x222) | (ushort)(1 << (uVar15 & 0x1f));
    }
    uVar15 = uVar15 + 1;
  }
  puVar13 = (undefined1 *)(iVar3 + 0xaa4);
  puVar14 = (undefined1 *)(iVar20 + 0xaf0);
  for (iVar8 = 0; iVar8 < 9; iVar8 = iVar8 + 1) {
    *puVar14 = *puVar13;
    puVar13 = puVar13 + 1;
    puVar14 = puVar14 + 1;
  }
  *(undefined4 *)(iVar20 + 0xb00) = 0;
  *(undefined4 *)(iVar20 + 0xac8) = 0;
  *(undefined4 *)(iVar20 + 0xad0) = 0;
  *(undefined4 *)(iVar20 + 0xac0) = 0;
  *(uint *)(iVar20 + 0xac4) = (uint)*(ushort *)(iVar17 + 0x222);
  *(undefined4 *)(iVar20 + 0xae0) = *(undefined4 *)(iVar20 + 0xaf0);
  *(undefined4 *)(iVar20 + 0xae4) = *(undefined4 *)(iVar20 + 0xaf4);
  *(undefined4 *)(iVar20 + 0xae8) = *(undefined4 *)(iVar20 + 0xaf8);
  *(undefined4 *)(iVar20 + 0xaec) = *(undefined4 *)(iVar20 + 0xafc);
  iVar8 = 0;
  *(undefined4 *)(iVar20 + 0x50) = 0;
  for (iVar3 = 0; iVar3 < 3; iVar3 = iVar3 + 1) {
    for (uVar16 = 0; (int)uVar16 < 0x20; uVar16 = uVar16 + 1) {
      if ((*(uint *)(iVar20 + iVar3 * 4 + 0xaf0) & 1 << (uVar16 & 0x1f)) != 0) {
        *(int *)(iVar20 + 0xac8) = *(int *)(iVar20 + 0xac8) + 1;
        *(uint *)(iVar20 + 0x50) =
             *(uint *)(iVar20 + 0x50) | 1 << ((int)(char)(&mDemonAttr)[iVar8] & 0x1fU);
      }
      iVar8 = iVar8 + 1;
      if (iVar8 == 0x48) break;
    }
    if (iVar8 == 0x48) break;
  }
  *(undefined4 *)(iVar20 + 0xad0) = *(undefined4 *)(iVar20 + 0xac8);
  *(undefined4 *)(iVar20 + 0xb98) = 0;
  for (uVar16 = 0; (int)uVar16 < 9; uVar16 = uVar16 + 1) {
    if ((*(uint *)(iVar20 + 0x50) & 1 << (uVar16 & 0x1f)) != 0) {
      *(int *)(iVar20 + 0xb98) = *(int *)(iVar20 + 0xb98) + 1;
    }
  }
  for (uVar16 = 0; (int)uVar16 < 10; uVar16 = uVar16 + 1) {
    if ((*(uint *)(iVar20 + 0xac4) & 1 << (uVar16 & 0x1f)) != 0) {
      *(int *)(iVar20 + 0xac0) = *(int *)(iVar20 + 0xac0) + 1;
    }
  }
  uVar5 = getData__7primTexFi(m_pPT,0x1c);
  (*(code *)&CreateFont__4FontFiPUc)(3,uVar5);
  lVar6 = __nw__FUi(0x3c);
  uVar4 = 0;
  if (lVar6 != 0) {
    uVar4 = __ct__9primLayerFv(lVar6);
  }
  *(undefined4 *)(iVar20 + 0x7f8) = uVar4;
  initialize__9primLayerFPUci(*(undefined4 *)(iVar20 + 0x7f8),m_pTex,0x10);
  setTex__9primLayerFiii(*(undefined4 *)(iVar20 + 0x7f8),0,0,0);
  setTex__9primLayerFiii(*(undefined4 *)(iVar20 + 0x7f8),1,1,0);
  setTex__9primLayerFiii(*(undefined4 *)(iVar20 + 0x7f8),2,2,0);
  setTex__9primLayerFiii(*(undefined4 *)(iVar20 + 0x7f8),3,3,0);
  setTex__9primLayerFiiiii(*(undefined4 *)(iVar20 + 0x7f8),0xd,7,0x40,0xe,0);
  setTex__9primLayerFiiiii(*(undefined4 *)(iVar20 + 0x7f8),0xe,8,0x28,0x2a,0);
  setTex__9primLayerFiiiii(*(undefined4 *)(iVar20 + 0x7f8),0xf,6,0x18,0x20,0);
  setTex__9primLayerFiii(*(undefined4 *)(iVar20 + 0x7f8),4,0xb,0);
  setTex__9primLayerFiii(*(undefined4 *)(iVar20 + 0x7f8),5,0xc,0);
  setTex__9primLayerFiii(*(undefined4 *)(iVar20 + 0x7f8),6,0xd,0);
  setTex__9primLayerFiii(*(undefined4 *)(iVar20 + 0x7f8),7,0xe,0);
  setTex__9primLayerFiii(*(undefined4 *)(iVar20 + 0x7f8),8,0xf,0);
  setTex__9primLayerFiii(*(undefined4 *)(iVar20 + 0x7f8),9,0x10,0);
  setTex__9primLayerFiii(*(undefined4 *)(iVar20 + 0x7f8),10,0x11,0);
  setTex__9primLayerFiii(*(undefined4 *)(iVar20 + 0x7f8),0xb,0x12,0);
  setTex__9primLayerFiii(*(undefined4 *)(iVar20 + 0x7f8),0xc,0x13,0);
  for (uVar16 = 0; (int)uVar16 < 4; uVar16 = uVar16 + 1) {
    lVar6 = __nw__FUi(0x150);
    uVar4 = 0;
    if (lVar6 != 0) {
      uVar4 = __ct__10primSpriteFb(lVar6,1);
    }
    *(undefined4 *)(iVar20 + uVar16 * 4 + 0x94) = uVar4;
    if ((uVar16 & 2) == 0) {
      iVar3 = 0;
    }
    else {
      iVar3 = 0x1c0;
    }
    if ((uVar16 & 1) == 0) {
      iVar8 = 0;
    }
    else {
      iVar8 = 0x200;
    }
    setDisp__10primPacketFP9primLayeriffff((float)iVar8,(float)iVar3,0x3f800000,0x3f800000,
                    *(undefined4 *)(iVar20 + uVar16 * 4 + 0x94),*(undefined4 *)(iVar20 + 0x7f8),
                    uVar16);
    setParent__10primPacketFP6Matrix(*(undefined4 *)(iVar20 + uVar16 * 4 + 0x94),iVar20 + 0xa80);
    fadein__8primFadeFi(*(int *)(iVar20 + uVar16 * 4 + 0x94) + 0xc,0x10);
  }
  iVar8 = iVar17 + 0x224;
  for (iVar3 = 0; iVar3 < 0x48; iVar3 = iVar3 + 1) {
    if ((*(byte *)(iVar8 + iVar3) & 0x80) != 0) {
      *(int *)(iVar20 + 0xa44) = iVar3 % 9;
      *(int *)(iVar20 + 0xa48) = iVar3 / 9;
      *(byte *)(iVar8 + iVar3) = *(byte *)(iVar8 + iVar3) & 0x7f;
      *(undefined1 *)(iVar20 + 0xbb4) = 0;
    }
    *(char *)(iVar20 + iVar3 * 6 + 0x4ec) = *(char *)(iVar8 + iVar3) + -1;
    *(undefined1 *)(iVar20 + iVar3 * 6 + 0x4ed) = 0;
    *(undefined1 *)(iVar20 + iVar3 * 6 + 0x4ee) = 0xff;
    *(undefined1 *)(iVar20 + iVar3 * 6 + 0x4ef) = 0xff;
    *(undefined1 *)(iVar20 + iVar3 * 6 + 0x4f0) = 0xff;
    *(undefined1 *)(iVar20 + iVar3 * 6 + 0x4f1) = 0xff;
  }
  *(int *)(iVar20 + 0xb94) =
       (int)(char)(&DAT_00554458)[(*(int *)(iVar20 + 0xa44) + *(int *)(iVar20 + 0xa48) * 9) * 0xc];
  lVar6 = __nw__FUi(0x80);
  uVar4 = 0;
  if (lVar6 != 0) {
    uVar4 = __ct__11solomonAreaFv(lVar6);
  }
  *(undefined4 *)(iVar20 + 0x6a0) = uVar4;
  initialize__11solomonAreaFP6MatrixP9primLayerib
            (*(undefined4 *)(iVar20 + 0x6a0),iVar20 + 0xa80,*(undefined4 *)(iVar20 + 0x7f8),
             *(undefined4 *)(iVar20 + 0xb94),0);
  fadein__8primFadeFi(*(int *)(iVar20 + 0x6a0) + 0x18,0x10);
  iVar8 = 0;
  for (iVar3 = 0; iVar3 < 0x48; iVar3 = iVar3 + 1) {
    iVar9 = iVar3 * 0xc;
    piVar19 = (int *)(&mSlotBaseTbl + iVar9);
    iVar2 = (char)(&DAT_00554458)[iVar3 * 0xc] * 3;
    lVar6 = __nw__FUi(0x6c);
    uVar4 = 0;
    if (lVar6 != 0) {
      uVar4 = __ct__11solomonSlotFP9primLayer(lVar6,*(undefined4 *)(iVar20 + 0x7f8));
    }
    *(undefined4 *)(iVar20 + iVar3 * 4 + 0x3cc) = uVar4;
    initialize__11solomonSlotFP6Matrixffb
              ((float)*piVar19,(float)*(int *)(&DAT_00554454 + iVar9),
               *(undefined4 *)(iVar20 + iVar3 * 4 + 0x3cc),iVar20 + 0xa80,0);
    setRGBA__11solomonSlotFiiii
              (*(undefined4 *)(iVar20 + iVar3 * 4 + 0x3cc),(&mAREASLOTCOLORTbl)[iVar2],
               (&DAT_005543f1)[iVar2],(&DAT_005543f2)[iVar2],0x24);
    fadein__11solomonSlotFi(*(undefined4 *)(iVar20 + iVar3 * 4 + 0x3cc),0x10);
    if ((iVar3 % 9 != 0) && ((&DAT_00554458)[iVar9] == (&DAT_00554458)[(iVar3 + -1) * 0xc])) {
      iVar10 = *piVar19 + *(int *)(&mSlotBaseTbl + (iVar3 + -1) * 0xc);
      if (iVar10 < 0) {
        iVar10 = iVar10 + 1;
      }
      iVar11 = *(int *)(&DAT_00554454 + iVar9) + *(int *)(&DAT_00554454 + (iVar3 + -1) * 0xc);
      if (iVar11 < 0) {
        iVar11 = iVar11 + 1;
      }
      lVar6 = __nw__FUi(0x260);
      uVar4 = 0;
      if (lVar6 != 0) {
        uVar4 = __ct__6prim2DFi(lVar6,6);
      }
      *(undefined4 *)(iVar20 + iVar8 * 4 + 0xa4) = uVar4;
      *(undefined4 *)(*(int *)(iVar20 + iVar8 * 4 + 0xa4) + 0x30) = m_pTex;
      setDisp__6prim2DFiffff((float)(iVar10 >> 1),(float)(iVar11 >> 1),0x3f800000,0x3f800000,
                      *(undefined4 *)(iVar20 + iVar8 * 4 + 0xa4),7);
      setCenterMode__6prim2DFi(*(undefined4 *)(iVar20 + iVar8 * 4 + 0xa4),2);
      setUV__6prim2DFiiii(*(undefined4 *)(iVar20 + iVar8 * 4 + 0xa4),1,9,0x78,0x10);
      setSize__6prim2DFii(*(undefined4 *)(iVar20 + iVar8 * 4 + 0xa4),
                      (*piVar19 - *(int *)(&mSlotBaseTbl + (iVar3 + -1) * 0xc)) + -0x28,8);
      fVar21 = (float)atan2f((float)(*(int *)(&DAT_00554454 + iVar9) -
                                             *(int *)(&DAT_00554454 + (iVar3 + -1) * 0xc)),
                                      (float)(*piVar19 -
                                             *(int *)(&mSlotBaseTbl + (iVar3 + -1) * 0xc)));
      setRotOffset__6prim2DFf(-fVar21,*(undefined4 *)(iVar20 + iVar8 * 4 + 0xa4));
      setParent__6prim2DFP6Matrix(*(undefined4 *)(iVar20 + iVar8 * 4 + 0xa4),iVar20 + 0xa80);
      setRGBA__6prim2DFiiii(*(undefined4 *)(iVar20 + iVar8 * 4 + 0xa4),(&mAREASLOTCOLORTbl)[iVar2],
                      (&DAT_005543f1)[iVar2],(&DAT_005543f2)[iVar2],0x24);
      setBlendMode__6prim2DFi(*(undefined4 *)(iVar20 + iVar8 * 4 + 0xa4),1);
      fadein__8primFadeFi(*(int *)(iVar20 + iVar8 * 4 + 0xa4) + 0x20,0x10);
      *(char *)(iVar20 + iVar3 * 6 + 0x4f0) = (char)iVar8;
      *(char *)(iVar20 + (iVar3 + -1) * 6 + 0x4f1) = (char)iVar8;
      iVar8 = iVar8 + 1;
    }
    if ((8 < iVar3) && ((&DAT_00554458)[iVar9] == (&DAT_00554458)[(iVar3 + -9) * 0xc])) {
      iVar10 = *piVar19 + *(int *)(&mSlotBaseTbl + (iVar3 + -9) * 0xc);
      if (iVar10 < 0) {
        iVar10 = iVar10 + 1;
      }
      iVar11 = *(int *)(&DAT_00554454 + iVar9) + *(int *)(&DAT_00554454 + (iVar3 + -9) * 0xc);
      if (iVar11 < 0) {
        iVar11 = iVar11 + 1;
      }
      lVar6 = __nw__FUi(0x260);
      uVar4 = 0;
      if (lVar6 != 0) {
        uVar4 = __ct__6prim2DFi(lVar6,6);
      }
      *(undefined4 *)(iVar20 + iVar8 * 4 + 0xa4) = uVar4;
      *(undefined4 *)(*(int *)(iVar20 + iVar8 * 4 + 0xa4) + 0x30) = m_pTex;
      setDisp__6prim2DFiffff((float)(iVar10 >> 1),(float)(iVar11 >> 1),0x3f800000,0x3f800000,
                      *(undefined4 *)(iVar20 + iVar8 * 4 + 0xa4),7);
      setCenterMode__6prim2DFi(*(undefined4 *)(iVar20 + iVar8 * 4 + 0xa4),2);
      setUV__6prim2DFiiii(*(undefined4 *)(iVar20 + iVar8 * 4 + 0xa4),1,9,0x78,0x10);
      setSize__6prim2DFii(*(undefined4 *)(iVar20 + iVar8 * 4 + 0xa4),
                      (*(int *)(&DAT_00554454 + iVar9) -
                      *(int *)(&DAT_00554454 + (iVar3 + -9) * 0xc)) + -0x28,8);
      fVar21 = (float)atan2f((float)(*(int *)(&DAT_00554454 + iVar9) -
                                             *(int *)(&DAT_00554454 + (iVar3 + -9) * 0xc)),
                                      (float)(*piVar19 -
                                             *(int *)(&mSlotBaseTbl + (iVar3 + -9) * 0xc)));
      setRotOffset__6prim2DFf(-fVar21,*(undefined4 *)(iVar20 + iVar8 * 4 + 0xa4));
      setParent__6prim2DFP6Matrix(*(undefined4 *)(iVar20 + iVar8 * 4 + 0xa4),iVar20 + 0xa80);
      setRGBA__6prim2DFiiii(*(undefined4 *)(iVar20 + iVar8 * 4 + 0xa4),(&mAREASLOTCOLORTbl)[iVar2],
                      (&DAT_005543f1)[iVar2],(&DAT_005543f2)[iVar2],0x24);
      setBlendMode__6prim2DFi(*(undefined4 *)(iVar20 + iVar8 * 4 + 0xa4),1);
      fadein__8primFadeFi(*(int *)(iVar20 + iVar8 * 4 + 0xa4) + 0x20,0x10);
      *(char *)(iVar20 + iVar3 * 6 + 0x4ee) = (char)iVar8;
      *(char *)(iVar20 + (iVar3 + -9) * 6 + 0x4ef) = (char)iVar8;
      iVar8 = iVar8 + 1;
    }
  }
  *(int *)(iVar20 + 0x3c8) = iVar8;
  for (iVar3 = 0; iVar3 < 0x48; iVar3 = iVar3 + 1) {
    cVar1 = *(char *)(iVar20 + iVar3 * 6 + 0x4ec);
    uVar18 = (ulong)cVar1;
    if (uVar18 != 0xffffffffffffffff) {
      *(int *)(iVar20 + 0xb00) = *(int *)(iVar20 + 0xb00) + 1;
      setDemon__11solomonSlotFi(*(undefined4 *)(iVar20 + iVar3 * 4 + 0x3cc),uVar18);
      mSetLine__7solomonFi(param_1,iVar3);
      iVar8 = (int)cVar1;
      if ((long)uVar18 < 0) {
        iVar8 = iVar8 + 0x1f;
      }
      uVar16 = (uint)(uVar18 & 0x1f);
      if (((long)uVar18 < 0) && ((uVar18 & 0x1f) != 0)) {
        uVar16 = uVar16 - 0x20;
      }
      iVar8 = iVar20 + (iVar8 >> 5) * 4;
      *(uint *)(iVar8 + 0xae0) = *(uint *)(iVar8 + 0xae0) & ~(1 << (uVar16 & 0x1f));
      *(int *)(iVar20 + 0xad0) = *(int *)(iVar20 + 0xad0) + -1;
    }
  }
  for (uVar16 = 0; (int)uVar16 < 9; uVar16 = uVar16 + 1) {
    if (((uint)*(ushort *)(iVar17 + 0x220) & 1 << (uVar16 & 0x1f)) != 0) {
      mFixArea__7solomonFi(param_1,uVar16);
    }
  }
  *(undefined4 *)(iVar20 + 0xa50) = 8;
  *(undefined4 *)(iVar20 + 0xa4c) = 9;
  *(undefined4 *)(iVar20 + 0xa70) = 0x3f800000;
  *(undefined4 *)(iVar20 + 0xa74) = 0x3f800000;
  *(undefined4 *)(iVar20 + 0xa78) = 0;
  *(undefined4 *)(iVar20 + 0xa7c) = 0;
  *(undefined4 *)(iVar20 + 0xa60) = 0x43800000;
  *(undefined4 *)(iVar20 + 0xa64) = 0x43600000;
  *(undefined4 *)(iVar20 + 0xa68) = 0x3f800000;
  *(undefined4 *)(iVar20 + 0xa6c) = 0x3f800000;
  *(undefined1 *)(iVar20 + 0x884) = 0;
  if (*(char *)(iVar20 + 0x890) == '\0') {
    if (*(ushort *)(iVar17 + 0x220) == 1) {
      start__13solomonEffectFb(*(undefined4 *)(iVar20 + 0x854),0);
      fadein__13solomonEffectFv(*(undefined4 *)(iVar20 + 0x854));
    }
    lVar6 = __nw__FUi(0x5c);
    uVar4 = 0;
    if (lVar6 != 0) {
      uVar4 = __ct__13solomonCursorFv(lVar6);
    }
    *(undefined4 *)(iVar20 + 0x69c) = uVar4;
    initialize__13solomonCursorFP6MatrixffP9primLayer
              (0x43800000,0x43600000,*(undefined4 *)(iVar20 + 0x69c),iVar20 + 0xa80,
               *(undefined4 *)(iVar20 + 0x7f8));
    iVar17 = *(int *)(iVar20 + 0xa44) + *(int *)(iVar20 + 0xa48) * 9;
    lVar6 = __nw__FUi(0x98);
    uVar4 = 0;
    if (lVar6 != 0) {
      uVar4 = __ct__10solomonThmFv(lVar6);
    }
    *(undefined4 *)(iVar20 + 0x6a4) = uVar4;
    initialize__10solomonThmFP7primTexbii
              (*(undefined4 *)(iVar20 + 0x6a4),m_pPT,*(int *)(iVar20 + 0xa44) < 5,
               (&DAT_00554458)[iVar17 * 0xc],*(undefined1 *)(iVar20 + iVar17 * 6 + 0x4ec));
    setHintData__10solomonThmFii
              (*(undefined4 *)(iVar20 + 0x6a4),*(undefined4 *)(iVar20 + 0xac0),
               *(undefined4 *)(iVar20 + 0xac4));
  }
  else {
    *(undefined4 *)(iVar20 + 0xa44) = 4;
    *(undefined4 *)(iVar20 + 0xa48) = 4;
  }
  mSetWorldPos__7solomonFb(param_1,1);
  return;
}

/* JP: 0x004f9bb0  solomon::mFadeoutBG()   [mFadeoutBG__7solomonFv]  size=0x154 */
void mFadeoutBG__7solomonFv(int param_1)

{
  int iVar1;
  
  for (iVar1 = 0; iVar1 < 4; iVar1 = iVar1 + 1) {
    fadeout__8primFadeFi(*(int *)(param_1 + iVar1 * 4 + 0x94) + 0xc,0x10);
  }
  fadeout__8primFadeFi(*(int *)(param_1 + 0x6a0) + 0x18,0x10);
  for (iVar1 = 0; iVar1 < 0x48; iVar1 = iVar1 + 1) {
    fadeout__11solomonSlotFi(*(undefined4 *)(param_1 + iVar1 * 4 + 0x3cc),0x10);
  }
  for (iVar1 = 0; iVar1 < *(int *)(param_1 + 0x3c8); iVar1 = iVar1 + 1) {
    fadeout__8primFadeFi(*(int *)(param_1 + iVar1 * 4 + 0xa4) + 0x20,0x10);
  }
  if (*(int *)(param_1 + 0x69c) != 0) {
    fadeout__13solomonCursorFv(*(undefined4 *)(param_1 + 0x69c));
  }
  if (*(int *)(param_1 + 0x854) != 0) {
    fadeout__13solomonEffectFv(*(undefined4 *)(param_1 + 0x854));
  }
  return;
}

/* JP: 0x004f9d10  solomon::mReleaseBG()   [mReleaseBG__7solomonFv]  size=0x42c */
void mReleaseBG__7solomonFv(int param_1)

{
  byte *pbVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = *(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x224;
  for (iVar2 = 0; iVar2 < 0x48; iVar2 = iVar2 + 1) {
    *(char *)(iVar3 + iVar2) = *(char *)(param_1 + iVar2 * 6 + 0x4ec) + '\x01';
  }
  pbVar1 = (byte *)(iVar3 + *(int *)(param_1 + 0xa44) + *(int *)(param_1 + 0xa48) * 9);
  *pbVar1 = *pbVar1 | 0x80;
  if (*(int *)(param_1 + 0x6a4) != 0) {
    iVar2 = *(int *)(param_1 + 0x6a4);
    if (iVar2 != 0) {
      (**(code **)(*(int *)(iVar2 + 0x14) + 8))(iVar2,1);
    }
    *(undefined4 *)(param_1 + 0x6a4) = 0;
  }
  if (*(int *)(param_1 + 0x69c) != 0) {
    iVar2 = *(int *)(param_1 + 0x69c);
    if (iVar2 != 0) {
      (**(code **)(*(int *)(iVar2 + 0x14) + 8))(iVar2,1);
    }
    *(undefined4 *)(param_1 + 0x69c) = 0;
  }
  if (*(int *)(param_1 + 0x808) != 0) {
    iVar2 = *(int *)(param_1 + 0x808);
    if (iVar2 != 0) {
      (**(code **)(*(int *)(iVar2 + 0x14) + 8))(iVar2,1);
    }
    *(undefined4 *)(param_1 + 0x808) = 0;
  }
  for (iVar2 = 0; iVar2 < 0x10; iVar2 = iVar2 + 1) {
    if (*(int *)(param_1 + iVar2 * 4 + 0x80c) != 0) {
      iVar3 = *(int *)(param_1 + iVar2 * 4 + 0x80c);
      if (iVar3 != 0) {
        (**(code **)(*(int *)(iVar3 + 0x14) + 8))(iVar3,1);
      }
      *(undefined4 *)(param_1 + iVar2 * 4 + 0x80c) = 0;
    }
  }
  if (*(int *)(param_1 + 0x6a0) != 0) {
    iVar2 = *(int *)(param_1 + 0x6a0);
    if (iVar2 != 0) {
      (**(code **)(*(int *)(iVar2 + 0x14) + 8))(iVar2,1);
    }
    *(undefined4 *)(param_1 + 0x6a0) = 0;
  }
  for (iVar2 = 0; iVar2 < 0x48; iVar2 = iVar2 + 1) {
    if (*(int *)(param_1 + iVar2 * 4 + 0x3cc) != 0) {
      iVar3 = *(int *)(param_1 + iVar2 * 4 + 0x3cc);
      if (iVar3 != 0) {
        (**(code **)(*(int *)(iVar3 + 0x14) + 8))(iVar3,1);
      }
      *(undefined4 *)(param_1 + iVar2 * 4 + 0x3cc) = 0;
    }
  }
  for (iVar2 = 0; iVar2 < *(int *)(param_1 + 0x3c8); iVar2 = iVar2 + 1) {
    if (*(int *)(param_1 + iVar2 * 4 + 0xa4) != 0) {
      DelayDeleteRequest__6prim2DFv(*(undefined4 *)(param_1 + iVar2 * 4 + 0xa4));
      *(undefined4 *)(param_1 + iVar2 * 4 + 0xa4) = 0;
    }
  }
  for (iVar2 = 0; iVar2 < 4; iVar2 = iVar2 + 1) {
    if (*(int *)(param_1 + iVar2 * 4 + 0x94) != 0) {
      DelayDeleteRequest__10primPacketFv(*(undefined4 *)(param_1 + iVar2 * 4 + 0x94));
      *(undefined4 *)(param_1 + iVar2 * 4 + 0x94) = 0;
    }
  }
  if (*(int *)(param_1 + 0x7f8) != 0) {
    DelayDeleteRequest__9primLayerFv(*(undefined4 *)(param_1 + 0x7f8));
    *(undefined4 *)(param_1 + 0x7f8) = 0;
  }
  (*(code *)&ClearFont__4FontFi)(3);
  return;
}

/* JP: 0x004fa140  solomon::mCheckKey(int)   [mCheckKey__7solomonFi]  size=0x3c8 */
void mCheckKey__7solomonFi(int param_1,uint param_2)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  bVar1 = false;
  iVar2 = *(int *)(param_1 + 0xa44);
  iVar3 = *(int *)(param_1 + 0xa48);
  if (*(int *)(param_1 + 0x870) == 0) {
    if (((param_2 & 0x20) == 0) || (*(int *)(param_1 + 0xa4c) + -1 <= iVar2)) {
      if (((param_2 & 0x80) != 0) && (0 < iVar2)) {
        iVar2 = iVar2 + -1;
        bVar1 = true;
      }
    }
    else {
      iVar2 = iVar2 + 1;
      bVar1 = true;
    }
    if (((param_2 & 0x10) == 0) || (iVar3 < 1)) {
      if (((param_2 & 0x40) != 0) && (iVar3 < *(int *)(param_1 + 0xa50) + -1)) {
        iVar3 = iVar3 + 1;
        bVar1 = true;
      }
    }
    else {
      iVar3 = iVar3 + -1;
      bVar1 = true;
    }
    if (bVar1) {
      iVar4 = iVar2 + iVar3 * 9;
      if ((*(int *)(param_1 + 0x3c) == -1) ||
         ((&DAT_00554458)[iVar4 * 0xc] ==
          (&DAT_00554458)[(*(int *)(param_1 + 0xa44) + *(int *)(param_1 + 0xa48) * 9) * 0xc])) {
        play__9primSoundFi(*(undefined4 *)(param_1 + 0x74),0);
        if (*(int *)(param_1 + 0xa44) != iVar2) {
          if (iVar2 == 2) {
            moveRight__10solomonThmFv(*(undefined4 *)(param_1 + 0x6a4));
          }
          else if (iVar2 == 6) {
            moveLeft__10solomonThmFv(*(undefined4 *)(param_1 + 0x6a4));
          }
        }
        if ((*(int *)(param_1 + 0x808) != 0) && (*(int *)(param_1 + 0x2c) != 0)) {
          setCursor__10floatDemonFP10primCursor
                    (*(undefined4 *)(param_1 + 0x808),*(undefined4 *)(param_1 + 0x2c));
        }
        setAlpha__11solomonSlotFi
                  (*(undefined4 *)
                    (param_1 + *(int *)(param_1 + 0xa44) * 4 + *(int *)(param_1 + 0xa48) * 0x24 +
                    0x3cc),0x24);
        setAlpha__11solomonSlotFi(*(undefined4 *)(param_1 + iVar4 * 4 + 0x3cc),0x40);
        *(int *)(param_1 + 0xa44) = iVar2;
        *(int *)(param_1 + 0xa48) = iVar3;
        setArea__11solomonAreaFibb
                  (*(undefined4 *)(param_1 + 0x6a0),(&DAT_00554458)[iVar4 * 0xc],
                   *(char *)(param_1 + iVar4 * 6 + 0x4ed) != '\0',0);
        setArea__10solomonThmFi(*(undefined4 *)(param_1 + 0x6a4),(&DAT_00554458)[iVar4 * 0xc]);
        if (*(int *)(param_1 + 0x3c) == -1) {
          setDemon__10solomonThmFi
                    (*(undefined4 *)(param_1 + 0x6a4),*(undefined1 *)(param_1 + iVar4 * 6 + 0x4ec));
        }
        mSetWorldScroll__7solomonFv(param_1);
      }
      else {
        play__9primSoundFi(*(undefined4 *)(param_1 + 0x74),4);
      }
    }
  }
  return;
}

/* JP: 0x004fa510  solomon::mSetWorldDest()   [mSetWorldDest__7solomonFv]  size=0x12c */
void mSetWorldDest__7solomonFv(int param_1)

{
  float fVar1;
  float fVar2;
  
  fVar1 = *(float *)(param_1 + 0xa54) * 1024.0 - 328.0;
  fVar2 = *(float *)(param_1 + 0xa54) * 896.0 - 328.0;
  if (*(float *)(param_1 + 0x858) < -fVar1) {
    *(float *)(param_1 + 0x858) = -fVar1;
  }
  else if (0.0 < *(float *)(param_1 + 0x858)) {
    *(undefined4 *)(param_1 + 0x858) = 0;
  }
  if (*(float *)(param_1 + 0x85c) < -fVar2) {
    *(float *)(param_1 + 0x85c) = -fVar2;
  }
  else if (8.0 < *(float *)(param_1 + 0x85c)) {
    *(undefined4 *)(param_1 + 0x85c) = 0x41000000;
  }
  return;
}

/* JP: 0x004fa640  solomon::mSetWorldPos(bool)   [mSetWorldPos__7solomonFb]  size=0x194 */
void mSetWorldPos__7solomonFb(int param_1,char param_2)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0xa4;
  if (*(char *)(param_1 + 0x890) != '\0') {
    iVar2 = 0x100;
  }
  *(undefined4 *)(param_1 + 0x870) = 1;
  iVar1 = (*(int *)(param_1 + 0xa44) + *(int *)(param_1 + 0xa48) * *(int *)(param_1 + 0xa4c)) * 0xc;
  if ((param_2 == '\0') && (*(char *)(param_1 + 0x884) != '\0')) {
    *(float *)(param_1 + 0x858) =
         (float)iVar2 + *(float *)(param_1 + 0x888) * *(float *)(param_1 + 0xa54);
    *(float *)(param_1 + 0x85c) =
         (float)iVar2 + *(float *)(param_1 + 0x88c) * *(float *)(param_1 + 0xa54);
  }
  else {
    *(undefined1 *)(param_1 + 0x884) = 0;
    *(float *)(param_1 + 0x858) =
         (float)iVar2 + -(float)*(int *)(&mSlotBaseTbl + iVar1) * *(float *)(param_1 + 0xa54);
    *(float *)(param_1 + 0x85c) =
         (float)iVar2 + -(float)*(int *)(&DAT_00554454 + iVar1) * *(float *)(param_1 + 0xa54);
  }
  mSetWorldDest__7solomonFv(param_1);
  return;
}

/* JP: 0x004fa7e0  solomon::mSetWorldScroll()   [mSetWorldScroll__7solomonFv]  size=0x234 */
void mSetWorldScroll__7solomonFv(int param_1)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = (*(int *)(param_1 + 0xa44) + *(int *)(param_1 + 0xa48) * *(int *)(param_1 + 0xa4c)) * 0xc;
  piVar2 = (int *)(&mSlotBaseTbl + iVar1);
  if (*(char *)(param_1 + 0x890) == '\0') {
    *(float *)(param_1 + 0x858) = -(float)*piVar2 * *(float *)(param_1 + 0xa54) + 164.0;
    *(float *)(param_1 + 0x85c) =
         -(float)*(int *)(&DAT_00554454 + iVar1) * *(float *)(param_1 + 0xa54) + 164.0;
  }
  else {
    *(float *)(param_1 + 0x858) = -(float)*piVar2 * *(float *)(param_1 + 0xa54) + 256.0;
    *(float *)(param_1 + 0x85c) =
         -(float)*(int *)(&DAT_00554454 + iVar1) * *(float *)(param_1 + 0xa54) + 224.0;
  }
  mSetWorldDest__7solomonFv(param_1);
  *(float *)(param_1 + 0x868) = (*(float *)(param_1 + 0x858) - *(float *)(param_1 + 0x860)) / 24.0;
  *(float *)(param_1 + 0x86c) = (*(float *)(param_1 + 0x85c) - *(float *)(param_1 + 0x864)) / 24.0;
  *(undefined4 *)(param_1 + 0x870) = 0x18;
  *(float *)(param_1 + 0x87c) = ((float)*piVar2 - *(float *)(param_1 + 0x874)) / 24.0;
  *(float *)(param_1 + 0x880) =
       ((float)*(int *)(&DAT_00554454 + iVar1) - *(float *)(param_1 + 0x878)) / 24.0;
  *(undefined1 *)(param_1 + 0x884) = 0;
  return;
}

/* JP: 0x004faa20  solomon::mWorldScroll()   [mWorldScroll__7solomonFv]  size=0x194 */
void mWorldScroll__7solomonFv(int param_1)

{
  int iVar1;
  
  if (*(int *)(param_1 + 0x870) != 0) {
    *(int *)(param_1 + 0x870) = *(int *)(param_1 + 0x870) + -1;
    if (*(int *)(param_1 + 0x870) == 0) {
      *(undefined4 *)(param_1 + 0x860) = *(undefined4 *)(param_1 + 0x858);
      *(undefined4 *)(param_1 + 0x864) = *(undefined4 *)(param_1 + 0x85c);
    }
    else {
      *(float *)(param_1 + 0x860) = *(float *)(param_1 + 0x860) + *(float *)(param_1 + 0x868);
      *(float *)(param_1 + 0x864) = *(float *)(param_1 + 0x864) + *(float *)(param_1 + 0x86c);
    }
    if (*(int *)(param_1 + 0x69c) != 0) {
      if (*(int *)(param_1 + 0x870) == 0) {
        iVar1 = (*(int *)(param_1 + 0xa44) + *(int *)(param_1 + 0xa48) * *(int *)(param_1 + 0xa4c))
                * 0xc;
        *(float *)(param_1 + 0x874) = (float)*(int *)(&mSlotBaseTbl + iVar1);
        *(float *)(param_1 + 0x878) = (float)*(int *)(&DAT_00554454 + iVar1);
      }
      else {
        *(float *)(param_1 + 0x874) = *(float *)(param_1 + 0x874) + *(float *)(param_1 + 0x87c);
        *(float *)(param_1 + 0x878) = *(float *)(param_1 + 0x878) + *(float *)(param_1 + 0x880);
      }
    }
  }
  *(undefined4 *)(param_1 + 0xa60) = *(undefined4 *)(param_1 + 0x860);
  *(undefined4 *)(param_1 + 0xa64) = *(undefined4 *)(param_1 + 0x864);
  if (*(int *)(param_1 + 0x69c) != 0) {
    setPos__13solomonCursorFff
              (*(undefined4 *)(param_1 + 0x874),*(undefined4 *)(param_1 + 0x878),
               *(undefined4 *)(param_1 + 0x69c));
  }
  *(int *)(param_1 + 0xab0) = (int)*(undefined8 *)(param_1 + 0xa60);
  *(int *)(param_1 + 0xab4) = (int)((ulong)*(undefined8 *)(param_1 + 0xa60) >> 0x20);
  *(undefined4 *)(param_1 + 0xab8) = *(undefined4 *)(param_1 + 0xa68);
  *(undefined4 *)(param_1 + 0xabc) = *(undefined4 *)(param_1 + 0xa6c);
  *(undefined4 *)(param_1 + 0xa80) = *(undefined4 *)(param_1 + 0xa70);
  *(undefined4 *)(param_1 + 0xa94) = *(undefined4 *)(param_1 + 0xa74);
  *(undefined4 *)(param_1 + 0xaa8) = *(undefined4 *)(param_1 + 0xa70);
  *(undefined4 *)(param_1 + 0xabc) = *(undefined4 *)(param_1 + 0xa74);
  return;
}

/* JP: 0x004fabc0  solomon::mCheckArea(int)   [mCheckArea__7solomonFi]  size=0xd0 */
undefined4 mCheckArea__7solomonFi(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = 0;
  while( true ) {
    if (0x47 < iVar1) {
      return 1;
    }
    if (((long)param_2 == (long)(char)(&DAT_00554458)[iVar1 * 0xc]) &&
       (*(char *)(param_1 + iVar1 * 6 + 0x4ec) != (&DAT_00554459)[iVar1 * 0xc])) break;
    iVar1 = iVar1 + 1;
  }
  return 0;
}

/* JP: 0x004fac90  solomon::mFixArea(int)   [mFixArea__7solomonFi]  size=0x110 */
void mFixArea__7solomonFi(int param_1,uint param_2)

{
  int iVar1;
  ushort *puVar2;
  
  for (iVar1 = 0; iVar1 < 0x48; iVar1 = iVar1 + 1) {
    if ((long)(int)param_2 == (long)(char)(&DAT_00554458)[iVar1 * 0xc]) {
      *(undefined1 *)(param_1 + iVar1 * 6 + 0x4ed) = 1;
      setFixEffect__11solomonSlotFv(*(undefined4 *)(param_1 + iVar1 * 4 + 0x3cc));
      *(int *)(param_1 + 0xb00) = *(int *)(param_1 + 0xb00) + -1;
    }
  }
  puVar2 = (ushort *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x220);
  *puVar2 = *puVar2 | (ushort)(1 << (param_2 & 0x1f));
  *(uint *)(param_1 + 0x5c) = param_2;
  *(undefined4 *)(param_1 + 0x58) = 0;
  return;
}

/* JP: 0x004fada0  solomon::mCheckNewMagic()   [mCheckNewMagic__7solomonFv]  size=0x30c */
undefined4 mCheckNewMagic__7solomonFv(int param_1)

{
  char cVar1;
  int iVar2;
  ulong uVar3;
  uint uVar4;
  ulong uVar5;
  
  do {
    if (0x47 < *(int *)(param_1 + 0x58)) {
      return 0;
    }
    if ((long)*(int *)(param_1 + 0x5c) ==
        (long)(char)(&DAT_00554458)[*(int *)(param_1 + 0x58) * 0xc]) {
      *(undefined4 *)(param_1 + 0x60) = 0;
      iVar2 = GetRegDat__9RegDatApiFiii(0x37,*(undefined1 *)(param_1 + *(int *)(param_1 + 0x58) * 6 + 0x4ec),
                              0xffffffffffffffff);
      if ((*(byte *)(iVar2 + 6) & 1) == 1) {
        *(int *)(param_1 + *(int *)(param_1 + 0x60) * 4 + 100) = (int)*(short *)(iVar2 + 8);
        *(int *)(param_1 + 0x60) = *(int *)(param_1 + 0x60) + 1;
      }
      if (((ulong)*(byte *)(iVar2 + 6) & 3) >> 1 == 1) {
        *(int *)(param_1 + *(int *)(param_1 + 0x60) * 4 + 100) = (int)*(short *)(iVar2 + 10);
        *(int *)(param_1 + 0x60) = *(int *)(param_1 + 0x60) + 1;
      }
      if (((ulong)*(byte *)(iVar2 + 6) & 7) >> 2 == 1) {
        *(int *)(param_1 + *(int *)(param_1 + 0x60) * 4 + 100) = (int)*(short *)(iVar2 + 0xc);
        *(int *)(param_1 + 0x60) = *(int *)(param_1 + 0x60) + 1;
      }
      if (((ulong)*(byte *)(iVar2 + 6) & 0xf) >> 3 == 1) {
        *(int *)(param_1 + *(int *)(param_1 + 0x60) * 4 + 100) = (int)*(short *)(iVar2 + 0xe);
        *(int *)(param_1 + 0x60) = *(int *)(param_1 + 0x60) + 1;
      }
      if (*(int *)(param_1 + 0x60) != 0) {
        cVar1 = *(char *)(param_1 + *(int *)(param_1 + 0x58) * 6 + 0x4ec);
        iVar2 = (int)cVar1;
        if (cVar1 < '\0') {
          iVar2 = iVar2 + 7;
        }
        uVar3 = (ulong)*(char *)(param_1 + *(int *)(param_1 + 0x58) * 6 + 0x4ec);
        uVar5 = uVar3 & 7;
        uVar4 = (uint)uVar5;
        if (((long)uVar3 < 0) && (uVar5 != 0)) {
          uVar4 = uVar4 - 8;
        }
        iVar2 = ourBtlSaveDat__10BtlSaveSec + (uint)*(byte *)(ourBtlSaveDat__10BtlSaveSec + 2) * 0x200 + 0x944 + (iVar2 >> 3);
        *(byte *)(iVar2 + 0x16a) = *(byte *)(iVar2 + 0x16a) | (byte)(1 << (uVar4 & 0x1f));
        return 1;
      }
    }
    *(int *)(param_1 + 0x58) = *(int *)(param_1 + 0x58) + 1;
  } while( true );
}

/* JP: 0x004fb0b0  solomon::mSetupMainWin()   [mSetupMainWin__7solomonFv]  size=0x264 */
void mSetupMainWin__7solomonFv(int param_1)

{
  undefined4 uVar1;
  long lVar2;
  int iVar3;
  ulong uVar4;
  
  uVar4 = 1;
  *(undefined1 *)(param_1 + 0xb05) = 2;
  *(undefined1 *)(param_1 + 0xb07) = 2;
  *(undefined1 *)(param_1 + 0xb09) = 2;
  if (*(int *)(param_1 + 0xb00) != 0) {
    uVar4 = 5;
    *(undefined1 *)(param_1 + 0xb09) = 0;
  }
  if (*(int *)(param_1 + 0xac8) != 0) {
    uVar4 = uVar4 | 1;
    *(undefined1 *)(param_1 + 0xb05) = 0;
  }
  if (*(int *)(param_1 + 0xac0) != 0) {
    uVar4 = uVar4 | 2;
    *(undefined1 *)(param_1 + 0xb07) = 0;
  }
  lVar2 = __nw__FUi(0x148);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = __ct__7primWinFv(lVar2);
  }
  *(undefined4 *)(param_1 + 0x78) = uVar1;
  uVar1 = *(undefined4 *)(param_1 + 0x78);
  initialize__7primWinFP7primTex(uVar1,m_pPT);
  setItem__7primWinFiii(uVar1,3,1,6);
  setTextArea__7primWinFiiib(uVar1,2,0x200,0x180,1);
  for (iVar3 = 0; iVar3 < 3; iVar3 = iVar3 + 1) {
    createText__7primWinFiiiiPciib(uVar1,iVar3,2,0x15c,iVar3 * 0x1a + 0x68,(&solomonMess_mainMenu_J)[iVar3],0,0);
    createText__7primWinFiiiiPciib(uVar1,iVar3 + 3,2,8,0x1a8,(&solomonMess_mainMenuNote_J)[iVar3],0,0);
  }
  setMenuWindow__7primWinFiiiii(uVar1,3,*(undefined4 *)(param_1 + 0x34),0,3,uVar4);
  buildWin__7primWinFiiiiii(uVar1,3,0,0,0,0,0);
  fadein__7primWinFi(*(undefined4 *)(param_1 + 0x78),0x10);
  *(undefined4 *)(param_1 + 0x8c) = uVar1;
  return;
}

/* JP: 0x004fb320  solomon::mReleaseMainWin()   [mReleaseMainWin__7solomonFv]  size=0x48 */
void mReleaseMainWin__7solomonFv(int param_1)

{
  if (*(int *)(param_1 + 0x78) != 0) {
    DelayDeleteRequest__7primWinFv(*(undefined4 *)(param_1 + 0x78));
    *(undefined4 *)(param_1 + 0x78) = 0;
  }
  return;
}

/* JP: 0x004fb370  solomon::mSetupHintWin()   [mSetupHintWin__7solomonFv]  size=0x560 */
void mSetupHintWin__7solomonFv(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  long lVar4;
  undefined8 uVar5;
  ulong uVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  
  *(undefined4 *)(param_1 + 0x34) = 0;
  *(undefined4 *)(param_1 + 0xba0) = 0;
  *(undefined4 *)(param_1 + 0xb9c) = *(undefined4 *)(param_1 + 0x34);
  if (5 < *(int *)(param_1 + 0xb9c)) {
    *(int *)(param_1 + 0xba0) = *(int *)(param_1 + 0xb9c) + -5;
    *(undefined4 *)(param_1 + 0xb9c) = 5;
  }
  *(undefined4 *)(param_1 + 0xbac) = 0;
  *(int *)(param_1 + 0xbb0) = *(int *)(param_1 + 0xba0) * -0x16;
  *(undefined4 *)(param_1 + 0xba4) = 0;
  iVar9 = *(int *)(param_1 + 0xac0);
  lVar4 = __nw__FUi(0x148);
  uVar2 = 0;
  if (lVar4 != 0) {
    uVar2 = __ct__7primWinFv(lVar4);
  }
  *(undefined4 *)(param_1 + 0x7c) = uVar2;
  iVar1 = *(int *)(param_1 + 0x7c);
  initialize__7primWinFP7primTex(iVar1,m_pPT);
  setItem__7primWinFiii(iVar1,3,iVar9,iVar9);
  setMenuTex__7primWinFP11MenuTextureiii(iVar1,0x421698,0,0x10,0x14);
  setTextArea__7primWinFiiib(iVar1,1,0x200,0x180,1);
  iVar7 = 0;
  uVar8 = 0;
  while (iVar7 < iVar9) {
    if ((*(uint *)(param_1 + 0xac4) & 1 << (uVar8 & 0x1f)) != 0) {
      createTexPoly__7primWinFiiiiii(iVar1,iVar7,0,0,(iVar7 - *(int *)(param_1 + 0xba0)) * 0x16,1,2);
      iVar3 = getPP__7primWinFi(iVar1,iVar7);
      *(undefined2 *)(iVar3 + 0x1c) = 1;
      *(short *)(iVar3 + 0x1e) = (short)iVar7;
      *(char *)(param_1 + iVar7 * 2 + 0xb04) = (char)uVar8;
      *(undefined1 *)(param_1 + iVar7 * 2 + 0xb05) = 0;
      uVar2 = GetRegDat__9RegDatApiFiii(10,uVar8 + 0xac,0xffffffffffffffff);
      createText__7primWinFiiiiPciib(iVar1,iVar7,1,0x12,(iVar7 - *(int *)(param_1 + 0xba0)) * 0x16,uVar2,0,0);
      iVar7 = iVar7 + 1;
    }
    uVar8 = uVar8 + 1;
  }
  buildWin__7primWinFiiiiii(iVar1,3,0x15c,0x70,0xe0,0x81,0);
  SetClip__10MenuWindowFUc(iVar1 + 0x3c,1);
  fadein__7primWinFi(iVar1,0x10);
  *(int *)(param_1 + 0x8c) = iVar1;
  if (*(char *)(param_1 + *(int *)(param_1 + 0x34) * 2 + 0xb05) == '\0') {
    uVar5 = getPT__7primWinFi(iVar1,*(undefined4 *)(param_1 + 0x34));
    SetCSA__8FontItemFUc(uVar5,1);
    iVar9 = (int)uVar5;
    *(undefined1 *)(iVar9 + 0x5c) = 0;
    uVar6 = (ulong)*(byte *)(iVar9 + 0x11) & 0xfffffffffffffffd | 2;
    *(char *)(iVar9 + 0x11) = (char)uVar6;
    *(byte *)(iVar9 + 0x10) =
         *(byte *)(iVar9 + 0x10) & 0xfd | (byte)((uint)((uVar6 << 0x3e) >> 0x3f) << 1);
  }
  iVar9 = (int)*(char *)(param_1 + *(int *)(param_1 + 0x34) * 2 + 0xb04);
  *(int *)(param_1 + 0xa44) = (int)(char)(&mAreaBasePoint)[iVar9 * 2];
  *(int *)(param_1 + 0xa48) = (int)(char)(&DAT_005543b1)[iVar9 * 2];
  iVar9 = *(int *)(param_1 + 0xa44) + *(int *)(param_1 + 0xa48) * 9;
  setArea__11solomonAreaFibb
            (*(undefined4 *)(param_1 + 0x6a0),(&DAT_00554458)[iVar9 * 0xc],
             *(char *)(param_1 + iVar9 * 6 + 0x4ed) != '\0',0);
  setArea__10solomonThmFi(*(undefined4 *)(param_1 + 0x6a4),(&DAT_00554458)[iVar9 * 0xc]);
  setDemon__10solomonThmFi(*(undefined4 *)(param_1 + 0x6a4),0xffffffffffffffff);
  mSetWorldScroll__7solomonFv(param_1);
  *(undefined4 *)(param_1 + 0x800) = 0;
  mReleaseMessWin__7solomonFv(param_1);
  mSetupMessWin__7solomonFPcbi
            (param_1,(&solomonMess_hintNote_J)
                     [*(char *)(param_1 + *(int *)(param_1 + 0x34) * 2 + 0xb04)],0,0);
  Finish__11MenuMessageFv(*(undefined4 *)(param_1 + 0x7fc));
  return;
}

/* JP: 0x004fb8d0  solomon::mReleaseHintWin()   [mReleaseHintWin__7solomonFv]  size=0x48 */
void mReleaseHintWin__7solomonFv(int param_1)

{
  if (*(int *)(param_1 + 0x7c) != 0) {
    DelayDeleteRequest__7primWinFv(*(undefined4 *)(param_1 + 0x7c));
    *(undefined4 *)(param_1 + 0x7c) = 0;
  }
  return;
}

/* JP: 0x004fb920  solomon::mSetupAreaResetWin()   [mSetupAreaResetWin__7solomonFv]  size=0x688 */
void mSetupAreaResetWin__7solomonFv(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  long lVar5;
  undefined8 uVar6;
  ulong uVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  
  uVar10 = 0;
  *(undefined4 *)(param_1 + 0xbc0) = 0;
  for (iVar4 = 0; iVar4 < 0x48; iVar4 = iVar4 + 1) {
    if (*(char *)(param_1 + iVar4 * 6 + 0x4ec) != -1) {
      uVar10 = uVar10 | 1 << ((int)(char)(&mDemonAttr)[*(char *)(param_1 + iVar4 * 6 + 0x4ec)] &
                             0x1fU);
    }
  }
  uVar10 = uVar10 & ~(uint)*(ushort *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x220);
  for (uVar9 = 0; (int)uVar9 < 9; uVar9 = uVar9 + 1) {
    if ((uVar10 & 1 << (uVar9 & 0x1f)) != 0) {
      *(int *)(param_1 + 0xbc0) = *(int *)(param_1 + 0xbc0) + 1;
    }
  }
  *(undefined4 *)(param_1 + 0x34) = 0;
  *(undefined4 *)(param_1 + 0xba0) = 0;
  *(undefined4 *)(param_1 + 0xb9c) = *(undefined4 *)(param_1 + 0x34);
  if (5 < *(int *)(param_1 + 0xb9c)) {
    *(int *)(param_1 + 0xba0) = *(int *)(param_1 + 0xb9c) + -5;
    *(undefined4 *)(param_1 + 0xb9c) = 5;
  }
  *(undefined4 *)(param_1 + 0xbac) = 0;
  *(int *)(param_1 + 0xbb0) = *(int *)(param_1 + 0xba0) * -0x16;
  *(undefined4 *)(param_1 + 0xba4) = 0;
  iVar4 = *(int *)(param_1 + 0xbc0);
  lVar5 = __nw__FUi(0x148);
  uVar2 = 0;
  if (lVar5 != 0) {
    uVar2 = __ct__7primWinFv(lVar5);
  }
  *(undefined4 *)(param_1 + 0x7c) = uVar2;
  iVar1 = *(int *)(param_1 + 0x7c);
  initialize__7primWinFP7primTex(iVar1,m_pPT);
  setItem__7primWinFiii(iVar1,3,iVar4,iVar4);
  setTex__7primWinFiiii(iVar1,0x14,0,0x10,0x14);
  setTextArea__7primWinFiiib(iVar1,1,0x200,0x180,1);
  iVar8 = 0;
  uVar9 = 0;
  while (iVar8 < iVar4) {
    if ((uVar10 & 1 << (uVar9 & 0x1f)) != 0) {
      createTexPoly__7primWinFiiiiii(iVar1,iVar8,0,0,(iVar8 - *(int *)(param_1 + 0xba0)) * 0x16,
                      (&mAREAICONTbl)[uVar9 * 2],(&DAT_005543d1)[uVar9 * 2]);
      iVar3 = getPP__7primWinFi(iVar1,iVar8);
      *(undefined2 *)(iVar3 + 0x1c) = 1;
      *(short *)(iVar3 + 0x1e) = (short)iVar8;
      *(char *)(param_1 + iVar8 * 2 + 0xb04) = (char)uVar9;
      *(undefined1 *)(param_1 + iVar8 * 2 + 0xb05) = 0;
      createText__7primWinFiiiiPciib(iVar1,iVar8,1,0x12,(iVar8 - *(int *)(param_1 + 0xba0)) * 0x16,
                      (&solomonMess_areaName_J)[uVar9],0,0);
      iVar8 = iVar8 + 1;
    }
    uVar9 = uVar9 + 1;
  }
  buildWin__7primWinFiiiiii(iVar1,3,0x15c,0x70,0xe0,0x81,0);
  SetClip__10MenuWindowFUc(iVar1 + 0x3c,1);
  fadein__7primWinFi(iVar1,0x10);
  *(int *)(param_1 + 0x8c) = iVar1;
  if (*(char *)(param_1 + *(int *)(param_1 + 0x34) * 2 + 0xb05) == '\0') {
    uVar6 = getPT__7primWinFi(iVar1,*(undefined4 *)(param_1 + 0x34));
    SetCSA__8FontItemFUc(uVar6,1);
    iVar4 = (int)uVar6;
    *(undefined1 *)(iVar4 + 0x5c) = 0;
    uVar7 = (ulong)*(byte *)(iVar4 + 0x11) & 0xfffffffffffffffd | 2;
    *(char *)(iVar4 + 0x11) = (char)uVar7;
    *(byte *)(iVar4 + 0x10) =
         *(byte *)(iVar4 + 0x10) & 0xfd | (byte)((uint)((uVar7 << 0x3e) >> 0x3f) << 1);
  }
  iVar4 = (int)*(char *)(param_1 + *(int *)(param_1 + 0x34) * 2 + 0xb04);
  *(int *)(param_1 + 0xa44) = (int)(char)(&mAreaBasePoint)[iVar4 * 2];
  *(int *)(param_1 + 0xa48) = (int)(char)(&DAT_005543b1)[iVar4 * 2];
  iVar4 = *(int *)(param_1 + 0xa44) + *(int *)(param_1 + 0xa48) * 9;
  setArea__11solomonAreaFibb
            (*(undefined4 *)(param_1 + 0x6a0),(&DAT_00554458)[iVar4 * 0xc],
             *(char *)(param_1 + iVar4 * 6 + 0x4ed) != '\0',0);
  setArea__10solomonThmFi(*(undefined4 *)(param_1 + 0x6a4),(&DAT_00554458)[iVar4 * 0xc]);
  setDemon__10solomonThmFi(*(undefined4 *)(param_1 + 0x6a4),0xffffffffffffffff);
  mSetWorldScroll__7solomonFv(param_1);
  mReleaseMessWin__7solomonFv(param_1);
  mSetupMessWin__7solomonFPcbi(param_1,PTR__5027_005547ec,0,0);
  Finish__11MenuMessageFv(*(undefined4 *)(param_1 + 0x7fc));
  return;
}

/* JP: 0x004fbfb0  solomon::mSetupQueryWin(int)   [mSetupQueryWin__7solomonFi]  size=0x354 */
void mSetupQueryWin__7solomonFi(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  long lVar4;
  undefined8 uVar5;
  int iVar6;
  int iVar7;
  undefined1 auStack_130 [264];
  float fStack_28;
  float fStack_24;
  int iStack_20;
  int iStack_10;
  
  iStack_20 = param_1;
  iStack_10 = param_2;
  lVar4 = __nw__FUi(0x148);
  uVar1 = 0;
  if (lVar4 != 0) {
    uVar1 = __ct__7primWinFv(lVar4);
  }
  *(undefined4 *)(iStack_20 + 0x88) = uVar1;
  uVar1 = *(undefined4 *)(iStack_20 + 0x88);
  initialize__7primWinFP7primTex(uVar1,m_pPT);
  setItem__7primWinFiii(uVar1,2,9,3);
  setTex__7primWinFiiii(uVar1,0x19,0,0,0);
  setTextArea__7primWinFiiib(uVar1,1,0x200,0x80,1);
  createText__7primWinFiiiiPciib(uVar1,0,1,0x38,0x30,solomonMess_query_J,0,0);
  createText__7primWinFiiiiPciib(uVar1,1,1,0x38,0x48,PTR__5029_005547f4,0,0);
  iVar6 = 0x10;
  if (iStack_10 == 2) {
    uVar5 = GetRegDat__9RegDatApiFiii(0xd,*(undefined1 *)
                                 (iStack_20 +
                                  (*(int *)(iStack_20 + 0xa44) + *(int *)(iStack_20 + 0xa48) * 9) *
                                  6 + 0x4ec),0xffffffffffffffff);
    sprintf(auStack_130,(&solomonMess_query_J)[iStack_10 + 2],uVar5);
    createText__7primWinFiiiiPciib(uVar1,2,1,0,0,auStack_130,0,0);
    iVar6 = 0;
  }
  else {
    createText__7primWinFiiiiPciib(uVar1,2,1,0,0,(&solomonMess_query_J)[iStack_10 + 2],0,0);
  }
  iVar2 = getPT__7primWinFi(uVar1,2);
  fStack_28 = *(float *)(iVar2 + 0x2c);
  iVar7 = (int)fStack_28;
  iVar2 = iVar7;
  if (iVar7 < 0) {
    iVar2 = iVar7 + 1;
  }
  fStack_24 = fStack_28;
  iVar3 = getPT__7primWinFi(uVar1,2);
  (**(code **)(*(int *)(iVar3 + 8) + 0x24))(0,(float)iVar6);
  setMenuWindow__7primWinFiiiii(uVar1,2,*(undefined4 *)(iStack_20 + 0x38),0,0xffffffffffffffff,0xffffff);
  buildWin__7primWinFiiiiii(uVar1,3,0x100 - (iVar2 >> 1),0x78,iVar7,0x60,6);
  fadein__7primWinFi(*(undefined4 *)(iStack_20 + 0x88),0x10);
  *(undefined4 *)(iStack_20 + 0x8c) = uVar1;
  return;
}

/* JP: 0x004fc310  solomon::mSetupMessWin(char*, bool, int)   [mSetupMessWin__7solomonFPcbi]  size=0x128 */
void mSetupMessWin__7solomonFPcbi(int param_1,undefined4 param_2,char param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  long lVar3;
  
  lVar3 = __nw__FUi(0x148);
  uVar1 = 0;
  if (lVar3 != 0) {
    uVar1 = __ct__7primWinFv(lVar3);
  }
  *(undefined4 *)(param_1 + 0x80) = uVar1;
  uVar1 = *(undefined4 *)(param_1 + 0x80);
  initialize__7primWinFP7primTex(uVar1,m_pPT);
  setItem__7primWinFiii(uVar1,1,0,1);
  setTextArea__7primWinFiiib(uVar1,0,0x200,0x100,0);
  uVar2 = addMessage__7primWinFiiPcib(uVar1,0,0,param_2,param_4,0);
  *(undefined4 *)(param_1 + 0x7fc) = uVar2;
  buildWin__7primWinFiiiiii(uVar1,3,0x74,0x158,0x170,0x40,0);
  fadein__7primWinFi(*(undefined4 *)(param_1 + 0x80),0x10);
  if (param_3 != '\0') {
    *(undefined4 *)(param_1 + 0x8c) = uVar1;
  }
  return;
}

/* JP: 0x004fc440  solomon::mReleaseMessWin()   [mReleaseMessWin__7solomonFv]  size=0x48 */
void mReleaseMessWin__7solomonFv(int param_1)

{
  if (*(int *)(param_1 + 0x80) != 0) {
    DelayDeleteRequest__7primWinFv(*(undefined4 *)(param_1 + 0x80));
    *(undefined4 *)(param_1 + 0x80) = 0;
  }
  return;
}

/* JP: 0x004fc490  solomon::mSetupSolomonMessWin()   [mSetupSolomonMessWin__7solomonFv]  size=0x10c */
void mSetupSolomonMessWin__7solomonFv(int param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  long lVar3;
  
  lVar3 = __nw__FUi(0x148);
  uVar1 = 0;
  if (lVar3 != 0) {
    uVar1 = __ct__7primWinFv(lVar3);
  }
  *(undefined4 *)(param_1 + 0x80) = uVar1;
  uVar1 = *(undefined4 *)(param_1 + 0x80);
  initialize__7primWinFP7primTex(uVar1,m_pPT);
  setItem__7primWinFiii(uVar1,1,0,1);
  setTextArea__7primWinFiiib(uVar1,0,0x200,0x100,0);
  uVar2 = addMessage__7primWinFiiPcib(uVar1,0,0,solomonMess_solomon_J,0,1);
  *(undefined4 *)(param_1 + 0x7fc) = uVar2;
  buildWin__7primWinFiiiiii(uVar1,3,0x48,0x150,0x170,0x40,6);
  fadein__7primWinFi(*(undefined4 *)(param_1 + 0x80),0x10);
  return;
}

/* JP: 0x004fc5a0  solomon::mSetupDemonMenuWin()   [mSetupDemonMenuWin__7solomonFv]  size=0x55c */
void mSetupDemonMenuWin__7solomonFv(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  long lVar3;
  undefined8 uVar4;
  ulong uVar5;
  uint uVar6;
  int iVar7;
  
  *(undefined4 *)(param_1 + 0x34) = *(undefined4 *)(param_1 + 0xb94);
  *(undefined4 *)(param_1 + 0xba0) = 0;
  *(undefined4 *)(param_1 + 0xb9c) = *(undefined4 *)(param_1 + 0x34);
  if (5 < *(int *)(param_1 + 0xb9c)) {
    *(int *)(param_1 + 0xba0) = *(int *)(param_1 + 0xb9c) + -5;
    *(undefined4 *)(param_1 + 0xb9c) = 5;
  }
  *(undefined4 *)(param_1 + 0xbac) = 0;
  *(int *)(param_1 + 0xbb0) = *(int *)(param_1 + 0xba0) * -0x16;
  *(undefined4 *)(param_1 + 0xba4) = 0;
  lVar3 = __nw__FUi(0x148);
  uVar1 = 0;
  if (lVar3 != 0) {
    uVar1 = __ct__7primWinFv(lVar3);
  }
  *(undefined4 *)(param_1 + 0x7c) = uVar1;
  iVar7 = *(int *)(param_1 + 0x7c);
  initialize__7primWinFP7primTex(iVar7,m_pPT);
  setItem__7primWinFiii(iVar7,3,9,9);
  setTex__7primWinFiiii(iVar7,0x14,0,0x10,0x14);
  setTextArea__7primWinFiiib(iVar7,1,0x200,0x180,1);
  for (uVar6 = 0; (int)uVar6 < 9; uVar6 = uVar6 + 1) {
    createTexPoly__7primWinFiiiiii(iVar7,uVar6,0,0,(uVar6 - *(int *)(param_1 + 0xba0)) * 0x16,
                    (&mAREAICONTbl)[uVar6 * 2],(&DAT_005543d1)[uVar6 * 2]);
    iVar2 = getPP__7primWinFi(iVar7,uVar6);
    *(undefined2 *)(iVar2 + 0x1c) = 1;
    *(short *)(iVar2 + 0x1e) = (short)uVar6;
    uVar4 = 0x20;
    *(undefined1 *)(param_1 + uVar6 * 2 + 0xb05) = 2;
    if ((*(uint *)(param_1 + 0x50) & 1 << (uVar6 & 0x1f)) != 0) {
      *(undefined1 *)(param_1 + uVar6 * 2 + 0xb05) = 0;
      uVar4 = 0;
    }
    createText__7primWinFiiiiPciib(iVar7,uVar6,1,0x12,(uVar6 - *(int *)(param_1 + 0xba0)) * 0x16,
                    (&solomonMess_areaName_J)[uVar6],uVar4,0);
  }
  buildWin__7primWinFiiiiii(iVar7,3,0x15c,0x70,0xe0,0x81,0);
  SetClip__10MenuWindowFUc(iVar7 + 0x3c,1);
  fadein__7primWinFi(iVar7,0x10);
  *(int *)(param_1 + 0x8c) = iVar7;
  uVar4 = getPT__7primWinFi(iVar7,*(undefined4 *)(param_1 + 0x34));
  SetCSA__8FontItemFUc(uVar4,1);
  iVar2 = (int)uVar4;
  *(undefined1 *)(iVar2 + 0x5c) = 0;
  uVar5 = (ulong)*(byte *)(iVar2 + 0x11) & 0xfffffffffffffffd | 2;
  *(char *)(iVar2 + 0x11) = (char)uVar5;
  *(byte *)(iVar2 + 0x10) =
       *(byte *)(iVar2 + 0x10) & 0xfd | (byte)((uint)((uVar5 << 0x3e) >> 0x3f) << 1);
  if (*(char *)(param_1 + *(int *)(param_1 + 0x34) * 2 + 0xb05) != '\0') {
    uVar4 = getPT__7primWinFi(iVar7,*(undefined4 *)(param_1 + 0x34));
    (**(code **)(*(int *)((int)uVar4 + 8) + 0x30))(uVar4,0x40,0x40,0x40);
  }
  *(int *)(param_1 + 0xa44) = (int)(char)(&mAreaBasePoint)[*(int *)(param_1 + 0x34) * 2];
  *(int *)(param_1 + 0xa48) = (int)(char)(&DAT_005543b1)[*(int *)(param_1 + 0x34) * 2];
  iVar7 = *(int *)(param_1 + 0xa44) + *(int *)(param_1 + 0xa48) * 9;
  setArea__11solomonAreaFibb
            (*(undefined4 *)(param_1 + 0x6a0),(&DAT_00554458)[iVar7 * 0xc],
             *(char *)(param_1 + iVar7 * 6 + 0x4ed) != '\0',0);
  setArea__10solomonThmFi(*(undefined4 *)(param_1 + 0x6a4),(&DAT_00554458)[iVar7 * 0xc]);
  setDemon__10solomonThmFi(*(undefined4 *)(param_1 + 0x6a4),0xffffffffffffffff);
  mSetWorldScroll__7solomonFv(param_1);
  return;
}

/* JP: 0x004fcb00  solomon::mSetupDemonWin()   [mSetupDemonWin__7solomonFv]  size=0x75c */
void mSetupDemonWin__7solomonFv(int param_1)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  long lVar5;
  undefined8 uVar6;
  ulong uVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  undefined4 uStack_28;
  
  uVar4 = *(undefined4 *)(param_1 + 0xac8);
  iVar10 = *(int *)(sm_pSubstance__15SaveMenuSection + 0xc);
  lVar5 = __nw__FUi(0x148);
  uVar3 = 0;
  if (lVar5 != 0) {
    uVar3 = __ct__7primWinFv(lVar5);
  }
  *(undefined4 *)(param_1 + 0x84) = uVar3;
  iVar2 = *(int *)(param_1 + 0x84);
  initialize__7primWinFP7primTex(iVar2,m_pPT);
  setItem__7primWinFiii(iVar2,3,uVar4,uVar4);
  setTex__7primWinFiiii(iVar2,0x14,0,0x10,0x14);
  uVar8 = 0;
  iVar11 = 0;
  *(undefined4 *)(param_1 + 0x34) = 0xffffffff;
  iVar9 = 0;
  while( true ) {
    if (((*(uint *)(param_1 + iVar11 * 4 + 0xaf0) & 1 << (uVar8 & 0x1f)) != 0) &&
       (cVar1 = (&mDemonAttr)[uVar8], (int)cVar1 == *(uint *)(param_1 + 0xb94))) {
      *(char *)(param_1 + iVar9 * 2 + 0xb04) = (char)uVar8;
      *(undefined1 *)(param_1 + iVar9 * 2 + 0xb05) = 1;
      if (((uint)*(ushort *)(iVar10 + 0x220) & 1 << ((int)cVar1 & 0x1fU)) == 0) {
        if (((*(uint *)(param_1 + iVar11 * 4 + 0xae0) & 1 << (uVar8 & 0x1f)) != 0) &&
           (*(undefined1 *)(param_1 + iVar9 * 2 + 0xb05) = 0, *(int *)(param_1 + 0x34) == -1)) {
          *(int *)(param_1 + 0x34) = iVar9;
        }
      }
      else {
        *(undefined1 *)(param_1 + iVar9 * 2 + 0xb05) = 2;
      }
      iVar9 = iVar9 + 1;
    }
    uVar8 = uVar8 + 1;
    if (uVar8 == 0x48) break;
    if ((uVar8 & 0x1f) == 0) {
      iVar11 = iVar11 + 1;
    }
  }
  *(int *)(param_1 + 0xacc) = iVar9;
  if (*(int *)(param_1 + 0x34) == -1) {
    *(undefined4 *)(param_1 + 0x34) = 0;
  }
  if (*(int *)(param_1 + 0x34) < 6) {
    *(undefined4 *)(param_1 + 0xba0) = 0;
    *(undefined4 *)(param_1 + 0xb9c) = *(undefined4 *)(param_1 + 0x34);
  }
  else {
    *(undefined4 *)(param_1 + 0xba0) = *(undefined4 *)(param_1 + 0x34);
    *(undefined4 *)(param_1 + 0xb9c) = 0;
    if (*(int *)(param_1 + 0xacc) <= *(int *)(param_1 + 0x34) + 6) {
      *(int *)(param_1 + 0xba0) = *(int *)(param_1 + 0xacc) + -6;
      *(int *)(param_1 + 0xb9c) = 6 - (*(int *)(param_1 + 0xacc) - *(int *)(param_1 + 0x34));
    }
  }
  *(undefined4 *)(param_1 + 0xbac) = 0;
  *(int *)(param_1 + 0xbb0) = *(int *)(param_1 + 0xba0) * -0x16;
  *(undefined4 *)(param_1 + 0xba4) = 0;
  for (iVar10 = 0; iVar10 < *(int *)(param_1 + 0xacc); iVar10 = iVar10 + 1) {
    createTexPoly__7primWinFiiiiii(iVar2,iVar10,0,0,(iVar10 - *(int *)(param_1 + 0xba0)) * 0x16,
                    (&mAREAICONTbl)
                    [(char)(&mDemonAttr)[*(char *)(param_1 + iVar10 * 2 + 0xb04)] * 2],
                    (&DAT_005543d1)
                    [(char)(&mDemonAttr)[*(char *)(param_1 + iVar10 * 2 + 0xb04)] * 2]);
    iVar9 = getPP__7primWinFi(iVar2,iVar10);
    *(undefined2 *)(iVar9 + 0x1c) = 1;
    *(short *)(iVar9 + 0x1e) = (short)iVar10;
  }
  setTextArea__7primWinFiiib(iVar2,2,0x200,0x180,1);
  for (iVar10 = 0; iVar10 < *(int *)(param_1 + 0xacc); iVar10 = iVar10 + 1) {
    uStack_28 = 0;
    if (*(char *)(param_1 + iVar10 * 2 + 0xb05) != '\0') {
      uStack_28 = 0x20;
    }
    uVar4 = GetRegDat__9RegDatApiFiii(0xd,*(undefined1 *)(param_1 + iVar10 * 2 + 0xb04),0xffffffffffffffff);
    createText__7primWinFiiiiPciib(iVar2,iVar10,2,0x12,(iVar10 - *(int *)(param_1 + 0xba0)) * 0x16,uVar4,uStack_28,
                    0);
  }
  uVar6 = getPT__7primWinFi(iVar2,*(undefined4 *)(param_1 + 0x34));
  SetCSA__8FontItemFUc(uVar6,1);
  iVar10 = (int)uVar6;
  *(undefined1 *)(iVar10 + 0x5c) = 0;
  uVar7 = (ulong)*(byte *)(iVar10 + 0x11) & 0xfffffffffffffffd | 2;
  *(char *)(iVar10 + 0x11) = (char)uVar7;
  *(byte *)(iVar10 + 0x10) =
       *(byte *)(iVar10 + 0x10) & 0xfd | (byte)((uint)((uVar7 << 0x3e) >> 0x3f) << 1);
  if (*(char *)(param_1 + *(int *)(param_1 + 0x34) * 2 + 0xb05) != '\0') {
    uVar6 = getPT__7primWinFi(iVar2,*(undefined4 *)(param_1 + 0x34));
    (**(code **)(*(int *)((int)uVar6 + 8) + 0x30))(uVar6,0x40,0x40,0x40);
  }
  buildWin__7primWinFiiiiii(iVar2,3,0x15c,0x70,0xe0,0x81,0);
  SetClip__10MenuWindowFUc(iVar2 + 0x3c,1);
  setDemon__10solomonThmFi
            (*(undefined4 *)(param_1 + 0x6a4),
             *(undefined1 *)(param_1 + *(int *)(param_1 + 0x34) * 2 + 0xb04));
  fadein__7primWinFi(*(undefined4 *)(param_1 + 0x84),0x10);
  *(int *)(param_1 + 0x8c) = iVar2;
  *(undefined4 *)(param_1 + 0x800) = 0;
  mReleaseMessWin__7solomonFv(param_1);
  mSetupMessWin__7solomonFPcbi
            (param_1,(&solomonMess_demonNote_J)
                     [*(char *)(param_1 + *(int *)(param_1 + 0x34) * 2 + 0xb04)],0,0);
  Finish__11MenuMessageFv(*(undefined4 *)(param_1 + 0x7fc));
  return;
}

/* JP: 0x004fd260  solomon::mReleaseDemonWin()   [mReleaseDemonWin__7solomonFv]  size=0x48 */
void mReleaseDemonWin__7solomonFv(int param_1)

{
  if (*(int *)(param_1 + 0x84) != 0) {
    DelayDeleteRequest__7primWinFv(*(undefined4 *)(param_1 + 0x84));
    *(undefined4 *)(param_1 + 0x84) = 0;
  }
  return;
}

/* JP: 0x004fd2b0  solomon::mMakeDemonList()   [mMakeDemonList__7solomonFv]  size=0x630 */
void mMakeDemonList__7solomonFv(int param_1)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  long lVar7;
  undefined8 uVar8;
  ulong uVar9;
  ulong uVar10;
  int iVar11;
  int iVar12;
  
  if (*(int *)(param_1 + 0x84) != 0) {
    DelayDeleteRequest__7primWinFv(*(undefined4 *)(param_1 + 0x84));
    *(undefined4 *)(param_1 + 0x84) = 0;
  }
  iVar12 = *(int *)(param_1 + 0xacc);
  iVar11 = *(int *)(sm_pSubstance__15SaveMenuSection + 0xc);
  lVar7 = __nw__FUi(0x148);
  uVar3 = 0;
  if (lVar7 != 0) {
    uVar3 = __ct__7primWinFv(lVar7);
  }
  *(undefined4 *)(param_1 + 0x84) = uVar3;
  iVar2 = *(int *)(param_1 + 0x84);
  initialize__7primWinFP7primTex(iVar2,m_pPT);
  setItem__7primWinFiii(iVar2,3,iVar12,iVar12);
  setTex__7primWinFiiii(iVar2,0x14,0,0x10,0x14);
  for (iVar6 = 0; iVar6 < iVar12; iVar6 = iVar6 + 1) {
    if (((uint)*(ushort *)(iVar11 + 0x220) & 1 << (*(uint *)(param_1 + 0xb94) & 0x1f)) == 0) {
      cVar1 = *(char *)(param_1 + iVar6 * 2 + 0xb04);
      iVar4 = (int)cVar1;
      if (cVar1 < '\0') {
        iVar4 = iVar4 + 0x1f;
      }
      uVar10 = (ulong)*(char *)(param_1 + iVar6 * 2 + 0xb04);
      uVar9 = uVar10 & 0x1f;
      uVar5 = (uint)uVar9;
      if (((long)uVar10 < 0) && (uVar9 != 0)) {
        uVar5 = uVar5 - 0x20;
      }
      if ((*(uint *)(param_1 + (iVar4 >> 5) * 4 + 0xae0) & 1 << (uVar5 & 0x1f)) == 0) {
        *(undefined1 *)(param_1 + iVar6 * 2 + 0xb05) = 1;
      }
      else {
        *(undefined1 *)(param_1 + iVar6 * 2 + 0xb05) = 0;
      }
    }
    else {
      *(undefined1 *)(param_1 + iVar6 * 2 + 0xb05) = 2;
    }
  }
  if (*(int *)(param_1 + 0x34) < 6) {
    *(undefined4 *)(param_1 + 0xba0) = 0;
    *(undefined4 *)(param_1 + 0xb9c) = *(undefined4 *)(param_1 + 0x34);
  }
  else {
    *(undefined4 *)(param_1 + 0xba0) = *(undefined4 *)(param_1 + 0x34);
    *(undefined4 *)(param_1 + 0xb9c) = 0;
    if (*(int *)(param_1 + 0xacc) <= *(int *)(param_1 + 0x34) + 6) {
      *(int *)(param_1 + 0xba0) = *(int *)(param_1 + 0xacc) + -6;
      *(int *)(param_1 + 0xb9c) = 6 - (*(int *)(param_1 + 0xacc) - *(int *)(param_1 + 0x34));
    }
  }
  *(undefined4 *)(param_1 + 0xbac) = 0;
  *(int *)(param_1 + 0xbb0) = *(int *)(param_1 + 0xba0) * -0x16;
  *(undefined4 *)(param_1 + 0xba4) = 0;
  for (iVar11 = 0; iVar11 < iVar12; iVar11 = iVar11 + 1) {
    createTexPoly__7primWinFiiiiii(iVar2,iVar11,0,0,(iVar11 - *(int *)(param_1 + 0xba0)) * 0x16,
                    (&mAREAICONTbl)
                    [(char)(&mDemonAttr)[*(char *)(param_1 + iVar11 * 2 + 0xb04)] * 2],
                    (&DAT_005543d1)
                    [(char)(&mDemonAttr)[*(char *)(param_1 + iVar11 * 2 + 0xb04)] * 2]);
    iVar6 = getPP__7primWinFi(iVar2,iVar11);
    *(undefined2 *)(iVar6 + 0x1c) = 1;
    *(short *)(iVar6 + 0x1e) = (short)iVar11;
  }
  setTextArea__7primWinFiiib(iVar2,2,0x200,0x180,1);
  for (iVar11 = 0; iVar11 < iVar12; iVar11 = iVar11 + 1) {
    uVar8 = 0;
    if (*(char *)(param_1 + iVar11 * 2 + 0xb05) != '\0') {
      uVar8 = 0x20;
    }
    uVar3 = GetRegDat__9RegDatApiFiii(0xd,*(undefined1 *)(param_1 + iVar11 * 2 + 0xb04),0xffffffffffffffff);
    createText__7primWinFiiiiPciib(iVar2,iVar11,2,0x12,(iVar11 - *(int *)(param_1 + 0xba0)) * 0x16,uVar3,uVar8,0);
  }
  uVar8 = getPT__7primWinFi(iVar2,*(undefined4 *)(param_1 + 0x34));
  SetCSA__8FontItemFUc(uVar8,1);
  iVar12 = (int)uVar8;
  *(undefined1 *)(iVar12 + 0x5c) = 0;
  uVar9 = (ulong)*(byte *)(iVar12 + 0x11) & 0xfffffffffffffffd | 2;
  *(char *)(iVar12 + 0x11) = (char)uVar9;
  *(byte *)(iVar12 + 0x10) =
       *(byte *)(iVar12 + 0x10) & 0xfd | (byte)((uint)((uVar9 << 0x3e) >> 0x3f) << 1);
  if (*(char *)(param_1 + *(int *)(param_1 + 0x34) * 2 + 0xb05) != '\0') {
    uVar8 = getPT__7primWinFi(iVar2,*(undefined4 *)(param_1 + 0x34));
    (**(code **)(*(int *)((int)uVar8 + 8) + 0x30))(uVar8,0x40,0x40,0x40);
  }
  buildWin__7primWinFiiiiii(iVar2,3,0x15c,0x70,0xe0,0x81,0);
  SetClip__10MenuWindowFUc(iVar2 + 0x3c,1);
  *(int *)(param_1 + 0x8c) = iVar2;
  select__12udScrollMarkFi(*(undefined4 *)(param_1 + 0x54),*(undefined4 *)(param_1 + 0xba0));
  return;
}

/* JP: 0x004fd8e0  solomon::mSetupMainCursor(int)   [mSetupMainCursor__7solomonFi]  size=0x104 */
void mSetupMainCursor__7solomonFi(int param_1,int param_2)

{
  undefined4 uVar1;
  long lVar2;
  
  if (*(int *)(param_1 + 0x2c) == 0) {
    lVar2 = __nw__FUi(0x10c);
    uVar1 = 0;
    if (lVar2 != 0) {
      uVar1 = __ct__10primCursorFv(lVar2);
    }
    *(undefined4 *)(param_1 + 0x2c) = uVar1;
    createCursor__10primCursorFiiii(*(undefined4 *)(param_1 + 0x2c),0,2,8,10);
    if (param_2 == 1) {
      setItem__10primCursorFP7primWini(*(undefined4 *)(param_1 + 0x2c),*(undefined4 *)(param_1 + 0x8c),
                      *(undefined4 *)(param_1 + 0x34));
    }
    else if (param_2 == 2) {
      setPolyItem__10primCursorFP7primWini(*(undefined4 *)(param_1 + 0x2c),*(undefined4 *)(param_1 + 0x8c),
                      *(undefined4 *)(param_1 + 0x34));
    }
    qMove__10primCursorFv(*(undefined4 *)(param_1 + 0x2c));
  }
  return;
}

/* JP: 0x004fd9f0  solomon::mReleaseMainCursor()   [mReleaseMainCursor__7solomonFv]  size=0x48 */
void mReleaseMainCursor__7solomonFv(int param_1)

{
  if (*(int *)(param_1 + 0x2c) != 0) {
    DelayDeleteRequest__10primCursorFv(*(undefined4 *)(param_1 + 0x2c));
    *(undefined4 *)(param_1 + 0x2c) = 0;
  }
  return;
}

/* JP: 0x004fda40  solomon::mSetDemon(int)   [mSetDemon__7solomonFi]  size=0xc0 */
void mSetDemon__7solomonFi(int param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  
  uVar1 = param_2;
  if ((int)param_2 < 0) {
    uVar1 = param_2 + 0x1f;
  }
  uVar3 = param_2 & 0x1f;
  if (((int)param_2 < 0) && (uVar3 != 0)) {
    uVar3 = uVar3 - 0x20;
  }
  iVar2 = param_1 + ((int)uVar1 >> 5) * 4;
  *(uint *)(iVar2 + 0xae0) = *(uint *)(iVar2 + 0xae0) & ~(1 << (uVar3 & 0x1f));
  *(int *)(param_1 + 0xad0) = *(int *)(param_1 + 0xad0) + -1;
  *(uint *)(param_1 + 0x3c) = param_2;
  setDemon__10solomonThmFi(*(undefined4 *)(param_1 + 0x6a4),param_2);
  return;
}

/* JP: 0x004fdb00  solomon::mBackDemon(int)   [mBackDemon__7solomonFi]  size=0x94 */
void mBackDemon__7solomonFi(int param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  
  uVar1 = param_2;
  if ((int)param_2 < 0) {
    uVar1 = param_2 + 0x1f;
  }
  uVar3 = param_2 & 0x1f;
  if (((int)param_2 < 0) && (uVar3 != 0)) {
    uVar3 = uVar3 - 0x20;
  }
  iVar2 = param_1 + ((int)uVar1 >> 5) * 4;
  *(uint *)(iVar2 + 0xae0) = *(uint *)(iVar2 + 0xae0) | 1 << (uVar3 & 0x1f);
  *(int *)(param_1 + 0xad0) = *(int *)(param_1 + 0xad0) + 1;
  return;
}

/* JP: 0x004fdba0  solomon::mSetSlotScroll(int)   [mSetSlotScroll__7solomonFi]  size=0xd4 */
void mSetSlotScroll__7solomonFi(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = 0;
  while( true ) {
    if (0x47 < iVar1) {
      return;
    }
    if ((long)param_2 == (long)*(char *)(param_1 + iVar1 * 6 + 0x4ec)) break;
    iVar1 = iVar1 + 1;
  }
  *(int *)(param_1 + 0xa44) = iVar1 % 9;
  *(int *)(param_1 + 0xa48) = iVar1 / 9;
  mSetWorldScroll__7solomonFv(param_1);
  return;
}

/* JP: 0x004fdc80  solomon::mSetFreeSlotScroll(int)   [mSetFreeSlotScroll__7solomonFi]  size=0x74 */
void mSetFreeSlotScroll__7solomonFi(undefined4 param_1)

{
  mSetWorldScroll__7solomonFv(param_1);
  return;
}

/* JP: 0x004fdd00  solomon::mCheckMapView(int, CAnalogStick*)   [mCheckMapView__7solomonFiP12CAnalogStick]  size=0x2b0 */
void mCheckMapView__7solomonFiP12CAnalogStick(undefined8 param_1,ulong param_2,byte *param_3)

{
  int iVar1;
  float fVar2;
  float fVar3;
  
  iVar1 = (int)param_1;
  if (*(int *)(iVar1 + 0x870) == 0) {
    if ((param_2 & 0x200) == 0) {
      if ((param_2 & 0x100) != 0) {
        if (*(float *)(iVar1 + 0xa54) < 2.0) {
          *(float *)(iVar1 + 0xa54) = *(float *)(iVar1 + 0xa54) + 0.01;
        }
        *(undefined4 *)(iVar1 + 0xa70) = *(undefined4 *)(iVar1 + 0xa54);
        *(undefined4 *)(iVar1 + 0xa74) = *(undefined4 *)(iVar1 + 0xa54);
        *(undefined4 *)(iVar1 + 0xa78) = 0;
        *(undefined4 *)(iVar1 + 0xa7c) = 0;
        mSetWorldPos__7solomonFb(param_1,0);
      }
    }
    else {
      if (0.5 < *(float *)(iVar1 + 0xa54)) {
        *(float *)(iVar1 + 0xa54) = *(float *)(iVar1 + 0xa54) - 0.01;
      }
      *(undefined4 *)(iVar1 + 0xa70) = *(undefined4 *)(iVar1 + 0xa54);
      *(undefined4 *)(iVar1 + 0xa74) = *(undefined4 *)(iVar1 + 0xa54);
      *(undefined4 *)(iVar1 + 0xa78) = 0;
      *(undefined4 *)(iVar1 + 0xa7c) = 0;
      mSetWorldPos__7solomonFb(param_1,0);
    }
    fVar2 = (float)(int)((uint)param_3[2] - (uint)param_3[3]) / 16.0;
    fVar3 = (float)(int)((uint)*param_3 - (uint)param_3[1]) / 16.0;
    if ((fVar2 != 0.0) || (fVar3 != 0.0)) {
      *(undefined1 *)(iVar1 + 0x884) = 1;
      *(float *)(iVar1 + 0x888) =
           fVar2 + (*(float *)(iVar1 + 0x860) - 164.0) / *(float *)(iVar1 + 0xa54);
      *(float *)(iVar1 + 0x88c) =
           fVar3 + (*(float *)(iVar1 + 0x864) - 164.0) / *(float *)(iVar1 + 0xa54);
      *(float *)(iVar1 + 0x858) = *(float *)(iVar1 + 0x888) * *(float *)(iVar1 + 0xa54) + 164.0;
      *(float *)(iVar1 + 0x85c) = *(float *)(iVar1 + 0x88c) * *(float *)(iVar1 + 0xa54) + 164.0;
      mSetWorldDest__7solomonFv(param_1);
      *(undefined4 *)(iVar1 + 0x864) = *(undefined4 *)(iVar1 + 0x85c);
      *(undefined4 *)(iVar1 + 0x860) = *(undefined4 *)(iVar1 + 0x858);
    }
  }
  return;
}

/* JP: 0x004fdfb0  solomon::mCheckSetDemon()   [mCheckSetDemon__7solomonFv]  size=0x1c4 */
void mCheckSetDemon__7solomonFv(int param_1)

{
  int iVar1;
  
  if (*(int *)(param_1 + 0x30) != 0) {
    if (*(char *)(param_1 + *(int *)(param_1 + 0x34) * 2 + 0xb05) == '\0') {
      setPos__10primCursorFff(0xc2c80000,0xc2c80000,*(undefined4 *)(param_1 + 0x30));
    }
    else {
      for (iVar1 = 0; iVar1 < 0x48; iVar1 = iVar1 + 1) {
        if (*(char *)(param_1 + iVar1 * 6 + 0x4ec) ==
            *(char *)(param_1 + *(int *)(param_1 + 0x34) * 2 + 0xb04)) {
          setPos__10primCursorFff(*(float *)(param_1 + 0x860) +
                          (*(float *)(param_1 + 0xa54) *
                           (float)(*(int *)(&mSlotBaseTbl + iVar1 * 0xc) + -0x14) - 22.0),
                          *(float *)(param_1 + 0x864) +
                          (*(float *)(param_1 + 0xa54) *
                           (float)*(int *)(&DAT_00554454 + iVar1 * 0xc) - 10.0),
                          *(undefined4 *)(param_1 + 0x30));
          return;
        }
      }
    }
  }
  return;
}

/* JP: 0x004fe180  solomon::mSetLine(int)   [mSetLine__7solomonFi]  size=0x328 */
void mSetLine__7solomonFi(int param_1,int param_2)

{
  long lVar1;
  
  lVar1 = isDemon__11solomonSlotFv(*(undefined4 *)(param_1 + param_2 * 4 + 0x3cc));
  if (lVar1 == 0) {
    if (*(char *)(param_1 + param_2 * 6 + 0x4ee) != -1) {
      setA__6prim2DFii(*(undefined4 *)(param_1 + *(char *)(param_1 + param_2 * 6 + 0x4ee) * 4 + 0xa4)
                      ,2,0x40);
      setA__6prim2DFii(*(undefined4 *)(param_1 + *(char *)(param_1 + param_2 * 6 + 0x4ee) * 4 + 0xa4)
                      ,3,0x40);
    }
    if (*(char *)(param_1 + param_2 * 6 + 0x4ef) != -1) {
      setA__6prim2DFii(*(undefined4 *)(param_1 + *(char *)(param_1 + param_2 * 6 + 0x4ef) * 4 + 0xa4)
                      ,0,0x40);
      setA__6prim2DFii(*(undefined4 *)(param_1 + *(char *)(param_1 + param_2 * 6 + 0x4ef) * 4 + 0xa4)
                      ,1,0x40);
    }
    if (*(char *)(param_1 + param_2 * 6 + 0x4f0) != -1) {
      setA__6prim2DFii(*(undefined4 *)(param_1 + *(char *)(param_1 + param_2 * 6 + 0x4f0) * 4 + 0xa4)
                      ,2,0x40);
      setA__6prim2DFii(*(undefined4 *)(param_1 + *(char *)(param_1 + param_2 * 6 + 0x4f0) * 4 + 0xa4)
                      ,3,0x40);
    }
    if (*(char *)(param_1 + param_2 * 6 + 0x4f1) != -1) {
      setA__6prim2DFii(*(undefined4 *)(param_1 + *(char *)(param_1 + param_2 * 6 + 0x4f1) * 4 + 0xa4)
                      ,0,0x40);
      setA__6prim2DFii(*(undefined4 *)(param_1 + *(char *)(param_1 + param_2 * 6 + 0x4f1) * 4 + 0xa4)
                      ,1,0x40);
    }
  }
  return;
}

/* JP: 0x004fe4b0  solomon::mEraseLine(int)   [mEraseLine__7solomonFi]  size=0x328 */
void mEraseLine__7solomonFi(int param_1,int param_2)

{
  long lVar1;
  
  lVar1 = isDemon__11solomonSlotFv(*(undefined4 *)(param_1 + param_2 * 4 + 0x3cc));
  if (lVar1 == 0) {
    if (*(char *)(param_1 + param_2 * 6 + 0x4ee) != -1) {
      setA__6prim2DFii(*(undefined4 *)(param_1 + *(char *)(param_1 + param_2 * 6 + 0x4ee) * 4 + 0xa4)
                      ,2,0x24);
      setA__6prim2DFii(*(undefined4 *)(param_1 + *(char *)(param_1 + param_2 * 6 + 0x4ee) * 4 + 0xa4)
                      ,3,0x24);
    }
    if (*(char *)(param_1 + param_2 * 6 + 0x4ef) != -1) {
      setA__6prim2DFii(*(undefined4 *)(param_1 + *(char *)(param_1 + param_2 * 6 + 0x4ef) * 4 + 0xa4)
                      ,0,0x24);
      setA__6prim2DFii(*(undefined4 *)(param_1 + *(char *)(param_1 + param_2 * 6 + 0x4ef) * 4 + 0xa4)
                      ,1,0x24);
    }
    if (*(char *)(param_1 + param_2 * 6 + 0x4f0) != -1) {
      setA__6prim2DFii(*(undefined4 *)(param_1 + *(char *)(param_1 + param_2 * 6 + 0x4f0) * 4 + 0xa4)
                      ,2,0x24);
      setA__6prim2DFii(*(undefined4 *)(param_1 + *(char *)(param_1 + param_2 * 6 + 0x4f0) * 4 + 0xa4)
                      ,3,0x24);
    }
    if (*(char *)(param_1 + param_2 * 6 + 0x4f1) != -1) {
      setA__6prim2DFii(*(undefined4 *)(param_1 + *(char *)(param_1 + param_2 * 6 + 0x4f1) * 4 + 0xa4)
                      ,0,0x24);
      setA__6prim2DFii(*(undefined4 *)(param_1 + *(char *)(param_1 + param_2 * 6 + 0x4f1) * 4 + 0xa4)
                      ,1,0x24);
    }
  }
  return;
}

/* JP: 0x004fe7e0  solomon::mWinPolling()   [mWinPolling__7solomonFv]  size=0x198 */
void mWinPolling__7solomonFv(int param_1)

{
  if ((*(int *)(param_1 + 0x78) != 0) && (*(char *)(*(int *)(param_1 + 0x78) + 0x102) != '\0')) {
    if (*(int *)(param_1 + 0x78) == *(int *)(param_1 + 0x8c)) {
      *(undefined4 *)(param_1 + 0x8c) = 0;
    }
    mReleaseMainWin__7solomonFv(param_1);
  }
  if ((*(int *)(param_1 + 0x7c) != 0) && (*(char *)(*(int *)(param_1 + 0x7c) + 0x102) != '\0')) {
    if (*(int *)(param_1 + 0x7c) == *(int *)(param_1 + 0x8c)) {
      *(undefined4 *)(param_1 + 0x8c) = 0;
    }
    mReleaseHintWin__7solomonFv(param_1);
  }
  if ((*(int *)(param_1 + 0x84) != 0) && (*(char *)(*(int *)(param_1 + 0x84) + 0x102) != '\0')) {
    if (*(int *)(param_1 + 0x84) == *(int *)(param_1 + 0x8c)) {
      *(undefined4 *)(param_1 + 0x8c) = 0;
    }
    mReleaseDemonWin__7solomonFv(param_1);
  }
  if ((*(int *)(param_1 + 0x80) != 0) && (*(char *)(*(int *)(param_1 + 0x80) + 0x102) != '\0')) {
    if (*(int *)(param_1 + 0x80) == *(int *)(param_1 + 0x8c)) {
      *(undefined4 *)(param_1 + 0x8c) = 0;
    }
    mReleaseMessWin__7solomonFv(param_1);
  }
  return;
}

/* JP: 0x004fe980  solomon::~solomon()   [@24@__dt__7solomonFv]  size=0x8 */
int _24___dt__7solomonFv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x18;
  if (iVar1 != 0) {
    *(undefined1 **)(param_1 + -4) = &__vt__7solomon;
    *(undefined4 *)(param_1 + 8) = 0x409830;
    if (*(int *)(param_1 + 0x83c) != 0) {
      DelayDeleteRequest__13solomonEffectFv(*(undefined4 *)(param_1 + 0x83c));
      *(undefined4 *)(param_1 + 0x83c) = 0;
    }
    Dispose__7CPollerFP7CPolObj(app__4CApp + 0x48,iVar1);
    if (m_pPT != 0) {
      __dt__7primTexFv(m_pPT,1);
      m_pPT = 0;
    }
    if (*(int *)(param_1 + 0x5c) != 0) {
      DelayDeleteRequest__9primSoundFv(*(undefined4 *)(param_1 + 0x5c));
      *(undefined4 *)(param_1 + 0x5c) = 0;
    }
    __dt__4FontFv(param_1 + 0x7dc,0xffffffffffffffff);
    __dt__7primWinFv(param_1 + 0x694,0xffffffffffffffff);
    if (iVar1 != -0x18) {
      *(undefined1 **)(param_1 + 8) = &__vt__17DelayDeleteObject;
    }
    __dt__7CPolObjFv(iVar1,0);
    if (0 < param_2) {
      __dl__FPv(iVar1);
    }
  }
  return iVar1;
}
