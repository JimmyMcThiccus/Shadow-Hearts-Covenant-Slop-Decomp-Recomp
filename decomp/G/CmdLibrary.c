/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdLibrary   functions: 20
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdLibrary.md).
 */

/* JP: 0x004619c0  CmdLibrary::CmdLibrary()   [__ct__10CmdLibraryFv]  size=0x9c */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __ct__10CmdLibraryFv(int param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  __ct__9MenuSceneFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__10CmdLibrary;
  uVar2 = uRam004236d0;
  uVar1 = uRam004236cc;
  *(undefined4 *)(param_1 + 0x58) = ___ptmf_null;
  *(undefined4 *)(param_1 + 0x5c) = uVar1;
  *(undefined4 *)(param_1 + 0x60) = uVar2;
  __ct__10CmdSubMenuFv(param_1 + 100);
  *(undefined4 *)(param_1 + 0x1b8) = 0;
  *(undefined4 *)(param_1 + 0x1bc) = 0;
  *(undefined4 *)(param_1 + 0x1c0) = 0;
  *(undefined4 *)(param_1 + 0x1c4) = 0;
  *(undefined4 *)(param_1 + 0x1c8) = 0;
  return param_1;
}

/* JP: 0x00461a60  CmdLibrary::~CmdLibrary()   [__dt__10CmdLibraryFv]  size=0xc8 */
int __dt__10CmdLibraryFv(int param_1,short param_2)

{
  int iVar1;
  
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__10CmdLibrary;
    if (*(int *)(param_1 + 0x1bc) != 0) {
      iVar1 = *(int *)(param_1 + 0x1bc);
      if (iVar1 != 0) {
        (**(code **)(*(int *)(iVar1 + 8) + 8))(iVar1,1);
      }
    }
    __dt__10CmdSubMenuFv(param_1 + 100,0xffffffffffffffff);
    __dt__9MenuSceneFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x00461b30  CmdLibrary::GetReady()   [GetReady__10CmdLibraryFv]  size=0x30c */
undefined4 GetReady__10CmdLibraryFv(int param_1)

{
  undefined *puVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  long lVar5;
  short sVar6;
  ushort uVar7;
  ushort uVar8;
  
  iVar4 = *(int *)(param_1 + 0x10);
  iVar2 = iVar4 + 0x28;
  *(int *)(param_1 + 0x1e0) = iVar4 + 0x348;
  *(int *)(param_1 + 0x1e4) = iVar4 + 0xb8;
  *(int *)(param_1 + 0x1e8) = iVar4 + 0x4e0;
  *(int *)(param_1 + 0x1f0) = iVar4 + 0xa60;
  *(int *)(param_1 + 0x1ec) = iVar4 + 0x780;
  *(int *)(param_1 + 500) = iVar4 + 0x10f0;
  *(undefined4 *)(param_1 + 0x1f8) = *(undefined4 *)(iVar4 + 0x68);
  *(int *)(param_1 + 0x18) = iVar4 + 0x3a0;
  *(undefined4 *)(param_1 + 0x1dc) = sm_pSound__7MenuObj;
  uVar3 = Find__13MenuDataTableFs(iVar2,0x14);
  *(undefined4 *)(param_1 + 0x1fc) = uVar3;
  uVar3 = Find__13MenuDataTableFs(iVar2,0x13);
  *(undefined4 *)(param_1 + 0x200) = uVar3;
  iVar4 = Find__13MenuDataTableFs(iVar2,0x30);
  *(int *)(param_1 + 0x204) = iVar4 + 0x10;
  for (uVar8 = 2; (short)uVar8 < 5; uVar8 = uVar8 + 1) {
    Convert__13MenuDataTableFPUci(*(undefined4 *)((uint)uVar8 * 0xc + *(int *)(param_1 + 0x54) + 0x10),0);
  }
  Initialize__9MenuSceneFPUcP9BufMemory(param_1 + 100,*(undefined4 *)(*(int *)(param_1 + 0x54) + 0x28),0);
  CreateScene__10CmdSubMenuFsP9MSDSystem(param_1 + 100,3,*(int *)(param_1 + 0x28) + 0x10);
  uVar8 = 0;
  uVar7 = 0;
  for (sVar6 = 0; sVar6 < 2; sVar6 = sVar6 + 1) {
    *(undefined2 *)(param_1 + 0x1cc) = 0xffff;
    lVar5 = Find__10CmdLibraryFss(param_1,sVar6,1);
    if ((lVar5 != 0) && (lVar5 = Find__10CmdLibraryFss(param_1,sVar6,1), lVar5 != 0)) {
      uVar7 = uVar8 | (ushort)(1 << ((int)sVar6 & 0x1fU));
      uVar8 = uVar7;
    }
  }
  *(ushort *)(param_1 + 0x80) = uVar7;
  puVar1 = PTR_Enter__10CmdLibraryFv_0050d620;
  uVar3 = DAT_0050d61c;
  *(undefined4 *)(param_1 + 0x58) = _6087;
  *(undefined4 *)(param_1 + 0x5c) = uVar3;
  *(undefined **)(param_1 + 0x60) = puVar1;
  return 1;
}

/* JP: 0x00461e40  CmdLibrary::Run()   [Run__10CmdLibraryFv]  size=0x5c */
undefined8 Run__10CmdLibraryFv(int param_1)

{
  long lVar1;
  
  do {
    lVar1 = __ptmf_test(param_1 + 0x58);
    if (lVar1 == 0) {
      return 0;
    }
    lVar1 = __ptmf_scall(param_1);
  } while (lVar1 != 0);
  return 0;
}

/* JP: 0x00461ea0  CmdLibrary::Create(short)   [Create__10CmdLibraryFs]  size=0x2ac */
void Create__10CmdLibraryFs(int param_1,short param_2)

{
  undefined4 uVar1;
  long lVar2;
  
  if (*(int *)(param_1 + 0x1b8) != 0) {
    (**(code **)(*(int *)(*(int *)(param_1 + 0x1b8) + 8) + 0xc))();
  }
  if (*(int *)(param_1 + 0x1c0) != 0) {
    (**(code **)(*(int *)(*(int *)(param_1 + 0x1c0) + 8) + 0xc))();
    *(undefined4 *)(param_1 + 0x1c0) = 0;
  }
  if (*(int *)(param_1 + 0x1c4) != 0) {
    (**(code **)(*(int *)(*(int *)(param_1 + 0x1c4) + 8) + 0xc))();
    *(undefined4 *)(param_1 + 0x1c4) = 0;
  }
  lVar2 = __nw__FUi(0x52c);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = __ct__10CmdExplainFv(lVar2);
  }
  *(undefined4 *)(param_1 + 0x1b8) = uVar1;
  Initialize__9MenuSceneFPUcP9BufMemory(*(undefined4 *)(param_1 + 0x1b8),*(undefined4 *)(*(int *)(param_1 + 0x54) + 0x40),
                  0);
  SetInfo__10CmdExplainFP4MenusUcUc
            (*(undefined4 *)(param_1 + 0x1b8),*(undefined4 *)(param_1 + 0x10),
             ((ushort)((int)*(short *)(param_1 + 0x80) >> ((int)param_2 & 0x1fU)) & 1) + 1,0xc,1);
  *(undefined2 *)(*(int *)(param_1 + 0x1b8) + 0x526) = 0;
  if (-1 < *(short *)(param_1 + 0x1cc)) {
    lVar2 = __nw__FUi(0x308);
    uVar1 = 0;
    if (lVar2 != 0) {
      uVar1 = __ct__14CmdLibraryInfoFv(lVar2);
    }
    *(undefined4 *)(param_1 + 0x1c0) = uVar1;
    CreateScene__14CmdLibraryInfoFP10CmdLibrarys(*(undefined4 *)(param_1 + 0x1c0),param_1,param_2);
    if (param_2 == 1) {
      SetImage__10CmdExplainFPcss
                (*(undefined4 *)(param_1 + 0x1b8),*(undefined4 *)(*(int *)(param_1 + 0x24) + 0x40),1
                 ,0);
      *(undefined1 *)(param_1 + 0x22) = 0;
      AddPlace__10MenuWindowFP9MenuPlace(*(undefined4 *)(*(int *)(param_1 + 0x1b8) + 0x520),
                      *(int *)(param_1 + 0x1c0) + 0x128);
    }
  }
  return;
}

