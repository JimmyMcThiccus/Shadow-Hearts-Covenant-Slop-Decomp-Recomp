/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdWolfBout   functions: 18
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdWolfBout.md).
 */

/* JP: 0x00483620  CmdWolfBout::CmdWolfBout()   [__ct__11CmdWolfBoutFv]  size=0x54 */
int __ct__11CmdWolfBoutFv(int param_1)

{
  __ct__15CmdPrivateSceneFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__11CmdWolfBout;
  *(undefined4 *)(param_1 + 0x78) = 0;
  *(undefined4 *)(param_1 + 0x80) = 0;
  *(undefined4 *)(param_1 + 0x84) = 0;
  return param_1;
}

/* JP: 0x00483680  CmdWolfBout::~CmdWolfBout()   [__dt__11CmdWolfBoutFv]  size=0x74 */
int __dt__11CmdWolfBoutFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__11CmdWolfBout;
    __dt__15CmdPrivateSceneFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x00483700  CmdWolfBout::GetReady()   [GetReady__11CmdWolfBoutFv]  size=0x270 */
undefined4 GetReady__11CmdWolfBoutFv(int param_1)

{
  undefined4 uVar1;
  
  *(undefined4 *)(param_1 + 0x68) = sm_pSound__7MenuObj;
  *(int *)(param_1 + 0x18) = *(int *)(param_1 + 0x10) + 0x3a0;
  uVar1 = Find__13MenuDataTableFs(*(int *)(param_1 + 0x10) + 0x28,0x2c);
  *(undefined4 *)(param_1 + 0x8c) = uVar1;
  *(undefined4 *)(param_1 + 0x70) = *(undefined4 *)(*(int *)(param_1 + 0x58) + 0x68);
  *(undefined4 *)(param_1 + 0x74) = *(undefined4 *)(*(int *)(param_1 + 0x58) + 0x6c);
  *(undefined4 *)(param_1 + 0x6c) = *(undefined4 *)(*(int *)(param_1 + 0x58) + 0x90);
  *(undefined1 *)(param_1 + 0x22) =
       *(undefined1 *)(*(int *)(*(int *)(*(int *)(param_1 + 0x58) + 0x5c) + 4) + 0xe43);
  Convert__13MenuDataTableFPUci(*(undefined4 *)(*(int *)(param_1 + 0x54) + 0x4c),0);
  SetTitle__11CmdTitleLogFPUci
            (*(undefined4 *)(*(int *)(param_1 + 0x58) + 0x60),
             *(undefined4 *)(*(int *)(param_1 + 0x54) + 0x10),0x10);
  Open__11CmdTitleLogFv(*(undefined4 *)(*(int *)(param_1 + 0x58) + 0x60));
  UpdateStamp__11CmdWolfBoutFss(param_1,1,0);
  *(byte *)(param_1 + 0x23) = *(byte *)(param_1 + 0x23) & 0xdf | 0x20;
  return 1;
}

/* JP: 0x00483970  CmdWolfBout::Run()   [Run__11CmdWolfBoutFv]  size=0x68 */
undefined4 Run__11CmdWolfBoutFv(int param_1)

