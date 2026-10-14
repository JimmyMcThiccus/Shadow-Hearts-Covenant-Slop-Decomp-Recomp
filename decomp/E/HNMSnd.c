/*
 * HNMSnd.c -- Ghidra decompiler output (SLPM_602.19, JP Furokuban), tidied by tools/E_gen_decomp.py
 * 32 functions. Types: u8/u16/u32/u64 = undefined1/2/4/8. Addresses in comments are JP main-exe addresses.
 */

/* ---- 0x00345e70 size 0x204  HNMSnd::HNMSnd(v)
 *      mangled: __ct__6HNMSndFv */
int __ct__6HNMSndFv(int param_1)

{
  u32 in_zero_lo;
  u32 in_zero_hi;
  u32 in_zero_udw;
  u32 in_register_0000000c;
  int iVar1;
  
  __ct__7CPolObjFv(param_1);
  *(u8 **)(param_1 + 0x14) = __vt__6HNMSnd;
  iVar1 = param_1 + 0xc0;
  do {
    *(u32 *)(iVar1 + 0x10) = in_zero_lo;
    *(u32 *)(iVar1 + 0x14) = in_zero_hi;
    *(u32 *)(iVar1 + 0x18) = in_zero_udw;
    *(u32 *)(iVar1 + 0x1c) = in_register_0000000c;
    iVar1 = iVar1 + 0x30;
  } while (iVar1 != param_1 + 0x3c0);
  for (iVar1 = 0; iVar1 < 8; iVar1 = iVar1 + 1) {
    *(u16 *)(param_1 + iVar1 * 0x14 + 0x1c) = 0;
  }
  *(u16 *)(param_1 + 0x3c4) = 0;
  *(u16 *)(param_1 + 0x436) = 0;
  *(u16 *)(param_1 + 0x434) = 0;
  for (iVar1 = 0; iVar1 < 0x10; iVar1 = iVar1 + 1) {
    *(u16 *)(param_1 + iVar1 * 0x30 + 0xc2) = 0;
    *(char *)(param_1 + *(short *)(param_1 + 0x436) + 0x414) = (char)iVar1;
    *(short *)(param_1 + 0x436) = *(short *)(param_1 + 0x436) + 1;
  }
  *(byte *)(param_1 + 0x3c0) = *(byte *)(param_1 + 0x3c0) & 0x7f;
  *(byte *)(param_1 + 0x3c0) = *(byte *)(param_1 + 0x3c0) & 0xdf;
  *(byte *)(param_1 + 0x3c0) = *(byte *)(param_1 + 0x3c0) & 0xbf;
  *(u8 *)(param_1 + 0x3f0) = 0;
  *(u8 *)(param_1 + 0x3f1) = 0;
  *(u8 *)(param_1 + 0x3f2) = 0xff;
  *(u8 *)(param_1 + 0x3f3) = 0xff;
  *(u8 *)(param_1 + 0x3fc) = 0;
  *(u8 *)(param_1 + 0x3fd) = 0;
  *(u8 *)(param_1 + 0x3fe) = 0xff;
  *(u8 *)(param_1 + 0x3ff) = 0xff;
  sys__6HNMSnd = param_1;
  Entry__7CPollerFP7CPolObjib(app__4CApp + 0x48,param_1,0x80,0);
  return param_1;
}

/* ---- 0x00346080 size 0x8c  HNMSnd::~HNMSnd(v)
 *      mangled: __dt__6HNMSndFv */
int __dt__6HNMSndFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(u8 **)(param_1 + 0x14) = __vt__6HNMSnd;
    sys__6HNMSnd = 0;
    Dispose__7CPollerFP7CPolObj(app__4CApp + 0x48,param_1);
    __dt__7CPolObjFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* ---- 0x00346110 size 0x382c  HNMSnd::Polling(v)
 *      mangled: Polling__6HNMSndFv */
u64 Polling__6HNMSndFv(int param_1)

