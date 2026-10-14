/*
 * primSound.c -- Ghidra decompiler output (SLPM_602.19, JP Furokuban), tidied by tools/E_gen_decomp.py
 * 11 functions. Types: u8/u16/u32/u64 = undefined1/2/4/8. Addresses in comments are JP main-exe addresses.
 */

/* ---- 0x003a6790 size 0x90  primSound::primSound(v)
 *      mangled: __ct__9primSoundFv */
u32 * __ct__9primSoundFv(u32 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = __vt__17DelayDeleteObject;
  __ct__7CPolObjFv(param_1 + 3);
  param_1[2] = __vt__9primSound;
  param_1[8] = 0x4073e0;
  param_1[10] = 0;
  *(u8 *)(param_1 + 0xb) = 0xff;
  *(u8 *)((int)param_1 + 0x2d) = 1;
  return param_1;
}

/* ---- 0x003a6820 size 0xa4  primSound::~primSound(v)
 *      mangled: __dt__9primSoundFv */
int __dt__9primSoundFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(u8 **)(param_1 + 8) = __vt__9primSound;
    *(u32 *)(param_1 + 0x20) = 0x4073e0;
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

/* ---- 0x003a68d0 size 0xbc  primSound::initialize(v)
 *      mangled: initialize__9primSoundFv */
void initialize__9primSoundFv(int param_1)

{
  u32 uVar1;
  long lVar2;
  
  *(u8 *)(param_1 + 0x2d) = 0;
  *(u32 *)(param_1 + 0x24) = 0;
  lVar2 = __nw__FUi(0x14c);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = __ct__9MenuSoundFv(lVar2);
  }
  *(u32 *)(param_1 + 0x28) = uVar1;
  Entry__7CPollerFP7CPolObjib(app__4CApp + 0x48,*(u32 *)(param_1 + 0x28),0x80,0);
  if (param_1 != 0) {
    param_1 = param_1 + 0xc;
  }
  Entry__7CPollerFP7CPolObjib(app__4CApp + 0x48,param_1,0x80,0);
  return;
}

/* ---- 0x003a6990 size 0x40  primSound::DelayDeleteRequest(v)
 *      mangled: DelayDeleteRequest__9primSoundFv */
void DelayDeleteRequest__9primSoundFv(int param_1)

{
  releaseSE__9primSoundFv(param_1);
  *(u8 *)(param_1 + 0x2d) = 1;
  *(u32 *)(param_1 + 0x24) = 1;
  return;
}

/* ---- 0x003a69d0 size 0x19c  primSound::Polling(v)
 *      mangled: Polling__9primSoundFv */
u64 Polling__9primSoundFv(int param_1)

{
  long lVar1;
  int iVar2;
  
  if ((*(char *)(param_1 + 0x2c) != -1) && (*(char *)(param_1 + 0x2e) == '\0')) {
    *(bool *)(param_1 + 0x2e) =
         *(char *)(*(int *)(param_1 + 0x28) + *(char *)(param_1 + 0x2c) * 0x14 + 0x1b) != '\0';
  }
  if ((*(int *)(param_1 + 0x24) == 1) &&
     (lVar1 = IsDelete__9MenuSoundFv(*(u32 *)(param_1 + 0x28)), lVar1 != 0)) {
    Dispose__7CPollerFP7CPolObj(app__4CApp + 0x48,*(u32 *)(param_1 + 0x28));
    iVar2 = param_1;
    if (param_1 != 0) {
      iVar2 = param_1 + 0xc;
    }
    Dispose__7CPollerFP7CPolObj(app__4CApp + 0x48,iVar2);
    if (*(int *)(param_1 + 0x28) != 0) {
      iVar2 = *(int *)(param_1 + 0x28);
      if (iVar2 != 0) {
        (**(code **)(*(int *)(iVar2 + 0x14) + 8))(iVar2,1);
      }
      *(u32 *)(param_1 + 0x28) = 0;
    }
    (**(code **)(*(int *)(param_1 + 8) + 0xc))();
  }
  return 0;
}

/* ---- 0x003a6b70 size 0x44  primSound::loadSE(Pc)
 *      mangled: loadSE__9primSoundFPc */
void loadSE__9primSoundFPc(int param_1,u32 param_2)

{
  u8 uVar1;
  
  uVar1 = GetSDH__9MenuSoundFPCc(*(u32 *)(param_1 + 0x28),param_2);
  *(u8 *)(param_1 + 0x2c) = uVar1;
  *(u8 *)(param_1 + 0x2e) = 0;
  return;
}

/* ---- 0x003a6bc0 size 0x60  primSound::releaseSE(v)
 *      mangled: releaseSE__9primSoundFv */
void releaseSE__9primSoundFv(int param_1)

{
  if (*(char *)(param_1 + 0x2c) != -1) {
    ReleaseSDH__9MenuSoundFc(*(u32 *)(param_1 + 0x28),*(u8 *)(param_1 + 0x2c));
    *(u8 *)(param_1 + 0x2c) = 0xff;
  }
  return;
}

/* ---- 0x003a6c20 size 0x3c  primSound::play(i)
 *      mangled: play__9primSoundFi */
void play__9primSoundFi(int param_1,u32 param_2)

{
  PlaySE__9MenuSoundFUiUcP8_SeParam(*(u32 *)(param_1 + 0x28),param_2,0,0);
  return;
}

/* ---- 0x003a6c60 size 0x34  primSound::stop(c)
 *      mangled: stop__9primSoundFc */
void stop__9primSoundFc(int param_1,u8 param_2)

{
  StopSE__9MenuSoundFc(*(u32 *)(param_1 + 0x28),param_2);
  return;
}

/* ---- 0x003a6ca0 size 0x8  primSound::@12@Polling(v)
 *      mangled: @12@Polling__9primSoundFv */
u64 _12_Polling__9primSoundFv(int param_1)

{
  long lVar1;
  int iVar2;
  
  if ((*(char *)(param_1 + 0x20) != -1) && (*(char *)(param_1 + 0x22) == '\0')) {
    *(bool *)(param_1 + 0x22) =
         *(char *)(*(int *)(param_1 + 0x1c) + *(char *)(param_1 + 0x20) * 0x14 + 0x1b) != '\0';
  }
  if ((*(int *)(param_1 + 0x18) == 1) &&
     (lVar1 = IsDelete__9MenuSoundFv(*(u32 *)(param_1 + 0x1c)), lVar1 != 0)) {
    Dispose__7CPollerFP7CPolObj(app__4CApp + 0x48,*(u32 *)(param_1 + 0x1c));
    iVar2 = 0;
    if (param_1 != 0xc) {
      iVar2 = param_1;
    }
    Dispose__7CPollerFP7CPolObj(app__4CApp + 0x48,iVar2);
    if (*(int *)(param_1 + 0x1c) != 0) {
      iVar2 = *(int *)(param_1 + 0x1c);
      if (iVar2 != 0) {
        (**(code **)(*(int *)(iVar2 + 0x14) + 8))(iVar2,1);
      }
      *(u32 *)(param_1 + 0x1c) = 0;
    }
    (**(code **)(*(int *)(param_1 + -4) + 0xc))();
  }
  return 0;
}

/* ---- 0x003a6cb0 size 0x8  primSound::@12@__dt(v)
 *      mangled: @12@__dt__9primSoundFv */
int _12___dt__9primSoundFv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0xc;
  if (iVar1 != 0) {
    *(u8 **)(param_1 + -4) = __vt__9primSound;
    *(u32 *)(param_1 + 0x14) = 0x4073e0;
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

