/* Cleaned retail CFieldSocket (SLUS_210.41 0x003f3680..). JP reference: ../G/CFieldSocket.c. Accessors: _types_retail.h (CS_*). */
#include "_types_retail.h"

/* US 0x003f4dc0 InitFieldSocketCB(void (*cb)(void*), void *arg) - called by CDMYStage::Polling (title/opening) */
void InitFieldSocketCB(void (*cb)(void *), void *arg) {
    if (!m_socket) { m_socket = CFieldSocket_ctor0(new(0x74)); }            /* default ctor 0x003f5590 */
    CS_START_CB(m_socket) = cb; CS_START_ARG(m_socket) = arg;               /* 0x003f6fc0 */
    SSHSys_SetAPI(g_SSHSys, m_socket);
}

/* US 0x003f52a0 CFieldSocket::WakeMapJump(const char *map)  (JP 0x003bd590) */
void CFieldSocket_WakeMapJump(CFieldSocket *s, const char *map) {
    if (CS_START_CB(s) != 0) return;                                        /* RETAIL: wait while a start callback is pending */
    if (fld && CS_ENTRY(s) == -2) {                                         /* leave to a fresh socket for another map */
        CFieldSocket_Sleep(s); CFieldSocket_SetMPS(s, map);
        SetChrPosSaveState(-1);                                             /* RETAIL */
        CS_PHASE(s) = 0x30; CField_Pause(fld, 1); CField_Delete(fld); fld = 0; return; }
    CFieldSocket_WakeUp(s);
    if (strcmp(map, WORLDMAP_NAME) == 0) { CFieldSocket_WorldMapJumpA(s, -1, 0, 0); return; }
    if (!fld) { fld = CField_ctor(new(0x2770)); CField_Init(fld, map); }    /* 0x2770 (JP 0x2330) */
    else { CScript_ResetEvent(fldScript); CScript_SetEventMagic(fldScript, 0);                                 /* RETAIL */
           CField_Pause(fld, 1); CF_FLAGS179(fld) = (CF_FLAGS179(fld) & ~2) | 2; CF_CTRL_MODE(fld) = 1;       /* displayed, control latched */
           Retail_FieldPreLoad_stub(fld); CFieldSocket_LoadMPS(s, map); }
    CF_ENTRY_ID(fld) = (s16)CS_ENTRY(s);
}

/* US 0x003f7800 CFieldSocket::LoadMPS(const char *map)  (JP 0x003c0440) */
int CFieldSocket_LoadMPS(CFieldSocket *s, const char *map) {
    strcpy(CS_MAPNAME(s), map);  GetMapName(path, CS_MAPNAME(s), 0 /*MSC*/);
    if (!fldScript) { fldScript = CScript_ctor(new(0x28)); CScript_Create(fldScript, 0, 0x200, 0x600, 5); CField_LinkA(fld); CFieldSocket_LoadScriptRegister(s); }
    else { CScript_EndScene(fldScript);
           if (UpdateFader slot1 idle (cur == total) && !(m_flags >> 7 & 0x1ff) && !CFieldSocket_isFaderDsp(s, 1)) CFieldSocket_SetFader(s, 1, 1, 0);  /* RETAIL: black immediately */ }
    if (pFldPreLoadMSC_flag == 0) { if (!CSndBufCache_Find(path, 2)) { CScript_LoadScript(fldScript, path, 0); m_flags = (m_flags & 0xfff0) | 1; } else m_flags = (m_flags & 0xfff0) | 2; }
    else m_flags = (m_flags & 0xfff0) | ((pFldPreLoadMSC_flag + 7) & 0xf);
    return 1;
}

