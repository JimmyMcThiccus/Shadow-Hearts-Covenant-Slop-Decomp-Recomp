/* ==== CLEANED (main exe; port: sh2_field/src/socket.rs) ==== */
#include "_types.h"
extern CFieldSocket *m_socket; extern struct CField *fld; extern struct CScript *fldScript; extern CSTGDB *m_pSDB; extern u8 m_flags /* 0x40ada0 */, m_flags2 /* 0x40ada1 */;

/* JP 0x003bcfd0 */
void InitFieldSocketM(const char *map) {
    if (!m_socket) { void *p = operator_new(0x6c); m_socket = p ? CFieldSocket_ctor(p, map) : 0; }
    else CFieldSocket_SetMPS(m_socket, map);
    SSHSys_SetAPI(sys__6SSHSys, m_socket);
}
/* JP 0x003bd8e0/0x003bd9c0 ctor + Init */
CFieldSocket *CFieldSocket_ctor(CFieldSocket *t, const char *map) {
    SSHApi_ctor(t); CPolObj_ctor(&t->polobj); t->vtbl = __vt__12CFieldSocket; t->vt_b = (void *)0x4076a0;
    scePrintf("## CFieldSocket::constructor\n");
    t->map[0] = 0; m_flags = 0; t->phase = 0; t->overlay_state = 0; memset(&t->fader[0], 0, 0x18);
    t->data_access = 0; t->entry_id = 0; t->overlay_buf = 0; t->blur = 0; t->smooth = 0;
    if (map) strcpy(t->map, map);
    return t;
}
/* JP 0x003bdbd0 */
int CFieldSocket_preLoad(CFieldSocket *t) {
    if (((m_flags2 >> 2) & 3) == 0 || SSHSys_isPrevApiGone(sys__6SSHSys)) {
        CFieldSocket_fieldOverlay(t);
        if (t->phase == 0) { CPause_DisableReset(app->pause); t->phase = 1; ExpansionTexture_changeLayer(LayerMan_GetLayer(7)); return 0; }
        return 1;
    }
    return 0;
}
/* JP 0x003bdd50 -- overlay load state machine (+0x54) */
int CFieldSocket_fieldOverlay(CFieldSocket *t) {
    switch (t->overlay_state) {
    case 0: { int r = Overlay_Load(&sys->overlay, "FIELD.BIN", fieldLoadCB, 0, t); if (r == 0) t->overlay_state = 1; else if (r == 3) t->overlay_state = 2; else return 0; break; }
    case 1: break;                                                                 /* async preload in flight */
    case 2:                                                                        /* loaded: build the world */
        sys__9FldMemory = new FldMemory; if (t->overlay_buf) { delete t->overlay_buf; t->overlay_buf = 0; }
        if (t->phase == 2) { CFieldSocket_WakeUp(t); t->phase = 3; }
        if (!strcmp(t->map, WORLDMAP_NAME)) CFieldSocket_WorldMapJumpA(t, -1, 0, 0);
        else { fld = new CField; CField_Init(fld, t->map); fld->entry_id = t->entry_id; }
        t->overlay_state = 3; CPause_EnableReset(app->pause, 1);
    default: return 1; }
    return 0;
}
/* JP 0x003bd590 WakeMapJump(map): jump to another field map / the world map from the running scene */
void CFieldSocket_WakeMapJump(CFieldSocket *t, const char *map) {
    if (!fld || t->entry_id != -2) {
        CFieldSocket_WakeUp(t);
        if (!strcmp(map, WORLDMAP_NAME)) CFieldSocket_WorldMapJumpA(t, -1, 0, 0);
        else {
            if (!fld) { fld = new CField; CField_Init(fld, map); }
            else { CField_Pause(fld, 1); fld->flags_18d = (fld->flags_18d & 0xef) | 0x10; CFieldSocket_LoadMPS(t, map); }
            fld->entry_id = t->entry_id;
        }
    } else { CFieldSocket_Sleep(t); CFieldSocket_SetMPS(t, map); t->phase = 0x30; CField_Pause(fld, 1); CField_Delete(fld); fld = 0; }
}
/* JP 0x003be2d0 */ int CFieldSocket_Start(CFieldSocket *t) { if (t->overlay_state == 3) { CFieldSocket_WakeUp(t); if ((t->phase & 0xf0) != 0x10) t->phase = 3; } else { t->phase = 2; CFieldSocket_DelayUpdate(t); } return 1; }
/* JP 0x003be730 closeInquiry */
int CFieldSocket_closeInquiry(CFieldSocket *t) {
    fld = sys__6CField;
    if (t->phase < 5) { if (CPoller_Find(app->poller_game, &t->polobj)) CPoller_Dispose(app->poller_game, &t->polobj);
        if (fld) { CField_ClearSDB(fld, 0); CField_closeInquiry(fld); } t->phase = 5; return 1; }
    if (t->phase == 6) { Overlay_Unload(&sys->overlay, 0); t->overlay_state = 0; t->phase = 7; CFieldSocket_Sleep(t); MenuObj_ReleaseCmdMenu(); if (sys__9FldMemory) delete sys__9FldMemory; }
    else if (t->phase == 5) { if (sys__6CField) { delete sys__6CField; fld = 0; } CFieldSocket_ClrFilter(t); t->phase = 6; return 1; }
    return 0;
}

/* ---- faders (two slots of 0xc bytes at +0x30, +0x3c) ---- */
/* JP 0x003bedf0 SetFader(slot, mode, frames) */
void CFieldSocket_SetFader(CFieldSocket *t, int slot, u8 mode, int frames) {
    Fader *f = &t->fader[slot]; u8 b = mode & 0x7f;
    if (b == f->mode && frames != 0) return;
    f->mode = b;
    f->cur = (!(mode & 0x80) || f->total == f->cur) ? 0 : frames * f->cur / f->total;
    f->total = frames; f->state = (f->state & 0xf0) | 1;
    if (b < 4) f->bright->color = (mode & 2) ? 0xffffff : 0;
    if (b == 7) f->bright->color = 0;
    if (frames == 0) { f->bright->alpha = (mode & 1) ? 0x80 : 0; if (!(mode & 1)) f->state &= 0xf0; }
}
/* JP 0x003bf110 UpdateFader(dt) */
void CFieldSocket_UpdateFader(CFieldSocket *t, u32 dt) {
    for (int i = 0; i < 2; i++) { Fader *f = &t->fader[i]; if (f->state & 0x10) continue;       /* paused */
        if (f->cur == f->total) { if ((f->state & 0xf) != 2) continue; f->mode = 0; f->state &= 0xf0; }
        int c = f->cur + dt; if (c >= f->total) { f->state = (f->state & 0xf0) | (f->mode & 1); c = f->total; }
        f->cur = c; int a;
        if (!(f->mode & 1)) a = (c == f->total) ? 0 : 0x80 - (c << 7) / f->total; else a = (c == f->total) ? 0x80 : (c << 7) / f->total;
        if ((f->mode >> 1) == 3) a >>= 1;
        f->bright->alpha = a; }
}
/* JP 0x003bed00 GetFaderLevel(slot) -> 0..0x7f */
int CFieldSocket_GetFaderLevel(CFieldSocket *t, int slot) {
    Fader *f = &t->fader[slot]; if (!(f->state & 0xf)) return 0; if (f->total == 0) return 0x7f;
    int l = (f->cur << 7) / f->total; return (f->mode & 1) ? l : 0x7f - l;
}
/* JP 0x003bf020 */ void CFieldSocket_ClrFader(CFieldSocket *t, int s) { Fader *f = &t->fader[s]; if (f->state & 0xf) f->state = (f->state & 0xf0) | 2; f->total = 0; f->cur = 0; }
/* JP 0x003becb0 */ int CFieldSocket_isFaderDsp(CFieldSocket *t, int s) { return (t->fader[s].state & 0xf) != 0; }

/* JP 0x003bf300 CommandMenu(cmd, arg) */
void CFieldSocket_CommandMenu(CFieldSocket *t, u16 cmd, u32 arg) {
    struct FieldGS *gs = GetFieldGS(); cmd &= 0xff;
    if (cmd == 0x10) { CFieldSocket_SaveScriptRegister(t); t->data_access = new dataAccess; dataAccess_initialize(t->data_access, 0, cbSave, t);
                       CFieldSocket_SetFader(t, 1, 1, 200); CField_Pause(fld, 0); }
    else if (cmd == 6) { CFieldSocket_SaveScriptRegister(t); CmdMenu *m = new CmdMenu(8, cbMenu, t); m->flags4a = arg; }
    else if (cmd == 5) { CFieldSocket_SaveScriptRegister(t); CmdMenuTutorial *m = new CmdMenuTutorial; u16 f = 0;
                         if (gs && ((gs->unk44 >> 2) & 3) == 0) arg |= 2; if (arg & 1) f = 2; if (!(arg & 2)) f |= 1; m->flags4a = f;
                         CmdMenuTutorial_StartTutorial(m, (arg >> 16) & 0xff, cbMenu2, t); }
    else if (cmd == 4) { CFieldSocket_SaveScriptRegister(t); CmdMenu *m = new CmdMenu(0, cbMenu, t); u16 f = 0; if (arg & 1) f = 2; if (!(arg & 2)) f |= 1; m->flags4a = f; }
    else if (gs) gs->unk44 = cmd;
}
/* JP 0x003bd1f0 GetMapName(buf, map, kind): kind 0 -> .MSC (script), 1 -> .MPS (SDB) */
int GetMapName(char *buf, const char *map, int kind) { return sprintf(buf, "%sFIELD/MPS/%s.%s", pDataPath, map, kind ? "MPS" : "MSC"); }


/* ==== RAW (Ghidra output, names/globals resolved; not hand-cleaned) ==== */
/* SECTION G  main-executable side: CFieldSocket (SSHApi subclass driving CField / world map)
 * JP SLPM_602.19 (Furokuban). Ghidra decompile with symbols/gp globals resolved. */

/* JP: 0x003bbcf0  SetChrPosSaveState(int)   [SetChrPosSaveState__Fi]  size=0x7c */
void SetChrPosSaveState__Fi(int param_1)

{
  int iVar1;
  
  if (param_1 == 1) {
    iVar1 = chrPosSaveFlag;
    if (chrPosSaveFlag == 0) {
      chrPosSaveFlag = 1;
      iVar1 = chrPosSaveFlag;
    }
  }
  else {
    iVar1 = param_1;
    if ((param_1 == 2) && (iVar1 = chrPosSaveFlag, chrPosSaveFlag == 1)) {
      chrPosSaveFlag = 2;
      iVar1 = chrPosSaveFlag;
    }
  }
  chrPosSaveFlag = iVar1;
  return;
}

