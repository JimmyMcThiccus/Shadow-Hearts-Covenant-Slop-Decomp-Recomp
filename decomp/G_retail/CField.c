/* Cleaned retail CField (SH2US_FIELD.BIN) - lifecycle, polling, camera selection. Retail-only parts are marked RETAIL.
 * JP reference: ../G/CField.c.  Notes: notes/G_retail/CField.md.  Accessors: _types_retail.h. */
#include "_types_retail.h"

/* ---------------------------------------------------------------- construction */
/* US 0x004f06e0 CField::CField  (JP 0x004a2b00) */
CField *CField_ctor(CField *f) {
    CScriptEx_ctor(f);                                   /* 0x0029b0b0 */
    CF_VTBL(f) = &__vt__6CField;                         /* 0x0043e460 */
    FVector_ctor(&CF_CAM_POS(f)); FVector_ctor(&CF_CAM_ANGLE(f)); FVector_ctor(&CF_PLAYER_POS(f));
    BufMemory_ctor((u8 *)f + 0x2140); FVector_ctor((u8 *)f + 0x2150); FVector_ctor((u8 *)f + 0x2160);
    memset((u8 *)f + 0x24, 0, 0x12d8);                   /* JP: 0xe98 */
    CF_STATE(f) = 1;
    for (int i = 0; i < 0x30; i++) *(s32 *)CF_OBJSE(f, i) = -1;      /* slot stride 0x2c (JP 0x28) */
    if (g_pMusic == 0) {                                  /* iGpffff8464 */
        CF_FLAGS179(f) = (CF_FLAGS179(f) & ~0x10) | 0x10;
        g_pMusic = new_CMusic(0xac);                      /* JP 0x94 */
        g_pMusic->cb = Retail_cbMusicA /*0x0051cbb0*/; g_pMusic->owner = f;
    }
    CF_SE(f) = new_CSe(8); CSe_vfunc3(CF_SE(f), 8, 0x20, 0); CSe_SetCallback(CF_SE(f), cbReadBGM_0x0051d190, f);
    return f;
}

/* US 0x004f0ad0 CField::Init(const char *map)  (JP 0x004a30b0) */
int CField_Init(CField *f, const char *map) {
    sys__6CField = f;                                    /* 0x0043ff34 */
    CField_preLoad(f);                                    /* 0x004f0b60 (JP LinkA-like: CScriptEx_Entry-less) */
    CField_Start(f);                                      /* 0x004f0ba0 */
    MenuObj_CreateField();
    CF_TEAMCHG(f) = FldTeamChange_ctor(new(0x88));        /* RETAIL: created here (0x00520c40) */
    if (map && *map) CField_MapJump(f, map);              /* 0x004fc630 */
    return 1;
}

/* US 0x004f0ba0 CField::Start (JP 0x004a3240) */
int CField_Start(CField *f) {
    if (!CF_PAD(f)) { CF_PAD(f) = CPad_ctor(new(0x18), 0); CPad_Enable(CF_PAD(f)); RF(void *, 8, CF_PAD(f)) = &prio_normal; }
    if (!CF_CAMERA(f)) { CF_CAMERA(f) = CFieldCamera_pre(new(0xf0)); CFieldCamera_Init(CF_CAMERA(f)); }   /* 0xf0 (JP 0xd0) */
    CScriptEx_Entry(f, 0x88);                             /* JP 0x70 */
    CF_FLAGS179(f) = (CF_FLAGS179(f) & ~2) | 2;           /* displayed (JP flags_18d.4) */
    return 1;
}

