/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdAroma   functions: 13
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdAroma.md).
 */

/* JP: 0x0045f4e0  CmdAroma::CmdAroma()   [__ct__8CmdAromaFv]  size=0x5c */
int __ct__8CmdAromaFv(int param_1)

{
  __ct__15CmdPrivateSceneFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__8CmdAroma;
  __ct__15CmdAromaBaseOilFv(param_1 + 0x70);
  __ct__13CmdAromaBlendFv(param_1 + 0x3f0);
  return param_1;
}

/* JP: 0x0045f540  CmdAroma::~CmdAroma()   [__dt__8CmdAromaFv]  size=0x9c */
int __dt__8CmdAromaFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__8CmdAroma;
    __dt__13CmdAromaBlendFv(param_1 + 0x3f0,0xffffffffffffffff);
    __dt__15CmdAromaBaseOilFv(param_1 + 0x70,0xffffffffffffffff);
    __dt__15CmdPrivateSceneFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x0045f5e0  CmdAroma::GetReady()   [GetReady__8CmdAromaFv]  size=0x1ac */
undefined4 GetReady__8CmdAromaFv(int param_1)

{
  int iVar1;
  undefined2 uVar2;
  undefined4 uVar3;
  
  iVar1 = *(int *)(param_1 + 0x10);
  *(int *)(param_1 + 0x18) = iVar1 + 0x3a0;
  uVar2 = GetRegCnt__9RegDatApiFii(0x3c,0xffffffffffffffff);
  *(undefined2 *)(param_1 + 0x518) = uVar2;
  uVar3 = Find__13MenuDataTableFs(iVar1 + 0x28,0x12);
  *(undefined4 *)(param_1 + 0x51c) = uVar3;
  SetTitle__11CmdTitleLogFPUci
            (*(undefined4 *)(*(int *)(param_1 + 0x58) + 0x60),
             *(undefined4 *)(*(int *)(param_1 + 0x54) + 0x10),0x14);
  Open__11CmdTitleLogFv(*(undefined4 *)(*(int *)(param_1 + 0x58) + 0x60));
  CreateScene__15CmdAromaBaseOilFP8CmdAroma(param_1 + 0x70,param_1);
  CreateScene__13CmdAromaBlendFP8CmdAroma(param_1 + 0x3f0,param_1);
  Open__10MenuWindowFUci(param_1 + 0x70,*(byte *)(param_1 + 0x120) & 7,
                  *(undefined4 *)(*(int *)(param_1 + 0xa4) + 0x10));
  *(byte *)(param_1 + 0x23) = *(byte *)(param_1 + 0x23) & 0xdf | 0x20;
  return 1;
}

/* JP: 0x0045f790  CmdAroma::Run()   [Run__8CmdAromaFv]  size=0x68 */
undefined4 Run__8CmdAromaFv(int param_1)

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

/* JP: 0x0045f800  CmdAroma::SafeDelayDelete()   [SafeDelayDelete__8CmdAromaFv]  size=0x50 */
void SafeDelayDelete__8CmdAromaFv(int param_1)

{
  ReleaseOT__7MenuObjFv(param_1 + 0x70);
  ReleaseOT__7MenuObjFv(param_1 + 0x3f0);
  (**(code **)(*(int *)(param_1 + 8) + 0xc))();
  return;
}

/* JP: 0x0045f850  CmdAroma::Close()   [Close__8CmdAromaFv]  size=0x48 */
void Close__8CmdAromaFv(int param_1)

{
  Close__10MenuWindowFUci(param_1 + 0x70,((ulong)*(byte *)(param_1 + 0x120) & 0x3f) >> 3,
                  *(undefined4 *)(*(int *)(param_1 + 0xa4) + 0x14));
  return;
}

/* JP: 0x0045f8a0  CmdAroma::ReadyScene()   [ReadyScene__8CmdAromaFv]  size=0x178 */
undefined4 ReadyScene__8CmdAromaFv(int param_1)

