/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdComboKey   functions: 21
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdComboKey.md).
 */

/* JP: 0x00485ef0  CmdComboKey::CmdComboKey()   [__ct__11CmdComboKeyFv]  size=0xb4 */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __ct__11CmdComboKeyFv(int param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  __ct__10CmdPCSceneFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__11CmdComboKey;
  uVar2 = uRam004236d0;
  uVar1 = uRam004236cc;
  *(undefined4 *)(param_1 + 0x7c) = ___ptmf_null;
  *(undefined4 *)(param_1 + 0x80) = uVar1;
  *(undefined4 *)(param_1 + 0x84) = uVar2;
  __ct__15CmdComboKeySlotFv(param_1 + 0x88);
  __ct__11CmdSubTitleFv(param_1 + 0xad0);
  *(undefined4 *)(param_1 + 0xc98) = 0;
  *(undefined4 *)(param_1 + 0xc9c) = 0;
  *(undefined4 *)(param_1 + 0xca0) = 0;
  *(undefined4 *)(param_1 + 0xca4) = 0;
  *(undefined4 *)(param_1 + 0xca8) = 0;
  *(undefined4 *)(param_1 + 0xcb0) = 0;
  return param_1;
}

/* JP: 0x00485fb0  CmdComboKey::~CmdComboKey()   [__dt__11CmdComboKeyFv]  size=0x184 */
int __dt__11CmdComboKeyFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__11CmdComboKey;
    if (*(int *)(param_1 + 0xc98) != 0) {
      (**(code **)(*(int *)(*(int *)(param_1 + 0xc98) + 8) + 0xc))();
    }
    if (*(int *)(param_1 + 0xc9c) != 0) {
      (**(code **)(*(int *)(*(int *)(param_1 + 0xc9c) + 8) + 0xc))();
    }
    if (*(int *)(param_1 + 0xca0) != 0) {
      (**(code **)(*(int *)(*(int *)(param_1 + 0xca0) + 8) + 0xc))();
    }
    if (*(int *)(param_1 + 0xca4) != 0) {
      (**(code **)(*(int *)(*(int *)(param_1 + 0xca4) + 8) + 0xc))();
    }
    if (*(int *)(param_1 + 0xca8) != 0) {
      (**(code **)(*(int *)(*(int *)(param_1 + 0xca8) + 8) + 0xc))();
    }
    if (*(int *)(param_1 + 0xcb0) != 0) {
      __dla__FPv(*(undefined4 *)(param_1 + 0xcb0));
    }
    __dt__11CmdSubTitleFv(param_1 + 0xad0,0xffffffffffffffff);
    __dt__15CmdComboKeySlotFv(param_1 + 0x88,0xffffffffffffffff);
    __dt__10CmdPCSceneFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x00486140  CmdComboKey::GetReady()   [GetReady__11CmdComboKeyFv]  size=0x1fc */
undefined4 GetReady__11CmdComboKeyFv(int param_1)

{
  undefined *puVar1;
  ushort uVar2;
  short sVar3;
  undefined4 uVar4;
  int iVar5;
  undefined8 uVar6;
  
  iVar5 = *(int *)(param_1 + 0x10);
  for (uVar2 = 2; (short)uVar2 < 6; uVar2 = uVar2 + 1) {
    Convert__13MenuDataTableFPUci(*(undefined4 *)((uint)uVar2 * 0xc + *(int *)(param_1 + 0x54) + 0x10),0);
  }
  CreatePCInfo__10CmdPCSceneFPUc(param_1,*(undefined4 *)(*(int *)(param_1 + 0x54) + 0x28));
  *(undefined2 *)(*(int *)(param_1 + 0x18) + 0x32) = 0;
  sVar3 = GetLayerCount__10CmdPCSceneFs(param_1,0);
  if (sVar3 < 2) {
    *(byte *)(param_1 + 0x23) = *(byte *)(param_1 + 0x23) & 0xfe;
  }
  SetChengePCMode__10CmdPCSceneFUc(param_1,0);
  uVar6 = GetRegCnt__9RegDatApiFii(0x38,0xffffffffffffffff);
  uVar4 = __nwa__FUi(uVar6);
  *(undefined4 *)(param_1 + 0xcb0) = uVar4;
  iVar5 = Find__13MenuDataTableFs(iVar5 + 0x28,0x31);
  *(int *)(param_1 + 0xcac) = iVar5 + 0x10;
  *(ushort *)(param_1 + 0xcb4) = *(ushort *)(iVar5 + 4) & 0xff;
  *(ushort *)(param_1 + 0xcb6) = *(ushort *)(iVar5 + 4) >> 8;
  puVar1 = PTR_Enter__11CmdComboKeyFv_0050da78;
  uVar4 = DAT_0050da74;
  *(undefined4 *)(param_1 + 0x7c) = _5077;
  *(undefined4 *)(param_1 + 0x80) = uVar4;
  *(undefined **)(param_1 + 0x84) = puVar1;
  return 1;
}

/* JP: 0x00486340  CmdComboKey::Run()   [Run__11CmdComboKeyFv]  size=0x104 */
undefined4 Run__11CmdComboKeyFv(int param_1)

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
    if ((lVar2 != 0) && (lVar2 = __ptmf_scall(param_1), lVar2 == 0)) {
      return 0;
    }
  }
  return 1;
}

/* JP: 0x00486450  CmdComboKey::Update(short)   [Update__11CmdComboKeyFs]  size=0x1b8 */
void Update__11CmdComboKeyFs(int param_1,undefined2 param_2)