/* JP: 0x003bbd70  InitChrPosSave()   [InitChrPosSave__Fv]  size=0x34 */
void * InitChrPosSave__Fv(void)

{
  void *pvVar1;
  
  pvVar1 = memset(&chrPosSaveInfo,0,0x400);
  chrPosSaveFlag = 0;
  return pvVar1;
}

/* JP: 0x003bbdb0  ClrChrPosSave(int)   [ClrChrPosSave__Fi]  size=0x40 */
void * ClrChrPosSave__Fi(int param_1)

{
  void *pvVar1;
  
  pvVar1 = memset(&chrPosSaveInfo + param_1 * 8,0,8);
  return pvVar1;
}

/* JP: 0x003bcfd0  InitFieldSocketM(const char*)   [InitFieldSocketM__FPCc]  size=0x8c */
void InitFieldSocketM__FPCc(undefined4 param_1)

{
  int iVar1;
  long lVar2;
  
  if (m_socket__12CFieldSocket == 0) {
    lVar2 = __nw__FUi(0x6c);
    iVar1 = 0;
    if (lVar2 != 0) {
      iVar1 = __ct__12CFieldSocketFPCc(lVar2,param_1);
    }
  }
  else {
    SetMPS__12CFieldSocketFPCc(m_socket__12CFieldSocket,param_1);
    iVar1 = m_socket__12CFieldSocket;
  }
  m_socket__12CFieldSocket = iVar1;
  SetAPI__6SSHSysFP6SSHApi(sys__6SSHSys,m_socket__12CFieldSocket);
  return;
}

/* JP: 0x003bd1f0  GetMapName(char*, const char*, int)   [GetMapName__FPcPCci]  size=0x74 */
int GetMapName__FPcPCci(char *param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  undefined **ppuVar2;
  
  if (param_3 == 0) {
    ppuVar2 = &_6710;
  }
  else {
    ppuVar2 = &_6711;
  }
  iVar1 = sprintf(param_1,_6712,pDataPath__7SysTool,param_2,ppuVar2);
  return iVar1;
}

/* JP: 0x003bd590  CFieldSocket::WakeMapJump(const char*)   [WakeMapJump__12CFieldSocketFPCc]  size=0x19c */
void WakeMapJump__12CFieldSocketFPCc(int param_1,char *param_2)

{
  int iVar1;
  long lVar2;
  
  if ((fld__12CFieldSocket == 0) || (*(int *)(param_1 + 0x48) != -2)) {
    WakeUp__12CFieldSocketFv(param_1);
    iVar1 = strcmp(param_2,WORLDMAP_NAME);
    if (iVar1 == 0) {
      WorldMapJumpA__12CFieldSocketFiiUi(param_1,0xffffffffffffffff,0,0);
    }
    else {
      if (fld__12CFieldSocket == 0) {
        lVar2 = __nw__FUi(0x2330);
        iVar1 = 0;
        if (lVar2 != 0) {
          iVar1 = __ct__6CFieldFv(lVar2);
        }
        fld__12CFieldSocket = iVar1;
        Init__6CFieldFPCc(fld__12CFieldSocket,param_2);
      }
      else {
        Pause__6CFieldFi(fld__12CFieldSocket,1);
        *(byte *)(fld__12CFieldSocket + 0x18d) =
             *(byte *)(fld__12CFieldSocket + 0x18d) & 0xef | 0x10;
        LoadMPS__12CFieldSocketFPCc(param_1,param_2);
      }
      *(short *)(fld__12CFieldSocket + 0x2a) = (short)*(undefined4 *)(param_1 + 0x48);
    }
  }
  else {
    Sleep__12CFieldSocketFv(param_1);
    SetMPS__12CFieldSocketFPCc(param_1,param_2);
    *(undefined4 *)(param_1 + 0x50) = 0x30;
    Pause__6CFieldFi(fld__12CFieldSocket,1);
    Delete__6CFieldFv(fld__12CFieldSocket);
    fld__12CFieldSocket = 0;
  }
  return;
}

/* JP: 0x003bd730  LayerMan_Init()   [LayerMan_Init__Fv]  size=0x4c */
void LayerMan_Init__Fv(void)

{
  int iVar1;
  
  for (iVar1 = 0; iVar1 < 0xc; iVar1 = iVar1 + 1) {
    (&layerTbl)[iVar1] = (char)iVar1;
  }
  return;
}

/* JP: 0x003bd780  LayerMan_GetLayer(int)   [LayerMan_GetLayer__Fi]  size=0x5c */
uint LayerMan_GetLayer__Fi(uint param_1)

{
  if ((int)param_1 < 0xc) {
    param_1 = (uint)(byte)(&layerTbl)[param_1];
  }
  return param_1;
}

/* JP: 0x003bd7e0  LayerMan_LoadLayer(const unsigned char*)   [LayerMan_LoadLayer__FPCUc]  size=0x5c */
void LayerMan_LoadLayer__FPCUc(int param_1)

{
  int iVar1;
  
  for (iVar1 = 0; iVar1 < 0xc; iVar1 = iVar1 + 1) {
    (&layerTbl)[*(byte *)(param_1 + iVar1)] = (char)iVar1;
  }
  return;
}

/* JP: 0x003bd8e0  CFieldSocket::CFieldSocket(const char*)   [__ct__12CFieldSocketFPCc]  size=0x94 */
int __ct__12CFieldSocketFPCc(int param_1,char *param_2)

{
  *(undefined1 **)(param_1 + 4) = __vt__6SSHApi;
  __ct__7CPolObjFv(param_1 + 8);
  *(undefined1 **)(param_1 + 4) = __vt__12CFieldSocket;
  *(undefined4 *)(param_1 + 0x1c) = 0x4076a0;
  Init__12CFieldSocketFv(param_1);
  if (param_2 != (char *)0x0) {
    strcpy((char *)(param_1 + 0x58),param_2);
  }
  return param_1;
}

/* JP: 0x003bd980  CFieldSocket::SetMPS(const char*)   [SetMPS__12CFieldSocketFPCc]  size=0x40 */
void SetMPS__12CFieldSocketFPCc(int param_1,char *param_2)

{
  if (param_2 != (char *)0x0) {
    strcpy((char *)(param_1 + 0x58),param_2);
  }
  return;
}

/* JP: 0x003bd9c0  CFieldSocket::Init()   [Init__12CFieldSocketFv]  size=0x88 */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void * Init__12CFieldSocketFv(int param_1)

{
  void *pvVar1;
  
  scePrintf(0x401630);
  *(undefined1 *)(param_1 + 0x58) = 0;
  _m_flags__12CFieldSocket = 0;
  *(undefined4 *)(param_1 + 0x50) = 0;
  *(undefined4 *)(param_1 + 0x54) = 0;
  pvVar1 = memset((void *)(param_1 + 0x30),0,0x18);
  *(undefined4 *)(param_1 + 0x68) = 0;
  *(undefined4 *)(param_1 + 0x48) = 0;
  *(undefined4 *)(param_1 + 0x2c) = 0;
  *(undefined4 *)(param_1 + 0x28) = 0;
  *(undefined4 *)(param_1 + 0x24) = 0;
  return pvVar1;
}

/* JP: 0x003bda80  CFieldSocket::~CFieldSocket()   [__dt__12CFieldSocketFv]  size=0xe4 */
int __dt__12CFieldSocketFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 4) = __vt__12CFieldSocket;
    *(undefined4 *)(param_1 + 0x1c) = 0x4076a0;
    scePrintf(0x401650);
    if (*(int *)(param_1 + 0x2c) != 0) {
      __dt__9BufMemoryFv(*(undefined4 *)(param_1 + 0x2c),1);
      *(undefined4 *)(param_1 + 0x2c) = 0;
    }
    m_socket__12CFieldSocket = 0;
    __dt__7CPolObjFv(param_1 + 8,0);
    if (param_1 != 0) {
      *(undefined1 **)(param_1 + 4) = __vt__6SSHApi;
    }
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x003bdbd0  CFieldSocket::preLoad()   [preLoad__12CFieldSocketFv]  size=0xc0 */
undefined4 preLoad__12CFieldSocketFv(int param_1)

