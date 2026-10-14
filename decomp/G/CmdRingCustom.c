/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdRingCustom   functions: 33
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdRingCustom.md).
 */

/* JP: 0x00466e30  CmdRingCustom::CmdRingCustom()   [__ct__13CmdRingCustomFv]  size=0xa8 */
int __ct__13CmdRingCustomFv(int param_1)

{
  __ct__10CmdPCSceneFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__13CmdRingCustom;
  __ct__10CmdSubMenuFv(param_1 + 0x8c);
  *(undefined4 *)(param_1 + 0x1e0) = 0;
  *(undefined4 *)(param_1 + 0x1e4) = 0;
  *(undefined4 *)(param_1 + 0x1e8) = 0;
  *(undefined4 *)(param_1 + 0x1ec) = 0;
  *(undefined4 *)(param_1 + 0x1f0) = 0;
  *(undefined4 *)(param_1 + 500) = 0;
  *(undefined4 *)(param_1 + 0x1f8) = 0;
  *(undefined4 *)(param_1 + 0x1fc) = 0;
  *(undefined4 *)(param_1 + 0x200) = 0;
  *(undefined1 *)(param_1 + 0x21d) = 7;
  *(undefined1 *)(param_1 + 0x21e) = 0;
  return param_1;
}

/* JP: 0x00466ee0  CmdRingCustom::~CmdRingCustom()   [__dt__13CmdRingCustomFv]  size=0x21c */
int __dt__13CmdRingCustomFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__13CmdRingCustom;
    if (*(int *)(param_1 + 0x1e0) != 0) {
      (**(code **)(*(int *)(*(int *)(param_1 + 0x1e0) + 8) + 0xc))();
    }
    if (*(int *)(param_1 + 0x1e4) != 0) {
      (**(code **)(*(int *)(*(int *)(param_1 + 0x1e4) + 8) + 0xc))();
    }
    if (*(int *)(param_1 + 0x1ec) != 0) {
      (**(code **)(*(int *)(*(int *)(param_1 + 0x1ec) + 8) + 0xc))();
    }
    if (*(int *)(param_1 + 0x1f0) != 0) {
      (**(code **)(*(int *)(*(int *)(param_1 + 0x1f0) + 8) + 0xc))();
    }
    if (*(int *)(param_1 + 500) != 0) {
      (**(code **)(*(int *)(*(int *)(param_1 + 500) + 8) + 0xc))();
    }
    if (*(int *)(param_1 + 0x1f8) != 0) {
      (**(code **)(*(int *)(*(int *)(param_1 + 0x1f8) + 8) + 0xc))();
    }
    if (*(int *)(param_1 + 0x1e8) != 0) {
      (**(code **)(*(int *)(*(int *)(param_1 + 0x1e8) + 8) + 0xc))();
    }
    if (*(int *)(param_1 + 0x1fc) != 0) {
      (**(code **)(*(int *)(*(int *)(param_1 + 0x1fc) + 8) + 0xc))();
    }
    if (*(int *)(param_1 + 0x200) != 0) {
      (**(code **)(*(int *)(*(int *)(param_1 + 0x200) + 8) + 0xc))();
    }
    if (*(int *)(param_1 + 0x88) != 0) {
      Destruct__5JRingFb(*(undefined4 *)(param_1 + 0x88),0);
    }
    __dt__10CmdSubMenuFv(param_1 + 0x8c,0xffffffffffffffff);
    __dt__10CmdPCSceneFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x00467100  CmdRingCustom::GetReady()   [GetReady__13CmdRingCustomFv]  size=0x34c */
undefined4 GetReady__13CmdRingCustomFv(int param_1)

{
  undefined *puVar1;
  ushort uVar2;
  short sVar3;
  undefined2 uVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  long lVar8;
  undefined8 uVar9;
  
  for (uVar2 = 2; (short)uVar2 < 0xc; uVar2 = uVar2 + 1) {
    Convert__13MenuDataTableFPUci(*(undefined4 *)((uint)uVar2 * 0xc + *(int *)(param_1 + 0x54) + 0x10),0);
  }
  CreatePCInfo__10CmdPCSceneFPUc(param_1,*(undefined4 *)(*(int *)(param_1 + 0x54) + 0x28));
  *(undefined2 *)(*(int *)(param_1 + 0x18) + 0x32) = 0;
  sVar3 = GetLayerCount__10CmdPCSceneFs(param_1,0);
  if (sVar3 < 2) {
    *(byte *)(param_1 + 0x23) = *(byte *)(param_1 + 0x23) & 0xfe;
  }
  SetChengePCMode__10CmdPCSceneFUc(param_1,0);
  iVar6 = *(int *)(param_1 + 0x10);
  uVar4 = GetRegCnt__9RegDatApiFii(0x11,0xffffffffffffffff);
  *(undefined2 *)(param_1 + 0x21a) = uVar4;
  iVar5 = Find__13MenuDataTableFs(iVar6 + 0x28,0x19);
  *(int *)(param_1 + 0x20c) = iVar5 + 0x10;
  *(char *)(param_1 + 0x21c) = (char)*(undefined2 *)(iVar5 + 4);
  *(undefined1 *)(param_1 + 0x21f) = *(undefined1 *)(iVar5 + 3);
  iVar5 = Find__13MenuDataTableFs(iVar6 + 0x28,0x18);
  *(short *)(param_1 + 0x218) = (short)*(undefined4 *)(iVar5 + 8);
  *(int *)(param_1 + 0x210) = iVar5 + 0x10;
  iVar6 = Find__13MenuDataTableFs(iVar6 + 0x28,10);
  *(int *)(param_1 + 0x214) = iVar6 + 0x10;
  lVar8 = __nw__FUi(0x5d0);
  uVar7 = 0;
  if (lVar8 != 0) {
    uVar7 = __ct__5JRingFsi(lVar8,0,0xc);
  }
  *(undefined4 *)(param_1 + 0x88) = uVar7;
  uVar9 = GetActive__4CPadFi(0);
  SetPad__5JRingFP4CPad(uVar9);
  SetRingPos__5JRingFff(0x439c0000,0x43910000,*(undefined4 *)(param_1 + 0x88));
  *(undefined2 *)(*(int *)(param_1 + 0x88) + 0x4a) = 3;
  *(undefined2 *)(*(int *)(param_1 + 0x88) + 0x4e) = 2;
  Initialize__9MenuSceneFPUcP9BufMemory(param_1 + 0x8c,*(undefined4 *)(*(int *)(param_1 + 0x54) + 0x34),0);
  CreateScene__10CmdSubMenuFsP9MSDSystem(param_1 + 0x8c,5,*(int *)(param_1 + 0x28) + 0x10);
  puVar1 = PTR_Enter__13CmdRingCustomFv_0050d6a0;
  uVar7 = DAT_0050d69c;
  *(undefined4 *)(param_1 + 0x7c) = _5506;
  *(undefined4 *)(param_1 + 0x80) = uVar7;
  *(undefined **)(param_1 + 0x84) = puVar1;
  return 1;
}

/* JP: 0x00467470  CmdRingCustom::Run()   [Run__13CmdRingCustomFv]  size=0x104 */
undefined8 Run__13CmdRingCustomFv(int param_1)

{
  bool bVar1;
  long lVar2;
  
  lVar2 = ChengePC__10CmdPCSceneFv(param_1);
  if (lVar2 == 0) {
    if (*(int *)(param_1 + 0x78) != 0) {
      if ((*(char *)(*(int *)(param_1 + 0x78) + 0x100) == '\x01') ||
         (*(char *)(*(int *)(param_1 + 0x78) + 0x100) == '\0')) {
        bVar1 = true;
      }
      else {
        bVar1 = false;
      }
      if (!bVar1) {
        *(undefined2 *)(*(int *)(param_1 + 0x10) + 0x48) = 0;
      }
    }
    lVar2 = __ptmf_test(param_1 + 0x7c);
    if (lVar2 != 0) {
      __ptmf_scall(param_1);
    }
  }
  return 0;
}

/* JP: 0x00467580  CmdRingCustom::Update(short)   [Update__13CmdRingCustomFs]  size=0x264 */
void Update__13CmdRingCustomFs(int param_1,undefined2 param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(*(int *)(param_1 + 0x18) + 0xec);
  CreateJudgmentRing__5CmdPCFP5JRingUc
            (*(undefined4 *)(param_1 + 0x70),*(undefined4 *)(param_1 + 0x88),0xff);
  RingActive__5JRingFv(*(undefined4 *)(param_1 + 0x88));
  UpdateMenu__13CmdRingCustomFv(param_1);
  UpdatePCInfo__10CmdPCSceneFsP11CmdPCStatus(param_1,param_2,0);
  if (*(int *)(param_1 + 0x1ec) != 0) {
    UpdateHitArea__13CmdRingCustomFs(param_1,1);
  }
  if (*(int *)(param_1 + 500) != 0) {
    UpdateFinal__13CmdRingCustomFss(param_1,1,0);
  }
  if (*(int *)(param_1 + 0x1e8) != 0) {
    UpdateGoods__13CmdRingCustomFs(param_1,1);
  }
  if (*(int *)(param_1 + 0x1fc) != 0) {
    UpdateCount__13CmdRingCustomFs(param_1,1);
  }
  if (*(int *)(param_1 + 0x200) != 0) {
    UpdateAutoRing__13CmdRingCustomFs(param_1,1);
  }
  if (*(char *)(param_1 + 0x21d) == '\x05') {
    if (-1 < (long)((ulong)*(byte *)(iVar1 + 0x21) << 0x3e)) {
      DestroyContent__13CmdRingCustomFs(param_1,*(undefined2 *)(iVar1 + 0x1e));
      iVar1 = MoveCursor__6CursorFi(*(undefined4 *)(param_1 + 0x18),2);
      CreateContent__13CmdRingCustomFs(param_1,*(undefined2 *)(iVar1 + 0x1e));
    }
    Select__10CmdSubMenuFP7CmdNoteP9MenuPlaceP9MenuPlace
              (param_1 + 0x8c,*(undefined4 *)(param_1 + 100),iVar1,0);
  }
  else if (*(char *)(param_1 + 0x21d) == '\x01') {
    Select__22CmdRingCustomFinalSlotFP13CmdRingCustom(*(undefined4 *)(param_1 + 500),param_1);
  }
  return;
}

/* JP: 0x004677f0  CmdRingCustom::DelayDelete()   [DelayDelete__13CmdRingCustomFv]  size=0x64 */
void DelayDelete__13CmdRingCustomFv(int param_1)

{
  ReleaseOT__7MenuObjFv(param_1 + 0xe4);
  if (*(int *)(param_1 + 0x88) != 0) {
    Destruct__5JRingFb(*(undefined4 *)(param_1 + 0x88),0);
    *(undefined4 *)(param_1 + 0x88) = 0;
  }
  DelayDelete__17DelayDeleteObjectFv(param_1);
  return;
}

/* JP: 0x00467860  CmdRingCustom::UpdateMenu()   [UpdateMenu__13CmdRingCustomFv]  size=0xc4 */
void UpdateMenu__13CmdRingCustomFv(int param_1)