{
  undefined4 uVar1;
  int *piVar2;
  int iVar3;
  ushort uVar4;
  undefined2 uVar5;
  int iVar6;
  
  uVar1 = *(undefined4 *)(param_1 + 0x5c);
  piVar2 = *(int **)(param_1 + 0x70);
  uVar4 = (ushort)*(byte *)(*piVar2 + 2);
  UpdatePCInfo__10CmdPCSceneFsP11CmdPCStatus(param_1,param_2,0);
  uVar5 = GetRegCnt__9RegDatApiFii(0x38,0xffffffffffffffff);
  CreateMagic__5CmdPCFP8CmdPartysPc(piVar2,uVar1,uVar5,*(undefined4 *)(param_1 + 0xcb0));
  UpdateScene__15CmdComboKeySlotFP11CmdComboKeyss(param_1 + 0x88,param_1,uVar4,1);
  Open__10MenuWindowFUci(param_1 + 0x88,*(byte *)(param_1 + 0x138) & 7,
                  *(undefined4 *)(*(int *)(param_1 + 0xbc) + 0x10));
  *(ushort *)(param_1 + 0xcb8) = uVar4;
  iVar3 = *(int *)(*(int *)(param_1 + 0x18) + 0xec);
  if ((iVar3 == 0) || (iVar6 = iVar3, -1 < (long)((ulong)*(byte *)(iVar3 + 0x21) << 0x3c))) {
    iVar6 = SetCursor__10MenuWindowFP6Cursori(param_1 + 0x88,*(undefined4 *)(param_1 + 0x18),2);
  }
  Select__6CursorFP9MenuPlace(*(undefined4 *)(param_1 + 0x18),iVar6);
  SelectSlot__11CmdComboKeyFsP9MenuPlaceP9MenuPlace(param_1,1,iVar6,iVar3);
  return;
}

/* JP: 0x00486610  CmdComboKey::UpdateCommand(short)   [UpdateCommand__11CmdComboKeyFs]  size=0x10c */
void UpdateCommand__11CmdComboKeyFs(int param_1,short param_2)

{
  int iVar1;
  undefined4 uVar2;
  long lVar3;
  
  if (*(int *)(param_1 + 0xc98) == 0) {
    lVar3 = __nw__FUi(0x374);
    uVar2 = 0;
    if (lVar3 != 0) {
      uVar2 = __ct__18CmdComboKeyCommandFv(lVar3);
    }
    *(undefined4 *)(param_1 + 0xc98) = uVar2;
    CreateScene__18CmdComboKeyCommandFP11CmdComboKey(*(undefined4 *)(param_1 + 0xc98),param_1);
  }
  UpdateScene__18CmdComboKeyCommandFP11CmdComboKeyss
            (*(undefined4 *)(param_1 + 0xc98),param_1,*(undefined2 *)(param_1 + 0xcb8),0);
  *(byte *)(*(int *)(param_1 + 0xc98) + 0x12) =
       *(byte *)(*(int *)(param_1 + 0xc98) + 0x12) & 0xfe | 1;
  if (param_2 != 0) {
    iVar1 = *(int *)(param_1 + 0xc98);
    Open__10MenuWindowFUci(iVar1,*(byte *)(iVar1 + 0xb0) & 7,*(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x10)
                   );
  }
  return;
}

/* JP: 0x00486720  CmdComboKey::UpdateCharacter(short)   [UpdateCharacter__11CmdComboKeyFs]  size=0xfc */
void UpdateCharacter__11CmdComboKeyFs(int param_1,short param_2)

{
  int iVar1;
  undefined4 uVar2;
  long lVar3;
  
  if (*(int *)(param_1 + 0xc9c) == 0) {
    lVar3 = __nw__FUi(0xf8);
    uVar2 = 0;
    if (lVar3 != 0) {
      uVar2 = __ct__20CmdComboKeyCharacterFv(lVar3);
    }
    *(undefined4 *)(param_1 + 0xc9c) = uVar2;
    CreateScene__20CmdComboKeyCharacterFP11CmdComboKey(*(undefined4 *)(param_1 + 0xc9c),param_1);
  }
  UpdateScene__20CmdComboKeyCharacterFP11CmdComboKey(*(undefined4 *)(param_1 + 0xc9c),param_1);
  *(byte *)(*(int *)(param_1 + 0xc9c) + 0x12) =
       *(byte *)(*(int *)(param_1 + 0xc9c) + 0x12) & 0xfe | 1;
  if (param_2 != 0) {
    iVar1 = *(int *)(param_1 + 0xc9c);
    Open__10MenuWindowFUci(iVar1,*(byte *)(iVar1 + 0xb0) & 7,*(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x10)
                   );
  }
  return;
}

/* JP: 0x00486820  CmdComboKey::UpdateGoods(short, short)   [UpdateGoods__11CmdComboKeyFss]  size=0x104 */
void UpdateGoods__11CmdComboKeyFss(int param_1,short param_2,undefined2 param_3)

{
  int iVar1;
  undefined4 uVar2;
  long lVar3;
  
  if (*(int *)(param_1 + 0xca0) == 0) {
    lVar3 = __nw__FUi(0x128);
    uVar2 = 0;
    if (lVar3 != 0) {
      uVar2 = __ct__16CmdComboKeyGoodsFv(lVar3);
    }
    *(undefined4 *)(param_1 + 0xca0) = uVar2;
    CreateScene__16CmdComboKeyGoodsFP11CmdComboKey(*(undefined4 *)(param_1 + 0xca0),param_1);
  }
  UpdateScene__16CmdComboKeyGoodsFP11CmdComboKeys(*(undefined4 *)(param_1 + 0xca0),param_1,param_3);
  *(byte *)(*(int *)(param_1 + 0xca0) + 0x12) =
       *(byte *)(*(int *)(param_1 + 0xca0) + 0x12) & 0xfe | 1;
  if (param_2 != 0) {
    iVar1 = *(int *)(param_1 + 0xca0);
    Open__10MenuWindowFUci(iVar1,*(byte *)(iVar1 + 0xb0) & 7,*(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x10)
                   );
  }
  return;
}

