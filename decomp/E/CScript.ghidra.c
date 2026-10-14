/*
 * CScript.ghidra.c -- Ghidra decompiler output (SLPM_602.19, JP Furokuban), tidied by tools/E_gen_decomp.py
 * 71 functions. Types: u8/u16/u32/u64 = undefined1/2/4/8. Addresses in comments are JP main-exe addresses.
 */

/* ---- 0x00291ba0 size 0x68  CScript::CScript(v)
 *      mangled: __ct__7CScriptFv */
int __ct__7CScriptFv(int param_1)

{
  __ct__7CPolObjFv(param_1);
  *(u8 **)(param_1 + 0x14) = __vt__7CScript;
  *(int *)(param_1 + 0x24) = sys__7CScript;
  sys__7CScript = param_1;
  *(u8 *)(param_1 + 0x18) = 0;
  *(u32 *)(param_1 + 0x1c) = 0;
  *(u32 *)(param_1 + 0x20) = 0;
  return param_1;
}

/* ---- 0x00291c10 size 0x8c  CScript::~CScript(v)
 *      mangled: __dt__7CScriptFv */
int __dt__7CScriptFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(u8 **)(param_1 + 0x14) = __vt__7CScript;
    Release__7CScriptFi(param_1,0);
    sys__7CScript = *(u32 *)(param_1 + 0x24);
    __dt__7CPolObjFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* ---- 0x00291ca0 size 0x44  CScript::GetBufferSize(ii)
 *      mangled: GetBufferSize__7CScriptFii */
int GetBufferSize__7CScriptFii(u64 param_1,int param_2,int param_3)

{
  return param_3 * 4 + param_2 * 4 + 0x8b0;
}

/* ---- 0x00291cf0 size 0x178  CScript::Create(PUciii)
 *      mangled: Create__7CScriptFPUciii */
void Create__7CScriptFPUciii(int param_1,void *param_2,int param_3,int param_4,u16 param_5)

{
  u64 uVar1;
  int iVar2;
  u32 uStack_40;
  
  if (*(int *)(param_1 + 0x1c) == 0) {
    uStack_40 = param_2;
    if (param_2 == (void *)0x0) {
      uVar1 = GetBufferSize__7CScriptFii(param_1,param_3,param_4);
      uStack_40 = (void *)__nwa__FUi(uVar1);
      *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfd | 2;
    }
    memset(uStack_40,0,0xa8);
    *(void **)(param_1 + 0x1c) = uStack_40;
    *(int *)(*(int *)(param_1 + 0x1c) + 0x40) = (int)uStack_40 + 0xb0;
    iVar2 = *(int *)(*(int *)(param_1 + 0x1c) + 0x40) + param_3 * 4;
    *(int *)(*(int *)(param_1 + 0x1c) + 0x14) = iVar2;
    *(int *)(*(int *)(param_1 + 0x1c) + 0x18) = iVar2;
    *(int *)(*(int *)(param_1 + 0x1c) + 0x4c) =
         *(int *)(*(int *)(param_1 + 0x1c) + 0x14) + param_4 * 4;
    memset(*(void **)(*(int *)(param_1 + 0x1c) + 0x40),0,(long)(param_3 << 2));
    *(short *)(*(int *)(param_1 + 0x1c) + 0x52) = (short)param_3;
    *(short *)(*(int *)(param_1 + 0x1c) + 0x50) = (short)param_4;
    *(u16 *)(*(int *)(param_1 + 0x1c) + 0x54) = param_5;
  }
  return;
}

/* ---- 0x00291e70 size 0xf4  CScript::Release(i)
 *      mangled: Release__7CScriptFi */
u64 Release__7CScriptFi(int param_1,int param_2)

{
  if (param_2 == 0) {
    Dispose__7CScriptFv(param_1);
  }
  ReleaseBss__7CScriptFv(param_1);
  if ((long)((ulong)*(byte *)(param_1 + 0x18) << 0x3c) < 0) {
    __dt__9BufMemoryFv(*(u32 *)(*(int *)(param_1 + 0x1c) + 0x5c),1);
    *(u32 *)(*(int *)(param_1 + 0x1c) + 0x5c) = 0;
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xf7;
  }
  if ((long)((ulong)*(byte *)(param_1 + 0x18) << 0x3e) < 0) {
    __dla__FPv(*(u32 *)(param_1 + 0x1c));
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfd;
  }
  *(u32 *)(param_1 + 0x1c) = 0;
  return 0;
}

/* ---- 0x00291f70 size 0x84  CScript::Delete(v)
 *      mangled: Delete__7CScriptFv */
void Delete__7CScriptFv(int param_1)

{
  *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xef | 0x10;
  if ((*(byte *)(param_1 + 0x18) & 1) == 0) {
    if (param_1 != 0) {
      (**(code **)(*(int *)(param_1 + 0x14) + 8))(param_1,1);
    }
  }
  return;
}

/* ---- 0x00292000 size 0xe0  CScript::LoadScript(PcPUc)
 *      mangled: LoadScript__7CScriptFPcPUc */
void LoadScript__7CScriptFPcPUc(int param_1,char *param_2,u32 param_3)

{
  if (*(int *)(param_1 + 0x1c) != 0) {
    strcpy((char *)(*(int *)(param_1 + 0x1c) + 0x68),param_2);
    *(u32 *)(*(int *)(param_1 + 0x1c) + 100) = param_3;
    if ((*(byte *)(param_1 + 0x18) & 1) == 0) {
      Entry__7CScriptFv(param_1);
    }
    else {
      EndScene__7CScriptFv(param_1);
    }
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfb;
    *(byte *)(*(int *)(param_1 + 0x1c) + 0x58) =
         *(byte *)(*(int *)(param_1 + 0x1c) + 0x58) & 0x3f | 0x40;
  }
  return;
}

/* ---- 0x002920e0 size 0xc8  CScript::LoadScriptB(PcP9BufMemory)
 *      mangled: LoadScriptB__7CScriptFPcP9BufMemory */
void LoadScriptB__7CScriptFPcP9BufMemory(int param_1,char *param_2,u32 param_3)

{
  long lVar1;
  
  if (*(int *)(param_1 + 0x1c) != 0) {
    strcpy((char *)(*(int *)(param_1 + 0x1c) + 0x68),param_2);
    if ((*(byte *)(param_1 + 0x18) & 1) == 0) {
      Entry__7CScriptFv(param_1);
    }
    else {
      EndScene__7CScriptFv(param_1);
    }
    lVar1 = LoadNext__7CScriptFP9BufMemory(param_1,param_3);
    if (lVar1 != 0) {
      *(byte *)(*(int *)(param_1 + 0x1c) + 0x58) =
           *(byte *)(*(int *)(param_1 + 0x1c) + 0x58) & 0x3f | 0x80;
    }
  }
  return;
}

/* ---- 0x002921b0 size 0x180  CScript::LoadNext(P9BufMemory)
 *      mangled: LoadNext__7CScriptFP9BufMemory */
u32 LoadNext__7CScriptFP9BufMemory(int param_1,int param_2)

{
  u32 uVar1;
  u32 uStack_10;
  
  if (((ulong)*(byte *)(*(int *)(param_1 + 0x1c) + 0x58) & 0xf) >> 1 == 3) {
    if (param_2 != 0) {
      *(int *)(*(int *)(param_1 + 0x1c) + 0x60) = param_2;
    }
    uVar1 = 0;
  }
  else {
    uStack_10 = param_2;
    if (param_2 == 0) {
      uStack_10 = *(int *)(*(int *)(param_1 + 0x1c) + 0x60);
    }
    *(u32 *)(*(int *)(param_1 + 0x1c) + 0x60) = 0;
    if (uStack_10 == 0) {
      uVar1 = 0;
    }
    else {
      *(u32 *)(*(int *)(param_1 + 0x1c) + 100) = 0;
      if (*(int *)(*(int *)(param_1 + 0x1c) + 0x5c) != 0) {
        __dt__9BufMemoryFv(*(u32 *)(*(int *)(param_1 + 0x1c) + 0x5c),1);
        *(u32 *)(*(int *)(param_1 + 0x1c) + 0x5c) = 0;
      }
      *(int *)(*(int *)(param_1 + 0x1c) + 0x5c) = uStack_10;
      *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xf7 | 8;
      *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfb;
      *(byte *)(*(int *)(param_1 + 0x1c) + 0x58) = *(byte *)(*(int *)(param_1 + 0x1c) + 0x58) & 0xf1
      ;
      uVar1 = 1;
    }
  }
  return uVar1;
}

/* ---- 0x00292330 size 0xa8  CScript::ReleaseBss(v)
 *      mangled: ReleaseBss__7CScriptFv */
void ReleaseBss__7CScriptFv(int param_1)

{
  if (*(int *)(param_1 + 0x1c) != 0) {
    if (((long)((ulong)*(byte *)(*(int *)(param_1 + 0x1c) + 0x35) << 0x3a) < 0) &&
       (*(int *)(*(int *)(param_1 + 0x1c) + 8) != 0)) {
      __dla__FPv(*(u32 *)(*(int *)(param_1 + 0x1c) + 8));
      *(u32 *)(*(int *)(param_1 + 0x1c) + 8) = 0;
    }
    *(byte *)(*(int *)(param_1 + 0x1c) + 0x35) = *(byte *)(*(int *)(param_1 + 0x1c) + 0x35) & 0xdf;
  }
  return;
}

/* ---- 0x002923e0 size 0x48c  CScript::InitScript(PcPUc)
 *      mangled: InitScript__7CScriptFPcPUc */
u32 InitScript__7CScriptFPcPUc(int param_1,char *param_2,int param_3)

{
  int *__src;
  int iVar1;
  int *piVar2;
  u32 uVar3;
  ushort *puVar4;
  ushort *puVar5;
  void *__src_00;
  ushort uVar6;
  int iVar7;
  int iStack_38;
  uint uStack_34;
  int iStack_30;
  char *pcStack_20;
  int *piStack_10;
  
  *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xbf;
  *(byte *)(*(int *)(param_1 + 0x1c) + 0x58) = *(byte *)(*(int *)(param_1 + 0x1c) + 0x58) & 0xf1;
  *(byte *)(*(int *)(param_1 + 0x1c) + 0x58) = *(byte *)(*(int *)(param_1 + 0x1c) + 0x58) & 0x3f;
  *(int *)(*(int *)(param_1 + 0x1c) + 0x48) = param_3;
  iStack_30 = param_1;
  pcStack_20 = param_2;
  piStack_10 = (int *)param_3;
  ReleaseBss__7CScriptFv(param_1);
  iVar7 = *(int *)(*(int *)(iStack_30 + 0x1c) + 0x40) +
          (uint)*(ushort *)(*(int *)(iStack_30 + 0x1c) + 0x52) * 4;
  *(int *)(*(int *)(iStack_30 + 0x1c) + 0x14) = iVar7;
  *(int *)(*(int *)(iStack_30 + 0x1c) + 0x18) = iVar7;
  if (pcStack_20 != (char *)0x0) {
    strcpy((char *)(*(int *)(iStack_30 + 0x1c) + 0x68),pcStack_20);
  }
  if (*(char *)(param_3 + 2) == '\0') {
    uVar3 = 0xffffffff;
  }
  else {
    CreateNewJCB__7CScriptFi(iStack_30,0);
    __src = *(int **)(*(int *)(iStack_30 + 0x1c) + 0x10);
    __src[9] = 0;
    piVar2 = (int *)((int)piStack_10 + (uint)*(byte *)(param_3 + 1) * 0x10);
    piStack_10 = piVar2;
    if (*(short *)(param_3 + 6) != 0) {
      piStack_10 = piVar2 + (uint)*(ushort *)(param_3 + 6) * 4;
      for (; piVar2 < piStack_10; piVar2 = piVar2 + (uint)*(ushort *)((int)piVar2 + 6) * 4) {
        if ((*piVar2 == 0x544e5645) && (__src[9] == 0)) {
          __src[9] = (int)piVar2;
        }
      }
    }
    *__src = (int)piStack_10;
    __src[1] = (int)(piStack_10 + (uint)*(ushort *)(param_3 + 8) * 4);
    uVar6 = 0;
    if (*(short *)(param_3 + 0x18) != 0) {
      puVar5 = (ushort *)(param_3 + (uint)*(ushort *)(param_3 + 0x18) * 0x10);
      uStack_34 = (uint)*puVar5;
      uVar6 = puVar5[1];
      for (iVar7 = 0; puVar4 = puVar5 + 2, iVar7 < (int)uStack_34; iVar7 = iVar7 + 1) {
        if ((*puVar4 & 0xf) == 0) {
          __src_00 = (void *)(*__src + (uint)puVar5[3]);
        }
        else {
          __src_00 = (void *)(__src[1] + (uint)puVar5[3]);
        }
        memcpy(&iStack_38,__src_00,4);
        if ((byte)((byte)*puVar4 >> 4) == 0) {
          iVar1 = *__src;
        }
        else {
          iVar1 = __src[1];
        }
        iStack_38 = iStack_38 + iVar1;
        memcpy(__src_00,&iStack_38,4);
        puVar5 = puVar4;
      }
    }
    if (*(short *)(param_3 + 0xc) != 0) {
      if (*(ushort *)(param_3 + 0xc) < uVar6) {
        __src[2] = param_3 + (uint)*(ushort *)(param_3 + 0x18) * 0x10;
      }
      else {
        iVar7 = __nwa__FUi(*(u16 *)(param_3 + 0xc));
        __src[2] = iVar7;
        *(byte *)((int)__src + 0x35) = *(byte *)((int)__src + 0x35) & 0xdf | 0x20;
      }
    }
    __src[3] = *__src + (uint)*(ushort *)(param_3 + 0xe);
    memcpy(*(void **)(iStack_30 + 0x1c),__src,0x40);
    *(int **)(*(int *)(iStack_30 + 0x1c) + 0x10) = __src;
    uVar3 = EnterUFunc__7CScriptFPUcPUcii(iStack_30,0,__src[3],0,0);
    *(u32 *)(*(int *)(iStack_30 + 0x1c) + 0xc) = uVar3;
    if ((*(int *)(*(int *)(iStack_30 + 0x1c) + 100) != 0) &&
       (*(int *)(*(int *)(iStack_30 + 0x1c) + 0x5c) != 0)) {
      __dt__9BufMemoryFv(*(u32 *)(*(int *)(iStack_30 + 0x1c) + 0x5c),1);
      *(u32 *)(*(int *)(iStack_30 + 0x1c) + 0x5c) = 0;
    }
    uVar3 = 0;
  }
  return uVar3;
}

/* ---- 0x00292870 size 0x120  CScript::StartScript(v)
 *      mangled: StartScript__7CScriptFv */
void StartScript__7CScriptFv(int param_1)

