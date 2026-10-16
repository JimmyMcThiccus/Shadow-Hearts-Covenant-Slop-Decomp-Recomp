# Round 6 FX3 (effects + renderer), 2026-10-15

## Status (2026-10-15, second batch after commit da98c3d)
`cargo check --workspace --all-targets` clean; `cargo test -p sh2_gfx -p sh2_formats` green (sh2_gfx lib 182; `bgfx_corpus_us` now has two
tests, maps and battle stages, both asserting **0 unsupported records**: maps 3558 records, stages incl. BBG 051 / 062 / 097).  Ghidra
(SLUS_210.41 on :8192) used under `locks/ghidra.lock`, released, left on SLUS_210.41.  No processes left running.
1. **209 variant 0** (WE_01_U slot 15) ported (`storm209.rs` `StormV0`, `CalculateFunc` 0x002e3920 and its children): a one-shot ball-lightning
   sequence on a millisecond clock around `(0, -15, 0)` -- dim ball, strikes from the ball upwards from 0.5 s (strike table 500..5300 ms), at
   1.9 s the ball grows with three sparks and the `FpFlare` glow, flickers until 5.5 s, shrinks, rises 100 units at 5.9 s, then the
   `FpRetailLenz6B` sparkles (70, falling, 1 s in / 1 s out) fade until 8.6 s and the prim hides for good.  The six arcs and the full-screen
   flash prim are created hidden and only the prim's own `+0x3c(1)` (0x002e09a0) would show them, which nothing calls: kept behind
   `StormV0::all_shown` (false).  Window: `screens/r6_fx3/we01_storm_sheet.png` (`--view-map WE_01_U --cam 72.3,-20,5.1,0,-15,0`, shots at
   30 / 75 / 120 / 195 / 230 frames: loading, ball + strike, ball, strike, grown ball with sparks + flare).  Ghidra lost part of the ball's
   part chain: all ten ball parts share scale and position.
2. **202 `FpBlackHole`** (BBG 062) ported from the US rewrite (`blackhole202.rs`; module notes list every address): the 250-part smoke spiral
   (`RotX(60) RotZ(angle) (r, 0, h)`, US `FuncPos` / `SetPacket` culling), seven lightning rings (`FpObjectThunder` subclass `0x2c1dd0`: closed
   loops at height 900 with a bouncing radius walk, drawn with `thunder.rs` strips via the new `Thunder::set_nodes`), the area smoke (JP
   `FpAreaSmoke` with the US arguments) and the strikes of the retail `FpObjectTnderBH2` (`0x2c1050`: every `20 (0.5 + rand)` frames from a
   visible rim point outwards or from the sky in front of the camera, revealed over 2.45 frames).  Window: `screens/r6_fx3/bbg062_sheet.png`
   (`SH2_BATTLE_DEMO=2 SH2_BATTLE_BG=62`): the black sky became a grey storm vortex; `bbg062_cpu_outside.png` (new dev tool
   `sh2_gfx/examples/bgfx_snap.rs`, CPU splat of the quads, untextured) shows the funnel with the ring on top from outside.
   Not ported: `FpRetailBolt`'s branch tables (`FUN_002bc420`, one 20-node bolt instead), the stage light flicker during strikes
   (`FUN_002bdfe0`), the hole's one-corner flash.  Not compared with a live capture (no save state at BBG 062): the near sprites veil the
   fighters a little when the battle camera sits inside the vortex, which the PS2 (no near clip for sprites) should do too.
3. `bgfx_corpus_us` sets the US region (the 204 mode-2 waterfall of BBG 097 was "unsupported" only because the test ran with JP rules).
4. Thunder API: `Thunder::set_nodes` (explicit polyline), `Thunder::truncated` (a growing bolt).

## Status (2026-10-15, first batch)
`cargo check --workspace --all-targets` clean; `cargo test -p sh2_gfx -p sh2_formats` green (sh2_gfx lib 179 incl. the new `script_torch`,
`retail_torch_and_field_attach`, `storm209::*`; `bgfx_corpus_us`: unsupported `{209: 1}` (was `{209: 3}`)).  Coverage: `run_all.sh run lsd --fresh
--jobs 4` **166 / 166 ok** (was 164 / 2 stub), `run_all.sh run fx --fresh --jobs 4` **306 / 306 ok** (was 304 / 2 stub).  Ghidra (SLUS_210.41 on
:8192, lock taken after FS2 released it, released again, left on SLUS_210.41).  No processes left running.  Screens: `screens/r6_fx3/`.
1. **N094 / N100B** (the last 2 lsd stubs):
   * the "empty name" was a port bug, not a retail lookup: the tracks do `strStrCopy(var, "Smg_a")` then `lsdGetModel(var)`, and the port's
     `strStrCopy` / `strStrNCopy` (2600 / 2601) were no-ops.  Now `strcpy` / `memcpy + NUL` into the VM data segment (`program.rs`, JP
     0x00323f40 / 0x00323f90).  N094 / N100B now look up `Smg_a .. Smg_f` / `Shouki_b`, all scene models.
   * `fefRetail3010` = **fefCreateTorch(pos, col1, col2, col3, size, &handle)** (US 0x0035d990 -> `new FpTorch` + `FpTorch::CreateFromParam`
     0x002a1850): colours arrive as 0..255 float vectors, `(u32) f & 0xff` bytes, x 0.502 -> `FpTorch::Create`.  `BgFx::from_torch` (bgfx.rs) +
     scene 3010 branch; drawn like every `fef*` particle.  `screens/r6_fx3/n094b/LSD_N094.LSD_t2850.00.png`: the monster's jaw burns (torch +
     smoke at `JAW0`).  `syscall_name` now also names the 17 retail ids (`us_func`).