{
  short sVar1;
  u8 uVar2;
  char cVar3;
  u16 uVar4;
  u32 uVar5;
  long lVar6;
  int iVar7;
  int iVar8;
  long unaff_s1;
  u8 uStack_e0;
  u8 uStack_df;
  u16 uStack_de;
  u16 uStack_dc;
  u8 uStack_d0;
  u8 uStack_cf;
  u16 uStack_ce;
  u16 uStack_cc;
  u8 uStack_c0;
  u8 uStack_bf;
  u16 uStack_be;
  u16 uStack_bc;
  char acStack_b0 [136];
  u32 uStack_28;
  u32 uStack_24;
  u32 uStack_20;
  u32 uStack_1c;
  int iStack_18;
  int iStack_14;
  int iStack_10;
  
  iStack_10 = param_1;
  switch(*(u8 *)(param_1 + 0x3f0)) {
  case 0:
    *(byte *)(param_1 + 0x3c0) = *(byte *)(param_1 + 0x3c0) & 0xfd;
    *(byte *)(param_1 + 0x3c0) = *(byte *)(param_1 + 0x3c0) & 0xf7;
    *(byte *)(param_1 + 0x3c0) = *(byte *)(param_1 + 0x3c0) & 0xfb;
    break;
  case 1:
    if (*(char *)(param_1 + 0x3f1) == '\x01') {
LAB_003462e8:
      if (*(int *)(&FRMem__6HNMApi + *(char *)(iStack_10 + 0x3f2) * 4) == 0) {
        if ((FRFlag__6HNMApi & 1 << ((int)*(char *)(iStack_10 + 0x3f2) & 0x1fU)) == 0) {
          if ((long)((ulong)*(byte *)(iStack_10 + 0x3c0) << 0x3c) < 0) {
            *(u8 *)(iStack_10 + 0x3f0) = 0;
            *(u8 *)(iStack_10 + 0x3f2) = 0xff;
            *(byte *)(iStack_10 + 0x3c0) = *(byte *)(iStack_10 + 0x3c0) & 0xf7;
          }
          else {
            *(u8 *)(iStack_10 + 0x3f1) = 0;
            *(u8 *)(iStack_10 + 0x3f2) = 0xff;
          }
        }
        else if ((long)((ulong)*(byte *)(iStack_10 + 0x3c0) << 0x3c) < 0) {
          FileReadCancel__6HNMApiFi(*(u8 *)(iStack_10 + 0x3f2));
        }
      }
      else if ((long)((ulong)*(byte *)(iStack_10 + 0x3c0) << 0x3c) < 0) {
        *(u8 *)(iStack_10 + 0x3f0) = 0;
        DataGetCall__6HNMApiFi(*(u8 *)(iStack_10 + 0x3f2));
        *(u8 *)(iStack_10 + 0x3f2) = 0xff;
        *(byte *)(iStack_10 + 0x3c0) = *(byte *)(iStack_10 + 0x3c0) & 0xf7;
      }
      else {
        *(u8 *)(iStack_10 + 0x3f0) = 2;
        *(u8 *)(iStack_10 + 0x3f1) = 0;
      }
    }
    else if (*(char *)(param_1 + 0x3f1) == '\0') {
      sprintf(acStack_b0,_6409,*(u32 *)(param_1 + 0x3ec));
      uVar2 = FileReadEntry__6HNMApiFPc(acStack_b0);
      *(u8 *)(iStack_10 + 0x3f2) = uVar2;
      if (-1 < *(char *)(iStack_10 + 0x3f2)) {
        *(byte *)(iStack_10 + 0x3c1) = *(byte *)(iStack_10 + 0x3c1) & 0xfb | 4;
        *(u8 *)(iStack_10 + 0x3f1) = 1;
        goto LAB_003462e8;
      }
      if ((long)((ulong)*(byte *)(iStack_10 + 0x3c0) << 0x3c) < 0) {
        *(u8 *)(iStack_10 + 0x3f0) = 0;
        *(byte *)(iStack_10 + 0x3c0) = *(byte *)(iStack_10 + 0x3c0) & 0xf7;
      }
    }
    break;
  case 2:
    if (*(char *)(param_1 + 0x3f1) == '\x01') {
LAB_00346598:
      lVar6 = IOPEntryCheck__6HNMSndFi(iStack_10,*(u8 *)(iStack_10 + 0x3f3));
      if (lVar6 == 1) {
        iStack_14 = (int)*(char *)(iStack_10 + 0x3f3);
        uStack_28 = *(u32 *)(iStack_10 + iStack_14 * 0x14 + 0x28);
        *(u32 *)(iStack_10 + 0x3f4) = uStack_28;
        uStack_24 = uStack_28;
        DataGetCall__6HNMApiFi(*(u8 *)(iStack_10 + 0x3f2));
        *(u8 *)(iStack_10 + 0x3f2) = 0xff;
        if ((long)((ulong)*(byte *)(iStack_10 + 0x3c0) << 0x3c) < 0) {
          IOPRelease__6HNMSndFi(iStack_10,*(u8 *)(iStack_10 + 0x3f3));
          *(u8 *)(iStack_10 + 0x3f0) = 0;
          *(byte *)(iStack_10 + 0x3c0) = *(byte *)(iStack_10 + 0x3c0) & 0xf7;
          *(byte *)(iStack_10 + 0x3c0) = *(byte *)(iStack_10 + 0x3c0) & 0xfb;
        }
        else if ((long)((ulong)*(byte *)(iStack_10 + 0x3c0) << 0x39) < 0) {
          *(u8 *)(iStack_10 + 0x3f0) = 7;
          *(u8 *)(iStack_10 + 0x3f1) = 0;
        }
        else {
          *(u8 *)(iStack_10 + 0x3f0) = 5;
          *(u8 *)(iStack_10 + 0x3f1) = 0;
        }
      }
    }
    else if (*(char *)(param_1 + 0x3f1) == '\0') {
      if ((long)((ulong)*(byte *)(param_1 + 0x3c0) << 0x3e) < 0) {
        uStack_20 = *(u32 *)(*(int *)(&FRMem__6HNMApi + *(char *)(param_1 + 0x3f2) * 4) + 4);
        uStack_1c = uStack_20;
        uVar2 = IOPEntry__6HNMSndFPUc(param_1,uStack_20);
        *(u8 *)(iStack_10 + 0x3f3) = uVar2;
        *(u8 *)(iStack_10 + 0x3f1) = 1;
        goto LAB_00346598;
      }
      if ((long)((ulong)*(byte *)(param_1 + 0x3c0) << 0x3c) < 0) {
        *(u8 *)(param_1 + 0x3f0) = 0;
        DataGetCall__6HNMApiFi(*(u8 *)(param_1 + 0x3f2));
        *(u8 *)(iStack_10 + 0x3f2) = 0xff;
        *(byte *)(iStack_10 + 0x3c0) = *(byte *)(iStack_10 + 0x3c0) & 0xf7;
      }
    }
    break;
  case 3:
    *(byte *)(param_1 + 0x3c0) = *(byte *)(param_1 + 0x3c0) & 0xfb;
    if ((long)((ulong)*(byte *)(param_1 + 0x3c0) << 0x3c) < 0) {
      if ((long)((ulong)*(byte *)(param_1 + 0x3c0) << 0x3b) < 0) {
        *(u8 *)(param_1 + 0x3f0) = 10;
        *(u8 *)(param_1 + 0x3f1) = 0;
      }
      else {
        IOPRelease__6HNMSndFi(param_1,*(u8 *)(param_1 + 0x3f3));
        *(u8 *)(iStack_10 + 0x3f0) = 0;
      }
      *(byte *)(iStack_10 + 0x3c0) = *(byte *)(iStack_10 + 0x3c0) & 0xf7;
    }
    break;
  case 4:
    if (*(char *)(param_1 + 0x3f1) != '\x01') {
      if (*(char *)(param_1 + 0x3f1) != '\0') break;
      StopBGM__6HNMSndFii(param_1,1,0xfa);
      *(u8 *)(iStack_10 + 0x3f1) = 1;
    }
    cVar3 = BGMEndCheck__6HNMSndFv(iStack_10);
    if (cVar3 == '\x01') {
      if ((long)((ulong)*(byte *)(iStack_10 + 0x3c0) << 0x3c) < 0) {
        if ((long)((ulong)*(byte *)(iStack_10 + 0x3c0) << 0x3b) < 0) {
          *(u8 *)(iStack_10 + 0x3f0) = 10;
          *(u8 *)(iStack_10 + 0x3f1) = 0;
        }
        else {
          IOPRelease__6HNMSndFi(iStack_10,*(u8 *)(iStack_10 + 0x3f3));
          *(u8 *)(iStack_10 + 0x3f0) = 0;
        }
        *(byte *)(iStack_10 + 0x3c0) = *(byte *)(iStack_10 + 0x3c0) & 0xf7;
        *(byte *)(iStack_10 + 0x3c0) = *(byte *)(iStack_10 + 0x3c0) & 0xfb;
      }
      else if ((long)((ulong)*(byte *)(iStack_10 + 0x3c0) << 0x39) < 0) {
        if ((long)((ulong)*(byte *)(iStack_10 + 0x3c0) << 0x39) < 0) {
          *(u8 *)(iStack_10 + 0x3f0) = 7;
          *(u8 *)(iStack_10 + 0x3f1) = 0;
          *(byte *)(iStack_10 + 0x3c0) = *(byte *)(iStack_10 + 0x3c0) & 0xdf;
        }
      }
      else {
        *(u8 *)(iStack_10 + 0x3f0) = 5;
        *(u8 *)(iStack_10 + 0x3f1) = 0;
      }
    }
    else if ((long)((ulong)*(byte *)(iStack_10 + 0x3c0) << 0x3c) < 0) {
      if ((long)((ulong)*(byte *)(iStack_10 + 0x3c0) << 0x3b) < 0) {
        *(u8 *)(iStack_10 + 0x3f0) = 9;
        *(u8 *)(iStack_10 + 0x3f1) = 1;
      }
      else {
        StopBGM__6HNMSndFii(iStack_10,0,0);
        IOPRelease__6HNMSndFi(iStack_10,*(u8 *)(iStack_10 + 0x3f3));
        *(u8 *)(iStack_10 + 0x3f0) = 0;
      }
      *(byte *)(iStack_10 + 0x3c0) = *(byte *)(iStack_10 + 0x3c0) & 0xf7;
      *(byte *)(iStack_10 + 0x3c0) = *(byte *)(iStack_10 + 0x3c0) & 0xfb;
    }
    else if ((long)((ulong)*(byte *)(iStack_10 + 0x3c0) << 0x39) < 0) {
      *(u8 *)(iStack_10 + 0x3f0) = 6;
      *(byte *)(iStack_10 + 0x3c0) = *(byte *)(iStack_10 + 0x3c0) & 0xdf;
    }
    break;
  case 5:
    if (*(char *)(param_1 + 0x3f1) != '\x01') {
      if (*(char *)(param_1 + 0x3f1) != '\0') break;
      uStack_c0 = 0x7f;
      uStack_bf = 0x40;
      uStack_be = 0;
      uStack_bc = 1000;
      PlayBGM__6HNMSndFUiiiP9_BgmParam(param_1,*(u32 *)(param_1 + 0x3f4),0,0x1001,&uStack_c0)
      ;
      *(byte *)(iStack_10 + 0x3c0) = *(byte *)(iStack_10 + 0x3c0) & 0xdf;
      *(u8 *)(iStack_10 + 0x3f1) = 1;
    }
    if ((long)((ulong)*(byte *)(iStack_10 + 0x3c0) << 0x3c) < 0) {
      if ((long)((ulong)*(byte *)(iStack_10 + 0x3c0) << 0x3b) < 0) {
        *(u8 *)(iStack_10 + 0x3f0) = 0;
        *(u8 *)(iStack_10 + 0x3f1) = 0;
      }
      else {
        StopBGM__6HNMSndFii(iStack_10,0,0);
        IOPRelease__6HNMSndFi(iStack_10,*(u8 *)(iStack_10 + 0x3f3));
        *(u8 *)(iStack_10 + 0x3f0) = 0;
      }
      *(byte *)(iStack_10 + 0x3c0) = *(byte *)(iStack_10 + 0x3c0) & 0xf7;
      *(byte *)(iStack_10 + 0x3c0) = *(byte *)(iStack_10 + 0x3c0) & 0xfb;
    }
    else if ((long)((ulong)*(byte *)(iStack_10 + 0x3c0) << 0x3d) < 0) {
      *(u8 *)(iStack_10 + 0x3f0) = 8;
      *(u8 *)(iStack_10 + 0x3f1) = 0;
      *(byte *)(iStack_10 + 0x3c0) = *(byte *)(iStack_10 + 0x3c0) & 0xfb;
    }
    else if ((long)((ulong)*(byte *)(iStack_10 + 0x3c0) << 0x39) < 0) {
      *(u8 *)(iStack_10 + 0x3f0) = 6;
      *(u8 *)(iStack_10 + 0x3f1) = 0;
    }
    *(byte *)(iStack_10 + 0x3c0) = *(byte *)(iStack_10 + 0x3c0) & 0xdf;
    break;
  case 6:
    if (*(char *)(param_1 + 0x3f1) != '\x01') {
      if (*(char *)(param_1 + 0x3f1) != '\0') break;
      StopBGM__6HNMSndFii(param_1,1,0xfa);
      *(u8 *)(iStack_10 + 0x3f1) = 1;
    }
    cVar3 = BGMEndCheck__6HNMSndFv(iStack_10);
    if (cVar3 == '\x01') {
      if ((long)((ulong)*(byte *)(iStack_10 + 0x3c0) << 0x3c) < 0) {
        if ((long)((ulong)*(byte *)(iStack_10 + 0x3c0) << 0x3b) < 0) {
          *(u8 *)(iStack_10 + 0x3f0) = 10;
          *(u8 *)(iStack_10 + 0x3f1) = 0;
        }
        else {
          IOPRelease__6HNMSndFi(iStack_10,*(u8 *)(iStack_10 + 0x3f3));
          *(u8 *)(iStack_10 + 0x3f0) = 0;
        }
        *(byte *)(iStack_10 + 0x3c0) = *(byte *)(iStack_10 + 0x3c0) & 0xf7;
        *(byte *)(iStack_10 + 0x3c0) = *(byte *)(iStack_10 + 0x3c0) & 0xfb;
      }
      else if ((long)((ulong)*(byte *)(iStack_10 + 0x3c0) << 0x3a) < 0) {
        if ((long)((ulong)*(byte *)(iStack_10 + 0x3c0) << 0x3a) < 0) {
          *(u8 *)(iStack_10 + 0x3f0) = 5;
          *(u8 *)(iStack_10 + 0x3f1) = 0;
          *(byte *)(iStack_10 + 0x3c0) = *(byte *)(iStack_10 + 0x3c0) & 0xbf;
        }
      }
      else {
        *(u8 *)(iStack_10 + 0x3f0) = 7;
        *(u8 *)(iStack_10 + 0x3f1) = 0;
      }
    }
    else if ((long)((ulong)*(byte *)(iStack_10 + 0x3c0) << 0x3c) < 0) {
      StopBGM__6HNMSndFii(iStack_10,0,0);
      if ((long)((ulong)*(byte *)(iStack_10 + 0x3c0) << 0x3b) < 0) {
        *(u8 *)(iStack_10 + 0x3f0) = 10;
        *(u8 *)(iStack_10 + 0x3f1) = 0;
      }
      else {
        IOPRelease__6HNMSndFi(iStack_10,*(u8 *)(iStack_10 + 0x3f3));
        *(u8 *)(iStack_10 + 0x3f0) = 0;
      }
      *(byte *)(iStack_10 + 0x3c0) = *(byte *)(iStack_10 + 0x3c0) & 0xf7;
      *(byte *)(iStack_10 + 0x3c0) = *(byte *)(iStack_10 + 0x3c0) & 0xfb;
    }
    else if ((long)((ulong)*(byte *)(iStack_10 + 0x3c0) << 0x39) < 0) {
      *(u8 *)(iStack_10 + 0x3f0) = 6;
      *(byte *)(iStack_10 + 0x3c0) = *(byte *)(iStack_10 + 0x3c0) & 0xdf;
    }
    break;
  case 7:
    if (*(char *)(param_1 + 0x3f1) != '\x01') {
      if (*(char *)(param_1 + 0x3f1) != '\0') break;
      uStack_d0 = 0x7f;
      uStack_cf = 0x40;
      uStack_ce = 0;
      uStack_cc = 1000;
      PlayBGM__6HNMSndFUiiiP9_BgmParam(param_1,*(u32 *)(param_1 + 0x3f4),1,0x1001,&uStack_d0)
      ;
      *(byte *)(iStack_10 + 0x3c0) = *(byte *)(iStack_10 + 0x3c0) & 0xbf;
      *(u8 *)(iStack_10 + 0x3f1) = 1;
    }
    if ((long)((ulong)*(byte *)(iStack_10 + 0x3c0) << 0x3c) < 0) {
      if ((long)((ulong)*(byte *)(iStack_10 + 0x3c0) << 0x3b) < 0) {
        *(u8 *)(iStack_10 + 0x3f0) = 9;
        *(u8 *)(iStack_10 + 0x3f1) = 0;
      }
      else {
        StopBGM__6HNMSndFii(iStack_10,0,0);
        IOPRelease__6HNMSndFi(iStack_10,*(u8 *)(iStack_10 + 0x3f3));
        *(u8 *)(iStack_10 + 0x3f0) = 0;
      }
      *(byte *)(iStack_10 + 0x3c0) = *(byte *)(iStack_10 + 0x3c0) & 0xf7;
      *(byte *)(iStack_10 + 0x3c0) = *(byte *)(iStack_10 + 0x3c0) & 0xfb;
    }
    else if ((long)((ulong)*(byte *)(iStack_10 + 0x3c0) << 0x3d) < 0) {
      *(u8 *)(iStack_10 + 0x3f0) = 8;
      *(u8 *)(iStack_10 + 0x3f1) = 0;
      *(byte *)(iStack_10 + 0x3c0) = *(byte *)(iStack_10 + 0x3c0) & 0xfb;
    }
    else if ((long)((ulong)*(byte *)(iStack_10 + 0x3c0) << 0x3a) < 0) {
      *(u8 *)(iStack_10 + 0x3f0) = 4;
      *(u8 *)(iStack_10 + 0x3f1) = 0;
    }
    *(byte *)(iStack_10 + 0x3c0) = *(byte *)(iStack_10 + 0x3c0) & 0xbf;
    break;
  case 8:
    *(byte *)(param_1 + 0x3c0) = *(byte *)(param_1 + 0x3c0) & 0xfb;
    if (*(char *)(param_1 + 0x3f1) != '\x01') {
      if (*(char *)(param_1 + 0x3f1) != '\0') break;
      StopBGM__6HNMSndFii(param_1,1,*(u32 *)(param_1 + 0x3f8));
      *(u8 *)(iStack_10 + 0x3f1) = 1;
    }
    cVar3 = BGMEndCheck__6HNMSndFv(iStack_10);
    if (cVar3 == '\x01') {
      if ((long)((ulong)*(byte *)(iStack_10 + 0x3c0) << 0x3c) < 0) {
        if ((long)((ulong)*(byte *)(iStack_10 + 0x3c0) << 0x3b) < 0) {
          *(u8 *)(iStack_10 + 0x3f0) = 10;
          *(u8 *)(iStack_10 + 0x3f1) = 0;
        }
        else {
          IOPRelease__6HNMSndFi(iStack_10,*(u8 *)(iStack_10 + 0x3f3));
          *(u8 *)(iStack_10 + 0x3f0) = 0;
        }
        *(byte *)(iStack_10 + 0x3c0) = *(byte *)(iStack_10 + 0x3c0) & 0xf7;
      }
      else {
        *(u8 *)(iStack_10 + 0x3f0) = 3;
        *(u8 *)(iStack_10 + 0x3f1) = 0;
      }
    }
    else if ((long)((ulong)*(byte *)(iStack_10 + 0x3c0) << 0x3c) < 0) {
      if ((long)((ulong)*(byte *)(iStack_10 + 0x3c0) << 0x3b) < 0) {
        *(u8 *)(iStack_10 + 0x3f0) = 9;
        *(u8 *)(iStack_10 + 0x3f1) = 1;
      }
      else {
        StopBGM__6HNMSndFii(iStack_10,0,0);
        IOPRelease__6HNMSndFi(iStack_10,*(u8 *)(iStack_10 + 0x3f3));
        *(u8 *)(iStack_10 + 0x3f0) = 0;
      }
      *(byte *)(iStack_10 + 0x3c0) = *(byte *)(iStack_10 + 0x3c0) & 0xf7;
    }
    break;
  case 9:
    if (*(char *)(param_1 + 0x3f1) != '\x01') {
      if (*(char *)(param_1 + 0x3f1) != '\0') break;
      StopBGM__6HNMSndFii(param_1,1,*(u32 *)(param_1 + 0x3f8));
      *(u8 *)(iStack_10 + 0x3f1) = 1;
    }
    cVar3 = BGMEndCheck__6HNMSndFv(iStack_10);
    if (cVar3 == '\x01') {
      *(u8 *)(iStack_10 + 0x3f0) = 10;
      *(u8 *)(iStack_10 + 0x3f1) = 0;
    }
    break;
  case 10:
    if (*(char *)(param_1 + 0x3f1) == '\0') {
      uStack_e0 = 0x7f;
      uStack_df = 0x40;
      uStack_de = 0;
      uStack_dc = 1000;
      PlayBGM__6HNMSndFUiiiP9_BgmParam(param_1,*(u32 *)(param_1 + 0x3f4),0,0x1001,&uStack_e0)
      ;
      *(u8 *)(iStack_10 + 0x3f0) = 0;
      *(u8 *)(iStack_10 + 0x3f1) = 0;
    }
  }
  switch(*(u8 *)(iStack_10 + 0x3fc)) {
  case 0:
    *(byte *)(iStack_10 + 0x3c1) = *(byte *)(iStack_10 + 0x3c1) & 0xfd;
    *(byte *)(iStack_10 + 0x3c1) = *(byte *)(iStack_10 + 0x3c1) & 0xfe;
    break;
  case 1:
    if (*(char *)(iStack_10 + 0x3fd) == '\x01') {
LAB_00347658:
      if (*(int *)(&FRMem__6HNMApi + *(char *)(iStack_10 + 0x3fe) * 4) == 0) {
        if ((FRFlag__6HNMApi & 1 << ((int)*(char *)(iStack_10 + 0x3fe) & 0x1fU)) == 0) {
          if ((long)((ulong)*(byte *)(iStack_10 + 0x3c1) << 0x3e) < 0) {
            *(u8 *)(iStack_10 + 0x3fc) = 0;
            *(u8 *)(iStack_10 + 0x3fe) = 0xff;
            *(byte *)(iStack_10 + 0x3c1) = *(byte *)(iStack_10 + 0x3c1) & 0xfd;
          }
          else {
            *(u8 *)(iStack_10 + 0x3fd) = 0;
            *(u8 *)(iStack_10 + 0x3fe) = 0xff;
          }
        }
        else if ((long)((ulong)*(byte *)(iStack_10 + 0x3c1) << 0x3e) < 0) {
          FileReadCancel__6HNMApiFi(*(u8 *)(iStack_10 + 0x3fe));
        }
      }
      else if ((long)((ulong)*(byte *)(iStack_10 + 0x3c1) << 0x3e) < 0) {
        *(u8 *)(iStack_10 + 0x3fc) = 0;
        DataGetCall__6HNMApiFi(*(u8 *)(iStack_10 + 0x3fe));
        *(u8 *)(iStack_10 + 0x3fe) = 0xff;
        *(byte *)(iStack_10 + 0x3c1) = *(byte *)(iStack_10 + 0x3c1) & 0xfd;
      }
      else {
        *(u8 *)(iStack_10 + 0x3fc) = 2;
        *(u8 *)(iStack_10 + 0x3fd) = 0;
      }
    }
    else if (*(char *)(iStack_10 + 0x3fd) == '\0') {
      uVar2 = FileReadEntry__6HNMApiFPc(0x3ff490);
      *(u8 *)(iStack_10 + 0x3fe) = uVar2;
      if (-1 < *(char *)(iStack_10 + 0x3fe)) {
        *(u8 *)(iStack_10 + 0x3fd) = 1;
        goto LAB_00347658;
      }
      if ((long)((ulong)*(byte *)(iStack_10 + 0x3c1) << 0x3e) < 0) {
        *(u8 *)(iStack_10 + 0x3fc) = 0;
        *(byte *)(iStack_10 + 0x3c1) = *(byte *)(iStack_10 + 0x3c1) & 0xfd;
      }
    }
    break;
  case 2:
    if ((long)((ulong)*(byte *)(iStack_10 + 0x3c1) << 0x3e) < 0) {
      *(u8 *)(iStack_10 + 0x3fc) = 0;
      DataGetCall__6HNMApiFi(*(u8 *)(iStack_10 + 0x3fe));
      *(u8 *)(iStack_10 + 0x3fe) = 0xff;
      *(byte *)(iStack_10 + 0x3c1) = *(byte *)(iStack_10 + 0x3c1) & 0xfd;
    }
    break;
  case 3:
    if (*(char *)(iStack_10 + 0x3fd) != '\x01') {
      if (*(char *)(iStack_10 + 0x3fd) != '\0') break;
      uVar2 = IOPEntry__6HNMSndFPUc
                        (iStack_10,
                         *(u32 *)
                          (*(int *)(&FRMem__6HNMApi + *(char *)(iStack_10 + 0x3fe) * 4) + 4));
      *(u8 *)(iStack_10 + 0x3ff) = uVar2;
      *(u8 *)(iStack_10 + 0x3fd) = 1;
    }
    lVar6 = IOPEntryCheck__6HNMSndFi(iStack_10,*(u8 *)(iStack_10 + 0x3ff));
    if (lVar6 == 1) {
      iStack_18 = (int)*(char *)(iStack_10 + 0x3ff);
      *(u32 *)(iStack_10 + 0x400) = *(u32 *)(iStack_10 + iStack_18 * 0x14 + 0x28);
      DataGetCall__6HNMApiFi(*(u8 *)(iStack_10 + 0x3fe));
      *(u8 *)(iStack_10 + 0x3fe) = 0xff;
      if ((long)((ulong)*(byte *)(iStack_10 + 0x3c1) << 0x3e) < 0) {
        IOPRelease__6HNMSndFi(iStack_10,*(u8 *)(iStack_10 + 0x3ff));
        *(u8 *)(iStack_10 + 0x3fc) = 0;
        *(byte *)(iStack_10 + 0x3c1) = *(byte *)(iStack_10 + 0x3c1) & 0xfd;
        *(byte *)(iStack_10 + 0x3c1) = *(byte *)(iStack_10 + 0x3c1) & 0xfe;
      }
      else {
        *(u8 *)(iStack_10 + 0x3fc) = 4;
        *(u8 *)(iStack_10 + 0x3fd) = 0;
      }
    }
    break;
  case 4:
    *(byte *)(iStack_10 + 0x3c1) = *(byte *)(iStack_10 + 0x3c1) & 0xfe;
    if ((long)((ulong)*(byte *)(iStack_10 + 0x3c1) << 0x3e) < 0) {
      IOPRelease__6HNMSndFi(iStack_10,*(u8 *)(iStack_10 + 0x3ff));
      *(u8 *)(iStack_10 + 0x3fc) = 0;
      *(byte *)(iStack_10 + 0x3c1) = *(byte *)(iStack_10 + 0x3c1) & 0xfd;
    }
    break;
  case 5:
    if (*(char *)(iStack_10 + 0x3fd) != '\x01') {
      if (*(char *)(iStack_10 + 0x3fd) != '\0') break;
      uVar5 = PlaySE2__6HNMSndFUibi(iStack_10,0x50000000,0,0x66);
      *(u32 *)(iStack_10 + 0x404) = uVar5;
      *(u8 *)(iStack_10 + 0x3fd) = 1;
    }
    if ((long)((ulong)*(byte *)(iStack_10 + 0x3c1) << 0x3e) < 0) {
      *(u8 *)(iStack_10 + 0x3fc) = 7;
      *(u8 *)(iStack_10 + 0x3fd) = 0;
      *(byte *)(iStack_10 + 0x3c1) = *(byte *)(iStack_10 + 0x3c1) & 0xfd;
      *(byte *)(iStack_10 + 0x3c1) = *(byte *)(iStack_10 + 0x3c1) & 0xfe;
    }
    else if ((*(byte *)(iStack_10 + 0x3c1) & 1) != 0) {
      *(u8 *)(iStack_10 + 0x3fc) = 6;
      *(u8 *)(iStack_10 + 0x3fd) = 0;
      *(byte *)(iStack_10 + 0x3c1) = *(byte *)(iStack_10 + 0x3c1) & 0xfe;
    }
    break;
  case 6:
    if (*(char *)(iStack_10 + 0x3fd) == '\x01') {
      iVar7 = GetTimer__7SysToolFv();
      *(int *)(iStack_10 + 0x410) =
           *(int *)(iStack_10 + 0x410) + (iVar7 - *(int *)(iStack_10 + 0x40c));
      *(int *)(iStack_10 + 0x40c) = iVar7;
      if (*(int *)(iStack_10 + 0x408) < *(int *)(iStack_10 + 0x410)) {
        *(u8 *)(iStack_10 + 0x3fc) = 7;
        *(u8 *)(iStack_10 + 0x3fd) = 0;
      }
    }
    else if (*(char *)(iStack_10 + 0x3fd) == '\0') {
      SetSEParam__6HNMSndFUiiiii
                (iStack_10,0x50000000,0,0,*(u32 *)(iStack_10 + 0x408),0xffffffffffffffff);
      *(u8 *)(iStack_10 + 0x3fd) = 1;
      uVar5 = GetTimer__7SysToolFv();
      *(u32 *)(iStack_10 + 0x40c) = uVar5;
      *(u32 *)(iStack_10 + 0x410) = 0;
    }
    break;
  case 7:
    if (*(char *)(iStack_10 + 0x3fd) != '\x01') {
      if (*(char *)(iStack_10 + 0x3fd) != '\0') break;
      SetSEEnd__6HNMSndFUii(iStack_10,0x50000000,0xffffffffffffffff);
      *(u8 *)(iStack_10 + 0x3fd) = 1;
    }
    cVar3 = SEEndCheck__6HNMSndFUii(iStack_10,0x50000000,0xffffffffffffffff);
    if (cVar3 != '\0') {
      IOPRelease__6HNMSndFi(iStack_10,*(u8 *)(iStack_10 + 0x3ff));
      *(u8 *)(iStack_10 + 0x3fc) = 0;
    }
  }
  for (iVar7 = 0; iVar7 < 8; iVar7 = iVar7 + 1) {
    sVar1 = *(short *)(iStack_10 + iVar7 * 0x14 + 0x1c);
    if (sVar1 == 3) {
      if ((*(short *)(iStack_10 + iVar7 * 0x14 + 0x1e) == 0) &&
         ((*(short *)(iStack_10 + 0x3c4) == 0 ||
          (*(int *)(iStack_10 + 0x3e0) != *(int *)(iStack_10 + iVar7 * 0x14 + 0x28))))) {
        uVar5 = ReleaseSDH__4SdrvFUi(sys__4Sdrv,*(u32 *)(iStack_10 + iVar7 * 0x14 + 0x28));
        *(u32 *)(iStack_10 + iVar7 * 0x14 + 0x24) = uVar5;
        if (*(int *)(iStack_10 + iVar7 * 0x14 + 0x24) != -1) {
          *(u16 *)(iStack_10 + iVar7 * 0x14 + 0x1c) = 0;
          *(u16 *)(iStack_10 + iVar7 * 0x14 + 0x1e) = 0;
          iVar8 = iStack_10 + iVar7 * 0x14;
          *(byte *)(iVar8 + 0x18) = *(byte *)(iVar8 + 0x18) & 0xfe;
        }
      }
    }
    else if (sVar1 == 2) {
      if ((*(byte *)(iStack_10 + iVar7 * 0x14 + 0x18) & 1) != 0) {
        *(u16 *)(iStack_10 + iVar7 * 0x14 + 0x1c) = 3;
        *(u16 *)(iStack_10 + iVar7 * 0x14 + 0x1e) = 0;
      }
    }
    else if (sVar1 == 1) {
      sVar1 = *(short *)(iStack_10 + iVar7 * 0x14 + 0x1e);
      if (sVar1 == 3) {
        lVar6 = CloseHandle__4SdrvFUi(sys__4Sdrv,*(u32 *)(iStack_10 + iVar7 * 0x14 + 0x24));
        if (lVar6 != 0) {
          if ((*(byte *)(iStack_10 + iVar7 * 0x14 + 0x18) & 1) == 0) {
            *(u16 *)(iStack_10 + iVar7 * 0x14 + 0x1e) = 0;
          }
          else {
            *(u16 *)(iStack_10 + iVar7 * 0x14 + 0x1c) = 0;
            iVar8 = iStack_10 + iVar7 * 0x14;
            *(byte *)(iVar8 + 0x18) = *(byte *)(iVar8 + 0x18) & 0xfe;
          }
        }
      }
      else if (sVar1 == 2) {
LAB_00348048:
        lVar6 = CloseHandle__4SdrvFUi(sys__4Sdrv,*(u32 *)(iStack_10 + iVar7 * 0x14 + 0x24));
        if (lVar6 != 0) {
          if ((*(byte *)(iStack_10 + iVar7 * 0x14 + 0x18) & 1) == 0) {
            *(u16 *)(iStack_10 + iVar7 * 0x14 + 0x1c) = 2;
            *(u16 *)(iStack_10 + iVar7 * 0x14 + 0x1e) = 0;
          }
          else {
            *(u16 *)(iStack_10 + iVar7 * 0x14 + 0x1c) = 3;
            *(u16 *)(iStack_10 + iVar7 * 0x14 + 0x1e) = 0;
          }
        }
      }
      else if (sVar1 == 1) {
LAB_00347f68:
        unaff_s1 = GetStatus__4SdrvFUi(sys__4Sdrv,*(u32 *)(iStack_10 + iVar7 * 0x14 + 0x24));
        if ((unaff_s1 == 0) || (unaff_s1 == -2)) {
          *(u16 *)(iStack_10 + iVar7 * 0x14 + 0x1e) = 3;
        }
        else if (unaff_s1 == 3) {
          uVar5 = GetOption__4SdrvFUi(sys__4Sdrv,*(u32 *)(iStack_10 + iVar7 * 0x14 + 0x24));
          *(u32 *)(iStack_10 + iVar7 * 0x14 + 0x28) = uVar5;
          *(u16 *)(iStack_10 + iVar7 * 0x14 + 0x1e) = 2;
          goto LAB_00348048;
        }
      }
      else if (sVar1 == 0) {
        uVar5 = AutoLoad__4SdrvFPvPv(sys__4Sdrv,*(u32 *)(iStack_10 + iVar7 * 0x14 + 0x20),0);
        *(u32 *)(iStack_10 + iVar7 * 0x14 + 0x24) = uVar5;
        if (*(int *)(iStack_10 + iVar7 * 0x14 + 0x24) != -1) {
          *(u16 *)(iStack_10 + iVar7 * 0x14 + 0x1e) = 1;
          goto LAB_00347f68;
        }
        if ((*(byte *)(iStack_10 + iVar7 * 0x14 + 0x18) & 1) != 0) {
          *(u16 *)(iStack_10 + iVar7 * 0x14 + 0x1c) = 0;
          iVar8 = iStack_10 + iVar7 * 0x14;
          *(byte *)(iVar8 + 0x18) = *(byte *)(iVar8 + 0x18) & 0xfe;
        }
      }
    }
  }
  sVar1 = *(short *)(iStack_10 + 0x3c4);
  if (sVar1 == 3) {
    sVar1 = *(short *)(iStack_10 + 0x3c6);
    if (sVar1 == 2) {
      uVar5 = ReleaseBGM__4SdrvFUii(sys__4Sdrv,*(u32 *)(iStack_10 + 0x3cc),0);
      *(u32 *)(iStack_10 + 0x3c8) = uVar5;
      if (*(int *)(iStack_10 + 0x3c8) != -1) {
        *(u16 *)(iStack_10 + 0x3c4) = 0;
        *(u16 *)(iStack_10 + 0x3c6) = 0;
        *(byte *)(iStack_10 + 0x3c0) = *(byte *)(iStack_10 + 0x3c0) & 0xfe;
      }
    }
    else if ((sVar1 != 1) && (sVar1 == 0)) {
      uVar5 = StopBGM__4SdrvFUiii(sys__4Sdrv,*(u32 *)(iStack_10 + 0x3cc),
                                  *(u32 *)(iStack_10 + 0x3e4),
                                  *(u32 *)(iStack_10 + 1000));
      *(u32 *)(iStack_10 + 0x3c8) = uVar5;
      if (*(int *)(iStack_10 + 0x3c8) != -1) {
        *(u16 *)(iStack_10 + 0x3c6) = 1;
      }
    }
  }
  else if (sVar1 == 2) {
    if ((*(byte *)(iStack_10 + 0x3c0) & 1) != 0) {
      *(u16 *)(iStack_10 + 0x3c4) = 3;
      *(u16 *)(iStack_10 + 0x3c6) = 0;
    }
  }
  else if (sVar1 == 1) {
    sVar1 = *(short *)(iStack_10 + 0x3c6);
    if (sVar1 == 3) {
      lVar6 = CloseHandle__4SdrvFUi(sys__4Sdrv,*(u32 *)(iStack_10 + 0x3c8));
      if (lVar6 != 0) {
        if ((*(byte *)(iStack_10 + 0x3c0) & 1) == 0) {
          *(u16 *)(iStack_10 + 0x3c6) = 0;
        }
        else {
          *(u16 *)(iStack_10 + 0x3c4) = 0;
          *(byte *)(iStack_10 + 0x3c0) = *(byte *)(iStack_10 + 0x3c0) & 0xfe;
        }
      }
    }
    else {
      if (sVar1 != 2) {
        if (sVar1 != 1) {
          if (sVar1 != 0) goto LAB_00348798;
          uVar5 = PlayBGM__4SdrvFUiiiP9_BgmParam
                            (sys__4Sdrv,*(u32 *)(iStack_10 + 0x3e0),
                             *(u32 *)(iStack_10 + 0x3e4),*(u32 *)(iStack_10 + 1000),
                             iStack_10 + 0x3d0);
          *(u32 *)(iStack_10 + 0x3c8) = uVar5;
          if (*(int *)(iStack_10 + 0x3c8) == -1) {
            if ((*(byte *)(iStack_10 + 0x3c0) & 1) != 0) {
              *(u16 *)(iStack_10 + 0x3c4) = 0;
              *(byte *)(iStack_10 + 0x3c0) = *(byte *)(iStack_10 + 0x3c0) & 0xfe;
            }
            goto LAB_00348798;
          }
          *(u16 *)(iStack_10 + 0x3c6) = 1;
        }
        unaff_s1 = GetStatus__4SdrvFUi(sys__4Sdrv,*(u32 *)(iStack_10 + 0x3c8));
        if (unaff_s1 == -2) {
          *(byte *)(iStack_10 + 0x3c0) = *(byte *)(iStack_10 + 0x3c0) & 0xfe | 1;
          *(u16 *)(iStack_10 + 0x3c6) = 3;
          goto LAB_00348798;
        }
        if (unaff_s1 == 0) {
          *(u16 *)(iStack_10 + 0x3c6) = 3;
          goto LAB_00348798;
        }
        if (unaff_s1 != 3) goto LAB_00348798;
        uVar5 = GetOption__4SdrvFUi(sys__4Sdrv,*(u32 *)(iStack_10 + 0x3c8));
        *(u32 *)(iStack_10 + 0x3cc) = uVar5;
        *(u16 *)(iStack_10 + 0x3c6) = 2;
      }
      lVar6 = CloseHandle__4SdrvFUi(sys__4Sdrv,*(u32 *)(iStack_10 + 0x3c8));
      if (lVar6 != 0) {
        if ((*(byte *)(iStack_10 + 0x3c0) & 1) == 0) {
          *(u16 *)(iStack_10 + 0x3c4) = 2;
          *(u16 *)(iStack_10 + 0x3c6) = 0;
        }
        else {
          *(u16 *)(iStack_10 + 0x3c4) = 3;
          *(u16 *)(iStack_10 + 0x3c6) = 0;
        }
      }
    }
  }
LAB_00348798:
  iVar7 = 0;
  do {
    if (0xf < iVar7) {
      return 0;
    }
    sVar1 = *(short *)(iStack_10 + iVar7 * 0x30 + 0xc2);
    if (sVar1 == 3) {
      sVar1 = *(short *)(iStack_10 + iVar7 * 0x30 + 0xc4);
      if (sVar1 == 3) {
        lVar6 = CloseHandle__4SdrvFUi(sys__4Sdrv,*(u32 *)(iStack_10 + iVar7 * 0x30 + 0xcc));
        if (lVar6 != 0) {
          if (*(char *)(iStack_10 + iVar7 * 0x30 + 0xc1) == '\0') {
            *(u16 *)(iStack_10 + iVar7 * 0x30 + 0xc4) = 0;
          }
          else {
            SETblEntry__6HNMSndFi(iStack_10,iVar7);
          }
        }
      }
      else if (sVar1 == 2) {
LAB_00349818:
        lVar6 = CloseHandle__4SdrvFUi(sys__4Sdrv,*(u32 *)(iStack_10 + iVar7 * 0x30 + 0xcc));
        if (lVar6 != 0) {
          SETblEntry__6HNMSndFi(iStack_10,iVar7);
        }
      }
      else if (sVar1 == 1) {
LAB_00349730:
        unaff_s1 = GetStatus__4SdrvFUi(sys__4Sdrv,*(u32 *)(iStack_10 + iVar7 * 0x30 + 0xcc));
        if (unaff_s1 == -2) {
          *(u16 *)(iStack_10 + iVar7 * 0x30 + 0xc4) = 2;
        }
        else if (unaff_s1 == 0) {
          *(u16 *)(iStack_10 + iVar7 * 0x30 + 0xc4) = 3;
        }
        else if (unaff_s1 == 3) {
          unaff_s1 = GetOption__4SdrvFUi(sys__4Sdrv,*(u32 *)(iStack_10 + iVar7 * 0x30 + 0xcc)
                                        );
          *(u16 *)(iStack_10 + iVar7 * 0x30 + 0xc4) = 2;
          goto LAB_00349818;
        }
      }
      else if (sVar1 == 0) {
        uVar5 = ReleaseSE__4SdrvFUii(sys__4Sdrv,*(u16 *)(iStack_10 + iVar7 * 0x30 + 0xc6),1);
        *(u32 *)(iStack_10 + iVar7 * 0x30 + 0xcc) = uVar5;
        if (*(int *)(iStack_10 + iVar7 * 0x30 + 0xcc) != -1) {
          *(u16 *)(iStack_10 + iVar7 * 0x30 + 0xc4) = 1;
          goto LAB_00349730;
        }
        if (*(char *)(iStack_10 + iVar7 * 0x30 + 0xc1) != '\0') {
          SETblEntry__6HNMSndFi(iStack_10,iVar7);
        }
      }
    }
    else if (sVar1 == 2) {
      if ((long)((ulong)*(byte *)(iStack_10 + iVar7 * 0x30 + 0xc0) << 0x39) < 0) {
        SEStereoReset__6HNMSndFi(iStack_10,iVar7);
      }
      sVar1 = *(short *)(iStack_10 + iVar7 * 0x30 + 0xc4);
      if (sVar1 == 4) {
        lVar6 = CloseHandle__4SdrvFUi(sys__4Sdrv,*(u32 *)(iStack_10 + iVar7 * 0x30 + 0xcc));
        if (lVar6 != 0) {
          if (*(char *)(iStack_10 + iVar7 * 0x30 + 0xc1) == '\0') {
            if ((*(byte *)(iStack_10 + iVar7 * 0x30 + 0xc0) & 1) == 0) {
              *(u16 *)(iStack_10 + iVar7 * 0x30 + 0xc4) = 0;
              iVar8 = iStack_10 + iVar7 * 0x30;
              *(byte *)(iVar8 + 0xc0) = *(byte *)(iVar8 + 0xc0) & 0xfb;
            }
            else {
              *(u16 *)(iStack_10 + iVar7 * 0x30 + 0xc2) = 3;
              *(u16 *)(iStack_10 + iVar7 * 0x30 + 0xc4) = 0;
              iVar8 = iStack_10 + iVar7 * 0x30;
              *(byte *)(iVar8 + 0xc0) = *(byte *)(iVar8 + 0xc0) & 0xfb;
            }
          }
          else {
            SETblEntry__6HNMSndFi(iStack_10,iVar7);
          }
        }
      }
      else if (sVar1 == 3) {
LAB_00349288:
        lVar6 = CloseHandle__4SdrvFUi(sys__4Sdrv,*(u32 *)(iStack_10 + iVar7 * 0x30 + 0xcc));
        if (lVar6 != 0) {
          if (*(char *)(iStack_10 + iVar7 * 0x30 + 0xc1) == '\0') {
            if ((*(byte *)(iStack_10 + iVar7 * 0x30 + 0xc0) & 1) == 0) {
              if (unaff_s1 == 1) {
                *(u16 *)(iStack_10 + iVar7 * 0x30 + 0xc4) = 0;
                iVar8 = iStack_10 + iVar7 * 0x30;
                *(byte *)(iVar8 + 0xc0) = *(byte *)(iVar8 + 0xc0) & 0xfb;
              }
              else if (unaff_s1 == 0) {
                iVar8 = iStack_10 + iVar7 * 0x30;
                *(byte *)(iVar8 + 0xc0) = *(byte *)(iVar8 + 0xc0) & 0xf7 | 8;
                *(u16 *)(iStack_10 + iVar7 * 0x30 + 0xc2) = 3;
                *(u16 *)(iStack_10 + iVar7 * 0x30 + 0xc4) = 0;
                iVar8 = iStack_10 + iVar7 * 0x30;
                *(byte *)(iVar8 + 0xc0) = *(byte *)(iVar8 + 0xc0) & 0xfb;
              }
              else {
                SETblEntry__6HNMSndFi(iStack_10,iVar7);
              }
            }
            else {
              *(u16 *)(iStack_10 + iVar7 * 0x30 + 0xc2) = 3;
              *(u16 *)(iStack_10 + iVar7 * 0x30 + 0xc4) = 0;
              iVar8 = iStack_10 + iVar7 * 0x30;
              *(byte *)(iVar8 + 0xc0) = *(byte *)(iVar8 + 0xc0) & 0xfb;
            }
          }
          else {
            SETblEntry__6HNMSndFi(iStack_10,iVar7);
          }
        }
      }
      else if (sVar1 == 2) {
LAB_00349170:
        unaff_s1 = GetStatus__4SdrvFUi(sys__4Sdrv,*(u32 *)(iStack_10 + iVar7 * 0x30 + 0xcc));
        if (unaff_s1 == -2) {
          iVar8 = iStack_10 + iVar7 * 0x30;
          *(byte *)(iVar8 + 0xc0) = *(byte *)(iVar8 + 0xc0) & 0xfe | 1;
          *(u16 *)(iStack_10 + iVar7 * 0x30 + 0xc4) = 4;
        }
        else if (unaff_s1 == 0) {
          *(u16 *)(iStack_10 + iVar7 * 0x30 + 0xc4) = 4;
        }
        else if (unaff_s1 == 3) {
          unaff_s1 = GetOption__4SdrvFUi(sys__4Sdrv,*(u32 *)(iStack_10 + iVar7 * 0x30 + 0xcc)
                                        );
          *(u16 *)(iStack_10 + iVar7 * 0x30 + 0xc4) = 3;
          goto LAB_00349288;
        }
      }
      else if (sVar1 == 1) {
LAB_00349010:
        uVar5 = GetSEStat__4SdrvFUi(sys__4Sdrv,*(u16 *)(iStack_10 + iVar7 * 0x30 + 0xc6));
        *(u32 *)(iStack_10 + iVar7 * 0x30 + 0xcc) = uVar5;
        if (*(int *)(iStack_10 + iVar7 * 0x30 + 0xcc) != -1) {
          *(u16 *)(iStack_10 + iVar7 * 0x30 + 0xc4) = 2;
          goto LAB_00349170;
        }
        if (*(char *)(iStack_10 + iVar7 * 0x30 + 0xc1) == '\0') {
          if ((*(byte *)(iStack_10 + iVar7 * 0x30 + 0xc0) & 1) != 0) {
            *(u16 *)(iStack_10 + iVar7 * 0x30 + 0xc2) = 3;
            *(u16 *)(iStack_10 + iVar7 * 0x30 + 0xc4) = 0;
            iVar8 = iStack_10 + iVar7 * 0x30;
            *(byte *)(iVar8 + 0xc0) = *(byte *)(iVar8 + 0xc0) & 0xfb;
          }
        }
        else {
          SETblEntry__6HNMSndFi(iStack_10,iVar7);
        }
      }
      else if (sVar1 == 0) {
        if (*(char *)(iStack_10 + iVar7 * 0x30 + 0xc1) == '\0') {
          if ((*(byte *)(iStack_10 + iVar7 * 0x30 + 0xc0) & 1) == 0) {
            if ((long)((ulong)*(byte *)(iStack_10 + iVar7 * 0x30 + 0xc0) << 0x3d) < 0) {
              *(u16 *)(iStack_10 + iVar7 * 0x30 + 0xc4) = 1;
              iVar8 = iStack_10 + iVar7 * 0x30;
              *(byte *)(iVar8 + 0xc0) = *(byte *)(iVar8 + 0xc0) & 0xf7;
              iVar8 = iStack_10 + iVar7 * 0x30;
              *(byte *)(iVar8 + 0xc0) = *(byte *)(iVar8 + 0xc0) & 0xef;
              goto LAB_00349010;
            }
          }
          else {
            *(u16 *)(iStack_10 + iVar7 * 0x30 + 0xc2) = 3;
            *(u16 *)(iStack_10 + iVar7 * 0x30 + 0xc4) = 0;
            iVar8 = iStack_10 + iVar7 * 0x30;
            *(byte *)(iVar8 + 0xc0) = *(byte *)(iVar8 + 0xc0) & 0xfb;
          }
        }
        else {
          SETblEntry__6HNMSndFi(iStack_10,iVar7);
        }
      }
    }
    else if (sVar1 == 1) {
      sVar1 = *(short *)(iStack_10 + iVar7 * 0x30 + 0xc4);
      if (sVar1 == 3) {
        lVar6 = CloseHandle__4SdrvFUi(sys__4Sdrv,*(u32 *)(iStack_10 + iVar7 * 0x30 + 0xcc));
        if (lVar6 != 0) {
          if (*(char *)(iStack_10 + iVar7 * 0x30 + 0xc1) == '\0') {
            if ((*(byte *)(iStack_10 + iVar7 * 0x30 + 0xc0) & 1) == 0) {
              *(u16 *)(iStack_10 + iVar7 * 0x30 + 0xc4) = 0;
              if ((long)((ulong)*(byte *)(iStack_10 + iVar7 * 0x30 + 0xc0) << 0x39) < 0) {
                SEStereoReset__6HNMSndFi(iStack_10,iVar7);
              }
            }
            else {
              SETblEntry__6HNMSndFi(iStack_10,iVar7);
            }
          }
          else {
            SETblEntry__6HNMSndFi(iStack_10,iVar7);
          }
        }
      }
      else if (sVar1 == 2) {
LAB_00348b28:
        if ((long)((ulong)*(byte *)(iStack_10 + iVar7 * 0x30 + 0xc0) << 0x39) < 0) {
          SEStereoReset__6HNMSndFi(iStack_10,iVar7);
        }
        lVar6 = CloseHandle__4SdrvFUi(sys__4Sdrv,*(u32 *)(iStack_10 + iVar7 * 0x30 + 0xcc));
        if (lVar6 != 0) {
          if (*(char *)(iStack_10 + iVar7 * 0x30 + 0xc1) == '\0') {
            if (*(short *)(iStack_10 + iVar7 * 0x30 + 0xc6) == -1) {
              SETblEntry__6HNMSndFi(iStack_10,iVar7);
            }
            else if ((*(byte *)(iStack_10 + iVar7 * 0x30 + 0xc0) & 1) == 0) {
              *(u16 *)(iStack_10 + iVar7 * 0x30 + 0xc2) = 2;
              *(u16 *)(iStack_10 + iVar7 * 0x30 + 0xc4) = 0;
              iVar8 = iStack_10 + iVar7 * 0x30;
              *(byte *)(iVar8 + 0xc0) = *(byte *)(iVar8 + 0xc0) & 0xfb | 4;
            }
            else {
              *(u16 *)(iStack_10 + iVar7 * 0x30 + 0xc2) = 3;
              *(u16 *)(iStack_10 + iVar7 * 0x30 + 0xc4) = 0;
            }
          }
          else {
            SETblEntry__6HNMSndFi(iStack_10,iVar7);
          }
        }
      }
      else if (sVar1 == 1) {
LAB_003489a8:
        unaff_s1 = GetStatus__4SdrvFUi(sys__4Sdrv,*(u32 *)(iStack_10 + iVar7 * 0x30 + 0xcc));
        if (unaff_s1 == -2) {
          iVar8 = iStack_10 + iVar7 * 0x30;
          *(byte *)(iVar8 + 0xc0) = *(byte *)(iVar8 + 0xc0) & 0xfe | 1;
          *(u16 *)(iStack_10 + iVar7 * 0x30 + 0xc4) = 3;
        }
        else if (unaff_s1 == 0) {
          *(u16 *)(iStack_10 + iVar7 * 0x30 + 0xc4) = 3;
        }
        else if (unaff_s1 == 3) {
          uVar4 = GetOption__4SdrvFUi(sys__4Sdrv,*(u32 *)(iStack_10 + iVar7 * 0x30 + 0xcc));
          *(u16 *)(iStack_10 + iVar7 * 0x30 + 0xc6) = uVar4;
          if ((long)((ulong)*(byte *)(iStack_10 + iVar7 * 0x30 + 0xc0) << 0x39) < 0) {
            SEStereoReset__6HNMSndFi(iStack_10,iVar7);
          }
          *(u16 *)(iStack_10 + iVar7 * 0x30 + 0xc4) = 2;
          goto LAB_00348b28;
        }
      }
      else if (sVar1 == 0) {
        if ((*(byte *)(iStack_10 + iVar7 * 0x30 + 0xc0) & 1) == 0) {
          if ((long)((ulong)*(byte *)(iStack_10 + iVar7 * 0x30 + 0xc0) << 0x39) < 0) {
            SEStereoReset__6HNMSndFi(iStack_10,iVar7);
          }
          uVar5 = PlaySE__4SdrvFUiP8_SeParam
                            (sys__4Sdrv,*(u32 *)(iStack_10 + iVar7 * 0x30 + 200),
                             iStack_10 + iVar7 * 0x30 + 0xe0);
          *(u32 *)(iStack_10 + iVar7 * 0x30 + 0xcc) = uVar5;
          iVar8 = iStack_10 + iVar7 * 0x30;
          *(byte *)(iVar8 + 0xc0) = *(byte *)(iVar8 + 0xc0) & 0xfd;
          if (*(int *)(iStack_10 + iVar7 * 0x30 + 0xcc) != -1) {
            *(u16 *)(iStack_10 + iVar7 * 0x30 + 0xc4) = 1;
            goto LAB_003489a8;
          }
        }
        else {
          SETblEntry__6HNMSndFi(iStack_10,iVar7);
        }
      }
    }
    iVar7 = iVar7 + 1;
  } while( true );
}

