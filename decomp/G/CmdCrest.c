/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdCrest   functions: 26
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdCrest.md).
 */

/* JP: 0x00490ca0  CmdCrest::CmdCrest()   [__ct__8CmdCrestFv]  size=0xd8 */
int __ct__8CmdCrestFv(int param_1)

{
  __ct__10CmdPCSceneFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__8CmdCrest;
  __ct__9MenuSceneFv(param_1 + 0x88);
  __ct__9MenuSceneFv(param_1 + 0xe0);
  __construct_array(param_1 + 0x138,0x2676b0,0x2677a0,0x40,3);
  __ct__10CmdSubMenuFv(param_1 + 0x1f8);
  __ct__14CmdCrestPCInfoFv(param_1 + 0x350);
  *(undefined4 *)(param_1 + 0x990) = 0;
  *(undefined4 *)(param_1 + 0x994) = 0;
  *(undefined4 *)(param_1 + 0x998) = 0;
  *(undefined4 *)(param_1 + 0x99c) = 0;
  *(undefined4 *)(param_1 + 0x9b0) = 0;
  *(undefined1 *)(param_1 + 0x9b9) = 6;
  return param_1;
}

/* JP: 0x00490d80  CmdCrest::~CmdCrest()   [__dt__8CmdCrestFv]  size=0x204 */
int __dt__8CmdCrestFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__8CmdCrest;
    if (*(int *)(param_1 + 0x9b0) != 0) {
      __dla__FPv(*(undefined4 *)(param_1 + 0x9b0));
    }
    if (*(int *)(param_1 + 0x990) != 0) {
      ReleaseOT__7MenuObjFv(*(undefined4 *)(param_1 + 0x990));
      (**(code **)(*(int *)(*(int *)(param_1 + 0x990) + 8) + 0xc))();
      *(undefined4 *)(param_1 + 0x990) = 0;
    }
    if (*(int *)(param_1 + 0x994) != 0) {
      ReleaseOT__7MenuObjFv(*(undefined4 *)(param_1 + 0x994));
      (**(code **)(*(int *)(*(int *)(param_1 + 0x994) + 8) + 0xc))();
      *(undefined4 *)(param_1 + 0x994) = 0;
    }
    if (*(int *)(param_1 + 0x998) != 0) {
      ReleaseOT__7MenuObjFv(*(undefined4 *)(param_1 + 0x998));
      (**(code **)(*(int *)(*(int *)(param_1 + 0x998) + 8) + 0xc))();
      *(undefined4 *)(param_1 + 0x998) = 0;
    }
    if (*(int *)(param_1 + 0x99c) != 0) {
      ReleaseOT__7MenuObjFv(*(undefined4 *)(param_1 + 0x99c));
      (**(code **)(*(int *)(*(int *)(param_1 + 0x99c) + 8) + 0xc))();
      *(undefined4 *)(param_1 + 0x99c) = 0;
    }
    __dt__14CmdCrestPCInfoFv(param_1 + 0x350,0xffffffffffffffff);
    __dt__10CmdSubMenuFv(param_1 + 0x1f8,0xffffffffffffffff);
    __destroy_arr(param_1 + 0x138,0x2677a0,0x40,3);
    __dt__9MenuSceneFv(param_1 + 0xe0,0xffffffffffffffff);
    __dt__9MenuSceneFv(param_1 + 0x88,0xffffffffffffffff);
    __dt__10CmdPCSceneFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x00490f90  CmdCrest::GetReady()   [GetReady__8CmdCrestFv]  size=0x400 */
undefined4 GetReady__8CmdCrestFv(int param_1)

{
  undefined *puVar1;
  undefined2 uVar2;
  short sVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  ushort uVar7;
  
  iVar4 = *(int *)(param_1 + 0x10);
  uVar2 = GetRegCnt__9RegDatApiFii(0x38,0xffffffffffffffff);
  *(undefined2 *)(param_1 + 0x9a4) = uVar2;
  uVar2 = GetRegCnt__9RegDatApiFii(0x37,0xffffffffffffffff);
  *(undefined2 *)(param_1 + 0x9a6) = uVar2;
  iVar4 = iVar4 + 0x28;
  iVar5 = Find__13MenuDataTableFs(iVar4,0xc);
  *(int *)(param_1 + 0x9a8) = iVar5 + 0x10;
  iVar4 = Find__13MenuDataTableFs(iVar4,0x17);
  *(int *)(param_1 + 0x9ac) = iVar4 + 0x10;
  uVar6 = __nwa__FUi((int)*(short *)(param_1 + 0x9a4) + (int)*(short *)(param_1 + 0x9a6));
  *(undefined4 *)(param_1 + 0x9b0) = uVar6;
  *(int *)(param_1 + 0x9b4) = *(int *)(param_1 + 0x9b0) + (int)*(short *)(param_1 + 0x9a4);
  for (uVar7 = 3; (short)uVar7 < 8; uVar7 = uVar7 + 1) {
    Convert__13MenuDataTableFPUci(*(undefined4 *)((uint)uVar7 * 0xc + *(int *)(param_1 + 0x54) + 0x10),0);
  }
  CreatePCInfo__10CmdPCSceneFPUc(param_1,*(undefined4 *)(*(int *)(param_1 + 0x54) + 0x34));
  Initialize__9MenuSceneFPUcP9BufMemory(param_1 + 0x1f8,*(undefined4 *)(*(int *)(param_1 + 0x54) + 0x40),0);
  CreateScene__10CmdSubMenuFsP9MSDSystem(param_1 + 0x1f8,3,*(int *)(param_1 + 0x28) + 0x10);
  Initialize__9MenuSceneFPUcP9BufMemory(param_1 + 0x88,*(undefined4 *)(*(int *)(param_1 + 0x54) + 0x4c),0);
  Initialize__9MenuSceneFPUcP9BufMemory(param_1 + 0xe0,*(undefined4 *)(*(int *)(param_1 + 0x54) + 0x58),0);
  iVar4 = param_1 + 0x138;
  for (uVar7 = 0; (short)uVar7 < 3; uVar7 = uVar7 + 1) {
    Create__11MenuTextureFPUc6GS_PSMUii(iVar4,*(undefined4 *)((uint)uVar7 * 0xc + *(int *)(param_1 + 0xdc) + 0x10),0x30,
                    0,0);
    iVar4 = iVar4 + 0x40;
  }
  CreateScene__14CmdCrestPCInfoFP8CmdCrest(param_1 + 0x350,param_1);
  *(undefined2 *)(*(int *)(param_1 + 0x18) + 0x32) = 0;
  sVar3 = GetLayerCount__10CmdPCSceneFs(param_1,0);
  if (sVar3 < 2) {
    *(byte *)(param_1 + 0x23) = *(byte *)(param_1 + 0x23) & 0xfe;
  }
  SetChengePCMode__10CmdPCSceneFUc(param_1,0);
  CreateEquipCrest__8CmdCrestFv(param_1);
  CreateMagic__5CmdPCFP8CmdPartysPc
            (*(undefined4 *)(param_1 + 0x70),*(undefined4 *)(param_1 + 0x5c),
             *(undefined2 *)(param_1 + 0x9a4),*(undefined4 *)(param_1 + 0x9b0));
  *(undefined1 *)(param_1 + 0x9bb) = *(undefined1 *)(*(int *)(param_1 + 0x18) + 0xf9);
  puVar1 = PTR_Enter__8CmdCrestFv_0050dbb8;
  uVar6 = DAT_0050dbb4;
  *(undefined4 *)(param_1 + 0x7c) = _5127;
  *(undefined4 *)(param_1 + 0x80) = uVar6;
  *(undefined **)(param_1 + 0x84) = puVar1;
  return 1;
}

/* JP: 0x00491390  CmdCrest::Run()   [Run__8CmdCrestFv]  size=0x104 */
undefined4 Run__8CmdCrestFv(int param_1)

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