{
  if ((*(int *)(param_1 + 0x1c) != 0) && (*(int *)(*(int *)(param_1 + 0x1c) + 0xc) != 0)) {
    if (((ulong)*(byte *)(*(int *)(param_1 + 0x1c) + 0x58) & 0xf) >> 1 == 3) {
      *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xdf;
      Entry__7CScriptFv(param_1);
      return;
    }
    StartScene__7CScriptFv(param_1);
    *(byte *)(*(int *)(param_1 + 0x1c) + 0x58) =
         *(byte *)(*(int *)(param_1 + 0x1c) + 0x58) & 0xf1 | 4;
    *(byte *)(*(int *)(param_1 + 0x1c) + 0x58) = *(byte *)(*(int *)(param_1 + 0x1c) + 0x58) & 0x3f;
    Entry__7CScriptFv(param_1);
  }
  *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xdf;
  return;
}

/* ---- 0x00292990 size 0x70  CScript::Entry(v)
 *      mangled: Entry__7CScriptFv */
void Entry__7CScriptFv(int param_1)

{
  if ((*(byte *)(param_1 + 0x18) & 1) == 0) {
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfe | 1;
    Entry__7CPollerFP7CPolObjib(app__4CApp + 0x48,param_1,0x80,0);
  }
  return;
}

/* ---- 0x00292a00 size 0x60  CScript::Dispose(v)
 *      mangled: Dispose__7CScriptFv */
void Dispose__7CScriptFv(int param_1)

{
  if ((*(byte *)(param_1 + 0x18) & 1) != 0) {
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfe;
    Dispose__7CPollerFP7CPolObj(app__4CApp + 0x48,param_1);
  }
  return;
}

/* ---- 0x00292a60 size 0x3c8  CScript::Polling(v)
 *      mangled: Polling__7CScriptFv */
u32 Polling__7CScriptFv(int param_1)

{
  u32 uVar1;
  long lVar2;
  
  if ((long)((ulong)*(byte *)(param_1 + 0x18) << 0x3b) < 0) {
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfe;
    Release__7CScriptFi(param_1,1);
    *(u8 *)(param_1 + 0xc) = 1;
    *(u8 *)(param_1 + 0xe) = 0;
    uVar1 = 1;
  }
  else {
    if (param_1 == sys__7CScript) {
      UpdateScan__7CScriptFv();
    }
    if ((long)((ulong)*(byte *)(param_1 + 0x18) << 0x3a) < 0) {
      uVar1 = 0;
    }
    else {
      if (((((*(int *)(*(int *)(param_1 + 0x1c) + 0xc) != 0) ||
            (*(int *)(*(int *)(param_1 + 0x1c) + 0x4c) == 0)) ||
           (*(short *)(*(int *)(param_1 + 0x1c) + 0x5a) == 0)) ||
          (lVar2 = CheckDlyEvent__7CScriptFv(param_1), lVar2 != 0)) &&
         (((*(int *)(*(int *)(param_1 + 0x1c) + 0xc) != 0 &&
           (((ulong)*(byte *)(*(int *)(param_1 + 0x1c) + 0x58) & 0xf) >> 1 != 0)) &&
          (((ulong)*(byte *)(*(int *)(param_1 + 0x1c) + 0x58) & 0xf) >> 1 < 4)))) {
        *(int *)(*(int *)(param_1 + 0x1c) + 0x44) = current__7CScript;
        current__7CScript = param_1;
        lVar2 = JobExec__7CScriptFv(param_1);
        current__7CScript = *(u32 *)(*(int *)(param_1 + 0x1c) + 0x44);
        if (*(int *)(*(int *)(param_1 + 0x1c) + 0xc) == 0) {
          lVar2 = -1;
        }
        if (-1 < lVar2) {
          return 0;
        }
        if (2 < ((ulong)*(byte *)(*(int *)(param_1 + 0x1c) + 0x58) & 0xf) >> 1) {
          TerminateJob__7CScriptFv(param_1);
          *(byte *)(*(int *)(param_1 + 0x1c) + 0x58) =
               *(byte *)(*(int *)(param_1 + 0x1c) + 0x58) & 0xf1 | 8;
          lVar2 = LoadNext__7CScriptFP9BufMemory(param_1,0);
          if (lVar2 == 0) {
            if ((long)((ulong)*(byte *)(param_1 + 0x18) << 0x39) < 0) {
              InitScript__7CScriptFPcPUc(param_1,0,*(u32 *)(*(int *)(param_1 + 0x1c) + 0x48))
              ;
              StartScript__7CScriptFv(param_1);
              return 0;
            }
          }
          else {
            *(byte *)(*(int *)(param_1 + 0x1c) + 0x58) =
                 *(byte *)(*(int *)(param_1 + 0x1c) + 0x58) & 0x3f | 0x80;
            *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfb | 4;
          }
        }
      }
      if (*(byte *)(*(int *)(param_1 + 0x1c) + 0x58) >> 6 != 0) {
        *(int *)(*(int *)(param_1 + 0x1c) + 0x44) = current__7CScript;
        current__7CScript = param_1;
        lVar2 = JobChain__7CScriptFv(param_1);
        current__7CScript = *(u32 *)(*(int *)(param_1 + 0x1c) + 0x44);
        if (-1 < lVar2) {
          if (lVar2 == 1) {
            StartScript__7CScriptFv(param_1);
          }
          return 0;
        }
      }
      if ((*(int *)(*(int *)(param_1 + 0x1c) + 0x4c) == 0) ||
         (*(short *)(*(int *)(param_1 + 0x1c) + 0x5a) == 0)) {
        *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfe;
        uVar1 = 1;
      }
      else {
        uVar1 = 0;
      }
    }
  }
  return uVar1;
}

/* ---- 0x00292e30 size 0x100  CScript::UpdateScan(v)
 *      mangled: UpdateScan__7CScriptFv */
void UpdateScan__7CScriptFv(void)

{
  long lVar1;
  
  lVar1 = GetActive__4CPadFi(0);
  if (lVar1 == 0) {
    bPadR__7CScript = 0;
  }
  else {
    bPadR__7CScript = (uint)*(ushort *)((&m_pCoreArray__4CPad)[*(int *)((int)lVar1 + 4)] + 0x6a);
  }
  bPadF__7CScript = bPadF__7CScript & bPadR__7CScript;
  bPadS__7CScript = bPadR__7CScript & ~bPadF__7CScript;
  if (lVar1 == 0) {
    bPadD__7CScript = 0;
  }
  else {
    bPadD__7CScript =
         ~bPadF__7CScript &
         (uint)*(ushort *)((&m_pCoreArray__4CPad)[*(int *)((int)lVar1 + 4)] + 0x70);
  }
  return;
}

/* ---- 0x00292f30 size 0xf4  CScript::CreateNewJCB(i)
 *      mangled: CreateNewJCB__7CScriptFi */
void * CreateNewJCB__7CScriptFi(int param_1,byte param_2)

{
  void *pvVar1;
  u32 uVar2;
  void *pvVar3;
  
  pvVar1 = *(void **)(*(int *)(param_1 + 0x1c) + 0x10);
  if (pvVar1 != (void *)0x0) {
    uVar2 = *(u32 *)((int)pvVar1 + 0x10);
    memcpy(pvVar1,*(void **)(param_1 + 0x1c),0x40);
    *(u32 *)((int)pvVar1 + 0x10) = uVar2;
  }
  pvVar1 = *(void **)(*(int *)(param_1 + 0x1c) + 0x18);
  memset(pvVar1,0,0x40);
  memcpy(pvVar1,*(void **)(param_1 + 0x1c),0x40);
  *(int *)((int)pvVar1 + 0x14) = (int)pvVar1 + 0x40;
  *(int *)((int)pvVar1 + 0x18) = (int)pvVar1 + 0x40;
  *(byte *)((int)pvVar1 + 0x35) = *(byte *)((int)pvVar1 + 0x35) & 0xf0 | param_2 & 0xf;
  pvVar3 = memcpy(*(void **)(param_1 + 0x1c),pvVar1,0x40);
  *(void **)(*(int *)(param_1 + 0x1c) + 0x10) = pvVar1;
  return pvVar3;
}

/* ---- 0x00293030 size 0x20  CScript::ResetEvent(v)
 *      mangled: ResetEvent__7CScriptFv */
void ResetEvent__7CScriptFv(int param_1)

{
  *(u32 *)(*(int *)(param_1 + 0x1c) + 0x28) = 0;
  return;
}

/* ---- 0x00293050 size 0x11c  CScript::DeleteCurJCB(v)
 *      mangled: DeleteCurJCB__7CScriptFv */
void DeleteCurJCB__7CScriptFv(int param_1)

{
  u32 *puVar1;
  void *__src;
  
  if (*(int *)(*(int *)(param_1 + 0x1c) + 0x28) != 0) {
    puVar1 = (u32 *)**(int **)(*(int *)(param_1 + 0x1c) + 0x28);
    if ((int)puVar1 < 0x10000) {
      **(u32 **)(*(int *)(param_1 + 0x1c) + 0x28) = 1;
    }
    else {
      *puVar1 = *(u32 *)(*(int *)(*(int *)(param_1 + 0x1c) + 0x18) + -4);
    }
  }
  if (*(int *)(*(int *)(param_1 + 0x1c) + 0x10) == 0) {
    __src = (void *)0x0;
  }
  else {
    __src = *(void **)(*(int *)(*(int *)(param_1 + 0x1c) + 0x10) + 0x10);
  }
  if (__src == (void *)0x0) {
    *(u32 *)(*(int *)(param_1 + 0x1c) + 0xc) = 0;
  }
  else {
    memcpy(*(void **)(param_1 + 0x1c),__src,0x40);
    *(void **)(*(int *)(param_1 + 0x1c) + 0x10) = __src;
  }
  return;
}

/* ---- 0x00293170 size 0x2c  CScript::cbReadComplete(iP9BufMemoryiPcPv)
 *      mangled: cbReadComplete__7CScriptFiP9BufMemoryiPcPv */
u64
cbReadComplete__7CScriptFiP9BufMemoryiPcPv
          (u64 param_1,u32 param_2,u64 param_3,u64 param_4,int param_5)

{
  *(u32 *)(*(int *)(param_5 + 0x1c) + 0x5c) = param_2;
  return 0;
}

/* ---- 0x002931a0 size 0x2c8  CScript::LoadTarg(v)
 *      mangled: LoadTarg__7CScriptFv */
u32 LoadTarg__7CScriptFv(int param_1)

{
  int iVar1;
  byte bVar2;
  long lVar3;
  u64 uVar4;
  
  bVar2 = *(byte *)(*(int *)(param_1 + 0x1c) + 0x58) >> 6;
  if (bVar2 == 2) {
    if (*(int *)(*(int *)(param_1 + 0x1c) + 0x5c) != 0) {
      InitScript__7CScriptFPcPUc
                (param_1,0,*(u32 *)(*(int *)(*(int *)(param_1 + 0x1c) + 0x5c) + 4));
      *(byte *)(*(int *)(param_1 + 0x1c) + 0x58) =
           *(byte *)(*(int *)(param_1 + 0x1c) + 0x58) & 0x3f | 0xc0;
      if (-1 < (long)((ulong)*(byte *)(param_1 + 0x18) << 0x3d)) {
        return 0xfffffffe;
      }
      return 1;
    }
  }
  else if ((bVar2 == 1) && (((ulong)*(byte *)(*(int *)(param_1 + 0x1c) + 0x58) & 0xf) >> 1 == 0)) {
    if (*(int *)(*(int *)(param_1 + 0x1c) + 0x5c) != 0) {
      __dt__9BufMemoryFv(*(u32 *)(*(int *)(param_1 + 0x1c) + 0x5c),1);
      *(u32 *)(*(int *)(param_1 + 0x1c) + 0x5c) = 0;
    }
    if (*(int *)(*(int *)(param_1 + 0x1c) + 100) == 0) {
      ReadOrder__11DvdromOrderFPCcPFiP9BufMemoryiPcPv_iiPvi
                (Dvdromour__11DvdromOrder,*(int *)(param_1 + 0x1c) + 0x68,0x293170,0,param_1,0);
      *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xf7 | 8;
    }
    else {
      lVar3 = __nw__FUi(0x10);
      uVar4 = 0;
      if (lVar3 != 0) {
        uVar4 = __ct__9BufMemoryFv(lVar3);
      }
      SetBuffer__9BufMemoryFUlPUc(uVar4,0x20000,*(u32 *)(*(int *)(param_1 + 0x1c) + 100));
      ReadOrder__11DvdromOrderFPCcPFiP9BufMemoryiPcPv_iiP9BufMemoryPvi
                (Dvdromour__11DvdromOrder,*(int *)(param_1 + 0x1c) + 0x68,0x293170,0,uVar4,param_1,0
                );
      *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xf7;
    }
    iVar1 = *(int *)(param_1 + 0x1c);
    *(byte *)(iVar1 + 0x58) =
         *(byte *)(iVar1 + 0x58) & 0x3f |
         (byte)(((uint)(((ulong)*(byte *)(iVar1 + 0x58) << 0x38) >> 0x3e) + 1 & 3) << 6);
  }
  return 0;
}

/* ---- 0x00293470 size 0xf8  CScript::TerminateJob(v)
 *      mangled: TerminateJob__7CScriptFv */
void TerminateJob__7CScriptFv(int param_1)

{
  int iVar1;
  
  if ((*(int *)(*(int *)(param_1 + 0x1c) + 0x4c) != 0) &&
     (*(short *)(*(int *)(param_1 + 0x1c) + 0x5a) != 0)) {
    memset(*(void **)(*(int *)(param_1 + 0x1c) + 0x4c),0,0x200);
    *(u16 *)(*(int *)(param_1 + 0x1c) + 0x5a) = 0;
  }
  iVar1 = *(int *)(*(int *)(param_1 + 0x1c) + 0x40) +
          (uint)*(ushort *)(*(int *)(param_1 + 0x1c) + 0x52) * 4;
  *(int *)(*(int *)(param_1 + 0x1c) + 0x14) = iVar1;
  *(int *)(*(int *)(param_1 + 0x1c) + 0x18) = iVar1;
  *(u32 *)(*(int *)(param_1 + 0x1c) + 0x10) = 0;
  *(u32 *)(*(int *)(param_1 + 0x1c) + 0xc) = 0;
  *(u32 *)(*(int *)(param_1 + 0x1c) + 0x20) = 0;
  *(u32 *)(*(int *)(param_1 + 0x1c) + 0x28) = 0;
  *(u32 *)(*(int *)(param_1 + 0x1c) + 0x2c) = 0;
  *(u32 *)(*(int *)(param_1 + 0x1c) + 0x30) = 0;
  return;
}

/* ---- 0x00293570 size 0xac  CScript::StartScene(v)
 *      mangled: StartScene__7CScriptFv */
void StartScene__7CScriptFv(int param_1)

{
  u32 uVar1;
  
  *(u32 *)(*(int *)(param_1 + 0x1c) + 0x18) =
       *(u32 *)(*(int *)(param_1 + 0x1c) + 0x14);
  uVar1 = EnterUFunc__7CScriptFPUcPUcii
                    (param_1,0,
                     **(int **)(param_1 + 0x1c) +
                     (uint)*(ushort *)(*(int *)(*(int *)(param_1 + 0x1c) + 0x48) + 0xe),0,0);
  *(u32 *)(*(int *)(param_1 + 0x1c) + 0xc) = uVar1;
  if (*(int *)(param_1 + 0x20) != 0) {
    StartSequence__9CScriptExFv(*(u32 *)(param_1 + 0x20));
  }
  return;
}