/* ---- 0x00349940 size 0x1d0  HNMSnd::ReleaseCheck(v)
 *      mangled: ReleaseCheck__6HNMSndFv */
u32 ReleaseCheck__6HNMSndFv(int param_1)

{
  u32 uVar1;
  int iVar2;
  
  iVar2 = 0;
  while( true ) {
    if (7 < iVar2) {
      iVar2 = 0;
      while( true ) {
        if (0xf < iVar2) {
          if ((*(short *)(param_1 + 0x3c4) == 3) ||
             ((*(short *)(param_1 + 0x3c4) != 0 && ((*(byte *)(param_1 + 0x3c0) & 1) != 0)))) {
            uVar1 = 0;
          }
          else {
            uVar1 = 1;
          }
          return uVar1;
        }
        if ((*(short *)(param_1 + iVar2 * 0x30 + 0xc2) == 3) ||
           ((*(short *)(param_1 + iVar2 * 0x30 + 0xc2) != 0 &&
            ((*(byte *)(param_1 + iVar2 * 0x30 + 0xc0) & 1) != 0)))) break;
        iVar2 = iVar2 + 1;
      }
      return 0;
    }
    if ((*(short *)(param_1 + iVar2 * 0x14 + 0x1c) == 3) ||
       ((*(short *)(param_1 + iVar2 * 0x14 + 0x1c) != 0 &&
        ((*(byte *)(param_1 + iVar2 * 0x14 + 0x18) & 1) != 0)))) break;
    iVar2 = iVar2 + 1;
  }
  return 0;
}