{
  undefined4 uVar1;
  undefined *puVar2;
  undefined8 uVar3;
  
  uVar3 = GetPlace__10MenuWindowFss(param_1 + 0x70,0,0);
  Select__6CursorFP9MenuPlace(*(undefined4 *)(param_1 + 0x18),uVar3);
  Select__15CmdAromaBaseOilFP8CmdAromaP9MenuGroupP9MenuGroup
            (param_1 + 0x70,param_1,*(undefined4 *)(*(int *)(param_1 + 0x18) + 0xec),0);
  *(undefined2 *)(param_1 + 0x49c) = 0x8000;
  UpdateScene__13CmdAromaBlendFP8CmdAromas
            (param_1 + 0x3f0,param_1,
             *(undefined2 *)(*(int *)(*(int *)(param_1 + 0x18) + 0xec) + 0x16));
  Close__10CmdElementFv(*(undefined4 *)(*(int *)(param_1 + 0x58) + 0x6c));
  SetChengePCMode__10CmdPCSceneFUc(*(undefined4 *)(param_1 + 0x58),0);
  puVar2 = PTR_SelectBaseOil__8CmdAromaFv_0050d5b0;
  uVar1 = DAT_0050d5ac;
  *(undefined4 *)(param_1 + 0x5c) = _5219;
  *(undefined4 *)(param_1 + 0x60) = uVar1;
  *(undefined **)(param_1 + 100) = puVar2;
  return 1;
}

/* JP: 0x0045fa20  CmdAroma::SetExplanation()   [SetExplanation__8CmdAromaFv]  size=0x12c */
void SetExplanation__8CmdAromaFv(int param_1)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  
  iVar2 = *(int *)(param_1 + 0x68);
  memset(iVar2 + 0x5c,0,0x10);
  uVar1 = *(ushort *)(*(int *)(*(int *)(param_1 + 0x18) + 0xec) + 0x16);
  iVar3 = *(int *)(param_1 + 0x51c);
  *(ushort *)(iVar2 + 0x5c) = uVar1;
  *(char *)(iVar2 + 0x5e) = (char)*(undefined2 *)(*(int *)(param_1 + 0x51c) + 4);
  uVar4 = GetRegDat__9RegDatApiFiii(0x10,uVar1,0xffffffffffffffff);
  *(undefined4 *)(iVar2 + 0x60) = uVar4;
  *(uint *)(iVar2 + 0x68) = (uint)uVar1 * 8 + iVar3 + 0x14;
  Open__10CmdExplainFv(*(undefined4 *)(param_1 + 0x68));
  return;
}

/* JP: 0x0045fb50  CmdAroma::SelectBaseOil()   [SelectBaseOil__8CmdAromaFv]  size=0x424 */
undefined4 SelectBaseOil__8CmdAromaFv(int param_1)

