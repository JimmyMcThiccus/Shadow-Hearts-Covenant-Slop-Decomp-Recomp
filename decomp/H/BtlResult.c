/*
 * BtlResult.c -- Ghidra decompiler output (SLPM_602.19, JP Furokuban), tidied by tools/E_gen_decomp.py
 * 6 functions. Types: u8/u16/u32/u64 = undefined1/2/4/8. Addresses in comments are JP main-exe addresses.
 */

/* ---- 0x003599a0 size 0x1f4  BtlResult::BtlResult(v)
 *      mangled: __ct__9BtlResultFv */
int __ct__9BtlResultFv(int param_1)

{
  u32 uVar1;
  int iVar2;
  
  __ct__7CPolObjFv(param_1);
  *(u32 *)(param_1 + 0x18) = 0;
  *(u32 *)(param_1 + 0x1c) = 0;
  *(u8 **)(param_1 + 0x20) = __vt__17DelayDeleteObject;
  *(u8 **)(param_1 + 0x14) = __vt__9BtlResult;
  *(u32 *)(param_1 + 0x20) = 0x406df0;
  __construct_array(param_1 + 0x60,0x359ba0,0x34c970,0x114,0xc);
  ourBtlResult__9BtlResult = param_1;
  *(u32 *)(param_1 + 0x24) = 0;
  *(u16 *)(param_1 + 0x28) = 0;
  *(u16 *)(param_1 + 0x2a) = 0;
  uVar1 = GetTimer__7SysToolFv();
  *(u32 *)(param_1 + 0x2c) = uVar1;
  for (iVar2 = 0; iVar2 < 0xc; iVar2 = iVar2 + 1) {
    *(u16 *)(param_1 + iVar2 * 0x114 + 0x60) = 0;
    *(u16 *)(param_1 + iVar2 * 0x114 + 0x62) = 0;
    *(u32 *)(param_1 + iVar2 * 0x114 + 0x160) = 0;
    *(u32 *)(param_1 + iVar2 * 0x114 + 0x168) = 0;
    *(u32 *)(param_1 + iVar2 * 0x114 + 0x164) = 0;
    *(u32 *)(param_1 + iVar2 * 0x114 + 0x16c) = 0;
    *(u32 *)(param_1 + iVar2 * 0x114 + 0x170) = 0;
  }
  *(u32 *)(param_1 + 0xd50) = 0;
  Entry__7CPollerFP7CPolObjib(app__4CApp + 0x48,param_1,0x80,0);
  return param_1;
}

/* ---- 0x00359be0 size 0x3ac  BtlResult::~BtlResult(v)
 *      mangled: __dt__9BtlResultFv */
int __dt__9BtlResultFv(int param_1,short param_2)

{
  int iVar1;
  
  if (param_1 != 0) {
    *(u8 **)(param_1 + 0x14) = __vt__9BtlResult;
    *(u32 *)(param_1 + 0x20) = 0x406df0;
    for (iVar1 = 0; iVar1 < 0xc; iVar1 = iVar1 + 1) {
      if ((long)((ulong)*(byte *)(param_1 + iVar1 * 0x114 + 0x60) << 0x3e) < 0) {
        Release__7MenuObjFv((MenuObj *)(param_1 + iVar1 * 0x114 + 0x6c));
      }
      if ((long)((ulong)*(byte *)(param_1 + iVar1 * 0x114 + 0x60) << 0x3c) < 0) {
        Release__7MenuObjFv((MenuObj *)(param_1 + iVar1 * 0x114 + 0xac));
      }
      if (((ulong)*(ushort *)(param_1 + iVar1 * 0x114 + 0x60) & 0xfff) >> 4 != 0) {
        __destroy_new_array(*(u32 *)(param_1 + iVar1 * 0x114 + 0x160),0x273e20);
      }
      if (*(int *)(param_1 + iVar1 * 0x114 + 0x168) != 0) {
        __destroy_new_array(*(u32 *)(param_1 + iVar1 * 0x114 + 0x168),0x2661a0);
      }
      if (*(int *)(param_1 + iVar1 * 0x114 + 0x164) != 0) {
        __destroy_new_array(*(u32 *)(param_1 + iVar1 * 0x114 + 0x164),0x277890);
      }
      if (*(int *)(param_1 + iVar1 * 0x114 + 0x16c) != 0) {
        __destroy_new_array(*(u32 *)(param_1 + iVar1 * 0x114 + 0x16c),0x2766d0);
      }
      if (*(int *)(param_1 + iVar1 * 0x114 + 0x170) != 0) {
        __destroy_new_array(*(u32 *)(param_1 + iVar1 * 0x114 + 0x170),0x28d070);
      }
    }
    if (*(int *)(param_1 + 0xd50) != 0) {
      iVar1 = *(int *)(param_1 + 0xd50);
      if (iVar1 != 0) {
        (**(code **)(*(int *)(iVar1 + 8) + 8))(iVar1,1);
      }
    }
    ourBtlResult__9BtlResult = 0;
    __destroy_arr(param_1 + 0x60,0x34c970,0x114,0xc);
    if (param_1 != -0x18) {
      *(u8 **)(param_1 + 0x20) = __vt__17DelayDeleteObject;
    }
    __dt__7CPolObjFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* ---- 0x00359f90 size 0x1f44  BtlResult::Polling(v)
 *      mangled: Polling__9BtlResultFv */
/* WARNING: Heritage AFTER dead removal. Example location: s0xffffffcc : 0x0035be5c */
/* WARNING: Restarted to delay deadcode elimination for space: stack */

u32 Polling__9BtlResultFv(int param_1)

{
  short sVar1;
  bool bVar2;
  bool bVar3;
  char cVar4;
  byte bVar5;
  int iVar6;
  int iVar7;
  int *piVar8;
  int iVar9;
  int iVar10;
  u32 uVar11;
  long lVar12;
  uint uVar13;
  int iVar14;
  ushort *extraout_a1_lo;
  ushort *p2;
  void *p3;
  uint uVar15;
  ulong uVar16;
  
  iVar14 = ourBtlSocket__9BtlSocket;
  iVar6 = ourBtlSocket__9BtlSocket + 0x16c;
  iVar7 = ourBtlSocket__9BtlSocket + 0x38;
  piVar8 = (int *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) +
                   (uint)(byte)ourBtlSaveDat__10BtlSaveSec[1] * 4 + 4);
  iVar9 = GetActive__4CPadFi(0);
  if ((*(ushort *)((&m_pCoreArray__4CPad)[*(int *)(iVar9 + 4)] + 0x6c) & 0x2000) != 0) {
    *(byte *)(param_1 + 0x24) = *(byte *)(param_1 + 0x24) & 0xfd | 2;
  }
  iVar10 = GetTimer__7SysToolFv();
  iVar9 = *(int *)(param_1 + 0x2c);
  *(int *)(param_1 + 0x2c) = iVar10;
  WinSequence__9BtlResultFv(param_1);
  sVar1 = *(short *)(param_1 + 0x28);
  if (sVar1 == 4) {
    bVar2 = false;
    for (iVar14 = 0; iVar14 < 0xc; iVar14 = iVar14 + 1) {
      if ((*(short *)(param_1 + iVar14 * 0x114 + 0x62) == 1) ||
         (*(short *)(param_1 + iVar14 * 0x114 + 0x62) == 0xc)) {
        bVar2 = true;
      }
    }
    if (*(int *)(param_1 + 0xd50) != 0) {
      iVar14 = *(int *)(param_1 + 0xd50);
      if ((long)((ulong)*(byte *)(iVar14 + 0x23) << 0x3c) < 0) {
        if ((*(char *)(iVar14 + 0x100) == '\x01') || (*(char *)(iVar14 + 0x100) == '\0')) {
          bVar3 = true;
        }
        else {
          bVar3 = false;
        }
      }
      else {
        bVar3 = true;
      }
      if (!bVar3) {
        bVar2 = true;
      }
    }
    if (!bVar2) {
      if (*(int *)(param_1 + 0xd50) != 0) {
        ReleaseOT__7MenuObjFv((MenuObj *)(*(int *)(param_1 + 0xd50) + 0x58));
      }
      SetMode__8BtlFaderFsf7_rgba32(0,1,0);
      (**(code **)(*(int *)(param_1 + 0x20) + 0xc))();
      return 1;
    }
  }
  else if (sVar1 == 3) {
    lVar12 = 0;
    while (lVar12 < *(char *)(iVar14 + 0x47)) {
      uVar15 = (uint)lVar12;
      if (((((ulong)*(ushort *)(param_1 + 0x24) & 0x3ff) >> 2 & (long)(1 << (uVar15 & 0x1f))) != 0)
         && (*(float *)(param_1 + uVar15 * 4 + 0xdbc) != 0.0)) {
        if ((long)((ulong)*(byte *)(param_1 + 0x24) << 0x3e) < 0) {
          *(u32 *)(param_1 + uVar15 * 4 + 0xdbc) = 0;
        }
        else {
          iVar6 = param_1 + uVar15 * 4;
          *(float *)(iVar6 + 0xdbc) =
               *(float *)(iVar6 + 0xdbc) - *(float *)(param_1 + uVar15 * 4 + 0xdbc) / 4.0;
          if (*(float *)(param_1 + uVar15 * 4 + 0xdbc) < 0.01) {
            *(u32 *)(param_1 + uVar15 * 4 + 0xdbc) = 0;
          }
        }
        WinCreate__9BtlResultFi(param_1,uVar15 + 2);
      }
      lVar12 = (long)(int)(uVar15 + 1);
    }
    if (*(short *)(param_1 + 0x2a) == 1) {
      if ((long)*(int *)(param_1 + 0x30) < (long)*(char *)(iVar14 + 0x47)) {
        Close__10MenuWindowFUci
                  ((MenuWindow *)(param_1 + (*(int *)(param_1 + 0x30) + 2) * 0x114 + 0xac),3,0x14d);
        *(u16 *)(param_1 + (*(int *)(param_1 + 0x30) + 2) * 0x114 + 0x62) = 0xc;
        *(u16 *)(param_1 + (*(int *)(param_1 + 0x30) + 2) * 0x114 + 100) = 0;
        *(int *)(param_1 + 0x30) = *(int *)(param_1 + 0x30) + 1;
      }
      else {
        *(u16 *)(param_1 + 0x28) = 4;
        *(u16 *)(param_1 + 0x2a) = 0;
      }
    }
    else if ((*(short *)(param_1 + 0x2a) == 0) &&
            ((long)((ulong)*(byte *)(param_1 + 0x24) << 0x3e) < 0)) {
      Close__10MenuWindowFUci((MenuWindow *)(param_1 + 0xac),0,0x14d);
      *(u16 *)(param_1 + 0x62) = 0xc;
      *(u16 *)(param_1 + 100) = 0;
      Close__10MenuWindowFUci((MenuWindow *)(param_1 + 0x1c0),0,0x14d);
      *(u16 *)(param_1 + 0x176) = 0xc;
      *(u16 *)(param_1 + 0x178) = 0;
      Close__10MenuWindowFUci((MenuWindow *)(param_1 + 0x2d4),3,0x14d);
      *(u16 *)(param_1 + 0x28a) = 0xc;
      *(u16 *)(param_1 + 0x28c) = 0;
      bVar5 = 0;
      if (*(int *)(param_1 + 0xd50) != 0) {
        iVar14 = *(int *)(param_1 + 0xd50);
        bVar5 = Close__10MenuWindowFUci
                          ((MenuWindow *)(iVar14 + 0x58),
                           (byte)(((ulong)*(byte *)(iVar14 + 0x108) << 0x3a) >> 0x3d),
                           *(int *)(*(int *)(iVar14 + 0x8c) + 0x14));
      }
      SetBtlResultBGMFadeOut__6HNMSndFi(sys__6HNMSnd,0x14d,bVar5);
      *(u16 *)(param_1 + 0x2a) = 1;
      *(u32 *)(param_1 + 0x30) = 1;
    }
  }
  else if (sVar1 == 2) {
    if (*(short *)(param_1 + 0x2a) == 1) {
      uVar16 = 0;
      if (*(int *)(param_1 + 0xda8) != 0) {
        *(int *)(param_1 + 0xda4) = *(int *)(param_1 + 0xda4) - *(int *)(param_1 + 0xda8);
        if (((long)((ulong)*(byte *)(param_1 + 0x24) << 0x3e) < 0) ||
           (*(int *)(param_1 + 0xda4) < 0)) {
          *(u32 *)(param_1 + 0xda4) = 0;
          *(u32 *)(param_1 + 0xda8) = 0;
        }
        uVar16 = 3;
      }
      if (*(int *)(param_1 + 0xdb0) != 0) {
        *(int *)(param_1 + 0xdac) = *(int *)(param_1 + 0xdac) - *(int *)(param_1 + 0xdb0);
        if (((long)((ulong)*(byte *)(param_1 + 0x24) << 0x3e) < 0) ||
           (*(int *)(param_1 + 0xdac) < 0)) {
          *(u32 *)(param_1 + 0xdac) = 0;
          *(u32 *)(param_1 + 0xdb0) = 0;
        }
        uVar16 = 3;
      }
      if ((*(int *)(param_1 + 0xdb8) != 0) &&
         ((long)((ulong)*(byte *)((int)ourBtlSaveDat__10BtlSaveSec + 3) << 0x3d) < 0)) {
        *(int *)(param_1 + 0xdb4) = *(int *)(param_1 + 0xdb4) - *(int *)(param_1 + 0xdb8);
        if (((long)((ulong)*(byte *)(param_1 + 0x24) << 0x3e) < 0) ||
           (*(int *)(param_1 + 0xdb4) < 0)) {
          *(u32 *)(param_1 + 0xdb4) = 0;
          *(u32 *)(param_1 + 0xdb8) = 0;
        }
        uVar16 = uVar16 | 5;
      }
      if (uVar16 != 0) {
        WinCreate__9BtlResultFi(param_1,1);
      }
      lVar12 = 0;
      while (lVar12 < *(char *)(iVar14 + 0x47)) {
        bVar2 = false;
        uVar15 = (uint)lVar12;
        if (((((ulong)*(ushort *)(param_1 + 0x24) & 0x3ff) >> 2 & (long)(1 << (uVar15 & 0x1f))) != 0
            ) && (*(float *)(param_1 + uVar15 * 4 + 0xdbc) != 0.0)) {
          if ((long)((ulong)*(byte *)(param_1 + 0x24) << 0x3e) < 0) {
            *(u32 *)(param_1 + uVar15 * 4 + 0xdbc) = 0;
          }
          else {
            iVar9 = param_1 + uVar15 * 4;
            *(float *)(iVar9 + 0xdbc) =
                 *(float *)(iVar9 + 0xdbc) - *(float *)(param_1 + uVar15 * 4 + 0xdbc) / 4.0;
            if (*(float *)(param_1 + uVar15 * 4 + 0xdbc) < 0.01) {
              *(u32 *)(param_1 + uVar15 * 4 + 0xdbc) = 0;
            }
          }
          bVar2 = true;
        }
        if (*(int *)(param_1 + uVar15 * 4 + 0xd54) == 0) {
          if (bVar2) {
            WinCreate__9BtlResultFi(param_1,uVar15 + 2);
          }
        }
        else {
          if ((long)((ulong)*(byte *)(param_1 + 0x24) << 0x3e) < 0) {
            iVar9 = param_1 + uVar15 * 4;
            iVar10 = *(int *)(iVar6 + *(char *)(iVar7 + uVar15 + 0x12) * 4 + 0x130) -
                     *(int *)(iVar9 + 0xd74);
          }
          else {
            uVar13 = *(int *)(param_1 + uVar15 * 4 + 0xd74) + *(int *)(param_1 + uVar15 * 4 + 0xd54)
            ;
            if (*(uint *)(iVar6 + *(char *)(iVar7 + uVar15 + 0x12) * 4 + 0x130) < uVar13) {
              uVar13 = *(uint *)(iVar6 + *(char *)(iVar7 + uVar15 + 0x12) * 4 + 0x130);
            }
            iVar9 = *(int *)(param_1 + uVar15 * 4 + 0xd74);
            iVar10 = uVar13 - iVar9;
          }
          iVar9 = GetNextExp__10BtlSaveSecFi
                            ((BtlSaveSec *)(int)*(char *)(iVar7 + uVar15 + 0x12),iVar9);
          if (iVar9 < iVar10) {
            iVar10 = iVar9;
          }
          cVar4 = *(char *)(iVar7 + uVar15 + 0x12);
          *(int *)(ourBtlSaveDat__10BtlSaveSec + cVar4 * 0x60 + 0x40) =
               *(int *)(ourBtlSaveDat__10BtlSaveSec + cVar4 * 0x60 + 0x40) + iVar10;
          iVar9 = param_1 + uVar15 * 4;
          *(int *)(iVar9 + 0xd74) = *(int *)(iVar9 + 0xd74) + iVar10;
          iVar9 = PCLevelSet__10BtlSaveSecFi
                            ((BtlSaveSec *)(int)*(char *)(iVar7 + uVar15 + 0x12),iVar7 + uVar15);
          p2 = extraout_a1_lo;
          if (iVar9 != 0) {
            *(ushort *)(param_1 + 0x24) =
                 *(ushort *)(param_1 + 0x24) & 0xfc03 |
                 (ushort)(((uint)(byte)(((ulong)*(ushort *)(param_1 + 0x24) << 0x36) >> 0x38) |
                          1 << (uVar15 & 0x1f) & 0xffU) << 2);
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd,0x1003,1,0);
            *(u32 *)(param_1 + uVar15 * 4 + 0xdbc) = 0x40c90fdb;
            iVar9 = GetRealMaxSP__10BtlSaveSecFiPc
                              ((BtlSaveSec *)(int)*(char *)(iVar7 + uVar15 + 0x12),0,p3);
            p2 = ourBtlSaveDat__10BtlSaveSec + *(char *)(iVar7 + uVar15 + 0x12) * 0x60;
            *(char *)((int)p2 + 0x69) = (char)iVar9;
          }
          if (*(uint *)(iVar6 + *(char *)(iVar7 + uVar15 + 0x12) * 4 + 0x130) <=
              *(uint *)(param_1 + uVar15 * 4 + 0xd74)) {
            *(u32 *)(param_1 + uVar15 * 4 + 0xd54) = 0;
          }
          iVar9 = GetNextExp__10BtlSaveSecFi
                            ((BtlSaveSec *)(int)*(char *)(iVar7 + uVar15 + 0x12),(int)p2);
          if (iVar9 < 1) {
            *(u32 *)(param_1 + uVar15 * 4 + 0xd54) = 0;
          }
          WinCreate__9BtlResultFi(param_1,uVar15 + 2);
          uVar16 = uVar16 | 3;
        }
        lVar12 = (long)(int)(uVar15 + 1);
      }
      if (*(int *)(param_1 + 0xd94) != 0) {
        if ((long)((ulong)*(byte *)(param_1 + 0x24) << 0x3e) < 0) {
          iVar7 = *(int *)(iVar14 + 0x294) - *(int *)(param_1 + 0xd98);
        }
        else {
          uVar15 = *(int *)(param_1 + 0xd98) + *(int *)(param_1 + 0xd94);
          if (*(uint *)(iVar14 + 0x294) < uVar15) {
            uVar15 = *(uint *)(iVar14 + 0x294);
          }
          iVar7 = uVar15 - *(int *)(param_1 + 0xd98);
        }
        *piVar8 = *piVar8 + iVar7;
        *(int *)(param_1 + 0xd98) = *(int *)(param_1 + 0xd98) + iVar7;
        if (*(uint *)(iVar14 + 0x294) <= *(uint *)(param_1 + 0xd98)) {
          *(u32 *)(param_1 + 0xd94) = 0;
        }
        if (99999999 < *piVar8) {
          *piVar8 = 99999999;
          *(u32 *)(param_1 + 0xd94) = 0;
        }
        WinCreate__9BtlResultFi(param_1,1);
        uVar16 = uVar16 | 3;
      }
      if (((long)((ulong)*(byte *)((int)ourBtlSaveDat__10BtlSaveSec + 3) << 0x3d) < 0) &&
         (*(int *)(param_1 + 0xd9c) != 0)) {
        if ((long)((ulong)*(byte *)(param_1 + 0x24) << 0x3e) < 0) {
          iVar7 = *(int *)(iVar14 + 0x298) - *(int *)(param_1 + 0xda0);
        }
        else {
          uVar15 = *(int *)(param_1 + 0xda0) + *(int *)(param_1 + 0xd9c);
          if (*(uint *)(iVar14 + 0x298) < uVar15) {
            uVar15 = *(uint *)(iVar14 + 0x298);
          }
          iVar7 = uVar15 - *(int *)(param_1 + 0xda0);
        }
        *ourBtlSaveDat__10BtlSaveSec = *ourBtlSaveDat__10BtlSaveSec + (short)iVar7;
        *(int *)(param_1 + 0xda0) = *(int *)(param_1 + 0xda0) + iVar7;
        if (*(uint *)(iVar14 + 0x298) <= *(uint *)(param_1 + 0xda0)) {
          *(u32 *)(param_1 + 0xd9c) = 0;
        }
        if (9999 < *ourBtlSaveDat__10BtlSaveSec) {
          *ourBtlSaveDat__10BtlSaveSec = 9999;
          *(u32 *)(param_1 + 0xd9c) = 0;
        }
        SetMeter__13CmdSoulEnergyFUi(*(u32 *)(param_1 + 0xd50),*ourBtlSaveDat__10BtlSaveSec);
        uVar16 = uVar16 | 5;
      }
      if (((*(uint *)(param_1 + 0x34) & 1) == 0) && ((uVar16 & 2) == 0)) {
        cVar4 = SEEndCheck__6HNMSndFUii(sys__6HNMSnd,0x3000,0xffffffffffffffff);
        if (cVar4 == '\0') {
          SetSEEnd__6HNMSndFUii(sys__6HNMSnd,0x3000,0xffffffffffffffff);
        }
        else {
          *(uint *)(param_1 + 0x34) = *(uint *)(param_1 + 0x34) | 1;
        }
      }
      if ((uVar16 == 0) && ((*(uint *)(param_1 + 0x34) & 3) == 3)) {
        for (iVar7 = 0; iVar7 < (int)(uint)*(byte *)(iVar14 + 0x16e); iVar7 = iVar7 + 1) {
          if (*(ushort *)(iVar6 + iVar7 * 2 + 4) < 100) {
            iVar9 = (uint)*(ushort *)(iVar6 + iVar7 * 2 + 4) +
                    (uint)(byte)ourBtlSaveDat__10BtlSaveSec[1] * 0x200;
            *(char *)((int)ourBtlSaveDat__10BtlSaveSec + iVar9 + 0x944) =
                 *(char *)((int)ourBtlSaveDat__10BtlSaveSec + iVar9 + 0x944) +
                 *(char *)(iVar6 + iVar7 + 0xc4);
            if (99 < *(byte *)((int)ourBtlSaveDat__10BtlSaveSec +
                              (uint)*(ushort *)(iVar6 + iVar7 * 2 + 4) +
                              (uint)(byte)ourBtlSaveDat__10BtlSaveSec[1] * 0x200 + 0x944)) {
              *(u8 *)
               ((int)ourBtlSaveDat__10BtlSaveSec +
               (uint)*(ushort *)(iVar6 + iVar7 * 2 + 4) +
               (uint)(byte)ourBtlSaveDat__10BtlSaveSec[1] * 0x200 + 0x944) = 99;
            }
          }
          else if (*(ushort *)(iVar6 + iVar7 * 2 + 4) < 200) {
            iVar9 = (*(ushort *)(iVar6 + iVar7 * 2 + 4) - 100) +
                    (uint)(byte)ourBtlSaveDat__10BtlSaveSec[1] * 0x200;
            *(char *)((int)ourBtlSaveDat__10BtlSaveSec + iVar9 + 0x9c4) =
                 *(char *)((int)ourBtlSaveDat__10BtlSaveSec + iVar9 + 0x9c4) +
                 *(char *)(iVar6 + iVar7 + 0xc4);
            if (99 < *(byte *)((int)ourBtlSaveDat__10BtlSaveSec +
                              (uint)*(ushort *)(iVar6 + iVar7 * 2 + 4) +
                              (uint)(byte)ourBtlSaveDat__10BtlSaveSec[1] * 0x200 + 0x960)) {
              *(u8 *)
               ((int)ourBtlSaveDat__10BtlSaveSec +
               (uint)*(ushort *)(iVar6 + iVar7 * 2 + 4) +
               (uint)(byte)ourBtlSaveDat__10BtlSaveSec[1] * 0x200 + 0x960) = 99;
            }
          }
          else if (*(ushort *)(iVar6 + iVar7 * 2 + 4) < 300) {
            iVar9 = (*(ushort *)(iVar6 + iVar7 * 2 + 4) - 200) +
                    (uint)(byte)ourBtlSaveDat__10BtlSaveSec[1] * 0x200;
            *(char *)((int)ourBtlSaveDat__10BtlSaveSec + iVar9 + 0xa24) =
                 *(char *)((int)ourBtlSaveDat__10BtlSaveSec + iVar9 + 0xa24) +
                 *(char *)(iVar6 + iVar7 + 0xc4);
            if (99 < *(byte *)((int)ourBtlSaveDat__10BtlSaveSec +
                              (uint)*(ushort *)(iVar6 + iVar7 * 2 + 4) +
                              (uint)(byte)ourBtlSaveDat__10BtlSaveSec[1] * 0x200 + 0x95c)) {
              *(u8 *)
               ((int)ourBtlSaveDat__10BtlSaveSec +
               (uint)*(ushort *)(iVar6 + iVar7 * 2 + 4) +
               (uint)(byte)ourBtlSaveDat__10BtlSaveSec[1] * 0x200 + 0x95c) = 99;
            }
          }
          else if (*(ushort *)(iVar6 + iVar7 * 2 + 4) < 400) {
            iVar9 = (*(ushort *)(iVar6 + iVar7 * 2 + 4) - 300) +
                    (uint)(byte)ourBtlSaveDat__10BtlSaveSec[1] * 0x200;
            *(char *)((int)ourBtlSaveDat__10BtlSaveSec + iVar9 + 0xa54) =
                 *(char *)((int)ourBtlSaveDat__10BtlSaveSec + iVar9 + 0xa54) +
                 *(char *)(iVar6 + iVar7 + 0xc4);
            if (99 < *(byte *)((int)ourBtlSaveDat__10BtlSaveSec +
                              (uint)*(ushort *)(iVar6 + iVar7 * 2 + 4) +
                              (uint)(byte)ourBtlSaveDat__10BtlSaveSec[1] * 0x200 + 0x928)) {
              *(u8 *)
               ((int)ourBtlSaveDat__10BtlSaveSec +
               (uint)*(ushort *)(iVar6 + iVar7 * 2 + 4) +
               (uint)(byte)ourBtlSaveDat__10BtlSaveSec[1] * 0x200 + 0x928) = 99;
            }
          }
          else if (*(ushort *)(iVar6 + iVar7 * 2 + 4) < 500) {
            uVar13 = *(ushort *)(iVar6 + iVar7 * 2 + 4) - 400;
            uVar15 = uVar13 & 7;
            if (((int)uVar13 < 0) && (uVar15 != 0)) {
              uVar15 = uVar15 - 8;
            }
            iVar9 = ((int)(*(ushort *)(iVar6 + iVar7 * 2 + 4) - 400) >> 3) +
                    (uint)(byte)ourBtlSaveDat__10BtlSaveSec[1] * 0x200;
            *(byte *)((int)ourBtlSaveDat__10BtlSaveSec + iVar9 + 0xaa4) =
                 *(byte *)((int)ourBtlSaveDat__10BtlSaveSec + iVar9 + 0xaa4) |
                 (byte)(1 << (uVar15 & 0x1f));
          }
          else if (*(ushort *)(iVar6 + iVar7 * 2 + 4) < 600) {
            iVar9 = (*(ushort *)(iVar6 + iVar7 * 2 + 4) - 500) +
                    (uint)(byte)ourBtlSaveDat__10BtlSaveSec[1] * 0x200;
            *(char *)((int)ourBtlSaveDat__10BtlSaveSec + iVar9 + 0xab8) =
                 *(char *)((int)ourBtlSaveDat__10BtlSaveSec + iVar9 + 0xab8) +
                 *(char *)(iVar6 + iVar7 + 0xc4);
            if (99 < *(byte *)((int)ourBtlSaveDat__10BtlSaveSec +
                              (uint)*(ushort *)(iVar6 + iVar7 * 2 + 4) +
                              (uint)(byte)ourBtlSaveDat__10BtlSaveSec[1] * 0x200 + 0x8c4)) {
              *(u8 *)
               ((int)ourBtlSaveDat__10BtlSaveSec +
               (uint)*(ushort *)(iVar6 + iVar7 * 2 + 4) +
               (uint)(byte)ourBtlSaveDat__10BtlSaveSec[1] * 0x200 + 0x8c4) = 99;
            }
          }
          else if (*(ushort *)(iVar6 + iVar7 * 2 + 4) < 700) {
            ourBtlSaveDat__10BtlSaveSec[0x6d4] =
                 ourBtlSaveDat__10BtlSaveSec[0x6d4] |
                 (ushort)(1 << (*(ushort *)(iVar6 + iVar7 * 2 + 4) - 600 & 0x1f));
          }
          else if (*(ushort *)(iVar6 + iVar7 * 2 + 4) < 800) {
            *(byte *)(ourBtlSaveDat__10BtlSaveSec + 0x6d7) =
                 (byte)ourBtlSaveDat__10BtlSaveSec[0x6d7] |
                 (byte)(1 << (*(ushort *)(iVar6 + iVar7 * 2 + 4) - 700 & 0x1f));
          }
          else if (*(ushort *)(iVar6 + iVar7 * 2 + 4) < 900) {
            uVar13 = *(ushort *)(iVar6 + iVar7 * 2 + 4) - 800;
            uVar15 = uVar13 & 7;
            if (((int)uVar13 < 0) && (uVar15 != 0)) {
              uVar15 = uVar15 - 8;
            }
            iVar9 = (int)(*(ushort *)(iVar6 + iVar7 * 2 + 4) - 800) >> 3;
            *(byte *)((int)ourBtlSaveDat__10BtlSaveSec + iVar9 + 0xdab) =
                 *(byte *)((int)ourBtlSaveDat__10BtlSaveSec + iVar9 + 0xdab) |
                 (byte)(1 << (uVar15 & 0x1f));
          }
          else {
            uVar15 = *(ushort *)(iVar6 + iVar7 * 2 + 4) - 900;
            uVar13 = uVar15 & 7;
            if (((int)uVar15 < 0) && (uVar13 != 0)) {
              uVar13 = uVar13 - 8;
            }
            iVar9 = ((int)(*(ushort *)(iVar6 + iVar7 * 2 + 4) - 400) >> 3) +
                    (uint)(byte)ourBtlSaveDat__10BtlSaveSec[1] * 0x200;
            *(byte *)((int)ourBtlSaveDat__10BtlSaveSec + iVar9 + 0x984) =
                 *(byte *)((int)ourBtlSaveDat__10BtlSaveSec + iVar9 + 0x984) |
                 (byte)(1 << (uVar13 & 0x1f));
          }
        }
        iVar7 = GetRegDat__9RegDatApiFiii(0x2e,0,0xffffffffffffffff);
        for (iVar9 = 0; iVar9 < (int)(uint)*(byte *)(iVar14 + 0x16f); iVar9 = iVar9 + 1) {
          if (-1 < (long)((ulong)*(byte *)(iVar7 + (uint)*(ushort *)(iVar6 + iVar9 * 2 + 0x160) *
                                                   0x38 + 0x14) << 0x39)) {
            iVar10 = (int)(uint)*(ushort *)(iVar6 + iVar9 * 2 + 0x160) >> 3;
            *(byte *)((int)ourBtlSaveDat__10BtlSaveSec + iVar10 + 0xdaf) =
                 *(byte *)((int)ourBtlSaveDat__10BtlSaveSec + iVar10 + 0xdaf) |
                 (byte)(1 << (*(ushort *)(iVar6 + iVar9 * 2 + 0x160) & 7));
          }
        }
        for (iVar9 = 0; iVar9 < (int)(uint)*(byte *)(iVar14 + 0x526); iVar9 = iVar9 + 1) {
          if (-1 < (long)((ulong)*(byte *)(iVar7 + (uint)*(byte *)(iVar6 + iVar9 + 0x3d4) * 0x38 +
                                          0x14) << 0x39)) {
            iVar10 = 1 << ((*(byte *)(iVar6 + iVar9 + 0x3d4) & 3) << 1);
            bVar5 = (byte)iVar10;
            if (*(char *)(iVar6 + iVar9 + 0x434) != '\0') {
              bVar5 = (byte)(iVar10 << 1);
            }
            iVar10 = (int)(uint)*(byte *)(iVar6 + iVar9 + 0x3d4) >> 2;
            *(byte *)((int)ourBtlSaveDat__10BtlSaveSec + iVar10 + 0xdef) =
                 *(byte *)((int)ourBtlSaveDat__10BtlSaveSec + iVar10 + 0xdef) | bVar5;
          }
        }
        *(u16 *)(param_1 + 0x28) = 3;
        *(u16 *)(param_1 + 0x2a) = 0;
      }
    }
    else if ((*(short *)(param_1 + 0x2a) == 0) &&
            ((*(float *)(param_1 + 0x50) =
                   *(float *)(param_1 + 0x50) + (float)(uint)(iVar10 - iVar9) * 0.001,
             0.5 <= *(float *)(param_1 + 0x50) ||
             ((long)((ulong)*(byte *)(param_1 + 0x24) << 0x3e) < 0)))) {
      bVar2 = false;
      *(u32 *)(param_1 + 0xda8) = 0;
      *(u32 *)(param_1 + 0xdb0) = 0;
      *(u32 *)(param_1 + 0xdb8) = 0;
      lVar12 = 0;
      while (lVar12 < *(char *)(iVar14 + 0x47)) {
        iVar9 = (int)lVar12;
        *(u32 *)(param_1 + iVar9 * 4 + 0xd54) = 0;
        if ((*(int *)(iVar6 + *(char *)(iVar7 + iVar9 + 0x12) * 4 + 0x130) != 0) &&
           (*(uint *)(param_1 + iVar9 * 4 + 0xd54) =
                 *(uint *)(iVar6 + *(char *)(iVar7 + iVar9 + 0x12) * 4 + 0x130) / 0x3c,
           *(int *)(param_1 + iVar9 * 4 + 0xd54) < 0xd)) {
          *(u32 *)(param_1 + iVar9 * 4 + 0xd54) = 0xd;
        }
        *(u32 *)(param_1 + iVar9 * 4 + 0xd74) = 0;
        iVar10 = GetNextExp__10BtlSaveSecFi
                           ((BtlSaveSec *)(int)*(char *)(iVar7 + iVar9 + 0x12),iVar7 + iVar9);
        if (iVar10 < 1) {
          *(u32 *)(param_1 + iVar9 * 4 + 0xd54) = 0;
        }
        if (*(int *)(param_1 + iVar9 * 4 + 0xd54) != 0) {
          bVar2 = true;
        }
        lVar12 = (long)(iVar9 + 1);
      }
      *(u32 *)(param_1 + 0xd94) = 0;
      if ((*(int *)(iVar14 + 0x294) != 0) &&
         (*(uint *)(param_1 + 0xd94) = *(uint *)(iVar14 + 0x294) / 0x3c,
         *(int *)(param_1 + 0xd94) < 0xd)) {
        *(u32 *)(param_1 + 0xd94) = 0xd;
      }
      *(u32 *)(param_1 + 0xd98) = 0;
      *(u32 *)(param_1 + 0xd9c) = 0;
      if ((*(int *)(iVar14 + 0x298) != 0) &&
         (*(uint *)(param_1 + 0xd9c) = *(uint *)(iVar14 + 0x298) / 0x3c,
         *(int *)(param_1 + 0xd9c) < 0xd)) {
        *(u32 *)(param_1 + 0xd9c) = 0xd;
      }
      *(u32 *)(param_1 + 0xda0) = 0;
      *(u32 *)(param_1 + 0x34) = 0;
      if ((((*(int *)(param_1 + 0xda8) != 0) || (*(int *)(param_1 + 0xdb0) != 0)) || (bVar2)) ||
         (*(int *)(param_1 + 0xd94) != 0)) {
        PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd,0x3000,1,0);
      }
      else {
        *(uint *)(param_1 + 0x34) = *(uint *)(param_1 + 0x34) | 1;
      }
      *(uint *)(param_1 + 0x34) = *(uint *)(param_1 + 0x34) | 2;
      *(u16 *)(param_1 + 0x2a) = 1;
    }
  }
  else {
    if (sVar1 != 1) {
      if (sVar1 != 0) {
        return 0;
      }
      if (*(short *)(param_1 + 0x2a) == 1) {
        if ((long)*(int *)(param_1 + 0x30) < (long)*(char *)(iVar14 + 0x47)) {
          WinCreate__9BtlResultFi(param_1,*(int *)(param_1 + 0x30) + 2);
          *(int *)(param_1 + 0x30) = *(int *)(param_1 + 0x30) + 1;
        }
        else {
          *(u16 *)(param_1 + 0x28) = 1;
          *(u16 *)(param_1 + 0x2a) = 0;
        }
      }
      else if (*(short *)(param_1 + 0x2a) == 0) {
        if ((*(char *)(ourBtlSocket__9BtlSocket + 0x600) == '\0') &&
           (*(char *)(ourBtlSocket__9BtlSocket + 0x600) == '\0')) {
          *(u8 *)(ourBtlSocket__9BtlSocket + 0x600) = 1;
        }
        if (*(char *)(ourBtlSocket__9BtlSocket + 0x600) == '\x04') {
          *(u32 *)(param_1 + 0xda4) = *(u32 *)(iVar14 + 0x290);
          *(u32 *)(param_1 + 0xdac) = *(u32 *)(iVar14 + 0x294);
          *(u32 *)(param_1 + 0xdb4) = *(u32 *)(iVar14 + 0x298);
          WinCreate__9BtlResultFi(param_1,0);
          WinCreate__9BtlResultFi(param_1,1);
          WinCreate__9BtlResultFi(param_1,2);
          if ((long)((ulong)*(byte *)((int)ourBtlSaveDat__10BtlSaveSec + 3) << 0x3d) < 0) {
            lVar12 = __nw__FUi(0x3f0);
            uVar11 = 0;
            if (lVar12 != 0) {
              uVar11 = __ct__13CmdSoulEnergyFv(lVar12);
            }
            *(u32 *)(param_1 + 0xd50) = uVar11;
            Initialize__9MenuSceneFPUcP9BufMemory
                      (*(MenuScene **)(param_1 + 0xd50),*(void **)(ourBtlSocket__9BtlSocket + 0x688)
                       ,(void *)0x0);
            SetMeter__13CmdSoulEnergyFUi
                      (*(u32 *)(param_1 + 0xd50),*ourBtlSaveDat__10BtlSaveSec);
            iVar14 = *(int *)(param_1 + 0xd50);
            Open__10MenuWindowFUci
                      ((MenuWindow *)(iVar14 + 0x58),*(byte *)(iVar14 + 0x108) & 7,
                       *(int *)(*(int *)(iVar14 + 0x8c) + 0x10));
          }
          SetMode__8BtlFaderFsf7_rgba32(0,0,0);
          *(u16 *)(param_1 + 0x2a) = 1;
          *(u32 *)(param_1 + 0x30) = 1;
        }
      }
    }
    bVar2 = false;
    for (iVar14 = 0; iVar14 < 0xc; iVar14 = iVar14 + 1) {
      if ((*(short *)(param_1 + iVar14 * 0x114 + 0x62) == 1) ||
         (*(short *)(param_1 + iVar14 * 0x114 + 0x62) == 0xc)) {
        bVar2 = true;
      }
    }
    if (!bVar2) {
      *(u16 *)(param_1 + 0x28) = 2;
      *(u16 *)(param_1 + 0x2a) = 0;
      *(u32 *)(param_1 + 0x50) = 0;
    }
  }
  return 0;
}

