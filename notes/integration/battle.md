# Battle presentation and rules (camera, stage, menu, AI, effects)

Status (2026-10-09).  Crate `port/crates/sh2_battle`; new files `camera.rs`, `stage.rs`, `ui.rs`, `ai.rs`, `actions.rs`, `host.rs`,
`effects_bridge.rs` (+ examples `btl_ls`, `btl_dump`, `btl_tags`, `btl_party`, `btl_bbg`, `btl_fx_trace`, `btl_fx_scan`); `plugin.rs` was rewired
(everything below is driven from `battle_tick` / `run_battle`), `flow.rs` got three small changes (see "Changes to existing files").
Run / verify (battle straight from the title screen, no field needed -- `devdrive.rs`):

```
export SH2_DISC_DIR=<JP Furokuban> SH2_US_DISC_DIR=<US disc 1> SH2_AUDIO=null SH2_LINEAR_BLEND=1
SH2_BATTLE_DEMO=2 SH2_BATTLE_SHOTS=/tmp/bshots SH2_BATTLE_CMDS=attack,magic,item cargo run -p sh2_app   # exits by itself, writes bt_NN_*.png
```
`SH2_BATTLE_DEMO=<MONSET>` starts battle `AP_03_U` (party Yuri / Ur / Blanca, `w0` = `SH2_BATTLE_BG`, default 0 -> nearest of the 13 demo backgrounds) and plays it
through the pad (`SH2_BATTLE_CMDS` = attack / magic / item / guard / fusion, cycled); `SH2_BATTLE_CAMDBG=ex,ey,ez,lx,ly,lz` pins the camera, `SH2_BATTLE_NOSTAGE=1`
drops the BBG.  `SH2_LINEAR_BLEND=1` is no longer needed (the black 3D layer of the default gamma pipeline was fixed 2026-10-09, see renderer.md).  Screenshots: `notes/integration/screens/gp_08..gp_14_battle_*.png` (intro, command menu, target select, judgement ring,
effect, magic menu, victory) -- they come from this driver (`--autoplay` now reaches the scripted tutorial battle itself: `screens/final/`).

## What is real and what is a placeholder

