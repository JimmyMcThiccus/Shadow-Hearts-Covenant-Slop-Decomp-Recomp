# OPENING.BIN (US retail title overlay) and the retail title flow

Section I.  Ghidra program `SH2US_OPENING.BIN` (import of `overlays/SH2US_OPENING.BIN`, image base `0x0045ea80`; 104 functions, all named).
Cleaned C: `decomp/I/opening.c`.  Rust: `port/crates/sh2_menu/src/title.rs`, `title::retail` (`Build::Retail`, `title::Machine`).
Disc folder copy: `OPENING.BIN` (57,472 B) is a plain disc file (not in `OPENING.PKB`); the title *data* is `OPENING.PKB` =
`BGM803.SSV` (7.9 MB), `DEMO.LSD` (76.5 MB), `INSTALL.DAT` (1.5 MB, **never referenced by the executable**), `OPENING.DAT` (2.3 MB), `THEATER.DAT` (1.4 MB).

## 1. Image layout

```
0x45ea80  MWo3 header: group 3, load 0x45ea80, text 0xdc40, data 0x400, bss 0 (!), ctor table 0x46cb00..0x46cb00 (empty), name "OPENING.BIN"
0x45eb00  code (first function = event callback 0x45eb00)  ...  0x46c6b8   (0xd918 bytes of code in 104 functions)
0x46c700  data (0x400): tbl_title_poly_pos, tbl_menu_item_pos, tbl_menu_decor_rect/uv, tbl_devwin_items, ptmf table, 5 strings
0x46cb00  end of image (file size 0xe080)
```
Notes
* No relocations, no static constructors.  The overlay's **globals live in the main image's `.sbss`** (0x440030..0x440060, reached with `gp`
  from SLUS) and its **vtables are pre-placed in main `.data`** (0x43f7c0..0x43f980; see the label list below) -- the overlay only holds code
  and read-only tables.  Its entry "function" (0x45eb00) is not an entry point but the *event callback* `cbOpeningEvent(event, a1, a2)`
  that is handed to `Menu`/`dataAccess` objects.
* Strings in the overlay: `opening/demo.lsd` 0x46c900, `OP_00_U` 0x46c918 (first map of a new game), `OPENING/BGM803.SSV` 0x46c9d0,
  `/BASLUS-20347-*` + `/NOPNOP-NOPPP-*` 0x46ca30 (memory-card directory patterns), `saveLoad/saveLoad.dat` 0x46ca40.
* Callers in the main image: `CDMYStage` (0x415c50..0x4162f0) loads it with `Overlay::Load(&SSHSys::sys->overlay, "OPENING.BIN", CBOverlay, 0, this)` from
  `preLoad`, creates `openingMessage` through the overlay's ctor (0x45eb60) and unloads it in `closeInquiry`.

## 2. Classes in the overlay (104 functions)

| group | functions | JP counterpart | retail change |
|---|---|---|---|
| `openingMessage` | 0x45eb40..0x462e70 (22) | JP 0x3a83f0..0x3ab500 | rewritten state machine (0x29 states), 5-row menu, device check, disclaimer, options |
| `install` (stub) / `primCursor` dtor | 0x462dc0, 0x462f40 | JP 0x3a7d00 `install` | `install::start` kept, never called |
| `deviceChecker` | 0x462f60..0x464900 (22) | JP 0x3990f0..0x399d60 | new modes (`mCheckSystem`), merges the system-file common block into `TitleShared` |
| `dataAccess` (boot check only) | 0x464bb0..0x468830 (15) | JP `dataAccess` (mInitialDeviceCheck) | only the **initial device check** (mode 2); load/save screen stays in main (0x3d37d0..) |
| `OptionScene` | 0x468aa0..0x469f90 + 0x46a430 (13) | none (JP only had the vibration row) | new Options screen (vibration / sound out / brightness / one more 2-way option) |
| `CursorScene`, `PictureScene`, `HelpScene`, `PanelScene` | 0x46a5b0..0x46c650 | none | helper `MenuScene`s of the Options menu |
| `OptionMenu` | 0x46adb0..0x46bdf0 (8) | none | `Menu` subclass (0xa40 B) hosting the above scenes |

