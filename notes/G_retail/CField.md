# CField - retail (US) field controller

Ghidra: program `SH2US_FIELD.BIN` (load 0x0045ea80), class range **0x004f0630 - 0x00522000** (US) vs JP `SH2JP_FIELD.BIN` 0x004a2a30 - 0x004ded30.
Names below are the JP mangled names (applied in Ghidra); `Retail_*` marks functions that do not exist in the JP demo.
JP reference: `notes/G/CField.md`, `decomp/G/CField.c`. Cleaned retail C: `decomp/G_retail/CField.c`. Address map: `us_map.txt`.

## 1. What "rewritten" really means

Section G reported that the retail CField shares only 1 of 201 methods with the JP demo by opcode skeleton. Reading both decompilations side by side
shows that **the source is the same** and only the *code generation* differs:

* JP Furokuban/Taikenban FIELD.BIN is compiled with no register allocation: `this` and every local are spilled to the stack right after the prologue
  (`pCStack_20 = this;`), every `FVector` operator is a real call (`__as__7FVectorFRC7FVector`, `__mi__...`, `__ml__...`).
* Retail FIELD.BIN keeps `this` in a saved register and inlines the VU0 vector math (`lqc2/vsub/sqc2`), so functions are 10-25 % smaller (`size JP/US` column) and
  accessor-style functions (`GetPos`, `isDsp`, `GetRot`, ...) disappear.
* Function order is preserved, so the two overlays are ordered-aligned (DP over size/callee-identity/constant multiset/caller sets; anchors: the 8-byte chunk tag
  constants `ENTRYPOS`, `MONSET`, `CAMERA`, `EVENTBOX`, `NAVIMAP`, `SLICE`, vtables).
* Cross-check: the multiset of float constants of 435 aligned JP/US pairs is identical for all but ~17 functions (listed in section 5); chunk-tag use, switch case
  sets, camera kinds, collision constants (`1.2`, `0.8`, `4.0`, `0.91`, `0.11`) and event-box maths are the same.
  **Consequence: the JP-derived Rust modules (`floor`, `movement`, `event`, `camera`) are valid for retail**; only the deltas in section 5 need `Build::Retail`.

_Generated tables use the JP mangled names as canonical keys. conf: A = anchored by chunk-tag constant / vtable, H = ordered call-graph + constant alignment (score >= 0.55), M = ordered alignment (< 0.55, tiny functions whose callees were inlined), C = hand-corrected or exact match from section G._

## 2. Object layout (retail `CField`, size **0x2770**, JP 0x2330)

`operator new(0x2770)` in `CFieldSocket::WakeMapJump` (US 0x003f52a0); the ctor (0x004f06e0) zeroes `this+0x24 .. +0x12fc` (JP: 0x24 .. 0xebc) and sets state = 1.
Offsets were recovered by aligning the `this`-relative access sequences of every matched pair (LCS on access width/order, majority vote) and checked on the named fields:

| JP off | JP name | US off | notes |
|---|---|---|---|
| 0x14 | vtbl | 0x14 | US vtable at main-exe data 0x0043e460: `[0, 0, ~CField 0x4f0830, Polling 0x4f32d0, CScriptEx::OnStart 0x29b1c0, OnEnd 0x29b1d0, CallFunc 0x4f7fb0]` |
| 0x28 / 0x2a | state / entry_id | 0x28 / 0x2a | unchanged |
| 0x16c | se (CSe*, `new 8`) | 0x15c | |
| 0x170 | navimap (CNaviMap*) | 0x160 | |
| 0x174 | vib[4] | 0x164 | (by delta) |
| 0x184 | team_change (FldTeamChange*) | 0x174 | **created in `CField::Init`** (`new 0x88`, ctor 0x00520c40); the demo's CField range contains no `new FldTeamChange` |
| 0x18c - 0x193 | flag bytes, model_count, scr_camera_active | 0x178 - 0x18b | flags are re-packed, see section 3; `model_count` 0x192 -> **0x18a**, `scr_camera_active` 0x193 -> **0x18b** |
| 0x1ac | pad (CPad*) | 0x1a4 | |
| 0x1b0 / 0x1b4 | event_boxes / cam_events | 0x1a8 / 0x1ac | |
| 0x1b8 / 0x1bc | floor / camera | 0x1b0 / 0x1b4 | camera object is 0xf0 bytes (JP 0xd0) |
| 0x1c0 | models[0x30] | 0x1b8 | slot 0 = controlled character |
| 0x3c0 | bg (CFieldBG*) | 0x3b8 | |
| ~0x3fc .. 0x5b0 | (sound/BG/misc) | +0x300 bytes inserted | new 0x300 byte block (0x30 x 0x10) before the window table; delta afterwards +0x2f8..+0x304 |
| 0x5ec / 0x5f0 / 0x5f4 | clr_flag / effect list / light frame | 0x8e4 / 0x8ec / 0x8f0 | effect list head at +0x8ec is a linked list of nodes (`Retail_*` helpers 0x51e270/0x51e3a0) |
| 0x5fc / 0x600 | event-box index / event id | 0x8f8 / 0x8fc | |
| 0x60c + i*0x14 | window slots (8) | 0x910 + i*0x14 | `+0` FieldMessage*, +6 flags, +0xc/+0xd size, +8/+0xa pos |
| 0x6b0 | face[4] | 0x9b4 | |
| 0x6a4 | mces_state | 0x9a8 | states 0..0x12 in retail (`UpdateMCES`, `Retail` end helpers 0x4f2360/0x4f24c0) |
| 0x6c0 / 0x6c1 / 0x6c2 | cur window / cur face / cur name | 0x9c4 / 0x9c5 / 0x9c6 | |
| 0x6c8 | camera_id (s16) | 0x9e0 | |
| 0x6d8 / 0x6dc / 0x6e0 | follow stamp / stored stick heading / cam_yaw_adjust | 0x9f0 / 0x9f4 / 0x9f8 | `retail::CamFollow` |
| 0x6ea.. | latched pad/stick (`MakeMoveControl`) | 0xa04.. | |
| 0x73c | ObjSE slots (0x30) | 0xa58 | **stride 0x28 -> 0x2c** |
| 0xebc | (vibration seq buffers) | 0x12fc | `Retail_CField_ResetAll` clears `+0x12fc .. +0x210c` |
| 0x1cd0 | cam_pos | 0x2110 | |
| 0x1ce0 | cam_angle (`.y` = yaw deg) | 0x2120 | |
| 0x1cf0 | player_pos | 0x2130 | |
| 0x1d00 | BufMemory | 0x2140 | |
| 0x1d10 / 0x1d20 | GsxCamera pos / at | 0x2150 / 0x2160 | |
| (new) | camera FX state | 0x9cc .. 0x9dc | `Retail_CField_CamBlurFxCmd` (u16 phase / length / amplitude ...) |

