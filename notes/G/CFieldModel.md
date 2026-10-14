# CFieldModel — actor/NPC/BG model wrapper (JP 0x004a3630 … 0x004dae40, 111 methods; `DelayDeleteObject` base, vtable at +8)

One instance per `CField` model slot (slot 0 = controlled character) and per BG model (`CFieldBG`, 0x2e0 bytes each). Wraps a section-C `Model`
(skinned, motion-driven) and adds: placement, motion chaining, move commands (manual / auto-move / path-move), floor snapping, model-to-model
collision, blink/talk/lip handling, shadow, mirror copies, and the loading cache (`_FieldDataCache`, `m_dCache` 0x600 bytes at JP 0x0055f390, `m_loadQ` 0x200 bytes at 0x0055f190).

## Layout (partial; offsets in bytes)

| off | name |
|---|---|
| 0x08 | vtable (`__vt__11CFieldModel`) |
| 0x10 | pos (FVector, world; y snapped to the floor) |
| 0x20 | rot (FVector, model euler: x pitch, y yaw, z roll) |
| 0x30 | move rotation used to orient the root translation (x,y,z at 0x30/0x34/0x38) |
| 0x40 | last applied translation |
| 0x50,0x60 | FVector members (view point / target) |
| 0x80..0x8b | state/flag bytes: 0x80 b0-1 display mode, b2-3 `PlayMoveMotion` allowed...; 0x85 b2-3 move mode (0 none, 1 auto-move, 2 path-move), b4-5 gait (0 idle, 1 walk, 2 run); 0x86 b3-4 hold/lock state; 0x88 b1-2 hit/avoid flags |
| 0x98 | s16 BG model kind (0/1/2, `CFieldBG::Dsp`) |
| 0xa4 | int[3] idle/walk/run motion ids (`SetMoveMotion(a,b,c)`; the ctor and `ReadCB` pass the defaults **1, 2, 3** = `fidl`, `walk`, `run` in `fldMotionList`; the earlier 0x1b..0x1d was a misreading) |
| 0xb0 / 0xb1 | navi-map item id+1 / icon (hi nibble) + colour (lo nibble) |
| 0xbd | auto-move stuck counter (> 100 => give up) |
| 0xc0 | script event id for "talk to this NPC" |
| 0xfc | s8 attach slot (-1 = free) |
| 0x194 | f32 accumulated walked distance |
| 0x198 | auto-move/path state, 0x1a0 FVector destination |
| 0x2b0 | f32 slope speed scale (`1.2/(dh+1.2)`) |
| 0x2cc | char[] current motion name |

## Movement pipeline (ported in `port/crates/sh2_field/src/movement.rs`)

1. `CField::Polling` -> `MakeMoveControl(&speed,&deg,pad)` (JP 0x004a5f20): left stick gauge/degree, or d-pad via `dirTbl` (speed 0.5, 45-degree steps); gait = run when gauge >= 0.95 and Cross not held, or Cross held with d-pad.
2. `CFieldModel::SetDir(FVector&, 2, 3)` turns the actor smoothly toward the camera-relative heading; `PlayMoveMotion(gait)` picks idle/walk/run motion.
3. The motion player invokes `CFieldModel::TransCallBack(const FVector& trans, FVector& out)` (JP 0x004cb410, 0xe2c bytes) every frame with the root-bone translation of the animation:
   * optional "hold" states zero the translation;
   * slope scale: floor height here vs one unit behind (`OnFloorChk`+`OnFloorPoint`), `scale = 1.2/(max(dh, -dh/2)+1.2)`, applied to trans.z;
   * rotate the translation by the model's Rx/Ry/Rz (`M = Rz*Ry*Rx`), scale 0.1 when flag `+0x19a.0` (scripted), clamp/redirect for auto-move/path-move;
   * model-to-model collision `HitChkM2M` (cancel the move and set `collided`), `AutoAvoid` for NPCs;
   * floor collision: `CircleChk(4.0, newpos)`; on failure up to 13 iterations of shrinking (x0.91) and rotating two candidate move vectors by +-atan(0.11) ("wall slide"), final `CircleChk` and `OnFloorPoint` to set y; if nothing works the actor stays (auto-movers count up `+0xbd`);
   * `UpdateMoveDistance` accumulates distance for the encounter system when the model is the manual (player) one.