/* ---- 0x00293620 size 0x170  CScript::EndScene(v)
 *      mangled: EndScene__7CScriptFv */
void EndScene__7CScriptFv(int param_1)

{
  u32 uVar1;
  
  if ((((ulong)*(byte *)(*(int *)(param_1 + 0x1c) + 0x58) & 0xf) >> 1 != 0) &&
     (((ulong)*(byte *)(*(int *)(param_1 + 0x1c) + 0x58) & 0xf) >> 1 < 3)) {
    if (*(short *)(*(int *)(*(int *)(param_1 + 0x1c) + 0x48) + 0x10) == -1) {
      *(byte *)(*(int *)(param_1 + 0x1c) + 0x58) =
           *(byte *)(*(int *)(param_1 + 0x1c) + 0x58) & 0xf1 | 8;
      TerminateJob__7CScriptFv(param_1);
    }
    else {
      TerminateJob__7CScriptFv(param_1);
      *(byte *)(*(int *)(param_1 + 0x1c) + 0x58) =
           *(byte *)(*(int *)(param_1 + 0x1c) + 0x58) & 0xf1 | 6;
      *(u8 *)(*(int *)(param_1 + 0x1c) + 0x34) = 0;
      uVar1 = EnterUFunc__7CScriptFPUcPUcii
                        (param_1,0,
                         **(int **)(param_1 + 0x1c) +
                         (uint)*(ushort *)(*(int *)(*(int *)(param_1 + 0x1c) + 0x48) + 0x10),0,0);
      *(u32 *)(*(int *)(param_1 + 0x1c) + 0xc) = uVar1;
      *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xdf;
    }
    *(u16 *)(*(int *)(param_1 + 0x1c) + 0x56) = 0;
  }
  return;
}

/* ---- 0x00293790 size 0x50  CScript::JobChain(v)
 *      mangled: JobChain__7CScriptFv */
u64 JobChain__7CScriptFv(u32 param_1)