## 3. Flag bytes (retail)

Only the bits confirmed by reading `Polling`, `Dsp`, `InitSDB`, `CameraUpdate`, `CallFunc` (see `sh2_field::retail::RetailFlags`):

| byte | meaning |
|---|---|
| +0x178 (JP 0x18c) | b0-1 delete / game-over on delete; b2-4 set to `0x1c` by `InitSDB` (JP `0x14`); **b5-7 camera follow mode** (1 init, 2 reset, 3 track, 4 ease out) |
| +0x179 (JP 0x18d, repacked) | b0 teardown (`Polling` step 1), **b1 displayed** (JP b4), b2 main menu requested (set on triangle and by op 0x4d), b4 set by `Init` |
| +0x17a | b3 freeze `player_pos`, b4 command menu created, b5 camera FX active (op 0x77), b6 location name set (op 0x2b) |
| +0x17c (JP 0x18e & 3) | player control mode 0 free, 1 scripted latch, 2 wait fader, 3 ready |
| +0x17d (JP 0x18d bits 2-3) | pause: 0 run, 1 hold input, 2 sleeping (only sound is polled) |
| +0x17e (JP 0x18d bits 0-1) | pending battle: 1 normal (`StartBtlIn`), 2 boss (`StartBtlInBoss`) |
| +0x186 | HUD/command state written by `Start` (3), `Dsp` (3), `InvokeCmdScene` (1) |
| +0x187 | countdown byte decremented each frame; at 0 `Retail_FieldDataCache_Tick` runs |
| +0x189 | sight trigger: index+1 of the monster that already noticed its target |

## 4. Lifecycle (retail)

Same shape as the demo (`notes/G/CField.md`): `CFieldSocket::fieldOverlay` -> `new CField(0x2770)` -> `Init(map)`:
`Init` (0x004f0ad0) = `iGpffff8544 (fld) = this; preLoad (0x4f0b60); Start (0x4f0ba0); MenuObj::CreateField; new FldTeamChange; MapJump(map)`.
`Start` creates `CPad(0)` (`new 0x18`), `CFieldCamera` (`new 0xf0`, ctor 0x5061c0 + `Init` 0x506250), registers the script object (`CScriptEx::Entry(0x88)`; JP 0x70).
`InitSDB` (0x004f7210) and `Polling` (0x004f32d0) follow the demo structure; the differences are listed next.

## 5. Differences against the JP demo

1. **Start position (`InitSDB`)** - after the common part (BG, MONSET, AutoLoadSE, SLICE, `ENTRYPOS[0]`) retail resolves
   `entry_id < -1 -> GetSavedChrPos(-(entry_id+2), &pos)` (save-block slot 0/1, US 0x3f7ca0) and otherwise `RestoreChrPos(0, &pos)` (battle-return slot, US 0x3f3860);
   `w = 1`. JP only does this for characters in `DispCharacter`. Ported as `retail::start_position` / `Field::init_sdb_ex`.
   `InitSDB` additionally calls the (inlined) `FldTimer::Mask(0)` on the global `FldTimer*` at 0x0043fe84 (JP `iGpffff8570`), writes 5 into a field of the global object at 0x0043fd28 (+0x1c, +0x58),
   and, while the MCES state (+0x9a8) is non-zero, sets the scene fader (slot 1) to mode 3 (mode 1 when +0x9aa bit 7 is clear) with 0 frames.
2. **Camera follow ease (`Polling`)** - state 4 uses a damping cap of **0.98** (JP 0.99), adds `if (-10 <= adj < 10) adj *= 0.92`, and the condition that keeps tracking
   (`(adj<0&&d<0)||(adj>0&&d>0)||(-10 <= x || x <= 10)`) is a **tautology** in the retail source, so modes 1-3 always fall into the ease-out mode 4. Ported as `retail::CamFollow`.
3. **Field monster sight** - `Polling` calls `Retail_CField_CheckNpcSight` (0x4fda20) every frame; script op 0x1b arms it. Needs the retail-only `GENERIC "TRILIST"` block
   (7 maps). See `retail::{TriList, sight_test}`.
4. **Camera FX** - `CameraUpdate` starts with `Retail_CField_StepCamBlurFx/EvalCamBlurFx`, which write two vectors into `CFieldCamera+0xd0/+0xe0` (position offset, pitch/roll offsets)
   and set the post-filter blur alpha (`CFieldSocket::SetBlurFilter`, `0x23 + 8*fx`). Controlled by script op 0x77. `CFieldCamera::Apply` adds them.
5. **Event boxes are walls** - `TransCallBack` (CFieldModel) calls `Retail_CField_CheckEventBoxSweep` -> `Retail_CFieldEvent_SweepHit` (0x507010, 0x610 bytes) for the controlled model
   when it enters an EVENTBOX it was not in last frame (`HitChkM2E`). Not ported (see open questions).
6. **`clipRadian`** loops (`while`) instead of two `if`s (US 0x4f0640 vs JP 0x4a2a50). `retail::clip_radian_for`.
7. **New script commands** in `CallFunc` (0x4f7fb0, 0x2680 bytes vs JP 0x3af0): 0x1b, 0x2b, 0x2f, 0x4c, 0x4d, 0x77 (`fld_ops::FLD_OPS_RETAIL_ONLY`). All other ids 0x00-0x7f exist in both builds.
8. **Menus**: `cbShop`/`cbTailor` (0x4faaf0/0x4fabf0) call retail `Dsp`/`Clr` variants (0x4f13d0/0x4f1460) and `CFieldModel::SuspendForMenu/ResumeAfterMenu/DspAfterMenu`
   (0x50ac70/0x50acf0/0x50aa80) which keep a copy of the model position at `CFieldModel+0x70`.
