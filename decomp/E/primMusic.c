/*
 * primMusic.c -- Ghidra decompiler output (SLPM_602.19, JP Furokuban), tidied by tools/E_gen_decomp.py
 * 10 functions. Types: u8/u16/u32/u64 = undefined1/2/4/8. Addresses in comments are JP main-exe addresses.
 */

/* ---- 0x003a6cc0 size 0x28  primMusic::DVD_CB(iP9BufMemoryiPcPv)
 *      mangled: DVD_CB__9primMusicFiP9BufMemoryiPcPv */
u64 DVD_CB__9primMusicFiP9BufMemoryiPcPv(u64 param_1,u32 param_2)

{
  mpBuffer = param_2;
  mbRead = 1;
  return 0;
}

/* ---- 0x003a6cf0 size 0x90  primMusic::primMusic(v)
 *      mangled: __ct__9primMusicFv */
u32 * __ct__9primMusicFv(u32 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = __vt__17DelayDeleteObject;
  __ct__7CPolObjFv(param_1 + 3);
  param_1[2] = __vt__9primMusic;
  param_1[8] = 0x407410;
  *(u8 *)(param_1 + 10) = 1;
  mpBuffer = 0;
  param_1[0xc] = 0;
  param_1[0xd] = 0;
  return param_1;
}

/* ---- 0x003a6d80 size 0xcc  primMusic::~primMusic(v)
 *      mangled: __dt__9primMusicFv */
int __dt__9primMusicFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(u8 **)(param_1 + 8) = __vt__9primMusic;
    *(u32 *)(param_1 + 0x20) = 0x407410;
    if (mpBuffer != 0) {
      __dt__9BufMemoryFv(mpBuffer,1);
      mpBuffer = 0;
    }
    __dt__7CPolObjFv(param_1 + 0xc,0);
    if (param_1 != 0) {
      *(u8 **)(param_1 + 8) = __vt__17DelayDeleteObject;
    }
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* ---- 0x003a6e50 size 0x164  primMusic::initialize(i)
 *      mangled: initialize__9primMusicFi */
void initialize__9primMusicFi(int param_1,int param_2)

{
  u32 uVar1;
  long lVar2;
  int iVar3;
  
  *(int *)(param_1 + 0x2c) = param_2;
  if (param_2 == 0) {
    lVar2 = __nw__FUi(0x94);
    uVar1 = 0;
    if (lVar2 != 0) {
      uVar1 = __ct__6CMusicFv(lVar2);
    }
    *(u32 *)(param_1 + 0x30) = uVar1;
    iVar3 = *(int *)(param_1 + 0x30);
    *(u32 *)(iVar3 + 0x84) = 0;
    *(int *)(iVar3 + 0x88) = param_1;
    iVar3 = param_1;
    if (param_1 != 0) {
      iVar3 = param_1 + 0xc;
    }
    Entry__7CPollerFP7CPolObjib(app__4CApp + 0x48,iVar3,0x80,0);
  }
  else if (param_2 == 1) {
    lVar2 = __nw__FUi(0xbc);
    uVar1 = 0;
    if (lVar2 != 0) {
      uVar1 = __ct__9StreamBGMFv(lVar2);
    }
    *(u32 *)(param_1 + 0x34) = uVar1;
    iVar3 = param_1;
    if (param_1 != 0) {
      iVar3 = param_1 + 0xc;
    }
    Entry__7CPollerFP7CPolObjib(app__4CApp + 0x48,iVar3,0x80,0);
  }
  *(u8 *)(param_1 + 0x28) = 0;
  *(u32 *)(param_1 + 0x24) = 0;
  return;
}

/* ---- 0x003a6fc0 size 0x20  primMusic::DelayDeleteRequest(v)
 *      mangled: DelayDeleteRequest__9primMusicFv */
void DelayDeleteRequest__9primMusicFv(int param_1)

{
  *(u32 *)(param_1 + 0x24) = 4;
  return;
}

/* ---- 0x003a6fe0 size 0x218  primMusic::Polling(v)
 *      mangled: Polling__9primMusicFv */
u64 Polling__9primMusicFv(int param_1)

{
  long lVar1;
  int iVar2;
  
  if (((*(int *)(param_1 + 0x24) == 1) && (mbRead != '\0')) &&
     (*(u32 *)(param_1 + 0x24) = 2, *(int *)(param_1 + 0x2c) == 0)) {
    PlayBGM__6CMusicFUiUiPUc(*(u32 *)(param_1 + 0x30),0,8,*(u32 *)(mpBuffer + 4));
  }
  if (*(int *)(param_1 + 0x24) == 4) {
    if (*(int *)(param_1 + 0x30) == 0) {
      if (*(int *)(param_1 + 0x34) != 0) {
        Delete__9StreamBGMFv(*(u32 *)(param_1 + 0x34));
        *(u32 *)(param_1 + 0x34) = 0;
        iVar2 = param_1;
        if (param_1 != 0) {
          iVar2 = param_1 + 0xc;
        }
        Dispose__7CPollerFP7CPolObj(app__4CApp + 0x48,iVar2);
        *(u8 *)(param_1 + 0x28) = 1;
        (**(code **)(*(int *)(param_1 + 8) + 0xc))();
      }
    }
    else {
      lVar1 = Release__6CMusicFv(*(u32 *)(param_1 + 0x30));
      if (lVar1 != 0) {
        if (*(int *)(param_1 + 0x30) != 0) {
          iVar2 = *(int *)(param_1 + 0x30);
          if (iVar2 != 0) {
            (**(code **)(*(int *)(iVar2 + 0x14) + 8))(iVar2,1);
          }
          *(u32 *)(param_1 + 0x30) = 0;
        }
        iVar2 = param_1;
        if (param_1 != 0) {
          iVar2 = param_1 + 0xc;
        }
        Dispose__7CPollerFP7CPolObj(app__4CApp + 0x48,iVar2);
        *(u8 *)(param_1 + 0x28) = 1;
        (**(code **)(*(int *)(param_1 + 8) + 0xc))();
      }
    }
  }
  return 0;
}