/* JP: 0x004914a0  CmdCrest::Update(short)   [Update__8CmdCrestFs]  size=0x31c */
void Update__8CmdCrestFs(int param_1,short param_2)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  undefined2 uVar4;
  float fVar5;
  undefined2 uStack_22;
  
  uVar4 = 0;
  iVar3 = *(int *)(*(int *)(param_1 + 0x18) + 0xec);
  piVar1 = *(int **)(param_1 + 0x70);
  CreateMagic__5CmdPCFP8CmdPartysPc
            (piVar1,*(undefined4 *)(param_1 + 0x5c),*(undefined2 *)(param_1 + 0x9a4),
             *(undefined4 *)(param_1 + 0x9b0));
  UpdatePCInfo__10CmdPCSceneFsP11CmdPCStatus(param_1,param_2,0);
  UpdateScene__14CmdCrestPCInfoFP8CmdCrests(param_1 + 0x350,param_1,0xffffffffffffffff);
  if (param_2 != 0) {
    Open__10MenuWindowFUci(param_1 + 0x350,*(byte *)(param_1 + 0x400) & 7,
                    *(undefined4 *)(*(int *)(param_1 + 900) + 0x10));
  }
  if (*(int *)(param_1 + 0x990) != 0) {
    iVar2 = *(int *)(param_1 + 0x990);
    fVar5 = (float)GetTargetY__10MenuWindowCFv(iVar2);
    uStack_22 = (undefined2)(int)(-fVar5 / *(float *)(*(int *)(iVar2 + 0x40) + 0x20));
  }
  UpdateSlot__8CmdCrestFs(param_1,param_2);
  if (*(char *)(param_1 + 0x9b9) == '\0') {
    SetScroll__10MenuWindowFss(*(undefined4 *)(param_1 + 0x990),0,uStack_22);
    FinishScroll__10MenuWindowFv(*(undefined4 *)(param_1 + 0x990));
    if (-1 < (long)((ulong)*(byte *)(iVar3 + 0x21) << 0x3e)) {
      iVar3 = SetCursor__10MenuWindowFP6Cursori(*(undefined4 *)(param_1 + 0x990),*(undefined4 *)(param_1 + 0x18),2);
      Select__6CursorFP9MenuPlace(*(undefined4 *)(param_1 + 0x18),iVar3);
    }
    UpdateScene__13CmdCrestMagicFP8CmdCrestsc
              (*(undefined4 *)(param_1 + 0x998),param_1,*(undefined2 *)(iVar3 + 0x16),0);
    Select__13CmdGoodsCrestFP9MenuSceneP7CmdNoteP9MenuGroupP9MenuGroup
              (*(undefined4 *)(param_1 + 0x990),param_1 + 0x88,*(undefined4 *)(param_1 + 100),iVar3,
               0);
    uVar4 = *(undefined2 *)(iVar3 + 0x22);
  }
  else if ((*(char *)(param_1 + 0x9b9) == '\x02') && (*(char *)(param_1 + 0x9b8) != '\0')) {
    SetExplanation__7CmdNoteFPCce
              (*(undefined4 *)(param_1 + 100),
               *(undefined4 *)
                ((uint)*(ushort *)(iVar3 + 0x22) * 0xc + *(int *)(param_1 + 0x28) + 0x14),
               *piVar1 + 10);
  }
  UpdateGoods__8CmdCrestFsss(param_1,param_2,uVar4,0);
  return;
}

/* JP: 0x004917c0  CmdCrest::UpdateSlot(short)   [UpdateSlot__8CmdCrestFs]  size=0x27c */
void UpdateSlot__8CmdCrestFs(int param_1,short param_2)

{
  undefined1 uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  long lVar5;
  short sVar6;
  char *pcVar7;
  
  if (*(int *)(param_1 + 0x990) == 0) {
    lVar5 = __nw__FUi(0x1c8);
    uVar3 = 0;
    if (lVar5 != 0) {
      uVar3 = __ct__13CmdGoodsCrestFv(lVar5);
    }
    *(undefined4 *)(param_1 + 0x990) = uVar3;
    CreateScene__13CmdGoodsCrestFP9MenuScenesss
              (*(undefined4 *)(param_1 + 0x990),param_1 + 0x88,0,8,0);
    CreateImage__13CmdGoodsCrestFP11MenuTexture(*(undefined4 *)(param_1 + 0x990),param_1 + 0x138);
  }
  uVar1 = *(undefined1 *)(**(int **)(param_1 + 0x70) + 0x2c);
  Reset__13CmdGoodsCrestFv(*(undefined4 *)(param_1 + 0x990));
  sVar6 = 0;
  iVar2 = **(int **)(param_1 + 0x70);
  for (pcVar7 = (char *)(iVar2 + 0x32); pcVar7 < (char *)(iVar2 + 0x3a); pcVar7 = pcVar7 + 1) {
    iVar4 = SetCrest__13CmdGoodsCrestFP9MenuScenesii
                      (*(undefined4 *)(param_1 + 0x990),param_1 + 0x88,*pcVar7,999,uVar1);
    if (*pcVar7 < '\0') {
      if (sVar6 != 0) {
        *(byte *)(iVar4 + 0x21) = *(byte *)(iVar4 + 0x21) & 0xfd;
      }
      sVar6 = sVar6 + 1;
    }
  }
  Start__13CmdGoodsCrestFv(*(undefined4 *)(param_1 + 0x990));
  SetScroll__10MenuWindowFss(*(undefined4 *)(param_1 + 0x990),0,0);
  *(byte *)(*(int *)(param_1 + 0x990) + 0x12) =
       *(byte *)(*(int *)(param_1 + 0x990) + 0x12) & 0xfe | 1;
  if (param_2 != 0) {
    iVar2 = *(int *)(param_1 + 0x990);
    Open__10MenuWindowFUci(iVar2,*(byte *)(iVar2 + 0xb0) & 7,*(undefined4 *)(*(int *)(iVar2 + 0x34) + 0x10)
                   );
  }
  return;
}

/* JP: 0x00491a40  CmdCrest::UpdateGoods(short, short, short)   [UpdateGoods__8CmdCrestFsss]  size=0x3c4 */
void UpdateGoods__8CmdCrestFsss(int param_1,short param_2,short param_3,short param_4)

{
  undefined1 uVar1;
  byte bVar2;
  short sVar3;
  int iVar4;
  int *piVar5;
  ushort uVar6;
  undefined4 uVar7;
  uint uVar8;
  int iVar9;
  uint uVar10;
  long lVar11;
  ulong uVar12;
  uint uVar13;
  
  if (*(int *)(param_1 + 0x994) == 0) {
    lVar11 = __nw__FUi(0x1c8);
    uVar7 = 0;
    if (lVar11 != 0) {
      uVar7 = __ct__13CmdGoodsCrestFv(lVar11);
    }
    *(undefined4 *)(param_1 + 0x994) = uVar7;
    CreateScene__13CmdGoodsCrestFP9MenuScenesss
              (*(undefined4 *)(param_1 + 0x994),param_1 + 0x88,1,*(undefined2 *)(param_1 + 0x9a6),1)
    ;
    CreateImage__13CmdGoodsCrestFP11MenuTexture(*(undefined4 *)(param_1 + 0x994),param_1 + 0x138);
  }
  iVar4 = *(int *)(param_1 + 0x5c);
  piVar5 = *(int **)(param_1 + 0x70);
  uVar6 = GetRestCrestSlot__5CmdPCFv(piVar5);
  uVar1 = *(undefined1 *)(*piVar5 + 0x2c);
  bVar2 = *(byte *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x28d);
  Reset__13CmdGoodsCrestFv(*(undefined4 *)(param_1 + 0x994));
  if (param_4 != 0) {
    SetCrest__13CmdGoodsCrestFP9MenuScenesii
              (*(undefined4 *)(param_1 + 0x994),param_1 + 0x88,0xfffffffffffffffe,99,
               0xffffffffffffffff);
  }
  uVar13 = *(uint *)(param_1 + 0x9ac);
  uVar8 = uVar13 + *(short *)(param_1 + 0x9a6) * 8;
  for (; uVar13 < uVar8; uVar13 = uVar13 + 8) {
    sVar3 = *(short *)(uVar13 + (uint)bVar2 * 2);
    if (-1 < sVar3) {
      iVar9 = (int)sVar3;
      if (sVar3 < 0) {
        iVar9 = iVar9 + 7;
      }
      uVar12 = (long)sVar3 & 7;
      uVar10 = (uint)uVar12;
      if (((long)sVar3 < 0) && (uVar12 != 0)) {
        uVar10 = uVar10 - 8;
      }
      if ((((int)(uint)*(byte *)(*(int *)(iVar4 + 8) + (iVar9 >> 3) + 0x160) >> (uVar10 & 0x1f) & 1U
           ) != 0) && (*(char *)(*(int *)(param_1 + 0x9b4) + (int)sVar3) == '\0')) {
        SetCrest__13CmdGoodsCrestFP9MenuScenesii
                  (*(undefined4 *)(param_1 + 0x994),param_1 + 0x88,sVar3,param_3 + (uVar6 & 0xff),
                   uVar1);
      }
    }
  }
  if ((*(short *)(*(int *)(param_1 + 0x994) + 0x1be) == 0) && (param_4 == 0)) {
    SetCrest__13CmdGoodsCrestFP9MenuScenesii
              (*(undefined4 *)(param_1 + 0x994),param_1 + 0x88,0xfffffffffffffffd,99,
               0xffffffffffffffff);
  }
  Start__13CmdGoodsCrestFv(*(undefined4 *)(param_1 + 0x994));
  SetScroll__10MenuWindowFss(*(undefined4 *)(param_1 + 0x994),0,0);
  *(byte *)(*(int *)(param_1 + 0x994) + 0x12) =
       *(byte *)(*(int *)(param_1 + 0x994) + 0x12) & 0xfe | 1;
  if (param_2 != 0) {
    iVar4 = *(int *)(param_1 + 0x994);
    Open__10MenuWindowFUci(iVar4,*(byte *)(iVar4 + 0xb0) & 7,*(undefined4 *)(*(int *)(iVar4 + 0x34) + 0x10)
                   );
  }
  return;
}