/* ---- 0x0035bee0 size 0x6b8  BtlResult::WinSequence(v)
 *      mangled: WinSequence__9BtlResultFv */
void WinSequence__9BtlResultFv(int param_1)

{
  short sVar1;
  int iVar2;
  int iVar3;
  
  for (iVar2 = 0; iVar2 < 0xc; iVar2 = iVar2 + 1) {
    sVar1 = *(short *)(param_1 + iVar2 * 0x114 + 0x62);
    if (sVar1 == 0xc) {
      sVar1 = *(short *)(param_1 + iVar2 * 0x114 + 100);
      if (sVar1 == 1) {
        Release__7MenuObjFv((MenuObj *)(param_1 + iVar2 * 0x114 + 0x6c));
        iVar3 = param_1 + iVar2 * 0x114;
        *(byte *)(iVar3 + 0x60) = *(byte *)(iVar3 + 0x60) & 0xfd;
        Release__7MenuObjFv((MenuObj *)(param_1 + iVar2 * 0x114 + 0xac));
        iVar3 = param_1 + iVar2 * 0x114;
        *(byte *)(iVar3 + 0x60) = *(byte *)(iVar3 + 0x60) & 0xf7;
        if (((ulong)*(ushort *)(param_1 + iVar2 * 0x114 + 0x60) & 0xfff) >> 4 != 0) {
          __destroy_new_array(*(u32 *)(param_1 + iVar2 * 0x114 + 0x160),0x273e20);
          *(u32 *)(param_1 + iVar2 * 0x114 + 0x160) = 0;
        }
        iVar3 = param_1 + iVar2 * 0x114;
        *(ushort *)(iVar3 + 0x60) = *(ushort *)(iVar3 + 0x60) & 0xf00f;
        if (*(int *)(param_1 + iVar2 * 0x114 + 0x168) != 0) {
          __destroy_new_array(*(u32 *)(param_1 + iVar2 * 0x114 + 0x168),0x2661a0);
          *(u32 *)(param_1 + iVar2 * 0x114 + 0x168) = 0;
        }
        if (*(int *)(param_1 + iVar2 * 0x114 + 0x164) != 0) {
          __destroy_new_array(*(u32 *)(param_1 + iVar2 * 0x114 + 0x164),0x277890);
        }
        *(u32 *)(param_1 + iVar2 * 0x114 + 0x164) = 0;
        if (*(int *)(param_1 + iVar2 * 0x114 + 0x16c) != 0) {
          __destroy_new_array(*(u32 *)(param_1 + iVar2 * 0x114 + 0x16c),0x2766d0);
        }
        *(u32 *)(param_1 + iVar2 * 0x114 + 0x16c) = 0;
        if (*(int *)(param_1 + iVar2 * 0x114 + 0x170) != 0) {
          __destroy_new_array(*(u32 *)(param_1 + iVar2 * 0x114 + 0x170),0x28d070);
        }
        *(u32 *)(param_1 + iVar2 * 0x114 + 0x170) = 0;
        *(u16 *)(param_1 + iVar2 * 0x114 + 0x62) = 0;
        *(u16 *)(param_1 + iVar2 * 0x114 + 100) = 0;
      }
      else if ((sVar1 == 0) && (*(char *)(param_1 + iVar2 * 0x114 + 0x154) == '\0')) {
        if ((*(byte *)(param_1 + iVar2 * 0x114 + 0x60) & 1) != 0) {
          ReleaseOT__7MenuObjFv((MenuObj *)(param_1 + iVar2 * 0x114 + 0x6c));
        }
        iVar3 = param_1 + iVar2 * 0x114;
        *(byte *)(iVar3 + 0x60) = *(byte *)(iVar3 + 0x60) & 0xfe;
        if ((long)((ulong)*(byte *)(param_1 + iVar2 * 0x114 + 0x60) << 0x3d) < 0) {
          ReleaseOT__7MenuObjFv((MenuObj *)(param_1 + iVar2 * 0x114 + 0xac));
        }
        iVar3 = param_1 + iVar2 * 0x114;
        *(byte *)(iVar3 + 0x60) = *(byte *)(iVar3 + 0x60) & 0xfb;
        *(u16 *)(param_1 + iVar2 * 0x114 + 100) = 1;
      }
    }
    else if (((sVar1 != 2) && (sVar1 == 1)) &&
            (*(char *)(param_1 + iVar2 * 0x114 + 0x154) == '\x01')) {
      *(u16 *)(param_1 + iVar2 * 0x114 + 0x62) = 2;
      *(u16 *)(param_1 + iVar2 * 0x114 + 100) = 0;
    }
  }
  return;
}

/* ---- 0x0035c5a0 size 0x15174  BtlResult::WinCreate(i)
 *      mangled: WinCreate__9BtlResultFi */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void WinCreate__9BtlResultFi(int param_1,int param_2)

