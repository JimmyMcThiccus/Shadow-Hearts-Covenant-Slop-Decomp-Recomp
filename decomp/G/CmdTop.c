/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdTop   functions: 15
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdTop.md).
 */

/* JP: 0x00438790  CmdTop::CmdTop()   [__ct__6CmdTopFv]  size=0x94 */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __ct__6CmdTopFv(int param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  __ct__9MenuSceneFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__6CmdTop;
  uVar2 = uRam004236d0;
  uVar1 = uRam004236cc;
  *(undefined4 *)(param_1 + 0x58) = ___ptmf_null;
  *(undefined4 *)(param_1 + 0x5c) = uVar1;
  *(undefined4 *)(param_1 + 0x60) = uVar2;
  *(undefined4 *)(param_1 + 100) = 0;
  *(undefined4 *)(param_1 + 0x68) = 0;
  *(undefined4 *)(param_1 + 0x6c) = 0;
  *(undefined4 *)(param_1 + 0x70) = 0;
  *(undefined4 *)(param_1 + 0x74) = 0;
  *(undefined4 *)(param_1 + 0x78) = 0;
  return param_1;
}

/* JP: 0x00438830  CmdTop::~CmdTop()   [__dt__6CmdTopFv]  size=0x130 */
int __dt__6CmdTopFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__6CmdTop;
    if (*(int *)(param_1 + 100) != 0) {
      (**(code **)(*(int *)(*(int *)(param_1 + 100) + 8) + 0xc))();
    }
    if (*(int *)(param_1 + 0x70) != 0) {
      (**(code **)(*(int *)(*(int *)(param_1 + 0x70) + 8) + 0xc))();
    }
    if (*(int *)(param_1 + 0x6c) != 0) {
      (**(code **)(*(int *)(*(int *)(param_1 + 0x6c) + 8) + 0xc))();
    }
    if (*(int *)(param_1 + 0x74) != 0) {
      ReleaseOT__7MenuObjFv(*(int *)(param_1 + 0x74) + 0x58);
      (**(code **)(*(int *)(*(int *)(param_1 + 0x74) + 8) + 0xc))();
    }
    __dt__9MenuSceneFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x00438960  CmdTop::GetReady()   [GetReady__6CmdTopFv]  size=0x394 */
undefined4 GetReady__6CmdTopFv(int param_1)

{
  short sVar1;
  int iVar2;
  undefined *puVar3;
  undefined4 uVar4;
  long lVar5;
  undefined8 uVar6;
  
  iVar2 = *(int *)(param_1 + 0x10);
  *(int *)(param_1 + 0x7c) = iVar2 + 0x4e0;
  *(int *)(param_1 + 0x80) = iVar2 + 0x780;
  *(undefined4 *)(param_1 + 0x84) = sm_pSound__7MenuObj;
  *(int *)(param_1 + 0x18) = iVar2 + 0x3a0;
  sVar1 = *(short *)(iVar2 + 0x44);
  if (*(int *)(param_1 + 100) == 0) {
    lVar5 = __nw__FUi(0x5f4);
    uVar4 = 0;
    if (lVar5 != 0) {
      uVar4 = __ct__10CmdTopMenuFv(lVar5);
    }
    *(undefined4 *)(param_1 + 100) = uVar4;
    CreateScene__10CmdTopMenuFP6CmdTop(*(undefined4 *)(param_1 + 100),param_1);
  }
  if (*(int *)(param_1 + 0x6c) == 0) {
    lVar5 = __nw__FUi(0x348);
    uVar4 = 0;
    if (lVar5 != 0) {
      uVar4 = __ct__14CmdTopPlayInfoFv(lVar5);
    }
    *(undefined4 *)(param_1 + 0x6c) = uVar4;
    CreateScene__14CmdTopPlayInfoFP6CmdTop(*(undefined4 *)(param_1 + 0x6c),param_1);
  }
  if (*(int *)(param_1 + 0x70) == 0) {
    lVar5 = __nw__FUi(0x74a0);
    uVar4 = 0;
    if (lVar5 != 0) {
      uVar4 = __ct__8CmdTopPCFv(lVar5);
    }
    *(undefined4 *)(param_1 + 0x70) = uVar4;
    CreateScene__8CmdTopPCFP6CmdTop(*(undefined4 *)(param_1 + 0x70),param_1);
  }
  if (*(int *)(param_1 + 0x74) == 0) {
    lVar5 = __nw__FUi(0x3f0);
    uVar4 = 0;
    if (lVar5 != 0) {
      uVar4 = __ct__13CmdSoulEnergyFv(lVar5);
    }
    *(undefined4 *)(param_1 + 0x74) = uVar4;
    Initialize__9MenuSceneFPUcP9BufMemory(*(undefined4 *)(param_1 + 0x74),
                    *(undefined4 *)(*(int *)(sm_pCmdMenu__7MenuObj + 0x54) + 0x7c),0);
    *(undefined4 *)(*(int *)(param_1 + 0x74) + 0x10) = *(undefined4 *)(param_1 + 0x10);
    SetMeter__13CmdSoulEnergyFUi(*(undefined4 *)(param_1 + 0x74),
                    **(undefined2 **)(*(int *)(param_1 + 0x10) + 0xbc));
  }
  UpdateScene__10CmdTopMenuFP6CmdTops(*(undefined4 *)(param_1 + 100),param_1,sVar1 / 0xc);
  uVar6 = GetPlace__10MenuWindowFs(*(undefined4 *)(param_1 + 100),sVar1);
  Select__9CmdWindowFP7CmdNoteP9MenuSceneP8MenuTextP8MenuText
            (*(undefined4 *)(param_1 + 100),*(undefined4 *)(param_1 + 0x7c),param_1,uVar6,0);
  *(int *)(param_1 + 0x8c) = (int)uVar6;
  puVar3 = PTR_Enter__6CmdTopFv_0050d108;
  uVar4 = DAT_0050d104;
  *(undefined4 *)(param_1 + 0x58) = _5439;
  *(undefined4 *)(param_1 + 0x5c) = uVar4;
  *(undefined **)(param_1 + 0x60) = puVar3;
  return 1;
}