/* JP: 0x00491e10  CmdCrest::UpdateCrestMagic(short, short, char)   [UpdateCrestMagic__8CmdCrestFssc]  size=0x114 */
void UpdateCrestMagic__8CmdCrestFssc
               (int param_1,short param_2,undefined2 param_3,undefined1 param_4)

{
  int iVar1;
  undefined4 uVar2;
  long lVar3;
  
  if (*(int *)(param_1 + 0x998) == 0) {
    lVar3 = __nw__FUi(0xca0);
    uVar2 = 0;
    if (lVar3 != 0) {
      uVar2 = __ct__13CmdCrestMagicFv(lVar3);
    }
    *(undefined4 *)(param_1 + 0x998) = uVar2;
    CreateScene__13CmdCrestMagicFP8CmdCrestP11MenuTexture
              (*(undefined4 *)(param_1 + 0x998),param_1,param_1 + 0x138);
  }
  UpdateScene__13CmdCrestMagicFP8CmdCrestsc
            (*(undefined4 *)(param_1 + 0x998),param_1,param_3,param_4);
  *(byte *)(*(int *)(param_1 + 0x998) + 0x12) =
       *(byte *)(*(int *)(param_1 + 0x998) + 0x12) & 0xfe | 1;
  if (param_2 != 0) {
    iVar1 = *(int *)(param_1 + 0x998);
    Open__10MenuWindowFUci(iVar1,*(byte *)(iVar1 + 0xb0) & 7,*(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x10)
                   );
  }
  return;
}

/* JP: 0x00491f30  CmdCrest::CreateEquipCrest()   [CreateEquipCrest__8CmdCrestFv]  size=0x148 */
void CreateEquipCrest__8CmdCrestFv(int param_1)

{
  short sVar1;
  int iVar2;
  char *pcVar3;
  char *pcVar4;
  int *piVar5;
  int *piVar6;
  
  memset(*(undefined4 *)(param_1 + 0x9b4),0,*(undefined2 *)(param_1 + 0x9a6));
  piVar5 = (int *)(*(int *)(param_1 + 0x5c) + 0x30);
  sVar1 = *(short *)(*(int *)(param_1 + 0x5c) + 0xe);
  piVar6 = piVar5 + sVar1 * 0x12 + (int)sVar1;
  for (; piVar5 < piVar6; piVar5 = piVar5 + 0x13) {
    iVar2 = *piVar5;
    for (pcVar4 = (char *)(iVar2 + 0x32); pcVar4 < (char *)(iVar2 + 0x3a); pcVar4 = pcVar4 + 1) {
      if (-1 < *pcVar4) {
        pcVar3 = (char *)(*(int *)(param_1 + 0x9b4) + (int)*pcVar4);
        *pcVar3 = *pcVar3 + '\x01';
      }
    }
  }
  return;
}

/* JP: 0x00492080  CmdCrest::Disarm(short)   [Disarm__8CmdCrestFs]  size=0x190 */
void Disarm__8CmdCrestFs(int param_1,short param_2)

{
  short sVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  uint uVar5;
  undefined1 *puVar6;
  
  uVar5 = 0xffff;
  if (-1 < param_2) {
    uVar5 = 1 << ((int)param_2 & 0x1fU) & 0xffff;
  }
  piVar3 = (int *)(*(int *)(param_1 + 0x5c) + 0x30);
  sVar1 = *(short *)(*(int *)(param_1 + 0x5c) + 0xe);
  piVar4 = piVar3 + sVar1 * 0x12 + (int)sVar1;
  for (; piVar3 < piVar4; piVar3 = piVar3 + 0x13) {
    if ((uVar5 & 1 << (*(byte *)(*piVar3 + 2) & 0x1f)) != 0) {
      iVar2 = *piVar3;
      for (puVar6 = (undefined1 *)(iVar2 + 0x32); puVar6 < (undefined1 *)(iVar2 + 0x3a);
          puVar6 = puVar6 + 1) {
        *puVar6 = 0xff;
      }
    }
  }
  return;
}

/* JP: 0x00492210  CmdCrest::Recommend()   [Recommend__8CmdCrestFv]  size=0x30c */
void Recommend__8CmdCrestFv(int param_1)

{
  short sVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  ushort uVar5;
  ushort uVar6;
  int iVar7;
  char *pcVar8;
  uint uVar9;
  int iVar10;
  uint uVar11;
  ulong uVar12;
  char *pcVar13;
  uint uVar14;
  short sVar15;
  short sVar16;
  
  iVar2 = *(int *)(param_1 + 0x5c);
  piVar3 = *(int **)(param_1 + 0x70);
  uVar5 = (ushort)*(byte *)(*piVar3 + 0x2c);
  iVar7 = GetRegDat__9RegDatApiFiii(0x37,0,0xffffffffffffffff);
  iVar4 = *piVar3;
  for (pcVar8 = (char *)(iVar4 + 0x32); pcVar8 < (char *)(iVar4 + 0x3a); pcVar8 = pcVar8 + 1) {
    if (-1 < *pcVar8) {
      pcVar13 = (char *)(*(int *)(param_1 + 0x9b4) + (int)*pcVar8);
      *pcVar13 = *pcVar13 + -1;
      *pcVar8 = -1;
    }
  }
  iVar4 = *piVar3;
  uVar14 = *(uint *)(param_1 + 0x9ac);
  uVar9 = uVar14 + *(short *)(param_1 + 0x9a6) * 8;
  sVar16 = 0;
  for (; uVar14 < uVar9; uVar14 = uVar14 + 8) {
    sVar1 = *(short *)(uVar14 + 6);
    sVar15 = sVar16;
    if (-1 < sVar1) {
      iVar10 = (int)sVar1;
      if ((long)sVar1 << 0x30 < 0) {
        iVar10 = iVar10 + 7;
      }
      uVar12 = (long)sVar1 & 7;
      uVar11 = (uint)uVar12;
      if (((long)sVar1 < 0) && (uVar12 != 0)) {
        uVar11 = uVar11 - 8;
      }
      if (((((int)(uint)*(byte *)(*(int *)(iVar2 + 8) + (iVar10 >> 3) + 0x160) >> (uVar11 & 0x1f) &
            1U) != 0) && (*(char *)(*(int *)(param_1 + 0x9b4) + (int)sVar1) == '\0')) &&
         (uVar6 = (ushort)*(byte *)(iVar7 + sVar1 * 0x1c + 4), uVar6 <= uVar5)) {
        sVar15 = sVar16 + 1;
        *(char *)(iVar4 + 0x32 + (int)sVar16) = (char)sVar1;
        pcVar8 = (char *)(*(int *)(param_1 + 0x9b4) + (int)sVar1);
        *pcVar8 = *pcVar8 + '\x01';
        uVar5 = uVar5 - uVar6;
        if (sVar15 == 8) break;
      }
    }
    sVar16 = sVar15;
  }
  UpdateScene__14CmdCrestPCInfoFP8CmdCrests(param_1 + 0x350,param_1,0xffffffffffffffff);
  UpdateSlot__8CmdCrestFs(param_1,0);
  UpdateGoods__8CmdCrestFsss(param_1,0,0,0);
  return;
}

/* JP: 0x00492520  CmdCrest::SetMenu(char, short)   [SetMenu__8CmdCrestFcs]  size=0xb0 */
void SetMenu__8CmdCrestFcs(int param_1,undefined1 param_2,undefined2 param_3)

{
  undefined4 uVar1;
  undefined *puVar2;
  
  *(undefined1 *)(param_1 + 0x20) = param_2;
  *(undefined2 *)(param_1 + 0x1e) = param_3;
  puVar2 = PTR_ShiftMenu__8CmdCrestFv_0050dbc8;
  uVar1 = DAT_0050dbc4;
  *(undefined4 *)(param_1 + 0x7c) = _5493;
  *(undefined4 *)(param_1 + 0x80) = uVar1;
  *(undefined **)(param_1 + 0x84) = puVar2;
  SetChengePCMode__10CmdPCSceneFUc(param_1,1);
  Shutdown__6CursorFv(*(undefined4 *)(param_1 + 0x18));
  Close__10MenuWindowFUci(param_1 + 0x250,((ulong)*(byte *)(param_1 + 0x300) & 0x3f) >> 3,
                  *(undefined4 *)(*(int *)(param_1 + 0x284) + 0x14));
  return;
}

/* JP: 0x004925d0  CmdCrest::StartDetail()   [StartDetail__8CmdCrestFv]  size=0x338 */
void StartDetail__8CmdCrestFv(int param_1)