{
  char cVar1;
  MenuSprite *pMVar2;
  MenuPolygon *pMVar3;
  ushort uVar4;
  uint uVar5;
  bool bVar6;
  short sVar7;
  int iVar8;
  u32 uVar9;
  int iVar10;
  u64 uVar11;
  void *pvVar12;
  void *extraout_a2_lo;
  void *extraout_a2_lo_00;
  void *p3;
  u32 uStack_170;
  u32 uStack_16c;
  u32 uStack_168;
  u32 uStack_164;
  u16 uStack_160;
  u8 uStack_15e;
  ulong uStack_158;
  u32 uStack_150;
  u32 uStack_14c;
  u32 uStack_148;
  u32 uStack_144;
  u32 uStack_140;
  u32 uStack_13c;
  u32 uStack_138;
  u32 uStack_134;
  u32 uStack_130;
  u32 uStack_12c;
  u32 uStack_128;
  u32 uStack_124;
  u32 uStack_120;
  u32 uStack_11c;
  u32 uStack_118;
  u32 uStack_114;
  u32 uStack_110;
  u32 uStack_10c;
  u32 uStack_108;
  u32 uStack_104;
  u32 uStack_100;
  u32 uStack_fc;
  u32 uStack_f8;
  u32 uStack_f4;
  int iStack_f0;
  u32 uStack_ec;
  u32 uStack_e8;
  u32 uStack_e4;
  u32 uStack_e0;
  u32 uStack_dc;
  u32 uStack_d8;
  int *piStack_d4;
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
  int iStack_a0;
  int iStack_9c;
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
  int iStack_58;
  int *piStack_54;
  int iStack_50;
  int iStack_4c;
  int iStack_48;
  MenuText *pMStack_44;
  float fStack_40;
  float fStack_3c;
  int iStack_38;
  int iStack_34;
  int iStack_30;
  BtlSaveSec *pBStack_2c;
  int iStack_28;
  int iStack_24;
  int iStack_20;
  int iStack_10;
  
  iStack_4c = ourBtlSocket__9BtlSocket + 0x16c;
  iStack_50 = ourBtlSocket__9BtlSocket + 0x38;
  iStack_20 = param_1;
  iStack_10 = param_2;
  iVar8 = GetCommonParam__10BtlSaveSecFv();
  piStack_d4 = (int *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) +
                       (uint)*(byte *)(iVar8 + 2) * 4 + 4);
  uStack_170 = (u32)__7163;
  uStack_16c = (u32)((ulong)__7163 >> 0x20);
  uStack_168 = DAT_003f9b78;
  uStack_164 = DAT_003f9b7c;
  uStack_160 = DAT_003f9b80;
  uStack_15e = DAT_003f9b82;
  piStack_54 = piStack_d4;
  switch(iStack_10) {
  case 0:
    if (*(short *)(iStack_20 + iStack_10 * 0x114 + 0x62) == 0) {
      *(u16 *)(iStack_20 + iStack_10 * 0x114 + 0x62) = 1;
      *(u16 *)(iStack_20 + iStack_10 * 0x114 + 100) = 0;
      *(u32 *)(iStack_20 + iStack_10 * 0x114 + 0x68) = 0;
      Create__8FontDrawF6GS_PSMUsUsUcUiP10ClutRaster
                (iStack_20 + iStack_10 * 0x114 + 0x6c,0x2c,0x40,0x20,0,0,0);
      iVar8 = iStack_20 + iStack_10 * 0x114;
      *(byte *)(iVar8 + 0x60) = *(byte *)(iVar8 + 0x60) & 0xfd | 2;
      *(u16 *)(iStack_20 + iStack_10 * 0x114 + 0x80) = 7;
      AddPriority__12MenuObjTableFP7MenuObj
                ((MenuObjTable *)(iStack_20 + iStack_10 * 0x114 + 0xc4),
                 (MenuObj *)(iStack_20 + iStack_10 * 0x114 + 0x6c));
      *(u16 *)(iStack_20 + iStack_10 * 0x114 + 0xc0) = 1;
      AddOT__7MenuObjFv((MenuObj *)(iStack_20 + iStack_10 * 0x114 + 0xac));
      iVar8 = iStack_20 + iStack_10 * 0x114;
      *(byte *)(iVar8 + 0x60) = *(byte *)(iVar8 + 0x60) & 0xfb | 4;
      Create__10MenuWindowFUcUcffff
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),0,1,0.0,0.0,512.0,448.0);
      iVar8 = iStack_20 + iStack_10 * 0x114;
      *(byte *)(iVar8 + 0x60) = *(byte *)(iVar8 + 0x60) & 0xf7 | 8;
      if (((ulong)*(ushort *)(iStack_20 + iStack_10 * 0x114 + 0x60) & 0xfff) >> 4 == 0) {
        uVar11 = __nwa__FUi(0x90);
        uVar9 = __construct_new_array(uVar11,0x27bfd0,0x27c030,0x80,1);
        *(u32 *)(iStack_20 + iStack_10 * 0x114 + 0x160) = uVar9;
        iVar8 = iStack_20 + iStack_10 * 0x114;
        *(ushort *)(iVar8 + 0x60) = *(ushort *)(iVar8 + 0x60) & 0xf00f | 0x10;
      }
      pMStack_44 = *(MenuText **)(iStack_20 + iStack_10 * 0x114 + 0x160);
      Create__8MenuTextFUcUc(pMStack_44,1,2);
      pMStack_44->nPriority = 8;
      pMStack_44->bShadow_x = 1;
      pMStack_44->bShadow_y = 0;
      pMStack_44->nCol = 0;
      pMStack_44->nRow = 0;
      SetMessage__8MenuTextFPcUiUcUc(pMStack_44,&_8252,0,0,1);
      (**(code **)((int)pMStack_44->pVptr + 0x24))(0x43e9999a,0x43c50000);
      pMStack_44->bFlags = pMStack_44->bFlags & 0xfe | 1;
      OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_
                (iStack_20 + iStack_10 * 0x114 + 0x6c,pMStack_44,1,0);
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)pMStack_44);
      uVar11 = __nwa__FUi(0xa0);
      uVar9 = __construct_new_array(uVar11,0x277820,0x277890,0x30,3);
      *(u32 *)(iStack_20 + iStack_10 * 0x114 + 0x164) = uVar9;
      iStack_5c = *(int *)(ourBtlSocket__9BtlSocket + 0x60c);
      uStack_dc = *(u32 *)(iStack_5c + (uint)*(ushort *)(iStack_5c + 10) * 4 + 0xc);
      uStack_d8 = uStack_dc;
      uVar11 = GetTex0__6JRCTexFb(*(u32 *)(ourBtlSocket__9BtlSocket + 0x60c),0);
      Create__11SendOnLocalFP4_QWDUl
                (*(u32 *)(iStack_20 + iStack_10 * 0x114 + 0x164),uStack_dc,uVar11);
      iStack_60 = *(int *)(iStack_20 + iStack_10 * 0x114 + 0x164);
      *(u16 *)(iStack_60 + 0x14) = 1;
      AddPriority__12MenuObjTableFP7MenuObj
                ((MenuObjTable *)(iStack_20 + iStack_10 * 0x114 + 0xc4),
                 *(MenuObj **)(iStack_20 + iStack_10 * 0x114 + 0x164));
      iStack_64 = *(int *)(ourBtlSocket__9BtlSocket + 0x610);
      uStack_e4 = *(u32 *)(iStack_64 + (uint)*(ushort *)(iStack_64 + 10) * 4 + 0xc);
      uStack_e0 = uStack_e4;
      uVar11 = GetTex0__6JRCTexFb(*(u32 *)(ourBtlSocket__9BtlSocket + 0x610),0);
      Create__11SendOnLocalFP4_QWDUl
                (*(int *)(iStack_20 + iStack_10 * 0x114 + 0x164) + 0x30,uStack_e4,uVar11);
      iVar8 = *(int *)(iStack_20 + iStack_10 * 0x114 + 0x164);
      iStack_68 = iVar8 + 0x30;
      *(u16 *)(iVar8 + 0x44) = 3;
      AddPriority__12MenuObjTableFP7MenuObj
                ((MenuObjTable *)(iStack_20 + iStack_10 * 0x114 + 0xc4),
                 (MenuObj *)(*(int *)(iStack_20 + iStack_10 * 0x114 + 0x164) + 0x30));
      iStack_6c = *(int *)(ourBtlSocket__9BtlSocket + 0x674);
      uStack_ec = *(u32 *)(iStack_6c + (uint)*(ushort *)(iStack_6c + 10) * 4 + 0xc);
      uStack_e8 = uStack_ec;
      uVar11 = GetTex0__6JRCTexFb(*(u32 *)(ourBtlSocket__9BtlSocket + 0x674),0);
      Create__11SendOnLocalFP4_QWDUl
                (*(int *)(iStack_20 + iStack_10 * 0x114 + 0x164) + 0x60,uStack_ec,uVar11);
      iVar8 = *(int *)(iStack_20 + iStack_10 * 0x114 + 0x164);
      iStack_70 = iVar8 + 0x60;
      *(u16 *)(iVar8 + 0x74) = 5;
      AddPriority__12MenuObjTableFP7MenuObj
                ((MenuObjTable *)(iStack_20 + iStack_10 * 0x114 + 0xc4),
                 (MenuObj *)(*(int *)(iStack_20 + iStack_10 * 0x114 + 0x164) + 0x60));
      if (*(int *)(iStack_20 + iStack_10 * 0x114 + 0x168) == 0) {
        uVar11 = __nwa__FUi(0x130);
        uVar9 = __construct_new_array(uVar11,0x266140,0x2661a0,0x60,3);
        *(u32 *)(iStack_20 + iStack_10 * 0x114 + 0x168) = uVar9;
      }
      pMVar2 = *(MenuSprite **)(iStack_20 + iStack_10 * 0x114 + 0x168);
      Create__10MenuSpriteFUc(pMVar2,1);
      pMVar2->bPflags = pMVar2->bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)pMVar2);
      pMVar2->nPriority = 2;
      (**(code **)((int)pMVar2->pVptr + 0x24))(0,0);
      SetUV__10MenuSpriteFUsUsUsUs
                (pMVar2,0,0,*(short *)(*(int *)(ourBtlSocket__9BtlSocket + 0x60c) + 2) + 1,
                 *(short *)(*(int *)(ourBtlSocket__9BtlSocket + 0x60c) + 4) + 1);
      (**(code **)((int)pMVar2->pVptr + 0x28))(0x44004000,0x43e08000);
      (**(code **)((int)pMVar2->pVptr + 0x30))(pMVar2,0x80,0x80,0x80);
      (**(code **)((int)pMVar2->pVptr + 0x2c))(pMVar2,0x80);
      pMVar2->bFlags = pMVar2->bFlags & 0xfe | 1;
      pMVar2->nCol = 1;
      pMVar2->nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)pMVar2);
      Create__10MenuSpriteFUc(pMVar2 + 1,1);
      pMVar2[1].bPflags = pMVar2[1].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 1));
      pMVar2[1].nPriority = 4;
      (**(code **)((int)pMVar2[1].pVptr + 0x24))(0,0);
      SetUV__10MenuSpriteFUsUsUsUs
                (pMVar2 + 1,0,0,*(short *)(*(int *)(ourBtlSocket__9BtlSocket + 0x610) + 2) + 1,
                 *(short *)(*(int *)(ourBtlSocket__9BtlSocket + 0x610) + 4) + 1);
      (**(code **)((int)pMVar2[1].pVptr + 0x28))(0x44008000,0x43e10000);
      (**(code **)((int)pMVar2[1].pVptr + 0x30))(pMVar2 + 1,0x80,0x80,0x80);
      (**(code **)((int)pMVar2[1].pVptr + 0x2c))(pMVar2 + 1,0x80);
      pMVar2[1].bFlags = pMVar2[1].bFlags & 0xfe | 1;
      pMVar2[1].nCol = 2;
      pMVar2[1].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 1));
      iStack_f0 = *(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x26c;
      iStack_58 = iStack_f0;
      Create__10MenuSpriteFUc(pMVar2 + 2,1);
      pMVar2[2].bPflags = pMVar2[2].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 2));
      pMVar2[2].nPriority = 6;
      (**(code **)((int)pMVar2[2].pVptr + 0x24))(0x43e10000,0x43c50000);
      sVar7 = *(short *)(iStack_58 + 2);
      if (sVar7 == 0xf) {
        SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 2,0x23,0,0x33,0x14);
      }
      else if (sVar7 == 0xc) {
        SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 2,0x12,0,0x22,0x14);
      }
      else if (sVar7 == 0xe) {
        SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 2,0x34,0,0x44,0x14);
      }
      else {
        SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 2,1,0,0x11,0x14);
      }
      (**(code **)((int)pMVar2[2].pVptr + 0x28))(0x41800000,0x41a00000);
      (**(code **)((int)pMVar2[2].pVptr + 0x30))(pMVar2 + 2,0x80,0x80,0x80);
      (**(code **)((int)pMVar2[2].pVptr + 0x2c))(pMVar2 + 2,0x80);
      pMVar2[2].bFlags = pMVar2[2].bFlags & 0xfe | 1;
      pMVar2[2].nCol = 3;
      pMVar2[2].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 2));
      Open__10MenuWindowFUci((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),0,0x14d);
    }
    break;
  case 1:
    if (*(short *)(iStack_20 + iStack_10 * 0x114 + 0x62) == 0) {
      *(u16 *)(iStack_20 + iStack_10 * 0x114 + 0x62) = 1;
      *(u16 *)(iStack_20 + iStack_10 * 0x114 + 100) = 0;
      *(u32 *)(iStack_20 + iStack_10 * 0x114 + 0x68) = 0;
      *(u16 *)(iStack_20 + iStack_10 * 0x114 + 0xc0) = 10;
      AddOT__7MenuObjFv((MenuObj *)(iStack_20 + iStack_10 * 0x114 + 0xac));
      iVar8 = iStack_20 + iStack_10 * 0x114;
      *(byte *)(iVar8 + 0x60) = *(byte *)(iVar8 + 0x60) & 0xfb | 4;
      Create__10MenuWindowFUcUcffff
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),0,1,0.0,0.0,512.0,448.0);
      iVar8 = iStack_20 + iStack_10 * 0x114;
      *(byte *)(iVar8 + 0x60) = *(byte *)(iVar8 + 0x60) & 0xf7 | 8;
      if (*(int *)(iStack_20 + iStack_10 * 0x114 + 0x164) == 0) {
        uVar11 = __nwa__FUi(0x130);
        uVar9 = __construct_new_array(uVar11,0x277820,0x277890,0x30,6);
        *(u32 *)(iStack_20 + iStack_10 * 0x114 + 0x164) = uVar9;
      }
      if (*(int *)(iStack_20 + iStack_10 * 0x114 + 0x168) == 0) {
        uVar11 = __nwa__FUi(0xfd0);
        uVar9 = __construct_new_array(uVar11,0x266140,0x2661a0,0x60,0x2a);
        *(u32 *)(iStack_20 + iStack_10 * 0x114 + 0x168) = uVar9;
      }
      if (*(int *)(iStack_20 + iStack_10 * 0x114 + 0x16c) == 0) {
        uVar11 = __nwa__FUi(0x94);
        uVar9 = __construct_new_array(uVar11,0x276640,0x2766d0,0x84,1);
        *(u32 *)(iStack_20 + iStack_10 * 0x114 + 0x16c) = uVar9;
      }
      if (*(int *)(iStack_20 + iStack_10 * 0x114 + 0x170) == 0) {
        uVar11 = __nwa__FUi(0x60);
        uVar9 = __construct_new_array(uVar11,0x28d000,0x28d070,0x28,2);
        *(u32 *)(iStack_20 + iStack_10 * 0x114 + 0x170) = uVar9;
      }
      bVar6 = true;
    }
    else {
      bVar6 = false;
    }
    pMVar2 = *(MenuSprite **)(iStack_20 + iStack_10 * 0x114 + 0x168);
    pMVar3 = *(MenuPolygon **)(iStack_20 + iStack_10 * 0x114 + 0x16c);
    iStack_48 = *(int *)(iStack_20 + iStack_10 * 0x114 + 0x170);
    iStack_28 = 0;
    iStack_30 = 0;
    if (bVar6) {
      Create__11MenuPolygonFUcUc(pMVar3,0,1);
      pMVar3->nPriority = 0;
      SetVertex__11MenuPolygonFiffb(pMVar3,0,361.0,54.0,true);
      SetColor__11MenuPolygonFiUcUcUc(pMVar3,0,0x41,0x41,0x4e);
      pMVar3->bA = 0x4c;
      UpdateRgba__7MenuObjFv((MenuObj *)pMVar3);
      SetVertex__11MenuPolygonFiffb(pMVar3,1,361.0,196.0,true);
      SetColor__11MenuPolygonFiUcUcUc(pMVar3,1,10,8,10);
      pMVar3->field_0x77 = 0x4c;
      UpdateRgba__7MenuObjFv((MenuObj *)pMVar3);
      SetVertex__11MenuPolygonFiffb(pMVar3,2,492.0,54.0,true);
      SetColor__11MenuPolygonFiUcUcUc(pMVar3,2,0x41,0x41,0x4e);
      pMVar3->field_0x7b = 0x4c;
      UpdateRgba__7MenuObjFv((MenuObj *)pMVar3);
      SetVertex__11MenuPolygonFiffb(pMVar3,3,492.0,196.0,true);
      SetColor__11MenuPolygonFiUcUcUc(pMVar3,3,10,8,10);
      pMVar3->field_0x7f = 0x4c;
      UpdateRgba__7MenuObjFv((MenuObj *)pMVar3);
      pMVar3->bFlags = pMVar3->bFlags & 0xfe | 1;
      pMVar3->nCol = 0;
      pMVar3->nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)pMVar3);
      iStack_74 = *(int *)(ourBtlSocket__9BtlSocket + 0x614);
      uStack_f8 = *(u32 *)(iStack_74 + (uint)*(ushort *)(iStack_74 + 10) * 4 + 0xc);
      uStack_f4 = uStack_f8;
      uVar11 = GetTex0__6JRCTexFb(*(u32 *)(ourBtlSocket__9BtlSocket + 0x614),0);
      Create__11SendOnLocalFP4_QWDUl
                (*(int *)(iStack_20 + iStack_10 * 0x114 + 0x164) + iStack_28 * 0x30,uStack_f8,uVar11
                );
      iStack_78 = *(int *)(iStack_20 + iStack_10 * 0x114 + 0x164) + iStack_28 * 0x30;
      *(u16 *)(iStack_78 + 0x14) = 1;
      AddPriority__12MenuObjTableFP7MenuObj
                ((MenuObjTable *)(iStack_20 + iStack_10 * 0x114 + 0xc4),
                 (MenuObj *)(*(int *)(iStack_20 + iStack_10 * 0x114 + 0x164) + iStack_28 * 0x30));
    }
    iStack_28 = iStack_28 + 1;
    if (bVar6) {
      Create__10MenuSpriteFUc(pMVar2,1);
      pMVar2->bPflags = pMVar2->bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)pMVar2);
      pMVar2->nPriority = 2;
      (**(code **)((int)pMVar2->pVptr + 0x24))(0x43c18000,0x42440000);
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2,2,0x46,0x26,0x4d);
      (**(code **)((int)pMVar2->pVptr + 0x28))(0x42a20000,0x40e00000);
      (**(code **)((int)pMVar2->pVptr + 0x30))(pMVar2,0x80,0x80,0x80);
      (**(code **)((int)pMVar2->pVptr + 0x2c))(pMVar2,0x80);
      pMVar2->bFlags = pMVar2->bFlags & 0xfe | 1;
      pMVar2->nCol = 1;
      pMVar2->nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)pMVar2);
      Create__10MenuSpriteFUc(pMVar2 + 1,1);
      pMVar2[1].bPflags = pMVar2[1].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 1));
      pMVar2[1].nPriority = 2;
      (**(code **)((int)pMVar2[1].pVptr + 0x24))(0x43c20000,0x43420000);
      uVar11 = 0x26;
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 1,0x26,0x4d,2,0x46);
      uVar11 = (**(code **)((int)pMVar2[1].pVptr + 0x28))(0x429e0000,0x40e00000,pMVar2 + 1,1,uVar11)
      ;
      (**(code **)((int)pMVar2[1].pVptr + 0x30))(pMVar2 + 1,0x80,0x80,0x80,0x60,0x80,uVar11);
      (**(code **)((int)pMVar2[1].pVptr + 0x2c))(pMVar2 + 1,0x80);
      pMVar2[1].bFlags = pMVar2[1].bFlags & 0xfe | 1;
      pMVar2[1].nCol = 2;
      pMVar2[1].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 1));
      Create__10MenuSpriteFUc(pMVar2 + 2,1);
      pMVar2[2].bPflags = pMVar2[2].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 2));
      pMVar2[2].nPriority = 2;
      (**(code **)((int)pMVar2[2].pVptr + 0x24))(0x43ae8000,0x42a00000);
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 2,0,0x4f,0xe,0x65);
      (**(code **)((int)pMVar2[2].pVptr + 0x28))(0x41600000,0x42860000);
      (**(code **)((int)pMVar2[2].pVptr + 0x30))(pMVar2 + 2,0x80,0x80,0x80);
      (**(code **)((int)pMVar2[2].pVptr + 0x2c))(pMVar2 + 2,0x80);
      pMVar2[2].bFlags = pMVar2[2].bFlags & 0xfe | 1;
      pMVar2[2].nCol = 3;
      pMVar2[2].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 2));
      Create__10MenuSpriteFUc(pMVar2 + 3,1);
      pMVar2[3].bPflags = pMVar2[3].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 3));
      pMVar2[3].nPriority = 2;
      (**(code **)((int)pMVar2[3].pVptr + 0x24))(0x43f50000,0x42d40000);
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 3,0xe,0x65,0,0x4f);
      (**(code **)((int)pMVar2[3].pVptr + 0x28))(0x41600000,0x42820000);
      (**(code **)((int)pMVar2[3].pVptr + 0x30))(pMVar2 + 3,0x80,0x80,0x80);
      (**(code **)((int)pMVar2[3].pVptr + 0x2c))(pMVar2 + 3,0x80);
      pMVar2[3].bFlags = pMVar2[3].bFlags & 0xfe | 1;
      pMVar2[3].nCol = 4;
      pMVar2[3].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 3));
      Create__10MenuSpriteFUc(pMVar2 + 4,1);
      pMVar2[4].bPflags = pMVar2[4].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 4));
      pMVar2[4].nPriority = 3;
      (**(code **)((int)pMVar2[4].pVptr + 0x24))(0x43aa0000,0x42280000);
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 4,0,0x1d,0x30,0x38);
      (**(code **)((int)pMVar2[4].pVptr + 0x28))(0x42400000,0x41d80000);
      (**(code **)((int)pMVar2[4].pVptr + 0x30))(pMVar2 + 4,0x80,0x80,0x80);
      (**(code **)((int)pMVar2[4].pVptr + 0x2c))(pMVar2 + 4,0x80);
      pMVar2[4].bFlags = pMVar2[4].bFlags & 0xfe | 1;
      pMVar2[4].nCol = 5;
      pMVar2[4].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 4));
      Create__10MenuSpriteFUc(pMVar2 + 5,1);
      pMVar2[5].bPflags = pMVar2[5].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 5));
      pMVar2[5].nPriority = 3;
      (**(code **)((int)pMVar2[5].pVptr + 0x24))(0x43aa0000,0x42860000);
      uVar11 = 5;
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 5,0,0x38,0x1a,0x46);
      (**(code **)((int)pMVar2[5].pVptr + 0x28))(0x41d00000,0x41600000,pMVar2 + 5,uVar11);
      (**(code **)((int)pMVar2[5].pVptr + 0x30))(pMVar2 + 5,0x80,0x80,0x80);
      (**(code **)((int)pMVar2[5].pVptr + 0x2c))(pMVar2 + 5,0x80);
      pMVar2[5].bFlags = pMVar2[5].bFlags & 0xfe | 1;
      pMVar2[5].nCol = 6;
      pMVar2[5].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 5));
      Create__10MenuSpriteFUc(pMVar2 + 6,1);
      pMVar2[6].bPflags = pMVar2[6].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 6));
      pMVar2[6].nPriority = 3;
      (**(code **)((int)pMVar2[6].pVptr + 0x24))(0x43ad8000,0x43120000);
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 6,0x30,0x1d,0x5a,0x5c);
      (**(code **)((int)pMVar2[6].pVptr + 0x28))(0x42280000,0x427c0000);
      (**(code **)((int)pMVar2[6].pVptr + 0x30))(pMVar2 + 6,0x80,0x80,0x80);
      (**(code **)((int)pMVar2[6].pVptr + 0x2c))(pMVar2 + 6,0x80);
      pMVar2[6].bFlags = pMVar2[6].bFlags & 0xfe | 1;
      pMVar2[6].nCol = 7;
      pMVar2[6].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 6));
      Create__10MenuSpriteFUc(pMVar2 + 7,1);
      uVar11 = 7;
      pMVar2[7].bPflags = pMVar2[7].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 7));
      pMVar2[7].nPriority = 3;
      (**(code **)((int)pMVar2[7].pVptr + 0x24))(0x43e80000,0x422c0000,pMVar2 + 7,3,uVar11);
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 7,0x5c,0x5a,0x30,0x1d);
      (**(code **)((int)pMVar2[7].pVptr + 0x28))(0x42280000,0x427c0000);
      (**(code **)((int)pMVar2[7].pVptr + 0x30))(pMVar2 + 7,0x80,0x80,0x80);
      (**(code **)((int)pMVar2[7].pVptr + 0x2c))(pMVar2 + 7,0x80);
      pMVar2[7].bFlags = pMVar2[7].bFlags & 0xfe | 1;
      pMVar2[7].nCol = 8;
      pMVar2[7].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 7));
      Create__10MenuSpriteFUc(pMVar2 + 8,1);
      pMVar2[8].bPflags = pMVar2[8].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 8));
      pMVar2[8].nPriority = 3;
      (**(code **)((int)pMVar2[8].pVptr + 0x24))(0x43f38000,0x43290000);
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 8,0x1a,0x46,0,0x38);
      (**(code **)((int)pMVar2[8].pVptr + 0x28))(0x41d00000,0x41600000);
      (**(code **)((int)pMVar2[8].pVptr + 0x30))(pMVar2 + 8,0x80,0x80,0x80);
      (**(code **)((int)pMVar2[8].pVptr + 0x2c))(pMVar2 + 8,0x80);
      pMVar2[8].bFlags = pMVar2[8].bFlags & 0xfe | 1;
      pMVar2[8].nCol = 9;
      pMVar2[8].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 8));
      Create__10MenuSpriteFUc(pMVar2 + 9,1);
      pMVar2[9].bPflags = pMVar2[9].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 9));
      pMVar2[9].nPriority = 3;
      (**(code **)((int)pMVar2[9].pVptr + 0x24))(0x43e88000,0x43350000);
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 9,0x30,0x38,0,0x1d);
      (**(code **)((int)pMVar2[9].pVptr + 0x28))(0x42400000,0x41d80000);
      (**(code **)((int)pMVar2[9].pVptr + 0x30))(pMVar2 + 9,0x80,0x80,0x80);
      (**(code **)((int)pMVar2[9].pVptr + 0x2c))(pMVar2 + 9,0x80);
      pMVar2[9].bFlags = pMVar2[9].bFlags & 0xfe | 1;
      pMVar2[9].nCol = 10;
      pMVar2[9].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 9));
      iStack_7c = *(int *)(ourBtlSocket__9BtlSocket + 0x66c);
      uStack_100 = *(u32 *)(iStack_7c + (uint)*(ushort *)(iStack_7c + 10) * 4 + 0xc);
      uStack_fc = uStack_100;
      uVar11 = GetTex0__6JRCTexFb(*(u32 *)(ourBtlSocket__9BtlSocket + 0x66c),0);
      Create__11SendOnLocalFP4_QWDUl
                (*(int *)(iStack_20 + iStack_10 * 0x114 + 0x164) + iStack_28 * 0x30,uStack_100,
                 uVar11);
      iStack_80 = *(int *)(iStack_20 + iStack_10 * 0x114 + 0x164) + iStack_28 * 0x30;
      *(u16 *)(iStack_80 + 0x14) = 4;
      AddPriority__12MenuObjTableFP7MenuObj
                ((MenuObjTable *)(iStack_20 + iStack_10 * 0x114 + 0xc4),
                 (MenuObj *)(*(int *)(iStack_20 + iStack_10 * 0x114 + 0x164) + iStack_28 * 0x30));
      Create__10MenuSpriteFUc(pMVar2 + 10,1);
      pMVar2[10].bPflags = pMVar2[10].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 10));
      pMVar2[10].nPriority = 5;
      (**(code **)((int)pMVar2[10].pVptr + 0x24))(0x43b48000,0x42b80000);
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 10,0,0,0x7b,6);
      (**(code **)((int)pMVar2[10].pVptr + 0x28))(0x43030000,0x40c00000);
      uVar11 = (**(code **)((int)pMVar2[10].pVptr + 0x30))(pMVar2 + 10,0x80,0x80,0x80);
      (**(code **)((int)pMVar2[10].pVptr + 0x2c))(pMVar2 + 10,0x80,uVar11);
      pMVar2[10].bFlags = pMVar2[10].bFlags & 0xfe | 1;
      pMVar2[10].nCol = 0xb;
      pMVar2[10].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 10));
    }
    iStack_28 = iStack_28 + 1;
    if (bVar6) {
      iStack_84 = *(int *)(ourBtlSocket__9BtlSocket + 0x618);
      uStack_108 = *(u32 *)(iStack_84 + (uint)*(ushort *)(iStack_84 + 10) * 4 + 0xc);
      uStack_104 = uStack_108;
      uVar11 = GetTex0__6JRCTexFb(*(u32 *)(ourBtlSocket__9BtlSocket + 0x618),0);
      Create__11SendOnLocalFP4_QWDUl
                (*(int *)(iStack_20 + iStack_10 * 0x114 + 0x164) + iStack_28 * 0x30,uStack_108,
                 uVar11);
      iStack_88 = *(int *)(iStack_20 + iStack_10 * 0x114 + 0x164) + iStack_28 * 0x30;
      *(u16 *)(iStack_88 + 0x14) = 6;
      AddPriority__12MenuObjTableFP7MenuObj
                ((MenuObjTable *)(iStack_20 + iStack_10 * 0x114 + 0xc4),
                 (MenuObj *)(*(int *)(iStack_20 + iStack_10 * 0x114 + 0x164) + iStack_28 * 0x30));
      CreatePacket__10MenuPacketFUs((MenuPacket *)(iStack_48 + iStack_30 * 0x28 + 0x18),5);
      uStack_158 = GetTex0__6JRCTexFb(*(u32 *)(ourBtlSocket__9BtlSocket + 0x618),1);
      SetRegister__12MenuRegisterFiUlUl
                (iStack_48 + iStack_30 * 0x28,0,0x16,
                 uStack_158 & 0xfffffffc0fffff | 0x2000000001300000);
      SetRegister__12MenuRegisterFiUlUl
                (iStack_48 + iStack_30 * 0x28,1,6,uStack_158 & 0xffffffffffffff | 0x600000000000000)
      ;
      *(u16 *)(iStack_48 + iStack_30 * 0x28 + 0x14) = 7;
      AddPriority__12MenuObjTableFP7MenuObj
                ((MenuObjTable *)(iStack_20 + iStack_10 * 0x114 + 0xc4),
                 (MenuObj *)(iStack_48 + iStack_30 * 0x28));
      Create__10MenuSpriteFUc(pMVar2 + 0xb,1);
      pMVar2[0xb].bPflags = pMVar2[0xb].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 0xb));
      pMVar2[0xb].nPriority = 8;
      (**(code **)((int)pMVar2[0xb].pVptr + 0x24))(0x43bc0000,0x427c0000);
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 0xb,0,0x18,0x5d,0x2f);
      uVar11 = (**(code **)((int)pMVar2[0xb].pVptr + 0x28))(0x42ba0000,0x41b80000);
      uVar11 = (**(code **)((int)pMVar2[0xb].pVptr + 0x30))(pMVar2 + 0xb,0x80,0x80,0x80,0x80,uVar11)
      ;
      (**(code **)((int)pMVar2[0xb].pVptr + 0x2c))(pMVar2 + 0xb,0x80,0x80,uVar11);
      pMVar2[0xb].bFlags = pMVar2[0xb].bFlags & 0xfe | 1;
      pMVar2[0xb].nCol = 0xc;
      pMVar2[0xb].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 0xb));
    }
    iStack_28 = iStack_28 + 1;
    iStack_30 = iStack_30 + 1;
    if (bVar6) {
      iStack_8c = *(int *)(ourBtlSocket__9BtlSocket + 0x61c);
      uStack_110 = *(u32 *)(iStack_8c + (uint)*(ushort *)(iStack_8c + 10) * 4 + 0xc);
      uStack_10c = uStack_110;
      uVar11 = GetTex0__6JRCTexFb(*(u32 *)(ourBtlSocket__9BtlSocket + 0x61c),0);
      Create__11SendOnLocalFP4_QWDUl
                (*(int *)(iStack_20 + iStack_10 * 0x114 + 0x164) + iStack_28 * 0x30,uStack_110,
                 uVar11);
      iStack_90 = *(int *)(iStack_20 + iStack_10 * 0x114 + 0x164) + iStack_28 * 0x30;
      *(u16 *)(iStack_90 + 0x14) = 9;
      AddPriority__12MenuObjTableFP7MenuObj
                ((MenuObjTable *)(iStack_20 + iStack_10 * 0x114 + 0xc4),
                 (MenuObj *)(*(int *)(iStack_20 + iStack_10 * 0x114 + 0x164) + iStack_28 * 0x30));
    }
    iStack_28 = iStack_28 + 1;
    if (bVar6) {
      Create__10MenuSpriteFUc(pMVar2 + 0xc,1);
      pMVar2[0xc].bPflags = pMVar2[0xc].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 0xc));
      pMVar2[0xc].nPriority = 10;
      if ((long)((ulong)*(byte *)((int)ourBtlSaveDat__10BtlSaveSec + 3) << 0x3d) < 0) {
        (**(code **)((int)pMVar2[0xc].pVptr + 0x24))(0x43bd8000,0x42d40000);
      }
      else {
        (**(code **)((int)pMVar2[0xc].pVptr + 0x24))(0x43bd8000,0x42ee0000);
      }
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 0xc,0,0,0x29,0x19);
      (**(code **)((int)pMVar2[0xc].pVptr + 0x28))(0x42240000,0x41c80000);
      (**(code **)((int)pMVar2[0xc].pVptr + 0x30))(pMVar2 + 0xc,0x41,0x3f,0x4b);
      (**(code **)((int)pMVar2[0xc].pVptr + 0x2c))(pMVar2 + 0xc,0x80);
      pMVar2[0xc].bFlags = pMVar2[0xc].bFlags & 0xfe | 1;
      pMVar2[0xc].nCol = 0xd;
      pMVar2[0xc].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 0xc));
      Create__10MenuSpriteFUc(pMVar2 + 0xd,1);
      pMVar2[0xd].bPflags = pMVar2[0xd].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 0xd));
      pMVar2[0xd].nPriority = 10;
      if ((long)((ulong)*(byte *)((int)ourBtlSaveDat__10BtlSaveSec + 3) << 0x3d) < 0) {
        (**(code **)((int)pMVar2[0xd].pVptr + 0x24))(0x43b80000,0x43050000);
      }
      else {
        (**(code **)((int)pMVar2[0xd].pVptr + 0x24))(0x43b80000,0x43120000);
      }
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 0xd,0x29,0,0x5d,0x16);
      (**(code **)((int)pMVar2[0xd].pVptr + 0x28))(0x42500000,0x41b00000);
      (**(code **)((int)pMVar2[0xd].pVptr + 0x30))(pMVar2 + 0xd,0x41,0x3f,0x4b);
      (**(code **)((int)pMVar2[0xd].pVptr + 0x2c))(pMVar2 + 0xd,0x80);
      pMVar2[0xd].bFlags = pMVar2[0xd].bFlags & 0xfe | 1;
      pMVar2[0xd].nCol = 0xe;
      pMVar2[0xd].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 0xd));
      Create__10MenuSpriteFUc(pMVar2 + 0xe,1);
      pMVar2[0xe].bPflags = pMVar2[0xe].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 0xe));
      pMVar2[0xe].nPriority = 10;
      (**(code **)((int)pMVar2[0xe].pVptr + 0x24))(0x43ba0000,0x431f0000);
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 0xe,0x5d,0,0x8d,0x16);
      (**(code **)((int)pMVar2[0xe].pVptr + 0x28))(0x42400000,0x41b00000);
      (**(code **)((int)pMVar2[0xe].pVptr + 0x30))(pMVar2 + 0xe,0x41,0x3f,0x4b);
      (**(code **)((int)pMVar2[0xe].pVptr + 0x2c))(pMVar2 + 0xe,0x80);
      if ((long)((ulong)*(byte *)((int)ourBtlSaveDat__10BtlSaveSec + 3) << 0x3d) < 0) {
        pMVar2[0xe].bFlags = pMVar2[0xe].bFlags & 0xfe | 1;
      }
      else {
        pMVar2[0xe].bFlags = pMVar2[0xe].bFlags & 0xfe;
      }
      pMVar2[0xe].nCol = 0xf;
      pMVar2[0xe].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 0xe));
    }
    iVar8 = *(int *)(iStack_20 + 0xda4);
    if (bVar6) {
      Create__10MenuSpriteFUc(pMVar2 + 0xf,1);
      pMVar2[0xf].bPflags = pMVar2[0xf].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 0xf));
      pMVar2[0xf].nPriority = 10;
      if ((long)((ulong)*(byte *)((int)ourBtlSaveDat__10BtlSaveSec + 3) << 0x3d) < 0) {
        (**(code **)((int)pMVar2[0xf].pVptr + 0x24))(0x43d20000,0x42d40000);
      }
      else {
        (**(code **)((int)pMVar2[0xf].pVptr + 0x24))(0x43d20000,0x42ee0000);
      }
      (**(code **)((int)pMVar2[0xf].pVptr + 0x28))(0x41500000,0x41b00000);
      (**(code **)((int)pMVar2[0xf].pVptr + 0x30))(pMVar2 + 0xf,0x58,0x58,0x58);
      (**(code **)((int)pMVar2[0xf].pVptr + 0x2c))(pMVar2 + 0xf,0x80);
      pMVar2[0xf].nCol = 0x10;
      pMVar2[0xf].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 0xf));
    }
    if (iVar8 < 100000) {
      pMVar2[0xf].bFlags = pMVar2[0xf].bFlags & 0xfe;
    }
    else {
      sVar7 = (short)((iVar8 / 100000) % 10);
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 0xf,sVar7 * 0xd,0x19,(sVar7 + 1) * 0xd,0x2f);
      pMVar2[0xf].bFlags = pMVar2[0xf].bFlags & 0xfe | 1;
    }
    if (bVar6) {
      Create__10MenuSpriteFUc(pMVar2 + 0x10,1);
      pMVar2[0x10].bPflags = pMVar2[0x10].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 0x10));
      pMVar2[0x10].nPriority = 10;
      if ((long)((ulong)*(byte *)((int)ourBtlSaveDat__10BtlSaveSec + 3) << 0x3d) < 0) {
        (**(code **)((int)pMVar2[0x10].pVptr + 0x24))(0x43d78000,0x42d40000);
      }
      else {
        (**(code **)((int)pMVar2[0x10].pVptr + 0x24))(0x43d78000,0x42ee0000);
      }
      (**(code **)((int)pMVar2[0x10].pVptr + 0x28))(0x41500000,0x41b00000);
      (**(code **)((int)pMVar2[0x10].pVptr + 0x30))(pMVar2 + 0x10,0x58,0x58,0x58);
      (**(code **)((int)pMVar2[0x10].pVptr + 0x2c))(pMVar2 + 0x10,0x80);
      pMVar2[0x10].nCol = 0x11;
      pMVar2[0x10].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 0x10));
    }
    if (iVar8 < 10000) {
      pMVar2[0x10].bFlags = pMVar2[0x10].bFlags & 0xfe;
    }
    else {
      sVar7 = (short)((iVar8 / 10000) % 10);
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 0x10,sVar7 * 0xd,0x19,(sVar7 + 1) * 0xd,0x2f);
      pMVar2[0x10].bFlags = pMVar2[0x10].bFlags & 0xfe | 1;
    }
    if (bVar6) {
      Create__10MenuSpriteFUc(pMVar2 + 0x11,1);
      pMVar2[0x11].bPflags = pMVar2[0x11].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 0x11));
      pMVar2[0x11].nPriority = 10;
      if ((long)((ulong)*(byte *)((int)ourBtlSaveDat__10BtlSaveSec + 3) << 0x3d) < 0) {
        (**(code **)((int)pMVar2[0x11].pVptr + 0x24))(0x43dd0000,0x42d40000);
      }
      else {
        (**(code **)((int)pMVar2[0x11].pVptr + 0x24))(0x43dd0000,0x42ee0000);
      }
      (**(code **)((int)pMVar2[0x11].pVptr + 0x28))(0x41500000,0x41b00000);
      (**(code **)((int)pMVar2[0x11].pVptr + 0x30))(pMVar2 + 0x11,0x58,0x58,0x58);
      (**(code **)((int)pMVar2[0x11].pVptr + 0x2c))(pMVar2 + 0x11,0x80);
      pMVar2[0x11].nCol = 0x12;
      pMVar2[0x11].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 0x11));
    }
    if (iVar8 < 1000) {
      pMVar2[0x11].bFlags = pMVar2[0x11].bFlags & 0xfe;
    }
    else {
      sVar7 = (short)((iVar8 / 1000) % 10);
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 0x11,sVar7 * 0xd,0x19,(sVar7 + 1) * 0xd,0x2f);
      pMVar2[0x11].bFlags = pMVar2[0x11].bFlags & 0xfe | 1;
    }
    if (bVar6) {
      Create__10MenuSpriteFUc(pMVar2 + 0x12,1);
      pMVar2[0x12].bPflags = pMVar2[0x12].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 0x12));
      pMVar2[0x12].nPriority = 10;
      if ((long)((ulong)*(byte *)((int)ourBtlSaveDat__10BtlSaveSec + 3) << 0x3d) < 0) {
        (**(code **)((int)pMVar2[0x12].pVptr + 0x24))(0x43e28000,0x42d40000);
      }
      else {
        (**(code **)((int)pMVar2[0x12].pVptr + 0x24))(0x43e28000,0x42ee0000);
      }
      (**(code **)((int)pMVar2[0x12].pVptr + 0x28))(0x41500000,0x41b00000);
      (**(code **)((int)pMVar2[0x12].pVptr + 0x30))(pMVar2 + 0x12,0x58,0x58,0x58);
      (**(code **)((int)pMVar2[0x12].pVptr + 0x2c))(pMVar2 + 0x12,0x80);
      pMVar2[0x12].nCol = 0x13;
      pMVar2[0x12].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 0x12));
    }
    if (iVar8 < 100) {
      pMVar2[0x12].bFlags = pMVar2[0x12].bFlags & 0xfe;
    }
    else {
      sVar7 = (short)((iVar8 / 100) % 10);
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 0x12,sVar7 * 0xd,0x19,(sVar7 + 1) * 0xd,0x2f);
      pMVar2[0x12].bFlags = pMVar2[0x12].bFlags & 0xfe | 1;
    }
    if (bVar6) {
      Create__10MenuSpriteFUc(pMVar2 + 0x13,1);
      pMVar2[0x13].bPflags = pMVar2[0x13].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 0x13));
      pMVar2[0x13].nPriority = 10;
      if ((long)((ulong)*(byte *)((int)ourBtlSaveDat__10BtlSaveSec + 3) << 0x3d) < 0) {
        (**(code **)((int)pMVar2[0x13].pVptr + 0x24))(0x43e80000,0x42d40000);
      }
      else {
        (**(code **)((int)pMVar2[0x13].pVptr + 0x24))(0x43e80000,0x42ee0000);
      }
      (**(code **)((int)pMVar2[0x13].pVptr + 0x28))(0x41500000,0x41b00000);
      uVar11 = (**(code **)((int)pMVar2[0x13].pVptr + 0x30))(pMVar2 + 0x13,0x58,0x58,0x58);
      (**(code **)((int)pMVar2[0x13].pVptr + 0x2c))(pMVar2 + 0x13,0x80,uVar11);
      pMVar2[0x13].nCol = 0x14;
      pMVar2[0x13].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 0x13));
    }
    if (iVar8 < 10) {
      pMVar2[0x13].bFlags = pMVar2[0x13].bFlags & 0xfe;
    }
    else {
      sVar7 = (short)((iVar8 / 10) % 10);
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 0x13,sVar7 * 0xd,0x19,(sVar7 + 1) * 0xd,0x2f);
      pMVar2[0x13].bFlags = pMVar2[0x13].bFlags & 0xfe | 1;
    }
    if (bVar6) {
      Create__10MenuSpriteFUc(pMVar2 + 0x14,1);
      pMVar2[0x14].bPflags = pMVar2[0x14].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 0x14));
      pMVar2[0x14].nPriority = 10;
      if ((long)((ulong)*(byte *)((int)ourBtlSaveDat__10BtlSaveSec + 3) << 0x3d) < 0) {
        (**(code **)((int)pMVar2[0x14].pVptr + 0x24))(0x43ed8000,0x42d40000);
      }
      else {
        (**(code **)((int)pMVar2[0x14].pVptr + 0x24))(0x43ed8000,0x42ee0000);
      }
      (**(code **)((int)pMVar2[0x14].pVptr + 0x28))(0x41500000,0x41b00000);
      (**(code **)((int)pMVar2[0x14].pVptr + 0x30))(pMVar2 + 0x14,0x58,0x58,0x58);
      (**(code **)((int)pMVar2[0x14].pVptr + 0x2c))(pMVar2 + 0x14,0x80);
      pMVar2[0x14].nCol = 0x15;
      pMVar2[0x14].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 0x14));
    }
    sVar7 = (short)(iVar8 % 10);
    SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 0x14,sVar7 * 0xd,0x19,(sVar7 + 1) * 0xd,0x2f);
    pMVar2[0x14].bFlags = pMVar2[0x14].bFlags & 0xfe | 1;
    iVar8 = *(int *)(iStack_20 + 0xdac);
    if (bVar6) {
      Create__10MenuSpriteFUc(pMVar2 + 0x15,1);
      pMVar2[0x15].bPflags = pMVar2[0x15].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 0x15));
      pMVar2[0x15].nPriority = 10;
      if ((long)((ulong)*(byte *)((int)ourBtlSaveDat__10BtlSaveSec + 3) << 0x3d) < 0) {
        (**(code **)((int)pMVar2[0x15].pVptr + 0x24))(0x43d20000,0x43050000);
      }
      else {
        (**(code **)((int)pMVar2[0x15].pVptr + 0x24))(0x43d20000,0x43120000);
      }
      (**(code **)((int)pMVar2[0x15].pVptr + 0x28))(0x41500000,0x41b00000);
      (**(code **)((int)pMVar2[0x15].pVptr + 0x30))(pMVar2 + 0x15,0x58,0x58,0x58);
      (**(code **)((int)pMVar2[0x15].pVptr + 0x2c))(pMVar2 + 0x15,0x80);
      pMVar2[0x15].nCol = 0x16;
      pMVar2[0x15].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 0x15));
    }
    if (iVar8 < 100000) {
      pMVar2[0x15].bFlags = pMVar2[0x15].bFlags & 0xfe;
    }
    else {
      sVar7 = (short)((iVar8 / 100000) % 10);
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 0x15,sVar7 * 0xd,0x19,(sVar7 + 1) * 0xd,0x2f);
      pMVar2[0x15].bFlags = pMVar2[0x15].bFlags & 0xfe | 1;
    }
    if (bVar6) {
      Create__10MenuSpriteFUc(pMVar2 + 0x16,1);
      pMVar2[0x16].bPflags = pMVar2[0x16].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 0x16));
      pMVar2[0x16].nPriority = 10;
      if ((long)((ulong)*(byte *)((int)ourBtlSaveDat__10BtlSaveSec + 3) << 0x3d) < 0) {
        (**(code **)((int)pMVar2[0x16].pVptr + 0x24))(0x43d78000,0x43050000);
      }
      else {
        (**(code **)((int)pMVar2[0x16].pVptr + 0x24))(0x43d78000,0x43120000);
      }
      (**(code **)((int)pMVar2[0x16].pVptr + 0x28))(0x41500000,0x41b00000);
      (**(code **)((int)pMVar2[0x16].pVptr + 0x30))(pMVar2 + 0x16,0x58,0x58,0x58);
      (**(code **)((int)pMVar2[0x16].pVptr + 0x2c))(pMVar2 + 0x16,0x80);
      pMVar2[0x16].nCol = 0x17;
      pMVar2[0x16].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 0x16));
    }
    if (iVar8 < 10000) {
      pMVar2[0x16].bFlags = pMVar2[0x16].bFlags & 0xfe;
    }
    else {
      sVar7 = (short)((iVar8 / 10000) % 10);
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 0x16,sVar7 * 0xd,0x19,(sVar7 + 1) * 0xd,0x2f);
      pMVar2[0x16].bFlags = pMVar2[0x16].bFlags & 0xfe | 1;
    }
    if (bVar6) {
      Create__10MenuSpriteFUc(pMVar2 + 0x17,1);
      pMVar2[0x17].bPflags = pMVar2[0x17].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 0x17));
      pMVar2[0x17].nPriority = 10;
      if ((long)((ulong)*(byte *)((int)ourBtlSaveDat__10BtlSaveSec + 3) << 0x3d) < 0) {
        (**(code **)((int)pMVar2[0x17].pVptr + 0x24))(0x43dd0000,0x43050000);
      }
      else {
        (**(code **)((int)pMVar2[0x17].pVptr + 0x24))(0x43dd0000,0x43120000);
      }
      (**(code **)((int)pMVar2[0x17].pVptr + 0x28))(0x41500000,0x41b00000);
      (**(code **)((int)pMVar2[0x17].pVptr + 0x30))(pMVar2 + 0x17,0x58,0x58,0x58);
      (**(code **)((int)pMVar2[0x17].pVptr + 0x2c))(pMVar2 + 0x17,0x80);
      pMVar2[0x17].nCol = 0x18;
      pMVar2[0x17].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 0x17));
    }
    if (iVar8 < 1000) {
      pMVar2[0x17].bFlags = pMVar2[0x17].bFlags & 0xfe;
    }
    else {
      sVar7 = (short)((iVar8 / 1000) % 10);
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 0x17,sVar7 * 0xd,0x19,(sVar7 + 1) * 0xd,0x2f);
      pMVar2[0x17].bFlags = pMVar2[0x17].bFlags & 0xfe | 1;
    }
    if (bVar6) {
      Create__10MenuSpriteFUc(pMVar2 + 0x18,1);
      pMVar2[0x18].bPflags = pMVar2[0x18].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 0x18));
      pMVar2[0x18].nPriority = 10;
      if ((long)((ulong)*(byte *)((int)ourBtlSaveDat__10BtlSaveSec + 3) << 0x3d) < 0) {
        (**(code **)((int)pMVar2[0x18].pVptr + 0x24))(0x43e28000,0x43050000);
      }
      else {
        (**(code **)((int)pMVar2[0x18].pVptr + 0x24))(0x43e28000,0x43120000);
      }
      (**(code **)((int)pMVar2[0x18].pVptr + 0x28))(0x41500000,0x41b00000);
      (**(code **)((int)pMVar2[0x18].pVptr + 0x30))(pMVar2 + 0x18,0x58,0x58,0x58);
      (**(code **)((int)pMVar2[0x18].pVptr + 0x2c))(pMVar2 + 0x18,0x80);
      pMVar2[0x18].nCol = 0x19;
      pMVar2[0x18].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 0x18));
    }
    if (iVar8 < 100) {
      pMVar2[0x18].bFlags = pMVar2[0x18].bFlags & 0xfe;
    }
    else {
      sVar7 = (short)((iVar8 / 100) % 10);
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 0x18,sVar7 * 0xd,0x19,(sVar7 + 1) * 0xd,0x2f);
      pMVar2[0x18].bFlags = pMVar2[0x18].bFlags & 0xfe | 1;
    }
    if (bVar6) {
      Create__10MenuSpriteFUc(pMVar2 + 0x19,1);
      pMVar2[0x19].bPflags = pMVar2[0x19].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 0x19));
      pMVar2[0x19].nPriority = 10;
      if ((long)((ulong)*(byte *)((int)ourBtlSaveDat__10BtlSaveSec + 3) << 0x3d) < 0) {
        (**(code **)((int)pMVar2[0x19].pVptr + 0x24))(0x43e80000,0x43050000);
      }
      else {
        (**(code **)((int)pMVar2[0x19].pVptr + 0x24))(0x43e80000,0x43120000);
      }
      (**(code **)((int)pMVar2[0x19].pVptr + 0x28))(0x41500000,0x41b00000);
      (**(code **)((int)pMVar2[0x19].pVptr + 0x30))(pMVar2 + 0x19,0x58,0x58,0x58);
      (**(code **)((int)pMVar2[0x19].pVptr + 0x2c))(pMVar2 + 0x19,0x80);
      pMVar2[0x19].nCol = 0x1a;
      pMVar2[0x19].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 0x19));
    }
    if (iVar8 < 10) {
      pMVar2[0x19].bFlags = pMVar2[0x19].bFlags & 0xfe;
    }
    else {
      sVar7 = (short)((iVar8 / 10) % 10);
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 0x19,sVar7 * 0xd,0x19,(sVar7 + 1) * 0xd,0x2f);
      pMVar2[0x19].bFlags = pMVar2[0x19].bFlags & 0xfe | 1;
    }
    if (bVar6) {
      Create__10MenuSpriteFUc(pMVar2 + 0x1a,1);
      pMVar2[0x1a].bPflags = pMVar2[0x1a].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 0x1a));
      pMVar2[0x1a].nPriority = 10;
      if ((long)((ulong)*(byte *)((int)ourBtlSaveDat__10BtlSaveSec + 3) << 0x3d) < 0) {
        (**(code **)((int)pMVar2[0x1a].pVptr + 0x24))(0x43ed8000,0x43050000);
      }
      else {
        (**(code **)((int)pMVar2[0x1a].pVptr + 0x24))(0x43ed8000,0x43120000);
      }
      (**(code **)((int)pMVar2[0x1a].pVptr + 0x28))(0x41500000,0x41b00000);
      (**(code **)((int)pMVar2[0x1a].pVptr + 0x30))(pMVar2 + 0x1a,0x58,0x58,0x58);
      (**(code **)((int)pMVar2[0x1a].pVptr + 0x2c))(pMVar2 + 0x1a,0x80);
      pMVar2[0x1a].nCol = 0x1b;
      pMVar2[0x1a].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 0x1a));
    }
    sVar7 = (short)(iVar8 % 10);
    SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 0x1a,sVar7 * 0xd,0x19,(sVar7 + 1) * 0xd,0x2f);
    pMVar2[0x1a].bFlags = pMVar2[0x1a].bFlags & 0xfe | 1;
    iVar8 = *(int *)(iStack_20 + 0xdb4);
    if (bVar6) {
      Create__10MenuSpriteFUc(pMVar2 + 0x1b,1);
      pMVar2[0x1b].bPflags = pMVar2[0x1b].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 0x1b));
      pMVar2[0x1b].nPriority = 10;
      (**(code **)((int)pMVar2[0x1b].pVptr + 0x24))(0x43dd0000,0x431f0000);
      (**(code **)((int)pMVar2[0x1b].pVptr + 0x28))(0x41500000,0x41b00000);
      (**(code **)((int)pMVar2[0x1b].pVptr + 0x30))(pMVar2 + 0x1b,0x58,0x58,0x58);
      (**(code **)((int)pMVar2[0x1b].pVptr + 0x2c))(pMVar2 + 0x1b,0x80);
      pMVar2[0x1b].nCol = 0x1c;
      pMVar2[0x1b].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 0x1b));
    }
    if ((iVar8 < 1000) ||
       (-1 < (long)((ulong)*(byte *)((int)ourBtlSaveDat__10BtlSaveSec + 3) << 0x3d))) {
      pMVar2[0x1b].bFlags = pMVar2[0x1b].bFlags & 0xfe;
    }
    else {
      sVar7 = (short)((iVar8 / 1000) % 10);
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 0x1b,sVar7 * 0xd,0x19,(sVar7 + 1) * 0xd,0x2f);
      pMVar2[0x1b].bFlags = pMVar2[0x1b].bFlags & 0xfe | 1;
    }
    if (bVar6) {
      Create__10MenuSpriteFUc(pMVar2 + 0x1c,1);
      pMVar2[0x1c].bPflags = pMVar2[0x1c].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 0x1c));
      pMVar2[0x1c].nPriority = 10;
      uVar11 = (**(code **)((int)pMVar2[0x1c].pVptr + 0x24))(0x43e28000,0x431f0000);
      uVar11 = (**(code **)((int)pMVar2[0x1c].pVptr + 0x28))
                         (0x41500000,0x41b00000,pMVar2 + 0x1c,0x38,uVar11);
      (**(code **)((int)pMVar2[0x1c].pVptr + 0x30))(pMVar2 + 0x1c,0x58,0x58,0x58,uVar11);
      (**(code **)((int)pMVar2[0x1c].pVptr + 0x2c))(pMVar2 + 0x1c,0x80);
      pMVar2[0x1c].nCol = 0x1d;
      pMVar2[0x1c].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 0x1c));
    }
    if ((iVar8 < 100) ||
       (-1 < (long)((ulong)*(byte *)((int)ourBtlSaveDat__10BtlSaveSec + 3) << 0x3d))) {
      pMVar2[0x1c].bFlags = pMVar2[0x1c].bFlags & 0xfe;
    }
    else {
      sVar7 = (short)((iVar8 / 100) % 10);
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 0x1c,sVar7 * 0xd,0x19,(sVar7 + 1) * 0xd,0x2f);
      pMVar2[0x1c].bFlags = pMVar2[0x1c].bFlags & 0xfe | 1;
    }
    if (bVar6) {
      Create__10MenuSpriteFUc(pMVar2 + 0x1d,1);
      pMVar2[0x1d].bPflags = pMVar2[0x1d].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 0x1d));
      pMVar2[0x1d].nPriority = 10;
      (**(code **)((int)pMVar2[0x1d].pVptr + 0x24))(0x43e80000,0x431f0000);
      (**(code **)((int)pMVar2[0x1d].pVptr + 0x28))(0x41500000,0x41b00000);
      (**(code **)((int)pMVar2[0x1d].pVptr + 0x30))(pMVar2 + 0x1d,0x58,0x58,0x58);
      (**(code **)((int)pMVar2[0x1d].pVptr + 0x2c))(pMVar2 + 0x1d,0x80);
      pMVar2[0x1d].nCol = 0x1e;
      pMVar2[0x1d].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 0x1d));
    }
    if ((iVar8 < 10) ||
       (-1 < (long)((ulong)*(byte *)((int)ourBtlSaveDat__10BtlSaveSec + 3) << 0x3d))) {
      pMVar2[0x1d].bFlags = pMVar2[0x1d].bFlags & 0xfe;
    }
    else {
      sVar7 = (short)((iVar8 / 10) % 10);
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 0x1d,sVar7 * 0xd,0x19,(sVar7 + 1) * 0xd,0x2f);
      pMVar2[0x1d].bFlags = pMVar2[0x1d].bFlags & 0xfe | 1;
    }
    if (bVar6) {
      Create__10MenuSpriteFUc(pMVar2 + 0x1e,1);
      pMVar2[0x1e].bPflags = pMVar2[0x1e].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 0x1e));
      pMVar2[0x1e].nPriority = 10;
      (**(code **)((int)pMVar2[0x1e].pVptr + 0x24))(0x43ed8000,0x431f0000);
      (**(code **)((int)pMVar2[0x1e].pVptr + 0x28))(0x41500000,0x41b00000);
      (**(code **)((int)pMVar2[0x1e].pVptr + 0x30))(pMVar2 + 0x1e,0x58,0x58,0x58);
      (**(code **)((int)pMVar2[0x1e].pVptr + 0x2c))(pMVar2 + 0x1e,0x80);
      pMVar2[0x1e].nCol = 0x1f;
      pMVar2[0x1e].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 0x1e));
    }
    if ((long)((ulong)*(byte *)((int)ourBtlSaveDat__10BtlSaveSec + 3) << 0x3d) < 0) {
      sVar7 = (short)(iVar8 % 10);
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 0x1e,sVar7 * 0xd,0x19,(sVar7 + 1) * 0xd,0x2f);
      pMVar2[0x1e].bFlags = pMVar2[0x1e].bFlags & 0xfe | 1;
    }
    else {
      pMVar2[0x1e].bFlags = pMVar2[0x1e].bFlags & 0xfe;
    }
    if (bVar6) {
      iStack_94 = *(int *)(ourBtlSocket__9BtlSocket + 0x62c);
      uStack_118 = *(u32 *)(iStack_94 + (uint)*(ushort *)(iStack_94 + 10) * 4 + 0xc);
      uStack_114 = uStack_118;
      uVar11 = GetTex0__6JRCTexFb(*(u32 *)(ourBtlSocket__9BtlSocket + 0x62c),0);
      Create__11SendOnLocalFP4_QWDUl
                (*(int *)(iStack_20 + iStack_10 * 0x114 + 0x164) + iStack_28 * 0x30,uStack_118,
                 uVar11);
      iStack_98 = *(int *)(iStack_20 + iStack_10 * 0x114 + 0x164) + iStack_28 * 0x30;
      *(u16 *)(iStack_98 + 0x14) = 0xb;
      AddPriority__12MenuObjTableFP7MenuObj
                ((MenuObjTable *)(iStack_20 + iStack_10 * 0x114 + 0xc4),
                 (MenuObj *)(*(int *)(iStack_20 + iStack_10 * 0x114 + 0x164) + iStack_28 * 0x30));
      CreatePacket__10MenuPacketFUs((MenuPacket *)(iStack_48 + iStack_30 * 0x28 + 0x18),4);
      SetRegister__12MenuRegisterFiUlUl(iStack_48 + iStack_30 * 0x28,0,0x42,0x44);
      *(u16 *)(iStack_48 + iStack_30 * 0x28 + 0x14) = 0xc;
      AddPriority__12MenuObjTableFP7MenuObj
                ((MenuObjTable *)(iStack_20 + iStack_10 * 0x114 + 0xc4),
                 (MenuObj *)(iStack_48 + iStack_30 * 0x28));
      Create__10MenuSpriteFUc(pMVar2 + 0x1f,1);
      pMVar2[0x1f].bPflags = pMVar2[0x1f].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 0x1f));
      pMVar2[0x1f].nPriority = 0xd;
      (**(code **)((int)pMVar2[0x1f].pVptr + 0x24))(0x43ae0000,0x43b88000);
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 0x1f,0,0,0x2c,0x19);
      (**(code **)((int)pMVar2[0x1f].pVptr + 0x28))(0x42300000,0x41c80000);
      (**(code **)((int)pMVar2[0x1f].pVptr + 0x30))(pMVar2 + 0x1f,0x80,0x80,0x80);
      (**(code **)((int)pMVar2[0x1f].pVptr + 0x2c))(pMVar2 + 0x1f,0x80);
      pMVar2[0x1f].bFlags = pMVar2[0x1f].bFlags & 0xfe | 1;
      pMVar2[0x1f].nCol = 0x20;
      pMVar2[0x1f].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 0x1f));
    }
    iStack_28 = iStack_28 + 1;
    iStack_30 = iStack_30 + 1;
    if (bVar6) {
      iStack_9c = *(int *)(ourBtlSocket__9BtlSocket + 0x630);
      uStack_120 = *(u32 *)(iStack_9c + (uint)*(ushort *)(iStack_9c + 10) * 4 + 0xc);
      uStack_11c = uStack_120;
      uVar11 = GetTex0__6JRCTexFb(*(u32 *)(ourBtlSocket__9BtlSocket + 0x630),0);
      Create__11SendOnLocalFP4_QWDUl
                (*(int *)(iStack_20 + iStack_10 * 0x114 + 0x164) + iStack_28 * 0x30,uStack_120,
                 uVar11);
      iStack_a0 = *(int *)(iStack_20 + iStack_10 * 0x114 + 0x164) + iStack_28 * 0x30;
      *(u16 *)(iStack_a0 + 0x14) = 0xe;
      AddPriority__12MenuObjTableFP7MenuObj
                ((MenuObjTable *)(iStack_20 + iStack_10 * 0x114 + 0xc4),
                 (MenuObj *)(*(int *)(iStack_20 + iStack_10 * 0x114 + 0x164) + iStack_28 * 0x30));
    }
    iStack_28 = iStack_28 + 1;
    iVar8 = *piStack_54;
    if (bVar6) {
      Create__10MenuSpriteFUc(pMVar2 + 0x20,1);
      pMVar2[0x20].bPflags = pMVar2[0x20].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 0x20));
      pMVar2[0x20].nPriority = 0xf;
      (**(code **)((int)pMVar2[0x20].pVptr + 0x24))(0x43c38000,0x43b90000);
      (**(code **)((int)pMVar2[0x20].pVptr + 0x28))(0x41900000,0x41a80000);
      (**(code **)((int)pMVar2[0x20].pVptr + 0x30))(pMVar2 + 0x20,0x80,0x80,0x80);
      (**(code **)((int)pMVar2[0x20].pVptr + 0x2c))(pMVar2 + 0x20,0x80);
      pMVar2[0x20].nCol = 0x21;
      pMVar2[0x20].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 0x20));
    }
    if (iVar8 < 10000000) {
      pMVar2[0x20].bFlags = pMVar2[0x20].bFlags & 0xfe;
    }
    else {
      sVar7 = (short)((iVar8 / 10000000) % 10);
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 0x20,sVar7 * 0x12,0,(sVar7 + 1) * 0x12,0x15);
      pMVar2[0x20].bFlags = pMVar2[0x20].bFlags & 0xfe | 1;
    }
    if (bVar6) {
      Create__10MenuSpriteFUc(pMVar2 + 0x21,1);
      pMVar2[0x21].bPflags = pMVar2[0x21].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 0x21));
      pMVar2[0x21].nPriority = 0xf;
      (**(code **)((int)pMVar2[0x21].pVptr + 0x24))(0x43c88000,0x43b90000);
      (**(code **)((int)pMVar2[0x21].pVptr + 0x28))(0x41900000,0x41a80000);
      (**(code **)((int)pMVar2[0x21].pVptr + 0x30))(pMVar2 + 0x21,0x80,0x80,0x80);
      (**(code **)((int)pMVar2[0x21].pVptr + 0x2c))(pMVar2 + 0x21,0x80);
      pMVar2[0x21].nCol = 0x22;
      pMVar2[0x21].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 0x21));
    }
    if (iVar8 < 1000000) {
      pMVar2[0x21].bFlags = pMVar2[0x21].bFlags & 0xfe;
    }
    else {
      sVar7 = (short)((iVar8 / 1000000) % 10);
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 0x21,sVar7 * 0x12,0,(sVar7 + 1) * 0x12,0x15);
      pMVar2[0x21].bFlags = pMVar2[0x21].bFlags & 0xfe | 1;
    }
    if (bVar6) {
      Create__10MenuSpriteFUc(pMVar2 + 0x22,1);
      pMVar2[0x22].bPflags = pMVar2[0x22].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 0x22));
      pMVar2[0x22].nPriority = 0xf;
      (**(code **)((int)pMVar2[0x22].pVptr + 0x24))(0x43cb0000,0x43b90000);
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 0x22,0xb4,0,0xc6,0x15);
      (**(code **)((int)pMVar2[0x22].pVptr + 0x28))(0x41900000,0x41a80000);
      (**(code **)((int)pMVar2[0x22].pVptr + 0x30))(pMVar2 + 0x22,0x80,0x80,0x80);
      (**(code **)((int)pMVar2[0x22].pVptr + 0x2c))(pMVar2 + 0x22,0x80);
      pMVar2[0x22].nCol = 0x23;
      pMVar2[0x22].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 0x22));
    }
    if (iVar8 < 1000000) {
      pMVar2[0x22].bFlags = pMVar2[0x22].bFlags & 0xfe;
    }
    else {
      pMVar2[0x22].bFlags = pMVar2[0x22].bFlags & 0xfe | 1;
    }
    if (bVar6) {
      Create__10MenuSpriteFUc(pMVar2 + 0x23,1);
      pMVar2[0x23].bPflags = pMVar2[0x23].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 0x23));
      pMVar2[0x23].nPriority = 0xf;
      (**(code **)((int)pMVar2[0x23].pVptr + 0x24))(0x43d00000,0x43b90000);
      (**(code **)((int)pMVar2[0x23].pVptr + 0x28))(0x41900000,0x41a80000);
      (**(code **)((int)pMVar2[0x23].pVptr + 0x30))(pMVar2 + 0x23,0x80,0x80,0x80);
      (**(code **)((int)pMVar2[0x23].pVptr + 0x2c))(pMVar2 + 0x23,0x80);
      pMVar2[0x23].nCol = 0x24;
      pMVar2[0x23].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 0x23));
    }
    if (iVar8 < 100000) {
      pMVar2[0x23].bFlags = pMVar2[0x23].bFlags & 0xfe;
    }
    else {
      sVar7 = (short)((iVar8 / 100000) % 10);
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 0x23,sVar7 * 0x12,0,(sVar7 + 1) * 0x12,0x15);
      pMVar2[0x23].bFlags = pMVar2[0x23].bFlags & 0xfe | 1;
    }
    if (bVar6) {
      Create__10MenuSpriteFUc(pMVar2 + 0x24,1);
      pMVar2[0x24].bPflags = pMVar2[0x24].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 0x24));
      pMVar2[0x24].nPriority = 0xf;
      (**(code **)((int)pMVar2[0x24].pVptr + 0x24))(0x43d50000,0x43b90000);
      (**(code **)((int)pMVar2[0x24].pVptr + 0x28))(0x41900000,0x41a80000);
      (**(code **)((int)pMVar2[0x24].pVptr + 0x30))(pMVar2 + 0x24,0x80,0x80,0x80);
      (**(code **)((int)pMVar2[0x24].pVptr + 0x2c))(pMVar2 + 0x24,0x80);
      pMVar2[0x24].nCol = 0x25;
      pMVar2[0x24].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 0x24));
    }
    if (iVar8 < 10000) {
      pMVar2[0x24].bFlags = pMVar2[0x24].bFlags & 0xfe;
    }
    else {
      sVar7 = (short)((iVar8 / 10000) % 10);
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 0x24,sVar7 * 0x12,0,(sVar7 + 1) * 0x12,0x15);
      pMVar2[0x24].bFlags = pMVar2[0x24].bFlags & 0xfe | 1;
    }
    if (bVar6) {
      Create__10MenuSpriteFUc(pMVar2 + 0x25,1);
      pMVar2[0x25].bPflags = pMVar2[0x25].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 0x25));
      pMVar2[0x25].nPriority = 0xf;
      (**(code **)((int)pMVar2[0x25].pVptr + 0x24))(0x43da0000,0x43b90000);
      uVar11 = (**(code **)((int)pMVar2[0x25].pVptr + 0x28))(0x41900000,0x41a80000);
      (**(code **)((int)pMVar2[0x25].pVptr + 0x30))(pMVar2 + 0x25,0x80,0x80,0x80,uVar11);
      (**(code **)((int)pMVar2[0x25].pVptr + 0x2c))(pMVar2 + 0x25,0x80);
      pMVar2[0x25].nCol = 0x26;
      pMVar2[0x25].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 0x25));
    }
    if (iVar8 < 1000) {
      pMVar2[0x25].bFlags = pMVar2[0x25].bFlags & 0xfe;
    }
    else {
      sVar7 = (short)((iVar8 / 1000) % 10);
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 0x25,sVar7 * 0x12,0,(sVar7 + 1) * 0x12,0x15);
      pMVar2[0x25].bFlags = pMVar2[0x25].bFlags & 0xfe | 1;
    }
    if (bVar6) {
      Create__10MenuSpriteFUc(pMVar2 + 0x26,1);
      pMVar2[0x26].bPflags = pMVar2[0x26].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 0x26));
      pMVar2[0x26].nPriority = 0xf;
      (**(code **)((int)pMVar2[0x26].pVptr + 0x24))(0x43dc8000,0x43b90000);
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 0x26,0xb4,0,0xc6,0x15);
      uVar11 = (**(code **)((int)pMVar2[0x26].pVptr + 0x28))(0x41900000,0x41a80000);
      (**(code **)((int)pMVar2[0x26].pVptr + 0x30))(pMVar2 + 0x26,0x80,0x80,0x80,uVar11);
      (**(code **)((int)pMVar2[0x26].pVptr + 0x2c))(pMVar2 + 0x26,0x80);
      pMVar2[0x26].nCol = 0x27;
      pMVar2[0x26].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 0x26));
    }
    if (iVar8 < 1000) {
      pMVar2[0x26].bFlags = pMVar2[0x26].bFlags & 0xfe;
    }
    else {
      pMVar2[0x26].bFlags = pMVar2[0x26].bFlags & 0xfe | 1;
    }
    if (bVar6) {
      Create__10MenuSpriteFUc(pMVar2 + 0x27,1);
      pMVar2[0x27].bPflags = pMVar2[0x27].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 0x27));
      pMVar2[0x27].nPriority = 0xf;
      (**(code **)((int)pMVar2[0x27].pVptr + 0x24))(0x43e18000,0x43b90000);
      (**(code **)((int)pMVar2[0x27].pVptr + 0x28))(0x41900000,0x41a80000);
      (**(code **)((int)pMVar2[0x27].pVptr + 0x30))(pMVar2 + 0x27,0x80,0x80,0x80);
      (**(code **)((int)pMVar2[0x27].pVptr + 0x2c))(pMVar2 + 0x27,0x80);
      pMVar2[0x27].nCol = 0x28;
      pMVar2[0x27].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 0x27));
    }
    if (iVar8 < 100) {
      pMVar2[0x27].bFlags = pMVar2[0x27].bFlags & 0xfe;
    }
    else {
      sVar7 = (short)((iVar8 / 100) % 10);
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 0x27,sVar7 * 0x12,0,(sVar7 + 1) * 0x12,0x15);
      pMVar2[0x27].bFlags = pMVar2[0x27].bFlags & 0xfe | 1;
    }
    if (bVar6) {
      Create__10MenuSpriteFUc(pMVar2 + 0x28,1);
      pMVar2[0x28].bPflags = pMVar2[0x28].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 0x28));
      pMVar2[0x28].nPriority = 0xf;
      (**(code **)((int)pMVar2[0x28].pVptr + 0x24))(0x43e68000,0x43b90000);
      (**(code **)((int)pMVar2[0x28].pVptr + 0x28))(0x41900000,0x41a80000);
      (**(code **)((int)pMVar2[0x28].pVptr + 0x30))(pMVar2 + 0x28,0x80,0x80,0x80);
      (**(code **)((int)pMVar2[0x28].pVptr + 0x2c))(pMVar2 + 0x28,0x80);
      pMVar2[0x28].nCol = 0x29;
      pMVar2[0x28].nRow = 0;
      pMVar2[0x28].bFlags = pMVar2[0x28].bFlags & 0xfe | 1;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 0x28));
    }
    if (iVar8 < 10) {
      pMVar2[0x28].bFlags = pMVar2[0x28].bFlags & 0xfe;
    }
    else {
      sVar7 = (short)((iVar8 / 10) % 10);
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 0x28,sVar7 * 0x12,0,(sVar7 + 1) * 0x12,0x15);
      pMVar2[0x28].bFlags = pMVar2[0x28].bFlags & 0xfe | 1;
    }
    if (bVar6) {
      Create__10MenuSpriteFUc(pMVar2 + 0x29,1);
      pMVar2[0x29].bPflags = pMVar2[0x29].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 0x29));
      pMVar2[0x29].nPriority = 0xf;
      (**(code **)((int)pMVar2[0x29].pVptr + 0x24))(0x43eb8000,0x43b90000);
      uVar11 = (**(code **)((int)pMVar2[0x29].pVptr + 0x28))(0x41900000,0x41a80000);
      (**(code **)((int)pMVar2[0x29].pVptr + 0x30))(pMVar2 + 0x29,0x80,0x80,0x80,0xf60,uVar11);
      (**(code **)((int)pMVar2[0x29].pVptr + 0x2c))(pMVar2 + 0x29,0x80);
      pMVar2[0x29].nCol = 0x2a;
      pMVar2[0x29].nRow = 0;
      pMVar2[0x29].bFlags = pMVar2[0x29].bFlags & 0xfe | 1;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 0x29));
    }
    sVar7 = (short)(iVar8 % 10);
    SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 0x29,sVar7 * 0x12,0,(sVar7 + 1) * 0x12,0x15);
    if (bVar6) {
      Open__10MenuWindowFUci((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),0,0x14d);
    }
    break;
  case 2:
  case 3:
  case 4:
  case 5:
  case 6:
  case 7:
  case 8:
  case 9:
    if (*(short *)(iStack_20 + iStack_10 * 0x114 + 0x62) == 0) {
      *(u16 *)(iStack_20 + iStack_10 * 0x114 + 0x62) = 1;
      *(u16 *)(iStack_20 + iStack_10 * 0x114 + 100) = 0;
      *(u32 *)(iStack_20 + iStack_10 * 0x114 + 0x68) = 0;
      *(u16 *)(iStack_20 + iStack_10 * 0x114 + 0xc0) = 10;
      AddOT__7MenuObjFv((MenuObj *)(iStack_20 + iStack_10 * 0x114 + 0xac));
      iVar8 = iStack_20 + iStack_10 * 0x114;
      *(byte *)(iVar8 + 0x60) = *(byte *)(iVar8 + 0x60) & 0xfb | 4;
      Create__10MenuWindowFUcUcffff
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),0,1,0.0,
                 (float)((iStack_10 + -2) * 0x2c + 0x2a),360.0,45.0);
      iVar8 = iStack_20 + iStack_10 * 0x114;
      *(byte *)(iVar8 + 0x60) = *(byte *)(iVar8 + 0x60) & 0xf7 | 8;
      if (((ulong)*(ushort *)(iStack_20 + iStack_10 * 0x114 + 0x60) & 0xfff) >> 4 == 0) {
        uVar11 = __nwa__FUi(0x90);
        uVar9 = __construct_new_array(uVar11,0x27bfd0,0x27c030,0x80,1);
        *(u32 *)(iStack_20 + iStack_10 * 0x114 + 0x160) = uVar9;
        iVar8 = iStack_20 + iStack_10 * 0x114;
        *(ushort *)(iVar8 + 0x60) = *(ushort *)(iVar8 + 0x60) & 0xf00f | 0x10;
      }
      if (*(int *)(iStack_20 + iStack_10 * 0x114 + 0x164) == 0) {
        uVar11 = __nwa__FUi(0x130);
        uVar9 = __construct_new_array(uVar11,0x277820,0x277890,0x30,6);
        *(u32 *)(iStack_20 + iStack_10 * 0x114 + 0x164) = uVar9;
      }
      if (*(int *)(iStack_20 + iStack_10 * 0x114 + 0x168) == 0) {
        uVar11 = __nwa__FUi(0xdf0);
        uVar9 = __construct_new_array(uVar11,0x266140,0x2661a0,0x60,0x25);
        *(u32 *)(iStack_20 + iStack_10 * 0x114 + 0x168) = uVar9;
      }
      if (*(int *)(iStack_20 + iStack_10 * 0x114 + 0x16c) == 0) {
        uVar11 = __nwa__FUi(0x430);
        uVar9 = __construct_new_array(uVar11,0x276640,0x2766d0,0x84,8);
        *(u32 *)(iStack_20 + iStack_10 * 0x114 + 0x16c) = uVar9;
      }
      if (*(int *)(iStack_20 + iStack_10 * 0x114 + 0x170) == 0) {
        uVar11 = __nwa__FUi(0x88);
        uVar9 = __construct_new_array(uVar11,0x28d000,0x28d070,0x28,3);
        *(u32 *)(iStack_20 + iStack_10 * 0x114 + 0x170) = uVar9;
      }
      bVar6 = true;
    }
    else {
      bVar6 = false;
    }
    pMStack_44 = *(MenuText **)(iStack_20 + iStack_10 * 0x114 + 0x160);
    pMVar2 = *(MenuSprite **)(iStack_20 + iStack_10 * 0x114 + 0x168);
    pMVar3 = *(MenuPolygon **)(iStack_20 + iStack_10 * 0x114 + 0x16c);
    iStack_48 = *(int *)(iStack_20 + iStack_10 * 0x114 + 0x170);
    iStack_24 = 0;
    iStack_28 = 0;
    iStack_30 = 0;
    pBStack_2c = (BtlSaveSec *)(int)*(char *)(iStack_50 + iStack_10 + 0x10);
    if (bVar6) {
      CreatePacket__10MenuPacketFUs((MenuPacket *)(iStack_48 + 0x18),4);
      SetRegister__12MenuRegisterFiUlUl(iStack_48 + iStack_30 * 0x28,0,0x42,0x44);
      *(u16 *)(iStack_48 + iStack_30 * 0x28 + 0x14) = 0;
      AddPriority__12MenuObjTableFP7MenuObj
                ((MenuObjTable *)(iStack_20 + iStack_10 * 0x114 + 0xc4),
                 (MenuObj *)(iStack_48 + iStack_30 * 0x28));
      Create__11MenuPolygonFUcUc(pMVar3,0,1);
      pMVar3->nPriority = 1;
      SetVertex__11MenuPolygonFiffb(pMVar3,0,0.0,2.0,true);
      SetColor__11MenuPolygonFiUcUcUc(pMVar3,0,0x28,0x28,0x28);
      pMVar3->bA = 0x80;
      UpdateRgba__7MenuObjFv((MenuObj *)pMVar3);
      SetVertex__11MenuPolygonFiffb(pMVar3,1,0.0,37.0,true);
      SetColor__11MenuPolygonFiUcUcUc(pMVar3,1,0x28,0x28,0x28);
      pMVar3->field_0x77 = 0x80;
      UpdateRgba__7MenuObjFv((MenuObj *)pMVar3);
      SetVertex__11MenuPolygonFiffb(pMVar3,2,70.0,2.0,true);
      SetColor__11MenuPolygonFiUcUcUc(pMVar3,2,0x32,0x32,0x32);
      pMVar3->field_0x7b = 0x80;
      UpdateRgba__7MenuObjFv((MenuObj *)pMVar3);
      SetVertex__11MenuPolygonFiffb(pMVar3,3,70.0,37.0,true);
      SetColor__11MenuPolygonFiUcUcUc(pMVar3,3,0x32,0x32,0x32);
      pMVar3->field_0x7f = 0x80;
      UpdateRgba__7MenuObjFv((MenuObj *)pMVar3);
      pMVar3->bFlags = pMVar3->bFlags & 0xfe | 1;
      pMVar3->nCol = 0;
      pMVar3->nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)pMVar3);
      Create__11MenuPolygonFUcUc(pMVar3 + 1,0,1);
      pMVar3[1].nPriority = 1;
      SetVertex__11MenuPolygonFiffb(pMVar3 + 1,0,70.0,2.0,true);
      SetColor__11MenuPolygonFiUcUcUc(pMVar3 + 1,0,0x32,0x32,0x32);
      pMVar3[1].bA = 0x80;
      UpdateRgba__7MenuObjFv((MenuObj *)(pMVar3 + 1));
      SetVertex__11MenuPolygonFiffb(pMVar3 + 1,1,70.0,37.0,true);
      SetColor__11MenuPolygonFiUcUcUc(pMVar3 + 1,1,0x32,0x32,0x32);
      pMVar3[1].field_0x77 = 0x80;
      UpdateRgba__7MenuObjFv((MenuObj *)(pMVar3 + 1));
      SetVertex__11MenuPolygonFiffb(pMVar3 + 1,2,185.0,2.0,true);
      SetColor__11MenuPolygonFiUcUcUc(pMVar3 + 1,2,0x3c,0x3c,0x3c);
      pMVar3[1].field_0x7b = 0x80;
      UpdateRgba__7MenuObjFv((MenuObj *)(pMVar3 + 1));
      SetVertex__11MenuPolygonFiffb(pMVar3 + 1,3,70.0,37.0,true);
      SetColor__11MenuPolygonFiUcUcUc(pMVar3 + 1,3,0x32,0x32,0x32);
      pMVar3[1].field_0x7f = 0x80;
      UpdateRgba__7MenuObjFv((MenuObj *)(pMVar3 + 1));
      pMVar3[1].bFlags = pMVar3[1].bFlags & 0xfe | 1;
      pMVar3[1].nCol = 1;
      pMVar3[1].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar3 + 1));
      Create__11MenuPolygonFUcUc(pMVar3 + 2,0,1);
      pMVar3[2].nPriority = 1;
      SetVertex__11MenuPolygonFiffb(pMVar3 + 2,0,70.0,37.0,true);
      SetColor__11MenuPolygonFiUcUcUc(pMVar3 + 2,0,0x3c,0x3c,0x3c);
      pMVar3[2].bA = 0x80;
      UpdateRgba__7MenuObjFv((MenuObj *)(pMVar3 + 2));
      SetVertex__11MenuPolygonFiffb(pMVar3 + 2,1,185.0,2.0,true);
      SetColor__11MenuPolygonFiUcUcUc(pMVar3 + 2,1,0x46,0x46,0x46);
      pMVar3[2].field_0x77 = 0x80;
      UpdateRgba__7MenuObjFv((MenuObj *)(pMVar3 + 2));
      SetVertex__11MenuPolygonFiffb(pMVar3 + 2,2,185.0,37.0,true);
      SetColor__11MenuPolygonFiUcUcUc(pMVar3 + 2,2,0x46,0x46,0x46);
      pMVar3[2].field_0x7b = 0x80;
      UpdateRgba__7MenuObjFv((MenuObj *)(pMVar3 + 2));
      SetVertex__11MenuPolygonFiffb(pMVar3 + 2,3,185.0,37.0,true);
      SetColor__11MenuPolygonFiUcUcUc(pMVar3 + 2,3,0x46,0x46,0x46);
      pMVar3[2].field_0x7f = 0x80;
      UpdateRgba__7MenuObjFv((MenuObj *)(pMVar3 + 2));
      pMVar3[2].bFlags = pMVar3[2].bFlags & 0xfe | 1;
      pMVar3[2].nCol = 2;
      pMVar3[2].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar3 + 2));
      Create__11MenuPolygonFUcUc(pMVar3 + 3,0,1);
      pMVar3[3].nPriority = 1;
      SetVertex__11MenuPolygonFiffb(pMVar3 + 3,0,185.0,2.0,true);
      SetColor__11MenuPolygonFiUcUcUc(pMVar3 + 3,0,0x46,0x46,0x46);
      pMVar3[3].bA = 0x80;
      UpdateRgba__7MenuObjFv((MenuObj *)(pMVar3 + 3));
      SetVertex__11MenuPolygonFiffb(pMVar3 + 3,1,185.0,37.0,true);
      SetColor__11MenuPolygonFiUcUcUc(pMVar3 + 3,1,0x46,0x46,0x46);
      pMVar3[3].field_0x77 = 0x80;
      UpdateRgba__7MenuObjFv((MenuObj *)(pMVar3 + 3));
      SetVertex__11MenuPolygonFiffb(pMVar3 + 3,2,202.0,2.0,true);
      SetColor__11MenuPolygonFiUcUcUc(pMVar3 + 3,2,0x4b,0x4b,0x4b);
      pMVar3[3].field_0x7b = 0x80;
      UpdateRgba__7MenuObjFv((MenuObj *)(pMVar3 + 3));
      SetVertex__11MenuPolygonFiffb(pMVar3 + 3,3,202.0,37.0,true);
      SetColor__11MenuPolygonFiUcUcUc(pMVar3 + 3,3,0x4b,0x4b,0x4b);
      pMVar3[3].field_0x7f = 0x80;
      UpdateRgba__7MenuObjFv((MenuObj *)(pMVar3 + 3));
      pMVar3[3].bFlags = pMVar3[3].bFlags & 0xfe | 1;
      pMVar3[3].nCol = 3;
      pMVar3[3].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar3 + 3));
      Create__11MenuPolygonFUcUc(pMVar3 + 4,0,1);
      pMVar3[4].nPriority = 1;
      SetVertex__11MenuPolygonFiffb(pMVar3 + 4,0,202.0,2.0,true);
      SetColor__11MenuPolygonFiUcUcUc(pMVar3 + 4,0,0x4b,0x4b,0x4b);
      pMVar3[4].bA = 0x80;
      UpdateRgba__7MenuObjFv((MenuObj *)(pMVar3 + 4));
      SetVertex__11MenuPolygonFiffb(pMVar3 + 4,1,202.0,37.0,true);
      SetColor__11MenuPolygonFiUcUcUc(pMVar3 + 4,1,0x4b,0x4b,0x4b);
      pMVar3[4].field_0x77 = 0x80;
      UpdateRgba__7MenuObjFv((MenuObj *)(pMVar3 + 4));
      SetVertex__11MenuPolygonFiffb(pMVar3 + 4,2,317.0,37.0,true);
      SetColor__11MenuPolygonFiUcUcUc(pMVar3 + 4,2,0x5a,0x5a,0x5a);
      pMVar3[4].field_0x7b = 0x80;
      UpdateRgba__7MenuObjFv((MenuObj *)(pMVar3 + 4));
      SetVertex__11MenuPolygonFiffb(pMVar3 + 4,3,317.0,37.0,true);
      SetColor__11MenuPolygonFiUcUcUc(pMVar3 + 4,3,0x5a,0x5a,0x5a);
      pMVar3[4].field_0x7f = 0x80;
      UpdateRgba__7MenuObjFv((MenuObj *)(pMVar3 + 4));
      pMVar3[4].bFlags = pMVar3[4].bFlags & 0xfe | 1;
      pMVar3[4].nCol = 4;
      pMVar3[4].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar3 + 4));
      CreatePacket__10MenuPacketFUs((MenuPacket *)(iStack_48 + (iStack_30 + 1) * 0x28 + 0x18),4);
      SetRegister__12MenuRegisterFiUlUl(iStack_48 + (iStack_30 + 1) * 0x28,0,0x42,0x48);
      *(u16 *)(iStack_48 + (iStack_30 + 1) * 0x28 + 0x14) = 2;
      AddPriority__12MenuObjTableFP7MenuObj
                ((MenuObjTable *)(iStack_20 + iStack_10 * 0x114 + 0xc4),
                 (MenuObj *)(iStack_48 + (iStack_30 + 1) * 0x28));
      Create__11MenuPolygonFUcUc(pMVar3 + 5,0,1);
      pMVar3[5].nPriority = 3;
      SetVertex__11MenuPolygonFiffb(pMVar3 + 5,0,262.0,9.0,true);
      SetColor__11MenuPolygonFiUcUcUc(pMVar3 + 5,0,0x10,4,0x80);
      pMVar3[5].bA = 0;
      UpdateRgba__7MenuObjFv((MenuObj *)(pMVar3 + 5));
      SetVertex__11MenuPolygonFiffb(pMVar3 + 5,1,262.0,19.0,true);
      SetColor__11MenuPolygonFiUcUcUc(pMVar3 + 5,1,0x10,4,0x80);
      pMVar3[5].field_0x77 = 0;
      UpdateRgba__7MenuObjFv((MenuObj *)(pMVar3 + 5));
      SetVertex__11MenuPolygonFiffb(pMVar3 + 5,2,278.0,9.0,true);
      SetColor__11MenuPolygonFiUcUcUc(pMVar3 + 5,2,0xc0,0xe0,0xff);
      pMVar3[5].field_0x7b = 0x20;
      UpdateRgba__7MenuObjFv((MenuObj *)(pMVar3 + 5));
      SetVertex__11MenuPolygonFiffb(pMVar3 + 5,3,278.0,19.0,true);
      SetColor__11MenuPolygonFiUcUcUc(pMVar3 + 5,3,0xc0,0xe0,0xff);
      pMVar3[5].field_0x7f = 0x20;
      UpdateRgba__7MenuObjFv((MenuObj *)(pMVar3 + 5));
      pMVar3[5].bFlags = pMVar3[5].bFlags & 0xfe | 1;
      pMVar3[5].nCol = 5;
      pMVar3[5].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar3 + 5));
      Create__11MenuPolygonFUcUc(pMVar3 + 6,0,1);
      pMVar3[6].nPriority = 3;
      SetVertex__11MenuPolygonFiffb(pMVar3 + 6,0,278.0,9.0,true);
      SetColor__11MenuPolygonFiUcUcUc(pMVar3 + 6,0,0xc0,0xe0,0xff);
      pMVar3[6].bA = 0x20;
      UpdateRgba__7MenuObjFv((MenuObj *)(pMVar3 + 6));
      SetVertex__11MenuPolygonFiffb(pMVar3 + 6,1,278.0,19.0,true);
      SetColor__11MenuPolygonFiUcUcUc(pMVar3 + 6,1,0xc0,0xe0,0xff);
      pMVar3[6].field_0x77 = 0x20;
      UpdateRgba__7MenuObjFv((MenuObj *)(pMVar3 + 6));
      SetVertex__11MenuPolygonFiffb(pMVar3 + 6,2,308.0,9.0,true);
      SetColor__11MenuPolygonFiUcUcUc(pMVar3 + 6,2,0xc0,0xe0,0xff);
      pMVar3[6].field_0x7b = 0x20;
      UpdateRgba__7MenuObjFv((MenuObj *)(pMVar3 + 6));
      SetVertex__11MenuPolygonFiffb(pMVar3 + 6,3,308.0,19.0,true);
      SetColor__11MenuPolygonFiUcUcUc(pMVar3 + 6,3,0xc0,0xe0,0xff);
      pMVar3[6].field_0x7f = 0x20;
      UpdateRgba__7MenuObjFv((MenuObj *)(pMVar3 + 6));
      pMVar3[6].bFlags = pMVar3[6].bFlags & 0xfe | 1;
      pMVar3[6].nCol = 6;
      pMVar3[6].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar3 + 6));
      Create__11MenuPolygonFUcUc(pMVar3 + 7,0,1);
      pMVar3[7].nPriority = 3;
      SetVertex__11MenuPolygonFiffb(pMVar3 + 7,0,308.0,9.0,true);
      SetColor__11MenuPolygonFiUcUcUc(pMVar3 + 7,0,0xc0,0xe0,0xff);
      pMVar3[7].bA = 0x20;
      UpdateRgba__7MenuObjFv((MenuObj *)(pMVar3 + 7));
      SetVertex__11MenuPolygonFiffb(pMVar3 + 7,1,308.0,19.0,true);
      SetColor__11MenuPolygonFiUcUcUc(pMVar3 + 7,1,0xc0,0xe0,0xff);
      pMVar3[7].field_0x77 = 0x20;
      UpdateRgba__7MenuObjFv((MenuObj *)(pMVar3 + 7));
      SetVertex__11MenuPolygonFiffb(pMVar3 + 7,2,348.0,9.0,true);
      SetColor__11MenuPolygonFiUcUcUc(pMVar3 + 7,2,0x10,4,0x80);
      pMVar3[7].field_0x7b = 0;
      UpdateRgba__7MenuObjFv((MenuObj *)(pMVar3 + 7));
      SetVertex__11MenuPolygonFiffb(pMVar3 + 7,3,348.0,19.0,true);
      SetColor__11MenuPolygonFiUcUcUc(pMVar3 + 7,3,0x10,4,0x80);
      pMVar3[7].field_0x7f = 0;
      UpdateRgba__7MenuObjFv((MenuObj *)(pMVar3 + 7));
      pMVar3[7].bFlags = pMVar3[7].bFlags & 0xfe | 1;
      pMVar3[7].nCol = 7;
      pMVar3[7].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar3 + 7));
    }
    iStack_30 = iStack_30 + 2;
    if (bVar6) {
      CreatePacket__10MenuPacketFUs((MenuPacket *)(iStack_48 + iStack_30 * 0x28 + 0x18),4);
      SetRegister__12MenuRegisterFiUlUl(iStack_48 + iStack_30 * 0x28,0,0x42,0x44);
      *(u16 *)(iStack_48 + iStack_30 * 0x28 + 0x14) = 4;
      AddPriority__12MenuObjTableFP7MenuObj
                ((MenuObjTable *)(iStack_20 + iStack_10 * 0x114 + 0xc4),
                 (MenuObj *)(iStack_48 + iStack_30 * 0x28));
      iStack_a4 = *(int *)(ourBtlSocket__9BtlSocket +
                           *(char *)((int)&uStack_170 +
                                    (uint)*(ushort *)
                                           ((int)ourBtlSaveDat__10BtlSaveSec +
                                           (int)pBStack_2c * 0xc0 + 0x4c)) * 4 + 0x604);
      uStack_124 = *(u32 *)(iStack_a4 + (uint)*(ushort *)(iStack_a4 + 10) * 4 + 0xc);
      uStack_128 = uStack_124;
      uVar11 = GetTex0__6JRCTexFb(*(u32 *)
                                   (ourBtlSocket__9BtlSocket +
                                    *(char *)((int)&uStack_170 +
                                             (uint)*(ushort *)
                                                    ((int)ourBtlSaveDat__10BtlSaveSec +
                                                    (int)pBStack_2c * 0xc0 + 0x4c)) * 4 + 0x604),0);
      Create__11SendOnLocalFP4_QWDUl
                (*(int *)(iStack_20 + iStack_10 * 0x114 + 0x164) + iStack_28 * 0x30,uStack_128,
                 uVar11);
      iStack_a8 = *(int *)(iStack_20 + iStack_10 * 0x114 + 0x164) + iStack_28 * 0x30;
      *(u16 *)(iStack_a8 + 0x14) = 5;
      AddPriority__12MenuObjTableFP7MenuObj
                ((MenuObjTable *)(iStack_20 + iStack_10 * 0x114 + 0xc4),
                 (MenuObj *)(*(int *)(iStack_20 + iStack_10 * 0x114 + 0x164) + iStack_28 * 0x30));
      Create__10MenuSpriteFUc(pMVar2,1);
      pMVar2->bPflags = pMVar2->bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)pMVar2);
      pMVar2->nPriority = 6;
      (**(code **)((int)pMVar2->pVptr + 0x24))(0x40c00000,0x40000000);
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2,0,0,0x50,0x24);
      (**(code **)((int)pMVar2->pVptr + 0x28))(0x42a00000,0x42100000);
      (**(code **)((int)pMVar2->pVptr + 0x30))(pMVar2,0x80,0x80,0x80);
      (**(code **)((int)pMVar2->pVptr + 0x2c))(pMVar2,0x80);
      pMVar2->bFlags = pMVar2->bFlags & 0xfe | 1;
      pMVar2->nCol = 8;
      pMVar2->nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)pMVar2);
    }
    iStack_30 = iStack_30 + 1;
    iStack_28 = iStack_28 + 1;
    if (bVar6) {
      iStack_ac = *(int *)(ourBtlSocket__9BtlSocket + 0x670);
      uStack_130 = *(u32 *)(iStack_ac + (uint)*(ushort *)(iStack_ac + 10) * 4 + 0xc);
      uStack_12c = uStack_130;
      uVar11 = GetTex0__6JRCTexFb(*(u32 *)(ourBtlSocket__9BtlSocket + 0x670),0);
      Create__11SendOnLocalFP4_QWDUl
                (*(int *)(iStack_20 + iStack_10 * 0x114 + 0x164) + iStack_28 * 0x30,uStack_130,
                 uVar11);
      iStack_b0 = *(int *)(iStack_20 + iStack_10 * 0x114 + 0x164) + iStack_28 * 0x30;
      *(u16 *)(iStack_b0 + 0x14) = 7;
      AddPriority__12MenuObjTableFP7MenuObj
                ((MenuObjTable *)(iStack_20 + iStack_10 * 0x114 + 0xc4),
                 (MenuObj *)(*(int *)(iStack_20 + iStack_10 * 0x114 + 0x164) + iStack_28 * 0x30));
      Create__10MenuSpriteFUc(pMVar2 + 1,1);
      pMVar2[1].bPflags = pMVar2[1].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 1));
      pMVar2[1].nPriority = 8;
      (**(code **)((int)pMVar2[1].pVptr + 0x24))(0xbf800000,0x40e00000);
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 1,0,0,0x22,0x22);
      (**(code **)((int)pMVar2[1].pVptr + 0x28))(0x42080000,0x42080000);
      (**(code **)((int)pMVar2[1].pVptr + 0x30))(pMVar2 + 1,0x80,0x80,0x80);
      (**(code **)((int)pMVar2[1].pVptr + 0x2c))(pMVar2 + 1,0x80);
      pMVar2[1].nCol = 9;
      pMVar2[1].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 1));
    }
    if ((long)(iStack_10 + -2) < (long)*(char *)(iStack_50 + 0x11)) {
      pMVar2[1].bFlags = pMVar2[1].bFlags & 0xfe | 1;
    }
    else {
      pMVar2[1].bFlags = pMVar2[1].bFlags & 0xfe;
    }
    iStack_28 = iStack_28 + 1;
    if (bVar6) {
      iStack_b4 = *(int *)(ourBtlSocket__9BtlSocket + 0x624);
      uStack_138 = *(u32 *)(iStack_b4 + (uint)*(ushort *)(iStack_b4 + 10) * 4 + 0xc);
      uStack_134 = uStack_138;
      uVar11 = GetTex0__6JRCTexFb(*(u32 *)(ourBtlSocket__9BtlSocket + 0x624),0);
      Create__11SendOnLocalFP4_QWDUl
                (*(int *)(iStack_20 + iStack_10 * 0x114 + 0x164) + iStack_28 * 0x30,uStack_138,
                 uVar11);
      iStack_b8 = *(int *)(iStack_20 + iStack_10 * 0x114 + 0x164) + iStack_28 * 0x30;
      *(u16 *)(iStack_b8 + 0x14) = 9;
      AddPriority__12MenuObjTableFP7MenuObj
                ((MenuObjTable *)(iStack_20 + iStack_10 * 0x114 + 0xc4),
                 (MenuObj *)(*(int *)(iStack_20 + iStack_10 * 0x114 + 0x164) + iStack_28 * 0x30));
      Create__10MenuSpriteFUc(pMVar2 + 2,1);
      pMVar2[2].bPflags = pMVar2[2].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 2));
      pMVar2[2].nPriority = 10;
      (**(code **)((int)pMVar2[2].pVptr + 0x24))(0x42c60000,0x41700000);
      (**(code **)((int)pMVar2[2].pVptr + 0x28))(0x41400000,0x41b00000);
      (**(code **)((int)pMVar2[2].pVptr + 0x30))(pMVar2 + 2,0x58,0x58,0x58);
      (**(code **)((int)pMVar2[2].pVptr + 0x2c))(pMVar2 + 2,0x80);
      pMVar2[2].nCol = 10;
      pMVar2[2].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 2));
      Create__10MenuSpriteFUc(pMVar2 + 3,1);
      pMVar2[3].bPflags = pMVar2[3].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 3));
      pMVar2[3].nPriority = 10;
      (**(code **)((int)pMVar2[3].pVptr + 0x24))(0x42da0000,0x41700000);
      (**(code **)((int)pMVar2[3].pVptr + 0x28))(0x41400000,0x41b00000);
      (**(code **)((int)pMVar2[3].pVptr + 0x30))(pMVar2 + 3,0x58,0x58,0x58);
      (**(code **)((int)pMVar2[3].pVptr + 0x2c))(pMVar2 + 3,0x80);
      pMVar2[3].nCol = 0xb;
      pMVar2[3].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 3));
    }
    uVar5 = *(byte *)((int)ourBtlSaveDat__10BtlSaveSec + (int)pBStack_2c * 0xc0 + 0x47) / 10;
    sVar7 = (short)uVar5;
    SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 2,sVar7 * 0xc,0,(sVar7 + 1) * 0xc,0x16);
    if (uVar5 == 0) {
      pMVar2[2].bFlags = pMVar2[2].bFlags & 0xfe;
    }
    else {
      pMVar2[2].bFlags = pMVar2[2].bFlags & 0xfe | 1;
    }
    uVar4 = (ushort)*(byte *)((int)ourBtlSaveDat__10BtlSaveSec + (int)pBStack_2c * 0xc0 + 0x47) % 10
    ;
    SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 3,uVar4 * 0xc,0,(uVar4 + 1) * 0xc,0x16);
    pMVar2[3].bFlags = pMVar2[3].bFlags & 0xfe | 1;
    iStack_28 = iStack_28 + 1;
    if (bVar6) {
      iStack_bc = *(int *)(ourBtlSocket__9BtlSocket + 0x628);
      uStack_140 = *(u32 *)(iStack_bc + (uint)*(ushort *)(iStack_bc + 10) * 4 + 0xc);
      uStack_13c = uStack_140;
      uVar11 = GetTex0__6JRCTexFb(*(u32 *)(ourBtlSocket__9BtlSocket + 0x628),0);
      Create__11SendOnLocalFP4_QWDUl
                (*(int *)(iStack_20 + iStack_10 * 0x114 + 0x164) + iStack_28 * 0x30,uStack_140,
                 uVar11);
      iStack_c0 = *(int *)(iStack_20 + iStack_10 * 0x114 + 0x164) + iStack_28 * 0x30;
      *(u16 *)(iStack_c0 + 0x14) = 0xb;
      AddPriority__12MenuObjTableFP7MenuObj
                ((MenuObjTable *)(iStack_20 + iStack_10 * 0x114 + 0xc4),
                 (MenuObj *)(*(int *)(iStack_20 + iStack_10 * 0x114 + 0x164) + iStack_28 * 0x30));
      Create__10MenuSpriteFUc(pMVar2 + 4,1);
      pMVar2[4].bPflags = pMVar2[4].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 4));
      pMVar2[4].nPriority = 0xc;
      (**(code **)((int)pMVar2[4].pVptr + 0x24))(0x430c0000,0x42000000);
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 4,1,8,0x3d,0x10);
      (**(code **)((int)pMVar2[4].pVptr + 0x28))(0x42700000,0x41000000);
      (**(code **)((int)pMVar2[4].pVptr + 0x30))(pMVar2 + 4,0x80,0x80,0x80);
      (**(code **)((int)pMVar2[4].pVptr + 0x2c))(pMVar2 + 4,0x80);
      pMVar2[4].bFlags = pMVar2[4].bFlags & 0xfe | 1;
      pMVar2[4].nCol = 0xc;
      pMVar2[4].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 4));
      Create__10MenuSpriteFUc(pMVar2 + 5,1);
      pMVar2[5].bPflags = pMVar2[5].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 5));
      pMVar2[5].nPriority = 0xc;
      (**(code **)((int)pMVar2[5].pVptr + 0x24))(0x435b0000,0x42000000);
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 5,0x3e,8,0x7a,0x10);
      (**(code **)((int)pMVar2[5].pVptr + 0x28))(0x42700000,0x41000000);
      uVar11 = (**(code **)((int)pMVar2[5].pVptr + 0x30))(pMVar2 + 5,0x80,0x80,0x80);
      (**(code **)((int)pMVar2[5].pVptr + 0x2c))(pMVar2 + 5,0x80,uVar11);
      pMVar2[5].bFlags = pMVar2[5].bFlags & 0xfe | 1;
      pMVar2[5].nCol = 0xd;
      pMVar2[5].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 5));
      Create__10MenuSpriteFUc(pMVar2 + 6,1);
      pMVar2[6].bPflags = pMVar2[6].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 6));
      pMVar2[6].nPriority = 0xc;
      (**(code **)((int)pMVar2[6].pVptr + 0x24))(0x43950000,0x42000000);
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 6,0x7b,8,0x92,0x10);
      (**(code **)((int)pMVar2[6].pVptr + 0x28))(0x41b80000,0x41000000);
      (**(code **)((int)pMVar2[6].pVptr + 0x30))(pMVar2 + 6,0x80,0x80,0x80);
      (**(code **)((int)pMVar2[6].pVptr + 0x2c))(pMVar2 + 6,0x80);
      pMVar2[6].bFlags = pMVar2[6].bFlags & 0xfe | 1;
      pMVar2[6].nCol = 0xe;
      pMVar2[6].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 6));
    }
    iStack_28 = iStack_28 + 1;
    uVar4 = *(ushort *)((int)ourBtlSaveDat__10BtlSaveSec + (int)pBStack_2c * 0xc0 + 0x62);
    iVar10 = GetRealMaxHP__10BtlSaveSecFiPc(pBStack_2c,0,(void *)((int)pBStack_2c * 2));
    iVar8 = (int)((uint)uVar4 * 0x37) / iVar10;
    if (iVar10 == 0) {
      trap(7);
    }
    if (bVar6) {
      Create__10MenuSpriteFUc(pMVar2 + 7,1);
      uVar11 = 0x40;
      pMVar2[7].bPflags = pMVar2[7].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 7));
      pMVar2[7].nPriority = 0xd;
      (**(code **)((int)pMVar2[7].pVptr + 0x24))(0x430e0000,0x42000000,pMVar2 + 7,uVar11);
      (**(code **)((int)pMVar2[7].pVptr + 0x30))(pMVar2 + 7,0x80,0x80,0x80);
      (**(code **)((int)pMVar2[7].pVptr + 0x2c))(pMVar2 + 7,0x80);
      pMVar2[7].bFlags = pMVar2[7].bFlags & 0xfe | 1;
      pMVar2[7].nCol = 0xf;
      pMVar2[7].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 7));
    }
    SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 7,3,1,(short)iVar8 + 3,7);
    (**(code **)((int)pMVar2[7].pVptr + 0x28))((float)iVar8,0x40c00000);
    pvVar12 = (void *)((int)ourBtlSaveDat__10BtlSaveSec + (int)pBStack_2c * 0xc0);
    uVar4 = *(ushort *)((int)pvVar12 + 0x66);
    iVar10 = GetRealMaxMP__10BtlSaveSecFiPc(pBStack_2c,0,pvVar12);
    iVar8 = (int)((uint)uVar4 * 0x38 - (uint)uVar4) / iVar10;
    if (iVar10 == 0) {
      trap(7);
    }
    if (bVar6) {
      Create__10MenuSpriteFUc(pMVar2 + 8,1);
      pMVar2[8].bPflags = pMVar2[8].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 8));
      pMVar2[8].nPriority = 0xd;
      (**(code **)((int)pMVar2[8].pVptr + 0x24))(0x435d0000,0x42000000);
      (**(code **)((int)pMVar2[8].pVptr + 0x30))(pMVar2 + 8,0x80,0x80,0x80);
      (**(code **)((int)pMVar2[8].pVptr + 0x2c))(pMVar2 + 8,0x80);
      pMVar2[8].bFlags = pMVar2[8].bFlags & 0xfe | 1;
      pMVar2[8].nCol = 0x10;
      pMVar2[8].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 8));
    }
    SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 8,0x40,1,(short)iVar8 + 0x40,7);
    (**(code **)((int)pMVar2[8].pVptr + 0x28))((float)iVar8,0x40c00000);
    cVar1 = *(char *)((int)ourBtlSaveDat__10BtlSaveSec + (int)pBStack_2c * 0xc0 + 0x69);
    iVar10 = GetRealMaxSP__10BtlSaveSecFiPc(pBStack_2c,0,ourBtlSaveDat__10BtlSaveSec);
    iVar8 = (cVar1 * 0x12) / iVar10;
    if (iVar10 == 0) {
      trap(7);
    }
    if (bVar6) {
      Create__10MenuSpriteFUc(pMVar2 + 9,1);
      pMVar2[9].bPflags = pMVar2[9].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 9));
      pMVar2[9].nPriority = 0xd;
      (**(code **)((int)pMVar2[9].pVptr + 0x24))(0x43960000,0x42000000);
      (**(code **)((int)pMVar2[9].pVptr + 0x30))(pMVar2 + 9,0x80,0x80,0x80);
      (**(code **)((int)pMVar2[9].pVptr + 0x2c))(pMVar2 + 9,0x80);
      pMVar2[9].bFlags = pMVar2[9].bFlags & 0xfe | 1;
      pMVar2[9].nCol = 0x11;
      pMVar2[9].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 9));
    }
    SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 9,0x7d,1,(short)iVar8 + 0x7d,7);
    (**(code **)((int)pMVar2[9].pVptr + 0x28))((float)iVar8,0x40c00000);
    pvVar12 = extraout_a2_lo;
    if (bVar6) {
      iStack_c4 = *(int *)(ourBtlSocket__9BtlSocket + 0x620);
      uStack_148 = *(u32 *)(iStack_c4 + (uint)*(ushort *)(iStack_c4 + 10) * 4 + 0xc);
      uStack_144 = uStack_148;
      uVar11 = GetTex0__6JRCTexFb(*(u32 *)(ourBtlSocket__9BtlSocket + 0x620),0);
      Create__11SendOnLocalFP4_QWDUl
                (*(int *)(iStack_20 + iStack_10 * 0x114 + 0x164) + iStack_28 * 0x30,uStack_148,
                 uVar11);
      iStack_c8 = *(int *)(iStack_20 + iStack_10 * 0x114 + 0x164) + iStack_28 * 0x30;
      *(u16 *)(iStack_c8 + 0x14) = 0xe;
      AddPriority__12MenuObjTableFP7MenuObj
                ((MenuObjTable *)(iStack_20 + iStack_10 * 0x114 + 0xc4),
                 (MenuObj *)(*(int *)(iStack_20 + iStack_10 * 0x114 + 0x164) + iStack_28 * 0x30));
      Create__10MenuSpriteFUc(pMVar2 + 10,1);
      pMVar2[10].bPflags = pMVar2[10].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 10));
      pMVar2[10].nPriority = 0xf;
      (**(code **)((int)pMVar2[10].pVptr + 0x24))(0x42a80000,0x40400000);
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 10,0,0,0x25,0xc);
      (**(code **)((int)pMVar2[10].pVptr + 0x28))(0x42140000,0x41400000);
      (**(code **)((int)pMVar2[10].pVptr + 0x30))(pMVar2 + 10,0x41,0x3f,0x4c);
      (**(code **)((int)pMVar2[10].pVptr + 0x2c))(pMVar2 + 10,0x80);
      pMVar2[10].bFlags = pMVar2[10].bFlags & 0xfe | 1;
      pMVar2[10].nCol = 0x12;
      pMVar2[10].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 10));
      Create__10MenuSpriteFUc(pMVar2 + 0xb,1);
      pMVar2[0xb].bPflags = pMVar2[0xb].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 0xb));
      pMVar2[0xb].nPriority = 0xf;
      (**(code **)((int)pMVar2[0xb].pVptr + 0x24))(0x42fa0000,0x41a80000);
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 0xb,0x25,0,0x35,0xc);
      (**(code **)((int)pMVar2[0xb].pVptr + 0x28))(0x41800000,0x41400000);
      (**(code **)((int)pMVar2[0xb].pVptr + 0x30))(pMVar2 + 0xb,0x34,0x47,0x65);
      (**(code **)((int)pMVar2[0xb].pVptr + 0x2c))(pMVar2 + 0xb,0x80);
      pMVar2[0xb].bFlags = pMVar2[0xb].bFlags & 0xfe | 1;
      pMVar2[0xb].nCol = 0x13;
      pMVar2[0xb].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 0xb));
      Create__10MenuSpriteFUc(pMVar2 + 0xc,1);
      pMVar2[0xc].bPflags = pMVar2[0xc].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 0xc));
      pMVar2[0xc].nPriority = 0xf;
      (**(code **)((int)pMVar2[0xc].pVptr + 0x24))(0x434c0000,0x41a80000);
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 0xc,0x35,0,0x45,0xc);
      (**(code **)((int)pMVar2[0xc].pVptr + 0x28))(0x41800000,0x41400000);
      (**(code **)((int)pMVar2[0xc].pVptr + 0x30))(pMVar2 + 0xc,0x55,0x26,0x4c);
      (**(code **)((int)pMVar2[0xc].pVptr + 0x2c))(pMVar2 + 0xc,0x80);
      pMVar2[0xc].bFlags = pMVar2[0xc].bFlags & 0xfe | 1;
      pMVar2[0xc].nCol = 0x14;
      pMVar2[0xc].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 0xc));
      Create__10MenuSpriteFUc(pMVar2 + 0xd,1);
      pMVar2[0xd].bPflags = pMVar2[0xd].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 0xd));
      pMVar2[0xd].nPriority = 0xf;
      (**(code **)((int)pMVar2[0xd].pVptr + 0x24))(0x438d8000,0x41a80000);
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 0xd,0x45,0,0x55,0xc);
      (**(code **)((int)pMVar2[0xd].pVptr + 0x28))(0x41800000,0x41400000);
      (**(code **)((int)pMVar2[0xd].pVptr + 0x30))(pMVar2 + 0xd,0x5a,0x24,0x24);
      (**(code **)((int)pMVar2[0xd].pVptr + 0x2c))(pMVar2 + 0xd,0x80);
      pMVar2[0xd].bFlags = pMVar2[0xd].bFlags & 0xfe | 1;
      pMVar2[0xd].nCol = 0x15;
      pMVar2[0xd].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 0xd));
      Create__10MenuSpriteFUc(pMVar2 + 0xe,1);
      pMVar2[0xe].bPflags = pMVar2[0xe].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 0xe));
      pMVar2[0xe].nPriority = 0xf;
      (**(code **)((int)pMVar2[0xe].pVptr + 0x24))(0x43868000,0x40400000);
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 0xe,0x55,0,0x73,0xc);
      (**(code **)((int)pMVar2[0xe].pVptr + 0x28))(0x41f00000,0x41400000);
      uVar11 = (**(code **)((int)pMVar2[0xe].pVptr + 0x30))(pMVar2 + 0xe,0x41,0x3f,0x4c);
      (**(code **)((int)pMVar2[0xe].pVptr + 0x2c))(pMVar2 + 0xe,0x80,pMVar2 + 0xe,uVar11);
      pMVar2[0xe].bFlags = pMVar2[0xe].bFlags & 0xfe | 1;
      pMVar2[0xe].nCol = 0x16;
      pMVar2[0xe].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 0xe));
      pvVar12 = extraout_a2_lo_00;
    }
    iStack_28 = iStack_28 + 1;
    iVar8 = GetRealMaxHP__10BtlSaveSecFiPc(pBStack_2c,0,pvVar12);
    iStack_34 = iVar8;
    if (iVar8 < 0) {
      iStack_34 = iVar8 + 1;
    }
    iStack_34 = iStack_34 >> 1;
    if ((iStack_34 < 2) && (2 < iVar8)) {
      iStack_34 = 2;
    }
    iStack_38 = iVar8;
    if (iVar8 < 0) {
      iStack_38 = iVar8 + 3;
    }
    iStack_38 = iStack_38 >> 2;
    if ((iStack_38 < 1) && (1 < iVar8)) {
      iStack_38 = 1;
    }
    if (bVar6) {
      Create__10MenuSpriteFUc(pMVar2 + 0xf,1);
      pMVar2[0xf].bPflags = pMVar2[0xf].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 0xf));
      pMVar2[0xf].nPriority = 0x10;
      (**(code **)((int)pMVar2[0xf].pVptr + 0x24))(0x430d0000,0x41a80000);
      (**(code **)((int)pMVar2[0xf].pVptr + 0x28))(0x41200000,0x41700000);
      (**(code **)((int)pMVar2[0xf].pVptr + 0x2c))(pMVar2 + 0xf,0x80);
      pMVar2[0xf].nCol = 0x17;
      pMVar2[0xf].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 0xf));
    }
    if (iStack_34 <
        (int)(uint)*(ushort *)((int)ourBtlSaveDat__10BtlSaveSec + (int)pBStack_2c * 0xc0 + 0x62)) {
      (**(code **)((int)pMVar2[0xf].pVptr + 0x30))(pMVar2 + 0xf,0x58,0x58,0x58);
    }
    else if (iStack_38 <
             (int)(uint)*(ushort *)
                         ((int)ourBtlSaveDat__10BtlSaveSec + (int)pBStack_2c * 0xc0 + 0x62)) {
      (**(code **)((int)pMVar2[0xf].pVptr + 0x30))(pMVar2 + 0xf,0x58,0x58,0);
    }
    else {
      (**(code **)((int)pMVar2[0xf].pVptr + 0x30))(pMVar2 + 0xf,0x58,0,0);
    }
    if (*(ushort *)((int)ourBtlSaveDat__10BtlSaveSec + (int)pBStack_2c * 0xc0 + 0x62) < 100) {
      pMVar2[0xf].bFlags = pMVar2[0xf].bFlags & 0xfe;
    }
    else {
      sVar7 = (short)((*(ushort *)((int)ourBtlSaveDat__10BtlSaveSec + (int)pBStack_2c * 0xc0 + 0x62)
                      / 100) % 10);
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 0xf,(sVar7 + 1) * 10,0xc,(sVar7 + 2) * 10,0x1b);
      pMVar2[0xf].bFlags = pMVar2[0xf].bFlags & 0xfe | 1;
    }
    if (bVar6) {
      Create__10MenuSpriteFUc(pMVar2 + 0x10,1);
      pMVar2[0x10].bPflags = pMVar2[0x10].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 0x10));
      pMVar2[0x10].nPriority = 0x10;
      (**(code **)((int)pMVar2[0x10].pVptr + 0x24))(0x43150000,0x41a80000);
      (**(code **)((int)pMVar2[0x10].pVptr + 0x28))(0x41200000,0x41700000);
      (**(code **)((int)pMVar2[0x10].pVptr + 0x2c))(pMVar2 + 0x10,0x80);
      pMVar2[0x10].nCol = 0x18;
      pMVar2[0x10].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 0x10));
    }
    if (iStack_34 <
        (int)(uint)*(ushort *)((int)ourBtlSaveDat__10BtlSaveSec + (int)pBStack_2c * 0xc0 + 0x62)) {
      (**(code **)((int)pMVar2[0x10].pVptr + 0x30))(pMVar2 + 0x10,0x58,0x58,0x58);
    }
    else if (iStack_38 <
             (int)(uint)*(ushort *)
                         ((int)ourBtlSaveDat__10BtlSaveSec + (int)pBStack_2c * 0xc0 + 0x62)) {
      (**(code **)((int)pMVar2[0x10].pVptr + 0x30))(pMVar2 + 0x10,0x58,0x58,0);
    }
    else {
      (**(code **)((int)pMVar2[0x10].pVptr + 0x30))(pMVar2 + 0x10,0x58,0,0);
    }
    if (*(ushort *)((int)ourBtlSaveDat__10BtlSaveSec + (int)pBStack_2c * 0xc0 + 0x62) < 10) {
      pMVar2[0x10].bFlags = pMVar2[0x10].bFlags & 0xfe;
    }
    else {
      sVar7 = (short)((*(ushort *)((int)ourBtlSaveDat__10BtlSaveSec + (int)pBStack_2c * 0xc0 + 0x62)
                      / 10) % 10);
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 0x10,(sVar7 + 1) * 10,0xc,(sVar7 + 2) * 10,0x1b);
      pMVar2[0x10].bFlags = pMVar2[0x10].bFlags & 0xfe | 1;
    }
    if (bVar6) {
      Create__10MenuSpriteFUc(pMVar2 + 0x11,1);
      pMVar2[0x11].bPflags = pMVar2[0x11].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 0x11));
      pMVar2[0x11].nPriority = 0x10;
      (**(code **)((int)pMVar2[0x11].pVptr + 0x24))(0x431d0000,0x41a80000);
      (**(code **)((int)pMVar2[0x11].pVptr + 0x28))(0x41200000,0x41700000);
      (**(code **)((int)pMVar2[0x11].pVptr + 0x2c))(pMVar2 + 0x11,0x80);
      pMVar2[0x11].nCol = 0x19;
      pMVar2[0x11].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 0x11));
    }
    if (iStack_34 <
        (int)(uint)*(ushort *)((int)ourBtlSaveDat__10BtlSaveSec + (int)pBStack_2c * 0xc0 + 0x62)) {
      (**(code **)((int)pMVar2[0x11].pVptr + 0x30))(pMVar2 + 0x11,0x58,0x58,0x58);
    }
    else if (iStack_38 <
             (int)(uint)*(ushort *)
                         ((int)ourBtlSaveDat__10BtlSaveSec + (int)pBStack_2c * 0xc0 + 0x62)) {
      (**(code **)((int)pMVar2[0x11].pVptr + 0x30))(pMVar2 + 0x11,0x58,0x58,0);
    }
    else {
      (**(code **)((int)pMVar2[0x11].pVptr + 0x30))(pMVar2 + 0x11,0x58,0,0);
    }
    uVar4 = *(ushort *)((int)ourBtlSaveDat__10BtlSaveSec + (int)pBStack_2c * 0xc0 + 0x62) % 10;
    SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 0x11,(uVar4 + 1) * 10,0xc,(uVar4 + 2) * 10,0x1b);
    pMVar2[0x11].bFlags = pMVar2[0x11].bFlags & 0xfe | 1;
    if (bVar6) {
      Create__10MenuSpriteFUc(pMVar2 + 0x12,1);
      pMVar2[0x12].bPflags = pMVar2[0x12].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 0x12));
      pMVar2[0x12].nPriority = 0x10;
      (**(code **)((int)pMVar2[0x12].pVptr + 0x24))(0x43250000,0x41a80000);
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 0x12,0,0xc,10,0x1b);
      (**(code **)((int)pMVar2[0x12].pVptr + 0x28))(0x41200000,0x41700000);
      (**(code **)((int)pMVar2[0x12].pVptr + 0x30))(pMVar2 + 0x12,0x58,0x58,0x58);
      (**(code **)((int)pMVar2[0x12].pVptr + 0x2c))(pMVar2 + 0x12,0x80);
      pMVar2[0x12].bFlags = pMVar2[0x12].bFlags & 0xfe | 1;
      pMVar2[0x12].nCol = 0x1a;
      pMVar2[0x12].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 0x12));
      Create__10MenuSpriteFUc(pMVar2 + 0x13,1);
      pMVar2[0x13].bPflags = pMVar2[0x13].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 0x13));
      pMVar2[0x13].nPriority = 0x10;
      (**(code **)((int)pMVar2[0x13].pVptr + 0x24))(0x432d0000,0x41a80000);
      (**(code **)((int)pMVar2[0x13].pVptr + 0x28))(0x41200000,0x41700000);
      uVar11 = (**(code **)((int)pMVar2[0x13].pVptr + 0x30))(pMVar2 + 0x13,0x58,0x58,0x58);
      (**(code **)((int)pMVar2[0x13].pVptr + 0x2c))(pMVar2 + 0x13,0x80,uVar11);
      pMVar2[0x13].nCol = 0x1b;
      pMVar2[0x13].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 0x13));
    }
    if (iVar8 < 100) {
      pMVar2[0x13].bFlags = pMVar2[0x13].bFlags & 0xfe;
    }
    else {
      sVar7 = (short)((iVar8 / 100) % 10);
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 0x13,(sVar7 + 1) * 10,0xc,(sVar7 + 2) * 10,0x1b);
      pMVar2[0x13].bFlags = pMVar2[0x13].bFlags & 0xfe | 1;
    }
    if (bVar6) {
      Create__10MenuSpriteFUc(pMVar2 + 0x14,1);
      pMVar2[0x14].bPflags = pMVar2[0x14].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 0x14));
      pMVar2[0x14].nPriority = 0x10;
      (**(code **)((int)pMVar2[0x14].pVptr + 0x24))(0x43350000,0x41a80000);
      (**(code **)((int)pMVar2[0x14].pVptr + 0x28))(0x41200000,0x41700000);
      (**(code **)((int)pMVar2[0x14].pVptr + 0x30))(pMVar2 + 0x14,0x58,0x58,0x58);
      (**(code **)((int)pMVar2[0x14].pVptr + 0x2c))(pMVar2 + 0x14,0x80);
      pMVar2[0x14].nCol = 0x1c;
      pMVar2[0x14].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 0x14));
    }
    if (iVar8 < 10) {
      pMVar2[0x14].bFlags = pMVar2[0x14].bFlags & 0xfe;
    }
    else {
      sVar7 = (short)((iVar8 / 10) % 10);
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 0x14,(sVar7 + 1) * 10,0xc,(sVar7 + 2) * 10,0x1b);
      pMVar2[0x14].bFlags = pMVar2[0x14].bFlags & 0xfe | 1;
    }
    if (bVar6) {
      Create__10MenuSpriteFUc(pMVar2 + 0x15,1);
      pMVar2[0x15].bPflags = pMVar2[0x15].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 0x15));
      pMVar2[0x15].nPriority = 0x10;
      (**(code **)((int)pMVar2[0x15].pVptr + 0x24))(0x433d0000,0x41a80000);
      (**(code **)((int)pMVar2[0x15].pVptr + 0x28))(0x41200000,0x41700000);
      (**(code **)((int)pMVar2[0x15].pVptr + 0x30))(pMVar2 + 0x15,0x58,0x58,0x58);
      (**(code **)((int)pMVar2[0x15].pVptr + 0x2c))(pMVar2 + 0x15,0x80);
      pMVar2[0x15].nCol = 0x1d;
      pMVar2[0x15].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 0x15));
    }
    sVar7 = (short)(iVar8 % 10);
    SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 0x15,(sVar7 + 1) * 10,0xc,(sVar7 + 2) * 10,0x1b);
    pMVar2[0x15].bFlags = pMVar2[0x15].bFlags & 0xfe | 1;
    iVar8 = GetRealMaxMP__10BtlSaveSecFiPc(pBStack_2c,0,p3);
    iStack_34 = iVar8;
    if (iVar8 < 0) {
      iStack_34 = iVar8 + 1;
    }
    iStack_34 = iStack_34 >> 1;
    if ((iStack_34 < 2) && (2 < iVar8)) {
      iStack_34 = 2;
    }
    iStack_38 = iVar8;
    if (iVar8 < 0) {
      iStack_38 = iVar8 + 3;
    }
    iStack_38 = iStack_38 >> 2;
    if ((iStack_38 < 1) && (1 < iVar8)) {
      iStack_38 = 1;
    }
    if (bVar6) {
      Create__10MenuSpriteFUc(pMVar2 + 0x16,1);
      pMVar2[0x16].bPflags = pMVar2[0x16].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 0x16));
      pMVar2[0x16].nPriority = 0x10;
      (**(code **)((int)pMVar2[0x16].pVptr + 0x24))(0x435c0000,0x41a80000);
      (**(code **)((int)pMVar2[0x16].pVptr + 0x28))(0x41200000,0x41700000);
      (**(code **)((int)pMVar2[0x16].pVptr + 0x2c))(pMVar2 + 0x16,0x80);
      pMVar2[0x16].nCol = 0x1e;
      pMVar2[0x16].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 0x16));
    }
    if (iStack_34 <
        (int)(uint)*(ushort *)((int)ourBtlSaveDat__10BtlSaveSec + (int)pBStack_2c * 0xc0 + 0x66)) {
      (**(code **)((int)pMVar2[0x16].pVptr + 0x30))(pMVar2 + 0x16,0x58,0x58,0x58);
    }
    else if (iStack_38 <
             (int)(uint)*(ushort *)
                         ((int)ourBtlSaveDat__10BtlSaveSec + (int)pBStack_2c * 0xc0 + 0x66)) {
      (**(code **)((int)pMVar2[0x16].pVptr + 0x30))(pMVar2 + 0x16,0x58,0x58,0);
    }
    else {
      (**(code **)((int)pMVar2[0x16].pVptr + 0x30))(pMVar2 + 0x16,0x58,0,0);
    }
    if (*(ushort *)((int)ourBtlSaveDat__10BtlSaveSec + (int)pBStack_2c * 0xc0 + 0x66) < 100) {
      pMVar2[0x16].bFlags = pMVar2[0x16].bFlags & 0xfe;
    }
    else {
      sVar7 = (short)((*(ushort *)((int)ourBtlSaveDat__10BtlSaveSec + (int)pBStack_2c * 0xc0 + 0x66)
                      / 100) % 10);
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 0x16,(sVar7 + 1) * 10,0xc,(sVar7 + 2) * 10,0x1b);
      pMVar2[0x16].bFlags = pMVar2[0x16].bFlags & 0xfe | 1;
    }
    if (bVar6) {
      Create__10MenuSpriteFUc(pMVar2 + 0x17,1);
      pMVar2[0x17].bPflags = pMVar2[0x17].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 0x17));
      pMVar2[0x17].nPriority = 0x10;
      (**(code **)((int)pMVar2[0x17].pVptr + 0x24))(0x43640000,0x41a80000);
      (**(code **)((int)pMVar2[0x17].pVptr + 0x28))(0x41200000,0x41700000);
      (**(code **)((int)pMVar2[0x17].pVptr + 0x2c))(pMVar2 + 0x17,0x80);
      pMVar2[0x17].nCol = 0x1f;
      pMVar2[0x17].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 0x17));
    }
    if (iStack_34 <
        (int)(uint)*(ushort *)((int)ourBtlSaveDat__10BtlSaveSec + (int)pBStack_2c * 0xc0 + 0x66)) {
      (**(code **)((int)pMVar2[0x17].pVptr + 0x30))(pMVar2 + 0x17,0x58,0x58,0x58);
    }
    else if (iStack_38 <
             (int)(uint)*(ushort *)
                         ((int)ourBtlSaveDat__10BtlSaveSec + (int)pBStack_2c * 0xc0 + 0x66)) {
      (**(code **)((int)pMVar2[0x17].pVptr + 0x30))(pMVar2 + 0x17,0x58,0x58,0);
    }
    else {
      (**(code **)((int)pMVar2[0x17].pVptr + 0x30))(pMVar2 + 0x17,0x58,0,0);
    }
    if (*(ushort *)((int)ourBtlSaveDat__10BtlSaveSec + (int)pBStack_2c * 0xc0 + 0x66) < 10) {
      pMVar2[0x17].bFlags = pMVar2[0x17].bFlags & 0xfe;
    }
    else {
      sVar7 = (short)((*(ushort *)((int)ourBtlSaveDat__10BtlSaveSec + (int)pBStack_2c * 0xc0 + 0x66)
                      / 10) % 10);
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 0x17,(sVar7 + 1) * 10,0xc,(sVar7 + 2) * 10,0x1b);
      pMVar2[0x17].bFlags = pMVar2[0x17].bFlags & 0xfe | 1;
    }
    if (bVar6) {
      Create__10MenuSpriteFUc(pMVar2 + 0x18,1);
      pMVar2[0x18].bPflags = pMVar2[0x18].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 0x18));
      pMVar2[0x18].nPriority = 0x10;
      (**(code **)((int)pMVar2[0x18].pVptr + 0x24))(0x436c0000,0x41a80000);
      (**(code **)((int)pMVar2[0x18].pVptr + 0x28))(0x41200000,0x41700000);
      (**(code **)((int)pMVar2[0x18].pVptr + 0x30))(pMVar2 + 0x18,0x58,0x58,0x58);
      (**(code **)((int)pMVar2[0x18].pVptr + 0x2c))(pMVar2 + 0x18,0x80);
      pMVar2[0x18].nCol = 0x20;
      pMVar2[0x18].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 0x18));
    }
    if (iStack_34 <
        (int)(uint)*(ushort *)((int)ourBtlSaveDat__10BtlSaveSec + (int)pBStack_2c * 0xc0 + 0x66)) {
      (**(code **)((int)pMVar2[0x18].pVptr + 0x30))(pMVar2 + 0x18,0x58,0x58,0x58);
    }
    else if (iStack_38 <
             (int)(uint)*(ushort *)
                         ((int)ourBtlSaveDat__10BtlSaveSec + (int)pBStack_2c * 0xc0 + 0x66)) {
      (**(code **)((int)pMVar2[0x18].pVptr + 0x30))(pMVar2 + 0x18,0x58,0x58,0);
    }
    else {
      (**(code **)((int)pMVar2[0x18].pVptr + 0x30))(pMVar2 + 0x18,0x58,0,0);
    }
    uVar4 = *(ushort *)((int)ourBtlSaveDat__10BtlSaveSec + (int)pBStack_2c * 0xc0 + 0x66) % 10;
    SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 0x18,(uVar4 + 1) * 10,0xc,(uVar4 + 2) * 10,0x1b);
    pMVar2[0x18].bFlags = pMVar2[0x18].bFlags & 0xfe | 1;
    if (bVar6) {
      Create__10MenuSpriteFUc(pMVar2 + 0x19,1);
      pMVar2[0x19].bPflags = pMVar2[0x19].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 0x19));
      pMVar2[0x19].nPriority = 0x10;
      (**(code **)((int)pMVar2[0x19].pVptr + 0x24))(0x43740000,0x41a80000);
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 0x19,0,0xc,10,0x1b);
      (**(code **)((int)pMVar2[0x19].pVptr + 0x28))(0x41200000,0x41700000);
      uVar11 = (**(code **)((int)pMVar2[0x19].pVptr + 0x30))(pMVar2 + 0x19,0x58,0x58,0x58);
      (**(code **)((int)pMVar2[0x19].pVptr + 0x2c))(pMVar2 + 0x19,0x80,uVar11);
      pMVar2[0x19].bFlags = pMVar2[0x19].bFlags & 0xfe | 1;
      pMVar2[0x19].nCol = 0x21;
      pMVar2[0x19].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 0x19));
      Create__10MenuSpriteFUc(pMVar2 + 0x1a,1);
      pMVar2[0x1a].bPflags = pMVar2[0x1a].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 0x1a));
      pMVar2[0x1a].nPriority = 0x10;
      (**(code **)((int)pMVar2[0x1a].pVptr + 0x24))(0x437c0000,0x41a80000);
      (**(code **)((int)pMVar2[0x1a].pVptr + 0x28))(0x41200000,0x41700000);
      (**(code **)((int)pMVar2[0x1a].pVptr + 0x30))(pMVar2 + 0x1a,0x58,0x58,0x58);
      (**(code **)((int)pMVar2[0x1a].pVptr + 0x2c))(pMVar2 + 0x1a,0x80);
      pMVar2[0x1a].nCol = 0x22;
      pMVar2[0x1a].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 0x1a));
    }
    if (iVar8 < 100) {
      pMVar2[0x1a].bFlags = pMVar2[0x1a].bFlags & 0xfe;
    }
    else {
      sVar7 = (short)((iVar8 / 100) % 10);
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 0x1a,(sVar7 + 1) * 10,0xc,(sVar7 + 2) * 10,0x1b);
      pMVar2[0x1a].bFlags = pMVar2[0x1a].bFlags & 0xfe | 1;
    }
    if (bVar6) {
      Create__10MenuSpriteFUc(pMVar2 + 0x1b,1);
      pMVar2[0x1b].bPflags = pMVar2[0x1b].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 0x1b));
      pMVar2[0x1b].nPriority = 0x10;
      (**(code **)((int)pMVar2[0x1b].pVptr + 0x24))(0x43820000,0x41a80000);
      (**(code **)((int)pMVar2[0x1b].pVptr + 0x28))(0x41200000,0x41700000);
      (**(code **)((int)pMVar2[0x1b].pVptr + 0x30))(pMVar2 + 0x1b,0x58,0x58,0x58);
      (**(code **)((int)pMVar2[0x1b].pVptr + 0x2c))(pMVar2 + 0x1b,0x80);
      pMVar2[0x1b].nCol = 0x23;
      pMVar2[0x1b].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 0x1b));
    }
    if (iVar8 < 10) {
      pMVar2[0x1b].bFlags = pMVar2[0x1b].bFlags & 0xfe;
    }
    else {
      sVar7 = (short)((iVar8 / 10) % 10);
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 0x1b,(sVar7 + 1) * 10,0xc,(sVar7 + 2) * 10,0x1b);
      pMVar2[0x1b].bFlags = pMVar2[0x1b].bFlags & 0xfe | 1;
    }
    if (bVar6) {
      Create__10MenuSpriteFUc(pMVar2 + 0x1c,1);
      pMVar2[0x1c].bPflags = pMVar2[0x1c].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 0x1c));
      pMVar2[0x1c].nPriority = 0x10;
      (**(code **)((int)pMVar2[0x1c].pVptr + 0x24))(0x43860000,0x41a80000);
      (**(code **)((int)pMVar2[0x1c].pVptr + 0x28))(0x41200000,0x41700000);
      (**(code **)((int)pMVar2[0x1c].pVptr + 0x30))(pMVar2 + 0x1c,0x58,0x58,0x58);
      (**(code **)((int)pMVar2[0x1c].pVptr + 0x2c))(pMVar2 + 0x1c,0x80);
      pMVar2[0x1c].nCol = 0x24;
      pMVar2[0x1c].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 0x1c));
    }
    sVar7 = (short)(iVar8 % 10);
    SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 0x1c,(sVar7 + 1) * 10,0xc,(sVar7 + 2) * 10,0x1b);
    pMVar2[0x1c].bFlags = pMVar2[0x1c].bFlags & 0xfe | 1;
    if (bVar6) {
      Create__10MenuSpriteFUc(pMVar2 + 0x1d,1);
      pMVar2[0x1d].bPflags = pMVar2[0x1d].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 0x1d));
      pMVar2[0x1d].nPriority = 0x10;
      (**(code **)((int)pMVar2[0x1d].pVptr + 0x24))(0x43958000,0x41a80000);
      uVar11 = (**(code **)((int)pMVar2[0x1d].pVptr + 0x28))(0x41200000,0x41700000);
      (**(code **)((int)pMVar2[0x1d].pVptr + 0x30))(pMVar2 + 0x1d,0x58,0x58,0x58,0x57,0x58,uVar11);
      (**(code **)((int)pMVar2[0x1d].pVptr + 0x2c))(pMVar2 + 0x1d,0x80);
      pMVar2[0x1d].nCol = 0x25;
      pMVar2[0x1d].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 0x1d));
    }
    if (*(char *)((int)ourBtlSaveDat__10BtlSaveSec + (int)pBStack_2c * 0xc0 + 0x69) < '\n') {
      pMVar2[0x1d].bFlags = pMVar2[0x1d].bFlags & 0xfe;
    }
    else {
      sVar7 = (short)(((int)*(char *)((int)ourBtlSaveDat__10BtlSaveSec +
                                     (int)pBStack_2c * 0xc0 + 0x69) / 10) % 10);
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 0x1d,(sVar7 + 1) * 10,0xc,(sVar7 + 2) * 10,0x1b);
      pMVar2[0x1d].bFlags = pMVar2[0x1d].bFlags & 0xfe | 1;
    }
    if (bVar6) {
      Create__10MenuSpriteFUc(pMVar2 + 0x1e,1);
      pMVar2[0x1e].bPflags = pMVar2[0x1e].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 0x1e));
      pMVar2[0x1e].nPriority = 0x10;
      (**(code **)((int)pMVar2[0x1e].pVptr + 0x24))(0x43998000,0x41a80000);
      (**(code **)((int)pMVar2[0x1e].pVptr + 0x28))(0x41200000,0x41700000);
      uVar11 = (**(code **)((int)pMVar2[0x1e].pVptr + 0x30))(pMVar2 + 0x1e,0x58,0x58,0x58);
      (**(code **)((int)pMVar2[0x1e].pVptr + 0x2c))(pMVar2 + 0x1e,0x80,uVar11);
      pMVar2[0x1e].nCol = 0x26;
      pMVar2[0x1e].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 0x1e));
    }
    sVar7 = (short)*(char *)((int)ourBtlSaveDat__10BtlSaveSec + (int)pBStack_2c * 0xc0 + 0x69) % 10;
    SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 0x1e,(sVar7 + 1) * 10,0xc,(sVar7 + 2) * 10,0x1b);
    pMVar2[0x1e].bFlags = pMVar2[0x1e].bFlags & 0xfe | 1;
    iVar8 = GetNextExp__10BtlSaveSecFi(pBStack_2c,-2);
    if (bVar6) {
      Create__10MenuSpriteFUc(pMVar2 + 0x1f,1);
      pMVar2[0x1f].bPflags = pMVar2[0x1f].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 0x1f));
      pMVar2[0x1f].nPriority = 0x10;
      (**(code **)((int)pMVar2[0x1f].pVptr + 0x24))(0x43958000,0x40400000);
      (**(code **)((int)pMVar2[0x1f].pVptr + 0x28))(0x41200000,0x41700000);
      (**(code **)((int)pMVar2[0x1f].pVptr + 0x30))(pMVar2 + 0x1f,0x58,0x58,0x58);
      (**(code **)((int)pMVar2[0x1f].pVptr + 0x2c))(pMVar2 + 0x1f,0x80);
      pMVar2[0x1f].nCol = 0x27;
      pMVar2[0x1f].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 0x1f));
    }
    if (iVar8 < 1) {
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 0x1f,0x73,0,0x7d,0xf);
      pMVar2[0x1f].bFlags = pMVar2[0x1f].bFlags & 0xfe | 1;
    }
    else if (iVar8 < 10000) {
      pMVar2[0x1f].bFlags = pMVar2[0x1f].bFlags & 0xfe;
    }
    else {
      sVar7 = (short)((iVar8 / 10000) % 10);
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 0x1f,(sVar7 + 1) * 10,0xc,(sVar7 + 2) * 10,0x1b);
      pMVar2[0x1f].bFlags = pMVar2[0x1f].bFlags & 0xfe | 1;
    }
    if (bVar6) {
      Create__10MenuSpriteFUc(pMVar2 + 0x20,1);
      pMVar2[0x20].bPflags = pMVar2[0x20].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 0x20));
      pMVar2[0x20].nPriority = 0x10;
      (**(code **)((int)pMVar2[0x20].pVptr + 0x24))(0x43998000,0x40400000);
      (**(code **)((int)pMVar2[0x20].pVptr + 0x28))(0x41200000,0x41700000);
      (**(code **)((int)pMVar2[0x20].pVptr + 0x30))(pMVar2 + 0x20,0x58,0x58,0x58);
      (**(code **)((int)pMVar2[0x20].pVptr + 0x2c))(pMVar2 + 0x20,0x80);
      pMVar2[0x20].nCol = 0x28;
      pMVar2[0x20].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 0x20));
    }
    if (iVar8 < 1) {
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 0x20,0x73,0,0x7d,0xf);
      pMVar2[0x20].bFlags = pMVar2[0x20].bFlags & 0xfe | 1;
    }
    else if (iVar8 < 1000) {
      pMVar2[0x20].bFlags = pMVar2[0x20].bFlags & 0xfe;
    }
    else {
      sVar7 = (short)((iVar8 / 1000) % 10);
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 0x20,(sVar7 + 1) * 10,0xc,(sVar7 + 2) * 10,0x1b);
      pMVar2[0x20].bFlags = pMVar2[0x20].bFlags & 0xfe | 1;
    }
    if (bVar6) {
      Create__10MenuSpriteFUc(pMVar2 + 0x21,1);
      pMVar2[0x21].bPflags = pMVar2[0x21].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 0x21));
      pMVar2[0x21].nPriority = 0x10;
      (**(code **)((int)pMVar2[0x21].pVptr + 0x24))(0x439d8000,0x40400000);
      (**(code **)((int)pMVar2[0x21].pVptr + 0x28))(0x41200000,0x41700000);
      (**(code **)((int)pMVar2[0x21].pVptr + 0x30))(pMVar2 + 0x21,0x58,0x58,0x58);
      (**(code **)((int)pMVar2[0x21].pVptr + 0x2c))(pMVar2 + 0x21,0x80);
      pMVar2[0x21].nCol = 0x29;
      pMVar2[0x21].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 0x21));
    }
    if (iVar8 < 1) {
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 0x21,0x73,0,0x7d,0xf);
      pMVar2[0x21].bFlags = pMVar2[0x21].bFlags & 0xfe | 1;
    }
    else if (iVar8 < 100) {
      pMVar2[0x21].bFlags = pMVar2[0x21].bFlags & 0xfe;
    }
    else {
      sVar7 = (short)((iVar8 / 100) % 10);
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 0x21,(sVar7 + 1) * 10,0xc,(sVar7 + 2) * 10,0x1b);
      pMVar2[0x21].bFlags = pMVar2[0x21].bFlags & 0xfe | 1;
    }
    if (bVar6) {
      Create__10MenuSpriteFUc(pMVar2 + 0x22,1);
      pMVar2[0x22].bPflags = pMVar2[0x22].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 0x22));
      pMVar2[0x22].nPriority = 0x10;
      (**(code **)((int)pMVar2[0x22].pVptr + 0x24))(0x43a18000,0x40400000);
      (**(code **)((int)pMVar2[0x22].pVptr + 0x28))(0x41200000,0x41700000);
      (**(code **)((int)pMVar2[0x22].pVptr + 0x30))(pMVar2 + 0x22,0x58,0x58,0x58);
      (**(code **)((int)pMVar2[0x22].pVptr + 0x2c))(pMVar2 + 0x22,0x80);
      pMVar2[0x22].nCol = 0x2a;
      pMVar2[0x22].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 0x22));
    }
    if (iVar8 < 1) {
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 0x22,0x73,0,0x7d,0xf);
      pMVar2[0x22].bFlags = pMVar2[0x22].bFlags & 0xfe | 1;
    }
    else if (iVar8 < 10) {
      pMVar2[0x22].bFlags = pMVar2[0x22].bFlags & 0xfe;
    }
    else {
      sVar7 = (short)((iVar8 / 10) % 10);
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 0x22,(sVar7 + 1) * 10,0xc,(sVar7 + 2) * 10,0x1b);
      pMVar2[0x22].bFlags = pMVar2[0x22].bFlags & 0xfe | 1;
    }
    if (bVar6) {
      Create__10MenuSpriteFUc(pMVar2 + 0x23,1);
      pMVar2[0x23].bPflags = pMVar2[0x23].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 0x23));
      pMVar2[0x23].nPriority = 0x10;
      (**(code **)((int)pMVar2[0x23].pVptr + 0x24))(0x43a58000,0x40400000);
      uVar11 = (**(code **)((int)pMVar2[0x23].pVptr + 0x28))(0x41200000,0x41700000);
      (**(code **)((int)pMVar2[0x23].pVptr + 0x30))(pMVar2 + 0x23,0x58,0x58,0x58,uVar11);
      (**(code **)((int)pMVar2[0x23].pVptr + 0x2c))(pMVar2 + 0x23,0x80);
      pMVar2[0x23].nCol = 0x2b;
      pMVar2[0x23].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 0x23));
    }
    if (iVar8 < 1) {
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 0x23,0x73,0,0x7d,0xf);
      pMVar2[0x23].bFlags = pMVar2[0x23].bFlags & 0xfe | 1;
    }
    else {
      sVar7 = (short)(iVar8 % 10);
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 0x23,(sVar7 + 1) * 10,0xc,(sVar7 + 2) * 10,0x1b);
      pMVar2[0x23].bFlags = pMVar2[0x23].bFlags & 0xfe | 1;
    }
    if (bVar6) {
      Create__8FontDrawF6GS_PSMUsUsUcUiP10ClutRaster
                (iStack_20 + iStack_10 * 0x114 + 0x6c,0x2c,0xc0,0x20,0,0,0);
      iVar8 = iStack_20 + iStack_10 * 0x114;
      *(byte *)(iVar8 + 0x60) = *(byte *)(iVar8 + 0x60) & 0xfd | 2;
      *(u16 *)(iStack_20 + iStack_10 * 0x114 + 0x80) = 0x11;
      AddPriority__12MenuObjTableFP7MenuObj
                ((MenuObjTable *)(iStack_20 + iStack_10 * 0x114 + 0xc4),
                 (MenuObj *)(iStack_20 + iStack_10 * 0x114 + 0x6c));
      Create__8MenuTextFUcUc((MenuText *)((int)pMStack_44 + iStack_24 * 0x80),1,2);
      *(u16 *)((int)pMStack_44 + iStack_24 * 0x80 + 0x14) = 0x12;
      *(u8 *)((int)pMStack_44 + iStack_24 * 0x80 + 0x5a) = 1;
      *(u8 *)((int)pMStack_44 + iStack_24 * 0x80 + 0x5b) = 0;
      SetMessage__8MenuTextFPcUiUcUc
                ((MenuText *)((int)pMStack_44 + iStack_24 * 0x80),
                 (void *)((int)ourBtlSaveDat__10BtlSaveSec + (int)pBStack_2c * 0xc0 + 0x4e),0,0,1);
      (**(code **)(*(int *)((int)pMStack_44 + iStack_24 * 0x80 + 8) + 0x24))(0x43000000,0x40000000);
      iVar8 = (int)pMStack_44 + iStack_24 * 0x80;
      *(byte *)(iVar8 + 0x12) = *(byte *)(iVar8 + 0x12) & 0xfe | 1;
      *(u16 *)((int)pMStack_44 + iStack_24 * 0x80 + 0x1c) = 0x2c;
      *(u16 *)((int)pMStack_44 + iStack_24 * 0x80 + 0x1e) = 0;
      OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_
                (iStack_20 + iStack_10 * 0x114 + 0x6c,(int)pMStack_44 + iStack_24 * 0x80,1,0);
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),
                 (MenuPlace *)((int)pMStack_44 + iStack_24 * 0x80));
    }
    iStack_24 = iStack_24 + 1;
    if (bVar6) {
      iStack_cc = *(int *)(ourBtlSocket__9BtlSocket + 0x618);
      uStack_150 = *(u32 *)(iStack_cc + (uint)*(ushort *)(iStack_cc + 10) * 4 + 0xc);
      uStack_14c = uStack_150;
      uVar11 = GetTex0__6JRCTexFb(*(u32 *)(ourBtlSocket__9BtlSocket + 0x618),0);
      Create__11SendOnLocalFP4_QWDUl
                (*(int *)(iStack_20 + iStack_10 * 0x114 + 0x164) + iStack_28 * 0x30,uStack_150,
                 uVar11);
      iStack_d0 = *(int *)(iStack_20 + iStack_10 * 0x114 + 0x164) + iStack_28 * 0x30;
      *(u16 *)(iStack_d0 + 0x14) = 0x13;
      AddPriority__12MenuObjTableFP7MenuObj
                ((MenuObjTable *)(iStack_20 + iStack_10 * 0x114 + 0xc4),
                 (MenuObj *)(*(int *)(iStack_20 + iStack_10 * 0x114 + 0x164) + iStack_28 * 0x30));
      Create__10MenuSpriteFUc(pMVar2 + 0x24,1);
      pMVar2[0x24].bPflags = pMVar2[0x24].bPflags & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv((MenuObj *)(pMVar2 + 0x24));
      pMVar2[0x24].nPriority = 0x14;
      SetUV__10MenuSpriteFUsUsUsUs(pMVar2 + 0x24,0,0x30,0x68,0x49);
      (**(code **)((int)pMVar2[0x24].pVptr + 0x30))(pMVar2 + 0x24,0x80,0x80,0x80);
      (**(code **)((int)pMVar2[0x24].pVptr + 0x2c))(pMVar2 + 0x24,0x80);
      pMVar2[0x24].nCol = 0x2d;
      pMVar2[0x24].nRow = 0;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),(MenuPlace *)(pMVar2 + 0x24));
    }
    if ((((ulong)*(ushort *)(iStack_20 + 0x24) & 0x3ff) >> 2 & (long)(1 << (iStack_10 - 2U & 0x1f)))
        == 0) {
      pMVar2[0x24].bFlags = pMVar2[0x24].bFlags & 0xfe;
    }
    else {
      fStack_40 = cosf(*(float *)(iStack_20 + (iStack_10 + -2) * 4 + 0xdbc));
      fStack_40 = fStack_40 * 104.0;
      fStack_3c = 55.0 - fStack_40 / 2.0;
      (**(code **)((int)pMVar2[0x24].pVptr + 0x24))(fStack_3c,0x41a00000);
      (**(code **)((int)pMVar2[0x24].pVptr + 0x28))(fStack_40,0x41c80000);
      pMVar2[0x24].bFlags = pMVar2[0x24].bFlags & 0xfe | 1;
    }
    iStack_28 = iStack_28 + 1;
    if (bVar6) {
      Open__10MenuWindowFUci((MenuWindow *)(iStack_20 + iStack_10 * 0x114 + 0xac),3,0x14d);
    }
  }
  return;
}

