# Retail-new menu / LSD / battle-result classes recovered in pass N5 (outside the Fp family)

All were found by vtable stores (`vtscan.py`, `clsgrp.py`, `fieldblock.py` in tools/I_N5), ctor/dtor pairing and the caller graph; names carry a `Retail` marker.  Confidence per row: `cert` = vtable role + ctor chain, `struct` = structural guess (role of the class inferred from callees only).

## Main executable (SLUS_210.41)

| class | base / shape | functions | evidence | purpose |
|---|---|---|---|---|
| `LSDRetailFilterHandler` | `LSDDeviceHandler` (vt 0x439200 at +0x10; global 0x457c10 constructed by `__sinit_LSDRetailFilter.cpp` 0x437820) | ctor 0x291200, dtor 0x291250, CheckData 0x2912d0, Open 0x291310, Read 0x291460, Close 0x292180, Event 0x291700 | cert (vtable order = CheckData/Open/Read/Close/Event/dtor, same as `LSDCaptionHandler`) | retail-new LSD track handler that drives a `SmoothFilter` layer (`LayerSetUp/FilterLevel`), `FontDraw` and `MenuWindow` objects; Open allocates a 0x3d8-byte handle (`LSDRetailFilterHandle`, ctor 0x2922c0, dtor 0x2923a0) |
| `LSDRetailFilterLayer` | `MenuObj` (vt 0x4391c0) | ctor 0x2924d0, dtor 0x292550 | cert | group object created by Event |
| `LSDRetailFilterWindow` | `MenuWindowObject` (vt 0x439220) | ctor 0x2926f0, dtor 0x292790, Create 0x292860, SetAlpha 0x2929a0, Update 0x292a30, Connect 0x292ea0, Destroy 0x292f40, Clear 0x292fe0 | cert | window of the filter handler; 0x292620 (calls `BtlSaveSec::GetYoahism`) belongs to the same cluster |
| `MenuCmdFieldData` | `MenuFieldData` (vt 0x439180) | ctor 0x291080, dtor 0x2910d0, GetReady 0x291150 | cert (`MenuObj::CreateCmdMenu` allocates 0x64 bytes instead of JP 0x5c) | field data holder of the in-game command menu (+0x60 = menu data entry) |
| `GameOverRetailMenu` | `MenuScene` (vt 0x439260) | ctor 0x293090 (called by `GameOverScene::GameOverScene`), dtor 0x293210, GetReady 0x2932e0 (4 rows x {2 MenuSprite + MenuText}), Release 0x293590, ClearItem 0x293650, SetItem 0x2937c0, OpenAt 0x293a30, row ctor/dtor 0x2931c0/0x293130 | cert for ctor/dtor/GetReady/Release, struct for the three `ReadData` helpers | the continue / load / title command list of the retail game-over screen |
| `MenuRetailPauseDialog` | `MenuScene` family (7 member objects; 0x308 bytes) | ctor 0x293c20, dtor 0x293cf0, DelayDelete 0x293e20, Run 0x293e60 | struct | confirmation dialog created by `MenuObj::PauseEvent` (0x2723a0): CPause event -5 -> `DisableReset`, `SetCallBack(0x2724c0)`, `EnablePause`, `CApp::Pause` (soft reset / return-to-title prompt) |
| `BtlResultRetailFxA` / `FxB` | `CPolObj` + `VIF1Prim` singletons (vt 0x43b210 / 0x43b1d0, secondary +0x28/+0x34) | ct, dt, Release (ReleaseOT+Dispose), Polling (timer + random +-8 jitter), getPacket (0xcd0 / 0x970 bytes, `JRCTex::GetTex0`), SetStrength, `@20@getPacket` | cert for the shape, struct for the purpose | two victory-screen packet effects (instances stored at gp-0x7c80 / gp-0x7c7c), twins of each other |
| `MenuSound` additions | existing class | `FindSDH` 0x28d5b0, `ReleaseSDH` 0x28e330, `PlaySE` 0x28e390, `StopSE` 0x28e410 (retail reorders the class: Polling sits before ReadSDH) and retail-new motion-linked SE table (`FindMotionSE` 0x28d6b0, `AddMotionSERef` 0x28e4a0, trampoline 0x28d360) | cert (bodies compared with JP) | |
| `MenuScene` retail vtable | existing class | slots 6/7/8 are three new virtuals (`Func6` 0x279010, `Func7` 0x279020 empty, `Update` 0x279030 returns 1); `DelayDelete__9MenuScene` 0x278eb0 is a MenuScene-specific override | cert | vtable now has 11 slots; `Shutdown/Restore` moved to 9/10 |