{
  long lVar1;
  u64 uVar2;
  
  lVar1 = ResetScene__7CScriptFv(param_1);
  if (lVar1 == 0) {
    uVar2 = LoadTarg__7CScriptFv(param_1);
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

/* ---- 0x00293880 size 0x14c  CScript::ResetScene(v)
 *      mangled: ResetScene__7CScriptFv */
u32 ResetScene__7CScriptFv(int param_1)

{
  u32 uVar1;
  int iVar2;
  
  if (((ulong)*(byte *)(*(int *)(param_1 + 0x1c) + 0x58) & 0xf) >> 1 == 0) {
    uVar1 = 0;
  }
  else if (((ulong)*(byte *)(*(int *)(param_1 + 0x1c) + 0x58) & 0xf) >> 1 == 4) {
    if (*(int *)(param_1 + 0x20) != 0) {
      ResetSequence__9CScriptExFi
                (*(u32 *)(param_1 + 0x20),*(u16 *)(*(int *)(param_1 + 0x1c) + 0x56));
    }
    *(u16 *)(*(int *)(param_1 + 0x1c) + 0x56) = 0;
    *(byte *)(*(int *)(param_1 + 0x1c) + 0x58) = *(byte *)(*(int *)(param_1 + 0x1c) + 0x58) & 0xf1;
    iVar2 = *(int *)(*(int *)(param_1 + 0x1c) + 0x40) +
            (uint)*(ushort *)(*(int *)(param_1 + 0x1c) + 0x52) * 4;
    *(int *)(*(int *)(param_1 + 0x1c) + 0x14) = iVar2;
    *(int *)(*(int *)(param_1 + 0x1c) + 0x18) = iVar2;
    *(u32 *)(*(int *)(param_1 + 0x1c) + 0x10) = 0;
    *(u32 *)(*(int *)(param_1 + 0x1c) + 0xc) = 0;
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}

/* ---- 0x002939d0 size 0x1a8  CScript::CheckDlyEvent(v)
 *      mangled: CheckDlyEvent__7CScriptFv */
u32 CheckDlyEvent__7CScriptFv(int param_1)

{
  uint uVar1;
  int iVar2;
  u8 *__dest;
  u8 *puVar3;
  int iVar4;
  size_t __n;
  
  if ((*(int *)(*(int *)(param_1 + 0x1c) + 0x4c) != 0) &&
     (*(short *)(*(int *)(param_1 + 0x1c) + 0x5a) != 0)) {
    uVar1 = (uint)*(ushort *)(*(int *)(param_1 + 0x1c) + 0x5a);
    iVar2 = GetTimer__7SysToolFv();
    __dest = *(u8 **)(*(int *)(param_1 + 0x1c) + 0x4c);
    for (iVar4 = 0; iVar4 < (int)uVar1; iVar4 = iVar4 + 1) {
      if (*(uint *)(__dest + 0xc) <= (uint)(iVar2 - *(int *)(__dest + 8))) {
        CallEvent__7CScriptFUiiP9_ParStackPi
                  (param_1,*(u32 *)(__dest + 4),*__dest,__dest + 0x10,0);
        *(short *)(*(int *)(param_1 + 0x1c) + 0x5a) =
             *(short *)(*(int *)(param_1 + 0x1c) + 0x5a) + -1;
        if (iVar4 < (int)(uVar1 - 1)) {
          __n = 0;
          puVar3 = __dest + (byte)__dest[1];
          for (; iVar4 < (int)uVar1; iVar4 = iVar4 + 1) {
            __n = (size_t)(int)((int)__n + (uint)(byte)puVar3[1]);
            puVar3 = puVar3 + (byte)puVar3[1];
          }
          memcpy(__dest,__dest + (byte)__dest[1],__n);
        }
        return 1;
      }
      __dest = __dest + (byte)__dest[1];
    }
  }
  return 0;
}

/* ---- 0x00293b80 size 0x120  CScript::GetDlyEvent(i)
 *      mangled: GetDlyEvent__7CScriptFi */
u8 * GetDlyEvent__7CScriptFi(int param_1,int param_2)

{
  u8 *__s;
  int iVar1;
  int iVar2;
  
  if (*(int *)(*(int *)(param_1 + 0x1c) + 0x4c) != 0) {
    __s = *(u8 **)(*(int *)(param_1 + 0x1c) + 0x4c);
    iVar2 = 0;
    for (iVar1 = 0; iVar1 < (int)(uint)*(ushort *)(*(int *)(param_1 + 0x1c) + 0x5a);
        iVar1 = iVar1 + 1) {
      iVar2 = iVar2 + (uint)(byte)__s[1];
      __s = __s + (byte)__s[1];
    }
    iVar1 = param_2 * 4 + 0x10;
    if ((long)iVar1 <= (long)(0x200 - iVar2)) {
      memset(__s,0,(long)iVar1);
      *__s = (char)param_2;
      __s[1] = (char)iVar1;
      *(short *)(*(int *)(param_1 + 0x1c) + 0x5a) = *(short *)(*(int *)(param_1 + 0x1c) + 0x5a) + 1;
      return __s;
    }
  }
  return (u8 *)0x0;
}

/* ---- 0x00293ca0 size 0x3fc  CScript::JobExec(v)
 *      mangled: JobExec__7CScriptFv */
u32 JobExec__7CScriptFv(int param_1)

{
  byte bVar1;
  long lVar2;
  uint uVar3;
  int iVar4;
  byte *pbStack_14;
  int iStack_10;
  
  uVar3 = REG_RCNT3_COUNT;
  if (uVar3 < HCount__3Gsx) {
    uVar3 = uVar3 + 0x10000;
  }
  iVar4 = uVar3 - HCount__3Gsx;
  iStack_10 = param_1;
  lVar2 = CheckDlyEvent__7CScriptFv(param_1);
  if (lVar2 == 0) {
    bVar1 = *(byte *)(*(int *)(iStack_10 + 0x1c) + 0x34);
    pbStack_14 = *(byte **)(*(int *)(iStack_10 + 0x1c) + 0xc);
    if (bVar1 == 0) goto LAB_00293d68;
    if (3 < bVar1) goto LAB_00293d68;
    FlushCache(0);
  }
  else {
    pbStack_14 = *(byte **)(*(int *)(iStack_10 + 0x1c) + 0xc);
  }
LAB_00293f70:
  do {
    lVar2 = GetParameter__7CScriptFRPUc(iStack_10,&pbStack_14);
    if (lVar2 == -1) {
      *(u32 *)(*(int *)(iStack_10 + 0x1c) + 0xc) = 0;
      return 0xffffffff;
    }
    if ((long)((ulong)*(byte *)(iStack_10 + 0x18) << 0x3b) < 0) {
      return 0;
    }
    if (lVar2 == -2) {
      *(byte **)(*(int *)(iStack_10 + 0x1c) + 0xc) = pbStack_14;
      *(u8 *)(*(int *)(iStack_10 + 0x1c) + 0x34) = 1;
      return 2;
    }
    bVar1 = *pbStack_14;
    if (bVar1 < 0x90) goto LAB_00293d68;
    if (0x9f < bVar1) goto LAB_00293d68;
    Statement__7CScriptFiRPUc(iStack_10,bVar1,&pbStack_14);
  } while (bVar1 == 0x98);
  if ((*(byte *)(*(int *)(iStack_10 + 0x1c) + 0x59) & 1) != 0) goto LAB_00293d68;
  do {
    *(byte **)(*(int *)(iStack_10 + 0x1c) + 0xc) = pbStack_14;
    CheckDlyEvent__7CScriptFv(iStack_10);
    if (pbStack_14 == (byte *)0x0) {
      DeleteCurJCB__7CScriptFv(iStack_10);
      if ((((ulong)*(byte *)(*(int *)(iStack_10 + 0x1c) + 0x58) & 0xf) >> 1 != 2) ||
         (*(int *)(*(int *)(iStack_10 + 0x1c) + 0xc) == 0)) {
        *(u32 *)(*(int *)(iStack_10 + 0x1c) + 0xc) = 0;
        if (((ulong)*(byte *)(*(int *)(iStack_10 + 0x1c) + 0x58) & 0xf) >> 1 == 3) {
          *(byte *)(*(int *)(iStack_10 + 0x1c) + 0x58) =
               *(byte *)(*(int *)(iStack_10 + 0x1c) + 0x58) & 0xf1 | 8;
        }
        return 0xffffffff;
      }
      pbStack_14 = *(byte **)(*(int *)(iStack_10 + 0x1c) + 0xc);
    }
    bVar1 = *pbStack_14;
    if ((bVar1 < 0x90) || (0x9f < bVar1)) {
      if (bVar1 == 0) {
        *(u32 *)(*(int *)(iStack_10 + 0x1c) + 0xc) = 0;
        return 0xffffffff;
      }
      if (bVar1 != 1) goto LAB_00293f70;
      pbStack_14 = pbStack_14 + 1;
    }
    else {
      Statement__7CScriptFiRPUc(iStack_10,bVar1,&pbStack_14);
      if (bVar1 == 0x98) goto LAB_00293f70;
    }
LAB_00293d68:
    *(u32 *)(*(int *)(iStack_10 + 0x1c) + 0x18) =
         *(u32 *)(*(int *)(iStack_10 + 0x1c) + 0x14);
    uVar3 = REG_RCNT3_COUNT;
    if (uVar3 < HCount__3Gsx) {
      uVar3 = uVar3 + 0x10000;
    }
    if ((ulong)(long)*(short *)(*(int *)(iStack_10 + 0x1c) + 0x54) <
        (ulong)(long)(int)((uVar3 - HCount__3Gsx) - iVar4)) {
      *(byte **)(*(int *)(iStack_10 + 0x1c) + 0xc) = pbStack_14;
      return 1;
    }
  } while( true );
}

/* ---- 0x002940a0 size 0x90  CScript::GetCodePtr(RPUc)
 *      mangled: GetCodePtr__7CScriptFRPUc */
int GetCodePtr__7CScriptFRPUc(int param_1,int *param_2)

{
  byte bVar1;
  byte bVar2;
  int iVar3;
  
  bVar1 = ((byte *)*param_2)[1];
  bVar2 = *(byte *)*param_2;
  iVar3 = **(int **)(param_1 + 0x1c);
  *param_2 = *param_2 + 2;
  return iVar3 + (uint)bVar2 + (uint)bVar1 * 0x100;
}

/* ---- 0x00294130 size 0x4e4  CScript::Statement(iRPUc)
 *      mangled: Statement__7CScriptFiRPUc */
void Statement__7CScriptFiRPUc(int param_1,int param_2,int *param_3)

{
  uint uVar1;
  byte *pbVar2;
  u32 uVar3;
  int iVar4;
  uint *puVar5;
  u32 *puVar6;
  int *piVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  
  *param_3 = *param_3 + 1;
  if (param_2 == 0x99) {
    iVar4 = LeaveUFunc__7CScriptFv(param_1);
    *param_3 = iVar4;
    if (*param_3 == 0) {
      puVar6 = *(u32 **)(*(int *)(param_1 + 0x1c) + 0x18);
      *(u32 **)(*(int *)(param_1 + 0x1c) + 0x18) = puVar6 + 1;
      *puVar6 = 0;
      return;
    }
    *(byte *)(*(int *)(param_1 + 0x1c) + 0x59) =
         *(byte *)(*(int *)(param_1 + 0x1c) + 0x59) & 0xfe | 1;
  }
  else {
    if (param_2 == 0x98) {
      puVar6 = (u32 *)(*(int *)(*(int *)(param_1 + 0x1c) + 0x18) + -4);
      *(u32 **)(*(int *)(param_1 + 0x1c) + 0x18) = puVar6;
      uVar3 = *puVar6;
      iVar4 = LeaveUFunc__7CScriptFv(param_1);
      *param_3 = iVar4;
      puVar6 = *(u32 **)(*(int *)(param_1 + 0x1c) + 0x18);
      *(u32 **)(*(int *)(param_1 + 0x1c) + 0x18) = puVar6 + 1;
      *puVar6 = uVar3;
      return;
    }
    if (param_2 == 0x94) {
      puVar5 = (uint *)(*(int *)(*(int *)(param_1 + 0x1c) + 0x18) + -4);
      *(uint **)(*(int *)(param_1 + 0x1c) + 0x18) = puVar5;
      uVar1 = *puVar5;
      iVar4 = GetCodePtr__7CScriptFRPUc(param_1,param_3);
      *param_3 = iVar4;
      uVar8 = (uint)*(byte *)*param_3 + (uint)((byte *)*param_3)[1] * 0x100;
      *param_3 = *param_3 + 2;
      uVar9 = (int)uVar8 >> 0xc & 7;
      *(byte *)(*(int *)(param_1 + 0x1c) + 0x59) = *(byte *)(*(int *)(param_1 + 0x1c) + 0x59) & 0xfe
      ;
      uVar11 = uVar8 & 0xfff;
      while (0 < (int)uVar11) {
        uVar10 = 0;
        if (uVar9 == 2) {
          pbVar2 = (byte *)*param_3;
          uVar10 = (uint)pbVar2[3] * 0x1000000 +
                   (uint)pbVar2[2] * 0x10000 + (uint)*pbVar2 + (uint)pbVar2[1] * 0x100;
          *param_3 = *param_3 + 4;
        }
        else if (uVar9 == 1) {
          uVar10 = (uint)*(byte *)*param_3 + (uint)((byte *)*param_3)[1] * 0x100;
          *param_3 = *param_3 + 2;
        }
        else if (uVar9 == 0) {
          pbVar2 = (byte *)*param_3;
          *param_3 = (int)(pbVar2 + 1);
          uVar10 = (uint)*pbVar2;
        }
        if (uVar10 == uVar1) {
          iVar4 = GetCodePtr__7CScriptFRPUc(param_1,param_3);
          *param_3 = iVar4;
          goto LAB_00294598;
        }
        *param_3 = *param_3 + 2;
        uVar11 = uVar11 - 1;
      }
      if ((uVar8 & 0x8000) != 0) {
        iVar4 = GetCodePtr__7CScriptFRPUc(param_1,param_3);
        *param_3 = iVar4;
      }
    }
    else if (param_2 == 0x92) {
      iVar4 = GetCodePtr__7CScriptFRPUc(param_1,param_3);
      piVar7 = (int *)(*(int *)(*(int *)(param_1 + 0x1c) + 0x18) + -4);
      *(int **)(*(int *)(param_1 + 0x1c) + 0x18) = piVar7;
      if (*piVar7 != 0) {
        *param_3 = iVar4;
      }
    }
    else if (param_2 == 0x91) {
      iVar4 = GetCodePtr__7CScriptFRPUc(param_1,param_3);
      piVar7 = (int *)(*(int *)(*(int *)(param_1 + 0x1c) + 0x18) + -4);
      *(int **)(*(int *)(param_1 + 0x1c) + 0x18) = piVar7;
      if (*piVar7 == 0) {
        *param_3 = iVar4;
      }
    }
    else if (param_2 == 0x90) {
      iVar4 = GetCodePtr__7CScriptFRPUc(param_1,param_3);
      *param_3 = iVar4;
    }
  }
LAB_00294598:
  *(u32 *)(*(int *)(param_1 + 0x1c) + 0x18) =
       *(u32 *)(*(int *)(param_1 + 0x1c) + 0x14);
  *(u32 *)(*(int *)(param_1 + 0x1c) + 0x20) = 0;
  *(byte *)(*(int *)(param_1 + 0x1c) + 0x59) = *(byte *)(*(int *)(param_1 + 0x1c) + 0x59) & 0xfe | 1
  ;
  return;
}

/* ---- 0x00294620 size 0xd9c  CScript::GetParameter(RPUc)
 *      mangled: GetParameter__7CScriptFRPUc */
u32 GetParameter__7CScriptFRPUc(int param_1,int *param_2)

{
  byte bVar1;
  byte *pbVar2;
  u8 *puVar3;
  u32 *puVar4;
  u8 *puVar5;
  uint uVar6;
  int iVar7;
  long lVar8;
  byte bVar9;
  
  if (*(char *)(*(int *)(param_1 + 0x1c) + 0x34) == '\x01') {
    lVar8 = ExecFunc__7CScriptFiii
                      (param_1,*(u8 *)(*(int *)(param_1 + 0x1c) + 0x36),
                       *(u8 *)(*(int *)(param_1 + 0x1c) + 0x37),
                       *(u32 *)(*(int *)(param_1 + 0x1c) + 0x38));
    if (lVar8 < 0) {
      *(int *)(*(int *)(param_1 + 0x1c) + 0x38) = (int)lVar8;
      return 0xfffffffe;
    }
    if (lVar8 == 0) {
      *(u32 *)(*(int *)(param_1 + 0x1c) + 0x18) =
           *(u32 *)(*(int *)(param_1 + 0x1c) + 0x14);
      *(u32 *)(*(int *)(param_1 + 0x1c) + 0x20) = 0;
      *(byte *)(*(int *)(param_1 + 0x1c) + 0x59) =
           *(byte *)(*(int *)(param_1 + 0x1c) + 0x59) & 0xfe | 1;
      *(u32 *)(*(int *)(param_1 + 0x1c) + 0x20) = 0;
    }
    else if (lVar8 == 7) {
      *param_2 = *(int *)(*(int *)(param_1 + 0x1c) + 0xc);
    }
    else if (lVar8 == 0x10) {
      *(u32 *)(*(int *)(param_1 + 0x1c) + 0x18) =
           *(u32 *)(*(int *)(param_1 + 0x1c) + 0x14);
      *(u32 *)(*(int *)(param_1 + 0x1c) + 0x20) = 0;
      *(byte *)(*(int *)(param_1 + 0x1c) + 0x59) =
           *(byte *)(*(int *)(param_1 + 0x1c) + 0x59) & 0xfe | 1;
      *(u32 *)(*(int *)(param_1 + 0x1c) + 0x20) = 0;
    }
    else {
      *(int *)(*(int *)(param_1 + 0x1c) + 0x18) = *(int *)(*(int *)(param_1 + 0x1c) + 0x18) + 4;
      *(int *)(*(int *)(param_1 + 0x1c) + 0x20) = *(int *)(*(int *)(param_1 + 0x1c) + 0x20) << 1;
      if (lVar8 == 2) {
        *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) = *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) | 1;
      }
    }
    *(byte *)(*(int *)(param_1 + 0x1c) + 0x35) = *(byte *)(*(int *)(param_1 + 0x1c) + 0x35) & 0xef;
    *(u8 *)(*(int *)(param_1 + 0x1c) + 0x34) = 0;
  }
  else if ((*(char *)(*(int *)(param_1 + 0x1c) + 0x34) == '\x02') ||
          (*(char *)(*(int *)(param_1 + 0x1c) + 0x34) == '\x03')) {
    *(u8 *)(*(int *)(param_1 + 0x1c) + 0x34) = 0;
  }
  do {
    while( true ) {
      while( true ) {
        if ((long)((ulong)*(byte *)(param_1 + 0x18) << 0x3a) < 0) {
          return 0;
        }
        if (((ulong)*(byte *)(*(int *)(param_1 + 0x1c) + 0x58) & 0xf) >> 1 == 4) {
          return 0xffffffff;
        }
        pbVar2 = (byte *)*param_2;
        *param_2 = (int)(pbVar2 + 1);
        bVar1 = *pbVar2;
        if (bVar1 < 0x20) break;
        if (bVar1 < 0x90) {
          Expression__7CScriptFUiRPUc(param_1,bVar1,param_2);
        }
        else {
          if (bVar1 < 0xa0) {
            *param_2 = *param_2 + -1;
            return 1;
          }
          bVar9 = bVar1;
          if (0xbb < bVar1) {
            pbVar2 = (byte *)*param_2;
            *param_2 = (int)(pbVar2 + 1);
            bVar9 = *pbVar2;
          }
          pbVar2 = (byte *)*param_2;
          *param_2 = (int)(pbVar2 + 1);
          uVar6 = (uint)*pbVar2;
          *(byte *)(*(int *)(param_1 + 0x1c) + 0x36) = bVar1;
          *(byte *)(*(int *)(param_1 + 0x1c) + 0x37) = bVar9;
          *(uint *)(*(int *)(param_1 + 0x1c) + 0x18) =
               *(int *)(*(int *)(param_1 + 0x1c) + 0x18) + uVar6 * -4;
          *(int *)(*(int *)(param_1 + 0x1c) + 0xc) = *param_2;
          lVar8 = ExecFunc__7CScriptFiii(param_1,bVar1,bVar9,uVar6);
          if (lVar8 < 0) {
            *(int *)(*(int *)(param_1 + 0x1c) + 0x38) = (int)lVar8;
            *(u8 *)(*(int *)(param_1 + 0x1c) + 0x34) = 1;
            return 0xfffffffe;
          }
          if (lVar8 == 0) {
            *(u32 *)(*(int *)(param_1 + 0x1c) + 0x18) =
                 *(u32 *)(*(int *)(param_1 + 0x1c) + 0x14);
            *(u32 *)(*(int *)(param_1 + 0x1c) + 0x20) = 0;
            *(byte *)(*(int *)(param_1 + 0x1c) + 0x59) =
                 *(byte *)(*(int *)(param_1 + 0x1c) + 0x59) & 0xfe | 1;
            *(u32 *)(*(int *)(param_1 + 0x1c) + 0x20) = 0;
          }
          else if (lVar8 == 7) {
            *param_2 = *(int *)(*(int *)(param_1 + 0x1c) + 0xc);
          }
          else if (lVar8 == 0x10) {
            *(u32 *)(*(int *)(param_1 + 0x1c) + 0x18) =
                 *(u32 *)(*(int *)(param_1 + 0x1c) + 0x14);
            *(u32 *)(*(int *)(param_1 + 0x1c) + 0x20) = 0;
            *(byte *)(*(int *)(param_1 + 0x1c) + 0x59) =
                 *(byte *)(*(int *)(param_1 + 0x1c) + 0x59) & 0xfe | 1;
            *(u32 *)(*(int *)(param_1 + 0x1c) + 0x20) = 0;
          }
          else {
            *(int *)(*(int *)(param_1 + 0x1c) + 0x18) =
                 *(int *)(*(int *)(param_1 + 0x1c) + 0x18) + 4;
            *(int *)(*(int *)(param_1 + 0x1c) + 0x20) =
                 *(int *)(*(int *)(param_1 + 0x1c) + 0x20) << 1;
            if (lVar8 == 2) {
              *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) =
                   *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) | 1;
            }
          }
        }
      }
      *(int *)(*(int *)(param_1 + 0x1c) + 0x20) = *(int *)(*(int *)(param_1 + 0x1c) + 0x20) << 1;
      if (bVar1 == 0x1b) {
        iVar7 = EnterUFunc__7CScriptFPUcPUcii
                          (param_1,*param_2 + 3,
                           **(int **)(param_1 + 0x1c) +
                           (uint)*(byte *)*param_2 + (uint)((byte *)*param_2)[1] * 0x100,
                           *(u8 *)(*param_2 + 2),0);
        *param_2 = iVar7;
        return 1;
      }
      if (bVar1 != 0x1a) break;
      bVar1 = ((byte *)*param_2)[1];
      bVar9 = *(byte *)*param_2;
      *param_2 = *param_2 + 2;
      iVar7 = *(int *)(*(int *)(param_1 + 0x1c) + 0x14);
      puVar5 = (u8 *)
               (*(int *)(iVar7 + -4) + (uint)*(ushort *)(iVar7 + -6) * 4 +
               ((uint)bVar9 + (uint)bVar1 * 0x100) * 4);
LAB_00295368:
      puVar4 = *(u32 **)(*(int *)(param_1 + 0x1c) + 0x18);
      *(u32 **)(*(int *)(param_1 + 0x1c) + 0x18) = puVar4 + 1;
      *puVar4 = puVar5;
    }
    if (bVar1 == 0x19) {
      pbVar2 = (byte *)*param_2;
      *param_2 = (int)(pbVar2 + 1);
      iVar7 = *(int *)(*(int *)(param_1 + 0x1c) + 0x14);
      puVar5 = (u8 *)
               ((uint)*pbVar2 + *(int *)(iVar7 + -4) + (uint)*(ushort *)(iVar7 + -6) * 4);
      goto LAB_00295368;
    }
    if (bVar1 == 0x18) {
      puVar5 = (u8 *)
               (*(int *)(*(int *)(param_1 + 0x1c) + 8) +
               (uint)*(byte *)*param_2 + (uint)((byte *)*param_2)[1] * 0x100);
      *param_2 = *param_2 + 2;
      goto LAB_00295368;
    }
    if (bVar1 == 0x16) {
      puVar5 = (u8 *)GetCodePtr__7CScriptFRPUc(param_1,param_2);
      goto LAB_00295368;
    }
    if (bVar1 == 0x15) {
      puVar5 = (u8 *)
               (*(int *)(*(int *)(param_1 + 0x1c) + 4) +
               (uint)*(byte *)*param_2 + (uint)((byte *)*param_2)[1] * 0x100);
      *param_2 = *param_2 + 2;
      goto LAB_00295368;
    }
    if (bVar1 == 0x14) {
      uVar6 = (uint)*(byte *)*param_2 + (uint)((byte *)*param_2)[1] * 0x100;
      *param_2 = *param_2 + 2;
      puVar5 = (u8 *)SafeGetFlagAddr__Fii(uVar6 >> 0xc,uVar6 & 0xfff);
      goto LAB_00295368;
    }
    if (bVar1 == 0x12) {
LAB_00295010:
      puVar3 = (u8 *)*param_2;
      *param_2 = (int)(puVar3 + 1);
      puVar5 = (u8 *)SafeGetFlagAddr__Fii(4,*puVar3);
      goto LAB_00295368;
    }
    if (bVar1 == 0x13) {
      *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) = *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) | 1;
      goto LAB_00295010;
    }
    if (bVar1 == 0x11) {
      puVar3 = (u8 *)*param_2;
      *param_2 = (int)(puVar3 + 1);
      puVar5 = (u8 *)SafeGetFlagAddr__Fii(2,*puVar3);
      goto LAB_00295368;
    }
    if (bVar1 == 0x10) {
      puVar3 = (u8 *)*param_2;
      *param_2 = (int)(puVar3 + 1);
      puVar5 = (u8 *)SafeGetFlagAddr__Fii(0,*puVar3);
      goto LAB_00295368;
    }
    if (bVar1 == 0xf) {
      *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) = *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) | 1;
      pbVar2 = (byte *)*param_2;
      puVar5 = (u8 *)
               ((uint)pbVar2[3] * 0x1000000 +
               (uint)pbVar2[2] * 0x10000 + (uint)*pbVar2 + (uint)pbVar2[1] * 0x100);
      *param_2 = *param_2 + 4;
      goto LAB_00295368;
    }
    if (bVar1 == 0xe) {
      pbVar2 = (byte *)*param_2;
      puVar5 = (u8 *)
               ((uint)pbVar2[3] * 0x1000000 +
               (uint)pbVar2[2] * 0x10000 + (uint)*pbVar2 + (uint)pbVar2[1] * 0x100);
      *param_2 = *param_2 + 4;
      goto LAB_00295368;
    }
    if (bVar1 == 0xd) {
      puVar5 = (u8 *)
               ((uint)*(byte *)*param_2 + (uint)((byte *)*param_2)[1] * 0x100 | 0xffff0000);
      *param_2 = *param_2 + 2;
      goto LAB_00295368;
    }
    if (bVar1 == 0xc) {
      puVar5 = (u8 *)((uint)*(byte *)*param_2 + (uint)((byte *)*param_2)[1] * 0x100);
      *param_2 = *param_2 + 2;
      goto LAB_00295368;
    }
    if (bVar1 == 0xb) {
      pbVar2 = (byte *)*param_2;
      *param_2 = (int)(pbVar2 + 1);
      puVar5 = (u8 *)(*pbVar2 | 0xffffff00);
      goto LAB_00295368;
    }
    if (bVar1 == 10) {
      pbVar2 = (byte *)*param_2;
      *param_2 = (int)(pbVar2 + 1);
      puVar5 = (u8 *)(uint)*pbVar2;
      goto LAB_00295368;
    }
    if (bVar1 == 9) {
      puVar5 = (u8 *)0x4;
      goto LAB_00295368;
    }
    if (bVar1 == 8) {
      puVar5 = (u8 *)0x2;
      goto LAB_00295368;
    }
    if (bVar1 == 7) {
      puVar5 = (u8 *)0x1;
      goto LAB_00295368;
    }
    if (bVar1 == 6) {
      puVar5 = (u8 *)0x0;
      goto LAB_00295368;
    }
    if (bVar1 == 5) {
      puVar5 = (u8 *)0xffffffff;
      goto LAB_00295368;
    }
    if (bVar1 == 4) {
      puVar5 = &NULSTR_1868;
      goto LAB_00295368;
    }
    if (bVar1 == 0x4f) {
      return 0xffffffff;
    }
    if (bVar1 != 1) {
      *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) = *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) >> 1;
      return 1;
    }
    *(u32 *)(*(int *)(param_1 + 0x1c) + 0x18) =
         *(u32 *)(*(int *)(param_1 + 0x1c) + 0x14);
  } while( true );
}

