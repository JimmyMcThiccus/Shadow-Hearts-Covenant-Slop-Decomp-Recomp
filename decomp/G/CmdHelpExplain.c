/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdHelpExplain   functions: 8
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdHelpExplain.md).
 */

/* JP: 0x0045bb60  CmdHelpExplain::CmdHelpExplain()   [__ct__14CmdHelpExplainFv]  size=0xdc */
int __ct__14CmdHelpExplainFv(int param_1)

{
  __ct__9CmdWindowFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__14CmdHelpExplain;
  *(undefined4 *)(param_1 + 0x18) = 0x4085c4;
  *(undefined4 *)(param_1 + 0x24) = 0x4085d0;
  __ct__8FontDrawFv(param_1 + 0xb8);
  __ct__8FontDrawFv(param_1 + 0xf8);
  __ct__8MenuTextFv(param_1 + 0x138);
  __ct__11MenuMessageFv(param_1 + 0x1b8);
  __ct__11MenuTextureFv(param_1 + 0x250);
  __ct__11SendOnLocalFv(param_1 + 0x290);
  __ct__10MenuSpriteFv(param_1 + 0x2c0);
  __ct__7KeyWaitFv(param_1 + 800);
  return param_1;
}

/* JP: 0x0045bc40  CmdHelpExplain::~CmdHelpExplain()   [__dt__14CmdHelpExplainFv]  size=0x134 */
int __dt__14CmdHelpExplainFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__14CmdHelpExplain;
    *(undefined4 *)(param_1 + 0x18) = 0x4085c4;
    *(undefined4 *)(param_1 + 0x24) = 0x4085d0;
    __dt__7KeyWaitFv(param_1 + 800,0xffffffffffffffff);
    __dt__10MenuSpriteFv(param_1 + 0x2c0,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x290,0xffffffffffffffff);
    __dt__11MenuTextureFv(param_1 + 0x250,0xffffffffffffffff);
    __dt__11MenuMessageFv(param_1 + 0x1b8,0xffffffffffffffff);
    __dt__8MenuTextFv(param_1 + 0x138,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0xf8,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0xb8,0xffffffffffffffff);
    __dt__9CmdWindowFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x0045bd80  CmdHelpExplain::CreateScene(CmdHelp*)   [CreateScene__14CmdHelpExplainFP7CmdHelp]  size=0x1dc */
void CreateScene__14CmdHelpExplainFP7CmdHelp(int param_1,undefined4 param_2)

{
  *(byte *)(param_1 + 0x3ff) = *(byte *)(param_1 + 0x3ff) & 7;
  SetData__9MenuSceneFUsP8FontDraw(param_2,2,param_1 + 0xb8);
  SetData__9MenuSceneFUsP8FontDraw(param_2,3,param_1 + 0xf8);
  SetData__9MenuSceneFUsP8MenuText(param_2,2,param_1 + 0x138);
  SetData__9MenuSceneFUsP11MenuMessage(param_2,0,param_1 + 0x1b8);
  SetData__9MenuSceneFUsP10MenuSprite(param_2,1,param_1 + 0x2c0);
  *(short *)(param_1 + 0x2a4) = *(short *)(param_1 + 0x2d4) + -1;
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0xb8);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0xf8);
  AddPlace__10MenuWindowFP9MenuPlace(param_1,param_1 + 0x138);
  AddPlace__10MenuWindowFP9MenuPlace(param_1,param_1 + 0x1b8);
  AddPlace__10MenuWindowFP9MenuPlace(param_1,param_1 + 0x2c0);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0x290);
  Create__7KeyWaitFv(param_1 + 800);
  *(int *)(param_1 + 0x48) = param_1 + 800;
  *(int *)(param_1 + 0x338) = param_1;
  SetData__9MenuSceneFUsP10MenuWindow(param_2,2,param_1);
  CreateScrollMark__10MenuWindowFUc(param_1,3);
  AddOT__7MenuObjFv(param_1);
  return;
}