{
  short sVar1;
  int iVar2;
  undefined *puVar3;
  undefined4 uVar4;
  long lVar5;
  
  if (*(char *)(param_1 + 0x9b9) == '\0') {
    sVar1 = *(short *)(*(int *)(param_1 + 0x990) + 0x1c2);
  }
  else {
    sVar1 = *(short *)(*(int *)(param_1 + 0x994) + 0x1c2);
  }
  lVar5 = __nw__FUi(0x1d68);
  uVar4 = 0;
  if (lVar5 != 0) {
    uVar4 = __ct__14CmdCrestDetailFv(lVar5);
  }
  *(undefined4 *)(param_1 + 0x99c) = uVar4;
  CreateScene__14CmdCrestDetailFP9MenuSceneP11MenuTexture
            (*(undefined4 *)(param_1 + 0x99c),param_1 + 0xe0,param_1 + 0x138);
  if (1 < sVar1) {
    CreateScrollMark__10MenuWindowFUc(*(undefined4 *)(param_1 + 0x99c),3);
    iVar2 = *(int *)(param_1 + 0x99c);
    SetArea__10ScrollMarkFUcffff(0xbf800000,0xbf800000,*(float *)(iVar2 + 0x6c) + 2.0,
                    *(float *)(iVar2 + 0x70) + 2.0,*(undefined4 *)(iVar2 + 0x44),
                    *(undefined1 *)(iVar2 + 0xa9));
  }
  iVar2 = *(int *)(param_1 + 0x78);
  Close__10MenuWindowFUci(iVar2 + 0x58,((ulong)*(byte *)(iVar2 + 0x108) & 0x3f) >> 3,
                  *(undefined4 *)(*(int *)(iVar2 + 0x8c) + 0x14));
  Close__10MenuWindowFUci(param_1 + 0x350,((ulong)*(byte *)(param_1 + 0x400) & 0x3f) >> 3,
                  *(undefined4 *)(*(int *)(param_1 + 900) + 0x14));
  iVar2 = *(int *)(param_1 + 0x990);
  Close__10MenuWindowFUci(iVar2,((ulong)*(byte *)(iVar2 + 0xb0) & 0x3f) >> 3,
                  *(undefined4 *)(*(int *)(iVar2 + 0x34) + 0x14));
  iVar2 = *(int *)(param_1 + 0x994);
  Close__10MenuWindowFUci(iVar2,((ulong)*(byte *)(iVar2 + 0xb0) & 0x3f) >> 3,
                  *(undefined4 *)(*(int *)(iVar2 + 0x34) + 0x14));
  iVar2 = *(int *)(param_1 + 0x998);
  Close__10MenuWindowFUci(iVar2,((ulong)*(byte *)(iVar2 + 0xb0) & 0x3f) >> 3,
                  *(undefined4 *)(*(int *)(iVar2 + 0x34) + 0x14));
  iVar2 = *(int *)(param_1 + 0x68);
  Close__10MenuWindowFUci(iVar2 + 0x58,((ulong)*(byte *)(iVar2 + 0x108) & 0x3f) >> 3,
                  *(undefined4 *)(*(int *)(iVar2 + 0x8c) + 0x14));
  *(byte *)(*(int *)(param_1 + 0x18) + 0x12) = *(byte *)(*(int *)(param_1 + 0x18) + 0x12) & 0xfe;
  *(undefined1 *)(param_1 + 0x9ba) = *(undefined1 *)(param_1 + 0x9b9);
  *(undefined1 *)(param_1 + 0x9b9) = 5;
  puVar3 = PTR_EnterDetail__8CmdCrestFv_0050dbd8;
  uVar4 = DAT_0050dbd4;
  *(undefined4 *)(param_1 + 0x7c) = _5509;
  *(undefined4 *)(param_1 + 0x80) = uVar4;
  *(undefined **)(param_1 + 0x84) = puVar3;
  SetChengePCMode__10CmdPCSceneFUc(param_1,0);
  PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),2,0,0);
  return;
}

/* JP: 0x00492910  CmdCrest::SetButtonReport()   [SetButtonReport__8CmdCrestFv]  size=0x18c */
void SetButtonReport__8CmdCrestFv(int param_1)

{
  short sVar1;
  int iVar2;
  int iVar3;
  ulong uVar4;
  
  iVar2 = *(int *)(param_1 + 0x68);
  iVar3 = *(int *)(*(int *)(param_1 + 0x18) + 0xec);
  sVar1 = *(short *)(iVar3 + 0x16);
  ClearReport__15CmdButtonReportFv(iVar2);
  iVar3 = *(int *)(iVar3 + 0x18);
  if (*(int *)(iVar3 + 0x44) == 0) {
    uVar4 = 0;
  }
  else {
    uVar4 = ((ulong)*(ushort *)(iVar3 + 0xb2) & 0x3ff) >> 2;
  }
  if (uVar4 != 0) {
    SetReport__15CmdButtonReportFii(iVar2,*(undefined1 *)(iVar2 + 0x20),0xd);
  }
  if (*(char *)(param_1 + 0x9b9) == '\x04') {
    SetOffset__15CmdButtonReportFf(0x42380000,iVar2);
    SetReport__15CmdButtonReportFii(iVar2,*(undefined1 *)(iVar2 + 0x20),6);
  }
  if (-1 < sVar1) {
    SetOffset__15CmdButtonReportFf(0x42380000,iVar2);
    SetReport__15CmdButtonReportFii(iVar2,*(undefined1 *)(iVar2 + 0x20),0x11);
  }
  return;
}

/* JP: 0x00492aa0  CmdCrest::UpdateComboKeyMagic()   [UpdateComboKeyMagic__8CmdCrestFv]  size=0xc0 */
void UpdateComboKeyMagic__8CmdCrestFv(int param_1)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  iVar1 = *(int *)(param_1 + 0x5c);
  uVar2 = iVar1 + 0x30;
  uVar3 = uVar2 + (*(short *)(iVar1 + 0xe) * 0x12 + (int)*(short *)(iVar1 + 0xe)) * 4;
  for (; uVar2 < uVar3; uVar2 = uVar2 + 0x4c) {
    UpdateComboKeyMagic__5CmdPCFP8CmdPartysPc
              (uVar2,iVar1,*(undefined2 *)(param_1 + 0x9a4),*(undefined4 *)(param_1 + 0x9b0));
  }
  return;
}

/* JP: 0x00492b60  CmdCrest::Enter()   [Enter__8CmdCrestFv]  size=0x1d4 */
undefined8 Enter__8CmdCrestFv(int param_1)

{
  bool bVar1;
  undefined4 uVar2;
  undefined *puVar3;
  undefined1 uVar4;
  
  if (*(char *)(param_1 + 0x21) == '\0') {
    (**(code **)(*(int *)(param_1 + 8) + 0x28))(param_1,1);
    *(undefined1 *)(param_1 + 0x20) = 0;
    *(undefined2 *)(param_1 + 0x1e) = 0;
    ShiftMenu__8CmdCrestFv(param_1);
    SetTitle__11CmdTitleLogFPUci
              (*(undefined4 *)(param_1 + 0x60),*(undefined4 *)(*(int *)(param_1 + 0x54) + 0x10),0x21
              );
    Open__11CmdTitleLogFv(*(undefined4 *)(param_1 + 0x60));
    uVar4 = CreateBackGround__7CmdMenuFs(*(undefined4 *)(param_1 + 0x10),8);
    *(undefined1 *)(param_1 + 0x20) = uVar4;
    *(char *)(param_1 + 0x21) = *(char *)(param_1 + 0x21) + '\x01';
  }
  else if (*(char *)(param_1 + 0x21) == '\x01') {
    if ((*(char *)(param_1 + 0x3f8) == '\x01') || (*(char *)(param_1 + 0x3f8) == '\0')) {
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
      *(undefined1 *)(param_1 + 0x9b9) = 3;
      *(undefined1 *)(param_1 + 0x21) = 0;
      puVar3 = PTR_ShiftMenu__8CmdCrestFv_0050dbe8;
      uVar2 = DAT_0050dbe4;
      *(undefined4 *)(param_1 + 0x7c) = _5611;
      *(undefined4 *)(param_1 + 0x80) = uVar2;
      *(undefined **)(param_1 + 0x84) = puVar3;
    }
  }
  return 0;
}

/* JP: 0x00492d40  CmdCrest::Exit()   [Exit__8CmdCrestFv]  size=0x274 */
undefined8 Exit__8CmdCrestFv(int param_1)

