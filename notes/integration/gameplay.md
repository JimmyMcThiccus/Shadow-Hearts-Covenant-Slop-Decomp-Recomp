# Gameplay layer: Title -> Field -> Battle -> Field in Bevy

Status (2026-10-09): `cargo run -p sh2_app` boots to the title, starts a new game, runs the first map script, walks the player
around with floor collision, triggers a random encounter, fights it with the Judgement Ring and returns to the field with the
result applied.  `cargo run -p sh2_app -- --autoplay` plays exactly that through the pad and writes screenshots; the same flow runs
headless in three unit tests (`cargo test -p sh2_app`).

## Where things live

| crate / file | contents |
|---|---|
| `sh2_core/src/game.rs` | `Scene` state (moved out of `main.rs`), `GamePad` (keyboard -> PS2 pad bits through `CPadCore`), `PadInjection`, `FieldRequest` / `BattleRequest` / `BattleReport`, `apply_sys_actions` (the `SSHSys::PollingApi` request -> `SetAPI` step), `GameCorePlugin` (60 Hz fixed clock + `GameSet` ordering) |
| `sh2_menu/src/plugin.rs` | `MenuPlugin`: title scene (`title::OpeningMessage` driven at 60 Hz), game-over scene (`gameover::GameOverScene`), quick save / continue, `ListWindow` (the reusable list menu built from `Window` + `Widget` text places + `Window::move_place`), `Cover` (fader) |
| `sh2_menu/src/bevy_ui.rs` | the Bevy-UI implementation of `MenuGfx`: `UiCanvas` layers, `LayerGfx: MenuGfx`, `render_canvas` (entity pool, `ZIndex` = command order), UI scale (512x448 virtual screen), CJK font loading |
| `sh2_menu/src/session.rs` | `GameSession` (owns a `SaveFile`: BTL0/FLDa/MENU, script registers, saved character position), `FileStorage: SaveStorage`, `save_session` / `load_session`, `NameDb` (SSHMES) |
| `sh2_menu/src/sjis.rs` (+ generated `sjis_table.rs`) | Shift-JIS <-> Unicode (CP932 table), game text codes (`$`, `%W n` ...) |
| `sh2_field/src/sim.rs` | `FieldSim`: renderer-independent `CField::Polling` (movement, event boxes, `CheckEncount`, camera) |
| `sh2_field/src/plugin.rs` | `FieldPlugin`: map load, `FieldHost: ScriptHost` (`CField::CallFunc`), phases (battle flash, map jump), message windows, rendering glue |
| `sh2_field/src/menu_overlay.rs` | in-game command menu (`CmdMenu` pages as `ListWindow`s) |
| `sh2_field/src/autopilot.rs` | `Pilot`: pad bits from game state (used by `--autoplay` and the headless test) |
| `sh2_battle/src/bridge.rs` | `PCEntry`/`MonsterEntry` (party + `MONSETTbl` -> `Fighter`s), result write-back (`MakeResultTrophy`), `SetSceneInit` (starting party) |
| `sh2_battle/src/plugin.rs` | `BattlePlugin`: `flow::Battle` + `flow::CommandMenu` + `JRing` as the attack resolver, battle UI, result screen, `SshSys::cb_battle` |
| `sh2_app/src/autoplay.rs` | `--autoplay` driver + the headless flow tests |
| `sh2_app/src/main.rs` | unchanged structure; now `pub use sh2_core::game::Scene`, `scene_transition` also applies `SysAction`s, registers the plugins, window 768x672 |

Small edits to existing files: `sh2_battle/src/flow.rs` (`Battle::ring`: the ring multiplier fed to `PhysHit.ring`, `Rng + Send + Sync`),
`sh2_menu/Cargo.toml` (bevy / sh2_core / sh2_gfx deps), `sh2_menu/src/lib.rs`, `sh2_field/src/lib.rs`, `sh2_battle/src/lib.rs`
(new modules).

## System ordering vs `CApp::Run`