/* ---- 0x002953c0 size 0x190  CScript::EnterUFunc(PUcPUcii)
 *      mangled: EnterUFunc__7CScriptFPUcPUcii */
byte * EnterUFunc__7CScriptFPUcPUcii
                 (int param_1,int param_2,byte *param_3,int param_4,u8 param_5)

{
  u8 *puVar1;
  int iVar2;
  short sVar3;
  u16 uVar4;
  
  iVar2 = (*(int *)(*(int *)(param_1 + 0x1c) + 0x18) + param_4 * -4) -
          *(int *)(*(int *)(param_1 + 0x1c) + 0x14);
  uVar4 = (u16)(iVar2 >> 2);
  if (iVar2 < 0) {
    uVar4 = (u16)(iVar2 + 3 >> 2);
  }
  *(uint *)(*(int *)(param_1 + 0x1c) + 0x18) =
       *(int *)(*(int *)(param_1 + 0x1c) + 0x18) + (uint)*param_3 + (uint)param_3[1] * 0x100;
  puVar1 = *(u8 **)(*(int *)(param_1 + 0x1c) + 0x18);
  *(u16 *)(puVar1 + 6) = uVar4;
  *(u32 *)(puVar1 + 8) = *(u32 *)(*(int *)(param_1 + 0x1c) + 0x14);
  *puVar1 = (char)param_4;
  puVar1[1] = param_5;
  if (param_2 == 0) {
    sVar3 = -1;
  }
  else {
    sVar3 = (short)param_2 - (short)**(u32 **)(param_1 + 0x1c);
  }
  *(short *)(puVar1 + 2) = sVar3;
  iVar2 = *(int *)(*(int *)(param_1 + 0x1c) + 0x18) + 0xc;
  *(int *)(*(int *)(param_1 + 0x1c) + 0x18) = iVar2;
  *(int *)(*(int *)(param_1 + 0x1c) + 0x14) = iVar2;
  return param_3 + 2;
}

/* ---- 0x00295550 size 0x94  CScript::LeaveUFunc(v)
 *      mangled: LeaveUFunc__7CScriptFv */
int LeaveUFunc__7CScriptFv(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(*(int *)(param_1 + 0x1c) + 0x14);
  *(u32 *)(*(int *)(param_1 + 0x1c) + 0x14) = *(u32 *)(iVar1 + -4);
  *(uint *)(*(int *)(param_1 + 0x1c) + 0x18) =
       *(int *)(iVar1 + -4) + (uint)*(ushort *)(iVar1 + -6) * 4;
  if (*(ushort *)(iVar1 + -10) == 0xffff) {
    iVar1 = 0;
  }
  else {
    iVar1 = **(int **)(param_1 + 0x1c) + (uint)*(ushort *)(iVar1 + -10);
  }
  return iVar1;
}

/* ---- 0x002955f0 size 0xa0  SafeGetFlagAddr(ii)
 *      mangled: SafeGetFlagAddr__Fii */
int SafeGetFlagAddr__Fii(u32 param_1,int param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(*(int *)(current__7CScript + 0x1c) + 0x40);
  switch(param_1) {
  case 0:
  case 1:
    iVar1 = iVar1 + param_2;
    break;
  case 2:
  case 3:
    iVar1 = iVar1 + param_2 * 2;
    break;
  case 4:
  case 5:
    iVar1 = iVar1 + param_2 * 4;
    break;
  default:
    iVar1 = 0;
  }
  return iVar1;
}

/* ---- 0x00295690 size 0xc0  ReadDataE(P9_ParStackPvi)
 *      mangled: ReadDataE__FP9_ParStackPvi */
void ReadDataE__FP9_ParStackPvi(int *param_1,char *param_2,int param_3)

{
  short asStack_34 [2];
  int *piStack_30;
  char *pcStack_20;
  int iStack_10;
  
  piStack_30 = param_1;
  pcStack_20 = param_2;
  iStack_10 = param_3;
  if (param_3 == 4) {
    memcpy(param_1,param_2,4);
  }
  else if (param_3 == 2) {
    memcpy(asStack_34,param_2,2);
    *piStack_30 = (int)asStack_34[0];
  }
  else if (param_3 == 1) {
    *param_1 = (int)*param_2;
  }
  return;
}

/* ---- 0x00295750 size 0xec  GetSize(RiRiRPUc)
 *      mangled: GetSize__FRiRiRPUc */
void GetSize__FRiRiRPUc(uint *param_1,uint *param_2,u32 *param_3)

{
  byte *pbVar1;
  uint uVar2;
  
  pbVar1 = (byte *)*param_3;
  *param_3 = pbVar1 + 1;
  *param_1 = (uint)*pbVar1;
  *param_2 = 1;
  if ((*param_1 & 0x80) == 0) {
    *param_1 = 1 << ((int)*param_1 >> 5 & 0x1fU);
  }
  else {
    *param_2 = *param_1 & 0x3f;
    if ((*param_1 & 0x40) != 0) {
      uVar2 = *param_2;
      pbVar1 = (byte *)*param_3;
      *param_3 = pbVar1 + 1;
      *param_2 = uVar2 * 0x100 + (uint)*pbVar1;
    }
    *param_1 = 4;
  }
  return;
}

/* ---- 0x00295840 size 0x1dcc  CScript::Expression(UiRPUc)
 *      mangled: Expression__7CScriptFUiRPUc */
void Expression__7CScriptFUiRPUc(int param_1,uint param_2,int *param_3)

