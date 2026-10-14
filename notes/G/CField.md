# CField — the field controller (FIELD.BIN, JP 0x004a2b00 … 0x004da520, 201 methods, object size 0x2330)

`CField : CScriptEx` (CScriptEx = section E script object; CField is both the per-scene object *and* the host of the field
script command set). A single instance exists while a field map is active: global `sys__6CField` (JP 0x0040ad..), also
`CFieldSocket::fld`. Created by `CFieldSocket::fieldOverlay`/`WakeMapJump` as `new CField (0x2330)`, `CField::Init(mapName)`.

## Lifecycle

```
CFieldSocket::Polling()                      (main exe, ticks while SSHSys' current API)
  fieldOverlay(): Overlay::Load("FIELD.BIN") (state machine +0x54: 0 request,1 waiting,2 loaded -> FldMemory created, CField created)
  WakeMapJump(map)  ->  new CField; CField::Init(map)
CField::Init(map)    sys__6CField=this; preLoad(); Start(); MenuObj::CreateField(); MapJump(map)
  preLoad            player_pos=(0,0,0,1); InitFieldModel()
  Start              new CPad(0), priority table; new CFieldCamera + Init; CScriptEx::Entry(0x70)  (script object joins the poller)
  MapJump(map)       clear event magic, SaveScriptRegister(), CFieldSocket::LoadMPS(map)   (or WORLDMAP -> worldMap)
     -> socket loads <map>.MSC + <map>.MPS (CSTGDB)  ... when ready:
  CField::ClearSDB(0); CField::InitSDB(sdb); Restart(); CScript::StartScript()
  InitSDB(sdb)       (0x004ab860) builds everything from the MPS: CFieldBG::Create/Dsp, MONSET -> SetEncountRate + field data 6/7,
                     AutoLoadSE (OBJSE), CFloorMan::SetData (SLICE present), player start via ENTRYPOS[entry_id] (SetDir/SetPos),
                     CAMEVENT -> CFieldEvent(is_camera=1) (+ relocation of CAMERA blob offsets), EVENTBOX -> CFieldEvent(0),
                     NAVIMAP -> CNaviMap::SetData; then models Update(0); entry -> +0x28 state = 2
  Polling            per frame (see below)
  Pause(f)           bits 2-3 of +0x18d (1 = paused by script/menu), CPad priority switched
  Delete             flag +0x18c.0; ResetSE, UnloadCharacter(-1), ClearSDB, VibRelease, FldTeamChange::Delete; final teardown in Polling (waits for sound/music release)
  ~CField            ReleaseField(MenuObj); game-over (+0x18c.1) -> InvokeGameOver else StartBattle(SysBtlParam, current MPS name)
```

## Object layout (recovered; offsets are bytes)