{
  if ((*(byte *)(**(int **)(param_1 + 0x70) + 0x59) & 1) == 0) {
    EnableFontItem__8FontItemFv(*(undefined4 *)(param_1 + 0x1d8));
    EnableFontItem__8FontItemFv(*(int *)(param_1 + 0x1d8) + 0x100);
    EnableFontItem__8FontItemFv(*(int *)(param_1 + 0x1d8) + 0x180);
  }
  else {
    DisableFontItem__8FontItemFv(*(undefined4 *)(param_1 + 0x1d8));
    DisableFontItem__8FontItemFv(*(int *)(param_1 + 0x1d8) + 0x100);
    DisableFontItem__8FontItemFv(*(int *)(param_1 + 0x1d8) + 0x180);
  }
  return;
}

/* JP: 0x00467930  CmdRingCustom::UpdateTitle(short, short)   [UpdateTitle__13CmdRingCustomFss]  size=0x124 */
void UpdateTitle__13CmdRingCustomFss(int param_1,short param_2,undefined2 param_3)

{
  int iVar1;
  long lVar2;
  
  iVar1 = *(int *)(param_1 + 0x1e0);
  if (iVar1 == 0) {
    lVar2 = __nw__FUi(0x1c8);
    iVar1 = 0;
    if (lVar2 != 0) {
      iVar1 = __ct__11CmdSubTitleFv(lVar2);
    }
    *(int *)(param_1 + 0x1e0) = iVar1;
    Initialize__9MenuSceneFPUcP9BufMemory(iVar1,*(undefined4 *)(*(int *)(param_1 + 0x54) + 0x40),0);
    Create__11CmdSubTitleFi(iVar1,1);
  }
  Reset__11CmdSubTitleFv(iVar1);
  SetTitle__11CmdSubTitleFii(iVar1,0,param_3);
  *(byte *)(iVar1 + 0x6a) = *(byte *)(iVar1 + 0x6a) & 0xfe | 1;
  if (param_2 != 0) {
    Open__10MenuWindowFUci(iVar1 + 0x58,*(byte *)(iVar1 + 0x108) & 7,
                    *(undefined4 *)(*(int *)(iVar1 + 0x8c) + 0x10));
  }
  return;
}

/* JP: 0x00467a60  CmdRingCustom::UpdateFence(short, short)   [UpdateFence__13CmdRingCustomFss]  size=0x1a8 */
void UpdateFence__13CmdRingCustomFss(int param_1,short param_2,short param_3)

{
  int iVar1;
  long lVar2;
  undefined8 uVar3;
  undefined1 auStack_90 [96];
  int iStack_30;
  short sStack_20;
  short sStack_10;
  
  iStack_30 = param_1;
  sStack_20 = param_2;
  sStack_10 = param_3;
  __ct__9MenuSceneFv(auStack_90);
  if (*(int *)(iStack_30 + 0x1e4) != 0) {
    (**(code **)(*(int *)(*(int *)(iStack_30 + 0x1e4) + 8) + 0xc))();
    *(undefined4 *)(iStack_30 + 0x1e4) = 0;
  }
  if (sStack_10 != 4) {
    Initialize__9MenuSceneFPUcP9BufMemory(auStack_90,
                    *(undefined4 *)
                     (((int)sStack_10 + 7U & 0xffff) * 0xc + *(int *)(iStack_30 + 0x54) + 0x10),0);
    lVar2 = __nw__FUi(0x178);
    uVar3 = 0;
    if (lVar2 != 0) {
      uVar3 = __ct__8CmdFenceFv(lVar2);
    }
    *(int *)(iStack_30 + 0x1e4) = (int)uVar3;
    CreateFence__8CmdFenceFP9MenuScenePUc
              (uVar3,auStack_90,*(undefined4 *)(*(int *)(iStack_30 + 0x54) + 0x1c));
    *(byte *)(*(int *)(iStack_30 + 0x1e4) + 0x12) =
         *(byte *)(*(int *)(iStack_30 + 0x1e4) + 0x12) & 0xfe | 1;
    if (sStack_20 != 0) {
      iVar1 = *(int *)(iStack_30 + 0x1e4);
      Open__10MenuWindowFUci(iVar1,*(byte *)(iVar1 + 0xb0) & 7,
                      *(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x10));
    }
  }
  __dt__9MenuSceneFv(auStack_90,0xffffffffffffffff);
  return;
}

/* JP: 0x00467c10  CmdRingCustom::UpdateHitArea(short)   [UpdateHitArea__13CmdRingCustomFs]  size=0x118 */
void UpdateHitArea__13CmdRingCustomFs(int param_1,short param_2)

{
  int iVar1;
  undefined4 uVar2;
  long lVar3;
  
  if (*(int *)(param_1 + 0x1ec) == 0) {
    lVar3 = __nw__FUi(0xea0);
    uVar2 = 0;
    if (lVar3 != 0) {
      uVar2 = __ct__20CmdRingCustomHitAreaFv(lVar3);
    }
    *(undefined4 *)(param_1 + 0x1ec) = uVar2;
    CreateScene__20CmdRingCustomHitAreaFP13CmdRingCustom(*(undefined4 *)(param_1 + 0x1ec),param_1);
  }
  UpdateScene__20CmdRingCustomHitAreaFP13CmdRingCustom(*(undefined4 *)(param_1 + 0x1ec),param_1);
  *(byte *)(*(int *)(param_1 + 0x1ec) + 0x12) =
       *(byte *)(*(int *)(param_1 + 0x1ec) + 0x12) & 0xfe | 1;
  if (param_2 != 0) {
    iVar1 = *(int *)(param_1 + 0x1ec);
    Open__10MenuWindowFUci(iVar1,*(byte *)(iVar1 + 0xb0) & 7,*(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x10)
                   );
  }
  UpdateInfo__13CmdRingCustomFssss(param_1,1,1,2,0);
  return;
}

/* JP: 0x00467d30  CmdRingCustom::UpdateInfo(short, short, short, short)   [UpdateInfo__13CmdRingCustomFssss]  size=0x12c */
void UpdateInfo__13CmdRingCustomFssss
               (int param_1,short param_2,short param_3,undefined2 param_4,undefined2 param_5)

{
  int iVar1;
  undefined4 uVar2;
  long lVar3;
  
  if (*(int *)(param_1 + 0x1f0) == 0) {
    lVar3 = __nw__FUi(0xa80);
    uVar2 = 0;
    if (lVar3 != 0) {
      uVar2 = __ct__17CmdRingCustomInfoFv(lVar3);
    }
    *(undefined4 *)(param_1 + 0x1f0) = uVar2;
    CreateScene__17CmdRingCustomInfoFP13CmdRingCustom(*(undefined4 *)(param_1 + 0x1f0),param_1);
  }
  if (-1 < param_3) {
    UpdateScene__17CmdRingCustomInfoFP13CmdRingCustomsss
              (*(undefined4 *)(param_1 + 0x1f0),param_1,param_3,param_4,param_5);
  }
  *(byte *)(*(int *)(param_1 + 0x1f0) + 0x12) =
       *(byte *)(*(int *)(param_1 + 0x1f0) + 0x12) & 0xfe | 1;
  if (param_2 != 0) {
    iVar1 = *(int *)(param_1 + 0x1f0);
    Open__10MenuWindowFUci(iVar1,*(byte *)(iVar1 + 0xb0) & 7,*(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x10)
                   );
  }
  return;
}

/* JP: 0x00467e60  CmdRingCustom::UpdateFinal(short, short)   [UpdateFinal__13CmdRingCustomFss]  size=0x1c8 */
void UpdateFinal__13CmdRingCustomFss(int param_1,short param_2,undefined2 param_3)

{
  int iVar1;
  undefined4 uVar2;
  long lVar3;
  
  if (*(int *)(param_1 + 500) == 0) {
    lVar3 = __nw__FUi(0x254);
    uVar2 = 0;
    if (lVar3 != 0) {
      uVar2 = __ct__22CmdRingCustomFinalSlotFv(lVar3);
    }
    *(undefined4 *)(param_1 + 500) = uVar2;
    CreateScene__22CmdRingCustomFinalSlotFP13CmdRingCustom(*(undefined4 *)(param_1 + 500),param_1);
    lVar3 = __nw__FUi(0x128);
    uVar2 = 0;
    if (lVar3 != 0) {
      uVar2 = __ct__23CmdRingCustomFinalGoodsFv(lVar3);
    }
    *(undefined4 *)(param_1 + 0x1f8) = uVar2;
    CreateScene__23CmdRingCustomFinalGoodsFP13CmdRingCustom
              (*(undefined4 *)(param_1 + 0x1f8),param_1);
  }
  UpdateScene__22CmdRingCustomFinalSlotFP13CmdRingCustom(*(undefined4 *)(param_1 + 500),param_1);
  UpdateScene__23CmdRingCustomFinalGoodsFP13CmdRingCustoms
            (*(undefined4 *)(param_1 + 0x1f8),param_1,param_3);
  if (param_2 == 0) {
    *(byte *)(*(int *)(param_1 + 500) + 0x12) = *(byte *)(*(int *)(param_1 + 500) + 0x12) & 0xfe | 1
    ;
    *(byte *)(*(int *)(param_1 + 0x1f8) + 0x12) =
         *(byte *)(*(int *)(param_1 + 0x1f8) + 0x12) & 0xfe | 1;
  }
  else {
    iVar1 = *(int *)(param_1 + 500);
    Open__10MenuWindowFUci(iVar1,*(byte *)(iVar1 + 0xb0) & 7,*(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x10)
                   );
    iVar1 = *(int *)(param_1 + 0x1f8);
    Open__10MenuWindowFUci(iVar1,*(byte *)(iVar1 + 0xb0) & 7,*(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x10)
                   );
  }
  return;
}

/* JP: 0x00468030  CmdRingCustom::UpdateGoods(short)   [UpdateGoods__13CmdRingCustomFs]  size=0xfc */
void UpdateGoods__13CmdRingCustomFs(int param_1,short param_2)

{
  int iVar1;
  undefined4 uVar2;
  long lVar3;
  
  if (*(int *)(param_1 + 0x1e8) == 0) {
    lVar3 = __nw__FUi(0x2f8);
    uVar2 = 0;
    if (lVar3 != 0) {
      uVar2 = __ct__18CmdRingCustomGoodsFv(lVar3);
    }
    *(undefined4 *)(param_1 + 0x1e8) = uVar2;
    CreateScene__18CmdRingCustomGoodsFP13CmdRingCustom(*(undefined4 *)(param_1 + 0x1e8),param_1);
  }
  UpdateScene__18CmdRingCustomGoodsFP13CmdRingCustom(*(undefined4 *)(param_1 + 0x1e8),param_1);
  *(byte *)(*(int *)(param_1 + 0x1e8) + 0x12) =
       *(byte *)(*(int *)(param_1 + 0x1e8) + 0x12) & 0xfe | 1;
  if (param_2 != 0) {
    iVar1 = *(int *)(param_1 + 0x1e8);
    Open__10MenuWindowFUci(iVar1,*(byte *)(iVar1 + 0xb0) & 7,*(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x10)
                   );
  }
  return;
}