Function map (name, size, JP address when the same mangled name exists in `SLPM_602.19`):

| US addr | size | name | JP addr (same name) | role |
|---|---|---|---|---|
| 0x0045eb00 | 0x38 | `cbOpeningEvent` | - | event sink for Menu/dataAccess callbacks: stores (event,a1,a2) in 0x440038/30/34 |
| 0x0045eb40 | 0x14 | `LSD_CB__14openingMessageFv` | 0x003a8340 (0x14) | LSDPlayer start callback -> g_lsd_started=1 |
| 0x0045eb60 | 0x130 | `__ct__14openingMessageFP10TitleShared` | - | ctor (0x120 B); takes the shared title state |
| 0x0045ec90 | 0x188 | `__dt__14openingMessageFv` | 0x003a8500 (0x170) | dtor (releases fader, poller entry, music, sound) |
| 0x0045ee20 | 0x40 | `Finish__14openingMessageFv` | - | state=0x28 + one more Polling (owner asks the title to end) |
| 0x0045ee60 | 0x24 | `SetReturnMode__14openingMessageFUc` | - | +0x94 return mode (from opening(u8)) |
| 0x0045ee90 | 0x1f4 | `initialize__14openingMessageFP9BufMemoryPFiPv_vPv` | - | create primTex/primSound/fader, pick first state |
| 0x0045f090 | 0x2a4 | `changeDispMode__14openingMessageFii` | 0x003a87b0 (0x2a4) | new GsxCamera for 640x448 / 512x448 |
| 0x0045f340 | 0x1788 | `Polling__14openingMessageFv` | 0x003a8a60 (0x15b8) | THE state machine (0x1840 B) |
| 0x00460ad0 | 0x24 | `CBEntry__14openingMessageFiPv` | 0x003aa020 (0x24) | callback target: cb_event = event |
| 0x00460b00 | 0x178 | `mSetupFader__14openingMessageFv` | 0x003aa050 (0x108) | fullscreen black primWin, cover(1) |
| 0x00460c80 | 0x8c | `mReleaseFader__14openingMessageFv` | 0x003aa160 (0x48) |  |
| 0x00460d10 | 0x160 | `mSetupTrialWin__14openingMessageFi` | - | one-polygon window showing opening.dat #idx (disclaimer) |
| 0x00460e70 | 0x8c | `mReleaseTrialWin__14openingMessageFv` | 0x003ab0c0 (0x48) |  |
| 0x00460f00 | 0xd5c | `mSetupTitleWin__14openingMessageFv` | 0x003aa1b0 (0xccc) | title logo window, 7 prim2D swirls, BGM803 stream |
| 0x00461c60 | 0xf8 | `mReleaseTitleWin__14openingMessageFv` | 0x003aae80 (0xbc) |  |
| 0x00461d60 | 0x8c0 | `mSetupMenuWin__14openingMessageFv` | - | 5-row menu window + cursor |
| 0x00462620 | 0xb0 | `mSetupLSD__14openingMessageFv` | - | new LSDPlayer + 3 PlugDevice + start callback |
| 0x004626d0 | 0x5f4 | `mMoveMenuCursor__14openingMessageFUs` | - | cursor topology (5 slots) |
| 0x00462cd0 | 0xe8 | `mReleaseMenuWin__14openingMessageFv` | 0x003aaf40 (0x70) |  |
| 0x00462dc0 | 0x94 | `__dt__10primCursorFv` | 0x003a3bd0 (0x94) | primCursor dtor (menu cursor holder, 0x10c B) |
| 0x00462e60 | 0x8 | `@24@__dt__14openingMessageFv` | 0x003ab500 (0x8) | DelayDeleteObject thunk (this-0x18) |
| 0x00462e70 | 0xcc | `mInitNewGame__14openingMessageFv` | - | New Game init (SaveData reset, world-map flags, MENU[0x80]=0) |
| 0x00462f40 | 0x20 | `start__7installFv` | 0x003a7e50 (0x48) | sets flag +0xbf (HDD install) - dead |
| 0x00462f60 | 0x3c | `__ct__13deviceCheckerFv` | 0x003990f0 (0x3c) |  |
| 0x00462fa0 | 0x94 | `__dt__13deviceCheckerFv` | 0x00399130 (0x84) |  |
| 0x00463040 | 0x68 | `initialize__13deviceCheckerFPUc` | - |  |
| 0x004630b0 | 0x6c | `checkDeviceAll__13deviceCheckerFv` | 0x00399220 (0x38) |  |
| 0x00463120 | 0x38 | `checkPollMC__13deviceCheckerFv` | 0x00399260 (0x38) |  |
| 0x00463160 | 0x34 | `finishPollMC__13deviceCheckerFv` | 0x003992a0 (0x34) |  |
| 0x004631a0 | 0x94 | `Polling__13deviceCheckerFv` | 0x003992e0 (0x74) |  |
| 0x00463240 | 0x80 | `recheck__13deviceCheckerFv` | - |  |
| 0x004632c0 | 0x73c | `mCheckSystem__13deviceCheckerFv` | - |  |
| 0x00463a00 | 0x32c | `mPollMC__13deviceCheckerFv` | 0x00399360 (0x304) |  |
| 0x00463d30 | 0x7ec | `mCheckAll__13deviceCheckerFv` | 0x00399670 (0x434) |  |
| 0x00464520 | 0x60 | `closeDevice__13deviceCheckerFv` | 0x00399ab0 (0x60) |  |
| 0x00464580 | 0x34 | `isChangeStatus__13deviceCheckerFv` | 0x00399b10 (0x34) |  |
| 0x004645c0 | 0x6c | `getActiveDeviceNum__13deviceCheckerFv` | 0x00399b50 (0x6c) |  |
| 0x00464630 | 0x124 | `getFreeDeviceNum__13deviceCheckerFPi` | - |  |
| 0x00464760 | 0x3c | `isMC1Active__13deviceCheckerFv` | - |  |
| 0x004647a0 | 0x3c | `isMC2Active__13deviceCheckerFv` | - |  |
| 0x004647e0 | 0x5c | `isOnlyHDD__13deviceCheckerFv` | 0x00399d00 (0x5c) |  |
| 0x00464840 | 0x3c | `getStatusE9__13deviceCheckerFv` | - |  |
| 0x00464880 | 0x3c | `getStatusEA__13deviceCheckerFv` | - |  |
| 0x004648c0 | 0x3c | `getStatusE8__13deviceCheckerFv` | - |  |
| 0x00464900 | 0x3c | `isHDD__13deviceCheckerFv` | 0x00399d60 (0x3c) |  |
| 0x00464940 | 0x270 | `mMcRawCheck__13deviceCheckerFv` | - |  |
| 0x00464bb0 | 0xbc | `DVD_CBFunc__10dataAccessFiP9BufMemoryiPcPv` | 0x00391cd0 (0xb8) |  |
| 0x00464c70 | 0x120 | `__ct__10dataAccessFv` | 0x00391d90 (0x134) |  |
| 0x00464d90 | 0x1d8 | `__dt__10dataAccessFv` | 0x00391ed0 (0x178) |  |
| 0x00464f70 | 0x230 | `initialize__10dataAccessFQ210dataAccess10ACCESSMODEPFiPv_vPv` | 0x00392050 (0x1c0) |  |
| 0x004651a0 | 0x244 | `Polling__10dataAccessFv` | 0x003922d0 (0x2018) |  |
| 0x004653f0 | 0x56c | `mSetupBG__10dataAccessFv` | 0x003942f0 (0x47c) |  |
| 0x00465960 | 0xcc | `mReleaseBG__10dataAccessFv` | 0x00394770 (0xa8) |  |
| 0x00465a30 | 0x2c0 | `mCheckDirKey__10dataAccessFi` | 0x00396f90 (0x280) |  |
| 0x00465cf0 | 0x3b8 | `mSelectItem__10dataAccessFi` | 0x00397210 (0x198) |  |
| 0x004660b0 | 0x244 | `mSetMainCursor__10dataAccessFi` | 0x003973f0 (0x13c) |  |
| 0x00466300 | 0x94 | `mReleaseMainCursor__10dataAccessFv` | 0x00397530 (0x60) |  |
| 0x004663a0 | 0xf8 | `mReleaseWin__10dataAccessFv` | 0x00396eb0 (0xe0) |  |
| 0x004664a0 | 0x120c | `mInitialDeviceCheck__10dataAccessFi` | 0x003976a0 (0x131c) |  |
| 0x004676b0 | 0x67c | `mSetupInitialWarning__10dataAccessFv` | 0x003989c0 (0x374) |  |
| 0x00467d30 | 0x9b8 | `mSetupProgressSystemSave__10dataAccessFv` | 0x00398d40 (0xcc) |  |
| 0x004686f0 | 0x140 | `mGrowProgress__10dataAccessFf` | - |  |
| 0x00468830 | 0x254 | `mSetupWarning__10dataAccessFPc` | 0x003955e0 (0x90) |  |
| 0x00468a90 | 0x8 | `@24@__dt__10dataAccessFv` | 0x003990e0 (0x8) |  |
| 0x00468aa0 | 0x1b4 | `__ct__11OptionSceneFv` | - |  |
| 0x00468c60 | 0x1cc | `__dt__11OptionSceneFv` | - |  |
| 0x00468e30 | 0x48 | `Release__11OptionSceneFv` | - |  |
| 0x00468e80 | 0x97c | `Create__11OptionSceneFv` | - |  |
| 0x00469800 | 0x80 | `Close__11OptionSceneFv` | - |  |
| 0x00469880 | 0x5c | `Run__11OptionSceneFv` | - |  |
| 0x004698e0 | 0x1a4 | `Apply__11OptionSceneFv` | - |  |
| 0x00469a90 | 0x2e8 | `stOpen__11OptionSceneFv` | - |  |
| 0x00469d80 | 0x210 | `stClose__11OptionSceneFv` | - |  |
| 0x00469f90 | 0x4a0 | `stMain__11OptionSceneFv` | - |  |
| 0x0046a430 | 0x178 | `UpdateHelp__11OptionSceneFv` | - |  |
| 0x0046a5b0 | 0x5c | `__ct__11CursorSceneFv` | - |  |
| 0x0046a610 | 0xac | `__dt__11CursorSceneFv` | - |  |
| 0x0046a6c0 | 0x94 | `Create__11CursorSceneFv` | - |  |
| 0x0046a760 | 0x48 | `Release__11CursorSceneFv` | - |  |
| 0x0046a7b0 | 0xb4 | `__ct__12PictureSceneFv` | - |  |
| 0x0046a870 | 0xf4 | `__dt__12PictureSceneFv` | - |  |
| 0x0046a970 | 0xb0 | `Create__12PictureSceneFv` | - |  |
| 0x0046aa20 | 0x98 | `Release__12PictureSceneFv` | - |  |
| 0x0046aac0 | 0x248 | `SetPicture__12PictureSceneFPUci` | - |  |
| 0x0046ad10 | 0x98 | `Open__12PictureSceneFv` | - |  |
| 0x0046adb0 | 0x304 | `__ct__10OptionMenuFiPFiPvP4Menu_iPv` | - |  |
| 0x0046b0c0 | 0x11c | `__dt__10OptionMenuFv` | - |  |
| 0x0046b1e0 | 0x724 | `Run__10OptionMenuFv` | - |  |
| 0x0046b910 | 0xd4 | `Step__10OptionMenuFs` | - |  |
| 0x0046b9f0 | 0x194 | `CreateScene__10OptionMenuFs` | - |  |
| 0x0046bb90 | 0xa8 | `Terminate__10OptionMenuFv` | - |  |
| 0x0046bc40 | 0x1ac | `OpenPanel__10OptionMenuFs` | - |  |
| 0x0046bdf0 | 0x94 | `ClosePanel__10OptionMenuFs` | - |  |
| 0x0046be90 | 0x8 | `@24@__dt__10OptionMenuFv` | - |  |
| 0x0046bea0 | 0xac | `__ct__9HelpSceneFv` | - |  |
| 0x0046bf50 | 0xfc | `__dt__9HelpSceneFv` | - |  |
| 0x0046c050 | 0x198 | `Create__9HelpSceneFv` | - |  |
| 0x0046c1f0 | 0x88 | `Release__9HelpSceneFv` | - |  |
| 0x0046c280 | 0xf8 | `SetText__9HelpSceneFPCce` | - |  |
| 0x0046c380 | 0x84 | `__ct__10PanelSceneFv` | - |  |
| 0x0046c410 | 0xc4 | `__dt__10PanelSceneFv` | - |  |
| 0x0046c4e0 | 0x16c | `Create__10PanelSceneFv` | - |  |
| 0x0046c650 | 0x68 | `Release__10PanelSceneFv` | - |  |

