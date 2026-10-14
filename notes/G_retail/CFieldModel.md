# CFieldModel - retail (US)

Ghidra `SH2US_FIELD.BIN`, methods in 0x00508590 - 0x00512330 (JP 0x004c06b0 - 0x004cc280, 111 methods; **79** matched, the rest are accessors that retail inlines).
JP reference `notes/G/CFieldModel.md`. Object size **0x340** (JP 0x2e0; `new 0x340` in `CFieldBG::Create` and `CField::LoadCharacter`). Vtable at +8: US 0x0043e530 `[0, 0, ~CFieldModel 0x508740, DelayDeleteObject::DelayDelete 0x223e70]`.

_Generated tables use the JP mangled names as canonical keys. conf: A = anchored by chunk-tag constant / vtable, H = ordered call-graph + constant alignment (score >= 0.55), M = ordered alignment (< 0.55, tiny functions whose callees were inlined), C = hand-corrected or exact match from section G._

## Layout (JP offset -> US offset, derived by aligned access sequences)

| JP range / field | US | notes |
|---|---|---|
| +0x08 vtbl, +0x10 pos, +0x20 rot (+0x24 yaw), +0x30 move rotation, +0x40, +0x50, +0x60 FVectors | same | |
| (new) | +0x70 FVector | position backup written by `Retail_CFieldModel_SuspendForMenu`, read by `ResumeAfterMenu` (shop / tailor / menu hide) |
| +0x80..+0x8c state bytes (display mode, gait, move mode, hold, hit flags) | +0x90..+0x9c | +0x10; byte +0x99 bit 7 is the *collided* flag (`SetCollided`/`isCollided`, JP +0x89) |
| +0x98 s16 BG model kind | +0xa8 | |
| +0x9c, +0xa0, +0xa4.. (motion ids, navi icon) | +0xac, +0xb4, +0xb8.. | +0x10 / +0x14 |
| +0xbc/+0xbd (auto-move stuck counter) | +0xcc/+0xcd | |
| (new) | +0xce, +0xcf, +0xd0, +0xf0 | field-monster sight: target index+1, sight cone value, "already noticed" flag, event id (written by script op 0x1b, read by `CheckNpcSight`) |
| +0xcc.. | +0xe4.. | +0x18 |
| +0xf0.. | +0x10c.. | +0x1c |
| +0x120.. (callbacks, move info) | +0x140.. | +0x20 |
| +0x190.. | +0x1b0.. | +0x20 |
| +0x2b0 slope scale | +0x310 | +0x60 (delta grows because of the new fields above) |
| +0x2cc current motion name | +0x31c | |
| (load queue) | +0x2d0.. | per-model 3-state read slots serviced by `FUN_00508fc0` (JP uses the global `m_loadQ` only) |

Global tables are unchanged in size: `_FieldDataCache` table 0x80 x 0xc at 0x00615a20 (JP 0x0055f390 - 0x600 bytes), load queue 0x20 x 0x10 at 0x00615820 (0x200 bytes).

## Differences against the JP demo
1. **Movement / collision is the same code.** `TransCallBack` (0x00511560, 0xdd0 bytes; JP 0x004cb410, 0xe30): slope scale `1.2 / (max(dh, -dh/2) + 1.2)`, rotation by `Rz*Ry*Rx`, `CircleChk(4.0)`, 13 shrink steps of 0.91 with
   +-atan(0.11) slides - identical constants. The Rust `movement.rs` is therefore valid for retail and is exercised on 1813 US entry points (`tests/retail_us.rs`).
2. **Event boxes as walls** - for the controlled model, once it overlaps a different EVENTBOX (`HitChkM2E`), `Retail_CField_CheckEventBoxSweep` -> `Retail_CFieldEvent_SweepHit` slides/cancels the step.
3. **`SetDir`** (0x0050d7b0): a heading change below 1 degree (`0.017453289`) snaps instead of starting a turn; the turn side is stored in a 2-bit field (`+0x96` bits 5-6; JP used `+0x85` bit 7);
   the turn-animation speed factor is `x * (cos*0.5 + 1)` instead of `x / (2 - cos)`; the turn limits are +-pi.