9. **Event classes** - `SetFieldEvent(class, id, kind, ...)` (US 0x4fc970): the demo passes class 1 for NPC talk / box examine / box enter-leave (2 for the default circle event, 0 for the timer alarm);
   retail passes **0x10** (box enter/leave), **0x11** (NPC talk), **0x12** (box examine), 1 (default circle event), 0 (timer) and only classes with the 0x10 bit are queued as delayed events (`AddDelayEvent`, 0x4fca70) while a 0xc2 script is running.
   The default circle-event table moved from `+0x3e8 + n*0x10` to `+0x3e0 + n*0x10` (`+0x3f0`-based index n-1). Boxes' enable bits in `flags178` bits 2-4 are all set by `InitSDB` (demo: bits 2 and 4).
10. **Smaller changes** (float-constant diff, all other pairs identical): `LoadFace` sets a default 96x96 face rectangle; `SetCharacterDir` uses +-pi/2 turn limits; `UpdatePathMove` adds a 0.9 / 20.0 / pi
   arrival rule; `CFieldModel::SetDir` ignores turns below 1 degree and stores the turn side in a 2-bit field (details in `CFieldModel.md`); `Pause` uses `+0x17d`;
   `FldTimer::Mask` is inlined (bit 3 of byte +0x61 of the `FldTimer*` at 0x0043fe84).
11. **Object sizes**: `CField` 0x2330 -> 0x2770, `CFieldModel` 0x2e0 -> 0x340, `CFieldCamera` 0xd0 -> 0xf0, `CFieldBG::Impl` 0x1d4 -> 0xc0, `CFieldSocket` 0x6c -> 0x74, `CMusic` 0x94 -> 0xac.

## 6. Method table