## FIELD.BIN overlay (SH2US_FIELD.BIN): retail-new Cmd pages 0x4dcc00-0x4ed400 (158 functions, 26 classes)

Pattern: each new page of the in-game menu is a `CmdWindow` family (`CmdRetailWinNN`: three vtables at +8/+0x18/+0x24, `@24@/@36@__dt` thunks, methods `CreateScene`, `UpdateScene`), a `Menu`-derived selector (`CmdRetailSelNN`, vtables at +0x14/+0x20) and a `CmdPrivateScene`-derived page (`CmdRetailPageNN`: MenuScene vtable with GetReady/Run/SafeDelayDelete/Close/ReadyScene/DisposeScene/BackGroundRun).  They hang off `CmdPrivate` / `CmdTop` (subpages added by the retail game); their message ids are MSD ids so the visible page names could not be recovered.  Numbers are address order.

| class | kind | ctor | members |
|---|---|---|---|
| `CmdRetailWin01` | window | 0x4dcd70 | 0x4dcd70 , 0x4dce90 , 0x4dd040 CreateScene, 0x4dd330 UpdateScene |
| `CmdRetailSel01` | selector | 0x4dd520 | 0x4dd520 , 0x4dd570 , 0x4dd600 Sub4dd600, 0x4dd950 Sub4dd950, 0x4dd9d0 Sub4dd9d0, 0x4dda40 Sub4dda40 |
| `CmdRetailPage01` | page | 0x4ddad0 | 0x4ddad0 , 0x4ddc10 , 0x4ddd80 GetReady, 0x4de370 Sub4de370, 0x4de5f0 Sub4de5f0, 0x4de6e0 Sub4de6e0, 0x4de840 Sub4de840, 0x4de910 Sub4de910, 0x4de970 Run, 0x4dea50 Sub4dea50, 0x4ded70 Sub4ded70, 0x4def40 Sub4def40, 0x4df450 Sub4df450, 0x4df950 Sub4df950 |
| `CmdRetailWin02` | window | 0x4dfa20 | 0x4dfa20 , 0x4dfb30 , 0x4dfc80 CreateScene, 0x4dfeb0 UpdateScene |
| `CmdRetailWin03` | window | 0x4e0190 | 0x4e0190 , 0x4e0220 , 0x4e02f0 CreateScene, 0x4e0470 UpdateScene |
| `CmdRetailPage02` | page | 0x4e06b0 | 0x4e06b0 , 0x4e0740 , 0x4e07d0 Sub4e07d0, 0x4e0880 GetReady, 0x4e0ab0 Sub4e0ab0, 0x4e0b70 Sub4e0b70, 0x4e0be0 Run, 0x4e0c40 Sub4e0c40, 0x4e0cf0 Sub4e0cf0, 0x4e0f80 Sub4e0f80, 0x4e10a0 Sub4e10a0, 0x4e12d0 Sub4e12d0, 0x4e1560 Sub4e1560, 0x4e1710 Sub4e1710 |
| `CmdRetailWin04` | window | 0x4e18d0 | 0x4e18d0 , 0x4e19d0 , 0x4e1af0 CreateScene |
| `CmdRetailWin05` | window | 0x4e1f30 | 0x4e1f30 , 0x4e2030 CreateScene, 0x4e2160 UpdateScene, 0x4e2240 , 0x4e2380 Sub4e2380, 0x4e3490 Sub4e3490 |
| `CmdRetailSel02` | selector | 0x4e36c0 | 0x4e36c0 , 0x4e3710 , 0x4e37a0 Sub4e37a0, 0x4e39d0 Sub4e39d0, 0x4e3a60 Sub4e3a60, 0x4e3ab0 Sub4e3ab0 |
| `CmdRetailPage03` | page | 0x4e3b10 | 0x4e3b10 , 0x4e3b80 , 0x4e3c00 GetReady, 0x4e3d60 Sub4e3d60, 0x4e3d80 Run, 0x4e3de0 Sub4e3de0, 0x4e3eb0 Sub4e3eb0, 0x4e4150 Sub4e4150 |
| `CmdRetailWin06` | window | 0x4e4240 | 0x4e4240 , 0x4e4300 , 0x4e4430 CreateScene |
| `CmdRetailWin07` | window | 0x4e4830 | 0x4e4830 , 0x4e48c0 , 0x4e4990 CreateScene, 0x4e4aa0 UpdateScene |
| `CmdRetailPage04` | page | 0x4e4ce0 | 0x4e4ce0 , 0x4e4d80 , 0x4e4e70 Sub4e4e70, 0x4e4ed0 GetReady, 0x4e5580 Sub4e5580, 0x4e5640 Sub4e5640 |
| `CmdRetailPlace01` | place | 0x4e57b0 | 0x4e57b0 , 0x4e5850 , 0x4e5920 Sub4e5920, 0x4e6220 Sub4e6220, 0x4e64f0 Sub4e64f0, 0x4e6ae0 Sub4e6ae0, 0x4e6c10 Sub4e6c10, 0x4e6c90 Sub4e6c90, 0x4e6d00 Sub4e6d00 |
| `CmdRetailWin08` | window | 0x4e6d30 | 0x4e6d30 , 0x4e6e40 , 0x4e6fa0 CreateScene |
| `CmdRetailPage05` | page | 0x4e7500 | 0x4e7500 , 0x4e75d0 , 0x4e76f0 Sub4e76f0, 0x4e7770 GetReady, 0x4e78e0 Run, 0x4e7bb0 Sub4e7bb0 |
| `CmdRetailWin09` | window | 0x4e8010 | 0x4e8010 , 0x4e80b0 CreateScene, 0x4e81e0 UpdateScene, 0x4e82b0 , 0x4e8380 Sub4e8380 |
| `CmdRetailWin10` | window | 0x4e8b10 | 0x4e8b10 , 0x4e8bd0 , 0x4e8cc0 CreateScene |
| `CmdRetailWin11` | window | 0x4e8fc0 | 0x4e8fc0 , 0x4e9090 , 0x4e91a0 CreateScene, 0x4e9200 UpdateScene, 0x4e95a0 Sub4e95a0, 0x4e9640 Sub4e9640, 0x4e96d0 Sub4e96d0, 0x4e9770 Sub4e9770 |
| `CmdRetailPage06` | page | 0x4e9870 | 0x4e9870 , 0x4e98f0 , 0x4e9980 Sub4e9980, 0x4e99c0 GetReady, 0x4e9aa0 Run, 0x4e9b00 Sub4e9b00, 0x4e9e10 Sub4e9e10, 0x4e9ee0 Sub4e9ee0 |
| `CmdRetailWin12` | window | 0x4ea0f0 | 0x4ea0f0 , 0x4ea180 , 0x4ea250 CreateScene, 0x4ea340 UpdateScene |
| `CmdRetailWin13` | window | 0x4ea430 | 0x4ea430 , 0x4ea4f0 , 0x4ea5e0 CreateScene |
| `CmdRetailWin14` | window | 0x4ea880 | 0x4ea880 , 0x4eaa00 CreateScene, 0x4eaa80 UpdateScene, 0x4eaac0 , 0x4eac60 Sub4eac60, 0x4eb3f0 Sub4eb3f0, 0x4eb480 Sub4eb480, 0x4eb4f0 Sub4eb4f0, 0x4eb7f0 Sub4eb7f0, 0x4eb890 Sub4eb890, 0x4ebf90 Sub4ebf90, 0x4ec190 Sub4ec190, 0x4ec410 Sub4ec410, 0x4ec690 Sub4ec690, 0x4ec720 Sub4ec720 |
| `CmdRetailWin15` | window | 0x4ec7b0 | 0x4ec7b0 , 0x4ec840 , 0x4ec910 CreateScene |
| `CmdRetailWin16` | window | 0x4eca70 | 0x4eca70 , 0x4ecb00 , 0x4ecbd0 CreateScene |
| `CmdRetailPage07` | page | 0x4ecdb0 | 0x4ecdb0 , 0x4ece00 , 0x4ece90 GetReady, 0x4ed130 Sub4ed130, 0x4ed1e0 Sub4ed1e0, 0x4ed2e0 Sub4ed2e0 |

