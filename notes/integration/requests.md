# Change requests for files owned by other agents

(Integration agent did not edit these; apply when convenient.)

1. `port/crates/sh2_app/src/viewer.rs:323` -- `TextFont { font_size: 16.0, ..default() }` does not compile on Bevy 0.19.1
   (`font_size` is `bevy::text::FontSize`): use `FontSize::Px(16.0)`.
2. `sh2_app`, `sh2_gfx::renderer`, any new `bevy.rs`/`plugin.rs`: the workspace glam is now **0.32** (matches Bevy's
   `bevy::math`). Use `glam::Vec3`/`Mat4` from the workspace crate or `bevy::math::*` interchangeably.
3. `sh2_core` now has a default `bevy` feature. Crates that use `sh2_core::{app,ssh_sys::SshSysPlugin,pause::CPause}` as Bevy
   resources need `sh2_core = { workspace = true, features = ["bevy"] }` (done for sh2_app, sh2_gfx and sh2_field).

## Cut scenes / movies (cutscene agent, 2026-10-09)

Applied (small, additive edits in files owned by others; all compile, `cargo check --workspace` clean):

4. `sh2_field/src/plugin.rs` `FieldPlugin::build`: three lines inside `if rendering { .. }` add `cutscene_plugin::CutscenePlugin`.  The plugin tags the
   `FieldCamera3d` itself and bridges `FieldRuntime::st.mces` (state 1 -> 5 while the LSD plays -> 0 / 3), so `host.rs` is untouched.
   `SH2_CUTSCENE=off` keeps the old placeholder wait, `SH2_CUTSCENE_SPEED=<x>` scales the cut-scene / movie clock (the autoplay already sets `SH2_CUTSCENE=off`).
5. `sh2_menu/src/plugin.rs` (JP demo title): `title_tick` gets `Commands` + `MovieStatus/MovieRequest`; `TitleCmd::PlayMovie` inserts a `MovieRequest`,
   `PauseExitMovie` removes it, `lsd_idle` = "no request", `lsd_started` = first frame shown; `PlayMusic` now posts `AudioRequest::PlayTitleBgm`;
   `MenuPlugin` adds `MoviePlugin` (rendering only).  `sh2_menu/Cargo.toml` depends on `sh2_script` (LSD parser).
6. `sh2_gfx`: `ipu/mpeg2.rs` (new), `model/skeleton.rs` `Skeleton::extras` (per-bone `extraMat` rotation, used by lip sync), `sh2_audio`:
   `AudioRequest::{PlayPcms, PausePcms, StopPcms}` + `AudioRuntime::pcms_position`, `Synth::stream_mut_ref`.
   `sh2_field/src/bevy.rs`: `spawn_field_map_bytes` (map from memory = the `MPS ` track of an LSD).

Not applied (retail title, `sh2_menu/src/title_retail_plugin.rs`): its placeholder movie clock (`MOVIE_FRAMES`, `Cmd::StartMovie`) should use the same hook:
`Effect::PlayMovie` on `Cmd::StartMovie` -> `commands.insert_resource(MovieRequest::new("OPENING/DEMO.LSD"))` (US demo.lsd = 640x448, 76 MB),
`lsd_idle` = `movie_req.is_none()`, `lsd_started` = `MovieStatus` is Playing / over, `Cmd::StopMovie` -> `remove_resource::<MovieRequest>()`.

## Battle agent (2026-10-10)
8. `sh2_field/src/plugin.rs` (applied): the encounter `fd` pair was `[SetFieldData(6), SetFieldData(7)]` = `(w0, bgm)`; the original stores selector 6 = BGM, 7 = battle background.
   Now `[fd7, fd6]`.  `sh2_field/examples/monsets.rs` also prints the MONSET `bg` / `bgm` words.
9. RingCustom for battle needs no resource: `sh2_battle::plugin::{ring_custom, ring_settings}` read the `BTL0` record bytes `0x60..0x77` that `sh2_field::cmd_ring` writes.

## Menu / save agent (2026-10-10)

Not applied (files of other agents); all new APIs below already exist in `sh2_menu` / `sh2_field`.

### R1. Battle: use the real Judgement-Ring customisation (`sh2_battle/src/plugin.rs`)