| JP addr | US addr | method (JP mangled name) | conf | size JP/US |
|---|---|---|---|---|
| `004a2b00` | `004f06e0` | `__ct__6CFieldFv` | H | 1f0/150 |
| `004a2db0` | `004f0830` | `__dt__6CFieldFv` | H | f0/120 |
| `004a2ef0` | `004f0950` | `CheckResetPause__6CFieldFv` | H | c0/90 |
| `004a2fb0` | `004f09e0` | `Delete__6CFieldFv` | H | 100/f0 |
| `004a30b0` | `004f0ad0` | `Init__6CFieldFPCc` | H | 80/90 |
| `004a3130` | `004f0b60` | `LinkA__6CFieldFv` | H | 30/40 |
| `004a3240` | `004f0ba0` | `Start__6CFieldFv` | H | 120/c0 |
| `004a3390` | `004f0c60` | `closeInquiry__6CFieldFv` | H | 30/20 |
| `004a33c0` | `004f0c80` | `Restart__6CFieldFv` | H | e0/80 |
| `004a34d0` | `004f0d00` | `PurgeModel__6CFieldFv` | H | a0/80 |
| `004a3570` | `004f0d80` | `SaveModel__6CFieldFv` | H | c0/a0 |
| `004a36a0` | `004f0e20` | `ClearSDB__6CFieldFi` | H | 260/1b0 |
| `004a3980` | `004f0fd0` | `GetBGModel__6CFieldFi` | C | 70/30 |
| `004a39f0` | `004f1000` | `GetCtrlModel__6CFieldFv` | C | 40/20 |
| `004a3a30` | `004f1020` | `CheckEventBox__6CFieldFR7FVector` | H | 70/60 |
| `004a3aa0` | `004f10c0` | `Pause__6CFieldFi` | C | e0/70 |
| `004a3bc0` | `004f1130` | `Dsp__6CFieldFv` | H | 1c0/170 |
| `004a3e20` | `004f12a0` | `Clr__6CFieldFv` | H | 170/130 |
| `004a41e0` | `004f17c0` | `SaveModelS__6CFieldFi` | H | 290/230 |
| `004a44e0` | `004f19f0` | `RestoreModel__6CFieldFii` | H | 350/290 |
| `004a4830` | `004f1c80` | `SaveField__6CFieldFv` | H | 140/110 |
| `004a4970` | `004f1df0` | `RestoreField__6CFieldFv` | H | 1f0/1e0 |
| `004a4b80` | `004f1fd0` | `PlayMCES__6CFieldFPCcii` | H | 180/1c0 |
| `004a4d40` | `004f2190` | `cbMCES__6CFieldFv` | H | 1a0/190 |
| `004a4ee0` | `004f2320` | `StartMCES__6CFieldFv` | H | 50/40 |
| `004a4f30` | `004f2430` | `SetMCESMode__6CFieldFPCcii` | H | b0/90 |
| `004a50c0` | `004f24c0` | `BreakMCES__6CFieldFi` | H | 150/140 |
| `004a5340` | `004f27b0` | `ResetMCES__6CFieldFi` | H | 130/150 |
| `004a54a0` | `004f2900` | `UpdateMCES__6CFieldFv` | H | 410/4e0 |
| `004a5990` | `004f2de0` | `FileReadOrder__6CFieldFiPCcPv` | H | 60/30 |
| `004a5ae0` | `004f2eb0` | `cbDataRead__6CFieldFiP9BufMemoryiPcPv` | H | 160/130 |
| `004a5c40` | `004f2fe0` | `ReleaseWindow__6CFieldFv` | H | 2e0/170 |
| `004a6260` | `004f32d0` | `Polling__6CFieldFv` | A | 1e40/1600 |
| `004a83f0` | `004f48d0` | `UpdateNavi__6CFieldFUii` | H | d0/80 |
| `004a84c0` | `004f4950` | `CameraUpdate__6CFieldFf` | H | 4f0/410 |
| `004a89f0` | `004f4d60` | `CheckMirror__6CFieldFv` | H | 130/100 |
| `004a8b20` | `004f4e60` | `ReverseVector__6CFieldFR7FVector` | H | c0/90 |
| `004a8be0` | `004f4ef0` | `UpdateFieldCamera__6CFieldFv` | A | 1a00/1590 |
| `004aa750` | `004f64b0` | `UpdateScrCamera__6CFieldFf` | H | 10b0/d60 |
| `004ab860` | `004f7210` | `InitSDB__6CFieldFP6CSTGDB` | A | 8a0/710 |
| `004ac100` | `004f7920` | `GetEntryPoint__6CFieldFiRi` | A | f0/c0 |
| `004ac1f0` | `004f79e0` | `AddLight__6CFieldFP5FrameUi` | H | 200/120 |
| `004ac3f0` | `004f7b00` | `UpdateLight__6CFieldFv` | H | 450/400 |
| `004ac870` | `004f7f00` | `AutoDelLight__6CFieldFv` | H | e0/b0 |
| `004ac950` | `004f7fb0` | `CallFunc__6CFieldFiiP9_ParStack` | A | 3af0/2680 |
| `004b06b0` | `004fa7d0` | `SpecialMenu__6CFieldFii` | H | 2a0/320 |
| `004b0a20` | `004faaf0` | `cbShop__6CFieldFiPv` | H | 120/100 |
| `004b0b40` | `004fabf0` | `cbTailor__6CFieldFiPv` | H | 110/100 |
| `004b0ce0` | `004fad40` | `SetRing__6CFieldFiiiiiPCc` | H | 200/1b0 |
| `004b0ee0` | `004faef0` | `RingControl__6CFieldFiiii` | H | 50/30 |
| `004b0f30` | `004faf20` | `cbRing__6CFieldFiPvPv` | H | d0/a0 |
| `004b1000` | `004fafc0` | `UpdateRing__6CFieldFv` | H | 530/420 |
| `004b1530` | `004fb3e0` | `RingResult__6CFieldFv` | H | 60/40 |
| `004b1b70` | `004fb8c0` | `SetFieldData__6CFieldFiii` | H | 860/8b0 |
| `004b24e0` | `004fc170` | `GetFieldData__6CFieldFiii` | H | 370/4c0 |
| `004b28b0` | `004fc630` | `MapJump__6CFieldFPCc` | H | 130/e0 |
| `004b29e0` | `004fc710` | `MapJumpA__6CFieldFPCci` | H | 130/140 |
| `004b2b90` | `004fc8b0` | `CharPathEvent__6CFieldFP11CFieldModelUii` | H | d0/c0 |
| `004b2c60` | `004fc970` | `SetFieldEvent__6CFieldFiUiiii` | H | 100/100 |
| `004b2d60` | `004fca70` | `AddDelayEvent__6CFieldFiUiiii` | C | 110/80 |
| `004b2e70` | `004fcaf0` | `UpdateDelayEvent__6CFieldFv` | H | f0/b0 |
| `004b2f60` | `004fcbb0` | `CallFieldEvent__6CFieldFiUiii` | H | c0/140 |
| `004b3020` | `004fccf0` | `LoadCharacter__6CFieldFiiUi` | H | 60/70 |
| `004b3080` | `004fcd60` | `LoadModelCB__6CFieldFP11CFieldModel` | H | 50/50 |
| `004b30d0` | `004fcdb0` | `LoadCharacter__6CFieldFiPCciUi` | H | 290/1e0 |
| `004b3360` | `004fcf90` | `UnloadCharacter__6CFieldFi` | H | 180/140 |
| `004b34e0` | `004fd0d0` | `DispCharacterEP__6CFieldFiiiiPCc` | H | 1c0/180 |
| `004b36a0` | `004fd250` | `DispCharacter__6CFieldFii7FVectoriiiPCc` | H | 400/320 |
| `004b3aa0` | `004fd570` | `ClrCharacter__6CFieldFii` | H | f0/c0 |
| `004b3b90` | `004fd630` | `WaitCharacterEx__6CFieldFii` | H | 180/120 |
| `004b3dd0` | `004fdc40` | `DetachModel__6CFieldFii` | H | 220/1c0 |
| `004b4130` | `004fdee0` | `CharAddItem__6CFieldFiiPCci` | H | 280/270 |
| `004b43b0` | `004fe150` | `CharRemoveItem__6CFieldFiPCc` | H | 160/140 |
| `004b4510` | `004fe290` | `SetMotion__6CFieldFiii` | H | 80/50 |
| `004b4590` | `004fe2e0` | `SetBGMotion__6CFieldFiPCcPCc` | H | 120/e0 |
| `004b46b0` | `004fe3c0` | `SetCharacterDir__6CFieldFiiii` | H | 520/420 |
| `004b4bd0` | `004fe7e0` | `GetCharacterInfo__6CFieldFii` | H | 220/1f0 |
| `004b4e20` | `004fe9d0` | `SetCharacterInfo__6CFieldFiii` | H | 1a0/190 |
| `004b5040` | `004feb60` | `CreateWindow__6CFieldFiiii` | H | a0/40 |
| `004b50e0` | `004feba0` | `RecreateWindow__6CFieldFPQ26CField8_WndInfo` | H | 140/d0 |
| `004b52a0` | `004fec70` | `SetWindowPos__6CFieldFii` | H | 70/20 |
| `004b5310` | `004fec90` | `SetWindowSize__6CFieldFii` | H | 60/20 |
| `004b5370` | `004fecb0` | `OpenWindow__6CFieldFii` | H | d0/b0 |
| `004b5440` | `004fed60` | `CloseWindow__6CFieldFii` | H | 80/40 |
| `004b54c0` | `004feda0` | `UpdateMsgState__6CFieldFv` | H | 120/e0 |
| `004b5600` | `004fee80` | `OpenMessage__6CFieldFPcii` | H | 110/c0 |
| `004b5710` | `004fef40` | `ClearMessage__6CFieldFv` | H | 70/40 |
| `004b5780` | `004fef80` | `KeyWait__6CFieldFv` | H | 100/b0 |
| `004b5880` | `004ff030` | `KeyWaitStat__6CFieldFv` | H | 100/b0 |
| `004b5980` | `004ff0e0` | `LoadFace__6CFieldFii` | H | d0/c0 |
| `004b5ac0` | `004ff1a0` | `ReleaseFace__6CFieldFi` | H | 80/50 |
| `004b5b40` | `004ff240` | `SetFacePos__6CFieldFii` | H | 80/90 |
| `004b5c00` | `004ff1f0` | `SetFaceSize__6CFieldFii` | C | 80/50 |
| `004b5c80` | `004ff2d0` | `OpenFace__6CFieldFii` | C | 70/40 |
| `004b5cf0` | `004ff310` | `CloseFace__6CFieldFii` | C | 70/40 |
| `004b5d60` | `004ff350` | `CreateName__6CFieldFiiii` | H | c0/70 |
| `004b5e20` | `004ff3c0` | `SetNamePos__6CFieldFii` | H | 90/50 |
| `004b5eb0` | `004ff410` | `OpenName__6CFieldFPcii` | H | 90/70 |
| `004b5f40` | `004ff480` | `CloseName__6CFieldFii` | C | 80/40 |
| `004b5fc0` | `004ff4c0` | `SelectInitItem__6CFieldFv` | C | b0/80 |
| `004b6070` | `004ff540` | `SelectAddItem__6CFieldFPCc` | H | 70/40 |
| `004b60e0` | `004ff5d0` | `SelectInit__6CFieldFi` | C | 90/90 |
| `004b6230` | `004ff660` | `Select__6CFieldFRi` | H | 270/180 |
| `004b6500` | `004ff800` | `LoadImage__6CFieldFPCci` | H | c0/a0 |
| `004b65c0` | `004ff8a0` | `DspImage__6CFieldFiiiii` | H | 80/40 |
| `004b6640` | `004ff8e0` | `ClrImage__6CFieldFiiib` | H | 90/60 |
| `004b66d0` | `004ff940` | `SetEncountRate__6CFieldFi` | H | 90/60 |
| `004b6760` | `004ff9a0` | `UpdateMoveDistance__6CFieldFfi` | H | 70/30 |
| `004b67d0` | `004ff9d0` | `TreasureControl__6CFieldFiii` | H | 250/1c0 |
| `004b6a20` | `004ffb90` | `DspIcon__6CFieldFii` | H | 60/40 |
| `004b6a80` | `004ffbd0` | `SetLookPoint__6CFieldFiPffUiii` | H | 1e0/150 |
| `004b6c60` | `004ffd20` | `ClrLookPoint__6CFieldFi` | H | e0/a0 |
| `004b6d40` | `004ffdc0` | `ChkLookPoint__6CFieldFi` | H | 200/180 |
| `004b6f40` | `004fff40` | `DetachLookPoint__6CFieldFi` | H | c0/90 |
| `004b7000` | `004fffd0` | `AttachLookPoint__6CFieldFi` | H | 110/d0 |
| `004b71f0` | `00500190` | `SetSavePoint__6CFieldFiPfi` | H | 360/250 |
| `004b7550` | `005003e0` | `UpdateSavePoint__6CFieldFv` | C | d0/60 |
| `004b7620` | `00500440` | `ClrSavePoint__6CFieldFi` | H | 150/100 |
| `004b7770` | `00500540` | `ChkSavePoint__6CFieldFv` | C | f0/90 |
| `004b78b0` | `005005d0` | `ShowSavePoint__6CFieldFi` | H | 110/90 |
| `004b7ac0` | `005006e0` | `SetWarpPoint__6CFieldFiPfii` | H | 2d0/210 |
| `004b7d90` | `005008f0` | `UpdateWarpPoint__6CFieldFv` | H | d0/c0 |
| `004b7e90` | `005009b0` | `ClrWarpPoint__6CFieldFi` | H | 130/e0 |
| `004b7fc0` | `00500ac0` | `WarpFade__6CFieldFii` | H | f0/c0 |
| `004b80b0` | `00500b80` | `ShowWarpPoint__6CFieldFi` | H | 120/90 |
| `004b81d0` | `00500c10` | `DoWarp__6CFieldFiiUiUi` | H | 3b0/2a0 |
| `004b8580` | `00500eb0` | `IsWarp__6CFieldFi` | H | 90/70 |
| `004b8670` | `00500f20` | `VibRelease__6CFieldFv` | H | a0/70 |
| `004b8710` | `00500f90` | `StartVib__6CFieldFiii` | H | 110/d0 |
| `004b8820` | `00501060` | `StartVib__6CFieldFiPCci` | H | 130/e0 |
| `004b8950` | `00501140` | `VibControl__6CFieldFiiii` | H | 260/1d0 |
| `004b8be0` | `00501310` | `isLoadBusy__6CFieldFv` | H | c0/a0 |
| `004b8cc0` | `005013b0` | `CheckEncount__6CFieldFv` | H | 520/460 |
| `004b91e0` | `00501810` | `ScriptSuspend__6CFieldFv` | H | 50/50 |
| `004b9230` | `00501860` | `InvokeBattle__6CFieldFiiiiii` | H | 300/240 |
| `004b9550` | `00501aa0` | `SetCamera__6CFieldFPfifi` | H | b0/80 |
| `004b9600` | `00501b20` | `SetCamera__6CFieldFPfiif` | H | b0/80 |
| `004b96b0` | `00501ba0` | `SetCamera__6CFieldFiPfPff` | H | b0/90 |
| `004b9760` | `00501c30` | `RestoreCamera__6CFieldFf` | C | 40/70 |
| `004b97a0` | `00502280` | `GetCamPath__6CFieldFiP7FVectorf` | H | 7b0/630 |
| `004bb1c0` | `005039c0` | `GetCamPathA__6CFieldFiP7FVectorf` | H | 5b0/430 |
| `004bb770` | `00503df0` | `GetCamPath2__6CFieldFP7FVectori7FVector` | H | 5b0/6c0 |
| `004bbd20` | `005044b0` | `ChkPathPoint__6CFieldF7FVectorP7FVectorPf` | H | 280/270 |
| `004bbfa0` | `00504720` | `GetPathPoint__6CFieldFfP7FVector` | H | a0/f0 |
| `004d56b0` | `00519360` | `OnLoadBGM__6CFieldFv` | H | 80/90 |
| `004d57c0` | `00519520` | `SetObjSE__6CFieldFiUiUiiP7FVector` | H | 1d0/180 |
| `004d5990` | `005196a0` | `SetObjSE__6CFieldFiPUli` | H | 580/490 |
| `004d5f10` | `00519b30` | `AutoLoadSE__6CFieldFv` | A | 1d0/1b0 |
| `004d7380` | `0051adf0` | `UpdateObjSE__6CFieldFv` | H | 600/5c0 |
| `004d7980` | `0051b3b0` | `CallSe__6CFieldFiiUi` | H | 4e0/420 |
| `004d7e60` | `0051b7d0` | `LoadBgm__6CFieldFPCc` | H | 210/1c0 |
| `004d8070` | `0051b990` | `LoadOrder__6CFieldFPCc` | H | b0/90 |
| `004d8120` | `0051ba20` | `CancelPlayOrder__6CFieldFv` | H | f0/a0 |
| `004d8210` | `0051bac0` | `PlayBgm__6CFieldFiUi` | H | 1e0/1e0 |
| `004d83f0` | `0051bca0` | `BgmFade__6CFieldFUiUi` | H | 80/60 |
| `004d8470` | `0051bd70` | `SetBgmVolume__6CFieldFi` | H | 30/10 |
| `004d84a0` | `0051bd80` | `WaitBgm__6CFieldFi` | H | a0/60 |
| `004d8540` | `0051bde0` | `SetBattleBgm__6CFieldFPCc` | H | 10/10 |
| `004d8550` | `0051be50` | `LoadSe__6CFieldFPCci` | H | 210/1c0 |
| `004d8760` | `0051c010` | `UnloadSeAll__6CFieldFv` | H | c0/e0 |
| `004d8820` | `0051c0f0` | `UnloadSeAll2__6CFieldFv` | H | 130/110 |
| `004d8950` | `0051c200` | `UnloadSeFromBank__6CFieldFi` | H | 110/c0 |
| `004d8a60` | `0051c2c0` | `UnloadSe__6CFieldFPCc` | H | 180/130 |
| `004d8be0` | `0051c530` | `MarkSE__6CFieldFv` | H | c0/60 |
| `004d8ca0` | `0051c590` | `ReleaseMarkSE__6CFieldFv` | H | 110/100 |
| `004d8db0` | `0051c690` | `PlaySe__6CFieldFUii` | H | 80/70 |
| `004d8e30` | `0051c700` | `PlaySeR__6CFieldFiUiii` | H | 170/130 |
| `004d8fa0` | `0051c830` | `SetSeVolume__6CFieldFi` | H | 10/10 |
| `004d8fb0` | `0051c840` | `StopSe__6CFieldFUi` | H | 60/40 |
| `004d9010` | `0051c880` | `WaitSe__6CFieldFUii` | H | 50/20 |
| `004d9060` | `0051c920` | `SetSoundData__6CFieldFiii` | H | 110/110 |
| `004d91b0` | `0051ca30` | `PlayStreamBgm__6CFieldFPCci` | H | d0/a0 |
| `004d9280` | `0051cad0` | `FadeStreamBgm__6CFieldFi` | H | 40/30 |
| `004d92c0` | `0051cb00` | `cbReadSoundFile__6CFieldFiP9BufMemoryiPv` | H | e0/b0 |
| `004d93e0` | `0051cbb0` | `cbMusicA__6CFieldFUcUi` | H | 1d0/180 |
| `004d95b0` | `0051cd30` | `ResetSE__6CFieldFv` | H | 70/60 |
| `004d96c0` | `0051cfa0` | `ClearBgmData__6CFieldFv` | H | 90/80 |
| `004d9750` | `0051d070` | `CmdBgmPlayReq__6CFieldFiUi` | H | 180/120 |
| `004d98d0` | `0051d230` | `CmdSeLoadSDH__6CFieldFi` | H | 2b0/290 |
| `004d9b80` | `0051d4c0` | `FindSE__6CFieldFPCc` | H | d0/90 |
| `004d9d10` | `0051d6b0` | `PollingSound__6CFieldFv` | H | 180/150 |
| `004d9e90` | `0051d930` | `SetEffParameter__6CFieldFPvPv` | H | 160/e0 |
| `004d9ff0` | `0051dd70` | `StartEffect__6CFieldFPCcUiPvPv` | H | 270/220 |
| `004da290` | `0051e1c0` | `OnLoadEffect__6CFieldFP9BufMemoryiPv` | H | 170/b0 |

