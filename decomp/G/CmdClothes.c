/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdClothes   functions: 13
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdClothes.md).
 */

/* JP: 0x00458020  CmdClothes::TailorEvent(int, void*)   [TailorEvent__10CmdClothesFiPv]  size=0x48 */
void TailorEvent__10CmdClothesFiPv(int param_1,undefined4 param_2)

{
  if (param_1 == 3) {
    RestoreTailor__10CmdClothesFv(param_2);
  }
  return;
}

/* JP: 0x00458070  CmdClothes::CmdClothes()   [__ct__10CmdClothesFv]  size=0x4c */
int __ct__10CmdClothesFv(int param_1)

{
  __ct__15CmdPrivateSceneFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__10CmdClothes;
  *(undefined4 *)(param_1 + 0x6c) = 0;
  *(undefined4 *)(param_1 + 0x70) = 0;
  return param_1;
}

/* JP: 0x004580c0  CmdClothes::~CmdClothes()   [__dt__10CmdClothesFv]  size=0x74 */
int __dt__10CmdClothesFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__10CmdClothes;
    __dt__15CmdPrivateSceneFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x00458140  CmdClothes::GetReady()   [GetReady__10CmdClothesFv]  size=0x144 */
undefined4 GetReady__10CmdClothesFv(int param_1)

{
  *(undefined4 *)(param_1 + 0x68) = sm_pSound__7MenuObj;
  *(int *)(param_1 + 0x18) = *(int *)(param_1 + 0x10) + 0x3a0;
  SetTitle__11CmdTitleLogFPUci
            (*(undefined4 *)(*(int *)(param_1 + 0x58) + 0x60),
             *(undefined4 *)(*(int *)(param_1 + 0x54) + 0x10),0x12);
  Open__11CmdTitleLogFv(*(undefined4 *)(*(int *)(param_1 + 0x58) + 0x60));
  UpdateClothes__10CmdClothesFv(param_1);
  *(byte *)(param_1 + 0x23) = *(byte *)(param_1 + 0x23) & 0xdf | 0x20;
  return 1;
}

/* JP: 0x00458290  CmdClothes::Run()   [Run__10CmdClothesFv]  size=0x68 */
undefined4 Run__10CmdClothesFv(int param_1)

{
  undefined4 uVar1;
  long lVar2;
  
  lVar2 = __ptmf_test(param_1 + 0x5c);
  if ((lVar2 == 0) || (lVar2 = __ptmf_scall(param_1), lVar2 == 0)) {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}

/* JP: 0x00458300  CmdClothes::DelayDelete()   [DelayDelete__10CmdClothesFv]  size=0x28 */
void DelayDelete__10CmdClothesFv(undefined4 param_1)

{
  SafeDelayDelete__10CmdClothesFv(param_1);
  return;
}

/* JP: 0x00458330  CmdClothes::SafeDelayDelete()   [SafeDelayDelete__10CmdClothesFv]  size=0x68 */
void SafeDelayDelete__10CmdClothesFv(int param_1)

{
  (**(code **)(*(int *)(*(int *)(param_1 + 0x6c) + 8) + 0xc))();
  *(undefined4 *)(param_1 + 0x6c) = 0;
  (**(code **)(*(int *)(*(int *)(param_1 + 0x70) + 8) + 0xc))();
  *(undefined4 *)(param_1 + 0x70) = 0;
  DelayDelete__17DelayDeleteObjectFv(param_1);
  return;
}

/* JP: 0x004583a0  CmdClothes::Close()   [Close__10CmdClothesFv]  size=0x7c */
void Close__10CmdClothesFv(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x6c);
  Close__10MenuWindowFUci(iVar1,((ulong)*(byte *)(iVar1 + 0xb0) & 0x3f) >> 3,
                  *(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x14));
  iVar1 = *(int *)(param_1 + 0x70);
  Close__10MenuWindowFUci(iVar1 + 0x58,((ulong)*(byte *)(iVar1 + 0x108) & 0x3f) >> 3,
                  *(undefined4 *)(*(int *)(iVar1 + 0x8c) + 0x14));
  return;
}