{
  int iVar1;
  bool bVar2;
  
  if (*(char *)(param_1 + 0x21) == '\0') {
    (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x14) + 0x28))(*(int *)(param_1 + 0x10),0,0,3);
    Shutdown__6CursorFv(*(undefined4 *)(param_1 + 0x18));
    iVar1 = *(int *)(param_1 + 0x78);
    Close__10MenuWindowFUci(iVar1 + 0x58,((ulong)*(byte *)(iVar1 + 0x108) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar1 + 0x8c) + 0x14));
    iVar1 = *(int *)(param_1 + 0x60);
    Close__10MenuWindowFUci(iVar1 + 0x58,((ulong)*(byte *)(iVar1 + 0x108) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar1 + 0x8c) + 0x14));
    Close__10MenuWindowFUci(param_1 + 0x250,((ulong)*(byte *)(param_1 + 0x300) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(param_1 + 0x284) + 0x14));
    iVar1 = *(int *)(param_1 + 0x990);
    Close__10MenuWindowFUci(iVar1,((ulong)*(byte *)(iVar1 + 0xb0) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x14));
    iVar1 = *(int *)(param_1 + 0x994);
    Close__10MenuWindowFUci(iVar1,((ulong)*(byte *)(iVar1 + 0xb0) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x14));
    Close__10MenuWindowFUci(param_1 + 0x350,((ulong)*(byte *)(param_1 + 0x400) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(param_1 + 900) + 0x14));
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
      ReleaseOT__7MenuObjFv(param_1 + 0x250);
      ReleaseOT__7MenuObjFv(param_1 + 0x350);
      (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x14) + 0x24))(*(int *)(param_1 + 0x10),0);
      DestroyScene__4MenuFP9MenuSceneb(*(undefined4 *)(param_1 + 0x10),param_1,1);
    }
  }
  return 0;
}

/* JP: 0x00492fc0  CmdCrest::ShiftMenu()   [ShiftMenu__8CmdCrestFv]  size=0x2e0 */
undefined8 ShiftMenu__8CmdCrestFv(int param_1)

{
  bool bVar1;
  undefined4 uVar2;
  undefined *puVar3;
  undefined4 uVar4;
  undefined *puVar5;
  int iVar6;
  
  if ((*(char *)(param_1 + 0x2f8) == '\x01') || (*(char *)(param_1 + 0x2f8) == '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if (bVar1) {
    if (*(char *)(param_1 + 0x2f8) == '\0') {
      UpdateScene__10CmdSubMenuFs(param_1 + 0x1f8,*(undefined1 *)(param_1 + 0x20));
      iVar6 = GetPlace__10MenuWindowFss(param_1 + 0x250,0,*(undefined2 *)(param_1 + 0x1e));
      Select__6CursorFP9MenuPlace(*(undefined4 *)(param_1 + 0x18),iVar6);
      Select__10CmdSubMenuFP7CmdNoteP9MenuPlaceP9MenuPlace
                (param_1 + 0x1f8,*(undefined4 *)(param_1 + 100),iVar6,0);
      if (*(char *)(param_1 + 0x9b8) != '\0') {
        SetExplanation__7CmdNoteFPCce
                  (*(undefined4 *)(param_1 + 100),
                   *(undefined4 *)
                    ((uint)*(ushort *)(iVar6 + 0x22) * 0xc + *(int *)(param_1 + 0x28) + 0x14),
                   **(int **)(param_1 + 0x70) + 10);
      }
    }
    else {
      SetChengePCMode__10CmdPCSceneFUc(param_1,1);
      Restore__6CursorFv(*(undefined4 *)(param_1 + 0x18));
      puVar5 = PTR_SelectDisarm__8CmdCrestFv_0050dc08;
      uVar4 = DAT_0050dc04;
      puVar3 = PTR_SelectMenu__8CmdCrestFv_0050dbf8;
      uVar2 = DAT_0050dbf4;
      if (*(char *)(param_1 + 0x20) == '\x02') {
        *(undefined4 *)(param_1 + 0x7c) = _5670;
        *(undefined4 *)(param_1 + 0x80) = uVar4;
        *(undefined **)(param_1 + 0x84) = puVar5;
        *(undefined1 *)(param_1 + 0x9b9) = 2;
      }
      else if (*(char *)(param_1 + 0x20) == '\0') {
        *(undefined4 *)(param_1 + 0x7c) = _5667;
        *(undefined4 *)(param_1 + 0x80) = uVar2;
        *(undefined **)(param_1 + 0x84) = puVar3;
        *(undefined1 *)(param_1 + 0x9b9) = 3;
      }
    }
  }
  return 0;
}

/* JP: 0x004932a0  CmdCrest::SelectMenu()   [SelectMenu__8CmdCrestFv]  size=0x310 */
undefined8 SelectMenu__8CmdCrestFv(int param_1)

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
      iVar6 = MoveVertical__9MenuSceneFi(param_1,0);
      if (iVar3 != iVar6) {
        Select__10CmdSubMenuFP7CmdNoteP9MenuPlaceP9MenuPlace
                  (param_1 + 0x1f8,*(undefined4 *)(param_1 + 100),iVar6,iVar3);
        PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),0,0,0);
      }
    }
    else {
      UpdateComboKeyMagic__8CmdCrestFv(param_1);
      SetChengePCMode__10CmdPCSceneFUc(param_1,0);
      puVar5 = PTR_Exit__8CmdCrestFv_0050dc28;
      uVar4 = DAT_0050dc24;
      *(undefined4 *)(param_1 + 0x7c) = _5731;
      *(undefined4 *)(param_1 + 0x80) = uVar4;
      *(undefined **)(param_1 + 0x84) = puVar5;
      PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),3,0,0);
    }
  }
  else {
    sVar1 = *(short *)(iVar3 + 0x1e);
    if (sVar1 == 2) {
      SetMenu__8CmdCrestFcs(param_1,2,0);
      *(undefined1 *)(param_1 + 0x9b8) = 1;
    }
    else if (sVar1 == 1) {
      Recommend__8CmdCrestFv(param_1);
    }
    else if (sVar1 == 0) {
      *(undefined1 *)(*(int *)(param_1 + 0x18) + 0xf9) = 0xfb;
      uVar7 = GetPlace__10MenuWindowFss(*(undefined4 *)(param_1 + 0x990),0,0);
      Select__6CursorFP9MenuPlace(*(undefined4 *)(param_1 + 0x18),uVar7);
      Select__13CmdGoodsCrestFP9MenuSceneP7CmdNoteP9MenuGroupP9MenuGroup
                (*(undefined4 *)(param_1 + 0x990),param_1 + 0x88,*(undefined4 *)(param_1 + 100),
                 uVar7,0);
      UpdateCrestMagic__8CmdCrestFssc(param_1,1,*(undefined2 *)((int)uVar7 + 0x16),0);
      SetButtonReport__8CmdCrestFv(param_1);
      Open__15CmdButtonReportFv(*(undefined4 *)(param_1 + 0x68));
      *(undefined1 *)(param_1 + 0x9b9) = 0;
      puVar5 = PTR_SelectSlot__8CmdCrestFv_0050dc18;
      uVar4 = DAT_0050dc14;
      *(undefined4 *)(param_1 + 0x7c) = _5724;
      *(undefined4 *)(param_1 + 0x80) = uVar4;
      *(undefined **)(param_1 + 0x84) = puVar5;
    }
    PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),2,0,0);
  }
  return 0;
}

/* JP: 0x004935b0  CmdCrest::SelectDisarm()   [SelectDisarm__8CmdCrestFv]  size=0x320 */
undefined8 SelectDisarm__8CmdCrestFv(int param_1)

{
  ushort uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  
  uVar1 = *(ushort *)(*(int *)(param_1 + 0x10) + 0x48);
  iVar2 = *(int *)(*(int *)(param_1 + 0x18) + 0xec);
  if ((uVar1 & 0x2000) == 0) {
    if ((uVar1 & 0x4000) == 0) {
      iVar4 = MoveVertical__9MenuSceneFi(param_1,0);
      if (iVar2 != iVar4) {
        uVar3 = *(undefined4 *)
                 ((uint)*(ushort *)(iVar4 + 0x22) * 0xc + *(int *)(param_1 + 0x28) + 0x14);
        if (*(short *)(iVar4 + 0x1e) == 0) {
          SetExplanation__7CmdNoteFPCce
                    (*(undefined4 *)(param_1 + 100),uVar3,**(int **)(param_1 + 0x70) + 10);
          *(undefined1 *)(param_1 + 0x9b8) = 1;
        }
        else {
          SetExplanation__7CmdNoteFPCce(*(undefined4 *)(param_1 + 100),uVar3);
          *(undefined1 *)(param_1 + 0x9b8) = 0;
        }
        Select__10CmdSubMenuFP7CmdNoteP9MenuPlaceP9MenuPlace(param_1 + 0x1f8,0,iVar4,iVar2);
        PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),0,0,0);
      }
    }
    else {
      *(undefined1 *)(param_1 + 0x9b8) = 0;
      SetMenu__8CmdCrestFcs(param_1,0,2);
      PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),3,0,0);
    }
  }
  else {
    if (*(short *)(iVar2 + 0x1e) == 0) {
      Disarm__8CmdCrestFs(param_1,*(undefined1 *)(**(int **)(param_1 + 0x70) + 2));
    }
    else {
      Disarm__8CmdCrestFs(param_1,0xffffffffffffffff);
    }
    CreateEquipCrest__8CmdCrestFv(param_1);
    CreateMagic__5CmdPCFP8CmdPartysPc
              (*(undefined4 *)(param_1 + 0x70),*(undefined4 *)(param_1 + 0x5c),
               *(undefined2 *)(param_1 + 0x9a4),*(undefined4 *)(param_1 + 0x9b0));
    UpdateScene__14CmdCrestPCInfoFP8CmdCrests(param_1 + 0x350,param_1,0xffffffffffffffff);
    UpdateSlot__8CmdCrestFs(param_1,0);
    UpdateGoods__8CmdCrestFsss(param_1,0,0,0);
    PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),2,0,0);
  }
  return 0;
}