/* JP: 0x00468130  CmdRingCustom::UpdateCount(short)   [UpdateCount__13CmdRingCustomFs]  size=0xfc */
void UpdateCount__13CmdRingCustomFs(int param_1,short param_2)

{
  int iVar1;
  undefined4 uVar2;
  long lVar3;
  
  if (*(int *)(param_1 + 0x1fc) == 0) {
    lVar3 = __nw__FUi(0x788);
    uVar2 = 0;
    if (lVar3 != 0) {
      uVar2 = __ct__18CmdRingCustomCountFv(lVar3);
    }
    *(undefined4 *)(param_1 + 0x1fc) = uVar2;
    CreateScene__18CmdRingCustomCountFP13CmdRingCustom(*(undefined4 *)(param_1 + 0x1fc),param_1);
  }
  UpdateScene__18CmdRingCustomCountFP13CmdRingCustom(*(undefined4 *)(param_1 + 0x1fc),param_1);
  *(byte *)(*(int *)(param_1 + 0x1fc) + 0x12) =
       *(byte *)(*(int *)(param_1 + 0x1fc) + 0x12) & 0xfe | 1;
  if (param_2 != 0) {
    iVar1 = *(int *)(param_1 + 0x1fc);
    Open__10MenuWindowFUci(iVar1,*(byte *)(iVar1 + 0xb0) & 7,*(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x10)
                   );
  }
  return;
}

/* JP: 0x00468230  CmdRingCustom::UpdateAutoRing(short)   [UpdateAutoRing__13CmdRingCustomFs]  size=0xfc */
void UpdateAutoRing__13CmdRingCustomFs(int param_1,short param_2)

{
  int iVar1;
  undefined4 uVar2;
  long lVar3;
  
  if (*(int *)(param_1 + 0x200) == 0) {
    lVar3 = __nw__FUi(0x1f8);
    uVar2 = 0;
    if (lVar3 != 0) {
      uVar2 = __ct__21CmdRingCustomAutoRingFv(lVar3);
    }
    *(undefined4 *)(param_1 + 0x200) = uVar2;
    CreateScene__21CmdRingCustomAutoRingFP13CmdRingCustom(*(undefined4 *)(param_1 + 0x200),param_1);
  }
  UpdateScene__21CmdRingCustomAutoRingFP13CmdRingCustom(*(undefined4 *)(param_1 + 0x200),param_1);
  *(byte *)(*(int *)(param_1 + 0x200) + 0x12) =
       *(byte *)(*(int *)(param_1 + 0x200) + 0x12) & 0xfe | 1;
  if (param_2 != 0) {
    iVar1 = *(int *)(param_1 + 0x200);
    Open__10MenuWindowFUci(iVar1,*(byte *)(iVar1 + 0xb0) & 7,*(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x10)
                   );
  }
  return;
}

/* JP: 0x00468330  CmdRingCustom::CreateContent(short)   [CreateContent__13CmdRingCustomFs]  size=0x130 */
void CreateContent__13CmdRingCustomFs(undefined4 param_1,short param_2)

{
  if (param_2 == 4) {
    UpdateAutoRing__13CmdRingCustomFs(param_1,1);
  }
  else if (param_2 == 3) {
    UpdateGoods__13CmdRingCustomFs(param_1,1);
  }
  else if (param_2 == 2) {
    UpdateCount__13CmdRingCustomFs(param_1,1);
    UpdateInfo__13CmdRingCustomFssss(param_1,1,0,1,0);
  }
  else if (param_2 == 1) {
    UpdateFinal__13CmdRingCustomFss(param_1,1,0);
  }
  else if (param_2 == 0) {
    UpdateHitArea__13CmdRingCustomFs(param_1,1);
  }
  UpdateTitle__13CmdRingCustomFss(param_1,1,param_2);
  UpdateFence__13CmdRingCustomFss(param_1,1,param_2);
  return;
}

/* JP: 0x00468460  CmdRingCustom::DestroyContent(short)   [DestroyContent__13CmdRingCustomFs]  size=0x190 */
void DestroyContent__13CmdRingCustomFs(int param_1,short param_2)

{
  if (param_2 == 4) {
    (**(code **)(*(int *)(*(int *)(param_1 + 0x200) + 8) + 0xc))();
    *(undefined4 *)(param_1 + 0x200) = 0;
  }
  else if (param_2 == 3) {
    (**(code **)(*(int *)(*(int *)(param_1 + 0x1e8) + 8) + 0xc))();
    *(undefined4 *)(param_1 + 0x1e8) = 0;
  }
  else if (param_2 == 2) {
    (**(code **)(*(int *)(*(int *)(param_1 + 0x1fc) + 8) + 0xc))();
    *(undefined4 *)(param_1 + 0x1fc) = 0;
    (**(code **)(*(int *)(*(int *)(param_1 + 0x1f0) + 8) + 0xc))();
    *(undefined4 *)(param_1 + 0x1f0) = 0;
  }
  else if (param_2 == 1) {
    (**(code **)(*(int *)(*(int *)(param_1 + 500) + 8) + 0xc))();
    *(undefined4 *)(param_1 + 500) = 0;
    (**(code **)(*(int *)(*(int *)(param_1 + 0x1f8) + 8) + 0xc))();
    *(undefined4 *)(param_1 + 0x1f8) = 0;
  }
  else if (param_2 == 0) {
    (**(code **)(*(int *)(*(int *)(param_1 + 0x1ec) + 8) + 0xc))();
    *(undefined4 *)(param_1 + 0x1ec) = 0;
    (**(code **)(*(int *)(*(int *)(param_1 + 0x1f0) + 8) + 0xc))();
    *(undefined4 *)(param_1 + 0x1f0) = 0;
  }
  return;
}

/* JP: 0x004685f0  CmdRingCustom::StartExplain()   [StartExplain__13CmdRingCustomFv]  size=0x3a4 */
void StartExplain__13CmdRingCustomFv(int param_1)

{
  int iVar1;
  undefined *puVar2;
  undefined4 uVar3;
  long lVar4;
  undefined2 uVar5;
  
  lVar4 = __nw__FUi(0x52c);
  uVar3 = 0;
  if (lVar4 != 0) {
    uVar3 = __ct__10CmdExplainFv(lVar4);
  }
  *(undefined4 *)(param_1 + 0x208) = uVar3;
  Initialize__9MenuSceneFPUcP9BufMemory(*(undefined4 *)(param_1 + 0x208),*(undefined4 *)(*(int *)(param_1 + 0x54) + 0x4c),
                  0);
  if (*(char *)(param_1 + 0x21d) == '\x03') {
    uVar5 = 2;
    iVar1 = *(int *)(param_1 + 0x1e8);
    Close__10MenuWindowFUci(iVar1,((ulong)*(byte *)(iVar1 + 0xb0) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x14));
  }
  else {
    uVar5 = 0;
    if (*(char *)(param_1 + 0x21d) == '\x06') {
      uVar5 = *(undefined2 *)(*(int *)(param_1 + 0x1f8) + 0xae);
    }
    iVar1 = *(int *)(param_1 + 500);
    Close__10MenuWindowFUci(iVar1,((ulong)*(byte *)(iVar1 + 0xb0) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x14));
    iVar1 = *(int *)(param_1 + 0x1f8);
    Close__10MenuWindowFUci(iVar1,((ulong)*(byte *)(iVar1 + 0xb0) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x14));
    SetIcon__10CmdExplainFP11MenuTexture(*(undefined4 *)(param_1 + 0x208),0x421698);
    SetImage__10CmdExplainFPcss
              (*(undefined4 *)(param_1 + 0x208),*(undefined4 *)(*(int *)(param_1 + 0x24) + 0x38),1,0
              );
  }
  SetInfo__10CmdExplainFP4MenusUcUc
            (*(undefined4 *)(param_1 + 0x208),*(undefined4 *)(param_1 + 0x10),uVar5,3,0);
  SetExplanation__7CmdNoteFPCce
            (*(undefined4 *)(param_1 + 100),*(undefined4 *)(*(int *)(param_1 + 0x24) + 0x20));
  iVar1 = *(int *)(param_1 + 0x78);
  Close__10MenuWindowFUci(iVar1 + 0x58,((ulong)*(byte *)(iVar1 + 0x108) & 0x3f) >> 3,
                  *(undefined4 *)(*(int *)(iVar1 + 0x8c) + 0x14));
  iVar1 = *(int *)(param_1 + 0x1e0);
  Close__10MenuWindowFUci(iVar1 + 0x58,((ulong)*(byte *)(iVar1 + 0x108) & 0x3f) >> 3,
                  *(undefined4 *)(*(int *)(iVar1 + 0x8c) + 0x14));
  iVar1 = *(int *)(param_1 + 0x1e4);
  Close__10MenuWindowFUci(iVar1,((ulong)*(byte *)(iVar1 + 0xb0) & 0x3f) >> 3,
                  *(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x14));
  iVar1 = *(int *)(param_1 + 0x68);
  Close__10MenuWindowFUci(iVar1 + 0x58,((ulong)*(byte *)(iVar1 + 0x108) & 0x3f) >> 3,
                  *(undefined4 *)(*(int *)(iVar1 + 0x8c) + 0x14));
  *(byte *)(*(int *)(param_1 + 0x18) + 0x12) = *(byte *)(*(int *)(param_1 + 0x18) + 0x12) & 0xfe;
  *(ushort *)(param_1 + 0x1e) = (ushort)(*(byte *)(param_1 + 0x23) >> 6);
  SetChengePCMode__10CmdPCSceneFUc(param_1,0);
  puVar2 = PTR_ShiftExplain__13CmdRingCustomFv_0050d6b0;
  uVar3 = DAT_0050d6ac;
  *(undefined4 *)(param_1 + 0x7c) = _5851;
  *(undefined4 *)(param_1 + 0x80) = uVar3;
  *(undefined **)(param_1 + 0x84) = puVar2;
  return;
}

/* JP: 0x004689a0  CmdRingCustom::SetExplain()   [SetExplain__13CmdRingCustomFv]  size=0x174 */
void SetExplain__13CmdRingCustomFv(int param_1)

{
  ushort uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  
  iVar2 = *(int *)(param_1 + 0x208);
  memset(iVar2 + 0x5c,0,0x10);
  uVar1 = *(ushort *)(*(int *)(*(int *)(param_1 + 0x18) + 0xec) + 0x16);
  *(ushort *)(iVar2 + 0x5c) = uVar1;
  if (*(char *)(param_1 + 0x21d) == '\x03') {
    puVar4 = (undefined4 *)(*(int *)(param_1 + 0x210) + (uint)uVar1 * 0x10);
    *(undefined4 *)(iVar2 + 0x60) = *puVar4;
    *(undefined4 *)(iVar2 + 100) = puVar4[1];
    *(undefined4 **)(iVar2 + 0x68) = puVar4 + 3;
  }
  else {
    puVar4 = (undefined4 *)(*(int *)(param_1 + 0x20c) + (uint)uVar1 * 8);
    *(undefined1 *)(iVar2 + 0x5e) = *(undefined1 *)(param_1 + 0x21c);
    uVar3 = GetRegDat__9RegDatApiFiii(0x11,uVar1,0xffffffffffffffff);
    *(undefined4 *)(iVar2 + 0x60) = uVar3;
    *(undefined4 *)(iVar2 + 100) = *puVar4;
    *(undefined4 **)(iVar2 + 0x68) = puVar4 + 1;
  }
  Open__10CmdExplainFv(*(undefined4 *)(param_1 + 0x208));
  return;
}

