# Effect system — object model and lifetime (section D)

Sources: `Effect.cpp` / `EffectCore.cpp` / `Vec.cpp` (0x002fc0c0..0x00305030), `EffectCamera/Model/Light/Sprite/Blur/Gunya/Barin`
(0x00305030..0x00324b00), `LsdEffect*` (0x00324b00), `Fp*Param` (0x00325750), `LineBlur` (0x00326860),
`PutiEffect.cpp` (0x0025ca60), `FpEffect*.cpp` (0x00298b60..0x002bf6f0), `JRing.cpp` (0x002bf6f0), `BgEffectMan/CBgElement/CSTGDB`
(0x003c1f60), `CGhostEfx` (0x003d3f50), `CBRingSoulOT/CBM41xOT/CBM524` (0x003da6e0..0x003dff50).
Rust: `port/crates/sh2_gfx/src/effects/` (`effect.rs`, `motion.rs`, `puti.rs`, `fp.rs`, `jring.rs`; `vsm.rs`/`efmg.rs` are re-exports of `sh2_script::{vsm,efmg}`, the merged VEC interpreter, see `notes/integration/vec_merge.md`).
Decompiled C: `decomp/D/*.c`.

## 1. Big picture

An *effect* in this engine is a **small script-driven scene**: an `EFMG` data file (see `effect_format.md`) carries a
bytecode program (VSM) plus the models, motions, cameras, lights, hit volumes and sounds it needs.  The program
runs in cooperative threads and drives all of them through 269 system calls.  Battle magic/attack animations, field
cut-ins and many menu effects are all effects.  Two *other* families sit beside the scripted effects and are
driven directly from game code instead of bytecode:

* **Puti / Fp particles** — `PutiPrim`/`PutiObject` (billboard particle quads) and ~15 `Fp*` effect classes (smoke, flare,
  fog, torch, candle, thunder, black hole, fountain, waterfall, lens flare...) created by `CreateFpEffect(type, params)`
  from the field background manager `BgEffectMan` (`type < 0x100`) or by the VSM system calls `fef*`/`pgr*`/`pph*`.
* **`JRing`** — the Judgement Ring (battle input) with its helper objects (`judgement_ring.md`).

## 2. Creating an effect

```
caller (BtlEff / CField::StartEffect / sysCreateEffect)
   path = sprintf("EFFECT/%s", name)            DvdromOrder::ReadOrder(path, callback)  -> BufMemory*
   callback:  new Effect(endCb,arg0,arg1)
              Effect::Create(BufMemory*)   -> new EffectCore(this)  [0x610 bytes]
                                              EffectCore::Create: AddOT(World, layer 9, new PolPacket)
                                              for each EFMG entry: 'T' -> vpTextureFile::Create, 'C' -> CreateVec
                                              EffectCore::Run -> main VEC.Start()
              Effect::OnCreate(core)          (virtual, hook for subclasses e.g. field/battle)
              Effect::SetGenModel/TarModel/GenPos/TarPos(n, array)   <- who casts / who is hit (tagModelSet {Model*,..})
              Effect::SetEndCallback(fn,a,b)
              Effect::Run()  -> CPoller::Entry(app+0x48, this, prio 0x80)
```
`CField::StartEffect(name,flags,paramA,paramB)` (FIELD.BIN 0x004d9ff0) builds a record `{next, Effect*, state, kindA,idxA,ptrA, kindB,idxB,ptrB}`
(arrays of `idx` pairs of 16/20 bytes: generating and target model sets/positions) and reads `EFFECT/<name>` with
`OnLoadEffect` (0x004da290) as the completion callback; `RemoveEffect` deletes by record.  Battle uses `BtlEff`
(BATTLE.BIN) the same way.  `Effect::Duplicate(Effect*)` / `EffectCore::Duplicate` (0x00304250, 2.6 KB) copy model sets,
positions, handles and add-time scalars from a parent when a script starts a nested effect
(`sysCreateEffect` → async load (`_cbNewEffectRead`) → `sysWaitCreateEffect` → `sysStartEffect`, which kills the parent's
threads, duplicates, runs the child and `PollDelete`s the parent = "effect chaining").