{
  ushort uVar1;
  int iVar2;
  undefined *puVar3;
  undefined4 uVar4;
  int iVar5;
  undefined8 uVar6;
  long lVar7;
  
  uVar1 = *(ushort *)(*(int *)(param_1 + 0x10) + 0x48);
  iVar2 = *(int *)(*(int *)(param_1 + 0x18) + 0xec);
  if ((uVar1 & 0x2000) == 0) {
    if ((uVar1 & 0x4000) != 0) {
      Select__15CmdAromaBaseOilFP8CmdAromaP9MenuGroupP9MenuGroup(param_1 + 0x70,param_1,0,iVar2);
      Close__10MenuWindowFUci(param_1 + 0x3f0,((ulong)*(byte *)(param_1 + 0x4a0) & 0x3f) >> 3,
                      *(undefined4 *)(*(int *)(param_1 + 0x424) + 0x14));
      return 1;
    }
    if ((uVar1 & 0x1000) == 0) {
      iVar5 = MoveVertical__9MenuSceneFi(param_1,0);
      if (iVar2 != iVar5) {
        Select__15CmdAromaBaseOilFP8CmdAromaP9MenuGroupP9MenuGroup
                  (param_1 + 0x70,param_1,iVar5,iVar2);
        UpdateScene__13CmdAromaBlendFP8CmdAromas
                  (param_1 + 0x3f0,param_1,*(undefined2 *)(iVar5 + 0x16));
      }
    }
    else {
      lVar7 = __nw__FUi(0x52c);
      uVar4 = 0;
      if (lVar7 != 0) {
        uVar4 = __ct__10CmdExplainFv(lVar7);
      }
      *(undefined4 *)(param_1 + 0x68) = uVar4;
      Initialize__9MenuSceneFPUcP9BufMemory(*(undefined4 *)(param_1 + 0x68),
                      *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x58) + 0x54) + 0x34),0);
      SetInfo__10CmdExplainFP4MenusUcUc
                (*(undefined4 *)(param_1 + 0x68),*(undefined4 *)(param_1 + 0x10),
                 *(undefined2 *)(param_1 + 0x11e),3,0);
      SetIcon__10CmdExplainFP11MenuTexture(*(undefined4 *)(param_1 + 0x68),0x421698);
      SetImage__10CmdExplainFPcss
                (*(undefined4 *)(param_1 + 0x68),*(undefined4 *)(*(int *)(param_1 + 0x24) + 0x20),1,
                 0);
      *(byte *)(*(int *)(param_1 + 0x18) + 0x12) = *(byte *)(*(int *)(param_1 + 0x18) + 0x12) & 0xfe
      ;
      SetExplanation__7CmdNoteFPCce
                (*(undefined4 *)(*(int *)(param_1 + 0x58) + 100),
                 *(undefined4 *)(*(int *)(param_1 + 0x28) + 0x14));
      Close__10MenuWindowFUci(param_1 + 0x70,((ulong)*(byte *)(param_1 + 0x120) & 0x3f) >> 3,
                      *(undefined4 *)(*(int *)(param_1 + 0xa4) + 0x14));
      Close__10MenuWindowFUci(param_1 + 0x3f0,((ulong)*(byte *)(param_1 + 0x4a0) & 0x3f) >> 3,
                      *(undefined4 *)(*(int *)(param_1 + 0x424) + 0x14));
      iVar2 = *(int *)(*(int *)(param_1 + 0x58) + 0x78);
      Close__10MenuWindowFUci(iVar2 + 0x58,((ulong)*(byte *)(iVar2 + 0x108) & 0x3f) >> 3,
                      *(undefined4 *)(*(int *)(iVar2 + 0x8c) + 0x14));
      puVar3 = PTR_ShiftExplain__8CmdAromaFv_0050d5d0;
      uVar4 = DAT_0050d5cc;
      *(undefined4 *)(param_1 + 0x5c) = _5293;
      *(undefined4 *)(param_1 + 0x60) = uVar4;
      *(undefined **)(param_1 + 100) = puVar3;
    }
  }
  else {
    uVar6 = GetPlace__10MenuWindowFss(param_1 + 0x3f0,0,0);
    Select__6CursorFP9MenuPlace(*(undefined4 *)(param_1 + 0x18),uVar6);
    Select__13CmdAromaBlendFP8CmdAromaP9MenuGroupP9MenuGroup(param_1 + 0x3f0,param_1,uVar6,0);
    puVar3 = PTR_SelectBlend__8CmdAromaFv_0050d5c0;
    uVar4 = DAT_0050d5bc;
    *(undefined4 *)(param_1 + 0x5c) = _5284;
    *(undefined4 *)(param_1 + 0x60) = uVar4;
    *(undefined **)(param_1 + 100) = puVar3;
  }
  return 0;
}

/* JP: 0x0045ff80  CmdAroma::SelectBlend()   [SelectBlend__8CmdAromaFv]  size=0x220 */
undefined8 SelectBlend__8CmdAromaFv(int param_1)

{
  ushort uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined *puVar4;
  undefined8 uVar5;
  
  uVar1 = *(ushort *)(*(int *)(param_1 + 0x10) + 0x48);
  iVar2 = *(int *)(*(int *)(param_1 + 0x18) + 0xec);
  if ((uVar1 & 0x4000) == 0) {
    if ((uVar1 & 0x10) == 0) {
      if ((uVar1 & 0x40) != 0) {
        MoveCursor__6CursorFi(*(undefined4 *)(param_1 + 0x18),2);
      }
    }
    else {
      MoveCursor__6CursorFi(*(undefined4 *)(param_1 + 0x18),1);
    }
    if (iVar2 != *(int *)(*(int *)(param_1 + 0x18) + 0xec)) {
      Select__13CmdAromaBlendFP8CmdAromaP9MenuGroupP9MenuGroup
                (param_1 + 0x3f0,param_1,*(undefined4 *)(*(int *)(param_1 + 0x18) + 0xec),iVar2);
    }
  }
  else {
    uVar5 = GetPlace__10MenuWindowFs(param_1 + 0x70,*(undefined2 *)(param_1 + 0x49e));
    Select__6CursorFP9MenuPlace(*(undefined4 *)(param_1 + 0x18),uVar5);
    Select__13CmdAromaBlendFP8CmdAromaP9MenuGroupP9MenuGroup(param_1 + 0x3f0,param_1,0,iVar2);
    Select__15CmdAromaBaseOilFP8CmdAromaP9MenuGroupP9MenuGroup
              (param_1 + 0x70,param_1,*(undefined4 *)(*(int *)(param_1 + 0x18) + 0xec),0);
    puVar4 = PTR_SelectBaseOil__8CmdAromaFv_0050d5e0;
    uVar3 = DAT_0050d5dc;
    *(undefined4 *)(param_1 + 0x5c) = _5362;
    *(undefined4 *)(param_1 + 0x60) = uVar3;
    *(undefined **)(param_1 + 100) = puVar4;
  }
  return 0;
}