{
  undefined4 uVar1;
  long lVar2;
  undefined8 uVar3;
  
  if ((((ulong)m_flags__12CFieldSocket+0x1 & 0xf) >> 2 == 0) ||
     (lVar2 = isPrevApiGone__6SSHSysFv(sys__6SSHSys), lVar2 != 0)) {
    fieldOverlay__12CFieldSocketFv(param_1);
    if (*(int *)(param_1 + 0x50) == 0) {
      DisableReset__6CPauseFv(*(undefined4 *)(app__4CApp + 0x78));
      *(undefined4 *)(param_1 + 0x50) = 1;
      uVar3 = LayerMan_GetLayer__Fi(7);
      changeLayer__16ExpansionTextureFi(uVar3);
      uVar1 = 0;
    }
    else {
      uVar1 = 1;
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

/* JP: 0x003bdc90  CFieldSocket::PreloadOverlay()   [PreloadOverlay__12CFieldSocketFv]  size=0xb4 */
void PreloadOverlay__12CFieldSocketFv(int param_1)

{
  undefined4 uVar1;
  long lVar2;
  
  lVar2 = __nw__FUi(0x10);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = __ct__9BufMemoryFUlUi(lVar2,FIELD_BIN_SIZE,0x80);
  }
  *(undefined4 *)(param_1 + 0x2c) = uVar1;
  PreLoad__7OverlayFP9BufMemoryPCcPFibiPv_viPv
            (sys__6SSHSys + 0x68,*(undefined4 *)(param_1 + 0x2c),0x401688,0x3bd840,1,
             m_socket__12CFieldSocket);
  m_flags__12CFieldSocket+0x1 = m_flags__12CFieldSocket+0x1 & 0xf3 | 4;
  return;
}

/* JP: 0x003bdd50  CFieldSocket::fieldOverlay()   [fieldOverlay__12CFieldSocketFv]  size=0x244 */
undefined4 fieldOverlay__12CFieldSocketFv(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  long lVar3;
  
  iVar2 = *(int *)(param_1 + 0x54);
  if (iVar2 == 2) {
    lVar3 = __nw__FUi(8);
    uVar1 = 0;
    if (lVar3 != 0) {
      uVar1 = __ct__9FldMemoryFv(lVar3);
    }
    sys__9FldMemory = uVar1;
    if (*(int *)(param_1 + 0x2c) != 0) {
      __dt__9BufMemoryFv(*(undefined4 *)(param_1 + 0x2c),1);
      *(undefined4 *)(param_1 + 0x2c) = 0;
    }
    if (*(int *)(param_1 + 0x50) == 2) {
      WakeUp__12CFieldSocketFv(param_1);
      *(undefined4 *)(param_1 + 0x50) = 3;
    }
    iVar2 = strcmp((char *)(param_1 + 0x58),WORLDMAP_NAME);
    if (iVar2 == 0) {
      WorldMapJumpA__12CFieldSocketFiiUi(param_1,0xffffffffffffffff,0,0);
    }
    else {
      lVar3 = __nw__FUi(0x2330);
      iVar2 = 0;
      if (lVar3 != 0) {
        iVar2 = __ct__6CFieldFv(lVar3);
      }
      fld__12CFieldSocket = iVar2;
      Init__6CFieldFPCc(fld__12CFieldSocket,param_1 + 0x58);
      *(short *)(fld__12CFieldSocket + 0x2a) = (short)*(undefined4 *)(param_1 + 0x48);
    }
    *(undefined4 *)(param_1 + 0x54) = 3;
    EnableReset__6CPauseFi(*(undefined4 *)(app__4CApp + 0x78),1);
  }
  else if (iVar2 != 1) {
    if (iVar2 != 0) {
      return 1;
    }
    lVar3 = Load__7OverlayFPCcPFibiPv_viPv(sys__6SSHSys + 0x68,0x401688,0x3bd840,0,param_1);
    if (lVar3 == 0) {
      *(undefined4 *)(param_1 + 0x54) = 1;
    }
    else {
      if (lVar3 != 3) {
        return 0;
      }
      *(undefined4 *)(param_1 + 0x54) = 2;
    }
  }
  return 0;
}

/* JP: 0x003bdfa0  CFieldSocket::fieldLoadCB(int, bool, int)   [fieldLoadCB__12CFieldSocketFibi]  size=0x20 */
void fieldLoadCB__12CFieldSocketFibi(int param_1)

{
  *(undefined4 *)(param_1 + 0x54) = 2;
  return;
}

/* JP: 0x003bdfc0  CFieldSocket::SetSmoothFilter(float, int)   [SetSmoothFilter__12CFieldSocketFfi]  size=0x90 */
void SetSmoothFilter__12CFieldSocketFfi(float param_1,int param_2,undefined4 param_3)

{
  undefined4 uStack_20;
  
  if (*(int *)(param_2 + 0x24) != 0) {
    uStack_20 = param_1;
    if (param_1 < 0.2) {
      uStack_20 = 0.2;
    }
    FilterLevel__12SmoothFilterFf(uStack_20,*(undefined4 *)(param_2 + 0x24));
    FilterAlpha__12SmoothFilterFi(*(undefined4 *)(param_2 + 0x24),param_3);
  }
  return;
}

/* JP: 0x003be050  CFieldSocket::SetBlurFilter(int)   [SetBlurFilter__12CFieldSocketFi]  size=0x48 */
void SetBlurFilter__12CFieldSocketFi(int param_1,undefined4 param_2)

{
  if (*(int *)(param_1 + 0x28) != 0) {
    FilterAlpha__10BlurFilterFi(*(undefined4 *)(param_1 + 0x28),param_2);
  }
  return;
}

/* JP: 0x003be0a0  CFieldSocket::DspFilter()   [DspFilter__12CFieldSocketFv]  size=0xb0 */
void DspFilter__12CFieldSocketFv(int param_1)

{
  undefined8 uVar1;
  
  if (-1 < (long)((ulong)m_flags__12CFieldSocket << 0x39)) {
    m_flags__12CFieldSocket = m_flags__12CFieldSocket & 0xbf | 0x40;
    if (*(int *)(param_1 + 0x28) != 0) {
      uVar1 = LayerMan_GetLayer__Fi(0xc);
      LayerSetUp__10BlurFilterFi(*(undefined4 *)(param_1 + 0x28),uVar1);
    }
    if (*(int *)(param_1 + 0x24) != 0) {
      uVar1 = LayerMan_GetLayer__Fi(0xc);
      LayerSetUp__12SmoothFilterFi(*(undefined4 *)(param_1 + 0x24),uVar1);
    }
  }
  return;
}

/* JP: 0x003be150  CFieldSocket::ClrFilter()   [ClrFilter__12CFieldSocketFv]  size=0x90 */
void ClrFilter__12CFieldSocketFv(int param_1)

{
  if (((ulong)m_flags__12CFieldSocket & 0x7f) >> 6 == 1) {
    m_flags__12CFieldSocket = m_flags__12CFieldSocket & 0xbf;
    if (*(int *)(param_1 + 0x28) != 0) {
      LayerRelease__10BlurFilterFv(*(undefined4 *)(param_1 + 0x28));
    }
    if (*(int *)(param_1 + 0x24) != 0) {
      LayerRelease__12SmoothFilterFv(*(undefined4 *)(param_1 + 0x24));
    }
  }
  return;
}

/* JP: 0x003be1e0  CFieldSocket::InitFilter()   [InitFilter__12CFieldSocketFv]  size=0xe4 */
void InitFilter__12CFieldSocketFv(int param_1)

{
  undefined4 uVar1;
  long lVar2;
  
  if (*(int *)(param_1 + 0x24) == 0) {
    lVar2 = __nw__FUi(0x38);
    uVar1 = 0;
    if (lVar2 != 0) {
      uVar1 = __ct__12SmoothFilterFv(lVar2);
    }
    *(undefined4 *)(param_1 + 0x24) = uVar1;
  }
  if (*(int *)(param_1 + 0x28) == 0) {
    lVar2 = __nw__FUi(0x30);
    uVar1 = 0;
    if (lVar2 != 0) {
      uVar1 = __ct__10BlurFilterFv(lVar2);
    }
    *(undefined4 *)(param_1 + 0x28) = uVar1;
  }
  SetSmoothFilter__12CFieldSocketFfi(0x3f800000,param_1,0x30);
  SetBlurFilter__12CFieldSocketFi(param_1,0x23);
  DspFilter__12CFieldSocketFv(param_1);
  return;
}

/* JP: 0x003be2d0  CFieldSocket::Start()   [Start__12CFieldSocketFv]  size=0x84 */
undefined4 Start__12CFieldSocketFv(int param_1)

{
  if (*(int *)(param_1 + 0x54) == 3) {
    WakeUp__12CFieldSocketFv(param_1);
    if ((*(uint *)(param_1 + 0x50) & 0xf0) != 0x10) {
      *(undefined4 *)(param_1 + 0x50) = 3;
    }
  }
  else {
    *(undefined4 *)(param_1 + 0x50) = 2;
    DelayUpdate__12CFieldSocketFv(param_1);
  }
  return 1;
}

/* JP: 0x003be360  CFieldSocket::WakeUp()   [WakeUp__12CFieldSocketFv]  size=0x340 */
void WakeUp__12CFieldSocketFv(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  long lVar3;
  int iVar4;
  
  if ((long)((ulong)m_flags__12CFieldSocket << 0x3b) < 0) {
    InitFilter__12CFieldSocketFv(param_1);
  }
  else {
    if (camera__4CApp == 0) {
      lVar3 = __nw__FUi(0x3a0);
      iVar1 = 0;
      if (lVar3 != 0) {
        iVar1 = __ct__9GsxCameraFUiUiUiUiUi(lVar3,0,0,0,0x18,0xb);
      }
      camera__4CApp = iVar1;
      if (camera__4CApp == 0) {
        return;
      }
    }
    *(int *)(param_1 + 0x20) = camera__4CApp;
    *(undefined4 *)(*(int *)(param_1 + 0x20) + 0x180) = 0xff000000;
    *(undefined4 *)(*(int *)(param_1 + 0x20) + 0x370) = 0x3f800000;
    *(undefined4 *)(*(int *)(param_1 + 0x20) + 0x374) = 0x46fa0000;
    SetViewMatrix__9GsxCameraFfffff
              (0x44000000,0x3f4ccccd,0x3f6eeeef,0x3f800000,0x4b7fff28,
               *(undefined4 *)(param_1 + 0x20));
    SetCamera__5WorldFUiiP9GsxCamera(0x42bf10,0,0,*(undefined4 *)(param_1 + 0x20));
    SetFFMode__3GsxFibi(0,1,2);
    SetInter30__3GsxFi(1);
    InitFilter__12CFieldSocketFv(param_1);
    Create__6P2ClutFv();
    DelayUpdate__12CFieldSocketFv(param_1);
    for (iVar1 = 0; iVar1 < 2; iVar1 = iVar1 + 1) {
      lVar3 = __nw__FUi(0x38);
      uVar2 = 0;
      if (lVar3 != 0) {
        uVar2 = __ct__12ScreenBrightFv(lVar3);
      }
      *(undefined4 *)(param_1 + iVar1 * 0xc + 0x30) = uVar2;
      *(undefined1 *)(*(int *)(param_1 + iVar1 * 0xc + 0x30) + 0x28) = 0;
      *(undefined2 *)(param_1 + iVar1 * 0xc + 0x3a) = 0;
      *(undefined2 *)(param_1 + iVar1 * 0xc + 0x38) = 0;
      iVar4 = param_1 + iVar1 * 0xc;
      *(byte *)(iVar4 + 0x34) = *(byte *)(iVar4 + 0x34) & 0xf0;
    }
    AddOT__5WorldFiP8VIF1Prim(0x42bf10,0xb,*(undefined4 *)(param_1 + 0x30));
    AddOT__5WorldFiP8VIF1Prim(0x42bf10,0xe,*(undefined4 *)(param_1 + 0x3c));
    SetFader__12CFieldSocketFiii(param_1,1,1,0);
    m_flags__12CFieldSocket = m_flags__12CFieldSocket & 0xef | 0x10;
  }
  return;
}

/* JP: 0x003be6a0  CFieldSocket::DelayUpdate()   [DelayUpdate__12CFieldSocketFv]  size=0x90 */
void DelayUpdate__12CFieldSocketFv(int param_1)

{
  long lVar1;
  int iVar2;
  
  iVar2 = param_1;
  if (param_1 != 0) {
    iVar2 = param_1 + 8;
  }
  lVar1 = Find__7CPollerCFPC7CPolObj(app__4CApp + 0x48,iVar2);
  if (lVar1 == 0) {
    if (param_1 != 0) {
      param_1 = param_1 + 8;
    }
    Entry__7CPollerFP7CPolObjib(app__4CApp + 0x48,param_1,0x80,0);
  }
  return;
}

/* JP: 0x003be730  CFieldSocket::closeInquiry()   [closeInquiry__12CFieldSocketFv]  size=0x1d4 */
undefined4 closeInquiry__12CFieldSocketFv(int param_1)

{
  undefined4 uVar1;
  long lVar2;
  int iVar3;
  
  fld__12CFieldSocket = sys__6CField;
  if (*(int *)(param_1 + 0x50) < 5) {
    iVar3 = param_1;
    if (param_1 != 0) {
      iVar3 = param_1 + 8;
    }
    lVar2 = Find__7CPollerCFPC7CPolObj(app__4CApp + 0x48,iVar3);
    if (lVar2 != 0) {
      iVar3 = param_1;
      if (param_1 != 0) {
        iVar3 = param_1 + 8;
      }
      Dispose__7CPollerFP7CPolObj(app__4CApp + 0x48,iVar3);
    }
    if (fld__12CFieldSocket != 0) {
      ClearSDB__6CFieldFi(fld__12CFieldSocket,0);
      closeInquiry__6CFieldFv(fld__12CFieldSocket);
    }
    *(undefined4 *)(param_1 + 0x50) = 5;
    uVar1 = 1;
  }
  else {
    if (*(int *)(param_1 + 0x50) == 6) {
      Unload__7OverlayFPFibiPv_v(sys__6SSHSys + 0x68,0);
      *(undefined4 *)(param_1 + 0x54) = 0;
      *(undefined4 *)(param_1 + 0x50) = 7;
      Sleep__12CFieldSocketFv(param_1);
      ReleaseCmdMenu__7MenuObjFv();
      if (sys__9FldMemory != 0) {
        __dt__9FldMemoryFv(sys__9FldMemory,1);
      }
    }
    else if (*(int *)(param_1 + 0x50) == 5) {
      if (sys__6CField != 0) {
        if (sys__6CField != 0) {
          (**(code **)(*(int *)(sys__6CField + 0x14) + 8))(sys__6CField,1);
        }
        fld__12CFieldSocket = 0;
      }
      ClrFilter__12CFieldSocketFv(param_1);
      *(undefined4 *)(param_1 + 0x50) = 6;
      return 1;
    }
    uVar1 = 0;
  }
  return uVar1;
}

/* JP: 0x003be910  CFieldSocket::LoadFieldData()   [LoadFieldData__12CFieldSocketFv]  size=0x58 */
void LoadFieldData__12CFieldSocketFv(void)

{
  if (-1 < (long)((ulong)m_flags__12CFieldSocket << 0x38)) {
    m_flags__12CFieldSocket = m_flags__12CFieldSocket & 0x7f | 0x80;
    CreateCmdMenu__7MenuObjFv();
  }
  return;
}

/* JP: 0x003be970  CFieldSocket::Sleep()   [Sleep__12CFieldSocketFv]  size=0x194 */
void Sleep__12CFieldSocketFv(int param_1)

{
  int iVar1;
  
  if ((long)((ulong)m_flags__12CFieldSocket << 0x3b) < 0) {
    for (iVar1 = 0; iVar1 < 2; iVar1 = iVar1 + 1) {
      if (*(int *)(param_1 + iVar1 * 0xc + 0x30) != 0) {
        ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,*(undefined4 *)(param_1 + iVar1 * 0xc + 0x30));
        (**(code **)(*(int *)(*(int *)(param_1 + iVar1 * 0xc + 0x30) + 0x1c) + 0xc))();
        *(undefined4 *)(param_1 + iVar1 * 0xc + 0x30) = 0;
      }
    }
    ClrFilter__12CFieldSocketFv(param_1);
    if (*(int *)(param_1 + 0x24) != 0) {
      (**(code **)(*(int *)(*(int *)(param_1 + 0x24) + 0x1c) + 0xc))();
      *(undefined4 *)(param_1 + 0x24) = 0;
    }
    if (*(int *)(param_1 + 0x28) != 0) {
      (**(code **)(*(int *)(*(int *)(param_1 + 0x28) + 0x1c) + 0xc))();
      *(undefined4 *)(param_1 + 0x28) = 0;
    }
    Release__6P2ClutFv();
    changeLayer__16ExpansionTextureFi(3);
    m_flags__12CFieldSocket = m_flags__12CFieldSocket & 0xef;
  }
  return;
}

/* JP: 0x003beb40  CFieldSocket::WorldMapJump(int, int, unsigned int)   [WorldMapJump__12CFieldSocketFiiUi]  size=0x58 */
void WorldMapJump__12CFieldSocketFiiUi
               (int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  if (*(int *)(param_1 + 0x50) == 4) {
    WorldMapJumpA__12CFieldSocketFiiUi(param_1,param_2,param_3,param_4);
  }
  return;
}

/* JP: 0x003beba0  CFieldSocket::WorldMapJumpA(int, int, unsigned int)   [WorldMapJumpA__12CFieldSocketFiiUi]  size=0x110 */
void WorldMapJumpA__12CFieldSocketFiiUi(int param_1,short param_2,short param_3,undefined4 param_4)

{
  short *psVar1;
  long lVar2;
  undefined8 uVar3;
  undefined4 uStack_10;
  
  lVar2 = __nw__FUi(0x92c);
  uVar3 = 0;
  if (lVar2 != 0) {
    uVar3 = __ct__8worldMapFv(lVar2);
  }
  psVar1 = (short *)GetWorldMapInfo__Fv();
  if (param_2 < 0) {
    param_2 = *psVar1;
    param_3 = psVar1[1];
    uStack_10 = *(undefined4 *)(psVar1 + 2);
  }
  else {
    *psVar1 = param_2;
    psVar1[1] = param_3;
    *(undefined4 *)(psVar1 + 2) = param_4;
    uStack_10 = param_4;
  }
  initialize__8worldMapFiii(uVar3,param_2,param_3,uStack_10);
  *(undefined4 *)(param_1 + 0x50) = 0x10;
  *(int *)(param_1 + 0x48) = (int)uVar3;
  return;
}

/* JP: 0x003becb0  CFieldSocket::isFaderDsp(int)   [isFaderDsp__12CFieldSocketFi]  size=0x4c */
bool isFaderDsp__12CFieldSocketFi(int param_1,int param_2)

{
  return (*(byte *)(param_1 + param_2 * 0xc + 0x34) & 0xf) != 0;
}

/* JP: 0x003bed00  CFieldSocket::GetFaderLevel(int)   [GetFaderLevel__12CFieldSocketFi]  size=0xe8 */
int GetFaderLevel__12CFieldSocketFi(int param_1,int param_2)

{
  int iVar1;
  
  param_1 = param_1 + param_2 * 0xc;
  if ((*(byte *)(param_1 + 0x34) & 0xf) == 0) {
    iVar1 = 0;
  }
  else if (*(short *)(param_1 + 0x3a) == 0) {
    iVar1 = 0x7f;
  }
  else {
    iVar1 = (int)((uint)*(ushort *)(param_1 + 0x38) << 7) / (int)*(short *)(param_1 + 0x3a);
    if (*(short *)(param_1 + 0x3a) == 0) {
      trap(7);
    }
    if ((*(byte *)(param_1 + 0x35) & 1) == 0) {
      iVar1 = 0x7f - iVar1;
    }
  }
  return iVar1;
}

/* JP: 0x003bedf0  CFieldSocket::SetFader(int, int, int)   [SetFader__12CFieldSocketFiii]  size=0x22c */
void SetFader__12CFieldSocketFiii(int param_1,int param_2,byte param_3,int param_4)

{
  byte bVar1;
  int *piVar2;
  undefined1 uVar3;
  long lVar4;
  
  param_1 = param_1 + param_2 * 0xc;
  piVar2 = (int *)(param_1 + 0x30);
  bVar1 = param_3 & 0x7f;
  if ((bVar1 != *(byte *)(param_1 + 0x35)) || (param_4 == 0)) {
    *(byte *)(param_1 + 0x35) = bVar1;
    if (((param_3 & 0x80) == 0) ||
       ((long)*(short *)(param_1 + 0x3a) == (ulong)*(ushort *)(param_1 + 0x38))) {
      *(undefined2 *)(param_1 + 0x38) = 0;
    }
    else {
      if (*(short *)(param_1 + 0x3a) == 0) {
        trap(7);
      }
      *(short *)(param_1 + 0x38) =
           (short)((int)(param_4 * (uint)*(ushort *)(param_1 + 0x38)) /
                  (int)*(short *)(param_1 + 0x3a));
    }
    *(short *)(param_1 + 0x3a) = (short)param_4;
    *(byte *)(param_1 + 0x34) = *(byte *)(param_1 + 0x34) & 0xf0 | 1;
    if (bVar1 < 4) {
      if ((param_3 & 2) == 0) {
        lVar4 = 0;
      }
      else {
        lVar4 = 0xffffff;
      }
      *(uint *)(*piVar2 + 0x34) = (uint)((ulong)(lVar4 << 0x28) >> 0x28);
    }
    if (bVar1 == 7) {
      *(undefined4 *)(*piVar2 + 0x34) = 0;
    }
    if (param_4 == 0) {
      if ((param_3 & 1) == 0) {
        uVar3 = 0;
      }
      else {
        uVar3 = 0x80;
      }
      *(undefined1 *)(*piVar2 + 0x28) = uVar3;
      if ((param_3 & 1) == 0) {
        *(byte *)(param_1 + 0x34) = *(byte *)(param_1 + 0x34) & 0xf0;
      }
    }
  }
  return;
}

/* JP: 0x003bf020  CFieldSocket::ClrFader(int)   [ClrFader__12CFieldSocketFi]  size=0x7c */
void ClrFader__12CFieldSocketFi(int param_1,int param_2)

{
  param_1 = param_1 + param_2 * 0xc;
  if ((*(byte *)(param_1 + 0x34) & 0xf) != 0) {
    *(byte *)(param_1 + 0x34) = *(byte *)(param_1 + 0x34) & 0xf0 | 2;
  }
  *(undefined2 *)(param_1 + 0x3a) = 0;
  *(undefined2 *)(param_1 + 0x38) = 0;
  return;
}

/* JP: 0x003bf0a0  CFieldSocket::PauseFader(int)   [PauseFader__12CFieldSocketFi]  size=0x70 */
void PauseFader__12CFieldSocketFi(int param_1,int param_2)

{
  *(byte *)(param_1 + 0x34) = *(byte *)(param_1 + 0x34) & 0xef | (param_2 == 0) << 4;
  *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xef | (param_2 == 0) << 4;
  return;
}

/* JP: 0x003bf110  CFieldSocket::UpdateFader(unsigned int)   [UpdateFader__12CFieldSocketFUi]  size=0x1e4 */
void UpdateFader__12CFieldSocketFUi(int param_1,int param_2)

{
  short sVar1;
  int *piVar2;
  int iVar3;
  long lVar4;
  long lVar5;
  int iVar6;
  
  piVar2 = (int *)(param_1 + 0x30);
  iVar6 = 0;
  do {
    if (1 < iVar6) {
      return;
    }
    if (-1 < (long)((ulong)*(byte *)(piVar2 + 1) << 0x3b)) {
      sVar1 = *(short *)((int)piVar2 + 10);
      lVar5 = (long)sVar1;
      if ((ulong)*(ushort *)(piVar2 + 2) == (long)*(short *)((int)piVar2 + 10)) {
        if ((*(byte *)(piVar2 + 1) & 0xf) != 2) goto LAB_003bf2c0;
        *(undefined1 *)((int)piVar2 + 5) = 0;
        *(byte *)(piVar2 + 1) = *(byte *)(piVar2 + 1) & 0xf0;
      }
      lVar4 = (long)(int)((uint)*(ushort *)(piVar2 + 2) + param_2);
      if (lVar5 <= (int)((uint)*(ushort *)(piVar2 + 2) + param_2)) {
        *(byte *)(piVar2 + 1) = *(byte *)(piVar2 + 1) & 0xf0 | *(byte *)((int)piVar2 + 5) & 1;
        lVar4 = lVar5;
      }
      *(short *)(piVar2 + 2) = (short)lVar4;
      if ((*(byte *)((int)piVar2 + 5) & 1) == 0) {
        if (lVar4 == lVar5) {
          iVar3 = 0;
        }
        else {
          if (lVar5 == 0) {
            trap(7);
          }
          iVar3 = 0x80 - ((int)lVar4 << 7) / (int)sVar1;
        }
      }
      else if (lVar4 == lVar5) {
        iVar3 = 0x80;
      }
      else {
        iVar3 = ((int)lVar4 << 7) / (int)sVar1;
        if (lVar5 == 0) {
          trap(7);
        }
      }
      if ((int)(uint)*(byte *)((int)piVar2 + 5) >> 1 == 3) {
        iVar3 = iVar3 >> 1;
      }
      *(char *)(*piVar2 + 0x28) = (char)iVar3;
    }
LAB_003bf2c0:
    iVar6 = iVar6 + 1;
    piVar2 = piVar2 + 3;
  } while( true );
}

/* JP: 0x003bf300  CFieldSocket::CommandMenu(int, int)   [CommandMenu__12CFieldSocketFii]  size=0x37c */
void CommandMenu__12CFieldSocketFii(int param_1,ushort param_2,uint param_3)

{
  int iVar1;
  long lVar2;
  long lVar3;
  undefined8 uVar4;
  ushort uVar5;
  uint uStack_10;
  
  lVar2 = GetFieldGS__Fv();
  uVar5 = param_2 & 0xff;
  if (uVar5 == 0x10) {
    SaveScriptRegister__12CFieldSocketFv(param_1);
    lVar2 = __nw__FUi(0x184);
    uVar4 = 0;
    if (lVar2 != 0) {
      uVar4 = __ct__10dataAccessFv(lVar2);
    }
    initialize__10dataAccessFQ210dataAccess10ACCESSMODEPFiPv_vPv(uVar4,0,0x3bfa40,param_1);
    *(int *)(param_1 + 0x68) = (int)uVar4;
    SetFader__12CFieldSocketFiii(param_1,1,1,200);
    Pause__6CFieldFi(fld__12CFieldSocket,0);
  }
  else if (uVar5 == 6) {
    SaveScriptRegister__12CFieldSocketFv(param_1);
    lVar2 = __nw__FUi(0x17f8);
    iVar1 = 0;
    if (lVar2 != 0) {
      iVar1 = __ct__7CmdMenuFsPFiPvP7CmdMenu_iPv(lVar2,8,0x3bf740,param_1);
    }
    *(short *)(iVar1 + 0x4a) = (short)param_3;
  }
  else if (uVar5 == 5) {
    SaveScriptRegister__12CFieldSocketFv(param_1);
    lVar3 = __nw__FUi(0x1a78);
    uVar4 = 0;
    if (lVar3 != 0) {
      uVar4 = __ct__15CmdMenuTutorialFv(lVar3);
    }
    uVar5 = 0;
    uStack_10 = param_3;
    if ((lVar2 != 0) && (((int)(uint)*(ushort *)((int)lVar2 + 0x44) >> 2 & 3U) == 0)) {
      uStack_10 = param_3 | 2;
    }
    if ((uStack_10 & 1) != 0) {
      uVar5 = 2;
    }
    if ((uStack_10 & 2) == 0) {
      uVar5 = uVar5 | 1;
    }
    *(ushort *)((int)uVar4 + 0x4a) = uVar5;
    StartTutorial__15CmdMenuTutorialFsPFiPvP7CmdMenu_iPv
              (uVar4,(ushort)(uStack_10 >> 0x10) & 0xff,0x3bf8d0,param_1);
  }
  else if (uVar5 == 4) {
    SaveScriptRegister__12CFieldSocketFv(param_1);
    lVar2 = __nw__FUi(0x17f8);
    iVar1 = 0;
    if (lVar2 != 0) {
      iVar1 = __ct__7CmdMenuFsPFiPvP7CmdMenu_iPv(lVar2,0,0x3bf740,param_1);
    }
    uVar5 = 0;
    if ((param_3 & 1) != 0) {
      uVar5 = 2;
    }
    if ((param_3 & 2) == 0) {
      uVar5 = uVar5 | 1;
    }
    *(ushort *)(iVar1 + 0x4a) = uVar5;
  }
  else if (lVar2 != 0) {
    *(ushort *)((int)lVar2 + 0x44) = param_2;
  }
  return;
}

/* JP: 0x003bf680  CFieldSocket::CheckCmdMenu()   [CheckCmdMenu__12CFieldSocketFv]  size=0xb8 */
bool CheckCmdMenu__12CFieldSocketFv(undefined4 param_1)

{
  bool bVar1;
  int iVar2;
  long lVar3;
  
  iVar2 = GetFieldGS__Fv();
  bVar1 = (*(ushort *)(iVar2 + 0x44) & 0xf) == 0;
  if (bVar1) {
    lVar3 = ChkSavePoint__6CFieldFv(fld__12CFieldSocket);
    CommandMenu__12CFieldSocketFii(param_1,4,-1 < lVar3);
  }
  return bVar1;
}

/* JP: 0x003bf740  CFieldSocket::cbMenu(int, void*, CmdMenu*)   [cbMenu__12CFieldSocketFiPvP7CmdMenu]  size=0x184 */
undefined4 cbMenu__12CFieldSocketFiPvP7CmdMenu(undefined4 param_1,undefined8 param_2,int param_3)

{
  switch(param_1) {
  case 0:
    if (sys__8FldTimer != 0) {
      *(byte *)(sys__8FldTimer + 0x61) = *(byte *)(sys__8FldTimer + 0x61) & 0xf7 | 8;
    }
    *(byte *)(fld__12CFieldSocket + 0x191) = *(byte *)(fld__12CFieldSocket + 0x191) & 0xbf | 0x40;
    break;
  case 1:
    Clr__6CFieldFv(fld__12CFieldSocket);
    break;
  case 2:
    Dsp__6CFieldFv(fld__12CFieldSocket);
    *(byte *)(fld__12CFieldSocket + 0x18d) = *(byte *)(fld__12CFieldSocket + 0x18d) & 0xf3 | 4;
    break;
  case 3:
    Pause__6CFieldFi(fld__12CFieldSocket,1);
    break;
  case 5:
    if (sys__6CField != 0) {
      *(byte *)(sys__6CField + 0x18d) = *(byte *)(sys__6CField + 0x18d) & 0xdf;
    }
    break;
  case 6:
    Pause__6CFieldFi(fld__12CFieldSocket,0);
    *(undefined1 *)(param_3 + 0x3d) = 0x11;
  }
  return 1;
}

/* JP: 0x003bf8d0  CFieldSocket::cbMenu2(int, void*, CmdMenu*)   [cbMenu2__12CFieldSocketFiPvP7CmdMenu]  size=0x164 */
undefined4 cbMenu2__12CFieldSocketFiPvP7CmdMenu(undefined4 param_1)

{
  switch(param_1) {
  case 0:
    if (sys__8FldTimer != 0) {
      *(byte *)(sys__8FldTimer + 0x61) = *(byte *)(sys__8FldTimer + 0x61) & 0xf7 | 8;
    }
    break;
  case 1:
    Clr__6CFieldFv(fld__12CFieldSocket);
    *(byte *)(fld__12CFieldSocket + 0x191) = *(byte *)(fld__12CFieldSocket + 0x191) & 0xbf | 0x40;
    break;
  case 2:
    Dsp__6CFieldFv(fld__12CFieldSocket);
    *(byte *)(fld__12CFieldSocket + 0x18d) = *(byte *)(fld__12CFieldSocket + 0x18d) & 0xf3 | 4;
    break;
  case 3:
    Pause__6CFieldFi(fld__12CFieldSocket,1);
    break;
  case 5:
    if (sys__6CField != 0) {
      *(byte *)(sys__6CField + 0x18d) = *(byte *)(sys__6CField + 0x18d) & 0xdf;
    }
    break;
  case 6:
    Pause__6CFieldFi(fld__12CFieldSocket,0);
  }
  return 1;
}

/* JP: 0x003bfa40  CFieldSocket::cbSave(int, void*)   [cbSave__12CFieldSocketFiPv]  size=0x114 */
void cbSave__12CFieldSocketFiPv(int param_1)

{
  if (param_1 == 4) {
    SetFader__12CFieldSocketFiii(m_socket__12CFieldSocket,1,1,0);
    SetFFMode__3GsxFibi(0,1,2);
    Dsp__6CFieldFv(fld__12CFieldSocket);
    *(byte *)(fld__12CFieldSocket + 0x18d) = *(byte *)(fld__12CFieldSocket + 0x18d) & 0xf3 | 4;
    SetFader__12CFieldSocketFiii(m_socket__12CFieldSocket,1,0,200);
    *(undefined4 *)(m_socket__12CFieldSocket + 0x50) = 0x20;
  }
  else if ((((param_1 != 3) && (param_1 != 5)) && (param_1 == 0)) && (sys__8FldTimer != 0)) {
    *(byte *)(sys__8FldTimer + 0x61) = *(byte *)(sys__8FldTimer + 0x61) & 0xf7 | 8;
  }
  return;
}

/* JP: 0x003bfb60  CFieldSocket::Polling()   [Polling__12CFieldSocketFv]  size=0x8dc */
undefined8 Polling__12CFieldSocketFv(int param_1)

{
  char *__dest;
  int iVar1;
  long lVar2;
  undefined8 uVar3;
  uint uVar4;
  undefined1 auStack_110 [64];
  undefined1 auStack_d0 [64];
  undefined1 auStack_90 [68];
  int iStack_4c;
  int iStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  void *pvStack_3c;
  void *pvStack_38;
  uint uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  int iStack_28;
  int iStack_24;
  int iStack_20;
  undefined4 uStack_1c;
  int iStack_18;
  undefined4 uStack_14;
  int iStack_10;
  
  iStack_20 = sys__6SSHSys;
  uStack_30 = *(undefined4 *)(sys__6SSHSys + 0x20);
  uStack_2c = uStack_30;
  uStack_14 = uStack_30;
  iStack_10 = param_1;
  if ((2 < *(int *)(param_1 + 0x54)) ||
     ((fieldOverlay__12CFieldSocketFv(param_1), m_pSDB__12CFieldSocket != 0 &&
      (*(int *)(iStack_10 + 0x50) != 2)))) {
    if ((*(uint *)(iStack_10 + 0x50) & 0xf0) == 0x30) {
      if ((sys__6CField == 0) &&
         (WakeMapJump__12CFieldSocketFPCc(iStack_10,iStack_10 + 0x58),
         *(int *)(iStack_10 + 0x50) != 0x10)) {
        *(undefined4 *)(iStack_10 + 0x50) = 3;
      }
    }
    else {
      if ((long)((ulong)m_flags__12CFieldSocket << 0x3b) < 0) {
        UpdateFader__12CFieldSocketFUi(iStack_10,uStack_14);
        if (*(int *)(iStack_10 + 0x50) < 4) {
          *(undefined4 *)(iStack_10 + 0x50) = 4;
        }
        if (*(int *)(iStack_10 + 0x54) != 3) {
          return 0;
        }
        uVar4 = *(uint *)(iStack_10 + 0x50) & 0xf0;
        if (uVar4 == 0x20) {
          if ((ulong)*(ushort *)(iStack_10 + 0x44) != (long)*(short *)(iStack_10 + 0x46)) {
            return 0;
          }
          Pause__6CFieldFi(fld__12CFieldSocket,1);
          *(undefined4 *)(iStack_10 + 0x50) = 4;
          return 0;
        }
        if (uVar4 == 0x10) {
          uVar4 = *(uint *)(iStack_10 + 0x50) & 0xf;
          if (uVar4 == 1) {
            fld__12CFieldSocket = 0;
            __dest = (char *)GetSavedMpsName__Fi(0);
            strcpy(__dest,WORLDMAP_NAME);
            Sleep__12CFieldSocketFv(iStack_10);
            SetFFMode__3GsxFibi(0,1,1);
            start__8worldMapFv(*(undefined4 *)(iStack_10 + 0x48));
            *(undefined4 *)(iStack_10 + 0x50) = 4;
            return 0;
          }
          if (uVar4 != 0) {
            return 0;
          }
          if (fld__12CFieldSocket != 0) {
            Delete__6CFieldFv(fld__12CFieldSocket);
            m_socket__12CFieldSocket = iStack_10;
          }
          *(int *)(iStack_10 + 0x50) = *(int *)(iStack_10 + 0x50) + 1;
          return 0;
        }
        if ((m_flags__12CFieldSocket & 0xf) == 1) {
          if (*(int *)(fldScript__12CFieldSocket + 0x1c) == 0) {
            uStack_34 = 0;
          }
          else {
            uStack_34 = (uint)(*(byte *)(*(int *)(fldScript__12CFieldSocket + 0x1c) + 0x58) >> 6 ==
                              3);
          }
          if (uStack_34 != 0) {
            m_flags__12CFieldSocket = m_flags__12CFieldSocket & 0xf0 | 3;
          }
        }
        if ((m_flags__12CFieldSocket & 0xf) == 2) {
          GetMapName__FPcPCci(auStack_90,iStack_10 + 0x58,0);
          lVar2 = Find__12CSndBufCacheFPCci(auStack_90,2);
          if ((lVar2 != 0) && (iVar1 = (int)lVar2, *(char *)(iVar1 + 1) == '\x02')) {
            lVar2 = __nw__FUi(0x10);
            iStack_18 = 0;
            if (lVar2 != 0) {
              iStack_18 = __ct__9BufMemoryFUlUi(lVar2,*(undefined4 *)(iVar1 + 8),0x40);
            }
            pvStack_38 = *(void **)(iStack_18 + 4);
            memcpy(pvStack_38,*(void **)(iVar1 + 4),(long)*(int *)(iVar1 + 8));
            FlushCache(0);
            LoadScriptB__7CScriptFPcP9BufMemory(fldScript__12CFieldSocket,auStack_90,iStack_18);
            m_flags__12CFieldSocket = m_flags__12CFieldSocket & 0xf0 | 3;
          }
        }
        if (((m_flags__12CFieldSocket & 0xf) == 8) && (pFldPreLoadMSC != 0)) {
          m_flags__12CFieldSocket = m_flags__12CFieldSocket & 0xf0 | 9;
        }
        if ((m_flags__12CFieldSocket & 0xf) == 9) {
          GetMapName__FPcPCci(auStack_d0,iStack_10 + 0x58,0);
          LoadScriptB__7CScriptFPcP9BufMemory(fldScript__12CFieldSocket,auStack_d0,pFldPreLoadMSC);
          pFldPreLoadMSC = 0;
          fFldPreLoadMSC = 0;
          m_flags__12CFieldSocket = m_flags__12CFieldSocket & 0xf0 | 3;
        }
        if ((m_flags__12CFieldSocket & 0xf) == 3) {
          if (m_pSDB__12CFieldSocket == 0) {
            GetMapName__FPcPCci(auStack_110,iStack_10 + 0x58,1);
            if (fFldPreLoadMPS == '\0') {
              lVar2 = Find__12CSndBufCacheFPCci(auStack_110,1);
              if (lVar2 == 0) {
                lVar2 = __nw__FUi(0x24);
                iVar1 = 0;
                if (lVar2 != 0) {
                  iVar1 = __ct__6CSTGDBFv(lVar2);
                }
                m_pSDB__12CFieldSocket = iVar1;
                Load__6CSTGDBFPCc(m_pSDB__12CFieldSocket,auStack_110);
              }
              else {
                iVar1 = (int)lVar2;
                if (*(char *)(iVar1 + 1) == '\x02') {
                  lVar2 = __nw__FUi(0x10);
                  uVar3 = 0;
                  if (lVar2 != 0) {
                    uVar3 = __ct__9BufMemoryFUlUi(lVar2,*(undefined4 *)(iVar1 + 8),0x40);
                  }
                  pvStack_3c = *(void **)((int)uVar3 + 4);
                  memcpy(pvStack_3c,*(void **)(iVar1 + 4),(long)*(int *)(iVar1 + 8));
                  FlushCache(0);
                  lVar2 = __nw__FUi(0x24);
                  iVar1 = 0;
                  if (lVar2 != 0) {
                    iVar1 = __ct__6CSTGDBFv(lVar2);
                  }
                  m_pSDB__12CFieldSocket = iVar1;
                  LoadCB__6CSTGDBFP9BufMemoryi(m_pSDB__12CFieldSocket,uVar3,0);
                }
              }
              m_flags__12CFieldSocket = m_flags__12CFieldSocket & 0xf0 | 4;
            }
            else if (pFldPreLoadMPS != 0) {
              lVar2 = __nw__FUi(0x24);
              iVar1 = 0;
              if (lVar2 != 0) {
                iVar1 = __ct__6CSTGDBFv(lVar2);
              }
              m_pSDB__12CFieldSocket = iVar1;
              LoadCB__6CSTGDBFP9BufMemoryi(m_pSDB__12CFieldSocket,pFldPreLoadMPS,0);
              pFldPreLoadMPS = 0;
              fFldPreLoadMPS = '\0';
              m_flags__12CFieldSocket = m_flags__12CFieldSocket & 0xf0 | 4;
            }
          }
        }
        else if ((3 < (m_flags__12CFieldSocket & 0xf)) && (m_pSDB__12CFieldSocket != 0)) {
          iStack_24 = m_pSDB__12CFieldSocket;
          uStack_44 = *(undefined4 *)(m_pSDB__12CFieldSocket + 0x14);
          iStack_28 = m_pSDB__12CFieldSocket;
          iStack_4c = *(int *)(m_pSDB__12CFieldSocket + 0x14);
          iStack_48 = iStack_4c;
          uStack_40 = uStack_44;
          uStack_1c = uStack_44;
          if (iStack_4c == 2) {
            ClearSDB__6CFieldFi(fld__12CFieldSocket,0);
            InitSDB__6CFieldFP6CSTGDB(fld__12CFieldSocket,m_pSDB__12CFieldSocket);
            if ((m_flags__12CFieldSocket & 0xf) == 4) {
              Restart__6CFieldFv(fld__12CFieldSocket);
              StartScript__7CScriptFv(fldScript__12CFieldSocket);
            }
            m_pSDB__12CFieldSocket = 0;
            m_flags__12CFieldSocket = m_flags__12CFieldSocket & 0xf0;
          }
        }
        if ((*(int *)(iStack_10 + 0x68) != 0) &&
           ((ulong)*(ushort *)(iStack_10 + 0x44) == (long)*(short *)(iStack_10 + 0x46))) {
          Clr__6CFieldFv(fld__12CFieldSocket);
          start__10dataAccessFQ210dataAccess9STARTMODEii(*(undefined4 *)(iStack_10 + 0x68),1,0,0);
          *(undefined4 *)(iStack_10 + 0x68) = 0;
          ClrFader__12CFieldSocketFi(iStack_10,1);
          SetFFMode__3GsxFibi(0,1,1);
        }
      }
      if (sys__6CField != 0) {
        CheckResetPause__6CFieldFv(sys__6CField);
      }
    }
  }
  return 0;
}

/* JP: 0x003c0440  CFieldSocket::LoadMPS(const char*)   [LoadMPS__12CFieldSocketFPCc]  size=0x1f0 */
undefined4 LoadMPS__12CFieldSocketFPCc(int param_1,char *param_2)

{
  int iVar1;
  long lVar2;
  undefined1 auStack_120 [256];
  int iStack_20;
  char *pcStack_10;
  
  iStack_20 = param_1;
  pcStack_10 = param_2;
  strcpy((char *)(param_1 + 0x58),param_2);
  GetMapName__FPcPCci(auStack_120,iStack_20 + 0x58,0);
  if (fldScript__12CFieldSocket == 0) {
    lVar2 = __nw__FUi(0x28);
    iVar1 = 0;
    if (lVar2 != 0) {
      iVar1 = __ct__7CScriptFv(lVar2);
    }
    fldScript__12CFieldSocket = iVar1;
    Create__7CScriptFPUciii(fldScript__12CFieldSocket,0,0x200,0x400,5);
    LinkA__6CFieldFv(fld__12CFieldSocket);
    LoadScriptRegister__12CFieldSocketFv(iStack_20);
  }
  else {
    EndScene__7CScriptFv(fldScript__12CFieldSocket);
    if (((ulong)*(ushort *)(iStack_20 + 0x44) == (long)*(short *)(iStack_20 + 0x46)) &&
       ((m_flags__12CFieldSocket+0x1 & 3) == 0)) {
      SetFader__12CFieldSocketFiii(iStack_20,1,1,0);
    }
  }
  if (fFldPreLoadMSC == '\0') {
    lVar2 = Find__12CSndBufCacheFPCci(auStack_120,2);
    if (lVar2 == 0) {
      LoadScript__7CScriptFPcPUc(fldScript__12CFieldSocket,auStack_120,0);
      m_flags__12CFieldSocket = m_flags__12CFieldSocket & 0xf0 | 1;
    }
    else {
      m_flags__12CFieldSocket = m_flags__12CFieldSocket & 0xf0 | 2;
    }
  }
  else {
    m_flags__12CFieldSocket = m_flags__12CFieldSocket & 0xf0 | fFldPreLoadMSC + 7U & 0xf;
  }
  return 1;
}

/* JP: 0x003c0630  CFieldSocket::CacheMPS(const char*)   [CacheMPS__12CFieldSocketFPCc]  size=0xa0 */
void CacheMPS__12CFieldSocketFPCc(undefined8 param_1,undefined4 param_2)

{
  long lVar1;
  undefined1 auStack_a0 [144];
  undefined4 uStack_10;
  
  uStack_10 = param_2;
  GetMapName__FPcPCci(auStack_a0,param_2,1);
  lVar1 = Find__12CSndBufCacheFPCci(auStack_a0,1);
  if (lVar1 == 0) {
    Clear__12CSndBufCacheFv();
    Load__12CSndBufCacheFPCciiPFiP9BufMemoryiPcPv_iPv(auStack_a0,1,0,0,0);
    GetMapName__FPcPCci(auStack_a0,uStack_10,0);
    Load__12CSndBufCacheFPCciiPFiP9BufMemoryiPcPv_iPv(auStack_a0,2,0,0,0);
  }
  return;
}

/* JP: 0x003c06d0  CFieldSocket::ReloadMPS()   [ReloadMPS__12CFieldSocketFv]  size=0x94 */
void ReloadMPS__12CFieldSocketFv(int param_1)

{
  undefined4 uVar1;
  long lVar2;
  undefined1 auStack_90 [128];
  int iStack_10;
  
  iStack_10 = param_1;
  GetMapName__FPcPCci(auStack_90,param_1 + 0x58,1);
  lVar2 = __nw__FUi(0x24);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = __ct__6CSTGDBFv(lVar2);
  }
  m_pSDB__12CFieldSocket = uVar1;
  Load__6CSTGDBFPCc(m_pSDB__12CFieldSocket,auStack_90);
  m_flags__12CFieldSocket = m_flags__12CFieldSocket & 0xf0 | 5;
  return;
}