4. `FloorChk()` (JP 0x004ca3c0) re-snaps y and rebuilds the frame matrix (`Rx Ry Rz` + translate).

Other groups: loading (`LoadModel`, `LoadMotion`, `UnloadMotion`, `ReadCB`, `DetachModel`, `FindData`, `_FieldDataCache::Find/GetNewData/EncodeKey/DecodeKey`), display (`Dsp/Clr/DispModel/DspModelEff/DispShadow/ClearShadow/DispClearCtrl/SetMirror/DspMirror`), motion control (`SetMotion` x3, `ChainMotion`, `GetMotionCode`, `SetMotionSpeed`, `SetBlink`, `SetTalk`, `SetFootStep`), view point (`SetViewPoint/UpdateViewPoint`: head tracking), auto-move (`AutoMove`, `MakeMoveNode`, `UpdateNodeLen`, `UpdateAutoMove`, `PauseAutoMove`, `ArriveDistination`), path-move (`PathMove`, `UpdatePathMove`, uses ENMYPATH `_PATHLIST`), callbacks (`EventCallBack`, `MotionEndCallBack`, `TransCallBack`).
`CFModel : Model` / `CXFModel : ExModel` are the thin Model subclasses that route the motion callbacks into CFieldModel.


## Model / motion lookup (verified 2026-10-09, Rust: `sh2_field::actors`)

* `CField::LoadCharacter(slot, number, flags)` (op 0x08, JP 0x004b3020) = `sprintf(name, "%03d.SET", number)` (FIELD.BIN 0x555da8) then
  `LoadCharacter(slot, name, -1, flags)` -> `CFieldModel::LoadModel(name)` -> `ReadFile` -> `"%sFIELD/MODEL/%s"` (0x556180).
* `CFieldModel::ReadCB` (0x004c13e0): the `.SET` is a package (`GetFileCount/GetFileEntry/GetFileID`); pass 0 feeds the `mdl` (0x556198) and `sdw`
  (0x5561a0) entries to `SetModel`, pass 1 gives every `anm` (0x5561a8) entry to `Model::createMotion` and a `tex` entry (0x5561b0) to the texture slot
  (+0x140).  The shipped `.SET` files have two `mdl`-tagged entries (body + hair/shadow mesh) and 5-23 `anm`.
* Script motion numbers: `GetMotionName(id)` (0x004c0270): `id >= 0` -> `fldMotionList[id]` (53 string pointers at 0x556010: 1 `fidl`, 2 `walk`, 3 `run`,
  4..6 `sq_a..c`, 7 `inve`, 8 `agre`, 9 `rejc`, 10..12 `ta_a..c`, 13..16 `he_a..d`, 17..19 `la_a..c`, 20..22 `an_a..c`, 23..25 `lk_a..c`, 26..37 `fac1..facc`,
  38..40 `bt_a..c`, 41 `ltrn`, 42 `rtrn`, 43 `wake`, 44..46 `gi_a..c`, 47..48 `md_a..b`, 49..52 `sd_a..d`); `id < 0` -> `DecodeMotionName(id)` (packed 6-char name over the
  38 symbol alphabet `.0-9A-Z_`, see `actors::encode_motion_name`).
* PC model number = `PcRec::model_nums[0]` (`BtlSaveSec::SetPCModelNum` writes all three; initial value `PC_I[4..6]`): PC 5 -> 005.SET, PC 0 -> 000.SET,
  PC 1 -> 001.SET (PC 5 switches to 6 in "Hatena" mode, script op 0x1a).
* The root track (`ROOT`, ~16.8 units over the 28-frame walk, 33 units over the 20-frame run, motion axes: forward = -z) is what
  `Model::addTime` splits off and hands to `CFieldModel::TransCallBack`; the model itself faces -z.