/* JP: 0x00486930  CmdComboKey::UpdateFence(CmdFence*, short, short, short)   [UpdateFence__11CmdComboKeyFP8CmdFencesss]  size=0x170 */
int UpdateFence__11CmdComboKeyFP8CmdFencesss
              (int param_1,int param_2,ushort param_3,short param_4,undefined2 param_5)

{
  int iVar1;
  long lVar2;
  undefined1 auStack_b0 [96];
  int iStack_50;
  int iStack_40;
  ushort uStack_30;
  short sStack_20;
  undefined2 uStack_10;
  
  iStack_50 = param_1;
  iStack_40 = param_2;
  uStack_30 = param_3;
  sStack_20 = param_4;
  uStack_10 = param_5;
  __ct__9MenuSceneFv(auStack_b0);
  Initialize__9MenuSceneFPUcP9BufMemory(auStack_b0,
                  *(undefined4 *)((uint)uStack_30 * 0xc + *(int *)(iStack_50 + 0x54) + 0x10),0);
  if (iStack_40 == 0) {
    lVar2 = __nw__FUi(0x178);
    iVar1 = 0;
    if (lVar2 != 0) {
      iVar1 = __ct__8CmdFenceFv(lVar2);
    }
    iStack_40 = iVar1;
    CreateFence__8CmdFenceFP9MenuScenePUc
              (iStack_40,auStack_b0,*(undefined4 *)(*(int *)(iStack_50 + 0x54) + 0x1c));
  }
  SetTitle__8CmdFenceFP9MenuScenes(iStack_40,auStack_b0,uStack_10);
  *(byte *)(iStack_40 + 0x12) = *(byte *)(iStack_40 + 0x12) & 0xfe | 1;
  if (sStack_20 != 0) {
    Open__10MenuWindowFUci(iStack_40,*(byte *)(iStack_40 + 0xb0) & 7,
                    *(undefined4 *)(*(int *)(iStack_40 + 0x34) + 0x10));
  }
  iVar1 = iStack_40;
  __dt__9MenuSceneFv(auStack_b0,0xffffffffffffffff);
  return iVar1;
}

/* JP: 0x00486aa0  CmdComboKey::CreateMask(short)   [CreateMask__11CmdComboKeyFs]  size=0x140 */
void CreateMask__11CmdComboKeyFs(int param_1,short param_2)

{
  short sVar1;
  int iVar2;
  long lVar3;
  uint uVar4;
  byte *pbVar5;
  byte abStack_24 [4];
  int iStack_20;
  short sStack_10;
  
  sVar1 = *(short *)(param_1 + 0xcb8);
  iVar2 = *(int *)(*(int *)(param_1 + 0x5c) + 4);
  pbVar5 = abStack_24;
  iStack_20 = param_1;
  sStack_10 = param_2;
  for (uVar4 = 1; (int)uVar4 < 4; uVar4 = uVar4 + 1) {
    *pbVar5 = (byte)(1 << (uVar4 & 0x1f));
    lVar3 = IsComboKeyData__11CmdComboKeyFP15SHORTCUTCommandcs
                      (iStack_20,iVar2 + sVar1 * 0x10 + 0xf44 + param_2 * 4,(char)uVar4,
                       *(undefined2 *)(iStack_20 + 0xcb8));
    if (lVar3 != 0) {
      *pbVar5 = 0;
    }
    pbVar5 = pbVar5 + 1;
  }
  *(byte *)(iStack_20 + 0xcbc) = ~(abStack_24[2] | abStack_24[0] | abStack_24[1]);
  return;
}

/* JP: 0x00486be0  CmdComboKey::IsComboKeyData(SHORTCUTCommand*, char, short)   [IsComboKeyData__11CmdComboKeyFP15SHORTCUTCommandcs]  size=0x16c */
undefined4
IsComboKeyData__11CmdComboKeyFP15SHORTCUTCommandcs
          (int param_1,char *param_2,char param_3,undefined2 param_4)

{
  undefined4 uVar1;
  short sVar2;
  long lVar3;
  char acStack_44 [2];
  short sStack_42;
  int iStack_40;
  char *pcStack_30;
  char cStack_20;
  undefined2 uStack_10;
  
  uVar1 = *(undefined4 *)(param_1 + 0x5c);
  iStack_40 = param_1;
  pcStack_30 = param_2;
  cStack_20 = param_3;
  uStack_10 = param_4;
  sVar2 = GetComboKeyCount__8CmdPartyFss(uVar1,param_3,param_4);
  acStack_44[0] = cStack_20;
  sStack_42 = 0;
  do {
    if (sVar2 <= sStack_42) {
      return 0;
    }
    lVar3 = GetComboKeyData__8CmdPartyFsP15SHORTCUTCommandPcP15CmdComboKeyData
                      (uVar1,uStack_10,acStack_44,*(undefined4 *)(iStack_40 + 0xcb0),0);
    if (lVar3 != 0) {
      if (cStack_20 == '\x01') {
        return 1;
      }
      if ((*pcStack_30 != cStack_20) || (*(short *)(pcStack_30 + 2) != sStack_42)) {
        return 1;
      }
    }
    sStack_42 = sStack_42 + 1;
  } while( true );
}

/* JP: 0x00486d50  CmdComboKey::StartButtonReport()   [StartButtonReport__11CmdComboKeyFv]  size=0xdc */
void StartButtonReport__11CmdComboKeyFv(int param_1)