/* JP: 0x0045bf60  CmdHelpExplain::UpdateScene(CmdHelp*, short)   [UpdateScene__14CmdHelpExplainFP7CmdHelps]  size=0x34c */
void UpdateScene__14CmdHelpExplainFP7CmdHelps(int param_1,int param_2,short param_3)

{
  int iVar1;
  uint uVar2;
  ulong uVar3;
  undefined1 auStack_80 [76];
  undefined4 uStack_34;
  int iStack_30;
  int iStack_20;
  short sStack_10;
  
  *(short *)(param_1 + 0xae) = param_3;
  uVar3 = (long)param_3 & 7;
  uVar2 = (uint)uVar3;
  if (((long)param_3 < 0) && (uVar3 != 0)) {
    uVar2 = uVar2 - 8;
  }
  iVar1 = (int)param_3;
  if (param_3 < 0) {
    iVar1 = iVar1 + 7;
  }
  iVar1 = *(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x180 + (iVar1 >> 3);
  *(byte *)(iVar1 + 0x50) = *(byte *)(iVar1 + 0x50) | (byte)(1 << (uVar2 & 0x1f));
  iStack_30 = param_1;
  iStack_20 = param_2;
  sStack_10 = param_3;
  SetNewIcon__11CmdHelpMenuFP7CmdHelp(param_2 + 0xa8,param_2);
  *(int *)(iStack_30 + 0xb4) = *(int *)(iStack_20 + 0x2d8) + sStack_10 * 0x24;
  ClearImage__8FontDrawFv(iStack_30 + 0xb8);
  uStack_34 = **(undefined4 **)(iStack_30 + 0xb4);
  SetMessage__8MenuTextFPcUiUcUc(iStack_30 + 0x138,uStack_34,*(byte *)(iStack_30 + 400) & 7,0,0);
  OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_30 + 0xb8,iStack_30 + 0x138,((ulong)*(byte *)(iStack_30 + 400) & 0xf) >> 3,
                  0);
  SetExplanation__7CmdNoteFPCce
            (*(undefined4 *)(iStack_20 + 0x2e0),*(undefined4 *)(*(int *)(iStack_20 + 0x28) + 0x2c),
             **(undefined4 **)(iStack_30 + 0xb4));
  SetExplanation__14CmdHelpExplainFP7CmdHelps(iStack_30,iStack_20,0);
  *(undefined1 *)(iStack_30 + 0x3fc) = 0;
  *(undefined1 *)(iStack_30 + 0x3fd) = 1;
  *(byte *)(iStack_30 + 0x3ff) = *(byte *)(iStack_30 + 0x3ff) & 0xfd;
  *(undefined1 *)(iStack_30 + 0x1d8) = 1;
  *(byte *)(iStack_30 + 0x2d2) = *(byte *)(iStack_30 + 0x2d2) & 0xfe;
  *(byte *)(iStack_30 + 0x2a2) = *(byte *)(iStack_30 + 0x2a2) & 0xfe;
  if (((ulong)*(byte *)(*(int *)(iStack_30 + 0xb4) + 0x1d) & 0x7f) >> 3 != 0) {
    sprintf(auStack_80,*(undefined4 *)(*(int *)(iStack_20 + 0x24) + 0x10),sStack_10);
    OrderFile__11MenuTextureFPCc6GS_PSMUii(iStack_30 + 0x250,auStack_80,0x30,0,0);
    *(undefined1 *)(iStack_30 + 0x3fd) = 0;
  }
  if ((*(uint *)(iStack_20 + 0x2c8) & 0xffff) < 2) {
    *(byte *)(*(int *)(iStack_30 + 0x44) + 0x12) =
         *(byte *)(*(int *)(iStack_30 + 0x44) + 0x12) & 0xfe;
  }
  else {
    *(byte *)(*(int *)(iStack_30 + 0x44) + 0x12) =
         *(byte *)(*(int *)(iStack_30 + 0x44) + 0x12) & 0xfe | 1;
  }
  return;
}

