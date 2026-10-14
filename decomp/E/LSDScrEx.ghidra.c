/*
 * LSDScrEx.ghidra.c -- Ghidra decompiler output (SLPM_602.19, JP Furokuban), tidied by tools/E_gen_decomp.py
 * 19 functions. Types: u8/u16/u32/u64 = undefined1/2/4/8. Addresses in comments are JP main-exe addresses.
 */

/* ---- 0x003ccd70 size 0x54  LSDScrEx::LSDScrEx(v)
 *      mangled: __ct__8LSDScrExFv */
int __ct__8LSDScrExFv(int param_1)

{
  __ct__9CScriptExFv(param_1);
  *(u8 **)(param_1 + 0x14) = __vt__8LSDScrEx;
  memset((void *)(param_1 + 0x24),0,0x48);
  return param_1;
}

/* ---- 0x003ccdd0 size 0x94  LSDScrEx::~LSDScrEx(v)
 *      mangled: __dt__8LSDScrExFv */
int __dt__8LSDScrExFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(u8 **)(param_1 + 0x14) = __vt__8LSDScrEx;
    sys__8LSDScrEx = 0;
    if (param_1 != 0) {
      *(u8 **)(param_1 + 0x14) = __vt__9CScriptEx;
      __dt__7CPolObjFv(param_1,0);
    }
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* ---- 0x003cce70 size 0x100  LSDScrEx::Delete(v)
 *      mangled: Delete__8LSDScrExFv */
void Delete__8LSDScrExFv(int param_1)

{
  u32 uVar1;
  int iVar2;
  
  if ((*(byte *)(param_1 + 0x58) & 1) == 0) {
    *(byte *)(param_1 + 0x58) = *(byte *)(param_1 + 0x58) & 0xfe | 1;
    iVar2 = sys__6CMusic;
    if (-1 < (long)((ulong)*(byte *)(param_1 + 0x58) << 0x3e)) {
      uVar1 = *(u32 *)(param_1 + 0x2c);
      *(u32 *)(sys__6CMusic + 0x84) = *(u32 *)(param_1 + 0x28);
      *(u32 *)(iVar2 + 0x88) = uVar1;
    }
    for (iVar2 = 0; iVar2 < 2; iVar2 = iVar2 + 1) {
      if (*(int *)(param_1 + iVar2 * 4 + 0x50) != 0) {
        Delete__9FldSpriteFv(*(u32 *)(param_1 + iVar2 * 4 + 0x50));
      }
    }
  }
  return;
}

/* ---- 0x003ccf70 size 0x108  LSDScrEx::Init(v)
 *      mangled: Init__8LSDScrExFv */
u32 Init__8LSDScrExFv(int param_1)

{
  int iVar1;
  long lVar2;
  
  iVar1 = sys__6CMusic;
  sys__8LSDScrEx = param_1;
  if (sys__6CMusic == 0) {
    *(byte *)(param_1 + 0x58) = *(byte *)(param_1 + 0x58) & 0xfd | 2;
    lVar2 = __nw__FUi(0x94);
    iVar1 = 0;
    if (lVar2 != 0) {
      iVar1 = __ct__6CMusicFv(lVar2);
    }
  }
  else {
    *(u32 *)(param_1 + 0x2c) = *(u32 *)(sys__6CMusic + 0x88);
    *(u32 *)(param_1 + 0x28) = *(u32 *)(iVar1 + 0x84);
    iVar1 = sys__6CMusic;
  }
  sys__6CMusic = iVar1;
  iVar1 = sys__6CMusic;
  *(code **)(sys__6CMusic + 0x84) = cbMusic__8LSDScrExFUcUiUi;
  *(int *)(iVar1 + 0x88) = param_1;
  preLoad__8LSDScrExFv(param_1);
  Start__8LSDScrExFv(param_1);
  return 1;
}

/* ---- 0x003cd080 size 0x40  LSDScrEx::LinkA(P10_EventWork)
 *      mangled: LinkA__8LSDScrExFP10_EventWork */
void LinkA__8LSDScrExFP10_EventWork(int param_1,u32 param_2)