`plugin.rs:1041-1063` (`ring_custom`, `ring_settings`, `RING_OFF_*`) read bytes `0x60..0x77` of the party record -- that was the first guess of the menu page.  The real
fields (decompiled `CmdPC::CustomJudgmentRing`, `CreateJudgmentRing`, `GetRestRingItem`) are at `+0x58..0x64` (demo) / `+0x5c..0x68` (**retail**; there `+0x68 = 0xff`
and `+0x6c` is a u32, so the old reader returns a garbage custom table on retail saves).  Replace the three helpers by one call:

```rust
// Phase::Attack, where the ring is created
let weapon_ring: &[u8] = pc_weapon_record_bytes(0x28..0x32);      // WPN_ record of the equipped weapon (the weapon's own narrowing per area)
let br = sh2_menu::ringcustom::battle_ring(session, pc, weapon_ring);
//   br.hits       -> number of PC_J areas (auto ring: 1)           -- instead of `hits_per_attack` from PCParam when the ring is built
//   br.ring_type  -> JRing +0x41 bits 2-3 (0 normal .. 3 gamble; auto ring = 1)
//   br.custom     -> Option<[u8; 20]>: `ring.custom_data = Some(JrCustom { raw })` + `ring.custom_convert()`
let areas = db.0.ring_areas(pc as usize, br.hits as usize);
let ring = RingRun::start_areas_custom(&areas, 1.6, seed, br.custom);
```

`sh2_menu::ringcustom::{ring_state, store_ring_state, rest, stock}` give the same state to any other consumer.

### R2. sh2_core: honour the Key Customize page (`sh2_core/src/game.rs`)

`sample_pad` applies `default_buttons()` only.  The menu page now edits the four u16 entries at `MENU+0x26c` (`GameSession.save.menu`).  Add a resource and use it:

```rust
#[derive(Resource, Default, Clone, Copy)] pub struct ButtonAssign(pub Option<[u16; 4]>);
pub fn sample_pad(.., assign: Res<ButtonAssign>, ..) { pad.feed(apply_button_assign(keyboard_to_pad(&keys), assign.0.unwrap_or_else(default_buttons)) | inj.raw); }
```

`sh2_menu::plugin::apply_system_options` (runs every frame) will then only need `assign.0 = Some(session.save.menu.button_entries())` -- say so and the two-line
`MenuSave::button_entries()` is added on the menu side.  (Vibration has no consumer: logged only; sound out is applied through
`sh2_audio::AudioRequest::SetSoundOut`.)

### R3. Battle: statistics the Score / Library pages read (`sh2_battle::bridge` / `plugin`)

* encounter start: `session.save.btl.set_monster_met(monster_id)` for every enemy of the set (library "met" bit, demo `+0xdaf`, retail `+0xf43`);
  victory: `set_monster_defeated(id)` (`+0xdcf` / `+0xf63`); the two-bit knowledge array (`monster_knowledge`) is read-only for now.
* `MENU+0x340+i` / `btl.set_combo_flags` for the combination techniques (Combo Magic page).
* Score (`sh2_menu::score`, retail only): per chapter block at `BTL0+0x14bc + chapter*0x400` (`retail` raw block), u32 words: `[0]` battles, `[1]` ran away, `[2]` max hits
  (max), `[3]` total hits, `[5]` combo successes, `[6]` max damage (max), `[7]` complete victories, `[9]` shortcuts, `[10..17]` bonuses, `[0x11 + 9*pc + j]`
  per member (`j` 1 berserk, 2 unconscious, 3/5 ring total/success, 4/6 perfect, 7/8 combo ring); `MENU+0x2cc + chapter*0x10`: shop ring total / success.  Nothing in the
  port increments them yet; a loaded real save shows its real values.

### R4. Retail new game (`sh2_battle::bridge::init_new_game_retail`)

`GameSession::new_game` (retail) now creates the real default block (bag 1 = `BTL0+2`, flags, `+0xec0 = 4`) and applies the `SCEN` rows of kinds 5..=10 itself
(key items, obtained bit sets, misc flag words: `BtlSave::apply_scene_row`, validated against a real save).  The bridge still has to write kinds 1..=4 into the bag
arrays (it does, through `BtlSave::BAG_STRIDE * bag()`; the bag is 1 in retail now).  `init_pc` also fills the ability-slot rows (`BtlSave::init_pc_slots`).

### R5. Retail save compatibility notes for everyone touching `session.save.btl.data`

`BtlSave.data` stays the **demo-shaped working copy** (all existing `OFF_*` constants valid); the retail block lives next to it in `BtlSave.retail` and is refreshed by
`BtlSave::sync_to_retail` when a file is written (`SaveFile::to_bytes`).  Fields outside the shared set (key items >= 3, misc flag words, monster library bits, score
blocks, ability slots) are read / written through the `BtlSave` accessors, never through `data`.  See `notes/integration/save_retail.md`.


