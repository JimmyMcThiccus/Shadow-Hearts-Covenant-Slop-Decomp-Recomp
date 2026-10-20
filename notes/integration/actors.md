# Real character and monster models (field actors, battle models) and the skin-weight finding

Status 2026-10-09: the capsules / boxes are gone.  The field shows the party leader (`FIELD/MODEL/005.SET`) with idle / walk / run motions, the battle
shows the party (`BTLDATA/CHR/nnn.BCM+ANM`) and the monsters of the monster set with idle / dash / attack / damage / death / win motions.
Screenshots: `screens/actors_field_ap_00_u_model005.png`, `actors_field_ap_02_u_model018.png` (controlled actor in the real map), `actors_battle_ring_dash_wolf.png`, `actors_battle_hold.png` (battle), `skin_pc_mags_shoulder.png`, `field_set_models_000_001_005_018_006.png`,
`btl_models_atck_005_404_418.png`.  Development viewer: `cargo run -p sh2_gfx --example char_view -- <files> [--motion m --time s --zoom z --shot out.png]`.

## 1. The skin weight (resolved)

`SkinAtomicPack2` has **no per-vertex blend weight**.  Disassembled VU1 programs `_dma_61` (0x003e3e00, 264 instructions) and `_dma_202`
(0x003e94a0, 231): per vertex `MTIR vi13, vf15w` (low 16 bits of the `w` word), `IADDIU vi13, vi13, 179`, `IAND vi13, vi13, 255`, then
`LQ vf18..vf21, 0..3(vi13)` and one `MULAx/MADDAy/MADDAz/MADDw` chain: **one 4x4 matrix per vertex**, selected by `slot*5 + bank` (`initPacket`
rewrites byte 0; bit 15 stays the strip ADC).  Bytes 2-3 of `w` are a u16 vertex identity (copies of one position share it; the face atomic
needs 9 bits) that the VU1 never reads.  The "weight" the earlier agents saw (0..255, no gradient) was that id.

The smoothness comes from **virtual frames** (`WFRH` extension block, `FrameWeight::calcWeight` 0x002577b0): the 11 `FRHD.extra_frames` of the PC
model are weighted blends (2 sources, u16 weights summing to 4096) of real frames: shoulders (`LSH0/carpL0`), collar, wrist (`ARM1/HAND0`), jaw
(`HEAD0/JAW0`).  Chunk palettes reference them as frame indices >= `FRHD.count`.  Welded vertices at the shoulders / collar all use the same
virtual frame, so they cannot tear; the old "first bone of the chunk" fallback separated them by up to 6.2 units.

Rust: `sh2_formats::model::{SkinVertex{slot,id}, FrameWeightDef, Model::frame_weights/total_frames, AtomicDef::vertex_bone_indices[_clamped]}`,
`sh2_gfx::model::ModelInstance::update_pose` (pose table = frames + virtual frames), tests `sh2_gfx/tests/skin_weight.rs` (slot/id layout, welded
vertices stay together over 12 motions of both reference models: worst separation 0, WFRH blend equals the lerp of its sources) and the visual check
`skin_pc_mags_shoulder.png` (arm raised: shoulder/elbow smooth).  Format notes: `notes/C/model_format.md`.

## 2. Other runtime features added to `ModelInstance` / `AnimatedModel`

| feature | original | Rust |
|---|---|---|
| root motion | `Model::addTime` splits the ROOT track translation off the pose and delivers it to `TranseCallBack` | `ModelInstance::strip_root`, `root_offset` (raw track vector, model axes: **the model faces -z, forward = -z**) |
| `Visible ` events | `Model::EventCallBack` sets/clears atomic `fxMode` bit 1; arg = atomic index or `0x8000\|group` (first atomic with header byte +0x17 = group) | `ModelInstance::visible` + `AnimatedModel` part visibility (without it all three hand poses A/B/C are drawn at once) |
| cross-fade | `InterSequenceControl` (`INTER_A/B`) | `ModelInstance::set_motion_blend(name, secs)` = lerp of the skinning matrices (smoothstep) |
| motion events | `Event::checkEvent` | `Motion::event_frames("MosEvent")` (hit frames; others stay raw) |
| `MdlAlpha` / `ACR` | model / atomic alpha (0..0x80), interpolated or discrete keys | `ModelInstance::model_alpha/atomic_alpha`; `animate_models` clones the atomic's material on first fade (cached materials are shared) and drives `tint.w` + blend like `bgmotion` |
| texture animation (`TXA*`, eye blink), dynamics (hair/cloth `DYNH`), blend shapes, billboards, water, shadows | | **ported 2026-10-09, section 7** |