/* ---- 0x00349b10 size 0xf8  HNMSnd::IOPEntry(PUc)
 *      mangled: IOPEntry__6HNMSndFPUc */
int IOPEntry__6HNMSndFPUc(int param_1,u32 param_2)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  while( true ) {
    if (7 < iVar2) {
      return -1;
    }
    if (*(short *)(param_1 + iVar2 * 0x14 + 0x1c) == 0) break;
    iVar2 = iVar2 + 1;
  }
  iVar1 = param_1 + iVar2 * 0x14;
  *(byte *)(iVar1 + 0x18) = *(byte *)(iVar1 + 0x18) & 0xfe;
  *(u16 *)(param_1 + iVar2 * 0x14 + 0x1c) = 1;
  *(u16 *)(param_1 + iVar2 * 0x14 + 0x1e) = 0;
  *(u32 *)(param_1 + iVar2 * 0x14 + 0x20) = param_2;
  return iVar2;
}

/* ---- 0x00349c10 size 0x9c  HNMSnd::IOPEntryCheck(i)
 *      mangled: IOPEntryCheck__6HNMSndFi */
u32 IOPEntryCheck__6HNMSndFi(int param_1,int param_2)

{
  u32 uVar1;
  
  if (*(short *)(param_1 + param_2 * 0x14 + 0x1c) == 2) {
    uVar1 = 1;
  }
  else if (*(short *)(param_1 + param_2 * 0x14 + 0x1c) == 1) {
    uVar1 = 0;
  }
  else {
    uVar1 = 0xffffffff;
  }
  return uVar1;
}

