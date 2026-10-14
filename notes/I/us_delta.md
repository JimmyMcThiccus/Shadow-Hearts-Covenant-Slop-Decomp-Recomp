# US retail (SLUS_210.41, Jul 2004) vs JP demo (SLPM_602.19, Oct 2003): system-level deltas

Section I.  Addresses: JP / US.  Ghidra: names applied in `SLUS_210.41` (new functions got descriptive names; see the end).
Rust: `port/crates/sh2_core/src/{boot,ssh_sys,fileio}.rs` (`Region::Us`, `SshSys.retail`, `VolumeId`/`DiscIdentity`, `SysBtlParamUs`, `StreamFade`, ...);
`cargo run -p sh2_core --example retail_boot` (with `SH2_US_DISC_DIR`) shows that the retail disc boots through the same `PKFINFO.TBL` path.

## 1. Boot / disc / data names

| item | JP demo | US retail |
|---|---|---|
| `SSHMain` (0x23bec0 / 0x2387e0) | `sceCdMmode(1)` x2 | **`sceCdMmode(2)`** (DVD-ROM); IOP image `cdrom0:\MODULES\IOPRP271.IMG`, module lists `SIO2MAN MCMAN MCSERV PADMAN` / `IOPUTY FIO LIBSD SDRV_IOP` identical |
| data tables | `common/sshmes.jpn`, `common/sshdat.jpn` | **`common/sshmes.na`, `common/sshdat.na`** (rodata 0x434580 / 0x4345a0).  The retail disc still contains `.JPN` copies, the executable has no string for them |
| `PKFINFO.TBL` | 28,416 B, 1,775 entries (1,734 files) | 71,680 B, **4,437 files** (BTLDATA 1248, COMMON 22, EFFECT 318, FIELD 2091, LSD 90, MENU 650, OPENING 5, SAVELOAD 1, SHOP 2, SOLOMON 2, WORLDMAP 5 + `OPENING.BIN`, `FIELD.BIN`, `BATTLE.BIN` plain files).  Same name hash (`enCode`/`deCode`), same reader: `Disc::open` / `search_file` work unchanged (test `retail_disc_resolves_na_names`) |
| `SysTool::AddLocalPath` (0x23c950 / 0x239270) | inserts the language directory before the file name | **identical code**, same 8-entry table (`""`, `JPN/`, `USA/`, `GBR/`, `FRA/`, `GER/`, `ITA/`, `SPA/`; US table at 0x42d780, strings 0x4332c8..).  The retail disc has no such directories, so the fallback never finds anything |
| `SSHSys::GetFullPathName` (0x3b6600 / 0x3edc40) | `sprintf(buf,"%s%s",pDataPath,name)`; fallback index = `SSHSys::Language` | index = **MENU save section byte +0x18** (`sm_pSubstance->data+0x18`, default 1 written by `SaveMenuSection::SetDefault`); `SSHSys::Language` (now a byte at 0x43fdfc) is still written by `PathInit` but never read |
| `GetLanguage` (0x3b5f60 / 0x3ed470) | `sceScfGetLanguage` -> `{0:1, 1:2, 2:4, 3:7, 4:5, 5:6}` | `sceScfGetLanguage` is **inlined** (0x239430: OSD config word, `ver==0 ? bit4 : bits16..20`, plus a tool-region override when the BIOS region letter is `'T'`) and the result is `0x10 + JP value`: `{0:0x11, 1:0x12, 2:0x14, 3:0x17, 4:0x15, 5:0x16, default 0x12}` |
| `SysTool::SetPathname` | `pDataPath ? sprintf("%s%s") : strcpy` | same (format string `%s%s` at 0x433308) |
| `FileIOLib` default volume label | "DEFAULT" | "NotSetDiskName" (0x432628) |

Rust: `boot::Region::{Jp,Us}` (`sshmes()/sshdat()/cd_media_mode()/title_overlay()`), `boot::get_language_us`, `boot::us_scf_language`, `SshSys::get_full_path_name_us`.