{
  *(u32 *)(param_1 + 0x24) = param_2;
  Link__9CScriptExFiP7CScript(param_1,0xc0,0);
  return;
}

/* ---- 0x003cd0c0 size 0x14  LSDScrEx::preLoad(v)
 *      mangled: preLoad__8LSDScrExFv */
u32 preLoad__8LSDScrExFv(void)

{
  return 1;
}

/* ---- 0x003cd0e0 size 0x30  LSDScrEx::Start(v)
 *      mangled: Start__8LSDScrExFv */
u32 Start__8LSDScrExFv(u32 param_1)

{
  Entry__9CScriptExFi(param_1,0x70);
  return 1;
}

/* ---- 0x003cd110 size 0xbc  LSDScrEx::closeInquiry(v)
 *      mangled: closeInquiry__8LSDScrExFv */
u64 closeInquiry__8LSDScrExFv(int param_1)

{
  int iVar1;
  
  Dispose__9CScriptExFv(param_1);
  if (sys__8CineMask != 0) {
    Delete__8CineMaskFv(sys__8CineMask);
    sys__8CineMask = 0;
  }
  for (iVar1 = 0; iVar1 < 8; iVar1 = iVar1 + 1) {
    if (*(int *)(param_1 + iVar1 * 4 + 0x30) != 0) {
      __dt__5CVibeFv(*(u32 *)(param_1 + iVar1 * 4 + 0x30),1);
      *(u32 *)(param_1 + iVar1 * 4 + 0x30) = 0;
    }
  }
  return 0;
}

/* ---- 0x003cd1d0 size 0x138  LSDScrEx::Polling(v)
 *      mangled: Polling__8LSDScrExFv */
u32 Polling__8LSDScrExFv(int param_1)

{
  bool bVar1;
  u32 uVar2;
  long lVar3;
  
  if ((*(byte *)(param_1 + 0x58) & 1) == 0) {
    PollingSound__8LSDScrExFv(param_1);
    EventHandlerUpdate__FP10_EventWork(*(u32 *)(param_1 + 0x24));
    uVar2 = 0;
  }
  else {
    bVar1 = false;
    if (((long)((ulong)*(byte *)(param_1 + 0x58) << 0x3e) < 0) && (sys__6CMusic != 0)) {
      lVar3 = Release__6CMusicFv(sys__6CMusic);
      if (lVar3 == 0) {
        bVar1 = true;
      }
      else {
        if (sys__6CMusic != 0) {
          (**(code **)(*(int *)(sys__6CMusic + 0x14) + 8))(sys__6CMusic,1);
        }
        sys__6CMusic = 0;
      }
    }
    if (bVar1) {
      uVar2 = 0;
    }
    else {
      *(byte *)(param_1 + 0x22) = *(byte *)(param_1 + 0x22) & 0xfe;
      closeInquiry__8LSDScrExFv(param_1);
      *(u8 *)(param_1 + 0xc) = 1;
      *(u8 *)(param_1 + 0xe) = 0;
      uVar2 = 1;
    }
  }
  return uVar2;
}

/* ---- 0x003cd310 size 0x364  LSDScrEx::CallFunc(iiP9_ParStack)
 *      mangled: CallFunc__8LSDScrExFiiP9_ParStack */
u64
CallFunc__8LSDScrExFiiP9_ParStack(int param_1,u32 param_2,u64 param_3,uint *param_4)