/* ---------------------------------------------------------------- InitSDB */
/* US 0x004f7210 CField::InitSDB(CSTGDB *db)  (JP 0x004ab860) - everything a map needs, in order */
int CField_InitSDB(CField *f, CSTGDB *db) {
    RF(int, 0x8f8, f) = -1; RF(int, 0x8fc, f) = 0;
    CF_FLAGS178(f) = (CF_FLAGS178(f) & 0xe3) | 0x1c;      /* JP: | 0x14 */
    if (CF_CTRL_MODE(f) == 1) CF_CTRL_MODE(f) = 2;
    m_pSTGDB = db;                                        /* 0x0043ff30 */
    FieldPreLoad_clear(f);                                /* 0x004fcba0 stub */
    CF_FLAGS17A(f) &= 0xdf; RF(u8, 0x8e7, f) = 0;
    CF_CAMERA_ID(f) = FieldCameraID(-2);
    if (CF_TEAMCHG(f)) FldTeamChange_Clr(CF_TEAMCHG(f));
    if (g_pFldTimer) FldTimer_Mask(g_pFldTimer, 0);       /* inlined: byte +0x61 &= ~8 */
    if (g_pHud) *(s16 *)(*(u8 **)((u8 *)g_pHud + 0x1c) + 0x58) = 5;
    int ctrl_shown = (ctrl = CField_GetCtrlModel(f)) && (RF(u8, 0x90, ctrl) & 0xc);
    for (i = 0; i < CF_MODEL_COUNT(f); i++) if (CF_MODEL(f, i)) { CFieldModel_ClearShadow(CF_MODEL(f, i)); CFieldModel_ClearModel(CF_MODEL(f, i)); }
    if (!CF_BG(f)) CF_BG(f) = CFieldBG_ctor(new(8));
    if (CF_MCES_STATE(f)) CFieldSocket_SetFader(m_socket, 1, (RF(u16, 0x9aa, f) & 0x80) ? 3 : 1, 0);   /* RETAIL */
    CFieldBG_Create(CF_BG(f), db, 0);  CFieldBG_Dsp(CF_BG(f));
    CF_FLAGS179(f) = (CF_FLAGS179(f) & ~2) | 2;
    if ((h = CSTGDB_Find(db, 'MONSET  '))) { CField_SetEncountRate(f, *(u8 *)((u8 *)h + 0x14)); CField_SetFieldData(f, 6, *(u16 *)((u8 *)h + 0x16), 0); CField_SetFieldData(f, 7, *(u16 *)((u8 *)h + 0x18), 0); }
    else CField_SetEncountRate(f, 0);
    CField_AutoLoadSE(f);                                 /* 0x00519b30 */
    if (CSTGDB_Find(db, 'SLICE   ')) { CF_FLOOR(f) = CFloorMan_ctor(new(0x20)); CFloorMan_SetData(CF_FLOOR(f), db); }
    CF_PLAYER_POS(f) = (FVector){0, 0, 0, 1};
    if ((h = CSTGDB_Find(db, 'ENTRYPOS'))) CF_PLAYER_POS(f) = *(FVector *)CSTGDB_GetDataAddr(db, h);       /* default = entry 0 */
    /* RETAIL: saved start position */
    int slot = -1; FVector p;
    if (CF_ENTRY_ID(f) < -1 && (slot = GetSavedChrPos(-(CF_ENTRY_ID(f) + 2), &p)) > -1) CF_PLAYER_POS(f) = p;     /* 0x003f7ca0 */
    if (slot < 0 && (slot = RestoreChrPos(0, &p)) > -1) CF_PLAYER_POS(f) = p;                                        /* 0x003f3860 */
    CF_PLAYER_POS(f).w = 1.0f;
    m_pCAMDAT = m_pCAMOLD = 0;
    if ((h = CSTGDB_Find(db, 'CAMEVENT'))) { CF_CAM_EVENTS(f) = CFieldEvent_ctor(new(0xc)); CFieldEvent_Init(CF_CAM_EVENTS(f), CSTGDB_GetDataAddr(db, h), CSTGDB_GetDataNum(db, h), 1); }
    if ((h = CSTGDB_Find(db, 'CAMERA  '))) { SDB_tagFCAMERA *c = CSTGDB_GetDataAddr(db, h);               /* blob offsets -> pointers */
        for (i = 0; i < CSTGDB_GetDataNum(db, h); i++, c++) c->blob = (char *)c + (u32)c->blob; }
    if ((h = CSTGDB_Find(db, 'EVENTBOX'))) { CF_EVENT_BOXES(f) = CFieldEvent_ctor(new(0xc)); CFieldEvent_Init(CF_EVENT_BOXES(f), CSTGDB_GetDataAddr(db, h), CSTGDB_GetDataNum(db, h), 0); }
    if ((h = CSTGDB_Find(db, 'NAVIMAP '))) { CF_NAVIMAP(f) = CNaviMap_ctor(new(0x120)); CNaviMap_SetData(CF_NAVIMAP(f), CSTGDB_GetDataAddr(db, h)); }
    ShadowControl *sc = CFieldBG_GetShadowCtrl(CF_BG(f), 0);
    if (sc && (ctrl = CField_GetCtrlModel(f)) && ctrl_shown && CF_ENTRY_ID(f) >= 0) {
        int dir; SDB_tagENTRYPOS *e = CField_GetEntryPoint(f, CF_ENTRY_ID(f), &dir);                       /* 0x004f7920 */
        if (e) { FVector q = {e->x, e->y, e->z, 1}; CFieldModel_SetDir(ctrl, dir, 2, 0); CFieldModel_SetPos(ctrl, q, 1); CF_PLAYER_POS(f) = q;
                 m_pCAMDAT = m_pCAMOLD = 0; CField_CameraUpdate(f, 0); }
        CFieldModel_ClearModel_ctrl(ctrl, -1); CFieldModel_DispShadow(ctrl, sc);                         /* 0x0050aed0 / 0x0050bd50 */
    }
    CFieldBG_Update(CF_BG(f), 0);
    for (i = 0; i < CF_MODEL_COUNT(f); i++) if (CF_MODEL(f, i)) CFieldModel_Update(CF_MODEL(f, i), 0);
    Gsx_SetFFMode(0, 1, 2); Gsx_SetInter30(1); CF_STATE(f) = 2;
    return 1;
}