## Retail title / cut scenes round 2 (cutscene agent, 2026-10-10)

Nothing in files owned by others was edited.  Notes for the owners:

1. `sh2_field/src/cmd_option.rs` (in-game Option page) indexes `OPTION.MSD` text entries 10.. for the option choices; the **US** file has one entry less
   (`txt[9..11]` = Strong / Weak / OFF, `[12..14]` = Stereo / Mono / Dolby, `[21,22]` = Subtitles ON / OFF, `[23,24]` = Navi Map).  The retail title screen
   (`title_retail_plugin::load_extras`) uses the US indices; the in-game page shows shifted labels on `--us` unless it is told the region.
2. Subtitles: `LSDCaptionHandler::Event` shows captions only when `MENU+0x275 & 1 == 0` (US bit 0 of the option byte, written by the Options screens); the cut scene
   player honours it (`GameSession.save.menu`).
3. `GameSession::new_game` resets the `MENU` option bytes (`+0x274 / 0x275 / 0x278`); the retail title keeps what the player chose on its Options screen across
   New Game.  A save / load round trip of those bytes is the menu owner's.
4. Theater unlock flags live in `TitleShared.common[2..]` (system file common block, `SaveManager::system.common`); `title_retail_plugin::{unlock_theater_scene,
   persist_common}` set / write them when a scene plays in the field (hook in `cutscene_plugin::field_bridge`).  `SH2_THEATER_UNLOCK=all` unlocks every scene for testing.
5. `sh2_field/src/host.rs` still logs "MCES movie X is not played in this port (placeholder wait)" for scenes the cut scene bridge takes over: harmless, but the log
   line could be dropped.
6. For the battle owner: the attract battle (`sh2_field::cutscene_plugin::attract`) starts `BtlSocket` with `SysBtlParam { w0: 0, regdat_id: monster set, pc[..] }` and an
   empty return map, drives the menu with `PadInjection` (confirm taps while `BattleView::menu_open`, ring zone press) and ends with `SshSys::request_title()` after
   `BattleReport::pending` / 2700 frames / a key.  The retail battle number (`BtlSocket+0x190`, 77 / 6 / 28 / 42 / 89 / 73) is not mapped to a background id yet.

## Field systems agent (2026-10-10)

Nothing of the earlier requests fell into the field-systems files except item 8 (applied).  New requests for files of other agents:

### F1. Command menu: grey the Save row off a save point (`cmd_top.rs` / `cmd_page.rs` / `menu_overlay.rs`)  -- DONE 2026-10-10 (M1, `notes/integration/menu_m1.md` section 3: `InGameMenu::save_gate` set in the triangle hook, `Env::can_save()`)

The original opens the main menu with `CommandMenu(4, ChkSavePoint() >= 0)` (`CmdMenu +0x4a = 3` on a save point, `1` elsewhere): the Data entry's **Save** row is only usable
while the player stands on a save point (the Load row always is).  The field side already computes it: `FieldRuntime::st.menu_save_ok` is set when triangle opens the menu
(`plugin.rs`, `SimEvent::MenuRequest`; `points::sync_points` keeps `st.on_save_point` current).  What is missing is a consumer:

* add `pub save_ok: bool` to `cmd_page::Env` (set by `menu_overlay.rs` from `FieldRuntime::st.menu_save_ok` when it builds the `Env`; `true` for the title / script-opened save
  page `MenuReq::Save`, which always saves);
* `cmd_top.rs`, state `Data` (rows 24/25 demo, 26/27 retail): draw the Save row greyed and answer the circle with the buzzer when `!env.save_ok`.

### F2. `sh2_menu::bevy_ui` Bevy-UI layers cannot mirror or rotate images

Layers `< SPRITE_BASE` are drawn as `ImageNode`s of the quad's bounding box (`quad_bounds`), so flipped UVs / rotated quads silently draw upright.  The world map had to move to a
sprite layer (`worldmap_plugin::WM_SCENE`).  Either document this on `UiCanvas::begin` or make `quad_bounds` users fall back to a mesh when the UVs are flipped.

## Round 3 notes (cutscene agent)

