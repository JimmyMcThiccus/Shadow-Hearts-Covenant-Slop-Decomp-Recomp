# CFieldBG - retail (US)

Ghidra `SH2US_FIELD.BIN` 0x0051e560 - 0x00520e40 (JP 0x004da620 - 0x004dd110, 24 methods; **20** matched). The handle object is 8 bytes `{Impl*, CSTGDB*}` in both builds; the **`Impl` shrank from 0x1d4 to 0xc0 bytes**
(`memset(impl, 0, 0xc0)` in `Create`, US 0x0051e640).

_Generated tables use the JP mangled names as canonical keys. conf: A = anchored by chunk-tag constant / vtable, H = ordered call-graph + constant alignment (score >= 0.55), M = ordered alignment (< 0.55, tiny functions whose callees were inlined), C = hand-corrected or exact match from section G._

## Retail `Impl` layout (read from `Create`/`Dsp`/`Clr`)

| off | meaning |
|---|---|
| +0x40 | `CFieldModel*[12]` BG models (count s16 at +0xb4) |
| +0x68 | `CBgElement*` (`new 0x288`, background effect manager, section D) |
| +0x6c | MIRROR records pointer (= chunk + 0x20), count s16 at +0xb8 |
| +0x70 | motion link table `{u16 model, u16 next, char* anm name}` x motions (count s16 at +0xb6), heads in `u16[10]` at +0x7c (0xffff) |
| +0x74 | exlight id (-1) |
| +0x90 / +0x94 / +0x98 | fog near / far / colour (defaults 10.0, 16777000.0; overwritten by the `FOG` chunk); +0xa0/+0xa4/+0xa8 are the copies |
| +0x9c / +0xac | background colour (`BGCOLOR` chunk, 0 when absent) and its copy |
| +0xb0 | flags: b0 displayed, b1 from `FIELD.+0x12` bit 0 (BG shadow variant), b2-3 extra-light pending |
| +0xb2 | s16 `Create` argument, +0xba u8 `FIELD.+0x10` |

## Differences against the JP demo
1. **Same chunk set, now with data.** The JP code already contains the `MIRROR` and `BGCOLOR` readers; no demo map has those chunks. Retail data has `MIRROR` in 23 maps, `BGCOLOR` in 49, `FOG` in 553/559, `MODEL` in 554, `LIGHT` in 531, `EFFECT` in 397 (test `us_chunk_census`).
2. **`Dsp`** (0x51f850) loads the fog into the active `GsxCamera` (`+0x380/+0x384` near/far, `+0x368 = 256/(far-near)`, `+0x36c = 255.0`, colour bytes at `+0x388..8b`) and the clear colour (`+0x180 = Impl+0x9c`); kind 0 models go to OT layers 8/9, kind 2 to 0/1, kind 1 (shadow receiver) to layer 2 / 5-6.
3. `Create` (0x51e640) creates models of kind 0/1/2 (`new CFieldModel` 0x340, `SetModel(.., kind+0x80)`, `SetPos`, `SetDir(..,0,3)`) and kind-3 motions linked per model; calls `GetShadowCtrl(1)` once models exist.
4. `CheckMirror` (0x51ed00) is unchanged (planar mirror projection against three corner points, `MIRROR` record size 0x30).

## Method table

| JP addr | US addr | method (JP mangled name) | conf | size JP/US |
|---|---|---|---|---|
| `004da620` | `0051e560` | `__ct__8CFieldBGFv` | H | 30/10 |
| `004da650` | `0051e570` | `Create__8CFieldBGFP9BufMemoryi` | H | 100/d0 |
| `004da750` | `0051e640` | `Create__8CFieldBGFP6CSTGDBi` | A | 6b0/610 |
| `004dafb0` | `0051ed00` | `CheckMirror__8CFieldBGFP9GsxCameraR7FVector` | H | ad0/a40 |
| `004dba80` | `0051f740` | `Release__8CFieldBGFv` | H | 140/110 |
| `004dbbc0` | `0051f850` | `Dsp__8CFieldBGFv` | H | 410/300 |
| `004dc170` | `0051fdd0` | `Clr__8CFieldBGFv` | H | 200/170 |
| `004dc370` | `0051ff40` | `SaveRestoreMotion__8CFieldBGFiPc` | H | 130/f0 |
| `004dc4c0` | `00520030` | `Update__8CFieldBGFf` | H | a0/90 |
| `004dc560` | `005200c0` | `LgtAttachFrame__8CFieldBGFiP5Frame` | H | 40/10 |
| `004dc5a0` | `005200d0` | `FindFrame__8CFieldBGFiPCc` | H | 80/40 |
| `004dc680` | `00520110` | `GetModelCount__8CFieldBGFv` | H | 60/20 |
| `004dc6e0` | `00520150` | `GetShadowCtrl__8CFieldBGFb` | H | d0/90 |
| `004dc7b0` | `005201e0` | `ReleaseShadow__8CFieldBGFv` | H | 90/70 |
| `004dc840` | `00520360` | `StartEffect__8CFieldBGFi` | H | 160/100 |
| `004dc9a0` | `00520460` | `StopEffect__8CFieldBGFi` | H | 150/100 |
| `004dcaf0` | `00520560` | `EffectAlpha__8CFieldBGFifi` | H | 140/110 |
| `004dcc30` | `00520670` | `AddExLight__8CFieldBGFPv` | H | 80/70 |
| `004dccb0` | `005206e0` | `RecreateExLight__8CFieldBGFv` | H | 3b0/3d0 |
| `004dd080` | `00520bd0` | `RemoveExLight__8CFieldBGFv` | H | 90/70 |

### JP methods without a US counterpart
`__dt__8CFieldBGFv` (JP 004a3900, 0x60), `GetMirrorInfo` (JP 004dae80, 0x40), `GetModel` (JP 004dc620, 0x60), `GetExLight` (JP 004dd060, 0x20)

### Retail-only helpers
| US addr | size | name | role |
|---|---|---|---|
| `0051ec50` | 0x20 | `FUN_0051ec50` | (unidentified helper) |
| `0051fb50` | 0x100 | `FUN_0051fb50` | script op: BG model attach (`CFieldBG` helper) |
| `0051fc50` | 0x60 | `FUN_0051fc50` | (unidentified helper) |
| `0051fcb0` | 0x90 | `FUN_0051fcb0` | (unidentified helper) |
| `0051fd40` | 0x90 | `FUN_0051fd40` | (unidentified helper) |
| `00520130` | 0x20 | `FUN_00520130` | (unidentified helper) |
| `00520250` | 0x110 | `FUN_00520250` | `SetFieldData` helper for BG effect slots (writes 0.001-scaled times) |
| `00520ab0` | 0x10 | `FUN_00520ab0` | (unidentified helper) |
| `00520ac0` | 0x110 | `FUN_00520ac0` | (unidentified helper) |
| `00520c40` | 0x150 | `FUN_00520c40` | `FldTeamChange` constructor (created by `CField::Init`) |
| `00520d90` | 0x10 | `thunk_FUN_00521610` | (unidentified helper) |
| `00520da0` | 0xa0 | `FUN_00520da0` | (unidentified helper) |