/* JP: 0x00462150  CmdLibrary::Update(short)   [Update__10CmdLibraryFs]  size=0x5cc */
void Update__10CmdLibraryFs(int param_1,short param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  byte unaff_s5_lo;
  
  iVar1 = *(int *)(param_1 + 0x1b8);
  memset(iVar1 + 0x5c,0,0x10);
  ClearReport__15CmdButtonReportFv(*(undefined4 *)(param_1 + 0x1f0));
  UpdateTitle__10CmdLibraryFs(param_1,param_2);
  if (*(short *)(param_1 + 0x1cc) < 0) {
    *(int *)(iVar1 + 0x68) = *(int *)(param_1 + 0x28) + 0x28;
  }
  else {
    iVar2 = *(int *)(param_1 + 0x1f0);
    iVar3 = *(int *)(param_1 + 0x1f8);
    *(undefined2 *)(iVar1 + 0x5c) = *(undefined2 *)(param_1 + 0x1ce);
    Reset__16MenuModelManegerFv(iVar3);
    iVar4 = *(int *)(iVar3 + 0x18);
    if (param_2 == 0) {
      iVar5 = *(short *)(param_1 + 0x1cc) * 0x20 + *(int *)(param_1 + 0x1fc);
      uVar6 = GetRegDat__9RegDatApiFiii(5,*(undefined2 *)(param_1 + 0x1ce),0xffffffffffffffff);
      *(undefined4 *)(iVar1 + 0x60) = uVar6;
      *(undefined4 *)(iVar1 + 100) = *(undefined4 *)(iVar5 + 0x10);
      *(int *)(iVar1 + 0x68) = iVar5 + 0x18;
      *(undefined4 *)(iVar4 + 0x10) = *(undefined4 *)(param_1 + 0x204);
      *(int *)(iVar4 + 0x14) = *(int *)(param_1 + 0x204) + 0x14;
      UpdateData__10CmdLibraryFv(param_1);
      unaff_s5_lo = *(byte *)(param_1 + 0x22);
      if (*(int *)(param_1 + 0x1c4) != 0) {
        unaff_s5_lo = 0;
      }
    }
    else if (param_2 == 1) {
      iVar5 = (*(short *)(param_1 + 0x1cc) * 0x1c + (int)*(short *)(param_1 + 0x1cc)) * 4 +
              *(int *)(param_1 + 0x200);
      *(undefined1 *)(iVar1 + 0x5f) = *(undefined1 *)(param_1 + 0x20);
      *(undefined4 *)(iVar1 + 0x60) = *(undefined4 *)(iVar5 + 0x10);
      *(undefined4 *)(iVar1 + 100) = *(undefined4 *)(iVar5 + 0x14);
      *(int *)(iVar1 + 0x68) = iVar5 + 0x1c;
      *(byte *)(*(int *)(param_1 + 0x1b8) + 0x525) =
           *(byte *)(*(int *)(param_1 + 0x1b8) + 0x525) & 0xf7 |
           (*(byte *)(param_1 + 0x1d1) & 1) << 3;
      *(int *)(iVar4 + 0x10) = iVar5 + 0x2c;
      *(int *)(iVar4 + 0x14) = iVar5 + 0x40;
      unaff_s5_lo = *(byte *)(param_1 + 0x1d1);
    }
    *(undefined2 *)(iVar3 + 0x68) = *(undefined2 *)(param_1 + 0x1e);
    uVar6 = *(undefined4 *)((uint)*(byte *)(param_1 + 0x1d2) * 8 + *(int *)(param_1 + 0x24) + 0x10);
    *(undefined2 *)(iVar3 + 0x3c) = *(undefined2 *)(param_1 + 0x1e);
    *(undefined4 *)(iVar3 + 0x24) = uVar6;
    if (*(char *)(param_1 + 0x1d3) != '\0') {
      uVar6 = *(undefined4 *)
               ((uint)(ushort)(*(byte *)(param_1 + 0x1d2) + 2) * 8 + *(int *)(param_1 + 0x24) + 0x10
               );
      *(undefined2 *)(iVar3 + 0x3e) = *(undefined2 *)(param_1 + 0x1e);
      *(undefined4 *)(iVar3 + 0x28) = uVar6;
    }
    if (-1 < *(char *)(param_1 + 0x1d5)) {
      if ('c' < *(char *)(param_1 + 0x1d5)) {
        *(char *)(param_1 + 0x1d5) = *(char *)(param_1 + 0x1d5) + -100;
        uVar6 = *(undefined4 *)(*(int *)(param_1 + 0x24) + 0x38);
        *(short *)(iVar3 + 0x3a) = (short)*(char *)(param_1 + 0x1d5);
        *(undefined4 *)(iVar3 + 0x20) = uVar6;
      }
      uVar6 = *(undefined4 *)(*(int *)(param_1 + 0x24) + 0x30);
      *(short *)(iVar3 + 0x38) = (short)*(char *)(param_1 + 0x1d5);
      *(undefined4 *)(iVar3 + 0x1c) = uVar6;
    }
    Access__16MenuModelManegerFv(iVar3);
    SetCamera__7CmdMenuFP13MenuDataModel
              (*(undefined4 *)(param_1 + 0x10),*(undefined4 *)(param_1 + 0x1d8));
    Create__10CmdElementFUc(*(undefined4 *)(param_1 + 500),*(undefined1 *)(param_1 + 0x1d0));
    Open__10CmdElementFv(*(undefined4 *)(param_1 + 500));
    UpdateScene__14CmdLibraryInfoFP10CmdLibrarys
              (*(undefined4 *)(param_1 + 0x1c0),param_1,*(short *)(param_1 + 0x1cc) + 1);
    *(byte *)(*(int *)(param_1 + 0x1c0) + 0x13a) =
         *(byte *)(*(int *)(param_1 + 0x1c0) + 0x13a) & 0xfe | unaff_s5_lo & 1;
    SetReport__15CmdButtonReportFii(iVar2,*(undefined1 *)(iVar2 + 0x20),0xc);
    SetReport__15CmdButtonReportFii(iVar2,*(undefined1 *)(iVar2 + 0x20),7);
    if (((param_2 == 0) && (*(char *)(param_1 + 0x22) != '\0')) &&
       (*(byte *)(param_1 + 0x23) >> 6 == 0)) {
      SetReport__15CmdButtonReportFii(iVar2,*(undefined1 *)(iVar2 + 0x20),0x11);
    }
    SetReport__15CmdButtonReportFii(iVar2,*(undefined1 *)(iVar2 + 0x20),0xb);
  }
  Open__10CmdExplainFv(*(undefined4 *)(param_1 + 0x1b8));
  return;
}

