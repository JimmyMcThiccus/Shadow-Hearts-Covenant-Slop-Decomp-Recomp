//! Measurement switches of the renderer (all off unless the variable is set; added for the round-6 GPU offload A/B runs, `notes/integration/r6_gp.md`).
//!
//! | variable | effect |
//! |---|---|
//! | `SH2_NO_VSYNC=1` | primary window `PresentMode::AutoNoVsync` (frame time = real work, not the display refresh); `=immediate` / `=mailbox` force that mode |
//! | `SH2_FRAMETIME=<label>` | log frame-time statistics (`label window scene frames mean p50 p95 p99 max` ms, then `cpu=` process CPU ms per frame over all threads, then `system=ms per frame` of the [`Scope`]-instrumented systems) every 5 s of wall clock, and append them to `SH2_FRAMETIME_OUT` (a TSV file) when set |
//! | `SH2_FIXED_DT=<fps>` | every frame advances `Time` by exactly `1 / fps` s (`TimeUpdateStrategy::ManualDuration`, `Time<Real>` included) and the main schedules run on the single-threaded executor (the multithreaded one orders the hundreds of unordered system pairs differently each run): runs become frame-deterministic, so two runs (CPU vs GPU path) photograph the same simulation frame (round 6 GPA: battle demo shots identical over 5 runs) |
| `SH2_AMBIGUITY=1` | log the system pairs of the main schedules that touch the same data without an order (schedule build warnings) |

use ::bevy::prelude::*;
use ::bevy::time::TimeUpdateStrategy;
use ::bevy::window::{PresentMode, PrimaryWindow};
use std::io::Write;
use std::time::Instant;