{
  undefined4 uVar1;
  long lVar2;
  
  lVar2 = __ptmf_test(param_1 + 0x5c);
  if ((lVar2 == 0) || (lVar2 = __ptmf_scall(param_1), lVar2 != 0)) {
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

/* JP: 0x004839e0  CmdWolfBout::SafeDelayDelete()   [SafeDelayDelete__11CmdWolfBoutFv]  size=0x74 */
void SafeDelayDelete__11CmdWolfBoutFv(int param_1)

{
  (**(code **)(*(int *)(*(int *)(param_1 + 0x80) + 8) + 0xc))();
  if (*(int *)(param_1 + 0x84) != 0) {
    (**(code **)(*(int *)(*(int *)(param_1 + 0x84) + 8) + 0xc))();
  }
  (**(code **)(*(int *)(param_1 + 8) + 0xc))();
  return;
}

/* JP: 0x00483a60  CmdWolfBout::Close()   [Close__11CmdWolfBoutFv]  size=0x4c */
void Close__11CmdWolfBoutFv(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x80);
  Close__10MenuWindowFUci(iVar1,((ulong)*(byte *)(iVar1 + 0xb0) & 0x3f) >> 3,
                  *(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x14));
  return;
}

/* JP: 0x00483ab0  CmdWolfBout::ReadyScene()   [ReadyScene__11CmdWolfBoutFv]  size=0x244 */
undefined4 ReadyScene__11CmdWolfBoutFv(int param_1)

{
  int iVar1;
  undefined *puVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  long lVar5;
  undefined1 auStack_70 [96];
  int iStack_10;
  
  iStack_10 = param_1;
  SetChengePCMode__10CmdPCSceneFUc(*(undefined4 *)(param_1 + 0x58),0);
  if (*(char *)(iStack_10 + 0x22) == '\0') {
    __ct__9MenuSceneFv(auStack_70);
    Initialize__9MenuSceneFPUcP9BufMemory(auStack_70,*(undefined4 *)(*(int *)(*(int *)(iStack_10 + 0x58) + 0x54) + 0x40),0
                   );
    lVar5 = __nw__FUi(0x2b0);
    uVar3 = 0;
    if (lVar5 != 0) {
      uVar3 = __ct__14CmdNoteMessageFv(lVar5);
    }
    *(undefined4 *)(iStack_10 + 0x78) = uVar3;
    CreateScene__14CmdNoteMessageFP9MenuScenePci
              (*(undefined4 *)(iStack_10 + 0x78),auStack_70,
               *(undefined4 *)(*(int *)(iStack_10 + 0x24) + 0x20),0);
    iVar1 = *(int *)(iStack_10 + 0x78);
    Open__10MenuWindowFUci(iVar1,*(byte *)(iVar1 + 0xb0) & 7,*(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x10)
                   );
    puVar2 = PTR_DisplayMessage__11CmdWolfBoutFv_0050da08;
    uVar3 = DAT_0050da04;
    *(undefined4 *)(iStack_10 + 0x5c) = _6193;
    *(undefined4 *)(iStack_10 + 0x60) = uVar3;
    *(undefined **)(iStack_10 + 100) = puVar2;
    __dt__9MenuSceneFv(auStack_70,0xffffffffffffffff);
    uVar3 = 0;
  }
  else {
    *(undefined2 *)(iStack_10 + 0x88) = 0xffff;
    uVar4 = GetPlace__10MenuWindowFss(*(undefined4 *)(iStack_10 + 0x80),0,0);
    Select__6CursorFP9MenuPlace(*(undefined4 *)(iStack_10 + 0x18),uVar4);
    SetWolf__11CmdWolfBoutFs(iStack_10,*(undefined2 *)((int)uVar4 + 0x16));
    UpdateProfile__11CmdWolfBoutFs(iStack_10,1);
    Select__16CmdWolfBoutStampFP11CmdWolfBoutP9MenuPlaceP9MenuPlace
              (*(undefined4 *)(iStack_10 + 0x80),iStack_10,uVar4,0);
    *(undefined1 *)(iStack_10 + 0x21) = 0;
    puVar2 = PTR_Enter__11CmdWolfBoutFv_0050d9f8;
    uVar3 = DAT_0050d9f4;
    *(undefined4 *)(iStack_10 + 0x5c) = _6189;
    *(undefined4 *)(iStack_10 + 0x60) = uVar3;
    *(undefined **)(iStack_10 + 100) = puVar2;
    uVar3 = 1;
  }
  return uVar3;
}

/* JP: 0x00483d00  CmdWolfBout::UpdateStamp(short, short)   [UpdateStamp__11CmdWolfBoutFss]  size=0x104 */
void UpdateStamp__11CmdWolfBoutFss(int param_1,short param_2,undefined2 param_3)

{
  int iVar1;
  undefined4 uVar2;
  long lVar3;
  
  if (*(int *)(param_1 + 0x80) != 0) {
    (**(code **)(*(int *)(*(int *)(param_1 + 0x80) + 8) + 0xc))();
  }
  lVar3 = __nw__FUi(0x280);
  uVar2 = 0;
  if (lVar3 != 0) {
    uVar2 = __ct__16CmdWolfBoutStampFv(lVar3);
  }
  *(undefined4 *)(param_1 + 0x80) = uVar2;
  CreateScene__16CmdWolfBoutStampFP11CmdWolfBouts(*(undefined4 *)(param_1 + 0x80),param_1,param_3);
  *(byte *)(*(int *)(param_1 + 0x80) + 0x12) = *(byte *)(*(int *)(param_1 + 0x80) + 0x12) & 0xfe | 1
  ;
  if (param_2 != 0) {
    iVar1 = *(int *)(param_1 + 0x80);
    Open__10MenuWindowFUci(iVar1,*(byte *)(iVar1 + 0xb0) & 7,*(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x10)
                   );
  }
  return;
}

/* JP: 0x00483e10  CmdWolfBout::UpdateProfile(short)   [UpdateProfile__11CmdWolfBoutFs]  size=0xfc */
void UpdateProfile__11CmdWolfBoutFs(int param_1,short param_2)

{
  int iVar1;
  undefined4 uVar2;
  long lVar3;
  
  if (*(int *)(param_1 + 0x84) == 0) {
    lVar3 = __nw__FUi(500);
    uVar2 = 0;
    if (lVar3 != 0) {
      uVar2 = __ct__18CmdWolfBoutProfileFv(lVar3);
    }
    *(undefined4 *)(param_1 + 0x84) = uVar2;
    CreateScene__18CmdWolfBoutProfileFP11CmdWolfBout(*(undefined4 *)(param_1 + 0x84),param_1);
  }
  UpdateScene__18CmdWolfBoutProfileFP11CmdWolfBout(*(undefined4 *)(param_1 + 0x84),param_1);
  *(byte *)(*(int *)(param_1 + 0x84) + 0x12) = *(byte *)(*(int *)(param_1 + 0x84) + 0x12) & 0xfe | 1
  ;
  if (param_2 != 0) {
    iVar1 = *(int *)(param_1 + 0x84);
    Open__10MenuWindowFUci(iVar1,*(byte *)(iVar1 + 0xb0) & 7,*(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x10)
                   );
  }
  return;
}

/* JP: 0x00483f10  CmdWolfBout::SetWolf(short)   [SetWolf__11CmdWolfBoutFs]  size=0x284 */
void SetWolf__11CmdWolfBoutFs(int param_1,short param_2)

{
  undefined2 uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  short sVar5;
  short sVar6;
  int iVar7;
  int iVar8;
  
  if (param_2 != *(short *)(param_1 + 0x88)) {
    iVar7 = (param_2 * 0xc + (int)param_2) * 4 + *(int *)(param_1 + 0x8c);
    sVar5 = FieldNpcLibrary__Fii(*(undefined2 *)(iVar7 + 0x30),0);
    sVar6 = 3;
    while ((-1 < sVar6 && (((long)sVar5 & (long)(1 << ((int)sVar6 & 0x1fU))) == 0))) {
      sVar6 = sVar6 + -1;
    }
    iVar2 = *(int *)(*(int *)(param_1 + 0x58) + 0x94);
    iVar8 = GetRegDat__9RegDatApiFiii(0x2e,*(undefined2 *)(iVar7 + sVar6 * 2 + 0x3c),0xffffffffffffffff);
    uVar1 = *(undefined2 *)(iVar8 + 4);
    Reset__16MenuModelManegerFv(*(undefined4 *)(param_1 + 0x6c));
    *(undefined2 *)(*(int *)(param_1 + 0x6c) + 0x68) = uVar1;
    uVar3 = *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x58) + 0x24) + 0x10);
    iVar4 = *(int *)(param_1 + 0x6c);
    *(undefined2 *)(iVar4 + 0x3c) = uVar1;
    *(undefined4 *)(iVar4 + 0x24) = uVar3;
    Access__16MenuModelManegerFv(*(undefined4 *)(param_1 + 0x6c));
    iVar4 = *(int *)(*(int *)(param_1 + 0x6c) + 0x18);
    *(int *)(iVar4 + 0x10) = iVar2;
    *(int *)(iVar4 + 0x14) = iVar2 + 0x10;
    SetCamera__7CmdMenuFP13MenuDataModel
              (*(undefined4 *)(param_1 + 0x10),*(undefined4 *)(iVar7 + 0x2c));
    Create__10CmdElementFUc(*(undefined4 *)(param_1 + 0x74),*(byte *)(iVar8 + 0x14) & 7);
    *(short *)(param_1 + 0x8a) = sVar6;
    *(short *)(param_1 + 0x88) = param_2;
  }
  return;
}

