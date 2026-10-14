/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: dRoll   functions: 6
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/dRoll.md).
 */

/* JP: 0x004f18c0  dRoll::dRoll()   [__ct__5dRollFv]  size=0xa8 */
int __ct__5dRollFv(int param_1)

{
  int iVar1;
  
  __ct__7CPolObjFv(param_1);
  *(undefined4 *)(param_1 + 0x18) = 0;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  *(undefined1 **)(param_1 + 0x20) = &__vt__17DelayDeleteObject;
  *(undefined1 **)(param_1 + 0x14) = &__vt__5dRoll;
  *(undefined4 *)(param_1 + 0x20) = 0x4097e0;
  for (iVar1 = 0; iVar1 < 10; iVar1 = iVar1 + 1) {
    *(undefined4 *)(param_1 + iVar1 * 4 + 0x34) = 0;
  }
  return param_1;
}

/* JP: 0x004f1970  dRoll::~dRoll()   [__dt__5dRollFv]  size=0x128 */
int __dt__5dRollFv(int param_1,short param_2)

{
  int iVar1;
  
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 0x14) = &__vt__5dRoll;
    *(undefined4 *)(param_1 + 0x20) = 0x4097e0;
    Dispose__7CPollerFP7CPolObj(app__4CApp + 0x48,param_1);
    for (iVar1 = 0; iVar1 < 3; iVar1 = iVar1 + 1) {
      if (*(int *)(param_1 + iVar1 * 4 + 0x34) != 0) {
        DelayDeleteRequest__6prim2DFv(*(undefined4 *)(param_1 + iVar1 * 4 + 0x34));
        *(undefined4 *)(param_1 + iVar1 * 4 + 0x34) = 0;
      }
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

/* JP: 0x004f1aa0  dRoll::start()   [start__5dRollFv]  size=0x1f8 */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void start__5dRollFv(int param_1)

{
  undefined4 uVar1;
  long lVar2;
  int iVar3;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined8 uStack_20;
  int iStack_10;
  
  uStack_40 = (undefined4)__6419;
  uStack_3c = (undefined4)((ulong)__6419 >> 0x20);
  uStack_38 = DAT_00554338;
  uStack_34 = DAT_0055433c;
  uStack_30 = DAT_00554340;
  uStack_2c = DAT_00554344;
  uStack_28 = DAT_00554348;
  uStack_24 = DAT_0055434c;
  uStack_20 = DAT_00554350;
  *(undefined4 *)(param_1 + 0x28) = 0;
  *(undefined1 *)(param_1 + 0x2c) = 0;
  *(undefined4 *)(param_1 + 0x30) = 0;
  iStack_10 = param_1;
  for (iVar3 = 0; iVar3 < 3; iVar3 = iVar3 + 1) {
    lVar2 = __nw__FUi(0x260);
    uVar1 = 0;
    if (lVar2 != 0) {
      uVar1 = __ct__6prim2DFi(lVar2,0xd);
    }
    *(undefined4 *)(iStack_10 + iVar3 * 4 + 0x34) = uVar1;
    *(undefined4 *)(*(int *)(iStack_10 + iVar3 * 4 + 0x34) + 0x30) = m_pBuffer;
    setDisp__6prim2DFiffff(0x433e0000,0x43600000,0x3fc00000,0x3fc00000,
                    *(undefined4 *)(iStack_10 + iVar3 * 4 + 0x34),6);
    setBlendMode__6prim2DFi(*(undefined4 *)(iStack_10 + iVar3 * 4 + 0x34),1);
    setRGBA__6prim2DFiiii(*(undefined4 *)(iStack_10 + iVar3 * 4 + 0x34),
                    *(undefined1 *)(&uStack_40 + iVar3),
                    *(undefined1 *)((int)&uStack_40 + iVar3 * 4 + 1),
                    *(undefined1 *)((int)&uStack_40 + iVar3 * 4 + 2),
                    *(undefined1 *)((int)&uStack_40 + iVar3 * 4 + 3));
    fadein__8primFadeFi(*(int *)(iStack_10 + iVar3 * 4 + 0x34) + 0x20,0x1e);
  }
  Entry__7CPollerFP7CPolObjib(app__4CApp + 0x48,iStack_10,0x80,0);
  return;
}

/* JP: 0x004f1ca0  dRoll::stop()   [stop__5dRollFv]  size=0x74 */
void stop__5dRollFv(int param_1)

{
  int iVar1;
  
  for (iVar1 = 0; iVar1 < 3; iVar1 = iVar1 + 1) {
    fadeout__8primFadeFi(*(int *)(param_1 + iVar1 * 4 + 0x34) + 0x20,0x1e);
  }
  *(undefined1 *)(param_1 + 0x2c) = 1;
  return;
}

/* JP: 0x004f1d20  dRoll::Polling()   [Polling__5dRollFv]  size=0x380 */
undefined8 Polling__5dRollFv(int param_1)

{
  undefined8 uVar1;
  long lVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
  *(float *)(param_1 + 0x30) = *(float *)(param_1 + 0x30) + 0.08;
  uVar1 = fptodp(*(undefined4 *)(param_1 + 0x30));
  uVar1 = sin(uVar1);
  uVar1 = dpmul(0x404e000000000000,uVar1);
  uVar1 = dpadd(0x4050000000000000,uVar1);
  uVar3 = dptofp(uVar1);
  uVar1 = fptodp(*(undefined4 *)(param_1 + 0x30));
  uVar1 = cos(uVar1);
  uVar1 = dpmul(0x404e000000000000,uVar1);
  uVar1 = dpadd(0x4061800000000000,uVar1);
  uVar4 = dptofp(uVar1);
  setPos__6prim2DFff(uVar3,uVar4,*(undefined4 *)(param_1 + 0x34));
  uVar1 = fptodp((*(float *)(param_1 + 0x30) * 5.0) / 4.0 + 1.0471973);
  uVar1 = sin(uVar1);
  uVar1 = dpmul(0x404e000000000000,uVar1);
  uVar1 = dpadd(0x4064c00000000000,uVar1);
  uVar3 = dptofp(uVar1);
  uVar1 = fptodp(*(float *)(param_1 + 0x30) / 2.0 - 1.0471973);
  uVar1 = cos(uVar1);
  uVar1 = dpmul(0x404e000000000000,uVar1);
  uVar1 = dpadd(0x4064000000000000,uVar1);
  uVar4 = dptofp(uVar1);
  setPos__6prim2DFff(uVar3,uVar4,*(undefined4 *)(param_1 + 0x38));
  uVar1 = fptodp((-*(float *)(param_1 + 0x30) * 3.0) / 4.0 - 3.141592);
  uVar1 = sin(uVar1);
  uVar1 = dpmul(0x404e000000000000,uVar1);
  uVar1 = dpadd(0x4058000000000000,uVar1);
  uVar3 = dptofp(uVar1);
  uVar1 = fptodp((-*(float *)(param_1 + 0x30) * 4.0) / 3.0);
  uVar1 = cos(uVar1);
  uVar1 = dpmul(0x404e000000000000,uVar1);
  uVar1 = dpadd(0x4059000000000000,uVar1);
  uVar4 = dptofp(uVar1);
  setPos__6prim2DFff(uVar3,uVar4,*(undefined4 *)(param_1 + 0x3c));
  if ((*(char *)(param_1 + 0x2c) != '\0') &&
     (lVar2 = isFade__8primFadeFv(*(int *)(param_1 + 0x34) + 0x20), lVar2 == 0)) {
    (**(code **)(*(int *)(param_1 + 0x20) + 0xc))();
  }
  return 0;
}

/* JP: 0x004f20b0  dRoll::~dRoll()   [@24@__dt__5dRollFv]  size=0x8 */
int _24___dt__5dRollFv(int param_1,short param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = param_1 + -0x18;
  if (iVar1 != 0) {
    *(undefined1 **)(param_1 + -4) = &__vt__5dRoll;
    *(undefined4 *)(param_1 + 8) = 0x4097e0;
    Dispose__7CPollerFP7CPolObj(app__4CApp + 0x48,iVar1);
    for (iVar2 = 0; iVar2 < 3; iVar2 = iVar2 + 1) {
      if (*(int *)(iVar1 + iVar2 * 4 + 0x34) != 0) {
        DelayDeleteRequest__6prim2DFv(*(undefined4 *)(iVar1 + iVar2 * 4 + 0x34));
        *(undefined4 *)(iVar1 + iVar2 * 4 + 0x34) = 0;
      }
    }
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