| off | type | name | notes |
|---|---|---|---|
| 0x00..0x23 | CScriptEx base | | vtable at +0x14 (`__vt__6CField`) |
| 0x28 | u16 | state | 1 constructed, 2 after InitSDB (wState==1 means "wait for models to finish loading", then ->2), 3 = frozen (dt forced to 0) |
| 0x2a | s16 | entry_id | ENTRYPOS index the player enters at (from `CFieldSocket+0x48`) |
| 0x2c.. | u8[8][4] queue | sound request queue | `AddQ`/`PollingSound`: entries `{cmd, arg, u16}` read/write indices at +0x14c/+0x14d; cmd 2 = BGM play request, 3 = SE bank load (SDH) |
| 0x16c | CSe* | se | 8 voices/0x20 |
| 0x170 | CNaviMap* | navimap | mini-map (0x120 object) |
| 0x174 | CVibe*[4] | vib | pad vibration channels; sequence buffers at +0x1d30 + ch*0x180 |
| 0x184 | FldTeamChange* | team_change | party swap UI |
| 0x18c | u8 | flags_18c | b0 deleting, b1 game-over on delete, b5-7 camera-follow mode (1 init,2 reset,3 track,4 ease) |
| 0x18d | u8 | flags_18d | b0-1 battle pending (1 normal,2 boss), b2-3 pause state, b4 displayed, b5 menu requested |
| 0x18e | u8 | flags_18e | b0-1 player control mode (0 free,1 scripted input latch,2 wait fader,3 ready), b7 freeze player_pos |
| 0x18f..0x191 | u8 | flags | b3 of 0x18f: field data loaded (`LoadFieldData`), 0x191 b6: timer mask / b1: ObjSE update enable |
| 0x192 | u8 | model_count | number of CFieldModel slots in use (<= 0x30) |
| 0x193 | u8 | scr_camera_active | script-driven camera (UpdateScrCamera) |
| 0x1ac | CPad* | pad | |
| 0x1b0 | CFieldEvent* | event_boxes | EVENTBOX |
| 0x1b4 | CFieldEvent* | cam_events | CAMEVENT |
| 0x1b8 | CFloorMan* | floor | |
| 0x1bc | CFieldCamera* | camera | |
| 0x1c0 | CFieldModel*[0x30] | models | slot 0 = controlled character (`GetCtrlModel`) |
| 0x3c0 | CFieldBG* | bg | |
| 0x5ec/0x5f0/0x5f4 | | clr_flag / effect list head / light attach frame | |
| 0x5fc / 0x600 | int | current event-box index / its event id | |
| 0x6a4 | u8 | mces_state | MCES (movie-ish cut-scene event streams) |
| 0x6c8 | s16 | camera_id | active CAMEVENT camera |
| 0x6e0 | float | cam_yaw_adjust | |
| 0x6ea..0x704 | | latched pad/stick (`MakeMoveControl` results) | |
| 0x73c | 0x30 x 0x28 | ObjSE slots | first dword = -1 when free |
| 0x1cd0 | FVector | cam_pos | |
| 0x1ce0 | FVector | cam_angle | `.y` = yaw deg |
| 0x1cf0 | FVector | player_pos | |
| 0x1d00 | BufMemory | | |
| 0x1d10 / 0x1d20 | FVector | active GsxCamera pos / at (+.w = fov) | |

(Ghidra: struct `CField` in `SH2JP_FIELD.BIN` with these named fields; `this` typed on all 201 methods.)

## CField::Polling (JP 0x004a6260) — frame logic

1. **teardown** if `flags_18c.0`: pump `PollingSound`, release CSe / CMusic; when both released: `PurgeModel`, delete CPad, CFieldCamera, `ReleaseWindow`, `closeInquiry` (Dispose script object), `SetAutoDelete(true)`.
2. `flags_18c.1`: Delete. `flags_18d & 3`: pending battle -> `StartBtlIn/StartBtlInBoss`, `ClrFilter`, `Delete`, `SSHSys::StartBattle(btlParam 0x55f180)`, `SetChrPosSaveState(1)`.
3. Wait for `CFieldSocket::isStable` (fader done). Update MCES, sound. If paused (`(18d>>2)&3 == 2`): only ObjSE.
4. `dt = SSHSys::GetFrameDelta()/1000.0`; run `UpdateRing` (judgement ring), `UpdateDelayEvent`, `UpdateMsgState`; `CFieldBG::Update(dt)`; every model `Update(dt)` + navi-map icons.
5. Random encounter: `CheckEncount()` > 0 -> pick a MONSET entry by `rand()%100` over cumulative weights -> `ScriptSuspend()` -> `InvokeBattle(...)`.
6. Input: `MakeMoveControl(&speed,&angleDeg,pad)`; camera-relative heading adjust (follow modes 1..4 using `SysTool::GetTimer`), `CFieldModel::SetDir(rot,2,3)`, `PlayMoveMotion`, `ChkLookPoint`, `UpdateNavi`. `player_pos` = ctrl model world pos.
7. Pad **0x1000 (triangle)** -> main menu (`CFieldSocket::CheckCmdMenu` -> `CommandMenu(4,..)` -> `new CmdMenu`); **0x2000 (circle)** -> talk/action: nearest displayed NPC within 12 units and dot(dir)>=0.5 else EVENTBOX probe 6 units ahead -> `SetFieldEvent(1, id, 4, ...)` (trigger type 4 = "examine").
8. EVENTBOX enter/leave: `HitCheck(player_pos, mode 0)` vs previous box -> `SetFieldEvent(1,id,2|1,...)`; FldTimer alarm -> `SetFieldEvent(0,...)`.
9. `CameraUpdate(dt)` (CAMEVENT lookup, `UpdateFieldCamera`, `CFieldCamera::Apply`), capture the GsxCamera pose into +0x1d10/+0x1d20, `CheckMirror`, `UpdateLight`.

