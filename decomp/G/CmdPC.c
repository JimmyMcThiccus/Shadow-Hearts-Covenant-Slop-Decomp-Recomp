/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdPC   functions: 21
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdPC.md).
 */

/* JP: 0x0043ad20  CmdPC::CmdPC()   [__ct__5CmdPCFv]  size=0x48 */
int __ct__5CmdPCFv(int param_1)

{
  *(undefined4 *)(param_1 + 0x28) = 0;
  *(undefined4 *)(param_1 + 0x2c) = 0;
  *(undefined4 *)(param_1 + 0x30) = 0;
  *(undefined4 *)(param_1 + 0x34) = 0;
  *(undefined1 *)(param_1 + 0x45) = 0;
  *(undefined4 *)(param_1 + 0x48) = 0;
  return param_1;
}

/* JP: 0x0043ad70  CmdPC::~CmdPC()   [__dt__5CmdPCFv]  size=0xb8 */
int __dt__5CmdPCFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    if (((sm_pFace__7MenuObj != 0) && (*(char *)(param_1 + 0x41) != '\0')) &&
       (*(int *)(param_1 + 0x30) != 0)) {
      ReleaseHandle__11FileManegerFi(sm_pFace__7MenuObj,*(undefined4 *)(*(int *)(param_1 + 0x30) + 0x18));
    }
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x0043ae30  CmdPC::Create(_PCParam_Ver00*, MenuDataPC*, _EQUIPParam_Ver00*, MenuDataTable*)   [Create__5CmdPCFP14_PCParam_Ver00P10MenuDataPCP17_EQUIPParam_Ver00P13MenuDataTable]  size=0x43c */
void Create__5CmdPCFP14_PCParam_Ver00P10MenuDataPCP17_EQUIPParam_Ver00P13MenuDataTable
               (int *param_1,int param_2,int param_3,undefined8 param_4,undefined4 param_5)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int *piVar6;
  char *pcVar7;
  char *pcVar8;
  int iVar9;
  
  iVar1 = ourBtlSaveDat__10BtlSaveSec;
  *param_1 = param_2;
  param_1[1] = param_3;
  *(undefined1 *)((int)param_1 + 0x3f) = *(undefined1 *)(param_3 + 0x32);
  memcpy(param_1 + 0xe,param_3 + 0x2a,5);
  iVar2 = GetHandle__11FileManegerFib(sm_pFace__7MenuObj,*(undefined2 *)(*param_1 + 8),0);
  param_1[0xc] = iVar2;
  *(undefined1 *)((int)param_1 + 0x41) = 1;
  if (*(int *)(param_1[0xc] + 0x14) != 0) {
    *(undefined1 *)((int)param_1 + 0x41) = 0;
  }
  for (piVar6 = param_1 + 0xe; piVar6 < (int *)((int)param_1 + 0x3d);
      piVar6 = (int *)((int)piVar6 + 1)) {
    if (*(char *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + (int)(short)((char)*piVar6 + 0x18) + 0x300) == '\0')
    {
      *(char *)piVar6 = -1;
    }
  }
  switch(*(undefined1 *)(*param_1 + 2)) {
  case 0:
    param_1[0xb] = *(uint *)(iVar1 + 0xd4c) & 0x7fff;
    break;
  case 1:
    param_1[10] = 0x1000;
    break;
  case 2:
    param_1[10] = *(int *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x2fc);
    break;
  case 4:
    iVar2 = GetRegCnt__9RegDatApiFii(0x36,4);
    for (uVar5 = 0; (int)uVar5 < iVar2; uVar5 = uVar5 + 1) {
      uVar3 = uVar5;
      if ((int)uVar5 < 0) {
        uVar3 = uVar5 + 7;
      }
      uVar4 = uVar5 & 7;
      if (((int)uVar5 < 0) && (uVar4 != 0)) {
        uVar4 = uVar4 - 8;
      }
      if ((*(byte *)(iVar1 + ((int)uVar3 >> 3) + 0xe2f) & uVar4) != 0) {
        param_1[10] = param_1[10] | 1 << (uVar5 & 0x1f);
      }
    }
    break;
  case 5:
    iVar2 = Find__13MenuDataTableFs(param_5,0x33);
    iVar9 = iVar2 + 0x10;
    for (uVar5 = 0; (int)uVar5 < *(int *)(iVar2 + 8); uVar5 = uVar5 + 1) {
      if (((uint)*(ushort *)(iVar1 + 0xe32) & 1 << (uVar5 & 0x1f)) != 0) {
        param_1[10] = param_1[10] | 1 << (uVar5 & 0x1f);
        param_1[10] = param_1[10] & (uint)*(ushort *)(iVar9 + 2);
      }
      iVar9 = iVar9 + 4;
    }
    if (*(short *)(*param_1 + 4) == 6) {
      *(undefined1 *)((int)param_1 + 0x3f) = 0xff;
    }
    break;
  case 6:
    param_1[10] = (int)*(char *)(iVar1 + 0xe37);
    break;
  case 7:
    param_1[0xb] = *(uint *)(iVar1 + 0xd4c) & 0x18000;
    break;
  case 0xb:
    param_1[10] = (uint)*(ushort *)(*param_1 + 0x3a);
  }
  pcVar7 = (char *)((int)param_1 + 0x39);
  pcVar8 = (char *)((int)param_1 + 0x3a);
  if (*pcVar7 == -1) {
    *pcVar7 = *pcVar8;
  }
  if (*pcVar8 == -1) {
    *pcVar8 = *pcVar7;
  }
  return;
}