/* JP: 0x0045c2b0  CmdHelpExplain::SetExplanation(CmdHelp*, short)   [SetExplanation__14CmdHelpExplainFP7CmdHelps]  size=0x2a0 */
void SetExplanation__14CmdHelpExplainFP7CmdHelps(int param_1,undefined4 param_2,short param_3)

{
  short sVar1;
  
  ClearImage__8FontDrawFv(param_1 + 0xf8);
  ClearMessage__11MenuMessageFv(param_1 + 0x1b8);
  SetFontColor__14PluralFontItemFUsUsUcUcUc(param_1 + 0x1b8,0,*(undefined2 *)(param_1 + 0x22c),
                  *(undefined1 *)(param_1 + 0x204),*(undefined1 *)(param_1 + 0x205),
                  *(undefined1 *)(param_1 + 0x206));
  Order__8FontDrawFP11MenuMessagePc(param_1 + 0xf8,param_1 + 0x1b8,
                  *(undefined4 *)(*(int *)(param_1 + 0xb4) + param_3 * 4 + 4));
  *(undefined2 *)(param_1 + 0x400) = 0xffff;
  for (sVar1 = 0; sVar1 < *(short *)(*(int *)(param_1 + 0xb4) + 0x1e); sVar1 = sVar1 + 1) {
    if (((*(char *)(*(int *)(*(int *)(param_1 + 0xb4) + 0x18) + sVar1 * 8 + 7) != '\0') &&
        ((long)param_3 == (long)*(char *)(*(int *)(*(int *)(param_1 + 0xb4) + 0x18) + sVar1 * 8 + 6)
        )) && (SetFontColor__14PluralFontItemFUsUsUcUcUc(param_1 + 0x1b8,
                               *(undefined2 *)
                                (*(int *)(*(int *)(param_1 + 0xb4) + 0x18) + sVar1 * 8),
                               *(undefined2 *)
                                (*(int *)(*(int *)(param_1 + 0xb4) + 0x18) + sVar1 * 8 + 2),0x20,
                               0x20,0x40), *(short *)(param_1 + 0x400) < 0)) {
      *(short *)(param_1 + 0x400) = sVar1;
    }
  }
  if ((((ulong)*(byte *)(*(int *)(param_1 + 0xb4) + 0x1d) & 0x7f) >> 3 &
      (long)(1 << ((int)param_3 & 0x1fU))) != 0) {
    *(byte *)(param_1 + 0x2d2) = *(byte *)(param_1 + 0x2d2) & 0xfe | 1;
  }
  *(byte *)(param_1 + 0x332) = *(byte *)(param_1 + 0x332) & 0xfe;
  *(char *)(param_1 + 0x3fe) = (char)param_3 + '\x01';
  SetButtonReport__7CmdHelpFs(param_2,*(undefined2 *)(*(int *)(param_1 + 0xb4) + 0x1e));
  return;
}

/* JP: 0x0045c550  CmdHelpExplain::Run(CmdHelp*)   [Run__14CmdHelpExplainFP7CmdHelp]  size=0xfcc */
/* WARNING: Removing unreachable block (ram,0x0045c738) */
/* WARNING: Removing unreachable block (ram,0x0045c774) */

undefined4 Run__14CmdHelpExplainFP7CmdHelp(int param_1,int param_2)