/* JP: 0x004938d0  CmdCrest::SelectSlot()   [SelectSlot__8CmdCrestFv]  size=0x4b0 */
undefined8 SelectSlot__8CmdCrestFv(int param_1)

{
  short sVar1;
  ushort uVar2;
  int iVar3;
  undefined *puVar4;
  undefined4 uVar5;
  int iVar6;
  undefined8 uVar7;
  
  uVar2 = *(ushort *)(*(int *)(param_1 + 0x10) + 0x48);
  iVar3 = *(int *)(*(int *)(param_1 + 0x18) + 0xec);
  sVar1 = *(short *)(iVar3 + 0x16);
  if ((uVar2 & 0x2000) == 0) {
    if ((uVar2 & 0x4000) == 0) {
      if (((uVar2 & 0x1000) == 0) || (sVar1 < 0)) {
        iVar6 = MoveVertical__9MenuSceneFi(param_1,1);
        if (iVar3 != iVar6) {
          Select__13CmdGoodsCrestFP9MenuSceneP7CmdNoteP9MenuGroupP9MenuGroup
                    (*(undefined4 *)(param_1 + 0x990),param_1 + 0x88,*(undefined4 *)(param_1 + 100),
                     iVar6,iVar3);
          UpdateGoods__8CmdCrestFsss(param_1,0,*(undefined2 *)(iVar6 + 0x22),0);
          UpdateScene__13CmdCrestMagicFP8CmdCrestsc
                    (*(undefined4 *)(param_1 + 0x998),param_1,*(undefined2 *)(iVar6 + 0x16),0);
          SetButtonReport__8CmdCrestFv(param_1);
          PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),0,0,0);
        }
      }
      else {
        StartDetail__8CmdCrestFv(param_1);
      }
    }
    else {
      *(undefined1 *)(*(int *)(param_1 + 0x18) + 0xf9) = *(undefined1 *)(param_1 + 0x9bb);
      Select__13CmdGoodsCrestFP9MenuSceneP7CmdNoteP9MenuGroupP9MenuGroup
                (*(undefined4 *)(param_1 + 0x990),0,0,0,iVar3);
      uVar5 = GetPlace__10MenuWindowFss(param_1 + 0x250,0,0);
      Select__6CursorFP9MenuPlace(*(undefined4 *)(param_1 + 0x18),uVar5);
      Select__10CmdSubMenuFP7CmdNoteP9MenuPlaceP9MenuPlace
                (param_1 + 0x1f8,*(undefined4 *)(param_1 + 100),uVar5,0);
      SetScroll__10MenuWindowFss(*(undefined4 *)(param_1 + 0x990),0,0);
      (**(code **)(*(int *)(*(int *)(param_1 + 0x998) + 8) + 0xc))();
      *(undefined4 *)(param_1 + 0x998) = 0;
      iVar3 = *(int *)(param_1 + 0x68);
      Close__10MenuWindowFUci(iVar3 + 0x58,((ulong)*(byte *)(iVar3 + 0x108) & 0x3f) >> 3,
                      *(undefined4 *)(*(int *)(iVar3 + 0x8c) + 0x14));
      *(undefined1 *)(param_1 + 0x9b9) = 3;
      puVar4 = PTR_SelectMenu__8CmdCrestFv_0050dc48;
      uVar5 = DAT_0050dc44;
      *(undefined4 *)(param_1 + 0x7c) = _5844;
      *(undefined4 *)(param_1 + 0x80) = uVar5;
      *(undefined **)(param_1 + 0x84) = puVar4;
      PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),3,0,0);
    }
  }
  else if ((*(short *)(*(int *)(param_1 + 0x994) + 0x1be) == 0) && (sVar1 < 0)) {
    PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),4,0,0);
  }
  else {
    if (-1 < sVar1) {
      UpdateGoods__8CmdCrestFsss(param_1,0,*(undefined2 *)(iVar3 + 0x22),1);
    }
    uVar7 = GetPlace__10MenuWindowFss(*(undefined4 *)(param_1 + 0x994),0,0);
    Select__6CursorFP9MenuPlace(*(undefined4 *)(param_1 + 0x18),uVar7);
    Select__13CmdGoodsCrestFP9MenuSceneP7CmdNoteP9MenuGroupP9MenuGroup
              (*(undefined4 *)(param_1 + 0x994),param_1 + 0x88,*(undefined4 *)(param_1 + 100),uVar7,
               0);
    *(int *)(param_1 + 0x988) = iVar3;
    UpdateScene__14CmdCrestPCInfoFP8CmdCrests
              (param_1 + 0x350,param_1,*(undefined2 *)((int)uVar7 + 0x22));
    UpdateScene__13CmdCrestMagicFP8CmdCrestsc
              (*(undefined4 *)(param_1 + 0x998),param_1,*(undefined2 *)((int)uVar7 + 0x16),1);
    SetChengePCMode__10CmdPCSceneFUc(param_1,0);
    *(undefined1 *)(param_1 + 0x9b9) = 4;
    puVar4 = PTR_SelectGoods__8CmdCrestFv_0050dc38;
    uVar5 = DAT_0050dc34;
    *(undefined4 *)(param_1 + 0x7c) = _5838;
    *(undefined4 *)(param_1 + 0x80) = uVar5;
    *(undefined **)(param_1 + 0x84) = puVar4;
    SetButtonReport__8CmdCrestFv(param_1);
    PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),2,0,0);
  }
  return 0;
}

/* JP: 0x00493d80  CmdCrest::SelectGoods()   [SelectGoods__8CmdCrestFv]  size=0x7dc */
undefined8 SelectGoods__8CmdCrestFv(int param_1)