Method: JP `openingMessage`/`deviceChecker`/`dataAccess` could *not* be matched by n-gram (the retail functions are rewritten), so names come from
decompile comparison; the names that coincide with a JP symbol keep it, new classes got descriptive names (`OptionMenu`, `OptionScene`,
`CursorScene`, `PictureScene`, `HelpScene`, `PanelScene`, `TitleShared`), marked "new" in the table.  Main-image helpers called from the overlay were named in
`SLUS_210.41` (prim2D/primTex/primWin/primSound/primMusic ctor+setters, `__nw__`, `__dl__`, `MsgTable`, `dataAccess` ctor/initialize/start/Polling,
`CDMYStage`/`openingBattleDemo` members); the prim* names come from the order/size of the JP `prim*` classes (same toolkit, smaller code) and are
role-confident rather than byte-verified.

## 3. Shared state: `TitleShared` (SLUS .bss 0x0045e940, getter 0x415a60)

| off | meaning |
|---|---|
| 0x00..0xff | in-RAM image of the **system common block** (EE RAM 0x100000, `SystemFile::StoreCommon/FlushCommon`): [0],[1]; flags1[0x40] @+2; flags2[0x40] @+0x42; [0x82],[0x83]; u32 @0x84 (newest timestamp), @0x88; rest.  `deviceChecker` ORs every device's block into it (timestamp = max); `CDMYStage::Start` ORs the live block back in (bytes 0..0x82). |
| 0x100 | merged once (`cRam0045ea40`) |
| 0x101 | `save_found`: a usable save exists -> default menu row = Continue |
| 0x102 | `intro_done`: device check + disclaimer + opening movie were already shown since power-on (the retail equivalent of JP `DAT_0040ad44`) |
| 0x104 | device-save mask (`GetDeviceSaveMask` 0x415a70 / `SetDeviceSaveMask` 0x415a80) |

