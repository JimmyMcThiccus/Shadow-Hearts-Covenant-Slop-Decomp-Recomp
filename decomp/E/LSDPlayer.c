/*
 * LSDPlayer.c -- LSD cutscene stream player (JP main 0x00387370..0x00388900, LSDPlayer.cpp)
 * Includes LSDDeviceHandler base and LSDPlayerHandler (the 'LSDC' control track).
 * See notes/E/lsd_format.md.
 */
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32; typedef int s32;

/* LSDDeviceHandler (sizeof 0x14, vtable __vt__16LSDDeviceHandler):
 *   +0x00 prev  +0x04 next  (intrusive list `LSDPlayer::List`, plugged by PlugDevice)
 *   +0x10 vptr: [0] dtor(+8)  [1] CheckData(+8)  [2] Open(+0xc)  [3] Read(+0x10)  [4] Event(+0x14... )
 * Concrete vtable layout used by the player (offsets from vptr):
 *   +0x08 CheckData(handler, _LSDTrackHdr*)            -> bool
 *   +0x0c Open(handler, RingBuffer*)                   -> _LSDHANDLE*   (track instance, NULL = no instance)
 *   +0x10 Read(handler, _LSDHANDLE*, RingBuffer*)      -> bytes consumed (0 = need more data)
 *   +0x14 Close(handler, _LSDHANDLE*)                  -> bool (done)
 *   +0x18 Event(handler, _LSDHANDLE*, int code, float time, float dt)
 * _LSDHANDLE: +0 tag, +4 closing flag, +8 owner LSDDeviceHandler*, +0xc handler private
 */
typedef struct _LSDHANDLE { u32 tag; s32 closing; struct LSDDeviceHandler *dev; void *priv; } _LSDHANDLE;

/* class LSDPlayer : CPolObj (vtable 0x406f60, sizeof ~0xb0).  Polled at priority 0x80 by CPoller(+0x48).
 * statics: sys__9LSDPlayer 0x40acf8, List__9LSDPlayer 0x40acfc (handler list head), LSDPlayerHnd 0x423750 */
typedef struct LSDPlayer {
    u8   polobj[0x14];
    void **vptr;            /* 0x14 */
    struct RingBuffer *evq; /* 0x18 event ring (0x5000 bytes, 8-byte events) */
    float time;             /* 0x1c current time in seconds */
    float dt;               /* 0x20 seconds per Polling = 1/(60 or 30) * speed ; 0 while stalled/paused */
    float lastDt;           /* 0x24 dt passed to the last Update */
    float speed;            /* 0x28 playback speed multiplier (1.0) */
    u32  recvTick;          /* 0x2c control data received up to this tick (set by LSDPlayerHandler::Read) */
    u8   hdr[0x40];         /* 0x30 copy of the LSDH header: 0x3a n_tracks, 0x3e ticks_per_sec */
    s32  state;             /* 0x70 -1 idle, 0 waiting for start callback, 1 playing, 2 done */
    s32  lastPktTrack;      /* 0x74 */
    s32  liveTracks;        /* 0x78 number of open track instances */
    int (*startCb)(void);   /* 0x7c optional "may start" callback (FldInitLSDPlayer / setStartCallBack) */
    s32  sema;              /* 0x80 */
    s32  stall;             /* 0x84 0 ok, 1 starving -> sent PAUSE, 2 recovering */
    s32  userPause;         /* 0x88 Pause()/Release() */
    u32  stallTick;         /* 0x8c tick we are waiting for */
    struct StreamFile *sf;  /* 0x90 DVD stream (ring buffer inside), 0x177000 byte buffer, chunk 0xc800 */
    _LSDHANDLE **tracks;    /* 0x94 array[n_tracks] of open instances */
    u8   parseState;        /* 0x98 0 = LSDH, 1 = track headers, 2 = packets */
    s32  trackIdx;          /* 0x9c */
    s32  exiting;           /* 0xa0 0 / 1 requested / 2 sent END to all tracks */
    s32  sem_init[3];       /* 0xa4 */
} LSDPlayer;

