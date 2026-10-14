/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdGraveyard   functions: 8
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdGraveyard.md).
 */

/* JP: 0x0045e680  CmdGraveyard::CmdGraveyard()   [__ct__12CmdGraveyardFv]  size=0x94 */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __ct__12CmdGraveyardFv(int param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  __ct__9MenuSceneFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__12CmdGraveyard;
  uVar2 = uRam004236d0;
  uVar1 = uRam004236cc;
  *(undefined4 *)(param_1 + 0x58) = ___ptmf_null;
  *(undefined4 *)(param_1 + 0x5c) = uVar1;
  *(undefined4 *)(param_1 + 0x60) = uVar2;
  __ct__16CmdGraveyardMenuFv(param_1 + 0x6c);
  __ct__12SmoothFilterFv(param_1 + 0x2e0);
  *(undefined4 *)(param_1 + 0x318) = 0x3f000000;
  return param_1;
}

/* JP: 0x0045e720  CmdGraveyard::~CmdGraveyard()   [__dt__12CmdGraveyardFv]  size=0x9c */
int __dt__12CmdGraveyardFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__12CmdGraveyard;
    __dt__12SmoothFilterFv(param_1 + 0x2e0,0xffffffffffffffff);
    __dt__16CmdGraveyardMenuFv(param_1 + 0x6c,0xffffffffffffffff);
    __dt__9MenuSceneFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x0045e7c0  CmdGraveyard::GetReady()   [GetReady__12CmdGraveyardFv]  size=0xb8 */
undefined4 GetReady__12CmdGraveyardFv(int param_1)

{
  undefined4 uVar1;
  undefined *puVar2;
  
  *(int *)(param_1 + 0x68) = *(int *)(param_1 + 0x10) + 0x780;
  *(int *)(param_1 + 0x18) = *(int *)(param_1 + 0x10) + 0x3a0;
  CreateScene__16CmdGraveyardMenuFP12CmdGraveyard(param_1 + 0x6c,param_1);
  puVar2 = PTR_Enter__12CmdGraveyardFv_0050d560;
  uVar1 = DAT_0050d55c;
  *(undefined4 *)(param_1 + 0x58) = _4909;
  *(undefined4 *)(param_1 + 0x5c) = uVar1;
  *(undefined **)(param_1 + 0x60) = puVar2;
  return 1;
}

/* JP: 0x0045e880  CmdGraveyard::Run()   [Run__12CmdGraveyardFv]  size=0x5c */
undefined8 Run__12CmdGraveyardFv(int param_1)

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

/* JP: 0x0045e8e0  CmdGraveyard::Enter()   [Enter__12CmdGraveyardFv]  size=0x23c */
undefined8 Enter__12CmdGraveyardFv(int param_1)

{
  bool bVar1;
  undefined4 uVar2;
  undefined *puVar3;
  undefined1 uVar4;
  
  if (*(char *)(param_1 + 0x21) == '\0') {
    Open__10MenuWindowFUci(param_1 + 0x6c,*(byte *)(param_1 + 0x11c) & 7,
                    *(undefined4 *)(*(int *)(param_1 + 0xa0) + 0x10));
    Select__6CursorFP9MenuPlace(*(undefined4 *)(param_1 + 0x18),param_1 + 0x260);
    SetCSA__8FontItemFUc(param_1 + 0x260,1);
    SetTitle__11CmdTitleLogFPUci
              (*(undefined4 *)(param_1 + 0x68),*(undefined4 *)(*(int *)(param_1 + 0x54) + 0x10),3);
    Open__11CmdTitleLogFv(*(undefined4 *)(param_1 + 0x68));
    SetExplanation__7CmdNoteFPCce
              (*(int *)(param_1 + 0x10) + 0x4e0,*(undefined4 *)(*(int *)(param_1 + 0x28) + 0x14));
    uVar4 = CreateBackGround__7CmdMenuFs(*(undefined4 *)(param_1 + 0x10),8);
    *(undefined1 *)(param_1 + 0x20) = uVar4;
    *(char *)(param_1 + 0x21) = *(char *)(param_1 + 0x21) + '\x01';
  }
  else if (*(char *)(param_1 + 0x21) == '\x01') {
    if ((*(char *)(param_1 + 0x114) == '\x01') || (*(char *)(param_1 + 0x114) == '\0')) {
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
      puVar3 = PTR_SelectMenu__12CmdGraveyardFv_0050d570;
      uVar2 = DAT_0050d56c;
      *(undefined4 *)(param_1 + 0x58) = _4943;
      *(undefined4 *)(param_1 + 0x5c) = uVar2;
      *(undefined **)(param_1 + 0x60) = puVar3;
      *(undefined1 *)(param_1 + 0x21) = 0;
    }
  }
  return 0;
}

/* JP: 0x0045eb20  CmdGraveyard::Exit()   [Exit__12CmdGraveyardFv]  size=0x19c */
undefined8 Exit__12CmdGraveyardFv(int param_1)