1. **UI canvas stretch (menu / presenter owner)**: `bevy_ui::fit_ui_scale` scales the 512 x 448 canvas layers uniformly (pillarbox in a 4:3 window) while the 3D cameras fill the 4:3 viewport (7/6 pixel stretch).  Everything on `CanvasRoot` layers (field windows, in-game menus, cut scene captions / `DspImage`, battle HUD) is therefore narrower than the picture behind it.  Fix there: give the `CanvasRoot` nodes a `UiTransform { scale: (vp_w / (512 s), vp_h / (448 s)) }` (see `title_retail_plugin::retail_fit_presenter` / `movie::present_rect_logical` for the formula) instead of a uniform scale.  I only did it for my own full-screen nodes (title root, movie picture).
2. `sh2_audio`: added `AudioRequest::StopTitleBgm { fade_ms }` (the title stream lives in `title_play`, `StopBgm` only stops the field / battle slot, so the title music played on into the game).  Posted (500 ms) on `OnExit(Scene::Title)` by both title plugins.
3. Canvas layer ids: `layer::FADER` (4) and `menu_overlay::BRIGHT_LAYER` (6) are rewritten every frame by their owners; cut scene content uses 5 and 7 (`cutscene_plugin::{IMAGE_LAYER, CAPTION_LAYER}`).

## UI canvas stretch (menu owner, 2026-10-10) -- DONE in `sh2_menu::bevy_ui`, one hook left for sh2_battle

* `bevy_ui::fit_ui_scale` now stretches every `CanvasRoot` (512 x 448 virtual layers: field windows, captions, `DspImage`, battle HUD, fader layers) over the 4:3 viewport of the UI camera
  (`UiScale` = viewport height / 448, horizontal `UiTransform` scale = (viewport width / 512) / `UiScale`).  Bevy UI lays a root out in the **camera viewport**, which
  `sh2_gfx::bevy::screen` sets to the 4:3 rectangle, so `Val::Percent(100)` nodes (cine bars, `FaderNode`, movie / pause overlays) already cover the picture; nothing
  may offset them by the window's letterbox bars (`movie::fit_movie_node` did: fixed).  `title_retail_plugin::retail_fit_presenter` now centres / stretches the title root in the viewport too.
  New resource `bevy_ui::UiViewport { size }` (+ `per_unit()`, `to_virtual(p)`).  `SH2_UI_PROBE=1` draws a magenta canvas frame, a 100 x 100 yellow square and a cyan 100 % node frame
  to check the alignment; `SH2_WINDOW=WxH` sets the window size of `sh2_app` / `cutscene_view`.  Screens: `notes/integration/screens/ui_fit/`.
* **sh2_battle hook** (`plugin.rs::sync_battle_render`, "screen positions of the heads"): the head -> virtual conversion still assumes a uniform `UiScale` (`p / s - off`), which is
  now 7/6 off horizontally.  Replace the `ui_scale` / `off` arithmetic by the stretch:
  ```rust
  // vp: Res<sh2_menu::bevy_ui::UiViewport>;  p = camera.world_to_viewport(..) (logical px inside the 4:3 viewport)
  rt.screen[i] = vp.to_virtual(p);
  ```
* Caption note for the cutscene owner: N004's second caption line is wider than the 512 frame (starts at x = 72, ends past 512) at every window size, including 4:3 -- not caused by the stretch.