2. **`fldAttachBG2`** (SMROOM / SMROOM2, map SM_07_U): the handler was already there (`Parent::Named`); what was missing is the field's model
   table.  `FindFieldModel(a, b)` (US 0x00342450, JP 0x0030bfe0, disassembled): walks `CField::GetBGModel(i)` over the `CFieldBG` models (MPS
   `MODEL` records of kind 0 / 1 / 2, file order) and returns the `b`-th whose type (`CFieldModel +0x98` JP / `+0xa8` US, `SetModelType`:
   kind 0 -> 1, kind 1 -> 2, kind 2 -> 0) is 1 when `a == 0`, else 0.  So `a == 0` counts kind-0 records, any other `a` kind-2 ones.
   * `scene::field_model_name(a, b)` (`"fld:0:b"` / `"fld:1:b"`), `FxActor::from_model_rest(model, world)` (rest pose frames, same convention
     as `render::fx_actor_of`).
   * Field hook (FS's `sh2_field/src/bevy.rs`, requests.md "Round 6 FX3"): `LoadedFieldMap::fx_models` filled in
     `spawn_field_map_bytes_with`, copied into `FxRunner::named_models` by `load_requested_map`.  SM_07_U: `fld:0:0` = `SM_07_U` (frames ROOT,
     root2, **conpane**, DOORr1, DOORr2), `fld:0:1` = `daiza`; SMROOM attaches `sm_01` to `conpane`, `sm_02` to ROOT.
   * Coverage harness (QA's `coverage/fx.rs`, 3 lines): field effects get the `fld:` names.  Not checked in a window (no quick way to start in
     SM_07_U; verified headless: no ignored ids, the parent resolves).
   * `fldAttachBG` (2302: `+0x518` reference frame) and `fldAttachBG2` (2303: `chainModel`) are treated the same (the model follows the frame).
3. **209 `FpRetailStorm209`** (`effects/storm209.rs`): variant selection decoded (`Create` 0x002e3150, `InitFpFlag` 0x002a5fa0, base ctor
   0x002a5b20: `+0x54` layer 10, `+0x58` 1; flag byte 2 bit 0x80 -> vtable +0x30 = `+0x58 = 0`).  WE_01_U: slot 15 (`0x210a0000`) = variant 0,
   slots 18 / 19 (`0x218a0000`) = **variant 1, ported**: the Tesla orb (`FpFlare` at (-28.3, -36.5, -69), colour `30 6c a8 80`, size 70 x 0.73),
   3 spark bolts re-aimed every frame (`FpObjectRetailStorm209B::CalculateFunc` 0x002e62d0: `SetPos(orb, orb + 20 (0.5 - rand))`,
   `ChangeForm(1)`), 5 green 30-node arcs and 2 red ones without depth test at the `CreateObjects` literals, `ChangeForm(0.8)` per frame; uses
   `thunder.rs` (`FpThunder` now has a consumer).  `screens/r6_fx3/we01_cam0.png` / `we01_cam0_zoom.png` (`--view-map WE_01_U --cam-index 0`):
   green arcs along the coil, red arc on the pillar, blue sparks in the capsule.  Variant 0 (the scripted storm, 9 KB `CalculateFunc`) is not
   ported: `Storm209::new` returns `None`, the record stays in `unsupported`.
4. Sanity: `sh2_app --us --autoplay --boost 80` exit 0 (title, OP_00_U, world map, AP_00_U / AP_02_U, battle menu, ring, victory, menu tour;
   0 panics, 0 slab errors): `screens/r6_fx3/sanity/` (+ `sheet.png`).

## Open
* (done in the second batch, see the top) **202 `FpBlackHole`** (BBG 62):  The US `Create` (0x002be590) is a rewrite of the JP one: a new object `0x2c0700` (0x3e0
  bytes, 20 parts, `0x2c0d20(param)`), the hole `0x2bf250` (250 parts, as JP `FpObjectBlackHole`), **7** ring objects `0x2c1dd0` / `0x2c1ef0`
  (0x340 bytes; args radius 123 / 110 / 120 / 125 / 130 / 140 / 150, colours `0x04808080` / `0x02aa787d` with the top byte 6 / 4 / 2, part counts
  0x17c..0xec), the `FpAreaSmoke` (`0x2c2a50` / `0x2c2c80`, same arguments as JP) and one `FpRetailBolt` (`0x2bc1d0`, Create `0x2bd690`:
  (0, -1000, 0) -> (0, -1000, 0), colours `0x3cffc896` / `0x1ec88264`, 20 nodes); prim fields `+0x90..+0xbc` as JP `+0x80..+0xac`, `+0xcc` =
  the record's first float.  JP `decomp/D/Fp.c` 14044..17103 covers the hole and the smoke; the ring objects and the new 0x3e0 object need the
  US decompile.  Estimate still ~1 day.
* 209 variant 0: done in the second batch.
* SMROOM not seen in a window.

## Files
`sh2_gfx/src/effects/{program,scene,bgfx,storm209,mod}.rs`; hooks: `sh2_field/src/bevy.rs` (FS), `sh2_app/examples/coverage/fx.rs` (QA).