/* JP: 0x00438d00  CmdTop::Run()   [Run__6CmdTopFv]  size=0x84 */
undefined8 Run__6CmdTopFv(int param_1)

{
  long lVar1;
  
  do {
    lVar1 = __ptmf_test(param_1 + 0x58);
    if (lVar1 == 0) break;
    lVar1 = __ptmf_scall(param_1);
  } while (lVar1 != 0);
  if (*(int *)(param_1 + 0x6c) != 0) {
    UpdateScene__14CmdTopPlayInfoFP6CmdTop(*(undefined4 *)(param_1 + 0x6c),param_1);
  }
  return 0;
}

/* JP: 0x00438d90  CmdTop::Shutdown()   [Shutdown__6CmdTopFv]  size=0x4c */
void Shutdown__6CmdTopFv(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 100);
  Close__10MenuWindowFUci(iVar1,((ulong)*(byte *)(iVar1 + 0xb0) & 0x3f) >> 3,
                  *(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x14));
  return;
}

/* JP: 0x00438de0  CmdTop::Restore()   [Restore__6CmdTopFv]  size=0x48 */
void Restore__6CmdTopFv(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 100);
  Open__10MenuWindowFUci(iVar1,*(byte *)(iVar1 + 0xb0) & 7,*(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x10));
  return;
}

/* JP: 0x00438e30  CmdTop::Enter()   [Enter__6CmdTopFv]  size=0x3c8 */
undefined8 Enter__6CmdTopFv(int param_1)

{
  int iVar1;
  bool bVar2;
  undefined4 uVar3;
  undefined *puVar4;
  undefined1 uVar5;
  
  if (*(char *)(param_1 + 0x21) == '\0') {
    if (*(char *)(*(int *)(param_1 + 100) + 0xa8) == '\0') {
      iVar1 = *(int *)(param_1 + 100);
      Open__10MenuWindowFUci(iVar1,*(byte *)(iVar1 + 0xb0) & 7,
                      *(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x10));
    }
    else {
      iVar1 = *(int *)(param_1 + 100);
      *(byte *)(iVar1 + 0x586) = *(byte *)(iVar1 + 0x586) & 0xfe | 1;
      *(byte *)(*(int *)(iVar1 + 0x44) + 0x12) = *(byte *)(*(int *)(iVar1 + 0x44) + 0x12) & 0xfe | 1
      ;
    }
    iVar1 = *(int *)(param_1 + 0x6c);
    Open__10MenuWindowFUci(iVar1,*(byte *)(iVar1 + 0xb0) & 7,*(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x10)
                   );
    iVar1 = *(int *)(param_1 + 0x70);
    Open__10MenuWindowFUci(iVar1,*(byte *)(iVar1 + 0xb0) & 7,*(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x10)
                   );
    iVar1 = *(int *)(param_1 + 0x74);
    Open__10MenuWindowFUci(iVar1 + 0x58,*(byte *)(iVar1 + 0x108) & 7,
                    *(undefined4 *)(*(int *)(iVar1 + 0x8c) + 0x10));
    SetTitle__11CmdTitleLogFPUci
              (*(undefined4 *)(param_1 + 0x80),*(undefined4 *)(*(int *)(param_1 + 0x54) + 0x10),0);
    Open__11CmdTitleLogFv(*(undefined4 *)(param_1 + 0x80));
    iVar1 = *(int *)(param_1 + 0x7c);
    Open__10MenuWindowFUci(iVar1 + 0x58,*(byte *)(iVar1 + 0x108) & 7,
                    *(undefined4 *)(*(int *)(iVar1 + 0x8c) + 0x10));
    uVar5 = CreateBackGround__7CmdMenuFs(*(undefined4 *)(param_1 + 0x10),7);
    *(undefined1 *)(param_1 + 0x20) = uVar5;
    Select__6CursorFP9MenuPlace(*(undefined4 *)(param_1 + 0x18),*(undefined4 *)(param_1 + 0x8c));
    *(byte *)(*(int *)(param_1 + 0x18) + 0xfb) = *(byte *)(*(int *)(param_1 + 0x18) + 0xfb) & 0xef;
    *(char *)(param_1 + 0x21) = *(char *)(param_1 + 0x21) + '\x01';
  }
  else if (*(char *)(param_1 + 0x21) == '\x01') {
    if ((*(char *)(*(int *)(param_1 + 0x70) + 0xa8) == '\x01') ||
       (*(char *)(*(int *)(param_1 + 0x70) + 0xa8) == '\0')) {
      bVar2 = true;
    }
    else {
      bVar2 = false;
    }
    if (bVar2) {
      if (*(char *)(param_1 + 0x20) != '\0') {
        DestroyBackGround__7CmdMenuFs(*(undefined4 *)(param_1 + 0x10),1);
        *(undefined1 *)(param_1 + 0x20) = 0;
      }
      if (-1 < (long)((ulong)*(byte *)(*(int *)(param_1 + 0x18) + 0x12) << 0x3d)) {
        AddOT__7MenuObjFv(*(undefined4 *)(param_1 + 0x18));
      }
      Restore__6CursorFv(*(undefined4 *)(param_1 + 0x18));
      puVar4 = PTR_SelectMenu__6CmdTopFv_0050d118;
      uVar3 = DAT_0050d114;
      *(undefined4 *)(param_1 + 0x58) = _5534;
      *(undefined4 *)(param_1 + 0x5c) = uVar3;
      *(undefined **)(param_1 + 0x60) = puVar4;
      *(undefined1 *)(param_1 + 0x21) = 0;
      *(undefined1 *)(*(int *)(param_1 + 0x10) + 0x4e) = 1;
    }
  }
  return 0;
}