/* JP: 0x00468b20  CmdRingCustom::SetButtonReport(short, short)   [SetButtonReport__13CmdRingCustomFss]  size=0xb0 */
void SetButtonReport__13CmdRingCustomFss(int param_1,short param_2,short param_3)

{
  ClearReport__15CmdButtonReportFv(*(undefined4 *)(param_1 + 0x68));
  if (param_3 != 0) {
    SetReport__15CmdButtonReportFii
              (*(int *)(param_1 + 0x68),*(undefined1 *)(*(int *)(param_1 + 0x68) + 0x20),0xd);
  }
  if (-1 < param_2) {
    SetReport__15CmdButtonReportFii
              (*(int *)(param_1 + 0x68),*(undefined1 *)(*(int *)(param_1 + 0x68) + 0x20),4);
  }
  return;
}

/* JP: 0x00468bd0  CmdRingCustom::ShiftMenu()   [ShiftMenu__13CmdRingCustomFv]  size=0x120 */
void ShiftMenu__13CmdRingCustomFv(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined *puVar3;
  undefined8 uVar4;
  
  uVar4 = GetPlace__10MenuWindowFss(param_1 + 0xe4,0,*(undefined1 *)(param_1 + 0x21d));
  Select__6CursorFP9MenuPlace(*(undefined4 *)(param_1 + 0x18),uVar4);
  Select__10CmdSubMenuFP7CmdNoteP9MenuPlaceP9MenuPlace
            (param_1 + 0x8c,*(undefined4 *)(param_1 + 100),uVar4,0);
  SetChengePCMode__10CmdPCSceneFUc(param_1,1);
  iVar1 = *(int *)(param_1 + 0x68);
  Close__10MenuWindowFUci(iVar1 + 0x58,((ulong)*(byte *)(iVar1 + 0x108) & 0x3f) >> 3,
                  *(undefined4 *)(*(int *)(iVar1 + 0x8c) + 0x14));
  *(undefined1 *)(param_1 + 0x21d) = 5;
  puVar3 = PTR_SelectMenu__13CmdRingCustomFv_0050d6c0;
  uVar2 = DAT_0050d6bc;
  *(undefined4 *)(param_1 + 0x7c) = _5954;
  *(undefined4 *)(param_1 + 0x80) = uVar2;
  *(undefined **)(param_1 + 0x84) = puVar3;
  return;
}

/* JP: 0x00468cf0  CmdRingCustom::StartMessage(char*)   [StartMessage__13CmdRingCustomFPc]  size=0x120 */
void StartMessage__13CmdRingCustomFPc(int param_1,undefined4 param_2)

{
  long lVar1;
  undefined8 uVar2;
  int iVar3;
  
  *(byte *)(*(int *)(param_1 + 0x18) + 0xfb) = *(byte *)(*(int *)(param_1 + 0x18) + 0xfb) & 0xef;
  *(byte *)(*(int *)(param_1 + 0x18) + 0x12) = *(byte *)(*(int *)(param_1 + 0x18) + 0x12) & 0xfe;
  *(undefined1 *)(param_1 + 0x21e) = 1;
  lVar1 = __nw__FUi(0x3e4);
  uVar2 = 0;
  if (lVar1 != 0) {
    uVar2 = __ct__14CmdRingMessageFv(lVar1);
  }
  iVar3 = (int)uVar2;
  *(int *)(param_1 + 0x204) = iVar3;
  Initialize__9MenuSceneFPUcP9BufMemory(uVar2,*(undefined4 *)(*(int *)(param_1 + 0x54) + 0x58),0);
  *(undefined2 *)(iVar3 + 0x1c) = 0x16;
  *(undefined4 *)(iVar3 + 0x10) = *(undefined4 *)(param_1 + 0x10);
  StartMessage__14CmdRingMessageFsPc(uVar2,*(undefined2 *)(param_1 + 0x1c),param_2);
  return;
}

/* JP: 0x00468e10  CmdRingCustom::Enter()   [Enter__13CmdRingCustomFv]  size=0x2b8 */
undefined8 Enter__13CmdRingCustomFv(int param_1)

{
  bool bVar1;
  undefined4 uVar2;
  undefined *puVar3;
  undefined1 uVar4;
  undefined8 uVar5;
  
  if (*(char *)(param_1 + 0x21) == '\0') {
    UpdateScene__10CmdSubMenuFs(param_1 + 0x8c,0);
    Open__10MenuWindowFUci(param_1 + 0xe4,*(byte *)(param_1 + 0x194) & 7,
                    *(undefined4 *)(*(int *)(param_1 + 0x118) + 0x10));
    (**(code **)(*(int *)(param_1 + 8) + 0x28))(param_1,1);
    uVar5 = GetPlace__10MenuWindowFiss(param_1 + 0xe4,2,0,0xffffffffffffffff);
    Select__6CursorFP9MenuPlace(*(undefined4 *)(param_1 + 0x18),uVar5);
    Select__10CmdSubMenuFP7CmdNoteP9MenuPlaceP9MenuPlace
              (param_1 + 0x8c,*(undefined4 *)(param_1 + 100),uVar5,0);
    CreateContent__13CmdRingCustomFs(param_1,*(undefined2 *)((int)uVar5 + 0x1e));
    SetTitle__11CmdTitleLogFPUci
              (*(undefined4 *)(param_1 + 0x60),*(undefined4 *)(*(int *)(param_1 + 0x54) + 0x10),0xe)
    ;
    Open__11CmdTitleLogFv(*(undefined4 *)(param_1 + 0x60));
    uVar4 = CreateBackGround__7CmdMenuFs(*(undefined4 *)(param_1 + 0x10),8);
    *(undefined1 *)(param_1 + 0x20) = uVar4;
    *(char *)(param_1 + 0x21) = *(char *)(param_1 + 0x21) + '\x01';
  }
  else if (*(char *)(param_1 + 0x21) == '\x01') {
    if ((*(char *)(*(int *)(param_1 + 0x1e0) + 0x100) == '\x01') ||
       (*(char *)(*(int *)(param_1 + 0x1e0) + 0x100) == '\0')) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
    if (bVar1) {
      if (*(char *)(param_1 + 0x20) != '\0') {
        DestroyBackGround__7CmdMenuFs(*(undefined4 *)(param_1 + 0x10),1);
        *(undefined1 *)(param_1 + 0x20) = 0;
      }
      Restore__6CursorFv(*(undefined4 *)(param_1 + 0x18));
      SetChengePCMode__10CmdPCSceneFUc(param_1,1);
      *(undefined1 *)(param_1 + 0x21d) = 5;
      *(undefined1 *)(*(int *)(param_1 + 0x10) + 0x4e) = 1;
      *(undefined1 *)(param_1 + 0x21) = 0;
      puVar3 = PTR_SelectMenu__13CmdRingCustomFv_0050d6d0;
      uVar2 = DAT_0050d6cc;
      *(undefined4 *)(param_1 + 0x7c) = _6002;
      *(undefined4 *)(param_1 + 0x80) = uVar2;
      *(undefined **)(param_1 + 0x84) = puVar3;
    }
  }
  return 0;
}

/* JP: 0x004690d0  CmdRingCustom::Exit()   [Exit__13CmdRingCustomFv]  size=0x480 */
undefined8 Exit__13CmdRingCustomFv(int param_1)

{
  char cVar1;
  int iVar2;
  bool bVar3;
  
  if (*(char *)(param_1 + 0x21) == '\0') {
    (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x14) + 0x28))(*(int *)(param_1 + 0x10),0,0,5);
    Shutdown__6CursorFv(*(undefined4 *)(param_1 + 0x18));
    iVar2 = *(int *)(param_1 + 0x78);
    Close__10MenuWindowFUci(iVar2 + 0x58,((ulong)*(byte *)(iVar2 + 0x108) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar2 + 0x8c) + 0x14));
    iVar2 = *(int *)(param_1 + 0x60);
    Close__10MenuWindowFUci(iVar2 + 0x58,((ulong)*(byte *)(iVar2 + 0x108) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar2 + 0x8c) + 0x14));
    Close__10MenuWindowFUci(param_1 + 0xe4,((ulong)*(byte *)(param_1 + 0x194) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(param_1 + 0x118) + 0x14));
    iVar2 = *(int *)(param_1 + 0x1e0);
    Close__10MenuWindowFUci(iVar2 + 0x58,((ulong)*(byte *)(iVar2 + 0x108) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar2 + 0x8c) + 0x14));
    if (*(int *)(param_1 + 0x1e4) != 0) {
      iVar2 = *(int *)(param_1 + 0x1e4);
      Close__10MenuWindowFUci(iVar2,((ulong)*(byte *)(iVar2 + 0xb0) & 0x3f) >> 3,
                      *(undefined4 *)(*(int *)(iVar2 + 0x34) + 0x14));
    }
    cVar1 = *(char *)(param_1 + 0x21d);
    if (cVar1 == '\x04') {
      iVar2 = *(int *)(param_1 + 0x200);
      Close__10MenuWindowFUci(iVar2,((ulong)*(byte *)(iVar2 + 0xb0) & 0x3f) >> 3,
                      *(undefined4 *)(*(int *)(iVar2 + 0x34) + 0x14));
    }
    else if (cVar1 == '\x03') {
      iVar2 = *(int *)(param_1 + 0x1e8);
      Close__10MenuWindowFUci(iVar2,((ulong)*(byte *)(iVar2 + 0xb0) & 0x3f) >> 3,
                      *(undefined4 *)(*(int *)(iVar2 + 0x34) + 0x14));
    }
    else if (cVar1 == '\x02') {
      iVar2 = *(int *)(param_1 + 0x1f0);
      Close__10MenuWindowFUci(iVar2,((ulong)*(byte *)(iVar2 + 0xb0) & 0x3f) >> 3,
                      *(undefined4 *)(*(int *)(iVar2 + 0x34) + 0x14));
      iVar2 = *(int *)(param_1 + 0x1fc);
      Close__10MenuWindowFUci(iVar2,((ulong)*(byte *)(iVar2 + 0xb0) & 0x3f) >> 3,
                      *(undefined4 *)(*(int *)(iVar2 + 0x34) + 0x14));
    }
    else if (cVar1 == '\x01') {
      iVar2 = *(int *)(param_1 + 500);
      Close__10MenuWindowFUci(iVar2,((ulong)*(byte *)(iVar2 + 0xb0) & 0x3f) >> 3,
                      *(undefined4 *)(*(int *)(iVar2 + 0x34) + 0x14));
      iVar2 = *(int *)(param_1 + 0x1f8);
      Close__10MenuWindowFUci(iVar2,((ulong)*(byte *)(iVar2 + 0xb0) & 0x3f) >> 3,
                      *(undefined4 *)(*(int *)(iVar2 + 0x34) + 0x14));
    }
    else if (cVar1 == '\0') {
      iVar2 = *(int *)(param_1 + 0x1ec);
      Close__10MenuWindowFUci(iVar2,((ulong)*(byte *)(iVar2 + 0xb0) & 0x3f) >> 3,
                      *(undefined4 *)(*(int *)(iVar2 + 0x34) + 0x14));
      iVar2 = *(int *)(param_1 + 0x1f0);
      Close__10MenuWindowFUci(iVar2,((ulong)*(byte *)(iVar2 + 0xb0) & 0x3f) >> 3,
                      *(undefined4 *)(*(int *)(iVar2 + 0x34) + 0x14));
    }
    RingClose__5JRingFi(*(undefined4 *)(param_1 + 0x88),0);
    *(char *)(param_1 + 0x21) = *(char *)(param_1 + 0x21) + '\x01';
  }
  else if (*(char *)(param_1 + 0x21) == '\x01') {
    if ((*(char *)(*(int *)(param_1 + 0x78) + 0x100) == '\x01') ||
       (*(char *)(*(int *)(param_1 + 0x78) + 0x100) == '\0')) {
      bVar3 = true;
    }
    else {
      bVar3 = false;
    }
    if (bVar3) {
      ReleaseOT__7MenuObjFv(param_1 + 0xe4);
      Destruct__5JRingFb(*(undefined4 *)(param_1 + 0x88),0);
      *(undefined4 *)(param_1 + 0x88) = 0;
      (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x14) + 0x24))(*(int *)(param_1 + 0x10),0);
      DestroyScene__4MenuFP9MenuSceneb(*(undefined4 *)(param_1 + 0x10),param_1,1);
    }
  }
  return 0;
}