{
  byte bVar1;
  byte *__src;
  void *__dest;
  byte *pbVar2;
  bool bVar3;
  float *pfVar4;
  ulong __n;
  int iVar5;
  int iStack_10c;
  int iStack_108;
  byte *pbStack_104;
  int iStack_100;
  int iStack_fc;
  int iStack_f8;
  int iStack_f4;
  u8 auStack_e4 [4];
  int iStack_e0;
  void *pvStack_dc;
  u8 auStack_d8 [4];
  int iStack_d4;
  void *pvStack_d0;
  u8 auStack_cc [4];
  int iStack_c8;
  void *pvStack_c4;
  int iStack_c0;
  int iStack_bc;
  void *pvStack_b8;
  int iStack_b4;
  int iStack_b0;
  void *pvStack_ac;
  int iStack_a8;
  int iStack_a4;
  void *pvStack_a0;
  int iStack_9c;
  int iStack_98;
  void *pvStack_94;
  int iStack_90;
  int iStack_8c;
  void *pvStack_88;
  int iStack_84;
  int iStack_80;
  void *pvStack_7c;
  int iStack_78;
  int iStack_74;
  byte *pbStack_70;
  int iStack_6c;
  int iStack_68;
  byte *pbStack_64;
  int iStack_60;
  int iStack_5c;
  byte *pbStack_58;
  int iStack_54;
  int iStack_50;
  byte *pbStack_4c;
  int iStack_48;
  int iStack_44;
  byte *pbStack_40;
  byte *pbStack_3c;
  byte *pbStack_38;
  byte bStack_32;
  byte bStack_31;
  int iStack_30;
  uint uStack_20;
  int *piStack_10;
  
  iVar5 = *(int *)(*(int *)(param_1 + 0x1c) + 0x18);
  pfVar4 = (float *)(iVar5 + -4);
  *(float **)(*(int *)(param_1 + 0x1c) + 0x18) = pfVar4;
  __src = (byte *)*pfVar4;
  if (((param_2 < 0x66) || (0x75 < param_2)) && ((param_2 < 0x80 || (0x84 < param_2)))) {
    *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) =
         *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) & 0xfffffffe;
  }
  iStack_30 = param_1;
  if (param_2 == 0x8f) {
    pbStack_38 = (byte *)(*(int *)(iVar5 + -0xc) + *(int *)(iVar5 + -8) * (int)__src);
    pfVar4 = (float *)(iVar5 + -0xc);
    *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) = *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) >> 2;
    *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) =
         *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) & 0xfffffffe;
  }
  else if (param_2 == 0x8e) {
    pbStack_38 = (byte *)(*(int *)(iVar5 + -8) + *(int *)(iVar5 + -0xc) * (int)__src);
    pfVar4 = (float *)(iVar5 + -0xc);
    *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) = *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) >> 2;
    *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) =
         *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) & 0xfffffffe;
  }
  else {
    if (param_2 == 0x8d) {
      *(uint *)(*(int *)(param_1 + 0x1c) + 0x1c) =
           *(int *)(*(int *)(param_1 + 0x1c) + 0x1c) +
           (uint)*(byte *)*param_3 + (uint)((byte *)*param_3)[1] * 0x100;
      *param_3 = *param_3 + 2;
      return;
    }
    pbStack_3c = __src;
    uStack_20 = param_2;
    piStack_10 = param_3;
    if (param_2 == 0x8c) {
      memcpy(*(void **)(*(int *)(param_1 + 0x1c) + 0x1c),(void *)*param_3,(long)(int)__src);
      *(byte **)(*(int *)(iStack_30 + 0x1c) + 0x1c) =
           __src + *(int *)(*(int *)(iStack_30 + 0x1c) + 0x1c);
      *(uint *)(*(int *)(iStack_30 + 0x1c) + 0x20) =
           *(uint *)(*(int *)(iStack_30 + 0x1c) + 0x20) >> 2;
      *piStack_10 = (int)(__src + *piStack_10);
      return;
    }
    if (param_2 == 0x8b) {
      pbVar2 = (byte *)*param_3;
      *param_3 = (int)(pbVar2 + 1);
      bVar1 = *pbVar2;
      __n = (ulong)bVar1;
      if ((bVar1 & 0x80) == 0) {
        memcpy(*(void **)(*(int *)(param_1 + 0x1c) + 0x1c),&pbStack_3c,__n);
      }
      else {
        __n = __n & 0x7f;
        memcpy(*(void **)(*(int *)(param_1 + 0x1c) + 0x1c),__src,__n);
      }
      *(int *)(*(int *)(iStack_30 + 0x1c) + 0x1c) =
           *(int *)(*(int *)(iStack_30 + 0x1c) + 0x1c) + (int)__n;
      *(uint *)(*(int *)(iStack_30 + 0x1c) + 0x20) =
           *(uint *)(*(int *)(iStack_30 + 0x1c) + 0x20) >> 1;
      return;
    }
    if (param_2 == 0x8a) {
      *(byte **)(*(int *)(param_1 + 0x1c) + 0x1c) = __src;
      *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) = *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) >> 1;
      return;
    }
    if (param_2 == 0x89) {
      GetSize__FRiRiRPUc(&iStack_e0,auStack_e4,param_3);
      pfVar4 = (float *)(iVar5 + -8);
      __dest = (void *)*pfVar4;
      ReadDataE__FP9_ParStackPvi(&pbStack_38,__dest,iStack_e0);
      pbStack_38 = (byte *)((uint)pbStack_38 | (uint)pbStack_3c);
      memcpy(__dest,&pbStack_38,(long)iStack_e0);
    }
    else if (param_2 == 0x88) {
      GetSize__FRiRiRPUc(&iStack_d4,auStack_d8,param_3);
      pfVar4 = (float *)(iVar5 + -8);
      pvStack_dc = (void *)*pfVar4;
      ReadDataE__FP9_ParStackPvi(&pbStack_38,pvStack_dc,iStack_d4);
      pbStack_38 = (byte *)((uint)pbStack_38 ^ (uint)pbStack_3c);
      memcpy(pvStack_dc,&pbStack_38,(long)iStack_d4);
    }
    else if (param_2 == 0x87) {
      GetSize__FRiRiRPUc(&iStack_c8,auStack_cc,param_3);
      pfVar4 = (float *)(iVar5 + -8);
      pvStack_d0 = (void *)*pfVar4;
      ReadDataE__FP9_ParStackPvi(&pbStack_38,pvStack_d0,iStack_c8);
      pbStack_38 = (byte *)((uint)pbStack_38 & (uint)pbStack_3c);
      memcpy(pvStack_d0,&pbStack_38,(long)iStack_c8);
    }
    else if (param_2 == 0x86) {
      GetSize__FRiRiRPUc(&iStack_bc,&iStack_c0,param_3);
      pfVar4 = (float *)(iVar5 + -8);
      pvStack_c4 = (void *)*pfVar4;
      iVar5 = iStack_bc;
      if (iStack_bc == 8) {
        iVar5 = 4;
      }
      ReadDataE__FP9_ParStackPvi(&pbStack_38,pvStack_c4,iVar5);
      if (iStack_bc == 8) {
        iStack_bc = 4;
      }
      else {
        pbStack_38 = (byte *)((int)pbStack_38 >> ((int)pbStack_3c * iStack_c0 & 0x1fU));
      }
      memcpy(pvStack_c4,&pbStack_38,(long)iStack_bc);
    }
    else if (param_2 == 0x85) {
      GetSize__FRiRiRPUc(&iStack_b0,&iStack_b4,param_3);
      pfVar4 = (float *)(iVar5 + -8);
      pvStack_b8 = (void *)*pfVar4;
      iVar5 = iStack_b0;
      if (iStack_b0 == 8) {
        iVar5 = 4;
      }
      ReadDataE__FP9_ParStackPvi(&pbStack_38,pvStack_b8,iVar5);
      if (iStack_b0 == 8) {
        iStack_b0 = 4;
      }
      else {
        pbStack_38 = (byte *)((int)pbStack_38 << ((int)pbStack_3c * iStack_b4 & 0x1fU));
      }
      memcpy(pvStack_b8,&pbStack_38,(long)iStack_b0);
    }
    else if (param_2 == 0x84) {
      GetSize__FRiRiRPUc(&iStack_a4,&iStack_a8,param_3);
      pfVar4 = (float *)(iVar5 + -8);
      pvStack_ac = (void *)*pfVar4;
      iVar5 = iStack_a4;
      if (iStack_a4 == 8) {
        iVar5 = 4;
      }
      ReadDataE__FP9_ParStackPvi(&pbStack_38,pvStack_ac,iVar5);
      if (iStack_a4 == 8) {
        pbStack_38 = (byte *)((float)pbStack_38 - (float)pbStack_3c);
        iStack_a4 = 4;
      }
      else {
        pbStack_38 = pbStack_38 + -((int)pbStack_3c * iStack_a8);
      }
      memcpy(pvStack_ac,&pbStack_38,(long)iStack_a4);
    }
    else if (param_2 == 0x83) {
      GetSize__FRiRiRPUc(&iStack_98,&iStack_9c,param_3);
      pfVar4 = (float *)(iVar5 + -8);
      pvStack_a0 = (void *)*pfVar4;
      iVar5 = iStack_98;
      if (iStack_98 == 8) {
        iVar5 = 4;
      }
      ReadDataE__FP9_ParStackPvi(&pbStack_38,pvStack_a0,iVar5);
      if (iStack_98 == 8) {
        pbStack_38 = (byte *)((float)pbStack_38 + (float)pbStack_3c);
        iStack_98 = 4;
      }
      else {
        pbStack_38 = pbStack_38 + (int)pbStack_3c * iStack_9c;
      }
      memcpy(pvStack_a0,&pbStack_38,(long)iStack_98);
    }
    else if (param_2 == 0x82) {
      GetSize__FRiRiRPUc(&iStack_8c,&iStack_90,param_3);
      pfVar4 = (float *)(iVar5 + -8);
      pvStack_94 = (void *)*pfVar4;
      iVar5 = iStack_8c;
      if (iStack_8c == 8) {
        iVar5 = 4;
      }
      ReadDataE__FP9_ParStackPvi(&pbStack_38,pvStack_94,iVar5);
      if (iStack_8c == 8) {
        iStack_8c = 4;
      }
      else {
        pbStack_38 = (byte *)((int)pbStack_38 % ((int)pbStack_3c * iStack_90));
        if ((int)pbStack_3c * iStack_90 == 0) {
          trap(7);
        }
      }
      memcpy(pvStack_94,&pbStack_38,(long)iStack_8c);
    }
    else if (param_2 == 0x81) {
      GetSize__FRiRiRPUc(&iStack_80,&iStack_84,param_3);
      pfVar4 = (float *)(iVar5 + -8);
      pvStack_88 = (void *)*pfVar4;
      if (iStack_80 == 8) {
        iStack_10c = 4;
      }
      else {
        iStack_10c = iStack_80;
      }
      ReadDataE__FP9_ParStackPvi(&pbStack_38,pvStack_88,iStack_10c);
      if (iStack_80 == 8) {
        pbStack_38 = (byte *)((float)pbStack_38 / (float)pbStack_3c);
        iStack_80 = 4;
      }
      else {
        pbStack_38 = (byte *)((int)pbStack_38 / ((int)pbStack_3c * iStack_84));
        if ((int)pbStack_3c * iStack_84 == 0) {
          trap(7);
        }
      }
      memcpy(pvStack_88,&pbStack_38,(long)iStack_80);
    }
    else if (param_2 == 0x80) {
      GetSize__FRiRiRPUc(&iStack_74,&iStack_78,param_3);
      pfVar4 = (float *)(iVar5 + -8);
      pvStack_7c = (void *)*pfVar4;
      if (iStack_74 == 8) {
        iStack_108 = 4;
      }
      else {
        iStack_108 = iStack_74;
      }
      ReadDataE__FP9_ParStackPvi(&pbStack_38,pvStack_7c,iStack_108);
      if (iStack_74 == 8) {
        pbStack_38 = (byte *)((float)pbStack_38 * (float)pbStack_3c);
        iStack_74 = 4;
      }
      else {
        pbStack_38 = pbStack_38 + (int)pbStack_3c * iStack_78;
      }
      memcpy(pvStack_7c,&pbStack_38,(long)iStack_74);
    }
    else if (param_2 == 0x7a) {
      bStack_32 = 1;
      pfVar4 = (float *)(iVar5 + -8);
      if ((*pfVar4 == 0.0) && (__src == (byte *)0x0)) {
        bStack_32 = 0;
      }
      pbStack_38 = (byte *)(uint)bStack_32;
    }
    else if (param_2 == 0x79) {
      bStack_31 = 0;
      pfVar4 = (float *)(iVar5 + -8);
      if ((*pfVar4 != 0.0) && (__src != (byte *)0x0)) {
        bStack_31 = 1;
      }
      pbStack_38 = (byte *)(uint)bStack_31;
    }
    else if (param_2 == 0x78) {
      pfVar4 = (float *)(iVar5 + -8);
      pbStack_38 = (byte *)((uint)*pfVar4 | (uint)__src);
    }
    else if (param_2 == 0x77) {
      pfVar4 = (float *)(iVar5 + -8);
      pbStack_38 = (byte *)((uint)*pfVar4 ^ (uint)__src);
    }
    else if (param_2 == 0x76) {
      pfVar4 = (float *)(iVar5 + -8);
      pbStack_38 = (byte *)((uint)*pfVar4 & (uint)__src);
    }
    else if (param_2 == 0x75) {
      pfVar4 = (float *)(iVar5 + -8);
      if ((*(uint *)(*(int *)(param_1 + 0x1c) + 0x20) & 3) == 0) {
        bVar3 = (byte *)*pfVar4 != __src;
      }
      else {
        bVar3 = *pfVar4 != (float)__src;
      }
      pbStack_38 = (byte *)(uint)bVar3;
      *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) = *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) >> 1;
      *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) =
           *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) & 0xfffffffe;
    }
    else if (param_2 == 0x74) {
      pfVar4 = (float *)(iVar5 + -8);
      if ((*(uint *)(*(int *)(param_1 + 0x1c) + 0x20) & 3) == 0) {
        bVar3 = (byte *)*pfVar4 == __src;
      }
      else {
        bVar3 = *pfVar4 == (float)__src;
      }
      pbStack_38 = (byte *)(uint)bVar3;
      *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) = *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) >> 1;
      *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) =
           *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) & 0xfffffffe;
    }
    else if (param_2 == 0x73) {
      pfVar4 = (float *)(iVar5 + -8);
      if ((*(uint *)(*(int *)(param_1 + 0x1c) + 0x20) & 3) == 0) {
        pbStack_38 = (byte *)((int)*pfVar4 < (int)__src ^ 1);
      }
      else {
        pbStack_38 = (byte *)(uint)((float)__src <= *pfVar4);
      }
      *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) = *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) >> 1;
      *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) =
           *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) & 0xfffffffe;
    }
    else if (param_2 == 0x72) {
      pfVar4 = (float *)(iVar5 + -8);
      if ((*(uint *)(*(int *)(param_1 + 0x1c) + 0x20) & 3) == 0) {
        pbStack_38 = (byte *)((int)__src < (int)*pfVar4 ^ 1);
      }
      else {
        pbStack_38 = (byte *)(uint)(*pfVar4 <= (float)__src);
      }
      *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) = *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) >> 1;
      *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) =
           *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) & 0xfffffffe;
    }
    else if (param_2 == 0x71) {
      pfVar4 = (float *)(iVar5 + -8);
      if ((*(uint *)(*(int *)(param_1 + 0x1c) + 0x20) & 3) == 0) {
        bVar3 = (int)__src < (int)*pfVar4;
      }
      else {
        bVar3 = (float)__src < *pfVar4;
      }
      pbStack_38 = (byte *)(uint)bVar3;
      *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) = *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) >> 1;
      *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) =
           *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) & 0xfffffffe;
    }
    else if (param_2 == 0x70) {
      pfVar4 = (float *)(iVar5 + -8);
      if ((*(uint *)(*(int *)(param_1 + 0x1c) + 0x20) & 3) == 0) {
        bVar3 = (int)*pfVar4 < (int)__src;
      }
      else {
        bVar3 = *pfVar4 < (float)__src;
      }
      pbStack_38 = (byte *)(uint)bVar3;
      *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) = *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) >> 1;
      *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) =
           *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) & 0xfffffffe;
    }
    else if (param_2 == 0x6d) {
      pfVar4 = (float *)(iVar5 + -8);
      pbStack_38 = (byte *)((int)*pfVar4 >> ((uint)__src & 0x1f));
      *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) = *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) >> 1;
      *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) =
           *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) & 0xfffffffe;
    }
    else if (param_2 == 0x6c) {
      pfVar4 = (float *)(iVar5 + -8);
      pbStack_38 = (byte *)((int)*pfVar4 << ((uint)__src & 0x1f));
      *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) = *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) >> 1;
      *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) =
           *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) & 0xfffffffe;
    }
    else if (param_2 == 0x6b) {
      pfVar4 = (float *)(iVar5 + -8);
      if ((*(uint *)(*(int *)(param_1 + 0x1c) + 0x20) & 3) == 0) {
        pbStack_38 = (byte *)((int)*pfVar4 - (int)__src);
        *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) = *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) >> 1
        ;
        *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) =
             *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) & 0xfffffffe;
      }
      else {
        pbStack_38 = (byte *)(*pfVar4 - (float)__src);
        *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) = *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) >> 1
        ;
        *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) = *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) | 1;
      }
    }
    else if (param_2 == 0x6a) {
      pfVar4 = (float *)(iVar5 + -8);
      if ((*(uint *)(*(int *)(param_1 + 0x1c) + 0x20) & 3) == 0) {
        pbStack_38 = __src + (int)*pfVar4;
        *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) = *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) >> 1
        ;
        *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) =
             *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) & 0xfffffffe;
      }
      else {
        pbStack_38 = (byte *)(*pfVar4 + (float)__src);
        *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) = *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) >> 1
        ;
        *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) = *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) | 1;
      }
    }
    else if (param_2 == 0x69) {
      pfVar4 = (float *)(iVar5 + -8);
      pbStack_38 = (byte *)((int)*pfVar4 % (int)__src);
      if (__src == (byte *)0x0) {
        trap(7);
      }
      *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) = *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) >> 1;
      *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) =
           *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) & 0xfffffffe;
    }
    else if (param_2 == 0x68) {
      pfVar4 = (float *)(iVar5 + -8);
      if ((*(uint *)(*(int *)(param_1 + 0x1c) + 0x20) & 3) == 0) {
        pbStack_38 = (byte *)((int)*pfVar4 / (int)__src);
        if (__src == (byte *)0x0) {
          trap(7);
        }
        *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) = *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) >> 1
        ;
        *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) =
             *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) & 0xfffffffe;
      }
      else {
        pbStack_38 = (byte *)(*pfVar4 / (float)__src);
        *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) = *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) >> 1
        ;
        *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) = *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) | 1;
      }
    }
    else if (param_2 == 0x67) {
      pfVar4 = (float *)(iVar5 + -8);
      if ((*(uint *)(*(int *)(param_1 + 0x1c) + 0x20) & 3) == 0) {
        pbStack_38 = (byte *)((int)*pfVar4 * (int)__src);
        *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) = *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) >> 1
        ;
        *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) =
             *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) & 0xfffffffe;
      }
      else {
        pbStack_38 = (byte *)(*pfVar4 * (float)__src);
        *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) = *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) >> 1
        ;
        *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) = *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) | 1;
      }
    }
    else if (param_2 == 0x66) {
      if ((*(uint *)(*(int *)(param_1 + 0x1c) + 0x20) & 1) == 0) {
        pbStack_38 = (byte *)-(int)__src;
      }
      else {
        pbStack_38 = (byte *)-(float)__src;
      }
    }
    else if (param_2 == 0x65) {
      pbStack_38 = (byte *)~(uint)__src;
    }
    else if (param_2 == 100) {
      pbStack_104 = (byte *)(uint)(__src == (byte *)0x0);
      pbStack_38 = pbStack_104;
    }
    else if (param_2 == 99) {
      GetSize__FRiRiRPUc(&iStack_68,&iStack_6c,param_3);
      pbStack_70 = pbStack_3c;
      if (iStack_68 == 8) {
        iStack_100 = 4;
      }
      else {
        iStack_100 = iStack_68;
      }
      ReadDataE__FP9_ParStackPvi(&pbStack_40,pbStack_3c,iStack_100);
      pbStack_38 = pbStack_40;
      if (iStack_68 == 8) {
        pbStack_40 = (byte *)((float)pbStack_40 - 1.0);
        iStack_68 = 4;
      }
      else {
        pbStack_40 = pbStack_40 + -iStack_6c;
      }
      memcpy(pbStack_70,&pbStack_40,(long)iStack_68);
    }
    else if (param_2 == 0x62) {
      GetSize__FRiRiRPUc(&iStack_5c,&iStack_60,param_3);
      pbStack_64 = pbStack_3c;
      if (iStack_5c == 8) {
        iStack_fc = 4;
      }
      else {
        iStack_fc = iStack_5c;
      }
      ReadDataE__FP9_ParStackPvi(&pbStack_40,pbStack_3c,iStack_fc);
      pbStack_38 = pbStack_40;
      if (iStack_5c == 8) {
        pbStack_40 = (byte *)((float)pbStack_40 + 1.0);
        iStack_5c = 4;
      }
      else {
        pbStack_40 = pbStack_40 + iStack_60;
      }
      memcpy(pbStack_64,&pbStack_40,(long)iStack_5c);
    }
    else if (param_2 == 0x61) {
      GetSize__FRiRiRPUc(&iStack_50,&iStack_54,param_3);
      pbStack_58 = pbStack_3c;
      if (iStack_50 == 8) {
        iStack_f8 = 4;
      }
      else {
        iStack_f8 = iStack_50;
      }
      ReadDataE__FP9_ParStackPvi(&pbStack_38,pbStack_3c,iStack_f8);
      if (iStack_50 == 8) {
        pbStack_38 = (byte *)((float)pbStack_38 - 1.0);
        iStack_50 = 4;
      }
      else {
        pbStack_38 = pbStack_38 + -iStack_54;
      }
      memcpy(pbStack_58,&pbStack_38,(long)iStack_50);
    }
    else if (param_2 == 0x60) {
      GetSize__FRiRiRPUc(&iStack_44,&iStack_48,param_3);
      pbStack_4c = pbStack_3c;
      if (iStack_44 == 8) {
        iStack_f4 = 4;
      }
      else {
        iStack_f4 = iStack_44;
      }
      ReadDataE__FP9_ParStackPvi(&pbStack_38,pbStack_3c,iStack_f4);
      if (iStack_44 == 8) {
        pbStack_38 = (byte *)((float)pbStack_38 + 1.0);
        iStack_44 = 4;
      }
      else {
        pbStack_38 = pbStack_38 + iStack_48;
      }
      memcpy(pbStack_4c,&pbStack_38,(long)iStack_44);
    }
    else {
      if (param_2 == 0x48) {
        return;
      }
      if (param_2 == 0x47) {
        *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) = *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) | 1;
        return;
      }
      if (param_2 == 0x46) {
        *(float *)(iVar5 + -8) = (float)*(int *)(iVar5 + -8);
        *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) = *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) | 2;
        return;
      }
      if (param_2 == 0x45) {
        pbStack_38 = (byte *)(float)(int)__src;
        *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) = *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) | 1;
      }
      else if (param_2 == 0x44) {
        pbStack_38 = (byte *)(int)(float)__src;
      }
      else {
        pbStack_3c._0_2_ = (short)__src;
        if (param_2 == 0x43) {
          pbStack_38 = (byte *)((uint)__src & 0xffff);
        }
        else if (param_2 == 0x42) {
          pbStack_38 = (byte *)(int)(short)pbStack_3c;
        }
        else {
          pbStack_3c._0_1_ = (char)__src;
          if (param_2 == 0x41) {
            pbStack_38 = (byte *)((uint)__src & 0xff);
          }
          else if (param_2 == 0x40) {
            pbStack_38 = (byte *)(int)(char)pbStack_3c;
          }
          else if (param_2 == 0x2f) {
            iVar5 = *(int *)(*(int *)(param_1 + 0x1c) + 0x14);
            pbStack_38 = __src + *(int *)(iVar5 + -4) + (uint)*(ushort *)(iVar5 + -6) * 4;
          }
          else if ((param_2 == 0x2d) || (param_2 == 0x2e)) {
            pbStack_38 = (byte *)(*(int *)(*(int *)(param_1 + 0x1c) + 0x40) + (int)__src * 4);
          }
          else if (param_2 == 0x2c) {
            pbStack_38 = (byte *)(*(int *)(*(int *)(param_1 + 0x1c) + 0x40) + (int)__src * 2);
          }
          else if (param_2 == 0x2b) {
            pbStack_38 = __src + *(int *)(*(int *)(param_1 + 0x1c) + 0x40);
          }
          else if (param_2 == 0x2a) {
            pbStack_38 = __src + *(int *)(*(int *)(param_1 + 0x1c) + 4);
          }
          else if (param_2 == 0x29) {
            pbStack_38 = __src + **(int **)(param_1 + 0x1c);
          }
          else if (param_2 == 0x28) {
            pfVar4 = (float *)(iVar5 + -8);
            memcpy((void *)*pfVar4,&pbStack_3c,4);
            pbStack_38 = pbStack_3c;
          }
          else if (param_2 == 0x27) {
            pfVar4 = (float *)(iVar5 + -8);
            memcpy((void *)*pfVar4,&pbStack_3c,2);
            pbStack_38 = (byte *)(int)(short)pbStack_3c;
          }
          else if (param_2 == 0x26) {
            pfVar4 = (float *)(iVar5 + -8);
            *(char *)*pfVar4 = (char)pbStack_3c;
            pbStack_38 = (byte *)(int)(char)pbStack_3c;
          }
          else {
            if (param_2 != 0x24) {
              if (param_2 != 0x25) {
                if (param_2 == 0x23) {
                  memcpy(&pbStack_40,__src,2);
                  pbStack_38 = (byte *)((uint)pbStack_40 & 0xffff);
                }
                else if (param_2 == 0x22) {
                  memcpy(&pbStack_40,__src,2);
                  pbStack_38 = (byte *)(int)(short)pbStack_40;
                }
                else if (param_2 == 0x21) {
                  pbStack_38 = (byte *)(uint)*__src;
                }
                else if (param_2 == 0x20) {
                  pbStack_38 = (byte *)(int)(char)*__src;
                }
                goto LAB_002975c0;
              }
              *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) =
                   *(uint *)(*(int *)(param_1 + 0x1c) + 0x20) | 1;
            }
            memcpy(&pbStack_40,__src,4);
            pbStack_38 = pbStack_40;
          }
        }
      }
    }
  }
