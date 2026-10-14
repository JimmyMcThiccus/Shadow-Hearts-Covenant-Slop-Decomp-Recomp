//! Section D — effects (`EffectCore`/`Effect`, VSM scripts, `Puti*`/`Fp*` particles, `JRing`).
//!
//! * [`efmg`]     EFFECT.PKB container (`EFMG`) + `HECO` bytecode section parser
//! * [`syscalls`] the 269-entry VSM system-call table (ids + names + context kind)
//! * [`vsm`]      VSM interpreter + thread scheduler (`VEC` / `EffectCore::Continue`)
//! * [`effect`]   `Effect` / `EffectCore` lifetime (create from data, per-frame update, end callback)
//! * [`motion`]   `EFCM` camera / `EFLT` light key tables (`EffectCameraMotion`, `EffectLightMotion`)
//! * [`puti`]     `PutiObject` / `PutiPrim` / `PutiManager` billboard particle system
//! * [`fp`]       `FpPrim` fading + `FpSmoke` / `FpFlare` / `FpThunder` parameter blocks and smoke simulation
//! * [`scene`]    the state the system calls build (effect models with real motion playback, sprites, lights, `EFCM` cameras, ribbons, polygons, fader) + [`scene::FxView`] / [`scene::FxEvent`]
//! * [`render`]   Bevy drawing of an [`scene::FxView`] (`EffectRenderPlugin`, `FxLive`)
//! * [`jring`]    the Judgement Ring (battle input mechanic) — pure logic, unit tested
//! * [`bgfx`]      background effects of stages / maps (`EFFECT` chunk: `FpTorch` / `FpCandle` / `FpFlare` / `FpSmoke`)
//! * [`program`]  a running effect program (`FxProgram` = EFMG + VEC machine + [`program::FxHost`]), used by battle, field and cut scenes
//! * [`compat`]   local stand-ins for types owned by other sections
//!
//! Rendering (GS packet building, `getPacket`/`MakePacket`) is deliberately **not** ported here: the
//! logic modules produce plain data (vertex positions, UVs, colours) for the Bevy layer ([`render`]).

pub mod bbp;
pub mod btlin;
pub mod bgfx;
pub mod bng;
pub mod bgfx_misc;
pub mod bgfx_more;
pub mod bgfx_render;
pub mod compat;
pub mod effect;
pub mod efmg;
pub mod fp;
pub mod jring;
pub mod lenz;
pub mod locus;
pub mod mote207;
pub mod motion;
pub mod pathcalc;
pub mod program;
pub mod puti;
pub mod rain206;
pub mod render;
pub mod runner;
pub mod sbd;
pub mod scene;
pub mod screenfx;
pub mod screenfx_pass;
pub mod syscalls;
pub mod vsm;