/* JP: 0x003c0770  CFieldSocket::SetWarp(int)   [SetWarp__12CFieldSocketFi]  size=0x128 */
void SetWarp__12CFieldSocketFi(int param_1,int param_2)

{
  if (param_2 < 0) {
    if ((param_2 == -1) && ((m_flags__12CFieldSocket+0x1 & 3) == 1)) {
      m_flags__12CFieldSocket+0x1 = m_flags__12CFieldSocket+0x1 & 0xfc | 2;
    }
  }
  else {
    m_flags__12CFieldSocket+0x1 = m_flags__12CFieldSocket+0x1 & 0xfc | 1U - (char)param_2 & 3;
  }
  if ((m_flags__12CFieldSocket+0x1 & 3) == 2) {
    SetFader__12CFieldSocketFiii(param_1,1,3,0);
    *(undefined4 *)(*(int *)(param_1 + 0x3c) + 0x34) = 0xffffff;
  }
  else if ((m_flags__12CFieldSocket+0x1 & 3) == 0) {
    SetFader__12CFieldSocketFiii(param_1,1,4,1);
  }
  return;
}

/* JP: 0x003c08a0  InitFieldSaveData()   [InitFieldSaveData__Fv]  size=0x28 */
void InitFieldSaveData__Fv(void)