{
  uint uVar1;
  int iVar2;
  long lVar3;
  
  switch(param_2) {
  case 0:
    uVar1 = *param_4;
    if ((uVar1 != 4) && ((uVar1 & 1) == 0)) {
      SetFader__12CFieldSocketFiii(m_socket__12CFieldSocket,1,uVar1 & 2 | 1,0);
    }
    SetFader__12CFieldSocketFiii(m_socket__12CFieldSocket,1,uVar1,param_4[1]);
    break;
  case 1:
    break;
  case 2:
    break;
  case 3:
    *(u16 *)(param_1 + 0x5a) = 1;
    strcpy((char *)(param_1 + 0x5c),(char *)*param_4);
    break;
  case 4:
    FadeBGM__6CMusicFUiUi(sys__6CMusic,0,*param_4);
    break;
  case 5:
    if (*param_4 == 0) {
      if (sys__8CineMask != 0) {
        Clr__8CineMaskFv(sys__8CineMask);
      }
    }
    else {
      iVar2 = sys__8CineMask;
      if (sys__8CineMask == 0) {
        lVar3 = __nw__FUi(0x4c);
        iVar2 = 0;
        if (lVar3 != 0) {
          iVar2 = __ct__8CineMaskFv(lVar3);
        }
      }
      sys__8CineMask = iVar2;
      Dsp__8CineMaskFv(sys__8CineMask);
    }
    break;
  case 6:
    StartVib__8LSDScrExFiPCci(param_1,*param_4,param_4[1],param_4[2]);
    break;
  case 7:
    StopVib__8LSDScrExFii(param_1,*param_4,param_4[1]);
    break;
  case 8:
    FadeVib__8LSDScrExFiii(param_1,*param_4,param_4[1],param_4[2]);
    break;
  case 9:
    DspImage__8LSDScrExFiPCcii(param_1,*param_4,param_4[1],param_4[2],param_4[3]);
    break;
  case 10:
    ClrImage__8LSDScrExFii(param_1,*param_4,param_4[1]);
    break;
  case 0xb:
    SetBGMotion__8LSDScrExFiPCc(param_1,*param_4,param_4[1]);
    break;
  case 0xc:
    SetBGMotionI__8LSDScrExFiPCcPCc(param_1,*param_4,param_4[1],param_4[2]);
    break;
  case 0xd:
    MCESInvokeBattle__Fv();
    break;
  case 0xe:
    if (m_pCurrent__8CFieldBG != 0) {
      EffectAlpha__8CFieldBGFifi((float)(int)param_4[1],m_pCurrent__8CFieldBG,*param_4,param_4[2]);
    }
    break;
  case 0xf:
    Pause__9LSDPlayerFv(sys__9LSDPlayer);
    Exit__9LSDPlayerFv(sys__9LSDPlayer);
  }
  return 0;
}

/* ---- 0x003cd680 size 0x108  LSDScrEx::PollingSound(v)
 *      mangled: PollingSound__8LSDScrExFv */
void PollingSound__8LSDScrExFv(int param_1)

{
  long lVar1;
  
  if (*(short *)(param_1 + 0x5a) == 1) {
    lVar1 = Find__18GenericDataHandlerFPCc(param_1 + 0x5c);
    if (lVar1 == 0) {
      *(u16 *)(param_1 + 0x5a) = 0;
    }
    else {
      PlayBGM__6CMusicFUiUiPUc
                (sys__6CMusic,0,(u8)playModeTbl,
                 *(u32 *)(*(int *)((int)lVar1 + 0x2c) + 4));
      *(short *)(param_1 + 0x5a) = *(short *)(param_1 + 0x5a) + 1;
    }
  }
  (**(code **)(*(int *)(sys__6CMusic + 0x14) + 0xc))();
  return;
}

/* ---- 0x003cd790 size 0xb4  LSDScrEx::cbMusic(UcUiUi)
 *      mangled: cbMusic__8LSDScrExFUcUiUi */
void cbMusic__8LSDScrExFUcUiUi(char param_1,u32 param_2)

{
  long lVar1;
  
  if (param_1 == '\x01') {
    *(u16 *)(sys__8LSDScrEx + 0x5a) = 0;
    lVar1 = Find__18GenericDataHandlerFPCc(sys__8LSDScrEx + 0x5c);
    if (lVar1 != 0) {
      RemoveData__18GenericDataHandlerFP16_GenericDataInfob(lVar1,0);
    }
  }
  else if (*(int *)(sys__8LSDScrEx + 0x28) != 0) {
    (**(code **)(sys__8LSDScrEx + 0x28))(param_1,param_2,*(u32 *)(sys__8LSDScrEx + 0x2c));
  }
  return;
}

