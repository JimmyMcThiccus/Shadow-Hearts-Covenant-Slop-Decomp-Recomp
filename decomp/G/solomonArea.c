/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: solomonArea   functions: 5
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/solomonArea.md).
 */

/* JP: 0x00503110  solomonArea::solomonArea()   [__ct__11solomonAreaFv]  size=0xc8 */
int __ct__11solomonAreaFv(int param_1)

{
  int iVar1;
  int iVar2;
  
  __ct__7CPolObjFv(param_1);
  __ct__8primFadeFv(param_1 + 0x18);
  *(undefined1 **)(param_1 + 0x14) = &__vt__11solomonArea;
  for (iVar2 = 0; iVar2 < 2; iVar2 = iVar2 + 1) {
    for (iVar1 = 0; iVar1 < 5; iVar1 = iVar1 + 1) {
      *(undefined4 *)(param_1 + iVar2 * 0x14 + iVar1 * 4 + 0x28) = 0;
    }
  }
  *(undefined4 *)(param_1 + 0x5c) = 0;
  return param_1;
}

/* JP: 0x005031e0  solomonArea::~solomonArea()   [__dt__11solomonAreaFv]  size=0x15c */
int __dt__11solomonAreaFv(int param_1,short param_2)

{
  int iVar1;
  int iVar2;
  
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 0x14) = &__vt__11solomonArea;
    Dispose__7CPollerFP7CPolObj(app__4CApp + 0x48,param_1);
    for (iVar2 = 0; iVar2 < 2; iVar2 = iVar2 + 1) {
      for (iVar1 = 0; iVar1 < 5; iVar1 = iVar1 + 1) {
        if (*(int *)(param_1 + iVar2 * 0x14 + iVar1 * 4 + 0x28) != 0) {
          DelayDeleteRequest__10primPacketFv(*(undefined4 *)(param_1 + iVar2 * 0x14 + iVar1 * 4 + 0x28));
          *(undefined4 *)(param_1 + iVar2 * 0x14 + iVar1 * 4 + 0x28) = 0;
        }
      }
    }
    __dt__8primFadeFv(param_1 + 0x18,0);
    __dt__7CPolObjFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x00503340  solomonArea::initialize(Matrix*, primLayer*, int, bool)   [initialize__11solomonAreaFP6MatrixP9primLayerib]  size=0x9c */
void initialize__11solomonAreaFP6MatrixP9primLayerib
               (int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
               undefined1 param_5)

{
  *(undefined4 *)(param_1 + 0x7c) = param_2;
  *(undefined4 *)(param_1 + 0x78) = param_3;
  *(undefined4 *)(param_1 + 0x58) = param_4;
  *(undefined1 *)(param_1 + 0x74) = param_5;
  *(undefined4 *)(param_1 + 0x50) = 3;
  *(undefined4 *)(param_1 + 0x54) = 0;
  *(undefined4 *)(param_1 + 0x6c) = 0;
  *(undefined4 *)(param_1 + 0x70) = 0;
  Entry__7CPollerFP7CPolObjib(app__4CApp + 0x48,param_1,0x80,0);
  return;
}

/* JP: 0x005033e0  solomonArea::setArea(int, bool, bool)   [setArea__11solomonAreaFibb]  size=0x94 */
void setArea__11solomonAreaFibb(int param_1,int param_2,undefined1 param_3,char param_4)

{
  if ((param_2 != *(int *)(param_1 + 0x58)) || (param_4 != '\0')) {
    *(int *)(param_1 + 0x58) = param_2;
    *(undefined1 *)(param_1 + 0x74) = param_3;
    *(uint *)(param_1 + 0x5c) = *(uint *)(param_1 + 0x5c) ^ 1;
    if (*(int *)(param_1 + 0x50) != 4) {
      *(undefined4 *)(param_1 + 0x50) = 4;
      *(undefined4 *)(param_1 + 0x54) = 0;
    }
  }
  return;
}

/* JP: 0x00503480  solomonArea::Polling()   [Polling__11solomonAreaFv]  size=0x920 */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 Polling__11solomonAreaFv(int param_1)