/* JP: 0x00469550  CmdRingCustom::SelectMenu()   [SelectMenu__13CmdRingCustomFv]  size=0x560 */
undefined8 SelectMenu__13CmdRingCustomFv(int param_1)

{
  short sVar1;
  ushort uVar2;
  int iVar3;
  bool bVar4;
  undefined4 uVar5;
  undefined *puVar6;
  int iVar7;
  int unaff_s0_lo;
  undefined2 uVar8;
  
  uVar2 = *(ushort *)(*(int *)(param_1 + 0x10) + 0x48);
  iVar3 = *(int *)(*(int *)(param_1 + 0x18) + 0xec);
  sVar1 = *(short *)(iVar3 + 0x1e);
  if ((uVar2 & 0x2000) == 0) {
    if ((uVar2 & 0x4000) == 0) {
      iVar7 = MoveVertical__9MenuSceneFi(param_1,0);
      if (iVar7 != iVar3) {
        DestroyContent__13CmdRingCustomFs(param_1,sVar1);
        CreateContent__13CmdRingCustomFs(param_1,*(undefined2 *)(iVar7 + 0x1e));
        Select__10CmdSubMenuFP7CmdNoteP9MenuPlaceP9MenuPlace
                  (param_1 + 0x8c,*(undefined4 *)(param_1 + 100),iVar7,iVar3);
        PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),0,0,0);
      }
    }
    else {
      *(char *)(param_1 + 0x21d) = (char)sVar1;
      SetChengePCMode__10CmdPCSceneFUc(param_1,0);
      puVar6 = PTR_Exit__13CmdRingCustomFv_0050d730;
      uVar5 = DAT_0050d72c;
      *(undefined4 *)(param_1 + 0x7c) = _6122;
      *(undefined4 *)(param_1 + 0x80) = uVar5;
      *(undefined **)(param_1 + 0x84) = puVar6;
      PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),3,0,0);
    }
  }
  else {
    uVar8 = 0xffff;
    bVar4 = false;
    if (sVar1 == 4) {
      iVar3 = *(int *)(*(int *)(param_1 + 0x200) + 500);
      *(undefined2 *)(iVar3 + 0x7e) = 0xe;
      SetCSA__8FontItemFUc(iVar3,0xe);
      unaff_s0_lo = *(int *)(*(int *)(param_1 + 0x200) + 500);
      Select__21CmdRingCustomAutoRingFP13CmdRingCustomP8MenuTextP8MenuTexts
                (*(undefined4 *)(param_1 + 0x200),param_1,unaff_s0_lo,0,1);
      puVar6 = PTR_SelectAutoRing__13CmdRingCustomFv_0050d720;
      uVar5 = DAT_0050d71c;
      *(undefined4 *)(param_1 + 0x7c) = _6115;
      *(undefined4 *)(param_1 + 0x80) = uVar5;
      *(undefined **)(param_1 + 0x84) = puVar6;
    }
    else if (sVar1 == 3) {
      uVar8 = 1;
      iVar3 = *(int *)(*(int *)(param_1 + 0x1e8) + 0x2f4);
      *(undefined2 *)(iVar3 + 0x7e) = 0xe;
      SetCSA__8FontItemFUc(iVar3,0xe);
      unaff_s0_lo = *(int *)(*(int *)(param_1 + 0x1e8) + 0x2f4);
      Select__18CmdRingCustomGoodsFP13CmdRingCustomP8MenuTextP8MenuTexts
                (*(undefined4 *)(param_1 + 0x1e8),param_1,unaff_s0_lo,0,1);
      puVar6 = PTR_SelectGoods__13CmdRingCustomFv_0050d710;
      uVar5 = DAT_0050d70c;
      *(undefined4 *)(param_1 + 0x7c) = _6112;
      *(undefined4 *)(param_1 + 0x80) = uVar5;
      *(undefined **)(param_1 + 0x84) = puVar6;
    }
    else if (sVar1 == 2) {
      SetClut__18CmdRingCustomCountFs(*(undefined4 *)(param_1 + 0x1fc),0xe);
      unaff_s0_lo = *(int *)(*(int *)(param_1 + 0x1fc) + 0x784);
      Select__18CmdRingCustomCountFP13CmdRingCustomP9MenuPlaceP9MenuPlaces
                (*(undefined4 *)(param_1 + 0x1fc),param_1,unaff_s0_lo,0,1);
      puVar6 = PTR_SelectCount__13CmdRingCustomFv_0050d700;
      uVar5 = DAT_0050d6fc;
      *(undefined4 *)(param_1 + 0x7c) = _6109;
      *(undefined4 *)(param_1 + 0x80) = uVar5;
      *(undefined **)(param_1 + 0x84) = puVar6;
    }
    else if (sVar1 == 1) {
      unaff_s0_lo = GetPlace__10MenuWindowFss(*(undefined4 *)(param_1 + 500),0,0);
      Select__22CmdRingCustomFinalSlotFP13CmdRingCustom(*(undefined4 *)(param_1 + 500),param_1);
      puVar6 = PTR_SelectFinalSlot__13CmdRingCustomFv_0050d6f0;
      uVar5 = DAT_0050d6ec;
      uVar8 = *(undefined2 *)(unaff_s0_lo + 0x16);
      bVar4 = true;
      *(undefined4 *)(param_1 + 0x7c) = _6106;
      *(undefined4 *)(param_1 + 0x80) = uVar5;
      *(undefined **)(param_1 + 0x84) = puVar6;
    }
    else if (sVar1 == 0) {
      unaff_s0_lo = GetPlace__10MenuWindowFss(*(undefined4 *)(param_1 + 0x1ec),0,0);
      Select__20CmdRingCustomHitAreaFP13CmdRingCustomP9MenuPlaceP9MenuPlace
                (*(undefined4 *)(param_1 + 0x1ec),param_1,unaff_s0_lo,0);
      puVar6 = PTR_SelectHitArea__13CmdRingCustomFv_0050d6e0;
      uVar5 = DAT_0050d6dc;
      *(undefined4 *)(param_1 + 0x7c) = _6103;
      *(undefined4 *)(param_1 + 0x80) = uVar5;
      *(undefined **)(param_1 + 0x84) = puVar6;
    }
    if (!bVar4) {
      SetChengePCMode__10CmdPCSceneFUc(param_1,0);
    }
    Select__6CursorFP9MenuPlace(*(undefined4 *)(param_1 + 0x18),unaff_s0_lo);
    SetButtonReport__13CmdRingCustomFss(param_1,uVar8,0);
    Open__15CmdButtonReportFv(*(undefined4 *)(param_1 + 0x68));
    *(char *)(param_1 + 0x21d) = (char)sVar1;
    PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),2,0,0);
  }
  return 0;
}

/* JP: 0x00469ab0  CmdRingCustom::SelectHitArea()   [SelectHitArea__13CmdRingCustomFv]  size=0x218 */
undefined8 SelectHitArea__13CmdRingCustomFv(int param_1)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  long lVar4;
  
  uVar1 = *(ushort *)(*(int *)(param_1 + 0x10) + 0x48);
  iVar2 = *(int *)(*(int *)(param_1 + 0x18) + 0xec);
  if ((uVar1 & 0x4000) == 0) {
    iVar3 = MoveVertical__9MenuSceneFi(param_1,0);
    if (iVar2 == iVar3) {
      lVar4 = 0;
      if ((uVar1 & 0x80) == 0) {
        if ((uVar1 & 0x20) != 0) {
          lVar4 = 1;
        }
      }
      else {
        lVar4 = -1;
      }
      if (lVar4 != 0) {
        Custom__20CmdRingCustomHitAreaFP13CmdRingCustomP9MenuPlaces
                  (*(undefined4 *)(param_1 + 0x1ec),param_1,iVar3,lVar4);
        UpdateInfo__13CmdRingCustomFssss(param_1,0,1,2,0);
        PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),1,0,0);
      }
    }
    else {
      Select__20CmdRingCustomHitAreaFP13CmdRingCustomP9MenuPlaceP9MenuPlace
                (*(undefined4 *)(param_1 + 0x1ec),param_1,iVar3,iVar2);
      PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),0,0,0);
    }
  }
  else {
    Select__20CmdRingCustomHitAreaFP13CmdRingCustomP9MenuPlaceP9MenuPlace
              (*(undefined4 *)(param_1 + 0x1ec),param_1,0,iVar2);
    SetScroll__10MenuWindowFss(*(undefined4 *)(param_1 + 0x1ec),0,0);
    ShiftMenu__13CmdRingCustomFv(param_1);
    PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),3,0,0);
  }
  return 0;
}

/* JP: 0x00469cd0  CmdRingCustom::SelectFinalSlot()   [SelectFinalSlot__13CmdRingCustomFv]  size=0x340 */
undefined8 SelectFinalSlot__13CmdRingCustomFv(int param_1)