{
  int iVar1;
  int iVar2;
  ulong uVar3;
  
  iVar1 = *(int *)(param_1 + 0x68);
  ClearReport__15CmdButtonReportFv(iVar1);
  iVar2 = *(int *)(*(int *)(*(int *)(param_1 + 0x18) + 0xec) + 0x18);
  if (*(int *)(iVar2 + 0x44) == 0) {
    uVar3 = 0;
  }
  else {
    uVar3 = ((ulong)*(ushort *)(iVar2 + 0xb2) & 0x3ff) >> 2;
  }
  if (uVar3 != 0) {
    SetReport__15CmdButtonReportFii(iVar1,*(undefined1 *)(iVar1 + 0x20),0xd);
  }
  Open__15CmdButtonReportFv(iVar1);
  return;
}

/* JP: 0x00486e30  CmdComboKey::SetComboKeyGoods(short, CmdGoodsComboKey*)   [SetComboKeyGoods__11CmdComboKeyFsP16CmdGoodsComboKey]  size=0x188 */
void SetComboKeyGoods__11CmdComboKeyFsP16CmdGoodsComboKey(int param_1,short param_2,int param_3)

{
  undefined1 auStack_38 [8];
  int iStack_30;
  short sStack_20;
  int iStack_10;
  
  *(byte *)(param_3 + 0xe2) = *(byte *)(param_3 + 0xe2) & 0xfe;
  *(byte *)(param_3 + 0x162) = *(byte *)(param_3 + 0x162) & 0xfe;
  iStack_30 = param_1;
  sStack_20 = param_2;
  iStack_10 = param_3;
  SetMessage__8MenuTextFPcUiUcUc(param_3 + 0x50,*(undefined4 *)(param_3 + 0x1b0),*(byte *)(param_3 + 0xa8) & 7,0,0)
  ;
  if (sStack_20 == 1) {
    SetIcon__10MenuCommonFcP10MenuSprite((char)*(undefined2 *)(iStack_10 + 0x1ba),iStack_10 + 0x150);
    *(byte *)(iStack_10 + 0x162) = *(byte *)(iStack_10 + 0x162) & 0xfe | 1;
  }
  if (-1 < *(short *)(iStack_10 + 0x1b8)) {
    sprintf(auStack_38,*(undefined4 *)(*(int *)(iStack_30 + 0x24) + 0x10),
                    *(undefined2 *)(iStack_10 + 0x1b8));
    SetMessage__8MenuTextFPcUiUcUc(iStack_10 + 0xd0,auStack_38,*(byte *)(iStack_10 + 0x128) & 7,1,0);
    *(byte *)(iStack_10 + 0xe2) = *(byte *)(iStack_10 + 0xe2) & 0xfe | 1;
  }
  return;
}

/* JP: 0x00486fc0  CmdComboKey::SetSlot(short, short, short)   [SetSlot__11CmdComboKeyFsss]  size=0xe0 */
void SetSlot__11CmdComboKeyFsss
               (int param_1,undefined1 param_2,undefined1 param_3,undefined2 param_4)

{
  undefined1 *puVar1;
  
  puVar1 = (undefined1 *)
           (*(int *)(*(int *)(param_1 + 0x5c) + 4) + *(short *)(param_1 + 0xcb8) * 0x10 + 0xf44 +
           (*(short *)(param_1 + 0x136) + -1) * 4);
  *puVar1 = param_2;
  puVar1[1] = param_3;
  *(undefined2 *)(puVar1 + 2) = param_4;
  return;
}

/* JP: 0x004870a0  CmdComboKey::SelectSlot(short, MenuPlace*, MenuPlace*)   [SelectSlot__11CmdComboKeyFsP9MenuPlaceP9MenuPlace]  size=0x170 */
void SelectSlot__11CmdComboKeyFsP9MenuPlaceP9MenuPlace
               (int param_1,undefined2 param_2,int param_3,int param_4)

{
  short sVar1;
  undefined4 uVar2;
  
  if (param_4 != 0) {
    if (*(short *)(param_4 + 0x1e) == 0) {
      (**(code **)(*(int *)(*(int *)(param_1 + 0xc9c) + 8) + 0xc))();
      *(undefined4 *)(param_1 + 0xc9c) = 0;
    }
    else {
      (**(code **)(*(int *)(*(int *)(param_1 + 0xc98) + 8) + 0xc))();
      *(undefined4 *)(param_1 + 0xc98) = 0;
    }
  }
  if (param_3 != 0) {
    sVar1 = *(short *)(param_3 + 0x1e);
    if (sVar1 != 0) {
      CreateMask__11CmdComboKeyFs(param_1,sVar1 + -1);
      UpdateCommand__11CmdComboKeyFs(param_1,param_2);
    }
    else {
      UpdateCharacter__11CmdComboKeyFs(param_1,param_2);
    }
    uVar2 = UpdateFence__11CmdComboKeyFP8CmdFencesss
                      (param_1,*(undefined4 *)(param_1 + 0xca4),4,0,sVar1 != 0);
    *(undefined4 *)(param_1 + 0xca4) = uVar2;
  }
  Select__15CmdComboKeySlotFP11CmdComboKeyP9MenuPlaceP9MenuPlace
            (param_1 + 0x88,param_1,param_3,param_4);
  return;
}

/* JP: 0x00487210  CmdComboKey::Enter()   [Enter__11CmdComboKeyFv]  size=0x280 */
undefined8 Enter__11CmdComboKeyFv(int param_1)

