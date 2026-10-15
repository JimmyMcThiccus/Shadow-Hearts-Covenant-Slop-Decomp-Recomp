//! `SH2_PERF=<file>`: per-scene CPU profile of a run (round 6 PF, `notes/integration/r6_pf.md`).
//!
//! Every frame is filed under a *segment* key (`Scene` + map + "menu" / "cut" / "wm" qualifiers).  Per segment the report gives the
//! frame time distribution, the main-app (`main app` span) and render-app (`sub app RenderApp` span) time per frame, the number of
//! `Assets<Image>` / `Assets<Mesh>` / material change events per frame (each `Modified` = a full GPU re-upload of that asset) and, when the
//! binary is built with `--features profile` (`bevy/trace`: one span per system), the systems ranked by total time.
//!
//! The report is rewritten every 5 s and at exit.  The span layer is a tiny aggregating `tracing` layer (no trace file): it costs
//! ~0.1 us per span enter/exit, so it can stay on for a whole autoplay run.  Without `SH2_PERF` nothing is installed.

use std::cell::RefCell;
use std::collections::HashMap;
use std::io::Write;
use std::sync::{Mutex, OnceLock};
use std::time::Instant;

use bevy::asset::AssetEvent;
use bevy::log::tracing_subscriber::{layer::Context, registry::LookupSpan, Layer};
use bevy::prelude::*;
use tracing::field::{Field, Visit};
use tracing::span::{Attributes, Id};
use tracing::Subscriber;

use sh2_core::game::Scene;

/// which thread a span ran on: 0 = main, 1 = render thread (the pipelined-rendering thread), 2 = task pool workers
fn thread_class() -> usize {
    THREAD_CLASS.with(|c| {
        let mut c = c.borrow_mut();
        if c.is_none() {
            *c = Some(if std::thread::current().name() == Some("main") { 0 } else { 2 });
        }
        c.unwrap()
    })
}

thread_local! {
    static THREAD_CLASS: RefCell<Option<usize>> = const { RefCell::new(None) };
    static STACK: RefCell<Vec<(u64, Instant)>> = const { RefCell::new(Vec::new()) };
}

const CLASSES: [&str; 3] = ["main", "render", "worker"];

#[derive(Default)]
struct SpanAgg {
    /// (label, thread class) -> (total ns, count) since the last frame boundary
    frame: HashMap<(String, usize), (u64, u32)>,
}

fn agg() -> &'static Mutex<SpanAgg> {
    static A: OnceLock<Mutex<SpanAgg>> = OnceLock::new();
    A.get_or_init(Default::default)
}

struct Label(String);

struct NameVisitor(Option<String>);
impl Visit for NameVisitor {
    fn record_str(&mut self, f: &Field, v: &str) {
        if f.name() == "name" {
            self.0 = Some(v.to_string());
        }
    }
    fn record_debug(&mut self, f: &Field, v: &dyn std::fmt::Debug) {
        if f.name() == "name" {
            self.0 = Some(format!("{v:?}"));
        }
    }
}

struct PerfLayer;

impl<S: Subscriber + for<'a> LookupSpan<'a>> Layer<S> for PerfLayer {
    fn on_new_span(&self, attrs: &Attributes<'_>, id: &Id, ctx: Context<'_, S>) {
        let mut v = NameVisitor(None);
        attrs.record(&mut v);
        let base = attrs.metadata().name();
        let label = match v.0 {
            // system spans: "system" name = "crate::module::fn"; keep the path (it says who owns the system)
            Some(n) if base == "system" => n,
            Some(n) => format!("{base} {n}"),
            None => base.to_string(),
        };
        if let Some(span) = ctx.span(id) {
            span.extensions_mut().insert(Label(label));
        }
    }

    fn on_enter(&self, id: &Id, ctx: Context<'_, S>) {
        if let Some(span) = ctx.span(id) {
            if span.metadata().name() == "render thread" {
                THREAD_CLASS.with(|c| *c.borrow_mut() = Some(1));
            }
        }
        STACK.with(|s| s.borrow_mut().push((id.into_u64(), Instant::now())));
    }