The `@24@__dt`/`@36@__dt` thunks of the 16 window classes (32 functions) and a further 336 this-adjust thunks of existing FIELD/BATTLE/main classes (384 in total with the Fp ones) were undefined in Ghidra; they were created from the matched JP vtables (`vtthunks.py`).

## Pass N6 additions (named at the end of section I; all three images now have 0 unnamed functions)

Sizes are lower bounds from the constructor (highest offset written); "cert" = shape/callee evidence, "struct" = structure and use only.  Address lists: `us_map_N6.txt` and Ghidra.  Cleaned C for the BATTLE classes: `decomp/I/us_battle_tarot.c`.

| class | base / vtables | members (addr) | evidence | purpose |
|---|---|---|---|---|
| `BtlTarotSelect` (BATTLE) | BtlEff-style `CPolObj`; Polling object | ct 0x5718b0, dt 0x5725b0, Destruct 0x572780, Polling 0x572850, MakePacket 0x576820, EndSet 0x57da00 | struct (ctor/Polling shape, packet builder; called from `CBattle::Polling` phase 0x0d) | tarot card pick screen: the fan of cards, cursor, card name/description windows; result goes to `CBattle` +0x407c/+0x407e/+0x4080 |
| `BtlTarotEffect` (BATTLE) | `BtlEff`; vtables 0x43e820 (+0x14), 0x43e830 (+0x28), 0x43e840 (+0x34); ctor calls `__ct__6BtlEffFii` | ct 0x57a510, dt 0x57acf0, Destruct 0x57ae50, Polling 0x57af20, MakePacket 0x57b2d0 (created: it was a vtable slot target, not a Ghidra function), EndSet 0x57d9f0 | struct | the card activation effect (flip, glow, particles), then calls `CBattle::TarotApplyCard` (0x6a0c30) |
| `CBattle::TarotApplyCard / TarotRevertCard` | existing class | 0x6a0c30 (0x41b0 bytes), 0x69e160 (0x2ad0) | struct (switch on card id; party stat and flag edits; Revert undoes at battle end) | apply/undo the tarot effect (retail-new battle mechanic); `TarotEffectFunc__7CBattle` 0x48fe30 is the phase driver |
| Berserk antics phases | `CBattle::Polling` phases 0x0f-0x12 | `Retail_CBattle_Phase0F_BerserkApproachAlly` 0x493450, `Phase10_BerserkFindItem` 0x493ed0, `Phase11_BerserkTalk` 0x494a00, `Phase12_BerserkPose` 0x4952d0 | struct (nStep machines; phase 0x12 ends by setting nPhase 0x14, nCmdKind 1) | the retail Berserk status acts out a short scene: walk to an ally, rummage for an item, talk, pose; then the turn proceeds |
| other phases | `CBattle::Polling` | `Phase0B_RingSkill` 0x48c0d0, `Phase15_Win` 0x4958d0, `Phase16_Lose` 0x499b40, `CloseBattleUI` 0x49ccd0 | struct | ring-skill phase, victory and defeat sequences |
| AIInit family | `CBattle` | `BtlChrSequence` 0x6abaf0 (switch on chr bState, 0x1ac40 bytes), out-of-line cases `State0E0F` 0x6c6730, `State31..34` 0x6ce010/0x6ce300/0x6ce770/0x6ceb10, `AddFriendship` 0x6ceeb0, `AIInit` 0x6cf020 | cert for AIInit (tiny, clear) | AIInit is one function, not a family of variants: `pAiCursor = pAiScript + 4`, AI registers (`aAiReg`, shorts at +0xfe..+0x10a) and `wTurnCount` zeroed.  The "family" is the sequencer state handlers that follow it in the image. |
| `primSpriteEx` (main) | `primPacket`; vtable 0x43b700 at +8; size >= 0x330 | ct 0x3db270 (arg: bool -> +0x32), mSetStaticPacket 0x3db330, getPacket 0x3db9c0, calcPos 0x3dbef0, SetPosW (`Retail_primSpriteEx_SetPosW`) 0x3dc5e0, dt 0x3de640 | struct | extended 2D sprite: 0x120-0x2e0 vertex block, colour init 0x7f, default size 1792x1824 (0x44e00000, 0x44e40000) |
| `CDiscCheck` (main) | `CPolObj`; vtable 0x43bd40; size 0x2c | ct 0x407380, dt 0x4073d0, Entry 0x407430, Dispose 0x407470, Delete 0x4074b0, Start(uchar) 0x407520, isReady 0x407530, ReadCB 0x407540, Polling 0x4075a0 | cert (CPolObj lifecycle, one async read callback) | retail disc check: reads from the disc and reports ready |
| `MenuElementIcons` (FIELD) | none (plain aggregate); vtable-like 0x43c410 at +8 | ct 0x478390, dt 0x4784a0 | struct | array of 0x20 x 0x60-byte entries (`__construct_array`), then a `MenuSprite` at +0xc0c and a `SendOnLocal` at +0xc6c; size >= 0xc70 |
| `worldMapPanel` (FIELD) | `CPolObj` + `Font` (+0x24); vtables 0x43e790 (+0x14), 0x43e7a0 (+0x20); size ~0x54 | ct 0x553ad0, dt 0x553ba0, initialize 0x553da0, Polling 0x553ef0, mSetupMainWin 0x5553c0, mSetupSubWin 0x555900, mSetupMsgTable 0x556000, mPlugLSD 0x556110, mUnplugLSD 0x5562c0, mSelectDestination 0x5563d0, mSetupScrollMarks 0x5569d0 | struct (names follow the `worldMap` sibling methods) | retail world-map destination panel (list of destinations with scroll marks, loaded from a LSD) |
| `worldMapObjA` / `worldMapObjB` | small objects owned by worldMap | `Retail_worldMapObjA_Ct/Dt` 0x556ae0/0x556b30, `Retail_worldMapObjB_Ct/Dt` 0x55f6b0/0x55f700 | struct | helper nodes |
| `CBGSwarm` (main) | CPolObj-style | Dt 0x414410, AddOT 0x4144e0, ReleaseOT 0x414570, Update 0x414600, CreateModels 0x414ce0, InitModel 0x414ec0 | struct | background swarm effect (many small models updated per frame) |
| `MenuModel` (main) | existing | 58 functions 0x27e9e0-... : ct/dt, Create, Order, CalcMatrix, Alpha/Angle/SingleColor setters, TranseCallBack | cert for those matched to JP, struct for `Retail_MenuModel_*` | menu 3D model wrapper; the FIELD overlay adds `MenuModelAura`, `MenuModelAuraPacket`, `MenuModelAuraRegister` (0x4d4df0-0x4d63a0) |
| main dataAccess / SaveMenuSection / BtlSaveSec | existing | `dataAccess` 0x3d37d0-: save/load screen (mSetupSelectDevice, mSetupQuit, mSetupProgress*, mSetupWarning*); `SaveMenuSection` 0x286c50-: retail-new members (UpdateHDDInstall, ResetPadAssign, RaiseCash, InitPartySets); `BtlSaveSec` 0x3bb940-: ct, SetDefault, mode setters (Yoahism, SoulSystem, RetailModeBit1, ComboMenu), AddEquip, MergeItemCounts and the clear-data carry-over | cert for the JP-matched ones, struct for `Retail_*` | save/load UI, HDD install option, New Game+ carry-over, and the stat tables |