/* JP: 0x00439200  CmdTop::Exit()   [Exit__6CmdTopFv]  size=0x548 */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 Exit__6CmdTopFv(int param_1)

{
  char cVar1;
  int iVar2;
  bool bVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  long lVar6;
  
  iVar2 = *(int *)(param_1 + 0x10);
  cVar1 = *(char *)(param_1 + 0x21);
  if (cVar1 == '\0') {
    lVar6 = IsSetupScene__7CmdMenuFv(iVar2);
    if (lVar6 == 0) {
      return 0;
    }
    *(char *)(param_1 + 0x21) = *(char *)(param_1 + 0x21) + '\x01';
    return 0;
  }
  if (cVar1 != '\x01') {
    if (cVar1 != '\x02') {
      return 0;
    }
    if ((*(char *)(*(int *)(param_1 + 0x70) + 0xa8) == '\x01') ||
       (*(char *)(*(int *)(param_1 + 0x70) + 0xa8) == '\0')) {
      bVar3 = true;
    }
    else {
      bVar3 = false;
    }
    if (!bVar3) {
      return 0;
    }
    (**(code **)(*(int *)(*(int *)(param_1 + 0x70) + 8) + 0xc))();
    *(undefined4 *)(param_1 + 0x70) = 0;
    (**(code **)(*(int *)(*(int *)(param_1 + 0x6c) + 8) + 0xc))();
    *(undefined4 *)(param_1 + 0x6c) = 0;
    ReleaseOT__7MenuObjFv(*(int *)(param_1 + 0x74) + 0x58);
    (**(code **)(*(int *)(*(int *)(param_1 + 0x74) + 8) + 0xc))();
    *(undefined4 *)(param_1 + 0x74) = 0;
    *(undefined1 *)(param_1 + 0x21) = 0;
    uVar5 = uRam004236d0;
    uVar4 = uRam004236cc;
    *(undefined4 *)(param_1 + 0x58) = ___ptmf_null;
    *(undefined4 *)(param_1 + 0x5c) = uVar4;
    *(undefined4 *)(param_1 + 0x60) = uVar5;
    (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x14) + 0x24))
              (*(int *)(param_1 + 0x10),*(undefined1 *)(param_1 + 0x20));
    if (*(char *)(*(int *)(param_1 + 100) + 0xa8) != '\0') {
      return 0;
    }
    (**(code **)(*(int *)(*(int *)(param_1 + 100) + 8) + 0xc))();
    *(undefined4 *)(param_1 + 100) = 0;
    DestroyScene__4MenuFP9MenuSceneb(*(undefined4 *)(param_1 + 0x10),param_1,1);
    return 0;
  }
  (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x14) + 0x28))
            (*(int *)(param_1 + 0x10),*(undefined1 *)(param_1 + 0x20),
             *(undefined2 *)(param_1 + 0x1c),*(undefined2 *)(param_1 + 0x1e));
  cVar1 = *(char *)(param_1 + 0x20);
  if (cVar1 == '\x15') {
    iVar2 = *(int *)(iVar2 + 0xb0);
    Close__10MenuWindowFUci(iVar2 + 0x5c,((ulong)*(byte *)(iVar2 + 0x10c) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar2 + 0x90) + 0x14));
  }
  else if (((((cVar1 == '\x10') || (cVar1 == '\v')) || (cVar1 == '\b')) ||
           ((cVar1 == '\n' || (cVar1 == '\x03')))) || ((cVar1 == '\x02' || (cVar1 == '\x01')))) {
    iVar2 = *(int *)(param_1 + 100);
    *(byte *)(iVar2 + 0x586) = *(byte *)(iVar2 + 0x586) & 0xfe;
    *(byte *)(*(int *)(iVar2 + 0x44) + 0x12) = *(byte *)(*(int *)(iVar2 + 0x44) + 0x12) & 0xfe;
    goto LAB_00439580;
  }
  iVar2 = *(int *)(param_1 + 100);
  Close__10MenuWindowFUci(iVar2,((ulong)*(byte *)(iVar2 + 0xb0) & 0x3f) >> 3,
                  *(undefined4 *)(*(int *)(iVar2 + 0x34) + 0x14));
LAB_00439580:
  cVar1 = *(char *)(param_1 + 0x20);
  if (((cVar1 == '\x0f') || (cVar1 == '\r')) || ((cVar1 == '\x0e' || (cVar1 == '\f')))) {
    Shutdown__6CursorFv(*(undefined4 *)(param_1 + 0x18));
  }
  else {
    *(byte *)(*(int *)(param_1 + 0x18) + 0xfb) = *(byte *)(*(int *)(param_1 + 0x18) + 0xfb) & 0xef;
    Leave__6CursorFv(*(undefined4 *)(param_1 + 0x18));
  }
  iVar2 = *(int *)(param_1 + 0x70);
  Close__10MenuWindowFUci(iVar2,((ulong)*(byte *)(iVar2 + 0xb0) & 0x3f) >> 3,
                  *(undefined4 *)(*(int *)(iVar2 + 0x34) + 0x14));
  iVar2 = *(int *)(param_1 + 0x6c);
  Close__10MenuWindowFUci(iVar2,((ulong)*(byte *)(iVar2 + 0xb0) & 0x3f) >> 3,
                  *(undefined4 *)(*(int *)(iVar2 + 0x34) + 0x14));
  iVar2 = *(int *)(param_1 + 0x74);
  Close__10MenuWindowFUci(iVar2 + 0x58,((ulong)*(byte *)(iVar2 + 0x108) & 0x3f) >> 3,
                  *(undefined4 *)(*(int *)(iVar2 + 0x8c) + 0x14));
  iVar2 = *(int *)(param_1 + 0x80);
  Close__10MenuWindowFUci(iVar2 + 0x58,((ulong)*(byte *)(iVar2 + 0x108) & 0x3f) >> 3,
                  *(undefined4 *)(*(int *)(iVar2 + 0x8c) + 0x14));
  *(char *)(param_1 + 0x21) = *(char *)(param_1 + 0x21) + '\x01';
  return 0;
}