## E1 hooks (effects agent, 2026-10-10)
* `sh2_battle/src/plugin.rs`: two one-line hooks (already applied by E1): after `spawn_stage` in the stage setup, `stage::spawn_stage_extras(...)` (stage LIGHT chunk -> character scene light, EFFECT chunk -> background flames / flares / smoke) with `DespawnOnExit(Scene::Battle)` on the returned entities; and `.add_plugins(crate::stage::StagePlugin)` next to `EffectRenderPlugin`.
* `sh2_field` owner (field maps): the same background effects exist on field maps (`EFFECT` chunk of the MPS, 559 maps).  `sh2_gfx::effects::bgfx_render::spawn_bg_fx(commands, &Sh2Disc, &[BgFxRecord { slot, kind, param }], seed, filter)` draws them (types 1 torch, 2 candle, 3 flare, 4 smoke; others are reported by `BgFx::unsupported`); add `sh2_gfx::effects::bgfx_render::BgFxPlugin` and pass the enabled `EFFECT` records (`param` = bytes from the record's parameter offset on, at least 0x80).  `sh2_battle::stage::effect_records` shows the conversion from an SBD.

## T1 (Tarot Card, 2026-10-10) -- hooks I made in files owned by U4 / others, please keep them
* `hud.rs`: `HudTarot::xs` (explicit x centres of the card backs; empty = the old uniform row) and `HudTarot::hide_prompt` (no `(X):Confirm` while the ring slides in /
  after the pick), new `TarotStage::Help(String)` (bottom strip only: live `10j` / `10k` keep the strip after the card is gone).  The three `apply_demo` literals got `..Default::default()`.
* `ui.rs`: `MenuBuild::tarot_locked` (the `Tarot Card` root row is greyed and Confirm is ignored while a card is active or Lucia is sealed; the test literal got the field).
* `models.rs`: `Phase::Tarot` -> `begin_cast(false)` (generic cast pose; retail uses the tarot pose, `bState` 0x16, motion not identified) and `casting_phase`.
* Open for the HUD owner: the retail ring is 3D (nodes on a circle, cards face-on only near the front); the flat row is the previous agent's reading of live `10e`/`10f`.  The back
  colour rotates grey / beige / teal / purple per use (`TarotState::back`); `HudTarot` only has the purple back.  The Fool's x2 / x4 damage-number scale is applied in
  `plugin.rs::consume_events` (`HitText::scale *= param / 100`); if `hud_hits` ever caps the scale, lift the cap for this.
* **sh2_field hook (E1, applied)**: `sh2_field/src/bevy.rs` `load_requested_map` spawns `sh2_gfx::effects::bgfx_render::spawn_bg_fx(..)` from `parse_sbd_full(MPS).fx_records()` (entity gets `FieldMapRoot`, so it despawns with the map) and `FieldMapPlugin` adds `BgFxPlugin` (idempotent; the battle `StagePlugin` adds it too).  Cut scenes that spawn maps through `spawn_field_map_bytes` (`cutscene_plugin.rs`) do not get the effects yet: add the same three lines there if wanted (`parse_sbd_full(&raw)`).

## U4 (2026-10-10): victory motion hook for B1 (models.rs)
`models.rs` now gates the winners' `Act::Win` on `rt.win_pose` (0.7 s after the win camera, like retail `Phase15_Win` step 5) and reports `rt.win_playing` / `rt.win_done` (a model in `Act::Win`
alive / none left).  The win sequence builds the Battle Bonus panel when `win_done` is set (or the player confirms).  If the win motion is changed to loop or to hold the last frame,
keep setting `rt.win_done` when the first run of motion 0x33 ends (retail `pModel+0x510 == 2`), and keep the pose until the result screen closes.


## Round 4, menu / title / save (M1, 2026-10-10)

1. **Vibration sources** (sh2_field cutscene owner, sh2_battle owner): post `sh2_menu::vibration::VibrationRequest { strength: 0.0..=1.0, ms }` (a Bevy message) -- the option scaling and the forwarding to the gamepads are done.  Candidates: the LSD `StartVib / StopVib / FadeVib` ops (`cutscene_plugin::ScriptOut`; the LGDT `VIBE` blob sequences are not decoded yet), battle hits / critical hits, the field's `Vibrate` calls.
2. **Option consumers still missing** (battle owner / field owner): `MENU+0x274` bit 6 "battle cursor memory" (remember the last battle command), `MENU+0x275` bit 1 "Navi Map" (field navigation arrow).  Message speed is now read by the field message windows.
3. **F2 / field-systems**: the real `dataAccess` screen runs through your `FieldScreens`; `ScreenReq::Data { load, reopen_menu }` opens it (script-opened saves can use `FieldScreens::req` directly), `FieldScreens::data_outcome` tells how it ended.  The command menu's Save row gate is `InGameMenu::save_gate = Some(on_save_point)` (set where the triangle opens the menu).  `field_logic_tick` now keeps `menu_wait` while a screen is active.
4. **Saves**: retail saves are written to the port's own memory-card image (`<save dir>/mcd_sh2_port.ps2`); anything that reads loose `SH2-nnn` files from the save directory must go through `FileStorage` / `SaveStorage` (it now serves the port card, then loose files, then the emulator card).
5. **Dev runs** write to `<tmp>/sh2_port_dev_saves` (or `SH2_SAVE_DIR`), never to `~/Library/Application Support/sh2_port` unless `SH2_REAL_SAVES=1`; the flags that make a run a "dev run" are `sh2_menu::session::{DEV_ENV, DEV_ARGS}` -- add yours there.