/* JP: 0x004841a0  CmdWolfBout::SetExplanation()   [SetExplanation__11CmdWolfBoutFv]  size=0x138 */
void SetExplanation__11CmdWolfBoutFv(int param_1)

{
  int iVar1;
  undefined1 uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  
  iVar1 = *(int *)(param_1 + 0x7c);
  memset(iVar1 + 0x5c,0,0x10);
  iVar3 = (*(short *)(param_1 + 0x88) * 0xc + (int)*(short *)(param_1 + 0x88)) * 4 +
          *(int *)(param_1 + 0x8c);
  puVar5 = (undefined4 *)(iVar3 + 0x10);
  *(undefined2 *)(iVar1 + 0x5c) =
       *(undefined2 *)((int)puVar5 + *(short *)(param_1 + 0x8a) * 2 + 0x24);
  uVar2 = FieldNpcLibrary__Fii(*(undefined2 *)(iVar3 + 0x30),0);
  *(undefined1 *)(iVar1 + 0x5f) = uVar2;
  uVar4 = GetRegDat__9RegDatApiFiii(5,*(undefined2 *)((int)puVar5 + *(short *)(param_1 + 0x8a) * 2 + 0x2c),
                          0xffffffffffffffff);
  *(undefined4 *)(iVar1 + 0x60) = uVar4;
  *(undefined4 *)(iVar1 + 100) = *puVar5;
  *(int *)(iVar1 + 0x68) = iVar3 + 0x1c;
  Open__10CmdExplainFv(*(undefined4 *)(param_1 + 0x7c));
  return;
}

