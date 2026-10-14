/* Section I -- cleaned Ghidra output of the retail (SLUS_210.41) system-level routines that differ from the JP demo.
 * Names: SLUS_210.41 (this section named the ones marked NEW).  Offsets are from `this`; globals are given by address.
 * Analysis output, not compilable source.  Diff notes: notes/I/us_delta.md.  Rust: port/crates/sh2_core/src/{boot,ssh_sys,fileio}.rs. */

/* ---- 0x00239430  inlined sceScfGetLanguage (NEW: replaces the SDK call) ----------------------------------------- */
uint GetLanguageRaw(void)
{
    u32 osd[4];
    GetOsdConfigParam(osd);
    if (!IsToolRegionT())                        /* 0x2393f0: rom0:ROMVER region letter == 'T' (DTL/tool unit) */
        return ((osd[0] >> 13) & 7) == 0 ? (osd[0] >> 4) & 1 : (osd[0] >> 16) & 0x1f;
    return g_tool_language;                      /* 0x42d7b4 */
}

/* ---- 0x003ed470  GetLanguage: 0x10 + JP index ------------------------------------------------------------------- */
int GetLanguage(void)
{
    switch (GetLanguageRaw()) {
    case 0: return 0x11;  case 1: return 0x12;  case 2: return 0x14;
    case 3: return 0x17;  case 4: return 0x15;  case 5: return 0x16;
    default: return 0x12;
    }
}

/* ---- 0x003edc40  SSHSys::GetFullPathName -------------------------------------------------------------------------- */
void GetFullPathName__6SSHSysFPcPc(char *buf, const char *name)
{
    sprintf(buf, "%s%s", pDataPath /*0x43fcb8, ""*/, name);
    if (FileIOLib_SearchFile(ourFio, buf) == 0)
        SysTool_AddLocalPath(buf, SaveMenuSection::sm_pSubstance->data[0x18] /* language dir index, default 1 */);  /* JP: SSHSys::Language */
}
void PathInit__6SSHSysFv(void) { pDataPath = ""; SSHSys_Language = GetLanguage(); /* byte @0x43fdfc, never read */ }

/* ---- 0x003ee6a0  SSHSys::PollingApi ------------------------------------------------------------------------------- */
void PollingApi__6SSHSysFv(SSHSys *this)
{
    if (pSysSE && Sdrv_GetStatus(sys__Sdrv, sysReq) == 3) { Sdrv_CloseHandle(sys__Sdrv, sysReq); delete pSysSE; pSysSE = 0; }
    if (this->initPhase != 0) return;
    if (g_stream_fade_state /*0x459aeb*/ != 0) StepStreamFade();                      /* NEW */
    switch (this->request) {                                                          /* +0x36 */
    case 0x10:                                                                        /* field */
        InitFieldSocketM(this->fieldName /*+0x58*/);  this->request = 0;  break;
    case 0x40:                                                                        /* NEW: return to title */
        ReleaseResidentA();  ReleaseResidentB();                                      /* 0x3f7790 / 0x3f77c0 */
        ReturnToTitle();                                                              /* 0x415b20 -> opening() */
        this->request = 0;  this->btlResult[0] = 0;  break;                           /* +0x54 */
    case 0x30:                                                                        /* game over */
        ReleaseResidentA();  ReleaseResidentB();                                      /* NEW */
        SSHSys_SetAPI(this, new GameOver());                                          /* 0x64 bytes (JP 0x54) */
        this->request = 0;  this->btlResult[0] = 0;  break;
    case 0x21: {                                                                      /* battle go */
        InitBtlSocket();
        BtlSocket *b = ourBtlSocket;  b->cb = cbBattle;  b->owner = this;            /* +0x198 / +0x194 (JP +0x164/+0x160) */
        u8 f0 = g_btl_flag0 /*0x459ae8*/;
        if (f0 == 2) g_btl_flag0 = 0;
        b->flag_18d = f0 & 1;  b->flag_18e = g_btl_flag1;  b->flag_18f = g_btl_flag2;
        if (f0 == 0) BtlSocket_SetBtlBGMNumber(b, this->param.bgm);                   /* +0x48 */
        else         BtlSocket_SetBtlBgmStream(b, g_btl_bgm_stream_a, g_btl_bgm_stream_b);   /* 0x368b10 NEW */
        b->battle_no = this->param.w0;                                                /* +0x190 */
        memcpy(&b->party_set /*+0x2c*/, &MENU->data[this->param.pc[0] * 0x20 + 0x84], 0x20);   /* party-set record instead of SetPC() */
        if (this->param.monster_set == 0) BtlSocket_SetMonsterSetById(b, this->param.regdat_id);      /* 0x3687d0 NEW */
        else BtlSocket_SetMonsterSet(b, this->param.monster_set, GetRegDat(0x35, this->param.regdat_id, -1));   /* JP kind 0x2f */
        this->request = 0;  break; }
    }
}

