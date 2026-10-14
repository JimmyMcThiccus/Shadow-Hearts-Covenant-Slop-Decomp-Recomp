/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdParty   functions: 13
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdParty.md).
 */

/* JP: 0x0043cad0  CmdParty::CmdParty()   [__ct__8CmdPartyFv]  size=0x48 */
int __ct__8CmdPartyFv(int param_1)

{
  __construct_array(param_1 + 0x30,0x43ad20,0x43ad70,0x4c,8);
  return param_1;
}

/* JP: 0x0043cb20  CmdParty::~CmdParty()   [__dt__8CmdPartyFv]  size=0x74 */
int __dt__8CmdPartyFv(int param_1,short param_2)

{
  if ((param_1 != 0) && (__destroy_arr(param_1 + 0x30,0x43ad70,0x4c,8), 0 < param_2)) {
    __dl__FPv(param_1);
  }
  return param_1;
}

/* JP: 0x0043cba0  CmdParty::Create(MenuDataTable*)   [Create__8CmdPartyFP13MenuDataTable]  size=0x368 */
undefined4 Create__8CmdPartyFP13MenuDataTable(undefined4 *param_1,undefined4 param_2)

{
  char cVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  ulong uVar7;
  int iVar8;
  long lVar9;
  uint uVar10;
  undefined4 *puVar11;
  
  *param_1 = param_2;
  param_1[1] = ourBtlSaveDat__10BtlSaveSec;
  param_1[2] = ourBtlSaveDat__10BtlSaveSec + (uint)*(byte *)(ourBtlSaveDat__10BtlSaveSec + 2) * 0x200 + 0x944;
  iVar3 = Find__13MenuDataTableFs(param_2,7);
  puVar11 = param_1 + 0xc;
  if (*(char *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x80) < '\x05') {
    iVar4 = *(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + *(char *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x80) * 0x20 +
            0x84;
  }
  else {
    iVar4 = *(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0xe4;
  }
  lVar9 = 0;
  while (lVar9 < *(char *)(iVar4 + 0xf)) {
    iVar8 = (int)lVar9;
    cVar1 = *(char *)(iVar4 + iVar8 + 0x12);
    if (-1 < cVar1) {
      Create__5CmdPCFP14_PCParam_Ver00P10MenuDataPCP17_EQUIPParam_Ver00P13MenuDataTable
                (puVar11,param_1[1] + cVar1 * 0xc0 + 0x44,iVar3 + 0x10 + cVar1 * 0x38,param_1[2],
                 param_2);
      UpdateState__5CmdPCFv(puVar11);
      param_1[iVar8 + 4] = puVar11;
      puVar11 = puVar11 + 0x13;
    }
    lVar9 = (long)(iVar8 + 1);
  }
  *(short *)((int)param_1 + 0xe) = (short)lVar9;
  iVar3 = Find__13MenuDataTableFs(param_2,0x11);
  uVar10 = iVar3 + 0x10;
  uVar5 = uVar10 + *(int *)(iVar3 + 8) * 0x24;
  for (; uVar10 < uVar5; uVar10 = uVar10 + 0x24) {
    if (*(short *)(uVar10 + 0x1e) != 0) {
      lVar9 = 0;
      while (lVar9 < *(short *)(uVar10 + 0x1e)) {
        iVar3 = (int)lVar9;
        sVar2 = *(short *)(*(int *)(uVar10 + 0x18) + iVar3 * 8 + 4);
        uVar7 = (long)sVar2 & 7;
        uVar6 = (uint)uVar7;
        if (((long)sVar2 < 0) && (uVar7 != 0)) {
          uVar6 = uVar6 - 8;
        }
        iVar4 = (int)sVar2;
        if (sVar2 < 0) {
          iVar4 = iVar4 + 7;
        }
        if ((1 << (uVar6 & 0x1f) &
            (uint)*(byte *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x180 + (iVar4 >> 3))) != 0) {
          *(undefined1 *)(*(int *)(uVar10 + 0x18) + iVar3 * 8 + 7) = 1;
        }
        lVar9 = (long)(iVar3 + 1);
      }
    }
  }
  ConvertComboKey__8CmdPartyFi(param_1,1);
  return 1;
}

/* JP: 0x0043cf10  CmdParty::FlushData()   [FlushData__8CmdPartyFv]  size=0x2c */
void FlushData__8CmdPartyFv(undefined4 param_1)

{
  ConvertComboKey__8CmdPartyFi(param_1,0);
  return;
}

/* JP: 0x0043cf40  CmdParty::FindPC(unsigned short)   [FindPC__8CmdPartyFUs]  size=0xc4 */
int FindPC__8CmdPartyFUs(int param_1,ushort param_2)

{
  int iVar1;
  ulong uVar2;
  
  uVar2 = 0;
  while( true ) {
    if ((ulong)(long)*(short *)(param_1 + 0xe) <= uVar2) {
      return 0;
    }
    iVar1 = (int)uVar2;
    if (param_2 == *(byte *)(*(int *)(param_1 + iVar1 * 0x4c + 0x30) + 2)) break;
    uVar2 = (ulong)(iVar1 + 1);
  }
  return param_1 + iVar1 * 0x4c + 0x30;
}

/* JP: 0x0043d010  CmdParty::GetPCIndex(unsigned short)   [GetPCIndex__8CmdPartyFUs]  size=0xa4 */
ulong GetPCIndex__8CmdPartyFUs(int param_1,ushort param_2)

{
  ulong uVar1;
  
  uVar1 = 0;
  while( true ) {
    if ((ulong)(long)*(short *)(param_1 + 0xe) <= uVar1) {
      return 0xffffffffffffffff;
    }
    if (param_2 == *(byte *)(*(int *)(param_1 + (int)uVar1 * 0x4c + 0x30) + 2)) break;
    uVar1 = (ulong)((int)uVar1 + 1);
  }
  return uVar1;
}

/* JP: 0x0043d0c0  CmdParty::SortPC(char*)   [SortPC__8CmdPartyFPc]  size=0xa8 */
void SortPC__8CmdPartyFPc(int param_1,undefined1 *param_2)

{
  undefined4 uVar1;
  short sVar2;
  undefined1 *puStack_10;
  
  puStack_10 = param_2;
  for (sVar2 = 0; sVar2 < *(short *)(param_1 + 0xe); sVar2 = sVar2 + 1) {
    uVar1 = FindPC__8CmdPartyFUs(param_1,*puStack_10);
    *(undefined4 *)(param_1 + sVar2 * 4 + 0x10) = uVar1;
    puStack_10 = puStack_10 + 1;
  }
  return;
}

/* JP: 0x0043d170  CmdParty::SetCommand(char)   [SetCommand__8CmdPartyFc]  size=0x80 */
void SetCommand__8CmdPartyFc(int param_1,undefined1 param_2)

{
  ulong uVar1;
  
  for (uVar1 = 0; uVar1 < (ulong)(long)*(short *)(param_1 + 0xe); uVar1 = (ulong)((int)uVar1 + 1)) {
    SetCommand__5CmdPCFc(param_1 + (int)uVar1 * 0x4c + 0x30,param_2);
  }
  return;
}

/* JP: 0x0043d1f0  CmdParty::GetLibraryMonster(short*, short*)   [GetLibraryMonster__8CmdPartyFPsPs]  size=0x248 */
void GetLibraryMonster__8CmdPartyFPsPs(undefined4 *param_1,short *param_2,short *param_3)

{
  short sVar1;
  bool bVar2;
  bool bVar3;
  int iVar4;
  uint uVar5;
  ulong uVar6;
  short *psVar7;
  uint uVar8;
  short *psVar9;
  uint uVar10;
  
  iVar4 = Find__13MenuDataTableFs(*param_1,0x14);
  uVar8 = iVar4 + 0x10;
  uVar10 = uVar8 + *(int *)(iVar4 + 8) * 0x20;
  *param_2 = 0;
  *param_3 = 0;
  for (; uVar8 < uVar10; uVar8 = uVar8 + 0x20) {
    bVar2 = false;
    bVar3 = false;
    psVar7 = (short *)(uVar8 + 0x12);
    psVar9 = psVar7 + *(char *)(uVar8 + 0x11);
    for (; psVar7 < psVar9; psVar7 = psVar7 + 1) {
      sVar1 = *psVar7;
      iVar4 = (int)sVar1;
      if (sVar1 < 0) {
        iVar4 = iVar4 + 7;
      }
      uVar6 = (long)sVar1 & 7;
      uVar5 = (uint)uVar6;
      if (((long)sVar1 < 0) && (uVar6 != 0)) {
        uVar5 = uVar5 - 8;
      }
      if (((uint)*(byte *)(param_1[1] + (iVar4 >> 3) + 0xdaf) & 1 << (uVar5 & 0x1f)) != 0) {
        bVar2 = true;
      }
      sVar1 = *psVar7;
      iVar4 = (int)sVar1;
      if (sVar1 < 0) {
        iVar4 = iVar4 + 7;
      }
      uVar6 = (long)sVar1 & 7;
      uVar5 = (uint)uVar6;
      if (((long)sVar1 < 0) && (uVar6 != 0)) {
        uVar5 = uVar5 - 8;
      }
      if (((uint)*(byte *)(param_1[1] + (iVar4 >> 3) + 0xdcf) & 1 << (uVar5 & 0x1f)) != 0) {
        bVar3 = true;
      }
    }
    if (bVar2) {
      *param_2 = *param_2 + 1;
    }
    if (bVar3) {
      *param_3 = *param_3 + 1;
    }
  }
  return;
}

/* JP: 0x0043d440  CmdParty::GetRestRingItem(short)   [GetRestRingItem__8CmdPartyFs]  size=0x268 */
char GetRestRingItem__8CmdPartyFs(int param_1,short param_2)

{
  char cVar1;
  char cVar2;
  int *piVar3;
  int *piVar4;
  char *pcVar5;
  
  cVar2 = '\0';
  piVar3 = (int *)(param_1 + 0x30);
  piVar4 = piVar3 + *(short *)(param_1 + 0xe) * 0x12 + (int)*(short *)(param_1 + 0xe);
  if (param_2 == 2) {
    for (; piVar3 < piVar4; piVar3 = piVar3 + 0x13) {
      for (pcVar5 = (char *)(*piVar3 + 0x5f); pcVar5 < (char *)(*piVar3 + 100); pcVar5 = pcVar5 + 1)
      {
        cVar2 = cVar2 + *pcVar5;
      }
    }
  }
  else if (param_2 == 1) {
    for (; piVar3 < piVar4; piVar3 = piVar3 + 0x13) {
      for (pcVar5 = (char *)(*piVar3 + 0x5a); pcVar5 < (char *)(*piVar3 + 0x5f); pcVar5 = pcVar5 + 1
          ) {
        cVar2 = cVar2 + *pcVar5;
      }
    }
  }
  else if (param_2 == 0) {
    for (; piVar3 < piVar4; piVar3 = piVar3 + 0x13) {
      cVar1 = GetExpansionRingItem__5CmdPCFv(piVar3);
      if ('\0' < cVar1) {
        cVar2 = cVar2 + cVar1;
      }
    }
  }
  else {
    for (; piVar3 < piVar4; piVar3 = piVar3 + 0x13) {
      if ((long)param_2 == (long)*(char *)(*piVar3 + 100)) {
        cVar2 = cVar2 + '\x01';
      }
    }
  }
  return *(char *)(*(int *)(param_1 + 8) + (int)param_2 + 0x174) - cVar2;
}

/* JP: 0x0043d6b0  CmdParty::GetComboKeyData(short, SHORTCUTCommand*, char*, CmdComboKeyData*)   [GetComboKeyData__8CmdPartyFsP15SHORTCUTCommandPcP15CmdComboKeyData]  size=0x5c4 */
undefined4
GetComboKeyData__8CmdPartyFsP15SHORTCUTCommandPcP15CmdComboKeyData
          (undefined4 *param_1,short param_2,char *param_3,int param_4,undefined4 *param_5)

{
  char cVar1;
  byte bVar2;
  ushort uVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  char *pcVar10;
  ushort *puStack_68;
  
  iVar4 = Find__13MenuDataTableFs(*param_1,0x31);
  iVar5 = param_2 * 0xc + iVar4;
  cVar1 = *param_3;
  uVar3 = *(ushort *)(param_3 + 2);
  if (((uint)*(byte *)(iVar5 + 0x1a) & 1 << ((int)cVar1 & 0x1fU)) != 0) {
    uVar8 = (uint)(short)uVar3;
    if (cVar1 == '\0') {
      if (((uint)*(byte *)(iVar5 + 0x1b) & 1 << (uVar8 & 0x1f)) != 0) {
        if (param_5 != (undefined4 *)0x0) {
          iVar4 = Find__13MenuDataTableFs(*param_1,0x32);
          iVar4 = uVar8 * 0xc + iVar4;
          *param_5 = *(undefined4 *)(iVar4 + 0x10);
          param_5[1] = *(undefined4 *)(iVar4 + 0x14);
          *(undefined2 *)(param_5 + 2) = 0xffff;
          *(short *)((int)param_5 + 10) = (short)*(char *)(iVar4 + 0x18);
        }
        return 1;
      }
    }
    else if (cVar1 == '\x01') {
      iVar4 = GetRegDat__9RegDatApiFiii(0x33,uVar3,0xffffffffffffffff);
      bVar2 = *(byte *)(param_1[2] + uVar8);
      if ((((ulong)*(byte *)(iVar4 + 4) & 0x7f) >> 5 == 0) && (bVar2 != 0)) {
        if (param_5 != (undefined4 *)0x0) {
          uVar6 = GetRegDat__9RegDatApiFiii(9,uVar3,0xffffffffffffffff);
          *param_5 = uVar6;
          uVar6 = GetRegDat__9RegDatApiFiii(0x1a,uVar3,0xffffffffffffffff);
          param_5[1] = uVar6;
          *(ushort *)(param_5 + 2) = (ushort)bVar2;
        }
        return 1;
      }
    }
    else if (cVar1 == '\x02') {
      iVar5 = GetRegDat__9RegDatApiFiii(0x38,uVar3,0xffffffffffffffff);
      cVar1 = *(char *)(param_4 + uVar8);
      if (((uVar3 == *(byte *)(iVar4 + 3)) || (((ulong)*(byte *)(iVar5 + 4) & 0x7f) >> 5 == 0)) &&
         (cVar1 != '\0')) {
        if (param_5 != (undefined4 *)0x0) {
          uVar6 = GetRegDat__9RegDatApiFiii(0xe,uVar3,0xffffffffffffffff);
          *param_5 = uVar6;
          uVar6 = GetRegDat__9RegDatApiFiii(0x1f,uVar3,0xffffffffffffffff);
          param_5[1] = uVar6;
          if (cVar1 == '\0') {
            trap(7);
          }
          *(short *)(param_5 + 2) = *(short *)(iVar5 + 0x1e) / (short)cVar1;
          *(ushort *)((int)param_5 + 10) = (ushort)(((ulong)*(byte *)(iVar5 + 6) << 0x3c) >> 0x3d);
        }
        return 1;
      }
    }
    else if (cVar1 == '\x03') {
      iVar4 = GetRegDat__9RegDatApiFiii(0x36,*(undefined2 *)(iVar5 + 0x16),uVar3);
      if (((ulong)*(byte *)(iVar4 + 4) & 0x7f) >> 5 != 0) {
        return 0;
      }
      if (param_2 < 0xc) {
        iVar7 = FindPC__8CmdPartyFUs(param_1,param_2);
        if ((1 << (uVar8 & 0x1f) & *(uint *)(iVar7 + 0x28)) == 0) {
          return 0;
        }
      }
      else {
        iVar7 = GetRegDat__9RegDatApiFiii(0x2c,param_2 + -0xc,0xffffffffffffffff);
        puStack_68 = (ushort *)(iVar7 + 8);
        iVar9 = 0;
        for (pcVar10 = (char *)(iVar7 + 0x16);
            (iVar9 < 7 &&
            ((*puStack_68 != uVar3 ||
             ((char)(*(char *)(param_1[1] + (int)(short)(param_2 + -0xc) + 0xd94) + '\x01') <
              *pcVar10)))); pcVar10 = pcVar10 + 1) {
          iVar9 = iVar9 + 1;
          puStack_68 = puStack_68 + 1;
        }
        if (iVar9 == 7) {
          return 0;
        }
      }
      if (param_5 != (undefined4 *)0x0) {
        uVar6 = GetRegDat__9RegDatApiFiii(0xc,*(undefined2 *)(iVar5 + 0x16),uVar3);
        *param_5 = uVar6;
        uVar6 = GetRegDat__9RegDatApiFiii(0x1d,*(undefined2 *)(iVar5 + 0x16),uVar3);
        param_5[1] = uVar6;
        *(undefined2 *)(param_5 + 2) = *(undefined2 *)(iVar4 + 0x1e);
        *(ushort *)((int)param_5 + 10) = (ushort)(((ulong)*(byte *)(iVar4 + 6) << 0x3c) >> 0x3d);
      }
      return 1;
    }
  }
  return 0;
}

/* JP: 0x0043dc80  CmdParty::GetComboKeyCount(short, short)   [GetComboKeyCount__8CmdPartyFss]  size=0x12c */
undefined4 GetComboKeyCount__8CmdPartyFss(undefined4 *param_1,short param_2,short param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = 0;
  if (param_2 == 3) {
    iVar1 = Find__13MenuDataTableFs(*param_1,0x31);
    uVar2 = GetRegCnt__9RegDatApiFii(0x36,*(undefined2 *)(param_3 * 0xc + iVar1 + 0x16));
  }
  else if (param_2 == 2) {
    uVar2 = GetRegCnt__9RegDatApiFii(0x38,0xffffffffffffffff);
  }
  else if (param_2 == 1) {
    uVar2 = GetRegCnt__9RegDatApiFii(0x33,0xffffffffffffffff);
  }
  else if (param_2 == 0) {
    iVar1 = Find__13MenuDataTableFs(*param_1,0x32);
    uVar2 = *(undefined4 *)(iVar1 + 8);
  }
  return uVar2;
}

/* JP: 0x0043ddb0  CmdParty::ConvertComboKey(int)   [ConvertComboKey__8CmdPartyFi]  size=0xbc */
void ConvertComboKey__8CmdPartyFi(undefined4 *param_1,int param_2)

{
  int iVar1;
  char *pcVar2;
  char *pcVar3;
  
  pcVar2 = (char *)(param_1[1] + 0xf44);
  iVar1 = Find__13MenuDataTableFs(*param_1,0x31);
  pcVar3 = pcVar2 + *(int *)(iVar1 + 8) * 0x10;
  for (; pcVar2 < pcVar3; pcVar2 = pcVar2 + 4) {
    if (*pcVar2 == '\0') {
      if (param_2 == 0) {
        pcVar2[2] = -1;
        pcVar2[3] = -1;
      }
      else {
        *(short *)(pcVar2 + 2) = (short)pcVar2[1];
      }
    }
  }
  return;
}
