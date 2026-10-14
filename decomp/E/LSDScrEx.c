/*
 * LSDScrEx.c -- CScriptEx id 0xc0 for LSD cutscene scripts (JP main 0x003ccd70..0x003cdfe0, EventServer.cpp)
 * class LSDScrEx : CScriptEx   (sizeof 0x6c, vtable __vt__8LSDScrEx 0x4077e0, static sys__8LSDScrEx 0x40add0)
 */
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32; typedef int s32;

typedef struct LSDScrEx {
    u8  cscriptex[0x24];       /* CScriptEx: +0x14 vptr, +0x18 next, +0x1c script, +0x20 id(0xc0), +0x22 flags */
    struct _EventWork *ew;     /* 0x24 owning EventHandler work */
    void (*musicCb)(u8, u32, u32); /* 0x28 saved CMusic callback (restored in Delete) */
    u32  musicCbArg;           /* 0x2c */
    struct CVibe *vib[8];      /* 0x30 vibration instances by script id */
    struct FldSprite *img[2];  /* 0x50 DspImage slots */
    u8   flags;                /* 0x58 b0 = deleted, b1 = we created CMusic (must destroy) */
    u16  bgmState;             /* 0x5a 0 idle, 1 = waiting for generic-data BGM, 2 = playing */
    char bgmName[0x10];        /* 0x5c name looked up in GenericDataHandler */
} LSDScrEx;

/* 0x003ccd70 ctor: CScriptEx::ct; vptr; memset(+0x24, 0, 0x48)
 * 0x003ccf70 Init(): sys__8LSDScrEx = this; if no CMusic: create (flags |= 2) else save its callback (+0x84/+0x88);
 *                    CMusic.cb = cbMusic; preLoad(); Start()   -> Entry(poller prio 0x70)
 * 0x003cd080 LinkA(EventWork*): this->ew = ew; CScriptEx::Link(0xc0, NULL)  == register as extension 0xc0 on sys CScript
 * 0x003cd1d0 Polling(): if !deleted { PollingSound(); EventHandlerUpdate(ew) } else tear down (Release music, CineMask, CVibe[8])
 * 0x003cd110 closeInquiry(): Dispose; CineMask::Delete; free vibes
 * 0x003cce70 Delete(): flags|=1; restore CMusic callback; delete FldSprite imgs
 */

/* 0x003cd310 CallFunc(sub, nargs, args)   -- the opcode 0xc0 interface; all sub-ops return 0 (void) */
int LSDScrEx_CallFunc(LSDScrEx *t, int sub, int nargs, u32 *a) {
    switch (sub) {
    case 0x00: /* SetFader(mode, time) */
        if (a[0] != 4 && !(a[0] & 1)) CFieldSocket_SetFader(m_socket, 1, (a[0] & 2) | 1, 0);
        CFieldSocket_SetFader(m_socket, 1, a[0], a[1]); break;
    case 0x03: /* SetNextBGM(char *name) */ t->bgmState = 1; strcpy(t->bgmName, (char *)a[0]); break;
    case 0x04: /* FadeBGM(time) */ CMusic_FadeBGM(sys_CMusic, 0, a[0]); break;
    case 0x05: /* CineMask(on) */
        if (!a[0]) { if (sys_CineMask) CineMask_Clr(sys_CineMask); }
        else { if (!sys_CineMask) sys_CineMask = new CineMask(0x4c); CineMask_Dsp(sys_CineMask); } break;
    case 0x06: LSDScrEx_StartVib(t, a[0], (char *)a[1], a[2]); break;
    case 0x07: LSDScrEx_StopVib (t, a[0], a[1]); break;
    case 0x08: LSDScrEx_FadeVib (t, a[0], a[1], a[2]); break;
    case 0x09: LSDScrEx_DspImage(t, a[0], (char *)a[1], a[2], a[3]); break;
    case 0x0a: LSDScrEx_ClrImage(t, a[0], a[1]); break;
    case 0x0b: LSDScrEx_SetBGMotion (t, a[0], (char *)a[1]); break;
    case 0x0c: LSDScrEx_SetBGMotionI(t, a[0], (char *)a[1], (char *)a[2]); break;
    case 0x0d: MCESInvokeBattle(); break;
    case 0x0e: if (CFieldBG_current) CFieldBG_EffectAlpha((float)a[1], CFieldBG_current, a[0], a[2]); break;
    case 0x0f: LSDPlayer_Pause(sys_LSDPlayer); LSDPlayer_Exit(sys_LSDPlayer); break;
    }
    return 0;
}
/* 0x003cd680 PollingSound: if bgmState==1: look up bgmName in GenericDataHandler; if found CMusic::PlayBGM(0, playModeTbl, data) , ++bgmState
 *                          then CMusic vtbl[3] (Polling)
 * 0x003cd790 cbMusic(char ev, u32, u32): ev==1 (BGM finished): bgmState=0 & RemoveData(generic) ; else forward to saved callback
 * 0x003cd850 StartVib(id, name, seq): destroy old CVibe[id]; data = GenericDataHandler::Find(name); seq = CVibeMan::GetSeqData(data->buf, seq);
 *            vib[id] = new CVibe; CVibeMan::Start(vib, seq, 0)
 * 0x003cd9b0 StopVib(id, fade): id<0: all (ReleaseAllVibe or CVibeMan::SetFader(0,fade)); else delete or CVibe::SetFader(0,fade,1)
 * 0x003cdaf0 FadeVib(id, vol, time): id<0 -> CVibeMan::Volume/SetFader else CVibe::SetFader(vol,time,0)
 * 0x003cdbb0 DspImage(slot, name, x, y): data from GenericDataHandler; FldSprite::Create(buf,1,1); layer 0xb; Dsp(x,y,0,0)
 * 0x003cdcc0 ClrImage(slot, keep): FldSprite::Clr; slot cleared unless keep
 * 0x003cdd50 SetBGMotion(model, motion): CFieldBG::GetModel(cur, id)->SetLastMotion/SetMotion(name)
 * 0x003cdde0 SetBGMotionI(model, dataName, motionName): load motion from an 'SQHD' (0x44485153) data blob (or a packed archive entry), createMotion, SetMotion
 */