### Effect (0x48 bytes, `CPolObj`)
| off | field |
|---|---|
| 0x14 | vptr `__vt__6Effect` (0x406850): `[2] __dt`, `[3] Polling`, `[4] OnCreate(EffectCore*)` |
| 0x18 | run state: 0 paused (only `CalcMatrix`), 1 running, 2 delete requested (`PollDelete`) |
| 0x1c | started (`Run` called; `Continue` re-enters the poller only if set) |
| 0x20 | `EffectCore*` (head of a `CList` — an Effect can own several cores) |
| 0x24 | `BufMemory*` the file image |
| 0x28 | pending child `Effect*` (nested creation) |
| 0x2c/0x30/0x34 | end callback `fn(void*,int)` + 2 args (cleared after the call) |
| 0x38/0x3c/0x40 | replace callback (`SetReplaceCallback`), used by `sysStartEffect` to run the successor |
| 0x44 | saved background colour (`GsxCamera::GetBgColor` at `Run`, restored in `Stop`) |

`Effect::Polling`: state 0 → `CalcMatrix` only (returns 0); else `core->Continue()`; when the core reports finished and an
end callback is set, call it once and clear it; return 1 (delete) if state == 2.

### EffectCore (0x610 bytes)
Layout in `effect.rs` header.  Key points:
* `+0x188..0x194` four *add-time* scalars (default 1/30 s): `sysSetAddTime(f, mask)` mask bit0→vibration, bit1→models/paths/gunya/barin,
  bit2→lights/cameras, bit3→hit volumes.  All animation inside an effect advances by `scalar` per `Continue` call, i.e. effect time is
  frame-driven at 30 Hz independent of `FpPrim::GetFrameSpeed`.
* Resource tables (all fixed size, filled by VSM system calls, released by `Cleanup`, 0x00300... 2.6 KB):
  EffectModel[40] (0x198), CustomModel[16] (0x238), EffectCamera[10] (0x278) + current camera (0x2a0), EffectSprite[10] (0x2a4),
  motion records[20] (0x2cc: {side,modelIdx,flag,flag,Motion*}), HitCylinder (0x36c), HitShot (0x370), EffectLight[10] (0x374),
  EffSeCtrl[10] (0x39c: Sdrv handle, loop state), EffectBlur[3] (0x448), CPathControl[50] (0x454), CPath[20] (0x51c),
  EffectGunya[3] (0x56c), EffectBarin (0x578), LineBlur[3] (0x57c), CVibe[5] (0x588), FpPrimInfo[10] (0x5b0 → `PutiPrim*` created by `fef*`),
  StreamBGM (0x600).  `m_Fader__10EffectCore` (static list of `ModelFader`, updated by `UpdateFader` each frame).
* `Cleanup` also restores the camera fog (`SetFogParam(saved)`) and background colour saved in the ctor (0x438..0x448).
* Model lookups: `GetGenModel(i)` / `GetTargetModel(i)` index the `tagModelSet` arrays (0x14-byte records) set by the caller;
  `GetModel(side, idx, 0|1, 0|1)` optionally returns the model's attached weapon models (`+0x52c/0x530`).
* `CreateWorkModel(n)` / `CloneWorkModel` instantiate `M[n]` (+ its `A[n]` motion) into the first free slot of the 40-entry table as an
  `EffectModel`; `CreateCustomModel` instantiates a `BBPLineModel` from `P[n]` and `AddCustom`s it to a work model.
* `LoadSe(n)`/`PlaySe`/`UnloadSe`: sound banks (`1` sections) loaded through `Sdrv::AutoLoad`, up to 10 per effect; `InitSysSE` preloads
  system sound handles.

### VEC thread (0x254 bytes) and scheduler
See `vsm.rs` header and `effect_format.md` §2.  Per frame (`EffectCore::Continue`): start idle threads → `AddTimeAll` → for each thread with
state running/yielded: `UpdateFader`, `DecodeVSM` (runs until yield/wait/end) → remove state-3 threads → if no live thread: set
`flags&3 = 1`, `Cleanup()`.  `fork` creates a child thread (copy of the parent's whole 40000-byte data segment, own stack area starting at
bp = 20000, thread id from the next instruction); `exit`/`killthr id`/`waitthr id` manage them.

