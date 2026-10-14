# Motion file format (`SQHD`, PKB entry type `anm`)

From `Model::createMotion` (JP 0x0023f170) → `SequenceControl::Cleate` (0x00245820) → `Sequence::Cleate` (0x00245af0) →
`RotAnim::Cleate` (0x00242b40) / `TranceAnim::Cleate` (0x00243010) / `Event::Cleate` (0x00245d60), runtime
`SequenceControl::addTime` (0x00245670), `Frame::calcMotion` (0x00243ed0), `Event::checkEvent` (0x00246260).
Rust: `port/crates/sh2_formats/src/motion.rs`.  Verified on 3,400+ motions (every file parses to exactly the start of the
next package entry; all rotation keys are unit quaternions to 3 decimals).

Motions of a character live next to its `mdl` in the same package (`anm` entries, 5-60 per model).  A motion contains one
track per bone *by name* (`ROOT`, `WAIST0`...; `Frame::searchFrame` links them), so a motion can be shared by any model
with the same bone names; missing tracks leave the bone at bind pose.

## Header (0x20 bytes)

| off | type | meaning |
|---|---|---|
| 0x00 | char[4] | `"SQHD"` |
| 0x04 | char[12] | motion name (`fidl`, `app`, `bef_1`, `save_00`...) — compared by `strncmp(..., 0xc)` |
| 0x10 | u16 | frame count (`SequenceControl::Cleate` subtracts 1 once when `+0x1a == 0`, so the stored value is last_frame+1) |
| 0x12 | u16 | number of bone tracks (`Sequence`) |
| 0x14 | u8 | flags: bit0 = loop, bit1 = main/full-body motion (`Model::setMotion` sends motions without bit1 to the sub-motion slot; `createInterMotion` ORs 2 into the two built-in `INTER_A/INTER_B` blend motions) |
| 0x15 | u8 | frames per second (30; the runtime stores `1.0/fps`, default 1/60 = 0x3c888889) |
| 0x16 | u16 | number of event tracks |
| 0x18 | u16 | 6 (unused) |
| 0x1a | u16 | "already adjusted" marker for the frame-count patch |

Duration in seconds = `last_frame / fps`.  `SequenceControl+0x1c` is the current time in **seconds**; sampling time in key
units is `time * fps` (key times are integer frames).

## Bone tracks (`Sequence`, one per bone, in file order)

```
char name[16]; u16 rot_count; u16 pos_count; pad to 0x20
u16 rot_time[rot_count];   pad16
s16 rot_key[rot_count][4]; pad16    quaternion xyzw = value/4096 (ITOF12)
u16 pos_time[pos_count];   pad16
u8  pos_key[pos_count][8]; pad16    SVector (below)
```
All counts of 1 mean "constant"; the sampler (`RotAnim::getQuaternion`, `TranceAnim::getTrance`) linearly searches for the
interval `t_i <= t < t_{i+1}` starting from the last used index (cursor at +8), `slerp` for rotation and lerp for
translation; past the last key it clamps to it.

`SVector` (8 bytes) — `SVector::ShortToFloat` (0x0023d910): `s16 x,y,z; u16 w`.
Component i = `(s16_i << 5) | ((w >> 5*i) & 31)` interpreted as a signed 20-bit integer, times `0.01`; if `w & 0x8000`
the scale is 1.0 instead (range extension, used when a coordinate exceeds 10485.75).  `w` bit field layout: x bits 0-4, y 5-9, z 10-14.

Pose: `Sequence::getMatrix` (0x00245be0) returns `D = [R(q) | d]` (rotation matrix with the translation in column 3).  The
skeleton step (see `Frame::calcMatrix`) is `M_i = M_parent * B_i^-1 * D_i * B_i` — keys are *deltas relative to the bind
pose* (identity keys = bind pose), expressed in the bone's bind frame.

## Event tracks (`Event`, header 0x10 + data)

```
char name[8]; u16 key_count; u16 bone_or_arg; u8 kind; pad to 0x10
keys: group = 2 keys if (kind&0xf)==3 else 4; n = round_up(key_count, group)
      kind&0xf: 0 -> n x f32 time          (pure trigger)
                1 -> n x { u16 time, s16 value }        value/256 for "Scale*" etc.
                2 -> n x { u16 time, u16 value, u32 extra }  (8 bytes)
                3 -> n x { u16 time, u8 value, u8 value2, u32 extra }
      kind>>4 != 0 : discrete (value taken at the key); == 0 and kind&0xf == 1: interpolated linearly between keys
```
`Event::checkEvent` calls the owning model's virtual `EventCallBack(const char *motion_name, event_header, value, bone_arg, extra)`
(`vtable+0x34`; `Model::EventCallBack` 0x00240290, `ExModel::EventCallBack` 0x002614c0, `MenuModel::EventCallBack` 0x00282260).
Events fire once as time passes their key (cursor at `Event+0x10`), `setIndex` re-seeks after `setCTime`/loops.

Event names seen in the shipped data (counts over FIELD/BTLDATA/EFFECT):

