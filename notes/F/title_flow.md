# Title / opening flow and game over (JP demo)

Entry: `opening()` (0x003a7ea0) is called by `main` (via `InitMain`) and by `GameOverScene::ShiftTitle`; it ends with
`SSHSys::SetAPI(new CDMYStage)`. `CDMYStage::Start` (section A) creates `openingMessage` (0x003a83f0) and calls `initialize`.
Rust: `sh2_menu::title` (state machine as pure `poll(inputs) -> commands`), `sh2_menu::gameover`.

## openingMessage (`Polling` switch on state @0xe0)

`initialize`: creates `LSDPlayer` if needed (callback sets `m_bLSDStart`), a `primSound`, the fader window (`mSetupFader`: one 640x448
black polygon, `fadein(1)`), applies the saved options (`SaveMenuSection::Update`), then state = **0x1a** the first time this boot
(`DAT_0040ad44` unset) else **0x10**.

```
0x1a trial splash: when fader clear -> DispMode 640x448, show splash texture 0x14, fadeout(32)    (mSetupTrialWin)
0x1b wait 450 frames or O/START -> fadein(32) -> 0x1c: release splash, -> 0x0a
0x0a movie: DispMode 640x448; when LSDPlayer idle: startStream("opening/demo.lsd") -> 0x0b
0x0b wait stream start; O/START => Pause+Exit (skip); stream end => 0x0c      (fader white, fadein(8))
0x0c wait fade -> 0x10
0x10 title: if cover not clear and not fading: build title (6 prim2D layers: logo + 5 additive swirls rotating +-0.0002 rad/frame, BGM803.SSV)
      fadeout(32); once clear -> timer=0, 0x11
0x11 PRESS START: pulse polygon 4 alpha 0..0x7e..0 over 128 frames; any O/START => SE 2, stop BGM, build menu (2 rows), 0x12;
      after 0x4b1 frames idle => stop BGM, fade to black, attract battle (0x13 -> 0x23)
0x12 menu "ゲームを始める / 振動設定": O on row 0 => black fade -> 0x13 (next 0x26); row 1 => 0x18; idle 0xe10 frames => attract battle
0x13 wait fade, release title+menu windows, state = next (+0xe4)
0x18/0x19 vibration screen (ON/OFF): O sets MENU option bits0-1 (ON = 0, OFF = 2) + CVibeMan::SetMode; X cancels; -> 0x12
0x23 attract battle: DispMode 512x448, SetFFMode, openingBattleDemo::start -> 0x24 (wait +0x23 started) -> 0x25
0x25 demo finished: if not skipped by a key -> 0x10 (title) else 0x0a (movie again); delete demo
0x26 new game: GetWorldMapInfo() fields cleared, FieldMapJump("WORLDMAP", 0), fadeout(1), DispMode 512x448 -> 0x27 -> self delete
0x00/0x01/0x03 initial device check (dataAccess mode 2) -- unused in the demo flow; 0x15..0x17 load via dataAccess (unused here)
0x1d..0x1f play CM/PV by menu row (lsd/cm_a.lsd, cm_b.lsd, pv.lsd) -- unreachable from the demo menu; 0x20..0x22 sub menu wait on m_MenuNum == 2
```
Buttons: O = 0x2000, START = 0x8, `any = 0x2008`.

## openingBattleDemo
`initialize(texPool, layer)`: picks entry `m_mons` of the 3-entry table {monster set, scenario, battle, bgm 0x191, party}:
`{3,0,0x4d,0x191,[5,0xb]}`, `{8,1,6,0x191,[0,1,2]}`, `{0x14,2,0x1c,0x191,[0,1,5,6]}`; clears the party sets, `JoinParty`/`JoinBattle` the members
and `BtlSaveSec::DemoInitPCParam(pc, scenario)`. `Polling`: 0 wait start -> banner `prim2D` (uv 1,1,0xd2,0x78 at y=320) fade-in, 1: `InitBtlSocket`,
`SetPC(count, members)`, `SetBtlBGMNumber`, `SetMonsterSet(RegDat 0x2f[monset])`, 2: run (skippable after 300 frames, hard limit 0x708 frames or battle fader mode 3),
3: `BtlSocket::BattleEnd`, banner released when the battle callback (event 0) reports done, 4: finished flag.

## GameOver
Created by `SSHSys::PollingApi` for transition code 0x30 (see section A). `GameOver::__ct` creates `GameOverScene`
(`OrderFile("MENU/MSD/GAMEOVER.MSD")`), registers with the poller and makes a default `GsxCamera` if none. Scene states:
`GetReady` (pick image `GO_%03d.TEX`), `ReadData` (texture arrived -> sprite+window open, effect from window record 0), `Realize`
(wait O once open or 5000 ticks), `ExitRealize` (close; if MENU byte 0x308 == 0 -> `ShiftTitle` else question window 1 "ロード しますか？" Yes/No with cursor 0),
`SelectLoad` (up/down/O; selected text id 0 = Yes creates `dataAccess` mode 1), `ExitSelectLoad` (No -> title; Yes -> `dataAccess::start(0, cursor pos)`).
`ReceiveEvent(5 loaded)` destroys the menu; `(4 finished)` returns to the title.