/* JP: 0x00462720  CmdLibrary::UpdateData()   [UpdateData__10CmdLibraryFv]  size=0x24c */
void UpdateData__10CmdLibraryFv(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  long lVar3;
  
  if (*(byte *)(param_1 + 0x23) >> 6 == 0) {
    if (*(int *)(param_1 + 0x1c4) != 0) {
      (**(code **)(*(int *)(*(int *)(param_1 + 0x1c4) + 8) + 0xc))();
      *(undefined4 *)(param_1 + 0x1c4) = 0;
    }
    Reset__10CmdExplainFv(*(undefined4 *)(param_1 + 0x1b8));
    *(byte *)(*(int *)(param_1 + 0x1b8) + 0x24e) =
         *(byte *)(*(int *)(param_1 + 0x1b8) + 0x24e) & 0xfe | 1;
    SetExplanation__7CmdNoteFPCce
              (*(undefined4 *)(param_1 + 0x1e8),
               *(undefined4 *)
                ((uint)*(ushort *)(*(int *)(*(int *)(param_1 + 0x18) + 0xec) + 0x1e) * 0xc +
                 *(int *)(param_1 + 0x28) + 0x14));
  }
  else {
    if (*(int *)(param_1 + 0x1c4) == 0) {
      lVar3 = __nw__FUi(0x1424);
      uVar2 = 0;
      if (lVar3 != 0) {
        uVar2 = __ct__16CmdLibraryDetailFv(lVar3);
      }
      *(undefined4 *)(param_1 + 0x1c4) = uVar2;
      CreateScene__16CmdLibraryDetailFP10CmdLibrary(*(undefined4 *)(param_1 + 0x1c4),param_1);
    }
    UpdateScene__16CmdLibraryDetailFP10CmdLibrarysUc
              (*(undefined4 *)(param_1 + 0x1c4),param_1,*(undefined2 *)(param_1 + 0x1ce),
               *(undefined1 *)(param_1 + 0x1d6));
    iVar1 = *(int *)(param_1 + 0x1c4);
    Open__10MenuWindowFUci(iVar1,*(byte *)(iVar1 + 0xb0) & 7,*(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x10)
                   );
    *(byte *)(*(int *)(param_1 + 0x1b8) + 0x24e) =
         *(byte *)(*(int *)(param_1 + 0x1b8) + 0x24e) & 0xfe;
    SetExplanation__7CmdNoteFPCce
              (*(undefined4 *)(param_1 + 0x1e8),*(undefined4 *)(*(int *)(param_1 + 0x28) + 0x2c));
  }
  return;
}

/* JP: 0x00462970  CmdLibrary::UpdateTitle(short)   [UpdateTitle__10CmdLibraryFs]  size=0x1ac */
void UpdateTitle__10CmdLibraryFs(int param_1,short param_2)

{
  int iVar1;
  long lVar2;
  
  iVar1 = *(int *)(param_1 + 0x1bc);
  if (iVar1 == 0) {
    lVar2 = __nw__FUi(0x248);
    iVar1 = 0;
    if (lVar2 != 0) {
      iVar1 = __ct__15CmdLibraryTitleFv(lVar2);
    }
    *(int *)(param_1 + 0x1bc) = iVar1;
    Initialize__9MenuSceneFPUcP9BufMemory(iVar1,*(undefined4 *)(*(int *)(param_1 + 0x54) + 0x34),0);
    Create__11CmdSubTitleFi(iVar1,1);
    CreateNumber__15CmdLibraryTitleFv(iVar1);
    *(undefined2 *)(iVar1 + 0x1c) = 0xffff;
    Open__10MenuWindowFUci(iVar1 + 0x58,*(byte *)(iVar1 + 0x108) & 7,
                    *(undefined4 *)(*(int *)(iVar1 + 0x8c) + 0x10));
  }
  if (param_2 != *(short *)(iVar1 + 0x1c)) {
    Reset__11CmdSubTitleFv(iVar1);
    SetTitle__11CmdSubTitleFii(iVar1,0,param_2);
    if (param_2 < 2) {
      SetNumber__15CmdLibraryTitleFv(iVar1);
    }
    *(short *)(iVar1 + 0x1c) = param_2;
    if (*(int *)(param_1 + 0x1c0) != 0) {
      *(byte *)(*(int *)(param_1 + 0x1c0) + 0x229) =
           *(byte *)(*(int *)(param_1 + 0x1c0) + 0x229) & 0xdf | 0x20;
    }
  }
  return;
}