Bytes used by the title: `common[1] != 0` enables the **Theater** row; `common[0x14]` bits 6/7 select how many attract-mode battles are in rotation.
New Game copies the whole 0x100 bytes to 0x100000 (`mInitNewGame` + `InitNewGameFlags(mask)`), so unlocked extras survive a new game.

## 4. The retail flow (`openingMessage::Polling`, state word +0x100)

Pad: `key` = trigger & 0x2008 (CIRCLE or START).  `cover(n)`/`reveal(n)` = the fader (`primWin` at +0x74): cover = fade to black (JP `fadein`), reveal = fade
in the picture (JP `fadeout`); `fader.clear` (+0x102) is set when a reveal has finished; `fader.busy` (+0x118).

```
power on -> main -> SSHMain -> opening() = SetAPI(new CDMYStage) -> preLoad(OPENING.BIN) -> Start: new openingMessage, ReadOrder("opening/opening.dat")
 initialize():  [cover(1)]  intro_done==0 ? state 1 : (return_mode ? reveal(1), state 0x0b : state 0x12)
 0x00 wait RegDat+JRing data                             (only when initialize was not reached)
 0x01 boot device check: new dataAccess(mode 2) in OPENING.BIN, reveal(1)            -> 0x02
 0x02 events from the check: 6 = "needs the 512x448 UI" -> DispMode(0x200,0x1c0); 3 = save found (TitleShared.save_found=1) / 2 = nothing -> 0x04
 0x04 event 4 (check UI finished) -> cover(1) -> 0x05
 0x05 DISCLAIMER: DispMode(0x280,0x1c0); window showing opening.dat #0 ("This story is a work of fiction ... living or dead."), reveal(0x20) -> 0x06
 0x06 hold 450 frames (7.5 s) or O/START (SE 2)           -> cover(0x20) -> 0x07 -> release, reveal(1) -> 0x0b
 0x0b OPENING MOVIE: new LSDPlayer + 3x PlugDevice; when the player is idle: startStream("opening/demo.lsd") -> 0x0c
 0x0c when the first frame arrived (LSD_CB): fader colour white; movie ends or O/START -> cover(speed 4 natural / 0x20 skipped) -> 0x0d
 0x0d after the cover: (if still playing: Pause + stop) wait 16 frames (0x0e), delete LSDPlayer, SetFFMode(0,1,1)             -> 0x12
 0x12 TITLE: DispMode 640x448, mSetupTitleWin (5 polys + 7 swirl prim2D + BGM803 stream), reveal(0x20)                  -> 0x13
 0x13 PRESS START: swirl rotation, "Press START button" polygon pulses (alpha 0..0x7e..0 over 128 frames)
        O/START -> SE 2, mSetupMenuWin -> 0x14 ;  1201 frames idle -> stop BGM, cover(0x20), event 2 (attract battle), -> 0x15 (next 0x23)
 0x14 MENU (5 rows, see 5): d-pad -> mMoveMenuCursor; O/START -> SE 2, stop BGM, cover(0x20), -> 0x15 with next_state by row:
        New Game   -> copy common block to 0x100000, mInitNewGame, InitNewGameFlags      next 0x26
        Continue   -> new dataAccess (main image, load mode)                              next 0x17
        Options    -> new OptionMenu(first scene 0x10, cbOpeningEvent)                    next 0x1d
        Installation/Theater -> owner event 3 (CDMYStage::CBTitle(3))                      next 0x20
      3600 frames without input -> attract battle exactly like the PRESS START timeout
 0x15 wait cover; release title + menu (+ BGM) -> next_state
 0x17 Continue: DispMode 512x448, dataAccess::start(STARTMODE 1) (go straight to the slot list), reveal(1) -> 0x18
 0x18 event 5 (slot loaded; dataAccess already did FieldMapJump(saved map)) -> 0x27 ; event 3 (quit) -> 0x19 -> event 4 -> cover(1) -> 0x12
 0x1d OPTIONS: reveal(0x10), start flag (menu+0x41=0x11) -> 0x1e: wait g_opening_event==5 (menu destroyed) -> cover(0x10) -> 0x1f -> 0x12
 0x20 THEATER/exit: reveal(0x20); event 4 + DelayDelete -> 0x21 (CDMYStage then runs StartTheater)
 0x23 ATTRACT: release BGM, DispMode 512x448, SetFFMode(0,1,2), event 4 + DelayDelete   (CDMYStage starts openingBattleDemo -> BtlSocket)
 0x26 NEW GAME: FieldMapJump("OP_00_U", 0) (JP demo: "WORLDMAP"), reveal(1) -> 0x27 -> event 4 + DelayDelete -> 0x28 (terminal)
 0x16 / 0x22 are dead (HDD install start / back).
```