{
  bool bVar1;
  undefined4 uVar2;
  undefined *puVar3;
  undefined1 uVar4;
  
  if (*(char *)(param_1 + 0x21) == '\0') {
    CreateScene__15CmdComboKeySlotFP11CmdComboKey(param_1 + 0x88,param_1);
    Initialize__9MenuSceneFPUcP9BufMemory(param_1 + 0xad0,*(undefined4 *)(*(int *)(param_1 + 0x54) + 0x34),0);
    Create__11CmdSubTitleFi(param_1 + 0xad0,2);
    Reset__11CmdSubTitleFv(param_1 + 0xad0);
    SetTitle__11CmdSubTitleFii(param_1 + 0xad0,0,0);
    SetTitle__11CmdSubTitleFii(param_1 + 0xad0,1,1);
    Open__10MenuWindowFUci(param_1 + 0xb28,*(byte *)(param_1 + 0xbd8) & 7,
                    *(undefined4 *)(*(int *)(param_1 + 0xb5c) + 0x10));
    (**(code **)(*(int *)(param_1 + 8) + 0x28))(param_1,1);
    SetTitle__11CmdTitleLogFPUci
              (*(undefined4 *)(param_1 + 0x60),*(undefined4 *)(*(int *)(param_1 + 0x54) + 0x10),0x20
              );
    Open__11CmdTitleLogFv(*(undefined4 *)(param_1 + 0x60));
    uVar4 = CreateBackGround__7CmdMenuFs(*(undefined4 *)(param_1 + 0x10),8);
    *(undefined1 *)(param_1 + 0x20) = uVar4;
    *(char *)(param_1 + 0x21) = *(char *)(param_1 + 0x21) + '\x01';
  }
  else if (*(char *)(param_1 + 0x21) == '\x01') {
    if ((*(char *)(param_1 + 0x130) == '\x01') || (*(char *)(param_1 + 0x130) == '\0')) {
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
      SetChengePCMode__10CmdPCSceneFUc(param_1,1);
      *(undefined1 *)(param_1 + 0x21) = 0;
      puVar3 = PTR_SelectSlot__11CmdComboKeyFv_0050da88;
      uVar2 = DAT_0050da84;
      *(undefined4 *)(param_1 + 0x7c) = _5377;
      *(undefined4 *)(param_1 + 0x80) = uVar2;
      *(undefined **)(param_1 + 0x84) = puVar3;
    }
  }
  return 0;
}

/* JP: 0x00487490  CmdComboKey::Exit()   [Exit__11CmdComboKeyFv]  size=0x28c */
undefined8 Exit__11CmdComboKeyFv(int param_1)

{
  int iVar1;
  bool bVar2;
  
  if (*(char *)(param_1 + 0x21) == '\0') {
    (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x14) + 0x28))
              (*(int *)(param_1 + 0x10),0,0,0xd);
    Leave__6CursorFv(*(undefined4 *)(param_1 + 0x18));
    iVar1 = *(int *)(param_1 + 0x78);
    Close__10MenuWindowFUci(iVar1 + 0x58,((ulong)*(byte *)(iVar1 + 0x108) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar1 + 0x8c) + 0x14));
    Close__10MenuWindowFUci(param_1 + 0x88,((ulong)*(byte *)(param_1 + 0x138) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(param_1 + 0xbc) + 0x14));
    Close__10MenuWindowFUci(param_1 + 0xb28,((ulong)*(byte *)(param_1 + 0xbd8) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(param_1 + 0xb5c) + 0x14));
    if (*(int *)(param_1 + 0xc98) == 0) {
      iVar1 = *(int *)(param_1 + 0xc9c);
      Close__10MenuWindowFUci(iVar1,((ulong)*(byte *)(iVar1 + 0xb0) & 0x3f) >> 3,
                      *(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x14));
    }
    else {
      iVar1 = *(int *)(param_1 + 0xc98);
      Close__10MenuWindowFUci(iVar1,((ulong)*(byte *)(iVar1 + 0xb0) & 0x3f) >> 3,
                      *(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x14));
    }
    iVar1 = *(int *)(param_1 + 0xca4);
    Close__10MenuWindowFUci(iVar1,((ulong)*(byte *)(iVar1 + 0xb0) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x14));
    *(char *)(param_1 + 0x21) = *(char *)(param_1 + 0x21) + '\x01';
  }
  else if (*(char *)(param_1 + 0x21) == '\x01') {
    if ((*(char *)(*(int *)(param_1 + 0x78) + 0x100) == '\x01') ||
       (*(char *)(*(int *)(param_1 + 0x78) + 0x100) == '\0')) {
      bVar2 = true;
    }
    else {
      bVar2 = false;
    }
    if (bVar2) {
      ReleaseOT__7MenuObjFv(param_1 + 0x88);
      ReleaseOT__7MenuObjFv(param_1 + 0xb28);
      (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x14) + 0x24))(*(int *)(param_1 + 0x10),0);
      DestroyScene__4MenuFP9MenuSceneb(*(undefined4 *)(param_1 + 0x10),param_1,1);
    }
  }
  return 0;
}

/* JP: 0x00487720  CmdComboKey::SelectSlot()   [SelectSlot__11CmdComboKeyFv]  size=0x420 */
undefined8 SelectSlot__11CmdComboKeyFv(int param_1)