/* ---- 0x003ee3f0  SSHSys::cbBattleA(code, arg, arg3) ---------------------------------------------------------------- */
int cbBattleA__6SSHSysFii(SSHSys *this, int code, int arg, int arg3)
{
    if (code == 0) {
        u8 r = ourBtlSocket->result /*+0x1a0*/ & 3;
        this->btlResult[0] = 2;
        if (r == 2 || r == 3) { this->btlResult[1] = 0xff; this->request = 0x10; SetChrPosSaveState(2); }
        else if (r == 1) {
            this->btlResult[1] = 0;
            if (this->btlResult[2] == 0) {
                this->request = 0x30;
                if (g_btl_flag0 && g_btl_bgm_stream_a && g_btl_bgm_stream_b) g_stream_fade_state = 1;   /* NEW */
                FieldPreLoadCancel();
            } else { this->request = 0x10; SetChrPosSaveState(2); }
        } else if (r == 0) {
            SetChrPosSaveState(2);
            if (arg3 == 1) FUN_003f5dc0();                                           /* NEW */
            this->btlResult[1] = 1;  this->request = 0x10;
        }
        this->btlResult[2] = 0;
    } else if (code == 1) FieldPreLoad(this->fieldName /*+0x58*/);
    return 1;
}

/* ---- 0x003eda50  NEW  SSHSys::StepStreamFade: deferred 500 ms fade-out of the custom battle BGM stream ---------------- */
void StepStreamFade__6SSHSysFv(void)
{
    switch (g_stream_fade_state) {                                                   /* 0x459aeb */
    case 1: Sdrv_FadeStream(sdrv, g_btl_bgm_stream_a, 0, 0, 500);  g_stream_fade_time = GetTimer();  g_stream_fade_state = 2;  return;
    case 2: if (GetTimer() - g_stream_fade_time < 500) return;  g_stream_fade_state = 3;  /* fallthrough */
    case 3: if (Sdrv_CloseStream(sdrv, g_btl_bgm_stream_a, 1) != -1) {
                g_btl_bgm_stream_a = g_btl_bgm_stream_b = 0;  g_btl_flag0 = 0;  g_stream_fade_state = 0; }
    }
}

/* ---- 0x003ee600 / 0x3ee620 / 0x3ee670 / 0x3eeb10  NEW small members -------------------------------------------------- */
void RequestTitle__6SSHSysFv(SSHSys *this)                         { this->request = 0x40; }
void SetBattleFlags__6SSHSysFUcUcUc(u8 a, u8 b, u8 c)             { g_btl_flag0 = a; g_btl_flag1 = b; g_btl_flag2 = c; }
void SetBattleBgmStream__6SSHSysFii(int a, int b)                  { g_btl_bgm_stream_a = a; g_btl_bgm_stream_b = b; }
int  GetDiscNo__6SSHSysFv(void)                                    { return g_disc_no; /* gp-0x7d80, parsed by InitPkb(first) */ }