/* JP: 0x00439750  CmdTop::SelectMenu()   [SelectMenu__6CmdTopFv]  size=0x650 */
undefined8 SelectMenu__6CmdTopFv(int param_1)

{
  ushort uVar1;
  int iVar2;
  undefined *puVar3;
  int iVar4;
  undefined4 uVar5;
  long lVar6;
  undefined8 uVar7;
  char cVar8;
  short sVar9;
  undefined1 auStack_c0 [96];
  undefined4 uStack_60;
  undefined4 *puStack_5c;
  undefined4 *puStack_58;
  int iStack_54;
  int iStack_50;
  int iStack_4c;
  int iStack_48;
  int iStack_44;
  int iStack_40;
  int iStack_3c;
  int iStack_38;
  int iStack_34;
  int iStack_30;
  int iStack_2c;
  int iStack_28;
  int iStack_24;
  short sStack_1e;
  short sStack_1c;
  ushort uStack_1a;
  ushort uStack_18;
  ushort uStack_16;
  short sStack_14;
  ushort uStack_12;
  int iStack_10;
  
  iStack_28 = *(int *)(param_1 + 0x10);
  uVar1 = *(ushort *)(iStack_28 + 0x48);
  iStack_2c = *(int *)(param_1 + 0x18);
  iVar2 = *(int *)(iStack_2c + 0xec);
  iStack_48 = iVar2;
  iStack_44 = iVar2;
  uStack_18 = uVar1;
  uStack_16 = uVar1;
  iStack_10 = param_1;
  if ((uVar1 & 0x2000) != 0) {
    if ((*(char *)(*(int *)(param_1 + 100) + 0xa8) == '\x01') ||
       (*(char *)(*(int *)(param_1 + 100) + 0xa8) == '\0')) {
      iStack_30 = 1;
    }
    else {
      iStack_30 = 0;
    }
    if (iStack_30 != 0) {
      uStack_1a = *(ushort *)(iVar2 + 0x22);
      iVar4 = (uint)uStack_1a * 0xc + *(int *)(param_1 + 0x28);
      iStack_4c = iVar4 + 0x10;
      cVar8 = (char)*(undefined2 *)(iVar4 + 0x18);
      *(char *)(param_1 + 0x20) = cVar8;
      iStack_24 = iStack_4c;
      uStack_12 = uStack_1a;
      if (cVar8 < '\0') {
        iVar2 = *(int *)(param_1 + 100);
        Close__10MenuWindowFUci(iVar2,((ulong)*(byte *)(iVar2 + 0xb0) & 0x3f) >> 3,
                        *(undefined4 *)(*(int *)(iVar2 + 0x34) + 0x14));
        *(undefined1 *)(iStack_10 + 0x20) = 2;
        puVar3 = PTR_ShiftMenu__6CmdTopFv_0050d158;
        uVar5 = DAT_0050d154;
        *(undefined4 *)(iStack_10 + 0x58) = _5700;
        *(undefined4 *)(iStack_10 + 0x5c) = uVar5;
        *(undefined **)(iStack_10 + 0x60) = puVar3;
      }
      else {
        sVar9 = *(short *)(iVar4 + 0x1a);
        *(short *)(param_1 + 0x1e) = sVar9;
        if (sVar9 < 0) {
          *(undefined2 *)(param_1 + 0x1e) = 0;
          puVar3 = PTR_Exit__6CmdTopFv_0050d148;
          uVar5 = DAT_0050d144;
          *(undefined4 *)(param_1 + 0x58) = _5697;
          *(undefined4 *)(param_1 + 0x5c) = uVar5;
          *(undefined **)(param_1 + 0x60) = puVar3;
        }
        else {
          lVar6 = SetTarget__8CmdTopPCFs
                            (*(undefined4 *)(param_1 + 0x70),*(undefined2 *)(param_1 + 0x1e));
          if (lVar6 == 0) {
            __ct__9MenuSceneFv(auStack_c0);
            iStack_38 = sm_pCmdMenu__7MenuObj;
            puStack_5c = (undefined4 *)(*(int *)(sm_pCmdMenu__7MenuObj + 0x54) + 0x88);
            puStack_58 = puStack_5c;
            Initialize__9MenuSceneFPUcP9BufMemory(auStack_c0,*puStack_5c,0);
            lVar6 = __nw__FUi(0x2b0);
            uVar5 = 0;
            if (lVar6 != 0) {
              uVar5 = __ct__14CmdNoteMessageFv(lVar6);
            }
            *(undefined4 *)(iStack_10 + 0x78) = uVar5;
            uStack_60 = *(undefined4 *)(*(int *)(iStack_10 + 0x24) + 0x48);
            CreateScene__14CmdNoteMessageFP9MenuScenePci
                      (*(undefined4 *)(iStack_10 + 0x78),auStack_c0,uStack_60,0);
            iVar2 = *(int *)(iStack_10 + 0x78);
            Open__10MenuWindowFUci(iVar2,*(byte *)(iVar2 + 0xb0) & 7,
                            *(undefined4 *)(*(int *)(iVar2 + 0x34) + 0x10));
            puVar3 = PTR_DisplayMessage__6CmdTopFv_0050d138;
            uVar5 = DAT_0050d134;
            *(undefined4 *)(iStack_10 + 0x58) = _5694;
            *(undefined4 *)(iStack_10 + 0x5c) = uVar5;
            *(undefined **)(iStack_10 + 0x60) = puVar3;
            __dt__9MenuSceneFv(auStack_c0,0xffffffffffffffff);
          }
          else {
            uVar7 = GetPlace__10MenuWindowFiss(*(undefined4 *)(iStack_10 + 0x70),2,0,0xffffffffffffffff);
            Select__6CursorFP9MenuPlace(*(undefined4 *)(iStack_10 + 0x18),uVar7);
            Select__8CmdTopPCFP6CmdTopP9MenuGroupP9MenuGroup
                      (*(undefined4 *)(iStack_10 + 0x70),iStack_10,uVar7,0);
            iStack_40 = *(int *)(iStack_10 + 100);
            iStack_54 = *(int *)(iStack_40 + 0x44);
            *(byte *)(iStack_54 + 0x12) = *(byte *)(iStack_54 + 0x12) & 0xfe;
            *(int *)(iStack_10 + 0x8c) = iVar2;
            puVar3 = PTR_SelectCharacter__6CmdTopFv_0050d128;
            uVar5 = DAT_0050d124;
            *(undefined4 *)(iStack_10 + 0x58) = _5689;
            *(undefined4 *)(iStack_10 + 0x5c) = uVar5;
            *(undefined **)(iStack_10 + 0x60) = puVar3;
            iStack_50 = iStack_54;
            iStack_34 = iStack_54;
          }
        }
      }
      PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(iStack_10 + 0x84),2,0,0);
      return 0;
    }
  }
  if ((uVar1 & 0x4000) == 0) {
    iVar4 = MoveVertical__9MenuSceneFi(param_1,0);
    if (iVar2 == iVar4) {
      iStack_3c = *(int *)(iStack_10 + 100);
      sStack_1e = *(short *)(iStack_3c + 0xae);
      if ((uVar1 & 0x20) == 0) {
        sVar9 = sStack_1e;
        if ((uVar1 & 0x80) != 0) {
          sVar9 = 0;
        }
      }
      else {
        sVar9 = 1;
      }
      if (sStack_1e != sVar9) {
        iVar2 = *(int *)(iStack_10 + 100);
        sStack_1c = sStack_1e;
        sStack_14 = sStack_1e;
        Close__10MenuWindowFUci(iVar2,((ulong)*(byte *)(iVar2 + 0xb0) & 0x3f) >> 3,
                        *(undefined4 *)(*(int *)(iVar2 + 0x34) + 0x14));
        Shutdown__6CursorFv(*(undefined4 *)(iStack_10 + 0x18));
        *(char *)(iStack_10 + 0x20) = (char)sVar9;
        puVar3 = PTR_ShiftMenu__6CmdTopFv_0050d178;
        uVar5 = DAT_0050d174;
        *(undefined4 *)(iStack_10 + 0x58) = _5720;
        *(undefined4 *)(iStack_10 + 0x5c) = uVar5;
        *(undefined **)(iStack_10 + 0x60) = puVar3;
        PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(iStack_10 + 0x84),6,0,0);
      }
    }
    else {
      Select__9CmdWindowFP7CmdNoteP9MenuSceneP8MenuTextP8MenuText
                (*(undefined4 *)(iStack_10 + 100),*(undefined4 *)(iStack_10 + 0x7c),iStack_10,iVar4,
                 iVar2);
      PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(iStack_10 + 0x84),0,0,0);
    }
  }
  else {
    *(undefined1 *)(param_1 + 0x20) = 0x17;
    puVar3 = PTR_Exit__6CmdTopFv_0050d168;
    uVar5 = DAT_0050d164;
    *(undefined4 *)(param_1 + 0x58) = _5705;
    *(undefined4 *)(param_1 + 0x5c) = uVar5;
    *(undefined **)(param_1 + 0x60) = puVar3;
    PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x84),3,0,0);
  }
  return 0;
}