/* ---------------------------------------------------------------- Polling */
/* US 0x004f32d0 CField::Polling  (JP 0x004a6260). Returns 1 when the object may be deleted by the poller. */
int CField_Polling(CField *f) {
    if (CF_COUNTDOWN(f) == 0) Retail_FieldDataCache_Tick(); else CF_COUNTDOWN(f)--;
    if (CF_FLAGS179(f) & 1) {                                           /* teardown requested */
        u32 busy = Retail_ReleaseSoundEffects(f) | (RF(int, 0x8ec, f) ? 8 : 0) | (CF_COUNTDOWN(f) ? 0x10 : 0) | (RF(u16, 0x1a2, f) ? 0x20 : 0) | (RF(u8, 0x1e, g_pGsxState) & 0x10 ? 0 : 0x40);
        if (busy) return 0;
        CMusic_Release(); CPad_dtor(CF_PAD(f)); CFieldCamera_dtor(CF_CAMERA(f)); Retail_FieldDataCache_ReleaseAll();
        CF_FLAGS179(f) &= ~1 ... ; CField_closeInquiry(f); SetAutoDelete(f, 1);  return 1;
    }
    if (CF_FLAGS178(f) & 3) { CField_Delete(f); return 0; }
    if (CF_BATTLE(f)) {                                                 /* 1 BtlIn, 2 BtlInBoss */
        (CF_BATTLE(f) == 2) ? StartBtlInBoss(f) : StartBtlIn();
        CFieldSocket_ClrFilter(m_socket); CField_Delete(f); SSHSys_StartBattle(g_SSHSys, &g_btlParam /*0x615800*/, 0); SetChrPosSaveState(1);  return 0;
    }
    if (CS_PHASE(m_socket) < 4) return 0;                               /* wait until the socket is running */
    if (CF_CTRL_MODE(f)) CF_PRELOAD_NAME(f)[0] = 0;
    if (CF_PRELOAD_NAME(f)[0] && !(RF(u8, 0x180, f) & 3) && !(RF(u8, 0x180, f) >> 5)) { CFieldSocket_CacheMPS(m_socket, CF_PRELOAD_NAME(f)); CF_PRELOAD_NAME(f)[0] = 0; }
    CField_PollingSound(f);
    if (CF_MCES_STATE(f)) CField_UpdateMCES(f);
    if (CF_PAUSE(f) == 2) { if (CF_HUDSTATE(f)) CField_PollingSound(f); return 0; }
    if (!CField_isLoadBusy(f) && !(CF_FLAGS17A(f) & 0x10)) CFieldSocket_CreateCmdMenu(m_socket);
    CField_UpdateRing(f);
    if (RF(u8, 0x8e8, f)) RF(u8, 0x8e8, f)--;
    u32 dt_ms = SSHSys_GetFrameDelta(); RF(u32, 0x9fc, f) += dt_ms; float dt = dt_ms / 1000.0f;
    CField_UpdateDelayEvent(f); CField_UpdateMsgState(f);
    if (CF_STATE(f) == 3) dt = 0;
    if (CF_BG(f)) CFieldBG_Update(CF_BG(f), dt);
    for (i = 0; i < CF_MODEL_COUNT(f); i++) { CFieldModel *m = CF_MODEL(f, i); if (!m) continue;
        CFieldModel_Update(m, dt);
        if (m->navi_id /*+0xd2*/ && CF_NAVIMAP(f)) {                                                 /* mini-map icons */
            int id = m->navi_id - 1;
            if (!(m->flags90 & 0xc)) CNaviMap_DspItem(CF_NAVIMAP(f), id, 0);
            else { FVector wp = CFieldModel_GetWorldPos(m); int ang = (int)(m->rot.y * 57.29579f) - 180; if (ang < 0) ang += 360;
                   CNaviMap_SetItem(CF_NAVIMAP(f), id, (m->navi_icon >> 4) ? 5 : 2, wp, ang, m->navi_icon & 15, 1, 0); } }
    }
    if (CF_STATE(f) == 1) {                                             /* wait for every model to finish loading */
        for (i = 0; i < CF_MODEL_COUNT(f); i++) if (CF_MODEL(f, i) && (RF(u8, 0x90, CF_MODEL(f, i)) & 3) == 1) return 0;
        CF_STATE(f) = 2; return 0;
    }
    CFieldModel *ctrl = CField_GetCtrlModel(f);
    int ready = 0;                                                      /* bit0 displayed, bit1 manual + fader < 0x60 */
    if (ctrl) { ready = (RF(u8, 0x90, ctrl) & 0xc) != 0;
        if (!(RF(u8, 0x95, ctrl) & 0xc) && (RF(u8, 0x98, ctrl) & 1) && CFieldSocket_GetFaderLevel(m_socket, 1) < 0x60) ready |= 2; }
    if (CF_CTRL_MODE(f) == 2 && CFieldSocket_GetFaderLevel(m_socket, 1) < 0x20) CF_CTRL_MODE(f) = 3;
    if (ready == 3 && CField_CheckEncount(f) > 0) {                                                 /* random encounter */
        u16 set = 0; SDB_tagHEADER *h = CSTGDB_Find(m_pSTGDB, 'MONSET  ');
        if (h) { u16 *e = CSTGDB_GetDataAddr(m_pSTGDB, h); int r = rand() % 100;
            for (i = 0; i < h->count; i++, e += 2) { if (r < ((u8 *)e)[2]) { set = e[0]; break; } r -= ((u8 *)e)[2]; } }
        CField_ScriptSuspend(f); CField_InvokeBattle(f, 0, -1, -1, -1, set, 1);  return 0;
    }
    /* ---- input: stick / d-pad -> speed + heading ---- */
    float speed = 0, deg = 0; u16 pad_press = PadPress(CF_PAD(f)), pad_trig = PadTrigger(CF_PAD(f));
    int gait = MakeMoveControl(&speed, &deg, CF_PAD(f));                                           /* unchanged, 0x004f3150 */
    CF_STICK_SPEED(f) = speed; CF_STICK_ANGLE(f) = deg; /* + latched button word */
    if (CF_CTRL_MODE(f) && speed < 0.1f) RF(float, 0xa1c, f) = 0;
    if (CF_CTRL_MODE(f) == 1) { /* replay the latched input */ pad_press = RF(u16, 0xa04, f); speed = RF(float, 0xa08, f); deg = RF(float, 0xa0c, f); }
    if (CF_PAUSE(f) == 1 || (CF_FLAGS179(f) & 4)) { speed = deg = 0; pad_trig = 0; pad_press = 0; }
    RF(float, 0xa08, f) = speed; RF(float, 0xa0c, f) = deg; RF(u16, 0xa04, f) = pad_press;
    if (speed < 0.1f) { CF_FLAGS178(f) &= 0x1f; CF_YAW_ADJUST(f) = 0; }                           /* follow mode off */
    if (ready) {
        CF_CAM_ANGLE(f) = CFieldCamera_GetAngle(CF_CAMERA(f));
        if (ready == 3) {
            float cam_yaw = CF_CAM_ANGLE(f).y;
            float model_in_stick_space = wrap360(cam_yaw + ctrl->rot.y * 57.29579f - 180.0f);
            /* RETAIL follow ease: see notes/G_retail/CField.md section 5.2 and sh2_field::retail::CamFollow */
            switch (CF_FLAGS178(f) >> 5) {
            case 4:                                                                                 /* ease out */
                (void)GetTimer();
                { float d = fabsf(CF_FOLLOW_HEAD(f) - deg); if (d > 180) d = 180; float g = 1 - d / 180; g *= g; if (g > 0.98f) g = 0.98f;   /* JP 0.99 */
                  CF_YAW_ADJUST(f) *= g;
                  if (CF_YAW_ADJUST(f) >= -10 && CF_YAW_ADJUST(f) < 10) CF_YAW_ADJUST(f) *= 0.92f; /* RETAIL */
                  if (CF_YAW_ADJUST(f) >= -1 && CF_YAW_ADJUST(f) < 1) { CF_FLAGS178(f) &= 0x1f; CF_YAW_ADJUST(f) = 0; }
                  deg += CF_YAW_ADJUST(f); }
                break;
            case 1: case 2: case 3:
                if (CF_FLAGS178(f) >> 5 == 1) CF_FOLLOW_HEAD(f) = deg;
                if (CF_FLAGS178(f) >> 5 != 3) {
                    CF_YAW_ADJUST(f) = wrap180(CF_YAW_ADJUST(f) - cam_yaw);
                    CF_FOLLOW_STAMP(f) = GetTimer(); CF_FLAGS178(f) = (CF_FLAGS178(f) & 0x1f) | 0x60; }
                { float d = wrap180(CF_FOLLOW_HEAD(f) - deg);
                  /* (adj<0&&d<0)||(adj>0&&d>0)||(-10<=x||x<=10): the last term is always true in the retail source */
                  CF_FLAGS178(f) = (CF_FLAGS178(f) & 0x1f) | 0x80; CF_FOLLOW_STAMP(f) = GetTimer();   /* -> ease out */
                  (void)d; }
                deg += CF_YAW_ADJUST(f);
                break;
            default: break;
            }
            if (speed >= 0.1f) {
                float h = GetRad((cam_yaw + deg) - 180.0f); clipRadian(&h);
                FVector dir = {0, h, 0, 1};
                if (!(RF(u8, 0x95, ctrl) & 0xc)) CFieldModel_PlayMoveMotion(ctrl, gait);
                if (h != ctrl->rot.y) CFieldModel_SetDir(ctrl, &dir, 2, 3);
            } else if (!(RF(u8, 0x95, ctrl) & 0xc)) CFieldModel_PlayMoveMotion(ctrl, 0);
            CField_ChkLookPoint(f, 1); CField_UpdateNavi(f, dt_ms, pad_trig);
        } else if (!(RF(u8, 0x90, ctrl) & 0x10) && !(RF(u8, 0x95, ctrl) & 0xc)) CFieldModel_PlayMoveMotion(ctrl, 0);
        if (!(CF_FLAGS17A(f) & 8)) CF_PLAYER_POS(f) = CFieldModel_GetWorldPos(ctrl);               /* +0x17a bit3 freezes player_pos */
        if (CF_NAVIMAP(f)) { CNaviMap_DspClr(CF_NAVIMAP(f), (!(RF(u8, 0x275, g_SaveSec_c) & 0xc)) | (GetTailorFlagAddr_bit ? 0 : 2));
                             CNaviMap_Update(CF_NAVIMAP(f), dt, ctrl->rot.y, &CF_PLAYER_POS(f)); }
    }
    /* ---- buttons: menu / talk / event boxes (only when no fade is in progress) ---- */
    if (!FaderBusy(m_socket)) {
        Retail_HudTick(f);                                                                           /* 0x0051d800 */
        if (pad_trig == 0x1000 /*triangle*/ && ready == 3 && CFieldSocket_CheckCmdMenu(m_socket)) {
            CF_FLAGS179(f) |= 4; FieldSaveCharPosition(CFieldModel_GetWorldPos(ctrl), CFieldModel_GetDir(ctrl)); return 0; }
        if (ready == 3 && CF_TEAMCHG(f)) FldTeamChange_Update(CF_TEAMCHG(f), pad_trig);
        if ((pad_trig & 0x2000 /*circle*/) && ready == 3) {
            /* talk: nearest displayed NPC within 12 units in front of the player (dot >= 0.5, not collided) */
            int best = -1; float bestd = -0.5f; FVector probe = ctrl_forward_probe(ctrl);
            for (i = 0; i < CF_MODEL_COUNT(f); i++) { CFieldModel *m = CF_MODEL(f, i);
                if (m && m != ctrl && (m->flags90 & 0xc)) { FVector v = CFieldModel_GetWorldPos(m) - probe_origin; if (Length(v) <= 12.0f) { Normalize(&v); float d = dot(v, probe_dir);
                        if (bestd < d && !isCollided(m) && d >= 0.5f) { bestd = d; best = i; } } } }
            int fired = 0;
            if (best < 0) { /* EVENTBOX probe 6 units ahead */
                int hit = CF_EVENT_BOXES(f) ? CFieldEvent_HitCheck(CF_EVENT_BOXES(f), probe_pos, 0, 1, -1) : -1;
                if (hit >= 0 && (CF_FLAGS178(f) & 0x10) && (CFieldEvent_GetEventBox(CF_EVENT_BOXES(f), hit)->flags & 4)) {    /* examine enabled (f178 bit4) + box flag bit2 */
                    CField_SetFieldEvent(f, 0x12 /* JP: 1 */, CFieldEvent_GetEventNum(CF_EVENT_BOXES(f), hit), 4, 1, 0); fired = 2; } }
            else if (RF(int, 0xd8, CF_MODEL(f, best))) { CField_SetFieldEvent(f, 0x11 /* JP: 1 */, RF(int, 0xd8, CF_MODEL(f, best)), 4, 1, 0); fired = 1; }      /* talk event id: CFieldModel +0xd8 (JP +0xc0) */
            if (!fired && RF(u8, 0x8e4, f)) {                                                          /* default circle event of the current clr_flag slot */
                u8 *rec = (u8 *)f + 0x3f0 + (RF(u8, 0x8e4, f) - 1) * 0x10;                              /* table {event id, u16 arg}[], JP 0x3e8+n*0x10, class 2 */
                if (*(int *)rec) CField_SetFieldEvent(f, 1 /* JP: 2 */, *(int *)rec, 0, 0, *(u16 *)(rec + 4)); }
        }
        /* EVENTBOX enter / leave (kind-0 boxes only, mode 0) */
        if (CF_EVENT_BOXES(f) && (ready & 1)) {
            int now = CFieldEvent_HitCheck(CF_EVENT_BOXES(f), CF_PLAYER_POS(f), 0, 0, -1), prev_id = 0, now_id = 0;
            if (RF(int, 0x8f8, f) != -1) prev_id = CFieldEvent_GetEventNum(CF_EVENT_BOXES(f), RF(int, 0x8f8, f));
            if (now != -1) now_id = CFieldEvent_GetEventNum(CF_EVENT_BOXES(f), now);
            if (prev_id != now_id) {
                if (RF(int, 0x8f8, f) != -1 && (CF_FLAGS178(f) & 0x08) && (GetEventBox(prev)->flags & 2)) CField_SetFieldEvent(f, 0x10 /* JP: 1 */, prev_id, 2, 0, 0);   /* leave */
                if (now != -1) { RF(int, 0x8fc, f) = now_id; if ((CF_FLAGS178(f) & 0x04) && !(GetEventBox(now)->flags & 1)) CField_SetFieldEvent(f, 0x10 /* JP: 1 */, now_id, 1, 0, 0); }   /* enter */
            }
            RF(int, 0x8f8, f) = now;
        }
        if (RF(int, 0x900, f) && g_pFldTimer && (g_pFldTimer->flags61 & 2) && ((CScript_GetState() >> 8) & 0xff) != 0xc2) {          /* FldTimer alarm */
            CField_SetFieldEvent(f, 0, RF(int, 0x900, f), 0, 0, 0); g_pFldTimer->flags61 &= ~2; RF(int, 0x900, f) = 0; }
        Retail_CField_CheckNpcSight(f);                                                              /* RETAIL: monster sight poll */
    }
    CField_CameraUpdate(f, dt);
    if (g_pGsxCamera) { CF_VEC_1d10(f) = GsxCamera_GetFrame()->pos; CF_VEC_1d20(f) = GsxCamera_GetFrame()->at; CF_VEC_1d20(f).w = g_pGsxCamera->fov; }
    CField_CheckMirror(f); CField_UpdateLight(f);
    return 0;
}