/* JP: 0x004601a0  CmdAroma::ShiftExplain()   [ShiftExplain__8CmdAromaFv]  size=0x168 */
undefined8 ShiftExplain__8CmdAromaFv(int param_1)

{
  bool bVar1;
  undefined4 uVar2;
  undefined *puVar3;
  
  puVar3 = PTR_SelectBaseOil__8CmdAromaFv_0050d600;
  uVar2 = DAT_0050d5fc;
  if ((*(char *)(param_1 + 0x118) == '\x01') || (*(char *)(param_1 + 0x118) == '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if (bVar1) {
    if (*(char *)(param_1 + 0x118) == '\0') {
      Select__15CmdAromaBaseOilFP8CmdAromaP9MenuGroupP9MenuGroup
                (param_1 + 0x70,param_1,0,*(undefined4 *)(*(int *)(param_1 + 0x18) + 0xec));
      SetExplanation__8CmdAromaFv(param_1);
      puVar3 = PTR_ExecExplain__8CmdAromaFv_0050d5f0;
      uVar2 = DAT_0050d5ec;
      *(undefined4 *)(param_1 + 0x5c) = _5419;
      *(undefined4 *)(param_1 + 0x60) = uVar2;
      *(undefined **)(param_1 + 100) = puVar3;
    }
    else {
      *(undefined4 *)(param_1 + 0x5c) = _5422;
      *(undefined4 *)(param_1 + 0x60) = uVar2;
      *(undefined **)(param_1 + 100) = puVar3;
    }
  }
  return 0;
}

/* JP: 0x00460310  CmdAroma::ExecExplain()   [ExecExplain__8CmdAromaFv]  size=0x260 */
undefined8 ExecExplain__8CmdAromaFv(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined *puVar3;
  long lVar4;
  
  lVar4 = Exec__10CmdExplainFUs
                    (*(undefined4 *)(param_1 + 0x68),
                     *(undefined2 *)(*(int *)(param_1 + 0x10) + 0x48));
  if ((lVar4 != 0) && ((int)lVar4 == 4)) {
    if ((long)((ulong)*(byte *)(*(int *)(param_1 + 0x68) + 0x525) << 0x3d) < 0) {
      Finish__10MenuWindowFv(param_1 + 0x70);
      Select__15CmdAromaBaseOilFP8CmdAromaP9MenuGroupP9MenuGroup
                (param_1 + 0x70,param_1,*(undefined4 *)(*(int *)(param_1 + 0x18) + 0xec),0);
      Restore__6CursorFv(*(undefined4 *)(param_1 + 0x18));
      Open__10MenuWindowFUci(param_1 + 0x70,*(byte *)(param_1 + 0x120) & 7,
                      *(undefined4 *)(*(int *)(param_1 + 0xa4) + 0x10));
      UpdateScene__13CmdAromaBlendFP8CmdAromas
                (param_1 + 0x3f0,param_1,
                 *(undefined2 *)(*(int *)(*(int *)(param_1 + 0x18) + 0xec) + 0x16));
      iVar1 = *(int *)(*(int *)(param_1 + 0x58) + 0x78);
      Open__10MenuWindowFUci(iVar1 + 0x58,*(byte *)(iVar1 + 0x108) & 7,
                      *(undefined4 *)(*(int *)(iVar1 + 0x8c) + 0x10));
      (**(code **)(*(int *)(*(int *)(param_1 + 0x68) + 8) + 0xc))();
      puVar3 = PTR_ShiftExplain__8CmdAromaFv_0050d610;
      uVar2 = DAT_0050d60c;
      *(undefined4 *)(param_1 + 0x5c) = _5451;
      *(undefined4 *)(param_1 + 0x60) = uVar2;
      *(undefined **)(param_1 + 100) = puVar3;
    }
    else {
      MoveCursor__6CursorFi(*(undefined4 *)(param_1 + 0x18),
                      *(byte *)(*(int *)(param_1 + 0x68) + 0x524) >> 4);
      SetExplanation__8CmdAromaFv(param_1);
    }
  }
  return 0;
}

/* JP: 0x00460570  CmdAroma::Release()   [Release__8CmdAromaFv]  size=0x10 */
void Release__8CmdAromaFv(void)

{
  return;
}
