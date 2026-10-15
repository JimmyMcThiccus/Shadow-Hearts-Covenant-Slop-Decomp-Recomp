//! Cut scenes and movies: every `LSD/*.LSD` (and any other `.LSD` on the disc) decodes (`CutsceneData::load`), the event clock reaches
//! the end, the `LSCR` script runs against the op set of the cut scene host (`cutscene_plugin::LscrHost`), embedded `.EFD` effect tracks
//! run, `MPS ` map tracks parse; movie files (`MOVS` track) demux and their MPEG-2 stream decodes (first 60 pictures; all with
//! `--decode-movies`).

use super::common::*;
use sh2_field::cutscene::{CutsceneData, Playhead};
use sh2_script::cscript::{CScript, ExCtx, ExResult, ScriptHost};
use std::collections::{BTreeMap, BTreeSet};

pub fn list_lsd(disc: &sh2_core::fileio::Disc) -> Vec<String> {
    let mut v = vec![];
    for (_, files) in disc.listing() {
        for (p, _) in files {
            if p.to_uppercase().ends_with(".LSD") {
                v.push(p);
            }
        }
    }
    v.sort();
    v.dedup();
    v
}

pub fn run_all(out: &std::path::Path, fresh: bool, only: Option<&str>, decode_all: bool) {
    let disc = sh2_core::fileio::Disc::open(disc_dir()).expect("US disc");
    let disc2 = disc2_dir().and_then(|d| sh2_core::fileio::Disc::open(d).ok());
    let f1 = list_lsd(&disc);
    let f2 = disc2.as_ref().map(list_lsd).unwrap_or_default();
    let mut files: Vec<String> = f1.iter().chain(f2.iter()).cloned().collect();
    files.sort();
    files.dedup();
    eprintln!("lsd: {} LSD files (disc 1 {}, disc 2 {})", files.len(), f1.len(), f2.len());
    let mut sink = Sink::open(out, "lsd", fresh);
    for path in files {
        if !mine() || only.map(|o| !path.contains(o)).unwrap_or(false) || sink.done.contains(&path) {
            continue;
        }
        let (in1, in2) = (f1.contains(&path), f2.contains(&path));
        begin_item(&path, if decode_all { 1800 } else { 240 });
        let src = if in1 { &disc } else { disc2.as_ref().unwrap() };
        let mut row = match guarded(|| check(src, &path, decode_all)) {
            Ok(r) => r,
            Err(p) => {
                let mut r = Row::new(&path);
                r.status = "fails".into();
                r.owner = owner_of_path(&p).into();
                r.detail = p;
                r
            }
        };
        let disc_tag = match (in1, in2) {
            (true, true) => {
                // same name on both discs: identical bytes?
                let same = disc.read(&path).ok().zip(disc2.as_ref().and_then(|d| d.read(&path).ok())).map(|(a, b)| a == b).unwrap_or(false);
                if same { "both" } else { "both (differ)" }
            }
            (true, false) => "disc 1",
            _ => "disc 2",
        };
        row.kv("disc", disc_tag);
        if !in1 {
            // the port's reader (`sh2_core::fileio::Disc::open` of disc 1) must find it through the attached disc 2 (`SH2_US_DISC2_DIR`)
            if disc.read(&path).is_err() {
                row.worse("stub");
                row.add_detail("disc 2 only and the port's disc 1 reader does not find it (SH2_US_DISC2_DIR fallback of sh2_core::fileio::Disc)");
                row.add_owner("CS");
            } else {
                row.kv("via_disc2_fallback", 1);
            }
        }
        end_item();
        eprintln!("lsd {path} [{disc_tag}]: {} {}", row.status, row.detail.chars().take(120).collect::<String>());
        sink.put(&row);
    }
}