{
  Initialize__14CFieldSaveDataFv();
  InitChrPosSave__Fv();
  return;
}

/* JP: 0x003c0960  SceneInit(int)   [SceneInit__Fi]  size=0xbc */
void SceneInit__Fi(int param_1)

{
  int iVar1;
  
  iVar1 = GetFieldGS__Fv();
  *(undefined4 *)(iVar1 + 0xc) = 0;
  *(undefined4 *)(iVar1 + 8) = 0;
  *(undefined4 *)(iVar1 + 4) = 0;
  *(undefined4 *)(iVar1 + 0x58) = 0;
  *(undefined4 *)(iVar1 + 0x54) = 0;
  RestoreTreasureFlag__Fv();
  SetSceneInit__10BtlSaveSecFib
            ((&iscInitMode)[param_1],**(short **)(sm_pSubstance__15SaveMenuSection + 0xc) != 0);
  return;
}

/* JP: 0x003c0a20  GetWorldMapInfo()   [GetWorldMapInfo__Fv]  size=0x64 */
int GetWorldMapInfo__Fv(void)

{
  long lVar1;
  int iVar2;
  
  lVar1 = FindChunk__14CFieldSaveDataFPCc(sys__14CFieldSaveData,0x4016e0);
  if (lVar1 == 0) {
    iVar2 = 0;
  }
  else {
    iVar2 = (int)lVar1 + 4;
  }
  return iVar2;
}

