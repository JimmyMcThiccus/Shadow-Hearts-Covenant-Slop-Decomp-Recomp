/* decomp/H/BMesWin.c — cleaned Ghidra output (SH2JP_BATTLE.BIN, JP Furokuban, base 0x00430a00).
 * 7 function(s). Types: see types.h. Names/gp globals resolved from symbols/SLPM_602.19.syms. */
#include "types.h"

/* ---------------------------------------------------------------------------
 * JP: 0x005d6a10  __ct__7BMesWinFiiiPci
 * C++: BMesWin::__ct(int, int, int, char *, int)
 * size: 0x114 bytes
 * --------------------------------------------------------------------------- */
int __ct__7BMesWinFiiiPci
              (int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
              undefined4 param_5,undefined4 param_6)

{
  __ct__7CPolObjFv(param_1);
  *(undefined4 *)(param_1 + 0x18) = 0;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  *(undefined4 *)(param_1 + 0x20) = 0x4049f0;
  *(undefined4 *)(param_1 + 0x14) = 0x40a7f0;
  *(undefined4 *)(param_1 + 0x20) = 0x40a800;
  __ct__8FontDrawFv(param_1 + 0x40);
  __ct__10MenuWindowFv(param_1 + 0x80);
  *(undefined2 *)(param_1 + 0x30) = 0;
  *(undefined4 *)(param_1 + 0x2c) = param_2;
  *(undefined2 *)(param_1 + 0x32) = 0;
  *(undefined2 *)(param_1 + 0x34) = 0;
  *(undefined4 *)(param_1 + 0x134) = 0;
  Entry__7CPollerFP7CPolObjib(iGpffff858c + 0x48,param_1,0x80,0);
  BMesWinEntry__7BtlMenuFP7BMesWin(param_1);
  Create__7BMesWinFiiPci(param_1,param_3,param_4,param_5,param_6);
  return param_1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005d6b30  __dt__7BMesWinFv
 * C++: BMesWin::__dt()
 * size: 0x19c bytes
 * --------------------------------------------------------------------------- */
int __dt__7BMesWinFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0x14) = 0x40a7f0;
    *(undefined4 *)(param_1 + 0x20) = 0x40a800;
    if ((long)((ulong)*(byte *)(param_1 + 0x30) << 0x3e) < 0) {
      Release__7MenuObjFv(param_1 + 0x40);
    }
    if ((long)((ulong)*(byte *)(param_1 + 0x30) << 0x3c) < 0) {
      Release__7MenuObjFv(param_1 + 0x80);
    }
    if (((ulong)*(ushort *)(param_1 + 0x30) & 0xfff) >> 4 != 0) {
      __destroy_new_array(*(undefined4 *)(param_1 + 0x134),0x273e20);
    }
    if (pcGpffff86ec != (code *)0x0) {
      (*pcGpffff86ec)(0x18,*(undefined4 *)(param_1 + 0x2c),0,0,0,0,uGpffff86e8);
      BMesWinRelease__7BtlMenuFP7BMesWin(param_1);
    }
    __dt__10MenuWindowFv(param_1 + 0x80,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x40,0xffffffffffffffff);
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
 * JP: 0x005d6cd0  Destruct__7BMesWinFv
 * C++: BMesWin::Destruct()
 * size: 0xe0 bytes
 * --------------------------------------------------------------------------- */
void Destruct__7BMesWinFv(int param_1)

