/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: worldMapThm   functions: 8
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/worldMapThm.md).
 */

/* JP: 0x0050b810  worldMapThm::worldMapThm()   [__ct__11worldMapThmFv]  size=0x28 */
undefined4 * __ct__11worldMapThmFv(undefined4 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  return param_1;
}

/* JP: 0x0050b840  worldMapThm::~worldMapThm()   [__dt__11worldMapThmFv]  size=0x5c */
int __dt__11worldMapThmFv(int param_1,short param_2)

{
  if ((param_1 != 0) && (mReleaseThmWin__11worldMapThmFv(param_1), 0 < param_2)) {
    __dl__FPv(param_1);
  }
  return param_1;
}

/* JP: 0x0050b8a0  worldMapThm::initialize(primTex*)   [initialize__11worldMapThmFP7primTex]  size=0x24 */
void initialize__11worldMapThmFP7primTex(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 8) = param_2;
  return;
}

/* JP: 0x0050b8d0  worldMapThm::dispThm(int, unsigned char*, unsigned char*)   [dispThm__11worldMapThmFiPUcPUc]  size=0x74 */
void dispThm__11worldMapThmFiPUcPUc(int *param_1,int param_2,int param_3,int param_4)

{
  param_1[3] = param_2;
  param_1[4] = param_3;
  param_1[5] = param_4;
  if (*param_1 != 0) {
    mReleaseThmWin__11worldMapThmFv(param_1);
  }
  mSetupThmWin__11worldMapThmFv(param_1);
  return;
}

/* JP: 0x0050b950  worldMapThm::fadeout()   [fadeout__11worldMapThmFv]  size=0x58 */
void fadeout__11worldMapThmFv(int *param_1)

{
  if (*param_1 != 0) {
    fadeout__7primWinFi(*param_1,8);
    fadeout__7primWinFi(param_1[1],8);
  }
  return;
}

/* JP: 0x0050b9b0  worldMapThm::kill()   [kill__11worldMapThmFv]  size=0x28 */
void kill__11worldMapThmFv(undefined4 param_1)

{
  mReleaseThmWin__11worldMapThmFv(param_1);
  return;
}

/* JP: 0x0050b9e0  worldMapThm::mSetupThmWin()   [mSetupThmWin__11worldMapThmFv]  size=0x3fc */
void mSetupThmWin__11worldMapThmFv(undefined4 *param_1)

{
  undefined4 uVar1;
  long lVar2;
  undefined8 uVar3;
  ulong uVar4;
  int iVar5;
  
  lVar2 = __nw__FUi(0x148);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = __ct__7primWinFv(lVar2);
  }
  *param_1 = uVar1;
  uVar1 = *param_1;
  initialize__7primWinFP7primTex(uVar1,param_1[2]);
  setItem__7primWinFiii(uVar1,1,1,0);
  setTex__7primWinFiiii(uVar1,param_1[3] + 10,0,0,0);
  createTexPoly__7primWinFiiiiii(uVar1,0,0,0x38,0x35,0,0);
  buildWin__7primWinFiiiiii(uVar1,2,0,0,0,0,0);
  fadein__7primWinFi(*param_1,8);
  lVar2 = __nw__FUi(0x148);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = __ct__7primWinFv(lVar2);
  }
  param_1[1] = uVar1;
  uVar1 = param_1[1];
  initialize__7primWinFP7primTex(uVar1,param_1[2]);
  setItem__7primWinFiii(uVar1,1,0,2);
  setTextArea__7primWinFiiib(uVar1,0,0x200,0x40,1);
  createText__7primWinFiiiiPciib(uVar1,0,0,0x18,0xd0,param_1[4],0,1);
  uVar3 = getPT__7primWinFi(uVar1,0);
  iVar5 = (int)uVar3;
  (**(code **)(*(int *)(iVar5 + 8) + 0x24))
            ((float)(int)(128.0 - *(float *)(iVar5 + 0x2c) / 2.0),0x43500000);
  SetCSA__8FontItemFUc(uVar3,0xc);
  *(undefined1 *)(iVar5 + 100) = 0x30;
  *(undefined1 *)(iVar5 + 0x65) = 0x28;
  *(undefined1 *)(iVar5 + 0x66) = 0x20;
  uVar4 = (ulong)*(byte *)(iVar5 + 0x11) & 0xffffffffffffffef | 0x10;
  *(char *)(iVar5 + 0x11) = (char)uVar4;
  *(byte *)(iVar5 + 0x10) =
       *(byte *)(iVar5 + 0x10) & 0xef | (byte)((uint)((uVar4 << 0x3b) >> 0x3f) << 4);
  createText__7primWinFiiiiPciib(uVar1,1,0,0x18,0xe6,param_1[5],0,3);
  uVar3 = getPT__7primWinFi(uVar1,1);
  iVar5 = (int)uVar3;
  (**(code **)(*(int *)(iVar5 + 8) + 0x24))
            ((float)(int)(128.0 - *(float *)(iVar5 + 0x2c) / 2.0),0x43660000);
  SetCSA__8FontItemFUc(uVar3,0xc);
  *(undefined1 *)(iVar5 + 100) = 0x30;
  *(undefined1 *)(iVar5 + 0x65) = 0x28;
  *(undefined1 *)(iVar5 + 0x66) = 0x20;
  uVar4 = (ulong)*(byte *)(iVar5 + 0x11) & 0xffffffffffffffef | 0x10;
  *(char *)(iVar5 + 0x11) = (char)uVar4;
  *(byte *)(iVar5 + 0x10) =
       *(byte *)(iVar5 + 0x10) & 0xef | (byte)((uint)((uVar4 << 0x3b) >> 0x3f) << 4);
  buildWin__7primWinFiiiiii(uVar1,5,0,0,0,0,0);
  fadein__7primWinFi(param_1[1],8);
  return;
}

/* JP: 0x0050bde0  worldMapThm::mReleaseThmWin()   [mReleaseThmWin__11worldMapThmFv]  size=0x70 */
void mReleaseThmWin__11worldMapThmFv(int *param_1)

{
  if (*param_1 != 0) {
    DelayDeleteRequest__7primWinFv(*param_1);
    *param_1 = 0;
  }
  if (param_1[1] != 0) {
    DelayDeleteRequest__7primWinFv(param_1[1]);
    param_1[1] = 0;
  }
  return;
}