/* JP: 0x00439da0  CmdTop::SelectCharacter()   [SelectCharacter__6CmdTopFv]  size=0x290 */
undefined8 SelectCharacter__6CmdTopFv(int param_1)

{
  ushort uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined *puVar4;
  int iVar5;
  
  uVar1 = *(ushort *)(*(int *)(param_1 + 0x10) + 0x48);
  iVar2 = *(int *)(*(int *)(param_1 + 0x18) + 0xec);
  if ((uVar1 & 0x2000) == 0) {
    if ((uVar1 & 0x4000) == 0) {
      iVar5 = MoveVertical__9MenuSceneFi(param_1,0);
      if (iVar2 != iVar5) {
        Select__8CmdTopPCFP6CmdTopP9MenuGroupP9MenuGroup
                  (*(undefined4 *)(param_1 + 0x70),param_1,iVar5,iVar2);
        PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x84),0,0,0);
      }
    }
    else {
      ClearTarget__8CmdTopPCFv(*(undefined4 *)(param_1 + 0x70));
      Select__6CursorFP9MenuPlace(*(undefined4 *)(param_1 + 0x18),*(undefined4 *)(param_1 + 0x8c));
      Select__9CmdWindowFP7CmdNoteP9MenuSceneP8MenuTextP8MenuText
                (*(undefined4 *)(param_1 + 100),*(undefined4 *)(param_1 + 0x7c),param_1,
                 *(undefined4 *)(param_1 + 0x8c),0);
      Select__8CmdTopPCFP6CmdTopP9MenuGroupP9MenuGroup
                (*(undefined4 *)(param_1 + 0x70),param_1,0,iVar2);
      iVar2 = *(int *)(*(int *)(param_1 + 100) + 0x44);
      *(byte *)(iVar2 + 0x12) = *(byte *)(iVar2 + 0x12) & 0xfe | 1;
      puVar4 = PTR_SelectMenu__6CmdTopFv_0050d198;
      uVar3 = DAT_0050d194;
      *(undefined4 *)(param_1 + 0x58) = _5795;
      *(undefined4 *)(param_1 + 0x5c) = uVar3;
      *(undefined **)(param_1 + 0x60) = puVar4;
      PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x84),3,0,0);
    }
  }
  else {
    *(undefined2 *)(param_1 + 0x1e) = *(undefined2 *)(iVar2 + 0x16);
    puVar4 = PTR_Exit__6CmdTopFv_0050d188;
    uVar3 = DAT_0050d184;
    *(undefined4 *)(param_1 + 0x58) = _5790;
    *(undefined4 *)(param_1 + 0x5c) = uVar3;
    *(undefined **)(param_1 + 0x60) = puVar4;
    ClearTarget__8CmdTopPCFv(*(undefined4 *)(param_1 + 0x70));
    PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x84),2,0,0);
  }
  BlinkSelect__8CmdTopPCFv(*(undefined4 *)(param_1 + 0x70));
  return 0;
}