LAB_002975c0:
  *pfVar4 = (float)pbStack_38;
  *(float **)(*(int *)(iStack_30 + 0x1c) + 0x18) = pfVar4 + 1;
  return;
}

/* ---- 0x00297610 size 0x280  CScript::ExecFunc(iii)
 *      mangled: ExecFunc__7CScriptFiii */
u64 ExecFunc__7CScriptFiii(int param_1,int param_2,u32 param_3,u32 param_4)

{
  u64 uVar1;
  
  if (param_2 < 0xbc) {
    switch(param_2) {
    case 0xa0:
      uVar1 = ifc_chain__7CScriptFP9_ParStack
                        (param_1,*(u32 *)(*(int *)(param_1 + 0x1c) + 0x18));
      break;
    case 0xa1:
      uVar1 = ifc_callEvent__7CScriptFiP9_ParStack
                        (param_1,param_4,*(u32 *)(*(int *)(param_1 + 0x1c) + 0x18));
      break;
    case 0xa2:
      uVar1 = ifc_callEventDly__7CScriptFiP9_ParStack
                        (param_1,param_4,*(u32 *)(*(int *)(param_1 + 0x1c) + 0x18));
      break;
    case 0xa3:
      uVar1 = ifc_getSysInfo__7CScriptFP9_ParStack
                        (param_1,*(u32 *)(*(int *)(param_1 + 0x1c) + 0x18));
      break;
    case 0xa4:
      uVar1 = ifc_setFlag__7CScriptFP9_ParStack
                        (param_1,*(u32 *)(*(int *)(param_1 + 0x1c) + 0x18));
      break;
    case 0xa5:
      uVar1 = ifc_clrFlag__7CScriptFP9_ParStack
                        (param_1,*(u32 *)(*(int *)(param_1 + 0x1c) + 0x18));
      break;
    case 0xa6:
      uVar1 = ifc_chkFlag__7CScriptFP9_ParStack
                        (param_1,*(u32 *)(*(int *)(param_1 + 0x1c) + 0x18));
      break;
    case 0xa7:
      uVar1 = ifc_reg_clr__7CScriptFP9_ParStack
                        (param_1,*(u32 *)(*(int *)(param_1 + 0x1c) + 0x18));
      break;
    default:
      uVar1 = 0x10;
      break;
    case 0xaa:
      uVar1 = ifc_wait__7CScriptFiP9_ParStack
                        (param_1,param_4,*(u32 *)(*(int *)(param_1 + 0x1c) + 0x18));
      break;
    case 0xab:
      uVar1 = ifc_sprintf__7CScriptFiP9_ParStack
                        (param_1,param_4,*(u32 *)(*(int *)(param_1 + 0x1c) + 0x18));
      break;
    case 0xac:
      uVar1 = ifc_get_pad__7CScriptFP9_ParStack
                        (param_1,*(u32 *)(*(int *)(param_1 + 0x1c) + 0x18));
      break;
    case 0xad:
      uVar1 = ifc_randomize__Fv();
      break;
    case 0xae:
      uVar1 = ifc_rnd__7CScriptFP9_ParStack
                        (param_1,*(u32 *)(*(int *)(param_1 + 0x1c) + 0x18));
      break;
    case 0xaf:
      uVar1 = ifc_dprintf__7CScriptFiP9_ParStack
                        (param_1,param_4,*(u32 *)(*(int *)(param_1 + 0x1c) + 0x18));
    }
  }
  else {
    uVar1 = CallFunc__9CScriptExFiiiP9_ParStack
                      (*(u32 *)(param_1 + 0x20),param_2,param_3,param_4,
                       *(u32 *)(*(int *)(param_1 + 0x1c) + 0x18));
  }
  return uVar1;
}

/* ---- 0x00297890 size 0x98  CScript::ifc_chain(P9_ParStack)
 *      mangled: ifc_chain__7CScriptFP9_ParStack */
u64 ifc_chain__7CScriptFP9_ParStack(int param_1,u32 *param_2)

{
  EndScene__7CScriptFv(current__7CScript);
  strcpy((char *)(*(int *)(current__7CScript + 0x1c) + 0x68),(char *)*param_2);
  *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfb | 4;
  *(byte *)(*(int *)(param_1 + 0x1c) + 0x58) =
       *(byte *)(*(int *)(param_1 + 0x1c) + 0x58) & 0x3f | 0x40;
  return 0;
}

/* ---- 0x00297930 size 0xb8  CScript::ifc_callEvent(iP9_ParStack)
 *      mangled: ifc_callEvent__7CScriptFiP9_ParStack */
u32 ifc_callEvent__7CScriptFiP9_ParStack(int param_1,int param_2,u32 *param_3)

{
  u32 uVar1;
  u8 auStack_b0 [128];
  int iStack_30;
  int iStack_20;
  u32 *puStack_10;
  
  uVar1 = *param_3;
  *param_3 = param_3;
  *(int *)(*(int *)(param_1 + 0x1c) + 0x18) = *(int *)(*(int *)(param_1 + 0x1c) + 0x18) + 4;
  iStack_30 = param_1;
  iStack_20 = param_2;
  puStack_10 = param_3;
  if (1 < param_2) {
    memcpy(auStack_b0,param_3 + 1,(long)((param_2 + -1) * 4));
  }
  CallEvent__7CScriptFUiiP9_ParStackPi(iStack_30,uVar1,iStack_20 + -1,auStack_b0,puStack_10);
  return 7;
}

/* ---- 0x002979f0 size 0xa8  CScript::ifc_callEventDly(iP9_ParStack)
 *      mangled: ifc_callEventDly__7CScriptFiP9_ParStack */
u64
ifc_callEventDly__7CScriptFiP9_ParStack(u32 param_1,int param_2,u32 *param_3)

{
  u32 uVar1;
  long lVar2;
  int iVar3;
  
  param_2 = param_2 + -2;
  lVar2 = GetDlyEvent__7CScriptFi(param_1,param_2);
  if (lVar2 != 0) {
    iVar3 = (int)lVar2;
    *(u32 *)(iVar3 + 0xc) = *param_3;
    *(u32 *)(iVar3 + 4) = param_3[1];
    uVar1 = GetTimer__7SysToolFv();
    *(u32 *)(iVar3 + 8) = uVar1;
    if (param_2 != 0) {
      memcpy((void *)(iVar3 + 0x10),param_3 + 2,(long)(param_2 * 4));
    }
  }
  return 0;
}

/* ---- 0x00297aa0 size 0x40  CScript::ifc_getSysInfo(P9_ParStack)
 *      mangled: ifc_getSysInfo__7CScriptFP9_ParStack */
u32 ifc_getSysInfo__7CScriptFP9_ParStack(u32 param_1,u32 *param_2)

{
  u32 uVar1;
  
  uVar1 = GetSysInfo__7CScriptFi(param_1,*param_2);
  *param_2 = uVar1;
  return 1;
}

/* ---- 0x00297ae0 size 0x14  CScript::GetSysInfo(i)
 *      mangled: GetSysInfo__7CScriptFi */
u64 GetSysInfo__7CScriptFi(void)

{
  return 0;
}

/* ---- 0x00297b00 size 0x94  CScript::ifc_setFlag(P9_ParStack)
 *      mangled: ifc_setFlag__7CScriptFP9_ParStack */
u64 ifc_setFlag__7CScriptFP9_ParStack(int param_1,uint *param_2)

{
  int iVar1;
  uint *puVar2;
  
  if (current__7CScript == 0) {
    iVar1 = *(int *)(param_1 + 0x1c);
  }
  else {
    iVar1 = *(int *)(current__7CScript + 0x1c);
  }
  puVar2 = (uint *)(*(int *)(iVar1 + 0x40) + ((int)*param_2 >> 5) * 4);
  *puVar2 = *puVar2 | 1 << (*param_2 & 0x1f);
  return 0;
}

/* ---- 0x00297ba0 size 0x98  CScript::ifc_clrFlag(P9_ParStack)
 *      mangled: ifc_clrFlag__7CScriptFP9_ParStack */
u64 ifc_clrFlag__7CScriptFP9_ParStack(int param_1,uint *param_2)

{
  int iVar1;
  uint *puVar2;
  
  if (current__7CScript == 0) {
    iVar1 = *(int *)(param_1 + 0x1c);
  }
  else {
    iVar1 = *(int *)(current__7CScript + 0x1c);
  }
  puVar2 = (uint *)(*(int *)(iVar1 + 0x40) + ((int)*param_2 >> 5) * 4);
  *puVar2 = *puVar2 & ~(1 << (*param_2 & 0x1f));
  return 0;
}

/* ---- 0x00297c40 size 0x94  CScript::ifc_chkFlag(P9_ParStack)
 *      mangled: ifc_chkFlag__7CScriptFP9_ParStack */
u32 ifc_chkFlag__7CScriptFP9_ParStack(int param_1,uint *param_2)

{
  int iVar1;
  
  if (current__7CScript == 0) {
    iVar1 = *(int *)(param_1 + 0x1c);
  }
  else {
    iVar1 = *(int *)(current__7CScript + 0x1c);
  }
  *param_2 = *(uint *)(*(int *)(iVar1 + 0x40) + ((int)*param_2 >> 5) * 4) >> (*param_2 & 0x1f) & 1;
  return 1;
}

/* ---- 0x00297ce0 size 0x124  CScript::ifc_reg_clr(P9_ParStack)
 *      mangled: ifc_reg_clr__7CScriptFP9_ParStack */
u64 ifc_reg_clr__7CScriptFP9_ParStack(int param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *__s;
  int iVar4;
  
  iVar2 = *param_2;
  iVar3 = param_2[1];
  iVar1 = param_2[2];
  if (current__7CScript == 0) {
    iVar4 = *(int *)(param_1 + 0x1c);
  }
  else {
    iVar4 = *(int *)(current__7CScript + 0x1c);
  }
  if ((int)(uint)*(ushort *)(iVar4 + 0x52) <= iVar3) {
    iVar3 = *(ushort *)(iVar4 + 0x52) - 1;
  }
  if (iVar2 < 0) {
    iVar2 = 0;
  }
  __s = (int *)(*(int *)(iVar4 + 0x40) + iVar2 * 4);
  if (iVar1 == 0) {
    memset(__s,0,(long)(((iVar3 - iVar2) + 1) * 4));
  }
  else {
    for (; iVar2 <= iVar3; iVar2 = iVar2 + 1) {
      *__s = iVar1;
      __s = __s + 1;
    }
  }
  return 0;
}

/* ---- 0x00297e10 size 0x1b0  CScript::ifc_wait(iP9_ParStack)
 *      mangled: ifc_wait__7CScriptFiP9_ParStack */
int ifc_wait__7CScriptFiP9_ParStack(int param_1,int param_2,int *param_3)

{
  u32 uVar1;
  int iVar2;
  u32 uStack_38;
  
  if (param_2 < 0) {
    iVar2 = GetTimer__7SysToolFv();
    if (-param_2 <= iVar2 - *(int *)(*(int *)(param_1 + 0x1c) + 0x3c)) {
      param_2 = 0;
    }
  }
  else {
    param_2 = *param_3;
    if (param_2 < 0) {
      if (DAT_00412e11 == '\x02') {
        uStack_38 = 60.0;
      }
      else {
        uStack_38 = 50.0;
      }
      param_2 = (int)((float)(param_2 * -1000) / (uStack_38 / (float)m_syncCount__3Gsx));
    }
    if (param_2 < 1) {
      param_2 = 0;
    }
    else {
      uVar1 = GetTimer__7SysToolFv();
      *(u32 *)(*(int *)(param_1 + 0x1c) + 0x3c) = uVar1;
      param_2 = -param_2;
    }
  }
  return param_2;
}