/* JP: 0x00458420  CmdClothes::RestoreTailor()   [RestoreTailor__10CmdClothesFv]  size=0x140 */
void RestoreTailor__10CmdClothesFv(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined *puVar3;
  
  uVar1 = *(undefined4 *)(param_1 + 0x10);
  CreateBackGround__7CmdMenuFs(uVar1,8);
  iVar2 = *(int *)(*(int *)(param_1 + 0x58) + 100);
  Open__10MenuWindowFUci(iVar2 + 0x58,*(byte *)(iVar2 + 0x108) & 7,
                  *(undefined4 *)(*(int *)(iVar2 + 0x8c) + 0x10));
  Open__11CmdTitleLogFv(*(undefined4 *)(*(int *)(param_1 + 0x58) + 0x60));
  UpdateMenu__10CmdPrivateFs(*(undefined4 *)(param_1 + 0x58),1);
  UpdatePCInfo__10CmdPCSceneFsP11CmdPCStatus(*(undefined4 *)(param_1 + 0x58),1,0);
  UpdateClothes__10CmdClothesFv(param_1);
  CreateLight__7CmdMenuFv(uVar1);
  puVar3 = PTR_FinishTailor__10CmdClothesFv_0050d4b0;
  uVar1 = DAT_0050d4ac;
  *(undefined4 *)(param_1 + 0x5c) = _5898;
  *(undefined4 *)(param_1 + 0x60) = uVar1;
  *(undefined **)(param_1 + 100) = puVar3;
  return;
}

/* JP: 0x00458560  CmdClothes::UpdateClothes()   [UpdateClothes__10CmdClothesFv]  size=0x18c */
void UpdateClothes__10CmdClothesFv(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  long lVar3;
  
  lVar3 = __nw__FUi(0x254);
  uVar2 = 0;
  if (lVar3 != 0) {
    uVar2 = __ct__14CmdClothesSlotFv(lVar3);
  }
  *(undefined4 *)(param_1 + 0x6c) = uVar2;
  CreateScene__14CmdClothesSlotFP10CmdClothes(*(undefined4 *)(param_1 + 0x6c),param_1);
  UpdateScene__14CmdClothesSlotFP10CmdClothes(*(undefined4 *)(param_1 + 0x6c),param_1);
  lVar3 = __nw__FUi(0x1c8);
  uVar2 = 0;
  if (lVar3 != 0) {
    uVar2 = __ct__11CmdSubTitleFv(lVar3);
  }
  *(undefined4 *)(param_1 + 0x70) = uVar2;
  Initialize__9MenuSceneFPUcP9BufMemory(*(undefined4 *)(param_1 + 0x70),
                  *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x58) + 0x54) + 100),0);
  Create__11CmdSubTitleFi(*(undefined4 *)(param_1 + 0x70),1);
  Reset__11CmdSubTitleFv(*(undefined4 *)(param_1 + 0x70));
  SetTitle__11CmdSubTitleFii(*(undefined4 *)(param_1 + 0x70),0,0);
  iVar1 = *(int *)(param_1 + 0x6c);
  Open__10MenuWindowFUci(iVar1,*(byte *)(iVar1 + 0xb0) & 7,*(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x10));
  iVar1 = *(int *)(param_1 + 0x70);
  Open__10MenuWindowFUci(iVar1 + 0x58,*(byte *)(iVar1 + 0x108) & 7,
                  *(undefined4 *)(*(int *)(iVar1 + 0x8c) + 0x10));
  return;
}

/* JP: 0x004586f0  CmdClothes::ReadyScene()   [ReadyScene__10CmdClothesFv]  size=0x2f8 */
undefined4 ReadyScene__10CmdClothesFv(int param_1)