{
  ushort uVar1;
  int iVar2;
  int *piVar3;
  undefined *puVar4;
  int iVar5;
  undefined4 uVar6;
  long lVar7;
  short sVar8;
  float fVar9;
  float fVar10;
  undefined4 uStack_38;
  
  uVar1 = *(ushort *)(*(int *)(param_1 + 0x10) + 0x48);
  iVar2 = *(int *)(*(int *)(param_1 + 0x18) + 0xec);
  if ((uVar1 & 0x6000) == 0) {
    if (((uVar1 & 0x1000) == 0) || (*(short *)(iVar2 + 0x16) < 0)) {
      if ((uVar1 & 0x8000) == 0) {
        iVar5 = MoveVertical__9MenuSceneFi(param_1,1);
        if (iVar2 != iVar5) {
          Select__13CmdGoodsCrestFP9MenuSceneP7CmdNoteP9MenuGroupP9MenuGroup
                    (*(undefined4 *)(param_1 + 0x994),param_1 + 0x88,*(undefined4 *)(param_1 + 100),
                     iVar5,iVar2);
          UpdateScene__14CmdCrestPCInfoFP8CmdCrests
                    (param_1 + 0x350,param_1,*(undefined2 *)(iVar5 + 0x22));
          UpdateScene__13CmdCrestMagicFP8CmdCrestsc
                    (*(undefined4 *)(param_1 + 0x998),param_1,*(undefined2 *)(iVar5 + 0x16),1);
          SetButtonReport__8CmdCrestFv(param_1);
          PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),0,0,0);
        }
      }
      else {
        *(undefined1 *)(*(int *)(param_1 + 0x18) + 0xf9) = *(undefined1 *)(param_1 + 0x9bb);
        lVar7 = __nw__FUi(0x160);
        uVar6 = 0;
        if (lVar7 != 0) {
          uVar6 = __ct__7CmdSortFv(lVar7);
        }
        *(undefined4 *)(param_1 + 0x9a0) = uVar6;
        *(ushort *)(*(int *)(param_1 + 0x9a0) + 0x15a) =
             (ushort)*(byte *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x28d);
        *(undefined4 *)(*(int *)(param_1 + 0x9a0) + 0x15c) =
             *(undefined4 *)(*(int *)(param_1 + 0x18) + 0xec);
        *(undefined4 *)(*(int *)(param_1 + 0x9a0) + 0x10) = *(undefined4 *)(param_1 + 0x10);
        Initialize__9MenuSceneFPUcP9BufMemory(*(undefined4 *)(param_1 + 0x9a0),
                        *(undefined4 *)(*(int *)(param_1 + 0x54) + 100),0);
        iVar2 = *(int *)(*(int *)(param_1 + 0x994) + 0x44);
        *(byte *)(iVar2 + 0x12) = *(byte *)(iVar2 + 0x12) & 0xfe;
        iVar2 = *(int *)(param_1 + 0x998);
        Close__10MenuWindowFUci(iVar2,((ulong)*(byte *)(iVar2 + 0xb0) & 0x3f) >> 3,
                        *(undefined4 *)(*(int *)(iVar2 + 0x34) + 0x14));
        iVar2 = *(int *)(param_1 + 0x68);
        Close__10MenuWindowFUci(iVar2 + 0x58,((ulong)*(byte *)(iVar2 + 0x108) & 0x3f) >> 3,
                        *(undefined4 *)(*(int *)(iVar2 + 0x8c) + 0x14));
        puVar4 = PTR_ExecSort__8CmdCrestFv_0050dc68;
        uVar6 = DAT_0050dc64;
        *(undefined4 *)(param_1 + 0x7c) = _5937;
        *(undefined4 *)(param_1 + 0x80) = uVar6;
        *(undefined **)(param_1 + 0x84) = puVar4;
        PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),2,0,0);
      }
    }
    else {
      StartDetail__8CmdCrestFv(param_1);
    }
  }
  else {
    uStack_38 = 3;
    piVar3 = *(int **)(param_1 + 0x70);
    iVar5 = *(int *)(param_1 + 0x988);
    if ((uVar1 & 0x2000) != 0) {
      if (-1 < (long)((ulong)*(byte *)(iVar2 + 0x21) << 0x3c)) {
        PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),4,0,0);
        return 0;
      }
      sVar8 = *(short *)(iVar5 + 0x1e);
      if (*(short *)(iVar2 + 0x16) < 0) {
        for (; sVar8 < 7; sVar8 = sVar8 + 1) {
          *(undefined1 *)(*piVar3 + (int)sVar8 + 0x32) =
               *(undefined1 *)(*piVar3 + (int)(short)(sVar8 + 1) + 0x32);
        }
        *(undefined1 *)(*piVar3 + 0x39) = 0xff;
      }
      else {
        *(char *)(*piVar3 + (int)sVar8 + 0x32) = (char)*(short *)(iVar2 + 0x16);
        for (sVar8 = 0; sVar8 < 8; sVar8 = sVar8 + 1) {
          if (*(char *)(*piVar3 + (int)sVar8 + 0x32) < '\0') {
            iVar5 = GetPlace__10MenuWindowFss(*(undefined4 *)(param_1 + 0x990),0,sVar8);
            break;
          }
        }
      }
      CreateEquipCrest__8CmdCrestFv(param_1);
      CreateMagic__5CmdPCFP8CmdPartysPc
                (*(undefined4 *)(param_1 + 0x70),*(undefined4 *)(param_1 + 0x5c),
                 *(undefined2 *)(param_1 + 0x9a4),*(undefined4 *)(param_1 + 0x9b0));
      iVar2 = *(int *)(param_1 + 0x990);
      fVar9 = (float)GetTargetY__10MenuWindowCFv(iVar2);
      fVar10 = *(float *)(*(int *)(iVar2 + 0x40) + 0x20);
      UpdateSlot__8CmdCrestFs(param_1,0);
      SetScroll__10MenuWindowFss(*(undefined4 *)(param_1 + 0x990),0,(short)(int)(-fVar9 / fVar10));
      uStack_38 = 2;
    }
    Select__6CursorFP9MenuPlace(*(undefined4 *)(param_1 + 0x18),iVar5);
    Select__13CmdGoodsCrestFP9MenuSceneP7CmdNoteP9MenuGroupP9MenuGroup
              (*(undefined4 *)(param_1 + 0x990),param_1 + 0x88,*(undefined4 *)(param_1 + 100),iVar5,
               0);
    UpdateScene__14CmdCrestPCInfoFP8CmdCrests(param_1 + 0x350,param_1,0xffffffffffffffff);
    *(undefined4 *)(param_1 + 0x988) = 0;
    UpdateScene__13CmdCrestMagicFP8CmdCrestsc
              (*(undefined4 *)(param_1 + 0x998),param_1,*(undefined2 *)(iVar5 + 0x16),0);
    UpdateGoods__8CmdCrestFsss(param_1,0,*(undefined2 *)(iVar5 + 0x22),0);
    SetChengePCMode__10CmdPCSceneFUc(param_1,1);
    *(undefined1 *)(param_1 + 0x9b9) = 0;
    puVar4 = PTR_SelectSlot__8CmdCrestFv_0050dc58;
    uVar6 = DAT_0050dc54;
    *(undefined4 *)(param_1 + 0x7c) = _5927;
    *(undefined4 *)(param_1 + 0x80) = uVar6;
    *(undefined **)(param_1 + 0x84) = puVar4;
    SetButtonReport__8CmdCrestFv(param_1);
    PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),uStack_38,0,0);
  }
  return 0;
}

/* JP: 0x00494560  CmdCrest::EnterDetail()   [EnterDetail__8CmdCrestFv]  size=0x220 */
undefined8 EnterDetail__8CmdCrestFv(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  bool bVar3;
  undefined *puVar4;
  
  if ((*(char *)(*(int *)(param_1 + 0x990) + 0xa8) == '\x01') ||
     (*(char *)(*(int *)(param_1 + 0x990) + 0xa8) == '\0')) {
    bVar3 = true;
  }
  else {
    bVar3 = false;
  }
  if (bVar3) {
    iVar1 = *(int *)(*(int *)(param_1 + 0x18) + 0xec);
    if (*(char *)(param_1 + 0x9ba) == '\0') {
      uVar2 = *(undefined4 *)(param_1 + 0x990);
    }
    else {
      uVar2 = *(undefined4 *)(param_1 + 0x994);
    }
    Select__13CmdGoodsCrestFP9MenuSceneP7CmdNoteP9MenuGroupP9MenuGroup(uVar2,0,0,0,iVar1);
    SetExplanation__7CmdNoteFPCce
              (*(undefined4 *)(param_1 + 100),*(undefined4 *)(*(int *)(param_1 + 0x104) + 0x28));
    UpdateScene__14CmdCrestDetailFP9MenuSceneP8CmdPartyP13MenuDataMagics
              (*(undefined4 *)(param_1 + 0x99c),param_1 + 0xe0,*(undefined4 *)(param_1 + 0x5c),
               *(undefined4 *)(param_1 + 0x9a8),*(undefined2 *)(iVar1 + 0x16));
    iVar1 = *(int *)(param_1 + 0x99c);
    Open__10MenuWindowFUci(iVar1,*(byte *)(iVar1 + 0xb0) & 7,*(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x10)
                   );
    iVar1 = *(int *)(param_1 + 0x990);
    *(byte *)(iVar1 + 0xb1) = *(byte *)(iVar1 + 0xb1) & 0xf7;
    *(byte *)(iVar1 + 0xb1) = *(byte *)(iVar1 + 0xb1) & 0xef | 0x10;
    puVar4 = PTR_ExecDetail__8CmdCrestFv_0050dc78;
    uVar2 = DAT_0050dc74;
    *(undefined4 *)(param_1 + 0x7c) = _6058;
    *(undefined4 *)(param_1 + 0x80) = uVar2;
    *(undefined **)(param_1 + 0x84) = puVar4;
  }
  return 0;
}

/* JP: 0x00494780  CmdCrest::ExitDetail()   [ExitDetail__8CmdCrestFv]  size=0x3d0 */
undefined8 ExitDetail__8CmdCrestFv(int param_1)