Free functions of the same translation unit:

| JP addr | US addr | method (JP mangled name) | conf | size JP/US |
|---|---|---|---|---|
| `004a2a50` | `004f0640` | `clipRadian__FRf` | C | b0/a0 |
| `004a3f90` | `004f1500` | `FldInitLSDPlayer__Fv` | C | 150/120 |
| `004a4fe0` | `004f2600` | `FieldBreakMCES__Fv` | C | 40/40 |
| `004a5020` | `004f2640` | `FieldExitPauseMCES__Fv` | C | a0/80 |
| `004a5250` | `004f26c0` | `MCESInvokeBattle__Fv` | C | f0/f0 |
| `004a59f0` | `004f2e10` | `_toUpper__Fi` | C | 50/20 |
| `004a5a40` | `004f2e30` | `_stricmp__FPCcPCc` | C | a0/80 |
| `004a5f20` | `004f3150` | `MakeMoveControl__FRfRfP4CPad` | C | 1f0/180 |
| `004b0c50` | `004facf0` | `GetNumber__FRPCc` | C | 90/50 |
| `004b1590` | `004fb420` | `VectorOperation__FiP9_ParStack` | C | 5c0/4a0 |
| `004b3d40` | `004fdbe0` | `FindFrame__FP11CFieldModelPCc` | C | 90/60 |
| `004b4020` | `004fde00` | `CalcStandParent__FR7FVectorP11CFieldModelf` | C | 110/e0 |
| `004b64c0` | `004ff7e0` | `GetImgName__FPcPCc` | C | 40/20 |
| `004b7110` | `005000a0` | `CreateSavePoint__FP9_SavPointP5Model` | C | b0/80 |
| `004b79c0` | `00500660` | `CreateWarpPoint__FP9_WapPointi` | C | c0/80 |
| `004b9f50` | `005028b0` | `GetNearestPath__FPQ23SDB10tagFCAMERA7FVectorRi` | C | 1270/1110 |
| `004bf920` | `005079f0` | `EncodeChar__Fi` | C | b0/60 |
| `004bff50` | `00507f20` | `EncodeMotionName__FPCc` | C | 170/110 |
| `004c00c0` | `00508030` | `DecodeMotionName__FPcUi` | C | 1b0/190 |
| `004c0270` | `005081c0` | `GetMotionName__FUi` | C | 60/50 |
| `004c02d0` | `00508210` | `InitFieldModel__Fv` | M | 10/10 |
| `004c02e0` | `00508220` | `GetModelReadCt__Fv` | M | 10/10 |
| `004c0370` | `00508230` | `mdlReadMotionCB__FiP9BufMemoryiPcPv` | C | 70/10 |
| `004c4020` | `0050b290` | `InterPolPitch__Ffff` | C | 120/a0 |
| `004c4e10` | `0050bc90` | `GetSmoothVelocity__Ffffff` | C | 1a0/c0 |
| `004c6bf0` | `0050d280` | `ClipRadian__Ff` | C | 180/f0 |
| `004c6fa0` | `0050d6b0` | `GetRotAngle__Fi` | C | c0/80 |
| `004c7e40` | `0050e410` | `checkKind__FPCc` | C | d0/a0 |
| `004ca4f0` | `005106d0` | `GetRand__Fi` | C | 40/30 |
| `004ca530` | `00510700` | `CalcModelBBox__FP5ModelPf` | C | 2b0/210 |
| `004cdcc0` | `00513410` | `CnvY__FUi` | C | 1c0/140 |
| `004cde80` | `00513550` | `CnvModelGray__FP5Model` | C | 100/a0 |
| `004cf0f0` | `00514320` | `CreateFldBGEffect__FiPv` | M | b0/70 |
| `004d0560` | `005150d0` | `GetColVector__FP7FVectorUi` | C | 150/e0 |
| `004d36b0` | `00517640` | `HalfCol__FUi` | C | 40/20 |
| `004d5600` | `005192e0` | `GetBgmFileName__FPcPCc` | C | 40/20 |
| `004d5640` | `00519300` | `GetSeFileName__FPcPCc` | C | 40/20 |
| `004d5680` | `00519320` | `cbReadBGM__FiP9BufMemoryiPcPv` | H | 30/40 |
| `004d5730` | `005193f0` | `GetObjSeSize__FPQ23SDB9tagFOBJSE` | C | 90/40 |
| `004d60e0` | `00519ce0` | `Exp3DVolume__F7FVector7FVector7FVectorRiRii` | C | 500/3d0 |
| `004d65e0` | `0051a0b0` | `Calc3DPosition__FP7FVectorP7FVectorP6_ObjSE` | C | c70/c20 |
| `004d7250` | `0051acd0` | `Exp3DVolumeC__FR7FVectorR7FVectorR7FVectorf` | C | 130/120 |
| `004daec0` | `0051ec70` | `CheckMirrorNormal__FR7FVector` | C | f0/90 |

