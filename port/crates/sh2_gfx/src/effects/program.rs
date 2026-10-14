//! A running effect program (`EffectCore::Create` + `Run` + `Continue`): an `EFMG` image (EFFECT.PKB `.EFD`, FIELD/EFF `.EFD`, LSD `.EFD` tracks) on the shared
//! VEC interpreter ([`sh2_script::vsm`]) with the effect host [`FxHost`] (the [`super::scene::FxScene`] state + the battle-side conventions: shot / cylinder hit
//! tests, the `btlEffectDamageSet` hit frame, handles).  Moved here from `sh2_battle::effects_bridge` (round 5) so the field and the cut scene player can run
//! programs without the battle crate; `sh2_battle::effects_bridge` re-exports everything.

use std::sync::Arc;

use glam::Vec3;
use sh2_script::efmg::{kind, Efmg, Heco};
use sh2_script::vsm::{Machine, SysCalls, Vec3 as VmCtx};

use super::scene::{FxActor, FxAssets, FxEnv, FxEvent, FxScene, FxView};

/// Hard stop (30 Hz ticks) for programs that wait for something the host never provides.  25 s: the longest retail program that ends on its own
/// (`113` *For the Child...*) runs 652 ticks; `btlSetWait` programs end at their `btlGetWait` poll ([`super::scene::FxScene::parked`]).
pub const MAX_TICKS: u32 = 30 * 25;

/// Where the effect happens: `GetModelSet(0, i)` = generating (casting) models, `GetModelSet(1, i)` = targets.  Positions are **Bevy** world feet.
#[derive(Clone, Debug, Default)]
pub struct FxContext {
    pub gen: Vec<Vec3>,
    pub targets: Vec<Vec3>,
    pub height: f32,
}

/// PS2 world <- Bevy world.
pub fn bevy_to_ps2(v: Vec3) -> Vec3 {
    Vec3::new(v.x, -v.y, -v.z)
}

impl FxContext {
    /// The skeleton-less environment of a context (used before the models publish their bones).
    pub fn to_env(&self) -> FxEnv {
        let mk = |v: &Vec<Vec3>| v.iter().map(|&p| FxActor::at(bevy_to_ps2(p), self.height)).collect::<Vec<_>>();
        FxEnv { gen: mk(&self.gen), targets: mk(&self.targets), scene_lights: vec![] }
    }
}

pub struct FxHost {
    pub ctx: FxContext,
    pub env: FxEnv,
    pub scene: FxScene,
    pub events: Vec<FxEvent>,
    pub tick: u32,
    /// tick of the last `hitCreateShot/Cylinder`: `hitIsModel*Hit` reports a hit 6 ticks later
    shot_born: u32,
    last_damage: std::collections::HashSet<(i32, i32)>,
    damage_at: std::collections::HashMap<(i32, i32), u32>,
    next_handle: u32,
    pub log: Vec<String>,
    pub unknown: std::collections::BTreeMap<&'static str, u32>,
    /// development: when `Some`, every system call is logged as `"t<tick> <id> <name>(int/float args)"` (capped at 4000 lines)
    pub trace: Option<Vec<String>>,
}

impl FxHost {
    fn new(ctx: FxContext, assets: Arc<FxAssets>) -> Self {
        let env = ctx.to_env();
        FxHost {
            ctx,
            env,
            scene: FxScene::new(assets),
            events: vec![],
            tick: 0,
            shot_born: 0,
            last_damage: Default::default(),
            damage_at: Default::default(),
            next_handle: 0x8000,
            log: vec![],
            unknown: Default::default(),
            trace: std::env::var_os("SH2_FX_TRACE").map(|_| Vec::new()),
        }
    }
    fn handle(&mut self) -> u32 {
        self.next_handle += 1;
        self.next_handle
    }
}