{
  int iVar1;
  int iVar2;
  undefined *puVar3;
  undefined4 uVar4;
  long lVar5;
  
  iVar1 = *(int *)(param_1 + 0x10);
  lVar5 = __nw__FUi(0x170);
  uVar4 = 0;
  if (lVar5 != 0) {
    uVar4 = __ct__6tailorFv(lVar5);
  }
  *(undefined4 *)(param_1 + 0x74) = uVar4;
  initialize__6tailorFPFiPv_vPvi(*(undefined4 *)(param_1 + 0x74),0x458020,param_1,1);
  SetChengePCMode__10CmdPCSceneFUc(*(undefined4 *)(param_1 + 0x58),0);
  iVar2 = *(int *)(iVar1 + 0xb0);
  Close__10MenuWindowFUci(iVar2 + 0x5c,((ulong)*(byte *)(iVar2 + 0x10c) & 0x3f) >> 3,
                  *(undefined4 *)(*(int *)(iVar2 + 0x90) + 0x14));
  iVar2 = *(int *)(*(int *)(param_1 + 0x58) + 0x78);
  Close__10MenuWindowFUci(iVar2 + 0x58,((ulong)*(byte *)(iVar2 + 0x108) & 0x3f) >> 3,
                  *(undefined4 *)(*(int *)(iVar2 + 0x8c) + 0x14));
  iVar2 = *(int *)(*(int *)(param_1 + 0x58) + 0x8c);
  Close__10MenuWindowFUci(iVar2,((ulong)*(byte *)(iVar2 + 0xb0) & 0x3f) >> 3,
                  *(undefined4 *)(*(int *)(iVar2 + 0x34) + 0x14));
  Close__10CmdElementFv(*(undefined4 *)(*(int *)(param_1 + 0x58) + 0x6c));
  iVar2 = *(int *)(*(int *)(param_1 + 0x58) + 100);
  Close__10MenuWindowFUci(iVar2 + 0x58,((ulong)*(byte *)(iVar2 + 0x108) & 0x3f) >> 3,
                  *(undefined4 *)(*(int *)(iVar2 + 0x8c) + 0x14));
  iVar2 = *(int *)(*(int *)(param_1 + 0x58) + 0x60);
  Close__10MenuWindowFUci(iVar2 + 0x58,((ulong)*(byte *)(iVar2 + 0x108) & 0x3f) >> 3,
                  *(undefined4 *)(*(int *)(iVar2 + 0x8c) + 0x14));
  iVar2 = *(int *)(param_1 + 0x70);
  Close__10MenuWindowFUci(iVar2 + 0x58,((ulong)*(byte *)(iVar2 + 0x108) & 0x3f) >> 3,
                  *(undefined4 *)(*(int *)(iVar2 + 0x8c) + 0x14));
  iVar2 = *(int *)(param_1 + 0x6c);
  Close__10MenuWindowFUci(iVar2,((ulong)*(byte *)(iVar2 + 0xb0) & 0x3f) >> 3,
                  *(undefined4 *)(*(int *)(iVar2 + 0x34) + 0x14));
  ReleaseLight__7CmdMenuFv(iVar1);
  Shutdown__6CursorFv(*(undefined4 *)(param_1 + 0x18));
  puVar3 = PTR_ReadyTailor__10CmdClothesFv_0050d4c0;
  uVar4 = DAT_0050d4bc;
  *(undefined4 *)(param_1 + 0x5c) = _5953;
  *(undefined4 *)(param_1 + 0x60) = uVar4;
  *(undefined **)(param_1 + 100) = puVar3;
  return 1;
}

/* JP: 0x004589f0  CmdClothes::ReadyTailor()   [ReadyTailor__10CmdClothesFv]  size=0x144 */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 ReadyTailor__10CmdClothesFv(int param_1)

{
  int iVar1;
  bool bVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
  if ((*(char *)(*(int *)(param_1 + 0x6c) + 0xa8) == '\x01') ||
     (*(char *)(*(int *)(param_1 + 0x6c) + 0xa8) == '\0')) {
    bVar2 = true;
  }
  else {
    bVar2 = false;
  }
  if (bVar2) {
    DestroyBackGround__7CmdMenuFs(*(undefined4 *)(param_1 + 0x10),0);
    (**(code **)(*(int *)(*(int *)(param_1 + 0x6c) + 8) + 0xc))();
    *(undefined4 *)(param_1 + 0x6c) = 0;
    (**(code **)(*(int *)(*(int *)(param_1 + 0x70) + 8) + 0xc))();
    *(undefined4 *)(param_1 + 0x70) = 0;
    iVar1 = *(int *)(param_1 + 0x58);
    (**(code **)(*(int *)(*(int *)(iVar1 + 0x78) + 8) + 0xc))();
    *(undefined4 *)(iVar1 + 0x78) = 0;
    start__6tailorFv(*(undefined4 *)(param_1 + 0x74));
    uVar4 = uRam004236d0;
    uVar3 = uRam004236cc;
    *(undefined4 *)(param_1 + 0x5c) = ___ptmf_null;
    *(undefined4 *)(param_1 + 0x60) = uVar3;
    *(undefined4 *)(param_1 + 100) = uVar4;
  }
  return 0;
}

/* JP: 0x00458b40  CmdClothes::FinishTailor()   [FinishTailor__10CmdClothesFv]  size=0xa8 */
bool FinishTailor__10CmdClothesFv(int param_1)

{
  bool bVar1;
  
  if ((*(char *)(*(int *)(param_1 + 0x6c) + 0xa8) == '\x01') ||
     (*(char *)(*(int *)(param_1 + 0x6c) + 0xa8) == '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if (bVar1) {
    Restore__6CursorFv(*(undefined4 *)(param_1 + 0x18));
  }
  return bVar1;
}