/* JP: 0x00462b20  CmdLibrary::ChengeMenu(MenuText*, MenuText*, bool)   [ChengeMenu__10CmdLibraryFP8MenuTextP8MenuTextb]  size=0x264 */
void ChengeMenu__10CmdLibraryFP8MenuTextP8MenuTextb
               (int param_1,int param_2,int param_3,char param_4)

{
  ushort uVar1;
  short sVar2;
  
  if (param_3 != 0) {
    SetCSA__8FontItemFUc(param_3,0);
    Close__10CmdExplainFv(*(undefined4 *)(param_1 + 0x1b8));
    Destroy__16MenuModelManegerFUc(*(undefined4 *)(param_1 + 0x1f8),0);
    Close__10CmdElementFv(*(undefined4 *)(param_1 + 500));
    *(undefined2 *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x2ac + *(short *)(param_3 + 0x1e) * 2) =
         *(undefined2 *)(param_1 + 0x1cc);
  }
  if (param_2 != 0) {
    uVar1 = *(ushort *)(param_2 + 0x1e);
    SetCSA__8FontItemFUc(param_2,1);
    SetExplanation__7CmdNoteFPCce
              (*(undefined4 *)(param_1 + 0x1e8),
               *(undefined4 *)((uint)uVar1 * 0xc + *(int *)(param_1 + 0x28) + 0x14));
    if (param_4 != '\0') {
      sVar2 = *(short *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x2ac + (short)uVar1 * 2);
      *(short *)(param_1 + 0x1cc) = sVar2;
      if (sVar2 < 0) {
        Find__10CmdLibraryFss(param_1,uVar1,1);
      }
      else if (uVar1 == 0) {
        SetMonster__10CmdLibraryFP15MenuDataMonster
                  (param_1,*(short *)(param_1 + 0x1cc) * 0x20 + *(int *)(param_1 + 0x1fc) + 0x10);
      }
      else {
        SetNPC__10CmdLibraryFs(param_1,*(undefined2 *)(param_1 + 0x1cc));
      }
    }
  }
  return;
}

/* JP: 0x00462d90  CmdLibrary::Find(short, short)   [Find__10CmdLibraryFss]  size=0x1a4 */
undefined4 Find__10CmdLibraryFss(int param_1,short param_2,short param_3)

{
  undefined2 uVar1;
  long lVar2;
  
  uVar1 = (undefined2)*(undefined4 *)(*(int *)(param_1 + param_2 * 4 + 0x1fc) + 8);
  if (param_3 == 0) {
    lVar2 = __ptmf_scall(param_1,0,*(undefined2 *)(param_1 + 0x1cc),0);
    if ((lVar2 != 0) ||
       (lVar2 = __ptmf_scall(param_1,0,uVar1,*(short *)(param_1 + 0x1cc) + 1), lVar2 != 0)) {
      return 1;
    }
  }
  else {
    lVar2 = __ptmf_scall(param_1,param_3,*(undefined2 *)(param_1 + 0x1cc),uVar1);
    if ((lVar2 != 0) ||
       (lVar2 = __ptmf_scall(param_1,param_3,0xffffffffffffffff,*(undefined2 *)(param_1 + 0x1cc))
       , lVar2 != 0)) {
      return 1;
    }
  }
  return 0;
}

/* JP: 0x00462f40  CmdLibrary::FindMonster(short, short, short)   [FindMonster__10CmdLibraryFsss]  size=0x154 */
undefined4 FindMonster__10CmdLibraryFsss(int param_1,short param_2,short param_3,short param_4)

{
  long lVar1;
  uint uVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_1 + 0x1fc) + 0x10;
  if (param_2 == 0) {
    for (uVar2 = iVar3 + (param_3 + -1) * 0x20; (uint)(iVar3 + param_4 * 0x20) <= uVar2;
        uVar2 = uVar2 - 0x20) {
      lVar1 = SetMonster__10CmdLibraryFP15MenuDataMonster(param_1,uVar2);
      if (lVar1 != 0) {
        return 1;
      }
    }
  }
  else {
    for (uVar2 = iVar3 + (param_3 + 1) * 0x20; uVar2 < (uint)(iVar3 + param_4 * 0x20);
        uVar2 = uVar2 + 0x20) {
      lVar1 = SetMonster__10CmdLibraryFP15MenuDataMonster(param_1,uVar2);
      if (lVar1 != 0) {
        return 1;
      }
    }
  }
  return 0;
}

/* JP: 0x004630a0  CmdLibrary::FindNPC(short, short, short)   [FindNPC__10CmdLibraryFsss]  size=0x1f0 */
bool FindNPC__10CmdLibraryFsss(int param_1,short param_2,short param_3,short param_4)

{
  char cVar1;
  
  cVar1 = '\0';
  param_3 = param_3 + *(short *)(*(int *)(param_1 + 0x200) + 4);
  param_4 = param_4 + *(short *)(*(int *)(param_1 + 0x200) + 4);
  if (param_2 == 0) {
    do {
      param_3 = param_3 + -1;
      if (param_3 < param_4) break;
      cVar1 = FieldNpcLibrary__Fii(param_3,0);
    } while (cVar1 == '\0');
  }
  else {
    do {
      param_3 = param_3 + 1;
      if (param_4 <= param_3) break;
      cVar1 = FieldNpcLibrary__Fii(param_3,0);
    } while (cVar1 == '\0');
  }
  if (cVar1 != '\0') {
    SetNPC__10CmdLibraryFs(param_1,param_3 - *(short *)(*(int *)(param_1 + 0x200) + 4));
  }
  return cVar1 != '\0';
}

/* JP: 0x00463290  CmdLibrary::SetMonster(MenuDataMonster*)   [SetMonster__10CmdLibraryFP15MenuDataMonster]  size=0x38c */
undefined4 SetMonster__10CmdLibraryFP15MenuDataMonster(int param_1,int param_2)