```
CApp::Run (per frame)                         Bevy
-------------------------------------------   --------------------------------------------------------------------
World::Begin/Render/EndUpdate (OT -> VIF1)    render world: meshes (FieldMapPlugin), Bevy UI (UiCanvas), gizmos (ring)
CPoller(0x60): SSHSys::Polling + PollingApi   Update:  system_poller -> scene_transition        [sh2_app/main.rs]
                                                       (SshSys::polling, apply_sys_actions, NextState<Scene>)
CPoller(0x48/0x54): scene objects             FixedUpdate @ 60 Hz, chained sets   [GameSet]
   CPad::Polling (inside SSHSys)                Input : autoplay_inject -> sample_pad (keyboard | PadInjection -> CPadCore)
   CScript::Polling (prio 0x70)                 Script: field_script_tick (VM + FieldHost, typewriter)
   CField::Polling / CBattle::Polling /         Logic : field_logic_tick, menu_tick (overlay), battle_tick, title_tick,
   Menu::Run (prio 0x80)                                gameover_tick
   CField::CameraUpdate                         Camera: field_camera_tick (FieldSim::tick already evaluated the camera)
m_pAppFunc                                    Update:  app_func_hook (unused)
ScreenBright::Draw (faders)                   UiCanvas layer FADER (`Cover`)
```

Why 60 Hz: all PS2 logic is frame based (speeds per frame, repeat counters, ring `dt = 1/60` constants), so the scene logic runs on
`Time<Fixed>` = 60 Hz and the render rate is free.  The handover through `SshSys` (closeInquiry -> preLoad -> Start) stays in `Update`
exactly as `CApp::Run` runs the system poller before the scene pollers; a scene's `OnEnter` therefore runs one frame after the request,
like the original's two-phase `Polling`.

Scene requests follow the original protocol:

* new game: title -> `SshSys::set_api(FieldSocket)` (`opening()` -> `FieldMapJump`), `FieldRequest{map, entry}`
* map jump (script op 0x20): `FieldRequest` + `set_api(FieldSocket)` (same-state `Scene::Field` re-entry rebuilds the runtime)
* encounter: `SshSys::start_battle(Some(param), Some(map))` (request 0x20) then `start_battle(None, None)` (0x21) ->
  `SysAction::StartBattle` -> `BattleRequest` + `set_api(BtlSocket)`
* battle end: `SshSys::cb_battle(0, outcome_bits)` (`cbBattleA`): win / escape -> request 0x10 (field, `FieldRequest.entry = RESTORE`
  = `FieldMapJump(name, -2)`, position from `GameSession::chr_pos` = `ChrPosSave`), defeat -> request 0x30 (game over)
* game over -> `ShiftTitle` = `set_api(DummyStage)`

## What is real

* Title state machine (`OpeningMessage`, JP 0x003a8a60), game-over state machine, both driven unmodified; real `OPENING.DAT` textures (trial
  splash 0x14, logo, mist background) decoded by `sh2_gfx::texture::decode_menu_texture`; real game over illustration from `MENU/IMG/GO`.
* Field: real MPS parse, `CFloorMan` collision + wall sliding + slope scale (`movement.rs`), event boxes (`CFieldEvent::HitCheck`), CAMEVENT
  / CAMERA table evaluation and `CFieldCamera::Apply`, the `CheckEncount` distance/roll logic (`encDist` read from `FIELD.BIN`), MONSET roll,
  real map script (`.MSC`) running in `sh2_script::CScript`, script register file persisted across maps and into saves.  Map geometry is the
  renderer agent's `FieldMapPlugin` (textured BG models).
* Script ops implemented in `FieldHost`: `0x20 MapJumpA`, `0x23 SetFieldData`, `0x28/0x29 SetFader`, `0x30-0x37` window/message ops
  (real Shift-JIS dialog text through `sh2_menu::message::Message`), `0x38 KeyWait` (suspend/resume protocol), `0x70 GetWorldMapInfo`.
  AP_00_U's start function really jumps to AP_02_U (a short cutscene in the retail flow); AP_02_U shows its opening dialogue; its exit
  box leads to AP_03_U, the first map with MONSET.
* Battle: party from the save block (`PcRec`) + `PC_I`/`PC_L` tables, monsters from `MON_`/`MONSET` records, `flow::Battle` phases, turn
  order, `rules::physical_damage` etc., `JRing` (section D state machine) as the resolver of every player attack with its result
  (`JrResult`) converted to the damage multiplier, rewards through `rules::make_result`, level-ups through `BtlSave::pc_level_from_exp`.
* Save/load: real `SaveFile` format, files in the user data dir (`~/Library/Application Support/sh2_port/BISLPM-00000-SH2/SH2-000`,
  `SH2_SAVE_DIR` overrides), system file slot table kept in sync.
* The Japanese text renders with the real strings (names from `SSHMES`, dialogue from scripts); fonts come from a system file
  (`Arial Unicode.ttf` on macOS, `SH2_FONT` overrides) because Bevy's `system_font_discovery` needs crates unavailable offline.

## What is placeholder (and the next step for each)