## 2. `FileIOLib` (JP 0x22a910.. / US 0x228450..)

* Object is **0x13ac8 bytes (JP 0x13ae8)**: the run flag moves to +0x13924, the poller to +0x1393c, device string to +0x13a5c, entry count to +0x13ac0.  Disc bookkeeping that lived in the
  object (`diskState` +0x13934, `diskResult` +0x13938, `diskNo` +0x1393c, layer +0x13940, label +0x13944) is now in globals (state words around 0x43fc60..0x43fc68 / 0x440270.., label at 0x42cf40);
  `SSHSys::Polling` clears `fioBusy` when the *global* disk state is 0.
* `InitPkb(first)` (0x228880) gets a parameter.  `first != 0` (from `Initialize`): read ISO9660 PVD (sector 0x10), store the **volume label** (PVD+0x28, 0x15 bytes) and the **disc number**
  (`sscanf(PVD+0xbe, "%d")` of the volume set id; getter `SSHSys::GetDiscNo` 0x3eeb10).  `first == 0` (disc swap/retry): compare both; mismatch -> `diskState = 3`, `diskResult = -1`.
  JP compared only against "DEFAULT".  Rust: `fileio::VolumeId::from_pvd`, `DiscIdentity::check`.
* **HDD power-off handling**: `SetHddDeviceName` (0x228540) no longer registers `sceCdPOffCallback(PowerOffCallBack)` (JP 0x22d980: `sceDevctl(hdd0,0x5003)`, wait `0x4806`, `sceCdPowerOff`).  Instead
  `ResetSystem` (0x228770) clears the run flag, waits for the IO thread, **stops the LSDPlayer** (`Pause`, `FUN_003c91c0`, poll `Reset()` until idle) and issues `sceDevctl("hdd0:", 0x5003)` (HDD cache flush).
* `Initialize` no longer calls `sceCdDiskReady(0)` nor copies the default label; `fioCmdCall` takes six arguments (0x1b stack-passed extras).
* New `PrepareFile(path)` (0x229ea0): `gettokun` + `enCode` + `searchInfo` and clears the 0x100-byte read-ahead buffer (0x44ef60) -- used by streaming.
* Missing in US: `checkPFSFreeSize`, `PowerOffCallBack`, `gettokun(Pcc)` (the 2-arg overload).

## 3. `CApp::Run` (JP 0x3d7730 size 0x4c0 / US 0x409cc0 size 0x680)

Same skeleton (World update/render, system poller, game pollers if not paused, `m_pAppFunc`, ScreenBright, GS sync, DelayDelete drain, screenshot slots, VSync/flip, `UpdatePolBreakState`, `DoReset`), plus:
* **no-draw switch** (`CApp::SetNoDraw(u8)` 0x409ca0, byte 0x43fed4): when non-zero the frame skips `World::BeginUpdate/WorldRender/EndUpdate`, `World::GetPacket`, `ScreenBright::Draw`, the DrawSync
  and the per-frame h-count statistics (the scene owns the display: movie / transitions).  No caller in the main image (set from an overlay).
* **GS completion**: `sceGsSyncPath(0,0)` is replaced by `GsKickFinish` (0x40adc0: `DrawSync` + FINISH GIF packet) before the DelayDelete drain and `GsWaitFinish` (0x40ae20: send a FINISH
  packet, spin on `GS_CSR` bit 1, clear it).
* **Frame pacing**: the frame start h-count is sampled (`iVar10`); on the fast path it spins until `GsxGetVSyncCount() >= syncCount-1` before `DrawSync`/stats and `VSync`; on the slow path
  (`GsxGetVSyncCount() >= syncCount`) it measures the time since the frame start; if that already exceeds 0x289 h-counts it waits until 0x2a8 (running `GsKickFinish/GsWaitFinish` inside the wait loop) and then does DrawSync, stats and `GsxForceFlip` -- JP did DrawSync/stats first and flipped unconditionally.
