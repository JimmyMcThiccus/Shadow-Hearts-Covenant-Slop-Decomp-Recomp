# Rewritten functions: what changed vs the JP demo (pass N6)

Scope: the 85 functions of the N5 cause group "rewritten (JP candidates, no confident pair)": 29 in SLUS_210.41, 43 in SH2US_FIELD.BIN, 13 in SH2US_BATTLE.BIN.  Each has a JP counterpart in the same class (or a clear JP role) but the US body differs too much for a byte/shape match.  Names are in `us_map_N6.txt` (rows with cause `rewritten`): 63 got the JP-style name `Method__Class` (JP name carried over because the role is the same), 22 got `Retail_<Class>_<Method>` because the behaviour is new.

Evidence method: JP name looked up in the JP program of the pair (SLPM_602.19, SH2JP_FIELD.BIN, SH2JP_BATTLE.BIN); decompiled both; compared size, line count and the callee set.  The "changed" statements below come from that comparison plus reading the US decompile; they are behavioural, not byte-level.  Source for the table: tools/I_N6/rewdiff.py.

## 1. Menu windows moved from primWin/primCursor to MenuObj / Cursor / CPoller (FIELD, 30 functions)

Applies to every `mRelease*Win`, `mSetup*Win`, `mSetup*Cursor`, `removeCursor` in `solomon`, `solomonThm`, `solomonCursor`, `tailor`, `worldMap`, `worldMapThm`.

* Release: JP calls `primWin::DelayDeleteRequest()` / `primCursor::DelayDeleteRequest()`.  US calls `MenuObj::ReleaseOT()` and then drops the object (the window is unlinked from the ordering table first; JP queued a delayed delete).  US bodies are about 0x40 bytes larger for that reason (e.g. `mReleaseMainWin__7solomon` 0x50 -> 0x90).
* Cursors: JP builds `primCursor` (`__ct__10primCursor`, `createCursor`, `changePri`, `leaveWin`).  US builds `Cursor` (`__ct__6Cursor`, `Create(r,g,b,a)`, `GetPlace(MenuWindow, x, y)`, `Select(MenuPlace*)`, `QuickMove`, `Leave`) and attaches it with `MenuObj::AddOT`.  So `mSetupMainCursor` is 0x110 -> 0x210 and `removeCursor__13solomonCursor` calls `Leave` + `ReleaseOT`.
* Setup: JP window setup is `primWin::initialize`, `fadein`, `setPolyRGBA`, `createText(..., GetRegDat(...))`.  US registers the window with `CPoller::Entry(CPolObj*, int, bool)` (polled objects), builds text with `MsgTable::GetString(i)` and `primTex::setTextArea(MenuWindow*, x, y, w, h, bool)` / `setWinTex`, and uses `menuSelectItem(primWin, int, primCursor)`.  Text now comes from the message table (localised strings), not the RegDat string records.  `solomonThm::mSetupThmBaseWin` 0x6b0 -> 0xa10 and now calls `mSetupHintWin` itself.
* `initialize__10solomonThm` additionally allocates a `MsgTable(const ushort*)` (`__ct__8MsgTable`, `__nw`), i.e. the shop/solomon theme owns its message table in the retail build.
* Retail-only helpers in the same area (no JP counterpart): `Retail_solomon_Sub546860`, `Retail_FldTeamChange_Sub521140`, `Retail_worldMap_CheckKeyHelperA/B`.

## 2. CmdXxx menu classes (FIELD, 13 functions)

* `Close__9CmdAroma`, `Close__11CmdWolfBout`: JP is a 0x50-byte stub; US (0x190, 0x150) waits for the ring to finish (`JRing::IsRingClosing`, `JRing::RingClose(int)`) before reporting closed, so closing is a multi-frame state in retail (new Polling-style wait).
* `Exit__13CmdRingCustom`: JP (0x480) tears down the JRing itself (`Destruct`, `RingClose`, `ReleaseOT`); US (0x180) no longer owns that teardown (moved to the Close path above).
* `SafeDelayDelete__13CmdFriendship` and `__13CmdPhotograph`: US adds a call to `MenuScene::DelayDelete()` (the retail scene frame is a MenuScene with its own delayed delete).
* `Run__11CmdWolfBout` adds `MenuModelPack::SetAction`.
* `__ct__` of CmdTechnique, CmdSword, CmdFusion, CmdFormation, `Close__9CmdStatus`, `Close__13CmdPhotograph`: +0x10..0x40 bytes each for the extra retail fields initialised (vtable of the multiple-inheritance MenuScene part); no new behaviour found.
* Retail-only: `Retail_CmdEquipment_OpenPage05` (a sixth equipment page), `UpdateScene__16CmdFusionLevelup`, `UpdateName__16CmdFormationTeam` (0x460, the per-slot name refresh with the language-dependent text widths), `__ct__6P2Font`.

## 3. Main executable (29 functions)