/* JP: 0x0043a030  CmdTop::SelectData()   [SelectData__6CmdTopFv]  size=0x3a8 */
undefined8 SelectData__6CmdTopFv(int param_1)

{
  short sVar1;
  ushort uVar2;
  int iVar3;
  undefined *puVar4;
  undefined4 uVar5;
  int iVar6;
  long lVar7;
  
  uVar2 = *(ushort *)(*(int *)(param_1 + 0x10) + 0x48);
  iVar3 = *(int *)(*(int *)(param_1 + 0x18) + 0xec);
  if ((uVar2 & 0x2000) == 0) {
    if ((uVar2 & 0x4000) == 0) {
      iVar6 = MoveVertical__9MenuSceneFi(param_1,0);
      if (iVar3 != iVar6) {
        Select__9CmdWindowFP7CmdNoteP9MenuSceneP8MenuTextP8MenuText
                  (*(undefined4 *)(param_1 + 0x68),*(undefined4 *)(param_1 + 0x7c),param_1,iVar6,
                   iVar3);
        PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x84),0,0,0);
      }
    }
    else {
      iVar3 = *(int *)(param_1 + 0x68);
      Close__10MenuWindowFUci(iVar3,((ulong)*(byte *)(iVar3 + 0xb0) & 0x3f) >> 3,
                      *(undefined4 *)(*(int *)(iVar3 + 0x34) + 0x14));
      Shutdown__6CursorFv(*(undefined4 *)(param_1 + 0x18));
      *(undefined1 *)(param_1 + 0x20) = 0;
      puVar4 = PTR_ShiftMenu__6CmdTopFv_0050d1b8;
      uVar5 = DAT_0050d1b4;
      *(undefined4 *)(param_1 + 0x58) = _5841;
      *(undefined4 *)(param_1 + 0x5c) = uVar5;
      *(undefined **)(param_1 + 0x60) = puVar4;
      PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x84),3,0,0);
    }
  }
  else {
    sVar1 = *(short *)(iVar3 + 0x1e);
    lVar7 = __nw__FUi(0x184);
    uVar5 = 0;
    if (lVar7 != 0) {
      uVar5 = __ct__10dataAccessFv(lVar7);
    }
    *(undefined4 *)(param_1 + 0x88) = uVar5;
    initialize__10dataAccessFQ210dataAccess10ACCESSMODEPFiPv_vPv(*(undefined4 *)(param_1 + 0x88),sVar1 != 0,0x435610,
                    *(undefined4 *)(param_1 + 0x10));
    iVar3 = *(int *)(param_1 + 0x68);
    Close__10MenuWindowFUci(iVar3,((ulong)*(byte *)(iVar3 + 0xb0) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar3 + 0x34) + 0x14));
    iVar3 = *(int *)(param_1 + 0x70);
    Close__10MenuWindowFUci(iVar3,((ulong)*(byte *)(iVar3 + 0xb0) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar3 + 0x34) + 0x14));
    iVar3 = *(int *)(param_1 + 0x6c);
    Close__10MenuWindowFUci(iVar3,((ulong)*(byte *)(iVar3 + 0xb0) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar3 + 0x34) + 0x14));
    iVar3 = *(int *)(param_1 + 0x74);
    Close__10MenuWindowFUci(iVar3 + 0x58,((ulong)*(byte *)(iVar3 + 0x108) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar3 + 0x8c) + 0x14));
    iVar3 = *(int *)(param_1 + 0x7c);
    Close__10MenuWindowFUci(iVar3 + 0x58,((ulong)*(byte *)(iVar3 + 0x108) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar3 + 0x8c) + 0x14));
    iVar3 = *(int *)(param_1 + 0x80);
    Close__10MenuWindowFUci(iVar3 + 0x58,((ulong)*(byte *)(iVar3 + 0x108) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar3 + 0x8c) + 0x14));
    uVar5 = Leave__6CursorFv(*(undefined4 *)(param_1 + 0x18));
    *(undefined4 *)(param_1 + 0x8c) = uVar5;
    puVar4 = PTR_ShiftDataAccess__6CmdTopFv_0050d1a8;
    uVar5 = DAT_0050d1a4;
    *(undefined4 *)(param_1 + 0x58) = _5836;
    *(undefined4 *)(param_1 + 0x5c) = uVar5;
    *(undefined **)(param_1 + 0x60) = puVar4;
    PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x84),2,0,0);
  }
  return 0;
}