impl SysCalls for FxHost {
    fn syscall(&mut self, vm: &mut VmCtx<'_>, id: i32, a: &[u32]) {
        if let Some(t) = self.trace.as_mut() {
            if t.len() < 4000 {
                let args: Vec<String> = a.iter().map(|&o| {
                    let (i, f) = (vm.read_i32(o), vm.read_f32(o));
                    if f.is_finite() && f.abs() > 1e-6 && f.abs() < 1e7 && (i.abs() > 0x10000) { format!("{f:.3}") } else { format!("{i}") }
                }).collect();
                let s = a.iter().map(|&o| vm.read_cstr(o)).filter(|s| s.len() > 2 && s.bytes().all(|b| b.is_ascii_graphic() || b == b' ')).collect::<Vec<_>>().join("|");
                t.push(format!("t{} {id} {}({}) {s}", self.tick, super::scene::syscall_name(id), args.join(", ")));
            }
        }
        if self.scene.syscall(vm, id, a, &self.env) {
            return;
        }
        let arg = |k: usize| a.get(k).copied().unwrap_or(0);
        let ri = |vm: &VmCtx<'_>, k: usize| vm.read_i32(arg(k));
        match id {
            1106 => {
                // btlEffectDamageSet(side, idx, ..., out at args[12]) -> CBattle::EffectDamageSet
                let (side, idx) = (ri(vm, 0), ri(vm, 1));
                // a looping script may call this every iteration: report each valid target once per 8 ticks
                let n = if side == 0 { self.env.gen.len() } else { self.env.targets.len() } as i32;
                let recent = self.damage_at.get(&(side, idx)).map(|&t| self.tick < t + 8).unwrap_or(false);
                if idx >= 0 && idx < n.max(1) && !recent && self.last_damage.insert((side, idx)) {
                    self.damage_at.insert((side, idx), self.tick);
                    self.events.push(FxEvent::Damage { side, index: idx, power: if a.len() > 7 { ri(vm, 7) } else { 100 }, extra: if a.len() > 8 { ri(vm, 8) } else { 0 } });
                }
                if a.len() > 12 {
                    vm.write_u32(arg(12), 0);
                }
            }
            // ---- hit*
            1300 | 1313 => {
                // hitCreateCylinder(id, out)
                self.shot_born = self.tick;
                let h = self.handle();
                vm.write_u32(arg(1), h);
            }
            // hitIsModelCylinderHit / hitIsModelShotHit(.., idx, out): 0 flying, 1 hit
            1303 | 1306 => {
                let r = if self.tick >= self.shot_born + 6 { 1 } else { 0 };
                vm.write_u32(arg(2), r);
            }
            1302 | 1305 => vm.write_u32(arg(1), 1), // hitIsEndCylinder / hitIsEndShot(.., out): ended
            1304 => {
                self.shot_born = self.tick;
                let h = self.handle();
                vm.write_u32(arg(3), h);
            }
            1315 => vm.write_u32(arg(1), 6), // hitGetShotHitFrame
            1307 | 1308 | 1310 | 1311 | 1312 | 1314 => {}
            // btl*: nothing to do in the port (the battle flow owns status / idle motions)
            1100 | 1101 | 1104 | 1110 | 1112 | 1116 | 1117 | 1118 | 1119 | 1120 | 1121 | 1122 | 1123 | 1125 | 1128 | 1130 | 1131 | 1132 | 1133 => {
                if id == 1119 || id == 1132 {
                    // btlCharacterTargetMove(.., out): finished at once; btlSetBGMParam
                    if a.len() > 6 {
                        vm.write_u32(arg(6), 1);
                    }
                }
                if id == 1120 || id == 1121 || id == 1118 {
                    // btlGetWeponWorldPos/Rot / btlGetWarpPos(kind, idx, .., out vec): the character's hand ~ the root
                    let (k, i) = (ri(vm, 0), ri(vm, 1));
                    let p = self.env.actor(k, i).map(|x| x.pos).unwrap_or(Vec3::ZERO);
                    if id == 1120 && a.len() > 3 {
                        for (n, x) in [p.x, p.y - 12.0, p.z, 1.0].iter().enumerate() {
                            vm.write_f32(arg(3) + 4 * n as u32, *x);
                        }
                    }
                }
            }
            2600 | 2601 => {} // strStrCopy / strStrNCopy: scripts only use them for debug names
            3100 => vm.write_u32(arg(0), 0), // padGetKeyPress
            _ => {
                *self.unknown.entry(super::scene::syscall_name(id)).or_default() += 1;
            }
        }
    }

    fn print(&mut self, s: &str) {
        if self.log.len() < 16 {
            self.log.push(s.to_string());
        }
    }
}

/// A running effect program.
pub struct FxProgram {
    pub id: i32,
    pub assets: Arc<FxAssets>,
    machine: Machine,
    pub host: FxHost,
    pub ticks: u32,
    pub finished: bool,
}

impl FxProgram {
    /// `EffectCore::Create` + `Run` for the EFMG image `file`.
    pub fn new(id: i32, file: Vec<u8>, ctx: FxContext) -> Result<Self, String> {
        let machine = {
            let efmg = Efmg::parse(&file).map_err(|e| e.to_string())?;
            let (_, sec) = efmg.iter_kind(kind::CODE).next().ok_or("no code section")?;
            let heco = Heco::parse(sec).map_err(|e| e.to_string())?;
            Machine::new(&heco)
        };
        let assets = Arc::new(FxAssets::new(id, file));
        Ok(FxProgram { id, assets: assets.clone(), machine, host: FxHost::new(ctx, assets), ticks: 0, finished: false })
    }

    /// Replace the environment (positions, skeletons, scene lights) before a step.
    pub fn set_env(&mut self, env: FxEnv) {
        self.host.env = env;
    }

    /// One effect tick (1/30 s).  Returns the events produced.
    pub fn step(&mut self) -> Vec<FxEvent> {
        if self.finished {
            return vec![];
        }
        self.ticks += 1;
        self.host.tick = self.ticks;
        self.host.last_damage.clear();
        // EffectCore::Continue: AddTimeAll, then the threads
        let env = std::mem::take(&mut self.host.env);
        self.host.scene.advance(&env);
        self.host.env = env;
        for h in std::mem::take(&mut self.host.scene.released) {
            self.machine.release_motion_wait(h);
        }
        let alive = self.machine.frame(&mut self.host);
        // `btlSetWait` + polling `btlGetWait`: the retail battle deletes the program on `BattleNext` (CBattle +0x25 bit 7) -- end it here
        if !alive || self.ticks >= MAX_TICKS || self.host.scene.parked {
            self.finished = true;
            self.machine.kill_all();
        }
        let mut ev = std::mem::take(&mut self.host.events);
        ev.extend(std::mem::take(&mut self.host.scene.events));
        ev
    }

    /// The renderable state of this tick.
    pub fn view(&self) -> FxView {
        self.host.scene.view(&self.host.env)
    }

    /// Bytes of the effect's sound bank (`1` section `n`).
    pub fn sound_bank(&self, n: u32) -> Option<Vec<u8>> {
        self.assets.section(kind::SOUND, n as u8).map(|b| b.to_vec())
    }
}

