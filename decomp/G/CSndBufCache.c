/* SECTION G  main-executable side: CSndBufCache (map/sound preload cache)
 * JP SLPM_602.19 (Furokuban). Ghidra decompile with symbols/gp globals resolved. */

/* JP: 0x003c1570  CSndBufCache::Clear()   [Clear__12CSndBufCacheFv]  size=0xb8 */
void Clear__12CSndBufCacheFv(void)

{
  undefined1 *puVar1;
  int iVar2;
  
  ResetSoundBuffer__4SdrvFi(sys__4Sdrv,0);
  puVar1 = &m_info__12CSndBufCache;
  for (iVar2 = 0; iVar2 < 8; iVar2 = iVar2 + 1) {
    if ((puVar1[1] == '\x02') || (puVar1[1] == '\x03')) {
      puVar1[1] = 0;
    }
    if (puVar1[1] == '\x01') {
      puVar1[1] = 4;
    }
    puVar1 = puVar1 + 0x40;
  }
  m_tmpData = 0;
  return;
}

/* JP: 0x003c1630  CSndBufCache::ReadFileCB(int, BufMemory*, int, char*, void*)   [ReadFileCB__12CSndBufCacheFiP9BufMemoryiPcPv]  size=0x128 */
undefined8
ReadFileCB__12CSndBufCacheFiP9BufMemoryiPcPv
          (int param_1,int param_2,int param_3,undefined4 param_4,code *param_5)

{
  int iVar1;
  int iVar2;
  
  m_orderCt__12CSndBufCache = m_orderCt__12CSndBufCache + -1;
  iVar1 = *(int *)(param_2 + 4);
  iVar2 = param_1 * 0x40;
  if (((&m_info__12CSndBufCache+0x1)[iVar2] == '\x04') || (m_tmpData == 0)) {
    (&m_info__12CSndBufCache+0x1)[iVar2] = 0;
    NextLoad__12CSndBufCacheFv();
  }
  else {
    *(int *)(&m_info__12CSndBufCache+0x8 + iVar2) = param_3;
    (&m_info__12CSndBufCache+0x1)[iVar2] = 2;
    ResizeSoundMemory__4SdrvFPvUi(sys__4Sdrv,m_tmpData,param_3 + (iVar1 - m_tmpData));
    m_tmpData = 0;
    if (param_5 != (code *)0x0) {
      (*param_5)(param_1,param_2,param_3,param_4,*(undefined4 *)(&m_info__12CSndBufCache+0xc + iVar2));
    }
    (&m_info__12CSndBufCache+0x4)[param_1 * 0x10] = iVar1;
    NextLoad__12CSndBufCacheFv();
  }
  return 0;
}

/* JP: 0x003c1760  CSndBufCache::NextLoad()   [NextLoad__12CSndBufCacheFv]  size=0x12c */
undefined4 NextLoad__12CSndBufCacheFv(void)

{
  char *__src;
  long lVar1;
  uint uVar2;
  undefined1 *puVar3;
  int iVar4;
  
  puVar3 = &m_info__12CSndBufCache;
  iVar4 = 0;
  while( true ) {
    if (7 < iVar4) {
      return 0;
    }
    if ((puVar3[1] == '\x03') && (lVar1 = GetSoundMemory__4SdrvFiUi(sys__4Sdrv,0,0), lVar1 != 0))
    break;
    iVar4 = iVar4 + 1;
    puVar3 = puVar3 + 0x40;
  }
  m_tmpData = (int)lVar1;
  uVar2 = m_tmpData + 0x3f;
  puVar3[1] = 1;
  SetBuffer__9BufMemoryFUlPUc(0x42be20,0,uVar2 & 0xffffffc0);
  ReadOrder__11DvdromOrderFPCcPFiP9BufMemoryiPcPv_iiP9BufMemoryPvi
            (Dvdromour__11DvdromOrder,puVar3 + 0x10,0x3c1630,iVar4,0x42be20,
             *(undefined4 *)(puVar3 + 4),0);
  __src = (char *)StripFileName__12CSndBufCacheFPCc(puVar3 + 0x10);
  strcpy(puVar3 + 0x10,__src);
  m_orderCt__12CSndBufCache = m_orderCt__12CSndBufCache + 1;
  return 1;
}