{
  ushort uVar1;
  int iVar2;
  undefined *puVar3;
  undefined4 uVar4;
  int iVar5;
  undefined8 uVar6;
  short sVar7;
  
  uVar1 = *(ushort *)(*(int *)(param_1 + 0x10) + 0x48);
  iVar2 = *(int *)(*(int *)(param_1 + 0x18) + 0xec);
  if ((uVar1 & 0x2000) == 0) {
    if ((uVar1 & 0x4000) == 0) {
      iVar5 = MoveVertical__9MenuSceneFi(param_1,0);
      if (iVar2 != iVar5) {
        SelectSlot__11CmdComboKeyFsP9MenuPlaceP9MenuPlace(param_1,0,iVar5,iVar2);
        PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),0,0,0);
      }
    }
    else {
      if (*(int *)(param_1 + 0xc98) != 0) {
        iVar5 = *(int *)(param_1 + 0xc98);
        Close__10MenuWindowFUci(iVar5,((ulong)*(byte *)(iVar5 + 0xb0) & 0x3f) >> 3,
                        *(undefined4 *)(*(int *)(iVar5 + 0x34) + 0x14));
      }
      if (*(int *)(param_1 + 0xc9c) != 0) {
        iVar5 = *(int *)(param_1 + 0xc9c);
        Close__10MenuWindowFUci(iVar5,((ulong)*(byte *)(iVar5 + 0xb0) & 0x3f) >> 3,
                        *(undefined4 *)(*(int *)(iVar5 + 0x34) + 0x14));
      }
      Select__15CmdComboKeySlotFP11CmdComboKeyP9MenuPlaceP9MenuPlace(param_1 + 0x88,param_1,0,iVar2)
      ;
      Leave__6CursorFv(*(undefined4 *)(param_1 + 0x18));
      SetChengePCMode__10CmdPCSceneFUc(param_1,0);
      puVar3 = PTR_Exit__11CmdComboKeyFv_0050dab8;
      uVar4 = DAT_0050dab4;
      *(undefined4 *)(param_1 + 0x7c) = _5462;
      *(undefined4 *)(param_1 + 0x80) = uVar4;
      *(undefined **)(param_1 + 0x84) = puVar3;
      PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),3,0,0);
    }
  }
  else {
    if (*(short *)(iVar2 + 0x1e) == 0) {
      uVar6 = GetPlace__10MenuWindowFss(*(undefined4 *)(param_1 + 0xc9c),0,0);
      Select__20CmdComboKeyCharacterFP11CmdComboKeyP9MenuPlaceP9MenuPlace
                (*(undefined4 *)(param_1 + 0xc9c),param_1,uVar6,0);
      Select__6CursorFP9MenuPlace(*(undefined4 *)(param_1 + 0x18),uVar6);
      StartButtonReport__11CmdComboKeyFv(param_1);
      puVar3 = PTR_SelectCharacter__11CmdComboKeyFv_0050daa8;
      uVar4 = DAT_0050daa4;
      *(undefined4 *)(param_1 + 0x7c) = _5453;
      *(undefined4 *)(param_1 + 0x80) = uVar4;
      *(undefined **)(param_1 + 0x84) = puVar3;
    }
    else {
      *(undefined2 *)(param_1 + 0x136) = *(undefined2 *)(iVar2 + 0x1e);
      UpdateScene__18CmdComboKeyCommandFP11CmdComboKeyss
                (*(undefined4 *)(param_1 + 0xc98),param_1,*(undefined2 *)(param_1 + 0xcb8),
                 *(short *)(iVar2 + 0x16) != 0);
      uVar6 = GetPlace__10MenuWindowFss(*(undefined4 *)(param_1 + 0xc98),0,0);
      Select__18CmdComboKeyCommandFP11CmdComboKeyP9MenuPlaceP9MenuPlace
                (*(undefined4 *)(param_1 + 0xc98),param_1,uVar6,0);
      Select__6CursorFP9MenuPlace(*(undefined4 *)(param_1 + 0x18),uVar6);
      sVar7 = *(short *)((int)uVar6 + 0x16);
      UpdateGoods__11CmdComboKeyFss(param_1,1,sVar7);
      if (sVar7 < 0) {
        sVar7 = 4;
      }
      uVar4 = UpdateFence__11CmdComboKeyFP8CmdFencesss
                        (param_1,*(undefined4 *)(param_1 + 0xca8),5,1,sVar7 << 1);
      *(undefined4 *)(param_1 + 0xca8) = uVar4;
      puVar3 = PTR_SelectCommand__11CmdComboKeyFv_0050da98;
      uVar4 = DAT_0050da94;
      *(undefined4 *)(param_1 + 0x7c) = _5450;
      *(undefined4 *)(param_1 + 0x80) = uVar4;
      *(undefined **)(param_1 + 0x84) = puVar3;
    }
    SetChengePCMode__10CmdPCSceneFUc(param_1,0);
    PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),2,0,0);
  }
  return 0;
}

/* JP: 0x00487b40  CmdComboKey::SelectCharacter()   [SelectCharacter__11CmdComboKeyFv]  size=0x290 */
undefined8 SelectCharacter__11CmdComboKeyFv(int param_1)