/* 0x00387370 */ LSDPlayer *LSDPlayer_ct(LSDPlayer *p) {
    CPolObj_ct(p); p->vptr = __vt__9LSDPlayer; sys__9LSDPlayer = p;
    p->sf = 0; p->parseState = 0; p->tracks = 0; p->trackIdx = 0; p->liveTracks = 0; p->time = 0; p->exiting = 0;
    p->state = -1; p->lastPktTrack = -1; p->recvTick = 0; p->startCb = 0; p->stall = 0; p->userPause = 0;
    p->speed = 1.0f;
    CPoller_Entry(app->poller48, p, 0x80, 0);
    p->evq = RingBuffer_new(0x5000, 0);
    p->dt = (1.0f / (60.0f / (1 - (Gsx_flags & 1 ? -1 : 0)))) * p->speed;   /* 1/60 (or 1/30 in Inter30 mode) */
    p->sema = CreateSema(&p->sem_init);
    return p;
}

/* 0x00387590 StreamPolling: StreamFile callback, runs dataCheck() whenever the ring buffer has data. */
void LSDPlayer_StreamPolling(LSDPlayer *p) { if (p->sf && p->sf->ring.used) LSDPlayer_dataCheck(p); }

/* 0x003875d0 PlugDevice: link an LSDDeviceHandler into the global list (head insert) */
int LSDPlayer_PlugDevice(LSDDeviceHandler *h) {
    if (h->prev || h->next) return 0;
    if (List__9LSDPlayer) { h->prev = List__9LSDPlayer; List__9LSDPlayer->next = h; }
    List__9LSDPlayer = h; return 1;
}

/* 0x00387620 Polling -- once per game frame (priority 0x80) */
int LSDPlayer_Polling(LSDPlayer *p) {
    WaitSema(p->sema);
    LSDPlayer_checkEvent(p);
    if (p->exiting == 0 && p->state == 1) {
        for (int i = 0; i < p->n_tracks; i++)               /* code 0 = per-frame update */
            if (p->tracks[i]) p->tracks[i]->dev->vptr->Event(p->time, p->lastDt, p->tracks[i]->dev, p->tracks[i], 0);
        u32 needTick = (u32)(p->ticks_per_sec * (p->time + p->dt));
        if (p->recvTick < needTick && p->sf->ring.used == 0) {   /* data starvation */
            p->lastDt = 0;
            if (p->stall == 0) {
                p->dt = 0;
                u32 pad = p->sf->ring.cursor == 0 ? 0x412f4000 /* 1,000,000 bytes? double 1000000.0 */ : 0;
                p->stallTick = min(p->sf->file->size, p->sf->written + pad);
                p->stall = 1; if (p->stallTick == 0) p->stall = 2;
                if (!p->userPause) for (each track) Event(.., code 5 /*PAUSE*/);
            }
        } else {
            if (p->stall == 2 && p->sf && p->sf->file && p->stallTick <= p->sf->file->read) {
                p->stall = 0;
                if (!p->userPause) { p->dt = (1.0f / (60.0f / Gsx_syncCount)) * p->speed; for (each track) Event(.., 6 /*RESUME*/); }
            }
            p->lastDt = p->dt;
            p->time += p->dt;
        }
    }
    SignalSema(p->sema);
    return 0;
}

/* 0x00387990 Pause / 0x00387a40 Release : user pause. Pause sets dt=0 and sends code 5 to all tracks (if not already
 * stalled); Release restores dt and sends code 6. */

