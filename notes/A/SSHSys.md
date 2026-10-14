# Section A: SSHSys / SSHApi / SysTool / CDMYStage / GameOver / CPauser (JP `SSHmain.cpp`)

JP: SSHLoadModules/SSHMain 23bcc0, SysTool 23c080..23c9ff, SSHApi 3b5df0, SSHSys 3b6130..3b7544 (+DoReset 3b7410), CDMYStage 3a7ea0, GameOver 3abe10, CPauser 3c9a90.
US: SSHMain 0x002387e0, SSHApi 0x3ed300.., SSHSys 0x3ed650..0x3eeee0, CDMYStage 0x415c50.., GameOver 0x3e3c00, CPauser 0x3fe690.

## SSHSys (0xB0, global `SSHSys::sys` 0x40ad60, `Language` 0x40ad64) -- Ghidra struct SSHSys
| off | type | name / meaning |
|---|---|---|
| 0x00 | CPolObj | base; vtbl@+0x14 = 0x407620 `{+8 __dt, +0xc Polling}`; registered in CApp system poller prio 0x40 |
| 0x18 | SysTool | vtbl `{+8 dt, +0xc Initialize, +0x10 Terminate, +0x14 SysInitialize, +0x18 SysTerminate, +0x1c PluginAttach, +0x20 CBPause}` @0x404ad0 |
| 0x1c | i32 | last GetTimer() |
| 0x20 | i32 | frame delta (ms) `GetFrameDelta` |
| 0x24 | SSHApi* | pending |
| 0x28 | SSHApi* | current |
| 0x2c | CPad* | pad 0 |
| 0x30 | i32 | initPhase (1 = waiting for MenuObj ready + BgEffectMan::cmnTexture) |
| 0x34 | u8 | pending state 0/1 preLoad requested/2 ready |
| 0x35 | u8 | current state 0 run/3 closeInquiry requested/4 closed |
| 0x36 | u8 | **request**: 0x10 field, 0x20 battle armed, 0x21 battle go, 0x30 game over, (US: 0x40 new scene) |
| 0x37 | u8 | fio disc-change busy |
| 0x38 | i16 | pause re-arm timer (ms) |
| 0x3a | i16 | reload value 500 (`SetPauseTmr`) |
| 0x3c | u16 | flags b6 = CLSDPauser instead of CPauser (`SetPauserType`, in FIELD.BIN) |
| 0x40 | _SysBtlParam (0x10) | `+0 u32, +4 regdatId, +8 u16 bgm, +0xa u8 pcCount, +0xb u8 monsterSet, +0xc u8 pc[4]` |
| 0x50 | u8[4] | battle result: [0]=2, [1]=0xff/0/1, [2]=no-gameover flag |
| 0x54 | char[0x14] | next field map name |
| 0x68 | Overlay (0x40) | FIELD/BATTLE overlay loader (group 1 at init) |
| 0xa8 | CScreenCap* | |

### State machine
`SetAPI(api)` accepted only if pending==null: marks current for close (state 3), pendState=1. `Polling`: update clock/pad (CPad::Polling), fio busy flag, pause timer; while `initPhase==1` wait; else: closeInquiry loop (state 3 -> 4), preLoad loop (pendState 1 -> 2), then handover when current null or closed: delete current, `pending->Start()`, current=pending. Finally `PollingApi`.
`PollingApi` (request byte): 0x10 -> `InitFieldSocketM(fieldName)` (create/retarget CFieldSocket then SetAPI); 0x30 -> `new GameOver`, SetAPI(0); 0x21 -> `GetRegDat(0x2f, regdatId, -1)` monster table, `InitBtlSocket()`, socket->cb = `cbBattle`, SetBtlBGMNumber/SetPC/SetMonsterSet. `StartBattle(param, field)` is two-step: with param -> request 0x20 (field name cleared, optionally set); with null param while 0x20 -> 0x21.
`cbBattleA(code, ...)`: code 0 (battle over): outcome=`BtlSocket+0x16c&3`: 2|3 -> [1]=0xff, request field; 1 -> [1]=0, game over unless [2] flag then field (FieldPreLoadCancel); 0 -> [1]=1, field. code 1 -> `FieldPreLoad(fieldName)`.
`ChkResetPause(pad, pauseEnabled, resetEnabled)`: reads pad real state (+ d-pad-up if left stick gauge>=0.1), `CApp::CheckReset(.., GetTimer, 0)` -> `CApp::Reset`, `CApp::CheckPause(..,0)` and pauseTimer==0 -> `CApp::Pause`, pauseTimer=reload.

### SSHApi (8 bytes, vtbl at +4) `{+8 __dt, +0xc preLoad(1), +0x10 Start(1), +0x14 closeInquiry(0), +0x18 Pause(bool), +0x1c Reset(int)(0)}`.
`SSHApi::Pause(false)` with no `CPauser::sys` creates CLSDPauser (0xc0) or CPauser (0xb8) depending on SSHSys flags b6. Derived classes put SSHApi first, CPolObj second (+8); Polling is reached via `@8@Polling` thunk.

### SysTool statics: LocalPath[8] 0x3f8870 ("", JPN/, USA/, GBR/, FRA/, GER/, ITA/, SPA/), pDataPath 0x40ac10, timer/vtimer/delta/counter/fraction/timerScale 0x40ac14..28.
`GetFullPathName(name)`: `pDataPath+name`; if `SearchFile` fails -> `AddLocalPath(buf, Language)` inserting the language dir *before the file name*. `GetLanguage()` maps `sceScfGetLanguage` {0:1(JPN),1:2(USA),2:4(FRA),3:7(SPA),4:5(GER),5:6(ITA)}.
**US data files use the extension `.NA`** (string `common/sshmes.na`).

### CDMYStage (0x60): SSHApi@0, CPolObj@8 (vtbl@+0x1c = 0x407490 @8 table), `+0x24 u8 inited`, `+0x28 openingMessage*`, `+0x2c GsxCamera*`, `+0x40/+0x50 two vec4`. Start: poller entry prio 0x80, `ReadOrder("opening/opening.dat", _dvd_callback)`, `new openingMessage`, `changeDispMode(0x280,0x1c0)`, LSDPlayer::PlugDevice x3 (once). Polling: when `_dvd_callback` has set the texture pool, `openingMessage::initialize`. **US**: `openingMessage` moved into the new OPENING.BIN overlay (loaded by `preLoad` via `Overlay::Load("OPENING.BIN")`, load addr 0x45ea80) and `opening(u8 mode)` exists.
### GameOver (JP 0x54, US 0x64): Menu subclass; `Polling` = `Menu::Run`; registers poller 0x48 prio 0x80, creates a white-background GsxCamera if `CApp::camera==0`; scene "MENU/MSD/GAMEOVER.MSD" via GameOverScene (section F).
### CPauser (0xb8): see port pause.rs (state 0 init -> 0x10 wait -> 0x20 unpause -> 0xff). Uses `PauseData` bitmap @0x401870, `MaskData`.