{
  int iVar1;
  bool bVar2;
  undefined4 uVar3;
  undefined *puVar4;
  undefined4 uVar5;
  undefined *puVar6;
  int iVar7;
  undefined4 uStack_18;
  
  iVar7 = *(int *)(param_1 + 0x99c);
  if (iVar7 == 0) {
    iVar7 = *(int *)(param_1 + 0x990);
  }
  if ((*(char *)(iVar7 + 0xa8) == '\x01') || (*(char *)(iVar7 + 0xa8) == '\0')) {
    bVar2 = true;
  }
  else {
    bVar2 = false;
  }
  if (bVar2) {
    if (*(char *)(*(int *)(param_1 + 0x990) + 0xa8) == '\0') {
      iVar7 = *(int *)(*(int *)(param_1 + 0x18) + 0xec);
      (**(code **)(*(int *)(*(int *)(param_1 + 0x99c) + 8) + 0xc))();
      *(undefined4 *)(param_1 + 0x99c) = 0;
      FinishScroll__10MenuWindowFv(*(undefined4 *)(param_1 + 0x990));
      FinishScroll__10MenuWindowFv(*(undefined4 *)(param_1 + 0x994));
      iVar1 = *(int *)(param_1 + 0x990);
      *(byte *)(iVar1 + 0xb1) = *(byte *)(iVar1 + 0xb1) & 0xf7;
      *(byte *)(iVar1 + 0xb1) = *(byte *)(iVar1 + 0xb1) & 0xef;
      Restore__6CursorFv(*(undefined4 *)(param_1 + 0x18));
      if (*(char *)(param_1 + 0x9ba) == '\0') {
        uStack_18 = *(undefined4 *)(param_1 + 0x990);
      }
      else {
        uStack_18 = *(undefined4 *)(param_1 + 0x994);
        UpdateScene__14CmdCrestPCInfoFP8CmdCrests
                  (param_1 + 0x350,param_1,*(undefined2 *)(iVar7 + 0x22));
      }
      Select__13CmdGoodsCrestFP9MenuSceneP7CmdNoteP9MenuGroupP9MenuGroup
                (uStack_18,param_1 + 0x88,*(undefined4 *)(param_1 + 100),iVar7,0);
      iVar7 = *(int *)(param_1 + 0x78);
      Open__10MenuWindowFUci(iVar7 + 0x58,*(byte *)(iVar7 + 0x108) & 7,
                      *(undefined4 *)(*(int *)(iVar7 + 0x8c) + 0x10));
      Open__10MenuWindowFUci(param_1 + 0x350,*(byte *)(param_1 + 0x400) & 7,
                      *(undefined4 *)(*(int *)(param_1 + 900) + 0x10));
      iVar7 = *(int *)(param_1 + 0x990);
      Open__10MenuWindowFUci(iVar7,*(byte *)(iVar7 + 0xb0) & 7,
                      *(undefined4 *)(*(int *)(iVar7 + 0x34) + 0x10));
      iVar7 = *(int *)(param_1 + 0x994);
      Open__10MenuWindowFUci(iVar7,*(byte *)(iVar7 + 0xb0) & 7,
                      *(undefined4 *)(*(int *)(iVar7 + 0x34) + 0x10));
      iVar7 = *(int *)(param_1 + 0x998);
      Open__10MenuWindowFUci(iVar7,*(byte *)(iVar7 + 0xb0) & 7,
                      *(undefined4 *)(*(int *)(iVar7 + 0x34) + 0x10));
    }
    else {
      *(undefined1 *)(param_1 + 0x9b9) = *(undefined1 *)(param_1 + 0x9ba);
      puVar6 = PTR_SelectSlot__8CmdCrestFv_0050dc98;
      uVar5 = DAT_0050dc94;
      puVar4 = PTR_SelectGoods__8CmdCrestFv_0050dc88;
      uVar3 = DAT_0050dc84;
      if (*(char *)(param_1 + 0x9b9) == '\x04') {
        *(undefined4 *)(param_1 + 0x7c) = _6105;
        *(undefined4 *)(param_1 + 0x80) = uVar3;
        *(undefined **)(param_1 + 0x84) = puVar4;
      }
      else {
        *(undefined4 *)(param_1 + 0x7c) = _6108;
        *(undefined4 *)(param_1 + 0x80) = uVar5;
        *(undefined **)(param_1 + 0x84) = puVar6;
        SetChengePCMode__10CmdPCSceneFUc(param_1,1);
      }
      SetButtonReport__8CmdCrestFv(param_1);
      Open__15CmdButtonReportFv(*(undefined4 *)(param_1 + 0x68));
    }
  }
  return 0;
}

/* JP: 0x00494b50  CmdCrest::ExecDetail()   [ExecDetail__8CmdCrestFv]  size=0x290 */
undefined8 ExecDetail__8CmdCrestFv(int param_1)

{
  int iVar1;
  bool bVar2;
  undefined4 uVar3;
  undefined *puVar4;
  int iVar5;
  
  if ((*(ushort *)(*(int *)(param_1 + 0x10) + 0x48) & 0x5000) == 0) {
    if (*(int *)(*(int *)(param_1 + 0x99c) + 0x44) != 0) {
      if ((*(char *)(*(int *)(param_1 + 0x99c) + 0xa8) == '\x01') ||
         (*(char *)(*(int *)(param_1 + 0x99c) + 0xa8) == '\0')) {
        bVar2 = true;
      }
      else {
        bVar2 = false;
      }
      if (bVar2) {
        iVar1 = *(int *)(*(int *)(param_1 + 0x18) + 0xec);
        iVar5 = MoveVertical__9MenuSceneFi(param_1,0);
        if (iVar1 != iVar5) {
          if (*(short *)(iVar5 + 0x16) < 0) {
            MoveVertical__9MenuSceneFi(param_1,0);
          }
          UpdateScene__14CmdCrestDetailFP9MenuSceneP8CmdPartyP13MenuDataMagics
                    (*(undefined4 *)(param_1 + 0x99c),param_1 + 0xe0,*(undefined4 *)(param_1 + 0x5c)
                     ,*(undefined4 *)(param_1 + 0x9a8),
                     *(undefined2 *)(*(int *)(*(int *)(param_1 + 0x18) + 0xec) + 0x16));
          iVar1 = *(int *)(param_1 + 0x99c);
          Open__10MenuWindowFUci(iVar1,*(byte *)(iVar1 + 0xb0) & 7,
                          *(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x10));
          PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),6,0,0);
        }
      }
    }
  }
  else {
    iVar1 = *(int *)(param_1 + 0x99c);
    Close__10MenuWindowFUci(iVar1,((ulong)*(byte *)(iVar1 + 0xb0) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x14));
    puVar4 = PTR_ExitDetail__8CmdCrestFv_0050dca8;
    uVar3 = DAT_0050dca4;
    *(undefined4 *)(param_1 + 0x7c) = _6158;
    *(undefined4 *)(param_1 + 0x80) = uVar3;
    *(undefined **)(param_1 + 0x84) = puVar4;
    PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),3,0,0);
  }
  return 0;
}

/* JP: 0x00494de0  CmdCrest::ExecSort()   [ExecSort__8CmdCrestFv]  size=0x2c8 */
undefined8 ExecSort__8CmdCrestFv(int param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  undefined *puVar6;
  long lVar7;
  undefined8 uVar8;
  
  iVar2 = *(int *)(param_1 + 0x9a0);
  lVar7 = (**(code **)(*(int *)(iVar2 + 8) + 0x1c))();
  if (lVar7 != 0) {
    cVar1 = *(char *)(iVar2 + 0x20);
    if (cVar1 == '\x04') {
      *(undefined1 *)(*(int *)(param_1 + 0x18) + 0xf9) = 0xfb;
      iVar3 = *(int *)(iVar2 + 0x15c);
      Select__13CmdGoodsCrestFP9MenuSceneP7CmdNoteP9MenuGroupP9MenuGroup
                (*(undefined4 *)(param_1 + 0x994),param_1 + 0x88,*(undefined4 *)(param_1 + 100),
                 iVar3,0);
      iVar4 = *(int *)(*(int *)(param_1 + 0x994) + 0x44);
      *(byte *)(iVar4 + 0x12) = *(byte *)(iVar4 + 0x12) & 0xfe | 1;
      UpdateCrestMagic__8CmdCrestFssc(param_1,1,*(undefined2 *)(iVar3 + 0x16),1);
      SetButtonReport__8CmdCrestFv(param_1);
      Open__15CmdButtonReportFv(*(undefined4 *)(param_1 + 0x68));
      (**(code **)(*(int *)(iVar2 + 8) + 0xc))();
      *(undefined4 *)(param_1 + 0x9a0) = 0;
      puVar6 = PTR_SelectGoods__8CmdCrestFv_0050dcb8;
      uVar5 = DAT_0050dcb4;
      *(undefined4 *)(param_1 + 0x7c) = _6226;
      *(undefined4 *)(param_1 + 0x80) = uVar5;
      *(undefined **)(param_1 + 0x84) = puVar6;
    }
    else if ((cVar1 != '\r') && (cVar1 == '\x0f')) {
      *(char *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x28d) = (char)*(undefined2 *)(iVar2 + 0x15a);
      UpdateGoods__8CmdCrestFsss
                (param_1,1,*(undefined2 *)(*(int *)(param_1 + 0x988) + 0x22),
                 *(undefined2 *)(*(int *)(param_1 + 0x994) + 0xae));
      uVar8 = GetPlace__10MenuWindowFss(*(undefined4 *)(param_1 + 0x994),0,0);
      Select__13CmdGoodsCrestFP9MenuSceneP7CmdNoteP9MenuGroupP9MenuGroup
                (*(undefined4 *)(param_1 + 0x994),param_1 + 0x88,0,uVar8,
                 *(undefined4 *)(iVar2 + 0x15c));
      *(int *)(iVar2 + 0x15c) = (int)uVar8;
      UpdateScene__14CmdCrestPCInfoFP8CmdCrests
                (param_1 + 0x350,param_1,*(undefined2 *)((int)uVar8 + 0x22));
    }
  }
  return 0;
}