/* JP: 0x0043b270  CmdPC::UpdateState()   [UpdateState__5CmdPCFv]  size=0x108 */
void UpdateState__5CmdPCFv(int *param_1)

{
  int iVar1;
  undefined8 uVar2;
  
  *(undefined2 *)((int)param_1 + 0x42) = *(undefined2 *)(*param_1 + 4);
  *(undefined1 *)(param_1 + 0x10) = *(undefined1 *)((int)param_1 + 0x3f);
  if (*(char *)(*param_1 + 2) == '\x06') {
    uVar2 = GetYoahism__10BtlSaveSecFv();
    iVar1 = GetRegDat__9RegDatApiFiii(0x40,uVar2,0xffffffffffffffff);
    *(undefined2 *)((int)param_1 + 0x42) = *(undefined2 *)(iVar1 + 6);
    param_1[0x12] = iVar1 + 10;
    *(char *)(param_1 + 0x10) = (char)(((ulong)*(byte *)(iVar1 + 4) & 3) >> 1) + -1;
    *(byte *)((int)param_1 + 0x45) = *(byte *)(iVar1 + 4) & 1;
  }
  GetRealStatus__5CmdPCFP11CmdPCStatus(param_1,param_1 + 2);
  param_1[9] = 0;
  return;
}

/* JP: 0x0043b380  CmdPC::SetCommand(char)   [SetCommand__5CmdPCFc]  size=0x6c */
void SetCommand__5CmdPCFc(int param_1,char param_2)

{
  if (param_2 == -2) {
    *(int *)(param_1 + 0x34) = param_1 + 0x38;
  }
  else {
    *(char *)(param_1 + 0x44) = param_2;
    *(int *)(param_1 + 0x34) = param_1 + 0x44;
  }
  return;
}

/* JP: 0x0043b3f0  CmdPC::GetRealStatus(CmdPCStatus*)   [GetRealStatus__5CmdPCFP11CmdPCStatus]  size=0x484 */
void GetRealStatus__5CmdPCFP11CmdPCStatus(int *param_1,int param_2)