/* ---- 0x00297fc0 size 0xd8  CScript::ifc_get_pad(P9_ParStack)
 *      mangled: ifc_get_pad__7CScriptFP9_ParStack */
u32 ifc_get_pad__7CScriptFP9_ParStack(u64 param_1,uint *param_2)

{
  char cVar1;
  uint uVar2;
  
  uVar2 = (uint)(ushort)param_2[1];
  cVar1 = (char)*param_2;
  if ((cVar1 == '\x04') || (cVar1 == '\x03')) {
    bPadF__7CScript = bPadF__7CScript | uVar2;
    bPadS__7CScript = bPadS__7CScript & ~uVar2;
    bPadD__7CScript = bPadD__7CScript & ~uVar2;
    uVar2 = bPadR__7CScript;
  }
  else {
    uVar2 = bPadD__7CScript;
    if ((cVar1 != '\x02') && (uVar2 = bPadS__7CScript, cVar1 != '\x01')) {
      uVar2 = bPadR__7CScript;
    }
  }
  *param_2 = uVar2;
  return 1;
}

/* ---- 0x002980a0 size 0x24  ifc_randomize(v)
 *      mangled: ifc_randomize__Fv */
u64 ifc_randomize__Fv(void)

{
  ipRandomize__Fv();
  return 0;
}

/* ---- 0x002980d0 size 0x74  CScript::ifc_rnd(P9_ParStack)
 *      mangled: ifc_rnd__7CScriptFP9_ParStack */
u32 ifc_rnd__7CScriptFP9_ParStack(u64 param_1,int *param_2)

{
  int iVar1;
  
  if (*param_2 == 0) {
    iVar1 = ipMakeRand__Fv();
  }
  else {
    iVar1 = iprnd__Fi(*param_2);
  }
  *param_2 = iVar1;
  return 1;
}

/* ---- 0x00298150 size 0x14  CScript::ifc_dprintf(iP9_ParStack)
 *      mangled: ifc_dprintf__7CScriptFiP9_ParStack */
u64 ifc_dprintf__7CScriptFiP9_ParStack(void)

{
  return 0;
}

/* ---- 0x00298170 size 0x60  CScript::ifc_sprintf(iP9_ParStack)
 *      mangled: ifc_sprintf__7CScriptFiP9_ParStack */
u64 ifc_sprintf__7CScriptFiP9_ParStack(u32 param_1,int param_2,u32 *param_3)

{
  ifc_xprintf__7CScriptFPcPciP9_ParStack(param_1,*param_3,param_3[1],param_2 + -2,param_3 + 2);
  return 0;
}

/* ---- 0x002981d0 size 0x1c0  CScript::ifc_xprintf(PcPciP9_ParStack)
 *      mangled: ifc_xprintf__7CScriptFPcPciP9_ParStack */
/* WARNING: Function: fptodp replaced with injection: fptodp */

void ifc_xprintf__7CScriptFPcPciP9_ParStack
               (u64 param_1,char *param_2,char *param_3,int param_4,int param_5)

{
  char cVar1;
  bool bVar2;
  size_t sVar3;
  char *pcVar4;
  char *pcVar5;
  int iVar6;
  char acStack_150 [272];
  char *pcStack_40;
  char *pcStack_30;
  int iStack_20;
  int iStack_10;
  
  iVar6 = 0;
  bVar2 = false;
  pcVar5 = acStack_150;
  pcStack_40 = param_2;
  pcStack_30 = param_3;
  iStack_20 = param_4;
  iStack_10 = param_5;
  while( true ) {
    cVar1 = *pcStack_30;
    if (cVar1 == '\0') break;
    pcVar4 = pcVar5 + 1;
    pcStack_30 = pcStack_30 + 1;
    *pcVar5 = cVar1;
    pcVar5 = pcVar4;
    if (bVar2) {
      if ((((cVar1 == 'd') || (cVar1 == 'x')) || (cVar1 == 'X')) ||
         (((cVar1 == 'c' || (cVar1 == 's')) || (cVar1 == 'f')))) {
        *pcVar4 = '\0';
        if (cVar1 == 'f') {
          sprintf(pcStack_40,acStack_150,(double)*(float *)(iStack_10 + iVar6 * 4));
        }
        else {
          sprintf(pcStack_40,acStack_150,*(u32 *)(iStack_10 + iVar6 * 4));
        }
        sVar3 = strlen(pcStack_40);
        pcStack_40 = pcStack_40 + (int)sVar3;
        if (iVar6 < iStack_20) {
          iVar6 = iVar6 + 1;
        }
        bVar2 = false;
        pcVar5 = acStack_150;
      }
    }
    else if (cVar1 == '%') {
      bVar2 = true;
    }
  }
  pcStack_30 = pcStack_30 + 1;
  *pcVar5 = '\0';
  if (pcVar5 != acStack_150) {
    strcpy(pcStack_40,acStack_150);
  }
  return;
}

/* ---- 0x00298390 size 0x4c  CScript::CallEvent(UiiP9_ParStackPi)
 *      mangled: CallEvent__7CScriptFUiiP9_ParStackPi */
void CallEvent__7CScriptFUiiP9_ParStackPi
               (u32 param_1,u32 param_2,u32 param_3,u32 param_4,
               u32 param_5)

{
  CallEventA__7CScriptFiUiiP9_ParStackPi(param_1,0,param_2,param_3,param_4,param_5);
  return;
}

/* ---- 0x002983e0 size 0x4c  CScript::CallEventT(UiiP9_ParStackPi)
 *      mangled: CallEventT__7CScriptFUiiP9_ParStackPi */
void CallEventT__7CScriptFUiiP9_ParStackPi
               (u32 param_1,u32 param_2,u32 param_3,u32 param_4,
               u32 param_5)

{
  CallEventA__7CScriptFiUiiP9_ParStackPi(param_1,1,param_2,param_3,param_4,param_5);
  return;
}

/* ---- 0x00298430 size 0x1e0  CScript::CallEventA(iUiiP9_ParStackPi)
 *      mangled: CallEventA__7CScriptFiUiiP9_ParStackPi */
u32
CallEventA__7CScriptFiUiiP9_ParStackPi
          (int param_1,uint param_2,int param_3,int param_4,void *param_5,int param_6)

{
  u32 uVar1;
  int *piVar2;
  int *piVar3;
  int iVar4;
  
  if (*(int *)(*(int *)(param_1 + 0x1c) + 0x24) != 0) {
    for (piVar2 = *(int **)(*(int *)(param_1 + 0x1c) + 0x24); *piVar2 == 0x544e5645;
        piVar2 = piVar2 + (uint)*(ushort *)((int)piVar2 + 6) * 4) {
      if (*(ushort *)(piVar2 + 2) == param_2) {
        piVar3 = (int *)((int)piVar2 + (uint)*(ushort *)(piVar2 + 1));
        for (iVar4 = 0; iVar4 < (int)(uint)*(ushort *)((int)piVar2 + 10); iVar4 = iVar4 + 1) {
          if (*piVar3 == param_3) {
            CreateNewJCB__7CScriptFi(param_1,1);
            if (param_4 != 0) {
              memcpy(*(void **)(*(int *)(param_1 + 0x1c) + 0x14),param_5,(long)(param_4 << 2));
              *(int *)(*(int *)(param_1 + 0x1c) + 0x18) =
                   *(int *)(*(int *)(param_1 + 0x1c) + 0x18) + param_4 * 4;
            }
            uVar1 = EnterUFunc__7CScriptFPUcPUcii
                              (param_1,0,
                               **(int **)(param_1 + 0x1c) + (uint)*(ushort *)((int)piVar3 + 6),
                               param_4,0);
            *(u32 *)(*(int *)(param_1 + 0x1c) + 0xc) = uVar1;
            *(int *)(*(int *)(param_1 + 0x1c) + 0x2c) = param_3;
            if (param_6 != 0) {
              *(int *)(*(int *)(param_1 + 0x1c) + 0x28) = param_6;
            }
            Entry__7CScriptFv(param_1);
            return 1;
          }
          piVar3 = piVar3 + 2;
        }
      }
    }
  }
  return 0;
}

/* ---- 0x00298610 size 0x64  CScript::GetEventMagic(v)
 *      mangled: GetEventMagic__7CScriptFv */
u32 GetEventMagic__7CScriptFv(int param_1)

{
  u32 uVar1;
  
  if ((*(int *)(*(int *)(param_1 + 0x1c) + 0xc) == 0) ||
     ((*(byte *)(*(int *)(param_1 + 0x1c) + 0x35) & 0xf) != 1)) {
    uVar1 = 0xffffffff;
  }
  else {
    uVar1 = *(u32 *)(*(int *)(param_1 + 0x1c) + 0x30);
  }
  return uVar1;
}

/* ---- 0x00298680 size 0x28  CScript::SetEventMagic(i)
 *      mangled: SetEventMagic__7CScriptFi */
void SetEventMagic__7CScriptFi(int param_1,u32 param_2)

{
  *(u32 *)(*(int *)(param_1 + 0x1c) + 0x30) = param_2;
  return;
}

/* ---- 0x002986b0 size 0x5c  CScriptEx::CScriptEx(v)
 *      mangled: __ct__9CScriptExFv */
int __ct__9CScriptExFv(int param_1)

{
  __ct__7CPolObjFv(param_1);
  *(u8 **)(param_1 + 0x14) = __vt__9CScriptEx;
  *(u32 *)(param_1 + 0x18) = 0;
  *(u32 *)(param_1 + 0x1c) = 0;
  *(u16 *)(param_1 + 0x20) = 0;
  *(u8 *)(param_1 + 0x22) = 0;
  return param_1;
}

/* ---- 0x00298710 size 0xb0  CScriptEx::Link(iP7CScript)
 *      mangled: Link__9CScriptExFiP7CScript */
void Link__9CScriptExFiP7CScript(int param_1,u16 param_2,int param_3)

{
  int iVar1;
  int iStack_10;
  
  *(u16 *)(param_1 + 0x20) = param_2;
  iStack_10 = param_3;
  if (param_3 == 0) {
    iStack_10 = sys__7CScript;
  }
  *(int *)(param_1 + 0x1c) = iStack_10;
  iVar1 = *(int *)(iStack_10 + 0x20);
  if (iVar1 == 0) {
    *(int *)(iStack_10 + 0x20) = param_1;
    *(u32 *)(param_1 + 0x18) = 0;
  }
  else {
    for (; *(int *)(iVar1 + 0x18) != 0; iVar1 = *(int *)(iVar1 + 0x18)) {
      if (iVar1 == param_1) {
        return;
      }
    }
    *(int *)(iVar1 + 0x18) = param_1;
    *(u32 *)(param_1 + 0x18) = 0;
  }
  return;
}

/* ---- 0x002987c0 size 0x10  CScriptEx::OnStart(v)
 *      mangled: OnStart__9CScriptExFv */
void OnStart__9CScriptExFv(void)

{
  return;
}

/* ---- 0x002987d0 size 0x14  CScriptEx::OnEnd(i)
 *      mangled: OnEnd__9CScriptExFi */
u64 OnEnd__9CScriptExFi(void)

{
  return 0;
}

/* ---- 0x002987f0 size 0x9c  CScriptEx::CallFunc(iiiP9_ParStack)
 *      mangled: CallFunc__9CScriptExFiiiP9_ParStack */
u64
CallFunc__9CScriptExFiiiP9_ParStack
          (int param_1,uint param_2,u32 param_3,u32 param_4,u32 param_5)

{
  u64 uVar1;
  
  while( true ) {
    if (param_1 == 0) {
      return 0x10;
    }
    if (*(ushort *)(param_1 + 0x20) == param_2) break;
    param_1 = *(int *)(param_1 + 0x18);
  }
  uVar1 = (**(code **)(*(int *)(param_1 + 0x14) + 0x18))(param_1,param_3,param_4,param_5);
  return uVar1;
}

/* ---- 0x00298890 size 0x70  CScriptEx::Entry(i)
 *      mangled: Entry__9CScriptExFi */
void Entry__9CScriptExFi(int param_1,u32 param_2)

{
  if ((*(byte *)(param_1 + 0x22) & 1) == 0) {
    *(byte *)(param_1 + 0x22) = *(byte *)(param_1 + 0x22) & 0xfe | 1;
    Entry__7CPollerFP7CPolObjib(app__4CApp + 0x48,param_1,param_2,0);
  }
  return;
}

/* ---- 0x00298900 size 0x68  CScriptEx::Dispose(v)
 *      mangled: Dispose__9CScriptExFv */
void Dispose__9CScriptExFv(int param_1)

{
  if ((*(byte *)(param_1 + 0x22) & 1) == 1) {
    *(byte *)(param_1 + 0x22) = *(byte *)(param_1 + 0x22) & 0xfe;
    Dispose__7CPollerFP7CPolObj(app__4CApp + 0x48,param_1);
  }
  return;
}

/* ---- 0x00298970 size 0x60  CScriptEx::StartSequence(v)
 *      mangled: StartSequence__9CScriptExFv */
void StartSequence__9CScriptExFv(int param_1)

{
  int iVar1;
  
  while (param_1 != 0) {
    iVar1 = *(int *)(param_1 + 0x18);
    (**(code **)(*(int *)(param_1 + 0x14) + 0x10))();
    param_1 = iVar1;
  }
  return;
}

/* ---- 0x002989d0 size 0xe8  CScriptEx::ResetSequence(i)
 *      mangled: ResetSequence__9CScriptExFi */
int ResetSequence__9CScriptExFi(int param_1,uint param_2)

{
  ushort uVar1;
  int iVar2;
  long lVar3;
  int iVar4;
  uint uVar5;
  uint uStack_10;
  
  uVar5 = (int)param_2 >> 8 & 0xff;
  uStack_10 = param_2 & 0xff;
  do {
    iVar4 = param_1;
    if (uVar5 == 0) break;
    param_1 = *(int *)(iVar4 + 0x18);
  } while (*(ushort *)(iVar4 + 0x20) != uVar5);
  while( true ) {
    if (iVar4 == 0) {
      return 0;
    }
    iVar2 = *(int *)(iVar4 + 0x18);
    uVar1 = *(ushort *)(iVar4 + 0x20);
    lVar3 = (**(code **)(*(int *)(iVar4 + 0x14) + 0x14))(iVar4,uStack_10);
    if (lVar3 != 0) break;
    uStack_10 = 0;
    iVar4 = iVar2;
  }
  return (uint)uVar1 * 0x100 + 1;
}

/* ---- 0x00298ac0 size 0x74  CScriptEx::~CScriptEx(v)
 *      mangled: __dt__9CScriptExFv */
int __dt__9CScriptExFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(u8 **)(param_1 + 0x14) = __vt__9CScriptEx;
    __dt__7CPolObjFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* ---- 0x00298b40 size 0x14  CScriptEx::Polling(v)
 *      mangled: Polling__9CScriptExFv */
u64 Polling__9CScriptExFv(void)

{
  return 0;
}