Shared loader: `sh2_gfx::bevy::character` (`parse_character`, `CharacterCache`, `CharacterGpu` system param, `spawn_character`, `spawn_flip_root`).

## 3. Field actors (`sh2_field/src/actors.rs`)

* Files: `CField::LoadCharacter(slot, number)` -> `"%03d.SET"` -> `FIELD/MODEL/<nnn>.SET` (package: `mdl` + a hair/shadow `mdl`, `anm` x 5..23).  PC model number =
  `PcRec::model_nums[0]` (PC 5 -> 005, PC 0 -> 000, PC 1 -> 001).  Map scripts pass explicit numbers (AP_02_U: slot 0 = 018, slot 1 = 006, NPC slots 235...).
* Motions: script number -> name through `fldMotionList` (53 names, `actors::FLD_MOTION_LIST`), negative numbers are packed names
  (`encode_motion_name`/`decode_motion_name`); `SetMoveMotion` defaults (1, 2, 3) = `fidl`, `walk`, `run`.
* API for the script host (all in `sh2_field::actors`):
  * `ActorPlugin` (add after `FieldPlugin`; `sh2_app/src/main.rs` registers it): spawns the controlled actor as slot 0 (`ActorKind::Player`) with the model the map script loaded into the
    control slot (`LoadCharacter(0, n)`: AP_02_U loads 018 = the priest), else after ~0.2 s the party leader's model (the script may replace it later: reload on `Actor::generation`),
    removes the capsule meshes of `plugin.rs` (`FieldPlayerMesh`; `ActorSettings{auto_player, replace_capsule}`), mirrors `FieldRuntime::sim.player` (pose, gait, `FieldLightSubject`) and drives the motions.
    `plugin.rs::bridge_actors` (other agent) already feeds NPC slots / motions / move motions through `ActorCommands`.
  * `CharacterModel` component on every actor root: `set_motion("fidl")`, `set_motion_id(2)`, `chain_motion`, `set_move_motion(idle, walk, run)`,
    `play_move_motion(MoveGait)`, `motion_finished()`, `blend`, `rate`.
  * `ActorCommands` resource (`ActorCommand::{Load(ActorSpawn), Unload(slot), SetMotion, ChainMotion, SetMoveMotion, SetPose, SetVisible}`) applied every `Update`;
    `ActorSpawner` system parameter / `spawn_actor(...)` for direct spawning; `ActorRegistry` (slot -> entity); `ActorPose` component (game space: y down, heading 0 = +z).
* Movement vs animation: the original moves the actor by the walk/run root translation (0.30 / 0.83 units per 60 Hz tick: `CharacterAsset::root_speed`).  `sim::WALK_SPEED` /
  `RUN_SPEED` (1.6 / 3.2) are placeholders ~5x too fast, so the skeleton plays in place and its rate is scaled to the real speed (clamped 0.7..2.5): feet slide.  Adopting the
  authentic speeds in `sim.rs` removes that and makes the walk cycle exact (the map is ~3x slower to cross; the autoplay timeouts would need review).
* Facing: model faces -z; under the PS2->Bevy flip identity looks along Bevy +z; the simulation heading `yaw` ("moving along (sin yaw, -cos yaw)" in Bevy space) is
  `Quat::from_rotation_y(PI - yaw)` (`actors::pose_transform`).

## 4. Battle models (`sh2_battle/src/models.rs`)

* Files: `BTLDATA/CHR/%03d.BCM` (+`.ANM`): party number = `PcRec::model_nums[0]`; monster number = **u16 at `MONSTERParam+4`** (the Ghidra struct labelled it a defensive
  element; `MonsterParam::chr_model` added, `def_element` kept as it was).  Demo monsters: ids 0/1/2/9/10/11/13/15/17/19/20/28/42/76/77/80 -> CHR 418/419/420/404/405/406/35/411/413/122/123/415/426/414/435/452.
* Motions (`BtlModel::SetBtlMotion` id -> name): idle `idla`/`idlb`/`idlc` (HP > 50 % / > 25 % / below), `app` (party intro), `dsh` (dash), `atck` (fallbacks `can1`, `mage`, `dsh`: CHR 418 has no
  `atck`), damage reactions `crvd` (flinch, `PAtkHitSet` state 0x16/0x18) / `flyi` -> `lad` (launch, state 0x1b, clip spread over the flight arc) / `defa` (guard) -- **`blwa` / `flya` / `koda` are attack motions** (JP ids 0x10..0x12; CHR 418 swings with `flya`), corrected 2026-10-17, `dwn` -> `dwni` (loop) for KO, `win`, `uitm` (item), `def` (guard), `esc`.