| area | now | next step |
|---|---|---|
| player / NPC models | capsule + nose cube, no motions; walk speed 1.6 / 3.2 units per tick (the original uses motion root translation) | load the character model + `walk`/`run` motions through `sh2_gfx::bevy::model::AnimatedModel`, take movement from the motion (`CFieldModel::TransCallBack`), implement script ops 0x08 `LoadCharacter`, 0x10/0x11 `SetMotion`, 0x17/0x18 model position/automove |
| script ops | **all ops used by the 43 JP and 546 US map scripts are implemented** (`sh2_field/src/host.rs`, table: `notes/integration/script_ops.md`); approximated: movie cut scenes (MCES = placeholder wait, LSD player not wired), shop / tailor UI, ring minigame, pad vibration, effects (timed objects) | LSD player for MCES, shop UI, motion lengths from every model |
| world map | done for the JP demo: new game opens the area select (`notes/integration/worldmap.md`) | US retail point list |
| battle visuals | primitive stage / characters, fixed camera, no effects or motions; ring drawn with gizmos (no `JRING.BIN` textures, no hit sprites) | `BtlModel`/`BtlBG` loading from `BTLDATA`, effect VM, JRing sprites (`HitMes/HitBar/HitArea`) |
| enemy AI / effects | enemies attack a random living PC (`AIS` scripts not decoded), items are a flat 30 % heal, magic/skills/fusion/guard-counter unavailable (menu offers Attack, Item, Guard, Run) | `AITurnFunc` VM, `EffectCodeFunc` |
| rewards | most demo `MONSTERParam` have EXP/cash 0: `bridge::monster_rewards` substitutes `hp/6` EXP and `hp/10` cash | none needed for retail data |
| starting party / items | PCs 5, 0, 1 from `PC_I` difficulty 3 (levels 12); starting items and cash 300 are made up (`RegDat 0x3f` scene tables not decoded) | decode `SCEN` (0x3f) |
| in-game menu | Items / Equipment / Status / Formation (swap) / Save / Load / Close from `ListWindow`s, English labels; item use, equipment change, magic, crests, options are missing | port `CmdItem`, `CmdEquipment` ... on top of `ListWindow` or the real `.MSD` scenes |
| title | movie (`DEMO.LSD`) and attract battle are skipped (`lsd_idle/lsd_started` reported true), swirl layers and music missing, "Continue" row added by the host | LSD/MPEG player, `StreamBGM` |
| audio | all `PlaySE` / BGM requests are logged | `Sdrv` replacement (rodio) |
| camera | `CAMERA` kinds 0-3 and 5 (nearest segment) as ported in `camera.rs`; kind 4 and rounded kind 5 missing; no roll; `FieldSim` falls back to a chase camera (frozen facing, 45-tick hysteresis) when no CAMEVENT is hit or the evaluated pose keeps the player off screen | finish `UpdateFieldCamera`, then drop the visibility fallback |

## Running it

```text
export SH2_DISC_DIR="<JP Furokuban folder>"
cargo run -p sh2_app                                   # keyboard: arrows/WASD move, Space/Z/Enter = O (confirm), X = cross (cancel / run),
                                                       # C/Tab = triangle (menu), F3 = field debug overlay (event boxes, encounter counter)
cargo run -p sh2_app -- --autoplay [--shots dir]       # scripted run + screenshots (default notes/integration/screens/gp_NN_*.png), exit 0 on success
cargo test -p sh2_app                                  # headless flows: title->field->battle->field, game over -> title, save -> continue
```

Screenshots of the last autoplay run: `notes/integration/screens/gp_*.png` (title splash, press start, menu, field, dialogue, in-game menu,
walking, battle command menu, judgement ring, victory, field after the battle).

## Notes for the next agent

* `FieldPlugin` / `BattlePlugin` / `MenuPlugin` only add rendering systems when `PbrPlugin` / `UiPlugin` are present, so they run under
  `MinimalPlugins` (see the tests).  Each has a runtime resource (`FieldRuntime`, `BattleRuntime`, `TitleRuntime`) that is inserted on
  `OnEnter` and removed on `OnExit`; everything with a transform is `DespawnOnExit(Scene::..)`.
* `UiCanvas` layers expire after 0.12 s without a producer (`TTL`), so a scene never leaves stale UI behind.
* The field map root of `FieldMapPlugin` is kept alive between visits and hidden outside `Scene::Field` (its loader skips an unchanged map
  name).
* Autoplay heuristics that depend on demo data: `Pilot` hints (`PILOT_HINTS`: AP_02_U exit box id 2, `PILOT_AVOID`: AP_03_U door box 1).