4. **`UpdatePathMove`** gains an arrival rule (`0.9`, `20.0`, `pi`); **`SetCharacterDir`** uses +-pi/2.
5. **Field-monster sight** (`Retail_CFieldModel_SightTest`, 0x00510d40): `v = target - self` (y dropped, normalised), `facing = (-sin(rotY), -cos(rotY))` with `rotY = +0x34`,
   `cone = min(int((1 - facing.v) * 90), 180)`; if `cone > sight` the answer is -2, then every TRILIST triangle is tested against the XZ segment self->target (-1 when blocked), else `cone`.
6. **Menu hide/restore** - `SuspendForMenu` (0x50ac70) / `ResumeAfterMenu` (0x50acf0) / `DspAfterMenu` (0x50aa80), state in `+0x92` bits 4-7.
7. **Display**: `DispModel(i,i,i)` (0x50a570) and `Dsp(i)` unchanged except for the inlined `ShadowControl`; `DispClearCtrl` the same.

## Method table

| JP addr | US addr | method (JP mangled name) | conf | size JP/US |
|---|---|---|---|---|
| `004c03e0` | `00508390` | `ReadMotionCB__11CFieldModelFiP9BufMemory` | H | 1b0/160 |
| `004c0620` | `00508540` | `GetLoadQ__11CFieldModelFi` | H | 60/30 |
| `004c0680` | `00508570` | `PurgeLoadQ__11CFieldModelFi` | H | 30/20 |
| `004c06b0` | `00508590` | `__ct__11CFieldModelFv` | H | c0/70 |
| `004c0840` | `00508600` | `InitWork__11CFieldModelFv` | H | 1b0/140 |
| `004c09f0` | `00508740` | `__dt__11CFieldModelFv` | H | 100/c0 |
| `004c0af0` | `00508800` | `Delete__11CFieldModelFv` | H | 130/e0 |
| `004c0c20` | `00508900` | `FindData__11CFieldModelFPCc` | H | 40/20 |
| `004c0c60` | `00508920` | `ReadFile__11CFieldModelFPCc` | H | e0/f0 |
| `004c0d40` | `00508a60` | `LoadMotion__11CFieldModelFPCcUiPFUiUiPv_vPv` | H | 1f0/1c0 |
| `004c0f30` | `00508c20` | `DetachModel__11CFieldModelFP15_FieldDataCache` | H | 310/270 |
| `004c1240` | `00508e90` | `UnloadMotion__11CFieldModelFPCc` | H | 1a0/130 |
| `004c13e0` | `005090a0` | `ReadCB__11CFieldModelFP15_FieldDataCachei` | H | 370/2c0 |
| `004c1750` | `00509360` | `LoadModel__11CFieldModelFPCc` | H | b0/80 |
| `004c1800` | `005093e0` | `Reset__11CFieldModelFi` | H | 140/110 |
| `004c1980` | `005094f0` | `ChgCtrl__11CFieldModelFi` | H | 80/60 |
| `004c1a40` | `00509550` | `GetAnmName__11CFieldModelFPUc` | H | 50/20 |
| `004c1a90` | `00509570` | `FindMotionData__11CFieldModelFPCc` | H | 80/50 |
| `004c1b10` | `005095c0` | `SetModelType__11CFieldModelFi` | H | 90/80 |
| `004c1ba0` | `00509640` | `SetMoveLock__11CFieldModelFi` | H | 40/40 |
| `004c1c60` | `00509680` | `SetModel__11CFieldModelFPUci` | H | 1e0/170 |
| `004c1e40` | `00509800` | `SetBlink__11CFieldModelFi` | H | 140/d0 |
| `004c1f80` | `005098d0` | `SetTalk__11CFieldModelFi` | H | 120/f0 |
| `004c20a0` | `005099c0` | `SetMotion__11CFieldModelFii` | H | 120/f0 |
| `004c23a0` | `00509bd0` | `SetMotion__11CFieldModelFi` | H | 90/70 |
| `004c2500` | `00509cc0` | `SetMotion__11CFieldModelFPCc` | H | 2a0/250 |
| `004c27a0` | `00509f10` | `DispModel__11CFieldModelFi` | H | 40/10 |
| `004c27e0` | `00509f20` | `DspModelEff__11CFieldModelFv` | H | 170/f0 |
| `004c2980` | `0050a010` | `ClrModelEff__11CFieldModelFv` | H | d0/90 |
| `004c2a50` | `0050a0a0` | `SetGhost__11CFieldModelFv` | H | b0/a0 |
| `004c2b00` | `0050a140` | `SetMirror__11CFieldModelFi` | H | 150/100 |
| `004c2c50` | `0050a240` | `DspMirror__11CFieldModelFv` | H | 2d0/1f0 |
| `004c2fc0` | `0050a430` | `ClrMirror__11CFieldModelFi` | H | 120/e0 |
| `004c30e0` | `0050a510` | `UpdateMirrorOfs__11CFieldModelFiR7FVector` | H | a0/60 |
| `004c3180` | `0050a570` | `DispModel__11CFieldModelFiii` | H | 470/440 |
| `004c35f0` | `0050a9b0` | `Clear__11CFieldModelFi` | H | 120/d0 |
| `004c3710` | `0050aaf0` | `Dsp__11CFieldModelFi` | H | 1b0/180 |
| `004c38c0` | `0050ad40` | `Clr__11CFieldModelFi` | H | 120/e0 |
| `004c39e0` | `0050ae20` | `ClearModel__11CFieldModelFv` | H | d0/b0 |
| `004c3ae0` | `0050aee0` | `ClearShadow__11CFieldModelFv` | H | 100/c0 |
| `004c3be0` | `0050afa0` | `DispClearCtrl__11CFieldModelFv` | H | 380/2a0 |
| `004c3f60` | `0050b240` | `SetViewPoint__11CFieldModelFP7FVectorfii` | H | c0/50 |
| `004c4140` | `0050b330` | `UpdateViewPoint__11CFieldModelFf` | H | cd0/960 |
| `004c4fb0` | `0050bd50` | `Update__11CFieldModelFf` | H | 1a90/1370 |
| `004c6a60` | `0050d0c0` | `GetFramePos__11CFieldModelFPc` | H | a0/80 |
| `004c6b00` | `0050d140` | `SetPos__11CFieldModelF7FVectorb` | H | f0/140 |
| `004c6d70` | `0050d370` | `GetWorldPos__11CFieldModelFv` | H | 100/d0 |
| `004c6ef0` | `0050d630` | `GetDir__11CFieldModelFv` | H | b0/80 |
| `004c7060` | `0050d730` | `SetDir__11CFieldModelFiii` | H | 80/80 |
| `004c70e0` | `0050d7b0` | `SetDir__11CFieldModelFR7FVectorii` | H | 6e0/5d0 |
| `004c77e0` | `0050dd80` | `HitChkM2M__11CFieldModelFf` | H | 250/260 |
| `004c7a30` | `0050dfe0` | `HitChkM2E__11CFieldModelFv` | H | 30/40 |
| `004c7a60` | `0050e020` | `SetMoveMotion__11CFieldModelFiii` | H | b0/70 |
| `004c7b10` | `0050e090` | `SetLastMotion__11CFieldModelFPCc` | H | 40/10 |
| `004c7b50` | `0050e1e0` | `PlayMoveMotion__11CFieldModelFi` | H | 1c0/160 |
| `004c7d10` | `0050e340` | `CheckLastCmdComplete__11CFieldModelFv` | H | 130/d0 |
| `004c7f10` | `0050e4b0` | `SearchFrame__11CFieldModelFPCc` | H | 70/50 |
| `004c7f80` | `0050e500` | `AutoMove__11CFieldModelFP7FVectoriii` | H | 320/310 |
| `004c82a0` | `0050e810` | `PathMove__11CFieldModelFiPC9_PATHLISTUi` | H | d0/e0 |
| `004c84c0` | `0050e990` | `MakeMoveNode__11CFieldModelFP7FVector7FVector` | H | 960/880 |
| `004c8e20` | `0050f210` | `UpdateNodeLen__11CFieldModelFv` | H | 1b0/120 |
| `004c8fd0` | `0050f330` | `PauseAutoMove__11CFieldModelFi` | H | 140/1c0 |
| `004c9110` | `0050f4f0` | `ArriveDistination__11CFieldModelFi` | H | 140/170 |
| `004c9250` | `0050f660` | `UpdateAutoMove__11CFieldModelFf` | H | 800/6f0 |
| `004c9a50` | `00511530` | `isCollided__11CFieldModelFv` | C | 30/10 |
| `004c9a80` | `0050fd50` | `UpdatePathMove__11CFieldModelFf` | H | 870/7d0 |
| `004ca2f0` | `00510520` | `PushChkFlags__11CFieldModelFv` | H | 50/30 |
| `004ca340` | `00510550` | `PopChkFlags__11CFieldModelFv` | H | 80/50 |
| `004ca3c0` | `005105a0` | `FloorChk__11CFieldModelFv` | H | 130/130 |
| `004ca7e0` | `00510910` | `AutoAvoid__11CFieldModelFv` | H | 400/430 |
| `004cac00` | `00510fa0` | `CreateModel__11CFieldModelFv` | H | f0/80 |
| `004cad50` | `00511020` | `GetFrame__11CFieldModelFv` | H | 50/20 |
| `004cada0` | `00511040` | `AddTime__11CFieldModelFf` | H | 90/70 |
| `004cae30` | `005110b0` | `CalcMatrix__11CFieldModelFv` | H | 90/70 |
| `004caec0` | `00511120` | `EventCallBack__11CFieldModelFPCcPCciiUi` | H | 1c0/140 |
| `004cb080` | `00511260` | `MotionEndCallBack__11CFieldModelFPCc` | H | 390/2d0 |
| `004cb410` | `00511560` | `TransCallBack__11CFieldModelFRC7FVector7FVector` | H | e30/dd0 |
| `004cc240` | `00511540` | `SetCollided__11CFieldModelFi` | C | 40/20 |
| `004cdc00` | `00513380` | `DspIcon__11CFieldModelFi` | H | c0/90 |