{
  undefined8 uVar1;
  undefined4 uVar2;
  long lVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int *piVar7;
  undefined8 *puVar8;
  int aiStack_320 [180];
  int aiStack_50 [4];
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  float fStack_28;
  float fStack_24;
  int iStack_20;
  uint uStack_1c;
  float fStack_18;
  float fStack_14;
  int iStack_10;
  
  aiStack_50[0] = (int)__6057;
  aiStack_50[1] = (int)((ulong)__6057 >> 0x20);
  aiStack_50[2] = DAT_005549d8;
  aiStack_50[3] = DAT_005549dc;
  uStack_40 = DAT_005549e0;
  uStack_3c = DAT_005549e4;
  uStack_38 = DAT_005549e8;
  uStack_34 = DAT_005549ec;
  uStack_30 = DAT_005549f0;
  puVar8 = (undefined8 *)&_6059;
  piVar7 = aiStack_320;
  iVar6 = 0x2d;
  iStack_10 = param_1;
  do {
    uVar1 = *puVar8;
    iVar4 = *(int *)(puVar8 + 1);
    iVar5 = *(int *)((int)puVar8 + 0xc);
    puVar8 = puVar8 + 2;
    iVar6 = iVar6 + -1;
    *piVar7 = (int)uVar1;
    piVar7[1] = (int)((ulong)uVar1 >> 0x20);
    piVar7[2] = iVar4;
    piVar7[3] = iVar5;
    piVar7 = piVar7 + 4;
  } while (0 < iVar6);
  fStack_14 = (float)fadePolling__8primFadeFv(iStack_10 + 0x18);
  fStack_18 = fStack_14;
  if (*(int *)(iStack_10 + 0x50) != 3) {
    if (*(int *)(iStack_10 + 0x50) != 4) goto LAB_00503bd0;
    *(int *)(iStack_10 + 0x54) = *(int *)(iStack_10 + 0x54) + 1;
    if (0xf < *(int *)(iStack_10 + 0x54)) {
      uStack_1c = *(uint *)(iStack_10 + 0x5c) ^ 1;
      for (iVar6 = 0; iVar6 < aiStack_50[*(int *)(iStack_10 + uStack_1c * 4 + 0x60)] + 1;
          iVar6 = iVar6 + 1) {
        if (*(int *)(iStack_10 + uStack_1c * 0x14 + iVar6 * 4 + 0x28) != 0) {
          DelayDeleteRequest__10primPacketFv(*(undefined4 *)(iStack_10 + uStack_1c * 0x14 + iVar6 * 4 + 0x28));
          *(undefined4 *)(iStack_10 + uStack_1c * 0x14 + iVar6 * 4 + 0x28) = 0;
        }
      }
    }
    fStack_14 = fStack_14 * ((float)(0x10 - *(int *)(iStack_10 + 0x54)) / 16.0);
  }
  if (*(int *)(iStack_10 + *(int *)(iStack_10 + 0x5c) * 0x14 + 0x28) == 0) {
    *(undefined4 *)(iStack_10 + *(int *)(iStack_10 + 0x5c) * 4 + 0x60) =
         *(undefined4 *)(iStack_10 + 0x58);
    *(undefined1 *)(iStack_10 + *(int *)(iStack_10 + 0x5c) + 0x68) =
         *(undefined1 *)(iStack_10 + 0x74);
    if (*(char *)(iStack_10 + 0x74) == '\0') {
      iStack_20 = *(int *)(iStack_10 + *(int *)(iStack_10 + 0x5c) * 4 + 0x60) * 0x14;
      lVar3 = __nw__FUi(0x150);
      uVar2 = 0;
      if (lVar3 != 0) {
        uVar2 = __ct__10primSpriteFb(lVar3,1);
      }
      *(undefined4 *)(iStack_10 + *(int *)(iStack_10 + 0x5c) * 0x14 + 0x28) = uVar2;
      setDisp__10primPacketFP9primLayeriffff((float)aiStack_320[iStack_20],(float)aiStack_320[iStack_20 + 1],0x40000000,
                      0x40000000,
                      *(undefined4 *)(iStack_10 + *(int *)(iStack_10 + 0x5c) * 0x14 + 0x28),
                      *(undefined4 *)(iStack_10 + 0x78),
                      *(int *)(iStack_10 + *(int *)(iStack_10 + 0x5c) * 4 + 0x60) + 4);
      setRGBA__10primPacketFiiii(*(undefined4 *)(iStack_10 + *(int *)(iStack_10 + 0x5c) * 0x14 + 0x28),0x80,
                      0x80,0x80,0);
    }
    else {
      iVar6 = *(int *)(iStack_10 + *(int *)(iStack_10 + 0x5c) * 4 + 0x60);
      iVar4 = iVar6 * 0x14;
      lVar3 = __nw__FUi(0x150);
      uVar2 = 0;
      if (lVar3 != 0) {
        uVar2 = __ct__10primSpriteFb(lVar3,0);
      }
      *(undefined4 *)(iStack_10 + *(int *)(iStack_10 + 0x5c) * 0x14 + 0x28) = uVar2;
      setDisp__10primPacketFP9primLayeriffff((float)aiStack_320[iVar6 * 0x14],(float)aiStack_320[iVar4 + 1],0x3f800000,
                      0x3f800000,
                      *(undefined4 *)(iStack_10 + *(int *)(iStack_10 + 0x5c) * 0x14 + 0x28),
                      *(undefined4 *)(iStack_10 + 0x78),4);
      setSize__10primPacketFii(*(undefined4 *)(iStack_10 + *(int *)(iStack_10 + 0x5c) * 0x14 + 0x28),
                      aiStack_320[iVar4 + 2],aiStack_320[iVar4 + 3]);
    }
    setParent__10primPacketFP6Matrix(*(undefined4 *)(iStack_10 + *(int *)(iStack_10 + 0x5c) * 0x14 + 0x28),
                    *(undefined4 *)(iStack_10 + 0x7c));
    for (iVar6 = 1; iVar6 <= aiStack_50[*(int *)(iStack_10 + 0x58)]; iVar6 = iVar6 + 1) {
      iVar4 = iVar6 + *(int *)(iStack_10 + *(int *)(iStack_10 + 0x5c) * 4 + 0x60) * 5;
      iVar5 = iVar4 * 4;
      lVar3 = __nw__FUi(0x150);
      uVar2 = 0;
      if (lVar3 != 0) {
        uVar2 = __ct__10primSpriteFb(lVar3,0);
      }
      *(undefined4 *)(iStack_10 + *(int *)(iStack_10 + 0x5c) * 0x14 + iVar6 * 4 + 0x28) = uVar2;
      setDisp__10primPacketFP9primLayeriffff((float)aiStack_320[iVar4 * 4],(float)aiStack_320[iVar5 + 1],0x3f800000,
                      0x3f800000,
                      *(undefined4 *)
                       (iStack_10 + *(int *)(iStack_10 + 0x5c) * 0x14 + iVar6 * 4 + 0x28),
                      *(undefined4 *)(iStack_10 + 0x78),4);
      setSize__10primPacketFii(*(undefined4 *)
                       (iStack_10 + *(int *)(iStack_10 + 0x5c) * 0x14 + iVar6 * 4 + 0x28),
                      aiStack_320[iVar5 + 2],aiStack_320[iVar5 + 3]);
      setParent__10primPacketFP6Matrix(*(undefined4 *)
                       (iStack_10 + *(int *)(iStack_10 + 0x5c) * 0x14 + iVar6 * 4 + 0x28),
                      *(undefined4 *)(iStack_10 + 0x7c));
    }
  }
  if (*(int *)(iStack_10 + 0x50) == 3) {
    *(int *)(iStack_10 + 0x54) = *(int *)(iStack_10 + 0x54) + 1;
  }
  if (0xf < *(int *)(iStack_10 + 0x54)) {
    *(undefined4 *)(iStack_10 + 0x50) = 0;
  }
  fStack_18 = fStack_18 * ((float)*(int *)(iStack_10 + 0x54) / 16.0);
LAB_00503bd0:
  if (*(int *)(iStack_10 + 0x50) != 0) {
    for (iVar6 = 0; iVar6 < 2; iVar6 = iVar6 + 1) {
      if (iVar6 == *(int *)(iStack_10 + 0x5c)) {
        fStack_24 = fStack_18;
        fStack_28 = fStack_18;
      }
      else {
        fStack_24 = fStack_14;
        fStack_28 = fStack_14;
      }
      if (*(int *)(iStack_10 + iVar6 * 0x14 + 0x28) != 0) {
        fStack_28 = fStack_24;
        for (iVar4 = 0; iVar4 < aiStack_50[*(int *)(iStack_10 + iVar6 * 4 + 0x60)] + 1;
            iVar4 = iVar4 + 1) {
          if ((iVar4 == 0) && (*(char *)(iStack_10 + iVar6 + 0x68) == '\0')) {
            setRGBA__10primPacketFiiii(*(undefined4 *)(iStack_10 + iVar6 * 0x14 + 0x28),0,0,0,
                            (int)(fStack_24 * 48.0));
          }
          else {
            setRGBA__10primPacketFiiii(*(undefined4 *)(iStack_10 + iVar6 * 0x14 + iVar4 * 4 + 0x28),0,0,0,
                            (int)(fStack_24 * 48.0));
          }
        }
      }
    }
  }
  return 0;
}