{
  byte *pbVar1;
  undefined1 uVar2;
  undefined2 uVar3;
  
  uVar3 = GetRealMaxHP__10BtlSaveSecFiPc(*(undefined1 *)(*param_1 + 2),0);
  *(undefined2 *)(param_2 + 8) = uVar3;
  uVar3 = GetRealMaxMP__10BtlSaveSecFiPc(*(undefined1 *)(*param_1 + 2),0);
  *(undefined2 *)(param_2 + 10) = uVar3;
  uVar3 = GetRealMaxSP__10BtlSaveSecFiPc(*(undefined1 *)(*param_1 + 2),0);
  *(undefined2 *)(param_2 + 0xc) = uVar3;
  uVar2 = GetRealStr__10BtlSaveSecFiPc(*(undefined1 *)(*param_1 + 2),0);
  *(undefined1 *)(param_2 + 0x16) = uVar2;
  uVar2 = GetRealVit__10BtlSaveSecFiPc(*(undefined1 *)(*param_1 + 2),0);
  *(undefined1 *)(param_2 + 0x17) = uVar2;
  uVar2 = GetRealInt__10BtlSaveSecFiPc(*(undefined1 *)(*param_1 + 2),0);
  *(undefined1 *)(param_2 + 0x19) = uVar2;
  uVar2 = GetRealPow__10BtlSaveSecFiPc(*(undefined1 *)(*param_1 + 2),0);
  *(undefined1 *)(param_2 + 0x1a) = uVar2;
  uVar2 = GetRealAgl__10BtlSaveSecFiPc(*(undefined1 *)(*param_1 + 2),0);
  *(undefined1 *)(param_2 + 0x18) = uVar2;
  uVar2 = GetRealLuc__10BtlSaveSecFiPc(*(undefined1 *)(*param_1 + 2),0);
  *(undefined1 *)(param_2 + 0x1b) = uVar2;
  uVar3 = GetRealPAtk__10BtlSaveSecFiPcPc(*(undefined1 *)(*param_1 + 2),0,0);
  *(undefined2 *)(param_2 + 0xe) = uVar3;
  uVar3 = GetRealSAtk__10BtlSaveSecFiPcPc(*(undefined1 *)(*param_1 + 2),0,0);
  *(undefined2 *)(param_2 + 0x12) = uVar3;
  uVar3 = GetRealPDef__10BtlSaveSecFiPcPc(*(undefined1 *)(*param_1 + 2),0,0);
  *(undefined2 *)(param_2 + 0x10) = uVar3;
  uVar3 = GetRealSDef__10BtlSaveSecFiPcPc(*(undefined1 *)(*param_1 + 2),0,0);
  *(undefined2 *)(param_2 + 0x14) = uVar3;
  *(undefined2 *)(param_2 + 2) = *(undefined2 *)(*param_1 + 0x1e);
  *(undefined2 *)(param_2 + 4) = *(undefined2 *)(*param_1 + 0x22);
  *(short *)(param_2 + 6) = (short)*(char *)(*param_1 + 0x25);
  pbVar1 = (byte *)param_1[0x12];
  if (pbVar1 != (byte *)0x0) {
    *(short *)(param_2 + 8) = (short)((int)((int)*(short *)(param_2 + 8) * (uint)*pbVar1) / 100);
    *(short *)(param_2 + 2) = (short)((int)((int)*(short *)(param_2 + 2) * (uint)*pbVar1) / 100);
    *(short *)(param_2 + 0xe) =
         (short)((int)((int)*(short *)(param_2 + 0xe) * (uint)pbVar1[1]) / 100);
    *(short *)(param_2 + 0x12) =
         (short)((int)((int)*(short *)(param_2 + 0x12) * (uint)pbVar1[2]) / 100);
  }
  if (*(short *)(param_2 + 8) < *(short *)(param_2 + 2)) {
    *(undefined2 *)(param_2 + 2) = *(undefined2 *)(param_2 + 8);
  }
  if (*(short *)(param_2 + 10) < *(short *)(param_2 + 4)) {
    *(undefined2 *)(param_2 + 4) = *(undefined2 *)(param_2 + 10);
  }
  *(undefined2 *)(param_2 + 6) = *(undefined2 *)(param_2 + 0xc);
  return;
}

/* JP: 0x0043b880  CmdPC::GetRealStatus(CmdPCStatus*, char, char)   [GetRealStatus__5CmdPCFP11CmdPCStatuscc]  size=0x264 */
void GetRealStatus__5CmdPCFP11CmdPCStatuscc
               (int *param_1,short *param_2,char param_3,undefined1 param_4)