{
  ushort uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined *puVar4;
  int iVar5;
  undefined8 uVar6;
  undefined4 uVar7;
  
  uVar1 = *(ushort *)(*(int *)(param_1 + 0x10) + 0x48);
  iVar2 = *(int *)(*(int *)(param_1 + 0x18) + 0xec);
  if ((uVar1 & 0x6000) == 0) {
    iVar5 = MoveVertical__9MenuSceneFi(param_1,1);
    if (iVar2 != iVar5) {
      Select__20CmdComboKeyCharacterFP11CmdComboKeyP9MenuPlaceP9MenuPlace
                (*(undefined4 *)(param_1 + 0xc9c),param_1,iVar5,iVar2);
      UpdateScene__15CmdComboKeySlotFP11CmdComboKeyss
                (param_1 + 0x88,param_1,*(undefined2 *)(iVar5 + 0x16),0);
      PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),0,0,0);
    }
  }
  else {
    uVar7 = 3;
    if ((uVar1 & 0x2000) != 0) {
      *(undefined2 *)(param_1 + 0xcb8) = *(undefined2 *)(iVar2 + 0x16);
      uVar7 = 2;
    }
    UpdateScene__15CmdComboKeySlotFP11CmdComboKeyss
              (param_1 + 0x88,param_1,*(undefined2 *)(param_1 + 0xcb8),1);
    uVar6 = GetPlace__10MenuWindowFss(param_1 + 0x88,0,0);
    Select__6CursorFP9MenuPlace(*(undefined4 *)(param_1 + 0x18),uVar6);
    Select__15CmdComboKeySlotFP11CmdComboKeyP9MenuPlaceP9MenuPlace(param_1 + 0x88,param_1,uVar6,0);
    Select__20CmdComboKeyCharacterFP11CmdComboKeyP9MenuPlaceP9MenuPlace
              (*(undefined4 *)(param_1 + 0xc9c),param_1,0,iVar2);
    SetScroll__10MenuWindowFss(*(undefined4 *)(param_1 + 0xc9c),0,0);
    iVar2 = *(int *)(param_1 + 0x68);
    Close__10MenuWindowFUci(iVar2 + 0x58,((ulong)*(byte *)(iVar2 + 0x108) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar2 + 0x8c) + 0x14));
    SetChengePCMode__10CmdPCSceneFUc(param_1,1);
    puVar4 = PTR_SelectSlot__11CmdComboKeyFv_0050dac8;
    uVar3 = DAT_0050dac4;
    *(undefined4 *)(param_1 + 0x7c) = _5505;
    *(undefined4 *)(param_1 + 0x80) = uVar3;
    *(undefined **)(param_1 + 0x84) = puVar4;
    PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),uVar7,0,0);
  }
  return 0;
}

/* JP: 0x00487dd0  CmdComboKey::SelectCommand()   [SelectCommand__11CmdComboKeyFv]  size=0x414 */
undefined8 SelectCommand__11CmdComboKeyFv(int param_1)

{
  ushort uVar1;
  int iVar2;
  undefined *puVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 uVar6;
  undefined8 uVar7;
  short sVar8;
  
  uVar1 = *(ushort *)(*(int *)(param_1 + 0x10) + 0x48);
  iVar2 = *(int *)(*(int *)(param_1 + 0x18) + 0xec);
  if ((uVar1 & 0x6000) == 0) {
    iVar5 = MoveVertical__9MenuSceneFi(param_1,0);
    if (iVar2 != iVar5) {
      sVar8 = *(short *)(iVar5 + 0x16);
      Select__18CmdComboKeyCommandFP11CmdComboKeyP9MenuPlaceP9MenuPlace
                (*(undefined4 *)(param_1 + 0xc98),param_1,iVar5,iVar2);
      UpdateScene__16CmdComboKeyGoodsFP11CmdComboKeys
                (*(undefined4 *)(param_1 + 0xca0),param_1,*(undefined2 *)(iVar5 + 0x16));
      if (sVar8 < 0) {
        sVar8 = 4;
      }
      uVar6 = UpdateFence__11CmdComboKeyFP8CmdFencesss
                        (param_1,*(undefined4 *)(param_1 + 0xca8),5,0,sVar8 << 1);
      *(undefined4 *)(param_1 + 0xca8) = uVar6;
      PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),0,0,0);
    }
  }
  else {
    uVar6 = 3;
    sVar8 = *(short *)(param_1 + 0x136);
    if ((uVar1 & 0x2000) != 0) {
      if (-1 < *(short *)(iVar2 + 0x16)) {
        uVar7 = GetPlace__10MenuWindowFss(*(undefined4 *)(param_1 + 0xca0),0,0);
        Select__6CursorFP9MenuPlace(*(undefined4 *)(param_1 + 0x18),uVar7);
        Select__16CmdComboKeyGoodsFP11CmdComboKeyP9MenuPlaceP9MenuPlace
                  (*(undefined4 *)(param_1 + 0xca0),param_1,uVar7,0);
        *(undefined2 *)(param_1 + 0xcba) = *(undefined2 *)(iVar2 + 0x16);
        StartButtonReport__11CmdComboKeyFv(param_1);
        puVar3 = PTR_SelectComboKey__11CmdComboKeyFv_0050dad8;
        uVar6 = DAT_0050dad4;
        *(undefined4 *)(param_1 + 0x7c) = _5550;
        *(undefined4 *)(param_1 + 0x80) = uVar6;
        *(undefined **)(param_1 + 0x84) = puVar3;
        PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),2,0,0);
        return 0;
      }
      SetSlot__11CmdComboKeyFsss(param_1,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff);
      UpdateScene__15CmdComboKeySlotFP11CmdComboKeyss
                (param_1 + 0x88,param_1,*(undefined2 *)(param_1 + 0xcb8),0);
      CreateMask__11CmdComboKeyFs(param_1,sVar8 + -1);
      uVar6 = 2;
    }
    uVar7 = GetPlace__10MenuWindowFss(param_1 + 0x88,0,sVar8);
    Select__6CursorFP9MenuPlace(*(undefined4 *)(param_1 + 0x18),uVar7);
    Select__15CmdComboKeySlotFP11CmdComboKeyP9MenuPlaceP9MenuPlace(param_1 + 0x88,param_1,uVar7,0);
    UpdateScene__18CmdComboKeyCommandFP11CmdComboKeyss
              (*(undefined4 *)(param_1 + 0xc98),param_1,*(undefined2 *)(param_1 + 0xcb8),0);
    (**(code **)(*(int *)(*(int *)(param_1 + 0xca0) + 8) + 0xc))();
    *(undefined4 *)(param_1 + 0xca0) = 0;
    (**(code **)(*(int *)(*(int *)(param_1 + 0xca8) + 8) + 0xc))();
    *(undefined4 *)(param_1 + 0xca8) = 0;
    SetChengePCMode__10CmdPCSceneFUc(param_1,1);
    puVar3 = PTR_SelectSlot__11CmdComboKeyFv_0050dae8;
    uVar4 = DAT_0050dae4;
    *(undefined4 *)(param_1 + 0x7c) = _5552;
    *(undefined4 *)(param_1 + 0x80) = uVar4;
    *(undefined **)(param_1 + 0x84) = puVar3;
    PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),uVar6,0,0);
  }
  return 0;
}