### Title menu items (opening.dat #7 / #8 / #9 = disabled / normal / highlighted, 128x160, 32 px rows)
1. **New Game**  2. **Continue**  3. **Options**  4. **Installation**  5. **Theater** (row order = `Row` enum; verified by rendering `opening.dat` #7-#9).
Layout (positions @0x46c720): New Game (108,264), Continue (268,296), Options (406,264), Installation (108,324), Theater (406,324); 6 frame pieces from #10 @0x46c750.
Cursor topology (`mMoveMenuCursor`): `0 -> right -> 2`, `0/2 -> down -> 1`, `1 -> left/right -> 0/2` (or to the lower row when the remembered "row" flag says so),
`1 -> down -> 3 (if Installation enabled) else 4`, `3 <-> 4` left/right, `3/4 -> up -> 1`.  Enablement: **Installation** needs `(SSHSys+0x3c & 7) != 0`
(row is drawn disabled and skipped otherwise; the code behind it is not present in the retail executables -- `INSTALL.DAT` is dead data); **Theater** needs
`TitleShared.common[1] != 0`.  Default row: Continue when a save was found, else New Game.  Rows 3 and 4 share one code path (event 3 -> `StartTheater`
-> FIELD.BIN object 0x553ad0, `opening/theater.dat`), so Installation is effectively unreachable.

### Disclaimer / boot device check texts (opening.dat message table #20, 44 strings)
"No memory card (8MB) (for PlayStation 2) inserted ...", "Insufficient free space ... at least %dKB", the "PlayStation BB Unit" HDD variants, "You can create the system data
necessary for a Shadow Hearts II save. Would you like to create it?" (message 17 = result class 0x10), "Start the game." / "Don't start the game." choices,
"Creating system data...", "Finished creating system data.", "System data already exists.".  The text comes from the data bundle, not from the executable --
**there is no `GetLanguage` / `sceScf` call anywhere in OPENING.BIN**; the only localisation hooks are the data files themselves (US disc: English images and strings).

## 5. Boot device check (`deviceChecker` + `dataAccess` mode 2)

`deviceChecker` (0x100 B, CPolObj, vtbl 0x43f7f0): modes 1 `mCheckAll`, 2 `mPollMC` (hot-plug), 3 `mCheckSystem`.  Device records at `this+0xc0+d*0x10`
(d = 0 memory-card slot 1, 1 slot 2, 2 "PlayStation BB Unit"): present, has-system-file, has-save-dir, error flags, free KB.  `mCheckAll` runs `SaveData::Open(d)`
(io state 0x457f14: 1 busy, 2 ok, 3 failed), reads the slot headers (0x457f10), ORs the device's system common block into `TitleShared`, counts saves and finishes with
`mMcRawCheck` (sceMc probe of both ports).  `dataAccess::mInitialDeviceCheck` (state @+0x12c, 0..14) turns the result into a message class (+0x134, 0..0x10 = message id
class+1 of opening.dat #20) and a Yes/No list; events to the title: **6** UI needed, **3** save found, **2** nothing usable / declined, **4** finished.

## 6. `CDMYStage` (retail, main image 0x415c50..0x4162f0) and `opening(u8)`

`CDMYStage` (SSHApi + CPolObj, 0x2c bytes allocated) keeps a static state `0x43ff0c`: 1 load needed -> 2 loading -> 3 running -> 4 closing -> 5 ready to unload -> 0.
* `preLoad` (every frame until it returns 1): `Overlay::Load("OPENING.BIN")`; `CBOverlay` (0x415ee0) sets state 3.
* `Start`: merge `0x100000` into `TitleShared`, `new openingMessage(&TitleShared)`, `changeDispMode(0x280,0x1c0)`; if not returning, `ReadOrder("opening/opening.dat", _dvd_callback)` (the callback stores
  the BufMemory in `0x43fef8` and calls `StartTitle`, which calls `SetReturnMode` + `initialize`).
* `CBTitle(event)` (0x415d70): remembers the last event, event 4 forgets the title.  `Polling`: event 2 -> create `openingBattleDemo`, state 4, pending demo; event 3 -> pending theater;
  once the title reports 4 the pending action runs (`openingBattleDemo::start` or `InitFieldSocketCB(StartTheater, 0)`) and the stage goes to 5; `closeInquiry` then unloads `OPENING.BIN`.
* `opening(u8 mode)` (0x415b40) = `opening()` + `SetReturnMode(mode)`; called by the attract battle when it ends: `mode = not_skipped`.
  `ReturnToTitle` (0x415b20) = request 0x40 target (SSHSys), see `us_delta.md`.

## 7. Attract-mode battles (retail `openingBattleDemo`, main image 0x416510..0x416ed0)

* Trigger: 1201 idle frames on PRESS START or 3600 idle frames on the menu.  The title ends (events 2 then 4), `openingBattleDemo` (a CPolObj, 0x58 B) is created and `start()`ed;
  Polling: banner `prim2D` (layer 0xe, opening.dat data, uv (1,1,0xd2,0x78)) fades in, `InitBtlSocket` + `SetPC` from the MENU party (members set with `JoinBattle`) +
  `SetMonsterSet(RegDat(0x35, monset))` + `SetBtlBGMNumber`; this `SetAPI(BtlSocket)` replaces `CDMYStage` in `SSHSys` and unloads OPENING.BIN.
  Runs up to 0xa8c = 2700 frames (45 s); a key after 60 frames cuts it (`not_skipped = 0`); the battle callback event 2 / 0 end it; then **`opening(not_skipped)`** re-creates the title:
  not skipped -> the opening movie plays again (state 0x0b), skipped -> straight to the title (0x12).
* Table @0x4306b0, six entries `{monset, scenario, battle, bgm, party[4]}`:

| # | monset | scenario | battle | bgm | party |
|---|---|---|---|---|---|
| 0 | 3 | 0 | 77 | 401 | 5, 11 |
| 1 | 16 | 1 | 6 | 401 | 0, 1, 2 |
| 2 | 82 | 2 | 28 | 401 | 0, 2, 5, 6 |
| 3 | 146 | 3 | 42 | 407 | 8, 9, 10 |
| 4 | 227 | 4 | 89 | 405 | 1, 4, 6, 7 |
| 5 | 249 | 5 | 73 | 403 | 0, 2, 3, 5 |

  Rotation (static index 0x43ff10) by progress bits `v = (common[0x14]&0x40 ? 1:0) + (common[0x14]&0x80 ? 1:0)`: v=0 cycles 0..2, v=1 cycles 3..5, v=2 cycles 0..5.
  (JP demo: 3 fixed battles `{3,8,0x14}`.)

## 8. DEMO.LSD trigger

`opening/demo.lsd` (OPENING.PKB, 76,517,344 B, LSD format see `notes/E/lsd_format.md`) is streamed by `LSDPlayer::startStream` (0x3c90d0) from state 0x0b: after the disclaimer on the first boot
(`intro_done == 0`) and after every attract battle that ended on its own.  The player is created with three `PlugDevice` registrations (0x4597d0 / 0x459940 / 0x459840) and a start callback; fader white
around the movie, 4 frames at the natural end / 0x20 frames when skipped, then 16 idle frames before the player is deleted.  JP's CM/PV rows (cm_a/cm_b/pv.lsd) are gone; the **Theater**
(FIELD.BIN, `opening/theater.dat`) replaced them.

## 9. Open questions
* What sets `SSHSys+0x3c` bits 0-2 (Installation enable) and bits 3-5 (surround capability: `SaveMenuSection::UpdateSurround` 0x286eb0 and the Options item mask)?  Not written anywhere in SLUS or OPENING.BIN; probably by the FIELD overlay / Sdrv init.
* Theater rows: Installation and Theater take the same exit; whether `THEATER.DAT` shows an "installation" page when entered from row 3 is not visible in the title code.
* `FUN_003bc710(0,0)` (0x2150 B, called by `mInitNewGame`) is the global save-data default routine; not decompiled here.
* The meaning of the 4 option items' strings (OptionScene ids 1,2,3,6) lives in the MENU MSD; the exact labels were not extracted.
* Names of main-image helpers marked "prim*" are by order/size, not byte-verified.

## 10. Labels created in Ghidra
SLUS_210.41: `g_title_shared` 0x45e940, `__vt__14openingMessage` 0x43f7d0 (+DelayDelete 0x43f7e0), `__vt__13deviceChecker` 0x43f7f0, `__vt__10dataAccess_opening` 0x43f800,
`__vt__11OptionScene` 0x43f820, `__vt__11CursorScene` 0x43f860, `__vt__12PictureScene` 0x43f8a0, `__vt__10OptionMenu` 0x43f8e0, `__vt__9HelpScene` 0x43f910, `__vt__10PanelScene` 0x43f950,
`__vt__9CDMYStage` 0x43c0e0, `__vt__17openingBattleDemo` 0x43c120, `tbl_attract_battles` 0x4306b0, `g_stream_fade_state` 0x459aeb, battle extras 0x459ae0..0x459ae8.
SH2US_OPENING.BIN: tables `tbl_title_poly_pos` 0x46c700, `tbl_menu_item_pos` 0x46c720, `tbl_menu_decor_rect` 0x46c750, `tbl_menu_decor_uv` 0x46c7b0, `tbl_devwin_items` 0x46c810,
`tbl_option_scene_ptmf` 0x46c860, strings, globals `g_opening_event` 0x440038, `g_lsd_started` 0x44003c, `g_saveload_primtex` 0x44005c ...