{
  if ((*(byte *)(param_1 + 0x30) & 1) != 0) {
    ReleaseOT__7MenuObjFv(param_1 + 0x40);
    *(byte *)(param_1 + 0x30) = *(byte *)(param_1 + 0x30) & 0xfe;
  }
  if ((long)((ulong)*(byte *)(param_1 + 0x30) << 0x3d) < 0) {
    ReleaseOT__7MenuObjFv(param_1 + 0x80);
    *(byte *)(param_1 + 0x30) = *(byte *)(param_1 + 0x30) & 0xfb;
  }
  Dispose__7CPollerFP7CPolObj(iGpffff858c + 0x48,param_1);
  (**(code **)(*(int *)(param_1 + 0x20) + 0xc))();
  BMesWinRelease__7BtlMenuFP7BMesWin(param_1);
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005d6db0  Polling__7BMesWinFv
 * C++: BMesWin::Polling()
 * size: 0x36c bytes
 * --------------------------------------------------------------------------- */
undefined4 Polling__7BMesWinFv(int param_1)

{
  ushort uVar1;
  short sVar2;
  float fStack_14;
  
  fStack_14 = *(float *)(iGpffff86b4 + 0x38);
  if ((*(byte *)(iGpffff86b4 + 0x24) & 1) != 0) {
    fStack_14 = 0.0;
  }
  uVar1 = *(ushort *)(*(int *)(*(int *)(g_86c0 + 4) * 4 + 0x40ac00) + 0x6c);
  sVar2 = *(short *)(param_1 + 0x32);
  if (sVar2 == 2) {
    if (*(char *)(param_1 + 0x128) == '\0') {
      if ((*(byte *)(param_1 + 0x30) & 1) != 0) {
        ReleaseOT__7MenuObjFv(param_1 + 0x40);
        *(byte *)(param_1 + 0x30) = *(byte *)(param_1 + 0x30) & 0xfe;
      }
      if ((long)((ulong)*(byte *)(param_1 + 0x30) << 0x3d) < 0) {
        ReleaseOT__7MenuObjFv(param_1 + 0x80);
        *(byte *)(param_1 + 0x30) = *(byte *)(param_1 + 0x30) & 0xfb;
      }
      (**(code **)(*(int *)(param_1 + 0x20) + 0xc))();
      return 1;
    }
  }
  else {
    if (sVar2 != 1) {
      if (sVar2 != 0) {
        return 0;
      }
      if (*(char *)(param_1 + 0x128) != '\x01') {
        return 0;
      }
      *(undefined2 *)(param_1 + 0x32) = 1;
      *(undefined2 *)(param_1 + 0x34) = 0;
      *(undefined4 *)(param_1 + 0x38) = 0;
    }
    sVar2 = *(short *)(param_1 + 0x3c);
    if (sVar2 == 3) {
      *(float *)(param_1 + 0x38) = *(float *)(param_1 + 0x38) + fStack_14;
      if ((2.0 <= *(float *)(param_1 + 0x38)) || ((uVar1 & 0xf000) != 0)) {
        SetClose__7BMesWinFv(param_1);
      }
    }
    else if (sVar2 == 2) {
      *(float *)(param_1 + 0x38) = *(float *)(param_1 + 0x38) + fStack_14;
      if (2.0 <= *(float *)(param_1 + 0x38)) {
        SetClose__7BMesWinFv(param_1);
      }
    }
    else if ((sVar2 == 1) && ((uVar1 & 0xf000) != 0)) {
      SetClose__7BMesWinFv(param_1);
    }
  }
  return 0;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005d7120  Create__7BMesWinFiiPci
 * C++: BMesWin::Create(int, int, char *, int)
 * size: 0x948 bytes
 * --------------------------------------------------------------------------- */
void Create__7BMesWinFiiPci
               (int param_1,undefined2 param_2,uint param_3,char *param_4,undefined2 param_5)

{
  short sVar1;
  bool bVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  float fVar8;
  float fStack_5c;
  float fStack_58;
  
  bVar2 = false;
  *(undefined2 *)(param_1 + 0x3c) = param_2;
  *(undefined2 *)(param_1 + 0x3e) = param_5;
  *(undefined2 *)(param_1 + 0x32) = 0;
  *(undefined2 *)(param_1 + 0x34) = 0;
  *(undefined2 *)(param_1 + 0x36) = 0;
  *(undefined4 *)(param_1 + 0x38) = 0;
  Create__8FontDrawF6GS_PSMUsUsUcUiP10ClutRaster(param_1 + 0x40,0x2c,0x280,0x40,0,0,0);
  *(byte *)(param_1 + 0x30) = *(byte *)(param_1 + 0x30) & 0xfd | 2;
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x98,param_1 + 0x40);
  *(undefined2 *)(param_1 + 0x94) = 1;
  AddOT__7MenuObjFv(param_1 + 0x80);
  *(byte *)(param_1 + 0x30) = *(byte *)(param_1 + 0x30) & 0xfb | 4;
  sVar1 = *(short *)(param_1 + 0x3e);
  if (sVar1 == 5) {
    Create__10MenuWindowFUcUcffff(*(undefined4 *)(iRam0040ab1c + 0x40),*(undefined4 *)(iRam0040ab1c + 0x44),
                    *(undefined4 *)(iRam0040ab1c + 0x48),*(undefined4 *)(iRam0040ab1c + 0x4c),
                    param_1 + 0x80,5,1);
    if (*(int *)(param_1 + 0xbc) != 0) {
      (**(code **)(*(int *)(*(int *)(param_1 + 0xbc) + 8) + 0x2c))(*(int *)(param_1 + 0xbc),0,0,0);
    }
    SetAlpha__10MenuWindowFUc(param_1 + 0x80,0x60);
  }
  else if (sVar1 == 4) {
    Create__10MenuWindowFUcUcffff(0x43800000,0x43600000,0x41800000,0x41a00000,param_1 + 0x80,0,1);
  }
  else if (((sVar1 == 3) || (sVar1 == 2)) || (sVar1 == 1)) {
    Create__10MenuWindowFUcUcffff(0x43800000,0x43600000,0x41800000,0x41a00000,param_1 + 0x80,7,1);
  }
  else if ((int)param_3 < 2) {
    Create__10MenuWindowFUcUcffff(0x43800000,0x43600000,0x41800000,0x41a00000,param_1 + 0x80,7,1);
  }
  else {
    Create__10MenuWindowFUcUcffff(0x43800000,0x43600000,0x41800000,0x41a00000,param_1 + 0x80,6,1);
    bVar2 = true;
  }
  *(byte *)(param_1 + 0x30) = *(byte *)(param_1 + 0x30) & 0xf7 | 8;
  if (((ulong)*(ushort *)(param_1 + 0x30) & 0xfff) >> 4 == 0) {
    uVar4 = __nwa__FUi(param_3 * 0x80 + 0x10);
    uVar3 = __construct_new_array(uVar4,0x27bfd0,0x27c030,0x80,param_3);
    *(undefined4 *)(param_1 + 0x134) = uVar3;
    *(ushort *)(param_1 + 0x30) =
         *(ushort *)(param_1 + 0x30) & 0xf00f | (ushort)((param_3 & 0xff) << 4);
  }
  iVar7 = *(int *)(param_1 + 0x134);
  fStack_58 = 0.0;
  fStack_5c = 0.0;
  for (iVar6 = 0; iVar6 < (int)param_3; iVar6 = iVar6 + 1) {
    Create__8MenuTextFUcUc(iVar7 + iVar6 * 0x80,1,2);
    *(undefined2 *)(iVar7 + iVar6 * 0x80 + 0x14) = 1;
    SetMessage__8MenuTextFPcUiUcUc(iVar7 + iVar6 * 0x80,param_4,0,0,1);
    *(undefined1 *)(iVar7 + iVar6 * 0x80 + 0x5a) = 1;
    *(undefined1 *)(iVar7 + iVar6 * 0x80 + 0x5b) = 0;
    *(undefined2 *)(iVar7 + iVar6 * 0x80 + 0x1c) = 0;
    *(short *)(iVar7 + iVar6 * 0x80 + 0x1e) = (short)iVar6;
    (**(code **)(*(int *)(iVar7 + iVar6 * 0x80 + 8) + 0x24))(0,fStack_5c);
    iVar5 = iVar7 + iVar6 * 0x80;
    *(byte *)(iVar5 + 0x12) = *(byte *)(iVar5 + 0x12) & 0xfe | 1;
    OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(param_1 + 0x40,iVar7 + iVar6 * 0x80,1,0);
    AddPlace__10MenuWindowFP9MenuPlace(param_1 + 0x80,iVar7 + iVar6 * 0x80);
    fVar8 = *(float *)(iVar7 + iVar6 * 0x80 + 0x2c);
    if (fVar8 <= fStack_58) {
      fVar8 = fStack_58;
    }
    fStack_58 = fVar8;
    fStack_5c = fStack_5c + 20.0;
    for (; *param_4 != '\0'; param_4 = param_4 + 1) {
    }
    param_4 = param_4 + 1;
  }
  if ((bVar2) && (fStack_5c < 60.0)) {
    fStack_5c = 60.0;
  }
  switch(*(undefined2 *)(param_1 + 0x3e)) {
  case 0:
    SetPosition__10MenuWindowFff(256.0 - fStack_58 / 2.0,224.0 - fStack_5c / 2.0,param_1 + 0x80);
    SetSize__10MenuWindowFff(fStack_58,fStack_5c,param_1 + 0x80);
    break;
  case 1:
    SetPosition__10MenuWindowFff(256.0 - fStack_58 / 2.0,0x41800000,param_1 + 0x80);
    SetSize__10MenuWindowFff(fStack_58,fStack_5c,param_1 + 0x80);
    break;
  case 2:
    SetPosition__10MenuWindowFff(512.0 - (fStack_58 + 12.8 + 8.0),0x41800000,param_1 + 0x80);
    SetSize__10MenuWindowFff(fStack_58,fStack_5c,param_1 + 0x80);
    break;
  case 3:
    if (fStack_58 < 128.0) {
      fStack_58 = 128.0;
    }
    uVar4 = SetPosition__10MenuWindowFff(512.0 - (fStack_58 + 12.8 + 8.0),0x41800000,param_1 + 0x80);
    SetSize__10MenuWindowFff(fStack_58,fStack_5c,param_1 + 0x80,uVar4);
    for (iVar6 = 0; iVar6 < (int)param_3; iVar6 = iVar6 + 1) {
      (**(code **)(*(int *)(iVar7 + iVar6 * 0x80 + 8) + 0x24))
                ((fStack_58 - *(float *)(iVar7 + iVar6 * 0x80 + 0x2c)) / 2.0,(float)iVar6 * 20.0);
    }
    break;
  case 4:
    SetPosition__10MenuWindowFff(0x43900000,0x439c6666,param_1 + 0x80);
    SetSize__10MenuWindowFff(fStack_58,fStack_5c,param_1 + 0x80);
    break;
  case 5:
    for (iVar7 = 0; iVar7 < (int)param_3; iVar7 = iVar7 + 1) {
      (**(code **)(*(int *)(*(int *)(param_1 + 0x134) + iVar7 * 0x54 + 8) + 0x24))
                (*(undefined4 *)(iRam0040ab1c + 0x50),0x3f800000);
    }
  }
  Open__10MenuWindowFUci(param_1 + 0x80,0,0x85);
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005d7a70  SetClose__7BMesWinFv
 * C++: BMesWin::SetClose()
 * size: 0x60 bytes
 * --------------------------------------------------------------------------- */
void SetClose__7BMesWinFv(int param_1)

{
  if (*(short *)(param_1 + 0x32) != 2) {
    Close__10MenuWindowFUci(param_1 + 0x80,0,0x85);
    *(undefined2 *)(param_1 + 0x32) = 2;
    *(undefined2 *)(param_1 + 0x34) = 0;
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005d8c00  @24@__dt__7BMesWinFv
 * C++: @24@__dt__7BMesWinFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int _24___dt__7BMesWinFv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x18;
  if (iVar1 != 0) {
    *(undefined4 *)(param_1 + -4) = 0x40a7f0;
    *(undefined4 *)(param_1 + 8) = 0x40a800;
    if ((long)((ulong)*(byte *)(param_1 + 0x18) << 0x3e) < 0) {
      Release__7MenuObjFv(param_1 + 0x28);
    }
    if ((long)((ulong)*(byte *)(param_1 + 0x18) << 0x3c) < 0) {
      Release__7MenuObjFv(param_1 + 0x68);
    }
    if (((ulong)*(ushort *)(param_1 + 0x18) & 0xfff) >> 4 != 0) {
      __destroy_new_array(*(undefined4 *)(param_1 + 0x11c),0x273e20);
    }
    if (pcGpffff86ec != (code *)0x0) {
      (*pcGpffff86ec)(0x18,*(undefined4 *)(param_1 + 0x14),0,0,0,0,uGpffff86e8);
      BMesWinRelease__7BtlMenuFP7BMesWin(iVar1);
    }
    __dt__10MenuWindowFv(param_1 + 0x68,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x28,0xffffffffffffffff);
    if (iVar1 != -0x18) {
      *(undefined4 *)(param_1 + 8) = 0x4049f0;
    }
    __dt__7CPolObjFv(iVar1,0);
    if (0 < param_2) {
      __dl__FPv(iVar1);
    }
  }
  return iVar1;
}