/* JP: 0x004881f0  CmdComboKey::SelectComboKey()   [SelectComboKey__11CmdComboKeyFv]  size=0x420 */
undefined8 SelectComboKey__11CmdComboKeyFv(int param_1)

{
  short sVar1;
  ushort uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined *puVar5;
  int iVar6;
  undefined8 uVar7;
  
  uVar2 = *(ushort *)(*(int *)(param_1 + 0x10) + 0x48);
  iVar3 = *(int *)(*(int *)(param_1 + 0x18) + 0xec);
  if ((uVar2 & 0x2000) == 0) {
    if ((uVar2 & 0x4000) == 0) {
      iVar6 = MoveVertical__9MenuSceneFi(param_1,1);
      if (iVar3 != iVar6) {
        Select__16CmdComboKeyGoodsFP11CmdComboKeyP9MenuPlaceP9MenuPlace
                  (*(undefined4 *)(param_1 + 0xca0),param_1,iVar6,iVar3);
        PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),0,0,0);
      }
    }
    else {
      uVar7 = GetPlace__10MenuWindowFs(*(undefined4 *)(param_1 + 0xc98),*(undefined2 *)(param_1 + 0xcba));
      Select__6CursorFP9MenuPlace(*(undefined4 *)(param_1 + 0x18),uVar7);
      Select__18CmdComboKeyCommandFP11CmdComboKeyP9MenuPlaceP9MenuPlace
                (*(undefined4 *)(param_1 + 0xc98),param_1,uVar7,0);
      Select__16CmdComboKeyGoodsFP11CmdComboKeyP9MenuPlaceP9MenuPlace
                (*(undefined4 *)(param_1 + 0xca0),param_1,0,iVar3);
      SetScroll__10MenuWindowFss(*(undefined4 *)(param_1 + 0xca0),0,0);
      iVar3 = *(int *)(param_1 + 0x68);
      Close__10MenuWindowFUci(iVar3 + 0x58,((ulong)*(byte *)(iVar3 + 0x108) & 0x3f) >> 3,
                      *(undefined4 *)(*(int *)(iVar3 + 0x8c) + 0x14));
      puVar5 = PTR_SelectCommand__11CmdComboKeyFv_0050db08;
      uVar4 = DAT_0050db04;
      *(undefined4 *)(param_1 + 0x7c) = _5600;
      *(undefined4 *)(param_1 + 0x80) = uVar4;
      *(undefined **)(param_1 + 0x84) = puVar5;
      PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),3,0,0);
    }
  }
  else {
    sVar1 = *(short *)(param_1 + 0x136);
    SetSlot__11CmdComboKeyFsss
              (param_1,*(undefined2 *)(param_1 + 0xcba),
               *(undefined2 *)
                (*(int *)(*(int *)(param_1 + 0xca0) + 0x124) +
                 (*(short *)(iVar3 + 0x1e) * 0x70 - (int)*(short *)(iVar3 + 0x1e)) * 4 + 0x1ba),
               *(undefined2 *)(iVar3 + 0x16));
    CreateMask__11CmdComboKeyFs(param_1,sVar1 + -1);
    UpdateCommand__11CmdComboKeyFs(param_1,0);
    UpdateScene__15CmdComboKeySlotFP11CmdComboKeyss
              (param_1 + 0x88,param_1,*(undefined2 *)(param_1 + 0xcb8),0);
    uVar7 = GetPlace__10MenuWindowFss(param_1 + 0x88,0,sVar1);
    Select__6CursorFP9MenuPlace(*(undefined4 *)(param_1 + 0x18),uVar7);
    Select__15CmdComboKeySlotFP11CmdComboKeyP9MenuPlaceP9MenuPlace(param_1 + 0x88,param_1,uVar7,0);
    (**(code **)(*(int *)(*(int *)(param_1 + 0xca0) + 8) + 0xc))();
    *(undefined4 *)(param_1 + 0xca0) = 0;
    if (*(int *)(param_1 + 0xca8) != 0) {
      (**(code **)(*(int *)(*(int *)(param_1 + 0xca8) + 8) + 0xc))();
      *(undefined4 *)(param_1 + 0xca8) = 0;
    }
    iVar3 = *(int *)(param_1 + 0x68);
    Close__10MenuWindowFUci(iVar3 + 0x58,((ulong)*(byte *)(iVar3 + 0x108) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar3 + 0x8c) + 0x14));
    SetChengePCMode__10CmdPCSceneFUc(param_1,1);
    puVar5 = PTR_SelectSlot__11CmdComboKeyFv_0050daf8;
    uVar4 = DAT_0050daf4;
    *(undefined4 *)(param_1 + 0x7c) = _5595;
    *(undefined4 *)(param_1 + 0x80) = uVar4;
    *(undefined **)(param_1 + 0x84) = puVar5;
    PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),2,0,0);
  }
  return 0;
}