* SaveDevice: `__ct__10SaveDevice` no longer calls `__ct__10SystemFile` but `__construct_array` (the device owns an array of slot records).  `GetInfo__12SaveDeviceMC` (memory-card info out-params) and `Retail_SaveData_CalcChecksum` have no JP bodies (the retail save format has a checksum pass; JP did not).  `Retail_BuildHDDPartitionKey` is the HDD partition key builder (retail HDD support, absent in JP).
* BtlBonus: `__ct__8BtlBonus` grows 0x160 -> 0xcc0.  New calls: `RegDatApi::GetRegDat(i,j,k)`, `sprintf`, `Retail_GetItemKindTable`, `Retail_FormatWideNumber`.  JP drew the post-battle bonus numbers directly; US formats them as text through a table-driven path.  This is the same area as phase 0x15 (Win) in `decomp/I/us_battle_phases.c`.
* BtlInBoss: `__ct__9BtlInBoss` is smaller (0x13d0 -> 0x1210) and swaps `FirstLight` creation for `BI_PolGrp` / `BI_Pol` polygon-group construction (`Create`, `AddPol`, `CalcCenter`, `CalcOffset`, `Matrix::ApplyMatrix`).  New classes `Retail_BtlInBossExModel`, `Retail_LightBuf` (see us_retail_classes.md).
* Fp (field-process) effects: `FpSun::Create` 0x380 -> 0xb70 (now builds the lens-flare chain with `FVector*`, `FVector(const FVector*)`); `FpObjectThunder::InitData` 0xd0 -> 0x480 (allocates a vertex array with `__nwa`/`__construct_new_array`, `CreateVertex`, `PutiObject::SetRegTest`; the lightning geometry is built as a vertex array (probably a polygon strip) instead of by `GetRad`/`sinf` per segment).
* Font/resource: `Font::CreateFont` 0x160 -> 0x260: palette is sorted/created through `ClutRaster::ClutSort` and `ClutRaster::Create` (replaces `FontDraw::CreateClut`).
* IO: `AnimServerHandler::Read` creates a `RingBuffer(ulong,uint)` per stream (`__nw`, `__nwa`); `LSDPlayer::StreamPolling` 0x40 -> 0x160; `LSDScrEx::SetBGMotion` no longer routes through CFieldBG/CFieldModel (`GetModel`, `SetMotion`, `SetLastMotion` dropped).
* Misc: `prim2D::calcPos` 0x4d0 -> 0x730 (extra scale/aspect cases for the retail screen), `dispCash::__dt` calls `ReleaseOT`, `HNMSnd::SetBGMParam` 0x80 -> 0x1b0 (per-channel param copy), `CPathControl::ClearPath` 0x10 -> 0x4d0 (JP was a memmove stub; US clears a per-path table), `FrameChange::__dt`, `__sinit_SSHmain.cpp` (more static ctors), plus `addTime__15SequenceControl`, `asmBlendNormal__10BlendShape`, `strncmp_261540` (library-side, no JP twin).
* Retail-only: `Retail_MsgTable_Format1/2` (message-table number formatting), `Retail_CGhostEfx_ReleaseLink`, `Retail_BtlInBossExModel_Ct/Dt`, `Retail_LightBuf_Ct/Dt`, `Retail_BtlInBoss_GetPacketWithMatrices`.

## 4. BATTLE overlay (13 functions)

* `EffectCheck__7CBattle`: JP 0x6780 bytes, US a 0xc0-byte wrapper that calls `Retail_CBattle_EffectCheckCore` (0x23c0).  The monolith was split; the core is still the per-effect hit/miss/damage-class check (EFCTCOMParam).  The rest of the former body moved into `GetTarget`.
* `GetTarget__7CBattle`: JP 0x4110 -> US 0x5b60 (538 -> 1587 decompile lines).  Adds `CheckGuard(int)`, `RegDatApi::GetRegDat`, `FVector::Length`, `Retail_CBattle_GetPAtkTable` (physical attack lookup), and calls `EffectCheckCore` directly.  This is the AI/auto target chooser (BtlChr AI script, `AIInit`, see us_battle_aiinit.c) and gains guard checks (the exact new modifiers were not decoded).
* `GetMoveTarget` shrinks 0x3d0 -> 0xa0 (no `rand`, no trap check): move-to-target position is chosen deterministically in retail.
* `GetComboTarget` 0x6e0 -> 0xce0, `CheckComboTarget` 0x510 -> 0x530 (uses `_vadd` / FVector copy): combo-chain target selection grows to handle the retail combo-ring rules.
* `DecSP__7CBattle` 0xbf0 -> 0x300: JP embedded the special-effect decoding (`SpecialEffectCode`); retail splits it, DecSP calls `DecSPp(int,int,int)` and `SpecialEffectCode` is a main-exe function (`SpecialEffectCode__FiiiP7ECParamP6EFFTBLP11BtlChrParam`, 0x369330).
* `MonsterSet__7CBattle` 0x180 -> 0x60: the per-slot copy loop became a `memcpy` of the MONSETTbl row.
* Retail-only (no JP body): `DeathInit__7CBattle` (0x5e0), `GetNextTurnChr2__7CBattle` (0xdc0), `TotalHitInfo::Reset`, `BMesWin::Polling` (0xb80), `Retail_CBattle_SetupStatusRecords` (0xd30; builds the per-character status record table, tied to the BtlSaveSec stat tables).

## Confidence
High for sections 1 and 4 (callee sets differ in a consistent, class-wide way).  Medium for section 3 (single-function inferences).  Where a function is marked "no JP body" the name is by behaviour only.