    fn on_exit(&self, id: &Id, ctx: Context<'_, S>) {
        let Some((sid, t0)) = STACK.with(|s| {
            let mut s = s.borrow_mut();
            let pos = s.iter().rposition(|(i, _)| *i == id.into_u64())?;
            Some(s.remove(pos))
        }) else {
            return;
        };
        let _ = sid;
        let ns = t0.elapsed().as_nanos() as u64;
        let Some(span) = ctx.span(id) else { return };
        let ext = span.extensions();
        let Some(Label(l)) = ext.get::<Label>() else { return };
        let class = thread_class();
        let mut a = agg().lock().unwrap();
        let e = a.frame.entry((l.clone(), class)).or_default();
        e.0 += ns;
        e.1 += 1;
    }
}

/// `LogPlugin::custom_layer`: the aggregating span layer (only with `SH2_PERF`)
pub fn custom_layer(_app: &mut App) -> Option<bevy::log::BoxedLayer> {
    std::env::var_os("SH2_PERF")?;
    Some(Box::new(PerfLayer))
}

#[derive(Default)]
struct Segment {
    frames: u32,
    seconds: f64,
    frame_ms: Vec<f32>,
    spans: HashMap<(String, usize), (u64, u32)>,
    image_mod: u64,
    image_add: u64,
    mesh_mod: u64,
    mesh_add: u64,
    mat_mod: u64,
    entities_max: u32,
    first_seen: f64,
}

#[derive(Resource)]
struct PerfState {
    out: std::path::PathBuf,
    start: Instant,
    last: Option<Instant>,
    last_write: Instant,
    order: Vec<String>,
    segs: HashMap<String, Segment>,
}

pub struct PerfPlugin;

impl Plugin for PerfPlugin {
    fn build(&self, app: &mut App) {
        let Some(out) = std::env::var_os("SH2_PERF") else { return };
        let now = Instant::now();
        app.insert_resource(PerfState { out: out.into(), start: now, last: None, last_write: now, order: Vec::new(), segs: HashMap::new() })
            .add_systems(Last, perf_frame);
    }
}

fn segment_key(world: &World) -> String {
    let scene = world.get_resource::<State<Scene>>().map(|s| *s.get()).unwrap_or_default();
    let mut k = format!("{scene:?}");
    if world.contains_resource::<sh2_field::worldmap_plugin::WorldMapRuntime>() {
        k.push_str(" worldmap");
    } else if scene == Scene::Field {
        if let Some(rt) = world.get_resource::<sh2_field::plugin::FieldRuntime>() {
            k.push(' ');
            k.push_str(&rt.map);
        }
    }
    if let Some(c) = world.get_resource::<sh2_field::cutscene_plugin::CutsceneStatus>() {
        if c.state == sh2_field::cutscene_plugin::CutsceneState::Playing {
            k.push_str(" cutscene ");
            k.push_str(&c.name);
        }
    }
    if world.get_resource::<sh2_field::menu_overlay::InGameMenu>().map(|m| m.open).unwrap_or(false) {
        k.push_str(" menu");
    }
    k
}

fn count<A: Asset>(world: &mut World, cursor: &mut Option<bevy::ecs::message::MessageCursor<AssetEvent<A>>>) -> (u64, u64) {
    let Some(msgs) = world.get_resource::<Messages<AssetEvent<A>>>() else { return (0, 0) };
    let cur = cursor.get_or_insert_with(|| msgs.get_cursor_current());
    let (mut m, mut a) = (0, 0);
    for e in cur.read(msgs) {
        match e {
            AssetEvent::Modified { .. } => m += 1,
            AssetEvent::Added { .. } => a += 1,
            _ => {}
        }
    }
    (m, a)
}

#[derive(Default)]
struct Cursors {
    img: Option<bevy::ecs::message::MessageCursor<AssetEvent<Image>>>,
    mesh: Option<bevy::ecs::message::MessageCursor<AssetEvent<Mesh>>>,
    cmat: Option<bevy::ecs::message::MessageCursor<AssetEvent<ColorMaterial>>>,
    smat: Option<bevy::ecs::message::MessageCursor<AssetEvent<sh2_gfx::bevy::material::Sh2Material>>>,
}