{
  undefined1 uVar1;
  uint uVar2;
  byte *pbVar3;
  short *psVar4;
  byte *pbVar5;
  short *psVar6;
  undefined1 *puVar7;
  
  puVar7 = (undefined1 *)(*param_1 + (int)param_3 + 0x2d);
  uVar1 = *puVar7;
  *puVar7 = param_4;
  GetRealStatus__5CmdPCFP11CmdPCStatus(param_1,param_2);
  param_2[1] = *(short *)((int)param_1 + 10);
  param_2[2] = (short)param_1[3];
  param_2[3] = *(short *)((int)param_1 + 0xe);
  param_2[0xe] = 0;
  param_2[0xf] = 0;
  pbVar3 = (byte *)((int)param_1 + 0x1e);
  pbVar5 = (byte *)(param_2 + 0xb);
  uVar2 = 0;
  psVar6 = param_2;
  for (psVar4 = (short *)((int)param_1 + 10); psVar6 = psVar6 + 1,
      psVar4 < (short *)((int)param_1 + 0x1e); psVar4 = psVar4 + 1) {
    if (*psVar4 < *psVar6) {
      *(uint *)(param_2 + 0xe) = *(uint *)(param_2 + 0xe) | 1 << (uVar2 & 0x1f);
    }
    else if (*psVar6 < *psVar4) {
      *(uint *)(param_2 + 0xe) = *(uint *)(param_2 + 0xe) | 2 << (uVar2 & 0x1f);
    }
    uVar2 = uVar2 + 2;
  }
  for (; pbVar3 < param_1 + 9; pbVar3 = pbVar3 + 1) {
    if (*pbVar3 < *pbVar5) {
      *(uint *)(param_2 + 0xe) = *(uint *)(param_2 + 0xe) | 1 << (uVar2 & 0x1f);
    }
    else if (*pbVar5 < *pbVar3) {
      *(uint *)(param_2 + 0xe) = *(uint *)(param_2 + 0xe) | 2 << (uVar2 & 0x1f);
    }
    pbVar5 = pbVar5 + 1;
    uVar2 = uVar2 + 2;
  }
  *puVar7 = uVar1;
  return;
}

/* JP: 0x0043baf0  CmdPC::FlushParameter(ECResult*)   [FlushParameter__5CmdPCFP8ECResult]  size=0xd8 */
undefined4 FlushParameter__5CmdPCFP8ECResult(int param_1,short *param_2)

{
  GetRealStatus__5CmdPCFP11CmdPCStatus(param_1,param_1 + 8);
  if (param_2 != (short *)0x0) {
    if ((*param_2 != 0) && (*(short *)(param_1 + 10) < *(short *)(param_1 + 0x10))) {
      return 0;
    }
    if ((param_2[1] != 0) && (*(short *)(param_1 + 0xc) < *(short *)(param_1 + 0x12))) {
      return 0;
    }
  }
  return 1;
}

/* JP: 0x0043bbd0  CmdPC::TakeOffEquipment()   [TakeOffEquipment__5CmdPCFv]  size=0x5c */
void TakeOffEquipment__5CmdPCFv(int *param_1)

{
  int iVar1;
  undefined1 *puVar2;
  
  iVar1 = *param_1;
  for (puVar2 = (undefined1 *)(iVar1 + 0x2d); puVar2 < (undefined1 *)(iVar1 + 0x32);
      puVar2 = puVar2 + 1) {
    *puVar2 = 0xff;
  }
  return;
}

/* JP: 0x0043bc30  CmdPC::CreateMagic(CmdParty*, short, char*)   [CreateMagic__5CmdPCFP8CmdPartysPc]  size=0x248 */
int CreateMagic__5CmdPCFP8CmdPartysPc(int *param_1,int param_2,undefined2 param_3,int param_4)

{
  char cVar1;
  byte bVar2;
  ushort uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  ulong uVar8;
  short *psVar9;
  uint uVar10;
  int iVar11;
  short sVar12;
  char *pcVar13;
  
  if (param_4 != 0) {
    memset(param_4,0,param_3);
  }
  iVar11 = 0;
  iVar4 = *param_1;
  for (pcVar13 = (char *)(iVar4 + 0x32); pcVar13 < (char *)(iVar4 + 0x3a); pcVar13 = pcVar13 + 1) {
    if (-1 < *pcVar13) {
      iVar5 = GetRegDat__9RegDatApiFiii(0x37,*pcVar13,0xffffffffffffffff);
      cVar1 = *pcVar13;
      sVar12 = (short)cVar1;
      iVar6 = (int)(short)cVar1;
      if (sVar12 < 0) {
        iVar6 = iVar6 + 7;
      }
      bVar2 = *(byte *)(*(int *)(param_2 + 8) + (iVar6 >> 3) + 0x16a);
      uVar8 = (long)sVar12 & 7;
      uVar7 = (uint)uVar8;
      if (((long)sVar12 < 0) && (uVar8 != 0)) {
        uVar7 = uVar7 - 8;
      }
      uVar3 = *(ushort *)(iVar5 + 6);
      psVar9 = (short *)(iVar5 + 8);
      for (uVar10 = 0; (int)uVar10 < 4; uVar10 = uVar10 + 1) {
        if ((-1 < *psVar9) &&
           ((((uint)uVar3 & 1 << (uVar10 & 0x1f)) == 0 ||
            (((int)(uint)bVar2 >> (uVar7 & 0x1f) & 1U) != 0)))) {
          if (param_4 != 0) {
            *(char *)(param_4 + *psVar9) = *(char *)(param_4 + *psVar9) + '\x01';
          }
          iVar11 = iVar11 + 1;
        }
        psVar9 = psVar9 + 1;
      }
    }
  }
  return iVar11;
}