/// Records the ops; which of them `LscrHost` handles / leaves unapplied is read from cutscene_plugin.rs (`srcscan::lscr_op_state`).
struct Probe {
    subs: BTreeMap<(u8, u8), u32>,
    exit: bool,
}
impl ScriptHost for Probe {
    fn call_ex(&mut self, _ctx: &mut ExCtx<'_>, ex: u8, sub: u8) -> ExResult {
        *self.subs.entry((ex, sub)).or_default() += 1;
        if ex == 0xc0 && sub == 0x0f {
            self.exit = true;
        }
        ExResult::Void
    }
}

fn check(disc: &sh2_core::fileio::Disc, path: &str, decode_all: bool) -> Row {
    let mut row = Row::new(path);
    let bytes = match disc.read(path) {
        Ok(b) => b,
        Err(e) => {
            row.status = "fails".into();
            row.detail = format!("read: {e}");
            row.owner = "CS".into();
            return row;
        }
    };
    let name = path.rsplit('/').next().unwrap_or(path).trim_end_matches(".LSD").to_string();
    let data = match CutsceneData::load(&name, &bytes) {
        Ok(d) => d,
        Err(e) => {
            row.status = "fails".into();
            row.detail = format!("LsdContent: {e}");
            row.owner = "CS".into();
            return row;
        }
    };
    let mut missing: BTreeSet<String> = BTreeSet::new();
    row.kv("secs", format!("{:.1}", data.duration_secs()));
    row.kv("tracks", data.content.tracks.len());
    row.kv("models", data.models.len());
    for w in &data.warnings {
        row.worse("stub");
        row.add_detail(w);
        if w.contains("shared-geometry") {
            row.add_owner("FX");
            missing.insert("shared-geometry atomics".into());
        } else {
            row.add_owner("CS");
            missing.insert("model parse".into());
        }
    }
    // the event clock
    let mut head = Playhead::new(&data.content);
    let mut n_ev = 0usize;
    let mut steps = 0;
    while !head.finished() && steps < 30 * 60 * 30 {
        n_ev += head.step(1.0 / 30.0).len();
        steps += 1;
    }
    row.kv("events", n_ev);
    if !head.finished() {
        row.worse("stub");
        row.add_detail(format!("event clock did not finish after {steps} steps"));
        row.add_owner("CS");
        missing.insert("clock never ends".into());
    }
    // the script
    if let Some(img) = data.script_image() {
        let mut vm = CScript::new(16, 0x200, 5);
        match vm.init_script(Some("lscr"), img) {
            Err(e) => {
                row.worse("fails");
                row.add_detail(format!("LSCR init: {e:?}"));
                row.add_owner("CS");
            }
            Ok(()) => {
                let mut host = Probe { subs: BTreeMap::new(), exit: false };
                vm.start_script();
                let timed: Vec<u32> = sh2_script::image::ScriptImage::parse(img).map(|p| {
                    let mut t: Vec<u32> = p.events.iter().filter(|s| s.kind == 1).flat_map(|s| s.entries.iter().map(|e| e.id)).collect();
                    t.sort_unstable();
                    t
                }).unwrap_or_default();
                let mut next = 0;
                for tick in 0..(data.content.header.duration_ticks.max(1) as u32 + 60) {
                    while let Some(&t) = timed.get(next) {
                        if tick >= t {
                            vm.call_event_t(t);
                            next += 1;
                        } else {
                            break;
                        }
                    }
                    vm.poll(&mut host);
                    if host.exit {
                        break;
                    }
                }
                vm.end_scene();
                vm.poll(&mut host);
                row.kv("lscr_ops", host.subs.iter().map(|((e, s), n)| format!("{e:02x}.{s:02x}x{n}")).collect::<Vec<_>>().join(","));
                for (&(e, s), n) in &host.subs {
                    let label = field_op_name(e, s);
                    // the op set of `cutscene_plugin::LscrHost` and what `apply_script_out` does with it, read from the code (srcscan)
                    let state = if e == 0xc0 { super::srcscan::lscr_op_state(s) } else { None };
                    if state.is_none() {
                        row.worse("stub");
                        row.add_detail(format!("LSCR op {label} x{n} unknown to the cut scene host"));
                        row.add_owner("CS");
                        missing.insert(format!("LSCR {label}"));
                    } else if state == Some(true) {
                        row.worse("stub");
                        row.add_detail(format!("LSCR {label} x{n} accepted, not applied"));
                        row.add_owner("CS");
                        missing.insert(format!("LSCR {label}"));
                    }
                }
            }
        }
    }
    // effect tracks
    let mut fx_bad = 0;
    for &t in &data.efd_tracks {
        let Some(raw) = data.content.raw(t) else { continue };
        match super::fx::run_program(2000 + t as i32, raw.to_vec(), 1) {
            Err(e) => {
                fx_bad += 1;
                row.worse("fails");
                row.add_detail(format!(".EFD track {t}: {e}"));
                row.add_owner("FX");
            }
            Ok(r) => {
                for k in r.unknown.keys().chain(r.unhandled.keys()).chain(r.ignored.keys()) {
                    missing.insert(format!("fx {k}"));
                    row.worse("stub");
                    row.add_owner("FX");
                }
            }
        }
    }
    row.kv("efd", data.efd_tracks.len());
    if fx_bad == 0 && missing.iter().any(|m| m.starts_with("fx ")) {
        row.add_detail(format!("effect tracks: {}", missing.iter().filter(|m| m.starts_with("fx ")).cloned().collect::<Vec<_>>().join(", ")));
    }
    // map tracks
    for &t in &data.map_tracks {
        let Some(raw) = data.content.raw(t) else { continue };
        if let Err(e) = sh2_field::mps::Mps::parse(raw.to_vec()) {
            row.worse("fails");
            row.add_detail(format!("MPS track {t}: {e:?}"));
            row.add_owner("CS");
        }
    }
    row.kv("maps", data.map_tracks.len());
    // captions
    for ((t, lines), (_, font)) in data.captions.iter().zip(data.caption_fonts.iter()) {
        if !lines.is_empty() && font.is_none() {
            row.worse("stub");
            row.add_detail(format!("caption track {t}: no font"));
            row.add_owner("CS");
            missing.insert("caption font".into());
        }
    }
    if data.dlby_track.is_some() {
        row.kv("dlby", 1);
    }
    // movie
    if data.movie_track.is_some() {
        row.kv("movie", 1);
        match sh2_menu::movie::split_lsd(&bytes) {
            Err(e) => {
                row.worse("fails");
                row.add_detail(format!("movie demux: {e}"));
                row.add_owner("CS");
            }
            Ok((es, info)) => {
                let mut dec = sh2_gfx::ipu::mpeg2::Mpeg2Decoder::new(&es);
                let mut n = 0;
                let lim = if decode_all { usize::MAX } else { 60 };
                loop {
                    if n >= lim {
                        break;
                    }
                    match dec.next_frame() {
                        Ok(Some(_)) => n += 1,
                        Ok(None) => break,
                        Err(e) => {
                            row.worse("fails");
                            row.add_detail(format!("MPEG-2 picture {n}: {e:?}"));
                            row.add_owner("CS");
                            break;
                        }
                    }
                }
                row.kv("pictures", n);
                row.kv("size", format!("{}x{}", info.width, info.height));
                if n == 0 {
                    row.worse("fails");
                    row.add_detail("no MPEG-2 picture decoded");
                    row.add_owner("CS");
                }
            }
        }
    }
    if data.pcms_track.is_none() && data.movie_track.is_none() {
        row.kv("nopcms", 1);
    }
    if !missing.is_empty() {
        row.kv("missing", missing.into_iter().collect::<Vec<_>>().join(",").replace(';', ""));
    }
    let logs = take_log();
    if !logs.is_empty() {
        row.kv("warnings", logs.iter().map(|(_, n)| n).sum::<usize>());
    }
    row
}