| name | meaning (from `EventCallBack`) |
|---|---|
| `PolColR/G/B/A` | per-atomic polygon colour channel animation (bone_arg = atomic) — effect models |
| `transX/Y/Z`, `rotateZ`, `scaleX/Y` | 2D sprite-model transforms (effects, menu) |
| `ScaleA`, `ScaleX/Y/Z` | bone scale (uniform / per axis), value/256 |
| `Visible ` | atomic/frame visibility switch (note the trailing space; 8 chars) |
| `TXA*` (`TXAeye`, `TXAA`, `TXAhp3_1`...) | texture-animation selector: index into the model's `TXAH` table (kind 0x11) |
| `SEtrigg`, `foot`, `ki_w` | sound-effect / footstep triggers |
| `MosEvent`, `MosCncel`, `MosCncl`, `MosCance` | motion event numbers consumed by the field/battle scripts |
| `MdlAlpha`, `TexAlpha`, `ACR`, `DYNA` | model alpha, texture alpha, accumulate-render, dynamics reset |

## Blending
`InterSequenceControl` (0x002442d0, size 0x50) is a motion that cross-fades from the current pose to the next motion
(`INTER_A`/`INTER_B`, `Model::createInterMotion`, `setNextMotion(name, frames)`); `setInterData` (0x00244530, 0xf8c bytes)
builds interpolation keys from the live frame matrices.  Not ported yet.

`EncodeMotionName/DecodeMotionName/GetMotionName` (FIELD.BIN 0x4bff50) map script motion numbers to these names — not analysed.


## Event handling in the port (2026-10-09; `sh2_gfx::model::ModelInstance::apply_events`, census over every `SQHD` of both discs)
Key decoding: `sh2_formats::motion::EventTrack::keys()` (`EventKey { time, value, value2, extra }`; kind 0 `f32` time, 1 `{u16 t, s16 v}`, 2 `{u16 t, u16 v, u32 extra}`,
3 `{u16 t, u8 v, u8 v2, u32 extra}`), `is_discrete()` (`kind >> 4 != 0`, else linear between keys).  Discrete events fire once when a key time is passed
(`event_time` cursor, reset on loop / motion change); interpolated tracks are sampled every update.

| event | tracks (JP / US) | who | applied as |
|---|---|---|---|
| `Visible ` (kind 0x11) | 5.7k / 14k | characters, BG | atomic `bone_arg` shown / hidden; `0x8000 | g` = **first** atomic whose header byte +0x17 is `g` (`Model::searchGroup`, 0x002407c0) |
| `TXAeye` + `TXAeyeA/B/a/ka/v/1..4/bo/ko/ny/_o` | 1.6k / 3.3k | characters (80 field + 23 battle models) | `changeTextureAnim(name, value)` (frame of the `TXAD` entry); plus the blink machine for entry `eye` (`Blink`, see notes/integration/actors.md) |
| `TXAA`, `TXAdr*`, `TXAfl`, `TXAhp*`, `TXASTU2`, `TXASUP1` ... | few | BG / effect / menu models | same |
| `MdlAlpha`, `MCA` (value 0..0x80) | 32 / 240 | characters, BG | model alpha |
| `ACR` | 38 / 191 | characters, BG | atomic alpha (`Atomic+0x2b3`) |
| `DYNA` (kind 0x11) | 8 / 280 | characters | `Model::DynaFunction(value)`: 0 disable / 1 enable / 2 reset the hair & cloth chains |
| `BSASeq01` (kind 0x13) | 0 / 46 | US models 409, 470 | blend-shape slider weights, see model_format.md |
| `SEtrigg`, `foot`, `ki_w`, `MosEvent`, `MosCncel`... | | audio / script | consumed by the field / battle layers (`Motion::event_frames`) |
| `ScaleA/X/Y/Z` (kind 1) | 7.9k / 9.4k (**effect models only**) | `ExModel::EventCallBack` | frame `bone_arg` scale = `(value & 0x7fff)/256`, bit 15 = sign (`Frame::extraMat` diagonal; the bone is scaled about its own pivot: `A = R * S * T`) |
| `PolColR/G/B/A` (kind 1) | 37k / 48k (effect models only) | `ExModel` | per-atomic colour channel / alpha (`value/128` here; the original scales by `ExModel+0x500..0x50c`, unverified) |
| `TexAlpha` | 263 / 362 (effects) | `ExModel` | alpha of every atomic using texture `bone_arg`: `(1 - value/4096 * sign) * 128` |
| `TPL` / `TPA` | 0 / 268 (effects) | `Model::EventCallBack` | `Atomic::set2PathColor/Alpha` (additive second pass) -- **not implemented** (no character or BG model has them) |
| `scaleX/Y`, `rotateZ`, `transX/Y/Z` (kind 1) | 27k / 35k (effects) | billboard (`BAtomic`) atomics | `bevy::billboard` parameters (scale `v/4096`, roll `v/-4096`, offset `v/32`, `-v/32`, `-v/32`) |