{
  char cVar1;
  short sVar2;
  ushort uVar3;
  int iVar4;
  undefined4 uVar5;
  bool bVar6;
  short sVar7;
  int iVar8;
  long lVar9;
  
  uVar3 = *(ushort *)(*(int *)(param_2 + 0x10) + 0x48);
  iVar4 = *(int *)(param_2 + 0x18);
  uVar5 = *(undefined4 *)(param_2 + 100);
  cVar1 = *(char *)(param_1 + 0x3fc);
  if (cVar1 == '\x01') {
    cVar1 = *(char *)(param_1 + 0x3fd);
    if (cVar1 == '\x03') {
      return 1;
    }
    if (cVar1 == '\x02') {
      if ((long)((ulong)*(byte *)(param_1 + 0x3ff) << 0x3e) < 0) {
        UpdateScene__14CmdHelpExplainFP7CmdHelps
                  (param_1,param_2,*(undefined2 *)(*(int *)(iVar4 + 0xec) + 0x16));
      }
      else {
        ReleaseOT__7MenuObjFv(param_1);
        *(char *)(param_1 + 0x3fd) = *(char *)(param_1 + 0x3fd) + '\x01';
      }
    }
    else if (cVar1 == '\x01') {
      if ((*(char *)(param_1 + 0xa8) == '\x01') || (*(char *)(param_1 + 0xa8) == '\0')) {
        bVar6 = true;
      }
      else {
        bVar6 = false;
      }
      if (bVar6) {
        *(char *)(param_1 + 0x3fd) = *(char *)(param_1 + 0x3fd) + '\x01';
      }
    }
    else if (cVar1 == '\0') {
      Close__10MenuWindowFUci(param_1,((ulong)*(byte *)(param_1 + 0xb0) & 0x3f) >> 3,
                      *(undefined4 *)(*(int *)(param_1 + 0x34) + 0x14));
      *(char *)(param_1 + 0x3fd) = *(char *)(param_1 + 0x3fd) + '\x01';
    }
  }
  else if (cVar1 == '\x03') {
    if (((*(byte *)(param_1 + 0x332) & 1) == 0) || ((uVar3 & 0x2000) == 0)) {
      if (((uVar3 & 0x8000) == 0) || (*(byte *)(param_1 + 0x3ff) >> 3 == 0)) {
        if (-1 < *(short *)(param_1 + 0x400)) {
          if ((uVar3 & 0x1000) == 0) {
            sVar2 = *(short *)(param_1 + 0x400);
            sVar7 = *(char *)(param_1 + 0x3fe) + -1;
            if ((uVar3 & 0x80) == 0) {
              if ((uVar3 & 0x20) != 0) {
                iVar8 = (int)*(short *)(param_1 + 0x400);
                while (iVar8 = iVar8 + 1,
                      (long)iVar8 < (long)*(short *)(*(int *)(param_1 + 0xb4) + 0x1e)) {
                  if ((*(char *)(*(int *)(*(int *)(param_1 + 0xb4) + 0x18) + iVar8 * 8 + 7) != '\0')
                     && ((long)sVar7 ==
                         (long)*(char *)(*(int *)(*(int *)(param_1 + 0xb4) + 0x18) + iVar8 * 8 + 6))
                     ) {
                    *(short *)(param_1 + 0x400) = (short)iVar8;
                  }
                }
                if (sVar2 == *(short *)(param_1 + 0x400)) {
                  lVar9 = 0;
                  while (lVar9 < *(short *)(param_1 + 0x400)) {
                    iVar8 = (int)lVar9;
                    if ((*(char *)(*(int *)(*(int *)(param_1 + 0xb4) + 0x18) + iVar8 * 8 + 7) !=
                         '\0') &&
                       ((long)sVar7 ==
                        (long)*(char *)(*(int *)(*(int *)(param_1 + 0xb4) + 0x18) + iVar8 * 8 + 6)))
                    {
                      *(short *)(param_1 + 0x400) = (short)lVar9;
                    }
                    lVar9 = (long)(iVar8 + 1);
                  }
                }
              }
            }
            else {
              iVar8 = (int)*(short *)(param_1 + 0x400);
              while (iVar8 = iVar8 + -1, -1 < iVar8) {
                if ((*(char *)(*(int *)(*(int *)(param_1 + 0xb4) + 0x18) + iVar8 * 8 + 7) != '\0')
                   && ((long)sVar7 ==
                       (long)*(char *)(*(int *)(*(int *)(param_1 + 0xb4) + 0x18) + iVar8 * 8 + 6)))
                {
                  *(short *)(param_1 + 0x400) = (short)iVar8;
                }
              }
              if (sVar2 == *(short *)(param_1 + 0x400)) {
                iVar8 = (int)*(short *)(*(int *)(param_1 + 0xb4) + 0x1e);
                while (iVar8 = iVar8 + -1, (long)*(short *)(param_1 + 0x400) <= (long)iVar8) {
                  if ((*(char *)(*(int *)(*(int *)(param_1 + 0xb4) + 0x18) + iVar8 * 8 + 7) != '\0')
                     && ((long)sVar7 ==
                         (long)*(char *)(*(int *)(*(int *)(param_1 + 0xb4) + 0x18) + iVar8 * 8 + 6))
                     ) {
                    *(short *)(param_1 + 0x400) = (short)iVar8;
                  }
                }
              }
            }
            if (sVar2 != *(short *)(param_1 + 0x400)) {
              SetFontColor__14PluralFontItemFUsUsUcUcUc(param_1 + 0x1b8,
                              *(undefined2 *)(*(int *)(*(int *)(param_1 + 0xb4) + 0x18) + sVar2 * 8)
                              ,*(undefined2 *)
                                (*(int *)(*(int *)(param_1 + 0xb4) + 0x18) + sVar2 * 8 + 2),0x20,
                              0x20,0x40);
              SetFontColor__14PluralFontItemFUsUsUcUcUc(param_1 + 0x1b8,
                              *(undefined2 *)
                               (*(int *)(*(int *)(param_1 + 0xb4) + 0x18) +
                               *(short *)(param_1 + 0x400) * 8),
                              *(undefined2 *)
                               (*(int *)(*(int *)(param_1 + 0xb4) + 0x18) +
                                *(short *)(param_1 + 0x400) * 8 + 2),0x40,0x40,0x80);
              PlaySE__9MenuSoundFUiUcP8_SeParam(uVar5,0,0,0);
            }
          }
          else {
            if (0xf < *(byte *)(param_1 + 0x3ff) >> 3) {
              for (iVar8 = 0; iVar8 < 0xf; iVar8 = iVar8 + 1) {
                *(undefined2 *)(param_1 + iVar8 * 2 + 0x402) =
                     *(undefined2 *)(param_1 + (iVar8 + 1) * 2 + 0x402);
              }
              *(byte *)(param_1 + 0x3ff) =
                   *(byte *)(param_1 + 0x3ff) & 7 |
                   (byte)(((uint)(((ulong)*(byte *)(param_1 + 0x3ff) << 0x38) >> 0x3b) - 1 & 0x1f)
                         << 3);
            }
            *(undefined2 *)
             (param_1 + (uint)(((ulong)*(byte *)(param_1 + 0x3ff) << 0x38) >> 0x3b) * 2 + 0x402) =
                 *(undefined2 *)(param_1 + 0xae);
            *(byte *)(param_1 + 0x3ff) =
                 *(byte *)(param_1 + 0x3ff) & 7 |
                 (byte)(((uint)(((ulong)*(byte *)(param_1 + 0x3ff) << 0x38) >> 0x3b) + 1 & 0x1f) <<
                       3);
            LinkJump__7CmdHelpFs
                      (param_2,*(undefined2 *)
                                (*(int *)(*(int *)(param_1 + 0xb4) + 0x18) +
                                 *(short *)(param_1 + 0x400) * 8 + 4));
            *(byte *)(param_1 + 0x3ff) = *(byte *)(param_1 + 0x3ff) & 0xfd | 2;
            *(undefined1 *)(param_1 + 0x3fc) = 1;
            PlaySE__9MenuSoundFUiUcP8_SeParam(uVar5,6,0,0);
          }
        }
      }
      else {
        *(byte *)(param_1 + 0x3ff) =
             *(byte *)(param_1 + 0x3ff) & 7 |
             (byte)(((uint)(((ulong)*(byte *)(param_1 + 0x3ff) << 0x38) >> 0x3b) - 1 & 0x1f) << 3);
        LinkJump__7CmdHelpFs
                  (param_2,*(undefined2 *)
                            (param_1 + (uint)(((ulong)*(byte *)(param_1 + 0x3ff) << 0x38) >> 0x3b) *
                                       2 + 0x402));
        *(byte *)(param_1 + 0x3ff) = *(byte *)(param_1 + 0x3ff) & 0xfd | 2;
        *(undefined1 *)(param_1 + 0x3fc) = 1;
        PlaySE__9MenuSoundFUiUcP8_SeParam(uVar5,6,0,0);
      }
    }
    else {
      SetExplanation__14CmdHelpExplainFP7CmdHelps(param_1,param_2,*(undefined1 *)(param_1 + 0x3fe));
      Start__11MenuMessageFv(param_1 + 0x1b8);
      *(undefined1 *)(param_1 + 0x3fc) = 2;
    }
  }
  else if (cVar1 == '\x02') {
    if ((uVar3 & 0x2000) != 0) {
      Finish__11MenuMessageFv(param_1 + 0x1b8);
    }
    if ((*(ushort *)(param_1 + 0x22e) <= *(ushort *)(param_1 + 0x238)) &&
       (*(ushort *)(param_1 + 0x22e) <= *(ushort *)(param_1 + 0x238))) {
      if ((long)*(char *)(param_1 + 0x3fe) <
          (long)((ulong)*(byte *)(*(int *)(param_1 + 0xb4) + 0x1d) & 7)) {
        SetPosition__7KeyWaitFi(param_1 + 800,1);
        *(byte *)(param_1 + 0x332) = *(byte *)(param_1 + 0x332) & 0xfe | 1;
      }
      if (-1 < *(short *)(param_1 + 0x400)) {
        SetFontColor__14PluralFontItemFUsUsUcUcUc(param_1 + 0x1b8,
                        *(undefined2 *)
                         (*(int *)(*(int *)(param_1 + 0xb4) + 0x18) +
                         *(short *)(param_1 + 0x400) * 8),
                        *(undefined2 *)
                         (*(int *)(*(int *)(param_1 + 0xb4) + 0x18) +
                          *(short *)(param_1 + 0x400) * 8 + 2),0x40,0x40,0x80);
      }
      *(undefined1 *)(param_1 + 0x3fc) = 3;
    }
  }
  else if (cVar1 == '\0') {
    cVar1 = *(char *)(param_1 + 0x3fd);
    if (cVar1 == '\x02') {
      if ((*(char *)(param_1 + 0xa8) == '\x01') || (*(char *)(param_1 + 0xa8) == '\0')) {
        bVar6 = true;
      }
      else {
        bVar6 = false;
      }
      if (bVar6) {
        Start__11MenuMessageFv(param_1 + 0x1b8);
        *(undefined1 *)(param_1 + 0x3fc) = 2;
        *(undefined1 *)(param_1 + 0x3fd) = 0;
      }
    }
    else {
      if (cVar1 != '\x01') {
        if ((cVar1 != '\0') || ((*(byte *)(param_1 + 0x28a) & 1) == 0)) goto LAB_0045d380;
        Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(param_1 + 0x290,param_1 + 0x268,*(undefined4 *)(param_1 + 0x264),1,
                        0xffffffffffffffff);
        (**(code **)(*(int *)(param_1 + 0x2c8) + 0x24))
                  ((float)(int)*(short *)(*(int *)(param_1 + 0xb4) + 0x20),
                   (float)(int)*(short *)(*(int *)(param_1 + 0xb4) + 0x22));
        (**(code **)(*(int *)(param_1 + 0x2c8) + 0x28))
                  ((float)**(ushort **)(param_1 + 0x260),
                   (float)*(ushort *)(*(int *)(param_1 + 0x260) + 2));
        SetUV__10MenuSpriteFUsUsUsUs(param_1 + 0x2c0,0,0,**(undefined2 **)(param_1 + 0x260),
                        *(undefined2 *)(*(int *)(param_1 + 0x260) + 2));
        *(byte *)(param_1 + 0x2a2) = *(byte *)(param_1 + 0x2a2) & 0xfe | 1;
        *(byte *)(param_1 + 0x2d2) = *(byte *)(param_1 + 0x2d2) & 0xfe | 1;
        *(char *)(param_1 + 0x3fd) = *(char *)(param_1 + 0x3fd) + '\x01';
      }
      Open__10MenuWindowFUci(param_1,*(byte *)(param_1 + 0xb0) & 7,
                      *(undefined4 *)(*(int *)(param_1 + 0x34) + 0x10));
      *(char *)(param_1 + 0x3fd) = *(char *)(param_1 + 0x3fd) + '\x01';
    }
  }
LAB_0045d380:
  if ((*(char *)(param_1 + 0x3fc) == '\x02') || (*(char *)(param_1 + 0x3fc) == '\x03')) {
    if ((uVar3 & 0x4000) == 0) {
      if ((*(byte *)(*(int *)(param_1 + 0x44) + 0x12) & 1) != 0) {
        iVar8 = *(int *)(iVar4 + 0xec);
        if ((uVar3 & 0x10) == 0) {
          if ((uVar3 & 0x40) != 0) {
            MoveCursor__6CursorFi(iVar4,2);
          }
        }
        else {
          MoveCursor__6CursorFi(iVar4,1);
        }
        if (*(int *)(iVar4 + 0xec) != iVar8) {
          *(undefined1 *)(param_1 + 0x3fc) = 1;
          *(byte *)(param_1 + 0x3ff) = *(byte *)(param_1 + 0x3ff) & 0xfd | 2;
          PlaySE__9MenuSoundFUiUcP8_SeParam(uVar5,6,0,0);
        }
      }
    }
    else {
      *(undefined1 *)(param_1 + 0x3fc) = 1;
      PlaySE__9MenuSoundFUiUcP8_SeParam(uVar5,3,0,0);
    }
  }
  return 0;
}