Free functions of the same unit are in `CField.md` (section 6, "free functions"). `_FieldDataCache`:

| JP addr | US addr | method (JP mangled name) | conf | size JP/US |
|---|---|---|---|---|
| `004bf770` | `00507890` | `Release__15_FieldDataCacheFv` | H | 90/a0 |
| `004bf800` | `00507930` | `FindKey__15_FieldDataCacheFPCc` | H | 120/c0 |
| `004bf9d0` | `00507a50` | `EncodeKey__15_FieldDataCacheFPCcRUi` | H | 170/160 |
| `004bfb40` | `00507bb0` | `DecodeKey__15_FieldDataCacheFPcUiUi` | H | 270/220 |
| `004bfdb0` | `00507dd0` | `Find__15_FieldDataCacheFiPCc` | H | c0/a0 |
| `004bfe70` | `00507e70` | `GetNewData__15_FieldDataCacheFiPCc` | H | e0/b0 |

`_AutoMoveInfo` / `_PathMoveInfo` / `CFModel` / `CXFModel` / `CBalIcon` / `BgeffLight*`:

| JP addr | US addr | method (JP mangled name) | conf | size JP/US |
|---|---|---|---|---|
| `004c8370` | `0050e8f0` | `clear__13_AutoMoveInfoFv` | H | 30/10 |
| `004c83a0` | `0050e900` | `FixNode__13_AutoMoveInfoFv` | H | f0/80 |