/* JP: 0x004842e0  CmdWolfBout::SetButtonReport(int)   [SetButtonReport__11CmdWolfBoutFi]  size=0x9c */
void SetButtonReport__11CmdWolfBoutFi(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x70);
  ClearReport__15CmdButtonReportFv(iVar1);
  SetReport__15CmdButtonReportFii(iVar1,*(undefined1 *)(iVar1 + 0x20),0xc);
  SetReport__15CmdButtonReportFii(iVar1,*(undefined1 *)(iVar1 + 0x20),7);
  if (param_2 != 0) {
    SetReport__15CmdButtonReportFii(iVar1,*(undefined1 *)(iVar1 + 0x20),4);
  }
  return;
}

/* JP: 0x00484380  CmdWolfBout::Enter()   [Enter__11CmdWolfBoutFv]  size=0xc0 */
undefined8 Enter__11CmdWolfBoutFv(int param_1)

{
  undefined4 uVar1;
  undefined *puVar2;
  
  if (*(char *)(*(int *)(param_1 + 0x70) + 0x100) == '\0') {
    SetButtonReport__11CmdWolfBoutFi(param_1,1);
    Open__15CmdButtonReportFv(*(undefined4 *)(param_1 + 0x70));
    puVar2 = PTR_SelectStamp__11CmdWolfBoutFv_0050da18;
    uVar1 = DAT_0050da14;
    *(undefined4 *)(param_1 + 0x5c) = _6336;
    *(undefined4 *)(param_1 + 0x60) = uVar1;
    *(undefined **)(param_1 + 100) = puVar2;
  }
  return 0;
}

/* JP: 0x00484440  CmdWolfBout::Exit()   [Exit__11CmdWolfBoutFv]  size=0xec */
undefined4 Exit__11CmdWolfBoutFv(int param_1)