{
  int iVar1;
  bool bVar2;
  
  if (*(char *)(param_1 + 0x21) == '\0') {
    (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x14) + 0x28))(*(int *)(param_1 + 0x10),0,0,8);
    Close__10MenuWindowFUci(param_1 + 0x6c,((ulong)*(byte *)(param_1 + 0x11c) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(param_1 + 0xa0) + 0x14));
    iVar1 = *(int *)(param_1 + 0x68);
    Close__10MenuWindowFUci(iVar1 + 0x58,((ulong)*(byte *)(iVar1 + 0x108) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar1 + 0x8c) + 0x14));
    Leave__6CursorFv(*(undefined4 *)(param_1 + 0x18));
    *(char *)(param_1 + 0x21) = *(char *)(param_1 + 0x21) + '\x01';
  }
  else if (*(char *)(param_1 + 0x21) == '\x01') {
    if ((*(char *)(param_1 + 0x114) == '\x01') || (*(char *)(param_1 + 0x114) == '\0')) {
      bVar2 = true;
    }
    else {
      bVar2 = false;
    }
    if (bVar2) {
      ReleaseOT__7MenuObjFv(param_1 + 0x6c);
      (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x14) + 0x24))(*(int *)(param_1 + 0x10),0);
      DestroyScene__4MenuFP9MenuSceneb(*(undefined4 *)(param_1 + 0x10),param_1,1);
    }
  }
  return 0;
}

/* JP: 0x0045ecc0  CmdGraveyard::SelectMenu()   [SelectMenu__12CmdGraveyardFv]  size=0x230 */
undefined8 SelectMenu__12CmdGraveyardFv(int param_1)

{
  ushort uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined *puVar4;
  undefined4 uVar5;
  undefined *puVar6;
  undefined4 uVar7;
  undefined *puVar8;
  
  puVar8 = PTR_Exit__12CmdGraveyardFv_0050d5a0;
  uVar7 = DAT_0050d59c;
  puVar6 = PTR_JumpGraveyard__12CmdGraveyardFv_0050d590;
  uVar5 = DAT_0050d58c;
  puVar4 = PTR_Exit__12CmdGraveyardFv_0050d580;
  uVar3 = DAT_0050d57c;
  iVar2 = *(int *)(*(int *)(param_1 + 0x18) + 0xec);
  uVar1 = *(ushort *)(*(int *)(param_1 + 0x10) + 0x48);
  if ((uVar1 & 0x2000) == 0) {
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
        SetCSA__8FontItemFUc(iVar2,0);
        SetCSA__8FontItemFUc(*(undefined4 *)(*(int *)(param_1 + 0x18) + 0xec),1);
      }
    }
    else {
      *(undefined4 *)(param_1 + 0x58) = _5005;
      *(undefined4 *)(param_1 + 0x5c) = uVar7;
      *(undefined **)(param_1 + 0x60) = puVar8;
    }
  }
  else if (*(short *)(iVar2 + 0x16) == 0) {
    *(undefined4 *)(param_1 + 0x58) = _5000;
    *(undefined4 *)(param_1 + 0x5c) = uVar5;
    *(undefined **)(param_1 + 0x60) = puVar6;
    LayerSetUp__12SmoothFilterFi(param_1 + 0x2e0,0xe);
  }
  else {
    *(undefined4 *)(param_1 + 0x58) = _4997;
    *(undefined4 *)(param_1 + 0x5c) = uVar3;
    *(undefined **)(param_1 + 0x60) = puVar4;
  }
  return 0;
}

/* JP: 0x0045eef0  CmdGraveyard::JumpGraveyard()   [JumpGraveyard__12CmdGraveyardFv]  size=0x168 */
undefined8 JumpGraveyard__12CmdGraveyardFv(int param_1)

{
  int iVar1;
  float fVar2;
  
  FilterLevel__12SmoothFilterFf(*(undefined4 *)(param_1 + 0x318),param_1 + 0x2e0);
  fVar2 = *(float *)(param_1 + 0x318) - 0.005;
  *(float *)(param_1 + 0x318) = fVar2;
  if (fVar2 <= 0.1) {
    MapJump__7CmdMenuFs(*(undefined4 *)(param_1 + 0x10),1);
    ReleaseOT__7MenuObjFv(param_1 + 0x6c);
    iVar1 = *(int *)(*(int *)(param_1 + 0x10) + 0xb0);
    RemoveObj__12MenuObjTableFP7MenuObj(*(int *)(iVar1 + 0x58) + 0x2c,iVar1 + 0x5c);
    iVar1 = GetScene__4MenuFs(*(undefined4 *)(param_1 + 0x10),0);
    ReleaseOT__7MenuObjFv(*(undefined4 *)(iVar1 + 100));
    LayerRelease__12SmoothFilterFv(param_1 + 0x2e0);
    (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x14) + 0x24))(*(int *)(param_1 + 0x10),0x17);
    DestroyScene__4MenuFP9MenuSceneb(*(undefined4 *)(param_1 + 0x10),param_1,1);
  }
  return 0;
}