| JP addr | US addr | method (JP mangled name) | conf | size JP/US |
|---|---|---|---|---|
| `004c8490` | `0050e980` | `clear__13_PathMoveInfoFv` | H | 30/10 |

| JP addr | US addr | method (JP mangled name) | conf | size JP/US |
|---|---|---|---|---|
| `004cc280` | `00512330` | `__ct__7CFModelFv` | H | 50/40 |
| `004cc2d0` | `00512370` | `__dt__7CFModelFv` | H | 90/70 |
| `004cc360` | `005123e0` | `getPacket__7CFModelFv` | H | 80/70 |
| `004cc410` | `00512450` | `EventCallBack__7CFModelFPCcPCciiUi` | M | 80/80 |
| `004cc4d0` | `005124e0` | `TranseCallBack__7CFModelFRC7FVector7FVector` | M | 60/60 |

| JP addr | US addr | method (JP mangled name) | conf | size JP/US |
|---|---|---|---|---|
| `004cc530` | `00512540` | `__ct__8CXFModelFv` | H | 50/40 |
| `004cc580` | `00512580` | `__dt__8CXFModelFv` | H | 90/70 |
| `004cc610` | `005125f0` | `getPacket__8CXFModelFv` | H | 90/70 |
| `004cc6a0` | `00512660` | `EventCallBack__8CXFModelFPCcPCciiUi` | M | 80/80 |
| `004cc720` | `00512750` | `MotionEndCallBack__8CXFModelFPCc` | H | 40/30 |