/* JP: 0x003c0a90  GetSavedMpsName(int)   [GetSavedMpsName__Fi]  size=0x78 */
int GetSavedMpsName__Fi(int param_1)

{
  long lVar1;
  int iVar2;
  
  lVar1 = GetFieldGS__Fv();
  if (lVar1 == 0) {
    iVar2 = 0;
  }
  else if (param_1 == 0) {
    iVar2 = (int)lVar1 + 0x10;
  }
  else {
    iVar2 = (int)lVar1 + 0x20;
  }
  return iVar2;
}

/* JP: 0x003c1140  CFieldSocket::LoadScriptRegister()   [LoadScriptRegister__12CFieldSocketFv]  size=0xd0 */
void * LoadScriptRegister__12CFieldSocketFv(void)

{
  void *pvVar1;
  int iVar2;
  
  pvVar1 = (void *)FindChunk__14CFieldSaveDataFPCc(sys__14CFieldSaveData,0x4016f0);
  if ((pvVar1 != (void *)0x0) && (fldScript__12CFieldSocket != 0)) {
    pvVar1 = memcpy(*(void **)(*(int *)(fldScript__12CFieldSocket + 0x1c) + 0x40),
                    (void *)((int)pvVar1 + 0x10),
                    (long)(int)((uint)*(ushort *)(*(int *)(fldScript__12CFieldSocket + 0x1c) + 0x52)
                               << 2));
    for (iVar2 = 0; iVar2 < 0x200; iVar2 = iVar2 + 1) {
    }
  }
  return pvVar1;
}