{
  short sVar1;
  ushort uVar2;
  undefined *puVar3;
  undefined8 uVar4;
  ulong uVar5;
  undefined4 uVar6;
  
  uVar2 = *(ushort *)(*(int *)(param_1 + 0x10) + 0x48);
  sVar1 = *(short *)(*(int *)(*(int *)(param_1 + 0x18) + 0xec) + 0x16);
  if ((uVar2 & 0x2000) == 0) {
    if ((uVar2 & 0x4000) == 0) {
      if (((uVar2 & 0x1000) != 0) && ((long)*(char *)(param_1 + 0x21f) <= (long)sVar1)) {
        StartExplain__13CmdRingCustomFv(param_1);
        PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),2,0,0);
      }
    }
    else {
      SetCSA__8FontItemFUc(*(int *)(param_1 + 500) + 0x1d4,0);
      ShiftMenu__13CmdRingCustomFv(param_1);
      PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),3,0,0);
    }
  }
  else {
    uVar6 = 4;
    if (((long)*(char *)(param_1 + 0x21f) <= (long)sVar1) ||
       (*(short *)(*(int *)(param_1 + 0x1f8) + 0xae) != 0)) {
      SetCSA__8FontItemFUc(*(int *)(param_1 + 500) + 0x1d4,0);
      if ((long)*(char *)(param_1 + 0x21f) <= (long)sVar1) {
        UpdateScene__23CmdRingCustomFinalGoodsFP13CmdRingCustoms
                  (*(undefined4 *)(param_1 + 0x1f8),param_1,1);
      }
      uVar4 = GetPlace__10MenuWindowFss(*(undefined4 *)(param_1 + 0x1f8),0,0);
      Select__6CursorFP9MenuPlace(*(undefined4 *)(param_1 + 0x18),uVar4);
      Select__23CmdRingCustomFinalGoodsFP13CmdRingCustomP9MenuGroupP9MenuGroups
                (*(undefined4 *)(param_1 + 0x1f8),param_1,uVar4,0,1);
      if (*(int *)(*(int *)(param_1 + 0x1f8) + 0x44) == 0) {
        uVar5 = 0;
      }
      else {
        uVar5 = ((ulong)*(ushort *)(*(int *)(param_1 + 0x1f8) + 0xb2) & 0x3ff) >> 2;
      }
      SetButtonReport__13CmdRingCustomFss(param_1,*(undefined2 *)((int)uVar4 + 0x16),uVar5);
      SetChengePCMode__10CmdPCSceneFUc(param_1,0);
      *(undefined1 *)(param_1 + 0x21d) = 6;
      puVar3 = PTR_SelectFinalGoods__13CmdRingCustomFv_0050d740;
      uVar6 = DAT_0050d73c;
      *(undefined4 *)(param_1 + 0x7c) = _6225;
      *(undefined4 *)(param_1 + 0x80) = uVar6;
      *(undefined **)(param_1 + 0x84) = puVar3;
      uVar6 = 2;
    }
    PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),uVar6,0,0);
  }
  return 0;
}

/* JP: 0x0046a010  CmdRingCustom::SelectFinalGoods()   [SelectFinalGoods__13CmdRingCustomFv]  size=0x320 */
undefined8 SelectFinalGoods__13CmdRingCustomFv(int param_1)

{
  ushort uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined *puVar4;
  int iVar5;
  undefined8 uVar6;
  ulong uVar7;
  undefined4 uVar8;
  
  uVar1 = *(ushort *)(*(int *)(param_1 + 0x10) + 0x48);
  iVar2 = *(int *)(*(int *)(param_1 + 0x18) + 0xec);
  if ((uVar1 & 0x6000) == 0) {
    if (((uVar1 & 0x1000) == 0) || (*(short *)(iVar2 + 0x16) < 0)) {
      iVar5 = MoveVertical__9MenuSceneFi(param_1,1);
      if (iVar2 != iVar5) {
        Select__23CmdRingCustomFinalGoodsFP13CmdRingCustomP9MenuGroupP9MenuGroups
                  (*(undefined4 *)(param_1 + 0x1f8),param_1,iVar5,iVar2,1);
        if (*(int *)(*(int *)(param_1 + 0x1f8) + 0x44) == 0) {
          uVar7 = 0;
        }
        else {
          uVar7 = ((ulong)*(ushort *)(*(int *)(param_1 + 0x1f8) + 0xb2) & 0x3ff) >> 2;
        }
        SetButtonReport__13CmdRingCustomFss(param_1,*(undefined2 *)(iVar5 + 0x16),uVar7);
        PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),0,0,0);
      }
    }
    else {
      StartExplain__13CmdRingCustomFv(param_1);
      PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),2,0,0);
    }
  }
  else {
    uVar8 = 3;
    if ((uVar1 & 0x2000) != 0) {
      *(char *)(**(int **)(param_1 + 0x70) + 100) = (char)*(short *)(iVar2 + 0x16);
      UpdateScene__22CmdRingCustomFinalSlotFP13CmdRingCustom(*(undefined4 *)(param_1 + 500),param_1)
      ;
      uVar8 = 0x1004;
    }
    uVar6 = GetPlace__10MenuWindowFss(*(undefined4 *)(param_1 + 500),0,0);
    Select__6CursorFP9MenuPlace(*(undefined4 *)(param_1 + 0x18),uVar6);
    Select__22CmdRingCustomFinalSlotFP13CmdRingCustom(*(undefined4 *)(param_1 + 500),param_1);
    Select__23CmdRingCustomFinalGoodsFP13CmdRingCustomP9MenuGroupP9MenuGroups
              (*(undefined4 *)(param_1 + 0x1f8),param_1,0,iVar2,1);
    UpdateScene__23CmdRingCustomFinalGoodsFP13CmdRingCustoms
              (*(undefined4 *)(param_1 + 0x1f8),param_1,0);
    SetChengePCMode__10CmdPCSceneFUc(param_1,1);
    SetButtonReport__13CmdRingCustomFss(param_1,*(undefined2 *)((int)uVar6 + 0x16),0);
    *(undefined1 *)(param_1 + 0x21d) = 1;
    puVar4 = PTR_SelectFinalSlot__13CmdRingCustomFv_0050d750;
    uVar3 = DAT_0050d74c;
    *(undefined4 *)(param_1 + 0x7c) = _6278;
    *(undefined4 *)(param_1 + 0x80) = uVar3;
    *(undefined **)(param_1 + 0x84) = puVar4;
    PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),uVar8,0,0);
  }
  return 0;
}

/* JP: 0x0046a330  CmdRingCustom::SelectGoods()   [SelectGoods__13CmdRingCustomFv]  size=0x46c */
undefined8 SelectGoods__13CmdRingCustomFv(int param_1)

{
  int *piVar1;
  int iVar2;
  ushort uVar3;
  int iVar4;
  long lVar5;
  undefined8 uVar6;
  undefined1 auStack_150 [268];
  undefined4 uStack_44;
  undefined4 uStack_40;
  int iStack_3c;
  int iStack_38;
  int iStack_34;
  int iStack_30;
  int *piStack_2c;
  int iStack_28;
  int iStack_24;
  undefined2 uStack_1e;
  short sStack_1c;
  undefined2 uStack_1a;
  ushort uStack_18;
  ushort uStack_16;
  undefined2 uStack_14;
  char cStack_11;
  int iStack_10;
  
  piVar1 = *(int **)(param_1 + 0x70);
  iStack_24 = *(int *)(param_1 + 0x10);
  uStack_18 = *(ushort *)(iStack_24 + 0x48);
  iVar2 = *(int *)(*(int *)(param_1 + 0x18) + 0xec);
  uVar3 = uStack_18;
  iStack_34 = iVar2;
  iStack_30 = iVar2;
  piStack_2c = piVar1;
  uStack_16 = uStack_18;
  iStack_10 = param_1;
  if (*(char *)(param_1 + 0x21e) != '\0') {
    *(undefined4 *)(param_1 + 0x204) = 0;
    iStack_28 = *(int *)(param_1 + 0x18);
    *(byte *)(iStack_28 + 0x12) = *(byte *)(iStack_28 + 0x12) & 0xfe | 1;
    if (*(char *)(*(int *)(param_1 + 0x10) + 0x4c) == '\0') {
      *(undefined1 *)(param_1 + 0x21e) = 0;
      PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),3,0,0);
      return 0;
    }
    uVar3 = uStack_18 | 0x2000;
    ResetExpansion__5CmdPCFPUc(piVar1,*piVar1 + 0x5f);
    ResetComboKey__5CmdPCFP8CmdPartycs
              (piVar1,*(undefined4 *)(iStack_10 + 0x5c),1,0xffffffffffffffff);
  }
  if ((uVar3 & 0x6000) == 0) {
    if ((uVar3 & 0x1000) == 0) {
      iVar4 = MoveVertical__9MenuSceneFi(iStack_10,0);
      if (iVar2 != iVar4) {
        Select__18CmdRingCustomGoodsFP13CmdRingCustomP8MenuTextP8MenuTexts
                  (*(undefined4 *)(iStack_10 + 0x1e8),iStack_10,iVar4,iVar2,1);
        uStack_44 = *(undefined4 *)(iStack_10 + 0x70);
        CreateJudgmentRing__5CmdPCFP5JRingUc(uStack_44,*(undefined4 *)(iStack_10 + 0x88),0xff);
        PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(iStack_10 + 0x58),0,0,0);
      }
    }
    else {
      StartExplain__13CmdRingCustomFv(iStack_10);
      PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(iStack_10 + 0x58),2,0,0);
    }
  }
  else {
    uStack_1a = *(undefined2 *)(iVar2 + 0x16);
    iVar4 = *(int *)(*(int *)(iStack_10 + 0x1e8) + 0x2f4);
    iStack_3c = iVar4;
    iStack_38 = iVar4;
    uStack_14 = uStack_1a;
    if ((uVar3 & 0x2000) == 0) {
      uStack_1e = *(undefined2 *)(iVar4 + 0x16);
      cStack_11 = (char)uStack_1e;
      *(byte *)(*piVar1 + 0x58) = *(byte *)(*piVar1 + 0x58) & 0x3f | cStack_11 << 6;
      CreateJudgmentRing__5CmdPCFP5JRingUc(piVar1,*(undefined4 *)(iStack_10 + 0x88),0xff);
      Select__18CmdRingCustomGoodsFP13CmdRingCustomP8MenuTextP8MenuTexts
                (*(undefined4 *)(iStack_10 + 0x1e8),iStack_10,0,iVar2,1);
      iVar2 = *(int *)(*(int *)(iStack_10 + 0x1e8) + 0x2f4);
      *(undefined2 *)(iVar2 + 0x7e) = 1;
      SetCSA__8FontItemFUc(iVar2,1);
      PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(iStack_10 + 0x58),3,0,0);
    }
    else {
      PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(iStack_10 + 0x58),2,0,0);
      if ((((iVar2 != iVar4) && (*(char *)(iStack_10 + 0x21e) == '\0')) &&
          (sStack_1c = *(short *)(iVar2 + 0x16), sStack_1c == 1)) &&
         ((lVar5 = IsExpandRing__5CmdPCFPUc(piVar1,*piVar1 + 0x5f), lVar5 != 0 ||
          (lVar5 = IsSetComboKey__5CmdPCFP8CmdPartycs
                             (piVar1,*(undefined4 *)(iStack_10 + 0x5c),1,0xffffffffffffffff),
          lVar5 != 0)))) {
        uStack_40 = *(undefined4 *)(*(int *)(iStack_10 + 0x24) + 0x58);
        uVar6 = GetRegDat__9RegDatApiFiii(0x11,2,0xffffffffffffffff);
        sprintf(auStack_150,uStack_40,uVar6);
        StartMessage__13CmdRingCustomFPc(iStack_10,auStack_150);
        return 0;
      }
      UpdateScene__18CmdRingCustomGoodsFP13CmdRingCustom
                (*(undefined4 *)(iStack_10 + 0x1e8),iStack_10);
      *(undefined1 *)(iStack_10 + 0x21e) = 0;
    }
    ShiftMenu__13CmdRingCustomFv(iStack_10);
  }
  return 0;
}