{
  bool bVar1;
  undefined4 uVar2;
  
  if ((*(char *)(*(int *)(param_1 + 0x84) + 0xa8) == '\x01') ||
     (*(char *)(*(int *)(param_1 + 0x84) + 0xa8) == '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if (bVar1) {
    (**(code **)(*(int *)(*(int *)(param_1 + 0x84) + 8) + 0xc))();
    *(undefined4 *)(param_1 + 0x84) = 0;
    if (*(short *)(*(int *)(param_1 + 0x80) + 0xae) != 0) {
      UpdateStamp__11CmdWolfBoutFss(param_1,0,0);
    }
    uVar2 = 1;
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

/* JP: 0x00484530  CmdWolfBout::SelectStamp()   [SelectStamp__11CmdWolfBoutFv]  size=0x5c8 */
undefined8 SelectStamp__11CmdWolfBoutFv(int param_1)

{
  undefined2 uVar1;
  ushort uVar2;
  int iVar3;
  int iVar4;
  undefined *puVar5;
  undefined4 uVar6;
  long lVar7;
  ulong uVar8;
  
  uVar2 = *(ushort *)(*(int *)(param_1 + 0x10) + 0x48);
  iVar3 = *(int *)(*(int *)(param_1 + 0x18) + 0xec);
  if ((uVar2 & 0x4000) == 0) {
    if ((uVar2 & 0x1000) == 0) {
      uVar8 = 0;
      if ((uVar2 & 0x10) == 0) {
        if ((uVar2 & 0x40) == 0) {
          if ((uVar2 & 0x80) == 0) {
            if ((uVar2 & 0x20) != 0) {
              uVar8 = 8;
            }
          }
          else {
            uVar8 = 4;
          }
        }
        else {
          uVar8 = 2;
        }
      }
      else {
        uVar8 = 1;
      }
      if (uVar8 != 0) {
        uVar2 = *(ushort *)(*(int *)(param_1 + 0x80) + 0xae);
        uVar1 = *(undefined2 *)(iVar3 + 0x1c);
        if (((((uVar2 == 0) &&
              ((long)(ulong)(byte)*(undefined2 *)(*(int *)(param_1 + 0x8c) + 4) <
               (long)*(char *)(param_1 + 0x22))) && (*(short *)(iVar3 + 0x1e) == 3)) &&
            ((uVar8 & 2) != 0)) || ((uVar2 != 0 && ((uVar8 & 1) != 0)))) {
          UpdateStamp__11CmdWolfBoutFss(param_1,0,uVar2 ^ 1);
          lVar7 = GetCornerPlace__10MenuWindowFis(*(undefined4 *)(param_1 + 0x80),2,uVar1);
          Select__6CursorFP9MenuPlace(*(undefined4 *)(param_1 + 0x18),lVar7);
          QuickMove__6CursorFv(*(undefined4 *)(param_1 + 0x18));
        }
        else {
          lVar7 = MoveCursor__6CursorFi(*(undefined4 *)(param_1 + 0x18),uVar8);
        }
        if (lVar7 != 0) {
          SetWolf__11CmdWolfBoutFs(param_1,*(undefined2 *)((int)lVar7 + 0x16));
          UpdateProfile__11CmdWolfBoutFs(param_1,0);
          Select__16CmdWolfBoutStampFP11CmdWolfBoutP9MenuPlaceP9MenuPlace
                    (*(undefined4 *)(param_1 + 0x80),param_1,lVar7,iVar3);
          PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x68),0,0,0);
        }
      }
    }
    else {
      lVar7 = __nw__FUi(0x52c);
      uVar6 = 0;
      if (lVar7 != 0) {
        uVar6 = __ct__10CmdExplainFv(lVar7);
      }
      *(undefined4 *)(param_1 + 0x7c) = uVar6;
      Initialize__9MenuSceneFPUcP9BufMemory(*(undefined4 *)(param_1 + 0x7c),
                      *(undefined4 *)(*(int *)(param_1 + 0x54) + 0x4c),0);
      SetInfo__10CmdExplainFP4MenusUcUc
                (*(undefined4 *)(param_1 + 0x7c),*(undefined4 *)(param_1 + 0x10),
                 *(undefined1 *)(param_1 + 0x22),0xc,1);
      SetImage__10CmdExplainFPcss
                (*(undefined4 *)(param_1 + 0x7c),*(undefined4 *)(*(int *)(param_1 + 0x24) + 0x10),1,
                 1);
      *(byte *)(*(int *)(param_1 + 0x18) + 0x12) = *(byte *)(*(int *)(param_1 + 0x18) + 0x12) & 0xfe
      ;
      iVar4 = *(int *)(param_1 + 0x80);
      Close__10MenuWindowFUci(iVar4,((ulong)*(byte *)(iVar4 + 0xb0) & 0x3f) >> 3,
                      *(undefined4 *)(*(int *)(iVar4 + 0x34) + 0x14));
      iVar4 = *(int *)(param_1 + 0x84);
      Close__10MenuWindowFUci(iVar4,((ulong)*(byte *)(iVar4 + 0xb0) & 0x3f) >> 3,
                      *(undefined4 *)(*(int *)(iVar4 + 0x34) + 0x14));
      iVar4 = *(int *)(*(int *)(param_1 + 0x58) + 0x78);
      Close__10MenuWindowFUci(iVar4 + 0x58,((ulong)*(byte *)(iVar4 + 0x108) & 0x3f) >> 3,
                      *(undefined4 *)(*(int *)(iVar4 + 0x8c) + 0x14));
      *(undefined2 *)(param_1 + 0x1e) = *(undefined2 *)(iVar3 + 0x22);
      SetButtonReport__11CmdWolfBoutFi(param_1,0);
      SetExplanation__7CmdNoteFPCce
                (*(undefined4 *)(*(int *)(param_1 + 0x58) + 100),
                 *(undefined4 *)(*(int *)(param_1 + 0x24) + 0x18));
      puVar5 = PTR_ShiftExplain__11CmdWolfBoutFv_0050da38;
      uVar6 = DAT_0050da34;
      *(undefined4 *)(param_1 + 0x5c) = _6380;
      *(undefined4 *)(param_1 + 0x60) = uVar6;
      *(undefined **)(param_1 + 100) = puVar5;
      PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x68),2,0,0);
    }
  }
  else {
    Leave__6CursorFv(*(undefined4 *)(param_1 + 0x18));
    iVar3 = *(int *)(param_1 + 0x84);
    Close__10MenuWindowFUci(iVar3,((ulong)*(byte *)(iVar3 + 0xb0) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar3 + 0x34) + 0x14));
    puVar5 = PTR_Exit__11CmdWolfBoutFv_0050da28;
    uVar6 = DAT_0050da24;
    *(undefined4 *)(param_1 + 0x5c) = _6374;
    *(undefined4 *)(param_1 + 0x60) = uVar6;
    *(undefined **)(param_1 + 100) = puVar5;
    PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x68),3,0,0);
  }
  return 0;
}

