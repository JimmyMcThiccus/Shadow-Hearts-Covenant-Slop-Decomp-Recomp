# Effects pass E2 (round 4, 2026-10-10)

Scope: what E1 (`effects_e1.md`) left open: the retail `Fp*` background-effect classes, the cutscene path, stage lights per fighter, the real GS blend, the bng focal length, LineBlur, VU1 model effects.
Evidence images: `screens/effects4/e2/` (every PNG listed below was looked at).  Tests: `cargo test -p sh2_gfx -p sh2_script` green (140 sh2_gfx lib tests + corpus tests); `cargo check -p sh2_battle` builds.

## 1. The GS blend of the stage effects (E1's "ALPHA 0x54" claim was wrong)
`0x54` is the **PRIM** word of the effect packets (`0x302a4000_00008000` GIF tag: PRIM = TRISTRIP | TME | ABE = 0x54), not an ALPHA register.  The real registers come from the `PutiObject`
constructor (`decomp/D/Puti.c` 0x0025cb..): `ALPHA_1 = 0x48` = `(Cs - 0) * As + Cd` (`Cs*As + Cd`, additive weighted by the source alpha), `TEST_1 = 0x73001` (ATE, ATST NEVER, AFAIL RGB_ONLY: colour
written, never Z; **ZTST GREATER = depth tested**).  `FpPrim::setZtest(0)` switches it to `0x33001` (ZTST ALWAYS, no depth test).  `FpTorch / FpCandle / FpFlare` do not call `SetRegAlpha`, so they are
`0x48`; `FpFog / FpSmoke / FpFunsui / ...` call `SetRegAlpha(0x44)` = `(Cs - Cd) * As + Cd`.  `Sh2Blend::Add` (SrcAlpha, One) already is `0x48` -- the stage effects were right, the justification was not.
Texture side: `SetWhiteTex` (US 0x002a3260) overwrites the **RGB of every CLUT entry with 0xff and keeps the CLUT alpha** (0 for index 0, 0x80 elsewhere in `CMNEFF.DAT`), so the `0x44` classes (smoke, fog)
sample *white with the CLUT alpha*, not "white with the grey ramp as alpha" (E1's guess): `bgfx_render::cmn_rgba` / `CmnTex::a` now do exactly that.

## 2. Ported classes (`sh2_gfx/src/effects/{bgfx_more,lenz}.rs`, wired in `bgfx.rs`)
| type | class | status |
|---|---|---|
| 5 | `FpFog` (US 0x0029b560.., JP decomp `Fp.c`) | real: `count` sprites on a ring, drifting, fade by life and by distance to the camera (`FpObjectFog::SetPacket` 0x00299e10); verified in `AI_04_U` (`ai_04_u_fogcam.png`) |
| 6 | `FpRetailLenz6` (US 0x002dd520..) | real: one star-glint sprite (`CMNEFF` 15) pulled `pull` units towards the camera, alpha cycle 100 / 150 / 500 / 0 / 500 ms; verified in `AI_00_U` (`ai_00_u_lenz6_peak.png`) |
| 200 | `FpLenzFlare` (US 0x002b0fe0 / 0x002b01d0, `FpSun` 0x002af1e0, `FpObjectSunFlare`, `FpObjectLenzFlare`, `FpObjectLenz`) | real except mode 1, the hard coded occluders of modes 8 / 10 and the `FpObjectRetailLenzSub` per-map alpha scripts: world glow objects (2-3 per mode), the 300 px glare on the sun's screen position, 17 ghosts on the line through the screen centre, edge fade windows, screen-space overlay drawn without depth test; verified `ca_00_u_sun_offaxis.png` (field) and `battle84/bt_01_intro.png` (BBG 84, mode 9) |
| 207 | `FpRetailMote207` (US 0x002cfbe0 .. 0x002d9020) | real: falling snow / dust motes (PE_00 / 01 / 02, BBG 030, N049 / N050): 69 hard coded volumes (`mote207.rs` tables, **extracted by emulating the 0x84dc byte `CreateObjects` with `tools/E2/mipsemu.py`** because the decompiler times out), fall + sideways jitter + landing fade, projected-width culling (< 2.5 px / > 31 px); verified `pe_00_n_motes.png` |
| 206 | `FpRetailRain206` heavy variant (US 0x002c99b0 .. 0x002cb270) | real except the depth test of the streaks (engine Z table), the splash object, the lightning strobe keyed on the map number and the thunder sounds: 1000 slanted screen-space streaks + the 3 full-screen tints (additive veil, black 56 / 20); verified `sa_01_n_rain.png` |
| 1-4 | torch / candle / flare / smoke | E1; now also in cutscene maps (below); **fixed a NaN alpha** in `Flame` (a torch with `period == 0` divided 0 / 0, found by the new corpus test on `GB_01_U`) |
Not ported (still `BgFx::unsupported`, 11 records of the whole US disc: `{200 (mode 1): 1, 201: 1, 204: 1, 208: 3, 209: 3}`): 201 `FpFunsui` (FI_01_U), 202 `FpBlackHole` (BBG 62, not in the field list), 204 `FpTaki` (BBG 51 / 97, IN_03_U), 208 drift (FU_15_U, FU_17_A / U: world-space crinkle-cloud particles, hard coded per map; the `FpObjectRetailDrift208B` init / update were read, the non-B objects of variant 1 were not), 209 storm (WE_01_U: 21 `FpThunder` bolts + flares + lens flare + tints + 17 child prims), 210 (creates nothing in retail: `CreateFpEffect` accepts it and does nothing).
`sh2_gfx/tests/bgfx_corpus_us.rs`: every effect record of all 1105 US maps steps 120 frames and yields finite quads (3549 supported records).

Record layouts found (US disc): type 5 / 6 do **not** use the torch header (`FVector pos` with the flag word in `w`): word 0 is the flag word, `+0x10` flags2, type 5 payload at `+0x20`
(`pos, rgba, tilt x/y, vel, size x/y, period (int), count (int), radius, height, speed randomisation`), type 6 at `+0x10` (`pos, rgba, size, pull`).  Type 200: `+0x00 pos`, `+0x0c` flags, `+0x1c` mode (f32).
206 / 207 / 208 records are a single `f32` variant (`CreateObjects(variant)`); the bytes after the real parameter block in the dumps are the next SBD chunk (`VERT EX`), not parameters.
`sbd_scan <disc> --dump <type>` prints the records of a type for every map (the last lines of each dump are the next SBD chunk, not parameters).

## 3. Cutscene path
`sh2_field::cutscene_plugin::show_map` now spawns the map's SBD `EFFECT` records (`BgFx`) with the map (hook: `MapInstance::fx`, shown / hidden / despawned with the map root,
`Propagate(layers())`); `CmnEffTextures` (resource, loaded once by `BgFxPlugin`) gives the common textures without disc access.  `CutscenePlugin` adds `BgFxPlugin`.  Scan: `cargo run -p sh2_field --example lsd_fx_scan -- --us [type..]`
(candles / torches / flares in N003-N005, N010, N022, N024, N028, N032, N036, N037, N049-N066; 207 in N049 / N050, 206 in N010, 200 in N065 / N066).  Verified in `N004` (Ap_02_u, 14 candles, 8 flares): `cut/LSD_N004.LSD_t0500.00.png`.
Field torches / candles / flares in a real field run were already shown by E1's hook (`load_requested_map`); `SH2_FX_FREEZE=<ticks>` (+ `SH2_FX_DEBUG=1`) freezes the effects after N ticks for deterministic shots, the viewer
camera is chosen with `--cam x,y,z,tx,ty,tz` (PS2 coordinates).