/* JP: 0x003c1890  CSndBufCache::Load(const char*, int, int, int(*)(int, BufMemory*, int, char*, void*)*, void*)   [Load__12CSndBufCacheFPCciiPFiP9BufMemoryiPcPv_iPv]  size=0x288 */
undefined4
Load__12CSndBufCacheFPCciiPFiP9BufMemoryiPcPv_iPv
          (char *param_1,uint param_2,uint param_3,undefined4 param_4,undefined4 param_5)

{
  char *__s1;
  int iVar1;
  undefined4 uVar2;
  long lVar3;
  byte *__s;
  int iVar4;
  int iVar5;
  int iVar6;
  
  __s1 = (char *)StripFileName__12CSndBufCacheFPCc(param_1);
  iVar6 = -1;
  __s = &m_info__12CSndBufCache;
  iVar4 = 0;
  iVar5 = iVar6;
  do {
    if (7 < iVar4) {
      if (iVar6 < 0) {
        if (-1 < iVar5) {
          __s = &m_info__12CSndBufCache + iVar5 * 0x40;
          iVar4 = iVar5;
        }
      }
      else {
        __s = &m_info__12CSndBufCache + iVar6 * 0x40;
        iVar4 = iVar6;
      }
      if (iVar4 < 8) {
        memset(__s,0,0x40);
        *__s = (byte)param_2;
        *(undefined4 *)(__s + 4) = param_4;
        *(undefined4 *)(__s + 0xc) = param_5;
        if (m_tmpData == 0) {
          lVar3 = GetSoundMemory__4SdrvFiUi(sys__4Sdrv,0,0);
          if (lVar3 == 0) {
            uVar2 = 0xffffffff;
          }
          else {
            m_tmpData = (int)lVar3;
            SetBuffer__9BufMemoryFUlPUc(0x42be20,0,m_tmpData + 0x3fU & 0xffffffc0);
            strcpy((char *)(__s + 0x10),__s1);
            ReadOrder__11DvdromOrderFPCcPFiP9BufMemoryiPcPv_iiP9BufMemoryPvi
                      (Dvdromour__11DvdromOrder,param_1,0x3c1630,iVar4,0x42be20,param_4,0);
            m_orderCt__12CSndBufCache = m_orderCt__12CSndBufCache + 1;
            __s[1] = 1;
            uVar2 = 1;
          }
        }
        else {
          __s[1] = 3;
          strcpy((char *)(__s + 0x10),param_1);
          uVar2 = 2;
        }
      }
      else {
        uVar2 = 0xffffffff;
      }
      return uVar2;
    }
    if (__s[1] == 0) {
      if (iVar5 < 0) {
        iVar5 = iVar4;
      }
    }
    else {
      iVar1 = strcasecmp(__s1,(char *)(__s + 0x10));
      if (iVar1 == 0) {
        return 2;
      }
      if ((((param_3 & 1) != 0) && (iVar6 < 0)) && (param_2 == *__s)) {
        iVar6 = iVar4;
      }
    }
    iVar4 = iVar4 + 1;
    __s = __s + 0x40;
  } while( true );
}

/* JP: 0x003c1b20  CSndBufCache::Find(const char*, int)   [Find__12CSndBufCacheFPCci]  size=0xbc */
byte * Find__12CSndBufCacheFPCci(undefined4 param_1,uint param_2)