/* ---- 0x00371860 size 0x8  BtlResult::@24@__dt(v)
 *      mangled: @24@__dt__9BtlResultFv */
int _24___dt__9BtlResultFv(int param_1,short param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = param_1 + -0x18;
  if (iVar1 != 0) {
    *(u8 **)(param_1 + -4) = __vt__9BtlResult;
    *(u32 *)(param_1 + 8) = 0x406df0;
    for (iVar2 = 0; iVar2 < 0xc; iVar2 = iVar2 + 1) {
      if ((long)((ulong)*(byte *)(iVar1 + iVar2 * 0x114 + 0x60) << 0x3e) < 0) {
        Release__7MenuObjFv((MenuObj *)(iVar1 + iVar2 * 0x114 + 0x6c));
      }
      if ((long)((ulong)*(byte *)(iVar1 + iVar2 * 0x114 + 0x60) << 0x3c) < 0) {
        Release__7MenuObjFv((MenuObj *)(iVar1 + iVar2 * 0x114 + 0xac));
      }
      if (((ulong)*(ushort *)(iVar1 + iVar2 * 0x114 + 0x60) & 0xfff) >> 4 != 0) {
        __destroy_new_array(*(u32 *)(iVar1 + iVar2 * 0x114 + 0x160),0x273e20);
      }
      if (*(int *)(iVar1 + iVar2 * 0x114 + 0x168) != 0) {
        __destroy_new_array(*(u32 *)(iVar1 + iVar2 * 0x114 + 0x168),0x2661a0);
      }
      if (*(int *)(iVar1 + iVar2 * 0x114 + 0x164) != 0) {
        __destroy_new_array(*(u32 *)(iVar1 + iVar2 * 0x114 + 0x164),0x277890);
      }
      if (*(int *)(iVar1 + iVar2 * 0x114 + 0x16c) != 0) {
        __destroy_new_array(*(u32 *)(iVar1 + iVar2 * 0x114 + 0x16c),0x2766d0);
      }
      if (*(int *)(iVar1 + iVar2 * 0x114 + 0x170) != 0) {
        __destroy_new_array(*(u32 *)(iVar1 + iVar2 * 0x114 + 0x170),0x28d070);
      }
    }
    if (*(int *)(param_1 + 0xd38) != 0) {
      iVar2 = *(int *)(param_1 + 0xd38);
      if (iVar2 != 0) {
        (**(code **)(*(int *)(iVar2 + 8) + 8))(iVar2,1);
      }
    }
    ourBtlResult__9BtlResult = 0;
    __destroy_arr(param_1 + 0x48,0x34c970,0x114,0xc);
    if (iVar1 != -0x18) {
      *(u8 **)(param_1 + 8) = __vt__17DelayDeleteObject;
    }
    __dt__7CPolObjFv(iVar1,0);
    if (0 < param_2) {
      __dl__FPv(iVar1);
    }
  }
  return iVar1;
}