| area | real (ported from the JP decompilation / read from the discs) | placeholder / missing |
|---|---|---|
| **Stage** (`stage.rs`) | `BTLDATA/BBG/%03d.BBG` container (`DAT`, `mdl` = the whole stage as an SSH1 model with its textures, `mbs` = SBD "BG element" container: `FOG`, `BGCOLOR`, `LIGHT` chunks parsed), id = first word of `_SysBtlParam` (`SetFieldData` of the map), rendered through `sh2_gfx::bevy::model::spawn_static_model` under a `Ps2Root` like the field maps; nearest available id when the demo disc lacks it (13 backgrounds exist) | the `anm` motions and the `EFFECT` chunk (animated BG parts), fog and `LIGHT` are not applied; the demo's maps give `w0` = 0 (no `SetFieldData` value) so background 1 / 2 is chosen by `resolve_bbg_id` |
| **Camera** (`camera.rs`) | `UpdateCamera` (orbit pose, half-second cosine ease, vibration, floor + arena clamp), modes 6, 7, 8, 9, 0xa, 0xf, 0x10, 0x11, 0x12 (structure), 0x18, 0x19, 0x1a with the constants read from the retail `Polling` (US decompile, `decomp/H/BtlCamera_Polling_US.c`); 0x13 attack camera: the retail yaw-pick / tracking logic of `FUN_005ad3b0`; modes 4/5/0xb-0xe/0x14 approximated (see the table in `camera.rs`); an effect's own `EFCM` camera takes over while `btlCameraControlStatus(0)`; cuts after the intro (the first command-menu shot was mid-ease) | the 3,100-line per-attack-id variants of 0x13, the ECCParam shot tables of 0xc..0xe, the bbox-fitting pass; formation positions are still the port's own (`BtlChrPosInit` would put the party in a tight row along x at z = -((depth+10)/10 + 15) - r, not 140 units apart: `models.rs::home_pos` is not mine) |
| **Command menu** (`ui.rs`) | structure of `SetMainMenu`: Attack -> shape (ST/HH/HA/KD) -> target, crest Magic (`PcRec::skills` = crest slots -> `MC_P` -> `MAGI`, MP costs, greyed rows), Special (SKIL group = party id), Fusion (PC 0), **Link / 連携** (another living member, none while a combo runs), Item (real `ITEM` rows with bag counts, battle-usable test, menu order, target class from the record flags), Guard, Run (only if the MONSET allows); SYSREG sounds cursor 0 / decide 2 / cancel 3 / buzzer 4 (`sh2_audio::se_ids`); `BtlMenuCBFunc` events (`MenuEvent`); real JP strings from `BATTLE.BIN` (`BtlMenuItem_J`, `BtlMenuNote_J`, `BtlMes_J`) and `SSHMES` names | tarot / aroma / snap / marionette / sword-art entries do not exist; the demo party has no learned skills in `SKIL`, crest magic needs `MC_P` + learn bits (Yuri / Blanca start with crests 18 / 20, 21) |
| **Enemy AI** (`ai.rs`) | the AIS token VM (`AITurnFunc`, `AIIfFunc` kinds 0..0x35, `AICalcFunc`, `AIGetValueOne`, `AIGetValue` 0..5), file selection (`MONSTERParam+0x20` -> `M%03d_%03d.AIS`), the `GetTarget` criterion decoder (21 handlers: highest/lowest HP/MP/SP, SDEF/PDEF, status filters, cluster rules, probability classes 100/50/70 %); US token dialect | conditions 0x17-0x19 (the flag word `BtlChr+0xfe` is only ever zeroed in the decompiled battle code, so false is exact), **0x1b exact** (`EffectCheck` JP 0x00650080 -> `actions::effect_check` over the skill record's effect words and the unit's statuses), **0x26** (`GetComboTarget` reduced to partner / fallback pick, `BtlHost::combo_target`); unported: `GetMoveTarget`; moves / flee / leave decisions are turned into "guard" because the flow has no per-monster flee yet |
| **Items / magic / skills** (`actions.rs`, `host.rs`) | `SpecialEffectCode` word decoding (classes 0x00..0x5f), the HP/MP/SP/revive/status/timed-stat subset of `EffectCodeFunc`, `GetSAtkDamage` / `GetSkillPAtkDamage` for damage skills (power = record `+0x1a` %), MP costs, bag consumption, poison tick | the full 82 KB `EffectCodeFunc` (protection flags, "dead reset", AI success statistics), `EffectDamageSet` (15 KB), multi-target areas, fusion transformation (a timed attack boost instead) Fusion presentation (`effects_bridge::fusion_presentation`: fusion camera, `fusa` motion, flash, model swap through `BattleModel.asset/holder`, revert when the boost ends), **Link combos** (`flow.rs`: the partner chooses and acts first, the leader acts after, one slot, `Battle::combo*`, test `link_hands_the_slot...`); casting motions of skills (`sp1..sp9`, `mags`, ...) come from the effect programs (`chrSetMotion` -> `FxEvent::CharMotion` -> a second model entity plays the effect's own motion) |
| **Effects** (`effects_bridge.rs` + `sh2_gfx::effects::{scene,render}`) | the VEC host now builds a real scene: effect models (`M` + `A` sections, real `ModelInstance` playback so `mdlWaitMotion*` waits the true motion length, attach to character frames by name with the joint position + animation rotation, `mdlSetOffsetRotTrans`), `EFCM` cameras (**first key vector = look-at, second = eye**, relative to the played model), `EFLT` lights (added to the scene light), screen sprites (`spr*`: layers < 5 are drawn in 3D behind the effect models so a darkening sprite dims the stage but not the effect), `bfd*` fader, `pph*` ribbons (`CPath`, strip = pos +- dir), `pgr*/pol*` quads, `col*` scene-light dimming, `shr*/chr*/btl*` queries of the characters' skeletons (`FxEnv`), sounds (`ssePlaySe` -> `AudioRequest::PlayEffectSe`, the EFMG `1` banks), `chrSetMotion/btlCharactorShow/shrStartModelAlphaFader/btlBattleBGShow` applied to the battle models and undone when the effect ends; 253 of 253 effects run; 181 end on their own in 300 ticks (the rest wait on hit tests the host answers after 6 ticks) | `blr*` blur (no framebuffer feedback), `bng*` shatter, `gny*`, `fef*` particles (never called by battle effects), `mdlAttach3` (character chained to an effect frame), `mdlCreateMemory` clones, texture alpha-test registers (`mdlSetTestReg`), model colour faders; weapon attacks have no EFD: they get the ring + a hit spark (`HitMark` stand-in) + the SYSBTL hit SE |
| **Rewards** (`host::UsRewards`) | EXP / cash / SP / drops from the retail table (`COMMON/SSHDAT.NA` section `MON_`) for monsters whose JP record is empty, matched by id **and** model number | none |

Fixed during verification: the stage is the **interior** of a rotunda (radius ~165, floor y = 0, a mirrored copy of the hall below the floor), so cameras must stay
inside it: `Overview` is now a wide-fov (300) shot at <= 115 units; character radius / height for the camera come from the models' bind-pose bounds (`BattleRuntime::dims`);
`BGCOLOR` -> `ClearColor`, `FOG` -> `Sh2Fog` are applied like the field maps do; empty demo-disc names fall back to `Magic n` / `Item n` / `Skill n`.
`MonsterParam::def_element` now reads `+0x14 & 7` (`GetPAtkDamage` uses that byte for the monster as defender *and* attacker; `+4` is the CHR model number).

## Decoded formats and tables (new facts)

* `BBG` / `SBD`: see `stage.rs` header.  `DAT` = 3 floats (arena 200 x 100 x 200) + count.
* `AIS`: see `ai.rs` header (token table, operand encoding, IF = `04 kind a b 05 target`, group markers, `GetTarget` criterion number layout:
  `block = c / 40` (plain / cluster / 50 % cluster), `h = (c % 40 - 1) % 13 + 1` stat rule, `s = (c % 40 - 1) / 13` probability class, 120..126 specials).
* `SKIL` header = 24 `{offset, count}` groups (group = party id, 0xc..0x15 fusion monsters, 0x16 monster skill sets (0x28 B = 20 x s16, -2 = empty), 0x17 monster skills (0x20 B)).
* `MC_P` = crest -> up to four `MAGI` ids (`+6` bit k = needs the learned bit `BtlSave+0xaae`).  `PcRec::skills` (PCParam `+0x76`) are the eight crest slots.
* Effect words: `actions.rs` header (class byte, kind = `byte2 + 3`, percent bit 3, "set" bit 2, status words take two words).  Item examples: Medi-Leaf `0x1000004b`
  (HP +75), Medi-Refine `0x1c030064` (HP set to 100 %), revive amulet = kind 0x2b + 20 % HP, "cure all" `0x26000000 / 0x64000000`.
* Target class of a record: `(flags & 0x7f) >> 5 == 0` -> opponents, else `(flags & 0x1ff) >> 7` = self / allies / opponents / everyone.
* `MONSTERParam+0x20` (i32) is the AIS id (`0xe` -> `M000_014`, `0x7eb` -> `M002_027`, `0x271e` -> `M010_014`, `0xc738` -> `M051_000`, ...); `+4` (u16) is the model number.
* `BtlSocket+0x15c` (battle background) = `_SysBtlParam` word 0 (`SSHSys::PollingApi` request 0x21 stores `s->btl.w0`).
* US AIS files use a shifted token numbering (group `0x2c`, call `0x2d`, skip `0x2e`; extra actions `0x28` guard and `0x2a` boss); `Dialect::Us` handles it, but the retail
  `AIIfFunc` condition numbering has not been verified, so only JP scripts are used.

## EffectCodeFunc (JP main 0x00331960, 82 KB) -- structure (documentation only)

`EffectCodeFunc(float power, int actor, int count, EFFTBL* recs, ECResult* out, float* rate, BtlChrParam* target, bool test, bool noRandom)` walks `count` 12-byte
records produced by `SpecialEffectCode` (`+1` flags: bit 1 percent, bits 2..4 duration type, bits 6..7 flag; `+4` kind; `+5` turns; `+6` chance; `+8` value) and, per
kind, mutates the target `BtlChr` (`+0x72/0x74` HP, `+0x76/0x78` MP, `+0x7a/0x7c` SP in the 0xb0-based view) while accumulating the result flags in `out` (`+0x20` applied
statuses, `+0x24` cured, `+0x28` blocked) and, when `rate != NULL`, a *dry-run* success percentage (the AI's `EffectCheck`).  Cases: 3/6/9, 4/7/10, 5/8/0xb HP/MP/SP
(flat or percent of max, add or set; kind 6/7/8 use the real max), 0xc..0x14 timed stat records, 0x15/0x16, 0x17..0x22 modifiers, 0x23 element, 0x29/0x2a guard,
0x2b revive, 0x2c..0x2f, 0x30..0x3f, 0x43 "has beneficial effect", 0x44..0x46, 0x47 status bits (duration type 0 inflict with chance and the 0x80/0x20 "dead reset"
paths, 1 cure, 2 permanent), 0x48 aux status.  `rand() % 100 <= chance` gates every infliction unless `noRandom`.

## Changes to existing files

* `flow.rs`: `Host::resolve_effect` takes `&mut [Option<Fighter>]` (MP/SP costs, status, revive); `Fighter::max_mp`; `EffectKind::Fusion = 7`; poison (status 0x47 bit 0/1)
  ticks 5 % / 10 % of the max HP at the turn start.
* `bridge.rs`: `Fighter::max_mp` for PCs / monsters.
* `plugin.rs`: rewritten around the new modules (public API for `models.rs` kept: `BattleRuntime`, `BattleCamera`, `BtlChr`, `Stage`, `BattleDb`).
* `Cargo.toml`: `sh2_audio` (menu SEs through `AudioRequest::PlayBattleSe`; ids 0 / 1 / 2 for cursor / confirm / cancel are guesses until `SYSBTL.SSE` is listened to).


## Second pass (battle presentation completion)

### Camera
`camera.rs` header = mode table (what is exact / approximated).  `BtlCamera::Polling` could not be decompiled for the JP demo (122 KB, Ghidra times out and stops at
the unresolved jump table); the **retail (US) `Polling` decompiles** and was used: `decomp/H/BtlCamera_Polling_US.c` (all modes, retail numbering: the retail build inserted
two cases so JP 0x18 / 0x19 / 0x1a = US 0x1b / 0x1c / 0x1d) and `decomp/H/BtlCamera_AttackFusion_US.c` (the separate attack-camera function and the fusion camera).
Helper conventions (verified against the sceVu0 sources): eye = `F + Rz Ry Rx (0, 0, -D)`, `D = fov / 512 * (k + radius + |size|)`; every shot eases through `UpdateCamera`.
Tutorial stage framing: the first command-menu shot was a half-second ease from the far intro pose (fov 300 -> 512); leaving the intro now cuts, and eyes are clamped to
the arena half extents (`DAT` x / z over 2).  Dev aids: `SH2_BATTLE_CAMLIST=home,portrait2,fusion,attack,... SH2_BATTLE_FXSHOTS=<dir>` cycles requests and photographs them.

### Effects
```
SH2_BATTLE_DEMO=2 SH2_BATTLE_FXLIST=3,28,43,63 SH2_BATTLE_FXSHOTS=/tmp/fx SH2_BATTLE_FXEVERY=10 cargo run -p sh2_app    # plays these EFDs from the party onto the first enemy, fx_<id>_<tick>.png
cargo run -p sh2_battle --example fx_corpus -- <JP disc>      # all effects headless: models / ribbons / quads / lights / camera ticks, unhandled calls
cargo run -p sh2_battle --example fx_dump -- <JP disc> 83 60  # per tick camera / model / ribbon state;  fx_cam, fx_frames, fx_find, fx_fusion: format / data dumps
```
* Data model: `FxScene` (state, PS2 world space, columns = `sceVu0FMATRIX`), `FxView` (what to draw), `FxEvent` (what the battle must do), `FxEnv` (actors: root matrix,
  named frame matrices, radius / height, model numbers, scene light colours).  `EffectRenderPlugin` + `FxLive` draw the view under a PS2 flip root through `Sh2Material`.
* Corpus facts: effects 28 / 43 / 82 / 94 (spells), 3 / 4 (items), 63 / 68 / 83 / 92 / 180 (ribbons, particles, fades) render; 135 / 252..254 build `pgr/pol` quads.
  `EFCM` keys: first vector = point looked at, second = eye (`EffectCamera::LookAt` JP 0x003080b0 takes `GetInter(key)` and `GetPos(key+0x10)`).
  `pph*` colour keys are 0..128 (alpha 255), `AddPath` dir is the half width.  `bfdSetMode(mode 3|2, secs, colour)` fades to / from the colour (255 = white).
* Screenshots: `notes/integration/screens/battle_fx/` (`effect_<id>.png` = six frames of an effect, `cameras_*.png`, `fusion_sequence.png`, `weapon_hit_spark.png`, ...).

### Actions, fusion, Link
* Fusion (`SH2_BATTLE_FUSION_CHR=<n>` / `SH2_BATTLE_FUSION_PC=<pc id>` force a model and the PC for the demo disc, whose `FUSM` rows are stubs pointing at party models): the
  menu entry is offered to PC 0; Phase::Fusion holds the flow 3 s: fusion camera, `fusa` / `mags` motion, white flash at 1.1 s, model swap (`BattleModel.asset/holder`), reverts
  to the human form when the +50 % boost status is gone.
* Link (連携): `MenuEvent::Link` -> `Phase::Link`: partner chooses and acts, then the leader (`Battle::combo`, `combo_queue`, `BattleEvent::ComboLink`); AI conditions 0x25 / 0x34 /
  0x35 see the pending state through `BtlHost::combo_pend / combo_cnt`; friendship bonuses need `PCParam` affinities (not wired: `Host` has no hook for them).  ComboForm / CmbBreak
  visuals: see combo_form.md / break_effects.md (2026-10-19).
* AI: 0x1b exact via `actions::effect_check`, 0x26 via `BtlHost::combo_target`, 0x17-0x19 = bits of the never-written flag word.
* SE ids: menu = SYSREG (cursor 0, decide 2, cancel 3, buzzer 4), hits = SYSBTL 0x1000 (0x1005 for critical hits), effect sounds from the EFMG banks.

### Known gaps / things not mine
* `models.rs::home_pos` / `plugin.rs::home_pos` formation is the port's own; `BtlChrPosInit` (CBattle 0x004ab590, 80 KB, party row at z = -((arena depth + 10) / 10) - 15 - r) is not ported.
* The party names in `BattleSetup::names` do not match the model numbers of the demo party (fighter 0 is labelled "Yuri" but loads CHR 005; PC id 0 / CHR 000 is the jacket model); Fusion
  is attached to PC id 0.
* The retail-only effect syscalls (17 ids) and the retail `FUSM` data are for the US-disc work.
* `sh2_app --autoplay` timed out in the title scene on 2026-10-09 23:56 (other agents' changes; not investigated).


## Third pass (retail presentation, 2026-10-10) -- screens in `screens/battle3/`

### Retail stage and formation (the "magenta placeholder" was a wrong background id)
* **BBG lookup.** `_SysBtlParam` word 0 = `GetFieldBattleInfo()+4` = `SetFieldData(7, id)` (the map's MONSET header word `+0x18`); `SetFieldData(6)` /
  header `+0x16` is the battle **BGM** (`CField::StartBattle`, decomp/G/CField.c:4739 / 7557).  `sh2_field::plugin` had the two swapped, so the retail maps (header
  `bgm 401, bg 77`) asked for BBG 401 and fell back to the nearest id (101, a magenta stage).  Fixed there (3 lines); the US disc has BBG 000..101 (no gaps that
  matter: `resolve_bbg_id` still falls back to the nearest).  AP_02_A / AP_03_U / AP_04_U / AP_05_U all use **BBG 077** (the cathedral hall with the compass floor).
* **Floor.** BBG 077 draws black: `FL_C` / `FL_D` (atomics with header word `+0x20 == 1`, flat, > 250 units, vertex colour 2..7/128) cover the whole floor at y = 0 (`FL_C`
  0.4 above it); the PS2 draws them first.  `stage::sink_backdrops` moves them 1 unit under the floor.  Remaining stage gaps: the `LIGHT` chunk, the `EFFECT` chunk /
  `BtlBG::SetAlpha` wall fades (groups FRL FRR BAL BAR LEF LEB RIF RIB RO FL), fog is applied but not verified against the original.  `SH2_BBG_ONLY=FL_A,FL_B` keeps only
  atomics with those name prefixes (debug), `examples/bbg_scan` lists every BBG (`--atoms <id>`, `--dump <id> <dir>`).
* **`BtlChrPosInit`** ported in `formation.rs` (JP 0x004ab590): party row at `z = -(DAT z / 10) - 15 - max R` packed by the bounding radii (`R = (size.x + size.z) / 2` of the
  first record of the model package's `bbx` section, `ChrBox::parse`), enemy rows at `+15` with the MONSET formation id (0..0x13: all random spreads of ids 0..6 and
  0xf..0x13, the tight variant of 7..0xe), ambush rings (`Ambush::PcFirst` / `EnemyFirst`), and the box-centre correction.  The sides now face each other along the
  stage's z axis (party Bevy +z): `plugin::BattleRuntime::{homes, boxes}`, `models::{read_box, side_facing}`, attack stand-off = radii + 8.  Camera: the overview shot is taken
  from behind the party; `CamChr` facing/size come from the formation, so the exact `BtlCamera` modes frame like the original (command-menu shot = Nicolai in a
  medium shot with Karin at the edge, `us_command_menu_nicolai.png`).  Tests: `formation::tests`, `stage::tests::retail_backdrops_sink_below_the_floor`.
* Dev driver: `--us` uses Karin + Nicolai, `SH2_BATTLE_EXIT_AFTER=<shot>` ends the run after a photograph (`intro`, `command_menu`, `target_select`, `judgement_ring`,
  `weapon_hit`, `fusion_end`), `SH2_BATTLE_BG=77`.

### Mechanics
* **Friendship (Link)**: `Host::{friendship, combo_changed}`; `Battle::do_attack` passes `combo_active` + `friendship(attacker, leader)` to `rules::physical_damage`
  (`mult += friendship * 0.2 / 10000`, only inside a Link slot); spells cast inside a combo get it too; `BtlHost::{aff, pc_ids}` hold the `PCParam+0x84` tables
  (record offset `0x48`, 12 x i16) loaded from the save at battle start, grown by 100 for both members when an item / spell / skill is used on another PC, written back
  at the end (`plugin::write_back_friendship`).  Test `flow::tests::friendship_boosts_only_combo_damage`.  Not done: the combo-magic phase sum `friendship / 200`.
* **ComboForm**: `ui::draw_combo_form` (LINK panel: members in action order, acting one highlighted, friendship bar).  **CmbBreak / BreakBBox / HitImpact**: ported 2026-10-19 (break_effects.md): the "Combo Break!" banner for a missed non-final combo member, the finisher shock wave, and the stone-chip shatter of a petrified monster (the old "16 shards" stand-in is gone).
* **RingCustom** (menu agent's `CmdRingCustom`): the 20 byte `JRCUSTOM` table lives in the `BTL0` party record `0x60..0x74` (hits `0x74`, type `0x75`, auto `0x76`);
  `plugin::{ring_custom, ring_settings}` read it, `RingRun::start_areas_custom` hands it to `JRing::custom_data` (`CustomConvert` widens / narrows zone and strike tail per
  hit).  Hit count, ring type (practice / technical / gamble) and auto ring are readable (`ring_settings`) but not applied.
* **Fusion on the US disc**: the retail `FUSM` row (0x20 B) is `{u8 i, u8 i, u16 CHR, u8 flags, u8 SP cost, ...}`; rows come in triplets (SP 3 / 4 / 5 = three forms), `effects_bridge::fusion_chr`
  reads the CHR (86, 88, 247, 89, 91, 248 ...; `us_fusion_row0_chr086.png`).  The menu lists up to 24 rows; which forms Yuri owns (save bits) is not modelled
  (`SH2_BATTLE_FUSION_PC=<pc>` offers the entry to another PC for testing).
* Tarot / aroma / snap / marionette: **not implemented** (no honest data): the retail tables decoded so far are `TARO` 22 x 8 B `{u16 id, u16 id, u8 25, u8 10, u16 id}`, `AROM`
  8 x 8 B + 56 x 0x40 B (effect words at `+0x1c`), `PHOT` 2 x 0x20, `STAR` / `ANNE` 5 x 0x20 B; the behaviour is in the retail BATTLE.BIN (`TarotEffectFunc`'s US
  address in `notes/H/us_map_candidates.txt` is a false stub match), the JP aroma phase (0xc) is in decomp/H/CBattle.c.

### Effects
* `mdlAttach3` is real: `FxScene::actor_follow` -> per-tick `FxEvent::ActorRoot` -> `effects_bridge::apply_fx_roots` (also makes `shrSetModelRootMatrix` work).
  `shrSetModelColor` / `shrStartModelColorFader` -> `FxEvent::ActorColor` -> `ModelInstance::atomic_color` (faded, undone at the end).
* Still ignored (corpus, US disc: 248 effects): `blr*` (285 calls: needs a render-to-texture feedback, no implementation), `bng*` (24), `gny*` (4), `fef*`, `camFog*` (59),
  `shrSetBackColor` (56), `mdlCreateShadow`, texture alpha-test registers (`mdlSetTestReg` etc.), `mdlCreateMemory` clones.  Effects 92 / 180 were re-photographed
  (`jp_effect_092_sequence.png`): no dark / glyph defect reproduced on the demo disc with the current renderer.  Weapon attacks still use the generic hit spark.
* Not done: per-attack-id variants of the attack camera, run-up easing and hit-stop (waiting for the live timings of the sibling pine-refinement agent, not yet in
  `pine_us_refinement.md`).
* `--us --autoplay` (2026-10-10 04:22) timed out in the field scene `AP_02_U` before reaching a battle (field / pilot work of other agents in flight; not related to the battle crate);
  the retail battle was verified through the dev driver (`SH2_BATTLE_DEMO=2 SH2_BATTLE_BG=77 ... -- --us`) instead.

### Battle HUD from the game's own art (2026-10-10, `sh2_battle::hud`) -- screens in `screens/battle_cmp/`
Ground truth: live PCSX2 captures of the retail battle (PINE: MONSET -> 0x00749544, 0x21 -> 0x00749536 from slot 13; the pre-session state was saved to slot 20 and restored; captured
with `screencapture -l <window id>`, the 640x448-ish output is 4:3-stretched so 1 virtual pixel = 3.21 x 2.75 screen pixels).  Findings:
* The HUD is **not MSD driven** (`BTL_002.BIN` entry 0 only holds the `%4d` number font setup); it is hand-placed sprites with texture pixels 1:1 in the 512 x 448 screen.  Art:
  `BTLDATA/BTL_000.BIN` = JRCTex atlases (`sh2_gfx::texture::decode_jrc`, palette 0): 1 italic digit font (`HP MP SP` labels y 0..9, digits y 0..13, columns in `hud::DIGIT_COLS`) --
  the lower part is a runtime render target; 3 gauges (`HP`/`MP`/`SP` fills 50 x 4); 5 command header capsule (y 30..86) + row gradient bar (top 25 rows) + scroll boxes; 8 plate ornaments;
  9 arrow / star icons (5 x 2 of 19 x 24); 18 "Turn Priority" title + arrow glyph; 19 card capsules; 20 emblem; 23 big letters; 24 enemy cards (letter on a peach capsule, 2 x 4 of 36 x 46).
  Portraits: `MENU/FACE/FI_%03d.TEX` (104 x 128), numbered by the character's **model number** (Karin 005, Nicolai 018, Yuri 000).  Text: the game font (`COMMON/CMNMENU.DAT` attach 0,
  20 x 20) with `spacing -1`; `hud::load_hud` also installs it into `UiCanvas::fonts` when the menu has not (the menu's own loader warns "bitmap fonts could not be loaded" on the US disc).
* Layout (virtual px): emblem (12, 11), portrait (22, 24, 52 x 64), title (80, 26), glyph (42, 62), next nine turns as cards from (84, 41), step 26 (18.5 while choosing a target);
  command header (0, 258, 240 x 50), carousel rows from y 309, pitch 25.5, bars 218 wide; help strip y 410..436; party rows right-aligned name ending x 323, gauges at x 325 / 376 / 428 (47 wide),
  bottom row y 377, pitch 25, the acting row is the teal-to-navy band; target plate (290, 49, 148 x 69) top right with the letter card, the name, `HP ?????` and the red arrow over the enemy.
* The command window is a **carousel**: the cursor entry is the header, the next three follow below; `Attack < Standard >` carries the shape inline (Left / Right change it, Confirm goes straight
  to the target list: `BtlMenu::shape`, `Button::{Left, Right}`).  In target mode only the acting character's row stays and the strip compresses.  `plugin::build_hud_view` assembles `HudView`; the old
  blue stand-ins remain as the fallback when the art is not on the disc.
* Not done: damage numbers (real: `BTL_002` digit sheets), the victory screen (`BTL_002` "Battle Bonus" art), status icons, the real cursor glow sprite, exact gradients of the header / plate frame;
  the ring and later states could not be captured (the pad pulses stopped registering after the target list).

### HUD follow-ups (2026-10-10, second round)
1. **Command entries**: the retail special-command label depends on the party member (`MenuBuild::special_label`, demo `BtlMenuItem` numbering mapped through `us_of`): Nicolai (PC 0xb) =
   `White Magic` (US label 23, help `note_of(25)`), Karin (5) = `Sword Arts` (19, hidden while no skill is learned, as in the real list), others `Special Skills` (26).  Root order is the same as
   the real captures: Attack, [special], Items, Defend, Combo, Run Away.  Yuri's list cannot be verified (not in the retail party): Attack, Crest Magic, [Fusion], Items, Defend, Combo, Run Away from
   `ui::BtlMenu::new`.  The real per-PC label table is in the retail `SetMainMenu` (not decompiled; the JP one is a static table).
2. **Help line**: on the `Attack` row it is the *shape's* help (`BtlText::note(1 + shape)`: Standard = "Attack enemy and push them backwards.").
3. **Camera at the command menu** -- live data (PINE, CBattle* @0x00440000, `pCamera` = CBattle+0x45c4 in the US build, found in the `CBattle` constructor): Nicolai's turn, shot 2 of
   `SetCharacterCamera1` (mode 7 state 4 / 8): PS2 eye (4.16, -16.78, -37.88), focus F (-2.88, -16.78, -50.24), pitch 0, yaw -156 deg, D = 14.98, fov 768.  Fighters sit at z ~ -50 (party row)
   in the real battle where the port's `BtlChrPosInit` gives ~ -33 (BBG 077 `DAT` z = 150 -> -(150/10) - 15 - R): the original's arena depth value or radius differs (not resolved: US `BtlChr`
   offsets of position / radius differ from the JP decompile, `+0x150` is the PCParam pointer, `+0x160` the position, `+0x390 / +0x3a0 / +0x3b0` = camera offset / box centre / box size).  The
   port's camera constants were left as they are; `SH2_BATTLE_MENU_AGE=<ticks>` photographs a later shot of the cycle (600 = shot 2).  Open: reconcile the formation depth, the focus height (16.8 above
   the floor in the real shot) and Karin's position.
4. **Stage brightness**: BBG geometry is vertex-lit (baked colours 7..255 / 128); the `LIGHT` chunk lights the *characters*, so it was not applied; no brightness change was made.
5. **HUD states from BTL_002** (`hud::{draw_floater, draw_result}`, art real, layout not captured from the live game): damage / heal numbers use the white digits of `BTL_002` entry 8, the victory
   screen is the `Battle Bonus` panel (entry 4 gold titles, entry 5 `Exp. Cash. Soul. Item.` strip + big digits, entry 6 panel), the turn strip / party panel are hidden on it.  Status icons and the
   ring-phase HUD were not touched (the ring is `sh2_gfx::effects::jring`; the "Press O" prompt is still the stand-in text).
Side-by-sides are in `screens/battle_cmp/` (`port_victory_battle_bonus.png`, `port_damage_number.png`, `port_ring_phase.png`, `port_command_menu_age600_nicolai_whitemagic.png`).  `SH2_SCREEN=native` for pixel comparisons.

### Formation and camera verified against the live battle (2026-10-10, third round)
* Save state 8 (first AP_03_U encounter, MONSET 2 = Revenant, Revenant, Statue, BBG 077) read over PINE (CBattle* @0x00440000; US `BtlChr` stride 0x510 from CBattle+0: `+0x150` PCParam ptr,
  **`+0x160` position, `+0x170` home, `+0x184` yaw**, `+0x390` camera offset, `+0x3a0` box centre, `+0x3b0` box size).  Party home z -32.70, x +-8.7; enemies in the wide variant of formation 4 (x -28.4 /
  +28.5 / -18.1, z 2.3 / 3.2 / 19.2); final positions = home - Rot(yaw) * box offset: all within 0.5 of `formation::layout` + `feet` (test `formation::tests::matches_the_live_retail_battle`).  The earlier
  "z = -50" reading was the units still walking in.  Radii from the `bbx` first record match the live values (Nicolai 2.686, Revenant 2.314, Karin 2.70 with her model 006 box).
* **Facing**: party yaw 180 +- 29.47 deg (Nicolai x<0: 150.53, Karin x>0: 209.45), enemies 0 +- 29.47 (Revenants -29.47 / +29.47, the Statue -10.25), sign = side of the centre line:
  `models::side_facing` (Bevy forward = (sin yaw, 0, cos yaw)).
* **Camera shot 1** (mode 7, state 2) live: eye (-8.45, -7.93, -7.19), focus (-8.62, -11.18, -32.70), D 25.67 (= 15 + radius + |box size|), fov 512, ry = facing + 30.  Fixed: the shot yaws are
  `front - 30 * side` (shot 1) / `front - 60 * side` (2) / `front + 35 * side` (3) in the port's mirrored orbit convention; the focus is the *box centre* (`CamChr::cam_off` = rotated box offset, y = -off.y)
  and `height` = box size y.  Port at the same state: eye (-8.12, 7.93, 6.44) vs live (-8.45, 7.93, 7.19), focus y 11.51 vs 11.18.  Test `camera::tests::shot_one_matches_the_live_retail_camera`.
* The retail ring prompt text is not drawn (only the JP build keeps "Press O ...").
* Blocked: the emulator was paused (title screen, slot 13 no longer loads the field state; PINE cannot resume) so the live ring / damage / Battle Bonus captures and a real-vs-port frame of shot 1
  could not be taken; slot 8 gives readable memory but a frozen display.

### Victory / messages / game over (2026-10-10, U2 pass) -- `notes/integration/battle_ui_u2.md`
`sh2_battle::hud_result`: the retail `BtlBonus` "You Get!" panel (geometry decoded from `SLUS_210.41` `MakePacket`), the `BtlResult`
count-up screen (JP `WinCreate` layout, `BTL_002` art, level-up flip), `BMesWin` message windows (action name top right, ambush /
combo / run-away / couldn't-get-away), the phase 0x15 / 0x16 / 8 timelines (camera + HUD close at 0.5 s, `Skip` prompt, 4 s hold,
fade, result screen; defeat fade at 3.5 s -> game over with the retail `MENU/IMG/EX/GO_%03d.TEX`).  Screens: `screens/battle_ui/u2_*.png`.