/* JP: 0x0043be80  CmdPC::GetRestCrestSlot()   [GetRestCrestSlot__5CmdPCFv]  size=0xcc */
char GetRestCrestSlot__5CmdPCFv(int *param_1)

{
  int iVar1;
  int iVar2;
  char cVar3;
  char *pcVar4;
  
  cVar3 = *(char *)(*param_1 + 0x2c);
  iVar1 = *param_1;
  for (pcVar4 = (char *)(iVar1 + 0x32); pcVar4 < (char *)(iVar1 + 0x3a); pcVar4 = pcVar4 + 1) {
    if (-1 < *pcVar4) {
      iVar2 = GetRegDat__9RegDatApiFiii(0x37,*pcVar4,0xffffffffffffffff);
      cVar3 = cVar3 - *(char *)(iVar2 + 4);
    }
  }
  return cVar3;
}

/* JP: 0x0043bf50  CmdPC::GetExpansionRingItem()   [GetExpansionRingItem__5CmdPCFv]  size=0x90 */
short GetExpansionRingItem__5CmdPCFv(int *param_1)

{
  short sVar1;
  
  sVar1 = (ushort)(((ulong)*(byte *)(*param_1 + 0x58) << 0x3a) >> 0x3d) -
          (*(byte *)(*param_1 + 0x58) & 7);
  if (sVar1 < 0) {
    sVar1 = 0;
  }
  return sVar1;
}

/* JP: 0x0043bfe0  CmdPC::CreateJudgmentRing(JRing*, unsigned char)   [CreateJudgmentRing__5CmdPCFP5JRingUc]  size=0x1cc */
long CreateJudgmentRing__5CmdPCFP5JRingUc(int *param_1,int param_2,byte param_3)

{
  int iVar1;
  ulong uVar2;
  long lVar3;
  undefined2 *puVar4;
  undefined2 *puVar5;
  byte bStack_10;
  
  AllAreaInitialize__5JRingFv(param_2);
  if ((*(byte *)(*param_1 + 0x59) & 1) == 0) {
    bStack_10 = param_3;
    if (param_3 == 0xff) {
      bStack_10 = *(byte *)(*param_1 + 0x58) >> 6;
    }
    uVar2 = ((ulong)*(byte *)(*param_1 + 0x58) & 0x3f) >> 3;
  }
  else {
    bStack_10 = 1;
    uVar2 = 1;
  }
  iVar1 = GetRegDat__9RegDatApiFiii(0x2b,*(undefined1 *)(*param_1 + 2),uVar2);
  puVar4 = (undefined2 *)(iVar1 + 2);
  puVar5 = puVar4 + (int)uVar2 * 3;
  for (; puVar4 < puVar5; puVar4 = puVar4 + 3) {
    AddStrikeArea__5JRingFsssP7_rgba32P7_rgba32(param_2,*puVar4,puVar4[1],puVar4[2],0,0);
  }
  *(byte *)(param_2 + 0x41) = *(byte *)(param_2 + 0x41) & 0xf3 | (bStack_10 & 3) << 2;
  lVar3 = CustomJudgmentRing__5CmdPCFP5JRingi(param_1,param_2,0);
  if (lVar3 == 0) {
    AreaReset__5JRingFv(param_2);
  }
  return lVar3;
}