/* US 0x003f7000 CFieldSocket::Polling()  (JP 0x003bfb60) - differences only; the MSC/MPS loading sub-machine (m_flags low nibble 1/2/3/4/8/9) is identical */
int CFieldSocket_Polling(CFieldSocket *s) {
    u32 dt = SSHSys_GetFrameDelta();
    if (CS_OVERLAY_STATE(s) <= 2) { CFieldSocket_fieldOverlay(s); if (!(m_pSDB && CS_PHASE(s) != 2)) return 0; }
    if ((CS_PHASE(s) & 0xf0) == 0x30) { if (!fld) { CFieldSocket_WakeMapJump(s, CS_MAPNAME(s)); if ((CS_PHASE(s) & 0xf0) != 0x10) CS_PHASE(s) = 3; } return 0; }
    if (m_flags & 0x10) {                                                   /* awake */
        CFieldSocket_UpdateFader(s, dt);
        if (CS_PHASE(s) < 4) { CS_PHASE(s) = 4; if (CS_START_CB(s)) CS_START_CB(s)(CS_START_ARG(s)); }     /* RETAIL: start callback */
        if (CS_OVERLAY_STATE(s) != 3) return 0;
        switch (CS_PHASE(s) & 0xf0) {
        case 0x40:                                                          /* RETAIL: loading screen finished? */
            if (LoadingGadget_isReady(g_loadGadget)) {
                if (!CFieldSocket_isFaderDsp(s, 1)) CFieldSocket_SetFader(s, 1, 1, 400);
                LoadingGadget_dtor(g_loadGadget); g_loadGadget = 0;
                CField_InitSDB(fld, m_pSDB);
                if (CS_PHASE(s) & 1) { CField_Restart(fld); CScript_StartScript(fldScript); } else CScript_flags(fldScript) &= ~0x20;
                CS_PHASE(s) = 4; m_pSDB = 0; }
            break;
        case 0x20: if (fader1.cur != fader1.total) return 0; CField_Pause(fld, 1); CS_PHASE(s) = 4; return 0;
        case 0x10:                                                          /* world map hand-over */
            switch (CS_PHASE(s) & 0xf) {
            case 8: if (!LoadingGadget_isReady(g_loadGadget)) return 0;     /* RETAIL sub-state: wait, then create the world map */
                    if (!CFieldSocket_isFaderDsp(s, 1)) CFieldSocket_SetFader(s, 1, 1, 400); LoadingGadget_dtor(g_loadGadget); g_loadGadget = 0;
                    { u16 *wm = GetWorldMapSection(); worldMap_initialize(CS_ENTRY(s), wm[0], wm[1], *(u32 *)(wm + 2)); } CS_PHASE(s) = 0x10; return 0;
            case 1: fld = 0; strcpy(GetSavedMpsName(0), WORLDMAP_NAME); CFieldSocket_Sleep(s); Gsx_SetFFMode(0, 1, 1); worldMap_start(CS_ENTRY(s)); CS_PHASE(s) = 4; return 0;
            case 0: if (fld) { CField_Delete(fld); m_socket = s; } CS_PHASE(s)++; return 0;
            default: return 0; }
        }
        if (m_flags & 0xf) { /* MSC states 1,2 (cache hit) ,8,9 (preloaded) -> LoadScriptB; state 3 -> create/load CSTGDB (Load or LoadCB) -> state 4 */ }
        else if (m_flags & 0xf > 3 && m_pSDB && m_pSDB->state == 2) {
            fldScript->flags |= 0x20; CField_ClearSDB(fld, 0);
            CS_PHASE(s) = (m_flags & 0xf) == 4 ? 0x41 : 0x40;               /* RETAIL: go through the loading-screen phase instead of InitSDB right here */
            g_loadGadget = LoadingGadget_ctor(new(0x2c)); LoadingGadget_start(g_loadGadget, GetSavedMapIndex()); m_flags &= 0xf0; }
        if (CS_DATAACCESS(s) && fader1.cur == fader1.total) { CField_Clr(fld); dataAccess_start(CS_DATAACCESS(s), 1, 0, 0); CS_DATAACCESS(s) = 0; CFieldSocket_ClrFader(s, 1); Gsx_SetFFMode(0, 1, 1); }
    }
    if (fld) CField_CheckResetPause(fld);
    return 0;
}

/* SSHSys::PollingApi request handlers that concern the field (US 0x003ee6a0): 0x10 -> InitFieldSocketM(name at SSHSys+0x58); 0x30 -> free timer + music, new GameOver(100), SetAPI(0);
 * 0x40 (retail) -> free timer (0x3f7790) + music (0x3f77c0), start the title/opening stage (0x415b20), clear +0x36 and +0x54. */