### JP methods without a US counterpart (inlined or merged in retail)
`SetTeamChgData` (JP 004a3160, 0x50), `preLoad` (JP 004a31e0, 0x60), `SetHalfVol` (JP 004a3dc0, 0x40), `GetModel` (JP 004a44b0, 0x30), `WaitCamera` (JP 004aa6e0, 0x30), `SetActiveFace` (JP 004b04b0, 0x30), `SetActiveName` (JP 004b04e0, 0x30), `SetActiveWindow` (JP 004b0510, 0x30), `LoadMotionCB` (JP 004b2b50, 0x40), `isPaused` (JP 004cc3e0, 0x30), `SetReverbMode` (JP 004d9170, 0x40), `cbMusic` (JP 004d93a0, 0x40), `AddQ` (JP 004d9620, 0xa0), `FindSoundReq` (JP 004d9c50, 0xc0), `OnEffectEnd` (JP 004da400, 0x40), `EffectControl` (JP 004da440, 0xe0), `RemoveEffect` (JP 004da520, 0x100)

## 7. Retail-only / unidentified functions in the CField range

| US addr | size | name | role |
|---|---|---|---|
| `004f0630` | 0x10 | `FUN_004f0630` | (unidentified helper) |
| `004f1080` | 0x40 | `Retail_CField_CheckEventBoxSweep` | wall test of the controlled model against EVENTBOX edges; calls `Retail_CFieldEvent_SweepHit` unless byte +0xa03 is set |
| `004f13d0` | 0x90 | `FUN_004f13d0` | shop/tailor re-entry: show every model + BG (`Dsp` variant used by `cbShop`/`cbTailor`) |
| `004f1460` | 0xa0 | `FUN_004f1460` | shop/tailor exit: hide every model + BG (`Clr` variant) and run `FUN_0051d800` |
| `004f1620` | 0xd0 | `FUN_004f1620` | (unidentified helper) |
| `004f1d90` | 0x60 | `Retail_CField_ResetAll` | full field reset: memset(+0x12fc, 0, 0xe10), `Clr`, `ReleaseWindow`, `ClearSDB(1)`, `PurgeModel` (used by `PlayMCES`/`cbMCES`) |
| `004f2360` | 0xd0 | `FUN_004f2360` | MCES end: leaves cut-scene state 8 (restores the HUD flag, unpauses sound, clears `SSHSys+0x3c` bits) |
| `004fa630` | 0xd0 | `Retail_CField_InvokeCmdScene` | script op 0x4d: build a command-menu scene object (`new 0x68`), install `Retail_CField_cbCmdScene`, mark the field menu-paused |
| `004fa700` | 0x10 | `Retail_CField_cbCmdScene` | (unidentified helper) |
| `004fa710` | 0xc0 | `Retail_CField_cbCmdScene` | callback of the above: 2 = unpause + `Pause(1)`, 1 = resume control, 3 = restore HUD |
| `004fc850` | 0x60 | `FUN_004fc850` | `cbLoadMotion` style event callback: `GsxCamera`-side notify unless ctrl mode == 1 |
| `004fcba0` | 0x10 | `FUN_004fcba0` | tiny stub called from `InitSDB` and `MapJumpA` |
| `004fd750` | 0xf0 | `Retail_SegSegIntersectXZ` | segment/segment intersection in the XZ plane (parameters t,u in [0,1]) |
| `004fd840` | 0xa0 | `Retail_TriSegIntersectXZ` | triangle outline vs segment (XZ), returns 1/2/3 = edge ab/bc/ca crossed |
| `004fd8e0` | 0x140 | `Retail_CField_SetNpcSight` | script op 0x1b: arm / disarm / query a field monster sight check (needs GENERIC "TRILIST") |
| `004fda20` | 0x1c0 | `Retail_CField_CheckNpcSight` | per-frame sight poll from `Polling`: first armed monster that sees its target raises `SetFieldEvent(4, event, 0, 1, packed arg)` |
| `004ff580` | 0x50 | `Retail_CField_SelectInit2` | script op 0x4c: selection window init with explicit parameters |
| `00500120` | 0x70 | `FUN_00500120` | script op 0x7e arg 0x1000: show a save point (`SavePoint::SetCheckModel/Show`) |
| `00500a90` | 0x30 | `FUN_00500a90` | script op 0x65: warp point state query (`(flags>>1)&1` of slot `*0xc + 0x84e`) |
| `00501ca0` | 0xc0 | `Retail_CField_CamBlurFxCmd` | script op 0x77: camera sway/blur FX parameters (+0x9cc..0x9dc) |
| `00501d60` | 0x290 | `Retail_CField_EvalCamBlurFx` | camera FX evaluation: writes the position offset / angle offset vectors consumed by `CFieldCamera::Apply` (+0xd0/+0xe0) and drives `SetBlurFilter(alpha)` |
| `00501ff0` | 0x290 | `Retail_CField_StepCamBlurFx` | camera FX stepping (time base 1/1000 s): advances the FX phase counters +0x9cc/+0x9d4/+0x9d6 |
| `00508240` | 0x90 | `FUN_00508240` | model read callback (decrements the model-read counter) |
| `005082d0` | 0xc0 | `FUN_005082d0` | motion read callback |
| `005135f0` | 0x10 | `FUN_005135f0` | (unidentified helper) |
| `00513600` | 0x10 | `FUN_00513600` | (unidentified helper) |
| `00519430` | 0xf0 | `FUN_00519430` | `CField::SetObjSE(index)` wrapper: finds OBJSE record `index` and calls `SetObjSE` |
| `0051bd00` | 0x70 | `FUN_0051bd00` | BGM state helper (used by `BgmFade`, `CallFunc`, `PollingSound`) |
| `0051bdf0` | 0x60 | `FUN_0051bdf0` | (unidentified helper) |
| `0051c3f0` | 0x140 | `FUN_0051c3f0` | (unidentified helper) |
| `0051c8a0` | 0x80 | `FUN_0051c8a0` | (unidentified helper) |
| `0051cd90` | 0x1d0 | `FUN_0051cd90` | teardown sound/effect release loop called from `Polling` step 1 |
| `0051cf60` | 0x40 | `FUN_0051cf60` | (unidentified helper) |
| `0051d020` | 0x50 | `FUN_0051d020` | (unidentified helper) |
| `0051d190` | 0xa0 | `FUN_0051d190` | (unidentified helper) |
| `0051d550` | 0x60 | `FUN_0051d550` | (unidentified helper) |
| `0051d5b0` | 0x100 | `FUN_0051d5b0` | `PollingSound` helper (request queue) |
| `0051d800` | 0x50 | `FUN_0051d800` | per-frame HUD/ObjSE tick called from `Polling` (`FUN_0051d800`) |
| `0051d850` | 0x60 | `FUN_0051d850` | (unidentified helper) |
| `0051d8b0` | 0x80 | `FUN_0051d8b0` | (unidentified helper) |
| `0051da10` | 0x60 | `FUN_0051da10` | (unidentified helper) |
| `0051da70` | 0x90 | `FUN_0051da70` | (unidentified helper) |
| `0051db00` | 0x10 | `FUN_0051db00` | (unidentified helper) |
| `0051db10` | 0xc0 | `FUN_0051db10` | (unidentified helper) |
| `0051dbd0` | 0x50 | `FUN_0051dbd0` | (unidentified helper) |
| `0051dc20` | 0x50 | `FUN_0051dc20` | (unidentified helper) |
| `0051dc70` | 0x100 | `FUN_0051dc70` | (unidentified helper) |
| `0051df90` | 0x1b0 | `FUN_0051df90` | (unidentified helper) |
| `0051e140` | 0x20 | `FUN_0051e140` | (unidentified helper) |
| `0051e160` | 0x30 | `FUN_0051e160` | script op 0x2f sub 0: forward to the effect object |
| `0051e190` | 0x30 | `FUN_0051e190` | script op 0x2f sub 1: forward to the effect object |
| `0051e270` | 0x130 | `FUN_0051e270` | effect list pruning (`RemoveEffect(NULL)`): frees finished entries of the list at +0x8ec |
| `0051e3a0` | 0x1c0 | `FUN_0051e3a0` | effect node release (recursive) |

## 8. Open questions
* Exact meaning of the `+0x300` byte block inserted before the window table (per-slot 16-byte records; `CField::SaveModel`/`RestoreModel` are the likely users).
* `Retail_CField_SetNpcSight` event argument layout `(min(dist/10, 0x7fff) << 16) | (cone << 8) | monster index` is taken from `CheckNpcSight`; the script side that consumes it is in the `.MSC` files (section E).
* `SweepHit` (0x507010) is a VU0-heavy slide-along-edge routine; the Rust port does not implement it.
* The remaining `FUN_` helpers in 0x51bd00 - 0x51e3a0 are the retail sound/effect request queue (JP `AddQ`/`FindSoundReq`/`EffectControl` merged into larger functions).
