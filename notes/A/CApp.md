# Section A: CApp / CThread / CTimer / CPoller / CPolObj / CList / CPause (JP `app.cpp`, 0x003d53f0..0x003d8768)

Neighbour map: `CGhostEfx` ... `CThread` 3d53f0 | `CTimer` 3d5a60 | `UpdatePolBreakState` 3d6460 | `CPolObj` 3d6470 | `CPoller` 3d6690 | `CList` 3d6d90 | `CApp` 3d7150 | `CPause` 3d7e90 | `~CApp` 3d8680 | `ScreenBright` 3d8770.
US: same order at 0x00407960..0x0040ad80 (see us_map.txt; US `Run` is 0x680 bytes vs 0x4c0, extra statics).

## Layouts (Ghidra structs created in SLPM_602.19: CThread, CTimer, CPolObj, CPoller, CList, DelayDeleteObject, CPause, CApp)

### CThread (0x48)
| off | type | name |
|---|---|---|
| 0x00 | int | tid (EE thread id, 0 = none) |
| 0x04 | CTimer* | timer (ms CTimer, kind 2 "wake thread", created lazily by CreateThread) |
| 0x08 | u32 | (stored arg) |
| 0x0c..0x3c | ThreadParam | status, +0x10 entry (=`Enter`), +0x14 stack, +0x18 stackSize (16-aligned), +0x1c gp, +0x20 initPriority (0xf if prio arg==0), +0x24 curPriority, +0x28 attr, +0x2c option(=this) ... |
| 0x3c | int | exit code |
| 0x40 | u8 | flags b0 alive, b1 ?, b2 default-priority |
| 0x44 | vtbl | `{+8 __dt, +0xc ExitInstance, +0x10 InitInstance, +0x14 Run}` |

`Enter(arg)` -> `EnterInstance`: `exit = InitInstance() ? Run() : ExitInstance(); Delete(this)`. Base InitInstance=1, ExitInstance=-1, Run calls ExitInstance. CApp overrides InitInstance (0x3d76d0) and Run (0x3d7730).

### CTimer (0x1c)  +0 next, +4 kind (0 stopwatch,1 callback,2 wake thread), +5 clock (0 VS,1 VV,2 MS), +8 flags (b0 running,b1 event,b2 repeat,b3 queued), +0xc cb / CThread*, +0x10 count, +0x14 period, +0x18 total.
Three global singly linked queues `m_pTblVS/VV/MS` (0x40adec/f0/f4). `TimerWatcher0` is the RCNT0 interrupt (INTC 9, target 0x823 NTSC or 0x249f), ticks MS list every interrupt and VV list every 17th (`m_fractionVV`); `TimerWatcherV` is the vsync-driven list. `SysTool::timer` (ms) and `vtimer` give the game clock (`SysTool::GetTimer`).

### CPolObj (0x18) / CPoller (0xc)
CPolObj: `+0 CPoller* owner, +4 next, +8 prev, +0xc autoDelete, +0xd linked, +0xe killReq, +0x10 u16 priority(0x80), +0x14 vtbl{+8 __dt(int del), +0xc bool Polling()}`.
CPoller: `+0 head, +4 tail, +8 current`. `Entry(obj, prio, autoDelete)` inserts sorted ascending (after equal priority). `Polling()` calls vtable+0xc on every object; non-zero return or `killReq` => `Remove`, delete if autoDelete. Disposing the object currently being polled only sets killReq (Remove sets `+0xe` when `owner->current == this`).

### CList (8) `+0 next, +4 prev`. Confusing naming: GetHead follows `prev`, GetTail follows `next`. Used for DelayDeleteObject.

### DelayDeleteObject (0x14): CList + `vtbl@+8 {+8 __dt, +0xc DelayDelete}`. `DelayDelete()` appends to `app->+0x6c` if not already queued; CApp::Run drains the queue after `sceGsSyncPath` calling the virtual dtor.

### CApp (0x150)
| off | type | name |
|---|---|---|
| 0x00 | CThread | base (vtbl +0x44 = __vt__4CApp 0x4078b0) |
| 0x48 | CPoller | game poller 0 (scene objects) |
| 0x54 | CPoller | game poller 1 |
| 0x60 | CPoller | system poller (SSHSys prio 0x40, CVibeMan, CPauser, FileIOLib poller is separate) |
| 0x6c | DelayDeleteObject | delayed-delete queue |
| 0x78 | CPause* | |
| 0x80 | ClutAdressControl | GsxRaster subclass (0x20 B) |
| 0xa0 | FVector[10] | |
| 0x140 | u8 | capture request |

Statics: app 0x40adfc, m_scrw/m_scrh 0x40ae00/04 (u16), camera 0x40ae08, m_pBright 0x40ae0c, m_pAppFunc 0x40ae10, m_vcount/hcount/ecount/wcount 0x40ae14/18/1c/20, m_capmd 0x40ae24, m_capct 0x40ae28, capTbl[60], rebootPath 0x430030 (0x80), m_World 0x42bf10 (0x4120).

`Run` frame (JP 0x3d7730): World Begin/Render/EndUpdate; system poller; if `!(pause->flags&1)` game pollers 0,1; m_pAppFunc; World::GetPacket; ScreenBright::Draw; sceGsSyncPath; DelayDelete drain; screenshot slots; DrawSync + hcount stats; VSync or GsxForceFlip; UpdatePolBreakState; if `pause->flags&8` -> DoReset().

### CPause (0x14)
`+0 flags (b0 paused, b1 pausing, b2 unpausing, b3 reset request, b6-7 reset-combo state)`, `+2 u16 padState`, `+4 i16 disablePause`, `+6 i16 disableReset`, `+8 u32 resetStartTime`, `+0xc` callback chain (nodes `{next, 16 x (fn(int resume, void*), arg)}` 0x84 B).
Pause/UnPause run all callbacks with 0/1 (SysTool::CBPause stops the game clock, SSHSys::CBPause forwards to the current SSHApi::Pause, CVibeMan mutes). `CheckUnPause(pad, mask)` is an edge filter (mask default START=8). `CheckReset(pad, time, mask)` soft reset: mask default 0xf09 (L1+R1+L2+R2+START+SELECT) must be held > 1000 ms.

### main / boot (JP 0x221ea0 etc.) see Misc.md.