/* JP: 0x0046a7a0  CmdRingCustom::SelectCount()   [SelectCount__13CmdRingCustomFv]  size=0x414 */
undefined8 SelectCount__13CmdRingCustomFv(int param_1)

{
  int *piVar1;
  int iVar2;
  ushort uVar3;
  int iVar4;
  long lVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined1 auStack_140 [264];
  undefined4 uStack_38;
  int iStack_34;
  int iStack_30;
  int iStack_2c;
  int iStack_28;
  int *piStack_24;
  int iStack_20;
  undefined2 uStack_1c;
  undefined2 uStack_1a;
  ushort uStack_18;
  ushort uStack_16;
  undefined2 uStack_14;
  byte bStack_11;
  int iStack_10;
  
  piVar1 = *(int **)(param_1 + 0x70);
  uStack_18 = *(ushort *)(*(int *)(param_1 + 0x10) + 0x48);
  iVar2 = *(int *)(*(int *)(param_1 + 0x18) + 0xec);
  uVar3 = uStack_18;
  iStack_2c = iVar2;
  iStack_28 = iVar2;
  piStack_24 = piVar1;
  uStack_16 = uStack_18;
  iStack_10 = param_1;
  if (*(char *)(param_1 + 0x21e) != '\0') {
    *(undefined4 *)(param_1 + 0x204) = 0;
    iStack_20 = *(int *)(param_1 + 0x18);
    *(byte *)(iStack_20 + 0x12) = *(byte *)(iStack_20 + 0x12) & 0xfe | 1;
    if (*(char *)(*(int *)(param_1 + 0x10) + 0x4c) == '\0') {
      *(undefined1 *)(param_1 + 0x21e) = 0;
      PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),3,0,0);
      return 0;
    }
    uVar3 = uStack_18 | 0x2000;
    ResetExpansion__5CmdPCFPUc(piVar1,*piVar1 + 0x5a);
    ResetExpansion__5CmdPCFPUc(piVar1,*piVar1 + 0x5f);
  }
  if ((uVar3 & 0x6000) == 0) {
    iVar4 = MoveVertical__9MenuSceneFi(iStack_10,0);
    if (iVar2 != iVar4) {
      Select__18CmdRingCustomCountFP13CmdRingCustomP9MenuPlaceP9MenuPlaces
                (*(undefined4 *)(iStack_10 + 0x1fc),iStack_10,iVar4,iVar2,1);
      CreateJudgmentRing__5CmdPCFP5JRingUc
                (*(undefined4 *)(iStack_10 + 0x70),*(undefined4 *)(iStack_10 + 0x88),0xff);
      PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(iStack_10 + 0x58),0,0,0);
    }
  }
  else {
    uStack_1a = *(undefined2 *)(iVar2 + 0x16);
    iVar4 = *(int *)(*(int *)(iStack_10 + 0x1fc) + 0x784);
    iStack_34 = iVar4;
    iStack_30 = iVar4;
    uStack_14 = uStack_1a;
    if ((uVar3 & 0x2000) == 0) {
      uStack_1c = *(undefined2 *)(iVar4 + 0x16);
      bStack_11 = (byte)uStack_1c;
      *(byte *)(*piVar1 + 0x58) = *(byte *)(*piVar1 + 0x58) & 199 | (bStack_11 & 7) << 3;
      CreateJudgmentRing__5CmdPCFP5JRingUc(piVar1,*(undefined4 *)(iStack_10 + 0x88),0xff);
      Select__18CmdRingCustomCountFP13CmdRingCustomP9MenuPlaceP9MenuPlaces
                (*(undefined4 *)(iStack_10 + 0x1fc),iStack_10,0,iVar2,1);
      SetClut__18CmdRingCustomCountFs(*(undefined4 *)(iStack_10 + 0x1fc),1);
      PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(iStack_10 + 0x58),3,0,0);
    }
    else {
      PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(iStack_10 + 0x58),2,0,0);
      if (((iVar2 != iVar4) && (*(char *)(iStack_10 + 0x21e) == '\0')) &&
         ((lVar5 = IsExpandRing__5CmdPCFPUc(piVar1,*piVar1 + 0x5a), lVar5 != 0 ||
          (lVar5 = IsExpandRing__5CmdPCFPUc(piVar1,*piVar1 + 0x5f), lVar5 != 0)))) {
        uStack_38 = *(undefined4 *)(*(int *)(iStack_10 + 0x24) + 0x50);
        uVar6 = GetRegDat__9RegDatApiFiii(0x11,1,0xffffffffffffffff);
        uVar7 = GetRegDat__9RegDatApiFiii(0x11,2,0xffffffffffffffff);
        sprintf(auStack_140,uStack_38,uVar6,uVar7);
        StartMessage__13CmdRingCustomFPc(iStack_10,auStack_140);
        return 0;
      }
      UpdateScene__18CmdRingCustomCountFP13CmdRingCustom
                (*(undefined4 *)(iStack_10 + 0x1fc),iStack_10);
      *(undefined1 *)(iStack_10 + 0x21e) = 0;
    }
    UpdateScene__17CmdRingCustomInfoFP13CmdRingCustomsss
              (*(undefined4 *)(iStack_10 + 0x1f0),iStack_10,0,1,0);
    ShiftMenu__13CmdRingCustomFv(iStack_10);
  }
  return 0;
}

/* JP: 0x0046abc0  CmdRingCustom::SelectAutoRing()   [SelectAutoRing__13CmdRingCustomFv]  size=0x5f4 */
undefined8 SelectAutoRing__13CmdRingCustomFv(int param_1)

{
  int *piVar1;
  int iVar2;
  bool bVar3;
  ushort uVar4;
  int iVar5;
  long lVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  char *pcVar9;
  undefined1 auStack_160 [268];
  undefined4 uStack_54;
  undefined4 uStack_50;
  char *pcStack_4c;
  int iStack_48;
  int iStack_44;
  char *pcStack_40;
  int iStack_3c;
  int iStack_38;
  int *piStack_34;
  int iStack_30;
  int iStack_2c;
  int iStack_28;
  int iStack_24;
  int iStack_20;
  undefined2 uStack_1a;
  ushort uStack_18;
  ushort uStack_16;
  ushort uStack_14;
  byte bStack_12;
  char cStack_11;
  int iStack_10;
  
  piVar1 = *(int **)(param_1 + 0x70);
  iStack_20 = *(int *)(param_1 + 0x10);
  uStack_16 = *(ushort *)(iStack_20 + 0x48);
  iStack_24 = *(int *)(param_1 + 0x18);
  iVar2 = *(int *)(iStack_24 + 0xec);
  uVar4 = uStack_16;
  iStack_3c = iVar2;
  iStack_38 = iVar2;
  piStack_34 = piVar1;
  uStack_14 = uStack_16;
  iStack_10 = param_1;
  if (*(char *)(param_1 + 0x21e) != '\0') {
    *(undefined4 *)(param_1 + 0x204) = 0;
    iStack_28 = *(int *)(param_1 + 0x18);
    *(byte *)(iStack_28 + 0x12) = *(byte *)(iStack_28 + 0x12) & 0xfe | 1;
    iStack_2c = *(int *)(param_1 + 0x10);
    if (*(char *)(iStack_2c + 0x4c) == '\0') {
      *(undefined1 *)(param_1 + 0x21e) = 0;
      PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),3,0,0);
      return 0;
    }
    uVar4 = uStack_16 | 0x2000;
    ResetExpansion__5CmdPCFPUc(piVar1,*piVar1 + 0x5a);
    ResetExpansion__5CmdPCFPUc(piVar1,*piVar1 + 0x5f);
    ResetComboKey__5CmdPCFP8CmdPartycs
              (piVar1,*(undefined4 *)(iStack_10 + 0x5c),1,0xffffffffffffffff);
    lVar6 = GetExpansionRingItem__5CmdPCFv(piVar1);
    if (lVar6 != 0) {
      uStack_18 = *(byte *)(*piVar1 + 0x58) & 7;
      cStack_11 = (char)uStack_18;
      *(byte *)(*piVar1 + 0x58) = *(byte *)(*piVar1 + 0x58) & 199 | cStack_11 << 3;
    }
    iVar5 = *piVar1;
    pcStack_40 = (char *)(iVar5 + 0x2f);
    for (pcVar9 = pcStack_40; pcVar9 < (char *)(iVar5 + 0x32); pcVar9 = pcVar9 + 1) {
      if ((-1 < *pcVar9) && (*(char *)(*(int *)(iStack_10 + 0x214) + *pcVar9 * 0xc + 10) != '\0')) {
        *pcVar9 = -1;
      }
    }
  }
  if ((uVar4 & 0x6000) == 0) {
    iVar5 = MoveVertical__9MenuSceneFi(iStack_10,0);
    if (iVar2 != iVar5) {
      Select__21CmdRingCustomAutoRingFP13CmdRingCustomP8MenuTextP8MenuTexts
                (*(undefined4 *)(iStack_10 + 0x200),iStack_10,iVar5,iVar2,1);
      uStack_54 = *(undefined4 *)(iStack_10 + 0x70);
      CreateJudgmentRing__5CmdPCFP5JRingUc(uStack_54,*(undefined4 *)(iStack_10 + 0x88),0xff);
      PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(iStack_10 + 0x58),0,0,0);
    }
  }
  else {
    iStack_30 = *(int *)(iStack_10 + 0x200);
    iVar5 = *(int *)(iStack_30 + 500);
    iStack_48 = iVar5;
    iStack_44 = iVar5;
    if ((uVar4 & 0x2000) == 0) {
      uStack_1a = *(undefined2 *)(iVar5 + 0x16);
      bStack_12 = (byte)uStack_1a;
      *(byte *)(*piVar1 + 0x59) = *(byte *)(*piVar1 + 0x59) & 0xfe | bStack_12 & 1;
      CreateJudgmentRing__5CmdPCFP5JRingUc(piVar1,*(undefined4 *)(iStack_10 + 0x88),0xff);
      Select__21CmdRingCustomAutoRingFP13CmdRingCustomP8MenuTextP8MenuTexts
                (*(undefined4 *)(iStack_10 + 0x200),iStack_10,0,iVar2,1);
      iVar2 = *(int *)(*(int *)(iStack_10 + 0x200) + 500);
      *(undefined2 *)(iVar2 + 0x7e) = 1;
      SetCSA__8FontItemFUc(iVar2,1);
      PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(iStack_10 + 0x58),3,0,0);
    }
    else {
      PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(iStack_10 + 0x58),2,0,0);
      if (((iVar2 != iVar5) && (*(short *)(iVar2 + 0x16) != 0)) &&
         (*(char *)(iStack_10 + 0x21e) == '\0')) {
        bVar3 = false;
        pcStack_4c = (char *)(*piVar1 + 0x2f);
        for (pcVar9 = pcStack_4c; pcVar9 < (char *)(*piVar1 + 0x32); pcVar9 = pcVar9 + 1) {
          if ((-1 < *pcVar9) &&
             (*(char *)(*(int *)(iStack_10 + 0x214) + *pcVar9 * 0xc + 10) != '\0')) {
            bVar3 = true;
            break;
          }
        }
        lVar6 = GetExpansionRingItem__5CmdPCFv(piVar1);
        if (((lVar6 != 0) || (lVar6 = IsExpandRing__5CmdPCFPUc(piVar1,*piVar1 + 0x5a), lVar6 != 0))
           || ((lVar6 = IsExpandRing__5CmdPCFPUc(piVar1,*piVar1 + 0x5f), lVar6 != 0 ||
               ((lVar6 = IsSetComboKey__5CmdPCFP8CmdPartycs
                                   (piVar1,*(undefined4 *)(iStack_10 + 0x5c),1,0xffffffffffffffff),
                lVar6 != 0 || (bVar3)))))) {
          uStack_50 = *(undefined4 *)(*(int *)(iStack_10 + 0x24) + 0x60);
          uVar7 = GetRegDat__9RegDatApiFiii(0x11,1,0xffffffffffffffff);
          uVar8 = GetRegDat__9RegDatApiFiii(0x11,2,0xffffffffffffffff);
          sprintf(auStack_160,uStack_50,uVar7,uVar8);
          StartMessage__13CmdRingCustomFPc(iStack_10,auStack_160);
          return 0;
        }
      }
      UpdateMenu__13CmdRingCustomFv(iStack_10);
      UpdateScene__21CmdRingCustomAutoRingFP13CmdRingCustom
                (*(undefined4 *)(iStack_10 + 0x200),iStack_10);
      *(undefined1 *)(iStack_10 + 0x21e) = 0;
    }
    ShiftMenu__13CmdRingCustomFv(iStack_10);
  }
  return 0;
}