/* ---- 0x00349cb0 size 0x178  HNMSnd::IOPRelease(i)
 *      mangled: IOPRelease__6HNMSndFi */
void IOPRelease__6HNMSndFi(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  if (param_2 == -1) {
    for (iVar2 = 0; iVar2 < 8; iVar2 = iVar2 + 1) {
      if ((*(short *)(param_1 + iVar2 * 0x14 + 0x1c) != 3) &&
         (*(short *)(param_1 + iVar2 * 0x14 + 0x1c) != 0)) {
        iVar1 = param_1 + iVar2 * 0x14;
        *(byte *)(iVar1 + 0x18) = *(byte *)(iVar1 + 0x18) & 0xfe | 1;
      }
    }
  }
  else if ((*(short *)(param_1 + param_2 * 0x14 + 0x1c) != 3) &&
          (*(short *)(param_1 + param_2 * 0x14 + 0x1c) != 0)) {
    param_1 = param_1 + param_2 * 0x14;
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfe | 1;
  }
  return;
}

/* ---- 0x00349e30 size 0xb4  HNMSnd::IsIOPRelease(i)
 *      mangled: IsIOPRelease__6HNMSndFi */
u32 IsIOPRelease__6HNMSndFi(int param_1,int param_2)

{
  u32 uVar1;
  
  if (((*(short *)(param_1 + param_2 * 0x14 + 0x1c) == 3) ||
      (*(short *)(param_1 + param_2 * 0x14 + 0x1c) == 0)) ||
     ((*(byte *)(param_1 + param_2 * 0x14 + 0x18) & 1) != 0)) {
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

/* ---- 0x00349ef0 size 0xc4  HNMSnd::IOPReleaseCheck(i)
 *      mangled: IOPReleaseCheck__6HNMSndFi */
u32 IOPReleaseCheck__6HNMSndFi(int param_1,int param_2)

{
  u32 uVar1;
  
  if (*(short *)(param_1 + param_2 * 0x14 + 0x1c) == 0) {
    uVar1 = 1;
  }
  else if ((*(short *)(param_1 + param_2 * 0x14 + 0x1c) == 3) ||
          ((*(byte *)(param_1 + param_2 * 0x14 + 0x18) & 1) != 0)) {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}

/* ---- 0x00349fc0 size 0x12c  HNMSnd::SETblEntry(i)
 *      mangled: SETblEntry__6HNMSndFi */
void SETblEntry__6HNMSndFi(int param_1,int param_2)

{
  int iVar1;
  
  *(char *)(param_1 + *(short *)(param_1 + 0x436) + 0x414) = (char)param_2;
  *(short *)(param_1 + 0x436) = *(short *)(param_1 + 0x436) + 1;
  if (0x1f < *(short *)(param_1 + 0x436)) {
    *(u16 *)(param_1 + 0x436) = 0;
  }
  iVar1 = param_1 + param_2 * 0x30;
  *(byte *)(iVar1 + 0xc0) = *(byte *)(iVar1 + 0xc0) & 0xfe;
  iVar1 = param_1 + param_2 * 0x30;
  *(byte *)(iVar1 + 0xc0) = *(byte *)(iVar1 + 0xc0) & 0xfd;
  *(u8 *)(param_1 + param_2 * 0x30 + 0xc1) = 0;
  *(u16 *)(param_1 + param_2 * 0x30 + 0xc2) = 0;
  *(u16 *)(param_1 + param_2 * 0x30 + 0xc4) = 0;
  return;
}

/* ---- 0x0034a0f0 size 0x67c  HNMSnd::PlaySE(UibP7FVector)
 *      mangled: PlaySE__6HNMSndFUibP7FVector */
uint PlaySE__6HNMSndFUibP7FVector(u64 param_1,int param_2,char param_3,long param_4)

{
  uint uVar1;
  u64 uVar2;
  int iVar3;
  int iVar4;
  u8 uVar5;
  int iVar6;
  float fVar7;
  u8 auVar8 [16];
  u8 auVar9 [16];
  u8 auStack_50 [16];
  u8 auStack_40 [16];
  u8 auStack_30 [8];
  u32 uStack_28;
  u32 uStack_24;
  u8 auStack_20 [4];
  float fStack_1c;
  u8 auStack_10 [16];
  
  iVar6 = (int)param_1;
  if (param_3 == '\0') {
    for (iVar3 = 0; iVar3 < 0x10; iVar3 = iVar3 + 1) {
      if (((*(short *)(iVar6 + iVar3 * 0x30 + 0xc2) == 1) ||
          (*(short *)(iVar6 + iVar3 * 0x30 + 0xc2) == 2)) &&
         (*(int *)(iVar6 + iVar3 * 0x30 + 200) == param_2)) {
        if ((*(short *)(iVar6 + iVar3 * 0x30 + 0xc2) == 1) &&
           (*(short *)(iVar6 + iVar3 * 0x30 + 0xc4) == 0)) {
          SETblEntry__6HNMSndFi(param_1,iVar3);
        }
        else {
          SetSEEnd__6HNMSndFUii(param_1,param_2,iVar3);
        }
      }
    }
  }
  if (*(short *)(iVar6 + 0x434) == *(short *)(iVar6 + 0x436)) {
    uVar1 = 0xffffffff;
  }
  else {
    uVar1 = (uint)*(byte *)(iVar6 + *(short *)(iVar6 + 0x434) + 0x414);
    *(short *)(iVar6 + 0x434) = *(short *)(iVar6 + 0x434) + 1;
    if (0x1f < *(short *)(iVar6 + 0x434)) {
      *(u16 *)(iVar6 + 0x434) = 0;
    }
    uVar5 = 0x7f;
    iVar3 = 0x40;
    iVar4 = iVar6 + uVar1 * 0x30;
    *(byte *)(iVar4 + 0xc0) = *(byte *)(iVar4 + 0xc0) & 0xdf;
    if (param_4 != 0) {
      iVar3 = iVar6 + uVar1 * 0x30;
      *(byte *)(iVar3 + 0xc0) = *(byte *)(iVar3 + 0xc0) & 0xdf | 0x20;
      __ct__7FVectorFPC7FVector(auStack_30,param_4);
      iVar3 = iVar6 + uVar1 * 0x30;
      *(int *)(iVar3 + 0xd0) = auStack_30._0_4_;
      *(int *)(iVar3 + 0xd4) = auStack_30._4_4_;
      *(u32 *)(iVar3 + 0xd8) = uStack_28;
      *(u32 *)(iVar3 + 0xdc) = uStack_24;
      auVar8 = _lqc2(*(u8 (*) [16])param_4);
      auVar9 = _lqc2(*(u8 (*) [16])(*(int *)(Sys__7CBattle + 0x4324) + 0x30));
      auVar8 = _vsub(auVar8,auVar9);
      auStack_50 = _sqc2(auVar8);
      __ct__7FVectorFRC7FVector(auStack_10,auStack_50);
      fVar7 = (float)Length__7FVectorCFv(auStack_10);
      iVar3 = (int)(127.0 - ((fVar7 - 10.0) * 127.0) / 180.0);
      if (iVar3 < 0) {
        iVar3 = 0;
      }
      if (0x7f < iVar3) {
        iVar3 = 0x7f;
      }
      uVar5 = (u8)iVar3;
      uVar2 = __ct__7FVectorFRC7FVector(auStack_40,auStack_10);
      Get3DAngle__F7FVector(auStack_20,uVar2);
      for (fVar7 = -fStack_1c - *(float *)(*(int *)(Sys__7CBattle + 0x4324) + 0x44); fVar7 < -180.0;
          fVar7 = fVar7 + 360.0) {
      }
      for (; 180.0 <= fVar7; fVar7 = fVar7 - 360.0) {
      }
      if (90.0 < fVar7) {
        fVar7 = 180.0 - fVar7;
      }
      if (fVar7 < -90.0) {
        fVar7 = -180.0 - fVar7;
      }
      if (0.0 <= fVar7) {
        if (45.0 < fVar7) {
          fVar7 = 45.0;
        }
        fVar7 = (fVar7 * 63.0) / 45.0 + 64.0;
      }
      else {
        if (fVar7 < -45.0) {
          fVar7 = -45.0;
        }
        fVar7 = 64.0 - (-fVar7 * 64.0) / 45.0;
      }
      iVar3 = (int)fVar7;
      if (iVar3 < 0) {
        iVar3 = 0;
      }
      if (0x7f < iVar3) {
        iVar3 = 0x7f;
      }
    }
    iVar4 = iVar6 + uVar1 * 0x30;
    *(byte *)(iVar4 + 0xc0) = *(byte *)(iVar4 + 0xc0) & 0xfe;
    iVar4 = iVar6 + uVar1 * 0x30;
    *(byte *)(iVar4 + 0xc0) = *(byte *)(iVar4 + 0xc0) & 0xfd;
    iVar4 = iVar6 + uVar1 * 0x30;
    *(byte *)(iVar4 + 0xc0) = *(byte *)(iVar4 + 0xc0) & 0xbf;
    *(u8 *)(iVar6 + uVar1 * 0x30 + 0xc1) = 0;
    *(int *)(iVar6 + uVar1 * 0x30 + 200) = param_2;
    *(u16 *)(iVar6 + uVar1 * 0x30 + 0xc2) = 1;
    *(u16 *)(iVar6 + uVar1 * 0x30 + 0xc4) = 0;
    *(u16 *)(iVar6 + uVar1 * 0x30 + 0xc6) = 0xffff;
    *(u8 *)(iVar6 + uVar1 * 0x30 + 0xe0) = uVar5;
    *(char *)(iVar6 + uVar1 * 0x30 + 0xe1) = (char)iVar3;
    *(u16 *)(iVar6 + uVar1 * 0x30 + 0xe2) = 0;
    *(u16 *)(iVar6 + uVar1 * 0x30 + 0xe4) = 1000;
    *(u16 *)(iVar6 + uVar1 * 0x30 + 0xe6) = 9;
    *(uint *)(iVar6 + uVar1 * 0x30 + 0xe8) = iVar6 + uVar1 * 0x30 + 0xc1;
  }
  return uVar1;
}

/* ---- 0x0034a770 size 0x3e4  HNMSnd::PlaySE2(Uibi)
 *      mangled: PlaySE2__6HNMSndFUibi */
uint PlaySE2__6HNMSndFUibi(int param_1,int param_2,char param_3,u8 param_4)

{
  uint uVar1;
  int iVar2;
  
  for (iVar2 = 0; iVar2 < 0x10; iVar2 = iVar2 + 1) {
    if ((param_3 == '\0') &&
       (((*(short *)(param_1 + iVar2 * 0x30 + 0xc2) == 1 ||
         (*(short *)(param_1 + iVar2 * 0x30 + 0xc2) == 2)) &&
        (*(int *)(param_1 + iVar2 * 0x30 + 200) == param_2)))) {
      if ((*(short *)(param_1 + iVar2 * 0x30 + 0xc2) == 1) &&
         (*(short *)(param_1 + iVar2 * 0x30 + 0xc4) == 0)) {
        SETblEntry__6HNMSndFi(param_1,iVar2);
      }
      else {
        SetSEEnd__6HNMSndFUii(param_1,param_2,iVar2);
      }
    }
  }
  if (*(short *)(param_1 + 0x434) == *(short *)(param_1 + 0x436)) {
    uVar1 = 0xffffffff;
  }
  else {
    uVar1 = (uint)*(byte *)(param_1 + *(short *)(param_1 + 0x434) + 0x414);
    *(short *)(param_1 + 0x434) = *(short *)(param_1 + 0x434) + 1;
    if (0x1f < *(short *)(param_1 + 0x434)) {
      *(u16 *)(param_1 + 0x434) = 0;
    }
    iVar2 = param_1 + uVar1 * 0x30;
    *(byte *)(iVar2 + 0xc0) = *(byte *)(iVar2 + 0xc0) & 0xfe;
    iVar2 = param_1 + uVar1 * 0x30;
    *(byte *)(iVar2 + 0xc0) = *(byte *)(iVar2 + 0xc0) & 0xfd;
    iVar2 = param_1 + uVar1 * 0x30;
    *(byte *)(iVar2 + 0xc0) = *(byte *)(iVar2 + 0xc0) & 0xdf;
    iVar2 = param_1 + uVar1 * 0x30;
    *(byte *)(iVar2 + 0xc0) = *(byte *)(iVar2 + 0xc0) & 0xbf;
    *(u8 *)(param_1 + uVar1 * 0x30 + 0xc1) = 0;
    *(int *)(param_1 + uVar1 * 0x30 + 200) = param_2;
    *(u16 *)(param_1 + uVar1 * 0x30 + 0xc2) = 1;
    *(u16 *)(param_1 + uVar1 * 0x30 + 0xc4) = 0;
    *(u16 *)(param_1 + uVar1 * 0x30 + 0xc6) = 0xffff;
    *(u8 *)(param_1 + uVar1 * 0x30 + 0xe0) = param_4;
    *(u8 *)(param_1 + uVar1 * 0x30 + 0xe1) = 0x40;
    *(u16 *)(param_1 + uVar1 * 0x30 + 0xe2) = 0;
    *(u16 *)(param_1 + uVar1 * 0x30 + 0xe4) = 1000;
    *(u16 *)(param_1 + uVar1 * 0x30 + 0xe6) = 9;
    *(uint *)(param_1 + uVar1 * 0x30 + 0xe8) = param_1 + uVar1 * 0x30 + 0xc1;
  }
  return uVar1;
}

/* ---- 0x0034ab60 size 0x1f0  HNMSnd::SetSEEnd(Uii)
 *      mangled: SetSEEnd__6HNMSndFUii */
void SetSEEnd__6HNMSndFUii(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  
  if (param_3 == -1) {
    for (iVar2 = 0; iVar2 < 0x10; iVar2 = iVar2 + 1) {
      if ((((param_2 == -1) || (*(int *)(param_1 + iVar2 * 0x30 + 200) == param_2)) &&
          (*(short *)(param_1 + iVar2 * 0x30 + 0xc2) != 0)) &&
         (*(short *)(param_1 + iVar2 * 0x30 + 0xc2) != 3)) {
        iVar1 = param_1 + iVar2 * 0x30;
        *(byte *)(iVar1 + 0xc0) = *(byte *)(iVar1 + 0xc0) & 0xfe | 1;
      }
    }
  }
  else if (((param_2 == -1) || (*(int *)(param_1 + param_3 * 0x30 + 200) == param_2)) &&
          ((*(short *)(param_1 + param_3 * 0x30 + 0xc2) != 0 &&
           (*(short *)(param_1 + param_3 * 0x30 + 0xc2) != 3)))) {
    param_1 = param_1 + param_3 * 0x30;
    *(byte *)(param_1 + 0xc0) = *(byte *)(param_1 + 0xc0) & 0xfe | 1;
  }
  return;
}

/* ---- 0x0034ad50 size 0xe4  HNMSnd::SetBtlSEEnd(v)
 *      mangled: SetBtlSEEnd__6HNMSndFv */
void SetBtlSEEnd__6HNMSndFv(int param_1)

{
  int iVar1;
  int iVar2;
  
  for (iVar2 = 0; iVar2 < 0x10; iVar2 = iVar2 + 1) {
    if (((*(short *)(param_1 + iVar2 * 0x30 + 0xc2) != 0) &&
        (*(short *)(param_1 + iVar2 * 0x30 + 0xc2) != 3)) &&
       (*(int *)(param_1 + iVar2 * 0x30 + 200) != 0x50000000)) {
      iVar1 = param_1 + iVar2 * 0x30;
      *(byte *)(iVar1 + 0xc0) = *(byte *)(iVar1 + 0xc0) & 0xfe | 1;
    }
  }
  return;
}

/* ---- 0x0034ae40 size 0x2fc  HNMSnd::SEEndCheck(Uii)
 *      mangled: SEEndCheck__6HNMSndFUii */
u32 SEEndCheck__6HNMSndFUii(int param_1,int param_2,int param_3)

{
  bool bVar1;
  u32 uVar2;
  int iVar3;
  int iVar4;
  
  if (param_3 == -1) {
    if (param_2 == -1) {
      bVar1 = false;
      for (iVar4 = 0; iVar4 < 0x10; iVar4 = iVar4 + 1) {
        if (*(short *)(param_1 + iVar4 * 0x30 + 0xc2) != 0) {
          if (-1 < (long)((ulong)*(byte *)(param_1 + iVar4 * 0x30 + 0xc0) << 0x3d)) {
            iVar3 = param_1 + iVar4 * 0x30;
            *(byte *)(iVar3 + 0xc0) = *(byte *)(iVar3 + 0xc0) & 0xfb | 4;
          }
          bVar1 = true;
        }
      }
      if (bVar1) {
        uVar2 = 0;
      }
      else {
        uVar2 = 1;
      }
    }
    else {
      bVar1 = false;
      for (iVar4 = 0; iVar4 < 0x10; iVar4 = iVar4 + 1) {
        if ((*(short *)(param_1 + iVar4 * 0x30 + 0xc2) != 0) &&
           (*(int *)(param_1 + iVar4 * 0x30 + 200) == param_2)) {
          if (-1 < (long)((ulong)*(byte *)(param_1 + iVar4 * 0x30 + 0xc0) << 0x3d)) {
            iVar3 = param_1 + iVar4 * 0x30;
            *(byte *)(iVar3 + 0xc0) = *(byte *)(iVar3 + 0xc0) & 0xfb | 4;
          }
          bVar1 = true;
        }
      }
      if (bVar1) {
        uVar2 = 0;
      }
      else {
        uVar2 = 1;
      }
    }
  }
  else if (*(short *)(param_1 + param_3 * 0x30 + 0xc2) == 0) {
    uVar2 = 1;
  }
  else if (*(int *)(param_1 + param_3 * 0x30 + 200) == param_2) {
    if (-1 < (long)((ulong)*(byte *)(param_1 + param_3 * 0x30 + 0xc0) << 0x3d)) {
      param_1 = param_1 + param_3 * 0x30;
      *(byte *)(param_1 + 0xc0) = *(byte *)(param_1 + 0xc0) & 0xfb | 4;
    }
    uVar2 = 0;
  }
  else {
    uVar2 = 1;
  }
  return uVar2;
}

/* ---- 0x0034b140 size 0x364  HNMSnd::BtlSEEndCheck(i)
 *      mangled: BtlSEEndCheck__6HNMSndFi */
bool BtlSEEndCheck__6HNMSndFi(int param_1,int param_2)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  
  bVar1 = false;
  for (iVar3 = 0; iVar3 < 0x10; iVar3 = iVar3 + 1) {
    if (*(short *)(param_1 + iVar3 * 0x30 + 0xc2) != 0) {
      if ((*(uint *)(param_1 + iVar3 * 0x30 + 200) < 0x60000000) ||
         (0x7fffffff < *(uint *)(param_1 + iVar3 * 0x30 + 200))) {
        if ((*(uint *)(param_1 + iVar3 * 0x30 + 200) < 0x90000000) ||
           (0x9fffffff < *(uint *)(param_1 + iVar3 * 0x30 + 200))) {
          if (((param_2 == 0) || (*(uint *)(param_1 + iVar3 * 0x30 + 200) < 0x2000000)) ||
             (0x2ffffff < *(uint *)(param_1 + iVar3 * 0x30 + 200))) {
            if (param_2 == 2) {
              if (-1 < (long)((ulong)*(byte *)(param_1 + iVar3 * 0x30 + 0xc0) << 0x3d)) {
                iVar2 = param_1 + iVar3 * 0x30;
                *(byte *)(iVar2 + 0xc0) = *(byte *)(iVar2 + 0xc0) & 0xfb | 4;
              }
              bVar1 = true;
            }
          }
          else {
            if (-1 < (long)((ulong)*(byte *)(param_1 + iVar3 * 0x30 + 0xc0) << 0x3d)) {
              iVar2 = param_1 + iVar3 * 0x30;
              *(byte *)(iVar2 + 0xc0) = *(byte *)(iVar2 + 0xc0) & 0xfb | 4;
            }
            bVar1 = true;
          }
        }
        else {
          if (-1 < (long)((ulong)*(byte *)(param_1 + iVar3 * 0x30 + 0xc0) << 0x3d)) {
            iVar2 = param_1 + iVar3 * 0x30;
            *(byte *)(iVar2 + 0xc0) = *(byte *)(iVar2 + 0xc0) & 0xfb | 4;
          }
          bVar1 = true;
        }
      }
      else {
        if (-1 < (long)((ulong)*(byte *)(param_1 + iVar3 * 0x30 + 0xc0) << 0x3d)) {
          iVar2 = param_1 + iVar3 * 0x30;
          *(byte *)(iVar2 + 0xc0) = *(byte *)(iVar2 + 0xc0) & 0xfb | 4;
        }
        bVar1 = true;
      }
    }
  }
  return !bVar1;
}

/* ---- 0x0034b4b0 size 0x1e4  HNMSnd::SetSEParam(Uiiiii)
 *      mangled: SetSEParam__6HNMSndFUiiiii */
void SetSEParam__6HNMSndFUiiiii
               (int param_1,int param_2,u32 param_3,u32 param_4,u32 param_5,
               int param_6)

{
  int iVar1;
  
  if (param_6 == -1) {
    for (iVar1 = 0; iVar1 < 0x10; iVar1 = iVar1 + 1) {
      if (((*(short *)(param_1 + iVar1 * 0x30 + 0xc2) != 0) &&
          (*(int *)(param_1 + iVar1 * 0x30 + 200) == param_2)) && (-1 < *(short *)(param_1 + 0x96)))
      {
        SetSEParam__4SdrvFUiiii
                  (sys__4Sdrv,*(u16 *)(param_1 + iVar1 * 0x30 + 0xc6),param_3,param_4,param_5
                  );
      }
    }
  }
  else if (((*(short *)(param_1 + param_6 * 0x30 + 0xc2) != 0) &&
           (*(int *)(param_1 + param_6 * 0x30 + 200) == param_2)) &&
          (-1 < *(short *)(param_1 + param_6 * 0x30 + 0xc6))) {
    SetSEParam__4SdrvFUiiii
              (sys__4Sdrv,*(u16 *)(param_1 + param_6 * 0x30 + 0xc6),param_3,param_4,param_5);
  }
  return;
}

/* ---- 0x0034b6a0 size 0x588  HNMSnd::SetSEParam(Ui7FVectori)
 *      mangled: SetSEParam__6HNMSndFUi7FVectori */
void SetSEParam__6HNMSndFUi7FVectori
               (int param_1,int param_2,u8 (*param_3) [16],long param_4)

{
  int iVar1;
  u64 uVar2;
  u32 uVar3;
  u32 uVar4;
  long lVar5;
  int iVar6;
  float fVar7;
  uint uVar8;
  u8 auVar9 [16];
  u8 auVar10 [16];
  u8 auStack_40 [16];
  u8 auStack_30 [16];
  u8 auStack_20 [4];
  float fStack_1c;
  u8 auStack_10 [16];
  
  auVar9 = _lqc2(*param_3);
  auVar10 = _lqc2(*(u8 (*) [16])(*(int *)(Sys__7CBattle + 0x4324) + 0x30));
  auVar9 = _vsub(auVar9,auVar10);
  auStack_40 = _sqc2(auVar9);
  __ct__7FVectorFRC7FVector(auStack_10,auStack_40);
  fVar7 = (float)Length__7FVectorCFv(auStack_10);
  uVar8 = (uint)(127.0 - ((fVar7 - 10.0) * 127.0) / 180.0);
  if ((int)uVar8 < 0) {
    uVar8 = 0;
  }
  if (0x7f < (int)uVar8) {
    uVar8 = 0x7f;
  }
  uVar2 = __ct__7FVectorFRC7FVector(auStack_30,auStack_10);
  Get3DAngle__F7FVector(auStack_20,uVar2);
  for (fVar7 = -fStack_1c - *(float *)(*(int *)(Sys__7CBattle + 0x4324) + 0x44); fVar7 < -180.0;
      fVar7 = fVar7 + 360.0) {
  }
  for (; 180.0 <= fVar7; fVar7 = fVar7 - 360.0) {
  }
  if (90.0 < fVar7) {
    fVar7 = 180.0 - fVar7;
  }
  if (fVar7 < -90.0) {
    fVar7 = -180.0 - fVar7;
  }
  if (0.0 <= fVar7) {
    if (45.0 < fVar7) {
      fVar7 = 45.0;
    }
    fVar7 = (fVar7 * 63.0) / 45.0 + 64.0;
  }
  else {
    if (fVar7 < -45.0) {
      fVar7 = -45.0;
    }
    fVar7 = 64.0 - (-fVar7 * 64.0) / 45.0;
  }
  lVar5 = (long)(int)fVar7;
  if (lVar5 < 0) {
    lVar5 = 0;
  }
  if (0x7f < lVar5) {
    lVar5 = 0x7f;
  }
  if (param_4 == -1) {
    for (iVar6 = 0; iVar6 < 0x10; iVar6 = iVar6 + 1) {
      if (((*(short *)(param_1 + iVar6 * 0x30 + 0xc2) != 0) &&
          (*(int *)(param_1 + iVar6 * 0x30 + 200) == param_2)) &&
         (-1 < *(short *)(param_1 + iVar6 * 0x30 + 0xc6))) {
        iVar1 = param_1 + iVar6 * 0x30;
        uVar2 = *(u64 *)*param_3;
        uVar3 = *(u32 *)(*param_3 + 8);
        uVar4 = *(u32 *)(*param_3 + 0xc);
        *(int *)(iVar1 + 0xd0) = (int)uVar2;
        *(int *)(iVar1 + 0xd4) = (int)((ulong)uVar2 >> 0x20);
        *(u32 *)(iVar1 + 0xd8) = uVar3;
        *(u32 *)(iVar1 + 0xdc) = uVar4;
        if ((*(byte *)(param_1 + iVar6 * 0x30 + 0xe0) != uVar8) ||
           (*(char *)(param_1 + iVar6 * 0x30 + 0xe1) != lVar5)) {
          *(char *)(param_1 + iVar6 * 0x30 + 0xe0) = (char)uVar8;
          *(char *)(param_1 + iVar6 * 0x30 + 0xe1) = (char)lVar5;
          SetSEParam__4SdrvFUiP8_SeParam
                    (sys__4Sdrv,*(u16 *)(param_1 + iVar6 * 0x30 + 0xc6),
                     param_1 + iVar6 * 0x30 + 0xe0);
        }
      }
    }
  }
  else {
    iVar6 = (int)param_4;
    if (((*(short *)(param_1 + iVar6 * 0x30 + 0xc2) != 0) &&
        (*(int *)(param_1 + iVar6 * 0x30 + 200) == param_2)) &&
       (-1 < *(short *)(param_1 + iVar6 * 0x30 + 0xc6))) {
      iVar1 = param_1 + iVar6 * 0x30;
      uVar2 = *(u64 *)*param_3;
      uVar3 = *(u32 *)(*param_3 + 8);
      uVar4 = *(u32 *)(*param_3 + 0xc);
      *(int *)(iVar1 + 0xd0) = (int)uVar2;
      *(int *)(iVar1 + 0xd4) = (int)((ulong)uVar2 >> 0x20);
      *(u32 *)(iVar1 + 0xd8) = uVar3;
      *(u32 *)(iVar1 + 0xdc) = uVar4;
      if ((*(byte *)(param_1 + iVar6 * 0x30 + 0xe0) != uVar8) ||
         (*(char *)(param_1 + iVar6 * 0x30 + 0xe1) != lVar5)) {
        *(char *)(param_1 + iVar6 * 0x30 + 0xe0) = (char)uVar8;
        *(char *)(param_1 + iVar6 * 0x30 + 0xe1) = (char)lVar5;
        SetSEParam__4SdrvFUiP8_SeParam
                  (sys__4Sdrv,*(u16 *)(param_1 + iVar6 * 0x30 + 0xc6),
                   param_1 + iVar6 * 0x30 + 0xe0);
      }
    }
  }
  return;
}

/* ---- 0x0034bc30 size 0xc4  HNMSnd::SetStereoReset(v)
 *      mangled: SetStereoReset__6HNMSndFv */
void SetStereoReset__6HNMSndFv(int param_1)

{
  int iVar1;
  int iVar2;
  
  for (iVar2 = 0; iVar2 < 0x10; iVar2 = iVar2 + 1) {
    if ((*(short *)(param_1 + iVar2 * 0x30 + 0xc2) != 0) &&
       ((long)((ulong)*(byte *)(param_1 + iVar2 * 0x30 + 0xc0) << 0x3a) < 0)) {
      iVar1 = param_1 + iVar2 * 0x30;
      *(byte *)(iVar1 + 0xc0) = *(byte *)(iVar1 + 0xc0) & 0xbf | 0x40;
    }
  }
  return;
}

/* ---- 0x0034bd00 size 0x48c  HNMSnd::SEStereoReset(i)
 *      mangled: SEStereoReset__6HNMSndFi */
void SEStereoReset__6HNMSndFi(int param_1,int param_2)

{
  u64 uVar1;
  long lVar2;
  float fVar3;
  uint uVar4;
  u8 auVar5 [16];
  u8 auVar6 [16];
  u8 auStack_40 [16];
  u8 auStack_30 [16];
  u8 auStack_20 [4];
  float fStack_1c;
  u8 auStack_10 [16];
  
  auVar5 = _lqc2(*(u8 (*) [16])(param_1 + param_2 * 0x30 + 0xd0));
  auVar6 = _lqc2(*(u8 (*) [16])(*(int *)(Sys__7CBattle + 0x4324) + 0x30));
  auVar5 = _vsub(auVar5,auVar6);
  auStack_40 = _sqc2(auVar5);
  __ct__7FVectorFRC7FVector(auStack_10,auStack_40);
  fVar3 = (float)Length__7FVectorCFv(auStack_10);
  uVar4 = (uint)(127.0 - ((fVar3 - 10.0) * 127.0) / 180.0);
  if ((int)uVar4 < 0) {
    uVar4 = 0;
  }
  if (0x7f < (int)uVar4) {
    uVar4 = 0x7f;
  }
  uVar1 = __ct__7FVectorFRC7FVector(auStack_30,auStack_10);
  Get3DAngle__F7FVector(auStack_20,uVar1);
  for (fVar3 = -fStack_1c - *(float *)(*(int *)(Sys__7CBattle + 0x4324) + 0x44); fVar3 < -180.0;
      fVar3 = fVar3 + 360.0) {
  }
  for (; 180.0 <= fVar3; fVar3 = fVar3 - 360.0) {
  }
  if (90.0 < fVar3) {
    fVar3 = 180.0 - fVar3;
  }
  if (fVar3 < -90.0) {
    fVar3 = -180.0 - fVar3;
  }
  if (0.0 <= fVar3) {
    if (45.0 < fVar3) {
      fVar3 = 45.0;
    }
    fVar3 = (fVar3 * 63.0) / 45.0 + 64.0;
  }
  else {
    if (fVar3 < -45.0) {
      fVar3 = -45.0;
    }
    fVar3 = 64.0 - (-fVar3 * 64.0) / 45.0;
  }
  lVar2 = (long)(int)fVar3;
  if (lVar2 < 0) {
    lVar2 = 0;
  }
  if (0x7f < lVar2) {
    lVar2 = 0x7f;
  }
  if ((*(byte *)(param_1 + param_2 * 0x30 + 0xe0) != uVar4) ||
     (*(char *)(param_1 + param_2 * 0x30 + 0xe1) != lVar2)) {
    if (*(short *)(param_1 + param_2 * 0x30 + 0xc6) < 0) {
      if ((*(short *)(param_1 + param_2 * 0x30 + 0xc2) == 1) &&
         (*(short *)(param_1 + param_2 * 0x30 + 0xc4) == 0)) {
        *(char *)(param_1 + param_2 * 0x30 + 0xe0) = (char)uVar4;
        *(char *)(param_1 + param_2 * 0x30 + 0xe1) = (char)lVar2;
        param_1 = param_1 + param_2 * 0x30;
        *(byte *)(param_1 + 0xc0) = *(byte *)(param_1 + 0xc0) & 0xbf;
      }
    }
    else {
      *(char *)(param_1 + param_2 * 0x30 + 0xe0) = (char)uVar4;
      *(char *)(param_1 + param_2 * 0x30 + 0xe1) = (char)lVar2;
      SetSEParam__4SdrvFUiP8_SeParam
                (sys__4Sdrv,*(u16 *)(param_1 + param_2 * 0x30 + 0xc6),
                 param_1 + param_2 * 0x30 + 0xe0);
      param_1 = param_1 + param_2 * 0x30;
      *(byte *)(param_1 + 0xc0) = *(byte *)(param_1 + 0xc0) & 0xbf;
    }
  }
  return;
}

/* ---- 0x0034c190 size 0xcc  HNMSnd::PlayBGM(UiiiP9_BgmParam)
 *      mangled: PlayBGM__6HNMSndFUiiiP9_BgmParam */
u32
PlayBGM__6HNMSndFUiiiP9_BgmParam
          (int param_1,u32 param_2,u32 param_3,u32 param_4,void *param_5)

{
  *(byte *)(param_1 + 0x3c0) = *(byte *)(param_1 + 0x3c0) & 0xfe;
  *(u16 *)(param_1 + 0x3c4) = 1;
  *(u16 *)(param_1 + 0x3c6) = 0;
  *(u32 *)(param_1 + 0x3cc) = 0;
  *(u32 *)(param_1 + 0x3e0) = param_2;
  *(u32 *)(param_1 + 0x3e4) = param_3;
  *(u32 *)(param_1 + 1000) = param_4;
  memcpy((void *)(param_1 + 0x3d0),param_5,0x10);
  *(u16 *)(param_1 + 0x3d6) = 2;
  *(code **)(param_1 + 0x3d8) = BGMCallBack__6HNMSndFUiUiiUi;
  *(int *)(param_1 + 0x3dc) = param_1;
  return 1;
}

/* ---- 0x0034c260 size 0x40  HNMSnd::BGMCallBack(UiUiiUi)
 *      mangled: BGMCallBack__6HNMSndFUiUiiUi */
void BGMCallBack__6HNMSndFUiUiiUi
               (u32 param_1,u32 param_2,u32 param_3,u32 param_4)

{
  BGMCBFunc__6HNMSndFUiUii(param_4,param_1,param_2,param_3);
  return;
}

/* ---- 0x0034c2a0 size 0x8c  HNMSnd::StopBGM(ii)
 *      mangled: StopBGM__6HNMSndFii */
void StopBGM__6HNMSndFii(int param_1,u32 param_2,u32 param_3)

{
  if ((*(short *)(param_1 + 0x3c4) != 0) && (*(short *)(param_1 + 0x3c4) != 3)) {
    *(byte *)(param_1 + 0x3c0) = *(byte *)(param_1 + 0x3c0) & 0xfe | 1;
    *(u32 *)(param_1 + 0x3e4) = param_2;
    *(u32 *)(param_1 + 1000) = param_3;
  }
  return;
}

/* ---- 0x0034c330 size 0x8c  HNMSnd::BGMCBFunc(UiUii)
 *      mangled: BGMCBFunc__6HNMSndFUiUii */
u32 BGMCBFunc__6HNMSndFUiUii(int param_1,int param_2,int param_3,int param_4)

{
  if (((*(int *)(param_1 + 0x3e0) == param_2) && (*(int *)(param_1 + 0x3cc) == param_3)) &&
     (param_4 == 0)) {
    *(short *)(param_1 + 0x3c6) = *(short *)(param_1 + 0x3c6) + 1;
  }
  return 0xffffffff;
}

/* ---- 0x0034c3c0 size 0x44  HNMSnd::BGMEndCheck(v)
 *      mangled: BGMEndCheck__6HNMSndFv */
bool BGMEndCheck__6HNMSndFv(int param_1)

{
  return *(short *)(param_1 + 0x3c4) == 0;
}

/* ---- 0x0034c410 size 0x78  HNMSnd::SetBGMParam(iii)
 *      mangled: SetBGMParam__6HNMSndFiii */
void SetBGMParam__6HNMSndFiii(int param_1,u32 param_2,u32 param_3,u32 param_4)

{
  if ((*(short *)(param_1 + 0x3c4) == 2) && ((*(byte *)(param_1 + 0x3c0) & 1) == 0)) {
    SetBGMParam__4SdrvFUiiii(sys__4Sdrv,*(u32 *)(param_1 + 0x3cc),param_2,param_3,param_4);
  }
  return;
}

/* ---- 0x0034c490 size 0x13c  HNMSnd::SetBtlBGMNumber(i)
 *      mangled: SetBtlBGMNumber__6HNMSndFi */
void SetBtlBGMNumber__6HNMSndFi(int param_1,u32 param_2)

{
  *(u32 *)(param_1 + 0x3ec) = param_2;
  if (*(int *)(param_1 + 0x3ec) < 0) {
    *(byte *)(param_1 + 0x3c1) = *(byte *)(param_1 + 0x3c1) & 0xfb | 4;
  }
  else {
    *(u8 *)(param_1 + 0x3f0) = 1;
    *(u8 *)(param_1 + 0x3f1) = 0;
    *(byte *)(param_1 + 0x3c0) = *(byte *)(param_1 + 0x3c0) & 0xfd;
    *(byte *)(param_1 + 0x3c0) = *(byte *)(param_1 + 0x3c0) & 0xef;
    *(byte *)(param_1 + 0x3c0) = *(byte *)(param_1 + 0x3c0) & 0xf7;
    *(byte *)(param_1 + 0x3c0) = *(byte *)(param_1 + 0x3c0) & 0xfb;
    *(byte *)(param_1 + 0x3c0) = *(byte *)(param_1 + 0x3c0) & 0xdf;
    *(byte *)(param_1 + 0x3c0) = *(byte *)(param_1 + 0x3c0) & 0xbf;
  }
  return;
}

/* ---- 0x0034c5d0 size 0xcc  HNMSnd::SetBtlBGMFadeOut(i)
 *      mangled: SetBtlBGMFadeOut__6HNMSndFi */
void SetBtlBGMFadeOut__6HNMSndFi(int param_1,u32 param_2)

{
  if (((*(char *)(param_1 + 0x3f0) == '\x05') || (*(char *)(param_1 + 0x3f0) == '\a')) &&
     (*(char *)(param_1 + 0x3f1) == '\x01')) {
    *(u8 *)(param_1 + 0x3f0) = 8;
    *(u8 *)(param_1 + 0x3f1) = 0;
    *(u32 *)(param_1 + 0x3f8) = param_2;
  }
  else {
    *(byte *)(param_1 + 0x3c0) = *(byte *)(param_1 + 0x3c0) & 0xfb | 4;
    *(u32 *)(param_1 + 0x3f8) = param_2;
  }
  return;
}

/* ---- 0x0034c6a0 size 0x7c  HNMSnd::SetBtlResultBGMReadEntry(v)
 *      mangled: SetBtlResultBGMReadEntry__6HNMSndFv */
void SetBtlResultBGMReadEntry__6HNMSndFv(int param_1)

{
  if (*(char *)(param_1 + 0x3fc) == '\0') {
    *(u8 *)(param_1 + 0x3fc) = 1;
    *(u8 *)(param_1 + 0x3fd) = 0;
    *(byte *)(param_1 + 0x3c1) = *(byte *)(param_1 + 0x3c1) & 0xfd;
    *(byte *)(param_1 + 0x3c1) = *(byte *)(param_1 + 0x3c1) & 0xfe;
  }
  return;
}

/* ---- 0x0034c720 size 0x44  HNMSnd::SetBtlResultBGMIOPEntry(v)
 *      mangled: SetBtlResultBGMIOPEntry__6HNMSndFv */
void SetBtlResultBGMIOPEntry__6HNMSndFv(int param_1)

{
  if (*(char *)(param_1 + 0x3fc) == '\x02') {
    *(u8 *)(param_1 + 0x3fc) = 3;
    *(u8 *)(param_1 + 0x3fd) = 0;
  }
  return;
}

/* ---- 0x0034c770 size 0x44  HNMSnd::SetBtlResultBGMPlay(v)
 *      mangled: SetBtlResultBGMPlay__6HNMSndFv */
void SetBtlResultBGMPlay__6HNMSndFv(int param_1)

{
  if (*(char *)(param_1 + 0x3fc) == '\x04') {
    *(u8 *)(param_1 + 0x3fc) = 5;
    *(u8 *)(param_1 + 0x3fd) = 0;
  }
  return;
}

/* ---- 0x0034c7c0 size 0x44  HNMSnd::SetBtlResultBGMFadeOut(i)
 *      mangled: SetBtlResultBGMFadeOut__6HNMSndFi */
void SetBtlResultBGMFadeOut__6HNMSndFi(int param_1,u32 param_2)

{
  *(byte *)(param_1 + 0x3c1) = *(byte *)(param_1 + 0x3c1) & 0xfe | 1;
  *(u32 *)(param_1 + 0x408) = param_2;
  return;
}

