/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: _FieldDataCache   functions: 7
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/_FieldDataCache.md).
 */

/* JP: 0x004a4470  _FieldDataCache::GetName(char*)   [GetName__15_FieldDataCacheFPc]  size=0x40 */
void GetName__15_FieldDataCacheFPc(undefined2 *param_1,undefined4 param_2)

{
  DecodeKey__15_FieldDataCacheFPcUiUi(param_2,*param_1,*(undefined4 *)(param_1 + 2));
  return;
}

/* JP: 0x004bf770  _FieldDataCache::Release()   [Release__15_FieldDataCacheFv]  size=0x90 */
undefined4 Release__15_FieldDataCacheFv(int param_1)

{
  short sVar1;
  undefined4 uVar2;
  
  sVar1 = *(short *)(param_1 + 2) + -1;
  *(short *)(param_1 + 2) = sVar1;
  if (sVar1 < 1) {
    if (*(int *)(param_1 + 8) != 0) {
      __dt__9BufMemoryFv(*(undefined4 *)(param_1 + 8),1);
    }
    memset(param_1,0,0xc);
    uVar2 = 1;
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

/* JP: 0x004bf800  _FieldDataCache::FindKey(const char*)   [FindKey__15_FieldDataCacheFPCc]  size=0x120 */
uint FindKey__15_FieldDataCacheFPCc(char *param_1)

{
  int iVar1;
  long lVar2;
  uint uVar3;
  int iVar4;
  char *pcStack_10;
  
  for (uVar3 = 0; uVar3 < 8; uVar3 = uVar3 + 1) {
    lVar2 = strcasecmp(param_1,(&keyTbl)[uVar3]);
    if (lVar2 == 0) {
      return uVar3;
    }
  }
  iVar4 = 0;
  pcStack_10 = param_1;
  for (uVar3 = 0; uVar3 < 3; uVar3 = uVar3 + 1) {
    if (*pcStack_10 == '\0') break;
    iVar1 = EncodeChar__Fi(*pcStack_10);
    if (uVar3 != 0) {
      iVar1 = iVar1 * 0x28;
    }
    iVar4 = iVar4 + iVar1;
    pcStack_10 = pcStack_10 + 1;
  }
  return iVar4 * 0x10 + 0xf;
}

/* JP: 0x004bf9d0  _FieldDataCache::EncodeKey(const char*, unsigned int&)   [EncodeKey__15_FieldDataCacheFPCcRUi]  size=0x170 */
uint EncodeKey__15_FieldDataCacheFPCcRUi(char *param_1,undefined4 *param_2)

{
  char cVar1;
  char *pcVar2;
  byte bVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  byte abStack_30 [12];
  undefined4 uStack_24;
  char *pcStack_20;
  undefined4 *puStack_10;
  
  uVar4 = 0;
  pcStack_20 = param_1;
  puStack_10 = param_2;
  memset(abStack_30,0,8);
  iVar5 = 0;
  do {
    pcVar2 = pcStack_20;
    if (8 < iVar5) {
LAB_004bfa98:
      uStack_24 = 0;
      for (iVar5 = 0; iVar5 < 4; iVar5 = iVar5 + 1) {
        iVar6 = (uint)abStack_30[iVar5 * 2] + (uint)abStack_30[iVar5 * 2 + 1] * 0x28;
        *(char *)((int)&uStack_24 + iVar5) = (char)iVar6;
        uVar4 = uVar4 | (iVar6 >> 8) << (iVar5 * 3 & 0x1fU);
      }
      *puStack_10 = uStack_24;
      return uVar4;
    }
    pcStack_20 = pcStack_20 + 1;
    cVar1 = *pcVar2;
    if (cVar1 == '\0') goto LAB_004bfa98;
    if (cVar1 == '.') {
      iVar5 = FindKey__15_FieldDataCacheFPCc(pcStack_20);
      uVar4 = iVar5 << 0xc;
      goto LAB_004bfa98;
    }
    if (7 < iVar5) goto LAB_004bfa98;
    bVar3 = EncodeChar__Fi(cVar1);
    abStack_30[iVar5] = bVar3;
    iVar5 = iVar5 + 1;
  } while( true );
}

/* JP: 0x004bfb40  _FieldDataCache::DecodeKey(char*, unsigned int, unsigned int)   [DecodeKey__15_FieldDataCacheFPcUiUi]  size=0x26c */
void DecodeKey__15_FieldDataCacheFPcUiUi(char *param_1,uint param_2,undefined4 param_3)

{
  uint uVar1;
  int iVar2;
  char *pcVar3;
  byte abStack_40 [12];
  undefined4 uStack_34;
  char *pcStack_30;
  uint uStack_20;
  undefined4 uStack_10;
  
  pcStack_30 = param_1;
  uStack_20 = param_2;
  uStack_10 = param_3;
  uStack_34 = param_3;
  for (iVar2 = 0; iVar2 < 4; iVar2 = iVar2 + 1) {
    uVar1 = (uint)*(byte *)((int)&uStack_34 + iVar2) +
            (uStack_20 >> (iVar2 * 3 & 0x1fU) & 7) * 0x100;
    abStack_40[iVar2 * 2] = (byte)(uVar1 % 0x28);
    abStack_40[iVar2 * 2 + 1] = (byte)(uVar1 / 0x28);
  }
  pcVar3 = pcStack_30;
  for (iVar2 = 0; (iVar2 < 8 && (abStack_40[iVar2] != 0)); iVar2 = iVar2 + 1) {
    *pcVar3 = n38tbl[abStack_40[iVar2]];
    pcVar3 = pcVar3 + 1;
  }
  *pcVar3 = '\0';
  uVar1 = uStack_20 >> 0xc;
  if ((uVar1 & 0xf) == 0xf) {
    uStack_20 = uStack_20 >> 0x10;
    if (uStack_20 != 0) {
      *pcVar3 = '.';
      for (iVar2 = 0; pcVar3 = pcVar3 + 1, iVar2 < 3; iVar2 = iVar2 + 1) {
        uVar1 = uStack_20 % 0x28;
        uStack_20 = uStack_20 / 0x28;
        if (uVar1 == 0) break;
        *pcVar3 = n38tbl[uVar1];
      }
      *pcVar3 = '\0';
    }
  }
  else {
    *pcVar3 = '.';
    uStack_20 = uVar1;
    strcpy(pcVar3 + 1,(&keyTbl)[uVar1]);
  }
  return;
}

/* JP: 0x004bfdb0  _FieldDataCache::Find(int, const char*)   [Find__15_FieldDataCacheFiPCc]  size=0xc0 */
short * Find__15_FieldDataCacheFiPCc(short *param_1,int param_2,undefined4 param_3)

{
  short sVar1;
  int iVar2;
  int iStack_34;
  short *psStack_30;
  int iStack_20;
  undefined4 uStack_10;
  
  psStack_30 = param_1;
  iStack_20 = param_2;
  uStack_10 = param_3;
  sVar1 = EncodeKey__15_FieldDataCacheFPCcRUi(param_3,&iStack_34);
  iVar2 = 0;
  while( true ) {
    if (iStack_20 <= iVar2) {
      return (short *)0x0;
    }
    if ((*param_1 == sVar1) && (*(int *)(param_1 + 2) == iStack_34)) break;
    iVar2 = iVar2 + 1;
    param_1 = param_1 + 6;
  }
  return param_1;
}

/* JP: 0x004bfe70  _FieldDataCache::GetNewData(int, const char*)   [GetNewData__15_FieldDataCacheFiPCc]  size=0xe0 */
undefined2 * GetNewData__15_FieldDataCacheFiPCc(undefined2 *param_1,int param_2,undefined4 param_3)

{
  undefined2 uVar1;
  int iVar2;
  undefined4 uStack_34;
  undefined2 *puStack_30;
  int iStack_20;
  undefined4 uStack_10;
  
  puStack_30 = param_1;
  iStack_20 = param_2;
  uStack_10 = param_3;
  uVar1 = EncodeKey__15_FieldDataCacheFPCcRUi(param_3,&uStack_34);
  iVar2 = 0;
  while( true ) {
    if (iStack_20 <= iVar2) {
      return (undefined2 *)0x0;
    }
    if (param_1[1] == 0) break;
    iVar2 = iVar2 + 1;
    param_1 = param_1 + 6;
  }
  memset(param_1,0,0xc);
  *param_1 = uVar1;
  *(undefined4 *)(param_1 + 2) = uStack_34;
  param_1[1] = 1;
  return param_1;
}