/* JP: 0x0043c1b0  CmdPC::CustomJudgmentRing(JRing*, int)   [CustomJudgmentRing__5CmdPCFP5JRingi]  size=0x250 */
char CustomJudgmentRing__5CmdPCFP5JRingi(int *param_1,int param_2,int param_3)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  char cVar4;
  int iVar5;
  ulong uVar6;
  uint uVar7;
  ulong uVar8;
  int unaff_s1_lo;
  char acStack_50 [5];
  undefined1 auStack_4b [5];
  undefined1 auStack_46 [5];
  undefined1 auStack_41 [17];
  int *piStack_30;
  int iStack_20;
  int iStack_10;
  
  piStack_30 = param_1;
  iStack_20 = param_2;
  iStack_10 = param_3;
  memset(acStack_50,0,0x14);
  uVar6 = ((ulong)*(byte *)(*piStack_30 + 0x58) & 0x3f) >> 3;
  iVar2 = *piStack_30;
  iVar3 = *piStack_30;
  iVar5 = GetRegDat__9RegDatApiFiii(0x30,*(undefined1 *)(*piStack_30 + 0x2d),0xffffffffffffffff);
  uVar7 = (int)uVar6 - 1U & 0xffff;
  if ((((uVar7 == 4) || (uVar7 == 3)) || (uVar7 == 2)) || ((uVar7 == 1 || (uVar7 == 0)))) {
    unaff_s1_lo = iVar5 + 0x28;
  }
  bVar1 = *(byte *)(*piStack_30 + 0x58);
  uVar8 = 0;
  while (uVar8 < uVar6) {
    iVar5 = (int)uVar8;
    acStack_50[iVar5] = *(char *)(iVar2 + 0x5a + iVar5) << 1;
    auStack_4b[iVar5] = *(undefined1 *)(unaff_s1_lo + iVar5);
    auStack_46[iVar5] = *(undefined1 *)(iVar3 + 0x5f + iVar5);
    auStack_41[iVar5] =
         *(undefined1 *)(unaff_s1_lo + (uint)(((ulong)bVar1 << 0x3a) >> 0x3d) + iVar5);
    uVar8 = (long)(iVar5 + 1) & 0xffff;
  }
  cVar4 = JRCustomCheck__5JRingFP8JRCUSTOM(iStack_20,acStack_50);
  if ((cVar4 != '\0') && (iStack_10 == 0)) {
    *(char **)(iStack_20 + 0x4f4) = acStack_50;
    AreaReset__5JRingFv(iStack_20);
  }
  return cVar4;
}

/* JP: 0x0043c400  CmdPC::IsExpandRing(unsigned char*)   [IsExpandRing__5CmdPCFPUc]  size=0x78 */
undefined4 IsExpandRing__5CmdPCFPUc(undefined8 param_1,char *param_2)

{
  char *pcStack_10;
  
  pcStack_10 = param_2;
  while( true ) {
    if (param_2 + 5 <= pcStack_10) {
      return 0;
    }
    if (*pcStack_10 != '\0') break;
    pcStack_10 = pcStack_10 + 1;
  }
  return 1;
}

/* JP: 0x0043c480  CmdPC::ResetExpansion(unsigned char*)   [ResetExpansion__5CmdPCFPUc]  size=0x58 */
void ResetExpansion__5CmdPCFPUc(undefined8 param_1,undefined1 *param_2)

{
  undefined1 *puStack_10;
  
  for (puStack_10 = param_2; puStack_10 < param_2 + 5; puStack_10 = puStack_10 + 1) {
    *puStack_10 = 0;
  }
  return;
}

/* JP: 0x0043c4e0  CmdPC::IsSetComboKey(SHORTCUTCommand*, char, short)   [IsSetComboKey__5CmdPCFP15SHORTCUTCommandcs]  size=0xd0 */
undefined4
IsSetComboKey__5CmdPCFP15SHORTCUTCommandcs
          (undefined8 param_1,char *param_2,char param_3,short param_4)

{
  char *pcStack_30;
  
  pcStack_30 = param_2;
  while( true ) {
    if (param_2 + 0x10 <= pcStack_30) {
      return 0;
    }
    if ((*pcStack_30 == param_3) && ((param_4 < 0 || (*(short *)(pcStack_30 + 2) == param_4))))
    break;
    pcStack_30 = pcStack_30 + 4;
  }
  return 1;
}

/* JP: 0x0043c5b0  CmdPC::IsSetComboKey(CmdParty*, char, short)   [IsSetComboKey__5CmdPCFP8CmdPartycs]  size=0x1a0 */
undefined4
IsSetComboKey__5CmdPCFP8CmdPartycs(int *param_1,int param_2,undefined1 param_3,undefined2 param_4)