/* JP: 0x003c1280  CFieldSocket::SaveScriptRegister()   [SaveScriptRegister__12CFieldSocketFv]  size=0x148 */
void SaveScriptRegister__12CFieldSocketFv(int param_1)

{
  short sVar1;
  uint uVar2;
  long lVar3;
  int iVar4;
  undefined1 auStack_20 [16];
  int iStack_10;
  
  if (fldScript__12CFieldSocket != 0) {
    iStack_10 = param_1;
    lVar3 = GetFieldGS__Fv();
    if (lVar3 != 0) {
      iVar4 = (int)lVar3;
      memset((void *)(iVar4 + 0x10),0,0x10);
      strcpy((char *)(iVar4 + 0x10),(char *)(iStack_10 + 0x58));
      if ((fld__12CFieldSocket != 0) &&
         (lVar3 = GetCtrlModel__6CFieldFv(fld__12CFieldSocket), lVar3 != 0)) {
        __ct__7FVectorFRC7FVector(auStack_20,(int)lVar3 + 0x10);
        SetShortPos__FPsP7FVector(iVar4 + 0x48,auStack_20);
        sVar1 = GetDir__11CFieldModelFv(lVar3);
        *(short *)(iVar4 + 0x4e) = sVar1 + 1;
      }
    }
    lVar3 = FindChunk__14CFieldSaveDataFPCc(sys__14CFieldSaveData,0x4016f0);
    if (lVar3 != 0) {
      uVar2 = (uint)*(ushort *)(*(int *)(fldScript__12CFieldSocket + 0x1c) + 0x52);
      if (0x200 < uVar2) {
        uVar2 = 0x200;
      }
      memcpy((void *)((int)lVar3 + 0x10),
             *(void **)(*(int *)(fldScript__12CFieldSocket + 0x1c) + 0x40),(long)(int)(uVar2 << 2));
    }
  }
  return;
}

/* JP: 0x003c13d0  CFieldSocket::SetGameOverType(int, int)   [SetGameOverType__12CFieldSocketFii]  size=0x194 */
void SetGameOverType__12CFieldSocketFii(undefined8 param_1,uint param_2,int param_3)

{
  int iVar1;
  ushort uVar2;
  undefined2 uVar3;
  
  iVar1 = GetFieldBattleInfo__Fv();
  if (param_2 == 0xffffffff) {
    if (param_3 < 2) {
      if (param_3 == 0) {
        uVar3 = 0;
      }
      else {
        uVar3 = 0xffff;
      }
      *(undefined2 *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x29e) = uVar3;
    }
  }
  else if (param_3 == 3) {
    *(undefined2 *)(iVar1 + 8) = 0;
    *(undefined2 *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x29e) =
         *(undefined2 *)(iVar1 + 6);
  }
  else if (param_3 == 2) {
    *(short *)(iVar1 + 8) = (short)param_2 + 1;
    *(short *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x29c) = (short)param_2;
  }
  else {
    uVar2 = (ushort)(1 << (param_2 & 0x1f));
    if (param_3 == 0) {
      uVar2 = *(ushort *)(iVar1 + 6) & ~uVar2;
    }
    else {
      uVar2 = *(ushort *)(iVar1 + 6) | uVar2;
    }
    *(ushort *)(iVar1 + 6) = uVar2;
    *(ushort *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x29e) = uVar2;
  }
  return;
}

/* JP: 0x003c1ed0  CFieldSocket::Polling()   [@8@Polling__12CFieldSocketFv]  size=0x8 */
undefined8 _8_Polling__12CFieldSocketFv(int param_1)