/* ---- 0x00228770  FileIOLib::ResetSystem (JP: only cleared the run flag and waited for myFp) -------------------------------- */
int ResetSystem__9FileIOLibFv(FileIOLib *this)
{
    this->run = 0;                                               /* +0x13924 (JP +0x13920) */
    while (myFp != 0) CThread_Wait(app, 10);
    if (g_LSDPlayer) {                                           /* NEW: quiesce the movie player before the reset */
        LSDPlayer_Pause(g_LSDPlayer);  LSDPlayer_FUN_003c91c0(g_LSDPlayer);
        while (!LSDPlayer_Reset(g_LSDPlayer)) VCALL(g_LSDPlayer, 0xc /*Polling*/);
    }
    sceDevctl("hdd0:" /*0x432648*/, 0x5003, 0, 0, 0, 0);          /* HDD cache flush; JP did this from the PowerOff callback */
    return 1;
}
long SetHddDeviceName__9FileIOLibFPCc(const char *dev)           /* 0x228540: no sceCdPOffCallback(PowerOffCallBack) any more */
{ long r = checkHddStatus(dev); if (r == 0) strcpy(HDDDevName, dev); return r; }

/* ---- 0x00228880  FileIOLib::InitPkb(first) -- first part -------------------------------------------------------------------- */
int InitPkb__9FileIOLibFv(FileIOLib *this, long first)
{
    if (sceCdDiskReady(1) == 6) return 0;
    u8 pvd[0x800];  memset(pvd, 0, sizeof pvd);
    if (sceCdDiskReady(0) == 2 && sceCdRead(0x10, 1, pvd, &mode) != 0) {
        sceCdSync(0);
        if (first == 0) {                                        /* swap/retry: verify */
            if (strncmp(g_volume_label /*0x42cf40*/, pvd + 0x28, 0x15) != 0) { g_disk_state = 3; g_disk_result = -1; return 0; }
            int n; sscanf(pvd + 0xbe, "%d", &n);
            if (n != g_disc_no)                                  { g_disk_state = 3; g_disk_result = -1; return 0; }
        } else {                                                 /* first: remember */
            memcpy(g_volume_label, pvd + 0x28, 0x15);  sscanf(pvd + 0xbe, "%d", &g_disc_no);
        }
        /* ... sceCdLayerSearchFile("\\PKFINFO.TBL;1"), read, copy header+entries, resolve LBAs -- unchanged ... */
    } else if (first == 0) g_disk_result = -1;
    return 0;
}

/* ---- 0x00409cc0  CApp::Run (differences only; skeleton as in notes/A/CApp.md) ------------------------------------------ */
void Run__4CAppFv(CApp *this)
{
    /* ... */
    for (;;) {
        int t0 = RCNT3 - HCount;                                          /* NEW: frame start */
        if (camera && !g_no_draw /*0x43fed4*/) { World_BeginUpdate(); WorldRender(); World_EndUpdate(); }
        CPoller_Polling(&this->sysPoller);  if (!(pause->flags & 1)) { CPoller_Polling(&p0); CPoller_Polling(&p1); }
        if (m_pAppFunc) m_pAppFunc();
        if (!g_no_draw) { WorldGetPacket(); ScreenBright_Draw(m_pBright); }
        GsKickFinish();                                                   /* DrawSync + FINISH packet (JP: sceGsSyncPath) */
        /* DelayDelete drain, screenshot slots (capTbl @0x45e3b0) ... */
        if (GsxGetVSyncCount() < m_syncCount) {                           /* fast frame */
            if (!g_no_draw) { while (GsxGetVSyncCount() < m_syncCount - 1) ; DrawSync(); /* stats */ }
            while (m_flags & 0x10) ;  VSync(m_syncCount);
        } else {                                                          /* slow frame */
            GsWaitFinish();
            if (!g_no_draw) { u32 e = RCNT3 - HCount - t0; if (e > 0x289) e = 0x2a8;
                              do { GsKickFinish(); GsWaitFinish(); } while ((RCNT3 - HCount) - t0 < e);
                              DrawSync(); /* stats */  GsxForceFlip();  GsWaitFinish(); }
            GsxClrVSyncCount();
        }
        HCount = RCNT3;  UpdatePolBreakState();
        if (pause->flags & 8) DoReset();
    }
}
void SetNoDraw__4CAppFUc(u8 v) { g_no_draw = v; }                         /* 0x409ca0 NEW */