{
  short sVar1;
  byte bVar2;
  int iVar3;
  uint uVar4;
  ulong uVar5;
  short *psVar6;
  char cVar7;
  short *psVar8;
  
  bVar2 = 0;
  cVar7 = '\0';
  psVar6 = (short *)(param_2 + 0x12);
  psVar8 = psVar6 + *(char *)(param_2 + 0x11);
  for (; psVar6 < psVar8; psVar6 = psVar6 + 1) {
    sVar1 = *psVar6;
    iVar3 = (int)sVar1;
    if (sVar1 < 0) {
      iVar3 = iVar3 + 3;
    }
    uVar5 = (long)sVar1 & 3;
    uVar4 = (uint)uVar5;
    if (((long)sVar1 < 0) && (uVar5 != 0)) {
      uVar4 = uVar4 - 4;
    }
    bVar2 = bVar2 | (byte)((int)(uint)*(byte *)(*(int *)(*(int *)(param_1 + 0x1e4) + 4) +
                                                (iVar3 >> 2) + 0xdef) >> ((uVar4 & 0xf) << 1)) & 3;
    sVar1 = *psVar6;
    iVar3 = (int)sVar1;
    if (sVar1 < 0) {
      iVar3 = iVar3 + 7;
    }
    uVar5 = (long)sVar1 & 7;
    uVar4 = (uint)uVar5;
    if (((long)sVar1 < 0) && (uVar5 != 0)) {
      uVar4 = uVar4 - 8;
    }
    if (((uint)*(byte *)(*(int *)(*(int *)(param_1 + 0x1e4) + 4) + (iVar3 >> 3) + 0xdcf) &
        1 << (uVar4 & 0x1f)) != 0) {
      cVar7 = '\x01';
    }
  }
  psVar6 = (short *)(param_2 + 0x12);
  psVar8 = psVar6 + *(char *)(param_2 + 0x11);
  while( true ) {
    if (psVar8 <= psVar6) {
      return 0;
    }
    sVar1 = *psVar6;
    iVar3 = (int)sVar1;
    if (sVar1 < 0) {
      iVar3 = iVar3 + 7;
    }
    uVar5 = (long)sVar1 & 7;
    uVar4 = (uint)uVar5;
    if (((long)sVar1 < 0) && (uVar5 != 0)) {
      uVar4 = uVar4 - 8;
    }
    if (((uint)*(byte *)(*(int *)(*(int *)(param_1 + 0x1e4) + 4) + (iVar3 >> 3) + 0xdaf) &
        1 << (uVar4 & 0x1f)) != 0) break;
    psVar6 = psVar6 + 1;
  }
  if ((*(byte *)(param_1 + 0x23) >> 6 != 0) && (cVar7 == '\0')) {
    return 0;
  }
  iVar3 = GetRegDat__9RegDatApiFiii(0x2e,*psVar6,0xffffffffffffffff);
  *(undefined2 *)(param_1 + 0x1cc) = *(undefined2 *)(param_2 + 0x1e);
  *(short *)(param_1 + 0x1ce) = *psVar6;
  *(byte *)(param_1 + 0x1d0) = *(byte *)(iVar3 + 0x14) & 7;
  *(char *)(param_1 + 0x1d5) = (char)*(undefined2 *)(iVar3 + 0x2e);
  *(byte *)(param_1 + 0x1d2) = (byte)(((ulong)*(byte *)(param_2 + 0x10) << 0x3e) >> 0x3f);
  *(undefined2 *)(param_1 + 0x1e) = *(undefined2 *)(iVar3 + 4);
  *(undefined4 *)(param_1 + 0x1d8) = *(undefined4 *)(param_2 + 0xc);
  *(byte *)(param_1 + 0x1d6) = bVar2;
  *(char *)(param_1 + 0x22) = cVar7;
  *(undefined1 *)(param_1 + 0x1d3) = 1;
  return 1;
}

/* JP: 0x00463620  CmdLibrary::SetNPC(short)   [SetNPC__10CmdLibraryFs]  size=0x120 */
void SetNPC__10CmdLibraryFs(int param_1,short param_2)

{
  undefined2 uVar1;
  undefined1 uVar2;
  int iVar3;
  
  iVar3 = (param_2 * 0x1c + (int)param_2) * 4 + *(int *)(param_1 + 0x200);
  *(short *)(param_1 + 0x1cc) = param_2;
  uVar1 = *(undefined2 *)(iVar3 + 0x7e);
  *(undefined2 *)(param_1 + 0x1e) = uVar1;
  *(undefined2 *)(param_1 + 0x1ce) = uVar1;
  uVar2 = FieldNpcLibrary__Fii((int)param_2 + (uint)*(ushort *)(*(int *)(param_1 + 0x200) + 4),0);
  *(undefined1 *)(param_1 + 0x20) = uVar2;
  *(byte *)(param_1 + 0x1d2) = (byte)(((ulong)*(byte *)(iVar3 + 0x7c) << 0x3e) >> 0x3f);
  *(byte *)(param_1 + 0x1d0) = *(byte *)(iVar3 + 0x7c) >> 2;
  *(undefined1 *)(param_1 + 0x1d5) = 0xff;
  *(byte *)(param_1 + 0x1d1) = *(byte *)(iVar3 + 0x7c) & 1;
  *(undefined4 *)(param_1 + 0x1d8) = *(undefined4 *)(iVar3 + 0x78);
  *(byte *)(param_1 + 0x1d3) = *(byte *)(iVar3 + 0x7d) & 1;
  return;
}

/* JP: 0x00463740  CmdLibrary::SafeDestroy()   [SafeDestroy__10CmdLibraryFv]  size=0x11c */
void SafeDestroy__10CmdLibraryFv(int param_1)

{
  if (*(int *)(param_1 + 0x1b8) != 0) {
    (**(code **)(*(int *)(*(int *)(param_1 + 0x1b8) + 8) + 0xc))();
    *(undefined4 *)(param_1 + 0x1b8) = 0;
  }
  if (*(int *)(param_1 + 0x1bc) != 0) {
    ReleaseOT__7MenuObjFv(*(int *)(param_1 + 0x1bc) + 0x58);
    (**(code **)(*(int *)(*(int *)(param_1 + 0x1bc) + 8) + 0xc))();
    *(undefined4 *)(param_1 + 0x1bc) = 0;
  }
  if (*(int *)(param_1 + 0x1c4) != 0) {
    ReleaseOT__7MenuObjFv(*(undefined4 *)(param_1 + 0x1c4));
    (**(code **)(*(int *)(*(int *)(param_1 + 0x1c4) + 8) + 0xc))();
    *(undefined4 *)(param_1 + 0x1c4) = 0;
  }
  if (*(int *)(param_1 + 0x1c0) != 0) {
    ReleaseOT__7MenuObjFv(*(undefined4 *)(param_1 + 0x1c0));
    (**(code **)(*(int *)(*(int *)(param_1 + 0x1c0) + 8) + 0xc))();
    *(undefined4 *)(param_1 + 0x1c0) = 0;
  }
  return;
}