fn perf_frame(world: &mut World, mut cur: Local<Cursors>) {
    let key = segment_key(world);
    let (im, ia) = count(world, &mut cur.img);
    let (mm, ma) = count(world, &mut cur.mesh);
    let (cm, _) = count(world, &mut cur.cmat);
    let (sm, _) = count(world, &mut cur.smat);
    let entities = world.entities().len();
    let spans = std::mem::take(&mut agg().lock().unwrap().frame);
    let mut st = world.resource_mut::<PerfState>();
    let now = Instant::now();
    let dt = st.last.replace(now).map(|p| (now - p).as_secs_f32());
    let elapsed = (now - st.start).as_secs_f64();
    if !st.segs.contains_key(&key) {
        st.order.push(key.clone());
    }
    let seg = st.segs.entry(key).or_insert_with(|| Segment { first_seen: elapsed, ..default() });
    if let Some(dt) = dt {
        seg.frames += 1;
        seg.seconds += dt as f64;
        seg.frame_ms.push(dt * 1000.0);
    }
    for (k, (ns, n)) in spans {
        let e = seg.spans.entry(k).or_default();
        e.0 += ns;
        e.1 += n;
    }
    seg.image_mod += im;
    seg.image_add += ia;
    seg.mesh_mod += mm;
    seg.mesh_add += ma;
    seg.mat_mod += cm + sm;
    seg.entities_max = seg.entities_max.max(entities);
    let exiting = world.get_resource::<Messages<AppExit>>().map(|m| !m.is_empty()).unwrap_or(false);
    let mut st = world.resource_mut::<PerfState>();
    if exiting || (now - st.last_write).as_secs_f32() > 5.0 {
        st.last_write = now;
        write_report(&st);
    }
}

fn pct(v: &[f32], p: f32) -> f32 {
    if v.is_empty() {
        return 0.0;
    }
    v[(((v.len() - 1) as f32) * p).round() as usize]
}

fn write_report(st: &PerfState) {
    let mut s = String::new();
    use std::fmt::Write as _;
    for key in &st.order {
        let seg = &st.segs[key];
        if seg.frames < 30 {
            continue;
        }
        let mut v = seg.frame_ms.clone();
        v.sort_by(|a, b| a.partial_cmp(b).unwrap());
        let n = seg.frames as f64;
        let per = |label: &str, class: usize| seg.spans.get(&(label.to_string(), class)).map(|e| e.0 as f64 / n / 1e6).unwrap_or(0.0);
        let _ = writeln!(
            s,
            "== {key}  (t={:.0}s, {} frames, {:.1} s)\nframe ms: mean {:.2} p50 {:.2} p95 {:.2} p99 {:.2} max {:.2}\nmain app {:.2} ms/frame, render app {:.2} ms/frame, winit {:.2}\nper frame: image Modified {:.2} Added {:.2}, mesh Modified {:.2} Added {:.2}, material Modified {:.2}; entities max {}",
            seg.first_seen,
            seg.frames,
            seg.seconds,
            seg.seconds * 1000.0 / n,
            pct(&v, 0.5),
            pct(&v, 0.95),
            pct(&v, 0.99),
            v.last().copied().unwrap_or(0.0),
            per("main app", 0),
            per("sub app RenderApp", 1),
            per("winit event_handler", 0),
            seg.image_mod as f64 / n,
            seg.image_add as f64 / n,
            seg.mesh_mod as f64 / n,
            seg.mesh_add as f64 / n,
            seg.mat_mod as f64 / n,
            seg.entities_max,
        );
        let mut top: Vec<_> = seg
            .spans
            .iter()
            .filter(|((l, _), _)| !matches!(l.as_str(), "main app" | "update" | "bevy_app" | "render thread" | "winit event_handler") && !l.starts_with("sub app") && !l.starts_with("schedule") && l != "multithreaded executor")
            .collect();
        top.sort_by(|a, b| b.1 .0.cmp(&a.1 .0));
        let mut sched: Vec<_> = seg.spans.iter().filter(|((l, _), _)| l.starts_with("schedule")).collect();
        sched.sort_by(|a, b| b.1 .0.cmp(&a.1 .0));
        for ((l, c), (ns, cnt)) in sched.iter().take(12) {
            let _ = writeln!(s, "  {:>8.3} ms/f  {:>6.1}/f  [{}] {}", *ns as f64 / n / 1e6, *cnt as f64 / n, CLASSES[*c], l);
        }
        let _ = writeln!(s, "  -- systems / spans");
        for ((l, c), (ns, cnt)) in top.iter().take(30) {
            let _ = writeln!(s, "  {:>8.3} ms/f  {:>6.1}/f  [{}] {}", *ns as f64 / n / 1e6, *cnt as f64 / n, CLASSES[*c], l);
        }
        s.push('\n');
    }
    if let Ok(mut f) = std::fs::File::create(&st.out) {
        let _ = f.write_all(s.as_bytes());
    }
}