/* ---------------------------------------------------------------- camera */
/* US 0x004f4950 CField::CameraUpdate(dt)  (JP 0x004a84c0): script camera, else follow the controlled model */
void CField_CameraUpdate(CField *f, float dt) {
    if (CF_FLAGS17A(f) & 0x20) {                          /* RETAIL: camera sway / blur FX (script op 0x77) */
        Retail_CField_StepCamBlurFx(dt, f);
        FVector pos_ofs = {0, 0, 0, 1}, ang_ofs = {0, 0, 0, 1};
        Retail_CField_EvalCamBlurFx(f, &pos_ofs, &ang_ofs);
        CC_POS_OFS(CF_CAMERA(f)) = pos_ofs; CC_ANG_OFS(CF_CAMERA(f)) = ang_ofs;
    }
    CFieldModel *ctrl = CField_GetCtrlModel(f);
    if (CF_SCRCAM(f)) {                                   /* script driven camera */
        CField_UpdateScrCamera(f, dt);
        if (CF_CTRL_MODE(f) == 3 && ctrl && (ctrl->flags90 & 0xc)) CF_CTRL_MODE(f) = 0;
        if (CF_SCRCAM(f)) { CFieldCamera_Apply(CF_CAMERA(f), dt); return; }
    }
    if (!ctrl) { CF_FLAGS178(f) &= 0x1f; CF_YAW_ADJUST(f) = 0; return; }
    int shown = (ctrl->flags90 & 0xc) != 0;
    if (shown) { FVector wp = CFieldModel_GetWorldPos(ctrl); if (!(CF_FLAGS17A(f) & 8)) { CF_PLAYER_POS(f) = wp; } else shown = shown; }
    if (shown) CField_UpdateFieldCamera(f);
    if (CF_CAMERA(f)) {
        float roll = shown ? -ctrl->move_rot.y /* +0x48 */ : 0;
        CFieldCamera_Apply(CF_CAMERA(f), roll);
        CF_CAM_ANGLE(f) = CFieldCamera_GetAngle(CF_CAMERA(f));
        if (CF_CTRL_MODE(f) == 3 && shown) {              /* control returns after a script: rebuild the follow correction */
            CF_CTRL_MODE(f) = 0;
            CF_YAW_ADJUST(f) = ctrl->rot.y * 57.29579f + 180.0f;
            if (CF_STICK_SPEED(f) >= 0.1f) { CF_YAW_ADJUST(f) = wrap180(CF_YAW_ADJUST(f) - CF_STICK_ANGLE(f)); CF_FLAGS178(f) = (CF_FLAGS178(f) & 0x1f) | 0x20; }
            if (CF_STICK_SPEED(f) >= 0.1f && RF(float, 0xa1c, f) >= 0.1f) { float d = wrap180(RF(float, 0xa20, f) - CF_STICK_ANGLE(f)); if (d < -5 || d > 5) { CF_FLAGS178(f) &= 0x1f; CF_YAW_ADJUST(f) = 0; } }
            if (RF(float, 0xa1c, f) < 0.1f) { CF_FLAGS178(f) &= 0x1f; CF_YAW_ADJUST(f) = 0; }
        }
        CF_CAM_POS(f) = CFieldCamera_GetCameraPos(CF_CAMERA(f));
    }
}