/* ---- 0x003a7200 size 0x48  primMusic::stop(v)
 *      mangled: stop__9primMusicFv */
void stop__9primMusicFv(int param_1)

{
  if (*(int *)(param_1 + 0x2c) == 1) {
    Stop__9StreamBGMFib(*(u32 *)(param_1 + 0x34),0x20,0);
  }
  return;
}

/* ---- 0x003a7250 size 0x110  primMusic::play(Pc)
 *      mangled: play__9primMusicFPc */
void play__9primMusicFPc(int param_1,u32 param_2)

{
  u8 auStack_220 [256];
  char acStack_120 [256];
  int iStack_20;
  u32 uStack_10;
  
  if (*(int *)(param_1 + 0x24) == 0) {
    iStack_20 = param_1;
    uStack_10 = param_2;
    if (*(int *)(param_1 + 0x2c) == 0) {
      sprintf(acStack_120,_2000,param_2);
      SetPathname__7SysToolFPcPCc(auStack_220,acStack_120);
      ReadOrder__11DvdromOrderFPCcPFiP9BufMemoryiPcPv_iiPvi
                (Dvdromour__11DvdromOrder,auStack_220,0x3a6cc0,0,iStack_20,0);
      mbRead = 0;
      *(u32 *)(iStack_20 + 0x24) = 1;
    }
    else if (*(int *)(param_1 + 0x2c) == 1) {
      SetPathname__7SysToolFPcPCc(auStack_220,param_2);
      Create__9StreamBGMFPCc(*(u32 *)(iStack_20 + 0x34),auStack_220);
      SetVolume__9StreamBGMFi(*(u32 *)(iStack_20 + 0x34),0x60);
      Play__9StreamBGMFv(*(u32 *)(iStack_20 + 0x34));
      *(u32 *)(iStack_20 + 0x24) = 2;
    }
  }
  return;
}

/* ---- 0x003a7360 size 0x8  primMusic::@12@Polling(v)
 *      mangled: @12@Polling__9primMusicFv */
u64 _12_Polling__9primMusicFv(int param_1)

{
  long lVar1;
  int iVar2;
  
  if (((*(int *)(param_1 + 0x18) == 1) && (mbRead != '\0')) &&
     (*(u32 *)(param_1 + 0x18) = 2, *(int *)(param_1 + 0x20) == 0)) {
    PlayBGM__6CMusicFUiUiPUc(*(u32 *)(param_1 + 0x24),0,8,*(u32 *)(mpBuffer + 4));
  }
  if (*(int *)(param_1 + 0x18) == 4) {
    if (*(int *)(param_1 + 0x24) == 0) {
      if (*(int *)(param_1 + 0x28) != 0) {
        Delete__9StreamBGMFv(*(u32 *)(param_1 + 0x28));
        *(u32 *)(param_1 + 0x28) = 0;
        iVar2 = 0;
        if (param_1 != 0xc) {
          iVar2 = param_1;
        }
        Dispose__7CPollerFP7CPolObj(app__4CApp + 0x48,iVar2);
        *(u8 *)(param_1 + 0x1c) = 1;
        (**(code **)(*(int *)(param_1 + -4) + 0xc))();
      }
    }
    else {
      lVar1 = Release__6CMusicFv(*(u32 *)(param_1 + 0x24));
      if (lVar1 != 0) {
        if (*(int *)(param_1 + 0x24) != 0) {
          iVar2 = *(int *)(param_1 + 0x24);
          if (iVar2 != 0) {
            (**(code **)(*(int *)(iVar2 + 0x14) + 8))(iVar2,1);
          }
          *(u32 *)(param_1 + 0x24) = 0;
        }
        iVar2 = 0;
        if (param_1 != 0xc) {
          iVar2 = param_1;
        }
        Dispose__7CPollerFP7CPolObj(app__4CApp + 0x48,iVar2);
        *(u8 *)(param_1 + 0x1c) = 1;
        (**(code **)(*(int *)(param_1 + -4) + 0xc))();
      }
    }
  }
  return 0;
}

/* ---- 0x003a7370 size 0x8  primMusic::@12@__dt(v)
 *      mangled: @12@__dt__9primMusicFv */
int _12___dt__9primMusicFv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0xc;
  if (iVar1 != 0) {
    *(u8 **)(param_1 + -4) = __vt__9primMusic;
    *(u32 *)(param_1 + 0x14) = 0x407410;
    if (mpBuffer != 0) {
      __dt__9BufMemoryFv(mpBuffer,1);
      mpBuffer = 0;
    }
    __dt__7CPolObjFv(param_1,0);
    if (iVar1 != 0) {
      *(u8 **)(param_1 + -4) = __vt__17DelayDeleteObject;
    }
    if (0 < param_2) {
      __dl__FPv(iVar1);
    }
  }
  return iVar1;
}