/* JP: 0x00463860  CmdLibrary::Enter()   [Enter__10CmdLibraryFv]  size=0x278 */
undefined8 Enter__10CmdLibraryFv(int param_1)

{
  int iVar1;
  bool bVar2;
  undefined4 uVar3;
  undefined *puVar4;
  undefined1 uVar5;
  undefined8 uVar6;
  
  iVar1 = *(int *)(param_1 + 0x10);
  if (*(char *)(param_1 + 0x21) == '\0') {
    UpdateScene__10CmdSubMenuFs(param_1 + 100,0);
    uVar6 = GetPlace__10MenuWindowFss(param_1 + 0xbc,0,0);
    Select__6CursorFP9MenuPlace(*(undefined4 *)(param_1 + 0x18),uVar6);
    ChengeMenu__10CmdLibraryFP8MenuTextP8MenuTextb(param_1,uVar6,0,1);
    Create__10CmdLibraryFs(param_1,0);
    Update__10CmdLibraryFs(param_1,0);
    Open__10MenuWindowFUci(param_1 + 0xbc,*(byte *)(param_1 + 0x16c) & 7,
                    *(undefined4 *)(*(int *)(param_1 + 0xf0) + 0x10));
    SetTitle__11CmdTitleLogFPUci
              (*(undefined4 *)(param_1 + 0x1ec),*(undefined4 *)(*(int *)(param_1 + 0x54) + 0x10),7);
    Open__11CmdTitleLogFv(*(undefined4 *)(param_1 + 0x1ec));
    Open__15CmdButtonReportFv(*(undefined4 *)(param_1 + 0x1f0));
    uVar5 = CreateBackGround__7CmdMenuFs(iVar1,8);
    *(undefined1 *)(param_1 + 0x20) = uVar5;
    *(char *)(param_1 + 0x21) = *(char *)(param_1 + 0x21) + '\x01';
  }
  else if (*(char *)(param_1 + 0x21) == '\x01') {
    if ((*(char *)(*(int *)(iVar1 + 0xb0) + 0x104) == '\x01') ||
       (*(char *)(*(int *)(iVar1 + 0xb0) + 0x104) == '\0')) {
      bVar2 = true;
    }
    else {
      bVar2 = false;
    }
    if (bVar2) {
      if (*(char *)(param_1 + 0x20) != '\0') {
        DestroyBackGround__7CmdMenuFs(iVar1,1);
        *(undefined1 *)(param_1 + 0x20) = 0;
      }
      Restore__6CursorFv(*(undefined4 *)(param_1 + 0x18));
      *(undefined1 *)(param_1 + 0x21) = 0;
      puVar4 = PTR_SelectMenu__10CmdLibraryFv_0050d650;
      uVar3 = DAT_0050d64c;
      *(undefined4 *)(param_1 + 0x58) = _6576;
      *(undefined4 *)(param_1 + 0x5c) = uVar3;
      *(undefined **)(param_1 + 0x60) = puVar4;
    }
  }
  return 0;
}

/* JP: 0x00463ae0  CmdLibrary::Exit()   [Exit__10CmdLibraryFv]  size=0x228 */
undefined8 Exit__10CmdLibraryFv(int param_1)

{
  int iVar1;
  bool bVar2;
  
  if (*(char *)(param_1 + 0x21) == '\0') {
    (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x14) + 0x28))
              (*(int *)(param_1 + 0x10),0,0,0x11);
    Shutdown__6CursorFv(*(undefined4 *)(param_1 + 0x18));
    Close__10MenuWindowFUci(param_1 + 0xbc,((ulong)*(byte *)(param_1 + 0x16c) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(param_1 + 0xf0) + 0x14));
    iVar1 = *(int *)(param_1 + 0x1ec);
    Close__10MenuWindowFUci(iVar1 + 0x58,((ulong)*(byte *)(iVar1 + 0x108) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar1 + 0x8c) + 0x14));
    iVar1 = *(int *)(param_1 + 0x1bc);
    Close__10MenuWindowFUci(iVar1 + 0x58,((ulong)*(byte *)(iVar1 + 0x108) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar1 + 0x8c) + 0x14));
    iVar1 = *(int *)(param_1 + 0x1f0);
    Close__10MenuWindowFUci(iVar1 + 0x58,((ulong)*(byte *)(iVar1 + 0x108) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar1 + 0x8c) + 0x14));
    *(char *)(param_1 + 0x21) = *(char *)(param_1 + 0x21) + '\x01';
  }
  else if (*(char *)(param_1 + 0x21) == '\x01') {
    if ((*(char *)(param_1 + 0x164) == '\x01') || (*(char *)(param_1 + 0x164) == '\0')) {
      bVar2 = true;
    }
    else {
      bVar2 = false;
    }
    if (bVar2) {
      ReleaseOT__7MenuObjFv(param_1 + 0xbc);
      ReleaseOT__7MenuObjFv(*(int *)(param_1 + 0x1bc) + 0x58);
      SafeDestroy__10CmdLibraryFv(param_1);
      (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x14) + 0x24))(*(int *)(param_1 + 0x10),0);
      DestroyScene__4MenuFP9MenuSceneb(*(undefined4 *)(param_1 + 0x10),param_1,1);
    }
  }
  return 0;
}

/* JP: 0x00463d10  CmdLibrary::SelectMenu()   [SelectMenu__10CmdLibraryFv]  size=0x83c */
undefined8 SelectMenu__10CmdLibraryFv(int param_1)

