/* decomp/H/BtlMenu.c — cleaned Ghidra output (SH2JP_BATTLE.BIN, JP Furokuban, base 0x00430a00).
 * 50 function(s). Types: see types.h. Names/gp globals resolved from symbols/SLPM_602.19.syms. */
#include "types.h"

/* ---------------------------------------------------------------------------
 * JP: 0x0058bba0  SetCallBack__7BtlMenuFPFiiiiiPvPv_vPv
 * C++: BtlMenu::SetCallBack(void *, void *)
 * size: 0x28 bytes
 * --------------------------------------------------------------------------- */
void SetCallBack__7BtlMenuFPFiiiiiPvPv_vPv(undefined4 param_1,undefined4 param_2)

{
  uGpffff86ec = param_1;
  uGpffff86e8 = param_2;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0058bbd0  MakeMesWin__7BtlMenuFiiPci
 * C++: BtlMenu::MakeMesWin(int, int, char *, int)
 * size: 0xfc bytes
 * --------------------------------------------------------------------------- */
int MakeMesWin__7BtlMenuFiiPci
              (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  bool bVar1;
  long lVar2;
  int iVar3;
  int iVar4;
  
  bVar1 = true;
  iVar4 = 0;
  while (bVar1) {
    bVar1 = false;
    iVar3 = iGpffff86f0;
    while ((iVar3 != 0 && (!bVar1))) {
      if (*(int *)(iVar3 + 0x2c) == iVar4) {
        bVar1 = true;
      }
      iVar3 = *(int *)(iVar3 + 0x28);
    }
    if (!bVar1) break;
    iVar4 = iVar4 + 1;
  }
  lVar2 = __nw__FUi(0x138);
  if (lVar2 != 0) {
    __ct__7BMesWinFiiiPci(lVar2,iVar4,param_1,param_2,param_3,param_4);
  }
  return iVar4;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0058bcd0  BMesWinEntry__7BtlMenuFP7BMesWin
 * C++: BtlMenu::BMesWinEntry(BMesWin *)
 * size: 0x6c bytes
 * --------------------------------------------------------------------------- */
void BMesWinEntry__7BtlMenuFP7BMesWin(int param_1)

{
  if (iGpffff86f4 == 0) {
    *(undefined4 *)(param_1 + 0x24) = 0;
    iGpffff86f0 = param_1;
  }
  else {
    *(int *)(param_1 + 0x24) = iGpffff86f4;
    *(int *)(*(int *)(param_1 + 0x24) + 0x28) = param_1;
  }
  *(undefined4 *)(param_1 + 0x28) = 0;
  iGpffff86f4 = param_1;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0058bd40  BMesWinRelease__7BtlMenuFP7BMesWin
 * C++: BtlMenu::BMesWinRelease(BMesWin *)
 * size: 0xa4 bytes
 * --------------------------------------------------------------------------- */
void BMesWinRelease__7BtlMenuFP7BMesWin(int param_1)

{
  if (*(int *)(param_1 + 0x24) == 0) {
    uGpffff86f0 = *(undefined4 *)(param_1 + 0x28);
  }
  else {
    *(undefined4 *)(*(int *)(param_1 + 0x24) + 0x28) = *(undefined4 *)(param_1 + 0x28);
  }
  if (*(int *)(param_1 + 0x28) == 0) {
    uGpffff86f4 = *(undefined4 *)(param_1 + 0x24);
  }
  else {
    *(undefined4 *)(*(int *)(param_1 + 0x28) + 0x24) = *(undefined4 *)(param_1 + 0x24);
  }
  *(undefined4 *)(param_1 + 0x24) = 0;
  *(undefined4 *)(param_1 + 0x28) = 0;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0058bdf0  AllMesWinDestruct__7BtlMenuFv
 * C++: BtlMenu::AllMesWinDestruct()
 * size: 0x5c bytes
 * --------------------------------------------------------------------------- */
void AllMesWinDestruct__7BtlMenuFv(void)

{
  int iVar1;
  int iVar2;
  
  iVar2 = iGpffff86f0;
  while (iVar2 != 0) {
    iVar1 = *(int *)(iVar2 + 0x28);
    Destruct__7BMesWinFv(iVar2);
    iVar2 = iVar1;
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0058be50  FindMesWin__7BtlMenuFi
 * C++: BtlMenu::FindMesWin(int)
 * size: 0x60 bytes
 * --------------------------------------------------------------------------- */
int FindMesWin__7BtlMenuFi(int param_1)

{
  int iVar1;
  
  iVar1 = iGpffff86f0;
  while( true ) {
    if (iVar1 == 0) {
      return 0;
    }
    if (*(int *)(iVar1 + 0x2c) == param_1) break;
    iVar1 = *(int *)(iVar1 + 0x28);
  }
  return iVar1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0058beb0  SetMesWinClose__7BtlMenuFi
 * C++: BtlMenu::SetMesWinClose(int)
 * size: 0x4c bytes
 * --------------------------------------------------------------------------- */
void SetMesWinClose__7BtlMenuFi(undefined4 param_1)

{
  long lVar1;
  
  lVar1 = FindMesWin__7BtlMenuFi(param_1);
  if (lVar1 != 0) {
    SetClose__7BMesWinFv(lVar1);
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0058bf00  MakeCursole__7BtlMenuFiUcUcUcUcUcP7FVectori
 * C++: BtlMenu::MakeCursole(int, uchar, uchar, uchar, uchar, uchar, FVector *, int)
 * size: 0x244 bytes
 * --------------------------------------------------------------------------- */
int MakeCursole__7BtlMenuFiUcUcUcUcUcP7FVectori
              (undefined4 param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4,
              undefined1 param_5,byte param_6,undefined8 param_7,int param_8)

{
  bool bVar1;
  long lVar2;
  ulong uVar3;
  int iVar4;
  int iStack_10;
  
  if (param_8 < 0) {
    bVar1 = true;
    iStack_10 = 0;
    while (bVar1) {
      bVar1 = false;
      iVar4 = iGpffff86f8;
      while ((iVar4 != 0 && (!bVar1))) {
        if (*(int *)(iVar4 + 0x50) == iStack_10) {
          bVar1 = true;
        }
        iVar4 = *(int *)(iVar4 + 0x4c);
      }
      if (!bVar1) break;
      iStack_10 = iStack_10 + 1;
    }
    lVar2 = __nw__FUi(0x180);
    if (lVar2 != 0) {
      __ct__8BCursoleFiiUcUcUcUcUcP7FVector
                (lVar2,iStack_10,param_1,param_2,param_3,param_4,param_5,param_6);
    }
  }
  else {
    lVar2 = FindBCursole__7BtlMenuFi(param_8);
    iStack_10 = param_8;
    if (lVar2 == 0) {
      lVar2 = __nw__FUi(0x180);
      if (lVar2 != 0) {
        __ct__8BCursoleFiiUcUcUcUcUcP7FVector
                  (lVar2,param_8,param_1,param_2,param_3,param_4,param_5,param_6);
      }
    }
    else {
      iVar4 = (int)lVar2;
      *(short *)(iVar4 + 0x56) = (short)param_1;
      Create__6CursorFUcUcUcUc(iVar4 + 0x58,param_2,param_3,param_4,param_5);
      *(ushort *)(iVar4 + 0x10a) = *(ushort *)(iVar4 + 0x10a) & 0xfc3f | (param_6 & 0xf) << 6;
      uVar3 = (ulong)*(byte *)(iVar4 + 0x109) & 0xfffffffffffffffd | 2;
      *(char *)(iVar4 + 0x109) = (char)uVar3;
      *(byte *)(iVar4 + 0x108) =
           *(byte *)(iVar4 + 0x108) & 0xfd | (byte)((uint)((uVar3 << 0x3e) >> 0x3f) << 1);
    }
  }
  return iStack_10;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0058c150  BCurEntry__7BtlMenuFP8BCursole
 * C++: BtlMenu::BCurEntry(BCursole *)
 * size: 0x6c bytes
 * --------------------------------------------------------------------------- */
void BCurEntry__7BtlMenuFP8BCursole(int param_1)

{
  if (iGpffff86fc == 0) {
    *(undefined4 *)(param_1 + 0x48) = 0;
    iGpffff86f8 = param_1;
  }
  else {
    *(int *)(param_1 + 0x48) = iGpffff86fc;
    *(int *)(*(int *)(param_1 + 0x48) + 0x4c) = param_1;
  }
  *(undefined4 *)(param_1 + 0x4c) = 0;
  iGpffff86fc = param_1;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0058c1c0  BCurRelease__7BtlMenuFP8BCursole
 * C++: BtlMenu::BCurRelease(BCursole *)
 * size: 0xa4 bytes
 * --------------------------------------------------------------------------- */
void BCurRelease__7BtlMenuFP8BCursole(int param_1)

{
  if (*(int *)(param_1 + 0x48) == 0) {
    uGpffff86f8 = *(undefined4 *)(param_1 + 0x4c);
  }
  else {
    *(undefined4 *)(*(int *)(param_1 + 0x48) + 0x4c) = *(undefined4 *)(param_1 + 0x4c);
  }
  if (*(int *)(param_1 + 0x4c) == 0) {
    uGpffff86fc = *(undefined4 *)(param_1 + 0x48);
  }
  else {
    *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x48) = *(undefined4 *)(param_1 + 0x48);
  }
  *(undefined4 *)(param_1 + 0x48) = 0;
  *(undefined4 *)(param_1 + 0x4c) = 0;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0058c270  AllBCurDestruct__7BtlMenuFv
 * C++: BtlMenu::AllBCurDestruct()
 * size: 0x5c bytes
 * --------------------------------------------------------------------------- */
void AllBCurDestruct__7BtlMenuFv(void)

{
  int iVar1;
  int iVar2;
  
  iVar2 = iGpffff86f8;
  while (iVar2 != 0) {
    iVar1 = *(int *)(iVar2 + 0x4c);
    Destruct__8BCursoleFv(iVar2);
    iVar2 = iVar1;
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0058c2d0  FindBCursole__7BtlMenuFi
 * C++: BtlMenu::FindBCursole(int)
 * size: 0x60 bytes
 * --------------------------------------------------------------------------- */
int FindBCursole__7BtlMenuFi(int param_1)

{
  int iVar1;
  
  iVar1 = iGpffff86f8;
  while( true ) {
    if (iVar1 == 0) {
      return 0;
    }
    if (*(int *)(iVar1 + 0x50) == param_1) break;
    iVar1 = *(int *)(iVar1 + 0x4c);
  }
  return iVar1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0058c330  __ct__7BtlMenuFib
 * C++: BtlMenu::__ct(int, bool)
 * size: 0x3e8 bytes
 * --------------------------------------------------------------------------- */
int __ct__7BtlMenuFib(int param_1,undefined2 param_2,char param_3)

{
  int iVar1;
  
  __ct__7CPolObjFv(param_1);
  *(undefined4 *)(param_1 + 0x18) = 0;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  *(undefined4 *)(param_1 + 0x20) = 0x4049f0;
  *(undefined4 *)(param_1 + 0x14) = 0x40a810;
  *(undefined4 *)(param_1 + 0x20) = 0x40a820;
  __construct_array(param_1 + 0x30,0x58c7a0,0x58c720,0x16c,6);
  __ct__8FontDrawFv(param_1 + 0x8bc);
  __ct__10MenuWindowFv(param_1 + 0x8fc);
  __ct__8MenuTextFv(param_1 + 0x9b0);
  __ct__6CursorFv(param_1 + 0xa34);
  *(undefined4 *)(param_1 + 0x24) = 0;
  if (param_3 == '\x01') {
    *(byte *)(param_1 + 0x24) = *(byte *)(param_1 + 0x24) & 0xfe | 1;
  }
  *(undefined2 *)(param_1 + 0x28) = param_2;
  *(undefined2 *)(param_1 + 0x2a) = 0;
  for (iVar1 = 0; iVar1 < 6; iVar1 = iVar1 + 1) {
    *(undefined2 *)(param_1 + iVar1 * 0x16c + 0x30) = 0;
    *(undefined2 *)(param_1 + iVar1 * 0x16c + 0x32) = 0;
    *(undefined4 *)(param_1 + iVar1 * 0x16c + 0x130) = 0;
    *(undefined4 *)(param_1 + iVar1 * 0x16c + 0x134) = 0;
    *(undefined4 *)(param_1 + iVar1 * 0x16c + 0x13c) = 0;
    *(undefined4 *)(param_1 + iVar1 * 0x16c + 0x140) = 0;
    *(undefined4 *)(param_1 + iVar1 * 0x16c + 0x138) = 0;
    *(undefined4 *)(param_1 + iVar1 * 0x16c + 0x144) = 0;
    *(undefined4 *)(param_1 + iVar1 * 0x16c + 0x148) = 0;
    *(undefined4 *)(param_1 + iVar1 * 0x16c + 0x14c) = 0;
  }
  *(undefined2 *)(param_1 + 0x8b8) = 0;
  *(undefined2 *)(param_1 + 0x8ba) = 0;
  *(undefined2 *)(param_1 + 0xa30) = 0;
  *(undefined2 *)(param_1 + 0xa32) = 0;
  *(undefined4 *)(param_1 + 0xb30) = 0;
  *(undefined4 *)(param_1 + 0xb34) = 0;
  *(undefined4 *)(param_1 + 0xb38) = 0;
  *(undefined4 *)(param_1 + 0xb3c) = 0;
  *(undefined2 *)(param_1 + 0xb44) = 0xffff;
  *(undefined2 *)(param_1 + 0xb46) = 0;
  *(undefined2 *)(param_1 + 0xb5e) = 0xffff;
  *(undefined2 *)(param_1 + 0xb5c) = 0xffff;
  *(undefined2 *)(param_1 + 0xb5a) = 0xffff;
  *(undefined2 *)(param_1 + 0xb58) = 0xffff;
  if (*(byte *)(*(int *)(g_83f8 + 0xc) + 0x274) >> 6 == 0) {
    *(undefined2 *)(param_1 + 0xb58) =
         *(undefined2 *)
          (iGpffff86b4 +
           (*(char *)(iGpffff86b4 + 0x2c) * 0x50 - (int)*(char *)(iGpffff86b4 + 0x2c)) * 0x10 +
          0x598);
    *(undefined2 *)(param_1 + 0xb5a) =
         *(undefined2 *)
          (iGpffff86b4 +
           (*(char *)(iGpffff86b4 + 0x2c) * 0x50 - (int)*(char *)(iGpffff86b4 + 0x2c)) * 0x10 +
          0x59a);
    *(undefined2 *)(param_1 + 0xb5c) =
         *(undefined2 *)
          (iGpffff86b4 +
           (*(char *)(iGpffff86b4 + 0x2c) * 0x50 - (int)*(char *)(iGpffff86b4 + 0x2c)) * 0x10 +
          0x59c);
    *(undefined2 *)(param_1 + 0xb5e) =
         *(undefined2 *)
          (iGpffff86b4 +
           (*(char *)(iGpffff86b4 + 0x2c) * 0x50 - (int)*(char *)(iGpffff86b4 + 0x2c)) * 0x10 +
          0x59e);
  }
  Entry__7CPollerFP7CPolObjib(iGpffff858c + 0x48,param_1,0x80,0);
  return param_1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0058c7e0  __dt__7BtlMenuFv
 * C++: BtlMenu::__dt()
 * size: 0x4a0 bytes
 * --------------------------------------------------------------------------- */
int __dt__7BtlMenuFv(int param_1,short param_2)

{
  int iVar1;
  int iVar2;
  
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0x14) = 0x40a810;
    *(undefined4 *)(param_1 + 0x20) = 0x40a820;
    for (iVar2 = 0; iVar2 < 6; iVar2 = iVar2 + 1) {
      if ((long)((ulong)*(byte *)(param_1 + iVar2 * 0x16c + 0x30) << 0x3e) < 0) {
        Release__7MenuObjFv(param_1 + iVar2 * 0x16c + 0x3c);
      }
      if ((long)((ulong)*(byte *)(param_1 + iVar2 * 0x16c + 0x30) << 0x3c) < 0) {
        Release__7MenuObjFv(param_1 + iVar2 * 0x16c + 0x7c);
      }
      if (((ulong)*(ushort *)(param_1 + iVar2 * 0x16c + 0x30) & 0xfff) >> 4 != 0) {
        __destroy_new_array(*(undefined4 *)(param_1 + iVar2 * 0x16c + 0x130),0x27c030);
      }
      if (*(int *)(param_1 + iVar2 * 0x16c + 0x134) != 0) {
        __destroy_new_array(*(undefined4 *)(param_1 + iVar2 * 0x16c + 0x134),0x27d4f0);
      }
      if (*(int *)(param_1 + iVar2 * 0x16c + 0x13c) != 0) {
        __destroy_new_array(*(undefined4 *)(param_1 + iVar2 * 0x16c + 0x13c),0x2661a0);
      }
      if (*(int *)(param_1 + iVar2 * 0x16c + 0x140) != 0) {
        iVar1 = *(int *)(param_1 + iVar2 * 0x16c + 0x140);
        if (iVar1 != 0) {
          (**(code **)(*(int *)(iVar1 + 8) + 8))(iVar1,1);
        }
      }
      if (*(int *)(param_1 + iVar2 * 0x16c + 0x138) != 0) {
        __destroy_new_array(*(undefined4 *)(param_1 + iVar2 * 0x16c + 0x138),0x277890);
      }
      if (*(int *)(param_1 + iVar2 * 0x16c + 0x144) != 0) {
        __destroy_new_array(*(undefined4 *)(param_1 + iVar2 * 0x16c + 0x144),0x28d070);
      }
      if (*(int *)(param_1 + iVar2 * 0x16c + 0x148) != 0) {
        __destroy_new_array(*(undefined4 *)(param_1 + iVar2 * 0x16c + 0x148),0x2766d0);
      }
      if (*(int *)(param_1 + iVar2 * 0x16c + 0x14c) != 0) {
        __destroy_new_array(*(undefined4 *)(param_1 + iVar2 * 0x16c + 0x14c),0x280920);
      }
    }
    if ((long)((ulong)*(byte *)(param_1 + 0x24) << 0x39) < 0) {
      Release__7MenuObjFv(param_1 + 0x8bc);
    }
    if ((*(byte *)(param_1 + 0x25) & 1) != 0) {
      Release__7MenuObjFv(param_1 + 0x8fc);
    }
    if ((long)((ulong)*(byte *)(param_1 + 0x24) << 0x3b) < 0) {
      Release__7MenuObjFv(param_1 + 0xa34);
    }
    if (*(int *)(param_1 + 0xb30) != 0) {
      iVar2 = *(int *)(param_1 + 0xb30);
      if (iVar2 != 0) {
        (**(code **)(*(int *)(iVar2 + 8) + 8))(iVar2,1);
      }
    }
    __dt__6CursorFv(param_1 + 0xa34,0xffffffffffffffff);
    __dt__8MenuTextFv(param_1 + 0x9b0,0xffffffffffffffff);
    __dt__10MenuWindowFv(param_1 + 0x8fc,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x8bc,0xffffffffffffffff);
    __destroy_arr(param_1 + 0x30,0x58c720,0x16c,6);
    if (param_1 != -0x18) {
      *(undefined4 *)(param_1 + 0x20) = 0x4049f0;
    }
    __dt__7CPolObjFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0058cc80  Destruct__7BtlMenuFv
 * C++: BtlMenu::Destruct()
 * size: 0x37c bytes
 * --------------------------------------------------------------------------- */
void Destruct__7BtlMenuFv(int param_1)

{
  int iVar1;
  int iVar2;
  
  for (iVar2 = 0; iVar2 < 6; iVar2 = iVar2 + 1) {
    if ((*(byte *)(param_1 + iVar2 * 0x16c + 0x30) & 1) != 0) {
      ReleaseOT__7MenuObjFv(param_1 + iVar2 * 0x16c + 0x3c);
      iVar1 = param_1 + iVar2 * 0x16c;
      *(byte *)(iVar1 + 0x30) = *(byte *)(iVar1 + 0x30) & 0xfe;
    }
    if ((long)((ulong)*(byte *)(param_1 + iVar2 * 0x16c + 0x30) << 0x3d) < 0) {
      ReleaseOT__7MenuObjFv(param_1 + iVar2 * 0x16c + 0x7c);
      iVar1 = param_1 + iVar2 * 0x16c;
      *(byte *)(iVar1 + 0x30) = *(byte *)(iVar1 + 0x30) & 0xfb;
    }
  }
  if ((long)((ulong)*(byte *)(param_1 + 0x24) << 0x3a) < 0) {
    ReleaseOT__7MenuObjFv(param_1 + 0x8bc);
    *(byte *)(param_1 + 0x24) = *(byte *)(param_1 + 0x24) & 0xdf;
  }
  if ((long)((ulong)*(byte *)(param_1 + 0x24) << 0x38) < 0) {
    ReleaseOT__7MenuObjFv(param_1 + 0x8fc);
    *(byte *)(param_1 + 0x24) = *(byte *)(param_1 + 0x24) & 0x7f;
  }
  if ((long)((ulong)*(byte *)(param_1 + 0x24) << 0x3c) < 0) {
    ReleaseOT__7MenuObjFv(param_1 + 0xa34);
    *(byte *)(param_1 + 0x24) = *(byte *)(param_1 + 0x24) & 0xf7;
  }
  if ((long)((ulong)*(byte *)(param_1 + 0x25) << 0x3e) < 0) {
    ReleaseOT__7MenuObjFv(*(undefined4 *)(param_1 + 0xb30));
    *(byte *)(param_1 + 0x25) = *(byte *)(param_1 + 0x25) & 0xfd;
  }
  if (*(int *)(param_1 + 0xb38) != 0) {
    for (iVar2 = *(int *)(iGpffff86b4 + 0x4370);
        (iVar2 != 0 && (iVar2 != *(int *)(param_1 + 0xb38))); iVar2 = *(int *)(iVar2 + 0x3c)) {
    }
    if (iVar2 != 0) {
      (**(code **)(*(int *)(*(int *)(param_1 + 0xb38) + 0x14) + 0x30))();
    }
  }
  *(undefined4 *)(param_1 + 0xb38) = 0;
  if (*(int *)(param_1 + 0xb3c) != 0) {
    for (iVar2 = *(int *)(iGpffff86b4 + *(int *)(*(int *)(param_1 + 0xb3c) + 0x48) * 0x4f0 + 0x54c);
        (iVar2 != 0 && (iVar2 != *(int *)(param_1 + 0xb3c))); iVar2 = *(int *)(iVar2 + 0x3c)) {
    }
    if (iVar2 != 0) {
      (**(code **)(*(int *)(*(int *)(param_1 + 0xb3c) + 0x14) + 0x30))();
    }
  }
  *(undefined4 *)(param_1 + 0xb3c) = 0;
  Dispose__7CPollerFP7CPolObj(iGpffff858c + 0x48,param_1);
  (**(code **)(*(int *)(param_1 + 0x20) + 0xc))();
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0058d000  Polling__7BtlMenuFv
 * C++: BtlMenu::Polling()
 * size: 0x15014 bytes
 * --------------------------------------------------------------------------- */
/* WARNING: Removing unreachable block (ram,0x0058f664) */
/* WARNING: Removing unreachable block (ram,0x00591758) */
/* WARNING: Removing unreachable block (ram,0x0059438c) */
/* WARNING: Removing unreachable block (ram,0x005982cc) */
/* WARNING: Removing unreachable block (ram,0x0059e5a4) */
/* WARNING: Removing unreachable block (ram,0x0059813c) */
/* WARNING: Removing unreachable block (ram,0x00594268) */
/* WARNING: Removing unreachable block (ram,0x005915ac) */
/* WARNING: Removing unreachable block (ram,0x0058f4b8) */
/* WARNING: Removing unreachable block (ram,0x0059b870) */

undefined4 Polling__7BtlMenuFv(int param_1)

{
  ushort uVar1;
  ushort uVar2;
  bool bVar3;
  char cVar4;
  ushort uVar5;
  undefined8 uVar6;
  int iVar7;
  long extraout_t0;
  short sVar8;
  ulong uVar9;
  int iVar10;
  long lVar11;
  uint uVar12;
  short sVar13;
  byte bVar14;
  undefined2 unaff_s0_lo;
  long lVar15;
  bool bVar16;
  ulong uVar17;
  bool bVar18;
  undefined1 auStack_8a0 [256];
  int aiStack_7a0 [22];
  undefined4 uStack_748;
  int iStack_744;
  int iStack_740;
  int iStack_73c;
  int iStack_738;
  int iStack_734;
  int iStack_730;
  int iStack_72c;
  int iStack_728;
  int iStack_724;
  int iStack_720;
  int iStack_71c;
  int iStack_718;
  int iStack_714;
  int iStack_710;
  int iStack_70c;
  int iStack_708;
  int iStack_704;
  int iStack_700;
  int iStack_6fc;
  int iStack_6f8;
  int iStack_6f4;
  int iStack_6f0;
  int iStack_6ec;
  int iStack_6e8;
  int iStack_6e4;
  int iStack_6e0;
  int iStack_6dc;
  int iStack_6d8;
  int iStack_6d4;
  int iStack_6d0;
  int iStack_6cc;
  int iStack_6c8;
  int iStack_6c4;
  int iStack_6c0;
  int iStack_6bc;
  int iStack_6b8;
  int iStack_6b4;
  int iStack_6b0;
  int iStack_6ac;
  int iStack_6a8;
  int iStack_6a4;
  int iStack_6a0;
  int iStack_69c;
  int iStack_698;
  int iStack_694;
  int iStack_690;
  int iStack_68c;
  int iStack_688;
  int iStack_684;
  int iStack_680;
  int iStack_67c;
  int iStack_678;
  int iStack_674;
  int iStack_670;
  int iStack_66c;
  int iStack_668;
  int iStack_664;
  int iStack_660;
  int iStack_65c;
  int iStack_658;
  int iStack_654;
  int iStack_650;
  int iStack_64c;
  int iStack_648;
  int iStack_644;
  int iStack_640;
  int iStack_63c;
  int iStack_638;
  int iStack_634;
  int iStack_630;
  int iStack_62c;
  int iStack_628;
  int iStack_624;
  int iStack_620;
  int iStack_61c;
  int iStack_618;
  int iStack_614;
  int iStack_610;
  int iStack_60c;
  int iStack_608;
  int iStack_604;
  int iStack_600;
  int iStack_5fc;
  int iStack_5f8;
  int iStack_5f4;
  int iStack_5f0;
  int iStack_5ec;
  int iStack_5e8;
  int iStack_5e4;
  int iStack_5e0;
  int iStack_5dc;
  int iStack_5d8;
  int iStack_5d4;
  int iStack_5d0;
  int iStack_5cc;
  int iStack_5c8;
  int iStack_5c4;
  int iStack_5c0;
  int iStack_5bc;
  int iStack_5b8;
  int iStack_5b4;
  int iStack_5b0;
  int iStack_5ac;
  int iStack_5a8;
  int iStack_5a4;
  int iStack_5a0;
  int iStack_59c;
  int iStack_598;
  int iStack_594;
  int iStack_590;
  int iStack_58c;
  int iStack_588;
  int iStack_584;
  int iStack_580;
  int iStack_57c;
  int iStack_578;
  int iStack_574;
  int iStack_570;
  int iStack_56c;
  int iStack_568;
  int iStack_564;
  int iStack_560;
  int iStack_55c;
  int iStack_558;
  int iStack_554;
  int iStack_550;
  int iStack_54c;
  int iStack_548;
  int iStack_544;
  int iStack_540;
  int iStack_53c;
  int iStack_538;
  int iStack_534;
  int iStack_530;
  int iStack_52c;
  int iStack_528;
  int iStack_524;
  undefined *puStack_520;
  int iStack_51c;
  int iStack_518;
  int iStack_514;
  int iStack_510;
  int iStack_50c;
  int iStack_508;
  undefined *puStack_504;
  int iStack_500;
  int iStack_4fc;
  int iStack_4f8;
  int iStack_4f4;
  int iStack_4f0;
  int iStack_4ec;
  int iStack_4e8;
  undefined *puStack_4e4;
  int iStack_4e0;
  int iStack_4dc;
  int iStack_4d8;
  int iStack_4d4;
  int iStack_4d0;
  int iStack_4cc;
  int iStack_4c8;
  undefined *puStack_4c4;
  undefined *puStack_4c0;
  int iStack_4bc;
  int iStack_4b8;
  int iStack_4b4;
  int iStack_4b0;
  int iStack_4ac;
  int iStack_4a8;
  int iStack_4a4;
  int iStack_4a0;
  int iStack_49c;
  int iStack_498;
  int iStack_494;
  int iStack_490;
  int iStack_48c;
  undefined *puStack_488;
  int iStack_484;
  int iStack_480;
  int iStack_47c;
  int iStack_478;
  int iStack_474;
  int iStack_470;
  undefined *puStack_46c;
  int iStack_468;
  int iStack_464;
  int iStack_460;
  int iStack_45c;
  int iStack_458;
  int iStack_454;
  int iStack_450;
  undefined *puStack_44c;
  undefined *puStack_448;
  int iStack_444;
  int iStack_440;
  int iStack_43c;
  int iStack_438;
  int iStack_434;
  int iStack_430;
  int iStack_42c;
  int iStack_428;
  int iStack_424;
  int iStack_420;
  int iStack_41c;
  int iStack_418;
  int iStack_414;
  int iStack_410;
  int iStack_40c;
  int iStack_408;
  int iStack_404;
  int iStack_400;
  int iStack_3fc;
  int iStack_3f8;
  undefined *puStack_3f4;
  undefined *puStack_3f0;
  int iStack_3ec;
  int iStack_3e8;
  int iStack_3e4;
  int iStack_3e0;
  int iStack_3dc;
  int iStack_3d8;
  int iStack_3d4;
  int iStack_3d0;
  int iStack_3cc;
  int iStack_3c8;
  int iStack_3c4;
  undefined *puStack_3c0;
  int iStack_3bc;
  int iStack_3b8;
  int iStack_3b4;
  int iStack_3b0;
  int iStack_3ac;
  int iStack_3a8;
  int iStack_3a4;
  int iStack_3a0;
  int iStack_39c;
  int iStack_398;
  int iStack_394;
  int iStack_390;
  undefined *puStack_38c;
  int iStack_388;
  int iStack_384;
  int iStack_380;
  int iStack_37c;
  int iStack_378;
  int iStack_374;
  undefined *puStack_370;
  undefined *puStack_36c;
  int iStack_368;
  int iStack_364;
  int iStack_360;
  int iStack_35c;
  int iStack_358;
  int iStack_354;
  int iStack_350;
  undefined *puStack_34c;
  int iStack_348;
  int iStack_344;
  int iStack_340;
  int iStack_33c;
  int iStack_338;
  int iStack_334;
  undefined *puStack_330;
  undefined *puStack_32c;
  int iStack_328;
  int iStack_324;
  int iStack_320;
  int iStack_31c;
  int iStack_318;
  int iStack_314;
  int iStack_310;
  undefined *puStack_30c;
  int iStack_308;
  int iStack_304;
  int iStack_300;
  int iStack_2fc;
  int iStack_2f8;
  int iStack_2f4;
  int iStack_2f0;
  int iStack_2ec;
  int iStack_2e8;
  int iStack_2e4;
  int iStack_2e0;
  undefined4 uStack_2dc;
  undefined1 *puStack_2d8;
  undefined1 *puStack_2d4;
  int iStack_2d0;
  int iStack_2cc;
  int iStack_2c8;
  uint uStack_2c4;
  undefined4 uStack_2c0;
  undefined4 uStack_2bc;
  undefined4 uStack_2b8;
  int iStack_2b4;
  int iStack_2b0;
  int iStack_2ac;
  int iStack_2a8;
  int iStack_2a4;
  int iStack_2a0;
  int iStack_29c;
  int iStack_298;
  int iStack_294;
  int iStack_290;
  int iStack_28c;
  int iStack_288;
  int iStack_284;
  int iStack_280;
  int iStack_27c;
  int iStack_278;
  int iStack_274;
  int iStack_270;
  int iStack_26c;
  int iStack_268;
  int iStack_264;
  int iStack_260;
  int iStack_25c;
  int iStack_258;
  int iStack_254;
  int iStack_250;
  int iStack_24c;
  int iStack_248;
  int iStack_244;
  int iStack_240;
  int iStack_23c;
  int iStack_238;
  int iStack_234;
  int iStack_230;
  int iStack_22c;
  int iStack_228;
  short sStack_222;
  short sStack_220;
  short sStack_21e;
  short sStack_21c;
  short sStack_21a;
  short sStack_218;
  short sStack_216;
  short sStack_214;
  short sStack_212;
  short sStack_210;
  short sStack_20e;
  short sStack_20c;
  short sStack_20a;
  short sStack_208;
  short sStack_206;
  short sStack_204;
  short sStack_202;
  short sStack_200;
  short sStack_1fe;
  short sStack_1fc;
  short sStack_1fa;
  short sStack_1f8;
  short sStack_1f6;
  short sStack_1f4;
  short sStack_1f2;
  short sStack_1f0;
  short sStack_1ee;
  short sStack_1ec;
  short sStack_1ea;
  short sStack_1e8;
  short sStack_1e6;
  short sStack_1e4;
  short sStack_1e2;
  short sStack_1e0;
  short sStack_1de;
  short sStack_1dc;
  short sStack_1da;
  short sStack_1d8;
  short sStack_1d6;
  short sStack_1d4;
  short sStack_1d2;
  short sStack_1d0;
  short sStack_1ce;
  short sStack_1cc;
  short sStack_1ca;
  short sStack_1c8;
  short sStack_1c6;
  short sStack_1c4;
  short sStack_1c2;
  short sStack_1c0;
  short sStack_1be;
  short sStack_1bc;
  short sStack_1ba;
  short sStack_1b8;
  short sStack_1b6;
  short sStack_1b4;
  short sStack_1b2;
  short sStack_1b0;
  short sStack_1ae;
  short sStack_1ac;
  short sStack_1aa;
  short sStack_1a8;
  short sStack_1a6;
  short sStack_1a4;
  short sStack_1a2;
  short sStack_1a0;
  short sStack_19e;
  short sStack_19c;
  short sStack_19a;
  short sStack_198;
  short sStack_196;
  short sStack_194;
  short sStack_192;
  short sStack_190;
  short sStack_18e;
  short sStack_18c;
  short sStack_18a;
  short sStack_188;
  short sStack_186;
  short sStack_184;
  short sStack_182;
  short sStack_180;
  short sStack_17e;
  short sStack_17c;
  short sStack_17a;
  short sStack_178;
  short sStack_176;
  short sStack_174;
  short sStack_172;
  short sStack_170;
  short sStack_16e;
  short sStack_16c;
  short sStack_16a;
  short sStack_168;
  short sStack_166;
  short sStack_164;
  short sStack_162;
  short sStack_160;
  short sStack_15e;
  short sStack_15c;
  short sStack_15a;
  short sStack_158;
  undefined2 uStack_156;
  undefined2 uStack_154;
  short sStack_152;
  short sStack_150;
  short sStack_14e;
  short sStack_14c;
  short sStack_14a;
  short sStack_148;
  short sStack_146;
  short sStack_144;
  short sStack_142;
  short sStack_140;
  short sStack_13e;
  short sStack_13c;
  short sStack_13a;
  short sStack_138;
  undefined2 uStack_136;
  undefined2 uStack_134;
  short sStack_132;
  short sStack_130;
  short sStack_12e;
  short sStack_12c;
  short sStack_12a;
  short sStack_128;
  short sStack_126;
  short sStack_124;
  short sStack_122;
  short sStack_120;
  short sStack_11e;
  short sStack_11c;
  short sStack_11a;
  short sStack_118;
  short sStack_116;
  short sStack_114;
  short sStack_112;
  short sStack_110;
  short sStack_10e;
  short sStack_10c;
  short sStack_10a;
  short sStack_108;
  undefined2 uStack_106;
  undefined2 uStack_104;
  short sStack_102;
  short sStack_100;
  short sStack_fe;
  short sStack_fc;
  short sStack_fa;
  short sStack_f8;
  short sStack_f6;
  short sStack_f4;
  short sStack_f2;
  short sStack_f0;
  short sStack_ee;
  short sStack_ec;
  undefined2 uStack_ea;
  undefined2 uStack_e8;
  short sStack_e6;
  short sStack_e4;
  short sStack_e2;
  short sStack_e0;
  short sStack_de;
  short sStack_dc;
  short sStack_da;
  short sStack_d8;
  short sStack_d6;
  short sStack_d4;
  short sStack_d2;
  short sStack_d0;
  short sStack_ce;
  short sStack_cc;
  short sStack_ca;
  short sStack_c8;
  short sStack_c6;
  short sStack_c4;
  short sStack_c2;
  short sStack_c0;
  short sStack_be;
  short sStack_bc;
  short sStack_ba;
  short sStack_b8;
  short sStack_b6;
  short sStack_b4;
  short sStack_b2;
  short sStack_b0;
  short sStack_ae;
  short sStack_ac;
  short sStack_aa;
  short sStack_a8;
  short sStack_a6;
  short sStack_a4;
  short sStack_a2;
  short sStack_a0;
  short sStack_9e;
  short sStack_9c;
  short sStack_9a;
  short sStack_98;
  short sStack_96;
  short sStack_94;
  short sStack_92;
  short sStack_90;
  short sStack_8e;
  short sStack_8c;
  short sStack_8a;
  short sStack_88;
  short sStack_86;
  short sStack_84;
  short sStack_82;
  short sStack_80;
  short sStack_7e;
  short sStack_7c;
  short sStack_7a;
  short sStack_78;
  short sStack_76;
  short sStack_74;
  short sStack_72;
  short sStack_70;
  short sStack_6e;
  short sStack_6c;
  short sStack_6a;
  short sStack_68;
  short sStack_66;
  short sStack_64;
  short sStack_62;
  short sStack_60;
  short sStack_5e;
  short sStack_5c;
  short sStack_5a;
  short sStack_58;
  short sStack_56;
  short sStack_54;
  short sStack_52;
  short sStack_50;
  short sStack_4e;
  short sStack_4c;
  short sStack_4a;
  short sStack_48;
  short sStack_46;
  short sStack_44;
  short sStack_42;
  short sStack_40;
  short sStack_3e;
  short sStack_3c;
  short sStack_3a;
  short sStack_38;
  short sStack_36;
  short sStack_34;
  short sStack_32;
  short sStack_30;
  short sStack_2e;
  short sStack_2c;
  short sStack_2a;
  short sStack_28;
  undefined2 uStack_26;
  undefined2 uStack_24;
  undefined2 uStack_22;
  undefined2 uStack_20;
  undefined2 uStack_1e;
  undefined2 uStack_1c;
  ushort uStack_1a;
  ushort uStack_18;
  ushort uStack_16;
  ushort uStack_14;
  undefined1 uStack_11;
  int iStack_10;
  
  iStack_10 = param_1;
  WinSequence__7BtlMenuFv(param_1);
  iStack_2e4 = g_86c0;
  uVar1 = *(ushort *)(*(int *)(*(int *)(g_86c0 + 4) * 4 + 0x40ac00) + 0x6c);
  iStack_2e0 = g_86c0;
  uVar2 = *(ushort *)(*(int *)(*(int *)(g_86c0 + 4) * 4 + 0x40ac00) + 0x70);
  uVar5 = uVar2 & 0xff0 | uVar1 & 0xf00f;
  uStack_1a = uVar2;
  uStack_18 = uVar2;
  uStack_16 = uVar1;
  uStack_14 = uVar1;
  switch(*(undefined2 *)(iStack_10 + 0x28)) {
  case 0:
    cVar4 = MainMenuFunc__7BtlMenuFv(iStack_10);
    if (cVar4 == '\0') {
      return 0;
    }
    break;
  case 1:
    iStack_238 = GetRegDat__9RegDatApiFiii(0x3e,0,0xffffffffffffffff);
    sVar8 = *(short *)(iStack_10 + 0x2a);
    if (sVar8 == 2) {
      *(undefined2 *)(iStack_10 + 0x28) = 0;
      *(undefined2 *)(iStack_10 + 0x2a) = 0;
      AllBCurDestruct__7BtlMenuFv();
    }
    else if (sVar8 == 1) {
      if (((*(short *)(iStack_10 + 0x19e) == 1) || (*(short *)(iStack_10 + 0x19e) == 2)) ||
         (*(short *)(iStack_10 + 0x19e) == 5)) {
        if (*(short *)(iStack_10 + 0xb44) == 1) {
          if (*(short *)(iStack_10 + 0xb46) == 3) {
            uVar5 = 0;
            *(float *)(iStack_10 + 0xb48) = *(float *)(iStack_10 + 0xb48) - pCGpffff86b4->flDeltaT;
            if (*(float *)(iStack_10 + 0xb48) <= 0.0) {
              *(undefined4 *)(iStack_10 + 0xb48) = 0x3e800000;
              iVar7 = -1;
              iStack_228 = 0;
              for (iVar10 = 0; iVar10 < 0xc; iVar10 = iVar10 + 1) {
                if ((((((pCGpffff86b4->aChr[iVar10].bFlagsA & 1) != 0) &&
                      ((long)((ulong)pCGpffff86b4->aChr[iVar10].bFlagsA << 0x3e) < 0)) &&
                     (-1 < (long)((ulong)pCGpffff86b4->aChr[iVar10].bFlagsA2 << 0x3d))) &&
                    ((0 < pCGpffff86b4->aChr[iVar10].nHp &&
                     ((pCGpffff86b4->aChr[iVar10].bFlagsB & 1) != 0)))) &&
                   ((long)iStack_228 < (long)pCGpffff86b4->aChr[iVar10].nHp)) {
                  iStack_228 = (int)pCGpffff86b4->aChr[iVar10].nHp;
                  iVar7 = iVar10;
                }
              }
              iStack_544 = *(int *)(iStack_10 + 0xb20);
              uStack_1e = *(undefined2 *)(iStack_544 + 0x1e);
              iStack_2e8 = iStack_544;
              uStack_1c = uStack_1e;
              uVar5 = AutoMenuFunc__7BtlMenuFiiiii(iStack_10,1,0,uStack_1e,iVar7,0xffffffffffffffff)
              ;
              if ((uVar5 & 0x2000) == 0) {
                *(byte *)(iStack_10 + 0x25) = *(byte *)(iStack_10 + 0x25) & 0xfb;
              }
              else if ((long)((ulong)*(byte *)(iStack_10 + 0x25) << 0x3d) < 0) {
                *(undefined2 *)(iStack_10 + 0xb46) = 4;
                *(undefined4 *)(iStack_10 + 0xb48) = 0x3f800000;
              }
              else {
                uVar5 = 0;
                *(undefined4 *)(iStack_10 + 0xb48) = 0x3f400000;
                *(byte *)(iStack_10 + 0x25) = *(byte *)(iStack_10 + 0x25) & 0xfb | 4;
              }
            }
          }
        }
        else if (*(short *)(iStack_10 + 0xb44) == 6) {
          if (*(short *)(iStack_10 + 0xb46) == 2) {
            uVar5 = 0;
            *(float *)(iStack_10 + 0xb48) = *(float *)(iStack_10 + 0xb48) - pCGpffff86b4->flDeltaT;
            if (*(float *)(iStack_10 + 0xb48) <= 0.0) {
              *(undefined4 *)(iStack_10 + 0xb48) = 0x3e800000;
              iVar7 = -1;
              iStack_228 = 0;
              for (iVar10 = 0; iVar10 < 0xc; iVar10 = iVar10 + 1) {
                if ((((pCGpffff86b4->aChr[iVar10].bFlagsA & 1) != 0) &&
                    ((long)((ulong)pCGpffff86b4->aChr[iVar10].bFlagsA << 0x3e) < 0)) &&
                   (((-1 < (long)((ulong)pCGpffff86b4->aChr[iVar10].bFlagsA2 << 0x3d) &&
                     ((0 < pCGpffff86b4->aChr[iVar10].nHp &&
                      ((pCGpffff86b4->aChr[iVar10].bFlagsB & 1) != 0)))) &&
                    ((long)iStack_228 < (long)pCGpffff86b4->aChr[iVar10].nHp)))) {
                  iStack_228 = (int)pCGpffff86b4->aChr[iVar10].nHp;
                  iVar7 = iVar10;
                }
              }
              iStack_548 = *(int *)(iStack_10 + 0xb20);
              uStack_22 = *(undefined2 *)(iStack_548 + 0x1e);
              iStack_2ec = iStack_548;
              uStack_20 = uStack_22;
              uVar5 = AutoMenuFunc__7BtlMenuFiiiii(iStack_10,1,0,uStack_22,iVar7,0xffffffffffffffff)
              ;
              if ((uVar5 & 0x2000) == 0) {
                *(byte *)(iStack_10 + 0x25) = *(byte *)(iStack_10 + 0x25) & 0xfb;
              }
              else if ((long)((ulong)*(byte *)(iStack_10 + 0x25) << 0x3d) < 0) {
                *(undefined2 *)(iStack_10 + 0xb46) = 3;
                *(undefined4 *)(iStack_10 + 0xb48) = 0x3f800000;
              }
              else {
                uVar5 = 0;
                *(undefined4 *)(iStack_10 + 0xb48) = 0x3f400000;
                *(byte *)(iStack_10 + 0x25) = *(byte *)(iStack_10 + 0x25) & 0xfb | 4;
              }
            }
          }
        }
        else if (*(short *)(iStack_10 + 0xb44) == 0x18) {
          if (*(short *)(iStack_10 + 0xb46) == 3) {
            uVar5 = 0;
            *(float *)(iStack_10 + 0xb48) = *(float *)(iStack_10 + 0xb48) - pCGpffff86b4->flDeltaT;
            if (*(float *)(iStack_10 + 0xb48) <= 0.0) {
              *(undefined4 *)(iStack_10 + 0xb48) = 0x3e800000;
              iVar7 = -1;
              iStack_228 = 0;
              for (iVar10 = 0; iVar10 < 0xc; iVar10 = iVar10 + 1) {
                if ((((pCGpffff86b4->aChr[iVar10].bFlagsA & 1) != 0) &&
                    ((long)((ulong)pCGpffff86b4->aChr[iVar10].bFlagsA << 0x3e) < 0)) &&
                   ((-1 < (long)((ulong)pCGpffff86b4->aChr[iVar10].bFlagsA2 << 0x3d) &&
                    (((0 < pCGpffff86b4->aChr[iVar10].nHp &&
                      ((pCGpffff86b4->aChr[iVar10].bFlagsB & 1) != 0)) &&
                     ((long)iStack_228 < (long)pCGpffff86b4->aChr[iVar10].nHp)))))) {
                  iStack_228 = (int)pCGpffff86b4->aChr[iVar10].nHp;
                  iVar7 = iVar10;
                }
              }
              iStack_54c = *(int *)(iStack_10 + 0xb20);
              uStack_26 = *(undefined2 *)(iStack_54c + 0x1e);
              iStack_2f0 = iStack_54c;
              uStack_24 = uStack_26;
              uVar5 = AutoMenuFunc__7BtlMenuFiiiii(iStack_10,1,0,uStack_26,iVar7,0xffffffffffffffff)
              ;
              if ((uVar5 & 0x2000) == 0) {
                *(byte *)(iStack_10 + 0x25) = *(byte *)(iStack_10 + 0x25) & 0xfb;
              }
              else if ((long)((ulong)*(byte *)(iStack_10 + 0x25) << 0x3d) < 0) {
                *(undefined2 *)(iStack_10 + 0xb46) = 4;
                *(undefined4 *)(iStack_10 + 0xb48) = 0x3f800000;
              }
              else {
                uVar5 = 0;
                *(undefined4 *)(iStack_10 + 0xb48) = 0x3f400000;
                *(byte *)(iStack_10 + 0x25) = *(byte *)(iStack_10 + 0x25) & 0xfb | 4;
              }
            }
          }
        }
        else if ((*(short *)(iStack_10 + 0xb44) == 0x1d) && (*(short *)(iStack_10 + 0xb46) == 3)) {
          uVar5 = 0;
          *(float *)(iStack_10 + 0xb48) = *(float *)(iStack_10 + 0xb48) - pCGpffff86b4->flDeltaT;
          if (*(float *)(iStack_10 + 0xb48) <= 0.0) {
            uVar5 = 0x2000;
            *(undefined2 *)(iStack_10 + 0xb46) = 4;
          }
        }
        if ((long)((ulong)*(byte *)(iStack_10 + 0x24) << 0x3d) < 0) {
          sVar8 = (short)*(undefined4 *)(iStack_10 + 0x2d4);
          if (999 < sVar8) {
            sVar8 = sVar8 + -1000;
          }
          if (sVar8 == 100) {
            sVar8 = -1;
          }
          DelaySelectFunc__7BtlMenuFiiiP12EFCTCOMParam(iStack_10,sVar8,0,0,0);
          *(byte *)(iStack_10 + 0x24) = *(byte *)(iStack_10 + 0x24) & 0xfb;
        }
        iStack_550 = *(int *)(iStack_10 + 0xb20);
        sVar8 = *(short *)(iStack_550 + 0x16);
        bVar18 = false;
        iVar7 = 0;
        iStack_2f4 = iStack_550;
        sStack_2a = sVar8;
        sStack_28 = sVar8;
        if ((uVar5 & 0x10) != 0) {
          bVar18 = true;
          iStack_554 = *(int *)(iStack_10 + 0xb20);
          sStack_2e = *(short *)(iStack_554 + 0x1e);
          iStack_2f8 = iStack_554;
          sStack_2c = sStack_2e;
          if (sStack_2e < 1) {
            iVar7 = 1;
          }
          else {
            MoveCursor__6CursorFi(iStack_10 + 0xa34,1);
            *(int *)(iStack_10 + 0x2d8) = *(int *)(iStack_10 + 0x2d8) + -1;
            iStack_558 = *(int *)(iStack_10 + 0xb20);
            sStack_32 = *(short *)(iStack_558 + 0x16);
            *(int *)(iStack_10 + 0x2d4) = (int)sStack_32;
            iStack_2fc = iStack_558;
            sStack_30 = sStack_32;
          }
        }
        if ((uVar5 & 0x40) != 0) {
          bVar18 = true;
          iStack_55c = *(int *)(iStack_10 + 0xb20);
          sStack_36 = *(short *)(iStack_55c + 0x1e);
          iStack_300 = iStack_55c;
          sStack_34 = sStack_36;
          if ((sStack_36 + 1 < 4) && (*(int *)(iStack_10 + 0x2d8) + 1 < *(int *)(iStack_10 + 0x2dc))
             ) {
            MoveCursor__6CursorFi(iStack_10 + 0xa34,2);
            *(int *)(iStack_10 + 0x2d8) = *(int *)(iStack_10 + 0x2d8) + 1;
            iStack_560 = *(int *)(iStack_10 + 0xb20);
            sStack_3a = *(short *)(iStack_560 + 0x16);
            *(int *)(iStack_10 + 0x2d4) = (int)sStack_3a;
            iStack_304 = iStack_560;
            sStack_38 = sStack_3a;
          }
          else {
            iVar7 = 2;
          }
        }
        bVar3 = false;
        if (((uVar5 & 0x500) != 0) && (0 < *(int *)(iStack_10 + 0x2d8))) {
          bVar3 = true;
          iVar7 = *(int *)(iStack_10 + 0x2d8) + -4;
          if (iVar7 < 0) {
            iVar7 = 0;
          }
          *(int *)(iStack_10 + 0x2d8) = iVar7;
          if (iVar7 < 0) {
            iVar7 = iVar7 + 3;
          }
          *(int *)(iStack_10 + 0x2e0) = iVar7 >> 2;
          iVar7 = 3;
        }
        bVar16 = false;
        if (((uVar5 & 0xa00) != 0) &&
           (*(int *)(iStack_10 + 0x2d8) + 1 < *(int *)(iStack_10 + 0x2dc))) {
          bVar16 = true;
          iVar7 = *(int *)(iStack_10 + 0x2d8) + 4;
          if (*(int *)(iStack_10 + 0x2dc) <= iVar7) {
            iVar7 = *(int *)(iStack_10 + 0x2dc) + -1;
          }
          *(int *)(iStack_10 + 0x2d8) = iVar7;
          if (iVar7 < 0) {
            iVar7 = iVar7 + 3;
          }
          *(int *)(iStack_10 + 0x2e0) = iVar7 >> 2;
          iVar7 = 3;
        }
        if (iVar7 != 0) {
          if (iVar7 == 1) {
            *(int *)(iStack_10 + 0x2d8) = *(int *)(iStack_10 + 0x2d8) + -1;
            *(int *)(iStack_10 + 0x2e0) = *(int *)(iStack_10 + 0x2e0) + -1;
            if (*(int *)(iStack_10 + 0x2e0) < 0) {
              *(int *)(iStack_10 + 0x2d8) = *(int *)(iStack_10 + 0x2dc) + -1;
              iVar7 = *(int *)(iStack_10 + 0x2dc);
              if (iVar7 < 0) {
                iVar7 = iVar7 + 3;
              }
              *(int *)(iStack_10 + 0x2e0) = iVar7 >> 2;
            }
          }
          else if (iVar7 == 2) {
            *(int *)(iStack_10 + 0x2d8) = *(int *)(iStack_10 + 0x2d8) + 1;
            *(int *)(iStack_10 + 0x2e0) = *(int *)(iStack_10 + 0x2e0) + 1;
            if (*(int *)(iStack_10 + 0x2dc) <= *(int *)(iStack_10 + 0x2d8)) {
              *(undefined4 *)(iStack_10 + 0x2d8) = 0;
              *(undefined4 *)(iStack_10 + 0x2e0) = 0;
            }
          }
          SetTargetMenu__7BtlMenuFiiiP12EFCTCOMParamii
                    (iStack_10,1,0,0,0,*(undefined4 *)(iStack_10 + 0x2d8),0xffffffffffffffff);
          Select__6CursorFP9MenuPlace(iStack_10 + 0xa34,
                          *(int *)(iStack_10 + 0x29c) + *(int *)(iStack_10 + 0x2c4) * 0x80);
        }
        iStack_564 = *(int *)(iStack_10 + 0xb20);
        sVar13 = *(short *)(iStack_564 + 0x16);
        iStack_308 = iStack_564;
        sStack_3e = sVar13;
        sStack_3c = sVar13;
        if (sVar8 != sVar13) {
          uVar12 = *(uint *)(iStack_10 + 0x2d8) & 3;
          if (((int)*(uint *)(iStack_10 + 0x2d8) < 0) && (uVar12 != 0)) {
            uVar12 = uVar12 - 4;
          }
          *(uint *)(iStack_10 + 0x2c4) = uVar12;
          *(undefined4 *)(iStack_10 + 0x2d0) = *(undefined4 *)(iStack_10 + 0x2d4);
          if (bVar18) {
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,0,1,0);
          }
          else if (bVar3) {
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,7,1,0);
          }
          else if (bVar16) {
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,6,1,0);
          }
        }
        if ((sVar8 != sVar13) || (-1 < (long)((ulong)*(byte *)(iStack_10 + 0x24) << 0x3e))) {
          sVar8 = (short)*(undefined4 *)(iStack_10 + 0x2d4);
          if (999 < sVar8) {
            sVar8 = sVar8 + -1000;
          }
          if (sVar8 == 100) {
            sVar8 = -1;
          }
          SelectFunc__7BtlMenuFiiiP12EFCTCOMParam(iStack_10,sVar8,0,0,0);
          iStack_22c = 1;
          aiStack_7a0[0] = *(int *)(iStack_10 + 0x2d4);
          if (((*(byte *)((int)pCGpffff86b4 +
                         (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb4) &
               1) == 0) &&
             (-1 < *(char *)(ourBtlSaveDat +
                             *(short *)((int)pCGpffff86b4 +
                                       (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) *
                                       0x10 + 0x120) * 0xc0 + 0xa8))) {
            MakeTurnOrderTable__7CBattleFfiPiiiPUisibi
                      (pCGpffff86b4,3.0,1,aiStack_7a0,0,0,
                       (uint *)(iStack_238 +
                                *(char *)(ourBtlSaveDat +
                                          *(short *)((int)pCGpffff86b4 +
                                                    (pCGpffff86b4->cActor * 0x50 -
                                                    (int)pCGpffff86b4->cActor) * 0x10 + 0x120) *
                                          0xc0 + 0xa8) * 0x20 + 4),(short)pCGpffff86b4->cActor,-1,
                       true,-2);
          }
          else {
            MakeTurnOrderTable__7CBattleFfiPiiiPUisibi
                      (pCGpffff86b4,3.0,1,aiStack_7a0,0,0,(uint *)0x0,(short)pCGpffff86b4->cActor,-1
                       ,true,-2);
          }
          *(byte *)(iStack_10 + 0x24) = *(byte *)(iStack_10 + 0x24) & 0xfd | 2;
          *(byte *)(iStack_10 + 0x24) = *(byte *)(iStack_10 + 0x24) & 0xfb | 4;
        }
        if ((uVar5 & 0x2000) != 0) {
          if (*(int *)(iStack_10 + 0x2d0) < 1000) {
            sVar8 = (short)*(undefined4 *)(iStack_10 + 0x2d4);
            if (sVar8 == 100) {
              sVar8 = -1;
            }
            *(undefined2 *)
             ((int)pCGpffff86b4 +
             (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x598) =
                 *(undefined2 *)(iStack_10 + 0xb58);
            *(short *)((int)pCGpffff86b4 +
                      (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x59a) =
                 (short)*(undefined4 *)(iStack_10 + 0x2d0);
            *(undefined2 *)
             ((int)pCGpffff86b4 +
             (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x59c) = 0xffff;
            *(undefined2 *)
             ((int)pCGpffff86b4 +
             (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x59e) = 0xffff;
            if (pcGpffff86ec != (code *)0x0) {
              (*pcGpffff86ec)(0x12,0,0xffffffffffffffff,0,0,0,uGpffff86e8);
            }
            if (pcGpffff86ec != (code *)0x0) {
              (*pcGpffff86ec)(4,sVar8,*(int *)(iStack_10 + 0x164) + -1,1,0xffffffffffffffff,0,
                              uGpffff86e8);
            }
            if (*(int *)(iStack_10 + 0xb38) != 0) {
              (**(code **)(*(int *)(*(int *)(iStack_10 + 0xb38) + 0x14) + 0x30))();
            }
            *(undefined4 *)(iStack_10 + 0xb38) = 0;
            AllWindowClose__7BtlMenuFv(iStack_10);
            AllBCurDestruct__7BtlMenuFv();
            *(undefined2 *)(iStack_10 + 0x28) = 0x14;
            *(undefined2 *)(iStack_10 + 0x2a) = 0;
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,2,1,0);
            return 0;
          }
          PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,4,1,0);
        }
        if ((uVar5 & 0x4000) != 0) {
          *(undefined2 *)(iStack_10 + 0x2a) = 2;
          puStack_30c = pCGpffff86b4->pTurnOrderDisp;
          *(undefined4 *)(puStack_30c + 100) = 0;
          if (pcGpffff86ec != (code *)0x0) {
            (*pcGpffff86ec)(0x12,0,0xffffffffffffffff,0,0,0,uGpffff86e8);
          }
          if (*(int *)(iStack_10 + 0xb38) != 0) {
            (**(code **)(*(int *)(*(int *)(iStack_10 + 0xb38) + 0x14) + 0x30))();
          }
          *(undefined4 *)(iStack_10 + 0xb38) = 0;
          if (pcGpffff86ec != (code *)0x0) {
            (*pcGpffff86ec)(3,0,0,0,0,0,uGpffff86e8);
          }
          PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,3,1,0);
        }
      }
    }
    else if (((sVar8 == 0) && (*(short *)(iStack_10 + 0x19e) != 0xc)) &&
            (*(short *)(iStack_10 + 0x19e) != 0xd)) {
      *(byte *)(iStack_10 + 0x25) = *(byte *)(iStack_10 + 0x25) & 0xf7 | 8;
      SetWindowMove__7BtlMenuFii(iStack_10,0,1);
      if (*(int *)(iStack_10 + 0x140) != 0) {
        SetMark__10ScrollMarkFUc(*(undefined4 *)(iStack_10 + 0x140),0);
      }
      SetTargetMenu__7BtlMenuFiiiP12EFCTCOMParamii
                (iStack_10,1,0,0,0,0xffffffffffffffff,*(undefined2 *)(iStack_10 + 0xb5a));
      SetWindowClose__7BtlMenuFii(iStack_10,2,6);
      CreateCursole__7BtlMenuFv(iStack_10);
      Select__6CursorFP9MenuPlace(iStack_10 + 0xa34,
                      *(int *)(iStack_10 + 0x29c) + *(int *)(iStack_10 + 0x2c4) * 0x80);
      QuickMove__6CursorFv(iStack_10 + 0xa34);
      SetNoteWindow__7BtlMenuFPc(iStack_10,uRam0040af44);
      AllBCurDestruct__7BtlMenuFv();
      *(undefined2 *)(iStack_10 + 0x2a) = 1;
      *(byte *)(iStack_10 + 0x24) = *(byte *)(iStack_10 + 0x24) & 0xfd;
      *(byte *)(iStack_10 + 0x24) = *(byte *)(iStack_10 + 0x24) & 0xfb;
    }
    break;
  case 2:
    iStack_23c = GetRegDat__9RegDatApiFiii(0x38,0,0xffffffffffffffff);
    if (*(short *)(iStack_10 + 0x2a) == 1) {
      if (((*(short *)(iStack_10 + 0x19e) == 1) || (*(short *)(iStack_10 + 0x19e) == 2)) ||
         (*(short *)(iStack_10 + 0x19e) == 5)) {
        iStack_568 = *(int *)(iStack_10 + 0xb20);
        sVar8 = *(short *)(iStack_568 + 0x16);
        bVar18 = false;
        lVar15 = 0;
        iStack_310 = iStack_568;
        sStack_42 = sVar8;
        sStack_40 = sVar8;
        if ((uVar2 & 0x10) != 0) {
          bVar18 = true;
          iStack_56c = *(int *)(iStack_10 + 0xb20);
          sStack_46 = *(short *)(iStack_56c + 0x1e);
          iStack_314 = iStack_56c;
          sStack_44 = sStack_46;
          if (sStack_46 < 1) {
            lVar15 = 1;
          }
          else {
            MoveCursor__6CursorFi(iStack_10 + 0xa34,1);
            *(int *)(iStack_10 + 0x2d8) = *(int *)(iStack_10 + 0x2d8) + -1;
            iStack_570 = *(int *)(iStack_10 + 0xb20);
            sStack_4a = *(short *)(iStack_570 + 0x16);
            *(int *)(iStack_10 + 0x2d4) = (int)sStack_4a;
            iStack_318 = iStack_570;
            sStack_48 = sStack_4a;
          }
        }
        if ((uVar2 & 0x40) != 0) {
          bVar18 = true;
          iStack_574 = *(int *)(iStack_10 + 0xb20);
          sStack_4e = *(short *)(iStack_574 + 0x1e);
          iStack_31c = iStack_574;
          sStack_4c = sStack_4e;
          if ((sStack_4e + 1 < 4) && (*(int *)(iStack_10 + 0x2d8) + 1 < *(int *)(iStack_10 + 0x2dc))
             ) {
            MoveCursor__6CursorFi(iStack_10 + 0xa34,2);
            *(int *)(iStack_10 + 0x2d8) = *(int *)(iStack_10 + 0x2d8) + 1;
            iStack_578 = *(int *)(iStack_10 + 0xb20);
            sStack_52 = *(short *)(iStack_578 + 0x16);
            *(int *)(iStack_10 + 0x2d4) = (int)sStack_52;
            iStack_320 = iStack_578;
            sStack_50 = sStack_52;
          }
          else {
            lVar15 = 2;
          }
        }
        bVar3 = false;
        if (((uVar2 & 0x500) != 0) && (0 < *(int *)(iStack_10 + 0x2d8))) {
          bVar3 = true;
          iVar7 = *(int *)(iStack_10 + 0x2d8) + -4;
          if (iVar7 < 0) {
            iVar7 = 0;
          }
          *(int *)(iStack_10 + 0x2d8) = iVar7;
          if (iVar7 < 0) {
            iVar7 = iVar7 + 3;
          }
          *(int *)(iStack_10 + 0x2e0) = iVar7 >> 2;
          lVar15 = 3;
        }
        bVar16 = false;
        if (((uVar2 & 0xa00) != 0) &&
           (*(int *)(iStack_10 + 0x2d8) + 1 < *(int *)(iStack_10 + 0x2dc))) {
          bVar16 = true;
          iVar7 = *(int *)(iStack_10 + 0x2d8) + 4;
          if (*(int *)(iStack_10 + 0x2dc) <= iVar7) {
            iVar7 = *(int *)(iStack_10 + 0x2dc) + -1;
          }
          *(int *)(iStack_10 + 0x2d8) = iVar7;
          if (iVar7 < 0) {
            iVar7 = iVar7 + 3;
          }
          *(int *)(iStack_10 + 0x2e0) = iVar7 >> 2;
          lVar15 = 3;
        }
        if (lVar15 != 0) {
          if (lVar15 == 1) {
            *(int *)(iStack_10 + 0x2d8) = *(int *)(iStack_10 + 0x2d8) + -1;
            *(int *)(iStack_10 + 0x2e0) = *(int *)(iStack_10 + 0x2e0) + -1;
            if (*(int *)(iStack_10 + 0x2e0) < 0) {
              *(int *)(iStack_10 + 0x2d8) = *(int *)(iStack_10 + 0x2dc) + -1;
              iVar7 = *(int *)(iStack_10 + 0x2dc);
              if (iVar7 < 0) {
                iVar7 = iVar7 + 3;
              }
              *(int *)(iStack_10 + 0x2e0) = iVar7 >> 2;
            }
          }
          else if (lVar15 == 2) {
            *(int *)(iStack_10 + 0x2d8) = *(int *)(iStack_10 + 0x2d8) + 1;
            *(int *)(iStack_10 + 0x2e0) = *(int *)(iStack_10 + 0x2e0) + 1;
            if (*(int *)(iStack_10 + 0x2dc) <= *(int *)(iStack_10 + 0x2d8)) {
              *(undefined4 *)(iStack_10 + 0x2d8) = 0;
              *(undefined4 *)(iStack_10 + 0x2e0) = 0;
            }
          }
          SetMagicMenu__7BtlMenuFiii
                    (iStack_10,1,*(undefined4 *)(iStack_10 + 0x2d8),0xffffffffffffffff);
          Select__6CursorFP9MenuPlace(iStack_10 + 0xa34,
                          *(int *)(iStack_10 + 0x29c) + *(int *)(iStack_10 + 0x2c4) * 0x80);
        }
        iStack_57c = *(int *)(iStack_10 + 0xb20);
        sVar13 = *(short *)(iStack_57c + 0x16);
        iStack_324 = iStack_57c;
        sStack_56 = sVar13;
        sStack_54 = sVar13;
        if (sVar8 != sVar13) {
          iStack_580 = *(int *)(iStack_10 + 0xb20);
          sStack_5a = *(short *)(iStack_580 + 0x1e);
          *(int *)(iStack_10 + 0x2c4) = (int)sStack_5a << 1;
          *(undefined4 *)(iStack_10 + 0x2d0) = *(undefined4 *)(iStack_10 + 0x2d4);
          iStack_328 = iStack_580;
          sStack_58 = sStack_5a;
          if (bVar18) {
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,0,1,0);
          }
          else if (bVar3) {
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,7,1,0);
          }
          else if (bVar16) {
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,6,1,0);
          }
        }
        if ((sVar8 != sVar13) || (-1 < (long)((ulong)*(byte *)(iStack_10 + 0x24) << 0x3e))) {
          lVar15 = (long)sVar13;
          if (999 < sVar13) {
            lVar15 = (long)(sVar13 + -1000);
          }
          uVar6 = GetRegDat__9RegDatApiFiii(0x1f,lVar15,0xffffffffffffffff);
          SetNoteWindow__7BtlMenuFPc(iStack_10,uVar6);
          puStack_32c = pCGpffff86b4->pTurnOrderDisp;
          *(undefined4 *)(puStack_32c + 100) = 0;
          iVar7 = (int)lVar15;
          GetTargetList__7CBattleFiiiiiP8ECCParamPiPi
                    (pCGpffff86b4,(int)pCGpffff86b4->cActor,-1,
                     (uint)(((ulong)*(ushort *)(iStack_23c + iVar7 * 0x44 + 4) << 0x37) >> 0x3e),
                     (uint)(((ulong)*(byte *)(iStack_23c + iVar7 * 0x44 + 5) << 0x3c) >> 0x3d),
                     (uint)(((ulong)*(byte *)(iStack_23c + iVar7 * 0x44 + 5) << 0x3a) >> 0x3e),
                     (void *)(iStack_23c + iVar7 * 0x44 + 8),&iStack_22c,aiStack_7a0);
          if (iStack_22c == 0) {
            MakeTurnOrderTable__7CBattleFfiPiiiPUisibi
                      (pCGpffff86b4,(float)*(ushort *)(iStack_23c + iVar7 * 0x44 + 0x1a) / 100.0,0,
                       (int *)0x0,2,iVar7,(uint *)0x0,(short)pCGpffff86b4->cActor,-1,true,-2);
          }
          else {
            MakeTurnOrderTable__7CBattleFfiPiiiPUisibi
                      (pCGpffff86b4,(float)*(ushort *)(iStack_23c + iVar7 * 0x44 + 0x1a) / 100.0,
                       iStack_22c,aiStack_7a0,2,iVar7,(uint *)(iStack_23c + iVar7 * 0x44 + 8),
                       (short)pCGpffff86b4->cActor,-1,true,-2);
            if (((ulong)*(byte *)(iStack_23c + iVar7 * 0x44 + 4) & 0x7f) >> 5 == 0) {
              for (iVar7 = 0; iVar7 < iStack_22c; iVar7 = iVar7 + 1) {
                SetSelectChr__13TurnOrderDispFii(pCGpffff86b4->pTurnOrderDisp,aiStack_7a0[iVar7],2);
              }
            }
            else {
              for (iVar7 = 0; iVar7 < iStack_22c; iVar7 = iVar7 + 1) {
                SetSelectChr__13TurnOrderDispFii(pCGpffff86b4->pTurnOrderDisp,aiStack_7a0[iVar7],1);
              }
            }
          }
          *(byte *)(iStack_10 + 0x24) = *(byte *)(iStack_10 + 0x24) & 0xfd | 2;
        }
        if ((uVar1 & 0x2000) == 0) {
          if ((uVar1 & 0x4000) == 0) {
            if ((((long)((ulong)*(byte *)(ourBtlSaveDat + 3) << 0x3e) < 0) &&
                ((*(byte *)((int)pCGpffff86b4 +
                           (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb4)
                 & 1) == 0)) && ((uVar1 & 0x1000) != 0)) {
              if ((*(int *)(iStack_10 + 0x2d4) < 1000) &&
                 (((ulong)*(byte *)(iStack_23c + *(int *)(iStack_10 + 0x2d0) * 0x44 + 4) & 0x7f) >>
                  5 == 0)) {
                *(undefined2 *)(iStack_10 + 0xb4c) = *(undefined2 *)(iStack_10 + 0x28);
                *(undefined2 *)(iStack_10 + 0xb4e) = *(undefined2 *)(iStack_10 + 0x2a);
                *(undefined2 *)(iStack_10 + 0xb50) = 2;
                *(undefined2 *)(iStack_10 + 0xb52) = 1;
                *(undefined1 *)(iStack_10 + 0xb54) = 2;
                *(byte *)(iStack_10 + 0xb55) =
                     (byte)(((ulong)*(byte *)(iStack_23c + *(int *)(iStack_10 + 0x2d0) * 0x44 + 6)
                            << 0x3c) >> 0x3d);
                *(short *)(iStack_10 + 0xb56) = (short)*(undefined4 *)(iStack_10 + 0x2d0);
                *(undefined2 *)(iStack_10 + 0x28) = 0x18;
                *(undefined2 *)(iStack_10 + 0x2a) = 0;
                PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,2,1,0);
                return 0;
              }
              PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,4,1,0);
            }
          }
          else {
            *(undefined2 *)(iStack_10 + 0x28) = 0;
            *(undefined2 *)(iStack_10 + 0x2a) = 0;
            puStack_330 = pCGpffff86b4->pTurnOrderDisp;
            *(undefined4 *)(puStack_330 + 100) = 0;
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,3,1,0);
          }
        }
        else if (*(int *)(iStack_10 + 0x2d4) < 1000) {
          iVar7 = iStack_23c + *(int *)(iStack_10 + 0x2d0) * 0x44;
          iStack_240 = iVar7 + 8;
          if (((*(byte *)(iVar7 + 0xb) >> 4 == 1) &&
              ((long)((ulong)*(byte *)(iVar7 + 0xb) << 0x3c) < 0)) && (*(char *)(iVar7 + 10) == '(')
             ) {
            iStack_22c = 0;
            for (iVar7 = 0; iVar7 < 0xc; iVar7 = iVar7 + 1) {
              if (((((pCGpffff86b4->aChr[iVar7].bFlagsA & 1) != 0) &&
                   ((long)((ulong)pCGpffff86b4->aChr[iVar7].bFlagsA << 0x3e) < 0)) &&
                  (-1 < (long)((ulong)pCGpffff86b4->aChr[iVar7].bFlagsA2 << 0x3d))) &&
                 ((pCGpffff86b4->aChr[iVar7].nHp < 1 &&
                  ((*(byte *)((int)pCGpffff86b4 +
                             (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb4
                             ) & 1) == (pCGpffff86b4->aChr[iVar7].bFlagsB & 1))))) {
                iStack_22c = iStack_22c + 1;
              }
            }
            if (iStack_22c == 0) {
              PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,4,1,0);
              return 0;
            }
          }
          if ((long)*(short *)(iStack_10 + 0xb5a) != (long)*(int *)(iStack_10 + 0x2d0)) {
            *(undefined2 *)(iStack_10 + 0xb5e) = 0xffff;
            *(undefined2 *)(iStack_10 + 0xb5c) = 0xffff;
          }
          *(short *)(iStack_10 + 0xb5a) = (short)*(undefined4 *)(iStack_10 + 0x2d0);
          *(undefined2 *)(iStack_10 + 0x28) = 3;
          *(undefined2 *)(iStack_10 + 0x2a) = 0;
          PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,2,1,0);
        }
        else {
          PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,4,1,0);
        }
      }
    }
    else if (((*(short *)(iStack_10 + 0x2a) == 0) && (*(short *)(iStack_10 + 0x19e) != 0xc)) &&
            (*(short *)(iStack_10 + 0x19e) != 0xd)) {
      *(byte *)(iStack_10 + 0x25) = *(byte *)(iStack_10 + 0x25) & 0xf7;
      SetWindowMove__7BtlMenuFii(iStack_10,0,1);
      if (*(int *)(iStack_10 + 0x140) != 0) {
        SetMark__10ScrollMarkFUc(*(undefined4 *)(iStack_10 + 0x140),0);
      }
      SetMagicMenu__7BtlMenuFiii(iStack_10,1,0xffffffffffffffff,*(undefined2 *)(iStack_10 + 0xb5a));
      CreateCursole__7BtlMenuFv(iStack_10);
      Select__6CursorFP9MenuPlace(iStack_10 + 0xa34,
                      *(int *)(iStack_10 + 0x29c) + *(int *)(iStack_10 + 0x2c4) * 0x80);
      QuickMove__6CursorFv(iStack_10 + 0xa34);
      SetWindowClose__7BtlMenuFii(iStack_10,2,6);
      AllBCurDestruct__7BtlMenuFv();
      *(undefined2 *)(iStack_10 + 0x2a) = 1;
      *(byte *)(iStack_10 + 0x24) = *(byte *)(iStack_10 + 0x24) & 0xfd;
    }
    break;
  case 3:
    iStack_244 = GetRegDat__9RegDatApiFiii(0x38,0,0xffffffffffffffff);
    iStack_248 = iStack_244 + *(int *)(iStack_10 + 0x2d4) * 0x44;
    uStack_11 = 0;
    iStack_24c = iStack_248 + 8;
    if (((*(byte *)(iStack_248 + 0xb) >> 4 == 1) &&
        ((long)((ulong)*(byte *)(iStack_248 + 0xb) << 0x3c) < 0)) &&
       (*(char *)(iStack_248 + 10) == '(')) {
      uStack_11 = 1;
    }
    sVar8 = *(short *)(iStack_10 + 0x2a);
    if (sVar8 == 2) {
      *(undefined2 *)(iStack_10 + 0x28) = 2;
      *(undefined2 *)(iStack_10 + 0x2a) = 0;
      AllBCurDestruct__7BtlMenuFv();
    }
    else if (sVar8 == 1) {
      if (((*(short *)(iStack_10 + 0x30a) == 1) || (*(short *)(iStack_10 + 0x30a) == 2)) ||
         (*(short *)(iStack_10 + 0x30a) == 5)) {
        if ((long)((ulong)*(byte *)(iStack_10 + 0x24) << 0x3d) < 0) {
          sVar8 = (short)*(undefined4 *)(iStack_10 + 0x440);
          if (999 < sVar8) {
            sVar8 = sVar8 + -1000;
          }
          if (sVar8 == 100) {
            sVar8 = -1;
          }
          DelaySelectFunc__7BtlMenuFiiiP12EFCTCOMParam
                    (iStack_10,sVar8,2,*(undefined4 *)(iStack_10 + 0x2d4),iStack_248);
          *(byte *)(iStack_10 + 0x24) = *(byte *)(iStack_10 + 0x24) & 0xfb;
        }
        iStack_584 = *(int *)(iStack_10 + 0xb20);
        sVar8 = *(short *)(iStack_584 + 0x16);
        bVar16 = false;
        bVar3 = false;
        bVar18 = false;
        iStack_334 = iStack_584;
        sStack_5e = sVar8;
        sStack_5c = sVar8;
        if (((ulong)*(byte *)(iStack_248 + 5) & 0xf) >> 1 != 5) {
          iVar7 = 0;
          if ((uVar2 & 0x10) != 0) {
            bVar18 = true;
            iStack_588 = *(int *)(iStack_10 + 0xb20);
            sStack_62 = *(short *)(iStack_588 + 0x1e);
            iStack_338 = iStack_588;
            sStack_60 = sStack_62;
            if (sStack_62 < 1) {
              iVar7 = 1;
            }
            else {
              MoveCursor__6CursorFi(iStack_10 + 0xa34,1);
              *(int *)(iStack_10 + 0x444) = *(int *)(iStack_10 + 0x444) + -1;
              iStack_58c = *(int *)(iStack_10 + 0xb20);
              sStack_66 = *(short *)(iStack_58c + 0x16);
              *(int *)(iStack_10 + 0x440) = (int)sStack_66;
              iStack_33c = iStack_58c;
              sStack_64 = sStack_66;
            }
          }
          if ((uVar2 & 0x40) != 0) {
            bVar18 = true;
            iStack_590 = *(int *)(iStack_10 + 0xb20);
            sStack_6a = *(short *)(iStack_590 + 0x1e);
            iStack_340 = iStack_590;
            sStack_68 = sStack_6a;
            if ((sStack_6a + 1 < 4) &&
               (*(int *)(iStack_10 + 0x444) + 1 < *(int *)(iStack_10 + 0x448))) {
              MoveCursor__6CursorFi(iStack_10 + 0xa34,2);
              *(int *)(iStack_10 + 0x444) = *(int *)(iStack_10 + 0x444) + 1;
              iStack_594 = *(int *)(iStack_10 + 0xb20);
              sStack_6e = *(short *)(iStack_594 + 0x16);
              *(int *)(iStack_10 + 0x440) = (int)sStack_6e;
              iStack_344 = iStack_594;
              sStack_6c = sStack_6e;
            }
            else {
              iVar7 = 2;
            }
          }
          bVar3 = false;
          if (((uVar2 & 0x500) != 0) && (0 < *(int *)(iStack_10 + 0x444))) {
            bVar3 = true;
            iVar7 = *(int *)(iStack_10 + 0x444) + -4;
            if (iVar7 < 0) {
              iVar7 = 0;
            }
            *(int *)(iStack_10 + 0x444) = iVar7;
            if (iVar7 < 0) {
              iVar7 = iVar7 + 3;
            }
            *(int *)(iStack_10 + 0x44c) = iVar7 >> 2;
            iVar7 = 3;
          }
          bVar16 = false;
          if (((uVar2 & 0xa00) != 0) &&
             (*(int *)(iStack_10 + 0x444) + 1 < *(int *)(iStack_10 + 0x448))) {
            bVar16 = true;
            iVar7 = *(int *)(iStack_10 + 0x444) + 4;
            if (*(int *)(iStack_10 + 0x448) <= iVar7) {
              iVar7 = *(int *)(iStack_10 + 0x448) + -1;
            }
            *(int *)(iStack_10 + 0x444) = iVar7;
            if (iVar7 < 0) {
              iVar7 = iVar7 + 3;
            }
            *(int *)(iStack_10 + 0x44c) = iVar7 >> 2;
            iVar7 = 3;
          }
          if (iVar7 != 0) {
            if (iVar7 == 1) {
              *(int *)(iStack_10 + 0x444) = *(int *)(iStack_10 + 0x444) + -1;
              *(int *)(iStack_10 + 0x44c) = *(int *)(iStack_10 + 0x44c) + -1;
              if (*(int *)(iStack_10 + 0x44c) < 0) {
                *(int *)(iStack_10 + 0x444) = *(int *)(iStack_10 + 0x448) + -1;
                iVar7 = *(int *)(iStack_10 + 0x448);
                if (iVar7 < 0) {
                  iVar7 = iVar7 + 3;
                }
                *(int *)(iStack_10 + 0x44c) = iVar7 >> 2;
              }
            }
            else if (iVar7 == 2) {
              *(int *)(iStack_10 + 0x444) = *(int *)(iStack_10 + 0x444) + 1;
              *(int *)(iStack_10 + 0x44c) = *(int *)(iStack_10 + 0x44c) + 1;
              if (*(int *)(iStack_10 + 0x448) <= *(int *)(iStack_10 + 0x444)) {
                *(undefined4 *)(iStack_10 + 0x444) = 0;
                *(undefined4 *)(iStack_10 + 0x44c) = 0;
              }
            }
            SetTargetMenu__7BtlMenuFiiiP12EFCTCOMParamii
                      (iStack_10,2,2,*(undefined4 *)(iStack_10 + 0x2d0),iStack_248,
                       *(undefined4 *)(iStack_10 + 0x444),0xffffffffffffffff);
            Select__6CursorFP9MenuPlace(iStack_10 + 0xa34,
                            *(int *)(iStack_10 + 0x408) + *(int *)(iStack_10 + 0x430) * 0x80);
          }
        }
        iStack_598 = *(int *)(iStack_10 + 0xb20);
        sVar13 = *(short *)(iStack_598 + 0x16);
        iStack_348 = iStack_598;
        sStack_72 = sVar13;
        sStack_70 = sVar13;
        if (sVar8 != sVar13) {
          uVar12 = *(uint *)(iStack_10 + 0x444) & 3;
          if (((int)*(uint *)(iStack_10 + 0x444) < 0) && (uVar12 != 0)) {
            uVar12 = uVar12 - 4;
          }
          *(uint *)(iStack_10 + 0x430) = uVar12;
          *(undefined4 *)(iStack_10 + 0x43c) = *(undefined4 *)(iStack_10 + 0x440);
          if (bVar18) {
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,0,1,0);
          }
          else if (bVar3) {
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,7,1,0);
          }
          else if (bVar16) {
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,6,1,0);
          }
        }
        if ((sVar8 != sVar13) || (-1 < (long)((ulong)*(byte *)(iStack_10 + 0x24) << 0x3e))) {
          sVar8 = (short)*(undefined4 *)(iStack_10 + 0x440);
          if (999 < sVar8) {
            sVar8 = sVar8 + -1000;
          }
          if (sVar8 == 100) {
            sVar8 = -1;
          }
          SelectFunc__7BtlMenuFiiiP12EFCTCOMParam
                    (iStack_10,sVar8,2,*(undefined4 *)(iStack_10 + 0x2d4),iStack_248);
          *(byte *)(iStack_10 + 0x24) = *(byte *)(iStack_10 + 0x24) & 0xfd | 2;
          *(byte *)(iStack_10 + 0x24) = *(byte *)(iStack_10 + 0x24) & 0xfb | 4;
        }
        if ((uVar1 & 0x2000) != 0) {
          if (*(int *)(iStack_10 + 0x440) < 1000) {
            sVar8 = (short)*(undefined4 *)(iStack_10 + 0x440);
            if (sVar8 == 100) {
              sVar8 = -1;
            }
            *(undefined2 *)
             ((int)pCGpffff86b4 +
             (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x598) =
                 *(undefined2 *)(iStack_10 + 0xb58);
            *(undefined2 *)
             ((int)pCGpffff86b4 +
             (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x59a) =
                 *(undefined2 *)(iStack_10 + 0xb5a);
            *(short *)((int)pCGpffff86b4 +
                      (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x59c) =
                 (short)*(undefined4 *)(iStack_10 + 0x43c);
            *(undefined2 *)
             ((int)pCGpffff86b4 +
             (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x59e) = 0xffff;
            if (pcGpffff86ec != (code *)0x0) {
              (*pcGpffff86ec)(0x12,0,0xffffffffffffffff,0,0,0,uGpffff86e8);
            }
            if (pcGpffff86ec != (code *)0x0) {
              (*pcGpffff86ec)(5,*(undefined4 *)(iStack_10 + 0x2d0),sVar8,0,0,0,uGpffff86e8);
            }
            if (*(int *)(iStack_10 + 0xb38) != 0) {
              (**(code **)(*(int *)(*(int *)(iStack_10 + 0xb38) + 0x14) + 0x30))();
            }
            *(undefined4 *)(iStack_10 + 0xb38) = 0;
            if (*(int *)(iStack_10 + 0xb3c) != 0) {
              (**(code **)(*(int *)(*(int *)(iStack_10 + 0xb3c) + 0x14) + 0x30))();
            }
            *(undefined4 *)(iStack_10 + 0xb3c) = 0;
            AllWindowClose__7BtlMenuFv(iStack_10);
            AllBCurDestruct__7BtlMenuFv();
            *(undefined2 *)(iStack_10 + 0x28) = 0x14;
            *(undefined2 *)(iStack_10 + 0x2a) = 0;
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,2,1,0);
            return 0;
          }
          PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,4,1,0);
        }
        if ((uVar1 & 0x4000) != 0) {
          *(undefined2 *)(iStack_10 + 0x2a) = 2;
          puStack_34c = pCGpffff86b4->pTurnOrderDisp;
          *(undefined4 *)(puStack_34c + 100) = 0;
          if (pcGpffff86ec != (code *)0x0) {
            (*pcGpffff86ec)(0x12,0,0xffffffffffffffff,0,0,0,uGpffff86e8);
          }
          if (*(int *)(iStack_10 + 0xb38) != 0) {
            (**(code **)(*(int *)(*(int *)(iStack_10 + 0xb38) + 0x14) + 0x30))();
          }
          *(undefined4 *)(iStack_10 + 0xb38) = 0;
          if (*(int *)(iStack_10 + 0xb3c) != 0) {
            (**(code **)(*(int *)(*(int *)(iStack_10 + 0xb3c) + 0x14) + 0x30))();
          }
          *(undefined4 *)(iStack_10 + 0xb3c) = 0;
          if (pcGpffff86ec != (code *)0x0) {
            (*pcGpffff86ec)(3,0,0,0,0,0,uGpffff86e8);
          }
          PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,3,1,0);
        }
      }
    }
    else if (((sVar8 == 0) && (*(short *)(iStack_10 + 0x30a) != 0xc)) &&
            (*(short *)(iStack_10 + 0x30a) != 0xd)) {
      *(byte *)(iStack_10 + 0x25) = *(byte *)(iStack_10 + 0x25) & 0xf7 | 8;
      SetWindowMove__7BtlMenuFii(iStack_10,0,2);
      SetWindowMove__7BtlMenuFii(iStack_10,1,1);
      SetTargetMenu__7BtlMenuFiiiP12EFCTCOMParamii
                (iStack_10,2,2,*(undefined4 *)(iStack_10 + 0x2d4),iStack_248,0xffffffffffffffff,
                 *(undefined2 *)(iStack_10 + 0xb5c));
      CreateCursole__7BtlMenuFv(iStack_10);
      Select__6CursorFP9MenuPlace(iStack_10 + 0xa34,
                      *(int *)(iStack_10 + 0x408) + *(int *)(iStack_10 + 0x430) * 0x80);
      QuickMove__6CursorFv(iStack_10 + 0xa34);
      SetWindowClose__7BtlMenuFii(iStack_10,3,6);
      SetNoteWindow__7BtlMenuFPc(iStack_10,uRam0040af48);
      *(undefined2 *)(iStack_10 + 0x2a) = 1;
      *(byte *)(iStack_10 + 0x24) = *(byte *)(iStack_10 + 0x24) & 0xfd;
      *(byte *)(iStack_10 + 0x24) = *(byte *)(iStack_10 + 0x24) & 0xfb;
    }
    break;
  case 4:
    iVar7 = GetRegDat__9RegDatApiFiii(0x33,0,0xffffffffffffffff);
    if (*(short *)(iStack_10 + 0x2a) == 1) {
      if (((*(short *)(iStack_10 + 0x19e) == 1) || (*(short *)(iStack_10 + 0x19e) == 2)) ||
         (*(short *)(iStack_10 + 0x19e) == 5)) {
        iStack_59c = *(int *)(iStack_10 + 0xb20);
        sVar8 = *(short *)(iStack_59c + 0x16);
        bVar18 = false;
        lVar15 = 0;
        iStack_350 = iStack_59c;
        sStack_76 = sVar8;
        sStack_74 = sVar8;
        if ((uVar2 & 0x10) != 0) {
          bVar18 = true;
          iStack_5a0 = *(int *)(iStack_10 + 0xb20);
          sStack_7a = *(short *)(iStack_5a0 + 0x1e);
          iStack_354 = iStack_5a0;
          sStack_78 = sStack_7a;
          if (sStack_7a < 1) {
            lVar15 = 1;
          }
          else {
            MoveCursor__6CursorFi(iStack_10 + 0xa34,1);
            *(int *)(iStack_10 + 0x2d8) = *(int *)(iStack_10 + 0x2d8) + -1;
            iStack_5a4 = *(int *)(iStack_10 + 0xb20);
            sStack_7e = *(short *)(iStack_5a4 + 0x16);
            *(int *)(iStack_10 + 0x2d4) = (int)sStack_7e;
            iStack_358 = iStack_5a4;
            sStack_7c = sStack_7e;
          }
        }
        if ((uVar2 & 0x40) != 0) {
          bVar18 = true;
          iStack_5a8 = *(int *)(iStack_10 + 0xb20);
          sStack_82 = *(short *)(iStack_5a8 + 0x1e);
          iStack_35c = iStack_5a8;
          sStack_80 = sStack_82;
          if ((sStack_82 + 1 < 4) && (*(int *)(iStack_10 + 0x2d8) + 1 < *(int *)(iStack_10 + 0x2dc))
             ) {
            MoveCursor__6CursorFi(iStack_10 + 0xa34,2);
            *(int *)(iStack_10 + 0x2d8) = *(int *)(iStack_10 + 0x2d8) + 1;
            iStack_5ac = *(int *)(iStack_10 + 0xb20);
            sStack_86 = *(short *)(iStack_5ac + 0x16);
            *(int *)(iStack_10 + 0x2d4) = (int)sStack_86;
            iStack_360 = iStack_5ac;
            sStack_84 = sStack_86;
          }
          else {
            lVar15 = 2;
          }
        }
        bVar3 = false;
        if (((uVar2 & 0x500) != 0) && (0 < *(int *)(iStack_10 + 0x2d8))) {
          bVar3 = true;
          iVar10 = *(int *)(iStack_10 + 0x2d8) + -4;
          if (iVar10 < 0) {
            iVar10 = 0;
          }
          *(int *)(iStack_10 + 0x2d8) = iVar10;
          if (iVar10 < 0) {
            iVar10 = iVar10 + 3;
          }
          *(int *)(iStack_10 + 0x2e0) = iVar10 >> 2;
          lVar15 = 3;
        }
        bVar16 = false;
        if (((uVar2 & 0xa00) != 0) &&
           (*(int *)(iStack_10 + 0x2d8) + 1 < *(int *)(iStack_10 + 0x2dc))) {
          bVar16 = true;
          iVar10 = *(int *)(iStack_10 + 0x2d8) + 4;
          if (*(int *)(iStack_10 + 0x2dc) <= iVar10) {
            iVar10 = *(int *)(iStack_10 + 0x2dc) + -1;
          }
          *(int *)(iStack_10 + 0x2d8) = iVar10;
          if (iVar10 < 0) {
            iVar10 = iVar10 + 3;
          }
          *(int *)(iStack_10 + 0x2e0) = iVar10 >> 2;
          lVar15 = 3;
        }
        if (lVar15 != 0) {
          if (lVar15 == 1) {
            *(int *)(iStack_10 + 0x2d8) = *(int *)(iStack_10 + 0x2d8) + -1;
            *(int *)(iStack_10 + 0x2e0) = *(int *)(iStack_10 + 0x2e0) + -1;
            if (*(int *)(iStack_10 + 0x2e0) < 0) {
              *(int *)(iStack_10 + 0x2d8) = *(int *)(iStack_10 + 0x2dc) + -1;
              iVar10 = *(int *)(iStack_10 + 0x2dc);
              if (iVar10 < 0) {
                iVar10 = iVar10 + 3;
              }
              *(int *)(iStack_10 + 0x2e0) = iVar10 >> 2;
            }
          }
          else if (lVar15 == 2) {
            *(int *)(iStack_10 + 0x2d8) = *(int *)(iStack_10 + 0x2d8) + 1;
            *(int *)(iStack_10 + 0x2e0) = *(int *)(iStack_10 + 0x2e0) + 1;
            if (*(int *)(iStack_10 + 0x2dc) <= *(int *)(iStack_10 + 0x2d8)) {
              *(undefined4 *)(iStack_10 + 0x2d8) = 0;
              *(undefined4 *)(iStack_10 + 0x2e0) = 0;
            }
          }
          SetItemMenu__7BtlMenuFiii
                    (iStack_10,1,*(undefined4 *)(iStack_10 + 0x2d8),0xffffffffffffffff);
          Select__6CursorFP9MenuPlace(iStack_10 + 0xa34,
                          *(int *)(iStack_10 + 0x29c) + *(int *)(iStack_10 + 0x2c4) * 0x80);
        }
        iStack_5b0 = *(int *)(iStack_10 + 0xb20);
        sVar13 = *(short *)(iStack_5b0 + 0x16);
        iStack_364 = iStack_5b0;
        sStack_8a = sVar13;
        sStack_88 = sVar13;
        if (sVar8 != sVar13) {
          iStack_5b4 = *(int *)(iStack_10 + 0xb20);
          sStack_8e = *(short *)(iStack_5b4 + 0x1e);
          *(int *)(iStack_10 + 0x2c4) = (int)sStack_8e << 1;
          *(undefined4 *)(iStack_10 + 0x2d0) = *(undefined4 *)(iStack_10 + 0x2d4);
          iStack_368 = iStack_5b4;
          sStack_8c = sStack_8e;
          if (bVar18) {
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,0,1,0);
          }
          else if (bVar3) {
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,7,1,0);
          }
          else if (bVar16) {
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,6,1,0);
          }
        }
        if ((sVar8 != sVar13) || (-1 < (long)((ulong)*(byte *)(iStack_10 + 0x24) << 0x3e))) {
          iVar10 = *(int *)(iStack_10 + 0x2d4);
          if (999 < iVar10) {
            iVar10 = iVar10 + -1000;
          }
          if (*(short *)(iVar7 + iVar10 * 0x30 + 0x22) < 0) {
            sprintf(auStack_8a0,0x654ec0,
                            (int)*(short *)(iVar7 + iVar10 * 0x30 + 0x18) % 1000);
            SetNoteWindow__7BtlMenuFPc(iStack_10,auStack_8a0);
          }
          else {
            uVar6 = GetRegDat__9RegDatApiFiii(0x1a,iVar10,0xffffffffffffffff);
            SetNoteWindow__7BtlMenuFPc(iStack_10,uVar6);
          }
          puStack_36c = pCGpffff86b4->pTurnOrderDisp;
          *(undefined4 *)(puStack_36c + 100) = 0;
          GetTargetList__7CBattleFiiiiiP8ECCParamPiPi
                    (pCGpffff86b4,(int)pCGpffff86b4->cActor,-1,
                     (uint)(((ulong)*(ushort *)(iVar7 + iVar10 * 0x30 + 4) << 0x37) >> 0x3e),
                     (uint)(((ulong)*(byte *)(iVar7 + iVar10 * 0x30 + 5) << 0x3c) >> 0x3d),
                     (uint)(((ulong)*(byte *)(iVar7 + iVar10 * 0x30 + 5) << 0x3a) >> 0x3e),
                     (void *)(iVar7 + iVar10 * 0x30 + 8),&iStack_22c,aiStack_7a0);
          if (iStack_22c == 0) {
            MakeTurnOrderTable__7CBattleFfiPiiiPUisibi
                      (pCGpffff86b4,(float)*(ushort *)(iVar7 + iVar10 * 0x30 + 0x1a) / 100.0,0,
                       (int *)0x0,3,iVar10,(uint *)(iVar7 + iVar10 * 0x30 + 8),
                       (short)pCGpffff86b4->cActor,-1,true,-2);
          }
          else {
            MakeTurnOrderTable__7CBattleFfiPiiiPUisibi
                      (pCGpffff86b4,(float)*(ushort *)(iVar7 + iVar10 * 0x30 + 0x1a) / 100.0,
                       iStack_22c,aiStack_7a0,3,iVar10,(uint *)(iVar7 + iVar10 * 0x30 + 8),
                       (short)pCGpffff86b4->cActor,-1,true,-2);
            uVar9 = ((ulong)*(byte *)(iVar7 + iVar10 * 0x30 + 4) & 0x7f) >> 5;
            if (uVar9 == 0) {
              for (iVar10 = 0; iVar10 < iStack_22c; iVar10 = iVar10 + 1) {
                SetSelectChr__13TurnOrderDispFii(pCGpffff86b4->pTurnOrderDisp,aiStack_7a0[iVar10],2)
                ;
              }
            }
            else {
              for (iVar10 = 0; iVar10 < iStack_22c; iVar10 = iVar10 + 1) {
                uVar9 = SetSelectChr__13TurnOrderDispFii
                                  (pCGpffff86b4->pTurnOrderDisp,aiStack_7a0[iVar10],1,pCGpffff86b4,
                                   uVar9);
              }
            }
          }
          *(byte *)(iStack_10 + 0x24) = *(byte *)(iStack_10 + 0x24) & 0xfd | 2;
        }
        if ((uVar1 & 0x2000) == 0) {
          if ((uVar1 & 0x4000) != 0) {
            *(undefined2 *)(iStack_10 + 0x28) = 0;
            *(undefined2 *)(iStack_10 + 0x2a) = 0;
            puStack_370 = pCGpffff86b4->pTurnOrderDisp;
            *(undefined4 *)(puStack_370 + 100) = 0;
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,3,1,0);
          }
        }
        else if (((*(int *)(iStack_10 + 0x2d0) < 1000) &&
                 (((ulong)*(byte *)(iVar7 + *(int *)(iStack_10 + 0x2d0) * 0x30 + 4) & 0x1f) >> 3 !=
                  0)) && (((ulong)*(byte *)(iVar7 + *(int *)(iStack_10 + 0x2d0) * 0x30 + 4) & 0x1f)
                          >> 3 != 3)) {
          if (((((ulong)*(byte *)(iVar7 + *(int *)(iStack_10 + 0x2d0) * 0x30 + 4) & 0x7f) >> 5 == 0)
              && (*(short *)(iVar7 + *(int *)(iStack_10 + 0x2d0) * 0x30 + 0x18) == -1)) &&
             ((*(int *)(iVar7 + *(int *)(iStack_10 + 0x2d0) * 0x30 + 8) == -1 &&
              (*(int *)(iVar7 + *(int *)(iStack_10 + 0x2d0) * 0x30 + 0xc) != -1)))) {
            if ((long)*(short *)(iStack_10 + 0xb5a) != (long)*(int *)(iStack_10 + 0x2d0)) {
              *(undefined2 *)(iStack_10 + 0xb5e) = 0xffff;
              *(undefined2 *)(iStack_10 + 0xb5c) = 0xffff;
            }
            *(short *)(iStack_10 + 0xb5a) = (short)*(undefined4 *)(iStack_10 + 0x2d0);
            *(undefined2 *)(iStack_10 + 0x28) = 6;
            *(undefined2 *)(iStack_10 + 0x2a) = 0;
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,2,1,0);
          }
          else {
            iVar7 = iVar7 + *(int *)(iStack_10 + 0x2d0) * 0x30;
            iStack_250 = iVar7 + 8;
            if (((*(byte *)(iVar7 + 0xb) >> 4 == 1) &&
                ((long)((ulong)*(byte *)(iVar7 + 0xb) << 0x3c) < 0)) &&
               (*(char *)(iVar7 + 10) == '(')) {
              iStack_22c = 0;
              for (iVar7 = 0; iVar7 < 0xc; iVar7 = iVar7 + 1) {
                if (((((pCGpffff86b4->aChr[iVar7].bFlagsA & 1) != 0) &&
                     ((long)((ulong)pCGpffff86b4->aChr[iVar7].bFlagsA << 0x3e) < 0)) &&
                    (-1 < (long)((ulong)pCGpffff86b4->aChr[iVar7].bFlagsA2 << 0x3d))) &&
                   ((pCGpffff86b4->aChr[iVar7].nHp < 1 &&
                    ((*(byte *)((int)pCGpffff86b4 +
                               (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 +
                               0xb4) & 1) == (pCGpffff86b4->aChr[iVar7].bFlagsB & 1))))) {
                  iStack_22c = iStack_22c + 1;
                }
              }
              if (iStack_22c == 0) {
                PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,4,1,0);
                return 0;
              }
            }
            if ((long)*(short *)(iStack_10 + 0xb5a) != (long)*(int *)(iStack_10 + 0x2d0)) {
              *(undefined2 *)(iStack_10 + 0xb5e) = 0xffff;
              *(undefined2 *)(iStack_10 + 0xb5c) = 0xffff;
            }
            *(short *)(iStack_10 + 0xb5a) = (short)*(undefined4 *)(iStack_10 + 0x2d0);
            *(undefined2 *)(iStack_10 + 0x28) = 5;
            *(undefined2 *)(iStack_10 + 0x2a) = 0;
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,2,1,0);
          }
        }
        else {
          PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,4,1,0);
        }
      }
    }
    else if (((*(short *)(iStack_10 + 0x2a) == 0) && (*(short *)(iStack_10 + 0x19e) != 0xc)) &&
            (*(short *)(iStack_10 + 0x19e) != 0xd)) {
      *(byte *)(iStack_10 + 0x25) = *(byte *)(iStack_10 + 0x25) & 0xf7;
      uVar6 = SetWindowMove__7BtlMenuFii(iStack_10,0,1);
      if (*(int *)(iStack_10 + 0x140) != 0) {
        SetMark__10ScrollMarkFUc(*(undefined4 *)(iStack_10 + 0x140),0,uVar6);
      }
      SetItemMenu__7BtlMenuFiii(iStack_10,1,0xffffffffffffffff,*(undefined2 *)(iStack_10 + 0xb5a));
      CreateCursole__7BtlMenuFv(iStack_10);
      Select__6CursorFP9MenuPlace(iStack_10 + 0xa34,
                      *(int *)(iStack_10 + 0x29c) + *(int *)(iStack_10 + 0x2c4) * 0x80);
      uVar6 = QuickMove__6CursorFv(iStack_10 + 0xa34);
      SetWindowClose__7BtlMenuFii(iStack_10,2,6,uVar6);
      AllBCurDestruct__7BtlMenuFv();
      *(undefined2 *)(iStack_10 + 0x2a) = 1;
      *(byte *)(iStack_10 + 0x24) = *(byte *)(iStack_10 + 0x24) & 0xfd;
    }
    break;
  case 5:
    iStack_254 = GetRegDat__9RegDatApiFiii(0x33,0,0xffffffffffffffff);
    iStack_258 = iStack_254 + *(int *)(iStack_10 + 0x2d4) * 0x30;
    uStack_11 = 0;
    iStack_25c = iStack_258 + 8;
    if (((*(byte *)(iStack_258 + 0xb) >> 4 == 1) &&
        ((long)((ulong)*(byte *)(iStack_258 + 0xb) << 0x3c) < 0)) &&
       (*(char *)(iStack_258 + 10) == '(')) {
      uStack_11 = 1;
    }
    sVar8 = *(short *)(iStack_10 + 0x2a);
    if (sVar8 == 2) {
      *(undefined2 *)(iStack_10 + 0x28) = 4;
      *(undefined2 *)(iStack_10 + 0x2a) = 0;
      AllBCurDestruct__7BtlMenuFv();
    }
    else if (sVar8 == 1) {
      if (((*(short *)(iStack_10 + 0x30a) == 1) || (*(short *)(iStack_10 + 0x30a) == 2)) ||
         (*(short *)(iStack_10 + 0x30a) == 5)) {
        if ((long)((ulong)*(byte *)(iStack_10 + 0x24) << 0x3d) < 0) {
          sVar8 = (short)*(undefined4 *)(iStack_10 + 0x440);
          if (999 < sVar8) {
            sVar8 = sVar8 + -1000;
          }
          if (sVar8 == 100) {
            sVar8 = -1;
          }
          DelaySelectFunc__7BtlMenuFiiiP12EFCTCOMParam
                    (iStack_10,sVar8,3,*(undefined4 *)(iStack_10 + 0x2d4),iStack_258);
          *(byte *)(iStack_10 + 0x24) = *(byte *)(iStack_10 + 0x24) & 0xfb;
        }
        iStack_5b8 = *(int *)(iStack_10 + 0xb20);
        sVar8 = *(short *)(iStack_5b8 + 0x16);
        bVar16 = false;
        bVar3 = false;
        bVar18 = false;
        iStack_374 = iStack_5b8;
        sStack_92 = sVar8;
        sStack_90 = sVar8;
        if (((ulong)*(byte *)(iStack_258 + 5) & 0xf) >> 1 != 5) {
          iVar7 = 0;
          if ((uVar2 & 0x10) != 0) {
            bVar16 = true;
            iStack_5bc = *(int *)(iStack_10 + 0xb20);
            sStack_96 = *(short *)(iStack_5bc + 0x1e);
            iStack_378 = iStack_5bc;
            sStack_94 = sStack_96;
            if (sStack_96 < 1) {
              iVar7 = 1;
            }
            else {
              MoveCursor__6CursorFi(iStack_10 + 0xa34,1);
              *(int *)(iStack_10 + 0x444) = *(int *)(iStack_10 + 0x444) + -1;
              iStack_5c0 = *(int *)(iStack_10 + 0xb20);
              sStack_9a = *(short *)(iStack_5c0 + 0x16);
              *(int *)(iStack_10 + 0x440) = (int)sStack_9a;
              iStack_37c = iStack_5c0;
              sStack_98 = sStack_9a;
            }
          }
          if ((uVar2 & 0x40) != 0) {
            bVar16 = true;
            iStack_5c4 = *(int *)(iStack_10 + 0xb20);
            sStack_9e = *(short *)(iStack_5c4 + 0x1e);
            iStack_380 = iStack_5c4;
            sStack_9c = sStack_9e;
            if ((sStack_9e + 1 < 4) &&
               (*(int *)(iStack_10 + 0x444) + 1 < *(int *)(iStack_10 + 0x448))) {
              MoveCursor__6CursorFi(iStack_10 + 0xa34,2);
              *(int *)(iStack_10 + 0x444) = *(int *)(iStack_10 + 0x444) + 1;
              iStack_5c8 = *(int *)(iStack_10 + 0xb20);
              sStack_a2 = *(short *)(iStack_5c8 + 0x16);
              *(int *)(iStack_10 + 0x440) = (int)sStack_a2;
              iStack_384 = iStack_5c8;
              sStack_a0 = sStack_a2;
            }
            else {
              iVar7 = 2;
            }
          }
          bVar18 = false;
          if (((uVar2 & 0x500) != 0) && (0 < *(int *)(iStack_10 + 0x444))) {
            bVar18 = true;
            iVar7 = *(int *)(iStack_10 + 0x444) + -4;
            if (iVar7 < 0) {
              iVar7 = 0;
            }
            *(int *)(iStack_10 + 0x444) = iVar7;
            if (iVar7 < 0) {
              iVar7 = iVar7 + 3;
            }
            *(int *)(iStack_10 + 0x44c) = iVar7 >> 2;
            iVar7 = 3;
          }
          bVar3 = false;
          if (((uVar2 & 0xa00) != 0) &&
             (*(int *)(iStack_10 + 0x444) + 1 < *(int *)(iStack_10 + 0x448))) {
            bVar3 = true;
            iVar7 = *(int *)(iStack_10 + 0x444) + 4;
            if (*(int *)(iStack_10 + 0x448) <= iVar7) {
              iVar7 = *(int *)(iStack_10 + 0x448) + -1;
            }
            *(int *)(iStack_10 + 0x444) = iVar7;
            if (iVar7 < 0) {
              iVar7 = iVar7 + 3;
            }
            *(int *)(iStack_10 + 0x44c) = iVar7 >> 2;
            iVar7 = 3;
          }
          if (iVar7 != 0) {
            if (iVar7 == 1) {
              *(int *)(iStack_10 + 0x444) = *(int *)(iStack_10 + 0x444) + -1;
              *(int *)(iStack_10 + 0x44c) = *(int *)(iStack_10 + 0x44c) + -1;
              if (*(int *)(iStack_10 + 0x44c) < 0) {
                *(int *)(iStack_10 + 0x444) = *(int *)(iStack_10 + 0x448) + -1;
                iVar7 = *(int *)(iStack_10 + 0x448);
                if (iVar7 < 0) {
                  iVar7 = iVar7 + 3;
                }
                *(int *)(iStack_10 + 0x44c) = iVar7 >> 2;
              }
            }
            else if (iVar7 == 2) {
              *(int *)(iStack_10 + 0x444) = *(int *)(iStack_10 + 0x444) + 1;
              *(int *)(iStack_10 + 0x44c) = *(int *)(iStack_10 + 0x44c) + 1;
              if (*(int *)(iStack_10 + 0x448) <= *(int *)(iStack_10 + 0x444)) {
                *(undefined4 *)(iStack_10 + 0x444) = 0;
                *(undefined4 *)(iStack_10 + 0x44c) = 0;
              }
            }
            uVar6 = SetTargetMenu__7BtlMenuFiiiP12EFCTCOMParamii
                              (iStack_10,2,3,*(undefined4 *)(iStack_10 + 0x2d4),iStack_258,
                               *(undefined4 *)(iStack_10 + 0x444),0xffffffffffffffff);
            Select__6CursorFP9MenuPlace(iStack_10 + 0xa34,
                            *(int *)(iStack_10 + 0x408) + *(int *)(iStack_10 + 0x430) * 0x80,uVar6);
          }
        }
        iStack_5cc = *(int *)(iStack_10 + 0xb20);
        sVar13 = *(short *)(iStack_5cc + 0x16);
        iStack_388 = iStack_5cc;
        sStack_a6 = sVar13;
        sStack_a4 = sVar13;
        if (sVar8 != sVar13) {
          uVar12 = *(uint *)(iStack_10 + 0x444) & 3;
          if (((int)*(uint *)(iStack_10 + 0x444) < 0) && (uVar12 != 0)) {
            uVar12 = uVar12 - 4;
          }
          *(uint *)(iStack_10 + 0x430) = uVar12;
          *(undefined4 *)(iStack_10 + 0x43c) = *(undefined4 *)(iStack_10 + 0x440);
          if (bVar16) {
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,0,1,0);
          }
          else if (bVar18) {
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,7,1,0);
          }
          else if (bVar3) {
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,6,1,0);
          }
        }
        if ((sVar8 != sVar13) || (-1 < (long)((ulong)*(byte *)(iStack_10 + 0x24) << 0x3e))) {
          sVar8 = (short)*(undefined4 *)(iStack_10 + 0x440);
          if (999 < sVar8) {
            sVar8 = sVar8 + -1000;
          }
          if (sVar8 == 100) {
            sVar8 = -1;
          }
          SelectFunc__7BtlMenuFiiiP12EFCTCOMParam
                    (iStack_10,sVar8,3,*(undefined4 *)(iStack_10 + 0x2d4),iStack_258);
          *(byte *)(iStack_10 + 0x24) = *(byte *)(iStack_10 + 0x24) & 0xfd | 2;
          *(byte *)(iStack_10 + 0x24) = *(byte *)(iStack_10 + 0x24) & 0xfb | 4;
        }
        if ((uVar1 & 0x2000) != 0) {
          if (*(int *)(iStack_10 + 0x43c) < 1000) {
            sVar8 = (short)*(undefined4 *)(iStack_10 + 0x440);
            if (sVar8 == 100) {
              sVar8 = -1;
            }
            *(undefined2 *)
             ((int)pCGpffff86b4 +
             (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x598) =
                 *(undefined2 *)(iStack_10 + 0xb58);
            *(undefined2 *)
             ((int)pCGpffff86b4 +
             (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x59a) =
                 *(undefined2 *)(iStack_10 + 0xb5a);
            *(short *)((int)pCGpffff86b4 +
                      (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x59c) =
                 (short)*(undefined4 *)(iStack_10 + 0x43c);
            *(undefined2 *)
             ((int)pCGpffff86b4 +
             (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x59e) = 0xffff;
            if (pcGpffff86ec != (code *)0x0) {
              (*pcGpffff86ec)(0x12,0,0xffffffffffffffff,0,0,0,uGpffff86e8);
            }
            if (pcGpffff86ec != (code *)0x0) {
              (*pcGpffff86ec)(6,*(undefined4 *)(iStack_10 + 0x2d0),sVar8,0,0,0,uGpffff86e8);
            }
            if (*(int *)(iStack_10 + 0xb38) != 0) {
              (**(code **)(*(int *)(*(int *)(iStack_10 + 0xb38) + 0x14) + 0x30))();
            }
            *(undefined4 *)(iStack_10 + 0xb38) = 0;
            if (*(int *)(iStack_10 + 0xb3c) != 0) {
              (**(code **)(*(int *)(*(int *)(iStack_10 + 0xb3c) + 0x14) + 0x30))();
            }
            *(undefined4 *)(iStack_10 + 0xb3c) = 0;
            AllWindowClose__7BtlMenuFv(iStack_10);
            AllBCurDestruct__7BtlMenuFv();
            *(undefined2 *)(iStack_10 + 0x28) = 0x14;
            *(undefined2 *)(iStack_10 + 0x2a) = 0;
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,2,1,0);
            return 0;
          }
          PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,4,1,0);
        }
        if ((uVar1 & 0x4000) != 0) {
          *(undefined2 *)(iStack_10 + 0x2a) = 2;
          puStack_38c = pCGpffff86b4->pTurnOrderDisp;
          *(undefined4 *)(puStack_38c + 100) = 0;
          if (pcGpffff86ec != (code *)0x0) {
            (*pcGpffff86ec)(0x12,0,0xffffffffffffffff,0,0,0,uGpffff86e8);
          }
          if (*(int *)(iStack_10 + 0xb38) != 0) {
            (**(code **)(*(int *)(*(int *)(iStack_10 + 0xb38) + 0x14) + 0x30))();
          }
          *(undefined4 *)(iStack_10 + 0xb38) = 0;
          if (*(int *)(iStack_10 + 0xb3c) != 0) {
            (**(code **)(*(int *)(*(int *)(iStack_10 + 0xb3c) + 0x14) + 0x30))();
          }
          *(undefined4 *)(iStack_10 + 0xb3c) = 0;
          if (pcGpffff86ec != (code *)0x0) {
            (*pcGpffff86ec)(3,0,0,0,0,0,uGpffff86e8);
          }
          PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,3,1,0);
        }
      }
    }
    else if (((sVar8 == 0) && (*(short *)(iStack_10 + 0x30a) != 0xc)) &&
            (*(short *)(iStack_10 + 0x30a) != 0xd)) {
      *(byte *)(iStack_10 + 0x25) = *(byte *)(iStack_10 + 0x25) & 0xf7 | 8;
      SetWindowMove__7BtlMenuFii(iStack_10,0,2);
      SetWindowMove__7BtlMenuFii(iStack_10,1,1);
      SetTargetMenu__7BtlMenuFiiiP12EFCTCOMParamii
                (iStack_10,2,3,*(undefined4 *)(iStack_10 + 0x2d4),iStack_258,0xffffffffffffffff,
                 *(undefined2 *)(iStack_10 + 0xb5c));
      CreateCursole__7BtlMenuFv(iStack_10);
      Select__6CursorFP9MenuPlace(iStack_10 + 0xa34,
                      *(int *)(iStack_10 + 0x408) + *(int *)(iStack_10 + 0x430) * 0x80);
      QuickMove__6CursorFv(iStack_10 + 0xa34);
      uVar6 = SetWindowClose__7BtlMenuFii(iStack_10,3,6);
      SetNoteWindow__7BtlMenuFPc(iStack_10,uRam0040af50,uVar6);
      *(undefined2 *)(iStack_10 + 0x2a) = 1;
      *(byte *)(iStack_10 + 0x24) = *(byte *)(iStack_10 + 0x24) & 0xfd;
      *(byte *)(iStack_10 + 0x24) = *(byte *)(iStack_10 + 0x24) & 0xfb;
    }
    break;
  case 6:
    if (*(short *)(iStack_10 + 0x2a) == 1) {
      if (((*(short *)(iStack_10 + 0x30a) == 1) || (*(short *)(iStack_10 + 0x30a) == 2)) ||
         (*(short *)(iStack_10 + 0x30a) == 5)) {
        iStack_5d0 = *(int *)(iStack_10 + 0xb20);
        sVar8 = *(short *)(iStack_5d0 + 0x16);
        bVar18 = false;
        iVar7 = 0;
        iStack_390 = iStack_5d0;
        sStack_aa = sVar8;
        sStack_a8 = sVar8;
        if ((uVar2 & 0x10) != 0) {
          bVar18 = true;
          iStack_5d4 = *(int *)(iStack_10 + 0xb20);
          sStack_ae = *(short *)(iStack_5d4 + 0x1e);
          iStack_394 = iStack_5d4;
          sStack_ac = sStack_ae;
          if (sStack_ae < 1) {
            iVar7 = 1;
          }
          else {
            MoveCursor__6CursorFi(iStack_10 + 0xa34,1);
            *(int *)(iStack_10 + 0x444) = *(int *)(iStack_10 + 0x444) + -1;
            iStack_5d8 = *(int *)(iStack_10 + 0xb20);
            sStack_b2 = *(short *)(iStack_5d8 + 0x16);
            *(int *)(iStack_10 + 0x440) = (int)sStack_b2;
            iStack_398 = iStack_5d8;
            sStack_b0 = sStack_b2;
          }
        }
        if ((uVar2 & 0x40) != 0) {
          bVar18 = true;
          iStack_5dc = *(int *)(iStack_10 + 0xb20);
          sStack_b6 = *(short *)(iStack_5dc + 0x1e);
          iStack_39c = iStack_5dc;
          sStack_b4 = sStack_b6;
          if ((sStack_b6 + 1 < 4) && (*(int *)(iStack_10 + 0x444) + 1 < *(int *)(iStack_10 + 0x448))
             ) {
            MoveCursor__6CursorFi(iStack_10 + 0xa34,2);
            *(int *)(iStack_10 + 0x444) = *(int *)(iStack_10 + 0x444) + 1;
            iStack_5e0 = *(int *)(iStack_10 + 0xb20);
            sStack_ba = *(short *)(iStack_5e0 + 0x16);
            *(int *)(iStack_10 + 0x440) = (int)sStack_ba;
            iStack_3a0 = iStack_5e0;
            sStack_b8 = sStack_ba;
          }
          else {
            iVar7 = 2;
          }
        }
        bVar3 = false;
        if (((uVar2 & 0x500) != 0) && (0 < *(int *)(iStack_10 + 0x444))) {
          bVar3 = true;
          iVar7 = *(int *)(iStack_10 + 0x444) + -4;
          if (iVar7 < 0) {
            iVar7 = 0;
          }
          *(int *)(iStack_10 + 0x444) = iVar7;
          if (iVar7 < 0) {
            iVar7 = iVar7 + 3;
          }
          *(int *)(iStack_10 + 0x44c) = iVar7 >> 2;
          iVar7 = 3;
        }
        bVar16 = false;
        if (((uVar2 & 0xa00) != 0) &&
           (*(int *)(iStack_10 + 0x444) + 1 < *(int *)(iStack_10 + 0x448))) {
          bVar16 = true;
          iVar7 = *(int *)(iStack_10 + 0x444) + 4;
          if (*(int *)(iStack_10 + 0x448) <= iVar7) {
            iVar7 = *(int *)(iStack_10 + 0x448) + -1;
          }
          *(int *)(iStack_10 + 0x444) = iVar7;
          if (iVar7 < 0) {
            iVar7 = iVar7 + 3;
          }
          *(int *)(iStack_10 + 0x44c) = iVar7 >> 2;
          iVar7 = 3;
        }
        if (iVar7 != 0) {
          if (iVar7 == 1) {
            *(int *)(iStack_10 + 0x444) = *(int *)(iStack_10 + 0x444) + -1;
            *(int *)(iStack_10 + 0x44c) = *(int *)(iStack_10 + 0x44c) + -1;
            if (*(int *)(iStack_10 + 0x44c) < 0) {
              *(int *)(iStack_10 + 0x444) = *(int *)(iStack_10 + 0x448) + -1;
              iVar7 = *(int *)(iStack_10 + 0x448);
              if (iVar7 < 0) {
                iVar7 = iVar7 + 3;
              }
              *(int *)(iStack_10 + 0x44c) = iVar7 >> 2;
            }
          }
          else if (iVar7 == 2) {
            *(int *)(iStack_10 + 0x444) = *(int *)(iStack_10 + 0x444) + 1;
            *(int *)(iStack_10 + 0x44c) = *(int *)(iStack_10 + 0x44c) + 1;
            if (*(int *)(iStack_10 + 0x448) <= *(int *)(iStack_10 + 0x444)) {
              *(undefined4 *)(iStack_10 + 0x444) = 0;
              *(undefined4 *)(iStack_10 + 0x44c) = 0;
            }
          }
          SetDamageTypeMenu__7BtlMenuFiii
                    (iStack_10,2,*(undefined4 *)(iStack_10 + 0x444),0xffffffffffffffff);
          Select__6CursorFP9MenuPlace(iStack_10 + 0xa34,
                          *(int *)(iStack_10 + 0x408) + *(int *)(iStack_10 + 0x430) * 0x80);
        }
        iStack_5e4 = *(int *)(iStack_10 + 0xb20);
        sStack_be = *(short *)(iStack_5e4 + 0x16);
        iStack_3a4 = iStack_5e4;
        sStack_bc = sStack_be;
        if (sVar8 != sStack_be) {
          uVar12 = *(uint *)(iStack_10 + 0x444) & 3;
          if (((int)*(uint *)(iStack_10 + 0x444) < 0) && (uVar12 != 0)) {
            uVar12 = uVar12 - 4;
          }
          *(uint *)(iStack_10 + 0x430) = uVar12;
          *(undefined4 *)(iStack_10 + 0x43c) = *(undefined4 *)(iStack_10 + 0x440);
          SetNoteWindow__7BtlMenuFPc
                    (iStack_10,*(undefined4 *)(iRam0040ab38 + *(int *)(iStack_10 + 0x440) * 4),4);
          if (bVar18) {
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,0,1,0);
          }
          else if (bVar3) {
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,7,1,0);
          }
          else if (bVar16) {
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,6,1,0);
          }
        }
        if ((uVar1 & 0x2000) == 0) {
          if ((uVar1 & 0x4000) == 0) {
            if ((((long)((ulong)*(byte *)(ourBtlSaveDat + 3) << 0x3e) < 0) &&
                ((*(byte *)((int)pCGpffff86b4 +
                           (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb4)
                 & 1) == 0)) && ((uVar1 & 0x1000) != 0)) {
              *(undefined2 *)(iStack_10 + 0xb4c) = *(undefined2 *)(iStack_10 + 0x28);
              *(undefined2 *)(iStack_10 + 0xb4e) = *(undefined2 *)(iStack_10 + 0x2a);
              *(undefined2 *)(iStack_10 + 0xb50) = 3;
              *(undefined2 *)(iStack_10 + 0xb52) = 2;
              *(undefined1 *)(iStack_10 + 0xb54) = 1;
              *(char *)(iStack_10 + 0xb55) = (char)*(undefined4 *)(iStack_10 + 0x43c);
              *(short *)(iStack_10 + 0xb56) = (short)*(undefined4 *)(iStack_10 + 0x2d0);
              *(undefined2 *)(iStack_10 + 0x28) = 0x18;
              *(undefined2 *)(iStack_10 + 0x2a) = 0;
              PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,2,1,0);
              return 0;
            }
          }
          else {
            *(undefined2 *)(iStack_10 + 0x28) = 4;
            *(undefined2 *)(iStack_10 + 0x2a) = 0;
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,3,1,0);
          }
        }
        else {
          if ((long)*(short *)(iStack_10 + 0xb5c) != (long)*(int *)(iStack_10 + 0x43c)) {
            *(undefined2 *)(iStack_10 + 0xb5e) = 0xffff;
          }
          *(short *)(iStack_10 + 0xb5c) = (short)*(undefined4 *)(iStack_10 + 0x43c);
          *(undefined2 *)(iStack_10 + 0x28) = 7;
          *(undefined2 *)(iStack_10 + 0x2a) = 0;
          PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,2,1,0);
        }
      }
    }
    else if (((*(short *)(iStack_10 + 0x2a) == 0) && (*(short *)(iStack_10 + 0x30a) != 0xc)) &&
            (*(short *)(iStack_10 + 0x30a) != 0xd)) {
      *(byte *)(iStack_10 + 0x25) = *(byte *)(iStack_10 + 0x25) & 0xf7;
      SetWindowMove__7BtlMenuFii(iStack_10,0,2);
      SetWindowMove__7BtlMenuFii(iStack_10,1,1);
      SetDamageTypeMenu__7BtlMenuFiii
                (iStack_10,2,0xffffffffffffffff,*(undefined2 *)(iStack_10 + 0xb5c));
      CreateCursole__7BtlMenuFv(iStack_10);
      Select__6CursorFP9MenuPlace(iStack_10 + 0xa34,
                      *(int *)(iStack_10 + 0x408) + *(int *)(iStack_10 + 0x430) * 0x80);
      QuickMove__6CursorFv(iStack_10 + 0xa34);
      SetWindowClose__7BtlMenuFii(iStack_10,3,6);
      SetNoteWindow__7BtlMenuFPc
                (iStack_10,*(undefined4 *)(iRam0040ab38 + *(int *)(iStack_10 + 0x440) * 4));
      AllBCurDestruct__7BtlMenuFv();
      *(undefined2 *)(iStack_10 + 0x2a) = 1;
      *(byte *)(iStack_10 + 0x24) = *(byte *)(iStack_10 + 0x24) & 0xfd;
    }
    break;
  case 7:
    iStack_260 = GetRegDat__9RegDatApiFiii(0x33,0,0xffffffffffffffff);
    iStack_264 = iStack_260 + *(int *)(iStack_10 + 0x2d4) * 0x30;
    uStack_11 = 0;
    iStack_268 = iStack_264 + 8;
    if (((*(byte *)(iStack_264 + 0xb) >> 4 == 1) &&
        ((long)((ulong)*(byte *)(iStack_264 + 0xb) << 0x3c) < 0)) &&
       (*(char *)(iStack_264 + 10) == '(')) {
      uStack_11 = 1;
    }
    iStack_26c = GetRegDat__9RegDatApiFiii(0x3e,0,0xffffffffffffffff);
    sVar8 = *(short *)(iStack_10 + 0x2a);
    if (sVar8 == 2) {
      *(undefined2 *)(iStack_10 + 0x28) = 6;
      *(undefined2 *)(iStack_10 + 0x2a) = 0;
      AllBCurDestruct__7BtlMenuFv();
    }
    else if (sVar8 == 1) {
      if (((*(short *)(iStack_10 + 0x476) == 1) || (*(short *)(iStack_10 + 0x476) == 2)) ||
         (*(short *)(iStack_10 + 0x476) == 5)) {
        if ((long)((ulong)*(byte *)(iStack_10 + 0x24) << 0x3d) < 0) {
          sVar8 = (short)*(undefined4 *)(iStack_10 + 0x5ac);
          if (999 < sVar8) {
            sVar8 = sVar8 + -1000;
          }
          if (sVar8 == 100) {
            sVar8 = -1;
          }
          DelaySelectFunc__7BtlMenuFiiiP12EFCTCOMParam(iStack_10,sVar8,0,0,0);
          *(byte *)(iStack_10 + 0x24) = *(byte *)(iStack_10 + 0x24) & 0xfb;
        }
        iStack_5e8 = *(int *)(iStack_10 + 0xb20);
        sVar8 = *(short *)(iStack_5e8 + 0x16);
        bVar18 = false;
        iVar7 = 0;
        iStack_3a8 = iStack_5e8;
        sStack_c2 = sVar8;
        sStack_c0 = sVar8;
        if ((uVar2 & 0x10) != 0) {
          bVar18 = true;
          iStack_5ec = *(int *)(iStack_10 + 0xb20);
          sStack_c6 = *(short *)(iStack_5ec + 0x1e);
          iStack_3ac = iStack_5ec;
          sStack_c4 = sStack_c6;
          if (sStack_c6 < 1) {
            iVar7 = 1;
          }
          else {
            MoveCursor__6CursorFi(iStack_10 + 0xa34,1);
            *(int *)(iStack_10 + 0x5b0) = *(int *)(iStack_10 + 0x5b0) + -1;
            iStack_5f0 = *(int *)(iStack_10 + 0xb20);
            sStack_ca = *(short *)(iStack_5f0 + 0x16);
            *(int *)(iStack_10 + 0x5ac) = (int)sStack_ca;
            iStack_3b0 = iStack_5f0;
            sStack_c8 = sStack_ca;
          }
        }
        if ((uVar2 & 0x40) != 0) {
          bVar18 = true;
          iStack_5f4 = *(int *)(iStack_10 + 0xb20);
          sStack_ce = *(short *)(iStack_5f4 + 0x1e);
          iStack_3b4 = iStack_5f4;
          sStack_cc = sStack_ce;
          if ((sStack_ce + 1 < 4) && (*(int *)(iStack_10 + 0x5b0) + 1 < *(int *)(iStack_10 + 0x5b4))
             ) {
            MoveCursor__6CursorFi(iStack_10 + 0xa34,2);
            *(int *)(iStack_10 + 0x5b0) = *(int *)(iStack_10 + 0x5b0) + 1;
            iStack_5f8 = *(int *)(iStack_10 + 0xb20);
            sStack_d2 = *(short *)(iStack_5f8 + 0x16);
            *(int *)(iStack_10 + 0x5ac) = (int)sStack_d2;
            iStack_3b8 = iStack_5f8;
            sStack_d0 = sStack_d2;
          }
          else {
            iVar7 = 2;
          }
        }
        bVar3 = false;
        if (((uVar2 & 0x500) != 0) && (0 < *(int *)(iStack_10 + 0x5b0))) {
          bVar3 = true;
          iVar7 = *(int *)(iStack_10 + 0x5b0) + -4;
          if (iVar7 < 0) {
            iVar7 = 0;
          }
          *(int *)(iStack_10 + 0x5b0) = iVar7;
          if (iVar7 < 0) {
            iVar7 = iVar7 + 3;
          }
          *(int *)(iStack_10 + 0x5b8) = iVar7 >> 2;
          iVar7 = 3;
        }
        bVar16 = false;
        if (((uVar2 & 0xa00) != 0) &&
           (*(int *)(iStack_10 + 0x5b0) + 1 < *(int *)(iStack_10 + 0x5b4))) {
          bVar16 = true;
          iVar7 = *(int *)(iStack_10 + 0x5b0) + 4;
          if (*(int *)(iStack_10 + 0x5b4) <= iVar7) {
            iVar7 = *(int *)(iStack_10 + 0x5b4) + -1;
          }
          *(int *)(iStack_10 + 0x5b0) = iVar7;
          if (iVar7 < 0) {
            iVar7 = iVar7 + 3;
          }
          *(int *)(iStack_10 + 0x5b8) = iVar7 >> 2;
          iVar7 = 3;
        }
        if (iVar7 != 0) {
          if (iVar7 == 1) {
            *(int *)(iStack_10 + 0x5b0) = *(int *)(iStack_10 + 0x5b0) + -1;
            *(int *)(iStack_10 + 0x5b8) = *(int *)(iStack_10 + 0x5b8) + -1;
            if (*(int *)(iStack_10 + 0x5b8) < 0) {
              *(int *)(iStack_10 + 0x5b0) = *(int *)(iStack_10 + 0x5b4) + -1;
              iVar7 = *(int *)(iStack_10 + 0x5b4);
              if (iVar7 < 0) {
                iVar7 = iVar7 + 3;
              }
              *(int *)(iStack_10 + 0x5b8) = iVar7 >> 2;
            }
          }
          else if (iVar7 == 2) {
            *(int *)(iStack_10 + 0x5b0) = *(int *)(iStack_10 + 0x5b0) + 1;
            *(int *)(iStack_10 + 0x5b8) = *(int *)(iStack_10 + 0x5b8) + 1;
            if (*(int *)(iStack_10 + 0x5b4) <= *(int *)(iStack_10 + 0x5b0)) {
              *(undefined4 *)(iStack_10 + 0x5b0) = 0;
              *(undefined4 *)(iStack_10 + 0x5b8) = 0;
            }
          }
          SetTargetMenu__7BtlMenuFiiiP12EFCTCOMParamii
                    (iStack_10,3,0,0,0,*(undefined4 *)(iStack_10 + 0x5b0),0xffffffffffffffff);
          Select__6CursorFP9MenuPlace(iStack_10 + 0xa34,
                          *(int *)(iStack_10 + 0x574) + *(int *)(iStack_10 + 0x59c) * 0x80);
        }
        iStack_5fc = *(int *)(iStack_10 + 0xb20);
        sVar13 = *(short *)(iStack_5fc + 0x16);
        iStack_3bc = iStack_5fc;
        sStack_d6 = sVar13;
        sStack_d4 = sVar13;
        if (sVar8 != sVar13) {
          uVar12 = *(uint *)(iStack_10 + 0x5b0) & 3;
          if (((int)*(uint *)(iStack_10 + 0x5b0) < 0) && (uVar12 != 0)) {
            uVar12 = uVar12 - 4;
          }
          *(uint *)(iStack_10 + 0x59c) = uVar12;
          *(undefined4 *)(iStack_10 + 0x5a8) = *(undefined4 *)(iStack_10 + 0x5ac);
          if (bVar18) {
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,0,1,0);
          }
          else if (bVar3) {
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,7,1,0);
          }
          else if (bVar16) {
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,6,1,0);
          }
        }
        if ((sVar8 != sVar13) || (-1 < (long)((ulong)*(byte *)(iStack_10 + 0x24) << 0x3e))) {
          sVar8 = (short)*(undefined4 *)(iStack_10 + 0x5ac);
          if (999 < sVar8) {
            sVar8 = sVar8 + -1000;
          }
          if (sVar8 == 100) {
            sVar8 = -1;
          }
          SelectFunc__7BtlMenuFiiiP12EFCTCOMParam(iStack_10,sVar8,0,0,0);
          iStack_22c = 1;
          aiStack_7a0[0] = *(int *)(iStack_10 + 0x5ac);
          if (((*(byte *)((int)pCGpffff86b4 +
                         (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb4) &
               1) == 0) &&
             (-1 < *(char *)(ourBtlSaveDat +
                             *(short *)((int)pCGpffff86b4 +
                                       (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) *
                                       0x10 + 0x120) * 0xc0 + 0xa8))) {
            MakeTurnOrderTable__7CBattleFfiPiiiPUisibi
                      (pCGpffff86b4,(float)*(ushort *)(iStack_264 + 0x1a) / 100.0,1,aiStack_7a0,3,
                       *(int *)(iStack_10 + 0x2d4),
                       (uint *)(iStack_26c +
                                *(char *)(ourBtlSaveDat +
                                          *(short *)((int)pCGpffff86b4 +
                                                    (pCGpffff86b4->cActor * 0x50 -
                                                    (int)pCGpffff86b4->cActor) * 0x10 + 0x120) *
                                          0xc0 + 0xa8) * 0x20 + 4),(short)pCGpffff86b4->cActor,-1,
                       true,-2);
          }
          else {
            MakeTurnOrderTable__7CBattleFfiPiiiPUisibi
                      (pCGpffff86b4,(float)*(ushort *)(iStack_264 + 0x1a) / 100.0,1,aiStack_7a0,3,
                       *(int *)(iStack_10 + 0x2d4),(uint *)0x0,(short)pCGpffff86b4->cActor,-1,true,
                       -2);
          }
          *(byte *)(iStack_10 + 0x24) = *(byte *)(iStack_10 + 0x24) & 0xfd | 2;
          *(byte *)(iStack_10 + 0x24) = *(byte *)(iStack_10 + 0x24) & 0xfb | 4;
        }
        if ((uVar1 & 0x2000) != 0) {
          if (*(int *)(iStack_10 + 0x5ac) < 1000) {
            sVar8 = (short)*(undefined4 *)(iStack_10 + 0x5ac);
            if (sVar8 == 100) {
              sVar8 = -1;
            }
            *(undefined2 *)
             ((int)pCGpffff86b4 +
             (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x598) =
                 *(undefined2 *)(iStack_10 + 0xb58);
            *(undefined2 *)
             ((int)pCGpffff86b4 +
             (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x59a) =
                 *(undefined2 *)(iStack_10 + 0xb5a);
            *(undefined2 *)
             ((int)pCGpffff86b4 +
             (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x59c) =
                 *(undefined2 *)(iStack_10 + 0xb5c);
            *(short *)((int)pCGpffff86b4 +
                      (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x59e) =
                 (short)*(undefined4 *)(iStack_10 + 0x5a8);
            if (pcGpffff86ec != (code *)0x0) {
              (*pcGpffff86ec)(0x12,0,0xffffffffffffffff,0,0,0,uGpffff86e8);
            }
            if (pcGpffff86ec != (code *)0x0) {
              (*pcGpffff86ec)(4,sVar8,*(undefined4 *)(iStack_10 + 0x43c),
                              *(undefined4 *)(iStack_264 + 0xc),*(undefined4 *)(iStack_10 + 0x2d4),0
                              ,uGpffff86e8);
            }
            if (*(int *)(iStack_10 + 0xb38) != 0) {
              (**(code **)(*(int *)(*(int *)(iStack_10 + 0xb38) + 0x14) + 0x30))();
            }
            *(undefined4 *)(iStack_10 + 0xb38) = 0;
            AllWindowClose__7BtlMenuFv(iStack_10);
            AllBCurDestruct__7BtlMenuFv();
            *(undefined2 *)(iStack_10 + 0x28) = 0x14;
            *(undefined2 *)(iStack_10 + 0x2a) = 0;
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,2,1,0);
            return 0;
          }
          PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,4,1,0);
        }
        if ((uVar1 & 0x4000) != 0) {
          *(undefined2 *)(iStack_10 + 0x2a) = 2;
          puStack_3c0 = pCGpffff86b4->pTurnOrderDisp;
          *(undefined4 *)(puStack_3c0 + 100) = 0;
          if (pcGpffff86ec != (code *)0x0) {
            (*pcGpffff86ec)(0x12,0,0xffffffffffffffff,0,0,0,uGpffff86e8);
          }
          if (*(int *)(iStack_10 + 0xb38) != 0) {
            (**(code **)(*(int *)(*(int *)(iStack_10 + 0xb38) + 0x14) + 0x30))();
          }
          *(undefined4 *)(iStack_10 + 0xb38) = 0;
          if (pcGpffff86ec != (code *)0x0) {
            (*pcGpffff86ec)(3,0,0,0,0,0,uGpffff86e8);
          }
          PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,3,1,0);
        }
      }
    }
    else if (((sVar8 == 0) && (*(short *)(iStack_10 + 0x476) != 0xc)) &&
            (*(short *)(iStack_10 + 0x476) != 0xd)) {
      *(byte *)(iStack_10 + 0x25) = *(byte *)(iStack_10 + 0x25) & 0xf7 | 8;
      SetWindowMove__7BtlMenuFii(iStack_10,0,3);
      SetWindowMove__7BtlMenuFii(iStack_10,1,2);
      SetWindowMove__7BtlMenuFii(iStack_10,2,1);
      SetTargetMenu__7BtlMenuFiiiP12EFCTCOMParamii
                (iStack_10,3,0,0,0,0xffffffffffffffff,*(undefined2 *)(iStack_10 + 0xb5e));
      CreateCursole__7BtlMenuFv(iStack_10);
      Select__6CursorFP9MenuPlace(iStack_10 + 0xa34,
                      *(int *)(iStack_10 + 0x574) + *(int *)(iStack_10 + 0x59c) * 0x80);
      QuickMove__6CursorFv(iStack_10 + 0xa34);
      SetWindowClose__7BtlMenuFii(iStack_10,4,6);
      SetNoteWindow__7BtlMenuFPc(iStack_10,uRam0040af44);
      AllBCurDestruct__7BtlMenuFv();
      *(undefined2 *)(iStack_10 + 0x2a) = 1;
      *(byte *)(iStack_10 + 0x24) = *(byte *)(iStack_10 + 0x24) & 0xfd;
      *(byte *)(iStack_10 + 0x24) = *(byte *)(iStack_10 + 0x24) & 0xfb;
    }
    break;
  case 8:
    if (*(short *)(iStack_10 + 0x2a) != 1) {
      if (*(short *)(iStack_10 + 0x2a) != 0) {
        return 0;
      }
      if (*(short *)(iStack_10 + 0x19e) == 0xc) {
        return 0;
      }
      if (*(short *)(iStack_10 + 0x19e) == 0xd) {
        return 0;
      }
      SetWindowMove__7BtlMenuFii(iStack_10,0,1);
      if (*(int *)(iStack_10 + 0x140) != 0) {
        SetMark__10ScrollMarkFUc(*(undefined4 *)(iStack_10 + 0x140),0);
      }
      uVar6 = SetGuardMenu__7BtlMenuFii(iStack_10,1,*(undefined2 *)(iStack_10 + 0xb5a));
      CreateCursole__7BtlMenuFv(iStack_10,uVar6);
      Select__6CursorFP9MenuPlace(iStack_10 + 0xa34,
                      *(int *)(iStack_10 + 0x29c) + *(int *)(iStack_10 + 0x2c4) * 0x80);
      QuickMove__6CursorFv(iStack_10 + 0xa34);
      SetWindowClose__7BtlMenuFii(iStack_10,2,6);
      SetNoteWindow__7BtlMenuFPc
                (iStack_10,*(undefined4 *)(iRam0040ab40 + *(int *)(iStack_10 + 0x2d0) * 4));
      AllBCurDestruct__7BtlMenuFv();
      *(undefined2 *)(iStack_10 + 0x2a) = 1;
      *(byte *)(iStack_10 + 0x24) = *(byte *)(iStack_10 + 0x24) & 0xfd;
      return 0;
    }
    if (((*(short *)(iStack_10 + 0x19e) != 1) && (*(short *)(iStack_10 + 0x19e) != 2)) &&
       (*(short *)(iStack_10 + 0x19e) != 5)) {
      return 0;
    }
    iStack_600 = *(int *)(iStack_10 + 0xb20);
    sVar8 = *(short *)(iStack_600 + 0x16);
    iStack_604 = *(int *)(iStack_10 + 0xb20);
    sVar13 = *(short *)(iStack_604 + 0x1e);
    iStack_3c8 = iStack_604;
    iStack_3c4 = iStack_600;
    sStack_de = sVar13;
    sStack_dc = sVar13;
    sStack_da = sVar8;
    sStack_d8 = sVar8;
    if (((uVar2 & 0x10) != 0) || ((sVar13 != 0 && ((uVar2 & 0x500) != 0)))) {
      MoveCursor__6CursorFi(iStack_10 + 0xa34,1);
      iStack_608 = *(int *)(iStack_10 + 0xb20);
      sVar13 = *(short *)(iStack_608 + 0x1e);
      iStack_3cc = iStack_608;
      sStack_e2 = sVar13;
      sStack_e0 = sVar13;
    }
    if (((uVar2 & 0x40) != 0) || ((sVar13 == 0 && ((uVar2 & 0xa00) != 0)))) {
      MoveCursor__6CursorFi(iStack_10 + 0xa34,2);
    }
    iStack_60c = *(int *)(iStack_10 + 0xb20);
    sVar13 = *(short *)(iStack_60c + 0x16);
    iStack_3d0 = iStack_60c;
    sStack_e6 = sVar13;
    sStack_e4 = sVar13;
    if (sVar13 == sVar8) {
      if (-1 < (long)((ulong)*(byte *)(iStack_10 + 0x24) << 0x3e)) goto code_r0x00594c88;
    }
    else {
      *(int *)(iStack_10 + 0x2d0) = (int)sVar13;
      SetNoteWindow__7BtlMenuFPc(iStack_10,*(undefined4 *)(iRam0040ab40 + sVar13 * 4));
      PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,0,1,0);
code_r0x00594c88:
      if (sVar13 == 1) {
        MakeTurnOrderTable__7CBattleFfiPiiiPUisibi
                  (pCGpffff86b4,2.5,0,(int *)0x0,0,0,(uint *)0x0,(short)pCGpffff86b4->cActor,-1,true
                   ,-2);
      }
      else if (sVar13 == 0) {
        MakeTurnOrderTable__7CBattleFfiPiiiPUisibi
                  (pCGpffff86b4,2.0,0,(int *)0x0,0,0,(uint *)0x0,(short)pCGpffff86b4->cActor,-1,true
                   ,-2);
      }
      *(byte *)(iStack_10 + 0x24) = *(byte *)(iStack_10 + 0x24) & 0xfd | 2;
    }
    if ((uVar1 & 0x2000) == 0) {
      if ((uVar1 & 0x4000) != 0) {
        *(undefined2 *)(iStack_10 + 0x28) = 0;
        *(undefined2 *)(iStack_10 + 0x2a) = 0;
        PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,3,1,0);
      }
    }
    else {
      *(undefined2 *)
       ((int)pCGpffff86b4 + (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x598
       ) = *(undefined2 *)(iStack_10 + 0xb58);
      *(short *)((int)pCGpffff86b4 +
                (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x59a) =
           (short)*(undefined4 *)(iStack_10 + 0x2d0);
      *(undefined2 *)
       ((int)pCGpffff86b4 + (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x59c
       ) = 0xffff;
      *(undefined2 *)
       ((int)pCGpffff86b4 + (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x59e
       ) = 0xffff;
      if (pcGpffff86ec != (code *)0x0) {
        (*pcGpffff86ec)(7,*(undefined4 *)(iStack_10 + 0x2d0),0,0,0,0,uGpffff86e8);
      }
      AllWindowClose__7BtlMenuFv(iStack_10);
      AllBCurDestruct__7BtlMenuFv();
      *(undefined2 *)(iStack_10 + 0x28) = 0x14;
      *(undefined2 *)(iStack_10 + 0x2a) = 0;
      PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,2,1,0);
    }
    break;
  case 9:
    sVar8 = *(short *)(iStack_10 + 0x2a);
    if (sVar8 == 2) {
      *(undefined2 *)(iStack_10 + 0x28) = 0;
      *(undefined2 *)(iStack_10 + 0x2a) = 0;
      AllBCurDestruct__7BtlMenuFv();
    }
    else if (sVar8 == 1) {
      if (((*(short *)(iStack_10 + 0x19e) == 1) || (*(short *)(iStack_10 + 0x19e) == 2)) ||
         (*(short *)(iStack_10 + 0x19e) == 5)) {
        if ((*(short *)(iStack_10 + 0xb44) == 0x14) && (*(short *)(iStack_10 + 0xb46) == 3)) {
          uVar5 = 0;
          *(float *)(iStack_10 + 0xb48) = *(float *)(iStack_10 + 0xb48) - pCGpffff86b4->flDeltaT;
          if (*(float *)(iStack_10 + 0xb48) <= 0.0) {
            *(undefined4 *)(iStack_10 + 0xb48) = 0x3e800000;
            iVar7 = -1;
            for (iVar10 = 0; iVar10 < 0xc; iVar10 = iVar10 + 1) {
              if (((((pCGpffff86b4->aChr[iVar10].bFlagsA & 1) != 0) &&
                   ((long)((ulong)pCGpffff86b4->aChr[iVar10].bFlagsA << 0x3e) < 0)) &&
                  (-1 < (long)((ulong)pCGpffff86b4->aChr[iVar10].bFlagsA2 << 0x3d))) &&
                 (((pCGpffff86b4->aChr[iVar10].bFlagsB & 1) == 0 &&
                  (pCGpffff86b4->aChr[iVar10].nCharId == 5)))) {
                iVar7 = iVar10;
              }
            }
            iStack_610 = *(int *)(iStack_10 + 0xb20);
            uStack_ea = *(undefined2 *)(iStack_610 + 0x1e);
            iStack_3d4 = iStack_610;
            uStack_e8 = uStack_ea;
            uVar5 = AutoMenuFunc__7BtlMenuFiiiii(iStack_10,1,0,uStack_ea,iVar7,0xffffffffffffffff);
            if ((uVar5 & 0x2000) == 0) {
              *(byte *)(iStack_10 + 0x25) = *(byte *)(iStack_10 + 0x25) & 0xfb;
            }
            else if ((long)((ulong)*(byte *)(iStack_10 + 0x25) << 0x3d) < 0) {
              *(undefined2 *)(iStack_10 + 0xb46) = 4;
              *(undefined4 *)(iStack_10 + 0xb48) = 0x3f800000;
            }
            else {
              uVar5 = 0;
              *(undefined4 *)(iStack_10 + 0xb48) = 0x3f400000;
              *(byte *)(iStack_10 + 0x25) = *(byte *)(iStack_10 + 0x25) & 0xfb | 4;
            }
          }
        }
        lVar11 = (long)iStack_10;
        iStack_614 = *(int *)(iStack_10 + 0xb20);
        sVar8 = *(short *)(iStack_614 + 0x16);
        bVar18 = false;
        lVar15 = 0;
        iStack_3d8 = iStack_614;
        sStack_ee = sVar8;
        sStack_ec = sVar8;
        if ((uVar5 & 0x10) != 0) {
          bVar18 = true;
          iStack_618 = *(int *)(iStack_10 + 0xb20);
          lVar11 = (long)iStack_618;
          sStack_f2 = *(short *)(iStack_618 + 0x1e);
          iStack_3dc = iStack_618;
          sStack_f0 = sStack_f2;
          if (sStack_f2 < 1) {
            lVar15 = 1;
          }
          else {
            MoveCursor__6CursorFi(iStack_10 + 0xa34,1);
            *(int *)(iStack_10 + 0x2d8) = *(int *)(iStack_10 + 0x2d8) + -1;
            lVar11 = (long)iStack_10;
            iStack_61c = *(int *)(iStack_10 + 0xb20);
            sStack_f6 = *(short *)(iStack_61c + 0x16);
            *(int *)(iStack_10 + 0x2d4) = (int)sStack_f6;
            iStack_3e0 = iStack_61c;
            sStack_f4 = sStack_f6;
          }
        }
        if ((uVar5 & 0x40) != 0) {
          bVar18 = true;
          iStack_620 = *(int *)(iStack_10 + 0xb20);
          sStack_fa = *(short *)(iStack_620 + 0x1e);
          lVar11 = (long)sStack_fa;
          iStack_3e4 = iStack_620;
          sStack_f8 = sStack_fa;
          if ((sStack_fa + 1 < 4) && (*(int *)(iStack_10 + 0x2d8) + 1 < *(int *)(iStack_10 + 0x2dc))
             ) {
            lVar11 = MoveCursor__6CursorFi(iStack_10 + 0xa34,2);
            *(int *)(iStack_10 + 0x2d8) = *(int *)(iStack_10 + 0x2d8) + 1;
            iStack_624 = *(int *)(iStack_10 + 0xb20);
            sStack_fe = *(short *)(iStack_624 + 0x16);
            *(int *)(iStack_10 + 0x2d4) = (int)sStack_fe;
            iStack_3e8 = iStack_624;
            sStack_fc = sStack_fe;
          }
          else {
            lVar15 = 2;
          }
        }
        bVar3 = false;
        if (((uVar5 & 0x500) != 0) && (0 < *(int *)(iStack_10 + 0x2d8))) {
          bVar3 = true;
          iVar7 = *(int *)(iStack_10 + 0x2d8) + -4;
          if (iVar7 < 0) {
            iVar7 = 0;
          }
          *(int *)(iStack_10 + 0x2d8) = iVar7;
          if (iVar7 < 0) {
            iVar7 = iVar7 + 3;
          }
          *(int *)(iStack_10 + 0x2e0) = iVar7 >> 2;
          lVar11 = 3;
          lVar15 = lVar11;
        }
        bVar16 = false;
        if (((uVar5 & 0xa00) != 0) &&
           (*(int *)(iStack_10 + 0x2d8) + 1 < *(int *)(iStack_10 + 0x2dc))) {
          bVar16 = true;
          iVar7 = *(int *)(iStack_10 + 0x2d8) + 4;
          if (*(int *)(iStack_10 + 0x2dc) <= iVar7) {
            iVar7 = *(int *)(iStack_10 + 0x2dc) + -1;
          }
          *(int *)(iStack_10 + 0x2d8) = iVar7;
          if (iVar7 < 0) {
            iVar7 = iVar7 + 3;
          }
          lVar11 = (long)(iVar7 >> 2);
          *(int *)(iStack_10 + 0x2e0) = iVar7 >> 2;
          lVar15 = 3;
        }
        if (lVar15 != 0) {
          if (lVar15 == 1) {
            lVar11 = (long)*(int *)(iStack_10 + 0x2d8);
            *(int *)(iStack_10 + 0x2d8) = *(int *)(iStack_10 + 0x2d8) + -1;
            *(int *)(iStack_10 + 0x2e0) = *(int *)(iStack_10 + 0x2e0) + -1;
            if (*(int *)(iStack_10 + 0x2e0) < 0) {
              *(int *)(iStack_10 + 0x2d8) = *(int *)(iStack_10 + 0x2dc) + -1;
              iVar7 = *(int *)(iStack_10 + 0x2dc);
              iVar10 = iVar7 >> 2;
              if (iVar7 < 0) {
                iVar10 = iVar7 + 3 >> 2;
                lVar11 = (long)iVar10;
              }
              *(int *)(iStack_10 + 0x2e0) = iVar10;
            }
          }
          else if (lVar15 == 2) {
            *(int *)(iStack_10 + 0x2d8) = *(int *)(iStack_10 + 0x2d8) + 1;
            *(int *)(iStack_10 + 0x2e0) = *(int *)(iStack_10 + 0x2e0) + 1;
            if (*(int *)(iStack_10 + 0x2dc) <= *(int *)(iStack_10 + 0x2d8)) {
              *(undefined4 *)(iStack_10 + 0x2d8) = 0;
              lVar11 = (long)iStack_10;
              *(undefined4 *)(iStack_10 + 0x2e0) = 0;
            }
          }
          SetMoveMenu__7BtlMenuFiii
                    (iStack_10,1,*(undefined4 *)(iStack_10 + 0x2d8),0xffffffffffffffff,1,
                     0xffffffffffffffff,lVar11);
          Select__6CursorFP9MenuPlace(iStack_10 + 0xa34,
                          *(int *)(iStack_10 + 0x29c) + *(int *)(iStack_10 + 0x2c4) * 0x80);
        }
        iStack_628 = *(int *)(iStack_10 + 0xb20);
        sVar13 = *(short *)(iStack_628 + 0x16);
        iStack_3ec = iStack_628;
        sStack_102 = sVar13;
        sStack_100 = sVar13;
        if (sVar8 != sVar13) {
          uVar12 = *(uint *)(iStack_10 + 0x2d8) & 3;
          if (((int)*(uint *)(iStack_10 + 0x2d8) < 0) && (uVar12 != 0)) {
            uVar12 = uVar12 - 4;
          }
          *(uint *)(iStack_10 + 0x2c4) = uVar12;
          *(undefined4 *)(iStack_10 + 0x2d0) = *(undefined4 *)(iStack_10 + 0x2d4);
          if (bVar18) {
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,0,1,0);
          }
          else if (bVar3) {
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,7,1,0);
          }
          else if (bVar16) {
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,6,1,0);
          }
        }
        if ((sVar8 != sVar13) || (-1 < (long)((ulong)*(byte *)(iStack_10 + 0x24) << 0x3e))) {
          puStack_3f0 = pCGpffff86b4->pTurnOrderDisp;
          *(undefined4 *)(puStack_3f0 + 100) = 0;
          if (*(int *)(iStack_10 + 0x2d4) < 0x80) {
            uVar6 = SetSelectChr__13TurnOrderDispFii
                              (pCGpffff86b4->pTurnOrderDisp,*(undefined4 *)(iStack_10 + 0x2d4),1);
            SetNoteWindow__7BtlMenuFPc(iStack_10,*puRam0040ab44,uVar6);
          }
          else {
            SetSelectChr__13TurnOrderDispFii
                      (pCGpffff86b4->pTurnOrderDisp,*(int *)(iStack_10 + 0x2d4) + -0x74,1);
            SetNoteWindow__7BtlMenuFPc(iStack_10,puRam0040ab44[1]);
          }
          if (pcGpffff86ec != (code *)0x0) {
            (*pcGpffff86ec)(8,*(undefined4 *)(iStack_10 + 0x2d4),0,0,0,0,uGpffff86e8);
          }
          MakeCursole__7BtlMenuFiUcUcUcUcUcP7FVectori
                    (*(undefined4 *)(iStack_10 + 0x2d4),0,1,2,0,0,0,0);
          *(byte *)(iStack_10 + 0x24) = *(byte *)(iStack_10 + 0x24) & 0xfd | 2;
        }
        if ((uVar5 & 0x2000) == 0) {
          if ((uVar5 & 0x4000) != 0) {
            *(undefined2 *)(iStack_10 + 0x2a) = 2;
            puStack_3f4 = pCGpffff86b4->pTurnOrderDisp;
            *(undefined4 *)(puStack_3f4 + 100) = 0;
            if (pcGpffff86ec != (code *)0x0) {
              (*pcGpffff86ec)(3,0,0,0,0,0,uGpffff86e8);
            }
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,3,1,0);
          }
        }
        else {
          if ((long)*(short *)(iStack_10 + 0xb5a) != (long)*(int *)(iStack_10 + 0x2d0)) {
            *(undefined2 *)(iStack_10 + 0xb5e) = 0xffff;
            *(undefined2 *)(iStack_10 + 0xb5c) = 0xffff;
          }
          *(short *)(iStack_10 + 0xb5a) = (short)*(undefined4 *)(iStack_10 + 0x2d0);
          *(undefined2 *)(iStack_10 + 0x28) = 10;
          *(undefined2 *)(iStack_10 + 0x2a) = 0;
          PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,2,1,0);
        }
      }
    }
    else if (((sVar8 == 0) && (*(short *)(iStack_10 + 0x19e) != 0xc)) &&
            (*(short *)(iStack_10 + 0x19e) != 0xd)) {
      SetWindowMove__7BtlMenuFii(iStack_10,0,1);
      if (*(int *)(iStack_10 + 0x140) != 0) {
        SetMark__10ScrollMarkFUc(*(undefined4 *)(iStack_10 + 0x140),0);
      }
      SetMoveMenu__7BtlMenuFiii(iStack_10,1,0xffffffffffffffff,*(undefined2 *)(iStack_10 + 0xb5a));
      uVar6 = CreateCursole__7BtlMenuFv(iStack_10);
      Select__6CursorFP9MenuPlace(iStack_10 + 0xa34,
                      *(int *)(iStack_10 + 0x29c) + *(int *)(iStack_10 + 0x2c4) * 0x80,uVar6);
      QuickMove__6CursorFv(iStack_10 + 0xa34);
      SetWindowClose__7BtlMenuFii(iStack_10,2,6);
      AllBCurDestruct__7BtlMenuFv();
      *(undefined2 *)(iStack_10 + 0x2a) = 1;
      *(byte *)(iStack_10 + 0x24) = *(byte *)(iStack_10 + 0x24) & 0xfd;
    }
    break;
  case 10:
    if (*(short *)(iStack_10 + 0x2a) == 1) {
      if (((*(short *)(iStack_10 + 0x30a) == 1) || (*(short *)(iStack_10 + 0x30a) == 2)) ||
         (*(short *)(iStack_10 + 0x30a) == 5)) {
        if ((*(short *)(iStack_10 + 0xb44) == 0x14) && (*(short *)(iStack_10 + 0xb46) == 4)) {
          uVar5 = 0;
          *(float *)(iStack_10 + 0xb48) = *(float *)(iStack_10 + 0xb48) - pCGpffff86b4->flDeltaT;
          if (*(float *)(iStack_10 + 0xb48) <= 0.0) {
            *(undefined4 *)(iStack_10 + 0xb48) = 0x3e800000;
            iStack_62c = *(int *)(iStack_10 + 0xb20);
            uStack_106 = *(undefined2 *)(iStack_62c + 0x1e);
            iStack_3f8 = iStack_62c;
            uStack_104 = uStack_106;
            uVar5 = AutoMenuFunc__7BtlMenuFiiiii(iStack_10,2,0,uStack_106,0,0xffffffffffffffff);
            if ((uVar5 & 0x2000) == 0) {
              *(byte *)(iStack_10 + 0x25) = *(byte *)(iStack_10 + 0x25) & 0xfb;
            }
            else if ((long)((ulong)*(byte *)(iStack_10 + 0x25) << 0x3d) < 0) {
              *(undefined2 *)(iStack_10 + 0xb46) = 5;
              *(undefined4 *)(iStack_10 + 0xb48) = 0x3f800000;
            }
            else {
              uVar5 = 0;
              *(undefined4 *)(iStack_10 + 0xb48) = 0x3f400000;
              *(byte *)(iStack_10 + 0x25) = *(byte *)(iStack_10 + 0x25) & 0xfb | 4;
            }
          }
        }
        iStack_630 = *(int *)(iStack_10 + 0xb20);
        sVar8 = *(short *)(iStack_630 + 0x16);
        iStack_634 = *(int *)(iStack_10 + 0xb20);
        sVar13 = *(short *)(iStack_634 + 0x1e);
        iStack_400 = iStack_634;
        iStack_3fc = iStack_630;
        sStack_10e = sVar13;
        sStack_10c = sVar13;
        sStack_10a = sVar8;
        sStack_108 = sVar8;
        if (((uVar5 & 0x10) != 0) || ((sVar13 != 0 && ((uVar5 & 0x500) != 0)))) {
          MoveCursor__6CursorFi(iStack_10 + 0xa34,1);
          iStack_638 = *(int *)(iStack_10 + 0xb20);
          sVar13 = *(short *)(iStack_638 + 0x1e);
          iStack_404 = iStack_638;
          sStack_112 = sVar13;
          sStack_110 = sVar13;
        }
        if (((uVar5 & 0x40) != 0) || ((sVar13 == 0 && ((uVar5 & 0xa00) != 0)))) {
          MoveCursor__6CursorFi(iStack_10 + 0xa34,2);
        }
        iStack_63c = *(int *)(iStack_10 + 0xb20);
        sStack_116 = *(short *)(iStack_63c + 0x16);
        iStack_408 = iStack_63c;
        sStack_114 = sStack_116;
        iVar7 = iStack_63c;
        if (sStack_116 != sVar8) {
          *(int *)(iStack_10 + 0x43c) = (int)sStack_116;
          SetNoteWindow__7BtlMenuFPc
                    (iStack_10,*(undefined4 *)(iRam0040ab4c + *(int *)(iStack_10 + 0x43c) * 4));
          iVar7 = PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,0,1,0);
        }
        if ((uVar5 & 0x2000) == 0) {
          if ((uVar5 & 0x4000) != 0) {
            *(undefined2 *)(iStack_10 + 0x28) = 9;
            *(undefined2 *)(iStack_10 + 0x2a) = 0;
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,3,1,0,sys__6HNMSnd_ptr,iVar7);
          }
        }
        else {
          *(undefined2 *)
           ((int)pCGpffff86b4 +
           (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x598) =
               *(undefined2 *)(iStack_10 + 0xb58);
          *(undefined2 *)
           ((int)pCGpffff86b4 +
           (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x59a) =
               *(undefined2 *)(iStack_10 + 0xb5a);
          *(short *)((int)pCGpffff86b4 +
                    (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x59c) =
               (short)*(undefined4 *)(iStack_10 + 0x43c);
          *(undefined2 *)
           ((int)pCGpffff86b4 +
           (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x59e) = 0xffff;
          if (pcGpffff86ec != (code *)0x0) {
            (*pcGpffff86ec)(9,*(undefined4 *)(iStack_10 + 0x2d0),*(undefined4 *)(iStack_10 + 0x43c),
                            0,0,0,uGpffff86e8);
          }
          AllWindowClose__7BtlMenuFv(iStack_10);
          AllBCurDestruct__7BtlMenuFv();
          *(undefined2 *)(iStack_10 + 0x28) = 0x14;
          *(undefined2 *)(iStack_10 + 0x2a) = 0;
          PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,2,1,0);
        }
      }
    }
    else if (((*(short *)(iStack_10 + 0x2a) == 0) && (*(short *)(iStack_10 + 0x30a) != 0xc)) &&
            (*(short *)(iStack_10 + 0x30a) != 0xd)) {
      SetWindowMove__7BtlMenuFii(iStack_10,0,2);
      SetWindowMove__7BtlMenuFii(iStack_10,1,1);
      SetMoveAfterMenu__7BtlMenuFii(iStack_10,2,*(undefined2 *)(iStack_10 + 0xb5c));
      CreateCursole__7BtlMenuFv(iStack_10);
      Select__6CursorFP9MenuPlace(iStack_10 + 0xa34,
                      *(int *)(iStack_10 + 0x408) + *(int *)(iStack_10 + 0x430) * 0x80);
      QuickMove__6CursorFv(iStack_10 + 0xa34);
      SetWindowClose__7BtlMenuFii(iStack_10,3,6);
      SetNoteWindow__7BtlMenuFPc
                (iStack_10,*(undefined4 *)(iRam0040ab4c + *(int *)(iStack_10 + 0x43c) * 4));
      MakeCursole__7BtlMenuFiUcUcUcUcUcP7FVectori(*(undefined4 *)(iStack_10 + 0x2d4),1,1,2,0,0,0,0);
      *(undefined2 *)(iStack_10 + 0x2a) = 1;
      *(byte *)(iStack_10 + 0x24) = *(byte *)(iStack_10 + 0x24) & 0xfd;
    }
    break;
  case 0xb:
    if (*(short *)(iStack_10 + 0x2a) == 1) {
      if (((*(short *)(iStack_10 + 0x19e) == 1) || (*(short *)(iStack_10 + 0x19e) == 2)) ||
         (*(short *)(iStack_10 + 0x19e) == 5)) {
        iStack_640 = *(int *)(iStack_10 + 0xb20);
        sVar8 = *(short *)(iStack_640 + 0x16);
        bVar18 = false;
        iVar7 = 0;
        iStack_40c = iStack_640;
        sStack_11a = sVar8;
        sStack_118 = sVar8;
        if ((uVar2 & 0x10) != 0) {
          bVar18 = true;
          iStack_644 = *(int *)(iStack_10 + 0xb20);
          sStack_11e = *(short *)(iStack_644 + 0x1e);
          iStack_410 = iStack_644;
          sStack_11c = sStack_11e;
          if (sStack_11e < 1) {
            iVar7 = 1;
          }
          else {
            MoveCursor__6CursorFi(iStack_10 + 0xa34,1);
            *(int *)(iStack_10 + 0x2d8) = *(int *)(iStack_10 + 0x2d8) + -1;
            iStack_648 = *(int *)(iStack_10 + 0xb20);
            sStack_122 = *(short *)(iStack_648 + 0x16);
            *(int *)(iStack_10 + 0x2d4) = (int)sStack_122;
            iStack_414 = iStack_648;
            sStack_120 = sStack_122;
          }
        }
        if ((uVar2 & 0x40) != 0) {
          bVar18 = true;
          iStack_64c = *(int *)(iStack_10 + 0xb20);
          sStack_126 = *(short *)(iStack_64c + 0x1e);
          iStack_418 = iStack_64c;
          sStack_124 = sStack_126;
          if ((sStack_126 + 1 < 4) &&
             (*(int *)(iStack_10 + 0x2d8) + 1 < *(int *)(iStack_10 + 0x2dc))) {
            MoveCursor__6CursorFi(iStack_10 + 0xa34,2);
            *(int *)(iStack_10 + 0x2d8) = *(int *)(iStack_10 + 0x2d8) + 1;
            iStack_650 = *(int *)(iStack_10 + 0xb20);
            sStack_12a = *(short *)(iStack_650 + 0x16);
            *(int *)(iStack_10 + 0x2d4) = (int)sStack_12a;
            iStack_41c = iStack_650;
            sStack_128 = sStack_12a;
          }
          else {
            iVar7 = 2;
          }
        }
        bVar3 = false;
        if (((uVar2 & 0x500) != 0) && (0 < *(int *)(iStack_10 + 0x2d8))) {
          bVar3 = true;
          iVar7 = *(int *)(iStack_10 + 0x2d8) + -4;
          if (iVar7 < 0) {
            iVar7 = 0;
          }
          *(int *)(iStack_10 + 0x2d8) = iVar7;
          if (iVar7 < 0) {
            iVar7 = iVar7 + 3;
          }
          *(int *)(iStack_10 + 0x2e0) = iVar7 >> 2;
          iVar7 = 3;
        }
        bVar16 = false;
        if (((uVar2 & 0xa00) != 0) &&
           (*(int *)(iStack_10 + 0x2d8) + 1 < *(int *)(iStack_10 + 0x2dc))) {
          bVar16 = true;
          iVar7 = *(int *)(iStack_10 + 0x2d8) + 4;
          if (*(int *)(iStack_10 + 0x2dc) <= iVar7) {
            iVar7 = *(int *)(iStack_10 + 0x2dc) + -1;
          }
          *(int *)(iStack_10 + 0x2d8) = iVar7;
          if (iVar7 < 0) {
            iVar7 = iVar7 + 3;
          }
          *(int *)(iStack_10 + 0x2e0) = iVar7 >> 2;
          iVar7 = 3;
        }
        if (iVar7 != 0) {
          if (iVar7 == 1) {
            *(int *)(iStack_10 + 0x2d8) = *(int *)(iStack_10 + 0x2d8) + -1;
            *(int *)(iStack_10 + 0x2e0) = *(int *)(iStack_10 + 0x2e0) + -1;
            if (*(int *)(iStack_10 + 0x2e0) < 0) {
              *(int *)(iStack_10 + 0x2d8) = *(int *)(iStack_10 + 0x2dc) + -1;
              iVar7 = *(int *)(iStack_10 + 0x2dc);
              if (iVar7 < 0) {
                iVar7 = iVar7 + 3;
              }
              *(int *)(iStack_10 + 0x2e0) = iVar7 >> 2;
            }
          }
          else if (iVar7 == 2) {
            *(int *)(iStack_10 + 0x2d8) = *(int *)(iStack_10 + 0x2d8) + 1;
            *(int *)(iStack_10 + 0x2e0) = *(int *)(iStack_10 + 0x2e0) + 1;
            if (*(int *)(iStack_10 + 0x2dc) <= *(int *)(iStack_10 + 0x2d8)) {
              *(undefined4 *)(iStack_10 + 0x2d8) = 0;
              *(undefined4 *)(iStack_10 + 0x2e0) = 0;
            }
          }
          SetFusionMenu__7BtlMenuFiii
                    (iStack_10,1,*(undefined4 *)(iStack_10 + 0x2d8),0xffffffffffffffff);
          Select__6CursorFP9MenuPlace(iStack_10 + 0xa34,
                          *(int *)(iStack_10 + 0x29c) + *(int *)(iStack_10 + 0x2c4) * 0x80);
        }
        iStack_654 = *(int *)(iStack_10 + 0xb20);
        sVar13 = *(short *)(iStack_654 + 0x16);
        iStack_420 = iStack_654;
        sStack_12e = sVar13;
        sStack_12c = sVar13;
        if (sVar8 != sVar13) {
          iStack_658 = *(int *)(iStack_10 + 0xb20);
          sStack_132 = *(short *)(iStack_658 + 0x1e);
          *(int *)(iStack_10 + 0x2c4) = (int)sStack_132;
          *(undefined4 *)(iStack_10 + 0x2d0) = *(undefined4 *)(iStack_10 + 0x2d4);
          iStack_424 = iStack_658;
          sStack_130 = sStack_132;
          if (*(int *)(iStack_10 + 0x2d4) == -1) {
            SetNoteWindow__7BtlMenuFPc(iStack_10,uRam0040af54);
          }
          else {
            iVar7 = *(int *)(iStack_10 + 0x2d4);
            if (999 < iVar7) {
              iVar7 = iVar7 + -1000;
            }
            uVar6 = GetRegDat__9RegDatApiFiii(0x16,iVar7 + -10,0xffffffffffffffff);
            SetNoteWindow__7BtlMenuFPc(iStack_10,uVar6);
          }
          if (bVar18) {
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,0,1,0);
          }
          else if (bVar3) {
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,7,1,0);
          }
          else if (bVar16) {
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,6,1,0);
          }
        }
        if ((sVar8 != sVar13) || (-1 < (long)((ulong)*(byte *)(iStack_10 + 0x24) << 0x3e))) {
          if (*(int *)(iStack_10 + 0x2d0) == -1) {
            MakeTurnOrderTable__7CBattleFfiPiiiPUisibi
                      (pCGpffff86b4,3.0,0,(int *)0x0,0,0,(uint *)0x0,(short)pCGpffff86b4->cActor,-1,
                       true,-1);
          }
          else {
            MakeTurnOrderTable__7CBattleFfiPiiiPUisibi
                      (pCGpffff86b4,3.0,0,(int *)0x0,0,0,(uint *)0x0,(short)pCGpffff86b4->cActor,-1,
                       true,*(int *)(iStack_10 + 0x2d0) + -10);
          }
          *(byte *)(iStack_10 + 0x24) = *(byte *)(iStack_10 + 0x24) & 0xfd | 2;
        }
        if ((uVar1 & 0x2000) == 0) {
          if ((uVar1 & 0x4000) != 0) {
            *(undefined2 *)(iStack_10 + 0x28) = 0;
            *(undefined2 *)(iStack_10 + 0x2a) = 0;
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,3,1,0);
            MakeTurnOrderTable__7CBattleFfiPiiiPUisibi
                      (pCGpffff86b4,3.0,0,(int *)0x0,0,0,(uint *)0x0,(short)pCGpffff86b4->cActor,-1,
                       true,-2);
          }
        }
        else if ((*(int *)(iStack_10 + 0x2d0) == -1) || (9 < *(int *)(iStack_10 + 0x2d0))) {
          *(undefined2 *)
           ((int)pCGpffff86b4 +
           (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x598) =
               *(undefined2 *)(iStack_10 + 0xb58);
          *(undefined2 *)
           ((int)pCGpffff86b4 +
           (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x59c) = 0xffff;
          *(undefined2 *)
           ((int)pCGpffff86b4 +
           (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x59e) = 0xffff;
          if (*(int *)(iStack_10 + 0x2d0) == -1) {
            *(short *)((int)pCGpffff86b4 +
                      (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x59a) =
                 (short)*(undefined4 *)(iStack_10 + 0x2d0);
          }
          else {
            *(short *)((int)pCGpffff86b4 +
                      (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x59a) =
                 (short)*(undefined4 *)(iStack_10 + 0x2d0) + -10;
          }
          if (pcGpffff86ec != (code *)0x0) {
            if (*(int *)(iStack_10 + 0x2d0) == -1) {
              (*pcGpffff86ec)(0xb,0xffffffffffffffff,0,0,0,0,uGpffff86e8);
            }
            else {
              (*pcGpffff86ec)(0xb,*(int *)(iStack_10 + 0x2d0) + -10,0,0,0,0,uGpffff86e8);
            }
          }
          AllWindowClose__7BtlMenuFv(iStack_10);
          AllBCurDestruct__7BtlMenuFv();
          *(undefined2 *)(iStack_10 + 0x28) = 0x14;
          *(undefined2 *)(iStack_10 + 0x2a) = 0;
          PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,2,1,0);
        }
        else {
          PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,4,1,0);
        }
      }
    }
    else if (((*(short *)(iStack_10 + 0x2a) == 0) && (*(short *)(iStack_10 + 0x19e) != 0xc)) &&
            (*(short *)(iStack_10 + 0x19e) != 0xd)) {
      SetWindowMove__7BtlMenuFii(iStack_10,0,1);
      if (*(int *)(iStack_10 + 0x140) != 0) {
        SetMark__10ScrollMarkFUc(*(undefined4 *)(iStack_10 + 0x140),0);
      }
      SetFusionMenu__7BtlMenuFiii(iStack_10,1,0xffffffffffffffff,*(undefined2 *)(iStack_10 + 0xb5a))
      ;
      CreateCursole__7BtlMenuFv(iStack_10);
      Select__6CursorFP9MenuPlace(iStack_10 + 0xa34,
                      *(int *)(iStack_10 + 0x29c) + *(int *)(iStack_10 + 0x2c4) * 0x80);
      QuickMove__6CursorFv(iStack_10 + 0xa34);
      uVar6 = SetWindowClose__7BtlMenuFii(iStack_10,2,6);
      if (*(int *)(iStack_10 + 0x2d4) == -1) {
        SetNoteWindow__7BtlMenuFPc(iStack_10,uRam0040af54);
      }
      else {
        iVar7 = *(int *)(iStack_10 + 0x2d4);
        if (999 < iVar7) {
          iVar7 = iVar7 + -1000;
        }
        uVar6 = GetRegDat__9RegDatApiFiii(0x16,iVar7 + -10,0xffffffffffffffff,iVar7 + -10,
                                *(int *)(iStack_10 + 0x2d4),uVar6);
        SetNoteWindow__7BtlMenuFPc(iStack_10,uVar6);
      }
      AllBCurDestruct__7BtlMenuFv();
      *(undefined2 *)(iStack_10 + 0x2a) = 1;
      *(byte *)(iStack_10 + 0x24) = *(byte *)(iStack_10 + 0x24) & 0xfd;
    }
    break;
  case 0xc:
    if ((*(byte *)((int)pCGpffff86b4 +
                  (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb4) & 1) == 0
       ) {
      if ((*(byte *)((int)pCGpffff86b4 +
                    (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb1) & 1) ==
          0) {
        unaff_s0_lo = *(undefined2 *)
                       ((int)pCGpffff86b4 +
                       (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x120);
      }
      else {
        switch(*(undefined2 *)
                ((int)pCGpffff86b4 +
                (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xba)) {
        case 0:
        case 1:
          unaff_s0_lo = 0xc;
          break;
        case 2:
        case 3:
          unaff_s0_lo = 0xd;
          break;
        case 4:
        case 5:
          unaff_s0_lo = 0xe;
          break;
        case 6:
        case 7:
          unaff_s0_lo = 0xf;
          break;
        case 8:
        case 9:
          unaff_s0_lo = 0x10;
          break;
        case 10:
        case 0xb:
          unaff_s0_lo = 0x11;
          break;
        case 0xc:
        case 0xd:
          unaff_s0_lo = 0x12;
          break;
        case 0xe:
          unaff_s0_lo = 0x13;
          break;
        case 0xf:
          unaff_s0_lo = 0x14;
          break;
        case 0x10:
          unaff_s0_lo = 0x15;
        }
      }
      iStack_270 = GetRegDat__9RegDatApiFiii(0x36,unaff_s0_lo,0xffffffffffffffff);
    }
    else {
      iStack_274 = GetRegDat__9RegDatApiFiii(0x36,0x17,0xffffffffffffffff);
    }
    if (*(short *)(iStack_10 + 0x2a) == 1) {
      if (((*(short *)(iStack_10 + 0x19e) == 1) || (*(short *)(iStack_10 + 0x19e) == 2)) ||
         (*(short *)(iStack_10 + 0x19e) == 5)) {
        if ((*(short *)(iStack_10 + 0xb44) == 10) && (*(short *)(iStack_10 + 0xb46) == 3)) {
          uVar5 = 0;
          *(float *)(iStack_10 + 0xb48) = *(float *)(iStack_10 + 0xb48) - pCGpffff86b4->flDeltaT;
          if (*(float *)(iStack_10 + 0xb48) <= 0.0) {
            *(undefined4 *)(iStack_10 + 0xb48) = 0x3e800000;
            iStack_65c = *(int *)(iStack_10 + 0xb20);
            uStack_136 = *(undefined2 *)(iStack_65c + 0x1e);
            iStack_428 = iStack_65c;
            uStack_134 = uStack_136;
            uVar5 = AutoMenuFunc__7BtlMenuFiiiii(iStack_10,1,0,uStack_136,1,0xffffffffffffffff);
            if ((uVar5 & 0x2000) == 0) {
              *(byte *)(iStack_10 + 0x25) = *(byte *)(iStack_10 + 0x25) & 0xfb;
            }
            else if ((long)((ulong)*(byte *)(iStack_10 + 0x25) << 0x3d) < 0) {
              *(undefined2 *)(iStack_10 + 0xb46) = 4;
              *(undefined4 *)(iStack_10 + 0xb48) = 0x3f800000;
            }
            else {
              uVar5 = 0;
              *(undefined4 *)(iStack_10 + 0xb48) = 0x3f400000;
              *(byte *)(iStack_10 + 0x25) = *(byte *)(iStack_10 + 0x25) & 0xfb | 4;
            }
          }
        }
        iStack_660 = *(int *)(iStack_10 + 0xb20);
        sVar8 = *(short *)(iStack_660 + 0x16);
        bVar18 = false;
        iVar7 = 0;
        iStack_42c = iStack_660;
        sStack_13a = sVar8;
        sStack_138 = sVar8;
        if ((uVar5 & 0x10) != 0) {
          bVar18 = true;
          iStack_664 = *(int *)(iStack_10 + 0xb20);
          sStack_13e = *(short *)(iStack_664 + 0x1e);
          iStack_430 = iStack_664;
          sStack_13c = sStack_13e;
          if (sStack_13e < 1) {
            iVar7 = 1;
          }
          else {
            MoveCursor__6CursorFi(iStack_10 + 0xa34,1);
            *(int *)(iStack_10 + 0x2d8) = *(int *)(iStack_10 + 0x2d8) + -1;
            iStack_668 = *(int *)(iStack_10 + 0xb20);
            sStack_142 = *(short *)(iStack_668 + 0x16);
            *(int *)(iStack_10 + 0x2d4) = (int)sStack_142;
            iStack_434 = iStack_668;
            sStack_140 = sStack_142;
          }
        }
        if ((uVar5 & 0x40) != 0) {
          bVar18 = true;
          iStack_66c = *(int *)(iStack_10 + 0xb20);
          sStack_146 = *(short *)(iStack_66c + 0x1e);
          iStack_438 = iStack_66c;
          sStack_144 = sStack_146;
          if ((sStack_146 + 1 < 4) &&
             (*(int *)(iStack_10 + 0x2d8) + 1 < *(int *)(iStack_10 + 0x2dc))) {
            MoveCursor__6CursorFi(iStack_10 + 0xa34,2);
            *(int *)(iStack_10 + 0x2d8) = *(int *)(iStack_10 + 0x2d8) + 1;
            iStack_670 = *(int *)(iStack_10 + 0xb20);
            sStack_14a = *(short *)(iStack_670 + 0x16);
            *(int *)(iStack_10 + 0x2d4) = (int)sStack_14a;
            iStack_43c = iStack_670;
            sStack_148 = sStack_14a;
          }
          else {
            iVar7 = 2;
          }
        }
        bVar3 = false;
        if (((uVar5 & 0x500) != 0) && (0 < *(int *)(iStack_10 + 0x2d8))) {
          bVar3 = true;
          iVar7 = *(int *)(iStack_10 + 0x2d8) + -4;
          if (iVar7 < 0) {
            iVar7 = 0;
          }
          *(int *)(iStack_10 + 0x2d8) = iVar7;
          if (iVar7 < 0) {
            iVar7 = iVar7 + 3;
          }
          *(int *)(iStack_10 + 0x2e0) = iVar7 >> 2;
          iVar7 = 3;
        }
        bVar16 = false;
        if (((uVar5 & 0xa00) != 0) &&
           (*(int *)(iStack_10 + 0x2d8) + 1 < *(int *)(iStack_10 + 0x2dc))) {
          bVar16 = true;
          iVar7 = *(int *)(iStack_10 + 0x2d8) + 4;
          if (*(int *)(iStack_10 + 0x2dc) <= iVar7) {
            iVar7 = *(int *)(iStack_10 + 0x2dc) + -1;
          }
          *(int *)(iStack_10 + 0x2d8) = iVar7;
          if (iVar7 < 0) {
            iVar7 = iVar7 + 3;
          }
          *(int *)(iStack_10 + 0x2e0) = iVar7 >> 2;
          iVar7 = 3;
        }
        if (iVar7 != 0) {
          if (iVar7 == 1) {
            *(int *)(iStack_10 + 0x2d8) = *(int *)(iStack_10 + 0x2d8) + -1;
            *(int *)(iStack_10 + 0x2e0) = *(int *)(iStack_10 + 0x2e0) + -1;
            if (*(int *)(iStack_10 + 0x2e0) < 0) {
              *(int *)(iStack_10 + 0x2d8) = *(int *)(iStack_10 + 0x2dc) + -1;
              iVar7 = *(int *)(iStack_10 + 0x2dc);
              if (iVar7 < 0) {
                iVar7 = iVar7 + 3;
              }
              *(int *)(iStack_10 + 0x2e0) = iVar7 >> 2;
            }
          }
          else if (iVar7 == 2) {
            *(int *)(iStack_10 + 0x2d8) = *(int *)(iStack_10 + 0x2d8) + 1;
            *(int *)(iStack_10 + 0x2e0) = *(int *)(iStack_10 + 0x2e0) + 1;
            if (*(int *)(iStack_10 + 0x2dc) <= *(int *)(iStack_10 + 0x2d8)) {
              *(undefined4 *)(iStack_10 + 0x2d8) = 0;
              *(undefined4 *)(iStack_10 + 0x2e0) = 0;
            }
          }
          SetSkill1Menu__7BtlMenuFiii
                    (iStack_10,1,*(undefined4 *)(iStack_10 + 0x2d8),0xffffffffffffffff);
          Select__6CursorFP9MenuPlace(iStack_10 + 0xa34,
                          *(int *)(iStack_10 + 0x29c) + *(int *)(iStack_10 + 0x2c4) * 0x80);
        }
        iStack_674 = *(int *)(iStack_10 + 0xb20);
        sVar13 = *(short *)(iStack_674 + 0x16);
        iStack_440 = iStack_674;
        sStack_14e = sVar13;
        sStack_14c = sVar13;
        if (sVar8 != sVar13) {
          iStack_678 = *(int *)(iStack_10 + 0xb20);
          sStack_152 = *(short *)(iStack_678 + 0x1e);
          *(int *)(iStack_10 + 0x2c4) = (int)sStack_152 << 1;
          *(undefined4 *)(iStack_10 + 0x2d0) = *(undefined4 *)(iStack_10 + 0x2d4);
          iStack_444 = iStack_678;
          sStack_150 = sStack_152;
          if (bVar18) {
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,0,1,0);
          }
          else if (bVar3) {
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,7,1,0);
          }
          else if (bVar16) {
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,6,1,0);
          }
        }
        if ((sVar8 != sVar13) || (-1 < (long)((ulong)*(byte *)(iStack_10 + 0x24) << 0x3e))) {
          iVar7 = *(int *)(iStack_10 + 0x2d4);
          if (999 < iVar7) {
            iVar7 = iVar7 + -1000;
          }
          if ((*(byte *)((int)pCGpffff86b4 +
                        (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb4) & 1
              ) == 0) {
            iStack_278 = iStack_270 + iVar7 * 0x40;
            if (*(short *)(iStack_270 + iVar7 * 0x40 + 0x3e) < 0) {
              sprintf(auStack_8a0,0x654ec0,(int)*(short *)(iStack_278 + 0x18) % 1000);
            }
            else {
              uVar6 = GetRegDat__9RegDatApiFiii(0x1d,*(undefined2 *)(iStack_270 + iVar7 * 0x40 + 0x3e),
                                      0xffffffffffffffff);
              strcpy(auStack_8a0,uVar6);
              uVar6 = GetRegDat__9RegDatApiFiii(0x1d,*(undefined2 *)(iStack_270 + iVar7 * 0x40 + 0x3e),
                                      0xffffffffffffffff);
              strcpy(auStack_8a0,uVar6);
            }
          }
          else {
            iStack_278 = iStack_274 + iVar7 * 0x20;
            sprintf(auStack_8a0,0x654ec0,(int)*(short *)(iStack_278 + 0x18) % 1000);
          }
          SetNoteWindow__7BtlMenuFPc(iStack_10,auStack_8a0);
          puStack_448 = pCGpffff86b4->pTurnOrderDisp;
          *(undefined4 *)(puStack_448 + 100) = 0;
          GetTargetList__7CBattleFiiiiiP8ECCParamPiPi
                    (pCGpffff86b4,(int)pCGpffff86b4->cActor,-1,
                     (uint)(((ulong)*(ushort *)(iStack_278 + 4) << 0x37) >> 0x3e),
                     (uint)(((ulong)*(byte *)(iStack_278 + 5) << 0x3c) >> 0x3d),
                     (uint)(((ulong)*(byte *)(iStack_278 + 5) << 0x3a) >> 0x3e),
                     (void *)(iStack_278 + 8),&iStack_22c,aiStack_7a0);
          if (iStack_22c == 0) {
            MakeTurnOrderTable__7CBattleFfiPiiiPUisibi
                      (pCGpffff86b4,(float)*(ushort *)(iStack_278 + 0x1a) / 100.0,0,(int *)0x0,1,
                       iVar7,(uint *)(iStack_278 + 8),(short)pCGpffff86b4->cActor,-1,true,-2);
          }
          else {
            MakeTurnOrderTable__7CBattleFfiPiiiPUisibi
                      (pCGpffff86b4,(float)*(ushort *)(iStack_278 + 0x1a) / 100.0,iStack_22c,
                       aiStack_7a0,1,iVar7,(uint *)(iStack_278 + 8),(short)pCGpffff86b4->cActor,-1,
                       true,-2);
            if (((ulong)*(byte *)(iStack_278 + 4) & 0x7f) >> 5 == 0) {
              for (iVar7 = 0; iVar7 < iStack_22c; iVar7 = iVar7 + 1) {
                SetSelectChr__13TurnOrderDispFii(pCGpffff86b4->pTurnOrderDisp,aiStack_7a0[iVar7],2);
              }
            }
            else {
              for (iVar7 = 0; iVar7 < iStack_22c; iVar7 = iVar7 + 1) {
                SetSelectChr__13TurnOrderDispFii(pCGpffff86b4->pTurnOrderDisp,aiStack_7a0[iVar7],1);
              }
            }
          }
          *(byte *)(iStack_10 + 0x24) = *(byte *)(iStack_10 + 0x24) & 0xfd | 2;
        }
        if ((uVar5 & 0x2000) == 0) {
          if ((uVar5 & 0x4000) == 0) {
            if ((((long)((ulong)*(byte *)(ourBtlSaveDat + 3) << 0x3e) < 0) &&
                ((*(byte *)((int)pCGpffff86b4 +
                           (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb4)
                 & 1) == 0)) && ((uVar5 & 0x1000) != 0)) {
              if ((*(int *)(iStack_10 + 0x2d4) < 1000) &&
                 (iStack_278 = iStack_270 + *(int *)(iStack_10 + 0x2d4) * 0x40,
                 ((ulong)*(byte *)(iStack_278 + 4) & 0x7f) >> 5 == 0)) {
                *(undefined2 *)(iStack_10 + 0xb4c) = *(undefined2 *)(iStack_10 + 0x28);
                *(undefined2 *)(iStack_10 + 0xb4e) = *(undefined2 *)(iStack_10 + 0x2a);
                *(undefined2 *)(iStack_10 + 0xb50) = 2;
                *(undefined2 *)(iStack_10 + 0xb52) = 1;
                *(undefined1 *)(iStack_10 + 0xb54) = 3;
                *(byte *)(iStack_10 + 0xb55) =
                     (byte)(((ulong)*(byte *)(iStack_278 + 6) << 0x3c) >> 0x3d);
                *(short *)(iStack_10 + 0xb56) = (short)*(undefined4 *)(iStack_10 + 0x2d4);
                *(undefined2 *)(iStack_10 + 0x28) = 0x18;
                *(undefined2 *)(iStack_10 + 0x2a) = 0;
                PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,2,1,0);
                return 0;
              }
              PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,4,1,0);
            }
          }
          else {
            *(undefined2 *)(iStack_10 + 0x28) = 0;
            *(undefined2 *)(iStack_10 + 0x2a) = 0;
            puStack_44c = pCGpffff86b4->pTurnOrderDisp;
            *(undefined4 *)(puStack_44c + 100) = 0;
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,3,1,0);
          }
        }
        else if (*(int *)(iStack_10 + 0x2d4) < 1000) {
          if ((*(byte *)((int)pCGpffff86b4 +
                        (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb4) & 1
              ) == 0) {
            iStack_278 = iStack_270 + *(int *)(iStack_10 + 0x2d4) * 0x40;
          }
          else {
            iStack_278 = iStack_274 + *(int *)(iStack_10 + 0x2d4) * 0x20;
          }
          iStack_27c = iStack_278 + 8;
          if (((*(byte *)(iStack_278 + 0xb) >> 4 == 1) &&
              ((long)((ulong)*(byte *)(iStack_278 + 0xb) << 0x3c) < 0)) &&
             (*(char *)(iStack_278 + 10) == '(')) {
            iStack_22c = 0;
            for (iVar7 = 0; iVar7 < 0xc; iVar7 = iVar7 + 1) {
              if (((((pCGpffff86b4->aChr[iVar7].bFlagsA & 1) != 0) &&
                   ((long)((ulong)pCGpffff86b4->aChr[iVar7].bFlagsA << 0x3e) < 0)) &&
                  (-1 < (long)((ulong)pCGpffff86b4->aChr[iVar7].bFlagsA2 << 0x3d))) &&
                 ((pCGpffff86b4->aChr[iVar7].nHp < 1 &&
                  ((*(byte *)((int)pCGpffff86b4 +
                             (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb4
                             ) & 1) == (pCGpffff86b4->aChr[iVar7].bFlagsB & 1))))) {
                iStack_22c = iStack_22c + 1;
              }
            }
            if (iStack_22c == 0) {
              PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,4,1,0);
              return 0;
            }
          }
          if ((long)*(short *)(iStack_10 + 0xb5a) != (long)*(int *)(iStack_10 + 0x2d0)) {
            *(undefined2 *)(iStack_10 + 0xb5e) = 0xffff;
            *(undefined2 *)(iStack_10 + 0xb5c) = 0xffff;
          }
          *(short *)(iStack_10 + 0xb5a) = (short)*(undefined4 *)(iStack_10 + 0x2d0);
          *(undefined2 *)(iStack_10 + 0x28) = 0xd;
          *(undefined2 *)(iStack_10 + 0x2a) = 0;
          PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,2,1,0);
        }
        else {
          PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,4,1,0);
        }
      }
    }
    else if (((*(short *)(iStack_10 + 0x2a) == 0) && (*(short *)(iStack_10 + 0x19e) != 0xc)) &&
            (*(short *)(iStack_10 + 0x19e) != 0xd)) {
      *(byte *)(iStack_10 + 0x25) = *(byte *)(iStack_10 + 0x25) & 0xf7;
      uVar6 = SetWindowMove__7BtlMenuFii(iStack_10,0,1);
      if (*(int *)(iStack_10 + 0x140) != 0) {
        SetMark__10ScrollMarkFUc(*(undefined4 *)(iStack_10 + 0x140),0,uVar6);
      }
      SetSkill1Menu__7BtlMenuFiii(iStack_10,1,0xffffffffffffffff,*(undefined2 *)(iStack_10 + 0xb5a))
      ;
      CreateCursole__7BtlMenuFv(iStack_10);
      Select__6CursorFP9MenuPlace(iStack_10 + 0xa34,
                      *(int *)(iStack_10 + 0x29c) + *(int *)(iStack_10 + 0x2c4) * 0x80);
      QuickMove__6CursorFv(iStack_10 + 0xa34);
      SetWindowClose__7BtlMenuFii(iStack_10,2,6);
      AllBCurDestruct__7BtlMenuFv();
      *(undefined2 *)(iStack_10 + 0x2a) = 1;
      *(byte *)(iStack_10 + 0x24) = *(byte *)(iStack_10 + 0x24) & 0xfd;
    }
    break;
  case 0xd:
    if ((*(byte *)((int)pCGpffff86b4 +
                  (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb4) & 1) == 0
       ) {
      if ((*(byte *)((int)pCGpffff86b4 +
                    (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb1) & 1) ==
          0) {
        unaff_s0_lo = *(undefined2 *)
                       ((int)pCGpffff86b4 +
                       (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x120);
      }
      else {
        switch(*(undefined2 *)
                ((int)pCGpffff86b4 +
                (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xba)) {
        case 0:
        case 1:
          unaff_s0_lo = 0xc;
          break;
        case 2:
        case 3:
          unaff_s0_lo = 0xd;
          break;
        case 4:
        case 5:
          unaff_s0_lo = 0xe;
          break;
        case 6:
        case 7:
          unaff_s0_lo = 0xf;
          break;
        case 8:
        case 9:
          unaff_s0_lo = 0x10;
          break;
        case 10:
        case 0xb:
          unaff_s0_lo = 0x11;
          break;
        case 0xc:
        case 0xd:
          unaff_s0_lo = 0x12;
          break;
        case 0xe:
          unaff_s0_lo = 0x13;
          break;
        case 0xf:
          unaff_s0_lo = 0x14;
          break;
        case 0x10:
          unaff_s0_lo = 0x15;
        }
      }
      iStack_280 = GetRegDat__9RegDatApiFiii(0x36,unaff_s0_lo,0xffffffffffffffff);
    }
    else {
      iStack_284 = GetRegDat__9RegDatApiFiii(0x36,0x17,0xffffffffffffffff);
    }
    if ((*(byte *)((int)pCGpffff86b4 +
                  (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb4) & 1) == 0
       ) {
      iStack_288 = iStack_280 + *(int *)(iStack_10 + 0x2d4) * 0x40;
    }
    else {
      iStack_288 = iStack_284 + *(int *)(iStack_10 + 0x2d4) * 0x20;
    }
    uStack_11 = 0;
    iStack_28c = iStack_288 + 8;
    if (((*(byte *)(iStack_288 + 0xb) >> 4 == 1) &&
        ((long)((ulong)*(byte *)(iStack_288 + 0xb) << 0x3c) < 0)) &&
       (*(char *)(iStack_288 + 10) == '(')) {
      uStack_11 = 1;
    }
    sVar8 = *(short *)(iStack_10 + 0x2a);
    if (sVar8 == 2) {
      *(undefined2 *)(iStack_10 + 0x28) = 0xc;
      *(undefined2 *)(iStack_10 + 0x2a) = 0;
      AllBCurDestruct__7BtlMenuFv();
    }
    else if (sVar8 == 1) {
      if (((*(short *)(iStack_10 + 0x30a) == 1) || (*(short *)(iStack_10 + 0x30a) == 2)) ||
         (*(short *)(iStack_10 + 0x30a) == 5)) {
        if ((*(short *)(iStack_10 + 0xb44) == 10) && (*(short *)(iStack_10 + 0xb46) == 4)) {
          uVar5 = 0;
          *(float *)(iStack_10 + 0xb48) = *(float *)(iStack_10 + 0xb48) - pCGpffff86b4->flDeltaT;
          if (*(float *)(iStack_10 + 0xb48) <= 0.0) {
            *(undefined4 *)(iStack_10 + 0xb48) = 0x3e800000;
            iVar7 = -1;
            iStack_228 = 0;
            for (iVar10 = 0; iVar10 < 0xc; iVar10 = iVar10 + 1) {
              if ((((((pCGpffff86b4->aChr[iVar10].bFlagsA & 1) != 0) &&
                    ((long)((ulong)pCGpffff86b4->aChr[iVar10].bFlagsA << 0x3e) < 0)) &&
                   (-1 < (long)((ulong)pCGpffff86b4->aChr[iVar10].bFlagsA2 << 0x3d))) &&
                  ((0 < pCGpffff86b4->aChr[iVar10].nHp &&
                   ((pCGpffff86b4->aChr[iVar10].bFlagsB & 1) != 0)))) &&
                 ((long)iStack_228 < (long)pCGpffff86b4->aChr[iVar10].nHp)) {
                iStack_228 = (int)pCGpffff86b4->aChr[iVar10].nHp;
                iVar7 = iVar10;
              }
            }
            iStack_67c = *(int *)(iStack_10 + 0xb20);
            uStack_156 = *(undefined2 *)(iStack_67c + 0x1e);
            iStack_450 = iStack_67c;
            uStack_154 = uStack_156;
            uVar5 = AutoMenuFunc__7BtlMenuFiiiii(iStack_10,2,0,uStack_156,iVar7,0xffffffffffffffff);
            if ((uVar5 & 0x2000) == 0) {
              *(byte *)(iStack_10 + 0x25) = *(byte *)(iStack_10 + 0x25) & 0xfb;
            }
            else if ((long)((ulong)*(byte *)(iStack_10 + 0x25) << 0x3d) < 0) {
              *(undefined2 *)(iStack_10 + 0xb46) = 5;
              *(undefined4 *)(iStack_10 + 0xb48) = 0x3f800000;
            }
            else {
              uVar5 = 0;
              *(undefined4 *)(iStack_10 + 0xb48) = 0x3f400000;
              *(byte *)(iStack_10 + 0x25) = *(byte *)(iStack_10 + 0x25) & 0xfb | 4;
            }
          }
        }
        if ((long)((ulong)*(byte *)(iStack_10 + 0x24) << 0x3d) < 0) {
          sVar8 = (short)*(undefined4 *)(iStack_10 + 0x440);
          if (999 < sVar8) {
            sVar8 = sVar8 + -1000;
          }
          if (sVar8 == 100) {
            sVar8 = -1;
          }
          DelaySelectFunc__7BtlMenuFiiiP12EFCTCOMParam
                    (iStack_10,sVar8,1,*(undefined4 *)(iStack_10 + 0x2d4),iStack_288);
          *(byte *)(iStack_10 + 0x24) = *(byte *)(iStack_10 + 0x24) & 0xfb;
        }
        iStack_680 = *(int *)(iStack_10 + 0xb20);
        sVar8 = *(short *)(iStack_680 + 0x16);
        bVar16 = false;
        bVar3 = false;
        bVar18 = false;
        iStack_454 = iStack_680;
        sStack_15a = sVar8;
        sStack_158 = sVar8;
        if (((ulong)*(byte *)(iStack_288 + 5) & 0xf) >> 1 != 5) {
          iVar7 = 0;
          if ((uVar5 & 0x10) != 0) {
            bVar18 = true;
            iStack_684 = *(int *)(iStack_10 + 0xb20);
            sStack_15e = *(short *)(iStack_684 + 0x1e);
            iStack_458 = iStack_684;
            sStack_15c = sStack_15e;
            if (sStack_15e < 1) {
              iVar7 = 1;
            }
            else {
              MoveCursor__6CursorFi(iStack_10 + 0xa34,1);
              *(int *)(iStack_10 + 0x444) = *(int *)(iStack_10 + 0x444) + -1;
              iStack_688 = *(int *)(iStack_10 + 0xb20);
              sStack_162 = *(short *)(iStack_688 + 0x16);
              *(int *)(iStack_10 + 0x440) = (int)sStack_162;
              iStack_45c = iStack_688;
              sStack_160 = sStack_162;
            }
          }
          if ((uVar5 & 0x40) != 0) {
            bVar18 = true;
            iStack_68c = *(int *)(iStack_10 + 0xb20);
            sStack_166 = *(short *)(iStack_68c + 0x1e);
            iStack_460 = iStack_68c;
            sStack_164 = sStack_166;
            if ((sStack_166 + 1 < 4) &&
               (*(int *)(iStack_10 + 0x444) + 1 < *(int *)(iStack_10 + 0x448))) {
              MoveCursor__6CursorFi(iStack_10 + 0xa34,2);
              *(int *)(iStack_10 + 0x444) = *(int *)(iStack_10 + 0x444) + 1;
              iStack_690 = *(int *)(iStack_10 + 0xb20);
              sStack_16a = *(short *)(iStack_690 + 0x16);
              *(int *)(iStack_10 + 0x440) = (int)sStack_16a;
              iStack_464 = iStack_690;
              sStack_168 = sStack_16a;
            }
            else {
              iVar7 = 2;
            }
          }
          bVar3 = false;
          if (((uVar5 & 0x500) != 0) && (0 < *(int *)(iStack_10 + 0x444))) {
            bVar3 = true;
            iVar7 = *(int *)(iStack_10 + 0x444) + -4;
            if (iVar7 < 0) {
              iVar7 = 0;
            }
            *(int *)(iStack_10 + 0x444) = iVar7;
            if (iVar7 < 0) {
              iVar7 = iVar7 + 3;
            }
            *(int *)(iStack_10 + 0x44c) = iVar7 >> 2;
            iVar7 = 3;
          }
          bVar16 = false;
          if (((uVar5 & 0xa00) != 0) &&
             (*(int *)(iStack_10 + 0x444) + 1 < *(int *)(iStack_10 + 0x448))) {
            bVar16 = true;
            iVar7 = *(int *)(iStack_10 + 0x444) + 4;
            if (*(int *)(iStack_10 + 0x448) <= iVar7) {
              iVar7 = *(int *)(iStack_10 + 0x448) + -1;
            }
            *(int *)(iStack_10 + 0x444) = iVar7;
            if (iVar7 < 0) {
              iVar7 = iVar7 + 3;
            }
            *(int *)(iStack_10 + 0x44c) = iVar7 >> 2;
            iVar7 = 3;
          }
          if (iVar7 != 0) {
            if (iVar7 == 1) {
              *(int *)(iStack_10 + 0x444) = *(int *)(iStack_10 + 0x444) + -1;
              *(int *)(iStack_10 + 0x44c) = *(int *)(iStack_10 + 0x44c) + -1;
              if (*(int *)(iStack_10 + 0x44c) < 0) {
                *(int *)(iStack_10 + 0x444) = *(int *)(iStack_10 + 0x448) + -1;
                iVar7 = *(int *)(iStack_10 + 0x448);
                if (iVar7 < 0) {
                  iVar7 = iVar7 + 3;
                }
                *(int *)(iStack_10 + 0x44c) = iVar7 >> 2;
              }
            }
            else if (iVar7 == 2) {
              *(int *)(iStack_10 + 0x444) = *(int *)(iStack_10 + 0x444) + 1;
              *(int *)(iStack_10 + 0x44c) = *(int *)(iStack_10 + 0x44c) + 1;
              if (*(int *)(iStack_10 + 0x448) <= *(int *)(iStack_10 + 0x444)) {
                *(undefined4 *)(iStack_10 + 0x444) = 0;
                *(undefined4 *)(iStack_10 + 0x44c) = 0;
              }
            }
            SetTargetMenu__7BtlMenuFiiiP12EFCTCOMParamii
                      (iStack_10,2,1,*(undefined4 *)(iStack_10 + 0x2d4),iStack_288,
                       *(undefined4 *)(iStack_10 + 0x444),0xffffffffffffffff);
            Select__6CursorFP9MenuPlace(iStack_10 + 0xa34,
                            *(int *)(iStack_10 + 0x408) + *(int *)(iStack_10 + 0x430) * 0x80);
          }
        }
        iStack_694 = *(int *)(iStack_10 + 0xb20);
        sVar13 = *(short *)(iStack_694 + 0x16);
        iStack_468 = iStack_694;
        sStack_16e = sVar13;
        sStack_16c = sVar13;
        if (sVar8 != sVar13) {
          uVar12 = *(uint *)(iStack_10 + 0x444) & 3;
          if (((int)*(uint *)(iStack_10 + 0x444) < 0) && (uVar12 != 0)) {
            uVar12 = uVar12 - 4;
          }
          *(uint *)(iStack_10 + 0x430) = uVar12;
          *(undefined4 *)(iStack_10 + 0x43c) = *(undefined4 *)(iStack_10 + 0x440);
          if (bVar18) {
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,0,1,0);
          }
          else if (bVar3) {
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,7,1,0,uVar12,4);
          }
          else if (bVar16) {
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,6,1,0,6,4);
          }
        }
        if ((sVar8 != sVar13) || (-1 < (long)((ulong)*(byte *)(iStack_10 + 0x24) << 0x3e))) {
          sVar8 = (short)*(undefined4 *)(iStack_10 + 0x440);
          if (999 < sVar8) {
            sVar8 = sVar8 + -1000;
          }
          if (sVar8 == 100) {
            sVar8 = -1;
          }
          SelectFunc__7BtlMenuFiiiP12EFCTCOMParam
                    (iStack_10,sVar8,1,*(undefined4 *)(iStack_10 + 0x2d4),iStack_288);
          *(byte *)(iStack_10 + 0x24) = *(byte *)(iStack_10 + 0x24) & 0xfd | 2;
          *(byte *)(iStack_10 + 0x24) = *(byte *)(iStack_10 + 0x24) & 0xfb | 4;
        }
        if ((uVar5 & 0x2000) != 0) {
          if (*(int *)(iStack_10 + 0x440) < 1000) {
            sVar8 = (short)*(undefined4 *)(iStack_10 + 0x440);
            if (sVar8 == 100) {
              sVar8 = -1;
            }
            *(undefined2 *)
             ((int)pCGpffff86b4 +
             (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x598) =
                 *(undefined2 *)(iStack_10 + 0xb58);
            *(undefined2 *)
             ((int)pCGpffff86b4 +
             (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x59a) =
                 *(undefined2 *)(iStack_10 + 0xb5a);
            *(short *)((int)pCGpffff86b4 +
                      (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x59c) =
                 (short)*(undefined4 *)(iStack_10 + 0x43c);
            *(undefined2 *)
             ((int)pCGpffff86b4 +
             (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x59e) = 0xffff;
            if (pcGpffff86ec != (code *)0x0) {
              (*pcGpffff86ec)(0x12,0,0xffffffffffffffff,0,0,0,uGpffff86e8);
            }
            if (pcGpffff86ec != (code *)0x0) {
              (*pcGpffff86ec)(0xc,*(undefined4 *)(iStack_10 + 0x2d0),sVar8,0,0,0,uGpffff86e8);
            }
            if (*(int *)(iStack_10 + 0xb38) != 0) {
              (**(code **)(*(int *)(*(int *)(iStack_10 + 0xb38) + 0x14) + 0x30))();
            }
            *(undefined4 *)(iStack_10 + 0xb38) = 0;
            if (*(int *)(iStack_10 + 0xb3c) != 0) {
              (**(code **)(*(int *)(*(int *)(iStack_10 + 0xb3c) + 0x14) + 0x30))();
            }
            *(undefined4 *)(iStack_10 + 0xb3c) = 0;
            AllWindowClose__7BtlMenuFv(iStack_10);
            AllBCurDestruct__7BtlMenuFv();
            *(undefined2 *)(iStack_10 + 0x28) = 0x14;
            *(undefined2 *)(iStack_10 + 0x2a) = 0;
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,2,1,0);
            return 0;
          }
          PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,4,1,0);
        }
        if ((uVar5 & 0x4000) != 0) {
          *(undefined2 *)(iStack_10 + 0x2a) = 2;
          puStack_46c = pCGpffff86b4->pTurnOrderDisp;
          *(undefined4 *)(puStack_46c + 100) = 0;
          if (pcGpffff86ec != (code *)0x0) {
            (*pcGpffff86ec)(0x12,0,0xffffffffffffffff,0,0,0,uGpffff86e8);
          }
          if (*(int *)(iStack_10 + 0xb38) != 0) {
            (**(code **)(*(int *)(*(int *)(iStack_10 + 0xb38) + 0x14) + 0x30))();
          }
          *(undefined4 *)(iStack_10 + 0xb38) = 0;
          if (*(int *)(iStack_10 + 0xb3c) != 0) {
            (**(code **)(*(int *)(*(int *)(iStack_10 + 0xb3c) + 0x14) + 0x30))();
          }
          *(undefined4 *)(iStack_10 + 0xb3c) = 0;
          if (pcGpffff86ec != (code *)0x0) {
            (*pcGpffff86ec)(3,0,0,0,0,0,uGpffff86e8);
          }
          PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,3,1,0);
        }
      }
    }
    else if (((sVar8 == 0) && (*(short *)(iStack_10 + 0x30a) != 0xc)) &&
            (*(short *)(iStack_10 + 0x30a) != 0xd)) {
      *(byte *)(iStack_10 + 0x25) = *(byte *)(iStack_10 + 0x25) & 0xf7 | 8;
      SetWindowMove__7BtlMenuFii(iStack_10,0,2);
      SetWindowMove__7BtlMenuFii(iStack_10,1,1);
      SetTargetMenu__7BtlMenuFiiiP12EFCTCOMParamii
                (iStack_10,2,1,*(undefined4 *)(iStack_10 + 0x2d4),iStack_288,0xffffffffffffffff,
                 *(undefined2 *)(iStack_10 + 0xb5c));
      CreateCursole__7BtlMenuFv(iStack_10);
      Select__6CursorFP9MenuPlace(iStack_10 + 0xa34,
                      *(int *)(iStack_10 + 0x408) + *(int *)(iStack_10 + 0x430) * 0x80);
      QuickMove__6CursorFv(iStack_10 + 0xa34);
      SetWindowClose__7BtlMenuFii(iStack_10,3,6);
      SetNoteWindow__7BtlMenuFPc(iStack_10,uRam0040af4c);
      *(undefined2 *)(iStack_10 + 0x2a) = 1;
      *(byte *)(iStack_10 + 0x24) = *(byte *)(iStack_10 + 0x24) & 0xfd;
      *(byte *)(iStack_10 + 0x24) = *(byte *)(iStack_10 + 0x24) & 0xfb;
    }
    break;
  case 0xe:
    if ((*(byte *)((int)pCGpffff86b4 +
                  (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb4) & 1) == 0
       ) {
      if ((*(byte *)((int)pCGpffff86b4 +
                    (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb1) & 1) ==
          0) {
        unaff_s0_lo = *(undefined2 *)
                       ((int)pCGpffff86b4 +
                       (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x120);
      }
      else {
        switch(*(undefined2 *)
                ((int)pCGpffff86b4 +
                (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xba)) {
        case 0:
        case 1:
          unaff_s0_lo = 0xc;
          break;
        case 2:
        case 3:
          unaff_s0_lo = 0xd;
          break;
        case 4:
        case 5:
          unaff_s0_lo = 0xe;
          break;
        case 6:
        case 7:
          unaff_s0_lo = 0xf;
          break;
        case 8:
        case 9:
          unaff_s0_lo = 0x10;
          break;
        case 10:
        case 0xb:
          unaff_s0_lo = 0x11;
          break;
        case 0xc:
        case 0xd:
          unaff_s0_lo = 0x12;
          break;
        case 0xe:
          unaff_s0_lo = 0x13;
          break;
        case 0xf:
          unaff_s0_lo = 0x14;
          break;
        case 0x10:
          unaff_s0_lo = 0x15;
        }
      }
      iStack_290 = GetRegDat__9RegDatApiFiii(0x36,unaff_s0_lo,0xffffffffffffffff);
    }
    else {
      iStack_294 = GetRegDat__9RegDatApiFiii(0x36,0x17,0xffffffffffffffff);
    }
    if ((*(byte *)((int)pCGpffff86b4 +
                  (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb4) & 1) == 0
       ) {
      iStack_298 = iStack_290;
    }
    else {
      iStack_298 = iStack_294;
    }
    uStack_11 = 0;
    iStack_29c = iStack_298 + 8;
    if (((*(byte *)(iStack_298 + 0xb) >> 4 == 1) &&
        ((long)((ulong)*(byte *)(iStack_298 + 0xb) << 0x3c) < 0)) &&
       (*(char *)(iStack_298 + 10) == '(')) {
      uStack_11 = 1;
    }
    sVar8 = *(short *)(iStack_10 + 0x2a);
    if (sVar8 == 2) {
      *(undefined2 *)(iStack_10 + 0x28) = 0;
      *(undefined2 *)(iStack_10 + 0x2a) = 0;
      AllBCurDestruct__7BtlMenuFv();
    }
    else if (sVar8 == 1) {
      if (((*(short *)(iStack_10 + 0x19e) == 1) || (*(short *)(iStack_10 + 0x19e) == 2)) ||
         (*(short *)(iStack_10 + 0x19e) == 5)) {
        if ((long)((ulong)*(byte *)(iStack_10 + 0x24) << 0x3d) < 0) {
          sVar8 = (short)*(undefined4 *)(iStack_10 + 0x2d4);
          if (999 < sVar8) {
            sVar8 = sVar8 + -1000;
          }
          if (sVar8 == 100) {
            sVar8 = -1;
          }
          DelaySelectFunc__7BtlMenuFiiiP12EFCTCOMParam(iStack_10,sVar8,1,0,iStack_298);
          *(byte *)(iStack_10 + 0x24) = *(byte *)(iStack_10 + 0x24) & 0xfb;
        }
        iStack_698 = *(int *)(iStack_10 + 0xb20);
        sVar8 = *(short *)(iStack_698 + 0x16);
        bVar16 = false;
        bVar3 = false;
        bVar18 = false;
        iStack_470 = iStack_698;
        sStack_172 = sVar8;
        sStack_170 = sVar8;
        if (((ulong)*(byte *)(iStack_298 + 5) & 0xf) >> 1 != 5) {
          iVar7 = 0;
          if ((uVar2 & 0x10) != 0) {
            bVar16 = true;
            iStack_69c = *(int *)(iStack_10 + 0xb20);
            sStack_176 = *(short *)(iStack_69c + 0x1e);
            iStack_474 = iStack_69c;
            sStack_174 = sStack_176;
            if (sStack_176 < 1) {
              iVar7 = 1;
            }
            else {
              MoveCursor__6CursorFi(iStack_10 + 0xa34,1);
              *(int *)(iStack_10 + 0x2d8) = *(int *)(iStack_10 + 0x2d8) + -1;
              iStack_6a0 = *(int *)(iStack_10 + 0xb20);
              sStack_17a = *(short *)(iStack_6a0 + 0x16);
              *(int *)(iStack_10 + 0x2d4) = (int)sStack_17a;
              iStack_478 = iStack_6a0;
              sStack_178 = sStack_17a;
            }
          }
          if ((uVar2 & 0x40) != 0) {
            bVar16 = true;
            iStack_6a4 = *(int *)(iStack_10 + 0xb20);
            sStack_17e = *(short *)(iStack_6a4 + 0x1e);
            iStack_47c = iStack_6a4;
            sStack_17c = sStack_17e;
            if ((sStack_17e + 1 < 4) &&
               (*(int *)(iStack_10 + 0x2d8) + 1 < *(int *)(iStack_10 + 0x2dc))) {
              MoveCursor__6CursorFi(iStack_10 + 0xa34,2);
              *(int *)(iStack_10 + 0x2d8) = *(int *)(iStack_10 + 0x2d8) + 1;
              iStack_6a8 = *(int *)(iStack_10 + 0xb20);
              sStack_182 = *(short *)(iStack_6a8 + 0x16);
              *(int *)(iStack_10 + 0x2d4) = (int)sStack_182;
              iStack_480 = iStack_6a8;
              sStack_180 = sStack_182;
            }
            else {
              iVar7 = 2;
            }
          }
          bVar18 = false;
          if (((uVar2 & 0x500) != 0) && (0 < *(int *)(iStack_10 + 0x2d8))) {
            bVar18 = true;
            iVar7 = *(int *)(iStack_10 + 0x2d8) + -4;
            if (iVar7 < 0) {
              iVar7 = 0;
            }
            *(int *)(iStack_10 + 0x2d8) = iVar7;
            if (iVar7 < 0) {
              iVar7 = iVar7 + 3;
            }
            *(int *)(iStack_10 + 0x2e0) = iVar7 >> 2;
            iVar7 = 3;
          }
          bVar3 = false;
          if (((uVar2 & 0xa00) != 0) &&
             (*(int *)(iStack_10 + 0x2d8) + 1 < *(int *)(iStack_10 + 0x2dc))) {
            bVar3 = true;
            iVar7 = *(int *)(iStack_10 + 0x2d8) + 4;
            if (*(int *)(iStack_10 + 0x2dc) <= iVar7) {
              iVar7 = *(int *)(iStack_10 + 0x2dc) + -1;
            }
            *(int *)(iStack_10 + 0x2d8) = iVar7;
            if (iVar7 < 0) {
              iVar7 = iVar7 + 3;
            }
            *(int *)(iStack_10 + 0x2e0) = iVar7 >> 2;
            iVar7 = 3;
          }
          if (iVar7 != 0) {
            if (iVar7 == 1) {
              *(int *)(iStack_10 + 0x2d8) = *(int *)(iStack_10 + 0x2d8) + -1;
              *(int *)(iStack_10 + 0x2e0) = *(int *)(iStack_10 + 0x2e0) + -1;
              if (*(int *)(iStack_10 + 0x2e0) < 0) {
                *(int *)(iStack_10 + 0x2d8) = *(int *)(iStack_10 + 0x2dc) + -1;
                iVar7 = *(int *)(iStack_10 + 0x2dc);
                if (iVar7 < 0) {
                  iVar7 = iVar7 + 3;
                }
                *(int *)(iStack_10 + 0x2e0) = iVar7 >> 2;
              }
            }
            else if (iVar7 == 2) {
              *(int *)(iStack_10 + 0x2d8) = *(int *)(iStack_10 + 0x2d8) + 1;
              *(int *)(iStack_10 + 0x2e0) = *(int *)(iStack_10 + 0x2e0) + 1;
              if (*(int *)(iStack_10 + 0x2dc) <= *(int *)(iStack_10 + 0x2d8)) {
                *(undefined4 *)(iStack_10 + 0x2d8) = 0;
                *(undefined4 *)(iStack_10 + 0x2e0) = 0;
              }
            }
            SetTargetMenu__7BtlMenuFiiiP12EFCTCOMParamii
                      (iStack_10,1,1,0,iStack_298,*(undefined4 *)(iStack_10 + 0x2d8),
                       0xffffffffffffffff);
            Select__6CursorFP9MenuPlace(iStack_10 + 0xa34,
                            *(int *)(iStack_10 + 0x29c) + *(int *)(iStack_10 + 0x2c4) * 0x80);
          }
        }
        iStack_6ac = *(int *)(iStack_10 + 0xb20);
        sVar13 = *(short *)(iStack_6ac + 0x16);
        iStack_484 = iStack_6ac;
        sStack_186 = sVar13;
        sStack_184 = sVar13;
        if (sVar8 != sVar13) {
          uVar12 = *(uint *)(iStack_10 + 0x2d8) & 3;
          if (((int)*(uint *)(iStack_10 + 0x2d8) < 0) && (uVar12 != 0)) {
            uVar12 = uVar12 - 4;
          }
          *(uint *)(iStack_10 + 0x2c4) = uVar12;
          *(undefined4 *)(iStack_10 + 0x2d0) = *(undefined4 *)(iStack_10 + 0x2d4);
          if (bVar16) {
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,0,1,0);
          }
          else if (bVar18) {
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,7,1,0);
          }
          else if (bVar3) {
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,6,1,0);
          }
        }
        if ((sVar8 != sVar13) || (-1 < (long)((ulong)*(byte *)(iStack_10 + 0x24) << 0x3e))) {
          sVar8 = (short)*(undefined4 *)(iStack_10 + 0x2d4);
          if (999 < sVar8) {
            sVar8 = sVar8 + -1000;
          }
          if (sVar8 == 100) {
            sVar8 = -1;
          }
          SelectFunc__7BtlMenuFiiiP12EFCTCOMParam(iStack_10,sVar8,1,0,iStack_298);
          *(byte *)(iStack_10 + 0x24) = *(byte *)(iStack_10 + 0x24) & 0xfd | 2;
          *(byte *)(iStack_10 + 0x24) = *(byte *)(iStack_10 + 0x24) & 0xfb | 4;
        }
        if ((uVar1 & 0x2000) != 0) {
          if (*(int *)(iStack_10 + 0x2d4) < 1000) {
            sVar8 = (short)*(undefined4 *)(iStack_10 + 0x2d4);
            if (sVar8 == 100) {
              sVar8 = -1;
            }
            *(undefined2 *)
             ((int)pCGpffff86b4 +
             (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x598) =
                 *(undefined2 *)(iStack_10 + 0xb58);
            *(short *)((int)pCGpffff86b4 +
                      (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x59a) =
                 (short)*(undefined4 *)(iStack_10 + 0x2d0);
            *(undefined2 *)
             ((int)pCGpffff86b4 +
             (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x59c) = 0xffff;
            *(undefined2 *)
             ((int)pCGpffff86b4 +
             (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x59e) = 0xffff;
            if (pcGpffff86ec != (code *)0x0) {
              (*pcGpffff86ec)(0x12,0,0xffffffffffffffff,0,0,0,uGpffff86e8);
            }
            if (pcGpffff86ec != (code *)0x0) {
              (*pcGpffff86ec)(0xc,0,sVar8,0,0,0,uGpffff86e8);
            }
            if (*(int *)(iStack_10 + 0xb38) != 0) {
              (**(code **)(*(int *)(*(int *)(iStack_10 + 0xb38) + 0x14) + 0x30))();
            }
            *(undefined4 *)(iStack_10 + 0xb38) = 0;
            if (*(int *)(iStack_10 + 0xb3c) != 0) {
              (**(code **)(*(int *)(*(int *)(iStack_10 + 0xb3c) + 0x14) + 0x30))();
            }
            *(undefined4 *)(iStack_10 + 0xb3c) = 0;
            AllWindowClose__7BtlMenuFv(iStack_10);
            AllBCurDestruct__7BtlMenuFv();
            *(undefined2 *)(iStack_10 + 0x28) = 0x14;
            *(undefined2 *)(iStack_10 + 0x2a) = 0;
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,2,1,0);
            return 0;
          }
          PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,4,1,0);
        }
        if ((uVar1 & 0x4000) != 0) {
          *(undefined2 *)(iStack_10 + 0x2a) = 2;
          puStack_488 = pCGpffff86b4->pTurnOrderDisp;
          *(undefined4 *)(puStack_488 + 100) = 0;
          if (pcGpffff86ec != (code *)0x0) {
            (*pcGpffff86ec)(0x12,0,0xffffffffffffffff,0,0,0,uGpffff86e8);
          }
          if (*(int *)(iStack_10 + 0xb38) != 0) {
            (**(code **)(*(int *)(*(int *)(iStack_10 + 0xb38) + 0x14) + 0x30))();
          }
          *(undefined4 *)(iStack_10 + 0xb38) = 0;
          iVar7 = iStack_10;
          if (*(int *)(iStack_10 + 0xb3c) != 0) {
            iVar7 = (**(code **)(*(int *)(*(int *)(iStack_10 + 0xb3c) + 0x14) + 0x30))();
          }
          *(undefined4 *)(iStack_10 + 0xb3c) = 0;
          if (pcGpffff86ec != (code *)0x0) {
            (*pcGpffff86ec)(3,0,0,0,0,0,uGpffff86e8,iVar7);
          }
          PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,3,1,0);
        }
      }
    }
    else if (((sVar8 == 0) && (*(short *)(iStack_10 + 0x19e) != 0xc)) &&
            (*(short *)(iStack_10 + 0x19e) != 0xd)) {
      *(byte *)(iStack_10 + 0x25) = *(byte *)(iStack_10 + 0x25) & 0xf7 | 8;
      SetWindowMove__7BtlMenuFii(iStack_10,0,1);
      SetTargetMenu__7BtlMenuFiiiP12EFCTCOMParamii
                (iStack_10,1,1,0,iStack_298,0xffffffffffffffff,*(undefined2 *)(iStack_10 + 0xb5a));
      CreateCursole__7BtlMenuFv(iStack_10);
      Select__6CursorFP9MenuPlace(iStack_10 + 0xa34,
                      *(int *)(iStack_10 + 0x29c) + *(int *)(iStack_10 + 0x2c4) * 0x80);
      QuickMove__6CursorFv(iStack_10 + 0xa34);
      SetWindowClose__7BtlMenuFii(iStack_10,2,6);
      SetNoteWindow__7BtlMenuFPc(iStack_10,uRam0040af4c);
      *(undefined2 *)(iStack_10 + 0x2a) = 1;
      *(byte *)(iStack_10 + 0x24) = *(byte *)(iStack_10 + 0x24) & 0xfd;
      *(byte *)(iStack_10 + 0x24) = *(byte *)(iStack_10 + 0x24) & 0xfb;
    }
    break;
  case 0xf:
    uStack_2b8 = GetRegDat__9RegDatApiFiii(0x3c,0,0xffffffffffffffff);
    uStack_2bc = GetRegDat__9RegDatApiFiii(0x3d,0,0xffffffffffffffff);
    sVar8 = *(short *)(iStack_10 + 0x2a);
    if (sVar8 == 3) {
      *(undefined2 *)(iStack_10 + 0x28) = 0;
      *(undefined2 *)(iStack_10 + 0x2a) = 0;
      AllBCurDestruct__7BtlMenuFv();
    }
    else {
      if (sVar8 != 2) {
        if (sVar8 != 1) {
          if (sVar8 != 0) {
            return 0;
          }
          if (pcGpffff86ec != (code *)0x0) {
            (*pcGpffff86ec)(0x13,pCGpffff86b4->cActor,3,1,0,0,uGpffff86e8);
          }
          *(undefined2 *)(iStack_10 + 0x2a) = 1;
        }
        if (*(short *)(iStack_10 + 0x19e) == 0xc) {
          return 0;
        }
        if (*(short *)(iStack_10 + 0x19e) == 0xd) {
          return 0;
        }
        SetWindowMove__7BtlMenuFii(iStack_10,0,1);
        if (*(int *)(iStack_10 + 0x140) != 0) {
          SetMark__10ScrollMarkFUc(*(undefined4 *)(iStack_10 + 0x140),0);
        }
        SetBaseAromaMenu__7BtlMenuFiii
                  (iStack_10,1,0xffffffffffffffff,*(undefined2 *)(iStack_10 + 0xb5a));
        uVar6 = CreateCursole__7BtlMenuFv(iStack_10);
        Select__6CursorFP9MenuPlace(iStack_10 + 0xa34,
                        *(int *)(iStack_10 + 0x29c) + *(int *)(iStack_10 + 0x2c4) * 0x80,uVar6);
        QuickMove__6CursorFv(iStack_10 + 0xa34);
        SetWindowClose__7BtlMenuFii(iStack_10,2,6);
        SetNoteWindow__7BtlMenuFPc(iStack_10,0x654ed0);
        AllBCurDestruct__7BtlMenuFv();
        *(undefined2 *)(iStack_10 + 0x2a) = 2;
        *(byte *)(iStack_10 + 0x24) = *(byte *)(iStack_10 + 0x24) & 0xfd;
        *(byte *)(iStack_10 + 0x24) = *(byte *)(iStack_10 + 0x24) & 0xfb;
      }
      if (((*(short *)(iStack_10 + 0x19e) == 1) || (*(short *)(iStack_10 + 0x19e) == 2)) ||
         (*(short *)(iStack_10 + 0x19e) == 5)) {
        if ((long)((ulong)*(byte *)(iStack_10 + 0x24) << 0x3d) < 0) {
          puStack_4c4 = pCGpffff86b4->pTurnOrderDisp;
          *(undefined4 *)(puStack_4c4 + 100) = 0;
          AllBCurDestruct__7BtlMenuFv();
          SetSelectChr__13TurnOrderDispFii(pCGpffff86b4->pTurnOrderDisp,pCGpffff86b4->cActor,1);
          MakeCursole__7BtlMenuFiUcUcUcUcUcP7FVectori
                    (pCGpffff86b4->cActor,0,1,2,0,0,0,0xffffffffffffffff);
          if (*(int *)(iStack_10 + 0xb3c) == 0) {
            iStack_6e4 = __nw__FUi(0x60);
            if (iStack_6e4 != 0) {
              iStack_6e4 = __ct__10CircleAreaFiif(0x41a00000,iStack_6e4,0,pCGpffff86b4->cActor);
            }
            *(int *)(iStack_10 + 0xb3c) = iStack_6e4;
          }
          else {
            ChangeTarget__10CircleAreaFi(*(undefined4 *)(iStack_10 + 0xb3c),pCGpffff86b4->cActor);
          }
          *(byte *)(iStack_10 + 0x24) = *(byte *)(iStack_10 + 0x24) & 0xfb;
        }
        iStack_6e8 = *(int *)(iStack_10 + 0xb20);
        sVar8 = *(short *)(iStack_6e8 + 0x16);
        bVar18 = false;
        iVar7 = 0;
        iStack_4c8 = iStack_6e8;
        sStack_1be = sVar8;
        sStack_1bc = sVar8;
        if ((uVar2 & 0x10) != 0) {
          bVar18 = true;
          iStack_6ec = *(int *)(iStack_10 + 0xb20);
          sStack_1c2 = *(short *)(iStack_6ec + 0x1e);
          iStack_4cc = iStack_6ec;
          sStack_1c0 = sStack_1c2;
          if (sStack_1c2 < 1) {
            iVar7 = 1;
          }
          else {
            MoveCursor__6CursorFi(iStack_10 + 0xa34,1);
            *(int *)(iStack_10 + 0x2d8) = *(int *)(iStack_10 + 0x2d8) + -1;
            iStack_6f0 = *(int *)(iStack_10 + 0xb20);
            sStack_1c6 = *(short *)(iStack_6f0 + 0x16);
            *(int *)(iStack_10 + 0x2d4) = (int)sStack_1c6;
            iStack_4d0 = iStack_6f0;
            sStack_1c4 = sStack_1c6;
          }
        }
        if ((uVar2 & 0x40) != 0) {
          bVar18 = true;
          iStack_6f4 = *(int *)(iStack_10 + 0xb20);
          sStack_1ca = *(short *)(iStack_6f4 + 0x1e);
          iStack_4d4 = iStack_6f4;
          sStack_1c8 = sStack_1ca;
          if ((sStack_1ca + 1 < 4) &&
             (*(int *)(iStack_10 + 0x2d8) + 1 < *(int *)(iStack_10 + 0x2dc))) {
            MoveCursor__6CursorFi(iStack_10 + 0xa34,2);
            *(int *)(iStack_10 + 0x2d8) = *(int *)(iStack_10 + 0x2d8) + 1;
            iStack_6f8 = *(int *)(iStack_10 + 0xb20);
            sStack_1ce = *(short *)(iStack_6f8 + 0x16);
            *(int *)(iStack_10 + 0x2d4) = (int)sStack_1ce;
            iStack_4d8 = iStack_6f8;
            sStack_1cc = sStack_1ce;
          }
          else {
            iVar7 = 2;
          }
        }
        bVar3 = false;
        if (((uVar2 & 0x500) != 0) && (0 < *(int *)(iStack_10 + 0x2d8))) {
          bVar3 = true;
          iVar7 = *(int *)(iStack_10 + 0x2d8) + -4;
          if (iVar7 < 0) {
            iVar7 = 0;
          }
          *(int *)(iStack_10 + 0x2d8) = iVar7;
          if (iVar7 < 0) {
            iVar7 = iVar7 + 3;
          }
          *(int *)(iStack_10 + 0x2e0) = iVar7 >> 2;
          iVar7 = 3;
        }
        bVar16 = false;
        if (((uVar2 & 0xa00) != 0) &&
           (*(int *)(iStack_10 + 0x2d8) + 1 < *(int *)(iStack_10 + 0x2dc))) {
          bVar16 = true;
          iVar7 = *(int *)(iStack_10 + 0x2d8) + 4;
          if (*(int *)(iStack_10 + 0x2dc) <= iVar7) {
            iVar7 = *(int *)(iStack_10 + 0x2dc) + -1;
          }
          *(int *)(iStack_10 + 0x2d8) = iVar7;
          if (iVar7 < 0) {
            iVar7 = iVar7 + 3;
          }
          *(int *)(iStack_10 + 0x2e0) = iVar7 >> 2;
          iVar7 = 3;
        }
        if (iVar7 != 0) {
          if (iVar7 == 1) {
            *(int *)(iStack_10 + 0x2d8) = *(int *)(iStack_10 + 0x2d8) + -1;
            *(int *)(iStack_10 + 0x2e0) = *(int *)(iStack_10 + 0x2e0) + -1;
            if (*(int *)(iStack_10 + 0x2e0) < 0) {
              *(int *)(iStack_10 + 0x2d8) = *(int *)(iStack_10 + 0x2dc) + -1;
              iVar7 = *(int *)(iStack_10 + 0x2dc);
              if (iVar7 < 0) {
                iVar7 = iVar7 + 3;
              }
              *(int *)(iStack_10 + 0x2e0) = iVar7 >> 2;
            }
          }
          else if (iVar7 == 2) {
            *(int *)(iStack_10 + 0x2d8) = *(int *)(iStack_10 + 0x2d8) + 1;
            *(int *)(iStack_10 + 0x2e0) = *(int *)(iStack_10 + 0x2e0) + 1;
            if (*(int *)(iStack_10 + 0x2dc) <= *(int *)(iStack_10 + 0x2d8)) {
              *(undefined4 *)(iStack_10 + 0x2d8) = 0;
              *(undefined4 *)(iStack_10 + 0x2e0) = 0;
            }
          }
          SetBaseAromaMenu__7BtlMenuFiii
                    (iStack_10,1,*(undefined4 *)(iStack_10 + 0x2d8),0xffffffffffffffff);
          Select__6CursorFP9MenuPlace(iStack_10 + 0xa34,
                          *(int *)(iStack_10 + 0x29c) + *(int *)(iStack_10 + 0x2c4) * 0x80);
        }
        iStack_6fc = *(int *)(iStack_10 + 0xb20);
        sVar13 = *(short *)(iStack_6fc + 0x16);
        iStack_4dc = iStack_6fc;
        sStack_1d2 = sVar13;
        sStack_1d0 = sVar13;
        if (sVar8 != sVar13) {
          iStack_700 = *(int *)(iStack_10 + 0xb20);
          sStack_1d6 = *(short *)(iStack_700 + 0x1e);
          *(int *)(iStack_10 + 0x2c4) = (int)sStack_1d6;
          *(undefined4 *)(iStack_10 + 0x2d0) = *(undefined4 *)(iStack_10 + 0x2d4);
          iStack_4e0 = iStack_700;
          sStack_1d4 = sStack_1d6;
          if (bVar18) {
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,0,1,0);
          }
          else if (bVar3) {
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,7,1,0);
          }
          else if (bVar16) {
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,6,1,0);
          }
        }
        if ((sVar8 != sVar13) || (-1 < (long)((ulong)*(byte *)(iStack_10 + 0x24) << 0x3e))) {
          if (-1 < (long)((ulong)*(byte *)(iStack_10 + 0x24) << 0x3e)) {
            *(byte *)(iStack_10 + 0x24) = *(byte *)(iStack_10 + 0x24) & 0xfb | 4;
          }
          *(byte *)(iStack_10 + 0x24) = *(byte *)(iStack_10 + 0x24) & 0xfd | 2;
        }
        if ((uVar1 & 0x2000) == 0) {
          if ((uVar1 & 0x4000) != 0) {
            *(undefined2 *)(iStack_10 + 0x2a) = 3;
            puStack_4e4 = pCGpffff86b4->pTurnOrderDisp;
            *(undefined4 *)(puStack_4e4 + 100) = 0;
            if (pcGpffff86ec != (code *)0x0) {
              (*pcGpffff86ec)(0x12,0,0xffffffffffffffff,0,0,0,uGpffff86e8);
            }
            if (*(int *)(iStack_10 + 0xb38) != 0) {
              (**(code **)(*(int *)(*(int *)(iStack_10 + 0xb38) + 0x14) + 0x30))();
            }
            *(undefined4 *)(iStack_10 + 0xb38) = 0;
            if (*(int *)(iStack_10 + 0xb3c) != 0) {
              (**(code **)(*(int *)(*(int *)(iStack_10 + 0xb3c) + 0x14) + 0x30))();
            }
            *(undefined4 *)(iStack_10 + 0xb3c) = 0;
            if (pcGpffff86ec != (code *)0x0) {
              (*pcGpffff86ec)(3,0,0,0,0,0,uGpffff86e8);
            }
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,3,1,0);
          }
        }
        else if (*(int *)(iStack_10 + 0x2d4) < 1000) {
          if ((long)*(short *)(iStack_10 + 0xb5a) != (long)*(int *)(iStack_10 + 0x2d0)) {
            *(undefined2 *)(iStack_10 + 0xb5e) = 0xffff;
            *(undefined2 *)(iStack_10 + 0xb5c) = 0xffff;
          }
          *(short *)(iStack_10 + 0xb5a) = (short)*(undefined4 *)(iStack_10 + 0x2d0);
          *(undefined2 *)(iStack_10 + 0x28) = 0x10;
          *(undefined2 *)(iStack_10 + 0x2a) = 0;
          PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,2,1,0);
        }
        else {
          PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,4,1,0);
        }
      }
    }
    break;
  case 0x10:
    uStack_2c0 = GetRegDat__9RegDatApiFiii(0x3c,0,0xffffffffffffffff);
    uStack_2c4 = GetRegCnt__9RegDatApiFii(0x3d,0xffffffffffffffff);
    iStack_2c8 = GetRegDat__9RegDatApiFiii(0x3d,0,0xffffffffffffffff);
    if (*(short *)(iStack_10 + 0x2a) == 1) {
      if (((*(short *)(iStack_10 + 0x30a) == 1) || (*(short *)(iStack_10 + 0x30a) == 2)) ||
         (*(short *)(iStack_10 + 0x30a) == 5)) {
        iStack_704 = *(int *)(iStack_10 + 0xb20);
        sVar8 = *(short *)(iStack_704 + 0x16);
        bVar18 = false;
        iVar7 = 0;
        iStack_4e8 = iStack_704;
        sStack_1da = sVar8;
        sStack_1d8 = sVar8;
        if ((uVar2 & 0x10) != 0) {
          bVar18 = true;
          iStack_708 = *(int *)(iStack_10 + 0xb20);
          sStack_1de = *(short *)(iStack_708 + 0x1e);
          iStack_4ec = iStack_708;
          sStack_1dc = sStack_1de;
          if (sStack_1de < 1) {
            iVar7 = 1;
          }
          else {
            MoveCursor__6CursorFi(iStack_10 + 0xa34,1);
            *(int *)(iStack_10 + 0x444) = *(int *)(iStack_10 + 0x444) + -1;
            iStack_70c = *(int *)(iStack_10 + 0xb20);
            sStack_1e2 = *(short *)(iStack_70c + 0x16);
            *(int *)(iStack_10 + 0x440) = (int)sStack_1e2;
            iStack_4f0 = iStack_70c;
            sStack_1e0 = sStack_1e2;
          }
        }
        if ((uVar2 & 0x40) != 0) {
          bVar18 = true;
          iStack_710 = *(int *)(iStack_10 + 0xb20);
          sStack_1e6 = *(short *)(iStack_710 + 0x1e);
          iStack_4f4 = iStack_710;
          sStack_1e4 = sStack_1e6;
          if ((sStack_1e6 + 1 < 4) &&
             (*(int *)(iStack_10 + 0x444) + 1 < *(int *)(iStack_10 + 0x448))) {
            MoveCursor__6CursorFi(iStack_10 + 0xa34,2);
            *(int *)(iStack_10 + 0x444) = *(int *)(iStack_10 + 0x444) + 1;
            iStack_714 = *(int *)(iStack_10 + 0xb20);
            sStack_1ea = *(short *)(iStack_714 + 0x16);
            *(int *)(iStack_10 + 0x440) = (int)sStack_1ea;
            iStack_4f8 = iStack_714;
            sStack_1e8 = sStack_1ea;
          }
          else {
            iVar7 = 2;
          }
        }
        bVar16 = false;
        bVar3 = false;
        if (((uVar2 & 0x500) != 0) && (0 < *(int *)(iStack_10 + 0x444))) {
          bVar3 = true;
          iVar7 = *(int *)(iStack_10 + 0x444) + -4;
          if (iVar7 < 0) {
            iVar7 = 0;
          }
          *(int *)(iStack_10 + 0x444) = iVar7;
          if (iVar7 < 0) {
            iVar7 = iVar7 + 3;
          }
          *(int *)(iStack_10 + 0x44c) = iVar7 >> 2;
          iVar7 = 3;
        }
        if (((uVar2 & 0xa00) != 0) &&
           (*(int *)(iStack_10 + 0x444) + 1 < *(int *)(iStack_10 + 0x448))) {
          bVar16 = true;
          iVar7 = *(int *)(iStack_10 + 0x444) + 4;
          if (*(int *)(iStack_10 + 0x448) <= iVar7) {
            iVar7 = *(int *)(iStack_10 + 0x448) + -1;
          }
          *(int *)(iStack_10 + 0x444) = iVar7;
          if (iVar7 < 0) {
            iVar7 = iVar7 + 3;
          }
          *(int *)(iStack_10 + 0x44c) = iVar7 >> 2;
          iVar7 = 3;
        }
        if (iVar7 != 0) {
          if (iVar7 == 1) {
            *(int *)(iStack_10 + 0x444) = *(int *)(iStack_10 + 0x444) + -1;
            *(int *)(iStack_10 + 0x44c) = *(int *)(iStack_10 + 0x44c) + -1;
            if (*(int *)(iStack_10 + 0x44c) < 0) {
              *(int *)(iStack_10 + 0x444) = *(int *)(iStack_10 + 0x448) + -1;
              iVar7 = *(int *)(iStack_10 + 0x448);
              if (iVar7 < 0) {
                iVar7 = iVar7 + 3;
              }
              *(int *)(iStack_10 + 0x44c) = iVar7 >> 2;
            }
          }
          else if (iVar7 == 2) {
            *(int *)(iStack_10 + 0x444) = *(int *)(iStack_10 + 0x444) + 1;
            *(int *)(iStack_10 + 0x44c) = *(int *)(iStack_10 + 0x44c) + 1;
            if (*(int *)(iStack_10 + 0x448) <= *(int *)(iStack_10 + 0x444)) {
              *(undefined4 *)(iStack_10 + 0x444) = 0;
              *(undefined4 *)(iStack_10 + 0x44c) = 0;
            }
          }
          SetAddAromaMenu__7BtlMenuFiii
                    (iStack_10,2,*(undefined4 *)(iStack_10 + 0x444),0xffffffffffffffff);
          Select__6CursorFP9MenuPlace(iStack_10 + 0xa34,
                          *(int *)(iStack_10 + 0x408) + *(int *)(iStack_10 + 0x430) * 0x80);
        }
        iStack_718 = *(int *)(iStack_10 + 0xb20);
        sVar13 = *(short *)(iStack_718 + 0x16);
        iStack_4fc = iStack_718;
        sStack_1ee = sVar13;
        sStack_1ec = sVar13;
        if (sVar8 != sVar13) {
          iStack_71c = *(int *)(iStack_10 + 0xb20);
          sStack_1f2 = *(short *)(iStack_71c + 0x1e);
          *(int *)(iStack_10 + 0x430) = (int)sStack_1f2 << 1;
          *(undefined4 *)(iStack_10 + 0x43c) = *(undefined4 *)(iStack_10 + 0x440);
          iStack_500 = iStack_71c;
          sStack_1f0 = sStack_1f2;
          if (bVar18) {
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,0,1,0);
          }
          else if (bVar3) {
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,7,1,0);
          }
          else if (bVar16) {
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,6,1,0);
          }
        }
        if ((sVar8 != sVar13) || (-1 < (long)((ulong)*(byte *)(iStack_10 + 0x24) << 0x3e))) {
          lVar15 = (long)*(int *)(iStack_10 + 0x440);
          if (999 < lVar15) {
            lVar15 = (long)(*(int *)(iStack_10 + 0x440) + -1000);
          }
          for (uVar12 = 0; uVar12 < uStack_2c4; uVar12 = uVar12 + 1) {
            if (((long)*(int *)(iStack_10 + 0x2d4) ==
                 (long)*(char *)(iStack_2c8 + uVar12 * 0x40 + 0x1c)) &&
               (lVar15 == *(char *)(iStack_2c8 + uVar12 * 0x40 + 0x1d))) {
              iStack_2cc = iStack_2c8 + uVar12 * 0x40;
              break;
            }
          }
          if (*(short *)(iStack_2cc + 0x18) < 1000) {
            sprintf(auStack_8a0,0x654f00,*(undefined2 *)(iStack_2cc + 0x18));
          }
          else {
            sprintf(auStack_8a0,0x654f00,*(short *)(iStack_2cc + 0x18) + -1000);
          }
          SetNoteWindow__7BtlMenuFPc(iStack_10,auStack_8a0);
          puStack_504 = pCGpffff86b4->pTurnOrderDisp;
          *(undefined4 *)(puStack_504 + 100) = 0;
          iStack_2d0 = iStack_2cc + 8;
          if ((*(byte *)(iStack_2cc + 0xb) >> 4 == 4) &&
             ((((ulong)*(ushort *)(iStack_2cc + 10) & 0xfff) >> 5 == 0x30 ||
              (((ulong)*(ushort *)(iStack_2cc + 10) & 0xfff) >> 5 == 0x31)))) {
            GetTargetList__7CBattleFiiiiiP8ECCParamPiPi
                      (pCGpffff86b4,(int)pCGpffff86b4->cActor,(int)pCGpffff86b4->cActor,2,1,0,
                       (void *)0x0,&iStack_22c,aiStack_7a0);
          }
          else {
            GetTargetList__7CBattleFiiiiiP8ECCParamPiPi
                      (pCGpffff86b4,(int)pCGpffff86b4->cActor,(int)pCGpffff86b4->cActor,1,1,0,
                       (void *)0x0,&iStack_22c,aiStack_7a0);
          }
          AllBCurDestruct__7BtlMenuFv();
          SetSelectChr__13TurnOrderDispFii(pCGpffff86b4->pTurnOrderDisp,pCGpffff86b4->cActor,1);
          MakeCursole__7BtlMenuFiUcUcUcUcUcP7FVectori
                    (pCGpffff86b4->cActor,0,1,2,0,0,0,0xffffffffffffffff);
          for (iVar7 = 0; iVar7 < iStack_22c; iVar7 = iVar7 + 1) {
            if ((long)pCGpffff86b4->cActor != (long)aiStack_7a0[iVar7]) {
              MakeCursole__7BtlMenuFiUcUcUcUcUcP7FVectori
                        (aiStack_7a0[iVar7],1,1,2,0,0,0,0xffffffffffffffff);
              SetSelectChr__13TurnOrderDispFii(pCGpffff86b4->pTurnOrderDisp,aiStack_7a0[iVar7],1);
            }
          }
          MakeTurnOrderTable__7CBattleFfiPiiiPUisibi
                    (pCGpffff86b4,(float)*(ushort *)(iStack_2cc + 0x1a) / 100.0,0,(int *)0x0,5,0,
                     (uint *)0x0,(short)pCGpffff86b4->cActor,-1,true,-2);
          *(byte *)(iStack_10 + 0x24) = *(byte *)(iStack_10 + 0x24) & 0xfd | 2;
        }
        if ((uVar1 & 0x2000) == 0) {
          if ((uVar1 & 0x4000) != 0) {
            *(undefined2 *)(iStack_10 + 0x28) = 0xf;
            *(undefined2 *)(iStack_10 + 0x2a) = 1;
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,3,1,0);
          }
        }
        else if (*(int *)(iStack_10 + 0x440) < 1000) {
          for (uVar12 = 0; uVar12 < uStack_2c4; uVar12 = uVar12 + 1) {
            if (((long)*(int *)(iStack_10 + 0x2d4) ==
                 (long)*(char *)(iStack_2c8 + uVar12 * 0x40 + 0x1c)) &&
               ((long)*(int *)(iStack_10 + 0x440) ==
                (long)*(char *)(iStack_2c8 + uVar12 * 0x40 + 0x1d))) {
              iStack_2cc = iStack_2c8 + uVar12 * 0x40;
              break;
            }
          }
          *(undefined2 *)
           ((int)pCGpffff86b4 +
           (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x598) =
               *(undefined2 *)(iStack_10 + 0xb58);
          *(undefined2 *)
           ((int)pCGpffff86b4 +
           (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x59a) =
               *(undefined2 *)(iStack_10 + 0xb5a);
          *(short *)((int)pCGpffff86b4 +
                    (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x59c) =
               (short)*(undefined4 *)(iStack_10 + 0x43c);
          *(undefined2 *)
           ((int)pCGpffff86b4 +
           (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x59e) = 0xffff;
          if (pcGpffff86ec != (code *)0x0) {
            (*pcGpffff86ec)(0x12,0,0xffffffffffffffff,0,0,0,uGpffff86e8);
          }
          if (pcGpffff86ec != (code *)0x0) {
            (*pcGpffff86ec)(0xe,uVar12,0,0,0,0,uGpffff86e8);
          }
          if (*(int *)(iStack_10 + 0xb38) != 0) {
            (**(code **)(*(int *)(*(int *)(iStack_10 + 0xb38) + 0x14) + 0x30))();
          }
          *(undefined4 *)(iStack_10 + 0xb38) = 0;
          if (*(int *)(iStack_10 + 0xb3c) != 0) {
            (**(code **)(*(int *)(*(int *)(iStack_10 + 0xb3c) + 0x14) + 0x30))();
          }
          *(undefined4 *)(iStack_10 + 0xb3c) = 0;
          AllWindowClose__7BtlMenuFv(iStack_10);
          AllBCurDestruct__7BtlMenuFv();
          *(undefined2 *)(iStack_10 + 0x28) = 0x14;
          *(undefined2 *)(iStack_10 + 0x2a) = 0;
          PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,2,1,0);
        }
        else {
          PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,4,1,0);
        }
      }
    }
    else if (((*(short *)(iStack_10 + 0x2a) == 0) && (*(short *)(iStack_10 + 0x30a) != 0xc)) &&
            (*(short *)(iStack_10 + 0x30a) != 0xd)) {
      SetWindowMove__7BtlMenuFii(iStack_10,0,2);
      SetWindowMove__7BtlMenuFii(iStack_10,1,1);
      SetAddAromaMenu__7BtlMenuFiii
                (iStack_10,2,0xffffffffffffffff,*(undefined2 *)(iStack_10 + 0xb5c));
      CreateCursole__7BtlMenuFv(iStack_10);
      Select__6CursorFP9MenuPlace(iStack_10 + 0xa34,
                      *(int *)(iStack_10 + 0x408) + *(int *)(iStack_10 + 0x430) * 0x80);
      QuickMove__6CursorFv(iStack_10 + 0xa34);
      SetWindowClose__7BtlMenuFii(iStack_10,3,6);
      *(undefined2 *)(iStack_10 + 0x2a) = 1;
      *(byte *)(iStack_10 + 0x24) = *(byte *)(iStack_10 + 0x24) & 0xfd;
    }
    break;
  case 0x12:
    iStack_2a0 = GetRegDat__9RegDatApiFiii(0x39,0,0xffffffffffffffff);
    CheckComboSkill__7CBattleFiPiPi(pCGpffff86b4,(int)pCGpffff86b4->cActor,&iStack_230,&iStack_234);
    if (*(short *)(iStack_10 + 0x2a) == 1) {
      if (((*(short *)(iStack_10 + 0x19e) == 1) || (*(short *)(iStack_10 + 0x19e) == 2)) ||
         (*(short *)(iStack_10 + 0x19e) == 5)) {
        iStack_6b0 = *(int *)(iStack_10 + 0xb20);
        sVar8 = *(short *)(iStack_6b0 + 0x16);
        bVar18 = false;
        lVar15 = 0;
        iStack_48c = iStack_6b0;
        sStack_18a = sVar8;
        sStack_188 = sVar8;
        if ((uVar2 & 0x10) != 0) {
          bVar18 = true;
          iStack_6b4 = *(int *)(iStack_10 + 0xb20);
          sStack_18e = *(short *)(iStack_6b4 + 0x1e);
          iStack_490 = iStack_6b4;
          sStack_18c = sStack_18e;
          if (sStack_18e < 1) {
            lVar15 = 1;
          }
          else {
            MoveCursor__6CursorFi(iStack_10 + 0xa34,1);
            *(int *)(iStack_10 + 0x2d8) = *(int *)(iStack_10 + 0x2d8) + -1;
            iStack_6b8 = *(int *)(iStack_10 + 0xb20);
            sStack_192 = *(short *)(iStack_6b8 + 0x16);
            *(int *)(iStack_10 + 0x2d4) = (int)sStack_192;
            iStack_494 = iStack_6b8;
            sStack_190 = sStack_192;
          }
        }
        if ((uVar2 & 0x40) != 0) {
          bVar18 = true;
          iStack_6bc = *(int *)(iStack_10 + 0xb20);
          sStack_196 = *(short *)(iStack_6bc + 0x1e);
          iStack_498 = iStack_6bc;
          sStack_194 = sStack_196;
          if ((sStack_196 + 1 < 4) &&
             (*(int *)(iStack_10 + 0x2d8) + 1 < *(int *)(iStack_10 + 0x2dc))) {
            MoveCursor__6CursorFi(iStack_10 + 0xa34,2);
            *(int *)(iStack_10 + 0x2d8) = *(int *)(iStack_10 + 0x2d8) + 1;
            iStack_6c0 = *(int *)(iStack_10 + 0xb20);
            sStack_19a = *(short *)(iStack_6c0 + 0x16);
            *(int *)(iStack_10 + 0x2d4) = (int)sStack_19a;
            iStack_49c = iStack_6c0;
            sStack_198 = sStack_19a;
          }
          else {
            lVar15 = 2;
          }
        }
        bVar3 = false;
        if (((uVar2 & 0x500) != 0) && (0 < *(int *)(iStack_10 + 0x2d8))) {
          bVar3 = true;
          iVar7 = *(int *)(iStack_10 + 0x2d8) + -4;
          if (iVar7 < 0) {
            iVar7 = 0;
          }
          *(int *)(iStack_10 + 0x2d8) = iVar7;
          if (iVar7 < 0) {
            iVar7 = iVar7 + 3;
          }
          *(int *)(iStack_10 + 0x2e0) = iVar7 >> 2;
          lVar15 = 3;
        }
        bVar16 = false;
        if (((uVar2 & 0xa00) != 0) &&
           (*(int *)(iStack_10 + 0x2d8) + 1 < *(int *)(iStack_10 + 0x2dc))) {
          bVar16 = true;
          iVar7 = *(int *)(iStack_10 + 0x2d8) + 4;
          if (*(int *)(iStack_10 + 0x2dc) <= iVar7) {
            iVar7 = *(int *)(iStack_10 + 0x2dc) + -1;
          }
          *(int *)(iStack_10 + 0x2d8) = iVar7;
          if (iVar7 < 0) {
            iVar7 = iVar7 + 3;
          }
          *(int *)(iStack_10 + 0x2e0) = iVar7 >> 2;
          lVar15 = 3;
        }
        if (lVar15 != 0) {
          if (lVar15 == 1) {
            *(int *)(iStack_10 + 0x2d8) = *(int *)(iStack_10 + 0x2d8) + -1;
            *(int *)(iStack_10 + 0x2e0) = *(int *)(iStack_10 + 0x2e0) + -1;
            if (*(int *)(iStack_10 + 0x2e0) < 0) {
              *(int *)(iStack_10 + 0x2d8) = *(int *)(iStack_10 + 0x2dc) + -1;
              iVar7 = *(int *)(iStack_10 + 0x2dc);
              if (iVar7 < 0) {
                iVar7 = iVar7 + 3;
              }
              *(int *)(iStack_10 + 0x2e0) = iVar7 >> 2;
            }
          }
          else if (lVar15 == 2) {
            *(int *)(iStack_10 + 0x2d8) = *(int *)(iStack_10 + 0x2d8) + 1;
            *(int *)(iStack_10 + 0x2e0) = *(int *)(iStack_10 + 0x2e0) + 1;
            if (*(int *)(iStack_10 + 0x2dc) <= *(int *)(iStack_10 + 0x2d8)) {
              *(undefined4 *)(iStack_10 + 0x2d8) = 0;
              *(undefined4 *)(iStack_10 + 0x2e0) = 0;
            }
          }
          SetComboSkillMenu__7BtlMenuFiii
                    (iStack_10,1,*(undefined4 *)(iStack_10 + 0x2d8),0xffffffffffffffff);
          Select__6CursorFP9MenuPlace(iStack_10 + 0xa34,
                          *(int *)(iStack_10 + 0x29c) + *(int *)(iStack_10 + 0x2c4) * 0x80);
        }
        iStack_6c4 = *(int *)(iStack_10 + 0xb20);
        sVar13 = *(short *)(iStack_6c4 + 0x16);
        iStack_4a0 = iStack_6c4;
        sStack_19e = sVar13;
        sStack_19c = sVar13;
        if (sVar8 != sVar13) {
          iStack_6c8 = *(int *)(iStack_10 + 0xb20);
          sStack_1a2 = *(short *)(iStack_6c8 + 0x1e);
          *(int *)(iStack_10 + 0x2c4) = (int)sStack_1a2 << 1;
          *(undefined4 *)(iStack_10 + 0x2d0) = *(undefined4 *)(iStack_10 + 0x2d4);
          iStack_4a4 = iStack_6c8;
          sStack_1a0 = sStack_1a2;
          if (bVar18) {
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,0,1,0);
          }
          else if (bVar3) {
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,7,1,0);
          }
          else if (bVar16) {
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,6,1,0);
          }
        }
        if ((sVar8 != sVar13) || (-1 < (long)((ulong)*(byte *)(iStack_10 + 0x24) << 0x3e))) {
          if (999 < sVar13) {
            sVar13 = sVar13 + -1000;
          }
          iStack_2a4 = iStack_2a0 + sVar13 * 0x40;
          if (((*(uint *)(ourBtlSaveDat + 0xd44) & 1 << ((int)sVar13 & 0x1fU)) == 0) ||
             (*(short *)(iStack_2a0 + sVar13 * 0x40 + 0x3c) < 0)) {
            strcpy(auStack_8a0,*(undefined4 *)(iRam0040ab20 + 0xa4));
          }
          else {
            uVar6 = GetRegDat__9RegDatApiFiii(0x20,sVar13,0xffffffffffffffff);
            strcpy(auStack_8a0,uVar6);
          }
          SetNoteWindow__7BtlMenuFPc(iStack_10,auStack_8a0);
          MakeTurnOrderTable__7CBattleFfiPiiiPUisibi
                    (pCGpffff86b4,(float)*(ushort *)(iStack_2a4 + 0x1a) / 100.0,0,(int *)0x0,4,
                     (int)sVar13,(uint *)(iStack_2a4 + 8),(short)pCGpffff86b4->cActor,-1,true,-2);
          *(byte *)(iStack_10 + 0x24) = *(byte *)(iStack_10 + 0x24) & 0xfd | 2;
        }
        if ((uVar1 & 0x2000) == 0) {
          if ((uVar1 & 0x4000) != 0) {
            *(undefined2 *)(iStack_10 + 0x28) = 0;
            *(undefined2 *)(iStack_10 + 0x2a) = 0;
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,3,1,0);
          }
        }
        else if (*(int *)(iStack_10 + 0x2d4) < 1000) {
          iStack_2a4 = iStack_2a0 + *(int *)(iStack_10 + 0x2d4) * 0x40;
          iStack_2a8 = iStack_2a4 + 8;
          if (((*(byte *)(iStack_2a4 + 0xb) >> 4 == 1) &&
              ((long)((ulong)*(byte *)(iStack_2a4 + 0xb) << 0x3c) < 0)) &&
             (*(char *)(iStack_2a4 + 10) == '(')) {
            iStack_22c = 0;
            for (iVar7 = 0; iVar7 < 0xc; iVar7 = iVar7 + 1) {
              if ((((pCGpffff86b4->aChr[iVar7].bFlagsA & 1) != 0) &&
                  ((long)((ulong)pCGpffff86b4->aChr[iVar7].bFlagsA << 0x3e) < 0)) &&
                 ((-1 < (long)((ulong)pCGpffff86b4->aChr[iVar7].bFlagsA2 << 0x3d) &&
                  ((pCGpffff86b4->aChr[iVar7].nHp < 1 &&
                   ((*(byte *)((int)pCGpffff86b4 +
                              (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 +
                              0xb4) & 1) == (pCGpffff86b4->aChr[iVar7].bFlagsB & 1))))))) {
                iStack_22c = iStack_22c + 1;
              }
            }
            if (iStack_22c == 0) {
              PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,4,1,0);
              return 0;
            }
          }
          if ((long)*(short *)(iStack_10 + 0xb5a) != (long)*(int *)(iStack_10 + 0x2d0)) {
            *(undefined2 *)(iStack_10 + 0xb5e) = 0xffff;
            *(undefined2 *)(iStack_10 + 0xb5c) = 0xffff;
          }
          *(short *)(iStack_10 + 0xb5a) = (short)*(undefined4 *)(iStack_10 + 0x2d0);
          *(undefined2 *)(iStack_10 + 0x28) = 0x13;
          *(undefined2 *)(iStack_10 + 0x2a) = 0;
          PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,2,1,0);
        }
        else {
          PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,4,1,0);
        }
      }
    }
    else if (((*(short *)(iStack_10 + 0x2a) == 0) && (*(short *)(iStack_10 + 0x19e) != 0xc)) &&
            (*(short *)(iStack_10 + 0x19e) != 0xd)) {
      *(byte *)(iStack_10 + 0x25) = *(byte *)(iStack_10 + 0x25) & 0xf7;
      SetWindowMove__7BtlMenuFii(iStack_10,0,1);
      if (*(int *)(iStack_10 + 0x140) != 0) {
        SetMark__10ScrollMarkFUc(*(undefined4 *)(iStack_10 + 0x140),0);
      }
      SetComboSkillMenu__7BtlMenuFiii
                (iStack_10,1,0xffffffffffffffff,*(undefined2 *)(iStack_10 + 0xb5a));
      CreateCursole__7BtlMenuFv(iStack_10);
      Select__6CursorFP9MenuPlace(iStack_10 + 0xa34,
                      *(int *)(iStack_10 + 0x29c) + *(int *)(iStack_10 + 0x2c4) * 0x80);
      QuickMove__6CursorFv(iStack_10 + 0xa34);
      SetWindowClose__7BtlMenuFii(iStack_10,2,6);
      AllBCurDestruct__7BtlMenuFv();
      *(undefined2 *)(iStack_10 + 0x2a) = 1;
      *(byte *)(iStack_10 + 0x24) = *(byte *)(iStack_10 + 0x24) & 0xfd;
    }
    break;
  case 0x13:
    iStack_2ac = GetRegDat__9RegDatApiFiii(0x39,0,0xffffffffffffffff);
    iStack_2b0 = iStack_2ac + *(int *)(iStack_10 + 0x2d4) * 0x40;
    uStack_11 = 0;
    iStack_2b4 = iStack_2b0 + 8;
    if (((*(byte *)(iStack_2b0 + 0xb) >> 4 == 1) &&
        ((long)((ulong)*(byte *)(iStack_2b0 + 0xb) << 0x3c) < 0)) &&
       (*(char *)(iStack_2b0 + 10) == '(')) {
      uStack_11 = 1;
    }
    CheckComboSkill__7CBattleFiPiPi(pCGpffff86b4,(int)pCGpffff86b4->cActor,&iStack_230,&iStack_234);
    sVar8 = *(short *)(iStack_10 + 0x2a);
    if (sVar8 == 2) {
      *(undefined2 *)(iStack_10 + 0x28) = 0x12;
      *(undefined2 *)(iStack_10 + 0x2a) = 0;
      AllBCurDestruct__7BtlMenuFv();
    }
    else if (sVar8 == 1) {
      if (((*(short *)(iStack_10 + 0x30a) == 1) || (*(short *)(iStack_10 + 0x30a) == 2)) ||
         (*(short *)(iStack_10 + 0x30a) == 5)) {
        if ((long)((ulong)*(byte *)(iStack_10 + 0x24) << 0x3d) < 0) {
          sVar8 = (short)*(undefined4 *)(iStack_10 + 0x440);
          if (999 < sVar8) {
            sVar8 = sVar8 + -1000;
          }
          if (sVar8 == 100) {
            sVar8 = -1;
          }
          DelaySelectFunc__7BtlMenuFiiiP12EFCTCOMParam
                    (iStack_10,sVar8,4,*(undefined4 *)(iStack_10 + 0x2d4),iStack_2b0);
          *(byte *)(iStack_10 + 0x24) = *(byte *)(iStack_10 + 0x24) & 0xfb;
        }
        iStack_6cc = *(int *)(iStack_10 + 0xb20);
        sVar8 = *(short *)(iStack_6cc + 0x16);
        bVar16 = false;
        bVar3 = false;
        bVar18 = false;
        iStack_4a8 = iStack_6cc;
        sStack_1a6 = sVar8;
        sStack_1a4 = sVar8;
        if (((ulong)*(byte *)(iStack_2b0 + 5) & 0xf) >> 1 != 5) {
          iVar7 = 0;
          if ((uVar2 & 0x10) != 0) {
            bVar16 = true;
            iStack_6d0 = *(int *)(iStack_10 + 0xb20);
            sStack_1aa = *(short *)(iStack_6d0 + 0x1e);
            iStack_4ac = iStack_6d0;
            sStack_1a8 = sStack_1aa;
            if (sStack_1aa < 1) {
              iVar7 = 1;
            }
            else {
              MoveCursor__6CursorFi(iStack_10 + 0xa34,1);
              *(int *)(iStack_10 + 0x444) = *(int *)(iStack_10 + 0x444) + -1;
              iStack_6d4 = *(int *)(iStack_10 + 0xb20);
              sStack_1ae = *(short *)(iStack_6d4 + 0x16);
              *(int *)(iStack_10 + 0x440) = (int)sStack_1ae;
              iStack_4b0 = iStack_6d4;
              sStack_1ac = sStack_1ae;
            }
          }
          if ((uVar2 & 0x40) != 0) {
            bVar16 = true;
            iStack_6d8 = *(int *)(iStack_10 + 0xb20);
            sStack_1b2 = *(short *)(iStack_6d8 + 0x1e);
            iStack_4b4 = iStack_6d8;
            sStack_1b0 = sStack_1b2;
            if ((sStack_1b2 + 1 < 4) &&
               (*(int *)(iStack_10 + 0x444) + 1 < *(int *)(iStack_10 + 0x448))) {
              MoveCursor__6CursorFi(iStack_10 + 0xa34,2);
              *(int *)(iStack_10 + 0x444) = *(int *)(iStack_10 + 0x444) + 1;
              iStack_6dc = *(int *)(iStack_10 + 0xb20);
              sStack_1b6 = *(short *)(iStack_6dc + 0x16);
              *(int *)(iStack_10 + 0x440) = (int)sStack_1b6;
              iStack_4b8 = iStack_6dc;
              sStack_1b4 = sStack_1b6;
            }
            else {
              iVar7 = 2;
            }
          }
          bVar18 = false;
          if (((uVar2 & 0x500) != 0) && (0 < *(int *)(iStack_10 + 0x444))) {
            bVar18 = true;
            iVar7 = *(int *)(iStack_10 + 0x444) + -4;
            if (iVar7 < 0) {
              iVar7 = 0;
            }
            *(int *)(iStack_10 + 0x444) = iVar7;
            if (iVar7 < 0) {
              iVar7 = iVar7 + 3;
            }
            *(int *)(iStack_10 + 0x44c) = iVar7 >> 2;
            iVar7 = 3;
          }
          bVar3 = false;
          if (((uVar2 & 0xa00) != 0) &&
             (*(int *)(iStack_10 + 0x444) + 1 < *(int *)(iStack_10 + 0x448))) {
            bVar3 = true;
            iVar7 = *(int *)(iStack_10 + 0x444) + 4;
            if (*(int *)(iStack_10 + 0x448) <= iVar7) {
              iVar7 = *(int *)(iStack_10 + 0x448) + -1;
            }
            *(int *)(iStack_10 + 0x444) = iVar7;
            if (iVar7 < 0) {
              iVar7 = iVar7 + 3;
            }
            *(int *)(iStack_10 + 0x44c) = iVar7 >> 2;
            iVar7 = 3;
          }
          if (iVar7 != 0) {
            if (iVar7 == 1) {
              *(int *)(iStack_10 + 0x444) = *(int *)(iStack_10 + 0x444) + -1;
              *(int *)(iStack_10 + 0x44c) = *(int *)(iStack_10 + 0x44c) + -1;
              if (*(int *)(iStack_10 + 0x44c) < 0) {
                *(int *)(iStack_10 + 0x444) = *(int *)(iStack_10 + 0x448) + -1;
                iVar7 = *(int *)(iStack_10 + 0x448);
                if (iVar7 < 0) {
                  iVar7 = iVar7 + 3;
                }
                *(int *)(iStack_10 + 0x44c) = iVar7 >> 2;
              }
            }
            else if (iVar7 == 2) {
              *(int *)(iStack_10 + 0x444) = *(int *)(iStack_10 + 0x444) + 1;
              *(int *)(iStack_10 + 0x44c) = *(int *)(iStack_10 + 0x44c) + 1;
              if (*(int *)(iStack_10 + 0x448) <= *(int *)(iStack_10 + 0x444)) {
                *(undefined4 *)(iStack_10 + 0x444) = 0;
                *(undefined4 *)(iStack_10 + 0x44c) = 0;
              }
            }
            SetTargetMenu__7BtlMenuFiiiP12EFCTCOMParamii
                      (iStack_10,2,4,*(undefined4 *)(iStack_10 + 0x2d4),iStack_2b0,
                       *(undefined4 *)(iStack_10 + 0x444),0xffffffffffffffff);
            Select__6CursorFP9MenuPlace(iStack_10 + 0xa34,
                            *(int *)(iStack_10 + 0x408) + *(int *)(iStack_10 + 0x430) * 0x80);
          }
        }
        iStack_6e0 = *(int *)(iStack_10 + 0xb20);
        sVar13 = *(short *)(iStack_6e0 + 0x16);
        iStack_4bc = iStack_6e0;
        sStack_1ba = sVar13;
        sStack_1b8 = sVar13;
        if (sVar8 != sVar13) {
          uVar12 = *(uint *)(iStack_10 + 0x444) & 3;
          if (((int)*(uint *)(iStack_10 + 0x444) < 0) && (uVar12 != 0)) {
            uVar12 = uVar12 - 4;
          }
          *(uint *)(iStack_10 + 0x430) = uVar12;
          *(undefined4 *)(iStack_10 + 0x43c) = *(undefined4 *)(iStack_10 + 0x440);
          if (bVar16) {
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,0,1,0);
          }
          else if (bVar18) {
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,7,1,0);
          }
          else if (bVar3) {
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,6,1,0);
          }
        }
        if ((sVar8 != sVar13) ||
           (uVar9 = (ulong)*(byte *)(iStack_10 + 0x24), -1 < (long)(uVar9 << 0x3e))) {
          sVar8 = (short)*(undefined4 *)(iStack_10 + 0x440);
          if (999 < sVar8) {
            sVar8 = sVar8 + -1000;
          }
          if (sVar8 == 100) {
            sVar8 = -1;
          }
          SelectFunc__7BtlMenuFiiiP12EFCTCOMParam
                    (iStack_10,sVar8,4,*(undefined4 *)(iStack_10 + 0x2d0),iStack_2b0);
          *(byte *)(iStack_10 + 0x24) = *(byte *)(iStack_10 + 0x24) & 0xfd | 2;
          uVar9 = 1;
          *(byte *)(iStack_10 + 0x24) = *(byte *)(iStack_10 + 0x24) & 0xfb | 4;
        }
        if ((uVar1 & 0x2000) != 0) {
          if (*(int *)(iStack_10 + 0x440) < 1000) {
            sVar8 = (short)*(undefined4 *)(iStack_10 + 0x440);
            if (sVar8 == 100) {
              sVar8 = -1;
            }
            *(undefined2 *)
             ((int)pCGpffff86b4 +
             (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x598) =
                 *(undefined2 *)(iStack_10 + 0xb58);
            *(undefined2 *)
             ((int)pCGpffff86b4 +
             (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x59a) =
                 *(undefined2 *)(iStack_10 + 0xb5a);
            *(short *)((int)pCGpffff86b4 +
                      (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x59c) =
                 (short)*(undefined4 *)(iStack_10 + 0x43c);
            *(undefined2 *)
             ((int)pCGpffff86b4 +
             (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x59e) = 0xffff;
            if (pcGpffff86ec != (code *)0x0) {
              (*pcGpffff86ec)(0x12,0,0xffffffffffffffff,0,0,0,uGpffff86e8);
            }
            if (pcGpffff86ec != (code *)0x0) {
              (*pcGpffff86ec)(0x11,*(undefined4 *)(iStack_10 + 0x2d0),sVar8,0,0,0,uGpffff86e8);
            }
            if (*(int *)(iStack_10 + 0xb38) != 0) {
              (**(code **)(*(int *)(*(int *)(iStack_10 + 0xb38) + 0x14) + 0x30))();
            }
            *(undefined4 *)(iStack_10 + 0xb38) = 0;
            if (*(int *)(iStack_10 + 0xb3c) != 0) {
              (**(code **)(*(int *)(*(int *)(iStack_10 + 0xb3c) + 0x14) + 0x30))();
            }
            *(undefined4 *)(iStack_10 + 0xb3c) = 0;
            AllWindowClose__7BtlMenuFv(iStack_10);
            AllBCurDestruct__7BtlMenuFv();
            *(undefined2 *)(iStack_10 + 0x28) = 0x14;
            *(undefined2 *)(iStack_10 + 0x2a) = 0;
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,2,1,0);
            return 0;
          }
          uVar9 = PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,4,1,0);
        }
        if ((uVar1 & 0x4000) != 0) {
          *(undefined2 *)(iStack_10 + 0x2a) = 2;
          puStack_4c0 = pCGpffff86b4->pTurnOrderDisp;
          *(undefined4 *)(puStack_4c0 + 100) = 0;
          if (pcGpffff86ec != (code *)0x0) {
            (*pcGpffff86ec)(0x12,0,0xffffffffffffffff,0,0,0,uGpffff86e8,uVar9);
          }
          if (*(int *)(iStack_10 + 0xb38) != 0) {
            (**(code **)(*(int *)(*(int *)(iStack_10 + 0xb38) + 0x14) + 0x30))();
          }
          *(undefined4 *)(iStack_10 + 0xb38) = 0;
          if (*(int *)(iStack_10 + 0xb3c) != 0) {
            (**(code **)(*(int *)(*(int *)(iStack_10 + 0xb3c) + 0x14) + 0x30))();
          }
          *(undefined4 *)(iStack_10 + 0xb3c) = 0;
          if (pcGpffff86ec != (code *)0x0) {
            (*pcGpffff86ec)(3,0,0,0,0,0,uGpffff86e8);
          }
          PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,3,1,0);
        }
      }
    }
    else if (((sVar8 == 0) && (*(short *)(iStack_10 + 0x30a) != 0xc)) &&
            (*(short *)(iStack_10 + 0x30a) != 0xd)) {
      *(byte *)(iStack_10 + 0x25) = *(byte *)(iStack_10 + 0x25) & 0xf7 | 8;
      SetWindowMove__7BtlMenuFii(iStack_10,0,2);
      SetWindowMove__7BtlMenuFii(iStack_10,1,1);
      SetTargetMenu__7BtlMenuFiiiP12EFCTCOMParamii
                (iStack_10,2,4,*(undefined4 *)(iStack_10 + 0x2d4),iStack_2b0,0xffffffffffffffff,
                 *(undefined2 *)(iStack_10 + 0xb5c));
      CreateCursole__7BtlMenuFv(iStack_10);
      Select__6CursorFP9MenuPlace(iStack_10 + 0xa34,
                      *(int *)(iStack_10 + 0x408) + *(int *)(iStack_10 + 0x430) * 0x80);
      QuickMove__6CursorFv(iStack_10 + 0xa34);
      SetWindowClose__7BtlMenuFii(iStack_10,3,6);
      SetNoteWindow__7BtlMenuFPc(iStack_10,uRam0040af48);
      AllBCurDestruct__7BtlMenuFv();
      *(undefined2 *)(iStack_10 + 0x2a) = 1;
      *(byte *)(iStack_10 + 0x24) = *(byte *)(iStack_10 + 0x24) & 0xfd;
      *(byte *)(iStack_10 + 0x24) = *(byte *)(iStack_10 + 0x24) & 0xfb;
    }
    break;
  case 0x14:
    for (iVar7 = 0; iVar7 < 6; iVar7 = iVar7 + 1) {
      if (*(short *)(iStack_10 + iVar7 * 0x16c + 0x32) != 0) {
        return 0;
      }
      if ((*(byte *)(iStack_10 + iVar7 * 0x16c + 0x30) & 1) != 0) {
        ReleaseOT__7MenuObjFv(iStack_10 + iVar7 * 0x16c + 0x3c);
      }
      iVar10 = iStack_10 + iVar7 * 0x16c;
      *(byte *)(iVar10 + 0x30) = *(byte *)(iVar10 + 0x30) & 0xfe;
      if ((long)((ulong)*(byte *)(iStack_10 + iVar7 * 0x16c + 0x30) << 0x3d) < 0) {
        ReleaseOT__7MenuObjFv(iStack_10 + iVar7 * 0x16c + 0x7c);
      }
      iVar10 = iStack_10 + iVar7 * 0x16c;
      *(byte *)(iVar10 + 0x30) = *(byte *)(iVar10 + 0x30) & 0xfb;
    }
    if (*(short *)(iStack_10 + 0x8b8) != 0) {
      return 0;
    }
    if ((long)((ulong)*(byte *)(iStack_10 + 0x24) << 0x38) < 0) {
      ReleaseOT__7MenuObjFv(iStack_10 + 0x8fc);
    }
    *(byte *)(iStack_10 + 0x24) = *(byte *)(iStack_10 + 0x24) & 0x7f;
    if (*(short *)(iStack_10 + 0xa30) != 0) {
      return 0;
    }
    if ((long)((ulong)*(byte *)(iStack_10 + 0x24) << 0x3c) < 0) {
      ReleaseOT__7MenuObjFv(iStack_10 + 0xa34);
    }
    *(byte *)(iStack_10 + 0x24) = *(byte *)(iStack_10 + 0x24) & 0xf7;
    if (*(short *)(iStack_10 + 0xa32) == 0) {
      if ((long)((ulong)*(byte *)(iStack_10 + 0x25) << 0x3e) < 0) {
        ReleaseOT__7MenuObjFv(*(undefined4 *)(iStack_10 + 0xb30));
      }
      *(byte *)(iStack_10 + 0x25) = *(byte *)(iStack_10 + 0x25) & 0xfd;
      (**(code **)(*(int *)(iStack_10 + 0x20) + 0xc))();
      if (pcGpffff86ec != (code *)0x0) {
        (*pcGpffff86ec)(0x17,0,0,0,0,0,uGpffff86e8);
      }
      return 1;
    }
    return 0;
  case 0x15:
    if (*(short *)(iStack_10 + 0x2a) == 1) {
      if (((*(short *)(iStack_10 + 0x19e) == 1) || (*(short *)(iStack_10 + 0x19e) == 2)) ||
         (*(short *)(iStack_10 + 0x19e) == 5)) {
        lVar15 = (long)iStack_10;
        iStack_720 = *(int *)(iStack_10 + 0xb20);
        sVar8 = *(short *)(iStack_720 + 0x16);
        uVar9 = (ulong)sVar8;
        uVar17 = 0;
        iVar7 = 0;
        iStack_508 = iStack_720;
        sStack_1f6 = sVar8;
        sStack_1f4 = sVar8;
        if ((uVar2 & 0x10) != 0) {
          uVar17 = 1;
          iStack_724 = *(int *)(iStack_10 + 0xb20);
          sStack_1fa = *(short *)(iStack_724 + 0x1e);
          lVar15 = (long)sStack_1fa;
          iStack_50c = iStack_724;
          sStack_1f8 = sStack_1fa;
          if (sStack_1fa < 1) {
            iVar7 = 1;
          }
          else {
            MoveCursor__6CursorFi(iStack_10 + 0xa34,1);
            *(int *)(iStack_10 + 0x2d8) = *(int *)(iStack_10 + 0x2d8) + -1;
            iStack_728 = *(int *)(iStack_10 + 0xb20);
            lVar15 = (long)iStack_728;
            sStack_1fe = *(short *)(iStack_728 + 0x16);
            uVar9 = (ulong)sStack_1fe;
            *(int *)(iStack_10 + 0x2d4) = (int)sStack_1fe;
            iStack_510 = iStack_728;
            sStack_1fc = sStack_1fe;
          }
        }
        if ((uVar2 & 0x40) != 0) {
          uVar17 = 1;
          lVar15 = (long)iStack_10;
          iStack_72c = *(int *)(iStack_10 + 0xb20);
          sStack_202 = *(short *)(iStack_72c + 0x1e);
          uVar9 = (ulong)sStack_202;
          iStack_514 = iStack_72c;
          sStack_200 = sStack_202;
          if ((sStack_202 + 1 < 4) &&
             (*(int *)(iStack_10 + 0x2d8) + 1 < *(int *)(iStack_10 + 0x2dc))) {
            uVar9 = MoveCursor__6CursorFi(iStack_10 + 0xa34,2);
            *(int *)(iStack_10 + 0x2d8) = *(int *)(iStack_10 + 0x2d8) + 1;
            iStack_730 = *(int *)(iStack_10 + 0xb20);
            sStack_206 = *(short *)(iStack_730 + 0x16);
            lVar15 = (long)iStack_10;
            *(int *)(iStack_10 + 0x2d4) = (int)sStack_206;
            iStack_518 = iStack_730;
            sStack_204 = sStack_206;
          }
          else {
            iVar7 = 2;
          }
        }
        if (((uVar2 & 0x500) != 0) && (0 < *(int *)(iStack_10 + 0x2d8))) {
          uVar17 = uVar17 | 2;
          iVar7 = *(int *)(iStack_10 + 0x2d8) + -4;
          if (iVar7 < 0) {
            iVar7 = 0;
          }
          *(int *)(iStack_10 + 0x2d8) = iVar7;
          iVar10 = iVar7 >> 2;
          uVar9 = uVar17;
          if (iVar7 < 0) {
            iVar10 = iVar7 + 3 >> 2;
            uVar9 = (ulong)iVar10;
          }
          lVar15 = (long)iStack_10;
          *(int *)(iStack_10 + 0x2e0) = iVar10;
          iVar7 = 3;
        }
        if (((uVar2 & 0xa00) != 0) &&
           (*(int *)(iStack_10 + 0x2d8) + 1 < *(int *)(iStack_10 + 0x2dc))) {
          uVar17 = uVar17 | 4;
          iVar7 = *(int *)(iStack_10 + 0x2d8) + 4;
          if (*(int *)(iStack_10 + 0x2dc) <= iVar7) {
            uVar9 = (ulong)*(int *)(iStack_10 + 0x2dc);
            iVar7 = *(int *)(iStack_10 + 0x2dc) + -1;
          }
          lVar15 = (long)iStack_10;
          *(int *)(iStack_10 + 0x2d8) = iVar7;
          if (iVar7 < 0) {
            iVar7 = iVar7 + 3;
            uVar9 = (ulong)iVar7;
          }
          *(int *)(iStack_10 + 0x2e0) = iVar7 >> 2;
          iVar7 = 3;
        }
        if (iVar7 != 0) {
          if (iVar7 == 1) {
            *(int *)(iStack_10 + 0x2d8) = *(int *)(iStack_10 + 0x2d8) + -1;
            *(int *)(iStack_10 + 0x2e0) = *(int *)(iStack_10 + 0x2e0) + -1;
            if (*(int *)(iStack_10 + 0x2e0) < 0) {
              uVar9 = (ulong)iStack_10;
              *(int *)(iStack_10 + 0x2d8) = *(int *)(iStack_10 + 0x2dc) + -1;
              iVar7 = *(int *)(iStack_10 + 0x2dc);
              if (iVar7 < 0) {
                iVar7 = iVar7 + 3;
              }
              *(int *)(iStack_10 + 0x2e0) = iVar7 >> 2;
            }
          }
          else if (iVar7 == 2) {
            iVar7 = *(int *)(iStack_10 + 0x2d8) + 1;
            uVar9 = (ulong)iVar7;
            *(int *)(iStack_10 + 0x2d8) = iVar7;
            *(int *)(iStack_10 + 0x2e0) = *(int *)(iStack_10 + 0x2e0) + 1;
            if (*(int *)(iStack_10 + 0x2dc) <= *(int *)(iStack_10 + 0x2d8)) {
              *(undefined4 *)(iStack_10 + 0x2d8) = 0;
              *(undefined4 *)(iStack_10 + 0x2e0) = 0;
            }
          }
          SetNextComboChrMenu__7BtlMenuFii
                    (iStack_10,1,*(undefined4 *)(iStack_10 + 0x2d8),iStack_10,lVar15,uVar9);
          Select__6CursorFP9MenuPlace(iStack_10 + 0xa34,
                          *(int *)(iStack_10 + 0x29c) + *(int *)(iStack_10 + 0x2c4) * 0x80);
        }
        iStack_734 = *(int *)(iStack_10 + 0xb20);
        sVar13 = *(short *)(iStack_734 + 0x16);
        iStack_51c = iStack_734;
        sStack_20a = sVar13;
        sStack_208 = sVar13;
        if (sVar8 != sVar13) {
          if ((uVar17 & 1) == 0) {
            if ((uVar17 & 2) == 0) {
              if ((uVar17 & 4) != 0) {
                PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,6,1,0);
              }
            }
            else {
              PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,7,1,0);
            }
          }
          else {
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,0,1,0);
          }
        }
        if ((sVar8 != sVar13) || (-1 < (long)((ulong)*(byte *)(iStack_10 + 0x24) << 0x3e))) {
          puStack_520 = pCGpffff86b4->pTurnOrderDisp;
          *(undefined4 *)(puStack_520 + 100) = 0;
          SetSelectChr__13TurnOrderDispFii
                    (pCGpffff86b4->pTurnOrderDisp,*(undefined4 *)(iStack_10 + 0x2d4),1);
          if (pcGpffff86ec != (code *)0x0) {
            (*pcGpffff86ec)(0,*(undefined4 *)(iStack_10 + 0x2d4),0,0,0,0,uGpffff86e8);
          }
          MakeCursole__7BtlMenuFiUcUcUcUcUcP7FVectori
                    (*(undefined4 *)(iStack_10 + 0x2d4),0,1,2,0,0,0,0);
          *(byte *)(iStack_10 + 0x24) = *(byte *)(iStack_10 + 0x24) & 0xfd | 2;
        }
        if ((uVar1 & 0x2000) != 0) {
          if (pcGpffff86ec != (code *)0x0) {
            (*pcGpffff86ec)(1,*(undefined4 *)(iStack_10 + 0x2d4),0,0,0,0,uGpffff86e8);
          }
          AllWindowClose__7BtlMenuFv(iStack_10);
          AllBCurDestruct__7BtlMenuFv();
          *(undefined2 *)(iStack_10 + 0x28) = 0x14;
          *(undefined2 *)(iStack_10 + 0x2a) = 0;
          PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,2,1,0);
        }
      }
    }
    else if (*(short *)(iStack_10 + 0x2a) == 0) {
      SetNextComboChrTitle__7BtlMenuFi(iStack_10,0);
      SetNextComboChrMenu__7BtlMenuFii(iStack_10,1,0xffffffffffffffff);
      CreateCursole__7BtlMenuFv(iStack_10);
      Select__6CursorFP9MenuPlace(iStack_10 + 0xa34,
                      *(int *)(iStack_10 + 0x29c) + *(int *)(iStack_10 + 0x2c4) * 0x80);
      QuickMove__6CursorFv(iStack_10 + 0xa34);
      SetWindowClose__7BtlMenuFii(iStack_10,2,6);
      SetNoteWindow__7BtlMenuFPc(iStack_10,*(undefined4 *)(iRam0040ab28 + 4));
      *(undefined2 *)(iStack_10 + 0x2a) = 1;
      *(byte *)(iStack_10 + 0x24) = *(byte *)(iStack_10 + 0x24) & 0xfd;
      *(undefined4 *)(iStack_10 + 0x2c) = 0;
      PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,0x2000000,1,0);
    }
    break;
  case 0x16:
    sVar8 = *(short *)(iStack_10 + 0x2a);
    if (sVar8 == 3) {
      for (iVar7 = 0; iVar7 < 6; iVar7 = iVar7 + 1) {
        if (*(short *)(iStack_10 + iVar7 * 0x16c + 0x32) != 0) {
          return 0;
        }
        if ((*(byte *)(iStack_10 + iVar7 * 0x16c + 0x30) & 1) != 0) {
          ReleaseOT__7MenuObjFv(iStack_10 + iVar7 * 0x16c + 0x3c);
        }
        iVar10 = iStack_10 + iVar7 * 0x16c;
        *(byte *)(iVar10 + 0x30) = *(byte *)(iVar10 + 0x30) & 0xfe;
        if ((long)((ulong)*(byte *)(iStack_10 + iVar7 * 0x16c + 0x30) << 0x3d) < 0) {
          ReleaseOT__7MenuObjFv(iStack_10 + iVar7 * 0x16c + 0x7c);
        }
        iVar10 = iStack_10 + iVar7 * 0x16c;
        *(byte *)(iVar10 + 0x30) = *(byte *)(iVar10 + 0x30) & 0xfb;
      }
      if (*(short *)(iStack_10 + 0x8b8) != 0) {
        return 0;
      }
      if ((long)((ulong)*(byte *)(iStack_10 + 0x24) << 0x38) < 0) {
        ReleaseOT__7MenuObjFv(iStack_10 + 0x8fc);
      }
      *(byte *)(iStack_10 + 0x24) = *(byte *)(iStack_10 + 0x24) & 0x7f;
      if (*(short *)(iStack_10 + 0xa30) != 0) {
        return 0;
      }
      if ((long)((ulong)*(byte *)(iStack_10 + 0x24) << 0x3c) < 0) {
        ReleaseOT__7MenuObjFv(iStack_10 + 0xa34);
      }
      *(byte *)(iStack_10 + 0x24) = *(byte *)(iStack_10 + 0x24) & 0xf7;
      if (*(short *)(iStack_10 + 0xa32) != 0) {
        return 0;
      }
      if ((long)((ulong)*(byte *)(iStack_10 + 0x25) << 0x3e) < 0) {
        ReleaseOT__7MenuObjFv(*(undefined4 *)(iStack_10 + 0xb30));
      }
      *(byte *)(iStack_10 + 0x25) = *(byte *)(iStack_10 + 0x25) & 0xfd;
      *(undefined2 *)(iStack_10 + 0x2a) = 0;
    }
    else if (sVar8 == 2) {
      if (*(short *)(iStack_10 + 0xb46) != 0) {
        AllWindowClose__7BtlMenuFv(iStack_10);
        AllBCurDestruct__7BtlMenuFv();
        sVar8 = *(short *)(iStack_10 + 0xb44);
        if (sVar8 == 0x24) {
          *(undefined2 *)(iStack_10 + 0x2a) = 3;
          *(undefined2 *)(iStack_10 + 0xb44) = 0x25;
          *(undefined2 *)(iStack_10 + 0xb46) = 0;
        }
        else if (sVar8 == 0x23) {
          *(undefined2 *)(iStack_10 + 0x2a) = 3;
          *(undefined2 *)(iStack_10 + 0xb44) = 0x24;
          *(undefined2 *)(iStack_10 + 0xb46) = 0;
        }
        else if (sVar8 == 0x22) {
          *(undefined2 *)(iStack_10 + 0x2a) = 3;
          *(undefined2 *)(iStack_10 + 0xb44) = 0x23;
          *(undefined2 *)(iStack_10 + 0xb46) = 0;
        }
        else if (sVar8 == 0x21) {
          *(undefined2 *)(iStack_10 + 0x2a) = 3;
          *(undefined2 *)(iStack_10 + 0xb44) = 0x22;
          *(undefined2 *)(iStack_10 + 0xb46) = 0;
        }
        else if (sVar8 == 0x20) {
          *(undefined2 *)(iStack_10 + 0x2a) = 3;
          *(undefined2 *)(iStack_10 + 0xb44) = 0x21;
          *(undefined2 *)(iStack_10 + 0xb46) = 0;
        }
        else if (sVar8 == 0x1f) {
          *(undefined2 *)(iStack_10 + 0x2a) = 3;
          *(undefined2 *)(iStack_10 + 0xb44) = 0x20;
          *(undefined2 *)(iStack_10 + 0xb46) = 0;
        }
        else if (sVar8 == 0x1e) {
          *(undefined2 *)(iStack_10 + 0x2a) = 3;
          *(undefined2 *)(iStack_10 + 0xb44) = 0x1f;
          *(undefined2 *)(iStack_10 + 0xb46) = 0;
        }
        else if (sVar8 == 0x1a) {
          *(undefined2 *)(iStack_10 + 0x2a) = 3;
          *(undefined2 *)(iStack_10 + 0xb44) = 0x1b;
          *(undefined2 *)(iStack_10 + 0xb46) = 0;
        }
        else if (sVar8 == 0x19) {
          *(undefined2 *)(iStack_10 + 0x2a) = 3;
          *(undefined2 *)(iStack_10 + 0xb44) = 0x1a;
          *(undefined2 *)(iStack_10 + 0xb46) = 0;
        }
        else if (sVar8 == 0x11) {
          *(undefined2 *)(iStack_10 + 0x2a) = 3;
          *(undefined2 *)(iStack_10 + 0xb44) = 0x12;
          *(undefined2 *)(iStack_10 + 0xb46) = 0;
        }
        else if (sVar8 == 0x10) {
          *(undefined2 *)(iStack_10 + 0x2a) = 3;
          *(undefined2 *)(iStack_10 + 0xb44) = 0x11;
          *(undefined2 *)(iStack_10 + 0xb46) = 0;
        }
        else if (sVar8 == 0xe) {
          *(undefined2 *)(iStack_10 + 0x2a) = 3;
          *(undefined2 *)(iStack_10 + 0xb44) = 0xf;
          *(undefined2 *)(iStack_10 + 0xb46) = 0;
        }
        else if (sVar8 == 0xd) {
          if (*(int *)&pCGpffff86b4->field_0x4330 != 0) {
            AreaBlinkInit__5JRingFv(*(undefined4 *)&pCGpffff86b4->field_0x4330);
          }
          *(undefined2 *)(iStack_10 + 0x2a) = 3;
          *(undefined2 *)(iStack_10 + 0xb44) = 0xe;
          *(undefined2 *)(iStack_10 + 0xb46) = 0;
        }
        else if (sVar8 == 0xc) {
          if (*(int *)&pCGpffff86b4->field_0x4330 != 0) {
            AreaBlinkInit__5JRingFv(*(undefined4 *)&pCGpffff86b4->field_0x4330);
          }
          *(undefined2 *)(iStack_10 + 0x2a) = 3;
          *(undefined2 *)(iStack_10 + 0xb44) = 0xd;
          *(undefined2 *)(iStack_10 + 0xb46) = 0;
        }
        else if (sVar8 == 0xb) {
          *(undefined2 *)(iStack_10 + 0x2a) = 3;
          *(undefined2 *)(iStack_10 + 0xb44) = 0xc;
          *(undefined2 *)(iStack_10 + 0xb46) = 0;
        }
        else if (sVar8 == 7) {
          *(undefined2 *)(iStack_10 + 0x2a) = 3;
          *(undefined2 *)(iStack_10 + 0xb44) = 8;
          *(undefined2 *)(iStack_10 + 0xb46) = 0;
        }
        else if (sVar8 == 4) {
          if (*(int *)&pCGpffff86b4->field_0x4330 != 0) {
            AreaBlinkInit__5JRingFv(*(undefined4 *)&pCGpffff86b4->field_0x4330);
          }
          *(undefined2 *)(iStack_10 + 0x2a) = 3;
          *(undefined2 *)(iStack_10 + 0xb44) = 5;
          *(undefined2 *)(iStack_10 + 0xb46) = 0;
        }
        else if (sVar8 == 3) {
          if (*(int *)&pCGpffff86b4->field_0x4330 != 0) {
            AreaBlinkInit__5JRingFv(*(undefined4 *)&pCGpffff86b4->field_0x4330);
          }
          *(undefined2 *)(iStack_10 + 0x2a) = 3;
          *(undefined2 *)(iStack_10 + 0xb44) = 4;
          *(undefined2 *)(iStack_10 + 0xb46) = 0;
        }
        else if (sVar8 == 2) {
          *(undefined2 *)(iStack_10 + 0x2a) = 3;
          *(undefined2 *)(iStack_10 + 0xb44) = 3;
          *(undefined2 *)(iStack_10 + 0xb46) = 0;
        }
        else {
          if (pcGpffff86ec != (code *)0x0) {
            (*pcGpffff86ec)(0x16,0,0,0,0,0,uGpffff86e8);
          }
          *(undefined2 *)(iStack_10 + 0x28) = 0x14;
          *(undefined2 *)(iStack_10 + 0x2a) = 0;
        }
      }
    }
    else if (sVar8 == 1) {
      iStack_740 = *(int *)(iStack_10 + 0xb20);
      sVar8 = *(short *)(iStack_740 + 0x16);
      iStack_53c = iStack_740;
      sStack_21e = sVar8;
      sStack_21c = sVar8;
      iVar7 = iStack_10;
      if ((uVar2 & 0x10) != 0) {
        iVar7 = MoveCursor__6CursorFi(iStack_10 + 0xa34,1);
      }
      if ((uVar2 & 0x40) != 0) {
        MoveCursor__6CursorFi(iStack_10 + 0xa34,2,iVar7);
      }
      iStack_744 = *(int *)(iStack_10 + 0xb20);
      sVar13 = *(short *)(iStack_744 + 0x16);
      iStack_540 = iStack_744;
      sStack_222 = sVar13;
      sStack_220 = sVar13;
      if (sVar13 != sVar8) {
        uStack_748 = *(undefined4 *)(g_83f8 + 0xc);
        uStack_2dc = uStack_748;
        if (*(short *)(iStack_10 + 0xb44) == 0) {
          if (sVar13 == 0) {
            *(undefined4 *)(iStack_10 + 0x158) = 1;
            uVar6 = GetRegDat__9RegDatApiFiii(0x23,2,0xffffffffffffffff);
            SetNoteWindow__7BtlMenuFPc(iStack_10,uVar6);
          }
          else {
            *(undefined4 *)(iStack_10 + 0x158) = 2;
            uVar6 = GetRegDat__9RegDatApiFiii(0x23,4,0xffffffffffffffff);
            SetNoteWindow__7BtlMenuFPc(iStack_10,uVar6);
          }
        }
        else if (sVar13 == 0) {
          *(undefined4 *)(iStack_10 + 0x158) = 1;
          uVar6 = GetRegDat__9RegDatApiFiii(0x24,2,0xffffffffffffffff);
          SetNoteWindow__7BtlMenuFPc(iStack_10,uVar6);
        }
        else {
          *(undefined4 *)(iStack_10 + 0x158) = 2;
          uVar6 = GetRegDat__9RegDatApiFiii(0x24,4,0xffffffffffffffff);
          SetNoteWindow__7BtlMenuFPc(iStack_10,uVar6);
        }
        PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,0,1,0);
      }
      if ((uVar1 & 0x2000) != 0) {
        if (pcGpffff86ec != (code *)0x0) {
          (*pcGpffff86ec)(0x15,sVar13,0,0,0,0,uGpffff86e8);
        }
        AllWindowClose__7BtlMenuFv(iStack_10);
        AllBCurDestruct__7BtlMenuFv();
        *(undefined2 *)(iStack_10 + 0x28) = 0x14;
        *(undefined2 *)(iStack_10 + 0x2a) = 0;
        PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,2,1,0);
      }
    }
    else if (((sVar8 == 0) && (*(short *)(iStack_10 + 0x32) != 0xc)) &&
            (*(short *)(iStack_10 + 0x32) != 0xd)) {
      SetTutorialMenu__7BtlMenuFii(iStack_10,0,*(undefined2 *)(iStack_10 + 0xb44));
      uVar6 = SetWindowClose__7BtlMenuFii(iStack_10,1,6);
      if (*(short *)(iStack_10 + 0xb44) == 0) {
        CreateCursole__7BtlMenuFv(iStack_10);
        *(undefined4 *)(iStack_10 + 0x158) = 1;
        uVar6 = GetRegDat__9RegDatApiFiii(0x23,2,0xffffffffffffffff);
        SetNoteWindow__7BtlMenuFPc(iStack_10,uVar6);
        Select__6CursorFP9MenuPlace(iStack_10 + 0xa34,
                        *(int *)(iStack_10 + 0x130) + *(int *)(iStack_10 + 0x158) * 0x80);
        QuickMove__6CursorFv(iStack_10 + 0xa34);
        *(undefined2 *)(iStack_10 + 0x2a) = 1;
      }
      else if (*(short *)(iStack_10 + 0xb44) == 0x13) {
        uVar6 = CreateCursole__7BtlMenuFv(iStack_10);
        *(undefined4 *)(iStack_10 + 0x158) = 1;
        uVar6 = GetRegDat__9RegDatApiFiii(0x24,2,0xffffffffffffffff,uVar6);
        SetNoteWindow__7BtlMenuFPc(iStack_10,uVar6);
        uVar6 = Select__6CursorFP9MenuPlace(iStack_10 + 0xa34,
                                *(int *)(iStack_10 + 0x130) + *(int *)(iStack_10 + 0x158) * 0x80);
        QuickMove__6CursorFv(iStack_10 + 0xa34,uVar6);
        *(undefined2 *)(iStack_10 + 0x2a) = 1;
      }
      else {
        SetNoteWindowClose__7BtlMenuFv(iStack_10,uVar6);
        AllBCurDestruct__7BtlMenuFv();
        *(undefined2 *)(iStack_10 + 0x2a) = 2;
      }
      sVar8 = *(short *)(iStack_10 + 0xb44);
      if (sVar8 == 0xd) {
        if (*(int *)&pCGpffff86b4->field_0x4330 != 0) {
          AreaBlinkInit__5JRingFv(*(undefined4 *)&pCGpffff86b4->field_0x4330);
          SetAreaBlink__5JRingFiii(*(undefined4 *)&pCGpffff86b4->field_0x4330,1,1,0);
        }
      }
      else if (sVar8 == 0xc) {
        if (*(int *)&pCGpffff86b4->field_0x4330 != 0) {
          AreaBlinkInit__5JRingFv(*(undefined4 *)&pCGpffff86b4->field_0x4330);
          SetAreaBlink__5JRingFiii(*(undefined4 *)&pCGpffff86b4->field_0x4330,0,1,0);
        }
      }
      else if (sVar8 == 4) {
        if (*(int *)&pCGpffff86b4->field_0x4330 != 0) {
          AreaBlinkInit__5JRingFv(*(undefined4 *)&pCGpffff86b4->field_0x4330);
          SetAreaBlink__5JRingFiii(*(undefined4 *)&pCGpffff86b4->field_0x4330,0,2,0);
          SetAreaBlink__5JRingFiii(*(undefined4 *)&pCGpffff86b4->field_0x4330,1,2,0);
        }
      }
      else if ((sVar8 == 3) && (*(int *)&pCGpffff86b4->field_0x4330 != 0)) {
        AreaBlinkInit__5JRingFv(*(undefined4 *)&pCGpffff86b4->field_0x4330);
        SetAreaBlink__5JRingFiii(*(undefined4 *)&pCGpffff86b4->field_0x4330,0,3,0);
        SetAreaBlink__5JRingFiii(*(undefined4 *)&pCGpffff86b4->field_0x4330,1,3,0);
      }
      PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,0x2000000,1,0);
    }
    break;
  case 0x17:
    sVar8 = *(short *)(iStack_10 + 0x2a);
    if (sVar8 != 3) {
      if (sVar8 != 2) {
        if (sVar8 != 1) {
          if (sVar8 != 0) {
            return 0;
          }
          *(uint *)(iStack_10 + 0xb34) = (uint)pCGpffff86b4->wTurnPendMask;
          if (pCGpffff86b4->nPhase == 0xb) {
            lVar15 = 0;
            while (lVar15 < *(short *)&pCGpffff86b4->field_0x3c30) {
              iVar7 = (int)lVar15;
              if ((*(uint *)(iStack_10 + 0xb34) &
                  1 << (*(uint *)((int)(pCGpffff86b4->aChr + 0xc) + iVar7 * 0x14 + 0x44) & 0x1f)) !=
                  0) {
                *(int *)(iStack_10 + 0xb34) =
                     *(int *)(iStack_10 + 0xb34) -
                     (1 << (*(uint *)((int)(pCGpffff86b4->aChr + 0xc) + iVar7 * 0x14 + 0x44) & 0x1f)
                     );
              }
              lVar15 = (long)(iVar7 + 1);
            }
          }
          for (uVar12 = 0;
              ((int)uVar12 < 0xc && ((*(uint *)(iStack_10 + 0xb34) & 1 << (uVar12 & 0x1f)) == 0));
              uVar12 = uVar12 + 1) {
          }
          *(uint *)(iStack_10 + 0x168) = uVar12;
          SetComboShortCutMenu__7BtlMenuFiii(iStack_10,0,uVar12,0xffffffffffffffff);
          uVar6 = SetWindowClose__7BtlMenuFii(iStack_10,1,6);
          SetNoteWindowClose__7BtlMenuFv(iStack_10,uVar6);
          AllBCurDestruct__7BtlMenuFv();
          *(undefined2 *)(iStack_10 + 0x2a) = 1;
          *(undefined4 *)(iStack_10 + 0x2c) = 0;
          return 0;
        }
        if ((pCGpffff86b4->aChr[*(int *)(iStack_10 + 0x168)].bFlagsA1 & 1) == 0) {
          puStack_2d4 = (undefined1 *)
                        (ourBtlSaveDat +
                         pCGpffff86b4->aChr[*(int *)(iStack_10 + 0x168)].nCharId * 0x10 + 0xf44);
        }
        else {
          puStack_2d4 = (undefined1 *)
                        (ourBtlSaveDat + pCGpffff86b4->aChr[*(int *)(iStack_10 + 0x168)].nSubId * 0x10
                        + 0x1004);
        }
        bVar18 = false;
        if ((uVar2 & 0x80) != 0) {
          iVar7 = 0;
          while ((iVar7 < *(int *)&pCGpffff86b4->field_0x439c &&
                 (pCGpffff86b4->aChr[*(int *)(iStack_10 + 0x168)].nCharId !=
                  (ushort)*(byte *)((int)pCGpffff86b4->aMonIds + iVar7 + -6)))) {
            iVar7 = iVar7 + 1;
          }
          do {
            if (iVar7 + -1 < 0) goto code_r0x0059f9e8;
            for (uVar12 = 0;
                ((int)uVar12 < 0xc &&
                (pCGpffff86b4->aChr[uVar12].nCharId !=
                 (ushort)*(byte *)((int)pCGpffff86b4->aMonIds + iVar7 + -7))); uVar12 = uVar12 + 1)
            {
            }
            iVar7 = iVar7 + -1;
          } while ((*(uint *)(iStack_10 + 0xb34) & 1 << (uVar12 & 0x1f)) == 0);
          *(uint *)(iStack_10 + 0x168) = uVar12;
          bVar18 = true;
code_r0x0059f9e8:
          if (!bVar18) {
            iVar7 = *(int *)&pCGpffff86b4->field_0x439c;
            do {
              if (iVar7 + -1 < 0) goto code_r0x0059fab8;
              for (uVar12 = 0;
                  ((int)uVar12 < 0xc &&
                  (pCGpffff86b4->aChr[uVar12].nCharId !=
                   (ushort)*(byte *)((int)pCGpffff86b4->aMonIds + iVar7 + -7))); uVar12 = uVar12 + 1
                  ) {
              }
              iVar7 = iVar7 + -1;
            } while ((*(uint *)(iStack_10 + 0xb34) & 1 << (uVar12 & 0x1f)) == 0);
            *(uint *)(iStack_10 + 0x168) = uVar12;
            bVar18 = true;
          }
code_r0x0059fab8:
          PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,0,1,0);
        }
        if ((uVar2 & 0x20) != 0) {
          iVar7 = 0;
          while ((iVar7 < *(int *)&pCGpffff86b4->field_0x439c &&
                 (pCGpffff86b4->aChr[*(int *)(iStack_10 + 0x168)].nCharId !=
                  (ushort)*(byte *)((int)pCGpffff86b4->aMonIds + iVar7 + -6)))) {
            iVar7 = iVar7 + 1;
          }
          do {
            if (*(int *)&pCGpffff86b4->field_0x439c <= iVar7 + 1) goto code_r0x0059fc38;
            for (uVar12 = 0;
                ((int)uVar12 < 0xc &&
                (pCGpffff86b4->aChr[uVar12].nCharId !=
                 (ushort)*(byte *)((int)pCGpffff86b4->aMonIds + iVar7 + -5))); uVar12 = uVar12 + 1)
            {
            }
            iVar7 = iVar7 + 1;
          } while ((*(uint *)(iStack_10 + 0xb34) & 1 << (uVar12 & 0x1f)) == 0);
          *(uint *)(iStack_10 + 0x168) = uVar12;
          bVar18 = true;
code_r0x0059fc38:
          if (!bVar18) {
            for (iVar7 = 0; iVar7 < *(int *)&pCGpffff86b4->field_0x439c; iVar7 = iVar7 + 1) {
              for (uVar12 = 0;
                  ((int)uVar12 < 0xc &&
                  (pCGpffff86b4->aChr[uVar12].nCharId !=
                   (ushort)*(byte *)((int)pCGpffff86b4->aMonIds + iVar7 + -6))); uVar12 = uVar12 + 1
                  ) {
              }
              if ((*(uint *)(iStack_10 + 0xb34) & 1 << (uVar12 & 0x1f)) != 0) {
                *(uint *)(iStack_10 + 0x168) = uVar12;
                bVar18 = true;
                break;
              }
            }
          }
          PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,0,1,0);
        }
        if (bVar18) {
          SetComboShortCutMenu__7BtlMenuFiii
                    (iStack_10,0,*(undefined4 *)(iStack_10 + 0x168),0xffffffffffffffff);
        }
        if ((uVar2 & 0x400) != 0) {
          iStack_524 = GetPlace__10MenuWindowFss(iStack_10 + 0x7c,0,0x14);
          sStack_20e = *(short *)(iStack_524 + 0x16);
          sStack_20c = sStack_20e;
          if (sStack_20e != 0) {
            *(undefined4 *)(iStack_10 + 0x16c) = 0;
            *(undefined4 *)(iStack_10 + 0x2c) = 0;
            *(undefined2 *)(iStack_10 + 0x2a) = 2;
            if (pcGpffff86ec != (code *)0x0) {
              (*pcGpffff86ec)(0x14,*(undefined4 *)(iStack_10 + 0x168),*puStack_2d4,
                              *(undefined2 *)(puStack_2d4 + 2),puStack_2d4[1],0,uGpffff86e8);
            }
            uVar6 = PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,2,1,0);
            SetComboShortCutMenu__7BtlMenuFiii
                      (iStack_10,0,*(undefined4 *)(iStack_10 + 0x168),0,iStack_10,uVar6);
            return 0;
          }
        }
        if ((uVar2 & 0x800) != 0) {
          iStack_528 = GetPlace__10MenuWindowFss(iStack_10 + 0x7c,1,0x14);
          sStack_212 = *(short *)(iStack_528 + 0x16);
          sStack_210 = sStack_212;
          if (sStack_212 != 0) {
            *(undefined4 *)(iStack_10 + 0x16c) = 1;
            *(undefined4 *)(iStack_10 + 0x2c) = 0;
            lVar15 = (long)iStack_10;
            *(undefined2 *)(iStack_10 + 0x2a) = 2;
            uVar6 = 0;
            if (pcGpffff86ec != (code *)0x0) {
              uVar6 = (*pcGpffff86ec)(0x14,*(undefined4 *)(iStack_10 + 0x168),puStack_2d4[4],
                                      *(undefined2 *)(puStack_2d4 + 6),puStack_2d4[5],0,uGpffff86e8)
              ;
              lVar15 = extraout_t0;
            }
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,2,1,0,lVar15,2,uVar6);
            SetComboShortCutMenu__7BtlMenuFiii(iStack_10,0,*(undefined4 *)(iStack_10 + 0x168),1);
            return 0;
          }
        }
        if ((uVar2 & 0x100) != 0) {
          iStack_52c = GetPlace__10MenuWindowFss(iStack_10 + 0x7c,0,0x15);
          sStack_216 = *(short *)(iStack_52c + 0x16);
          sStack_214 = sStack_216;
          if (sStack_216 != 0) {
            *(undefined4 *)(iStack_10 + 0x16c) = 2;
            *(undefined4 *)(iStack_10 + 0x2c) = 0;
            *(undefined2 *)(iStack_10 + 0x2a) = 2;
            if (pcGpffff86ec != (code *)0x0) {
              (*pcGpffff86ec)(0x14,*(undefined4 *)(iStack_10 + 0x168),puStack_2d4[8],
                              *(undefined2 *)(puStack_2d4 + 10),puStack_2d4[9],0,uGpffff86e8);
            }
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,2,1,0);
            SetComboShortCutMenu__7BtlMenuFiii(iStack_10,0,*(undefined4 *)(iStack_10 + 0x168),2);
            return 0;
          }
        }
        if ((uVar2 & 0x200) == 0) {
          return 0;
        }
        iStack_530 = GetPlace__10MenuWindowFss(iStack_10 + 0x7c,1,0x15);
        sStack_21a = *(short *)(iStack_530 + 0x16);
        if (sStack_21a == 0) {
          return 0;
        }
        *(undefined4 *)(iStack_10 + 0x16c) = 3;
        *(undefined4 *)(iStack_10 + 0x2c) = 0;
        *(undefined2 *)(iStack_10 + 0x2a) = 2;
        sStack_218 = sStack_21a;
        if (pcGpffff86ec != (code *)0x0) {
          (*pcGpffff86ec)(0x14,*(undefined4 *)(iStack_10 + 0x168),puStack_2d4[0xc],
                          *(undefined2 *)(puStack_2d4 + 0xe),puStack_2d4[0xd],0,uGpffff86e8);
        }
        PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,2,1,0);
        SetComboShortCutMenu__7BtlMenuFiii(iStack_10,0,*(undefined4 *)(iStack_10 + 0x168),3);
        return 0;
      }
      *(float *)(iStack_10 + 0x2c) = *(float *)(iStack_10 + 0x2c) + pCGpffff86b4->flDeltaT;
      if (*(float *)(iStack_10 + 0x2c) < 1.0) {
        return 0;
      }
      *(undefined2 *)(iStack_10 + 0x2a) = 3;
    }
    AllWindowClose__7BtlMenuFv(iStack_10);
    *(undefined2 *)(iStack_10 + 0x28) = 0x14;
    *(undefined2 *)(iStack_10 + 0x2a) = 0;
    break;
  case 0x18:
    sVar8 = *(short *)(iStack_10 + 0x2a);
    if (sVar8 != 3) {
      if (sVar8 != 2) {
        if (sVar8 != 1) {
          if (sVar8 != 0) {
            return 0;
          }
          if (*(short *)(iStack_10 + *(short *)(iStack_10 + 0xb50) * 0x16c + 0x32) == 0xc) {
            return 0;
          }
          if (*(short *)(iStack_10 + *(short *)(iStack_10 + 0xb50) * 0x16c + 0x32) == 0xd) {
            return 0;
          }
          SetComboShortCutSettingMenu__7BtlMenuFiii
                    (iStack_10,*(undefined2 *)(iStack_10 + 0xb50),pCGpffff86b4->cActor,
                     0xffffffffffffffff);
          AllBCurDestruct__7BtlMenuFv();
          *(undefined2 *)(iStack_10 + 0x2a) = 1;
          *(undefined4 *)(iStack_10 + 0x2c) = 0;
          return 0;
        }
        if ((*(byte *)((int)pCGpffff86b4 +
                      (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb1) & 1)
            == 0) {
          puStack_2d8 = (undefined1 *)
                        (ourBtlSaveDat +
                         *(short *)((int)pCGpffff86b4 +
                                   (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10
                                   + 0x120) * 0x10 + 0xf44);
        }
        else {
          puStack_2d8 = (undefined1 *)
                        (ourBtlSaveDat +
                         *(short *)((int)pCGpffff86b4 +
                                   (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10
                                   + 0xba) * 0x10 + 0x1004);
        }
        if ((uVar2 & 0x400) != 0) {
          *puStack_2d8 = *(undefined1 *)(iStack_10 + 0xb54);
          puStack_2d8[1] = *(undefined1 *)(iStack_10 + 0xb55);
          *(undefined2 *)(puStack_2d8 + 2) = *(undefined2 *)(iStack_10 + 0xb56);
          *(undefined4 *)(iStack_10 + *(short *)(iStack_10 + 0xb50) * 0x16c + 0x168) = 0;
          *(undefined4 *)(iStack_10 + 0x2c) = 0;
          *(undefined2 *)(iStack_10 + 0x2a) = 2;
          PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,2,1,0);
          SetComboShortCutSettingMenu__7BtlMenuFiii
                    (iStack_10,*(undefined2 *)(iStack_10 + 0xb50),pCGpffff86b4->cActor,0);
          return 0;
        }
        if ((uVar2 & 0x800) != 0) {
          puStack_2d8[4] = *(undefined1 *)(iStack_10 + 0xb54);
          puStack_2d8[5] = *(undefined1 *)(iStack_10 + 0xb55);
          *(undefined2 *)(puStack_2d8 + 6) = *(undefined2 *)(iStack_10 + 0xb56);
          *(undefined4 *)(iStack_10 + *(short *)(iStack_10 + 0xb50) * 0x16c + 0x168) = 1;
          *(undefined4 *)(iStack_10 + 0x2c) = 0;
          *(undefined2 *)(iStack_10 + 0x2a) = 2;
          PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,2,1,0);
          SetComboShortCutSettingMenu__7BtlMenuFiii
                    (iStack_10,*(undefined2 *)(iStack_10 + 0xb50),pCGpffff86b4->cActor,1);
          return 0;
        }
        if ((uVar2 & 0x100) != 0) {
          puStack_2d8[8] = *(undefined1 *)(iStack_10 + 0xb54);
          puStack_2d8[9] = *(undefined1 *)(iStack_10 + 0xb55);
          *(undefined2 *)(puStack_2d8 + 10) = *(undefined2 *)(iStack_10 + 0xb56);
          *(undefined4 *)(iStack_10 + *(short *)(iStack_10 + 0xb50) * 0x16c + 0x168) = 2;
          *(undefined4 *)(iStack_10 + 0x2c) = 0;
          *(undefined2 *)(iStack_10 + 0x2a) = 2;
          PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,2,1,0);
          SetComboShortCutSettingMenu__7BtlMenuFiii
                    (iStack_10,*(undefined2 *)(iStack_10 + 0xb50),pCGpffff86b4->cActor,2);
          return 0;
        }
        if ((uVar2 & 0x200) != 0) {
          puStack_2d8[0xc] = *(undefined1 *)(iStack_10 + 0xb54);
          puStack_2d8[0xd] = *(undefined1 *)(iStack_10 + 0xb55);
          *(undefined2 *)(puStack_2d8 + 0xe) = *(undefined2 *)(iStack_10 + 0xb56);
          *(undefined4 *)(iStack_10 + *(short *)(iStack_10 + 0xb50) * 0x16c + 0x168) = 3;
          *(undefined4 *)(iStack_10 + 0x2c) = 0;
          *(undefined2 *)(iStack_10 + 0x2a) = 2;
          PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,2,1,0);
          SetComboShortCutSettingMenu__7BtlMenuFiii
                    (iStack_10,*(undefined2 *)(iStack_10 + 0xb50),pCGpffff86b4->cActor,3);
          return 0;
        }
        if ((uVar1 & 0x4000) == 0) {
          return 0;
        }
        SetWindowClose__7BtlMenuFii(iStack_10,*(undefined2 *)(iStack_10 + 0xb50),0xffffffffffffffff)
        ;
        *(byte *)(iStack_10 + 0x24) = *(byte *)(iStack_10 + 0x24) & 0xfd;
        *(undefined2 *)(iStack_10 + 0x28) = *(undefined2 *)(iStack_10 + 0xb4c);
        *(undefined2 *)(iStack_10 + 0x2a) = *(undefined2 *)(iStack_10 + 0xb4e);
        PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,3,1,0);
        if (4 < *(int *)(iStack_10 + (*(short *)(iStack_10 + 0xb50) + -1) * 0x16c + 0x170)) {
          if (*(int *)(iStack_10 + 0xb30) == 0) {
            iStack_738 = __nw__FUi(0x84);
            if (iStack_738 != 0) {
              iStack_738 = __ct__10ScrollMarkFv(iStack_738);
            }
            *(int *)(iStack_10 + 0xb30) = iStack_738;
            Create__10ScrollMarkFUcP10MenuWindowUc(*(undefined4 *)(iStack_10 + 0xb30),3,0,0);
            iStack_534 = *(int *)(iStack_10 + 0xb30);
            *(undefined2 *)(iStack_534 + 0x14) = 0x10;
            AddOT__7MenuObjFv(*(undefined4 *)(iStack_10 + 0xb30));
            *(byte *)(iStack_10 + 0x25) = *(byte *)(iStack_10 + 0x25) & 0xfd | 2;
            *(undefined2 *)(iStack_10 + 0xa32) = 1;
          }
          SetArea__10ScrollMarkFUcffff(*pfRam0040ab1c + 48.0,
                          *(undefined4 *)
                           (iStack_10 + (*(short *)(iStack_10 + 0xb50) + -1) * 0x16c + 0x17c),
                          pfRam0040ab1c[2] - 80.0,
                          *(undefined4 *)
                           (iStack_10 + (*(short *)(iStack_10 + 0xb50) + -1) * 0x16c + 0x180),
                          *(undefined4 *)(iStack_10 + 0xb30),3);
          bVar14 = 0 < *(int *)(iStack_10 + (*(short *)(iStack_10 + 0xb50) + -1) * 0x16c + 0x174);
          if (*(int *)(iStack_10 + (*(short *)(iStack_10 + 0xb50) + -1) * 0x16c + 0x174) * 4 + 4 <
              *(int *)(iStack_10 + (*(short *)(iStack_10 + 0xb50) + -1) * 0x16c + 0x170)) {
            bVar14 = bVar14 | 2;
          }
          SetMark__10ScrollMarkFUc(*(undefined4 *)(iStack_10 + 0xb30),bVar14);
          return 0;
        }
        if (*(short *)(iStack_10 + 0xa32) != 1) {
          return 0;
        }
        *(undefined2 *)(iStack_10 + 0xa32) = 2;
        return 0;
      }
      *(float *)(iStack_10 + 0x2c) = *(float *)(iStack_10 + 0x2c) + pCGpffff86b4->flDeltaT;
      if (*(float *)(iStack_10 + 0x2c) < 1.0) {
        return 0;
      }
      *(undefined2 *)(iStack_10 + 0x2a) = 3;
    }
    SetWindowClose__7BtlMenuFii(iStack_10,*(undefined2 *)(iStack_10 + 0xb50),0xffffffffffffffff);
    *(byte *)(iStack_10 + 0x24) = *(byte *)(iStack_10 + 0x24) & 0xfd;
    *(undefined2 *)(iStack_10 + 0x28) = *(undefined2 *)(iStack_10 + 0xb4c);
    *(undefined2 *)(iStack_10 + 0x2a) = *(undefined2 *)(iStack_10 + 0xb4e);
    if (*(int *)(iStack_10 + *(short *)(iStack_10 + 0xb52) * 0x16c + 0x170) < 5) {
      if (*(short *)(iStack_10 + 0xa32) == 1) {
        *(undefined2 *)(iStack_10 + 0xa32) = 2;
      }
    }
    else {
      if (*(int *)(iStack_10 + 0xb30) == 0) {
        iStack_73c = __nw__FUi(0x84);
        if (iStack_73c != 0) {
          iStack_73c = __ct__10ScrollMarkFv(iStack_73c);
        }
        *(int *)(iStack_10 + 0xb30) = iStack_73c;
        Create__10ScrollMarkFUcP10MenuWindowUc(*(undefined4 *)(iStack_10 + 0xb30),3,0,0);
        iStack_538 = *(int *)(iStack_10 + 0xb30);
        *(undefined2 *)(iStack_538 + 0x14) = 0x10;
        AddOT__7MenuObjFv(*(undefined4 *)(iStack_10 + 0xb30));
        *(byte *)(iStack_10 + 0x25) = *(byte *)(iStack_10 + 0x25) & 0xfd | 2;
        *(undefined2 *)(iStack_10 + 0xa32) = 1;
      }
      SetArea__10ScrollMarkFUcffff(*pfRam0040ab1c + 48.0,
                      *(undefined4 *)(iStack_10 + *(short *)(iStack_10 + 0xb52) * 0x16c + 0x17c),
                      pfRam0040ab1c[2] - 80.0,
                      *(undefined4 *)(iStack_10 + *(short *)(iStack_10 + 0xb52) * 0x16c + 0x180),
                      *(undefined4 *)(iStack_10 + 0xb30),3);
      bVar14 = 0 < *(int *)(iStack_10 + *(short *)(iStack_10 + 0xb52) * 0x16c + 0x174);
      if (*(int *)(iStack_10 + *(short *)(iStack_10 + 0xb52) * 0x16c + 0x174) * 4 + 4 <
          *(int *)(iStack_10 + *(short *)(iStack_10 + 0xb52) * 0x16c + 0x170)) {
        bVar14 = bVar14 | 2;
      }
      SetMark__10ScrollMarkFUc(*(undefined4 *)(iStack_10 + 0xb30),bVar14);
    }
  }
  return 0;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005a2020  MainMenuFunc__7BtlMenuFv
 * C++: BtlMenu::MainMenuFunc()
 * size: 0x3564 bytes
 * --------------------------------------------------------------------------- */
/* WARNING: Removing unreachable block (ram,0x005a45d0) */

undefined4 MainMenuFunc__7BtlMenuFv(int param_1)

{
  char cVar1;
  short sVar2;
  short sVar3;
  bool bVar4;
  bool bVar5;
  bool bVar6;
  bool bVar7;
  ushort uVar8;
  undefined8 uVar9;
  int iVar10;
  int iVar11;
  long lVar12;
  
  uVar8 = *(ushort *)(*(int *)(*(int *)(g_86c0 + 4) * 4 + 0x40ac00) + 0x70) & 0xff0 |
          *(ushort *)(*(int *)(*(int *)(g_86c0 + 4) * 4 + 0x40ac00) + 0x6c) & 0xf00f;
  if (*(short *)(param_1 + 0x2a) == 1) {
    if ((*(short *)(param_1 + 0x32) == 2) || (*(short *)(param_1 + 0x32) == 5)) {
      if (*(short *)(param_1 + 0xb44) == 1) {
        sVar2 = *(short *)(param_1 + 0xb46);
        if (sVar2 == 2) {
          uVar8 = 0;
          *(float *)(param_1 + 0xb48) = *(float *)(param_1 + 0xb48) - pCGpffff86b4->flDeltaT;
          if (*(float *)(param_1 + 0xb48) <= 0.0) {
            *(undefined4 *)(param_1 + 0xb48) = 0x3e800000;
            uVar8 = AutoMenuFunc__7BtlMenuFiiiii
                              (param_1,0,0,*(undefined2 *)(*(int *)(param_1 + 0xb20) + 0x1e),0,4);
            if ((uVar8 & 0x2000) == 0) {
              *(byte *)(param_1 + 0x25) = *(byte *)(param_1 + 0x25) & 0xfb;
            }
            else if ((long)((ulong)*(byte *)(param_1 + 0x25) << 0x3d) < 0) {
              *(undefined2 *)(param_1 + 0xb46) = 3;
              *(undefined4 *)(param_1 + 0xb48) = 0x3f800000;
            }
            else {
              uVar8 = 0;
              *(undefined4 *)(param_1 + 0xb48) = 0x3f400000;
              *(byte *)(param_1 + 0x25) = *(byte *)(param_1 + 0x25) & 0xfb | 4;
            }
          }
        }
        else if (sVar2 == 1) {
          uVar8 = 0;
          SetWindowClose__7BtlMenuFii(param_1,5,0xffffffffffffffff);
          *(undefined2 *)(param_1 + 0xb46) = 2;
          *(undefined4 *)(param_1 + 0xb48) = 0x3f800000;
          *(byte *)(param_1 + 0x25) = *(byte *)(param_1 + 0x25) & 0xfb | 4;
        }
        else if (sVar2 == 0) {
          uVar8 = 0;
        }
      }
      else if (*(short *)(param_1 + 0xb44) == 6) {
        if (*(short *)(param_1 + 0xb46) == 1) {
          uVar8 = 0;
          *(float *)(param_1 + 0xb48) = *(float *)(param_1 + 0xb48) - pCGpffff86b4->flDeltaT;
          if (*(float *)(param_1 + 0xb48) <= 0.0) {
            *(undefined4 *)(param_1 + 0xb48) = 0x3e800000;
            uVar8 = AutoMenuFunc__7BtlMenuFiiiii
                              (param_1,0,0,*(undefined2 *)(*(int *)(param_1 + 0xb20) + 0x1e),0,4);
            if ((uVar8 & 0x2000) == 0) {
              *(byte *)(param_1 + 0x25) = *(byte *)(param_1 + 0x25) & 0xfb;
            }
            else if ((long)((ulong)*(byte *)(param_1 + 0x25) << 0x3d) < 0) {
              *(undefined2 *)(param_1 + 0xb46) = 2;
              *(undefined4 *)(param_1 + 0xb48) = 0x3f800000;
            }
            else {
              uVar8 = 0;
              *(undefined4 *)(param_1 + 0xb48) = 0x3f400000;
              *(byte *)(param_1 + 0x25) = *(byte *)(param_1 + 0x25) & 0xfb | 4;
            }
          }
        }
        else if (*(short *)(param_1 + 0xb46) == 0) {
          uVar8 = 0;
          *(undefined2 *)(param_1 + 0xb46) = 1;
          *(undefined4 *)(param_1 + 0xb48) = 0x3f800000;
          *(byte *)(param_1 + 0x25) = *(byte *)(param_1 + 0x25) & 0xfb | 4;
        }
      }
      else if (*(short *)(param_1 + 0xb44) == 9) {
        sVar2 = *(short *)(param_1 + 0xb46);
        if (sVar2 == 2) {
          uVar8 = 0;
          if (*(short *)(param_1 + 0x74e) == 0) {
            *(undefined2 *)(param_1 + 0xb44) = 10;
            *(undefined2 *)(param_1 + 0xb46) = 0;
            SetTutorialMenu__7BtlMenuFii(param_1,5,*(undefined2 *)(param_1 + 0xb44));
          }
        }
        else if (sVar2 == 1) {
          uVar8 = 0;
          SetWindowClose__7BtlMenuFii(param_1,5,0xffffffffffffffff);
          *(undefined2 *)(param_1 + 0xb46) = 2;
        }
        else if (sVar2 == 0) {
          uVar8 = 0;
        }
      }
      else if (*(short *)(param_1 + 0xb44) == 10) {
        sVar2 = *(short *)(param_1 + 0xb46);
        if (sVar2 == 2) {
          uVar8 = 0;
          *(float *)(param_1 + 0xb48) = *(float *)(param_1 + 0xb48) - pCGpffff86b4->flDeltaT;
          if (*(float *)(param_1 + 0xb48) <= 0.0) {
            *(undefined4 *)(param_1 + 0xb48) = 0x3e800000;
            uVar8 = AutoMenuFunc__7BtlMenuFiiiii
                              (param_1,0,0,*(undefined2 *)(*(int *)(param_1 + 0xb20) + 0x1e),0x19,
                               0xffffffffffffffff);
            if ((uVar8 & 0x2000) == 0) {
              *(byte *)(param_1 + 0x25) = *(byte *)(param_1 + 0x25) & 0xfb;
            }
            else if ((long)((ulong)*(byte *)(param_1 + 0x25) << 0x3d) < 0) {
              *(undefined2 *)(param_1 + 0xb46) = 3;
              *(undefined4 *)(param_1 + 0xb48) = 0x3f800000;
            }
            else {
              uVar8 = 0;
              *(undefined4 *)(param_1 + 0xb48) = 0x3f400000;
              *(byte *)(param_1 + 0x25) = *(byte *)(param_1 + 0x25) & 0xfb | 4;
            }
          }
        }
        else if (sVar2 == 1) {
          uVar8 = 0;
          SetWindowClose__7BtlMenuFii(param_1,5,0xffffffffffffffff);
          *(undefined2 *)(param_1 + 0xb46) = 2;
          *(undefined4 *)(param_1 + 0xb48) = 0x3f800000;
          *(byte *)(param_1 + 0x25) = *(byte *)(param_1 + 0x25) & 0xfb | 4;
        }
        else if (sVar2 == 0) {
          uVar8 = 0;
        }
      }
      else if (*(short *)(param_1 + 0xb44) == 0x14) {
        sVar2 = *(short *)(param_1 + 0xb46);
        if (sVar2 == 2) {
          uVar8 = 0;
          *(float *)(param_1 + 0xb48) = *(float *)(param_1 + 0xb48) - pCGpffff86b4->flDeltaT;
          if (*(float *)(param_1 + 0xb48) <= 0.0) {
            *(undefined4 *)(param_1 + 0xb48) = 0x3e800000;
            uVar8 = AutoMenuFunc__7BtlMenuFiiiii
                              (param_1,0,0,*(undefined2 *)(*(int *)(param_1 + 0xb20) + 0x1e),10,
                               0xffffffffffffffff);
            if ((uVar8 & 0x2000) == 0) {
              *(byte *)(param_1 + 0x25) = *(byte *)(param_1 + 0x25) & 0xfb;
            }
            else if ((long)((ulong)*(byte *)(param_1 + 0x25) << 0x3d) < 0) {
              *(undefined2 *)(param_1 + 0xb46) = 3;
              *(undefined4 *)(param_1 + 0xb48) = 0x3f800000;
            }
            else {
              uVar8 = 0;
              *(undefined4 *)(param_1 + 0xb48) = 0x3f400000;
              *(byte *)(param_1 + 0x25) = *(byte *)(param_1 + 0x25) & 0xfb | 4;
            }
          }
        }
        else if (sVar2 == 1) {
          uVar8 = 0;
          SetWindowClose__7BtlMenuFii(param_1,5,0xffffffffffffffff);
          *(undefined2 *)(param_1 + 0xb46) = 2;
          *(undefined4 *)(param_1 + 0xb48) = 0x3f800000;
          *(byte *)(param_1 + 0x25) = *(byte *)(param_1 + 0x25) & 0xfb | 4;
        }
        else if (sVar2 == 0) {
          uVar8 = 0;
        }
      }
      else if (*(short *)(param_1 + 0xb44) == 0x15) {
        sVar2 = *(short *)(param_1 + 0xb46);
        if (sVar2 == 2) {
          uVar8 = 0;
          if (*(short *)(param_1 + 0x74e) == 0) {
            *(undefined2 *)(param_1 + 0xb44) = 0x16;
            *(undefined2 *)(param_1 + 0xb46) = 0;
            SetTutorialMenu__7BtlMenuFii(param_1,5,*(undefined2 *)(param_1 + 0xb44));
          }
        }
        else if (sVar2 == 1) {
          uVar8 = 0;
          SetWindowClose__7BtlMenuFii(param_1,5,0xffffffffffffffff);
          *(undefined2 *)(param_1 + 0xb46) = 2;
        }
        else if (sVar2 == 0) {
          uVar8 = 0;
        }
      }
      else if (*(short *)(param_1 + 0xb44) == 0x16) {
        sVar2 = *(short *)(param_1 + 0xb46);
        if (sVar2 == 2) {
          uVar8 = 0;
          if (*(short *)(param_1 + 0x74e) == 0) {
            *(undefined2 *)(param_1 + 0xb44) = 0x17;
            *(undefined2 *)(param_1 + 0xb46) = 0;
            SetTutorialMenu__7BtlMenuFii(param_1,5,*(undefined2 *)(param_1 + 0xb44));
          }
        }
        else if (sVar2 == 1) {
          uVar8 = 0;
          SetWindowClose__7BtlMenuFii(param_1,5,0xffffffffffffffff);
          *(undefined2 *)(param_1 + 0xb46) = 2;
        }
        else if (sVar2 == 0) {
          uVar8 = 0;
          *(float *)(param_1 + 0xb48) = *(float *)(param_1 + 0xb48) - pCGpffff86b4->flDeltaT;
          if (*(float *)(param_1 + 0xb48) <= 0.0) {
            *(undefined4 *)(param_1 + 0xb48) = 0x3f000000;
            uVar8 = AutoMenuFunc__7BtlMenuFiiiii
                              (param_1,0,0,*(undefined2 *)(*(int *)(param_1 + 0xb20) + 0x1e),0,4);
            if (uVar8 == 0x2000) {
              uVar8 = 0x20;
            }
          }
        }
      }
      else if (*(short *)(param_1 + 0xb44) == 0x17) {
        sVar2 = *(short *)(param_1 + 0xb46);
        if (sVar2 == 2) {
          uVar8 = 0;
          if (*(short *)(param_1 + 0x74e) == 0) {
            *(undefined2 *)(param_1 + 0xb44) = 0x18;
            *(undefined2 *)(param_1 + 0xb46) = 0;
            SetTutorialMenu__7BtlMenuFii(param_1,5,*(undefined2 *)(param_1 + 0xb44));
          }
        }
        else if (sVar2 == 1) {
          uVar8 = 0;
          SetWindowClose__7BtlMenuFii(param_1,5,0xffffffffffffffff);
          *(undefined2 *)(param_1 + 0xb46) = 2;
        }
        else if (sVar2 == 0) {
          uVar8 = 0;
          *(float *)(param_1 + 0xb48) = *(float *)(param_1 + 0xb48) - pCGpffff86b4->flDeltaT;
          if (*(float *)(param_1 + 0xb48) <= 0.0) {
            *(undefined4 *)(param_1 + 0xb48) = 0x3f000000;
            uVar8 = AutoMenuFunc__7BtlMenuFiiiii
                              (param_1,0,0,*(undefined2 *)(*(int *)(param_1 + 0xb20) + 0x1e),0,4);
            if (uVar8 == 0x2000) {
              uVar8 = 0x20;
            }
          }
        }
      }
      else if (*(short *)(param_1 + 0xb44) == 0x18) {
        sVar2 = *(short *)(param_1 + 0xb46);
        if (sVar2 == 2) {
          uVar8 = 0;
          *(float *)(param_1 + 0xb48) = *(float *)(param_1 + 0xb48) - pCGpffff86b4->flDeltaT;
          if (*(float *)(param_1 + 0xb48) <= 0.0) {
            *(undefined4 *)(param_1 + 0xb48) = 0x3e800000;
            uVar8 = AutoMenuFunc__7BtlMenuFiiiii
                              (param_1,0,0,*(undefined2 *)(*(int *)(param_1 + 0xb20) + 0x1e),3,
                               0xffffffffffffffff);
            if ((uVar8 & 0x2000) == 0) {
              *(byte *)(param_1 + 0x25) = *(byte *)(param_1 + 0x25) & 0xfb;
            }
            else if ((long)((ulong)*(byte *)(param_1 + 0x25) << 0x3d) < 0) {
              *(undefined2 *)(param_1 + 0xb46) = 3;
              *(undefined4 *)(param_1 + 0xb48) = 0x3f800000;
            }
            else {
              uVar8 = 0;
              *(undefined4 *)(param_1 + 0xb48) = 0x3f400000;
              *(byte *)(param_1 + 0x25) = *(byte *)(param_1 + 0x25) & 0xfb | 4;
            }
          }
        }
        else if (sVar2 == 1) {
          uVar8 = 0;
          SetWindowClose__7BtlMenuFii(param_1,5,0xffffffffffffffff);
          *(undefined2 *)(param_1 + 0xb46) = 2;
          *(undefined4 *)(param_1 + 0xb48) = 0x3f800000;
          *(byte *)(param_1 + 0x25) = *(byte *)(param_1 + 0x25) & 0xfb | 4;
        }
        else if (sVar2 == 0) {
          uVar8 = 0;
          *(float *)(param_1 + 0xb48) = *(float *)(param_1 + 0xb48) - pCGpffff86b4->flDeltaT;
          if (*(float *)(param_1 + 0xb48) <= 0.0) {
            *(undefined4 *)(param_1 + 0xb48) = 0x3e800000;
            uVar8 = AutoMenuFunc__7BtlMenuFiiiii
                              (param_1,0,0,*(undefined2 *)(*(int *)(param_1 + 0xb20) + 0x1e),3,
                               0xffffffffffffffff);
            if (uVar8 == 0x2000) {
              uVar8 = 0;
            }
          }
        }
      }
      else if (*(short *)(param_1 + 0xb44) == 0x1c) {
        sVar2 = *(short *)(param_1 + 0xb46);
        if (sVar2 == 2) {
          uVar8 = 0;
          if (*(short *)(param_1 + 0x74e) == 0) {
            *(undefined2 *)(param_1 + 0xb44) = 0x1d;
            *(undefined2 *)(param_1 + 0xb46) = 0;
            SetTutorialMenu__7BtlMenuFii(param_1,5,*(undefined2 *)(param_1 + 0xb44));
          }
        }
        else if (sVar2 == 1) {
          uVar8 = 0;
          SetWindowClose__7BtlMenuFii(param_1,5,0xffffffffffffffff);
          *(undefined2 *)(param_1 + 0xb46) = 2;
        }
        else if (sVar2 == 0) {
          uVar8 = 0;
        }
      }
      else if (*(short *)(param_1 + 0xb44) == 0x1d) {
        sVar2 = *(short *)(param_1 + 0xb46);
        if (sVar2 == 2) {
          uVar8 = 0;
          *(float *)(param_1 + 0xb48) = *(float *)(param_1 + 0xb48) - pCGpffff86b4->flDeltaT;
          if (*(float *)(param_1 + 0xb48) <= 0.0) {
            *(undefined4 *)(param_1 + 0xb48) = 0x3e800000;
            uVar8 = AutoMenuFunc__7BtlMenuFiiiii
                              (param_1,0,0,*(undefined2 *)(*(int *)(param_1 + 0xb20) + 0x1e),1,
                               0xffffffffffffffff);
            if ((uVar8 & 0x2000) == 0) {
              *(byte *)(param_1 + 0x25) = *(byte *)(param_1 + 0x25) & 0xfb;
            }
            else if ((long)((ulong)*(byte *)(param_1 + 0x25) << 0x3d) < 0) {
              *(undefined2 *)(param_1 + 0xb46) = 3;
              *(undefined4 *)(param_1 + 0xb48) = 0x3f800000;
            }
            else {
              uVar8 = 0;
              *(undefined4 *)(param_1 + 0xb48) = 0x3f400000;
              *(byte *)(param_1 + 0x25) = *(byte *)(param_1 + 0x25) & 0xfb | 4;
            }
          }
        }
        else if (sVar2 == 1) {
          uVar8 = 0;
          SetWindowClose__7BtlMenuFii(param_1,5,0xffffffffffffffff);
          *(undefined2 *)(param_1 + 0xb46) = 2;
          *(undefined4 *)(param_1 + 0xb48) = 0x3f800000;
          *(byte *)(param_1 + 0x25) = *(byte *)(param_1 + 0x25) & 0xfb | 4;
        }
        else if (sVar2 == 0) {
          uVar8 = 0;
        }
      }
      sVar2 = *(short *)(*(int *)(param_1 + 0xb20) + 0x16);
      lVar12 = 0;
      bVar4 = false;
      if ((uVar8 & 0x10) != 0) {
        bVar4 = true;
        if (*(short *)(*(int *)(param_1 + 0xb20) + 0x1e) < 1) {
          lVar12 = 1;
        }
        else {
          MoveCursor__6CursorFi(param_1 + 0xa34,1);
          *(int *)(param_1 + 0x16c) = *(int *)(param_1 + 0x16c) + -1;
          *(int *)(param_1 + 0x168) = (int)*(short *)(*(int *)(param_1 + 0xb20) + 0x16);
        }
      }
      if ((uVar8 & 0x40) != 0) {
        bVar4 = true;
        if ((*(short *)(*(int *)(param_1 + 0xb20) + 0x1e) + 1 < 4) &&
           (*(int *)(param_1 + 0x16c) + 1 < *(int *)(param_1 + 0x170))) {
          MoveCursor__6CursorFi(param_1 + 0xa34,2);
          *(int *)(param_1 + 0x16c) = *(int *)(param_1 + 0x16c) + 1;
          *(int *)(param_1 + 0x168) = (int)*(short *)(*(int *)(param_1 + 0xb20) + 0x16);
        }
        else {
          lVar12 = 2;
        }
      }
      bVar5 = false;
      if (((uVar8 & 0x500) != 0) && (0 < *(int *)(param_1 + 0x16c))) {
        bVar5 = true;
        iVar10 = *(int *)(param_1 + 0x16c) + -4;
        if (iVar10 < 0) {
          iVar10 = 0;
        }
        *(int *)(param_1 + 0x16c) = iVar10;
        if (iVar10 < 0) {
          iVar10 = iVar10 + 3;
        }
        *(int *)(param_1 + 0x174) = iVar10 >> 2;
        lVar12 = 3;
      }
      bVar6 = false;
      if (((uVar8 & 0xa00) != 0) && (*(int *)(param_1 + 0x16c) + 1 < *(int *)(param_1 + 0x170))) {
        bVar6 = true;
        iVar10 = *(int *)(param_1 + 0x16c) + 4;
        if (*(int *)(param_1 + 0x170) <= iVar10) {
          iVar10 = *(int *)(param_1 + 0x170) + -1;
        }
        *(int *)(param_1 + 0x16c) = iVar10;
        if (iVar10 < 0) {
          iVar10 = iVar10 + 3;
        }
        *(int *)(param_1 + 0x174) = iVar10 >> 2;
        lVar12 = 3;
      }
      bVar7 = false;
      if (lVar12 != 0) {
        if (lVar12 == 1) {
          *(int *)(param_1 + 0x16c) = *(int *)(param_1 + 0x16c) + -1;
          *(int *)(param_1 + 0x174) = *(int *)(param_1 + 0x174) + -1;
          if (*(int *)(param_1 + 0x174) < 0) {
            *(int *)(param_1 + 0x16c) = *(int *)(param_1 + 0x170) + -1;
            iVar10 = *(int *)(param_1 + 0x170);
            if (iVar10 < 0) {
              iVar10 = iVar10 + 3;
            }
            *(int *)(param_1 + 0x174) = iVar10 >> 2;
          }
        }
        else if (lVar12 == 2) {
          *(int *)(param_1 + 0x16c) = *(int *)(param_1 + 0x16c) + 1;
          *(int *)(param_1 + 0x174) = *(int *)(param_1 + 0x174) + 1;
          if (*(int *)(param_1 + 0x170) <= *(int *)(param_1 + 0x16c)) {
            *(undefined4 *)(param_1 + 0x16c) = 0;
            *(undefined4 *)(param_1 + 0x174) = 0;
          }
        }
        SetMainMenu__7BtlMenuFiiii
                  (param_1,0,*(undefined4 *)(param_1 + 0x16c),*(undefined1 *)(param_1 + 0xb43),
                   0xffffffffffffffff);
        Select__6CursorFP9MenuPlace(param_1 + 0xa34,*(int *)(param_1 + 0x130) + *(int *)(param_1 + 0x158) * 0x80
                       );
      }
      if (sVar2 != *(short *)(*(int *)(param_1 + 0xb20) + 0x16)) {
        *(int *)(param_1 + 0x158) = (int)*(short *)(*(int *)(param_1 + 0xb20) + 0x1e) << 1;
        *(undefined4 *)(param_1 + 0x164) = *(undefined4 *)(param_1 + 0x168);
      }
      if ((*(char *)(param_1 + 0xb42) < '\x02') ||
         ((((*(int *)(param_1 + 0x168) != 1 && (*(int *)(param_1 + 0x168) != 2)) &&
           (*(int *)(param_1 + 0x168) != 3)) && (*(int *)(param_1 + 0x168) != 4)))) {
        if (*(int *)(param_1 + 0x140) != 0) {
          SetMark__10ScrollMarkFUc(*(undefined4 *)(param_1 + 0x140),0);
        }
      }
      else {
        if (*(int *)(param_1 + 0x140) != 0) {
          SetMark__10ScrollMarkFUc(*(undefined4 *)(param_1 + 0x140),0xc);
        }
        cVar1 = *(char *)(param_1 + 0xb43);
        if ((uVar8 & 0x80) != 0) {
          bVar7 = true;
          do {
            if (*(char *)(param_1 + 0xb43) < '\x01') {
              *(undefined1 *)(param_1 + 0xb43) = 3;
            }
            else {
              *(char *)(param_1 + 0xb43) = *(char *)(param_1 + 0xb43) + -1;
            }
          } while (((uint)*(ushort *)(param_1 + 0xb40) &
                   1 << ((int)*(char *)(param_1 + 0xb43) & 0x1fU)) == 0);
        }
        if ((uVar8 & 0x20) != 0) {
          bVar7 = true;
          do {
            *(char *)(param_1 + 0xb43) = *(char *)(param_1 + 0xb43) + '\x01';
            if ('\x03' < *(char *)(param_1 + 0xb43)) {
              *(undefined1 *)(param_1 + 0xb43) = 0;
            }
          } while (((uint)*(ushort *)(param_1 + 0xb40) &
                   1 << ((int)*(char *)(param_1 + 0xb43) & 0x1fU)) == 0);
        }
        if (cVar1 != *(char *)(param_1 + 0xb43)) {
          SetMainMenu__7BtlMenuFiiii
                    (param_1,0,*(undefined4 *)(param_1 + 0x16c),*(undefined1 *)(param_1 + 0xb43),
                     0xffffffffffffffff);
          Select__6CursorFP9MenuPlace(param_1 + 0xa34,
                          *(int *)(param_1 + 0x130) + *(int *)(param_1 + 0x158) * 0x80);
        }
      }
      sVar3 = *(short *)(*(int *)(param_1 + 0xb20) + 0x16);
      if (sVar2 != sVar3) {
        *(int *)(param_1 + 0x158) = (int)*(short *)(*(int *)(param_1 + 0xb20) + 0x1e) << 1;
        *(undefined4 *)(param_1 + 0x164) = *(undefined4 *)(param_1 + 0x168);
        if (bVar4) {
          PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,0,1,0);
        }
        else if (bVar5) {
          PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,7,1,0);
        }
        else if (bVar6) {
          PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,6,1,0);
        }
        else if (bVar7) {
          PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,1,1,0);
        }
      }
      if ((sVar3 != sVar2) || (-1 < (long)((ulong)*(byte *)(param_1 + 0x24) << 0x3e))) {
        lVar12 = (long)sVar3;
        if (999 < sVar3) {
          lVar12 = (long)(sVar3 + -1000);
        }
        uVar9 = SetNoteWindow__7BtlMenuFPc(param_1,*(undefined4 *)(iRam0040ab30 + (int)lVar12 * 4));
        switch(lVar12) {
        case 1:
        case 2:
        case 3:
        case 4:
          if (*(int *)(param_1 + 0x140) != 0) {
            if (*(char *)(param_1 + 0xb42) < '\x02') {
              SetMark__10ScrollMarkFUc(*(undefined4 *)(param_1 + 0x140),0);
            }
            else {
              SetMark__10ScrollMarkFUc(*(undefined4 *)(param_1 + 0x140),0xc);
            }
          }
          MakeTurnOrderTable__7CBattleFfiPiiiPUisibi
                    (pCGpffff86b4,3.0,0,(int *)0x0,0,0,(uint *)0x0,(short)pCGpffff86b4->cActor,-1,
                     true,-2);
          break;
        case 5:
        case 0xd:
        case 0xe:
        case 0xf:
        case 0x10:
        case 0x12:
        case 0x13:
        case 0x14:
        case 0x19:
        case 0x1a:
          if (*(int *)(param_1 + 0x140) != 0) {
            SetMark__10ScrollMarkFUc(*(undefined4 *)(param_1 + 0x140),0,uVar9);
          }
          MakeTurnOrderTable__7CBattleFfiPiiiPUisibi
                    (pCGpffff86b4,3.0,0,(int *)0x0,0,0,(uint *)0x0,(short)pCGpffff86b4->cActor,-1,
                     true,-2);
          break;
        case 6:
          if (*(int *)(param_1 + 0x140) != 0) {
            SetMark__10ScrollMarkFUc(*(undefined4 *)(param_1 + 0x140),0,uVar9);
          }
          MakeTurnOrderTable__7CBattleFfiPiiiPUisibi
                    (pCGpffff86b4,3.0,0,(int *)0x0,0,0,(uint *)0x0,(short)pCGpffff86b4->cActor,-1,
                     true,-2);
          break;
        case 8:
          if (*(int *)(param_1 + 0x140) != 0) {
            SetMark__10ScrollMarkFUc(*(undefined4 *)(param_1 + 0x140),0);
          }
          MakeTurnOrderTable__7CBattleFfiPiiiPUisibi
                    (pCGpffff86b4,3.0,0,(int *)0x0,0,0,(uint *)0x0,(short)pCGpffff86b4->cActor,-1,
                     true,-2);
          break;
        case 9:
          if (*(int *)(param_1 + 0x140) != 0) {
            SetMark__10ScrollMarkFUc(*(undefined4 *)(param_1 + 0x140),0);
          }
          MakeTurnOrderTable__7CBattleFfiPiiiPUisibi
                    (pCGpffff86b4,2.5,0,(int *)0x0,0,0,(uint *)0x0,(short)pCGpffff86b4->cActor,-1,
                     true,-2);
          break;
        case 10:
          if (*(int *)(param_1 + 0x140) != 0) {
            SetMark__10ScrollMarkFUc(*(undefined4 *)(param_1 + 0x140),0,uVar9);
          }
          MakeTurnOrderTable__7CBattleFfiPiiiPUisibi
                    (pCGpffff86b4,2.5,0,(int *)0x0,0,0,(uint *)0x0,(short)pCGpffff86b4->cActor,-1,
                     true,-2);
          break;
        case 0xb:
          if (*(int *)(param_1 + 0x140) != 0) {
            SetMark__10ScrollMarkFUc(*(undefined4 *)(param_1 + 0x140),0,uVar9);
          }
          MakeTurnOrderTable__7CBattleFfiPiiiPUisibi
                    (pCGpffff86b4,3.0,0,(int *)0x0,0,0,(uint *)0x0,(short)pCGpffff86b4->cActor,-1,
                     true,-2);
          break;
        case 0xc:
        case 0x15:
          if (*(int *)(param_1 + 0x140) != 0) {
            SetMark__10ScrollMarkFUc(*(undefined4 *)(param_1 + 0x140),0,uVar9);
          }
          MakeTurnOrderTable__7CBattleFfiPiiiPUisibi
                    (pCGpffff86b4,3.0,0,(int *)0x0,0,0,(uint *)0x0,(short)pCGpffff86b4->cActor,-1,
                     true,-2);
          break;
        case 0x16:
        case 0x17:
        case 0x18:
          if (*(int *)(param_1 + 0x140) != 0) {
            SetMark__10ScrollMarkFUc(*(undefined4 *)(param_1 + 0x140),0,uVar9);
          }
          iVar10 = GetRegDat__9RegDatApiFiii(0x36,*(undefined2 *)
                                         ((int)pCGpffff86b4 +
                                         (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) *
                                         0x10 + 0x120),0xffffffffffffffff);
          MakeTurnOrderTable__7CBattleFfiPiiiPUisibi
                    (pCGpffff86b4,(float)*(ushort *)(iVar10 + 0x1a) / 100.0,0,(int *)0x0,0,0,
                     (uint *)0x0,(short)pCGpffff86b4->cActor,-1,true,-2);
        }
        *(byte *)(param_1 + 0x24) = *(byte *)(param_1 + 0x24) & 0xfd | 2;
      }
      if ((uVar8 & 0x2000) != 0) {
        switch(sVar3) {
        case 1:
        case 2:
        case 3:
        case 4:
          if (*(short *)(param_1 + 0xb58) != sVar3) {
            *(undefined2 *)(param_1 + 0xb5e) = 0xffff;
            *(undefined2 *)(param_1 + 0xb5c) = 0xffff;
            *(undefined2 *)(param_1 + 0xb5a) = 0xffff;
          }
          *(short *)(param_1 + 0xb58) = sVar3;
          *(undefined2 *)(param_1 + 0x28) = 1;
          *(undefined2 *)(param_1 + 0x2a) = 0;
          PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,2,1,0);
          return 0;
        case 5:
          if (*(short *)(param_1 + 0xb58) != sVar3) {
            *(undefined2 *)(param_1 + 0xb5e) = 0xffff;
            *(undefined2 *)(param_1 + 0xb5c) = 0xffff;
            *(undefined2 *)(param_1 + 0xb5a) = 0xffff;
          }
          *(short *)(param_1 + 0xb58) = sVar3;
          *(undefined2 *)(param_1 + 0x28) = 0x12;
          *(undefined2 *)(param_1 + 0x2a) = 0;
          PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,2,1,0);
          return 0;
        case 6:
          if (*(short *)(param_1 + 0xb58) != sVar3) {
            *(undefined2 *)(param_1 + 0xb5e) = 0xffff;
            *(undefined2 *)(param_1 + 0xb5c) = 0xffff;
            *(undefined2 *)(param_1 + 0xb5a) = 0xffff;
          }
          *(short *)(param_1 + 0xb58) = sVar3;
          *(undefined2 *)(param_1 + 0x28) = 2;
          *(undefined2 *)(param_1 + 0x2a) = 0;
          PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,2,1,0);
          return 0;
        case 8:
          if (*(short *)(param_1 + 0xb58) != sVar3) {
            *(undefined2 *)(param_1 + 0xb5e) = 0xffff;
            *(undefined2 *)(param_1 + 0xb5c) = 0xffff;
            *(undefined2 *)(param_1 + 0xb5a) = 0xffff;
          }
          *(short *)(param_1 + 0xb58) = sVar3;
          *(undefined2 *)(param_1 + 0x28) = 4;
          *(undefined2 *)(param_1 + 0x2a) = 0;
          PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,2,1,0);
          return 0;
        case 9:
          if (*(short *)(param_1 + 0xb58) != sVar3) {
            *(undefined2 *)(param_1 + 0xb5e) = 0xffff;
            *(undefined2 *)(param_1 + 0xb5c) = 0xffff;
            *(undefined2 *)(param_1 + 0xb5a) = 0xffff;
          }
          *(short *)(param_1 + 0xb58) = sVar3;
          *(undefined2 *)(param_1 + 0x28) = 8;
          *(undefined2 *)(param_1 + 0x2a) = 0;
          PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,2,1,0);
          return 0;
        case 10:
          iVar10 = 0;
          lVar12 = 0;
          while (lVar12 < 0xc) {
            iVar11 = (int)lVar12;
            if ((((pCGpffff86b4->aChr[iVar11].bFlagsA & 1) != 0) &&
                ((long)((ulong)pCGpffff86b4->aChr[iVar11].bFlagsA << 0x3e) < 0)) &&
               ((-1 < (long)((ulong)pCGpffff86b4->aChr[iVar11].bFlagsA2 << 0x3d) &&
                (((lVar12 != pCGpffff86b4->cActor && (0 < pCGpffff86b4->aChr[iVar11].nHp)) &&
                 ((*(byte *)((int)pCGpffff86b4 +
                            (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb4)
                  & 1) == (pCGpffff86b4->aChr[iVar11].bFlagsB & 1))))))) {
              iVar10 = iVar10 + 1;
            }
            lVar12 = (long)(iVar11 + 1);
          }
          if (iVar10 != 0) {
            if (*(short *)(param_1 + 0xb58) != sVar3) {
              *(undefined2 *)(param_1 + 0xb5e) = 0xffff;
              *(undefined2 *)(param_1 + 0xb5c) = 0xffff;
              *(undefined2 *)(param_1 + 0xb5a) = 0xffff;
            }
            *(short *)(param_1 + 0xb58) = sVar3;
            *(undefined2 *)(param_1 + 0x28) = 9;
            *(undefined2 *)(param_1 + 0x2a) = 0;
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,2,1,0);
            return 0;
          }
          break;
        case 0xb:
          *(short *)((int)pCGpffff86b4 +
                    (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x598) =
               sVar3;
          *(undefined2 *)
           ((int)pCGpffff86b4 +
           (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x59a) = 0xffff;
          *(undefined2 *)
           ((int)pCGpffff86b4 +
           (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x59c) = 0xffff;
          *(undefined2 *)
           ((int)pCGpffff86b4 +
           (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x59e) = 0xffff;
          if (*(int *)(param_1 + 0x140) != 0) {
            SetMark__10ScrollMarkFUc(*(undefined4 *)(param_1 + 0x140),0);
          }
          if (pcGpffff86ec != (code *)0x0) {
            (*pcGpffff86ec)(10,0,0,0,0,0,uGpffff86e8);
          }
          AllWindowClose__7BtlMenuFv(param_1);
          AllBCurDestruct__7BtlMenuFv();
          *(undefined2 *)(param_1 + 0x28) = 0x14;
          *(undefined2 *)(param_1 + 0x2a) = 0;
          *(byte *)(param_1 + 0x24) = *(byte *)(param_1 + 0x24) & 0xfd;
          PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,2,1,0);
          return 0;
        case 0xc:
        case 0x15:
          if (*(short *)(param_1 + 0xb58) != sVar3) {
            *(undefined2 *)(param_1 + 0xb5e) = 0xffff;
            *(undefined2 *)(param_1 + 0xb5c) = 0xffff;
            *(undefined2 *)(param_1 + 0xb5a) = 0xffff;
          }
          *(short *)(param_1 + 0xb58) = sVar3;
          *(undefined2 *)(param_1 + 0x28) = 0xb;
          *(undefined2 *)(param_1 + 0x2a) = 0;
          PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,2,1,0);
          return 0;
        case 0xd:
        case 0xe:
        case 0x12:
        case 0x13:
        case 0x14:
        case 0x19:
        case 0x1a:
          if (*(short *)(param_1 + 0xb58) != sVar3) {
            *(undefined2 *)(param_1 + 0xb5e) = 0xffff;
            *(undefined2 *)(param_1 + 0xb5c) = 0xffff;
            *(undefined2 *)(param_1 + 0xb5a) = 0xffff;
          }
          *(short *)(param_1 + 0xb58) = sVar3;
          *(undefined2 *)(param_1 + 0x28) = 0xc;
          *(undefined2 *)(param_1 + 0x2a) = 0;
          PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,2,1,0);
          return 0;
        case 0xf:
          *(short *)((int)pCGpffff86b4 +
                    (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x598) =
               sVar3;
          *(undefined2 *)
           ((int)pCGpffff86b4 +
           (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x59a) = 0xffff;
          *(undefined2 *)
           ((int)pCGpffff86b4 +
           (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x59c) = 0xffff;
          *(undefined2 *)
           ((int)pCGpffff86b4 +
           (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x59e) = 0xffff;
          if (*(int *)(param_1 + 0x140) != 0) {
            SetMark__10ScrollMarkFUc(*(undefined4 *)(param_1 + 0x140),0);
          }
          if (pcGpffff86ec != (code *)0x0) {
            (*pcGpffff86ec)(0xd,0,0,0,0,0,uGpffff86e8);
          }
          AllWindowClose__7BtlMenuFv(param_1);
          AllBCurDestruct__7BtlMenuFv();
          *(undefined2 *)(param_1 + 0x28) = 0x14;
          *(undefined2 *)(param_1 + 0x2a) = 0;
          *(byte *)(param_1 + 0x24) = *(byte *)(param_1 + 0x24) & 0xfd;
          PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,2,1,0);
          return 0;
        case 0x10:
          if (*(short *)(param_1 + 0xb58) != sVar3) {
            *(undefined2 *)(param_1 + 0xb5e) = 0xffff;
            *(undefined2 *)(param_1 + 0xb5c) = 0xffff;
            *(undefined2 *)(param_1 + 0xb5a) = 0xffff;
          }
          *(short *)(param_1 + 0xb58) = sVar3;
          *(undefined2 *)(param_1 + 0x28) = 0xf;
          *(undefined2 *)(param_1 + 0x2a) = 0;
          PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,2,1,0);
          return 0;
        case 0x11:
          if (*(short *)(param_1 + 0xb58) != sVar3) {
            *(undefined2 *)(param_1 + 0xb5e) = 0xffff;
            *(undefined2 *)(param_1 + 0xb5c) = 0xffff;
            *(undefined2 *)(param_1 + 0xb5a) = 0xffff;
          }
          *(short *)(param_1 + 0xb58) = sVar3;
          *(undefined2 *)(param_1 + 0x28) = 0x11;
          *(undefined2 *)(param_1 + 0x2a) = 0;
          PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,2,1,0);
          return 0;
        case 0x16:
        case 0x17:
        case 0x18:
          if (*(short *)(param_1 + 0xb58) != sVar3) {
            *(undefined2 *)(param_1 + 0xb5e) = 0xffff;
            *(undefined2 *)(param_1 + 0xb5c) = 0xffff;
            *(undefined2 *)(param_1 + 0xb5a) = 0xffff;
          }
          *(short *)(param_1 + 0xb58) = sVar3;
          *(undefined2 *)(param_1 + 0x28) = 0xe;
          *(undefined2 *)(param_1 + 0x2a) = 0;
          PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,2,1,0);
          return 0;
        }
        PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,4,1,0);
      }
      if (((*(byte *)(param_1 + 0x24) & 1) == 0) || ((uVar8 & 0x4000) == 0)) {
        if (((long)((ulong)*(byte *)(ourBtlSaveDat + 3) << 0x3e) < 0) &&
           (((*(byte *)((int)pCGpffff86b4 +
                       (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb4) & 1)
             == 0 && ((uVar8 & 0x1000) != 0)))) {
          if ((sVar3 == 4) || (((sVar3 == 3 || (sVar3 == 2)) || (sVar3 == 1)))) {
            *(undefined2 *)(param_1 + 0xb4c) = *(undefined2 *)(param_1 + 0x28);
            *(undefined2 *)(param_1 + 0xb4e) = *(undefined2 *)(param_1 + 0x2a);
            *(undefined2 *)(param_1 + 0xb50) = 1;
            *(undefined2 *)(param_1 + 0xb52) = 0;
            *(undefined1 *)(param_1 + 0xb54) = 0;
            if (sVar3 == 4) {
              *(undefined1 *)(param_1 + 0xb55) = 3;
            }
            else if (sVar3 == 3) {
              *(undefined1 *)(param_1 + 0xb55) = 2;
            }
            else if (sVar3 == 2) {
              *(undefined1 *)(param_1 + 0xb55) = 1;
            }
            else {
              *(undefined1 *)(param_1 + 0xb55) = 0;
            }
            *(undefined2 *)(param_1 + 0xb56) = 0xffff;
            if (*(int *)(param_1 + 0x140) != 0) {
              SetMark__10ScrollMarkFUc(*(undefined4 *)(param_1 + 0x140),0);
            }
            *(undefined2 *)(param_1 + 0x28) = 0x18;
            *(undefined2 *)(param_1 + 0x2a) = 0;
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,2,1,0);
            return 0;
          }
          PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,4,1,0);
        }
      }
      else {
        if (*(int *)(param_1 + 0x140) != 0) {
          SetMark__10ScrollMarkFUc(*(undefined4 *)(param_1 + 0x140),0);
        }
        if (pcGpffff86ec != (code *)0x0) {
          (*pcGpffff86ec)(2,0,0,0,0,0,uGpffff86e8);
        }
        AllWindowClose__7BtlMenuFv(param_1);
        AllBCurDestruct__7BtlMenuFv();
        *(undefined2 *)(param_1 + 0x28) = 0x14;
        *(undefined2 *)(param_1 + 0x2a) = 0;
        PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,3,1,0);
      }
    }
  }
  else if (*(short *)(param_1 + 0x2a) == 0) {
    *(byte *)(param_1 + 0x25) = *(byte *)(param_1 + 0x25) & 0xf7;
    SetMainMenu__7BtlMenuFiiii
              (param_1,0,0xffffffffffffffff,0xffffffffffffffff,*(undefined2 *)(param_1 + 0xb58));
    sVar2 = *(short *)(param_1 + 0xb44);
    if (((((sVar2 == 0x1d) || (sVar2 == 0x1c)) || (sVar2 == 0x18)) ||
        (((sVar2 == 0x17 || (sVar2 == 0x16)) ||
         ((sVar2 == 0x15 || ((sVar2 == 0x14 || (sVar2 == 9)))))))) || (sVar2 == 1)) {
      SetTutorialMenu__7BtlMenuFii(param_1,5,*(undefined2 *)(param_1 + 0xb44));
      SetWindowClose__7BtlMenuFii(param_1,1,5);
      *(undefined4 *)(param_1 + 0xb48) = 0x3f800000;
    }
    else {
      SetWindowClose__7BtlMenuFii(param_1,1,6);
    }
    CreateCursole__7BtlMenuFv(param_1);
    Select__6CursorFP9MenuPlace(param_1 + 0xa34,*(int *)(param_1 + 0x130) + *(int *)(param_1 + 0x158) * 0x80);
    QuickMove__6CursorFv(param_1 + 0xa34);
    uVar9 = AllBCurDestruct__7BtlMenuFv();
    *(byte *)(param_1 + 0x24) = *(byte *)(param_1 + 0x24) & 0xfd;
    *(undefined2 *)(param_1 + 0x2a) = 1;
    if (*(short *)(param_1 + 0x32) == 1) {
      PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,0x2000000,1,0,uVar9);
    }
  }
  return 1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005a5590  DelaySelectFunc__7BtlMenuFiiiP12EFCTCOMParam
 * C++: BtlMenu::DelaySelectFunc(int, int, int, EFCTCOMParam *)
 * size: 0x344 bytes
 * --------------------------------------------------------------------------- */
void DelaySelectFunc__7BtlMenuFiiiP12EFCTCOMParam
               (undefined8 param_1,int param_2,int param_3,undefined8 param_4,int param_5)

{
  int iVar1;
  int aiStack_90 [15];
  int aiStack_54 [5];
  int iStack_40;
  int iStack_30;
  int iStack_10;
  
  iStack_40 = param_2;
  iStack_30 = param_3;
  iStack_10 = param_5;
  if (param_3 == 0) {
    AllBCurDestruct__7BtlMenuFv();
    MakeCursole__7BtlMenuFiUcUcUcUcUcP7FVectori(iStack_40,0,1,2,0,2,0,0xffffffffffffffff);
  }
  else {
    GetTargetList__7CBattleFiiiiiP8ECCParamPiPi
              (pCGpffff86b4,(int)pCGpffff86b4->cActor,param_2,
               (uint)(((ulong)*(ushort *)(param_5 + 4) << 0x37) >> 0x3e),
               (uint)(((ulong)*(byte *)(param_5 + 5) << 0x3c) >> 0x3d),
               (uint)(((ulong)*(byte *)(param_5 + 5) << 0x3a) >> 0x3e),(void *)(param_5 + 8),
               aiStack_54,aiStack_90);
    AllBCurDestruct__7BtlMenuFv();
    if (((ulong)*(byte *)(iStack_10 + 5) & 0xf) >> 1 == 5) {
      if (((ulong)*(byte *)(iStack_10 + 4) & 0x7f) >> 5 == 0) {
        for (iVar1 = 0; iVar1 < aiStack_54[0]; iVar1 = iVar1 + 1) {
          MakeCursole__7BtlMenuFiUcUcUcUcUcP7FVectori
                    (aiStack_90[iVar1],1,1,2,0,3,0,0xffffffffffffffff);
        }
      }
      else {
        for (iVar1 = 0; iVar1 < aiStack_54[0]; iVar1 = iVar1 + 1) {
          MakeCursole__7BtlMenuFiUcUcUcUcUcP7FVectori
                    (aiStack_90[iVar1],1,1,2,0,0,0,0xffffffffffffffff);
        }
      }
    }
    else if (((ulong)*(byte *)(iStack_10 + 4) & 0x7f) >> 5 == 0) {
      for (iVar1 = 0; iVar1 < aiStack_54[0]; iVar1 = iVar1 + 1) {
        if (iStack_40 == aiStack_90[iVar1]) {
          MakeCursole__7BtlMenuFiUcUcUcUcUcP7FVectori
                    (aiStack_90[iVar1],0,1,2,0,2,0,0xffffffffffffffff);
        }
        else {
          MakeCursole__7BtlMenuFiUcUcUcUcUcP7FVectori
                    (aiStack_90[iVar1],1,1,2,0,3,0,0xffffffffffffffff);
        }
      }
    }
    else {
      for (iVar1 = 0; iVar1 < aiStack_54[0]; iVar1 = iVar1 + 1) {
        if (iStack_40 == aiStack_90[iVar1]) {
          MakeCursole__7BtlMenuFiUcUcUcUcUcP7FVectori
                    (aiStack_90[iVar1],0,1,2,0,0,0,0xffffffffffffffff);
        }
        else {
          MakeCursole__7BtlMenuFiUcUcUcUcUcP7FVectori
                    (aiStack_90[iVar1],1,1,2,0,0,0,0xffffffffffffffff);
        }
      }
    }
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005a58e0  SelectFunc__7BtlMenuFiiiP12EFCTCOMParam
 * C++: BtlMenu::SelectFunc(int, int, int, EFCTCOMParam *)
 * size: 0xb6c bytes
 * --------------------------------------------------------------------------- */
/* WARNING: Removing unreachable block (ram,0x005a6334) */

void SelectFunc__7BtlMenuFiiiP12EFCTCOMParam
               (int param_1,int param_2,int param_3,int param_4,int param_5)

{
  undefined4 uVar1;
  long lVar2;
  ulong uVar3;
  int iVar4;
  int iVar5;
  int aiStack_c0 [14];
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
  undefined *puStack_60;
  undefined *puStack_5c;
  int iStack_58;
  int iStack_54;
  int iStack_50;
  int iStack_40;
  int iStack_30;
  int iStack_20;
  int iStack_10;
  
  iStack_50 = param_1;
  iStack_40 = param_2;
  iStack_30 = param_3;
  iStack_20 = param_4;
  iStack_10 = param_5;
  if (param_3 == 0) {
    if (pcGpffff86ec != (code *)0x0) {
      (*pcGpffff86ec)(0x12,param_2,2,0,0xffffffffffffffff,0,uGpffff86e8);
    }
    iStack_54 = 1;
    aiStack_c0[0] = iStack_40;
    if (*(int *)(iStack_50 + 0xb38) == 0) {
      iStack_70 = __nw__FUi(0xac);
      if (iStack_70 != 0) {
        iStack_70 = __ct__10TargetInfoFiiiss(iStack_70,0xffffffffffffffff,iStack_40,pCGpffff86b4->cActor,
                                    (short)iStack_30,(short)iStack_20);
      }
      *(int *)(iStack_50 + 0xb38) = iStack_70;
    }
    else {
      iStack_58 = (int)pCGpffff86b4->cActor;
      iVar4 = *(int *)(iStack_50 + 0xb38);
      *(int *)(iVar4 + 0x48) = iStack_40;
      *(int *)(iVar4 + 0x5c) = iStack_58;
      *(short *)(iVar4 + 0x60) = (short)iStack_30;
      *(short *)(iVar4 + 0x62) = (short)iStack_20;
      for (iVar5 = 0; iVar5 < 9; iVar5 = iVar5 + 1) {
        *(undefined4 *)(iVar4 + iVar5 * 4 + 0x88) = 0;
        *(undefined4 *)(iVar4 + iVar5 * 4 + 100) = 0;
      }
    }
    puStack_5c = pCGpffff86b4->pTurnOrderDisp;
    *(undefined4 *)(puStack_5c + 100) = 0;
    SetSelectChr__13TurnOrderDispFii(pCGpffff86b4->pTurnOrderDisp,iStack_40,2);
    if (pcGpffff86ec != (code *)0x0) {
      (*pcGpffff86ec)(0x13,iStack_40,2,0,0xffffffffffffffff,0,uGpffff86e8);
    }
  }
  else {
    if (pcGpffff86ec != (code *)0x0) {
      (*pcGpffff86ec)(0x12,param_2,((ulong)*(ushort *)(param_5 + 4) & 0x1ff) >> 7,
                      ((ulong)*(byte *)(param_5 + 5) & 0xf) >> 1,
                      ((ulong)*(byte *)(param_5 + 5) & 0x3f) >> 4,param_5 + 8,uGpffff86e8);
    }
    puStack_60 = pCGpffff86b4->pTurnOrderDisp;
    *(undefined4 *)(puStack_60 + 100) = 0;
    GetTargetList__7CBattleFiiiiiP8ECCParamPiPi
              (pCGpffff86b4,(int)pCGpffff86b4->cActor,iStack_40,
               (uint)(((ulong)*(ushort *)(iStack_10 + 4) << 0x37) >> 0x3e),
               (uint)(((ulong)*(byte *)(iStack_10 + 5) << 0x3c) >> 0x3d),
               (uint)(((ulong)*(byte *)(iStack_10 + 5) << 0x3a) >> 0x3e),(void *)(iStack_10 + 8),
               &iStack_54,aiStack_c0);
    if (((ulong)*(byte *)(iStack_10 + 5) & 0xf) >> 1 == 5) {
      if (((ulong)*(byte *)(iStack_10 + 4) & 0x7f) >> 5 == 0) {
        for (iVar4 = 0; iVar4 < iStack_54; iVar4 = iVar4 + 1) {
          SetSelectChr__13TurnOrderDispFii(pCGpffff86b4->pTurnOrderDisp,aiStack_c0[iVar4],2);
        }
      }
      else {
        for (iVar4 = 0; iVar4 < iStack_54; iVar4 = iVar4 + 1) {
          SetSelectChr__13TurnOrderDispFii(pCGpffff86b4->pTurnOrderDisp,aiStack_c0[iVar4],1);
        }
      }
    }
    else if (((ulong)*(byte *)(iStack_10 + 4) & 0x7f) >> 5 == 0) {
      SetSelectChr__13TurnOrderDispFii(pCGpffff86b4->pTurnOrderDisp,iStack_40,2);
    }
    else {
      SetSelectChr__13TurnOrderDispFii(pCGpffff86b4->pTurnOrderDisp,iStack_40,1);
    }
    if (-1 < iStack_40) {
      if (*(int *)(iStack_50 + 0xb38) == 0) {
        iStack_74 = __nw__FUi(0xac);
        if (iStack_74 != 0) {
          iStack_74 = __ct__10TargetInfoFiiiss(iStack_74,0xffffffffffffffff,iStack_40,pCGpffff86b4->cActor,
                                      (short)iStack_30,(short)iStack_20);
        }
        *(int *)(iStack_50 + 0xb38) = iStack_74;
      }
      else {
        iStack_64 = (int)pCGpffff86b4->cActor;
        iVar4 = *(int *)(iStack_50 + 0xb38);
        *(int *)(iVar4 + 0x48) = iStack_40;
        *(int *)(iVar4 + 0x5c) = iStack_64;
        *(short *)(iVar4 + 0x60) = (short)iStack_30;
        *(short *)(iVar4 + 0x62) = (short)iStack_20;
        for (iVar5 = 0; iVar5 < 9; iVar5 = iVar5 + 1) {
          *(undefined4 *)(iVar4 + iVar5 * 4 + 0x88) = 0;
          *(undefined4 *)(iVar4 + iVar5 * 4 + 100) = 0;
        }
      }
    }
    if (*(int *)(iStack_50 + 0xb3c) == 0) {
      uVar3 = ((ulong)*(byte *)(iStack_10 + 5) & 0xf) >> 1;
      if (uVar3 == 4) {
        uVar3 = ((ulong)*(byte *)(iStack_10 + 5) & 0x3f) >> 4;
        if (uVar3 == 2) {
          lVar2 = __nw__FUi(0x70);
          uVar1 = 0;
          if (lVar2 != 0) {
            uVar1 = __ct__18StraightCircleAreaFiiiff(0x40f00000,0x42200000,lVar2,0,pCGpffff86b4->cActor,iStack_40);
          }
          *(undefined4 *)(iStack_50 + 0xb3c) = uVar1;
        }
        else if (uVar3 == 1) {
          lVar2 = __nw__FUi(0x70);
          uVar1 = 0;
          if (lVar2 != 0) {
            uVar1 = __ct__18StraightCircleAreaFiiiff(0x40f00000,0x41f00000,lVar2,0,pCGpffff86b4->cActor,iStack_40);
          }
          *(undefined4 *)(iStack_50 + 0xb3c) = uVar1;
        }
        else if (uVar3 == 0) {
          lVar2 = __nw__FUi(0x70);
          uVar1 = 0;
          if (lVar2 != 0) {
            uVar1 = __ct__18StraightCircleAreaFiiiff(0x40f00000,0x41a00000,lVar2,0,pCGpffff86b4->cActor,iStack_40);
          }
          *(undefined4 *)(iStack_50 + 0xb3c) = uVar1;
        }
      }
      else if (uVar3 == 3) {
        uVar3 = ((ulong)*(byte *)(iStack_10 + 5) & 0x3f) >> 4;
        if (uVar3 == 2) {
          lVar2 = __nw__FUi(100);
          uVar1 = 0;
          if (lVar2 != 0) {
            uVar1 = __ct__12StraightAreaFiiif(0x418c0000,lVar2,0,pCGpffff86b4->cActor,iStack_40);
          }
          *(undefined4 *)(iStack_50 + 0xb3c) = uVar1;
        }
        else if (uVar3 == 1) {
          iStack_88 = __nw__FUi(100);
          if (iStack_88 != 0) {
            iStack_88 = __ct__12StraightAreaFiiif(0x41480000,iStack_88,0,pCGpffff86b4->cActor,iStack_40);
          }
          *(int *)(iStack_50 + 0xb3c) = iStack_88;
        }
        else if (uVar3 == 0) {
          iStack_84 = __nw__FUi(100);
          if (iStack_84 != 0) {
            iStack_84 = __ct__12StraightAreaFiiif(0x40f00000,iStack_84,0,pCGpffff86b4->cActor,iStack_40);
          }
          *(int *)(iStack_50 + 0xb3c) = iStack_84;
        }
      }
      else if (uVar3 == 1) {
        uVar3 = ((ulong)*(byte *)(iStack_10 + 5) & 0x3f) >> 4;
        if (uVar3 == 2) {
          iStack_80 = __nw__FUi(0x60);
          if (iStack_80 != 0) {
            iStack_80 = __ct__10CircleAreaFiif(0x42200000,iStack_80,0,iStack_40);
          }
          *(int *)(iStack_50 + 0xb3c) = iStack_80;
        }
        else if (uVar3 == 1) {
          iStack_7c = __nw__FUi(0x60);
          if (iStack_7c != 0) {
            iStack_7c = __ct__10CircleAreaFiif(0x41f00000,iStack_7c,0,iStack_40);
          }
          *(int *)(iStack_50 + 0xb3c) = iStack_7c;
        }
        else if (uVar3 == 0) {
          iStack_78 = __nw__FUi(0x60);
          if (iStack_78 != 0) {
            iStack_78 = __ct__10CircleAreaFiif(0x41a00000,iStack_78,0,iStack_40);
          }
          *(int *)(iStack_50 + 0xb3c) = iStack_78;
        }
      }
    }
    else {
      uVar3 = ((ulong)*(byte *)(iStack_10 + 5) & 0xf) >> 1;
      if (uVar3 == 4) {
        iStack_6c = *(int *)(iStack_50 + 0xb3c);
        *(int *)(iStack_6c + 0x5c) = iStack_40;
      }
      else if (uVar3 == 3) {
        iStack_68 = *(int *)(iStack_50 + 0xb3c);
        *(int *)(iStack_68 + 0x5c) = iStack_40;
      }
      else if (uVar3 == 1) {
        ChangeTarget__10CircleAreaFi(*(undefined4 *)(iStack_50 + 0xb3c),iStack_40);
      }
    }
    MakeTurnOrderTable__7CBattleFfiPiiiPUisibi
              (pCGpffff86b4,(float)*(ushort *)(iStack_10 + 0x1a) / 100.0,iStack_54,aiStack_c0,
               iStack_30,iStack_20,(uint *)(iStack_10 + 8),(short)pCGpffff86b4->cActor,-1,true,-2);
    if (pcGpffff86ec != (code *)0x0) {
      (*pcGpffff86ec)(0x13,iStack_40,((ulong)*(ushort *)(iStack_10 + 4) & 0x1ff) >> 7,
                      ((ulong)*(byte *)(iStack_10 + 5) & 0xf) >> 1,
                      ((ulong)*(byte *)(iStack_10 + 5) & 0x3f) >> 4,iStack_10 + 8,uGpffff86e8);
    }
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005a6450  AllWindowClose__7BtlMenuFv
 * C++: BtlMenu::AllWindowClose()
 * size: 0x27c bytes
 * --------------------------------------------------------------------------- */
void AllWindowClose__7BtlMenuFv(int param_1)

{
  int iVar1;
  
  for (iVar1 = 0; iVar1 < 6; iVar1 = iVar1 + 1) {
    if (((*(short *)(param_1 + iVar1 * 0x16c + 0x32) != 0) &&
        (*(short *)(param_1 + iVar1 * 0x16c + 0x32) != 0xc)) &&
       (*(short *)(param_1 + iVar1 * 0x16c + 0x32) != 0xd)) {
      *(undefined2 *)(param_1 + iVar1 * 0x16c + 0x32) = 0xc;
      *(undefined2 *)(param_1 + iVar1 * 0x16c + 0x34) = 0;
      *(undefined2 *)(param_1 + iVar1 * 0x16c + 0x36) = 0;
      *(undefined4 *)(param_1 + iVar1 * 0x16c + 0x38) = 0;
      Close__10MenuWindowFUci(param_1 + iVar1 * 0x16c + 0x7c,
                      *(uint *)(param_1 + iVar1 * 0x16c + 0x178) & 0xff,0x85);
      if (*(int *)(param_1 + iVar1 * 0x16c + 0x140) != 0) {
        SetMark__10ScrollMarkFUc(*(undefined4 *)(param_1 + iVar1 * 0x16c + 0x140),0);
      }
    }
  }
  if (((*(short *)(param_1 + 0x8b8) != 0) && (*(short *)(param_1 + 0x8b8) != 0xc)) &&
     (*(short *)(param_1 + 0x8b8) != 0xd)) {
    *(undefined2 *)(param_1 + 0x8b8) = 0xc;
    *(undefined2 *)(param_1 + 0x8ba) = 0;
    Close__10MenuWindowFUci(param_1 + 0x8fc,0,0x85);
  }
  if (*(short *)(param_1 + 0xa30) == 1) {
    *(undefined2 *)(param_1 + 0xa30) = 2;
  }
  if (*(short *)(param_1 + 0xa32) == 1) {
    *(undefined2 *)(param_1 + 0xa32) = 2;
  }
  if (*(int *)(param_1 + 0xb3c) != 0) {
    (**(code **)(*(int *)(*(int *)(param_1 + 0xb3c) + 0x14) + 0x30))();
  }
  *(undefined4 *)(param_1 + 0xb3c) = 0;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005a66d0  WinSequence__7BtlMenuFv
 * C++: BtlMenu::WinSequence()
 * size: 0x46fc bytes
 * --------------------------------------------------------------------------- */
void WinSequence__7BtlMenuFv(int param_1)

{
  short sVar1;
  ushort uVar2;
  undefined4 uVar3;
  int iVar4;
  undefined8 uVar5;
  long lVar6;
  int iVar7;
  int iVar8;
  ulong uVar9;
  int iVar10;
  float fVar11;
  uint uVar12;
  float fStack_44;
  float fStack_40;
  float fStack_3c;
  float fStack_38;
  float fStack_34;
  float fStack_30;
  
  uVar2 = *(ushort *)(*(int *)(*(int *)(g_86c0 + 4) * 4 + 0x40ac00) + 0x6c);
  for (iVar8 = 0; iVar8 < 6; iVar8 = iVar8 + 1) {
    switch(*(undefined2 *)(param_1 + iVar8 * 0x16c + 0x32)) {
    case 1:
      if (*(char *)(param_1 + iVar8 * 0x16c + 0x124) == '\x01') {
        *(undefined2 *)(param_1 + iVar8 * 0x16c + 0x32) = 2;
        *(undefined2 *)(param_1 + iVar8 * 0x16c + 0x34) = 0;
        if ((long)((ulong)*(byte *)(param_1 + iVar8 * 0x16c + 0x31) << 0x3b) < 0) {
          Start__11MenuMessageFv(*(undefined4 *)(param_1 + iVar8 * 0x16c + 0x134));
        }
      }
      break;
    case 2:
      if ((long)((ulong)*(byte *)(param_1 + iVar8 * 0x16c + 0x31) << 0x3b) < 0) {
        iVar10 = *(int *)(param_1 + iVar8 * 0x16c + 0x134);
        if (*(ushort *)(iVar10 + 0x80) < *(ushort *)(iVar10 + 0x76)) {
          if ((uVar2 & 0x2000) != 0) {
            Finish__11MenuMessageFv(*(undefined4 *)(param_1 + iVar8 * 0x16c + 0x134));
          }
        }
        else {
          if (*(int *)(param_1 + iVar8 * 0x16c + 0x14c) == 0) {
            uVar5 = __nwa__FUi(0xec);
            uVar3 = __construct_new_array(uVar5,0x2808a0,0x280920,0xdc,1);
            *(undefined4 *)(param_1 + iVar8 * 0x16c + 0x14c) = uVar3;
            Create__7KeyWaitFv(*(undefined4 *)(param_1 + iVar8 * 0x16c + 0x14c));
            iVar10 = *(int *)(param_1 + iVar8 * 0x16c + 0x14c);
            *(undefined2 *)(iVar10 + 0x1e) = 1;
            *(byte *)(iVar10 + 0x12) = *(byte *)(iVar10 + 0x12) & 0xfd;
            *(byte *)(iVar10 + 0x12) = *(byte *)(iVar10 + 0x12) & 0xfe;
            iVar10 = *(int *)(param_1 + iVar8 * 0x16c + 0x14c);
            *(int *)(param_1 + iVar8 * 0x16c + 0xc4) = iVar10;
            *(int *)(iVar10 + 0x18) = param_1 + iVar8 * 0x16c + 0x7c;
            SetPosition__7KeyWaitFi(*(undefined4 *)(param_1 + iVar8 * 0x16c + 0x14c),1);
            iVar10 = *(int *)(param_1 + iVar8 * 0x16c + 0x14c);
            *(byte *)(iVar10 + 0x22) = *(byte *)(iVar10 + 0x22) & 0xbf | 0x40;
            iVar10 = *(int *)(param_1 + iVar8 * 0x16c + 0x14c);
            *(undefined2 *)(iVar10 + 0x1e) = 10;
            uVar9 = (ulong)*(byte *)(iVar10 + 0x12) & 0xfffffffffffffffd | 2;
            *(char *)(iVar10 + 0x12) = (char)uVar9;
            *(byte *)(iVar10 + 0x12) =
                 *(byte *)(iVar10 + 0x12) & 0xfe | (byte)((uVar9 << 0x3e) >> 0x3f);
          }
          if (((long)((ulong)*(byte *)(*(int *)(param_1 + iVar8 * 0x16c + 0x14c) + 0x22) << 0x39) <
               0) && ((char)*(undefined2 *)(*(int *)(param_1 + iVar8 * 0x16c + 0x14c) + 0x1e) ==
                      '\r')) {
            *(undefined2 *)(param_1 + 0xb46) = 1;
          }
        }
      }
      break;
    case 3:
      iVar10 = param_1 + iVar8 * 0x16c;
      *(float *)(iVar10 + 0x38) = *(float *)(iVar10 + 0x38) + *(float *)(iGpffff86b4 + 0x38);
      fStack_40 = *(float *)(param_1 + iVar8 * 0x16c + 0x38) / 0.13333334;
      fStack_44 = pfRam0040ab1c[4];
      if ((long)((ulong)*(byte *)(param_1 + 0x25) << 0x3c) < 0) {
        fStack_44 = -pfRam0040ab1c[6];
      }
      if (fStack_40 < 1.0) {
        fStack_30 = *(float *)(param_1 + iVar8 * 0x16c + 0x184) +
                    fStack_40 * (fStack_44 - *(float *)(param_1 + iVar8 * 0x16c + 0x184));
        fStack_34 = *(float *)(param_1 + iVar8 * 0x16c + 0x188) +
                    fStack_40 * (pfRam0040ab1c[5] - *(float *)(param_1 + iVar8 * 0x16c + 0x188));
        fStack_38 = *(float *)(param_1 + iVar8 * 0x16c + 0x18c) +
                    fStack_40 * (pfRam0040ab1c[6] - *(float *)(param_1 + iVar8 * 0x16c + 0x18c));
        fStack_3c = *(float *)(param_1 + iVar8 * 0x16c + 400) +
                    fStack_40 * (pfRam0040ab1c[7] - *(float *)(param_1 + iVar8 * 0x16c + 400));
      }
      else {
        fStack_30 = fStack_44;
        fStack_34 = pfRam0040ab1c[5];
        fStack_38 = pfRam0040ab1c[6];
        fStack_3c = pfRam0040ab1c[7];
      }
      uVar5 = SetPosition__10MenuWindowFff(fStack_30,fStack_34,param_1 + iVar8 * 0x16c + 0x7c);
      SetSize__10MenuWindowFff(fStack_38,fStack_3c,param_1 + iVar8 * 0x16c + 0x7c,uVar5);
      iVar10 = GetPlace__10MenuWindowFss(param_1 + iVar8 * 0x16c + 0x7c,
                               (short)*(undefined4 *)(param_1 + iVar8 * 0x16c + 0x150),
                               (short)*(undefined4 *)(param_1 + iVar8 * 0x16c + 0x154));
      fVar11 = -*(float *)(iVar10 + 0x28) + 2.0;
      fStack_34 = fVar11;
      if (fStack_40 < 1.0) {
        fStack_34 = *(float *)(param_1 + iVar8 * 0x16c + 0x194) +
                    fStack_40 * (fVar11 - *(float *)(param_1 + iVar8 * 0x16c + 0x194));
      }
      *(undefined4 *)(*(int *)(param_1 + iVar8 * 0x16c + 0xbc) + 0x38) = 0;
      uVar5 = SetScroll__10MenuWindowFss(param_1 + iVar8 * 0x16c + 0x7c,0,0);
      SetOffset__10MenuWindowFff(0,fStack_34,param_1 + iVar8 * 0x16c + 0x7c,uVar5);
      *(float *)(param_1 + iVar8 * 0x16c + 0x198) = fStack_34;
      iVar4 = *(int *)(param_1 + iVar8 * 0x16c + 0xc0);
      *(byte *)(iVar4 + 0x12) = *(byte *)(iVar4 + 0x12) & 0xfe;
      if (1.0 <= fStack_40) {
        *(undefined2 *)(param_1 + iVar8 * 0x16c + 0x32) = 4;
        *(undefined2 *)(param_1 + iVar8 * 0x16c + 0x34) = 0;
        SetPosition__10MenuWindowFff(fStack_44,pfRam0040ab1c[5],param_1 + iVar8 * 0x16c + 0x7c);
        SetSize__10MenuWindowFff(pfRam0040ab1c[6],pfRam0040ab1c[7],param_1 + iVar8 * 0x16c + 0x7c);
        *(float *)(param_1 + iVar8 * 0x16c + 0x184) = fStack_44;
        *(float *)(param_1 + iVar8 * 0x16c + 0x188) = pfRam0040ab1c[5];
        *(float *)(param_1 + iVar8 * 0x16c + 0x18c) = pfRam0040ab1c[6];
        *(float *)(param_1 + iVar8 * 0x16c + 400) = pfRam0040ab1c[7];
        SetOffset__10MenuWindowFff(0,fVar11,param_1 + iVar8 * 0x16c + 0x7c);
        *(float *)(param_1 + iVar8 * 0x16c + 0x198) = fVar11;
      }
      if (((iVar8 == 0) && (-1 < *(short *)(iVar10 + 0x16))) && (*(short *)(iVar10 + 0x16) < 5)) {
        fVar11 = *(float *)(iVar10 + 0x28);
        iVar10 = GetPlace__10MenuWindowFss(param_1 + 0x7c,(short)*(undefined4 *)(param_1 + 0x150) + 1,
                                 (short)*(undefined4 *)(param_1 + 0x154));
        fStack_34 = fStack_40 * 6.0 + -6.0;
        if (fStack_34 <= -6.0) {
          fStack_34 = -6.0;
        }
        if (0.0 <= fStack_34) {
          fStack_34 = 0.0;
        }
        fStack_34 = fStack_34 + fVar11;
        if (*(short *)(param_1 + 0x32) == 4) {
          fStack_34 = fVar11;
        }
        (**(code **)(*(int *)(iVar10 + 8) + 0x24))(*(undefined4 *)(iVar10 + 0x24),fStack_34);
      }
      if (*(int *)(param_1 + iVar8 * 0x16c + 0x13c) != 0) {
        iVar4 = GetPlace__10MenuWindowFss(param_1 + iVar8 * 0x16c + 0x7c,
                                (short)*(undefined4 *)(param_1 + iVar8 * 0x16c + 0x150),
                                (short)*(undefined4 *)(param_1 + iVar8 * 0x16c + 0x154));
        iVar10 = *(int *)(param_1 + iVar8 * 0x16c + 0x13c);
        (**(code **)(*(int *)(iVar10 + 0x188) + 0x24))(0,*(float *)(iVar4 + 0x28) - 2.0);
        SetUV__10MenuSpriteFUsUsUsUs(iVar10 + 0x180,0,0,0xf8,0x1b);
        (**(code **)(*(int *)(iVar10 + 0x188) + 0x28))(0x43780000,0x41d80000);
        fStack_40 = fStack_40 * 128.0;
        if (fStack_40 < 0.0) {
          fStack_40 = 0.0;
        }
        if (128.0 < fStack_40) {
          fStack_40 = 128.0;
        }
        if (fStack_40 < 2.1474836e+09) {
          uVar12 = (uint)fStack_40;
        }
        else {
          uVar12 = (int)(fStack_40 - 2.1474836e+09) | 0x80000000;
        }
        (**(code **)(*(int *)(iVar10 + 0x188) + 0x2c))(iVar10 + 0x180,uVar12);
        for (iVar4 = 0; iVar4 < 4; iVar4 = iVar4 + 1) {
          fVar11 = 128.0 - fStack_40;
          if (fVar11 < 2.1474836e+09) {
            uVar12 = (uint)fVar11;
          }
          else {
            uVar12 = (int)(fVar11 - 2.1474836e+09) | 0x80000000;
          }
          iVar7 = iVar10 + iVar4 * 0x60;
          (**(code **)(*(int *)(iVar7 + 8) + 0x2c))(iVar7,uVar12);
        }
        for (iVar4 = 5; iVar4 < 0x16; iVar4 = iVar4 + 1) {
          fVar11 = 128.0 - fStack_40;
          if (fVar11 < 2.1474836e+09) {
            uVar12 = (uint)fVar11;
          }
          else {
            uVar12 = (int)(fVar11 - 2.1474836e+09) | 0x80000000;
          }
          iVar7 = iVar10 + iVar4 * 0x60;
          (**(code **)(*(int *)(iVar7 + 8) + 0x2c))(iVar7,uVar12);
        }
      }
      break;
    case 5:
      iVar10 = param_1 + iVar8 * 0x16c;
      *(float *)(iVar10 + 0x38) = *(float *)(iVar10 + 0x38) + *(float *)(iGpffff86b4 + 0x38);
      fStack_40 = *(float *)(param_1 + iVar8 * 0x16c + 0x38) / 0.13333334;
      if (fStack_40 < 1.0) {
        fStack_30 = *(float *)(param_1 + iVar8 * 0x16c + 0x184) +
                    fStack_40 * (*pfRam0040ab1c - *(float *)(param_1 + iVar8 * 0x16c + 0x184));
        fStack_34 = *(float *)(param_1 + iVar8 * 0x16c + 0x188) +
                    fStack_40 *
                    (*(float *)(param_1 + iVar8 * 0x16c + 0x17c) -
                    *(float *)(param_1 + iVar8 * 0x16c + 0x188));
        fStack_38 = *(float *)(param_1 + iVar8 * 0x16c + 0x18c) +
                    fStack_40 * (pfRam0040ab1c[2] - *(float *)(param_1 + iVar8 * 0x16c + 0x18c));
        fStack_3c = *(float *)(param_1 + iVar8 * 0x16c + 400) +
                    fStack_40 *
                    (*(float *)(param_1 + iVar8 * 0x16c + 0x180) -
                    *(float *)(param_1 + iVar8 * 0x16c + 400));
      }
      else {
        fStack_30 = *pfRam0040ab1c;
        fStack_34 = *(float *)(param_1 + iVar8 * 0x16c + 0x17c);
        fStack_38 = pfRam0040ab1c[2];
        fStack_3c = *(float *)(param_1 + iVar8 * 0x16c + 0x180);
      }
      SetPosition__10MenuWindowFff(fStack_30,fStack_34,param_1 + iVar8 * 0x16c + 0x7c);
      SetSize__10MenuWindowFff(fStack_38,fStack_3c,param_1 + iVar8 * 0x16c + 0x7c);
      iVar10 = GetPlace__10MenuWindowFss(param_1 + iVar8 * 0x16c + 0x7c,
                               (short)*(undefined4 *)(param_1 + iVar8 * 0x16c + 0x150),
                               (short)*(undefined4 *)(param_1 + iVar8 * 0x16c + 0x154));
      fStack_34 = *(float *)(param_1 + iVar8 * 0x16c + 0x194);
      if (fStack_40 < 1.0) {
        fStack_34 = fStack_34 +
                    fStack_40 * (*(float *)(param_1 + iVar8 * 0x16c + 0x160) - fStack_34);
      }
      else {
        fStack_34 = *(float *)(param_1 + iVar8 * 0x16c + 0x160);
      }
      *(undefined4 *)(*(int *)(param_1 + iVar8 * 0x16c + 0xbc) + 0x38) = 0;
      uVar5 = SetScroll__10MenuWindowFss(param_1 + iVar8 * 0x16c + 0x7c,0,0);
      SetOffset__10MenuWindowFff(0,fStack_34,param_1 + iVar8 * 0x16c + 0x7c,param_1,uVar5);
      *(float *)(param_1 + iVar8 * 0x16c + 0x198) = fStack_34;
      iVar4 = *(int *)(param_1 + iVar8 * 0x16c + 0xc0);
      if (fStack_40 < 1.0) {
        *(byte *)(iVar4 + 0x12) = *(byte *)(iVar4 + 0x12) & 0xfe;
      }
      else {
        *(undefined2 *)(param_1 + iVar8 * 0x16c + 0x32) = 2;
        *(undefined2 *)(param_1 + iVar8 * 0x16c + 0x34) = 0;
        SetPosition__10MenuWindowFff(*pfRam0040ab1c,*(undefined4 *)(param_1 + iVar8 * 0x16c + 0x17c),
                        param_1 + iVar8 * 0x16c + 0x7c);
        SetSize__10MenuWindowFff(pfRam0040ab1c[2],*(undefined4 *)(param_1 + iVar8 * 0x16c + 0x180),
                        param_1 + iVar8 * 0x16c + 0x7c);
        *(float *)(param_1 + iVar8 * 0x16c + 0x184) = *pfRam0040ab1c;
        *(undefined4 *)(param_1 + iVar8 * 0x16c + 0x188) =
             *(undefined4 *)(param_1 + iVar8 * 0x16c + 0x17c);
        *(float *)(param_1 + iVar8 * 0x16c + 0x18c) = pfRam0040ab1c[2];
        *(undefined4 *)(param_1 + iVar8 * 0x16c + 400) =
             *(undefined4 *)(param_1 + iVar8 * 0x16c + 0x180);
        SetOffset__10MenuWindowFff(0,*(undefined4 *)(param_1 + iVar8 * 0x16c + 0x160),
                        param_1 + iVar8 * 0x16c + 0x7c);
        *(byte *)(iVar4 + 0x12) = *(byte *)(iVar4 + 0x12) & 0xfe | 1;
        *(undefined4 *)(param_1 + iVar8 * 0x16c + 0x198) =
             *(undefined4 *)(param_1 + iVar8 * 0x16c + 0x160);
      }
      if (((iVar8 == 0) && (-1 < *(short *)(iVar10 + 0x16))) && (*(short *)(iVar10 + 0x16) < 5)) {
        fVar11 = *(float *)(iVar10 + 0x28);
        iVar10 = GetPlace__10MenuWindowFss(param_1 + 0x7c,(short)*(undefined4 *)(param_1 + 0x150) + 1,
                                 (short)*(undefined4 *)(param_1 + 0x154));
        fStack_34 = fStack_40 * -6.0;
        if (fStack_34 <= -6.0) {
          fStack_34 = -6.0;
        }
        if (0.0 <= fStack_34) {
          fStack_34 = 0.0;
        }
        fStack_34 = fStack_34 + fVar11;
        if (*(short *)(param_1 + 0x32) == 2) {
          fStack_34 = fVar11 - 6.0;
        }
        (**(code **)(*(int *)(iVar10 + 8) + 0x24))(*(undefined4 *)(iVar10 + 0x24),fStack_34);
      }
      if (*(int *)(param_1 + iVar8 * 0x16c + 0x13c) != 0) {
        iVar4 = GetPlace__10MenuWindowFss(param_1 + iVar8 * 0x16c + 0x7c,
                                (short)*(undefined4 *)(param_1 + iVar8 * 0x16c + 0x150),
                                (short)*(undefined4 *)(param_1 + iVar8 * 0x16c + 0x154));
        iVar10 = *(int *)(param_1 + iVar8 * 0x16c + 0x13c);
        (**(code **)(*(int *)(iVar10 + 0x188) + 0x24))(0,*(float *)(iVar4 + 0x28) - 2.0);
        SetUV__10MenuSpriteFUsUsUsUs(iVar10 + 0x180,0,0,0xf8,0x1b);
        (**(code **)(*(int *)(iVar10 + 0x188) + 0x28))(0x43780000,0x41d80000);
        fStack_40 = fStack_40 * 128.0;
        if (fStack_40 < 0.0) {
          fStack_40 = 0.0;
        }
        if (128.0 < fStack_40) {
          fStack_40 = 128.0;
        }
        fVar11 = 128.0 - fStack_40;
        if (fVar11 < 2.1474836e+09) {
          uVar12 = (uint)fVar11;
        }
        else {
          uVar12 = (int)(fVar11 - 2.1474836e+09) | 0x80000000;
        }
        (**(code **)(*(int *)(iVar10 + 0x188) + 0x2c))(iVar10 + 0x180,uVar12);
        for (iVar4 = 0; iVar4 < 4; iVar4 = iVar4 + 1) {
          if (fStack_40 < 2.1474836e+09) {
            uVar12 = (uint)fStack_40;
          }
          else {
            uVar12 = (int)(fStack_40 - 2.1474836e+09) | 0x80000000;
          }
          iVar7 = iVar10 + iVar4 * 0x60;
          (**(code **)(*(int *)(iVar7 + 8) + 0x2c))(iVar7,uVar12);
        }
        for (iVar4 = 5; iVar4 < 0x16; iVar4 = iVar4 + 1) {
          if (fStack_40 < 2.1474836e+09) {
            uVar12 = (uint)fStack_40;
          }
          else {
            uVar12 = (int)(fStack_40 - 2.1474836e+09) | 0x80000000;
          }
          iVar7 = iVar10 + iVar4 * 0x60;
          (**(code **)(*(int *)(iVar7 + 8) + 0x2c))(iVar7,uVar12);
        }
      }
      break;
    case 6:
      iVar10 = param_1 + iVar8 * 0x16c;
      *(float *)(iVar10 + 0x38) = *(float *)(iVar10 + 0x38) + *(float *)(iGpffff86b4 + 0x38);
      fStack_40 = *(float *)(param_1 + iVar8 * 0x16c + 0x38) / 0.13333334;
      fStack_44 = pfRam0040ab1c[8];
      if ((long)((ulong)*(byte *)(param_1 + 0x25) << 0x3c) < 0) {
        fStack_44 = -pfRam0040ab1c[10];
      }
      if (fStack_40 < 1.0) {
        fStack_30 = *(float *)(param_1 + iVar8 * 0x16c + 0x184) +
                    fStack_40 * (fStack_44 - *(float *)(param_1 + iVar8 * 0x16c + 0x184));
        fStack_34 = *(float *)(param_1 + iVar8 * 0x16c + 0x188) +
                    fStack_40 * (pfRam0040ab1c[9] - *(float *)(param_1 + iVar8 * 0x16c + 0x188));
        fStack_38 = *(float *)(param_1 + iVar8 * 0x16c + 0x18c) +
                    fStack_40 * (pfRam0040ab1c[10] - *(float *)(param_1 + iVar8 * 0x16c + 0x18c));
        fStack_3c = *(float *)(param_1 + iVar8 * 0x16c + 400) +
                    fStack_40 * (pfRam0040ab1c[0xb] - *(float *)(param_1 + iVar8 * 0x16c + 400));
      }
      else {
        fStack_30 = fStack_44;
        fStack_34 = pfRam0040ab1c[9];
        fStack_38 = pfRam0040ab1c[10];
        fStack_3c = pfRam0040ab1c[0xb];
      }
      SetPosition__10MenuWindowFff(fStack_30,fStack_34,param_1 + iVar8 * 0x16c + 0x7c);
      SetSize__10MenuWindowFff(fStack_38,fStack_3c,param_1 + iVar8 * 0x16c + 0x7c);
      iVar10 = *(int *)(param_1 + iVar8 * 0x16c + 0xc0);
      *(byte *)(iVar10 + 0x12) = *(byte *)(iVar10 + 0x12) & 0xfe;
      iVar10 = GetPlace__10MenuWindowFss(param_1 + iVar8 * 0x16c + 0x7c,
                               (short)*(undefined4 *)(param_1 + iVar8 * 0x16c + 0x150),
                               (short)*(undefined4 *)(param_1 + iVar8 * 0x16c + 0x154));
      fVar11 = -*(float *)(iVar10 + 0x28) + 2.0;
      *(undefined4 *)(*(int *)(param_1 + iVar8 * 0x16c + 0xbc) + 0x38) = 0;
      SetScroll__10MenuWindowFss(param_1 + iVar8 * 0x16c + 0x7c,0,0);
      SetOffset__10MenuWindowFff(0,fVar11,param_1 + iVar8 * 0x16c + 0x7c);
      *(float *)(param_1 + iVar8 * 0x16c + 0x198) = fVar11;
      if (1.0 <= fStack_40) {
        *(undefined2 *)(param_1 + iVar8 * 0x16c + 0x32) = 7;
        *(undefined2 *)(param_1 + iVar8 * 0x16c + 0x34) = 0;
        SetPosition__10MenuWindowFff(fStack_44,pfRam0040ab1c[9],param_1 + iVar8 * 0x16c + 0x7c);
        SetSize__10MenuWindowFff(pfRam0040ab1c[10],pfRam0040ab1c[0xb],param_1 + iVar8 * 0x16c + 0x7c);
        *(float *)(param_1 + iVar8 * 0x16c + 0x184) = fStack_44;
        *(float *)(param_1 + iVar8 * 0x16c + 0x188) = pfRam0040ab1c[9];
        *(float *)(param_1 + iVar8 * 0x16c + 0x18c) = pfRam0040ab1c[10];
        *(float *)(param_1 + iVar8 * 0x16c + 400) = pfRam0040ab1c[0xb];
      }
      if (*(int *)(param_1 + iVar8 * 0x16c + 0x13c) != 0) {
        iVar4 = GetPlace__10MenuWindowFss(param_1 + iVar8 * 0x16c + 0x7c,
                                (short)*(undefined4 *)(param_1 + iVar8 * 0x16c + 0x150),
                                (short)*(undefined4 *)(param_1 + iVar8 * 0x16c + 0x154));
        iVar10 = *(int *)(param_1 + iVar8 * 0x16c + 0x13c);
        (**(code **)(*(int *)(iVar10 + 0x188) + 0x24))(0,*(float *)(iVar4 + 0x28) - 2.0);
        SetUV__10MenuSpriteFUsUsUsUs(iVar10 + 0x180,0,0,0xf8,0x1b);
        (**(code **)(*(int *)(iVar10 + 0x188) + 0x28))(0x43780000,0x41d80000);
        fStack_40 = fStack_40 * 32.0;
        if (fStack_40 < 0.0) {
          fStack_40 = 0.0;
        }
        if (32.0 <= fStack_40) {
          fStack_40 = 32.0;
        }
        fVar11 = 128.0 - fStack_40;
        if (fVar11 < 2.1474836e+09) {
          uVar12 = (uint)fVar11;
        }
        else {
          uVar12 = (int)(fVar11 - 2.1474836e+09) | 0x80000000;
        }
        (**(code **)(*(int *)(iVar10 + 0x188) + 0x2c))(iVar10 + 0x180,uVar12);
        lVar6 = GetPlace__10MenuWindowFss(param_1 + iVar8 * 0x16c + 0x7c,
                                (short)*(undefined4 *)(param_1 + iVar8 * 0x16c + 0x150),
                                (short)*(undefined4 *)(param_1 + iVar8 * 0x16c + 0x154));
        if (lVar6 != 0) {
          fVar11 = 128.0 - fStack_40;
          if (fVar11 < 2.1474836e+09) {
            uVar12 = (uint)fVar11;
          }
          else {
            uVar12 = (int)(fVar11 - 2.1474836e+09) | 0x80000000;
          }
          (**(code **)(*(int *)((int)lVar6 + 8) + 0x2c))(lVar6,uVar12);
        }
        lVar6 = GetPlace__10MenuWindowFss(param_1 + iVar8 * 0x16c + 0x7c,
                                (short)*(undefined4 *)(param_1 + iVar8 * 0x16c + 0x150) + 1,
                                (short)*(undefined4 *)(param_1 + iVar8 * 0x16c + 0x154));
        if (lVar6 != 0) {
          fStack_40 = 128.0 - fStack_40;
          if (fStack_40 < 2.1474836e+09) {
            uVar12 = (uint)fStack_40;
          }
          else {
            uVar12 = (int)(fStack_40 - 2.1474836e+09) | 0x80000000;
          }
          (**(code **)(*(int *)((int)lVar6 + 8) + 0x2c))(lVar6,uVar12);
        }
        for (iVar4 = 0; iVar4 < 4; iVar4 = iVar4 + 1) {
          iVar7 = iVar10 + iVar4 * 0x60;
          (**(code **)(*(int *)(iVar7 + 8) + 0x2c))(iVar7,0);
        }
        for (iVar4 = 5; iVar4 < 0x16; iVar4 = iVar4 + 1) {
          iVar7 = iVar10 + iVar4 * 0x60;
          (**(code **)(*(int *)(iVar7 + 8) + 0x2c))(iVar7,0);
        }
      }
      break;
    case 8:
      iVar10 = param_1 + iVar8 * 0x16c;
      *(float *)(iVar10 + 0x38) = *(float *)(iVar10 + 0x38) + *(float *)(iGpffff86b4 + 0x38);
      fStack_40 = *(float *)(param_1 + iVar8 * 0x16c + 0x38) / 0.13333334;
      fStack_44 = pfRam0040ab1c[4];
      if ((long)((ulong)*(byte *)(param_1 + 0x25) << 0x3c) < 0) {
        fStack_44 = -pfRam0040ab1c[6];
      }
      if (fStack_40 < 1.0) {
        fStack_30 = *(float *)(param_1 + iVar8 * 0x16c + 0x184) +
                    fStack_40 * (fStack_44 - *(float *)(param_1 + iVar8 * 0x16c + 0x184));
        fStack_34 = *(float *)(param_1 + iVar8 * 0x16c + 0x188) +
                    fStack_40 * (pfRam0040ab1c[5] - *(float *)(param_1 + iVar8 * 0x16c + 0x188));
        fStack_38 = *(float *)(param_1 + iVar8 * 0x16c + 0x18c) +
                    fStack_40 * (pfRam0040ab1c[6] - *(float *)(param_1 + iVar8 * 0x16c + 0x18c));
        fStack_3c = *(float *)(param_1 + iVar8 * 0x16c + 400) +
                    fStack_40 * (pfRam0040ab1c[7] - *(float *)(param_1 + iVar8 * 0x16c + 400));
      }
      else {
        fStack_30 = fStack_44;
        fStack_34 = pfRam0040ab1c[5];
        fStack_38 = pfRam0040ab1c[6];
        fStack_3c = pfRam0040ab1c[7];
      }
      SetPosition__10MenuWindowFff(fStack_30,fStack_34,param_1 + iVar8 * 0x16c + 0x7c);
      SetSize__10MenuWindowFff(fStack_38,fStack_3c,param_1 + iVar8 * 0x16c + 0x7c);
      iVar10 = *(int *)(param_1 + iVar8 * 0x16c + 0xc0);
      *(byte *)(iVar10 + 0x12) = *(byte *)(iVar10 + 0x12) & 0xfe;
      iVar10 = GetPlace__10MenuWindowFss(param_1 + iVar8 * 0x16c + 0x7c,
                               (short)*(undefined4 *)(param_1 + iVar8 * 0x16c + 0x150),
                               (short)*(undefined4 *)(param_1 + iVar8 * 0x16c + 0x154));
      fVar11 = -*(float *)(iVar10 + 0x28) + 2.0;
      *(undefined4 *)(*(int *)(param_1 + iVar8 * 0x16c + 0xbc) + 0x38) = 0;
      SetScroll__10MenuWindowFss(param_1 + iVar8 * 0x16c + 0x7c,0,0);
      SetOffset__10MenuWindowFff(0,fVar11,param_1 + iVar8 * 0x16c + 0x7c);
      *(float *)(param_1 + iVar8 * 0x16c + 0x198) = fVar11;
      if (1.0 <= fStack_40) {
        *(undefined2 *)(param_1 + iVar8 * 0x16c + 0x32) = 4;
        *(undefined2 *)(param_1 + iVar8 * 0x16c + 0x34) = 0;
        SetPosition__10MenuWindowFff(fStack_44,pfRam0040ab1c[5],param_1 + iVar8 * 0x16c + 0x7c);
        SetSize__10MenuWindowFff(pfRam0040ab1c[6],pfRam0040ab1c[7],param_1 + iVar8 * 0x16c + 0x7c);
        *(float *)(param_1 + iVar8 * 0x16c + 0x184) = fStack_44;
        *(float *)(param_1 + iVar8 * 0x16c + 0x188) = pfRam0040ab1c[5];
        *(float *)(param_1 + iVar8 * 0x16c + 0x18c) = pfRam0040ab1c[6];
        *(float *)(param_1 + iVar8 * 0x16c + 400) = pfRam0040ab1c[7];
      }
      if (*(int *)(param_1 + iVar8 * 0x16c + 0x13c) != 0) {
        iVar4 = GetPlace__10MenuWindowFss(param_1 + iVar8 * 0x16c + 0x7c,
                                (short)*(undefined4 *)(param_1 + iVar8 * 0x16c + 0x150),
                                (short)*(undefined4 *)(param_1 + iVar8 * 0x16c + 0x154));
        iVar10 = *(int *)(param_1 + iVar8 * 0x16c + 0x13c);
        (**(code **)(*(int *)(iVar10 + 0x188) + 0x24))(0,*(float *)(iVar4 + 0x28) - 2.0);
        SetUV__10MenuSpriteFUsUsUsUs(iVar10 + 0x180,0,0,0xf8,0x1b);
        (**(code **)(*(int *)(iVar10 + 0x188) + 0x28))(0x43780000,0x41d80000);
        fStack_40 = fStack_40 * 32.0;
        if (fStack_40 < 0.0) {
          fStack_40 = 0.0;
        }
        if (32.0 <= fStack_40) {
          fStack_40 = 32.0;
        }
        fVar11 = fStack_40 + 96.0;
        if (fVar11 < 2.1474836e+09) {
          uVar12 = (uint)fVar11;
        }
        else {
          uVar12 = (int)(fVar11 - 2.1474836e+09) | 0x80000000;
        }
        (**(code **)(*(int *)(iVar10 + 0x188) + 0x2c))(iVar10 + 0x180,uVar12);
        lVar6 = GetPlace__10MenuWindowFss(param_1 + iVar8 * 0x16c + 0x7c,
                                (short)*(undefined4 *)(param_1 + iVar8 * 0x16c + 0x150),
                                (short)*(undefined4 *)(param_1 + iVar8 * 0x16c + 0x154));
        if (lVar6 != 0) {
          fVar11 = fStack_40 + 96.0;
          if (fVar11 < 2.1474836e+09) {
            uVar12 = (uint)fVar11;
          }
          else {
            uVar12 = (int)(fVar11 - 2.1474836e+09) | 0x80000000;
          }
          (**(code **)(*(int *)((int)lVar6 + 8) + 0x2c))(lVar6,uVar12);
        }
        lVar6 = GetPlace__10MenuWindowFss(param_1 + iVar8 * 0x16c + 0x7c,
                                (short)*(undefined4 *)(param_1 + iVar8 * 0x16c + 0x150) + 1,
                                (short)*(undefined4 *)(param_1 + iVar8 * 0x16c + 0x154));
        if (lVar6 != 0) {
          fStack_40 = fStack_40 + 96.0;
          if (fStack_40 < 2.1474836e+09) {
            uVar12 = (uint)fStack_40;
          }
          else {
            uVar12 = (int)(fStack_40 - 2.1474836e+09) | 0x80000000;
          }
          (**(code **)(*(int *)((int)lVar6 + 8) + 0x2c))(lVar6,uVar12);
        }
        for (iVar4 = 0; iVar4 < 4; iVar4 = iVar4 + 1) {
          iVar7 = iVar10 + iVar4 * 0x60;
          (**(code **)(*(int *)(iVar7 + 8) + 0x2c))(iVar7,0);
        }
        for (iVar4 = 5; iVar4 < 0x16; iVar4 = iVar4 + 1) {
          iVar7 = iVar10 + iVar4 * 0x60;
          (**(code **)(*(int *)(iVar7 + 8) + 0x2c))(iVar7,0);
        }
      }
      break;
    case 9:
      iVar10 = param_1 + iVar8 * 0x16c;
      *(float *)(iVar10 + 0x38) = *(float *)(iVar10 + 0x38) + *(float *)(iGpffff86b4 + 0x38);
      fStack_40 = *(float *)(param_1 + iVar8 * 0x16c + 0x38) / 0.13333334;
      fStack_44 = pfRam0040ab1c[0xc];
      if ((long)((ulong)*(byte *)(param_1 + 0x25) << 0x3c) < 0) {
        fStack_44 = -pfRam0040ab1c[0xe];
      }
      if (fStack_40 < 1.0) {
        fStack_30 = *(float *)(param_1 + iVar8 * 0x16c + 0x184) +
                    fStack_40 * (fStack_44 - *(float *)(param_1 + iVar8 * 0x16c + 0x184));
        fStack_34 = *(float *)(param_1 + iVar8 * 0x16c + 0x188) +
                    fStack_40 * (pfRam0040ab1c[0xd] - *(float *)(param_1 + iVar8 * 0x16c + 0x188));
        fStack_38 = *(float *)(param_1 + iVar8 * 0x16c + 0x18c) +
                    fStack_40 * (pfRam0040ab1c[0xe] - *(float *)(param_1 + iVar8 * 0x16c + 0x18c));
        fStack_3c = *(float *)(param_1 + iVar8 * 0x16c + 400) +
                    fStack_40 * (pfRam0040ab1c[0xf] - *(float *)(param_1 + iVar8 * 0x16c + 400));
      }
      else {
        fStack_30 = fStack_44;
        fStack_34 = pfRam0040ab1c[0xd];
        fStack_38 = pfRam0040ab1c[0xe];
        fStack_3c = pfRam0040ab1c[0xf];
      }
      SetPosition__10MenuWindowFff(fStack_30,fStack_34,param_1 + iVar8 * 0x16c + 0x7c);
      SetSize__10MenuWindowFff(fStack_38,fStack_3c,param_1 + iVar8 * 0x16c + 0x7c);
      iVar10 = *(int *)(param_1 + iVar8 * 0x16c + 0xc0);
      *(byte *)(iVar10 + 0x12) = *(byte *)(iVar10 + 0x12) & 0xfe;
      iVar10 = GetPlace__10MenuWindowFss(param_1 + iVar8 * 0x16c + 0x7c,
                               (short)*(undefined4 *)(param_1 + iVar8 * 0x16c + 0x150),
                               (short)*(undefined4 *)(param_1 + iVar8 * 0x16c + 0x154));
      fVar11 = -*(float *)(iVar10 + 0x28) + 2.0;
      *(undefined4 *)(*(int *)(param_1 + iVar8 * 0x16c + 0xbc) + 0x38) = 0;
      SetScroll__10MenuWindowFss(param_1 + iVar8 * 0x16c + 0x7c,0,0);
      SetOffset__10MenuWindowFff(0,fVar11,param_1 + iVar8 * 0x16c + 0x7c);
      *(float *)(param_1 + iVar8 * 0x16c + 0x198) = fVar11;
      if (1.0 <= fStack_40) {
        *(undefined2 *)(param_1 + iVar8 * 0x16c + 0x32) = 10;
        *(undefined2 *)(param_1 + iVar8 * 0x16c + 0x34) = 0;
        SetPosition__10MenuWindowFff(fStack_44,pfRam0040ab1c[0xd],param_1 + iVar8 * 0x16c + 0x7c);
        SetSize__10MenuWindowFff(pfRam0040ab1c[0xe],pfRam0040ab1c[0xf],param_1 + iVar8 * 0x16c + 0x7c);
        *(float *)(param_1 + iVar8 * 0x16c + 0x184) = fStack_44;
        *(float *)(param_1 + iVar8 * 0x16c + 0x188) = pfRam0040ab1c[0xd];
        *(float *)(param_1 + iVar8 * 0x16c + 0x18c) = pfRam0040ab1c[0xe];
        *(float *)(param_1 + iVar8 * 0x16c + 400) = pfRam0040ab1c[0xf];
      }
      if (*(int *)(param_1 + iVar8 * 0x16c + 0x13c) != 0) {
        iVar4 = GetPlace__10MenuWindowFss(param_1 + iVar8 * 0x16c + 0x7c,
                                (short)*(undefined4 *)(param_1 + iVar8 * 0x16c + 0x150),
                                (short)*(undefined4 *)(param_1 + iVar8 * 0x16c + 0x154));
        iVar10 = *(int *)(param_1 + iVar8 * 0x16c + 0x13c);
        (**(code **)(*(int *)(iVar10 + 0x188) + 0x24))(0,*(float *)(iVar4 + 0x28) - 2.0);
        SetUV__10MenuSpriteFUsUsUsUs(iVar10 + 0x180,0,0,0xf8,0x1b);
        (**(code **)(*(int *)(iVar10 + 0x188) + 0x28))(0x43780000,0x41d80000);
        fStack_40 = fStack_40 * 32.0;
        if (fStack_40 < 0.0) {
          fStack_40 = 0.0;
        }
        if (32.0 <= fStack_40) {
          fStack_40 = 32.0;
        }
        fVar11 = 96.0 - fStack_40;
        if (fVar11 < 2.1474836e+09) {
          uVar12 = (uint)fVar11;
        }
        else {
          uVar12 = (int)(fVar11 - 2.1474836e+09) | 0x80000000;
        }
        (**(code **)(*(int *)(iVar10 + 0x188) + 0x2c))(iVar10 + 0x180,uVar12);
        lVar6 = GetPlace__10MenuWindowFss(param_1 + iVar8 * 0x16c + 0x7c,
                                (short)*(undefined4 *)(param_1 + iVar8 * 0x16c + 0x150),
                                (short)*(undefined4 *)(param_1 + iVar8 * 0x16c + 0x154));
        if (lVar6 != 0) {
          fVar11 = 96.0 - fStack_40;
          if (fVar11 < 2.1474836e+09) {
            uVar12 = (uint)fVar11;
          }
          else {
            uVar12 = (int)(fVar11 - 2.1474836e+09) | 0x80000000;
          }
          (**(code **)(*(int *)((int)lVar6 + 8) + 0x2c))(lVar6,uVar12);
        }
        lVar6 = GetPlace__10MenuWindowFss(param_1 + iVar8 * 0x16c + 0x7c,
                                (short)*(undefined4 *)(param_1 + iVar8 * 0x16c + 0x150) + 1,
                                (short)*(undefined4 *)(param_1 + iVar8 * 0x16c + 0x154));
        if (lVar6 != 0) {
          fStack_40 = 96.0 - fStack_40;
          if (fStack_40 < 2.1474836e+09) {
            uVar12 = (uint)fStack_40;
          }
          else {
            uVar12 = (int)(fStack_40 - 2.1474836e+09) | 0x80000000;
          }
          (**(code **)(*(int *)((int)lVar6 + 8) + 0x2c))(lVar6,uVar12);
        }
        for (iVar4 = 0; iVar4 < 4; iVar4 = iVar4 + 1) {
          iVar7 = iVar10 + iVar4 * 0x60;
          (**(code **)(*(int *)(iVar7 + 8) + 0x2c))(iVar7,0);
        }
        for (iVar4 = 5; iVar4 < 0x16; iVar4 = iVar4 + 1) {
          iVar7 = iVar10 + iVar4 * 0x60;
          (**(code **)(*(int *)(iVar7 + 8) + 0x2c))(iVar7,0);
        }
      }
      break;
    case 0xb:
      iVar10 = param_1 + iVar8 * 0x16c;
      *(float *)(iVar10 + 0x38) = *(float *)(iVar10 + 0x38) + *(float *)(iGpffff86b4 + 0x38);
      fStack_40 = *(float *)(param_1 + iVar8 * 0x16c + 0x38) / 0.13333334;
      fStack_44 = pfRam0040ab1c[8];
      if ((long)((ulong)*(byte *)(param_1 + 0x25) << 0x3c) < 0) {
        fStack_44 = -pfRam0040ab1c[10];
      }
      if (fStack_40 < 1.0) {
        fStack_30 = *(float *)(param_1 + iVar8 * 0x16c + 0x184) +
                    fStack_40 * (fStack_44 - *(float *)(param_1 + iVar8 * 0x16c + 0x184));
        fStack_34 = *(float *)(param_1 + iVar8 * 0x16c + 0x188) +
                    fStack_40 * (pfRam0040ab1c[9] - *(float *)(param_1 + iVar8 * 0x16c + 0x188));
        fStack_38 = *(float *)(param_1 + iVar8 * 0x16c + 0x18c) +
                    fStack_40 * (pfRam0040ab1c[10] - *(float *)(param_1 + iVar8 * 0x16c + 0x18c));
        fStack_3c = *(float *)(param_1 + iVar8 * 0x16c + 400) +
                    fStack_40 * (pfRam0040ab1c[0xb] - *(float *)(param_1 + iVar8 * 0x16c + 400));
      }
      else {
        fStack_30 = fStack_44;
        fStack_34 = pfRam0040ab1c[9];
        fStack_38 = pfRam0040ab1c[10];
        fStack_3c = pfRam0040ab1c[0xb];
      }
      SetPosition__10MenuWindowFff(fStack_30,fStack_34,param_1 + iVar8 * 0x16c + 0x7c);
      SetSize__10MenuWindowFff(fStack_38,fStack_3c,param_1 + iVar8 * 0x16c + 0x7c);
      iVar10 = *(int *)(param_1 + iVar8 * 0x16c + 0xc0);
      *(byte *)(iVar10 + 0x12) = *(byte *)(iVar10 + 0x12) & 0xfe;
      iVar10 = GetPlace__10MenuWindowFss(param_1 + iVar8 * 0x16c + 0x7c,
                               (short)*(undefined4 *)(param_1 + iVar8 * 0x16c + 0x150),
                               (short)*(undefined4 *)(param_1 + iVar8 * 0x16c + 0x154));
      fVar11 = -*(float *)(iVar10 + 0x28) + 2.0;
      *(undefined4 *)(*(int *)(param_1 + iVar8 * 0x16c + 0xbc) + 0x38) = 0;
      uVar5 = SetScroll__10MenuWindowFss(param_1 + iVar8 * 0x16c + 0x7c,0,0);
      SetOffset__10MenuWindowFff(0,fVar11,param_1 + iVar8 * 0x16c + 0x7c,uVar5);
      *(float *)(param_1 + iVar8 * 0x16c + 0x198) = fVar11;
      if (1.0 <= fStack_40) {
        *(undefined2 *)(param_1 + iVar8 * 0x16c + 0x32) = 7;
        *(undefined2 *)(param_1 + iVar8 * 0x16c + 0x34) = 0;
        SetPosition__10MenuWindowFff(fStack_44,pfRam0040ab1c[9],param_1 + iVar8 * 0x16c + 0x7c);
        SetSize__10MenuWindowFff(pfRam0040ab1c[10],pfRam0040ab1c[0xb],param_1 + iVar8 * 0x16c + 0x7c);
        *(float *)(param_1 + iVar8 * 0x16c + 0x184) = fStack_44;
        *(float *)(param_1 + iVar8 * 0x16c + 0x188) = pfRam0040ab1c[9];
        *(float *)(param_1 + iVar8 * 0x16c + 0x18c) = pfRam0040ab1c[10];
        *(float *)(param_1 + iVar8 * 0x16c + 400) = pfRam0040ab1c[0xb];
      }
      if (*(int *)(param_1 + iVar8 * 0x16c + 0x13c) != 0) {
        iVar4 = GetPlace__10MenuWindowFss(param_1 + iVar8 * 0x16c + 0x7c,
                                (short)*(undefined4 *)(param_1 + iVar8 * 0x16c + 0x150),
                                (short)*(undefined4 *)(param_1 + iVar8 * 0x16c + 0x154));
        iVar10 = *(int *)(param_1 + iVar8 * 0x16c + 0x13c);
        (**(code **)(*(int *)(iVar10 + 0x188) + 0x24))(0,*(float *)(iVar4 + 0x28) - 2.0);
        SetUV__10MenuSpriteFUsUsUsUs(iVar10 + 0x180,0,0,0xf8,0x1b);
        (**(code **)(*(int *)(iVar10 + 0x188) + 0x28))(0x43780000,0x41d80000);
        fStack_40 = fStack_40 * 32.0;
        if (fStack_40 < 0.0) {
          fStack_40 = 0.0;
        }
        if (32.0 <= fStack_40) {
          fStack_40 = 32.0;
        }
        fVar11 = fStack_40 + 64.0;
        if (fVar11 < 2.1474836e+09) {
          uVar12 = (uint)fVar11;
        }
        else {
          uVar12 = (int)(fVar11 - 2.1474836e+09) | 0x80000000;
        }
        (**(code **)(*(int *)(iVar10 + 0x188) + 0x2c))(iVar10 + 0x180,uVar12);
        lVar6 = GetPlace__10MenuWindowFss(param_1 + iVar8 * 0x16c + 0x7c,
                                (short)*(undefined4 *)(param_1 + iVar8 * 0x16c + 0x150),
                                (short)*(undefined4 *)(param_1 + iVar8 * 0x16c + 0x154));
        if (lVar6 != 0) {
          fVar11 = fStack_40 + 64.0;
          if (fVar11 < 2.1474836e+09) {
            uVar12 = (uint)fVar11;
          }
          else {
            uVar12 = (int)(fVar11 - 2.1474836e+09) | 0x80000000;
          }
          (**(code **)(*(int *)((int)lVar6 + 8) + 0x2c))(lVar6,uVar12);
        }
        lVar6 = GetPlace__10MenuWindowFss(param_1 + iVar8 * 0x16c + 0x7c,
                                (short)*(undefined4 *)(param_1 + iVar8 * 0x16c + 0x150) + 1,
                                (short)*(undefined4 *)(param_1 + iVar8 * 0x16c + 0x154));
        if (lVar6 != 0) {
          fStack_40 = fStack_40 + 64.0;
          if (fStack_40 < 2.1474836e+09) {
            uVar12 = (uint)fStack_40;
          }
          else {
            uVar12 = (int)(fStack_40 - 2.1474836e+09) | 0x80000000;
          }
          (**(code **)(*(int *)((int)lVar6 + 8) + 0x2c))(lVar6,uVar12);
        }
        for (iVar4 = 0; iVar4 < 4; iVar4 = iVar4 + 1) {
          iVar7 = iVar10 + iVar4 * 0x60;
          (**(code **)(*(int *)(iVar7 + 8) + 0x2c))(iVar7,0);
        }
        for (iVar4 = 5; iVar4 < 0x16; iVar4 = iVar4 + 1) {
          iVar7 = iVar10 + iVar4 * 0x60;
          (**(code **)(*(int *)(iVar7 + 8) + 0x2c))(iVar7,0);
        }
      }
      break;
    case 0xc:
      sVar1 = *(short *)(param_1 + iVar8 * 0x16c + 0x34);
      if (sVar1 == 1) {
        Release__7MenuObjFv(param_1 + iVar8 * 0x16c + 0x3c);
        iVar10 = param_1 + iVar8 * 0x16c;
        *(byte *)(iVar10 + 0x30) = *(byte *)(iVar10 + 0x30) & 0xfd;
        Release__7MenuObjFv(param_1 + iVar8 * 0x16c + 0x7c);
        iVar10 = param_1 + iVar8 * 0x16c;
        *(byte *)(iVar10 + 0x30) = *(byte *)(iVar10 + 0x30) & 0xf7;
        if (((ulong)*(ushort *)(param_1 + iVar8 * 0x16c + 0x30) & 0xfff) >> 4 != 0) {
          __destroy_new_array(*(undefined4 *)(param_1 + iVar8 * 0x16c + 0x130),0x27c030);
        }
        iVar10 = param_1 + iVar8 * 0x16c;
        *(ushort *)(iVar10 + 0x30) = *(ushort *)(iVar10 + 0x30) & 0xf00f;
        *(undefined4 *)(param_1 + iVar8 * 0x16c + 0x130) = 0;
        if (*(int *)(param_1 + iVar8 * 0x16c + 0x134) != 0) {
          __destroy_new_array(*(undefined4 *)(param_1 + iVar8 * 0x16c + 0x134),0x27d4f0);
        }
        *(undefined4 *)(param_1 + iVar8 * 0x16c + 0x134) = 0;
        iVar10 = param_1 + iVar8 * 0x16c;
        *(byte *)(iVar10 + 0x31) = *(byte *)(iVar10 + 0x31) & 0xef;
        if (*(int *)(param_1 + iVar8 * 0x16c + 0x13c) != 0) {
          __destroy_new_array(*(undefined4 *)(param_1 + iVar8 * 0x16c + 0x13c),0x2661a0);
        }
        *(undefined4 *)(param_1 + iVar8 * 0x16c + 0x13c) = 0;
        if ((*(int *)(param_1 + iVar8 * 0x16c + 0x140) != 0) &&
           (iVar10 = *(int *)(param_1 + iVar8 * 0x16c + 0x140), iVar10 != 0)) {
          (**(code **)(*(int *)(iVar10 + 8) + 8))(iVar10,1);
        }
        *(undefined4 *)(param_1 + iVar8 * 0x16c + 0x140) = 0;
        if (*(int *)(param_1 + iVar8 * 0x16c + 0x138) != 0) {
          __destroy_new_array(*(undefined4 *)(param_1 + iVar8 * 0x16c + 0x138),0x277890);
        }
        *(undefined4 *)(param_1 + iVar8 * 0x16c + 0x138) = 0;
        if (*(int *)(param_1 + iVar8 * 0x16c + 0x144) != 0) {
          __destroy_new_array(*(undefined4 *)(param_1 + iVar8 * 0x16c + 0x144),0x28d070);
        }
        *(undefined4 *)(param_1 + iVar8 * 0x16c + 0x144) = 0;
        if (*(int *)(param_1 + iVar8 * 0x16c + 0x148) != 0) {
          __destroy_new_array(*(undefined4 *)(param_1 + iVar8 * 0x16c + 0x148),0x2766d0);
        }
        *(undefined4 *)(param_1 + iVar8 * 0x16c + 0x148) = 0;
        if (*(int *)(param_1 + iVar8 * 0x16c + 0x14c) != 0) {
          __destroy_new_array(*(undefined4 *)(param_1 + iVar8 * 0x16c + 0x14c),0x280920);
        }
        *(undefined4 *)(param_1 + iVar8 * 0x16c + 0x14c) = 0;
        *(undefined2 *)(param_1 + iVar8 * 0x16c + 0x32) = 0;
        *(undefined2 *)(param_1 + iVar8 * 0x16c + 0x34) = 0;
      }
      else if ((sVar1 == 0) && (*(char *)(param_1 + iVar8 * 0x16c + 0x124) == '\0')) {
        ReleaseOT__7MenuObjFv(param_1 + iVar8 * 0x16c + 0x3c);
        iVar10 = param_1 + iVar8 * 0x16c;
        *(byte *)(iVar10 + 0x30) = *(byte *)(iVar10 + 0x30) & 0xfe;
        ReleaseOT__7MenuObjFv(param_1 + iVar8 * 0x16c + 0x7c);
        iVar10 = param_1 + iVar8 * 0x16c;
        *(byte *)(iVar10 + 0x30) = *(byte *)(iVar10 + 0x30) & 0xfb;
        *(undefined2 *)(param_1 + iVar8 * 0x16c + 0x34) = 1;
      }
    }
  }
  sVar1 = *(short *)(param_1 + 0x8b8);
  if (sVar1 == 0xc) {
    if (*(short *)(param_1 + 0x8ba) == 1) {
      Release__7MenuObjFv(param_1 + 0x8bc);
      *(byte *)(param_1 + 0x24) = *(byte *)(param_1 + 0x24) & 0xbf;
      Release__7MenuObjFv(param_1 + 0x8fc);
      *(byte *)(param_1 + 0x25) = *(byte *)(param_1 + 0x25) & 0xfe;
      *(undefined2 *)(param_1 + 0x8b8) = 0;
      *(undefined2 *)(param_1 + 0x8ba) = 0;
    }
    else if ((*(short *)(param_1 + 0x8ba) == 0) && (*(char *)(param_1 + 0x9a4) == '\0')) {
      ReleaseOT__7MenuObjFv(param_1 + 0x8bc);
      *(byte *)(param_1 + 0x24) = *(byte *)(param_1 + 0x24) & 0xdf;
      ReleaseOT__7MenuObjFv(param_1 + 0x8fc);
      *(byte *)(param_1 + 0x24) = *(byte *)(param_1 + 0x24) & 0x7f;
      *(undefined2 *)(param_1 + 0x8ba) = 1;
    }
  }
  else if (((sVar1 != 2) && (sVar1 == 1)) && (*(char *)(param_1 + 0x9a4) == '\x01')) {
    *(undefined2 *)(param_1 + 0x8b8) = 2;
    *(undefined2 *)(param_1 + 0x8ba) = 0;
  }
  if (*(short *)(param_1 + 0xa30) == 2) {
    if ((long)((ulong)*(byte *)(param_1 + 0x24) << 0x3c) < 0) {
      ReleaseOT__7MenuObjFv(param_1 + 0xa34);
      *(byte *)(param_1 + 0x24) = *(byte *)(param_1 + 0x24) & 0xf7;
    }
    else if ((long)((ulong)*(byte *)(param_1 + 0x24) << 0x3b) < 0) {
      Release__7MenuObjFv(param_1 + 0xa34);
      *(byte *)(param_1 + 0x24) = *(byte *)(param_1 + 0x24) & 0xef;
      *(undefined2 *)(param_1 + 0xa30) = 0;
    }
  }
  if (*(short *)(param_1 + 0xa32) == 2) {
    if ((long)((ulong)*(byte *)(param_1 + 0x25) << 0x3e) < 0) {
      ReleaseOT__7MenuObjFv(*(undefined4 *)(param_1 + 0xb30));
      *(byte *)(param_1 + 0x25) = *(byte *)(param_1 + 0x25) & 0xfd;
    }
    else {
      iVar8 = *(int *)(param_1 + 0xb30);
      if (iVar8 != 0) {
        (**(code **)(*(int *)(iVar8 + 8) + 8))(iVar8,1);
      }
      *(undefined4 *)(param_1 + 0xb30) = 0;
      *(undefined2 *)(param_1 + 0xa32) = 0;
    }
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005aadd0  SetMode__7BtlMenuFib
 * C++: BtlMenu::SetMode(int, bool)
 * size: 0x90 bytes
 * --------------------------------------------------------------------------- */
void SetMode__7BtlMenuFib(int param_1,undefined2 param_2,char param_3)

{
  *(byte *)(param_1 + 0x24) = *(byte *)(param_1 + 0x24) & 0xfe;
  if (param_3 == '\x01') {
    *(byte *)(param_1 + 0x24) = *(byte *)(param_1 + 0x24) & 0xfe | 1;
  }
  *(undefined2 *)(param_1 + 0x28) = param_2;
  *(undefined2 *)(param_1 + 0x2a) = 0;
  *(undefined4 *)(param_1 + 0xb34) = 0;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005aae60  IsReady__7BtlMenuFv
 * C++: BtlMenu::IsReady()
 * size: 0x178 bytes
 * --------------------------------------------------------------------------- */
undefined4 IsReady__7BtlMenuFv(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  iVar2 = 0;
  while( true ) {
    if (5 < iVar2) {
      if ((*(short *)(param_1 + 0x8b8) == 1) || (*(short *)(param_1 + 0x8b8) == 0xc)) {
        uVar1 = 0;
      }
      else if (*(short *)(param_1 + 0xa30) == 2) {
        uVar1 = 0;
      }
      else {
        uVar1 = 1;
      }
      return uVar1;
    }
    if ((((*(short *)(param_1 + iVar2 * 0x16c + 0x32) != 0) &&
         (*(short *)(param_1 + iVar2 * 0x16c + 0x32) != 2)) &&
        (*(short *)(param_1 + iVar2 * 0x16c + 0x32) != 4)) &&
       ((*(short *)(param_1 + iVar2 * 0x16c + 0x32) != 7 &&
        (*(short *)(param_1 + iVar2 * 0x16c + 0x32) != 10)))) break;
    iVar2 = iVar2 + 1;
  }
  return 0;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005aafe0  AutoMenuFunc__7BtlMenuFiiiii
 * C++: BtlMenu::AutoMenuFunc(int, int, int, int, int)
 * size: 0x2c8 bytes
 * --------------------------------------------------------------------------- */
undefined4
AutoMenuFunc__7BtlMenuFiiiii
          (int param_1,int param_2,undefined4 param_3,int param_4,int param_5,int param_6)

{
  long lVar1;
  int iVar2;
  int iVar3;
  int aiStack_160 [64];
  int iStack_60;
  int iStack_50;
  undefined4 uStack_40;
  int iStack_30;
  int iStack_20;
  int iStack_10;
  
  iVar2 = 0;
  iVar3 = -1;
  iStack_60 = param_1;
  iStack_50 = param_2;
  uStack_40 = param_3;
  iStack_30 = param_4;
  iStack_20 = param_5;
  iStack_10 = param_6;
  lVar1 = GetPlace__10MenuWindowFss(param_1 + param_2 * 0x16c + 0x7c,(short)param_3,0);
  while (lVar1 != 0) {
    aiStack_160[iVar2] = (int)*(short *)((int)lVar1 + 0x16);
    if (iStack_10 == -1) {
      if (iStack_20 == aiStack_160[iVar2]) {
        iVar3 = iVar2;
      }
    }
    else if ((iStack_20 <= aiStack_160[iVar2]) && (aiStack_160[iVar2] <= iStack_10)) {
      iVar3 = iVar2;
    }
    iVar2 = iVar2 + 1;
    lVar1 = GetPlace__10MenuWindowFss(iStack_60 + iStack_50 * 0x16c + 0x7c,(short)uStack_40,(short)iVar2);
  }
  if (iVar3 == -1) {
    if ((((iStack_50 == 0) && (iStack_10 == -1)) &&
        ((iStack_20 == 1 || (((iStack_20 == 2 || (iStack_20 == 3)) || (iStack_20 == 4)))))) &&
       (((aiStack_160[iStack_30] == 1 || (aiStack_160[iStack_30] == 2)) ||
        ((aiStack_160[iStack_30] == 3 || (aiStack_160[iStack_30] == 4)))))) {
      return 0x20;
    }
  }
  else {
    if (iVar3 == iStack_30) {
      return 0x2000;
    }
    if (iVar3 < iStack_30) {
      return 0x10;
    }
    if (iStack_30 < iVar3) {
      return 0x40;
    }
  }
  return 0x40;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005ab2b0  SetWindowMove__7BtlMenuFii
 * C++: BtlMenu::SetWindowMove(int, int)
 * size: 0xa50 bytes
 * --------------------------------------------------------------------------- */
void SetWindowMove__7BtlMenuFii(int param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  
  if (param_3 == 3) {
    if (*(short *)(param_1 + param_2 * 0x16c + 0x32) != 10) {
      *(undefined2 *)(param_1 + param_2 * 0x16c + 0x32) = 9;
      *(undefined2 *)(param_1 + param_2 * 0x16c + 0x34) = 0;
      *(undefined2 *)(param_1 + param_2 * 0x16c + 0x36) = 0;
      *(undefined4 *)(param_1 + param_2 * 0x16c + 0x38) = 0;
      *(undefined4 *)(param_1 + param_2 * 0x16c + 0x184) =
           *(undefined4 *)(param_1 + param_2 * 0x16c + 0xe0);
      *(undefined4 *)(param_1 + param_2 * 0x16c + 0x188) =
           *(undefined4 *)(param_1 + param_2 * 0x16c + 0xe4);
      *(undefined4 *)(param_1 + param_2 * 0x16c + 0x18c) =
           *(undefined4 *)(param_1 + param_2 * 0x16c + 0xe8);
      *(undefined4 *)(param_1 + param_2 * 0x16c + 400) =
           *(undefined4 *)(param_1 + param_2 * 0x16c + 0xec);
      *(undefined4 *)(param_1 + param_2 * 0x16c + 0x194) =
           *(undefined4 *)(param_1 + param_2 * 0x16c + 0x198);
    }
  }
  else if (param_3 == 2) {
    if ((*(short *)(param_1 + param_2 * 0x16c + 0x32) == 10) ||
       (*(short *)(param_1 + param_2 * 0x16c + 0x32) == 9)) {
      *(undefined2 *)(param_1 + param_2 * 0x16c + 0x32) = 0xb;
      *(undefined2 *)(param_1 + param_2 * 0x16c + 0x34) = 0;
      *(undefined2 *)(param_1 + param_2 * 0x16c + 0x36) = 0;
      *(undefined4 *)(param_1 + param_2 * 0x16c + 0x38) = 0;
    }
    else {
      *(undefined2 *)(param_1 + param_2 * 0x16c + 0x32) = 6;
      *(undefined2 *)(param_1 + param_2 * 0x16c + 0x34) = 0;
      *(undefined2 *)(param_1 + param_2 * 0x16c + 0x36) = 0;
      *(undefined4 *)(param_1 + param_2 * 0x16c + 0x38) = 0;
    }
    *(undefined4 *)(param_1 + param_2 * 0x16c + 0x184) =
         *(undefined4 *)(param_1 + param_2 * 0x16c + 0xe0);
    *(undefined4 *)(param_1 + param_2 * 0x16c + 0x188) =
         *(undefined4 *)(param_1 + param_2 * 0x16c + 0xe4);
    *(undefined4 *)(param_1 + param_2 * 0x16c + 0x18c) =
         *(undefined4 *)(param_1 + param_2 * 0x16c + 0xe8);
    *(undefined4 *)(param_1 + param_2 * 0x16c + 400) =
         *(undefined4 *)(param_1 + param_2 * 0x16c + 0xec);
    *(undefined4 *)(param_1 + param_2 * 0x16c + 0x194) =
         *(undefined4 *)(param_1 + param_2 * 0x16c + 0x198);
  }
  else if (param_3 == 1) {
    if ((*(short *)(param_1 + param_2 * 0x16c + 0x32) == 7) ||
       (*(short *)(param_1 + param_2 * 0x16c + 0x32) == 6)) {
      *(undefined2 *)(param_1 + param_2 * 0x16c + 0x32) = 8;
      *(undefined2 *)(param_1 + param_2 * 0x16c + 0x34) = 0;
      *(undefined2 *)(param_1 + param_2 * 0x16c + 0x36) = 0;
      *(undefined4 *)(param_1 + param_2 * 0x16c + 0x38) = 0;
    }
    else if ((*(short *)(param_1 + param_2 * 0x16c + 0x32) == 2) ||
            (*(short *)(param_1 + param_2 * 0x16c + 0x32) == 1)) {
      *(undefined2 *)(param_1 + param_2 * 0x16c + 0x32) = 3;
      *(undefined2 *)(param_1 + param_2 * 0x16c + 0x34) = 0;
      *(undefined2 *)(param_1 + param_2 * 0x16c + 0x36) = 0;
      *(undefined4 *)(param_1 + param_2 * 0x16c + 0x38) = 0;
      *(int *)(param_1 + param_2 * 0x16c + 0x150) =
           (int)*(short *)(*(int *)(param_1 + 0xb20) + 0x1c);
      *(int *)(param_1 + param_2 * 0x16c + 0x154) =
           (int)*(short *)(*(int *)(param_1 + 0xb20) + 0x1e);
      uVar1 = GetTargetX__10MenuWindowCFv(param_1 + param_2 * 0x16c + 0x7c);
      *(undefined4 *)(param_1 + param_2 * 0x16c + 0x15c) = uVar1;
      uVar1 = GetTargetY__10MenuWindowCFv(param_1 + param_2 * 0x16c + 0x7c);
      *(undefined4 *)(param_1 + param_2 * 0x16c + 0x160) = uVar1;
      uVar1 = GetTargetY__10MenuWindowCFv(param_1 + param_2 * 0x16c + 0x7c);
      *(undefined4 *)(param_1 + param_2 * 0x16c + 0x198) = uVar1;
    }
    else {
      *(undefined2 *)(param_1 + param_2 * 0x16c + 0x32) = 3;
      *(undefined2 *)(param_1 + param_2 * 0x16c + 0x34) = 0;
      *(undefined2 *)(param_1 + param_2 * 0x16c + 0x36) = 0;
      *(undefined4 *)(param_1 + param_2 * 0x16c + 0x38) = 0;
    }
    *(undefined4 *)(param_1 + param_2 * 0x16c + 0x184) =
         *(undefined4 *)(param_1 + param_2 * 0x16c + 0xe0);
    *(undefined4 *)(param_1 + param_2 * 0x16c + 0x188) =
         *(undefined4 *)(param_1 + param_2 * 0x16c + 0xe4);
    *(undefined4 *)(param_1 + param_2 * 0x16c + 0x18c) =
         *(undefined4 *)(param_1 + param_2 * 0x16c + 0xe8);
    *(undefined4 *)(param_1 + param_2 * 0x16c + 400) =
         *(undefined4 *)(param_1 + param_2 * 0x16c + 0xec);
    *(undefined4 *)(param_1 + param_2 * 0x16c + 0x194) =
         *(undefined4 *)(param_1 + param_2 * 0x16c + 0x198);
  }
  else if ((param_3 == 0) && (*(short *)(param_1 + param_2 * 0x16c + 0x32) != 2)) {
    *(undefined2 *)(param_1 + param_2 * 0x16c + 0x32) = 5;
    *(undefined2 *)(param_1 + param_2 * 0x16c + 0x34) = 0;
    *(undefined2 *)(param_1 + param_2 * 0x16c + 0x36) = 0;
    *(undefined4 *)(param_1 + param_2 * 0x16c + 0x38) = 0;
    *(undefined4 *)(param_1 + param_2 * 0x16c + 0x184) =
         *(undefined4 *)(param_1 + param_2 * 0x16c + 0xe0);
    *(undefined4 *)(param_1 + param_2 * 0x16c + 0x188) =
         *(undefined4 *)(param_1 + param_2 * 0x16c + 0xe4);
    *(undefined4 *)(param_1 + param_2 * 0x16c + 0x18c) =
         *(undefined4 *)(param_1 + param_2 * 0x16c + 0xe8);
    *(undefined4 *)(param_1 + param_2 * 0x16c + 400) =
         *(undefined4 *)(param_1 + param_2 * 0x16c + 0xec);
    *(undefined4 *)(param_1 + param_2 * 0x16c + 0x194) =
         *(undefined4 *)(param_1 + param_2 * 0x16c + 0x198);
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005abd00  SetWindowClose__7BtlMenuFii
 * C++: BtlMenu::SetWindowClose(int, int)
 * size: 0x224 bytes
 * --------------------------------------------------------------------------- */
void SetWindowClose__7BtlMenuFii(int param_1,int param_2,int param_3)

{
  if (param_3 == -1) {
    if (((*(short *)(param_1 + param_2 * 0x16c + 0x32) != 0) &&
        (*(short *)(param_1 + param_2 * 0x16c + 0x32) != 0xc)) &&
       (*(short *)(param_1 + param_2 * 0x16c + 0x32) != 0xd)) {
      Close__10MenuWindowFUci(param_1 + param_2 * 0x16c + 0x7c,
                      *(uint *)(param_1 + param_2 * 0x16c + 0x178) & 0xff,0x85);
      *(undefined2 *)(param_1 + param_2 * 0x16c + 0x32) = 0xc;
      *(undefined2 *)(param_1 + param_2 * 0x16c + 0x34) = 0;
    }
  }
  else {
    for (; param_2 < param_3; param_2 = param_2 + 1) {
      if (((*(short *)(param_1 + param_2 * 0x16c + 0x32) != 0) &&
          (*(short *)(param_1 + param_2 * 0x16c + 0x32) != 0xc)) &&
         (*(short *)(param_1 + param_2 * 0x16c + 0x32) != 0xd)) {
        Close__10MenuWindowFUci(param_1 + param_2 * 0x16c + 0x7c,
                        *(uint *)(param_1 + param_2 * 0x16c + 0x178) & 0xff,0x85);
        *(undefined2 *)(param_1 + param_2 * 0x16c + 0x32) = 0xc;
        *(undefined2 *)(param_1 + param_2 * 0x16c + 0x34) = 0;
      }
    }
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005abf30  SetNoteWindow__7BtlMenuFPc
 * C++: BtlMenu::SetNoteWindow(char *)
 * size: 0x2d4 bytes
 * --------------------------------------------------------------------------- */
void SetNoteWindow__7BtlMenuFPc(int param_1,undefined4 param_2)

{
  bool bVar1;
  
  bVar1 = false;
  if (*(short *)(param_1 + 0x8b8) == 0) {
    bVar1 = true;
    *(undefined2 *)(param_1 + 0x8b8) = 1;
    *(undefined2 *)(param_1 + 0x8ba) = 0;
    Create__8FontDrawF6GS_PSMUsUsUcUiP10ClutRaster(param_1 + 0x8bc,0x2c,0x400,0x20,1,0,0);
    *(byte *)(param_1 + 0x24) = *(byte *)(param_1 + 0x24) & 0xbf | 0x40;
    *(undefined2 *)(param_1 + 0x8d0) = 4;
    AddOT__7MenuObjFv(param_1 + 0x8bc);
    *(byte *)(param_1 + 0x24) = *(byte *)(param_1 + 0x24) & 0xdf | 0x20;
    *(undefined2 *)(param_1 + 0x910) = 4;
    AddOT__7MenuObjFv(param_1 + 0x8fc);
    *(byte *)(param_1 + 0x24) = *(byte *)(param_1 + 0x24) & 0x7f | 0x80;
    Create__10MenuWindowFUcUcffff(*(undefined4 *)(iRam0040ab1c + 0x40),*(undefined4 *)(iRam0040ab1c + 0x44),
                    *(undefined4 *)(iRam0040ab1c + 0x48),*(undefined4 *)(iRam0040ab1c + 0x4c),
                    param_1 + 0x8fc,5,1);
    *(byte *)(param_1 + 0x25) = *(byte *)(param_1 + 0x25) & 0xfe | 1;
    if (*(int *)(param_1 + 0x938) != 0) {
      (**(code **)(*(int *)(*(int *)(param_1 + 0x938) + 8) + 0x2c))(*(int *)(param_1 + 0x938),0,0,0)
      ;
    }
    SetAlpha__10MenuWindowFUc(param_1 + 0x8fc,0x60);
    Create__8MenuTextFUcUc(param_1 + 0x9b0,1,2);
    (**(code **)(*(int *)(param_1 + 0x9b8) + 0x24))(*(undefined4 *)(iRam0040ab1c + 0x50),0x3f800000)
    ;
    *(undefined1 *)(param_1 + 0xa0a) = 1;
    *(undefined1 *)(param_1 + 0xa0b) = 0;
    *(undefined2 *)(param_1 + 0x9cc) = 0;
    *(undefined2 *)(param_1 + 0x9ce) = 0;
    AddPlace__10MenuWindowFP9MenuPlace(param_1 + 0x8fc,param_1 + 0x9b0);
  }
  if (!bVar1) {
    ClearImage__8FontDrawFv(param_1 + 0x8bc);
  }
  SetMessage__8MenuTextFPcUiUcUc(param_1 + 0x9b0,param_2,0,0,1);
  OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(param_1 + 0x8bc,param_1 + 0x9b0,1,0);
  if (bVar1) {
    Open__10MenuWindowFUci(param_1 + 0x8fc,0,0x85);
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005ac210  SetNoteWindowClose__7BtlMenuFv
 * C++: BtlMenu::SetNoteWindowClose()
 * size: 0x88 bytes
 * --------------------------------------------------------------------------- */
void SetNoteWindowClose__7BtlMenuFv(int param_1)

{
  if ((*(short *)(param_1 + 0x8b8) == 1) || (*(short *)(param_1 + 0x8b8) == 2)) {
    Close__10MenuWindowFUci(param_1 + 0x8fc,0,0x85);
    *(undefined2 *)(param_1 + 0x8b8) = 0xc;
    *(undefined2 *)(param_1 + 0x8ba) = 0;
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005ac2a0  CreateCursole__7BtlMenuFv
 * C++: BtlMenu::CreateCursole()
 * size: 0x16c bytes
 * --------------------------------------------------------------------------- */
void CreateCursole__7BtlMenuFv(int param_1)

{
  ulong uVar1;
  
  if (-1 < (long)((ulong)*(byte *)(param_1 + 0x24) << 0x3b)) {
    Create__6CursorFUcUcUcUc(param_1 + 0xa34,0,2,8,1);
    *(byte *)(param_1 + 0x24) = *(byte *)(param_1 + 0x24) & 0xef | 0x10;
  }
  *(ushort *)(param_1 + 0xae6) = *(ushort *)(param_1 + 0xae6) & 0xfc3f;
  uVar1 = (ulong)*(byte *)(param_1 + 0xae5) & 0xfffffffffffffffd | 2;
  *(char *)(param_1 + 0xae5) = (char)uVar1;
  *(byte *)(param_1 + 0xae4) =
       *(byte *)(param_1 + 0xae4) & 0xfd | (byte)((uint)((uVar1 << 0x3e) >> 0x3f) << 1);
  *(undefined2 *)(param_1 + 0xa48) = 0x10;
  if (-1 < (long)((ulong)*(byte *)(param_1 + 0x24) << 0x3c)) {
    AddOT__7MenuObjFv(param_1 + 0xa34);
    *(byte *)(param_1 + 0x24) = *(byte *)(param_1 + 0x24) & 0xf7 | 8;
  }
  *(byte *)(param_1 + 0xa46) = *(byte *)(param_1 + 0xa46) & 0xfe | 1;
  *(undefined2 *)(param_1 + 0xa30) = 1;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005ac410  SetNextComboChrTitle__7BtlMenuFi
 * C++: BtlMenu::SetNextComboChrTitle(int)
 * size: 0x584 bytes
 * --------------------------------------------------------------------------- */
void SetNextComboChrTitle__7BtlMenuFi(int param_1,int param_2)

{
  undefined4 uVar1;
  undefined8 uVar2;
  int iVar3;
  float fVar4;
  
  *(undefined2 *)(param_1 + param_2 * 0x16c + 0x32) = 1;
  *(undefined2 *)(param_1 + param_2 * 0x16c + 0x34) = 0;
  *(undefined4 *)(param_1 + param_2 * 0x16c + 0x38) = 0;
  Create__8FontDrawF6GS_PSMUsUsUcUiP10ClutRaster(param_1 + param_2 * 0x16c + 0x3c,0x2c,0x400,0x20,0,0,0);
  iVar3 = param_1 + param_2 * 0x16c;
  *(byte *)(iVar3 + 0x30) = *(byte *)(iVar3 + 0x30) & 0xfd | 2;
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + param_2 * 0x16c + 0x94,param_1 + param_2 * 0x16c + 0x3c);
  *(undefined2 *)(param_1 + param_2 * 0x16c + 0x90) = 8;
  AddOT__7MenuObjFv(param_1 + param_2 * 0x16c + 0x7c);
  iVar3 = param_1 + param_2 * 0x16c;
  *(byte *)(iVar3 + 0x30) = *(byte *)(iVar3 + 0x30) & 0xfb | 4;
  Create__10MenuWindowFUcUcffff(*(float *)(iRam0040ab1c + 0x10) + 48.0,*(float *)(iRam0040ab1c + 0x14) - 1.0,
                  0x41a00000,*(undefined4 *)(iRam0040ab1c + 0x1c),param_1 + param_2 * 0x16c + 0x7c,7
                  ,1);
  *(float *)(param_1 + param_2 * 0x16c + 0x17c) = *(float *)(iRam0040ab1c + 0x14) - 1.0;
  *(undefined4 *)(param_1 + param_2 * 0x16c + 0x180) = *(undefined4 *)(iRam0040ab1c + 0x1c);
  *(float *)(param_1 + param_2 * 0x16c + 0x184) = *(float *)(iRam0040ab1c + 0x10) + 48.0;
  *(float *)(param_1 + param_2 * 0x16c + 0x188) = *(float *)(iRam0040ab1c + 0x14) - 1.0;
  *(float *)(param_1 + param_2 * 0x16c + 400) = *(float *)(iRam0040ab1c + 0x14) - 1.0;
  *(undefined4 *)(param_1 + param_2 * 0x16c + 0x178) = 3;
  iVar3 = param_1 + param_2 * 0x16c;
  *(byte *)(iVar3 + 0x30) = *(byte *)(iVar3 + 0x30) & 0xf7 | 8;
  if (((ulong)*(ushort *)(param_1 + param_2 * 0x16c + 0x30) & 0xfff) >> 4 == 0) {
    uVar2 = __nwa__FUi(0x90);
    uVar1 = __construct_new_array(uVar2,0x27bfd0,0x27c030,0x80,1);
    *(undefined4 *)(param_1 + param_2 * 0x16c + 0x130) = uVar1;
    iVar3 = param_1 + param_2 * 0x16c;
    *(ushort *)(iVar3 + 0x30) = *(ushort *)(iVar3 + 0x30) & 0xf00f | 0x10;
  }
  iVar3 = *(int *)(param_1 + param_2 * 0x16c + 0x130);
  Create__8MenuTextFUcUc(iVar3,1,2);
  *(undefined2 *)(iVar3 + 0x14) = 1;
  (**(code **)(*(int *)(iVar3 + 8) + 0x24))(0,0);
  SetMessage__8MenuTextFPcUiUcUc(iVar3,*puRam0040ab28,0,0,1);
  *(undefined1 *)(iVar3 + 0x5a) = 1;
  *(undefined1 *)(iVar3 + 0x5b) = 0;
  *(undefined2 *)(iVar3 + 0x1c) = 0;
  *(undefined2 *)(iVar3 + 0x1e) = 0;
  OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(param_1 + param_2 * 0x16c + 0x3c,iVar3,1,0);
  AddPlace__10MenuWindowFP9MenuPlace(param_1 + param_2 * 0x16c + 0x7c,iVar3);
  fVar4 = *(float *)(iVar3 + 0x2c);
  SetSize__10MenuWindowFff(fVar4 + 1.0,*(undefined4 *)(iRam0040ab1c + 0x1c),param_1 + param_2 * 0x16c + 0x7c)
  ;
  *(float *)(param_1 + param_2 * 0x16c + 0x18c) = fVar4 + 1.0;
  *(undefined4 *)(param_1 + param_2 * 0x16c + 400) = *(undefined4 *)(iRam0040ab1c + 0x1c);
  Open__10MenuWindowFUci(param_1 + param_2 * 0x16c + 0x7c,3,0x85);
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005ac9a0  SetNextComboChrMenu__7BtlMenuFii
 * C++: BtlMenu::SetNextComboChrMenu(int, int)
 * size: 0x238 bytes
 * --------------------------------------------------------------------------- */
void SetNextComboChrMenu__7BtlMenuFii(int param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  int iVar2;
  long lVar3;
  undefined1 auStack_2330 [256];
  undefined1 auStack_2230 [8192];
  undefined2 auStack_230 [256];
  int iStack_30;
  undefined4 uStack_20;
  int iStack_10;
  
  iVar2 = 0;
  iStack_10 = param_3;
  if ((param_3 == -1) &&
     (iStack_10 = 0,
     (*(uint *)(param_1 + 0xb34) & 1 << ((int)*(char *)(iGpffff86b4 + 0x2c) & 0x1fU)) != 0)) {
    for (lVar3 = 0; lVar3 < 0xc; lVar3 = (long)(int)((uint)lVar3 + 1)) {
      if ((*(uint *)(param_1 + 0xb34) & 1 << ((uint)lVar3 & 0x1f)) != 0) {
        if (lVar3 == *(char *)(iGpffff86b4 + 0x2c)) break;
        iStack_10 = iStack_10 + 1;
      }
    }
  }
  iStack_30 = param_1;
  uStack_20 = param_2;
  for (uVar1 = 0; (int)uVar1 < 0xc; uVar1 = uVar1 + 1) {
    if ((*(uint *)(iStack_30 + 0xb34) & 1 << (uVar1 & 0x1f)) != 0) {
      auStack_230[iVar2] = (short)uVar1;
      strcpy(auStack_2230 + iVar2 * 0x20,
                      *(undefined4 *)(iGpffff86b4 + uVar1 * 0x4f0 + 0x11c));
      if (*(short *)(iGpffff86b4 + uVar1 * 0x4f0 + 0x13a) != -1) {
        strcat(auStack_2230 + iVar2 * 0x20,
                        *(undefined4 *)
                         (iRam0040ab24 + *(short *)(iGpffff86b4 + uVar1 * 0x4f0 + 0x13a) * 4));
      }
      auStack_2330[iVar2] = 1;
      iVar2 = iVar2 + 1;
    }
  }
  CreateMenu1__7BtlMenuFiiiiPsPcPcbb
            (iStack_30,uStack_20,iStack_10,0xffffffffffffffff,iVar2,auStack_230,auStack_2230,
             auStack_2330);
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005acbe0  SetTargetMenu__7BtlMenuFiiiP12EFCTCOMParamii
 * C++: BtlMenu::SetTargetMenu(int, int, int, EFCTCOMParam *, int, int)
 * size: 0xf00 bytes
 * --------------------------------------------------------------------------- */
void SetTargetMenu__7BtlMenuFiiiP12EFCTCOMParamii
               (int param_1,undefined4 param_2,int param_3,undefined4 param_4,int param_5,
               undefined4 param_6,undefined4 param_7)

{
  bool bVar1;
  int iVar2;
  undefined8 uVar3;
  long lVar4;
  int iVar5;
  undefined1 auStack_23e0 [96];
  undefined1 auStack_2380 [256];
  undefined1 auStack_2280 [8192];
  undefined2 auStack_280 [262];
  float fStack_74;
  int iStack_70;
  undefined4 uStack_60;
  int iStack_50;
  undefined4 uStack_40;
  int iStack_30;
  undefined4 uStack_20;
  undefined4 uStack_10;
  
  iVar5 = 0;
  bVar1 = false;
  lVar4 = 0;
  while (lVar4 < 0xc) {
    iVar2 = (int)lVar4;
    if ((((((*(byte *)(iGpffff86b4 + iVar2 * 0x4f0 + 0xb0) & 1) != 0) &&
          ((long)((ulong)*(byte *)(iGpffff86b4 + iVar2 * 0x4f0 + 0xb0) << 0x3e) < 0)) &&
         (-1 < (long)((ulong)*(byte *)(iGpffff86b4 + iVar2 * 0x4f0 + 0xb2) << 0x3d))) &&
        (((lVar4 != *(char *)(iGpffff86b4 + 0x2c) &&
          (0 < *(short *)(iGpffff86b4 + iVar2 * 0x4f0 + 0x124))) &&
         (((*(byte *)(iGpffff86b4 +
                      (*(char *)(iGpffff86b4 + 0x2c) * 0x50 - (int)*(char *)(iGpffff86b4 + 0x2c)) *
                      0x10 + 0xb4) & 1) != (*(byte *)(iGpffff86b4 + iVar2 * 0x4f0 + 0xb4) & 1) &&
          (((long)((ulong)*(byte *)(iGpffff86b4 + iVar2 * 0x4f0 + 0xb0) << 0x3a) < 0 &&
           ('\x15' < *(char *)(iGpffff86b4 + iVar2 * 0x4f0 + 0xb8))))))))) &&
       (*(char *)(iGpffff86b4 + iVar2 * 0x4f0 + 0xb8) < '\'')) {
      bVar1 = true;
    }
    lVar4 = (long)(iVar2 + 1);
  }
  iStack_70 = param_1;
  uStack_60 = param_2;
  iStack_50 = param_3;
  uStack_40 = param_4;
  iStack_30 = param_5;
  uStack_20 = param_6;
  uStack_10 = param_7;
  if (param_3 == 0) {
    for (iVar2 = 0; iVar2 < 0xc; iVar2 = iVar2 + 1) {
      if (((((((*(byte *)(iGpffff86b4 + iVar2 * 0x4f0 + 0xb0) & 1) != 0) &&
             ((long)((ulong)*(byte *)(iGpffff86b4 + iVar2 * 0x4f0 + 0xb0) << 0x3e) < 0)) &&
            (-1 < (long)((ulong)*(byte *)(iGpffff86b4 + iVar2 * 0x4f0 + 0xb2) << 0x3d))) &&
           ((*(byte *)(iGpffff86b4 +
                       (*(char *)(iGpffff86b4 + 0x2c) * 0x50 - (int)*(char *)(iGpffff86b4 + 0x2c)) *
                       0x10 + 0xb4) & 1) != (*(byte *)(iGpffff86b4 + iVar2 * 0x4f0 + 0xb4) & 1))) &&
          ((!bVar1 ||
           ((((long)((ulong)*(byte *)(iGpffff86b4 + iVar2 * 0x4f0 + 0xb0) << 0x3a) < 0 &&
             ('\x15' < *(char *)(iGpffff86b4 + iVar2 * 0x4f0 + 0xb8))) &&
            (*(char *)(iGpffff86b4 + iVar2 * 0x4f0 + 0xb8) < '\'')))))) &&
         (0 < *(short *)(iGpffff86b4 + iVar2 * 0x4f0 + 0x124))) {
        auStack_280[iVar5] = (short)iVar2;
        strcpy(auStack_2280 + iVar5 * 0x20,
                        *(undefined4 *)(iGpffff86b4 + iVar2 * 0x4f0 + 0x11c));
        if (*(short *)(iGpffff86b4 + iVar2 * 0x4f0 + 0x13a) != -1) {
          strcat(auStack_2280 + iVar5 * 0x20,
                          *(undefined4 *)
                           (iRam0040ab24 + *(short *)(iGpffff86b4 + iVar2 * 0x4f0 + 0x13a) * 4));
        }
        auStack_2380[iVar5] = 1;
        iVar5 = iVar5 + 1;
      }
    }
  }
  else if (((ulong)*(byte *)(param_5 + 5) & 0xf) >> 1 == 5) {
    auStack_280[0] = 100;
    if (((ulong)*(ushort *)(param_5 + 4) & 0x1ff) >> 7 == 1) {
      strcpy(auStack_2280,*(undefined4 *)(iRam0040ab20 + 0xb0));
    }
    else if (((ulong)*(ushort *)(param_5 + 4) & 0x1ff) >> 7 == 2) {
      strcpy(auStack_2280,*(undefined4 *)(iRam0040ab20 + 0xb4));
    }
    else {
      strcpy(auStack_2280,*(undefined4 *)(iRam0040ab20 + 0xac));
    }
    auStack_2380[0] = 1;
    if (((ulong)*(byte *)(iStack_30 + 4) & 0x7f) >> 5 == 1) {
      uVar3 = SpecialEffectCode__FiiiP7ECParamP6EFFTBLP11BtlChrParam(*(undefined1 *)(iGpffff86b4 + 0x2c),iStack_50,uStack_40,iStack_30 + 8,
                              auStack_23e0,
                              iGpffff86b4 +
                              (*(char *)(iGpffff86b4 + 0x2c) * 0x50 -
                              (int)*(char *)(iGpffff86b4 + 0x2c)) * 0x10 + 0xb0);
      iVar5 = 0;
      lVar4 = 0;
      while (lVar4 < 0xc) {
        iVar2 = (int)lVar4;
        if ((((*(byte *)(iGpffff86b4 + iVar2 * 0x4f0 + 0xb0) & 1) != 0) &&
            ((long)((ulong)*(byte *)(iGpffff86b4 + iVar2 * 0x4f0 + 0xb0) << 0x3e) < 0)) &&
           ((((-1 < (long)((ulong)*(byte *)(iGpffff86b4 + iVar2 * 0x4f0 + 0xb2) << 0x3d) &&
              ((((ulong)*(ushort *)(iStack_30 + 4) & 0x1ff) >> 7 != 0 ||
               (lVar4 == *(char *)(iGpffff86b4 + 0x2c))))) &&
             ((((ulong)*(ushort *)(iStack_30 + 4) & 0x1ff) >> 7 != 1 ||
              ((*(byte *)(iGpffff86b4 +
                          (*(char *)(iGpffff86b4 + 0x2c) * 0x50 - (int)*(char *)(iGpffff86b4 + 0x2c)
                          ) * 0x10 + 0xb4) & 1) ==
               (*(byte *)(iGpffff86b4 + iVar2 * 0x4f0 + 0xb4) & 1))))) &&
            (((((ulong)*(ushort *)(iStack_30 + 4) & 0x1ff) >> 7 != 2 ||
              ((*(byte *)(iGpffff86b4 +
                          (*(char *)(iGpffff86b4 + 0x2c) * 0x50 - (int)*(char *)(iGpffff86b4 + 0x2c)
                          ) * 0x10 + 0xb4) & 1) !=
               (*(byte *)(iGpffff86b4 + iVar2 * 0x4f0 + 0xb4) & 1))) &&
             (EffectCodeFunc__FiiP6EFFTBLfP8ECResultPfP11BtlChrParambb(0x3f800000,lVar4,uVar3,auStack_23e0,0,&fStack_74,
                              iGpffff86b4 + iVar2 * 0x4f0 + 0xb0,0,0), 0.0 < fStack_74)))))) {
          iVar5 = iVar5 + 1;
        }
        lVar4 = (long)(iVar2 + 1);
      }
      if (iVar5 == 0) {
        auStack_2380[0] = 0;
      }
    }
    iVar5 = 1;
  }
  else {
    uVar3 = SpecialEffectCode__FiiiP7ECParamP6EFFTBLP11BtlChrParam(*(undefined1 *)(iGpffff86b4 + 0x2c),param_3,param_4,param_5 + 8,
                            auStack_23e0,
                            iGpffff86b4 +
                            (*(char *)(iGpffff86b4 + 0x2c) * 0x50 -
                            (int)*(char *)(iGpffff86b4 + 0x2c)) * 0x10 + 0xb0);
    lVar4 = 0;
    while (lVar4 < 0xc) {
      iVar2 = (int)lVar4;
      if ((((((*(byte *)(iGpffff86b4 + iVar2 * 0x4f0 + 0xb0) & 1) != 0) &&
            ((long)((ulong)*(byte *)(iGpffff86b4 + iVar2 * 0x4f0 + 0xb0) << 0x3e) < 0)) &&
           ((-1 < (long)((ulong)*(byte *)(iGpffff86b4 + iVar2 * 0x4f0 + 0xb2) << 0x3d) &&
            ((((ulong)*(ushort *)(iStack_30 + 4) & 0x1ff) >> 7 != 0 ||
             (lVar4 == *(char *)(iGpffff86b4 + 0x2c))))))) &&
          (((((ulong)*(ushort *)(iStack_30 + 4) & 0x1ff) >> 7 != 1 ||
            ((*(byte *)(iGpffff86b4 +
                        (*(char *)(iGpffff86b4 + 0x2c) * 0x50 - (int)*(char *)(iGpffff86b4 + 0x2c))
                        * 0x10 + 0xb4) & 1) == (*(byte *)(iGpffff86b4 + iVar2 * 0x4f0 + 0xb4) & 1)))
           && ((((ulong)*(ushort *)(iStack_30 + 4) & 0x1ff) >> 7 != 2 ||
               ((*(byte *)(iGpffff86b4 +
                           (*(char *)(iGpffff86b4 + 0x2c) * 0x50 -
                           (int)*(char *)(iGpffff86b4 + 0x2c)) * 0x10 + 0xb4) & 1) !=
                (*(byte *)(iGpffff86b4 + iVar2 * 0x4f0 + 0xb4) & 1))))))) &&
         (((((ulong)*(byte *)(iStack_30 + 4) & 0x7f) >> 5 != 0 || (!bVar1)) ||
          ((((long)((ulong)*(byte *)(iGpffff86b4 + iVar2 * 0x4f0 + 0xb0) << 0x3a) < 0 &&
            ('\x15' < *(char *)(iGpffff86b4 + iVar2 * 0x4f0 + 0xb8))) &&
           (*(char *)(iGpffff86b4 + iVar2 * 0x4f0 + 0xb8) < '\'')))))) {
        if (((*(byte *)(param_5 + 0xb) >> 4 == 1) &&
            ((long)((ulong)*(byte *)(param_5 + 0xb) << 0x3c) < 0)) &&
           (*(char *)(param_5 + 10) == '(')) {
          if (*(short *)(iGpffff86b4 + iVar2 * 0x4f0 + 0x124) < 1) {
LAB_005ad878:
            auStack_280[iVar5] = (short)lVar4;
            strcpy(auStack_2280 + iVar5 * 0x20,
                            *(undefined4 *)(iGpffff86b4 + iVar2 * 0x4f0 + 0x11c));
            if (*(short *)(iGpffff86b4 + iVar2 * 0x4f0 + 0x13a) != -1) {
              strcat(auStack_2280 + iVar5 * 0x20,
                              *(undefined4 *)
                               (iRam0040ab24 + *(short *)(iGpffff86b4 + iVar2 * 0x4f0 + 0x13a) * 4))
              ;
            }
            auStack_2380[iVar5] = 0;
            if (((ulong)*(byte *)(iStack_30 + 4) & 0x7f) >> 5 == 1) {
              EffectCodeFunc__FiiP6EFFTBLfP8ECResultPfP11BtlChrParambb(0x3f800000,lVar4,uVar3,auStack_23e0,0,&fStack_74,
                              iGpffff86b4 + iVar2 * 0x4f0 + 0xb0,0,0);
              if (0.0 < fStack_74) {
                auStack_2380[iVar5] = 1;
              }
            }
            else {
              auStack_2380[iVar5] = 1;
            }
            iVar5 = iVar5 + 1;
          }
        }
        else if (0 < *(short *)(iGpffff86b4 + iVar2 * 0x4f0 + 0x124)) goto LAB_005ad878;
      }
      lVar4 = (long)(iVar2 + 1);
    }
  }
  if ((long)((ulong)*(byte *)(iStack_70 + 0x25) << 0x3c) < 0) {
    CreateMenu1__7BtlMenuFiiiiPsPcPcbb
              (iStack_70,uStack_60,uStack_20,uStack_10,iVar5,auStack_280,auStack_2280,auStack_2380);
  }
  else {
    CreateMenu1__7BtlMenuFiiiiPsPcPcbb
              (iStack_70,uStack_60,uStack_20,uStack_10,iVar5,auStack_280,auStack_2280,auStack_2380);
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005adae0  SetDamageTypeMenu__7BtlMenuFiii
 * C++: BtlMenu::SetDamageTypeMenu(int, int, int)
 * size: 0x184 bytes
 * --------------------------------------------------------------------------- */
void SetDamageTypeMenu__7BtlMenuFiii
               (undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4)

{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined1 auStack_2340 [256];
  undefined1 auStack_2240 [8192];
  undefined2 auStack_240 [256];
  undefined4 uStack_40;
  undefined4 uStack_30;
  int iStack_20;
  undefined4 uStack_10;
  
  iVar2 = 0;
  iStack_20 = param_3;
  if (param_3 == -1) {
    cVar1 = *(char *)(iGpffff86b4 +
                      (*(char *)(iGpffff86b4 + 0x2c) * 0x50 - (int)*(char *)(iGpffff86b4 + 0x2c)) *
                      0x10 + 0x3cc);
    if (cVar1 == '\x03') {
      iStack_20 = 3;
    }
    else if (cVar1 == '\x02') {
      iStack_20 = 2;
    }
    else if (cVar1 == '\x01') {
      iStack_20 = 1;
    }
    else {
      iStack_20 = 0;
    }
  }
  uStack_40 = param_1;
  uStack_30 = param_2;
  uStack_10 = param_4;
  for (iVar3 = 0; iVar3 < 4; iVar3 = iVar3 + 1) {
    auStack_240[iVar2] = (short)iVar3;
    strcpy(auStack_2240 + iVar2 * 0x20,*(undefined4 *)(iRam0040ab34 + iVar3 * 4));
    auStack_2340[iVar2] = 1;
    iVar2 = iVar2 + 1;
  }
  CreateMenu1__7BtlMenuFiiiiPsPcPcbb
            (uStack_40,uStack_30,iStack_20,uStack_10,iVar2,auStack_240,auStack_2240,auStack_2340);
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005adc70  SetMainMenu__7BtlMenuFiiii
 * C++: BtlMenu::SetMainMenu(int, int, int, int)
 * size: 0xd464 bytes
 * --------------------------------------------------------------------------- */
void SetMainMenu__7BtlMenuFiiii(uint param_1,int param_2,uint param_3,int param_4,int param_5)

{
  char cVar1;
  short sVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  undefined8 uVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int aiStack_4a0 [32];
  int aiStack_420 [32];
  int aiStack_3a0 [32];
  int aiStack_320 [32];
  undefined1 auStack_2a0 [48];
  int aiStack_270 [32];
  int iStack_1f0;
  float fStack_1ec;
  int iStack_1e8;
  float fStack_1e4;
  float fStack_1e0;
  int iStack_1dc;
  undefined4 uStack_1d8;
  undefined4 uStack_1d4;
  undefined4 uStack_1d0;
  undefined4 uStack_1cc;
  undefined4 uStack_1c8;
  undefined4 uStack_1c4;
  int iStack_1c0;
  int iStack_1bc;
  int iStack_1b8;
  int iStack_1b4;
  int iStack_1b0;
  int iStack_1ac;
  int iStack_1a8;
  int iStack_1a4;
  int iStack_1a0;
  int iStack_19c;
  int iStack_198;
  int iStack_194;
  int iStack_190;
  int iStack_18c;
  int iStack_188;
  int iStack_184;
  uint uStack_180;
  int iStack_17c;
  int iStack_178;
  int iStack_174;
  undefined4 uStack_170;
  int iStack_16c;
  undefined4 uStack_168;
  int iStack_164;
  undefined4 uStack_160;
  uint uStack_15c;
  int iStack_158;
  int iStack_154;
  int iStack_150;
  uint uStack_14c;
  int iStack_148;
  uint uStack_144;
  int iStack_140;
  uint uStack_13c;
  int iStack_138;
  int iStack_134;
  uint uStack_130;
  int iStack_12c;
  int iStack_128;
  int iStack_124;
  int iStack_120;
  int iStack_11c;
  uint uStack_118;
  int iStack_114;
  int iStack_110;
  int iStack_10c;
  undefined4 uStack_108;
  int iStack_104;
  int iStack_100;
  undefined4 uStack_fc;
  int iStack_f8;
  int iStack_f4;
  int iStack_f0;
  int iStack_ec;
  uint uStack_e8;
  int iStack_e4;
  uint uStack_e0;
  int iStack_dc;
  uint uStack_d8;
  int iStack_d4;
  int iStack_d0;
  uint uStack_cc;
  int iStack_c8;
  int iStack_c4;
  ushort *puStack_c0;
  ushort *puStack_bc;
  uint uStack_b8;
  int iStack_b4;
  float fStack_b0;
  float fStack_ac;
  float fStack_a8;
  int iStack_a4;
  undefined4 uStack_a0;
  int iStack_9c;
  int iStack_98;
  uint uStack_94;
  uint uStack_90;
  uint uStack_8c;
  short sStack_88;
  short sStack_86;
  short sStack_84;
  short sStack_82;
  short sStack_80;
  short sStack_7e;
  short sStack_7c;
  short sStack_7a;
  short sStack_78;
  short sStack_76;
  short sStack_74;
  short sStack_72;
  short sStack_70;
  short sStack_6e;
  short sStack_6c;
  short sStack_6a;
  short sStack_68;
  short sStack_66;
  short sStack_64;
  short sStack_62;
  undefined2 uStack_60;
  undefined2 uStack_5e;
  undefined2 uStack_5c;
  undefined2 uStack_5a;
  short sStack_58;
  short sStack_56;
  short sStack_54;
  short sStack_52;
  uint uStack_50;
  int iStack_40;
  uint uStack_30;
  int iStack_20;
  int iStack_10;
  
  iStack_98 = 0;
  iStack_9c = 0;
  uStack_50 = param_1;
  iStack_40 = param_2;
  uStack_30 = param_3;
  iStack_20 = param_4;
  iStack_10 = param_5;
  iStack_b4 = GetRegDat__9RegDatApiFiii(0x3a,*(undefined4 *)
                                    ((int)pCGpffff86b4 +
                                    (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10
                                    + 0x55c),0xffffffffffffffff);
  if (*(short *)(uStack_50 + iStack_40 * 0x16c + 0x32) == 0) {
    iStack_98 = 1;
    *(undefined2 *)(uStack_50 + iStack_40 * 0x16c + 0x32) = 1;
    *(undefined2 *)(uStack_50 + iStack_40 * 0x16c + 0x34) = 0;
    *(undefined2 *)(uStack_50 + iStack_40 * 0x16c + 0x36) = 0;
    *(undefined4 *)(uStack_50 + iStack_40 * 0x16c + 0x38) = 0;
    *(undefined2 *)(uStack_50 + iStack_40 * 0x16c + 0x90) = 8;
    AddOT__7MenuObjFv(uStack_50 + iStack_40 * 0x16c + 0x7c);
    iVar12 = uStack_50 + iStack_40 * 0x16c;
    *(byte *)(iVar12 + 0x30) = *(byte *)(iVar12 + 0x30) & 0xfb | 4;
    Create__10MenuWindowFUcUcffff(*pfRam0040ab1c,pfRam0040ab1c[1],pfRam0040ab1c[2],pfRam0040ab1c[3],
                    uStack_50 + iStack_40 * 0x16c + 0x7c,0,1);
    *(undefined4 *)(uStack_50 + iStack_40 * 0x16c + 0x178) = 3;
    iVar12 = uStack_50 + iStack_40 * 0x16c;
    *(byte *)(iVar12 + 0x30) = *(byte *)(iVar12 + 0x30) & 0xf7 | 8;
    if ((*(byte *)((int)pCGpffff86b4 +
                  (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb4) & 1) == 0
       ) {
      puStack_bc = (ushort *)
                   GetRegDat__9RegDatApiFiii(0x2b,*(undefined2 *)
                                         ((int)pCGpffff86b4 +
                                         (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) *
                                         0x10 + 0x120),0xffffffffffffffff);
      puStack_c0 = puStack_bc;
      if ((*(byte *)(ourBtlSaveDat +
                     *(short *)((int)pCGpffff86b4 +
                               (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 +
                               0x120) * 0xc0 + 0x9d) & 1) == 0) {
        puStack_c0 = puStack_bc +
                     ((uint)(((ulong)*(byte *)(ourBtlSaveDat +
                                               *(short *)((int)pCGpffff86b4 +
                                                         (pCGpffff86b4->cActor * 0x50 -
                                                         (int)pCGpffff86b4->cActor) * 0x10 + 0x120)
                                               * 0xc0 + 0x9c) << 0x3a) >> 0x3d) - 1) * 0x10;
      }
      uStack_b8 = (uint)*puStack_c0;
    }
    else {
      uStack_b8 = (uint)*(byte *)(iStack_b4 + 1);
    }
    switch(*(undefined1 *)(iStack_b4 + 2)) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
      *(undefined2 *)(uStack_50 + 0xb40) = 1;
      *(undefined1 *)(uStack_50 + 0xb42) = 1;
      break;
    case 8:
    case 9:
    case 10:
    case 0xb:
    case 0xc:
    case 0xd:
    case 0xe:
    case 0xf:
    case 0x28:
    case 0x29:
    case 0x2a:
    case 0x2b:
    case 0x2c:
    case 0x2d:
    case 0x2e:
    case 0x2f:
    case 0x40:
    case 0x41:
    case 0x42:
    case 0x43:
    case 0x44:
    case 0x45:
    case 0x46:
    case 0x47:
      *(undefined2 *)(uStack_50 + 0xb40) = 2;
      *(undefined1 *)(uStack_50 + 0xb42) = 1;
      break;
    case 0x10:
    case 0x11:
    case 0x12:
    case 0x13:
    case 0x14:
    case 0x15:
    case 0x16:
    case 0x17:
    case 0x30:
    case 0x31:
    case 0x32:
    case 0x33:
    case 0x34:
    case 0x35:
    case 0x36:
    case 0x37:
    case 0x48:
    case 0x49:
    case 0x4a:
    case 0x4b:
    case 0x4c:
    case 0x4d:
    case 0x4e:
    case 0x4f:
      *(undefined2 *)(uStack_50 + 0xb40) = 4;
      *(undefined1 *)(uStack_50 + 0xb42) = 1;
      break;
    case 0x18:
    case 0x19:
    case 0x1a:
    case 0x1b:
    case 0x1c:
    case 0x1d:
    case 0x1e:
    case 0x1f:
    case 0x38:
    case 0x39:
    case 0x3a:
    case 0x3b:
    case 0x3c:
    case 0x3d:
    case 0x3e:
    case 0x3f:
    case 0x50:
    case 0x51:
    case 0x52:
    case 0x53:
    case 0x54:
    case 0x55:
    case 0x56:
    case 0x57:
      *(undefined2 *)(uStack_50 + 0xb40) = 8;
      *(undefined1 *)(uStack_50 + 0xb42) = 1;
      break;
    case 0x20:
    case 0x21:
    case 0x22:
    case 0x23:
    case 0x24:
    case 0x25:
    case 0x26:
    case 0x27:
      *(undefined2 *)(uStack_50 + 0xb40) = 0xe;
      *(undefined1 *)(uStack_50 + 0xb42) = 3;
      break;
    case 0x58:
    case 0x59:
    case 0x5a:
    case 0x5b:
    case 0x5c:
    case 0x5d:
    case 0x5e:
    case 0x5f:
      *(undefined2 *)(uStack_50 + 0xb40) = 0xf;
      *(undefined1 *)(uStack_50 + 0xb42) = 4;
      break;
    case 0x60:
    case 0x61:
    case 0x62:
    case 99:
    case 100:
    case 0x65:
    case 0x66:
    case 0x67:
    case 0x78:
    case 0x79:
    case 0x7a:
    case 0x7b:
    case 0x7c:
    case 0x7d:
    case 0x7e:
    case 0x7f:
      *(undefined2 *)(uStack_50 + 0xb40) = 3;
      *(undefined1 *)(uStack_50 + 0xb42) = 2;
      break;
    case 0x68:
    case 0x69:
    case 0x6a:
    case 0x6b:
    case 0x6c:
    case 0x6d:
    case 0x6e:
    case 0x6f:
    case 0x80:
    case 0x81:
    case 0x82:
    case 0x83:
    case 0x84:
    case 0x85:
    case 0x86:
    case 0x87:
      *(undefined2 *)(uStack_50 + 0xb40) = 5;
      *(undefined1 *)(uStack_50 + 0xb42) = 2;
      break;
    case 0x70:
    case 0x71:
    case 0x72:
    case 0x73:
    case 0x74:
    case 0x75:
    case 0x76:
    case 0x77:
    case 0x88:
    case 0x89:
    case 0x8a:
    case 0x8b:
    case 0x8c:
    case 0x8d:
    case 0x8e:
    case 0x8f:
      *(undefined2 *)(uStack_50 + 0xb40) = 9;
      *(undefined1 *)(uStack_50 + 0xb42) = 2;
    }
    cVar1 = *(char *)((int)pCGpffff86b4 +
                     (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x3cc);
    if (cVar1 == '\x03') {
      *(undefined1 *)(uStack_50 + 0xb43) = 3;
    }
    else if (cVar1 == '\x02') {
      *(undefined1 *)(uStack_50 + 0xb43) = 2;
    }
    else if (cVar1 == '\x01') {
      *(undefined1 *)(uStack_50 + 0xb43) = 1;
    }
    else {
      *(undefined1 *)(uStack_50 + 0xb43) = 0;
    }
    if (*(int *)(uStack_50 + iStack_40 * 0x16c + 0x140) == 0) {
      iStack_1bc = __nw__FUi(0x84);
      if (iStack_1bc != 0) {
        iStack_1bc = __ct__10ScrollMarkFv(iStack_1bc);
      }
      *(int *)(uStack_50 + iStack_40 * 0x16c + 0x140) = iStack_1bc;
      iStack_188 = *(int *)(uStack_50 + iStack_40 * 0x16c + 0x140);
      *(undefined2 *)(iStack_188 + 0x14) = 0x10;
      Create__10ScrollMarkFUcP10MenuWindowUc(*(undefined4 *)(uStack_50 + iStack_40 * 0x16c + 0x140),0xc,0,0);
      AddPriority__12MenuObjTableFP7MenuObj(uStack_50 + iStack_40 * 0x16c + 0x94,
                      *(undefined4 *)(uStack_50 + iStack_40 * 0x16c + 0x140));
    }
  }
  else {
    uStack_30 = *(uint *)(uStack_50 + iStack_40 * 0x16c + 0x16c);
    iStack_20 = (int)*(char *)(uStack_50 + 0xb43);
    if (((*(short *)(uStack_50 + iStack_40 * 0x16c + 0x32) != 2) &&
        (*(short *)(uStack_50 + iStack_40 * 0x16c + 0x32) != 1)) &&
       (*(short *)(uStack_50 + iStack_40 * 0x16c + 0x32) != 5)) {
      SetWindowMove__7BtlMenuFii(uStack_50,iStack_40,0);
      SetMark__10ScrollMarkFUc(*(undefined4 *)(uStack_50 + iStack_40 * 0x16c + 0x140),0);
      if (4 < *(int *)(uStack_50 + iStack_40 * 0x16c + 0x170)) {
        if (*(int *)(uStack_50 + 0xb30) == 0) {
          iStack_1c0 = __nw__FUi(0x84);
          if (iStack_1c0 != 0) {
            iStack_1c0 = __ct__10ScrollMarkFv(iStack_1c0);
          }
          *(int *)(uStack_50 + 0xb30) = iStack_1c0;
          Create__10ScrollMarkFUcP10MenuWindowUc(*(undefined4 *)(uStack_50 + 0xb30),3,0,0);
          iStack_18c = *(int *)(uStack_50 + 0xb30);
          *(undefined2 *)(iStack_18c + 0x14) = 0x10;
          AddOT__7MenuObjFv(*(undefined4 *)(uStack_50 + 0xb30));
          *(byte *)(uStack_50 + 0x25) = *(byte *)(uStack_50 + 0x25) & 0xfd | 2;
          SetArea__10ScrollMarkFUcffff(*pfRam0040ab1c + 48.0,
                          *(undefined4 *)(uStack_50 + iStack_40 * 0x16c + 0x17c),
                          pfRam0040ab1c[2] - 80.0,
                          *(undefined4 *)(uStack_50 + iStack_40 * 0x16c + 0x180),
                          *(undefined4 *)(uStack_50 + 0xb30),3);
          *(undefined2 *)(uStack_50 + 0xa32) = 1;
        }
        uVar5 = uStack_30;
        if ((int)uStack_30 < 0) {
          uVar5 = uStack_30 + 3;
        }
        iVar12 = ((int)uVar5 >> 2) * 4;
        uStack_8c = (uint)(0 < iVar12);
        if (iVar12 + 4 < *(int *)(uStack_50 + iStack_40 * 0x16c + 0x170)) {
          uStack_8c = uStack_8c | 2;
        }
        SetMark__10ScrollMarkFUc(*(undefined4 *)(uStack_50 + 0xb30),uStack_8c);
        return;
      }
      if (*(short *)(uStack_50 + 0xa32) != 1) {
        return;
      }
      *(undefined2 *)(uStack_50 + 0xa32) = 2;
      return;
    }
  }
  if (iStack_98 == 0) {
    ClearImage__8FontDrawFv(uStack_50 + iStack_40 * 0x16c + 0x3c);
  }
  else {
    Create__8FontDrawF6GS_PSMUsUsUcUiP10ClutRaster(uStack_50 + iStack_40 * 0x16c + 0x3c,0x2c,0x100,0x80,1,0,0);
    iVar12 = uStack_50 + iStack_40 * 0x16c;
    *(byte *)(iVar12 + 0x30) = *(byte *)(iVar12 + 0x30) & 0xfd | 2;
    *(undefined2 *)(uStack_50 + iStack_40 * 0x16c + 0x50) = 7;
    AddPriority__12MenuObjTableFP7MenuObj(uStack_50 + iStack_40 * 0x16c + 0x94,uStack_50 + iStack_40 * 0x16c + 0x3c);
    if (((ulong)*(ushort *)(uStack_50 + iStack_40 * 0x16c + 0x30) & 0xfff) >> 4 == 0) {
      uVar6 = __nwa__FUi(0x410);
      uVar3 = __construct_new_array(uVar6,0x27bfd0,0x27c030,0x80,8);
      *(undefined4 *)(uStack_50 + iStack_40 * 0x16c + 0x130) = uVar3;
      iVar12 = uStack_50 + iStack_40 * 0x16c;
      *(ushort *)(iVar12 + 0x30) = *(ushort *)(iVar12 + 0x30) & 0xf00f | 0x80;
    }
    iVar12 = *(int *)(uStack_50 + iStack_40 * 0x16c + 0x130);
    iVar13 = 0;
    for (iVar4 = 0; iVar4 < 4; iVar4 = iVar4 + 1) {
      Create__8MenuTextFUcUc(iVar12 + iVar13 * 0x80,0,2);
      *(undefined2 *)(iVar12 + iVar13 * 0x80 + 0x14) = 8;
      *(undefined1 *)(iVar12 + iVar13 * 0x80 + 0x5a) = 1;
      *(undefined1 *)(iVar12 + iVar13 * 0x80 + 0x5b) = 0;
      *(undefined2 *)(iVar12 + iVar13 * 0x80 + 0x1c) = 0;
      *(short *)(iVar12 + iVar13 * 0x80 + 0x1e) = (short)iVar4;
      AddPlace__10MenuWindowFP9MenuPlace(uStack_50 + iStack_40 * 0x16c + 0x7c,iVar12 + iVar13 * 0x80);
      iVar14 = iVar13 + 1;
      Create__8MenuTextFUcUc(iVar12 + iVar14 * 0x80,0,2);
      *(undefined2 *)(iVar12 + iVar14 * 0x80 + 0x14) = 8;
      *(undefined1 *)(iVar12 + iVar14 * 0x80 + 0x5a) = 1;
      *(undefined1 *)(iVar12 + iVar14 * 0x80 + 0x5b) = 0;
      *(undefined2 *)(iVar12 + iVar14 * 0x80 + 0x1c) = 1;
      *(short *)(iVar12 + iVar14 * 0x80 + 0x1e) = (short)iVar4;
      AddPlace__10MenuWindowFP9MenuPlace(uStack_50 + iStack_40 * 0x16c + 0x7c,iVar12 + iVar14 * 0x80);
      iVar13 = iVar13 + 2;
    }
    uVar6 = __nwa__FUi(0xa0);
    uVar3 = __construct_new_array(uVar6,0x277820,0x277890,0x30,3);
    *(undefined4 *)(uStack_50 + iStack_40 * 0x16c + 0x138) = uVar3;
    iStack_190 = *(int *)&pCGpffff86b4->field_0x4234;
    uStack_1c8 = *(undefined4 *)(iStack_190 + (uint)*(ushort *)(iStack_190 + 10) * 4 + 0xc);
    uStack_1c4 = uStack_1c8;
    uVar6 = GetTex0__6JRCTexFb(*(undefined4 *)&pCGpffff86b4->field_0x4234,0);
    Create__11SendOnLocalFP4_QWDUl(*(undefined4 *)(uStack_50 + iStack_40 * 0x16c + 0x138),uStack_1c8,uVar6);
    iStack_194 = *(int *)(uStack_50 + iStack_40 * 0x16c + 0x138);
    *(undefined2 *)(iStack_194 + 0x14) = 1;
    AddPriority__12MenuObjTableFP7MenuObj(uStack_50 + iStack_40 * 0x16c + 0x94,
                    *(undefined4 *)(uStack_50 + iStack_40 * 0x16c + 0x138));
    iStack_198 = *(int *)&pCGpffff86b4->field_0x4238;
    uStack_1d0 = *(undefined4 *)(iStack_198 + (uint)*(ushort *)(iStack_198 + 10) * 4 + 0xc);
    uStack_1cc = uStack_1d0;
    uVar6 = GetTex0__6JRCTexFb(*(undefined4 *)&pCGpffff86b4->field_0x4238,0);
    Create__11SendOnLocalFP4_QWDUl(*(int *)(uStack_50 + iStack_40 * 0x16c + 0x138) + 0x30,uStack_1d0,uVar6);
    iVar4 = *(int *)(uStack_50 + iStack_40 * 0x16c + 0x138);
    iStack_19c = iVar4 + 0x30;
    *(undefined2 *)(iVar4 + 0x44) = 3;
    AddPriority__12MenuObjTableFP7MenuObj(uStack_50 + iStack_40 * 0x16c + 0x94,
                    *(int *)(uStack_50 + iStack_40 * 0x16c + 0x138) + 0x30);
    iStack_1a0 = *(int *)&pCGpffff86b4->field_0x4248;
    uStack_1d8 = *(undefined4 *)(iStack_1a0 + (uint)*(ushort *)(iStack_1a0 + 10) * 4 + 0xc);
    uStack_1d4 = uStack_1d8;
    uVar6 = GetTex0__6JRCTexFb(*(undefined4 *)&pCGpffff86b4->field_0x4248,0);
    Create__11SendOnLocalFP4_QWDUl(*(int *)(uStack_50 + iStack_40 * 0x16c + 0x138) + 0x60,uStack_1d8,uVar6);
    iVar4 = *(int *)(uStack_50 + iStack_40 * 0x16c + 0x138);
    iStack_1a4 = iVar4 + 0x60;
    *(undefined2 *)(iVar4 + 0x74) = 5;
    AddPriority__12MenuObjTableFP7MenuObj(uStack_50 + iStack_40 * 0x16c + 0x94,
                    *(int *)(uStack_50 + iStack_40 * 0x16c + 0x138) + 0x60);
    if (*(int *)(uStack_50 + iStack_40 * 0x16c + 0x13c) == 0) {
      uVar6 = __nwa__FUi(0x850);
      uVar3 = __construct_new_array(uVar6,0x266140,0x2661a0,0x60,0x16);
      *(undefined4 *)(uStack_50 + iStack_40 * 0x16c + 0x13c) = uVar3;
    }
    iVar4 = *(int *)(uStack_50 + iStack_40 * 0x16c + 0x13c);
    iVar13 = 0;
    for (uStack_8c = 0; (int)uStack_8c < 4; uStack_8c = uStack_8c + 1) {
      Create__10MenuSpriteFUc(iVar4 + iVar13 * 0x60,0);
      iVar14 = iVar4 + iVar13 * 0x60;
      *(byte *)(iVar14 + 0x21) = *(byte *)(iVar14 + 0x21) & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv(iVar4 + iVar13 * 0x60);
      *(undefined2 *)(iVar4 + iVar13 * 0x60 + 0x14) = 4;
      uVar6 = (**(code **)(*(int *)(iVar4 + iVar13 * 0x60 + 8) + 0x24))
                        (0,(float)(int)uStack_8c * 26.0);
      SetUV__10MenuSpriteFUsUsUsUs(iVar4 + iVar13 * 0x60,1,1,0xdd,0x1c,uVar6);
      (**(code **)(*(int *)(iVar4 + iVar13 * 0x60 + 8) + 0x28))(0x435c0000,0x41d80000);
      iVar14 = iVar4 + iVar13 * 0x60;
      (**(code **)(*(int *)(iVar14 + 8) + 0x30))(iVar14,0x80,0x80,0x80);
      iVar14 = iVar4 + iVar13 * 0x60;
      (**(code **)(*(int *)(iVar14 + 8) + 0x2c))(iVar14,0x80);
      iVar14 = iVar4 + iVar13 * 0x60;
      *(byte *)(iVar14 + 0x21) = *(byte *)(iVar14 + 0x21) & 0xfd;
      iVar14 = iVar4 + iVar13 * 0x60;
      *(byte *)(iVar14 + 0x12) = *(byte *)(iVar14 + 0x12) & 0xfe | 1;
      uStack_5a = (undefined2)uStack_8c;
      *(undefined2 *)(iVar4 + iVar13 * 0x60 + 0x1c) = 2;
      *(undefined2 *)(iVar4 + iVar13 * 0x60 + 0x1e) = uStack_5a;
      AddPlace__10MenuWindowFP9MenuPlace(uStack_50 + iStack_40 * 0x16c + 0x7c,iVar4 + iVar13 * 0x60);
      iVar13 = iVar13 + 1;
    }
    Create__10MenuSpriteFUc(iVar4 + iVar13 * 0x60,0);
    iVar14 = iVar4 + iVar13 * 0x60;
    *(byte *)(iVar14 + 0x21) = *(byte *)(iVar14 + 0x21) & 0xbf | 0x40;
    UpdateEnv__7MenuObjFv(iVar4 + iVar13 * 0x60);
    *(undefined2 *)(iVar4 + iVar13 * 0x60 + 0x14) = 2;
    (**(code **)(*(int *)(iVar4 + iVar13 * 0x60 + 8) + 0x24))(0,0);
    (**(code **)(*(int *)(iVar4 + iVar13 * 0x60 + 8) + 0x28))(0x437f0000,0x41c00000);
    SetUV__10MenuSpriteFUsUsUsUs(iVar4 + iVar13 * 0x60,0,0,0xff,0x18);
    iVar14 = iVar4 + iVar13 * 0x60;
    (**(code **)(*(int *)(iVar14 + 8) + 0x30))(iVar14,0x80,0x80,0x80);
    iVar14 = iVar4 + iVar13 * 0x60;
    (**(code **)(*(int *)(iVar14 + 8) + 0x2c))(iVar14,0);
    iVar14 = iVar4 + iVar13 * 0x60;
    *(byte *)(iVar14 + 0x21) = *(byte *)(iVar14 + 0x21) & 0xfd;
    iVar14 = iVar4 + iVar13 * 0x60;
    *(byte *)(iVar14 + 0x12) = *(byte *)(iVar14 + 0x12) & 0xfe | 1;
    *(undefined2 *)(iVar4 + iVar13 * 0x60 + 0x1c) = 2;
    *(undefined2 *)(iVar4 + iVar13 * 0x60 + 0x1e) = 4;
    AddPlace__10MenuWindowFP9MenuPlace(uStack_50 + iStack_40 * 0x16c + 0x7c,iVar4 + iVar13 * 0x60);
    for (uStack_8c = 0; iVar13 = iVar13 + 1, (int)uStack_8c < 0x10; uStack_8c = uStack_8c + 1) {
      Create__10MenuSpriteFUc(iVar4 + iVar13 * 0x60,0);
      iVar14 = iVar4 + iVar13 * 0x60;
      *(byte *)(iVar14 + 0x21) = *(byte *)(iVar14 + 0x21) & 0xbf | 0x40;
      UpdateEnv__7MenuObjFv(iVar4 + iVar13 * 0x60);
      *(undefined2 *)(iVar4 + iVar13 * 0x60 + 0x14) = 4;
      (**(code **)(*(int *)(iVar4 + iVar13 * 0x60 + 8) + 0x24))
                ((float)(int)(uStack_8c << 4) + 16.0,0);
      SetUV__10MenuSpriteFUsUsUsUs(iVar4 + iVar13 * 0x60,0x13,0x53,0x24,0x5c);
      (**(code **)(*(int *)(iVar4 + iVar13 * 0x60 + 8) + 0x28))(0x41880000,0x41100000);
      iVar14 = iVar4 + iVar13 * 0x60;
      (**(code **)(*(int *)(iVar14 + 8) + 0x30))(iVar14,0x80,0x80,0x80);
      iVar14 = iVar4 + iVar13 * 0x60;
      (**(code **)(*(int *)(iVar14 + 8) + 0x2c))(iVar14,0x80);
      iVar14 = iVar4 + iVar13 * 0x60;
      *(byte *)(iVar14 + 0x21) = *(byte *)(iVar14 + 0x21) & 0xfd;
      iVar14 = iVar4 + iVar13 * 0x60;
      *(byte *)(iVar14 + 0x12) = *(byte *)(iVar14 + 0x12) & 0xfe;
      SetRendering__7MenuObjFUc(iVar4 + iVar13 * 0x60,0);
      uStack_5c = (undefined2)uStack_8c;
      *(undefined2 *)(iVar4 + iVar13 * 0x60 + 0x1c) = uStack_5c;
      *(undefined2 *)(iVar4 + iVar13 * 0x60 + 0x1e) = 5;
      AddPlace__10MenuWindowFP9MenuPlace(uStack_50 + iStack_40 * 0x16c + 0x7c,iVar4 + iVar13 * 0x60);
    }
    Create__10MenuSpriteFUc(iVar4 + iVar13 * 0x60,0);
    iVar14 = iVar4 + iVar13 * 0x60;
    *(byte *)(iVar14 + 0x21) = *(byte *)(iVar14 + 0x21) & 0xbf | 0x40;
    UpdateEnv__7MenuObjFv(iVar4 + iVar13 * 0x60);
    *(undefined2 *)(iVar4 + iVar13 * 0x60 + 0x14) = 6;
    (**(code **)(*(int *)(iVar4 + iVar13 * 0x60 + 8) + 0x24))(0,0);
    (**(code **)(*(int *)(iVar4 + iVar13 * 0x60 + 8) + 0x28))(0x41900000,0x41b00000);
    SetUV__10MenuSpriteFUsUsUsUs(iVar4 + iVar13 * 0x60,0,0,0x12,0x16);
    iVar14 = iVar4 + iVar13 * 0x60;
    (**(code **)(*(int *)(iVar14 + 8) + 0x30))(iVar14,0x80,0x80,0x80);
    iVar14 = iVar4 + iVar13 * 0x60;
    (**(code **)(*(int *)(iVar14 + 8) + 0x2c))(iVar14,0x80);
    iVar14 = iVar4 + iVar13 * 0x60;
    *(byte *)(iVar14 + 0x21) = *(byte *)(iVar14 + 0x21) & 0xfd;
    iVar14 = iVar4 + iVar13 * 0x60;
    *(byte *)(iVar14 + 0x12) = *(byte *)(iVar14 + 0x12) & 0xfe;
    SetRendering__7MenuObjFUc(iVar4 + iVar13 * 0x60,0);
    *(undefined2 *)(iVar4 + iVar13 * 0x60 + 0x1c) = 3;
    *(undefined2 *)(iVar4 + iVar13 * 0x60 + 0x1e) = 6;
    AddPlace__10MenuWindowFP9MenuPlace(uStack_50 + iStack_40 * 0x16c + 0x7c,iVar4 + iVar13 * 0x60);
    uStack_60 = *(undefined2 *)(iVar12 + 0x48);
    CreateScroll__10MenuWindowFUissffUc(pfRam0040ab1c[2],0x43800000,uStack_50 + iStack_40 * 0x16c + 0x7c,uStack_60,0x20,
                    0x10,0);
    *(undefined4 *)(*(int *)(uStack_50 + iStack_40 * 0x16c + 0xbc) + 0x38) = 0;
    SetScroll__10MenuWindowFss(uStack_50 + iStack_40 * 0x16c + 0x7c,0,0);
  }
  for (uStack_8c = 0; (int)uStack_8c < 0x20; uStack_8c = uStack_8c + 1) {
    if (((*(char *)((int)pCGpffff86b4 +
                   uStack_8c * 0xc +
                   (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x1bc) == 'G')
        && (((ulong)*(byte *)((int)pCGpffff86b4 +
                             uStack_8c * 0xc +
                             (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 +
                             0x1b9) & 0x1f) >> 2 == 0)) &&
       ((*(uint *)((int)pCGpffff86b4 +
                  uStack_8c * 0xc + (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10
                  + 0x1c0) & 8) != 0)) {
      iStack_9c = 1;
    }
  }
  uStack_8c = (uint)*(char *)(uStack_50 + 0xb43);
  if (((uint)*(ushort *)(uStack_50 + 0xb40) & 1 << (uStack_8c & 0x1f)) == 0) {
    for (uStack_8c = 0;
        ((int)uStack_8c < 4 &&
        (((uint)*(ushort *)(uStack_50 + 0xb40) & 1 << (uStack_8c & 0x1f)) == 0));
        uStack_8c = uStack_8c + 1) {
    }
    *(char *)(uStack_50 + 0xb43) = (char)uStack_8c;
  }
  if (uStack_8c == 3) {
    aiStack_270[0] = 4;
  }
  else if (uStack_8c == 2) {
    aiStack_270[0] = 3;
  }
  else if (uStack_8c == 1) {
    aiStack_270[0] = 2;
  }
  else if (uStack_8c == 0) {
    aiStack_270[0] = 1;
  }
  else {
    aiStack_270[uStack_8c] = 0;
  }
  iVar12 = 1;
  if ((((*(byte *)((int)pCGpffff86b4 +
                  (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb4) & 1) == 0
       ) && (pCGpffff86b4->nComboCnt != 0)) && (iStack_9c == 0)) {
    CheckComboSkill__7CBattleFiPiPi
              (pCGpffff86b4,(int)pCGpffff86b4->cActor,(int *)&uStack_8c,(int *)&uStack_90);
    if (*(short *)((int)pCGpffff86b4 +
                  (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x120) == 6) {
      iStack_c4 = GetRegDat__9RegDatApiFiii(0x40,0,0xffffffffffffffff);
      if (-1 < (long)((ulong)*(byte *)(iStack_c4 + *(int *)(ourBtlSocket + 0x698) * 0x10 + 4) << 0x3e
                     )) {
        uStack_8c = 0;
      }
    }
    iVar12 = 1;
    if (uStack_8c != 0) {
      aiStack_270[1] = 5;
      iVar12 = 2;
    }
  }
  uStack_8c = 0x7fff;
  if ((((*(byte *)((int)pCGpffff86b4 +
                  (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb4) & 1) == 0
       ) && (*(short *)((int)pCGpffff86b4 +
                       (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x120) ==
             0)) && ((*(uint *)(ourBtlSaveDat + 0xd4c) & 0x7fff) != 0)) {
    aiStack_270[iVar12] = 0xc;
    iVar12 = iVar12 + 1;
  }
  if (((*(byte *)((int)pCGpffff86b4 +
                 (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb4) & 1) == 0)
     && (*(short *)((int)pCGpffff86b4 +
                   (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x120) == 1))
  {
    uStack_94 = 0x1000;
    aiStack_270[iVar12] = 0xd;
    iVar12 = iVar12 + 1;
  }
  if ((((*(byte *)((int)pCGpffff86b4 +
                  (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb4) & 1) == 0
       ) && (*(short *)((int)pCGpffff86b4 +
                       (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x120) ==
             2)) && (*(int *)(*(int *)(g_83f8 + 0xc) + 0x2fc) != 0)) {
    iStack_1dc = *(int *)(*(int *)(g_83f8 + 0xc) + 0x2fc);
    iStack_c8 = iStack_1dc;
    if (iStack_1dc != 0) {
      aiStack_270[iVar12] = 0xe;
      iVar12 = iVar12 + 1;
    }
  }
  if ((((*(byte *)((int)pCGpffff86b4 +
                  (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb4) & 1) == 0
       ) && (*(short *)((int)pCGpffff86b4 +
                       (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x120) ==
             3)) &&
     ((*(char *)(ourBtlSaveDat + 0xdab) != '\0' ||
      ((*(char *)(ourBtlSaveDat + 0xdac) != '\0' || (*(char *)(ourBtlSaveDat + 0xdad) != '\0')))))) {
    aiStack_270[iVar12] = 0xf;
    iVar12 = iVar12 + 1;
  }
  if ((((*(byte *)((int)pCGpffff86b4 +
                  (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb4) & 1) == 0
       ) && (*(short *)((int)pCGpffff86b4 +
                       (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x120) ==
             3)) && (*(char *)(ourBtlSaveDat + 0xdae) != '\0')) {
    uStack_cc = GetRegCnt__9RegDatApiFii(0x3d,0xffffffffffffffff);
    iStack_d0 = GetRegDat__9RegDatApiFiii(0x3d,0,0xffffffffffffffff);
    iStack_d4 = 0;
    for (uStack_8c = 0; uStack_8c < uStack_cc; uStack_8c = uStack_8c + 1) {
      if ((((uint)*(byte *)(ourBtlSaveDat + 0xdae) &
           1 << ((int)*(char *)(iStack_d0 + uStack_8c * 0x40 + 0x1c) & 0x1fU)) != 0) &&
         (((uint)*(byte *)(ourBtlSaveDat + 0xdae) &
          1 << ((int)*(char *)(iStack_d0 + uStack_8c * 0x40 + 0x1d) & 0x1fU)) != 0)) {
        iStack_d4 = iStack_d4 + 1;
      }
    }
    if (iStack_d4 != 0) {
      aiStack_270[iVar12] = 0x10;
      iVar12 = iVar12 + 1;
    }
  }
  if ((((*(byte *)((int)pCGpffff86b4 +
                  (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb4) & 1) == 0
       ) && ((*(byte *)((int)pCGpffff86b4 +
                       (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb1) & 1)
             == 0)) &&
     ((*(short *)((int)pCGpffff86b4 +
                 (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x120) == 4 &&
      (((*(char *)(ourBtlSaveDat + 0xe2f) != '\0' || (*(char *)(ourBtlSaveDat + 0xe30) != '\0')) ||
       (*(char *)(ourBtlSaveDat + 0xe31) != '\0')))))) {
    uStack_d8 = GetRegCnt__9RegDatApiFii(0x36,4);
    iStack_dc = 0;
    for (uStack_8c = 0; uStack_8c < uStack_d8; uStack_8c = uStack_8c + 1) {
      uVar5 = uStack_8c & 7;
      if (((int)uStack_8c < 0) && (uVar5 != 0)) {
        uVar5 = uVar5 - 8;
      }
      if (((uint)*(byte *)(ourBtlSaveDat + ((int)uStack_8c >> 3) + 0xe2f) & 1 << (uVar5 & 0x1f)) != 0)
      {
        iStack_dc = iStack_dc + 1;
      }
    }
    if (iStack_dc != 0) {
      aiStack_270[iVar12] = 0x12;
      iVar12 = iVar12 + 1;
    }
  }
  if (((*(byte *)((int)pCGpffff86b4 +
                 (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb4) & 1) == 0)
     && (*(short *)((int)pCGpffff86b4 +
                   (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x120) == 5))
  {
    uStack_e0 = GetRegCnt__9RegDatApiFii(0x36,5);
    uStack_94 = (uint)*(ushort *)(ourBtlSaveDat + 0x43e);
    iStack_e4 = 0;
    for (uStack_8c = 0; uStack_8c < uStack_e0; uStack_8c = uStack_8c + 1) {
      if (((uint)*(ushort *)(ourBtlSaveDat + 0x43e) & 1 << (uStack_8c & 0x1f)) != 0) {
        iStack_e4 = iStack_e4 + 1;
      }
    }
    if (iStack_e4 != 0) {
      aiStack_270[iVar12] = 0x13;
      iVar12 = iVar12 + 1;
    }
  }
  if ((((*(byte *)((int)pCGpffff86b4 +
                  (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb4) & 1) == 0
       ) && (*(short *)((int)pCGpffff86b4 +
                       (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x120) ==
             6)) && (*(char *)(ourBtlSaveDat + 0xe37) != '\0')) {
    uStack_e8 = GetRegCnt__9RegDatApiFii(0x36,6);
    iStack_ec = 0;
    for (uStack_8c = 0; uStack_8c < uStack_e8; uStack_8c = uStack_8c + 1) {
      if (((long)*(char *)(ourBtlSaveDat + 0xe37) & (long)(1 << (uStack_8c & 0x1f))) != 0) {
        iStack_ec = iStack_ec + 1;
      }
    }
    iStack_f0 = GetRegDat__9RegDatApiFiii(0x40,0,0xffffffffffffffff);
    if (-1 < (long)((ulong)*(byte *)(iStack_f0 + *(int *)(ourBtlSocket + 0x698) * 0x10 + 4) << 0x3e))
    {
      iStack_ec = 0;
    }
    if (iStack_ec != 0) {
      aiStack_270[iVar12] = 0x14;
      iVar12 = iVar12 + 1;
    }
  }
  if ((((*(byte *)((int)pCGpffff86b4 +
                  (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb4) & 1) == 0
       ) && (*(short *)((int)pCGpffff86b4 +
                       (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x120) ==
             7)) && ((*(uint *)(ourBtlSaveDat + 0xd4c) & 0x18000) != 0)) {
    aiStack_270[iVar12] = 0x15;
    iVar12 = iVar12 + 1;
  }
  if (((*(byte *)((int)pCGpffff86b4 +
                 (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb4) & 1) == 0)
     && (((*(short *)((int)pCGpffff86b4 +
                     (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x120) == 8
          || (*(short *)((int)pCGpffff86b4 +
                        (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x120) ==
              9)) ||
         (*(short *)((int)pCGpffff86b4 +
                    (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x120) == 10)
         ))) {
    if (*(short *)((int)pCGpffff86b4 +
                  (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x120) == 8) {
      iStack_f4 = 0x16;
    }
    else if (*(short *)((int)pCGpffff86b4 +
                       (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x120) ==
             9) {
      iStack_f4 = 0x17;
    }
    else {
      iStack_f4 = 0x18;
    }
    aiStack_270[iVar12] = iStack_f4;
    iVar12 = iVar12 + 1;
  }
  if (((*(byte *)((int)pCGpffff86b4 +
                 (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb4) & 1) == 0)
     && (*(short *)((int)pCGpffff86b4 +
                   (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x120) == 0xb)
     ) {
    aiStack_270[iVar12] = 0x19;
    iVar12 = iVar12 + 1;
  }
  if (((*(byte *)((int)pCGpffff86b4 +
                 (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb4) & 1) == 0)
     && ((*(byte *)((int)pCGpffff86b4 +
                   (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb1) & 1) !=
         0)) {
    switch(*(undefined2 *)
            ((int)pCGpffff86b4 +
            (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xba)) {
    case 0:
    case 1:
      uStack_8c = 0xc;
      break;
    case 2:
    case 3:
      uStack_8c = 0xd;
      break;
    case 4:
    case 5:
      uStack_8c = 0xe;
      break;
    case 6:
    case 7:
      uStack_8c = 0xf;
      break;
    case 8:
    case 9:
      uStack_8c = 0x10;
      break;
    case 10:
    case 0xb:
      uStack_8c = 0x11;
      break;
    case 0xc:
    case 0xd:
      uStack_8c = 0x12;
      break;
    case 0xe:
      uStack_8c = 0x13;
      break;
    case 0xf:
      uStack_8c = 0x14;
      break;
    case 0x10:
      uStack_8c = 0x15;
    }
    iStack_f8 = GetRegDat__9RegDatApiFiii(0x2c,*(undefined2 *)
                                      ((int)pCGpffff86b4 +
                                      (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) *
                                      0x10 + 0xba),0xffffffffffffffff);
    uStack_fc = GetRegDat__9RegDatApiFiii(0x36,uStack_8c,0xffffffffffffffff);
    iStack_100 = 0;
    for (uStack_8c = 0; (int)uStack_8c < 7; uStack_8c = uStack_8c + 1) {
      if ((-1 < *(short *)(iStack_f8 + uStack_8c * 2 + 8)) &&
         ((long)*(char *)(iStack_f8 + uStack_8c + 0x16) <=
          (long)(int)(*(byte *)(ourBtlSaveDat +
                                *(short *)((int)pCGpffff86b4 +
                                          (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor)
                                          * 0x10 + 0xba) + 0xd94) + 1))) {
        iStack_100 = iStack_100 + 1;
      }
    }
    if (iStack_100 != 0) {
      aiStack_270[iVar12] = 0x1a;
      iVar12 = iVar12 + 1;
    }
  }
  if ((*(byte *)((int)pCGpffff86b4 +
                (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb4) & 1) == 0)
  {
    iStack_104 = GetRegDat__9RegDatApiFiii(0x37,0,0xffffffffffffffff);
    uStack_108 = GetRegDat__9RegDatApiFiii(0x38,0,0xffffffffffffffff);
    for (uStack_8c = 0; (int)uStack_8c < 0x20; uStack_8c = uStack_8c + 1) {
      aiStack_320[uStack_8c] = 0;
    }
    iStack_10c = 0;
    for (uStack_8c = 0; (int)uStack_8c < 8; uStack_8c = uStack_8c + 1) {
      if (-1 < *(char *)(ourBtlSaveDat +
                         *(short *)((int)pCGpffff86b4 +
                                   (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10
                                   + 0x120) * 0xc0 + uStack_8c + 0x76)) {
        uStack_90 = (uint)*(char *)(ourBtlSaveDat +
                                    *(short *)((int)pCGpffff86b4 +
                                              (pCGpffff86b4->cActor * 0x50 -
                                              (int)pCGpffff86b4->cActor) * 0x10 + 0x120) * 0xc0 +
                                    uStack_8c + 0x76);
        if (-1 < *(short *)(iStack_104 + uStack_90 * 0x1c + 8)) {
          if ((*(byte *)(iStack_104 + uStack_90 * 0x1c + 6) & 1) == 0) {
LAB_005b0e40:
            for (iVar4 = 0;
                (iVar4 < iStack_10c &&
                ((long)aiStack_320[iVar4] != (long)*(short *)(iStack_104 + uStack_90 * 0x1c + 8)));
                iVar4 = iVar4 + 1) {
            }
            if (iVar4 < iStack_10c) {
              aiStack_3a0[iVar4] = aiStack_3a0[iVar4] + 1;
            }
            else {
              aiStack_320[iStack_10c] = (int)*(short *)(iStack_104 + uStack_90 * 0x1c + 8);
              aiStack_3a0[iStack_10c] = 1;
              iStack_10c = iStack_10c + 1;
            }
          }
          else if ((*(byte *)(iStack_104 + uStack_90 * 0x1c + 6) & 1) != 0) {
            uVar5 = uStack_90 & 7;
            if (((int)uStack_90 < 0) && (uVar5 != 0)) {
              uVar5 = uVar5 - 8;
            }
            if (((uint)*(byte *)(ourBtlSaveDat + (uint)*(byte *)(ourBtlSaveDat + 2) * 0x200 +
                                 ((int)uStack_90 >> 3) + 0xaae) & 1 << (uVar5 & 0x1f)) != 0)
            goto LAB_005b0e40;
          }
        }
        if (-1 < *(short *)(iStack_104 + uStack_90 * 0x1c + 10)) {
          if ((long)((ulong)*(byte *)(iStack_104 + uStack_90 * 0x1c + 6) << 0x3e) < 0) {
            if ((long)((ulong)*(byte *)(iStack_104 + uStack_90 * 0x1c + 6) << 0x3e) < 0) {
              uVar5 = uStack_90 & 7;
              if (((int)uStack_90 < 0) && (uVar5 != 0)) {
                uVar5 = uVar5 - 8;
              }
              if (((uint)*(byte *)(ourBtlSaveDat + (uint)*(byte *)(ourBtlSaveDat + 2) * 0x200 +
                                   ((int)uStack_90 >> 3) + 0xaae) & 1 << (uVar5 & 0x1f)) != 0)
              goto LAB_005b1018;
            }
          }
          else {
LAB_005b1018:
            for (iVar4 = 0;
                (iVar4 < iStack_10c &&
                ((long)aiStack_320[iVar4] != (long)*(short *)(iStack_104 + uStack_90 * 0x1c + 10)));
                iVar4 = iVar4 + 1) {
            }
            if (iVar4 < iStack_10c) {
              aiStack_3a0[iVar4] = aiStack_3a0[iVar4] + 1;
            }
            else {
              aiStack_320[iStack_10c] = (int)*(short *)(iStack_104 + uStack_90 * 0x1c + 10);
              aiStack_3a0[iStack_10c] = 1;
              iStack_10c = iStack_10c + 1;
            }
          }
        }
        if (-1 < *(short *)(iStack_104 + uStack_90 * 0x1c + 0xc)) {
          if ((long)((ulong)*(byte *)(iStack_104 + uStack_90 * 0x1c + 6) << 0x3d) < 0) {
            if ((long)((ulong)*(byte *)(iStack_104 + uStack_90 * 0x1c + 6) << 0x3d) < 0) {
              uVar5 = uStack_90 & 7;
              if (((int)uStack_90 < 0) && (uVar5 != 0)) {
                uVar5 = uVar5 - 8;
              }
              if (((uint)*(byte *)(ourBtlSaveDat + (uint)*(byte *)(ourBtlSaveDat + 2) * 0x200 +
                                   ((int)uStack_90 >> 3) + 0xaae) & 1 << (uVar5 & 0x1f)) != 0)
              goto LAB_005b11f0;
            }
          }
          else {
LAB_005b11f0:
            for (iVar4 = 0;
                (iVar4 < iStack_10c &&
                ((long)aiStack_320[iVar4] != (long)*(short *)(iStack_104 + uStack_90 * 0x1c + 0xc)))
                ; iVar4 = iVar4 + 1) {
            }
            if (iVar4 < iStack_10c) {
              aiStack_3a0[iVar4] = aiStack_3a0[iVar4] + 1;
            }
            else {
              aiStack_320[iStack_10c] = (int)*(short *)(iStack_104 + uStack_90 * 0x1c + 0xc);
              aiStack_3a0[iStack_10c] = 1;
              iStack_10c = iStack_10c + 1;
            }
          }
        }
        if (-1 < *(short *)(iStack_104 + uStack_90 * 0x1c + 0xe)) {
          if ((long)((ulong)*(byte *)(iStack_104 + uStack_90 * 0x1c + 6) << 0x3c) < 0) {
            if ((long)((ulong)*(byte *)(iStack_104 + uStack_90 * 0x1c + 6) << 0x3c) < 0) {
              uVar5 = uStack_90 & 7;
              if (((int)uStack_90 < 0) && (uVar5 != 0)) {
                uVar5 = uVar5 - 8;
              }
              if (((uint)*(byte *)(ourBtlSaveDat + (uint)*(byte *)(ourBtlSaveDat + 2) * 0x200 +
                                   ((int)uStack_90 >> 3) + 0xaae) & 1 << (uVar5 & 0x1f)) != 0)
              goto LAB_005b13c0;
            }
          }
          else {
LAB_005b13c0:
            for (iVar4 = 0;
                (iVar4 < iStack_10c &&
                ((long)aiStack_320[iVar4] != (long)*(short *)(iStack_104 + uStack_90 * 0x1c + 0xe)))
                ; iVar4 = iVar4 + 1) {
            }
            if (iVar4 < iStack_10c) {
              aiStack_3a0[iVar4] = aiStack_3a0[iVar4] + 1;
            }
            else {
              aiStack_320[iStack_10c] = (int)*(short *)(iStack_104 + uStack_90 * 0x1c + 0xe);
              aiStack_3a0[iStack_10c] = 1;
              iStack_10c = iStack_10c + 1;
            }
          }
        }
      }
    }
    sVar2 = *(short *)((int)pCGpffff86b4 +
                      (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x120);
    if (((sVar2 == 10) || (sVar2 == 9)) || (sVar2 == 8)) {
      iStack_10c = 0;
    }
    else if (sVar2 == 6) {
      iStack_110 = GetRegDat__9RegDatApiFiii(0x40,0,0xffffffffffffffff);
      if (-1 < (long)((ulong)*(byte *)(iStack_110 + *(int *)(ourBtlSocket + 0x698) * 0x10 + 4) <<
                     0x3e)) {
        iStack_10c = 0;
      }
    }
    if (iStack_10c != 0) {
      aiStack_270[iVar12] = 6;
      iVar12 = iVar12 + 1;
    }
  }
  if ((*(byte *)((int)pCGpffff86b4 +
                (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb4) & 1) == 0)
  {
    iStack_114 = 0;
    uStack_118 = GetRegCnt__9RegDatApiFii(0x33,0xffffffffffffffff);
    iStack_11c = GetRegDat__9RegDatApiFiii(0x33,0,0xffffffffffffffff);
    for (uStack_8c = 0; uStack_8c < uStack_118; uStack_8c = uStack_8c + 1) {
      if (((*(char *)(ourBtlSaveDat + (uint)*(byte *)(ourBtlSaveDat + 2) * 0x200 + uStack_8c + 0x944) !=
            '\0') && (((ulong)*(byte *)(iStack_11c + uStack_8c * 0x30 + 4) & 0x1f) >> 3 != 0)) &&
         (((ulong)*(byte *)(iStack_11c + uStack_8c * 0x30 + 4) & 0x1f) >> 3 != 3)) {
        iStack_114 = iStack_114 + 1;
      }
    }
    if (iStack_114 != 0) {
      aiStack_270[iVar12] = 8;
      iVar12 = iVar12 + 1;
    }
  }
  aiStack_270[iVar12] = 9;
  iVar4 = iVar12 + 1;
  iStack_120 = 0;
  iStack_124 = 0;
  for (uStack_8c = 0; (int)uStack_8c < 0xc; uStack_8c = uStack_8c + 1) {
    if (((((pCGpffff86b4->aChr[uStack_8c].bFlagsA & 1) != 0) &&
         ((long)((ulong)pCGpffff86b4->aChr[uStack_8c].bFlagsA << 0x3e) < 0)) &&
        ((-1 < (long)((ulong)pCGpffff86b4->aChr[uStack_8c].bFlagsA2 << 0x3d) &&
         ((((long)(int)uStack_8c != (long)pCGpffff86b4->cActor &&
           ((*(byte *)((int)pCGpffff86b4 +
                      (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb4) & 1)
            == (pCGpffff86b4->aChr[uStack_8c].bFlagsB & 1))) &&
          (iStack_120 = iStack_120 + 1, 0 < pCGpffff86b4->aChr[uStack_8c].nHp)))))) &&
       ((((*(byte *)((int)pCGpffff86b4 +
                    (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb4) & 1) !=
          0 || (0 < pCGpffff86b4->aChr[uStack_8c].nSp)) ||
        ((pCGpffff86b4->aChr[uStack_8c].nCharId == 8 ||
         ((pCGpffff86b4->aChr[uStack_8c].nCharId == 9 ||
          (pCGpffff86b4->aChr[uStack_8c].nCharId == 10)))))))) {
      uStack_90 = 0;
      while (((int)uStack_90 < 0x20 &&
             (((pCGpffff86b4->aChr[uStack_8c].aStatus[uStack_90].bKind != 0x47 ||
               (((ulong)pCGpffff86b4->aChr[uStack_8c].aStatus[uStack_90].bFlags & 0x1f) >> 2 != 0))
              || ((pCGpffff86b4->aChr[uStack_8c].aStatus[uStack_90].nValue & 0x24U) == 0))))) {
        uStack_90 = uStack_90 + 1;
      }
      if (0x1f < (int)uStack_90) {
        iStack_124 = iStack_124 + 1;
      }
    }
  }
  if ((iStack_120 != 0) && ((*(byte *)(ourBtlSaveDat + 3) & 1) != 0)) {
    aiStack_270[iVar4] = 10;
    iVar4 = iVar12 + 2;
  }
  aiStack_270[iVar4] = 0xb;
  iVar4 = iVar4 + 1;
  if ((((int)uStack_30 < 0) && (iStack_20 < 0)) && (-1 < iStack_10)) {
    for (uStack_8c = 0; ((int)uStack_8c < iVar4 && (iStack_10 != aiStack_270[uStack_8c]));
        uStack_8c = uStack_8c + 1) {
    }
    if ((int)uStack_8c < iVar4) {
      uStack_30 = uStack_8c;
    }
    else if ((iStack_10 < 0) || (4 < iStack_10)) {
      uStack_30 = 0;
    }
    else {
      for (uStack_8c = 0;
          ((int)uStack_8c < iVar4 && ((aiStack_270[uStack_8c] < 0 || (4 < aiStack_270[uStack_8c]))))
          ; uStack_8c = uStack_8c + 1) {
      }
      if ((int)uStack_8c < iVar4) {
        uStack_30 = uStack_8c;
      }
      else {
        uStack_30 = 0;
      }
    }
  }
  else if ((((int)uStack_30 < 0) && (iStack_20 < 0)) && ((int)uStack_30 < 0)) {
    uStack_30 = 0;
  }
  iVar12 = *(int *)(uStack_50 + iStack_40 * 0x16c + 0x130);
  iVar4 = *(int *)(uStack_50 + iStack_40 * 0x16c + 0x13c);
  uStack_a0 = 0;
  iVar11 = 0;
  iVar13 = 0;
  iVar14 = 0;
  fStack_ac = 0.0;
  uVar5 = uStack_30;
  if ((int)uStack_30 < 0) {
    uVar5 = uStack_30 + 3;
  }
  uVar7 = ((int)uVar5 >> 2) * 4;
  *(byte *)(iVar4 + 0x7f2) = *(byte *)(iVar4 + 0x7f2) & 0xfe;
  uVar5 = SetRendering__7MenuObjFUc(iVar4 + 0x7e0,0);
  if (((int)uVar7 < 1) && (uVar10 = uVar7 + 3, -1 < (int)uVar10)) {
    uStack_8c = (uint)*(char *)(uStack_50 + 0xb43);
    if (((uint)*(ushort *)(uStack_50 + 0xb40) & 1 << (uStack_8c & 0x1f)) == 0) {
      for (uStack_8c = 0;
          (uVar10 = 0, (int)uStack_8c < 4 &&
          (uVar10 = uStack_50, ((uint)*(ushort *)(uStack_50 + 0xb40) & 1 << (uStack_8c & 0x1f)) == 0
          )); uStack_8c = uStack_8c + 1) {
      }
      *(char *)(uStack_50 + 0xb43) = (char)uStack_8c;
      uVar5 = uStack_8c;
    }
    uStack_94 = 6;
    for (uStack_90 = 0; (int)uStack_90 < 0x20; uStack_90 = uStack_90 + 1) {
      uVar5 = uStack_90 * 3;
      uVar10 = 0x23;
      if (*(char *)((int)pCGpffff86b4 +
                   uStack_90 * 0xc +
                   (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x1bc) == '#')
      {
        uVar5 = pCGpffff86b4->cActor * 0x50;
        uVar10 = *(uint *)((int)pCGpffff86b4 +
                          uStack_90 * 0xc + (uVar5 - (int)pCGpffff86b4->cActor) * 0x10 + 0x1c0);
        uStack_94 = uVar10;
      }
    }
    if (uStack_8c == 3) {
      uStack_8c = 4;
      if (uStack_94 == 6) {
        SetUV__10MenuSpriteFUsUsUsUs(iVar4 + 0x7e0,0x36,0x16,0x48,0x2c,uVar10,uVar5);
      }
      else {
        SetUV__10MenuSpriteFUsUsUsUs(iVar4 + 0x7e0,0x36,0,0x48,0x16);
      }
    }
    else if (uStack_8c == 2) {
      uStack_8c = 3;
      if (uStack_94 == 6) {
        SetUV__10MenuSpriteFUsUsUsUs(iVar4 + 0x7e0,0x24,0x16,0x36,0x2c);
      }
      else {
        SetUV__10MenuSpriteFUsUsUsUs(iVar4 + 0x7e0,0x24,0,0x36,0x16,0x16,uVar5);
      }
    }
    else if (uStack_8c == 1) {
      uStack_8c = 2;
      if (uStack_94 == 6) {
        SetUV__10MenuSpriteFUsUsUsUs(iVar4 + 0x7e0,0x12,0x16,0x24,0x2c);
      }
      else {
        SetUV__10MenuSpriteFUsUsUsUs(iVar4 + 0x7e0,0x12,0,0x24,0x16);
      }
    }
    else if (uStack_8c == 0) {
      uStack_8c = 1;
      if (uStack_94 == 6) {
        SetUV__10MenuSpriteFUsUsUsUs(iVar4 + 0x7e0,0,0x16,0x12,0x2c);
      }
      else {
        SetUV__10MenuSpriteFUsUsUsUs(iVar4 + 0x7e0,0,0,0x12,0x16);
      }
    }
    else {
      uStack_8c = 0;
      if (uStack_94 == 6) {
        SetUV__10MenuSpriteFUsUsUsUs(iVar4 + 0x7e0,0,0x16,0x12,0x2c,0x16,uVar5);
      }
      else {
        SetUV__10MenuSpriteFUsUsUsUs(iVar4 + 0x7e0,0,0,0x12,0x16);
      }
    }
    (**(code **)(*(int *)(iVar4 + 0x7e8) + 0x30))
              (iVar4 + 0x7e0,*(undefined1 *)(uStack_94 * 4 + 0x654ea0),
               *(undefined1 *)(uStack_94 * 4 + 0x654ea1),*(undefined1 *)(uStack_94 * 4 + 0x654ea2));
    *(byte *)(iVar4 + 0x7f2) = *(byte *)(iVar4 + 0x7f2) & 0xfe | 1;
    SetRendering__7MenuObjFUc(iVar4 + 0x7e0,1);
    uVar6 = (**(code **)(*(int *)(iVar4 + 0x7e8) + 0x24))(0x43530000,fStack_ac + 15.0);
    SetCSA__8FontItemFUc(iVar12,0,iVar12,uVar6);
    *(undefined1 *)(iVar12 + 0x5c) = 0;
    UpdateEnv__7MenuObjFv(iVar12);
    uStack_5e = (undefined2)uStack_8c;
    *(undefined2 *)(iVar12 + 0x16) = uStack_5e;
    (**(code **)(*(int *)(iVar12 + 8) + 0x24))(0x42400000,fStack_ac + 20.0);
    SetMessage__8MenuTextFPcUiUcUc(iVar12,*puRam0040ab2c,0,0,1);
    *(undefined2 *)(iVar12 + 0x1c) = 0;
    *(undefined2 *)(iVar12 + 0x1e) = 0;
    *(byte *)(iVar12 + 0x21) = *(byte *)(iVar12 + 0x21) & 0xfd | 2;
    *(byte *)(iVar12 + 0x12) = *(byte *)(iVar12 + 0x12) & 0xfe | 1;
    SetRendering__7MenuObjFUc(iVar12,1);
    OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(uStack_50 + iStack_40 * 0x16c + 0x3c,iVar12,1,0);
    if (uStack_30 == 0) {
      *(undefined4 *)(uStack_50 + iStack_40 * 0x16c + 0x158) = 0;
      *(undefined4 *)(uStack_50 + iStack_40 * 0x16c + 0x16c) = 0;
      sStack_62 = *(short *)(iVar12 + 0x16);
      *(int *)(uStack_50 + iStack_40 * 0x16c + 0x164) = (int)sStack_62;
      *(int *)(uStack_50 + iStack_40 * 0x16c + 0x168) = (int)sStack_62;
    }
    if (uStack_8c == 0) {
      (**(code **)(*(int *)(iVar12 + 0x88) + 0x24))(0x42400000,fStack_ac + 14.0);
      SetMessage__8MenuTextFPcUiUcUc(iVar12 + 0x80,0x6551a8,0,0,1);
      *(undefined2 *)(iVar12 + 0x9c) = 1;
      *(undefined2 *)(iVar12 + 0x9e) = 0;
      *(byte *)(iVar12 + 0xa1) = *(byte *)(iVar12 + 0xa1) & 0xfd;
      *(byte *)(iVar12 + 0x92) = *(byte *)(iVar12 + 0x92) & 0xfe;
      SetRendering__7MenuObjFUc(iVar12 + 0x80,0);
      OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(uStack_50 + iStack_40 * 0x16c + 0x3c,iVar12 + 0x80,1,0);
    }
    else {
      SetMessage__8MenuTextFPcUiUcUc(iVar12 + 0x80,puRam0040ab2c[uStack_8c],0,0,1);
      sStack_64 = *(short *)(iVar12 + 0x16);
      uStack_8c = (uint)sStack_64;
      if ((int)uStack_8c < 1000) {
        SetCSA__8FontItemFUc(iVar12 + 0x80,0);
        *(undefined1 *)(iVar12 + 0xdc) = 0;
        UpdateEnv__7MenuObjFv(iVar12 + 0x80);
      }
      else {
        uVar6 = SetCSA__8FontItemFUc(iVar12 + 0x80,2);
        *(undefined1 *)(iVar12 + 0xdc) = 0;
        UpdateEnv__7MenuObjFv(iVar12 + 0x80,uVar6);
      }
      *(undefined2 *)(iVar12 + 0x9c) = 1;
      *(undefined2 *)(iVar12 + 0x9e) = 0;
      *(byte *)(iVar12 + 0xa1) = *(byte *)(iVar12 + 0xa1) & 0xfd;
      *(byte *)(iVar12 + 0x92) = *(byte *)(iVar12 + 0x92) & 0xfe | 1;
      SetRendering__7MenuObjFUc(iVar12 + 0x80,1);
      OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(uStack_50 + iStack_40 * 0x16c + 0x3c,iVar12 + 0x80,1,0);
      fStack_1e0 = *(float *)(iVar12 + 0xac);
      sStack_56 = (short)(int)fStack_1e0;
      fStack_1e4 = *(float *)(iVar12 + 0xb0);
      sStack_58 = (short)(int)fStack_1e4;
      iVar13 = (int)sStack_56;
      if (sStack_56 < 0) {
        iVar13 = iVar13 + 1;
      }
      sStack_52 = 100 - (short)(iVar13 >> 1);
      sStack_54 = (short)(int)(fStack_ac + 14.0);
      (**(code **)(*(int *)(iVar12 + 0x88) + 0x24))
                ((float)(int)sStack_52 + 48.0,(float)(int)sStack_54);
      SetArea__10ScrollMarkFUcffff((float)(int)sStack_52 + 48.0,(float)(int)sStack_54,(float)(int)sStack_56,
                      (float)(int)sStack_58,*(undefined4 *)(uStack_50 + iStack_40 * 0x16c + 0x140),
                      0xc);
    }
    iVar11 = 2;
    (**(code **)(*(int *)(iVar4 + 8) + 0x24))(0,fStack_ac);
    uVar6 = SetUV__10MenuSpriteFUsUsUsUs(iVar4,1,0x1d,0xf5,0x52);
    (**(code **)(*(int *)(iVar4 + 8) + 0x28))(0x43740000,0x42540000,iVar4,uVar6);
    *(byte *)(iVar4 + 0x12) = *(byte *)(iVar4 + 0x12) & 0xfe | 1;
    SetRendering__7MenuObjFUc(iVar4,1);
    iVar13 = 1;
    iVar14 = 1;
    fStack_ac = fStack_ac + 52.0;
  }
  uVar5 = 1;
  if ((((*(byte *)((int)pCGpffff86b4 +
                  (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb4) & 1) == 0
       ) && (pCGpffff86b4->nComboCnt != 0)) && (iStack_9c == 0)) {
    CheckComboSkill__7CBattleFiPiPi
              (pCGpffff86b4,(int)pCGpffff86b4->cActor,(int *)&uStack_8c,(int *)&uStack_90);
    if ((*(short *)((int)pCGpffff86b4 +
                   (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x120) == 6)
       && (iStack_128 = GetRegDat__9RegDatApiFiii(0x40,0,0xffffffffffffffff),
          -1 < (long)((ulong)*(byte *)(iStack_128 + *(int *)(ourBtlSocket + 0x698) * 0x10 + 4) <<
                     0x3e))) {
      uStack_8c = 0;
    }
    uVar5 = 1;
    if (uStack_8c != 0) {
      if (((int)uVar7 < 2) && (0 < (int)(uVar7 + 3))) {
        if (uVar7 == 1) {
          fStack_ac = fStack_ac + 9.0;
        }
        SetCSA__8FontItemFUc(iVar12 + iVar11 * 0x80,0);
        *(undefined1 *)(iVar12 + iVar11 * 0x80 + 0x5c) = 0;
        UpdateEnv__7MenuObjFv(iVar12 + iVar11 * 0x80);
        *(undefined2 *)(iVar12 + iVar11 * 0x80 + 0x16) = 5;
        (**(code **)(*(int *)(iVar12 + iVar11 * 0x80 + 8) + 0x24))(0x42400000,fStack_ac + 2.0);
        SetMessage__8MenuTextFPcUiUcUc(iVar12 + iVar11 * 0x80,puRam0040ab2c[5],0,0,1);
        *(undefined2 *)(iVar12 + iVar11 * 0x80 + 0x1c) = 0;
        *(short *)(iVar12 + iVar11 * 0x80 + 0x1e) = (short)iVar14;
        iVar8 = iVar12 + iVar11 * 0x80;
        *(byte *)(iVar8 + 0x21) = *(byte *)(iVar8 + 0x21) & 0xfd | 2;
        iVar8 = iVar12 + iVar11 * 0x80;
        *(byte *)(iVar8 + 0x12) = *(byte *)(iVar8 + 0x12) & 0xfe | 1;
        SetRendering__7MenuObjFUc(iVar12 + iVar11 * 0x80,1);
        OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(uStack_50 + iStack_40 * 0x16c + 0x3c,iVar12 + iVar11 * 0x80,1,0);
        if (uStack_30 == 1) {
          *(int *)(uStack_50 + iStack_40 * 0x16c + 0x158) = iVar11;
          *(undefined4 *)(uStack_50 + iStack_40 * 0x16c + 0x16c) = 1;
          sStack_66 = *(short *)(iVar12 + iVar11 * 0x80 + 0x16);
          *(int *)(uStack_50 + iStack_40 * 0x16c + 0x164) = (int)sStack_66;
          *(int *)(uStack_50 + iStack_40 * 0x16c + 0x168) = (int)sStack_66;
        }
        iVar9 = iVar11 + 1;
        (**(code **)(*(int *)(iVar12 + iVar9 * 0x80 + 8) + 0x24))(0x42400000,fStack_ac + 2.0);
        SetMessage__8MenuTextFPcUiUcUc(iVar12 + iVar9 * 0x80,0x6551a8,0,0,1);
        *(undefined2 *)(iVar12 + iVar9 * 0x80 + 0x1c) = 1;
        *(short *)(iVar12 + iVar9 * 0x80 + 0x1e) = (short)iVar14;
        iVar8 = iVar12 + iVar9 * 0x80;
        *(byte *)(iVar8 + 0x21) = *(byte *)(iVar8 + 0x21) & 0xfd;
        iVar8 = iVar12 + iVar9 * 0x80;
        *(byte *)(iVar8 + 0x12) = *(byte *)(iVar8 + 0x12) & 0xfe;
        SetRendering__7MenuObjFUc(iVar12 + iVar9 * 0x80,0);
        OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(uStack_50 + iStack_40 * 0x16c + 0x3c,iVar12 + iVar9 * 0x80,1,0);
        iVar11 = iVar11 + 2;
        (**(code **)(*(int *)(iVar4 + iVar13 * 0x60 + 8) + 0x24))(0,fStack_ac);
        SetUV__10MenuSpriteFUsUsUsUs(iVar4 + iVar13 * 0x60,1,1,0xdd,0x1c);
        (**(code **)(*(int *)(iVar4 + iVar13 * 0x60 + 8) + 0x28))(0x435c0000,0x41d80000);
        iVar8 = iVar4 + iVar13 * 0x60;
        *(byte *)(iVar8 + 0x12) = *(byte *)(iVar8 + 0x12) & 0xfe | 1;
        SetRendering__7MenuObjFUc(iVar4 + iVar13 * 0x60,1);
        iVar13 = iVar13 + 1;
        iVar14 = iVar14 + 1;
        fStack_ac = fStack_ac + 26.0;
      }
      uVar5 = 2;
    }
  }
  uStack_8c = 0x7fff;
  if ((((*(byte *)((int)pCGpffff86b4 +
                  (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb4) & 1) == 0
       ) && (*(short *)((int)pCGpffff86b4 +
                       (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x120) ==
             0)) && ((*(uint *)(ourBtlSaveDat + 0xd4c) & 0x7fff) != 0)) {
    if (((int)uVar7 <= (int)uVar5) && ((int)uVar5 <= (int)(uVar7 + 3))) {
      if (uVar7 == uVar5) {
        fStack_ac = fStack_ac + 9.0;
      }
      if (((*(byte *)((int)pCGpffff86b4 +
                     (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb1) & 1)
           == 0) && (iStack_9c != 0)) {
        SetCSA__8FontItemFUc(iVar12 + iVar11 * 0x80,2);
        *(undefined1 *)(iVar12 + iVar11 * 0x80 + 0x5c) = 0;
        UpdateEnv__7MenuObjFv(iVar12 + iVar11 * 0x80);
        *(undefined2 *)(iVar12 + iVar11 * 0x80 + 0x16) = 0x3f4;
      }
      else {
        SetCSA__8FontItemFUc(iVar12 + iVar11 * 0x80,0);
        *(undefined1 *)(iVar12 + iVar11 * 0x80 + 0x5c) = 0;
        UpdateEnv__7MenuObjFv(iVar12 + iVar11 * 0x80);
        *(undefined2 *)(iVar12 + iVar11 * 0x80 + 0x16) = 0xc;
      }
      (**(code **)(*(int *)(iVar12 + iVar11 * 0x80 + 8) + 0x24))(0x42400000,fStack_ac + 2.0);
      SetMessage__8MenuTextFPcUiUcUc(iVar12 + iVar11 * 0x80,puRam0040ab2c[0xc],0,0,1);
      *(undefined2 *)(iVar12 + iVar11 * 0x80 + 0x1c) = 0;
      *(short *)(iVar12 + iVar11 * 0x80 + 0x1e) = (short)iVar14;
      iVar8 = iVar12 + iVar11 * 0x80;
      *(byte *)(iVar8 + 0x21) = *(byte *)(iVar8 + 0x21) & 0xfd | 2;
      iVar8 = iVar12 + iVar11 * 0x80;
      *(byte *)(iVar8 + 0x12) = *(byte *)(iVar8 + 0x12) & 0xfe | 1;
      SetRendering__7MenuObjFUc(iVar12 + iVar11 * 0x80,1);
      OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(uStack_50 + iStack_40 * 0x16c + 0x3c,iVar12 + iVar11 * 0x80,1,0);
      if (uStack_30 == uVar5) {
        *(int *)(uStack_50 + iStack_40 * 0x16c + 0x158) = iVar11;
        *(uint *)(uStack_50 + iStack_40 * 0x16c + 0x16c) = uVar5;
        sStack_68 = *(short *)(iVar12 + iVar11 * 0x80 + 0x16);
        *(int *)(uStack_50 + iStack_40 * 0x16c + 0x164) = (int)sStack_68;
        *(int *)(uStack_50 + iStack_40 * 0x16c + 0x168) = (int)sStack_68;
      }
      iVar9 = iVar11 + 1;
      (**(code **)(*(int *)(iVar12 + iVar9 * 0x80 + 8) + 0x24))(0x42400000,fStack_ac + 2.0);
      SetMessage__8MenuTextFPcUiUcUc(iVar12 + iVar9 * 0x80,0x6551a8,0,0,1);
      *(undefined2 *)(iVar12 + iVar9 * 0x80 + 0x1c) = 1;
      *(short *)(iVar12 + iVar9 * 0x80 + 0x1e) = (short)iVar14;
      iVar8 = iVar12 + iVar9 * 0x80;
      *(byte *)(iVar8 + 0x21) = *(byte *)(iVar8 + 0x21) & 0xfd;
      iVar8 = iVar12 + iVar9 * 0x80;
      *(byte *)(iVar8 + 0x12) = *(byte *)(iVar8 + 0x12) & 0xfe;
      SetRendering__7MenuObjFUc(iVar12 + iVar9 * 0x80,0);
      OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(uStack_50 + iStack_40 * 0x16c + 0x3c,iVar12 + iVar9 * 0x80,1,0);
      iVar11 = iVar11 + 2;
      (**(code **)(*(int *)(iVar4 + iVar13 * 0x60 + 8) + 0x24))(0,fStack_ac);
      SetUV__10MenuSpriteFUsUsUsUs(iVar4 + iVar13 * 0x60,1,1,0xdd,0x1c);
      (**(code **)(*(int *)(iVar4 + iVar13 * 0x60 + 8) + 0x28))(0x435c0000,0x41d80000);
      iVar8 = iVar4 + iVar13 * 0x60;
      *(byte *)(iVar8 + 0x12) = *(byte *)(iVar8 + 0x12) & 0xfe | 1;
      SetRendering__7MenuObjFUc(iVar4 + iVar13 * 0x60,1);
      iVar13 = iVar13 + 1;
      iVar14 = iVar14 + 1;
      fStack_ac = fStack_ac + 26.0;
    }
    uVar5 = uVar5 + 1;
  }
  if (((*(byte *)((int)pCGpffff86b4 +
                 (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb4) & 1) == 0)
     && (*(short *)((int)pCGpffff86b4 +
                   (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x120) == 1))
  {
    uStack_94 = 0x1000;
    if (((int)uVar7 <= (int)uVar5) && ((int)uVar5 <= (int)(uVar7 + 3))) {
      if (uVar7 == uVar5) {
        fStack_ac = fStack_ac + 9.0;
      }
      if (iStack_9c == 0) {
        uVar6 = SetCSA__8FontItemFUc(iVar12 + iVar11 * 0x80,0);
        iVar8 = iVar12 + iVar11 * 0x80;
        *(undefined1 *)(iVar8 + 0x5c) = 0;
        UpdateEnv__7MenuObjFv(iVar12 + iVar11 * 0x80,iVar8,uVar6);
        *(undefined2 *)(iVar12 + iVar11 * 0x80 + 0x16) = 0xd;
      }
      else {
        SetCSA__8FontItemFUc(iVar12 + iVar11 * 0x80,2);
        *(undefined1 *)(iVar12 + iVar11 * 0x80 + 0x5c) = 0;
        UpdateEnv__7MenuObjFv(iVar12 + iVar11 * 0x80);
        *(undefined2 *)(iVar12 + iVar11 * 0x80 + 0x16) = 0x3f5;
      }
      (**(code **)(*(int *)(iVar12 + iVar11 * 0x80 + 8) + 0x24))(0x42400000,fStack_ac + 2.0);
      SetMessage__8MenuTextFPcUiUcUc(iVar12 + iVar11 * 0x80,puRam0040ab2c[0xd],0,0,1);
      *(undefined2 *)(iVar12 + iVar11 * 0x80 + 0x1c) = 0;
      *(short *)(iVar12 + iVar11 * 0x80 + 0x1e) = (short)iVar14;
      iVar8 = iVar12 + iVar11 * 0x80;
      *(byte *)(iVar8 + 0x21) = *(byte *)(iVar8 + 0x21) & 0xfd | 2;
      iVar8 = iVar12 + iVar11 * 0x80;
      *(byte *)(iVar8 + 0x12) = *(byte *)(iVar8 + 0x12) & 0xfe | 1;
      SetRendering__7MenuObjFUc(iVar12 + iVar11 * 0x80,1);
      OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(uStack_50 + iStack_40 * 0x16c + 0x3c,iVar12 + iVar11 * 0x80,1,0);
      if (uStack_30 == uVar5) {
        *(int *)(uStack_50 + iStack_40 * 0x16c + 0x158) = iVar11;
        *(uint *)(uStack_50 + iStack_40 * 0x16c + 0x16c) = uVar5;
        sStack_6a = *(short *)(iVar12 + iVar11 * 0x80 + 0x16);
        *(int *)(uStack_50 + iStack_40 * 0x16c + 0x164) = (int)sStack_6a;
        *(int *)(uStack_50 + iStack_40 * 0x16c + 0x168) = (int)sStack_6a;
      }
      iVar9 = iVar11 + 1;
      (**(code **)(*(int *)(iVar12 + iVar9 * 0x80 + 8) + 0x24))(0x42400000,fStack_ac + 2.0);
      SetMessage__8MenuTextFPcUiUcUc(iVar12 + iVar9 * 0x80,0x6551a8,0,0,1);
      *(undefined2 *)(iVar12 + iVar9 * 0x80 + 0x1c) = 1;
      *(short *)(iVar12 + iVar9 * 0x80 + 0x1e) = (short)iVar14;
      iVar8 = iVar12 + iVar9 * 0x80;
      *(byte *)(iVar8 + 0x21) = *(byte *)(iVar8 + 0x21) & 0xfd;
      iVar8 = iVar12 + iVar9 * 0x80;
      *(byte *)(iVar8 + 0x12) = *(byte *)(iVar8 + 0x12) & 0xfe;
      SetRendering__7MenuObjFUc(iVar12 + iVar9 * 0x80,0);
      OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(uStack_50 + iStack_40 * 0x16c + 0x3c,iVar12 + iVar9 * 0x80,1,0);
      iVar11 = iVar11 + 2;
      (**(code **)(*(int *)(iVar4 + iVar13 * 0x60 + 8) + 0x24))(0,fStack_ac);
      SetUV__10MenuSpriteFUsUsUsUs(iVar4 + iVar13 * 0x60,1,1,0xdd,0x1c);
      (**(code **)(*(int *)(iVar4 + iVar13 * 0x60 + 8) + 0x28))(0x435c0000,0x41d80000);
      iVar8 = iVar4 + iVar13 * 0x60;
      *(byte *)(iVar8 + 0x12) = *(byte *)(iVar8 + 0x12) & 0xfe | 1;
      SetRendering__7MenuObjFUc(iVar4 + iVar13 * 0x60,1);
      iVar13 = iVar13 + 1;
      iVar14 = iVar14 + 1;
      fStack_ac = fStack_ac + 26.0;
    }
    uVar5 = uVar5 + 1;
  }
  if (((((*(byte *)((int)pCGpffff86b4 +
                   (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb4) & 1) ==
         0) && (*(short *)((int)pCGpffff86b4 +
                          (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x120)
                == 2)) && (*(int *)(*(int *)(g_83f8 + 0xc) + 0x2fc) != 0)) &&
     (iStack_1e8 = *(int *)(*(int *)(g_83f8 + 0xc) + 0x2fc), iStack_12c = iStack_1e8,
     iStack_1e8 != 0)) {
    if (((int)uVar7 <= (int)uVar5) && ((int)uVar5 <= (int)(uVar7 + 3))) {
      if (uVar7 == uVar5) {
        fStack_ac = fStack_ac + 9.0;
      }
      if (iStack_9c == 0) {
        SetCSA__8FontItemFUc(iVar12 + iVar11 * 0x80,0);
        *(undefined1 *)(iVar12 + iVar11 * 0x80 + 0x5c) = 0;
        UpdateEnv__7MenuObjFv(iVar12 + iVar11 * 0x80);
        *(undefined2 *)(iVar12 + iVar11 * 0x80 + 0x16) = 0xe;
      }
      else {
        SetCSA__8FontItemFUc(iVar12 + iVar11 * 0x80,2);
        *(undefined1 *)(iVar12 + iVar11 * 0x80 + 0x5c) = 0;
        UpdateEnv__7MenuObjFv(iVar12 + iVar11 * 0x80);
        *(undefined2 *)(iVar12 + iVar11 * 0x80 + 0x16) = 0x3f6;
      }
      (**(code **)(*(int *)(iVar12 + iVar11 * 0x80 + 8) + 0x24))(0x42400000,fStack_ac + 2.0);
      SetMessage__8MenuTextFPcUiUcUc(iVar12 + iVar11 * 0x80,puRam0040ab2c[0xe],0,0,1);
      *(undefined2 *)(iVar12 + iVar11 * 0x80 + 0x1c) = 0;
      *(short *)(iVar12 + iVar11 * 0x80 + 0x1e) = (short)iVar14;
      iVar8 = iVar12 + iVar11 * 0x80;
      *(byte *)(iVar8 + 0x21) = *(byte *)(iVar8 + 0x21) & 0xfd | 2;
      iVar8 = iVar12 + iVar11 * 0x80;
      *(byte *)(iVar8 + 0x12) = *(byte *)(iVar8 + 0x12) & 0xfe | 1;
      SetRendering__7MenuObjFUc(iVar12 + iVar11 * 0x80,1);
      OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(uStack_50 + iStack_40 * 0x16c + 0x3c,iVar12 + iVar11 * 0x80,1,0);
      if (uStack_30 == uVar5) {
        *(int *)(uStack_50 + iStack_40 * 0x16c + 0x158) = iVar11;
        *(uint *)(uStack_50 + iStack_40 * 0x16c + 0x16c) = uVar5;
        sStack_6c = *(short *)(iVar12 + iVar11 * 0x80 + 0x16);
        *(int *)(uStack_50 + iStack_40 * 0x16c + 0x164) = (int)sStack_6c;
        *(int *)(uStack_50 + iStack_40 * 0x16c + 0x168) = (int)sStack_6c;
      }
      iVar9 = iVar11 + 1;
      (**(code **)(*(int *)(iVar12 + iVar9 * 0x80 + 8) + 0x24))(0x42400000,fStack_ac + 2.0);
      SetMessage__8MenuTextFPcUiUcUc(iVar12 + iVar9 * 0x80,0x6551a8,0,0,1);
      *(undefined2 *)(iVar12 + iVar9 * 0x80 + 0x1c) = 1;
      *(short *)(iVar12 + iVar9 * 0x80 + 0x1e) = (short)iVar14;
      iVar8 = iVar12 + iVar9 * 0x80;
      *(byte *)(iVar8 + 0x21) = *(byte *)(iVar8 + 0x21) & 0xfd;
      iVar8 = iVar12 + iVar9 * 0x80;
      *(byte *)(iVar8 + 0x12) = *(byte *)(iVar8 + 0x12) & 0xfe;
      uVar6 = SetRendering__7MenuObjFUc(iVar12 + iVar9 * 0x80,0);
      OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(uStack_50 + iStack_40 * 0x16c + 0x3c,iVar12 + iVar9 * 0x80,1,0,uStack_50,uVar6
                     );
      iVar11 = iVar11 + 2;
      uVar6 = (**(code **)(*(int *)(iVar4 + iVar13 * 0x60 + 8) + 0x24))(0,fStack_ac);
      SetUV__10MenuSpriteFUsUsUsUs(iVar4 + iVar13 * 0x60,1,1,0xdd,0x1c,uVar6);
      (**(code **)(*(int *)(iVar4 + iVar13 * 0x60 + 8) + 0x28))(0x435c0000,0x41d80000);
      iVar8 = iVar4 + iVar13 * 0x60;
      *(byte *)(iVar8 + 0x12) = *(byte *)(iVar8 + 0x12) & 0xfe | 1;
      SetRendering__7MenuObjFUc(iVar4 + iVar13 * 0x60,1);
      iVar13 = iVar13 + 1;
      iVar14 = iVar14 + 1;
      fStack_ac = fStack_ac + 26.0;
    }
    uVar5 = uVar5 + 1;
  }
  if ((((*(byte *)((int)pCGpffff86b4 +
                  (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb4) & 1) == 0
       ) && (*(short *)((int)pCGpffff86b4 +
                       (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x120) ==
             3)) &&
     ((*(char *)(ourBtlSaveDat + 0xdab) != '\0' ||
      ((*(char *)(ourBtlSaveDat + 0xdac) != '\0' || (*(char *)(ourBtlSaveDat + 0xdad) != '\0')))))) {
    if (((int)uVar7 <= (int)uVar5) && ((int)uVar5 <= (int)(uVar7 + 3))) {
      if (uVar7 == uVar5) {
        fStack_ac = fStack_ac + 9.0;
      }
      *(undefined2 *)(iVar12 + iVar11 * 0x80 + 0x16) = 0xf;
      SetCSA__8FontItemFUc(iVar12 + iVar11 * 0x80,0);
      *(undefined1 *)(iVar12 + iVar11 * 0x80 + 0x5c) = 0;
      uVar6 = UpdateEnv__7MenuObjFv(iVar12 + iVar11 * 0x80);
      iVar8 = iVar12 + iVar11 * 0x80;
      uVar6 = (**(code **)(*(int *)(iVar8 + 8) + 0x24))(0x42400000,fStack_ac + 2.0,iVar8,uVar6);
      SetMessage__8MenuTextFPcUiUcUc(iVar12 + iVar11 * 0x80,puRam0040ab2c[0xf],0,0,1,uVar6);
      *(undefined2 *)(iVar12 + iVar11 * 0x80 + 0x1c) = 0;
      *(short *)(iVar12 + iVar11 * 0x80 + 0x1e) = (short)iVar14;
      iVar8 = iVar12 + iVar11 * 0x80;
      *(byte *)(iVar8 + 0x21) = *(byte *)(iVar8 + 0x21) & 0xfd | 2;
      iVar8 = iVar12 + iVar11 * 0x80;
      *(byte *)(iVar8 + 0x12) = *(byte *)(iVar8 + 0x12) & 0xfe | 1;
      SetRendering__7MenuObjFUc(iVar12 + iVar11 * 0x80,1);
      OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(uStack_50 + iStack_40 * 0x16c + 0x3c,iVar12 + iVar11 * 0x80,1,0);
      if (uStack_30 == uVar5) {
        *(int *)(uStack_50 + iStack_40 * 0x16c + 0x158) = iVar11;
        *(uint *)(uStack_50 + iStack_40 * 0x16c + 0x16c) = uVar5;
        sStack_6e = *(short *)(iVar12 + iVar11 * 0x80 + 0x16);
        *(int *)(uStack_50 + iStack_40 * 0x16c + 0x164) = (int)sStack_6e;
        *(int *)(uStack_50 + iStack_40 * 0x16c + 0x168) = (int)sStack_6e;
      }
      iVar9 = iVar11 + 1;
      (**(code **)(*(int *)(iVar12 + iVar9 * 0x80 + 8) + 0x24))(0x42400000,fStack_ac + 2.0);
      SetMessage__8MenuTextFPcUiUcUc(iVar12 + iVar9 * 0x80,0x6551a8,0,0,1);
      *(undefined2 *)(iVar12 + iVar9 * 0x80 + 0x1c) = 1;
      *(short *)(iVar12 + iVar9 * 0x80 + 0x1e) = (short)iVar14;
      iVar8 = iVar12 + iVar9 * 0x80;
      *(byte *)(iVar8 + 0x21) = *(byte *)(iVar8 + 0x21) & 0xfd;
      iVar8 = iVar12 + iVar9 * 0x80;
      *(byte *)(iVar8 + 0x12) = *(byte *)(iVar8 + 0x12) & 0xfe;
      SetRendering__7MenuObjFUc(iVar12 + iVar9 * 0x80,0);
      OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(uStack_50 + iStack_40 * 0x16c + 0x3c,iVar12 + iVar9 * 0x80,1,0);
      iVar11 = iVar11 + 2;
      (**(code **)(*(int *)(iVar4 + iVar13 * 0x60 + 8) + 0x24))(0,fStack_ac);
      SetUV__10MenuSpriteFUsUsUsUs(iVar4 + iVar13 * 0x60,1,1,0xdd,0x1c);
      (**(code **)(*(int *)(iVar4 + iVar13 * 0x60 + 8) + 0x28))(0x435c0000,0x41d80000);
      iVar8 = iVar4 + iVar13 * 0x60;
      *(byte *)(iVar8 + 0x12) = *(byte *)(iVar8 + 0x12) & 0xfe | 1;
      SetRendering__7MenuObjFUc(iVar4 + iVar13 * 0x60,1);
      iVar13 = iVar13 + 1;
      iVar14 = iVar14 + 1;
      fStack_ac = fStack_ac + 26.0;
    }
    uVar5 = uVar5 + 1;
  }
  if ((((*(byte *)((int)pCGpffff86b4 +
                  (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb4) & 1) == 0
       ) && (*(short *)((int)pCGpffff86b4 +
                       (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x120) ==
             3)) && (*(char *)(ourBtlSaveDat + 0xdae) != '\0')) {
    uStack_130 = GetRegCnt__9RegDatApiFii(0x3d,0xffffffffffffffff);
    iStack_134 = GetRegDat__9RegDatApiFiii(0x3d,0,0xffffffffffffffff);
    iStack_138 = 0;
    for (uStack_8c = 0; uStack_8c < uStack_130; uStack_8c = uStack_8c + 1) {
      if ((((uint)*(byte *)(ourBtlSaveDat + 0xdae) &
           1 << ((int)*(char *)(iStack_134 + uStack_8c * 0x40 + 0x1c) & 0x1fU)) != 0) &&
         (((uint)*(byte *)(ourBtlSaveDat + 0xdae) &
          1 << ((int)*(char *)(iStack_134 + uStack_8c * 0x40 + 0x1d) & 0x1fU)) != 0)) {
        iStack_138 = iStack_138 + 1;
      }
    }
    if (iStack_138 != 0) {
      if (((int)uVar7 <= (int)uVar5) && ((int)uVar5 <= (int)(uVar7 + 3))) {
        if (uVar7 == uVar5) {
          fStack_ac = fStack_ac + 9.0;
        }
        if ((*(short *)&pCGpffff86b4->field_0x3ef0 < 0) && (iStack_9c == 0)) {
          *(undefined2 *)(iVar12 + iVar11 * 0x80 + 0x16) = 0x10;
          uVar6 = SetCSA__8FontItemFUc(iVar12 + iVar11 * 0x80,0);
          *(undefined1 *)(iVar12 + iVar11 * 0x80 + 0x5c) = 0;
          UpdateEnv__7MenuObjFv(iVar12 + iVar11 * 0x80,uVar6);
        }
        else {
          *(undefined2 *)(iVar12 + iVar11 * 0x80 + 0x16) = 0x3f8;
          SetCSA__8FontItemFUc(iVar12 + iVar11 * 0x80,2);
          *(undefined1 *)(iVar12 + iVar11 * 0x80 + 0x5c) = 0;
          UpdateEnv__7MenuObjFv(iVar12 + iVar11 * 0x80);
        }
        (**(code **)(*(int *)(iVar12 + iVar11 * 0x80 + 8) + 0x24))(0x42400000,fStack_ac + 2.0);
        SetMessage__8MenuTextFPcUiUcUc(iVar12 + iVar11 * 0x80,puRam0040ab2c[0x10],0,0,1);
        *(undefined2 *)(iVar12 + iVar11 * 0x80 + 0x1c) = 0;
        *(short *)(iVar12 + iVar11 * 0x80 + 0x1e) = (short)iVar14;
        iVar8 = iVar12 + iVar11 * 0x80;
        *(byte *)(iVar8 + 0x21) = *(byte *)(iVar8 + 0x21) & 0xfd | 2;
        iVar8 = iVar12 + iVar11 * 0x80;
        *(byte *)(iVar8 + 0x12) = *(byte *)(iVar8 + 0x12) & 0xfe | 1;
        SetRendering__7MenuObjFUc(iVar12 + iVar11 * 0x80,1);
        OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(uStack_50 + iStack_40 * 0x16c + 0x3c,iVar12 + iVar11 * 0x80,1,0);
        if (uStack_30 == uVar5) {
          *(int *)(uStack_50 + iStack_40 * 0x16c + 0x158) = iVar11;
          *(uint *)(uStack_50 + iStack_40 * 0x16c + 0x16c) = uVar5;
          sStack_70 = *(short *)(iVar12 + iVar11 * 0x80 + 0x16);
          *(int *)(uStack_50 + iStack_40 * 0x16c + 0x164) = (int)sStack_70;
          *(int *)(uStack_50 + iStack_40 * 0x16c + 0x168) = (int)sStack_70;
        }
        iVar9 = iVar11 + 1;
        (**(code **)(*(int *)(iVar12 + iVar9 * 0x80 + 8) + 0x24))(0x42400000,fStack_ac + 2.0);
        SetMessage__8MenuTextFPcUiUcUc(iVar12 + iVar9 * 0x80,0x6551a8,0,0,1);
        *(undefined2 *)(iVar12 + iVar9 * 0x80 + 0x1c) = 1;
        *(short *)(iVar12 + iVar9 * 0x80 + 0x1e) = (short)iVar14;
        iVar8 = iVar12 + iVar9 * 0x80;
        *(byte *)(iVar8 + 0x21) = *(byte *)(iVar8 + 0x21) & 0xfd;
        iVar8 = iVar12 + iVar9 * 0x80;
        *(byte *)(iVar8 + 0x12) = *(byte *)(iVar8 + 0x12) & 0xfe;
        SetRendering__7MenuObjFUc(iVar12 + iVar9 * 0x80,0);
        OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(uStack_50 + iStack_40 * 0x16c + 0x3c,iVar12 + iVar9 * 0x80,1,0);
        iVar11 = iVar11 + 2;
        (**(code **)(*(int *)(iVar4 + iVar13 * 0x60 + 8) + 0x24))(0,fStack_ac);
        SetUV__10MenuSpriteFUsUsUsUs(iVar4 + iVar13 * 0x60,1,1,0xdd,0x1c);
        (**(code **)(*(int *)(iVar4 + iVar13 * 0x60 + 8) + 0x28))(0x435c0000,0x41d80000);
        iVar8 = iVar4 + iVar13 * 0x60;
        *(byte *)(iVar8 + 0x12) = *(byte *)(iVar8 + 0x12) & 0xfe | 1;
        SetRendering__7MenuObjFUc(iVar4 + iVar13 * 0x60,1);
        iVar13 = iVar13 + 1;
        iVar14 = iVar14 + 1;
        fStack_ac = fStack_ac + 26.0;
      }
      uVar5 = uVar5 + 1;
    }
  }
  if (((((*(byte *)((int)pCGpffff86b4 +
                   (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb4) & 1) ==
         0) && ((*(byte *)((int)pCGpffff86b4 +
                          (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb1) &
                1) == 0)) &&
      (*(short *)((int)pCGpffff86b4 +
                 (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x120) == 4)) &&
     (((*(char *)(ourBtlSaveDat + 0xe2f) != '\0' || (*(char *)(ourBtlSaveDat + 0xe30) != '\0')) ||
      (*(char *)(ourBtlSaveDat + 0xe31) != '\0')))) {
    uStack_13c = GetRegCnt__9RegDatApiFii(0x36,4);
    iStack_140 = 0;
    for (uStack_8c = 0; uStack_8c < uStack_13c; uStack_8c = uStack_8c + 1) {
      uVar10 = uStack_8c & 7;
      if (((int)uStack_8c < 0) && (uVar10 != 0)) {
        uVar10 = uVar10 - 8;
      }
      if (((uint)*(byte *)(ourBtlSaveDat + ((int)uStack_8c >> 3) + 0xe2f) & 1 << (uVar10 & 0x1f)) != 0
         ) {
        iStack_140 = iStack_140 + 1;
      }
    }
    if (iStack_140 != 0) {
      if (((int)uVar7 <= (int)uVar5) && ((int)uVar5 <= (int)(uVar7 + 3))) {
        if (uVar7 == uVar5) {
          fStack_ac = fStack_ac + 9.0;
        }
        if (iStack_9c == 0) {
          *(undefined2 *)(iVar12 + iVar11 * 0x80 + 0x16) = 0x12;
          SetCSA__8FontItemFUc(iVar12 + iVar11 * 0x80,0);
          *(undefined1 *)(iVar12 + iVar11 * 0x80 + 0x5c) = 0;
          UpdateEnv__7MenuObjFv(iVar12 + iVar11 * 0x80);
        }
        else {
          *(undefined2 *)(iVar12 + iVar11 * 0x80 + 0x16) = 0x3fa;
          SetCSA__8FontItemFUc(iVar12 + iVar11 * 0x80,2);
          *(undefined1 *)(iVar12 + iVar11 * 0x80 + 0x5c) = 0;
          UpdateEnv__7MenuObjFv(iVar12 + iVar11 * 0x80);
        }
        (**(code **)(*(int *)(iVar12 + iVar11 * 0x80 + 8) + 0x24))(0x42400000,fStack_ac + 2.0);
        SetMessage__8MenuTextFPcUiUcUc(iVar12 + iVar11 * 0x80,puRam0040ab2c[0x12],0,0,1);
        *(undefined2 *)(iVar12 + iVar11 * 0x80 + 0x1c) = 0;
        *(short *)(iVar12 + iVar11 * 0x80 + 0x1e) = (short)iVar14;
        iVar8 = iVar12 + iVar11 * 0x80;
        *(byte *)(iVar8 + 0x21) = *(byte *)(iVar8 + 0x21) & 0xfd | 2;
        iVar8 = iVar12 + iVar11 * 0x80;
        *(byte *)(iVar8 + 0x12) = *(byte *)(iVar8 + 0x12) & 0xfe | 1;
        uVar6 = SetRendering__7MenuObjFUc(iVar12 + iVar11 * 0x80,1);
        iVar9 = uStack_50 + iStack_40 * 0x16c;
        iVar8 = iVar9 + 0x3c;
        uVar6 = OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iVar8,iVar12 + iVar11 * 0x80,1,0,iVar8,iVar9,uVar6);
        if (uStack_30 == uVar5) {
          *(int *)(uStack_50 + iStack_40 * 0x16c + 0x158) = iVar11;
          *(uint *)(uStack_50 + iStack_40 * 0x16c + 0x16c) = uVar5;
          sStack_72 = *(short *)(iVar12 + iVar11 * 0x80 + 0x16);
          *(int *)(uStack_50 + iStack_40 * 0x16c + 0x164) = (int)sStack_72;
          *(int *)(uStack_50 + iStack_40 * 0x16c + 0x168) = (int)sStack_72;
        }
        iVar9 = iVar11 + 1;
        iVar8 = iVar12 + iVar9 * 0x80;
        (**(code **)(*(int *)(iVar8 + 8) + 0x24))(0x42400000,fStack_ac + 2.0,iVar8,uVar6);
        SetMessage__8MenuTextFPcUiUcUc(iVar12 + iVar9 * 0x80,0x6551a8,0,0,1);
        *(undefined2 *)(iVar12 + iVar9 * 0x80 + 0x1c) = 1;
        *(short *)(iVar12 + iVar9 * 0x80 + 0x1e) = (short)iVar14;
        iVar8 = iVar12 + iVar9 * 0x80;
        *(byte *)(iVar8 + 0x21) = *(byte *)(iVar8 + 0x21) & 0xfd;
        iVar8 = iVar12 + iVar9 * 0x80;
        *(byte *)(iVar8 + 0x12) = *(byte *)(iVar8 + 0x12) & 0xfe;
        SetRendering__7MenuObjFUc(iVar12 + iVar9 * 0x80,0);
        OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(uStack_50 + iStack_40 * 0x16c + 0x3c,iVar12 + iVar9 * 0x80,1,0);
        iVar11 = iVar11 + 2;
        uVar6 = (**(code **)(*(int *)(iVar4 + iVar13 * 0x60 + 8) + 0x24))(0,fStack_ac);
        SetUV__10MenuSpriteFUsUsUsUs(iVar4 + iVar13 * 0x60,1,1,0xdd,0x1c,uVar6);
        (**(code **)(*(int *)(iVar4 + iVar13 * 0x60 + 8) + 0x28))(0x435c0000,0x41d80000);
        iVar8 = iVar4 + iVar13 * 0x60;
        *(byte *)(iVar8 + 0x12) = *(byte *)(iVar8 + 0x12) & 0xfe | 1;
        SetRendering__7MenuObjFUc(iVar4 + iVar13 * 0x60,1);
        iVar13 = iVar13 + 1;
        iVar14 = iVar14 + 1;
        fStack_ac = fStack_ac + 26.0;
      }
      uVar5 = uVar5 + 1;
    }
  }
  if (((*(byte *)((int)pCGpffff86b4 +
                 (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb4) & 1) == 0)
     && (*(short *)((int)pCGpffff86b4 +
                   (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x120) == 5))
  {
    uStack_144 = GetRegCnt__9RegDatApiFii(0x36,5);
    uStack_94 = (uint)*(ushort *)(ourBtlSaveDat + 0x43e);
    iStack_148 = 0;
    for (uStack_8c = 0; uStack_8c < uStack_144; uStack_8c = uStack_8c + 1) {
      if ((uStack_94 & 1 << (uStack_8c & 0x1f)) != 0) {
        iStack_148 = iStack_148 + 1;
      }
    }
    if (iStack_148 != 0) {
      if (((int)uVar7 <= (int)uVar5) && ((int)uVar5 <= (int)(uVar7 + 3))) {
        if (uVar7 == uVar5) {
          fStack_ac = fStack_ac + 9.0;
        }
        if (iStack_9c == 0) {
          SetCSA__8FontItemFUc(iVar12 + iVar11 * 0x80,0);
          *(undefined1 *)(iVar12 + iVar11 * 0x80 + 0x5c) = 0;
          UpdateEnv__7MenuObjFv(iVar12 + iVar11 * 0x80);
          *(undefined2 *)(iVar12 + iVar11 * 0x80 + 0x16) = 0x13;
        }
        else {
          SetCSA__8FontItemFUc(iVar12 + iVar11 * 0x80,2);
          *(undefined1 *)(iVar12 + iVar11 * 0x80 + 0x5c) = 0;
          UpdateEnv__7MenuObjFv(iVar12 + iVar11 * 0x80);
          *(undefined2 *)(iVar12 + iVar11 * 0x80 + 0x16) = 0x3fb;
        }
        (**(code **)(*(int *)(iVar12 + iVar11 * 0x80 + 8) + 0x24))(0x42400000,fStack_ac + 2.0);
        SetMessage__8MenuTextFPcUiUcUc(iVar12 + iVar11 * 0x80,puRam0040ab2c[0x13],0,0,1);
        *(undefined2 *)(iVar12 + iVar11 * 0x80 + 0x1c) = 0;
        *(short *)(iVar12 + iVar11 * 0x80 + 0x1e) = (short)iVar14;
        iVar8 = iVar12 + iVar11 * 0x80;
        *(byte *)(iVar8 + 0x21) = *(byte *)(iVar8 + 0x21) & 0xfd | 2;
        iVar8 = iVar12 + iVar11 * 0x80;
        *(byte *)(iVar8 + 0x12) = *(byte *)(iVar8 + 0x12) & 0xfe | 1;
        SetRendering__7MenuObjFUc(iVar12 + iVar11 * 0x80,1);
        OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(uStack_50 + iStack_40 * 0x16c + 0x3c,iVar12 + iVar11 * 0x80,1,0);
        if (uStack_30 == uVar5) {
          *(int *)(uStack_50 + iStack_40 * 0x16c + 0x158) = iVar11;
          *(uint *)(uStack_50 + iStack_40 * 0x16c + 0x16c) = uVar5;
          sStack_74 = *(short *)(iVar12 + iVar11 * 0x80 + 0x16);
          *(int *)(uStack_50 + iStack_40 * 0x16c + 0x164) = (int)sStack_74;
          *(int *)(uStack_50 + iStack_40 * 0x16c + 0x168) = (int)sStack_74;
        }
        iVar9 = iVar11 + 1;
        (**(code **)(*(int *)(iVar12 + iVar9 * 0x80 + 8) + 0x24))(0x42400000,fStack_ac + 2.0);
        SetMessage__8MenuTextFPcUiUcUc(iVar12 + iVar9 * 0x80,0x6551a8,0,0,1);
        *(undefined2 *)(iVar12 + iVar9 * 0x80 + 0x1c) = 1;
        *(short *)(iVar12 + iVar9 * 0x80 + 0x1e) = (short)iVar14;
        iVar8 = iVar12 + iVar9 * 0x80;
        *(byte *)(iVar8 + 0x21) = *(byte *)(iVar8 + 0x21) & 0xfd;
        iVar8 = iVar12 + iVar9 * 0x80;
        *(byte *)(iVar8 + 0x12) = *(byte *)(iVar8 + 0x12) & 0xfe;
        SetRendering__7MenuObjFUc(iVar12 + iVar9 * 0x80,0);
        OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(uStack_50 + iStack_40 * 0x16c + 0x3c,iVar12 + iVar9 * 0x80,1,0);
        iVar11 = iVar11 + 2;
        (**(code **)(*(int *)(iVar4 + iVar13 * 0x60 + 8) + 0x24))(0,fStack_ac);
        SetUV__10MenuSpriteFUsUsUsUs(iVar4 + iVar13 * 0x60,1,1,0xdd,0x1c);
        (**(code **)(*(int *)(iVar4 + iVar13 * 0x60 + 8) + 0x28))(0x435c0000,0x41d80000);
        iVar8 = iVar4 + iVar13 * 0x60;
        *(byte *)(iVar8 + 0x12) = *(byte *)(iVar8 + 0x12) & 0xfe | 1;
        SetRendering__7MenuObjFUc(iVar4 + iVar13 * 0x60,1);
        iVar13 = iVar13 + 1;
        iVar14 = iVar14 + 1;
        fStack_ac = fStack_ac + 26.0;
      }
      uVar5 = uVar5 + 1;
    }
  }
  if ((((*(byte *)((int)pCGpffff86b4 +
                  (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb4) & 1) == 0
       ) && (*(short *)((int)pCGpffff86b4 +
                       (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x120) ==
             6)) && (*(char *)(ourBtlSaveDat + 0xe37) != '\0')) {
    uStack_14c = GetRegCnt__9RegDatApiFii(0x36,6);
    iStack_150 = 0;
    for (uStack_8c = 0; uStack_8c < uStack_14c; uStack_8c = uStack_8c + 1) {
      if (((long)*(char *)(ourBtlSaveDat + 0xe37) & (long)(1 << (uStack_8c & 0x1f))) != 0) {
        iStack_150 = iStack_150 + 1;
      }
    }
    iStack_154 = GetRegDat__9RegDatApiFiii(0x40,0,0xffffffffffffffff);
    if (-1 < (long)((ulong)*(byte *)(iStack_154 + *(int *)(ourBtlSocket + 0x698) * 0x10 + 4) << 0x3e)
       ) {
      iStack_150 = 0;
    }
    if (iStack_150 != 0) {
      if (((int)uVar7 <= (int)uVar5) && ((int)uVar5 <= (int)(uVar7 + 3))) {
        if (uVar7 == uVar5) {
          fStack_ac = fStack_ac + 9.0;
        }
        if (iStack_9c == 0) {
          SetCSA__8FontItemFUc(iVar12 + iVar11 * 0x80,0);
          *(undefined1 *)(iVar12 + iVar11 * 0x80 + 0x5c) = 0;
          UpdateEnv__7MenuObjFv(iVar12 + iVar11 * 0x80);
          *(undefined2 *)(iVar12 + iVar11 * 0x80 + 0x16) = 0x14;
        }
        else {
          uVar6 = SetCSA__8FontItemFUc(iVar12 + iVar11 * 0x80,2);
          *(undefined1 *)(iVar12 + iVar11 * 0x80 + 0x5c) = 0;
          UpdateEnv__7MenuObjFv(iVar12 + iVar11 * 0x80,uVar6);
          *(undefined2 *)(iVar12 + iVar11 * 0x80 + 0x16) = 0x3fc;
        }
        uVar6 = (**(code **)(*(int *)(iVar12 + iVar11 * 0x80 + 8) + 0x24))
                          (0x42400000,fStack_ac + 2.0);
        iVar8 = iVar12 + iVar11 * 0x80;
        SetMessage__8MenuTextFPcUiUcUc(iVar8,puRam0040ab2c[0x14],0,0,1,iVar8,uVar6);
        *(undefined2 *)(iVar12 + iVar11 * 0x80 + 0x1c) = 0;
        *(short *)(iVar12 + iVar11 * 0x80 + 0x1e) = (short)iVar14;
        iVar8 = iVar12 + iVar11 * 0x80;
        *(byte *)(iVar8 + 0x21) = *(byte *)(iVar8 + 0x21) & 0xfd | 2;
        iVar8 = iVar12 + iVar11 * 0x80;
        *(byte *)(iVar8 + 0x12) = *(byte *)(iVar8 + 0x12) & 0xfe | 1;
        SetRendering__7MenuObjFUc(iVar12 + iVar11 * 0x80,1);
        OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(uStack_50 + iStack_40 * 0x16c + 0x3c,iVar12 + iVar11 * 0x80,1,0);
        if (uStack_30 == uVar5) {
          *(int *)(uStack_50 + iStack_40 * 0x16c + 0x158) = iVar11;
          *(uint *)(uStack_50 + iStack_40 * 0x16c + 0x16c) = uVar5;
          sStack_76 = *(short *)(iVar12 + iVar11 * 0x80 + 0x16);
          *(int *)(uStack_50 + iStack_40 * 0x16c + 0x164) = (int)sStack_76;
          *(int *)(uStack_50 + iStack_40 * 0x16c + 0x168) = (int)sStack_76;
        }
        iVar9 = iVar11 + 1;
        uVar6 = (**(code **)(*(int *)(iVar12 + iVar9 * 0x80 + 8) + 0x24))
                          (0x42400000,fStack_ac + 2.0);
        SetMessage__8MenuTextFPcUiUcUc(iVar12 + iVar9 * 0x80,0x6551a8,0,0,1,uVar6);
        *(undefined2 *)(iVar12 + iVar9 * 0x80 + 0x1c) = 1;
        *(short *)(iVar12 + iVar9 * 0x80 + 0x1e) = (short)iVar14;
        iVar8 = iVar12 + iVar9 * 0x80;
        *(byte *)(iVar8 + 0x21) = *(byte *)(iVar8 + 0x21) & 0xfd;
        iVar8 = iVar12 + iVar9 * 0x80;
        *(byte *)(iVar8 + 0x12) = *(byte *)(iVar8 + 0x12) & 0xfe;
        SetRendering__7MenuObjFUc(iVar12 + iVar9 * 0x80,0);
        OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(uStack_50 + iStack_40 * 0x16c + 0x3c,iVar12 + iVar9 * 0x80,1,0);
        iVar11 = iVar11 + 2;
        uVar6 = (**(code **)(*(int *)(iVar4 + iVar13 * 0x60 + 8) + 0x24))(0,fStack_ac);
        SetUV__10MenuSpriteFUsUsUsUs(iVar4 + iVar13 * 0x60,1,1,0xdd,0x1c,uVar6);
        (**(code **)(*(int *)(iVar4 + iVar13 * 0x60 + 8) + 0x28))(0x435c0000,0x41d80000);
        iVar8 = iVar4 + iVar13 * 0x60;
        *(byte *)(iVar8 + 0x12) = *(byte *)(iVar8 + 0x12) & 0xfe | 1;
        SetRendering__7MenuObjFUc(iVar4 + iVar13 * 0x60,1);
        iVar13 = iVar13 + 1;
        iVar14 = iVar14 + 1;
        fStack_ac = fStack_ac + 26.0;
      }
      uVar5 = uVar5 + 1;
    }
  }
  if ((((*(byte *)((int)pCGpffff86b4 +
                  (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb4) & 1) == 0
       ) && (*(short *)((int)pCGpffff86b4 +
                       (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x120) ==
             7)) && ((*(uint *)(ourBtlSaveDat + 0xd4c) & 0x18000) != 0)) {
    if (((int)uVar7 <= (int)uVar5) && ((int)uVar5 <= (int)(uVar7 + 3))) {
      if (uVar7 == uVar5) {
        fStack_ac = fStack_ac + 9.0;
      }
      if (((*(byte *)((int)pCGpffff86b4 +
                     (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb1) & 1)
           == 0) && (iStack_9c != 0)) {
        SetCSA__8FontItemFUc(iVar12 + iVar11 * 0x80,2);
        *(undefined1 *)(iVar12 + iVar11 * 0x80 + 0x5c) = 0;
        UpdateEnv__7MenuObjFv(iVar12 + iVar11 * 0x80);
        *(undefined2 *)(iVar12 + iVar11 * 0x80 + 0x16) = 0x3fd;
      }
      else {
        SetCSA__8FontItemFUc(iVar12 + iVar11 * 0x80,0);
        *(undefined1 *)(iVar12 + iVar11 * 0x80 + 0x5c) = 0;
        UpdateEnv__7MenuObjFv(iVar12 + iVar11 * 0x80);
        *(undefined2 *)(iVar12 + iVar11 * 0x80 + 0x16) = 0x15;
      }
      (**(code **)(*(int *)(iVar12 + iVar11 * 0x80 + 8) + 0x24))(0x42400000,fStack_ac + 2.0);
      SetMessage__8MenuTextFPcUiUcUc(iVar12 + iVar11 * 0x80,puRam0040ab2c[0x15],0,0,1);
      *(undefined2 *)(iVar12 + iVar11 * 0x80 + 0x1c) = 0;
      *(short *)(iVar12 + iVar11 * 0x80 + 0x1e) = (short)iVar14;
      iVar8 = iVar12 + iVar11 * 0x80;
      *(byte *)(iVar8 + 0x21) = *(byte *)(iVar8 + 0x21) & 0xfd | 2;
      iVar8 = iVar12 + iVar11 * 0x80;
      *(byte *)(iVar8 + 0x12) = *(byte *)(iVar8 + 0x12) & 0xfe | 1;
      SetRendering__7MenuObjFUc(iVar12 + iVar11 * 0x80,1);
      OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(uStack_50 + iStack_40 * 0x16c + 0x3c,iVar12 + iVar11 * 0x80,1,0);
      if (uStack_30 == uVar5) {
        *(int *)(uStack_50 + iStack_40 * 0x16c + 0x158) = iVar11;
        *(uint *)(uStack_50 + iStack_40 * 0x16c + 0x16c) = uVar5;
        sStack_78 = *(short *)(iVar12 + iVar11 * 0x80 + 0x16);
        *(int *)(uStack_50 + iStack_40 * 0x16c + 0x164) = (int)sStack_78;
        *(int *)(uStack_50 + iStack_40 * 0x16c + 0x168) = (int)sStack_78;
      }
      iVar9 = iVar11 + 1;
      (**(code **)(*(int *)(iVar12 + iVar9 * 0x80 + 8) + 0x24))(0x42400000,fStack_ac + 2.0);
      SetMessage__8MenuTextFPcUiUcUc(iVar12 + iVar9 * 0x80,0x6551a8,0,0,1);
      *(undefined2 *)(iVar12 + iVar9 * 0x80 + 0x1c) = 1;
      *(short *)(iVar12 + iVar9 * 0x80 + 0x1e) = (short)iVar14;
      iVar8 = iVar12 + iVar9 * 0x80;
      *(byte *)(iVar8 + 0x21) = *(byte *)(iVar8 + 0x21) & 0xfd;
      iVar8 = iVar12 + iVar9 * 0x80;
      *(byte *)(iVar8 + 0x12) = *(byte *)(iVar8 + 0x12) & 0xfe;
      SetRendering__7MenuObjFUc(iVar12 + iVar9 * 0x80,0);
      uVar6 = OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(uStack_50 + iStack_40 * 0x16c + 0x3c,iVar12 + iVar9 * 0x80,1,0);
      iVar11 = iVar11 + 2;
      iVar8 = iVar4 + iVar13 * 0x60;
      (**(code **)(*(int *)(iVar8 + 8) + 0x24))(0,fStack_ac,iVar8,iVar13 * 2,uVar6);
      SetUV__10MenuSpriteFUsUsUsUs(iVar4 + iVar13 * 0x60,1,1,0xdd,0x1c);
      (**(code **)(*(int *)(iVar4 + iVar13 * 0x60 + 8) + 0x28))(0x435c0000,0x41d80000);
      iVar8 = iVar4 + iVar13 * 0x60;
      *(byte *)(iVar8 + 0x12) = *(byte *)(iVar8 + 0x12) & 0xfe | 1;
      SetRendering__7MenuObjFUc(iVar4 + iVar13 * 0x60,1);
      iVar13 = iVar13 + 1;
      iVar14 = iVar14 + 1;
      fStack_ac = fStack_ac + 26.0;
    }
    uVar5 = uVar5 + 1;
  }
  if (((*(byte *)((int)pCGpffff86b4 +
                 (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb4) & 1) == 0)
     && (((*(short *)((int)pCGpffff86b4 +
                     (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x120) == 8
          || (*(short *)((int)pCGpffff86b4 +
                        (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x120) ==
              9)) ||
         (*(short *)((int)pCGpffff86b4 +
                    (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x120) == 10)
         ))) {
    iStack_158 = GetRegDat__9RegDatApiFiii(0x36,*(undefined2 *)
                                       ((int)pCGpffff86b4 +
                                       (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) *
                                       0x10 + 0x120),0xffffffffffffffff);
    iStack_a4 = DecMPp__7CBattleFiiii
                          (pCGpffff86b4,(int)pCGpffff86b4->cActor,1,0,
                           (uint)*(ushort *)(iStack_158 + 0x1e));
    iStack_a4 = iStack_a4 / 100;
    uStack_15c = (uint)((long)iStack_a4 <=
                       (long)*(short *)((int)pCGpffff86b4 +
                                       (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) *
                                       0x10 + 0x128));
    if (*(short *)((int)pCGpffff86b4 +
                  (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x120) == 8) {
      uStack_160 = 0x16;
    }
    else if (*(short *)((int)pCGpffff86b4 +
                       (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x120) ==
             9) {
      uStack_160 = 0x17;
    }
    else {
      uStack_160 = 0x18;
    }
    if (((int)uVar7 <= (int)uVar5) && ((int)uVar5 <= (int)(uVar7 + 3))) {
      if (uVar7 == uVar5) {
        fStack_ac = fStack_ac + 9.0;
      }
      if ((uStack_15c == 0) || (iStack_9c != 0)) {
        SetCSA__8FontItemFUc(iVar12 + iVar11 * 0x80,2);
        *(undefined1 *)(iVar12 + iVar11 * 0x80 + 0x5c) = 0;
        uVar3 = UpdateEnv__7MenuObjFv(iVar12 + iVar11 * 0x80);
        *(short *)(iVar12 + iVar11 * 0x80 + 0x16) = (short)uStack_160 + 1000;
      }
      else {
        SetCSA__8FontItemFUc(iVar12 + iVar11 * 0x80,0);
        *(undefined1 *)(iVar12 + iVar11 * 0x80 + 0x5c) = 0;
        UpdateEnv__7MenuObjFv(iVar12 + iVar11 * 0x80);
        *(short *)(iVar12 + iVar11 * 0x80 + 0x16) = (short)uStack_160;
        uVar3 = uStack_160;
      }
      iVar8 = iVar12 + iVar11 * 0x80;
      (**(code **)(*(int *)(iVar8 + 8) + 0x24))(0x42400000,fStack_ac + 2.0,iVar8,uVar3);
      uVar6 = GetRegDat__9RegDatApiFiii(0xc,*(undefined2 *)(iStack_158 + 2),0xffffffffffffffff);
      SetMessage__8MenuTextFPcUiUcUc(iVar12 + iVar11 * 0x80,uVar6,0,0,1);
      *(undefined2 *)(iVar12 + iVar11 * 0x80 + 0x1c) = 0;
      *(short *)(iVar12 + iVar11 * 0x80 + 0x1e) = (short)iVar14;
      iVar8 = iVar12 + iVar11 * 0x80;
      *(byte *)(iVar8 + 0x21) = *(byte *)(iVar8 + 0x21) & 0xfd | 2;
      iVar8 = iVar12 + iVar11 * 0x80;
      *(byte *)(iVar8 + 0x12) = *(byte *)(iVar8 + 0x12) & 0xfe | 1;
      SetRendering__7MenuObjFUc(iVar12 + iVar11 * 0x80,1);
      OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(uStack_50 + iStack_40 * 0x16c + 0x3c,iVar12 + iVar11 * 0x80,1,0);
      if (uStack_30 == uVar5) {
        *(int *)(uStack_50 + iStack_40 * 0x16c + 0x158) = iVar11;
        *(uint *)(uStack_50 + iStack_40 * 0x16c + 0x16c) = uVar5;
        sStack_7a = *(short *)(iVar12 + iVar11 * 0x80 + 0x16);
        *(int *)(uStack_50 + iStack_40 * 0x16c + 0x164) = (int)sStack_7a;
        *(int *)(uStack_50 + iStack_40 * 0x16c + 0x168) = (int)sStack_7a;
      }
      iVar9 = iVar11 + 1;
      sprintf(auStack_2a0,0x6551b0,iStack_a4);
      SetMessage__8MenuTextFPcUiUcUc(iVar12 + iVar9 * 0x80,auStack_2a0,0,0,1);
      *(undefined2 *)(iVar12 + iVar9 * 0x80 + 0x1c) = 1;
      *(short *)(iVar12 + iVar9 * 0x80 + 0x1e) = (short)iVar14;
      iVar8 = iVar12 + iVar9 * 0x80;
      *(byte *)(iVar8 + 0x21) = *(byte *)(iVar8 + 0x21) & 0xfd;
      iVar8 = iVar12 + iVar9 * 0x80;
      *(byte *)(iVar8 + 0x12) = *(byte *)(iVar8 + 0x12) & 0xfe | 1;
      SetRendering__7MenuObjFUc(iVar12 + iVar9 * 0x80,1);
      OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(uStack_50 + iStack_40 * 0x16c + 0x3c,iVar12 + iVar9 * 0x80,0,0);
      fStack_1ec = *(float *)(iVar12 + iVar9 * 0x80 + 0x2c);
      fStack_b0 = fStack_1ec;
      (**(code **)(*(int *)(iVar12 + iVar9 * 0x80 + 8) + 0x24))(217.0 - fStack_1ec,fStack_ac + 2.0);
      iVar11 = iVar11 + 2;
      (**(code **)(*(int *)(iVar4 + iVar13 * 0x60 + 8) + 0x24))(0,fStack_ac);
      SetUV__10MenuSpriteFUsUsUsUs(iVar4 + iVar13 * 0x60,1,1,0xdd,0x1c);
      (**(code **)(*(int *)(iVar4 + iVar13 * 0x60 + 8) + 0x28))(0x435c0000,0x41d80000);
      iVar8 = iVar4 + iVar13 * 0x60;
      *(byte *)(iVar8 + 0x12) = *(byte *)(iVar8 + 0x12) & 0xfe | 1;
      SetRendering__7MenuObjFUc(iVar4 + iVar13 * 0x60,1);
      iVar13 = iVar13 + 1;
      iVar14 = iVar14 + 1;
      fStack_ac = fStack_ac + 26.0;
    }
    uVar5 = uVar5 + 1;
  }
  if (((*(byte *)((int)pCGpffff86b4 +
                 (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb4) & 1) == 0)
     && (*(short *)((int)pCGpffff86b4 +
                   (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x120) == 0xb)
     ) {
    if (((int)uVar7 <= (int)uVar5) && ((int)uVar5 <= (int)(uVar7 + 3))) {
      if (uVar7 == uVar5) {
        fStack_ac = fStack_ac + 9.0;
      }
      if (iStack_9c == 0) {
        *(undefined2 *)(iVar12 + iVar11 * 0x80 + 0x16) = 0x19;
        SetCSA__8FontItemFUc(iVar12 + iVar11 * 0x80,0);
        *(undefined1 *)(iVar12 + iVar11 * 0x80 + 0x5c) = 0;
        UpdateEnv__7MenuObjFv(iVar12 + iVar11 * 0x80);
      }
      else {
        *(undefined2 *)(iVar12 + iVar11 * 0x80 + 0x16) = 0x401;
        SetCSA__8FontItemFUc(iVar12 + iVar11 * 0x80,2);
        *(undefined1 *)(iVar12 + iVar11 * 0x80 + 0x5c) = 0;
        UpdateEnv__7MenuObjFv(iVar12 + iVar11 * 0x80);
      }
      (**(code **)(*(int *)(iVar12 + iVar11 * 0x80 + 8) + 0x24))(0x42400000,fStack_ac + 2.0);
      SetMessage__8MenuTextFPcUiUcUc(iVar12 + iVar11 * 0x80,puRam0040ab2c[0x19],0,0,1);
      *(undefined2 *)(iVar12 + iVar11 * 0x80 + 0x1c) = 0;
      *(short *)(iVar12 + iVar11 * 0x80 + 0x1e) = (short)iVar14;
      iVar8 = iVar12 + iVar11 * 0x80;
      *(byte *)(iVar8 + 0x21) = *(byte *)(iVar8 + 0x21) & 0xfd | 2;
      iVar8 = iVar12 + iVar11 * 0x80;
      *(byte *)(iVar8 + 0x12) = *(byte *)(iVar8 + 0x12) & 0xfe | 1;
      SetRendering__7MenuObjFUc(iVar12 + iVar11 * 0x80,1);
      OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(uStack_50 + iStack_40 * 0x16c + 0x3c,iVar12 + iVar11 * 0x80,1,0);
      if (uStack_30 == uVar5) {
        *(int *)(uStack_50 + iStack_40 * 0x16c + 0x158) = iVar11;
        *(uint *)(uStack_50 + iStack_40 * 0x16c + 0x16c) = uVar5;
        sStack_7c = *(short *)(iVar12 + iVar11 * 0x80 + 0x16);
        *(int *)(uStack_50 + iStack_40 * 0x16c + 0x164) = (int)sStack_7c;
        *(int *)(uStack_50 + iStack_40 * 0x16c + 0x168) = (int)sStack_7c;
      }
      iVar8 = iVar11 + 1;
      (**(code **)(*(int *)(iVar12 + iVar8 * 0x80 + 8) + 0x24))(0x42400000,fStack_ac + 2.0);
      SetMessage__8MenuTextFPcUiUcUc(iVar12 + iVar8 * 0x80,0x6551a8,0,0,1);
      *(undefined2 *)(iVar12 + iVar8 * 0x80 + 0x1c) = 1;
      *(short *)(iVar12 + iVar8 * 0x80 + 0x1e) = (short)iVar14;
      iVar9 = iVar12 + iVar8 * 0x80;
      *(byte *)(iVar9 + 0x21) = *(byte *)(iVar9 + 0x21) & 0xfd;
      iVar9 = iVar12 + iVar8 * 0x80;
      *(byte *)(iVar9 + 0x12) = *(byte *)(iVar9 + 0x12) & 0xfe;
      SetRendering__7MenuObjFUc(iVar12 + iVar8 * 0x80,0);
      uVar6 = OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(uStack_50 + iStack_40 * 0x16c + 0x3c,iVar12 + iVar8 * 0x80,1,0);
      iVar11 = iVar11 + 2;
      iVar8 = iVar4 + iVar13 * 0x60;
      uVar6 = (**(code **)(*(int *)(iVar8 + 8) + 0x24))(0,fStack_ac,iVar8,uVar6);
      SetUV__10MenuSpriteFUsUsUsUs(iVar4 + iVar13 * 0x60,1,1,0xdd,0x1c,uVar6);
      (**(code **)(*(int *)(iVar4 + iVar13 * 0x60 + 8) + 0x28))(0x435c0000,0x41d80000);
      iVar8 = iVar4 + iVar13 * 0x60;
      *(byte *)(iVar8 + 0x12) = *(byte *)(iVar8 + 0x12) & 0xfe | 1;
      SetRendering__7MenuObjFUc(iVar4 + iVar13 * 0x60,1);
      iVar13 = iVar13 + 1;
      iVar14 = iVar14 + 1;
      fStack_ac = fStack_ac + 26.0;
    }
    uVar5 = uVar5 + 1;
  }
  if (((*(byte *)((int)pCGpffff86b4 +
                 (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb4) & 1) == 0)
     && ((*(byte *)((int)pCGpffff86b4 +
                   (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb1) & 1) !=
         0)) {
    switch(*(undefined2 *)
            ((int)pCGpffff86b4 +
            (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xba)) {
    case 0:
    case 1:
      uStack_8c = 0xc;
      break;
    case 2:
    case 3:
      uStack_8c = 0xd;
      break;
    case 4:
    case 5:
      uStack_8c = 0xe;
      break;
    case 6:
    case 7:
      uStack_8c = 0xf;
      break;
    case 8:
    case 9:
      uStack_8c = 0x10;
      break;
    case 10:
    case 0xb:
      uStack_8c = 0x11;
      break;
    case 0xc:
    case 0xd:
      uStack_8c = 0x12;
      break;
    case 0xe:
      uStack_8c = 0x13;
      break;
    case 0xf:
      uStack_8c = 0x14;
      break;
    case 0x10:
      uStack_8c = 0x15;
    }
    iStack_164 = GetRegDat__9RegDatApiFiii(0x2c,*(undefined2 *)
                                       ((int)pCGpffff86b4 +
                                       (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) *
                                       0x10 + 0xba),0xffffffffffffffff);
    uStack_168 = GetRegDat__9RegDatApiFiii(0x36,uStack_8c,0xffffffffffffffff);
    iStack_16c = 0;
    for (uStack_8c = 0; (int)uStack_8c < 7; uStack_8c = uStack_8c + 1) {
      if ((-1 < *(short *)(iStack_164 + uStack_8c * 2 + 8)) &&
         ((long)*(char *)(iStack_164 + uStack_8c + 0x16) <=
          (long)(int)(*(byte *)(ourBtlSaveDat +
                                *(short *)((int)pCGpffff86b4 +
                                          (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor)
                                          * 0x10 + 0xba) + 0xd94) + 1))) {
        iStack_16c = iStack_16c + 1;
      }
    }
    if (iStack_16c != 0) {
      if (((int)uVar7 <= (int)uVar5) && ((int)uVar5 <= (int)(uVar7 + 3))) {
        if (uVar7 == uVar5) {
          fStack_ac = fStack_ac + 9.0;
        }
        if (iStack_9c == 0) {
          *(undefined2 *)(iVar12 + iVar11 * 0x80 + 0x16) = 0x1a;
          SetCSA__8FontItemFUc(iVar12 + iVar11 * 0x80,0);
          *(undefined1 *)(iVar12 + iVar11 * 0x80 + 0x5c) = 0;
          UpdateEnv__7MenuObjFv(iVar12 + iVar11 * 0x80);
        }
        else {
          *(undefined2 *)(iVar12 + iVar11 * 0x80 + 0x16) = 0x402;
          SetCSA__8FontItemFUc(iVar12 + iVar11 * 0x80,2);
          *(undefined1 *)(iVar12 + iVar11 * 0x80 + 0x5c) = 0;
          UpdateEnv__7MenuObjFv(iVar12 + iVar11 * 0x80);
        }
        (**(code **)(*(int *)(iVar12 + iVar11 * 0x80 + 8) + 0x24))(0x42400000,fStack_ac + 2.0);
        SetMessage__8MenuTextFPcUiUcUc(iVar12 + iVar11 * 0x80,puRam0040ab2c[0x1a],0,0,1);
        *(undefined2 *)(iVar12 + iVar11 * 0x80 + 0x1c) = 0;
        *(short *)(iVar12 + iVar11 * 0x80 + 0x1e) = (short)iVar14;
        iVar8 = iVar12 + iVar11 * 0x80;
        *(byte *)(iVar8 + 0x21) = *(byte *)(iVar8 + 0x21) & 0xfd | 2;
        iVar8 = iVar12 + iVar11 * 0x80;
        *(byte *)(iVar8 + 0x12) = *(byte *)(iVar8 + 0x12) & 0xfe | 1;
        SetRendering__7MenuObjFUc(iVar12 + iVar11 * 0x80,1);
        OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(uStack_50 + iStack_40 * 0x16c + 0x3c,iVar12 + iVar11 * 0x80,1,0);
        if (uStack_30 == uVar5) {
          *(int *)(uStack_50 + iStack_40 * 0x16c + 0x158) = iVar11;
          *(uint *)(uStack_50 + iStack_40 * 0x16c + 0x16c) = uVar5;
          sStack_7e = *(short *)(iVar12 + iVar11 * 0x80 + 0x16);
          *(int *)(uStack_50 + iStack_40 * 0x16c + 0x164) = (int)sStack_7e;
          *(int *)(uStack_50 + iStack_40 * 0x16c + 0x168) = (int)sStack_7e;
        }
        iVar8 = iVar11 + 1;
        uVar6 = (**(code **)(*(int *)(iVar12 + iVar8 * 0x80 + 8) + 0x24))
                          (0x42400000,fStack_ac + 2.0);
        SetMessage__8MenuTextFPcUiUcUc(iVar12 + iVar8 * 0x80,0x6551a8,0,0,1,1,uVar6);
        *(undefined2 *)(iVar12 + iVar8 * 0x80 + 0x1c) = 1;
        *(short *)(iVar12 + iVar8 * 0x80 + 0x1e) = (short)iVar14;
        iVar9 = iVar12 + iVar8 * 0x80;
        *(byte *)(iVar9 + 0x21) = *(byte *)(iVar9 + 0x21) & 0xfd;
        iVar9 = iVar12 + iVar8 * 0x80;
        *(byte *)(iVar9 + 0x12) = *(byte *)(iVar9 + 0x12) & 0xfe;
        SetRendering__7MenuObjFUc(iVar12 + iVar8 * 0x80,0);
        OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(uStack_50 + iStack_40 * 0x16c + 0x3c,iVar12 + iVar8 * 0x80,1,0);
        iVar11 = iVar11 + 2;
        uVar6 = (**(code **)(*(int *)(iVar4 + iVar13 * 0x60 + 8) + 0x24))(0,fStack_ac);
        SetUV__10MenuSpriteFUsUsUsUs(iVar4 + iVar13 * 0x60,1,1,0xdd,0x1c,uVar6);
        (**(code **)(*(int *)(iVar4 + iVar13 * 0x60 + 8) + 0x28))(0x435c0000,0x41d80000);
        iVar8 = iVar4 + iVar13 * 0x60;
        *(byte *)(iVar8 + 0x12) = *(byte *)(iVar8 + 0x12) & 0xfe | 1;
        SetRendering__7MenuObjFUc(iVar4 + iVar13 * 0x60,1);
        iVar13 = iVar13 + 1;
        iVar14 = iVar14 + 1;
        fStack_ac = fStack_ac + 26.0;
      }
      uVar5 = uVar5 + 1;
    }
  }
  if ((*(byte *)((int)pCGpffff86b4 +
                (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb4) & 1) == 0)
  {
    iVar8 = GetRegDat__9RegDatApiFiii(0x37,0,0xffffffffffffffff);
    uStack_170 = GetRegDat__9RegDatApiFiii(0x38,0,0xffffffffffffffff);
    for (uStack_8c = 0; (int)uStack_8c < 0x20; uStack_8c = uStack_8c + 1) {
      aiStack_420[uStack_8c] = 0;
    }
    iStack_174 = 0;
    for (uStack_8c = 0; (int)uStack_8c < 8; uStack_8c = uStack_8c + 1) {
      if (-1 < *(char *)(ourBtlSaveDat +
                         *(short *)((int)pCGpffff86b4 +
                                   (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10
                                   + 0x120) * 0xc0 + uStack_8c + 0x76)) {
        uStack_90 = (uint)*(char *)(ourBtlSaveDat +
                                    *(short *)((int)pCGpffff86b4 +
                                              (pCGpffff86b4->cActor * 0x50 -
                                              (int)pCGpffff86b4->cActor) * 0x10 + 0x120) * 0xc0 +
                                    uStack_8c + 0x76);
        if (-1 < *(short *)(iVar8 + uStack_90 * 0x1c + 8)) {
          if ((*(byte *)(iVar8 + uStack_90 * 0x1c + 6) & 1) == 0) {
LAB_005b8028:
            for (iVar9 = 0;
                (iVar9 < iStack_174 &&
                ((long)aiStack_420[iVar9] != (long)*(short *)(iVar8 + uStack_90 * 0x1c + 8)));
                iVar9 = iVar9 + 1) {
            }
            if (iVar9 < iStack_174) {
              aiStack_4a0[iVar9] = aiStack_4a0[iVar9] + 1;
            }
            else {
              aiStack_420[iStack_174] = (int)*(short *)(iVar8 + uStack_90 * 0x1c + 8);
              aiStack_4a0[iStack_174] = 1;
              iStack_174 = iStack_174 + 1;
            }
          }
          else if ((*(byte *)(iVar8 + uStack_90 * 0x1c + 6) & 1) != 0) {
            uVar10 = uStack_90 & 7;
            if (((int)uStack_90 < 0) && (uVar10 != 0)) {
              uVar10 = uVar10 - 8;
            }
            if (((uint)*(byte *)(ourBtlSaveDat + (uint)*(byte *)(ourBtlSaveDat + 2) * 0x200 +
                                 ((int)uStack_90 >> 3) + 0xaae) & 1 << (uVar10 & 0x1f)) != 0)
            goto LAB_005b8028;
          }
        }
        if (-1 < *(short *)(iVar8 + uStack_90 * 0x1c + 10)) {
          if ((long)((ulong)*(byte *)(iVar8 + uStack_90 * 0x1c + 6) << 0x3e) < 0) {
            if ((long)((ulong)*(byte *)(iVar8 + uStack_90 * 0x1c + 6) << 0x3e) < 0) {
              uVar10 = uStack_90 & 7;
              if (((int)uStack_90 < 0) && (uVar10 != 0)) {
                uVar10 = uVar10 - 8;
              }
              if (((uint)*(byte *)(ourBtlSaveDat + (uint)*(byte *)(ourBtlSaveDat + 2) * 0x200 +
                                   ((int)uStack_90 >> 3) + 0xaae) & 1 << (uVar10 & 0x1f)) != 0)
              goto LAB_005b81e8;
            }
          }
          else {
LAB_005b81e8:
            for (iVar9 = 0;
                (iVar9 < iStack_174 &&
                ((long)aiStack_420[iVar9] != (long)*(short *)(iVar8 + uStack_90 * 0x1c + 10)));
                iVar9 = iVar9 + 1) {
            }
            if (iVar9 < iStack_174) {
              aiStack_4a0[iVar9] = aiStack_4a0[iVar9] + 1;
            }
            else {
              aiStack_420[iStack_174] = (int)*(short *)(iVar8 + uStack_90 * 0x1c + 10);
              aiStack_4a0[iStack_174] = 1;
              iStack_174 = iStack_174 + 1;
            }
          }
        }
        if (-1 < *(short *)(iVar8 + uStack_90 * 0x1c + 0xc)) {
          if ((long)((ulong)*(byte *)(iVar8 + uStack_90 * 0x1c + 6) << 0x3d) < 0) {
            if ((long)((ulong)*(byte *)(iVar8 + uStack_90 * 0x1c + 6) << 0x3d) < 0) {
              uVar10 = uStack_90 & 7;
              if (((int)uStack_90 < 0) && (uVar10 != 0)) {
                uVar10 = uVar10 - 8;
              }
              if (((uint)*(byte *)(ourBtlSaveDat + (uint)*(byte *)(ourBtlSaveDat + 2) * 0x200 +
                                   ((int)uStack_90 >> 3) + 0xaae) & 1 << (uVar10 & 0x1f)) != 0)
              goto LAB_005b83a8;
            }
          }
          else {
LAB_005b83a8:
            for (iVar9 = 0;
                (iVar9 < iStack_174 &&
                ((long)aiStack_420[iVar9] != (long)*(short *)(iVar8 + uStack_90 * 0x1c + 0xc)));
                iVar9 = iVar9 + 1) {
            }
            if (iVar9 < iStack_174) {
              aiStack_4a0[iVar9] = aiStack_4a0[iVar9] + 1;
            }
            else {
              aiStack_420[iStack_174] = (int)*(short *)(iVar8 + uStack_90 * 0x1c + 0xc);
              aiStack_4a0[iStack_174] = 1;
              iStack_174 = iStack_174 + 1;
            }
          }
        }
        if (-1 < *(short *)(iVar8 + uStack_90 * 0x1c + 0xe)) {
          if ((long)((ulong)*(byte *)(iVar8 + uStack_90 * 0x1c + 6) << 0x3c) < 0) {
            if ((long)((ulong)*(byte *)(iVar8 + uStack_90 * 0x1c + 6) << 0x3c) < 0) {
              uVar10 = uStack_90 & 7;
              if (((int)uStack_90 < 0) && (uVar10 != 0)) {
                uVar10 = uVar10 - 8;
              }
              if (((uint)*(byte *)(ourBtlSaveDat + (uint)*(byte *)(ourBtlSaveDat + 2) * 0x200 +
                                   ((int)uStack_90 >> 3) + 0xaae) & 1 << (uVar10 & 0x1f)) != 0)
              goto LAB_005b8560;
            }
          }
          else {
LAB_005b8560:
            for (iVar9 = 0;
                (iVar9 < iStack_174 &&
                ((long)aiStack_420[iVar9] != (long)*(short *)(iVar8 + uStack_90 * 0x1c + 0xe)));
                iVar9 = iVar9 + 1) {
            }
            if (iVar9 < iStack_174) {
              aiStack_4a0[iVar9] = aiStack_4a0[iVar9] + 1;
            }
            else {
              aiStack_420[iStack_174] = (int)*(short *)(iVar8 + uStack_90 * 0x1c + 0xe);
              aiStack_4a0[iStack_174] = 1;
              iStack_174 = iStack_174 + 1;
            }
          }
        }
      }
    }
    sVar2 = *(short *)((int)pCGpffff86b4 +
                      (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x120);
    if (((sVar2 == 10) || (sVar2 == 9)) || (sVar2 == 8)) {
      iStack_174 = 0;
    }
    else if ((sVar2 == 6) &&
            (iStack_178 = GetRegDat__9RegDatApiFiii(0x40,0,0xffffffffffffffff),
            -1 < (long)((ulong)*(byte *)(iStack_178 + *(int *)(ourBtlSocket + 0x698) * 0x10 + 4) <<
                       0x3e))) {
      iStack_174 = 0;
    }
    if (iStack_174 != 0) {
      if (((int)uVar7 <= (int)uVar5) && ((int)uVar5 <= (int)(uVar7 + 3))) {
        if (uVar7 == uVar5) {
          fStack_ac = fStack_ac + 9.0;
        }
        if (iStack_9c == 0) {
          SetCSA__8FontItemFUc(iVar12 + iVar11 * 0x80,0);
          *(undefined1 *)(iVar12 + iVar11 * 0x80 + 0x5c) = 0;
          UpdateEnv__7MenuObjFv(iVar12 + iVar11 * 0x80);
          *(undefined2 *)(iVar12 + iVar11 * 0x80 + 0x16) = 6;
        }
        else {
          SetCSA__8FontItemFUc(iVar12 + iVar11 * 0x80,2);
          *(undefined1 *)(iVar12 + iVar11 * 0x80 + 0x5c) = 0;
          UpdateEnv__7MenuObjFv(iVar12 + iVar11 * 0x80);
          *(undefined2 *)(iVar12 + iVar11 * 0x80 + 0x16) = 0x3ee;
        }
        (**(code **)(*(int *)(iVar12 + iVar11 * 0x80 + 8) + 0x24))(0x42400000,fStack_ac + 2.0);
        SetMessage__8MenuTextFPcUiUcUc(iVar12 + iVar11 * 0x80,puRam0040ab2c[6],0,0,1);
        *(undefined2 *)(iVar12 + iVar11 * 0x80 + 0x1c) = 0;
        *(short *)(iVar12 + iVar11 * 0x80 + 0x1e) = (short)iVar14;
        iVar8 = iVar12 + iVar11 * 0x80;
        *(byte *)(iVar8 + 0x21) = *(byte *)(iVar8 + 0x21) & 0xfd | 2;
        iVar8 = iVar12 + iVar11 * 0x80;
        *(byte *)(iVar8 + 0x12) = *(byte *)(iVar8 + 0x12) & 0xfe | 1;
        SetRendering__7MenuObjFUc(iVar12 + iVar11 * 0x80,1);
        OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(uStack_50 + iStack_40 * 0x16c + 0x3c,iVar12 + iVar11 * 0x80,1,0);
        if (uStack_30 == uVar5) {
          *(int *)(uStack_50 + iStack_40 * 0x16c + 0x158) = iVar11;
          *(uint *)(uStack_50 + iStack_40 * 0x16c + 0x16c) = uVar5;
          sStack_80 = *(short *)(iVar12 + iVar11 * 0x80 + 0x16);
          *(int *)(uStack_50 + iStack_40 * 0x16c + 0x164) = (int)sStack_80;
          *(int *)(uStack_50 + iStack_40 * 0x16c + 0x168) = (int)sStack_80;
        }
        iVar9 = iVar11 + 1;
        (**(code **)(*(int *)(iVar12 + iVar9 * 0x80 + 8) + 0x24))(0x42400000,fStack_ac + 2.0);
        SetMessage__8MenuTextFPcUiUcUc(iVar12 + iVar9 * 0x80,0x6551a8,0,0,1);
        *(undefined2 *)(iVar12 + iVar9 * 0x80 + 0x1c) = 1;
        *(short *)(iVar12 + iVar9 * 0x80 + 0x1e) = (short)iVar14;
        iVar8 = iVar12 + iVar9 * 0x80;
        *(byte *)(iVar8 + 0x21) = *(byte *)(iVar8 + 0x21) & 0xfd;
        iVar8 = iVar12 + iVar9 * 0x80;
        *(byte *)(iVar8 + 0x12) = *(byte *)(iVar8 + 0x12) & 0xfe;
        SetRendering__7MenuObjFUc(iVar12 + iVar9 * 0x80,0);
        OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(uStack_50 + iStack_40 * 0x16c + 0x3c,iVar12 + iVar9 * 0x80,1,0);
        iVar11 = iVar11 + 2;
        (**(code **)(*(int *)(iVar4 + iVar13 * 0x60 + 8) + 0x24))(0,fStack_ac);
        SetUV__10MenuSpriteFUsUsUsUs(iVar4 + iVar13 * 0x60,1,1,0xdd,0x1c);
        (**(code **)(*(int *)(iVar4 + iVar13 * 0x60 + 8) + 0x28))(0x435c0000,0x41d80000);
        iVar8 = iVar4 + iVar13 * 0x60;
        *(byte *)(iVar8 + 0x12) = *(byte *)(iVar8 + 0x12) & 0xfe | 1;
        SetRendering__7MenuObjFUc(iVar4 + iVar13 * 0x60,1);
        iVar13 = iVar13 + 1;
        iVar14 = iVar14 + 1;
        fStack_ac = fStack_ac + 26.0;
      }
      uVar5 = uVar5 + 1;
    }
  }
  if ((*(byte *)((int)pCGpffff86b4 +
                (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb4) & 1) == 0)
  {
    iStack_17c = 0;
    uStack_180 = GetRegCnt__9RegDatApiFii(0x33,0xffffffffffffffff);
    iStack_184 = GetRegDat__9RegDatApiFiii(0x33,0,0xffffffffffffffff);
    for (uStack_8c = 0; uStack_8c < uStack_180; uStack_8c = uStack_8c + 1) {
      if (((*(char *)(ourBtlSaveDat + (uint)*(byte *)(ourBtlSaveDat + 2) * 0x200 + uStack_8c + 0x944) !=
            '\0') && (((ulong)*(byte *)(iStack_184 + uStack_8c * 0x30 + 4) & 0x1f) >> 3 != 0)) &&
         (((ulong)*(byte *)(iStack_184 + uStack_8c * 0x30 + 4) & 0x1f) >> 3 != 3)) {
        iStack_17c = iStack_17c + 1;
      }
    }
    if (iStack_17c != 0) {
      if (((int)uVar7 <= (int)uVar5) && ((int)uVar5 <= (int)(uVar7 + 3))) {
        if (uVar7 == uVar5) {
          fStack_ac = fStack_ac + 9.0;
        }
        SetCSA__8FontItemFUc(iVar12 + iVar11 * 0x80,0);
        *(undefined1 *)(iVar12 + iVar11 * 0x80 + 0x5c) = 0;
        UpdateEnv__7MenuObjFv(iVar12 + iVar11 * 0x80);
        *(undefined2 *)(iVar12 + iVar11 * 0x80 + 0x16) = 8;
        (**(code **)(*(int *)(iVar12 + iVar11 * 0x80 + 8) + 0x24))(0x42400000,fStack_ac + 2.0);
        SetMessage__8MenuTextFPcUiUcUc(iVar12 + iVar11 * 0x80,puRam0040ab2c[8],0,0,1);
        *(undefined2 *)(iVar12 + iVar11 * 0x80 + 0x1c) = 0;
        *(short *)(iVar12 + iVar11 * 0x80 + 0x1e) = (short)iVar14;
        iVar8 = iVar12 + iVar11 * 0x80;
        *(byte *)(iVar8 + 0x21) = *(byte *)(iVar8 + 0x21) & 0xfd | 2;
        iVar8 = iVar12 + iVar11 * 0x80;
        *(byte *)(iVar8 + 0x12) = *(byte *)(iVar8 + 0x12) & 0xfe | 1;
        SetRendering__7MenuObjFUc(iVar12 + iVar11 * 0x80,1);
        OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(uStack_50 + iStack_40 * 0x16c + 0x3c,iVar12 + iVar11 * 0x80,1,0);
        if (uStack_30 == uVar5) {
          *(int *)(uStack_50 + iStack_40 * 0x16c + 0x158) = iVar11;
          *(uint *)(uStack_50 + iStack_40 * 0x16c + 0x16c) = uVar5;
          sStack_82 = *(short *)(iVar12 + iVar11 * 0x80 + 0x16);
          *(int *)(uStack_50 + iStack_40 * 0x16c + 0x164) = (int)sStack_82;
          *(int *)(uStack_50 + iStack_40 * 0x16c + 0x168) = (int)sStack_82;
        }
        iVar9 = iVar11 + 1;
        (**(code **)(*(int *)(iVar12 + iVar9 * 0x80 + 8) + 0x24))(0x42400000,fStack_ac + 2.0);
        SetMessage__8MenuTextFPcUiUcUc(iVar12 + iVar9 * 0x80,0x6551a8,0,0,1);
        *(undefined2 *)(iVar12 + iVar9 * 0x80 + 0x1c) = 1;
        *(short *)(iVar12 + iVar9 * 0x80 + 0x1e) = (short)iVar14;
        iVar8 = iVar12 + iVar9 * 0x80;
        *(byte *)(iVar8 + 0x21) = *(byte *)(iVar8 + 0x21) & 0xfd;
        iVar8 = iVar12 + iVar9 * 0x80;
        *(byte *)(iVar8 + 0x12) = *(byte *)(iVar8 + 0x12) & 0xfe;
        SetRendering__7MenuObjFUc(iVar12 + iVar9 * 0x80,0);
        OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(uStack_50 + iStack_40 * 0x16c + 0x3c,iVar12 + iVar9 * 0x80,1,0);
        iVar11 = iVar11 + 2;
        (**(code **)(*(int *)(iVar4 + iVar13 * 0x60 + 8) + 0x24))(0,fStack_ac);
        uVar6 = SetUV__10MenuSpriteFUsUsUsUs(iVar4 + iVar13 * 0x60,1,1,0xdd,0x1c);
        iVar8 = iVar4 + iVar13 * 0x60;
        (**(code **)(*(int *)(iVar8 + 8) + 0x28))(0x435c0000,0x41d80000,iVar8,uVar6);
        iVar8 = iVar4 + iVar13 * 0x60;
        *(byte *)(iVar8 + 0x12) = *(byte *)(iVar8 + 0x12) & 0xfe | 1;
        SetRendering__7MenuObjFUc(iVar4 + iVar13 * 0x60,1);
        iVar13 = iVar13 + 1;
        iVar14 = iVar14 + 1;
        fStack_ac = fStack_ac + 26.0;
      }
      uVar5 = uVar5 + 1;
    }
  }
  if (((int)uVar7 <= (int)uVar5) && ((int)uVar5 <= (int)(uVar7 + 3))) {
    if (uVar7 == uVar5) {
      fStack_ac = fStack_ac + 9.0;
    }
    SetCSA__8FontItemFUc(iVar12 + iVar11 * 0x80,0);
    *(undefined1 *)(iVar12 + iVar11 * 0x80 + 0x5c) = 0;
    UpdateEnv__7MenuObjFv(iVar12 + iVar11 * 0x80);
    *(undefined2 *)(iVar12 + iVar11 * 0x80 + 0x16) = 9;
    (**(code **)(*(int *)(iVar12 + iVar11 * 0x80 + 8) + 0x24))(0x42400000,fStack_ac + 2.0);
    SetMessage__8MenuTextFPcUiUcUc(iVar12 + iVar11 * 0x80,puRam0040ab2c[9],0,0,1);
    *(undefined2 *)(iVar12 + iVar11 * 0x80 + 0x1c) = 0;
    *(short *)(iVar12 + iVar11 * 0x80 + 0x1e) = (short)iVar14;
    iVar8 = iVar12 + iVar11 * 0x80;
    *(byte *)(iVar8 + 0x21) = *(byte *)(iVar8 + 0x21) & 0xfd | 2;
    iVar8 = iVar12 + iVar11 * 0x80;
    *(byte *)(iVar8 + 0x12) = *(byte *)(iVar8 + 0x12) & 0xfe | 1;
    SetRendering__7MenuObjFUc(iVar12 + iVar11 * 0x80,1);
    OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(uStack_50 + iStack_40 * 0x16c + 0x3c,iVar12 + iVar11 * 0x80,1,0);
    if (uStack_30 == uVar5) {
      *(int *)(uStack_50 + iStack_40 * 0x16c + 0x158) = iVar11;
      *(uint *)(uStack_50 + iStack_40 * 0x16c + 0x16c) = uVar5;
      sStack_84 = *(short *)(iVar12 + iVar11 * 0x80 + 0x16);
      *(int *)(uStack_50 + iStack_40 * 0x16c + 0x164) = (int)sStack_84;
      *(int *)(uStack_50 + iStack_40 * 0x16c + 0x168) = (int)sStack_84;
    }
    iVar9 = iVar11 + 1;
    (**(code **)(*(int *)(iVar12 + iVar9 * 0x80 + 8) + 0x24))(0x42400000,fStack_ac + 2.0);
    SetMessage__8MenuTextFPcUiUcUc(iVar12 + iVar9 * 0x80,0x6551a8,0,0,1);
    *(undefined2 *)(iVar12 + iVar9 * 0x80 + 0x1c) = 1;
    *(short *)(iVar12 + iVar9 * 0x80 + 0x1e) = (short)iVar14;
    iVar8 = iVar12 + iVar9 * 0x80;
    *(byte *)(iVar8 + 0x21) = *(byte *)(iVar8 + 0x21) & 0xfd;
    iVar8 = iVar12 + iVar9 * 0x80;
    *(byte *)(iVar8 + 0x12) = *(byte *)(iVar8 + 0x12) & 0xfe;
    SetRendering__7MenuObjFUc(iVar12 + iVar9 * 0x80,0);
    uVar6 = OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(uStack_50 + iStack_40 * 0x16c + 0x3c,iVar12 + iVar9 * 0x80,1,0);
    iVar11 = iVar11 + 2;
    iVar8 = iVar4 + iVar13 * 0x60;
    (**(code **)(*(int *)(iVar8 + 8) + 0x24))(0,fStack_ac,iVar8,iVar13 * 2,uVar6);
    SetUV__10MenuSpriteFUsUsUsUs(iVar4 + iVar13 * 0x60,1,1,0xdd,0x1c);
    (**(code **)(*(int *)(iVar4 + iVar13 * 0x60 + 8) + 0x28))(0x435c0000,0x41d80000);
    iVar8 = iVar4 + iVar13 * 0x60;
    *(byte *)(iVar8 + 0x12) = *(byte *)(iVar8 + 0x12) & 0xfe | 1;
    SetRendering__7MenuObjFUc(iVar4 + iVar13 * 0x60,1);
    iVar13 = iVar13 + 1;
    iVar14 = iVar14 + 1;
    fStack_ac = fStack_ac + 26.0;
  }
  uVar10 = uVar5 + 1;
  iStack_120 = 0;
  iStack_124 = 0;
  for (uStack_8c = 0; (int)uStack_8c < 0xc; uStack_8c = uStack_8c + 1) {
    if (((((((pCGpffff86b4->aChr[uStack_8c].bFlagsA & 1) != 0) &&
           ((long)((ulong)pCGpffff86b4->aChr[uStack_8c].bFlagsA << 0x3e) < 0)) &&
          (-1 < (long)((ulong)pCGpffff86b4->aChr[uStack_8c].bFlagsA2 << 0x3d))) &&
         (((long)(int)uStack_8c != (long)pCGpffff86b4->cActor &&
          ((*(byte *)((int)pCGpffff86b4 +
                     (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb4) & 1)
           == (pCGpffff86b4->aChr[uStack_8c].bFlagsB & 1))))) &&
        (iStack_120 = iStack_120 + 1, 0 < pCGpffff86b4->aChr[uStack_8c].nHp)) &&
       ((((*(byte *)((int)pCGpffff86b4 +
                    (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb4) & 1) !=
          0 || (0 < pCGpffff86b4->aChr[uStack_8c].nSp)) ||
        ((pCGpffff86b4->aChr[uStack_8c].nCharId == 8 ||
         ((pCGpffff86b4->aChr[uStack_8c].nCharId == 9 ||
          (pCGpffff86b4->aChr[uStack_8c].nCharId == 10)))))))) {
      uStack_90 = 0;
      while (((int)uStack_90 < 0x20 &&
             (((pCGpffff86b4->aChr[uStack_8c].aStatus[uStack_90].bKind != 0x47 ||
               (((ulong)pCGpffff86b4->aChr[uStack_8c].aStatus[uStack_90].bFlags & 0x1f) >> 2 != 0))
              || ((pCGpffff86b4->aChr[uStack_8c].aStatus[uStack_90].nValue & 0x24U) == 0))))) {
        uStack_90 = uStack_90 + 1;
      }
      if (0x1f < (int)uStack_90) {
        iStack_124 = iStack_124 + 1;
      }
    }
  }
  if ((iStack_120 != 0) && ((*(byte *)(ourBtlSaveDat + 3) & 1) != 0)) {
    if (((int)uVar7 <= (int)uVar10) && ((int)uVar10 <= (int)(uVar7 + 3))) {
      if (uVar7 == uVar10) {
        fStack_ac = fStack_ac + 9.0;
      }
      if (iStack_124 == 0) {
        SetCSA__8FontItemFUc(iVar12 + iVar11 * 0x80,2);
        *(undefined1 *)(iVar12 + iVar11 * 0x80 + 0x5c) = 0;
        UpdateEnv__7MenuObjFv(iVar12 + iVar11 * 0x80);
        *(undefined2 *)(iVar12 + iVar11 * 0x80 + 0x16) = 0x3f2;
      }
      else {
        SetCSA__8FontItemFUc(iVar12 + iVar11 * 0x80,0);
        *(undefined1 *)(iVar12 + iVar11 * 0x80 + 0x5c) = 0;
        UpdateEnv__7MenuObjFv(iVar12 + iVar11 * 0x80);
        *(undefined2 *)(iVar12 + iVar11 * 0x80 + 0x16) = 10;
      }
      (**(code **)(*(int *)(iVar12 + iVar11 * 0x80 + 8) + 0x24))(0x42400000,fStack_ac + 2.0);
      SetMessage__8MenuTextFPcUiUcUc(iVar12 + iVar11 * 0x80,puRam0040ab2c[10],0,0,1);
      *(undefined2 *)(iVar12 + iVar11 * 0x80 + 0x1c) = 0;
      *(short *)(iVar12 + iVar11 * 0x80 + 0x1e) = (short)iVar14;
      iVar8 = iVar12 + iVar11 * 0x80;
      *(byte *)(iVar8 + 0x21) = *(byte *)(iVar8 + 0x21) & 0xfd | 2;
      iVar8 = iVar12 + iVar11 * 0x80;
      *(byte *)(iVar8 + 0x12) = *(byte *)(iVar8 + 0x12) & 0xfe | 1;
      SetRendering__7MenuObjFUc(iVar12 + iVar11 * 0x80,1);
      OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(uStack_50 + iStack_40 * 0x16c + 0x3c,iVar12 + iVar11 * 0x80,1,0);
      if (uStack_30 == uVar10) {
        *(int *)(uStack_50 + iStack_40 * 0x16c + 0x158) = iVar11;
        *(uint *)(uStack_50 + iStack_40 * 0x16c + 0x16c) = uVar10;
        sStack_86 = *(short *)(iVar12 + iVar11 * 0x80 + 0x16);
        *(int *)(uStack_50 + iStack_40 * 0x16c + 0x164) = (int)sStack_86;
        *(int *)(uStack_50 + iStack_40 * 0x16c + 0x168) = (int)sStack_86;
      }
      iVar8 = iVar11 + 1;
      (**(code **)(*(int *)(iVar12 + iVar8 * 0x80 + 8) + 0x24))(0x42400000,fStack_ac + 2.0);
      SetMessage__8MenuTextFPcUiUcUc(iVar12 + iVar8 * 0x80,0x6551a8,0,0,1);
      *(undefined2 *)(iVar12 + iVar8 * 0x80 + 0x1c) = 1;
      *(short *)(iVar12 + iVar8 * 0x80 + 0x1e) = (short)iVar14;
      iVar9 = iVar12 + iVar8 * 0x80;
      *(byte *)(iVar9 + 0x21) = *(byte *)(iVar9 + 0x21) & 0xfd;
      iVar9 = iVar12 + iVar8 * 0x80;
      *(byte *)(iVar9 + 0x12) = *(byte *)(iVar9 + 0x12) & 0xfe;
      SetRendering__7MenuObjFUc(iVar12 + iVar8 * 0x80,0);
      OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(uStack_50 + iStack_40 * 0x16c + 0x3c,iVar12 + iVar8 * 0x80,1,0);
      iVar11 = iVar11 + 2;
      (**(code **)(*(int *)(iVar4 + iVar13 * 0x60 + 8) + 0x24))(0,fStack_ac);
      SetUV__10MenuSpriteFUsUsUsUs(iVar4 + iVar13 * 0x60,1,1,0xdd,0x1c);
      (**(code **)(*(int *)(iVar4 + iVar13 * 0x60 + 8) + 0x28))(0x435c0000,0x41d80000);
      iVar8 = iVar4 + iVar13 * 0x60;
      *(byte *)(iVar8 + 0x12) = *(byte *)(iVar8 + 0x12) & 0xfe | 1;
      SetRendering__7MenuObjFUc(iVar4 + iVar13 * 0x60,1);
      iVar13 = iVar13 + 1;
      iVar14 = iVar14 + 1;
      fStack_ac = fStack_ac + 26.0;
    }
    uVar10 = uVar5 + 2;
  }
  if (((int)uVar7 <= (int)uVar10) && ((int)uVar10 <= (int)(uVar7 + 3))) {
    if (uVar7 == uVar10) {
      fStack_ac = fStack_ac + 9.0;
    }
    SetCSA__8FontItemFUc(iVar12 + iVar11 * 0x80,0);
    *(undefined1 *)(iVar12 + iVar11 * 0x80 + 0x5c) = 0;
    UpdateEnv__7MenuObjFv(iVar12 + iVar11 * 0x80);
    *(undefined2 *)(iVar12 + iVar11 * 0x80 + 0x16) = 0xb;
    (**(code **)(*(int *)(iVar12 + iVar11 * 0x80 + 8) + 0x24))(0x42400000,fStack_ac + 2.0);
    SetMessage__8MenuTextFPcUiUcUc(iVar12 + iVar11 * 0x80,puRam0040ab2c[0xb],0,0,1);
    *(undefined2 *)(iVar12 + iVar11 * 0x80 + 0x1c) = 0;
    *(short *)(iVar12 + iVar11 * 0x80 + 0x1e) = (short)iVar14;
    iVar8 = iVar12 + iVar11 * 0x80;
    *(byte *)(iVar8 + 0x21) = *(byte *)(iVar8 + 0x21) & 0xfd | 2;
    iVar8 = iVar12 + iVar11 * 0x80;
    *(byte *)(iVar8 + 0x12) = *(byte *)(iVar8 + 0x12) & 0xfe | 1;
    SetRendering__7MenuObjFUc(iVar12 + iVar11 * 0x80,1);
    OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(uStack_50 + iStack_40 * 0x16c + 0x3c,iVar12 + iVar11 * 0x80,1,0);
    if (uStack_30 == uVar10) {
      *(int *)(uStack_50 + iStack_40 * 0x16c + 0x158) = iVar11;
      *(uint *)(uStack_50 + iStack_40 * 0x16c + 0x16c) = uVar10;
      sStack_88 = *(short *)(iVar12 + iVar11 * 0x80 + 0x16);
      *(int *)(uStack_50 + iStack_40 * 0x16c + 0x164) = (int)sStack_88;
      *(int *)(uStack_50 + iStack_40 * 0x16c + 0x168) = (int)sStack_88;
    }
    iVar8 = iVar11 + 1;
    (**(code **)(*(int *)(iVar12 + iVar8 * 0x80 + 8) + 0x24))(0x42400000,fStack_ac + 2.0);
    SetMessage__8MenuTextFPcUiUcUc(iVar12 + iVar8 * 0x80,0x6551a8,0,0,1);
    *(undefined2 *)(iVar12 + iVar8 * 0x80 + 0x1c) = 1;
    *(short *)(iVar12 + iVar8 * 0x80 + 0x1e) = (short)iVar14;
    iVar9 = iVar12 + iVar8 * 0x80;
    *(byte *)(iVar9 + 0x21) = *(byte *)(iVar9 + 0x21) & 0xfd;
    iVar9 = iVar12 + iVar8 * 0x80;
    *(byte *)(iVar9 + 0x12) = *(byte *)(iVar9 + 0x12) & 0xfe;
    SetRendering__7MenuObjFUc(iVar12 + iVar8 * 0x80,0);
    uVar6 = OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(uStack_50 + iStack_40 * 0x16c + 0x3c,iVar12 + iVar8 * 0x80,1,0);
    iVar11 = iVar11 + 2;
    iVar8 = iVar4 + iVar13 * 0x60;
    uVar6 = (**(code **)(*(int *)(iVar8 + 8) + 0x24))(0,fStack_ac,iVar8,uVar6);
    SetUV__10MenuSpriteFUsUsUsUs(iVar4 + iVar13 * 0x60,1,1,0xdd,0x1c,uVar6);
    (**(code **)(*(int *)(iVar4 + iVar13 * 0x60 + 8) + 0x28))(0x435c0000,0x41d80000);
    iVar8 = iVar4 + iVar13 * 0x60;
    *(byte *)(iVar8 + 0x12) = *(byte *)(iVar8 + 0x12) & 0xfe | 1;
    SetRendering__7MenuObjFUc(iVar4 + iVar13 * 0x60,1);
    iVar13 = iVar13 + 1;
    iVar14 = iVar14 + 1;
    fStack_ac = fStack_ac + 26.0;
  }
  for (; iVar14 < 4; iVar14 = iVar14 + 1) {
    (**(code **)(*(int *)(iVar12 + iVar11 * 0x80 + 8) + 0x24))(0x42400000,fStack_ac + 2.0);
    SetMessage__8MenuTextFPcUiUcUc(iVar12 + iVar11 * 0x80,0x6551a8,0,0,1);
    *(undefined2 *)(iVar12 + iVar11 * 0x80 + 0x1c) = 0;
    *(short *)(iVar12 + iVar11 * 0x80 + 0x1e) = (short)iVar14;
    iVar8 = iVar12 + iVar11 * 0x80;
    *(byte *)(iVar8 + 0x21) = *(byte *)(iVar8 + 0x21) & 0xfd;
    iVar8 = iVar12 + iVar11 * 0x80;
    *(byte *)(iVar8 + 0x12) = *(byte *)(iVar8 + 0x12) & 0xfe;
    SetRendering__7MenuObjFUc(iVar12 + iVar11 * 0x80,0);
    OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(uStack_50 + iStack_40 * 0x16c + 0x3c,iVar12 + iVar11 * 0x80,1,0);
    iVar8 = iVar11 + 1;
    (**(code **)(*(int *)(iVar12 + iVar8 * 0x80 + 8) + 0x24))(0x42400000,fStack_ac + 2.0);
    SetMessage__8MenuTextFPcUiUcUc(iVar12 + iVar8 * 0x80,0x6551a8,0,0,1);
    *(undefined2 *)(iVar12 + iVar8 * 0x80 + 0x1c) = 1;
    *(short *)(iVar12 + iVar8 * 0x80 + 0x1e) = (short)iVar14;
    iVar9 = iVar12 + iVar8 * 0x80;
    *(byte *)(iVar9 + 0x21) = *(byte *)(iVar9 + 0x21) & 0xfd;
    iVar9 = iVar12 + iVar8 * 0x80;
    *(byte *)(iVar9 + 0x12) = *(byte *)(iVar9 + 0x12) & 0xfe;
    SetRendering__7MenuObjFUc(iVar12 + iVar8 * 0x80,0);
    OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(uStack_50 + iStack_40 * 0x16c + 0x3c,iVar12 + iVar8 * 0x80,1,0);
    iVar11 = iVar11 + 2;
    (**(code **)(*(int *)(iVar4 + iVar13 * 0x60 + 8) + 0x24))(0,fStack_ac);
    SetUV__10MenuSpriteFUsUsUsUs(iVar4 + iVar13 * 0x60,1,1,0xdd,0x1c);
    (**(code **)(*(int *)(iVar4 + iVar13 * 0x60 + 8) + 0x28))(0x435c0000,0x41d80000);
    iVar8 = iVar4 + iVar13 * 0x60;
    *(byte *)(iVar8 + 0x12) = *(byte *)(iVar8 + 0x12) & 0xfe | 1;
    SetRendering__7MenuObjFUc(iVar4 + iVar13 * 0x60,1);
    iVar13 = iVar13 + 1;
    fStack_ac = fStack_ac + 26.0;
  }
  *(uint *)(uStack_50 + iStack_40 * 0x16c + 0x170) = uVar10 + 1;
  uVar5 = uVar7;
  if ((int)uVar7 < 0) {
    uVar5 = uVar7 + 3;
  }
  *(int *)(uStack_50 + iStack_40 * 0x16c + 0x174) = (int)uVar5 >> 2;
  iVar12 = *(int *)(uStack_50 + iStack_40 * 0x16c + 0x170);
  iVar13 = iVar12 + 3;
  if (iVar13 < 0) {
    iVar13 = iVar12 + 6;
  }
  uStack_90 = iVar13 >> 2;
  if ((int)uStack_90 < 2) {
    uStack_8c = 0;
  }
  else {
    fStack_a8 = 219.0 - ((float)(int)uStack_90 * 12.0 + 5.0);
    for (uStack_8c = 0; (int)uStack_8c < (int)uStack_90; uStack_8c = uStack_8c + 1) {
      (**(code **)(*(int *)(iVar4 + (uStack_8c + 5) * 0x60 + 8) + 0x24))(fStack_a8,fStack_ac);
      if (*(uint *)(uStack_50 + iStack_40 * 0x16c + 0x174) == uStack_8c) {
        SetUV__10MenuSpriteFUsUsUsUs(iVar4 + (uStack_8c + 5) * 0x60,1,0x53,0x13,0x5c);
        (**(code **)(*(int *)(iVar4 + (uStack_8c + 5) * 0x60 + 8) + 0x28))(0x41900000,0x41100000);
        fStack_a8 = fStack_a8 + 17.0;
      }
      else {
        SetUV__10MenuSpriteFUsUsUsUs(iVar4 + (uStack_8c + 5) * 0x60,0x14,0x53,0x21,0x5c);
        (**(code **)(*(int *)(iVar4 + (uStack_8c + 5) * 0x60 + 8) + 0x28))(0x41500000,0x41100000);
        fStack_a8 = fStack_a8 + 12.0;
      }
      iStack_1a8 = iVar4 + (uStack_8c + 5) * 0x60;
      *(byte *)(iStack_1a8 + 0x12) = *(byte *)(iStack_1a8 + 0x12) & 0xfe | 1;
      iStack_1ac = iVar4 + (uStack_8c + 5) * 0x60;
      SetRendering__7MenuObjFUc(iStack_1ac,1);
    }
    fStack_ac = fStack_ac + 8.0;
  }
  for (; (int)uStack_8c < 0x10; uStack_8c = uStack_8c + 1) {
    iStack_1b0 = iVar4 + (uStack_8c + 5) * 0x60;
    *(byte *)(iStack_1b0 + 0x12) = *(byte *)(iStack_1b0 + 0x12) & 0xfe;
    iStack_1b4 = iVar4 + (uStack_8c + 5) * 0x60;
    SetRendering__7MenuObjFUc(iStack_1b4,0);
  }
  *(float *)(uStack_50 + iStack_40 * 0x16c + 0x17c) =
       (pfRam0040ab1c[1] + pfRam0040ab1c[3]) - fStack_ac;
  *(float *)(uStack_50 + iStack_40 * 0x16c + 0x180) = fStack_ac;
  SetPosition__10MenuWindowFff(*pfRam0040ab1c,(pfRam0040ab1c[1] + pfRam0040ab1c[3]) - fStack_ac,
                  uStack_50 + iStack_40 * 0x16c + 0x7c);
  SetSize__10MenuWindowFff(pfRam0040ab1c[2],fStack_ac,uStack_50 + iStack_40 * 0x16c + 0x7c);
  *(float *)(uStack_50 + iStack_40 * 0x16c + 0x184) = *pfRam0040ab1c;
  *(float *)(uStack_50 + iStack_40 * 0x16c + 0x188) =
       (pfRam0040ab1c[1] + pfRam0040ab1c[3]) - fStack_ac;
  *(float *)(uStack_50 + iStack_40 * 0x16c + 0x18c) = pfRam0040ab1c[2];
  *(float *)(uStack_50 + iStack_40 * 0x16c + 400) = fStack_ac;
  SetMark__10ScrollMarkFUc(*(undefined4 *)(uStack_50 + iStack_40 * 0x16c + 0x140),0);
  if (*(int *)(uStack_50 + iStack_40 * 0x16c + 0x170) < 5) {
    if (*(short *)(uStack_50 + 0xa32) == 1) {
      *(undefined2 *)(uStack_50 + 0xa32) = 2;
    }
  }
  else {
    if (*(int *)(uStack_50 + 0xb30) == 0) {
      iStack_1f0 = __nw__FUi(0x84);
      if (iStack_1f0 != 0) {
        iStack_1f0 = __ct__10ScrollMarkFv(iStack_1f0);
      }
      *(int *)(uStack_50 + 0xb30) = iStack_1f0;
      Create__10ScrollMarkFUcP10MenuWindowUc(*(undefined4 *)(uStack_50 + 0xb30),3,0,0);
      iStack_1b8 = *(int *)(uStack_50 + 0xb30);
      *(undefined2 *)(iStack_1b8 + 0x14) = 0x10;
      AddOT__7MenuObjFv(*(undefined4 *)(uStack_50 + 0xb30));
      *(byte *)(uStack_50 + 0x25) = *(byte *)(uStack_50 + 0x25) & 0xfd | 2;
      *(undefined2 *)(uStack_50 + 0xa32) = 1;
    }
    SetArea__10ScrollMarkFUcffff(*pfRam0040ab1c + 48.0,*(undefined4 *)(uStack_50 + iStack_40 * 0x16c + 0x17c),
                    pfRam0040ab1c[2] - 80.0,*(undefined4 *)(uStack_50 + iStack_40 * 0x16c + 0x180),
                    *(undefined4 *)(uStack_50 + 0xb30),3);
    uStack_8c = (uint)(0 < (int)uVar7);
    if ((int)(uVar7 + 4) < *(int *)(uStack_50 + iStack_40 * 0x16c + 0x170)) {
      uStack_8c = uStack_8c | 2;
    }
    SetMark__10ScrollMarkFUc(*(undefined4 *)(uStack_50 + 0xb30),uStack_8c);
  }
  if (iStack_98 != 0) {
    Open__10MenuWindowFUci(uStack_50 + iStack_40 * 0x16c + 0x7c,3,0x85);
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005bb180  SetMagicMenu__7BtlMenuFiii
 * C++: BtlMenu::SetMagicMenu(int, int, int)
 * size: 0xce4 bytes
 * --------------------------------------------------------------------------- */
void SetMagicMenu__7BtlMenuFiii
               (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined8 uVar7;
  int iVar8;
  int iVar9;
  ulong uVar11;
  uint uVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  undefined1 auStack_2740 [256];
  undefined2 auStack_2640 [256];
  undefined1 auStack_2440 [8192];
  undefined2 auStack_440 [256];
  int aiStack_240 [64];
  int aiStack_140 [64];
  undefined4 uStack_40;
  undefined4 uStack_30;
  undefined4 uStack_20;
  undefined4 uStack_10;
  int iVar10;
  
  iVar5 = 0;
  uStack_40 = param_1;
  uStack_30 = param_2;
  uStack_20 = param_3;
  uStack_10 = param_4;
  iVar2 = GetRegDat__9RegDatApiFiii(0x37,0,0xffffffffffffffff);
  iVar3 = GetRegDat__9RegDatApiFiii(0x38,0,0xffffffffffffffff);
  iVar6 = *(int *)(g_83f8 + 0xc);
  iVar8 = 0;
  iVar4 = 0;
  do {
    if (7 < iVar4) {
      cVar1 = *(char *)(iVar6 + 0x28e);
      if (cVar1 == '\x03') {
        for (iVar6 = 0; iVar2 = iVar6, iVar6 < iVar8; iVar6 = iVar6 + 1) {
          while (iVar2 = iVar2 + 1, iVar2 < iVar8) {
            if (*(ushort *)(iVar3 + aiStack_140[iVar2] * 0x44 + 0x42) <
                *(ushort *)(iVar3 + aiStack_140[iVar6] * 0x44 + 0x42)) {
              iVar4 = aiStack_140[iVar6];
              aiStack_140[iVar6] = aiStack_140[iVar2];
              aiStack_140[iVar2] = iVar4;
            }
          }
        }
      }
      else if (cVar1 == '\x02') {
        for (iVar6 = 0; iVar2 = iVar6, iVar6 < iVar8; iVar6 = iVar6 + 1) {
          while (iVar2 = iVar2 + 1, iVar2 < iVar8) {
            if (*(ushort *)(iVar3 + aiStack_140[iVar2] * 0x44 + 0x40) <
                *(ushort *)(iVar3 + aiStack_140[iVar6] * 0x44 + 0x40)) {
              iVar4 = aiStack_140[iVar6];
              aiStack_140[iVar6] = aiStack_140[iVar2];
              aiStack_140[iVar2] = iVar4;
            }
          }
        }
      }
      else if (cVar1 == '\x01') {
        for (iVar6 = 0; iVar2 = iVar6, iVar6 < iVar8; iVar6 = iVar6 + 1) {
          while (iVar2 = iVar2 + 1, iVar2 < iVar8) {
            if (*(ushort *)(iVar3 + aiStack_140[iVar2] * 0x44 + 0x3e) <
                *(ushort *)(iVar3 + aiStack_140[iVar6] * 0x44 + 0x3e)) {
              iVar4 = aiStack_140[iVar6];
              aiStack_140[iVar6] = aiStack_140[iVar2];
              aiStack_140[iVar2] = iVar4;
            }
          }
        }
      }
      else {
        for (iVar6 = 0; iVar2 = iVar6, iVar6 < iVar8; iVar6 = iVar6 + 1) {
          while (iVar2 = iVar2 + 1, iVar2 < iVar8) {
            if (aiStack_140[iVar2] < aiStack_140[iVar6]) {
              iVar4 = aiStack_140[iVar6];
              aiStack_140[iVar6] = aiStack_140[iVar2];
              aiStack_140[iVar2] = iVar4;
            }
          }
        }
      }
      for (iVar6 = 0; iVar6 < iVar8; iVar6 = iVar6 + 1) {
        iVar2 = DecMPp__7CBattleFiiii
                          (pCGpffff86b4,(int)pCGpffff86b4->cActor,2,aiStack_140[iVar6],
                           (uint)*(ushort *)(iVar3 + aiStack_140[iVar6] * 0x44 + 0x1e));
        aiStack_240[iVar6] = iVar2 / 100;
      }
      for (iVar6 = 0; iVar6 < iVar8; iVar6 = iVar6 + 1) {
        if ((((ulong)*(byte *)(iVar3 + aiStack_140[iVar6] * 0x44 + 4) & 0x1f) >> 3 != 0) &&
           (((ulong)*(byte *)(iVar3 + aiStack_140[iVar6] * 0x44 + 4) & 0x1f) >> 3 != 3)) {
          auStack_440[iVar5] = (short)aiStack_140[iVar6];
          uVar7 = GetRegDat__9RegDatApiFiii(0xe,aiStack_140[iVar6],0xffffffffffffffff);
          strcpy(auStack_2440 + iVar5 * 0x20,uVar7);
          auStack_2640[iVar5] = (short)aiStack_240[iVar6];
          auStack_2740[iVar5] = 0;
          if ((long)aiStack_240[iVar6] <=
              (long)*(short *)((int)pCGpffff86b4 +
                              (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 +
                              0x128)) {
            auStack_2740[iVar5] = 1;
          }
          iVar5 = iVar5 + 1;
        }
      }
      CreateMenu2__7BtlMenuFiiiiPsPcPsPcbb
                (uStack_40,uStack_30,uStack_20,uStack_10,iVar5,auStack_440,auStack_2440,auStack_2640
                );
      return;
    }
    if (-1 < *(char *)(ourBtlSaveDat +
                       *(short *)((int)pCGpffff86b4 +
                                 (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 +
                                 0x120) * 0xc0 + iVar4 + 0x76)) {
      cVar1 = *(char *)(ourBtlSaveDat +
                        *(short *)((int)pCGpffff86b4 +
                                  (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 +
                                  0x120) * 0xc0 + iVar4 + 0x76);
      uVar11 = (ulong)cVar1;
      iVar15 = (int)cVar1;
      iVar9 = (int)cVar1;
      iVar10 = (int)cVar1;
      if (-1 < *(short *)(iVar2 + cVar1 * 0x1c + 8)) {
        if ((*(byte *)(iVar2 + iVar10 * 0x1c + 6) & 1) == 0) {
LAB_005bb390:
          for (iVar13 = 0;
              (iVar13 < iVar8 &&
              ((long)aiStack_140[iVar13] != (long)*(short *)(iVar2 + (iVar9 * 8 - iVar15) * 4 + 8)))
              ; iVar13 = iVar13 + 1) {
          }
          if (iVar8 <= iVar13) {
            aiStack_140[iVar8] = (int)*(short *)(iVar2 + iVar15 * 0x1c + 8);
            iVar8 = iVar8 + 1;
          }
        }
        else if ((*(byte *)(iVar2 + iVar10 * 0x1c + 6) & 1) != 0) {
          uVar12 = (uint)(uVar11 & 7);
          if (((long)uVar11 < 0) && ((uVar11 & 7) != 0)) {
            uVar12 = uVar12 - 8;
          }
          if (((uint)*(byte *)(ourBtlSaveDat + (uint)*(byte *)(ourBtlSaveDat + 2) * 0x200 + (iVar9 >> 3)
                              + 0xaae) & 1 << (uVar12 & 0x1f)) != 0) goto LAB_005bb390;
        }
      }
      iVar13 = (int)cVar1;
      if (-1 < *(short *)(iVar2 + (iVar15 * 8 - iVar10) * 4 + 10)) {
        if ((long)((ulong)*(byte *)(iVar2 + iVar10 * 0x1c + 6) << 0x3e) < 0) {
          if ((long)((ulong)*(byte *)(iVar2 + (iVar10 * 8 - iVar13) * 4 + 6) << 0x3e) < 0) {
            uVar12 = (uint)(uVar11 & 7);
            if (((long)uVar11 < 0) && ((uVar11 & 7) != 0)) {
              uVar12 = uVar12 - 8;
            }
            if (((uint)*(byte *)(ourBtlSaveDat + (uint)*(byte *)(ourBtlSaveDat + 2) * 0x200 +
                                 (iVar13 >> 3) + 0xaae) & 1 << (uVar12 & 0x1f)) != 0)
            goto LAB_005bb4f0;
          }
        }
        else {
LAB_005bb4f0:
          for (iVar14 = 0;
              (iVar14 < iVar8 &&
              ((long)aiStack_140[iVar14] != (long)*(short *)(iVar2 + iVar13 * 0x1c + 10)));
              iVar14 = iVar14 + 1) {
          }
          if (iVar8 <= iVar14) {
            aiStack_140[iVar8] = (int)*(short *)(iVar2 + iVar10 * 0x1c + 10);
            iVar8 = iVar8 + 1;
          }
        }
      }
      if (-1 < *(short *)(iVar2 + iVar10 * 0x1c + 0xc)) {
        if ((long)((ulong)*(byte *)(iVar2 + iVar10 * 0x1c + 6) << 0x3d) < 0) {
          if ((long)((ulong)*(byte *)(iVar2 + iVar10 * 0x1c + 6) << 0x3d) < 0) {
            uVar12 = (uint)(uVar11 & 7);
            if (((long)uVar11 < 0) && ((uVar11 & 7) != 0)) {
              uVar12 = uVar12 - 8;
            }
            if (((uint)*(byte *)(ourBtlSaveDat + (uint)*(byte *)(ourBtlSaveDat + 2) * 0x200 +
                                 (iVar15 >> 3) + 0xaae) & 1 << (uVar12 & 0x1f)) != 0)
            goto LAB_005bb650;
          }
        }
        else {
LAB_005bb650:
          for (iVar14 = 0;
              (iVar14 < iVar8 &&
              ((long)aiStack_140[iVar14] !=
               (long)*(short *)(iVar2 + (iVar15 * 8 - iVar13) * 4 + 0xc))); iVar14 = iVar14 + 1) {
          }
          if (iVar8 <= iVar14) {
            aiStack_140[iVar8] = (int)*(short *)(iVar2 + iVar13 * 0x1c + 0xc);
            iVar8 = iVar8 + 1;
          }
        }
      }
      if (-1 < *(short *)(iVar2 + (iVar13 * 8 - iVar10) * 4 + 0xe)) {
        if ((long)((ulong)*(byte *)(iVar2 + iVar10 * 0x1c + 6) << 0x3c) < 0) {
          if ((long)((ulong)*(byte *)(iVar2 + iVar10 * 0x1c + 6) << 0x3c) < 0) {
            uVar12 = (uint)(uVar11 & 7);
            if (((long)uVar11 < 0) && ((uVar11 & 7) != 0)) {
              uVar12 = uVar12 - 8;
            }
            if (((uint)*(byte *)(ourBtlSaveDat + (uint)*(byte *)(ourBtlSaveDat + 2) * 0x200 +
                                 (iVar10 >> 3) + 0xaae) & 1 << (uVar12 & 0x1f)) != 0)
            goto LAB_005bb7b8;
          }
        }
        else {
LAB_005bb7b8:
          for (iVar15 = 0;
              (iVar15 < iVar8 &&
              ((long)aiStack_140[iVar15] != (long)*(short *)(iVar2 + iVar10 * 0x1c + 0xe)));
              iVar15 = iVar15 + 1) {
          }
          if (iVar8 <= iVar15) {
            aiStack_140[iVar8] = (int)*(short *)(iVar2 + iVar9 * 0x1c + 0xe);
            iVar8 = iVar8 + 1;
          }
        }
      }
    }
    iVar4 = iVar4 + 1;
  } while( true );
}

/* ---------------------------------------------------------------------------
 * JP: 0x005bbe70  SetItemMenu__7BtlMenuFiii
 * C++: BtlMenu::SetItemMenu(int, int, int)
 * size: 0x424 bytes
 * --------------------------------------------------------------------------- */
void SetItemMenu__7BtlMenuFiii
               (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  int iVar2;
  int iVar3;
  ulong uVar4;
  undefined8 uVar5;
  int iVar6;
  ulong uVar7;
  int iVar8;
  int iVar9;
  ulong uVar10;
  char acStack_2740 [512];
  undefined1 auStack_2540 [256];
  ushort auStack_2440 [256];
  undefined1 auStack_2240 [8192];
  undefined2 auStack_240 [256];
  undefined4 uStack_40;
  undefined4 uStack_30;
  undefined4 uStack_20;
  undefined4 uStack_10;
  
  iVar8 = 0;
  uStack_40 = param_1;
  uStack_30 = param_2;
  uStack_20 = param_3;
  uStack_10 = param_4;
  uVar4 = GetRegCnt__9RegDatApiFii(0x33,0xffffffffffffffff);
  iVar3 = GetRegDat__9RegDatApiFiii(0x33,0,0xffffffffffffffff);
  iVar2 = *(int *)(g_83f8 + 0xc);
  uVar7 = 0;
  while (uVar7 < uVar4) {
    uVar10 = 0;
    while (iVar6 = (int)uVar7, uVar10 < uVar4) {
      iVar9 = (int)uVar10;
      if (uVar7 == *(ushort *)(iVar3 + iVar9 * 0x30 + 0x2c)) {
        acStack_2740[iVar6 * 2] = (char)uVar10;
      }
      if (uVar7 == *(ushort *)(iVar3 + iVar9 * 0x30 + 0x2e)) {
        acStack_2740[iVar6 * 2 + 1] = (char)uVar10;
      }
      uVar10 = (ulong)(iVar9 + 1);
    }
    uVar7 = (ulong)(iVar6 + 1);
  }
  uVar7 = 0;
  while (uVar7 < uVar4) {
    cVar1 = *(char *)(iVar2 + 0x28c);
    iVar6 = (int)uVar7;
    if (cVar1 == '\x02') {
      uVar7 = (ulong)acStack_2740[iVar6 * 2 + 1];
    }
    else if (cVar1 == '\x01') {
      uVar7 = (ulong)acStack_2740[iVar6 * 2];
    }
    iVar9 = (int)uVar7;
    if (((*(char *)(ourBtlSaveDat + (uint)*(byte *)(ourBtlSaveDat + 2) * 0x200 + iVar9 + 0x944) != '\0')
        && (((ulong)*(byte *)(iVar3 + iVar9 * 0x30 + 4) & 0x1f) >> 3 != 0)) &&
       (((ulong)*(byte *)(iVar3 + iVar9 * 0x30 + 4) & 0x1f) >> 3 != 3)) {
      auStack_240[iVar8] = (short)uVar7;
      uVar5 = GetRegDat__9RegDatApiFiii(9,uVar7,0xffffffffffffffff);
      strcpy(auStack_2240 + iVar8 * 0x20,uVar5);
      auStack_2440[iVar8] =
           (ushort)*(byte *)(ourBtlSaveDat + (uint)*(byte *)(ourBtlSaveDat + 2) * 0x200 + iVar9 + 0x944)
      ;
      auStack_2540[iVar8] = 0;
      if (((ulong)*(byte *)(iVar3 + iVar9 * 0x30 + 4) & 0x7f) >> 5 == 0) {
        if ((*(byte *)(ourBtlSaveDat +
                       *(short *)(iGpffff86b4 +
                                  (*(char *)(iGpffff86b4 + 0x2c) * 0x50 -
                                  (int)*(char *)(iGpffff86b4 + 0x2c)) * 0x10 + 0x120) * 0xc0 + 0x9c)
             >> 6 != 1) &&
           ((*(byte *)(ourBtlSaveDat +
                       *(short *)(iGpffff86b4 +
                                  (*(char *)(iGpffff86b4 + 0x2c) * 0x50 -
                                  (int)*(char *)(iGpffff86b4 + 0x2c)) * 0x10 + 0x120) * 0xc0 + 0x9d)
            & 1) == 0)) {
          auStack_2540[iVar8] = 1;
        }
      }
      else {
        auStack_2540[iVar8] = 1;
      }
      iVar8 = iVar8 + 1;
    }
    uVar7 = (ulong)(iVar6 + 1);
  }
  CreateMenu2__7BtlMenuFiiiiPsPcPsPcbb
            (uStack_40,uStack_30,uStack_20,uStack_10,iVar8,auStack_240,auStack_2240,auStack_2440);
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005bc2a0  SetGuardMenu__7BtlMenuFii
 * C++: BtlMenu::SetGuardMenu(int, int)
 * size: 0xd4 bytes
 * --------------------------------------------------------------------------- */
void SetGuardMenu__7BtlMenuFii(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  undefined1 auStack_2330 [256];
  undefined1 auStack_2230 [8192];
  undefined2 auStack_230 [256];
  undefined4 uStack_30;
  undefined4 uStack_20;
  undefined4 uStack_10;
  
  iVar1 = 0;
  uStack_30 = param_1;
  uStack_20 = param_2;
  uStack_10 = param_3;
  for (iVar2 = 0; iVar2 < 2; iVar2 = iVar2 + 1) {
    auStack_230[iVar1] = (short)iVar2;
    strcpy(auStack_2230 + iVar1 * 0x20,*(undefined4 *)(iRam0040ab3c + iVar2 * 4));
    auStack_2330[iVar1] = 1;
    iVar1 = iVar1 + 1;
  }
  CreateMenu1__7BtlMenuFiiiiPsPcPcbb
            (uStack_30,uStack_20,0xffffffffffffffff,uStack_10,iVar1,auStack_230,auStack_2230,
             auStack_2330);
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005bc380  SetMoveMenu__7BtlMenuFiii
 * C++: BtlMenu::SetMoveMenu(int, int, int)
 * size: 0x4a8 bytes
 * --------------------------------------------------------------------------- */
void SetMoveMenu__7BtlMenuFiii
               (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  long lVar2;
  int iVar3;
  int iVar4;
  undefined1 auStack_2340 [256];
  undefined1 auStack_2240 [8192];
  undefined2 auStack_240 [256];
  undefined4 uStack_40;
  undefined4 uStack_30;
  undefined4 uStack_20;
  undefined4 uStack_10;
  
  iVar3 = 0;
  lVar2 = 0;
  uStack_40 = param_1;
  uStack_30 = param_2;
  uStack_20 = param_3;
  uStack_10 = param_4;
  while (lVar2 < 0xc) {
    iVar1 = (int)lVar2;
    if (((((*(byte *)(iGpffff86b4 + iVar1 * 0x4f0 + 0xb0) & 1) != 0) &&
         ((long)((ulong)*(byte *)(iGpffff86b4 + iVar1 * 0x4f0 + 0xb0) << 0x3e) < 0)) &&
        (-1 < (long)((ulong)*(byte *)(iGpffff86b4 + iVar1 * 0x4f0 + 0xb2) << 0x3d))) &&
       ((((lVar2 != *(char *)(iGpffff86b4 + 0x2c) &&
          ((*(byte *)(iGpffff86b4 +
                      (*(char *)(iGpffff86b4 + 0x2c) * 0x50 - (int)*(char *)(iGpffff86b4 + 0x2c)) *
                      0x10 + 0xb4) & 1) == (*(byte *)(iGpffff86b4 + iVar1 * 0x4f0 + 0xb4) & 1))) &&
         (0 < *(short *)(iGpffff86b4 + iVar1 * 0x4f0 + 0x124))) &&
        ((((*(byte *)(iGpffff86b4 +
                      (*(char *)(iGpffff86b4 + 0x2c) * 0x50 - (int)*(char *)(iGpffff86b4 + 0x2c)) *
                      0x10 + 0xb4) & 1) != 0 || (0 < *(short *)(iGpffff86b4 + iVar1 * 0x4f0 + 300)))
         || ((*(short *)(iGpffff86b4 + iVar1 * 0x4f0 + 0x120) == 8 ||
             ((*(short *)(iGpffff86b4 + iVar1 * 0x4f0 + 0x120) == 9 ||
              (*(short *)(iGpffff86b4 + iVar1 * 0x4f0 + 0x120) == 10)))))))))) {
      iVar4 = 0;
      while ((iVar4 < 0x20 &&
             (((*(char *)(iGpffff86b4 + iVar1 * 0x4f0 + iVar4 * 0xc + 0x1bc) != 'G' ||
               (((ulong)*(byte *)(iGpffff86b4 + iVar1 * 0x4f0 + iVar4 * 0xc + 0x1b9) & 0x1f) >> 2 !=
                0)) || ((*(uint *)(iGpffff86b4 + iVar1 * 0x4f0 + iVar4 * 0xc + 0x1c0) & 0x24) == 0))
             ))) {
        iVar4 = iVar4 + 1;
      }
      if (0x1f < iVar4) {
        auStack_240[iVar3] = (short)lVar2;
        strcpy(auStack_2240 + iVar3 * 0x20,
                        *(undefined4 *)(iGpffff86b4 + iVar1 * 0x4f0 + 0x11c));
        if (*(short *)(iGpffff86b4 + iVar1 * 0x4f0 + 0x13a) != -1) {
          strcat(auStack_2240 + iVar3 * 0x20,
                          *(undefined4 *)
                           (iRam0040ab24 + *(short *)(iGpffff86b4 + iVar1 * 0x4f0 + 0x13a) * 4));
        }
        auStack_2340[iVar3] = 1;
        iVar3 = iVar3 + 1;
      }
    }
    lVar2 = (long)(iVar1 + 1);
  }
  CreateMenu1__7BtlMenuFiiiiPsPcPcbb
            (uStack_40,uStack_30,uStack_20,uStack_10,iVar3,auStack_240,auStack_2240,auStack_2340);
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005bc830  SetMoveAfterMenu__7BtlMenuFii
 * C++: BtlMenu::SetMoveAfterMenu(int, int)
 * size: 0xd4 bytes
 * --------------------------------------------------------------------------- */
void SetMoveAfterMenu__7BtlMenuFii(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  undefined1 auStack_2330 [256];
  undefined1 auStack_2230 [8192];
  undefined2 auStack_230 [256];
  undefined4 uStack_30;
  undefined4 uStack_20;
  undefined4 uStack_10;
  
  iVar1 = 0;
  uStack_30 = param_1;
  uStack_20 = param_2;
  uStack_10 = param_3;
  for (iVar2 = 0; iVar2 < 2; iVar2 = iVar2 + 1) {
    auStack_230[iVar1] = (short)iVar2;
    strcpy(auStack_2230 + iVar1 * 0x20,*(undefined4 *)(iRam0040ab48 + iVar2 * 4));
    auStack_2330[iVar1] = 1;
    iVar1 = iVar1 + 1;
  }
  CreateMenu1__7BtlMenuFiiiiPsPcPcbb
            (uStack_30,uStack_20,0xffffffffffffffff,uStack_10,iVar1,auStack_230,auStack_2230,
             auStack_2330);
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005bc910  SetFusionMenu__7BtlMenuFiii
 * C++: BtlMenu::SetFusionMenu(int, int, int)
 * size: 0x5b0 bytes
 * --------------------------------------------------------------------------- */
void SetFusionMenu__7BtlMenuFiii
               (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  bool bVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  undefined8 uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  long lVar9;
  undefined1 auStack_2540 [256];
  short asStack_2440 [256];
  undefined1 auStack_2240 [8192];
  short asStack_240 [256];
  undefined4 uStack_40;
  undefined4 uStack_30;
  undefined4 uStack_20;
  undefined4 uStack_10;
  
  bVar2 = false;
  for (iVar3 = 0; iVar3 < 0x20; iVar3 = iVar3 + 1) {
    if (((*(char *)((int)pCGpffff86b4 +
                   iVar3 * 0xc + (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 +
                   0x1bc) == 'G') &&
        (((ulong)*(byte *)((int)pCGpffff86b4 +
                          iVar3 * 0xc +
                          (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x1b9)
         & 0x1f) >> 2 == 0)) &&
       ((*(uint *)((int)pCGpffff86b4 +
                  iVar3 * 0xc + (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 +
                  0x1c0) & 8) != 0)) {
      bVar2 = true;
    }
  }
  lVar9 = -1;
  if ((*(byte *)((int)pCGpffff86b4 +
                (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb1) & 1) != 0)
  {
    lVar9 = (long)*(short *)((int)pCGpffff86b4 +
                            (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xba)
    ;
  }
  uStack_40 = param_1;
  uStack_30 = param_2;
  uStack_20 = param_3;
  uStack_10 = param_4;
  iVar3 = GetRegDat__9RegDatApiFiii(0x2c,0,0xffffffffffffffff);
  uVar8 = *(uint *)(ourBtlSaveDat + 0xd4c);
  if (lVar9 != -1) {
    uVar8 = uVar8 - (1 << ((uint)lVar9 & 0x1f));
  }
  bVar1 = (*(byte *)((int)pCGpffff86b4 +
                    (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb1) & 1) !=
          0;
  if (bVar1) {
    asStack_240[0] = -1;
    strcpy(auStack_2240,0x6552a8);
    asStack_2440[0] = -1;
    auStack_2540[0] = 1;
  }
  uVar6 = (uint)bVar1;
  if (*(short *)((int)pCGpffff86b4 +
                (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x120) == 0) {
    for (uVar7 = 0; (int)uVar7 < 0xf; uVar7 = uVar7 + 1) {
      if ((uVar8 & 1 << (uVar7 & 0x1f)) != 0) {
        asStack_240[uVar6] = (short)uVar7 + 10;
        uVar5 = GetRegDat__9RegDatApiFiii(4,uVar7,0xffffffffffffffff);
        strcpy(auStack_2240 + uVar6 * 0x20,uVar5);
        iVar4 = DecSPp__7CBattleFiii
                          (pCGpffff86b4,(int)pCGpffff86b4->cActor,
                           (uint)*(byte *)(iVar3 + uVar7 * 0x20 + 5),uVar7);
        asStack_2440[uVar6] = (short)((iVar4 + 99) / 100);
        if (asStack_2440[uVar6] < 1) {
          asStack_2440[uVar6] = 1;
        }
        auStack_2540[uVar6] = 0;
        if (!bVar2) {
          auStack_2540[uVar6] = 1;
        }
        uVar6 = uVar6 + 1;
      }
    }
  }
  else {
    for (uVar7 = 0xf; (int)uVar7 < 0x11; uVar7 = uVar7 + 1) {
      if ((uVar8 & 1 << (uVar7 & 0x1f)) != 0) {
        asStack_240[uVar6] = (short)uVar7 + 10;
        uVar5 = GetRegDat__9RegDatApiFiii(4,uVar7,0xffffffffffffffff);
        strcpy(auStack_2240 + uVar6 * 0x20,uVar5);
        iVar4 = DecSPp__7CBattleFiii
                          (pCGpffff86b4,(int)pCGpffff86b4->cActor,
                           (uint)*(byte *)(iVar3 + uVar7 * 0x20 + 5),uVar7);
        asStack_2440[uVar6] = (short)((iVar4 + 99) / 100);
        if (asStack_2440[uVar6] < 1) {
          asStack_2440[uVar6] = 1;
        }
        auStack_2540[uVar6] = 0;
        if (!bVar2) {
          auStack_2540[uVar6] = 1;
        }
        uVar6 = uVar6 + 1;
      }
    }
  }
  CreateMenu2__7BtlMenuFiiiiPsPcPsPcbb
            (uStack_40,uStack_30,uStack_20,uStack_10,uVar6,asStack_240,auStack_2240,asStack_2440);
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005bcec0  SetSkill1Menu__7BtlMenuFiii
 * C++: BtlMenu::SetSkill1Menu(int, int, int)
 * size: 0x89c bytes
 * --------------------------------------------------------------------------- */
void SetSkill1Menu__7BtlMenuFiii
               (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  undefined8 uVar4;
  short unaff_s0_lo;
  uint uVar5;
  uint uVar6;
  ulong uVar7;
  undefined1 auStack_2550 [256];
  short asStack_2450 [256];
  undefined1 auStack_2250 [8192];
  undefined2 auStack_250 [258];
  undefined4 uStack_4c;
  int iStack_48;
  uint uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_30;
  undefined4 uStack_20;
  undefined4 uStack_10;
  
  uVar6 = 0;
  uStack_40 = param_1;
  uStack_30 = param_2;
  uStack_20 = param_3;
  uStack_10 = param_4;
  if ((*(byte *)((int)pCGpffff86b4 +
                (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb4) & 1) == 0)
  {
    if ((*(byte *)((int)pCGpffff86b4 +
                  (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb1) & 1) == 0
       ) {
      unaff_s0_lo = *(short *)((int)pCGpffff86b4 +
                              (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 +
                              0x120);
      if (unaff_s0_lo == 6) {
        uVar7 = (ulong)*(char *)(ourBtlSaveDat + 0xe37);
        if (*(int *)(ourBtlSocket + 0x698) == 1) {
          uVar7 = 0;
        }
      }
      else if (unaff_s0_lo == 5) {
        uVar7 = (ulong)*(ushort *)(ourBtlSaveDat + 0x43e);
      }
      else if (unaff_s0_lo == 2) {
        uVar7 = (ulong)*(int *)(*(int *)(g_83f8 + 0xc) + 0x2fc);
      }
      else if (unaff_s0_lo == 1) {
        uVar7 = 0x1000;
      }
      else {
        uVar7 = 0xffffffffffffffff;
      }
    }
    else {
      iVar2 = GetRegDat__9RegDatApiFiii(0x2c,*(undefined2 *)
                                    ((int)pCGpffff86b4 +
                                    (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10
                                    + 0xba),0xffffffffffffffff);
      switch(*(undefined2 *)
              ((int)pCGpffff86b4 +
              (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xba)) {
      case 0:
      case 1:
        unaff_s0_lo = 0xc;
        break;
      case 2:
      case 3:
        unaff_s0_lo = 0xd;
        break;
      case 4:
      case 5:
        unaff_s0_lo = 0xe;
        break;
      case 6:
      case 7:
        unaff_s0_lo = 0xf;
        break;
      case 8:
      case 9:
        unaff_s0_lo = 0x10;
        break;
      case 10:
      case 0xb:
        unaff_s0_lo = 0x11;
        break;
      case 0xc:
      case 0xd:
        unaff_s0_lo = 0x12;
        break;
      case 0xe:
        unaff_s0_lo = 0x13;
        break;
      case 0xf:
        unaff_s0_lo = 0x14;
        break;
      case 0x10:
        unaff_s0_lo = 0x15;
      }
      uVar7 = 0;
      for (uVar5 = 0; (int)uVar5 < 7; uVar5 = uVar5 + 1) {
        if ((-1 < *(short *)(iVar2 + uVar5 * 2 + 8)) &&
           ((long)*(char *)(iVar2 + uVar5 + 0x16) <=
            (long)(int)(*(byte *)(ourBtlSaveDat +
                                  *(short *)((int)pCGpffff86b4 +
                                            (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor
                                            ) * 0x10 + 0xba) + 0xd94) + 1))) {
          uVar7 = uVar7 | (long)(1 << (uVar5 & 0x1f));
        }
      }
    }
    uStack_44 = GetRegCnt__9RegDatApiFii(0x36,unaff_s0_lo);
    iVar2 = GetRegDat__9RegDatApiFiii(0x36,unaff_s0_lo,0xffffffffffffffff);
    for (uVar5 = 0; uVar5 < uStack_44; uVar5 = uVar5 + 1) {
      if (((((ulong)*(byte *)(iVar2 + uVar5 * 0x40 + 4) & 0x1f) >> 3 != 0) &&
          (((ulong)*(byte *)(iVar2 + uVar5 * 0x40 + 4) & 0x1f) >> 3 != 3)) &&
         ((uVar7 & (long)(1 << (uVar5 & 0x1f))) != 0)) {
        auStack_250[uVar6] = (short)uVar5;
        uVar4 = GetRegDat__9RegDatApiFiii(0xc,*(undefined2 *)(iVar2 + uVar5 * 0x40 + 2),0xffffffffffffffff);
        strcpy(auStack_2250 + uVar6 * 0x20,uVar4);
        iVar3 = DecMPp__7CBattleFiiii
                          (pCGpffff86b4,(int)pCGpffff86b4->cActor,1,uVar5,
                           (uint)*(ushort *)(iVar2 + uVar5 * 0x40 + 0x1e));
        asStack_2450[uVar6] = (short)(iVar3 / 100);
        auStack_2550[uVar6] = 0;
        if (asStack_2450[uVar6] <=
            *(short *)((int)pCGpffff86b4 +
                      (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x128)) {
          auStack_2550[uVar6] = 1;
        }
        uVar6 = uVar6 + 1;
      }
    }
    CreateMenu2__7BtlMenuFiiiiPsPcPsPcbb
              (uStack_40,uStack_30,uStack_20,uStack_10,uVar6,auStack_250,auStack_2250,asStack_2450);
  }
  else {
    iVar2 = *(int *)((int)pCGpffff86b4 +
                    (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x148);
    iStack_48 = GetRegDat__9RegDatApiFiii(0x36,0x16,0xffffffffffffffff);
    uStack_4c = GetRegDat__9RegDatApiFiii(0x36,0x17,0xffffffffffffffff);
    if (*(short *)(iVar2 + 0x16) == -1) {
      iVar3 = iStack_48 + *(short *)(iVar2 + 0x18) * 0x28;
      for (iVar2 = 0; iVar2 < 0x14; iVar2 = iVar2 + 1) {
        if (-1 < *(short *)(iVar3 + iVar2 * 2)) {
          auStack_250[uVar6] = *(undefined2 *)(iVar3 + iVar2 * 2);
          uVar4 = GetRegDat__9RegDatApiFiii(0xc,0x17,*(undefined2 *)(iVar3 + iVar2 * 2));
          strcpy(auStack_2250 + uVar6 * 0x20,uVar4);
          asStack_2450[uVar6] = 0;
          auStack_2550[uVar6] = 1;
          uVar6 = uVar6 + 1;
        }
      }
    }
    else {
      bVar1 = -1 < *(short *)(iVar2 + 0x16);
      if (bVar1) {
        auStack_250[0] = *(undefined2 *)(iVar2 + 0x16);
        uVar4 = GetRegDat__9RegDatApiFiii(0xc,0x17,*(undefined2 *)(iVar2 + 0x16));
        strcpy(auStack_2250,uVar4);
        asStack_2450[0] = 0;
        auStack_2550[0] = 1;
      }
      uVar6 = (uint)bVar1;
      if (-1 < *(short *)(iVar2 + 0x18)) {
        uVar6 = (uint)bVar1;
        auStack_250[uVar6] = *(undefined2 *)(iVar2 + 0x18);
        uVar4 = GetRegDat__9RegDatApiFiii(0xc,0x17,*(undefined2 *)(iVar2 + 0x18));
        strcpy(auStack_2250 + uVar6 * 0x20,uVar4);
        asStack_2450[uVar6] = 0;
        auStack_2550[uVar6] = 1;
        uVar6 = uVar6 + 1;
      }
    }
    CreateMenu2__7BtlMenuFiiiiPsPcPsPcbb
              (uStack_40,uStack_30,uStack_20,uStack_10,uVar6,auStack_250,auStack_2250,asStack_2450);
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005bd760  SetComboSkillMenu__7BtlMenuFiii
 * C++: BtlMenu::SetComboSkillMenu(int, int, int)
 * size: 0x264 bytes
 * --------------------------------------------------------------------------- */
void SetComboSkillMenu__7BtlMenuFiii
               (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  ushort uVar1;
  uint uVar2;
  int iVar3;
  undefined8 uVar4;
  int iVar5;
  uint uVar6;
  undefined1 auStack_2550 [256];
  ushort auStack_2450 [256];
  undefined1 auStack_2250 [8192];
  undefined2 auStack_250 [260];
  uint uStack_48;
  uint uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_30;
  undefined4 uStack_20;
  undefined4 uStack_10;
  
  iVar5 = 0;
  uStack_40 = param_1;
  uStack_30 = param_2;
  uStack_20 = param_3;
  uStack_10 = param_4;
  CheckComboSkill__7CBattleFiPiPi
            (pCGpffff86b4,(int)pCGpffff86b4->cActor,(int *)&uStack_44,(int *)&uStack_48);
  uVar2 = GetRegCnt__9RegDatApiFii(0x39,0xffffffffffffffff);
  iVar3 = GetRegDat__9RegDatApiFiii(0x39,0,0xffffffffffffffff);
  for (uVar6 = 0; uVar6 < uVar2; uVar6 = uVar6 + 1) {
    if ((uStack_44 & 1 << (uVar6 & 0x1f)) != 0) {
      auStack_250[iVar5] = (short)uVar6;
      if ((*(uint *)(ourBtlSaveDat + 0xd44) & 1 << (uVar6 & 0x1f)) == 0) {
        strcpy(auStack_2250 + iVar5 * 0x20,*(undefined4 *)(iRam0040ab20 + 0xa4));
      }
      else {
        uVar4 = GetRegDat__9RegDatApiFiii(0xf,uVar6,0xffffffffffffffff);
        strcpy(auStack_2250 + iVar5 * 0x20,uVar4);
      }
      auStack_2550[iVar5] = 0;
      if ((uStack_48 & 1 << (uVar6 & 0x1f)) != 0) {
        auStack_2550[iVar5] = 1;
      }
      uVar1 = *(ushort *)(iVar3 + uVar6 * 0x40 + 0x1e);
      if (((pCGpffff86b4->bGmodFlags & 1) != 0) && (pCGpffff86b4->wGmodStat == 1)) {
        uVar1 = (ushort)((int)((uint)uVar1 * (uint)(ushort)pCGpffff86b4->nGmodValue) / 100);
      }
      auStack_2450[iVar5] = uVar1;
      iVar5 = iVar5 + 1;
    }
  }
  CreateMenu2__7BtlMenuFiiiiPsPcPsPcbb
            (uStack_40,uStack_30,uStack_20,uStack_10,iVar5,auStack_250,auStack_2250,auStack_2450);
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005bd9d0  SetBaseAromaMenu__7BtlMenuFiii
 * C++: BtlMenu::SetBaseAromaMenu(int, int, int)
 * size: 0x260 bytes
 * --------------------------------------------------------------------------- */
void SetBaseAromaMenu__7BtlMenuFiii
               (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  ulong uVar4;
  undefined8 uVar5;
  int iVar6;
  uint a3;
  ulong uVar7;
  undefined1 auStack_2340 [256];
  undefined1 auStack_2240 [8192];
  undefined2 auStack_240 [256];
  undefined4 uStack_40;
  undefined4 uStack_30;
  undefined4 uStack_20;
  undefined4 uStack_10;
  
  iVar6 = 0;
  uStack_40 = param_1;
  uStack_30 = param_2;
  uStack_20 = param_3;
  uStack_10 = param_4;
  uVar4 = GetRegCnt__9RegDatApiFii(0x3c,0xffffffffffffffff);
  uVar1 = GetRegCnt__9RegDatApiFii(0x3d,0xffffffffffffffff);
  iVar2 = GetRegDat__9RegDatApiFiii(0x3d,0,0xffffffffffffffff);
  for (uVar7 = 0; uVar7 < uVar4; uVar7 = (ulong)(int)((uint)uVar7 + 1)) {
    if (((uint)*(byte *)(ourBtlSaveDat + 0xdae) & 1 << ((uint)uVar7 & 0x1f)) != 0) {
      auStack_240[iVar6] = (short)uVar7;
      uVar5 = GetRegDat__9RegDatApiFiii(0x10,uVar7,0xffffffffffffffff);
      strcpy(auStack_2240 + iVar6 * 0x20,uVar5);
      auStack_2340[iVar6] = 0;
      a3 = 0;
      while ((a3 < uVar1 &&
             ((uVar7 != (long)*(char *)(iVar2 + a3 * 0x40 + 0x1c) ||
              (iVar3 = DecMPp__7CBattleFiiii
                                 (pCGpffff86b4,(int)pCGpffff86b4->cActor,5,a3,
                                  (uint)*(ushort *)(iVar2 + a3 * 0x40 + 0x1e)),
              (long)*(short *)((int)pCGpffff86b4 +
                              (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 +
                              0x128) < (long)(iVar3 / 100)))))) {
        a3 = a3 + 1;
      }
      if (a3 < uVar1) {
        auStack_2340[iVar6] = 1;
      }
      iVar6 = iVar6 + 1;
    }
  }
  CreateMenu1__7BtlMenuFiiiiPsPcPcbb
            (uStack_40,uStack_30,uStack_20,uStack_10,iVar6,auStack_240,auStack_2240,auStack_2340);
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005bdc30  SetAddAromaMenu__7BtlMenuFiii
 * C++: BtlMenu::SetAddAromaMenu(int, int, int)
 * size: 0x2ac bytes
 * --------------------------------------------------------------------------- */
void SetAddAromaMenu__7BtlMenuFiii
               (int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  ulong uVar4;
  undefined8 uVar5;
  int iVar6;
  ulong uVar7;
  uint a3;
  undefined1 auStack_2540 [256];
  short asStack_2440 [256];
  undefined1 auStack_2240 [8192];
  undefined2 auStack_240 [256];
  int iStack_40;
  undefined4 uStack_30;
  undefined4 uStack_20;
  undefined4 uStack_10;
  
  iVar6 = 0;
  iStack_40 = param_1;
  uStack_30 = param_2;
  uStack_20 = param_3;
  uStack_10 = param_4;
  uVar4 = GetRegCnt__9RegDatApiFii(0x3c,0xffffffffffffffff);
  uVar1 = GetRegCnt__9RegDatApiFii(0x3d,0xffffffffffffffff);
  iVar2 = GetRegDat__9RegDatApiFiii(0x3d,0,0xffffffffffffffff);
  for (uVar7 = 0; uVar7 < uVar4; uVar7 = (ulong)(int)((uint)uVar7 + 1)) {
    if ((((uint)*(byte *)(ourBtlSaveDat + 0xdae) & 1 << ((uint)uVar7 & 0x1f)) != 0) &&
       (uVar7 != (long)*(int *)(iStack_40 + 0x2d4))) {
      a3 = 0;
      while ((a3 < uVar1 &&
             (((long)*(int *)(iStack_40 + 0x2d4) != (long)*(char *)(iVar2 + a3 * 0x40 + 0x1c) ||
              (uVar7 != (long)*(char *)(iVar2 + a3 * 0x40 + 0x1d)))))) {
        a3 = a3 + 1;
      }
      auStack_240[iVar6] = (short)uVar7;
      uVar5 = GetRegDat__9RegDatApiFiii(0x10,uVar7,0xffffffffffffffff);
      strcpy(auStack_2240 + iVar6 * 0x20,uVar5);
      iVar3 = DecMPp__7CBattleFiiii
                        (pCGpffff86b4,(int)pCGpffff86b4->cActor,5,a3,
                         (uint)*(ushort *)(iVar2 + a3 * 0x40 + 0x1e));
      asStack_2440[iVar6] = (short)(iVar3 / 100);
      auStack_2540[iVar6] = 0;
      if (asStack_2440[iVar6] <=
          *(short *)((int)pCGpffff86b4 +
                    (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0x128)) {
        auStack_2540[iVar6] = 1;
      }
      iVar6 = iVar6 + 1;
    }
  }
  CreateMenu2__7BtlMenuFiiiiPsPcPsPcbb
            (iStack_40,uStack_30,uStack_20,uStack_10,iVar6,auStack_240,auStack_2240,asStack_2440);
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005bdee0  SetComboShortCutMenu__7BtlMenuFiii
 * C++: BtlMenu::SetComboShortCutMenu(int, int, int)
 * size: 0x9d14 bytes
 * --------------------------------------------------------------------------- */
/* WARNING: Removing unreachable block (ram,0x005c38c8) */
/* WARNING: Removing unreachable block (ram,0x005c3918) */
/* WARNING: Removing unreachable block (ram,0x005c3968) */

void SetComboShortCutMenu__7BtlMenuFiii(int param_1,int param_2,uint param_3,uint param_4)

{
  byte bVar1;
  char cVar2;
  short sVar3;
  int *piVar4;
  undefined4 uVar5;
  CBattle *pCVar6;
  undefined8 uVar7;
  int iVar8;
  int *piVar9;
  int iVar10;
  int *piVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  long lVar15;
  long extraout_t2;
  uint uVar16;
  ulong uVar17;
  undefined2 uVar18;
  undefined1 auStack_210 [128];
  int aiStack_190 [4];
  int aiStack_180 [4];
  int aiStack_170 [4];
  int aiStack_160 [3];
  float fStack_154;
  float fStack_150;
  float fStack_14c;
  float fStack_148;
  float fStack_144;
  float fStack_140;
  undefined4 uStack_13c;
  undefined4 uStack_138;
  undefined4 uStack_134;
  undefined4 uStack_130;
  undefined4 uStack_12c;
  undefined4 uStack_128;
  undefined4 uStack_124;
  undefined4 uStack_120;
  undefined4 uStack_11c;
  undefined4 uStack_118;
  undefined4 uStack_114;
  undefined4 uStack_110;
  undefined4 uStack_10c;
  undefined4 uStack_108;
  undefined4 uStack_104;
  undefined4 uStack_100;
  undefined4 uStack_fc;
  undefined4 uStack_f8;
  undefined4 uStack_f4;
  undefined4 uStack_f0;
  undefined4 uStack_ec;
  undefined4 uStack_e8;
  undefined4 uStack_e4;
  undefined4 uStack_e0;
  int iStack_dc;
  int iStack_d8;
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
  undefined4 uStack_ac;
  undefined4 uStack_a8;
  undefined4 uStack_a4;
  undefined4 uStack_a0;
  uint uStack_9c;
  int iStack_98;
  int iStack_94;
  int iStack_90;
  int iStack_8c;
  int iStack_88;
  int iStack_84;
  float fStack_80;
  undefined4 uStack_7c;
  float fStack_78;
  float fStack_74;
  undefined4 uStack_70;
  byte abStack_6c [4];
  byte abStack_68 [4];
  char acStack_64 [4];
  undefined4 uStack_60;
  int iStack_5c;
  int iStack_58;
  int iStack_54;
  int iStack_50;
  int iStack_4c;
  int iStack_48;
  int iStack_44;
  int iStack_40;
  int iStack_30;
  uint uStack_20;
  uint uStack_10;
  
  uStack_60 = 6;
  for (iVar10 = 0; iVar10 < 0x20; iVar10 = iVar10 + 1) {
    if (*(char *)((int)pCGpffff86b4 +
                 iVar10 * 0xc + (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 +
                 0x1bc) == '#') {
      uStack_60 = *(undefined4 *)
                   ((int)pCGpffff86b4 +
                   iVar10 * 0xc + (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 +
                   0x1c0);
    }
  }
  if ((pCGpffff86b4->aChr[param_3].bFlagsA1 & 1) == 0) {
    iStack_8c = ourBtlSaveDat + pCGpffff86b4->aChr[param_3].nCharId * 0x10 + 0xf44;
  }
  else {
    iStack_8c = ourBtlSaveDat + pCGpffff86b4->aChr[param_3].nSubId * 0x10 + 0x1004;
  }
  iStack_40 = param_1;
  iStack_30 = param_2;
  uStack_20 = param_3;
  uStack_10 = param_4;
  if (*(short *)(param_1 + param_2 * 0x16c + 0x32) == 0) {
    iStack_48 = 1;
    *(undefined2 *)(param_1 + param_2 * 0x16c + 0x32) = 1;
    *(undefined2 *)(param_1 + param_2 * 0x16c + 0x34) = 0;
    *(undefined2 *)(param_1 + param_2 * 0x16c + 0x36) = 0;
    *(undefined4 *)(param_1 + param_2 * 0x16c + 0x38) = 0;
    *(undefined2 *)(param_1 + param_2 * 0x16c + 0x90) = 8;
    AddOT__7MenuObjFv(param_1 + param_2 * 0x16c + 0x7c);
    iVar10 = iStack_40 + iStack_30 * 0x16c;
    *(byte *)(iVar10 + 0x30) = *(byte *)(iVar10 + 0x30) & 0xfb | 4;
    Create__10MenuWindowFUcUcffff(0,0,0x44000000,0x43e00000,iStack_40 + iStack_30 * 0x16c + 0x7c,0,1);
    *(undefined4 *)(iStack_40 + iStack_30 * 0x16c + 0x178) = 0;
    iVar10 = iStack_40 + iStack_30 * 0x16c;
    *(byte *)(iVar10 + 0x30) = *(byte *)(iVar10 + 0x30) & 0xf7 | 8;
  }
  else {
    iStack_48 = 0;
  }
  if (iStack_48 == 0) {
    if ((long)((ulong)*(byte *)(iStack_40 + iStack_30 * 0x16c + 0x30) << 0x3e) < 0) {
      ClearImage__8FontDrawFv(iStack_40 + iStack_30 * 0x16c + 0x3c);
    }
  }
  else {
    Create__8FontDrawF6GS_PSMUsUsUcUiP10ClutRaster(iStack_40 + iStack_30 * 0x16c + 0x3c,0x2c,0x100,0x200,1,0,0);
    iVar10 = iStack_40 + iStack_30 * 0x16c;
    *(byte *)(iVar10 + 0x30) = *(byte *)(iVar10 + 0x30) & 0xfd | 2;
    if (((ulong)*(ushort *)(iStack_40 + iStack_30 * 0x16c + 0x30) & 0xfff) >> 4 == 0) {
      uVar7 = __nwa__FUi(0x390);
      uVar5 = __construct_new_array(uVar7,0x27bfd0,0x27c030,0x80,7);
      *(undefined4 *)(iStack_40 + iStack_30 * 0x16c + 0x130) = uVar5;
      iVar10 = iStack_40 + iStack_30 * 0x16c;
      *(ushort *)(iVar10 + 0x30) = *(ushort *)(iVar10 + 0x30) & 0xf00f | 0x70;
    }
    if (*(int *)(iStack_40 + iStack_30 * 0x16c + 0x138) == 0) {
      uVar7 = __nwa__FUi(0x130);
      uVar5 = __construct_new_array(uVar7,0x277820,0x277890,0x30,6);
      *(undefined4 *)(iStack_40 + iStack_30 * 0x16c + 0x138) = uVar5;
    }
    if (*(int *)(iStack_40 + iStack_30 * 0x16c + 0x13c) == 0) {
      uVar7 = __nwa__FUi(0xc70);
      uVar5 = __construct_new_array(uVar7,0x266140,0x2661a0,0x60,0x21);
      *(undefined4 *)(iStack_40 + iStack_30 * 0x16c + 0x13c) = uVar5;
    }
    if (*(int *)(iStack_40 + iStack_30 * 0x16c + 0x144) == 0) {
      uVar7 = __nwa__FUi(0x88);
      uVar5 = __construct_new_array(uVar7,0x28d000,0x28d070,0x28,3);
      *(undefined4 *)(iStack_40 + iStack_30 * 0x16c + 0x144) = uVar5;
    }
    if (*(int *)(iStack_40 + iStack_30 * 0x16c + 0x148) == 0) {
      uVar7 = __nwa__FUi(0x118);
      uVar5 = __construct_new_array(uVar7,0x276640,0x2766d0,0x84,2);
      *(undefined4 *)(iStack_40 + iStack_30 * 0x16c + 0x148) = uVar5;
    }
  }
  iStack_84 = *(int *)(iStack_40 + iStack_30 * 0x16c + 0x138);
  iVar10 = *(int *)(iStack_40 + iStack_30 * 0x16c + 0x130);
  iVar14 = *(int *)(iStack_40 + iStack_30 * 0x16c + 0x13c);
  iStack_88 = *(int *)(iStack_40 + iStack_30 * 0x16c + 0x144);
  iVar8 = *(int *)(iStack_40 + iStack_30 * 0x16c + 0x148);
  iVar13 = 0;
  iStack_50 = 0;
  iStack_4c = 0;
  for (iVar12 = 0; iVar12 < 4; iVar12 = iVar12 + 1) {
    acStack_64[iVar12] = '\0';
    cVar2 = *(char *)(iStack_8c + iVar12 * 4);
    if (cVar2 == '\x03') {
      if ((pCGpffff86b4->aChr[uStack_20].bFlagsB & 1) == 0) {
        if ((pCGpffff86b4->aChr[uStack_20].bFlagsA1 & 1) == 0) {
          iStack_44 = (int)pCGpffff86b4->aChr[uStack_20].nCharId;
        }
        else {
          switch(pCGpffff86b4->aChr[uStack_20].nSubId) {
          case 0:
          case 1:
            iStack_44 = 0xc;
            break;
          case 2:
          case 3:
            iStack_44 = 0xd;
            break;
          case 4:
          case 5:
            iStack_44 = 0xe;
            break;
          case 6:
          case 7:
            iStack_44 = 0xf;
            break;
          case 8:
          case 9:
            iStack_44 = 0x10;
            break;
          case 10:
          case 0xb:
            iStack_44 = 0x11;
            break;
          case 0xc:
          case 0xd:
            iStack_44 = 0x12;
            break;
          case 0xe:
            iStack_44 = 0x13;
            break;
          case 0xf:
            iStack_44 = 0x14;
            break;
          case 0x10:
            iStack_44 = 0x15;
          }
        }
        iStack_94 = GetRegDat__9RegDatApiFiii(0x36,iStack_44,0xffffffffffffffff);
        iStack_5c = DecMPp__7CBattleFiiii
                              (pCGpffff86b4,uStack_20,1,(int)*(short *)(iStack_8c + iVar12 * 4 + 2),
                               (uint)*(ushort *)
                                      (iStack_94 + *(short *)(iStack_8c + iVar12 * 4 + 2) * 0x40 +
                                      0x1e));
        iStack_5c = iStack_5c / 100;
        if ((long)iStack_5c <= (long)pCGpffff86b4->aChr[uStack_20].nMp) {
          acStack_64[iVar12] = '\x01';
        }
        abStack_68[iVar12] =
             (byte)(((ulong)*(byte *)(iStack_94 + *(short *)(iStack_8c + iVar12 * 4 + 2) * 0x40 + 6)
                    << 0x3c) >> 0x3d);
        abStack_6c[iVar12] =
             *(byte *)(iStack_94 + *(short *)(iStack_8c + iVar12 * 4 + 2) * 0x40 + 4) & 7;
      }
    }
    else if (cVar2 == '\x02') {
      iStack_90 = GetRegDat__9RegDatApiFiii(0x38,0,0xffffffffffffffff);
      iStack_5c = DecMPp__7CBattleFiiii
                            (pCGpffff86b4,uStack_20,2,(int)*(short *)(iStack_8c + iVar12 * 4 + 2),
                             (uint)*(ushort *)
                                    (iStack_90 + *(short *)(iStack_8c + iVar12 * 4 + 2) * 0x44 +
                                    0x1e));
      iStack_5c = iStack_5c / 100;
      if ((long)iStack_5c <= (long)pCGpffff86b4->aChr[uStack_20].nMp) {
        acStack_64[iVar12] = '\x01';
      }
      abStack_68[iVar12] =
           (byte)(((ulong)*(byte *)(iStack_90 + *(short *)(iStack_8c + iVar12 * 4 + 2) * 0x44 + 6)
                  << 0x3c) >> 0x3d);
      abStack_6c[iVar12] =
           *(byte *)(iStack_90 + *(short *)(iStack_8c + iVar12 * 4 + 2) * 0x44 + 4) & 7;
    }
    else if (cVar2 == '\x01') {
      if (*(char *)(ourBtlSaveDat + (uint)*(byte *)(ourBtlSaveDat + 2) * 0x200 +
                    (int)*(short *)(iStack_8c + iVar12 * 4 + 2) + 0x944) != '\0') {
        acStack_64[iVar12] = '\x01';
      }
      abStack_68[iVar12] = *(byte *)(iStack_8c + iVar12 * 4 + 1);
      abStack_6c[iVar12] = (byte)uStack_60;
    }
    else if (cVar2 == '\0') {
      acStack_64[iVar12] = '\x01';
      abStack_68[iVar12] = *(byte *)(iStack_8c + iVar12 * 4 + 1);
      abStack_6c[iVar12] = (byte)uStack_60;
    }
  }
  if (iStack_48 != 0) {
    CreatePacket__10MenuPacketFUs(iStack_88 + iStack_50 * 0x28 + 0x18,4);
    SetRegister__12MenuRegisterFiUlUl(iStack_88 + iStack_50 * 0x28,0,0x42,0x44);
    *(undefined2 *)(iStack_88 + iStack_50 * 0x28 + 0x14) = 0;
    AddPriority__12MenuObjTableFP7MenuObj(iStack_40 + iStack_30 * 0x16c + 0x94,iStack_88 + iStack_50 * 0x28);
    Create__11MenuPolygonFUcUc(iVar8,0,1);
    *(undefined2 *)(iVar8 + 0x14) = 0;
    SetVertex__11MenuPolygonFiffb(0,0x439e8000,iVar8,0,1);
    SetColor__11MenuPolygonFiUcUcUc(iVar8,0,0,0,0);
    *(undefined1 *)(iVar8 + 0x4f) = 0;
    uVar17 = (ulong)*(byte *)(iVar8 + 0x11) & 0xffffffffffffffef | 0x10;
    *(char *)(iVar8 + 0x11) = (char)uVar17;
    *(byte *)(iVar8 + 0x10) =
         *(byte *)(iVar8 + 0x10) & 0xef | (byte)((uint)((uVar17 << 0x3b) >> 0x3f) << 4);
    SetVertex__11MenuPolygonFiffb(0,0x43ae8000,iVar8,1,1);
    SetColor__11MenuPolygonFiUcUcUc(iVar8,1,0,0,0);
    *(undefined1 *)(iVar8 + 0x77) = 0x40;
    *(byte *)(iVar8 + 0x11) = *(byte *)(iVar8 + 0x11) & 0xef | 0x10;
    *(byte *)(iVar8 + 0x10) = *(byte *)(iVar8 + 0x10) & 0xef | 0x10;
    SetVertex__11MenuPolygonFiffb(0x44004000,0x439e8000,iVar8,2,1);
    SetColor__11MenuPolygonFiUcUcUc(iVar8,2,0,0,0);
    *(undefined1 *)(iVar8 + 0x7b) = 0;
    uVar17 = (ulong)*(byte *)(iVar8 + 0x11) & 0xffffffffffffffef | 0x10;
    *(char *)(iVar8 + 0x11) = (char)uVar17;
    *(byte *)(iVar8 + 0x10) =
         *(byte *)(iVar8 + 0x10) & 0xef | (byte)((uint)((uVar17 << 0x3b) >> 0x3f) << 4);
    SetVertex__11MenuPolygonFiffb(0x43ff8000,0x43ae8000,iVar8,3,1);
    SetColor__11MenuPolygonFiUcUcUc(iVar8,3,0,0,0);
    *(undefined1 *)(iVar8 + 0x7f) = 0x40;
    uVar17 = (ulong)*(byte *)(iVar8 + 0x11) & 0xffffffffffffffef | 0x10;
    *(char *)(iVar8 + 0x11) = (char)uVar17;
    *(byte *)(iVar8 + 0x10) =
         *(byte *)(iVar8 + 0x10) & 0xef | (byte)((uint)((uVar17 << 0x3b) >> 0x3f) << 4);
    *(byte *)(iVar8 + 0x12) = *(byte *)(iVar8 + 0x12) & 0xfe | 1;
    *(undefined2 *)(iVar8 + 0x1c) = 0;
    *(undefined2 *)(iVar8 + 0x1e) = 0;
    AddPlace__10MenuWindowFP9MenuPlace(iStack_40 + iStack_30 * 0x16c + 0x7c,iVar8);
    Create__11MenuPolygonFUcUc(iVar8 + 0x84,0,1);
    *(undefined2 *)(iVar8 + 0x98) = 0;
    SetVertex__11MenuPolygonFiffb(0,0x43ae8000,iVar8 + 0x84,0,1);
    SetColor__11MenuPolygonFiUcUcUc(iVar8 + 0x84,0,0,0,0);
    *(undefined1 *)(iVar8 + 0xd3) = 0x40;
    uVar17 = (ulong)*(byte *)(iVar8 + 0x95) & 0xffffffffffffffef | 0x10;
    *(char *)(iVar8 + 0x95) = (char)uVar17;
    *(byte *)(iVar8 + 0x94) =
         *(byte *)(iVar8 + 0x94) & 0xef | (byte)((uint)((uVar17 << 0x3b) >> 0x3f) << 4);
    SetVertex__11MenuPolygonFiffb(0,0x43e08000,iVar8 + 0x84,1,1);
    SetColor__11MenuPolygonFiUcUcUc(iVar8 + 0x84,1,0,0,0);
    *(undefined1 *)(iVar8 + 0xfb) = 0x40;
    uVar17 = (ulong)*(byte *)(iVar8 + 0x95) & 0xffffffffffffffef | 0x10;
    *(char *)(iVar8 + 0x95) = (char)uVar17;
    *(byte *)(iVar8 + 0x94) =
         *(byte *)(iVar8 + 0x94) & 0xef | (byte)((uint)((uVar17 << 0x3b) >> 0x3f) << 4);
    SetVertex__11MenuPolygonFiffb(0x44004000,0x43ae8000,iVar8 + 0x84,2,1);
    SetColor__11MenuPolygonFiUcUcUc(iVar8 + 0x84,2,0,0,0);
    *(undefined1 *)(iVar8 + 0xff) = 0x40;
    uVar17 = (ulong)*(byte *)(iVar8 + 0x95) & 0xffffffffffffffef | 0x10;
    *(char *)(iVar8 + 0x95) = (char)uVar17;
    *(byte *)(iVar8 + 0x94) =
         *(byte *)(iVar8 + 0x94) & 0xef | (byte)((uint)((uVar17 << 0x3b) >> 0x3f) << 4);
    SetVertex__11MenuPolygonFiffb(0x43ff8000,0x43e08000,iVar8 + 0x84,3,1);
    SetColor__11MenuPolygonFiUcUcUc(iVar8 + 0x84,3,0,0,0);
    *(undefined1 *)(iVar8 + 0x103) = 0x40;
    uVar17 = (ulong)*(byte *)(iVar8 + 0x95) & 0xffffffffffffffef | 0x10;
    *(char *)(iVar8 + 0x95) = (char)uVar17;
    *(byte *)(iVar8 + 0x94) =
         *(byte *)(iVar8 + 0x94) & 0xef | (byte)((uint)((uVar17 << 0x3b) >> 0x3f) << 4);
    *(byte *)(iVar8 + 0x96) = *(byte *)(iVar8 + 0x96) & 0xfe | 1;
    *(undefined2 *)(iVar8 + 0xa0) = 1;
    *(undefined2 *)(iVar8 + 0xa2) = 0;
    AddPlace__10MenuWindowFP9MenuPlace(iStack_40 + iStack_30 * 0x16c + 0x7c,iVar8 + 0x84);
  }
  iStack_50 = iStack_50 + 1;
  if (iStack_48 != 0) {
    iStack_b0 = *(int *)&pCGpffff86b4->field_0x4304;
    uStack_e4 = *(undefined4 *)(iStack_b0 + (uint)*(ushort *)(iStack_b0 + 10) * 4 + 0xc);
    uStack_e0 = uStack_e4;
    uVar7 = GetTex0__6JRCTexFb(*(undefined4 *)&pCGpffff86b4->field_0x4304,0);
    Create__11SendOnLocalFP4_QWDUl(iStack_84 + iStack_4c * 0x30,uStack_e4,uVar7);
    *(undefined2 *)(iStack_84 + iStack_4c * 0x30 + 0x14) = 1;
    AddPriority__12MenuObjTableFP7MenuObj(iStack_40 + iStack_30 * 0x16c + 0x94,iStack_84 + iStack_4c * 0x30);
    CreatePacket__10MenuPacketFUs(iStack_88 + iStack_50 * 0x28 + 0x18,4);
    SetRegister__12MenuRegisterFiUlUl(iStack_88 + iStack_50 * 0x28,0,0x42,0x48);
    *(undefined2 *)(iStack_88 + iStack_50 * 0x28 + 0x14) = 1;
    AddPriority__12MenuObjTableFP7MenuObj(iStack_40 + iStack_30 * 0x16c + 0x94,iStack_88 + iStack_50 * 0x28);
    Create__10MenuSpriteFUc(iVar14,1);
    *(byte *)(iVar14 + 0x21) = *(byte *)(iVar14 + 0x21) & 0xbf | 0x40;
    uVar17 = (ulong)*(byte *)(iVar14 + 0x11) & 0xfffffffffffffffd | 2;
    *(char *)(iVar14 + 0x11) = (char)uVar17;
    *(byte *)(iVar14 + 0x10) =
         *(byte *)(iVar14 + 0x10) & 0xfd | (byte)((uint)((uVar17 << 0x3e) >> 0x3f) << 1);
    *(undefined2 *)(iVar14 + 0x14) = 2;
    (**(code **)(*(int *)(iVar14 + 8) + 0x24))(0x435c0000,0x43b60000);
    uVar7 = SetUV__10MenuSpriteFUsUsUsUs(iVar14,0,0,0x25,0x46);
    uVar7 = (**(code **)(*(int *)(iVar14 + 8) + 0x28))(0x42140000,0x428c0000,iVar14,iVar14,uVar7);
    (**(code **)(*(int *)(iVar14 + 8) + 0x30))(iVar14,0x80,0x40,0x10,uVar7);
    (**(code **)(*(int *)(iVar14 + 8) + 0x2c))(iVar14,0x40);
    *(byte *)(iVar14 + 0x12) = *(byte *)(iVar14 + 0x12) & 0xfe | 1;
    *(undefined2 *)(iVar14 + 0x1c) = 0;
    *(undefined2 *)(iVar14 + 0x1e) = 1;
    AddPlace__10MenuWindowFP9MenuPlace(iStack_40 + iStack_30 * 0x16c + 0x7c,iVar14);
    Create__10MenuSpriteFUc(iVar14 + 0x60,1);
    *(byte *)(iVar14 + 0x81) = *(byte *)(iVar14 + 0x81) & 0xbf | 0x40;
    uVar17 = (ulong)*(byte *)(iVar14 + 0x71) & 0xfffffffffffffffd | 2;
    *(char *)(iVar14 + 0x71) = (char)uVar17;
    *(byte *)(iVar14 + 0x70) =
         *(byte *)(iVar14 + 0x70) & 0xfd | (byte)((uint)((uVar17 << 0x3e) >> 0x3f) << 1);
    *(undefined2 *)(iVar14 + 0x74) = 2;
    (**(code **)(*(int *)(iVar14 + 0x68) + 0x24))(0x437e0000,0x43b60000);
    uVar7 = SetUV__10MenuSpriteFUsUsUsUs(iVar14 + 0x60,0x25,0,0,0x46);
    (**(code **)(*(int *)(iVar14 + 0x68) + 0x28))(0x42140000,0x428c0000,iVar14 + 0x60,uVar7);
    (**(code **)(*(int *)(iVar14 + 0x68) + 0x30))(iVar14 + 0x60,0x80,0x40,0x10);
    (**(code **)(*(int *)(iVar14 + 0x68) + 0x2c))(iVar14 + 0x60,0x40);
    *(byte *)(iVar14 + 0x72) = *(byte *)(iVar14 + 0x72) & 0xfe | 1;
    *(undefined2 *)(iVar14 + 0x7c) = 1;
    *(undefined2 *)(iVar14 + 0x7e) = 1;
    AddPlace__10MenuWindowFP9MenuPlace(iStack_40 + iStack_30 * 0x16c + 0x7c,iVar14 + 0x60);
  }
  iStack_50 = iStack_50 + 1;
  iStack_4c = iStack_4c + 1;
  if (iStack_48 != 0) {
    Create__10MenuSpriteFUc(iVar14 + 0xc0,1);
    *(byte *)(iVar14 + 0xe1) = *(byte *)(iVar14 + 0xe1) & 0xbf | 0x40;
    uVar17 = (ulong)*(byte *)(iVar14 + 0xd1) & 0xfffffffffffffffd | 2;
    *(char *)(iVar14 + 0xd1) = (char)uVar17;
    *(byte *)(iVar14 + 0xd0) =
         *(byte *)(iVar14 + 0xd0) & 0xfd | (byte)((uint)((uVar17 << 0x3e) >> 0x3f) << 1);
    *(undefined2 *)(iVar14 + 0xd4) = 3;
    (**(code **)(*(int *)(iVar14 + 200) + 0x24))(0x435f0000,0x43ba8000);
    SetUV__10MenuSpriteFUsUsUsUs(iVar14 + 0xc0,0x47,0x2a,0x56,0x3d);
    (**(code **)(*(int *)(iVar14 + 200) + 0x28))(0x41700000,0x41980000);
    *(byte *)(iVar14 + 0xd2) = *(byte *)(iVar14 + 0xd2) & 0xfe | 1;
    *(undefined2 *)(iVar14 + 0xdc) = 0;
    *(undefined2 *)(iVar14 + 0xde) = 2;
    AddPlace__10MenuWindowFP9MenuPlace(iStack_40 + iStack_30 * 0x16c + 0x7c,iVar14 + 0xc0);
    Create__10MenuSpriteFUc(iVar14 + 0x120,1);
    *(byte *)(iVar14 + 0x141) = *(byte *)(iVar14 + 0x141) & 0xbf | 0x40;
    uVar17 = (ulong)*(byte *)(iVar14 + 0x131) & 0xfffffffffffffffd | 2;
    *(char *)(iVar14 + 0x131) = (char)uVar17;
    *(byte *)(iVar14 + 0x130) =
         *(byte *)(iVar14 + 0x130) & 0xfd | (byte)((uint)((uVar17 << 0x3e) >> 0x3f) << 1);
    *(undefined2 *)(iVar14 + 0x134) = 3;
    (**(code **)(*(int *)(iVar14 + 0x128) + 0x24))(0x436e0000,0x43ba8000);
    SetUV__10MenuSpriteFUsUsUsUs(iVar14 + 0x120,0x67,0x2a,0x71,0x3d);
    (**(code **)(*(int *)(iVar14 + 0x128) + 0x28))(0x41200000,0x41980000);
    *(byte *)(iVar14 + 0x132) = *(byte *)(iVar14 + 0x132) & 0xfe | 1;
    *(undefined2 *)(iVar14 + 0x13c) = 1;
    *(undefined2 *)(iVar14 + 0x13e) = 2;
    AddPlace__10MenuWindowFP9MenuPlace(iStack_40 + iStack_30 * 0x16c + 0x7c,iVar14 + 0x120);
  }
  if ((uStack_10 == 0) && (acStack_64[0] != '\0')) {
    (**(code **)(*(int *)(iVar14 + 200) + 0x30))(iVar14 + 0xc0,0x40,0x80,0x60);
    (**(code **)(*(int *)(iVar14 + 200) + 0x2c))(iVar14 + 0xc0,0x60);
    (**(code **)(*(int *)(iVar14 + 0x128) + 0x30))(iVar14 + 0x120,0x40,0x80,0x60);
    (**(code **)(*(int *)(iVar14 + 0x128) + 0x2c))(iVar14 + 0x120,0x60);
  }
  else if (acStack_64[0] == '\0') {
    uVar7 = (**(code **)(*(int *)(iVar14 + 200) + 0x30))(iVar14 + 0xc0,0x80,0x40,0x10);
    (**(code **)(*(int *)(iVar14 + 200) + 0x2c))(iVar14 + 0xc0,0x20,iVar14 + 0xc0,0x20,uVar7);
    (**(code **)(*(int *)(iVar14 + 0x128) + 0x30))(iVar14 + 0x120,0x80,0x40,0x10);
    (**(code **)(*(int *)(iVar14 + 0x128) + 0x2c))(iVar14 + 0x120,0x20);
  }
  else {
    (**(code **)(*(int *)(iVar14 + 200) + 0x30))(iVar14 + 0xc0,0x80,0x40,0x10);
    (**(code **)(*(int *)(iVar14 + 200) + 0x2c))(iVar14 + 0xc0,0x40);
    uVar7 = (**(code **)(*(int *)(iVar14 + 0x128) + 0x30))(iVar14 + 0x120,0x80,0x40,0x10);
    (**(code **)(*(int *)(iVar14 + 0x128) + 0x2c))(iVar14 + 0x120,0x40,uVar7);
  }
  if (iStack_48 != 0) {
    Create__10MenuSpriteFUc(iVar14 + 0x180,1);
    *(byte *)(iVar14 + 0x1a1) = *(byte *)(iVar14 + 0x1a1) & 0xbf | 0x40;
    uVar17 = (ulong)*(byte *)(iVar14 + 0x191) & 0xfffffffffffffffd | 2;
    *(char *)(iVar14 + 0x191) = (char)uVar17;
    *(byte *)(iVar14 + 400) =
         *(byte *)(iVar14 + 400) & 0xfd | (byte)((uint)((uVar17 << 0x3e) >> 0x3f) << 1);
    *(undefined2 *)(iVar14 + 0x194) = 3;
    (**(code **)(*(int *)(iVar14 + 0x188) + 0x24))(0x43848000,0x43ba8000);
    SetUV__10MenuSpriteFUsUsUsUs(iVar14 + 0x180,0x56,0x2a,0x67,0x3d);
    (**(code **)(*(int *)(iVar14 + 0x188) + 0x28))(0x41880000,0x41980000);
    *(byte *)(iVar14 + 0x192) = *(byte *)(iVar14 + 0x192) & 0xfe | 1;
    *(undefined2 *)(iVar14 + 0x19c) = 0;
    *(undefined2 *)(iVar14 + 0x19e) = 3;
    AddPlace__10MenuWindowFP9MenuPlace(iStack_40 + iStack_30 * 0x16c + 0x7c,iVar14 + 0x180);
    Create__10MenuSpriteFUc(iVar14 + 0x1e0,1);
    *(byte *)(iVar14 + 0x201) = *(byte *)(iVar14 + 0x201) & 0xbf | 0x40;
    uVar17 = (ulong)*(byte *)(iVar14 + 0x1f1) & 0xfffffffffffffffd | 2;
    *(char *)(iVar14 + 0x1f1) = (char)uVar17;
    *(byte *)(iVar14 + 0x1f0) =
         *(byte *)(iVar14 + 0x1f0) & 0xfd | (byte)((uint)((uVar17 << 0x3e) >> 0x3f) << 1);
    *(undefined2 *)(iVar14 + 500) = 3;
    (**(code **)(*(int *)(iVar14 + 0x1e8) + 0x24))(0x438c0000,0x43ba8000);
    SetUV__10MenuSpriteFUsUsUsUs(iVar14 + 0x1e0,0x67,0x2a,0x71,0x3d);
    (**(code **)(*(int *)(iVar14 + 0x1e8) + 0x28))(0x41200000,0x41980000);
    *(byte *)(iVar14 + 0x1f2) = *(byte *)(iVar14 + 0x1f2) & 0xfe | 1;
    *(undefined2 *)(iVar14 + 0x1fc) = 1;
    *(undefined2 *)(iVar14 + 0x1fe) = 3;
    AddPlace__10MenuWindowFP9MenuPlace(iStack_40 + iStack_30 * 0x16c + 0x7c,iVar14 + 0x1e0);
  }
  if ((uStack_10 == 1) && (acStack_64[1] != '\0')) {
    (**(code **)(*(int *)(iVar14 + 0x188) + 0x30))(iVar14 + 0x180,0x40,0x80,0x60);
    (**(code **)(*(int *)(iVar14 + 0x188) + 0x2c))(iVar14 + 0x180,0x60);
    (**(code **)(*(int *)(iVar14 + 0x1e8) + 0x30))(iVar14 + 0x1e0,0x40,0x80,0x60);
    (**(code **)(*(int *)(iVar14 + 0x1e8) + 0x2c))(iVar14 + 0x1e0,0x60);
  }
  else if (acStack_64[1] == '\0') {
    (**(code **)(*(int *)(iVar14 + 0x188) + 0x30))(iVar14 + 0x180,0x80,0x40,0x10);
    (**(code **)(*(int *)(iVar14 + 0x188) + 0x2c))(iVar14 + 0x180,0x20);
    (**(code **)(*(int *)(iVar14 + 0x1e8) + 0x30))(iVar14 + 0x1e0,0x80,0x40,0x10);
    (**(code **)(*(int *)(iVar14 + 0x1e8) + 0x2c))(iVar14 + 0x1e0,0x20);
  }
  else {
    (**(code **)(*(int *)(iVar14 + 0x188) + 0x30))(iVar14 + 0x180,0x80,0x40,0x10);
    (**(code **)(*(int *)(iVar14 + 0x188) + 0x2c))(iVar14 + 0x180,0x40);
    (**(code **)(*(int *)(iVar14 + 0x1e8) + 0x30))(iVar14 + 0x1e0,0x80,0x40,0x10);
    (**(code **)(*(int *)(iVar14 + 0x1e8) + 0x2c))(iVar14 + 0x1e0,0x40);
  }
  if (iStack_48 != 0) {
    Create__10MenuSpriteFUc(iVar14 + 0x240,1);
    *(byte *)(iVar14 + 0x261) = *(byte *)(iVar14 + 0x261) & 0xbf | 0x40;
    *(byte *)(iVar14 + 0x251) = *(byte *)(iVar14 + 0x251) & 0xfd | 2;
    *(byte *)(iVar14 + 0x250) = *(byte *)(iVar14 + 0x250) & 0xfd | 2;
    *(undefined2 *)(iVar14 + 0x254) = 3;
    (**(code **)(*(int *)(iVar14 + 0x248) + 0x24))(0x434c0000,0x43ca8000);
    SetUV__10MenuSpriteFUsUsUsUs(iVar14 + 0x240,0x47,0x2a,0x56,0x3d);
    (**(code **)(*(int *)(iVar14 + 0x248) + 0x28))(0x41700000,0x41980000);
    *(byte *)(iVar14 + 0x252) = *(byte *)(iVar14 + 0x252) & 0xfe | 1;
    *(undefined2 *)(iVar14 + 0x25c) = 0;
    *(undefined2 *)(iVar14 + 0x25e) = 4;
    uVar7 = AddPlace__10MenuWindowFP9MenuPlace(iStack_40 + iStack_30 * 0x16c + 0x7c,iVar14 + 0x240);
    Create__10MenuSpriteFUc(iVar14 + 0x2a0,1,uVar7);
    *(byte *)(iVar14 + 0x2c1) = *(byte *)(iVar14 + 0x2c1) & 0xbf | 0x40;
    uVar17 = (ulong)*(byte *)(iVar14 + 0x2b1) & 0xfffffffffffffffd | 2;
    *(char *)(iVar14 + 0x2b1) = (char)uVar17;
    *(byte *)(iVar14 + 0x2b0) =
         *(byte *)(iVar14 + 0x2b0) & 0xfd | (byte)((uint)((uVar17 << 0x3e) >> 0x3f) << 1);
    *(undefined2 *)(iVar14 + 0x2b4) = 3;
    (**(code **)(*(int *)(iVar14 + 0x2a8) + 0x24))(0x435a0000,0x43ca8000);
    SetUV__10MenuSpriteFUsUsUsUs(iVar14 + 0x2a0,0x71,0x2a,0x7c,0x3d);
    (**(code **)(*(int *)(iVar14 + 0x2a8) + 0x28))(0x41300000,0x41980000);
    *(byte *)(iVar14 + 0x2b2) = *(byte *)(iVar14 + 0x2b2) & 0xfe | 1;
    *(undefined2 *)(iVar14 + 700) = 1;
    *(undefined2 *)(iVar14 + 0x2be) = 4;
    AddPlace__10MenuWindowFP9MenuPlace(iStack_40 + iStack_30 * 0x16c + 0x7c,iVar14 + 0x2a0);
  }
  if ((uStack_10 == 2) && (acStack_64[2] != '\0')) {
    (**(code **)(*(int *)(iVar14 + 0x248) + 0x30))(iVar14 + 0x240,0x40,0x80,0x60);
    (**(code **)(*(int *)(iVar14 + 0x248) + 0x2c))(iVar14 + 0x240,0x60);
    (**(code **)(*(int *)(iVar14 + 0x2a8) + 0x30))(iVar14 + 0x2a0,0x40,0x80,0x60);
    (**(code **)(*(int *)(iVar14 + 0x2a8) + 0x2c))(iVar14 + 0x2a0,0x60);
  }
  else if (acStack_64[2] == '\0') {
    (**(code **)(*(int *)(iVar14 + 0x248) + 0x30))(iVar14 + 0x240,0x80,0x40,0x10);
    (**(code **)(*(int *)(iVar14 + 0x248) + 0x2c))(iVar14 + 0x240,0x20);
    (**(code **)(*(int *)(iVar14 + 0x2a8) + 0x30))(iVar14 + 0x2a0,0x80,0x40,0x10);
    (**(code **)(*(int *)(iVar14 + 0x2a8) + 0x2c))(iVar14 + 0x2a0,0x20);
  }
  else {
    uVar7 = (**(code **)(*(int *)(iVar14 + 0x248) + 0x30))(iVar14 + 0x240,0x80,0x40,0x10);
    (**(code **)(*(int *)(iVar14 + 0x248) + 0x2c))(iVar14 + 0x240,0x40,0x240,uVar7);
    (**(code **)(*(int *)(iVar14 + 0x2a8) + 0x30))(iVar14 + 0x2a0,0x80,0x40,0x10);
    (**(code **)(*(int *)(iVar14 + 0x2a8) + 0x2c))(iVar14 + 0x2a0,0x40);
  }
  if (iStack_48 != 0) {
    Create__10MenuSpriteFUc(iVar14 + 0x300,1);
    *(byte *)(iVar14 + 0x321) = *(byte *)(iVar14 + 0x321) & 0xbf | 0x40;
    uVar17 = (ulong)*(byte *)(iVar14 + 0x311) & 0xfffffffffffffffd | 2;
    *(char *)(iVar14 + 0x311) = (char)uVar17;
    *(byte *)(iVar14 + 0x310) =
         *(byte *)(iVar14 + 0x310) & 0xfd | (byte)((uint)((uVar17 << 0x3e) >> 0x3f) << 1);
    *(undefined2 *)(iVar14 + 0x314) = 3;
    (**(code **)(*(int *)(iVar14 + 0x308) + 0x24))(0x438c8000,0x43ca8000);
    SetUV__10MenuSpriteFUsUsUsUs(iVar14 + 0x300,0x56,0x2a,0x67,0x3d);
    (**(code **)(*(int *)(iVar14 + 0x308) + 0x28))(0x41880000,0x41980000);
    *(byte *)(iVar14 + 0x312) = *(byte *)(iVar14 + 0x312) & 0xfe | 1;
    *(undefined2 *)(iVar14 + 0x31c) = 0;
    *(undefined2 *)(iVar14 + 0x31e) = 5;
    AddPlace__10MenuWindowFP9MenuPlace(iStack_40 + iStack_30 * 0x16c + 0x7c,iVar14 + 0x300);
    Create__10MenuSpriteFUc(iVar14 + 0x360,1);
    *(byte *)(iVar14 + 0x381) = *(byte *)(iVar14 + 0x381) & 0xbf | 0x40;
    uVar17 = (ulong)*(byte *)(iVar14 + 0x371) & 0xfffffffffffffffd | 2;
    *(char *)(iVar14 + 0x371) = (char)uVar17;
    *(byte *)(iVar14 + 0x370) =
         *(byte *)(iVar14 + 0x370) & 0xfd | (byte)((uint)((uVar17 << 0x3e) >> 0x3f) << 1);
    *(undefined2 *)(iVar14 + 0x374) = 3;
    (**(code **)(*(int *)(iVar14 + 0x368) + 0x24))(0x43938000,0x43ca8000);
    SetUV__10MenuSpriteFUsUsUsUs(iVar14 + 0x360,0x71,0x2a,0x7c,0x3d);
    (**(code **)(*(int *)(iVar14 + 0x368) + 0x28))(0x41300000,0x41980000);
    *(byte *)(iVar14 + 0x372) = *(byte *)(iVar14 + 0x372) & 0xfe | 1;
    *(undefined2 *)(iVar14 + 0x37c) = 1;
    *(undefined2 *)(iVar14 + 0x37e) = 5;
    AddPlace__10MenuWindowFP9MenuPlace(iStack_40 + iStack_30 * 0x16c + 0x7c,iVar14 + 0x360);
  }
  if ((uStack_10 == 3) && (acStack_64[3] != '\0')) {
    uVar7 = (**(code **)(*(int *)(iVar14 + 0x308) + 0x30))(iVar14 + 0x300,0x40,0x80,0x60);
    (**(code **)(*(int *)(iVar14 + 0x308) + 0x2c))(iVar14 + 0x300,0x60,0x18,uVar7);
    (**(code **)(*(int *)(iVar14 + 0x368) + 0x30))(iVar14 + 0x360,0x40,0x80,0x60);
    (**(code **)(*(int *)(iVar14 + 0x368) + 0x2c))(iVar14 + 0x360,0x60);
  }
  else if (acStack_64[3] == '\0') {
    (**(code **)(*(int *)(iVar14 + 0x308) + 0x30))(iVar14 + 0x300,0x80,0x40,0x10);
    (**(code **)(*(int *)(iVar14 + 0x308) + 0x2c))(iVar14 + 0x300,0x20);
    (**(code **)(*(int *)(iVar14 + 0x368) + 0x30))(iVar14 + 0x360,0x80,0x40,0x10);
    (**(code **)(*(int *)(iVar14 + 0x368) + 0x2c))(iVar14 + 0x360,0x20);
  }
  else {
    (**(code **)(*(int *)(iVar14 + 0x308) + 0x30))(iVar14 + 0x300,0x80,0x40,0x10);
    (**(code **)(*(int *)(iVar14 + 0x308) + 0x2c))(iVar14 + 0x300,0x40);
    (**(code **)(*(int *)(iVar14 + 0x368) + 0x30))(iVar14 + 0x360,0x80,0x40,0x10);
    (**(code **)(*(int *)(iVar14 + 0x368) + 0x2c))(iVar14 + 0x360,0x40);
  }
  if (iStack_48 != 0) {
    Create__10MenuSpriteFUc(iVar14 + 0x3c0,1);
    *(byte *)(iVar14 + 0x3e1) = *(byte *)(iVar14 + 0x3e1) & 0xbf | 0x40;
    uVar17 = (ulong)*(byte *)(iVar14 + 0x3d1) & 0xfffffffffffffffd | 2;
    *(char *)(iVar14 + 0x3d1) = (char)uVar17;
    *(byte *)(iVar14 + 0x3d0) =
         *(byte *)(iVar14 + 0x3d0) & 0xfd | (byte)((uint)((uVar17 << 0x3e) >> 0x3f) << 1);
    *(undefined2 *)(iVar14 + 0x3d4) = 4;
    (**(code **)(*(int *)(iVar14 + 0x3c8) + 0x24))(0x43400000,0x43b60000);
    SetUV__10MenuSpriteFUsUsUsUs(iVar14 + 0x3c0,0x25,0x1f,0x45,0x43);
    (**(code **)(*(int *)(iVar14 + 0x3c8) + 0x28))(0x42000000,0x42100000);
    *(byte *)(iVar14 + 0x3d2) = *(byte *)(iVar14 + 0x3d2) & 0xfe | 1;
    *(undefined2 *)(iVar14 + 0x3dc) = 0;
    *(undefined2 *)(iVar14 + 0x3de) = 6;
    AddPlace__10MenuWindowFP9MenuPlace(iStack_40 + iStack_30 * 0x16c + 0x7c,iVar14 + 0x3c0);
  }
  if ((uStack_10 == 0) && (acStack_64[0] != '\0')) {
    (**(code **)(*(int *)(iVar14 + 0x3c8) + 0x30))(iVar14 + 0x3c0,0x40,0x80,0x60);
    (**(code **)(*(int *)(iVar14 + 0x3c8) + 0x2c))(iVar14 + 0x3c0,0x60);
  }
  else if (acStack_64[0] == '\0') {
    (**(code **)(*(int *)(iVar14 + 0x3c8) + 0x30))(iVar14 + 0x3c0,0x80,0x40,0x10);
    (**(code **)(*(int *)(iVar14 + 0x3c8) + 0x2c))(iVar14 + 0x3c0,0x20);
  }
  else {
    (**(code **)(*(int *)(iVar14 + 0x3c8) + 0x30))(iVar14 + 0x3c0,0x80,0x40,0x10);
    (**(code **)(*(int *)(iVar14 + 0x3c8) + 0x2c))(iVar14 + 0x3c0,0x40);
  }
  if (iStack_48 != 0) {
    Create__10MenuSpriteFUc(iVar14 + 0x420,1);
    *(byte *)(iVar14 + 0x441) = *(byte *)(iVar14 + 0x441) & 0xbf | 0x40;
    uVar17 = (ulong)*(byte *)(iVar14 + 0x431) & 0xfffffffffffffffd | 2;
    *(char *)(iVar14 + 0x431) = (char)uVar17;
    *(byte *)(iVar14 + 0x430) =
         *(byte *)(iVar14 + 0x430) & 0xfd | (byte)((uint)((uVar17 << 0x3e) >> 0x3f) << 1);
    *(undefined2 *)(iVar14 + 0x434) = 4;
    (**(code **)(*(int *)(iVar14 + 0x428) + 0x24))(0x43900000,0x43b60000);
    SetUV__10MenuSpriteFUsUsUsUs(iVar14 + 0x420,0x25,0x1f,0x45,0x43);
    (**(code **)(*(int *)(iVar14 + 0x428) + 0x28))(0x42000000,0x42100000);
    *(byte *)(iVar14 + 0x432) = *(byte *)(iVar14 + 0x432) & 0xfe | 1;
    *(undefined2 *)(iVar14 + 0x43c) = 0;
    *(undefined2 *)(iVar14 + 0x43e) = 7;
    AddPlace__10MenuWindowFP9MenuPlace(iStack_40 + iStack_30 * 0x16c + 0x7c,iVar14 + 0x420);
  }
  if ((uStack_10 == 1) && (acStack_64[1] != '\0')) {
    (**(code **)(*(int *)(iVar14 + 0x428) + 0x30))(iVar14 + 0x420,0x40,0x80,0x60);
    (**(code **)(*(int *)(iVar14 + 0x428) + 0x2c))(iVar14 + 0x420,0x60);
  }
  else if (acStack_64[1] == '\0') {
    (**(code **)(*(int *)(iVar14 + 0x428) + 0x30))(iVar14 + 0x420,0x80,0x40,0x10);
    (**(code **)(*(int *)(iVar14 + 0x428) + 0x2c))(iVar14 + 0x420,0x20);
  }
  else {
    (**(code **)(*(int *)(iVar14 + 0x428) + 0x30))(iVar14 + 0x420,0x80,0x40,0x10);
    (**(code **)(*(int *)(iVar14 + 0x428) + 0x2c))(iVar14 + 0x420,0x40);
  }
  if (iStack_48 != 0) {
    Create__10MenuSpriteFUc(iVar14 + 0x480,1);
    *(byte *)(iVar14 + 0x4a1) = *(byte *)(iVar14 + 0x4a1) & 0xbf | 0x40;
    uVar17 = (ulong)*(byte *)(iVar14 + 0x491) & 0xfffffffffffffffd | 2;
    *(char *)(iVar14 + 0x491) = (char)uVar17;
    *(byte *)(iVar14 + 0x490) =
         *(byte *)(iVar14 + 0x490) & 0xfd | (byte)((uint)((uVar17 << 0x3e) >> 0x3f) << 1);
    *(undefined2 *)(iVar14 + 0x494) = 4;
    (**(code **)(*(int *)(iVar14 + 0x488) + 0x24))(0x432d0000,0x43c60000);
    SetUV__10MenuSpriteFUsUsUsUs(iVar14 + 0x480,0x25,0x1f,0x45,0x43);
    (**(code **)(*(int *)(iVar14 + 0x488) + 0x28))(0x42000000,0x42100000);
    *(byte *)(iVar14 + 0x492) = *(byte *)(iVar14 + 0x492) & 0xfe | 1;
    *(undefined2 *)(iVar14 + 0x49c) = 0;
    *(undefined2 *)(iVar14 + 0x49e) = 8;
    AddPlace__10MenuWindowFP9MenuPlace(iStack_40 + iStack_30 * 0x16c + 0x7c,iVar14 + 0x480);
  }
  if ((uStack_10 == 2) && (acStack_64[2] != '\0')) {
    (**(code **)(*(int *)(iVar14 + 0x488) + 0x30))(iVar14 + 0x480,0x40,0x80,0x60);
    (**(code **)(*(int *)(iVar14 + 0x488) + 0x2c))(iVar14 + 0x480,0x60);
  }
  else if (acStack_64[2] == '\0') {
    (**(code **)(*(int *)(iVar14 + 0x488) + 0x30))(iVar14 + 0x480,0x80,0x40,0x10);
    (**(code **)(*(int *)(iVar14 + 0x488) + 0x2c))(iVar14 + 0x480,0x20);
  }
  else {
    (**(code **)(*(int *)(iVar14 + 0x488) + 0x30))(iVar14 + 0x480,0x80,0x40,0x10);
    (**(code **)(*(int *)(iVar14 + 0x488) + 0x2c))(iVar14 + 0x480,0x40);
  }
  if (iStack_48 != 0) {
    Create__10MenuSpriteFUc(iVar14 + 0x4e0,1);
    *(byte *)(iVar14 + 0x501) = *(byte *)(iVar14 + 0x501) & 0xbf | 0x40;
    uVar17 = (ulong)*(byte *)(iVar14 + 0x4f1) & 0xfffffffffffffffd | 2;
    *(char *)(iVar14 + 0x4f1) = (char)uVar17;
    *(byte *)(iVar14 + 0x4f0) =
         *(byte *)(iVar14 + 0x4f0) & 0xfd | (byte)((uint)((uVar17 << 0x3e) >> 0x3f) << 1);
    *(undefined2 *)(iVar14 + 0x4f4) = 4;
    (**(code **)(*(int *)(iVar14 + 0x4e8) + 0x24))(0x43998000,0x43c60000);
    SetUV__10MenuSpriteFUsUsUsUs(iVar14 + 0x4e0,0x25,0x1f,0x45,0x43);
    (**(code **)(*(int *)(iVar14 + 0x4e8) + 0x28))(0x42000000,0x42100000);
    *(byte *)(iVar14 + 0x4f2) = *(byte *)(iVar14 + 0x4f2) & 0xfe | 1;
    *(undefined2 *)(iVar14 + 0x4fc) = 0;
    *(undefined2 *)(iVar14 + 0x4fe) = 9;
    AddPlace__10MenuWindowFP9MenuPlace(iStack_40 + iStack_30 * 0x16c + 0x7c,iVar14 + 0x4e0);
  }
  if ((uStack_10 == 3) && (acStack_64[3] != '\0')) {
    (**(code **)(*(int *)(iVar14 + 0x4e8) + 0x30))(iVar14 + 0x4e0,0x40,0x80,0x60);
    (**(code **)(*(int *)(iVar14 + 0x4e8) + 0x2c))(iVar14 + 0x4e0,0x60);
  }
  else if (acStack_64[3] == '\0') {
    (**(code **)(*(int *)(iVar14 + 0x4e8) + 0x30))(iVar14 + 0x4e0,0x80,0x40,0x10);
    (**(code **)(*(int *)(iVar14 + 0x4e8) + 0x2c))(iVar14 + 0x4e0,0x20);
  }
  else {
    (**(code **)(*(int *)(iVar14 + 0x4e8) + 0x30))(iVar14 + 0x4e0,0x80,0x40,0x10);
    (**(code **)(*(int *)(iVar14 + 0x4e8) + 0x2c))(iVar14 + 0x4e0,0x40);
  }
  if (iStack_48 != 0) {
    iStack_b4 = *(int *)&pCGpffff86b4->field_0x4248;
    uStack_ec = *(undefined4 *)(iStack_b4 + (uint)*(ushort *)(iStack_b4 + 10) * 4 + 0xc);
    uStack_e8 = uStack_ec;
    uVar7 = GetTex0__6JRCTexFb(*(undefined4 *)&pCGpffff86b4->field_0x4248,0);
    Create__11SendOnLocalFP4_QWDUl(iStack_84 + iStack_4c * 0x30,uStack_ec,uVar7);
    *(undefined2 *)(iStack_84 + iStack_4c * 0x30 + 0x14) = 7;
    AddPriority__12MenuObjTableFP7MenuObj(iStack_40 + iStack_30 * 0x16c + 0x94,iStack_84 + iStack_4c * 0x30);
    Create__10MenuSpriteFUc(iVar14 + 0x540,1);
    *(byte *)(iVar14 + 0x561) = *(byte *)(iVar14 + 0x561) & 0xbf | 0x40;
    uVar17 = (ulong)*(byte *)(iVar14 + 0x551) & 0xfffffffffffffffd | 2;
    *(char *)(iVar14 + 0x551) = (char)uVar17;
    *(byte *)(iVar14 + 0x550) =
         *(byte *)(iVar14 + 0x550) & 0xfd | (byte)((uint)((uVar17 << 0x3e) >> 0x3f) << 1);
    *(undefined2 *)(iVar14 + 0x554) = 8;
    (**(code **)(*(int *)(iVar14 + 0x548) + 0x24))(0x43470000,0x43ba0000);
    (**(code **)(*(int *)(iVar14 + 0x548) + 0x28))(0x41900000,0x41b00000);
    (**(code **)(*(int *)(iVar14 + 0x548) + 0x2c))(iVar14 + 0x540,0x80);
    *(undefined2 *)(iVar14 + 0x55c) = 0;
    *(undefined2 *)(iVar14 + 0x55e) = 10;
    AddPlace__10MenuWindowFP9MenuPlace(iStack_40 + iStack_30 * 0x16c + 0x7c,iVar14 + 0x540);
    Create__10MenuSpriteFUc(iVar14 + 0x5a0,1);
    *(byte *)(iVar14 + 0x5c1) = *(byte *)(iVar14 + 0x5c1) & 0xbf | 0x40;
    uVar17 = (ulong)*(byte *)(iVar14 + 0x5b1) & 0xfffffffffffffffd | 2;
    *(char *)(iVar14 + 0x5b1) = (char)uVar17;
    *(byte *)(iVar14 + 0x5b0) =
         *(byte *)(iVar14 + 0x5b0) & 0xfd | (byte)((uint)((uVar17 << 0x3e) >> 0x3f) << 1);
    *(undefined2 *)(iVar14 + 0x5b4) = 8;
    (**(code **)(*(int *)(iVar14 + 0x5a8) + 0x24))(0x43938000,0x43ba0000);
    (**(code **)(*(int *)(iVar14 + 0x5a8) + 0x28))(0x41900000,0x41b00000);
    (**(code **)(*(int *)(iVar14 + 0x5a8) + 0x2c))(iVar14 + 0x5a0,0x80);
    *(undefined2 *)(iVar14 + 0x5bc) = 1;
    *(undefined2 *)(iVar14 + 0x5be) = 10;
    AddPlace__10MenuWindowFP9MenuPlace(iStack_40 + iStack_30 * 0x16c + 0x7c,iVar14 + 0x5a0);
    Create__10MenuSpriteFUc(iVar14 + 0x600,1);
    *(byte *)(iVar14 + 0x621) = *(byte *)(iVar14 + 0x621) & 0xbf | 0x40;
    uVar17 = (ulong)*(byte *)(iVar14 + 0x611) & 0xfffffffffffffffd | 2;
    *(char *)(iVar14 + 0x611) = (char)uVar17;
    *(byte *)(iVar14 + 0x610) =
         *(byte *)(iVar14 + 0x610) & 0xfd | (byte)((uint)((uVar17 << 0x3e) >> 0x3f) << 1);
    *(undefined2 *)(iVar14 + 0x614) = 8;
    (**(code **)(*(int *)(iVar14 + 0x608) + 0x24))(0x43340000,0x43ca0000);
    (**(code **)(*(int *)(iVar14 + 0x608) + 0x28))(0x41900000,0x41b00000);
    (**(code **)(*(int *)(iVar14 + 0x608) + 0x2c))(iVar14 + 0x600,0x80);
    *(undefined2 *)(iVar14 + 0x61c) = 2;
    *(undefined2 *)(iVar14 + 0x61e) = 10;
    AddPlace__10MenuWindowFP9MenuPlace(iStack_40 + iStack_30 * 0x16c + 0x7c,iVar14 + 0x600);
    Create__10MenuSpriteFUc(iVar14 + 0x660,1);
    *(byte *)(iVar14 + 0x681) = *(byte *)(iVar14 + 0x681) & 0xbf | 0x40;
    uVar17 = (ulong)*(byte *)(iVar14 + 0x671) & 0xfffffffffffffffd | 2;
    *(char *)(iVar14 + 0x671) = (char)uVar17;
    *(byte *)(iVar14 + 0x670) =
         *(byte *)(iVar14 + 0x670) & 0xfd | (byte)((uint)((uVar17 << 0x3e) >> 0x3f) << 1);
    *(undefined2 *)(iVar14 + 0x674) = 8;
    (**(code **)(*(int *)(iVar14 + 0x668) + 0x24))(0x439d0000,0x43ca0000);
    (**(code **)(*(int *)(iVar14 + 0x668) + 0x28))(0x41900000,0x41b00000);
    (**(code **)(*(int *)(iVar14 + 0x668) + 0x2c))(iVar14 + 0x660,0x80);
    *(undefined2 *)(iVar14 + 0x67c) = 3;
    *(undefined2 *)(iVar14 + 0x67e) = 10;
    AddPlace__10MenuWindowFP9MenuPlace(iStack_40 + iStack_30 * 0x16c + 0x7c,iVar14 + 0x660);
  }
  for (uVar16 = 0; (int)uVar16 < 4; uVar16 = uVar16 + 1) {
    bVar1 = abStack_68[uVar16];
    if (bVar1 == 4) {
      if (abStack_6c[uVar16] == 6) {
        SetUV__10MenuSpriteFUsUsUsUs(iVar14 + (uVar16 + 0xe) * 0x60,0x48,0x16,0x5a,0x2c);
      }
      else {
        SetUV__10MenuSpriteFUsUsUsUs(iVar14 + (uVar16 + 0xe) * 0x60,0x48,0,0x5a,0x16);
      }
    }
    else if (bVar1 == 3) {
      if (abStack_6c[uVar16] == 6) {
        SetUV__10MenuSpriteFUsUsUsUs(iVar14 + (uVar16 + 0xe) * 0x60,0x36,0x16,0x48,0x2c);
      }
      else {
        SetUV__10MenuSpriteFUsUsUsUs(iVar14 + (uVar16 + 0xe) * 0x60,0x36,0,0x48,0x16);
      }
    }
    else if (bVar1 == 2) {
      if (abStack_6c[uVar16] == 6) {
        SetUV__10MenuSpriteFUsUsUsUs(iVar14 + (uVar16 + 0xe) * 0x60,0x24,0x16,0x36,0x2c);
      }
      else {
        SetUV__10MenuSpriteFUsUsUsUs(iVar14 + (uVar16 + 0xe) * 0x60,0x24,0,0x36,0x16);
      }
    }
    else if (bVar1 == 1) {
      if (abStack_6c[uVar16] == 6) {
        SetUV__10MenuSpriteFUsUsUsUs(iVar14 + (uVar16 + 0xe) * 0x60,0x12,0x16,0x24,0x2c);
      }
      else {
        SetUV__10MenuSpriteFUsUsUsUs(iVar14 + (uVar16 + 0xe) * 0x60,0x12,0,0x24,0x16);
      }
    }
    else if (bVar1 == 0) {
      if (abStack_6c[uVar16] == 6) {
        SetUV__10MenuSpriteFUsUsUsUs(iVar14 + (uVar16 + 0xe) * 0x60,0,0x16,0x12,0x2c);
      }
      else {
        SetUV__10MenuSpriteFUsUsUsUs(iVar14 + (uVar16 + 0xe) * 0x60,0,0,0x12,0x16);
      }
    }
    if ((uStack_10 == uVar16) && (acStack_64[uVar16] != '\0')) {
      iVar8 = iVar14 + (uVar16 + 0xe) * 0x60;
      (**(code **)(*(int *)(iVar8 + 8) + 0x30))
                (iVar8,*(undefined1 *)((char)abStack_6c[uVar16] * 4 + 0x654ea0),
                 *(undefined1 *)((char)abStack_6c[uVar16] * 4 + 0x654ea1),
                 *(undefined1 *)((char)abStack_6c[uVar16] * 4 + 0x654ea2));
      iVar8 = iVar14 + (uVar16 + 0xe) * 0x60;
      *(byte *)(iVar8 + 0x12) = *(byte *)(iVar8 + 0x12) & 0xfe | 1;
    }
    else if (acStack_64[uVar16] == '\0') {
      iVar8 = iVar14 + (uVar16 + 0xe) * 0x60;
      *(byte *)(iVar8 + 0x12) = *(byte *)(iVar8 + 0x12) & 0xfe;
    }
    else {
      if (uStack_10 == 0xffffffff) {
        iVar8 = iVar14 + (uVar16 + 0xe) * 0x60;
        (**(code **)(*(int *)(iVar8 + 8) + 0x30))
                  (iVar8,*(undefined1 *)((char)abStack_6c[uVar16] * 4 + 0x654ea0),
                   *(undefined1 *)((char)abStack_6c[uVar16] * 4 + 0x654ea1),
                   *(undefined1 *)((char)abStack_6c[uVar16] * 4 + 0x654ea2));
      }
      else {
        iVar8 = iVar14 + (uVar16 + 0xe) * 0x60;
        (**(code **)(*(int *)(iVar8 + 8) + 0x30))
                  (iVar8,(int)(uint)*(byte *)((char)abStack_6c[uVar16] * 4 + 0x654ea0) >> 1,
                   (int)(uint)*(byte *)((char)abStack_6c[uVar16] * 4 + 0x654ea1) >> 1,
                   (int)(uint)*(byte *)((char)abStack_6c[uVar16] * 4 + 0x654ea2) >> 1);
      }
      iVar8 = iVar14 + (uVar16 + 0xe) * 0x60;
      *(byte *)(iVar8 + 0x12) = *(byte *)(iVar8 + 0x12) & 0xfe | 1;
    }
  }
  iStack_4c = iStack_4c + 1;
  iVar8 = 0x12;
  uVar18 = 0xb;
  piVar11 = (int *)0xc;
  piVar9 = aiStack_190;
  piVar4 = piVar9;
  while (piVar4 != (int *)0x0) {
    *(undefined1 *)piVar9 = 0;
    piVar9 = (int *)((int)piVar9 + 1);
    piVar11 = (int *)((int)piVar11 + -1);
    piVar4 = piVar11;
  }
  iStack_98 = 0;
  for (uVar16 = 0; (int)uVar16 < 0xc; uVar16 = uVar16 + 1) {
    if ((*(uint *)(iStack_40 + 0xb34) & 1 << (uVar16 & 0x1f)) != 0) {
      aiStack_190[iStack_98] = (int)pCGpffff86b4->aChr[uVar16].nCharId;
      iStack_98 = iStack_98 + 1;
    }
  }
  if (iStack_48 != 0) {
    iStack_b8 = *(int *)&pCGpffff86b4->field_0x4264;
    uStack_f4 = *(undefined4 *)(iStack_b8 + (uint)*(ushort *)(iStack_b8 + 10) * 4 + 0xc);
    uStack_f0 = uStack_f4;
    uVar7 = GetTex0__6JRCTexFb(*(undefined4 *)&pCGpffff86b4->field_0x4264,0);
    Create__11SendOnLocalFP4_QWDUl(iStack_84 + iStack_4c * 0x30,uStack_f4,uVar7);
    *(undefined2 *)(iStack_84 + iStack_4c * 0x30 + 0x14) = 9;
    AddPriority__12MenuObjTableFP7MenuObj(iStack_40 + iStack_30 * 0x16c + 0x94,iStack_84 + iStack_4c * 0x30);
    CreatePacket__10MenuPacketFUs(iStack_88 + iStack_50 * 0x28 + 0x18,4);
    SetRegister__12MenuRegisterFiUlUl(iStack_88 + iStack_50 * 0x28,0,0x42,0x44);
    *(undefined2 *)(iStack_88 + iStack_50 * 0x28 + 0x14) = 9;
    AddPriority__12MenuObjTableFP7MenuObj(iStack_40 + iStack_30 * 0x16c + 0x94,iStack_88 + iStack_50 * 0x28);
    if (aiStack_190[0] < 8) {
      iStack_bc = *(int *)&pCGpffff86b4->field_0x42c4;
      uStack_fc = *(undefined4 *)(iStack_bc + (uint)*(ushort *)(iStack_bc + 10) * 4 + 0xc);
      uStack_f8 = uStack_fc;
      uVar7 = GetTex0__6JRCTexFb(*(undefined4 *)&pCGpffff86b4->field_0x42c4,0);
      Create__11SendOnLocalFP4_QWDUl(iStack_84 + (iStack_4c + 1) * 0x30,uStack_fc,uVar7);
    }
    else if (aiStack_190[0] < 0xb) {
      iStack_c0 = *(int *)&pCGpffff86b4->field_0x42c8;
      uStack_104 = *(undefined4 *)(iStack_c0 + (uint)*(ushort *)(iStack_c0 + 10) * 4 + 0xc);
      uStack_100 = uStack_104;
      uVar7 = GetTex0__6JRCTexFb(*(undefined4 *)&pCGpffff86b4->field_0x42c8,0);
      Create__11SendOnLocalFP4_QWDUl(iStack_84 + (iStack_4c + 1) * 0x30,uStack_104,uVar7);
    }
    else {
      iStack_c4 = *(int *)&pCGpffff86b4->field_0x42cc;
      uStack_10c = *(undefined4 *)(iStack_c4 + (uint)*(ushort *)(iStack_c4 + 10) * 4 + 0xc);
      uStack_108 = uStack_10c;
      uVar7 = GetTex0__6JRCTexFb(*(undefined4 *)&pCGpffff86b4->field_0x42cc,0);
      Create__11SendOnLocalFP4_QWDUl(iStack_84 + (iStack_4c + 1) * 0x30,uStack_10c,uVar7);
    }
    *(undefined2 *)(iStack_84 + (iStack_4c + 1) * 0x30 + 0x14) = 0xb;
    AddPriority__12MenuObjTableFP7MenuObj(iStack_40 + iStack_30 * 0x16c + 0x94,iStack_84 + (iStack_4c + 1) * 0x30);
    if (aiStack_190[1] < 8) {
      iStack_c8 = *(int *)&pCGpffff86b4->field_0x42c4;
      uStack_114 = *(undefined4 *)(iStack_c8 + (uint)*(ushort *)(iStack_c8 + 10) * 4 + 0xc);
      uStack_110 = uStack_114;
      uVar7 = GetTex0__6JRCTexFb(*(undefined4 *)&pCGpffff86b4->field_0x42c4,0);
      Create__11SendOnLocalFP4_QWDUl(iStack_84 + (iStack_4c + 2) * 0x30,uStack_114,uVar7);
    }
    else if (aiStack_190[1] < 0xb) {
      iStack_cc = *(int *)&pCGpffff86b4->field_0x42c8;
      uStack_11c = *(undefined4 *)(iStack_cc + (uint)*(ushort *)(iStack_cc + 10) * 4 + 0xc);
      uStack_118 = uStack_11c;
      uVar7 = GetTex0__6JRCTexFb(*(undefined4 *)&pCGpffff86b4->field_0x42c8,0);
      Create__11SendOnLocalFP4_QWDUl(iStack_84 + (iStack_4c + 2) * 0x30,uStack_11c,uVar7);
    }
    else {
      iStack_d0 = *(int *)&pCGpffff86b4->field_0x42cc;
      uStack_124 = *(undefined4 *)(iStack_d0 + (uint)*(ushort *)(iStack_d0 + 10) * 4 + 0xc);
      uStack_120 = uStack_124;
      uVar7 = GetTex0__6JRCTexFb(*(undefined4 *)&pCGpffff86b4->field_0x42cc,0);
      Create__11SendOnLocalFP4_QWDUl(iStack_84 + (iStack_4c + 2) * 0x30,uStack_124,uVar7);
    }
    *(undefined2 *)(iStack_84 + (iStack_4c + 2) * 0x30 + 0x14) = 0xd;
    AddPriority__12MenuObjTableFP7MenuObj(iStack_40 + iStack_30 * 0x16c + 0x94,iStack_84 + (iStack_4c + 2) * 0x30);
    if (aiStack_190[2] < 8) {
      iStack_d4 = *(int *)&pCGpffff86b4->field_0x42c4;
      uStack_12c = *(undefined4 *)(iStack_d4 + (uint)*(ushort *)(iStack_d4 + 10) * 4 + 0xc);
      uStack_128 = uStack_12c;
      uVar7 = GetTex0__6JRCTexFb(*(undefined4 *)&pCGpffff86b4->field_0x42c4,0);
      Create__11SendOnLocalFP4_QWDUl(iStack_84 + (iStack_4c + 3) * 0x30,uStack_12c,uVar7);
    }
    else if (aiStack_190[2] < 0xb) {
      iStack_d8 = *(int *)&pCGpffff86b4->field_0x42c8;
      uStack_134 = *(undefined4 *)(iStack_d8 + (uint)*(ushort *)(iStack_d8 + 10) * 4 + 0xc);
      uStack_130 = uStack_134;
      uVar7 = GetTex0__6JRCTexFb(*(undefined4 *)&pCGpffff86b4->field_0x42c8,0);
      Create__11SendOnLocalFP4_QWDUl(iStack_84 + (iStack_4c + 3) * 0x30,uStack_134,uVar7);
    }
    else {
      iStack_dc = *(int *)&pCGpffff86b4->field_0x42cc;
      uStack_13c = *(undefined4 *)(iStack_dc + (uint)*(ushort *)(iStack_dc + 10) * 4 + 0xc);
      uStack_138 = uStack_13c;
      uVar7 = GetTex0__6JRCTexFb(*(undefined4 *)&pCGpffff86b4->field_0x42cc,0);
      Create__11SendOnLocalFP4_QWDUl(iStack_84 + (iStack_4c + 3) * 0x30,uStack_13c,uVar7);
    }
    *(undefined2 *)(iStack_84 + (iStack_4c + 3) * 0x30 + 0x14) = 0xf;
    AddPriority__12MenuObjTableFP7MenuObj(iStack_40 + iStack_30 * 0x16c + 0x94,iStack_84 + (iStack_4c + 3) * 0x30);
    *(undefined2 *)(iStack_40 + iStack_30 * 0x16c + 0x50) = 0x11;
    AddPriority__12MenuObjTableFP7MenuObj(iStack_40 + iStack_30 * 0x16c + 0x94,iStack_40 + iStack_30 * 0x16c + 0x3c);
  }
  iStack_50 = iStack_50 + 1;
  iStack_54 = 0;
  iStack_58 = 0;
  iStack_98 = 0;
  for (uVar16 = 0; (int)uVar16 < 0xc; uVar16 = uVar16 + 1) {
    if ((*(uint *)(iStack_40 + 0xb34) & 1 << (uVar16 & 0x1f)) != 0) {
      aiStack_160[iStack_58] = iVar8;
      aiStack_170[iStack_58] = iVar13;
      if (iStack_48 != 0) {
        Create__10MenuSpriteFUc(iVar14 + iVar8 * 0x60,1);
        iVar12 = iVar14 + iVar8 * 0x60;
        *(byte *)(iVar12 + 0x21) = *(byte *)(iVar12 + 0x21) & 0xbf | 0x40;
        iVar12 = iVar14 + iVar8 * 0x60;
        uVar17 = (ulong)*(byte *)(iVar12 + 0x11) & 0xfffffffffffffffd | 2;
        *(char *)(iVar12 + 0x11) = (char)uVar17;
        iVar12 = iVar14 + iVar8 * 0x60;
        *(byte *)(iVar12 + 0x10) =
             *(byte *)(iVar12 + 0x10) & 0xfd | (byte)((uint)((uVar17 << 0x3e) >> 0x3f) << 1);
        *(undefined2 *)(iVar14 + iVar8 * 0x60 + 0x14) = 6;
        uVar7 = SetUV__10MenuSpriteFUsUsUsUs(iVar14 + iVar8 * 0x60,0x25,0,0x34,0x1f);
        iVar12 = iVar14 + iVar8 * 0x60;
        (**(code **)(*(int *)(iVar12 + 8) + 0x28))(0x41700000,0x41f80000,iVar12,iVar8 * 0x60,uVar7);
        *(short *)(iVar14 + iVar8 * 0x60 + 0x1c) = (short)iStack_54;
        *(undefined2 *)(iVar14 + iVar8 * 0x60 + 0x1e) = 0xb;
        AddPlace__10MenuWindowFP9MenuPlace(iStack_40 + iStack_30 * 0x16c + 0x7c,iVar14 + iVar8 * 0x60);
        Create__10MenuSpriteFUc(iVar14 + (iVar8 + 1) * 0x60,1);
        iVar12 = iVar14 + (iVar8 + 1) * 0x60;
        *(byte *)(iVar12 + 0x21) = *(byte *)(iVar12 + 0x21) & 0xbf | 0x40;
        iVar12 = iVar14 + (iVar8 + 1) * 0x60;
        uVar17 = (ulong)*(byte *)(iVar12 + 0x11) & 0xfffffffffffffffd | 2;
        *(char *)(iVar12 + 0x11) = (char)uVar17;
        iVar12 = iVar14 + (iVar8 + 1) * 0x60;
        *(byte *)(iVar12 + 0x10) =
             *(byte *)(iVar12 + 0x10) & 0xfd | (byte)((uint)((uVar17 << 0x3e) >> 0x3f) << 1);
        *(undefined2 *)(iVar14 + (iVar8 + 1) * 0x60 + 0x14) = 6;
        SetUV__10MenuSpriteFUsUsUsUs(iVar14 + (iVar8 + 1) * 0x60,0x34,0,0x45,0x1f);
        *(short *)(iVar14 + (iVar8 + 1) * 0x60 + 0x1c) = (short)iStack_54 + 1;
        *(undefined2 *)(iVar14 + (iVar8 + 1) * 0x60 + 0x1e) = 0xb;
        AddPlace__10MenuWindowFP9MenuPlace(iStack_40 + iStack_30 * 0x16c + 0x7c,iVar14 + (iVar8 + 1) * 0x60);
        Create__10MenuSpriteFUc(iVar14 + (iVar8 + 2) * 0x60,1);
        iVar12 = iVar14 + (iVar8 + 2) * 0x60;
        *(byte *)(iVar12 + 0x21) = *(byte *)(iVar12 + 0x21) & 0xbf | 0x40;
        iVar12 = iVar14 + (iVar8 + 2) * 0x60;
        uVar17 = (ulong)*(byte *)(iVar12 + 0x11) & 0xfffffffffffffffd | 2;
        *(char *)(iVar12 + 0x11) = (char)uVar17;
        iVar12 = iVar14 + (iVar8 + 2) * 0x60;
        *(byte *)(iVar12 + 0x10) =
             *(byte *)(iVar12 + 0x10) & 0xfd | (byte)((uint)((uVar17 << 0x3e) >> 0x3f) << 1);
        *(undefined2 *)(iVar14 + (iVar8 + 2) * 0x60 + 0x14) = 6;
        SetUV__10MenuSpriteFUsUsUsUs(iVar14 + (iVar8 + 2) * 0x60,0x34,0x1f,0x25,0);
        (**(code **)(*(int *)(iVar14 + (iVar8 + 2) * 0x60 + 8) + 0x28))(0x41700000,0x41f80000);
        *(short *)(iVar14 + (iVar8 + 2) * 0x60 + 0x1c) = (short)iStack_54 + 2;
        *(undefined2 *)(iVar14 + (iVar8 + 2) * 0x60 + 0x1e) = 0xb;
        AddPlace__10MenuWindowFP9MenuPlace(iStack_40 + iStack_30 * 0x16c + 0x7c,iVar14 + (iVar8 + 2) * 0x60);
        Create__10MenuSpriteFUc(iVar14 + (iVar8 + 3) * 0x60,1);
        iVar12 = iVar14 + (iVar8 + 3) * 0x60;
        *(byte *)(iVar12 + 0x21) = *(byte *)(iVar12 + 0x21) & 0xbf | 0x40;
        iVar12 = iVar14 + (iVar8 + 3) * 0x60;
        uVar17 = (ulong)*(byte *)(iVar12 + 0x11) & 0xfffffffffffffffd | 2;
        *(char *)(iVar12 + 0x11) = (char)uVar17;
        iVar12 = iVar14 + (iVar8 + 3) * 0x60;
        *(byte *)(iVar12 + 0x10) =
             *(byte *)(iVar12 + 0x10) & 0xfd | (byte)((uint)((uVar17 << 0x3e) >> 0x3f) << 1);
        *(undefined2 *)(iVar14 + (iVar8 + 3) * 0x60 + 0x14) = 10;
        SetUV__10MenuSpriteFUsUsUsUs(iVar14 + (iVar8 + 3) * 0x60,0x46,0,0x6c,0x19);
        (**(code **)(*(int *)(iVar14 + (iVar8 + 3) * 0x60 + 8) + 0x28))(0x42180000,0x41c80000);
        *(short *)(iVar14 + (iVar8 + 3) * 0x60 + 0x1c) = (short)iStack_54 + 3;
        *(undefined2 *)(iVar14 + (iVar8 + 3) * 0x60 + 0x1e) = 0xb;
        AddPlace__10MenuWindowFP9MenuPlace(iStack_40 + iStack_30 * 0x16c + 0x7c,iVar14 + (iVar8 + 3) * 0x60);
        Create__10MenuSpriteFUc(iVar14 + (iVar8 + 4) * 0x60,1);
        iVar12 = iVar14 + (iVar8 + 4) * 0x60;
        *(byte *)(iVar12 + 0x21) = *(byte *)(iVar12 + 0x21) & 0xbf | 0x40;
        iVar12 = iVar14 + (iVar8 + 4) * 0x60;
        uVar17 = (ulong)*(byte *)(iVar12 + 0x11) & 0xfffffffffffffffd | 2;
        *(char *)(iVar12 + 0x11) = (char)uVar17;
        iVar12 = iVar14 + (iVar8 + 4) * 0x60;
        *(byte *)(iVar12 + 0x10) =
             *(byte *)(iVar12 + 0x10) & 0xfd | (byte)((uint)((uVar17 << 0x3e) >> 0x3f) << 1);
        if (iStack_98 == 0) {
          *(undefined2 *)(iVar14 + (iVar8 + 4) * 0x60 + 0x14) = 0xc;
        }
        else if (iStack_98 == 1) {
          *(undefined2 *)(iVar14 + (iVar8 + 4) * 0x60 + 0x14) = 0xe;
        }
        else {
          *(undefined2 *)(iVar14 + (iVar8 + 4) * 0x60 + 0x14) = 0x10;
        }
        (**(code **)(*(int *)(iVar14 + (iVar8 + 4) * 0x60 + 8) + 0x28))(0x42100000,0x41b00000);
        *(short *)(iVar14 + (iVar8 + 4) * 0x60 + 0x1c) = (short)iStack_54 + 4;
        *(undefined2 *)(iVar14 + (iVar8 + 4) * 0x60 + 0x1e) = 0xb;
        AddPlace__10MenuWindowFP9MenuPlace(iStack_40 + iStack_30 * 0x16c + 0x7c,iVar14 + (iVar8 + 4) * 0x60);
        Create__8MenuTextFUcUc(iVar10 + iVar13 * 0x80,1,2);
        *(undefined1 *)(iVar10 + iVar13 * 0x80 + 0x5a) = 1;
        *(undefined1 *)(iVar10 + iVar13 * 0x80 + 0x5b) = 0;
        *(undefined2 *)(iVar10 + iVar13 * 0x80 + 0x14) = 0x12;
        *(short *)(iVar10 + iVar13 * 0x80 + 0x1c) = (short)iStack_54 + 5;
        *(undefined2 *)(iVar10 + iVar13 * 0x80 + 0x1e) = 0xb;
        AddPlace__10MenuWindowFP9MenuPlace(iStack_40 + iStack_30 * 0x16c + 0x7c,iVar10 + iVar13 * 0x80);
      }
      strcpy(auStack_210,pCGpffff86b4->aChr[uVar16].pNamePtr);
      sVar3 = pCGpffff86b4->aChr[uVar16].nNameSuffix;
      lVar15 = (long)sVar3;
      pCVar6 = pCGpffff86b4;
      if (sVar3 != -1) {
        pCVar6 = (CBattle *)
                 strcat(auStack_210,
                                 *(undefined4 *)
                                  (iRam0040ab24 + pCGpffff86b4->aChr[uVar16].nNameSuffix * 4));
        lVar15 = extraout_t2;
      }
      SetMessage__8MenuTextFPcUiUcUc(iVar10 + iVar13 * 0x80,auStack_210,0,0,1,1,lVar15,pCVar6);
      OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_40 + iStack_30 * 0x16c + 0x3c,iVar10 + iVar13 * 0x80,1,0);
      fStack_140 = *(float *)(iVar10 + iVar13 * 0x80 + 0x2c);
      fStack_74 = fStack_140;
      aiStack_180[iStack_58] = (int)(fStack_140 + 0.5) + 0x37;
      iVar12 = iVar14 + iVar8 * 0x60;
      *(byte *)(iVar12 + 0x12) = *(byte *)(iVar12 + 0x12) & 0xfe | 1;
      (**(code **)(*(int *)(iVar14 + (iVar8 + 1) * 0x60 + 8) + 0x28))
                ((float)(aiStack_180[iStack_58] + -0x1e),0x41f80000);
      iVar12 = iVar14 + (iVar8 + 1) * 0x60;
      *(byte *)(iVar12 + 0x12) = *(byte *)(iVar12 + 0x12) & 0xfe | 1;
      iVar12 = iVar14 + (iVar8 + 2) * 0x60;
      *(byte *)(iVar12 + 0x12) = *(byte *)(iVar12 + 0x12) & 0xfe | 1;
      if (uStack_20 == uVar16) {
        iVar12 = iVar14 + iVar8 * 0x60;
        (**(code **)(*(int *)(iVar12 + 8) + 0x30))(iVar12,0x20,0x80,0x60);
        iVar12 = iVar14 + iVar8 * 0x60;
        uVar7 = (**(code **)(*(int *)(iVar12 + 8) + 0x2c))(iVar12,0x60);
        iVar12 = iVar14 + (iVar8 + 1) * 0x60;
        (**(code **)(*(int *)(iVar12 + 8) + 0x30))(iVar12,0x20,0x80,0x60,0x60,iVar12,uVar7);
        iVar12 = iVar14 + (iVar8 + 1) * 0x60;
        (**(code **)(*(int *)(iVar12 + 8) + 0x2c))(iVar12,0x60);
        iVar12 = iVar14 + (iVar8 + 2) * 0x60;
        (**(code **)(*(int *)(iVar12 + 8) + 0x30))(iVar12,0x20,0x80,0x60);
        iVar12 = iVar14 + (iVar8 + 2) * 0x60;
        (**(code **)(*(int *)(iVar12 + 8) + 0x2c))(iVar12,0x60);
        SetCSA__8FontItemFUc(iVar10 + iVar13 * 0x80,1);
        *(undefined1 *)(iVar10 + iVar13 * 0x80 + 0x5c) = 0;
        iVar12 = iVar10 + iVar13 * 0x80;
        *(byte *)(iVar12 + 0x11) = *(byte *)(iVar12 + 0x11) & 0xfd | 2;
        iVar12 = iVar10 + iVar13 * 0x80;
        *(byte *)(iVar12 + 0x10) = *(byte *)(iVar12 + 0x10) & 0xfd | 2;
        iVar12 = iVar10 + iVar13 * 0x80;
        (**(code **)(*(int *)(iVar12 + 8) + 0x2c))(iVar12,0x80);
      }
      else {
        iVar12 = iVar14 + iVar8 * 0x60;
        (**(code **)(*(int *)(iVar12 + 8) + 0x30))(iVar12,0x80,0x40,0x10);
        iVar12 = iVar14 + iVar8 * 0x60;
        (**(code **)(*(int *)(iVar12 + 8) + 0x2c))(iVar12,0x40);
        iVar12 = iVar14 + (iVar8 + 1) * 0x60;
        uVar7 = (**(code **)(*(int *)(iVar12 + 8) + 0x30))(iVar12,0x80,0x40,0x10);
        iVar12 = iVar14 + (iVar8 + 1) * 0x60;
        (**(code **)(*(int *)(iVar12 + 8) + 0x2c))(iVar12,0x40,(iVar8 + 1) * 3,uVar7);
        iVar12 = iVar14 + (iVar8 + 2) * 0x60;
        (**(code **)(*(int *)(iVar12 + 8) + 0x30))(iVar12,0x80,0x40,0x10);
        iVar12 = iVar14 + (iVar8 + 2) * 0x60;
        (**(code **)(*(int *)(iVar12 + 8) + 0x2c))(iVar12,0x40);
        SetCSA__8FontItemFUc(iVar10 + iVar13 * 0x80,0);
        *(undefined1 *)(iVar10 + iVar13 * 0x80 + 0x5c) = 0;
        iVar12 = iVar10 + iVar13 * 0x80;
        *(byte *)(iVar12 + 0x11) = *(byte *)(iVar12 + 0x11) & 0xfd | 2;
        iVar12 = iVar10 + iVar13 * 0x80;
        *(byte *)(iVar12 + 0x10) = *(byte *)(iVar12 + 0x10) & 0xfd | 2;
        if (uStack_10 == 0xffffffff) {
          iVar12 = iVar10 + iVar13 * 0x80;
          (**(code **)(*(int *)(iVar12 + 8) + 0x2c))(iVar12,0x80);
        }
        else {
          iVar12 = iVar10 + iVar13 * 0x80;
          (**(code **)(*(int *)(iVar12 + 8) + 0x2c))(iVar12,0x40);
        }
      }
      iVar12 = iVar14 + (iVar8 + 3) * 0x60;
      *(byte *)(iVar12 + 0x12) = *(byte *)(iVar12 + 0x12) & 0xfe | 1;
      if (pCGpffff86b4->aChr[uVar16].nCharId < 8) {
        uStack_9c = (uint)*(short *)&pCGpffff86b4->aChr[uVar16].field_0xdc;
        if (uStack_9c == 0x51) {
          uStack_9c = 5;
        }
        if (uStack_9c == 0x54) {
          uStack_9c = 3;
        }
        if (uStack_9c == 0x57) {
          uStack_9c = 4;
        }
        if ((pCGpffff86b4->aChr[uVar16].bFlagsA1 & 1) != 0) {
          uStack_9c = (uint)*(ushort *)
                             (ourBtlSaveDat + pCGpffff86b4->aChr[uVar16].nCharId * 0xc0 + 0x48);
        }
        if ((int)uStack_9c < 6) {
          SetUV__10MenuSpriteFUsUsUsUs(iVar14 + (iVar8 + 4) * 0x60,0,uStack_9c * 0x18 + 1 & 0xffff,0x24,
                          uStack_9c * 0x18 + 0x17 & 0xffff);
        }
        else {
          SetUV__10MenuSpriteFUsUsUsUs(iVar14 + (iVar8 + 4) * 0x60,0x24,(uStack_9c - 6) * 0x18 + 1 & 0xffff,0x48,
                          (uStack_9c - 6) * 0x18 + 0x17 & 0xffff);
        }
      }
      else if (pCGpffff86b4->aChr[uVar16].nCharId < 0xb) {
        SetUV__10MenuSpriteFUsUsUsUs(iVar14 + (iVar8 + 4) * 0x60,0,
                        (pCGpffff86b4->aChr[uVar16].nCharId + -8) * 0x18 + 1,0x24,
                        (pCGpffff86b4->aChr[uVar16].nCharId + -8) * 0x18 + 0x17);
      }
      else {
        SetUV__10MenuSpriteFUsUsUsUs(iVar14 + (iVar8 + 4) * 0x60,0,1,0x24,0x17);
      }
      iVar12 = iVar14 + (iVar8 + 4) * 0x60;
      *(byte *)(iVar12 + 0x12) = *(byte *)(iVar12 + 0x12) & 0xfe | 1;
      iVar12 = iVar10 + iVar13 * 0x80;
      *(byte *)(iVar12 + 0x12) = *(byte *)(iVar12 + 0x12) & 0xfe | 1;
      iVar13 = iVar13 + 1;
      iVar8 = iVar8 + 5;
      iStack_54 = iStack_54 + 6;
      iStack_58 = iStack_58 + 1;
      iStack_98 = iStack_98 + 1;
    }
  }
  if (iStack_58 == 3) {
    if (aiStack_180[1] < 0) {
      aiStack_180[1] = aiStack_180[1] + 1;
    }
    fStack_80 = (float)(0x100 - ((aiStack_180[1] >> 1) + 4 + aiStack_180[0]));
  }
  else if (iStack_58 == 2) {
    fStack_80 = (float)(0x100 - (aiStack_180[0] + 2));
  }
  else {
    if (aiStack_180[0] < 0) {
      aiStack_180[0] = aiStack_180[0] + 1;
    }
    fStack_80 = (float)(0x100 - (aiStack_180[0] >> 1));
  }
  for (iVar12 = 0; iVar12 < iStack_58; iVar12 = iVar12 + 1) {
    (**(code **)(*(int *)(iVar14 + aiStack_160[iVar12] * 0x60 + 8) + 0x24))(fStack_80,0x43a68000);
    (**(code **)(*(int *)(iVar14 + (aiStack_160[iVar12] + 1) * 0x60 + 8) + 0x24))
              (fStack_80 + 15.0,0x43a68000);
    (**(code **)(*(int *)(iVar14 + (aiStack_160[iVar12] + 2) * 0x60 + 8) + 0x24))
              ((fStack_80 + (float)aiStack_180[iVar12]) - 15.0,0x43a60000);
    (**(code **)(*(int *)(iVar14 + (aiStack_160[iVar12] + 3) * 0x60 + 8) + 0x24))
              (fStack_80 + 4.0,0x43a88000);
    (**(code **)(*(int *)(iVar14 + (aiStack_160[iVar12] + 4) * 0x60 + 8) + 0x24))
              (fStack_80 + 5.0,0x43a90000);
    (**(code **)(*(int *)(iVar10 + aiStack_170[iVar12] * 0x80 + 8) + 0x24))
              (fStack_80 + 43.0,0x43a98000);
    fStack_80 = fStack_80 + (float)(aiStack_180[iVar12] + 4);
  }
  for (; iStack_58 < 3; iStack_58 = iStack_58 + 1) {
    if (iStack_48 != 0) {
      Create__10MenuSpriteFUc(iVar14 + iVar8 * 0x60,1);
      iVar12 = iVar14 + iVar8 * 0x60;
      *(byte *)(iVar12 + 0x21) = *(byte *)(iVar12 + 0x21) & 0xbf | 0x40;
      iVar12 = iVar14 + iVar8 * 0x60;
      uVar17 = (ulong)*(byte *)(iVar12 + 0x11) & 0xfffffffffffffffd | 2;
      *(char *)(iVar12 + 0x11) = (char)uVar17;
      iVar12 = iVar14 + iVar8 * 0x60;
      *(byte *)(iVar12 + 0x10) =
           *(byte *)(iVar12 + 0x10) & 0xfd | (byte)((uint)((uVar17 << 0x3e) >> 0x3f) << 1);
      *(undefined2 *)(iVar14 + iVar8 * 0x60 + 0x14) = 6;
      SetUV__10MenuSpriteFUsUsUsUs(iVar14 + iVar8 * 0x60,0x25,0,0x34,0x1f);
      (**(code **)(*(int *)(iVar14 + iVar8 * 0x60 + 8) + 0x28))(0x41700000,0x41f80000);
      *(short *)(iVar14 + iVar8 * 0x60 + 0x1c) = (short)iStack_54;
      *(undefined2 *)(iVar14 + iVar8 * 0x60 + 0x1e) = 0xb;
      uVar7 = AddPlace__10MenuWindowFP9MenuPlace(iStack_40 + iStack_30 * 0x16c + 0x7c,iVar14 + iVar8 * 0x60);
      iVar12 = iVar14 + (iVar8 + 1) * 0x60;
      Create__10MenuSpriteFUc(iVar12,1,iVar12,1,uVar7);
      iVar12 = iVar14 + (iVar8 + 1) * 0x60;
      *(byte *)(iVar12 + 0x21) = *(byte *)(iVar12 + 0x21) & 0xbf | 0x40;
      iVar12 = iVar14 + (iVar8 + 1) * 0x60;
      uVar17 = (ulong)*(byte *)(iVar12 + 0x11) & 0xfffffffffffffffd | 2;
      *(char *)(iVar12 + 0x11) = (char)uVar17;
      iVar12 = iVar14 + (iVar8 + 1) * 0x60;
      *(byte *)(iVar12 + 0x10) =
           *(byte *)(iVar12 + 0x10) & 0xfd | (byte)((uint)((uVar17 << 0x3e) >> 0x3f) << 1);
      *(undefined2 *)(iVar14 + (iVar8 + 1) * 0x60 + 0x14) = 6;
      SetUV__10MenuSpriteFUsUsUsUs(iVar14 + (iVar8 + 1) * 0x60,0x34,0,0x45,0x1f);
      *(short *)(iVar14 + (iVar8 + 1) * 0x60 + 0x1c) = (short)iStack_54 + 1;
      *(undefined2 *)(iVar14 + (iVar8 + 1) * 0x60 + 0x1e) = 0xb;
      AddPlace__10MenuWindowFP9MenuPlace(iStack_40 + iStack_30 * 0x16c + 0x7c,iVar14 + (iVar8 + 1) * 0x60);
      Create__10MenuSpriteFUc(iVar14 + (iVar8 + 2) * 0x60,1);
      iVar12 = iVar14 + (iVar8 + 2) * 0x60;
      *(byte *)(iVar12 + 0x21) = *(byte *)(iVar12 + 0x21) & 0xbf | 0x40;
      iVar12 = iVar14 + (iVar8 + 2) * 0x60;
      uVar17 = (ulong)*(byte *)(iVar12 + 0x11) & 0xfffffffffffffffd | 2;
      *(char *)(iVar12 + 0x11) = (char)uVar17;
      iVar12 = iVar14 + (iVar8 + 2) * 0x60;
      *(byte *)(iVar12 + 0x10) =
           *(byte *)(iVar12 + 0x10) & 0xfd | (byte)((uint)((uVar17 << 0x3e) >> 0x3f) << 1);
      *(undefined2 *)(iVar14 + (iVar8 + 2) * 0x60 + 0x14) = 6;
      SetUV__10MenuSpriteFUsUsUsUs(iVar14 + (iVar8 + 2) * 0x60,0x34,0x1f,0x25,0);
      (**(code **)(*(int *)(iVar14 + (iVar8 + 2) * 0x60 + 8) + 0x28))(0x41700000,0x41f80000);
      *(short *)(iVar14 + (iVar8 + 2) * 0x60 + 0x1c) = (short)iStack_54 + 2;
      *(undefined2 *)(iVar14 + (iVar8 + 2) * 0x60 + 0x1e) = 0xb;
      AddPlace__10MenuWindowFP9MenuPlace(iStack_40 + iStack_30 * 0x16c + 0x7c,iVar14 + (iVar8 + 2) * 0x60);
      Create__10MenuSpriteFUc(iVar14 + (iVar8 + 3) * 0x60,1);
      iVar12 = iVar14 + (iVar8 + 3) * 0x60;
      *(byte *)(iVar12 + 0x21) = *(byte *)(iVar12 + 0x21) & 0xbf | 0x40;
      iVar12 = iVar14 + (iVar8 + 3) * 0x60;
      uVar17 = (ulong)*(byte *)(iVar12 + 0x11) & 0xfffffffffffffffd | 2;
      *(char *)(iVar12 + 0x11) = (char)uVar17;
      iVar12 = iVar14 + (iVar8 + 3) * 0x60;
      *(byte *)(iVar12 + 0x10) =
           *(byte *)(iVar12 + 0x10) & 0xfd | (byte)((uint)((uVar17 << 0x3e) >> 0x3f) << 1);
      *(undefined2 *)(iVar14 + (iVar8 + 3) * 0x60 + 0x14) = 10;
      SetUV__10MenuSpriteFUsUsUsUs(iVar14 + (iVar8 + 3) * 0x60,0x46,0,0x6c,0x19);
      (**(code **)(*(int *)(iVar14 + (iVar8 + 3) * 0x60 + 8) + 0x28))(0x42180000,0x41c80000);
      *(short *)(iVar14 + (iVar8 + 3) * 0x60 + 0x1c) = (short)iStack_54 + 3;
      *(undefined2 *)(iVar14 + (iVar8 + 3) * 0x60 + 0x1e) = 0xb;
      AddPlace__10MenuWindowFP9MenuPlace(iStack_40 + iStack_30 * 0x16c + 0x7c,iVar14 + (iVar8 + 3) * 0x60);
      Create__10MenuSpriteFUc(iVar14 + (iVar8 + 4) * 0x60,1);
      iVar12 = iVar14 + (iVar8 + 4) * 0x60;
      *(byte *)(iVar12 + 0x21) = *(byte *)(iVar12 + 0x21) & 0xbf | 0x40;
      iVar12 = iVar14 + (iVar8 + 4) * 0x60;
      uVar17 = (ulong)*(byte *)(iVar12 + 0x11) & 0xfffffffffffffffd | 2;
      *(char *)(iVar12 + 0x11) = (char)uVar17;
      iVar12 = iVar14 + (iVar8 + 4) * 0x60;
      *(byte *)(iVar12 + 0x10) =
           *(byte *)(iVar12 + 0x10) & 0xfd | (byte)((uint)((uVar17 << 0x3e) >> 0x3f) << 1);
      *(undefined2 *)(iVar14 + (iVar8 + 4) * 0x60 + 0x14) = 0xc;
      (**(code **)(*(int *)(iVar14 + (iVar8 + 4) * 0x60 + 8) + 0x28))(0x42100000,0x41b00000);
      *(short *)(iVar14 + (iVar8 + 4) * 0x60 + 0x1c) = (short)iStack_54 + 4;
      *(undefined2 *)(iVar14 + (iVar8 + 4) * 0x60 + 0x1e) = 0xb;
      AddPlace__10MenuWindowFP9MenuPlace(iStack_40 + iStack_30 * 0x16c + 0x7c,iVar14 + (iVar8 + 4) * 0x60);
      Create__8MenuTextFUcUc(iVar10 + iVar13 * 0x80,1,2);
      *(undefined1 *)(iVar10 + iVar13 * 0x80 + 0x5a) = 1;
      *(undefined1 *)(iVar10 + iVar13 * 0x80 + 0x5b) = 0;
      *(undefined2 *)(iVar10 + iVar13 * 0x80 + 0x14) = 0x12;
      *(short *)(iVar10 + iVar13 * 0x80 + 0x1c) = (short)iStack_54 + 5;
      *(undefined2 *)(iVar10 + iVar13 * 0x80 + 0x1e) = 0xb;
      AddPlace__10MenuWindowFP9MenuPlace(iStack_40 + iStack_30 * 0x16c + 0x7c,iVar10 + iVar13 * 0x80);
    }
    iVar12 = iVar14 + iVar8 * 0x60;
    *(byte *)(iVar12 + 0x12) = *(byte *)(iVar12 + 0x12) & 0xfe;
    iVar12 = iVar14 + (iVar8 + 1) * 0x60;
    *(byte *)(iVar12 + 0x12) = *(byte *)(iVar12 + 0x12) & 0xfe;
    iVar12 = iVar14 + (iVar8 + 2) * 0x60;
    *(byte *)(iVar12 + 0x12) = *(byte *)(iVar12 + 0x12) & 0xfe;
    iVar12 = iVar14 + (iVar8 + 3) * 0x60;
    *(byte *)(iVar12 + 0x12) = *(byte *)(iVar12 + 0x12) & 0xfe;
    iVar12 = iVar14 + (iVar8 + 4) * 0x60;
    *(byte *)(iVar12 + 0x12) = *(byte *)(iVar12 + 0x12) & 0xfe;
    iVar12 = iVar10 + iVar13 * 0x80;
    *(byte *)(iVar12 + 0x12) = *(byte *)(iVar12 + 0x12) & 0xfe;
    iVar13 = iVar13 + 1;
    iVar8 = iVar8 + 5;
    iStack_54 = iStack_54 + 6;
  }
  iStack_4c = iStack_4c + 4;
  for (uVar16 = 0; (int)uVar16 < 4; uVar16 = uVar16 + 1) {
    if (uVar16 == 3) {
      iStack_54 = 1;
      uVar18 = 0x15;
      fStack_78 = 339.0;
      uStack_7c = 0x43ca0000;
    }
    else if (uVar16 == 2) {
      iStack_54 = 0;
      uVar18 = 0x15;
      fStack_78 = 173.0;
      uStack_7c = 0x43ca0000;
    }
    else if (uVar16 == 1) {
      iStack_54 = 1;
      uVar18 = 0x14;
      fStack_78 = 320.0;
      uStack_7c = 0x43ba0000;
    }
    else if (uVar16 == 0) {
      iStack_54 = 0;
      uVar18 = 0x14;
      fStack_78 = 192.0;
      uStack_7c = 0x43ba0000;
    }
    if (iStack_48 != 0) {
      Create__8MenuTextFUcUc(iVar10 + iVar13 * 0x80,1,2);
      *(undefined1 *)(iVar10 + iVar13 * 0x80 + 0x5a) = 1;
      *(undefined1 *)(iVar10 + iVar13 * 0x80 + 0x5b) = 0;
      *(undefined2 *)(iVar10 + iVar13 * 0x80 + 0x14) = 0x14;
      *(short *)(iVar10 + iVar13 * 0x80 + 0x1c) = (short)iStack_54;
      *(undefined2 *)(iVar10 + iVar13 * 0x80 + 0x1e) = uVar18;
      AddPlace__10MenuWindowFP9MenuPlace(iStack_40 + iStack_30 * 0x16c + 0x7c,iVar10 + iVar13 * 0x80);
    }
    cVar2 = *(char *)(iStack_8c + uVar16 * 4);
    if (cVar2 == '\x03') {
      if ((pCGpffff86b4->aChr[uStack_20].bFlagsB & 1) == 0) {
        if ((pCGpffff86b4->aChr[uStack_20].bFlagsA1 & 1) == 0) {
          iStack_44 = (int)pCGpffff86b4->aChr[uStack_20].nCharId;
        }
        else {
          switch(pCGpffff86b4->aChr[uStack_20].nSubId) {
          case 0:
          case 1:
            iStack_44 = 0xc;
            break;
          case 2:
          case 3:
            iStack_44 = 0xd;
            break;
          case 4:
          case 5:
            iStack_44 = 0xe;
            break;
          case 6:
          case 7:
            iStack_44 = 0xf;
            break;
          case 8:
          case 9:
            iStack_44 = 0x10;
            break;
          case 10:
          case 0xb:
            iStack_44 = 0x11;
            break;
          case 0xc:
          case 0xd:
            iStack_44 = 0x12;
            break;
          case 0xe:
            iStack_44 = 0x13;
            break;
          case 0xf:
            iStack_44 = 0x14;
            break;
          case 0x10:
            iStack_44 = 0x15;
          }
        }
        uStack_a8 = GetRegDat__9RegDatApiFiii(0x36,iStack_44,0xffffffffffffffff);
        uStack_70 = GetRegDat__9RegDatApiFiii(0xc,iStack_44,*(undefined2 *)(iStack_8c + uVar16 * 4 + 2));
      }
      else {
        uStack_ac = GetRegDat__9RegDatApiFiii(0x36,0x17,0xffffffffffffffff);
        uStack_70 = GetRegDat__9RegDatApiFiii(0xc,0x17,*(undefined2 *)(iStack_8c + uVar16 * 4 + 2));
      }
      if (acStack_64[uVar16] == '\0') {
        *(undefined2 *)(iVar10 + iVar13 * 0x80 + 0x16) = 0;
      }
      else {
        *(undefined2 *)(iVar10 + iVar13 * 0x80 + 0x16) = 1;
      }
      if (uVar16 == uStack_10) {
        SetCSA__8FontItemFUc(iVar10 + iVar13 * 0x80,1);
        *(undefined1 *)(iVar10 + iVar13 * 0x80 + 0x5c) = 0;
        iVar14 = iVar10 + iVar13 * 0x80;
        uVar17 = (ulong)*(byte *)(iVar14 + 0x11) & 0xfffffffffffffffd | 2;
        *(char *)(iVar14 + 0x11) = (char)uVar17;
        iVar14 = iVar10 + iVar13 * 0x80;
        *(byte *)(iVar14 + 0x10) =
             *(byte *)(iVar14 + 0x10) & 0xfd | (byte)((uint)((uVar17 << 0x3e) >> 0x3f) << 1);
        iVar14 = iVar10 + iVar13 * 0x80;
        (**(code **)(*(int *)(iVar14 + 8) + 0x2c))(iVar14,0x80);
      }
      else {
        SetCSA__8FontItemFUc(iVar10 + iVar13 * 0x80,0);
        *(undefined1 *)(iVar10 + iVar13 * 0x80 + 0x5c) = 0xc;
        iVar14 = iVar10 + iVar13 * 0x80;
        uVar17 = (ulong)*(byte *)(iVar14 + 0x11) & 0xfffffffffffffffd | 2;
        *(char *)(iVar14 + 0x11) = (char)uVar17;
        iVar14 = iVar10 + iVar13 * 0x80;
        *(byte *)(iVar14 + 0x10) =
             *(byte *)(iVar14 + 0x10) & 0xfd | (byte)((uint)((uVar17 << 0x3e) >> 0x3f) << 1);
        if ((uStack_10 == 0xffffffff) && (acStack_64[uVar16] != '\0')) {
          iVar14 = iVar10 + iVar13 * 0x80;
          (**(code **)(*(int *)(iVar14 + 8) + 0x2c))(iVar14,0x80);
        }
        else {
          iVar14 = iVar10 + iVar13 * 0x80;
          (**(code **)(*(int *)(iVar14 + 8) + 0x2c))(iVar14,0x40);
        }
      }
      SetMessage__8MenuTextFPcUiUcUc(iVar10 + iVar13 * 0x80,uStack_70,0,0,1);
      iVar14 = iVar10 + iVar13 * 0x80;
      *(byte *)(iVar14 + 0x12) = *(byte *)(iVar14 + 0x12) & 0xfe | 1;
      OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_40 + iStack_30 * 0x16c + 0x3c,iVar10 + iVar13 * 0x80,1,0);
      fStack_150 = *(float *)(iVar10 + iVar13 * 0x80 + 0x2c);
      fStack_74 = fStack_150;
      if ((uVar16 & 1) == 0) {
        (**(code **)(*(int *)(iVar10 + iVar13 * 0x80 + 8) + 0x24))(fStack_78 - fStack_150,uStack_7c)
        ;
      }
      else {
        (**(code **)(*(int *)(iVar10 + iVar13 * 0x80 + 8) + 0x24))(fStack_78,uStack_7c);
      }
    }
    else if (cVar2 == '\x02') {
      uStack_a4 = GetRegDat__9RegDatApiFiii(0x38,0,0xffffffffffffffff);
      uStack_70 = GetRegDat__9RegDatApiFiii(0xe,*(undefined2 *)(iStack_8c + uVar16 * 4 + 2),0xffffffffffffffff
                                 );
      if (acStack_64[uVar16] == '\0') {
        *(undefined2 *)(iVar10 + iVar13 * 0x80 + 0x16) = 0;
      }
      else {
        *(undefined2 *)(iVar10 + iVar13 * 0x80 + 0x16) = 1;
      }
      if (uVar16 == uStack_10) {
        SetCSA__8FontItemFUc(iVar10 + iVar13 * 0x80,1);
        *(undefined1 *)(iVar10 + iVar13 * 0x80 + 0x5c) = 0;
        iVar14 = iVar10 + iVar13 * 0x80;
        *(byte *)(iVar14 + 0x11) = *(byte *)(iVar14 + 0x11) & 0xfd | 2;
        iVar14 = iVar10 + iVar13 * 0x80;
        *(byte *)(iVar14 + 0x10) = *(byte *)(iVar14 + 0x10) & 0xfd | 2;
        iVar14 = iVar10 + iVar13 * 0x80;
        (**(code **)(*(int *)(iVar14 + 8) + 0x2c))(iVar14,0x80);
      }
      else {
        SetCSA__8FontItemFUc(iVar10 + iVar13 * 0x80,0);
        *(undefined1 *)(iVar10 + iVar13 * 0x80 + 0x5c) = 4;
        iVar14 = iVar10 + iVar13 * 0x80;
        *(byte *)(iVar14 + 0x11) = *(byte *)(iVar14 + 0x11) & 0xfd | 2;
        iVar14 = iVar10 + iVar13 * 0x80;
        *(byte *)(iVar14 + 0x10) = *(byte *)(iVar14 + 0x10) & 0xfd | 2;
        if ((uStack_10 == 0xffffffff) && (acStack_64[uVar16] != '\0')) {
          iVar14 = iVar10 + iVar13 * 0x80;
          (**(code **)(*(int *)(iVar14 + 8) + 0x2c))(iVar14,0x80);
        }
        else {
          iVar14 = iVar10 + iVar13 * 0x80;
          (**(code **)(*(int *)(iVar14 + 8) + 0x2c))(iVar14,0x40);
        }
      }
      SetMessage__8MenuTextFPcUiUcUc(iVar10 + iVar13 * 0x80,uStack_70,0,0,1);
      iVar14 = iVar10 + iVar13 * 0x80;
      *(byte *)(iVar14 + 0x12) = *(byte *)(iVar14 + 0x12) & 0xfe | 1;
      uVar7 = OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_40 + iStack_30 * 0x16c + 0x3c,iVar10 + iVar13 * 0x80,1,0);
      fStack_14c = *(float *)(iVar10 + iVar13 * 0x80 + 0x2c);
      fStack_74 = fStack_14c;
      if ((uVar16 & 1) == 0) {
        iVar14 = iVar10 + iVar13 * 0x80;
        (**(code **)(*(int *)(iVar14 + 8) + 0x24))(fStack_78 - fStack_14c,uStack_7c,iVar14,uVar7);
      }
      else {
        (**(code **)(*(int *)(iVar10 + iVar13 * 0x80 + 8) + 0x24))(fStack_78,uStack_7c);
      }
    }
    else if (cVar2 == '\x01') {
      uStack_a0 = GetRegDat__9RegDatApiFiii(0x33,0,0xffffffffffffffff);
      uStack_70 = GetRegDat__9RegDatApiFiii(9,*(undefined2 *)(iStack_8c + uVar16 * 4 + 2),0xffffffffffffffff);
      if (acStack_64[uVar16] == '\0') {
        *(undefined2 *)(iVar10 + iVar13 * 0x80 + 0x16) = 0;
      }
      else {
        *(undefined2 *)(iVar10 + iVar13 * 0x80 + 0x16) = 1;
      }
      if (uVar16 == uStack_10) {
        SetCSA__8FontItemFUc(iVar10 + iVar13 * 0x80,1);
        *(undefined1 *)(iVar10 + iVar13 * 0x80 + 0x5c) = 0;
        iVar14 = iVar10 + iVar13 * 0x80;
        *(byte *)(iVar14 + 0x11) = *(byte *)(iVar14 + 0x11) & 0xfd | 2;
        iVar14 = iVar10 + iVar13 * 0x80;
        *(byte *)(iVar14 + 0x10) = *(byte *)(iVar14 + 0x10) & 0xfd | 2;
        iVar14 = iVar10 + iVar13 * 0x80;
        (**(code **)(*(int *)(iVar14 + 8) + 0x2c))(iVar14,0x80);
      }
      else {
        SetCSA__8FontItemFUc(iVar10 + iVar13 * 0x80,1);
        *(undefined1 *)(iVar10 + iVar13 * 0x80 + 0x5c) = 4;
        iVar14 = iVar10 + iVar13 * 0x80;
        uVar17 = (ulong)*(byte *)(iVar14 + 0x11) & 0xfffffffffffffffd | 2;
        *(char *)(iVar14 + 0x11) = (char)uVar17;
        iVar14 = iVar10 + iVar13 * 0x80;
        *(byte *)(iVar14 + 0x10) =
             *(byte *)(iVar14 + 0x10) & 0xfd | (byte)((uint)((uVar17 << 0x3e) >> 0x3f) << 1);
        if ((uStack_10 == 0xffffffff) && (acStack_64[uVar16] != '\0')) {
          iVar14 = iVar10 + iVar13 * 0x80;
          (**(code **)(*(int *)(iVar14 + 8) + 0x2c))(iVar14,0x80);
        }
        else {
          iVar14 = iVar10 + iVar13 * 0x80;
          (**(code **)(*(int *)(iVar14 + 8) + 0x2c))(iVar14,0x40);
        }
      }
      SetMessage__8MenuTextFPcUiUcUc(iVar10 + iVar13 * 0x80,uStack_70,0,0,1);
      iVar14 = iVar10 + iVar13 * 0x80;
      *(byte *)(iVar14 + 0x12) = *(byte *)(iVar14 + 0x12) & 0xfe | 1;
      OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_40 + iStack_30 * 0x16c + 0x3c,iVar10 + iVar13 * 0x80,1,0);
      fStack_148 = *(float *)(iVar10 + iVar13 * 0x80 + 0x2c);
      fStack_74 = fStack_148;
      if ((uVar16 & 1) == 0) {
        (**(code **)(*(int *)(iVar10 + iVar13 * 0x80 + 8) + 0x24))(fStack_78 - fStack_148,uStack_7c)
        ;
      }
      else {
        (**(code **)(*(int *)(iVar10 + iVar13 * 0x80 + 8) + 0x24))(fStack_78,uStack_7c);
      }
    }
    else if (cVar2 == '\0') {
      *(undefined2 *)(iVar10 + iVar13 * 0x80 + 0x16) = 1;
      if (uVar16 == uStack_10) {
        SetCSA__8FontItemFUc(iVar10 + iVar13 * 0x80,1);
        *(undefined1 *)(iVar10 + iVar13 * 0x80 + 0x5c) = 0;
        iVar14 = iVar10 + iVar13 * 0x80;
        uVar17 = (ulong)*(byte *)(iVar14 + 0x11) & 0xfffffffffffffffd | 2;
        *(char *)(iVar14 + 0x11) = (char)uVar17;
        iVar14 = iVar10 + iVar13 * 0x80;
        *(byte *)(iVar14 + 0x10) =
             *(byte *)(iVar14 + 0x10) & 0xfd | (byte)((uint)((uVar17 << 0x3e) >> 0x3f) << 1);
        iVar14 = iVar10 + iVar13 * 0x80;
        (**(code **)(*(int *)(iVar14 + 8) + 0x2c))(iVar14,0x80);
      }
      else {
        SetCSA__8FontItemFUc(iVar10 + iVar13 * 0x80,0);
        *(undefined1 *)(iVar10 + iVar13 * 0x80 + 0x5c) = 0;
        iVar14 = iVar10 + iVar13 * 0x80;
        uVar17 = (ulong)*(byte *)(iVar14 + 0x11) & 0xfffffffffffffffd | 2;
        *(char *)(iVar14 + 0x11) = (char)uVar17;
        iVar14 = iVar10 + iVar13 * 0x80;
        *(byte *)(iVar14 + 0x10) =
             *(byte *)(iVar14 + 0x10) & 0xfd | (byte)((uint)((uVar17 << 0x3e) >> 0x3f) << 1);
        if (uStack_10 == 0xffffffff) {
          iVar14 = iVar10 + iVar13 * 0x80;
          (**(code **)(*(int *)(iVar14 + 8) + 0x2c))(iVar14,0x80);
        }
        else {
          iVar14 = iVar10 + iVar13 * 0x80;
          (**(code **)(*(int *)(iVar14 + 8) + 0x2c))(iVar14,0x40);
        }
      }
      SetMessage__8MenuTextFPcUiUcUc(iVar10 + iVar13 * 0x80,puRam0040ab20[1],0,0,1);
      iVar14 = iVar10 + iVar13 * 0x80;
      *(byte *)(iVar14 + 0x12) = *(byte *)(iVar14 + 0x12) & 0xfe | 1;
      uVar7 = OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_40 + iStack_30 * 0x16c + 0x3c,iVar10 + iVar13 * 0x80,1,0);
      fStack_144 = *(float *)(iVar10 + iVar13 * 0x80 + 0x2c);
      fStack_74 = fStack_144;
      if ((uVar16 & 1) == 0) {
        iVar14 = iVar10 + iVar13 * 0x80;
        (**(code **)(*(int *)(iVar14 + 8) + 0x24))(fStack_78 - fStack_144,uStack_7c,iVar14,uVar7);
      }
      else {
        (**(code **)(*(int *)(iVar10 + iVar13 * 0x80 + 8) + 0x24))(fStack_78,uStack_7c);
      }
    }
    else {
      *(undefined2 *)(iVar10 + iVar13 * 0x80 + 0x16) = 0;
      SetCSA__8FontItemFUc(iVar10 + iVar13 * 0x80,2);
      *(undefined1 *)(iVar10 + iVar13 * 0x80 + 0x5c) = 0;
      iVar14 = iVar10 + iVar13 * 0x80;
      uVar17 = (ulong)*(byte *)(iVar14 + 0x11) & 0xfffffffffffffffd | 2;
      *(char *)(iVar14 + 0x11) = (char)uVar17;
      iVar14 = iVar10 + iVar13 * 0x80;
      *(byte *)(iVar14 + 0x10) =
           *(byte *)(iVar14 + 0x10) & 0xfd | (byte)((uint)((uVar17 << 0x3e) >> 0x3f) << 1);
      iVar14 = iVar10 + iVar13 * 0x80;
      uVar7 = (**(code **)(*(int *)(iVar14 + 8) + 0x2c))(iVar14,0x40);
      SetMessage__8MenuTextFPcUiUcUc(iVar10 + iVar13 * 0x80,*puRam0040ab20,0,0,1,uVar7);
      iVar14 = iVar10 + iVar13 * 0x80;
      *(byte *)(iVar14 + 0x12) = *(byte *)(iVar14 + 0x12) & 0xfe | 1;
      OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_40 + iStack_30 * 0x16c + 0x3c,iVar10 + iVar13 * 0x80,1,0);
      fStack_154 = *(float *)(iVar10 + iVar13 * 0x80 + 0x2c);
      fStack_74 = fStack_154;
      if ((uVar16 & 1) == 0) {
        (**(code **)(*(int *)(iVar10 + iVar13 * 0x80 + 8) + 0x24))(fStack_78 - fStack_154,uStack_7c)
        ;
      }
      else {
        (**(code **)(*(int *)(iVar10 + iVar13 * 0x80 + 8) + 0x24))(fStack_78,uStack_7c);
      }
    }
    iVar13 = iVar13 + 1;
  }
  if (*(short *)(iStack_40 + 0xa32) == 1) {
    *(undefined2 *)(iStack_40 + 0xa32) = 2;
  }
  if (iStack_48 != 0) {
    Open__10MenuWindowFUci(iStack_40 + iStack_30 * 0x16c + 0x7c,0,0x85);
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005c7c00  SetComboShortCutSettingMenu__7BtlMenuFiii
 * C++: BtlMenu::SetComboShortCutSettingMenu(int, int, int)
 * size: 0x7614 bytes
 * --------------------------------------------------------------------------- */
/* WARNING: Removing unreachable block (ram,0x005cdad8) */
/* WARNING: Removing unreachable block (ram,0x005cdb28) */
/* WARNING: Removing unreachable block (ram,0x005cdb78) */

void SetComboShortCutSettingMenu__7BtlMenuFiii(int param_1,int param_2,int param_3,uint param_4)

{
  byte bVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  int iVar8;
  undefined8 uVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  uint uVar13;
  ulong uVar14;
  undefined2 uVar15;
  float fVar16;
  int iStack_88;
  float fStack_78;
  float fStack_74;
  undefined4 uStack_6c;
  byte abStack_68 [4];
  byte abStack_64 [4];
  char acStack_60 [4];
  undefined4 uStack_5c;
  int iStack_58;
  undefined4 uStack_54;
  int iStack_50;
  int iStack_4c;
  int iStack_48;
  int iStack_44;
  int iStack_40;
  int iStack_30;
  int iStack_20;
  uint uStack_10;
  
  uStack_5c = 6;
  for (iVar11 = 0; iVar11 < 0x20; iVar11 = iVar11 + 1) {
    if (*(char *)((int)pCGpffff86b4 +
                 iVar11 * 0xc + (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 +
                 0x1bc) == '#') {
      uStack_5c = *(undefined4 *)
                   ((int)pCGpffff86b4 +
                   iVar11 * 0xc + (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 +
                   0x1c0);
    }
  }
  if ((pCGpffff86b4->aChr[param_3].bFlagsA1 & 1) == 0) {
    iStack_88 = ourBtlSaveDat + pCGpffff86b4->aChr[param_3].nCharId * 0x10 + 0xf44;
  }
  else {
    iStack_88 = ourBtlSaveDat + pCGpffff86b4->aChr[param_3].nSubId * 0x10 + 0x1004;
  }
  iStack_40 = param_1;
  iStack_30 = param_2;
  iStack_20 = param_3;
  uStack_10 = param_4;
  if (*(short *)(param_1 + param_2 * 0x16c + 0x32) == 0) {
    iStack_48 = 1;
    *(undefined2 *)(param_1 + param_2 * 0x16c + 0x32) = 1;
    *(undefined2 *)(param_1 + param_2 * 0x16c + 0x34) = 0;
    *(undefined2 *)(param_1 + param_2 * 0x16c + 0x36) = 0;
    *(undefined4 *)(param_1 + param_2 * 0x16c + 0x38) = 0;
    *(undefined2 *)(param_1 + param_2 * 0x16c + 0x90) = 8;
    AddOT__7MenuObjFv(param_1 + param_2 * 0x16c + 0x7c);
    iVar11 = iStack_40 + iStack_30 * 0x16c;
    *(byte *)(iVar11 + 0x30) = *(byte *)(iVar11 + 0x30) & 0xfb | 4;
    Create__10MenuWindowFUcUcffff(0,0,0x44000000,0x43e00000,iStack_40 + iStack_30 * 0x16c + 0x7c,0,1);
    *(undefined4 *)(iStack_40 + iStack_30 * 0x16c + 0x178) = 0;
    iVar11 = iStack_40 + iStack_30 * 0x16c;
    *(byte *)(iVar11 + 0x30) = *(byte *)(iVar11 + 0x30) & 0xf7 | 8;
  }
  else {
    iStack_48 = 0;
  }
  if (iStack_48 == 0) {
    if ((long)((ulong)*(byte *)(iStack_40 + iStack_30 * 0x16c + 0x30) << 0x3e) < 0) {
      ClearImage__8FontDrawFv(iStack_40 + iStack_30 * 0x16c + 0x3c);
    }
  }
  else {
    Create__8FontDrawF6GS_PSMUsUsUcUiP10ClutRaster(iStack_40 + iStack_30 * 0x16c + 0x3c,0x2c,0x100,0x200,1,0,0);
    iVar11 = iStack_40 + iStack_30 * 0x16c;
    *(byte *)(iVar11 + 0x30) = *(byte *)(iVar11 + 0x30) & 0xfd | 2;
    if (((ulong)*(ushort *)(iStack_40 + iStack_30 * 0x16c + 0x30) & 0xfff) >> 4 == 0) {
      uVar9 = __nwa__FUi(0x210);
      uVar7 = __construct_new_array(uVar9,0x27bfd0,0x27c030,0x80,4);
      *(undefined4 *)(iStack_40 + iStack_30 * 0x16c + 0x130) = uVar7;
      iVar11 = iStack_40 + iStack_30 * 0x16c;
      *(ushort *)(iVar11 + 0x30) = *(ushort *)(iVar11 + 0x30) & 0xf00f | 0x40;
    }
    if (*(int *)(iStack_40 + iStack_30 * 0x16c + 0x138) == 0) {
      uVar9 = __nwa__FUi(0x70);
      uVar7 = __construct_new_array(uVar9,0x277820,0x277890,0x30,2);
      *(undefined4 *)(iStack_40 + iStack_30 * 0x16c + 0x138) = uVar7;
    }
    if (*(int *)(iStack_40 + iStack_30 * 0x16c + 0x13c) == 0) {
      uVar9 = __nwa__FUi(0x6d0);
      uVar7 = __construct_new_array(uVar9,0x266140,0x2661a0,0x60,0x12);
      *(undefined4 *)(iStack_40 + iStack_30 * 0x16c + 0x13c) = uVar7;
    }
    if (*(int *)(iStack_40 + iStack_30 * 0x16c + 0x144) == 0) {
      uVar9 = __nwa__FUi(0x88);
      uVar7 = __construct_new_array(uVar9,0x28d000,0x28d070,0x28,3);
      *(undefined4 *)(iStack_40 + iStack_30 * 0x16c + 0x144) = uVar7;
    }
    if (*(int *)(iStack_40 + iStack_30 * 0x16c + 0x148) == 0) {
      uVar9 = __nwa__FUi(0x19c);
      uVar7 = __construct_new_array(uVar9,0x276640,0x2766d0,0x84,3);
      *(undefined4 *)(iStack_40 + iStack_30 * 0x16c + 0x148) = uVar7;
    }
  }
  fVar16 = ((*(float *)(iRam0040ab1c + 4) - 128.0) / 2.0 + 128.0) - 42.0;
  iVar11 = *(int *)(iStack_40 + iStack_30 * 0x16c + 0x138);
  iVar3 = *(int *)(iStack_40 + iStack_30 * 0x16c + 0x130);
  iVar4 = *(int *)(iStack_40 + iStack_30 * 0x16c + 0x13c);
  iVar5 = *(int *)(iStack_40 + iStack_30 * 0x16c + 0x144);
  iVar6 = *(int *)(iStack_40 + iStack_30 * 0x16c + 0x148);
  iVar12 = 0;
  iStack_50 = 0;
  iStack_4c = 0;
  for (iVar10 = 0; iVar10 < 4; iVar10 = iVar10 + 1) {
    acStack_60[iVar10] = '\0';
    cVar2 = *(char *)(iStack_88 + iVar10 * 4);
    if (cVar2 == '\x03') {
      if ((pCGpffff86b4->aChr[iStack_20].bFlagsB & 1) == 0) {
        if ((pCGpffff86b4->aChr[iStack_20].bFlagsA1 & 1) == 0) {
          iStack_44 = (int)pCGpffff86b4->aChr[iStack_20].nCharId;
        }
        else {
          switch(pCGpffff86b4->aChr[iStack_20].nSubId) {
          case 0:
          case 1:
            iStack_44 = 0xc;
            break;
          case 2:
          case 3:
            iStack_44 = 0xd;
            break;
          case 4:
          case 5:
            iStack_44 = 0xe;
            break;
          case 6:
          case 7:
            iStack_44 = 0xf;
            break;
          case 8:
          case 9:
            iStack_44 = 0x10;
            break;
          case 10:
          case 0xb:
            iStack_44 = 0x11;
            break;
          case 0xc:
          case 0xd:
            iStack_44 = 0x12;
            break;
          case 0xe:
            iStack_44 = 0x13;
            break;
          case 0xf:
            iStack_44 = 0x14;
            break;
          case 0x10:
            iStack_44 = 0x15;
          }
        }
        iVar8 = GetRegDat__9RegDatApiFiii(0x36,iStack_44,0xffffffffffffffff);
        iStack_58 = DecMPp__7CBattleFiiii
                              (pCGpffff86b4,iStack_20,1,(int)*(short *)(iStack_88 + iVar10 * 4 + 2),
                               (uint)*(ushort *)
                                      (iVar8 + *(short *)(iStack_88 + iVar10 * 4 + 2) * 0x40 + 0x1e)
                              );
        iStack_58 = iStack_58 / 100;
        if ((long)iStack_58 <= (long)pCGpffff86b4->aChr[iStack_20].nMp) {
          acStack_60[iVar10] = '\x01';
        }
        abStack_64[iVar10] =
             (byte)(((ulong)*(byte *)(iVar8 + *(short *)(iStack_88 + iVar10 * 4 + 2) * 0x40 + 6) <<
                    0x3c) >> 0x3d);
        abStack_68[iVar10] =
             *(byte *)(iVar8 + *(short *)(iStack_88 + iVar10 * 4 + 2) * 0x40 + 4) & 7;
      }
    }
    else if (cVar2 == '\x02') {
      iVar8 = GetRegDat__9RegDatApiFiii(0x38,0,0xffffffffffffffff);
      iStack_58 = DecMPp__7CBattleFiiii
                            (pCGpffff86b4,iStack_20,2,(int)*(short *)(iStack_88 + iVar10 * 4 + 2),
                             (uint)*(ushort *)
                                    (iVar8 + *(short *)(iStack_88 + iVar10 * 4 + 2) * 0x44 + 0x1e));
      iStack_58 = iStack_58 / 100;
      if ((long)iStack_58 <= (long)pCGpffff86b4->aChr[iStack_20].nMp) {
        acStack_60[iVar10] = '\x01';
      }
      abStack_64[iVar10] =
           (byte)(((ulong)*(byte *)(iVar8 + *(short *)(iStack_88 + iVar10 * 4 + 2) * 0x44 + 6) <<
                  0x3c) >> 0x3d);
      abStack_68[iVar10] = *(byte *)(iVar8 + *(short *)(iStack_88 + iVar10 * 4 + 2) * 0x44 + 4) & 7;
    }
    else if (cVar2 == '\x01') {
      if (*(char *)(ourBtlSaveDat + (uint)*(byte *)(ourBtlSaveDat + 2) * 0x200 +
                    (int)*(short *)(iStack_88 + iVar10 * 4 + 2) + 0x944) != '\0') {
        acStack_60[iVar10] = '\x01';
      }
      abStack_64[iVar10] = *(byte *)(iStack_88 + iVar10 * 4 + 1);
      abStack_68[iVar10] = (byte)uStack_5c;
    }
    else if (cVar2 == '\0') {
      acStack_60[iVar10] = '\x01';
      abStack_64[iVar10] = *(byte *)(iStack_88 + iVar10 * 4 + 1);
      abStack_68[iVar10] = (byte)uStack_5c;
    }
  }
  if (iStack_48 != 0) {
    CreatePacket__10MenuPacketFUs(iVar5 + iStack_50 * 0x28 + 0x18,4);
    SetRegister__12MenuRegisterFiUlUl(iVar5 + iStack_50 * 0x28,0,0x42,0x44);
    *(undefined2 *)(iVar5 + iStack_50 * 0x28 + 0x14) = 0;
    AddPriority__12MenuObjTableFP7MenuObj(iStack_40 + iStack_30 * 0x16c + 0x94,iVar5 + iStack_50 * 0x28);
    Create__11MenuPolygonFUcUc(iVar6,0,1);
    *(undefined2 *)(iVar6 + 0x14) = 0;
    SetVertex__11MenuPolygonFiffb(0,fVar16,iVar6,0,1);
    SetColor__11MenuPolygonFiUcUcUc(iVar6,0,0,0,0);
    *(undefined1 *)(iVar6 + 0x4f) = 0;
    uVar14 = (ulong)*(byte *)(iVar6 + 0x11) & 0xffffffffffffffef | 0x10;
    *(char *)(iVar6 + 0x11) = (char)uVar14;
    *(byte *)(iVar6 + 0x10) =
         *(byte *)(iVar6 + 0x10) & 0xef | (byte)((uint)((uVar14 << 0x3b) >> 0x3f) << 4);
    SetVertex__11MenuPolygonFiffb(0,fVar16 + 16.0,iVar6,1,1);
    SetColor__11MenuPolygonFiUcUcUc(iVar6,1,0,0,0);
    *(undefined1 *)(iVar6 + 0x77) = 0x60;
    uVar14 = (ulong)*(byte *)(iVar6 + 0x11) & 0xffffffffffffffef | 0x10;
    *(char *)(iVar6 + 0x11) = (char)uVar14;
    *(byte *)(iVar6 + 0x10) =
         *(byte *)(iVar6 + 0x10) & 0xef | (byte)((uint)((uVar14 << 0x3b) >> 0x3f) << 4);
    SetVertex__11MenuPolygonFiffb(0x44004000,fVar16,iVar6,2,1);
    SetColor__11MenuPolygonFiUcUcUc(iVar6,2,0,0,0);
    *(undefined1 *)(iVar6 + 0x7b) = 0;
    uVar14 = (ulong)*(byte *)(iVar6 + 0x11) & 0xffffffffffffffef | 0x10;
    *(char *)(iVar6 + 0x11) = (char)uVar14;
    *(byte *)(iVar6 + 0x10) =
         *(byte *)(iVar6 + 0x10) & 0xef | (byte)((uint)((uVar14 << 0x3b) >> 0x3f) << 4);
    SetVertex__11MenuPolygonFiffb(0x43ff8000,fVar16 + 16.0,iVar6,3,1);
    SetColor__11MenuPolygonFiUcUcUc(iVar6,3,0,0,0);
    *(undefined1 *)(iVar6 + 0x7f) = 0x60;
    uVar14 = (ulong)*(byte *)(iVar6 + 0x11) & 0xffffffffffffffef | 0x10;
    *(char *)(iVar6 + 0x11) = (char)uVar14;
    *(byte *)(iVar6 + 0x10) =
         *(byte *)(iVar6 + 0x10) & 0xef | (byte)((uint)((uVar14 << 0x3b) >> 0x3f) << 4);
    *(byte *)(iVar6 + 0x12) = *(byte *)(iVar6 + 0x12) & 0xfe | 1;
    *(undefined2 *)(iVar6 + 0x1c) = 0;
    *(undefined2 *)(iVar6 + 0x1e) = 0;
    uVar9 = AddPlace__10MenuWindowFP9MenuPlace(iStack_40 + iStack_30 * 0x16c + 0x7c,iVar6);
    Create__11MenuPolygonFUcUc(iVar6 + 0x84,0,1,1,0x84,uVar9);
    *(undefined2 *)(iVar6 + 0x98) = 0;
    SetVertex__11MenuPolygonFiffb(0,fVar16 + 16.0,iVar6 + 0x84,0,1);
    SetColor__11MenuPolygonFiUcUcUc(iVar6 + 0x84,0,0,0,0);
    *(undefined1 *)(iVar6 + 0xd3) = 0x60;
    *(byte *)(iVar6 + 0x95) = *(byte *)(iVar6 + 0x95) & 0xef | 0x10;
    *(byte *)(iVar6 + 0x94) = *(byte *)(iVar6 + 0x94) & 0xef | 0x10;
    SetVertex__11MenuPolygonFiffb(0,fVar16 + 68.0,iVar6 + 0x84,1,1);
    SetColor__11MenuPolygonFiUcUcUc(iVar6 + 0x84,1,0,0,0);
    *(undefined1 *)(iVar6 + 0xfb) = 0x60;
    uVar14 = (ulong)*(byte *)(iVar6 + 0x95) & 0xffffffffffffffef | 0x10;
    *(char *)(iVar6 + 0x95) = (char)uVar14;
    *(byte *)(iVar6 + 0x94) =
         *(byte *)(iVar6 + 0x94) & 0xef | (byte)((uint)((uVar14 << 0x3b) >> 0x3f) << 4);
    SetVertex__11MenuPolygonFiffb(0x44004000,fVar16 + 16.0,iVar6 + 0x84,2,1);
    SetColor__11MenuPolygonFiUcUcUc(iVar6 + 0x84,2,0,0,0);
    *(undefined1 *)(iVar6 + 0xff) = 0x60;
    uVar14 = (ulong)*(byte *)(iVar6 + 0x95) & 0xffffffffffffffef | 0x10;
    *(char *)(iVar6 + 0x95) = (char)uVar14;
    *(byte *)(iVar6 + 0x94) =
         *(byte *)(iVar6 + 0x94) & 0xef | (byte)((uint)((uVar14 << 0x3b) >> 0x3f) << 4);
    SetVertex__11MenuPolygonFiffb(0x43ff8000,fVar16 + 68.0,iVar6 + 0x84,3,1);
    SetColor__11MenuPolygonFiUcUcUc(iVar6 + 0x84,3,0,0,0);
    *(undefined1 *)(iVar6 + 0x103) = 0x60;
    uVar14 = (ulong)*(byte *)(iVar6 + 0x95) & 0xffffffffffffffef | 0x10;
    *(char *)(iVar6 + 0x95) = (char)uVar14;
    *(byte *)(iVar6 + 0x94) =
         *(byte *)(iVar6 + 0x94) & 0xef | (byte)((uint)((uVar14 << 0x3b) >> 0x3f) << 4);
    *(byte *)(iVar6 + 0x96) = *(byte *)(iVar6 + 0x96) & 0xfe | 1;
    *(undefined2 *)(iVar6 + 0xa0) = 1;
    *(undefined2 *)(iVar6 + 0xa2) = 0;
    AddPlace__10MenuWindowFP9MenuPlace(iStack_40 + iStack_30 * 0x16c + 0x7c,iVar6 + 0x84);
    Create__11MenuPolygonFUcUc(iVar6 + 0x108,0,1);
    *(undefined2 *)(iVar6 + 0x11c) = 0;
    SetVertex__11MenuPolygonFiffb(0,fVar16 + 68.0,iVar6 + 0x108,0,1);
    SetColor__11MenuPolygonFiUcUcUc(iVar6 + 0x108,0,0,0,0);
    *(undefined1 *)(iVar6 + 0x157) = 0x60;
    uVar14 = (ulong)*(byte *)(iVar6 + 0x119) & 0xffffffffffffffef | 0x10;
    *(char *)(iVar6 + 0x119) = (char)uVar14;
    *(byte *)(iVar6 + 0x118) =
         *(byte *)(iVar6 + 0x118) & 0xef | (byte)((uint)((uVar14 << 0x3b) >> 0x3f) << 4);
    uVar9 = SetVertex__11MenuPolygonFiffb(0,fVar16 + 84.0,iVar6 + 0x108,1,1);
    SetColor__11MenuPolygonFiUcUcUc(iVar6 + 0x108,1,0,0,0,uVar9);
    *(undefined1 *)(iVar6 + 0x17f) = 0;
    uVar14 = (ulong)*(byte *)(iVar6 + 0x119) & 0xffffffffffffffef | 0x10;
    *(char *)(iVar6 + 0x119) = (char)uVar14;
    *(byte *)(iVar6 + 0x118) =
         *(byte *)(iVar6 + 0x118) & 0xef | (byte)((uint)((uVar14 << 0x3b) >> 0x3f) << 4);
    SetVertex__11MenuPolygonFiffb(0x44004000,fVar16 + 68.0,iVar6 + 0x108,2,1);
    SetColor__11MenuPolygonFiUcUcUc(iVar6 + 0x108,2,0,0,0);
    *(undefined1 *)(iVar6 + 0x183) = 0x60;
    uVar14 = (ulong)*(byte *)(iVar6 + 0x119) & 0xffffffffffffffef | 0x10;
    *(char *)(iVar6 + 0x119) = (char)uVar14;
    *(byte *)(iVar6 + 0x118) =
         *(byte *)(iVar6 + 0x118) & 0xef | (byte)((uint)((uVar14 << 0x3b) >> 0x3f) << 4);
    uVar9 = SetVertex__11MenuPolygonFiffb(0x43ff8000,fVar16 + 84.0,iVar6 + 0x108,3,1);
    SetColor__11MenuPolygonFiUcUcUc(iVar6 + 0x108,3,0,0,0,0x40,iVar6 + 0x108,uVar9);
    *(undefined1 *)(iVar6 + 0x187) = 0;
    uVar14 = (ulong)*(byte *)(iVar6 + 0x119) & 0xffffffffffffffef | 0x10;
    *(char *)(iVar6 + 0x119) = (char)uVar14;
    *(byte *)(iVar6 + 0x118) =
         *(byte *)(iVar6 + 0x118) & 0xef | (byte)((uint)((uVar14 << 0x3b) >> 0x3f) << 4);
    *(byte *)(iVar6 + 0x11a) = *(byte *)(iVar6 + 0x11a) & 0xfe | 1;
    *(undefined2 *)(iVar6 + 0x124) = 1;
    *(undefined2 *)(iVar6 + 0x126) = 0;
    AddPlace__10MenuWindowFP9MenuPlace(iStack_40 + iStack_30 * 0x16c + 0x7c,iVar6 + 0x108);
  }
  iStack_50 = iStack_50 + 1;
  uVar9 = 1;
  if (iStack_48 != 0) {
    uVar7 = *(undefined4 *)
             (*(int *)&pCGpffff86b4->field_0x4304 +
              (uint)*(ushort *)(*(int *)&pCGpffff86b4->field_0x4304 + 10) * 4 + 0xc);
    uVar9 = GetTex0__6JRCTexFb(*(undefined4 *)&pCGpffff86b4->field_0x4304,0);
    Create__11SendOnLocalFP4_QWDUl(iVar11 + iStack_4c * 0x30,uVar7,uVar9);
    *(undefined2 *)(iVar11 + iStack_4c * 0x30 + 0x14) = 1;
    AddPriority__12MenuObjTableFP7MenuObj(iStack_40 + iStack_30 * 0x16c + 0x94,iVar11 + iStack_4c * 0x30);
    CreatePacket__10MenuPacketFUs(iVar5 + iStack_50 * 0x28 + 0x18,4);
    SetRegister__12MenuRegisterFiUlUl(iVar5 + iStack_50 * 0x28,0,0x42,0x48);
    *(undefined2 *)(iVar5 + iStack_50 * 0x28 + 0x14) = 1;
    AddPriority__12MenuObjTableFP7MenuObj(iStack_40 + iStack_30 * 0x16c + 0x94,iVar5 + iStack_50 * 0x28);
    Create__10MenuSpriteFUc(iVar4,1);
    *(byte *)(iVar4 + 0x21) = *(byte *)(iVar4 + 0x21) & 0xbf | 0x40;
    *(byte *)(iVar4 + 0x11) = *(byte *)(iVar4 + 0x11) & 0xfd | 2;
    *(byte *)(iVar4 + 0x10) = *(byte *)(iVar4 + 0x10) & 0xfd | 2;
    *(undefined2 *)(iVar4 + 0x14) = 2;
    uVar9 = (**(code **)(*(int *)(iVar4 + 8) + 0x24))(0x435c0000,fVar16 + 8.0);
    SetUV__10MenuSpriteFUsUsUsUs(iVar4,0,0,0x25,0x46,uVar9);
    (**(code **)(*(int *)(iVar4 + 8) + 0x28))(0x42140000,0x428c0000);
    (**(code **)(*(int *)(iVar4 + 8) + 0x30))(iVar4,0x80,0x40,0x10);
    (**(code **)(*(int *)(iVar4 + 8) + 0x2c))(iVar4,0x40);
    *(byte *)(iVar4 + 0x12) = *(byte *)(iVar4 + 0x12) & 0xfe | 1;
    *(undefined2 *)(iVar4 + 0x1c) = 0;
    *(undefined2 *)(iVar4 + 0x1e) = 1;
    AddPlace__10MenuWindowFP9MenuPlace(iStack_40 + iStack_30 * 0x16c + 0x7c,iVar4);
    Create__10MenuSpriteFUc(iVar4 + 0x60,1);
    *(byte *)(iVar4 + 0x81) = *(byte *)(iVar4 + 0x81) & 0xbf | 0x40;
    uVar14 = (ulong)*(byte *)(iVar4 + 0x71) & 0xfffffffffffffffd | 2;
    *(char *)(iVar4 + 0x71) = (char)uVar14;
    *(byte *)(iVar4 + 0x70) =
         *(byte *)(iVar4 + 0x70) & 0xfd | (byte)((uint)((uVar14 << 0x3e) >> 0x3f) << 1);
    *(undefined2 *)(iVar4 + 0x74) = 2;
    (**(code **)(*(int *)(iVar4 + 0x68) + 0x24))(0x437e0000,fVar16 + 8.0);
    SetUV__10MenuSpriteFUsUsUsUs(iVar4 + 0x60,0x25,0,0,0x46);
    (**(code **)(*(int *)(iVar4 + 0x68) + 0x28))(0x42140000,0x428c0000);
    (**(code **)(*(int *)(iVar4 + 0x68) + 0x30))(iVar4 + 0x60,0x80,0x40,0x10);
    (**(code **)(*(int *)(iVar4 + 0x68) + 0x2c))(iVar4 + 0x60,0x40);
    *(byte *)(iVar4 + 0x72) = *(byte *)(iVar4 + 0x72) & 0xfe | 1;
    *(undefined2 *)(iVar4 + 0x7c) = 1;
    *(undefined2 *)(iVar4 + 0x7e) = 1;
    uVar9 = AddPlace__10MenuWindowFP9MenuPlace(iStack_40 + iStack_30 * 0x16c + 0x7c,iVar4 + 0x60);
  }
  iStack_50 = iStack_50 + 1;
  iStack_4c = iStack_4c + 1;
  if (iStack_48 != 0) {
    Create__10MenuSpriteFUc(iVar4 + 0xc0,1,uVar9);
    *(byte *)(iVar4 + 0xe1) = *(byte *)(iVar4 + 0xe1) & 0xbf | 0x40;
    uVar14 = (ulong)*(byte *)(iVar4 + 0xd1) & 0xfffffffffffffffd | 2;
    *(char *)(iVar4 + 0xd1) = (char)uVar14;
    *(byte *)(iVar4 + 0xd0) =
         *(byte *)(iVar4 + 0xd0) & 0xfd | (byte)((uint)((uVar14 << 0x3e) >> 0x3f) << 1);
    *(undefined2 *)(iVar4 + 0xd4) = 3;
    (**(code **)(*(int *)(iVar4 + 200) + 0x24))(0x435f0000,fVar16 + 17.0);
    SetUV__10MenuSpriteFUsUsUsUs(iVar4 + 0xc0,0x47,0x2a,0x56,0x3d);
    (**(code **)(*(int *)(iVar4 + 200) + 0x28))(0x41700000,0x41980000);
    *(byte *)(iVar4 + 0xd2) = *(byte *)(iVar4 + 0xd2) & 0xfe | 1;
    *(undefined2 *)(iVar4 + 0xdc) = 0;
    *(undefined2 *)(iVar4 + 0xde) = 2;
    uVar9 = AddPlace__10MenuWindowFP9MenuPlace(iStack_40 + iStack_30 * 0x16c + 0x7c,iVar4 + 0xc0);
    Create__10MenuSpriteFUc(iVar4 + 0x120,1,uVar9);
    *(byte *)(iVar4 + 0x141) = *(byte *)(iVar4 + 0x141) & 0xbf | 0x40;
    uVar14 = (ulong)*(byte *)(iVar4 + 0x131) & 0xfffffffffffffffd | 2;
    *(char *)(iVar4 + 0x131) = (char)uVar14;
    *(byte *)(iVar4 + 0x130) =
         *(byte *)(iVar4 + 0x130) & 0xfd | (byte)((uint)((uVar14 << 0x3e) >> 0x3f) << 1);
    *(undefined2 *)(iVar4 + 0x134) = 3;
    (**(code **)(*(int *)(iVar4 + 0x128) + 0x24))(0x436e0000,fVar16 + 17.0);
    SetUV__10MenuSpriteFUsUsUsUs(iVar4 + 0x120,0x67,0x2a,0x71,0x3d);
    (**(code **)(*(int *)(iVar4 + 0x128) + 0x28))(0x41200000,0x41980000);
    *(byte *)(iVar4 + 0x132) = *(byte *)(iVar4 + 0x132) & 0xfe | 1;
    *(undefined2 *)(iVar4 + 0x13c) = 1;
    *(undefined2 *)(iVar4 + 0x13e) = 2;
    AddPlace__10MenuWindowFP9MenuPlace(iStack_40 + iStack_30 * 0x16c + 0x7c,iVar4 + 0x120);
  }
  if ((uStack_10 == 0) && (acStack_60[0] != '\0')) {
    (**(code **)(*(int *)(iVar4 + 200) + 0x30))(iVar4 + 0xc0,0x40,0x80,0x60);
    (**(code **)(*(int *)(iVar4 + 200) + 0x2c))(iVar4 + 0xc0,0x60);
    (**(code **)(*(int *)(iVar4 + 0x128) + 0x30))(iVar4 + 0x120,0x40,0x80,0x60);
    (**(code **)(*(int *)(iVar4 + 0x128) + 0x2c))(iVar4 + 0x120,0x60);
  }
  else if (acStack_60[0] == '\0') {
    (**(code **)(*(int *)(iVar4 + 200) + 0x30))(iVar4 + 0xc0,0x80,0x40,0x10);
    (**(code **)(*(int *)(iVar4 + 200) + 0x2c))(iVar4 + 0xc0,0x20);
    (**(code **)(*(int *)(iVar4 + 0x128) + 0x30))(iVar4 + 0x120,0x80,0x40,0x10);
    (**(code **)(*(int *)(iVar4 + 0x128) + 0x2c))(iVar4 + 0x120,0x20);
  }
  else {
    (**(code **)(*(int *)(iVar4 + 200) + 0x30))(iVar4 + 0xc0,0x80,0x40,0x10);
    (**(code **)(*(int *)(iVar4 + 200) + 0x2c))(iVar4 + 0xc0,0x40);
    (**(code **)(*(int *)(iVar4 + 0x128) + 0x30))(iVar4 + 0x120,0x80,0x40,0x10);
    (**(code **)(*(int *)(iVar4 + 0x128) + 0x2c))(iVar4 + 0x120,0x40);
  }
  if (iStack_48 != 0) {
    Create__10MenuSpriteFUc(iVar4 + 0x180,1);
    *(byte *)(iVar4 + 0x1a1) = *(byte *)(iVar4 + 0x1a1) & 0xbf | 0x40;
    uVar14 = (ulong)*(byte *)(iVar4 + 0x191) & 0xfffffffffffffffd | 2;
    *(char *)(iVar4 + 0x191) = (char)uVar14;
    *(byte *)(iVar4 + 400) =
         *(byte *)(iVar4 + 400) & 0xfd | (byte)((uint)((uVar14 << 0x3e) >> 0x3f) << 1);
    *(undefined2 *)(iVar4 + 0x194) = 3;
    (**(code **)(*(int *)(iVar4 + 0x188) + 0x24))(0x43848000,fVar16 + 17.0);
    SetUV__10MenuSpriteFUsUsUsUs(iVar4 + 0x180,0x56,0x2a,0x67,0x3d);
    (**(code **)(*(int *)(iVar4 + 0x188) + 0x28))(0x41880000,0x41980000);
    *(byte *)(iVar4 + 0x192) = *(byte *)(iVar4 + 0x192) & 0xfe | 1;
    *(undefined2 *)(iVar4 + 0x19c) = 0;
    *(undefined2 *)(iVar4 + 0x19e) = 3;
    AddPlace__10MenuWindowFP9MenuPlace(iStack_40 + iStack_30 * 0x16c + 0x7c,iVar4 + 0x180);
    Create__10MenuSpriteFUc(iVar4 + 0x1e0,1);
    *(byte *)(iVar4 + 0x201) = *(byte *)(iVar4 + 0x201) & 0xbf | 0x40;
    uVar14 = (ulong)*(byte *)(iVar4 + 0x1f1) & 0xfffffffffffffffd | 2;
    *(char *)(iVar4 + 0x1f1) = (char)uVar14;
    *(byte *)(iVar4 + 0x1f0) =
         *(byte *)(iVar4 + 0x1f0) & 0xfd | (byte)((uint)((uVar14 << 0x3e) >> 0x3f) << 1);
    *(undefined2 *)(iVar4 + 500) = 3;
    (**(code **)(*(int *)(iVar4 + 0x1e8) + 0x24))(0x438c0000,fVar16 + 17.0);
    uVar9 = SetUV__10MenuSpriteFUsUsUsUs(iVar4 + 0x1e0,0x67,0x2a,0x71,0x3d);
    (**(code **)(*(int *)(iVar4 + 0x1e8) + 0x28))(0x41200000,0x41980000,iVar4 + 0x1e0,uVar9);
    *(byte *)(iVar4 + 0x1f2) = *(byte *)(iVar4 + 0x1f2) & 0xfe | 1;
    *(undefined2 *)(iVar4 + 0x1fc) = 1;
    *(undefined2 *)(iVar4 + 0x1fe) = 3;
    AddPlace__10MenuWindowFP9MenuPlace(iStack_40 + iStack_30 * 0x16c + 0x7c,iVar4 + 0x1e0);
  }
  if ((uStack_10 == 1) && (acStack_60[1] != '\0')) {
    (**(code **)(*(int *)(iVar4 + 0x188) + 0x30))(iVar4 + 0x180,0x40,0x80,0x60);
    (**(code **)(*(int *)(iVar4 + 0x188) + 0x2c))(iVar4 + 0x180,0x60);
    (**(code **)(*(int *)(iVar4 + 0x1e8) + 0x30))(iVar4 + 0x1e0,0x40,0x80,0x60);
    (**(code **)(*(int *)(iVar4 + 0x1e8) + 0x2c))(iVar4 + 0x1e0,0x60);
  }
  else if (acStack_60[1] == '\0') {
    (**(code **)(*(int *)(iVar4 + 0x188) + 0x30))(iVar4 + 0x180,0x80,0x40,0x10);
    (**(code **)(*(int *)(iVar4 + 0x188) + 0x2c))(iVar4 + 0x180,0x20);
    uVar9 = (**(code **)(*(int *)(iVar4 + 0x1e8) + 0x30))(iVar4 + 0x1e0,0x80,0x40,0x10);
    (**(code **)(*(int *)(iVar4 + 0x1e8) + 0x2c))(iVar4 + 0x1e0,0x20,uVar9);
  }
  else {
    (**(code **)(*(int *)(iVar4 + 0x188) + 0x30))(iVar4 + 0x180,0x80,0x40,0x10);
    (**(code **)(*(int *)(iVar4 + 0x188) + 0x2c))(iVar4 + 0x180,0x40);
    (**(code **)(*(int *)(iVar4 + 0x1e8) + 0x30))(iVar4 + 0x1e0,0x80,0x40,0x10);
    (**(code **)(*(int *)(iVar4 + 0x1e8) + 0x2c))(iVar4 + 0x1e0,0x40);
  }
  if (iStack_48 != 0) {
    Create__10MenuSpriteFUc(iVar4 + 0x240,1);
    *(byte *)(iVar4 + 0x261) = *(byte *)(iVar4 + 0x261) & 0xbf | 0x40;
    uVar14 = (ulong)*(byte *)(iVar4 + 0x251) & 0xfffffffffffffffd | 2;
    *(char *)(iVar4 + 0x251) = (char)uVar14;
    *(byte *)(iVar4 + 0x250) =
         *(byte *)(iVar4 + 0x250) & 0xfd | (byte)((uint)((uVar14 << 0x3e) >> 0x3f) << 1);
    *(undefined2 *)(iVar4 + 0x254) = 3;
    (**(code **)(*(int *)(iVar4 + 0x248) + 0x24))(0x434c0000,fVar16 + 49.0);
    SetUV__10MenuSpriteFUsUsUsUs(iVar4 + 0x240,0x47,0x2a,0x56,0x3d);
    (**(code **)(*(int *)(iVar4 + 0x248) + 0x28))(0x41700000,0x41980000);
    *(byte *)(iVar4 + 0x252) = *(byte *)(iVar4 + 0x252) & 0xfe | 1;
    *(undefined2 *)(iVar4 + 0x25c) = 0;
    *(undefined2 *)(iVar4 + 0x25e) = 4;
    uVar9 = AddPlace__10MenuWindowFP9MenuPlace(iStack_40 + iStack_30 * 0x16c + 0x7c,iVar4 + 0x240);
    Create__10MenuSpriteFUc(iVar4 + 0x2a0,1,0x2a0,iVar4 + 0x2a0,uVar9);
    *(byte *)(iVar4 + 0x2c1) = *(byte *)(iVar4 + 0x2c1) & 0xbf | 0x40;
    uVar14 = (ulong)*(byte *)(iVar4 + 0x2b1) & 0xfffffffffffffffd | 2;
    *(char *)(iVar4 + 0x2b1) = (char)uVar14;
    *(byte *)(iVar4 + 0x2b0) =
         *(byte *)(iVar4 + 0x2b0) & 0xfd | (byte)((uint)((uVar14 << 0x3e) >> 0x3f) << 1);
    *(undefined2 *)(iVar4 + 0x2b4) = 3;
    (**(code **)(*(int *)(iVar4 + 0x2a8) + 0x24))(0x435a0000,fVar16 + 49.0);
    SetUV__10MenuSpriteFUsUsUsUs(iVar4 + 0x2a0,0x71,0x2a,0x7c,0x3d);
    (**(code **)(*(int *)(iVar4 + 0x2a8) + 0x28))(0x41300000,0x41980000);
    *(byte *)(iVar4 + 0x2b2) = *(byte *)(iVar4 + 0x2b2) & 0xfe | 1;
    *(undefined2 *)(iVar4 + 700) = 1;
    *(undefined2 *)(iVar4 + 0x2be) = 4;
    AddPlace__10MenuWindowFP9MenuPlace(iStack_40 + iStack_30 * 0x16c + 0x7c,iVar4 + 0x2a0);
  }
  if ((uStack_10 == 2) && (acStack_60[2] != '\0')) {
    (**(code **)(*(int *)(iVar4 + 0x248) + 0x30))(iVar4 + 0x240,0x40,0x80,0x60);
    (**(code **)(*(int *)(iVar4 + 0x248) + 0x2c))(iVar4 + 0x240,0x60);
    (**(code **)(*(int *)(iVar4 + 0x2a8) + 0x30))(iVar4 + 0x2a0,0x40,0x80,0x60);
    (**(code **)(*(int *)(iVar4 + 0x2a8) + 0x2c))(iVar4 + 0x2a0,0x60);
  }
  else if (acStack_60[2] == '\0') {
    (**(code **)(*(int *)(iVar4 + 0x248) + 0x30))(iVar4 + 0x240,0x80,0x40,0x10);
    (**(code **)(*(int *)(iVar4 + 0x248) + 0x2c))(iVar4 + 0x240,0x20);
    (**(code **)(*(int *)(iVar4 + 0x2a8) + 0x30))(iVar4 + 0x2a0,0x80,0x40,0x10);
    (**(code **)(*(int *)(iVar4 + 0x2a8) + 0x2c))(iVar4 + 0x2a0,0x20);
  }
  else {
    (**(code **)(*(int *)(iVar4 + 0x248) + 0x30))(iVar4 + 0x240,0x80,0x40,0x10);
    (**(code **)(*(int *)(iVar4 + 0x248) + 0x2c))(iVar4 + 0x240,0x40);
    (**(code **)(*(int *)(iVar4 + 0x2a8) + 0x30))(iVar4 + 0x2a0,0x80,0x40,0x10);
    (**(code **)(*(int *)(iVar4 + 0x2a8) + 0x2c))(iVar4 + 0x2a0,0x40);
  }
  if (iStack_48 != 0) {
    Create__10MenuSpriteFUc(iVar4 + 0x300,1);
    *(byte *)(iVar4 + 0x321) = *(byte *)(iVar4 + 0x321) & 0xbf | 0x40;
    uVar14 = (ulong)*(byte *)(iVar4 + 0x311) & 0xfffffffffffffffd | 2;
    *(char *)(iVar4 + 0x311) = (char)uVar14;
    *(byte *)(iVar4 + 0x310) =
         *(byte *)(iVar4 + 0x310) & 0xfd | (byte)((uint)((uVar14 << 0x3e) >> 0x3f) << 1);
    *(undefined2 *)(iVar4 + 0x314) = 3;
    (**(code **)(*(int *)(iVar4 + 0x308) + 0x24))(0x438c8000,fVar16 + 49.0);
    SetUV__10MenuSpriteFUsUsUsUs(iVar4 + 0x300,0x56,0x2a,0x67,0x3d);
    (**(code **)(*(int *)(iVar4 + 0x308) + 0x28))(0x41880000,0x41980000);
    *(byte *)(iVar4 + 0x312) = *(byte *)(iVar4 + 0x312) & 0xfe | 1;
    *(undefined2 *)(iVar4 + 0x31c) = 0;
    *(undefined2 *)(iVar4 + 0x31e) = 5;
    AddPlace__10MenuWindowFP9MenuPlace(iStack_40 + iStack_30 * 0x16c + 0x7c,iVar4 + 0x300);
    Create__10MenuSpriteFUc(iVar4 + 0x360,1);
    *(byte *)(iVar4 + 0x381) = *(byte *)(iVar4 + 0x381) & 0xbf | 0x40;
    uVar14 = (ulong)*(byte *)(iVar4 + 0x371) & 0xfffffffffffffffd | 2;
    *(char *)(iVar4 + 0x371) = (char)uVar14;
    *(byte *)(iVar4 + 0x370) =
         *(byte *)(iVar4 + 0x370) & 0xfd | (byte)((uint)((uVar14 << 0x3e) >> 0x3f) << 1);
    *(undefined2 *)(iVar4 + 0x374) = 3;
    uVar9 = (**(code **)(*(int *)(iVar4 + 0x368) + 0x24))(0x43938000,fVar16 + 49.0);
    SetUV__10MenuSpriteFUsUsUsUs(iVar4 + 0x360,0x71,0x2a,0x7c,0x3d,uVar9);
    (**(code **)(*(int *)(iVar4 + 0x368) + 0x28))(0x41300000,0x41980000);
    *(byte *)(iVar4 + 0x372) = *(byte *)(iVar4 + 0x372) & 0xfe | 1;
    *(undefined2 *)(iVar4 + 0x37c) = 1;
    *(undefined2 *)(iVar4 + 0x37e) = 5;
    AddPlace__10MenuWindowFP9MenuPlace(iStack_40 + iStack_30 * 0x16c + 0x7c,iVar4 + 0x360);
  }
  if ((uStack_10 == 3) && (acStack_60[3] != '\0')) {
    uVar9 = (**(code **)(*(int *)(iVar4 + 0x308) + 0x30))(iVar4 + 0x300,0x40,0x80,0x60);
    uVar9 = (**(code **)(*(int *)(iVar4 + 0x308) + 0x2c))(iVar4 + 0x300,0x60,uVar9);
    (**(code **)(*(int *)(iVar4 + 0x368) + 0x30))(iVar4 + 0x360,0x40,0x80,0x60,0x40,uVar9);
    (**(code **)(*(int *)(iVar4 + 0x368) + 0x2c))(iVar4 + 0x360,0x60);
  }
  else if (acStack_60[3] == '\0') {
    (**(code **)(*(int *)(iVar4 + 0x308) + 0x30))(iVar4 + 0x300,0x80,0x40,0x10);
    (**(code **)(*(int *)(iVar4 + 0x308) + 0x2c))(iVar4 + 0x300,0x20);
    (**(code **)(*(int *)(iVar4 + 0x368) + 0x30))(iVar4 + 0x360,0x80,0x40,0x10);
    (**(code **)(*(int *)(iVar4 + 0x368) + 0x2c))(iVar4 + 0x360,0x20);
  }
  else {
    (**(code **)(*(int *)(iVar4 + 0x308) + 0x30))(iVar4 + 0x300,0x80,0x40,0x10);
    (**(code **)(*(int *)(iVar4 + 0x308) + 0x2c))(iVar4 + 0x300,0x40);
    (**(code **)(*(int *)(iVar4 + 0x368) + 0x30))(iVar4 + 0x360,0x80,0x40,0x10);
    (**(code **)(*(int *)(iVar4 + 0x368) + 0x2c))(iVar4 + 0x360,0x40);
  }
  if (iStack_48 != 0) {
    Create__10MenuSpriteFUc(iVar4 + 0x3c0,1);
    *(byte *)(iVar4 + 0x3e1) = *(byte *)(iVar4 + 0x3e1) & 0xbf | 0x40;
    uVar14 = (ulong)*(byte *)(iVar4 + 0x3d1) & 0xfffffffffffffffd | 2;
    *(char *)(iVar4 + 0x3d1) = (char)uVar14;
    *(byte *)(iVar4 + 0x3d0) =
         *(byte *)(iVar4 + 0x3d0) & 0xfd | (byte)((uint)((uVar14 << 0x3e) >> 0x3f) << 1);
    *(undefined2 *)(iVar4 + 0x3d4) = 4;
    (**(code **)(*(int *)(iVar4 + 0x3c8) + 0x24))(0x43400000,fVar16 + 8.0);
    uVar9 = SetUV__10MenuSpriteFUsUsUsUs(iVar4 + 0x3c0,0x25,0x1f,0x45,0x43);
    (**(code **)(*(int *)(iVar4 + 0x3c8) + 0x28))
              (0x42000000,0x42100000,iVar4 + 0x3c0,iVar4 + 0x3c0,uVar9);
    *(byte *)(iVar4 + 0x3d2) = *(byte *)(iVar4 + 0x3d2) & 0xfe | 1;
    *(undefined2 *)(iVar4 + 0x3dc) = 0;
    *(undefined2 *)(iVar4 + 0x3de) = 6;
    AddPlace__10MenuWindowFP9MenuPlace(iStack_40 + iStack_30 * 0x16c + 0x7c,iVar4 + 0x3c0);
  }
  if ((uStack_10 == 0) && (acStack_60[0] != '\0')) {
    (**(code **)(*(int *)(iVar4 + 0x3c8) + 0x30))(iVar4 + 0x3c0,0x40,0x80,0x60);
    (**(code **)(*(int *)(iVar4 + 0x3c8) + 0x2c))(iVar4 + 0x3c0,0x60);
  }
  else if (acStack_60[0] == '\0') {
    (**(code **)(*(int *)(iVar4 + 0x3c8) + 0x30))(iVar4 + 0x3c0,0x80,0x40,0x10);
    (**(code **)(*(int *)(iVar4 + 0x3c8) + 0x2c))(iVar4 + 0x3c0,0x20);
  }
  else {
    (**(code **)(*(int *)(iVar4 + 0x3c8) + 0x30))(iVar4 + 0x3c0,0x80,0x40,0x10);
    (**(code **)(*(int *)(iVar4 + 0x3c8) + 0x2c))(iVar4 + 0x3c0,0x40);
  }
  if (iStack_48 != 0) {
    Create__10MenuSpriteFUc(iVar4 + 0x420,1);
    *(byte *)(iVar4 + 0x441) = *(byte *)(iVar4 + 0x441) & 0xbf | 0x40;
    uVar14 = (ulong)*(byte *)(iVar4 + 0x431) & 0xfffffffffffffffd | 2;
    *(char *)(iVar4 + 0x431) = (char)uVar14;
    *(byte *)(iVar4 + 0x430) =
         *(byte *)(iVar4 + 0x430) & 0xfd | (byte)((uint)((uVar14 << 0x3e) >> 0x3f) << 1);
    *(undefined2 *)(iVar4 + 0x434) = 4;
    (**(code **)(*(int *)(iVar4 + 0x428) + 0x24))(0x43900000,fVar16 + 8.0);
    SetUV__10MenuSpriteFUsUsUsUs(iVar4 + 0x420,0x25,0x1f,0x45,0x43);
    (**(code **)(*(int *)(iVar4 + 0x428) + 0x28))(0x42000000,0x42100000);
    *(byte *)(iVar4 + 0x432) = *(byte *)(iVar4 + 0x432) & 0xfe | 1;
    *(undefined2 *)(iVar4 + 0x43c) = 0;
    *(undefined2 *)(iVar4 + 0x43e) = 7;
    AddPlace__10MenuWindowFP9MenuPlace(iStack_40 + iStack_30 * 0x16c + 0x7c,iVar4 + 0x420);
  }
  if ((uStack_10 == 1) && (acStack_60[1] != '\0')) {
    (**(code **)(*(int *)(iVar4 + 0x428) + 0x30))(iVar4 + 0x420,0x40,0x80,0x60);
    (**(code **)(*(int *)(iVar4 + 0x428) + 0x2c))(iVar4 + 0x420,0x60);
  }
  else if (acStack_60[1] == '\0') {
    (**(code **)(*(int *)(iVar4 + 0x428) + 0x30))(iVar4 + 0x420,0x80,0x40,0x10);
    (**(code **)(*(int *)(iVar4 + 0x428) + 0x2c))(iVar4 + 0x420,0x20);
  }
  else {
    (**(code **)(*(int *)(iVar4 + 0x428) + 0x30))(iVar4 + 0x420,0x80,0x40,0x10);
    (**(code **)(*(int *)(iVar4 + 0x428) + 0x2c))(iVar4 + 0x420,0x40);
  }
  if (iStack_48 != 0) {
    Create__10MenuSpriteFUc(iVar4 + 0x480,1);
    *(byte *)(iVar4 + 0x4a1) = *(byte *)(iVar4 + 0x4a1) & 0xbf | 0x40;
    uVar14 = (ulong)*(byte *)(iVar4 + 0x491) & 0xfffffffffffffffd | 2;
    *(char *)(iVar4 + 0x491) = (char)uVar14;
    *(byte *)(iVar4 + 0x490) =
         *(byte *)(iVar4 + 0x490) & 0xfd | (byte)((uint)((uVar14 << 0x3e) >> 0x3f) << 1);
    *(undefined2 *)(iVar4 + 0x494) = 4;
    (**(code **)(*(int *)(iVar4 + 0x488) + 0x24))(0x432d0000,fVar16 + 40.0);
    SetUV__10MenuSpriteFUsUsUsUs(iVar4 + 0x480,0x25,0x1f,0x45,0x43);
    (**(code **)(*(int *)(iVar4 + 0x488) + 0x28))(0x42000000,0x42100000);
    *(byte *)(iVar4 + 0x492) = *(byte *)(iVar4 + 0x492) & 0xfe | 1;
    *(undefined2 *)(iVar4 + 0x49c) = 0;
    *(undefined2 *)(iVar4 + 0x49e) = 8;
    AddPlace__10MenuWindowFP9MenuPlace(iStack_40 + iStack_30 * 0x16c + 0x7c,iVar4 + 0x480);
  }
  if ((uStack_10 == 2) && (acStack_60[2] != '\0')) {
    (**(code **)(*(int *)(iVar4 + 0x488) + 0x30))(iVar4 + 0x480,0x40,0x80,0x60);
    (**(code **)(*(int *)(iVar4 + 0x488) + 0x2c))(iVar4 + 0x480,0x60);
  }
  else if (acStack_60[2] == '\0') {
    (**(code **)(*(int *)(iVar4 + 0x488) + 0x30))(iVar4 + 0x480,0x80,0x40,0x10);
    (**(code **)(*(int *)(iVar4 + 0x488) + 0x2c))(iVar4 + 0x480,0x20);
  }
  else {
    (**(code **)(*(int *)(iVar4 + 0x488) + 0x30))(iVar4 + 0x480,0x80,0x40,0x10);
    (**(code **)(*(int *)(iVar4 + 0x488) + 0x2c))(iVar4 + 0x480,0x40);
  }
  if (iStack_48 != 0) {
    Create__10MenuSpriteFUc(iVar4 + 0x4e0,1);
    *(byte *)(iVar4 + 0x501) = *(byte *)(iVar4 + 0x501) & 0xbf | 0x40;
    uVar14 = (ulong)*(byte *)(iVar4 + 0x4f1) & 0xfffffffffffffffd | 2;
    *(char *)(iVar4 + 0x4f1) = (char)uVar14;
    *(byte *)(iVar4 + 0x4f0) =
         *(byte *)(iVar4 + 0x4f0) & 0xfd | (byte)((uint)((uVar14 << 0x3e) >> 0x3f) << 1);
    *(undefined2 *)(iVar4 + 0x4f4) = 4;
    (**(code **)(*(int *)(iVar4 + 0x4e8) + 0x24))(0x43998000,fVar16 + 40.0);
    SetUV__10MenuSpriteFUsUsUsUs(iVar4 + 0x4e0,0x25,0x1f,0x45,0x43);
    (**(code **)(*(int *)(iVar4 + 0x4e8) + 0x28))(0x42000000,0x42100000);
    *(byte *)(iVar4 + 0x4f2) = *(byte *)(iVar4 + 0x4f2) & 0xfe | 1;
    *(undefined2 *)(iVar4 + 0x4fc) = 0;
    *(undefined2 *)(iVar4 + 0x4fe) = 9;
    AddPlace__10MenuWindowFP9MenuPlace(iStack_40 + iStack_30 * 0x16c + 0x7c,iVar4 + 0x4e0);
  }
  if ((uStack_10 == 3) && (acStack_60[3] != '\0')) {
    (**(code **)(*(int *)(iVar4 + 0x4e8) + 0x30))(iVar4 + 0x4e0,0x40,0x80,0x60);
    (**(code **)(*(int *)(iVar4 + 0x4e8) + 0x2c))(iVar4 + 0x4e0,0x60);
  }
  else if (acStack_60[3] == '\0') {
    uVar9 = (**(code **)(*(int *)(iVar4 + 0x4e8) + 0x30))(iVar4 + 0x4e0,0x80,0x40,0x10);
    (**(code **)(*(int *)(iVar4 + 0x4e8) + 0x2c))(iVar4 + 0x4e0,0x20,uVar9);
  }
  else {
    (**(code **)(*(int *)(iVar4 + 0x4e8) + 0x30))(iVar4 + 0x4e0,0x80,0x40,0x10);
    (**(code **)(*(int *)(iVar4 + 0x4e8) + 0x2c))(iVar4 + 0x4e0,0x40);
  }
  uVar15 = 10;
  if (iStack_48 != 0) {
    uVar7 = *(undefined4 *)
             (*(int *)&pCGpffff86b4->field_0x4248 +
              (uint)*(ushort *)(*(int *)&pCGpffff86b4->field_0x4248 + 10) * 4 + 0xc);
    uVar9 = GetTex0__6JRCTexFb(*(undefined4 *)&pCGpffff86b4->field_0x4248,0);
    Create__11SendOnLocalFP4_QWDUl(iVar11 + iStack_4c * 0x30,uVar7,uVar9);
    *(undefined2 *)(iVar11 + iStack_4c * 0x30 + 0x14) = 5;
    AddPriority__12MenuObjTableFP7MenuObj(iStack_40 + iStack_30 * 0x16c + 0x94,iVar11 + iStack_4c * 0x30);
    Create__10MenuSpriteFUc(iVar4 + 0x540,1);
    *(byte *)(iVar4 + 0x561) = *(byte *)(iVar4 + 0x561) & 0xbf | 0x40;
    uVar14 = (ulong)*(byte *)(iVar4 + 0x551) & 0xfffffffffffffffd | 2;
    *(char *)(iVar4 + 0x551) = (char)uVar14;
    *(byte *)(iVar4 + 0x550) =
         *(byte *)(iVar4 + 0x550) & 0xfd | (byte)((uint)((uVar14 << 0x3e) >> 0x3f) << 1);
    *(undefined2 *)(iVar4 + 0x554) = 6;
    (**(code **)(*(int *)(iVar4 + 0x548) + 0x24))(0x43470000,fVar16 + 16.0);
    (**(code **)(*(int *)(iVar4 + 0x548) + 0x28))(0x41900000,0x41b00000);
    (**(code **)(*(int *)(iVar4 + 0x548) + 0x2c))(iVar4 + 0x540,0x80);
    *(undefined2 *)(iVar4 + 0x55c) = 0;
    *(undefined2 *)(iVar4 + 0x55e) = 10;
    AddPlace__10MenuWindowFP9MenuPlace(iStack_40 + iStack_30 * 0x16c + 0x7c,iVar4 + 0x540);
    Create__10MenuSpriteFUc(iVar4 + 0x5a0,1);
    *(byte *)(iVar4 + 0x5c1) = *(byte *)(iVar4 + 0x5c1) & 0xbf | 0x40;
    uVar14 = (ulong)*(byte *)(iVar4 + 0x5b1) & 0xfffffffffffffffd | 2;
    *(char *)(iVar4 + 0x5b1) = (char)uVar14;
    *(byte *)(iVar4 + 0x5b0) =
         *(byte *)(iVar4 + 0x5b0) & 0xfd | (byte)((uint)((uVar14 << 0x3e) >> 0x3f) << 1);
    *(undefined2 *)(iVar4 + 0x5b4) = 6;
    (**(code **)(*(int *)(iVar4 + 0x5a8) + 0x24))(0x43938000,fVar16 + 16.0);
    (**(code **)(*(int *)(iVar4 + 0x5a8) + 0x28))(0x41900000,0x41b00000);
    (**(code **)(*(int *)(iVar4 + 0x5a8) + 0x2c))(iVar4 + 0x5a0,0x80);
    *(undefined2 *)(iVar4 + 0x5bc) = 1;
    *(undefined2 *)(iVar4 + 0x5be) = 10;
    AddPlace__10MenuWindowFP9MenuPlace(iStack_40 + iStack_30 * 0x16c + 0x7c,iVar4 + 0x5a0);
    Create__10MenuSpriteFUc(iVar4 + 0x600,1);
    *(byte *)(iVar4 + 0x621) = *(byte *)(iVar4 + 0x621) & 0xbf | 0x40;
    uVar14 = (ulong)*(byte *)(iVar4 + 0x611) & 0xfffffffffffffffd | 2;
    *(char *)(iVar4 + 0x611) = (char)uVar14;
    *(byte *)(iVar4 + 0x610) =
         *(byte *)(iVar4 + 0x610) & 0xfd | (byte)((uint)((uVar14 << 0x3e) >> 0x3f) << 1);
    *(undefined2 *)(iVar4 + 0x614) = 6;
    (**(code **)(*(int *)(iVar4 + 0x608) + 0x24))(0x43340000,fVar16 + 48.0);
    (**(code **)(*(int *)(iVar4 + 0x608) + 0x28))(0x41900000,0x41b00000);
    (**(code **)(*(int *)(iVar4 + 0x608) + 0x2c))(iVar4 + 0x600,0x80);
    *(undefined2 *)(iVar4 + 0x61c) = 2;
    *(undefined2 *)(iVar4 + 0x61e) = 10;
    AddPlace__10MenuWindowFP9MenuPlace(iStack_40 + iStack_30 * 0x16c + 0x7c,iVar4 + 0x600);
    Create__10MenuSpriteFUc(iVar4 + 0x660,1);
    *(byte *)(iVar4 + 0x681) = *(byte *)(iVar4 + 0x681) & 0xbf | 0x40;
    uVar14 = (ulong)*(byte *)(iVar4 + 0x671) & 0xfffffffffffffffd | 2;
    *(char *)(iVar4 + 0x671) = (char)uVar14;
    *(byte *)(iVar4 + 0x670) =
         *(byte *)(iVar4 + 0x670) & 0xfd | (byte)((uint)((uVar14 << 0x3e) >> 0x3f) << 1);
    *(undefined2 *)(iVar4 + 0x674) = 6;
    uVar9 = (**(code **)(*(int *)(iVar4 + 0x668) + 0x24))(0x439d0000,fVar16 + 48.0);
    (**(code **)(*(int *)(iVar4 + 0x668) + 0x28))(0x41900000,0x41b00000,iVar4 + 0x660,uVar9);
    (**(code **)(*(int *)(iVar4 + 0x668) + 0x2c))(iVar4 + 0x660,0x80);
    *(undefined2 *)(iVar4 + 0x67c) = 3;
    *(undefined2 *)(iVar4 + 0x67e) = 10;
    AddPlace__10MenuWindowFP9MenuPlace(iStack_40 + iStack_30 * 0x16c + 0x7c,iVar4 + 0x660);
  }
  for (uVar13 = 0; (int)uVar13 < 4; uVar13 = uVar13 + 1) {
    bVar1 = abStack_64[uVar13];
    if (bVar1 == 4) {
      if (abStack_68[uVar13] == 6) {
        SetUV__10MenuSpriteFUsUsUsUs(iVar4 + (uVar13 + 0xe) * 0x60,0x48,0x16,0x5a,0x2c);
      }
      else {
        SetUV__10MenuSpriteFUsUsUsUs(iVar4 + (uVar13 + 0xe) * 0x60,0x48,0,0x5a,0x16);
      }
    }
    else if (bVar1 == 3) {
      if (abStack_68[uVar13] == 6) {
        SetUV__10MenuSpriteFUsUsUsUs(iVar4 + (uVar13 + 0xe) * 0x60,0x36,0x16,0x48,0x2c);
      }
      else {
        SetUV__10MenuSpriteFUsUsUsUs(iVar4 + (uVar13 + 0xe) * 0x60,0x36,0,0x48,0x16);
      }
    }
    else if (bVar1 == 2) {
      if (abStack_68[uVar13] == 6) {
        SetUV__10MenuSpriteFUsUsUsUs(iVar4 + (uVar13 + 0xe) * 0x60,0x24,0x16,0x36,0x2c);
      }
      else {
        SetUV__10MenuSpriteFUsUsUsUs(iVar4 + (uVar13 + 0xe) * 0x60,0x24,0,0x36,0x16);
      }
    }
    else if (bVar1 == 1) {
      if (abStack_68[uVar13] == 6) {
        SetUV__10MenuSpriteFUsUsUsUs(iVar4 + (uVar13 + 0xe) * 0x60,0x12,0x16,0x24,0x2c);
      }
      else {
        SetUV__10MenuSpriteFUsUsUsUs(iVar4 + (uVar13 + 0xe) * 0x60,0x12,0,0x24,0x16);
      }
    }
    else if (bVar1 == 0) {
      if (abStack_68[uVar13] == 6) {
        SetUV__10MenuSpriteFUsUsUsUs(iVar4 + (uVar13 + 0xe) * 0x60,0,0x16,0x12,0x2c);
      }
      else {
        SetUV__10MenuSpriteFUsUsUsUs(iVar4 + (uVar13 + 0xe) * 0x60,0,0,0x12,0x16);
      }
    }
    if ((uStack_10 == uVar13) && (acStack_60[uVar13] != '\0')) {
      iVar11 = iVar4 + (uVar13 + 0xe) * 0x60;
      (**(code **)(*(int *)(iVar11 + 8) + 0x30))
                (iVar11,*(undefined1 *)((char)abStack_68[uVar13] * 4 + 0x654ea0),
                 *(undefined1 *)((char)abStack_68[uVar13] * 4 + 0x654ea1),
                 *(undefined1 *)((char)abStack_68[uVar13] * 4 + 0x654ea2));
      iVar11 = iVar4 + (uVar13 + 0xe) * 0x60;
      *(byte *)(iVar11 + 0x12) = *(byte *)(iVar11 + 0x12) & 0xfe | 1;
    }
    else if (acStack_60[uVar13] == '\0') {
      iVar11 = iVar4 + (uVar13 + 0xe) * 0x60;
      *(byte *)(iVar11 + 0x12) = *(byte *)(iVar11 + 0x12) & 0xfe;
    }
    else {
      if (uStack_10 == 0xffffffff) {
        iVar11 = iVar4 + (uVar13 + 0xe) * 0x60;
        (**(code **)(*(int *)(iVar11 + 8) + 0x30))
                  (iVar11,*(undefined1 *)((char)abStack_68[uVar13] * 4 + 0x654ea0),
                   *(undefined1 *)((char)abStack_68[uVar13] * 4 + 0x654ea1),
                   *(undefined1 *)((char)abStack_68[uVar13] * 4 + 0x654ea2));
      }
      else {
        iVar11 = iVar4 + (uVar13 + 0xe) * 0x60;
        (**(code **)(*(int *)(iVar11 + 8) + 0x30))
                  (iVar11,(int)(uint)*(byte *)((char)abStack_68[uVar13] * 4 + 0x654ea0) >> 1,
                   (int)(uint)*(byte *)((char)abStack_68[uVar13] * 4 + 0x654ea1) >> 1,
                   (int)(uint)*(byte *)((char)abStack_68[uVar13] * 4 + 0x654ea2) >> 1,2);
      }
      iVar11 = iVar4 + (uVar13 + 0xe) * 0x60;
      *(byte *)(iVar11 + 0x12) = *(byte *)(iVar11 + 0x12) & 0xfe | 1;
    }
  }
  iStack_4c = iStack_4c + 1;
  if (iStack_48 != 0) {
    CreatePacket__10MenuPacketFUs(iVar5 + iStack_50 * 0x28 + 0x18,4);
    SetRegister__12MenuRegisterFiUlUl(iVar5 + iStack_50 * 0x28,0,0x42,0x44);
    *(undefined2 *)(iVar5 + iStack_50 * 0x28 + 0x14) = 7;
    AddPriority__12MenuObjTableFP7MenuObj(iStack_40 + iStack_30 * 0x16c + 0x94,iVar5 + iStack_50 * 0x28);
    *(undefined2 *)(iStack_40 + iStack_30 * 0x16c + 0x50) = 7;
    AddPriority__12MenuObjTableFP7MenuObj(iStack_40 + iStack_30 * 0x16c + 0x94,iStack_40 + iStack_30 * 0x16c + 0x3c);
  }
  iStack_50 = iStack_50 + 1;
  for (uVar13 = 0; (int)uVar13 < 4; uVar13 = uVar13 + 1) {
    if (uVar13 == 3) {
      uStack_54 = 1;
      uVar15 = 0x15;
      fStack_74 = 339.0;
      fStack_78 = fVar16 + 48.0;
    }
    else if (uVar13 == 2) {
      uStack_54 = 0;
      uVar15 = 0x15;
      fStack_74 = 173.0;
      fStack_78 = fVar16 + 48.0;
    }
    else if (uVar13 == 1) {
      uStack_54 = 1;
      uVar15 = 0x14;
      fStack_74 = 320.0;
      fStack_78 = fVar16 + 16.0;
    }
    else if (uVar13 == 0) {
      uStack_54 = 0;
      uVar15 = 0x14;
      fStack_74 = 192.0;
      fStack_78 = fVar16 + 16.0;
    }
    if (iStack_48 != 0) {
      Create__8MenuTextFUcUc(iVar3 + iVar12 * 0x80,1,2);
      *(undefined1 *)(iVar3 + iVar12 * 0x80 + 0x5a) = 1;
      *(undefined1 *)(iVar3 + iVar12 * 0x80 + 0x5b) = 0;
      *(undefined2 *)(iVar3 + iVar12 * 0x80 + 0x14) = 8;
      *(short *)(iVar3 + iVar12 * 0x80 + 0x1c) = (short)uStack_54;
      *(undefined2 *)(iVar3 + iVar12 * 0x80 + 0x1e) = uVar15;
      AddPlace__10MenuWindowFP9MenuPlace(iStack_40 + iStack_30 * 0x16c + 0x7c,iVar3 + iVar12 * 0x80);
    }
    cVar2 = *(char *)(iStack_88 + uVar13 * 4);
    if (cVar2 == '\x03') {
      if ((pCGpffff86b4->aChr[iStack_20].bFlagsB & 1) == 0) {
        if ((pCGpffff86b4->aChr[iStack_20].bFlagsA1 & 1) == 0) {
          iStack_44 = (int)pCGpffff86b4->aChr[iStack_20].nCharId;
        }
        else {
          switch(pCGpffff86b4->aChr[iStack_20].nSubId) {
          case 0:
          case 1:
            iStack_44 = 0xc;
            break;
          case 2:
          case 3:
            iStack_44 = 0xd;
            break;
          case 4:
          case 5:
            iStack_44 = 0xe;
            break;
          case 6:
          case 7:
            iStack_44 = 0xf;
            break;
          case 8:
          case 9:
            iStack_44 = 0x10;
            break;
          case 10:
          case 0xb:
            iStack_44 = 0x11;
            break;
          case 0xc:
          case 0xd:
            iStack_44 = 0x12;
            break;
          case 0xe:
            iStack_44 = 0x13;
            break;
          case 0xf:
            iStack_44 = 0x14;
            break;
          case 0x10:
            iStack_44 = 0x15;
          }
        }
        GetRegDat__9RegDatApiFiii(0x36,iStack_44,0xffffffffffffffff);
        uStack_6c = GetRegDat__9RegDatApiFiii(0xc,iStack_44,*(undefined2 *)(iStack_88 + uVar13 * 4 + 2));
      }
      else {
        GetRegDat__9RegDatApiFiii(0x36,0x17,0xffffffffffffffff);
        uStack_6c = GetRegDat__9RegDatApiFiii(0xc,0x17,*(undefined2 *)(iStack_88 + uVar13 * 4 + 2));
      }
      if (acStack_60[uVar13] == '\0') {
        *(undefined2 *)(iVar3 + iVar12 * 0x80 + 0x16) = 0;
      }
      else {
        *(undefined2 *)(iVar3 + iVar12 * 0x80 + 0x16) = 1;
      }
      if (uVar13 == uStack_10) {
        SetCSA__8FontItemFUc(iVar3 + iVar12 * 0x80,1);
        *(undefined1 *)(iVar3 + iVar12 * 0x80 + 0x5c) = 0;
        iVar11 = iVar3 + iVar12 * 0x80;
        uVar14 = (ulong)*(byte *)(iVar11 + 0x11) & 0xfffffffffffffffd | 2;
        *(char *)(iVar11 + 0x11) = (char)uVar14;
        iVar11 = iVar3 + iVar12 * 0x80;
        *(byte *)(iVar11 + 0x10) =
             *(byte *)(iVar11 + 0x10) & 0xfd | (byte)((uint)((uVar14 << 0x3e) >> 0x3f) << 1);
        iVar11 = iVar3 + iVar12 * 0x80;
        (**(code **)(*(int *)(iVar11 + 8) + 0x2c))(iVar11,0x80);
      }
      else {
        SetCSA__8FontItemFUc(iVar3 + iVar12 * 0x80,0);
        *(undefined1 *)(iVar3 + iVar12 * 0x80 + 0x5c) = 0xc;
        iVar11 = iVar3 + iVar12 * 0x80;
        uVar14 = (ulong)*(byte *)(iVar11 + 0x11) & 0xfffffffffffffffd | 2;
        *(char *)(iVar11 + 0x11) = (char)uVar14;
        iVar11 = iVar3 + iVar12 * 0x80;
        *(byte *)(iVar11 + 0x10) =
             *(byte *)(iVar11 + 0x10) & 0xfd | (byte)((uint)((uVar14 << 0x3e) >> 0x3f) << 1);
        if ((uStack_10 == 0xffffffff) && (acStack_60[uVar13] != '\0')) {
          iVar11 = iVar3 + iVar12 * 0x80;
          (**(code **)(*(int *)(iVar11 + 8) + 0x2c))(iVar11,0x80);
        }
        else {
          iVar11 = iVar3 + iVar12 * 0x80;
          (**(code **)(*(int *)(iVar11 + 8) + 0x2c))(iVar11,0x40);
        }
      }
      SetMessage__8MenuTextFPcUiUcUc(iVar3 + iVar12 * 0x80,uStack_6c,0,0,1);
      iVar11 = iVar3 + iVar12 * 0x80;
      *(byte *)(iVar11 + 0x12) = *(byte *)(iVar11 + 0x12) & 0xfe | 1;
      OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_40 + iStack_30 * 0x16c + 0x3c,iVar3 + iVar12 * 0x80,1,0);
      if ((uVar13 & 1) == 0) {
        (**(code **)(*(int *)(iVar3 + iVar12 * 0x80 + 8) + 0x24))
                  (fStack_74 - *(float *)(iVar3 + iVar12 * 0x80 + 0x2c),fStack_78);
      }
      else {
        (**(code **)(*(int *)(iVar3 + iVar12 * 0x80 + 8) + 0x24))(fStack_74,fStack_78);
      }
    }
    else if (cVar2 == '\x02') {
      GetRegDat__9RegDatApiFiii(0x38,0,0xffffffffffffffff);
      uVar7 = GetRegDat__9RegDatApiFiii(0xe,*(undefined2 *)(iStack_88 + uVar13 * 4 + 2),0xffffffffffffffff);
      if (acStack_60[uVar13] == '\0') {
        *(undefined2 *)(iVar3 + iVar12 * 0x80 + 0x16) = 0;
      }
      else {
        *(undefined2 *)(iVar3 + iVar12 * 0x80 + 0x16) = 1;
      }
      if (uVar13 == uStack_10) {
        SetCSA__8FontItemFUc(iVar3 + iVar12 * 0x80,1);
        *(undefined1 *)(iVar3 + iVar12 * 0x80 + 0x5c) = 0;
        iVar11 = iVar3 + iVar12 * 0x80;
        *(byte *)(iVar11 + 0x11) = *(byte *)(iVar11 + 0x11) & 0xfd | 2;
        iVar11 = iVar3 + iVar12 * 0x80;
        *(byte *)(iVar11 + 0x10) = *(byte *)(iVar11 + 0x10) & 0xfd | 2;
        iVar11 = iVar3 + iVar12 * 0x80;
        (**(code **)(*(int *)(iVar11 + 8) + 0x2c))(iVar11,0x80);
      }
      else {
        SetCSA__8FontItemFUc(iVar3 + iVar12 * 0x80,0);
        *(undefined1 *)(iVar3 + iVar12 * 0x80 + 0x5c) = 4;
        iVar11 = iVar3 + iVar12 * 0x80;
        *(byte *)(iVar11 + 0x11) = *(byte *)(iVar11 + 0x11) & 0xfd | 2;
        iVar11 = iVar3 + iVar12 * 0x80;
        *(byte *)(iVar11 + 0x10) = *(byte *)(iVar11 + 0x10) & 0xfd | 2;
        if ((uStack_10 == 0xffffffff) && (acStack_60[uVar13] != '\0')) {
          iVar11 = iVar3 + iVar12 * 0x80;
          (**(code **)(*(int *)(iVar11 + 8) + 0x2c))(iVar11,0x80);
        }
        else {
          iVar11 = iVar3 + iVar12 * 0x80;
          (**(code **)(*(int *)(iVar11 + 8) + 0x2c))(iVar11,0x40);
        }
      }
      SetMessage__8MenuTextFPcUiUcUc(iVar3 + iVar12 * 0x80,uVar7,0,0,1);
      iVar11 = iVar3 + iVar12 * 0x80;
      *(byte *)(iVar11 + 0x12) = *(byte *)(iVar11 + 0x12) & 0xfe | 1;
      uVar9 = OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_40 + iStack_30 * 0x16c + 0x3c,iVar3 + iVar12 * 0x80,1,0);
      if ((uVar13 & 1) == 0) {
        iVar11 = iVar3 + iVar12 * 0x80;
        (**(code **)(*(int *)(iVar11 + 8) + 0x24))
                  (fStack_74 - *(float *)(iVar3 + iVar12 * 0x80 + 0x2c),fStack_78,iVar11,
                   iVar12 * 0x80,uVar9);
      }
      else {
        (**(code **)(*(int *)(iVar3 + iVar12 * 0x80 + 8) + 0x24))(fStack_74,fStack_78);
      }
    }
    else if (cVar2 == '\x01') {
      GetRegDat__9RegDatApiFiii(0x33,0,0xffffffffffffffff);
      uVar7 = GetRegDat__9RegDatApiFiii(9,*(undefined2 *)(iStack_88 + uVar13 * 4 + 2),0xffffffffffffffff);
      if (acStack_60[uVar13] == '\0') {
        *(undefined2 *)(iVar3 + iVar12 * 0x80 + 0x16) = 0;
      }
      else {
        *(undefined2 *)(iVar3 + iVar12 * 0x80 + 0x16) = 1;
      }
      if (uVar13 == uStack_10) {
        SetCSA__8FontItemFUc(iVar3 + iVar12 * 0x80,1);
        *(undefined1 *)(iVar3 + iVar12 * 0x80 + 0x5c) = 0;
        iVar11 = iVar3 + iVar12 * 0x80;
        uVar14 = (ulong)*(byte *)(iVar11 + 0x11) & 0xfffffffffffffffd | 2;
        *(char *)(iVar11 + 0x11) = (char)uVar14;
        iVar11 = iVar3 + iVar12 * 0x80;
        *(byte *)(iVar11 + 0x10) =
             *(byte *)(iVar11 + 0x10) & 0xfd | (byte)((uint)((uVar14 << 0x3e) >> 0x3f) << 1);
        iVar11 = iVar3 + iVar12 * 0x80;
        (**(code **)(*(int *)(iVar11 + 8) + 0x2c))(iVar11,0x80);
      }
      else {
        SetCSA__8FontItemFUc(iVar3 + iVar12 * 0x80,1);
        *(undefined1 *)(iVar3 + iVar12 * 0x80 + 0x5c) = 4;
        iVar11 = iVar3 + iVar12 * 0x80;
        uVar14 = (ulong)*(byte *)(iVar11 + 0x11) & 0xfffffffffffffffd | 2;
        *(char *)(iVar11 + 0x11) = (char)uVar14;
        iVar11 = iVar3 + iVar12 * 0x80;
        *(byte *)(iVar11 + 0x10) =
             *(byte *)(iVar11 + 0x10) & 0xfd | (byte)((uint)((uVar14 << 0x3e) >> 0x3f) << 1);
        if ((uStack_10 == 0xffffffff) && (acStack_60[uVar13] != '\0')) {
          iVar11 = iVar3 + iVar12 * 0x80;
          (**(code **)(*(int *)(iVar11 + 8) + 0x2c))(iVar11,0x80);
        }
        else {
          iVar11 = iVar3 + iVar12 * 0x80;
          (**(code **)(*(int *)(iVar11 + 8) + 0x2c))(iVar11,0x40);
        }
      }
      SetMessage__8MenuTextFPcUiUcUc(iVar3 + iVar12 * 0x80,uVar7,0,0,1);
      iVar11 = iVar3 + iVar12 * 0x80;
      *(byte *)(iVar11 + 0x12) = *(byte *)(iVar11 + 0x12) & 0xfe | 1;
      OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_40 + iStack_30 * 0x16c + 0x3c,iVar3 + iVar12 * 0x80,1,0);
      if ((uVar13 & 1) == 0) {
        (**(code **)(*(int *)(iVar3 + iVar12 * 0x80 + 8) + 0x24))
                  (fStack_74 - *(float *)(iVar3 + iVar12 * 0x80 + 0x2c),fStack_78);
      }
      else {
        (**(code **)(*(int *)(iVar3 + iVar12 * 0x80 + 8) + 0x24))(fStack_74,fStack_78);
      }
    }
    else if (cVar2 == '\0') {
      *(undefined2 *)(iVar3 + iVar12 * 0x80 + 0x16) = 1;
      if (uVar13 == uStack_10) {
        SetCSA__8FontItemFUc(iVar3 + iVar12 * 0x80,1);
        *(undefined1 *)(iVar3 + iVar12 * 0x80 + 0x5c) = 0;
        iVar11 = iVar3 + iVar12 * 0x80;
        *(byte *)(iVar11 + 0x11) = *(byte *)(iVar11 + 0x11) & 0xfd | 2;
        iVar11 = iVar3 + iVar12 * 0x80;
        *(byte *)(iVar11 + 0x10) = *(byte *)(iVar11 + 0x10) & 0xfd | 2;
        iVar11 = iVar3 + iVar12 * 0x80;
        (**(code **)(*(int *)(iVar11 + 8) + 0x2c))(iVar11,0x80);
      }
      else {
        SetCSA__8FontItemFUc(iVar3 + iVar12 * 0x80,0);
        *(undefined1 *)(iVar3 + iVar12 * 0x80 + 0x5c) = 0;
        iVar11 = iVar3 + iVar12 * 0x80;
        *(byte *)(iVar11 + 0x11) = *(byte *)(iVar11 + 0x11) & 0xfd | 2;
        iVar11 = iVar3 + iVar12 * 0x80;
        *(byte *)(iVar11 + 0x10) = *(byte *)(iVar11 + 0x10) & 0xfd | 2;
        if (uStack_10 == 0xffffffff) {
          iVar11 = iVar3 + iVar12 * 0x80;
          (**(code **)(*(int *)(iVar11 + 8) + 0x2c))(iVar11,0x80);
        }
        else {
          iVar11 = iVar3 + iVar12 * 0x80;
          (**(code **)(*(int *)(iVar11 + 8) + 0x2c))(iVar11,0x40);
        }
      }
      SetMessage__8MenuTextFPcUiUcUc(iVar3 + iVar12 * 0x80,puRam0040ab20[1],0,0,1);
      iVar11 = iVar3 + iVar12 * 0x80;
      *(byte *)(iVar11 + 0x12) = *(byte *)(iVar11 + 0x12) & 0xfe | 1;
      OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_40 + iStack_30 * 0x16c + 0x3c,iVar3 + iVar12 * 0x80,1,0);
      if ((uVar13 & 1) == 0) {
        (**(code **)(*(int *)(iVar3 + iVar12 * 0x80 + 8) + 0x24))
                  (fStack_74 - *(float *)(iVar3 + iVar12 * 0x80 + 0x2c),fStack_78);
      }
      else {
        (**(code **)(*(int *)(iVar3 + iVar12 * 0x80 + 8) + 0x24))(fStack_74,fStack_78);
      }
    }
    else {
      *(undefined2 *)(iVar3 + iVar12 * 0x80 + 0x16) = 0;
      SetCSA__8FontItemFUc(iVar3 + iVar12 * 0x80,2);
      *(undefined1 *)(iVar3 + iVar12 * 0x80 + 0x5c) = 0;
      iVar11 = iVar3 + iVar12 * 0x80;
      uVar14 = (ulong)*(byte *)(iVar11 + 0x11) & 0xfffffffffffffffd | 2;
      *(char *)(iVar11 + 0x11) = (char)uVar14;
      iVar11 = iVar3 + iVar12 * 0x80;
      *(byte *)(iVar11 + 0x10) =
           *(byte *)(iVar11 + 0x10) & 0xfd | (byte)((uint)((uVar14 << 0x3e) >> 0x3f) << 1);
      iVar11 = iVar3 + iVar12 * 0x80;
      (**(code **)(*(int *)(iVar11 + 8) + 0x2c))(iVar11,0x40);
      SetMessage__8MenuTextFPcUiUcUc(iVar3 + iVar12 * 0x80,*puRam0040ab20,0,0,1);
      iVar11 = iVar3 + iVar12 * 0x80;
      *(byte *)(iVar11 + 0x12) = *(byte *)(iVar11 + 0x12) & 0xfe | 1;
      OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_40 + iStack_30 * 0x16c + 0x3c,iVar3 + iVar12 * 0x80,1,0);
      if ((uVar13 & 1) == 0) {
        (**(code **)(*(int *)(iVar3 + iVar12 * 0x80 + 8) + 0x24))
                  (fStack_74 - *(float *)(iVar3 + iVar12 * 0x80 + 0x2c),fStack_78);
      }
      else {
        (**(code **)(*(int *)(iVar3 + iVar12 * 0x80 + 8) + 0x24))(fStack_74,fStack_78);
      }
    }
    iVar12 = iVar12 + 1;
  }
  if (*(short *)(iStack_40 + 0xa32) == 1) {
    *(undefined2 *)(iStack_40 + 0xa32) = 2;
  }
  if (iStack_48 != 0) {
    Open__10MenuWindowFUci(iStack_40 + iStack_30 * 0x16c + 0x7c,0,0x85);
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005cf220  SetTutorialMenu__7BtlMenuFii
 * C++: BtlMenu::SetTutorialMenu(int, int)
 * size: 0x24ec bytes
 * --------------------------------------------------------------------------- */
void SetTutorialMenu__7BtlMenuFii(int param_1,int param_2,int param_3)

{
  bool bVar1;
  undefined4 uVar2;
  ulong uVar3;
  undefined8 uVar4;
  int iVar5;
  int iVar6;
  float fVar7;
  float fVar8;
  float fStack_3c;
  
  bVar1 = *(short *)(param_1 + param_2 * 0x16c + 0x32) == 0;
  if (bVar1) {
    *(undefined2 *)(param_1 + param_2 * 0x16c + 0x32) = 1;
    *(undefined2 *)(param_1 + param_2 * 0x16c + 0x34) = 0;
    *(undefined2 *)(param_1 + param_2 * 0x16c + 0x36) = 0;
    *(undefined4 *)(param_1 + param_2 * 0x16c + 0x38) = 0;
    *(undefined2 *)(param_1 + param_2 * 0x16c + 0x90) = 8;
    AddOT__7MenuObjFv(param_1 + param_2 * 0x16c + 0x7c);
    iVar6 = param_1 + param_2 * 0x16c;
    *(byte *)(iVar6 + 0x30) = *(byte *)(iVar6 + 0x30) & 0xfb | 4;
    Create__10MenuWindowFUcUcffff(0,0,0x44000000,0x43e00000,param_1 + param_2 * 0x16c + 0x7c,6,1);
    iVar6 = param_1 + param_2 * 0x16c;
    *(byte *)(iVar6 + 0x30) = *(byte *)(iVar6 + 0x30) & 0xf7 | 8;
    Create__8FontDrawF6GS_PSMUsUsUcUiP10ClutRaster(param_1 + param_2 * 0x16c + 0x3c,0x2c,0x280,0x200,0,0,0);
    iVar6 = param_1 + param_2 * 0x16c;
    *(byte *)(iVar6 + 0x30) = *(byte *)(iVar6 + 0x30) & 0xfd | 2;
    *(undefined2 *)(param_1 + param_2 * 0x16c + 0x50) = 0;
    AddPriority__12MenuObjTableFP7MenuObj(param_1 + param_2 * 0x16c + 0x94,param_1 + param_2 * 0x16c + 0x3c);
    *(undefined4 *)(param_1 + param_2 * 0x16c + 0x178) = 0;
  }
  fVar7 = *(float *)(iRam0040ab1c + 4);
  fVar8 = *(float *)(iRam0040ab1c + 4);
  switch(param_3) {
  case 0:
  case 0x13:
    if (((ulong)*(ushort *)(param_1 + param_2 * 0x16c + 0x30) & 0xfff) >> 4 == 0) {
      uVar4 = __nwa__FUi(400);
      uVar2 = __construct_new_array(uVar4,0x27bfd0,0x27c030,0x80,3);
      *(undefined4 *)(param_1 + param_2 * 0x16c + 0x130) = uVar2;
      iVar6 = param_1 + param_2 * 0x16c;
      *(ushort *)(iVar6 + 0x30) = *(ushort *)(iVar6 + 0x30) & 0xf00f | 0x30;
    }
    iVar6 = *(int *)(param_1 + param_2 * 0x16c + 0x130);
    if (bVar1) {
      SetPosition__10MenuWindowFff(0x42b00000,0x43380000,param_1 + param_2 * 0x16c + 0x7c);
      SetSize__10MenuWindowFff(0x43a80000,0x42a00000,param_1 + param_2 * 0x16c + 0x7c);
      Create__8MenuTextFUcUc(iVar6,1,2);
      (**(code **)(*(int *)(iVar6 + 8) + 0x24))(0,0);
      *(undefined1 *)(iVar6 + 0x5a) = 0;
      *(undefined1 *)(iVar6 + 0x5b) = 0;
      *(undefined2 *)(iVar6 + 0x1c) = 0;
      *(undefined2 *)(iVar6 + 0x1e) = 0;
      SetCSA__8FontItemFUc(iVar6,0);
      *(undefined1 *)(iVar6 + 0x5c) = 0;
      uVar3 = (ulong)*(byte *)(iVar6 + 0x11) & 0xfffffffffffffffd | 2;
      *(char *)(iVar6 + 0x11) = (char)uVar3;
      *(byte *)(iVar6 + 0x10) =
           *(byte *)(iVar6 + 0x10) & 0xfd | (byte)((uint)((uVar3 << 0x3e) >> 0x3f) << 1);
      *(byte *)(iVar6 + 0x21) = *(byte *)(iVar6 + 0x21) & 0xfd;
      *(byte *)(iVar6 + 0x12) = *(byte *)(iVar6 + 0x12) & 0xfe | 1;
      *(undefined2 *)(iVar6 + 0x14) = 1;
      AddPlace__10MenuWindowFP9MenuPlace(param_1 + param_2 * 0x16c + 0x7c,iVar6);
      Create__8MenuTextFUcUc(iVar6 + 0x80,1,2);
      *(undefined2 *)(iVar6 + 0x96) = 0;
      (**(code **)(*(int *)(iVar6 + 0x88) + 0x24))(0x43100000,0x42200000);
      *(undefined1 *)(iVar6 + 0xda) = 0;
      *(undefined1 *)(iVar6 + 0xdb) = 0;
      *(undefined2 *)(iVar6 + 0x9c) = 0;
      *(undefined2 *)(iVar6 + 0x9e) = 1;
      SetCSA__8FontItemFUc(iVar6 + 0x80,0);
      *(undefined1 *)(iVar6 + 0xdc) = 0;
      uVar3 = (ulong)*(byte *)(iVar6 + 0x91) & 0xfffffffffffffffd | 2;
      *(char *)(iVar6 + 0x91) = (char)uVar3;
      *(byte *)(iVar6 + 0x90) =
           *(byte *)(iVar6 + 0x90) & 0xfd | (byte)((uint)((uVar3 << 0x3e) >> 0x3f) << 1);
      *(byte *)(iVar6 + 0xa1) = *(byte *)(iVar6 + 0xa1) & 0xfd | 2;
      *(byte *)(iVar6 + 0x92) = *(byte *)(iVar6 + 0x92) & 0xfe | 1;
      *(undefined2 *)(iVar6 + 0x94) = 1;
      AddPlace__10MenuWindowFP9MenuPlace(param_1 + param_2 * 0x16c + 0x7c,iVar6 + 0x80);
      Create__8MenuTextFUcUc(iVar6 + 0x100,1,2);
      *(undefined2 *)(iVar6 + 0x116) = 1;
      (**(code **)(*(int *)(iVar6 + 0x108) + 0x24))(0x43100000,0x42700000);
      *(undefined1 *)(iVar6 + 0x15a) = 0;
      *(undefined1 *)(iVar6 + 0x15b) = 0;
      *(undefined2 *)(iVar6 + 0x11c) = 0;
      *(undefined2 *)(iVar6 + 0x11e) = 2;
      SetCSA__8FontItemFUc(iVar6 + 0x100,0);
      *(undefined1 *)(iVar6 + 0x15c) = 0;
      uVar3 = (ulong)*(byte *)(iVar6 + 0x111) & 0xfffffffffffffffd | 2;
      *(char *)(iVar6 + 0x111) = (char)uVar3;
      *(byte *)(iVar6 + 0x110) =
           *(byte *)(iVar6 + 0x110) & 0xfd | (byte)((uint)((uVar3 << 0x3e) >> 0x3f) << 1);
      *(byte *)(iVar6 + 0x121) = *(byte *)(iVar6 + 0x121) & 0xfd | 2;
      *(byte *)(iVar6 + 0x112) = *(byte *)(iVar6 + 0x112) & 0xfe | 1;
      *(undefined2 *)(iVar6 + 0x114) = 1;
      AddPlace__10MenuWindowFP9MenuPlace(param_1 + param_2 * 0x16c + 0x7c,iVar6 + 0x100);
      if (param_3 == 0x13) {
        uVar4 = GetRegDat__9RegDatApiFiii(0x24,0,0xffffffffffffffff);
        SetMessage__8MenuTextFPcUiUcUc(iVar6,uVar4,0,0,1);
        OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(param_1 + param_2 * 0x16c + 0x3c,iVar6,0,0);
        uVar4 = GetRegDat__9RegDatApiFiii(0x24,1,0xffffffffffffffff);
        SetMessage__8MenuTextFPcUiUcUc(iVar6 + 0x80,uVar4,0,0,1);
        OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(param_1 + param_2 * 0x16c + 0x3c,iVar6 + 0x80,0,0);
        uVar4 = GetRegDat__9RegDatApiFiii(0x24,3,0xffffffffffffffff);
        SetMessage__8MenuTextFPcUiUcUc(iVar6 + 0x100,uVar4,0,0,1);
        OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(param_1 + param_2 * 0x16c + 0x3c,iVar6 + 0x100,0,0);
      }
      else if (param_3 == 0) {
        uVar4 = GetRegDat__9RegDatApiFiii(0x23,0,0xffffffffffffffff);
        SetMessage__8MenuTextFPcUiUcUc(iVar6,uVar4,0,0,1);
        OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(param_1 + param_2 * 0x16c + 0x3c,iVar6,0,0);
        uVar4 = GetRegDat__9RegDatApiFiii(0x23,1,0xffffffffffffffff);
        SetMessage__8MenuTextFPcUiUcUc(iVar6 + 0x80,uVar4,0,0,1);
        OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(param_1 + param_2 * 0x16c + 0x3c,iVar6 + 0x80,0,0);
        uVar4 = GetRegDat__9RegDatApiFiii(0x23,3,0xffffffffffffffff);
        SetMessage__8MenuTextFPcUiUcUc(iVar6 + 0x100,uVar4,0,0,1);
        OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(param_1 + param_2 * 0x16c + 0x3c,iVar6 + 0x100,0,0);
      }
      (**(code **)(*(int *)(iVar6 + 8) + 0x24))(168.0 - *(float *)(iVar6 + 0x2c) / 2.0,0);
      fStack_3c = *(float *)(iVar6 + 300);
      if (fStack_3c <= *(float *)(iVar6 + 0xac)) {
        fStack_3c = *(float *)(iVar6 + 0xac);
      }
      (**(code **)(*(int *)(iVar6 + 0x88) + 0x24))(168.0 - fStack_3c / 2.0,0x42200000);
      (**(code **)(*(int *)(iVar6 + 0x108) + 0x24))(168.0 - fStack_3c / 2.0,0x42700000);
    }
    break;
  case 1:
  case 9:
  case 10:
  case 0x14:
  case 0x15:
  case 0x16:
  case 0x17:
  case 0x18:
  case 0x1c:
  case 0x1d:
    if (*(int *)(param_1 + param_2 * 0x16c + 0x134) == 0) {
      uVar4 = __nwa__FUi(0xa8);
      uVar2 = __construct_new_array(uVar4,0x27d490,0x27d4f0,0x98,1);
      *(undefined4 *)(param_1 + param_2 * 0x16c + 0x134) = uVar2;
    }
    iVar6 = *(int *)(param_1 + param_2 * 0x16c + 0x134);
    if (bVar1) {
      SetPosition__10MenuWindowFff(0x42800000,((fVar7 - 128.0) / 2.0 + 128.0) - 30.0,
                      param_1 + param_2 * 0x16c + 0x7c);
      SetSize__10MenuWindowFff(0x43c00000,0x42700000,param_1 + param_2 * 0x16c + 0x7c);
      iVar5 = param_1 + param_2 * 0x16c;
      *(byte *)(iVar5 + 0x31) = *(byte *)(iVar5 + 0x31) & 0xef | 0x10;
      (**(code **)(*(int *)(iVar6 + 8) + 0x60))(iVar6,0x48,2);
      *(undefined2 *)(iVar6 + 0x14) = 1;
      (**(code **)(*(int *)(iVar6 + 8) + 0x24))(0,0);
      *(undefined2 *)(iVar6 + 0x1c) = 0;
      *(undefined2 *)(iVar6 + 0x1e) = 0;
      *(undefined1 *)(iVar6 + 0x5a) = 0;
      *(undefined1 *)(iVar6 + 0x5b) = 0;
      *(byte *)(iVar6 + 0x58) = *(byte *)(iVar6 + 0x58) & 0xf7;
      *(byte *)(iVar6 + 0x12) = *(byte *)(iVar6 + 0x12) & 0xfe | 1;
      AddPlace__10MenuWindowFP9MenuPlace(param_1 + param_2 * 0x16c + 0x7c,iVar6);
      if (param_3 == 0x1d) {
        uVar4 = GetRegDat__9RegDatApiFiii(0x24,0xe,0xffffffffffffffff);
        Order__8FontDrawFP11MenuMessagePc(param_1 + param_2 * 0x16c + 0x3c,iVar6,uVar4);
      }
      else if (param_3 == 0x1c) {
        uVar4 = GetRegDat__9RegDatApiFiii(0x24,0xd,0xffffffffffffffff);
        Order__8FontDrawFP11MenuMessagePc(param_1 + param_2 * 0x16c + 0x3c,iVar6,uVar4);
      }
      else if (param_3 == 0x18) {
        uVar4 = GetRegDat__9RegDatApiFiii(0x24,9,0xffffffffffffffff);
        Order__8FontDrawFP11MenuMessagePc(param_1 + param_2 * 0x16c + 0x3c,iVar6,uVar4);
      }
      else if (param_3 == 0x17) {
        uVar4 = GetRegDat__9RegDatApiFiii(0x24,8,0xffffffffffffffff);
        Order__8FontDrawFP11MenuMessagePc(param_1 + param_2 * 0x16c + 0x3c,iVar6,uVar4);
      }
      else if (param_3 == 0x16) {
        uVar4 = GetRegDat__9RegDatApiFiii(0x24,7,0xffffffffffffffff);
        Order__8FontDrawFP11MenuMessagePc(param_1 + param_2 * 0x16c + 0x3c,iVar6,uVar4);
      }
      else if (param_3 == 0x15) {
        uVar4 = GetRegDat__9RegDatApiFiii(0x24,6,0xffffffffffffffff);
        Order__8FontDrawFP11MenuMessagePc(param_1 + param_2 * 0x16c + 0x3c,iVar6,uVar4);
      }
      else if (param_3 == 0x14) {
        uVar4 = GetRegDat__9RegDatApiFiii(0x24,5,0xffffffffffffffff);
        Order__8FontDrawFP11MenuMessagePc(param_1 + param_2 * 0x16c + 0x3c,iVar6,uVar4);
      }
      else if (param_3 == 10) {
        uVar4 = GetRegDat__9RegDatApiFiii(0x23,0xd,0xffffffffffffffff);
        Order__8FontDrawFP11MenuMessagePc(param_1 + param_2 * 0x16c + 0x3c,iVar6,uVar4);
      }
      else if (param_3 == 9) {
        uVar4 = GetRegDat__9RegDatApiFiii(0x23,0xc,0xffffffffffffffff);
        Order__8FontDrawFP11MenuMessagePc(param_1 + param_2 * 0x16c + 0x3c,iVar6,uVar4);
      }
      else if (param_3 == 1) {
        uVar4 = GetRegDat__9RegDatApiFiii(0x23,5,0xffffffffffffffff);
        Order__8FontDrawFP11MenuMessagePc(param_1 + param_2 * 0x16c + 0x3c,iVar6,uVar4);
      }
    }
    break;
  case 2:
  case 3:
  case 4:
  case 5:
  case 7:
  case 8:
  case 0xb:
  case 0xc:
  case 0xd:
  case 0xe:
  case 0xf:
  case 0x10:
  case 0x11:
  case 0x12:
  case 0x19:
  case 0x1a:
  case 0x1b:
  case 0x1e:
  case 0x1f:
  case 0x20:
  case 0x21:
  case 0x22:
  case 0x23:
  case 0x24:
  case 0x25:
    if (*(int *)(param_1 + param_2 * 0x16c + 0x134) == 0) {
      uVar4 = __nwa__FUi(0xa8);
      uVar2 = __construct_new_array(uVar4,0x27d490,0x27d4f0,0x98,1);
      *(undefined4 *)(param_1 + param_2 * 0x16c + 0x134) = uVar2;
    }
    iVar6 = *(int *)(param_1 + param_2 * 0x16c + 0x134);
    if (bVar1) {
      SetPosition__10MenuWindowFff(0x42800000,(fVar8 + 70.0) - 30.0,param_1 + param_2 * 0x16c + 0x7c);
      SetSize__10MenuWindowFff(0x43c00000,0x42700000,param_1 + param_2 * 0x16c + 0x7c);
      iVar5 = param_1 + param_2 * 0x16c;
      *(byte *)(iVar5 + 0x31) = *(byte *)(iVar5 + 0x31) & 0xef | 0x10;
      (**(code **)(*(int *)(iVar6 + 8) + 0x60))(iVar6,0x48,2);
      *(undefined2 *)(iVar6 + 0x14) = 1;
      (**(code **)(*(int *)(iVar6 + 8) + 0x24))(0,0);
      *(undefined2 *)(iVar6 + 0x1c) = 0;
      *(undefined2 *)(iVar6 + 0x1e) = 0;
      *(undefined1 *)(iVar6 + 0x5a) = 0;
      *(undefined1 *)(iVar6 + 0x5b) = 0;
      *(byte *)(iVar6 + 0x58) = *(byte *)(iVar6 + 0x58) & 0xf7;
      *(byte *)(iVar6 + 0x12) = *(byte *)(iVar6 + 0x12) & 0xfe | 1;
      AddPlace__10MenuWindowFP9MenuPlace(param_1 + param_2 * 0x16c + 0x7c,iVar6);
      if (param_3 == 0x25) {
        uVar4 = GetRegDat__9RegDatApiFiii(0x24,0x16,0xffffffffffffffff);
        Order__8FontDrawFP11MenuMessagePc(param_1 + param_2 * 0x16c + 0x3c,iVar6,uVar4);
      }
      else if (param_3 == 0x24) {
        uVar4 = GetRegDat__9RegDatApiFiii(0x24,0x15,0xffffffffffffffff);
        Order__8FontDrawFP11MenuMessagePc(param_1 + param_2 * 0x16c + 0x3c,iVar6,uVar4);
      }
      else if (param_3 == 0x23) {
        uVar4 = GetRegDat__9RegDatApiFiii(0x24,0x14,0xffffffffffffffff);
        Order__8FontDrawFP11MenuMessagePc(param_1 + param_2 * 0x16c + 0x3c,iVar6,uVar4);
      }
      else if (param_3 == 0x22) {
        uVar4 = GetRegDat__9RegDatApiFiii(0x24,0x13,0xffffffffffffffff);
        Order__8FontDrawFP11MenuMessagePc(param_1 + param_2 * 0x16c + 0x3c,iVar6,uVar4);
      }
      else if (param_3 == 0x21) {
        uVar4 = GetRegDat__9RegDatApiFiii(0x24,0x12,0xffffffffffffffff);
        Order__8FontDrawFP11MenuMessagePc(param_1 + param_2 * 0x16c + 0x3c,iVar6,uVar4);
      }
      else if (param_3 == 0x20) {
        uVar4 = GetRegDat__9RegDatApiFiii(0x24,0x11,0xffffffffffffffff);
        Order__8FontDrawFP11MenuMessagePc(param_1 + param_2 * 0x16c + 0x3c,iVar6,uVar4);
      }
      else if (param_3 == 0x1f) {
        uVar4 = GetRegDat__9RegDatApiFiii(0x24,0x10,0xffffffffffffffff);
        Order__8FontDrawFP11MenuMessagePc(param_1 + param_2 * 0x16c + 0x3c,iVar6,uVar4);
      }
      else if (param_3 == 0x1e) {
        uVar4 = GetRegDat__9RegDatApiFiii(0x24,0xf,0xffffffffffffffff);
        Order__8FontDrawFP11MenuMessagePc(param_1 + param_2 * 0x16c + 0x3c,iVar6,uVar4);
      }
      else if (param_3 == 0x1b) {
        uVar4 = GetRegDat__9RegDatApiFiii(0x24,0xc,0xffffffffffffffff);
        Order__8FontDrawFP11MenuMessagePc(param_1 + param_2 * 0x16c + 0x3c,iVar6,uVar4);
      }
      else if (param_3 == 0x1a) {
        uVar4 = GetRegDat__9RegDatApiFiii(0x24,0xb,0xffffffffffffffff);
        Order__8FontDrawFP11MenuMessagePc(param_1 + param_2 * 0x16c + 0x3c,iVar6,uVar4);
      }
      else if (param_3 == 0x19) {
        uVar4 = GetRegDat__9RegDatApiFiii(0x24,10,0xffffffffffffffff);
        Order__8FontDrawFP11MenuMessagePc(param_1 + param_2 * 0x16c + 0x3c,iVar6,uVar4);
      }
      else if (param_3 == 0x12) {
        uVar4 = GetRegDat__9RegDatApiFiii(0x23,0x15,0xffffffffffffffff);
        Order__8FontDrawFP11MenuMessagePc(param_1 + param_2 * 0x16c + 0x3c,iVar6,uVar4);
      }
      else if (param_3 == 0x11) {
        uVar4 = GetRegDat__9RegDatApiFiii(0x23,0x14,0xffffffffffffffff);
        Order__8FontDrawFP11MenuMessagePc(param_1 + param_2 * 0x16c + 0x3c,iVar6,uVar4);
      }
      else if (param_3 == 0x10) {
        uVar4 = GetRegDat__9RegDatApiFiii(0x23,0x13,0xffffffffffffffff);
        Order__8FontDrawFP11MenuMessagePc(param_1 + param_2 * 0x16c + 0x3c,iVar6,uVar4);
      }
      else if (param_3 == 0xf) {
        uVar4 = GetRegDat__9RegDatApiFiii(0x23,0x12,0xffffffffffffffff);
        Order__8FontDrawFP11MenuMessagePc(param_1 + param_2 * 0x16c + 0x3c,iVar6,uVar4);
      }
      else if (param_3 == 0xe) {
        uVar4 = GetRegDat__9RegDatApiFiii(0x23,0x11,0xffffffffffffffff);
        Order__8FontDrawFP11MenuMessagePc(param_1 + param_2 * 0x16c + 0x3c,iVar6,uVar4);
      }
      else if (param_3 == 0xd) {
        uVar4 = GetRegDat__9RegDatApiFiii(0x23,0x10,0xffffffffffffffff);
        Order__8FontDrawFP11MenuMessagePc(param_1 + param_2 * 0x16c + 0x3c,iVar6,uVar4);
      }
      else if (param_3 == 0xc) {
        uVar4 = GetRegDat__9RegDatApiFiii(0x23,0xf,0xffffffffffffffff);
        Order__8FontDrawFP11MenuMessagePc(param_1 + param_2 * 0x16c + 0x3c,iVar6,uVar4);
      }
      else if (param_3 == 0xb) {
        uVar4 = GetRegDat__9RegDatApiFiii(0x23,0xe,0xffffffffffffffff);
        Order__8FontDrawFP11MenuMessagePc(param_1 + param_2 * 0x16c + 0x3c,iVar6,uVar4);
      }
      else if (param_3 == 8) {
        uVar4 = GetRegDat__9RegDatApiFiii(0x23,0xb,0xffffffffffffffff);
        Order__8FontDrawFP11MenuMessagePc(param_1 + param_2 * 0x16c + 0x3c,iVar6,uVar4);
      }
      else if (param_3 == 7) {
        uVar4 = GetRegDat__9RegDatApiFiii(0x23,10,0xffffffffffffffff);
        Order__8FontDrawFP11MenuMessagePc(param_1 + param_2 * 0x16c + 0x3c,iVar6,uVar4);
      }
      else if (param_3 == 5) {
        uVar4 = GetRegDat__9RegDatApiFiii(0x23,9,0xffffffffffffffff);
        Order__8FontDrawFP11MenuMessagePc(param_1 + param_2 * 0x16c + 0x3c,iVar6,uVar4);
      }
      else if (param_3 == 4) {
        uVar4 = GetRegDat__9RegDatApiFiii(0x23,8,0xffffffffffffffff);
        Order__8FontDrawFP11MenuMessagePc(param_1 + param_2 * 0x16c + 0x3c,iVar6,uVar4);
      }
      else if (param_3 == 3) {
        uVar4 = GetRegDat__9RegDatApiFiii(0x23,7,0xffffffffffffffff);
        Order__8FontDrawFP11MenuMessagePc(param_1 + param_2 * 0x16c + 0x3c,iVar6,uVar4);
      }
      else if (param_3 == 2) {
        uVar4 = GetRegDat__9RegDatApiFiii(0x23,6,0xffffffffffffffff);
        Order__8FontDrawFP11MenuMessagePc(param_1 + param_2 * 0x16c + 0x3c,iVar6,uVar4);
      }
    }
  }
  if (*(short *)(param_1 + 0xa32) == 1) {
    *(undefined2 *)(param_1 + 0xa32) = 2;
  }
  if (bVar1) {
    Open__10MenuWindowFUci(param_1 + param_2 * 0x16c + 0x7c,0,0x85);
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005d1710  CreateMenu1__7BtlMenuFiiiiPsPcPcbb
 * C++: BtlMenu::CreateMenu1(int, int, int, int, short *, char *, char *, bool, bool)
 * size: 0x26fc bytes
 * --------------------------------------------------------------------------- */
void CreateMenu1__7BtlMenuFiiiiPsPcPcbb
               (int param_1,int param_2,int param_3,int param_4,int param_5,int param_6,int param_7,
               int param_8,char param_9,byte param_10)

{
  bool bVar1;
  undefined4 uVar2;
  undefined8 uVar3;
  ulong uVar4;
  long lVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  byte bVar15;
  int iStack_bc;
  int iStack_b8;
  float fStack_98;
  float fStack_94;
  int iStack_60;
  
  bVar1 = false;
  if (*(short *)(param_1 + param_2 * 0x16c + 0x32) == 0) {
    bVar1 = true;
    iVar13 = param_1 + param_2 * 0x16c;
    *(byte *)(iVar13 + 0x31) = *(byte *)(iVar13 + 0x31) & 0xdf | (param_10 & 1) << 5;
    *(undefined2 *)(param_1 + param_2 * 0x16c + 0x32) = 1;
    *(undefined2 *)(param_1 + param_2 * 0x16c + 0x34) = 0;
    *(undefined2 *)(param_1 + param_2 * 0x16c + 0x36) = 0;
    *(undefined4 *)(param_1 + param_2 * 0x16c + 0x38) = 0;
    *(undefined2 *)(param_1 + param_2 * 0x16c + 0x90) = 8;
    AddOT__7MenuObjFv(param_1 + param_2 * 0x16c + 0x7c);
    iVar13 = param_1 + param_2 * 0x16c;
    *(byte *)(iVar13 + 0x30) = *(byte *)(iVar13 + 0x30) & 0xfb | 4;
    Create__10MenuWindowFUcUcffff(*pfRam0040ab1c,pfRam0040ab1c[1],pfRam0040ab1c[2],pfRam0040ab1c[3],
                    param_1 + param_2 * 0x16c + 0x7c,0,1);
    *(undefined4 *)(param_1 + param_2 * 0x16c + 0x178) = 3;
    iVar13 = param_1 + param_2 * 0x16c;
    *(byte *)(iVar13 + 0x30) = *(byte *)(iVar13 + 0x30) & 0xf7 | 8;
    iStack_60 = param_3;
    if (*(int *)(param_1 + param_2 * 0x16c + 0x140) == 0) {
      iStack_b8 = __nw__FUi(0x84);
      if (iStack_b8 != 0) {
        iStack_b8 = __ct__10ScrollMarkFv(iStack_b8);
      }
      *(int *)(param_1 + param_2 * 0x16c + 0x140) = iStack_b8;
      *(undefined2 *)(*(int *)(param_1 + param_2 * 0x16c + 0x140) + 0x14) = 0x10;
      Create__10ScrollMarkFUcP10MenuWindowUc(*(undefined4 *)(param_1 + param_2 * 0x16c + 0x140),0xc,0,0);
      AddPriority__12MenuObjTableFP7MenuObj(param_1 + param_2 * 0x16c + 0x94,
                      *(undefined4 *)(param_1 + param_2 * 0x16c + 0x140));
    }
  }
  else {
    iStack_60 = *(int *)(param_1 + param_2 * 0x16c + 0x16c);
    if (((*(short *)(param_1 + param_2 * 0x16c + 0x32) != 2) &&
        (*(short *)(param_1 + param_2 * 0x16c + 0x32) != 1)) &&
       (*(short *)(param_1 + param_2 * 0x16c + 0x32) != 5)) {
      SetWindowMove__7BtlMenuFii(param_1,param_2,0);
      SetMark__10ScrollMarkFUc(*(undefined4 *)(param_1 + param_2 * 0x16c + 0x140),0);
      if (4 < *(int *)(param_1 + param_2 * 0x16c + 0x170)) {
        if (*(int *)(param_1 + 0xb30) == 0) {
          iStack_bc = __nw__FUi(0x84);
          if (iStack_bc != 0) {
            iStack_bc = __ct__10ScrollMarkFv(iStack_bc);
          }
          *(int *)(param_1 + 0xb30) = iStack_bc;
          Create__10ScrollMarkFUcP10MenuWindowUc(*(undefined4 *)(param_1 + 0xb30),3,0,0);
          *(undefined2 *)(*(int *)(param_1 + 0xb30) + 0x14) = 0x10;
          AddOT__7MenuObjFv(*(undefined4 *)(param_1 + 0xb30));
          *(byte *)(param_1 + 0x25) = *(byte *)(param_1 + 0x25) & 0xfd | 2;
          SetArea__10ScrollMarkFUcffff(*pfRam0040ab1c + 48.0,*(undefined4 *)(param_1 + param_2 * 0x16c + 0x17c),
                          pfRam0040ab1c[2] - 80.0,*(undefined4 *)(param_1 + param_2 * 0x16c + 0x180)
                          ,*(undefined4 *)(param_1 + 0xb30),3);
          *(undefined2 *)(param_1 + 0xa32) = 1;
        }
        if (iStack_60 < 0) {
          iStack_60 = iStack_60 + 3;
        }
        iVar13 = (iStack_60 >> 2) * 4;
        bVar15 = 0 < iVar13;
        if (iVar13 + 4 < *(int *)(param_1 + param_2 * 0x16c + 0x170)) {
          bVar15 = bVar15 | 2;
        }
        SetMark__10ScrollMarkFUc(*(undefined4 *)(param_1 + 0xb30),bVar15);
        return;
      }
      if (*(short *)(param_1 + 0xa32) != 1) {
        return;
      }
      *(undefined2 *)(param_1 + 0xa32) = 2;
      return;
    }
  }
  if (bVar1) {
    Create__8FontDrawF6GS_PSMUsUsUcUiP10ClutRaster(param_1 + param_2 * 0x16c + 0x3c,0x2c,0xc0,0x60,1,0,0);
    iVar13 = param_1 + param_2 * 0x16c;
    *(byte *)(iVar13 + 0x30) = *(byte *)(iVar13 + 0x30) & 0xfd | 2;
    *(undefined2 *)(param_1 + param_2 * 0x16c + 0x50) = 5;
    AddPriority__12MenuObjTableFP7MenuObj(param_1 + param_2 * 0x16c + 0x94,param_1 + param_2 * 0x16c + 0x3c);
    if (((ulong)*(ushort *)(param_1 + param_2 * 0x16c + 0x30) & 0xfff) >> 4 == 0) {
      uVar3 = __nwa__FUi(0x210);
      uVar2 = __construct_new_array(uVar3,0x27bfd0,0x27c030,0x80,4);
      *(undefined4 *)(param_1 + param_2 * 0x16c + 0x130) = uVar2;
      iVar13 = param_1 + param_2 * 0x16c;
      *(ushort *)(iVar13 + 0x30) = *(ushort *)(iVar13 + 0x30) & 0xf00f | 0x40;
    }
    iVar13 = *(int *)(param_1 + param_2 * 0x16c + 0x130);
    iVar10 = 0;
    for (iVar6 = 0; iVar6 < 4; iVar6 = iVar6 + 1) {
      Create__8MenuTextFUcUc(iVar13 + iVar10 * 0x80,0,2);
      *(undefined2 *)(iVar13 + iVar10 * 0x80 + 0x14) = 6;
      *(undefined1 *)(iVar13 + iVar10 * 0x80 + 0x5a) = 1;
      *(undefined1 *)(iVar13 + iVar10 * 0x80 + 0x5b) = 0;
      *(undefined2 *)(iVar13 + iVar10 * 0x80 + 0x1c) = 0;
      *(short *)(iVar13 + iVar10 * 0x80 + 0x1e) = (short)iVar6;
      AddPlace__10MenuWindowFP9MenuPlace(param_1 + param_2 * 0x16c + 0x7c,iVar13 + iVar10 * 0x80);
      iVar10 = iVar10 + 1;
    }
    uVar3 = __nwa__FUi(0x70);
    uVar2 = __construct_new_array(uVar3,0x277820,0x277890,0x30,2);
    *(undefined4 *)(param_1 + param_2 * 0x16c + 0x138) = uVar2;
    uVar2 = *(undefined4 *)
             (*(int *)(iGpffff86b4 + 0x4234) +
              (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x4234) + 10) * 4 + 0xc);
    uVar3 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x4234),0);
    Create__11SendOnLocalFP4_QWDUl(*(undefined4 *)(param_1 + param_2 * 0x16c + 0x138),uVar2,uVar3);
    *(undefined2 *)(*(int *)(param_1 + param_2 * 0x16c + 0x138) + 0x14) = 1;
    AddPriority__12MenuObjTableFP7MenuObj(param_1 + param_2 * 0x16c + 0x94,
                    *(undefined4 *)(param_1 + param_2 * 0x16c + 0x138));
    uVar2 = *(undefined4 *)
             (*(int *)(iGpffff86b4 + 0x4238) +
              (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x4238) + 10) * 4 + 0xc);
    uVar3 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x4238),0);
    Create__11SendOnLocalFP4_QWDUl(*(int *)(param_1 + param_2 * 0x16c + 0x138) + 0x30,uVar2,uVar3);
    *(undefined2 *)(*(int *)(param_1 + param_2 * 0x16c + 0x138) + 0x44) = 3;
    AddPriority__12MenuObjTableFP7MenuObj(param_1 + param_2 * 0x16c + 0x94,
                    *(int *)(param_1 + param_2 * 0x16c + 0x138) + 0x30);
    if (*(int *)(param_1 + param_2 * 0x16c + 0x13c) == 0) {
      uVar3 = __nwa__FUi(0x850);
      uVar2 = __construct_new_array(uVar3,0x266140,0x2661a0,0x60,0x16);
      *(undefined4 *)(param_1 + param_2 * 0x16c + 0x13c) = uVar2;
    }
    iVar10 = *(int *)(param_1 + param_2 * 0x16c + 0x13c);
    iVar14 = 0;
    for (iVar6 = 0; iVar6 < 4; iVar6 = iVar6 + 1) {
      Create__10MenuSpriteFUc(iVar10 + iVar14 * 0x60,0);
      iVar7 = iVar10 + iVar14 * 0x60;
      *(byte *)(iVar7 + 0x21) = *(byte *)(iVar7 + 0x21) & 0xbf | 0x40;
      iVar7 = iVar10 + iVar14 * 0x60;
      uVar4 = (ulong)*(byte *)(iVar7 + 0x11) & 0xfffffffffffffffd | 2;
      *(char *)(iVar7 + 0x11) = (char)uVar4;
      iVar7 = iVar10 + iVar14 * 0x60;
      *(byte *)(iVar7 + 0x10) =
           *(byte *)(iVar7 + 0x10) & 0xfd | (byte)((uint)((uVar4 << 0x3e) >> 0x3f) << 1);
      *(undefined2 *)(iVar10 + iVar14 * 0x60 + 0x14) = 4;
      uVar3 = (**(code **)(*(int *)(iVar10 + iVar14 * 0x60 + 8) + 0x24))(0,(float)iVar6 * 26.0);
      SetUV__10MenuSpriteFUsUsUsUs(iVar10 + iVar14 * 0x60,1,1,0xdd,0x1c,uVar3);
      (**(code **)(*(int *)(iVar10 + iVar14 * 0x60 + 8) + 0x28))(0x435c0000,0x41d80000);
      iVar7 = iVar10 + iVar14 * 0x60;
      (**(code **)(*(int *)(iVar7 + 8) + 0x30))(iVar7,0x80,0x80,0x80);
      iVar7 = iVar10 + iVar14 * 0x60;
      (**(code **)(*(int *)(iVar7 + 8) + 0x2c))(iVar7,0x80);
      iVar7 = iVar10 + iVar14 * 0x60;
      *(byte *)(iVar7 + 0x21) = *(byte *)(iVar7 + 0x21) & 0xfd;
      iVar7 = iVar10 + iVar14 * 0x60;
      *(byte *)(iVar7 + 0x12) = *(byte *)(iVar7 + 0x12) & 0xfe | 1;
      *(undefined2 *)(iVar10 + iVar14 * 0x60 + 0x1c) = 2;
      *(short *)(iVar10 + iVar14 * 0x60 + 0x1e) = (short)iVar6;
      AddPlace__10MenuWindowFP9MenuPlace(param_1 + param_2 * 0x16c + 0x7c,iVar10 + iVar14 * 0x60);
      iVar14 = iVar14 + 1;
    }
    Create__10MenuSpriteFUc(iVar10 + iVar14 * 0x60,0);
    iVar6 = iVar10 + iVar14 * 0x60;
    *(byte *)(iVar6 + 0x21) = *(byte *)(iVar6 + 0x21) & 0xbf | 0x40;
    iVar6 = iVar10 + iVar14 * 0x60;
    uVar4 = (ulong)*(byte *)(iVar6 + 0x11) & 0xfffffffffffffffd | 2;
    *(char *)(iVar6 + 0x11) = (char)uVar4;
    iVar6 = iVar10 + iVar14 * 0x60;
    *(byte *)(iVar6 + 0x10) =
         *(byte *)(iVar6 + 0x10) & 0xfd | (byte)((uint)((uVar4 << 0x3e) >> 0x3f) << 1);
    *(undefined2 *)(iVar10 + iVar14 * 0x60 + 0x14) = 2;
    (**(code **)(*(int *)(iVar10 + iVar14 * 0x60 + 8) + 0x24))(0,0);
    (**(code **)(*(int *)(iVar10 + iVar14 * 0x60 + 8) + 0x28))(0x437f0000,0x41c00000);
    SetUV__10MenuSpriteFUsUsUsUs(iVar10 + iVar14 * 0x60,0,0,0xff,0x18);
    iVar6 = iVar10 + iVar14 * 0x60;
    (**(code **)(*(int *)(iVar6 + 8) + 0x30))(iVar6,0x80,0x80,0x80);
    iVar6 = iVar10 + iVar14 * 0x60;
    (**(code **)(*(int *)(iVar6 + 8) + 0x2c))(iVar6,0);
    iVar6 = iVar10 + iVar14 * 0x60;
    *(byte *)(iVar6 + 0x21) = *(byte *)(iVar6 + 0x21) & 0xfd;
    iVar6 = iVar10 + iVar14 * 0x60;
    *(byte *)(iVar6 + 0x12) = *(byte *)(iVar6 + 0x12) & 0xfe | 1;
    *(undefined2 *)(iVar10 + iVar14 * 0x60 + 0x1c) = 2;
    *(undefined2 *)(iVar10 + iVar14 * 0x60 + 0x1e) = 4;
    AddPlace__10MenuWindowFP9MenuPlace(param_1 + param_2 * 0x16c + 0x7c,iVar10 + iVar14 * 0x60);
    for (iVar6 = 0; iVar14 = iVar14 + 1, iVar6 < 0x10; iVar6 = iVar6 + 1) {
      Create__10MenuSpriteFUc(iVar10 + iVar14 * 0x60,0);
      iVar7 = iVar10 + iVar14 * 0x60;
      *(byte *)(iVar7 + 0x21) = *(byte *)(iVar7 + 0x21) & 0xbf | 0x40;
      iVar7 = iVar10 + iVar14 * 0x60;
      uVar4 = (ulong)*(byte *)(iVar7 + 0x11) & 0xfffffffffffffffd | 2;
      *(char *)(iVar7 + 0x11) = (char)uVar4;
      iVar7 = iVar10 + iVar14 * 0x60;
      *(byte *)(iVar7 + 0x10) =
           *(byte *)(iVar7 + 0x10) & 0xfd | (byte)((uint)((uVar4 << 0x3e) >> 0x3f) << 1);
      *(undefined2 *)(iVar10 + iVar14 * 0x60 + 0x14) = 4;
      (**(code **)(*(int *)(iVar10 + iVar14 * 0x60 + 8) + 0x24))((float)(iVar6 << 4) + 16.0,0);
      SetUV__10MenuSpriteFUsUsUsUs(iVar10 + iVar14 * 0x60,0x13,0x53,0x24,0x5c);
      (**(code **)(*(int *)(iVar10 + iVar14 * 0x60 + 8) + 0x28))(0x41880000,0x41100000);
      iVar7 = iVar10 + iVar14 * 0x60;
      (**(code **)(*(int *)(iVar7 + 8) + 0x30))(iVar7,0x80,0x80,0x80);
      iVar7 = iVar10 + iVar14 * 0x60;
      (**(code **)(*(int *)(iVar7 + 8) + 0x2c))(iVar7,0x80);
      iVar7 = iVar10 + iVar14 * 0x60;
      *(byte *)(iVar7 + 0x21) = *(byte *)(iVar7 + 0x21) & 0xfd;
      iVar7 = iVar10 + iVar14 * 0x60;
      *(byte *)(iVar7 + 0x12) = *(byte *)(iVar7 + 0x12) & 0xfe;
      iVar7 = iVar10 + iVar14 * 0x60;
      *(byte *)(iVar7 + 0x12) = *(byte *)(iVar7 + 0x12) & 0xfe;
      *(short *)(iVar10 + iVar14 * 0x60 + 0x1c) = (short)iVar6;
      *(undefined2 *)(iVar10 + iVar14 * 0x60 + 0x1e) = 5;
      AddPlace__10MenuWindowFP9MenuPlace(param_1 + param_2 * 0x16c + 0x7c,iVar10 + iVar14 * 0x60);
    }
    Create__10MenuSpriteFUc(iVar10 + iVar14 * 0x60,0);
    iVar6 = iVar10 + iVar14 * 0x60;
    *(byte *)(iVar6 + 0x21) = *(byte *)(iVar6 + 0x21) & 0xbf | 0x40;
    iVar6 = iVar10 + iVar14 * 0x60;
    *(byte *)(iVar6 + 0x11) = *(byte *)(iVar6 + 0x11) & 0xfd | 2;
    iVar6 = iVar10 + iVar14 * 0x60;
    *(byte *)(iVar6 + 0x10) = *(byte *)(iVar6 + 0x10) & 0xfd | 2;
    *(undefined2 *)(iVar10 + iVar14 * 0x60 + 0x14) = 4;
    (**(code **)(*(int *)(iVar10 + iVar14 * 0x60 + 8) + 0x24))(0,0);
    (**(code **)(*(int *)(iVar10 + iVar14 * 0x60 + 8) + 0x28))(0x41900000,0x41a80000);
    SetUV__10MenuSpriteFUsUsUsUs(iVar10 + iVar14 * 0x60,0,0,0x12,0x15);
    iVar6 = iVar10 + iVar14 * 0x60;
    (**(code **)(*(int *)(iVar6 + 8) + 0x30))(iVar6,0x80,0x80,0x80);
    iVar6 = iVar10 + iVar14 * 0x60;
    (**(code **)(*(int *)(iVar6 + 8) + 0x2c))(iVar6,0x80);
    iVar6 = iVar10 + iVar14 * 0x60;
    *(byte *)(iVar6 + 0x21) = *(byte *)(iVar6 + 0x21) & 0xfd;
    iVar6 = iVar10 + iVar14 * 0x60;
    *(byte *)(iVar6 + 0x12) = *(byte *)(iVar6 + 0x12) & 0xfe;
    iVar6 = iVar10 + iVar14 * 0x60;
    *(byte *)(iVar6 + 0x12) = *(byte *)(iVar6 + 0x12) & 0xfe;
    *(undefined2 *)(iVar10 + iVar14 * 0x60 + 0x1c) = 3;
    *(undefined2 *)(iVar10 + iVar14 * 0x60 + 0x1e) = 6;
    AddPlace__10MenuWindowFP9MenuPlace(param_1 + param_2 * 0x16c + 0x7c,iVar10 + iVar14 * 0x60);
    CreateScroll__10MenuWindowFUissffUc(pfRam0040ab1c[2],0x43800000,param_1 + param_2 * 0x16c + 0x7c,
                    *(undefined2 *)(iVar13 + 0x48),0x20,0x10,0);
    *(undefined4 *)(*(int *)(param_1 + param_2 * 0x16c + 0xbc) + 0x38) = 0;
    SetScroll__10MenuWindowFss(param_1 + param_2 * 0x16c + 0x7c,0,0);
  }
  else {
    ClearImage__8FontDrawFv(param_1 + param_2 * 0x16c + 0x3c);
  }
  if ((iStack_60 < 0) && (-1 < param_4)) {
    iStack_60 = 0;
    while ((iStack_60 < param_5 && ((long)param_4 != (long)*(short *)(param_6 + iStack_60 * 2)))) {
      iStack_60 = iStack_60 + 1;
    }
    if (param_5 <= iStack_60) {
      iStack_60 = 0;
    }
  }
  else if (((iStack_60 < 0) && ((param_4 < 0 && (iStack_60 = 0, bVar1)))) && (param_9 != '\0')) {
    for (iVar13 = 0; iVar13 < param_5; iVar13 = iVar13 + 1) {
      if ((long)*(char *)(iGpffff86b4 + 0x2c) == (long)*(short *)(param_6 + iVar13 * 2)) {
        iStack_60 = iVar13;
      }
    }
  }
  iVar13 = *(int *)(param_1 + param_2 * 0x16c + 0x130);
  iVar10 = *(int *)(param_1 + param_2 * 0x16c + 0x13c);
  iVar7 = 0;
  iVar14 = 0;
  iVar8 = 0;
  fStack_98 = 0.0;
  iVar9 = 0;
  iVar6 = iStack_60;
  if (iStack_60 < 0) {
    iVar6 = iStack_60 + 3;
  }
  iVar12 = (iVar6 >> 2) * 4;
  for (iVar6 = 0; iVar6 < param_5; iVar6 = iVar6 + 1) {
    if ((iVar12 <= iVar9) && (iVar9 <= iVar12 + 3)) {
      if ((param_8 == 0) || (*(char *)(param_8 + iVar6) == '\0')) {
        *(short *)(iVar13 + iVar7 * 0x80 + 0x16) = *(short *)(param_6 + iVar6 * 2) + 1000;
        SetCSA__8FontItemFUc(iVar13 + iVar7 * 0x80,2);
        *(undefined1 *)(iVar13 + iVar7 * 0x80 + 0x5c) = 0;
        iVar11 = iVar13 + iVar7 * 0x80;
        uVar4 = (ulong)*(byte *)(iVar11 + 0x11) & 0xfffffffffffffffd | 2;
        *(char *)(iVar11 + 0x11) = (char)uVar4;
        iVar11 = iVar13 + iVar7 * 0x80;
        *(byte *)(iVar11 + 0x10) =
             *(byte *)(iVar11 + 0x10) & 0xfd | (byte)((uint)((uVar4 << 0x3e) >> 0x3f) << 1);
      }
      else {
        *(undefined2 *)(iVar13 + iVar7 * 0x80 + 0x16) = *(undefined2 *)(param_6 + iVar6 * 2);
        SetCSA__8FontItemFUc(iVar13 + iVar7 * 0x80,0);
        *(undefined1 *)(iVar13 + iVar7 * 0x80 + 0x5c) = 0;
        iVar11 = iVar13 + iVar7 * 0x80;
        uVar4 = (ulong)*(byte *)(iVar11 + 0x11) & 0xfffffffffffffffd | 2;
        *(char *)(iVar11 + 0x11) = (char)uVar4;
        iVar11 = iVar13 + iVar7 * 0x80;
        *(byte *)(iVar11 + 0x10) =
             *(byte *)(iVar11 + 0x10) & 0xfd | (byte)((uint)((uVar4 << 0x3e) >> 0x3f) << 1);
      }
      (**(code **)(*(int *)(iVar13 + iVar7 * 0x80 + 8) + 0x24))(0x42400000,fStack_98 + 2.0);
      SetMessage__8MenuTextFPcUiUcUc(iVar13 + iVar7 * 0x80,param_7 + iVar6 * 0x20,0,0,1);
      *(undefined2 *)(iVar13 + iVar7 * 0x80 + 0x1c) = 0;
      *(short *)(iVar13 + iVar7 * 0x80 + 0x1e) = (short)iVar8;
      iVar11 = iVar13 + iVar7 * 0x80;
      *(byte *)(iVar11 + 0x21) = *(byte *)(iVar11 + 0x21) & 0xfd | 2;
      iVar11 = iVar13 + iVar7 * 0x80;
      *(byte *)(iVar11 + 0x12) = *(byte *)(iVar11 + 0x12) & 0xfe | 1;
      iVar11 = iVar13 + iVar7 * 0x80;
      *(byte *)(iVar11 + 0x12) = *(byte *)(iVar11 + 0x12) & 0xfe | 1;
      OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(param_1 + param_2 * 0x16c + 0x3c,iVar13 + iVar7 * 0x80,1,0);
      if (iStack_60 == iVar9) {
        *(int *)(param_1 + param_2 * 0x16c + 0x158) = iVar7;
        *(int *)(param_1 + param_2 * 0x16c + 0x16c) = iVar9;
        iVar11 = (int)*(short *)(iVar13 + iVar7 * 0x80 + 0x16);
        *(int *)(param_1 + param_2 * 0x16c + 0x164) = iVar11;
        *(int *)(param_1 + param_2 * 0x16c + 0x168) = iVar11;
      }
      iVar7 = iVar7 + 1;
      (**(code **)(*(int *)(iVar10 + iVar14 * 0x60 + 8) + 0x24))(0,fStack_98);
      SetUV__10MenuSpriteFUsUsUsUs(iVar10 + iVar14 * 0x60,1,1,0xdd,0x1c);
      (**(code **)(*(int *)(iVar10 + iVar14 * 0x60 + 8) + 0x28))(0x435c0000,0x41d80000);
      iVar11 = iVar10 + iVar14 * 0x60;
      *(byte *)(iVar11 + 0x12) = *(byte *)(iVar11 + 0x12) & 0xfe | 1;
      iVar11 = iVar10 + iVar14 * 0x60;
      *(byte *)(iVar11 + 0x12) = *(byte *)(iVar11 + 0x12) & 0xfe | 1;
      iVar14 = iVar14 + 1;
      iVar8 = iVar8 + 1;
      fStack_98 = fStack_98 + 26.0;
    }
    iVar9 = iVar9 + 1;
  }
  for (; iVar8 < 4; iVar8 = iVar8 + 1) {
    (**(code **)(*(int *)(iVar13 + iVar7 * 0x80 + 8) + 0x24))(0x42400000,fStack_98 + 2.0);
    SetMessage__8MenuTextFPcUiUcUc(iVar13 + iVar7 * 0x80,0x6551a8,0,0,1);
    *(undefined2 *)(iVar13 + iVar7 * 0x80 + 0x1c) = 0;
    *(short *)(iVar13 + iVar7 * 0x80 + 0x1e) = (short)iVar8;
    iVar6 = iVar13 + iVar7 * 0x80;
    *(byte *)(iVar6 + 0x21) = *(byte *)(iVar6 + 0x21) & 0xfd;
    iVar6 = iVar13 + iVar7 * 0x80;
    *(byte *)(iVar6 + 0x12) = *(byte *)(iVar6 + 0x12) & 0xfe;
    iVar6 = iVar13 + iVar7 * 0x80;
    *(byte *)(iVar6 + 0x12) = *(byte *)(iVar6 + 0x12) & 0xfe;
    OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(param_1 + param_2 * 0x16c + 0x3c,iVar13 + iVar7 * 0x80,1,0);
    iVar7 = iVar7 + 1;
    (**(code **)(*(int *)(iVar10 + iVar14 * 0x60 + 8) + 0x24))(0,fStack_98);
    SetUV__10MenuSpriteFUsUsUsUs(iVar10 + iVar14 * 0x60,1,1,0xdd,0x1c);
    (**(code **)(*(int *)(iVar10 + iVar14 * 0x60 + 8) + 0x28))(0x435c0000,0x41d80000);
    iVar6 = iVar10 + iVar14 * 0x60;
    *(byte *)(iVar6 + 0x12) = *(byte *)(iVar6 + 0x12) & 0xfe | 1;
    iVar6 = iVar10 + iVar14 * 0x60;
    *(byte *)(iVar6 + 0x12) = *(byte *)(iVar6 + 0x12) & 0xfe | 1;
    iVar14 = iVar14 + 1;
    fStack_98 = fStack_98 + 26.0;
  }
  *(int *)(param_1 + param_2 * 0x16c + 0x170) = iVar9;
  iVar13 = iVar12;
  if (iVar12 < 0) {
    iVar13 = iVar12 + 3;
  }
  *(int *)(param_1 + param_2 * 0x16c + 0x174) = iVar13 >> 2;
  iVar13 = *(int *)(param_1 + param_2 * 0x16c + 0x170);
  iVar6 = iVar13 + 3;
  if (iVar6 < 0) {
    iVar6 = iVar13 + 6;
  }
  iVar6 = iVar6 >> 2;
  if (iVar6 < 2) {
    iVar13 = 0;
  }
  else {
    fStack_94 = 219.0 - ((float)iVar6 * 12.0 + 5.0);
    for (iVar13 = 0; iVar13 < iVar6; iVar13 = iVar13 + 1) {
      (**(code **)(*(int *)(iVar10 + (iVar13 + 5) * 0x60 + 8) + 0x24))(fStack_94,fStack_98);
      if (*(int *)(param_1 + param_2 * 0x16c + 0x174) == iVar13) {
        SetUV__10MenuSpriteFUsUsUsUs(iVar10 + (iVar13 + 5) * 0x60,1,0x53,0x13,0x5c);
        (**(code **)(*(int *)(iVar10 + (iVar13 + 5) * 0x60 + 8) + 0x28))(0x41900000,0x41100000);
        fStack_94 = fStack_94 + 17.0;
      }
      else {
        SetUV__10MenuSpriteFUsUsUsUs(iVar10 + (iVar13 + 5) * 0x60,0x14,0x53,0x21,0x5c);
        (**(code **)(*(int *)(iVar10 + (iVar13 + 5) * 0x60 + 8) + 0x28))(0x41500000,0x41100000);
        fStack_94 = fStack_94 + 12.0;
      }
      iVar14 = iVar10 + (iVar13 + 5) * 0x60;
      *(byte *)(iVar14 + 0x12) = *(byte *)(iVar14 + 0x12) & 0xfe | 1;
      iVar14 = iVar10 + (iVar13 + 5) * 0x60;
      *(byte *)(iVar14 + 0x12) = *(byte *)(iVar14 + 0x12) & 0xfe | 1;
    }
    fStack_98 = fStack_98 + 8.0;
  }
  for (; iVar13 < 0x10; iVar13 = iVar13 + 1) {
    iVar6 = iVar10 + (iVar13 + 5) * 0x60;
    *(byte *)(iVar6 + 0x12) = *(byte *)(iVar6 + 0x12) & 0xfe;
    iVar6 = iVar10 + (iVar13 + 5) * 0x60;
    *(byte *)(iVar6 + 0x12) = *(byte *)(iVar6 + 0x12) & 0xfe;
  }
  *(float *)(param_1 + param_2 * 0x16c + 0x17c) = (pfRam0040ab1c[1] + pfRam0040ab1c[3]) - fStack_98;
  *(float *)(param_1 + param_2 * 0x16c + 0x180) = fStack_98;
  SetPosition__10MenuWindowFff(*pfRam0040ab1c,(pfRam0040ab1c[1] + pfRam0040ab1c[3]) - fStack_98,
                  param_1 + param_2 * 0x16c + 0x7c);
  SetSize__10MenuWindowFff(pfRam0040ab1c[2],fStack_98,param_1 + param_2 * 0x16c + 0x7c);
  *(float *)(param_1 + param_2 * 0x16c + 0x184) = *pfRam0040ab1c;
  *(float *)(param_1 + param_2 * 0x16c + 0x188) = (pfRam0040ab1c[1] + pfRam0040ab1c[3]) - fStack_98;
  *(float *)(param_1 + param_2 * 0x16c + 0x18c) = pfRam0040ab1c[2];
  *(float *)(param_1 + param_2 * 0x16c + 400) = fStack_98;
  SetMark__10ScrollMarkFUc(*(undefined4 *)(param_1 + param_2 * 0x16c + 0x140),0);
  if (*(int *)(param_1 + param_2 * 0x16c + 0x170) < 5) {
    if (*(short *)(param_1 + 0xa32) == 1) {
      *(undefined2 *)(param_1 + 0xa32) = 2;
    }
  }
  else {
    if (*(int *)(param_1 + 0xb30) == 0) {
      lVar5 = __nw__FUi(0x84);
      uVar2 = 0;
      if (lVar5 != 0) {
        uVar2 = __ct__10ScrollMarkFv(lVar5);
      }
      *(undefined4 *)(param_1 + 0xb30) = uVar2;
      Create__10ScrollMarkFUcP10MenuWindowUc(*(undefined4 *)(param_1 + 0xb30),3,0,0);
      *(undefined2 *)(*(int *)(param_1 + 0xb30) + 0x14) = 0x10;
      AddOT__7MenuObjFv(*(undefined4 *)(param_1 + 0xb30));
      *(byte *)(param_1 + 0x25) = *(byte *)(param_1 + 0x25) & 0xfd | 2;
      *(undefined2 *)(param_1 + 0xa32) = 1;
    }
    SetArea__10ScrollMarkFUcffff(*pfRam0040ab1c + 48.0,*(undefined4 *)(param_1 + param_2 * 0x16c + 0x17c),
                    pfRam0040ab1c[2] - 80.0,*(undefined4 *)(param_1 + param_2 * 0x16c + 0x180),
                    *(undefined4 *)(param_1 + 0xb30),3);
    bVar15 = 0 < iVar12;
    if (iVar12 + 4 < *(int *)(param_1 + param_2 * 0x16c + 0x170)) {
      bVar15 = bVar15 | 2;
    }
    SetMark__10ScrollMarkFUc(*(undefined4 *)(param_1 + 0xb30),bVar15);
  }
  if (bVar1) {
    Open__10MenuWindowFUci(param_1 + param_2 * 0x16c + 0x7c,3,0x85);
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005d3e10  CreateMenu2__7BtlMenuFiiiiPsPcPsPcbb
 * C++: BtlMenu::CreateMenu2(int, int, int, int, short *, char *, short *, char *, bool, bool)
 * size: 0x2bfc bytes
 * --------------------------------------------------------------------------- */
void CreateMenu2__7BtlMenuFiiiiPsPcPsPcbb
               (int param_1,int param_2,int param_3,int param_4,int param_5,int param_6,int param_7,
               int param_8,int param_9,char param_10,byte param_11)

{
  short sVar1;
  undefined4 uVar2;
  int iVar3;
  undefined8 uVar4;
  long lVar5;
  int iVar6;
  ulong uVar7;
  int iVar8;
  long extraout_a2;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  byte bVar16;
  undefined1 auStack_160 [140];
  float fStack_d4;
  undefined4 uStack_d0;
  undefined4 uStack_cc;
  undefined4 uStack_c8;
  undefined4 uStack_c4;
  int iStack_c0;
  int iStack_bc;
  int iStack_b8;
  int iStack_b4;
  int iStack_b0;
  int iStack_ac;
  int iStack_a8;
  int iStack_a4;
  int iStack_a0;
  float fStack_9c;
  float fStack_98;
  float fStack_94;
  int iStack_90;
  int iStack_8c;
  short sStack_88;
  undefined2 uStack_86;
  short sStack_84;
  undefined2 uStack_82;
  int iStack_80;
  int iStack_70;
  int iStack_60;
  int iStack_50;
  int iStack_40;
  int iStack_30;
  int iStack_20;
  int iStack_10;
  
  iStack_90 = 0;
  iStack_80 = param_1;
  iStack_70 = param_2;
  iStack_50 = param_4;
  iStack_40 = param_5;
  iStack_30 = param_6;
  iStack_20 = param_7;
  iStack_10 = param_8;
  if (*(short *)(param_1 + param_2 * 0x16c + 0x32) == 0) {
    iStack_90 = 1;
    iVar15 = param_1 + param_2 * 0x16c;
    *(byte *)(iVar15 + 0x31) = *(byte *)(iVar15 + 0x31) & 0xdf | (param_11 & 1) << 5;
    *(undefined2 *)(param_1 + param_2 * 0x16c + 0x32) = 1;
    *(undefined2 *)(param_1 + param_2 * 0x16c + 0x34) = 0;
    *(undefined2 *)(param_1 + param_2 * 0x16c + 0x36) = 0;
    *(undefined4 *)(param_1 + param_2 * 0x16c + 0x38) = 0;
    *(undefined2 *)(param_1 + param_2 * 0x16c + 0x90) = 8;
    iStack_60 = param_3;
    AddOT__7MenuObjFv(param_1 + param_2 * 0x16c + 0x7c);
    iVar15 = iStack_80 + iStack_70 * 0x16c;
    *(byte *)(iVar15 + 0x30) = *(byte *)(iVar15 + 0x30) & 0xfb | 4;
    Create__10MenuWindowFUcUcffff(*pfRam0040ab1c,pfRam0040ab1c[1],pfRam0040ab1c[2],pfRam0040ab1c[3],
                    iStack_80 + iStack_70 * 0x16c + 0x7c,0,1);
    *(undefined4 *)(iStack_80 + iStack_70 * 0x16c + 0x178) = 3;
    iVar15 = iStack_80 + iStack_70 * 0x16c;
    *(byte *)(iVar15 + 0x30) = *(byte *)(iVar15 + 0x30) & 0xf7 | 8;
    if (*(int *)(iStack_80 + iStack_70 * 0x16c + 0x140) == 0) {
      iStack_bc = __nw__FUi(0x84);
      if (iStack_bc != 0) {
        iStack_bc = __ct__10ScrollMarkFv(iStack_bc);
      }
      *(int *)(iStack_80 + iStack_70 * 0x16c + 0x140) = iStack_bc;
      iStack_a0 = *(int *)(iStack_80 + iStack_70 * 0x16c + 0x140);
      *(undefined2 *)(iStack_a0 + 0x14) = 0x10;
      Create__10ScrollMarkFUcP10MenuWindowUc(*(undefined4 *)(iStack_80 + iStack_70 * 0x16c + 0x140),0xc,0,0);
      AddPriority__12MenuObjTableFP7MenuObj(iStack_80 + iStack_70 * 0x16c + 0x94,
                      *(undefined4 *)(iStack_80 + iStack_70 * 0x16c + 0x140));
    }
  }
  else {
    iStack_60 = *(int *)(param_1 + param_2 * 0x16c + 0x16c);
    if (((*(short *)(param_1 + param_2 * 0x16c + 0x32) != 2) &&
        (*(short *)(param_1 + param_2 * 0x16c + 0x32) != 1)) &&
       (*(short *)(param_1 + param_2 * 0x16c + 0x32) != 5)) {
      SetWindowMove__7BtlMenuFii(param_1,param_2,0);
      SetMark__10ScrollMarkFUc(*(undefined4 *)(iStack_80 + iStack_70 * 0x16c + 0x140),0);
      if (4 < *(int *)(iStack_80 + iStack_70 * 0x16c + 0x170)) {
        if (*(int *)(iStack_80 + 0xb30) == 0) {
          iStack_c0 = __nw__FUi(0x84);
          if (iStack_c0 != 0) {
            iStack_c0 = __ct__10ScrollMarkFv(iStack_c0);
          }
          *(int *)(iStack_80 + 0xb30) = iStack_c0;
          Create__10ScrollMarkFUcP10MenuWindowUc(*(undefined4 *)(iStack_80 + 0xb30),3,0,0);
          iStack_a4 = *(int *)(iStack_80 + 0xb30);
          *(undefined2 *)(iStack_a4 + 0x14) = 0x10;
          AddOT__7MenuObjFv(*(undefined4 *)(iStack_80 + 0xb30));
          *(byte *)(iStack_80 + 0x25) = *(byte *)(iStack_80 + 0x25) & 0xfd | 2;
          SetArea__10ScrollMarkFUcffff(*pfRam0040ab1c + 48.0,
                          *(undefined4 *)(iStack_80 + iStack_70 * 0x16c + 0x17c),
                          pfRam0040ab1c[2] - 80.0,
                          *(undefined4 *)(iStack_80 + iStack_70 * 0x16c + 0x180),
                          *(undefined4 *)(iStack_80 + 0xb30),3);
          *(undefined2 *)(iStack_80 + 0xa32) = 1;
        }
        iVar15 = iStack_60;
        if (iStack_60 < 0) {
          iVar15 = iStack_60 + 3;
        }
        iVar15 = (iVar15 >> 2) * 4;
        bVar16 = 0 < iVar15;
        if (iVar15 + 4 < *(int *)(iStack_80 + iStack_70 * 0x16c + 0x170)) {
          bVar16 = bVar16 | 2;
        }
        SetMark__10ScrollMarkFUc(*(undefined4 *)(iStack_80 + 0xb30),bVar16);
        return;
      }
      if (*(short *)(iStack_80 + 0xa32) != 1) {
        return;
      }
      *(undefined2 *)(iStack_80 + 0xa32) = 2;
      return;
    }
  }
  if (iStack_90 == 0) {
    ClearImage__8FontDrawFv(iStack_80 + iStack_70 * 0x16c + 0x3c);
  }
  else {
    Create__8FontDrawF6GS_PSMUsUsUcUiP10ClutRaster(iStack_80 + iStack_70 * 0x16c + 0x3c,0x2c,0x100,0x60,1,0,0);
    iVar15 = iStack_80 + iStack_70 * 0x16c;
    *(byte *)(iVar15 + 0x30) = *(byte *)(iVar15 + 0x30) & 0xfd | 2;
    *(undefined2 *)(iStack_80 + iStack_70 * 0x16c + 0x50) = 5;
    AddPriority__12MenuObjTableFP7MenuObj(iStack_80 + iStack_70 * 0x16c + 0x94,iStack_80 + iStack_70 * 0x16c + 0x3c);
    if (((ulong)*(ushort *)(iStack_80 + iStack_70 * 0x16c + 0x30) & 0xfff) >> 4 == 0) {
      uVar4 = __nwa__FUi(0x410);
      uVar2 = __construct_new_array(uVar4,0x27bfd0,0x27c030,0x80,8);
      *(undefined4 *)(iStack_80 + iStack_70 * 0x16c + 0x130) = uVar2;
      iVar15 = iStack_80 + iStack_70 * 0x16c;
      *(ushort *)(iVar15 + 0x30) = *(ushort *)(iVar15 + 0x30) & 0xf00f | 0x80;
    }
    iVar15 = *(int *)(iStack_80 + iStack_70 * 0x16c + 0x130);
    iVar3 = 0;
    for (iVar9 = 0; iVar9 < 4; iVar9 = iVar9 + 1) {
      Create__8MenuTextFUcUc(iVar15 + iVar3 * 0x80,0,2);
      *(undefined2 *)(iVar15 + iVar3 * 0x80 + 0x14) = 6;
      *(undefined1 *)(iVar15 + iVar3 * 0x80 + 0x5a) = 1;
      *(undefined1 *)(iVar15 + iVar3 * 0x80 + 0x5b) = 0;
      *(undefined2 *)(iVar15 + iVar3 * 0x80 + 0x1c) = 0;
      *(short *)(iVar15 + iVar3 * 0x80 + 0x1e) = (short)iVar9;
      AddPlace__10MenuWindowFP9MenuPlace(iStack_80 + iStack_70 * 0x16c + 0x7c,iVar15 + iVar3 * 0x80);
      iVar6 = iVar3 + 1;
      Create__8MenuTextFUcUc(iVar15 + iVar6 * 0x80,0,2);
      *(undefined2 *)(iVar15 + iVar6 * 0x80 + 0x14) = 6;
      *(undefined1 *)(iVar15 + iVar6 * 0x80 + 0x5a) = 1;
      *(undefined1 *)(iVar15 + iVar6 * 0x80 + 0x5b) = 0;
      *(undefined2 *)(iVar15 + iVar6 * 0x80 + 0x1c) = 1;
      *(short *)(iVar15 + iVar6 * 0x80 + 0x1e) = (short)iVar9;
      AddPlace__10MenuWindowFP9MenuPlace(iStack_80 + iStack_70 * 0x16c + 0x7c,iVar15 + iVar6 * 0x80);
      iVar3 = iVar3 + 2;
    }
    uVar4 = __nwa__FUi(0x70);
    uVar2 = __construct_new_array(uVar4,0x277820,0x277890,0x30,2);
    *(undefined4 *)(iStack_80 + iStack_70 * 0x16c + 0x138) = uVar2;
    iStack_a8 = *(int *)(iGpffff86b4 + 0x4234);
    uStack_c8 = *(undefined4 *)(iStack_a8 + (uint)*(ushort *)(iStack_a8 + 10) * 4 + 0xc);
    uStack_c4 = uStack_c8;
    uVar4 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x4234),0);
    Create__11SendOnLocalFP4_QWDUl(*(undefined4 *)(iStack_80 + iStack_70 * 0x16c + 0x138),uStack_c8,uVar4);
    iStack_ac = *(int *)(iStack_80 + iStack_70 * 0x16c + 0x138);
    *(undefined2 *)(iStack_ac + 0x14) = 1;
    AddPriority__12MenuObjTableFP7MenuObj(iStack_80 + iStack_70 * 0x16c + 0x94,
                    *(undefined4 *)(iStack_80 + iStack_70 * 0x16c + 0x138));
    iStack_b0 = *(int *)(iGpffff86b4 + 0x4238);
    uStack_d0 = *(undefined4 *)(iStack_b0 + (uint)*(ushort *)(iStack_b0 + 10) * 4 + 0xc);
    uStack_cc = uStack_d0;
    uVar4 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x4238),0);
    Create__11SendOnLocalFP4_QWDUl(*(int *)(iStack_80 + iStack_70 * 0x16c + 0x138) + 0x30,uStack_d0,uVar4);
    iVar3 = *(int *)(iStack_80 + iStack_70 * 0x16c + 0x138);
    iStack_b4 = iVar3 + 0x30;
    *(undefined2 *)(iVar3 + 0x44) = 3;
    AddPriority__12MenuObjTableFP7MenuObj(iStack_80 + iStack_70 * 0x16c + 0x94,
                    *(int *)(iStack_80 + iStack_70 * 0x16c + 0x138) + 0x30);
    if (*(int *)(iStack_80 + iStack_70 * 0x16c + 0x13c) == 0) {
      uVar4 = __nwa__FUi(0x850);
      uVar2 = __construct_new_array(uVar4,0x266140,0x2661a0,0x60,0x16);
      *(undefined4 *)(iStack_80 + iStack_70 * 0x16c + 0x13c) = uVar2;
    }
    iVar3 = *(int *)(iStack_80 + iStack_70 * 0x16c + 0x13c);
    iVar9 = 0;
    for (iVar6 = 0; iVar6 < 4; iVar6 = iVar6 + 1) {
      Create__10MenuSpriteFUc(iVar3 + iVar9 * 0x60,0);
      iVar8 = iVar3 + iVar9 * 0x60;
      *(byte *)(iVar8 + 0x21) = *(byte *)(iVar8 + 0x21) & 0xbf | 0x40;
      iVar8 = iVar3 + iVar9 * 0x60;
      uVar7 = (ulong)*(byte *)(iVar8 + 0x11) & 0xfffffffffffffffd | 2;
      *(char *)(iVar8 + 0x11) = (char)uVar7;
      iVar8 = iVar3 + iVar9 * 0x60;
      *(byte *)(iVar8 + 0x10) =
           *(byte *)(iVar8 + 0x10) & 0xfd | (byte)((uint)((uVar7 << 0x3e) >> 0x3f) << 1);
      *(undefined2 *)(iVar3 + iVar9 * 0x60 + 0x14) = 4;
      (**(code **)(*(int *)(iVar3 + iVar9 * 0x60 + 8) + 0x24))(0,(float)iVar6 * 26.0);
      SetUV__10MenuSpriteFUsUsUsUs(iVar3 + iVar9 * 0x60,1,1,0xdd,0x1c);
      (**(code **)(*(int *)(iVar3 + iVar9 * 0x60 + 8) + 0x28))(0x435c0000,0x41d80000);
      iVar8 = iVar3 + iVar9 * 0x60;
      (**(code **)(*(int *)(iVar8 + 8) + 0x30))(iVar8,0x80,0x80,0x80);
      iVar8 = iVar3 + iVar9 * 0x60;
      (**(code **)(*(int *)(iVar8 + 8) + 0x2c))(iVar8,0x80);
      iVar8 = iVar3 + iVar9 * 0x60;
      *(byte *)(iVar8 + 0x21) = *(byte *)(iVar8 + 0x21) & 0xfd;
      iVar8 = iVar3 + iVar9 * 0x60;
      *(byte *)(iVar8 + 0x12) = *(byte *)(iVar8 + 0x12) & 0xfe | 1;
      *(undefined2 *)(iVar3 + iVar9 * 0x60 + 0x1c) = 2;
      *(short *)(iVar3 + iVar9 * 0x60 + 0x1e) = (short)iVar6;
      AddPlace__10MenuWindowFP9MenuPlace(iStack_80 + iStack_70 * 0x16c + 0x7c,iVar3 + iVar9 * 0x60);
      iVar9 = iVar9 + 1;
    }
    Create__10MenuSpriteFUc(iVar3 + iVar9 * 0x60,0);
    iVar6 = iVar3 + iVar9 * 0x60;
    *(byte *)(iVar6 + 0x21) = *(byte *)(iVar6 + 0x21) & 0xbf | 0x40;
    iVar6 = iVar3 + iVar9 * 0x60;
    uVar7 = (ulong)*(byte *)(iVar6 + 0x11) & 0xfffffffffffffffd | 2;
    *(char *)(iVar6 + 0x11) = (char)uVar7;
    iVar6 = iVar3 + iVar9 * 0x60;
    *(byte *)(iVar6 + 0x10) =
         *(byte *)(iVar6 + 0x10) & 0xfd | (byte)((uint)((uVar7 << 0x3e) >> 0x3f) << 1);
    *(undefined2 *)(iVar3 + iVar9 * 0x60 + 0x14) = 2;
    (**(code **)(*(int *)(iVar3 + iVar9 * 0x60 + 8) + 0x24))(0,0);
    (**(code **)(*(int *)(iVar3 + iVar9 * 0x60 + 8) + 0x28))(0x437f0000,0x41c00000);
    SetUV__10MenuSpriteFUsUsUsUs(iVar3 + iVar9 * 0x60,0,0,0xff,0x18);
    iVar6 = iVar3 + iVar9 * 0x60;
    uVar4 = (**(code **)(*(int *)(iVar6 + 8) + 0x30))(iVar6,0x80,0x80,0x80);
    iVar6 = iVar3 + iVar9 * 0x60;
    (**(code **)(*(int *)(iVar6 + 8) + 0x2c))(iVar6,0,iVar9 * 0x60,iVar6,uVar4);
    iVar6 = iVar3 + iVar9 * 0x60;
    *(byte *)(iVar6 + 0x21) = *(byte *)(iVar6 + 0x21) & 0xfd;
    iVar6 = iVar3 + iVar9 * 0x60;
    *(byte *)(iVar6 + 0x12) = *(byte *)(iVar6 + 0x12) & 0xfe | 1;
    *(undefined2 *)(iVar3 + iVar9 * 0x60 + 0x1c) = 2;
    *(undefined2 *)(iVar3 + iVar9 * 0x60 + 0x1e) = 4;
    AddPlace__10MenuWindowFP9MenuPlace(iStack_80 + iStack_70 * 0x16c + 0x7c,iVar3 + iVar9 * 0x60);
    iVar9 = iVar9 + 1;
    iVar6 = iVar9;
    for (iVar8 = 0; iVar8 < 0x10; iVar8 = iVar8 + 1) {
      Create__10MenuSpriteFUc(iVar3 + iVar6 * 0x60,0,iVar6 * 0x60,iVar9);
      iVar9 = iVar3 + iVar6 * 0x60;
      *(byte *)(iVar9 + 0x21) = *(byte *)(iVar9 + 0x21) & 0xbf | 0x40;
      iVar9 = iVar3 + iVar6 * 0x60;
      uVar7 = (ulong)*(byte *)(iVar9 + 0x11) & 0xfffffffffffffffd | 2;
      *(char *)(iVar9 + 0x11) = (char)uVar7;
      iVar9 = iVar3 + iVar6 * 0x60;
      *(byte *)(iVar9 + 0x10) =
           *(byte *)(iVar9 + 0x10) & 0xfd | (byte)((uint)((uVar7 << 0x3e) >> 0x3f) << 1);
      *(undefined2 *)(iVar3 + iVar6 * 0x60 + 0x14) = 4;
      (**(code **)(*(int *)(iVar3 + iVar6 * 0x60 + 8) + 0x24))((float)(iVar8 << 4) + 16.0,0);
      uVar4 = SetUV__10MenuSpriteFUsUsUsUs(iVar3 + iVar6 * 0x60,0x13,0x53,0x24,0x5c);
      iVar9 = iVar3 + iVar6 * 0x60;
      (**(code **)(*(int *)(iVar9 + 8) + 0x28))(0x41880000,0x41100000,iVar9,uVar4);
      iVar9 = iVar3 + iVar6 * 0x60;
      (**(code **)(*(int *)(iVar9 + 8) + 0x30))(iVar9,0x80,0x80,0x80);
      iVar9 = iVar3 + iVar6 * 0x60;
      (**(code **)(*(int *)(iVar9 + 8) + 0x2c))(iVar9,0x80);
      iVar9 = iVar3 + iVar6 * 0x60;
      *(byte *)(iVar9 + 0x21) = *(byte *)(iVar9 + 0x21) & 0xfd;
      iVar9 = iVar3 + iVar6 * 0x60;
      *(byte *)(iVar9 + 0x12) = *(byte *)(iVar9 + 0x12) & 0xfe;
      iVar9 = iVar3 + iVar6 * 0x60;
      *(byte *)(iVar9 + 0x12) = *(byte *)(iVar9 + 0x12) & 0xfe;
      *(short *)(iVar3 + iVar6 * 0x60 + 0x1c) = (short)iVar8;
      *(undefined2 *)(iVar3 + iVar6 * 0x60 + 0x1e) = 5;
      iVar9 = AddPlace__10MenuWindowFP9MenuPlace(iStack_80 + iStack_70 * 0x16c + 0x7c,iVar3 + iVar6 * 0x60);
      iVar6 = iVar6 + 1;
    }
    Create__10MenuSpriteFUc(iVar3 + iVar6 * 0x60,0,iVar6 * 2,iVar9);
    iVar9 = iVar3 + iVar6 * 0x60;
    *(byte *)(iVar9 + 0x21) = *(byte *)(iVar9 + 0x21) & 0xbf | 0x40;
    iVar9 = iVar3 + iVar6 * 0x60;
    uVar7 = (ulong)*(byte *)(iVar9 + 0x11) & 0xfffffffffffffffd | 2;
    *(char *)(iVar9 + 0x11) = (char)uVar7;
    iVar9 = iVar3 + iVar6 * 0x60;
    *(byte *)(iVar9 + 0x10) =
         *(byte *)(iVar9 + 0x10) & 0xfd | (byte)((uint)((uVar7 << 0x3e) >> 0x3f) << 1);
    *(undefined2 *)(iVar3 + iVar6 * 0x60 + 0x14) = 4;
    (**(code **)(*(int *)(iVar3 + iVar6 * 0x60 + 8) + 0x24))(0,0);
    (**(code **)(*(int *)(iVar3 + iVar6 * 0x60 + 8) + 0x28))(0x41900000,0x41a80000);
    SetUV__10MenuSpriteFUsUsUsUs(iVar3 + iVar6 * 0x60,0,0,0x12,0x15);
    iVar9 = iVar3 + iVar6 * 0x60;
    (**(code **)(*(int *)(iVar9 + 8) + 0x30))(iVar9,0x80,0x80,0x80);
    iVar9 = iVar3 + iVar6 * 0x60;
    (**(code **)(*(int *)(iVar9 + 8) + 0x2c))(iVar9,0x80);
    iVar9 = iVar3 + iVar6 * 0x60;
    *(byte *)(iVar9 + 0x21) = *(byte *)(iVar9 + 0x21) & 0xfd;
    iVar9 = iVar3 + iVar6 * 0x60;
    *(byte *)(iVar9 + 0x12) = *(byte *)(iVar9 + 0x12) & 0xfe;
    iVar9 = iVar3 + iVar6 * 0x60;
    *(byte *)(iVar9 + 0x12) = *(byte *)(iVar9 + 0x12) & 0xfe;
    *(undefined2 *)(iVar3 + iVar6 * 0x60 + 0x1c) = 3;
    *(undefined2 *)(iVar3 + iVar6 * 0x60 + 0x1e) = 6;
    AddPlace__10MenuWindowFP9MenuPlace(iStack_80 + iStack_70 * 0x16c + 0x7c,iVar3 + iVar6 * 0x60);
    uStack_86 = *(undefined2 *)(iVar15 + 0x48);
    CreateScroll__10MenuWindowFUissffUc(pfRam0040ab1c[2],0x43800000,iStack_80 + iStack_70 * 0x16c + 0x7c,uStack_86,0x20,
                    0x10,0);
    *(undefined4 *)(*(int *)(iStack_80 + iStack_70 * 0x16c + 0xbc) + 0x38) = 0;
    SetScroll__10MenuWindowFss(iStack_80 + iStack_70 * 0x16c + 0x7c,0,0);
  }
  if ((iStack_60 < 0) && (-1 < iStack_50)) {
    iStack_60 = 0;
    while ((iStack_60 < iStack_40 &&
           ((long)iStack_50 != (long)*(short *)(iStack_30 + iStack_60 * 2)))) {
      iStack_60 = iStack_60 + 1;
    }
    if (iStack_40 <= iStack_60) {
      iStack_60 = 0;
    }
  }
  else if (((iStack_60 < 0) && ((iStack_50 < 0 && (iStack_60 = 0, iStack_90 != 0)))) &&
          (param_10 != '\0')) {
    for (iVar15 = 0; iVar15 < iStack_40; iVar15 = iVar15 + 1) {
      if ((long)*(char *)(iGpffff86b4 + 0x2c) == (long)*(short *)(iStack_30 + iVar15 * 2)) {
        iStack_60 = iVar15;
      }
    }
  }
  iVar15 = *(int *)(iStack_80 + iStack_70 * 0x16c + 0x130);
  iVar3 = *(int *)(iStack_80 + iStack_70 * 0x16c + 0x13c);
  iVar8 = 0;
  iVar14 = 0;
  iVar6 = 0;
  fStack_98 = 0.0;
  iVar12 = 0;
  iVar9 = iStack_60;
  if (iStack_60 < 0) {
    iVar9 = iStack_60 + 3;
  }
  iVar10 = (iVar9 >> 2) * 4;
  for (iVar9 = 0; iVar9 < iStack_40; iVar9 = iVar9 + 1) {
    if ((iVar10 <= iVar12) && (iVar12 <= iVar10 + 3)) {
      if ((param_9 == 0) || (*(char *)(param_9 + iVar9) == '\0')) {
        sStack_84 = *(short *)(iStack_30 + iVar9 * 2) + 1000;
        *(short *)(iVar15 + iVar8 * 0x80 + 0x16) = sStack_84;
        SetCSA__8FontItemFUc(iVar15 + iVar8 * 0x80,2);
        *(undefined1 *)(iVar15 + iVar8 * 0x80 + 0x5c) = 0;
        iVar13 = iVar15 + iVar8 * 0x80;
        uVar7 = (ulong)*(byte *)(iVar13 + 0x11) & 0xfffffffffffffffd | 2;
        *(char *)(iVar13 + 0x11) = (char)uVar7;
        iVar13 = iVar15 + iVar8 * 0x80;
        *(byte *)(iVar13 + 0x10) =
             *(byte *)(iVar13 + 0x10) & 0xfd | (byte)((uint)((uVar7 << 0x3e) >> 0x3f) << 1);
      }
      else {
        uStack_82 = *(undefined2 *)(iStack_30 + iVar9 * 2);
        *(undefined2 *)(iVar15 + iVar8 * 0x80 + 0x16) = uStack_82;
        SetCSA__8FontItemFUc(iVar15 + iVar8 * 0x80,0);
        *(undefined1 *)(iVar15 + iVar8 * 0x80 + 0x5c) = 0;
        iVar13 = iVar15 + iVar8 * 0x80;
        uVar7 = (ulong)*(byte *)(iVar13 + 0x11) & 0xfffffffffffffffd | 2;
        *(char *)(iVar13 + 0x11) = (char)uVar7;
        iVar13 = iVar15 + iVar8 * 0x80;
        *(byte *)(iVar13 + 0x10) =
             *(byte *)(iVar13 + 0x10) & 0xfd | (byte)((uint)((uVar7 << 0x3e) >> 0x3f) << 1);
      }
      (**(code **)(*(int *)(iVar15 + iVar8 * 0x80 + 8) + 0x24))(0x42400000,fStack_98 + 2.0);
      SetMessage__8MenuTextFPcUiUcUc(iVar15 + iVar8 * 0x80,iStack_20 + iVar9 * 0x20,0,0,1);
      *(undefined2 *)(iVar15 + iVar8 * 0x80 + 0x1c) = 0;
      *(short *)(iVar15 + iVar8 * 0x80 + 0x1e) = (short)iVar6;
      iVar13 = iVar15 + iVar8 * 0x80;
      *(byte *)(iVar13 + 0x21) = *(byte *)(iVar13 + 0x21) & 0xfd | 2;
      iVar13 = iVar15 + iVar8 * 0x80;
      *(byte *)(iVar13 + 0x12) = *(byte *)(iVar13 + 0x12) & 0xfe | 1;
      iVar13 = iVar15 + iVar8 * 0x80;
      *(byte *)(iVar13 + 0x12) = *(byte *)(iVar13 + 0x12) & 0xfe | 1;
      sVar1 = OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_80 + iStack_70 * 0x16c + 0x3c,iVar15 + iVar8 * 0x80,1,0);
      lVar5 = extraout_a2;
      if (iStack_60 == iVar12) {
        *(int *)(iStack_80 + iStack_70 * 0x16c + 0x158) = iVar8;
        *(int *)(iStack_80 + iStack_70 * 0x16c + 0x16c) = iVar12;
        sStack_88 = *(short *)(iVar15 + iVar8 * 0x80 + 0x16);
        *(int *)(iStack_80 + iStack_70 * 0x16c + 0x164) = (int)sStack_88;
        lVar5 = (long)iStack_80;
        *(int *)(iStack_80 + iStack_70 * 0x16c + 0x168) = (int)sStack_88;
        sVar1 = sStack_88;
      }
      iVar13 = iVar8 + 1;
      if ((param_9 == 0) || (*(char *)(param_9 + iVar9) == '\0')) {
        SetCSA__8FontItemFUc(iVar15 + iVar13 * 0x80,2,lVar5,iVar13,sVar1);
        *(undefined1 *)(iVar15 + iVar13 * 0x80 + 0x5c) = 0;
        iVar11 = iVar15 + iVar13 * 0x80;
        uVar7 = (ulong)*(byte *)(iVar11 + 0x11) & 0xfffffffffffffffd | 2;
        *(char *)(iVar11 + 0x11) = (char)uVar7;
        iVar11 = iVar15 + iVar13 * 0x80;
        *(byte *)(iVar11 + 0x10) =
             *(byte *)(iVar11 + 0x10) & 0xfd | (byte)((uint)((uVar7 << 0x3e) >> 0x3f) << 1);
      }
      else {
        iVar11 = iVar15 + iVar13 * 0x80;
        SetCSA__8FontItemFUc(iVar11,0,iVar13 * 0x80,iVar11,sVar1);
        *(undefined1 *)(iVar15 + iVar13 * 0x80 + 0x5c) = 0;
        iVar11 = iVar15 + iVar13 * 0x80;
        uVar7 = (ulong)*(byte *)(iVar11 + 0x11) & 0xfffffffffffffffd | 2;
        *(char *)(iVar11 + 0x11) = (char)uVar7;
        iVar11 = iVar15 + iVar13 * 0x80;
        *(byte *)(iVar11 + 0x10) =
             *(byte *)(iVar11 + 0x10) & 0xfd | (byte)((uint)((uVar7 << 0x3e) >> 0x3f) << 1);
      }
      sprintf(auStack_160,0x6551b0,*(undefined2 *)(iStack_10 + iVar9 * 2));
      SetMessage__8MenuTextFPcUiUcUc(iVar15 + iVar13 * 0x80,auStack_160,0,0,1);
      *(undefined2 *)(iVar15 + iVar13 * 0x80 + 0x1c) = 1;
      *(short *)(iVar15 + iVar13 * 0x80 + 0x1e) = (short)iVar6;
      iVar11 = iVar15 + iVar13 * 0x80;
      *(byte *)(iVar11 + 0x21) = *(byte *)(iVar11 + 0x21) & 0xfd;
      if (*(short *)(iStack_10 + iVar9 * 2) < 0) {
        iVar11 = iVar15 + iVar13 * 0x80;
        *(byte *)(iVar11 + 0x12) = *(byte *)(iVar11 + 0x12) & 0xfe;
        iVar11 = iVar15 + iVar13 * 0x80;
        *(byte *)(iVar11 + 0x12) = *(byte *)(iVar11 + 0x12) & 0xfe;
      }
      else {
        iVar11 = iVar15 + iVar13 * 0x80;
        *(byte *)(iVar11 + 0x12) = *(byte *)(iVar11 + 0x12) & 0xfe | 1;
        iVar11 = iVar15 + iVar13 * 0x80;
        *(byte *)(iVar11 + 0x12) = *(byte *)(iVar11 + 0x12) & 0xfe | 1;
      }
      OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_80 + iStack_70 * 0x16c + 0x3c,iVar15 + iVar13 * 0x80,0,0);
      fStack_d4 = *(float *)(iVar15 + iVar13 * 0x80 + 0x2c);
      fStack_9c = fStack_d4;
      (**(code **)(*(int *)(iVar15 + iVar13 * 0x80 + 8) + 0x24))(217.0 - fStack_d4,fStack_98 + 2.0);
      iVar8 = iVar8 + 2;
      (**(code **)(*(int *)(iVar3 + iVar14 * 0x60 + 8) + 0x24))(0,fStack_98);
      SetUV__10MenuSpriteFUsUsUsUs(iVar3 + iVar14 * 0x60,1,1,0xdd,0x1c);
      (**(code **)(*(int *)(iVar3 + iVar14 * 0x60 + 8) + 0x28))(0x435c0000,0x41d80000);
      iVar13 = iVar3 + iVar14 * 0x60;
      *(byte *)(iVar13 + 0x12) = *(byte *)(iVar13 + 0x12) & 0xfe | 1;
      iVar13 = iVar3 + iVar14 * 0x60;
      *(byte *)(iVar13 + 0x12) = *(byte *)(iVar13 + 0x12) & 0xfe | 1;
      iVar14 = iVar14 + 1;
      iVar6 = iVar6 + 1;
      fStack_98 = fStack_98 + 26.0;
    }
    iVar12 = iVar12 + 1;
  }
  for (; iVar6 < 4; iVar6 = iVar6 + 1) {
    (**(code **)(*(int *)(iVar15 + iVar8 * 0x80 + 8) + 0x24))(0x42400000,fStack_98 + 2.0);
    SetMessage__8MenuTextFPcUiUcUc(iVar15 + iVar8 * 0x80,0x6551a8,0,0,1);
    *(undefined2 *)(iVar15 + iVar8 * 0x80 + 0x1c) = 0;
    *(short *)(iVar15 + iVar8 * 0x80 + 0x1e) = (short)iVar6;
    iVar9 = iVar15 + iVar8 * 0x80;
    *(byte *)(iVar9 + 0x21) = *(byte *)(iVar9 + 0x21) & 0xfd;
    iVar9 = iVar15 + iVar8 * 0x80;
    *(byte *)(iVar9 + 0x12) = *(byte *)(iVar9 + 0x12) & 0xfe;
    iVar9 = iVar15 + iVar8 * 0x80;
    *(byte *)(iVar9 + 0x12) = *(byte *)(iVar9 + 0x12) & 0xfe;
    OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_80 + iStack_70 * 0x16c + 0x3c,iVar15 + iVar8 * 0x80,1,0);
    iVar9 = iVar8 + 1;
    (**(code **)(*(int *)(iVar15 + iVar9 * 0x80 + 8) + 0x24))(0x42400000,fStack_98 + 2.0);
    SetMessage__8MenuTextFPcUiUcUc(iVar15 + iVar9 * 0x80,0x6551a8,0,0,1);
    *(undefined2 *)(iVar15 + iVar9 * 0x80 + 0x1c) = 1;
    *(short *)(iVar15 + iVar9 * 0x80 + 0x1e) = (short)iVar6;
    iVar13 = iVar15 + iVar9 * 0x80;
    *(byte *)(iVar13 + 0x21) = *(byte *)(iVar13 + 0x21) & 0xfd;
    iVar13 = iVar15 + iVar9 * 0x80;
    *(byte *)(iVar13 + 0x12) = *(byte *)(iVar13 + 0x12) & 0xfe;
    iVar13 = iVar15 + iVar9 * 0x80;
    *(byte *)(iVar13 + 0x12) = *(byte *)(iVar13 + 0x12) & 0xfe;
    OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_80 + iStack_70 * 0x16c + 0x3c,iVar15 + iVar9 * 0x80,1,0);
    iVar8 = iVar8 + 2;
    (**(code **)(*(int *)(iVar3 + iVar14 * 0x60 + 8) + 0x24))(0,fStack_98);
    SetUV__10MenuSpriteFUsUsUsUs(iVar3 + iVar14 * 0x60,1,1,0xdd,0x1c);
    (**(code **)(*(int *)(iVar3 + iVar14 * 0x60 + 8) + 0x28))(0x435c0000,0x41d80000);
    iVar9 = iVar3 + iVar14 * 0x60;
    *(byte *)(iVar9 + 0x12) = *(byte *)(iVar9 + 0x12) & 0xfe | 1;
    iVar9 = iVar3 + iVar14 * 0x60;
    *(byte *)(iVar9 + 0x12) = *(byte *)(iVar9 + 0x12) & 0xfe | 1;
    iVar14 = iVar14 + 1;
    fStack_98 = fStack_98 + 26.0;
  }
  *(int *)(iStack_80 + iStack_70 * 0x16c + 0x170) = iVar12;
  iVar15 = iVar10;
  if (iVar10 < 0) {
    iVar15 = iVar10 + 3;
  }
  *(int *)(iStack_80 + iStack_70 * 0x16c + 0x174) = iVar15 >> 2;
  iVar15 = *(int *)(iStack_80 + iStack_70 * 0x16c + 0x170);
  iStack_8c = iVar15 + 3;
  if (iStack_8c < 0) {
    iStack_8c = iVar15 + 6;
  }
  iStack_8c = iStack_8c >> 2;
  if (iStack_8c < 2) {
    iVar15 = 0;
  }
  else {
    fStack_94 = 219.0 - ((float)iStack_8c * 12.0 + 5.0);
    for (iVar15 = 0; iVar15 < iStack_8c; iVar15 = iVar15 + 1) {
      (**(code **)(*(int *)(iVar3 + (iVar15 + 5) * 0x60 + 8) + 0x24))(fStack_94,fStack_98);
      if (*(int *)(iStack_80 + iStack_70 * 0x16c + 0x174) == iVar15) {
        SetUV__10MenuSpriteFUsUsUsUs(iVar3 + (iVar15 + 5) * 0x60,1,0x53,0x13,0x5c);
        (**(code **)(*(int *)(iVar3 + (iVar15 + 5) * 0x60 + 8) + 0x28))(0x41900000,0x41100000);
        fStack_94 = fStack_94 + 17.0;
      }
      else {
        SetUV__10MenuSpriteFUsUsUsUs(iVar3 + (iVar15 + 5) * 0x60,0x14,0x53,0x21,0x5c);
        (**(code **)(*(int *)(iVar3 + (iVar15 + 5) * 0x60 + 8) + 0x28))(0x41500000,0x41100000);
        fStack_94 = fStack_94 + 12.0;
      }
      iVar9 = iVar3 + (iVar15 + 5) * 0x60;
      *(byte *)(iVar9 + 0x12) = *(byte *)(iVar9 + 0x12) & 0xfe | 1;
      iVar9 = iVar3 + (iVar15 + 5) * 0x60;
      *(byte *)(iVar9 + 0x12) = *(byte *)(iVar9 + 0x12) & 0xfe | 1;
    }
    fStack_98 = fStack_98 + 8.0;
  }
  for (; iVar15 < 0x10; iVar15 = iVar15 + 1) {
    iVar9 = iVar3 + (iVar15 + 5) * 0x60;
    *(byte *)(iVar9 + 0x12) = *(byte *)(iVar9 + 0x12) & 0xfe;
    iVar9 = iVar3 + (iVar15 + 5) * 0x60;
    *(byte *)(iVar9 + 0x12) = *(byte *)(iVar9 + 0x12) & 0xfe;
  }
  *(float *)(iStack_80 + iStack_70 * 0x16c + 0x17c) =
       (pfRam0040ab1c[1] + pfRam0040ab1c[3]) - fStack_98;
  *(float *)(iStack_80 + iStack_70 * 0x16c + 0x180) = fStack_98;
  SetPosition__10MenuWindowFff(*pfRam0040ab1c,(pfRam0040ab1c[1] + pfRam0040ab1c[3]) - fStack_98,
                  iStack_80 + iStack_70 * 0x16c + 0x7c);
  SetSize__10MenuWindowFff(pfRam0040ab1c[2],fStack_98,iStack_80 + iStack_70 * 0x16c + 0x7c);
  *(float *)(iStack_80 + iStack_70 * 0x16c + 0x184) = *pfRam0040ab1c;
  *(float *)(iStack_80 + iStack_70 * 0x16c + 0x188) =
       (pfRam0040ab1c[1] + pfRam0040ab1c[3]) - fStack_98;
  *(float *)(iStack_80 + iStack_70 * 0x16c + 0x18c) = pfRam0040ab1c[2];
  *(float *)(iStack_80 + iStack_70 * 0x16c + 400) = fStack_98;
  SetMark__10ScrollMarkFUc(*(undefined4 *)(iStack_80 + iStack_70 * 0x16c + 0x140),0);
  if (*(int *)(iStack_80 + iStack_70 * 0x16c + 0x170) < 5) {
    if (*(short *)(iStack_80 + 0xa32) == 1) {
      *(undefined2 *)(iStack_80 + 0xa32) = 2;
    }
  }
  else {
    if (*(int *)(iStack_80 + 0xb30) == 0) {
      lVar5 = __nw__FUi(0x84);
      uVar2 = 0;
      if (lVar5 != 0) {
        uVar2 = __ct__10ScrollMarkFv(lVar5);
      }
      *(undefined4 *)(iStack_80 + 0xb30) = uVar2;
      Create__10ScrollMarkFUcP10MenuWindowUc(*(undefined4 *)(iStack_80 + 0xb30),3,0,0);
      iStack_b8 = *(int *)(iStack_80 + 0xb30);
      *(undefined2 *)(iStack_b8 + 0x14) = 0x10;
      AddOT__7MenuObjFv(*(undefined4 *)(iStack_80 + 0xb30));
      *(byte *)(iStack_80 + 0x25) = *(byte *)(iStack_80 + 0x25) & 0xfd | 2;
      *(undefined2 *)(iStack_80 + 0xa32) = 1;
    }
    SetArea__10ScrollMarkFUcffff(*pfRam0040ab1c + 48.0,*(undefined4 *)(iStack_80 + iStack_70 * 0x16c + 0x17c),
                    pfRam0040ab1c[2] - 80.0,*(undefined4 *)(iStack_80 + iStack_70 * 0x16c + 0x180),
                    *(undefined4 *)(iStack_80 + 0xb30),3);
    bVar16 = 0 < iVar10;
    if (iVar10 + 4 < *(int *)(iStack_80 + iStack_70 * 0x16c + 0x170)) {
      bVar16 = bVar16 | 2;
    }
    SetMark__10ScrollMarkFUc(*(undefined4 *)(iStack_80 + 0xb30),bVar16);
  }
  if (iStack_90 != 0) {
    Open__10MenuWindowFUci(iStack_80 + iStack_70 * 0x16c + 0x7c,3,0x85);
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005d8bf0  @24@__dt__7BtlMenuFv
 * C++: @24@__dt__7BtlMenuFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int _24___dt__7BtlMenuFv(int param_1,short param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = param_1 + -0x18;
  if (iVar2 != 0) {
    *(undefined4 *)(param_1 + -4) = 0x40a810;
    *(undefined4 *)(param_1 + 8) = 0x40a820;
    for (iVar3 = 0; iVar3 < 6; iVar3 = iVar3 + 1) {
      if ((long)((ulong)*(byte *)(iVar2 + iVar3 * 0x16c + 0x30) << 0x3e) < 0) {
        Release__7MenuObjFv(iVar2 + iVar3 * 0x16c + 0x3c);
      }
      if ((long)((ulong)*(byte *)(iVar2 + iVar3 * 0x16c + 0x30) << 0x3c) < 0) {
        Release__7MenuObjFv(iVar2 + iVar3 * 0x16c + 0x7c);
      }
      if (((ulong)*(ushort *)(iVar2 + iVar3 * 0x16c + 0x30) & 0xfff) >> 4 != 0) {
        __destroy_new_array(*(undefined4 *)(iVar2 + iVar3 * 0x16c + 0x130),0x27c030);
      }
      if (*(int *)(iVar2 + iVar3 * 0x16c + 0x134) != 0) {
        __destroy_new_array(*(undefined4 *)(iVar2 + iVar3 * 0x16c + 0x134),0x27d4f0);
      }
      if (*(int *)(iVar2 + iVar3 * 0x16c + 0x13c) != 0) {
        __destroy_new_array(*(undefined4 *)(iVar2 + iVar3 * 0x16c + 0x13c),0x2661a0);
      }
      if (*(int *)(iVar2 + iVar3 * 0x16c + 0x140) != 0) {
        iVar1 = *(int *)(iVar2 + iVar3 * 0x16c + 0x140);
        if (iVar1 != 0) {
          (**(code **)(*(int *)(iVar1 + 8) + 8))(iVar1,1);
        }
      }
      if (*(int *)(iVar2 + iVar3 * 0x16c + 0x138) != 0) {
        __destroy_new_array(*(undefined4 *)(iVar2 + iVar3 * 0x16c + 0x138),0x277890);
      }
      if (*(int *)(iVar2 + iVar3 * 0x16c + 0x144) != 0) {
        __destroy_new_array(*(undefined4 *)(iVar2 + iVar3 * 0x16c + 0x144),0x28d070);
      }
      if (*(int *)(iVar2 + iVar3 * 0x16c + 0x148) != 0) {
        __destroy_new_array(*(undefined4 *)(iVar2 + iVar3 * 0x16c + 0x148),0x2766d0);
      }
      if (*(int *)(iVar2 + iVar3 * 0x16c + 0x14c) != 0) {
        __destroy_new_array(*(undefined4 *)(iVar2 + iVar3 * 0x16c + 0x14c),0x280920);
      }
    }
    if ((long)((ulong)*(byte *)(param_1 + 0xc) << 0x39) < 0) {
      Release__7MenuObjFv(param_1 + 0x8a4);
    }
    if ((*(byte *)(param_1 + 0xd) & 1) != 0) {
      Release__7MenuObjFv(param_1 + 0x8e4);
    }
    if ((long)((ulong)*(byte *)(param_1 + 0xc) << 0x3b) < 0) {
      Release__7MenuObjFv(param_1 + 0xa1c);
    }
    if (*(int *)(param_1 + 0xb18) != 0) {
      iVar3 = *(int *)(param_1 + 0xb18);
      if (iVar3 != 0) {
        (**(code **)(*(int *)(iVar3 + 8) + 8))(iVar3,1);
      }
    }
    __dt__6CursorFv(param_1 + 0xa1c,0xffffffffffffffff);
    __dt__8MenuTextFv(param_1 + 0x998,0xffffffffffffffff);
    __dt__10MenuWindowFv(param_1 + 0x8e4,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x8a4,0xffffffffffffffff);
    __destroy_arr(param_1 + 0x18,0x58c720,0x16c,6);
    if (iVar2 != -0x18) {
      *(undefined4 *)(param_1 + 8) = 0x4049f0;
    }
    __dt__7CPolObjFv(iVar2,0);
    if (0 < param_2) {
      __dl__FPv(iVar2);
    }
  }
  return iVar2;
}