/* JP: 0x0045d520  CmdHelpExplain::~CmdHelpExplain()   [@24@__dt__14CmdHelpExplainFv]  size=0x8 */
undefined4 * _24___dt__14CmdHelpExplainFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -6;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-4] = &__vt__14CmdHelpExplain;
    *param_1 = 0x4085c4;
    param_1[3] = 0x4085d0;
    __dt__7KeyWaitFv(param_1 + 0xc2,0xffffffffffffffff);
    __dt__10MenuSpriteFv(param_1 + 0xaa,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x9e,0xffffffffffffffff);
    __dt__11MenuTextureFv(param_1 + 0x8e,0xffffffffffffffff);
    __dt__11MenuMessageFv(param_1 + 0x68,0xffffffffffffffff);
    __dt__8MenuTextFv(param_1 + 0x48,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x38,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x28,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}

/* JP: 0x0045d530  CmdHelpExplain::~CmdHelpExplain()   [@36@__dt__14CmdHelpExplainFv]  size=0x8 */
undefined4 * _36___dt__14CmdHelpExplainFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -9;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-7] = &__vt__14CmdHelpExplain;
    param_1[-3] = 0x4085c4;
    *param_1 = 0x4085d0;
    __dt__7KeyWaitFv(param_1 + 0xbf,0xffffffffffffffff);
    __dt__10MenuSpriteFv(param_1 + 0xa7,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x9b,0xffffffffffffffff);
    __dt__11MenuTextureFv(param_1 + 0x8b,0xffffffffffffffff);
    __dt__11MenuMessageFv(param_1 + 0x65,0xffffffffffffffff);
    __dt__8MenuTextFv(param_1 + 0x45,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x35,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x25,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}