{
  undefined2 uVar1;
  ushort uVar2;
  int iVar3;
  bool bVar4;
  undefined *puVar5;
  byte bVar6;
  undefined4 uVar7;
  int iVar8;
  long lVar9;
  undefined8 uVar10;
  char cStack_11;
  
  iVar3 = *(int *)(*(int *)(param_1 + 0x18) + 0xec);
  uVar1 = *(undefined2 *)(iVar3 + 0x1e);
  uVar2 = *(ushort *)(*(int *)(param_1 + 0x10) + 0x48);
  lVar9 = Exec__10CmdExplainFUs(*(undefined4 *)(param_1 + 0x1b8),uVar2);
  puVar5 = PTR_Exit__10CmdLibraryFv_0050d660;
  uVar7 = DAT_0050d65c;
  iVar8 = (int)lVar9;
  if (lVar9 == 0) {
    if ((*(char *)(*(int *)(param_1 + 0x1b8) + 0x114) == '\x01') ||
       (*(char *)(*(int *)(param_1 + 0x1b8) + 0x114) == '\0')) {
      bVar4 = true;
    }
    else {
      bVar4 = false;
    }
    if (bVar4) {
      if (((uVar2 & 0x8000) == 0) || (*(int *)(*(int *)(param_1 + 0x1f8) + 0x18) == 0)) {
        if (((uVar2 & 0x1000) == 0) || (*(char *)(param_1 + 0x22) == '\0')) {
          if (((uVar2 & 8) == 0) || (*(short *)(param_1 + 0x1cc) < 0)) {
            if ((*(char *)(*(int *)(param_1 + 0x1b8) + 0x20) == '\x03') &&
               (iVar8 = MoveVertical__9MenuSceneFi(param_1,0), iVar3 != iVar8)) {
              ChengeMenu__10CmdLibraryFP8MenuTextP8MenuTextb(param_1,iVar8,iVar3,1);
              PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x1dc),0,0,0);
            }
          }
          else {
            iVar3 = *(int *)(param_1 + 0x1bc);
            Close__10MenuWindowFUci(iVar3 + 0x58,((ulong)*(byte *)(iVar3 + 0x108) & 0x3f) >> 3,
                            *(undefined4 *)(*(int *)(iVar3 + 0x8c) + 0x14));
            Close__10CmdExplainFv(*(undefined4 *)(param_1 + 0x1b8));
            PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x1dc),6,0,0);
          }
        }
        else {
          *(byte *)(*(int *)(param_1 + 0x1c0) + 0x13a) =
               *(byte *)(*(int *)(param_1 + 0x1c0) + 0x13a) & 0xfe |
               *(byte *)(param_1 + 0x23) >> 6 & 1;
          *(byte *)(param_1 + 0x23) =
               *(byte *)(param_1 + 0x23) & 0x3f |
               (byte)(((uint)(((ulong)*(byte *)(param_1 + 0x23) << 0x38) >> 0x3e) ^ 1) << 6);
          UpdateData__10CmdLibraryFv(param_1);
          Start__11MenuMessageFv(*(int *)(param_1 + 0x1b8) + 0x23c);
          PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x1dc),6,0,0);
        }
      }
      else {
        SetAction__13MenuModelPackFv(*(undefined4 *)(*(int *)(param_1 + 0x1f8) + 0x18));
      }
    }
  }
  else if (iVar8 == 4) {
    if ((long)((ulong)*(byte *)(*(int *)(param_1 + 0x1b8) + 0x525) << 0x3d) < 0) {
      *(undefined4 *)(param_1 + 0x58) = _6653;
      *(undefined4 *)(param_1 + 0x5c) = uVar7;
      *(undefined **)(param_1 + 0x60) = puVar5;
    }
    else {
      bVar6 = *(byte *)(*(int *)(param_1 + 0x1b8) + 0x524) >> 4;
      if (bVar6 == 0) {
        if (*(char *)(*(int *)(param_1 + 0x1bc) + 0x100) == '\0') {
          SafeDestroy__10CmdLibraryFv(param_1);
          lVar9 = __nw__FUi(0xf8);
          uVar7 = 0;
          if (lVar9 != 0) {
            uVar7 = __ct__14CmdLibraryListFv(lVar9);
          }
          *(undefined4 *)(param_1 + 0x1c8) = uVar7;
          CreateScene__14CmdLibraryListFP10CmdLibrarys
                    (*(undefined4 *)(param_1 + 0x1c8),param_1,uVar1);
          uVar10 = GetPlace__10MenuWindowFs(*(undefined4 *)(param_1 + 0x1c8),*(undefined2 *)(param_1 + 0x1cc)
                                  );
          Scroll__10MenuWindowFP9MenuPlace(*(undefined4 *)(param_1 + 0x1c8),uVar10);
          FinishScroll__10MenuWindowFv(*(undefined4 *)(param_1 + 0x1c8));
          Select__6CursorFP9MenuPlace(*(undefined4 *)(param_1 + 0x18),uVar10);
          Select__14CmdLibraryListFP10CmdLibraryP9MenuGroupP9MenuGroup
                    (*(undefined4 *)(param_1 + 0x1c8),param_1,uVar10,0);
          ClearReport__15CmdButtonReportFv(*(undefined4 *)(param_1 + 0x1f0));
          if (*(int *)(*(int *)(param_1 + 0x1c8) + 0x44) == 0) {
            cStack_11 = '\0';
          }
          else {
            cStack_11 = (char)(((ulong)*(ushort *)(*(int *)(param_1 + 0x1c8) + 0xb2) << 0x36) >>
                              0x38);
          }
          if (cStack_11 != '\0') {
            SetReport__15CmdButtonReportFii
                      (*(int *)(param_1 + 0x1f0),*(undefined1 *)(*(int *)(param_1 + 0x1f0) + 0x20),
                       0xd);
          }
          iVar3 = *(int *)(param_1 + 0x1c8);
          Open__10MenuWindowFUci(iVar3,*(byte *)(iVar3 + 0xb0) & 7,
                          *(undefined4 *)(*(int *)(iVar3 + 0x34) + 0x10));
          puVar5 = PTR_SelectList__10CmdLibraryFv_0050d670;
          uVar7 = DAT_0050d66c;
          *(undefined4 *)(param_1 + 0x58) = _6666;
          *(undefined4 *)(param_1 + 0x5c) = uVar7;
          *(undefined **)(param_1 + 0x60) = puVar5;
          return 0;
        }
        Create__10CmdLibraryFs(param_1,uVar1);
      }
      else {
        Find__10CmdLibraryFss(param_1,uVar1,(short)((int)(uint)bVar6 >> 3));
      }
      Update__10CmdLibraryFs(param_1,uVar1);
    }
  }
  else if (iVar8 == 3) {
    if (*(int *)(param_1 + 0x1c0) != 0) {
      *(byte *)(*(int *)(param_1 + 0x1c0) + 0x229) =
           *(byte *)(*(int *)(param_1 + 0x1c0) + 0x229) & 0xdf;
      iVar3 = *(int *)(param_1 + 0x1c0);
      Close__10MenuWindowFUci(iVar3,((ulong)*(byte *)(iVar3 + 0xb0) & 0x3f) >> 3,
                      *(undefined4 *)(*(int *)(iVar3 + 0x34) + 0x14));
    }
    if (*(int *)(param_1 + 0x1c4) != 0) {
      iVar3 = *(int *)(param_1 + 0x1c4);
      Close__10MenuWindowFUci(iVar3,((ulong)*(byte *)(iVar3 + 0xb0) & 0x3f) >> 3,
                      *(undefined4 *)(*(int *)(iVar3 + 0x34) + 0x14));
    }
    Destroy__16MenuModelManegerFUc(*(undefined4 *)(param_1 + 0x1f8),0);
    Close__10CmdElementFv(*(undefined4 *)(param_1 + 500));
  }
  else if (iVar8 == 1) {
    if (*(int *)(param_1 + 0x1c0) != 0) {
      iVar3 = *(int *)(param_1 + 0x1c0);
      Open__10MenuWindowFUci(iVar3,*(byte *)(iVar3 + 0xb0) & 7,
                      *(undefined4 *)(*(int *)(iVar3 + 0x34) + 0x10));
    }
    if (*(int *)(param_1 + 0x1c4) != 0) {
      iVar3 = *(int *)(param_1 + 0x1c4);
      Open__10MenuWindowFUci(iVar3,*(byte *)(iVar3 + 0xb0) & 7,
                      *(undefined4 *)(*(int *)(iVar3 + 0x34) + 0x10));
    }
  }
  return 0;
}