/* US 0x004f4ef0 CField::UpdateFieldCamera  (JP 0x004a8be0): pick the CAMEVENT, evaluate the CAMERA entry, feed the CFieldCamera */
void CField_UpdateFieldCamera(CField *f) {
    FVector pl = CF_PLAYER_POS(f);  CField_ReverseVector(f, &pl);                   /* mirror reversal */
    if (CF_CAM_EVENTS(f)) {
        int id = CFieldEvent_HitCheck(CF_CAM_EVENTS(f), pl, 0, 0, -1);
        if (id < 0) id = FieldCameraID(-2);                                          /* camera remembered in the save block */
        if (id >= 0) {
            SDB_tagHEADER *h = CSTGDB_Find(m_pSTGDB, 'CAMERA  ');
            if (h) {
                SDB_tagFCAMERA *tab = CSTGDB_GetDataAddr(m_pSTGDB, h);
                m_pCAMDAT = tab + CFieldEvent_GetEventNum(CF_CAM_EVENTS(f), id);     /* CAMEVENT.id = CAMERA index */
                if (m_pCAMOLD && m_pCAMOLD != m_pCAMDAT && m_pCAMDAT->blend_flag && m_pCAMOLD->blend_flag) CFieldCamera_CompFrame(50.0f, CF_CAMERA(f));
                if (id != CF_CAMERA_ID(f)) { int had = CF_CAMERA_ID(f) >= 0; CF_CAMERA_ID(f) = id;
                    if (had) { CF_YAW_ADJUST(f) += CF_CAM_ANGLE(f).y; CF_FLAGS178(f) = (CF_FLAGS178(f) & 0x1f) | ((CF_FLAGS178(f) >> 5) == 4 ? 0x40 : 0x20); } }   /* -> CamFollow mode 2 / 1 */
            }
            if (CF_CTRL_MODE(f) == 0) FieldCameraID(id);
        }
    }
    if (!m_pCAMDAT) return;
    SDB_tagFCAMERA *cd = m_pCAMDAT; u8 *blob = cd->blob; if (!blob) return;
    FVector tgt, cam; float fov = 320.0f; int ok = 0; FVector p = pl; p.y -= 12.0f;
    switch (cd->kind) {
    case 0: cam = *(FVector *)blob; tgt = *(FVector *)(blob + 0x10); fov = *(u16 *)(blob + 0x20); ok = 1; break;
    case 1: { FVector off = (*(FVector *)blob - *(FVector *)(blob + 0x10)); RotY(ctrl_rot_y, &off); FVector a = off + pl; FVector d = CFieldCamera_GetCameraPos(CF_CAMERA(f)) - a;
              cam = a + d * 0.94f; cam.w = 1; tgt = p; fov = *(u16 *)(blob + 0x20); ok = 1; break; }
    case 2: { cam = (*(FVector *)blob - *(FVector *)(blob + 0x10)); cam.y -= 12.0f; cam += pl; tgt = p; fov = *(u16 *)(blob + 0x20); ok = 1; break; }
    case 3: case 4: {
        FVector pivot = *(FVector *)blob, base = *(FVector *)(blob + 0x10), aim = Pivot_Aim(blob, pivot, base, p);   /* clamp yaw/pitch of pivot->p to blob limits (+0x40,+0x44,+0x50,+0x54) */
        fov = *(u16 *)(blob + 0x20); tgt = aim; cam = pivot;
        if (cd->kind == 4) {                                                       /* leash: camera never more than 100 from the pivot */
            float len = Length(pivot - aim); cam = pivot; if (len > 100.0f) cam = pivot + (aim - pivot) * (100.0f / len);
            tgt = p; }
        ok = 1; break; }
    case 5: {
        u32 w3c = *(u32 *)(blob + 0x30 + 0xc); int rounded = ((w3c & 0xff000000) == 0) ? (int)(w3c & 2) > 0 : 0;
        if (!rounded) { /* nearest-segment mode: nearest node by mean of (node.p, midpoint) distances, then GetCamPath(i) chain */ ... see sh2_field::camera::eval_path_camera }
        else {
            FVector pos = pl; int seg; float v = GetNearestPath(cd, &pos, &seg);
            if (v >= 1000.0f) GetCamPath2(f, out, (int)(v - 1000.0f), pl); else GetCamPathA(v, f, seg, out);        /* out[0] target, out[1] camera, out[1].w = fov */
            fov = out[1].w; tgt = out[0]; cam = out[1]; }
        if (m_pCAMOLD == m_pCAMDAT && CFieldSocket_GetFaderLevel(m_socket, 1) != 0x7f) {   /* low-pass towards the camera that is already applied */
            tgt = tgt + (ReverseVector(CC_TARGET(CF_CAMERA(f))) - tgt) * 0.81f; cam = cam + (ReverseVector(CC_CAM(CF_CAMERA(f))) - cam) * 0.81f; }
        ok = 1; break; }
    }
    if (ok) { CFieldCamera_SetViewAngle(CF_CAMERA(f), fov / 512.0f);
              CField_ReverseVector(f, &tgt); CField_ReverseVector(f, &cam);
              CFieldCamera_SetTargetPos(CF_CAMERA(f), tgt); CC_CAM(CF_CAMERA(f)) = cam; }
    m_pCAMOLD = m_pCAMDAT;
}