| JP addr | US addr | method (JP mangled name) | conf | size JP/US |
|---|---|---|---|---|
| `004cc840` | `00512780` | `__dt__8CBalIconFv` | H | 80/60 |
| `004cc8c0` | `005127e0` | `Delete__8CBalIconFv` | H | 40/40 |
| `004cc900` | `00512820` | `Release__8CBalIconFv` | H | 60/40 |
| `004cc960` | `00512860` | `SetPat__8CBalIconFii` | H | 2c0/200 |
| `004cce50` | `00512a60` | `Dsp__8CBalIconFv` | H | 40/10 |
| `004cce90` | `00512a70` | `Clr__8CBalIconFv` | H | 40/20 |
| `004cced0` | `00512a90` | `SetCenter__8CBalIconFP7FVector` | H | 140/150 |
| `004cd010` | `00512be0` | `AddTime__8CBalIconFf` | H | b30/7a0 |

| JP addr | US addr | method (JP mangled name) | conf | size JP/US |
|---|---|---|---|---|
| `004ce240` | `005137a0` | `__ct__10BgeffLightFiPv` | H | 2e0/260 |
| `004ce520` | `00513a00` | `__dt__10BgeffLightFv` | H | 80/70 |
| `004ce5a0` | `00513a70` | `DeleteLight__10BgeffLightFv` | H | 80/60 |
| `004ce620` | `00513ad0` | `Calculate__10BgeffLightFv` | H | 330/2d0 |
| `004ce950` | `00513da0` | `SetPacket__10BgeffLightFv` | H | 630/540 |

| JP addr | US addr | method (JP mangled name) | conf | size JP/US |
|---|---|---|---|---|
| `004ce040` | `00513610` | `__ct__14BgeffLightPrimFPv` | H | 120/e0 |
| `004ce160` | `005136f0` | `__dt__14BgeffLightPrimFv` | H | 90/70 |
| `004ce1f0` | `00513760` | `OnDelete__14BgeffLightPrimFv` | H | 50/40 |

### JP methods without a US counterpart (inlined in retail)
`GetPos` (JP 004a3630, 0x40), `isDsp` (JP 004a3670, 0x30), `isAutoCtrl` (JP 004a8230, 0x30), `GetRot` (JP 004a8260, 0x40), `isManual` (JP 004a82e0, 0x70), `isLoading` (JP 004a8350, 0x30), `GetRotY` (JP 004a8380, 0x20), `GetMdlRot` (JP 004aa6a0, 0x40), `GetModel` (JP 004ab800, 0x20), `isLoaded` (JP 004ac840, 0x30), `isEmpty` (JP 004b0540, 0x30), `ClrViewPoint` (JP 004b0570, 0x20), `SetManual` (JP 004b0590, 0x40), `SetCmd` (JP 004b05d0, 0x30), `SetMotionSpeed` (JP 004b0600, 0x30), `SetLastCmdEvent` (JP 004b0630, 0x30), `isMove` (JP 004b3d10, 0x30), `isFloorChk` (JP 004b3ff0, 0x30), `isHitChk` (JP 004b4df0, 0x30), `SetHitCheck` (JP 004b4fc0, 0x40), `SetFloorChk` (JP 004b5000, 0x40), `GetNewLoadQ` (JP 004c0590, 0x90), `SetFootStep` (JP 004c1a00, 0x40), `AddNaviItem` (JP 004c1be0, 0x80), `ChainMotion` (JP 004c21c0, 0x1e0), `GetMotionCode` (JP 004c2430, 0xd0), `DispShadow` (JP 004c3ab0, 0x30), `ResetMotion` (JP 004c77c0, 0x20), `GetBaseModel` (JP 004cabe0, 0x20), `SetRot` (JP 004dae00, 0x40), `SetExModel` (JP 004dae40, 0x40), `GetLastMotion` (JP 004dc4a0, 0x20)