/* JP: 0x0046b1c0  CmdRingCustom::ShiftExplain()   [ShiftExplain__13CmdRingCustomFv]  size=0x224 */
undefined8 ShiftExplain__13CmdRingCustomFv(int param_1)

{
  bool bVar1;
  undefined4 uVar2;
  undefined *puVar3;
  undefined4 uVar4;
  undefined *puVar5;
  int iVar6;
  
  puVar5 = PTR_SelectFinalSlot__13CmdRingCustomFv_0050d780;
  uVar4 = DAT_0050d77c;
  puVar3 = PTR_SelectGoods__13CmdRingCustomFv_0050d770;
  uVar2 = DAT_0050d76c;
  iVar6 = *(int *)(param_1 + 0x1e8);
  if (iVar6 == 0) {
    iVar6 = *(int *)(param_1 + 500);
  }
  if ((*(char *)(iVar6 + 0xa8) == '\x01') || (*(char *)(iVar6 + 0xa8) == '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if (bVar1) {
    if (*(char *)(iVar6 + 0xa8) == '\0') {
      SetExplain__13CmdRingCustomFv(param_1);
      iVar6 = *(int *)(param_1 + 0x68);
      Close__10MenuWindowFUci(iVar6 + 0x58,((ulong)*(byte *)(iVar6 + 0x108) & 0x3f) >> 3,
                      *(undefined4 *)(*(int *)(iVar6 + 0x8c) + 0x14));
      puVar3 = PTR_ExecExplain__13CmdRingCustomFv_0050d760;
      uVar2 = DAT_0050d75c;
      *(undefined4 *)(param_1 + 0x7c) = _6582;
      *(undefined4 *)(param_1 + 0x80) = uVar2;
      *(undefined **)(param_1 + 0x84) = puVar3;
    }
    else {
      if (*(int *)(param_1 + 0x1e8) == 0) {
        if (*(char *)(param_1 + 0x21d) == '\x01') {
          *(undefined4 *)(param_1 + 0x7c) = _6592;
          *(undefined4 *)(param_1 + 0x80) = uVar4;
          *(undefined **)(param_1 + 0x84) = puVar5;
        }
        else {
          FinishScroll__10MenuWindowFv(*(undefined4 *)(param_1 + 0x1f8));
          puVar3 = PTR_SelectFinalGoods__13CmdRingCustomFv_0050d790;
          uVar2 = DAT_0050d78c;
          *(undefined4 *)(param_1 + 0x7c) = _6595;
          *(undefined4 *)(param_1 + 0x80) = uVar2;
          *(undefined **)(param_1 + 0x84) = puVar3;
        }
      }
      else {
        *(undefined4 *)(param_1 + 0x7c) = _6587;
        *(undefined4 *)(param_1 + 0x80) = uVar2;
        *(undefined **)(param_1 + 0x84) = puVar3;
      }
      SetChengePCMode__10CmdPCSceneFUc(param_1,*(ushort *)(param_1 + 0x1e) & 0xff);
    }
  }
  return 0;
}

/* JP: 0x0046b3f0  CmdRingCustom::ExecExplain()   [ExecExplain__13CmdRingCustomFv]  size=0x488 */
undefined8 ExecExplain__13CmdRingCustomFv(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined *puVar3;
  byte bVar4;
  long lVar5;
  
  lVar5 = Exec__10CmdExplainFUs
                    (*(undefined4 *)(param_1 + 0x208),
                     *(undefined2 *)(*(int *)(param_1 + 0x10) + 0x48));
  if ((lVar5 != 0) && ((int)lVar5 == 4)) {
    if ((long)((ulong)*(byte *)(*(int *)(param_1 + 0x208) + 0x525) << 0x3d) < 0) {
      uVar1 = *(undefined4 *)(*(int *)(param_1 + 0x18) + 0xec);
      QuickMove__6CursorFv(*(undefined4 *)(param_1 + 0x18));
      ClearAfter__6CursorFv(*(undefined4 *)(param_1 + 0x18));
      *(byte *)(*(int *)(param_1 + 0x18) + 0x12) =
           *(byte *)(*(int *)(param_1 + 0x18) + 0x12) & 0xfe | 1;
      if (*(int *)(param_1 + 0x1e8) == 0) {
        iVar2 = *(int *)(param_1 + 500);
        Open__10MenuWindowFUci(iVar2,*(byte *)(iVar2 + 0xb0) & 7,
                        *(undefined4 *)(*(int *)(iVar2 + 0x34) + 0x10));
        iVar2 = *(int *)(param_1 + 0x1f8);
        Open__10MenuWindowFUci(iVar2,*(byte *)(iVar2 + 0xb0) & 7,
                        *(undefined4 *)(*(int *)(iVar2 + 0x34) + 0x10));
        if (*(char *)(param_1 + 0x21d) == '\x01') {
          Select__22CmdRingCustomFinalSlotFP13CmdRingCustom(*(undefined4 *)(param_1 + 500),param_1);
        }
        else {
          Select__23CmdRingCustomFinalGoodsFP13CmdRingCustomP9MenuGroupP9MenuGroups
                    (*(undefined4 *)(param_1 + 0x1f8),param_1,uVar1,0,1);
        }
      }
      else {
        iVar2 = *(int *)(param_1 + 0x1e8);
        Open__10MenuWindowFUci(iVar2,*(byte *)(iVar2 + 0xb0) & 7,
                        *(undefined4 *)(*(int *)(iVar2 + 0x34) + 0x10));
        Select__18CmdRingCustomGoodsFP13CmdRingCustomP8MenuTextP8MenuTexts
                  (*(undefined4 *)(param_1 + 0x1e8),param_1,uVar1,0,1);
      }
      iVar2 = *(int *)(param_1 + 0x78);
      Open__10MenuWindowFUci(iVar2 + 0x58,*(byte *)(iVar2 + 0x108) & 7,
                      *(undefined4 *)(*(int *)(iVar2 + 0x8c) + 0x10));
      iVar2 = *(int *)(param_1 + 0x1e0);
      Open__10MenuWindowFUci(iVar2 + 0x58,*(byte *)(iVar2 + 0x108) & 7,
                      *(undefined4 *)(*(int *)(iVar2 + 0x8c) + 0x10));
      iVar2 = *(int *)(param_1 + 0x1e4);
      Open__10MenuWindowFUci(iVar2,*(byte *)(iVar2 + 0xb0) & 7,
                      *(undefined4 *)(*(int *)(iVar2 + 0x34) + 0x10));
      Open__15CmdButtonReportFv(*(undefined4 *)(param_1 + 0x68));
      (**(code **)(*(int *)(*(int *)(param_1 + 0x208) + 8) + 0xc))();
      puVar3 = PTR_ShiftExplain__13CmdRingCustomFv_0050d7a0;
      uVar1 = DAT_0050d79c;
      *(undefined4 *)(param_1 + 0x7c) = _6629;
      *(undefined4 *)(param_1 + 0x80) = uVar1;
      *(undefined **)(param_1 + 0x84) = puVar3;
    }
    else {
      uVar1 = *(undefined4 *)(*(int *)(param_1 + 0x18) + 0xec);
      bVar4 = *(byte *)(*(int *)(param_1 + 0x208) + 0x524) >> 4;
      MoveCursor__6CursorFi(*(undefined4 *)(param_1 + 0x18),bVar4);
      iVar2 = *(int *)(*(int *)(param_1 + 0x18) + 0xec);
      if (*(short *)(iVar2 + 0x16) < 0) {
        MoveCursor__6CursorFi(*(undefined4 *)(param_1 + 0x18),bVar4);
        iVar2 = *(int *)(*(int *)(param_1 + 0x18) + 0xec);
      }
      SetExplain__13CmdRingCustomFv(param_1);
      if (*(int *)(param_1 + 0x1e8) == 0) {
        Select__23CmdRingCustomFinalGoodsFP13CmdRingCustomP9MenuGroupP9MenuGroups
                  (*(undefined4 *)(param_1 + 0x1f8),param_1,iVar2,uVar1,0);
      }
      else {
        Select__18CmdRingCustomGoodsFP13CmdRingCustomP8MenuTextP8MenuTexts
                  (*(undefined4 *)(param_1 + 0x1e8),param_1,iVar2,uVar1,0);
        CreateJudgmentRing__5CmdPCFP5JRingUc
                  (*(undefined4 *)(param_1 + 0x70),*(undefined4 *)(param_1 + 0x88),0xff);
      }
    }
  }
  return 0;
}