## 4. Stage lights per fighter
`stage::light_fighters` evaluates `LightControl::light_matrix` at every `BattleModel`'s waist (feet + 15 units, the stage default subject was `(0, -15, -6)`) and attaches a
`sh2_gfx::bevy::model::ModelLightOverride` to the fighter's holder and its weapons; `apply_model_light_overrides` gives each lit draw a private material copy with `Sh2Material::own_light` (the global
`sync_material_globals` skips those).  Test `stage::tests::point_light_differs_per_fighter`.  The global scene light (arena centre) is still published for everything else (shadows, shop, ...).

## 5. bng focal length (E1 guessed 512)
`EffectBarin::EffectBarin` (JP 0x00321e20) copies the camera's view-screen matrix (`GsxCamera::GetViewMatrix` = camera + 0x2c0, `sceVu0ViewScreenMatrix(scrz, ax, ay, cx, cy ..)`) and derives the pixel -> view
mapping from it: `x = (px - 256) / (ax * scrz)`, `y = (py - 224) / (ay * scrz)` with `SetViewMatrix(scrz, 0.8, 0.93333334)` (BtlCamera / EffectCamera / JRing; `EffectCamera::LookAt` calls `SetScreenZ(key.fov)`).
`bng::Focal::from_scrz` replaces `FOCAL = 512`; `FxScene::current_scrz()` = playing effect camera fov, else `default_scrz` (512, the host may set it from the battle camera).  The same matrix projects the shards back
(`FreePol::GetPacket(this + 0x5a0)`), so at rest the picture is unchanged; only the release speed (view units) and perspective depend on it.  The grey level `(x + 0.8) * 128` was re-derived from
`FreePol::GetPacket` (JP 0x00320ae0): the normal `(0,0,-1)` goes through the shard matrix, the `(0,-1,0,0)`-row matrix (-> `(-y, y, z)`), is normalised and multiplied by the matrix (right = 1,1,1,1; pos = 0.8) -- confirmed.
Side faces of the shards (the `+0x0c` thickness strip) are still not drawn.
**Request for U4 (camera.rs):** `CamPose::fov_y` uses `tan(fov_y / 2) = 224 / scrz`; the engine's `SetViewMatrix(scrz, 0.8, 0.9333)` gives `tan(fov_y / 2) = 224 / (0.9333 * scrz) = 240 / scrz` (the field camera of
`renderer.md` already uses `0.75 * angle` = 240 / scrz).  The battle camera is 7 % too narrow vertically if `fov_scale` is `scrz`.