* The screenshot table `capTbl` moved to 0x45e3b0 (bss grew; the overlay base 0x45ea80 is unchanged), capture-full message via `FUN_00232c40`.

## 4. `SSHSys` (JP 0x3b6130..0x3b74a0 / US 0x3ed650..0x3eeee0; object still 0xb0 bytes)

Layout: `_SysBtlParam` is **0x14 bytes** (5 party slots) so `btlResult[4]` moves to +0x54, `fieldName` to +0x58 (0x10 bytes before the unchanged `Overlay` at +0x68); the ctor (0x3edb80) zeroes the
battle-extras globals 0x459ae0..0x459af0.

New / changed behaviour
* **Request byte +0x36 = 0x40 (new): "return to title".**  `SSHSys::RequestTitle` (0x3ee600) sets it; `PollingApi` (0x3ee6a0) then runs `ReleaseResidentA` (0x3f7790: frees the object at 0x43fe84 through `FUN_004044b0`)
  and `ReleaseResidentB` (0x3f77c0: frees 0x43fe54 when its +0x7c flag is set), clears `btlResult[0]` and calls `opening()` (`ReturnToTitle` 0x415b20 -> `SetAPI(new CDMYStage)`).  Request 0x30 (game over) now also
  releases both residents and clears `btlResult[0]`.  (Rust: `req::TITLE`, `SshSys::request_title`, `take_residents_release`.)
* `PollingApi` also calls `StepStreamFade` (0x3eda50) every frame while the byte at 0x459aeb is non-zero: a deferred **500 ms fade-out + close of the custom battle BGM stream** (`Sdrv` commands 0xf / 0x11);
  armed by `cbBattleA` when a battle ended in game over with `flag0 && stream_a && stream_b` set.  (Rust: `StreamFade`, `arm_stream_fade_on_game_over`.)
* Battle start (request 0x21): `BtlSocket+0x18d/0x18e/0x18f` get the three flag bytes set by `SetBattleFlags` (0x3ee620, globals 0x459ae8..a), `flag0 == 2` is reset to 0, `flag0 != 0` selects
  `SetBtlBgmStream(a, b)` (0x368b10; `SetBattleBgmStream` 0x3ee670, globals 0x459ae0/e4) instead of `SetBtlBGMNumber`; `SetPC(count, pc)` is replaced by copying the 0x20-byte **party-set record #`pc[0]`** of the MENU section
  (`data + pc0*0x20 + 0x84`, the 5 party sets) into `BtlSocket+0x2c`; the monster set comes from `GetRegDat(0x35, id)` + `SetMonsterSet(count, table)` or, when the count byte is 0, directly by id (0x3687d0).
  (Rust: `SysBtlParamUs`, `BattleExtrasUs`.)
* `cbBattleA(code, arg, arg3)` (0x3ee3f0): `BtlSocket` outcome byte moved to +0x1a0; victory with `arg3 == 1` additionally calls `FUN_003f5dc0`; defeat arms the stream fade (above).
* `Polling` (0x3ed750): the current API is deleted and cleared as soon as `closeInquiry()` returns 0 (JP kept it in state 4 until the handover); `fioBusy` is cleared from the global disk state; otherwise identical.
* `DiskChange*` unchanged; `SetPauserType`/`GetFrameDelta` are in FIELD.BIN as before.
* New SSHApi *implementers*: **none**.  The SetAPI callers are `opening`, `opening(u8)` (new), `InitBtlSocket`, `InitFieldSocketM`, `PollingApi` (GameOver) and the new `InitFieldSocketCB` (0x3f4dc0), which
  creates the `CFieldSocket` in **callback mode** (`SetCallback` 0x3f6fc0 stores a hook at +0x34/+0x38; `CFieldSocket::Start` runs it instead of loading a map) -- used for the Theater (`StartTheater` 0x415be0 creates the FIELD.BIN object 0x553ad0, `opening/theater.dat`).
* `GameOver` is **0x64 bytes** (JP 0x54): `Menu` + camera (+0x58) + a `MenuSound` (+0x5c, 0x14c B, polled) + a streamed BGM object (+0x60, 0xc0 B, `FUN_00401980`); scene `GameOverScene` is 0x708 bytes.