* Choreography from `BattleRuntime` (rules engine resolves an attack in one `poll()`, so visuals follow its events): phase `Attack` of actor A -> A dashes (`dsh`, speed-matched) to 46 units in
  front of the target and waits; the first `Damage` event -> `atck` at 1.5x, ROOT track moves A forward, the target reacts at the `MosEvent` frame; `Defeated` -> `dwn`/`dwni`
  (enemies dissolve ~2 s later); after the swing A dashes home; `Victory` -> `win`.  Placeholder meshes (`BtlChr`) lose their `Mesh3d`; `plugin.rs::sync_positions` reads `BattleModel::{chr,pos}` back into `BattleRuntime::positions` for the BtlCamera port / effects. The scene light is reset to the neutral `Sh2SceneLight` for the battle and restored on exit.
* `SH2_BATTLE_MODEL_SHOTS=<dir>` writes a screenshot after every choreography step (development aid).

## 5. Gaps

* NPC slots loaded by name (`LoadCharacterByName`, `char_id == -1`) are not bridged (`bridge_actors` only handles numbers); `.SET` files that are missing in the demo (e.g. 235 renders as a 1-atomic object) just show what the data has.
* Dev aids: `SH2_ACTOR_SHOTS=<dir>` (walking screenshots), `SH2_ACTOR_DEBUG=1` (pose log), `SH2_BATTLE_MODEL_SHOTS=<dir>`.
* Lip sync, weapon models (`BTLDATA/WPN`), the `sdw` shadow models of battle packages (the port projects the visible body atomics instead), receiver-conforming shadows (stairs) are not done; eyes, blink, hair / cloth dynamics, `MdlAlpha` / `ACR`, drop shadows are (section 7).
* Battle: no `can1..4` combo motions, `mags/magi/mage` casting (menu has no magic), fusion/special motions (`fusa`.. `sp0..31`), monster attacks without `atck` use a procedural lunge, hit reaction
  choice (`blwa`/`flya`/`defa`/`koda`) is a heuristic (the original picks by attack shape / ring result), camera and stage are still the placeholders of `plugin.rs`.
* Field: `walk`/`run` cross-fade is a matrix lerp (not the `INTER_A/B` interpolation keys); `ltrn`/`rtrn` (turn) motions are not used; no floor-slope adaptation of the animation.

## 6. Verification notes (2026-10-09)

* `cargo check --workspace`, `cargo test -p sh2_gfx -p sh2_field -p sh2_battle` pass (new: `sh2_gfx/tests/{skin_weight,character_runtime}.rs`, `actors::tests`, `models::tests`).
* Autoplay runs (`--autoplay`, several agents share the default `screens/` dir, so use `--shots <dir>`): field actor spawns (018 in AP_02_U, 005 fallback), battle models for 3 PCs + monsters, choreography
  (dash -> hold -> strike -> hit/down -> gone) logged by `SH2_BATTLE_MODEL_SHOTS`.
* **Open renderer issue seen from the game app**: with the default gamma-space pipeline (HDR 3D camera + `Sh2GammaDecode`) the 3D layer of the *game* app (field and battle) renders pure black
  behind the UI; `SH2_LINEAR_BLEND=1` renders correctly (the standalone viewer / `char_view` are fine).  The screenshots above were taken with `SH2_LINEAR_BLEND=1`.  Suspect: the 2D background camera
  (order -10, clear black) / 3D camera (order 0, HDR) / UI camera (order 100) combination in `sh2_menu/src/plugin.rs`.
* The AP_02_U "walk" camera of `FieldSim` frames only floor (player out of view); not an actor problem.

## 7. Character rendering completion (2026-10-09, `sh2_gfx::{model, bevy}`)

Screens: `notes/integration/screens/characters/` (`char_view` = `cargo run -p sh2_gfx --example char_view -- <files> [--motion m --time s --zoom z --cam-y y --us --run --spin deg/s --frames n --eye i --no-floor --shot out.png]`;
`SH2_NO_DYNAMICS=1`, `SH2_NO_SHADOW=1` switch the features off; `cargo run -p sh2_gfx --example model_census [-- --us]`, `txa_dump`, `dyn_dump` are the data tools).