## B1 (2026-10-10): Revenant height (72 vs 92 px) and the posed bbox hook for U4's anchors
Checked: **not a model scale and not a wrong model/LOD**.  `BtlModel` has no per-monster scale (`SetScale` is only used by the death shrink and the petrify-break copy at 1.02; `MONSTERParam+0x15` bits 5..7, the "size class", are read by the camera / target code, not by the model).  CHR 418 has one `mdl`; its bind pose is 17.1 high, the port plays `idla` (15.6 .. 15.9 over the cycle, hunched shoulders), `idlb` is 11.4.
The Statue (CHR 419, 14.5 posed) matches live (72 vs 73 px) while the Revenant (15.9) is 22 % short: relative to the Statue the live Revenant is ~1.15 x taller than its `idla` data, i.e. it stands in a pose close to the **bind pose (17.1)**.  The motion data have no scale events (`idla` / `idlb` of 418 carry none).  Open: the live idle pose of a monster while the target page is open (a live PINE read of the Revenant's `BtlModel+0x510` motion id / `+0x4f4` name and its `Frame` matrices would settle it; B1 did not use the emulator).
Hook for the anchors: `models::posed_bounds(&AnimatedModel) -> Option<(Vec3, Vec3)>` returns the bounds of the current pose (PS2 model space, y down); `BattleRuntime::dims` / `plugin::sync_positions` still use the bind-pose bounds (`CharacterAsset::bounds`).  Anchoring the arrow / icons on `posed_bounds` of `BattleModel::holder` (min y = top) would follow the posed height instead of the bind height.

## E2 (2026-10-10): requests / hooks (effects)
1. **U4 (`sh2_battle/src/camera.rs`)**: `CamPose::fov_y` uses `tan(fov_y / 2) = 224 / fov_scale`.  The engine's `GsxCamera::SetViewMatrix(scrz, 0.8, 0.93333334)` (BtlCamera, EffectCamera via `SetScreenZ(key.fov)`) gives vertical focal `ay * scrz`, i.e. `tan(fov_y / 2) = 224 / (0.9333 * scrz) = 240 / scrz` (the field camera already uses `0.75 * angle` = 240 / scrz, see renderer.md).  If `fov_scale` is `scrz` the battle camera is ~7 % too narrow vertically.  Not edited (not E2's file).  `FxScene::default_scrz` (sh2_gfx) can be set from `rt.cam.pose.fov_scale` by the host for the bng shatter.
2. **F2 (`sh2_field/src/cutscene_plugin.rs`)**: small hook edits made by E2 -- `MapInstance::fx`, `show_map(.., cmn)`, `Inputs::cmn`, `BgFxPlugin` in `CutscenePlugin::build` -- the map's SBD `EFFECT` records (torches, candles, flares, smoke, fog, lens flares, motes, rain ...) now spawn with the cutscene map and follow its visibility.
3. **B1 (`sh2_battle/src/models.rs`)**: nothing edited; `stage::light_fighters` only *reads* `BattleModel { pos, holder, weapons }` and inserts `sh2_gfx::bevy::model::ModelLightOverride` on those entities.

## Windows round 3 (2026-10-14)
* **R2 DONE**: `sh2_core::game::ButtonAssign` (+ `sample_pad`), fed by `sh2_menu::plugin::apply_system_options`; `MenuSave::button_entries()` falls back to the build default for an unwritten block.
* **R3 library part DONE, naming corrected**: see `notes/integration/library_bits.md`.  `monster_met` / `monster_defeated` of the earlier text are now `monster_defeated` (+0xf43, set on every won battle) / `monster_snapped` (+0xf63, Snap Shot).  The knowledge array (+0xf83) is still read-only; the retail result code writes it from a per-battle list (`BtlSocket+0x58a`, flag bytes `+0x64a`) whose source is not identified.  Combo-flag and Score counters of R3 remain open.
* **Option consumers DONE**: battle cursor memory (`sh2_battle::ui::BtlMenu::{with_memory, path}`, per-fighter `cursor_mem`) and the Navi Map (radar, `notes/integration/navimap.md`; the option bits are `MENU+0x275` bits 2-3, not bit 1).
* **Audio**: `AudioRequest::StopGlobalSe { id }` releases UI sounds started with `PlaySystemSe` / `PlayBattleSe` (they are now tracked like `PlayGlobalSe`); the battle result screen releases 0x3000 when the count ends and `exit_battle` releases every SYSREG loop (0x2000, 0x2001, 0x3000, 0x3001).  Field owners: any other looping SYSREG sound you start needs the same release.