## 5. Title / overlay

* New overlay **OPENING.BIN** (MWo3 group 3, load 0x45ea80, empty ctor table), loaded by `CDMYStage::preLoad`, unloaded by `closeInquiry`; see `notes/I/opening.md`.
* `opening()` (0x415aa0) unchanged in shape (`SetAPI(new CDMYStage)`, 0x2c-byte object); new `opening(u8 return_mode)` (0x415b40) used when the attract battle ends; `ReturnToTitle` (0x415b20) is request 0x40.
* `openingMessage`/`deviceChecker`/`dataAccess` (boot check) moved to the overlay; `dataAccess` (load/save) and `openingBattleDemo` stay in the main image (0x3d37d0.. / 0x416510..).

## 6. `RegDatApi::GetRegDat` (JP 0x37b6b0 / US 0x3b9540)

`sshdat` has **37 tables (JP 33)**, `sshmes` **47 (JP 44)**.  The switch grows from kinds `0x00..0x43` to **`0x00..0x53`** (+16): the plain per-file data kinds start at **0x2f** (JP 0x26) and run to 0x53 (files 0..0x24);
kinds `0x20..0x2e` are the name/description kinds (`GetFileEntry` pairs, e.g. 0x25 is a 4-way tier switch like JP 0x16).  The monster-set table is **kind 0x35** (JP 0x2f), used by `StartBattle` and the attract
battle.  Rust: `regdat.rs` still describes the JP kinds; the US tables need a second kind map (open).

## 7. Other small deltas seen
* `SSHSys::Initialize` is byte-identical in size (0x350); `SetPauseTmr`, `ChkResetPause`, `CBPause`, `ScreenCapture` unchanged.
* `mwOverlayInit` / `mwInit` / `mwExit` (0x3c58b0 / 0x3c5940 / 0x3c5930) identical; the US `__nw__/__dl__` are 0x3c56e0 / 0x3c5680.
* `main`/`CApp` ctor (0x21f6c0 / 0x21f780) unchanged; `capTbl`, `rebootPath` moved with the bss.
* EE-kernel patch code sits at the end of the US `.text` (0x429e90..0x437310: TLB-mapping helper for 0x70004000 and a thread/scheduler routine touching KSEG0 0x8007xxxx); the JP build has only `InitTLB`.

## 8. Names applied in SLUS_210.41 (new, no JP counterpart)
`RequestTitle__6SSHSysFv` 0x3ee600, `SetBattleFlags__6SSHSysFUcUcUc` 0x3ee620, `SetBattleBgmStream__6SSHSysFii` 0x3ee670, `StepStreamFade__6SSHSysFv` 0x3eda50, `GetDiscNo__6SSHSysFv` 0x3eeb10,
`PrepareFile__9FileIOLibFPc` 0x229ea0, `SetNoDraw__4CAppFUc` 0x409ca0, `GsKickFinish__Fv` 0x40adc0, `GsWaitFinish__Fv` 0x40ae20, `ReturnToTitle__Fv` 0x415b20, `opening__FUc` 0x415b40, `StartTheater__Fv` 0x415be0,
`InitFieldSocketCB__FPFv_vPv` 0x3f4dc0, `SetCallback__12CFieldSocketFPFv_vPv` 0x3f6fc0, `ReleaseResidentA/B__Fv` 0x3f7790/0x3f77c0, `GetTitleShared__Fv` 0x415a60, `Get/SetDeviceSaveMask` 0x415a70/0x415a80,
`InitNewGameFlags__FUc` 0x3f3e30, `GetGameSection__Fv` 0x3f4cd0, `GetWorldMapSection__Fv` 0x3f7c00, operator new/delete 0x3c56e0/0x3c5680/0x3c56c0/0x3c5660, plus the prim*/dataAccess/CDMYStage/openingBattleDemo names listed in `notes/I/opening.md`.