/* ---- 0x003cd850 size 0x158  LSDScrEx::StartVib(iPCci)
 *      mangled: StartVib__8LSDScrExFiPCci */
void StartVib__8LSDScrExFiPCci(int param_1,int param_2,u32 param_3,u32 param_4)

{
  long lVar1;
  long lVar2;
  u64 uVar3;
  
  if (*(int *)(param_1 + param_2 * 4 + 0x30) != 0) {
    __dt__5CVibeFv(*(u32 *)(param_1 + param_2 * 4 + 0x30),1);
    *(u32 *)(param_1 + param_2 * 4 + 0x30) = 0;
  }
  lVar1 = Find__18GenericDataHandlerFPCc(param_3);
  if ((lVar1 != 0) &&
     (lVar1 = GetSeqData__8CVibeManFPvi(*(u32 *)(*(int *)((int)lVar1 + 0x2c) + 4),param_4),
     lVar1 != 0)) {
    lVar2 = __nw__FUi(0x44);
    uVar3 = 0;
    if (lVar2 != 0) {
      uVar3 = __ct__5CVibeFv(lVar2);
    }
    *(int *)(param_1 + param_2 * 4 + 0x30) = (int)uVar3;
    Start__8CVibeManFP5CVibeP10_ActSeqHdri(sys__8CVibeMan,uVar3,lVar1,0);
  }
  return;
}

/* ---- 0x003cd9b0 size 0x134  LSDScrEx::StopVib(ii)
 *      mangled: StopVib__8LSDScrExFii */
void StopVib__8LSDScrExFii(int param_1,int param_2,int param_3)

{
  if (param_2 < 0) {
    if (param_3 < 1) {
      ReleaseAllVibe__8CVibeManFv(sys__8CVibeMan);
    }
    else {
      SetFader__8CVibeManFii(sys__8CVibeMan,0,param_3);
    }
  }
  else if (*(int *)(param_1 + param_2 * 4 + 0x30) != 0) {
    if (((*(byte *)(*(int *)(param_1 + param_2 * 4 + 0x30) + 0x14) & 3) == 0) || (param_3 < 1)) {
      __dt__5CVibeFv(*(u32 *)(param_1 + param_2 * 4 + 0x30),1);
      *(u32 *)(param_1 + param_2 * 4 + 0x30) = 0;
    }
    else {
      SetFader__5CVibeFiii(*(u32 *)(param_1 + param_2 * 4 + 0x30),0,param_3,1);
    }
  }
  return;
}

/* ---- 0x003cdaf0 size 0xc0  LSDScrEx::FadeVib(iii)
 *      mangled: FadeVib__8LSDScrExFiii */
void FadeVib__8LSDScrExFiii(int param_1,int param_2,u32 param_3,int param_4)

{
  if (param_2 < 0) {
    if (param_4 < 1) {
      Volume__8CVibeManFi(sys__8CVibeMan,param_3);
    }
    else {
      SetFader__8CVibeManFii(sys__8CVibeMan,param_3,param_4);
    }
  }
  else if (*(int *)(param_1 + param_2 * 4 + 0x30) != 0) {
    SetFader__5CVibeFiii(*(u32 *)(param_1 + param_2 * 4 + 0x30),param_3,param_4,0);
  }
  return;
}

/* ---- 0x003cdbb0 size 0x104  LSDScrEx::DspImage(iPCcii)
 *      mangled: DspImage__8LSDScrExFiPCcii */
void DspImage__8LSDScrExFiPCcii
               (int param_1,int param_2,u32 param_3,u32 param_4,u32 param_5)

{
  int iVar1;
  long lVar2;
  long lVar3;
  
  lVar2 = Find__18GenericDataHandlerFPCc(param_3);
  if (lVar2 != 0) {
    iVar1 = *(int *)(param_1 + param_2 * 4 + 0x50);
    if (iVar1 == 0) {
      lVar3 = __nw__FUi(0xd0);
      iVar1 = 0;
      if (lVar3 != 0) {
        iVar1 = __ct__9FldSpriteFv(lVar3);
      }
      *(int *)(param_1 + param_2 * 4 + 0x50) = iVar1;
    }
    Create__9FldSpriteFP9BufMemoryib(iVar1,*(u32 *)((int)lVar2 + 0x2c),1,1);
    SetLayer__9FldSpriteFi(iVar1,0xb);
    Dsp__9FldSpriteFiiii(iVar1,param_4,param_5,0,0);
  }
  return;
}