Pad bit meanings seen: 0x10/0x40 d-pad up/down (menus), 0x1000 triangle, 0x2000 circle (confirm), 0x4000 cross (cancel).

## Field script commands (CField::CallFunc, JP 0x004ac950, 0x3ae4 bytes)

`CallFunc(op, argc, _ParStack*)` is the entry point of the `fld*` command family of section E's VM: `switch(op)` with ~125 cases.
Handlers (only the calls visible per case; "(inline)" = small code in the switch):

| op | handler calls |
|---|---|
| 0x00 | `CField::GetCharacterInfo` |
| 0x01 | `CField::SetCharacterInfo` |
| 0x02 | (inline) |
| 0x03 | `CField::CharRemoveItem` |
| 0x04 | (inline) |
| 0x05 | (inline) |
| 0x07 | (inline) |
| 0x08 | `CField::LoadCharacter` |
| 0x09 | `CField::UnloadCharacter` |
| 0x0a | (inline) |
| 0x0b | (inline) |
| 0x0c | `CField::ClrCharacter` |
| 0x0d | `CFieldModel::SetMoveMotion` |
| 0x0e | (inline) |
| 0x0f | `CFieldModel::UnloadMotion` |
| 0x10 | `CField::SetMotion` |
| 0x11 | `EncodeMotionName`, `CField::SetMotion` |
| 0x12 | (inline) |
| 0x14 | `CField::GetBGModel`, `CFieldModel::CheckLastCmdComplete`, `CFieldModel::SetLastCmdEvent` |
| 0x15 | `CFieldModel::SetMotionSpeed` |
| 0x16 | (inline) |
| 0x17 | `CFieldModel::GetPos` |
| 0x18 | `CFieldModel::SetCmd` |
| 0x19 | `CSTGDB::Find`, `CSTGDB::GetDataNum`, `CSTGDB::GetDataAddr`, `CFieldModel::PathMove`, `CFieldModel::SetCmd` |
| 0x1a | `CField::WaitCharacterEx` |
| 0x1c | `CFieldModel::SetManual`, `CFieldModel::ChgCtrl` |
| 0x1d | `CField::GetModel` |
| 0x1e | `CField::GetEntryPoint`, `CField::GetModel` |
| 0x1f | `CField::GetModel`, `CFieldModel::ClrViewPoint` |
| 0x20 | `CField::MapJumpA` |
| 0x21 | (inline) |
| 0x22 | `CField::GetModel`, `CField::AddLight` |
| 0x23 | `CField::SetFieldData` |
| 0x24 | (inline) |
| 0x25 | `CField::SetBGMotion` |
| 0x26 | `CField::GetBGModel`, `CFieldModel::SearchFrame`, `Frame::getWorldPos` |
| 0x27 | `CField::GetEntryPoint` |
| 0x28 | `CFieldSocket::SetFader` |
| 0x29 | `CFieldSocket::SetFader` |
| 0x2a | `CField::GetBGModel`, `CFieldModel::isEmpty`, `CFieldModel::SetMotionSpeed` |
| 0x2c | `CField::LoadImage` |
| 0x2d | (inline) |
| 0x2e | (inline) |
| 0x30 | `MenuObj::IsReadyField`, `CField::CreateWindow` |
| 0x31 | `CField::SetActiveWindow` |
| 0x32 | `CField::SetWindowPos` |
| 0x33 | `CField::SetWindowSize` |
| 0x34 | `CField::OpenWindow` |
| 0x35 | `CField::CloseWindow` |
| 0x36 | `CField::OpenMessage` |
| 0x37 | `CField::ClearMessage` |
| 0x38 | `CField::KeyWait` |
| 0x39 | `MenuObj::IsReadyField`, `CField::CreateName` |
| 0x3a | `CField::SetActiveName` |
| 0x3b | `CField::SetNamePos` |
| 0x3c | `CField::OpenName` |
| 0x3d | `CField::CloseName` |
| 0x40 | `CField::LoadFace` |
| 0x41 | `CField::ReleaseFace` |
| 0x42 | `CField::SetActiveFace` |
| 0x43 | `CField::SetFacePos` |
| 0x44 | `CField::SetFaceSize` |
| 0x45 | `CField::OpenFace` |
| 0x46 | `CField::CloseFace` |
| 0x48 | `CField::Select`, `CField::SelectInit`, `CField::SelectInitItem`, `CField::SelectAddItem` |
| 0x49 | `CField::SelectInit`, `CField::SelectInitItem` |
| 0x4a | `CField::SelectAddItem` |
| 0x4b | `CField::Select` |
| 0x4e | `FldTimer::Create`, `FldTimer::SetPos`, `FldTimer::SetCount` |
| 0x4f | `FldTimer::GetCount`, `FldTimer::Clr`, `FldTimer::Dsp`, `FldTimer::Stop`, `FldTimer::Start` |
| 0x50 | `CField::LoadBgm` |
| 0x51 | `CField::PlayBgm` |
| 0x52 | `CField::BgmFade` |
| 0x53 | `CField::SetBgmVolume` |
| 0x54 | `CField::WaitBgm` |
| 0x55 | `CField::SetBattleBgm` |
| 0x56 | `CField::LoadSe` |
| 0x57 | `CField::UnloadSe` |
| 0x58 | `CField::PlaySe` |
| 0x59 | `CField::SetSeVolume` |
| 0x5a | `CField::StopSe` |
| 0x5b | `CField::WaitSe` |
| 0x5c | (inline) |
| 0x5d | `CField::SetSoundData` |
| 0x5e | `CField::PlayStreamBgm` |
| 0x5f | `CField::PlaySeR`, `CField::StopSe` |
| 0x60 | (inline) |
| 0x61 | (inline) |
| 0x62 | `CField::Pause`, `CScript::Pause`, `CField::StartMCES` |
| 0x63 | (inline) |
| 0x64 | `CField::RingResult` |
| 0x65 | `CField::ClrWarpPoint`, `CField::DoWarp`, `CFieldSocket::SetWarp`, `CField::WarpFade`, `CField::GetEntryPoint`, `CField::IsWarp` |
| 0x66 | (inline) |
| 0x67 | (inline) |
| 0x68 | `CharacterEquip` |
| 0x69 | `CField::StartVib` |
| 0x6a | `CField::StartVib` |
| 0x6b | `CField::VibControl` |
| 0x6c | `CField::VibControl` |
| 0x6d | `CField::VibControl` |
| 0x6e | `CField::VibControl` |
| 0x6f | `SSHSys::DiskChangeStat`, `SSHSys::DiskChangeRetry`, `CField::SetFieldEvent`, `SSHSys::DiskChange`, `VectorOperation` |
| 0x70 | `GetWorldMapInfo` |
| 0x71 | `SetChrPosSaveState`, `FieldCameraID`, `CField::ResetSE`, `CFieldSocket::WorldMapJump`, `CField::ScriptSuspend` |
| 0x72 | `CField::ScriptSuspend` |
| 0x73 | `FindDTCInfo`, `GetDTCData`, `CField::ScriptSuspend` |
| 0x74 | (inline) |
| 0x75 | (inline) |
| 0x76 | `CField::WaitCamera`, `CField::SetCamera` |
| 0x78 | `CField::RestoreCamera` |
| 0x79 | (inline) |
| 0x7a | (inline) |
| 0x7b | `CField::ClrLookPoint` |
| 0x7c | `CField::DspIcon` |
| 0x7d | `InventoryChange`, `BtlSaveSec::GetPCParam`, `BtlSaveSec::SetPCParam`, `BtlSaveSec::AddPCParam` |
| 0x7e | `CField::ClrSavePoint`, `CField::GetEntryPoint`, `CField::SetSavePoint` |
| 0x7f | `CField::SpecialMenu`, `CScript::Pause` |