/// CPU time of the instrumented renderer systems (`SH2_FRAMETIME` only): name -> (total seconds, calls) of the current window.
static SCOPES: std::sync::Mutex<Vec<(&'static str, f64, u32)>> = std::sync::Mutex::new(Vec::new());

fn enabled() -> bool {
    static ON: std::sync::OnceLock<bool> = std::sync::OnceLock::new();
    *ON.get_or_init(|| std::env::var_os("SH2_FRAMETIME").is_some())
}

/// Times its lifetime into the `SH2_FRAMETIME` report (no-op otherwise).
pub struct Scope(&'static str, Option<Instant>);

impl Scope {
    pub fn new(name: &'static str) -> Scope {
        Scope(name, enabled().then(Instant::now))
    }
}

impl Drop for Scope {
    fn drop(&mut self) {
        let Some(t0) = self.1 else { return };
        let dt = t0.elapsed().as_secs_f64();
        if let Ok(mut v) = SCOPES.lock() {
            match v.iter_mut().find(|e| e.0 == self.0) {
                Some(e) => {
                    e.1 += dt;
                    e.2 += 1;
                }
                None => v.push((self.0, dt, 1)),
            }
        }
    }
}

#[derive(Resource)]
struct FrameStats {
    label: String,
    out: Option<std::path::PathBuf>,
    last: Option<Instant>,
    window_start: Option<Instant>,
    samples: Vec<f32>,
    window: u32,
    /// process CPU time (all threads: main, render, audio ...) at the window start
    cpu_start: Option<f64>,
}

/// CPU time (user + kernel, all threads) the process has used so far, in seconds.
#[cfg(windows)]
pub fn process_cpu_seconds() -> Option<f64> {
    #[repr(C)]
    #[derive(Default, Clone, Copy)]
    struct FileTime {
        lo: u32,
        hi: u32,
    }
    #[link(name = "kernel32")]
    extern "system" {
        fn GetCurrentProcess() -> *mut std::ffi::c_void;
        fn GetProcessTimes(p: *mut std::ffi::c_void, c: *mut FileTime, e: *mut FileTime, k: *mut FileTime, u: *mut FileTime) -> i32;
    }
    let (mut c, mut e, mut k, mut u) = (FileTime::default(), FileTime::default(), FileTime::default(), FileTime::default());
    // SAFETY: plain Win32 call with valid out pointers; the pseudo handle needs no closing
    let ok = unsafe { GetProcessTimes(GetCurrentProcess(), &mut c, &mut e, &mut k, &mut u) };
    let t = |f: FileTime| ((f.hi as u64) << 32 | f.lo as u64) as f64 * 1e-7;
    (ok != 0).then(|| t(k) + t(u))
}

#[cfg(not(windows))]
pub fn process_cpu_seconds() -> Option<f64> {
    None
}

fn percentile(sorted: &[f32], p: f32) -> f32 {
    if sorted.is_empty() {
        return 0.0;
    }
    let i = ((sorted.len() - 1) as f32 * p).round() as usize;
    sorted[i.min(sorted.len() - 1)]
}

fn record_frame(mut st: ResMut<FrameStats>, scene: Option<Res<State<sh2_core::game::Scene>>>) {
    let now = Instant::now();
    if let Some(prev) = st.last.replace(now) {
        st.samples.push((now - prev).as_secs_f32() * 1000.0);
    }
    let start = *st.window_start.get_or_insert(now);
    if st.cpu_start.is_none() {
        st.cpu_start = process_cpu_seconds();
    }
    if (now - start).as_secs_f32() < 5.0 || st.samples.is_empty() {
        return;
    }
    // process CPU ms per frame (all threads) over the window
    let cpu_now = process_cpu_seconds();
    let cpu_ms = match (st.cpu_start, cpu_now) {
        (Some(a), Some(b)) => (b - a) * 1000.0 / st.samples.len() as f64,
        _ => 0.0,
    };
    st.cpu_start = cpu_now;
    st.window += 1;
    let mut v = std::mem::take(&mut st.samples);
    v.sort_by(|a, b| a.partial_cmp(b).unwrap());
    let mean = v.iter().sum::<f32>() / v.len() as f32;
    let scene = scene.map(|s| format!("{:?}", s.get())).unwrap_or_else(|| "-".into());
    // per-frame CPU ms of the instrumented systems
    let frames = v.len() as f64;
    let scopes: String = SCOPES
        .lock()
        .map(|mut sc| {
            let out = sc.iter().map(|(n, t, _)| format!("\t{n}={:.3}", t * 1000.0 / frames)).collect::<String>();
            sc.clear();
            out
        })
        .unwrap_or_default();
    let line = format!(
        "{}\t{}\t{}\t{}\t{:.3}\t{:.3}\t{:.3}\t{:.3}\t{:.3}\tcpu={:.3}{}",
        st.label,
        st.window,
        scene,
        v.len(),
        mean,
        percentile(&v, 0.5),
        percentile(&v, 0.95),
        percentile(&v, 0.99),
        v.last().copied().unwrap_or(0.0),
        cpu_ms,
        scopes
    );
    log::info!("frametime\t{line}");
    if let Some(p) = &st.out {
        if let Ok(mut f) = std::fs::OpenOptions::new().create(true).append(true).open(p) {
            let _ = writeln!(f, "{line}");
        }
    }
    st.window_start = Some(now);
}

fn no_vsync(mut windows: Query<&mut Window, With<PrimaryWindow>>) {
    // `SH2_NO_VSYNC=immediate` / `mailbox` pick the mode explicitly (`1`: `AutoNoVsync`)
    let want = match std::env::var("SH2_NO_VSYNC").as_deref() {
        Ok("immediate") => PresentMode::Immediate,
        Ok("mailbox") => PresentMode::Mailbox,
        _ => PresentMode::AutoNoVsync,
    };
    for mut w in &mut windows {
        if w.present_mode != want {
            w.present_mode = want;
        }
    }
}

/// The game's main schedules (the ones whose system order decides what a frame shows).
fn deterministic_schedules() -> [::bevy::ecs::intern::Interned<dyn ::bevy::ecs::schedule::ScheduleLabel>; 5] {
    use ::bevy::ecs::schedule::ScheduleLabel;
    [PreUpdate.intern(), FixedUpdate.intern(), Update.intern(), PostUpdate.intern(), Last.intern()]
}

pub struct Sh2PerfPlugin;

impl Plugin for Sh2PerfPlugin {
    fn build(&self, app: &mut App) {
        if std::env::var_os("SH2_NO_VSYNC").is_some() {
            app.add_systems(Update, no_vsync);
        }
        if let Some(fps) = std::env::var("SH2_FIXED_DT").ok().and_then(|v| v.parse::<f64>().ok()).filter(|f| *f > 0.0) {
            app.insert_resource(TimeUpdateStrategy::ManualDuration(std::time::Duration::from_secs_f64(1.0 / fps)));
            // the multithreaded executor runs systems that have no order between them in a different order each run: single-threaded,
            // the order is the (fixed) topological one, so two runs evaluate the same frame the same way
            for label in deterministic_schedules() {
                app.edit_schedule(label, |s| {
                    s.set_executor(::bevy::ecs::schedule::SingleThreadedExecutor::default());
                });
            }
        }
        if std::env::var_os("SH2_AMBIGUITY").is_some() {
            // `SH2_AMBIGUITY=1`: log every pair of systems that touch the same data without an order (schedule build warnings)
            for label in deterministic_schedules() {
                app.edit_schedule(label, |s| {
                    s.set_build_settings(::bevy::ecs::schedule::ScheduleBuildSettings {
                        ambiguity_detection: ::bevy::ecs::schedule::LogLevel::Warn,
                        ..Default::default()
                    });
                });
            }
        }
        if let Ok(label) = std::env::var("SH2_FRAMETIME") {
            app.insert_resource(FrameStats {
                label,
                out: std::env::var_os("SH2_FRAMETIME_OUT").map(Into::into),
                last: None,
                window_start: None,
                samples: Vec::new(),
                window: 0,
                cpu_start: None,
            })
            .add_systems(Last, record_frame);
        }
    }
}