{
  char *__s1;
  int iVar1;
  byte *pbVar2;
  int iVar3;
  
  __s1 = (char *)StripFileName__12CSndBufCacheFPCc(param_1);
  pbVar2 = &m_info__12CSndBufCache;
  iVar3 = 0;
  while( true ) {
    if (7 < iVar3) {
      return (byte *)0x0;
    }
    if (((pbVar2[1] != 0) && (param_2 == *pbVar2)) &&
       (iVar1 = strcasecmp(__s1,(char *)(pbVar2 + 0x10)), iVar1 == 0)) break;
    iVar3 = iVar3 + 1;
    pbVar2 = pbVar2 + 0x40;
  }
  return pbVar2;
}

/* JP: 0x003c1be0  CSndBufCache::FindType(int)   [FindType__12CSndBufCacheFi]  size=0x84 */
byte * FindType__12CSndBufCacheFi(uint param_1)

{
  byte *pbVar1;
  int iVar2;
  
  pbVar1 = &m_info__12CSndBufCache;
  iVar2 = 0;
  while( true ) {
    if (7 < iVar2) {
      return (byte *)0x0;
    }
    if ((pbVar1[1] != 0) && (param_1 == *pbVar1)) break;
    iVar2 = iVar2 + 1;
    pbVar1 = pbVar1 + 0x40;
  }
  return pbVar1;
}

/* JP: 0x003c1c70  CSndBufCache::StripFileName(const char*)   [StripFileName__12CSndBufCacheFPCc]  size=0x1c4 */
byte * StripFileName__12CSndBufCacheFPCc(byte *param_1)

{
  size_t sVar1;
  byte *pbVar2;
  byte *pbVar3;
  byte bVar4;
  byte bVar5;
  byte *pbVar6;
  byte *pbStack_10;
  
  pbVar6 = pDataPath__7SysTool;
  do {
    pbVar2 = pbVar6 + 1;
    bVar5 = *pbVar6;
    pbVar3 = param_1;
    pbVar6 = pDataPath__7SysTool;
    if (bVar5 == 0) break;
    pbVar6 = pbVar2;
  } while (bVar5 != 0x3a);
  do {
    pbVar2 = pbVar3 + 1;
    bVar5 = *pbVar3;
    pbStack_10 = param_1;
    if (bVar5 == 0) break;
    pbVar3 = pbVar2;
    pbStack_10 = pbVar2;
  } while (bVar5 != 0x3a);
  sVar1 = strlen((char *)pbVar6);
  pbVar3 = pbStack_10;
  do {
    pbStack_10 = pbVar3;
    if (sVar1 == 0) break;
    bVar5 = *pbVar6;
    bVar4 = *pbStack_10;
    if ((0x60 < bVar5) && (bVar5 < 0x7b)) {
      bVar5 = bVar5 & 0xdf;
    }
    if ((0x60 < bVar4) && (bVar4 < 0x7b)) {
      bVar4 = bVar4 & 0xdf;
    }
    sVar1 = (long)((int)sVar1 + -1);
    pbVar6 = pbVar6 + 1;
    pbVar3 = pbStack_10 + 1;
  } while (bVar5 == bVar4);
  if ((*pbStack_10 == 0x2f) || (*pbStack_10 == 0x5c)) {
    pbStack_10 = pbStack_10 + 1;
  }
  return pbStack_10;
}

/* JP: 0x003c1e40  CSndBufCache::StripFileNameB(const char*)   [StripFileNameB__12CSndBufCacheFPCc]  size=0x8c */
char * StripFileNameB__12CSndBufCacheFPCc(char *param_1)

{
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  
  pcVar2 = param_1;
  while( true ) {
    pcVar3 = pcVar2 + 1;
    cVar1 = *pcVar2;
    if (cVar1 == '\0') break;
    pcVar2 = pcVar3;
    if (((cVar1 == ':') || (cVar1 == '/')) || (cVar1 == '\\')) {
      param_1 = pcVar3;
    }
  }
  return param_1;
}