/* JP: 0x0043a3e0  CmdTop::ShiftMenu()   [ShiftMenu__6CmdTopFv]  size=0x410 */
undefined8 ShiftMenu__6CmdTopFv(int param_1)

{
  bool bVar1;
  undefined *puVar2;
  undefined4 uVar3;
  undefined *puVar4;
  undefined4 uVar5;
  long lVar6;
  undefined8 uVar7;
  int iVar8;
  
  iVar8 = *(int *)(param_1 + 100);
  if (iVar8 == 0) {
    iVar8 = *(int *)(param_1 + 0x68);
  }
  if ((*(char *)(iVar8 + 0xa8) == '\x01') || (*(char *)(iVar8 + 0xa8) == '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if (bVar1) {
    if (*(char *)(iVar8 + 0xa8) == '\0') {
      if (*(char *)(param_1 + 0x20) == '\x02') {
        (**(code **)(*(int *)(*(int *)(param_1 + 100) + 8) + 0xc))();
        *(undefined4 *)(param_1 + 100) = 0;
        lVar6 = __nw__FUi(500);
        uVar5 = 0;
        if (lVar6 != 0) {
          uVar5 = __ct__14CmdTopMenuDataFv(lVar6);
        }
        *(undefined4 *)(param_1 + 0x68) = uVar5;
        CreateScene__14CmdTopMenuDataFP6CmdTop(*(undefined4 *)(param_1 + 0x68),param_1);
        uVar7 = GetPlace__10MenuWindowFiss(*(undefined4 *)(param_1 + 0x68),2,0,0xffffffffffffffff);
        Select__6CursorFP9MenuPlace(*(undefined4 *)(param_1 + 0x18),uVar7);
        Select__9CmdWindowFP7CmdNoteP9MenuSceneP8MenuTextP8MenuText
                  (*(undefined4 *)(param_1 + 0x68),*(undefined4 *)(param_1 + 0x7c),param_1,uVar7,0);
        iVar8 = *(int *)(param_1 + 0x68);
        Open__10MenuWindowFUci(iVar8,*(byte *)(iVar8 + 0xb0) & 7,
                        *(undefined4 *)(*(int *)(iVar8 + 0x34) + 0x10));
      }
      else {
        if (*(int *)(param_1 + 0x68) == 0) {
          UpdateScene__10CmdTopMenuFP6CmdTops
                    (*(undefined4 *)(param_1 + 100),param_1,*(undefined1 *)(param_1 + 0x20));
          SetCursor__10MenuWindowFP6Cursori(*(undefined4 *)(param_1 + 100),*(undefined4 *)(param_1 + 0x18),2);
          uVar5 = *(undefined4 *)(*(int *)(param_1 + 0x18) + 0xec);
        }
        else {
          (**(code **)(*(int *)(*(int *)(param_1 + 0x68) + 8) + 0xc))();
          *(undefined4 *)(param_1 + 0x68) = 0;
          lVar6 = __nw__FUi(0x5f4);
          uVar5 = 0;
          if (lVar6 != 0) {
            uVar5 = __ct__10CmdTopMenuFv(lVar6);
          }
          *(undefined4 *)(param_1 + 100) = uVar5;
          CreateScene__10CmdTopMenuFP6CmdTop(*(undefined4 *)(param_1 + 100),param_1);
          UpdateScene__10CmdTopMenuFP6CmdTops
                    (*(undefined4 *)(param_1 + 100),param_1,*(undefined1 *)(param_1 + 0x20));
          uVar5 = GetPlace__10MenuWindowFs(*(undefined4 *)(param_1 + 100),9);
          Select__6CursorFP9MenuPlace(*(undefined4 *)(param_1 + 0x18),uVar5);
        }
        Select__9CmdWindowFP7CmdNoteP9MenuSceneP8MenuTextP8MenuText
                  (*(undefined4 *)(param_1 + 100),*(undefined4 *)(param_1 + 0x7c),param_1,uVar5,0);
        iVar8 = *(int *)(param_1 + 100);
        Open__10MenuWindowFUci(iVar8,*(byte *)(iVar8 + 0xb0) & 7,
                        *(undefined4 *)(*(int *)(iVar8 + 0x34) + 0x10));
      }
    }
    else {
      Restore__6CursorFv(*(undefined4 *)(param_1 + 0x18));
      puVar4 = PTR_SelectMenu__6CmdTopFv_0050d1d8;
      uVar3 = DAT_0050d1d4;
      puVar2 = PTR_SelectData__6CmdTopFv_0050d1c8;
      uVar5 = DAT_0050d1c4;
      if (*(char *)(param_1 + 0x20) == '\x02') {
        *(undefined4 *)(param_1 + 0x58) = _5903;
        *(undefined4 *)(param_1 + 0x5c) = uVar5;
        *(undefined **)(param_1 + 0x60) = puVar2;
      }
      else {
        *(undefined4 *)(param_1 + 0x58) = _5906;
        *(undefined4 *)(param_1 + 0x5c) = uVar3;
        *(undefined **)(param_1 + 0x60) = puVar4;
      }
    }
  }
  return 0;
}

/* JP: 0x0043a7f0  CmdTop::ShiftDataAccess()   [ShiftDataAccess__6CmdTopFv]  size=0x188 */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 ShiftDataAccess__6CmdTopFv(int param_1)

{
  bool bVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined *puVar4;
  
  if ((*(char *)(*(int *)(param_1 + 0x70) + 0xa8) == '\x01') ||
     (*(char *)(*(int *)(param_1 + 0x70) + 0xa8) == '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if (bVar1) {
    if (*(char *)(*(int *)(param_1 + 0x70) + 0xa8) == '\0') {
      *(byte *)(*(int *)(param_1 + 0x18) + 0x12) = *(byte *)(*(int *)(param_1 + 0x18) + 0x12) & 0xfe
      ;
      start__10dataAccessFQ210dataAccess9STARTMODEii(*(undefined4 *)(param_1 + 0x88),0,0,0);
      uVar3 = uRam004236d0;
      uVar2 = uRam004236cc;
      *(undefined4 *)(param_1 + 0x58) = ___ptmf_null;
      *(undefined4 *)(param_1 + 0x5c) = uVar2;
      *(undefined4 *)(param_1 + 0x60) = uVar3;
    }
    else {
      Select__6CursorFP9MenuPlace(*(undefined4 *)(param_1 + 0x18),*(undefined4 *)(param_1 + 0x8c));
      puVar4 = PTR_SelectData__6CmdTopFv_0050d1e8;
      uVar2 = DAT_0050d1e4;
      *(undefined4 *)(param_1 + 0x58) = _5954;
      *(undefined4 *)(param_1 + 0x5c) = uVar2;
      *(undefined **)(param_1 + 0x60) = puVar4;
    }
  }
  return 0;
}

/* JP: 0x0043a980  CmdTop::DataAccessEvent()   [DataAccessEvent__6CmdTopFv]  size=0x1e0 */
void DataAccessEvent__6CmdTopFv(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined *puVar3;
  
  iVar1 = *(int *)(param_1 + 0x68);
  Open__10MenuWindowFUci(iVar1,*(byte *)(iVar1 + 0xb0) & 7,*(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x10));
  iVar1 = *(int *)(param_1 + 0x70);
  Open__10MenuWindowFUci(iVar1,*(byte *)(iVar1 + 0xb0) & 7,*(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x10));
  iVar1 = *(int *)(param_1 + 0x6c);
  Open__10MenuWindowFUci(iVar1,*(byte *)(iVar1 + 0xb0) & 7,*(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x10));
  iVar1 = *(int *)(param_1 + 0x74);
  Open__10MenuWindowFUci(iVar1 + 0x58,*(byte *)(iVar1 + 0x108) & 7,
                  *(undefined4 *)(*(int *)(iVar1 + 0x8c) + 0x10));
  iVar1 = *(int *)(param_1 + 0x7c);
  Open__10MenuWindowFUci(iVar1 + 0x58,*(byte *)(iVar1 + 0x108) & 7,
                  *(undefined4 *)(*(int *)(iVar1 + 0x8c) + 0x10));
  Open__11CmdTitleLogFv(*(undefined4 *)(param_1 + 0x80));
  getCursorPos__10dataAccessFPfPf(*(undefined4 *)(param_1 + 0x88),*(undefined4 *)(*(int *)(param_1 + 0x18) + 0xd8),
                  *(int *)(*(int *)(param_1 + 0x18) + 0xd8) + 4);
  ClearAfter__6CursorFv(*(undefined4 *)(param_1 + 0x18));
  *(byte *)(*(int *)(param_1 + 0x18) + 0x12) = *(byte *)(*(int *)(param_1 + 0x18) + 0x12) & 0xfe | 1
  ;
  puVar3 = PTR_ShiftDataAccess__6CmdTopFv_0050d1f8;
  uVar2 = DAT_0050d1f4;
  *(undefined4 *)(param_1 + 0x58) = _5978;
  *(undefined4 *)(param_1 + 0x5c) = uVar2;
  *(undefined **)(param_1 + 0x60) = puVar3;
  return;
}

/* JP: 0x0043ab60  CmdTop::DisplayMessage()   [DisplayMessage__6CmdTopFv]  size=0x1b8 */
undefined8 DisplayMessage__6CmdTopFv(int param_1)

{
  int iVar1;
  bool bVar2;
  undefined4 uVar3;
  undefined *puVar4;
  long lVar5;
  
  if (*(char *)(param_1 + 0x21) == '\x01') {
    if ((*(char *)(*(int *)(param_1 + 0x78) + 0xa8) == '\x01') ||
       (*(char *)(*(int *)(param_1 + 0x78) + 0xa8) == '\0')) {
      bVar2 = true;
    }
    else {
      bVar2 = false;
    }
    if (bVar2) {
      ClearTarget__8CmdTopPCFv(*(undefined4 *)(param_1 + 0x70));
      (**(code **)(*(int *)(*(int *)(param_1 + 0x78) + 8) + 0xc))();
      *(undefined4 *)(param_1 + 0x78) = 0;
      *(undefined1 *)(param_1 + 0x21) = 0;
      puVar4 = PTR_SelectMenu__6CmdTopFv_0050d208;
      uVar3 = DAT_0050d204;
      *(undefined4 *)(param_1 + 0x58) = _6026;
      *(undefined4 *)(param_1 + 0x5c) = uVar3;
      *(undefined **)(param_1 + 0x60) = puVar4;
    }
  }
  else if ((*(char *)(param_1 + 0x21) == '\0') &&
          (lVar5 = Run__14CmdNoteMessageFUs
                             (*(undefined4 *)(param_1 + 0x78),
                              *(undefined2 *)(*(int *)(param_1 + 0x10) + 0x48)), lVar5 != 0)) {
    iVar1 = *(int *)(param_1 + 0x78);
    Close__10MenuWindowFUci(iVar1,((ulong)*(byte *)(iVar1 + 0xb0) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x14));
    *(char *)(param_1 + 0x21) = *(char *)(param_1 + 0x21) + '\x01';
  }
  return 0;
}
