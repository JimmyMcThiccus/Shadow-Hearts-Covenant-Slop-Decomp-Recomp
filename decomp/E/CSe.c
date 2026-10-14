/*
 * CSe.c -- Ghidra decompiler output (SLPM_602.19, JP Furokuban), tidied by tools/E_gen_decomp.py
 * 25 functions. Types: u8/u16/u32/u64 = undefined1/2/4/8. Addresses in comments are JP main-exe addresses.
 */

/* ---- 0x003c3bd0 size 0x30  CSe::CSe(v)
 *      mangled: __ct__3CSeFv */
u32 * __ct__3CSeFv(u32 *param_1)

{
  param_1[1] = __vt__3CSe;
  *param_1 = 0;
  return param_1;
}

/* ---- 0x003c3c00 size 0x8c  CSe::~CSe(v)
 *      mangled: __dt__3CSeFv */
int * __dt__3CSeFv(int *param_1,short param_2)

{
  if (param_1 != (int *)0x0) {
    param_1[1] = (int)__vt__3CSe;
    if (*param_1 != 0) {
      ResetAll__3CSeFv(param_1);
      __dla__FPv(*param_1);
    }
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* ---- 0x003c3c90 size 0x128  CSe::Create(UiUiUi)
 *      mangled: Create__3CSeFUiUiUi */
void Create__3CSeFUiUiUi(int *param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  uint uVar2;
  
  if (*param_1 == 0) {
    uVar2 = param_2 * 0xc + param_3 * (param_4 + 0x20) + 0x117;
    iVar1 = __nwa__FUi(uVar2 & 0xfffffffc);
    *param_1 = iVar1;
    memset((void *)*param_1,0,(long)(int)(uVar2 & 0xfffffffc));
    param_1 = (int *)*param_1;
    *param_1 = (int)(param_1 + 5);
    param_1[1] = *param_1 + param_2 * 0xc;
    param_1[2] = param_1[1] + (param_4 + 0x20) * param_3;
    *(short *)(param_1 + 3) = (short)param_2;
    *(short *)((int)param_1 + 0xe) = (short)param_3;
    *(short *)(param_1 + 4) = (short)param_4 + 0x20;
  }
  return;
}

/* ---- 0x003c3dc0 size 0x10c  CSe::Release(v)
 *      mangled: Release__3CSeFv */
u32 Release__3CSeFv(int *param_1)

{
  int iVar1;
  u32 uVar2;
  byte bVar3;
  
  if (*param_1 == 0) {
    return 1;
  }
  iVar1 = *param_1;
  bVar3 = *(byte *)(iVar1 + 0x12) & 3;
  if (bVar3 == 2) {
LAB_003c3e88:
    __dla__FPv(*param_1);
    *param_1 = 0;
    uVar2 = 1;
  }
  else {
    if (bVar3 == 1) {
LAB_003c3e60:
      (**(code **)(param_1[1] + 0x14))();
      if ((*(byte *)(iVar1 + 0x12) & 3) != 1) goto LAB_003c3e88;
    }
    else if ((*(byte *)(iVar1 + 0x12) & 3) == 0) {
      *(byte *)(iVar1 + 0x12) = *(byte *)(iVar1 + 0x12) & 0xfc | 1;
      SeReleaseAll__3CSeFv(param_1);
      RemoveAllSDH__3CSeFv(param_1);
      goto LAB_003c3e60;
    }
    uVar2 = 0;
  }
  return uVar2;
}

/* ---- 0x003c3ed0 size 0x114  CSe::LoadSDH(Pv)
 *      mangled: LoadSDH__3CSeFPv */
int LoadSDH__3CSeFPv(int *param_1,int param_2)

{
  u32 *puVar1;
  long lVar2;
  int *piVar3;
  int iVar4;
  
  if (*param_1 == 0) {
    iVar4 = -1;
  }
  else {
    puVar1 = (u32 *)*param_1;
    if (((*(byte *)((int)puVar1 + 0x12) & 3) == 0) &&
       (-1 < (long)((ulong)*(byte *)((int)puVar1 + 0x12) << 0x3c))) {
      piVar3 = (int *)*puVar1;
      for (iVar4 = 0; iVar4 < (int)(uint)*(ushort *)(puVar1 + 3); iVar4 = iVar4 + 1) {
        if ((*piVar3 == 0) && (lVar2 = SetBatchQ__3CSeFiUiUi(param_1,1,iVar4,param_2), lVar2 != 0))
        {
          *piVar3 = param_2;
          piVar3[2] = *(int *)(param_2 + 0xc);
          return iVar4;
        }
        piVar3 = piVar3 + 3;
      }
      iVar4 = -2;
    }
    else {
      iVar4 = -2;
    }
  }
  return iVar4;
}

/* ---- 0x003c3ff0 size 0x50  CSe::RemoveAllSDH(v)
 *      mangled: RemoveAllSDH__3CSeFv */
void RemoveAllSDH__3CSeFv(int *param_1)

{
  int iVar1;
  
  iVar1 = *param_1;
  if (iVar1 != 0) {
    *(byte *)(iVar1 + 0x12) = *(byte *)(iVar1 + 0x12) & 0xf7 | 8;
  }
  return;
}

/* ---- 0x003c4040 size 0xdc  CSe::RemoveSDH(Ui)
 *      mangled: RemoveSDH__3CSeFUi */
u32 RemoveSDH__3CSeFUi(int *param_1,int param_2)

{
  u32 *puVar1;
  long lVar2;
  int *piVar3;
  int iVar4;
  
  if (*param_1 != 0) {
    puVar1 = (u32 *)*param_1;
    piVar3 = (int *)*puVar1;
    for (iVar4 = 0; iVar4 < (int)(uint)*(ushort *)(puVar1 + 3); iVar4 = iVar4 + 1) {
      if (((*piVar3 != 0) && (piVar3[1] == param_2)) &&
         (lVar2 = SetBatchQ__3CSeFiUiUi(param_1,3,iVar4,param_2), lVar2 != 0)) {
        *piVar3 = 0;
        piVar3[1] = 0;
        return 1;
      }
      piVar3 = piVar3 + 3;
    }
  }
  return 0;
}

/* ---- 0x003c4120 size 0xd4  CSe::MarkSDH(Uii)
 *      mangled: MarkSDH__3CSeFUii */
void MarkSDH__3CSeFUii(int *param_1,uint param_2,int param_3)

{
  u32 *puVar1;
  uint *puVar2;
  uint uVar3;
  int iVar4;
  
  if (*param_1 != 0) {
    puVar1 = (u32 *)*param_1;
    puVar2 = (uint *)*puVar1;
    for (iVar4 = 0; iVar4 < (int)(uint)*(ushort *)(puVar1 + 3); iVar4 = iVar4 + 1) {
      if ((*puVar2 != 0) && (puVar2[1] == param_2)) {
        if (param_3 == 0) {
          uVar3 = *puVar2 & 0x7fffffff;
        }
        else {
          uVar3 = *puVar2 | 0x80000000;
        }
        *puVar2 = uVar3;
      }
      puVar2 = puVar2 + 3;
    }
  }
  return;
}

/* ---- 0x003c4200 size 0xb0  CSe::FindSDH(Pv)
 *      mangled: FindSDH__3CSeFPv */
int FindSDH__3CSeFPv(int *param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  
  if (*param_1 != 0) {
    piVar1 = *(int **)*param_1;
    for (iVar2 = 0; iVar2 < (int)(uint)*(ushort *)((u32 *)*param_1 + 3); iVar2 = iVar2 + 1) {
      if ((*piVar1 == param_2) && (piVar1[1] != 0)) {
        return piVar1[1];
      }
      piVar1 = piVar1 + 3;
    }
  }
  return 0;
}

/* ---- 0x003c42b0 size 0xec  CSe::SeFind(Ui)
 *      mangled: SeFind__3CSeFUi */
int SeFind__3CSeFUi(int *param_1,int param_2)

{
  int iVar1;
  byte *pbVar2;
  int iVar3;
  
  if (*param_1 == 0) {
    iVar1 = -1;
  }
  else {
    iVar1 = *param_1;
    if ((*(byte *)(iVar1 + 0x12) & 3) == 0) {
      pbVar2 = *(byte **)(iVar1 + 4);
      for (iVar3 = 0; iVar3 < (int)(uint)*(ushort *)(iVar1 + 0xe); iVar3 = iVar3 + 1) {
        if (((*pbVar2 & 0x8f) == 0x82) && (*(int *)(pbVar2 + 4) == param_2)) {
          return iVar3;
        }
        pbVar2 = pbVar2 + *(ushort *)(iVar1 + 0x10);
      }
      iVar1 = -2;
    }
    else {
      iVar1 = -1;
    }
  }
  return iVar1;
}

/* ---- 0x003c43a0 size 0xe0  CSe::SeFind2(Ui)
 *      mangled: SeFind2__3CSeFUi */
int SeFind2__3CSeFUi(int *param_1,int param_2)

{
  int iVar1;
  byte *pbVar2;
  int iVar3;
  
  if (*param_1 == 0) {
    iVar1 = -1;
  }
  else {
    iVar1 = *param_1;
    if ((*(byte *)(iVar1 + 0x12) & 3) == 0) {
      pbVar2 = *(byte **)(iVar1 + 4);
      for (iVar3 = 0; iVar3 < (int)(uint)*(ushort *)(iVar1 + 0xe); iVar3 = iVar3 + 1) {
        if (((*pbVar2 & 0x80) != 0) && (*(int *)(pbVar2 + 4) == param_2)) {
          return iVar3;
        }
        pbVar2 = pbVar2 + *(ushort *)(iVar1 + 0x10);
      }
      iVar1 = -2;
    }
    else {
      iVar1 = -1;
    }
  }
  return iVar1;
}

/* ---- 0x003c4480 size 0x15c  CSe::SePlay(UiP8_SeParam)
 *      mangled: SePlay__3CSeFUiP8_SeParam */
int SePlay__3CSeFUiP8_SeParam(int *param_1,u32 param_2,void *param_3)

{
  int iVar1;
  byte *__s;
  int iVar2;
  
  if (*param_1 == 0) {
    iVar1 = -1;
  }
  else {
    iVar1 = *param_1;
    if ((*(byte *)(iVar1 + 0x12) & 3) == 0) {
      __s = *(byte **)(iVar1 + 4);
      for (iVar2 = 0; iVar2 < (int)(uint)*(ushort *)(iVar1 + 0xe); iVar2 = iVar2 + 1) {
        if ((*__s & 0x80) == 0) {
          memset(__s,0,(ulong)*(ushort *)(iVar1 + 0x10));
          *__s = 0xc0;
          __s[1] = __s[1] | 1;
          *(u32 *)(__s + 4) = param_2;
          InitSeParam__4SdrvFP8_SeParamiPv(sys__4Sdrv,__s + 0x14,9,__s);
          if (param_3 != (void *)0x0) {
            memcpy(__s + 0x14,param_3,6);
          }
          HandleSE__3CSeFP7_SeWork(param_1,__s);
          return iVar2;
        }
        __s = __s + *(ushort *)(iVar1 + 0x10);
      }
      iVar1 = -2;
    }
    else {
      iVar1 = -1;
    }
  }
  return iVar1;
}

/* ---- 0x003c45e0 size 0x134  CSe::SePlayN(UiP8_SeParam)
 *      mangled: SePlayN__3CSeFUiP8_SeParam */
void SePlayN__3CSeFUiP8_SeParam(int *param_1,u32 param_2,void *param_3)

{
  int iVar1;
  byte *__s;
  int iVar2;
  
  if ((*param_1 != 0) && (iVar1 = *param_1, (*(byte *)(iVar1 + 0x12) & 3) == 0)) {
    __s = *(byte **)(iVar1 + 4);
    for (iVar2 = 0; iVar2 < (int)(uint)*(ushort *)(iVar1 + 0xe); iVar2 = iVar2 + 1) {
      if ((*__s & 0x80) == 0) {
        memset(__s,0,(ulong)*(ushort *)(iVar1 + 0x10));
        *__s = 0x80;
        __s[1] = __s[1] | 3;
        *(u32 *)(__s + 4) = param_2;
        InitSeParam__4SdrvFP8_SeParamiPv(sys__4Sdrv,__s + 0x14,8,0);
        if (param_3 != (void *)0x0) {
          memcpy(__s + 0x14,param_3,6);
        }
        HandleSE__3CSeFP7_SeWork(param_1,__s);
        return;
      }
      __s = __s + *(ushort *)(iVar1 + 0x10);
    }
  }
  return;
}

/* ---- 0x003c4720 size 0x88  CSe::SeGetWork(i)
 *      mangled: SeGetWork__3CSeFi */
int SeGetWork__3CSeFi(int *param_1,int param_2)

{
  int iVar1;
  
  if (*param_1 == 0) {
    iVar1 = 0;
  }
  else if ((*(byte *)(*param_1 + 0x12) & 3) == 0) {
    iVar1 = *(int *)(*param_1 + 4) + (uint)*(ushort *)(*param_1 + 0x10) * param_2;
  }
  else {
    iVar1 = 0;
  }
  return iVar1;
}

/* ---- 0x003c47b0 size 0x64  CSe::SeUpdate(i)
 *      mangled: SeUpdate__3CSeFi */
void SeUpdate__3CSeFi(u32 param_1,u32 param_2)

{
  long lVar1;
  
  lVar1 = SeGetWork__3CSeFi(param_1,param_2);
  if (lVar1 != 0) {
    *(byte *)((int)lVar1 + 1) = *(byte *)((int)lVar1 + 1) | 0x10;
    HandleSE__3CSeFP7_SeWork(param_1,lVar1);
  }
  return;
}

/* ---- 0x003c4820 size 0x84  CSe::SeFade(iii)
 *      mangled: SeFade__3CSeFiii */
void SeFade__3CSeFiii(u32 param_1,u32 param_2,u16 param_3,u16 param_4)

{
  long lVar1;
  int iVar2;
  
  lVar1 = SeGetWork__3CSeFi(param_1,param_2);
  if (lVar1 != 0) {
    iVar2 = (int)lVar1;
    *(u16 *)(iVar2 + 0x10) = param_3;
    *(u16 *)(iVar2 + 0x12) = param_4;
    *(byte *)(iVar2 + 1) = *(byte *)(iVar2 + 1) | 0x20;
    HandleSE__3CSeFP7_SeWork(param_1,lVar1);
  }
  return;
}

/* ---- 0x003c48b0 size 0xa8  CSe::isPlaying(i)
 *      mangled: isPlaying__3CSeFi */
u32 isPlaying__3CSeFi(u32 param_1,u32 param_2)

{
  byte *pbVar1;
  u32 uVar2;
  
  pbVar1 = (byte *)SeGetWork__3CSeFi(param_1,param_2);
  if ((*pbVar1 & 0x8f) == 0x82) {
    uVar2 = 1;
  }
  else if ((*pbVar1 & 0x20) == 0) {
    if ((*pbVar1 & 0x8f) == 0x83) {
      uVar2 = 0;
    }
    else {
      uVar2 = 0xffffffff;
    }
  }
  else {
    uVar2 = 0xfffffffe;
  }
  return uVar2;
}

/* ---- 0x003c4960 size 0x64  CSe::SeRelease(i)
 *      mangled: SeRelease__3CSeFi */
void SeRelease__3CSeFi(u32 param_1,u32 param_2)

{
  long lVar1;
  
  lVar1 = SeGetWork__3CSeFi(param_1,param_2);
  if (lVar1 != 0) {
    *(byte *)((int)lVar1 + 1) = *(byte *)((int)lVar1 + 1) | 0x40;
    HandleSE__3CSeFP7_SeWork(param_1,lVar1);
  }
  return;
}

/* ---- 0x003c49d0 size 0x50  CSe::SeReleaseAll(v)
 *      mangled: SeReleaseAll__3CSeFv */
void SeReleaseAll__3CSeFv(int *param_1)

{
  int iVar1;
  
  iVar1 = *param_1;
  if (iVar1 != 0) {
    *(byte *)(iVar1 + 0x12) = *(byte *)(iVar1 + 0x12) & 0xfb | 4;
  }
  return;
}

/* ---- 0x003c4a20 size 0x25c  CSe::ResetAll(v)
 *      mangled: ResetAll__3CSeFv */
uint ResetAll__3CSeFv(u32 *param_1)

{
  u32 *puVar1;
  long lVar2;
  byte *pbVar3;
  int *piVar4;
  uint uVar5;
  char *pcVar6;
  int iVar7;
  
  puVar1 = (u32 *)*param_1;
  uVar5 = 0;
  if ((long)((ulong)*(byte *)((int)puVar1 + 0x12) << 0x3d) < 0) {
    pbVar3 = (byte *)puVar1[1];
    for (iVar7 = 0; iVar7 < (int)(uint)*(ushort *)((int)puVar1 + 0xe); iVar7 = iVar7 + 1) {
      if ((*pbVar3 & 0xbf) == 0x83) {
        *pbVar3 = 0;
      }
      else if ((*pbVar3 & 0x80) != 0) {
        pbVar3[1] = pbVar3[1] | 0x40;
        HandleSE__3CSeFP7_SeWork(param_1,pbVar3);
        if ((*pbVar3 & 0x80) != 0) {
          uVar5 = 2;
        }
      }
      pbVar3 = pbVar3 + *(ushort *)(puVar1 + 4);
    }
    if (uVar5 == 0) {
      *(byte *)((int)puVar1 + 0x12) = *(byte *)((int)puVar1 + 0x12) & 0xfb;
    }
  }
  if ((long)((ulong)*(byte *)((int)puVar1 + 0x12) << 0x3c) < 0) {
    piVar4 = (int *)*puVar1;
    for (iVar7 = 0; iVar7 < (int)(uint)*(ushort *)(puVar1 + 3); iVar7 = iVar7 + 1) {
      if ((*piVar4 != 0) && (piVar4[1] != 0)) {
        lVar2 = SetBatchQ__3CSeFiUiUi(param_1,3,iVar7,piVar4[1]);
        if (lVar2 == 0) {
          uVar5 = uVar5 | 1;
        }
        else {
          *piVar4 = 0;
          piVar4[1] = 0;
        }
      }
      piVar4 = piVar4 + 3;
    }
    if ((uVar5 & 1) == 0) {
      *(byte *)((int)puVar1 + 0x12) = *(byte *)((int)puVar1 + 0x12) & 0xf7;
      pcVar6 = (char *)puVar1[2];
      for (iVar7 = 0; iVar7 < 0x10; iVar7 = iVar7 + 1) {
        if (*pcVar6 == '\x01') {
          *pcVar6 = '\x02';
        }
        pcVar6 = pcVar6 + 0x10;
      }
    }
  }
  return uVar5;
}

/* ---- 0x003c4c80 size 0x1d0  CSe::Polling(v)
 *      mangled: Polling__3CSeFv */
void Polling__3CSeFv(int *param_1)

{
  int iVar1;
  long lVar2;
  byte *pbVar3;
  char *pcVar4;
  int iVar5;
  
  iVar1 = *param_1;
  if ((iVar1 != 0) && ((*(byte *)(iVar1 + 0x12) & 3) != 2)) {
    lVar2 = ResetAll__3CSeFv(param_1);
    pcVar4 = *(char **)(iVar1 + 8);
    for (iVar5 = 0; iVar5 < 0x10; iVar5 = iVar5 + 1) {
      if ((*pcVar4 != '\0') && (HandleBatchQ__3CSeFP7_BatchQ(param_1,pcVar4), *pcVar4 != '\0')) {
        lVar2 = 1;
      }
      pcVar4 = pcVar4 + 0x10;
    }
    pbVar3 = *(byte **)(iVar1 + 4);
    for (iVar5 = 0; iVar5 < (int)(uint)*(ushort *)(iVar1 + 0xe); iVar5 = iVar5 + 1) {
      if (*pbVar3 == 0x83) {
        *pbVar3 = 0;
      }
      else if ((((*pbVar3 != 0xc3) && ((*pbVar3 & 0x80) != 0)) && (pbVar3[1] != 0)) &&
              (HandleSE__3CSeFP7_SeWork(param_1,pbVar3), (*pbVar3 & 0x80) != 0)) {
        lVar2 = 1;
      }
      pbVar3 = pbVar3 + *(ushort *)(iVar1 + 0x10);
    }
    if (((*(byte *)(iVar1 + 0x12) & 3) == 1) && (lVar2 == 0)) {
      *(byte *)(iVar1 + 0x12) = *(byte *)(iVar1 + 0x12) & 0xfc | 2;
    }
  }
  return;
}

/* ---- 0x003c4e50 size 0xc4  CSe::SetBatchQ(iUiUi)
 *      mangled: SetBatchQ__3CSeFiUiUi */
u32 SetBatchQ__3CSeFiUiUi(int *param_1,char param_2,u16 param_3,u32 param_4)

{
  char *pcVar1;
  int iVar2;
  
  pcVar1 = *(char **)(*param_1 + 8);
  iVar2 = 0;
  while( true ) {
    if (0xf < iVar2) {
      return 0;
    }
    if (*pcVar1 == '\0') break;
    iVar2 = iVar2 + 1;
    pcVar1 = pcVar1 + 0x10;
  }
  *pcVar1 = param_2;
  pcVar1[1] = '\0';
  *(u16 *)(pcVar1 + 8) = param_3;
  *(u32 *)(pcVar1 + 0xc) = param_4;
  HandleBatchQ__3CSeFP7_BatchQ(param_1,pcVar1);
  return 1;
}

/* ---- 0x003c4f20 size 0x258  CSe::HandleBatchQ(P7_BatchQ)
 *      mangled: HandleBatchQ__3CSeFP7_BatchQ */
void HandleBatchQ__3CSeFP7_BatchQ(int *param_1,char *param_2)

{
  char cVar1;
  u32 uVar2;
  int *piVar3;
  u32 uVar4;
  long lVar5;
  int iVar6;
  
  while( true ) {
    cVar1 = *param_2;
    if (cVar1 == '\x03') {
      lVar5 = CheckSeReq__3CSeFv(param_1);
      if ((lVar5 == 0) &&
         (lVar5 = ReleaseSDH__4SdrvFUi(sys__4Sdrv,*(u32 *)(param_2 + 0xc)), lVar5 != -1)) {
        *param_2 = '\0';
      }
      return;
    }
    if ((cVar1 != '\x02') && (cVar1 != '\x01')) {
      return;
    }
    if (param_2[1] != '\x01') break;
    uVar2 = *(u32 *)(param_2 + 4);
    lVar5 = GetStatus__4SdrvFUi(sys__4Sdrv,uVar2);
    if (lVar5 == -2) {
      *param_2 = '\0';
      CloseHandle__4SdrvFUi(sys__4Sdrv,uVar2);
      return;
    }
    if (lVar5 != 3) {
      return;
    }
    piVar3 = (int *)*param_1;
    iVar6 = *piVar3 + (uint)*(ushort *)(param_2 + 8) * 0xc;
    uVar4 = GetOption__4SdrvFUi(sys__4Sdrv,uVar2);
    *(u32 *)(iVar6 + 4) = uVar4;
    CloseHandle__4SdrvFUi(sys__4Sdrv,uVar2);
    if (((*(byte *)((int)piVar3 + 0x12) & 3) == 0) && (*param_2 != '\x02')) {
      *param_2 = '\0';
      return;
    }
    *param_2 = '\x03';
    *(u32 *)(param_2 + 0xc) = *(u32 *)(iVar6 + 4);
  }
  if (param_2[1] != '\0') {
    return;
  }
  if ((*(byte *)(*param_1 + 0x12) & 3) != 0) {
    *param_2 = '\0';
    return;
  }
  lVar5 = AutoLoad__4SdrvFPvPv(sys__4Sdrv,*(u32 *)(param_2 + 0xc),0);
  if (lVar5 == -1) {
    return;
  }
  *(int *)(param_2 + 4) = (int)lVar5;
  param_2[1] = param_2[1] + '\x01';
  return;
}

/* ---- 0x003c5180 size 0x400  CSe::HandleSE(P7_SeWork)
 *      mangled: HandleSE__3CSeFP7_SeWork */
void HandleSE__3CSeFP7_SeWork(u64 param_1,byte *param_2)

{
  u32 uVar1;
  u32 uVar2;
  long lVar3;
  
  if ((param_2[1] & 1) != 0) {
    if (param_2[2] == 1) {
      uVar1 = *(u32 *)(param_2 + 0xc);
      lVar3 = GetStatus__4SdrvFUi(sys__4Sdrv,uVar1);
      if ((lVar3 != -2) && (lVar3 != 3)) {
        return;
      }
      uVar2 = GetOption__4SdrvFUi(sys__4Sdrv,uVar1);
      *(u32 *)(param_2 + 8) = uVar2;
      CloseHandle__4SdrvFUi(sys__4Sdrv,uVar1);
      if ((lVar3 == 3) && (*(int *)(param_2 + 8) == -1)) {
        lVar3 = -2;
      }
      CloseHandle__4SdrvFUi(sys__4Sdrv,uVar1);
      if (lVar3 == -2) {
        if ((param_2[1] & 2) == 0) {
          *param_2 = *param_2 | 0x21;
        }
        else {
          *param_2 = 0;
        }
        param_2[1] = 0;
        return;
      }
      *param_2 = *param_2 | 2;
      param_2[2] = 0;
      if ((param_2[1] & 2) != 0) {
        param_2[1] = 0;
        *param_2 = 0;
        return;
      }
      param_2[1] = param_2[1] & 0xf0;
    }
    else if (param_2[2] == 0) {
      if ((param_2[1] & 0x40) == 0) {
        lVar3 = PlaySE__4SdrvFUiP8_SeParam(sys__4Sdrv,*(u32 *)(param_2 + 4),param_2 + 0x14);
        if (lVar3 == -1) {
          return;
        }
        *(int *)(param_2 + 0xc) = (int)lVar3;
        param_2[2] = param_2[2] + 1;
        return;
      }
      param_2[1] = param_2[1] & 0xf0;
      param_2[2] = 0;
    }
  }
  if ((param_2[1] & 0x40) == 0) {
    if ((param_2[1] & 0x10) != 0) {
      if (((*param_2 & 1) == 0) && ((*param_2 & 2) != 0)) {
        SetSEParam__4SdrvFUiP8_SeParam(sys__4Sdrv,*(u32 *)(param_2 + 8),param_2 + 0x14);
      }
      param_2[1] = param_2[1] & 0xef;
    }
    if ((param_2[1] & 0x20) != 0) {
      if (((*param_2 & 1) == 0) && ((*param_2 & 2) != 0)) {
        SetSEParam__4SdrvFUiiii
                  (sys__4Sdrv,*(u32 *)(param_2 + 8),0,*(u16 *)(param_2 + 0x10),
                   *(u16 *)(param_2 + 0x12));
      }
      param_2[1] = param_2[1] & 0xdf;
    }
  }
  else if (((((*param_2 & 0x30) != 0) || ((*param_2 & 1) != 0)) || ((*param_2 & 2) == 0)) ||
          (lVar3 = ReleaseSE__4SdrvFUii(sys__4Sdrv,*(u32 *)(param_2 + 8),0), lVar3 != -1)) {
    *param_2 = 0;
    param_2[1] = 0;
  }
  return;
}

/* ---- 0x003c5580 size 0xa0  CSe::CheckSeReq(v)
 *      mangled: CheckSeReq__3CSeFv */
u32 CheckSeReq__3CSeFv(int *param_1)

{
  byte *pbVar1;
  int iVar2;
  
  pbVar1 = *(byte **)(*param_1 + 4);
  iVar2 = 0;
  while( true ) {
    if ((int)(uint)*(ushort *)(*param_1 + 0xe) <= iVar2) {
      return 0;
    }
    if (((*pbVar1 & 0x80) != 0) && ((pbVar1[1] & 0x11) != 0)) break;
    iVar2 = iVar2 + 1;
  }
  return 1;
}