{
  byte bVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  short sVar5;
  undefined4 uVar6;
  long lVar7;
  
  iVar3 = param_1[1];
  bVar1 = *(byte *)(iVar3 + 0x33);
  iVar4 = param_1[0xb];
  sVar5 = *(short *)(iVar3 + 0x34);
  sVar2 = *(short *)(iVar3 + 0x36);
  lVar7 = IsSetComboKey__5CmdPCFP15SHORTCUTCommandcs
                    (param_1,*(int *)(param_2 + 4) + (short)(ushort)*(byte *)(*param_1 + 2) * 0x10 +
                             0xf44,param_3,param_4);
  if (lVar7 == 0) {
    for (; sVar5 < sVar2; sVar5 = sVar5 + 1) {
      if (((iVar4 << (bVar1 & 0x1f) & 1 << ((int)sVar5 & 0x1fU)) != 0) &&
         (lVar7 = IsSetComboKey__5CmdPCFP15SHORTCUTCommandcs
                            (param_1,*(int *)(param_2 + 4) + sVar5 * 0x10 + 0xf44,param_3,param_4),
         lVar7 != 0)) {
        return 1;
      }
    }
    uVar6 = 0;
  }
  else {
    uVar6 = 1;
  }
  return uVar6;
}

/* JP: 0x0043c750  CmdPC::ResetComboKey(SHORTCUTCommand*, char, short)   [ResetComboKey__5CmdPCFP15SHORTCUTCommandcs]  size=0xe0 */
void ResetComboKey__5CmdPCFP15SHORTCUTCommandcs
               (undefined8 param_1,char *param_2,char param_3,short param_4)

{
  char *pcStack_30;
  
  for (pcStack_30 = param_2; pcStack_30 < param_2 + 0x10; pcStack_30 = pcStack_30 + 4) {
    if ((*pcStack_30 == param_3) && ((param_4 < 0 || (*(short *)(pcStack_30 + 2) == param_4)))) {
      *pcStack_30 = -1;
      pcStack_30[1] = -1;
      pcStack_30[2] = -1;
      pcStack_30[3] = -1;
    }
  }
  return;
}

/* JP: 0x0043c830  CmdPC::ResetComboKey(CmdParty*, char, short)   [ResetComboKey__5CmdPCFP8CmdPartycs]  size=0x17c */
void ResetComboKey__5CmdPCFP8CmdPartycs
               (int *param_1,int param_2,undefined1 param_3,undefined2 param_4)

{
  byte bVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  short sVar5;
  
  iVar3 = param_1[1];
  bVar1 = *(byte *)(iVar3 + 0x33);
  iVar4 = param_1[0xb];
  sVar5 = *(short *)(iVar3 + 0x34);
  sVar2 = *(short *)(iVar3 + 0x36);
  ResetComboKey__5CmdPCFP15SHORTCUTCommandcs
            (param_1,*(int *)(param_2 + 4) + (short)(ushort)*(byte *)(*param_1 + 2) * 0x10 + 0xf44,
             param_3,param_4);
  for (; sVar5 < sVar2; sVar5 = sVar5 + 1) {
    if ((iVar4 << (bVar1 & 0x1f) & 1 << ((int)sVar5 & 0x1fU)) != 0) {
      ResetComboKey__5CmdPCFP15SHORTCUTCommandcs
                (param_1,*(int *)(param_2 + 4) + sVar5 * 0x10 + 0xf44,param_3,param_4);
    }
  }
  return;
}

/* JP: 0x0043c9b0  CmdPC::UpdateComboKeyMagic(CmdParty*, short, char*)   [UpdateComboKeyMagic__5CmdPCFP8CmdPartysPc]  size=0x118 */
void UpdateComboKeyMagic__5CmdPCFP8CmdPartysPc
               (int *param_1,int param_2,undefined2 param_3,int param_4)

{
  int iVar1;
  char *pcVar2;
  
  CreateMagic__5CmdPCFP8CmdPartysPc(param_1,param_2,param_3,param_4);
  iVar1 = *(int *)(param_2 + 4) + (short)(ushort)*(byte *)(*param_1 + 2) * 0x10;
  for (pcVar2 = (char *)(iVar1 + 0xf44); pcVar2 < (char *)(iVar1 + 0xf54); pcVar2 = pcVar2 + 4) {
    if ((*pcVar2 == '\x02') && (*(char *)(param_4 + *(short *)(pcVar2 + 2)) == '\0')) {
      *pcVar2 = -1;
      pcVar2[1] = -1;
      pcVar2[2] = -1;
      pcVar2[3] = -1;
    }
  }
  return;
}