/* JP: 0x00484b00  CmdWolfBout::ShiftExplain()   [ShiftExplain__11CmdWolfBoutFv]  size=0x134 */
undefined8 ShiftExplain__11CmdWolfBoutFv(int param_1)

{
  bool bVar1;
  undefined4 uVar2;
  undefined *puVar3;
  
  puVar3 = PTR_SelectStamp__11CmdWolfBoutFv_0050da58;
  uVar2 = DAT_0050da54;
  if ((*(char *)(*(int *)(param_1 + 0x80) + 0xa8) == '\x01') ||
     (*(char *)(*(int *)(param_1 + 0x80) + 0xa8) == '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if (bVar1) {
    if (*(char *)(*(int *)(param_1 + 0x80) + 0xa8) == '\0') {
      SetExplanation__11CmdWolfBoutFv(param_1);
      puVar3 = PTR_ExecExplain__11CmdWolfBoutFv_0050da48;
      uVar2 = DAT_0050da44;
      *(undefined4 *)(param_1 + 0x5c) = _6488;
      *(undefined4 *)(param_1 + 0x60) = uVar2;
      *(undefined **)(param_1 + 100) = puVar3;
    }
    else {
      *(undefined4 *)(param_1 + 0x5c) = _6491;
      *(undefined4 *)(param_1 + 0x60) = uVar2;
      *(undefined **)(param_1 + 100) = puVar3;
    }
  }
  return 0;
}

/* JP: 0x00484c40  CmdWolfBout::ExecExplain()   [ExecExplain__11CmdWolfBoutFv]  size=0x470 */
undefined8 ExecExplain__11CmdWolfBoutFv(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined *puVar3;
  ushort uVar4;
  short sVar5;
  long lVar6;
  undefined8 uVar7;
  
  lVar6 = Exec__10CmdExplainFUs
                    (*(undefined4 *)(param_1 + 0x7c),
                     *(undefined2 *)(*(int *)(param_1 + 0x10) + 0x48));
  if (lVar6 != 0) {
    if ((int)lVar6 == 4) {
      if ((long)((ulong)*(byte *)(*(int *)(param_1 + 0x7c) + 0x525) << 0x3d) < 0) {
        uVar4 = *(ushort *)(*(int *)(param_1 + 0x8c) + 4) & 0xff;
        if (uVar4 == 0) {
          trap(7);
        }
        UpdateStamp__11CmdWolfBoutFss(param_1,1,*(short *)(param_1 + 0x1e) / (short)uVar4);
        UpdateProfile__11CmdWolfBoutFs(param_1,1);
        iVar1 = *(int *)(*(int *)(param_1 + 0x58) + 0x78);
        Open__10MenuWindowFUci(iVar1 + 0x58,*(byte *)(iVar1 + 0x108) & 7,
                        *(undefined4 *)(*(int *)(iVar1 + 0x8c) + 0x10));
        uVar7 = GetPlace__10MenuWindowFs(*(undefined4 *)(param_1 + 0x80),
                                *(undefined1 *)
                                 (*(int *)(*(int *)(*(int *)(param_1 + 0x58) + 0x5c) + 4) + 0xe44 +
                                 (int)*(short *)(param_1 + 0x1e)));
        Select__6CursorFP9MenuPlace(*(undefined4 *)(param_1 + 0x18),uVar7);
        QuickMove__6CursorFv(*(undefined4 *)(param_1 + 0x18));
        ClearAfter__6CursorFv(*(undefined4 *)(param_1 + 0x18));
        *(byte *)(*(int *)(param_1 + 0x18) + 0x12) =
             *(byte *)(*(int *)(param_1 + 0x18) + 0x12) & 0xfe | 1;
        Select__16CmdWolfBoutStampFP11CmdWolfBoutP9MenuPlaceP9MenuPlace
                  (*(undefined4 *)(param_1 + 0x80),param_1,uVar7,0);
        SetButtonReport__11CmdWolfBoutFi(param_1,1);
        (**(code **)(*(int *)(*(int *)(param_1 + 0x7c) + 8) + 0xc))();
        puVar3 = PTR_ShiftExplain__11CmdWolfBoutFv_0050da68;
        uVar2 = DAT_0050da64;
        *(undefined4 *)(param_1 + 0x5c) = _6521;
        *(undefined4 *)(param_1 + 0x60) = uVar2;
        *(undefined **)(param_1 + 100) = puVar3;
      }
      else {
        sVar5 = 1;
        if ((*(byte *)(*(int *)(param_1 + 0x7c) + 0x524) >> 4 & 4) != 0) {
          sVar5 = -1;
        }
        *(short *)(param_1 + 0x1e) = *(short *)(param_1 + 0x1e) + sVar5;
        if (*(short *)(param_1 + 0x1e) < 0) {
          *(short *)(param_1 + 0x1e) = *(char *)(param_1 + 0x22) + -1;
        }
        else if ((short)*(char *)(param_1 + 0x22) <= *(short *)(param_1 + 0x1e)) {
          *(undefined2 *)(param_1 + 0x1e) = 0;
        }
        SetWolf__11CmdWolfBoutFs
                  (param_1,*(undefined1 *)
                            (*(int *)(*(int *)(*(int *)(param_1 + 0x58) + 0x5c) + 4) + 0xe44 +
                            (int)*(short *)(param_1 + 0x1e)));
        SetExplanation__11CmdWolfBoutFv(param_1);
      }
    }
    else if ((int)lVar6 == 3) {
      Destroy__16MenuModelManegerFUc(*(undefined4 *)(param_1 + 0x6c),0);
    }
  }
  return 0;
}

/* JP: 0x004850b0  CmdWolfBout::DisplayMessage()   [DisplayMessage__11CmdWolfBoutFv]  size=0x194 */
undefined4 DisplayMessage__11CmdWolfBoutFv(int param_1)

{
  int iVar1;
  bool bVar2;
  long lVar3;
  
  if (*(char *)(param_1 + 0x21) == '\x01') {
    if ((*(char *)(*(int *)(param_1 + 0x78) + 0xa8) == '\x01') ||
       (*(char *)(*(int *)(param_1 + 0x78) + 0xa8) == '\0')) {
      bVar2 = true;
    }
    else {
      bVar2 = false;
    }
    if (bVar2) {
      (**(code **)(*(int *)(*(int *)(param_1 + 0x78) + 8) + 0xc))();
      *(undefined4 *)(param_1 + 0x78) = 0;
      *(undefined1 *)(param_1 + 0x21) = 0;
      return 1;
    }
  }
  else if ((*(char *)(param_1 + 0x21) == '\0') &&
          (lVar3 = Run__14CmdNoteMessageFUs
                             (*(undefined4 *)(param_1 + 0x78),
                              *(undefined2 *)(*(int *)(param_1 + 0x10) + 0x48)), lVar3 != 0)) {
    iVar1 = *(int *)(param_1 + 0x78);
    Close__10MenuWindowFUci(iVar1,((ulong)*(byte *)(iVar1 + 0xb0) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x14));
    *(char *)(param_1 + 0x21) = *(char *)(param_1 + 0x21) + '\x01';
  }
  return 0;
}