## 6. LineBlur / `fef*` / `cus*`
Real host run of all 248 US effects (900 ticks, `sh2_battle/examples/fx_ignored_scan.rs`, `FxScene::ignored_ids`): **no effect calls `blrCreateLine` (2107..2112) or any `fefCreate*` / `fefSet*` (3000..3010)**, so LineBlur
and the fef creation calls stay accepted-and-ignored.  The accepted-but-not-drawn calls that *are* used: `sbgCreate / Play / GetReady` (3300 / 3301 / 3305, 36 effects: sound BG, nothing to draw) and
**`cusCreate` / `cusShow` (1000 / 1001, effects 9, 10, 11, 17, 33, 34, 90, 95, 98, 100, 149, 219)** = `EffectCore::CreateCustomModel` -> a `BBPLineModel` (line / ribbon model from the effect package's
`P` = `BBPF` section, attached to a frame of an effect model with `EffectModel::AddCustom`): **not drawn** -- the largest visible gap left in the effect host.
(The stub corpus test `sh2_script/tests/vsm_corpus_us.rs` under-reports calls: effects that wait on host results never reach them; the real-host scan above is the one to trust.  Every effect also carries
a `sys` wrapper for all ids, so a static count of `sys` instructions is meaningless.)

## 7. VU1 model effects (analysis only)
`SkinAtomicPack2::setSpecialEffect` (JP 0x0024fd40) selects the microcode: id 0 = `_dma_61` (0x3e3e00), 1 = `_dma_154` (0x3e71b0), 2 = `_dma_170` (0x3e7c90), 3 = `_dma_186` (0x3e88b0); 1-3 set `PRIM |= 0x220`
(FGE + CTXT 2: the second GS context) and ids 2 / 3 bind the `ExpansionTexture` (`setTexture` 0x00252340).  `_dma_154` disassembled (`tools/B/vudis.py SLPM_602.19 3E71B0`): the normal skin + light pass
(palette matrices, `MAX 0`, light matrix `vf2..14`, ambient `vf6`, `FTOI0` colour) followed by a **second pass that builds ST from the reflection vector**
(`n * (n . c) - c` with `c` = data qword 34, `ST = 0.5 * r + 0.5`) = sphere-map environment mapping from the `ExpansionTexture`.  Census (US, 195 k atomics): id 1 on 330 atomics -- gold / jewellery / crowns
/ bells / guns (`gold`, `kazari`, `jewel`, `oukan`, `kane01`, `gun3`, `CROSS`, `bomb` in CHR 185 / 249 / 251 / 494, FIELD MODEL 068, LSD N006-N009, N056, N070 ...), id 2 on 28 (wings `ue`, `hane`: CHR 512, effect 221), id 3 on 117 (mirror frames `Kaga*`, `Kagami`, `DOOR`: the MS_* mirror rooms, IF_11 / 16 / 17).
Disassembled `_dma_170` / `_dma_186`: both skin programs end in a second pass whose ST are **screen space coordinates into the frame-buffer copy held by the `ExpansionTexture`** (constants `0.875 = 448 / 512`,
`1 / 512`, `1 / 448`, `LOI 1792 / 1824` = the GS screen origin): id 2 offsets the lookup by the view-space normal (`SUB.xyz vf24, vf28, vf24`, scaled by -1 / 0.5) = a **refraction / distortion** of what is behind
the wings, id 3 maps the screen position directly (the glass / mirror panes show the frame buffer, plus the plain program).  There is no outline program among the three; the "outline" of the old renderer note
does not exist as a special effect.  **Not implemented**: needs the `ExpansionTexture` content, the qword-34 constant (set in `SkinAtomicPack2::getPacket`)
and the context-2 blend; the shiny-metal highlight is missing on those atomics.  `TPL` / `TPA` (`Atomic::set2PathColor / Alpha`, JP 0x00242810 / 0x00242890): sets the atomic's constant colour vector (`+0x320`,
VU1 data word 12, w = atomic alpha * model alpha), the "second pass" bit `+0x2b2 & 1` and the translucent flag `+0x2b1` (value < 0x80); only effect-model motions carry them (268); `ModelInstance::two_path` still
only records the values.