(Ops 0x67 and 0x6f/0x7d contain nested switches on a sub-command; `InventoryChange` ops 0x00-0x08 under 0x66.)

## Other method groups (all in `decomp/G/CField.c`)

* **Characters** `LoadCharacter(slot,name,..)`, `UnloadCharacter`, `DispCharacter[EP]`, `ClrCharacter`, `WaitCharacterEx`, `DetachModel`, `CharAddItem/RemoveItem`, `SetMotion`, `SetBGMotion`, `SetCharacterDir/Info`, `GetCharacterInfo` — drive `CFieldModel` (the NPC/player actor, 111 methods).
* **Windows/messages** `CreateWindow/RecreateWindow/OpenWindow/CloseWindow/SetWindowPos/Size`, `OpenMessage/ClearMessage/KeyWait`, `LoadFace/OpenFace/CloseFace`, `CreateName/OpenName`, `Select*` — thin wrappers over `FieldMessage`/`FaceImage` objects.
* **Points** `SetSavePoint/UpdateSavePoint/ClrSavePoint/ChkSavePoint/ShowSavePoint`, `SetWarpPoint/UpdateWarpPoint/ClrWarpPoint/DoWarp/WarpFade/IsWarp`, `SetLookPoint/ChkLookPoint/Attach/DetachLookPoint` (head-turn targets).
* **Camera** `SetCamera(x3 overloads)`, `RestoreCamera`, `UpdateScrCamera`, `UpdateFieldCamera`, `GetCamPath/GetCamPathA/GetCamPath2/ChkPathPoint/GetPathPoint` (spline camera kinds 4/5).
* **Audio** `LoadBgm/PlayBgm/BgmFade/WaitBgm/SetBgmVolume/PlayStreamBgm/LoadSe/UnloadSe*/PlaySe/PlaySeR/StopSe/SetObjSE/UpdateObjSE/AutoLoadSE/SetReverbMode/SetSoundData/...` (all CSe/CMusic/Sdrv glue).
* **Battle/encounter** `CheckEncount`, `UpdateMoveDistance`, `SetEncountRate`, `InvokeBattle`.
* **Ring** `SetRing/RingControl/UpdateRing/RingResult/cbRing` — judgement-ring minigames inside field events.
* **Effects** `StartEffect/EffectControl/RemoveEffect/SetEffParameter/OnLoadEffect` (.EFD files via `FileReadOrder`).
* **Save/restore** `SaveModel/SaveModelS/RestoreModel/SaveField/RestoreField` (field state kept across menu/battle trips).
* **Treasure** `TreasureControl`, `DspIcon`; **vibration** `StartVib` (two overloads: GENERIC "VIBRATION" block or raw .SEQ), `VibControl`, `VibRelease`.
* **Data** `SetFieldData/GetFieldData` (per-map scratch values: 6/7 = battle bg/bgm from MONSET).

## US retail delta

The retail FIELD.BIN rewrites this whole class (opcode-skeleton similarity of every CField method vs the JP demo is below 0.3; 1/201
methods matched). MPS container and chunk set are unchanged (+MIRROR, +BGCOLOR chunks). See `us_port.md`.