## 3. Resource classes driven by system calls
* `EffectModel` (SSH1 model + motion; `ExModel` subclass 0x5b0 B): local matrix at +0x560 (`SetTrans`/`SetRot`/`SetMatrix`), optional parent model at +0x518
  (matrix chaining, `UnChain`), custom list +0x514, `tagEMFlag` +0x5a8, `TranseCallBack` applies the model's root-translation motion in the
  effect's space, `SetEffectTestReg` patches GS test registers for alpha-test materials, `MotionEndCallBack` releases a `mdlWaitMotion` wait.
* `EffectCamera` (+`EffectCameraMotion`): see `effect_format.md` §3; `LookAt` writes the GsxCamera, `SetVibratePower(amp,freq...)`/`GetVibPower` implement
  camera shake, box cameras follow a hit box (`GetBoxPos/Inter`), vector cameras interpolate between two FVectors (`GetVecPos/Inter`).
* `EffectLight`/`EffectLightMotion`: §4 there.
* `EffectSprite` (0x90 B): 2D quad (4 FVector + int) -> `GetPacket(i)`.
* `EffectBlur` (0x70 B) full-screen/zoom blur sprite (`Create`, `SetAlpha`, `getPacket`), `LineBlur` (radial line blur: `Create`, `SetCenter(x,y)`,
  `SetPower(f)`, `SetBlurRect`, `ChangeLine`, `GetUV`) — also used standalone by `CBattle`.
* `EffectGunya` ("squishy" lattice deformation of a model: `Initialize`, `ClumpSt`, `AddRotKey`), `EffectBarin` ("barin"/free polygons: `AddPolygon(FreePol*)`, `PixelTo3D`).
* `HitShot` (projectile with `HitDynaKey` list, `IsAtEnd`, `AddTime(dt,speed)`) and `HitCylinder`: hit volumes tested by `hitIs*` system calls and by `EffectCore::HitEnd`.
* `LsdEffectServer` (LSD cutscene track handler for effect tracks: `Open/Read/Event/Close`, `CheckData(_LSDTrackHdr*)`) — static handler at 0x00421e40.

## 4. VSM opcodes
Table in `vsm.rs` header (all 63 verified against 1.4 M instructions in the retail data).

## 5. Other classes
Summaries and layouts: `Puti.md`, `Fp.md`, `BgEffect.md`, `Misc.md` (this directory).

## 6. Open questions
* The `EffectCodeFunc` / `SpecialEffectCode` pair (0x0032fb10, 0x00331960, 82 KB) interprets *battle effect tables* (`EFFTBL`) — it sits next to the effect classes but belongs to the battle system (section H).
* Exact meaning of several `sys*` handlers' `kind` (context) values beyond 0/1/2 — none observed.
* Names of individual effect files: they are addressed by PKFINFO hash; the list of names has to come from script data (section E/G/H).

## 7. Rendering bridge (2026-10-09, `sh2_gfx::effects::{scene,render}`, `sh2_battle::effects_bridge`)
The syscall families are implemented in `scene.rs` (`FxScene::syscall`) following `decomp/E/VecHandlers.c`; facts found while doing so: `EffectCamera::LookAt` (0x003080b0) uses key vector 0 as the
look-at point (`GetInter`) and vector 1 (+0x10) as the eye (`motion.rs` calls them `pos` / `target`: swapped); a camera whose `EFCM` header byte 10 & 3 == 1 is relative to the model it was played on
(`camPlay(h, kind, idx)`); `sprCreate` takes three corner vectors (screen pixels), `sprShow(h, on, layer)` with layers < 5 below the effect models (OT 5 / 9); `bfdSetMode(mode 2|3, secs, colour)` = `BtlFader`
fade in / out; `pphCreate(capacity, life frames)`, `pphAddPath(h, pos, dir)` (dir = half width), colour / ST keys in frames / 30 s; `pgrCreate` + `polCreate3D|BB` quads with `polSetVertex(w, h)` = size, `polSetSt(i, u, v)`,
`polSetColor(i, rgba)`; `chrCreateMotion(side, idx, standalone index)` + `chrSetMotion(side, idx, name)` play an effect-owned `A` motion on a battle character; `mdlAttach(h, kind, idx, frame)` chains to a named frame
(world position of the joint, rotation of the animation, not the bone's bind orientation).  Counts of calls per family over the 253 JP effects: `notes/integration/battle.md` ("Second pass").