/* ---- 0x003cdcc0 size 0x8c  LSDScrEx::ClrImage(ii)
 *      mangled: ClrImage__8LSDScrExFii */
void ClrImage__8LSDScrExFii(int param_1,int param_2,int param_3)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + param_2 * 4 + 0x50);
  if ((iVar1 != 0) && (Clr__9FldSpriteFiib(iVar1,0,0,param_3 != 0), param_3 == 0)) {
    *(u32 *)(param_1 + param_2 * 4 + 0x50) = 0;
  }
  return;
}

/* ---- 0x003cdd50 size 0x84  LSDScrEx::SetBGMotion(iPCc)
 *      mangled: SetBGMotion__8LSDScrExFiPCc */
void SetBGMotion__8LSDScrExFiPCc(u64 param_1,u32 param_2,u32 param_3)

{
  long lVar1;
  
  lVar1 = GetModel__8CFieldBGFi(m_pCurrent__8CFieldBG,param_2);
  if (lVar1 != 0) {
    *(byte *)((int)lVar1 + 0x81) = *(byte *)((int)lVar1 + 0x81) & 0xdf;
    SetLastMotion__11CFieldModelFPCc(lVar1,param_3);
    SetMotion__11CFieldModelFPCc(lVar1,param_3);
  }
  return;
}

/* ---- 0x003cdde0 size 0x1fc  LSDScrEx::SetBGMotionI(iPCcPCc)
 *      mangled: SetBGMotionI__8LSDScrExFiPCcPCc */
void SetBGMotionI__8LSDScrExFiPCcPCc
               (u64 param_1,u32 param_2,u32 param_3,char *param_4)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  long lVar5;
  long lVar6;
  int iVar7;
  char acStack_60 [12];
  u8 uStack_54;
  int *piStack_48;
  char *pcStack_44;
  u32 uStack_30;
  u32 uStack_20;
  char *pcStack_10;
  
  uStack_30 = param_2;
  uStack_20 = param_3;
  pcStack_10 = param_4;
  lVar5 = GetModel__8CFieldBGFi(m_pCurrent__8CFieldBG,param_2);
  if ((lVar5 != 0) && (lVar6 = Find__18GenericDataHandlerFPCc(uStack_20), lVar6 != 0)) {
    uStack_54 = 0;
    piVar1 = *(int **)(*(int *)((int)lVar6 + 0x2c) + 4);
    piStack_48 = piVar1;
    if (*piVar1 == 0x44485153) {
      memcpy(acStack_60,piVar1 + 1,0xc);
      pcStack_10 = acStack_60;
      piVar3 = piVar1;
    }
    else {
      iVar2 = GetFileCount(piVar1);
      for (iVar7 = 0; piVar3 = piVar1, iVar7 < iVar2; iVar7 = iVar7 + 1) {
        piVar3 = (int *)GetFileEntry(piVar1,iVar7);
        pcStack_44 = (char *)GetFileID(piVar1,iVar7);
        iVar4 = strcmp((char *)&_3394,pcStack_44);
        if ((iVar4 == 0) && (iVar4 = strncmp((char *)(piVar3 + 1),pcStack_10,0xc), iVar4 == 0))
        break;
      }
      if (iVar2 <= iVar7) {
        return;
      }
    }
    iVar2 = (int)lVar5;
    createMotion__5ModelFPUc(*(u32 *)(iVar2 + 0x70),piVar3);
    *(byte *)(iVar2 + 0x81) = *(byte *)(iVar2 + 0x81) & 0xdf;
    SetLastMotion__11CFieldModelFPCc(lVar5,pcStack_10);
    SetMotion__11CFieldModelFPCc(lVar5,pcStack_10);
  }
  return;
}