{
  char *__dest;
  int iVar1;
  long lVar2;
  undefined8 uVar3;
  uint uVar4;
  undefined1 auStack_110 [64];
  undefined1 auStack_d0 [64];
  undefined1 auStack_90 [68];
  int iStack_4c;
  int iStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  void *pvStack_3c;
  void *pvStack_38;
  uint uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  int iStack_28;
  int iStack_24;
  int iStack_20;
  undefined4 uStack_1c;
  int iStack_18;
  undefined4 uStack_14;
  int iStack_10;
  
  iStack_10 = param_1 + -8;
  iStack_20 = sys__6SSHSys;
  uStack_30 = *(undefined4 *)(sys__6SSHSys + 0x20);
  uStack_2c = uStack_30;
  uStack_14 = uStack_30;
  if ((2 < *(int *)(param_1 + 0x4c)) ||
     ((fieldOverlay__12CFieldSocketFv(iStack_10), m_pSDB__12CFieldSocket != 0 &&
      (*(int *)(iStack_10 + 0x50) != 2)))) {
    if ((*(uint *)(iStack_10 + 0x50) & 0xf0) == 0x30) {
      if ((sys__6CField == 0) &&
         (WakeMapJump__12CFieldSocketFPCc(iStack_10,iStack_10 + 0x58),
         *(int *)(iStack_10 + 0x50) != 0x10)) {
        *(undefined4 *)(iStack_10 + 0x50) = 3;
      }
    }
    else {
      if ((long)((ulong)m_flags__12CFieldSocket << 0x3b) < 0) {
        UpdateFader__12CFieldSocketFUi(iStack_10,uStack_14);
        if (*(int *)(iStack_10 + 0x50) < 4) {
          *(undefined4 *)(iStack_10 + 0x50) = 4;
        }
        if (*(int *)(iStack_10 + 0x54) != 3) {
          return 0;
        }
        uVar4 = *(uint *)(iStack_10 + 0x50) & 0xf0;
        if (uVar4 == 0x20) {
          if ((ulong)*(ushort *)(iStack_10 + 0x44) != (long)*(short *)(iStack_10 + 0x46)) {
            return 0;
          }
          Pause__6CFieldFi(fld__12CFieldSocket,1);
          *(undefined4 *)(iStack_10 + 0x50) = 4;
          return 0;
        }
        if (uVar4 == 0x10) {
          uVar4 = *(uint *)(iStack_10 + 0x50) & 0xf;
          if (uVar4 == 1) {
            fld__12CFieldSocket = 0;
            __dest = (char *)GetSavedMpsName__Fi(0);
            strcpy(__dest,WORLDMAP_NAME);
            Sleep__12CFieldSocketFv(iStack_10);
            SetFFMode__3GsxFibi(0,1,1);
            start__8worldMapFv(*(undefined4 *)(iStack_10 + 0x48));
            *(undefined4 *)(iStack_10 + 0x50) = 4;
            return 0;
          }
          if (uVar4 != 0) {
            return 0;
          }
          if (fld__12CFieldSocket != 0) {
            Delete__6CFieldFv(fld__12CFieldSocket);
            m_socket__12CFieldSocket = iStack_10;
          }
          *(int *)(iStack_10 + 0x50) = *(int *)(iStack_10 + 0x50) + 1;
          return 0;
        }
        if ((m_flags__12CFieldSocket & 0xf) == 1) {
          if (*(int *)(fldScript__12CFieldSocket + 0x1c) == 0) {
            uStack_34 = 0;
          }
          else {
            uStack_34 = (uint)(*(byte *)(*(int *)(fldScript__12CFieldSocket + 0x1c) + 0x58) >> 6 ==
                              3);
          }
          if (uStack_34 != 0) {
            m_flags__12CFieldSocket = m_flags__12CFieldSocket & 0xf0 | 3;
          }
        }
        if ((m_flags__12CFieldSocket & 0xf) == 2) {
          GetMapName__FPcPCci(auStack_90,iStack_10 + 0x58,0);
          lVar2 = Find__12CSndBufCacheFPCci(auStack_90,2);
          if ((lVar2 != 0) && (iVar1 = (int)lVar2, *(char *)(iVar1 + 1) == '\x02')) {
            lVar2 = __nw__FUi(0x10);
            iStack_18 = 0;
            if (lVar2 != 0) {
              iStack_18 = __ct__9BufMemoryFUlUi(lVar2,*(undefined4 *)(iVar1 + 8),0x40);
            }
            pvStack_38 = *(void **)(iStack_18 + 4);
            memcpy(pvStack_38,*(void **)(iVar1 + 4),(long)*(int *)(iVar1 + 8));
            FlushCache(0);
            LoadScriptB__7CScriptFPcP9BufMemory(fldScript__12CFieldSocket,auStack_90,iStack_18);
            m_flags__12CFieldSocket = m_flags__12CFieldSocket & 0xf0 | 3;
          }
        }
        if (((m_flags__12CFieldSocket & 0xf) == 8) && (pFldPreLoadMSC != 0)) {
          m_flags__12CFieldSocket = m_flags__12CFieldSocket & 0xf0 | 9;
        }
        if ((m_flags__12CFieldSocket & 0xf) == 9) {
          GetMapName__FPcPCci(auStack_d0,iStack_10 + 0x58,0);
          LoadScriptB__7CScriptFPcP9BufMemory(fldScript__12CFieldSocket,auStack_d0,pFldPreLoadMSC);
          pFldPreLoadMSC = 0;
          fFldPreLoadMSC = 0;
          m_flags__12CFieldSocket = m_flags__12CFieldSocket & 0xf0 | 3;
        }
        if ((m_flags__12CFieldSocket & 0xf) == 3) {
          if (m_pSDB__12CFieldSocket == 0) {
            GetMapName__FPcPCci(auStack_110,iStack_10 + 0x58,1);
            if (fFldPreLoadMPS == '\0') {
              lVar2 = Find__12CSndBufCacheFPCci(auStack_110,1);
              if (lVar2 == 0) {
                lVar2 = __nw__FUi(0x24);
                iVar1 = 0;
                if (lVar2 != 0) {
                  iVar1 = __ct__6CSTGDBFv(lVar2);
                }
                m_pSDB__12CFieldSocket = iVar1;
                Load__6CSTGDBFPCc(m_pSDB__12CFieldSocket,auStack_110);
              }
              else {
                iVar1 = (int)lVar2;
                if (*(char *)(iVar1 + 1) == '\x02') {
                  lVar2 = __nw__FUi(0x10);
                  uVar3 = 0;
                  if (lVar2 != 0) {
                    uVar3 = __ct__9BufMemoryFUlUi(lVar2,*(undefined4 *)(iVar1 + 8),0x40);
                  }
                  pvStack_3c = *(void **)((int)uVar3 + 4);
                  memcpy(pvStack_3c,*(void **)(iVar1 + 4),(long)*(int *)(iVar1 + 8));
                  FlushCache(0);
                  lVar2 = __nw__FUi(0x24);
                  iVar1 = 0;
                  if (lVar2 != 0) {
                    iVar1 = __ct__6CSTGDBFv(lVar2);
                  }
                  m_pSDB__12CFieldSocket = iVar1;
                  LoadCB__6CSTGDBFP9BufMemoryi(m_pSDB__12CFieldSocket,uVar3,0);
                }
              }
              m_flags__12CFieldSocket = m_flags__12CFieldSocket & 0xf0 | 4;
            }
            else if (pFldPreLoadMPS != 0) {
              lVar2 = __nw__FUi(0x24);
              iVar1 = 0;
              if (lVar2 != 0) {
                iVar1 = __ct__6CSTGDBFv(lVar2);
              }
              m_pSDB__12CFieldSocket = iVar1;
              LoadCB__6CSTGDBFP9BufMemoryi(m_pSDB__12CFieldSocket,pFldPreLoadMPS,0);
              pFldPreLoadMPS = 0;
              fFldPreLoadMPS = '\0';
              m_flags__12CFieldSocket = m_flags__12CFieldSocket & 0xf0 | 4;
            }
          }
        }
        else if ((3 < (m_flags__12CFieldSocket & 0xf)) && (m_pSDB__12CFieldSocket != 0)) {
          iStack_24 = m_pSDB__12CFieldSocket;
          uStack_44 = *(undefined4 *)(m_pSDB__12CFieldSocket + 0x14);
          iStack_28 = m_pSDB__12CFieldSocket;
          iStack_4c = *(int *)(m_pSDB__12CFieldSocket + 0x14);
          iStack_48 = iStack_4c;
          uStack_40 = uStack_44;
          uStack_1c = uStack_44;
          if (iStack_4c == 2) {
            ClearSDB__6CFieldFi(fld__12CFieldSocket,0);
            InitSDB__6CFieldFP6CSTGDB(fld__12CFieldSocket,m_pSDB__12CFieldSocket);
            if ((m_flags__12CFieldSocket & 0xf) == 4) {
              Restart__6CFieldFv(fld__12CFieldSocket);
              StartScript__7CScriptFv(fldScript__12CFieldSocket);
            }
            m_pSDB__12CFieldSocket = 0;
            m_flags__12CFieldSocket = m_flags__12CFieldSocket & 0xf0;
          }
        }
        if ((*(int *)(iStack_10 + 0x68) != 0) &&
           ((ulong)*(ushort *)(iStack_10 + 0x44) == (long)*(short *)(iStack_10 + 0x46))) {
          Clr__6CFieldFv(fld__12CFieldSocket);
          start__10dataAccessFQ210dataAccess9STARTMODEii(*(undefined4 *)(iStack_10 + 0x68),1,0,0);
          *(undefined4 *)(iStack_10 + 0x68) = 0;
          ClrFader__12CFieldSocketFi(iStack_10,1);
          SetFFMode__3GsxFibi(0,1,1);
        }
      }
      if (sys__6CField != 0) {
        CheckResetPause__6CFieldFv(sys__6CField);
      }
    }
  }
  return 0;
}

/* JP: 0x003c1ee0  CFieldSocket::~CFieldSocket()   [@8@__dt__12CFieldSocketFv]  size=0x8 */
int _8___dt__12CFieldSocketFv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -8;
  if (iVar1 != 0) {
    *(undefined1 **)(param_1 + -4) = __vt__12CFieldSocket;
    *(undefined4 *)(param_1 + 0x14) = 0x4076a0;
    scePrintf(0x401650);
    if (*(int *)(param_1 + 0x24) != 0) {
      __dt__9BufMemoryFv(*(undefined4 *)(param_1 + 0x24),1);
      *(undefined4 *)(param_1 + 0x24) = 0;
    }
    m_socket__12CFieldSocket = 0;
    __dt__7CPolObjFv(param_1,0);
    if (iVar1 != 0) {
      *(undefined1 **)(param_1 + -4) = __vt__6SSHApi;
    }
    if (0 < param_2) {
      __dl__FPv(iVar1);
    }
  }
  return iVar1;
}