| feature | original | port | evidence |
|---|---|---|---|
| **Drop shadow** | `ShadowControl` (`getPacket` 0x00258ae0, `Model::ShadowProcess`): flat silhouette of the caster rendered orthographically from the shadow light into a 128x128 offscreen texture (grey 0x80 cleared), projected onto the *receiver* floor models and modulated | `bevy::shadow`: skinned vertices of every visible atomic projected along the scene light (strongest of `Sh2SceneLight`'s slots, elevation >= 35 deg) onto the actor's floor plane, rasterised on the CPU into a 64x64 texture, quad at the feet; **superseded 2026-10-09 (section 8 / renderer.md Polish pass 3): darkness 29.7 % from `_dma_228`, shadow drawn on the collision floor triangles**.  Created for every `in_place` character = field actors and battle models | `char_pc005_shadow_floor.png`, `game_field_ap_02_u_actor_shadow*.png`, `game_battle_revenant.png` |
| **Eyes / blink** | `TXAeye` events + `CFieldModel::Update` blink machine (`SetBlink`) -> `changeTextureAnim("eye", frame)` | `ModelInstance::{change_texture_anim, texanim_frame}` + `model::Blink` (30 Hz ticks: wait 64 + rand(60), close 1..n, reopen n..0; armed for the `eye` entry of every model), per-instance copy of the animated textures + materials (`bevy::texanim`, `AnimatedModel::tex_images`) so actors sharing a cached character blink independently | `blink_eye_frames_0_vs_2_pc005.png` |
| group `Visible `, `MdlAlpha`/`MCA`, `ACR`, `TexAlpha`, `PolCol*`, `Scale*` | `Model` / `ExModel::EventCallBack` | `ModelInstance::apply_events` (all of them; see notes/C/motion_format.md for which only occur on effect models) | |
| **Hair / cloth** | `DynamicsControl` + `BRN_LinkList` | `model::{brn, dynamics}` (full solver port, notes/C/Dynamics.md); 35 JP character packages simulated in `tests/dynamics_runtime.rs`; the actor's world matrix is fed from `GlobalTransform` | `dynamics_hair_pc005_turning_dyn_vs_static.png`, `dynamics_running_dyn_vs_static_018_007_057.png` |
| **Blend shape** | `BlendShapeControl` (`BSASeq01`) | `Model::blend_shapes`, `ModelInstance::shape_geometry`; only US BTLDATA/CHR 409 / 470 (frog eyelids) | `frog_eyelids_blendshape.png` |
| **Billboard** | `BAtomic::getPacket` | `bevy::billboard` (camera-facing quads, `scaleX/Y rotateZ trans*` events, first-element offset / colour quirk), drawn as ordinary parts of an `AnimatedModel` (save point `COMMON/SVP.BIN`, `BTL_001.BIN`, field effects) | `billboard_btl001_bef1.png` |
| **Water** | `WaterAtomicP1::addTime` | `model::water` (U-coordinate wobble); no model uses it | unit tests |

Findings worth remembering: the second `mdl` of a field `.SET` is a *level of detail* (`createLevelofDetale`), not a shadow model; the shadow casters are the visible atomics
of the main model.  `Frame::getWorldPos` uses the **negated** record vector (`Skeleton::pivot`).  Gravity of a `DYNH` chain defaults to 24.5 when the raw value is 0.

Gaps: `TPL` / `TPA` second-pass colour / alpha (effect models only), `BSASeq00` presets, `BoundingCircle` collision of the chains (`DHSH`), `SetDynaGRV`, `IKControl`, lip sync (`lips.rs` is
still unused by the actors), shadows on non-flat floors / shadow receivers, the exact shadow darkness, VU1 special-effect atomics (`b15 >> 4`), blink timing source (30 Hz assumed).


## 8. Dynamics / events pass (2026-10-09, `sh2_gfx::model`)

* **`DHSH` collision circles** (`BoundingCircle::Create` 0x00254860, `checkCollision` 0x00253d50, `CollisionFnc` 0x002547c0, `BRN_LinkList::applyCollisionForce` 0x0024a1c0, `calcNextLinkList`
  0x00249670, `applyForces` 0x00249b40) are ported (`model::dynamics::{BoundingCircle, parse_circles, check_collision}`, `brn::{CollisionInfo, calc_next_collide}`).  Records are 0x20 bytes
  `{vec3 centre, w, vec3 radii, pad, u32 frame}`, in the mesh space of a frame (the matrix is `model-to-world * pose[frame]`).  Per sub-step the chain is integrated once; the callback (only
  at retry index 0, it always clears the per-link `BRN_CollisionInfo` first) tests every segment (previous link or the root joint -> link) against the unit sphere of every circle
  (closest approach inside the segment, else the end point), accumulates a push direction `M * (p * inv * inv)`, the smallest squared depth and a hit count, and normalises them; a hit makes
  the step run **again** (retry 1) with `applyCollisionForce` after each link: the *velocity* component into the surface is reduced to 0.5 of itself minus the root velocity, and the link is pushed out
  by `(1 - depth) * 2` along the normal (the decompilation reads / writes `BRN_Link.vel`, not the force).  Tests: ball hit / miss / retry (`dynamics::collision_tests`); the 35 JP
  `DYNH` models stay finite (`tests/dynamics_runtime.rs`).
* **`SetDynaGRV`** (`Model::SetDynaGRV` 0x0023ff20 -> `DynamicsControl::SetDynaGRV` -> `Dynamics::SetGrv`): gravity = `dir * 24.5` (flag 0: default `(0, 24.5, 0)`).  Only the *cutscene* model
  class calls it: `MCESModel::EventCallBack` (0x0038cd90) handles the motion event `GRV<5-char model name>`: the named model's frame `0x3fffb8`'s world rotation applied to `(0, 1, 0)` gives the
  direction.  Port: `ModelInstance::grv_requests` collects the events, `ModelInstance::set_dyna_grv(dir, flag)` applies them (the LSD player resolves the other model).
* **`IKControl`** is dead code in the shipped executables: `Model+0x4a4` is zeroed by `Model::create` / `MirrorModel::createMirror` and no instruction in the main exe, FIELD.BIN or BATTLE.BIN
  ever stores to it (searched `0x4a4(` on all three), there is no `IKControl` / `IKs` constructor symbol; `IKControl::calcIK` (0x00254ba0) forwards to `IKs::calcIK` (0x00254ca0, a 3-pass
  cyclic-coordinate-descent solver that rotates each joint of a chain towards a target and re-propagates with `IKs::calcMatrix`).  Nothing to port.
* **Blink**: the machine ticks once per `CFieldModel::Update`; the field runs at 30 frames per second (`CFieldSocket::WakeUp` 0x003be4c0 calls `Gsx::SetFFMode(0, 1, 2)`, i.e. `m_syncCount = 2`), so the
  30 Hz of `model::blink` is the real rate (previously an assumption).
* **`TPL` / `TPA`** (`Model::EventCallBack` -> `Atomic::set2PathColor` 0x00242810 / `set2PathAlpha` 0x00242890, `SkinAtomicPack2` variants 0x0024f8c0 / 0x0024f910): they set the atomic's constant
  colour vector (`+0x320`, uploaded as VU1 data word 12 by `Pack1Atomic::getPacket` 0x0024d410, whose w is overwritten each frame by `atomic alpha * model alpha`), the "second pass active" bit
  (`+0x2b2 & 1`, non-zero value) and the translucent flag (`+0x2b1`, value < 0x80).  `ModelInstance::two_path` records the values; no second pass is drawn (only 268 effect-model motions
  carry `TPA`, no field / character model).
* **`BSASeq00`** (`changeShapeGrp(value2 / 4096 s, group = bone arg, shape = value)` -> `BlendShape::changeShape` / `setEndTime` / `addtime`): implemented as a weight transition
  (`ModelInstance::shape_anim`, preset k >= 1 = full weight on target k, 0 = base shape) -- unverified, no shipped data uses it.
* **Shadows**: darkness 29.7 %, receivers = collision floor, see renderer.md "Polish pass 3".

Remaining: lip sync not wired, `TPL`/`TPA` second pass, `BSASeq00` semantics unverified, collision-circle behaviour only unit-tested (no reference capture), the collision floor is the shadow receiver (not the visual floor).

## 9. Character texture alpha (2026-10-09)
Hair, lashes, lace and fringes were drawn opaque because character materials ignored the GS alpha state; they now use the map rule (PRIM ABE x default `ALPHA_1` 0x44 / `TEST_1` 0x5370b = GEQUAL 0x70, AFAIL RGB_ONLY):
an opaque cut-out draw plus a colour-only blended draw per atomic with translucent texels.  Details, evidence and screenshots: notes/integration/renderer.md "Character alpha".  Debug switch `SH2_CHAR_ALPHA_OFF=1`.