## Retail-only / unidentified functions in the CFieldModel range

| US addr | size | name | role |
|---|---|---|---|
| `00506c80` | 0x10 | `FUN_00506c80` | `CFieldEvent::Init(boxes, count, is_camera)` |
| `00507010` | 0x610 | `Retail_CFieldEvent_SweepHit` | `CFieldEvent::SweepHit(box, p0, p1)`: slides a movement segment along the nearest edge of an EVENTBOX (wall collision against event volumes) |
| `00507760` | 0x80 | `FUN_00507760` | `_FieldDataCache` entry reference release |
| `005077e0` | 0xb0 | `Retail_FieldDataCache_TickN` | `_FieldDataCache` slot aging loop (frees entries whose count reached 0) |
| `005084f0` | 0x50 | `FUN_005084f0` | `_FieldDataCache::GetNewData` free-slot search (32 entries at 0x615820) |
| `005088e0` | 0x10 | `Retail_FieldDataCache_Tick` | (unidentified helper) |
| `005088f0` | 0x10 | `Retail_FieldDataCache_ReleaseAll` | (unidentified helper) |
| `00508a10` | 0x50 | `FUN_00508a10` | `CFieldModel::GetNewLoadQ` (find a free load-queue slot) |
| `00508fc0` | 0xe0 | `FUN_00508fc0` | `CFieldModel::PollLoadQ` (service the 3-state load queue +0x2d0..) |
| `005097f0` | 0x10 | `FUN_005097f0` | (unidentified helper) |
| `00509ab0` | 0x120 | `FUN_00509ab0` | `CFieldModel::ChainMotion` |
| `00509c40` | 0x80 | `FUN_00509c40` | `CFieldModel::GetMotionCode` (search of the 0x37 motion-name table) |
| `0050aa80` | 0x70 | `Retail_CFieldModel_DspAfterMenu` | show the model again after a menu (`Dsp` + clear the suspend state) |
| `0050ac70` | 0x80 | `Retail_CFieldModel_SuspendForMenu` | `SuspendForMenu`: save position to +0x70 and hide the model for the shop/tailor/menus |
| `0050acf0` | 0x50 | `Retail_CFieldModel_ResumeAfterMenu` | `ResumeAfterMenu`: restore position from +0x70 |
| `0050aed0` | 0x10 | `FUN_0050aed0` | (unidentified helper) |
| `0050d440` | 0x1f0 | `FUN_0050d440` | `CFieldModel::GetDir`-like direction helper used by `GetCharacterInfo` |
| `0050e0a0` | 0x140 | `FUN_0050e0a0` | turn/motion state helper (`SetDir` finishing) used by `DispModel` |
| `00510d40` | 0x250 | `Retail_CFieldModel_SightTest` | monster sight test: cone value `(1-cos)*90` against the viewing limit, then TRILIST triangle blocking |
| `00510f90` | 0x10 | `FUN_00510f90` | (unidentified helper) |
| `005124d0` | 0x10 | `FUN_005124d0` | (unidentified helper) |
| `005126e0` | 0x10 | `FUN_005126e0` | (unidentified helper) |
| `005126f0` | 0x60 | `FUN_005126f0` | (unidentified helper) |
| `005142e0` | 0x10 | `FUN_005142e0` | (unidentified helper) |
| `005142f0` | 0x10 | `FUN_005142f0` | (unidentified helper) |
| `00514300` | 0x10 | `FUN_00514300` | (unidentified helper) |
| `00514310` | 0x10 | `FUN_00514310` | (unidentified helper) |