/* JP: 0x00464550  CmdLibrary::SelectList()   [SelectList__10CmdLibraryFv]  size=0x310 */
undefined8 SelectList__10CmdLibraryFv(int param_1)

{
  short sVar1;
  short sVar2;
  ushort uVar3;
  int iVar4;
  bool bVar5;
  undefined *puVar6;
  undefined4 uVar7;
  int iVar8;
  
  if ((*(char *)(*(int *)(param_1 + 0x1c8) + 0xa8) == '\x01') ||
     (*(char *)(*(int *)(param_1 + 0x1c8) + 0xa8) == '\0')) {
    bVar5 = true;
  }
  else {
    bVar5 = false;
  }
  if (bVar5) {
    uVar3 = *(ushort *)(*(int *)(param_1 + 0x10) + 0x48);
    iVar4 = *(int *)(*(int *)(param_1 + 0x18) + 0xec);
    if ((uVar3 & 0x6008) == 0) {
      iVar8 = MoveVertical__9MenuSceneFi(param_1,1);
      if (iVar4 != iVar8) {
        Select__14CmdLibraryListFP10CmdLibraryP9MenuGroupP9MenuGroup
                  (*(undefined4 *)(param_1 + 0x1c8),param_1,iVar8,iVar4);
        PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x1dc),0,0,0);
      }
    }
    else {
      sVar1 = *(short *)(*(int *)(param_1 + 0x1c8) + 0xae);
      if ((uVar3 & 0x2000) == 0) {
        sVar2 = *(short *)(param_1 + 0x1cc);
        PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x1dc),3,0,0);
      }
      else {
        sVar2 = *(short *)(iVar4 + 0x16);
        PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x1dc),2,0,0);
      }
      if (sVar1 == 0) {
        SetMonster__10CmdLibraryFP15MenuDataMonster
                  (param_1,sVar2 * 0x20 + *(int *)(param_1 + 0x1fc) + 0x10);
      }
      else {
        SetNPC__10CmdLibraryFs(param_1,sVar2);
      }
      uVar7 = GetPlace__10MenuWindowFss(param_1 + 0xbc,0,sVar1);
      Select__6CursorFP9MenuPlace(*(undefined4 *)(param_1 + 0x18),uVar7);
      ChengeMenu__10CmdLibraryFP8MenuTextP8MenuTextb(param_1,uVar7,0,0);
      iVar4 = *(int *)(param_1 + 0x1c8);
      Close__10MenuWindowFUci(iVar4,((ulong)*(byte *)(iVar4 + 0xb0) & 0x3f) >> 3,
                      *(undefined4 *)(*(int *)(iVar4 + 0x34) + 0x14));
      puVar6 = PTR_CloseList__10CmdLibraryFv_0050d680;
      uVar7 = DAT_0050d67c;
      *(undefined4 *)(param_1 + 0x58) = _6802;
      *(undefined4 *)(param_1 + 0x5c) = uVar7;
      *(undefined **)(param_1 + 0x60) = puVar6;
    }
  }
  return 0;
}

/* JP: 0x00464860  CmdLibrary::CloseList()   [CloseList__10CmdLibraryFv]  size=0x134 */
undefined8 CloseList__10CmdLibraryFv(int param_1)

{
  undefined2 uVar1;
  bool bVar2;
  undefined4 uVar3;
  undefined *puVar4;
  
  if ((*(char *)(*(int *)(param_1 + 0x1c8) + 0xa8) == '\x01') ||
     (*(char *)(*(int *)(param_1 + 0x1c8) + 0xa8) == '\0')) {
    bVar2 = true;
  }
  else {
    bVar2 = false;
  }
  if (bVar2) {
    uVar1 = *(undefined2 *)(*(int *)(param_1 + 0x1c8) + 0xae);
    (**(code **)(*(int *)(*(int *)(param_1 + 0x1c8) + 8) + 0xc))();
    *(undefined4 *)(param_1 + 0x1c8) = 0;
    Create__10CmdLibraryFs(param_1,uVar1);
    Update__10CmdLibraryFs(param_1,uVar1);
    puVar4 = PTR_SelectMenu__10CmdLibraryFv_0050d690;
    uVar3 = DAT_0050d68c;
    *(undefined4 *)(param_1 + 0x58) = _6850;
    *(undefined4 *)(param_1 + 0x5c) = uVar3;
    *(undefined **)(param_1 + 0x60) = puVar4;
  }
  return 0;
}