/* 0x00387b50 checkEvent -- pop due events from the event ring and dispatch */
void LSDPlayer_checkEvent(LSDPlayer *p) {
    if (p->state == 1)                                   /* reap finished tracks */
        for (int i = 0; i < p->n_tracks; i++) {
            _LSDHANDLE *t = p->tracks[i];
            if (t && t->closing && t->dev->vptr->Close(t->dev, t)) { p->tracks[i] = 0; if (--p->liveTracks == 0) p->state = 2; }
        }
    if (p->exiting == 1) {                               /* Exit(): END (4) to everybody */
        for (each live track) { Event(0, 0, .., 4); t->closing = 1; }
        p->exiting = 2;
    }
    if (p->evq->used && p->exiting == 0) {
        do {
            int   evTime = peek_i32(p->evq, 0);          /* ticks */
            u16   evCode = peek_u16(p->evq, 4);          /* low 12 bits = command */
            u16   evTrk  = peek_u16(p->evq, 6);
            if (p->state == 0) {                         /* not started yet */
                if (p->startCb && !p->startCb()) return;
                p->time = (float)(evTime / p->ticks_per_sec); p->state = 1;
            }
            if ((int)(p->time * p->ticks_per_sec) < evTime) return;      /* not due */
            _LSDHANDLE *t = p->tracks[evTrk];
            if (t) { t->dev->vptr->Event(p->time, p->lastDt, t->dev, t, evCode & 0xfff); if ((evCode & 0xfff) == 4) t->closing = 1; }
            RingBuffer_clearBlock(p->evq, 8);
        } while (p->evq->used >= 8);
    }
}

/* 0x00387e50 dataCheck -- stream parser (three states) */
void LSDPlayer_dataCheck(LSDPlayer *p) {
    WaitSema(p->sema);
    int used;
    do {
        used = 0;
        RingBuffer *r = &p->sf->ring;
        switch (p->parseState) {
        case 0: if (r->used >= 0x40) { used = reciveInit(p, r); if (used) p->parseState = 1; } break;
        case 1: if (r->used >= 0x20) { used = reciveTrackHdr(p, r); if (++p->trackIdx >= p->n_tracks) p->parseState = 2; } break;
        case 2: if (r->used >= 0x10) { PktHdr *h = peek(r); if (r->used >= h->blocks * 16 + 16) used = recivePacket(p, r); } break;
        }
        RingBuffer_clearBlock(r, used);
    } while (used);
    SignalSema(p->sema);
}
/* 0x00387fb0 reciveInit: copy 0x40 header, alloc tracks[n_tracks]=0 (returns 0x40) */
/* 0x00388030 reciveTrackHdr: for each registered LSDDeviceHandler h in List: if h->CheckData(hdr) { tracks[idx] = h->Open(ring);
 *            tracks[idx]->closing = 0; liveTracks++; break; }  returns hdr.size_units*16 */
/* 0x00388170 recivePacket: if packet.track < n_tracks && tracks[track]: n = dev->Read(..); if n==0 -> wait for more (lastPktTrack=track);
 *            else return n.  Unknown track -> skip blocks*16+16 */
/* 0x00388220 startStream(path): new StreamFile(path, 0x177000, 0xc800) polled via FileIOLib poller; callback = StreamPolling */
/* 0x00388310 Exit: stop stream; if dt==0 && exiting==0: exiting=1 (checkEvent sends END to every track), dt restored */
/* 0x003883d0 Reset: allowed only in state 2 or -1; frees the track array, clears the event ring, state=-1 */

/* ---------------- LSDPlayerHandler ('LSDC' track, JP 0x003885b0..) ---------------- */
/* CheckData: tag == 'LSDC' (0x4344534c)
 * Open:      owner = sys__9LSDPlayer; old = Gsx::SetInter30(1); (remember) ; Gsx::SetFFMode(0, 1, 60/ticks_per_sec) -- locks the
 *            display to the LSD tick rate. returns &priv
 * Close:     Gsx::SetInter30(old); Gsx::SetFFMode(0,1,saved)
 * Read(ring): packet at ring head: 16-byte hdr, +0x10: u8 flags, +0x14 u32 tick, +0x18 u32 nRecords ('CTRL' @+0x1c);
 *            records from +0x20: { u16 type==1, u16 -, u16 count, u16 -, count*8 bytes } -> appended verbatim to LSDPlayer.evq
 *            (printf "ring full" when evq has no room). Sets LSDPlayer.recvTick = tick; if stall==1 -> 2. flags&1 prints "end".
 */
